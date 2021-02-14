/*******************************************************************************

    Copyright 2021 Ben Wojtowicz

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

    File: LTE_fdd_dl_fg_interface.cc

    Description: Contains all the implementations for the LTE FDD DL File
                 Generator interface.

    Revision History
    ----------    -------------    --------------------------------------------
    02/14/2021    Ben Wojtowicz    Created file

*******************************************************************************/

/*******************************************************************************
                              INCLUDES
*******************************************************************************/

#include "LTE_fdd_dl_fg_interface.h"

#include "libtools_helpers.h"

#include "assert.h"

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

LTE_fdd_dl_fg_interface::LTE_fdd_dl_fg_interface() :
    flowgraph{NULL}, file_name_token{"file_name"}, output_type_token{"output_type"},
    bandwidth_token{"bandwidth"}, freq_band_token{"freq_band"}, n_frames_token{"n_frames"},
    n_ant_token{"n_ant"}, n_id_cell_token{"n_id_cell"}, mcc_token{"mcc"}, mnc_token{"mnc"},
    cell_id_token{"cell_id"}, tracking_area_code_token{"tracking_area_code"},
    q_rx_lev_min_token{"q_rx_lev_min"}, p0_nominal_pusch_token{"p0_nominal_pusch"},
    p0_nominal_pucch_token{"p0_nominal_pucch"}, q_hyst_token{"q_hyst"},
    neigh_cell_list_token{"neigh_cell_list"}, search_win_size_token{"search_win_size"},
    percent_load_token{"percent_load"}, sib3_present_token{"sib3_present"},
    sib4_present_token{"sib4_present"}, sib8_present_token{"sib8_present"},
    file_name{"/tmp/LTE_fdd_dl_fg_samps.bin"}, output_type{"gr_complex"}, ctrl_socket{NULL},
    N_frames{30}, N_ant{1}, N_id_cell{0}, percent_load{0}, sib3_present{0}, sib4_present{0},
    sib8_present{0}, ctrl_connected{false}, shutdown{false}
{
    start_ctrl_port();

    // MIB
    mib.dl_Bandwidth_SetValue(MasterInformationBlock::k_dl_Bandwidth_n100);
    mib.phich_Config_Set()->phich_Duration_SetValue(PHICH_Config::k_phich_Duration_normal);
    mib.phich_Config_Set()->phich_Resource_SetValue(PHICH_Config::k_phich_Resource_one);
    mib.systemFrameNumber_SetValue(0);
    mib.spare_SetValue(0);
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
    sib1.cellAccessRelatedInfo_value.plmn_IdentityList_Set()->SetValue(plmn_id);
    sib1.cellAccessRelatedInfo_value.trackingAreaCode_Set()->SetValue(0);
    sib1.cellAccessRelatedInfo_value.cellIdentity_Set()->SetValue(0);
    sib1.cellAccessRelatedInfo_value.cellBarred_SetValue(SystemInformationBlockType1::cellAccessRelatedInfo::k_cellBarred_notBarred);
    sib1.cellAccessRelatedInfo_value.intraFreqReselection_SetValue(SystemInformationBlockType1::cellAccessRelatedInfo::k_intraFreqReselection_allowed);
    sib1.cellAccessRelatedInfo_value.csg_Indication_SetValue(false);
    sib1.cellAccessRelatedInfo_value.csg_Identity_Clear();
    sib1.cellSelectionInfo_value.q_RxLevMin_Set()->SetValue(-70);
    sib1.cellSelectionInfo_value.q_RxLevMinOffset_SetValue(1);
    sib1.p_Max_Set()->SetValue(-30);
    sib1.freqBandIndicator_SetValue(1);
    std::vector<SchedulingInfo> sched_info(1);
    sched_info[0].si_Periodicity_SetValue(SchedulingInfo::k_si_Periodicity_rf8);
    sched_info[0].sib_MappingInfo_Set()->SetValue({});
    sib1.schedulingInfoList_Set()->SetValue(sched_info);
    sib1.tdd_Config_Clear();
    sib1.si_WindowLength_SetValue(SystemInformationBlockType1::k_si_WindowLength_ms2);
    sib1.systemInfoValueTag_SetValue(0);
    sib1.nonCriticalExtension_Clear();
    // SIB2
    sib2.ac_BarringInfo_value.Clear();
    sib2.radioResourceConfigCommon_Set()->rach_ConfigCommon_Set()->preambleInfo_value.numberOfRA_Preambles_SetValue(RACH_ConfigCommon::preambleInfo::k_numberOfRA_Preambles_n64);
    sib2.radioResourceConfigCommon_Set()->rach_ConfigCommon_Set()->preambleInfo_value.preamblesGroupAConfig_value.Clear();
    sib2.radioResourceConfigCommon_Set()->rach_ConfigCommon_Set()->powerRampingParameters_value.powerRampingStep_SetValue(RACH_ConfigCommon::powerRampingParameters::k_powerRampingStep_dB6);
    sib2.radioResourceConfigCommon_Set()->rach_ConfigCommon_Set()->powerRampingParameters_value.preambleInitialReceivedTargetPower_SetValue(RACH_ConfigCommon::powerRampingParameters::k_preambleInitialReceivedTargetPower_dBm_100);
    sib2.radioResourceConfigCommon_Set()->rach_ConfigCommon_Set()->ra_SupervisionInfo_value.preambleTransMax_SetValue(RACH_ConfigCommon::ra_SupervisionInfo::k_preambleTransMax_n200);
    sib2.radioResourceConfigCommon_Set()->rach_ConfigCommon_Set()->ra_SupervisionInfo_value.ra_ResponseWindowSize_SetValue(RACH_ConfigCommon::ra_SupervisionInfo::k_ra_ResponseWindowSize_sf10);
    sib2.radioResourceConfigCommon_Set()->rach_ConfigCommon_Set()->ra_SupervisionInfo_value.mac_ContentionResolutionTimer_SetValue(RACH_ConfigCommon::ra_SupervisionInfo::k_mac_ContentionResolutionTimer_sf64);
    sib2.radioResourceConfigCommon_Set()->rach_ConfigCommon_Set()->maxHARQ_Msg3Tx_SetValue(1);
    sib2.radioResourceConfigCommon_Set()->bcch_Config_Set()->modificationPeriodCoeff_SetValue(BCCH_Config::k_modificationPeriodCoeff_n2);
    sib2.radioResourceConfigCommon_Set()->pcch_Config_Set()->defaultPagingCycle_SetValue(PCCH_Config::k_defaultPagingCycle_rf256);
    sib2.radioResourceConfigCommon_Set()->pcch_Config_Set()->nB_SetValue(PCCH_Config::k_nB_oneT);
    sib2.radioResourceConfigCommon_Set()->prach_Config_Set()->rootSequenceIndex_SetValue(0);
    sib2.radioResourceConfigCommon_Set()->prach_Config_Set()->prach_ConfigInfo_Set()->prach_ConfigIndex_SetValue(0);
    sib2.radioResourceConfigCommon_Set()->prach_Config_Set()->prach_ConfigInfo_Set()->highSpeedFlag_SetValue(false);
    sib2.radioResourceConfigCommon_Set()->prach_Config_Set()->prach_ConfigInfo_Set()->zeroCorrelationZoneConfig_SetValue(0);
    sib2.radioResourceConfigCommon_Set()->prach_Config_Set()->prach_ConfigInfo_Set()->prach_FreqOffset_SetValue(0);
    sib2.radioResourceConfigCommon_Set()->pdsch_ConfigCommon_Set()->referenceSignalPower_SetValue(-60);
    sib2.radioResourceConfigCommon_Set()->pdsch_ConfigCommon_Set()->p_b_SetValue(0);
    sib2.radioResourceConfigCommon_Set()->pusch_ConfigCommon_Set()->pusch_ConfigBasic_value.n_SB_SetValue(1);
    sib2.radioResourceConfigCommon_Set()->pusch_ConfigCommon_Set()->pusch_ConfigBasic_value.hoppingMode_SetValue(PUSCH_ConfigCommon::pusch_ConfigBasic::k_hoppingMode_interSubFrame);
    sib2.radioResourceConfigCommon_Set()->pusch_ConfigCommon_Set()->pusch_ConfigBasic_value.pusch_HoppingOffset_SetValue(0);
    sib2.radioResourceConfigCommon_Set()->pusch_ConfigCommon_Set()->pusch_ConfigBasic_value.enable64QAM_SetValue(true);
    sib2.radioResourceConfigCommon_Set()->pusch_ConfigCommon_Set()->ul_ReferenceSignalsPUSCH_Set()->groupHoppingEnabled_SetValue(false);
    sib2.radioResourceConfigCommon_Set()->pusch_ConfigCommon_Set()->ul_ReferenceSignalsPUSCH_Set()->groupAssignmentPUSCH_SetValue(0);
    sib2.radioResourceConfigCommon_Set()->pusch_ConfigCommon_Set()->ul_ReferenceSignalsPUSCH_Set()->sequenceHoppingEnabled_SetValue(false);
    sib2.radioResourceConfigCommon_Set()->pusch_ConfigCommon_Set()->ul_ReferenceSignalsPUSCH_Set()->cyclicShift_SetValue(0);
    sib2.radioResourceConfigCommon_Set()->pucch_ConfigCommon_Set()->deltaPUCCH_Shift_SetValue(PUCCH_ConfigCommon::k_deltaPUCCH_Shift_ds1);
    sib2.radioResourceConfigCommon_Set()->pucch_ConfigCommon_Set()->nRB_CQI_SetValue(0);
    sib2.radioResourceConfigCommon_Set()->pucch_ConfigCommon_Set()->nCS_AN_SetValue(0);
    sib2.radioResourceConfigCommon_Set()->pucch_ConfigCommon_Set()->n1PUCCH_AN_SetValue(0);
    sib2.radioResourceConfigCommon_Set()->soundingRS_UL_ConfigCommon_Set()->SetChoice(SoundingRS_UL_ConfigCommon::k_release);
    sib2.radioResourceConfigCommon_Set()->uplinkPowerControlCommon_Set()->p0_NominalPUSCH_SetValue(-70);
    sib2.radioResourceConfigCommon_Set()->uplinkPowerControlCommon_Set()->alpha_SetValue(UplinkPowerControlCommon::k_alpha_al1);
    sib2.radioResourceConfigCommon_Set()->uplinkPowerControlCommon_Set()->p0_NominalPUCCH_SetValue(-96);
    sib2.radioResourceConfigCommon_Set()->uplinkPowerControlCommon_Set()->deltaFList_PUCCH_Set()->deltaF_PUCCH_Format1_SetValue(DeltaFList_PUCCH::k_deltaF_PUCCH_Format1_deltaF0);
    sib2.radioResourceConfigCommon_Set()->uplinkPowerControlCommon_Set()->deltaFList_PUCCH_Set()->deltaF_PUCCH_Format1b_SetValue(DeltaFList_PUCCH::k_deltaF_PUCCH_Format1b_deltaF1);
    sib2.radioResourceConfigCommon_Set()->uplinkPowerControlCommon_Set()->deltaFList_PUCCH_Set()->deltaF_PUCCH_Format2_SetValue(DeltaFList_PUCCH::k_deltaF_PUCCH_Format2_deltaF0);
    sib2.radioResourceConfigCommon_Set()->uplinkPowerControlCommon_Set()->deltaFList_PUCCH_Set()->deltaF_PUCCH_Format2a_SetValue(DeltaFList_PUCCH::k_deltaF_PUCCH_Format2a_deltaF0);
    sib2.radioResourceConfigCommon_Set()->uplinkPowerControlCommon_Set()->deltaFList_PUCCH_Set()->deltaF_PUCCH_Format2b_SetValue(DeltaFList_PUCCH::k_deltaF_PUCCH_Format2b_deltaF0);
    sib2.radioResourceConfigCommon_Set()->uplinkPowerControlCommon_Set()->deltaPreambleMsg3_SetValue(-1);
    sib2.radioResourceConfigCommon_Set()->ul_CyclicPrefixLength_Set()->SetValue(UL_CyclicPrefixLength::k_len1);
    sib2.ue_TimersAndConstants_Set()->t300_SetValue(UE_TimersAndConstants::k_t300_ms1000);
    sib2.ue_TimersAndConstants_Set()->t301_SetValue(UE_TimersAndConstants::k_t301_ms1000);
    sib2.ue_TimersAndConstants_Set()->t310_SetValue(UE_TimersAndConstants::k_t310_ms1000);
    sib2.ue_TimersAndConstants_Set()->n310_SetValue(UE_TimersAndConstants::k_n310_n20);
    sib2.ue_TimersAndConstants_Set()->t311_SetValue(UE_TimersAndConstants::k_t311_ms1000);
    sib2.ue_TimersAndConstants_Set()->n311_SetValue(UE_TimersAndConstants::k_n311_n10);
    sib2.freqInfo_value.ul_CarrierFreq_Clear();
    sib2.freqInfo_value.ul_Bandwidth_Clear();
    sib2.freqInfo_value.additionalSpectrumEmission_Set()->SetValue(1);
    sib2.timeAlignmentTimerCommon_Set()->SetValue(TimeAlignmentTimer::k_sf500);
    // SIB3
    sib3.cellReselectionInfoCommon_value.q_Hyst_SetValue(SystemInformationBlockType3::cellReselectionInfoCommon::k_q_Hyst_dB0);
    sib3.cellReselectionInfoCommon_value.speedStateReselectionPars_value.Clear();
    sib3.cellReselectionServingFreqInfo_value.s_NonIntraSearch_Clear();
    sib3.cellReselectionServingFreqInfo_value.threshServingLow_Set()->SetValue(0);
    sib3.cellReselectionServingFreqInfo_value.cellReselectionPriority_Set()->SetValue(0);
    sib3.intraFreqCellReselectionInfo_value.q_RxLevMin_Set()->SetValue(sib1.cellSelectionInfo_value.q_RxLevMin_Get().Value());
    sib3.intraFreqCellReselectionInfo_value.p_Max_Set()->SetValue(sib1.p_Max_Get().Value());
    sib3.intraFreqCellReselectionInfo_value.s_IntraSearch_Clear();
    sib3.intraFreqCellReselectionInfo_value.allowedMeasBandwidth_Clear();
    sib3.intraFreqCellReselectionInfo_value.presenceAntennaPort1_Set()->SetValue(false);
    sib3.intraFreqCellReselectionInfo_value.neighCellConfig_Set()->SetValue(0);
    sib3.intraFreqCellReselectionInfo_value.t_ReselectionEUTRA_Set()->SetValue(0);
    sib3.intraFreqCellReselectionInfo_value.t_ReselectionEUTRA_SF_Clear();
    // SIB4
    sib4.intraFreqNeighCellList_Clear();
    sib4.intraFreqBlackCellList_Clear();
    sib4.csg_PhysCellIdRange_Clear();
    // SIB8
    sib8.systemTimeInfo_Clear();
    sib8.searchWindowSize_SetValue(0);
    sib8.parametersHRPD_value.Clear();
    sib8.parameters1XRTT_value.Clear();
}

