#line 2 "LTE_fdd_enb_rlc.cc" // Make __FILE__ omit the path
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

    File: LTE_fdd_enb_rlc.cc

    Description: Contains all the implementations for the LTE FDD eNodeB
                 radio link control layer.

    Revision History
    ----------    -------------    --------------------------------------------
    11/10/2013    Ben Wojtowicz    Created file
    01/18/2014    Ben Wojtowicz    Added level to debug prints.
    05/04/2014    Ben Wojtowicz    Added communication to MAC and PDCP.
    06/15/2014    Ben Wojtowicz    Added basic AM receive functionality.
    08/03/2014    Ben Wojtowicz    Added transmit functionality.
    09/03/2014    Ben Wojtowicz    Added debug print and status request.
    11/01/2014    Ben Wojtowicz    Fixed VRR updating and added debug.
    11/29/2014    Ben Wojtowicz    Using the byte message structure and added
                                   UMD support.
    12/16/2014    Ben Wojtowicz    Added ol extension to message queues.
    12/24/2014    Ben Wojtowicz    Using asymmetric QoS.
    02/15/2015    Ben Wojtowicz    Moved to new message queue and added header
                                   extension/multiple data support to UMD.
    03/11/2015    Ben Wojtowicz    Added header extension/multiple data support
                                   to AMD.
    07/25/2015    Ben Wojtowicz    Using the new user QoS structure.
    12/06/2015    Ben Wojtowicz    Changed boost::mutex to pthread_mutex_t and
                                   sem_t.
    07/03/2016    Ben Wojtowicz    Added error log for AMD PDU segments.
    12/18/2016    Ben Wojtowicz    Properly handling multiple AMD PDUs.
    07/29/2017    Ben Wojtowicz    Try more than one reassembly and always send
                                   poll frames.
    02/14/2021    Ben Wojtowicz    Massive reformat.

*******************************************************************************/

/*******************************************************************************
                              INCLUDES
*******************************************************************************/

#include "LTE_fdd_enb_rlc.h"
#include "liblte_rlc.h"

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
LTE_fdd_enb_rlc::LTE_fdd_enb_rlc(LTE_fdd_enb_interface *iface) :
    interface{iface}, started{false}
{
}
LTE_fdd_enb_rlc::~LTE_fdd_enb_rlc()
{
    stop();
}

/********************/
/*    Start/Stop    */
/********************/
void LTE_fdd_enb_rlc::start(LTE_fdd_enb_msgq *from_mac,
                            LTE_fdd_enb_msgq *from_pdcp,
                            LTE_fdd_enb_msgq *to_mac,
                            LTE_fdd_enb_msgq *to_pdcp)
{
    std::lock_guard<std::mutex> lock(start_mutex);

    if(started)
        return;

    started        = true;
    msgq_from_mac  = from_mac;
    msgq_from_pdcp = from_pdcp;
    msgq_to_mac    = to_mac;
    msgq_to_pdcp   = to_pdcp;
    LTE_fdd_enb_msgq_cb mac_cb(&LTE_fdd_enb_msgq_cb_wrapper<LTE_fdd_enb_rlc, &LTE_fdd_enb_rlc::handle_mac_msg>, this);
    msgq_from_mac->attach_rx(mac_cb);
    LTE_fdd_enb_msgq_cb pdcp_cb(&LTE_fdd_enb_msgq_cb_wrapper<LTE_fdd_enb_rlc, &LTE_fdd_enb_rlc::handle_pdcp_msg>, this);
    msgq_from_pdcp->attach_rx(pdcp_cb);
}
void LTE_fdd_enb_rlc::stop()
{
    std::lock_guard<std::mutex> lock(start_mutex);

    if(started)
        started = false;
}

