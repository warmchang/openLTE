#line 2 "LTE_fdd_enb_pdcp.cc" // Make __FILE__ omit the path
/*******************************************************************************

    Copyright 2013-2015, 2017, 2021 Ben Wojtowicz

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

    File: LTE_fdd_enb_pdcp.cc

    Description: Contains all the implementations for the LTE FDD eNodeB
                 packet data convergence protocol layer.

    Revision History
    ----------    -------------    --------------------------------------------
    11/10/2013    Ben Wojtowicz    Created file
    01/18/2014    Ben Wojtowicz    Added level to debug prints.
    05/04/2014    Ben Wojtowicz    Added communication to RLC and RRC.
    06/15/2014    Ben Wojtowicz    Added simple header parsing.
    08/03/2014    Ben Wojtowicz    Added transmit functionality.
    11/01/2014    Ben Wojtowicz    Added SRB2 and security support.
    11/29/2014    Ben Wojtowicz    Added communication to IP gateway.
    12/16/2014    Ben Wojtowicz    Added ol extension to message queues.
    02/15/2015    Ben Wojtowicz    Moved to new message queue.
    12/06/2015    Ben Wojtowicz    Changed boost::mutex to pthread_mutex_t and
                                   sem_t.
    07/29/2017    Ben Wojtowicz    Moved away from singleton pattern.
    02/14/2021    Ben Wojtowicz    Massive reformat.

*******************************************************************************/

/*******************************************************************************
                              INCLUDES
*******************************************************************************/

#include "LTE_fdd_enb_pdcp.h"
#include "LTE_fdd_enb_rlc.h"
#include "liblte_pdcp.h"
#include "liblte_security.h"

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
LTE_fdd_enb_pdcp::LTE_fdd_enb_pdcp(LTE_fdd_enb_interface *iface) :
    interface{iface}, started{false}
{
}
LTE_fdd_enb_pdcp::~LTE_fdd_enb_pdcp()
{
    stop();
}

/********************/
/*    Start/Stop    */
/********************/
void LTE_fdd_enb_pdcp::start(LTE_fdd_enb_msgq *from_rlc,
                             LTE_fdd_enb_msgq *from_rrc,
                             LTE_fdd_enb_msgq *from_gw,
                             LTE_fdd_enb_msgq *to_rlc,
                             LTE_fdd_enb_msgq *to_rrc,
                             LTE_fdd_enb_msgq *to_gw)
{
    std::lock_guard<std::mutex> lock(start_mutex);
    LTE_fdd_enb_msgq_cb         rlc_cb(&LTE_fdd_enb_msgq_cb_wrapper<LTE_fdd_enb_pdcp, &LTE_fdd_enb_pdcp::handle_rlc_msg>, this);
    LTE_fdd_enb_msgq_cb         rrc_cb(&LTE_fdd_enb_msgq_cb_wrapper<LTE_fdd_enb_pdcp, &LTE_fdd_enb_pdcp::handle_rrc_msg>, this);
    LTE_fdd_enb_msgq_cb         gw_cb(&LTE_fdd_enb_msgq_cb_wrapper<LTE_fdd_enb_pdcp, &LTE_fdd_enb_pdcp::handle_gw_msg>, this);

    if(started)
        return;

    started       = true;
    msgq_from_rlc = from_rlc;
    msgq_from_rrc = from_rrc;
    msgq_from_gw  = from_gw;
    msgq_to_rlc   = to_rlc;
    msgq_to_rrc   = to_rrc;
    msgq_to_gw    = to_gw;
    msgq_from_rlc->attach_rx(rlc_cb);
    msgq_from_rrc->attach_rx(rrc_cb);
    msgq_from_gw->attach_rx(gw_cb);
}
void LTE_fdd_enb_pdcp::stop()
{
    std::lock_guard<std::mutex> lock(start_mutex);

    if(started)
        started = false;
}

