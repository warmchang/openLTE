#line 2 "LTE_fdd_enb_rrc.cc" // Make __FILE__ omit the path
/*******************************************************************************

    Copyright 2013-2017, 2021 Ben Wojtowicz
    Copyright 2016 Przemek Bereski (UE capability information and UE capability
                                    enquiry support)

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

    File: LTE_fdd_enb_rrc.cc

    Description: Contains all the implementations for the LTE FDD eNodeB
                 radio resource control layer.

    Revision History
    ----------    -------------    --------------------------------------------
    11/10/2013    Ben Wojtowicz    Created file
    01/18/2014    Ben Wojtowicz    Added level to debug prints.
    05/04/2014    Ben Wojtowicz    Added PDCP communication and UL CCCH state
                                   machine.
    06/15/2014    Ben Wojtowicz    Added UL DCCH message handling and MME NAS
                                   message handling.
    08/03/2014    Ben Wojtowicz    Added downlink NAS message handling and
                                   connection release.
    11/01/2014    Ben Wojtowicz    Added RRC connection reconfiguration and
                                   security mode command messages.
    11/29/2014    Ben Wojtowicz    Added DRB1 and DRB2 support and user
                                   recovery on RRC connection request.
    12/16/2014    Ben Wojtowicz    Added ol extension to message queues.
    12/24/2014    Ben Wojtowicz    Using default data QoS and copying SRB1
                                   PDCP config to SRB2.
    02/15/2015    Ben Wojtowicz    Moved to new message queue and using the
                                   fixed user switch.
    07/25/2015    Ben Wojtowicz    Using the new user QoS structure, moved DRBs
                                   to RLC AM, and changed the default time
                                   alignment timer to 10240 subframes.
    12/06/2015    Ben Wojtowicz    Changed boost::mutex to pthread_mutex_t and
                                   sem_t.
    02/13/2016    Ben Wojtowicz    Added RRC connection reestablishment state
                                   machine.
    07/03/2016    Przemek Bereski  Added UE capability information and UE
                                   capability enquiry support.
    07/29/2017    Ben Wojtowicz    Add SR support, populate physical layer
                                   dedicated configurations, remove QOS and
                                   fixed UL scheduling.
    02/14/2021    Ben Wojtowicz    Massive reformat and using the new RRC
                                   library.

*******************************************************************************/

/*******************************************************************************
                              INCLUDES
*******************************************************************************/

#include "LTE_fdd_enb_rrc.h"
#include "LTE_fdd_enb_pdcp.h"
#include "LTE_fdd_enb_mac.h"
#include "LTE_fdd_enb_user_mgr.h"

/*******************************************************************************
                              DEFINES
*******************************************************************************/

// SR configuration
#define I_SR_MIN       15
#define I_SR_MAX       34
#define N_1_P_PUCCH_SR 1

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
LTE_fdd_enb_rrc::LTE_fdd_enb_rrc(LTE_fdd_enb_interface *iface, LTE_fdd_enb_user_mgr *um,
                                 LTE_fdd_enb_mac *_mac) :
    interface{iface}, started{false}, user_mgr{um}, mac{_mac}
{
}
LTE_fdd_enb_rrc::~LTE_fdd_enb_rrc()
{
    stop();
}

/********************/
/*    Start/Stop    */
/********************/
void LTE_fdd_enb_rrc::start(LTE_fdd_enb_msgq *from_pdcp,
                            LTE_fdd_enb_msgq *from_mme,
                            LTE_fdd_enb_msgq *to_pdcp,
                            LTE_fdd_enb_msgq *to_mme)
{
    std::lock_guard<std::mutex> lock(start_mutex);
    LTE_fdd_enb_msgq_cb         pdcp_cb(&LTE_fdd_enb_msgq_cb_wrapper<LTE_fdd_enb_rrc, &LTE_fdd_enb_rrc::handle_pdcp_msg>, this);
    LTE_fdd_enb_msgq_cb         mme_cb(&LTE_fdd_enb_msgq_cb_wrapper<LTE_fdd_enb_rrc, &LTE_fdd_enb_rrc::handle_mme_msg>, this);

    if(started)
        return;

    started        = true;
    i_sr           = I_SR_MIN;
    msgq_from_pdcp = from_pdcp;
    msgq_from_mme  = from_mme;
    msgq_to_pdcp   = to_pdcp;
    msgq_to_mme    = to_mme;
    msgq_from_pdcp->attach_rx(pdcp_cb);
    msgq_from_mme->attach_rx(mme_cb);
}
void LTE_fdd_enb_rrc::stop()
{
    std::lock_guard<std::mutex> lock(start_mutex);

    if(started)
        started = false;
}

/***********************/
/*    Communication    */
/***********************/
void LTE_fdd_enb_rrc::handle_pdcp_msg(LTE_FDD_ENB_MESSAGE_STRUCT &msg)
{
    if(LTE_FDD_ENB_DEST_LAYER_RRC != msg.dest_layer &&
       LTE_FDD_ENB_DEST_LAYER_ANY != msg.dest_layer)
        return msgq_to_mme->send(msg); // Forward message to MME

    if(msg.type == LTE_FDD_ENB_MESSAGE_TYPE_RRC_PDU_READY)
        return handle_pdu_ready(&msg.msg.rrc_pdu_ready);

    interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                              LTE_FDD_ENB_DEBUG_LEVEL_RRC,
                              __FILE__,
                              __LINE__,
                              "Received invalid PDCP message %s",
                              LTE_fdd_enb_message_type_text[msg.type]);
}
void LTE_fdd_enb_rrc::handle_mme_msg(LTE_FDD_ENB_MESSAGE_STRUCT &msg)
{
    if(LTE_FDD_ENB_DEST_LAYER_RRC != msg.dest_layer &&
       LTE_FDD_ENB_DEST_LAYER_ANY != msg.dest_layer)
        return msgq_to_pdcp->send(msg); // Forward message to PDCP

    switch(msg.type)
    {
    case LTE_FDD_ENB_MESSAGE_TYPE_RRC_NAS_MSG_READY:
        handle_nas_msg(&msg.msg.rrc_nas_msg_ready);
        break;
    case LTE_FDD_ENB_MESSAGE_TYPE_RRC_CMD_READY:
        handle_cmd(&msg.msg.rrc_cmd_ready);
        break;
    default:
        interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                  LTE_FDD_ENB_DEBUG_LEVEL_RRC,
                                  __FILE__,
                                  __LINE__,
                                  "Received invalid MME message %s",
                                  LTE_fdd_enb_message_type_text[msg.type]);
        break;
    }
}
void LTE_fdd_enb_rrc::send_pdcp_sdu_ready(LTE_fdd_enb_user     *user,
                                          LTE_fdd_enb_rb       *rb,
                                          std::vector<uint8_t> &sdu)
{
    LTE_FDD_ENB_PDCP_SDU_READY_MSG_STRUCT sdu_ready;

    rb->queue_pdcp_sdu(sdu);

    interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                              LTE_FDD_ENB_DEBUG_LEVEL_RRC,
                              __FILE__,
                              __LINE__,
                              sdu,
                              "Sending PDU to PDCP for RNTI=%u and RB=%s",
                              user->get_c_rnti(),
                              LTE_fdd_enb_rb_text[rb->get_rb_id()]);

    sdu_ready.user = user;
    sdu_ready.rb   = rb;
    msgq_to_pdcp->send(LTE_FDD_ENB_MESSAGE_TYPE_PDCP_SDU_READY,
                       LTE_FDD_ENB_DEST_LAYER_PDCP,
                       (LTE_FDD_ENB_MESSAGE_UNION *)&sdu_ready,
                       sizeof(sdu_ready));
}
void LTE_fdd_enb_rrc::send_mme_nas_msg_ready(LTE_fdd_enb_user           *user,
                                             LTE_fdd_enb_rb             *rb,
                                             const std::vector<uint8_t> &nas_msg)
{
    LTE_FDD_ENB_MME_NAS_MSG_READY_MSG_STRUCT nas_msg_ready;

    rb->queue_mme_nas_msg(nas_msg);

    interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                              LTE_FDD_ENB_DEBUG_LEVEL_RRC,
                              __FILE__,
                              __LINE__,
                              nas_msg,
                              "Sending NAS MSG to MME for RNTI=%u and RB=%s",
                              user->get_c_rnti(),
                              LTE_fdd_enb_rb_text[rb->get_rb_id()]);

    nas_msg_ready.user = user;
    nas_msg_ready.rb   = rb;
    msgq_to_mme->send(LTE_FDD_ENB_MESSAGE_TYPE_MME_NAS_MSG_READY,
                      LTE_FDD_ENB_DEST_LAYER_MME,
                      (LTE_FDD_ENB_MESSAGE_UNION *)&nas_msg_ready,
                      sizeof(nas_msg_ready));
}

/****************************/
/*    External Interface    */
/****************************/
void LTE_fdd_enb_rrc::update_sys_info()
{
    std::lock_guard<std::mutex>  lock(sys_info_mutex);
    interface->get_sys_info(sys_info);
}

