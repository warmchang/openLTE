#line 2 "LTE_fdd_enb_mac.cc" // Make __FILE__ omit the path
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

    File: LTE_fdd_enb_mac.cc

    Description: Contains all the implementations for the LTE FDD eNodeB
                 medium access control layer.

    Revision History
    ----------    -------------    --------------------------------------------
    11/10/2013    Ben Wojtowicz    Created file
    01/18/2014    Ben Wojtowicz    Cached a copy of the interface class, added
                                   real-time priority to PHY->MAC message queue,
                                   added level to debug prints, and fixed
                                   subframe scheduling.
    03/26/2014    Ben Wojtowicz    Fixed the uplink decode subframe scheduling.
    04/12/2014    Ben Wojtowicz    Using the latest LTE library.
    05/04/2014    Ben Wojtowicz    Added RLC communication handling and UL and
                                   DL CCCH message processing.
    06/15/2014    Ben Wojtowicz    Added uplink scheduling and changed fn_combo
                                   to current_tti.
    08/03/2014    Ben Wojtowicz    Removed debug message.
    09/03/2014    Ben Wojtowicz    Combined the contention resolution ID and
                                   the first downlink RLC message.
    11/01/2014    Ben Wojtowicz    Added NDI toggling.
    11/29/2014    Ben Wojtowicz    Using the byte message struct for SDUs.
    12/16/2014    Ben Wojtowicz    Added ol extension to message queues.
    12/24/2014    Ben Wojtowicz    Dynamically determining MCS for downlink
                                   data.
    02/15/2015    Ben Wojtowicz    Moved to new message queue, added support
                                   for higher order modulation schemes, fixed
                                   C-RNTI release, changed RTS timing, and
                                   added DL QoS TTI frequency.
    03/15/2015    Ben Wojtowicz    Fixed RTS issues.
    07/25/2015    Ben Wojtowicz    Combined the DL and UL schedule messages into
                                   a single PHY schedule message and using a
                                   local copy of LIBLTE_MAC_PDU_STRUCT.
    12/06/2015    Ben Wojtowicz    Changed boost::mutex to pthread_mutex_t and
                                   sem_t, added and used some helper functions,
                                   fixed an issue with RTS response on late
                                   subframes, and properly initialize allocation
                                   structure (thanks to Markus Grab for finding
                                   this).
    02/13/2016    Ben Wojtowicz    Added a user inactivity timer.
    03/12/2016    Ben Wojtowicz    Added PUCCH and H-ARQ support.
    07/03/2016    Ben Wojtowicz    Fixed memcpy lengths.
    07/31/2016    Ben Wojtowicz    Reworked the RTS logic and limited the number
                                   of HARQ retransmissions.
    07/29/2017    Ben Wojtowicz    Added SR support, added IPC direct to a UE
                                   MAC, using the latest LTE library, and
                                   refactored the UL scheduler from fixed
                                   scheduling to using SR and BSR.
    02/14/2021    Ben Wojtowicz    Massive reformat, using the new RRC library,
                                   and added a persistent DL scheduler.

*******************************************************************************/

/*******************************************************************************
                              INCLUDES
*******************************************************************************/

#include "LTE_fdd_enb_user_mgr.h"
#include "LTE_fdd_enb_timer_mgr.h"
#include "LTE_fdd_enb_mac.h"
#include "LTE_fdd_enb_phy.h"

/*******************************************************************************
                              DEFINES
*******************************************************************************/

#define BSR_GRANT_SIZE_BYTES 10

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
LTE_fdd_enb_mac::LTE_fdd_enb_mac(LTE_fdd_enb_interface *iface, LTE_fdd_enb_timer_mgr *tm,
                                 LTE_fdd_enb_user_mgr *um, LTE_fdd_enb_rlc *_rlc) :
    interface{iface}, started{false}, timer_mgr{tm}, user_mgr{um}, rlc{_rlc}
{
}
LTE_fdd_enb_mac::~LTE_fdd_enb_mac()
{
    stop();
}
void LTE_fdd_enb_mac::set_phy_and_rrc(LTE_fdd_enb_phy *_phy, LTE_fdd_enb_rrc *_rrc)
{
    phy = _phy;
    rrc = _rrc;
}

/********************/
/*    Start/Stop    */
/********************/
void LTE_fdd_enb_mac::start(LTE_fdd_enb_msgq      *from_phy,
                            LTE_fdd_enb_msgq      *from_rlc,
                            LTE_fdd_enb_msgq      *to_phy,
                            LTE_fdd_enb_msgq      *to_rlc,
                            LTE_fdd_enb_msgq      *to_timer,
                            bool                   direct_to_ue)
{
    std::lock_guard<std::mutex> lock(start_mutex);

    if(started)
        return;

    started       = true;
    msgq_from_phy = from_phy;
    msgq_from_rlc = from_rlc;
    msgq_to_phy   = to_phy;
    msgq_to_rlc   = to_rlc;
    msgq_to_timer = to_timer;
    LTE_fdd_enb_msgq_cb phy_cb(&LTE_fdd_enb_msgq_cb_wrapper<LTE_fdd_enb_mac, &LTE_fdd_enb_mac::handle_phy_msg>,
                               this);
    msgq_from_phy->attach_rx(phy_cb, 90);
    LTE_fdd_enb_msgq_cb rlc_cb(&LTE_fdd_enb_msgq_cb_wrapper<LTE_fdd_enb_mac, &LTE_fdd_enb_mac::handle_rlc_msg>,
                               this);
    msgq_from_rlc->attach_rx(rlc_cb);

    msgq_to_ue = NULL;
    if(direct_to_ue)
    {
        libtools_ipc_msgq_cb ue_cb(&libtools_ipc_msgq_cb_wrapper<LTE_fdd_enb_mac, &LTE_fdd_enb_mac::handle_ue_msg>,
                                   this);
        msgq_to_ue   = new libtools_ipc_msgq("enb_to_ue");
        msgq_from_ue = new libtools_ipc_msgq("ue_to_enb", ue_cb);
    }

    // Initialize scheduler
    interface->get_sys_info(sys_info);
    for(uint32 i=0; i<10; i++)
    {
        sched_dl_subfr[i].allocations.N_dl_alloc = 0;
        sched_dl_subfr[i].allocations.N_ul_alloc = 0;
        sched_dl_subfr[i].N_avail_prbs           = interface->get_n_rb_dl() - get_n_reserved_prbs(i);
        sched_dl_subfr[i].N_sched_prbs           = 0;
        sched_dl_subfr[i].current_tti            = i;
        sched_dl_subfr[i].next_prb               = 0;

        sched_ul_subfr[i].decodes.N_ul_alloc = 0;
        sched_ul_subfr[i].N_avail_prbs       = interface->get_n_rb_ul();
        sched_ul_subfr[i].N_sched_prbs       = 0;
        sched_ul_subfr[i].current_tti        = i;
        sched_ul_subfr[i].N_pucch            = 0;
        sched_ul_subfr[i].next_prb           = 0;
    }
    sched_dl_subfr[0].current_tti = 10;
    sched_dl_subfr[1].current_tti = 11;
    sched_dl_subfr[2].current_tti = 12;
    sched_cur_dl_subfn            = 3;
    sched_cur_ul_subfn            = 0;

    // Schedule SIB1
    uint32 sib1_ttis[] = {85, 105, 125, 145};
    for(uint32 i=0; i<4; i++)
    {
        liblte_phy_get_tbs_mcs_and_n_prb_for_dl(sys_info.sib_alloc[0].msg[0].N_bits,
                                                sib1_ttis[i] % 10,
                                                interface->get_n_rb_dl(),
                                                sys_info.sib_alloc[0].rnti,
                                                &sys_info.sib_alloc[0].tbs,
                                                &sys_info.sib_alloc[0].mcs,
                                                &sys_info.sib_alloc[0].N_prb);
        sys_info.sib_alloc[0].rv_idx   = (uint32)ceilf(1.5 * ((sib1_ttis[i] / 20) % 4)) % 4; // 36.321 section 5.3.1
        sys_info.sib_alloc[0].dl_alloc = true;
        LTE_FDD_ENB_PERSISTENT_DL_STRUCT *sib_pd = new LTE_FDD_ENB_PERSISTENT_DL_STRUCT;
        memcpy(&sib_pd->alloc, &sys_info.sib_alloc[0], sizeof(LIBLTE_PHY_ALLOCATION_STRUCT));
        sib_pd->next_tti        = sib1_ttis[i];
        sib_pd->tti_periodicity = 80;
        sib_pd->timer_id        = LTE_FDD_ENB_INVALID_TIMER_ID;
        persistent_dl(sib_pd);
    }

    // Schedule all allocated SIBs
    for(uint32 i=1; i<sys_info.sib_alloc.size(); i++)
    {
        if(sys_info.sib_alloc[i].msg[0].N_bits == 0)
            continue;
        uint32 sib_tti = interface->get_si_periodicity() * 10 + i;
        liblte_phy_get_tbs_mcs_and_n_prb_for_dl(sys_info.sib_alloc[i].msg[0].N_bits,
                                                sib_tti % 10,
                                                interface->get_n_rb_dl(),
                                                sys_info.sib_alloc[i].rnti,
                                                &sys_info.sib_alloc[i].tbs,
                                                &sys_info.sib_alloc[i].mcs,
                                                &sys_info.sib_alloc[i].N_prb);
        sys_info.sib_alloc[0].rv_idx   = 0; // 36.321 section 5.3.1
        sys_info.sib_alloc[i].dl_alloc = true;
        LTE_FDD_ENB_PERSISTENT_DL_STRUCT *sib_pd = new LTE_FDD_ENB_PERSISTENT_DL_STRUCT;
        memcpy(&sib_pd->alloc, &sys_info.sib_alloc[i], sizeof(LIBLTE_PHY_ALLOCATION_STRUCT));
        sib_pd->next_tti        = sib_tti;
        sib_pd->tti_periodicity = interface->get_si_periodicity() * 10;
        sib_pd->timer_id        = LTE_FDD_ENB_INVALID_TIMER_ID;
        persistent_dl(sib_pd);
    }
}
void LTE_fdd_enb_mac::stop()
{
    std::lock_guard<std::mutex> lock(start_mutex);

    if(!started)
        return;

    started = false;
    if(NULL != msgq_to_ue)
        delete msgq_to_ue;
}

