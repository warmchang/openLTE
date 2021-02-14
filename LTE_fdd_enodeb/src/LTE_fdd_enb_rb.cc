#line 2 "LTE_fdd_enb_rb.cc" // Make __FILE__ omit the path
/*******************************************************************************

    Copyright 2014-2017, 2021 Ben Wojtowicz

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

    File: LTE_fdd_enb_rb.cc

    Description: Contains all the implementations for the LTE FDD eNodeB
                 radio bearer class.

    Revision History
    ----------    -------------    --------------------------------------------
    05/04/2014    Ben Wojtowicz    Created file
    06/15/2014    Ben Wojtowicz    Added more states and procedures, QoS, MME,
                                   RLC, and uplink scheduling functionality.
    08/03/2014    Ben Wojtowicz    Added MME procedures/states, RRC NAS support,
                                   RRC transaction id, PDCP sequence numbers,
                                   and RLC transmit variables.
    09/03/2014    Ben Wojtowicz    Added ability to store the contetion
                                   resolution identity and fixed an issue with
                                   t_poll_retransmit.
    11/01/2014    Ben Wojtowicz    Added SRB2 support and PDCP security.
    11/29/2014    Ben Wojtowicz    Added more DRB support, moved almost
                                   everything to byte messages structs, added
                                   IP gateway and RLC UMD support.
    12/16/2014    Ben Wojtowicz    Added QoS for default data services.
    12/24/2014    Ben Wojtowicz    Added asymmetric QoS support and fixed a
                                   UMD reassembly bug.
    02/15/2015    Ben Wojtowicz    Split UL/DL QoS TTI frequency, added reset
                                   user support, and added multiple UMD RLC data
                                   support.
    07/25/2015    Ben Wojtowicz    Moved QoS structure to the user class, fixed
                                   RLC AM TX and RX buffers, and moved DRBs to
                                   RLC AM.
    12/06/2015    Ben Wojtowicz    Changed boost::mutex to pthread_mutex_t and
                                   sem_t and fixed the updating of VT(A) in the
                                   retransmission buffer.
    12/18/2016    Ben Wojtowicz    Properly handling multiple RLC AMD PDUs.
    07/29/2017    Ben Wojtowicz    Remove last TTI storage and refactored AMD
                                   reception buffer handling to support more
                                   than one PDU with the same SN.
    02/14/2021    Ben Wojtowicz    Massive reformat.

*******************************************************************************/

/*******************************************************************************
                              INCLUDES
*******************************************************************************/

#include "LTE_fdd_enb_rb.h"
#include "LTE_fdd_enb_timer_mgr.h"
#include "LTE_fdd_enb_user.h"
#include "LTE_fdd_enb_rlc.h"
#include "LTE_fdd_enb_mac.h"
#include "libtools_helpers.h"