/*******************************/
/*    PDCP Message Handlers    */
/*******************************/
void LTE_fdd_enb_rrc::handle_pdu_ready(LTE_FDD_ENB_RRC_PDU_READY_MSG_STRUCT *pdu_ready)
{
    LIBLTE_BIT_MSG_STRUCT *pdu;

    if(LTE_FDD_ENB_ERROR_NONE != pdu_ready->rb->get_next_rrc_pdu(&pdu))
        return interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                         LTE_FDD_ENB_DEBUG_LEVEL_RRC,
                                         __FILE__,
                                         __LINE__,
                                         "Received pdu_ready message with no PDU queued");
    liblte_full_stack_message fsm;
    for(uint32 i=0; i<pdu->N_bits; i++)
        fsm.rrc.push_back(pdu->msg[i]);

    interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                              LTE_FDD_ENB_DEBUG_LEVEL_RRC,
                              __FILE__,
                              __LINE__,
                              fsm.rrc,
                              "Received PDU for RNTI=%u and RB=%s",
                              pdu_ready->user->get_c_rnti(),
                              LTE_fdd_enb_rb_text[pdu_ready->rb->get_rb_id()]);

    // Call the appropriate state machine
    switch(pdu_ready->rb->get_rb_id())
    {
    case LTE_FDD_ENB_RB_SRB0:
        ccch_sm(fsm.rrc, pdu_ready->user, pdu_ready->rb);
        break;
    case LTE_FDD_ENB_RB_SRB1:
    case LTE_FDD_ENB_RB_SRB2:
        dcch_sm(fsm.rrc, pdu_ready->user, pdu_ready->rb);
        break;
    default:
        interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                  LTE_FDD_ENB_DEBUG_LEVEL_RRC,
                                  __FILE__,
                                  __LINE__,
                                  fsm.rrc,
                                  "Received PDU for RNTI=%u and invalid RB=%s",
                                  pdu_ready->user->get_c_rnti(),
                                  LTE_fdd_enb_rb_text[pdu_ready->rb->get_rb_id()]);
        break;
    }

    // Delete the PDU
    pdu_ready->rb->delete_next_rrc_pdu();
}

/******************************/
/*    MME Message Handlers    */
/******************************/
void LTE_fdd_enb_rrc::handle_nas_msg(LTE_FDD_ENB_RRC_NAS_MSG_READY_MSG_STRUCT *nas_msg)
{
    LIBLTE_BYTE_MSG_STRUCT *msg;

    if(LTE_FDD_ENB_ERROR_NONE != nas_msg->rb->get_next_rrc_nas_msg(&msg))
        return interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                         LTE_FDD_ENB_DEBUG_LEVEL_RRC,
                                         __FILE__,
                                         __LINE__,
                                         "Received NAS message with no message queued");

    interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                              LTE_FDD_ENB_DEBUG_LEVEL_RRC,
                              __FILE__,
                              __LINE__,
                              msg,
                              "Received NAS message for RNTI=%u and RB=%s",
                              nas_msg->user->get_c_rnti(),
                              LTE_fdd_enb_rb_text[nas_msg->rb->get_rb_id()]);

    // Send the NAS message
    send_dl_info_transfer(nas_msg->user, nas_msg->rb, msg);

    // Delete the NAS message
    nas_msg->rb->delete_next_rrc_nas_msg();
}
void LTE_fdd_enb_rrc::handle_cmd(LTE_FDD_ENB_RRC_CMD_READY_MSG_STRUCT *cmd)
{
    LIBLTE_BYTE_MSG_STRUCT *msg;
    LTE_fdd_enb_rb         *srb2 = NULL;
    LTE_fdd_enb_rb         *drb1 = NULL;
    LTE_fdd_enb_rb         *drb2 = NULL;

    interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                              LTE_FDD_ENB_DEBUG_LEVEL_RRC,
                              __FILE__,
                              __LINE__,
                              "Received MME command %s for RNTI=%u and RB=%s",
                              LTE_fdd_enb_rrc_cmd_text[cmd->cmd],
                              cmd->user->get_c_rnti(),
                              LTE_fdd_enb_rb_text[cmd->rb->get_rb_id()]);

    switch(cmd->cmd)
    {
    case LTE_FDD_ENB_RRC_CMD_RELEASE:
        send_rrc_con_release(cmd->user, cmd->rb);
        break;
    case LTE_FDD_ENB_RRC_CMD_SECURITY:
        send_ue_capability_enquiry(cmd->user, cmd->rb);
        send_security_mode_command(cmd->user, cmd->rb);
        break;
    case LTE_FDD_ENB_RRC_CMD_SETUP_DEF_DRB:
        if(LTE_FDD_ENB_ERROR_NONE != cmd->user->setup_srb2(&srb2) ||
           LTE_FDD_ENB_ERROR_NONE != cmd->user->setup_drb(LTE_FDD_ENB_RB_DRB1, &drb1))
        {
            interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                      LTE_FDD_ENB_DEBUG_LEVEL_RRC,
                                      __FILE__,
                                      __LINE__,
                                      "Handle CMD can't setup default DRB");
            break;
        }

        // Configure SRB2
        srb2->set_rrc_procedure(cmd->rb->get_rrc_procedure());
        srb2->set_rrc_state(cmd->rb->get_rrc_state());
        srb2->set_mme_procedure(cmd->rb->get_mme_procedure());
        srb2->set_mme_state(cmd->rb->get_mme_state());
        srb2->set_pdcp_config(cmd->rb->get_pdcp_config());

        // Configure DRB1
        drb1->set_eps_bearer_id(cmd->user->get_eps_bearer_id());
        drb1->set_drb_id(1);
        drb1->set_lc_id(3);
        drb1->set_log_chan_group(2);

        if(LTE_FDD_ENB_ERROR_NONE == cmd->rb->get_next_rrc_nas_msg(&msg))
        {
            send_rrc_con_reconfig(cmd->user, cmd->rb, msg);
            cmd->rb->delete_next_rrc_nas_msg();
        }else{
            send_rrc_con_reconfig(cmd->user, cmd->rb, NULL);
        }
        break;
    case LTE_FDD_ENB_RRC_CMD_SETUP_DED_DRB:
        if(LTE_FDD_ENB_ERROR_NONE != cmd->user->setup_srb2(&srb2)                     ||
           LTE_FDD_ENB_ERROR_NONE != cmd->user->setup_drb(LTE_FDD_ENB_RB_DRB1, &drb1) ||
           LTE_FDD_ENB_ERROR_NONE != cmd->user->setup_drb(LTE_FDD_ENB_RB_DRB2, &drb2))
        {
            interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                      LTE_FDD_ENB_DEBUG_LEVEL_RRC,
                                      __FILE__,
                                      __LINE__,
                                      "Handle CMD can't setup dedicated DRB");
            break;
        }

        // Configure SRB2
        srb2->set_rrc_procedure(cmd->rb->get_rrc_procedure());
        srb2->set_rrc_state(cmd->rb->get_rrc_state());
        srb2->set_mme_procedure(cmd->rb->get_mme_procedure());
        srb2->set_mme_state(cmd->rb->get_mme_state());
        srb2->set_pdcp_config(cmd->rb->get_pdcp_config());

        // Configure DRB1
        drb1->set_eps_bearer_id(cmd->user->get_eps_bearer_id());
        drb1->set_drb_id(1);
        drb1->set_lc_id(3);
        drb1->set_log_chan_group(2);

        // Configure DRB2
        drb2->set_eps_bearer_id(cmd->user->get_eps_bearer_id()+1);
        drb2->set_drb_id(2);
        drb2->set_lc_id(4);
        drb2->set_log_chan_group(3);

        if(LTE_FDD_ENB_ERROR_NONE == cmd->rb->get_next_rrc_nas_msg(&msg))
        {
            send_rrc_con_reconfig(cmd->user, cmd->rb, msg);
            cmd->rb->delete_next_rrc_nas_msg();
        }else{
            send_rrc_con_reconfig(cmd->user, cmd->rb, NULL);
        }
        break;
    default:
        interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                  LTE_FDD_ENB_DEBUG_LEVEL_RRC,
                                  __FILE__,
                                  __LINE__,
                                  "Received MME command %s for RNTI=%u and RB=%s",
                                  LTE_fdd_enb_rrc_cmd_text[cmd->cmd],
                                  cmd->user->get_c_rnti(),
                                  LTE_fdd_enb_rb_text[cmd->rb->get_rb_id()]);
        break;
    }
}

