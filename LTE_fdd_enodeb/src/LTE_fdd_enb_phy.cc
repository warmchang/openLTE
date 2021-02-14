#line 2 "LTE_fdd_enb_phy.cc" // Make __FILE__ omit the path
/*******************************************************************************

    Copyright 2013-2017, 2021 Ben Wojtowicz

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*******************************************************************************

    File: LTE_fdd_enb_phy.cc

    Description: Contains all the implementations for the LTE FDD eNodeB
                 physical layer.

    Revision History
    ----------    -------------    --------------------------------------------
    11/10/2013    Ben Wojtowicz    Created file
    01/18/2014    Ben Wojtowicz    Cached a copy of the interface class, added
                                   level to debug prints, add the ability to
                                   handle late subframes, fixed a bug with
                                   transmitting SIB2 for 1.4MHz bandwidth, and
                                   added PRACH detection.
    03/26/2014    Ben Wojtowicz    Using the latest LTE library and added PUSCH
                                   decode support.
    04/12/2014    Ben Wojtowicz    Using the latest LTE library.
    05/04/2014    Ben Wojtowicz    Added PCAP support, PHICH support, and timer
                                   support.
    06/15/2014    Ben Wojtowicz    Changed fn_combo to current_tti.
    08/03/2014    Ben Wojtowicz    Added support for limiting PCAP output.
    12/16/2014    Ben Wojtowicz    Added ol extension to message queue.
    02/15/2015    Ben Wojtowicz    Moved to new message queue and changed the
                                   RTS timing.
    03/11/2015    Ben Wojtowicz    Changed the RTS timing.
    07/25/2015    Ben Wojtowicz    Combined the DL and UL schedule messages into
                                   a single PHY schedule message and using the
                                   new radio interface.
    12/06/2015    Ben Wojtowicz    Changed boost::mutex to pthread_mutex_t and
                                   sem_t.
    03/12/2016    Ben Wojtowicz    Added PUCCH support.
    07/03/2016    Ben Wojtowicz    Not including UL PDCCH allocations in a check
                                   of how many DL PRBs are being used.
    07/31/2016    Ben Wojtowicz    Added an external interface for getting the
                                   current TTIs.
    07/29/2017    Ben Wojtowicz    Added IPC direct to a UE PHY, added SR
                                   support, and using the latest LTE library.
    02/14/2021    Ben Wojtowicz    Massive reformat and using the new RRC
                                   library.

*******************************************************************************/

/*******************************************************************************
                              INCLUDES
*******************************************************************************/

#include "LTE_fdd_enb_phy.h"
#include "LTE_fdd_enb_radio.h"

/*******************************************************************************
                              DEFINES
*******************************************************************************/

#define N_TURBO_ITERATIONS 1

/*******************************************************************************
                              TYPEDEFS
*******************************************************************************/


/*******************************************************************************
                              GLOBAL VARIABLES
*******************************************************************************/


/*******************************************************************************
                              CLASS IMPLEMENTATIONS
*******************************************************************************/

/********************************/
/*    Constructor/Destructor    */
/********************************/
LTE_fdd_enb_phy::LTE_fdd_enb_phy(LTE_fdd_enb_interface *iface, LTE_fdd_enb_mac *_mac) :
    interface{iface}, started{false}, mac{_mac}
{
}
LTE_fdd_enb_phy::~LTE_fdd_enb_phy()
{
    stop();
}