/*******************************************************************************
                              DEFINES
*******************************************************************************/


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
LTE_fdd_enb_rb::LTE_fdd_enb_rb(LTE_FDD_ENB_RB_ENUM    _rb,
                               LTE_fdd_enb_interface *iface,
                               LTE_fdd_enb_timer_mgr *tm,
                               LTE_fdd_enb_user      *_user,
                               LTE_fdd_enb_rlc       *_rlc) :
    rb{_rb}, interface{iface}, timer_mgr{tm}, user{_user}, rlc{_rlc}, rrc_transaction_id{0},
    pdcp_rx_count{0}, pdcp_tx_count{0},
    t_poll_retransmit_timer_id{LTE_FDD_ENB_INVALID_TIMER_ID}, rlc_vrr{0},
    rlc_vrmr{LIBLTE_RLC_AM_WINDOW_SIZE}, rlc_vrh{0}, rlc_vta{0},
    rlc_vtms{LIBLTE_RLC_AM_WINDOW_SIZE}, rlc_vts{0}, rlc_vruh{0}, rlc_vrur{0},
    rlc_um_window_size{512}, rlc_first_um_segment_sn{0xFFFF}, rlc_last_um_segment_sn{0xFFFF},
    rlc_vtus{0}, mac_con_res_id{0}
{
    if(LTE_FDD_ENB_RB_SRB0 == rb)
    {
        mme_procedure = LTE_FDD_ENB_MME_PROC_IDLE;
        mme_state     = LTE_FDD_ENB_MME_STATE_IDLE;
        rrc_procedure = LTE_FDD_ENB_RRC_PROC_IDLE;
        rrc_state     = LTE_FDD_ENB_RRC_STATE_IDLE;
        pdcp_config   = LTE_FDD_ENB_PDCP_CONFIG_N_A;
        rlc_config    = LTE_FDD_ENB_RLC_CONFIG_TM;
        mac_config    = LTE_FDD_ENB_MAC_CONFIG_TM;
    }else if(LTE_FDD_ENB_RB_SRB1 == rb){
        mme_procedure = LTE_FDD_ENB_MME_PROC_IDLE;
        mme_state     = LTE_FDD_ENB_MME_STATE_IDLE;
        rrc_procedure = LTE_FDD_ENB_RRC_PROC_IDLE;
        rrc_state     = LTE_FDD_ENB_RRC_STATE_IDLE;
        pdcp_config   = LTE_FDD_ENB_PDCP_CONFIG_N_A;
        rlc_config    = LTE_FDD_ENB_RLC_CONFIG_AM;
        mac_config    = LTE_FDD_ENB_MAC_CONFIG_TM;
    }else if(LTE_FDD_ENB_RB_SRB2 == rb){
        mme_procedure = LTE_FDD_ENB_MME_PROC_IDLE;
        mme_state     = LTE_FDD_ENB_MME_STATE_IDLE;
        rrc_procedure = LTE_FDD_ENB_RRC_PROC_IDLE;
        rrc_state     = LTE_FDD_ENB_RRC_STATE_IDLE;
        pdcp_config   = LTE_FDD_ENB_PDCP_CONFIG_N_A;
        rlc_config    = LTE_FDD_ENB_RLC_CONFIG_AM;
        mac_config    = LTE_FDD_ENB_MAC_CONFIG_TM;
    }else if(LTE_FDD_ENB_RB_DRB1 == rb){
        pdcp_config = LTE_FDD_ENB_PDCP_CONFIG_LONG_SN;
        rlc_config  = LTE_FDD_ENB_RLC_CONFIG_AM;
        mac_config  = LTE_FDD_ENB_MAC_CONFIG_TM;
    }else if(LTE_FDD_ENB_RB_DRB2 == rb){
        pdcp_config = LTE_FDD_ENB_PDCP_CONFIG_LONG_SN;
        rlc_config  = LTE_FDD_ENB_RLC_CONFIG_AM;
        mac_config  = LTE_FDD_ENB_MAC_CONFIG_TM;
    }

    // RLC
    rlc_am_rx_buffer.clear();
    rlc_am_tx_buffer.clear();
    rlc_um_rx_buffer.clear();
}
LTE_fdd_enb_rb::~LTE_fdd_enb_rb()
{
    // MAC
    mac_sdu_queue_mutex.lock();
    for(auto it=mac_sdu_queue.begin(); it!=mac_sdu_queue.end(); it++)
        delete (*it);

    // RLC
    rlc_pdu_queue_mutex.lock();
    for(auto it=rlc_pdu_queue.begin(); it!=rlc_pdu_queue.end(); it++)
        delete (*it);
    rlc_sdu_queue_mutex.lock();
    for(auto it=rlc_sdu_queue.begin(); it!=rlc_sdu_queue.end(); it++)
        delete (*it);
    for(auto rlc_am_rx : rlc_am_rx_buffer)
        delete rlc_am_rx.second;
    for(auto rlc_am_tx : rlc_am_tx_buffer)
        delete rlc_am_tx.second;
    for(auto rlc_um_rx : rlc_um_rx_buffer)
        delete rlc_um_rx.second;
    if(LTE_FDD_ENB_INVALID_TIMER_ID != t_poll_retransmit_timer_id)
        timer_mgr->stop_timer(t_poll_retransmit_timer_id);

    // PDCP
    pdcp_pdu_queue_mutex.lock();
    for(auto it=pdcp_pdu_queue.begin(); it!=pdcp_pdu_queue.end(); it++)
        delete (*it);
    pdcp_sdu_queue_mutex.lock();
    for(auto it=pdcp_sdu_queue.begin(); it!=pdcp_sdu_queue.end(); it++)
        delete (*it);
    pdcp_data_sdu_queue_mutex.lock();
    for(auto it=pdcp_data_sdu_queue.begin(); it!=pdcp_data_sdu_queue.end(); it++)
        delete (*it);

    // RRC
    rrc_pdu_queue_mutex.lock();
    for(auto it=rrc_pdu_queue.begin(); it!=rrc_pdu_queue.end(); it++)
        delete (*it);
    rrc_nas_msg_queue_mutex.lock();
    for(auto it=rrc_nas_msg_queue.begin(); it!=rrc_nas_msg_queue.end(); it++)
        delete (*it);

    // MME
    mme_nas_msg_queue_mutex.lock();
    for(auto it=mme_nas_msg_queue.begin(); it!=mme_nas_msg_queue.end(); it++)
        delete (*it);

    // GW
    gw_data_msg_queue_mutex.lock();
    for(auto it=gw_data_msg_queue.begin(); it!=gw_data_msg_queue.end(); it++)
        delete (*it);
}

/******************/
/*    Identity    */
/******************/
LTE_FDD_ENB_RB_ENUM LTE_fdd_enb_rb::get_rb_id()
{
    return rb;
}
void LTE_fdd_enb_rb::reset_user(LTE_fdd_enb_user *_user)
{
    user = _user;
}

/************/
/*    GW    */
/************/
void LTE_fdd_enb_rb::queue_gw_data_msg(LIBLTE_BYTE_MSG_STRUCT *gw_data)
{
    queue_msg(gw_data, gw_data_msg_queue_mutex, &gw_data_msg_queue);
}
LTE_FDD_ENB_ERROR_ENUM LTE_fdd_enb_rb::get_next_gw_data_msg(LIBLTE_BYTE_MSG_STRUCT **gw_data)
{
    return get_next_msg(gw_data_msg_queue_mutex, &gw_data_msg_queue, gw_data);
}
LTE_FDD_ENB_ERROR_ENUM LTE_fdd_enb_rb::delete_next_gw_data_msg()
{
    return delete_next_msg(gw_data_msg_queue_mutex, &gw_data_msg_queue);
}

