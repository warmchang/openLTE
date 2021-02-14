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

    File: LTE_fdd_enb_interface.h

    Description: Contains all the definitions for the LTE FDD eNodeB interface.

    Revision History
    ----------    -------------    --------------------------------------------
    11/09/2013    Ben Wojtowicz    Created file
    01/18/2014    Ben Wojtowicz    Added dynamic variables and added level to
                                   debug prints.
    03/26/2014    Ben Wojtowicz    Using the latest LTE library.
    04/12/2014    Ben Wojtowicz    Pulled in a patch from Max Suraev for more
                                   descriptive start failures.
    05/04/2014    Ben Wojtowicz    Added PCAP support and more error types.
    06/15/2014    Ben Wojtowicz    Added new error causes, ... support for info
                                   messages, and using the latest LTE library.
    07/22/2014    Ben Wojtowicz    Added clock source as a configurable
                                   parameter.
    08/03/2014    Ben Wojtowicz    Added HSS support.
    09/03/2014    Ben Wojtowicz    Added read only parameters for UL EARFCN,
                                   DL center frequency and UL center frequency.
    11/01/2014    Ben Wojtowicz    Added parameters for IP address assignment,
                                   DNS address, config file, and user file.
    11/29/2014    Ben Wojtowicz    Added support for the IP gateway.
    02/15/2015    Ben Wojtowicz    Moved to new message queue, added IP pcap
                                   support, and put error enum into common hdr.
    03/11/2015    Ben Wojtowicz    Made a common routine for formatting time.
    07/25/2015    Ben Wojtowicz    Made tx_gain and rx_gain into config file
                                   tracked parameters.
    12/06/2015    Ben Wojtowicz    Changed boost::mutex to sem_t.
    02/13/2016    Ben Wojtowicz    Added a command to print all registered
                                   users.
    07/29/2017    Ben Wojtowicz    Added input parameters for direct IPC to a UE
                                   and using the latest tools library.
    02/14/2021    Ben Wojtowicz    Massive reformat and using the new RRC
                                   library.

*******************************************************************************/

#ifndef __LTE_FDD_ENB_INTERFACE_H__
#define __LTE_FDD_ENB_INTERFACE_H__

/*******************************************************************************
                              INCLUDES
*******************************************************************************/

#include "LTE_fdd_enb_common.h"
#include "LTE_fdd_enb_msgq.h"
#include "liblte_common.h"
#include "libtools_server_socket.h"
#include <string>
#include <mutex>

/*******************************************************************************
                              DEFINES
*******************************************************************************/

#define LTE_FDD_ENB_CTRL_PORT     30000
#define LTE_FDD_ENB_MAX_LINE_SIZE 512

/*******************************************************************************
                              FORWARD DECLARATIONS
*******************************************************************************/

class LTE_fdd_enb_timer_mgr;
class LTE_fdd_enb_user_mgr;
class LTE_fdd_enb_hss;
class LTE_fdd_enb_gw;
class LTE_fdd_enb_mme;
class LTE_fdd_enb_rrc;
class LTE_fdd_enb_pdcp;
class LTE_fdd_enb_rlc;
class LTE_fdd_enb_mac;
class LTE_fdd_enb_phy;
class LTE_fdd_enb_radio;

/*******************************************************************************
                              TYPEDEFS
*******************************************************************************/

typedef enum{
    LTE_FDD_ENB_DEBUG_TYPE_ERROR = 0,
    LTE_FDD_ENB_DEBUG_TYPE_WARNING,
    LTE_FDD_ENB_DEBUG_TYPE_INFO,
    LTE_FDD_ENB_DEBUG_TYPE_DEBUG,
    LTE_FDD_ENB_DEBUG_TYPE_N_ITEMS,
}LTE_FDD_ENB_DEBUG_TYPE_ENUM;
static const char LTE_fdd_enb_debug_type_text[LTE_FDD_ENB_DEBUG_TYPE_N_ITEMS][100] = {"error",
                                                                                      "warning",
                                                                                      "info",
                                                                                      "debug"};