/***********************/
/*    Communication    */
/***********************/
void LTE_fdd_enb_mac::handle_phy_msg(LTE_FDD_ENB_MESSAGE_STRUCT &msg)
{
    if(LTE_FDD_ENB_DEST_LAYER_MAC != msg.dest_layer &&
       LTE_FDD_ENB_DEST_LAYER_ANY != msg.dest_layer)
        return msgq_to_rlc->send(msg); // Forward message to RLC

    if(msgq_to_ue != NULL && msg.type != LTE_FDD_ENB_MESSAGE_TYPE_READY_TO_SEND)
        return;

    switch(msg.type)
    {
    case LTE_FDD_ENB_MESSAGE_TYPE_READY_TO_SEND:
        handle_ready_to_send(&msg.msg.ready_to_send);
        break;
    case LTE_FDD_ENB_MESSAGE_TYPE_PRACH_DECODE:
        handle_prach_decode(&msg.msg.prach_decode);
        break;
    case LTE_FDD_ENB_MESSAGE_TYPE_PUCCH_DECODE:
        handle_pucch_decode(&msg.msg.pucch_decode);
        break;
    case LTE_FDD_ENB_MESSAGE_TYPE_PUSCH_DECODE:
        handle_pusch_decode(&msg.msg.pusch_decode);
        break;
    default:
        interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_WARNING,
                                  LTE_FDD_ENB_DEBUG_LEVEL_MAC,
                                  __FILE__,
                                  __LINE__,
                                  "Received invalid PHY message %s",
                                  LTE_fdd_enb_message_type_text[msg.type]);
        break;
    }
}
void LTE_fdd_enb_mac::handle_rlc_msg(LTE_FDD_ENB_MESSAGE_STRUCT &msg)
{
    if(LTE_FDD_ENB_DEST_LAYER_MAC != msg.dest_layer &&
       LTE_FDD_ENB_DEST_LAYER_ANY != msg.dest_layer)
        return msgq_to_phy->send(msg); // Forward message to PHY

    if(msg.type == LTE_FDD_ENB_MESSAGE_TYPE_MAC_SDU_READY)
        return handle_sdu_ready(&msg.msg.mac_sdu_ready);

    interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                              LTE_FDD_ENB_DEBUG_LEVEL_MAC,
                              __FILE__,
                              __LINE__,
                              "Received invalid RLC message %s",
                              LTE_fdd_enb_message_type_text[msg.type]);
}
void LTE_fdd_enb_mac::handle_ue_msg(LIBTOOLS_IPC_MSGQ_MESSAGE_STRUCT *msg)
{
    LTE_FDD_ENB_PRACH_DECODE_MSG_STRUCT prach_decode;
    LTE_FDD_ENB_PUSCH_DECODE_MSG_STRUCT pusch_decode;

    interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                              LTE_FDD_ENB_DEBUG_LEVEL_MAC,
                              __FILE__,
                              __LINE__,
                              "Received UE message %s",
                              libtools_ipc_msgq_message_type_text[msg->type]);

    switch(msg->type)
    {
    case LIBTOOLS_IPC_MSGQ_MESSAGE_TYPE_KILL:
        msgq_to_ue = NULL;
        break;
    case LIBTOOLS_IPC_MSGQ_MESSAGE_TYPE_RACH:
        prach_decode.num_preambles = 1;
        prach_decode.current_tti   = sched_ul_subfr[sched_cur_ul_subfn].current_tti;
        prach_decode.timing_adv[0] = 0;
        prach_decode.preamble[0]   = msg->msg.rach.preamble;
        handle_prach_decode(&prach_decode);
        break;
    case LIBTOOLS_IPC_MSGQ_MESSAGE_TYPE_MAC_PDU:
        memcpy(&pusch_decode.msg, &msg->msg.mac_pdu_msg.msg, sizeof(pusch_decode.msg));
        pusch_decode.current_tti = sched_ul_subfr[sched_cur_ul_subfn].current_tti;
        pusch_decode.rnti        = msg->msg.mac_pdu_msg.rnti;
        handle_pusch_decode(&pusch_decode);
        break;
    default:
        interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                  LTE_FDD_ENB_DEBUG_LEVEL_MAC,
                                  __FILE__,
                                  __LINE__,
                                  "Received invalid UE message %s",
                                  libtools_ipc_msgq_message_type_text[msg->type]);
        break;
    }
}
void LTE_fdd_enb_mac::send_rlc_pdu_ready(LTE_fdd_enb_user       *user,
                                         LTE_fdd_enb_rb         *rb,
                                         LIBLTE_BYTE_MSG_STRUCT *pdu)
{
    rb->queue_rlc_pdu(pdu);
    interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                              LTE_FDD_ENB_DEBUG_LEVEL_MAC,
                              __FILE__,
                              __LINE__,
                              pdu,
                              "Sending SDU to RLC for RNTI=%u, RB=%s",
                              user->get_c_rnti(),
                              LTE_fdd_enb_rb_text[rb->get_rb_id()]);

    LTE_FDD_ENB_RLC_PDU_READY_MSG_STRUCT pdu_ready;
    pdu_ready.user = user;
    pdu_ready.rb   = rb;
    msgq_to_rlc->send(LTE_FDD_ENB_MESSAGE_TYPE_RLC_PDU_READY,
                      LTE_FDD_ENB_DEST_LAYER_RLC,
                      (LTE_FDD_ENB_MESSAGE_UNION *)&pdu_ready,
                      sizeof(pdu_ready));
}

/****************************/
/*    External Interface    */
/****************************/
void LTE_fdd_enb_mac::align_ttis_with_phy(uint32 ul_current_tti)
{
    uint32 expected_mac_tti = liblte_phy_add_to_tti(ul_current_tti, 2);
    if(expected_mac_tti == sched_ul_subfr[sched_cur_ul_subfn].current_tti)
        return;

    uint32 N_subfrs_to_skip = liblte_phy_sub_from_tti(expected_mac_tti,
                                                      sched_ul_subfr[sched_cur_ul_subfn].current_tti);
    interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                              LTE_FDD_ENB_DEBUG_LEVEL_MAC,
                              __FILE__,
                              __LINE__,
                              "TTI misalignment PHY(+2)=%u MAC=%u, skipping %u subframes",
                              expected_mac_tti,
                              sched_ul_subfr[sched_cur_ul_subfn].current_tti,
                              N_subfrs_to_skip);
    for(uint32 i=0; i<N_subfrs_to_skip; i++)
        advance_tti_and_clear_subframe();
}
void LTE_fdd_enb_mac::update_sys_info()
{
    std::lock_guard<std::mutex>  lock(sys_info_mutex);
    interface->get_sys_info(sys_info);
}
void LTE_fdd_enb_mac::add_periodic_sr_pucch(uint16 rnti,
                                            uint32 i_sr,
                                            uint32 n_1_p_pucch)
{
    LTE_FDD_ENB_UL_SR_SCHED_QUEUE_STRUCT *sr = NULL;
    sr = new LTE_FDD_ENB_UL_SR_SCHED_QUEUE_STRUCT;
    if(NULL == sr)
        return;

    sr->i_sr        = i_sr;
    sr->n_1_p_pucch = n_1_p_pucch - 1;
    sr->rnti        = rnti;

    ul_sr_sched_queue_mutex.lock();
    ul_sr_sched_queue.push_back(sr);
    ul_sr_sched_queue_mutex.unlock();
}
void LTE_fdd_enb_mac::remove_periodic_sr_pucch(uint16 rnti)
{
    std::lock_guard<std::mutex> lock(ul_sr_sched_queue_mutex);

    for(auto ul_sr=ul_sr_sched_queue.begin(); ul_sr!=ul_sr_sched_queue.end(); ul_sr++)
    {
        if(rnti == (*ul_sr)->rnti)
        {
            LTE_FDD_ENB_UL_SR_SCHED_QUEUE_STRUCT *sr = (*ul_sr);
            ul_sr_sched_queue.erase(ul_sr);
            delete sr;
            return;
        }
    }
}