LTE_fdd_dl_fg_interface::~LTE_fdd_dl_fg_interface()
{
    stop_ctrl_port();
}

void LTE_fdd_dl_fg_interface::start_ctrl_port()
{
    std::lock_guard<std::mutex> lock(ctrl_mutex);

    if(NULL != ctrl_socket)
        return;

    libtools_server_socket_receive_callback receive_cb(
        &libtools_server_socket_receive_callback::wrapper<LTE_fdd_dl_fg_interface, &LTE_fdd_dl_fg_interface::handle_ctrl_msg>,
        this);
    libtools_server_socket_connect_disconnect_callback connect_cb(
        &libtools_server_socket_connect_disconnect_callback::wrapper<LTE_fdd_dl_fg_interface, &LTE_fdd_dl_fg_interface::handle_ctrl_connect>,
        this);
    libtools_server_socket_connect_disconnect_callback disconnect_cb(
        &libtools_server_socket_connect_disconnect_callback::wrapper<LTE_fdd_dl_fg_interface, &LTE_fdd_dl_fg_interface::handle_ctrl_disconnect>,
        this);
    libtools_server_socket_error_callback error_cb(
        &libtools_server_socket_error_callback::wrapper<LTE_fdd_dl_fg_interface, &LTE_fdd_dl_fg_interface::handle_ctrl_error>,
        this);

    LIBTOOLS_SERVER_SOCKET_ERROR_ENUM err;
    ctrl_socket = new libtools_server_socket(LTE_FDD_DL_FG_CTRL_PORT, receive_cb, connect_cb,
                                             disconnect_cb, error_cb, err);
    if(err == LIBTOOLS_SERVER_SOCKET_ERROR_NONE)
        return;
    printf("ERROR: Couldn't open ctrl_socket %u\n", err);
    ctrl_socket = NULL;
}