typedef enum{
    LTE_FDD_ENB_DEBUG_LEVEL_RADIO = 0,
    LTE_FDD_ENB_DEBUG_LEVEL_PHY,
    LTE_FDD_ENB_DEBUG_LEVEL_MAC,
    LTE_FDD_ENB_DEBUG_LEVEL_RLC,
    LTE_FDD_ENB_DEBUG_LEVEL_PDCP,
    LTE_FDD_ENB_DEBUG_LEVEL_RRC,
    LTE_FDD_ENB_DEBUG_LEVEL_MME,
    LTE_FDD_ENB_DEBUG_LEVEL_GW,
    LTE_FDD_ENB_DEBUG_LEVEL_USER,
    LTE_FDD_ENB_DEBUG_LEVEL_RB,
    LTE_FDD_ENB_DEBUG_LEVEL_TIMER,
    LTE_FDD_ENB_DEBUG_LEVEL_IFACE,
    LTE_FDD_ENB_DEBUG_LEVEL_MSGQ,
    LTE_FDD_ENB_DEBUG_LEVEL_N_ITEMS,
}LTE_FDD_ENB_DEBUG_LEVEL_ENUM;
static const char LTE_fdd_enb_debug_level_text[LTE_FDD_ENB_DEBUG_LEVEL_N_ITEMS][100] = {"radio",
                                                                                        "phy",
                                                                                        "mac",
                                                                                        "rlc",
                                                                                        "pdcp",
                                                                                        "rrc",
                                                                                        "mme",
                                                                                        "gw",
                                                                                        "user",
                                                                                        "rb",
                                                                                        "timer",
                                                                                        "iface",
                                                                                        "msgq"};

typedef enum{
    LTE_FDD_ENB_PCAP_DIRECTION_UL = 0,
    LTE_FDD_ENB_PCAP_DIRECTION_DL,
    LTE_FDD_ENB_PCAP_DIRECTION_N_ITEMS,
}LTE_FDD_ENB_PCAP_DIRECTION_ENUM;
static const char LTE_fdd_enb_pcap_direction_text[LTE_FDD_ENB_PCAP_DIRECTION_N_ITEMS][20] = {"UL",
                                                                                             "DL"};

typedef struct{
    MasterInformationBlock                    mib;
    SystemInformationBlockType1               sib1;
    SystemInformationBlockType2               sib2;
    SystemInformationBlockType3               sib3;
    SystemInformationBlockType4               sib4;
    SystemInformationBlockType5               sib5;
    SystemInformationBlockType6               sib6;
    SystemInformationBlockType7               sib7;
    SystemInformationBlockType8               sib8;
    std::vector<LIBLTE_PHY_ALLOCATION_STRUCT> sib_alloc;
}LTE_FDD_ENB_SYS_INFO_STRUCT;

/*******************************************************************************
                              CLASS DECLARATIONS
*******************************************************************************/

class LTE_fdd_enb_interface
{
public:
    LTE_fdd_enb_interface();
    ~LTE_fdd_enb_interface();