/**********************/
/*    PHY Handlers    */
/**********************/
void LTE_fdd_enb_mac::handle_ready_to_send(LTE_FDD_ENB_READY_TO_SEND_MSG_STRUCT *rts)
{
    // Send tick to timer manager
    LTE_FDD_ENB_TIMER_TICK_MSG_STRUCT timer_tick;
    msgq_to_timer->send(LTE_FDD_ENB_MESSAGE_TYPE_TIMER_TICK,
                        LTE_FDD_ENB_DEST_LAYER_TIMER_MGR,
                        (LTE_FDD_ENB_MESSAGE_UNION *)&timer_tick,
                        sizeof(LTE_FDD_ENB_TIMER_TICK_MSG_STRUCT));

    msgq_to_phy->send(LTE_FDD_ENB_MESSAGE_TYPE_PHY_SCHEDULE,
                      &sched_dl_subfr[sched_cur_dl_subfn],
                      &sched_ul_subfr[sched_cur_ul_subfn]);

    advance_tti_and_clear_subframe();

    // Call the schedulers
    rar_scheduler();
    dl_scheduler();
    ul_scheduler();
    ul_sr_scheduler();
}
void LTE_fdd_enb_mac::handle_prach_decode(LTE_FDD_ENB_PRACH_DECODE_MSG_STRUCT *prach_decode)
{
    // Construct a random access response for each preamble
    for(uint32 i=0; i<prach_decode->num_preambles; i++)
    {
        interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                                  LTE_FDD_ENB_DEBUG_LEVEL_MAC,
                                  __FILE__,
                                  __LINE__,
                                  "PRACH decode preamble=%u, timing_adv=%u, sfn=%u, subfr=%u",
                                  prach_decode->preamble[i],
                                  prach_decode->timing_adv[i],
                                  prach_decode->current_tti/10,
                                  prach_decode->current_tti%10);
        construct_random_access_response(prach_decode->preamble[i],
                                         prach_decode->timing_adv[i],
                                         prach_decode->current_tti);
    }
}
void LTE_fdd_enb_mac::handle_pucch_decode(LTE_FDD_ENB_PUCCH_DECODE_MSG_STRUCT *pucch_decode)
{
    LTE_fdd_enb_user *user;

    if(LTE_FDD_ENB_ERROR_NONE != user_mgr->find_user(pucch_decode->rnti, &user))
        return interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                         LTE_FDD_ENB_DEBUG_LEVEL_MAC,
                                         __FILE__,
                                         __LINE__,
                                         "Failed to find PUCCH user RNTI=%u TTI=%u",
                                         pucch_decode->rnti,
                                         pucch_decode->current_tti);

    if(LTE_FDD_ENB_PUCCH_TYPE_ACK_NACK == pucch_decode->type)
    {
        handle_pucch_ack_nack(user,
                              pucch_decode->current_tti,
                              &pucch_decode->msg);
    }else{
        handle_pucch_sr(user,
                        pucch_decode->current_tti,
                        &pucch_decode->msg);
    }
}
void LTE_fdd_enb_mac::handle_pucch_ack_nack(LTE_fdd_enb_user      *user,
                                            uint32                 current_tti,
                                            LIBLTE_BIT_MSG_STRUCT *msg)
{
    interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                              LTE_FDD_ENB_DEBUG_LEVEL_MAC,
                              __FILE__,
                              __LINE__,
                              "PUCCH ACK/NACK received for TTI=%u RNTI=%u ACK/NACK=%u",
                              current_tti,
                              user->get_c_rnti(),
                              msg->msg[0]);

    if(msg->msg[0])
    {
        // Received ACK
        user->clear_harq_info(current_tti);
        interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                                  LTE_FDD_ENB_DEBUG_LEVEL_MAC,
                                  __FILE__,
                                  __LINE__,
                                  "Clearing HARQ info RNTI=%u TTI=%u",
                                  user->get_c_rnti(),
                                  current_tti);
        return;
    }

    // Received NACK, resend HARQ information if possible
    LIBLTE_MAC_PDU_STRUCT        mac_pdu;
    LIBLTE_PHY_ALLOCATION_STRUCT alloc;
    if(LTE_FDD_ENB_ERROR_NONE != user->get_harq_info(current_tti,
                                                     &mac_pdu,
                                                     &alloc))
        return interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                         LTE_FDD_ENB_DEBUG_LEVEL_MAC,
                                         __FILE__,
                                         __LINE__,
                                         "Failed to find HARQ info RNTI=%u TTI=%u",
                                         user->get_c_rnti(),
                                         current_tti);
    if(LTE_FDD_ENB_MAX_HARQ_RETX <= alloc.harq_retx_count)
        return interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                                         LTE_FDD_ENB_DEBUG_LEVEL_MAC,
                                         __FILE__,
                                         __LINE__,
                                         "Not resending HARQ due to max retx RNTI=%u TTI=%u",
                                         user->get_c_rnti(),
                                         current_tti);
    alloc.harq_retx_count++;
    alloc.ndi ^= 0x01;
    if(LTE_FDD_ENB_ERROR_NONE == add_to_dl_sched_queue(liblte_phy_add_to_tti(sched_dl_subfr[sched_cur_dl_subfn].current_tti,
                                                                             4),
                                                       &mac_pdu,
                                                       &alloc))
        return interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                                         LTE_FDD_ENB_DEBUG_LEVEL_MAC,
                                         __FILE__,
                                         __LINE__,
                                         "Resending HARQ info RNTI=%u TTI=%u (%u)",
                                         user->get_c_rnti(),
                                         current_tti,
                                         alloc.harq_retx_count);
    interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                              LTE_FDD_ENB_DEBUG_LEVEL_MAC,
                              __FILE__,
                              __LINE__,
                              "Failed to resend HARQ info RNTI=%u TTI=%u",
                              user->get_c_rnti(),
                              current_tti);
}
void LTE_fdd_enb_mac::handle_pucch_sr(LTE_fdd_enb_user      *user,
                                      uint32                 current_tti,
                                      LIBLTE_BIT_MSG_STRUCT *msg)
{
    if(!msg->msg[0])
        return;

    interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                              LTE_FDD_ENB_DEBUG_LEVEL_MAC,
                              __FILE__,
                              __LINE__,
                              "PUCCH SR received for %u RNTI=%u",
                              current_tti,
                              user->get_c_rnti());

    // Schedule a grant big enough to at least hold long BSR
    sched_ul(user, BSR_GRANT_SIZE_BYTES*8);
}
void LTE_fdd_enb_mac::handle_pusch_decode(LTE_FDD_ENB_PUSCH_DECODE_MSG_STRUCT *pusch_decode)
{
    // Find the user
    LTE_fdd_enb_user *user = NULL;
    if(LTE_FDD_ENB_ERROR_NONE != user_mgr->find_user(pusch_decode->rnti, &user))
        return interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                         LTE_FDD_ENB_DEBUG_LEVEL_MAC,
                                         __FILE__,
                                         __LINE__,
                                         &pusch_decode->msg,
                                         "PUSCH decode for invalid RNTI (%u)",
                                         pusch_decode->rnti);

    // Reset the C-RNTI release timer
    user_mgr->reset_c_rnti_timer(pusch_decode->rnti);

    // Reset the inactivity timer
    user->reset_inactivity_timer(LTE_FDD_ENB_USER_INACTIVITY_TIMER_VALUE_MS);

    interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                              LTE_FDD_ENB_DEBUG_LEVEL_MAC,
                              __FILE__,
                              __LINE__,
                              &pusch_decode->msg,
                              "PUSCH decode for RNTI=%u CURRENT_TTI=%u",
                              pusch_decode->rnti,
                              pusch_decode->current_tti);
    interface->send_lte_pcap_msg(LTE_FDD_ENB_PCAP_DIRECTION_UL,
                                 pusch_decode->rnti,
                                 pusch_decode->current_tti,
                                 pusch_decode->msg.msg,
                                 pusch_decode->msg.N_bits);

    // Set the correct channel type
    LIBLTE_MAC_PDU_STRUCT mac_pdu;
    mac_pdu.chan_type = LIBLTE_MAC_CHAN_TYPE_ULSCH;

    // Unpack MAC PDU
    liblte_mac_unpack_mac_pdu(&pusch_decode->msg,
                              false, // Simultaneous PUCCH/PUSCH
                              &mac_pdu);

    for(uint32 i=0; i<mac_pdu.N_subheaders; i++)
    {
        if(LIBLTE_MAC_ULSCH_CCCH_LCID == mac_pdu.subheader[i].lcid){
            handle_ulsch_ccch_sdu(user, mac_pdu.subheader[i].lcid, &mac_pdu.subheader[i].payload.sdu);
        }else if(LIBLTE_MAC_ULSCH_DCCH_LCID_BEGIN <= mac_pdu.subheader[i].lcid &&
                 LIBLTE_MAC_ULSCH_DCCH_LCID_END   >= mac_pdu.subheader[i].lcid){
            handle_ulsch_dcch_sdu(user, mac_pdu.subheader[i].lcid, &mac_pdu.subheader[i].payload.sdu);
        }else if(LIBLTE_MAC_ULSCH_EXT_POWER_HEADROOM_REPORT_LCID == mac_pdu.subheader[i].lcid){
            handle_ulsch_ext_power_headroom_report(user, &mac_pdu.subheader[i].payload.ext_power_headroom);
        }else if(LIBLTE_MAC_ULSCH_POWER_HEADROOM_REPORT_LCID == mac_pdu.subheader[i].lcid){
            handle_ulsch_power_headroom_report(user, &mac_pdu.subheader[i].payload.power_headroom);
        }else if(LIBLTE_MAC_ULSCH_C_RNTI_LCID == mac_pdu.subheader[i].lcid){
            handle_ulsch_c_rnti(&user, &mac_pdu.subheader[i].payload.c_rnti);
        }else if(LIBLTE_MAC_ULSCH_TRUNCATED_BSR_LCID == mac_pdu.subheader[i].lcid){
            handle_ulsch_truncated_bsr(user, &mac_pdu.subheader[i].payload.truncated_bsr);
        }else if(LIBLTE_MAC_ULSCH_SHORT_BSR_LCID == mac_pdu.subheader[i].lcid){
            handle_ulsch_short_bsr(user, &mac_pdu.subheader[i].payload.short_bsr);
        }else if(LIBLTE_MAC_ULSCH_LONG_BSR_LCID == mac_pdu.subheader[i].lcid){
            handle_ulsch_long_bsr(user, &mac_pdu.subheader[i].payload.long_bsr);
        }
    }
}