void LTE_fdd_dl_fg_interface::stop_ctrl_port()
{
    std::lock_guard<std::mutex> lock(ctrl_mutex);

    if(NULL == ctrl_socket)
        return;

    delete ctrl_socket;
    ctrl_socket = NULL;
}

void LTE_fdd_dl_fg_interface::send_ctrl_msg(std::string msg)
{
    std::lock_guard<std::mutex> lock(ctrl_mutex);

    if(!ctrl_connected)
        return;

    ctrl_socket->send(msg + "\n", ctrl_sock_fd);
}

void LTE_fdd_dl_fg_interface::handle_ctrl_msg(const std::string msg,
                                              const int32       sock_fd)
{
    if(0 == msg.find("shutdown"))
    {
        send_ctrl_msg("ok");
        shutdown = true;
        return;
    }
    if(0 == msg.find("start"))
        return handle_start();
    if(0 == msg.find("stop"))
        return handle_stop();
    if(0 == msg.find("read"))
        return handle_read(msg);
    if(0 == msg.find("write"))
        return handle_write(msg);
    if(0 == msg.find("help"))
        return handle_help();
    send_ctrl_msg("fail invalid command");
}

void LTE_fdd_dl_fg_interface::handle_ctrl_connect(const int32 sock_fd)
{
    ctrl_mutex.lock();
    ctrl_connected = true;
    ctrl_sock_fd   = sock_fd;
    ctrl_mutex.unlock();

    send_ctrl_msg("*** LTE FDD DL FILE GENERATOR ***");
    send_ctrl_msg("Type help to see a list of commands");
}

