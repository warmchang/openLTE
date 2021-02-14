#line 2 "LTE_fdd_enb_interface.cc" // Make __FILE__ omit the path
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

    File: LTE_fdd_enb_interface.cc

    Description: Contains all the implementations for the LTE FDD eNodeB
                 interface.

    Revision History
    ----------    -------------    --------------------------------------------
    11/09/2013    Ben Wojtowicz    Created file
    01/18/2014    Ben Wojtowicz    Added dynamic variable support, added level
                                   to debug prints, fixed usec time in debug
                                   prints, and added uint32 variables.
    03/26/2014    Ben Wojtowicz    Added message printing.
    05/04/2014    Ben Wojtowicz    Added PCAP support.
    06/15/2014    Ben Wojtowicz    Added  ... support for info messages and
                                   using the latest LTE library.
    07/22/2014    Ben Wojtowicz    Added clock source as a configurable
                                   parameter.
    08/03/2014    Ben Wojtowicz    Added HSS support.
    09/03/2014    Ben Wojtowicz    Added read only parameters for UL EARFCN,
                                   DL center frequency and UL center frequency.
    11/01/2014    Ben Wojtowicz    Added parameters for IP address assignment,
                                   DNS address, config file, and user file.
    11/29/2014    Ben Wojtowicz    Added support for the IP gateway.
    12/16/2014    Ben Wojtowicz    Added ol extension to message queues.
    02/15/2015    Ben Wojtowicz    Moved to new message queue, added IP pcap
                                   support, and added UTC time to the log port.
    03/11/2015    Ben Wojtowicz    Made a common routine for formatting time.
    07/25/2015    Ben Wojtowicz    Added config file support for TX/RX gains.
    12/06/2015    Ben Wojtowicz    Changed boost::mutex to pthread_mutex_t and
                                   sem_t.
    02/13/2016    Ben Wojtowicz    Added a command to print all registered
                                   users.
    07/29/2017    Ben Wojtowicz    Added input parameters for direct IPC to a UE
                                   and using the latest tools library.
    02/14/2021    Ben Wojtowicz    Massive reformat and using the new RRC
                                   library.

*******************************************************************************/

/*******************************************************************************
                              INCLUDES
*******************************************************************************/

#include "LTE_fdd_enb_interface.h"
#include "LTE_fdd_enb_user_mgr.h"
#include "LTE_fdd_enb_hss.h"
#include "LTE_fdd_enb_gw.h"
#include "LTE_fdd_enb_mme.h"
#include "LTE_fdd_enb_rrc.h"
#include "LTE_fdd_enb_pdcp.h"
#include "LTE_fdd_enb_rlc.h"
#include "LTE_fdd_enb_mac.h"
#include "LTE_fdd_enb_phy.h"
#include "LTE_fdd_enb_radio.h"
#include "LTE_fdd_enb_timer_mgr.h"
#include "liblte_interface.h"
#include "libtools_helpers.h"
#include <boost/lexical_cast.hpp>
#include <arpa/inet.h>
#include <sys/time.h>
#include <stdarg.h>

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
LTE_fdd_enb_interface::LTE_fdd_enb_interface() :
    ctrl_socket{NULL}, debug_socket{NULL}, ctrl_connected{false}, debug_connected{false},
    shutdown_token{"shutdown"}, start_token{"start"}, stop_token{"stop"},
    construct_si_token{"construct_si"}, add_user_token{"add_user"},
    delete_user_token{"delete_user"}, print_users_token{"print_users"},
    print_registered_users_token{"print_registered_users"},
    read_token{"read"}, write_token{"write"}, help_token{"help"}, bandwidth_token{"bandwidth"},
    band_token{"band"}, dl_earfcn_token{"dl_earfcn"}, n_ant_token{"n_ant"},
    n_id_cell_token{"n_id_cell"}, mcc_token{"mcc"}, mnc_token{"mnc"},
    cell_id_token{"cell_id"}, tracking_area_code_token{"tracking_area_code"},
    q_rx_lev_min_token{"q_rx_lev_min"}, si_periodicity_token{"si_periodicity"},
    si_window_length_token{"si_window_length"}, p0_nominal_pusch_token{"p0_nominal_pusch"},
    p0_nominal_pucch_token{"p0_nominal_pucch"}, sib3_present_token{"sib3_present"},
    q_hyst_token{"q_hyst"}, sib4_present_token{"sib4_present"},
    sib5_present_token{"sib5_present"}, sib6_present_token{"sib6_present"},
    sib7_present_token{"sib7_present"}, sib8_present_token{"sib8_present"},
    mac_direct_to_ue_token{"mac_direct_to_ue"}, phy_direct_to_ue_token{"phy_direct_to_ue"},
    debug_type_token{"debug_type"}, debug_level_token{"debug_level"},
    enable_pcap_token{"enable_pcap"}, ip_addr_start_token{"ip_addr_start"},
    dns_addr_token{"dns_addr"}, use_cnfg_file_token{"use_cnfg_file"},
    use_user_file_token{"use_user_file"}, available_radios_token{"available_radios"},
    selected_radio_name_token{"selected_radio_name"},
    selected_radio_idx_token{"selected_radio_idx"}, clock_source_token{"clock_source"},
    tx_gain_token{"tx_gain"}, rx_gain_token{"rx_gain"}, imsi_token{"imsi"}, imei_token{"imei"},
    k_token{"k"}, timer_mgr{new LTE_fdd_enb_timer_mgr(this)},
    user_mgr{new LTE_fdd_enb_user_mgr(this, timer_mgr)}, hss{new LTE_fdd_enb_hss()},
    gw{new LTE_fdd_enb_gw(this, user_mgr)}, mme{new LTE_fdd_enb_mme(this, user_mgr, hss)},
    pdcp{new LTE_fdd_enb_pdcp(this)}, rlc{new LTE_fdd_enb_rlc(this)},
    mac{new LTE_fdd_enb_mac(this, timer_mgr, user_mgr, rlc)},
    phy{new LTE_fdd_enb_phy(this, mac)}, radio{new LTE_fdd_enb_radio(this, phy)},
    N_rb_dl{LIBLTE_PHY_N_RB_DL_10MHZ}, N_rb_ul{LIBLTE_PHY_N_RB_UL_10MHZ},
    dl_center_freq{liblte_interface_dl_earfcn_to_frequency(liblte_interface_first_dl_earfcn[0])},
    ul_center_freq{liblte_interface_dl_earfcn_to_frequency(liblte_interface_get_corresponding_ul_earfcn(liblte_interface_first_dl_earfcn[0]))},
    N_sc_rb_dl{LIBLTE_PHY_N_SC_RB_DL_NORMAL_CP}, N_sc_rb_ul{LIBLTE_PHY_N_SC_RB_UL},
    debug_type{0xFFFFFFFF}, debug_level{0xFFFFFFFF}, ip_addr_start{0xC0A80102},
    dns_addr{0xC0A80101}, N_id_cell{0}, dl_earfcn{liblte_interface_first_dl_earfcn[0]},
    ul_earfcn{liblte_interface_get_corresponding_ul_earfcn(dl_earfcn)}, N_ant{1},
    N_id_1{0}, N_id_2{0}, shutdown{false}, started{false}, sib3_present{false},
    sib4_present{false}, sib5_present{false}, sib6_present{false}, sib7_present{false},
    sib8_present{false}, mac_direct_to_ue{false}, phy_direct_to_ue{false},
    enable_pcap{false}, use_cnfg_file{false}, use_user_file{false}
{
    rrc = new LTE_fdd_enb_rrc(this, user_mgr, mac);
    mac->set_phy_and_rrc(phy, rrc);

    // MIB
    sys_info.mib.dl_Bandwidth_SetValue(MasterInformationBlock::k_dl_Bandwidth_n50);
    sys_info.mib.phich_Config_Set()->phich_Duration_SetValue(PHICH_Config::k_phich_Duration_normal);
    sys_info.mib.phich_Config_Set()->phich_Resource_SetValue(PHICH_Config::k_phich_Resource_one);
    sys_info.mib.systemFrameNumber_SetValue(0);
    sys_info.mib.spare_SetValue(0);
    // SIB1
    std::vector<MCC_MNC_Digit> mcc(3);
    mcc[0].SetValue(0);
    mcc[1].SetValue(0);
    mcc[2].SetValue(1);
    std::vector<PLMN_IdentityInfo> plmn_id(1);
    plmn_id[0].plmn_Identity_Set()->mcc_Set()->SetValue(mcc);
    std::vector<MCC_MNC_Digit> mnc(2);
    mnc[0].SetValue(0);
    mnc[1].SetValue(1);
    plmn_id[0].plmn_Identity_Set()->mnc_Set()->SetValue(mnc);
    plmn_id[0].cellReservedForOperatorUse_SetValue(PLMN_IdentityInfo::k_cellReservedForOperatorUse_notReserved);
    sys_info.sib1.cellAccessRelatedInfo_value.plmn_IdentityList_Set()->SetValue(plmn_id);
    sys_info.sib1.cellAccessRelatedInfo_value.trackingAreaCode_Set()->SetValue(0);
    sys_info.sib1.cellAccessRelatedInfo_value.cellIdentity_Set()->SetValue(0);
    sys_info.sib1.cellAccessRelatedInfo_value.cellBarred_SetValue(SystemInformationBlockType1::cellAccessRelatedInfo::k_cellBarred_notBarred);
    sys_info.sib1.cellAccessRelatedInfo_value.intraFreqReselection_SetValue(SystemInformationBlockType1::cellAccessRelatedInfo::k_intraFreqReselection_allowed);
    sys_info.sib1.cellAccessRelatedInfo_value.csg_Indication_SetValue(false);
    sys_info.sib1.cellAccessRelatedInfo_value.csg_Identity_Clear();
    sys_info.sib1.cellSelectionInfo_value.q_RxLevMin_Set()->SetValue(-70);
    sys_info.sib1.cellSelectionInfo_value.q_RxLevMinOffset_SetValue(1);
    sys_info.sib1.p_Max_Set()->SetValue(23);
    sys_info.sib1.freqBandIndicator_SetValue(1);
    std::vector<SchedulingInfo> sched_info(1);
    sched_info[0].si_Periodicity_SetValue(SchedulingInfo::k_si_Periodicity_rf8);
    sched_info[0].sib_MappingInfo_Set()->SetValue({});
    sys_info.sib1.schedulingInfoList_Set()->SetValue(sched_info);
    sys_info.sib1.tdd_Config_Clear();
    sys_info.sib1.si_WindowLength_SetValue(SystemInformationBlockType1::k_si_WindowLength_ms1);
    sys_info.sib1.systemInfoValueTag_SetValue(0);
    sys_info.sib1.nonCriticalExtension_Clear();
    // SIB2
    sys_info.sib2.ac_BarringInfo_value.Clear();
    sys_info.sib2.radioResourceConfigCommon_Set()->rach_ConfigCommon_Set()->preambleInfo_value.numberOfRA_Preambles_SetValue(RACH_ConfigCommon::preambleInfo::k_numberOfRA_Preambles_n4);
    sys_info.sib2.radioResourceConfigCommon_Set()->rach_ConfigCommon_Set()->preambleInfo_value.preamblesGroupAConfig_value.Clear();
    sys_info.sib2.radioResourceConfigCommon_Set()->rach_ConfigCommon_Set()->powerRampingParameters_value.powerRampingStep_SetValue(RACH_ConfigCommon::powerRampingParameters::k_powerRampingStep_dB6);
    sys_info.sib2.radioResourceConfigCommon_Set()->rach_ConfigCommon_Set()->powerRampingParameters_value.preambleInitialReceivedTargetPower_SetValue(RACH_ConfigCommon::powerRampingParameters::k_preambleInitialReceivedTargetPower_dBm_90);
    sys_info.sib2.radioResourceConfigCommon_Set()->rach_ConfigCommon_Set()->ra_SupervisionInfo_value.preambleTransMax_SetValue(RACH_ConfigCommon::ra_SupervisionInfo::k_preambleTransMax_n200);
    sys_info.sib2.radioResourceConfigCommon_Set()->rach_ConfigCommon_Set()->ra_SupervisionInfo_value.ra_ResponseWindowSize_SetValue(RACH_ConfigCommon::ra_SupervisionInfo::k_ra_ResponseWindowSize_sf7);
    sys_info.sib2.radioResourceConfigCommon_Set()->rach_ConfigCommon_Set()->ra_SupervisionInfo_value.mac_ContentionResolutionTimer_SetValue(RACH_ConfigCommon::ra_SupervisionInfo::k_mac_ContentionResolutionTimer_sf64);
    sys_info.sib2.radioResourceConfigCommon_Set()->rach_ConfigCommon_Set()->maxHARQ_Msg3Tx_SetValue(1);
    sys_info.sib2.radioResourceConfigCommon_Set()->bcch_Config_Set()->modificationPeriodCoeff_SetValue(BCCH_Config::k_modificationPeriodCoeff_n2);
    sys_info.sib2.radioResourceConfigCommon_Set()->pcch_Config_Set()->defaultPagingCycle_SetValue(PCCH_Config::k_defaultPagingCycle_rf256);
    sys_info.sib2.radioResourceConfigCommon_Set()->pcch_Config_Set()->nB_SetValue(PCCH_Config::k_nB_oneT);
    sys_info.sib2.radioResourceConfigCommon_Set()->prach_Config_Set()->rootSequenceIndex_SetValue(0);
    sys_info.sib2.radioResourceConfigCommon_Set()->prach_Config_Set()->prach_ConfigInfo_Set()->prach_ConfigIndex_SetValue(0);
    sys_info.sib2.radioResourceConfigCommon_Set()->prach_Config_Set()->prach_ConfigInfo_Set()->highSpeedFlag_SetValue(false);
    sys_info.sib2.radioResourceConfigCommon_Set()->prach_Config_Set()->prach_ConfigInfo_Set()->zeroCorrelationZoneConfig_SetValue(1);
    sys_info.sib2.radioResourceConfigCommon_Set()->prach_Config_Set()->prach_ConfigInfo_Set()->prach_FreqOffset_SetValue(0);
    sys_info.sib2.radioResourceConfigCommon_Set()->pdsch_ConfigCommon_Set()->referenceSignalPower_SetValue(0);
    sys_info.sib2.radioResourceConfigCommon_Set()->pdsch_ConfigCommon_Set()->p_b_SetValue(0);
    sys_info.sib2.radioResourceConfigCommon_Set()->pusch_ConfigCommon_Set()->pusch_ConfigBasic_value.n_SB_SetValue(1);
    sys_info.sib2.radioResourceConfigCommon_Set()->pusch_ConfigCommon_Set()->pusch_ConfigBasic_value.hoppingMode_SetValue(PUSCH_ConfigCommon::pusch_ConfigBasic::k_hoppingMode_interSubFrame);
    sys_info.sib2.radioResourceConfigCommon_Set()->pusch_ConfigCommon_Set()->pusch_ConfigBasic_value.pusch_HoppingOffset_SetValue(0);
    sys_info.sib2.radioResourceConfigCommon_Set()->pusch_ConfigCommon_Set()->pusch_ConfigBasic_value.enable64QAM_SetValue(true);
    sys_info.sib2.radioResourceConfigCommon_Set()->pusch_ConfigCommon_Set()->ul_ReferenceSignalsPUSCH_Set()->groupHoppingEnabled_SetValue(false);
    sys_info.sib2.radioResourceConfigCommon_Set()->pusch_ConfigCommon_Set()->ul_ReferenceSignalsPUSCH_Set()->groupAssignmentPUSCH_SetValue(0);
    sys_info.sib2.radioResourceConfigCommon_Set()->pusch_ConfigCommon_Set()->ul_ReferenceSignalsPUSCH_Set()->sequenceHoppingEnabled_SetValue(false);
    sys_info.sib2.radioResourceConfigCommon_Set()->pusch_ConfigCommon_Set()->ul_ReferenceSignalsPUSCH_Set()->cyclicShift_SetValue(0);
    sys_info.sib2.radioResourceConfigCommon_Set()->pucch_ConfigCommon_Set()->deltaPUCCH_Shift_SetValue(PUCCH_ConfigCommon::k_deltaPUCCH_Shift_ds1);
    sys_info.sib2.radioResourceConfigCommon_Set()->pucch_ConfigCommon_Set()->nRB_CQI_SetValue(0);
    sys_info.sib2.radioResourceConfigCommon_Set()->pucch_ConfigCommon_Set()->nCS_AN_SetValue(0);
    sys_info.sib2.radioResourceConfigCommon_Set()->pucch_ConfigCommon_Set()->n1PUCCH_AN_SetValue(0);
    sys_info.sib2.radioResourceConfigCommon_Set()->soundingRS_UL_ConfigCommon_Set()->SetChoice(SoundingRS_UL_ConfigCommon::k_release);
    sys_info.sib2.radioResourceConfigCommon_Set()->uplinkPowerControlCommon_Set()->p0_NominalPUSCH_SetValue(-70);
    sys_info.sib2.radioResourceConfigCommon_Set()->uplinkPowerControlCommon_Set()->alpha_SetValue(UplinkPowerControlCommon::k_alpha_al1);
    sys_info.sib2.radioResourceConfigCommon_Set()->uplinkPowerControlCommon_Set()->p0_NominalPUCCH_SetValue(-96);
    sys_info.sib2.radioResourceConfigCommon_Set()->uplinkPowerControlCommon_Set()->deltaFList_PUCCH_Set()->deltaF_PUCCH_Format1_SetValue(DeltaFList_PUCCH::k_deltaF_PUCCH_Format1_deltaF0);
    sys_info.sib2.radioResourceConfigCommon_Set()->uplinkPowerControlCommon_Set()->deltaFList_PUCCH_Set()->deltaF_PUCCH_Format1b_SetValue(DeltaFList_PUCCH::k_deltaF_PUCCH_Format1b_deltaF1);
    sys_info.sib2.radioResourceConfigCommon_Set()->uplinkPowerControlCommon_Set()->deltaFList_PUCCH_Set()->deltaF_PUCCH_Format2_SetValue(DeltaFList_PUCCH::k_deltaF_PUCCH_Format2_deltaF0);
    sys_info.sib2.radioResourceConfigCommon_Set()->uplinkPowerControlCommon_Set()->deltaFList_PUCCH_Set()->deltaF_PUCCH_Format2a_SetValue(DeltaFList_PUCCH::k_deltaF_PUCCH_Format2a_deltaF0);
    sys_info.sib2.radioResourceConfigCommon_Set()->uplinkPowerControlCommon_Set()->deltaFList_PUCCH_Set()->deltaF_PUCCH_Format2b_SetValue(DeltaFList_PUCCH::k_deltaF_PUCCH_Format2b_deltaF0);
    sys_info.sib2.radioResourceConfigCommon_Set()->uplinkPowerControlCommon_Set()->deltaPreambleMsg3_SetValue(-1);
    sys_info.sib2.radioResourceConfigCommon_Set()->ul_CyclicPrefixLength_Set()->SetValue(UL_CyclicPrefixLength::k_len1);
    sys_info.sib2.ue_TimersAndConstants_Set()->t300_SetValue(UE_TimersAndConstants::k_t300_ms1000);
    sys_info.sib2.ue_TimersAndConstants_Set()->t301_SetValue(UE_TimersAndConstants::k_t301_ms1000);
    sys_info.sib2.ue_TimersAndConstants_Set()->t310_SetValue(UE_TimersAndConstants::k_t310_ms1000);
    sys_info.sib2.ue_TimersAndConstants_Set()->n310_SetValue(UE_TimersAndConstants::k_n310_n20);
    sys_info.sib2.ue_TimersAndConstants_Set()->t311_SetValue(UE_TimersAndConstants::k_t311_ms30000);
    sys_info.sib2.ue_TimersAndConstants_Set()->n311_SetValue(UE_TimersAndConstants::k_n311_n1);
    sys_info.sib2.freqInfo_value.ul_CarrierFreq_Clear();
    sys_info.sib2.freqInfo_value.ul_Bandwidth_Clear();
    sys_info.sib2.freqInfo_value.additionalSpectrumEmission_Set()->SetValue(1);
    sys_info.sib2.timeAlignmentTimerCommon_Set()->SetValue(TimeAlignmentTimer::k_sf10240);
    // SIB3
    sys_info.sib3.cellReselectionInfoCommon_value.q_Hyst_SetValue(SystemInformationBlockType3::cellReselectionInfoCommon::k_q_Hyst_dB0);
    sys_info.sib3.cellReselectionInfoCommon_value.speedStateReselectionPars_value.Clear();
    sys_info.sib3.cellReselectionServingFreqInfo_value.s_NonIntraSearch_Clear();
    sys_info.sib3.cellReselectionServingFreqInfo_value.threshServingLow_Set()->SetValue(0);
    sys_info.sib3.cellReselectionServingFreqInfo_value.cellReselectionPriority_Set()->SetValue(0);
    sys_info.sib3.intraFreqCellReselectionInfo_value.q_RxLevMin_Set()->SetValue(sys_info.sib1.cellSelectionInfo_value.q_RxLevMin_Get().Value());
    sys_info.sib3.intraFreqCellReselectionInfo_value.p_Max_Set()->SetValue(sys_info.sib1.p_Max_Get().Value());
    sys_info.sib3.intraFreqCellReselectionInfo_value.s_IntraSearch_Clear();
    sys_info.sib3.intraFreqCellReselectionInfo_value.allowedMeasBandwidth_Clear();
    sys_info.sib3.intraFreqCellReselectionInfo_value.presenceAntennaPort1_Set()->SetValue(false);
    sys_info.sib3.intraFreqCellReselectionInfo_value.neighCellConfig_Set()->SetValue(0);
    sys_info.sib3.intraFreqCellReselectionInfo_value.t_ReselectionEUTRA_Set()->SetValue(0);
    sys_info.sib3.intraFreqCellReselectionInfo_value.t_ReselectionEUTRA_SF_Clear();
    // SIB4
    sys_info.sib4.intraFreqNeighCellList_Clear();
    sys_info.sib4.intraFreqBlackCellList_Clear();
    sys_info.sib4.csg_PhysCellIdRange_Clear();
    // SIB5
    sys_info.sib5.interFreqCarrierFreqList_Clear();
    // SIB6
    sys_info.sib6.carrierFreqListUTRA_FDD_Clear();
    sys_info.sib6.carrierFreqListUTRA_TDD_Clear();
    sys_info.sib6.t_ReselectionUTRA_Set()->SetValue(1);
    sys_info.sib6.t_ReselectionUTRA_SF_Clear();
    // SIB7
    sys_info.sib7.t_ReselectionGERAN_Set()->SetValue(1);
    sys_info.sib7.t_ReselectionGERAN_SF_Clear();
    sys_info.sib7.carrierFreqsInfoList_Clear();
    // SIB8
    sys_info.sib8.systemTimeInfo_Clear();
    sys_info.sib8.searchWindowSize_SetValue(0);
    sys_info.sib8.parametersHRPD_value.Clear();
    sys_info.sib8.parameters1XRTT_value.Clear();

    open_lte_pcap_fd();
    open_ip_pcap_fd();
}
LTE_fdd_enb_interface::~LTE_fdd_enb_interface()
{
    stop_ports();

    fclose(lte_pcap_fd);
    fclose(ip_pcap_fd);
}