/*************/
/*    MME    */
/*************/
void LTE_fdd_enb_rb::queue_mme_nas_msg(const std::vector<uint8_t> &nas_msg)
{
    LIBLTE_BYTE_MSG_STRUCT actual_msg;
    actual_msg.N_bytes = nas_msg.size();
    for(uint32 i=0; i<nas_msg.size(); i++)
        actual_msg.msg[i] = nas_msg[i];
    queue_msg(&actual_msg, mme_nas_msg_queue_mutex, &mme_nas_msg_queue);
}
LTE_FDD_ENB_ERROR_ENUM LTE_fdd_enb_rb::get_next_mme_nas_msg(LIBLTE_BYTE_MSG_STRUCT **nas_msg)
{
    return get_next_msg(mme_nas_msg_queue_mutex, &mme_nas_msg_queue, nas_msg);
}
LTE_FDD_ENB_ERROR_ENUM LTE_fdd_enb_rb::delete_next_mme_nas_msg()
{
    return delete_next_msg(mme_nas_msg_queue_mutex, &mme_nas_msg_queue);
}
void LTE_fdd_enb_rb::set_mme_procedure(LTE_FDD_ENB_MME_PROC_ENUM procedure)
{
    interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                              LTE_FDD_ENB_DEBUG_LEVEL_RB,
                              __FILE__,
                              __LINE__,
                              "%s MME procedure moving from %s to %s for RNTI=%u",
                              LTE_fdd_enb_rb_text[rb],
                              LTE_fdd_enb_mme_proc_text[mme_procedure],
                              LTE_fdd_enb_mme_proc_text[procedure],
                              user->get_c_rnti());

    mme_procedure = procedure;
}
LTE_FDD_ENB_MME_PROC_ENUM LTE_fdd_enb_rb::get_mme_procedure()
{
    return mme_procedure;
}
void LTE_fdd_enb_rb::set_mme_state(LTE_FDD_ENB_MME_STATE_ENUM state)
{
    interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                              LTE_FDD_ENB_DEBUG_LEVEL_RB,
                              __FILE__,
                              __LINE__,
                              "%s MME state moving from %s to %s for RNTI=%u",
                              LTE_fdd_enb_rb_text[rb],
                              LTE_fdd_enb_mme_state_text[mme_state],
                              LTE_fdd_enb_mme_state_text[state],
                              user->get_c_rnti());

    mme_state = state;
}
LTE_FDD_ENB_MME_STATE_ENUM LTE_fdd_enb_rb::get_mme_state()
{
    return mme_state;
}

/*************/
/*    RRC    */
/*************/
void LTE_fdd_enb_rb::queue_rrc_pdu(LIBLTE_BIT_MSG_STRUCT *pdu)
{
    queue_msg(pdu, rrc_pdu_queue_mutex, &rrc_pdu_queue);
}
LTE_FDD_ENB_ERROR_ENUM LTE_fdd_enb_rb::get_next_rrc_pdu(LIBLTE_BIT_MSG_STRUCT **pdu)
{
    return get_next_msg(rrc_pdu_queue_mutex, &rrc_pdu_queue, pdu);
}
LTE_FDD_ENB_ERROR_ENUM LTE_fdd_enb_rb::delete_next_rrc_pdu()
{
    return delete_next_msg(rrc_pdu_queue_mutex, &rrc_pdu_queue);
}
void LTE_fdd_enb_rb::queue_rrc_nas_msg(LIBLTE_BYTE_MSG_STRUCT *nas_msg)
{
    queue_msg(nas_msg, rrc_nas_msg_queue_mutex, &rrc_nas_msg_queue);
}
LTE_FDD_ENB_ERROR_ENUM LTE_fdd_enb_rb::get_next_rrc_nas_msg(LIBLTE_BYTE_MSG_STRUCT **nas_msg)
{
    return get_next_msg(rrc_nas_msg_queue_mutex, &rrc_nas_msg_queue, nas_msg);
}
LTE_FDD_ENB_ERROR_ENUM LTE_fdd_enb_rb::delete_next_rrc_nas_msg()
{
    return delete_next_msg(rrc_nas_msg_queue_mutex, &rrc_nas_msg_queue);
}
void LTE_fdd_enb_rb::set_rrc_procedure(LTE_FDD_ENB_RRC_PROC_ENUM procedure)
{
    interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                              LTE_FDD_ENB_DEBUG_LEVEL_RB,
                              __FILE__,
                              __LINE__,
                              "%s RRC procedure moving from %s to %s for RNTI=%u",
                              LTE_fdd_enb_rb_text[rb],
                              LTE_fdd_enb_rrc_proc_text[rrc_procedure],
                              LTE_fdd_enb_rrc_proc_text[procedure],
                              user->get_c_rnti());
    rrc_procedure = procedure;
}
LTE_FDD_ENB_RRC_PROC_ENUM LTE_fdd_enb_rb::get_rrc_procedure()
{
    return rrc_procedure;
}
void LTE_fdd_enb_rb::set_rrc_state(LTE_FDD_ENB_RRC_STATE_ENUM state)
{
    interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                              LTE_FDD_ENB_DEBUG_LEVEL_RB,
                              __FILE__,
                              __LINE__,
                              "%s RRC state moving from %s to %s for RNTI=%u",
                              LTE_fdd_enb_rb_text[rb],
                              LTE_fdd_enb_rrc_state_text[rrc_state],
                              LTE_fdd_enb_rrc_state_text[state],
                              user->get_c_rnti());
    rrc_state = state;
}
LTE_FDD_ENB_RRC_STATE_ENUM LTE_fdd_enb_rb::get_rrc_state()
{
    return rrc_state;
}
uint8 LTE_fdd_enb_rb::get_rrc_transaction_id()
{
    return rrc_transaction_id;
}
void LTE_fdd_enb_rb::set_rrc_transaction_id(uint8 transaction_id)
{
    rrc_transaction_id = transaction_id;
}

