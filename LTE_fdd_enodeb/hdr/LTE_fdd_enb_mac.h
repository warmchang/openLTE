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

    File: LTE_fdd_enb_mac.h

    Description: Contains all the definitions for the LTE FDD eNodeB
                 medium access control layer.

    Revision History
    ----------    -------------    --------------------------------------------
    11/09/2013    Ben Wojtowicz    Created file
    01/18/2014    Ben Wojtowicz    Cached a copy of the interface class.
    05/04/2014    Ben Wojtowicz    Added ULSCH handling.
    06/15/2014    Ben Wojtowicz    Added uplink scheduling and changed fn_combo
                                   to current_tti.
    11/29/2014    Ben Wojtowicz    Using the byte message struct for SDUs.
    12/16/2014    Ben Wojtowicz    Added ol extension to message queues.
    02/15/2015    Ben Wojtowicz    Moved to new message queue.
    12/06/2015    Ben Wojtowicz    Changed boost::mutex to sem_t and added some
                                   helper functions.
    02/13/2016    Ben Wojtowicz    Removed boost message queue include.
    07/31/2016    Ben Wojtowicz    Added a define for max HARQ retransmissions.
    07/29/2017    Ben Wojtowicz    Added SR support and added IPC direct to a UE
                                   MAC.
    02/14/2021    Ben Wojtowicz    Massive reformat and added a persistent DL
                                   scheduler.

*******************************************************************************/

#ifndef __LTE_FDD_ENB_MAC_H__
#define __LTE_FDD_ENB_MAC_H__

/*******************************************************************************
                              INCLUDES
*******************************************************************************/

#include "LTE_fdd_enb_interface.h"
#include "LTE_fdd_enb_msgq.h"
#include "LTE_fdd_enb_user.h"
#include "liblte_mac.h"
#include "libtools_ipc_msgq.h"
#include <list>
#include <mutex>

/*******************************************************************************
                              DEFINES
*******************************************************************************/

#define LTE_FDD_ENB_MAX_HARQ_RETX 5

/*******************************************************************************
                              FORWARD DECLARATIONS
*******************************************************************************/


/*******************************************************************************
                              TYPEDEFS
*******************************************************************************/

typedef struct{
    LIBLTE_PHY_ALLOCATION_STRUCT dl_alloc;
    LIBLTE_PHY_ALLOCATION_STRUCT ul_alloc;
    LIBLTE_MAC_RAR_STRUCT        rar;
    uint32                       current_tti;
}LTE_FDD_ENB_RAR_SCHED_QUEUE_STRUCT;

typedef struct{
    LIBLTE_PHY_ALLOCATION_STRUCT alloc;
    LIBLTE_MAC_PDU_STRUCT        mac_pdu;
    uint32                       current_tti;
}LTE_FDD_ENB_DL_SCHED_QUEUE_STRUCT;

typedef struct{
    LIBLTE_PHY_ALLOCATION_STRUCT alloc;
    uint32                       current_tti;
}LTE_FDD_ENB_UL_SCHED_QUEUE_STRUCT;

typedef struct{
    uint32 i_sr;
    uint32 n_1_p_pucch;
    uint16 rnti;
}LTE_FDD_ENB_UL_SR_SCHED_QUEUE_STRUCT;

typedef struct{
    LIBLTE_PHY_ALLOCATION_STRUCT alloc;
    uint32                       next_tti;
    uint32                       tti_periodicity;
    uint32                       timer_id;
}LTE_FDD_ENB_PERSISTENT_DL_STRUCT;

/*******************************************************************************
                              CLASS DECLARATIONS
*******************************************************************************/

class LTE_fdd_enb_mac
{
public:
    LTE_fdd_enb_mac(LTE_fdd_enb_interface *iface, LTE_fdd_enb_timer_mgr *tm, LTE_fdd_enb_user_mgr *um, LTE_fdd_enb_rlc *_rlc);
    ~LTE_fdd_enb_mac();
    void set_phy_and_rrc(LTE_fdd_enb_phy *_phy, LTE_fdd_enb_rrc *_rrc);