/***********************/
/*    Communication    */
/***********************/
void LTE_fdd_enb_interface::start_ports()
{
    start_ctrl_port();
    start_debug_port();
}
void LTE_fdd_enb_interface::start_ctrl_port()
{
    std::lock_guard<std::mutex> lock(ctrl_mutex);

    if(NULL != ctrl_socket)
        return;

    libtools_server_socket_receive_callback receive_cb(
        &libtools_server_socket_receive_callback::wrapper<LTE_fdd_enb_interface, &LTE_fdd_enb_interface::handle_ctrl_msg>,
        this);
    libtools_server_socket_connect_disconnect_callback connect_cb(
        &libtools_server_socket_connect_disconnect_callback::wrapper<LTE_fdd_enb_interface, &LTE_fdd_enb_interface::handle_ctrl_connect>,
        this);
    libtools_server_socket_connect_disconnect_callback disconnect_cb(
        &libtools_server_socket_connect_disconnect_callback::wrapper<LTE_fdd_enb_interface, &LTE_fdd_enb_interface::handle_ctrl_disconnect>,
        this);
    libtools_server_socket_error_callback error_cb(
        &libtools_server_socket_error_callback::wrapper<LTE_fdd_enb_interface, &LTE_fdd_enb_interface::handle_ctrl_error>,
        this);
    LIBTOOLS_SERVER_SOCKET_ERROR_ENUM error;
    ctrl_socket = new libtools_server_socket(LTE_FDD_ENB_CTRL_PORT,
                                             receive_cb,
                                             connect_cb,
                                             disconnect_cb,
                                             error_cb,
                                             error);
    if(LIBTOOLS_SERVER_SOCKET_ERROR_NONE == error)
        return;
    send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                   LTE_FDD_ENB_DEBUG_LEVEL_IFACE,
                   __FILE__,
                   __LINE__,
                   "Couldn't open ctrl_socket %s",
                   libtools_server_socket_error_text[error]);
    ctrl_socket = NULL;
}
void LTE_fdd_enb_interface::start_debug_port()
{
    std::lock_guard<std::mutex> lock(debug_mutex);

    if(NULL != debug_socket)
        return;

    libtools_server_socket_receive_callback receive_cb(
        &libtools_server_socket_receive_callback::wrapper<LTE_fdd_enb_interface, &LTE_fdd_enb_interface::handle_debug_msg>,
        this);
    libtools_server_socket_connect_disconnect_callback connect_cb(
        &libtools_server_socket_connect_disconnect_callback::wrapper<LTE_fdd_enb_interface, &LTE_fdd_enb_interface::handle_debug_connect>,
        this);
    libtools_server_socket_connect_disconnect_callback disconnect_cb(
        &libtools_server_socket_connect_disconnect_callback::wrapper<LTE_fdd_enb_interface, &LTE_fdd_enb_interface::handle_debug_disconnect>,
        this);
    libtools_server_socket_error_callback error_cb(
        &libtools_server_socket_error_callback::wrapper<LTE_fdd_enb_interface, &LTE_fdd_enb_interface::handle_debug_error>,
        this);
    LIBTOOLS_SERVER_SOCKET_ERROR_ENUM error;
    debug_socket = new libtools_server_socket(LTE_FDD_ENB_CTRL_PORT + 1,
                                              receive_cb,
                                              connect_cb,
                                              disconnect_cb,
                                              error_cb,
                                              error);
    if(LIBTOOLS_SERVER_SOCKET_ERROR_NONE == error)
        return;
    printf("Couldn't open debug_socket %s\n", libtools_server_socket_error_text[error]);
    debug_socket = NULL;
}
void LTE_fdd_enb_interface::stop_ports()
{
    stop_ctrl_port();
    stop_debug_port();
}
void LTE_fdd_enb_interface::stop_ctrl_port()
{
    std::lock_guard<std::mutex> lock(ctrl_mutex);

    if(NULL == ctrl_socket)
        return;

    delete ctrl_socket;
    ctrl_socket = NULL;
}
void LTE_fdd_enb_interface::stop_debug_port()
{
    std::lock_guard<std::mutex> lock(debug_mutex);

    if(NULL == debug_socket)
        return;

    delete debug_socket;
    debug_socket = NULL;
}
void LTE_fdd_enb_interface::send_ctrl_msg(std::string msg)
{
    std::lock_guard<std::mutex> lock(ctrl_mutex);

    if(!ctrl_connected)
        return;

    ctrl_socket->send(msg + "\n", ctrl_sock_fd);
}
void LTE_fdd_enb_interface::send_ctrl_info_msg(std::string msg, ...)
{
    if(!ctrl_connected)
        return;
    std::string tmp_msg = "info ";
    va_list     args;
    va_start(args, msg);
    char *args_msg;
    if(-1 != vasprintf(&args_msg, msg.c_str(), args))
        tmp_msg += args_msg;
    free(args_msg);
    send_ctrl_msg(tmp_msg);
}
void LTE_fdd_enb_interface::send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ENUM  type,
                                           LTE_FDD_ENB_DEBUG_LEVEL_ENUM level,
                                           std::string                  file_name,
                                           int32                        line,
                                           std::string                  msg,
                                           ...)
{
    std::lock_guard<std::mutex>  lock(debug_mutex);
    std::string                  tmp_msg;
    va_list                      args;
    char                        *args_msg;

    if(!debug_connected             ||
       !(debug_type  & (1 << type)) ||
       !(debug_level & (1 << level)))
        return;

    // Format the output string
    get_formatted_time(tmp_msg);
    tmp_msg += " ";
    tmp_msg += LTE_fdd_enb_debug_type_text[type];
    tmp_msg += " ";
    tmp_msg += LTE_fdd_enb_debug_level_text[level];
    tmp_msg += " ";
    tmp_msg += file_name.c_str();
    tmp_msg += " ";
    tmp_msg += std::to_string(line);
    tmp_msg += " ";
    va_start(args, msg);
    if(-1 != vasprintf(&args_msg, msg.c_str(), args))
        tmp_msg += args_msg;
    tmp_msg += "\n";

    // Cleanup the variable argument string
    free(args_msg);

    debug_socket->send(tmp_msg, debug_sock_fd);
}
void LTE_fdd_enb_interface::send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ENUM   type,
                                           LTE_FDD_ENB_DEBUG_LEVEL_ENUM  level,
                                           std::string                   file_name,
                                           int32                         line,
                                           LIBLTE_BIT_MSG_STRUCT        *lte_msg,
                                           std::string                   msg,
                                           ...)
{
    std::lock_guard<std::mutex>  lock(debug_mutex);
    std::string                  tmp_msg;
    va_list                      args;
    uint32                       i;
    uint32                       hex_val;
    char                        *args_msg;

    if(!debug_connected             ||
       !(debug_type  & (1 << type)) ||
       !(debug_level & (1 << level)))
        return;

    // Format the output string
    get_formatted_time(tmp_msg);
    tmp_msg += " ";
    tmp_msg += LTE_fdd_enb_debug_type_text[type];
    tmp_msg += " ";
    tmp_msg += LTE_fdd_enb_debug_level_text[level];
    tmp_msg += " ";
    tmp_msg += file_name.c_str();
    tmp_msg += " ";
    tmp_msg += std::to_string(line);
    tmp_msg += " ";
    va_start(args, msg);
    if(-1 != vasprintf(&args_msg, msg.c_str(), args))
        tmp_msg += args_msg;
    tmp_msg += " ";
    hex_val  = 0;
    for(i=0; i<lte_msg->N_bits; i++)
    {
        hex_val <<= 1;
        hex_val  |= lte_msg->msg[i];
        if((i % 4) == 3)
        {
            if(hex_val < 0xA)
            {
                tmp_msg += (char)(hex_val + '0');
            }else{
                tmp_msg += (char)((hex_val-0xA) + 'A');
            }
            hex_val = 0;
        }
    }
    if((lte_msg->N_bits % 4) != 0)
    {
        for(i=0; i<4-(lte_msg->N_bits % 4); i++)
        {
            hex_val <<= 1;
        }
        if(hex_val < 0xA)
        {
            tmp_msg += (char)(hex_val + '0');
        }else{
            tmp_msg += (char)((hex_val-0xA) + 'A');
        }
    }
    tmp_msg += "\n";

    // Cleanup the variable argument string
    free(args_msg);

    debug_socket->send(tmp_msg, debug_sock_fd);
}
void LTE_fdd_enb_interface::send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ENUM   type,
                                           LTE_FDD_ENB_DEBUG_LEVEL_ENUM  level,
                                           std::string                   file_name,
                                           int32                         line,
                                           std::vector<bool>            &lte_msg,
                                           std::string                   msg,
                                           ...)
{
    std::lock_guard<std::mutex>  lock(debug_mutex);
    std::string                  tmp_msg;
    va_list                      args;
    uint32                       i;
    uint32                       hex_val;
    char                        *args_msg;

    if(!debug_connected             ||
       !(debug_type  & (1 << type)) ||
       !(debug_level & (1 << level)))
        return;

    // Format the output string
    get_formatted_time(tmp_msg);
    tmp_msg += " ";
    tmp_msg += LTE_fdd_enb_debug_type_text[type];
    tmp_msg += " ";
    tmp_msg += LTE_fdd_enb_debug_level_text[level];
    tmp_msg += " ";
    tmp_msg += file_name.c_str();
    tmp_msg += " ";
    tmp_msg += std::to_string(line);
    tmp_msg += " ";
    va_start(args, msg);
    if(-1 != vasprintf(&args_msg, msg.c_str(), args))
        tmp_msg += args_msg;
    tmp_msg += " ";
    hex_val  = 0;
    for(i=0; i<lte_msg.size(); i++)
    {
        hex_val <<= 1;
        hex_val  |= lte_msg[i];
        if((i % 4) == 3)
        {
            if(hex_val < 0xA)
            {
                tmp_msg += (char)(hex_val + '0');
            }else{
                tmp_msg += (char)((hex_val-0xA) + 'A');
            }
            hex_val = 0;
        }
    }
    if((lte_msg.size() % 4) != 0)
    {
        for(i=0; i<4-(lte_msg.size() % 4); i++)
        {
            hex_val <<= 1;
        }
        if(hex_val < 0xA)
        {
            tmp_msg += (char)(hex_val + '0');
        }else{
            tmp_msg += (char)((hex_val-0xA) + 'A');
        }
    }
    tmp_msg += "\n";

    // Cleanup the variable argument string
    free(args_msg);

    debug_socket->send(tmp_msg, debug_sock_fd);
}
void LTE_fdd_enb_interface::send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ENUM   type,
                                           LTE_FDD_ENB_DEBUG_LEVEL_ENUM  level,
                                           std::string                   file_name,
                                           int32                         line,
                                           LIBLTE_BYTE_MSG_STRUCT       *lte_msg,
                                           std::string                   msg,
                                           ...)
{
    std::lock_guard<std::mutex>  lock(debug_mutex);
    std::string                  tmp_msg;
    va_list                      args;
    char                        *args_msg;

    if(!debug_connected             ||
       !(debug_type  & (1 << type)) ||
       !(debug_level & (1 << level)))
        return;

    // Format the output string
    get_formatted_time(tmp_msg);
    tmp_msg += " ";
    tmp_msg += LTE_fdd_enb_debug_type_text[type];
    tmp_msg += " ";
    tmp_msg += LTE_fdd_enb_debug_level_text[level];
    tmp_msg += " ";
    tmp_msg += file_name.c_str();
    tmp_msg += " ";
    tmp_msg += std::to_string(line);
    tmp_msg += " ";
    va_start(args, msg);
    if(-1 != vasprintf(&args_msg, msg.c_str(), args))
        tmp_msg += args_msg;
    tmp_msg += " msg_size=" + std::to_string(lte_msg->N_bytes);
    if(lte_msg->N_bytes > 0)
    {
        tmp_msg += " " + to_string(lte_msg->msg, lte_msg->N_bytes) + "\n";
    }else{
        tmp_msg += "\n";
    }

    // Cleanup the variable argument string
    free(args_msg);

    debug_socket->send(tmp_msg, debug_sock_fd);
}
void LTE_fdd_enb_interface::send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ENUM   type,
                                           LTE_FDD_ENB_DEBUG_LEVEL_ENUM  level,
                                           std::string                   file_name,
                                           int32                         line,
                                           const std::vector<uint8_t>   &lte_msg,
                                           std::string                   msg,
                                           ...)
{
    std::lock_guard<std::mutex>  lock(debug_mutex);
    std::string                  tmp_msg;
    va_list                      args;
    char                        *args_msg;

    if(!debug_connected             ||
       !(debug_type  & (1 << type)) ||
       !(debug_level & (1 << level)))
        return;

    // Format the output string
    get_formatted_time(tmp_msg);
    tmp_msg += " ";
    tmp_msg += LTE_fdd_enb_debug_type_text[type];
    tmp_msg += " ";
    tmp_msg += LTE_fdd_enb_debug_level_text[level];
    tmp_msg += " ";
    tmp_msg += file_name.c_str();
    tmp_msg += " ";
    tmp_msg += std::to_string(line);
    tmp_msg += " ";
    va_start(args, msg);
    if(-1 != vasprintf(&args_msg, msg.c_str(), args))
        tmp_msg += args_msg;
    tmp_msg += " msg_size=" + std::to_string(lte_msg.size());
    tmp_msg += "\n";

    // Cleanup the variable argument string
    free(args_msg);

    debug_socket->send(tmp_msg, debug_sock_fd);
}
void LTE_fdd_enb_interface::open_lte_pcap_fd()
{
    uint32 magic_number = 0xa1b2c3d4;
    uint32 timezone     = 0;
    uint32 sigfigs      = 0;
    uint32 snap_len     = 0xFFFF;
    uint32 dlt          = 147;
    uint32 tmp_u32;
    uint16 major_version = 2;
    uint16 minor_version = 4;
    uint16 tmp_u16;

    lte_pcap_fd = fopen("/tmp/LTE_fdd_enodeb.pcap", "w");

    tmp_u32 = htonl(magic_number);
    fwrite(&tmp_u32, sizeof(tmp_u32), 1, lte_pcap_fd);
    tmp_u16 = htons(major_version);
    fwrite(&tmp_u16, sizeof(tmp_u16), 1, lte_pcap_fd);
    tmp_u16 = htons(minor_version);
    fwrite(&tmp_u16, sizeof(tmp_u16), 1, lte_pcap_fd);
    tmp_u32 = htonl(timezone);
    fwrite(&tmp_u32, sizeof(tmp_u32), 1, lte_pcap_fd);
    tmp_u32 = htonl(sigfigs);
    fwrite(&tmp_u32, sizeof(tmp_u32), 1, lte_pcap_fd);
    tmp_u32 = htonl(snap_len);
    fwrite(&tmp_u32, sizeof(tmp_u32), 1, lte_pcap_fd);
    tmp_u32 = htonl(dlt);
    fwrite(&tmp_u32, sizeof(tmp_u32), 1, lte_pcap_fd);
}
void LTE_fdd_enb_interface::open_ip_pcap_fd()
{
    uint32 magic_number = 0xa1b2c3d4;
    uint32 timezone     = 0;
    uint32 sigfigs      = 0;
    uint32 snap_len     = 0xFFFF;
    uint32 dlt          = 228;
    uint32 tmp_u32;
    uint16 major_version = 2;
    uint16 minor_version = 4;
    uint16 tmp_u16;

    ip_pcap_fd = fopen("/tmp/LTE_fdd_enodeb_ip.pcap", "w");

    tmp_u32 = htonl(magic_number);
    fwrite(&tmp_u32, sizeof(tmp_u32), 1, ip_pcap_fd);
    tmp_u16 = htons(major_version);
    fwrite(&tmp_u16, sizeof(tmp_u16), 1, ip_pcap_fd);
    tmp_u16 = htons(minor_version);
    fwrite(&tmp_u16, sizeof(tmp_u16), 1, ip_pcap_fd);
    tmp_u32 = htonl(timezone);
    fwrite(&tmp_u32, sizeof(tmp_u32), 1, ip_pcap_fd);
    tmp_u32 = htonl(sigfigs);
    fwrite(&tmp_u32, sizeof(tmp_u32), 1, ip_pcap_fd);
    tmp_u32 = htonl(snap_len);
    fwrite(&tmp_u32, sizeof(tmp_u32), 1, ip_pcap_fd);
    tmp_u32 = htonl(dlt);
    fwrite(&tmp_u32, sizeof(tmp_u32), 1, ip_pcap_fd);
}
void LTE_fdd_enb_interface::send_lte_pcap_msg(LTE_FDD_ENB_PCAP_DIRECTION_ENUM  dir,
                                              uint32                           rnti,
                                              uint32                           current_tti,
                                              uint8                           *msg,
                                              uint32                           N_bits)
{
    struct timeval  time;
    struct timezone time_zone;
    uint32          i;
    uint32          idx;
    uint32          length;
    uint32          tmp_u32;
    uint16          tmp_u16;
    uint8           pcap_c_hdr[15];
    uint8           pcap_msg[LIBLTE_MAX_MSG_SIZE*2];

    if(!enable_pcap)
        return;

    // Get approximate time stamp
    gettimeofday(&time, &time_zone);

    // Radio Type
    pcap_c_hdr[0] = 1;

    // Direction
    pcap_c_hdr[1] = dir;

    // RNTI Type
    if(0xFFFFFFFF == rnti)
    {
        pcap_c_hdr[2] = 0;
    }else if(LIBLTE_MAC_P_RNTI == rnti){
        pcap_c_hdr[2] = 1;
    }else if(LIBLTE_MAC_RA_RNTI_START <= rnti &&
             LIBLTE_MAC_RA_RNTI_END   >= rnti){
        pcap_c_hdr[2] = 2;
    }else if(LIBLTE_MAC_SI_RNTI == rnti){
        pcap_c_hdr[2] = 4;
    }else if(LIBLTE_MAC_M_RNTI == rnti){
        pcap_c_hdr[2] = 6;
    }else{
        pcap_c_hdr[2] = 3;
    }

    // RNTI Tag and RNTI
    pcap_c_hdr[3] = 2;
    tmp_u16       = htons((uint16)rnti);
    memcpy(&pcap_c_hdr[4], &tmp_u16, sizeof(uint16));

    // UEID Tag and UEID
    pcap_c_hdr[6] = 3;
    tmp_u16       = htons((uint16)rnti);
    memcpy(&pcap_c_hdr[7], &tmp_u16, sizeof(uint16));

    // SUBFN Tag and SUBFN
    pcap_c_hdr[9] = 4;
    tmp_u16       = htons((uint16)(((current_tti/10) << 4) | current_tti%10));
    memcpy(&pcap_c_hdr[10], &tmp_u16, sizeof(uint16));

    // CRC Status Tag and CRC Status
    pcap_c_hdr[12] = 7;
    pcap_c_hdr[13] = 1;

    // Payload Tag
    pcap_c_hdr[14] = 1;

    // Payload
    idx           = 0;
    pcap_msg[idx] = 0;
    for(i=0; i<N_bits; i++)
    {
        pcap_msg[idx] <<= 1;
        pcap_msg[idx]  |= msg[i];
        if((i % 8) == 7)
        {
            idx++;
            pcap_msg[idx] = 0;
        }
    }

    // Total Length
    length = 15 + idx;

    // Write Data
    tmp_u32 = htonl(time.tv_sec);
    fwrite(&tmp_u32, sizeof(uint32), 1, lte_pcap_fd);
    tmp_u32 = htonl(time.tv_usec);
    fwrite(&tmp_u32, sizeof(uint32), 1, lte_pcap_fd);
    tmp_u32 = htonl(length);
    fwrite(&tmp_u32,   sizeof(uint32), 1,   lte_pcap_fd);
    fwrite(&tmp_u32,   sizeof(uint32), 1,   lte_pcap_fd);
    fwrite(pcap_c_hdr, sizeof(uint8),  15,  lte_pcap_fd);
    fwrite(pcap_msg,   sizeof(uint8),  idx, lte_pcap_fd);
}
void LTE_fdd_enb_interface::send_ip_pcap_msg(uint8 *msg, uint32 N_bytes)
{
    struct timeval  time;
    struct timezone time_zone;
    uint32          tmp;

    if(!enable_pcap)
        return;

    // Get approximate time stamp
    gettimeofday(&time, &time_zone);

    // Write Data
    tmp = htonl(time.tv_sec);
    fwrite(&tmp, sizeof(uint32), 1, ip_pcap_fd);
    tmp = htonl(time.tv_usec);
    fwrite(&tmp, sizeof(uint32), 1, ip_pcap_fd);
    tmp = htonl(N_bytes);
    fwrite(&tmp, sizeof(uint32), 1,       ip_pcap_fd);
    fwrite(&tmp, sizeof(uint32), 1,       ip_pcap_fd);
    fwrite(msg,  sizeof(uint8),  N_bytes, ip_pcap_fd);
}
void LTE_fdd_enb_interface::handle_ctrl_msg(const std::string msg, const int32 sock_fd)
{
    if(0 == msg.find(shutdown_token))
    {
        send_ctrl_msg("ok");
        shutdown = true;
        if(radio->is_started())
            return handle_stop();
        return;
    }
    if(0 == msg.find(start_token))
        return handle_start();
    if(0 == msg.find(stop_token))
        return handle_stop();
    if(0 == msg.find(construct_si_token))
    {
        if(!app_is_started())
            return send_ctrl_msg("fail already stopped");
        construct_sys_info();
        return send_ctrl_msg("ok");
    }
    if(0 == msg.find(add_user_token))
        return handle_add_user(msg);
    if(0 == msg.find(delete_user_token))
        return handle_delete_user(msg);
    if(0 == msg.find(print_users_token))
        return handle_print_users();
    if(0 == msg.find(print_registered_users_token))
        return handle_print_registered_users();
    if(0 == msg.find(read_token))
        return handle_read(msg);
    if(0 == msg.find(write_token))
    {
        handle_write(msg);
        write_cnfg_file();
        return;
    }
    if(0 == msg.find(help_token))
        return handle_help();
    send_ctrl_msg("fail invalid command");
}
void LTE_fdd_enb_interface::handle_ctrl_connect(const int32 sock_fd)
{
    ctrl_mutex.lock();
    ctrl_connected = true;
    ctrl_sock_fd   = sock_fd;
    ctrl_mutex.unlock();

    send_ctrl_msg("*** LTE FDD ENB ***");
    send_ctrl_msg("Type " + help_token + " to see a list of commands");
}
void LTE_fdd_enb_interface::handle_ctrl_disconnect(const int32 sock_fd)
{
    std::lock_guard<std::mutex> lock(ctrl_mutex);

    ctrl_connected = false;
}
void LTE_fdd_enb_interface::handle_ctrl_error(const LIBTOOLS_SERVER_SOCKET_ERROR_ENUM err)
{
    send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_ERROR,
                   LTE_FDD_ENB_DEBUG_LEVEL_IFACE,
                   __FILE__,
                   __LINE__,
                   "ctrl_socket error %s",
                   libtools_server_socket_error_text[err]);
    assert(0);
}
void LTE_fdd_enb_interface::handle_debug_msg(const std::string msg, const int32 sock_fd)
{
    // No messages to handle
}
void LTE_fdd_enb_interface::handle_debug_connect(const int32 sock_fd)
{
    debug_mutex.lock();
    debug_connected = true;
    debug_sock_fd = sock_fd;
    debug_mutex.unlock();

    send_debug_msg(LTE_FDD_ENB_DEBUG_TYPE_INFO,
                   LTE_FDD_ENB_DEBUG_LEVEL_IFACE,
                   __FILE__,
                   __LINE__,
                   "*** LTE FDD ENB DEBUG INTERFACE ***");
}
void LTE_fdd_enb_interface::handle_debug_disconnect(const int32 sock_fd)
{
    std::lock_guard<std::mutex> lock(debug_mutex);

    debug_connected = false;
}
void LTE_fdd_enb_interface::handle_debug_error(const LIBTOOLS_SERVER_SOCKET_ERROR_ENUM err)
{
    printf("debug_socket error %s\n", libtools_server_socket_error_text[err]);
    assert(0);
}