/************************/
/*    State Machines    */
/************************/
void LTE_fdd_enb_rrc::ccch_sm(std::vector<uint8_t> &msg,
                              LTE_fdd_enb_user     *user,
                              LTE_fdd_enb_rb       *rb)
{
    LTE_fdd_enb_user *loc_user = user;
    LTE_fdd_enb_rb   *loc_rb   = rb;
    LTE_fdd_enb_rb   *srb1     = NULL;

    // Parse the message
    parse_ul_ccch_message(msg, &loc_user, &loc_rb);

    switch(loc_rb->get_rrc_procedure())
    {
    case LTE_FDD_ENB_RRC_PROC_RRC_CON_REQ:
        switch(loc_rb->get_rrc_state())
        {
        case LTE_FDD_ENB_RRC_STATE_IDLE:
            loc_user->setup_srb1(&srb1);
            if(NULL != srb1)
            {
                loc_rb->set_rrc_state(LTE_FDD_ENB_RRC_STATE_SRB1_SETUP);
                send_rrc_con_setup(loc_user, loc_rb);
                srb1->set_rrc_procedure(LTE_FDD_ENB_RRC_PROC_RRC_CON_REQ);
                srb1->set_rrc_state(LTE_FDD_ENB_RRC_STATE_WAIT_FOR_CON_SETUP_COMPLETE);
            }else{
                interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                          LTE_FDD_ENB_DEBUG_LEVEL_RRC,
                                          __FILE__,
                                          __LINE__,
                                          "UL-CCCH-Message can't setup srb1");
            }
            break;
        default:
            interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                      LTE_FDD_ENB_DEBUG_LEVEL_RRC,
                                      __FILE__,
                                      __LINE__,
                                      "UL-CCCH-Message RRC CON REQ state machine invalid state %s",
                                      LTE_fdd_enb_rrc_state_text[loc_rb->get_rrc_state()]);
            break;
        }
        break;
    case LTE_FDD_ENB_RRC_PROC_RRC_CON_REEST_REQ:
        switch(loc_rb->get_rrc_state())
        {
        case LTE_FDD_ENB_RRC_STATE_IDLE:
            loc_user->setup_srb1(&srb1);
            if(NULL != srb1)
            {
                loc_rb->set_rrc_state(LTE_FDD_ENB_RRC_STATE_SRB1_SETUP);
                send_rrc_con_reest(loc_user, loc_rb);
                srb1->set_rrc_procedure(LTE_FDD_ENB_RRC_PROC_RRC_CON_REEST_REQ);
                srb1->set_rrc_state(LTE_FDD_ENB_RRC_STATE_WAIT_FOR_CON_REEST_COMPLETE);
            }else{
                send_rrc_con_reest_reject(loc_user, loc_rb);
            }
            break;
        default:
            interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                      LTE_FDD_ENB_DEBUG_LEVEL_RRC,
                                      __FILE__,
                                      __LINE__,
                                      "UL-CCCH-Message RRC CON REEST REQ state machine invalid state %s",
                                      LTE_fdd_enb_rrc_state_text[loc_rb->get_rrc_state()]);
            break;
        }
        break;
    default:
        interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                  LTE_FDD_ENB_DEBUG_LEVEL_RRC,
                                  __FILE__,
                                  __LINE__,
                                  "CCCH state machine invalid procedure %s",
                                  LTE_fdd_enb_rrc_proc_text[loc_rb->get_rrc_procedure()]);
        break;
    }
}
void LTE_fdd_enb_rrc::dcch_sm(std::vector<uint8_t> &msg,
                              LTE_fdd_enb_user     *user,
                              LTE_fdd_enb_rb       *rb)
{
    switch(rb->get_rrc_procedure())
    {
    case LTE_FDD_ENB_RRC_PROC_RRC_CON_REEST_REQ:
    case LTE_FDD_ENB_RRC_PROC_RRC_CON_REQ:
        switch(rb->get_rrc_state())
        {
        case LTE_FDD_ENB_RRC_STATE_WAIT_FOR_CON_SETUP_COMPLETE:
        case LTE_FDD_ENB_RRC_STATE_WAIT_FOR_CON_REEST_COMPLETE:
        case LTE_FDD_ENB_RRC_STATE_RRC_CONNECTED:
            // Parse the message
            parse_ul_dcch_message(msg, user, rb);
            break;
        default:
            interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                      LTE_FDD_ENB_DEBUG_LEVEL_RRC,
                                      __FILE__,
                                      __LINE__,
                                      "UL-DCCH-Message RRC CON REQ state machine invalid state %s",
                                      LTE_fdd_enb_rrc_state_text[rb->get_rrc_state()]);
            break;
        }
        break;
    default:
        interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                  LTE_FDD_ENB_DEBUG_LEVEL_RRC,
                                  __FILE__,
                                  __LINE__,
                                  "DCCH state machine invalid procedure %s",
                                  LTE_fdd_enb_rrc_proc_text[rb->get_rrc_procedure()]);
        break;
    }
}