/***********************/
/*    Communication    */
/***********************/
void LTE_fdd_enb_rlc::handle_mac_msg(LTE_FDD_ENB_MESSAGE_STRUCT &msg)
{
    if(LTE_FDD_ENB_DEST_LAYER_RLC != msg.dest_layer &&
       LTE_FDD_ENB_DEST_LAYER_ANY != msg.dest_layer)
        return msgq_to_pdcp->send(msg); // Forward message to PDCP

    if(msg.type == LTE_FDD_ENB_MESSAGE_TYPE_RLC_PDU_READY)
        return handle_pdu_ready(&msg.msg.rlc_pdu_ready);

    interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                              LTE_FDD_ENB_DEBUG_LEVEL_RLC,
                              __FILE__,
                              __LINE__,
                              "Received invalid MAC message %s",
                              LTE_fdd_enb_message_type_text[msg.type]);
}
void LTE_fdd_enb_rlc::handle_pdcp_msg(LTE_FDD_ENB_MESSAGE_STRUCT &msg)
{
    if(LTE_FDD_ENB_DEST_LAYER_RLC != msg.dest_layer &&
       LTE_FDD_ENB_DEST_LAYER_ANY != msg.dest_layer)
        return msgq_to_mac->send(msg); // Forward message to MAC

    if(msg.type == LTE_FDD_ENB_MESSAGE_TYPE_RLC_SDU_READY)
        return handle_sdu_ready(&msg.msg.rlc_sdu_ready);

    interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                              LTE_FDD_ENB_DEBUG_LEVEL_RLC,
                              __FILE__,
                              __LINE__,
                              "Received invalid PDCP message %s",
                              LTE_fdd_enb_message_type_text[msg.type]);
}
void LTE_fdd_enb_rlc::send_mac_sdu_ready(LTE_fdd_enb_user       *user,
                                         LTE_fdd_enb_rb         *rb,
                                         LIBLTE_BYTE_MSG_STRUCT *sdu)
{
    LTE_FDD_ENB_MAC_SDU_READY_MSG_STRUCT sdu_ready;

    rb->queue_mac_sdu(sdu);

    interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                              LTE_FDD_ENB_DEBUG_LEVEL_RLC,
                              __FILE__,
                              __LINE__,
                              sdu,
                              "Sending PDU to MAC for RNTI=%u, RB=%s, VT(A)=%u, VT(MS)=%u",
                              user->get_c_rnti(),
                              LTE_fdd_enb_rb_text[rb->get_rb_id()],
                              rb->get_rlc_vta(),
                              rb->get_rlc_vtms());

    sdu_ready.user = user;
    sdu_ready.rb   = rb;
    msgq_to_mac->send(LTE_FDD_ENB_MESSAGE_TYPE_MAC_SDU_READY,
                      LTE_FDD_ENB_DEST_LAYER_MAC,
                      (LTE_FDD_ENB_MESSAGE_UNION *)&sdu_ready,
                      sizeof(sdu_ready));
}
void LTE_fdd_enb_rlc::send_pdcp_pdu_ready(LTE_fdd_enb_user       *user,
                                          LTE_fdd_enb_rb         *rb,
                                          LIBLTE_BYTE_MSG_STRUCT *pdu)
{
    LTE_FDD_ENB_PDCP_PDU_READY_MSG_STRUCT pdu_ready;

    rb->queue_pdcp_pdu(pdu);

    interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                              LTE_FDD_ENB_DEBUG_LEVEL_RLC,
                              __FILE__,
                              __LINE__,
                              pdu,
                              "Sending SDU to PDCP for RNTI=%u, RB=%s",
                              user->get_c_rnti(),
                              LTE_fdd_enb_rb_text[rb->get_rb_id()]);

    pdu_ready.user = user;
    pdu_ready.rb   = rb;
    msgq_to_pdcp->send(LTE_FDD_ENB_MESSAGE_TYPE_PDCP_PDU_READY,
                       LTE_FDD_ENB_DEST_LAYER_PDCP,
                       (LTE_FDD_ENB_MESSAGE_UNION *)&pdu_ready,
                       sizeof(pdu_ready));
}