/******************************/
/*    RLC Message Handlers    */
/******************************/
void LTE_fdd_enb_mac::handle_sdu_ready(LTE_FDD_ENB_MAC_SDU_READY_MSG_STRUCT *sdu_ready)
{
    LIBLTE_BYTE_MSG_STRUCT *sdu;
    if(LTE_FDD_ENB_ERROR_NONE != sdu_ready->rb->get_next_mac_sdu(&sdu))
        return interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                         LTE_FDD_ENB_DEBUG_LEVEL_MAC,
                                         __FILE__,
                                         __LINE__,
                                         "Received sdu_ready message with no SDU queued");

    LTE_fdd_enb_user *user = sdu_ready->user;

    interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                              LTE_FDD_ENB_DEBUG_LEVEL_MAC,
                              __FILE__,
                              __LINE__,
                              sdu,
                              "Received SDU for RNTI=%u and RB=%s",
                              user->get_c_rnti(),
                              LTE_fdd_enb_rb_text[sdu_ready->rb->get_rb_id()]);

    // Fill in the allocation
    LIBLTE_PHY_ALLOCATION_STRUCT alloc = {0};
    alloc.pre_coder_type = LIBLTE_PHY_PRE_CODER_TYPE_TX_DIVERSITY;
    alloc.mod_type       = get_modulation_type(user->get_mcs());
    alloc.chan_type      = LIBLTE_PHY_CHAN_TYPE_DLSCH;
    alloc.rv_idx         = 0;
    alloc.N_codewords    = 1;
    sys_info_mutex.lock();
    if(1 == interface->get_n_ant())
    {
        alloc.tx_mode = 1;
    }else{
        alloc.tx_mode = 2;
    }
    sys_info_mutex.unlock();
    alloc.rnti         = user->get_c_rnti();
    alloc.tpc          = LIBLTE_PHY_TPC_COMMAND_DCI_1_1A_1B_1D_2_3_DB_ZERO;
    alloc.harq_process = user->get_harq_process();
    user->increment_harq_process();
    alloc.ndi             = 0;
    alloc.harq_retx_count = 0;

    // Pack the PDU
    LIBLTE_MAC_PDU_STRUCT mac_pdu;
    mac_pdu.chan_type = LIBLTE_MAC_CHAN_TYPE_DLSCH;
    if(sdu_ready->rb->get_send_con_res_id())
    {
        mac_pdu.N_subheaders                          = 2;
        mac_pdu.subheader[0].lcid                     = LIBLTE_MAC_DLSCH_UE_CONTENTION_RESOLUTION_ID_LCID;
        mac_pdu.subheader[0].payload.ue_con_res_id.id = sdu_ready->rb->get_con_res_id();
        mac_pdu.subheader[1].lcid                     = sdu_ready->rb->get_rb_id();
        memcpy(&mac_pdu.subheader[1].payload.sdu, sdu, sizeof(LIBLTE_BYTE_MSG_STRUCT));
        sdu_ready->rb->set_send_con_res_id(false);
    }else{
        mac_pdu.N_subheaders      = 1;
        mac_pdu.subheader[0].lcid = sdu_ready->rb->get_rb_id();
        memcpy(&mac_pdu.subheader[0].payload.sdu, sdu, sizeof(LIBLTE_BYTE_MSG_STRUCT));
    }

    // Add the PDU to the scheduling queue
    interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                              LTE_FDD_ENB_DEBUG_LEVEL_MAC,
                              __FILE__,
                              __LINE__,
                              "Attempting to schedule PDU for RNTI=%u, requested TTI=%u",
                              alloc.rnti,
                              liblte_phy_add_to_tti(sched_dl_subfr[sched_cur_dl_subfn].current_tti, 4));
    if(LTE_FDD_ENB_ERROR_NONE != add_to_dl_sched_queue(liblte_phy_add_to_tti(sched_dl_subfr[sched_cur_dl_subfn].current_tti,
                                                                             4),
                                                       &mac_pdu,
                                                       &alloc))
    {
        interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                  LTE_FDD_ENB_DEBUG_LEVEL_MAC,
                                  __FILE__,
                                  __LINE__,
                                  "Can't schedule PDU");
    }else{
        interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                                  LTE_FDD_ENB_DEBUG_LEVEL_MAC,
                                  __FILE__,
                                  __LINE__,
                                  &alloc.msg[0],
                                  "PDU scheduled for RNTI=%u, DL_QUEUE_SIZE=%u",
                                  alloc.rnti,
                                  dl_sched_queue.size());
    }

    // Delete the SDU
    sdu_ready->rb->delete_next_mac_sdu();
}

/**************************/
/*    MAC PDU Handlers    */
/**************************/
void LTE_fdd_enb_mac::handle_ulsch_ccch_sdu(LTE_fdd_enb_user       *user,
                                            uint32                  lcid,
                                            LIBLTE_BYTE_MSG_STRUCT *sdu)
{
    if(LIBLTE_MAC_ULSCH_CCCH_LCID != lcid)
        return interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                                         LTE_FDD_ENB_DEBUG_LEVEL_MAC,
                                         __FILE__,
                                         __LINE__,
                                         sdu,
                                         "Not handling ULSCH SDU for RNTI=%u, LCID=%u",
                                         user->get_c_rnti(),
                                         lcid);

    interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                              LTE_FDD_ENB_DEBUG_LEVEL_MAC,
                              __FILE__,
                              __LINE__,
                              sdu,
                              "Handling ULSCH SDU for RNTI=%u, LCID=%u",
                              user->get_c_rnti(),
                              lcid);

    // Get SRB0
    LTE_fdd_enb_rb *rb = NULL;
    user->get_srb0(&rb);
    if(NULL == rb)
        return interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                         LTE_FDD_ENB_DEBUG_LEVEL_MAC,
                                         __FILE__,
                                         __LINE__,
                                         "SRB0 is NULL for RNTI=%u",
                                         user->get_c_rnti());

    // Save the contention resolution ID
    uint64 con_res_id = 0;
    for(uint32 i=0; i<sdu->N_bytes; i++)
    {
        con_res_id <<= 8;
        con_res_id  |= sdu->msg[i];
    }
    rb->set_con_res_id(con_res_id);
    rb->set_send_con_res_id(true);

    // Send the SDU to RLC
    send_rlc_pdu_ready(user, rb, sdu);

    // Update the uplink buffer size
    user->update_ul_buffer_size(sdu->N_bytes);

    // Schedule uplink
    sched_ul(user, user->get_ul_buffer_size()*8);
}
void LTE_fdd_enb_mac::handle_ulsch_dcch_sdu(LTE_fdd_enb_user       *user,
                                            uint32                  lcid,
                                            LIBLTE_BYTE_MSG_STRUCT *sdu)
{
    if(!(LIBLTE_MAC_ULSCH_DCCH_LCID_BEGIN <= lcid &&
         LIBLTE_MAC_ULSCH_DCCH_LCID_END   >= lcid))
        return interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                                         LTE_FDD_ENB_DEBUG_LEVEL_MAC,
                                         __FILE__,
                                         __LINE__,
                                         sdu,
                                         "Not handling ULSCH SDU for RNTI=%u, LCID=%u",
                                         user->get_c_rnti(),
                                         lcid);

    interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                              LTE_FDD_ENB_DEBUG_LEVEL_MAC,
                              __FILE__,
                              __LINE__,
                              sdu,
                              "Handling ULSCH DCCH_SDU for RNTI=%u, LCID=%u",
                              user->get_c_rnti(),
                              lcid);

    // Get RB
    LTE_fdd_enb_rb *rb = NULL;
    if(LTE_FDD_ENB_RB_SRB1 == lcid)
    {
        user->get_srb1(&rb);
    }else if(LTE_FDD_ENB_RB_SRB2 == lcid){
        user->get_srb2(&rb);
    }else if(LTE_FDD_ENB_ERROR_NONE != user->get_drb((LTE_FDD_ENB_RB_ENUM)lcid, &rb)){
        return interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                         LTE_FDD_ENB_DEBUG_LEVEL_MAC,
                                         __FILE__,
                                         __LINE__,
                                         "Not handling ULSCH DCCH_SDU for RNTI=%u, LCID=%u",
                                         user->get_c_rnti(),
                                         lcid);
    }
    if(NULL == rb)
        return interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                         LTE_FDD_ENB_DEBUG_LEVEL_MAC,
                                         __FILE__,
                                         __LINE__,
                                         "RB is NULL for RNTI=%u",
                                         user->get_c_rnti());

    // Send the SDU to RLC
    send_rlc_pdu_ready(user, rb, sdu);

    // Update the uplink buffer size
    user->update_ul_buffer_size(sdu->N_bytes);

    // Schedule uplink
    sched_ul(user, user->get_ul_buffer_size()*8);
}
void LTE_fdd_enb_mac::handle_ulsch_ext_power_headroom_report(LTE_fdd_enb_user                        *user,
                                                             LIBLTE_MAC_EXT_POWER_HEADROOM_CE_STRUCT *ext_power_headroom)
{
    interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                              LTE_FDD_ENB_DEBUG_LEVEL_MAC,
                              __FILE__,
                              __LINE__,
                              "Not handling ULSCH EXTENDED_POWER_HEADROOM_REPORT");
}
void LTE_fdd_enb_mac::handle_ulsch_power_headroom_report(LTE_fdd_enb_user                    *user,
                                                         LIBLTE_MAC_POWER_HEADROOM_CE_STRUCT *power_headroom)
{
    interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                              LTE_FDD_ENB_DEBUG_LEVEL_MAC,
                              __FILE__,
                              __LINE__,
                              "Not handling ULSCH POWER_HEADROOM_REPORT");
}
void LTE_fdd_enb_mac::handle_ulsch_c_rnti(LTE_fdd_enb_user            **user,
                                          LIBLTE_MAC_C_RNTI_CE_STRUCT  *c_rnti)
{
    interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                              LTE_FDD_ENB_DEBUG_LEVEL_MAC,
                              __FILE__,
                              __LINE__,
                              "Received C_RNTI=%u for C_RNTI=%u",
                              c_rnti->c_rnti,
                              (*user)->get_c_rnti());

    if(c_rnti->c_rnti         != (*user)->get_c_rnti() &&
       LTE_FDD_ENB_ERROR_NONE == user_mgr->find_user(c_rnti->c_rnti, user))
        user_mgr->release_c_rnti((*user)->get_c_rnti());
}
void LTE_fdd_enb_mac::handle_ulsch_truncated_bsr(LTE_fdd_enb_user                   *user,
                                                 LIBLTE_MAC_TRUNCATED_BSR_CE_STRUCT *truncated_bsr)
{
    interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                              LTE_FDD_ENB_DEBUG_LEVEL_MAC,
                              __FILE__,
                              __LINE__,
                              "Received truncated BSR for LCG_ID=%u (%u < Buffer Size <= %u), C_RNTI=%u",
                              truncated_bsr->lcg_id,
                              truncated_bsr->min_buffer_size,
                              truncated_bsr->max_buffer_size,
                              user->get_c_rnti());

    user->set_ul_buffer_size(truncated_bsr->max_buffer_size);

    sched_ul(user, truncated_bsr->max_buffer_size*8);
}
void LTE_fdd_enb_mac::handle_ulsch_short_bsr(LTE_fdd_enb_user               *user,
                                             LIBLTE_MAC_SHORT_BSR_CE_STRUCT *short_bsr)
{
    interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                              LTE_FDD_ENB_DEBUG_LEVEL_MAC,
                              __FILE__,
                              __LINE__,
                              "Received short BSR for LCG_ID=%u (%u < Buffer Size <= %u), C_RNTI=%u",
                              short_bsr->lcg_id,
                              short_bsr->min_buffer_size,
                              short_bsr->max_buffer_size,
                              user->get_c_rnti());

    user->set_ul_buffer_size(short_bsr->max_buffer_size);

    sched_ul(user, short_bsr->max_buffer_size*8);
}
void LTE_fdd_enb_mac::handle_ulsch_long_bsr(LTE_fdd_enb_user              *user,
                                            LIBLTE_MAC_LONG_BSR_CE_STRUCT *long_bsr)
{
    interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                              LTE_FDD_ENB_DEBUG_LEVEL_MAC,
                              __FILE__,
                              __LINE__,
                              "Received long BSR (%u < Buffer Size 0 <= %u), (%u < Buffer Size 1 <= %u), (%u < Buffer Size 2 <= %u), (%u < Buffer Size 3 <= %u), C_RNTI=%u",
                              long_bsr->min_buffer_size_0,
                              long_bsr->max_buffer_size_0,
                              long_bsr->min_buffer_size_1,
                              long_bsr->max_buffer_size_1,
                              long_bsr->min_buffer_size_2,
                              long_bsr->max_buffer_size_2,
                              long_bsr->min_buffer_size_3,
                              long_bsr->max_buffer_size_3,
                              user->get_c_rnti());

    user->set_ul_buffer_size(long_bsr->max_buffer_size_0 +
                             long_bsr->max_buffer_size_1 +
                             long_bsr->max_buffer_size_2 +
                             long_bsr->max_buffer_size_3);

    sched_ul(user, (long_bsr->max_buffer_size_0 +
                    long_bsr->max_buffer_size_1 +
                    long_bsr->max_buffer_size_2 +
                    long_bsr->max_buffer_size_3)*8);
}