/********************/
/*    Start/Stop    */
/********************/
void LTE_fdd_enb_phy::start(LTE_fdd_enb_msgq      *from_mac,
                            LTE_fdd_enb_msgq      *to_mac,
                            bool                   direct_to_ue,
                            LTE_fdd_enb_radio     *_radio)
{
    if(started)
        return;

    // Get the latest sys info
    update_sys_info();

    // Initialize phy
    radio = _radio;
    liblte_phy_init(&phy_struct,
                    radio->get_phy_sample_rate(),
                    interface->get_n_id_cell(),
                    interface->get_n_ant(),
                    interface->get_n_rb_dl(),
                    interface->get_n_sc_rb_dl(),
                    sys_info.mib.phich_Config_Get().phich_Resource_Value());
    liblte_phy_ul_init(phy_struct,
                       interface->get_n_id_cell(),
                       sys_info.sib2.radioResourceConfigCommon_Get());

    // Downlink
    for(uint32 i=0; i<10; i++)
    {
        dl_schedule[i].current_tti            = i;
        dl_schedule[i].allocations.N_dl_alloc = 0;
        dl_schedule[i].allocations.N_ul_alloc = 0;
        dl_schedule[i].allocations.N_symbs    = 2; // FIXME: Make this dynamic every subfr
        ul_schedule[i].current_tti            = i;
        ul_schedule[i].decodes.N_ul_alloc     = 0;
        ul_schedule[i].N_pucch                = 0;
    }
    pcfich.cfi = 2; // FIXME: Make this dynamic every subfr
    for(uint32 i=0; i<10; i++)
        for(uint32 j=0; j<25; j++)
            for(uint32 k=0; k<8; k++)
                phich[i].present[j][k] = false;

    dl_subframe.num = 0;
    dl_current_tti  = 0;

    // Uplink
    ul_current_tti       = liblte_phy_sub_from_tti(0, 2);
    uint8 prach_cnfg_idx = sys_info.sib2.radioResourceConfigCommon_Get().prach_Config_Get().prach_ConfigInfo_Get().prach_ConfigIndex_Value();
    prach_sfn_mod        = 1;
    if(prach_cnfg_idx ==  0 || prach_cnfg_idx ==  1 || prach_cnfg_idx ==  2 ||
       prach_cnfg_idx == 15 || prach_cnfg_idx == 16 || prach_cnfg_idx == 17 ||
       prach_cnfg_idx == 18 || prach_cnfg_idx == 31 || prach_cnfg_idx == 32 ||
       prach_cnfg_idx == 33 || prach_cnfg_idx == 34 || prach_cnfg_idx == 47 ||
       prach_cnfg_idx == 48 || prach_cnfg_idx == 49 || prach_cnfg_idx == 50 ||
       prach_cnfg_idx == 63)
        prach_sfn_mod = 2;
    prach_subfn_zero_allowed = true;
    switch(prach_cnfg_idx % 16)
    {
    case 0:
        // Intentional fall through
    case 3:
        prach_subfn_mod   = 10;
        prach_subfn_check = 1;
        break;
    case 1:
        // Intentional fall through
    case 4:
        prach_subfn_mod   = 10;
        prach_subfn_check = 4;
        break;
    case 2:
        // Intentional fall through
    case 5:
        prach_subfn_mod   = 10;
        prach_subfn_check = 7;
        break;
    case 6:
        prach_subfn_mod   = 5;
        prach_subfn_check = 1;
        break;
    case 7:
        prach_subfn_mod   = 5;
        prach_subfn_check = 2;
        break;
    case 8:
        prach_subfn_mod   = 5;
        prach_subfn_check = 3;
        break;
    case 9:
        prach_subfn_mod   = 3;
        prach_subfn_check = 1;
        break;
    case 10:
        prach_subfn_mod   = 3;
        prach_subfn_check = 2;
        break;
    case 11:
        prach_subfn_mod          = 3;
        prach_subfn_check        = 0;
        prach_subfn_zero_allowed = false;
        break;
    case 12:
        prach_subfn_mod   = 2;
        prach_subfn_check = 0;
        break;
    case 13:
        prach_subfn_mod   = 2;
        prach_subfn_check = 1;
        break;
    case 14:
        prach_subfn_mod   = 1;
        prach_subfn_check = 0;
        break;
    case 15:
        prach_subfn_mod   = 10;
        prach_subfn_check = 9;
        break;
    }

    // eNodeB communication
    msgq_from_mac = from_mac;
    msgq_to_mac   = to_mac;
    LTE_fdd_enb_msgq_cb mac_cb(&LTE_fdd_enb_msgq_cb_wrapper<LTE_fdd_enb_phy, &LTE_fdd_enb_phy::handle_mac_msg>, this);
    msgq_from_mac->attach_rx(mac_cb);

    // UE communication
    msgq_to_ue = NULL;
    if(direct_to_ue)
    {
        libtools_ipc_msgq_cb ue_cb(&libtools_ipc_msgq_cb_wrapper<LTE_fdd_enb_phy, &LTE_fdd_enb_phy::handle_ue_msg>, this);
        msgq_to_ue = new libtools_ipc_msgq("enb_ue", ue_cb);
    }

    started = true;
}
void LTE_fdd_enb_phy::stop()
{
    if(!started)
        return;

    started = false;

    if(NULL != msgq_to_ue)
        delete msgq_to_ue;

    liblte_phy_ul_cleanup(phy_struct);
    liblte_phy_cleanup(phy_struct);
}