/****************************/
/*    External Interface    */
/****************************/
void LTE_fdd_enb_rlc::update_sys_info()
{
    std::lock_guard<std::mutex>  lock(sys_info_mutex);
    interface->get_sys_info(sys_info);
}
void LTE_fdd_enb_rlc::handle_retransmit(LIBLTE_RLC_SINGLE_AMD_PDU_STRUCT *amd,
                                        LTE_fdd_enb_user                 *user,
                                        LTE_fdd_enb_rb                   *rb)
{
    LIBLTE_BYTE_MSG_STRUCT pdu;

    // Pack the PDU
    amd->hdr.p = LIBLTE_RLC_P_FIELD_STATUS_REPORT_REQUESTED;
    liblte_rlc_pack_amd_pdu(amd, &amd->data, &pdu);

    // Start t-pollretransmit
    rb->rlc_start_t_poll_retransmit();

    interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                              LTE_FDD_ENB_DEBUG_LEVEL_RLC,
                              __FILE__,
                              __LINE__,
                              "Re-sending AMD PDU for RNTI=%u, RB=%s, VT(A)=%u, SN=%u, VT(MS)=%u, RF=%s, P=%s, FI=%s",
                              user->get_c_rnti(),
                              LTE_fdd_enb_rb_text[rb->get_rb_id()],
                              rb->get_rlc_vta(),
                              amd->hdr.sn,
                              rb->get_rlc_vtms(),
                              liblte_rlc_rf_field_text[amd->hdr.rf],
                              liblte_rlc_p_field_text[amd->hdr.p],
                              liblte_rlc_fi_field_text[amd->hdr.fi]);

    // Send the SDU to MAC
    send_mac_sdu_ready(user, rb, &pdu);
}