/**************/
/*    PDCP    */
/**************/
void LTE_fdd_enb_rb::queue_pdcp_pdu(LIBLTE_BYTE_MSG_STRUCT *pdu)
{
    queue_msg(pdu, pdcp_pdu_queue_mutex, &pdcp_pdu_queue);
}
LTE_FDD_ENB_ERROR_ENUM LTE_fdd_enb_rb::get_next_pdcp_pdu(LIBLTE_BYTE_MSG_STRUCT **pdu)
{
    return get_next_msg(pdcp_pdu_queue_mutex, &pdcp_pdu_queue, pdu);
}
LTE_FDD_ENB_ERROR_ENUM LTE_fdd_enb_rb::delete_next_pdcp_pdu()
{
    return delete_next_msg(pdcp_pdu_queue_mutex, &pdcp_pdu_queue);
}
void LTE_fdd_enb_rb::queue_pdcp_sdu(std::vector<uint8_t> &sdu)
{
    LIBLTE_BIT_MSG_STRUCT actual_sdu;
    actual_sdu.N_bits = sdu.size();
    for(uint32 i=0; i<sdu.size(); i++)
        actual_sdu.msg[i] = sdu[i];
    queue_msg(&actual_sdu, pdcp_sdu_queue_mutex, &pdcp_sdu_queue);
}
LTE_FDD_ENB_ERROR_ENUM LTE_fdd_enb_rb::get_next_pdcp_sdu(LIBLTE_BIT_MSG_STRUCT **sdu)
{
    return get_next_msg(pdcp_sdu_queue_mutex, &pdcp_sdu_queue, sdu);
}
LTE_FDD_ENB_ERROR_ENUM LTE_fdd_enb_rb::delete_next_pdcp_sdu()
{
    return delete_next_msg(pdcp_sdu_queue_mutex, &pdcp_sdu_queue);
}
void LTE_fdd_enb_rb::queue_pdcp_data_sdu(LIBLTE_BYTE_MSG_STRUCT *sdu)
{
    queue_msg(sdu, pdcp_data_sdu_queue_mutex, &pdcp_data_sdu_queue);
}
LTE_FDD_ENB_ERROR_ENUM LTE_fdd_enb_rb::get_next_pdcp_data_sdu(LIBLTE_BYTE_MSG_STRUCT **sdu)
{
    return get_next_msg(pdcp_data_sdu_queue_mutex, &pdcp_data_sdu_queue, sdu);
}
LTE_FDD_ENB_ERROR_ENUM LTE_fdd_enb_rb::delete_next_pdcp_data_sdu()
{
    return delete_next_msg(pdcp_data_sdu_queue_mutex, &pdcp_data_sdu_queue);
}
void LTE_fdd_enb_rb::set_pdcp_config(LTE_FDD_ENB_PDCP_CONFIG_ENUM config)
{
    pdcp_config = config;
}
LTE_FDD_ENB_PDCP_CONFIG_ENUM LTE_fdd_enb_rb::get_pdcp_config()
{
    return pdcp_config;
}
uint32 LTE_fdd_enb_rb::get_pdcp_rx_count()
{
    return pdcp_rx_count;
}
void LTE_fdd_enb_rb::set_pdcp_rx_count(uint32 rx_count)
{
    pdcp_rx_count = rx_count;
}
uint32 LTE_fdd_enb_rb::get_pdcp_tx_count()
{
    return pdcp_tx_count;
}
void LTE_fdd_enb_rb::set_pdcp_tx_count(uint32 tx_count)
{
    pdcp_tx_count = tx_count;
}