/***************************/
/*    Data Constructors    */
/***************************/
void LTE_fdd_enb_mac::construct_random_access_response(uint8  preamble,
                                                       uint16 timing_adv,
                                                       uint32 current_tti)
{
    // Allocate a user
    LTE_fdd_enb_user *user = NULL;
    if(LTE_FDD_ENB_ERROR_NONE != user_mgr->add_user(&user, rrc, rlc))
        return interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                         LTE_FDD_ENB_DEBUG_LEVEL_MAC,
                                         __FILE__,
                                         __LINE__,
                                         "No free C-RNTI or add_user fail");

    // Save C-RNTI
    LIBLTE_MAC_RAR_STRUCT rar;
    rar.temp_c_rnti = user->get_c_rnti();

    // Fill in the DL allocation
    LIBLTE_PHY_ALLOCATION_STRUCT dl_alloc;
    dl_alloc.pre_coder_type = LIBLTE_PHY_PRE_CODER_TYPE_TX_DIVERSITY;
    dl_alloc.mod_type       = get_modulation_type(user->get_mcs());
    dl_alloc.chan_type      = LIBLTE_PHY_CHAN_TYPE_DLSCH;
    dl_alloc.rv_idx         = 0;
    dl_alloc.N_codewords    = 1;
    dl_alloc.tx_mode        = 1; // From 36.213 v10.3.0 section 7.1
    dl_alloc.rnti           = 1 + current_tti%10 + 0*10; // FIXME: What is f_id

    // Fill in the UL allocation
    LIBLTE_PHY_ALLOCATION_STRUCT ul_alloc;
    ul_alloc.pre_coder_type = LIBLTE_PHY_PRE_CODER_TYPE_TX_DIVERSITY;
    ul_alloc.mod_type       = get_modulation_type(user->get_mcs());
    ul_alloc.chan_type      = LIBLTE_PHY_CHAN_TYPE_ULSCH;
    ul_alloc.rv_idx         = 0; // From 36.213 v10.3.0 section 8.6.1
    ul_alloc.N_codewords    = 1;
    ul_alloc.N_layers       = 1;
    ul_alloc.tx_mode        = 1; // From 36.213 v10.3.0 section 7.1
    ul_alloc.rnti           = rar.temp_c_rnti;
    sys_info_mutex.lock();
    liblte_phy_get_tbs_mcs_and_n_prb_for_ul(56,
                                            interface->get_n_rb_ul(),
                                            &ul_alloc.tbs,
                                            &ul_alloc.mcs,
                                            &ul_alloc.N_prb);
    sys_info_mutex.unlock();

    // Fill in the RAR
    rar.hdr_type       = LIBLTE_MAC_RAR_HEADER_TYPE_RAPID;
    rar.hopping_flag   = LIBLTE_MAC_RAR_HOPPING_DISABLED;
    rar.tpc_command    = LIBLTE_MAC_RAR_TPC_COMMAND_0dB;
    rar.ul_delay       = LIBLTE_MAC_RAR_UL_DELAY_DISABLED;
    rar.csi_req        = LIBLTE_MAC_RAR_CSI_REQ_DISABLED;
    rar.timing_adv_cmd = timing_adv;
    rar.mcs            = ul_alloc.mcs;
    rar.RAPID          = preamble;

    // Temporarily pack the RAR to determine the number of bits needed
    liblte_mac_pack_random_access_response_pdu(&rar,
                                               &dl_alloc.msg[0]);

    // Add the RAR to the scheduling queue
    if(LTE_FDD_ENB_ERROR_NONE != add_to_rar_sched_queue(current_tti,
                                                        &dl_alloc,
                                                        &ul_alloc,
                                                        &rar))
        return interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                         LTE_FDD_ENB_DEBUG_LEVEL_MAC,
                                         __FILE__,
                                         __LINE__,
                                         "Can't schedule RAR");
    interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                              LTE_FDD_ENB_DEBUG_LEVEL_MAC,
                              __FILE__,
                              __LINE__,
                              "RAR scheduled %u",
                              rar_sched_queue.size());
}