/******************************/
/*    MAC Message Handlers    */
/******************************/
void LTE_fdd_enb_rlc::handle_pdu_ready(LTE_FDD_ENB_RLC_PDU_READY_MSG_STRUCT *pdu_ready)
{
    LIBLTE_BYTE_MSG_STRUCT *pdu;

    if(LTE_FDD_ENB_ERROR_NONE != pdu_ready->rb->get_next_rlc_pdu(&pdu))
        return interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                         LTE_FDD_ENB_DEBUG_LEVEL_RLC,
                                         __FILE__,
                                         __LINE__,
                                         "Received pdu_ready message with no PDU queued");

    interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                              LTE_FDD_ENB_DEBUG_LEVEL_RLC,
                              __FILE__,
                              __LINE__,
                              pdu,
                              "Received PDU for RNTI=%u and RB=%s",
                              pdu_ready->user->get_c_rnti(),
                              LTE_fdd_enb_rb_text[pdu_ready->rb->get_rb_id()]);

    switch(pdu_ready->rb->get_rlc_config())
    {
    case LTE_FDD_ENB_RLC_CONFIG_TM:
        handle_tm_pdu(pdu, pdu_ready->user, pdu_ready->rb);
        break;
    case LTE_FDD_ENB_RLC_CONFIG_UM:
        handle_um_pdu(pdu, pdu_ready->user, pdu_ready->rb);
        break;
    case LTE_FDD_ENB_RLC_CONFIG_AM:
        handle_am_pdu(pdu, pdu_ready->user, pdu_ready->rb);
        break;
    default:
        interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                  LTE_FDD_ENB_DEBUG_LEVEL_RLC,
                                  __FILE__,
                                  __LINE__,
                                  pdu,
                                  "Received PDU for RNTI=%u, RB=%s, and invalid rlc_config=%s",
                                  pdu_ready->user->get_c_rnti(),
                                  LTE_fdd_enb_rb_text[pdu_ready->rb->get_rb_id()],
                                  LTE_fdd_enb_rlc_config_text[pdu_ready->rb->get_rlc_config()]);
        break;
    }

    // Delete the PDU
    pdu_ready->rb->delete_next_rlc_pdu();
}
void LTE_fdd_enb_rlc::handle_tm_pdu(LIBLTE_BYTE_MSG_STRUCT *pdu,
                                    LTE_fdd_enb_user       *user,
                                    LTE_fdd_enb_rb         *rb)
{
    // Send the SDU to PDCP
    send_pdcp_pdu_ready(user, rb, pdu);
}
void LTE_fdd_enb_rlc::handle_um_pdu(LIBLTE_BYTE_MSG_STRUCT *pdu,
                                    LTE_fdd_enb_user       *user,
                                    LTE_fdd_enb_rb         *rb)
{
    LIBLTE_BYTE_MSG_STRUCT    pdcp_pdu;
    LIBLTE_RLC_UMD_PDU_STRUCT umd;
    LIBLTE_RLC_FI_FIELD_ENUM  orig_fi;
    int32                     vrul = (int32)rb->get_rlc_vruh() - (int32)rb->get_rlc_um_window_size();
    uint16                    vrur = rb->get_rlc_vrur();

    umd.hdr.sn_size = LIBLTE_RLC_UMD_SN_SIZE_10_BITS;
    if(LIBLTE_SUCCESS != liblte_rlc_unpack_umd_pdu(pdu, &umd))
        return interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                         LTE_FDD_ENB_DEBUG_LEVEL_RLC,
                                         __FILE__,
                                         __LINE__,
                                         "Can't unpack UMD PDU");

    if(vrul       <= umd.hdr.sn &&
       umd.hdr.sn  < vrur)
        return interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                                         LTE_FDD_ENB_DEBUG_LEVEL_RLC,
                                         __FILE__,
                                         __LINE__,
                                         &umd.data[0],
                                         "Received UMD PDU for RNTI=%u, RB=%s, that is outside of the receiving window (%d <= %u < %u)",
                                         user->get_c_rnti(),
                                         LTE_fdd_enb_rb_text[rb->get_rb_id()],
                                         vrul,
                                         umd.hdr.sn,
                                         vrur);

    interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                              LTE_FDD_ENB_DEBUG_LEVEL_RLC,
                              __FILE__,
                              __LINE__,
                              &umd.data[0],
                              "Received UMD PDU for RNTI=%u, RB=%s, VR(UL)=%d, SN=%u, VR(UR)=%u, FI=%s",
                              user->get_c_rnti(),
                              LTE_fdd_enb_rb_text[rb->get_rb_id()],
                              vrul,
                              umd.hdr.sn,
                              vrur,
                              liblte_rlc_fi_field_text[umd.hdr.fi]);

    if(1 == umd.N_data)
    {
        // Place RLC data PDU in reception buffer
        rb->rlc_add_to_um_reception_buffer(&umd, 0);

        if(LTE_FDD_ENB_ERROR_NONE == rb->rlc_um_reassemble(&pdcp_pdu))
            send_pdcp_pdu_ready(user, rb, &pdcp_pdu); // Send the SDU to PDCP
        return;
    }

    if(2 == umd.N_data)
    {
        // Place first RLC data PDU in reception buffer
        orig_fi = umd.hdr.fi;
        if(LIBLTE_RLC_FI_FIELD_FULL_SDU != umd.hdr.fi)
            umd.hdr.fi = LIBLTE_RLC_FI_FIELD_LAST_SDU_SEGMENT;
        rb->rlc_add_to_um_reception_buffer(&umd, 0);

        if(LTE_FDD_ENB_ERROR_NONE == rb->rlc_um_reassemble(&pdcp_pdu))
            send_pdcp_pdu_ready(user, rb, &pdcp_pdu); // Send the PDU to PDCP

        // Place the second RLC data PDU in reception buffer
        if(LIBLTE_RLC_FI_FIELD_MIDDLE_SDU_SEGMENT == orig_fi)
        {
            umd.hdr.fi = LIBLTE_RLC_FI_FIELD_FIRST_SDU_SEGMENT;
        }else{
            umd.hdr.fi = orig_fi;
        }
        rb->rlc_add_to_um_reception_buffer(&umd, 1);

        if(LTE_FDD_ENB_ERROR_NONE == rb->rlc_um_reassemble(&pdcp_pdu))
            send_pdcp_pdu_ready(user, rb, &pdcp_pdu); // Send the SDU to PDCP
        return;
    }

    interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                              LTE_FDD_ENB_DEBUG_LEVEL_RLC,
                              __FILE__,
                              __LINE__,
                              "Multiple data segments (%u) in one RLC PDU",
                              umd.N_data);
}
void LTE_fdd_enb_rlc::handle_am_pdu(LIBLTE_BYTE_MSG_STRUCT *pdu,
                                    LTE_fdd_enb_user       *user,
                                    LTE_fdd_enb_rb         *rb)
{
    LIBLTE_BYTE_MSG_STRUCT       pdcp_pdu;
    LIBLTE_RLC_AMD_PDUS_STRUCT   amd_pdus;
    LIBLTE_RLC_STATUS_PDU_STRUCT status;
    uint32                       i;
    uint16                       vrr  = rb->get_rlc_vrr();
    uint16                       vrmr = rb->get_rlc_vrmr();
    uint16                       vrh  = rb->get_rlc_vrh();

    if(LIBLTE_SUCCESS != liblte_rlc_unpack_amd_pdu(pdu, &amd_pdus) &&
       LIBLTE_RLC_DC_FIELD_CONTROL_PDU != amd_pdus.pdu[0].hdr.dc)
        return interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                         LTE_FDD_ENB_DEBUG_LEVEL_RLC,
                                         __FILE__,
                                         __LINE__,
                                         "Can't unpack AMD PDU");

    if(LIBLTE_RLC_DC_FIELD_CONTROL_PDU == amd_pdus.pdu[0].hdr.dc)
        return handle_status_pdu(pdu, user, rb);

    if(LIBLTE_RLC_RF_FIELD_AMD_PDU_SEGMENT == amd_pdus.pdu[0].hdr.rf)
        return interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                         LTE_FDD_ENB_DEBUG_LEVEL_RLC,
                                         __FILE__,
                                         __LINE__,
                                         &amd_pdus.pdu[0].data,
                                         "Not handling AMD PDU segments");

    for(i=0; i<amd_pdus.N_pdu; i++)
    {
        if(vrr                    <= amd_pdus.pdu[i].hdr.sn &&
           amd_pdus.pdu[i].hdr.sn <  vrmr)
        {
            interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                                      LTE_FDD_ENB_DEBUG_LEVEL_RLC,
                                      __FILE__,
                                      __LINE__,
                                      &amd_pdus.pdu[i].data,
                                      "Received AMD PDU for RNTI=%u, RB=%s, VR(R)=%u, SN=%u, VR(MR)=%u, VR(H)=%u, RF=%s, P=%s, FI=%s",
                                      user->get_c_rnti(),
                                      LTE_fdd_enb_rb_text[rb->get_rb_id()],
                                      vrr,
                                      amd_pdus.pdu[i].hdr.sn,
                                      vrmr,
                                      vrh,
                                      liblte_rlc_rf_field_text[amd_pdus.pdu[i].hdr.rf],
                                      liblte_rlc_p_field_text[amd_pdus.pdu[i].hdr.p],
                                      liblte_rlc_fi_field_text[amd_pdus.pdu[i].hdr.fi]);

            // Place RLC data PDU in reception buffer
            rb->rlc_add_to_am_reception_buffer(&amd_pdus.pdu[i]);

            // Update VR(H)
            if(amd_pdus.pdu[i].hdr.sn >= vrh)
                rb->set_rlc_vrh(amd_pdus.pdu[i].hdr.sn + 1);

            // Update VR(MS)
            // FIXME

            // Update VR(R)/VR(MR) and reassemble
            if(amd_pdus.pdu[i].hdr.sn == vrr)
            {
                rb->update_rlc_vrr();
                // FIXME: Handle AMD PDU Segments

                while(LTE_FDD_ENB_ERROR_NONE == rb->rlc_am_reassemble(&pdcp_pdu))
                    send_pdcp_pdu_ready(user, rb, &pdcp_pdu); // Send the SDU to PDCP
            }

        }else{
            interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                                      LTE_FDD_ENB_DEBUG_LEVEL_RLC,
                                      __FILE__,
                                      __LINE__,
                                      &amd_pdus.pdu[i].data,
                                      "Received AMD PDU for RNTI=%u, RB=%s, that is outside of the receiving window (%u <= %u < %u), P=%s",
                                      user->get_c_rnti(),
                                      LTE_fdd_enb_rb_text[rb->get_rb_id()],
                                      vrr,
                                      amd_pdus.pdu[i].hdr.sn,
                                      vrmr,
                                      liblte_rlc_p_field_text[amd_pdus.pdu[i].hdr.p]);
        }

        if(amd_pdus.pdu[i].hdr.p)
        {
            // Send a STATUS PDU to ACK/NACK SNs
            rb->rlc_get_am_reception_buffer_status(&status);
            send_status_pdu(&status, user, rb);
        }
    }
}
void LTE_fdd_enb_rlc::handle_status_pdu(LIBLTE_BYTE_MSG_STRUCT *pdu,
                                        LTE_fdd_enb_user       *user,
                                        LTE_fdd_enb_rb         *rb)
{
    LIBLTE_RLC_STATUS_PDU_STRUCT status;

    liblte_rlc_unpack_status_pdu(pdu, &status);

    rb->rlc_update_transmission_buffer(&status);

    interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                              LTE_FDD_ENB_DEBUG_LEVEL_RLC,
                              __FILE__,
                              __LINE__,
                              pdu,
                              "Received STATUS PDU");
}