/*************/
/*    RLC    */
/*************/
void LTE_fdd_enb_rb::queue_rlc_pdu(LIBLTE_BYTE_MSG_STRUCT *pdu)
{
    queue_msg(pdu, rlc_pdu_queue_mutex, &rlc_pdu_queue);
}
LTE_FDD_ENB_ERROR_ENUM LTE_fdd_enb_rb::get_next_rlc_pdu(LIBLTE_BYTE_MSG_STRUCT **pdu)
{
    return get_next_msg(rlc_pdu_queue_mutex, &rlc_pdu_queue, pdu);
}
LTE_FDD_ENB_ERROR_ENUM LTE_fdd_enb_rb::delete_next_rlc_pdu()
{
    return delete_next_msg(rlc_pdu_queue_mutex, &rlc_pdu_queue);
}
void LTE_fdd_enb_rb::queue_rlc_sdu(LIBLTE_BYTE_MSG_STRUCT *sdu)
{
    queue_msg(sdu, rlc_sdu_queue_mutex, &rlc_sdu_queue);
}
LTE_FDD_ENB_ERROR_ENUM LTE_fdd_enb_rb::get_next_rlc_sdu(LIBLTE_BYTE_MSG_STRUCT **sdu)
{
    return get_next_msg(rlc_sdu_queue_mutex, &rlc_sdu_queue, sdu);
}
LTE_FDD_ENB_ERROR_ENUM LTE_fdd_enb_rb::delete_next_rlc_sdu()
{
    return delete_next_msg(rlc_sdu_queue_mutex, &rlc_sdu_queue);
}
LTE_FDD_ENB_RLC_CONFIG_ENUM LTE_fdd_enb_rb::get_rlc_config()
{
    return rlc_config;
}
uint16 LTE_fdd_enb_rb::get_rlc_vrr()
{
    return rlc_vrr;
}
void LTE_fdd_enb_rb::set_rlc_vrr(uint16 vrr)
{
    rlc_vrr  = vrr;
    rlc_vrmr = rlc_vrr + LIBLTE_RLC_AM_WINDOW_SIZE;
}
void LTE_fdd_enb_rb::update_rlc_vrr()
{
    uint32 i;
    uint16 vrr = rlc_vrr;

    for(i=vrr; i<rlc_vrh; i++)
    {
        if(rlc_am_rx_buffer.end() != rlc_am_rx_buffer.find(i))
        {
            rlc_vrr = i+1;
        }else{
            break;
        }
    }
}
uint16 LTE_fdd_enb_rb::get_rlc_vrmr()
{
    return rlc_vrmr;
}
uint16 LTE_fdd_enb_rb::get_rlc_vrh()
{
    return rlc_vrh;
}
void LTE_fdd_enb_rb::set_rlc_vrh(uint16 vrh)
{
    rlc_vrh = vrh;
}
void LTE_fdd_enb_rb::rlc_add_to_am_reception_buffer(LIBLTE_RLC_SINGLE_AMD_PDU_STRUCT *amd_pdu)
{
    LIBLTE_RLC_SINGLE_AMD_PDU_STRUCT *new_pdu = new LIBLTE_RLC_SINGLE_AMD_PDU_STRUCT;

    if(NULL == new_pdu)
        return;

    if(rlc_am_rx_buffer.end() == rlc_am_rx_buffer.find(amd_pdu->hdr.sn))
    {
        memcpy(new_pdu, amd_pdu, sizeof(LIBLTE_RLC_SINGLE_AMD_PDU_STRUCT));
        rlc_am_rx_buffer[amd_pdu->hdr.sn] = new_pdu;
    }else{
        delete new_pdu;
    }
}
void LTE_fdd_enb_rb::rlc_get_am_reception_buffer_status(LIBLTE_RLC_STATUS_PDU_STRUCT *status)
{
    uint32 i;

    // Fill in the ACK_SN
    status->ack_sn = rlc_vrh;

    // Determine if any NACK_SNs are needed
    status->N_nack = 0;
    for(i=rlc_vrr; i<rlc_vrh; i++)
    {
        if(i > 0x3FFFF)
            i -= 0x3FFFF;

        if(rlc_am_rx_buffer.end() == rlc_am_rx_buffer.find(i))
            status->nack_sn[status->N_nack++] = i;
    }

    // Update VR(R) if there are no missing frames
    if(0 == status->N_nack)
        set_rlc_vrr(rlc_vrh);
}
LTE_FDD_ENB_ERROR_ENUM LTE_fdd_enb_rb::rlc_am_reassemble(LIBLTE_BYTE_MSG_STRUCT *sdu)
{
    std::list<uint16>           first;
    std::list<uint16>           last;
    std::list<uint16>::iterator first_iter;
    std::list<uint16>::iterator last_iter;
    LTE_FDD_ENB_ERROR_ENUM      err = LTE_FDD_ENB_ERROR_CANT_REASSEMBLE_SDU;
    uint32                      i;

    // Find all first and last SDUs
    for(auto rlc_am_rx : rlc_am_rx_buffer)
    {
        if(LIBLTE_RLC_FI_FIELD_FULL_SDU == rlc_am_rx.second->hdr.fi)
        {
            first.push_back(rlc_am_rx.second->hdr.sn);
            last.push_back(rlc_am_rx.second->hdr.sn);
        }else if(LIBLTE_RLC_FI_FIELD_FIRST_SDU_SEGMENT == rlc_am_rx.second->hdr.fi){
            first.push_back(rlc_am_rx.second->hdr.sn);
        }else if(LIBLTE_RLC_FI_FIELD_LAST_SDU_SEGMENT == rlc_am_rx.second->hdr.fi){
            last.push_back(rlc_am_rx.second->hdr.sn);
        }
    }

    // Check all first segments to see if the complete SDU is present
    for(first_iter=first.begin(); first_iter!=first.end(); first_iter++)
    {
        for(last_iter=last.begin(); last_iter!=last.end(); last_iter++)
            if((*last_iter) >= (*first_iter))
                break;

        if(last_iter != last.end())
        {
            // Check that the whole SDU is present
            bool reassemble = true;
            for(i=(*first_iter); i<=(*last_iter); i++)
                if(rlc_am_rx_buffer.end() == rlc_am_rx_buffer.find(i))
                {
                    reassemble = false;
                    break;
                }
            if(!reassemble)
                continue;

            // Reorder and reassemble the SDU
            sdu->N_bytes = 0;
            for(i=(*first_iter); i<=(*last_iter); i++)
            {
                auto rlc_am_rx_it = rlc_am_rx_buffer.find(i);
                memcpy(&sdu->msg[sdu->N_bytes], (*rlc_am_rx_it).second->data.msg, (*rlc_am_rx_it).second->data.N_bytes);
                sdu->N_bytes += (*rlc_am_rx_it).second->data.N_bytes;
                delete (*rlc_am_rx_it).second;
                rlc_am_rx_buffer.erase(rlc_am_rx_it);
            }
            err = LTE_FDD_ENB_ERROR_NONE;
            continue;
        }
    }

    return err;
}
uint16 LTE_fdd_enb_rb::get_rlc_vta()
{
    return rlc_vta;
}
void LTE_fdd_enb_rb::set_rlc_vta(uint16 vta)
{
    rlc_vta  = vta;
    rlc_vtms = rlc_vta + LIBLTE_RLC_AM_WINDOW_SIZE;
}
uint16 LTE_fdd_enb_rb::get_rlc_vtms()
{
    return rlc_vtms;
}
uint16 LTE_fdd_enb_rb::get_rlc_vts()
{
    return rlc_vts;
}
void LTE_fdd_enb_rb::set_rlc_vts(uint16 vts)
{
    rlc_vts = vts;
}
void LTE_fdd_enb_rb::rlc_add_to_transmission_buffer(LIBLTE_RLC_SINGLE_AMD_PDU_STRUCT *amd_pdu)
{
    LIBLTE_RLC_SINGLE_AMD_PDU_STRUCT *new_pdu = new LIBLTE_RLC_SINGLE_AMD_PDU_STRUCT;

    if(NULL == new_pdu)
        return;

    memcpy(new_pdu, amd_pdu, sizeof(LIBLTE_RLC_SINGLE_AMD_PDU_STRUCT));
    rlc_am_tx_buffer[amd_pdu->hdr.sn] = new_pdu;
}
void LTE_fdd_enb_rb::rlc_update_transmission_buffer(LIBLTE_RLC_STATUS_PDU_STRUCT *status)
{
    uint32 i = rlc_vta;
    uint32 j;
    bool   update_vta = true;
    bool   remove_sn;

    while(i != status->ack_sn)
    {
        remove_sn = true;
        for(j=0; j<status->N_nack; j++)
        {
            if(i == status->nack_sn[j])
            {
                remove_sn  = false;
                update_vta = false;
                break;
            }
        }
        if(remove_sn)
        {
            auto rlc_am_tx_it = rlc_am_tx_buffer.find(i);
            if(rlc_am_tx_buffer.end() != rlc_am_tx_it)
            {
                delete (*rlc_am_tx_it).second;
                rlc_am_tx_buffer.erase(rlc_am_tx_it);
            }
            if(update_vta)
                set_rlc_vta(i+1);
        }
        i = (i+1) % 1024;
    }

    if(rlc_am_tx_buffer.size() == 0)
        rlc_stop_t_poll_retransmit();
}
void LTE_fdd_enb_rb::rlc_start_t_poll_retransmit()
{
    LTE_fdd_enb_timer_cb timer_expiry_cb(&LTE_fdd_enb_timer_cb_wrapper<LTE_fdd_enb_rb, &LTE_fdd_enb_rb::handle_t_poll_retransmit_timer_expiry>, this);

    if(LTE_FDD_ENB_INVALID_TIMER_ID == t_poll_retransmit_timer_id)
        timer_mgr->start_timer(100, timer_expiry_cb, &t_poll_retransmit_timer_id);
}
void LTE_fdd_enb_rb::rlc_stop_t_poll_retransmit()
{
    timer_mgr->stop_timer(t_poll_retransmit_timer_id);
    t_poll_retransmit_timer_id = LTE_FDD_ENB_INVALID_TIMER_ID;
}
void LTE_fdd_enb_rb::handle_t_poll_retransmit_timer_expiry(uint32 timer_id)
{
    auto rlc_am_tx_it = rlc_am_tx_buffer.find(rlc_vta);

    t_poll_retransmit_timer_id = LTE_FDD_ENB_INVALID_TIMER_ID;

    if(rlc_am_tx_buffer.end() != rlc_am_tx_it)
        rlc->handle_retransmit((*rlc_am_tx_it).second, user, this);
}
void LTE_fdd_enb_rb::set_rlc_vruh(uint16 vruh)
{
    rlc_vruh = vruh;
}
uint16 LTE_fdd_enb_rb::get_rlc_vruh()
{
    return rlc_vruh;
}
void LTE_fdd_enb_rb::set_rlc_vrur(uint16 vrur)
{
    rlc_vrur = vrur;
}
uint16 LTE_fdd_enb_rb::get_rlc_vrur()
{
    return rlc_vrur ;
}
uint16 LTE_fdd_enb_rb::get_rlc_um_window_size()
{
    return rlc_um_window_size;
}
void LTE_fdd_enb_rb::rlc_add_to_um_reception_buffer(LIBLTE_RLC_UMD_PDU_STRUCT *umd_pdu,
                                                    uint32                     idx)
{
    LIBLTE_RLC_UMD_PDU_STRUCT *new_pdu = new LIBLTE_RLC_UMD_PDU_STRUCT;

    if(NULL == new_pdu)
        return;

    if(rlc_um_rx_buffer.end() != rlc_um_rx_buffer.find(umd_pdu->hdr.sn))
    {
        delete new_pdu;
        return;
    }

    memcpy(new_pdu, &umd_pdu->data[idx], sizeof(LIBLTE_BYTE_MSG_STRUCT));
    rlc_um_rx_buffer[umd_pdu->hdr.sn] = new_pdu;
}
LTE_FDD_ENB_ERROR_ENUM LTE_fdd_enb_rb::rlc_um_reassemble(LIBLTE_BYTE_MSG_STRUCT *sdu)
{
    std::list<uint16>           first;
    std::list<uint16>           last;
    std::list<uint16>::iterator first_iter;
    std::list<uint16>::iterator last_iter;
    LTE_FDD_ENB_ERROR_ENUM      err = LTE_FDD_ENB_ERROR_CANT_REASSEMBLE_SDU;
    uint32                      i;

    // Find all first and last SDUs
    for(auto rlc_um_rx : rlc_um_rx_buffer)
    {
        if(LIBLTE_RLC_FI_FIELD_FULL_SDU == rlc_um_rx.second->hdr.fi)
        {
            first.push_back(rlc_um_rx.second->hdr.sn);
            last.push_back(rlc_um_rx.second->hdr.sn);
        }else if(LIBLTE_RLC_FI_FIELD_FIRST_SDU_SEGMENT == rlc_um_rx.second->hdr.fi){
            first.push_back(rlc_um_rx.second->hdr.sn);
        }else if(LIBLTE_RLC_FI_FIELD_LAST_SDU_SEGMENT == rlc_um_rx.second->hdr.fi){
            last.push_back(rlc_um_rx.second->hdr.sn);
        }
    }

    // Check all first segments to see if the complete SDU is present
    for(first_iter=first.begin(); first_iter!=first.end(); first_iter++)
    {
        for(last_iter=last.begin(); last_iter!=last.end(); last_iter++)
            if((*last_iter) >= (*first_iter))
                break;

        if(last_iter != last.end())
        {
            // Check that the whole SDU is present
            bool reassemble = true;
            for(i=(*first_iter); i<=(*last_iter); i++)
                if(rlc_um_rx_buffer.end() == rlc_um_rx_buffer.find(i))
                {
                    reassemble = false;
                    break;
                }
            if(!reassemble)
                continue;

            // Reorder and reassemble the SDU
            sdu->N_bytes = 0;
            for(i=(*first_iter); i<=(*last_iter); i++)
            {
                auto rlc_um_rx_it = rlc_um_rx_buffer.find(i);
                memcpy(&sdu->msg[sdu->N_bytes], (*rlc_um_rx_it).second->data[0].msg, (*rlc_um_rx_it).second->data[0].N_bytes);
                sdu->N_bytes += (*rlc_um_rx_it).second->data[0].N_bytes;
                delete (*rlc_um_rx_it).second;
                rlc_um_rx_buffer.erase(rlc_um_rx_it);
            }
            err = LTE_FDD_ENB_ERROR_NONE;
            continue;
        }
    }

    return err;
}
void LTE_fdd_enb_rb::set_rlc_vtus(uint16 vtus)
{
    rlc_vtus = vtus;
}
uint16 LTE_fdd_enb_rb::get_rlc_vtus()
{
    return rlc_vtus;
}