/*************************/
/*    Message Parsers    */
/*************************/
void LTE_fdd_enb_rrc::parse_ul_ccch_message(std::vector<uint8_t>  &msg,
                                            LTE_fdd_enb_user     **user,
                                            LTE_fdd_enb_rb       **rb)
{
    LTE_fdd_enb_user *act_user = NULL;

    // Parse the message
    UL_CCCH_Message ul_ccch;
    ul_ccch.Unpack(msg);

    if(ul_ccch.message_Get().Choice() != UL_CCCH_MessageType::k_c1)
        return interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                                         LTE_FDD_ENB_DEBUG_LEVEL_RRC,
                                         __FILE__,
                                         __LINE__,
                                         "Received invalid UL-CCCH-Message %s for RNTI=%u, RB=%s",
                                         ul_ccch.ToStringNoNewLines().c_str(),
                                         (*user)->get_c_rnti(),
                                         LTE_fdd_enb_rb_text[(*rb)->get_rb_id()]);
    interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                              LTE_FDD_ENB_DEBUG_LEVEL_RRC,
                              __FILE__,
                              __LINE__,
                              "Received %s for RNTI=%u, RB=%s",
                              ul_ccch.message_Get().c1_ToStringNoNewLines().c_str(),
                              (*user)->get_c_rnti(),
                              LTE_fdd_enb_rb_text[(*rb)->get_rb_id()]);

    switch(ul_ccch.message_Get().c1_Choice())
    {
    case UL_CCCH_MessageType::k_c1_rrcConnectionRequest:
        if(ul_ccch.message_Get().c1_rrcConnectionRequest_Get().criticalExtensions_Choice() != RRCConnectionRequest::k_criticalExtensions_rrcConnectionRequest_r8)
            return interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                                             LTE_FDD_ENB_DEBUG_LEVEL_RRC,
                                             __FILE__,
                                             __LINE__,
                                             "Received invalid RRC Connection Request %s for RNTI=%u, RB=%s",
                                             ul_ccch.ToStringNoNewLines().c_str(),
                                             (*user)->get_c_rnti(),
                                             LTE_fdd_enb_rb_text[(*rb)->get_rb_id()]);
        (*rb)->set_rrc_procedure(LTE_FDD_ENB_RRC_PROC_RRC_CON_REQ);
        if(ul_ccch.message_Get().c1_rrcConnectionRequest_Get().criticalExtensions_rrcConnectionRequest_r8_Get().ue_Identity_Get().Choice() != InitialUE_Identity::k_s_TMSI)
            break;
        if(LTE_FDD_ENB_ERROR_NONE != user_mgr->find_user(ul_ccch.message_Get().c1_rrcConnectionRequest_Get().criticalExtensions_rrcConnectionRequest_r8_Get().ue_Identity_Get().s_TMSI_Get(), &act_user))
            break;
        if(act_user != (*user))
        {
            act_user->copy_rbs((*user));
            (*user)->clear_rbs();
            user_mgr->transfer_c_rnti(*user, act_user);
            *user = act_user;
        }
        interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                                  LTE_FDD_ENB_DEBUG_LEVEL_RRC,
                                  __FILE__,
                                  __LINE__,
                                  "IMSI=%s is associated with RNTI=%u, RB=%s",
                                  (*user)->get_imsi_str().c_str(),
                                  (*user)->get_c_rnti(),
                                  LTE_fdd_enb_rb_text[(*rb)->get_rb_id()]);
        break;
    case UL_CCCH_MessageType::k_c1_rrcConnectionReestablishmentRequest:
        if(ul_ccch.message_Get().c1_rrcConnectionReestablishmentRequest_Get().criticalExtensions_Choice() != RRCConnectionReestablishmentRequest::k_criticalExtensions_rrcConnectionReestablishmentRequest_r8)
            return interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                                             LTE_FDD_ENB_DEBUG_LEVEL_RRC,
                                             __FILE__,
                                             __LINE__,
                                             "Received invalid RRC Connection Reestablishment Request %s for RNTI=%u, RB=%s",
                                             ul_ccch.ToStringNoNewLines().c_str(),
                                             (*user)->get_c_rnti(),
                                             LTE_fdd_enb_rb_text[(*rb)->get_rb_id()]);
        (*rb)->set_rrc_procedure(LTE_FDD_ENB_RRC_PROC_RRC_CON_REEST_REQ);
        (*rb)->set_rrc_state(LTE_FDD_ENB_RRC_STATE_IDLE);
        if(LTE_FDD_ENB_ERROR_NONE != user_mgr->find_user(ul_ccch.message_Get().c1_rrcConnectionReestablishmentRequest_Get().criticalExtensions_rrcConnectionReestablishmentRequest_r8_Get().ue_Identity_Get().c_RNTI_Get().Value(), &act_user))
            break;
        if(act_user != (*user))
        {
            act_user->copy_rbs((*user));
            (*user)->clear_rbs();
            user_mgr->transfer_c_rnti(*user, act_user);
            *user = act_user;
        }
        interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                                  LTE_FDD_ENB_DEBUG_LEVEL_RRC,
                                  __FILE__,
                                  __LINE__,
                                  "IMSI=%s is associated with RNTI=%u, RB=%s",
                                  (*user)->get_imsi_str().c_str(),
                                  (*user)->get_c_rnti(),
                                  LTE_fdd_enb_rb_text[(*rb)->get_rb_id()]);
        break;
    default:
        interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                  LTE_FDD_ENB_DEBUG_LEVEL_RRC,
                                  __FILE__,
                                  __LINE__,
                                  msg,
                                  "UL-CCCH-Message received with invalid msg_type=%s",
                                  ul_ccch.message_Get().c1_ToStringNoNewLines().c_str());
        break;
    }
}
void LTE_fdd_enb_rrc::parse_ul_dcch_message(std::vector<uint8_t> &msg,
                                            LTE_fdd_enb_user     *user,
                                            LTE_fdd_enb_rb       *rb)
{
    LTE_FDD_ENB_MME_RRC_CMD_RESP_MSG_STRUCT cmd_resp;

    // Parse the message
    UL_DCCH_Message ul_dcch;
    ul_dcch.Unpack(msg);

    if(ul_dcch.message_Get().Choice() != UL_DCCH_MessageType::k_c1)
        return interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                                         LTE_FDD_ENB_DEBUG_LEVEL_RRC,
                                         __FILE__,
                                         __LINE__,
                                         "Received invalid UL-DCCH-Message %s for RNTI=%u, RB=%s",
                                         ul_dcch.ToStringNoNewLines().c_str(),
                                         user->get_c_rnti(),
                                         LTE_fdd_enb_rb_text[rb->get_rb_id()]);
    interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                              LTE_FDD_ENB_DEBUG_LEVEL_RRC,
                              __FILE__,
                              __LINE__,
                              "Received %s for RNTI=%u, RB=%s",
                              ul_dcch.message_Get().c1_ToStringNoNewLines().c_str(),
                              user->get_c_rnti(),
                              LTE_fdd_enb_rb_text[rb->get_rb_id()]);

    switch(ul_dcch.message_Get().c1_Choice())
    {
    case UL_DCCH_MessageType::k_c1_rrcConnectionReestablishmentComplete:
        rb->set_rrc_state(LTE_FDD_ENB_RRC_STATE_RRC_CONNECTED);
        break;
    case UL_DCCH_MessageType::k_c1_rrcConnectionSetupComplete:
        if(ul_dcch.message_Get().c1_rrcConnectionSetupComplete_Get().criticalExtensions_Choice() != RRCConnectionSetupComplete::k_criticalExtensions_c1 ||
           ul_dcch.message_Get().c1_rrcConnectionSetupComplete_Get().criticalExtensions_c1_Choice() != RRCConnectionSetupComplete::k_criticalExtensions_c1_rrcConnectionSetupComplete_r8)
            return interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                                             LTE_FDD_ENB_DEBUG_LEVEL_RRC,
                                             __FILE__,
                                             __LINE__,
                                             "Received invalid RRC Connection Setup Complete %s for RNTI=%u, RB=%s",
                                             ul_dcch.ToStringNoNewLines().c_str(),
                                             user->get_c_rnti(),
                                             LTE_fdd_enb_rb_text[rb->get_rb_id()]);
        rb->set_rrc_state(LTE_FDD_ENB_RRC_STATE_RRC_CONNECTED);

        // Send the NAS message to MME
        send_mme_nas_msg_ready(user, rb, ul_dcch.message_Get().c1_rrcConnectionSetupComplete_Get().criticalExtensions_c1_rrcConnectionSetupComplete_r8_Get().dedicatedInfoNAS_Get().Value());
        break;
    case UL_DCCH_MessageType::k_c1_ulInformationTransfer:
        if(ul_dcch.message_Get().c1_ulInformationTransfer_Get().criticalExtensions_Choice() != ULInformationTransfer::k_criticalExtensions_c1 ||
           ul_dcch.message_Get().c1_ulInformationTransfer_Get().criticalExtensions_c1_Choice() != ULInformationTransfer::k_criticalExtensions_c1_ulInformationTransfer_r8)
            return interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                                             LTE_FDD_ENB_DEBUG_LEVEL_RRC,
                                             __FILE__,
                                             __LINE__,
                                             "Received invalid UL Information Tranfser %s for RNTI=%u, RB=%s",
                                             ul_dcch.ToStringNoNewLines().c_str(),
                                             user->get_c_rnti(),
                                             LTE_fdd_enb_rb_text[rb->get_rb_id()]);
        if(ul_dcch.message_Get().c1_ulInformationTransfer_Get().criticalExtensions_c1_ulInformationTransfer_r8_Get().dedicatedInfoType_Choice() != ULInformationTransfer_r8_IEs::k_dedicatedInfoType_dedicatedInfoNAS)
            return interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                             LTE_FDD_ENB_DEBUG_LEVEL_RRC,
                                             __FILE__,
                                             __LINE__,
                                             msg,
                                             "UL-DCCH-Message UL Information Transfer received with invalid dedicated info %s",
                                             ul_dcch.message_Get().c1_ulInformationTransfer_Get().criticalExtensions_c1_ulInformationTransfer_r8_Get().dedicatedInfoType_ToStringNoNewLines().c_str());
        // Send the NAS message to MME
        send_mme_nas_msg_ready(user, rb, ul_dcch.message_Get().c1_ulInformationTransfer_Get().criticalExtensions_c1_ulInformationTransfer_r8_Get().dedicatedInfoType_dedicatedInfoNAS_Get().Value());
        break;
    case UL_DCCH_MessageType::k_c1_securityModeComplete:
        // Signal MME
        cmd_resp.user     = user;
        cmd_resp.rb       = rb;
        cmd_resp.cmd_resp = LTE_FDD_ENB_MME_RRC_CMD_RESP_SECURITY;
        msgq_to_mme->send(LTE_FDD_ENB_MESSAGE_TYPE_MME_RRC_CMD_RESP,
                          LTE_FDD_ENB_DEST_LAYER_MME,
                          (LTE_FDD_ENB_MESSAGE_UNION *)&cmd_resp,
                          sizeof(LTE_FDD_ENB_MME_RRC_CMD_RESP_MSG_STRUCT));
        break;
    case UL_DCCH_MessageType::k_c1_rrcConnectionReconfigurationComplete:
        break;
    case UL_DCCH_MessageType::k_c1_ueCapabilityInformation:
        interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                                  LTE_FDD_ENB_DEBUG_LEVEL_RRC,
                                  __FILE__,
                                  __LINE__,
                                  msg,
                                  "UE Capability Information for RNTI=%u",
                                  user->get_c_rnti());
        break;
    default:
        interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                                  LTE_FDD_ENB_DEBUG_LEVEL_RRC,
                                  __FILE__,
                                  __LINE__,
                                  msg,
                                  "UL-DCCH-Message received with invalid msg_type=%s",
                                  ul_dcch.message_Get().c1_ToStringNoNewLines().c_str());
        break;
    }
}