/*******************/
/*    Scheduler    */
/*******************/
void LTE_fdd_enb_mac::sched_ul(LTE_fdd_enb_user *user,
                               uint32            requested_tbs)
{
    if(requested_tbs == 0)
        return;

    LIBLTE_PHY_ALLOCATION_STRUCT alloc;
    alloc.pre_coder_type = LIBLTE_PHY_PRE_CODER_TYPE_TX_DIVERSITY;
    alloc.mod_type       = get_modulation_type(user->get_mcs());
    alloc.chan_type      = LIBLTE_PHY_CHAN_TYPE_ULSCH;
    alloc.rv_idx         = 0;
    alloc.N_codewords    = 1;
    alloc.N_layers       = 1;
    alloc.tx_mode        = 1;
    alloc.rnti           = user->get_c_rnti();
    alloc.tpc            = LIBLTE_PHY_TPC_COMMAND_DCI_0_3_4_DB_NEG_1;
    alloc.ndi            = 0;
    uint32 bits_req      = requested_tbs;
    if(bits_req > (user->get_max_ul_bytes_per_subfn()*8))
        bits_req = user->get_max_ul_bytes_per_subfn()*8;
    sys_info_mutex.lock();
    liblte_phy_get_tbs_and_n_prb_for_ul(bits_req,
                                        interface->get_n_rb_ul(),
                                        user->get_mcs(),
                                        &alloc.tbs,
                                        &alloc.N_prb);
    sys_info_mutex.unlock();

    // Add the allocation to the scheduling queue
    uint32 tti = liblte_phy_add_to_tti(sched_ul_subfr[sched_cur_ul_subfn].current_tti, 10);
    if(LTE_FDD_ENB_ERROR_NONE != add_to_ul_sched_queue(tti, &alloc))
        return interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                         LTE_FDD_ENB_DEBUG_LEVEL_MAC,
                                         __FILE__,
                                         __LINE__,
                                         "Can't schedule UL");
    interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                              LTE_FDD_ENB_DEBUG_LEVEL_MAC,
                              __FILE__,
                              __LINE__,
                              "UL scheduled (mcs=%u, tbs=%u, N_prb=%u) for RNTI=%u, UL_QUEUE_SIZE=%u TTI=%u",
                              alloc.mcs,
                              alloc.tbs,
                              alloc.N_prb,
                              alloc.rnti,
                              ul_sched_queue.size(),
                              tti);
}
void LTE_fdd_enb_mac::persistent_dl(LTE_FDD_ENB_PERSISTENT_DL_STRUCT *sched)
{
    while(!liblte_phy_is_tti_in_future(sched->next_tti,
                                       sched_dl_subfr[sched_cur_dl_subfn].current_tti))
        sched->next_tti = liblte_phy_add_to_tti(sched->next_tti, sched->tti_periodicity);
    add_to_dl_sched_queue(sched->next_tti, NULL, &sched->alloc);
    sched->next_tti = liblte_phy_add_to_tti(sched->next_tti, sched->tti_periodicity);

    if(sched->timer_id == LTE_FDD_ENB_INVALID_TIMER_ID)
    {
        std::lock_guard<std::mutex> lock(persistent_dl_queue_mutex);
        persistent_dl_queue.push_back(sched);
    }

    LTE_fdd_enb_timer_cb timer_expiry_cb(&LTE_fdd_enb_timer_cb_wrapper<LTE_fdd_enb_mac, &LTE_fdd_enb_mac::handle_persistent_dl_timer_expiry>, this);
    timer_mgr->start_timer(sched->tti_periodicity, timer_expiry_cb, &sched->timer_id);
}
void LTE_fdd_enb_mac::handle_persistent_dl_timer_expiry(uint32 timer_id)
{
    std::lock_guard<std::mutex> lock(persistent_dl_queue_mutex);
    for(auto pd : persistent_dl_queue)
        if(pd->timer_id == timer_id)
            return persistent_dl(pd);
}
void LTE_fdd_enb_mac::rar_scheduler()
{
    std::lock_guard<std::mutex> rar_lock(rar_sched_queue_mutex);
    std::lock_guard<std::mutex> si_lock(sys_info_mutex);

    // Schedule RAR for the next subframe
    while(0 != rar_sched_queue.size())
    {
        LTE_FDD_ENB_RAR_SCHED_QUEUE_STRUCT *rar_sched = rar_sched_queue.front();

        // Determine when the response window starts
        uint32 resp_win_start = liblte_phy_add_to_tti(rar_sched->current_tti, 3);

        // Determine when the response window stops
        uint32 resp_win_stop = liblte_phy_add_to_tti(resp_win_start,
                                                     interface->get_ra_response_window_size());

        // Check to see if the response window has passed
        if(liblte_phy_is_tti_in_past(resp_win_stop, sched_dl_subfr[sched_cur_dl_subfn].current_tti))
        {
            // Response window has passed, remove from queue
            interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                                      LTE_FDD_ENB_DEBUG_LEVEL_MAC,
                                      __FILE__,
                                      __LINE__,
                                      "RAR outside of resp win %u %u",
                                      resp_win_stop,
                                      sched_dl_subfr[sched_cur_dl_subfn].current_tti);
            rar_sched_queue.pop_front();
            delete rar_sched;
            continue;
        }

        // Check to see if the current_tti is outside of the response window
        if(liblte_phy_is_tti_in_past(sched_dl_subfr[sched_cur_dl_subfn].current_tti, resp_win_start) ||
           liblte_phy_is_tti_in_future(sched_dl_subfr[sched_cur_dl_subfn].current_tti, resp_win_stop))
            break;

        // Process the RAR, since the current_tti falls within the response window
        LTE_FDD_ENB_DL_SCHEDULE_MSG_STRUCT *dl_subfr = &sched_dl_subfr[sched_cur_dl_subfn];
        LTE_FDD_ENB_UL_SCHEDULE_MSG_STRUCT *ul_subfr = &sched_ul_subfr[(sched_cur_dl_subfn+6)%10];

        // Determine how many PRBs are needed for the DL allocation, if using this subframe
        liblte_phy_get_tbs_mcs_and_n_prb_for_dl(rar_sched->dl_alloc.msg[0].N_bits,
                                                sched_cur_dl_subfn,
                                                interface->get_n_rb_dl(),
                                                rar_sched->dl_alloc.rnti,
                                                &rar_sched->dl_alloc.tbs,
                                                &rar_sched->dl_alloc.mcs,
                                                &rar_sched->dl_alloc.N_prb);

        // Check for scheduling headroom
        if(!scheduling_headroom(dl_subfr, ul_subfr,
                                rar_sched->dl_alloc.N_prb, rar_sched->ul_alloc.N_prb))
            break;

        interface->send_lte_pcap_msg(LTE_FDD_ENB_PCAP_DIRECTION_DL,
                                     rar_sched->dl_alloc.rnti,
                                     dl_subfr->current_tti,
                                     rar_sched->dl_alloc.msg[0].msg,
                                     rar_sched->dl_alloc.msg[0].N_bits);

        // Determine the RB start for the UL allocation
        uint32 rb_start     = ul_subfr->next_prb;
        ul_subfr->next_prb += rar_sched->ul_alloc.N_prb;

        // Fill in the PRBs for the UL allocation
        for(uint32 i=0; i<rar_sched->ul_alloc.N_prb; i++)
        {
            rar_sched->ul_alloc.prb[0][i] = rb_start+i;
            rar_sched->ul_alloc.prb[1][i] = rb_start+i;
        }

        // Determine the RIV for the UL and re-pack the RAR
        uint32 riv = interface->get_n_rb_ul()*(interface->get_n_rb_ul() - rar_sched->ul_alloc.N_prb + 1) + (interface->get_n_rb_ul() - 1 - rb_start);
        if((rar_sched->ul_alloc.N_prb-1) <= (interface->get_n_rb_ul()/2))
            riv = interface->get_n_rb_ul()*(rar_sched->ul_alloc.N_prb - 1) + rb_start;

        // Fill in the RBA for the UL allocation
        uint32 mask = 0;
        for(uint32 i=0; i<(uint32)ceilf(logf(interface->get_n_rb_ul()*(interface->get_n_rb_ul()+1)/2)/logf(2)); i++)
            mask = (mask << 1) | 1;
        rar_sched->rar.rba = riv & mask;

        // Re-pack the RAR
        liblte_mac_pack_random_access_response_pdu(&rar_sched->rar,
                                                   &rar_sched->dl_alloc.msg[0]);

        // Determine the RB start for the DL allocation
        rb_start            = dl_subfr->next_prb;
        dl_subfr->next_prb += rar_sched->dl_alloc.N_prb;

        // Fill in the PRBs for the DL allocation
        for(uint32 i=0; i<rar_sched->dl_alloc.N_prb; i++)
        {
            rar_sched->dl_alloc.prb[0][i] = rb_start+i;
            rar_sched->dl_alloc.prb[1][i] = rb_start+i;
        }

        interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                                  LTE_FDD_ENB_DEBUG_LEVEL_MAC,
                                  __FILE__,
                                  __LINE__,
                                  &rar_sched->dl_alloc.msg[0],
                                  "RAR sent %u %u %u %u",
                                  resp_win_start,
                                  resp_win_stop,
                                  dl_subfr->current_tti,
                                  ul_subfr->current_tti);

        // Schedule DL
        if(NULL == msgq_to_ue)
        {
            memcpy(&dl_subfr->allocations.dl_alloc[dl_subfr->allocations.N_dl_alloc],
                   &rar_sched->dl_alloc,
                   sizeof(LIBLTE_PHY_ALLOCATION_STRUCT));
            dl_subfr->allocations.N_dl_alloc++;
            // Schedule UL decode 6 subframes from now
            memcpy(&ul_subfr->decodes.ul_alloc[ul_subfr->decodes.N_ul_alloc],
                   &rar_sched->ul_alloc,
                   sizeof(LIBLTE_PHY_ALLOCATION_STRUCT));
            ul_subfr->decodes.N_ul_alloc++;
        }else{
            LIBTOOLS_IPC_MSGQ_RAR_PDU_MSG_STRUCT rar_pdu_msg;
            memcpy(&rar_pdu_msg.msg, &rar_sched->dl_alloc.msg, sizeof(rar_pdu_msg.msg));
            rar_pdu_msg.tti = ul_subfr->current_tti;
            msgq_to_ue->send(LIBTOOLS_IPC_MSGQ_MESSAGE_TYPE_RAR_PDU,
                             (LIBTOOLS_IPC_MSGQ_MESSAGE_UNION *)&rar_pdu_msg,
                             sizeof(rar_pdu_msg));
        }

        // Remove RAR from queue
        rar_sched_queue.pop_front();
        delete rar_sched;
    }
}
void LTE_fdd_enb_mac::dl_scheduler()
{
    std::lock_guard<std::mutex> lock(dl_sched_queue_mutex);

    // Schedule DL for the next subframe
    while(0 != dl_sched_queue.size())
    {
        LTE_FDD_ENB_DL_SCHED_QUEUE_STRUCT *dl_sched = dl_sched_queue.front();

        // Check if the scheduled TTI is in the past
        if(liblte_phy_is_tti_in_past(dl_sched->current_tti,
                                     sched_dl_subfr[sched_cur_dl_subfn].current_tti))
        {
            // Remove DL schedule from queue
            interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                                      LTE_FDD_ENB_DEBUG_LEVEL_MAC,
                                      __FILE__,
                                      __LINE__,
                                      "DL in the past %u %u",
                                      dl_sched->current_tti,
                                      sched_dl_subfr[sched_cur_dl_subfn].current_tti);
            dl_sched_queue.pop_front();
            delete dl_sched;
            continue;
        }

        // Check to see if the scheduled TTI matches the current TTI
        if(dl_sched->current_tti != sched_dl_subfr[sched_cur_dl_subfn].current_tti)
            break;

        LTE_FDD_ENB_DL_SCHEDULE_MSG_STRUCT *dl_subfr = &sched_dl_subfr[sched_cur_dl_subfn];
        if(dl_sched->alloc.rnti != LIBLTE_MAC_SI_RNTI)
        {
            // Pack the message and determine TBS
            liblte_mac_pack_mac_pdu(&dl_sched->mac_pdu,
                                    &dl_sched->alloc.msg[0]);
            liblte_phy_get_tbs_and_n_prb_for_dl(dl_sched->alloc.msg[0].N_bits,
                                                dl_subfr->N_avail_prbs - dl_subfr->N_sched_prbs,
                                                dl_sched->alloc.mcs,
                                                &dl_sched->alloc.tbs,
                                                &dl_sched->alloc.N_prb);

            // Pad and repack if needed
            if(dl_sched->alloc.tbs > dl_sched->alloc.msg[0].N_bits)
            {
                uint32 N_pad = (dl_sched->alloc.tbs - dl_sched->alloc.msg[0].N_bits)/8;

                if(1 == N_pad)
                {
                    for(uint32 i=0; i<dl_sched->mac_pdu.N_subheaders; i++)
                        memcpy(&dl_sched->mac_pdu.subheader[dl_sched->mac_pdu.N_subheaders-i],
                               &dl_sched->mac_pdu.subheader[dl_sched->mac_pdu.N_subheaders-i-1],
                               sizeof(LIBLTE_MAC_PDU_SUBHEADER_STRUCT));
                    dl_sched->mac_pdu.subheader[0].lcid = LIBLTE_MAC_DLSCH_PADDING_LCID;
                    dl_sched->mac_pdu.N_subheaders++;
                }else if(2 == N_pad){
                    for(uint32 i=0; i<dl_sched->mac_pdu.N_subheaders; i++)
                        memcpy(&dl_sched->mac_pdu.subheader[dl_sched->mac_pdu.N_subheaders-i+1],
                               &dl_sched->mac_pdu.subheader[dl_sched->mac_pdu.N_subheaders-i-1],
                               sizeof(LIBLTE_MAC_PDU_SUBHEADER_STRUCT));
                    dl_sched->mac_pdu.subheader[0].lcid  = LIBLTE_MAC_DLSCH_PADDING_LCID;
                    dl_sched->mac_pdu.subheader[1].lcid  = LIBLTE_MAC_DLSCH_PADDING_LCID;
                    dl_sched->mac_pdu.N_subheaders      += 2;
                }else{
                    dl_sched->mac_pdu.subheader[dl_sched->mac_pdu.N_subheaders].lcid = LIBLTE_MAC_DLSCH_PADDING_LCID;
                    dl_sched->mac_pdu.N_subheaders++;
                }

                liblte_mac_pack_mac_pdu(&dl_sched->mac_pdu,
                                        &dl_sched->alloc.msg[0]);
            }
        }

        // Check for scheduling headroom
        if(!scheduling_headroom(dl_subfr, NULL, dl_sched->alloc.N_prb, 0))
            break;

        // Determine the RB start for the allocation
        uint32 rb_start     = dl_subfr->next_prb;
        dl_subfr->next_prb += dl_sched->alloc.N_prb;

        // Fill in the PRBs for the allocation
        for(uint32 i=0; i<dl_sched->alloc.N_prb; i++)
        {
            dl_sched->alloc.prb[0][i] = rb_start+i;
            dl_sched->alloc.prb[1][i] = rb_start+i;
        }

        // Send a PCAP message
        interface->send_lte_pcap_msg(LTE_FDD_ENB_PCAP_DIRECTION_DL,
                                     dl_sched->alloc.rnti,
                                     dl_subfr->current_tti,
                                     dl_sched->alloc.msg[0].msg,
                                     dl_sched->alloc.tbs);

        interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                                  LTE_FDD_ENB_DEBUG_LEVEL_MAC,
                                  __FILE__,
                                  __LINE__,
                                  &dl_sched->alloc.msg[0],
                                  "DL allocation (mcs=%u, tbs=%u, N_prb=%u) sent for RNTI=%u CURRENT_TTI=%u",
                                  dl_sched->alloc.mcs,
                                  dl_sched->alloc.tbs,
                                  dl_sched->alloc.N_prb,
                                  dl_sched->alloc.rnti,
                                  dl_subfr->current_tti);

        // Schedule DL
        if(NULL == msgq_to_ue)
        {
            memcpy(&dl_subfr->allocations.dl_alloc[dl_subfr->allocations.N_dl_alloc],
                   &dl_sched->alloc,
                   sizeof(LIBLTE_PHY_ALLOCATION_STRUCT));
            dl_subfr->allocations.N_dl_alloc++;

            if(dl_sched->alloc.rnti != LIBLTE_MAC_SI_RNTI)
            {
                // Schedule ACK/NACK PUCCH 4 subframes from now and store the DL allocation for potential H-ARQ retransmission
                std::lock_guard<std::mutex>         si_lock(sys_info_mutex);
                LTE_FDD_ENB_UL_SCHEDULE_MSG_STRUCT *ul_subfr   = &sched_ul_subfr[(sched_cur_dl_subfn+4)%10];
                ul_subfr->pucch[ul_subfr->N_pucch].type        = LTE_FDD_ENB_PUCCH_TYPE_ACK_NACK;
                ul_subfr->pucch[ul_subfr->N_pucch].rnti        = dl_sched->alloc.rnti;
                ul_subfr->pucch[ul_subfr->N_pucch].n_1_p_pucch = sys_info.sib2.radioResourceConfigCommon_Get().pucch_ConfigCommon_Get().n1PUCCH_AN_Value();
                ul_subfr->pucch[ul_subfr->N_pucch].decode      = true;
                ul_subfr->N_pucch++;
                LTE_fdd_enb_user *user;
                if(LTE_FDD_ENB_ERROR_NONE == user_mgr->find_user(dl_sched->alloc.rnti, &user))
                    user->store_harq_info(ul_subfr->current_tti, &dl_sched->mac_pdu, &dl_sched->alloc);
            }
        }else{
            LIBTOOLS_IPC_MSGQ_MAC_PDU_MSG_STRUCT mac_pdu_msg;
            memcpy(&mac_pdu_msg.msg, &dl_sched->alloc.msg[0], sizeof(mac_pdu_msg.msg));
            mac_pdu_msg.rnti = dl_sched->alloc.rnti;
            msgq_to_ue->send(LIBTOOLS_IPC_MSGQ_MESSAGE_TYPE_MAC_PDU,
                             (LIBTOOLS_IPC_MSGQ_MESSAGE_UNION *)&mac_pdu_msg,
                             sizeof(mac_pdu_msg));
        }

        // Remove DL schedule from queue
        dl_sched_queue.pop_front();
        delete dl_sched;
    }
}
void LTE_fdd_enb_mac::ul_scheduler()
{
    std::lock_guard<std::mutex> lock(ul_sched_queue_mutex);

    // Schedule UL for the next subframe
    while(0 != ul_sched_queue.size())
    {
        LTE_FDD_ENB_UL_SCHED_QUEUE_STRUCT  *ul_sched = ul_sched_queue.front();
        LTE_FDD_ENB_DL_SCHEDULE_MSG_STRUCT *dl_subfr = &sched_dl_subfr[sched_cur_dl_subfn];
        LTE_FDD_ENB_UL_SCHEDULE_MSG_STRUCT *ul_subfr = &sched_ul_subfr[(sched_cur_dl_subfn+4)%10];

        // Check if the scheduled TTI is in the past
        if(liblte_phy_is_tti_in_past(ul_sched->current_tti, ul_subfr->current_tti))
        {
            // Remove UL schedule from queue
            interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                                      LTE_FDD_ENB_DEBUG_LEVEL_MAC,
                                      __FILE__,
                                      __LINE__,
                                      "UL in the past %u %u",
                                      ul_sched->current_tti,
                                      ul_subfr->current_tti);
            ul_sched_queue.pop_front();
            delete ul_sched;
            continue;
        }

        // Check for scheduling headroom
        if(!scheduling_headroom(dl_subfr, ul_subfr, 0, ul_sched->alloc.N_prb))
            break;

        // Determine the RB start
        uint32 rb_start     = ul_subfr->next_prb;
        ul_subfr->next_prb += ul_sched->alloc.N_prb;

        // Fill in the PRBs
        for(uint32 i=0; i<ul_sched->alloc.N_prb; i++)
        {
            ul_sched->alloc.prb[0][i] = rb_start+i;
            ul_sched->alloc.prb[1][i] = rb_start+i;
        }

        interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                                  LTE_FDD_ENB_DEBUG_LEVEL_MAC,
                                  __FILE__,
                                  __LINE__,
                                  "UL allocation sent for RNTI=%u CURRENT_TTI=%u",
                                  ul_sched->alloc.rnti,
                                  ul_subfr->current_tti);

        // Schedule UL decode 4 subframes from now
        if(NULL == msgq_to_ue)
        {
            memcpy(&ul_subfr->decodes.ul_alloc[ul_subfr->decodes.N_ul_alloc],
                   &ul_sched->alloc,
                   sizeof(LIBLTE_PHY_ALLOCATION_STRUCT));
            ul_subfr->decodes.N_ul_alloc++;
            // Schedule UL allocation
            memcpy(&dl_subfr->allocations.ul_alloc[dl_subfr->allocations.N_ul_alloc],
                   &ul_sched->alloc,
                   sizeof(LIBLTE_PHY_ALLOCATION_STRUCT));
            dl_subfr->allocations.N_ul_alloc++;
        }else{
            LIBTOOLS_IPC_MSGQ_UL_ALLOC_MSG_STRUCT ul_alloc_msg;
            ul_alloc_msg.size = ul_sched->alloc.tbs;
            ul_alloc_msg.tti  = ul_subfr->current_tti;
            ul_alloc_msg.rnti = ul_sched->alloc.rnti;
            msgq_to_ue->send(LIBTOOLS_IPC_MSGQ_MESSAGE_TYPE_UL_ALLOC,
                             (LIBTOOLS_IPC_MSGQ_MESSAGE_UNION *)&ul_alloc_msg,
                             sizeof(ul_alloc_msg));
        }

        // Remove UL schedule from queue
        ul_sched_queue.pop_front();
        delete ul_sched;
    }
}
void LTE_fdd_enb_mac::ul_sr_scheduler()
{
    std::lock_guard<std::mutex> lock(ul_sr_sched_queue_mutex);

    // Schedule UL SR for the next subframe
    LTE_FDD_ENB_UL_SCHEDULE_MSG_STRUCT *ul_subfr = &sched_ul_subfr[sched_cur_ul_subfn];
    for(auto ul_sr : ul_sr_sched_queue)
    {
        uint32 sr_periodicity;
        uint32 N_offset_sr;
        liblte_phy_pucch_map_sr_config_idx(ul_sr->i_sr, &sr_periodicity, &N_offset_sr);
        if((liblte_phy_sub_from_tti(ul_subfr->current_tti, N_offset_sr) % sr_periodicity) == 0)
        {
            ul_subfr->pucch[ul_subfr->N_pucch].type        = LTE_FDD_ENB_PUCCH_TYPE_SR;
            ul_subfr->pucch[ul_subfr->N_pucch].rnti        = ul_sr->rnti;
            ul_subfr->pucch[ul_subfr->N_pucch].n_1_p_pucch = ul_sr->n_1_p_pucch;
            ul_subfr->pucch[ul_subfr->N_pucch].decode      = true;
            ul_subfr->N_pucch++;
        }
    }
}
LTE_FDD_ENB_ERROR_ENUM LTE_fdd_enb_mac::add_to_rar_sched_queue(uint32                        current_tti,
                                                               LIBLTE_PHY_ALLOCATION_STRUCT *dl_alloc,
                                                               LIBLTE_PHY_ALLOCATION_STRUCT *ul_alloc,
                                                               LIBLTE_MAC_RAR_STRUCT        *rar)
{
    LTE_FDD_ENB_RAR_SCHED_QUEUE_STRUCT *rar_sched = NULL;
    rar_sched = new LTE_FDD_ENB_RAR_SCHED_QUEUE_STRUCT;
    if(NULL == rar_sched)
        return LTE_FDD_ENB_ERROR_CANT_SCHEDULE;

    rar_sched->current_tti = current_tti;
    memcpy(&rar_sched->dl_alloc, dl_alloc, sizeof(LIBLTE_PHY_ALLOCATION_STRUCT));
    memcpy(&rar_sched->ul_alloc, ul_alloc, sizeof(LIBLTE_PHY_ALLOCATION_STRUCT));
    memcpy(&rar_sched->rar, rar, sizeof(LIBLTE_MAC_RAR_STRUCT));

    std::lock_guard<std::mutex> lock(rar_sched_queue_mutex);
    rar_sched_queue.push_back(rar_sched);

    return LTE_FDD_ENB_ERROR_NONE;
}
LTE_FDD_ENB_ERROR_ENUM LTE_fdd_enb_mac::add_to_dl_sched_queue(uint32                        current_tti,
                                                              LIBLTE_MAC_PDU_STRUCT        *mac_pdu,
                                                              LIBLTE_PHY_ALLOCATION_STRUCT *alloc)
{
    LTE_FDD_ENB_DL_SCHED_QUEUE_STRUCT *dl_sched = NULL;
    dl_sched = new LTE_FDD_ENB_DL_SCHED_QUEUE_STRUCT;
    if(NULL == dl_sched)
        return LTE_FDD_ENB_ERROR_CANT_SCHEDULE;

    dl_sched->current_tti = current_tti;
    if(mac_pdu != NULL)
        memcpy(&dl_sched->mac_pdu, mac_pdu, sizeof(LIBLTE_MAC_PDU_STRUCT));
    memcpy(&dl_sched->alloc, alloc, sizeof(LIBLTE_PHY_ALLOCATION_STRUCT));

    std::lock_guard<std::mutex> lock(dl_sched_queue_mutex);
    for(auto scheduled_item : dl_sched_queue)
        if(scheduled_item->alloc.rnti  == dl_sched->alloc.rnti &&
           scheduled_item->current_tti == dl_sched->current_tti)
            dl_sched->current_tti = liblte_phy_add_to_tti(dl_sched->current_tti, 1);
    for(auto iter=dl_sched_queue.begin(); iter!=dl_sched_queue.end(); iter++)
    {
        if(liblte_phy_is_tti_in_future((*iter)->current_tti, dl_sched->current_tti))
        {
            dl_sched_queue.insert(iter, dl_sched);
            return LTE_FDD_ENB_ERROR_NONE;
        }
    }
    dl_sched_queue.push_back(dl_sched);

    return LTE_FDD_ENB_ERROR_NONE;
}
LTE_FDD_ENB_ERROR_ENUM LTE_fdd_enb_mac::add_to_ul_sched_queue(uint32                        current_tti,
                                                              LIBLTE_PHY_ALLOCATION_STRUCT *alloc)
{
    LTE_FDD_ENB_UL_SCHED_QUEUE_STRUCT *ul_sched = NULL;
    ul_sched = new LTE_FDD_ENB_UL_SCHED_QUEUE_STRUCT;
    if(NULL == ul_sched)
        return LTE_FDD_ENB_ERROR_CANT_SCHEDULE;

    ul_sched->current_tti = current_tti;
    memcpy(&ul_sched->alloc, alloc, sizeof(LIBLTE_PHY_ALLOCATION_STRUCT));

    std::lock_guard<std::mutex> lock(ul_sched_queue_mutex);
    bool sched = true;
    for(auto ul_sq : ul_sched_queue)
        if(ul_sq->alloc.rnti == alloc->rnti && ul_sq->current_tti == ul_sched->current_tti)
            sched = false;
    if(!sched)
        return LTE_FDD_ENB_ERROR_CANT_SCHEDULE;

    ul_sched_queue.push_back(ul_sched);
    return LTE_FDD_ENB_ERROR_NONE;
}