void LTE_fdd_dl_fg_interface::handle_ctrl_disconnect(const int32 sock_fd)
{
    std::lock_guard<std::mutex> lock(ctrl_mutex);

    ctrl_connected = false;
}

void LTE_fdd_dl_fg_interface::handle_ctrl_error(const LIBTOOLS_SERVER_SOCKET_ERROR_ENUM err)
{
    printf("ERROR: ctrl_socket error %u\n", err);
    assert(0);
}

void LTE_fdd_dl_fg_interface::handle_read(std::string msg)
{
    if(0 != msg.find("read "))
        return send_ctrl_msg("fail invalid read command");
    std::string param = msg.substr(5);
    if(0 == param.find(file_name_token))
        return send_ctrl_msg("ok " + file_name);
    if(0 == param.find(output_type_token))
        return send_ctrl_msg("ok " + output_type);
    if(0 == param.find(bandwidth_token))
        return send_ctrl_msg("ok " + bandwidth_to_string());
    if(0 == param.find(freq_band_token))
        return send_ctrl_msg("ok " + std::to_string(sib1.freqBandIndicator_Value()));
    if(0 == param.find(n_frames_token))
        return send_ctrl_msg("ok " + std::to_string(N_frames));
    if(0 == param.find(n_ant_token))
        return send_ctrl_msg("ok " + std::to_string(N_ant));
    if(0 == param.find(n_id_cell_token))
        return send_ctrl_msg("ok " + std::to_string(N_id_cell));
    if(0 == param.find(mcc_token))
        return send_ctrl_msg("ok " +
                             std::to_string(sib1.cellAccessRelatedInfo_value.plmn_IdentityList_Get().Value()[0].plmn_Identity_Get().mcc_Get().Value()[0].Value()) +
                             std::to_string(sib1.cellAccessRelatedInfo_value.plmn_IdentityList_Get().Value()[0].plmn_Identity_Get().mcc_Get().Value()[1].Value()) +
                             std::to_string(sib1.cellAccessRelatedInfo_value.plmn_IdentityList_Get().Value()[0].plmn_Identity_Get().mcc_Get().Value()[2].Value()));
    if(0 == param.find(mnc_token))
    {
        if(sib1.cellAccessRelatedInfo_value.plmn_IdentityList_Get().Value()[0].plmn_Identity_Get().mnc_Get().Value().size() == 2)
            return send_ctrl_msg("ok " +
                                 std::to_string(sib1.cellAccessRelatedInfo_value.plmn_IdentityList_Get().Value()[0].plmn_Identity_Get().mnc_Get().Value()[0].Value()) +
                                 std::to_string(sib1.cellAccessRelatedInfo_value.plmn_IdentityList_Get().Value()[0].plmn_Identity_Get().mnc_Get().Value()[1].Value()));
        return send_ctrl_msg("ok " +
                             std::to_string(sib1.cellAccessRelatedInfo_value.plmn_IdentityList_Get().Value()[0].plmn_Identity_Get().mnc_Get().Value()[0].Value()) +
                             std::to_string(sib1.cellAccessRelatedInfo_value.plmn_IdentityList_Get().Value()[0].plmn_Identity_Get().mnc_Get().Value()[1].Value()) +
                             std::to_string(sib1.cellAccessRelatedInfo_value.plmn_IdentityList_Get().Value()[0].plmn_Identity_Get().mnc_Get().Value()[2].Value()));
    }
    if(0 == param.find(cell_id_token))
        return send_ctrl_msg("ok " + std::to_string(sib1.cellAccessRelatedInfo_value.cellIdentity_Get().Value()));
    if(0 == param.find(tracking_area_code_token))
        return send_ctrl_msg("ok " + std::to_string(sib1.cellAccessRelatedInfo_value.trackingAreaCode_Get().Value()));
    if(0 == param.find(q_rx_lev_min_token))
        return send_ctrl_msg("ok " + std::to_string(sib1.cellSelectionInfo_value.q_RxLevMin_Get().Value()));
    if(0 == param.find(p0_nominal_pusch_token))
        return send_ctrl_msg("ok " + std::to_string(sib2.radioResourceConfigCommon_Get().uplinkPowerControlCommon_Get().p0_NominalPUSCH_Value()));
    if(0 == param.find(p0_nominal_pucch_token))
        return send_ctrl_msg("ok " + std::to_string(sib2.radioResourceConfigCommon_Get().uplinkPowerControlCommon_Get().p0_NominalPUCCH_Value()));
    if(0 == param.find(q_hyst_token))
        return send_ctrl_msg("ok " + sib3.cellReselectionInfoCommon_value.q_Hyst_ValueToString(sib3.cellReselectionInfoCommon_value.q_Hyst_Value()));
    if(0 == param.find(neigh_cell_list_token))
        return send_ctrl_msg("ok " + neigh_cell_list_to_string());
    if(0 == param.find(search_win_size_token))
        return send_ctrl_msg("ok " + std::to_string(sib8.searchWindowSize_Value()));
    if(0 == param.find(percent_load_token))
        return send_ctrl_msg("ok " + std::to_string(percent_load));
    if(0 == param.find(sib3_present_token))
        return send_ctrl_msg("ok " + std::to_string(sib3_present));
    if(0 == param.find(sib4_present_token))
        return send_ctrl_msg("ok " + std::to_string(sib4_present));
    if(0 == param.find(sib8_present_token))
        return send_ctrl_msg("ok " + std::to_string(sib8_present));
    send_ctrl_msg("fail invalid read parameter");
}