/*******************************/
/*    PDCP Message Handlers    */
/*******************************/
void LTE_fdd_enb_rlc::handle_sdu_ready(LTE_FDD_ENB_RLC_SDU_READY_MSG_STRUCT *sdu_ready)
{
    LIBLTE_BYTE_MSG_STRUCT *sdu;

    if(LTE_FDD_ENB_ERROR_NONE != sdu_ready->rb->get_next_rlc_sdu(&sdu))
        return interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                         LTE_FDD_ENB_DEBUG_LEVEL_RLC,
                                         __FILE__,
                                         __LINE__,
                                         "Received sdu_ready message with no SDU queued");

    interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                              LTE_FDD_ENB_DEBUG_LEVEL_RLC,
                              __FILE__,
                              __LINE__,
                              sdu,
                              "Received SDU for RNTI=%u and RB=%s",
                              sdu_ready->user->get_c_rnti(),
                              LTE_fdd_enb_rb_text[sdu_ready->rb->get_rb_id()]);

    switch(sdu_ready->rb->get_rlc_config())
    {
    case LTE_FDD_ENB_RLC_CONFIG_TM:
        handle_tm_sdu(sdu, sdu_ready->user, sdu_ready->rb);
        break;
    case LTE_FDD_ENB_RLC_CONFIG_UM:
        handle_um_sdu(sdu, sdu_ready->user, sdu_ready->rb);
        break;
    case LTE_FDD_ENB_RLC_CONFIG_AM:
        handle_am_sdu(sdu, sdu_ready->user, sdu_ready->rb);
        break;
    default:
        interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                  LTE_FDD_ENB_DEBUG_LEVEL_RLC,
                                  __FILE__,
                                  __LINE__,
                                  "Received SDU for RNTI=%u, RB=%s, and invalid rlc_config=%s",
                                  sdu_ready->user->get_c_rnti(),
                                  LTE_fdd_enb_rb_text[sdu_ready->rb->get_rb_id()],
                                  LTE_fdd_enb_rlc_config_text[sdu_ready->rb->get_rlc_config()]);
        break;
    }

    // Delete the SDU
    sdu_ready->rb->delete_next_rlc_sdu();
}
void LTE_fdd_enb_rlc::handle_tm_sdu(LIBLTE_BYTE_MSG_STRUCT *sdu,
                                    LTE_fdd_enb_user       *user,
                                    LTE_fdd_enb_rb         *rb)
{
    interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                              LTE_FDD_ENB_DEBUG_LEVEL_RLC,
                              __FILE__,
                              __LINE__,
                              "Sending TMD PDU for RNTI=%u, RB=%s",
                              user->get_c_rnti(),
                              LTE_fdd_enb_rb_text[rb->get_rb_id()]);

    // Send the PDU to MAC
    send_mac_sdu_ready(user, rb, sdu);
}
void LTE_fdd_enb_rlc::handle_um_sdu(LIBLTE_BYTE_MSG_STRUCT *sdu,
                                    LTE_fdd_enb_user       *user,
                                    LTE_fdd_enb_rb         *rb)
{
    LIBLTE_RLC_UMD_PDU_STRUCT umd;
    LIBLTE_BYTE_MSG_STRUCT    pdu;
    uint32                    byte_idx        = 0;
    uint32                    bytes_per_subfn = user->get_max_dl_bytes_per_subfn();
    uint16                    vtus            = rb->get_rlc_vtus();

    if(sdu->N_bytes <= bytes_per_subfn)
    {
        // Pack the PDU
        umd.hdr.fi      = LIBLTE_RLC_FI_FIELD_FULL_SDU;
        umd.hdr.sn      = vtus;
        umd.hdr.sn_size = LIBLTE_RLC_UMD_SN_SIZE_10_BITS;
        umd.N_data      = 1;
        memcpy(&umd.data, sdu, sizeof(LIBLTE_BYTE_MSG_STRUCT));
        rb->set_rlc_vtus(vtus+1);
        liblte_rlc_pack_umd_pdu(&umd, &pdu);

        // Send the PDU to MAC
        send_mac_sdu_ready(user, rb, &pdu);

        return;
    }

    // Segment the message
    while(byte_idx < sdu->N_bytes)
    {
        umd.hdr.fi = LIBLTE_RLC_FI_FIELD_MIDDLE_SDU_SEGMENT;
        umd.hdr.sn = vtus;
        if(byte_idx == 0)
            umd.hdr.fi = LIBLTE_RLC_FI_FIELD_FIRST_SDU_SEGMENT;
        if((sdu->N_bytes - byte_idx) >= bytes_per_subfn)
        {
            memcpy(&umd.data[0].msg[0], &sdu->msg[byte_idx], bytes_per_subfn);
            umd.data[0].N_bytes  = bytes_per_subfn;
            byte_idx            += bytes_per_subfn;
        }else{
            memcpy(&umd.data[0].msg[0], &sdu->msg[byte_idx], sdu->N_bytes - byte_idx);
            umd.data[0].N_bytes = sdu->N_bytes - byte_idx;
            byte_idx            = sdu->N_bytes;
        }
        umd.N_data = 1;
        if(byte_idx == sdu->N_bytes)
            umd.hdr.fi = LIBLTE_RLC_FI_FIELD_LAST_SDU_SEGMENT;
        rb->set_rlc_vtus(vtus+1);
        vtus = rb->get_rlc_vtus();
        liblte_rlc_pack_umd_pdu(&umd, &pdu);

        // Send the PDU to MAC
        send_mac_sdu_ready(user, rb, &pdu);
    }
}
void LTE_fdd_enb_rlc::handle_am_sdu(LIBLTE_BYTE_MSG_STRUCT *sdu,
                                    LTE_fdd_enb_user       *user,
                                    LTE_fdd_enb_rb         *rb)
{
    LIBLTE_RLC_SINGLE_AMD_PDU_STRUCT amd;
    uint32                           byte_idx        = 0;
    uint32                           bytes_per_subfn = user->get_max_dl_bytes_per_subfn();
    uint16                           vts             = rb->get_rlc_vts();

    if(sdu->N_bytes <= bytes_per_subfn)
    {
        amd.hdr.dc = LIBLTE_RLC_DC_FIELD_DATA_PDU;
        amd.hdr.rf = LIBLTE_RLC_RF_FIELD_AMD_PDU;
        amd.hdr.sn = vts;
        amd.hdr.p  = LIBLTE_RLC_P_FIELD_STATUS_REPORT_REQUESTED;
        amd.hdr.fi = LIBLTE_RLC_FI_FIELD_FULL_SDU;
        memcpy(&amd.data, sdu, sizeof(LIBLTE_BYTE_MSG_STRUCT));
        rb->set_rlc_vts(vts+1);

        send_amd_pdu(&amd, user, rb);
        return;
    }

    // Segment the message
    while(byte_idx < sdu->N_bytes)
    {
        amd.hdr.dc = LIBLTE_RLC_DC_FIELD_DATA_PDU;
        amd.hdr.rf = LIBLTE_RLC_RF_FIELD_AMD_PDU;
        amd.hdr.sn = vts;
        amd.hdr.p  = LIBLTE_RLC_P_FIELD_STATUS_REPORT_NOT_REQUESTED;
        amd.hdr.fi = LIBLTE_RLC_FI_FIELD_MIDDLE_SDU_SEGMENT;
        if(byte_idx == 0)
            amd.hdr.fi = LIBLTE_RLC_FI_FIELD_FIRST_SDU_SEGMENT;
        if((sdu->N_bytes - byte_idx) >= bytes_per_subfn)
        {
            memcpy(&amd.data.msg[0], &sdu->msg[byte_idx], bytes_per_subfn);
            amd.data.N_bytes  = bytes_per_subfn;
            byte_idx         += bytes_per_subfn;
        }else{
            memcpy(&amd.data.msg[0], &sdu->msg[byte_idx], sdu->N_bytes - byte_idx);
            amd.data.N_bytes = sdu->N_bytes - byte_idx;
            byte_idx         = sdu->N_bytes;
        }
        if(byte_idx == sdu->N_bytes)
        {
            amd.hdr.fi = LIBLTE_RLC_FI_FIELD_LAST_SDU_SEGMENT;
            amd.hdr.p  = LIBLTE_RLC_P_FIELD_STATUS_REPORT_REQUESTED;
        }
        rb->set_rlc_vts(vts+1);
        vts = rb->get_rlc_vts();

        send_amd_pdu(&amd, user, rb);
    }
}