    // Start/Stop
    void start(LTE_fdd_enb_msgq *from_phy, LTE_fdd_enb_msgq *from_rlc, LTE_fdd_enb_msgq *to_phy, LTE_fdd_enb_msgq *to_rlc, LTE_fdd_enb_msgq *to_timer, bool direct_to_ue);
    void stop();

    // External interface
    void align_ttis_with_phy(uint32 ul_current_tti);
    void update_sys_info();
    void add_periodic_sr_pucch(uint16 rnti, uint32 i_sr, uint32 n_1_p_pucch);
    void remove_periodic_sr_pucch(uint16 rnti);

    void send_dl_traffic(LTE_fdd_enb_user *user, LTE_fdd_enb_rb *rb, uint32 num_frames, uint32 size);

private:
    // Start/Stop
    std::mutex             start_mutex;
    LTE_fdd_enb_interface *interface;
    bool                   started;

    // Communication
    void handle_phy_msg(LTE_FDD_ENB_MESSAGE_STRUCT &msg);
    void handle_rlc_msg(LTE_FDD_ENB_MESSAGE_STRUCT &msg);
    void handle_ue_msg(LIBTOOLS_IPC_MSGQ_MESSAGE_STRUCT *msg);
    void send_rlc_pdu_ready(LTE_fdd_enb_user *user, LTE_fdd_enb_rb *rb, LIBLTE_BYTE_MSG_STRUCT *pdu);
    LTE_fdd_enb_msgq  *msgq_from_phy;
    LTE_fdd_enb_msgq  *msgq_from_rlc;
    LTE_fdd_enb_msgq  *msgq_to_phy;
    LTE_fdd_enb_msgq  *msgq_to_rlc;
    LTE_fdd_enb_msgq  *msgq_to_timer;
    libtools_ipc_msgq *msgq_to_ue;
    libtools_ipc_msgq *msgq_from_ue;

    // PHY Message Handlers
    void handle_ready_to_send(LTE_FDD_ENB_READY_TO_SEND_MSG_STRUCT *rts);
    void handle_prach_decode(LTE_FDD_ENB_PRACH_DECODE_MSG_STRUCT *prach_decode);
    void handle_pucch_decode(LTE_FDD_ENB_PUCCH_DECODE_MSG_STRUCT *pucch_decode);
    void handle_pucch_ack_nack(LTE_fdd_enb_user *user, uint32 current_tti, LIBLTE_BIT_MSG_STRUCT *msg);
    void handle_pucch_sr(LTE_fdd_enb_user *user, uint32 current_tti, LIBLTE_BIT_MSG_STRUCT *msg);
    void handle_pusch_decode(LTE_FDD_ENB_PUSCH_DECODE_MSG_STRUCT *pusch_decode);

    // RLC Message Handlers
    void handle_sdu_ready(LTE_FDD_ENB_MAC_SDU_READY_MSG_STRUCT *sdu_ready);

    // MAC PDU Handlers
    void handle_ulsch_ccch_sdu(LTE_fdd_enb_user *user, uint32 lcid, LIBLTE_BYTE_MSG_STRUCT *sdu);
    void handle_ulsch_dcch_sdu(LTE_fdd_enb_user *user, uint32 lcid, LIBLTE_BYTE_MSG_STRUCT *sdu);
    void handle_ulsch_ext_power_headroom_report(LTE_fdd_enb_user *user, LIBLTE_MAC_EXT_POWER_HEADROOM_CE_STRUCT *ext_power_headroom);
    void handle_ulsch_power_headroom_report(LTE_fdd_enb_user *user, LIBLTE_MAC_POWER_HEADROOM_CE_STRUCT *power_headroom);
    void handle_ulsch_c_rnti(LTE_fdd_enb_user **user, LIBLTE_MAC_C_RNTI_CE_STRUCT *c_rnti);
    void handle_ulsch_truncated_bsr(LTE_fdd_enb_user *user, LIBLTE_MAC_TRUNCATED_BSR_CE_STRUCT *truncated_bsr);
    void handle_ulsch_short_bsr(LTE_fdd_enb_user *user, LIBLTE_MAC_SHORT_BSR_CE_STRUCT *short_bsr);
    void handle_ulsch_long_bsr(LTE_fdd_enb_user *user, LIBLTE_MAC_LONG_BSR_CE_STRUCT *long_bsr);