/***********************/
/*    Communication    */
/***********************/
void LTE_fdd_enb_pdcp::handle_rlc_msg(LTE_FDD_ENB_MESSAGE_STRUCT &msg)
{
    if(LTE_FDD_ENB_DEST_LAYER_PDCP != msg.dest_layer &&
       LTE_FDD_ENB_DEST_LAYER_ANY  != msg.dest_layer)
        return msgq_to_rrc->send(msg); // Forward message to RRC

    if(msg.type == LTE_FDD_ENB_MESSAGE_TYPE_PDCP_PDU_READY)
        return handle_pdu_ready(&msg.msg.pdcp_pdu_ready);

    interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                              LTE_FDD_ENB_DEBUG_LEVEL_PDCP,
                              __FILE__,
                              __LINE__,
                              "Received invalid RLC message %s",
                              LTE_fdd_enb_message_type_text[msg.type]);
}
void LTE_fdd_enb_pdcp::handle_rrc_msg(LTE_FDD_ENB_MESSAGE_STRUCT &msg)
{
    if(LTE_FDD_ENB_DEST_LAYER_PDCP != msg.dest_layer &&
       LTE_FDD_ENB_DEST_LAYER_ANY  != msg.dest_layer)
        return msgq_to_rlc->send(msg); // Forward message to RLC

    if(msg.type == LTE_FDD_ENB_MESSAGE_TYPE_PDCP_SDU_READY)
        return handle_sdu_ready(&msg.msg.pdcp_sdu_ready);

    interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                              LTE_FDD_ENB_DEBUG_LEVEL_PDCP,
                              __FILE__,
                              __LINE__,
                              "Received invalid RRC message %s",
                              LTE_fdd_enb_message_type_text[msg.type]);
}
void LTE_fdd_enb_pdcp::handle_gw_msg(LTE_FDD_ENB_MESSAGE_STRUCT &msg)
{
    if(LTE_FDD_ENB_DEST_LAYER_PDCP != msg.dest_layer &&
       LTE_FDD_ENB_DEST_LAYER_ANY  != msg.dest_layer)
        return interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                         LTE_FDD_ENB_DEBUG_LEVEL_PDCP,
                                         __FILE__,
                                         __LINE__,
                                         "Received GW message for invalid layer %s",
                                         LTE_fdd_enb_dest_layer_text[msg.dest_layer]);

    if(msg.type == LTE_FDD_ENB_MESSAGE_TYPE_PDCP_DATA_SDU_READY)
        return handle_data_sdu_ready(&msg.msg.pdcp_data_sdu_ready);

    interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                              LTE_FDD_ENB_DEBUG_LEVEL_PDCP,
                              __FILE__,
                              __LINE__,
                              "Received invalid GW message %s",
                              LTE_fdd_enb_message_type_text[msg.type]);
}
void LTE_fdd_enb_pdcp::send_rlc_sdu_ready(LTE_fdd_enb_user       *user,
                                          LTE_fdd_enb_rb         *rb,
                                          LIBLTE_BYTE_MSG_STRUCT *sdu)
{
    LTE_FDD_ENB_RLC_SDU_READY_MSG_STRUCT sdu_ready;

    rb->queue_rlc_sdu(sdu);

    interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                              LTE_FDD_ENB_DEBUG_LEVEL_PDCP,
                              __FILE__,
                              __LINE__,
                              sdu,
                              "Sending PDU to RLC for RNTI=%u and RB=%s",
                              user->get_c_rnti(),
                              LTE_fdd_enb_rb_text[rb->get_rb_id()]);

    sdu_ready.user = user;
    sdu_ready.rb   = rb;
    msgq_to_rlc->send(LTE_FDD_ENB_MESSAGE_TYPE_RLC_SDU_READY,
                      LTE_FDD_ENB_DEST_LAYER_RLC,
                      (LTE_FDD_ENB_MESSAGE_UNION *)&sdu_ready,
                      sizeof(sdu_ready));
}
void LTE_fdd_enb_pdcp::send_rrc_pdu_ready(LTE_fdd_enb_user      *user,
                                          LTE_fdd_enb_rb        *rb,
                                          LIBLTE_BIT_MSG_STRUCT *pdu)
{
    LTE_FDD_ENB_RRC_PDU_READY_MSG_STRUCT pdu_ready;

    rb->queue_rrc_pdu(pdu);

    interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                              LTE_FDD_ENB_DEBUG_LEVEL_PDCP,
                              __FILE__,
                              __LINE__,
                              pdu,
                              "Sending SDU to RRC for RNTI=%u and RB=%s",
                              user->get_c_rnti(),
                              LTE_fdd_enb_rb_text[rb->get_rb_id()]);

    pdu_ready.user = user;
    pdu_ready.rb   = rb;
    msgq_to_rrc->send(LTE_FDD_ENB_MESSAGE_TYPE_RRC_PDU_READY,
                      LTE_FDD_ENB_DEST_LAYER_RRC,
                      (LTE_FDD_ENB_MESSAGE_UNION *)&pdu_ready,
                      sizeof(pdu_ready));
}

/****************************/
/*    External Interface    */
/****************************/
void LTE_fdd_enb_pdcp::update_sys_info()
{
    std::lock_guard<std::mutex>  lock(sys_info_mutex);
    interface->get_sys_info(sys_info);
}