void LTE_fdd_dl_fg_interface::handle_write(std::string msg)
{
    if(0 != msg.find("write "))
        return send_ctrl_msg("fail invalid write command");
    std::string param = msg.substr(6);
    int64 value;
    if(0 == param.find(file_name_token + " "))
    {
        file_name = param.substr(file_name_token.length()+1);
        return send_ctrl_msg("ok");
    }
    if(0 == param.find(output_type_token + " "))
    {
        if(0 == param.substr(output_type_token.length()+1).find("int8"))
        {
            output_type = "int8";
            return send_ctrl_msg("ok");
        }
        if(0 == param.substr(output_type_token.length()+1).find("gr_complex"))
        {
            output_type = "gr_complex";
            return send_ctrl_msg("ok");
        }
        return send_ctrl_msg("fail invalid output_type");
    }
    if(0 == param.find(bandwidth_token + " "))
        return write_bandwidth(param.substr(bandwidth_token.length()+1));
    if(0 == param.find(freq_band_token + " "))
    {
        if(to_number(param.substr(freq_band_token.length()+1), value, 1, 25) ||
           sib1.freqBandIndicator_SetValue(value))
            return send_ctrl_msg("fail invalid " + freq_band_token);
        return send_ctrl_msg("ok");
    }
    if(0 == param.find(n_frames_token + " "))
    {
        if(to_number(param.substr(n_frames_token.length()+1), value, 1, 1000))
            return send_ctrl_msg("fail invalid " + n_frames_token);
        N_frames = value;
        return send_ctrl_msg("ok");
    }
    if(0 == param.find(n_ant_token + " "))
    {
        if(to_number(param.substr(n_ant_token.length()+1), value, 1, 4) || value == 3)
            return send_ctrl_msg("fail invalid " + n_ant_token);
        N_ant = value;
        return send_ctrl_msg("ok");
    }
    if(0 == param.find(n_id_cell_token + " "))
    {
        if(to_number(param.substr(n_id_cell_token.length()+1), value, 0, 503))
            return send_ctrl_msg("fail invalid " + n_id_cell_token);
        N_id_cell = value;
        return send_ctrl_msg("ok");
    }
    if(0 == param.find(mcc_token + " "))
        return write_mcc(param.substr(mcc_token.length()+1));
    if(0 == param.find(mnc_token + " "))
        return write_mnc(param.substr(mnc_token.length()+1));
    if(0 == param.find(cell_id_token + " "))
    {
        if(to_number(param.substr(cell_id_token.length()+1), value, 0, 268435455) ||
           sib1.cellAccessRelatedInfo_value.cellIdentity_Set()->SetValue(value))
            return send_ctrl_msg("fail invalid " + cell_id_token);
        return send_ctrl_msg("ok");
    }
    if(0 == param.find(tracking_area_code_token + " "))
    {
        if(to_number(param.substr(tracking_area_code_token.length()+1), value, 0, 65535) ||
           sib1.cellAccessRelatedInfo_value.trackingAreaCode_Set()->SetValue(value))
            return send_ctrl_msg("fail invalid " + tracking_area_code_token);
        return send_ctrl_msg("ok");
    }
    if(0 == param.find(q_rx_lev_min_token + " "))
    {
        if(to_number(param.substr(q_rx_lev_min_token.length()+1), value, -70, -22) ||
           sib1.cellSelectionInfo_value.q_RxLevMin_Set()->SetValue(value) ||
           sib3.intraFreqCellReselectionInfo_value.q_RxLevMin_Set()->SetValue(sib1.cellSelectionInfo_value.q_RxLevMin_Set()->Value()))
            return send_ctrl_msg("fail invalid " + q_rx_lev_min_token);
        return send_ctrl_msg("ok");
    }
    if(0 == param.find(p0_nominal_pusch_token + " "))
    {
        if(to_number(param.substr(p0_nominal_pusch_token.length()+1), value, -126, 24) ||
           sib2.radioResourceConfigCommon_Set()->uplinkPowerControlCommon_Set()->p0_NominalPUSCH_SetValue(value))
            return send_ctrl_msg("fail invalid " + p0_nominal_pusch_token);
        return send_ctrl_msg("ok");
    }
    if(0 == param.find(p0_nominal_pucch_token + " "))
    {
        if(to_number(param.substr(p0_nominal_pucch_token.length()+1), value, -127, -96) ||
           sib2.radioResourceConfigCommon_Set()->uplinkPowerControlCommon_Set()->p0_NominalPUCCH_SetValue(value))
            return send_ctrl_msg("fail invalid " + p0_nominal_pucch_token);
        return send_ctrl_msg("ok");
    }
    if(0 == param.find(q_hyst_token + " "))
    {
        if(sib3.cellReselectionInfoCommon_value.q_Hyst_SetValue(param.substr(q_hyst_token.length()+1)))
            return send_ctrl_msg("fail invalid " + q_hyst_token);
        return send_ctrl_msg("ok");
    }
    if(0 == param.find(neigh_cell_list_token + " "))
        return write_neigh_cell_list(param.substr(neigh_cell_list_token.length()+1));
    if(0 == param.find(search_win_size_token + " "))
    {
        if(to_number(param.substr(search_win_size_token.length()+1), value, 0, 15) ||
           sib8.searchWindowSize_SetValue(value))
            return send_ctrl_msg("fail invalid " + search_win_size_token);
        return send_ctrl_msg("ok");
    }
    if(0 == param.find(percent_load_token + " "))
    {
        if(to_number(param.substr(percent_load_token.length()+1), value, 0, 100))
            return send_ctrl_msg("fail invalid " + percent_load_token);
        percent_load = value;
        return send_ctrl_msg("ok");
    }
    if(0 == param.find(sib3_present_token + " "))
    {
        if(to_number(param.substr(sib3_present_token.length()+1), value, 0, 1))
            return send_ctrl_msg("fail invalid " + sib3_present_token);
        sib3_present = value;
        return send_ctrl_msg("ok");
    }
    if(0 == param.find(sib4_present_token + " "))
    {
        if(to_number(param.substr(sib4_present_token.length()+1), value, 0, 1))
            return send_ctrl_msg("fail invalid " + sib4_present_token);
        sib4_present = value;
        return send_ctrl_msg("ok");
    }
    if(0 == param.find(sib8_present_token + " "))
    {
        if(to_number(param.substr(sib8_present_token.length()+1), value, 0, 1))
            return send_ctrl_msg("fail invalid " + sib8_present_token);
        sib8_present = value;
        return send_ctrl_msg("ok");
    }
    send_ctrl_msg("fail invalid write parameter");
}