    // Communication
    void start_ports();
    void stop_ports();
    void send_ctrl_msg(std::string msg);
    void send_ctrl_info_msg(std::string msg, ...);
    void send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ENUM type, LTE_FDD_ENB_DEBUG_LEVEL_ENUM level, std::string file_name, int32 line, std::string msg, ...);
    void send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ENUM type, LTE_FDD_ENB_DEBUG_LEVEL_ENUM level, std::string file_name, int32 line, LIBLTE_BIT_MSG_STRUCT *lte_msg, std::string msg, ...);
    void send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ENUM type, LTE_FDD_ENB_DEBUG_LEVEL_ENUM level, std::string file_name, int32 line, std::vector<bool> &lte_msg, std::string msg, ...);
    void send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ENUM type, LTE_FDD_ENB_DEBUG_LEVEL_ENUM level, std::string file_name, int32 line, LIBLTE_BYTE_MSG_STRUCT *lte_msg, std::string msg, ...);
    void send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ENUM type, LTE_FDD_ENB_DEBUG_LEVEL_ENUM level, std::string file_name, int32 line, const std::vector<uint8_t> &lte_msg, std::string msg, ...);
    void open_lte_pcap_fd();
    void open_ip_pcap_fd();
    void send_lte_pcap_msg(LTE_FDD_ENB_PCAP_DIRECTION_ENUM dir, uint32 rnti, uint32 current_tti, uint8 *msg, uint32 N_bits);
    void send_ip_pcap_msg(uint8 *msg, uint32 N_bytes);
    void handle_ctrl_msg(const std::string msg, const int32 sock_fd);
    void handle_ctrl_connect(const int32 sock_fd);
    void handle_ctrl_disconnect(const int32 sock_fd);
    void handle_ctrl_error(const LIBTOOLS_SERVER_SOCKET_ERROR_ENUM err);
    void handle_debug_msg(const std::string msg, const int32 sock_fd);
    void handle_debug_connect(const int32 sock_fd);
    void handle_debug_disconnect(const int32 sock_fd);
    void handle_debug_error(const LIBTOOLS_SERVER_SOCKET_ERROR_ENUM err);

    // Handlers
    MasterInformationBlock::dl_Bandwidth_Enum get_bandwidth();
    uint32 get_band();
    uint16 get_dl_earfcn();
    uint16 get_ul_earfcn();
    uint32 get_n_rb_dl();
    uint32 get_n_rb_ul();
    uint32 get_dl_center_freq();
    uint32 get_ul_center_freq();
    uint32 get_n_sc_rb_dl();
    uint32 get_n_sc_rb_ul();
    uint8 get_n_ant();
    uint16 get_n_id_cell();
    uint8 get_n_id_1();
    uint8 get_n_id_2();
    const MCC& get_mcc();
    const MNC& get_mnc();
    uint32 get_cell_id();
    uint16 get_tracking_area_code();
    int16 get_q_rx_lev_min();
    uint16 get_si_periodicity();
    uint8 get_si_window_length();
    uint8 get_ra_response_window_size();
    int8 get_p0_nominal_pusch();
    int8 get_p0_nominal_pucch();
    bool get_sib3_present();
    SystemInformationBlockType3::cellReselectionInfoCommon::q_Hyst_Enum get_q_hyst();
    bool get_sib4_present();
    bool get_sib5_present();
    bool get_sib6_present();
    bool get_sib7_present();
    bool get_sib8_present();
    bool get_mac_direct_to_ue();
    bool get_phy_direct_to_ue();
    uint32 get_debug_type();
    uint32 get_debug_level();
    bool get_enable_pcap();
    uint32 get_ip_addr_start();
    uint32 get_dns_addr();
    bool get_use_cnfg_file();
    bool get_use_user_file();
    int set_use_user_file(std::string _use_user_file);
    void handle_add_user(std::string msg);
    void read_cnfg_file();
    bool get_shutdown();
    bool app_is_started();
    void construct_sys_info();
    void get_sys_info(LTE_FDD_ENB_SYS_INFO_STRUCT &_sys_info);
    void get_rrc_phy_cnfg_ded(PhysicalConfigDedicated *pcd, uint32 i_cqi_pmi, uint32 i_ri, uint32 i_sr, uint32 n_1_p_pucch);