/******************************/
/*    RLC Message Handlers    */
/******************************/
void LTE_fdd_enb_pdcp::handle_pdu_ready(LTE_FDD_ENB_PDCP_PDU_READY_MSG_STRUCT *pdu_ready)
{
    LTE_FDD_ENB_GW_DATA_READY_MSG_STRUCT      gw_data_ready;
    LIBLTE_PDCP_CONTROL_PDU_STRUCT            contents;
    LIBLTE_PDCP_DATA_PDU_WITH_LONG_SN_STRUCT  data_contents;
    LIBLTE_BYTE_MSG_STRUCT                   *pdu;
    LIBLTE_BIT_MSG_STRUCT                     rrc_pdu;
    uint8                                    *pdu_ptr;
    uint32                                    i;

    if(LTE_FDD_ENB_ERROR_NONE != pdu_ready->rb->get_next_pdcp_pdu(&pdu))
        return;

    interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                              LTE_FDD_ENB_DEBUG_LEVEL_PDCP,
                              __FILE__,
                              __LINE__,
                              pdu,
                              "Received PDU for RNTI=%u and RB=%s",
                              pdu_ready->user->get_c_rnti(),
                              LTE_fdd_enb_rb_text[pdu_ready->rb->get_rb_id()]);

    // FIXME: Add SN and integrity verification

    if(LTE_FDD_ENB_RB_SRB0 == pdu_ready->rb->get_rb_id())
    {
        // Convert to bit struct for RRC
        pdu_ptr = rrc_pdu.msg;
        for(i=0; i<pdu->N_bytes; i++)
            liblte_value_2_bits(pdu->msg[i], &pdu_ptr, 8);
        rrc_pdu.N_bits = pdu->N_bytes * 8;

        // Send the SDU to RRC
        send_rrc_pdu_ready(pdu_ready->user, pdu_ready->rb, &rrc_pdu);
    }else if(LTE_FDD_ENB_RB_SRB1 == pdu_ready->rb->get_rb_id() ||
             LTE_FDD_ENB_RB_SRB2 == pdu_ready->rb->get_rb_id()){
        liblte_pdcp_unpack_control_pdu(pdu, &contents);

        // Send the SDU to RRC
        send_rrc_pdu_ready(pdu_ready->user, pdu_ready->rb, &contents.data);
    }else if(LTE_FDD_ENB_RB_DRB1 == pdu_ready->rb->get_rb_id()){
        liblte_pdcp_unpack_data_pdu_with_long_sn(pdu, &data_contents);

        // Queue the SDU for GW
        pdu_ready->rb->queue_gw_data_msg(&data_contents.data);

        // Signal GW
        gw_data_ready.user = pdu_ready->user;
        gw_data_ready.rb   = pdu_ready->rb;
        msgq_to_gw->send(LTE_FDD_ENB_MESSAGE_TYPE_GW_DATA_READY,
                         LTE_FDD_ENB_DEST_LAYER_GW,
                         (LTE_FDD_ENB_MESSAGE_UNION *)&gw_data_ready,
                         sizeof(LTE_FDD_ENB_GW_DATA_READY_MSG_STRUCT));
    }else{
        interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                  LTE_FDD_ENB_DEBUG_LEVEL_PDCP,
                                  __FILE__,
                                  __LINE__,
                                  pdu,
                                  "Received PDU for RNTI=%u with invalid RB=%s",
                                  pdu_ready->user->get_c_rnti(),
                                  LTE_fdd_enb_rb_text[pdu_ready->rb->get_rb_id()]);
    }

    // Delete the PDU
    pdu_ready->rb->delete_next_pdcp_pdu();
}