std::string LTE_fdd_dl_fg_interface::bandwidth_to_string()
{
    switch(mib.dl_Bandwidth_Value())
    {
    case MasterInformationBlock::k_dl_Bandwidth_n6:
        return "1.4";
    case MasterInformationBlock::k_dl_Bandwidth_n15:
        return "3";
    case MasterInformationBlock::k_dl_Bandwidth_n25:
        return "5";
    case MasterInformationBlock::k_dl_Bandwidth_n50:
        return "10";
    case MasterInformationBlock::k_dl_Bandwidth_n75:
        return "15";
    case MasterInformationBlock::k_dl_Bandwidth_n100:
        return "20";
    }
    return "";
}

void LTE_fdd_dl_fg_interface::write_bandwidth(std::string bw)
{
    if(0 == bw.find("1.4"))
    {
        mib.dl_Bandwidth_SetValue(MasterInformationBlock::k_dl_Bandwidth_n6);
        return send_ctrl_msg("ok");
    }
    if(0 == bw.find("3"))
    {
        mib.dl_Bandwidth_SetValue(MasterInformationBlock::k_dl_Bandwidth_n15);
        return send_ctrl_msg("ok");
    }
    if(0 == bw.find("5"))
    {
        mib.dl_Bandwidth_SetValue(MasterInformationBlock::k_dl_Bandwidth_n25);
        return send_ctrl_msg("ok");
    }
    if(0 == bw.find("10"))
    {
        mib.dl_Bandwidth_SetValue(MasterInformationBlock::k_dl_Bandwidth_n50);
        return send_ctrl_msg("ok");
    }
    if(0 == bw.find("15"))
    {
        mib.dl_Bandwidth_SetValue(MasterInformationBlock::k_dl_Bandwidth_n75);
        return send_ctrl_msg("ok");
    }
    if(0 == bw.find("20"))
    {
        mib.dl_Bandwidth_SetValue(MasterInformationBlock::k_dl_Bandwidth_n100);
        return send_ctrl_msg("ok");
    }
    send_ctrl_msg("fail invalid bandwidth");
}