/*************************/
/*    Message Senders    */
/*************************/
void LTE_fdd_enb_rrc::send_dl_info_transfer(LTE_fdd_enb_user       *user,
                                            LTE_fdd_enb_rb         *rb,
                                            LIBLTE_BYTE_MSG_STRUCT *msg)
{
    DL_DCCH_Message dl_dcch;
    dl_dcch.message_Set()->SetChoice(DL_DCCH_MessageType::k_c1);
    dl_dcch.message_Set()->c1_SetChoice(DL_DCCH_MessageType::k_c1_dlInformationTransfer);
    dl_dcch.message_Set()->c1_dlInformationTransfer_Set()->rrc_TransactionIdentifier_Set()->SetValue(rb->get_rrc_transaction_id());
    dl_dcch.message_Set()->c1_dlInformationTransfer_Set()->criticalExtensions_SetChoice(DLInformationTransfer::k_criticalExtensions_c1);
    dl_dcch.message_Set()->c1_dlInformationTransfer_Set()->criticalExtensions_c1_SetChoice(DLInformationTransfer::k_criticalExtensions_c1_dlInformationTransfer_r8);
    dl_dcch.message_Set()->c1_dlInformationTransfer_Set()->criticalExtensions_c1_dlInformationTransfer_r8_Set()->dedicatedInfoType_SetChoice(DLInformationTransfer_r8_IEs::k_dedicatedInfoType_dedicatedInfoNAS);
    std::vector<uint8_t> di_nas;
    for(uint32 i=0; i<msg->N_bytes; i++)
        di_nas.push_back(msg->msg[i]);
    dl_dcch.message_Set()->c1_dlInformationTransfer_Set()->criticalExtensions_c1_dlInformationTransfer_r8_Set()->dedicatedInfoType_dedicatedInfoNAS_Set()->SetValue(di_nas);
    liblte_full_stack_message fsm;
    dl_dcch.Pack(fsm.rrc);
    interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                              LTE_FDD_ENB_DEBUG_LEVEL_RRC,
                              __FILE__,
                              __LINE__,
                              "Sending DL Info Transfer for RNTI=%u, RB=%s",
                              user->get_c_rnti(),
                              LTE_fdd_enb_rb_text[rb->get_rb_id()]);

    // Send the PDU to PDCP
    send_pdcp_sdu_ready(user, rb, fsm.rrc);
}
void LTE_fdd_enb_rrc::send_rrc_con_reconfig(LTE_fdd_enb_user       *user,
                                            LTE_fdd_enb_rb         *rb,
                                            LIBLTE_BYTE_MSG_STRUCT *msg)
{
    LTE_fdd_enb_rb *drb1 = NULL;
    user->get_drb(LTE_FDD_ENB_RB_DRB1, &drb1);
    LTE_fdd_enb_rb *drb2 = NULL;
    user->get_drb(LTE_FDD_ENB_RB_DRB2, &drb2);

    DL_DCCH_Message dl_dcch;
    dl_dcch.message_Set()->SetChoice(DL_DCCH_MessageType::k_c1);
    dl_dcch.message_Set()->c1_SetChoice(DL_DCCH_MessageType::k_c1_rrcConnectionReconfiguration);
    dl_dcch.message_Set()->c1_rrcConnectionReconfiguration_Set()->rrc_TransactionIdentifier_Set()->SetValue(rb->get_rrc_transaction_id());
    dl_dcch.message_Set()->c1_rrcConnectionReconfiguration_Set()->criticalExtensions_SetChoice(RRCConnectionReconfiguration::k_criticalExtensions_c1);
    dl_dcch.message_Set()->c1_rrcConnectionReconfiguration_Set()->criticalExtensions_c1_SetChoice(RRCConnectionReconfiguration::k_criticalExtensions_c1_rrcConnectionReconfiguration_r8);
    dl_dcch.message_Set()->c1_rrcConnectionReconfiguration_Set()->criticalExtensions_c1_rrcConnectionReconfiguration_r8_Set()->measConfig_Clear();
    dl_dcch.message_Set()->c1_rrcConnectionReconfiguration_Set()->criticalExtensions_c1_rrcConnectionReconfiguration_r8_Set()->mobilityControlInfo_Clear();
    dl_dcch.message_Set()->c1_rrcConnectionReconfiguration_Set()->criticalExtensions_c1_rrcConnectionReconfiguration_r8_Set()->dedicatedInfoNASList_Clear();
    if(NULL != msg)
    {
        std::vector<uint8_t> tmp_msg(msg->N_bytes);
        for(uint32 i=0; i<msg->N_bytes; i++)
            tmp_msg[i] = msg->msg[i];
        DedicatedInfoNAS di_nas;
        di_nas.SetValue(tmp_msg);
        dl_dcch.message_Set()->c1_rrcConnectionReconfiguration_Set()->criticalExtensions_c1_rrcConnectionReconfiguration_r8_Set()->dedicatedInfoNASList_SetValue({di_nas});
    }
    std::vector<SRB_ToAddMod> srb_list(1);
    srb_list[0].srb_Identity_SetValue(2);
    srb_list[0].rlc_Config_SetChoice(SRB_ToAddMod::k_rlc_Config_defaultValue);
    srb_list[0].logicalChannelConfig_SetChoice(SRB_ToAddMod::k_logicalChannelConfig_defaultValue);
    dl_dcch.message_Set()->c1_rrcConnectionReconfiguration_Set()->criticalExtensions_c1_rrcConnectionReconfiguration_r8_Set()->radioResourceConfigDedicated_Set()->srb_ToAddModList_Set()->SetValue(srb_list);
    dl_dcch.message_Set()->c1_rrcConnectionReconfiguration_Set()->criticalExtensions_c1_rrcConnectionReconfiguration_r8_Set()->radioResourceConfigDedicated_Set()->drb_ToAddModList_Clear();
    if(NULL != drb1)
    {
        DRB_ToAddMod drb;
        drb.eps_BearerIdentity_SetValue(drb1->get_eps_bearer_id());
        drb.drb_Identity_Set()->SetValue(drb1->get_drb_id());
        drb.pdcp_Config_Set()->discardTimer_SetValue(PDCP_Config::k_discardTimer_infinity);
        drb.pdcp_Config_Set()->rlc_AM_value.SetPresence(true);
        drb.pdcp_Config_Set()->rlc_AM_value.statusReportRequired_SetValue(true);
        drb.pdcp_Config_Set()->headerCompression_SetChoice(PDCP_Config::k_headerCompression_notUsed);
        drb.rlc_Config_Set()->SetChoice(RLC_Config::k_am);
        drb.rlc_Config_Set()->am_value.ul_AM_RLC_Set()->t_PollRetransmit_Set()->SetValue(T_PollRetransmit::k_ms45);
        drb.rlc_Config_Set()->am_value.ul_AM_RLC_Set()->pollPDU_Set()->SetValue(PollPDU::k_pInfinity);
        drb.rlc_Config_Set()->am_value.ul_AM_RLC_Set()->pollByte_Set()->SetValue(PollByte::k_kBinfinity);
        drb.rlc_Config_Set()->am_value.ul_AM_RLC_Set()->maxRetxThreshold_SetValue(UL_AM_RLC::k_maxRetxThreshold_t4);
        drb.rlc_Config_Set()->am_value.dl_AM_RLC_Set()->t_Reordering_Set()->SetValue(T_Reordering::k_ms35);
        drb.rlc_Config_Set()->am_value.dl_AM_RLC_Set()->t_StatusProhibit_Set()->SetValue(T_StatusProhibit::k_ms0);
        drb.logicalChannelIdentity_SetValue(drb1->get_lc_id());
        drb.logicalChannelConfig_Set()->ul_SpecificParameters_value.SetPresence(true);
        drb.logicalChannelConfig_Set()->ul_SpecificParameters_value.priority_SetValue(13);
        drb.logicalChannelConfig_Set()->ul_SpecificParameters_value.prioritisedBitRate_SetValue(LogicalChannelConfig::ul_SpecificParameters::k_prioritisedBitRate_infinity);
        drb.logicalChannelConfig_Set()->ul_SpecificParameters_value.bucketSizeDuration_SetValue(LogicalChannelConfig::ul_SpecificParameters::k_bucketSizeDuration_ms100);
        drb.logicalChannelConfig_Set()->ul_SpecificParameters_value.logicalChannelGroup_SetValue(drb1->get_log_chan_group());
        drb.logicalChannelConfig_Set()->logicalChannelSR_Mask_r9_Clear();
        dl_dcch.message_Set()->c1_rrcConnectionReconfiguration_Set()->criticalExtensions_c1_rrcConnectionReconfiguration_r8_Set()->radioResourceConfigDedicated_Set()->drb_ToAddModList_Set()->SetValue({drb});
    }
    if(NULL != drb2)
    {
        DRB_ToAddMod drb;
        drb.eps_BearerIdentity_SetValue(drb2->get_eps_bearer_id());
        drb.drb_Identity_Set()->SetValue(drb2->get_drb_id());
        drb.pdcp_Config_Set()->discardTimer_SetValue(PDCP_Config::k_discardTimer_infinity);
        drb.pdcp_Config_Set()->rlc_AM_value.SetPresence(true);
        drb.pdcp_Config_Set()->rlc_AM_value.statusReportRequired_SetValue(true);
        drb.pdcp_Config_Set()->headerCompression_SetChoice(PDCP_Config::k_headerCompression_notUsed);
        drb.rlc_Config_Set()->SetChoice(RLC_Config::k_am);
        drb.rlc_Config_Set()->am_value.ul_AM_RLC_Set()->t_PollRetransmit_Set()->SetValue(T_PollRetransmit::k_ms45);
        drb.rlc_Config_Set()->am_value.ul_AM_RLC_Set()->pollPDU_Set()->SetValue(PollPDU::k_pInfinity);
        drb.rlc_Config_Set()->am_value.ul_AM_RLC_Set()->pollByte_Set()->SetValue(PollByte::k_kBinfinity);
        drb.rlc_Config_Set()->am_value.ul_AM_RLC_Set()->maxRetxThreshold_SetValue(UL_AM_RLC::k_maxRetxThreshold_t4);
        drb.rlc_Config_Set()->am_value.dl_AM_RLC_Set()->t_Reordering_Set()->SetValue(T_Reordering::k_ms35);
        drb.rlc_Config_Set()->am_value.dl_AM_RLC_Set()->t_StatusProhibit_Set()->SetValue(T_StatusProhibit::k_ms0);
        drb.logicalChannelIdentity_SetValue(drb2->get_lc_id());
        drb.logicalChannelConfig_Set()->ul_SpecificParameters_value.SetPresence(true);
        drb.logicalChannelConfig_Set()->ul_SpecificParameters_value.priority_SetValue(13);
        drb.logicalChannelConfig_Set()->ul_SpecificParameters_value.prioritisedBitRate_SetValue(LogicalChannelConfig::ul_SpecificParameters::k_prioritisedBitRate_infinity);
        drb.logicalChannelConfig_Set()->ul_SpecificParameters_value.bucketSizeDuration_SetValue(LogicalChannelConfig::ul_SpecificParameters::k_bucketSizeDuration_ms100);
        drb.logicalChannelConfig_Set()->ul_SpecificParameters_value.logicalChannelGroup_SetValue(drb2->get_log_chan_group());
        drb.logicalChannelConfig_Set()->logicalChannelSR_Mask_r9_Clear();
        std::vector<DRB_ToAddMod> drb_list = dl_dcch.message_Get().c1_rrcConnectionReconfiguration_Get().criticalExtensions_c1_rrcConnectionReconfiguration_r8_Get().radioResourceConfigDedicated_Get().drb_ToAddModList_Get().Value();
        drb_list.push_back(drb);
        dl_dcch.message_Set()->c1_rrcConnectionReconfiguration_Set()->criticalExtensions_c1_rrcConnectionReconfiguration_r8_Set()->radioResourceConfigDedicated_Set()->drb_ToAddModList_Set()->SetValue(drb_list);
    }
    dl_dcch.message_Set()->c1_rrcConnectionReconfiguration_Set()->criticalExtensions_c1_rrcConnectionReconfiguration_r8_Set()->radioResourceConfigDedicated_Set()->drb_ToReleaseList_Clear();
    dl_dcch.message_Set()->c1_rrcConnectionReconfiguration_Set()->criticalExtensions_c1_rrcConnectionReconfiguration_r8_Set()->radioResourceConfigDedicated_Set()->mac_MainConfig_Clear();
    dl_dcch.message_Set()->c1_rrcConnectionReconfiguration_Set()->criticalExtensions_c1_rrcConnectionReconfiguration_r8_Set()->radioResourceConfigDedicated_Set()->sps_Config_Clear();
    interface->get_rrc_phy_cnfg_ded(dl_dcch.message_Set()->c1_rrcConnectionReconfiguration_Set()->criticalExtensions_c1_rrcConnectionReconfiguration_r8_Set()->radioResourceConfigDedicated_Set()->physicalConfigDedicated_Set(),
                                    0, 0, i_sr, N_1_P_PUCCH_SR);
    mac->add_periodic_sr_pucch(user->get_c_rnti(), i_sr, N_1_P_PUCCH_SR);
    increment_i_sr();
    dl_dcch.message_Set()->c1_rrcConnectionReconfiguration_Set()->criticalExtensions_c1_rrcConnectionReconfiguration_r8_Set()->radioResourceConfigDedicated_Set()->rlf_TimersAndConstants_r9_Clear();
    dl_dcch.message_Set()->c1_rrcConnectionReconfiguration_Set()->criticalExtensions_c1_rrcConnectionReconfiguration_r8_Set()->securityConfigHO_Clear();
    dl_dcch.message_Set()->c1_rrcConnectionReconfiguration_Set()->criticalExtensions_c1_rrcConnectionReconfiguration_r8_Set()->nonCriticalExtension_Clear();
    liblte_full_stack_message fsm;
    dl_dcch.Pack(fsm.rrc);
    interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                              LTE_FDD_ENB_DEBUG_LEVEL_RRC,
                              __FILE__,
                              __LINE__,
                              "Sending RRC Connection Reconfiguration for RNTI=%u, RB=%s",
                              user->get_c_rnti(),
                              LTE_fdd_enb_rb_text[rb->get_rb_id()]);

    // Send the PDU to PDCP
    send_pdcp_sdu_ready(user, rb, fsm.rrc);
}
void LTE_fdd_enb_rrc::send_rrc_con_reest(LTE_fdd_enb_user *user,
                                         LTE_fdd_enb_rb   *rb)
{
    DL_CCCH_Message dl_ccch;
    dl_ccch.message_Set()->SetChoice(DL_CCCH_MessageType::k_c1);
    dl_ccch.message_Set()->c1_SetChoice(DL_CCCH_MessageType::k_c1_rrcConnectionReestablishment);
    dl_ccch.message_Set()->c1_rrcConnectionReestablishment_Set()->rrc_TransactionIdentifier_Set()->SetValue(rb->get_rrc_transaction_id());
    dl_ccch.message_Set()->c1_rrcConnectionReestablishment_Set()->rrc_TransactionIdentifier_Set()->SetValue(rb->get_rrc_transaction_id());
    dl_ccch.message_Set()->c1_rrcConnectionReestablishment_Set()->criticalExtensions_SetChoice(RRCConnectionReestablishment::k_criticalExtensions_c1);
    dl_ccch.message_Set()->c1_rrcConnectionReestablishment_Set()->criticalExtensions_c1_SetChoice(RRCConnectionReestablishment::k_criticalExtensions_c1_rrcConnectionReestablishment_r8);
    std::vector<SRB_ToAddMod> srb_list(1);
    srb_list[0].srb_Identity_SetValue(1);
    srb_list[0].rlc_Config_SetChoice(SRB_ToAddMod::k_rlc_Config_defaultValue);
    srb_list[0].logicalChannelConfig_SetChoice(SRB_ToAddMod::k_logicalChannelConfig_defaultValue);
    RRCConnectionReestablishment_r8_IEs rrc_con_reest;
    rrc_con_reest.radioResourceConfigDedicated_Set()->srb_ToAddModList_Set()->SetValue(srb_list);
    rrc_con_reest.radioResourceConfigDedicated_Set()->drb_ToAddModList_Clear();
    rrc_con_reest.radioResourceConfigDedicated_Set()->drb_ToReleaseList_Clear();
    rrc_con_reest.radioResourceConfigDedicated_Set()->mac_MainConfig_SetChoice(RadioResourceConfigDedicated::k_mac_MainConfig_explicitValue);
    rrc_con_reest.radioResourceConfigDedicated_Set()->mac_MainConfig_explicitValue_Set()->ul_SCH_Config_value.SetPresence(true);
    rrc_con_reest.radioResourceConfigDedicated_Set()->mac_MainConfig_explicitValue_Set()->ul_SCH_Config_value.maxHARQ_Tx_SetValue(MAC_MainConfig::ul_SCH_Config::k_maxHARQ_Tx_n1);
    rrc_con_reest.radioResourceConfigDedicated_Set()->mac_MainConfig_explicitValue_Set()->ul_SCH_Config_value.periodicBSR_Timer_Clear();
    rrc_con_reest.radioResourceConfigDedicated_Set()->mac_MainConfig_explicitValue_Set()->ul_SCH_Config_value.retxBSR_Timer_SetValue(MAC_MainConfig::ul_SCH_Config::k_retxBSR_Timer_sf1280);
    rrc_con_reest.radioResourceConfigDedicated_Set()->mac_MainConfig_explicitValue_Set()->ul_SCH_Config_value.ttiBundling_SetValue(false);
    rrc_con_reest.radioResourceConfigDedicated_Set()->mac_MainConfig_explicitValue_Set()->drx_Config_Clear();
    rrc_con_reest.radioResourceConfigDedicated_Set()->mac_MainConfig_explicitValue_Set()->timeAlignmentTimerDedicated_Set()->SetValue(TimeAlignmentTimer::k_sf10240);
    rrc_con_reest.radioResourceConfigDedicated_Set()->mac_MainConfig_explicitValue_Set()->phr_Config_Clear();
    rrc_con_reest.radioResourceConfigDedicated_Set()->mac_MainConfig_explicitValue_Set()->sr_ProhibitTimer_r9_Clear();
    rrc_con_reest.radioResourceConfigDedicated_Set()->mac_MainConfig_explicitValue_Set()->sCellDeactivationTimer_r10_Clear();
    rrc_con_reest.radioResourceConfigDedicated_Set()->mac_MainConfig_explicitValue_Set()->extendedBSR_Sizes_r10_Clear();
    rrc_con_reest.radioResourceConfigDedicated_Set()->mac_MainConfig_explicitValue_Set()->extendedPHR_r10_Clear();
    rrc_con_reest.radioResourceConfigDedicated_Set()->sps_Config_Clear();
    interface->get_rrc_phy_cnfg_ded(rrc_con_reest.radioResourceConfigDedicated_Set()->physicalConfigDedicated_Set(), 0, 0, i_sr, N_1_P_PUCCH_SR);
    rrc_con_reest.radioResourceConfigDedicated_Set()->rlf_TimersAndConstants_r9_Clear();
    rrc_con_reest.nextHopChainingCount_Set()->SetValue(0);
    rrc_con_reest.nonCriticalExtension_Clear();
    dl_ccch.message_Set()->c1_rrcConnectionReestablishment_Set()->criticalExtensions_c1_rrcConnectionReestablishment_r8_Set(rrc_con_reest);
    liblte_full_stack_message fsm;
    dl_ccch.Pack(fsm.rrc);
    mac->add_periodic_sr_pucch(user->get_c_rnti(), i_sr, N_1_P_PUCCH_SR);
    increment_i_sr();
    interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                              LTE_FDD_ENB_DEBUG_LEVEL_RRC,
                              __FILE__,
                              __LINE__,
                              "Sending RRC Connection Reestablishment for RNTI=%u, RB=%s",
                              user->get_c_rnti(),
                              LTE_fdd_enb_rb_text[rb->get_rb_id()]);

    // Send the PDU to PDCP
    send_pdcp_sdu_ready(user, rb, fsm.rrc);
}
void LTE_fdd_enb_rrc::send_rrc_con_reest_reject(LTE_fdd_enb_user *user,
                                                LTE_fdd_enb_rb   *rb)
{
    DL_CCCH_Message dl_ccch;
    dl_ccch.message_Set()->SetChoice(DL_CCCH_MessageType::k_c1);
    dl_ccch.message_Set()->c1_SetChoice(DL_CCCH_MessageType::k_c1_rrcConnectionReestablishmentReject);
    dl_ccch.message_Set()->c1_rrcConnectionReestablishmentReject_Set()->criticalExtensions_SetChoice(RRCConnectionReestablishmentReject::k_criticalExtensions_rrcConnectionReestablishmentReject_r8);
    dl_ccch.message_Set()->c1_rrcConnectionReestablishmentReject_Set()->criticalExtensions_rrcConnectionReestablishmentReject_r8_Set()->nonCriticalExtension_Clear();
    liblte_full_stack_message fsm;
    dl_ccch.Pack(fsm.rrc);
    interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                              LTE_FDD_ENB_DEBUG_LEVEL_RRC,
                              __FILE__,
                              __LINE__,
                              "Sending RRC Connection Reestablishment Reject for RNTI=%u, RB=%s",
                              user->get_c_rnti(),
                              LTE_fdd_enb_rb_text[rb->get_rb_id()]);

    // Send the PDU to PDCP
    send_pdcp_sdu_ready(user, rb, fsm.rrc);
}
void LTE_fdd_enb_rrc::send_rrc_con_release(LTE_fdd_enb_user *user,
                                           LTE_fdd_enb_rb   *rb)
{
    DL_DCCH_Message dl_dcch;
    dl_dcch.message_Set()->SetChoice(DL_DCCH_MessageType::k_c1);
    dl_dcch.message_Set()->c1_SetChoice(DL_DCCH_MessageType::k_c1_rrcConnectionRelease);
    dl_dcch.message_Set()->c1_rrcConnectionRelease_Set()->rrc_TransactionIdentifier_Set()->SetValue(rb->get_rrc_transaction_id());
    dl_dcch.message_Set()->c1_rrcConnectionRelease_Set()->criticalExtensions_SetChoice(RRCConnectionRelease::k_criticalExtensions_c1);
    dl_dcch.message_Set()->c1_rrcConnectionRelease_Set()->criticalExtensions_c1_SetChoice(RRCConnectionRelease::k_criticalExtensions_c1_rrcConnectionRelease_r8);
    dl_dcch.message_Set()->c1_rrcConnectionRelease_Set()->criticalExtensions_c1_rrcConnectionRelease_r8_Set()->releaseCause_Set()->SetValue(ReleaseCause::k_other);
    dl_dcch.message_Set()->c1_rrcConnectionRelease_Set()->criticalExtensions_c1_rrcConnectionRelease_r8_Set()->redirectedCarrierInfo_Clear();
    dl_dcch.message_Set()->c1_rrcConnectionRelease_Set()->criticalExtensions_c1_rrcConnectionRelease_r8_Set()->idleModeMobilityControlInfo_Clear();
    dl_dcch.message_Set()->c1_rrcConnectionRelease_Set()->criticalExtensions_c1_rrcConnectionRelease_r8_Set()->nonCriticalExtension_Clear();
    liblte_full_stack_message fsm;
    dl_dcch.Pack(fsm.rrc);
    interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                              LTE_FDD_ENB_DEBUG_LEVEL_RRC,
                              __FILE__,
                              __LINE__,
                              "Sending RRC Connection Release for RNTI=%u, RB=%s",
                              user->get_c_rnti(),
                              LTE_fdd_enb_rb_text[rb->get_rb_id()]);

    mac->remove_periodic_sr_pucch(user->get_c_rnti());

    // Send the PDU to PDCP
    send_pdcp_sdu_ready(user, rb, fsm.rrc);
}
void LTE_fdd_enb_rrc::send_rrc_con_setup(LTE_fdd_enb_user *user,
                                         LTE_fdd_enb_rb   *rb)
{
    DL_CCCH_Message dl_ccch;
    dl_ccch.message_Set()->SetChoice(DL_CCCH_MessageType::k_c1);
    dl_ccch.message_Set()->c1_SetChoice(DL_CCCH_MessageType::k_c1_rrcConnectionSetup);
    dl_ccch.message_Set()->c1_rrcConnectionSetup_Set()->rrc_TransactionIdentifier_Set()->SetValue(rb->get_rrc_transaction_id());
    dl_ccch.message_Set()->c1_rrcConnectionSetup_Set()->criticalExtensions_SetChoice(RRCConnectionSetup::k_criticalExtensions_c1);
    dl_ccch.message_Set()->c1_rrcConnectionSetup_Set()->criticalExtensions_c1_SetChoice(RRCConnectionSetup::k_criticalExtensions_c1_rrcConnectionSetup_r8);
    std::vector<SRB_ToAddMod> srb_list(1);
    srb_list[0].srb_Identity_SetValue(1);
    srb_list[0].rlc_Config_SetChoice(SRB_ToAddMod::k_rlc_Config_defaultValue);
    srb_list[0].logicalChannelConfig_SetChoice(SRB_ToAddMod::k_logicalChannelConfig_defaultValue);
    dl_ccch.message_Set()->c1_rrcConnectionSetup_Set()->criticalExtensions_c1_rrcConnectionSetup_r8_Set()->radioResourceConfigDedicated_Set()->srb_ToAddModList_Set()->SetValue(srb_list);
    dl_ccch.message_Set()->c1_rrcConnectionSetup_Set()->criticalExtensions_c1_rrcConnectionSetup_r8_Set()->radioResourceConfigDedicated_Set()->drb_ToAddModList_Clear();
    dl_ccch.message_Set()->c1_rrcConnectionSetup_Set()->criticalExtensions_c1_rrcConnectionSetup_r8_Set()->radioResourceConfigDedicated_Set()->drb_ToReleaseList_Clear();
    dl_ccch.message_Set()->c1_rrcConnectionSetup_Set()->criticalExtensions_c1_rrcConnectionSetup_r8_Set()->radioResourceConfigDedicated_Set()->mac_MainConfig_SetChoice(RadioResourceConfigDedicated::k_mac_MainConfig_explicitValue);
    dl_ccch.message_Set()->c1_rrcConnectionSetup_Set()->criticalExtensions_c1_rrcConnectionSetup_r8_Set()->radioResourceConfigDedicated_Set()->mac_MainConfig_explicitValue_Set()->ul_SCH_Config_value.SetPresence(true);
    dl_ccch.message_Set()->c1_rrcConnectionSetup_Set()->criticalExtensions_c1_rrcConnectionSetup_r8_Set()->radioResourceConfigDedicated_Set()->mac_MainConfig_explicitValue_Set()->ul_SCH_Config_value.maxHARQ_Tx_SetValue(MAC_MainConfig::ul_SCH_Config::k_maxHARQ_Tx_n1);
    dl_ccch.message_Set()->c1_rrcConnectionSetup_Set()->criticalExtensions_c1_rrcConnectionSetup_r8_Set()->radioResourceConfigDedicated_Set()->mac_MainConfig_explicitValue_Set()->ul_SCH_Config_value.periodicBSR_Timer_Clear();
    dl_ccch.message_Set()->c1_rrcConnectionSetup_Set()->criticalExtensions_c1_rrcConnectionSetup_r8_Set()->radioResourceConfigDedicated_Set()->mac_MainConfig_explicitValue_Set()->ul_SCH_Config_value.retxBSR_Timer_SetValue(MAC_MainConfig::ul_SCH_Config::k_retxBSR_Timer_sf1280);
    dl_ccch.message_Set()->c1_rrcConnectionSetup_Set()->criticalExtensions_c1_rrcConnectionSetup_r8_Set()->radioResourceConfigDedicated_Set()->mac_MainConfig_explicitValue_Set()->ul_SCH_Config_value.ttiBundling_SetValue(false);
    dl_ccch.message_Set()->c1_rrcConnectionSetup_Set()->criticalExtensions_c1_rrcConnectionSetup_r8_Set()->radioResourceConfigDedicated_Set()->mac_MainConfig_explicitValue_Set()->drx_Config_Clear();
    dl_ccch.message_Set()->c1_rrcConnectionSetup_Set()->criticalExtensions_c1_rrcConnectionSetup_r8_Set()->radioResourceConfigDedicated_Set()->mac_MainConfig_explicitValue_Set()->timeAlignmentTimerDedicated_Set()->SetValue(TimeAlignmentTimer::k_sf10240);
    dl_ccch.message_Set()->c1_rrcConnectionSetup_Set()->criticalExtensions_c1_rrcConnectionSetup_r8_Set()->radioResourceConfigDedicated_Set()->mac_MainConfig_explicitValue_Set()->phr_Config_Clear();
    dl_ccch.message_Set()->c1_rrcConnectionSetup_Set()->criticalExtensions_c1_rrcConnectionSetup_r8_Set()->radioResourceConfigDedicated_Set()->mac_MainConfig_explicitValue_Set()->sr_ProhibitTimer_r9_Clear();
    dl_ccch.message_Set()->c1_rrcConnectionSetup_Set()->criticalExtensions_c1_rrcConnectionSetup_r8_Set()->radioResourceConfigDedicated_Set()->mac_MainConfig_explicitValue_Set()->sCellDeactivationTimer_r10_Clear();
    dl_ccch.message_Set()->c1_rrcConnectionSetup_Set()->criticalExtensions_c1_rrcConnectionSetup_r8_Set()->radioResourceConfigDedicated_Set()->mac_MainConfig_explicitValue_Set()->extendedBSR_Sizes_r10_Clear();
    dl_ccch.message_Set()->c1_rrcConnectionSetup_Set()->criticalExtensions_c1_rrcConnectionSetup_r8_Set()->radioResourceConfigDedicated_Set()->mac_MainConfig_explicitValue_Set()->extendedPHR_r10_Clear();
    dl_ccch.message_Set()->c1_rrcConnectionSetup_Set()->criticalExtensions_c1_rrcConnectionSetup_r8_Set()->radioResourceConfigDedicated_Set()->sps_Config_Clear();
    interface->get_rrc_phy_cnfg_ded(dl_ccch.message_Set()->c1_rrcConnectionSetup_Set()->criticalExtensions_c1_rrcConnectionSetup_r8_Set()->radioResourceConfigDedicated_Set()->physicalConfigDedicated_Set(),
                                    0, 0, i_sr, N_1_P_PUCCH_SR);
    mac->add_periodic_sr_pucch(user->get_c_rnti(), i_sr, N_1_P_PUCCH_SR);
    increment_i_sr();
    dl_ccch.message_Set()->c1_rrcConnectionSetup_Set()->criticalExtensions_c1_rrcConnectionSetup_r8_Set()->radioResourceConfigDedicated_Set()->rlf_TimersAndConstants_r9_Clear();
    dl_ccch.message_Set()->c1_rrcConnectionSetup_Set()->criticalExtensions_c1_rrcConnectionSetup_r8_Set()->nonCriticalExtension_Clear();
    liblte_full_stack_message fsm;
    dl_ccch.Pack(fsm.rrc);
    interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                              LTE_FDD_ENB_DEBUG_LEVEL_RRC,
                              __FILE__,
                              __LINE__,
                              "Sending RRC Connection Setup for RNTI=%u, RB=%s",
                              user->get_c_rnti(),
                              LTE_fdd_enb_rb_text[rb->get_rb_id()]);

    // Send the PDU to PDCP
    send_pdcp_sdu_ready(user, rb, fsm.rrc);
}
void LTE_fdd_enb_rrc::send_security_mode_command(LTE_fdd_enb_user *user,
                                                 LTE_fdd_enb_rb   *rb)
{
    DL_DCCH_Message dl_dcch;
    dl_dcch.message_Set()->SetChoice(DL_DCCH_MessageType::k_c1);
    dl_dcch.message_Set()->c1_SetChoice(DL_DCCH_MessageType::k_c1_securityModeCommand);
    dl_dcch.message_Set()->c1_securityModeCommand_Set()->rrc_TransactionIdentifier_Set()->SetValue(rb->get_rrc_transaction_id());
    dl_dcch.message_Set()->c1_securityModeCommand_Set()->criticalExtensions_SetChoice(SecurityModeCommand::k_criticalExtensions_c1);
    dl_dcch.message_Set()->c1_securityModeCommand_Set()->criticalExtensions_c1_SetChoice(SecurityModeCommand::k_criticalExtensions_c1_securityModeCommand_r8);
    dl_dcch.message_Set()->c1_securityModeCommand_Set()->criticalExtensions_c1_securityModeCommand_r8_Set()->securityConfigSMC_Set()->securityAlgorithmConfig_Set()->cipheringAlgorithm_SetValue(SecurityAlgorithmConfig::k_cipheringAlgorithm_eea0);
    dl_dcch.message_Set()->c1_securityModeCommand_Set()->criticalExtensions_c1_securityModeCommand_r8_Set()->securityConfigSMC_Set()->securityAlgorithmConfig_Set()->integrityProtAlgorithm_SetValue(SecurityAlgorithmConfig::k_integrityProtAlgorithm_eia2);
    dl_dcch.message_Set()->c1_securityModeCommand_Set()->criticalExtensions_c1_securityModeCommand_r8_Set()->nonCriticalExtension_Clear();
    liblte_full_stack_message fsm;
    dl_dcch.Pack(fsm.rrc);
    interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                              LTE_FDD_ENB_DEBUG_LEVEL_RRC,
                              __FILE__,
                              __LINE__,
                              "Sending Security Mode Command for RNTI=%u, RB=%s",
                              user->get_c_rnti(),
                              LTE_fdd_enb_rb_text[rb->get_rb_id()]);

    // Configure PDCP for security
    rb->set_pdcp_config(LTE_FDD_ENB_PDCP_CONFIG_SECURITY);

    // Send the PDU to PDCP
    send_pdcp_sdu_ready(user, rb, fsm.rrc);
}
void LTE_fdd_enb_rrc::send_ue_capability_enquiry(LTE_fdd_enb_user *user,
                                                 LTE_fdd_enb_rb   *rb)
{
    DL_DCCH_Message dl_dcch;
    dl_dcch.message_Set()->SetChoice(DL_DCCH_MessageType::k_c1);
    dl_dcch.message_Set()->c1_SetChoice(DL_DCCH_MessageType::k_c1_ueCapabilityEnquiry);
    dl_dcch.message_Set()->c1_ueCapabilityEnquiry_Set()->rrc_TransactionIdentifier_Set()->SetValue((rb->get_rrc_transaction_id() + 1) % 4);
    dl_dcch.message_Set()->c1_ueCapabilityEnquiry_Set()->criticalExtensions_SetChoice(UECapabilityEnquiry::k_criticalExtensions_c1);
    dl_dcch.message_Set()->c1_ueCapabilityEnquiry_Set()->criticalExtensions_c1_SetChoice(UECapabilityEnquiry::k_criticalExtensions_c1_ueCapabilityEnquiry_r8);
    std::vector<RAT_Type> rats(5);
    rats[0].SetValue(RAT_Type::k_eutra);
    rats[1].SetValue(RAT_Type::k_utra);
    rats[2].SetValue(RAT_Type::k_geran_cs);
    rats[3].SetValue(RAT_Type::k_geran_ps);
    rats[4].SetValue(RAT_Type::k_cdma2000_1XRTT);
    dl_dcch.message_Set()->c1_ueCapabilityEnquiry_Set()->criticalExtensions_c1_ueCapabilityEnquiry_r8_Set()->ue_CapabilityRequest_Set()->SetValue(rats);
    dl_dcch.message_Set()->c1_ueCapabilityEnquiry_Set()->criticalExtensions_c1_ueCapabilityEnquiry_r8_Set()->nonCriticalExtension_Clear();
    liblte_full_stack_message fsm;
    dl_dcch.Pack(fsm.rrc);
    interface->send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                              LTE_FDD_ENB_DEBUG_LEVEL_RRC,
                              __FILE__,
                              __LINE__,
                              "Sending UE Capability Enquiry for RNTI=%u, RB=%s",
                              user->get_c_rnti(),
                              LTE_fdd_enb_rb_text[rb->get_rb_id()]);

    // Send the PDU to PDCP
    send_pdcp_sdu_ready(user, rb, fsm.rrc);
}

/*****************/
/*    Helpers    */
/*****************/
void LTE_fdd_enb_rrc::increment_i_sr()
{
    i_sr++;
    if(i_sr > I_SR_MAX)
        i_sr = I_SR_MIN;
}