/*************/
/*    MAC    */
/*************/
void LTE_fdd_enb_rb::queue_mac_sdu(LIBLTE_BYTE_MSG_STRUCT *sdu)
{
    queue_msg(sdu, mac_sdu_queue_mutex, &mac_sdu_queue);
}
LTE_FDD_ENB_ERROR_ENUM LTE_fdd_enb_rb::get_next_mac_sdu(LIBLTE_BYTE_MSG_STRUCT **sdu)
{
    return get_next_msg(mac_sdu_queue_mutex, &mac_sdu_queue, sdu);
}
LTE_FDD_ENB_ERROR_ENUM LTE_fdd_enb_rb::delete_next_mac_sdu()
{
    return delete_next_msg(mac_sdu_queue_mutex, &mac_sdu_queue);
}
LTE_FDD_ENB_MAC_CONFIG_ENUM LTE_fdd_enb_rb::get_mac_config()
{
    return mac_config;
}
void LTE_fdd_enb_rb::set_con_res_id(uint64 con_res_id)
{
    mac_con_res_id = con_res_id;
}
uint64 LTE_fdd_enb_rb::get_con_res_id()
{
    return mac_con_res_id;
}
void LTE_fdd_enb_rb::set_send_con_res_id(bool send_con_res_id)
{
    mac_send_con_res_id = send_con_res_id;
}
bool LTE_fdd_enb_rb::get_send_con_res_id()
{
    return mac_send_con_res_id;
}