void LTE_fdd_dl_fg_interface::write_mcc(std::string mcc_value)
{
    if(3 != mcc_value.length())
        return send_ctrl_msg("fail invalid mcc");

    std::vector<MCC_MNC_Digit> mcc(3);
    for(uint32 i=0; i<3; i++)
        mcc[i].SetValue((uint32)(mcc_value[i] & 0xF));
    std::vector<PLMN_IdentityInfo> plmn_ids = sib1.cellAccessRelatedInfo_value.plmn_IdentityList_Set()->Value();
    plmn_ids[0].plmn_Identity_Set()->mcc_Set()->SetValue(mcc);
    sib1.cellAccessRelatedInfo_value.plmn_IdentityList_Set()->SetValue(plmn_ids);
    send_ctrl_msg("ok");
}

void LTE_fdd_dl_fg_interface::write_mnc(std::string mnc_value)
{
    if(2 != mnc_value.length() && 3 != mnc_value.length())
        return send_ctrl_msg("fail invalid mnc");

    std::vector<MCC_MNC_Digit> mnc(mnc_value.length());
    for(uint32 i=0; i<mnc_value.length(); i++)
        mnc[i].SetValue((uint32)(mnc_value[i] & 0xF));
    std::vector<PLMN_IdentityInfo> plmn_ids = sib1.cellAccessRelatedInfo_value.plmn_IdentityList_Set()->Value();
    plmn_ids[0].plmn_Identity_Set()->mnc_Set()->SetValue(mnc);
    sib1.cellAccessRelatedInfo_value.plmn_IdentityList_Set()->SetValue(plmn_ids);
    send_ctrl_msg("ok");
}

std::string LTE_fdd_dl_fg_interface::neigh_cell_list_to_string()
{
    if(!sib4.intraFreqNeighCellList_IsPresent())
        return "0:";
    std::string tmp = std::to_string(sib4.intraFreqNeighCellList_Get().Value().size());
    tmp += ":";
    for(auto nc : sib4.intraFreqNeighCellList_Get().Value())
    {
        tmp += std::to_string(nc.physCellId_Get().Value()) + ',';
        tmp += nc.q_OffsetCell_Get().ValueToString(nc.q_OffsetCell_Get().Value()) + ';';
    }
    return tmp;
}

void LTE_fdd_dl_fg_interface::write_neigh_cell_list(std::string neigh_cell_list)
{
    size_t colon_idx = neigh_cell_list.find(":");
    if(std::string::npos == colon_idx)
        return send_ctrl_msg("fail invalid neigh_cell_list");
    std::string size_value = neigh_cell_list.substr(0, colon_idx);
    int64 size;
    if(to_number(size_value, size, 0, maxCellIntra))
        return send_ctrl_msg("fail invalid_neigh_cell_list");
    std::vector<IntraFreqNeighCellInfo> neigh_list(size);
    std::string tmp_str = neigh_cell_list.substr(colon_idx+1);
    for(uint32 i=0; i<size; i++)
    {
        size_t comma_idx = tmp_str.find(",");
        int64 value;
        if(std::string::npos == comma_idx ||
           to_number(tmp_str.substr(0, comma_idx), value, 0, 503) ||
           neigh_list[i].physCellId_Set()->SetValue(value))
            return send_ctrl_msg("fail invalid neigh_cell_list");
        tmp_str = tmp_str.substr(comma_idx+1);
        size_t semi_colon_idx = tmp_str.find(";");
        if(std::string::npos == semi_colon_idx ||
           neigh_list[i].q_OffsetCell_Set()->SetValue(tmp_str.substr(0, semi_colon_idx)))
            return send_ctrl_msg("fail invalid neigh_cell_list");
        tmp_str = tmp_str.substr(semi_colon_idx+1);
    }
    sib4.intraFreqNeighCellList_Set()->SetValue(neigh_list);
    send_ctrl_msg("ok");
}

void LTE_fdd_dl_fg_interface::handle_start()
{
    if(flowgraph != NULL)
        return send_ctrl_msg("fail already started");

    if(samp_buf.get() != NULL)
        samp_buf.reset();
    size_t samp_size = sizeof(int8);
    if(output_type == "gr_complex")
        samp_size = sizeof(gr_complex);
    samp_buf = LTE_fdd_dl_fg_make_samp_buf(samp_size);
    samp_buf.get()->set_parameters(&mib, &sib1, &sib2, &sib3, &sib4, &sib8, &N_frames, &N_ant,
                                   &N_id_cell, &percent_load, &sib3_present, &sib4_present,
                                   &sib8_present);
    flowgraph = new LTE_fdd_dl_fg_flowgraph();
    if(flowgraph->start(file_name, samp_buf, samp_size))
        return send_ctrl_msg("fail start issue");
    send_ctrl_msg("ok");
}

void LTE_fdd_dl_fg_interface::handle_stop()
{
    if(flowgraph == NULL)
        return send_ctrl_msg("fail not started");

    if(flowgraph->stop())
        return send_ctrl_msg("fail stop issue");
    delete flowgraph;
    flowgraph = NULL;
    samp_buf.reset();
    send_ctrl_msg("ok");
}