/******************/
/*    Handlers    */
/******************/
void LTE_fdd_enb_interface::handle_read(std::string msg)
{
    if(0 != msg.find(read_token + " "))
        return send_ctrl_msg("fail invalid " + read_token + " command");
    std::string param = msg.substr(read_token.length() + 1);
    if(0 == param.find(bandwidth_token))
        return send_ctrl_msg("ok " + get_bandwidth_string());
    if(0 == param.find(band_token))
        return send_ctrl_msg("ok " + std::to_string(get_band()));
    if(0 == param.find(dl_earfcn_token))
        return send_ctrl_msg("ok " + std::to_string(dl_earfcn));
    if(0 == param.find(n_ant_token))
        return send_ctrl_msg("ok " + std::to_string(N_ant));
    if(0 == param.find(n_id_cell_token))
        return send_ctrl_msg("ok " + std::to_string(N_id_cell));
    if(0 == param.find(mcc_token))
        return send_ctrl_msg("ok " + get_mcc_string());
    if(0 == param.find(mnc_token))
        return send_ctrl_msg("ok " + get_mnc_string());
    if(0 == param.find(cell_id_token))
        return send_ctrl_msg("ok " + std::to_string(get_cell_id()));
    if(0 == param.find(tracking_area_code_token))
        return send_ctrl_msg("ok " + std::to_string(get_tracking_area_code()));
    if(0 == param.find(q_rx_lev_min_token))
        return send_ctrl_msg("ok " + std::to_string(get_q_rx_lev_min()));
    if(0 == param.find(si_periodicity_token))
        return send_ctrl_msg("ok " + get_si_periodicity_string());
    if(0 == param.find(si_window_length_token))
        return send_ctrl_msg("ok " + get_si_window_length_string());
    if(0 == param.find(p0_nominal_pusch_token))
        return send_ctrl_msg("ok " + std::to_string(get_p0_nominal_pusch()));
    if(0 == param.find(p0_nominal_pucch_token))
        return send_ctrl_msg("ok " + std::to_string(get_p0_nominal_pucch()));
    if(0 == param.find(sib3_present_token))
        return send_ctrl_msg("ok " + get_sib3_present_string());
    if(0 == param.find(q_hyst_token))
        return send_ctrl_msg("ok " + get_q_hyst_string());
    if(0 == param.find(sib4_present_token))
        return send_ctrl_msg("ok " + get_sib4_present_string());
    if(0 == param.find(sib5_present_token))
        return send_ctrl_msg("ok " + get_sib5_present_string());
    if(0 == param.find(sib6_present_token))
        return send_ctrl_msg("ok " + get_sib6_present_string());
    if(0 == param.find(sib7_present_token))
        return send_ctrl_msg("ok " + get_sib7_present_string());
    if(0 == param.find(sib8_present_token))
        return send_ctrl_msg("ok " + get_sib8_present_string());
    if(0 == param.find(mac_direct_to_ue_token))
        return send_ctrl_msg("ok " + get_mac_direct_to_ue_string());
    if(0 == param.find(phy_direct_to_ue_token))
        return send_ctrl_msg("ok " + get_phy_direct_to_ue_string());
    if(0 == param.find(debug_type_token))
        return send_ctrl_msg("ok " + get_debug_type_string());
    if(0 == param.find(debug_level_token))
        return send_ctrl_msg("ok " + get_debug_level_string());
    if(0 == param.find(enable_pcap_token))
        return send_ctrl_msg("ok " + get_enable_pcap_string());
    if(0 == param.find(ip_addr_start_token))
        return send_ctrl_msg("ok " + get_ip_addr_start_string());
    if(0 == param.find(dns_addr_token))
        return send_ctrl_msg("ok " + get_dns_addr_string());
    if(0 == param.find(use_cnfg_file_token))
        return send_ctrl_msg("ok " + get_use_cnfg_file_string());
    if(0 == param.find(use_user_file_token))
        return send_ctrl_msg("ok " + get_use_user_file_string());
    if(0 == param.find(available_radios_token))
        return send_ctrl_msg(
            "ok " + radio->get_available_radios_string());
    if(0 == param.find(selected_radio_name_token))
        return send_ctrl_msg(
            "ok " + radio->get_selected_radio().name);
    if(0 == param.find(selected_radio_idx_token))
        return send_ctrl_msg(
            "ok " + std::to_string(radio->get_selected_radio_idx()));
    if(0 == param.find(clock_source_token))
        return send_ctrl_msg("ok " + radio->get_clock_source());
    if(0 == param.find(tx_gain_token))
        return send_ctrl_msg(
            "ok " + std::to_string(radio->get_tx_gain()));
    if(0 == param.find(rx_gain_token))
        return send_ctrl_msg(
            "ok " + std::to_string(radio->get_rx_gain()));
    send_ctrl_msg("fail invalid " + read_token + " parameter");
}
void LTE_fdd_enb_interface::handle_write(std::string msg)
{
    if(0 != msg.find(write_token + " "))
        return send_ctrl_msg("fail invalid " + write_token + " command");
    std::string param = msg.substr(write_token.length() + 1);
    if(0 == param.find(mcc_token + " "))
    {
        if(set_mcc(param.substr(mcc_token.length()+1)))
            return send_ctrl_msg("fail invalid " + mcc_token + " value");
        return send_ctrl_msg("ok");
    }
    if(0 == param.find(mnc_token + " "))
    {
        if(set_mnc(param.substr(mnc_token.length()+1)))
            return send_ctrl_msg("fail invalid " + mnc_token + " value");
        return send_ctrl_msg("ok");
    }
    if(0 == param.find(cell_id_token + " "))
    {
        if(set_cell_id(param.substr(cell_id_token.length()+1)))
            return send_ctrl_msg("fail invalid " + cell_id_token + " value");
        return send_ctrl_msg("ok");
    }
    if(0 == param.find(tracking_area_code_token + " "))
    {
        if(set_tracking_area_code(param.substr(tracking_area_code_token.length()+1)))
            return send_ctrl_msg("fail invalid " + tracking_area_code_token + " value");
        return send_ctrl_msg("ok");
    }
    if(0 == param.find(q_rx_lev_min_token + " "))
    {
        if(set_q_rx_lev_min(param.substr(q_rx_lev_min_token.length()+1)))
            return send_ctrl_msg("fail invalid " + q_rx_lev_min_token + " value");
        return send_ctrl_msg("ok");
    }
    if(0 == param.find(p0_nominal_pusch_token + " "))
    {
        if(set_p0_nominal_pusch(param.substr(p0_nominal_pusch_token.length()+1)))
            return send_ctrl_msg("fail invalid " + p0_nominal_pusch_token + " value");
        return send_ctrl_msg("ok");
    }
    if(0 == param.find(p0_nominal_pucch_token + " "))
    {
        if(set_p0_nominal_pucch(param.substr(p0_nominal_pucch_token.length()+1)))
            return send_ctrl_msg("fail invalid " + p0_nominal_pucch_token + " value");
        return send_ctrl_msg("ok");
    }
    if(0 == param.find(sib3_present_token + " "))
    {
        if(set_sib3_present(param.substr(sib3_present_token.length()+1)))
            return send_ctrl_msg("fail invalid " + sib3_present_token + " value");
        return send_ctrl_msg("ok");
    }
    if(0 == param.find(q_hyst_token + " "))
    {
        if(set_q_hyst(param.substr(q_hyst_token.length()+1)))
            return send_ctrl_msg("fail invalid " + q_hyst_token + " value");
        return send_ctrl_msg("ok");
    }
    if(0 == param.find(sib4_present_token + " "))
    {
        if(set_sib4_present(param.substr(sib4_present_token.length()+1)))
            return send_ctrl_msg("fail invalid " + sib4_present_token + " value");
        return send_ctrl_msg("ok");
    }
    if(0 == param.find(sib5_present_token + " "))
    {
        if(set_sib5_present(param.substr(sib5_present_token.length()+1)))
            return send_ctrl_msg("fail invalid " + sib5_present_token + " value");
        return send_ctrl_msg("ok");
    }
    if(0 == param.find(sib6_present_token + " "))
    {
        if(set_sib6_present(param.substr(sib6_present_token.length()+1)))
            return send_ctrl_msg("fail invalid " + sib6_present_token + " value");
        return send_ctrl_msg("ok");
    }
    if(0 == param.find(sib7_present_token + " "))
    {
        if(set_sib7_present(param.substr(sib7_present_token.length()+1)))
            return send_ctrl_msg("fail invalid " + sib7_present_token + " value");
        return send_ctrl_msg("ok");
    }
    if(0 == param.find(sib8_present_token + " "))
    {
        if(set_sib8_present(param.substr(sib8_present_token.length()+1)))
            return send_ctrl_msg("fail invalid " + sib8_present_token + " value");
        return send_ctrl_msg("ok");
    }
    if(0 == param.find(debug_type_token + " "))
    {
        if(set_debug_type(param.substr(debug_type_token.length()+1)))
            return send_ctrl_msg("fail invalid " + debug_type_token + " value");
        return send_ctrl_msg("ok");
    }
    if(0 == param.find(debug_level_token + " "))
    {
        if(set_debug_level(param.substr(debug_level_token.length()+1)))
            return send_ctrl_msg("fail invalid " + debug_level_token + " value");
        return send_ctrl_msg("ok");
    }
    if(0 == param.find(use_cnfg_file_token + " "))
    {
        if(set_use_cnfg_file(param.substr(use_cnfg_file_token.length()+1)))
            return send_ctrl_msg("fail invalid " + use_cnfg_file_token + " value");
        if(!use_cnfg_file)
            delete_cnfg_file();
        return send_ctrl_msg("ok");
    }
    if(0 == param.find(use_user_file_token + " "))
    {
        if(set_use_user_file(param.substr(use_user_file_token.length()+1)))
            return send_ctrl_msg("fail invalid " + use_user_file_token + " value");
        return send_ctrl_msg("ok");
    }
    {
        std::lock_guard<std::mutex> lock(start_mutex);
        if(started)
            return send_ctrl_msg("fail already started");
    }
    if(0 == param.find(bandwidth_token + " "))
    {
        if(set_bandwidth(param.substr(bandwidth_token.length()+1)))
            return send_ctrl_msg("fail invalid " + bandwidth_token + " value");
        return send_ctrl_msg("ok");
    }
    if(0 == param.find(band_token + " "))
    {
        if(set_band(param.substr(band_token.length()+1)))
            return send_ctrl_msg("fail invalid " + band_token + " value");
        return send_ctrl_msg("ok");
    }
    if(0 == param.find(dl_earfcn_token + " "))
    {
        if(set_dl_earfcn(param.substr(dl_earfcn_token.length()+1)))
            return send_ctrl_msg("fail invalid " + dl_earfcn_token + " value");
        return send_ctrl_msg("ok");
    }
    if(0 == param.find(n_ant_token + " "))
    {
        if(set_n_ant(param.substr(n_ant_token.length()+1)))
            return send_ctrl_msg("fail invalid " + n_ant_token + " value");
        return send_ctrl_msg("ok");
    }
    if(0 == param.find(n_id_cell_token + " "))
    {
        if(set_n_id_cell(param.substr(n_id_cell_token.length()+1)))
            return send_ctrl_msg("fail invalid " + n_id_cell_token + " value");
        return send_ctrl_msg("ok");
    }
    if(0 == param.find(si_periodicity_token + " "))
    {
        if(set_si_periodicity(param.substr(si_periodicity_token.length()+1)))
            return send_ctrl_msg("fail invalid " + si_periodicity_token + " value");
        return send_ctrl_msg("ok");
    }
    if(0 == param.find(si_window_length_token + " "))
    {
        if(set_si_window_length(param.substr(si_window_length_token.length()+1)))
            return send_ctrl_msg("fail invalid " + si_window_length_token + " value");
        return send_ctrl_msg("ok");
    }
    if(0 == param.find(mac_direct_to_ue_token + " "))
    {
        if(set_mac_direct_to_ue(param.substr(mac_direct_to_ue_token.length()+1)))
            return send_ctrl_msg("fail invalid " + mac_direct_to_ue_token + " value");
        return send_ctrl_msg("ok");
    }
    if(0 == param.find(phy_direct_to_ue_token + " "))
    {
        if(set_phy_direct_to_ue(param.substr(phy_direct_to_ue_token.length()+1)))
            return send_ctrl_msg("fail invalid " + phy_direct_to_ue_token + " value");
        return send_ctrl_msg("ok");
    }
    if(0 == param.find(enable_pcap_token + " "))
    {
        if(set_enable_pcap(param.substr(enable_pcap_token.length()+1)))
            return send_ctrl_msg("fail invalid " + enable_pcap_token + " value");
        return send_ctrl_msg("ok");
    }
    if(0 == param.find(ip_addr_start_token + " "))
    {
        if(set_ip_addr_start(param.substr(ip_addr_start_token.length()+1)))
            return send_ctrl_msg("fail invalid " + ip_addr_start_token + " value");
        return send_ctrl_msg("ok");
    }
    if(0 == param.find(dns_addr_token + " "))
    {
        if(set_dns_addr(param.substr(dns_addr_token.length()+1)))
            return send_ctrl_msg("fail invalid " + dns_addr_token + " value");
        return send_ctrl_msg("ok");
    }
    if(0 == param.find(selected_radio_idx_token + " "))
    {
        if(radio->set_selected_radio_idx(param.substr(selected_radio_idx_token.length()+1)))
            return send_ctrl_msg("fail invalid " + selected_radio_idx_token + " value");
        return send_ctrl_msg("ok");
    }
    if(0 == param.find(clock_source_token + " "))
    {
        if(radio->set_clock_source(param.substr(clock_source_token.length()+1)))
            return send_ctrl_msg("fail invalid " + clock_source_token + " value");
        return send_ctrl_msg("ok");
    }
    if(0 == param.find(tx_gain_token + " "))
    {
        if(radio->set_tx_gain(param.substr(tx_gain_token.length()+1)))
            return send_ctrl_msg("fail invalid " + tx_gain_token + " value");
        return send_ctrl_msg("ok");
    }
    if(0 == param.find(rx_gain_token + " "))
    {
        if(radio->set_rx_gain(param.substr(rx_gain_token.length()+1)))
            return send_ctrl_msg("fail invalid " + rx_gain_token + " value");
        return send_ctrl_msg("ok");
    }
    send_ctrl_msg("fail invalid " + write_token + " parameter");
}
std::string LTE_fdd_enb_interface::get_bandwidth_string()
{
    return sys_info.mib.dl_Bandwidth_ValueToString(sys_info.mib.dl_Bandwidth_Value());
}
MasterInformationBlock::dl_Bandwidth_Enum LTE_fdd_enb_interface::get_bandwidth()
{
    return sys_info.mib.dl_Bandwidth_Value();
}
int LTE_fdd_enb_interface::set_bandwidth(std::string bandwidth)
{
    if(0 != sys_info.mib.dl_Bandwidth_SetValue(bandwidth))
        return -1;
    switch(sys_info.mib.dl_Bandwidth_Value())
    {
    case MasterInformationBlock::k_dl_Bandwidth_n100:
        N_rb_dl = LIBLTE_PHY_N_RB_DL_20MHZ;
        N_rb_ul = LIBLTE_PHY_N_RB_UL_20MHZ;
        break;
    case MasterInformationBlock::k_dl_Bandwidth_n75:
        N_rb_dl = LIBLTE_PHY_N_RB_DL_15MHZ;
        N_rb_ul = LIBLTE_PHY_N_RB_UL_15MHZ;
        break;
    case MasterInformationBlock::k_dl_Bandwidth_n50:
        N_rb_dl = LIBLTE_PHY_N_RB_DL_10MHZ;
        N_rb_ul = LIBLTE_PHY_N_RB_UL_10MHZ;
        break;
    case MasterInformationBlock::k_dl_Bandwidth_n25:
        N_rb_dl = LIBLTE_PHY_N_RB_DL_5MHZ;
        N_rb_ul = LIBLTE_PHY_N_RB_UL_5MHZ;
        break;
    case MasterInformationBlock::k_dl_Bandwidth_n15:
        N_rb_dl = LIBLTE_PHY_N_RB_DL_3MHZ;
        N_rb_ul = LIBLTE_PHY_N_RB_UL_3MHZ;
        break;
    case MasterInformationBlock::k_dl_Bandwidth_n6:
        N_rb_dl = LIBLTE_PHY_N_RB_DL_1_4MHZ;
        N_rb_ul = LIBLTE_PHY_N_RB_UL_1_4MHZ;
        break;
    }
    return 0;
}
uint32 LTE_fdd_enb_interface::get_band()
{
    return sys_info.sib1.freqBandIndicator_Value();
}
int LTE_fdd_enb_interface::set_band(std::string band)
{
    int64 value;
    if(to_number(band, value, 1, 25) || sys_info.sib1.freqBandIndicator_SetValue(value))
        return -1;
    dl_earfcn      = liblte_interface_first_dl_earfcn[value];
    ul_earfcn      = liblte_interface_get_corresponding_ul_earfcn(dl_earfcn);
    dl_center_freq = liblte_interface_dl_earfcn_to_frequency(dl_earfcn);
    ul_center_freq = liblte_interface_ul_earfcn_to_frequency(ul_earfcn);
    return 0;
}
uint16 LTE_fdd_enb_interface::get_dl_earfcn()
{
    return dl_earfcn;
}
int LTE_fdd_enb_interface::set_dl_earfcn(std::string _dl_earfcn)
{
    int64 value;
    if(to_number(_dl_earfcn, value, 0, 65535))
        return -1;
    int64_t band_num = sys_info.sib1.freqBandIndicator_Value();
    int64_t band = -1;
    for(uint32 i=0; i<LIBLTE_INTERFACE_BAND_N_ITEMS; i++)
    {
        if(band_num == liblte_interface_band_num[i])
        {
            band = i;
            break;
        }
    }
    if(band == -1)
        return -1;
    if(!(value >= liblte_interface_first_dl_earfcn[band] &&
         value <= liblte_interface_last_dl_earfcn[band]))
        return -1;
    dl_earfcn      = value;
    ul_earfcn      = liblte_interface_get_corresponding_ul_earfcn(dl_earfcn);
    dl_center_freq = liblte_interface_dl_earfcn_to_frequency(dl_earfcn);
    ul_center_freq = liblte_interface_ul_earfcn_to_frequency(ul_earfcn);
    return 0;
}
uint16 LTE_fdd_enb_interface::get_ul_earfcn()
{
    return ul_earfcn;
}
uint32 LTE_fdd_enb_interface::get_n_rb_dl()
{
    return N_rb_dl;
}
uint32 LTE_fdd_enb_interface::get_n_rb_ul()
{
    return N_rb_ul;
}
uint32 LTE_fdd_enb_interface::get_dl_center_freq()
{
    return dl_center_freq;
}
uint32 LTE_fdd_enb_interface::get_ul_center_freq()
{
    return ul_center_freq;
}
uint32 LTE_fdd_enb_interface::get_n_sc_rb_dl()
{
    return N_sc_rb_dl;
}
uint32 LTE_fdd_enb_interface::get_n_sc_rb_ul()
{
    return N_sc_rb_ul;
}
uint8 LTE_fdd_enb_interface::get_n_ant()
{
    return N_ant;
}
int LTE_fdd_enb_interface::set_n_ant(std::string _N_ant)
{
    int64 value;
    if(to_number(_N_ant, value, 1, 4) || value == 3)
        return -1;
    N_ant = value;
    return 0;
}
uint16 LTE_fdd_enb_interface::get_n_id_cell()
{
    return N_id_cell;
}
int LTE_fdd_enb_interface::set_n_id_cell(std::string _N_id_cell)
{
    int64 value;
    if(to_number(_N_id_cell, value, 0, 503))
        return -1;
    N_id_cell = value;
    N_id_2    = N_id_cell % 3;
    N_id_1    = (N_id_cell - N_id_2) / 3;
    return 0;
}
uint8 LTE_fdd_enb_interface::get_n_id_1()
{
    return N_id_1;
}
uint8 LTE_fdd_enb_interface::get_n_id_2()
{
    return N_id_2;
}
std::string LTE_fdd_enb_interface::get_mcc_string()
{
    return (std::to_string(sys_info.sib1.cellAccessRelatedInfo_value.plmn_IdentityList_Get().Value()[0].plmn_Identity_Get().mcc_Get().Value()[0].Value()) +
            std::to_string(sys_info.sib1.cellAccessRelatedInfo_value.plmn_IdentityList_Get().Value()[0].plmn_Identity_Get().mcc_Get().Value()[1].Value()) +
            std::to_string(sys_info.sib1.cellAccessRelatedInfo_value.plmn_IdentityList_Get().Value()[0].plmn_Identity_Get().mcc_Get().Value()[2].Value()));
}
const MCC& LTE_fdd_enb_interface::get_mcc()
{
    return sys_info.sib1.cellAccessRelatedInfo_value.plmn_IdentityList_Get().Value()[0].plmn_Identity_Get().mcc_Get();
}
int LTE_fdd_enb_interface::set_mcc(std::string mcc)
{
    if(3 != mcc.length())
        return -1;
    std::vector<MCC_MNC_Digit> mcc_value(3);
    for(uint32 i=0; i<3; i++)
        if(mcc_value[i].SetValue((uint32)(mcc[i] & 0xF)))
            return -1;
    std::vector<PLMN_IdentityInfo> plmn_ids = sys_info.sib1.cellAccessRelatedInfo_value.plmn_IdentityList_Set()->Value();
    plmn_ids[0].plmn_Identity_Set()->mcc_Set()->SetValue(mcc_value);
    sys_info.sib1.cellAccessRelatedInfo_value.plmn_IdentityList_Set()->SetValue(plmn_ids);
    return 0;
}
std::string LTE_fdd_enb_interface::get_mnc_string()
{
    if(sys_info.sib1.cellAccessRelatedInfo_value.plmn_IdentityList_Get().Value()[0].plmn_Identity_Get().mnc_Get().Value().size() == 3)
        return (std::to_string(sys_info.sib1.cellAccessRelatedInfo_value.plmn_IdentityList_Get().Value()[0].plmn_Identity_Get().mnc_Get().Value()[0].Value()) +
                std::to_string(sys_info.sib1.cellAccessRelatedInfo_value.plmn_IdentityList_Get().Value()[0].plmn_Identity_Get().mnc_Get().Value()[1].Value()) +
                std::to_string(sys_info.sib1.cellAccessRelatedInfo_value.plmn_IdentityList_Get().Value()[0].plmn_Identity_Get().mnc_Get().Value()[2].Value()));
    return (std::to_string(sys_info.sib1.cellAccessRelatedInfo_value.plmn_IdentityList_Get().Value()[0].plmn_Identity_Get().mnc_Get().Value()[0].Value()) +
            std::to_string(sys_info.sib1.cellAccessRelatedInfo_value.plmn_IdentityList_Get().Value()[0].plmn_Identity_Get().mnc_Get().Value()[1].Value()));
}
const MNC& LTE_fdd_enb_interface::get_mnc()
{
    return sys_info.sib1.cellAccessRelatedInfo_value.plmn_IdentityList_Get().Value()[0].plmn_Identity_Get().mnc_Get();
}
int LTE_fdd_enb_interface::set_mnc(std::string mnc)
{
    if(2 != mnc.length() && 3 != mnc.length())
        return -1;
    std::vector<MCC_MNC_Digit> mnc_value(mnc.length());
    for(uint32 i=0; i<mnc.length(); i++)
        if(mnc_value[i].SetValue((uint32)(mnc[i] & 0xF)))
            return -1;
    std::vector<PLMN_IdentityInfo> plmn_ids = sys_info.sib1.cellAccessRelatedInfo_value.plmn_IdentityList_Set()->Value();
    plmn_ids[0].plmn_Identity_Set()->mnc_Set()->SetValue(mnc_value);
    sys_info.sib1.cellAccessRelatedInfo_value.plmn_IdentityList_Set()->SetValue(plmn_ids);
    return 0;
}
uint32 LTE_fdd_enb_interface::get_cell_id()
{
    return sys_info.sib1.cellAccessRelatedInfo_value.cellIdentity_Get().Value();
}
int LTE_fdd_enb_interface::set_cell_id(std::string cell_id)
{
    int64 value;
    if(to_number(cell_id, value, 0, 268435455))
        return -1;
    return sys_info.sib1.cellAccessRelatedInfo_value.cellIdentity_Set()->SetValue(value);
}
uint16 LTE_fdd_enb_interface::get_tracking_area_code()
{
    return sys_info.sib1.cellAccessRelatedInfo_value.trackingAreaCode_Get().Value();
}
int LTE_fdd_enb_interface::set_tracking_area_code(std::string tracking_area_code)
{
    int64 value;
    if(to_number(tracking_area_code, value, 0, 65535))
        return -1;
    return sys_info.sib1.cellAccessRelatedInfo_value.trackingAreaCode_Set()->SetValue(value);
}
int16 LTE_fdd_enb_interface::get_q_rx_lev_min()
{
    return sys_info.sib1.cellSelectionInfo_value.q_RxLevMin_Get().Value() * 2;
}
int LTE_fdd_enb_interface::set_q_rx_lev_min(std::string q_rx_lev_min)
{
    int64 value;
    if(to_number(q_rx_lev_min, value, -140, -44) || (value % 2) != 0)
        return -1;
    return sys_info.sib1.cellSelectionInfo_value.q_RxLevMin_Set()->SetValue(value / 2);
}
std::string LTE_fdd_enb_interface::get_si_periodicity_string()
{
    return sys_info.sib1.schedulingInfoList_Get().Value()[0].si_Periodicity_ValueToString(sys_info.sib1.schedulingInfoList_Get().Value()[0].si_Periodicity_Value());
}
uint16 LTE_fdd_enb_interface::get_si_periodicity()
{
    switch(sys_info.sib1.schedulingInfoList_Get().Value()[0].si_Periodicity_Value())
    {
    case SchedulingInfo::k_si_Periodicity_rf8:
        return 8;
    case SchedulingInfo::k_si_Periodicity_rf16:
        return 16;
    case SchedulingInfo::k_si_Periodicity_rf32:
        return 32;
    case SchedulingInfo::k_si_Periodicity_rf64:
        return 64;
    case SchedulingInfo::k_si_Periodicity_rf128:
        return 128;
    case SchedulingInfo::k_si_Periodicity_rf256:
        return 256;
    case SchedulingInfo::k_si_Periodicity_rf512:
        return 512;
    }
    return 0;
}
int LTE_fdd_enb_interface::set_si_periodicity(std::string si_periodicity)
{
    std::vector<SchedulingInfo> sched_info = sys_info.sib1.schedulingInfoList_Set()->Value();
    for(auto si : sched_info)
        if(0 != si.si_Periodicity_SetValue(si_periodicity))
            return -1;
    sys_info.sib1.schedulingInfoList_Set()->SetValue(sched_info);
    return 0;
}
std::string LTE_fdd_enb_interface::get_si_window_length_string()
{
    return sys_info.sib1.si_WindowLength_ValueToString(sys_info.sib1.si_WindowLength_Value());
}
uint8 LTE_fdd_enb_interface::get_si_window_length()
{
    switch(sys_info.sib1.si_WindowLength_Value())
    {
    case SystemInformationBlockType1::k_si_WindowLength_ms1:
        return 1;
    case SystemInformationBlockType1::k_si_WindowLength_ms2:
        return 2;
    case SystemInformationBlockType1::k_si_WindowLength_ms5:
        return 5;
    case SystemInformationBlockType1::k_si_WindowLength_ms10:
        return 10;
    case SystemInformationBlockType1::k_si_WindowLength_ms15:
        return 15;
    case SystemInformationBlockType1::k_si_WindowLength_ms20:
        return 20;
    case SystemInformationBlockType1::k_si_WindowLength_ms40:
        return 40;
    }
    return 0;
}
int LTE_fdd_enb_interface::set_si_window_length(std::string si_window_length)
{
    return sys_info.sib1.si_WindowLength_SetValue(si_window_length);
}
uint8 LTE_fdd_enb_interface::get_ra_response_window_size()
{
    switch(sys_info.sib2.radioResourceConfigCommon_Get().rach_ConfigCommon_Get().ra_SupervisionInfo_value.ra_ResponseWindowSize_Value())
    {
    case RACH_ConfigCommon::ra_SupervisionInfo::k_ra_ResponseWindowSize_sf2:
        return 2;
    case RACH_ConfigCommon::ra_SupervisionInfo::k_ra_ResponseWindowSize_sf3:
        return 3;
    case RACH_ConfigCommon::ra_SupervisionInfo::k_ra_ResponseWindowSize_sf4:
        return 4;
    case RACH_ConfigCommon::ra_SupervisionInfo::k_ra_ResponseWindowSize_sf5:
        return 5;
    case RACH_ConfigCommon::ra_SupervisionInfo::k_ra_ResponseWindowSize_sf6:
        return 6;
    case RACH_ConfigCommon::ra_SupervisionInfo::k_ra_ResponseWindowSize_sf7:
        return 7;
    case RACH_ConfigCommon::ra_SupervisionInfo::k_ra_ResponseWindowSize_sf8:
        return 8;
    case RACH_ConfigCommon::ra_SupervisionInfo::k_ra_ResponseWindowSize_sf10:
        return 10;
    }
    return 0;
}
int8 LTE_fdd_enb_interface::get_p0_nominal_pusch()
{
    return sys_info.sib2.radioResourceConfigCommon_Get().uplinkPowerControlCommon_Get().p0_NominalPUSCH_Value();
}
int LTE_fdd_enb_interface::set_p0_nominal_pusch(std::string p0_nominal_pusch)
{
    int64 value;
    if(to_number(p0_nominal_pusch, value, -126, 24))
        return -1;
    return sys_info.sib2.radioResourceConfigCommon_Set()->uplinkPowerControlCommon_Set()->p0_NominalPUSCH_SetValue(value);
}
int8 LTE_fdd_enb_interface::get_p0_nominal_pucch()
{
    return sys_info.sib2.radioResourceConfigCommon_Get().uplinkPowerControlCommon_Get().p0_NominalPUCCH_Value();
}
int LTE_fdd_enb_interface::set_p0_nominal_pucch(std::string p0_nominal_pucch)
{
    int64 value;
    if(to_number(p0_nominal_pucch, value, -126, 24))
        return -1;
    return sys_info.sib2.radioResourceConfigCommon_Set()->uplinkPowerControlCommon_Set()->p0_NominalPUCCH_SetValue(value);
}
std::string LTE_fdd_enb_interface::get_sib3_present_string()
{
    return bool_to_enable_string(sib3_present);
}
bool LTE_fdd_enb_interface::get_sib3_present()
{
    return sib3_present;
}
int LTE_fdd_enb_interface::set_sib3_present(std::string _sib3_present)
{
    sib3_present = enable_string_to_bool(_sib3_present);
    return 0;
}
std::string LTE_fdd_enb_interface::get_q_hyst_string()
{
    return sys_info.sib3.cellReselectionInfoCommon_value.q_Hyst_ValueToString(sys_info.sib3.cellReselectionInfoCommon_value.q_Hyst_Value());
}
SystemInformationBlockType3::cellReselectionInfoCommon::q_Hyst_Enum LTE_fdd_enb_interface::get_q_hyst()
{
    return sys_info.sib3.cellReselectionInfoCommon_value.q_Hyst_Value();
}
int LTE_fdd_enb_interface::set_q_hyst(std::string q_hyst)
{
    return sys_info.sib3.cellReselectionInfoCommon_value.q_Hyst_SetValue(q_hyst);
}
std::string LTE_fdd_enb_interface::get_sib4_present_string()
{
    return bool_to_enable_string(sib4_present);
}
bool LTE_fdd_enb_interface::get_sib4_present()
{
    return sib4_present;
}
int LTE_fdd_enb_interface::set_sib4_present(std::string _sib4_present)
{
    sib4_present = enable_string_to_bool(_sib4_present);
    return 0;
}
std::string LTE_fdd_enb_interface::get_sib5_present_string()
{
    return bool_to_enable_string(sib5_present);
}
bool LTE_fdd_enb_interface::get_sib5_present()
{
    return sib5_present;
}
int LTE_fdd_enb_interface::set_sib5_present(std::string _sib5_present)
{
    sib5_present = enable_string_to_bool(_sib5_present);
    return 0;
}
std::string LTE_fdd_enb_interface::get_sib6_present_string()
{
    return bool_to_enable_string(sib6_present);
}
bool LTE_fdd_enb_interface::get_sib6_present()
{
    return sib6_present;
}
int LTE_fdd_enb_interface::set_sib6_present(std::string _sib6_present)
{
    sib6_present = enable_string_to_bool(_sib6_present);
    return 0;
}
std::string LTE_fdd_enb_interface::get_sib7_present_string()
{
    return bool_to_enable_string(sib7_present);
}
bool LTE_fdd_enb_interface::get_sib7_present()
{
    return sib7_present;
}
int LTE_fdd_enb_interface::set_sib7_present(std::string _sib7_present)
{
    sib7_present = enable_string_to_bool(_sib7_present);
    return 0;
}
std::string LTE_fdd_enb_interface::get_sib8_present_string()
{
    return bool_to_enable_string(sib8_present);
}
bool LTE_fdd_enb_interface::get_sib8_present()
{
    return sib8_present;
}
int LTE_fdd_enb_interface::set_sib8_present(std::string _sib8_present)
{
    sib8_present = enable_string_to_bool(_sib8_present);
    return 0;
}
std::string LTE_fdd_enb_interface::get_mac_direct_to_ue_string()
{
    return bool_to_enable_string(mac_direct_to_ue);
}
bool LTE_fdd_enb_interface::get_mac_direct_to_ue()
{
    return mac_direct_to_ue;
}
int LTE_fdd_enb_interface::set_mac_direct_to_ue(std::string _mac_direct_to_ue)
{
    mac_direct_to_ue = enable_string_to_bool(_mac_direct_to_ue);
    if(mac_direct_to_ue)
        phy_direct_to_ue = false;
    return 0;
}
std::string LTE_fdd_enb_interface::get_phy_direct_to_ue_string()
{
    return bool_to_enable_string(phy_direct_to_ue);
}
bool LTE_fdd_enb_interface::get_phy_direct_to_ue()
{
    return phy_direct_to_ue;
}
int LTE_fdd_enb_interface::set_phy_direct_to_ue(std::string _phy_direct_to_ue)
{
    phy_direct_to_ue = enable_string_to_bool(_phy_direct_to_ue);
    if(phy_direct_to_ue)
        mac_direct_to_ue = false;
    return 0;
}
std::string LTE_fdd_enb_interface::get_debug_type_string()
{
    std::string str;
    for(uint32 i=0; i<LTE_FDD_ENB_DEBUG_TYPE_N_ITEMS; i++)
        if(debug_type & (1 << i))
            str += (std::string)LTE_fdd_enb_debug_type_text[i] + " ";
    return str;
}
uint32 LTE_fdd_enb_interface::get_debug_type()
{
    return debug_type;
}
int LTE_fdd_enb_interface::set_debug_type(std::string _debug_type)
{
    uint32 value = 0;
    for(uint32 i=0; i<LTE_FDD_ENB_DEBUG_TYPE_N_ITEMS; i++)
        if(std::string::npos != _debug_type.find(LTE_fdd_enb_debug_type_text[i]))
            value |= 1 << i;
    debug_type = value;
    return 0;
}
std::string LTE_fdd_enb_interface::get_debug_level_string()
{
    std::string str;
    for(uint32 i=0; i<LTE_FDD_ENB_DEBUG_LEVEL_N_ITEMS; i++)
        if(debug_level & (1 << i))
            str += (std::string)LTE_fdd_enb_debug_level_text[i] + " ";
    return str;
}
uint32 LTE_fdd_enb_interface::get_debug_level()
{
    return debug_level;
}
int LTE_fdd_enb_interface::set_debug_level(std::string _debug_level)
{
    uint32 value = 0;
    for(uint32 i=0; i<LTE_FDD_ENB_DEBUG_LEVEL_N_ITEMS; i++)
        if(std::string::npos != _debug_level.find(LTE_fdd_enb_debug_level_text[i]))
            value |= 1 << i;
    debug_level = value;
    return 0;
}
std::string LTE_fdd_enb_interface::get_enable_pcap_string()
{
    return bool_to_enable_string(enable_pcap);
}
bool LTE_fdd_enb_interface::get_enable_pcap()
{
    return enable_pcap;
}
int LTE_fdd_enb_interface::set_enable_pcap(std::string _enable_pcap)
{
    enable_pcap = enable_string_to_bool(_enable_pcap);
    return 0;
}
std::string LTE_fdd_enb_interface::get_ip_addr_start_string()
{
    std::string str;
    for(uint32 i=0; i<8; i++)
    {
        uint32 hex = ((ip_addr_start) >> (7-i)*4) & 0x0F;
        if(hex < 0xA)
        {
            str += (char)(hex + '0');
        }else{
            str += (char)((hex-0xA) + 'A');
        }
    }
    return str;
}
uint32 LTE_fdd_enb_interface::get_ip_addr_start()
{
    return ip_addr_start;
}
int LTE_fdd_enb_interface::set_ip_addr_start(std::string _ip_addr_start)
{
    if(8 != _ip_addr_start.length())
        return -1;
    uint8 value[4];
    if(to_number(_ip_addr_start, 4, value))
        return -1;
    ip_addr_start = 0;
    for(uint32 i=0; i<4; i++)
        ip_addr_start = (ip_addr_start << 8) + value[i];
    return 0;
}
std::string LTE_fdd_enb_interface::get_dns_addr_string()
{
    std::string str;
    for(uint32 i=0; i<8; i++)
    {
        uint32 hex = ((dns_addr) >> (7-i)*4) & 0x0F;
        if(hex < 0xA)
        {
            str += (char)(hex + '0');
        }else{
            str += (char)((hex-0xA) + 'A');
        }
    }
    return str;
}
uint32 LTE_fdd_enb_interface::get_dns_addr()
{
    return dns_addr;
}
int LTE_fdd_enb_interface::set_dns_addr(std::string _dns_addr)
{
    if(8 != _dns_addr.length())
        return -1;
    uint8 value[4];
    if(to_number(_dns_addr, 4, value))
        return -1;
    dns_addr = 0;
    for(uint32 i=0; i<4; i++)
        dns_addr = (dns_addr << 8) + value[i];
    return 0;
}
std::string LTE_fdd_enb_interface::get_use_cnfg_file_string()
{
    return bool_to_enable_string(use_cnfg_file);
}
bool LTE_fdd_enb_interface::get_use_cnfg_file()
{
    return use_cnfg_file;
}
int LTE_fdd_enb_interface::set_use_cnfg_file(std::string _use_cnfg_file)
{
    use_cnfg_file = enable_string_to_bool(_use_cnfg_file);
    return 0;
}
std::string LTE_fdd_enb_interface::get_use_user_file_string()
{
    return bool_to_enable_string(use_user_file);
}
bool LTE_fdd_enb_interface::get_use_user_file()
{
    return use_user_file;
}
int LTE_fdd_enb_interface::set_use_user_file(std::string _use_user_file)
{
    use_user_file = enable_string_to_bool(_use_user_file);
    return 0;
}
std::string LTE_fdd_enb_interface::bool_to_enable_string(bool value)
{
    if(value)
        return "on";
    return "off";
}
bool LTE_fdd_enb_interface::enable_string_to_bool(std::string enable)
{
    if(enable == "on")
        return true;
    return false;
}
void LTE_fdd_enb_interface::handle_start()
{
    {
        std::lock_guard<std::mutex> lock(start_mutex);
        if(started)
            return send_ctrl_msg("fail already started");
        started = true;
    }

    // Initialize inter-stack communication
    phy_to_mac_comm   = new LTE_fdd_enb_msgq(this, "phy_to_mac");
    mac_to_phy_comm   = new LTE_fdd_enb_msgq(this, "mac_to_phy");
    mac_to_rlc_comm   = new LTE_fdd_enb_msgq(this, "mac_to_rlc");
    mac_to_timer_comm = new LTE_fdd_enb_msgq(this, "mac_to_timer");
    rlc_to_mac_comm   = new LTE_fdd_enb_msgq(this, "rlc_to_mac");
    rlc_to_pdcp_comm  = new LTE_fdd_enb_msgq(this, "rlc_to_pdcp");
    pdcp_to_rlc_comm  = new LTE_fdd_enb_msgq(this, "pdcp_to_rlc");
    pdcp_to_rrc_comm  = new LTE_fdd_enb_msgq(this, "pdcp_to_rrc");
    rrc_to_pdcp_comm  = new LTE_fdd_enb_msgq(this, "rrc_to_pdcp");
    rrc_to_mme_comm   = new LTE_fdd_enb_msgq(this, "rrc_to_mme");
    mme_to_rrc_comm   = new LTE_fdd_enb_msgq(this, "mme_to_rrc");
    pdcp_to_gw_comm   = new LTE_fdd_enb_msgq(this, "pdcp_to_gw");
    gw_to_pdcp_comm   = new LTE_fdd_enb_msgq(this, "gw_to_pdcp");

    // Construct the system information
    construct_sys_info();

    // Start layers
    char err_str[LTE_FDD_ENB_MAX_LINE_SIZE];
    if(LTE_FDD_ENB_ERROR_NONE != gw->start(pdcp_to_gw_comm, gw_to_pdcp_comm, err_str))
        return send_ctrl_msg("fail GW start issue " + (std::string)err_str);

    phy->start(mac_to_phy_comm, phy_to_mac_comm, phy_direct_to_ue, radio);
    mac->start(phy_to_mac_comm, rlc_to_mac_comm, mac_to_phy_comm, mac_to_rlc_comm, mac_to_timer_comm, mac_direct_to_ue);
    timer_mgr->start(mac_to_timer_comm);
    rlc->start(mac_to_rlc_comm, pdcp_to_rlc_comm, rlc_to_mac_comm, rlc_to_pdcp_comm);
    pdcp->start(rlc_to_pdcp_comm, rrc_to_pdcp_comm, gw_to_pdcp_comm, pdcp_to_rlc_comm, pdcp_to_rrc_comm, pdcp_to_gw_comm);
    rrc->start(pdcp_to_rrc_comm, mme_to_rrc_comm, rrc_to_pdcp_comm, rrc_to_mme_comm);
    mme->start(rrc_to_mme_comm, mme_to_rrc_comm);
    if(LTE_FDD_ENB_ERROR_NONE == radio->start())
        return send_ctrl_msg("ok");

    start_mutex.lock();
    started = false;
    start_mutex.unlock();

    phy->stop();
    mac->stop();
    timer_mgr->stop();
    rlc->stop();
    pdcp->stop();
    rrc->stop();
    mme->stop();

    send_ctrl_msg("fail radio start issue");
}
void LTE_fdd_enb_interface::handle_stop()
{
    {
        std::lock_guard<std::mutex> lock(start_mutex);
        if(!started)
            return send_ctrl_msg("fail already stopped");
        started = false;
    }

    // Stop all layers
    if(LTE_FDD_ENB_ERROR_NONE != radio->stop())
        return send_ctrl_msg("fail radio stop issue");

    phy->stop();
    mac->stop();
    timer_mgr->stop();
    rlc->stop();
    pdcp->stop();
    rrc->stop();
    mme->stop();
    gw->stop();

    // Send a message to all inter-stack communication message queues and cleanup
    phy_to_mac_comm->send(LTE_FDD_ENB_MESSAGE_TYPE_KILL,
                          LTE_FDD_ENB_DEST_LAYER_ANY,
                          NULL,
                          0);
    mac_to_phy_comm->send(LTE_FDD_ENB_MESSAGE_TYPE_KILL,
                          LTE_FDD_ENB_DEST_LAYER_ANY,
                          NULL,
                          0);
    mac_to_rlc_comm->send(LTE_FDD_ENB_MESSAGE_TYPE_KILL,
                          LTE_FDD_ENB_DEST_LAYER_ANY,
                          NULL,
                          0);
    mac_to_timer_comm->send(LTE_FDD_ENB_MESSAGE_TYPE_KILL,
                            LTE_FDD_ENB_DEST_LAYER_ANY,
                            NULL,
                            0);
    rlc_to_mac_comm->send(LTE_FDD_ENB_MESSAGE_TYPE_KILL,
                          LTE_FDD_ENB_DEST_LAYER_ANY,
                          NULL,
                          0);
    rlc_to_pdcp_comm->send(LTE_FDD_ENB_MESSAGE_TYPE_KILL,
                           LTE_FDD_ENB_DEST_LAYER_ANY,
                           NULL,
                           0);
    pdcp_to_rlc_comm->send(LTE_FDD_ENB_MESSAGE_TYPE_KILL,
                           LTE_FDD_ENB_DEST_LAYER_ANY,
                           NULL,
                           0);
    pdcp_to_rrc_comm->send(LTE_FDD_ENB_MESSAGE_TYPE_KILL,
                           LTE_FDD_ENB_DEST_LAYER_ANY,
                           NULL,
                           0);
    rrc_to_pdcp_comm->send(LTE_FDD_ENB_MESSAGE_TYPE_KILL,
                           LTE_FDD_ENB_DEST_LAYER_ANY,
                           NULL,
                           0);
    rrc_to_mme_comm->send(LTE_FDD_ENB_MESSAGE_TYPE_KILL,
                          LTE_FDD_ENB_DEST_LAYER_ANY,
                          NULL,
                          0);
    mme_to_rrc_comm->send(LTE_FDD_ENB_MESSAGE_TYPE_KILL,
                          LTE_FDD_ENB_DEST_LAYER_ANY,
                          NULL,
                          0);
    pdcp_to_gw_comm->send(LTE_FDD_ENB_MESSAGE_TYPE_KILL,
                          LTE_FDD_ENB_DEST_LAYER_ANY,
                          NULL,
                          0);
    gw_to_pdcp_comm->send(LTE_FDD_ENB_MESSAGE_TYPE_KILL,
                          LTE_FDD_ENB_DEST_LAYER_ANY,
                          NULL,
                          0);
    delete phy_to_mac_comm;
    delete mac_to_phy_comm;
    delete mac_to_rlc_comm;
    delete mac_to_timer_comm;
    delete rlc_to_mac_comm;
    delete rlc_to_pdcp_comm;
    delete pdcp_to_rlc_comm;
    delete pdcp_to_rrc_comm;
    delete rrc_to_pdcp_comm;
    delete rrc_to_mme_comm;
    delete mme_to_rrc_comm;
    delete pdcp_to_gw_comm;
    delete gw_to_pdcp_comm;

    // Delete layers
    delete pdcp;
    delete mme;
    delete gw;

    send_ctrl_msg("ok");
}
void LTE_fdd_enb_interface::handle_help()
{
    send_ctrl_msg("***System Configuration Parameters***");
    send_ctrl_msg("\tCommands:");
    send_ctrl_msg("\t\t" + start_token + " - Constructs the system information and starts the eNB");
    send_ctrl_msg("\t\t" + stop_token + " - Stops the eNB");
    send_ctrl_msg("\t\t" + shutdown_token + " - Stops the eNB and exits");
    send_ctrl_msg("\t\t" + construct_si_token + " - Constructs the new system information");
    send_ctrl_msg("\t\t" + help_token + " - Prints this screen");
    send_ctrl_msg("\t\t" + add_user_token + " " + imsi_token + "=<" + imsi_token + "> " + imei_token + "=<" + imei_token + "> " + k_token + "=<" + k_token + "> - Adds a user to the HSS (<imsi> and <imei> are 15 decimal digits, and <k> is 32 hex digits)");
    send_ctrl_msg("\t\t" + delete_user_token + " " + imsi_token + "=<" + imsi_token + "> - Deletes a user from the HSS");
    send_ctrl_msg("\t\t" + print_users_token + " - Prints all the users in the HSS");
    send_ctrl_msg("\t\t" + print_registered_users_token + " - Prints all the users currently registered");
    send_ctrl_msg("\t\t" + read_token + " - Reads the specified parameter (" + read_token + " <param>)");
    send_ctrl_msg("\t\t" + write_token + " - Writes the specified parameter (" + write_token + " <param> <value>)");

    // System Parameters
    send_ctrl_msg("\tSystem Parameters:");
    send_ctrl_msg("\t\t" + bandwidth_token + " = " + get_bandwidth_string());
    send_ctrl_msg("\t\t" + band_token + " = " + std::to_string(get_band()));
    send_ctrl_msg("\t\t" + dl_earfcn_token + " = " + std::to_string(dl_earfcn));
    send_ctrl_msg("\t\t" + n_ant_token + " = " + std::to_string(N_ant));
    send_ctrl_msg("\t\t" + n_id_cell_token + " = " + std::to_string(N_id_cell));
    send_ctrl_msg("\t\t" + mcc_token + " = " + get_mcc_string());
    send_ctrl_msg("\t\t" + mnc_token + " = " + get_mnc_string());
    send_ctrl_msg("\t\t" + cell_id_token + " = " + std::to_string(get_cell_id()));
    send_ctrl_msg("\t\t" + tracking_area_code_token + " = " + std::to_string(get_tracking_area_code()));
    send_ctrl_msg("\t\t" + q_rx_lev_min_token + " = " + std::to_string(get_q_rx_lev_min()));
    send_ctrl_msg("\t\t" + si_periodicity_token + " = " + get_si_periodicity_string());
    send_ctrl_msg("\t\t" + si_window_length_token + " = " + get_si_window_length_string());
    send_ctrl_msg("\t\t" + p0_nominal_pusch_token + " = " + std::to_string(get_p0_nominal_pusch()));
    send_ctrl_msg("\t\t" + p0_nominal_pucch_token + " = " + std::to_string(get_p0_nominal_pucch()));
    send_ctrl_msg("\t\t" + sib3_present_token + " = " + get_sib3_present_string());
    send_ctrl_msg("\t\t" + q_hyst_token + " = " + get_q_hyst_string());
    send_ctrl_msg("\t\t" + sib4_present_token + " = " + get_sib4_present_string());
    send_ctrl_msg("\t\t" + sib5_present_token + " = " + get_sib5_present_string());
    send_ctrl_msg("\t\t" + sib6_present_token + " = " + get_sib6_present_string());
    send_ctrl_msg("\t\t" + sib7_present_token + " = " + get_sib7_present_string());
    send_ctrl_msg("\t\t" + sib8_present_token + " = " + get_sib8_present_string());
    send_ctrl_msg("\t\t" + mac_direct_to_ue_token + " = " + get_mac_direct_to_ue_string());
    send_ctrl_msg("\t\t" + phy_direct_to_ue_token + " = " + get_phy_direct_to_ue_string());
    send_ctrl_msg("\t\t" + debug_type_token + " = " + get_debug_type_string());
    send_ctrl_msg("\t\t" + debug_level_token + " = " + get_debug_level_string());
    send_ctrl_msg("\t\t" + enable_pcap_token + " = " + get_enable_pcap_string());
    send_ctrl_msg("\t\t" + ip_addr_start_token + " = " + get_ip_addr_start_string());
    send_ctrl_msg("\t\t" + dns_addr_token + " = " + get_dns_addr_string());
    send_ctrl_msg("\t\t" + use_cnfg_file_token + " = " + get_use_cnfg_file_string());
    send_ctrl_msg("\t\t" + use_user_file_token + " = " + get_use_user_file_string());
}
void LTE_fdd_enb_interface::handle_add_user(std::string msg)
{
    if(0 != msg.find(add_user_token + " "))
        return send_ctrl_msg("fail invalid " + add_user_token + " command");
    std::string param = msg.substr(add_user_token.length() + 1);
    if(std::string::npos == param.find(imsi_token + "="))
        return send_ctrl_msg("fail " + add_user_token + " command missing " + imsi_token);
    std::string imsi_str = param.substr(param.find(imsi_token)+imsi_token.length()+1);
    imsi_str = imsi_str.substr(0, imsi_str.find(" "));
    if(!is_string_valid_as_number(imsi_str, 15, 10))
        return send_ctrl_msg("fail " + add_user_token + " command with invalid " + imsi_token);
    if(std::string::npos == param.find(imei_token + "="))
        return send_ctrl_msg("fail " + add_user_token + " command missing " + imei_token);
    std::string imei_str = param.substr(param.find(imei_token)+imei_token.length()+1);
    imei_str = imei_str.substr(0, imei_str.find(" "));
    if(!is_string_valid_as_number(imei_str, 15, 10))
        return send_ctrl_msg("fail " + add_user_token + " command with invalid " + imei_token);
    if(std::string::npos == param.find(k_token + "="))
        return send_ctrl_msg("fail " + add_user_token + " command missing " + k_token);
    std::string k_str = param.substr(param.find(k_token)+k_token.length()+1);
    k_str = k_str.substr(0, k_str.find(" "));
    if(!is_string_valid_as_number(k_str, 32, 16))
        return send_ctrl_msg("fail " + add_user_token + " command with invalid " + k_token);
    if(LTE_FDD_ENB_ERROR_NONE != hss->add_user(imsi_str, imei_str, k_str))
        return send_ctrl_msg("fail HSS add_user failure");
    send_ctrl_msg("ok");
}
void LTE_fdd_enb_interface::handle_delete_user(std::string msg)
{
    if(0 != msg.find(delete_user_token + " "))
        return send_ctrl_msg("fail invalid " + delete_user_token + " command");
    std::string param = msg.substr(delete_user_token.length() + 1);
    if(std::string::npos == param.find(imsi_token + "="))
        return send_ctrl_msg("fail " + delete_user_token + " command missing " + imsi_token);
    std::string imsi_str = param.substr(param.find(imsi_token)+imsi_token.length()+1);
    imsi_str = imsi_str.substr(0, imsi_str.find(" "));
    if(!is_string_valid_as_number(imsi_str, 15, 10))
        return send_ctrl_msg("fail " + delete_user_token + " command with invalid " + imsi_token);
    if(LTE_FDD_ENB_ERROR_NONE != hss->del_user(imsi_str))
        return send_ctrl_msg("fail HSS delete user failure");
    send_ctrl_msg("ok");
}
void LTE_fdd_enb_interface::handle_print_users()
{
    send_ctrl_msg("ok " + hss->print_all_users());
}
void LTE_fdd_enb_interface::handle_print_registered_users()
{
    send_ctrl_msg("ok " + user_mgr->print_all_users());
}
void LTE_fdd_enb_interface::read_cnfg_file()
{
    hss->read_user_file(this);

    FILE *cnfg_file = fopen("/tmp/LTE_fdd_enb.cnfg_db", "r");
    if(NULL == cnfg_file)
        return;
    char str[LTE_FDD_ENB_MAX_LINE_SIZE];
    while(NULL != fgets(str, LTE_FDD_ENB_MAX_LINE_SIZE, cnfg_file))
    {
        std::string line_str = str;
        handle_write("write " + line_str.substr(0, line_str.length()-1));
    }
    fclose(cnfg_file);
}
void LTE_fdd_enb_interface::write_cnfg_file()
{
    if(!use_cnfg_file)
        return;
    FILE *cnfg_file = fopen("/tmp/LTE_fdd_enb.cnfg_db", "w");
    if(NULL == cnfg_file)
        return;
    fprintf(cnfg_file, "%s %s\n", bandwidth_token.c_str(), get_bandwidth_string().c_str());
    fprintf(cnfg_file, "%s %s\n", band_token.c_str(), std::to_string(get_band()).c_str());
    fprintf(cnfg_file, "%s %s\n", dl_earfcn_token.c_str(), std::to_string(dl_earfcn).c_str());
    fprintf(cnfg_file, "%s %s\n", n_ant_token.c_str(), std::to_string(N_ant).c_str());
    fprintf(cnfg_file, "%s %s\n", n_id_cell_token.c_str(), std::to_string(N_id_cell).c_str());
    fprintf(cnfg_file, "%s %s\n", mcc_token.c_str(), get_mcc_string().c_str());
    fprintf(cnfg_file, "%s %s\n", mnc_token.c_str(), get_mnc_string().c_str());
    fprintf(cnfg_file, "%s %s\n", cell_id_token.c_str(), std::to_string(get_cell_id()).c_str());
    fprintf(cnfg_file, "%s %s\n", tracking_area_code_token.c_str(), std::to_string(get_tracking_area_code()).c_str());
    fprintf(cnfg_file, "%s %s\n", q_rx_lev_min_token.c_str(), std::to_string(get_q_rx_lev_min()).c_str());
    fprintf(cnfg_file, "%s %s\n", si_periodicity_token.c_str(), get_si_periodicity_string().c_str());
    fprintf(cnfg_file, "%s %s\n", si_window_length_token.c_str(), get_si_window_length_string().c_str());
    fprintf(cnfg_file, "%s %s\n", p0_nominal_pusch_token.c_str(), std::to_string(get_p0_nominal_pusch()).c_str());
    fprintf(cnfg_file, "%s %s\n", p0_nominal_pucch_token.c_str(), std::to_string(get_p0_nominal_pucch()).c_str());
    fprintf(cnfg_file, "%s %s\n", sib3_present_token.c_str(), get_sib3_present_string().c_str());
    fprintf(cnfg_file, "%s %s\n", q_hyst_token.c_str(), get_q_hyst_string().c_str());
    fprintf(cnfg_file, "%s %s\n", sib4_present_token.c_str(), get_sib4_present_string().c_str());
    fprintf(cnfg_file, "%s %s\n", sib5_present_token.c_str(), get_sib5_present_string().c_str());
    fprintf(cnfg_file, "%s %s\n", sib6_present_token.c_str(), get_sib6_present_string().c_str());
    fprintf(cnfg_file, "%s %s\n", sib7_present_token.c_str(), get_sib7_present_string().c_str());
    fprintf(cnfg_file, "%s %s\n", sib8_present_token.c_str(), get_sib8_present_string().c_str());
    fprintf(cnfg_file, "%s %s\n", mac_direct_to_ue_token.c_str(), get_mac_direct_to_ue_string().c_str());
    fprintf(cnfg_file, "%s %s\n", phy_direct_to_ue_token.c_str(), get_phy_direct_to_ue_string().c_str());
    fprintf(cnfg_file, "%s %s\n", debug_type_token.c_str(), get_debug_type_string().c_str());
    fprintf(cnfg_file, "%s %s\n", debug_level_token.c_str(), get_debug_level_string().c_str());
    fprintf(cnfg_file, "%s %s\n", enable_pcap_token.c_str(), get_enable_pcap_string().c_str());
    fprintf(cnfg_file, "%s %s\n", ip_addr_start_token.c_str(), get_ip_addr_start_string().c_str());
    fprintf(cnfg_file, "%s %s\n", dns_addr_token.c_str(), get_dns_addr_string().c_str());
    fprintf(cnfg_file, "%s %s\n", use_user_file_token.c_str(), get_use_user_file_string().c_str());
    fclose(cnfg_file);
}
void LTE_fdd_enb_interface::delete_cnfg_file()
{
    remove("/tmp/LTE_fdd_enb.cnfg_db");
}
bool LTE_fdd_enb_interface::get_shutdown()
{
    return shutdown;
}
bool LTE_fdd_enb_interface::app_is_started()
{
    std::lock_guard<std::mutex> lock(start_mutex);
    return started;
}
void LTE_fdd_enb_interface::construct_sys_info()
{
    std::vector<uint32> sib_array;
    if(sib3_present)
        sib_array.push_back(3);
    if(sib4_present)
        sib_array.push_back(4);
    if(sib5_present)
        sib_array.push_back(5);
    if(sib6_present)
        sib_array.push_back(6);
    if(sib7_present)
        sib_array.push_back(7);
    if(sib8_present)
        sib_array.push_back(8);

    std::vector<SchedulingInfo> sched_info_list;
    SchedulingInfo::si_Periodicity_Enum si_periodicity = sys_info.sib1.schedulingInfoList_Get().Value()[0].si_Periodicity_Value();
    SchedulingInfo sched_info;
    sched_info.si_Periodicity_SetValue(si_periodicity);
    sched_info.sib_MappingInfo_Set()->SetValue({});
    sched_info_list.push_back(sched_info);
    for(auto type : sib_array)
    {
        SIB_Type sib_type;
        if(type == 3)
            sib_type.SetValue(SIB_Type::k_sibType3);
        if(type == 4)
            sib_type.SetValue(SIB_Type::k_sibType4);
        if(type == 5)
            sib_type.SetValue(SIB_Type::k_sibType5);
        if(type == 6)
            sib_type.SetValue(SIB_Type::k_sibType6);
        if(type == 7)
            sib_type.SetValue(SIB_Type::k_sibType7);
        if(type == 8)
            sib_type.SetValue(SIB_Type::k_sibType8);
        SchedulingInfo sched_info;
        sched_info.si_Periodicity_SetValue(si_periodicity);
        sched_info.sib_MappingInfo_Set()->SetValue({sib_type});
        sched_info_list.push_back(sched_info);
    }
    sys_info.sib1.schedulingInfoList_Set()->SetValue(sched_info_list);

    // Pack SIB1
    {
        BCCH_DL_SCH_Message bcch_dl_sch;
        bcch_dl_sch.message_Set()->SetChoice(BCCH_DL_SCH_MessageType::k_c1);
        bcch_dl_sch.message_Set()->c1_SetChoice(BCCH_DL_SCH_MessageType::k_c1_systemInformationBlockType1);
        bcch_dl_sch.message_Set()->c1_systemInformationBlockType1_Set(sys_info.sib1);
        std::vector<uint8_t> bits;
        bcch_dl_sch.Pack(bits);
        LIBLTE_PHY_ALLOCATION_STRUCT alloc;
        alloc.msg[0].N_bits = bits.size();
        for(uint32 i=0; i<bits.size(); i++)
            alloc.msg[0].msg[i] = bits[i];
        alloc.pre_coder_type = LIBLTE_PHY_PRE_CODER_TYPE_TX_DIVERSITY;
        alloc.mod_type       = LIBLTE_PHY_MODULATION_TYPE_QPSK;
        alloc.rv_idx         = 0; // 36.321 section 5.3.1
        alloc.N_codewords    = 1;
        alloc.rnti           = LIBLTE_MAC_SI_RNTI;
        alloc.tx_mode        = 1;
        sys_info.sib_alloc.push_back(alloc);
    }

    // Pack additional SIBs
    for(auto si : sched_info_list)
    {
        BCCH_DL_SCH_Message bcch_dl_sch;
        bcch_dl_sch.message_Set()->SetChoice(BCCH_DL_SCH_MessageType::k_c1);
        bcch_dl_sch.message_Set()->c1_SetChoice(BCCH_DL_SCH_MessageType::k_c1_systemInformation);
        bcch_dl_sch.message_Set()->c1_systemInformation_Set()->criticalExtensions_SetChoice(SystemInformation::k_criticalExtensions_systemInformation_r8);
        SystemInformation_r8_IEs::sib_TypeAndInfo_ sib;
        if(si.sib_MappingInfo_Get().Value().size() == 0)
        {
            sib.sib_TypeAndInfo_SetChoice(SystemInformation_r8_IEs::sib_TypeAndInfo_::k_sib_TypeAndInfo_sib2);
            sib.sib_TypeAndInfo_sib2_Set(sys_info.sib2);
        }else{
            switch(si.sib_MappingInfo_Get().Value()[0].Value())
            {
            case SIB_Type::k_sibType3:
                sib.sib_TypeAndInfo_SetChoice(SystemInformation_r8_IEs::sib_TypeAndInfo_::k_sib_TypeAndInfo_sib3);
                sib.sib_TypeAndInfo_sib3_Set(sys_info.sib3);
                break;
            case SIB_Type::k_sibType4:
                sib.sib_TypeAndInfo_SetChoice(SystemInformation_r8_IEs::sib_TypeAndInfo_::k_sib_TypeAndInfo_sib4);
                sib.sib_TypeAndInfo_sib4_Set(sys_info.sib4);
                break;
            case SIB_Type::k_sibType5:
                sib.sib_TypeAndInfo_SetChoice(SystemInformation_r8_IEs::sib_TypeAndInfo_::k_sib_TypeAndInfo_sib5);
                sib.sib_TypeAndInfo_sib5_Set(sys_info.sib5);
                break;
            case SIB_Type::k_sibType6:
                sib.sib_TypeAndInfo_SetChoice(SystemInformation_r8_IEs::sib_TypeAndInfo_::k_sib_TypeAndInfo_sib6);
                sib.sib_TypeAndInfo_sib6_Set(sys_info.sib6);
                break;
            case SIB_Type::k_sibType7:
                sib.sib_TypeAndInfo_SetChoice(SystemInformation_r8_IEs::sib_TypeAndInfo_::k_sib_TypeAndInfo_sib7);
                sib.sib_TypeAndInfo_sib7_Set(sys_info.sib7);
                break;
            case SIB_Type::k_sibType8:
                sib.sib_TypeAndInfo_SetChoice(SystemInformation_r8_IEs::sib_TypeAndInfo_::k_sib_TypeAndInfo_sib8);
                sib.sib_TypeAndInfo_sib8_Set(sys_info.sib8);
                break;
            default:
                break;
            }
        }
        bcch_dl_sch.message_Set()->c1_systemInformation_Set()->criticalExtensions_systemInformation_r8_Set()->sib_TypeAndInfo_SetValue({sib});
        std::vector<uint8_t> bits;
        bcch_dl_sch.Pack(bits);
        LIBLTE_PHY_ALLOCATION_STRUCT alloc;
        alloc.msg[0].N_bits = bits.size();
        for(uint32 i=0; i<bits.size(); i++)
            alloc.msg[0].msg[i] = bits[i];
        alloc.pre_coder_type = LIBLTE_PHY_PRE_CODER_TYPE_TX_DIVERSITY;
        alloc.mod_type       = LIBLTE_PHY_MODULATION_TYPE_QPSK;
        alloc.rv_idx         = 0; // 36.321 section 5.3.1
        alloc.N_codewords    = 1;
        alloc.rnti           = LIBLTE_MAC_SI_RNTI;
        alloc.tx_mode        = 1;
        sys_info.sib_alloc.push_back(alloc);
    }

    // Update all layers
    phy->update_sys_info();
    mac->update_sys_info();
    rlc->update_sys_info();
    pdcp->update_sys_info();
    rrc->update_sys_info();
    mme->update_sys_info();
}
void LTE_fdd_enb_interface::get_sys_info(LTE_FDD_ENB_SYS_INFO_STRUCT &_sys_info)
{
    memcpy((void*)&_sys_info, &sys_info, sizeof(sys_info));
}
void LTE_fdd_enb_interface::get_rrc_phy_cnfg_ded(PhysicalConfigDedicated *pcd,
                                                 uint32                   i_cqi_pmi,
                                                 uint32                   i_ri,
                                                 uint32                   i_sr,
                                                 uint32                   n_1_p_pucch)
{
    pcd->pdsch_ConfigDedicated_Clear();
    pcd->pucch_ConfigDedicated_Clear();
    pcd->pusch_ConfigDedicated_Clear();
    pcd->uplinkPowerControlDedicated_Clear();
    pcd->tpc_PDCCH_ConfigPUCCH_Clear();
    pcd->tpc_PDCCH_ConfigPUSCH_Clear();
    pcd->cqi_ReportConfig_Clear();
    pcd->soundingRS_UL_ConfigDedicated_Clear();
    pcd->antennaInfo_Clear();
    pcd->schedulingRequestConfig_Set()->SetChoice(SchedulingRequestConfig::k_setup);
    pcd->schedulingRequestConfig_Set()->setup_value.sr_PUCCH_ResourceIndex_SetValue(n_1_p_pucch);
    pcd->schedulingRequestConfig_Set()->setup_value.sr_ConfigIndex_SetValue(i_sr);
    pcd->schedulingRequestConfig_Set()->setup_value.dsr_TransMax_SetValue(SchedulingRequestConfig::setup::k_dsr_TransMax_n16);
    pcd->cqi_ReportConfig_v920_Clear();
    pcd->antennaInfo_v920_Clear();
    pcd->antennaInfo_r10_Clear();
    pcd->cif_Presence_Clear();
    pcd->cqi_ReportConfig_v10x0_Clear();
    pcd->csi_RS_Config_r10_Clear();
    pcd->pucch_ConfigDedicated_v10x0_Clear();
    pcd->pusch_ConfigDedicated_v10x0_Clear();
    pcd->schedulingRequestConfig_v10x0_Clear();
    pcd->soundingRS_UL_ConfigDedicated_v10x0_Clear();
    pcd->soundingRS_UL_ConfigDedicatedAperiodic_r10_Clear();
    pcd->ul_AntennaInfo_r10_Clear();
}