/******************************/
/*    RRC Message Handlers    */
/******************************/
void LTE_fdd_enb_pdcp::handle_sdu_ready(LTE_FDD_ENB_PDCP_SDU_READY_MSG_STRUCT *sdu_ready)
{
    LIBLTE_PDCP_CONTROL_PDU_STRUCT  contents;
    LIBLTE_BYTE_MSG_STRUCT          pdu;
    LIBLTE_BIT_MSG_STRUCT          *sdu;
    uint8                          *sdu_ptr;
    uint32                          i;

    if(LTE_FDD_ENB_ERROR_NONE != sdu_ready->rb->get_next_pdcp_sdu(&sdu))
    {
        interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                  LTE_FDD_ENB_DEBUG_LEVEL_PDCP,
                                  __FILE__,
                                  __LINE__,
                                  "Received SDU ready with no data, RNTI=%u, RB=%s",
                                  sdu_ready->user->get_c_rnti(),
                                  LTE_fdd_enb_rb_text[sdu_ready->rb->get_rb_id()]);
        return;
    }

    interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                              LTE_FDD_ENB_DEBUG_LEVEL_PDCP,
                              __FILE__,
                              __LINE__,
                              sdu,
                              "Received SDU for RNTI=%u and RB=%s",
                              sdu_ready->user->get_c_rnti(),
                              LTE_fdd_enb_rb_text[sdu_ready->rb->get_rb_id()]);

    if(LTE_FDD_ENB_RB_SRB0 == sdu_ready->rb->get_rb_id())
    {
        // Make sure the SDU is byte aligned
        if((sdu->N_bits % 8) != 0)
            while((sdu->N_bits % 8) != 0)
                sdu->msg[sdu->N_bits++] = 0;

        // Convert from bit to byte struct
        sdu_ptr = sdu->msg;
        for(i=0; i<sdu->N_bits/8; i++)
            pdu.msg[i] = liblte_bits_2_value(&sdu_ptr, 8);
        pdu.N_bytes = sdu->N_bits/8;

        send_rlc_sdu_ready(sdu_ready->user, sdu_ready->rb, &pdu);
    }else if(LTE_FDD_ENB_RB_SRB1 == sdu_ready->rb->get_rb_id() ||
             LTE_FDD_ENB_RB_SRB2 == sdu_ready->rb->get_rb_id()){
        // Pack the control PDU
        contents.count = sdu_ready->rb->get_pdcp_tx_count();
        if(LTE_FDD_ENB_PDCP_CONFIG_SECURITY == sdu_ready->rb->get_pdcp_config())
        {
            liblte_pdcp_pack_control_pdu(&contents,
                                         sdu,
                                         sdu_ready->user->get_auth_vec()->k_rrc_int,
                                         LIBLTE_SECURITY_DIRECTION_DOWNLINK,
                                         sdu_ready->rb->get_rb_id()-1,
                                         &pdu);
        }else{
            liblte_pdcp_pack_control_pdu(&contents,
                                         sdu,
                                         &pdu);
        }

        // Increment the SN
        sdu_ready->rb->set_pdcp_tx_count(contents.count + 1);

        send_rlc_sdu_ready(sdu_ready->user, sdu_ready->rb, &pdu);
    }else{
        interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                  LTE_FDD_ENB_DEBUG_LEVEL_PDCP,
                                  __FILE__,
                                  __LINE__,
                                  sdu,
                                  "Received SDU for RNTI=%u with invalid RB=%s",
                                  sdu_ready->user->get_c_rnti(),
                                  LTE_fdd_enb_rb_text[sdu_ready->rb->get_rb_id()]);
    }

    // Delete the SDU
    sdu_ready->rb->delete_next_pdcp_sdu();
}

/*****************************/
/*    GW Message Handlers    */
/*****************************/
void LTE_fdd_enb_pdcp::handle_data_sdu_ready(LTE_FDD_ENB_PDCP_DATA_SDU_READY_MSG_STRUCT *data_sdu_ready)
{
    LIBLTE_PDCP_DATA_PDU_WITH_LONG_SN_STRUCT  contents;
    LIBLTE_BYTE_MSG_STRUCT                    pdu;
    LIBLTE_BYTE_MSG_STRUCT                   *sdu;

    if(LTE_FDD_ENB_ERROR_NONE != data_sdu_ready->rb->get_next_pdcp_data_sdu(&sdu))
    {
        interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                  LTE_FDD_ENB_DEBUG_LEVEL_PDCP,
                                  __FILE__,
                                  __LINE__,
                                  "Received data SDU ready from GW with no data, RNTI=%u, RB=%s",
                                  data_sdu_ready->user->get_c_rnti(),
                                  LTE_fdd_enb_rb_text[data_sdu_ready->rb->get_rb_id()]);
        return;
    }

    interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                              LTE_FDD_ENB_DEBUG_LEVEL_PDCP,
                              __FILE__,
                              __LINE__,
                              sdu,
                              "Received data SDU from GW for RNTI=%u and RB=%s",
                              data_sdu_ready->user->get_c_rnti(),
                              LTE_fdd_enb_rb_text[data_sdu_ready->rb->get_rb_id()]);

    if(data_sdu_ready->rb->get_rb_id()       >= LTE_FDD_ENB_RB_DRB1 &&
       data_sdu_ready->rb->get_pdcp_config() == LTE_FDD_ENB_PDCP_CONFIG_LONG_SN)
    {
        // Pack the data PDU
        contents.count = data_sdu_ready->rb->get_pdcp_tx_count();
        liblte_pdcp_pack_data_pdu_with_long_sn(&contents, sdu, &pdu);

        // Increment the SN
        data_sdu_ready->rb->set_pdcp_tx_count(contents.count + 1);

        send_rlc_sdu_ready(data_sdu_ready->user, data_sdu_ready->rb, &pdu);
    }else{
        interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                  LTE_FDD_ENB_DEBUG_LEVEL_PDCP,
                                  __FILE__,
                                  __LINE__,
                                  "Received data SDU from GW for invalid RB=%s, RNTI=%u",
                                  LTE_fdd_enb_rb_text[data_sdu_ready->rb->get_rb_id()],
                                  data_sdu_ready->user->get_c_rnti());
    }

    // Delete the SDU
    data_sdu_ready->rb->delete_next_pdcp_data_sdu();
}