void LTE_fdd_dl_fg_interface::handle_help()
{
    send_ctrl_msg("*** LTE FDD DL FILE GENERATOR HELP ***");
    send_ctrl_msg("Commands:");
    send_ctrl_msg("\tstart    - Starts generating the output file with the current parameters");
    send_ctrl_msg("\tstop     - Stops generating the output file");
    send_ctrl_msg("\tshutdown - Shuts down the entire application");
    send_ctrl_msg("\thelp     - Prints this screen");
    send_ctrl_msg("\tread     - Reads the specified parameter (read <param>)");
    send_ctrl_msg("\twrite    - Writes the specified parameter (write <param> <value>)");
    send_ctrl_msg("Parameters:");
    send_ctrl_msg("\t\t" + file_name_token + " = " + file_name);
    send_ctrl_msg("\t\t" + output_type_token + " = " + output_type);
    send_ctrl_msg("\t\t" + bandwidth_token + " = " + bandwidth_to_string());
    send_ctrl_msg("\t\t" + freq_band_token + " = " + std::to_string(sib1.freqBandIndicator_Value()));
    send_ctrl_msg("\t\t" + n_frames_token + " = " + std::to_string(N_frames));
    send_ctrl_msg("\t\t" + n_ant_token + " = " + std::to_string(N_ant));
    send_ctrl_msg("\t\t" + n_id_cell_token + " = " + std::to_string(N_id_cell));
    send_ctrl_msg("\t\t" + mcc_token + " = " +
                  std::to_string(sib1.cellAccessRelatedInfo_value.plmn_IdentityList_Get().Value()[0].plmn_Identity_Get().mcc_Get().Value()[0].Value()) +
                  std::to_string(sib1.cellAccessRelatedInfo_value.plmn_IdentityList_Get().Value()[0].plmn_Identity_Get().mcc_Get().Value()[1].Value()) +
                  std::to_string(sib1.cellAccessRelatedInfo_value.plmn_IdentityList_Get().Value()[0].plmn_Identity_Get().mcc_Get().Value()[2].Value()));
    if(sib1.cellAccessRelatedInfo_value.plmn_IdentityList_Get().Value()[0].plmn_Identity_Get().mnc_Get().Value().size() == 2)
    {
        send_ctrl_msg("\t\t" + mnc_token + " = " +
                      std::to_string(sib1.cellAccessRelatedInfo_value.plmn_IdentityList_Get().Value()[0].plmn_Identity_Get().mnc_Get().Value()[0].Value()) +
                      std::to_string(sib1.cellAccessRelatedInfo_value.plmn_IdentityList_Get().Value()[0].plmn_Identity_Get().mnc_Get().Value()[1].Value()));
    }else{
        send_ctrl_msg("\t\t" + mnc_token + " = " +
                      std::to_string(sib1.cellAccessRelatedInfo_value.plmn_IdentityList_Get().Value()[0].plmn_Identity_Get().mnc_Get().Value()[0].Value()) +
                      std::to_string(sib1.cellAccessRelatedInfo_value.plmn_IdentityList_Get().Value()[0].plmn_Identity_Get().mnc_Get().Value()[1].Value()) +
                      std::to_string(sib1.cellAccessRelatedInfo_value.plmn_IdentityList_Get().Value()[0].plmn_Identity_Get().mnc_Get().Value()[2].Value()));
    }
    send_ctrl_msg("\t\t" + cell_id_token + " = " + std::to_string(sib1.cellAccessRelatedInfo_value.cellIdentity_Get().Value()));
    send_ctrl_msg("\t\t" + tracking_area_code_token + " = " + std::to_string(sib1.cellAccessRelatedInfo_value.trackingAreaCode_Get().Value()));
    send_ctrl_msg("\t\t" + q_rx_lev_min_token + " = " + std::to_string(sib1.cellSelectionInfo_value.q_RxLevMin_Get().Value()));
    send_ctrl_msg("\t\t" + p0_nominal_pusch_token + " = " + std::to_string(sib2.radioResourceConfigCommon_Get().uplinkPowerControlCommon_Get().p0_NominalPUSCH_Value()));
    send_ctrl_msg("\t\t" + p0_nominal_pucch_token + " = " + std::to_string(sib2.radioResourceConfigCommon_Get().uplinkPowerControlCommon_Get().p0_NominalPUCCH_Value()));
    send_ctrl_msg("\t\t" + q_hyst_token + " = " + sib3.cellReselectionInfoCommon_value.q_Hyst_ValueToString(sib3.cellReselectionInfoCommon_value.q_Hyst_Value()));
    send_ctrl_msg("\t\t" + neigh_cell_list_token + " = " + neigh_cell_list_to_string());
    send_ctrl_msg("\t\t" + search_win_size_token + " = " + std::to_string(sib8.searchWindowSize_Value()));
    send_ctrl_msg("\t\t" + percent_load_token + " = " + std::to_string(percent_load));
    send_ctrl_msg("\t\t" + sib3_present_token + " = " + std::to_string(sib3_present));
    send_ctrl_msg("\t\t" + sib4_present_token + " = " + std::to_string(sib4_present));
    send_ctrl_msg("\t\t" + sib8_present_token + " = " + std::to_string(sib8_present));
}

bool LTE_fdd_dl_fg_interface::get_shutdown()
{
    return shutdown;
}