/*************/
/*    DRB    */
/*************/
void LTE_fdd_enb_rb::set_eps_bearer_id(uint32 ebi)
{
    eps_bearer_id = ebi;
}
uint32 LTE_fdd_enb_rb::get_eps_bearer_id()
{
    return eps_bearer_id;
}
void LTE_fdd_enb_rb::set_lc_id(uint32 _lc_id)
{
    lc_id = _lc_id;
}
uint32 LTE_fdd_enb_rb::get_lc_id()
{
    return lc_id;
}
void LTE_fdd_enb_rb::set_drb_id(uint8 _drb_id)
{
    drb_id = _drb_id;
}
uint8 LTE_fdd_enb_rb::get_drb_id()
{
    return drb_id;
}
void LTE_fdd_enb_rb::set_log_chan_group(uint8 lcg)
{
    log_chan_group = lcg;
}
uint8 LTE_fdd_enb_rb::get_log_chan_group()
{
    return log_chan_group;
}

/*****************/
/*    Generic    */
/*****************/
void LTE_fdd_enb_rb::queue_msg(LIBLTE_BIT_MSG_STRUCT              *msg,
                               std::mutex                         &mutex,
                               std::list<LIBLTE_BIT_MSG_STRUCT *> *queue)
{
    std::lock_guard<std::mutex>  lock(mutex);
    LIBLTE_BIT_MSG_STRUCT       *loc_msg = new LIBLTE_BIT_MSG_STRUCT;

    memcpy(loc_msg, msg, sizeof(LIBLTE_BIT_MSG_STRUCT));
    queue->push_back(loc_msg);
}
void LTE_fdd_enb_rb::queue_msg(LIBLTE_BYTE_MSG_STRUCT              *msg,
                               std::mutex                          &mutex,
                               std::list<LIBLTE_BYTE_MSG_STRUCT *> *queue)
{
    std::lock_guard<std::mutex>  lock(mutex);
    LIBLTE_BYTE_MSG_STRUCT      *loc_msg = new LIBLTE_BYTE_MSG_STRUCT;

    memcpy(loc_msg, msg, sizeof(LIBLTE_BYTE_MSG_STRUCT));
    queue->push_back(loc_msg);
}
LTE_FDD_ENB_ERROR_ENUM LTE_fdd_enb_rb::get_next_msg(std::mutex                          &mutex,
                                                    std::list<LIBLTE_BIT_MSG_STRUCT *>  *queue,
                                                    LIBLTE_BIT_MSG_STRUCT              **msg)
{
    std::lock_guard<std::mutex> lock(mutex);

    if(0 == queue->size())
        return LTE_FDD_ENB_ERROR_NO_MSG_IN_QUEUE;

    *msg = queue->front();
    return LTE_FDD_ENB_ERROR_NONE;
}
LTE_FDD_ENB_ERROR_ENUM LTE_fdd_enb_rb::get_next_msg(std::mutex                           &mutex,
                                                    std::list<LIBLTE_BYTE_MSG_STRUCT *>  *queue,
                                                    LIBLTE_BYTE_MSG_STRUCT              **msg)
{
    std::lock_guard<std::mutex> lock(mutex);

    if(0 == queue->size())
        return LTE_FDD_ENB_ERROR_NO_MSG_IN_QUEUE;

    *msg = queue->front();
    return LTE_FDD_ENB_ERROR_NONE;
}
LTE_FDD_ENB_ERROR_ENUM LTE_fdd_enb_rb::delete_next_msg(std::mutex                         &mutex,
                                                       std::list<LIBLTE_BIT_MSG_STRUCT *> *queue)
{
    std::lock_guard<std::mutex>  lock(mutex);
    LIBLTE_BIT_MSG_STRUCT       *msg;

    if(0 == queue->size())
        return LTE_FDD_ENB_ERROR_NO_MSG_IN_QUEUE;

    msg = queue->front();
    queue->pop_front();
    delete msg;
    return LTE_FDD_ENB_ERROR_NONE;
}
LTE_FDD_ENB_ERROR_ENUM LTE_fdd_enb_rb::delete_next_msg(std::mutex                          &mutex,
                                                       std::list<LIBLTE_BYTE_MSG_STRUCT *> *queue)
{
    std::lock_guard<std::mutex>  lock(mutex);
    LIBLTE_BYTE_MSG_STRUCT      *msg;

    if(0 == queue->size())
        return LTE_FDD_ENB_ERROR_NO_MSG_IN_QUEUE;

    msg = queue->front();
    queue->pop_front();
    delete msg;
    return LTE_FDD_ENB_ERROR_NONE;
}