/****************************/
/*    External Interface    */
/****************************/
void LTE_fdd_enb_phy::update_sys_info()
{
    std::lock_guard<std::mutex> lock(sys_info_mutex);
    interface->get_sys_info(sys_info);
}
uint32 LTE_fdd_enb_phy::get_n_cce()
{
    std::lock_guard<std::mutex> si_lock(sys_info_mutex);
    std::lock_guard<std::mutex> dl_lock(dl_sched_mutex);
    uint32                      N_cce;

    double phich_res = 0.0;
    switch(sys_info.mib.phich_Config_Get().phich_Resource_Value())
    {
    case PHICH_Config::k_phich_Resource_oneSixth:
        phich_res = 1/6;
        break;
    case PHICH_Config::k_phich_Resource_half:
        phich_res = 0.5;
        break;
    case PHICH_Config::k_phich_Resource_one:
        phich_res = 1.0;
        break;
    case PHICH_Config::k_phich_Resource_two:
        phich_res = 2.0;
        break;
    }
    liblte_phy_get_n_cce(phy_struct,
                         phich_res,
                         dl_schedule[0].allocations.N_symbs,
                         interface->get_n_ant(),
                         &N_cce);

    return N_cce;
}

/***********************/
/*    Communication    */
/***********************/
void LTE_fdd_enb_phy::handle_mac_msg(LTE_FDD_ENB_MESSAGE_STRUCT &msg)
{
    if(LTE_FDD_ENB_DEST_LAYER_PHY != msg.dest_layer &&
       LTE_FDD_ENB_DEST_LAYER_ANY != msg.dest_layer)
        return interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                         LTE_FDD_ENB_DEBUG_LEVEL_PHY,
                                         __FILE__,
                                         __LINE__,
                                         "Received message for invalid layer %s",
                                         LTE_fdd_enb_dest_layer_text[msg.dest_layer]);

    switch(msg.type)
    {
    case LTE_FDD_ENB_MESSAGE_TYPE_PHY_SCHEDULE:
        handle_phy_schedule(&msg.msg.phy_schedule);
        break;
    default:
        interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_WARNING,
                                  LTE_FDD_ENB_DEBUG_LEVEL_PHY,
                                  __FILE__,
                                  __LINE__,
                                  "Received invalid message %s",
                                  LTE_fdd_enb_message_type_text[msg.type]);
        break;
    }
}
void LTE_fdd_enb_phy::handle_ue_msg(LIBTOOLS_IPC_MSGQ_MESSAGE_STRUCT *msg)
{
    switch(msg->type)
    {
    case LIBTOOLS_IPC_MSGQ_MESSAGE_TYPE_KILL:
        msgq_to_ue = NULL;
        break;
    default:
        interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                  LTE_FDD_ENB_DEBUG_LEVEL_PHY,
                                  __FILE__,
                                  __LINE__,
                                  "Received invalid UE message %s",
                                  libtools_ipc_msgq_message_type_text[msg->type]);
        break;
    }
}

/*************************/
/*    Radio Interface    */
/*************************/
void LTE_fdd_enb_phy::radio_interface(LTE_FDD_ENB_RADIO_TX_BUF_STRUCT *tx_buf,
                                      LTE_FDD_ENB_RADIO_RX_BUF_STRUCT *rx_buf)
{
    if(!started)
        return;

    // Once started, this routine gets called every millisecond (except the first) to:
    //     1) align TTIs
    align_ttis_with_radio(rx_buf->current_tti);
    //     2) process the new uplink subframe
    process_ul(rx_buf);
    //     3) generate the next downlink subframe
    process_dl(tx_buf);
}
void LTE_fdd_enb_phy::radio_interface(LTE_FDD_ENB_RADIO_TX_BUF_STRUCT *tx_buf)
{
    // This routine gets called once to generate the first downlink subframe
    process_dl(tx_buf);
}