    // Data Constructors
    void construct_random_access_response(uint8 preamble, uint16 timing_adv, uint32 current_tti);

    // Scheduler
    void sched_ul(LTE_fdd_enb_user *user, uint32 requested_tbs);
    void persistent_dl(LTE_FDD_ENB_PERSISTENT_DL_STRUCT *persistent_dl);
    void handle_persistent_dl_timer_expiry(uint32 timer_id);
    void rar_scheduler();
    void dl_scheduler();
    void ul_scheduler();
    void ul_sr_scheduler();
    LTE_FDD_ENB_ERROR_ENUM add_to_rar_sched_queue(uint32 current_tti, LIBLTE_PHY_ALLOCATION_STRUCT *dl_alloc, LIBLTE_PHY_ALLOCATION_STRUCT *ul_alloc, LIBLTE_MAC_RAR_STRUCT *rar);
    LTE_FDD_ENB_ERROR_ENUM add_to_dl_sched_queue(uint32 current_tti, LIBLTE_MAC_PDU_STRUCT *mac_pdu, LIBLTE_PHY_ALLOCATION_STRUCT *alloc);
    LTE_FDD_ENB_ERROR_ENUM add_to_ul_sched_queue(uint32 current_tti, LIBLTE_PHY_ALLOCATION_STRUCT *alloc);
    std::mutex                                       rar_sched_queue_mutex;
    std::mutex                                       dl_sched_queue_mutex;
    std::mutex                                       persistent_dl_queue_mutex;
    std::mutex                                       ul_sched_queue_mutex;
    std::mutex                                       ul_sr_sched_queue_mutex;
    std::list<LTE_FDD_ENB_RAR_SCHED_QUEUE_STRUCT*>   rar_sched_queue;
    std::list<LTE_FDD_ENB_DL_SCHED_QUEUE_STRUCT*>    dl_sched_queue;
    std::list<LTE_FDD_ENB_PERSISTENT_DL_STRUCT*>     persistent_dl_queue;
    std::list<LTE_FDD_ENB_UL_SCHED_QUEUE_STRUCT*>    ul_sched_queue;
    std::list<LTE_FDD_ENB_UL_SR_SCHED_QUEUE_STRUCT*> ul_sr_sched_queue;
    LTE_FDD_ENB_DL_SCHEDULE_MSG_STRUCT               sched_dl_subfr[10];
    LTE_FDD_ENB_UL_SCHEDULE_MSG_STRUCT               sched_ul_subfr[10];
    uint8                                            sched_cur_dl_subfn;
    uint8                                            sched_cur_ul_subfn;

    // Parameters
    LTE_fdd_enb_timer_mgr       *timer_mgr;
    LTE_fdd_enb_user_mgr        *user_mgr;
    LTE_fdd_enb_phy             *phy;
    LTE_fdd_enb_rlc             *rlc;
    LTE_fdd_enb_rrc             *rrc;
    std::mutex                   sys_info_mutex;
    LTE_FDD_ENB_SYS_INFO_STRUCT  sys_info;

    // Helpers
    void advance_tti_and_clear_subframe();
    uint32 get_n_reserved_prbs(uint32 current_tti);
    bool scheduling_headroom(LTE_FDD_ENB_DL_SCHEDULE_MSG_STRUCT *dl_subfr, LTE_FDD_ENB_UL_SCHEDULE_MSG_STRUCT *ul_subfr, uint32 N_dl_prbs, uint32 N_ul_prbs);
    LIBLTE_PHY_MODULATION_TYPE_ENUM get_modulation_type(uint8 mcs);
};

#endif /* __LTE_FDD_ENB_MAC_H__ */