private:
    // Communication
    void start_ctrl_port();
    void start_debug_port();
    void stop_ctrl_port();
    void stop_debug_port();
    std::mutex              ctrl_mutex;
    std::mutex              debug_mutex;
    FILE                   *lte_pcap_fd;
    FILE                   *ip_pcap_fd;
    libtools_server_socket *ctrl_socket;
    libtools_server_socket *debug_socket;
    int32                   ctrl_sock_fd;
    int32                   debug_sock_fd;
    bool                    ctrl_connected;
    bool                    debug_connected;

    // Handlers
    void handle_read(std::string msg);
    void handle_write(std::string msg);
    std::string get_bandwidth_string();
    int set_bandwidth(std::string bandwidth);
    int set_band(std::string band);
    int set_dl_earfcn(std::string _dl_earfcn);
    int set_n_ant(std::string _N_ant);
    int set_n_id_cell(std::string _N_id_cell);
    std::string get_mcc_string();
    int set_mcc(std::string mcc);
    std::string get_mnc_string();
    int set_mnc(std::string mnc);
    int set_cell_id(std::string cell_id);
    int set_tracking_area_code(std::string tracking_area_code);
    int set_q_rx_lev_min(std::string q_rx_lev_min);
    std::string get_si_periodicity_string();
    int set_si_periodicity(std::string si_periodicity);
    std::string get_si_window_length_string();
    int set_si_window_length(std::string si_window_length);
    int set_p0_nominal_pusch(std::string p0_nominal_pusch);
    int set_p0_nominal_pucch(std::string p0_nominal_pucch);
    std::string get_sib3_present_string();
    int set_sib3_present(std::string _sib3_present);
    std::string get_q_hyst_string();
    int set_q_hyst(std::string q_hyst);
    std::string get_sib4_present_string();
    int set_sib4_present(std::string _sib4_present);
    std::string get_sib5_present_string();
    int set_sib5_present(std::string _sib5_present);
    std::string get_sib6_present_string();
    int set_sib6_present(std::string _sib6_present);
    std::string get_sib7_present_string();
    int set_sib7_present(std::string _sib7_present);
    std::string get_sib8_present_string();
    int set_sib8_present(std::string _sib8_present);
    std::string get_mac_direct_to_ue_string();
    int set_mac_direct_to_ue(std::string _mac_direct_to_ue);
    std::string get_phy_direct_to_ue_string();
    int set_phy_direct_to_ue(std::string _phy_direct_to_ue);
    std::string get_debug_type_string();
    int set_debug_type(std::string _debug_type);
    std::string get_debug_level_string();
    int set_debug_level(std::string _debug_level);
    std::string get_enable_pcap_string();
    int set_enable_pcap(std::string _enable_pcap);
    std::string get_ip_addr_start_string();
    int set_ip_addr_start(std::string _ip_addr_start);
    std::string get_dns_addr_string();
    int set_dns_addr(std::string _dns_addr);
    std::string get_use_cnfg_file_string();
    int set_use_cnfg_file(std::string _use_cnfg_file);
    std::string get_use_user_file_string();
    std::string bool_to_enable_string(bool value);
    bool enable_string_to_bool(std::string enable);
    void handle_start();
    void handle_stop();
    void handle_help();
    void handle_delete_user(std::string msg);
    void handle_print_users();
    void handle_print_registered_users();
    void write_cnfg_file();
    void delete_cnfg_file();

    // Variables
    const std::string            shutdown_token;
    const std::string            start_token;
    const std::string            stop_token;
    const std::string            construct_si_token;
    const std::string            add_user_token;
    const std::string            delete_user_token;
    const std::string            print_users_token;
    const std::string            print_registered_users_token;
    const std::string            read_token;
    const std::string            write_token;
    const std::string            help_token;
    const std::string            bandwidth_token;
    const std::string            band_token;
    const std::string            dl_earfcn_token;
    const std::string            n_ant_token;
    const std::string            n_id_cell_token;
    const std::string            mcc_token;
    const std::string            mnc_token;
    const std::string            cell_id_token;
    const std::string            tracking_area_code_token;
    const std::string            q_rx_lev_min_token;
    const std::string            si_periodicity_token;
    const std::string            si_window_length_token;
    const std::string            p0_nominal_pusch_token;
    const std::string            p0_nominal_pucch_token;
    const std::string            sib3_present_token;
    const std::string            q_hyst_token;
    const std::string            sib4_present_token;
    const std::string            sib5_present_token;
    const std::string            sib6_present_token;
    const std::string            sib7_present_token;
    const std::string            sib8_present_token;
    const std::string            mac_direct_to_ue_token;
    const std::string            phy_direct_to_ue_token;
    const std::string            debug_type_token;
    const std::string            debug_level_token;
    const std::string            enable_pcap_token;
    const std::string            ip_addr_start_token;
    const std::string            dns_addr_token;
    const std::string            use_cnfg_file_token;
    const std::string            use_user_file_token;
    const std::string            available_radios_token;
    const std::string            selected_radio_name_token;
    const std::string            selected_radio_idx_token;
    const std::string            clock_source_token;
    const std::string            tx_gain_token;
    const std::string            rx_gain_token;
    const std::string            imsi_token;
    const std::string            imei_token;
    const std::string            k_token;
    LTE_fdd_enb_timer_mgr       *timer_mgr;
    LTE_fdd_enb_user_mgr        *user_mgr;
    LTE_fdd_enb_hss             *hss;
    LTE_fdd_enb_gw              *gw;
    LTE_fdd_enb_mme             *mme;
    LTE_fdd_enb_rrc             *rrc;
    LTE_fdd_enb_pdcp            *pdcp;
    LTE_fdd_enb_rlc             *rlc;
    LTE_fdd_enb_mac             *mac;
    LTE_fdd_enb_phy             *phy;
    LTE_fdd_enb_radio           *radio;
    LTE_FDD_ENB_SYS_INFO_STRUCT  sys_info;
    std::mutex                   start_mutex;
    uint32                       N_rb_dl;
    uint32                       N_rb_ul;
    uint32                       dl_center_freq;
    uint32                       ul_center_freq;
    const uint32                 N_sc_rb_dl;
    const uint32                 N_sc_rb_ul;
    uint32                       debug_type;
    uint32                       debug_level;
    uint32                       ip_addr_start;
    uint32                       dns_addr;
    uint16                       N_id_cell;
    uint16                       dl_earfcn;
    uint16                       ul_earfcn;
    uint8                        N_ant;
    uint8                        N_id_1;
    uint8                        N_id_2;
    bool                         shutdown;
    bool                         started;
    bool                         sib3_present;
    bool                         sib4_present;
    bool                         sib5_present;
    bool                         sib6_present;
    bool                         sib7_present;
    bool                         sib8_present;
    bool                         mac_direct_to_ue;
    bool                         phy_direct_to_ue;
    bool                         enable_pcap;
    bool                         use_cnfg_file;
    bool                         use_user_file;


    // Inter-stack communication
    LTE_fdd_enb_msgq *phy_to_mac_comm;
    LTE_fdd_enb_msgq *mac_to_phy_comm;
    LTE_fdd_enb_msgq *mac_to_rlc_comm;
    LTE_fdd_enb_msgq *mac_to_timer_comm;
    LTE_fdd_enb_msgq *rlc_to_mac_comm;
    LTE_fdd_enb_msgq *rlc_to_pdcp_comm;
    LTE_fdd_enb_msgq *pdcp_to_rlc_comm;
    LTE_fdd_enb_msgq *pdcp_to_rrc_comm;
    LTE_fdd_enb_msgq *rrc_to_pdcp_comm;
    LTE_fdd_enb_msgq *rrc_to_mme_comm;
    LTE_fdd_enb_msgq *mme_to_rrc_comm;
    LTE_fdd_enb_msgq *pdcp_to_gw_comm;
    LTE_fdd_enb_msgq *gw_to_pdcp_comm;
};

#endif /* __LTE_FDD_ENB_INTERFACE_H__ */