/*****************/
/*    Helpers    */
/*****************/
void LTE_fdd_enb_mac::advance_tti_and_clear_subframe()
{
    // Advance the TTI
    sched_dl_subfr[sched_cur_dl_subfn].current_tti = liblte_phy_add_to_tti(sched_dl_subfr[sched_cur_dl_subfn].current_tti, 10);
    sched_ul_subfr[sched_cur_ul_subfn].current_tti = liblte_phy_add_to_tti(sched_ul_subfr[sched_cur_ul_subfn].current_tti, 10);

    // Clear the subframe
    sched_dl_subfr[sched_cur_dl_subfn].allocations.N_dl_alloc = 0;
    sched_dl_subfr[sched_cur_dl_subfn].allocations.N_ul_alloc = 0;
    sched_dl_subfr[sched_cur_dl_subfn].N_avail_prbs           = interface->get_n_rb_dl() - get_n_reserved_prbs(sched_dl_subfr[sched_cur_dl_subfn].current_tti);
    sched_dl_subfr[sched_cur_dl_subfn].N_sched_prbs           = 0;
    sched_dl_subfr[sched_cur_dl_subfn].next_prb               = 0;
    sched_ul_subfr[sched_cur_ul_subfn].decodes.N_ul_alloc     = 0;
    sched_ul_subfr[sched_cur_ul_subfn].N_sched_prbs           = 0;
    sched_ul_subfr[sched_cur_ul_subfn].N_pucch                = 0;
    sched_ul_subfr[sched_cur_ul_subfn].next_prb               = 0;

    // Advance the subframe numbers
    sched_cur_dl_subfn = (sched_cur_dl_subfn + 1) % 10;
    sched_cur_ul_subfn = (sched_cur_ul_subfn + 1) % 10;
}
uint32 LTE_fdd_enb_mac::get_n_reserved_prbs(uint32 current_tti)
{
    // Reserve PRBs for the MIB
    uint32 N_reserved_prbs = 0;
    if(0 == (current_tti % 10))
        N_reserved_prbs += 6;

    // Reserve PRBs for SIB1
    if(5 == (current_tti % 10) &&
       0 == ((current_tti / 10) % 2))
        N_reserved_prbs += sys_info.sib_alloc[0].N_prb;

    // Reserve PRBs for all other SIBs
    for(uint32 i=0; i<sys_info.sib_alloc.size(); i++)
        if(0                                           != sys_info.sib_alloc[i].msg[0].N_bits &&
           (i * interface->get_si_window_length())%10  == (current_tti % 10)                  &&
           ((i * interface->get_si_window_length())/10 == ((current_tti / 10) % interface->get_si_periodicity())))
            N_reserved_prbs += sys_info.sib_alloc[i].N_prb;

    return N_reserved_prbs;
}
bool LTE_fdd_enb_mac::scheduling_headroom(LTE_FDD_ENB_DL_SCHEDULE_MSG_STRUCT *dl_subfr,
                                          LTE_FDD_ENB_UL_SCHEDULE_MSG_STRUCT *ul_subfr,
                                          uint32                              N_dl_prbs,
                                          uint32                              N_ul_prbs)
{
    uint32 N_cce = phy->get_n_cce();
    int32  N_avail_dcis = N_cce - (dl_subfr->allocations.N_dl_alloc +
                                   dl_subfr->allocations.N_ul_alloc);

    if(N_avail_dcis == 0)
        return false;

    int32 N_avail_dl_prbs = dl_subfr->N_avail_prbs - dl_subfr->N_sched_prbs;
    if(N_avail_dl_prbs < (int32)N_dl_prbs)
        return false;

    if(ul_subfr == NULL)
        return true;

    int32 N_avail_ul_prbs = ul_subfr->N_avail_prbs - ul_subfr->N_sched_prbs;
    if(N_avail_ul_prbs < (int32)N_ul_prbs)
        return false;

    return true;
}
LIBLTE_PHY_MODULATION_TYPE_ENUM LTE_fdd_enb_mac::get_modulation_type(uint8 mcs)
{
    if(mcs < 10 || mcs == 29)
        return LIBLTE_PHY_MODULATION_TYPE_QPSK;
    if(mcs < 17 || mcs == 30)
        return LIBLTE_PHY_MODULATION_TYPE_16QAM;
    return LIBLTE_PHY_MODULATION_TYPE_64QAM;
}
