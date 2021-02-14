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

    File: LTE_fdd_enb_phy.h

    Description: Contains all the definitions for the LTE FDD eNodeB
                 physical layer.

    Revision History
    ----------    -------------    --------------------------------------------
    11/09/2013    Ben Wojtowicz    Created file
    01/18/2014    Ben Wojtowicz    Cached a copy of the interface class and
                                   added the ability to handle late subframes.
    05/04/2014    Ben Wojtowicz    Added PHICH support.
    06/15/2014    Ben Wojtowicz    Changed fn_combo to current_tti.
    12/16/2014    Ben Wojtowicz    Added ol extension to message queue.
    02/15/2015    Ben Wojtowicz    Moved to new message queue.
    07/25/2015    Ben Wojtowicz    Combined the DL and UL schedule messages into
                                   a single PHY schedule message.
    12/06/2015    Ben Wojtowicz    Changed boost::mutex to sem_t.
    07/31/2016    Ben Wojtowicz    Added an external interface for getting the
                                   current TTIs.
    07/29/2017    Ben Wojtowicz    Added IPC direct to a UE PHY.
    02/14/2021    Ben Wojtowicz    Massive reformat.

*******************************************************************************/

#ifndef __LTE_FDD_ENB_PHY_H__
#define __LTE_FDD_ENB_PHY_H__

/*******************************************************************************
                              INCLUDES
*******************************************************************************/

#include "LTE_fdd_enb_interface.h"
#include "LTE_fdd_enb_msgq.h"
#include "LTE_fdd_enb_radio.h"
#include "LTE_fdd_enb_mac.h"
#include "liblte_phy.h"
#include <mutex>

/*******************************************************************************
                              DEFINES
*******************************************************************************/


/*******************************************************************************
                              FORWARD DECLARATIONS
*******************************************************************************/


/*******************************************************************************
                              TYPEDEFS
*******************************************************************************/


/*******************************************************************************
                              CLASS DECLARATIONS
*******************************************************************************/

class LTE_fdd_enb_phy
{
public:
    LTE_fdd_enb_phy(LTE_fdd_enb_interface *iface, LTE_fdd_enb_mac *_mac);
    ~LTE_fdd_enb_phy();

    // Start/Stop
    void start(LTE_fdd_enb_msgq *from_mac, LTE_fdd_enb_msgq *to_mac, bool direct_to_ue, LTE_fdd_enb_radio *_radio);
    void stop(void);

    // External interface
    void update_sys_info(void);
    uint32 get_n_cce(void);

    // Radio interface
    void radio_interface(LTE_FDD_ENB_RADIO_TX_BUF_STRUCT *tx_buf, LTE_FDD_ENB_RADIO_RX_BUF_STRUCT *rx_buf);
    void radio_interface(LTE_FDD_ENB_RADIO_TX_BUF_STRUCT *tx_buf);

private:
    // Start/Stop
    LTE_fdd_enb_interface *interface;
    bool                   started;

    // Communication
    void handle_mac_msg(LTE_FDD_ENB_MESSAGE_STRUCT &msg);
    void handle_ue_msg(LIBTOOLS_IPC_MSGQ_MESSAGE_STRUCT *msg);
    LTE_fdd_enb_msgq  *msgq_from_mac;
    LTE_fdd_enb_msgq  *msgq_to_mac;
    libtools_ipc_msgq *msgq_to_ue;

    // Generic
    void align_ttis_with_radio(uint32 radio_ul_tti);
    LIBLTE_PHY_STRUCT *phy_struct;

    // Downlink
    void handle_phy_schedule(LTE_FDD_ENB_PHY_SCHEDULE_MSG_STRUCT *phy_sched);
    void process_pss_sss();
    void process_pbch(uint32 sfn);
    void process_pdcch_and_pdsch();
    void process_dl(LTE_FDD_ENB_RADIO_TX_BUF_STRUCT *tx_buf);
    LTE_fdd_enb_radio                  *radio;
    LTE_fdd_enb_mac                    *mac;
    std::mutex                          sys_info_mutex;
    std::mutex                          dl_sched_mutex;
    std::mutex                          ul_sched_mutex;
    LTE_FDD_ENB_SYS_INFO_STRUCT         sys_info;
    LTE_FDD_ENB_DL_SCHEDULE_MSG_STRUCT  dl_schedule[10];
    LTE_FDD_ENB_UL_SCHEDULE_MSG_STRUCT  ul_schedule[10];
    LIBLTE_PHY_PCFICH_STRUCT            pcfich;
    LIBLTE_PHY_PHICH_STRUCT             phich[10];
    LIBLTE_PHY_SUBFRAME_STRUCT          dl_subframe;
    LIBLTE_BIT_MSG_STRUCT               dl_rrc_msg;
    uint32                              dl_current_tti;

    // Uplink
    void process_prach(LTE_FDD_ENB_RADIO_RX_BUF_STRUCT *rx_buf, uint32 sfn);
    void process_pucch();
    void process_pusch();
    void process_ul(LTE_FDD_ENB_RADIO_RX_BUF_STRUCT *rx_buf);
    LTE_FDD_ENB_PRACH_DECODE_MSG_STRUCT prach_decode;
    LTE_FDD_ENB_PUCCH_DECODE_MSG_STRUCT pucch_decode;
    LTE_FDD_ENB_PUSCH_DECODE_MSG_STRUCT pusch_decode;
    LIBLTE_PHY_SUBFRAME_STRUCT          ul_subframe;
    uint32                              ul_current_tti;
    uint32                              prach_sfn_mod;
    uint32                              prach_subfn_mod;
    uint32                              prach_subfn_check;
    bool                                prach_subfn_zero_allowed;
};

#endif /* __LTE_FDD_ENB_PHY_H__ */