/*****************/
/*    Generic    */
/*****************/
void LTE_fdd_enb_phy::align_ttis_with_radio(uint32 radio_ul_tti)
{
    if(radio_ul_tti == ul_current_tti)
        return;

    interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                              LTE_FDD_ENB_DEBUG_LEVEL_PHY,
                              __FILE__,
                              __LINE__,
                              "Radio issue RX TTI=%u expecting %u",
                              radio_ul_tti,
                              ul_current_tti);
    ul_current_tti = radio_ul_tti;
    dl_current_tti = liblte_phy_add_to_tti(ul_current_tti, 2);

    mac->align_ttis_with_phy(ul_current_tti);
}

/******************/
/*    Downlink    */
/******************/
void LTE_fdd_enb_phy::handle_phy_schedule(LTE_FDD_ENB_PHY_SCHEDULE_MSG_STRUCT *phy_sched)
{
    if(liblte_phy_is_tti_in_future(phy_sched->dl_sched.current_tti, dl_current_tti))
    {
        std::lock_guard<std::mutex> dl_lock(dl_sched_mutex);

        if(phy_sched->dl_sched.allocations.N_dl_alloc ||
           phy_sched->dl_sched.allocations.N_ul_alloc)
        {
            interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                                      LTE_FDD_ENB_DEBUG_LEVEL_PHY,
                                      __FILE__,
                                      __LINE__,
                                      "Received PDSCH schedule from MAC CURRENT_TTI:MAC=%u,PHY=%u N_dl_allocs=%u N_ul_allocs=%u",
                                      phy_sched->dl_sched.current_tti,
                                      dl_current_tti,
                                      phy_sched->dl_sched.allocations.N_dl_alloc,
                                      phy_sched->dl_sched.allocations.N_ul_alloc);
        }
        memcpy(&dl_schedule[phy_sched->dl_sched.current_tti%10],
               &phy_sched->dl_sched,
               sizeof(LTE_FDD_ENB_DL_SCHEDULE_MSG_STRUCT));
    }else{
        interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                  LTE_FDD_ENB_DEBUG_LEVEL_PHY,
                                  __FILE__,
                                  __LINE__,
                                  "Late DL subframe (MAC=%u, PHY=%u), ignoring",
                                  phy_sched->dl_sched.current_tti,
                                  dl_current_tti);
    }

    if(liblte_phy_is_tti_in_future(phy_sched->ul_sched.current_tti, ul_current_tti))
    {
        std::lock_guard<std::mutex> ul_lock(ul_sched_mutex);

        if(phy_sched->ul_sched.decodes.N_ul_alloc)
        {
            interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                                      LTE_FDD_ENB_DEBUG_LEVEL_PHY,
                                      __FILE__,
                                      __LINE__,
                                      "Received PUSCH schedule from MAC CURRENT_TTI:MAC=%u,PHY=%u N_ul_decodes=%u",
                                      phy_sched->ul_sched.current_tti,
                                      ul_current_tti,
                                      phy_sched->ul_sched.decodes.N_ul_alloc);
        }

        memcpy(&ul_schedule[phy_sched->ul_sched.current_tti%10],
               &phy_sched->ul_sched,
               sizeof(LTE_FDD_ENB_UL_SCHEDULE_MSG_STRUCT));
    }else{
        interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                  LTE_FDD_ENB_DEBUG_LEVEL_PHY,
                                  __FILE__,
                                  __LINE__,
                                  "Late UL subframe (MAC=%u, PHY=%u), ignoring",
                                  phy_sched->ul_sched.current_tti,
                                  ul_current_tti);
    }
}
void LTE_fdd_enb_phy::process_pss_sss()
{
    if(dl_subframe.num != 0 && dl_subframe.num != 5)
        return;

    liblte_phy_map_pss(phy_struct,
                       &dl_subframe,
                       interface->get_n_id_2(),
                       interface->get_n_ant());
    liblte_phy_map_sss(phy_struct,
                       &dl_subframe,
                       interface->get_n_id_1(),
                       interface->get_n_id_2(),
                       interface->get_n_ant());
}
void LTE_fdd_enb_phy::process_pbch(uint32 sfn)
{
    if(dl_subframe.num != 0)
        return;
    sys_info.mib.systemFrameNumber_SetValue(sfn/4);
    BCCH_BCH_Message bcch_bch;
    bcch_bch.message_Set()->MasterInformationBlock_value_Set(sys_info.mib);
    std::vector<uint8_t> bits;
    bcch_bch.Pack(bits);
    dl_rrc_msg.N_bits = bits.size();
    for(uint32 i=0; i<bits.size(); i++)
        dl_rrc_msg.msg[i] = bits[i];
    interface->send_lte_pcap_msg(LTE_FDD_ENB_PCAP_DIRECTION_DL,
                                 0xFFFFFFFF,
                                 dl_current_tti,
                                 dl_rrc_msg.msg,
                                 dl_rrc_msg.N_bits);
    liblte_phy_bch_channel_encode(phy_struct,
                                  dl_rrc_msg.msg,
                                  dl_rrc_msg.N_bits,
                                  interface->get_n_id_cell(),
                                  interface->get_n_ant(),
                                  &dl_subframe,
                                  sfn);
}
void LTE_fdd_enb_phy::process_pdcch_and_pdsch()
{
    std::lock_guard<std::mutex> lock(dl_sched_mutex);

    double phich_res = 0.0;
    switch(sys_info.mib.phich_Config_Get().phich_Resource_Value())
    {
    case PHICH_Config::k_phich_Resource_oneSixth:
        phich_res = 1/6;
        break;
    case PHICH_Config::k_phich_Resource_half:
        phich_res = 0.5;
        break;
    case PHICH_Config::k_phich_Resource_one:
        phich_res = 1.0;
        break;
    case PHICH_Config::k_phich_Resource_two:
        phich_res = 2.0;
        break;
    }
    liblte_phy_pdcch_channel_encode(phy_struct,
                                    &pcfich,
                                    &phich[dl_subframe.num],
                                    &dl_schedule[dl_subframe.num].allocations,
                                    interface->get_n_id_cell(),
                                    interface->get_n_ant(),
                                    phich_res,
                                    sys_info.mib.phich_Config_Get().phich_Duration_Value(),
                                    &dl_subframe);

    if(dl_schedule[dl_subframe.num].allocations.N_dl_alloc != 0)
        liblte_phy_pdsch_channel_encode(phy_struct,
                                        &dl_schedule[dl_subframe.num].allocations,
                                        interface->get_n_id_cell(),
                                        interface->get_n_ant(),
                                        &dl_subframe);

    // Clear PHICH
    for(uint32 i=0; i<25; i++)
        for(uint32 j=0; j<8; j++)
            phich[dl_subframe.num].present[i][j] = false;
}
void LTE_fdd_enb_phy::process_dl(LTE_FDD_ENB_RADIO_TX_BUF_STRUCT *tx_buf)
{
    // Initialize the DL subframe
    dl_subframe.num = dl_current_tti%10;
    for(uint32 p=0; p<interface->get_n_ant(); p++)
        for(uint32 i=0; i<14; i++)
            for(uint32 j=0; j<LIBLTE_PHY_N_RB_DL_20MHZ*LIBLTE_PHY_N_SC_RB_DL_NORMAL_CP; j++)
                dl_subframe.tx_symb[p][i][j] = complex(0, 0);

    // Handle PSS and SSS
    process_pss_sss();

    // Handle CRS
    liblte_phy_map_crs(phy_struct,
                       &dl_subframe,
                       interface->get_n_id_cell(),
                       interface->get_n_ant());

    // Handle PBCH
    process_pbch(dl_current_tti/10);

    // Handle PDCCH & PDSCH
    process_pdcch_and_pdsch();

    for(uint32 p=0; p<interface->get_n_ant(); p++)
        liblte_phy_create_dl_subframe(phy_struct,
                                      &dl_subframe,
                                      p,
                                      &tx_buf->samps[p][0]);
    tx_buf->N_samps_per_ant = phy_struct->N_samps_per_subfr;
    tx_buf->current_tti     = dl_current_tti;
    tx_buf->N_ant           = interface->get_n_ant();

    // Update current TTI
    dl_current_tti = liblte_phy_add_to_tti(dl_current_tti, 1);

    // Send READY TO SEND message to MAC
    LTE_FDD_ENB_READY_TO_SEND_MSG_STRUCT rts;
    msgq_to_mac->send(LTE_FDD_ENB_MESSAGE_TYPE_READY_TO_SEND,
                      LTE_FDD_ENB_DEST_LAYER_MAC,
                      (LTE_FDD_ENB_MESSAGE_UNION *)&rts,
                      sizeof(rts));

    // Send samples to radio
    radio->send(tx_buf);

    // Send samples to UE
    if(NULL != msgq_to_ue)
        msgq_to_ue->send(LIBTOOLS_IPC_MSGQ_MESSAGE_TYPE_PHY_SAMPS,
                         (LIBTOOLS_IPC_MSGQ_MESSAGE_UNION *)tx_buf,
                         sizeof(LIBTOOLS_IPC_MSGQ_PHY_SAMPS_MSG_STRUCT));
}