/******************************/
/*    Message Constructors    */
/******************************/
void LTE_fdd_enb_rlc::send_status_pdu(LIBLTE_RLC_STATUS_PDU_STRUCT *status_pdu,
                                      LTE_fdd_enb_user             *user,
                                      LTE_fdd_enb_rb               *rb)
{
    LIBLTE_BYTE_MSG_STRUCT mac_sdu;

    // Pack the PDU
    liblte_rlc_pack_status_pdu(status_pdu, &mac_sdu);

    interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                              LTE_FDD_ENB_DEBUG_LEVEL_RLC,
                              __FILE__,
                              __LINE__,
                              "Sending STATUS PDU for RNTI=%u, RB=%s",
                              user->get_c_rnti(),
                              LTE_fdd_enb_rb_text[rb->get_rb_id()]);

    // Send the PDU to MAC
    send_mac_sdu_ready(user, rb, &mac_sdu);
}
void LTE_fdd_enb_rlc::send_amd_pdu(LIBLTE_RLC_SINGLE_AMD_PDU_STRUCT *amd,
                                   LTE_fdd_enb_user                 *user,
                                   LTE_fdd_enb_rb                   *rb)
{
    LIBLTE_BYTE_MSG_STRUCT pdu;
    uint16                 vta  = rb->get_rlc_vta();
    uint16                 vtms = rb->get_rlc_vtms();

    // Pack the PDU
    liblte_rlc_pack_amd_pdu(amd, &amd->data, &pdu);

    // Store
    rb->rlc_add_to_transmission_buffer(amd);

    // Start t-pollretransmit
    rb->rlc_start_t_poll_retransmit();

    if(vta         <= amd->hdr.sn &&
       amd->hdr.sn <  vtms)
    {
        interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                                  LTE_FDD_ENB_DEBUG_LEVEL_RLC,
                                  __FILE__,
                                  __LINE__,
                                  "Sending AMD PDU for RNTI=%u, RB=%s, VT(A)=%u, SN=%u, VT(MS)=%u, RF=%s, P=%s, FI=%s",
                                  user->get_c_rnti(),
                                  LTE_fdd_enb_rb_text[rb->get_rb_id()],
                                  vta,
                                  amd->hdr.sn,
                                  vtms,
                                  liblte_rlc_rf_field_text[amd->hdr.rf],
                                  liblte_rlc_p_field_text[amd->hdr.p],
                                  liblte_rlc_fi_field_text[amd->hdr.fi]);

        // Send the PDU to MAC
        send_mac_sdu_ready(user, rb, &pdu);
        return;
    }

    interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                              LTE_FDD_ENB_DEBUG_LEVEL_RLC,
                              __FILE__,
                              __LINE__,
                              &pdu,
                              "Can't send AMD PDU for RNTI=%u, RB=%s, outside of transmit window (%u <= %u < %u)",
                              user->get_c_rnti(),
                              LTE_fdd_enb_rb_text[rb->get_rb_id()],
                              vta,
                              amd->hdr.sn,
                              vtms);
}