/****************/
/*    Uplink    */
/****************/
void LTE_fdd_enb_phy::process_prach(LTE_FDD_ENB_RADIO_RX_BUF_STRUCT *rx_buf,
                                    uint32                           sfn)
{
    if((sfn % prach_sfn_mod) != 0)
        return;

    if((ul_subframe.num % prach_subfn_mod) != prach_subfn_check)
        return;

    if(ul_subframe.num == 0 && !prach_subfn_zero_allowed)
        return;

    prach_decode.current_tti = ul_current_tti;
    liblte_phy_detect_prach(phy_struct,
                            rx_buf->samps[0],
                            sys_info.sib2.radioResourceConfigCommon_Get().prach_Config_Get().prach_ConfigInfo_Get().prach_FreqOffset_Value(),
                            &prach_decode.num_preambles,
                            prach_decode.preamble,
                            prach_decode.timing_adv);

    if(prach_decode.num_preambles == 0)
        return;

    msgq_to_mac->send(LTE_FDD_ENB_MESSAGE_TYPE_PRACH_DECODE,
                      LTE_FDD_ENB_DEST_LAYER_MAC,
                      (LTE_FDD_ENB_MESSAGE_UNION *)&prach_decode,
                      sizeof(LTE_FDD_ENB_PRACH_DECODE_MSG_STRUCT));
}
void LTE_fdd_enb_phy::process_pucch()
{
    std::lock_guard<std::mutex> lock(ul_sched_mutex);

    pucch_decode.current_tti = ul_current_tti;
    for(uint32 i=0; i<ul_schedule[ul_subframe.num].N_pucch; i++)
    {
        pucch_decode.rnti           = ul_schedule[ul_subframe.num].pucch[i].rnti;
        pucch_decode.type           = ul_schedule[ul_subframe.num].pucch[i].type;
        LIBLTE_ERROR_ENUM pucch_err =
            liblte_phy_pucch_format_1_1a_1b_channel_decode(phy_struct,
                                                           &ul_subframe,
                                                           LIBLTE_PHY_PUCCH_FORMAT_1B,
                                                           interface->get_n_ant(),
                                                           ul_schedule[ul_subframe.num].pucch[i].n_1_p_pucch,
                                                           pucch_decode.msg.msg,
                                                           &pucch_decode.msg.N_bits);
        if(pucch_decode.type == LTE_FDD_ENB_PUCCH_TYPE_SR)
        {
            if(pucch_err == LIBLTE_SUCCESS)
                msgq_to_mac->send(LTE_FDD_ENB_MESSAGE_TYPE_PUCCH_DECODE,
                                  LTE_FDD_ENB_DEST_LAYER_MAC,
                                  (LTE_FDD_ENB_MESSAGE_UNION *)&pucch_decode,
                                  sizeof(LTE_FDD_ENB_PUCCH_DECODE_MSG_STRUCT));
            continue;
        }

        // LTE_FDD_ENB_PUCCH_TYPE_ACK_NACK
        pucch_decode.msg.msg[0] = 0;
        pucch_decode.msg.N_bits = 1;
        if(LIBLTE_SUCCESS == pucch_err)
            pucch_decode.msg.msg[0] = 1;
        msgq_to_mac->send(LTE_FDD_ENB_MESSAGE_TYPE_PUCCH_DECODE,
                          LTE_FDD_ENB_DEST_LAYER_MAC,
                          (LTE_FDD_ENB_MESSAGE_UNION *)&pucch_decode,
                          sizeof(LTE_FDD_ENB_PUCCH_DECODE_MSG_STRUCT));
    }
    ul_schedule[ul_subframe.num].N_pucch = 0;
}
void LTE_fdd_enb_phy::process_pusch()
{
    std::lock_guard<std::mutex> lock(ul_sched_mutex);

    for(uint32 i=0; i<ul_schedule[ul_subframe.num].decodes.N_ul_alloc; i++)
    {
        // Determine PHICH indecies
        uint32 I_prb_ra      = ul_schedule[ul_subframe.num].decodes.ul_alloc[i].prb[0][0];
        uint32 n_group_phich = I_prb_ra % phy_struct->N_group_phich;
        uint32 n_seq_phich   = (I_prb_ra/phy_struct->N_group_phich) % (2*phy_struct->N_sf_phich);

        // Add NACK to PHICH
        phich[(ul_subframe.num + 4) % 10].present[n_group_phich][n_seq_phich] = true;
        phich[(ul_subframe.num + 4) % 10].b[n_group_phich][n_seq_phich]       = 0;

        // Attempt decode
        if(LIBLTE_SUCCESS == liblte_phy_pusch_channel_decode(phy_struct,
                                                             &ul_subframe,
                                                             &ul_schedule[ul_subframe.num].decodes.ul_alloc[i],
                                                             interface->get_n_id_cell(),
                                                             1,
                                                             N_TURBO_ITERATIONS,
                                                             pusch_decode.msg.msg,
                                                             &pusch_decode.msg.N_bits))
        {
            pusch_decode.current_tti = ul_current_tti;
            pusch_decode.rnti        = ul_schedule[ul_subframe.num].decodes.ul_alloc[i].rnti;

            msgq_to_mac->send(LTE_FDD_ENB_MESSAGE_TYPE_PUSCH_DECODE,
                              LTE_FDD_ENB_DEST_LAYER_MAC,
                              (LTE_FDD_ENB_MESSAGE_UNION *)&pusch_decode,
                              sizeof(LTE_FDD_ENB_PUSCH_DECODE_MSG_STRUCT));

            // Add ACK to PHICH
            phich[(ul_subframe.num + 4) % 10].b[n_group_phich][n_seq_phich]       = 1;
        }
    }
    ul_schedule[ul_subframe.num].decodes.N_ul_alloc = 0;
}
void LTE_fdd_enb_phy::process_ul(LTE_FDD_ENB_RADIO_RX_BUF_STRUCT *rx_buf)
{
    ul_subframe.num = ul_current_tti%10;

    // Handle PRACH
    process_prach(rx_buf, ul_current_tti/10);

    // Construct the UL subframe
    ul_sched_mutex.lock();
    uint32 N_pucch = ul_schedule[ul_subframe.num].N_pucch;
    uint32 N_alloc = ul_schedule[ul_subframe.num].decodes.N_ul_alloc;
    ul_sched_mutex.unlock();
    LIBLTE_ERROR_ENUM subfr_err = LIBLTE_SUCCESS;
    if(N_pucch != 0 || N_alloc != 0)
        subfr_err = liblte_phy_get_ul_subframe(phy_struct, rx_buf->samps[0], &ul_subframe);

    // Handle PUCCH
    if(subfr_err == LIBLTE_SUCCESS && N_pucch != 0)
        process_pucch();

    // Handle PUSCH
    if(subfr_err == LIBLTE_SUCCESS && N_alloc != 0)
        process_pusch();

    // Update counters
    ul_current_tti = liblte_phy_add_to_tti(ul_current_tti, 1);
}
