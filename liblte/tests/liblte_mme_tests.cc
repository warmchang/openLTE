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

    File: liblte_mme_tests.cc

    Description: Contains all the tests for the LTE MME library.

    Revision History
    ----------    -------------    --------------------------------------------
    02/14/2021    Ben Wojtowicz    Created file.

*******************************************************************************/

/*******************************************************************************
                              INCLUDES
*******************************************************************************/

#include "liblte_mme.h"
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
                              FUNCTIONS
*******************************************************************************/

int additional_information_test(void)
{
//    Additional_Information add_info;
//    if(0 != add_info.SetValue({0xA5, 0x5A}))
//        return -1;
//    std::vector<uint8_t> ie;
//    if(0 != add_info.Pack(ie))
//        return -1;
//    if(3 != ie.size())
//        return -1;
//    if(2 != ie[0] || 0xA5 != ie[1] || 0x5A != ie[2])
//        return -1;
//    if(0 != add_info.Unpack(ie))
//        return -1;
//    if(2 != add_info.Value().size() || 0xA5 != add_info.Value()[0] ||
//       0x5A != add_info.Value()[1])
//        return -1;
    return 0;
}

int dev_prop_test(uint8 bo)
{
    LIBLTE_MME_DEVICE_PROPERTIES_ENUM device_props = LIBLTE_MME_DEVICE_PROPERTIES_CONFIGURED_FOR_LOW_PRIORITY;
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    msg.msg[0] = 0;
    if(LIBLTE_SUCCESS != liblte_mme_pack_device_properties_ie(device_props, bo, &ie_ptr))
        return -1;
    if(0 != (ie_ptr - msg.msg))
        return -1;
    if((1 << bo) != msg.msg[0])
        return -1;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_device_properties_ie(&ie_ptr, bo, &device_props))
        return -1;
    if(LIBLTE_MME_DEVICE_PROPERTIES_CONFIGURED_FOR_LOW_PRIORITY != device_props)
        return -1;
    return 0;
}

int device_properties_test(void)
{
    if(0 != dev_prop_test(0))
        return -1;
    if(0 != dev_prop_test(4))
        return -1;
    return 0;
}

int eps_bearer_context_status_test(void)
{
    LIBLTE_MME_EPS_BEARER_CONTEXT_STATUS_STRUCT ebcs;
    for(uint32 i=0; i<16; i++)
    {
        ebcs.ebi[i] = false;
        if(i%2)
            ebcs.ebi[i] = true;
    }
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_eps_bearer_context_status_ie(&ebcs, &ie_ptr))
        return -1;
    if(3 != (ie_ptr - msg.msg))
        return -1;
    if(2 != msg.msg[0] || 0xA0 != msg.msg[1] || 0xAA != msg.msg[2])
        return -1;
    ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_eps_bearer_context_status_ie(&ie_ptr, &ebcs))
        return -1;
    for(uint32 i=5; i<16; i++)
    {
        if(i%2)
        {
            if(ebcs.ebi[i] != true)
                return -1;
        }else{
            if(ebcs.ebi[i] != false)
                return -1;
        }
    }
    return 0;
}

int location_area_id_test(void)
{
    LIBLTE_MME_LOCATION_AREA_ID_STRUCT lai;
    std::vector<MCC_MNC_Digit> mcc(3);
    mcc[0].SetValue(3);
    mcc[1].SetValue(1);
    mcc[2].SetValue(0);
    lai.mcc.SetValue(mcc);
    std::vector<MCC_MNC_Digit> mnc(2);
    mnc[0].SetValue(1);
    mnc[1].SetValue(0);
    lai.mnc.SetValue(mnc);
    lai.lac = 0x1234;
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_location_area_id_ie(&lai, &ie_ptr))
        return -1;
    if(5 != (ie_ptr - msg.msg))
        return -1;
    if(0x13 != msg.msg[0] || 0xF0 != msg.msg[1] || 0x01 != msg.msg[2] || 0x12 != msg.msg[3] ||
       0x34 != msg.msg[4])
        return -1;
    ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_location_area_id_ie(&ie_ptr, &lai))
        return -1;
    if(3 != lai.mcc.Value()[0].Value() || 1 != lai.mcc.Value()[1].Value() ||
       0 != lai.mcc.Value()[2].Value() || 1 != lai.mnc.Value()[0].Value() ||
       0 != lai.mnc.Value()[1].Value() || 0x1234 != lai.lac)
        return -1;
    return 0;
}

int mobile_id_imsi_test(void)
{
    LIBLTE_MME_MOBILE_ID_STRUCT mobile_id;
    mobile_id.type_of_id = LIBLTE_MME_MOBILE_ID_TYPE_IMSI;
    for(uint32 i=0; i<15; i++)
        mobile_id.imsi[i] = (i+1)%10;
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_mobile_id_ie(&mobile_id, &ie_ptr))
        return -1;
    if(9 != (ie_ptr - msg.msg))
        return -1;
    if(0x08 != msg.msg[0] || 0x19 != msg.msg[1] || 0x32 != msg.msg[2] || 0x54 != msg.msg[3] ||
       0x76 != msg.msg[4] || 0x98 != msg.msg[5] || 0x10 != msg.msg[6] || 0x32 != msg.msg[7] ||
       0x54 != msg.msg[8])
        return -1;
    ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_mobile_id_ie(&ie_ptr, &mobile_id))
        return -1;
    if(LIBLTE_MME_MOBILE_ID_TYPE_IMSI != mobile_id.type_of_id)
        return -1;
    for(uint32 i=0; i<15; i++)
        if(mobile_id.imsi[i] != (i+1)%10)
            return -1;
    return 0;
}

int mobile_id_imei_test(void)
{
    LIBLTE_MME_MOBILE_ID_STRUCT mobile_id;
    mobile_id.type_of_id = LIBLTE_MME_MOBILE_ID_TYPE_IMEI;
    for(uint32 i=0; i<15; i++)
        mobile_id.imei[i] = (i+1)%10;
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_mobile_id_ie(&mobile_id, &ie_ptr))
        return -1;
    if(9 != (ie_ptr - msg.msg))
        return -1;
    if(0x08 != msg.msg[0] || 0x1A != msg.msg[1] || 0x32 != msg.msg[2] || 0x54 != msg.msg[3] ||
       0x76 != msg.msg[4] || 0x98 != msg.msg[5] || 0x10 != msg.msg[6] || 0x32 != msg.msg[7] ||
       0x54 != msg.msg[8])
        return -1;
    ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_mobile_id_ie(&ie_ptr, &mobile_id))
        return -1;
    if(LIBLTE_MME_MOBILE_ID_TYPE_IMEI != mobile_id.type_of_id)
        return -1;
    for(uint32 i=0; i<15; i++)
        if(mobile_id.imei[i] != (i+1)%10)
            return -1;
    return 0;
}

int mobile_id_imeisv_test(void)
{
    LIBLTE_MME_MOBILE_ID_STRUCT mobile_id;
    mobile_id.type_of_id = LIBLTE_MME_MOBILE_ID_TYPE_IMEISV;
    for(uint32 i=0; i<16; i++)
        mobile_id.imeisv[i] = (i+1)%10;
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_mobile_id_ie(&mobile_id, &ie_ptr))
        return -1;
    if(10 != (ie_ptr - msg.msg))
        return -1;
    if(0x09 != msg.msg[0] || 0x13 != msg.msg[1] || 0x32 != msg.msg[2] || 0x54 != msg.msg[3] ||
       0x76 != msg.msg[4] || 0x98 != msg.msg[5] || 0x10 != msg.msg[6] || 0x32 != msg.msg[7] ||
       0x54 != msg.msg[8] || 0xF6 != msg.msg[9])
        return -1;
    ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_mobile_id_ie(&ie_ptr, &mobile_id))
        return -1;
    if(LIBLTE_MME_MOBILE_ID_TYPE_IMEISV != mobile_id.type_of_id)
        return -1;
    for(uint32 i=0; i<16; i++)
        if(mobile_id.imeisv[i] != (i+1)%10)
            return -1;
    return 0;
}

int mobile_id_tmsi_test(void)
{
    LIBLTE_MME_MOBILE_ID_STRUCT mobile_id;
    mobile_id.type_of_id = LIBLTE_MME_MOBILE_ID_TYPE_TMSI;
    mobile_id.tmsi = 0x12345678;
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_mobile_id_ie(&mobile_id, &ie_ptr))
        return -1;
    if(6 != (ie_ptr - msg.msg))
        return -1;
    if(0x05 != msg.msg[0] || 0xF4 != msg.msg[1] || 0x12 != msg.msg[2] || 0x34 != msg.msg[3] ||
       0x56 != msg.msg[4] || 0x78 != msg.msg[5])
        return -1;
    ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_mobile_id_ie(&ie_ptr, &mobile_id))
        return -1;
    if(LIBLTE_MME_MOBILE_ID_TYPE_TMSI != mobile_id.type_of_id)
        return -1;
    if(mobile_id.tmsi != 0x12345678)
        return -1;
    return 0;
}

int mobile_id_tmgi_test(void)
{
    LIBLTE_MME_MOBILE_ID_STRUCT mobile_id;
    mobile_id.type_of_id = LIBLTE_MME_MOBILE_ID_TYPE_TMGI;
    mobile_id.tmgi.mbms_service_id = 0x123456;
    std::vector<MCC_MNC_Digit> mcc(3);
    mcc[0].SetValue(1);
    mcc[1].SetValue(2);
    mcc[2].SetValue(3);
    mobile_id.tmgi.mcc.SetValue(mcc);
    std::vector<MCC_MNC_Digit> mnc(2);
    mnc[0].SetValue(4);
    mnc[1].SetValue(5);
    mobile_id.tmgi.mnc.SetValue(mnc);
    mobile_id.tmgi.mbms_session_id = 0xFE;
    mobile_id.tmgi.mbms_session_id_ind = true;
    mobile_id.tmgi.mcc_mnc_ind = true;
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_mobile_id_ie(&mobile_id, &ie_ptr))
        return -1;
    if(9 != (ie_ptr - msg.msg))
        return -1;
    if(0x08 != msg.msg[0] || 0x35 != msg.msg[1] || 0x12 != msg.msg[2] || 0x34 != msg.msg[3] ||
       0x56 != msg.msg[4] || 0x21 != msg.msg[5] || 0xF3 != msg.msg[6] || 0x54 != msg.msg[7] ||
       0xFE != msg.msg[8])
        return -1;
    ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_mobile_id_ie(&ie_ptr, &mobile_id))
        return -1;
    if(LIBLTE_MME_MOBILE_ID_TYPE_TMGI != mobile_id.type_of_id)
        return -1;
    if(mobile_id.tmgi.mbms_service_id != 0x123456 || mobile_id.tmgi.mcc.Value()[0].Value() != 1 ||
       mobile_id.tmgi.mcc.Value()[1].Value() != 2 || mobile_id.tmgi.mcc.Value()[2].Value() != 3 ||
       mobile_id.tmgi.mnc.Value()[0].Value() != 4 || mobile_id.tmgi.mnc.Value()[1].Value() != 5 ||
       mobile_id.tmgi.mbms_session_id != 0xFE || mobile_id.tmgi.mbms_session_id_ind != true ||
       mobile_id.tmgi.mcc_mnc_ind != true)
        return -1;
    return 0;
}

int mobile_id_test(void)
{
    if(0 != mobile_id_imsi_test())
        return -1;
    if(0 != mobile_id_imei_test())
        return -1;
    if(0 != mobile_id_imeisv_test())
        return -1;
    if(0 != mobile_id_tmsi_test())
        return -1;
    if(0 != mobile_id_tmgi_test())
        return -1;
    return 0;
}

int mobile_station_classmark_2_test(void)
{
    LIBLTE_MME_MOBILE_STATION_CLASSMARK_2_STRUCT ms_cm2;
    ms_cm2.rev_lev = LIBLTE_MME_REVISION_LEVEL_R99;
    ms_cm2.rf_power_cap = LIBLTE_MME_RF_POWER_CAPABILITY_CLASS_3;
    ms_cm2.ss_screen_ind = LIBLTE_MME_SS_SCREEN_INDICATOR_2;
    ms_cm2.es_ind = false;
    ms_cm2.a5_1 = true;
    ms_cm2.ps_cap = false;
    ms_cm2.sm_cap = true;
    ms_cm2.vbs = false;
    ms_cm2.vgcs = true;
    ms_cm2.fc = false;
    ms_cm2.cm3 = true;
    ms_cm2.lcsva_cap = false;
    ms_cm2.ucs2 = true;
    ms_cm2.solsa = false;
    ms_cm2.cmsp = true;
    ms_cm2.a5_3 = false;
    ms_cm2.a5_2 = true;
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_mobile_station_classmark_2_ie(&ms_cm2, &ie_ptr))
        return -1;
    if(4 != (ie_ptr - msg.msg))
        return -1;
    if(0x03 != msg.msg[0] || 0x4A != msg.msg[1] || 0x2A != msg.msg[2] || 0x95 != msg.msg[3])
        return -1;
    ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_mobile_station_classmark_2_ie(&ie_ptr, &ms_cm2))
        return -1;
    if(ms_cm2.rev_lev != LIBLTE_MME_REVISION_LEVEL_R99 ||
       ms_cm2.rf_power_cap != LIBLTE_MME_RF_POWER_CAPABILITY_CLASS_3 ||
       ms_cm2.ss_screen_ind != LIBLTE_MME_SS_SCREEN_INDICATOR_2 ||
       ms_cm2.es_ind || !ms_cm2.a5_1 || ms_cm2.ps_cap || !ms_cm2.sm_cap || ms_cm2.vbs ||
       !ms_cm2.vgcs || ms_cm2.fc || !ms_cm2.cm3 || ms_cm2.lcsva_cap || !ms_cm2.ucs2 ||
       ms_cm2.solsa || !ms_cm2.cmsp || ms_cm2.a5_3 || !ms_cm2.a5_2)
        return -1;
    return 0;
}

int mobile_station_classmark_3_test(void)
{
    LIBLTE_MME_MOBILE_STATION_CLASSMARK_3_STRUCT ms_cm3;
    ms_cm3.multi_band_support.assoc_radio_cap_2 = 0xA;
    ms_cm3.multi_band_support.assoc_radio_cap_1 = 0x5;
    ms_cm3.multi_band_support.pgsm_support = true;
    ms_cm3.multi_band_support.e_rgsm_support = false;
    ms_cm3.multi_band_support.gsm_1800_support = true;
    ms_cm3.multi_band_support.a5_7 = false;
    ms_cm3.multi_band_support.a5_6 = true;
    ms_cm3.multi_band_support.a5_5 = false;
    ms_cm3.multi_band_support.a5_4 = true;
    ms_cm3.ms_meas_cap.sms_value = 0x3;
    ms_cm3.ms_meas_cap.sm_value = 0xC;
    ms_cm3.gsm400_support.assoc_radio_cap = 0xE;
    ms_cm3.gsm400_support.gsm450_support = true;
    ms_cm3.gsm400_support.gsm480_support = false;
    ms_cm3.dtm.dtm_gprs_multi_slot_class = 0x1;
    ms_cm3.dtm.dtm_egprs_multi_slot_class = 0x2;
    ms_cm3.dtm.single_slot_dtm = false;
    ms_cm3.dtm.dtm_egprs_multi_slot_class_present = true;
    ms_cm3.r_support = 0x5;
    ms_cm3.ecsd_multi_slot_cap = 0x15;
    ms_cm3.gsm1900_assoc_radio_cap = 0x6;
    ms_cm3.gsm750_assoc_radio_cap = 0xA;
    ms_cm3.high_multi_slot_cap = 0x1;
    ms_cm3.gmsk_multi_slot_power_profile = 0x2;
    ms_cm3.eight_psk_multi_slot_power_profile = 0x3;
    ms_cm3.darp = 0x1;
    ms_cm3.tgsm810_assoc_radio_cap = 0x9;
    ms_cm3.vamos_level = 0x1;
    ms_cm3.r_support_present = true;
    ms_cm3.hscsd_multi_slot_cap_present = false;
    ms_cm3.ucs2_treatment = true;
    ms_cm3.ext_meas_cap = false;
    ms_cm3.ms_meas_cap_present = true;
    ms_cm3.ms_pos_method_cap_present = false;
    ms_cm3.ecsd_multi_slot_cap_present = true;
    ms_cm3.eight_psk_present = false;
    ms_cm3.gsm400_support_present = true;
    ms_cm3.gsm850_assoc_radio_cap_present = false;
    ms_cm3.gsm1900_assoc_radio_cap_present = true;
    ms_cm3.umts_fdd_rat_cap = false;
    ms_cm3.umts_3_84_mcps_tdd_rat_cap = true;
    ms_cm3.cdma2000_rat_cap = false;
    ms_cm3.dtm_present = true;
    ms_cm3.single_band_support_present = false;
    ms_cm3.gsm750_assoc_radio_cap_present = true;
    ms_cm3.umts_1_28_mcps_tdd_rat_cap = false;
    ms_cm3.geran_feature_package = true;
    ms_cm3.ext_dtm_present = false;
    ms_cm3.high_multi_slot_cap_present = true;
    ms_cm3.geran_iu_mode_cap_present = false;
    ms_cm3.geran_feature_package_2 = true;
    ms_cm3.tgsm400_support_present = false;
    ms_cm3.dtm_enhancements_cap = true;
    ms_cm3.dtm_high_multi_slot_present = false;
    ms_cm3.repeated_acch_cap = true;
    ms_cm3.gsm710_assoc_radio_cap_present = false;
    ms_cm3.tgsm810_assoc_radio_cap_present = true;
    ms_cm3.ciphering_mode_setting_cap = false;
    ms_cm3.additional_pos_cap = true;
    ms_cm3.eutra_fdd_support = false;
    ms_cm3.eutra_tdd_support = true;
    ms_cm3.eutra_meas_and_reporting_support = false;
    ms_cm3.prio_based_reselection_support = true;
    ms_cm3.utra_csg_cells_reporting = false;
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_mobile_station_classmark_3_ie(&ms_cm3, &ie_ptr))
        return -1;
    if(13 != (ie_ptr - msg.msg))
        return -1;
    if(0xAB != msg.msg[0] || 0x4B != msg.msg[1] || 0xAA != msg.msg[2] || 0x78 != msg.msg[3] ||
       0xD5 != msg.msg[4] || 0xB9 != msg.msg[5] || 0x65 != msg.msg[6] || 0x59 != msg.msg[7] ||
       0xA5 != msg.msg[8] || 0x5B != msg.msg[9] || 0x1A != msg.msg[10] ||
       0xCA != msg.msg[11] || 0xA4 != msg.msg[12])
        return -1;
    ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_mobile_station_classmark_3_ie(&ie_ptr, &ms_cm3))
        return -1;
    if(ms_cm3.multi_band_support.assoc_radio_cap_2 != 0xA ||
       ms_cm3.multi_band_support.assoc_radio_cap_1 != 0x5 ||
       !ms_cm3.multi_band_support.pgsm_support || ms_cm3.multi_band_support.e_rgsm_support ||
       !ms_cm3.multi_band_support.gsm_1800_support || ms_cm3.multi_band_support.a5_7 ||
       !ms_cm3.multi_band_support.a5_6 || ms_cm3.multi_band_support.a5_5 ||
       !ms_cm3.multi_band_support.a5_4 || ms_cm3.ms_meas_cap.sms_value != 0x3 ||
       ms_cm3.ms_meas_cap.sm_value != 0xC || ms_cm3.gsm400_support.assoc_radio_cap != 0xE ||
       !ms_cm3.gsm400_support.gsm450_support || ms_cm3.gsm400_support.gsm480_support ||
       ms_cm3.dtm.dtm_gprs_multi_slot_class != 0x1 ||
       ms_cm3.dtm.dtm_egprs_multi_slot_class != 0x2 || ms_cm3.dtm.single_slot_dtm ||
       !ms_cm3.dtm.dtm_egprs_multi_slot_class_present || ms_cm3.r_support != 0x5 ||
       ms_cm3.ecsd_multi_slot_cap != 0x15 || ms_cm3.gsm1900_assoc_radio_cap != 0x6 ||
       ms_cm3.gsm750_assoc_radio_cap != 0xA || ms_cm3.high_multi_slot_cap != 0x1 ||
       ms_cm3.gmsk_multi_slot_power_profile != 0x2 ||
       ms_cm3.eight_psk_multi_slot_power_profile != 0x3 || ms_cm3.darp != 0x1 ||
       ms_cm3.tgsm810_assoc_radio_cap != 0x9 || ms_cm3.vamos_level != 0x1 ||
       !ms_cm3.r_support_present || ms_cm3.hscsd_multi_slot_cap_present ||
       !ms_cm3.ucs2_treatment || ms_cm3.ext_meas_cap || !ms_cm3.ms_meas_cap_present ||
       ms_cm3.ms_pos_method_cap_present || !ms_cm3.ecsd_multi_slot_cap_present ||
       ms_cm3.eight_psk_present || !ms_cm3.gsm400_support_present ||
       ms_cm3.gsm850_assoc_radio_cap_present || !ms_cm3.gsm1900_assoc_radio_cap_present ||
       ms_cm3.umts_fdd_rat_cap || !ms_cm3.umts_3_84_mcps_tdd_rat_cap ||
       ms_cm3.cdma2000_rat_cap || !ms_cm3.dtm_present || ms_cm3.single_band_support_present ||
       !ms_cm3.gsm750_assoc_radio_cap_present || ms_cm3.umts_1_28_mcps_tdd_rat_cap ||
       !ms_cm3.geran_feature_package || ms_cm3.ext_dtm_present ||
       !ms_cm3.high_multi_slot_cap_present || ms_cm3.geran_iu_mode_cap_present ||
       !ms_cm3.geran_feature_package_2 || ms_cm3.tgsm400_support_present ||
       !ms_cm3.dtm_enhancements_cap || ms_cm3.dtm_high_multi_slot_present ||
       !ms_cm3.repeated_acch_cap || ms_cm3.gsm710_assoc_radio_cap_present ||
       !ms_cm3.tgsm810_assoc_radio_cap_present || ms_cm3.ciphering_mode_setting_cap ||
       !ms_cm3.additional_pos_cap || ms_cm3.eutra_fdd_support || !ms_cm3.eutra_tdd_support ||
       ms_cm3.eutra_meas_and_reporting_support || !ms_cm3.prio_based_reselection_support ||
       ms_cm3.utra_csg_cells_reporting)
        return -1;
    return 0;
}

int nas_security_parameters_from_eutra_test(void)
{
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_nas_security_parameters_from_eutra_ie(0xA, &ie_ptr))
        return -1;
    if(1 != (ie_ptr - msg.msg))
        return -1;
    if(0x0A != msg.msg[0])
        return -1;
    ie_ptr = msg.msg;
    uint8 cnt;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_nas_security_parameters_from_eutra_ie(&ie_ptr,
                                                                                 &cnt))
        return -1;
    if(cnt != 0xA)
        return -1;
    return 0;
}

int nas_security_parameters_to_eutra_test(void)
{
    LIBLTE_MME_NAS_SECURITY_PARAMETERS_TO_EUTRA_STRUCT sec_params;
    sec_params.eea = LIBLTE_MME_TYPE_OF_CIPHERING_ALGORITHM_EEA3;
    sec_params.eia = LIBLTE_MME_TYPE_OF_INTEGRITY_ALGORITHM_EIA7;
    sec_params.tsc_flag = LIBLTE_MME_TYPE_OF_SECURITY_CONTEXT_FLAG_MAPPED;
    sec_params.nonce_mme = 0x87654321;
    sec_params.nas_ksi = 0x5;
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_nas_security_parameters_to_eutra_ie(&sec_params,
                                                                             &ie_ptr))
        return -1;
    if(6 != (ie_ptr - msg.msg))
        return -1;
    if(0x87 != msg.msg[0] || 0x65 != msg.msg[1] || 0x43 != msg.msg[2] || 0x21 != msg.msg[3] ||
       0x37 != msg.msg[4] || 0x0D != msg.msg[5])
        return -1;
    ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_nas_security_parameters_to_eutra_ie(&ie_ptr,
                                                                               &sec_params))
        return -1;
    if(sec_params.eea != LIBLTE_MME_TYPE_OF_CIPHERING_ALGORITHM_EEA3 ||
       sec_params.eia != LIBLTE_MME_TYPE_OF_INTEGRITY_ALGORITHM_EIA7 ||
       sec_params.tsc_flag != LIBLTE_MME_TYPE_OF_SECURITY_CONTEXT_FLAG_MAPPED ||
       sec_params.nonce_mme != 0x87654321 || sec_params.nas_ksi != 0x5)
        return -1;
    return 0;
}

int plmn_list_test(void)
{
    LIBLTE_MME_PLMN_LIST_STRUCT plmn_list;
    plmn_list.N_plmns = 4;
    std::vector<MCC_MNC_Digit> mcc(3);
    mcc[0].SetValue(1);
    mcc[1].SetValue(2);
    mcc[2].SetValue(3);
    plmn_list.mcc[0].SetValue(mcc);
    mcc[0].SetValue(2);
    mcc[1].SetValue(3);
    mcc[2].SetValue(4);
    plmn_list.mcc[1].SetValue(mcc);
    mcc[0].SetValue(3);
    mcc[1].SetValue(4);
    mcc[2].SetValue(5);
    plmn_list.mcc[2].SetValue(mcc);
    mcc[0].SetValue(4);
    mcc[1].SetValue(5);
    mcc[2].SetValue(6);
    plmn_list.mcc[3].SetValue(mcc);
    std::vector<MCC_MNC_Digit> mnc2(2);
    mnc2[0].SetValue(8);
    mnc2[1].SetValue(9);
    plmn_list.mnc[0].SetValue(mnc2);
    mnc2[0].SetValue(7);
    mnc2[1].SetValue(8);
    plmn_list.mnc[1].SetValue(mnc2);
    std::vector<MCC_MNC_Digit> mnc3(3);
    mnc3[0].SetValue(6);
    mnc3[1].SetValue(7);
    mnc3[2].SetValue(8);
    plmn_list.mnc[2].SetValue(mnc3);
    mnc3[0].SetValue(5);
    mnc3[1].SetValue(6);
    mnc3[2].SetValue(7);
    plmn_list.mnc[3].SetValue(mnc3);
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_plmn_list_ie(&plmn_list, &ie_ptr))
        return -1;
    if(13 != (ie_ptr - msg.msg))
        return -1;
    if(0x0C != msg.msg[0] || 0x21 != msg.msg[1] || 0xF3 != msg.msg[2] || 0x98 != msg.msg[3] ||
       0x32 != msg.msg[4] || 0xF4 != msg.msg[5] || 0x87 != msg.msg[6] || 0x43 != msg.msg[7] ||
       0x85 != msg.msg[8] || 0x76 != msg.msg[9] || 0x54 != msg.msg[10] ||
       0x76 != msg.msg[11] || 0x65 != msg.msg[12])
        return -1;
    ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_plmn_list_ie(&ie_ptr, &plmn_list))
        return -1;
    if(plmn_list.N_plmns != 4 || plmn_list.mcc[0].Value()[0].Value() != 1 ||
       plmn_list.mcc[0].Value()[1].Value() != 2 || plmn_list.mcc[0].Value()[2].Value() != 3 ||
       plmn_list.mcc[1].Value()[0].Value() != 2 || plmn_list.mcc[1].Value()[1].Value() != 3 ||
       plmn_list.mcc[1].Value()[2].Value() != 4 || plmn_list.mcc[2].Value()[0].Value() != 3 ||
       plmn_list.mcc[2].Value()[1].Value() != 4 || plmn_list.mcc[2].Value()[2].Value() != 5 ||
       plmn_list.mcc[3].Value()[0].Value() != 4 || plmn_list.mcc[3].Value()[1].Value() != 5 ||
       plmn_list.mcc[3].Value()[2].Value() != 6 || plmn_list.mnc[0].Value()[0].Value() != 8 ||
       plmn_list.mnc[0].Value()[1].Value() != 9 || plmn_list.mnc[1].Value()[0].Value() != 7 ||
       plmn_list.mnc[1].Value()[1].Value() != 8 || plmn_list.mnc[2].Value()[0].Value() != 6 ||
       plmn_list.mnc[2].Value()[1].Value() != 7 || plmn_list.mnc[2].Value()[2].Value() != 8 ||
       plmn_list.mnc[3].Value()[0].Value() != 5 || plmn_list.mnc[3].Value()[1].Value() != 6 ||
       plmn_list.mnc[3].Value()[2].Value() != 7)
        return -1;
    return 0;
}

int supported_codec_list_test(void)
{
    LIBLTE_MME_SUPPORTED_CODEC_LIST_STRUCT supported_codec_list;
    supported_codec_list.N_supported_codecs = 2;
    supported_codec_list.supported_codec[0].sys_id = 0xA5;
    supported_codec_list.supported_codec[0].codec_bitmap = 0x1234;
    supported_codec_list.supported_codec[1].sys_id = 0x5A;
    supported_codec_list.supported_codec[1].codec_bitmap = 0x5678;
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_supported_codec_list_ie(&supported_codec_list,
                                                                 &ie_ptr))
        return -1;
    if(9 != (ie_ptr - msg.msg))
        return -1;
    if(0x08 != msg.msg[0] || 0xA5 != msg.msg[1] || 0x02 != msg.msg[2] || 0x12 != msg.msg[3] ||
       0x34 != msg.msg[4] || 0x5A != msg.msg[5] || 0x02 != msg.msg[6] || 0x56 != msg.msg[7] ||
       0x78 != msg.msg[8])
        return -1;
    ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_supported_codec_list_ie(&ie_ptr,
                                                                   &supported_codec_list))
        return -1;
    if(supported_codec_list.N_supported_codecs != 2 ||
       supported_codec_list.supported_codec[0].sys_id != 0xA5 ||
       supported_codec_list.supported_codec[0].codec_bitmap != 0x1234 ||
       supported_codec_list.supported_codec[1].sys_id != 0x5A ||
       supported_codec_list.supported_codec[1].codec_bitmap != 0x5678)
        return -1;
    return 0;
}

int aur_test(uint8 bo)
{
    LIBLTE_MME_ADDITIONAL_UPDATE_RESULT_ENUM result =
        LIBLTE_MME_ADDITIONAL_UPDATE_RESULT_SMS_ONLY;
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    msg.msg[0] = 0;
    if(LIBLTE_SUCCESS != liblte_mme_pack_additional_update_result_ie(result, bo, &ie_ptr))
        return -1;
    if(0 != (ie_ptr - msg.msg))
        return -1;
    if((0x2 << bo) != msg.msg[0])
        return -1;
    ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_additional_update_result_ie(&ie_ptr, bo, &result))
        return -1;
    if(result != LIBLTE_MME_ADDITIONAL_UPDATE_RESULT_SMS_ONLY)
        return -1;
    return 0;
}

int additional_update_result_test(void)
{
    if(0 != aur_test(0))
        return -1;
    if(0 != aur_test(4))
        return -1;
    return 0;
}

int aut_test(uint8 bo)
{
    LIBLTE_MME_ADDITIONAL_UPDATE_TYPE_ENUM aut = LIBLTE_MME_ADDITIONAL_UPDATE_TYPE_SMS_ONLY;
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    msg.msg[0] = 0;
    if(LIBLTE_SUCCESS != liblte_mme_pack_additional_update_type_ie(aut, bo, &ie_ptr))
        return -1;
    if(0 != (ie_ptr - msg.msg))
        return -1;
    if((0x1 << bo) != msg.msg[0])
        return -1;
    ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_additional_update_type_ie(&ie_ptr, bo, &aut))
        return -1;
    if(aut != LIBLTE_MME_ADDITIONAL_UPDATE_TYPE_SMS_ONLY)
        return -1;
    return 0;
}

int additional_update_type_test(void)
{
    if(0 != aut_test(0))
        return -1;
    if(0 != aut_test(4))
        return -1;
    return 0;
}

int authentication_failure_parameter_test(void)
{
    uint8 auth_fail_param[14] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14};
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_authentication_failure_parameter_ie(auth_fail_param,
                                                                             &ie_ptr))
        return -1;
    if(15 != (ie_ptr - msg.msg))
        return -1;
    if(0x0E != msg.msg[0] || 0x01 != msg.msg[1] || 0x02 != msg.msg[2] || 0x03 != msg.msg[3] ||
       0x04 != msg.msg[4] || 0x05 != msg.msg[5] || 0x06 != msg.msg[6] || 0x07 != msg.msg[7] ||
       0x08 != msg.msg[8] || 0x09 != msg.msg[9] || 0x0A != msg.msg[10] ||
       0x0B != msg.msg[11] || 0x0C != msg.msg[12] || 0x0D != msg.msg[13] ||
       0x0E != msg.msg[14])
        return -1;
    ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_authentication_failure_parameter_ie(&ie_ptr,
                                                                               auth_fail_param))
        return -1;
    for(uint32 i=0; i<14; i++)
        if(auth_fail_param[i] != i+1)
            return -1;
    return 0;
}

int authentication_parameter_autn_test(void)
{
    uint8 autn[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_authentication_parameter_autn_ie(autn, &ie_ptr))
        return -1;
    if(17 != (ie_ptr - msg.msg))
        return -1;
    if(0x10 != msg.msg[0] || 0x01 != msg.msg[1] || 0x02 != msg.msg[2] || 0x03 != msg.msg[3] ||
       0x04 != msg.msg[4] || 0x05 != msg.msg[5] || 0x06 != msg.msg[6] || 0x07 != msg.msg[7] ||
       0x08 != msg.msg[8] || 0x09 != msg.msg[9] || 0x0A != msg.msg[10] ||
       0x0B != msg.msg[11] || 0x0C != msg.msg[12] || 0x0D != msg.msg[13] ||
       0x0E != msg.msg[14] || 0x0F != msg.msg[15] || 0x10 != msg.msg[16])
        return -1;
    ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_authentication_parameter_autn_ie(&ie_ptr, autn))
        return -1;
    for(uint32 i=0; i<16; i++)
        if(autn[i] != i+1)
            return -1;
    return 0;
}

int authentication_parameter_rand_test(void)
{
    uint8 rand_val[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_authentication_parameter_rand_ie(rand_val, &ie_ptr))
        return -1;
    if(16 != (ie_ptr - msg.msg))
        return -1;
    if(0x01 != msg.msg[0] || 0x02 != msg.msg[1] || 0x03 != msg.msg[2] || 0x04 != msg.msg[3] ||
       0x05 != msg.msg[4] || 0x06 != msg.msg[5] || 0x07 != msg.msg[6] || 0x08 != msg.msg[7] ||
       0x09 != msg.msg[8] || 0x0A != msg.msg[9] || 0x0B != msg.msg[10] ||
       0x0C != msg.msg[11] || 0x0D != msg.msg[12] || 0x0E != msg.msg[13] ||
       0x0F != msg.msg[14] || 0x10 != msg.msg[15])
        return -1;
    ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_authentication_parameter_rand_ie(&ie_ptr,
                                                                            rand_val))
        return -1;
    for(uint32 i=0; i<16; i++)
        if(rand_val[i] != i+1)
            return -1;
    return 0;
}

int authentication_response_parameter_test(void)
{
    uint8 res[8] = {1,2,3,4,5,6,7,8};
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_authentication_response_parameter_ie(res, &ie_ptr))
        return -1;
    if(9 != (ie_ptr - msg.msg))
        return -1;
    if(0x08 != msg.msg[0] || 0x01 != msg.msg[1] || 0x02 != msg.msg[2] || 0x03 != msg.msg[3] ||
       0x04 != msg.msg[4] || 0x05 != msg.msg[5] || 0x06 != msg.msg[6] || 0x07 != msg.msg[7] ||
       0x08 != msg.msg[8])
        return -1;
    ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_authentication_response_parameter_ie(&ie_ptr, res))
        return -1;
    for(uint32 i=0; i<8; i++)
        if(res[i] != i+1)
            return -1;
    return 0;
}

int cksn_test(uint8 bo)
{
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    msg.msg[0] = 0;
    if(LIBLTE_SUCCESS != liblte_mme_pack_ciphering_key_sequence_number_ie(0x5, bo, &ie_ptr))
        return -1;
    if(0 != (ie_ptr - msg.msg))
        return -1;
    if((0x5 << bo) != msg.msg[0])
        return -1;
    ie_ptr = msg.msg;
    uint8 ks;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_ciphering_key_sequence_number_ie(&ie_ptr, bo, &ks))
        return -1;
    if(ks != 0x5)
        return -1;
    return 0;
}

int ciphering_key_sequence_number_test(void)
{
    if(0 != cksn_test(0))
        return -1;
    if(0 != cksn_test(4))
        return -1;
    return 0;
}

int csfb_resp_test(uint8 bo)
{
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    msg.msg[0] = 0;
    if(LIBLTE_SUCCESS != liblte_mme_pack_csfb_response_ie(0x5, bo, &ie_ptr))
        return -1;
    if(0 != (ie_ptr - msg.msg))
        return -1;
    if((0x5 << bo) != msg.msg[0])
        return -1;
    ie_ptr = msg.msg;
    uint8 csfb_resp;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_csfb_response_ie(&ie_ptr, bo, &csfb_resp))
        return -1;
    if(csfb_resp != 0x5)
        return -1;
    return 0;
}

int csfb_response_test(void)
{
    if(0 != csfb_resp_test(0))
        return -1;
    if(0 != csfb_resp_test(4))
        return -1;
    return 0;
}

int daylight_saving_time_test(void)
{
    LIBLTE_MME_DAYLIGHT_SAVING_TIME_ENUM dst = LIBLTE_MME_DAYLIGHT_SAVING_TIME_PLUS_ONE_HOUR;
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_daylight_saving_time_ie(dst, &ie_ptr))
        return -1;
    if(2 != (ie_ptr - msg.msg))
        return -1;
    if(0x01 != msg.msg[0] || 0x01 != msg.msg[1])
        return -1;
    ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_daylight_saving_time_ie(&ie_ptr, &dst))
        return -1;
    if(dst != LIBLTE_MME_DAYLIGHT_SAVING_TIME_PLUS_ONE_HOUR)
        return -1;
    return 0;
}

int dt_test(uint8 bo)
{
    LIBLTE_MME_DETACH_TYPE_STRUCT detach_type;
    detach_type.switch_off = LIBLTE_MME_SO_FLAG_SWITCH_OFF;
    detach_type.type_of_detach = LIBLTE_MME_TOD_UL_IMSI_DETACH;
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    msg.msg[0] = 0;
    if(LIBLTE_SUCCESS != liblte_mme_pack_detach_type_ie(&detach_type, bo, &ie_ptr))
        return -1;
    if(0 != (ie_ptr - msg.msg))
        return -1;
    if((0xA << bo) != msg.msg[0])
        return -1;
    ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_detach_type_ie(&ie_ptr, bo, &detach_type))
        return -1;
    if(detach_type.switch_off != LIBLTE_MME_SO_FLAG_SWITCH_OFF ||
       detach_type.type_of_detach != LIBLTE_MME_TOD_UL_IMSI_DETACH)
        return -1;
    return 0;
}

int detach_type_test(void)
{
    if(0 != dt_test(0))
        return -1;
    if(0 != dt_test(4))
        return -1;
    return 0;
}

int drx_parameter_test(void)
{
    LIBLTE_MME_DRX_PARAMETER_STRUCT drx_param;
    drx_param.non_drx_timer = LIBLTE_MME_NON_DRX_TIMER_MAX_8S_NON_DRX_MODE;
    drx_param.split_pg_cycle_code = 0xA5;
    drx_param.drx_cycle_len_coeff_and_value = 0x6;
    drx_param.split_on_ccch = false;
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_drx_parameter_ie(&drx_param, &ie_ptr))
        return -1;
    if(2 != (ie_ptr - msg.msg))
        return -1;
    if(0xA5 != msg.msg[0] || 0x64 != msg.msg[1])
        return -1;
    ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_drx_parameter_ie(&ie_ptr, &drx_param))
        return -1;
    if(drx_param.non_drx_timer != LIBLTE_MME_NON_DRX_TIMER_MAX_8S_NON_DRX_MODE ||
       drx_param.split_pg_cycle_code != 0xA5 ||
       drx_param.drx_cycle_len_coeff_and_value != 0x6 || drx_param.split_on_ccch)
        return -1;
    return 0;
}

int emm_cause_test(void)
{
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_emm_cause_ie(0xA5, &ie_ptr))
        return -1;
    if(1 != (ie_ptr - msg.msg))
        return -1;
    if(0xA5 != msg.msg[0])
        return -1;
    ie_ptr = msg.msg;
    uint8 emm_cause;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_emm_cause_ie(&ie_ptr, &emm_cause))
        return -1;
    if(emm_cause != 0xA5)
        return -1;
    return 0;
}

int ear_test(uint8 bo)
{
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    msg.msg[0] = 0;
    if(LIBLTE_SUCCESS != liblte_mme_pack_eps_attach_result_ie(0x6, bo, &ie_ptr))
        return -1;
    if(0 != (ie_ptr - msg.msg))
        return -1;
    if((0x6 << bo) != msg.msg[0])
        return -1;
    ie_ptr = msg.msg;
    uint8 result;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_eps_attach_result_ie(&ie_ptr, bo, &result))
        return -1;
    if(result != 0x6)
        return -1;
    return 0;
}

int eps_attach_result_test(void)
{
    if(0 != ear_test(0))
        return -1;
    if(0 != ear_test(4))
        return -1;
    return 0;
}

int eat_test(uint8 bo)
{
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    msg.msg[0] = 0;
    if(LIBLTE_SUCCESS != liblte_mme_pack_eps_attach_type_ie(0x6, bo, &ie_ptr))
        return -1;
    if(0 != (ie_ptr - msg.msg))
        return -1;
    if((0x6 << bo) != msg.msg[0])
        return -1;
    ie_ptr = msg.msg;
    uint8 type;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_eps_attach_type_ie(&ie_ptr, bo, &type))
        return -1;
    if(type != 0x6)
        return -1;
    return 0;
}

int eps_attach_type_test(void)
{
    if(0 != eat_test(0))
        return -1;
    if(0 != eat_test(4))
        return -1;
    return 0;
}

int eps_mobile_id_guti_test(void)
{
    LIBLTE_MME_EPS_MOBILE_ID_STRUCT eps_mobile_id;
    eps_mobile_id.type_of_id = LIBLTE_MME_EPS_MOBILE_ID_TYPE_GUTI;
    eps_mobile_id.guti.m_tmsi = 0x12345678;
    std::vector<MCC_MNC_Digit> mcc(3);
    mcc[0].SetValue(1);
    mcc[1].SetValue(2);
    mcc[2].SetValue(3);
    eps_mobile_id.guti.mcc.SetValue(mcc);
    std::vector<MCC_MNC_Digit> mnc(3);
    mnc[0].SetValue(4);
    mnc[1].SetValue(5);
    mnc[2].SetValue(6);
    eps_mobile_id.guti.mnc.SetValue(mnc);
    eps_mobile_id.guti.mme_group_id = 0xABCD;
    eps_mobile_id.guti.mme_code = 0xEF;
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_eps_mobile_id_ie(&eps_mobile_id, &ie_ptr))
        return -1;
    if(12 != (ie_ptr - msg.msg))
        return -1;
    if(0x0B != msg.msg[0] || 0xF6 != msg.msg[1] || 0x21 != msg.msg[2] || 0x63 != msg.msg[3] ||
       0x54 != msg.msg[4] || 0xAB != msg.msg[5] || 0xCD != msg.msg[6] || 0xEF != msg.msg[7] ||
       0x12 != msg.msg[8] || 0x34 != msg.msg[9] || 0x56 != msg.msg[10] || 0x78 != msg.msg[11])
        return -1;
    ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_eps_mobile_id_ie(&ie_ptr, &eps_mobile_id))
        return -1;
    if(eps_mobile_id.type_of_id != LIBLTE_MME_EPS_MOBILE_ID_TYPE_GUTI ||
       eps_mobile_id.guti.m_tmsi != 0x12345678 ||
       eps_mobile_id.guti.mcc.Value()[0].Value() != 1 ||
       eps_mobile_id.guti.mcc.Value()[1].Value() != 2 ||
       eps_mobile_id.guti.mcc.Value()[2].Value() != 3 ||
       eps_mobile_id.guti.mnc.Value()[0].Value() != 4 ||
       eps_mobile_id.guti.mnc.Value()[1].Value() != 5 ||
       eps_mobile_id.guti.mnc.Value()[2].Value() != 6 ||
       eps_mobile_id.guti.mme_group_id != 0xABCD || eps_mobile_id.guti.mme_code != 0xEF)
        return -1;
    return 0;
}

int eps_mobile_id_imei_test(void)
{
    LIBLTE_MME_EPS_MOBILE_ID_STRUCT eps_mobile_id;
    eps_mobile_id.type_of_id = LIBLTE_MME_EPS_MOBILE_ID_TYPE_IMEI;
    for(uint32 i=0; i<15; i++)
        eps_mobile_id.imei[i] = i%10;
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_eps_mobile_id_ie(&eps_mobile_id, &ie_ptr))
        return -1;
    if(9 != (ie_ptr - msg.msg))
        return -1;
    if(0x08 != msg.msg[0] || 0x0B != msg.msg[1] || 0x21 != msg.msg[2] || 0x43 != msg.msg[3] ||
       0x65 != msg.msg[4] || 0x87 != msg.msg[5] || 0x09 != msg.msg[6] || 0x21 != msg.msg[7] ||
       0x43 != msg.msg[8])
        return -1;
    ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_eps_mobile_id_ie(&ie_ptr, &eps_mobile_id))
        return -1;
    for(uint32 i=0; i<15; i++)
        if(eps_mobile_id.imei[i] != i%10)
            return -1;
    return 0;
}

int eps_mobile_id_imsi_test(void)
{
    LIBLTE_MME_EPS_MOBILE_ID_STRUCT eps_mobile_id;
    eps_mobile_id.type_of_id = LIBLTE_MME_EPS_MOBILE_ID_TYPE_IMSI;
    for(uint32 i=0; i<15; i++)
        eps_mobile_id.imsi[i] = i%10;
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_eps_mobile_id_ie(&eps_mobile_id, &ie_ptr))
        return -1;
    if(9 != (ie_ptr - msg.msg))
        return -1;
    if(0x08 != msg.msg[0] || 0x09 != msg.msg[1] || 0x21 != msg.msg[2] || 0x43 != msg.msg[3] ||
       0x65 != msg.msg[4] || 0x87 != msg.msg[5] || 0x09 != msg.msg[6] || 0x21 != msg.msg[7] ||
       0x43 != msg.msg[8])
        return -1;
    ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_eps_mobile_id_ie(&ie_ptr, &eps_mobile_id))
        return -1;
    for(uint32 i=0; i<15; i++)
        if(eps_mobile_id.imsi[i] != i%10)
            return -1;
    return 0;
}

int eps_mobile_id_test(void)
{
    if(0 != eps_mobile_id_guti_test())
        return -1;
    if(0 != eps_mobile_id_imei_test())
        return -1;
    if(0 != eps_mobile_id_imsi_test())
        return -1;
    return 0;
}

int eps_network_feature_support_test(void)
{
    LIBLTE_MME_EPS_NETWORK_FEATURE_SUPPORT_STRUCT eps_nfs;
    eps_nfs.cs_lcs = LIBLTE_MME_CS_LCS_NOT_SUPPORTED;
    eps_nfs.esrps = false;
    eps_nfs.epc_lcs = true;
    eps_nfs.emc_bs = false;
    eps_nfs.ims_vops = true;
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_eps_network_feature_support_ie(&eps_nfs, &ie_ptr))
        return -1;
    if(2 != (ie_ptr - msg.msg))
        return -1;
    if(0x01 != msg.msg[0] || 0x0D != msg.msg[1])
        return -1;
    ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_eps_network_feature_support_ie(&ie_ptr, &eps_nfs))
        return -1;
    if(eps_nfs.cs_lcs != LIBLTE_MME_CS_LCS_NOT_SUPPORTED || eps_nfs.esrps ||
       !eps_nfs.epc_lcs || eps_nfs.emc_bs || !eps_nfs.ims_vops)
        return -1;
    return 0;
}

int eur_test(uint8 bo)
{
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    msg.msg[0] = 0;
    if(LIBLTE_SUCCESS != liblte_mme_pack_eps_update_result_ie(0x6, bo, &ie_ptr))
        return -1;
    if(0 != (ie_ptr - msg.msg))
        return -1;
    if((0x6 << bo) != msg.msg[0])
        return -1;
    ie_ptr = msg.msg;
    uint8 result;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_eps_update_result_ie(&ie_ptr, bo, &result))
        return -1;
    if(result != 0x6)
        return -1;
    return 0;
}

int eps_update_result_test(void)
{
    if(0 != eur_test(0))
        return -1;
    if(0 != eur_test(4))
        return -1;
    return 0;
}

int eut_test(uint8 bo)
{
    LIBLTE_MME_EPS_UPDATE_TYPE_STRUCT eps_update_type;
    eps_update_type.type = LIBLTE_MME_EPS_UPDATE_TYPE_COMBINED_TA_LA_UPDATING;
    eps_update_type.active_flag = true;
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    msg.msg[0] = 0;
    if(LIBLTE_SUCCESS != liblte_mme_pack_eps_update_type_ie(&eps_update_type, bo, &ie_ptr))
        return -1;
    if(0 != (ie_ptr - msg.msg))
        return -1;
    if((0x9 << bo) != msg.msg[0])
        return -1;
    ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_eps_update_type_ie(&ie_ptr, bo, &eps_update_type))
        return -1;
    if(eps_update_type.type != LIBLTE_MME_EPS_UPDATE_TYPE_COMBINED_TA_LA_UPDATING ||
       !eps_update_type.active_flag)
        return -1;
    return 0;
}

int eps_update_type_test(void)
{
    if(0 != eut_test(0))
        return -1;
    if(0 != eut_test(4))
        return -1;
    return 0;
}

int esm_message_container_test(void)
{
    LIBLTE_BYTE_MSG_STRUCT esm_msg;
    esm_msg.N_bytes = 10;
    for(uint32 i=0; i<10; i++)
        esm_msg.msg[i] = i;
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_esm_message_container_ie(&esm_msg, &ie_ptr))
        return -1;
    if(12 != (ie_ptr - msg.msg))
        return -1;
    if(0x00 != msg.msg[0] || 0x0A != msg.msg[1] || 0x00 != msg.msg[2] || 0x01 != msg.msg[3] ||
       0x02 != msg.msg[4] || 0x03 != msg.msg[5] || 0x04 != msg.msg[6] || 0x05 != msg.msg[7] ||
       0x06 != msg.msg[8] || 0x07 != msg.msg[9] || 0x08 != msg.msg[10] ||
       0x09 != msg.msg[11])
        return -1;
    ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_esm_message_container_ie(&ie_ptr, &esm_msg))
        return -1;
    if(esm_msg.N_bytes != 10)
        return -1;
    for(uint32 i=0; i<10; i++)
        if(esm_msg.msg[i] != i)
            return -1;
    return 0;
}

int gprs_timer_test(void)
{
    LIBLTE_MME_GPRS_TIMER_STRUCT timer;
    timer.unit = LIBLTE_MME_GPRS_TIMER_UNIT_1_MINUTE;
    timer.value = 0x15;
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_gprs_timer_ie(&timer, &ie_ptr))
        return -1;
    if(1 != (ie_ptr - msg.msg))
        return -1;
    if(0x35 != msg.msg[0])
        return -1;
    ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_gprs_timer_ie(&ie_ptr, &timer))
        return -1;
    if(timer.unit != LIBLTE_MME_GPRS_TIMER_UNIT_1_MINUTE ||
       timer.value != 0x15)
        return -1;
    return 0;
}

int gprs_timer_2_test(void)
{
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_gprs_timer_2_ie(0xA5, &ie_ptr))
        return -1;
    if(2 != (ie_ptr - msg.msg))
        return -1;
    if(0x01 != msg.msg[0] || 0xA5 != msg.msg[1])
        return -1;
    ie_ptr = msg.msg;
    uint8 timer;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_gprs_timer_2_ie(&ie_ptr, &timer))
        return -1;
    if(timer != 0xA5)
        return -1;
    return 0;
}

int gprs_timer_3_test(void)
{
    LIBLTE_MME_GPRS_TIMER_3_STRUCT timer;
    timer.unit = LIBLTE_MME_GPRS_TIMER_3_UNIT_10_HOURS;
    timer.value = 0x15;
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_gprs_timer_3_ie(&timer, &ie_ptr))
        return -1;
    if(2 != (ie_ptr - msg.msg))
        return -1;
    if(0x01 != msg.msg[0] || 0x55 != msg.msg[1])
        return -1;
    ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_gprs_timer_3_ie(&ie_ptr, &timer))
        return -1;
    if(timer.unit != LIBLTE_MME_GPRS_TIMER_3_UNIT_10_HOURS ||
       timer.value != 0x15)
        return -1;
    return 0;
}

int it2_test(uint8 bo)
{
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    msg.msg[0] = 0;
    if(LIBLTE_SUCCESS != liblte_mme_pack_identity_type_2_ie(LIBLTE_MME_ID_TYPE_2_IMEI,
                                                            bo, &ie_ptr))
        return -1;
    if(0 != (ie_ptr - msg.msg))
        return -1;
    if((0x2 << bo) != msg.msg[0])
        return -1;
    ie_ptr = msg.msg;
    uint8 id_type;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_identity_type_2_ie(&ie_ptr, bo, &id_type))
        return -1;
    if(id_type != LIBLTE_MME_ID_TYPE_2_IMEI)
        return -1;
    return 0;
}

int identity_type_2_test(void)
{
    if(0 != it2_test(0))
        return -1;
    if(0 != it2_test(4))
        return -1;
    return 0;
}

int ir_test(uint8 bo)
{
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    msg.msg[0] = 0;
    if(LIBLTE_SUCCESS != liblte_mme_pack_imeisv_request_ie(LIBLTE_MME_IMEISV_REQUESTED,
                                                           bo, &ie_ptr))
        return -1;
    if(0 != (ie_ptr - msg.msg))
        return -1;
    if((0x1 << bo) != msg.msg[0])
        return -1;
    ie_ptr = msg.msg;
    LIBLTE_MME_IMEISV_REQUEST_ENUM imeisv_req;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_imeisv_request_ie(&ie_ptr, bo, &imeisv_req))
        return -1;
    if(imeisv_req != LIBLTE_MME_IMEISV_REQUESTED)
        return -1;
    return 0;
}

int imeisv_request_test(void)
{
    if(0 != ir_test(0))
        return -1;
    if(0 != ir_test(4))
        return -1;
    return 0;
}

int ksi_and_sequence_number_test(void)
{
    LIBLTE_MME_KSI_AND_SEQUENCE_NUMBER_STRUCT ksi_and_seq_num;
    ksi_and_seq_num.ksi = 0x6;
    ksi_and_seq_num.seq_num = 0x15;
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_ksi_and_sequence_number_ie(&ksi_and_seq_num,
                                                                    &ie_ptr))
        return -1;
    if(1 != (ie_ptr - msg.msg))
        return -1;
    if(0xD5 != msg.msg[0])
        return -1;
    ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_ksi_and_sequence_number_ie(&ie_ptr,
                                                                      &ksi_and_seq_num))
        return -1;
    if(ksi_and_seq_num.ksi != 0x6 || ksi_and_seq_num.seq_num != 0x15)
        return -1;
    return 0;
}

int ms_network_capability_test(void)
{
    LIBLTE_MME_MS_NETWORK_CAPABILITY_STRUCT ms_network_cap;
    ms_network_cap.ss_screening = LIBLTE_MME_SS_SCREENING_INDICATOR_PHASE_2;
    ms_network_cap.gea[1] = false;
    ms_network_cap.gea[2] = true;
    ms_network_cap.gea[3] = false;
    ms_network_cap.gea[4] = true;
    ms_network_cap.gea[5] = false;
    ms_network_cap.gea[6] = true;
    ms_network_cap.gea[7] = false;
    ms_network_cap.sm_cap_ded = true;
    ms_network_cap.sm_cap_gprs = false;
    ms_network_cap.ucs2 = true;
    ms_network_cap.solsa = false;
    ms_network_cap.revision = true;
    ms_network_cap.pfc = false;
    ms_network_cap.lcsva = true;
    ms_network_cap.ho_g2u_via_iu = false;
    ms_network_cap.ho_g2e_via_s1 = true;
    ms_network_cap.emm_comb = false;
    ms_network_cap.isr = true;
    ms_network_cap.srvcc = false;
    ms_network_cap.epc = true;
    ms_network_cap.nf = false;
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_ms_network_capability_ie(&ms_network_cap, &ie_ptr))
        return -1;
    if(4 != (ie_ptr - msg.msg))
        return -1;
    if(0x03 != msg.msg[0] || 0x55 != msg.msg[1] || 0x55 != msg.msg[2] || 0x54 != msg.msg[3])
        return -1;
    ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_ms_network_capability_ie(&ie_ptr, &ms_network_cap))
        return -1;
    if(ms_network_cap.ss_screening != LIBLTE_MME_SS_SCREENING_INDICATOR_PHASE_2 ||
       ms_network_cap.gea[1] || !ms_network_cap.gea[2] || ms_network_cap.gea[3] ||
       !ms_network_cap.gea[4] || ms_network_cap.gea[5] || !ms_network_cap.gea[6] ||
       ms_network_cap.gea[7] || !ms_network_cap.sm_cap_ded || ms_network_cap.sm_cap_gprs ||
       !ms_network_cap.ucs2 || ms_network_cap.solsa || !ms_network_cap.revision ||
       ms_network_cap.pfc || !ms_network_cap.lcsva || ms_network_cap.ho_g2u_via_iu ||
       !ms_network_cap.ho_g2e_via_s1 || ms_network_cap.emm_comb || !ms_network_cap.isr ||
       ms_network_cap.srvcc || !ms_network_cap.epc || ms_network_cap.nf)
        return -1;
    return 0;
}

int nksi_test(uint8 bo)
{
    LIBLTE_MME_NAS_KEY_SET_ID_STRUCT nas_ksi;
    nas_ksi.tsc_flag = LIBLTE_MME_TYPE_OF_SECURITY_CONTEXT_FLAG_MAPPED;
    nas_ksi.nas_ksi = 0x1;
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    msg.msg[0] = 0;
    if(LIBLTE_SUCCESS != liblte_mme_pack_nas_key_set_id_ie(&nas_ksi, bo, &ie_ptr))
        return -1;
    if(0 != (ie_ptr - msg.msg))
        return -1;
    if((0x9 << bo) != msg.msg[0])
        return -1;
    ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_nas_key_set_id_ie(&ie_ptr, bo, &nas_ksi))
        return -1;
    if(nas_ksi.tsc_flag != LIBLTE_MME_TYPE_OF_SECURITY_CONTEXT_FLAG_MAPPED ||
       nas_ksi.nas_ksi != 0x1)
        return -1;
    return 0;
}

int nas_key_set_id_test(void)
{
    if(0 != nksi_test(0))
        return -1;
    if(0 != nksi_test(4))
        return -1;
    return 0;
}

int nas_message_container_test(void)
{
    LIBLTE_BYTE_MSG_STRUCT nas_msg;
    nas_msg.N_bytes = 10;
    for(uint32 i=0; i<10; i++)
        nas_msg.msg[i] = i;
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_nas_message_container_ie(&nas_msg, &ie_ptr))
        return -1;
    if(11 != (ie_ptr - msg.msg))
        return -1;
    if(0x0A != msg.msg[0] || 0x00 != msg.msg[1] || 0x01 != msg.msg[2] || 0x02 != msg.msg[3] ||
       0x03 != msg.msg[4] || 0x04 != msg.msg[5] || 0x05 != msg.msg[6] || 0x06 != msg.msg[7] ||
       0x07 != msg.msg[8] || 0x08 != msg.msg[9] || 0x09 != msg.msg[10])
        return -1;
    ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_nas_message_container_ie(&ie_ptr, &nas_msg))
        return -1;
    if(nas_msg.N_bytes != 10)
        return -1;
    for(uint32 i=0; i<10; i++)
        if(nas_msg.msg[i] != i)
            return -1;
    return 0;
}

int nas_security_algorithms_test(void)
{
    LIBLTE_MME_NAS_SECURITY_ALGORITHMS_STRUCT nas_sec_algs;
    nas_sec_algs.type_of_eea = LIBLTE_MME_TYPE_OF_CIPHERING_ALGORITHM_EEA5;
    nas_sec_algs.type_of_eia = LIBLTE_MME_TYPE_OF_INTEGRITY_ALGORITHM_EIA4;
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_nas_security_algorithms_ie(&nas_sec_algs, &ie_ptr))
        return -1;
    if(1 != (ie_ptr - msg.msg))
        return -1;
    if(0x54 != msg.msg[0])
        return -1;
    ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_nas_security_algorithms_ie(&ie_ptr, &nas_sec_algs))
        return -1;
    if(nas_sec_algs.type_of_eea != LIBLTE_MME_TYPE_OF_CIPHERING_ALGORITHM_EEA5 ||
       nas_sec_algs.type_of_eia != LIBLTE_MME_TYPE_OF_INTEGRITY_ALGORITHM_EIA4)
        return -1;
    return 0;
}

int network_name_test(void)
{
    LIBLTE_MME_NETWORK_NAME_STRUCT net_name;
    net_name.name = "test";
    net_name.add_ci = LIBLTE_MME_ADD_CI_ADD;
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_network_name_ie(&net_name, &ie_ptr))
        return -1;
    if(6 != (ie_ptr - msg.msg))
        return -1;
    if(0x05 != msg.msg[0] || 0x8C != msg.msg[1] || 0xF4 != msg.msg[2] || 0xF2 != msg.msg[3] ||
       0x9C != msg.msg[4] || 0x0E != msg.msg[5])
        return -1;
    ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_network_name_ie(&ie_ptr, &net_name))
        return -1;
    if(net_name.name != "test" || net_name.add_ci != LIBLTE_MME_ADD_CI_ADD)
        return -1;
    return 0;
}

int nonce_test(void)
{
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_nonce_ie(0x12345678, &ie_ptr))
        return -1;
    if(4 != (ie_ptr - msg.msg))
        return -1;
    if(0x12 != msg.msg[0] || 0x34 != msg.msg[1] || 0x56 != msg.msg[2] || 0x78 != msg.msg[3])
        return -1;
    ie_ptr = msg.msg;
    uint32 nonce;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_nonce_ie(&ie_ptr, &nonce))
        return -1;
    if(nonce != 0x12345678)
        return -1;
    return 0;
}

int paging_identity_test(void)
{
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_paging_identity_ie(LIBLTE_MME_PAGING_IDENTITY_TMSI,
                                                            &ie_ptr))
        return -1;
    if(1 != (ie_ptr - msg.msg))
        return -1;
    if(0x01 != msg.msg[0])
        return -1;
    ie_ptr = msg.msg;
    uint8 paging_id;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_paging_identity_ie(&ie_ptr, &paging_id))
        return -1;
    if(paging_id != LIBLTE_MME_PAGING_IDENTITY_TMSI)
        return -1;
    return 0;
}

int p_tmsi_signature_test(void)
{
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_p_tmsi_signature_ie(0x12345678, &ie_ptr))
        return -1;
    if(4 != (ie_ptr - msg.msg))
        return -1;
    if(0x12 != msg.msg[0] || 0x34 != msg.msg[1] || 0x56 != msg.msg[2] || 0x78 != msg.msg[3])
        return -1;
    ie_ptr = msg.msg;
    uint32 p_tmsi_signature;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_p_tmsi_signature_ie(&ie_ptr, &p_tmsi_signature))
        return -1;
    if(p_tmsi_signature != 0x12345678)
        return -1;
    return 0;
}

int st_test(uint8 bo)
{
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    msg.msg[0] = 0;
    if(LIBLTE_SUCCESS != liblte_mme_pack_service_type_ie(LIBLTE_MME_SERVICE_TYPE_MT_CSFB,
                                                         bo, &ie_ptr))
        return -1;
    if(0 != (ie_ptr - msg.msg))
        return -1;
    if((0x1 << bo) != msg.msg[0])
        return -1;
    ie_ptr = msg.msg;
    uint8 value;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_service_type_ie(&ie_ptr, bo, &value))
        return -1;
    if(value != LIBLTE_MME_SERVICE_TYPE_MT_CSFB)
        return -1;
    return 0;
}

int service_type_test(void)
{
    if(0 != st_test(0))
        return -1;
    if(0 != st_test(4))
        return -1;
    return 0;
}

int short_mac_test(void)
{
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_short_mac_ie(0x1234, &ie_ptr))
        return -1;
    if(2 != (ie_ptr - msg.msg))
        return -1;
    if(0x12 != msg.msg[0] || 0x34 != msg.msg[1])
        return -1;
    ie_ptr = msg.msg;
    uint16 short_mac;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_short_mac_ie(&ie_ptr, &short_mac))
        return -1;
    if(short_mac != 0x1234)
        return -1;
    return 0;
}

int time_zone_test(void)
{
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_time_zone_ie(0x12, &ie_ptr))
        return -1;
    if(1 != (ie_ptr - msg.msg))
        return -1;
    if(0x12 != msg.msg[0])
        return -1;
    ie_ptr = msg.msg;
    uint8 time_zone;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_time_zone_ie(&ie_ptr, &time_zone))
        return -1;
    if(time_zone != 0x12)
        return -1;
    return 0;
}

int time_zone_and_time_test(void)
{
    LIBLTE_MME_TIME_ZONE_AND_TIME_STRUCT ttz;
    ttz.year = 2020;
    ttz.month = 1;
    ttz.day = 8;
    ttz.hour = 11;
    ttz.minute = 20;
    ttz.second = 50;
    ttz.tz = 0x12;
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_time_zone_and_time_ie(&ttz, &ie_ptr))
        return -1;
    if(7 != (ie_ptr - msg.msg))
        return -1;
    if(0x02 != msg.msg[0] || 0x10 != msg.msg[1] || 0x80 != msg.msg[2] || 0x11 != msg.msg[3] ||
       0x02 != msg.msg[4] || 0x05 != msg.msg[5] || 0x12 != msg.msg[6])
        return -1;
    ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_time_zone_and_time_ie(&ie_ptr, &ttz))
        return -1;
    if(ttz.year != 2020 || ttz.month != 1 || ttz.day != 8 || ttz.hour != 11 ||
       ttz.minute != 20 || ttz.second != 50 || ttz.tz != 0x12)
        return -1;
    return 0;
}

int ts_test(uint8 bo)
{
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    msg.msg[0] = 0;
    if(LIBLTE_SUCCESS != liblte_mme_pack_tmsi_status_ie(LIBLTE_MME_TMSI_STATUS_VALID_TMSI,
                                                        bo, &ie_ptr))
        return -1;
    if(0 != (ie_ptr - msg.msg))
        return -1;
    if((0x1 << bo) != msg.msg[0])
        return -1;
    ie_ptr = msg.msg;
    LIBLTE_MME_TMSI_STATUS_ENUM tmsi_status;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_tmsi_status_ie(&ie_ptr, bo, &tmsi_status))
        return -1;
    if(tmsi_status != LIBLTE_MME_TMSI_STATUS_VALID_TMSI)
        return -1;
    return 0;
}

int tmsi_status_test(void)
{
    if(0 != ts_test(0))
        return -1;
    if(0 != ts_test(4))
        return -1;
    return 0;
}

int tracking_area_id_test(void)
{
    LIBLTE_MME_TRACKING_AREA_ID_STRUCT tai;
    std::vector<MCC_MNC_Digit> mcc(3);
    mcc[0].SetValue(1);
    mcc[1].SetValue(2);
    mcc[2].SetValue(3);
    tai.mcc.SetValue(mcc);
    std::vector<MCC_MNC_Digit> mnc(2);
    mnc[0].SetValue(4);
    mnc[1].SetValue(5);
    tai.mnc.SetValue(mnc);
    tai.tac = 0xABCD;
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_tracking_area_id_ie(&tai, &ie_ptr))
        return -1;
    if(5 != (ie_ptr - msg.msg))
        return -1;
    if(0x21 != msg.msg[0] || 0xF3 != msg.msg[1] || 0x54 != msg.msg[2] || 0xAB != msg.msg[3] ||
       0xCD != msg.msg[4])
        return -1;
    ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_tracking_area_id_ie(&ie_ptr, &tai))
        return -1;
    if(tai.mcc.Value()[0].Value() != 1 || tai.mcc.Value()[1].Value() != 2 ||
       tai.mcc.Value()[2].Value() != 3 || tai.mnc.Value()[0].Value() != 4 ||
       tai.mnc.Value()[1].Value() != 5 || tai.tac != 0xABCD)
        return -1;
    return 0;
}

int tracking_area_identity_list_test(void)
{
    LIBLTE_MME_TRACKING_AREA_IDENTITY_LIST_STRUCT tai_list;
    tai_list.N_tais = 2;
    std::vector<MCC_MNC_Digit> mcc(3);
    mcc[0].SetValue(1);
    mcc[1].SetValue(2);
    mcc[2].SetValue(3);
    tai_list.tai[0].mcc.SetValue(mcc);
    std::vector<MCC_MNC_Digit> mnc2(2);
    mnc2[0].SetValue(4);
    mnc2[1].SetValue(5);
    tai_list.tai[0].mnc.SetValue(mnc2);
    tai_list.tai[0].tac = 0xABCD;
    mcc[0].SetValue(4);
    mcc[1].SetValue(5);
    mcc[2].SetValue(6);
    tai_list.tai[1].mcc.SetValue(mcc);
    std::vector<MCC_MNC_Digit> mnc3(3);
    mnc3[0].SetValue(7);
    mnc3[1].SetValue(8);
    mnc3[2].SetValue(9);
    tai_list.tai[1].mnc.SetValue(mnc3);
    tai_list.tai[1].tac = 0x1234;
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_tracking_area_identity_list_ie(&tai_list, &ie_ptr))
        return -1;
    if(12 != (ie_ptr - msg.msg))
        return -1;
    if(0x0B != msg.msg[0] || 0x41 != msg.msg[1] || 0x21 != msg.msg[2] || 0xF3 != msg.msg[3] ||
       0x54 != msg.msg[4] || 0xAB != msg.msg[5] || 0xCD != msg.msg[6] || 0x54 != msg.msg[7] ||
       0x96 != msg.msg[8] || 0x87 != msg.msg[9] || 0x12 != msg.msg[10] || 0x34 != msg.msg[11])
        return -1;
    ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_tracking_area_identity_list_ie(&ie_ptr, &tai_list))
        return -1;
    if(tai_list.N_tais != 2 || tai_list.tai[0].mcc.Value()[0].Value() != 1 ||
       tai_list.tai[0].mcc.Value()[1].Value() != 2 ||
       tai_list.tai[0].mcc.Value()[2].Value() != 3 ||
       tai_list.tai[0].mnc.Value()[0].Value() != 4 ||
       tai_list.tai[0].mnc.Value()[1].Value() != 5 ||
       tai_list.tai[0].tac != 0xABCD || tai_list.tai[1].mcc.Value()[0].Value() != 4 ||
       tai_list.tai[1].mcc.Value()[1].Value() != 5 ||
       tai_list.tai[1].mcc.Value()[2].Value() != 6 ||
       tai_list.tai[1].mnc.Value()[0].Value() != 7 ||
       tai_list.tai[1].mnc.Value()[1].Value() != 8 ||
       tai_list.tai[1].mnc.Value()[2].Value() != 9 || tai_list.tai[1].tac != 0x1234)
        return -1;
    return 0;
}

int ue_network_capability_test(void)
{
    LIBLTE_MME_UE_NETWORK_CAPABILITY_STRUCT ue_network_cap;
    for(uint32 i=0; i<8; i++)
    {
        ue_network_cap.eea[i] = i%2;
        ue_network_cap.eia[i] = i%2;
        ue_network_cap.uea[i] = i%2;
        ue_network_cap.uia[i] = i%2;
    }
    ue_network_cap.uea_present = true;
    ue_network_cap.ucs2 = false;
    ue_network_cap.ucs2_present = true;
    ue_network_cap.uia_present = true;
    ue_network_cap.lpp = false;
    ue_network_cap.lpp_present = true;
    ue_network_cap.lcs = true;
    ue_network_cap.lcs_present = true;
    ue_network_cap.onexsrvcc = false;
    ue_network_cap.onexsrvcc_present = true;
    ue_network_cap.nf = false;
    ue_network_cap.nf_present = true;
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_ue_network_capability_ie(&ue_network_cap, &ie_ptr))
        return -1;
    if(6 != (ie_ptr - msg.msg))
        return -1;
    if(0x05 != msg.msg[0] || 0x55 != msg.msg[1] || 0x55 != msg.msg[2] || 0x55 != msg.msg[3] ||
       0x55 != msg.msg[4] || 0x04 != msg.msg[5])
        return -1;
    ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_ue_network_capability_ie(&ie_ptr, &ue_network_cap))
        return -1;
    if(!ue_network_cap.uea_present || ue_network_cap.ucs2 || !ue_network_cap.ucs2_present ||
       !ue_network_cap.uia_present || ue_network_cap.lpp || !ue_network_cap.lpp_present ||
       !ue_network_cap.lcs || !ue_network_cap.lcs_present || ue_network_cap.onexsrvcc ||
       !ue_network_cap.onexsrvcc_present || ue_network_cap.nf || !ue_network_cap.nf_present)
        return -1;
    for(uint32 i=0; i<8; i++)
        if(ue_network_cap.eea[i] != i%2 || ue_network_cap.eia[i] != i%2 ||
           ue_network_cap.uea[i] != i%2 || ue_network_cap.uia[i] != i%2)
            return -1;
    return 0;
}

int urcun_test(uint8 bo)
{
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    msg.msg[0] = 0;
    if(LIBLTE_SUCCESS != liblte_mme_pack_ue_radio_capability_update_needed_ie(LIBLTE_MME_URC_UPDATE_NEEDED,
                                                                              bo, &ie_ptr))
        return -1;
    if(0 != (ie_ptr - msg.msg))
        return -1;
    if((0x1 << bo) != msg.msg[0])
        return -1;
    ie_ptr = msg.msg;
    uint8 urc_update;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_ue_radio_capability_update_needed_ie(&ie_ptr, bo,
                                                                                &urc_update))
        return -1;
    if(urc_update != LIBLTE_MME_URC_UPDATE_NEEDED)
        return -1;
    return 0;
}

int ue_radio_capability_update_needed_test(void)
{
    if(0 != urcun_test(0))
        return -1;
    if(0 != urcun_test(4))
        return -1;
    return 0;
}

int ue_security_capabilities_test(void)
{
    LIBLTE_MME_UE_SECURITY_CAPABILITIES_STRUCT ue_sec_cap;
    for(uint32 i=0; i<8; i++)
    {
        ue_sec_cap.eea[i] = i%2;
        ue_sec_cap.eia[i] = i%2;
        ue_sec_cap.uea[i] = i%2;
        ue_sec_cap.uia[i] = i%2;
        ue_sec_cap.gea[i] = i%2;
    }
    ue_sec_cap.uea_present = true;
    ue_sec_cap.uia_present = true;
    ue_sec_cap.gea_present = true;
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_ue_security_capabilities_ie(&ue_sec_cap, &ie_ptr))
        return -1;
    if(6 != (ie_ptr - msg.msg))
        return -1;
    if(0x05 != msg.msg[0] || 0x55 != msg.msg[1] || 0x55 != msg.msg[2] || 0x55 != msg.msg[3] ||
       0x55 != msg.msg[4] || 0x55 != msg.msg[5])
        return -1;
    ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_ue_security_capabilities_ie(&ie_ptr, &ue_sec_cap))
        return -1;
    if(!ue_sec_cap.uea_present || !ue_sec_cap.uia_present || !ue_sec_cap.gea_present)
        return -1;
    for(uint32 i=0; i<8; i++)
        if(ue_sec_cap.eea[i] != i%2 || ue_sec_cap.eia[i] != i%2 ||
           ue_sec_cap.uea[i] != i%2 || ue_sec_cap.uia[i] != i%2 || ue_sec_cap.gea[i] != i%2)
            return -1;
    return 0;
}

int emergency_number_list_test(void)
{
    LIBLTE_MME_EMERGENCY_NUMBER_LIST_STRUCT emerg_num_list;
    emerg_num_list.N_emerg_nums = 1;
    emerg_num_list.emerg_num[0].emerg_service_cat = LIBLTE_MME_EMERGENCY_SERVICE_CATEGORY_AMBULANCE;
    emerg_num_list.emerg_num[0].N_emerg_num_digits = 3;
    emerg_num_list.emerg_num[0].emerg_num[0] = 9;
    emerg_num_list.emerg_num[0].emerg_num[1] = 1;
    emerg_num_list.emerg_num[0].emerg_num[2] = 1;
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_emergency_number_list_ie(&emerg_num_list, &ie_ptr))
        return -1;
    if(5 != (ie_ptr - msg.msg))
        return -1;
    if(0x03 != msg.msg[0] || 0x03 != msg.msg[1] || 0x01 != msg.msg[2] || 0x19 != msg.msg[3] ||
       0xF1 != msg.msg[4])
        return -1;
    ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_emergency_number_list_ie(&ie_ptr, &emerg_num_list))
        return -1;
    if(emerg_num_list.N_emerg_nums != 1 ||
       emerg_num_list.emerg_num[0].emerg_service_cat != LIBLTE_MME_EMERGENCY_SERVICE_CATEGORY_AMBULANCE ||
       emerg_num_list.emerg_num[0].N_emerg_num_digits != 3 ||
       emerg_num_list.emerg_num[0].emerg_num[0] != 9 ||
       emerg_num_list.emerg_num[0].emerg_num[1] != 1 ||
       emerg_num_list.emerg_num[0].emerg_num[2] != 1)
        return -1;
    return 0;
}

int cli_test(void)
{
    LIBLTE_MME_CLI_STRUCT cli;
    cli.type_of_num = LIBLTE_MME_TYPE_OF_NUMBER_NETWORK_SPECIFIC;
    cli.num_plan_id = LIBLTE_MME_NUMBERING_PLAN_IDENTIFICATION_NATIONAL;
    cli.pres_ind = LIBLTE_MME_PRESENTATION_RESTRICTED;
    cli.screen_ind = LIBLTE_MME_SCREENING_USER_PROVIDED_VERIFIED_FAILED;
    cli.num_digits = 10;
    for(uint32 i=0; i<10; i++)
        cli.digits[i] = i;
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_cli_ie(&cli, &ie_ptr))
        return -1;
    if(8 != (ie_ptr - msg.msg))
        return -1;
    if(0x07 != msg.msg[0] || 0xB4 != msg.msg[1] || 0xA2 != msg.msg[2] || 0x10 != msg.msg[3] ||
       0x32 != msg.msg[4] || 0x54 != msg.msg[5] || 0x76 != msg.msg[6] || 0x98 != msg.msg[7])
        return -1;
    ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_cli_ie(&ie_ptr, &cli))
        return -1;
    if(cli.type_of_num != LIBLTE_MME_TYPE_OF_NUMBER_NETWORK_SPECIFIC ||
       cli.num_plan_id != LIBLTE_MME_NUMBERING_PLAN_IDENTIFICATION_NATIONAL ||
       cli.pres_ind != LIBLTE_MME_PRESENTATION_RESTRICTED ||
       cli.screen_ind != LIBLTE_MME_SCREENING_USER_PROVIDED_VERIFIED_FAILED ||
       cli.num_digits != 10)
        return -1;
    for(uint32 i=0; i<10; i++)
        if(cli.digits[i] != i)
            return -1;
    return 0;
}

int ss_code_test(void)
{
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_ss_code_ie(0xA5, &ie_ptr))
        return -1;
    if(1 != (ie_ptr - msg.msg))
        return -1;
    if(0xA5 != msg.msg[0])
        return -1;
    ie_ptr = msg.msg;
    uint8 code;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_ss_code_ie(&ie_ptr, &code))
        return -1;
    if(code != 0xA5)
        return -1;
    return 0;
}

int lcs_indicator_test(void)
{
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_lcs_indicator_ie(0xA5, &ie_ptr))
        return -1;
    if(1 != (ie_ptr - msg.msg))
        return -1;
    if(0xA5 != msg.msg[0])
        return -1;
    ie_ptr = msg.msg;
    uint8 lcs_ind;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_lcs_indicator_ie(&ie_ptr, &lcs_ind))
        return -1;
    if(lcs_ind != 0xA5)
        return -1;
    return 0;
}

int generic_message_container_type_test(void)
{
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_generic_message_container_type_ie(0xA5, &ie_ptr))
        return -1;
    if(1 != (ie_ptr - msg.msg))
        return -1;
    if(0xA5 != msg.msg[0])
        return -1;
    ie_ptr = msg.msg;
    uint8 msg_cont_type;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_generic_message_container_type_ie(&ie_ptr,
                                                                             &msg_cont_type))
        return -1;
    if(msg_cont_type != 0xA5)
        return -1;
    return 0;
}

int generic_message_container_test(void)
{
    LIBLTE_BYTE_MSG_STRUCT gen_msg;
    gen_msg.N_bytes = 10;
    for(uint32 i=0; i<10; i++)
        gen_msg.msg[i] = i;
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_generic_message_container_ie(&gen_msg, &ie_ptr))
        return -1;
    if(12 != (ie_ptr - msg.msg))
        return -1;
    if(0x00 != msg.msg[0] || 0x0A != msg.msg[1] || 0x00 != msg.msg[2] || 0x01 != msg.msg[3] ||
       0x02 != msg.msg[4] || 0x03 != msg.msg[5] || 0x04 != msg.msg[6] || 0x05 != msg.msg[7] ||
       0x06 != msg.msg[8] || 0x07 != msg.msg[9] || 0x08 != msg.msg[10] ||
       0x09 != msg.msg[11])
        return -1;
    ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_generic_message_container_ie(&ie_ptr, &gen_msg))
        return -1;
    if(gen_msg.N_bytes != 10)
        return -1;
    for(uint32 i=0; i<10; i++)
        if(gen_msg.msg[i] != i)
            return -1;
    return 0;
}

int voice_domain_pref_and_ue_usage_setting_test(void)
{
    LIBLTE_MME_VOICE_DOMAIN_PREF_AND_UE_USAGE_SETTING_STRUCT vdpuus;
    vdpuus.ue_usage_setting = LIBLTE_MME_UE_USAGE_SETTING_DATA_CENTRIC;
    vdpuus.voice_domain_pref = LIBLTE_MME_VOICE_DOMAIN_PREF_PS_ONLY;
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_voice_domain_pref_and_ue_usage_setting_ie(&vdpuus,
                                                                                   &ie_ptr))
        return -1;
    if(2 != (ie_ptr - msg.msg))
        return -1;
    if(0x01 != msg.msg[0] || 0x05 != msg.msg[1])
        return -1;
    ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_voice_domain_pref_and_ue_usage_setting_ie(&ie_ptr,
                                                                                     &vdpuus))
        return -1;
    if(vdpuus.ue_usage_setting != LIBLTE_MME_UE_USAGE_SETTING_DATA_CENTRIC ||
       vdpuus.voice_domain_pref != LIBLTE_MME_VOICE_DOMAIN_PREF_PS_ONLY)
        return -1;
    return 0;
}

int gt_test(uint8 bo)
{
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    msg.msg[0] = 0;
    if(LIBLTE_SUCCESS != liblte_mme_pack_guti_type_ie(LIBLTE_MME_GUTI_TYPE_MAPPED,
                                                      bo, &ie_ptr))
        return -1;
    if(0 != (ie_ptr - msg.msg))
        return -1;
    if((0x1 << bo) != msg.msg[0])
        return -1;
    ie_ptr = msg.msg;
    LIBLTE_MME_GUTI_TYPE_ENUM guti_type;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_guti_type_ie(&ie_ptr, bo, &guti_type))
        return -1;
    if(guti_type != LIBLTE_MME_GUTI_TYPE_MAPPED)
        return -1;
    return 0;
}

int guti_type_test(void)
{
    if(0 != gt_test(0))
        return -1;
    if(0 != gt_test(4))
        return -1;
    return 0;
}

int access_point_name_test(void)
{
    LIBLTE_MME_ACCESS_POINT_NAME_STRUCT apn;
    apn.apn = "test";
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_access_point_name_ie(&apn, &ie_ptr))
        return -1;
    if(6 != (ie_ptr - msg.msg))
        return -1;
    if(0x05 != msg.msg[0] || 0x04 != msg.msg[1] || 't' != msg.msg[2] || 'e' != msg.msg[3] ||
       's' != msg.msg[4] || 't' != msg.msg[5])
        return -1;
    ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_access_point_name_ie(&ie_ptr, &apn))
        return -1;
    if(apn.apn != "test")
        return -1;
    return 0;
}

int apn_aggregate_maximum_bit_rate_test(void)
{
    LIBLTE_MME_APN_AGGREGATE_MAXIMUM_BIT_RATE_STRUCT apn_ambr;
    apn_ambr.apn_ambr_dl = 0xA5;
    apn_ambr.apn_ambr_ul = 0x5A;
    apn_ambr.ext_present = true;
    apn_ambr.apn_ambr_dl_ext = 0x12;
    apn_ambr.apn_ambr_ul_ext = 0xEF;
    apn_ambr.ext2_present = false;
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_apn_aggregate_maximum_bit_rate_ie(&apn_ambr,
                                                                           &ie_ptr))
        return -1;
    if(5 != (ie_ptr - msg.msg))
        return -1;
    if(0x04 != msg.msg[0] || 0xA5 != msg.msg[1] || 0x5A != msg.msg[2] || 0x12 != msg.msg[3] ||
       0xEF != msg.msg[4])
        return -1;
    ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_apn_aggregate_maximum_bit_rate_ie(&ie_ptr,
                                                                             &apn_ambr))
        return -1;
    if(apn_ambr.apn_ambr_dl != 0xA5 || apn_ambr.apn_ambr_ul != 0x5A ||
       !apn_ambr.ext_present || apn_ambr.apn_ambr_dl_ext != 0x12 ||
       apn_ambr.apn_ambr_ul_ext != 0xEF || apn_ambr.ext2_present)
        return -1;
    return 0;
}

int ct_test(uint8 bo)
{
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    msg.msg[0] = 0;
    if(LIBLTE_SUCCESS != liblte_mme_pack_connectivity_type_ie(LIBLTE_MME_CONNECTIVITY_TYPE_LIPA_PDN,
                                                              bo, &ie_ptr))
        return -1;
    if(0 != (ie_ptr - msg.msg))
        return -1;
    if((0x1 << bo) != msg.msg[0])
        return -1;
    ie_ptr = msg.msg;
    uint8 con_type;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_connectivity_type_ie(&ie_ptr, bo, &con_type))
        return -1;
    if(con_type != LIBLTE_MME_CONNECTIVITY_TYPE_LIPA_PDN)
        return -1;
    return 0;
}

int connectivity_type_test(void)
{
    if(0 != ct_test(0))
        return -1;
    if(0 != ct_test(4))
        return -1;
    return 0;
}

int eps_quality_of_service_test(void)
{
    LIBLTE_MME_EPS_QUALITY_OF_SERVICE_STRUCT qos;
    qos.qci = 0xA5;
    qos.br_present = true;
    qos.mbr_ul = 0x5A;
    qos.mbr_dl = 0x12;
    qos.gbr_ul = 0x34;
    qos.gbr_dl = 0x56;
    qos.br_ext_present = false;
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_eps_quality_of_service_ie(&qos, &ie_ptr))
        return -1;
    if(6 != (ie_ptr - msg.msg))
        return -1;
    if(0x05 != msg.msg[0] || 0xA5 != msg.msg[1] || 0x5A != msg.msg[2] || 0x12 != msg.msg[3] ||
       0x34 != msg.msg[4] || 0x56 != msg.msg[5])
        return -1;
    ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_eps_quality_of_service_ie(&ie_ptr, &qos))
        return -1;
    if(qos.qci != 0xA5 || !qos.br_present || qos.mbr_ul != 0x5A || qos.mbr_dl != 0x12 ||
       qos.gbr_ul != 0x34 || qos.gbr_dl != 0x56 || qos.br_ext_present)
        return -1;
    return 0;
}

int esm_cause_test(void)
{
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_esm_cause_ie(0xA5, &ie_ptr))
        return -1;
    if(1 != (ie_ptr - msg.msg))
        return -1;
    if(0xA5 != msg.msg[0])
        return -1;
    ie_ptr = msg.msg;
    uint8 cause;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_esm_cause_ie(&ie_ptr, &cause))
        return -1;
    if(cause != 0xA5)
        return -1;
    return 0;
}

int eitf_test(uint8 bo)
{
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    msg.msg[0] = 0;
    if(LIBLTE_SUCCESS != liblte_mme_pack_esm_info_transfer_flag_ie(LIBLTE_MME_ESM_INFO_TRANSFER_FLAG_REQUIRED,
                                                                   bo, &ie_ptr))
        return -1;
    if(0 != (ie_ptr - msg.msg))
        return -1;
    if((0x1 << bo) != msg.msg[0])
        return -1;
    ie_ptr = msg.msg;
    LIBLTE_MME_ESM_INFO_TRANSFER_FLAG_ENUM esm_info_transfer_flag;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_esm_info_transfer_flag_ie(&ie_ptr, bo,
                                                                     &esm_info_transfer_flag))
        return -1;
    if(esm_info_transfer_flag != LIBLTE_MME_ESM_INFO_TRANSFER_FLAG_REQUIRED)
        return -1;
    return 0;
}

int esm_info_transfer_flag_test(void)
{
    if(0 != eitf_test(0))
        return -1;
    if(0 != eitf_test(4))
        return -1;
    return 0;
}

int lebi_test(uint8 bo)
{
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    msg.msg[0] = 0;
    if(LIBLTE_SUCCESS != liblte_mme_pack_linked_eps_bearer_identity_ie(LIBLTE_MME_LINKED_EPS_BEARER_IDENTITY_5,
                                                                       bo, &ie_ptr))
        return -1;
    if(0 != (ie_ptr - msg.msg))
        return -1;
    if((0x5 << bo) != msg.msg[0])
        return -1;
    ie_ptr = msg.msg;
    uint8 bearer_id;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_linked_eps_bearer_identity_ie(&ie_ptr, bo,
                                                                         &bearer_id))
        return -1;
    if(bearer_id != LIBLTE_MME_LINKED_EPS_BEARER_IDENTITY_5)
        return -1;
    return 0;
}

int linked_eps_bearer_identity_test(void)
{
    if(0 != lebi_test(0))
        return -1;
    if(0 != lebi_test(4))
        return -1;
    return 0;
}

int llc_service_access_point_identifier_test(void)
{
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_llc_service_access_point_identifier_ie(LIBLTE_MME_LLC_SAPI_3,
                                                                                &ie_ptr))
        return -1;
    if(1 != (ie_ptr - msg.msg))
        return -1;
    if(0x03 != msg.msg[0])
        return -1;
    ie_ptr = msg.msg;
    uint8 llc_sapi;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_llc_service_access_point_identifier_ie(&ie_ptr,
                                                                                  &llc_sapi))
        return -1;
    if(llc_sapi != LIBLTE_MME_LLC_SAPI_3)
        return -1;
    return 0;
}

int notification_indicator_test(void)
{
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_notification_indicator_ie(LIBLTE_MME_NOTIFICATION_INDICATOR_SRVCC_HO_CANCELLED_IMS_SESSION_REEST_REQ,
                                                                   &ie_ptr))
        return -1;
    if(2 != (ie_ptr - msg.msg))
        return -1;
    if(0x01 != msg.msg[0] || 0x01 != msg.msg[1])
        return -1;
    ie_ptr = msg.msg;
    uint8 notification_ind;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_notification_indicator_ie(&ie_ptr,
                                                                     &notification_ind))
        return -1;
    if(notification_ind != LIBLTE_MME_NOTIFICATION_INDICATOR_SRVCC_HO_CANCELLED_IMS_SESSION_REEST_REQ)
        return -1;
    return 0;
}

int packet_flow_identifier_test(void)
{
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_packet_flow_identifier_ie(LIBLTE_MME_PACKET_FLOW_ID_SMS,
                                                                   &ie_ptr))
        return -1;
    if(2 != (ie_ptr - msg.msg))
        return -1;
    if(0x01 != msg.msg[0] || 0x02 != msg.msg[1])
        return -1;
    ie_ptr = msg.msg;
    uint8 packet_flow_id;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_packet_flow_identifier_ie(&ie_ptr,
                                                                     &packet_flow_id))
        return -1;
    if(packet_flow_id != LIBLTE_MME_PACKET_FLOW_ID_SMS)
        return -1;
    return 0;
}

int pdn_address_test(void)
{
    LIBLTE_MME_PDN_ADDRESS_STRUCT pdn_addr;
    pdn_addr.pdn_type = LIBLTE_MME_PDN_TYPE_IPV4;
    for(uint32 i=0; i<4; i++)
        pdn_addr.addr[i] = i;
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_pdn_address_ie(&pdn_addr, &ie_ptr))
        return -1;
    if(6 != (ie_ptr - msg.msg))
        return -1;
    if(0x05 != msg.msg[0] || 0x01 != msg.msg[1] || 0x00 != msg.msg[2] || 0x01 != msg.msg[3] ||
       0x02 != msg.msg[4] || 0x03 != msg.msg[5])
        return -1;
    ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_pdn_address_ie(&ie_ptr, &pdn_addr))
        return -1;
    if(pdn_addr.pdn_type != LIBLTE_MME_PDN_TYPE_IPV4)
        return -1;
    for(uint32 i=0; i<4; i++)
        if(pdn_addr.addr[i] != i)
            return -1;
    return 0;
}

int pt_test(uint8 bo)
{
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    msg.msg[0] = 0;
    if(LIBLTE_SUCCESS != liblte_mme_pack_pdn_type_ie(LIBLTE_MME_PDN_TYPE_IPV4V6, bo, &ie_ptr))
        return -1;
    if(0 != (ie_ptr - msg.msg))
        return -1;
    if((0x3 << bo) != msg.msg[0])
        return -1;
    ie_ptr = msg.msg;
    uint8 pdn_type;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_pdn_type_ie(&ie_ptr, bo, &pdn_type))
        return -1;
    if(pdn_type != LIBLTE_MME_PDN_TYPE_IPV4V6)
        return -1;
    return 0;
}

int pdn_type_test(void)
{
    if(0 != pt_test(0))
        return -1;
    if(0 != pt_test(4))
        return -1;
    return 0;
}

int protocol_config_options_test(void)
{
    LIBLTE_MME_PROTOCOL_CONFIG_OPTIONS_STRUCT pco;
    pco.N_opts = 2;
    pco.opt[0].id = LIBLTE_MME_CONFIGURATION_PROTOCOL_OPTIONS_LCP;
    pco.opt[0].len = 2;
    pco.opt[0].contents[0] = 0xA5;
    pco.opt[0].contents[1] = 0x5A;
    pco.opt[1].id = LIBLTE_MME_CONFIGURATION_PROTOCOL_OPTIONS_PAP;
    pco.opt[1].len = 4;
    for(uint32 i=0; i<4; i++)
        pco.opt[1].contents[i] = i;
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_protocol_config_options_ie(&pco, &ie_ptr))
        return -1;
    if(14 != (ie_ptr - msg.msg))
        return -1;
    if(0x0D != msg.msg[0] || 0x80 != msg.msg[1] || 0xC0 != msg.msg[2] || 0x21 != msg.msg[3] ||
       0x02 != msg.msg[4] || 0xA5 != msg.msg[5] || 0x5A != msg.msg[6] || 0xC0 != msg.msg[7] ||
       0x23 != msg.msg[8] || 0x04 != msg.msg[9] || 0x00 != msg.msg[10] ||
       0x01 != msg.msg[11] || 0x02 != msg.msg[12] || 0x03 != msg.msg[13])
        return -1;
    ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_protocol_config_options_ie(&ie_ptr, &pco))
        return -1;
    if(pco.N_opts != 2 || pco.opt[0].id != LIBLTE_MME_CONFIGURATION_PROTOCOL_OPTIONS_LCP ||
       pco.opt[0].len != 2 || pco.opt[0].contents[0] != 0xA5 ||
       pco.opt[0].contents[1] != 0x5A ||
       pco.opt[1].id != LIBLTE_MME_CONFIGURATION_PROTOCOL_OPTIONS_PAP ||
       pco.opt[1].len != 4)
        return -1;
    for(uint32 i=0; i<4; i++)
        if(pco.opt[1].contents[i] != i)
            return -1;
    return 0;
}

int quality_of_service_test(void)
{
    LIBLTE_MME_QUALITY_OF_SERVICE_STRUCT qos;
    qos.delay_class = LIBLTE_MME_QOS_DELAY_CLASS_1;
    qos.reliability_class = LIBLTE_MME_QOS_RELIABILITY_CLASS_UL_SUBSCRIBED;
    qos.peak_throughput = LIBLTE_MME_QOS_PEAK_THROUGHPUT_UP_TO_4000BPS;
    qos.precedence_class = LIBLTE_MME_QOS_PRECEDENCE_CLASS_HIGH_PRIORITY;
    qos.mean_throughput = LIBLTE_MME_QOS_MEAN_THROUGHPUT_100BPH;
    qos.traffic_class = LIBLTE_MME_QOS_TRAFFIC_CLASS_STREAMING;
    qos.delivery_order = LIBLTE_MME_QOS_DELIVERY_ORDER_WITH_DELIVERY_ORDER_YES;
    qos.delivery_of_erroneous_sdu = LIBLTE_MME_QOS_DELIVERY_OF_ERRONEOUS_SDU_NO_DETECT;
    qos.max_sdu_size = 0xA5;
    qos.mbr_ul = 0x5A;
    qos.mbr_dl = 0xA5;
    qos.residual_ber = LIBLTE_MME_QOS_RESIDUAL_BER_1_E_NEG_4;
    qos.sdu_error_ratio = LIBLTE_MME_QOS_SDU_ERROR_RATIO_7_E_NEG_3;
    qos.transfer_delay = 0x15;
    qos.traffic_handling_prio = LIBLTE_MME_QOS_TRAFFIC_HANDLING_PRIORITY_LEVEL_1;
    qos.gbr_ul = 0xA5;
    qos.gbr_dl = 0x5A;
    qos.signalling_ind = LIBLTE_MME_QOS_SIGNALLING_INDICATOR_OPTIMIZED_FOR_SIGNALLING;
    qos.source_stats_descriptor = LIBLTE_MME_QOS_SOURCE_STATISTICS_DESCRIPTOR_SPEECH;
    qos.mbr_dl_ext = 0xA5;
    qos.gbr_dl_ext = 0x5A;
    qos.dl_ext_present = true;
    qos.ul_ext_present = false;
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_quality_of_service_ie(&qos, &ie_ptr))
        return -1;
    if(15 != (ie_ptr - msg.msg))
        return -1;
    if(0x0E != msg.msg[0] || 0x08 != msg.msg[1] || 0x31 != msg.msg[2] || 0x01 != msg.msg[3] ||
       0x49 != msg.msg[4] || 0xA5 != msg.msg[5] || 0x5A != msg.msg[6] || 0xA5 != msg.msg[7] ||
       0x62 != msg.msg[8] || 0x55 != msg.msg[9] || 0xA5 != msg.msg[10] ||
       0x5A != msg.msg[11] || 0x11 != msg.msg[12] || 0xA5 != msg.msg[13] ||
       0x5A != msg.msg[14])
        return -1;
    ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_quality_of_service_ie(&ie_ptr, &qos))
        return -1;
    if(qos.delay_class != LIBLTE_MME_QOS_DELAY_CLASS_1 ||
       qos.reliability_class != LIBLTE_MME_QOS_RELIABILITY_CLASS_UL_SUBSCRIBED ||
       qos.peak_throughput != LIBLTE_MME_QOS_PEAK_THROUGHPUT_UP_TO_4000BPS ||
       qos.precedence_class != LIBLTE_MME_QOS_PRECEDENCE_CLASS_HIGH_PRIORITY ||
       qos.mean_throughput != LIBLTE_MME_QOS_MEAN_THROUGHPUT_100BPH ||
       qos.traffic_class != LIBLTE_MME_QOS_TRAFFIC_CLASS_STREAMING ||
       qos.delivery_order != LIBLTE_MME_QOS_DELIVERY_ORDER_WITH_DELIVERY_ORDER_YES ||
       qos.delivery_of_erroneous_sdu != LIBLTE_MME_QOS_DELIVERY_OF_ERRONEOUS_SDU_NO_DETECT ||
       qos.max_sdu_size != 0xA5 || qos.mbr_ul != 0x5A || qos.mbr_dl != 0xA5 ||
       qos.residual_ber != LIBLTE_MME_QOS_RESIDUAL_BER_1_E_NEG_4 ||
       qos.sdu_error_ratio != LIBLTE_MME_QOS_SDU_ERROR_RATIO_7_E_NEG_3 ||
       qos.transfer_delay != 0x15 ||
       qos.traffic_handling_prio != LIBLTE_MME_QOS_TRAFFIC_HANDLING_PRIORITY_LEVEL_1 ||
       qos.gbr_ul != 0xA5 || qos.gbr_dl != 0x5A ||
       qos.signalling_ind != LIBLTE_MME_QOS_SIGNALLING_INDICATOR_OPTIMIZED_FOR_SIGNALLING ||
       qos.source_stats_descriptor != LIBLTE_MME_QOS_SOURCE_STATISTICS_DESCRIPTOR_SPEECH ||
       qos.mbr_dl_ext != 0xA5 || qos.gbr_dl_ext != 0x5A || !qos.dl_ext_present ||
       qos.ul_ext_present)
        return -1;
    return 0;
}

int rp_test(uint8 bo)
{
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    msg.msg[0] = 0;
    if(LIBLTE_SUCCESS != liblte_mme_pack_radio_priority_ie(LIBLTE_MME_RADIO_PRIORITY_LEVEL_3,
                                                           bo, &ie_ptr))
        return -1;
    if(0 != (ie_ptr - msg.msg))
        return -1;
    if((0x3 << bo) != msg.msg[0])
        return -1;
    ie_ptr = msg.msg;
    uint8 radio_prio;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_radio_priority_ie(&ie_ptr, bo, &radio_prio))
        return -1;
    if(radio_prio != LIBLTE_MME_RADIO_PRIORITY_LEVEL_3)
        return -1;
    return 0;
}

int radio_priority_test(void)
{
    if(0 != rp_test(0))
        return -1;
    if(0 != rp_test(4))
        return -1;
    return 0;
}

int rt_test(uint8 bo)
{
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    msg.msg[0] = 0;
    if(LIBLTE_SUCCESS != liblte_mme_pack_request_type_ie(LIBLTE_MME_REQUEST_TYPE_UNUSED,
                                                         bo, &ie_ptr))
        return -1;
    if(0 != (ie_ptr - msg.msg))
        return -1;
    if((0x3 << bo) != msg.msg[0])
        return -1;
    ie_ptr = msg.msg;
    uint8 req_type;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_request_type_ie(&ie_ptr, bo, &req_type))
        return -1;
    if(req_type != LIBLTE_MME_REQUEST_TYPE_UNUSED)
        return -1;
    return 0;
}

int request_type_test(void)
{
    if(0 != rt_test(0))
        return -1;
    if(0 != rt_test(4))
        return -1;
    return 0;
}

int traffic_flow_aggregate_description_test(void)
{
    LIBLTE_MME_TRAFFIC_FLOW_AGGREGATE_DESCRIPTION_STRUCT tfad;
    tfad.packet_filter_list_size = 1;
    tfad.parameter_list_size = 2;
    tfad.tft_op_code = LIBLTE_MME_TFT_OPERATION_CODE_DELETE_EXISTING_TFT;
    tfad.packet_filter_list[0].dir = LIBLTE_MME_TFT_PACKET_FILTER_DIRECTION_DOWNLINK_ONLY;
    tfad.packet_filter_list[0].id = 0x5;
    tfad.packet_filter_list[0].eval_precedence = 0x5A;
    tfad.packet_filter_list[0].filter_size = 2;
    tfad.packet_filter_list[0].filter[0] = 0xA5;
    tfad.packet_filter_list[0].filter[1] = 0x5A;
    tfad.parameter_list[0].id = 0xAB;
    tfad.parameter_list[0].parameter_size = 2;
    tfad.parameter_list[0].parameter[0] = 0xA5;
    tfad.parameter_list[0].parameter[1] = 0x5A;
    tfad.parameter_list[1].id = 0xCD;
    tfad.parameter_list[1].parameter_size = 2;
    tfad.parameter_list[1].parameter[0] = 0x12;
    tfad.parameter_list[1].parameter[1] = 0x34;
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_traffic_flow_aggregate_description_ie(&tfad,
                                                                               &ie_ptr))
        return -1;
    if(15 != (ie_ptr - msg.msg))
        return -1;
    if(0x0E != msg.msg[0] || 0x51 != msg.msg[1] || 0x15 != msg.msg[2] || 0x5A != msg.msg[3] ||
       0x02 != msg.msg[4] || 0xA5 != msg.msg[5] || 0x5A != msg.msg[6] || 0xAB != msg.msg[7] ||
       0x02 != msg.msg[8] || 0xA5 != msg.msg[9] || 0x5A != msg.msg[10] ||
       0xCD != msg.msg[11] || 0x02 != msg.msg[12] || 0x12 != msg.msg[13] ||
       0x34 != msg.msg[14])
        return -1;
    ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_traffic_flow_aggregate_description_ie(&ie_ptr,
                                                                                 &tfad))
        return -1;
    if(tfad.packet_filter_list_size != 1 || tfad.parameter_list_size != 2 ||
       tfad.tft_op_code != LIBLTE_MME_TFT_OPERATION_CODE_DELETE_EXISTING_TFT ||
       tfad.packet_filter_list[0].dir != LIBLTE_MME_TFT_PACKET_FILTER_DIRECTION_DOWNLINK_ONLY ||
       tfad.packet_filter_list[0].id != 0x5 ||
       tfad.packet_filter_list[0].eval_precedence != 0x5A ||
       tfad.packet_filter_list[0].filter_size != 2 ||
       tfad.packet_filter_list[0].filter[0] != 0xA5 ||
       tfad.packet_filter_list[0].filter[1] != 0x5A || tfad.parameter_list[0].id != 0xAB ||
       tfad.parameter_list[0].parameter_size != 2 ||
       tfad.parameter_list[0].parameter[0] != 0xA5 ||
       tfad.parameter_list[0].parameter[1] != 0x5A ||
       tfad.parameter_list[1].id != 0xCD || tfad.parameter_list[1].parameter_size != 2 ||
       tfad.parameter_list[1].parameter[0] != 0x12 ||
       tfad.parameter_list[1].parameter[1] != 0x34)
        return -1;
    return 0;
}

int traffic_flow_template_test(void)
{
    LIBLTE_MME_TRAFFIC_FLOW_AGGREGATE_DESCRIPTION_STRUCT tft;
    tft.packet_filter_list_size = 1;
    tft.parameter_list_size = 2;
    tft.tft_op_code = LIBLTE_MME_TFT_OPERATION_CODE_DELETE_PACKET_FILTERS_FROM_EXISTING_TFT;
    tft.packet_filter_list[0].dir = LIBLTE_MME_TFT_PACKET_FILTER_DIRECTION_DOWNLINK_ONLY;
    tft.packet_filter_list[0].id = 0x5;
    tft.packet_filter_list[0].eval_precedence = 0x5A;
    tft.packet_filter_list[0].filter_size = 2;
    tft.packet_filter_list[0].filter[0] = 0xA5;
    tft.packet_filter_list[0].filter[1] = 0x5A;
    tft.parameter_list[0].id = 0xAB;
    tft.parameter_list[0].parameter_size = 2;
    tft.parameter_list[0].parameter[0] = 0xA5;
    tft.parameter_list[0].parameter[1] = 0x5A;
    tft.parameter_list[1].id = 0xCD;
    tft.parameter_list[1].parameter_size = 2;
    tft.parameter_list[1].parameter[0] = 0x12;
    tft.parameter_list[1].parameter[1] = 0x34;
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_traffic_flow_template_ie(&tft, &ie_ptr))
        return -1;
    if(11 != (ie_ptr - msg.msg))
        return -1;
    if(0x0A != msg.msg[0] || 0xB1 != msg.msg[1] || 0x15 != msg.msg[2] || 0xAB != msg.msg[3] ||
       0x02 != msg.msg[4] || 0xA5 != msg.msg[5] || 0x5A != msg.msg[6] || 0xCD != msg.msg[7] ||
       0x02 != msg.msg[8] || 0x12 != msg.msg[9] || 0x34 != msg.msg[10])
        return -1;
    ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_traffic_flow_template_ie(&ie_ptr, &tft))
        return -1;
    if(tft.packet_filter_list_size != 1 || tft.parameter_list_size != 2 ||
       tft.tft_op_code != LIBLTE_MME_TFT_OPERATION_CODE_DELETE_PACKET_FILTERS_FROM_EXISTING_TFT ||
       tft.packet_filter_list[0].dir != LIBLTE_MME_TFT_PACKET_FILTER_DIRECTION_DOWNLINK_ONLY ||
       tft.packet_filter_list[0].id != 0x5 ||
       tft.packet_filter_list[0].eval_precedence != 0x5A ||
       tft.packet_filter_list[0].filter_size != 2 ||
       tft.packet_filter_list[0].filter[0] != 0xA5 ||
       tft.packet_filter_list[0].filter[1] != 0x5A || tft.parameter_list[0].id != 0xAB ||
       tft.parameter_list[0].parameter_size != 2 ||
       tft.parameter_list[0].parameter[0] != 0xA5 ||
       tft.parameter_list[0].parameter[1] != 0x5A ||
       tft.parameter_list[1].id != 0xCD || tft.parameter_list[1].parameter_size != 2 ||
       tft.parameter_list[1].parameter[0] != 0x12 ||
       tft.parameter_list[1].parameter[1] != 0x34)
        return -1;
    return 0;
}

int transaction_identifier_test(void)
{
    LIBLTE_MME_TRANSACTION_IDENTIFIER_STRUCT trans_id;
    trans_id.ti_flag = LIBLTE_MME_TI_FLAG_SENT_TO_ORIGINATOR;
    trans_id.tio = LIBLTE_MME_TI_VALUE_IS_GIVEN_BY_TIE;
    trans_id.tie = 0x5A;
    LIBLTE_BYTE_MSG_STRUCT msg;
    uint8 *ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_transaction_identifier_ie(&trans_id, &ie_ptr))
        return -1;
    if(3 != (ie_ptr - msg.msg))
        return -1;
    if(0x02 != msg.msg[0] || 0xF0 != msg.msg[1] || 0xDA != msg.msg[2])
        return -1;
    ie_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_transaction_identifier_ie(&ie_ptr, &trans_id))
        return -1;
    if(trans_id.ti_flag != LIBLTE_MME_TI_FLAG_SENT_TO_ORIGINATOR ||
       trans_id.tio != LIBLTE_MME_TI_VALUE_IS_GIVEN_BY_TIE || trans_id.tie != 0x5A)
        return -1;
    return 0;
}

int parse_msg_header_test(void)
{
    LIBLTE_BYTE_MSG_STRUCT msg;
    msg.msg[0] = LIBLTE_MME_PD_EPS_MOBILITY_MANAGEMENT;
    msg.msg[1] = LIBLTE_MME_MSG_TYPE_ATTACH_REQUEST;
    uint8 pd;
    uint8 msg_type;
    if(LIBLTE_SUCCESS != liblte_mme_parse_msg_header(&msg, &pd, &msg_type))
        return -1;
    if(pd != LIBLTE_MME_PD_EPS_MOBILITY_MANAGEMENT ||
       msg_type != LIBLTE_MME_MSG_TYPE_ATTACH_REQUEST)
        return -1;
    return 0;
}

int security_protected_nas_msg_test(void)
{
    LIBLTE_BYTE_MSG_STRUCT msg;
    msg.N_bytes = 4;
    for(uint32 i=0; i<msg.N_bytes; i++)
        msg.msg[i] = i;
    uint8 key[32];
    for(uint32 i=0; i<32; i++)
        key[i] = i;
    LIBLTE_BYTE_MSG_STRUCT sec_msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_security_protected_nas_msg(&msg,
                                                                    LIBLTE_MME_SECURITY_HDR_TYPE_PLAIN_NAS,
                                                                    key,
                                                                    0,
                                                                    LIBLTE_SECURITY_DIRECTION_DOWNLINK,
                                                                    &sec_msg))
        return -1;
    if(sec_msg.N_bytes != 4)
        return -1;
    for(uint32 i=0; i<sec_msg.N_bytes; i++)
        if(sec_msg.msg[i] != i)
            return -1;
    if(LIBLTE_SUCCESS != liblte_mme_pack_security_protected_nas_msg(&msg,
                                                                    LIBLTE_MME_SECURITY_HDR_TYPE_INTEGRITY_AND_CIPHERED,
                                                                    key,
                                                                    0x12,
                                                                    LIBLTE_SECURITY_DIRECTION_DOWNLINK,
                                                                    &sec_msg))
        return -1;
    if(sec_msg.N_bytes != 10)
        return -1;
    if(sec_msg.msg[0] != 0x27 || sec_msg.msg[1] != 0xD6 || sec_msg.msg[2] != 0x85 ||
       sec_msg.msg[3] != 0x46 || sec_msg.msg[4] != 0x27 || sec_msg.msg[5] != 0x12)
        return -1;
    for(uint32 i=0; i<4; i++)
        if(sec_msg.msg[6+i] != i)
            return -1;
    return 0;
}

int attach_accept_msg_test(void)
{
    LIBLTE_MME_ATTACH_ACCEPT_MSG_STRUCT attach_accept;
    attach_accept.eps_attach_result = LIBLTE_MME_EPS_ATTACH_RESULT_COMBINED_EPS_IMSI_ATTACH;
    attach_accept.t3412.unit = LIBLTE_MME_GPRS_TIMER_UNIT_1_MINUTE;
    attach_accept.t3412.value = 2;
    attach_accept.tai_list.N_tais = 1;
    std::vector<MCC_MNC_Digit> mcc(3);
    mcc[0].SetValue(1);
    mcc[1].SetValue(2);
    mcc[2].SetValue(3);
    attach_accept.tai_list.tai[0].mcc.SetValue(mcc);
    std::vector<MCC_MNC_Digit> mnc2(2);
    mnc2[0].SetValue(4);
    mnc2[1].SetValue(5);
    attach_accept.tai_list.tai[0].mnc.SetValue(mnc2);
    attach_accept.tai_list.tai[0].tac = 0xABCD;
    attach_accept.esm_msg.N_bytes = 2;
    attach_accept.esm_msg.msg[0] = 0xA5;
    attach_accept.esm_msg.msg[1] = 0x5A;
    attach_accept.guti.type_of_id = LIBLTE_MME_EPS_MOBILE_ID_TYPE_GUTI;
    attach_accept.guti.guti.m_tmsi = 0x12345678;
    attach_accept.guti.guti.mcc.SetValue(mcc);
    attach_accept.guti.guti.mnc.SetValue(mnc2);
    attach_accept.guti.guti.mme_group_id = 0xABCD;
    attach_accept.guti.guti.mme_code = 0xEF;
    attach_accept.ms_id.type_of_id = LIBLTE_MME_MOBILE_ID_TYPE_TMSI;
    attach_accept.ms_id.tmsi = 0x12345678;
    attach_accept.t3402.unit = LIBLTE_MME_GPRS_TIMER_UNIT_1_MINUTE;
    attach_accept.t3402.value = 4;
    attach_accept.equivalent_plmns.N_plmns = 1;
    attach_accept.equivalent_plmns.mcc[0].SetValue(mcc);
    std::vector<MCC_MNC_Digit> mnc3(3);
    mnc3[0].SetValue(4);
    mnc3[1].SetValue(5);
    mnc3[2].SetValue(6);
    attach_accept.equivalent_plmns.mnc[0].SetValue(mnc3);
    attach_accept.eps_network_feature_support.cs_lcs = LIBLTE_MME_CS_LCS_SUPPORTED;
    attach_accept.eps_network_feature_support.esrps = false;
    attach_accept.eps_network_feature_support.epc_lcs = true;
    attach_accept.eps_network_feature_support.emc_bs = false;
    attach_accept.eps_network_feature_support.ims_vops = true;
    attach_accept.t3412_ext.unit = LIBLTE_MME_GPRS_TIMER_3_UNIT_1_HOUR;
    attach_accept.t3412_ext.value = 1;
    attach_accept.guti_present = true;
    attach_accept.lai_present = false;
    attach_accept.ms_id_present = true;
    attach_accept.emm_cause_present = false;
    attach_accept.t3402_present = true;
    attach_accept.t3423_present = false;
    attach_accept.equivalent_plmns_present = true;
    attach_accept.emerg_num_list_present = false;
    attach_accept.eps_network_feature_support_present = true;
    attach_accept.additional_update_result_present = false;
    attach_accept.t3412_ext_present = true;
    uint8 key[32];
    for(uint32 i=0;i<32; i++)
        key[i] = i;
    LIBLTE_BYTE_MSG_STRUCT sec_msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_attach_accept_msg(&attach_accept,
                                                           LIBLTE_MME_SECURITY_HDR_TYPE_INTEGRITY_AND_CIPHERED,
                                                           key,
                                                           0x12,
                                                           LIBLTE_SECURITY_DIRECTION_DOWNLINK,
                                                           &sec_msg))
        return -1;
    if(54 != sec_msg.N_bytes)
        return -1;
    if(0x27 != sec_msg.msg[0] || 0x41 != sec_msg.msg[1] || 0x54 != sec_msg.msg[2] ||
       0x30 != sec_msg.msg[3] || 0x97 != sec_msg.msg[4] || 0x12 != sec_msg.msg[5] ||
       0x07 != sec_msg.msg[6] || 0x42 != sec_msg.msg[7] || 0x02 != sec_msg.msg[8] ||
       0x22 != sec_msg.msg[9] || 0x06 != sec_msg.msg[10] || 0x00 != sec_msg.msg[11] ||
       0x21 != sec_msg.msg[12] || 0xF3 != sec_msg.msg[13] || 0x54 != sec_msg.msg[14] ||
       0xAB != sec_msg.msg[15] || 0xCD != sec_msg.msg[16] || 0x00 != sec_msg.msg[17] ||
       0x02 != sec_msg.msg[18] || 0xA5 != sec_msg.msg[19] || 0x5A != sec_msg.msg[20] ||
       0x50 != sec_msg.msg[21] || 0x0B != sec_msg.msg[22] || 0xF6 != sec_msg.msg[23] ||
       0x21 != sec_msg.msg[24] || 0xF3 != sec_msg.msg[25] || 0x54 != sec_msg.msg[26] ||
       0xAB != sec_msg.msg[27] || 0xCD != sec_msg.msg[28] || 0xEF != sec_msg.msg[29] ||
       0x12 != sec_msg.msg[30] || 0x34 != sec_msg.msg[31] || 0x56 != sec_msg.msg[32] ||
       0x78 != sec_msg.msg[33] || 0x23 != sec_msg.msg[34] || 0x05 != sec_msg.msg[35] ||
       0xF4 != sec_msg.msg[36] || 0x12 != sec_msg.msg[37] || 0x34 != sec_msg.msg[38] ||
       0x56 != sec_msg.msg[39] || 0x78 != sec_msg.msg[40] || 0x17 != sec_msg.msg[41] ||
       0x24 != sec_msg.msg[42] || 0x4A != sec_msg.msg[43] || 0x03 != sec_msg.msg[44] ||
       0x21 != sec_msg.msg[45] || 0x63 != sec_msg.msg[46] || 0x54 != sec_msg.msg[47] ||
       0x64 != sec_msg.msg[48] || 0x01 != sec_msg.msg[49] || 0x15 != sec_msg.msg[50] ||
       0x5E != sec_msg.msg[51] || 0x01 != sec_msg.msg[52] || 0x21 != sec_msg.msg[53])
        return -1;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_attach_accept_msg(&sec_msg, &attach_accept))
        return -1;
    if(attach_accept.eps_attach_result != LIBLTE_MME_EPS_ATTACH_RESULT_COMBINED_EPS_IMSI_ATTACH ||
       attach_accept.t3412.unit != LIBLTE_MME_GPRS_TIMER_UNIT_1_MINUTE ||
       attach_accept.t3412.value != 2 || attach_accept.tai_list.N_tais != 1 ||
       attach_accept.tai_list.tai[0].mcc.Value()[0].Value() != 1 ||
       attach_accept.tai_list.tai[0].mcc.Value()[1].Value() != 2 ||
       attach_accept.tai_list.tai[0].mcc.Value()[2].Value() != 3 ||
       attach_accept.tai_list.tai[0].mnc.Value()[0].Value() != 4 ||
       attach_accept.tai_list.tai[0].mnc.Value()[1].Value() != 5 ||
       attach_accept.tai_list.tai[0].tac != 0xABCD || attach_accept.esm_msg.N_bytes != 2 ||
       attach_accept.esm_msg.msg[0] != 0xA5 || attach_accept.esm_msg.msg[1] != 0x5A ||
       attach_accept.guti.type_of_id != LIBLTE_MME_EPS_MOBILE_ID_TYPE_GUTI ||
       attach_accept.guti.guti.m_tmsi != 0x12345678 ||
       attach_accept.guti.guti.mcc.Value()[0].Value() != 1 ||
       attach_accept.guti.guti.mcc.Value()[1].Value() != 2 ||
       attach_accept.guti.guti.mcc.Value()[2].Value() != 3 ||
       attach_accept.guti.guti.mnc.Value()[0].Value() != 4 ||
       attach_accept.guti.guti.mnc.Value()[1].Value() != 5 ||
       attach_accept.guti.guti.mme_group_id != 0xABCD ||
       attach_accept.guti.guti.mme_code != 0xEF ||
       attach_accept.ms_id.type_of_id != LIBLTE_MME_MOBILE_ID_TYPE_TMSI ||
       attach_accept.ms_id.tmsi != 0x12345678 ||
       attach_accept.t3402.unit != LIBLTE_MME_GPRS_TIMER_UNIT_1_MINUTE ||
       attach_accept.t3402.value != 4 || attach_accept.equivalent_plmns.N_plmns != 1 ||
       attach_accept.equivalent_plmns.mcc[0].Value()[0].Value() != 1 ||
       attach_accept.equivalent_plmns.mcc[0].Value()[1].Value() != 2 ||
       attach_accept.equivalent_plmns.mcc[0].Value()[2].Value() != 3 ||
       attach_accept.equivalent_plmns.mnc[0].Value()[0].Value() != 4 ||
       attach_accept.equivalent_plmns.mnc[0].Value()[1].Value() != 5 ||
       attach_accept.equivalent_plmns.mnc[0].Value()[2].Value() != 6 ||
       attach_accept.eps_network_feature_support.cs_lcs != LIBLTE_MME_CS_LCS_SUPPORTED ||
       attach_accept.eps_network_feature_support.esrps ||
       !attach_accept.eps_network_feature_support.epc_lcs ||
       attach_accept.eps_network_feature_support.emc_bs ||
       !attach_accept.eps_network_feature_support.ims_vops ||
       attach_accept.t3412_ext.unit != LIBLTE_MME_GPRS_TIMER_3_UNIT_1_HOUR ||
       attach_accept.t3412_ext.value != 1 || !attach_accept.guti_present ||
       attach_accept.lai_present || !attach_accept.ms_id_present ||
       attach_accept.emm_cause_present || !attach_accept.t3402_present ||
       attach_accept.t3423_present || !attach_accept.equivalent_plmns_present ||
       attach_accept.emerg_num_list_present ||
       !attach_accept.eps_network_feature_support_present ||
       attach_accept.additional_update_result_present || !attach_accept.t3412_ext_present)
        return -1;
    return 0;
}

int attach_complete_msg_test(void)
{
    LIBLTE_MME_ATTACH_COMPLETE_MSG_STRUCT attach_comp;
    attach_comp.esm_msg.N_bytes = 2;
    attach_comp.esm_msg.msg[0] = 0xA5;
    attach_comp.esm_msg.msg[1] = 0x5A;
    uint8 key[32];
    for(uint32 i=0;i<32; i++)
        key[i] = i;
    LIBLTE_BYTE_MSG_STRUCT sec_msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_attach_complete_msg(&attach_comp,
                                                             LIBLTE_MME_SECURITY_HDR_TYPE_INTEGRITY_AND_CIPHERED,
                                                             key,
                                                             0x12,
                                                             LIBLTE_SECURITY_DIRECTION_DOWNLINK,
                                                             &sec_msg))
        return -1;
    if(12 != sec_msg.N_bytes)
        return -1;
    if(0x27 != sec_msg.msg[0] || 0x66 != sec_msg.msg[1] || 0xAD != sec_msg.msg[2] ||
       0x42 != sec_msg.msg[3] || 0x82 != sec_msg.msg[4] || 0x12 != sec_msg.msg[5] ||
       0x07 != sec_msg.msg[6] || 0x43 != sec_msg.msg[7] || 0x00 != sec_msg.msg[8] ||
       0x02 != sec_msg.msg[9] || 0xA5 != sec_msg.msg[10] || 0x5A != sec_msg.msg[11])
        return -1;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_attach_complete_msg(&sec_msg, &attach_comp))
        return -1;
    if(attach_comp.esm_msg.N_bytes != 2 || attach_comp.esm_msg.msg[0] != 0xA5 ||
       attach_comp.esm_msg.msg[1] != 0x5A)
        return -1;
    return 0;
}

int attach_reject_msg_test(void)
{
    LIBLTE_MME_ATTACH_REJECT_MSG_STRUCT attach_rej;
    attach_rej.esm_msg.N_bytes = 2;
    attach_rej.esm_msg.msg[0] = 0xA5;
    attach_rej.esm_msg.msg[1] = 0x5A;
    attach_rej.emm_cause = LIBLTE_MME_EMM_CAUSE_IMSI_UNKNOWN_IN_HSS;
    attach_rej.esm_msg_present = true;
    attach_rej.t3446_value_present = false;
    LIBLTE_BYTE_MSG_STRUCT msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_attach_reject_msg(&attach_rej, &msg))
        return -1;
    if(8 != msg.N_bytes)
        return -1;
    if(0x07 != msg.msg[0] || 0x44 != msg.msg[1] || 0x02 != msg.msg[2] ||
       0x78 != msg.msg[3] || 0x00 != msg.msg[4] || 0x02 != msg.msg[5] ||
       0xA5 != msg.msg[6] || 0x5A != msg.msg[7])
        return -1;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_attach_reject_msg(&msg, &attach_rej))
        return -1;
    if(attach_rej.esm_msg.N_bytes != 2 || attach_rej.esm_msg.msg[0] != 0xA5 ||
       attach_rej.esm_msg.msg[1] != 0x5A ||
       attach_rej.emm_cause != LIBLTE_MME_EMM_CAUSE_IMSI_UNKNOWN_IN_HSS ||
       !attach_rej.esm_msg_present || attach_rej.t3446_value_present)
        return -1;
    return 0;
}

int attach_request_msg_test(void)
{
    LIBLTE_MME_ATTACH_REQUEST_MSG_STRUCT attach_req;
    attach_req.nas_ksi.tsc_flag = LIBLTE_MME_TYPE_OF_SECURITY_CONTEXT_FLAG_MAPPED;
    attach_req.nas_ksi.nas_ksi = 0x1;
    attach_req.eps_mobile_id.type_of_id = LIBLTE_MME_EPS_MOBILE_ID_TYPE_GUTI;
    attach_req.eps_mobile_id.guti.m_tmsi = 0x12345678;
    std::vector<MCC_MNC_Digit> mcc(3);
    mcc[0].SetValue(1);
    mcc[1].SetValue(2);
    mcc[2].SetValue(3);
    attach_req.eps_mobile_id.guti.mcc.SetValue(mcc);
    std::vector<MCC_MNC_Digit> mnc(3);
    mnc[0].SetValue(4);
    mnc[1].SetValue(5);
    mnc[2].SetValue(6);
    attach_req.eps_mobile_id.guti.mnc.SetValue(mnc);
    attach_req.eps_mobile_id.guti.mme_group_id = 0xABCD;
    attach_req.eps_mobile_id.guti.mme_code = 0xEF;
    for(uint32 i=0; i<8; i++)
    {
        attach_req.ue_network_cap.eea[i] = i%2;
        attach_req.ue_network_cap.eia[i] = i%2;
        attach_req.ue_network_cap.uea[i] = i%2;
        attach_req.ue_network_cap.uia[i] = i%2;
    }
    attach_req.ue_network_cap.uea_present = true;
    attach_req.ue_network_cap.ucs2 = false;
    attach_req.ue_network_cap.ucs2_present = true;
    attach_req.ue_network_cap.uia_present = true;
    attach_req.ue_network_cap.lpp = false;
    attach_req.ue_network_cap.lpp_present = true;
    attach_req.ue_network_cap.lcs = true;
    attach_req.ue_network_cap.lcs_present = true;
    attach_req.ue_network_cap.onexsrvcc = false;
    attach_req.ue_network_cap.onexsrvcc_present = true;
    attach_req.ue_network_cap.nf = false;
    attach_req.ue_network_cap.nf_present = true;
    attach_req.esm_msg.N_bytes = 2;
    attach_req.esm_msg.msg[0] = 0xA5;
    attach_req.esm_msg.msg[1] = 0x5A;
    attach_req.additional_guti.type_of_id = LIBLTE_MME_EPS_MOBILE_ID_TYPE_GUTI;
    attach_req.additional_guti.guti.m_tmsi = 0x12345678;
    attach_req.additional_guti.guti.mcc.SetValue(mcc);
    attach_req.additional_guti.guti.mnc.SetValue(mnc);
    attach_req.additional_guti.guti.mme_group_id = 0xABCD;
    attach_req.additional_guti.guti.mme_code = 0xEF;
    attach_req.drx_param.non_drx_timer = LIBLTE_MME_NON_DRX_TIMER_MAX_8S_NON_DRX_MODE;
    attach_req.drx_param.split_pg_cycle_code = 0xA5;
    attach_req.drx_param.drx_cycle_len_coeff_and_value = 0x6;
    attach_req.drx_param.split_on_ccch = false;
    mcc[0].SetValue(2);
    mcc[1].SetValue(3);
    mcc[2].SetValue(4);
    attach_req.old_lai.mcc.SetValue(mcc);
    mnc[0].SetValue(5);
    mnc[1].SetValue(6);
    mnc[2].SetValue(7);
    attach_req.old_lai.mnc.SetValue(mnc);
    attach_req.old_lai.lac = 0x1234;
    attach_req.ms_cm2.rev_lev = LIBLTE_MME_REVISION_LEVEL_R99;
    attach_req.ms_cm2.rf_power_cap = LIBLTE_MME_RF_POWER_CAPABILITY_CLASS_3;
    attach_req.ms_cm2.ss_screen_ind = LIBLTE_MME_SS_SCREEN_INDICATOR_2;
    attach_req.ms_cm2.es_ind = false;
    attach_req.ms_cm2.a5_1 = true;
    attach_req.ms_cm2.ps_cap = false;
    attach_req.ms_cm2.sm_cap = true;
    attach_req.ms_cm2.vbs = false;
    attach_req.ms_cm2.vgcs = true;
    attach_req.ms_cm2.fc = false;
    attach_req.ms_cm2.cm3 = true;
    attach_req.ms_cm2.lcsva_cap = false;
    attach_req.ms_cm2.ucs2 = true;
    attach_req.ms_cm2.solsa = false;
    attach_req.ms_cm2.cmsp = true;
    attach_req.ms_cm2.a5_3 = false;
    attach_req.ms_cm2.a5_2 = true;
    attach_req.supported_codecs.N_supported_codecs = 2;
    attach_req.supported_codecs.supported_codec[0].sys_id = 0xA5;
    attach_req.supported_codecs.supported_codec[0].codec_bitmap = 0x1234;
    attach_req.supported_codecs.supported_codec[1].sys_id = 0x5A;
    attach_req.supported_codecs.supported_codec[1].codec_bitmap = 0x5678;
    attach_req.voice_domain_pref_and_ue_usage_setting.ue_usage_setting = LIBLTE_MME_UE_USAGE_SETTING_DATA_CENTRIC;
    attach_req.voice_domain_pref_and_ue_usage_setting.voice_domain_pref = LIBLTE_MME_VOICE_DOMAIN_PREF_PS_ONLY;
    attach_req.old_guti_type = LIBLTE_MME_GUTI_TYPE_MAPPED;
    attach_req.eps_attach_type = LIBLTE_MME_EPS_ATTACH_TYPE_COMBINED_EPS_IMSI_ATTACH;
    attach_req.old_p_tmsi_signature_present = false;
    attach_req.additional_guti_present = true;
    attach_req.last_visited_registered_tai_present = false;
    attach_req.drx_param_present = true;
    attach_req.ms_network_cap_present = false;
    attach_req.old_lai_present = true;
    attach_req.tmsi_status_present = false;
    attach_req.ms_cm2_present = true;
    attach_req.ms_cm3_present = false;
    attach_req.supported_codecs_present = true;
    attach_req.additional_update_type_present = false;
    attach_req.voice_domain_pref_and_ue_usage_setting_present = true;
    attach_req.device_properties_present = false;
    attach_req.old_guti_type_present = true;
    LIBLTE_BYTE_MSG_STRUCT msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_attach_request_msg(&attach_req, &msg))
        return -1;
    if(66 != msg.N_bytes)
        return -1;
    if(0x07 != msg.msg[0] || 0x41 != msg.msg[1] || 0x92 != msg.msg[2] ||
       0x0B != msg.msg[3] || 0xF6 != msg.msg[4] || 0x21 != msg.msg[5] ||
       0x63 != msg.msg[6] || 0x54 != msg.msg[7] || 0xAB != msg.msg[8] ||
       0xCD != msg.msg[9] || 0xEF != msg.msg[10] || 0x12 != msg.msg[11] ||
       0x34 != msg.msg[12] || 0x56 != msg.msg[13] || 0x78 != msg.msg[14] ||
       0x05 != msg.msg[15] || 0x55 != msg.msg[16] || 0x55 != msg.msg[17] ||
       0x55 != msg.msg[18] || 0x55 != msg.msg[19] || 0x04 != msg.msg[20] ||
       0x00 != msg.msg[21] || 0x02 != msg.msg[22] || 0xA5 != msg.msg[23] ||
       0x5A != msg.msg[24] || 0x50 != msg.msg[25] || 0x0B != msg.msg[26] ||
       0xF6 != msg.msg[27] || 0x21 != msg.msg[28] || 0x63 != msg.msg[29] ||
       0x54 != msg.msg[30] || 0xAB != msg.msg[31] || 0xCD != msg.msg[32] ||
       0xEF != msg.msg[33] || 0x12 != msg.msg[34] || 0x34 != msg.msg[35] ||
       0x56 != msg.msg[36] || 0x78 != msg.msg[37] || 0x5C != msg.msg[38] ||
       0xA5 != msg.msg[39] || 0x64 != msg.msg[40] || 0x13 != msg.msg[41] ||
       0x32 != msg.msg[42] || 0x74 != msg.msg[43] || 0x65 != msg.msg[44] ||
       0x12 != msg.msg[45] || 0x34 != msg.msg[46] || 0x11 != msg.msg[47] ||
       0x03 != msg.msg[48] || 0x4A != msg.msg[49] || 0x2A != msg.msg[50] ||
       0x95 != msg.msg[51] || 0x40 != msg.msg[52] || 0x08 != msg.msg[53] ||
       0xA5 != msg.msg[54] || 0x02 != msg.msg[55] || 0x12 != msg.msg[56] ||
       0x34 != msg.msg[57] || 0x5A != msg.msg[58] || 0x02 != msg.msg[59] ||
       0x56 != msg.msg[60] || 0x78 != msg.msg[61] || 0x5D != msg.msg[62] ||
       0x01 != msg.msg[63] || 0x05 != msg.msg[64] || 0xE1 != msg.msg[65])
        return -1;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_attach_request_msg(&msg, &attach_req))
        return -1;
    if(attach_req.nas_ksi.tsc_flag != LIBLTE_MME_TYPE_OF_SECURITY_CONTEXT_FLAG_MAPPED ||
       attach_req.nas_ksi.nas_ksi != 0x1 ||
       attach_req.eps_mobile_id.type_of_id != LIBLTE_MME_EPS_MOBILE_ID_TYPE_GUTI ||
       attach_req.eps_mobile_id.guti.m_tmsi != 0x12345678 ||
       attach_req.eps_mobile_id.guti.mcc.Value()[0].Value() != 1 ||
       attach_req.eps_mobile_id.guti.mcc.Value()[1].Value() != 2 ||
       attach_req.eps_mobile_id.guti.mcc.Value()[2].Value() != 3 ||
       attach_req.eps_mobile_id.guti.mnc.Value()[0].Value() != 4 ||
       attach_req.eps_mobile_id.guti.mnc.Value()[1].Value() != 5 ||
       attach_req.eps_mobile_id.guti.mnc.Value()[2].Value() != 6 ||
       attach_req.eps_mobile_id.guti.mme_group_id != 0xABCD ||
       attach_req.eps_mobile_id.guti.mme_code != 0xEF)
        return -1;
    for(uint32 i=0; i<8; i++)
        if(attach_req.ue_network_cap.eea[i] != i%2 || attach_req.ue_network_cap.eia[i] != i%2 ||
           attach_req.ue_network_cap.uea[i] != i%2 || attach_req.ue_network_cap.uia[i] != i%2)
            return -1;
    if(!attach_req.ue_network_cap.uea_present || attach_req.ue_network_cap.ucs2 ||
       !attach_req.ue_network_cap.ucs2_present || !attach_req.ue_network_cap.uia_present ||
       attach_req.ue_network_cap.lpp || !attach_req.ue_network_cap.lpp_present ||
       !attach_req.ue_network_cap.lcs || !attach_req.ue_network_cap.lcs_present ||
       attach_req.ue_network_cap.onexsrvcc || !attach_req.ue_network_cap.onexsrvcc_present ||
       attach_req.ue_network_cap.nf || !attach_req.ue_network_cap.nf_present ||
       attach_req.esm_msg.N_bytes != 2 || attach_req.esm_msg.msg[0] != 0xA5 ||
       attach_req.esm_msg.msg[1] != 0x5A ||
       attach_req.additional_guti.type_of_id != LIBLTE_MME_EPS_MOBILE_ID_TYPE_GUTI ||
       attach_req.additional_guti.guti.m_tmsi !=0x12345678 ||
       attach_req.additional_guti.guti.mcc.Value()[0].Value() != 1 ||
       attach_req.additional_guti.guti.mcc.Value()[1].Value() != 2 ||
       attach_req.additional_guti.guti.mcc.Value()[2].Value() != 3 ||
       attach_req.additional_guti.guti.mnc.Value()[0].Value() != 4 ||
       attach_req.additional_guti.guti.mnc.Value()[1].Value() != 5 ||
       attach_req.additional_guti.guti.mnc.Value()[2].Value() != 6 ||
       attach_req.additional_guti.guti.mme_group_id != 0xABCD ||
       attach_req.additional_guti.guti.mme_code != 0xEF ||
       attach_req.drx_param.non_drx_timer != LIBLTE_MME_NON_DRX_TIMER_MAX_8S_NON_DRX_MODE ||
       attach_req.drx_param.split_pg_cycle_code != 0xA5 ||
       attach_req.drx_param.drx_cycle_len_coeff_and_value != 0x6 ||
       attach_req.drx_param.split_on_ccch ||
       attach_req.old_lai.mcc.Value()[0].Value() != 2 ||
       attach_req.old_lai.mcc.Value()[1].Value() != 3 ||
       attach_req.old_lai.mcc.Value()[2].Value() != 4 ||
       attach_req.old_lai.mnc.Value()[0].Value() != 5 ||
       attach_req.old_lai.mnc.Value()[1].Value() != 6 ||
       attach_req.old_lai.mnc.Value()[2].Value() != 7 || attach_req.old_lai.lac != 0x1234 ||
       attach_req.ms_cm2.rev_lev != LIBLTE_MME_REVISION_LEVEL_R99 ||
       attach_req.ms_cm2.rf_power_cap != LIBLTE_MME_RF_POWER_CAPABILITY_CLASS_3 ||
       attach_req.ms_cm2.ss_screen_ind != LIBLTE_MME_SS_SCREEN_INDICATOR_2 ||
       attach_req.ms_cm2.es_ind || !attach_req.ms_cm2.a5_1 || attach_req.ms_cm2.ps_cap ||
       !attach_req.ms_cm2.sm_cap || attach_req.ms_cm2.vbs || !attach_req.ms_cm2.vgcs ||
       attach_req.ms_cm2.fc || !attach_req.ms_cm2.cm3 || attach_req.ms_cm2.lcsva_cap ||
       !attach_req.ms_cm2.ucs2 || attach_req.ms_cm2.solsa || !attach_req.ms_cm2.cmsp ||
       attach_req.ms_cm2.a5_3 || !attach_req.ms_cm2.a5_2 ||
       attach_req.supported_codecs.N_supported_codecs != 2 ||
       attach_req.supported_codecs.supported_codec[0].sys_id != 0xA5 ||
       attach_req.supported_codecs.supported_codec[0].codec_bitmap != 0x1234 ||
       attach_req.supported_codecs.supported_codec[1].sys_id != 0x5A ||
       attach_req.supported_codecs.supported_codec[1].codec_bitmap != 0x5678 ||
       attach_req.voice_domain_pref_and_ue_usage_setting.ue_usage_setting != LIBLTE_MME_UE_USAGE_SETTING_DATA_CENTRIC ||
       attach_req.voice_domain_pref_and_ue_usage_setting.voice_domain_pref != LIBLTE_MME_VOICE_DOMAIN_PREF_PS_ONLY ||
       attach_req.old_guti_type != LIBLTE_MME_GUTI_TYPE_MAPPED ||
       attach_req.eps_attach_type != LIBLTE_MME_EPS_ATTACH_TYPE_COMBINED_EPS_IMSI_ATTACH ||
       attach_req.old_p_tmsi_signature_present || !attach_req.additional_guti_present ||
       attach_req.last_visited_registered_tai_present || !attach_req.drx_param_present ||
       attach_req.ms_network_cap_present || !attach_req.old_lai_present ||
       attach_req.tmsi_status_present || !attach_req.ms_cm2_present ||
       attach_req.ms_cm3_present || !attach_req.supported_codecs_present ||
       attach_req.additional_update_type_present ||
       !attach_req.voice_domain_pref_and_ue_usage_setting_present ||
       attach_req.device_properties_present || !attach_req.old_guti_type_present)
        return -1;
    return 0;
}

int authentication_failure_msg_test(void)
{
    LIBLTE_MME_AUTHENTICATION_FAILURE_MSG_STRUCT auth_fail;
    auth_fail.emm_cause = LIBLTE_MME_EMM_CAUSE_MAC_FAILURE;
    auth_fail.auth_fail_param_present = false;
    LIBLTE_BYTE_MSG_STRUCT msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_authentication_failure_msg(&auth_fail, &msg))
        return -1;
    if(3 != msg.N_bytes)
        return -1;
    if(0x07 != msg.msg[0] || 0x5C != msg.msg[1] || 0x14 != msg.msg[2])
        return -1;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_authentication_failure_msg(&msg, &auth_fail))
        return -1;
    if(auth_fail.emm_cause != LIBLTE_MME_EMM_CAUSE_MAC_FAILURE ||
       auth_fail.auth_fail_param_present)
        return -1;
    return 0;
}

int authentication_reject_msg_test(void)
{
    LIBLTE_MME_AUTHENTICATION_REJECT_MSG_STRUCT auth_reject;
    LIBLTE_BYTE_MSG_STRUCT msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_authentication_reject_msg(&auth_reject, &msg))
        return -1;
    if(2 != msg.N_bytes)
        return -1;
    if(0x07 != msg.msg[0] || 0x54 != msg.msg[1])
        return -1;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_authentication_reject_msg(&msg, &auth_reject))
        return -1;
    return 0;
}

int authentication_request_msg_test(void)
{
    LIBLTE_MME_AUTHENTICATION_REQUEST_MSG_STRUCT auth_req;
    auth_req.nas_ksi.tsc_flag = LIBLTE_MME_TYPE_OF_SECURITY_CONTEXT_FLAG_MAPPED;
    auth_req.nas_ksi.nas_ksi = 0x1;
    for(uint32 i=0; i<16; i++)
    {
        auth_req.autn[i] = i;
        auth_req.rand[i] = i;
    }
    LIBLTE_BYTE_MSG_STRUCT msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_authentication_request_msg(&auth_req, &msg))
        return -1;
    if(36 != msg.N_bytes)
        return -1;
    if(0x07 != msg.msg[0] || 0x52 != msg.msg[1] || 0x09 != msg.msg[2] ||
       0x00 != msg.msg[3] || 0x01 != msg.msg[4] || 0x02 != msg.msg[5] ||
       0x03 != msg.msg[6] || 0x04 != msg.msg[7] || 0x05 != msg.msg[8] ||
       0x06 != msg.msg[9] || 0x07 != msg.msg[10] || 0x08 != msg.msg[11] ||
       0x09 != msg.msg[12] || 0x0A != msg.msg[13] || 0x0B != msg.msg[14] ||
       0x0C != msg.msg[15] || 0x0D != msg.msg[16] || 0x0E != msg.msg[17] ||
       0x0F != msg.msg[18] || 0x10 != msg.msg[19] || 0x00 != msg.msg[20] ||
       0x01 != msg.msg[21] || 0x02 != msg.msg[22] || 0x03 != msg.msg[23] ||
       0x04 != msg.msg[24] || 0x05 != msg.msg[25] || 0x06 != msg.msg[26] ||
       0x07 != msg.msg[27] || 0x08 != msg.msg[28] || 0x09 != msg.msg[29] ||
       0x0A != msg.msg[30] || 0x0B != msg.msg[31] || 0x0C != msg.msg[32] ||
       0x0D != msg.msg[33] || 0x0E != msg.msg[34] || 0x0F != msg.msg[35])
        return -1;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_authentication_request_msg(&msg, &auth_req))
        return -1;
    if(auth_req.nas_ksi.tsc_flag != LIBLTE_MME_TYPE_OF_SECURITY_CONTEXT_FLAG_MAPPED ||
       auth_req.nas_ksi.nas_ksi != 0x1)
        return -1;
    for(uint32 i=0; i<16; i++)
        if(auth_req.autn[i] != i || auth_req.rand[i] != i)
            return -1;
    return 0;
}

int authentication_response_msg_test(void)
{
    LIBLTE_MME_AUTHENTICATION_RESPONSE_MSG_STRUCT auth_resp;
    for(uint32 i=0; i<8; i++)
        auth_resp.res[i] = i;
    LIBLTE_BYTE_MSG_STRUCT msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_authentication_response_msg(&auth_resp, &msg))
        return -1;
    if(11 != msg.N_bytes)
        return -1;
    if(0x07 != msg.msg[0] || 0x53 != msg.msg[1] || 0x08 != msg.msg[2] ||
       0x00 != msg.msg[3] || 0x01 != msg.msg[4] || 0x02 != msg.msg[5] ||
       0x03 != msg.msg[6] || 0x04 != msg.msg[7] || 0x05 != msg.msg[8] ||
       0x06 != msg.msg[9] || 0x07 != msg.msg[10])
        return -1;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_authentication_response_msg(&msg, &auth_resp))
        return -1;
    for(uint32 i=0; i<8; i++)
        if(auth_resp.res[i] != i)
            return -1;
    return 0;
}

int detach_accept_msg_test(void)
{
    LIBLTE_MME_DETACH_ACCEPT_MSG_STRUCT detach_accept;
    uint8 key[32];
    for(uint32 i=0;i<32; i++)
        key[i] = i;
    LIBLTE_BYTE_MSG_STRUCT sec_msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_detach_accept_msg(&detach_accept,
                                                           LIBLTE_MME_SECURITY_HDR_TYPE_INTEGRITY_AND_CIPHERED,
                                                           key,
                                                           0x12,
                                                           LIBLTE_SECURITY_DIRECTION_DOWNLINK,
                                                           &sec_msg))
        return -1;
    if(8 != sec_msg.N_bytes)
        return -1;
    if(0x27 != sec_msg.msg[0] || 0x52 != sec_msg.msg[1] || 0x5A != sec_msg.msg[2] ||
       0xB9 != sec_msg.msg[3] || 0xC9 != sec_msg.msg[4] || 0x12 != sec_msg.msg[5] ||
       0x07 != sec_msg.msg[6] || 0x46 != sec_msg.msg[7])
        return -1;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_detach_accept_msg(&sec_msg, &detach_accept))
        return -1;
    return 0;
}

int detach_request_msg_test(void)
{
    LIBLTE_MME_DETACH_REQUEST_MSG_STRUCT detach_req;
    detach_req.detach_type.switch_off = LIBLTE_MME_SO_FLAG_SWITCH_OFF;
    detach_req.detach_type.type_of_detach = LIBLTE_MME_TOD_UL_IMSI_DETACH;
    detach_req.nas_ksi.tsc_flag = LIBLTE_MME_TYPE_OF_SECURITY_CONTEXT_FLAG_MAPPED;
    detach_req.nas_ksi.nas_ksi = 0x1;
    detach_req.eps_mobile_id.type_of_id = LIBLTE_MME_EPS_MOBILE_ID_TYPE_GUTI;
    detach_req.eps_mobile_id.guti.m_tmsi = 0x12345678;
    std::vector<MCC_MNC_Digit> mcc(3);
    mcc[0].SetValue(1);
    mcc[1].SetValue(2);
    mcc[2].SetValue(3);
    detach_req.eps_mobile_id.guti.mcc.SetValue(mcc);
    std::vector<MCC_MNC_Digit> mnc(2);
    mnc[0].SetValue(4);
    mnc[1].SetValue(5);
    detach_req.eps_mobile_id.guti.mnc.SetValue(mnc);
    detach_req.eps_mobile_id.guti.mme_group_id = 0xABCD;
    detach_req.eps_mobile_id.guti.mme_code = 0xEF;
    uint8 key[32];
    for(uint32 i=0;i<32; i++)
        key[i] = i;
    LIBLTE_BYTE_MSG_STRUCT sec_msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_detach_request_msg(&detach_req,
                                                            LIBLTE_MME_SECURITY_HDR_TYPE_INTEGRITY_AND_CIPHERED,
                                                            key,
                                                            0x12,
                                                            LIBLTE_SECURITY_DIRECTION_DOWNLINK,
                                                            &sec_msg))
        return -1;
    if(21 != sec_msg.N_bytes)
        return -1;
    if(0x27 != sec_msg.msg[0] || 0x16 != sec_msg.msg[1] || 0xE4 != sec_msg.msg[2] ||
       0x0B != sec_msg.msg[3] || 0x78 != sec_msg.msg[4] || 0x12 != sec_msg.msg[5] ||
       0x07 != sec_msg.msg[6] || 0x45 != sec_msg.msg[7] || 0x9A != sec_msg.msg[8] ||
       0x0B != sec_msg.msg[9] || 0xF6 != sec_msg.msg[10] || 0x21 != sec_msg.msg[11] ||
       0xF3 != sec_msg.msg[12] || 0x54 != sec_msg.msg[13] || 0xAB != sec_msg.msg[14] ||
       0xCD != sec_msg.msg[15] || 0xEF != sec_msg.msg[16] || 0x12 != sec_msg.msg[17] ||
       0x34 != sec_msg.msg[18] || 0x56 != sec_msg.msg[19] || 0x78 != sec_msg.msg[20])
        return -1;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_detach_request_msg(&sec_msg, &detach_req))
        return -1;
    if(detach_req.detach_type.switch_off != LIBLTE_MME_SO_FLAG_SWITCH_OFF ||
       detach_req.detach_type.type_of_detach != LIBLTE_MME_TOD_UL_IMSI_DETACH ||
       detach_req.nas_ksi.tsc_flag != LIBLTE_MME_TYPE_OF_SECURITY_CONTEXT_FLAG_MAPPED ||
       detach_req.nas_ksi.nas_ksi != 0x1 ||
       detach_req.eps_mobile_id.type_of_id != LIBLTE_MME_EPS_MOBILE_ID_TYPE_GUTI ||
       detach_req.eps_mobile_id.guti.m_tmsi != 0x12345678 ||
       detach_req.eps_mobile_id.guti.mcc.Value()[0].Value() != 1 ||
       detach_req.eps_mobile_id.guti.mcc.Value()[1].Value() != 2 ||
       detach_req.eps_mobile_id.guti.mcc.Value()[2].Value() != 3 ||
       detach_req.eps_mobile_id.guti.mnc.Value()[0].Value() != 4 ||
       detach_req.eps_mobile_id.guti.mnc.Value()[1].Value() != 5 ||
       detach_req.eps_mobile_id.guti.mme_group_id != 0xABCD ||
       detach_req.eps_mobile_id.guti.mme_code != 0xEF)
        return -1;
    return 0;
}

int dl_nas_transport_msg_test(void)
{
    LIBLTE_MME_DOWNLINK_NAS_TRANSPORT_MSG_STRUCT dl_nas_transport;
    dl_nas_transport.nas_msg.N_bytes = 2;
    dl_nas_transport.nas_msg.msg[0] = 0xA5;
    dl_nas_transport.nas_msg.msg[1] = 0x5A;
    uint8 key[32];
    for(uint32 i=0;i<32; i++)
        key[i] = i;
    LIBLTE_BYTE_MSG_STRUCT sec_msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_downlink_nas_transport_msg(&dl_nas_transport,
                                                                    LIBLTE_MME_SECURITY_HDR_TYPE_INTEGRITY_AND_CIPHERED,
                                                                    key,
                                                                    0x12,
                                                                    LIBLTE_SECURITY_DIRECTION_DOWNLINK,
                                                                    &sec_msg))
        return -1;
    if(11 != sec_msg.N_bytes)
        return -1;
    if(0x27 != sec_msg.msg[0] || 0xC9 != sec_msg.msg[1] || 0x1A != sec_msg.msg[2] ||
       0xAA != sec_msg.msg[3] || 0xAA != sec_msg.msg[4] || 0x12 != sec_msg.msg[5] ||
       0x07 != sec_msg.msg[6] || 0x62 != sec_msg.msg[7] || 0x02 != sec_msg.msg[8] ||
       0xA5 != sec_msg.msg[9] || 0x5A != sec_msg.msg[10])
        return -1;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_downlink_nas_transport_msg(&sec_msg,
                                                                      &dl_nas_transport))
        return -1;
    if(dl_nas_transport.nas_msg.N_bytes != 2 || dl_nas_transport.nas_msg.msg[0] != 0xA5 ||
       dl_nas_transport.nas_msg.msg[1] != 0x5A)
        return -1;
    return 0;
}

int emm_information_msg_test(void)
{
    LIBLTE_MME_EMM_INFORMATION_MSG_STRUCT emm_info;
    emm_info.short_net_name.name = "test";
    emm_info.short_net_name.add_ci= LIBLTE_MME_ADD_CI_ADD;
    emm_info.utc_and_local_time_zone.year = 2020;
    emm_info.utc_and_local_time_zone.month = 1;
    emm_info.utc_and_local_time_zone.day = 8;
    emm_info.utc_and_local_time_zone.hour = 11;
    emm_info.utc_and_local_time_zone.minute = 20;
    emm_info.utc_and_local_time_zone.second = 50;
    emm_info.utc_and_local_time_zone.tz = 0x12;
    emm_info.full_net_name_present = false;
    emm_info.short_net_name_present = true;
    emm_info.local_time_zone_present = false;
    emm_info.utc_and_local_time_zone_present = true;
    emm_info.net_dst_present = false;
    uint8 key[32];
    for(uint32 i=0;i<32; i++)
        key[i] = i;
    LIBLTE_BYTE_MSG_STRUCT sec_msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_emm_information_msg(&emm_info,
                                                             LIBLTE_MME_SECURITY_HDR_TYPE_INTEGRITY_AND_CIPHERED,
                                                             key,
                                                             0x12,
                                                             LIBLTE_SECURITY_DIRECTION_DOWNLINK,
                                                             &sec_msg))
        return -1;
    if(23 != sec_msg.N_bytes)
        return -1;
    if(0x27 != sec_msg.msg[0] || 0x2E != sec_msg.msg[1] || 0xDD != sec_msg.msg[2] ||
       0x6C != sec_msg.msg[3] || 0xC8 != sec_msg.msg[4] || 0x12 != sec_msg.msg[5] ||
       0x07 != sec_msg.msg[6] || 0x61 != sec_msg.msg[7] || 0x45 != sec_msg.msg[8] ||
       0x05 != sec_msg.msg[9] || 0x8C != sec_msg.msg[10] || 0xF4 != sec_msg.msg[11] ||
       0xF2 != sec_msg.msg[12] || 0x9C != sec_msg.msg[13] || 0x0E != sec_msg.msg[14] ||
       0x47 != sec_msg.msg[15] || 0x02 != sec_msg.msg[16] || 0x10 != sec_msg.msg[17] ||
       0x80 != sec_msg.msg[18] || 0x11 != sec_msg.msg[19] || 0x02 != sec_msg.msg[20] ||
       0x05 != sec_msg.msg[21] || 0x12 != sec_msg.msg[22])
        return -1;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_emm_information_msg(&sec_msg, &emm_info))
        return -1;
    if(emm_info.short_net_name.name != "test" ||
       emm_info.short_net_name.add_ci != LIBLTE_MME_ADD_CI_ADD ||
       emm_info.utc_and_local_time_zone.year != 2020 ||
       emm_info.utc_and_local_time_zone.month != 1 ||
       emm_info.utc_and_local_time_zone.day != 8 ||
       emm_info.utc_and_local_time_zone.hour != 11 ||
       emm_info.utc_and_local_time_zone.minute != 20 ||
       emm_info.utc_and_local_time_zone.second != 50 ||
       emm_info.utc_and_local_time_zone.tz != 0x12 || emm_info.full_net_name_present ||
       !emm_info.short_net_name_present || emm_info.local_time_zone_present ||
       !emm_info.utc_and_local_time_zone_present || emm_info.net_dst_present)
        return -1;
    return 0;
}

int emm_status_msg_test(void)
{
    LIBLTE_MME_EMM_STATUS_MSG_STRUCT emm_status;
    emm_status.emm_cause = LIBLTE_MME_EMM_CAUSE_IMSI_UNKNOWN_IN_HSS;
    uint8 key[32];
    for(uint32 i=0;i<32; i++)
        key[i] = i;
    LIBLTE_BYTE_MSG_STRUCT sec_msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_emm_status_msg(&emm_status,
                                                        LIBLTE_MME_SECURITY_HDR_TYPE_INTEGRITY_AND_CIPHERED,
                                                        key,
                                                        0x12,
                                                        LIBLTE_SECURITY_DIRECTION_DOWNLINK,
                                                        &sec_msg))
        return -1;
    if(9 != sec_msg.N_bytes)
        return -1;
    if(0x27 != sec_msg.msg[0] || 0xD2 != sec_msg.msg[1] || 0xB6 != sec_msg.msg[2] ||
       0x44 != sec_msg.msg[3] || 0x7E != sec_msg.msg[4] || 0x12 != sec_msg.msg[5] ||
       0x07 != sec_msg.msg[6] || 0x60 != sec_msg.msg[7] || 0x02 != sec_msg.msg[8])
        return -1;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_emm_status_msg(&sec_msg, &emm_status))
        return -1;
    if(emm_status.emm_cause != LIBLTE_MME_EMM_CAUSE_IMSI_UNKNOWN_IN_HSS)
        return -1;
    return 0;
}

int extended_service_request_msg_test(void)
{
    LIBLTE_MME_EXTENDED_SERVICE_REQUEST_MSG_STRUCT ext_service_req;
    ext_service_req.nas_ksi.tsc_flag = LIBLTE_MME_TYPE_OF_SECURITY_CONTEXT_FLAG_MAPPED;
    ext_service_req.nas_ksi.nas_ksi = 0x1;
    ext_service_req.m_tmsi.type_of_id = LIBLTE_MME_MOBILE_ID_TYPE_TMSI;
    ext_service_req.m_tmsi.tmsi = 0x12345678;
    for(uint32 i=0; i<16; i++)
    {
        ext_service_req.eps_bearer_context_status.ebi[i] = false;
        if(i%2)
            ext_service_req.eps_bearer_context_status.ebi[i] = true;
    }
    ext_service_req.service_type = LIBLTE_MME_SERVICE_TYPE_MT_CSFB;
    ext_service_req.csfb_resp_present = false;
    ext_service_req.eps_bearer_context_status_present = true;
    ext_service_req.device_props_present = false;
    uint8 key[32];
    for(uint32 i=0;i<32; i++)
        key[i] = i;
    LIBLTE_BYTE_MSG_STRUCT sec_msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_extended_service_request_msg(&ext_service_req,
                                                                      LIBLTE_MME_SECURITY_HDR_TYPE_INTEGRITY_AND_CIPHERED,
                                                                      key,
                                                                      0x12,
                                                                      LIBLTE_SECURITY_DIRECTION_DOWNLINK,
                                                                      &sec_msg))
        return -1;
    if(19 != sec_msg.N_bytes)
        return -1;
    if(0x27 != sec_msg.msg[0] || 0x6B != sec_msg.msg[1] || 0xB1 != sec_msg.msg[2] ||
       0xF9 != sec_msg.msg[3] || 0xD8 != sec_msg.msg[4] || 0x12 != sec_msg.msg[5] ||
       0x07 != sec_msg.msg[6] || 0x4C != sec_msg.msg[7] || 0x91 != sec_msg.msg[8] ||
       0x05 != sec_msg.msg[9] || 0xF4 != sec_msg.msg[10] || 0x12 != sec_msg.msg[11] ||
       0x34 != sec_msg.msg[12] || 0x56 != sec_msg.msg[13] || 0x78 != sec_msg.msg[14] ||
       0x57 != sec_msg.msg[15] || 0x02 != sec_msg.msg[16] || 0xA0 != sec_msg.msg[17] ||
       0xAA != sec_msg.msg[18])
        return -1;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_extended_service_request_msg(&sec_msg,
                                                                        &ext_service_req))
        return -1;
    if(ext_service_req.nas_ksi.tsc_flag != LIBLTE_MME_TYPE_OF_SECURITY_CONTEXT_FLAG_MAPPED ||
       ext_service_req.nas_ksi.nas_ksi != 0x1 ||
       ext_service_req.m_tmsi.type_of_id != LIBLTE_MME_MOBILE_ID_TYPE_TMSI ||
       ext_service_req.m_tmsi.tmsi != 0x12345678)
        return -1;
    for(uint32 i=0; i<16; i++)
    {
        if(i%2 && !ext_service_req.eps_bearer_context_status.ebi[i])
            return -1;
        if(!(i%2) && ext_service_req.eps_bearer_context_status.ebi[i])
            return -1;
    }
    if(ext_service_req.service_type != LIBLTE_MME_SERVICE_TYPE_MT_CSFB ||
       ext_service_req.csfb_resp_present ||
       !ext_service_req.eps_bearer_context_status_present ||
       ext_service_req.device_props_present)
        return -1;
    return 0;
}

int guti_reallocation_command_msg_test(void)
{
    LIBLTE_MME_GUTI_REALLOCATION_COMMAND_MSG_STRUCT guti_realloc_cmd;
    guti_realloc_cmd.guti.type_of_id = LIBLTE_MME_EPS_MOBILE_ID_TYPE_GUTI;
    guti_realloc_cmd.guti.guti.m_tmsi = 0x12345678;
    std::vector<MCC_MNC_Digit> mcc(3);
    mcc[0].SetValue(1);
    mcc[1].SetValue(2);
    mcc[2].SetValue(3);
    guti_realloc_cmd.guti.guti.mcc.SetValue(mcc);
    std::vector<MCC_MNC_Digit> mnc(2);
    mnc[0].SetValue(4);
    mnc[1].SetValue(5);
    guti_realloc_cmd.guti.guti.mnc.SetValue(mnc);
    guti_realloc_cmd.guti.guti.mme_group_id = 0xABCD;
    guti_realloc_cmd.guti.guti.mme_code = 0xEF;
    guti_realloc_cmd.tai_list_present = false;
    uint8 key[32];
    for(uint32 i=0;i<32; i++)
        key[i] = i;
    LIBLTE_BYTE_MSG_STRUCT sec_msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_guti_reallocation_command_msg(&guti_realloc_cmd,
                                                                       LIBLTE_MME_SECURITY_HDR_TYPE_INTEGRITY_AND_CIPHERED,
                                                                       key,
                                                                       0x12,
                                                                       LIBLTE_SECURITY_DIRECTION_DOWNLINK,
                                                                       &sec_msg))
        return -1;
    if(20 != sec_msg.N_bytes)
        return -1;
    if(0x27 != sec_msg.msg[0] || 0x34 != sec_msg.msg[1] || 0x69 != sec_msg.msg[2] ||
       0xF8 != sec_msg.msg[3] || 0x29 != sec_msg.msg[4] || 0x12 != sec_msg.msg[5] ||
       0x07 != sec_msg.msg[6] || 0x50 != sec_msg.msg[7] || 0x0B != sec_msg.msg[8] ||
       0xF6 != sec_msg.msg[9] || 0x21 != sec_msg.msg[10] || 0xF3 != sec_msg.msg[11] ||
       0x54 != sec_msg.msg[12] || 0xAB != sec_msg.msg[13] || 0xCD != sec_msg.msg[14] ||
       0xEF != sec_msg.msg[15] || 0x12 != sec_msg.msg[16] || 0x34 != sec_msg.msg[17] ||
       0x56 != sec_msg.msg[18] || 0x78 != sec_msg.msg[19])
        return -1;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_guti_reallocation_command_msg(&sec_msg,
                                                                         &guti_realloc_cmd))
        return -1;
    if(guti_realloc_cmd.guti.type_of_id != LIBLTE_MME_EPS_MOBILE_ID_TYPE_GUTI ||
       guti_realloc_cmd.guti.guti.m_tmsi != 0x12345678 ||
       guti_realloc_cmd.guti.guti.mcc.Value()[0].Value() != 1 ||
       guti_realloc_cmd.guti.guti.mcc.Value()[1].Value() != 2 ||
       guti_realloc_cmd.guti.guti.mcc.Value()[2].Value() != 3 ||
       guti_realloc_cmd.guti.guti.mnc.Value()[0].Value() != 4 ||
       guti_realloc_cmd.guti.guti.mnc.Value()[1].Value() != 5 ||
       guti_realloc_cmd.guti.guti.mme_group_id != 0xABCD ||
       guti_realloc_cmd.guti.guti.mme_code != 0xEF || guti_realloc_cmd.tai_list_present)
        return -1;
    return 0;
}

int guti_reallocation_complete_msg_test(void)
{
    LIBLTE_MME_GUTI_REALLOCATION_COMPLETE_MSG_STRUCT guti_realloc_complete;
    uint8 key[32];
    for(uint32 i=0;i<32; i++)
        key[i] = i;
    LIBLTE_BYTE_MSG_STRUCT sec_msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_guti_reallocation_complete_msg(&guti_realloc_complete,
                                                                        LIBLTE_MME_SECURITY_HDR_TYPE_INTEGRITY_AND_CIPHERED,
                                                                        key,
                                                                        0x12,
                                                                        LIBLTE_SECURITY_DIRECTION_DOWNLINK,
                                                                        &sec_msg))
        return -1;
    if(8 != sec_msg.N_bytes)
        return -1;
    if(0x27 != sec_msg.msg[0] || 0x3F != sec_msg.msg[1] || 0x9B != sec_msg.msg[2] ||
       0xA8 != sec_msg.msg[3] || 0x88 != sec_msg.msg[4] || 0x12 != sec_msg.msg[5] ||
       0x07 != sec_msg.msg[6] || 0x51 != sec_msg.msg[7])
        return -1;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_guti_reallocation_complete_msg(&sec_msg,
                                                                          &guti_realloc_complete))
        return -1;
    return 0;
}

int identity_request_msg_test(void)
{
    LIBLTE_MME_ID_REQUEST_MSG_STRUCT id_req;
    id_req.id_type = LIBLTE_MME_ID_TYPE_2_IMEI;
    LIBLTE_BYTE_MSG_STRUCT msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_identity_request_msg(&id_req, &msg))
        return -1;
    if(3 != msg.N_bytes)
        return -1;
    if(0x07 != msg.msg[0] || 0x55 != msg.msg[1] || 0x02 != msg.msg[2])
        return -1;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_identity_request_msg(&msg, &id_req))
        return -1;
    if(id_req.id_type != LIBLTE_MME_ID_TYPE_2_IMEI)
        return -1;
    return 0;
}

int identity_response_msg_test(void)
{
    LIBLTE_MME_ID_RESPONSE_MSG_STRUCT id_resp;
    id_resp.mobile_id.type_of_id = LIBLTE_MME_MOBILE_ID_TYPE_TMSI;
    id_resp.mobile_id.tmsi = 0x12345678;
    LIBLTE_BYTE_MSG_STRUCT msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_identity_response_msg(&id_resp, &msg))
        return -1;
    if(8 != msg.N_bytes)
        return -1;
    if(0x07 != msg.msg[0] || 0x56 != msg.msg[1] || 0x05 != msg.msg[2] ||
       0xF4 != msg.msg[3] || 0x12 != msg.msg[4] || 0x34 != msg.msg[5] ||
       0x56 != msg.msg[6] || 0x78 != msg.msg[7])
        return -1;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_identity_response_msg(&msg, &id_resp))
        return -1;
    if(id_resp.mobile_id.type_of_id != LIBLTE_MME_MOBILE_ID_TYPE_TMSI ||
       id_resp.mobile_id.tmsi != 0x12345678)
        return -1;
    return 0;
}

int security_mode_command_msg_test(void)
{
    LIBLTE_MME_SECURITY_MODE_COMMAND_MSG_STRUCT sec_mode_cmd;
    sec_mode_cmd.selected_nas_sec_algs.type_of_eea = LIBLTE_MME_TYPE_OF_CIPHERING_ALGORITHM_EEA5;
    sec_mode_cmd.selected_nas_sec_algs.type_of_eia = LIBLTE_MME_TYPE_OF_INTEGRITY_ALGORITHM_EIA4;
    sec_mode_cmd.nas_ksi.tsc_flag = LIBLTE_MME_TYPE_OF_SECURITY_CONTEXT_FLAG_MAPPED;
    sec_mode_cmd.nas_ksi.nas_ksi = 0x1;
    for(uint32 i=0; i<8; i++)
    {
        sec_mode_cmd.ue_security_cap.eea[i] = i%2;
        sec_mode_cmd.ue_security_cap.eia[i] = i%2;
        sec_mode_cmd.ue_security_cap.uea[i] = i%2;
        sec_mode_cmd.ue_security_cap.uia[i] = i%2;
        sec_mode_cmd.ue_security_cap.gea[i] = i%2;
    }
    sec_mode_cmd.ue_security_cap.uea_present = true;
    sec_mode_cmd.ue_security_cap.uia_present = true;
    sec_mode_cmd.ue_security_cap.gea_present = true;
    sec_mode_cmd.nonce_ue = 0x12345678;
    sec_mode_cmd.imeisv_req_present = false;
    sec_mode_cmd.nonce_ue_present = true;
    sec_mode_cmd.nonce_mme_present = false;
    uint8 key[32];
    for(uint32 i=0;i<32; i++)
        key[i] = i;
    LIBLTE_BYTE_MSG_STRUCT sec_msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_security_mode_command_msg(&sec_mode_cmd,
                                                                   LIBLTE_MME_SECURITY_HDR_TYPE_INTEGRITY_AND_CIPHERED,
                                                                   key,
                                                                   0x12,
                                                                   LIBLTE_SECURITY_DIRECTION_DOWNLINK,
                                                                   &sec_msg))
        return -1;
    if(21 != sec_msg.N_bytes)
        return -1;
    if(0x27 != sec_msg.msg[0] || 0x72 != sec_msg.msg[1] || 0xE4 != sec_msg.msg[2] ||
       0xF3 != sec_msg.msg[3] || 0x9E != sec_msg.msg[4] || 0x12 != sec_msg.msg[5] ||
       0x07 != sec_msg.msg[6] || 0x5D != sec_msg.msg[7] || 0x54 != sec_msg.msg[8] ||
       0x09 != sec_msg.msg[9] || 0x05 != sec_msg.msg[10] || 0x55 != sec_msg.msg[11] ||
       0x55 != sec_msg.msg[12] || 0x55 != sec_msg.msg[13] || 0x55 != sec_msg.msg[14] ||
       0x55 != sec_msg.msg[15] || 0x55 != sec_msg.msg[16] || 0x12 != sec_msg.msg[17] ||
       0x34 != sec_msg.msg[18] || 0x56 != sec_msg.msg[19] || 0x78 != sec_msg.msg[20])
        return -1;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_security_mode_command_msg(&sec_msg, &sec_mode_cmd))
        return -1;
    if(sec_mode_cmd.selected_nas_sec_algs.type_of_eea != LIBLTE_MME_TYPE_OF_CIPHERING_ALGORITHM_EEA5 ||
       sec_mode_cmd.selected_nas_sec_algs.type_of_eia != LIBLTE_MME_TYPE_OF_INTEGRITY_ALGORITHM_EIA4 ||
       sec_mode_cmd.nas_ksi.tsc_flag != LIBLTE_MME_TYPE_OF_SECURITY_CONTEXT_FLAG_MAPPED ||
       sec_mode_cmd.nas_ksi.nas_ksi != 0x1)
        return -1;
    for(uint32 i=0; i<8; i++)
        if(sec_mode_cmd.ue_security_cap.eea[i] != i%2 ||
           sec_mode_cmd.ue_security_cap.eia[i] != i%2 ||
           sec_mode_cmd.ue_security_cap.uea[i] != i%2 ||
           sec_mode_cmd.ue_security_cap.uia[i] != i%2 ||
           sec_mode_cmd.ue_security_cap.gea[i] != i%2)
            return -1;
    if(!sec_mode_cmd.ue_security_cap.uea_present ||
       !sec_mode_cmd.ue_security_cap.uia_present ||
       !sec_mode_cmd.ue_security_cap.gea_present ||
       sec_mode_cmd.nonce_ue != 0x12345678 || sec_mode_cmd.imeisv_req_present ||
       !sec_mode_cmd.nonce_ue_present || sec_mode_cmd.nonce_mme_present)
        return -1;
    return 0;
}

int security_mode_complete_msg_test(void)
{
    LIBLTE_MME_SECURITY_MODE_COMPLETE_MSG_STRUCT sec_mode_comp;
    sec_mode_comp.imeisv_present = false;
    uint8 key[32];
    for(uint32 i=0;i<32; i++)
        key[i] = i;
    LIBLTE_BYTE_MSG_STRUCT sec_msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_security_mode_complete_msg(&sec_mode_comp,
                                                                    LIBLTE_MME_SECURITY_HDR_TYPE_INTEGRITY_AND_CIPHERED,
                                                                    key,
                                                                    0x12,
                                                                    LIBLTE_SECURITY_DIRECTION_DOWNLINK,
                                                                    &sec_msg))
        return -1;
    if(8 != sec_msg.N_bytes)
        return -1;
    if(0x27 != sec_msg.msg[0] || 0x79 != sec_msg.msg[1] || 0xBF != sec_msg.msg[2] ||
       0xF0 != sec_msg.msg[3] || 0xD9 != sec_msg.msg[4] || 0x12 != sec_msg.msg[5] ||
       0x07 != sec_msg.msg[6] || 0x5E != sec_msg.msg[7])
        return -1;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_security_mode_complete_msg(&sec_msg,
                                                                      &sec_mode_comp))
        return -1;
    if(sec_mode_comp.imeisv_present)
        return -1;
    return 0;
}

int security_mode_reject_msg_test(void)
{
    LIBLTE_MME_SECURITY_MODE_REJECT_MSG_STRUCT sec_mode_rej;
    sec_mode_rej.emm_cause = LIBLTE_MME_EMM_CAUSE_SECURITY_MODE_REJECTED_UNSPECIFIED;
    LIBLTE_BYTE_MSG_STRUCT msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_security_mode_reject_msg(&sec_mode_rej, &msg))
        return -1;
    if(3 != msg.N_bytes)
        return -1;
    if(0x07 != msg.msg[0] || 0x5F != msg.msg[1] || 0x18 != msg.msg[2])
        return -1;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_security_mode_reject_msg(&msg, &sec_mode_rej))
        return -1;
    if(sec_mode_rej.emm_cause != LIBLTE_MME_EMM_CAUSE_SECURITY_MODE_REJECTED_UNSPECIFIED)
        return -1;
    return 0;
}

int service_reject_msg_test(void)
{
    LIBLTE_MME_SERVICE_REJECT_MSG_STRUCT service_rej;
    service_rej.emm_cause = LIBLTE_MME_EMM_CAUSE_CS_SERVICE_TEMPORARILY_NOT_AVAILABLE;
    service_rej.t3446 = 0xA5;
    service_rej.t3442_present = false;
    service_rej.t3446_present = true;
    uint8 key[32];
    for(uint32 i=0;i<32; i++)
        key[i] = i;
    LIBLTE_BYTE_MSG_STRUCT sec_msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_service_reject_msg(&service_rej,
                                                            LIBLTE_MME_SECURITY_HDR_TYPE_INTEGRITY_AND_CIPHERED,
                                                            key,
                                                            0x12,
                                                            LIBLTE_SECURITY_DIRECTION_DOWNLINK,
                                                            &sec_msg))
        return -1;
    if(12 != sec_msg.N_bytes)
        return -1;
    if(0x27 != sec_msg.msg[0] || 0xFB != sec_msg.msg[1] || 0x64 != sec_msg.msg[2] ||
       0x31 != sec_msg.msg[3] || 0x2F != sec_msg.msg[4] || 0x12 != sec_msg.msg[5] ||
       0x07 != sec_msg.msg[6] || 0x4E != sec_msg.msg[7] || 0x27 != sec_msg.msg[8] ||
       0x5F != sec_msg.msg[9] || 0x01 != sec_msg.msg[10] || 0xA5 != sec_msg.msg[11])
        return -1;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_service_reject_msg(&sec_msg, &service_rej))
        return -1;
    if(service_rej.emm_cause != LIBLTE_MME_EMM_CAUSE_CS_SERVICE_TEMPORARILY_NOT_AVAILABLE ||
       service_rej.t3446 != 0xA5 || service_rej.t3442_present || !service_rej.t3446_present)
        return -1;
    return 0;
}

int service_request_msg_test(void)
{
    LIBLTE_MME_SERVICE_REQUEST_MSG_STRUCT service_req;
    service_req.ksi_and_seq_num.ksi = 0x6;
    service_req.ksi_and_seq_num.seq_num = 0x15;
    service_req.short_mac = 0x1234;
    LIBLTE_BYTE_MSG_STRUCT msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_service_request_msg(&service_req, &msg))
        return -1;
    if(4 != msg.N_bytes)
        return -1;
    if(0xC7 != msg.msg[0] || 0xD5 != msg.msg[1] || 0x12 != msg.msg[2] || 0x34 != msg.msg[3])
        return -1;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_service_request_msg(&msg, &service_req))
        return -1;
    if(service_req.ksi_and_seq_num.ksi != 0x6 || service_req.ksi_and_seq_num.seq_num != 0x15 ||
       service_req.short_mac != 0x1234)
        return -1;
    return 0;
}

int tracking_area_update_accept_msg_test(void)
{
    LIBLTE_MME_TRACKING_AREA_UPDATE_ACCEPT_MSG_STRUCT ta_update_accept;
    ta_update_accept.guti.type_of_id = LIBLTE_MME_EPS_MOBILE_ID_TYPE_GUTI;
    ta_update_accept.guti.guti.m_tmsi = 0x12345678;
    std::vector<MCC_MNC_Digit> mcc(3);
    mcc[0].SetValue(1);
    mcc[1].SetValue(2);
    mcc[2].SetValue(3);
    ta_update_accept.guti.guti.mcc.SetValue(mcc);
    std::vector<MCC_MNC_Digit> mnc2(2);
    mnc2[0].SetValue(4);
    mnc2[1].SetValue(5);
    ta_update_accept.guti.guti.mnc.SetValue(mnc2);
    ta_update_accept.guti.guti.mme_group_id = 0xABCD;
    ta_update_accept.guti.guti.mme_code = 0xEF;
    for(uint32 i=0; i<16; i++)
    {
        ta_update_accept.eps_bearer_context_status.ebi[i] = false;
        if(i%2)
            ta_update_accept.eps_bearer_context_status.ebi[i] = true;
    }
    ta_update_accept.ms_id.type_of_id = LIBLTE_MME_MOBILE_ID_TYPE_TMSI;
    ta_update_accept.ms_id.tmsi = 0x12345678;
    ta_update_accept.t3402.unit = LIBLTE_MME_GPRS_TIMER_UNIT_1_MINUTE;
    ta_update_accept.t3402.value = 0x15;
    ta_update_accept.equivalent_plmns.N_plmns = 1;
    ta_update_accept.equivalent_plmns.mcc[0].SetValue(mcc);
    std::vector<MCC_MNC_Digit> mnc3(3);
    mnc3[0].SetValue(4);
    mnc3[1].SetValue(5);
    mnc3[2].SetValue(6);
    ta_update_accept.equivalent_plmns.mnc[0].SetValue(mnc3);
    ta_update_accept.eps_network_feature_support.cs_lcs = LIBLTE_MME_CS_LCS_SUPPORTED;
    ta_update_accept.eps_network_feature_support.esrps = false;
    ta_update_accept.eps_network_feature_support.epc_lcs = true;
    ta_update_accept.eps_network_feature_support.emc_bs = false;
    ta_update_accept.eps_network_feature_support.ims_vops = true;
    ta_update_accept.t3412_ext.unit = LIBLTE_MME_GPRS_TIMER_UNIT_1_MINUTE;
    ta_update_accept.t3412_ext.value = 1;
    ta_update_accept.eps_update_result = LIBLTE_MME_EPS_UPDATE_RESULT_TA_UPDATED;
    ta_update_accept.t3412_present = false;
    ta_update_accept.guti_present = true;
    ta_update_accept.tai_list_present = false;
    ta_update_accept.eps_bearer_context_status_present = true;
    ta_update_accept.lai_present = false;
    ta_update_accept.ms_id_present = true;
    ta_update_accept.emm_cause_present = false;
    ta_update_accept.t3402_present = true;
    ta_update_accept.t3423_present = false;
    ta_update_accept.equivalent_plmns_present = true;
    ta_update_accept.emerg_num_list_present = false;
    ta_update_accept.eps_network_feature_support_present = true;
    ta_update_accept.additional_update_result_present = false;
    ta_update_accept.t3412_ext_present = true;
    uint8 key[32];
    for(uint32 i=0;i<32; i++)
        key[i] = i;
    LIBLTE_BYTE_MSG_STRUCT sec_msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_tracking_area_update_accept_msg(&ta_update_accept,
                                                                         LIBLTE_MME_SECURITY_HDR_TYPE_INTEGRITY_AND_CIPHERED,
                                                                         key,
                                                                         0x12,
                                                                         LIBLTE_SECURITY_DIRECTION_DOWNLINK,
                                                                         &sec_msg))
        return -1;
    if(46 != sec_msg.N_bytes)
        return -1;
    if(0x27 != sec_msg.msg[0] || 0xF9 != sec_msg.msg[1] || 0xB6 != sec_msg.msg[2] ||
       0x78 != sec_msg.msg[3] || 0xB8 != sec_msg.msg[4] || 0x12 != sec_msg.msg[5] ||
       0x07 != sec_msg.msg[6] || 0x49 != sec_msg.msg[7] || 0x00 != sec_msg.msg[8] ||
       0x50 != sec_msg.msg[9] || 0x0B != sec_msg.msg[10] || 0xF6 != sec_msg.msg[11] ||
       0x21 != sec_msg.msg[12] || 0xF3 != sec_msg.msg[13] || 0x54 != sec_msg.msg[14] ||
       0xAB != sec_msg.msg[15] || 0xCD != sec_msg.msg[16] || 0xEF != sec_msg.msg[17] ||
       0x12 != sec_msg.msg[18] || 0x34 != sec_msg.msg[19] || 0x56 != sec_msg.msg[20] ||
       0x78 != sec_msg.msg[21] || 0x57 != sec_msg.msg[22] || 0x02 != sec_msg.msg[23] ||
       0xA0 != sec_msg.msg[24] || 0xAA != sec_msg.msg[25] || 0x23 != sec_msg.msg[26] ||
       0x05 != sec_msg.msg[27] || 0xF4 != sec_msg.msg[28] || 0x12 != sec_msg.msg[29] ||
       0x34 != sec_msg.msg[30] || 0x56 != sec_msg.msg[31] || 0x78 != sec_msg.msg[32] ||
       0x17 != sec_msg.msg[33] || 0x35 != sec_msg.msg[34] || 0x4A != sec_msg.msg[35] ||
       0x03 != sec_msg.msg[36] || 0x21 != sec_msg.msg[37] || 0x63 != sec_msg.msg[38] ||
       0x54 != sec_msg.msg[39] || 0x64 != sec_msg.msg[40] || 0x01 != sec_msg.msg[41] ||
       0x15 != sec_msg.msg[42] || 0x5E != sec_msg.msg[43] || 0x01 != sec_msg.msg[44] ||
       0x21 != sec_msg.msg[45])
        return -1;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_tracking_area_update_accept_msg(&sec_msg,
                                                                           &ta_update_accept))
        return -1;
    if(ta_update_accept.guti.type_of_id != LIBLTE_MME_EPS_MOBILE_ID_TYPE_GUTI ||
       ta_update_accept.guti.guti.m_tmsi != 0x12345678 ||
       ta_update_accept.guti.guti.mcc.Value()[0].Value() != 1 ||
       ta_update_accept.guti.guti.mcc.Value()[1].Value() != 2 ||
       ta_update_accept.guti.guti.mcc.Value()[2].Value() != 3 ||
       ta_update_accept.guti.guti.mnc.Value()[0].Value() != 4 ||
       ta_update_accept.guti.guti.mnc.Value()[1].Value() != 5 ||
       ta_update_accept.guti.guti.mme_group_id != 0xABCD ||
       ta_update_accept.guti.guti.mme_code != 0xEF)
        return -1;
    for(uint32 i=0; i<16; i++)
    {
        if(i%2 && !ta_update_accept.eps_bearer_context_status.ebi[i])
            return -1;
        if(!(i%2) && ta_update_accept.eps_bearer_context_status.ebi[i])
            return -1;
    }
    if(ta_update_accept.ms_id.type_of_id != LIBLTE_MME_MOBILE_ID_TYPE_TMSI ||
       ta_update_accept.ms_id.tmsi != 0x12345678 ||
       ta_update_accept.t3402.unit != LIBLTE_MME_GPRS_TIMER_UNIT_1_MINUTE ||
       ta_update_accept.t3402.value != 0x15 ||
       ta_update_accept.equivalent_plmns.N_plmns != 1 ||
       ta_update_accept.equivalent_plmns.mcc[0].Value()[0].Value() != 1 ||
       ta_update_accept.equivalent_plmns.mcc[0].Value()[1].Value() != 2 ||
       ta_update_accept.equivalent_plmns.mcc[0].Value()[2].Value() != 3 ||
       ta_update_accept.equivalent_plmns.mnc[0].Value()[0].Value() != 4 ||
       ta_update_accept.equivalent_plmns.mnc[0].Value()[1].Value() != 5 ||
       ta_update_accept.equivalent_plmns.mnc[0].Value()[2].Value() != 6 ||
       ta_update_accept.eps_network_feature_support.cs_lcs != LIBLTE_MME_CS_LCS_SUPPORTED ||
       ta_update_accept.eps_network_feature_support.esrps ||
       !ta_update_accept.eps_network_feature_support.epc_lcs ||
       ta_update_accept.eps_network_feature_support.emc_bs ||
       !ta_update_accept.eps_network_feature_support.ims_vops ||
       ta_update_accept.t3412_ext.unit != LIBLTE_MME_GPRS_TIMER_UNIT_1_MINUTE ||
       ta_update_accept.t3412_ext.value != 1 ||
       ta_update_accept.eps_update_result != LIBLTE_MME_EPS_UPDATE_RESULT_TA_UPDATED ||
       ta_update_accept.t3412_present || !ta_update_accept.guti_present ||
       ta_update_accept.tai_list_present ||
       !ta_update_accept.eps_bearer_context_status_present ||
       ta_update_accept.lai_present || !ta_update_accept.ms_id_present ||
       ta_update_accept.emm_cause_present || !ta_update_accept.t3402_present ||
       ta_update_accept.t3423_present || !ta_update_accept.equivalent_plmns_present ||
       ta_update_accept.emerg_num_list_present ||
       !ta_update_accept.eps_network_feature_support_present ||
       ta_update_accept.additional_update_result_present ||
       !ta_update_accept.t3412_ext_present)
        return -1;
    return 0;
}

int tracking_area_update_complete_msg_test(void)
{
    LIBLTE_MME_TRACKING_AREA_UPDATE_COMPLETE_MSG_STRUCT ta_update_complete;
    uint8 key[32];
    for(uint32 i=0;i<32; i++)
        key[i] = i;
    LIBLTE_BYTE_MSG_STRUCT sec_msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_tracking_area_update_complete_msg(&ta_update_complete,
                                                                           LIBLTE_MME_SECURITY_HDR_TYPE_INTEGRITY_AND_CIPHERED,
                                                                           key,
                                                                           0x12,
                                                                           LIBLTE_SECURITY_DIRECTION_DOWNLINK,
                                                                           &sec_msg))
        return -1;
    if(8 != sec_msg.N_bytes)
        return -1;
    if(0x27 != sec_msg.msg[0] || 0x6A != sec_msg.msg[1] || 0xC3 != sec_msg.msg[2] ||
       0x52 != sec_msg.msg[3] || 0xB1 != sec_msg.msg[4] || 0x12 != sec_msg.msg[5] ||
       0x07 != sec_msg.msg[6] || 0x4A != sec_msg.msg[7])
        return -1;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_tracking_area_update_complete_msg(&sec_msg,
                                                                             &ta_update_complete))
        return -1;
    return 0;
}

int tracking_area_update_reject_msg_test(void)
{
    LIBLTE_MME_TRACKING_AREA_UPDATE_REJECT_MSG_STRUCT ta_update_rej;
    ta_update_rej.emm_cause = LIBLTE_MME_EMM_CAUSE_IMSI_UNKNOWN_IN_HSS;
    ta_update_rej.t3446_present = false;
    uint8 key[32];
    for(uint32 i=0;i<32; i++)
        key[i] = i;
    LIBLTE_BYTE_MSG_STRUCT sec_msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_tracking_area_update_reject_msg(&ta_update_rej,
                                                                         LIBLTE_MME_SECURITY_HDR_TYPE_INTEGRITY_AND_CIPHERED,
                                                                         key,
                                                                         0x12,
                                                                         LIBLTE_SECURITY_DIRECTION_DOWNLINK,
                                                                         &sec_msg))
        return -1;
    if(9 != sec_msg.N_bytes)
        return -1;
    if(0x27 != sec_msg.msg[0] || 0xAA != sec_msg.msg[1] || 0x88 != sec_msg.msg[2] ||
       0x2B != sec_msg.msg[3] || 0x34 != sec_msg.msg[4] || 0x12 != sec_msg.msg[5] ||
       0x07 != sec_msg.msg[6] || 0x4B != sec_msg.msg[7] || 0x02 != sec_msg.msg[8])
        return -1;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_tracking_area_update_reject_msg(&sec_msg,
                                                                           &ta_update_rej))
        return -1;
    if(ta_update_rej.emm_cause != LIBLTE_MME_EMM_CAUSE_IMSI_UNKNOWN_IN_HSS ||
       ta_update_rej.t3446_present)
        return -1;
    return 0;
}

int tracking_area_update_request_msg_test(void)
{
    LIBLTE_MME_TRACKING_AREA_UPDATE_REQUEST_MSG_STRUCT ta_update_req;
    ta_update_req.eps_update_type.type = LIBLTE_MME_EPS_UPDATE_TYPE_COMBINED_TA_LA_UPDATING;
    ta_update_req.eps_update_type.active_flag = true;
    ta_update_req.nas_ksi.tsc_flag = LIBLTE_MME_TYPE_OF_SECURITY_CONTEXT_FLAG_MAPPED;
    ta_update_req.nas_ksi.nas_ksi = 0x1;
    ta_update_req.old_guti.type_of_id = LIBLTE_MME_EPS_MOBILE_ID_TYPE_GUTI;
    ta_update_req.old_guti.guti.m_tmsi = 0x12345678;
    std::vector<MCC_MNC_Digit> mcc(3);
    mcc[0].SetValue(1);
    mcc[1].SetValue(2);
    mcc[2].SetValue(3);
    ta_update_req.old_guti.guti.mcc.SetValue(mcc);
    std::vector<MCC_MNC_Digit> mnc(2);
    mnc[0].SetValue(4);
    mnc[1].SetValue(5);
    ta_update_req.old_guti.guti.mnc.SetValue(mnc);
    ta_update_req.old_guti.guti.mme_group_id = 0xABCD;
    ta_update_req.old_guti.guti.mme_code = 0xEF;
    ta_update_req.additional_guti.type_of_id = LIBLTE_MME_EPS_MOBILE_ID_TYPE_GUTI;
    ta_update_req.additional_guti.guti.m_tmsi = 0x12345678;
    ta_update_req.additional_guti.guti.mcc.SetValue(mcc);
    ta_update_req.additional_guti.guti.mnc.SetValue(mnc);
    ta_update_req.additional_guti.guti.mme_group_id = 0xABCD;
    ta_update_req.additional_guti.guti.mme_code = 0xEF;
    for(uint32 i=0; i<8; i++)
    {
        ta_update_req.ue_network_cap.eea[i] = i%2;
        ta_update_req.ue_network_cap.eia[i] = i%2;
        ta_update_req.ue_network_cap.uea[i] = i%2;
        ta_update_req.ue_network_cap.uia[i] = i%2;
    }
    ta_update_req.ue_network_cap.uea_present = true;
    ta_update_req.ue_network_cap.ucs2 = false;
    ta_update_req.ue_network_cap.ucs2_present = true;
    ta_update_req.ue_network_cap.uia_present = true;
    ta_update_req.ue_network_cap.lpp = false;
    ta_update_req.ue_network_cap.lpp_present = true;
    ta_update_req.ue_network_cap.lcs = true;
    ta_update_req.ue_network_cap.lcs_present = true;
    ta_update_req.ue_network_cap.onexsrvcc = false;
    ta_update_req.ue_network_cap.onexsrvcc_present = true;
    ta_update_req.ue_network_cap.nf = false;
    ta_update_req.ue_network_cap.nf_present = true;
    ta_update_req.drx_param.non_drx_timer = LIBLTE_MME_NON_DRX_TIMER_MAX_8S_NON_DRX_MODE;
    ta_update_req.drx_param.split_pg_cycle_code = 0xA5;
    ta_update_req.drx_param.drx_cycle_len_coeff_and_value = 0x6;
    ta_update_req.drx_param.split_on_ccch = false;
    for(uint32 i=0; i<16; i++)
    {
        ta_update_req.eps_bearer_context_status.ebi[i] = false;
        if(i%2)
            ta_update_req.eps_bearer_context_status.ebi[i] = true;
    }
    ta_update_req.old_lai.mcc.SetValue(mcc);
    std::vector<MCC_MNC_Digit> mnc3(3);
    mnc3[0].SetValue(4);
    mnc3[1].SetValue(5);
    mnc3[2].SetValue(6);
    ta_update_req.old_lai.mnc.SetValue(mnc3);
    ta_update_req.old_lai.lac = 0x1234;
    ta_update_req.ms_cm2.rev_lev = LIBLTE_MME_REVISION_LEVEL_R99;
    ta_update_req.ms_cm2.rf_power_cap = LIBLTE_MME_RF_POWER_CAPABILITY_CLASS_3;
    ta_update_req.ms_cm2.ss_screen_ind = LIBLTE_MME_SS_SCREEN_INDICATOR_2;
    ta_update_req.ms_cm2.es_ind = false;
    ta_update_req.ms_cm2.a5_1 = true;
    ta_update_req.ms_cm2.ps_cap = false;
    ta_update_req.ms_cm2.sm_cap = true;
    ta_update_req.ms_cm2.vbs = false;
    ta_update_req.ms_cm2.vgcs = true;
    ta_update_req.ms_cm2.fc = false;
    ta_update_req.ms_cm2.cm3 = true;
    ta_update_req.ms_cm2.lcsva_cap = false;
    ta_update_req.ms_cm2.ucs2 = true;
    ta_update_req.ms_cm2.solsa = false;
    ta_update_req.ms_cm2.cmsp = true;
    ta_update_req.ms_cm2.a5_3 = false;
    ta_update_req.ms_cm2.a5_2 = true;
    ta_update_req.supported_codecs.N_supported_codecs = 2;
    ta_update_req.supported_codecs.supported_codec[0].sys_id = 0xA5;
    ta_update_req.supported_codecs.supported_codec[0].codec_bitmap = 0x1234;
    ta_update_req.supported_codecs.supported_codec[1].sys_id = 0x5A;
    ta_update_req.supported_codecs.supported_codec[1].codec_bitmap = 0x5678;
    ta_update_req.voice_domain_pref_and_ue_usage_setting.ue_usage_setting = LIBLTE_MME_UE_USAGE_SETTING_DATA_CENTRIC;
    ta_update_req.voice_domain_pref_and_ue_usage_setting.voice_domain_pref = LIBLTE_MME_VOICE_DOMAIN_PREF_PS_ONLY;
    ta_update_req.tmsi_status = LIBLTE_MME_TMSI_STATUS_VALID_TMSI;
    ta_update_req.device_properties = LIBLTE_MME_DEVICE_PROPERTIES_CONFIGURED_FOR_LOW_PRIORITY;
    ta_update_req.gprs_ciphering_ksn = 0x5;
    ta_update_req.non_current_native_nas_ksi_present = false;
    ta_update_req.gprs_ciphering_ksn_present = true;
    ta_update_req.old_p_tmsi_signature_present = false;
    ta_update_req.additional_guti_present = true;
    ta_update_req.nonce_ue_present = false;
    ta_update_req.ue_network_cap_present = true;
    ta_update_req.last_visited_registered_tai_present = false;
    ta_update_req.drx_param_present = true;
    ta_update_req.ue_radio_cap_update_needed_present = false;
    ta_update_req.eps_bearer_context_status_present = true;
    ta_update_req.ms_network_cap_present = false;
    ta_update_req.old_lai_present = true;
    ta_update_req.tmsi_status_present = false;
    ta_update_req.ms_cm2_present = true;
    ta_update_req.ms_cm3_present = false;
    ta_update_req.supported_codecs_present = true;
    ta_update_req.additional_update_type_present = false;
    ta_update_req.voice_domain_pref_and_ue_usage_setting_present = true;
    ta_update_req.old_guti_type_present = false;
    ta_update_req.device_properties_present = true;
    uint8 key[32];
    for(uint32 i=0;i<32; i++)
        key[i] = i;
    LIBLTE_BYTE_MSG_STRUCT sec_msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_tracking_area_update_request_msg(&ta_update_req,
                                                                          LIBLTE_MME_SECURITY_HDR_TYPE_INTEGRITY_AND_CIPHERED,
                                                                          key,
                                                                          0x12,
                                                                          LIBLTE_SECURITY_DIRECTION_DOWNLINK,
                                                                          &sec_msg))
        return -1;
    if(74 != sec_msg.N_bytes)
        return -1;
    if(0x27 != sec_msg.msg[0] || 0xE9 != sec_msg.msg[1] || 0x15 != sec_msg.msg[2] ||
       0xF4 != sec_msg.msg[3] || 0x08 != sec_msg.msg[4] || 0x12 != sec_msg.msg[5] ||
       0x07 != sec_msg.msg[6] || 0x48 != sec_msg.msg[7] || 0x99 != sec_msg.msg[8] ||
       0x0B != sec_msg.msg[9] || 0xF6 != sec_msg.msg[10] || 0x21 != sec_msg.msg[11] ||
       0xF3 != sec_msg.msg[12] || 0x54 != sec_msg.msg[13] || 0xAB != sec_msg.msg[14] ||
       0xCD != sec_msg.msg[15] || 0xEF != sec_msg.msg[16] || 0x12 != sec_msg.msg[17] ||
       0x34 != sec_msg.msg[18] || 0x56 != sec_msg.msg[19] || 0x78 != sec_msg.msg[20] ||
       0x85 != sec_msg.msg[21] || 0x50 != sec_msg.msg[22] || 0x0B != sec_msg.msg[23] ||
       0xF6 != sec_msg.msg[24] || 0x21 != sec_msg.msg[25] || 0xF3 != sec_msg.msg[26] ||
       0x54 != sec_msg.msg[27] || 0xAB != sec_msg.msg[28] || 0xCD != sec_msg.msg[29] ||
       0xEF != sec_msg.msg[30] || 0x12 != sec_msg.msg[31] || 0x34 != sec_msg.msg[32] ||
       0x56 != sec_msg.msg[33] || 0x78 != sec_msg.msg[34] || 0x58 != sec_msg.msg[35] ||
       0x05 != sec_msg.msg[36] || 0x55 != sec_msg.msg[37] || 0x55 != sec_msg.msg[38] ||
       0x55 != sec_msg.msg[39] || 0x55 != sec_msg.msg[40] || 0x04 != sec_msg.msg[41] ||
       0x5C != sec_msg.msg[42] || 0xA5 != sec_msg.msg[43] || 0x64 != sec_msg.msg[44] ||
       0x57 != sec_msg.msg[45] || 0x02 != sec_msg.msg[46] || 0xA0 != sec_msg.msg[47] ||
       0xAA != sec_msg.msg[48] || 0x13 != sec_msg.msg[49] || 0x21 != sec_msg.msg[50] ||
       0x63 != sec_msg.msg[51] || 0x54 != sec_msg.msg[52] || 0x12 != sec_msg.msg[53] ||
       0x34 != sec_msg.msg[54] || 0x11 != sec_msg.msg[55] || 0x03 != sec_msg.msg[56] ||
       0x4A != sec_msg.msg[57] || 0x2A != sec_msg.msg[58] || 0x95 != sec_msg.msg[59] ||
       0x40 != sec_msg.msg[60] || 0x08 != sec_msg.msg[61] || 0xA5 != sec_msg.msg[62] ||
       0x02 != sec_msg.msg[63] || 0x12 != sec_msg.msg[64] || 0x34 != sec_msg.msg[65] ||
       0x5A != sec_msg.msg[66] || 0x02 != sec_msg.msg[67] || 0x56 != sec_msg.msg[68] ||
       0x78 != sec_msg.msg[69] || 0x5D != sec_msg.msg[70] || 0x01 != sec_msg.msg[71] ||
       0x05 != sec_msg.msg[72] || 0xD1 != sec_msg.msg[73])
        return -1;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_tracking_area_update_request_msg(&sec_msg,
                                                                            &ta_update_req))
        return -1;
    if(ta_update_req.eps_update_type.type != LIBLTE_MME_EPS_UPDATE_TYPE_COMBINED_TA_LA_UPDATING ||
       !ta_update_req.eps_update_type.active_flag ||
       ta_update_req.nas_ksi.tsc_flag != LIBLTE_MME_TYPE_OF_SECURITY_CONTEXT_FLAG_MAPPED ||
       ta_update_req.nas_ksi.nas_ksi != 0x1 ||
       ta_update_req.old_guti.type_of_id != LIBLTE_MME_EPS_MOBILE_ID_TYPE_GUTI ||
       ta_update_req.old_guti.guti.m_tmsi != 0x12345678 ||
       ta_update_req.old_guti.guti.mcc.Value()[0].Value() != 1 ||
       ta_update_req.old_guti.guti.mcc.Value()[1].Value() != 2 ||
       ta_update_req.old_guti.guti.mcc.Value()[2].Value() != 3 ||
       ta_update_req.old_guti.guti.mnc.Value()[0].Value() != 4 ||
       ta_update_req.old_guti.guti.mnc.Value()[1].Value() != 5 ||
       ta_update_req.old_guti.guti.mme_group_id != 0xABCD ||
       ta_update_req.old_guti.guti.mme_code != 0xEF ||
       ta_update_req.additional_guti.type_of_id != LIBLTE_MME_EPS_MOBILE_ID_TYPE_GUTI ||
       ta_update_req.additional_guti.guti.m_tmsi != 0x12345678 ||
       ta_update_req.additional_guti.guti.mcc.Value()[0].Value() != 1 ||
       ta_update_req.additional_guti.guti.mcc.Value()[1].Value() != 2 ||
       ta_update_req.additional_guti.guti.mcc.Value()[2].Value() != 3 ||
       ta_update_req.additional_guti.guti.mnc.Value()[0].Value() != 4 ||
       ta_update_req.additional_guti.guti.mnc.Value()[1].Value() != 5 ||
       ta_update_req.additional_guti.guti.mme_group_id != 0xABCD ||
       ta_update_req.additional_guti.guti.mme_code != 0xEF)
        return -1;
    for(uint32 i=0; i<8; i++)
        if(ta_update_req.ue_network_cap.eea[i] != i%2 ||
           ta_update_req.ue_network_cap.eia[i] != i%2 ||
           ta_update_req.ue_network_cap.uea[i] != i%2 ||
           ta_update_req.ue_network_cap.uia[i] != i%2)
            return -1;
    if(!ta_update_req.ue_network_cap.uea_present || ta_update_req.ue_network_cap.ucs2 ||
       !ta_update_req.ue_network_cap.ucs2_present ||
       !ta_update_req.ue_network_cap.uia_present || ta_update_req.ue_network_cap.lpp ||
       !ta_update_req.ue_network_cap.lpp_present || !ta_update_req.ue_network_cap.lcs ||
       !ta_update_req.ue_network_cap.lcs_present || ta_update_req.ue_network_cap.onexsrvcc ||
       !ta_update_req.ue_network_cap.onexsrvcc_present || ta_update_req.ue_network_cap.nf ||
       !ta_update_req.ue_network_cap.nf_present ||
       ta_update_req.drx_param.non_drx_timer != LIBLTE_MME_NON_DRX_TIMER_MAX_8S_NON_DRX_MODE ||
       ta_update_req.drx_param.split_pg_cycle_code != 0xA5 ||
       ta_update_req.drx_param.drx_cycle_len_coeff_and_value != 0x6 ||
       ta_update_req.drx_param.split_on_ccch)
        return -1;
    for(uint32 i=0; i<16; i++)
    {
        if(i%2 && !ta_update_req.eps_bearer_context_status.ebi[i])
            return -1;
        if(!(i%2) && ta_update_req.eps_bearer_context_status.ebi[i])
            return -1;
    }
    if(ta_update_req.old_lai.mcc.Value()[0].Value() != 1 ||
       ta_update_req.old_lai.mcc.Value()[1].Value() != 2 ||
       ta_update_req.old_lai.mcc.Value()[2].Value() != 3 ||
       ta_update_req.old_lai.mnc.Value()[0].Value() != 4 ||
       ta_update_req.old_lai.mnc.Value()[1].Value() != 5 ||
       ta_update_req.old_lai.mnc.Value()[2].Value() != 6 ||
       ta_update_req.old_lai.lac != 0x1234 ||
       ta_update_req.ms_cm2.rev_lev != LIBLTE_MME_REVISION_LEVEL_R99 ||
       ta_update_req.ms_cm2.rf_power_cap != LIBLTE_MME_RF_POWER_CAPABILITY_CLASS_3 ||
       ta_update_req.ms_cm2.ss_screen_ind != LIBLTE_MME_SS_SCREEN_INDICATOR_2 ||
       ta_update_req.ms_cm2.es_ind || !ta_update_req.ms_cm2.a5_1 ||
       ta_update_req.ms_cm2.ps_cap || !ta_update_req.ms_cm2.sm_cap ||
       ta_update_req.ms_cm2.vbs || !ta_update_req.ms_cm2.vgcs ||
       ta_update_req.ms_cm2.fc || !ta_update_req.ms_cm2.cm3 ||
       ta_update_req.ms_cm2.lcsva_cap || !ta_update_req.ms_cm2.ucs2 ||
       ta_update_req.ms_cm2.solsa || !ta_update_req.ms_cm2.cmsp ||
       ta_update_req.ms_cm2.a5_3 || !ta_update_req.ms_cm2.a5_2 ||
       ta_update_req.supported_codecs.N_supported_codecs != 2 ||
       ta_update_req.supported_codecs.supported_codec[0].sys_id != 0xA5 ||
       ta_update_req.supported_codecs.supported_codec[0].codec_bitmap != 0x1234 ||
       ta_update_req.supported_codecs.supported_codec[1].sys_id != 0x5A ||
       ta_update_req.supported_codecs.supported_codec[1].codec_bitmap != 0x5678 ||
       ta_update_req.voice_domain_pref_and_ue_usage_setting.ue_usage_setting != LIBLTE_MME_UE_USAGE_SETTING_DATA_CENTRIC ||
       ta_update_req.voice_domain_pref_and_ue_usage_setting.voice_domain_pref != LIBLTE_MME_VOICE_DOMAIN_PREF_PS_ONLY ||
       ta_update_req.tmsi_status != LIBLTE_MME_TMSI_STATUS_VALID_TMSI ||
       ta_update_req.device_properties != LIBLTE_MME_DEVICE_PROPERTIES_CONFIGURED_FOR_LOW_PRIORITY ||
       ta_update_req.gprs_ciphering_ksn != 0x5 ||
       ta_update_req.non_current_native_nas_ksi_present ||
       !ta_update_req.gprs_ciphering_ksn_present ||
       ta_update_req.old_p_tmsi_signature_present || !ta_update_req.additional_guti_present ||
       ta_update_req.nonce_ue_present || !ta_update_req.ue_network_cap_present ||
       ta_update_req.last_visited_registered_tai_present ||
       !ta_update_req.drx_param_present || ta_update_req.ue_radio_cap_update_needed_present ||
       !ta_update_req.eps_bearer_context_status_present ||
       ta_update_req.ms_network_cap_present || !ta_update_req.old_lai_present ||
       ta_update_req.tmsi_status_present || !ta_update_req.ms_cm2_present ||
       ta_update_req.ms_cm3_present || !ta_update_req.supported_codecs_present ||
       ta_update_req.additional_update_type_present ||
       !ta_update_req.voice_domain_pref_and_ue_usage_setting_present ||
       ta_update_req.old_guti_type_present || !ta_update_req.device_properties_present)
        return -1;
    return 0;
}

int ul_nas_transport_msg_test(void)
{
    LIBLTE_MME_UPLINK_NAS_TRANSPORT_MSG_STRUCT ul_nas_transport;
    ul_nas_transport.nas_msg.N_bytes = 2;
    ul_nas_transport.nas_msg.msg[0] = 0xA5;
    ul_nas_transport.nas_msg.msg[1] = 0x5A;
    uint8 key[32];
    for(uint32 i=0;i<32; i++)
        key[i] = i;
    LIBLTE_BYTE_MSG_STRUCT sec_msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_uplink_nas_transport_msg(&ul_nas_transport,
                                                                  LIBLTE_MME_SECURITY_HDR_TYPE_INTEGRITY_AND_CIPHERED,
                                                                  key,
                                                                  0x12,
                                                                  LIBLTE_SECURITY_DIRECTION_DOWNLINK,
                                                                  &sec_msg))
        return -1;
    if(11 != sec_msg.N_bytes)
        return -1;
    if(0x27 != sec_msg.msg[0] || 0x27 != sec_msg.msg[1] || 0x46 != sec_msg.msg[2] ||
       0x8F != sec_msg.msg[3] || 0xB9 != sec_msg.msg[4] || 0x12 != sec_msg.msg[5] ||
       0x07 != sec_msg.msg[6] || 0x63 != sec_msg.msg[7] || 0x02 != sec_msg.msg[8] ||
       0xA5 != sec_msg.msg[9] || 0x5A != sec_msg.msg[10])
        return -1;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_uplink_nas_transport_msg(&sec_msg,
                                                                    &ul_nas_transport))
        return -1;
    if(ul_nas_transport.nas_msg.N_bytes != 2 ||
       ul_nas_transport.nas_msg.msg[0] != 0xA5 || ul_nas_transport.nas_msg.msg[1] != 0x5A)
        return -1;
    return 0;
}

int dl_generic_nas_transport_msg_test(void)
{
    LIBLTE_MME_DOWNLINK_GENERIC_NAS_TRANSPORT_MSG_STRUCT dl_generic_nas_transport;
    dl_generic_nas_transport.generic_msg_cont.N_bytes = 2;
    dl_generic_nas_transport.generic_msg_cont.msg[0] = 0xA5;
    dl_generic_nas_transport.generic_msg_cont.msg[1] = 0x5A;
    dl_generic_nas_transport.generic_msg_cont_type = LIBLTE_MME_GENERIC_MESSAGE_CONTAINER_TYPE_LPP;
//    dl_generic_nas_transport.add_info.Clear();
    uint8 key[32];
    for(uint32 i=0;i<32; i++)
        key[i] = i;
    LIBLTE_BYTE_MSG_STRUCT sec_msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_downlink_generic_nas_transport_msg(&dl_generic_nas_transport,
                                                                            LIBLTE_MME_SECURITY_HDR_TYPE_INTEGRITY_AND_CIPHERED,
                                                                            key,
                                                                            0x12,
                                                                            LIBLTE_SECURITY_DIRECTION_DOWNLINK,
                                                                            &sec_msg))
        return -1;
    if(13 != sec_msg.N_bytes)
        return -1;
    if(0x27 != sec_msg.msg[0] || 0xC2 != sec_msg.msg[1] || 0xE4 != sec_msg.msg[2] ||
       0x84 != sec_msg.msg[3] || 0x00 != sec_msg.msg[4] || 0x12 != sec_msg.msg[5] ||
       0x07 != sec_msg.msg[6] || 0x68 != sec_msg.msg[7] || 0x01 != sec_msg.msg[8] ||
       0x00 != sec_msg.msg[9] || 0x02 != sec_msg.msg[10] || 0xA5 != sec_msg.msg[11] ||
       0x5A != sec_msg.msg[12])
        return -1;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_downlink_generic_nas_transport_msg(&sec_msg,
                                                                              &dl_generic_nas_transport))
        return -1;
    if(dl_generic_nas_transport.generic_msg_cont.N_bytes != 2 ||
       dl_generic_nas_transport.generic_msg_cont.msg[0] != 0xA5 ||
       dl_generic_nas_transport.generic_msg_cont.msg[1] != 0x5A ||
       dl_generic_nas_transport.generic_msg_cont_type != LIBLTE_MME_GENERIC_MESSAGE_CONTAINER_TYPE_LPP)
//       dl_generic_nas_transport.generic_msg_cont_type != LIBLTE_MME_GENERIC_MESSAGE_CONTAINER_TYPE_LPP ||
//       dl_generic_nas_transport.add_info.IsPresent())
        return -1;
    return 0;
}

int ul_generic_nas_transport_msg_test(void)
{
    LIBLTE_MME_UPLINK_GENERIC_NAS_TRANSPORT_MSG_STRUCT ul_generic_nas_transport;
    ul_generic_nas_transport.generic_msg_cont.N_bytes = 2;
    ul_generic_nas_transport.generic_msg_cont.msg[0] = 0xA5;
    ul_generic_nas_transport.generic_msg_cont.msg[1] = 0x5A;
    ul_generic_nas_transport.generic_msg_cont_type = LIBLTE_MME_GENERIC_MESSAGE_CONTAINER_TYPE_LPP;
//    ul_generic_nas_transport.add_info.Clear();
    uint8 key[32];
    for(uint32 i=0;i<32; i++)
        key[i] = i;
    LIBLTE_BYTE_MSG_STRUCT sec_msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_uplink_generic_nas_transport_msg(&ul_generic_nas_transport,
                                                                          LIBLTE_MME_SECURITY_HDR_TYPE_INTEGRITY_AND_CIPHERED,
                                                                          key,
                                                                          0x12,
                                                                          LIBLTE_SECURITY_DIRECTION_DOWNLINK,
                                                                          &sec_msg))
        return -1;
    if(13 != sec_msg.N_bytes)
        return -1;
    if(0x27 != sec_msg.msg[0] || 0xF5 != sec_msg.msg[1] || 0x3C != sec_msg.msg[2] ||
       0x5A != sec_msg.msg[3] || 0x01 != sec_msg.msg[4] || 0x12 != sec_msg.msg[5] ||
       0x07 != sec_msg.msg[6] || 0x69 != sec_msg.msg[7] || 0x01 != sec_msg.msg[8] ||
       0x00 != sec_msg.msg[9] || 0x02 != sec_msg.msg[10] || 0xA5 != sec_msg.msg[11] ||
       0x5A != sec_msg.msg[12])
        return -1;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_uplink_generic_nas_transport_msg(&sec_msg,
                                                                            &ul_generic_nas_transport))
        return -1;
    if(ul_generic_nas_transport.generic_msg_cont.N_bytes != 2 ||
       ul_generic_nas_transport.generic_msg_cont.msg[0] != 0xA5 ||
       ul_generic_nas_transport.generic_msg_cont.msg[1] != 0x5A ||
       ul_generic_nas_transport.generic_msg_cont_type != LIBLTE_MME_GENERIC_MESSAGE_CONTAINER_TYPE_LPP)
//       ul_generic_nas_transport.generic_msg_cont_type != LIBLTE_MME_GENERIC_MESSAGE_CONTAINER_TYPE_LPP ||
//       ul_generic_nas_transport.add_info.IsPresent())
        return -1;
    return 0;
}

int activate_dedicated_eps_bearer_context_accept_msg_test(void)
{
    LIBLTE_MME_ACTIVATE_DEDICATED_EPS_BEARER_CONTEXT_ACCEPT_MSG_STRUCT act_ded_eps_bearer_context_accept;
    act_ded_eps_bearer_context_accept.eps_bearer_id = 0x5;
    act_ded_eps_bearer_context_accept.proc_transaction_id = 0xA5;
    act_ded_eps_bearer_context_accept.protocol_cnfg_opts_present = false;
    LIBLTE_BYTE_MSG_STRUCT msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_activate_dedicated_eps_bearer_context_accept_msg(&act_ded_eps_bearer_context_accept,
                                                                                          &msg))
        return -1;
    if(3 != msg.N_bytes)
        return -1;
    if(0x52 != msg.msg[0] || 0xA5 != msg.msg[1] || 0xC6 != msg.msg[2])
        return -1;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_activate_dedicated_eps_bearer_context_accept_msg(&msg,
                                                                                            &act_ded_eps_bearer_context_accept))
        return -1;
    if(act_ded_eps_bearer_context_accept.eps_bearer_id != 0x5 ||
       act_ded_eps_bearer_context_accept.proc_transaction_id != 0xA5 ||
       act_ded_eps_bearer_context_accept.protocol_cnfg_opts_present)
        return -1;
    return 0;
}

int activate_dedicated_eps_bearer_context_reject_msg_test(void)
{
    LIBLTE_MME_ACTIVATE_DEDICATED_EPS_BEARER_CONTEXT_REJECT_MSG_STRUCT act_ded_eps_bearer_context_rej;
    act_ded_eps_bearer_context_rej.eps_bearer_id = 0x5;
    act_ded_eps_bearer_context_rej.proc_transaction_id = 0xA5;
    act_ded_eps_bearer_context_rej.esm_cause = LIBLTE_MME_ESM_CAUSE_UNKNOWN_PDN_TYPE;
    act_ded_eps_bearer_context_rej.protocol_cnfg_opts_present = false;
    LIBLTE_BYTE_MSG_STRUCT msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_activate_dedicated_eps_bearer_context_reject_msg(&act_ded_eps_bearer_context_rej,
                                                                                          &msg))
        return -1;
    if(4 != msg.N_bytes)
        return -1;
    if(0x52 != msg.msg[0] || 0xA5 != msg.msg[1] || 0xC7 != msg.msg[2] || 0x1C != msg.msg[3])
        return -1;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_activate_dedicated_eps_bearer_context_reject_msg(&msg,
                                                                                            &act_ded_eps_bearer_context_rej))
        return -1;
    if(act_ded_eps_bearer_context_rej.eps_bearer_id != 0x5 ||
       act_ded_eps_bearer_context_rej.proc_transaction_id != 0xA5 ||
       act_ded_eps_bearer_context_rej.esm_cause != LIBLTE_MME_ESM_CAUSE_UNKNOWN_PDN_TYPE ||
       act_ded_eps_bearer_context_rej.protocol_cnfg_opts_present)
        return -1;
    return 0;
}

int activate_dedicated_eps_bearer_context_request_msg_test(void)
{
    LIBLTE_MME_ACTIVATE_DEDICATED_EPS_BEARER_CONTEXT_REQUEST_MSG_STRUCT act_ded_eps_bearer_context_req;
    act_ded_eps_bearer_context_req.eps_qos.qci = 0xA5;
    act_ded_eps_bearer_context_req.eps_qos.br_present = true;
    act_ded_eps_bearer_context_req.eps_qos.mbr_ul = 0x5A;
    act_ded_eps_bearer_context_req.eps_qos.mbr_dl = 0x12;
    act_ded_eps_bearer_context_req.eps_qos.gbr_ul = 0x34;
    act_ded_eps_bearer_context_req.eps_qos.gbr_dl = 0x56;
    act_ded_eps_bearer_context_req.eps_qos.br_ext_present = false;
    act_ded_eps_bearer_context_req.tft.packet_filter_list_size = 1;
    act_ded_eps_bearer_context_req.tft.parameter_list_size = 2;
    act_ded_eps_bearer_context_req.tft.tft_op_code = LIBLTE_MME_TFT_OPERATION_CODE_DELETE_PACKET_FILTERS_FROM_EXISTING_TFT;
    act_ded_eps_bearer_context_req.tft.packet_filter_list[0].dir = LIBLTE_MME_TFT_PACKET_FILTER_DIRECTION_DOWNLINK_ONLY;
    act_ded_eps_bearer_context_req.tft.packet_filter_list[0].id = 0x5;
    act_ded_eps_bearer_context_req.tft.packet_filter_list[0].eval_precedence = 0x5A;
    act_ded_eps_bearer_context_req.tft.packet_filter_list[0].filter_size = 2;
    act_ded_eps_bearer_context_req.tft.packet_filter_list[0].filter[0] = 0xA5;
    act_ded_eps_bearer_context_req.tft.packet_filter_list[0].filter[1] = 0x5A;
    act_ded_eps_bearer_context_req.tft.parameter_list[0].id = 0xAB;
    act_ded_eps_bearer_context_req.tft.parameter_list[0].parameter_size = 2;
    act_ded_eps_bearer_context_req.tft.parameter_list[0].parameter[0] = 0xA5;
    act_ded_eps_bearer_context_req.tft.parameter_list[0].parameter[1] = 0x5A;
    act_ded_eps_bearer_context_req.tft.parameter_list[1].id = 0xCD;
    act_ded_eps_bearer_context_req.tft.parameter_list[1].parameter_size = 2;
    act_ded_eps_bearer_context_req.tft.parameter_list[1].parameter[0] = 0x12;
    act_ded_eps_bearer_context_req.tft.parameter_list[1].parameter[1] = 0x34;
    act_ded_eps_bearer_context_req.negotiated_qos.delay_class = LIBLTE_MME_QOS_DELAY_CLASS_1;
    act_ded_eps_bearer_context_req.negotiated_qos.reliability_class = LIBLTE_MME_QOS_RELIABILITY_CLASS_UL_SUBSCRIBED;
    act_ded_eps_bearer_context_req.negotiated_qos.peak_throughput = LIBLTE_MME_QOS_PEAK_THROUGHPUT_UP_TO_4000BPS;
    act_ded_eps_bearer_context_req.negotiated_qos.precedence_class = LIBLTE_MME_QOS_PRECEDENCE_CLASS_HIGH_PRIORITY;
    act_ded_eps_bearer_context_req.negotiated_qos.mean_throughput = LIBLTE_MME_QOS_MEAN_THROUGHPUT_100BPH;
    act_ded_eps_bearer_context_req.negotiated_qos.traffic_class = LIBLTE_MME_QOS_TRAFFIC_CLASS_STREAMING;
    act_ded_eps_bearer_context_req.negotiated_qos.delivery_order = LIBLTE_MME_QOS_DELIVERY_ORDER_WITH_DELIVERY_ORDER_YES;
    act_ded_eps_bearer_context_req.negotiated_qos.delivery_of_erroneous_sdu = LIBLTE_MME_QOS_DELIVERY_OF_ERRONEOUS_SDU_NO_DETECT;
    act_ded_eps_bearer_context_req.negotiated_qos.max_sdu_size = 0xA5;
    act_ded_eps_bearer_context_req.negotiated_qos.mbr_ul = 0x5A;
    act_ded_eps_bearer_context_req.negotiated_qos.mbr_dl = 0xA5;
    act_ded_eps_bearer_context_req.negotiated_qos.residual_ber = LIBLTE_MME_QOS_RESIDUAL_BER_1_E_NEG_4;
    act_ded_eps_bearer_context_req.negotiated_qos.sdu_error_ratio = LIBLTE_MME_QOS_SDU_ERROR_RATIO_7_E_NEG_3;
    act_ded_eps_bearer_context_req.negotiated_qos.transfer_delay = 0x15;
    act_ded_eps_bearer_context_req.negotiated_qos.traffic_handling_prio = LIBLTE_MME_QOS_TRAFFIC_HANDLING_PRIORITY_LEVEL_1;
    act_ded_eps_bearer_context_req.negotiated_qos.gbr_ul = 0xA5;
    act_ded_eps_bearer_context_req.negotiated_qos.gbr_dl = 0x5A;
    act_ded_eps_bearer_context_req.negotiated_qos.signalling_ind = LIBLTE_MME_QOS_SIGNALLING_INDICATOR_OPTIMIZED_FOR_SIGNALLING;
    act_ded_eps_bearer_context_req.negotiated_qos.source_stats_descriptor = LIBLTE_MME_QOS_SOURCE_STATISTICS_DESCRIPTOR_SPEECH;
    act_ded_eps_bearer_context_req.negotiated_qos.mbr_dl_ext = 0xA5;
    act_ded_eps_bearer_context_req.negotiated_qos.gbr_dl_ext = 0x5A;
    act_ded_eps_bearer_context_req.negotiated_qos.dl_ext_present = true;
    act_ded_eps_bearer_context_req.negotiated_qos.ul_ext_present = false;
    act_ded_eps_bearer_context_req.protocol_cnfg_opts.N_opts = 2;
    act_ded_eps_bearer_context_req.protocol_cnfg_opts.opt[0].id = LIBLTE_MME_CONFIGURATION_PROTOCOL_OPTIONS_LCP;
    act_ded_eps_bearer_context_req.protocol_cnfg_opts.opt[0].len = 2;
    act_ded_eps_bearer_context_req.protocol_cnfg_opts.opt[0].contents[0] = 0xA5;
    act_ded_eps_bearer_context_req.protocol_cnfg_opts.opt[0].contents[1] = 0x5A;
    act_ded_eps_bearer_context_req.protocol_cnfg_opts.opt[1].id = LIBLTE_MME_CONFIGURATION_PROTOCOL_OPTIONS_PAP;
    act_ded_eps_bearer_context_req.protocol_cnfg_opts.opt[1].len = 4;
    for(uint32 i=0; i<4; i++)
        act_ded_eps_bearer_context_req.protocol_cnfg_opts.opt[1].contents[i] = i;
    act_ded_eps_bearer_context_req.eps_bearer_id = 0x5;
    act_ded_eps_bearer_context_req.proc_transaction_id = 0xA5;
    act_ded_eps_bearer_context_req.linked_eps_bearer_id = LIBLTE_MME_LINKED_EPS_BEARER_IDENTITY_5;
    act_ded_eps_bearer_context_req.radio_prio = LIBLTE_MME_RADIO_PRIORITY_LEVEL_3;
    act_ded_eps_bearer_context_req.transaction_id_present = false;
    act_ded_eps_bearer_context_req.negotiated_qos_present = true;
    act_ded_eps_bearer_context_req.llc_sapi_present = false;
    act_ded_eps_bearer_context_req.radio_prio_present = true;
    act_ded_eps_bearer_context_req.packet_flow_id_present = false;
    act_ded_eps_bearer_context_req.protocol_cnfg_opts_present = true;
    LIBLTE_BYTE_MSG_STRUCT msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_activate_dedicated_eps_bearer_context_request_msg(&act_ded_eps_bearer_context_req,
                                                                                           &msg))
        return -1;
    if(53 != msg.N_bytes)
        return -1;
    if(0x52 != msg.msg[0] || 0xA5 != msg.msg[1] || 0xC5 != msg.msg[2] ||
       0x05 != msg.msg[3] || 0x05 != msg.msg[4] || 0xA5 != msg.msg[5] ||
       0x5A != msg.msg[6] || 0x12 != msg.msg[7] || 0x34 != msg.msg[8] ||
       0x56 != msg.msg[9] || 0x0A != msg.msg[10] || 0xB1 != msg.msg[11] ||
       0x15 != msg.msg[12] || 0xAB != msg.msg[13] || 0x02 != msg.msg[14] ||
       0xA5 != msg.msg[15] || 0x5A != msg.msg[16] || 0xCD != msg.msg[17] ||
       0x02 != msg.msg[18] || 0x12 != msg.msg[19] || 0x34 != msg.msg[20] ||
       0x30 != msg.msg[21] || 0x0E != msg.msg[22] || 0x08 != msg.msg[23] ||
       0x31 != msg.msg[24] || 0x01 != msg.msg[25] || 0x49 != msg.msg[26] ||
       0xA5 != msg.msg[27] || 0x5A != msg.msg[28] || 0xA5 != msg.msg[29] ||
       0x62 != msg.msg[30] || 0x55 != msg.msg[31] || 0xA5 != msg.msg[32] ||
       0x5A != msg.msg[33] || 0x11 != msg.msg[34] || 0xA5 != msg.msg[35] ||
       0x5A != msg.msg[36] || 0x83 != msg.msg[37] || 0x27 != msg.msg[38] ||
       0x0D != msg.msg[39] || 0x80 != msg.msg[40] || 0xC0 != msg.msg[41] ||
       0x21 != msg.msg[42] || 0x02 != msg.msg[43] || 0xA5 != msg.msg[44] ||
       0x5A != msg.msg[45] || 0xC0 != msg.msg[46] || 0x23 != msg.msg[47] ||
       0x04 != msg.msg[48] || 0x00 != msg.msg[49] || 0x01 != msg.msg[50] ||
       0x02 != msg.msg[51] || 0x03 != msg.msg[52])
        return -1;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_activate_dedicated_eps_bearer_context_request_msg(&msg,
                                                                                             &act_ded_eps_bearer_context_req))
        return -1;
    if(act_ded_eps_bearer_context_req.eps_qos.qci != 0xA5 ||
       !act_ded_eps_bearer_context_req.eps_qos.br_present ||
       act_ded_eps_bearer_context_req.eps_qos.mbr_ul != 0x5A ||
       act_ded_eps_bearer_context_req.eps_qos.mbr_dl != 0x12 ||
       act_ded_eps_bearer_context_req.eps_qos.gbr_ul != 0x34 ||
       act_ded_eps_bearer_context_req.eps_qos.gbr_dl != 0x56 ||
       act_ded_eps_bearer_context_req.eps_qos.br_ext_present ||
       act_ded_eps_bearer_context_req.tft.packet_filter_list_size != 1 ||
       act_ded_eps_bearer_context_req.tft.parameter_list_size != 2 ||
       act_ded_eps_bearer_context_req.tft.tft_op_code != LIBLTE_MME_TFT_OPERATION_CODE_DELETE_PACKET_FILTERS_FROM_EXISTING_TFT ||
       act_ded_eps_bearer_context_req.tft.packet_filter_list[0].dir != LIBLTE_MME_TFT_PACKET_FILTER_DIRECTION_DOWNLINK_ONLY ||
       act_ded_eps_bearer_context_req.tft.packet_filter_list[0].id != 0x5 ||
       act_ded_eps_bearer_context_req.tft.packet_filter_list[0].eval_precedence != 0x5A ||
       act_ded_eps_bearer_context_req.tft.packet_filter_list[0].filter_size != 2 ||
       act_ded_eps_bearer_context_req.tft.packet_filter_list[0].filter[0] != 0xA5 ||
       act_ded_eps_bearer_context_req.tft.packet_filter_list[0].filter[1] != 0x5A ||
       act_ded_eps_bearer_context_req.tft.parameter_list[0].id != 0xAB ||
       act_ded_eps_bearer_context_req.tft.parameter_list[0].parameter_size != 2 ||
       act_ded_eps_bearer_context_req.tft.parameter_list[0].parameter[0] != 0xA5 ||
       act_ded_eps_bearer_context_req.tft.parameter_list[0].parameter[1] != 0x5A ||
       act_ded_eps_bearer_context_req.tft.parameter_list[1].id != 0xCD ||
       act_ded_eps_bearer_context_req.tft.parameter_list[1].parameter_size != 2 ||
       act_ded_eps_bearer_context_req.tft.parameter_list[1].parameter[0] != 0x12 ||
       act_ded_eps_bearer_context_req.tft.parameter_list[1].parameter[1] != 0x34 ||
       act_ded_eps_bearer_context_req.negotiated_qos.delay_class != LIBLTE_MME_QOS_DELAY_CLASS_1 ||
       act_ded_eps_bearer_context_req.negotiated_qos.reliability_class != LIBLTE_MME_QOS_RELIABILITY_CLASS_UL_SUBSCRIBED ||
       act_ded_eps_bearer_context_req.negotiated_qos.peak_throughput != LIBLTE_MME_QOS_PEAK_THROUGHPUT_UP_TO_4000BPS ||
       act_ded_eps_bearer_context_req.negotiated_qos.precedence_class != LIBLTE_MME_QOS_PRECEDENCE_CLASS_HIGH_PRIORITY ||
       act_ded_eps_bearer_context_req.negotiated_qos.mean_throughput != LIBLTE_MME_QOS_MEAN_THROUGHPUT_100BPH ||
       act_ded_eps_bearer_context_req.negotiated_qos.traffic_class != LIBLTE_MME_QOS_TRAFFIC_CLASS_STREAMING ||
       act_ded_eps_bearer_context_req.negotiated_qos.delivery_order != LIBLTE_MME_QOS_DELIVERY_ORDER_WITH_DELIVERY_ORDER_YES ||
       act_ded_eps_bearer_context_req.negotiated_qos.delivery_of_erroneous_sdu != LIBLTE_MME_QOS_DELIVERY_OF_ERRONEOUS_SDU_NO_DETECT ||
       act_ded_eps_bearer_context_req.negotiated_qos.max_sdu_size != 0xA5 ||
       act_ded_eps_bearer_context_req.negotiated_qos.mbr_ul != 0x5A ||
       act_ded_eps_bearer_context_req.negotiated_qos.mbr_dl != 0xA5 ||
       act_ded_eps_bearer_context_req.negotiated_qos.residual_ber != LIBLTE_MME_QOS_RESIDUAL_BER_1_E_NEG_4 ||
       act_ded_eps_bearer_context_req.negotiated_qos.sdu_error_ratio != LIBLTE_MME_QOS_SDU_ERROR_RATIO_7_E_NEG_3 ||
       act_ded_eps_bearer_context_req.negotiated_qos.transfer_delay != 0x15 ||
       act_ded_eps_bearer_context_req.negotiated_qos.traffic_handling_prio != LIBLTE_MME_QOS_TRAFFIC_HANDLING_PRIORITY_LEVEL_1 ||
       act_ded_eps_bearer_context_req.negotiated_qos.gbr_ul != 0xA5 ||
       act_ded_eps_bearer_context_req.negotiated_qos.gbr_dl != 0x5A ||
       act_ded_eps_bearer_context_req.negotiated_qos.signalling_ind != LIBLTE_MME_QOS_SIGNALLING_INDICATOR_OPTIMIZED_FOR_SIGNALLING ||
       act_ded_eps_bearer_context_req.negotiated_qos.source_stats_descriptor != LIBLTE_MME_QOS_SOURCE_STATISTICS_DESCRIPTOR_SPEECH ||
       act_ded_eps_bearer_context_req.negotiated_qos.mbr_dl_ext != 0xA5 ||
       act_ded_eps_bearer_context_req.negotiated_qos.gbr_dl_ext != 0x5A ||
       !act_ded_eps_bearer_context_req.negotiated_qos.dl_ext_present ||
       act_ded_eps_bearer_context_req.negotiated_qos.ul_ext_present ||
       act_ded_eps_bearer_context_req.protocol_cnfg_opts.N_opts != 2 ||
       act_ded_eps_bearer_context_req.protocol_cnfg_opts.opt[0].id != LIBLTE_MME_CONFIGURATION_PROTOCOL_OPTIONS_LCP ||
       act_ded_eps_bearer_context_req.protocol_cnfg_opts.opt[0].len != 2 ||
       act_ded_eps_bearer_context_req.protocol_cnfg_opts.opt[0].contents[0] != 0xA5 ||
       act_ded_eps_bearer_context_req.protocol_cnfg_opts.opt[0].contents[1] != 0x5A ||
       act_ded_eps_bearer_context_req.protocol_cnfg_opts.opt[1].id != LIBLTE_MME_CONFIGURATION_PROTOCOL_OPTIONS_PAP ||
       act_ded_eps_bearer_context_req.protocol_cnfg_opts.opt[1].len != 4)
        return -1;
    for(uint32 i=0; i<4; i++)
        if(act_ded_eps_bearer_context_req.protocol_cnfg_opts.opt[1].contents[i] != i)
            return -1;
    if(act_ded_eps_bearer_context_req.eps_bearer_id != 0x5 ||
       act_ded_eps_bearer_context_req.proc_transaction_id != 0xA5 ||
       act_ded_eps_bearer_context_req.linked_eps_bearer_id != LIBLTE_MME_LINKED_EPS_BEARER_IDENTITY_5 ||
       act_ded_eps_bearer_context_req.radio_prio != LIBLTE_MME_RADIO_PRIORITY_LEVEL_3 ||
       act_ded_eps_bearer_context_req.transaction_id_present ||
       !act_ded_eps_bearer_context_req.negotiated_qos_present ||
       act_ded_eps_bearer_context_req.llc_sapi_present ||
       !act_ded_eps_bearer_context_req.radio_prio_present ||
       act_ded_eps_bearer_context_req.packet_flow_id_present ||
       !act_ded_eps_bearer_context_req.protocol_cnfg_opts_present)
        return -1;
    return 0;
}

int activate_default_eps_bearer_context_accept_msg_test(void)
{
    LIBLTE_MME_ACTIVATE_DEFAULT_EPS_BEARER_CONTEXT_ACCEPT_MSG_STRUCT act_def_eps_bearer_context_accept;
    act_def_eps_bearer_context_accept.eps_bearer_id = 0x5;
    act_def_eps_bearer_context_accept.proc_transaction_id = 0xA5;
    act_def_eps_bearer_context_accept.protocol_cnfg_opts_present = false;
    LIBLTE_BYTE_MSG_STRUCT msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_activate_default_eps_bearer_context_accept_msg(&act_def_eps_bearer_context_accept,
                                                                                        &msg))
        return -1;
    if(3 != msg.N_bytes)
        return -1;
    if(0x52 != msg.msg[0] || 0xA5 != msg.msg[1] || 0xC2 != msg.msg[2])
        return -1;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_activate_default_eps_bearer_context_accept_msg(&msg,
                                                                                          &act_def_eps_bearer_context_accept))
        return -1;
    if(act_def_eps_bearer_context_accept.eps_bearer_id != 0x5 ||
       act_def_eps_bearer_context_accept.proc_transaction_id != 0xA5 ||
       act_def_eps_bearer_context_accept.protocol_cnfg_opts_present)
        return -1;
    return 0;
}

int activate_default_eps_bearer_context_reject_msg_test(void)
{
    LIBLTE_MME_ACTIVATE_DEFAULT_EPS_BEARER_CONTEXT_REJECT_MSG_STRUCT act_def_eps_bearer_context_rej;
    act_def_eps_bearer_context_rej.eps_bearer_id = 0x5;
    act_def_eps_bearer_context_rej.proc_transaction_id = 0xA5;
    act_def_eps_bearer_context_rej.esm_cause = LIBLTE_MME_ESM_CAUSE_UNKNOWN_PDN_TYPE;
    act_def_eps_bearer_context_rej.protocol_cnfg_opts_present = false;
    LIBLTE_BYTE_MSG_STRUCT msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_activate_default_eps_bearer_context_reject_msg(&act_def_eps_bearer_context_rej,
                                                                                        &msg))
        return -1;
    if(4 != msg.N_bytes)
        return -1;
    if(0x52 != msg.msg[0] || 0xA5 != msg.msg[1] || 0xC3 != msg.msg[2] || 0x1C != msg.msg[3])
        return -1;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_activate_default_eps_bearer_context_reject_msg(&msg,
                                                                                          &act_def_eps_bearer_context_rej))
        return -1;
    if(act_def_eps_bearer_context_rej.eps_bearer_id != 0x5 ||
       act_def_eps_bearer_context_rej.proc_transaction_id != 0xA5 ||
       act_def_eps_bearer_context_rej.esm_cause != LIBLTE_MME_ESM_CAUSE_UNKNOWN_PDN_TYPE ||
       act_def_eps_bearer_context_rej.protocol_cnfg_opts_present)
        return -1;
    return 0;
}

int activate_default_eps_bearer_context_request_msg_test(void)
{
    LIBLTE_MME_ACTIVATE_DEFAULT_EPS_BEARER_CONTEXT_REQUEST_MSG_STRUCT act_def_eps_bearer_context_req;
    act_def_eps_bearer_context_req.eps_qos.qci = 0xA5;
    act_def_eps_bearer_context_req.eps_qos.br_present = true;
    act_def_eps_bearer_context_req.eps_qos.mbr_ul = 0x5A;
    act_def_eps_bearer_context_req.eps_qos.mbr_dl = 0x12;
    act_def_eps_bearer_context_req.eps_qos.gbr_ul = 0x34;
    act_def_eps_bearer_context_req.eps_qos.gbr_dl = 0x56;
    act_def_eps_bearer_context_req.eps_qos.br_ext_present = false;
    act_def_eps_bearer_context_req.apn.apn = "test";
    act_def_eps_bearer_context_req.pdn_addr.pdn_type = LIBLTE_MME_PDN_TYPE_IPV4;
    for(uint32 i=0; i<4; i++)
        act_def_eps_bearer_context_req.pdn_addr.addr[i] = i;
    act_def_eps_bearer_context_req.negotiated_qos.delay_class = LIBLTE_MME_QOS_DELAY_CLASS_1;
    act_def_eps_bearer_context_req.negotiated_qos.reliability_class = LIBLTE_MME_QOS_RELIABILITY_CLASS_UL_SUBSCRIBED;
    act_def_eps_bearer_context_req.negotiated_qos.peak_throughput = LIBLTE_MME_QOS_PEAK_THROUGHPUT_UP_TO_4000BPS;
    act_def_eps_bearer_context_req.negotiated_qos.precedence_class = LIBLTE_MME_QOS_PRECEDENCE_CLASS_HIGH_PRIORITY;
    act_def_eps_bearer_context_req.negotiated_qos.mean_throughput = LIBLTE_MME_QOS_MEAN_THROUGHPUT_100BPH;
    act_def_eps_bearer_context_req.negotiated_qos.traffic_class = LIBLTE_MME_QOS_TRAFFIC_CLASS_STREAMING;
    act_def_eps_bearer_context_req.negotiated_qos.delivery_order = LIBLTE_MME_QOS_DELIVERY_ORDER_WITH_DELIVERY_ORDER_YES;
    act_def_eps_bearer_context_req.negotiated_qos.delivery_of_erroneous_sdu = LIBLTE_MME_QOS_DELIVERY_OF_ERRONEOUS_SDU_NO_DETECT;
    act_def_eps_bearer_context_req.negotiated_qos.max_sdu_size = 0xA5;
    act_def_eps_bearer_context_req.negotiated_qos.mbr_ul = 0x5A;
    act_def_eps_bearer_context_req.negotiated_qos.mbr_dl = 0xA5;
    act_def_eps_bearer_context_req.negotiated_qos.residual_ber = LIBLTE_MME_QOS_RESIDUAL_BER_1_E_NEG_4;
    act_def_eps_bearer_context_req.negotiated_qos.sdu_error_ratio = LIBLTE_MME_QOS_SDU_ERROR_RATIO_7_E_NEG_3;
    act_def_eps_bearer_context_req.negotiated_qos.transfer_delay = 0x15;
    act_def_eps_bearer_context_req.negotiated_qos.traffic_handling_prio = LIBLTE_MME_QOS_TRAFFIC_HANDLING_PRIORITY_LEVEL_1;
    act_def_eps_bearer_context_req.negotiated_qos.gbr_ul = 0xA5;
    act_def_eps_bearer_context_req.negotiated_qos.gbr_dl = 0x5A;
    act_def_eps_bearer_context_req.negotiated_qos.signalling_ind = LIBLTE_MME_QOS_SIGNALLING_INDICATOR_OPTIMIZED_FOR_SIGNALLING;
    act_def_eps_bearer_context_req.negotiated_qos.source_stats_descriptor = LIBLTE_MME_QOS_SOURCE_STATISTICS_DESCRIPTOR_SPEECH;
    act_def_eps_bearer_context_req.negotiated_qos.mbr_dl_ext = 0xA5;
    act_def_eps_bearer_context_req.negotiated_qos.gbr_dl_ext = 0x5A;
    act_def_eps_bearer_context_req.negotiated_qos.dl_ext_present = true;
    act_def_eps_bearer_context_req.negotiated_qos.ul_ext_present = false;
    act_def_eps_bearer_context_req.apn_ambr.apn_ambr_dl = 0xA5;
    act_def_eps_bearer_context_req.apn_ambr.apn_ambr_ul = 0x5A;
    act_def_eps_bearer_context_req.apn_ambr.ext_present = true;
    act_def_eps_bearer_context_req.apn_ambr.apn_ambr_dl_ext = 0x12;
    act_def_eps_bearer_context_req.apn_ambr.apn_ambr_ul_ext = 0xEF;
    act_def_eps_bearer_context_req.apn_ambr.ext2_present = false;
    act_def_eps_bearer_context_req.protocol_cnfg_opts.N_opts = 2;
    act_def_eps_bearer_context_req.protocol_cnfg_opts.opt[0].id = LIBLTE_MME_CONFIGURATION_PROTOCOL_OPTIONS_LCP;
    act_def_eps_bearer_context_req.protocol_cnfg_opts.opt[0].len = 2;
    act_def_eps_bearer_context_req.protocol_cnfg_opts.opt[0].contents[0] = 0xA5;
    act_def_eps_bearer_context_req.protocol_cnfg_opts.opt[0].contents[1] = 0x5A;
    act_def_eps_bearer_context_req.protocol_cnfg_opts.opt[1].id = LIBLTE_MME_CONFIGURATION_PROTOCOL_OPTIONS_PAP;
    act_def_eps_bearer_context_req.protocol_cnfg_opts.opt[1].len = 4;
    for(uint32 i=0; i<4; i++)
        act_def_eps_bearer_context_req.protocol_cnfg_opts.opt[1].contents[i] = i;
    act_def_eps_bearer_context_req.eps_bearer_id = 0x5;
    act_def_eps_bearer_context_req.proc_transaction_id = 0xA5;
    act_def_eps_bearer_context_req.radio_prio = LIBLTE_MME_RADIO_PRIORITY_LEVEL_3;
    act_def_eps_bearer_context_req.transaction_id_present = false;
    act_def_eps_bearer_context_req.negotiated_qos_present = true;
    act_def_eps_bearer_context_req.llc_sapi_present = false;
    act_def_eps_bearer_context_req.radio_prio_present = true;
    act_def_eps_bearer_context_req.packet_flow_id_present = false;
    act_def_eps_bearer_context_req.apn_ambr_present = true;
    act_def_eps_bearer_context_req.esm_cause_present = false;
    act_def_eps_bearer_context_req.protocol_cnfg_opts_present = true;
    act_def_eps_bearer_context_req.connectivity_type_present = false;
    LIBLTE_BYTE_MSG_STRUCT msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_activate_default_eps_bearer_context_request_msg(&act_def_eps_bearer_context_req,
                                                                                         &msg))
        return -1;
    if(59 != msg.N_bytes)
        return -1;
    if(0x52 != msg.msg[0] || 0xA5 != msg.msg[1] || 0xC1 != msg.msg[2] ||
       0x05 != msg.msg[3] || 0xA5 != msg.msg[4] || 0x5A != msg.msg[5] ||
       0x12 != msg.msg[6] || 0x34 != msg.msg[7] || 0x56 != msg.msg[8] ||
       0x05 != msg.msg[9] || 0x04 != msg.msg[10] || 0x74 != msg.msg[11] ||
       0x65 != msg.msg[12] || 0x73 != msg.msg[13] || 0x74 != msg.msg[14] ||
       0x05 != msg.msg[15] || 0x01 != msg.msg[16] || 0x00 != msg.msg[17] ||
       0x01 != msg.msg[18] || 0x02 != msg.msg[19] || 0x03 != msg.msg[20] ||
       0x30 != msg.msg[21] || 0x0E != msg.msg[22] || 0x08 != msg.msg[23] ||
       0x31 != msg.msg[24] || 0x01 != msg.msg[25] || 0x49 != msg.msg[26] ||
       0xA5 != msg.msg[27] || 0x5A != msg.msg[28] || 0xA5 != msg.msg[29] ||
       0x62 != msg.msg[30] || 0x55 != msg.msg[31] || 0xA5 != msg.msg[32] ||
       0x5A != msg.msg[33] || 0x11 != msg.msg[34] || 0xA5 != msg.msg[35] ||
       0x5A != msg.msg[36] || 0x83 != msg.msg[37] || 0x5E != msg.msg[38] ||
       0x04 != msg.msg[39] || 0xA5 != msg.msg[40] || 0x5A != msg.msg[41] ||
       0x12 != msg.msg[42] || 0xEF != msg.msg[43] || 0x27 != msg.msg[44] ||
       0x0D != msg.msg[45] || 0x80 != msg.msg[46] || 0xC0 != msg.msg[47] ||
       0x21 != msg.msg[48] || 0x02 != msg.msg[49] || 0xA5 != msg.msg[50] ||
       0x5A != msg.msg[51] || 0xC0 != msg.msg[52] || 0x23 != msg.msg[53] ||
       0x04 != msg.msg[54] || 0x00 != msg.msg[55] || 0x01 != msg.msg[56] ||
       0x02 != msg.msg[57] || 0x03 != msg.msg[58])
        return -1;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_activate_default_eps_bearer_context_request_msg(&msg,
                                                                                           &act_def_eps_bearer_context_req))
        return -1;
    if(act_def_eps_bearer_context_req.eps_qos.qci != 0xA5 ||
       !act_def_eps_bearer_context_req.eps_qos.br_present ||
       act_def_eps_bearer_context_req.eps_qos.mbr_ul != 0x5A ||
       act_def_eps_bearer_context_req.eps_qos.mbr_dl != 0x12 ||
       act_def_eps_bearer_context_req.eps_qos.gbr_ul != 0x34 ||
       act_def_eps_bearer_context_req.eps_qos.gbr_dl != 0x56 ||
       act_def_eps_bearer_context_req.eps_qos.br_ext_present ||
       act_def_eps_bearer_context_req.apn.apn != "test" ||
       act_def_eps_bearer_context_req.pdn_addr.pdn_type != LIBLTE_MME_PDN_TYPE_IPV4)
        return -1;
    for(uint32 i=0; i<4; i++)
        if(act_def_eps_bearer_context_req.pdn_addr.addr[i] != i)
            return -1;
    if(act_def_eps_bearer_context_req.negotiated_qos.delay_class != LIBLTE_MME_QOS_DELAY_CLASS_1 ||
       act_def_eps_bearer_context_req.negotiated_qos.reliability_class != LIBLTE_MME_QOS_RELIABILITY_CLASS_UL_SUBSCRIBED ||
       act_def_eps_bearer_context_req.negotiated_qos.peak_throughput != LIBLTE_MME_QOS_PEAK_THROUGHPUT_UP_TO_4000BPS ||
       act_def_eps_bearer_context_req.negotiated_qos.precedence_class != LIBLTE_MME_QOS_PRECEDENCE_CLASS_HIGH_PRIORITY ||
       act_def_eps_bearer_context_req.negotiated_qos.mean_throughput != LIBLTE_MME_QOS_MEAN_THROUGHPUT_100BPH ||
       act_def_eps_bearer_context_req.negotiated_qos.traffic_class != LIBLTE_MME_QOS_TRAFFIC_CLASS_STREAMING ||
       act_def_eps_bearer_context_req.negotiated_qos.delivery_order != LIBLTE_MME_QOS_DELIVERY_ORDER_WITH_DELIVERY_ORDER_YES ||
       act_def_eps_bearer_context_req.negotiated_qos.delivery_of_erroneous_sdu != LIBLTE_MME_QOS_DELIVERY_OF_ERRONEOUS_SDU_NO_DETECT ||
       act_def_eps_bearer_context_req.negotiated_qos.max_sdu_size != 0xA5 ||
       act_def_eps_bearer_context_req.negotiated_qos.mbr_ul != 0x5A ||
       act_def_eps_bearer_context_req.negotiated_qos.mbr_dl != 0xA5 ||
       act_def_eps_bearer_context_req.negotiated_qos.residual_ber != LIBLTE_MME_QOS_RESIDUAL_BER_1_E_NEG_4 ||
       act_def_eps_bearer_context_req.negotiated_qos.sdu_error_ratio != LIBLTE_MME_QOS_SDU_ERROR_RATIO_7_E_NEG_3 ||
       act_def_eps_bearer_context_req.negotiated_qos.transfer_delay != 0x15 ||
       act_def_eps_bearer_context_req.negotiated_qos.traffic_handling_prio != LIBLTE_MME_QOS_TRAFFIC_HANDLING_PRIORITY_LEVEL_1 ||
       act_def_eps_bearer_context_req.negotiated_qos.gbr_ul != 0xA5 ||
       act_def_eps_bearer_context_req.negotiated_qos.gbr_dl != 0x5A ||
       act_def_eps_bearer_context_req.negotiated_qos.signalling_ind != LIBLTE_MME_QOS_SIGNALLING_INDICATOR_OPTIMIZED_FOR_SIGNALLING ||
       act_def_eps_bearer_context_req.negotiated_qos.source_stats_descriptor != LIBLTE_MME_QOS_SOURCE_STATISTICS_DESCRIPTOR_SPEECH ||
       act_def_eps_bearer_context_req.negotiated_qos.mbr_dl_ext != 0xA5 ||
       act_def_eps_bearer_context_req.negotiated_qos.gbr_dl_ext != 0x5A ||
       !act_def_eps_bearer_context_req.negotiated_qos.dl_ext_present ||
       act_def_eps_bearer_context_req.negotiated_qos.ul_ext_present ||
       act_def_eps_bearer_context_req.apn_ambr.apn_ambr_dl != 0xA5 ||
       act_def_eps_bearer_context_req.apn_ambr.apn_ambr_ul != 0x5A ||
       !act_def_eps_bearer_context_req.apn_ambr.ext_present ||
       act_def_eps_bearer_context_req.apn_ambr.apn_ambr_dl_ext != 0x12 ||
       act_def_eps_bearer_context_req.apn_ambr.apn_ambr_ul_ext != 0xEF ||
       act_def_eps_bearer_context_req.apn_ambr.ext2_present ||
       act_def_eps_bearer_context_req.protocol_cnfg_opts.N_opts != 2 ||
       act_def_eps_bearer_context_req.protocol_cnfg_opts.opt[0].id != LIBLTE_MME_CONFIGURATION_PROTOCOL_OPTIONS_LCP ||
       act_def_eps_bearer_context_req.protocol_cnfg_opts.opt[0].len != 2 ||
       act_def_eps_bearer_context_req.protocol_cnfg_opts.opt[0].contents[0] != 0xA5 ||
       act_def_eps_bearer_context_req.protocol_cnfg_opts.opt[0].contents[1] != 0x5A ||
       act_def_eps_bearer_context_req.protocol_cnfg_opts.opt[1].id != LIBLTE_MME_CONFIGURATION_PROTOCOL_OPTIONS_PAP ||
       act_def_eps_bearer_context_req.protocol_cnfg_opts.opt[1].len != 4)
        return -1;
    for(uint32 i=0; i<4; i++)
        if(act_def_eps_bearer_context_req.protocol_cnfg_opts.opt[1].contents[i] != i)
            return -1;
    if(act_def_eps_bearer_context_req.eps_bearer_id != 0x5 ||
       act_def_eps_bearer_context_req.proc_transaction_id != 0xA5 ||
       act_def_eps_bearer_context_req.radio_prio != LIBLTE_MME_RADIO_PRIORITY_LEVEL_3 ||
       act_def_eps_bearer_context_req.transaction_id_present ||
       !act_def_eps_bearer_context_req.negotiated_qos_present ||
       act_def_eps_bearer_context_req.llc_sapi_present ||
       !act_def_eps_bearer_context_req.radio_prio_present ||
       act_def_eps_bearer_context_req.packet_flow_id_present ||
       !act_def_eps_bearer_context_req.apn_ambr_present ||
       act_def_eps_bearer_context_req.esm_cause_present ||
       !act_def_eps_bearer_context_req.protocol_cnfg_opts_present ||
       act_def_eps_bearer_context_req.connectivity_type_present)
        return -1;
    return 0;
}

int bearer_resource_allocation_reject_msg_test(void)
{
    LIBLTE_MME_BEARER_RESOURCE_ALLOCATION_REJECT_MSG_STRUCT bearer_res_alloc_rej;
    bearer_res_alloc_rej.t3496.unit = LIBLTE_MME_GPRS_TIMER_3_UNIT_10_HOURS;
    bearer_res_alloc_rej.t3496.value = 0x15;
    bearer_res_alloc_rej.eps_bearer_id = 0x5;
    bearer_res_alloc_rej.proc_transaction_id = 0xA5;
    bearer_res_alloc_rej.esm_cause = LIBLTE_MME_ESM_CAUSE_UNKNOWN_PDN_TYPE;
    bearer_res_alloc_rej.protocol_cnfg_opts_present = false;
    bearer_res_alloc_rej.t3496_present = true;
    LIBLTE_BYTE_MSG_STRUCT msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_bearer_resource_allocation_reject_msg(&bearer_res_alloc_rej,
                                                                               &msg))
        return -1;
    if(7 != msg.N_bytes)
        return -1;
    if(0x52 != msg.msg[0] || 0xA5 != msg.msg[1] || 0xD5 != msg.msg[2] || 0x1C != msg.msg[3] ||
       0x37 != msg.msg[4] || 0x01 != msg.msg[5] || 0x55 != msg.msg[6])
        return -1;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_bearer_resource_allocation_reject_msg(&msg,
                                                                                 &bearer_res_alloc_rej))
        return -1;
    if(bearer_res_alloc_rej.t3496.unit != LIBLTE_MME_GPRS_TIMER_3_UNIT_10_HOURS ||
       bearer_res_alloc_rej.t3496.value != 0x15 || bearer_res_alloc_rej.eps_bearer_id != 0x5 ||
       bearer_res_alloc_rej.proc_transaction_id != 0xA5 ||
       bearer_res_alloc_rej.esm_cause != LIBLTE_MME_ESM_CAUSE_UNKNOWN_PDN_TYPE ||
       bearer_res_alloc_rej.protocol_cnfg_opts_present ||
       !bearer_res_alloc_rej.t3496_present)
        return -1;
    return 0;
}

int bearer_resource_allocation_request_msg_test(void)
{
    LIBLTE_MME_BEARER_RESOURCE_ALLOCATION_REQUEST_MSG_STRUCT bearer_res_alloc_req;
    bearer_res_alloc_req.tfa.packet_filter_list_size = 1;
    bearer_res_alloc_req.tfa.parameter_list_size = 2;
    bearer_res_alloc_req.tfa.tft_op_code = LIBLTE_MME_TFT_OPERATION_CODE_DELETE_EXISTING_TFT;
    bearer_res_alloc_req.tfa.packet_filter_list[0].dir = LIBLTE_MME_TFT_PACKET_FILTER_DIRECTION_DOWNLINK_ONLY;
    bearer_res_alloc_req.tfa.packet_filter_list[0].id = 0x5;
    bearer_res_alloc_req.tfa.packet_filter_list[0].eval_precedence = 0x5A;
    bearer_res_alloc_req.tfa.packet_filter_list[0].filter_size = 2;
    bearer_res_alloc_req.tfa.packet_filter_list[0].filter[0] = 0xA5;
    bearer_res_alloc_req.tfa.packet_filter_list[0].filter[1] = 0x5A;
    bearer_res_alloc_req.tfa.parameter_list[0].id = 0xAB;
    bearer_res_alloc_req.tfa.parameter_list[0].parameter_size = 2;
    bearer_res_alloc_req.tfa.parameter_list[0].parameter[0] = 0xA5;
    bearer_res_alloc_req.tfa.parameter_list[0].parameter[1] = 0x5A;
    bearer_res_alloc_req.tfa.parameter_list[1].id = 0xCD;
    bearer_res_alloc_req.tfa.parameter_list[1].parameter_size = 2;
    bearer_res_alloc_req.tfa.parameter_list[1].parameter[0] = 0x12;
    bearer_res_alloc_req.tfa.parameter_list[1].parameter[1] = 0x34;
    bearer_res_alloc_req.req_tf_qos.qci = 0xA5;
    bearer_res_alloc_req.req_tf_qos.br_present = true;
    bearer_res_alloc_req.req_tf_qos.mbr_ul = 0x5A;
    bearer_res_alloc_req.req_tf_qos.mbr_dl = 0x12;
    bearer_res_alloc_req.req_tf_qos.gbr_ul = 0x34;
    bearer_res_alloc_req.req_tf_qos.gbr_dl = 0x56;
    bearer_res_alloc_req.req_tf_qos.br_ext_present = false;
    bearer_res_alloc_req.device_properties = LIBLTE_MME_DEVICE_PROPERTIES_CONFIGURED_FOR_LOW_PRIORITY;
    bearer_res_alloc_req.eps_bearer_id = 0x5;
    bearer_res_alloc_req.proc_transaction_id = 0xA5;
    bearer_res_alloc_req.linked_eps_bearer_id = LIBLTE_MME_LINKED_EPS_BEARER_IDENTITY_5;
    bearer_res_alloc_req.protocol_cnfg_opts_present = false;
    bearer_res_alloc_req.device_properties_present = true;
    LIBLTE_BYTE_MSG_STRUCT msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_bearer_resource_allocation_request_msg(&bearer_res_alloc_req,
                                                                                &msg))
        return -1;
    if(26 != msg.N_bytes)
        return -1;
    if(0x52 != msg.msg[0] || 0xA5 != msg.msg[1] || 0xD4 != msg.msg[2] ||
       0x05 != msg.msg[3] || 0x0E != msg.msg[4] || 0x51 != msg.msg[5] ||
       0x15 != msg.msg[6] || 0x5A != msg.msg[7] || 0x02 != msg.msg[8] ||
       0xA5 != msg.msg[9] || 0x5A != msg.msg[10] || 0xAB != msg.msg[11] ||
       0x02 != msg.msg[12] || 0xA5 != msg.msg[13] || 0x5A != msg.msg[14] ||
       0xCD != msg.msg[15] || 0x02 != msg.msg[16] || 0x12 != msg.msg[17] ||
       0x34 != msg.msg[18] || 0x05 != msg.msg[19] || 0xA5 != msg.msg[20] ||
       0x5A != msg.msg[21] || 0x12 != msg.msg[22] || 0x34 != msg.msg[23] ||
       0x56 != msg.msg[24] || 0xC1 != msg.msg[25])
        return -1;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_bearer_resource_allocation_request_msg(&msg,
                                                                                  &bearer_res_alloc_req))
        return -1;
    if(bearer_res_alloc_req.tfa.packet_filter_list_size != 1 ||
       bearer_res_alloc_req.tfa.parameter_list_size != 2 ||
       bearer_res_alloc_req.tfa.tft_op_code != LIBLTE_MME_TFT_OPERATION_CODE_DELETE_EXISTING_TFT ||
       bearer_res_alloc_req.tfa.packet_filter_list[0].dir != LIBLTE_MME_TFT_PACKET_FILTER_DIRECTION_DOWNLINK_ONLY ||
       bearer_res_alloc_req.tfa.packet_filter_list[0].id != 0x5 ||
       bearer_res_alloc_req.tfa.packet_filter_list[0].eval_precedence != 0x5A ||
       bearer_res_alloc_req.tfa.packet_filter_list[0].filter_size != 2 ||
       bearer_res_alloc_req.tfa.packet_filter_list[0].filter[0] != 0xA5 ||
       bearer_res_alloc_req.tfa.packet_filter_list[0].filter[1] != 0x5A ||
       bearer_res_alloc_req.tfa.parameter_list[0].id != 0xAB ||
       bearer_res_alloc_req.tfa.parameter_list[0].parameter_size != 2 ||
       bearer_res_alloc_req.tfa.parameter_list[0].parameter[0] != 0xA5 ||
       bearer_res_alloc_req.tfa.parameter_list[0].parameter[1] != 0x5A ||
       bearer_res_alloc_req.tfa.parameter_list[1].id != 0xCD ||
       bearer_res_alloc_req.tfa.parameter_list[1].parameter_size != 2 ||
       bearer_res_alloc_req.tfa.parameter_list[1].parameter[0] != 0x12 ||
       bearer_res_alloc_req.tfa.parameter_list[1].parameter[1] != 0x34 ||
       bearer_res_alloc_req.req_tf_qos.qci != 0xA5 ||
       !bearer_res_alloc_req.req_tf_qos.br_present ||
       bearer_res_alloc_req.req_tf_qos.mbr_ul != 0x5A ||
       bearer_res_alloc_req.req_tf_qos.mbr_dl != 0x12 ||
       bearer_res_alloc_req.req_tf_qos.gbr_ul != 0x34 ||
       bearer_res_alloc_req.req_tf_qos.gbr_dl != 0x56 ||
       bearer_res_alloc_req.req_tf_qos.br_ext_present ||
       bearer_res_alloc_req.device_properties != LIBLTE_MME_DEVICE_PROPERTIES_CONFIGURED_FOR_LOW_PRIORITY ||
       bearer_res_alloc_req.eps_bearer_id != 0x5 ||
       bearer_res_alloc_req.proc_transaction_id != 0xA5 ||
       bearer_res_alloc_req.linked_eps_bearer_id != LIBLTE_MME_LINKED_EPS_BEARER_IDENTITY_5 ||
       bearer_res_alloc_req.protocol_cnfg_opts_present ||
       !bearer_res_alloc_req.device_properties_present)
        return -1;
    return 0;
}

int bearer_resource_modification_reject_msg_test(void)
{
    LIBLTE_MME_BEARER_RESOURCE_MODIFICATION_REJECT_MSG_STRUCT bearer_res_mod_rej;
    bearer_res_mod_rej.t3496.unit = LIBLTE_MME_GPRS_TIMER_3_UNIT_10_HOURS;
    bearer_res_mod_rej.t3496.value = 0x15;
    bearer_res_mod_rej.eps_bearer_id = 0x5;
    bearer_res_mod_rej.proc_transaction_id = 0xA5;
    bearer_res_mod_rej.esm_cause = LIBLTE_MME_ESM_CAUSE_UNKNOWN_PDN_TYPE;
    bearer_res_mod_rej.protocol_cnfg_opts_present = false;
    bearer_res_mod_rej.t3496_present = true;
    LIBLTE_BYTE_MSG_STRUCT msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_bearer_resource_modification_reject_msg(&bearer_res_mod_rej,
                                                                                 &msg))
        return -1;
    if(7 != msg.N_bytes)
        return -1;
    if(0x52 != msg.msg[0] || 0xA5 != msg.msg[1] || 0xD7 != msg.msg[2] || 0x1C != msg.msg[3] ||
       0x37 != msg.msg[4] || 0x01 != msg.msg[5] || 0x55 != msg.msg[6])
        return -1;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_bearer_resource_modification_reject_msg(&msg,
                                                                                   &bearer_res_mod_rej))
        return -1;
    if(bearer_res_mod_rej.t3496.unit != LIBLTE_MME_GPRS_TIMER_3_UNIT_10_HOURS ||
       bearer_res_mod_rej.t3496.value != 0x15 || bearer_res_mod_rej.eps_bearer_id != 0x5 ||
       bearer_res_mod_rej.proc_transaction_id != 0xA5 ||
       bearer_res_mod_rej.esm_cause != LIBLTE_MME_ESM_CAUSE_UNKNOWN_PDN_TYPE ||
       bearer_res_mod_rej.protocol_cnfg_opts_present ||
       !bearer_res_mod_rej.t3496_present)
        return -1;
    return 0;
}

int bearer_resource_modification_request_msg_test(void)
{
    LIBLTE_MME_BEARER_RESOURCE_MODIFICATION_REQUEST_MSG_STRUCT bearer_res_mod_req;
    bearer_res_mod_req.tfa.packet_filter_list_size = 1;
    bearer_res_mod_req.tfa.parameter_list_size = 2;
    bearer_res_mod_req.tfa.tft_op_code = LIBLTE_MME_TFT_OPERATION_CODE_DELETE_EXISTING_TFT;
    bearer_res_mod_req.tfa.packet_filter_list[0].dir = LIBLTE_MME_TFT_PACKET_FILTER_DIRECTION_DOWNLINK_ONLY;
    bearer_res_mod_req.tfa.packet_filter_list[0].id = 0x5;
    bearer_res_mod_req.tfa.packet_filter_list[0].eval_precedence = 0x5A;
    bearer_res_mod_req.tfa.packet_filter_list[0].filter_size = 2;
    bearer_res_mod_req.tfa.packet_filter_list[0].filter[0] = 0xA5;
    bearer_res_mod_req.tfa.packet_filter_list[0].filter[1] = 0x5A;
    bearer_res_mod_req.tfa.parameter_list[0].id = 0xAB;
    bearer_res_mod_req.tfa.parameter_list[0].parameter_size = 2;
    bearer_res_mod_req.tfa.parameter_list[0].parameter[0] = 0xA5;
    bearer_res_mod_req.tfa.parameter_list[0].parameter[1] = 0x5A;
    bearer_res_mod_req.tfa.parameter_list[1].id = 0xCD;
    bearer_res_mod_req.tfa.parameter_list[1].parameter_size = 2;
    bearer_res_mod_req.tfa.parameter_list[1].parameter[0] = 0x12;
    bearer_res_mod_req.tfa.parameter_list[1].parameter[1] = 0x34;
    bearer_res_mod_req.req_tf_qos.qci = 0xA5;
    bearer_res_mod_req.req_tf_qos.br_present = true;
    bearer_res_mod_req.req_tf_qos.mbr_ul = 0x5A;
    bearer_res_mod_req.req_tf_qos.mbr_dl = 0x12;
    bearer_res_mod_req.req_tf_qos.gbr_ul = 0x34;
    bearer_res_mod_req.req_tf_qos.gbr_dl = 0x56;
    bearer_res_mod_req.req_tf_qos.br_ext_present = false;
    bearer_res_mod_req.device_properties = LIBLTE_MME_DEVICE_PROPERTIES_CONFIGURED_FOR_LOW_PRIORITY;
    bearer_res_mod_req.eps_bearer_id = 0x5;
    bearer_res_mod_req.proc_transaction_id = 0xA5;
    bearer_res_mod_req.eps_bearer_id_for_packet_filter = LIBLTE_MME_LINKED_EPS_BEARER_IDENTITY_5;
    bearer_res_mod_req.esm_cause = LIBLTE_MME_ESM_CAUSE_UNUSED;
    bearer_res_mod_req.esm_cause_present = true;
    bearer_res_mod_req.protocol_cnfg_opts_present = false;
    bearer_res_mod_req.device_properties_present = true;
    LIBLTE_BYTE_MSG_STRUCT msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_bearer_resource_modification_request_msg(&bearer_res_mod_req,
                                                                                  &msg))
        return -1;
    if(29 != msg.N_bytes)
        return -1;
    if(0x52 != msg.msg[0] || 0xA5 != msg.msg[1] || 0xD6 != msg.msg[2] ||
       0x05 != msg.msg[3] || 0x0E != msg.msg[4] || 0x51 != msg.msg[5] ||
       0x15 != msg.msg[6] || 0x5A != msg.msg[7] || 0x02 != msg.msg[8] ||
       0xA5 != msg.msg[9] || 0x5A != msg.msg[10] || 0xAB != msg.msg[11] ||
       0x02 != msg.msg[12] || 0xA5 != msg.msg[13] || 0x5A != msg.msg[14] ||
       0xCD != msg.msg[15] || 0x02 != msg.msg[16] || 0x12 != msg.msg[17] ||
       0x34 != msg.msg[18] || 0x5B != msg.msg[19] || 0x05 != msg.msg[20] ||
       0xA5 != msg.msg[21] || 0x5A != msg.msg[22] || 0x12 != msg.msg[23] ||
       0x34 != msg.msg[24] || 0x56 != msg.msg[25] || 0x58 != msg.msg[26] ||
       0x2E != msg.msg[27] || 0xC1 != msg.msg[28])
        return -1;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_bearer_resource_modification_request_msg(&msg,
                                                                                    &bearer_res_mod_req))
        return -1;
    if(bearer_res_mod_req.tfa.packet_filter_list_size != 1 ||
       bearer_res_mod_req.tfa.parameter_list_size != 2 ||
       bearer_res_mod_req.tfa.tft_op_code != LIBLTE_MME_TFT_OPERATION_CODE_DELETE_EXISTING_TFT ||
       bearer_res_mod_req.tfa.packet_filter_list[0].dir != LIBLTE_MME_TFT_PACKET_FILTER_DIRECTION_DOWNLINK_ONLY ||
       bearer_res_mod_req.tfa.packet_filter_list[0].id != 0x5 ||
       bearer_res_mod_req.tfa.packet_filter_list[0].eval_precedence != 0x5A ||
       bearer_res_mod_req.tfa.packet_filter_list[0].filter_size != 2 ||
       bearer_res_mod_req.tfa.packet_filter_list[0].filter[0] != 0xA5 ||
       bearer_res_mod_req.tfa.packet_filter_list[0].filter[1] != 0x5A ||
       bearer_res_mod_req.tfa.parameter_list[0].id != 0xAB ||
       bearer_res_mod_req.tfa.parameter_list[0].parameter_size != 2 ||
       bearer_res_mod_req.tfa.parameter_list[0].parameter[0] != 0xA5 ||
       bearer_res_mod_req.tfa.parameter_list[0].parameter[1] != 0x5A ||
       bearer_res_mod_req.tfa.parameter_list[1].id != 0xCD ||
       bearer_res_mod_req.tfa.parameter_list[1].parameter_size != 2 ||
       bearer_res_mod_req.tfa.parameter_list[1].parameter[0] != 0x12 ||
       bearer_res_mod_req.tfa.parameter_list[1].parameter[1] != 0x34 ||
       bearer_res_mod_req.req_tf_qos.qci != 0xA5 ||
       !bearer_res_mod_req.req_tf_qos.br_present ||
       bearer_res_mod_req.req_tf_qos.mbr_ul != 0x5A ||
       bearer_res_mod_req.req_tf_qos.mbr_dl != 0x12 ||
       bearer_res_mod_req.req_tf_qos.gbr_ul != 0x34 ||
       bearer_res_mod_req.req_tf_qos.gbr_dl != 0x56 ||
       bearer_res_mod_req.req_tf_qos.br_ext_present ||
       bearer_res_mod_req.device_properties != LIBLTE_MME_DEVICE_PROPERTIES_CONFIGURED_FOR_LOW_PRIORITY ||
       bearer_res_mod_req.eps_bearer_id != 0x5 ||
       bearer_res_mod_req.proc_transaction_id != 0xA5 ||
       bearer_res_mod_req.eps_bearer_id_for_packet_filter != LIBLTE_MME_LINKED_EPS_BEARER_IDENTITY_5 ||
       bearer_res_mod_req.esm_cause != LIBLTE_MME_ESM_CAUSE_UNUSED ||
       !bearer_res_mod_req.esm_cause_present ||
       bearer_res_mod_req.protocol_cnfg_opts_present ||
       !bearer_res_mod_req.device_properties_present)
        return -1;
    return 0;
}

int deactivate_eps_bearer_context_accept_msg_test(void)
{
    LIBLTE_MME_DEACTIVATE_EPS_BEARER_CONTEXT_ACCEPT_MSG_STRUCT deact_eps_bearer_context_accept;
    deact_eps_bearer_context_accept.eps_bearer_id = 0x5;
    deact_eps_bearer_context_accept.proc_transaction_id = 0xA5;
    deact_eps_bearer_context_accept.protocol_cnfg_opts_present = false;
    LIBLTE_BYTE_MSG_STRUCT msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_deactivate_eps_bearer_context_accept_msg(&deact_eps_bearer_context_accept,
                                                                                  &msg))
        return -1;
    if(3 != msg.N_bytes)
        return -1;
    if(0x52 != msg.msg[0] || 0xA5 != msg.msg[1] || 0xCE != msg.msg[2])
        return -1;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_deactivate_eps_bearer_context_accept_msg(&msg,
                                                                                    &deact_eps_bearer_context_accept))
        return -1;
    if(deact_eps_bearer_context_accept.eps_bearer_id != 0x5 ||
       deact_eps_bearer_context_accept.proc_transaction_id != 0xA5 ||
       deact_eps_bearer_context_accept.protocol_cnfg_opts_present)
        return -1;
    return 0;
}

int deactivate_eps_bearer_context_request_msg_test(void)
{
    LIBLTE_MME_DEACTIVATE_EPS_BEARER_CONTEXT_REQUEST_MSG_STRUCT deact_eps_bearer_context_req;
    deact_eps_bearer_context_req.eps_bearer_id = 0x5;
    deact_eps_bearer_context_req.proc_transaction_id = 0xA5;
    deact_eps_bearer_context_req.esm_cause = LIBLTE_MME_ESM_CAUSE_UNUSED;
    deact_eps_bearer_context_req.protocol_cnfg_opts_present = false;
    LIBLTE_BYTE_MSG_STRUCT msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_deactivate_eps_bearer_context_request_msg(&deact_eps_bearer_context_req,
                                                                                   &msg))
        return -1;
    if(4 != msg.N_bytes)
        return -1;
    if(0x52 != msg.msg[0] || 0xA5 != msg.msg[1] || 0xCD != msg.msg[2] || 0x2E != msg.msg[3])
        return -1;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_deactivate_eps_bearer_context_request_msg(&msg,
                                                                                     &deact_eps_bearer_context_req))
        return -1;
    if(deact_eps_bearer_context_req.eps_bearer_id != 0x5 ||
       deact_eps_bearer_context_req.proc_transaction_id != 0xA5 ||
       deact_eps_bearer_context_req.esm_cause != LIBLTE_MME_ESM_CAUSE_UNUSED ||
       deact_eps_bearer_context_req.protocol_cnfg_opts_present)
        return -1;
    return 0;
}

int esm_information_request_msg_test(void)
{
    LIBLTE_MME_ESM_INFORMATION_REQUEST_MSG_STRUCT esm_info_req;
    esm_info_req.eps_bearer_id = 0x5;
    esm_info_req.proc_transaction_id = 0xA5;
    LIBLTE_BYTE_MSG_STRUCT msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_esm_information_request_msg(&esm_info_req, &msg))
        return -1;
    if(3 != msg.N_bytes)
        return -1;
    if(0x52 != msg.msg[0] || 0xA5 != msg.msg[1] || 0xD9 != msg.msg[2])
        return -1;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_esm_information_request_msg(&msg, &esm_info_req))
        return -1;
    if(esm_info_req.eps_bearer_id != 0x5 ||
       esm_info_req.proc_transaction_id != 0xA5)
        return -1;
    return 0;
}

int esm_information_response_msg_test(void)
{
    LIBLTE_MME_ESM_INFORMATION_RESPONSE_MSG_STRUCT esm_info_resp;
    esm_info_resp.apn.apn = "test";
    esm_info_resp.eps_bearer_id = 0x5;
    esm_info_resp.proc_transaction_id = 0xA5;
    esm_info_resp.apn_present = true;
    esm_info_resp.protocol_cnfg_opts_present = false;
    LIBLTE_BYTE_MSG_STRUCT msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_esm_information_response_msg(&esm_info_resp, &msg))
        return -1;
    if(10 != msg.N_bytes)
        return -1;
    if(0x52 != msg.msg[0] || 0xA5 != msg.msg[1] || 0xDA != msg.msg[2] || 0x28 != msg.msg[3] ||
       0x05 != msg.msg[4] || 0x04 != msg.msg[5] || 0x74 != msg.msg[6] || 0x65 != msg.msg[7] ||
       0x73 != msg.msg[8] || 0x74 != msg.msg[9])
        return -1;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_esm_information_response_msg(&msg, &esm_info_resp))
        return -1;
    if(esm_info_resp.apn.apn != "test" || esm_info_resp.eps_bearer_id != 0x5 ||
       esm_info_resp.proc_transaction_id != 0xA5 || !esm_info_resp.apn_present ||
       esm_info_resp.protocol_cnfg_opts_present)
        return -1;
    return 0;
}

int esm_status_msg_test(void)
{
    LIBLTE_MME_ESM_STATUS_MSG_STRUCT esm_status;
    esm_status.eps_bearer_id = 0x5;
    esm_status.proc_transaction_id = 0xA5;
    esm_status.esm_cause = LIBLTE_MME_ESM_CAUSE_UNUSED;
    LIBLTE_BYTE_MSG_STRUCT msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_esm_status_msg(&esm_status, &msg))
        return -1;
    if(4 != msg.N_bytes)
        return -1;
    if(0x52 != msg.msg[0] || 0xA5 != msg.msg[1] || 0xE8 != msg.msg[2] || 0x2E != msg.msg[3])
        return -1;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_esm_status_msg(&msg, &esm_status))
        return -1;
    if(esm_status.eps_bearer_id != 0x5 || esm_status.proc_transaction_id != 0xA5 ||
       esm_status.esm_cause != LIBLTE_MME_ESM_CAUSE_UNUSED)
        return -1;
    return 0;
}

int modify_eps_bearer_context_accept_msg_test(void)
{
    LIBLTE_MME_MODIFY_EPS_BEARER_CONTEXT_ACCEPT_MSG_STRUCT mod_eps_bearer_context_accept;
    mod_eps_bearer_context_accept.eps_bearer_id = 0x5;
    mod_eps_bearer_context_accept.proc_transaction_id = 0xA5;
    mod_eps_bearer_context_accept.protocol_cnfg_opts_present = false;
    LIBLTE_BYTE_MSG_STRUCT msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_modify_eps_bearer_context_accept_msg(&mod_eps_bearer_context_accept,
                                                                              &msg))
        return -1;
    if(3 != msg.N_bytes)
        return -1;
    if(0x52 != msg.msg[0] || 0xA5 != msg.msg[1] || 0xCA != msg.msg[2])
        return -1;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_modify_eps_bearer_context_accept_msg(&msg,
                                                                                &mod_eps_bearer_context_accept))
        return -1;
    if(mod_eps_bearer_context_accept.eps_bearer_id != 0x5 ||
       mod_eps_bearer_context_accept.proc_transaction_id != 0xA5 ||
       mod_eps_bearer_context_accept.protocol_cnfg_opts_present)
        return -1;
    return 0;
}

int modify_eps_bearer_context_reject_msg_test(void)
{
    LIBLTE_MME_MODIFY_EPS_BEARER_CONTEXT_REJECT_MSG_STRUCT mod_eps_bearer_context_rej;
    mod_eps_bearer_context_rej.eps_bearer_id = 0x5;
    mod_eps_bearer_context_rej.proc_transaction_id = 0xA5;
    mod_eps_bearer_context_rej.esm_cause = LIBLTE_MME_ESM_CAUSE_UNUSED;
    mod_eps_bearer_context_rej.protocol_cnfg_opts_present = false;
    LIBLTE_BYTE_MSG_STRUCT msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_modify_eps_bearer_context_reject_msg(&mod_eps_bearer_context_rej,
                                                                              &msg))
        return -1;
    if(4 != msg.N_bytes)
        return -1;
    if(0x52 != msg.msg[0] || 0xA5 != msg.msg[1] || 0xCB != msg.msg[2] || 0x2E != msg.msg[3])
        return -1;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_modify_eps_bearer_context_reject_msg(&msg,
                                                                                &mod_eps_bearer_context_rej))
        return -1;
    if(mod_eps_bearer_context_rej.eps_bearer_id != 0x5 ||
       mod_eps_bearer_context_rej.proc_transaction_id != 0xA5 ||
       mod_eps_bearer_context_rej.esm_cause != LIBLTE_MME_ESM_CAUSE_UNUSED ||
       mod_eps_bearer_context_rej.protocol_cnfg_opts_present)
        return -1;
    return 0;
}

int modify_eps_bearer_context_request_msg_test(void)
{
    LIBLTE_MME_MODIFY_EPS_BEARER_CONTEXT_REQUEST_MSG_STRUCT mod_eps_bearer_context_req;
    mod_eps_bearer_context_req.tft.packet_filter_list_size = 1;
    mod_eps_bearer_context_req.tft.parameter_list_size = 2;
    mod_eps_bearer_context_req.tft.tft_op_code = LIBLTE_MME_TFT_OPERATION_CODE_DELETE_PACKET_FILTERS_FROM_EXISTING_TFT;
    mod_eps_bearer_context_req.tft.packet_filter_list[0].dir = LIBLTE_MME_TFT_PACKET_FILTER_DIRECTION_DOWNLINK_ONLY;
    mod_eps_bearer_context_req.tft.packet_filter_list[0].id = 0x5;
    mod_eps_bearer_context_req.tft.packet_filter_list[0].eval_precedence = 0x5A;
    mod_eps_bearer_context_req.tft.packet_filter_list[0].filter_size = 2;
    mod_eps_bearer_context_req.tft.packet_filter_list[0].filter[0] = 0xA5;
    mod_eps_bearer_context_req.tft.packet_filter_list[0].filter[1] = 0x5A;
    mod_eps_bearer_context_req.tft.parameter_list[0].id = 0xAB;
    mod_eps_bearer_context_req.tft.parameter_list[0].parameter_size = 2;
    mod_eps_bearer_context_req.tft.parameter_list[0].parameter[0] = 0xA5;
    mod_eps_bearer_context_req.tft.parameter_list[0].parameter[1] = 0x5A;
    mod_eps_bearer_context_req.tft.parameter_list[1].id = 0xCD;
    mod_eps_bearer_context_req.tft.parameter_list[1].parameter_size = 2;
    mod_eps_bearer_context_req.tft.parameter_list[1].parameter[0] = 0x12;
    mod_eps_bearer_context_req.tft.parameter_list[1].parameter[1] = 0x34;
    mod_eps_bearer_context_req.protocol_cnfg_opts.N_opts = 2;
    mod_eps_bearer_context_req.protocol_cnfg_opts.opt[0].id = LIBLTE_MME_CONFIGURATION_PROTOCOL_OPTIONS_LCP;
    mod_eps_bearer_context_req.protocol_cnfg_opts.opt[0].len = 2;
    mod_eps_bearer_context_req.protocol_cnfg_opts.opt[0].contents[0] = 0xA5;
    mod_eps_bearer_context_req.protocol_cnfg_opts.opt[0].contents[1] = 0x5A;
    mod_eps_bearer_context_req.protocol_cnfg_opts.opt[1].id = LIBLTE_MME_CONFIGURATION_PROTOCOL_OPTIONS_PAP;
    mod_eps_bearer_context_req.protocol_cnfg_opts.opt[1].len = 4;
    for(uint32 i=0; i<4; i++)
        mod_eps_bearer_context_req.protocol_cnfg_opts.opt[1].contents[i] = i;
    mod_eps_bearer_context_req.eps_bearer_id = 0x5;
    mod_eps_bearer_context_req.proc_transaction_id = 0xA5;
    mod_eps_bearer_context_req.negotiated_llc_sapi = LIBLTE_MME_LLC_SAPI_3;
    mod_eps_bearer_context_req.packet_flow_id = LIBLTE_MME_PACKET_FLOW_ID_SMS;
    mod_eps_bearer_context_req.new_eps_qos_present = false;
    mod_eps_bearer_context_req.tft_present = true;
    mod_eps_bearer_context_req.new_qos_present = false;
    mod_eps_bearer_context_req.negotiated_llc_sapi_present = true;
    mod_eps_bearer_context_req.radio_prio_present = false;
    mod_eps_bearer_context_req.packet_flow_id_present = true;
    mod_eps_bearer_context_req.apn_ambr_present = false;
    mod_eps_bearer_context_req.protocol_cnfg_opts_present = true;
    LIBLTE_BYTE_MSG_STRUCT msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_modify_eps_bearer_context_request_msg(&mod_eps_bearer_context_req,
                                                                               &msg))
        return -1;
    if(35 != msg.N_bytes)
        return -1;
    if(0x52 != msg.msg[0] || 0xA5 != msg.msg[1] || 0xC9 != msg.msg[2] ||
       0x36 != msg.msg[3] || 0x0A != msg.msg[4] || 0xB1 != msg.msg[5] ||
       0x15 != msg.msg[6] || 0xAB != msg.msg[7] || 0x02 != msg.msg[8] ||
       0xA5 != msg.msg[9] || 0x5A != msg.msg[10] || 0xCD != msg.msg[11] ||
       0x02 != msg.msg[12] || 0x12 != msg.msg[13] || 0x34 != msg.msg[14] ||
       0x32 != msg.msg[15] || 0x03 != msg.msg[16] || 0x34 != msg.msg[17] ||
       0x01 != msg.msg[18] || 0x02 != msg.msg[19] || 0x27 != msg.msg[20] ||
       0x0D != msg.msg[21] || 0x80 != msg.msg[22] || 0xC0 != msg.msg[23] ||
       0x21 != msg.msg[24] || 0x02 != msg.msg[25] || 0xA5 != msg.msg[26] ||
       0x5A != msg.msg[27] || 0xC0 != msg.msg[28] || 0x23 != msg.msg[29] ||
       0x04 != msg.msg[30] || 0x00 != msg.msg[31] || 0x01 != msg.msg[32] ||
       0x02 != msg.msg[33] || 0x03 != msg.msg[34])
        return -1;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_modify_eps_bearer_context_request_msg(&msg,
                                                                                 &mod_eps_bearer_context_req))
        return -1;
    if(mod_eps_bearer_context_req.tft.packet_filter_list_size != 1 ||
       mod_eps_bearer_context_req.tft.parameter_list_size != 2 ||
       mod_eps_bearer_context_req.tft.tft_op_code != LIBLTE_MME_TFT_OPERATION_CODE_DELETE_PACKET_FILTERS_FROM_EXISTING_TFT ||
       mod_eps_bearer_context_req.tft.packet_filter_list[0].dir != LIBLTE_MME_TFT_PACKET_FILTER_DIRECTION_DOWNLINK_ONLY ||
       mod_eps_bearer_context_req.tft.packet_filter_list[0].id != 0x5 ||
       mod_eps_bearer_context_req.tft.packet_filter_list[0].eval_precedence != 0x5A ||
       mod_eps_bearer_context_req.tft.packet_filter_list[0].filter_size != 2 ||
       mod_eps_bearer_context_req.tft.packet_filter_list[0].filter[0] != 0xA5 ||
       mod_eps_bearer_context_req.tft.packet_filter_list[0].filter[1] != 0x5A ||
       mod_eps_bearer_context_req.tft.parameter_list[0].id != 0xAB ||
       mod_eps_bearer_context_req.tft.parameter_list[0].parameter_size != 2 ||
       mod_eps_bearer_context_req.tft.parameter_list[0].parameter[0] != 0xA5 ||
       mod_eps_bearer_context_req.tft.parameter_list[0].parameter[1] != 0x5A ||
       mod_eps_bearer_context_req.tft.parameter_list[1].id != 0xCD ||
       mod_eps_bearer_context_req.tft.parameter_list[1].parameter_size != 2 ||
       mod_eps_bearer_context_req.tft.parameter_list[1].parameter[0] != 0x12 ||
       mod_eps_bearer_context_req.tft.parameter_list[1].parameter[1] != 0x34 ||
       mod_eps_bearer_context_req.protocol_cnfg_opts.N_opts != 2 ||
       mod_eps_bearer_context_req.protocol_cnfg_opts.opt[0].id != LIBLTE_MME_CONFIGURATION_PROTOCOL_OPTIONS_LCP ||
       mod_eps_bearer_context_req.protocol_cnfg_opts.opt[0].len != 2 ||
       mod_eps_bearer_context_req.protocol_cnfg_opts.opt[0].contents[0] != 0xA5 ||
       mod_eps_bearer_context_req.protocol_cnfg_opts.opt[0].contents[1] != 0x5A ||
       mod_eps_bearer_context_req.protocol_cnfg_opts.opt[1].id != LIBLTE_MME_CONFIGURATION_PROTOCOL_OPTIONS_PAP ||
       mod_eps_bearer_context_req.protocol_cnfg_opts.opt[1].len != 4)
        return -1;
    for(uint32 i=0; i<4; i++)
        if(mod_eps_bearer_context_req.protocol_cnfg_opts.opt[1].contents[i] != i)
            return -1;
    if(mod_eps_bearer_context_req.eps_bearer_id != 0x5 ||
       mod_eps_bearer_context_req.proc_transaction_id != 0xA5 ||
       mod_eps_bearer_context_req.negotiated_llc_sapi != LIBLTE_MME_LLC_SAPI_3 ||
       mod_eps_bearer_context_req.packet_flow_id != LIBLTE_MME_PACKET_FLOW_ID_SMS ||
       mod_eps_bearer_context_req.new_eps_qos_present ||
       !mod_eps_bearer_context_req.tft_present ||
       mod_eps_bearer_context_req.new_qos_present ||
       !mod_eps_bearer_context_req.negotiated_llc_sapi_present ||
       mod_eps_bearer_context_req.radio_prio_present ||
       !mod_eps_bearer_context_req.packet_flow_id_present ||
       mod_eps_bearer_context_req.apn_ambr_present ||
       !mod_eps_bearer_context_req.protocol_cnfg_opts_present)
        return -1;
    return 0;
}

int notification_msg_test(void)
{
    LIBLTE_MME_NOTIFICATION_MSG_STRUCT notification;
    notification.eps_bearer_id = 0x5;
    notification.proc_transaction_id = 0xA5;
    notification.notification_ind = LIBLTE_MME_NOTIFICATION_INDICATOR_SRVCC_HO_CANCELLED_IMS_SESSION_REEST_REQ;
    LIBLTE_BYTE_MSG_STRUCT msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_notification_msg(&notification, &msg))
        return -1;
    if(5 != msg.N_bytes)
        return -1;
    if(0x52 != msg.msg[0] || 0xA5 != msg.msg[1] || 0xDB != msg.msg[2] || 0x01 != msg.msg[3] ||
       0x01 != msg.msg[4])
        return -1;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_notification_msg(&msg, &notification))
        return -1;
    if(notification.eps_bearer_id != 0x5 ||
       notification.proc_transaction_id != 0xA5 ||
       notification.notification_ind != LIBLTE_MME_NOTIFICATION_INDICATOR_SRVCC_HO_CANCELLED_IMS_SESSION_REEST_REQ)
        return -1;
    return 0;
}

int pdn_connectivity_reject_msg_test(void)
{
    LIBLTE_MME_PDN_CONNECTIVITY_REJECT_MSG_STRUCT pdn_con_rej;
    pdn_con_rej.t3496.unit = LIBLTE_MME_GPRS_TIMER_3_UNIT_10_HOURS;
    pdn_con_rej.t3496.value = 0x15;
    pdn_con_rej.eps_bearer_id = 0x5;
    pdn_con_rej.proc_transaction_id = 0xA5;
    pdn_con_rej.esm_cause = LIBLTE_MME_ESM_CAUSE_UNUSED;
    pdn_con_rej.protocol_cnfg_opts_present = false;
    pdn_con_rej.t3496_present = true;
    LIBLTE_BYTE_MSG_STRUCT msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_pdn_connectivity_reject_msg(&pdn_con_rej, &msg))
        return -1;
    if(7 != msg.N_bytes)
        return -1;
    if(0x52 != msg.msg[0] || 0xA5 != msg.msg[1] || 0xD1 != msg.msg[2] || 0x2E != msg.msg[3] ||
       0x37 != msg.msg[4] || 0x01 != msg.msg[5] || 0x55 != msg.msg[6])
        return -1;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_pdn_connectivity_reject_msg(&msg, &pdn_con_rej))
        return -1;
    if(pdn_con_rej.t3496.unit != LIBLTE_MME_GPRS_TIMER_3_UNIT_10_HOURS ||
       pdn_con_rej.t3496.value != 0x15 || pdn_con_rej.eps_bearer_id != 0x5 ||
       pdn_con_rej.proc_transaction_id != 0xA5 ||
       pdn_con_rej.esm_cause != LIBLTE_MME_ESM_CAUSE_UNUSED ||
       pdn_con_rej.protocol_cnfg_opts_present || !pdn_con_rej.t3496_present)
        return -1;
    return 0;
}

int pdn_connectivity_request_msg_test(void)
{
    LIBLTE_MME_PDN_CONNECTIVITY_REQUEST_MSG_STRUCT pdn_con_req;
    pdn_con_req.apn.apn = "test";
    pdn_con_req.device_properties = LIBLTE_MME_DEVICE_PROPERTIES_CONFIGURED_FOR_LOW_PRIORITY;
    pdn_con_req.eps_bearer_id = 0x5;
    pdn_con_req.proc_transaction_id = 0xA5;
    pdn_con_req.pdn_type = LIBLTE_MME_PDN_TYPE_IPV4;
    pdn_con_req.request_type = LIBLTE_MME_REQUEST_TYPE_UNUSED;
    pdn_con_req.esm_info_transfer_flag_present = false;
    pdn_con_req.apn_present = true;
    pdn_con_req.protocol_cnfg_opts_present = false;
    pdn_con_req.device_properties_present = true;
    LIBLTE_BYTE_MSG_STRUCT msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_pdn_connectivity_request_msg(&pdn_con_req, &msg))
        return -1;
    if(12 != msg.N_bytes)
        return -1;
    if(0x52 != msg.msg[0] || 0xA5 != msg.msg[1] || 0xD0 != msg.msg[2] || 0x13 != msg.msg[3] ||
       0x28 != msg.msg[4] || 0x05 != msg.msg[5] || 0x04 != msg.msg[6] || 0x74 != msg.msg[7] ||
       0x65 != msg.msg[8] || 0x73 != msg.msg[9] || 0x74 != msg.msg[10] || 0xC1 != msg.msg[11])
        return -1;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_pdn_connectivity_request_msg(&msg, &pdn_con_req))
        return -1;
    if(pdn_con_req.apn.apn != "test" ||
       pdn_con_req.device_properties != LIBLTE_MME_DEVICE_PROPERTIES_CONFIGURED_FOR_LOW_PRIORITY ||
       pdn_con_req.eps_bearer_id != 0x5 || pdn_con_req.proc_transaction_id != 0xA5 ||
       pdn_con_req.pdn_type != LIBLTE_MME_PDN_TYPE_IPV4 ||
       pdn_con_req.request_type != LIBLTE_MME_REQUEST_TYPE_UNUSED ||
       pdn_con_req.esm_info_transfer_flag_present || !pdn_con_req.apn_present ||
       pdn_con_req.protocol_cnfg_opts_present || !pdn_con_req.device_properties_present)
        return -1;
    return 0;
}

int pdn_disconnect_reject_msg_test(void)
{
    LIBLTE_MME_PDN_DISCONNECT_REJECT_MSG_STRUCT pdn_discon_rej;
    pdn_discon_rej.eps_bearer_id = 0x5;
    pdn_discon_rej.proc_transaction_id = 0xA5;
    pdn_discon_rej.esm_cause = LIBLTE_MME_ESM_CAUSE_UNUSED;
    pdn_discon_rej.protocol_cnfg_opts_present = false;
    LIBLTE_BYTE_MSG_STRUCT msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_pdn_disconnect_reject_msg(&pdn_discon_rej, &msg))
        return -1;
    if(4 != msg.N_bytes)
        return -1;
    if(0x52 != msg.msg[0] || 0xA5 != msg.msg[1] || 0xD3 != msg.msg[2] || 0x2E != msg.msg[3])
        return -1;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_pdn_disconnect_reject_msg(&msg, &pdn_discon_rej))
        return -1;
    if(pdn_discon_rej.eps_bearer_id != 0x5 || pdn_discon_rej.proc_transaction_id != 0xA5 ||
       pdn_discon_rej.esm_cause != LIBLTE_MME_ESM_CAUSE_UNUSED ||
       pdn_discon_rej.protocol_cnfg_opts_present)
        return -1;
    return 0;
}

int pdn_disconnect_request_msg_test(void)
{
    LIBLTE_MME_PDN_DISCONNECT_REQUEST_MSG_STRUCT pdn_discon_req;
    pdn_discon_req.eps_bearer_id = 0x5;
    pdn_discon_req.proc_transaction_id = 0xA5;
    pdn_discon_req.linked_eps_bearer_id = LIBLTE_MME_LINKED_EPS_BEARER_IDENTITY_5;
    pdn_discon_req.protocol_cnfg_opts_present = false;
    LIBLTE_BYTE_MSG_STRUCT msg;
    if(LIBLTE_SUCCESS != liblte_mme_pack_pdn_disconnect_request_msg(&pdn_discon_req, &msg))
        return -1;
    if(4 != msg.N_bytes)
        return -1;
    if(0x52 != msg.msg[0] || 0xA5 != msg.msg[1] || 0xD2 != msg.msg[2] || 0x05 != msg.msg[3])
        return -1;
    if(LIBLTE_SUCCESS != liblte_mme_unpack_pdn_disconnect_request_msg(&msg, &pdn_discon_req))
        return -1;
    if(pdn_discon_req.eps_bearer_id != 0x5 || pdn_discon_req.proc_transaction_id != 0xA5 ||
       pdn_discon_req.linked_eps_bearer_id != LIBLTE_MME_LINKED_EPS_BEARER_IDENTITY_5 ||
       pdn_discon_req.protocol_cnfg_opts_present)
        return -1;
    return 0;
}

int main(int argc, char *argv[])
{
    printf("additional_information_test: ");
    if(0 != additional_information_test())
        exit(-1);
    printf("pass\n");
    printf("device_properties_test: ");
    if(0 != device_properties_test())
        exit(-1);
    printf("pass\n");
    printf("eps_bearer_context_status_test: ");
    if(0 != eps_bearer_context_status_test())
        exit(-1);
    printf("pass\n");
    printf("location_area_id_test: ");
    if(0 != location_area_id_test())
        exit(-1);
    printf("pass\n");
    printf("mobile_id_test: ");
    if(0 != mobile_id_test())
        exit(-1);
    printf("pass\n");
    printf("mobile_station_classmark_2_test: ");
    if(0 != mobile_station_classmark_2_test())
        exit(-1);
    printf("pass\n");
    printf("mobile_station_classmark_3_test: ");
    if(0 != mobile_station_classmark_3_test())
        exit(-1);
    printf("pass\n");
    printf("nas_security_parameters_from_eutra_test: ");
    if(0 != nas_security_parameters_from_eutra_test())
        exit(-1);
    printf("pass\n");
    printf("nas_security_parameters_to_eutra_test: ");
    if(0 != nas_security_parameters_to_eutra_test())
        exit(-1);
    printf("pass\n");
    printf("plmn_list_test: ");
    if(0 != plmn_list_test())
        exit(-1);
    printf("pass\n");
    printf("supported_codec_list_test: ");
    if(0 != supported_codec_list_test())
        exit(-1);
    printf("pass\n");
    printf("additional_update_result_test: ");
    if(0 != additional_update_result_test())
        exit(-1);
    printf("pass\n");
    printf("additional_update_type_test: ");
    if(0 != additional_update_type_test())
        exit(-1);
    printf("pass\n");
    printf("authentication_failure_parameter_test: ");
    if(0 != authentication_failure_parameter_test())
        exit(-1);
    printf("pass\n");
    printf("authentication_parameter_autn_test: ");
    if(0 != authentication_parameter_autn_test())
        exit(-1);
    printf("pass\n");
    printf("authentication_parameter_rand_test: ");
    if(0 != authentication_parameter_rand_test())
        exit(-1);
    printf("pass\n");
    printf("authentication_response_parameter_test: ");
    if(0 != authentication_response_parameter_test())
        exit(-1);
    printf("pass\n");
    printf("ciphering_key_sequence_number_test: ");
    if(0 != ciphering_key_sequence_number_test())
        exit(-1);
    printf("pass\n");
    printf("csfb_response_test: ");
    if(0 != csfb_response_test())
        exit(-1);
    printf("pass\n");
    printf("daylight_saving_time_test: ");
    if(0 != daylight_saving_time_test())
        exit(-1);
    printf("pass\n");
    printf("detach_type_test: ");
    if(0 != detach_type_test())
        exit(-1);
    printf("pass\n");
    printf("drx_parameter_test: ");
    if(0 != drx_parameter_test())
        exit(-1);
    printf("pass\n");
    printf("emm_cause_test: ");
    if(0 != emm_cause_test())
        exit(-1);
    printf("pass\n");
    printf("eps_attach_result_test: ");
    if(0 != eps_attach_result_test())
        exit(-1);
    printf("pass\n");
    printf("eps_attach_type_test: ");
    if(0 != eps_attach_type_test())
        exit(-1);
    printf("pass\n");
    printf("eps_mobile_id_test: ");
    if(0 != eps_mobile_id_test())
        exit(-1);
    printf("pass\n");
    printf("eps_network_feature_support_test: ");
    if(0 != eps_network_feature_support_test())
        exit(-1);
    printf("pass\n");
    printf("eps_update_result_test: ");
    if(0 != eps_update_result_test())
        exit(-1);
    printf("pass\n");
    printf("eps_update_type_test: ");
    if(0 != eps_update_type_test())
        exit(-1);
    printf("pass\n");
    printf("esm_message_container_test: ");
    if(0 != esm_message_container_test())
        exit(-1);
    printf("pass\n");
    printf("gprs_timer_test: ");
    if(0 != gprs_timer_test())
        exit(-1);
    printf("pass\n");
    printf("gprs_timer_2_test: ");
    if(0 != gprs_timer_2_test())
        exit(-1);
    printf("pass\n");
    printf("gprs_timer_3_test: ");
    if(0 != gprs_timer_3_test())
        exit(-1);
    printf("pass\n");
    printf("identity_type_2_test: ");
    if(0 != identity_type_2_test())
        exit(-1);
    printf("pass\n");
    printf("imeisv_request_test: ");
    if(0 != imeisv_request_test())
        exit(-1);
    printf("pass\n");
    printf("ksi_and_sequence_number_test: ");
    if(0 != ksi_and_sequence_number_test())
        exit(-1);
    printf("pass\n");
    printf("ms_network_capability_test: ");
    if(0 != ms_network_capability_test())
        exit(-1);
    printf("pass\n");
    printf("nas_key_set_id_test: ");
    if(0 != nas_key_set_id_test())
        exit(-1);
    printf("pass\n");
    printf("nas_message_container_test: ");
    if(0 != nas_message_container_test())
        exit(-1);
    printf("pass\n");
    printf("nas_security_algorithms_test: ");
    if(0 != nas_security_algorithms_test())
        exit(-1);
    printf("pass\n");
    printf("network_name_test: ");
    if(0 != network_name_test())
        exit(-1);
    printf("pass\n");
    printf("nonce_test: ");
    if(0 != nonce_test())
        exit(-1);
    printf("pass\n");
    printf("paging_identity_test: ");
    if(0 != paging_identity_test())
        exit(-1);
    printf("pass\n");
    printf("p_tmsi_signature_test: ");
    if(0 != p_tmsi_signature_test())
        exit(-1);
    printf("pass\n");
    printf("service_type_test: ");
    if(0 != service_type_test())
        exit(-1);
    printf("pass\n");
    printf("short_mac_test: ");
    if(0 != short_mac_test())
        exit(-1);
    printf("pass\n");
    printf("time_zone_test: ");
    if(0 != time_zone_test())
        exit(-1);
    printf("pass\n");
    printf("time_zone_and_time_test: ");
    if(0 != time_zone_and_time_test())
        exit(-1);
    printf("pass\n");
    printf("tmsi_status_test: ");
    if(0 != tmsi_status_test())
        exit(-1);
    printf("pass\n");
    printf("tracking_area_id_test: ");
    if(0 != tracking_area_id_test())
        exit(-1);
    printf("pass\n");
    printf("tracking_area_identity_list_test: ");
    if(0 != tracking_area_identity_list_test())
        exit(-1);
    printf("pass\n");
    printf("ue_network_capability_test: ");
    if(0 != ue_network_capability_test())
        exit(-1);
    printf("pass\n");
    printf("ue_radio_capability_update_needed_test: ");
    if(0 != ue_radio_capability_update_needed_test())
        exit(-1);
    printf("pass\n");
    printf("ue_security_capabilities_test: ");
    if(0 != ue_security_capabilities_test())
        exit(-1);
    printf("pass\n");
    printf("emergency_number_list_test: ");
    if(0 != emergency_number_list_test())
        exit(-1);
    printf("pass\n");
    printf("cli_test: ");
    if(0 != cli_test())
        exit(-1);
    printf("pass\n");
    printf("ss_code_test: ");
    if(0 != ss_code_test())
        exit(-1);
    printf("pass\n");
    printf("lcs_indicator_test: ");
    if(0 != lcs_indicator_test())
        exit(-1);
    printf("pass\n");
    printf("generic_message_container_type_test: ");
    if(0 != generic_message_container_type_test())
        exit(-1);
    printf("pass\n");
    printf("generic_message_container_test: ");
    if(0 != generic_message_container_test())
        exit(-1);
    printf("pass\n");
    printf("voice_domain_pref_and_ue_usage_setting_test: ");
    if(0 != voice_domain_pref_and_ue_usage_setting_test())
        exit(-1);
    printf("pass\n");
    printf("guti_type_test: ");
    if(0 != guti_type_test())
        exit(-1);
    printf("pass\n");
    printf("access_point_name_test: ");
    if(0 != access_point_name_test())
        exit(-1);
    printf("pass\n");
    printf("apn_aggregate_maximum_bit_rate_test: ");
    if(0 != apn_aggregate_maximum_bit_rate_test())
        exit(-1);
    printf("pass\n");
    printf("connectivity_type_test: ");
    if(0 != connectivity_type_test())
        exit(-1);
    printf("pass\n");
    printf("eps_quality_of_service_test: ");
    if(0 != eps_quality_of_service_test())
        exit(-1);
    printf("pass\n");
    printf("esm_cause_test: ");
    if(0 != esm_cause_test())
        exit(-1);
    printf("pass\n");
    printf("esm_info_transfer_flag_test: ");
    if(0 != esm_info_transfer_flag_test())
        exit(-1);
    printf("pass\n");
    printf("linked_eps_bearer_identity_test: ");
    if(0 != linked_eps_bearer_identity_test())
        exit(-1);
    printf("pass\n");
    printf("llc_service_access_point_identifier_test: ");
    if(0 != llc_service_access_point_identifier_test())
        exit(-1);
    printf("pass\n");
    printf("notification_indicator_test: ");
    if(0 != notification_indicator_test())
        exit(-1);
    printf("pass\n");
    printf("packet_flow_identifier_test: ");
    if(0 != packet_flow_identifier_test())
        exit(-1);
    printf("pass\n");
    printf("pdn_address_test: ");
    if(0 != pdn_address_test())
        exit(-1);
    printf("pass\n");
    printf("pdn_type_test: ");
    if(0 != pdn_type_test())
        exit(-1);
    printf("pass\n");
    printf("protocol_config_options_test: ");
    if(0 != protocol_config_options_test())
        exit(-1);
    printf("pass\n");
    printf("quality_of_service_test: ");
    if(0 != quality_of_service_test())
        exit(-1);
    printf("pass\n");
    printf("radio_priority_test: ");
    if(0 != radio_priority_test())
        exit(-1);
    printf("pass\n");
    printf("request_type_test: ");
    if(0 != request_type_test())
        exit(-1);
    printf("pass\n");
    printf("traffic_flow_aggregate_description_test: ");
    if(0 != traffic_flow_aggregate_description_test())
        exit(-1);
    printf("pass\n");
    printf("traffic_flow_template_test: ");
    if(0 != traffic_flow_template_test())
        exit(-1);
    printf("pass\n");
    printf("transaction_identifier_test: ");
    if(0 != transaction_identifier_test())
        exit(-1);
    printf("pass\n");
    printf("parse_msg_header_test: ");
    if(0 != parse_msg_header_test())
        exit(-1);
    printf("pass\n");
    printf("security_protected_nas_msg_test: ");
    if(0 != security_protected_nas_msg_test())
        exit(-1);
    printf("pass\n");
    printf("attach_accept_msg_test: ");
    if(0 != attach_accept_msg_test())
        exit(-1);
    printf("pass\n");
    printf("attach_complete_msg_test: ");
    if(0 != attach_complete_msg_test())
        exit(-1);
    printf("pass\n");
    printf("attach_reject_msg_test: ");
    if(0 != attach_reject_msg_test())
        exit(-1);
    printf("pass\n");
    printf("attach_request_msg_test: ");
    if(0 != attach_request_msg_test())
        exit(-1);
    printf("pass\n");
    printf("authentication_failure_msg_test: ");
    if(0 != authentication_failure_msg_test())
        exit(-1);
    printf("pass\n");
    printf("authentication_reject_msg_test: ");
    if(0 != authentication_reject_msg_test())
        exit(-1);
    printf("pass\n");
    printf("authentication_request_msg_test: ");
    if(0 != authentication_request_msg_test())
        exit(-1);
    printf("pass\n");
    printf("authentication_response_msg_test: ");
    if(0 != authentication_response_msg_test())
        exit(-1);
    printf("pass\n");
    printf("detach_accept_msg_test: ");
    if(0 != detach_accept_msg_test())
        exit(-1);
    printf("pass\n");
    printf("detach_request_msg_test: ");
    if(0 != detach_request_msg_test())
        exit(-1);
    printf("pass\n");
    printf("dl_nas_transport_msg_test: ");
    if(0 != dl_nas_transport_msg_test())
        exit(-1);
    printf("pass\n");
    printf("emm_information_msg_test: ");
    if(0 != emm_information_msg_test())
        exit(-1);
    printf("pass\n");
    printf("emm_status_msg_test: ");
    if(0 != emm_status_msg_test())
        exit(-1);
    printf("pass\n");
    printf("extended_service_request_msg_test: ");
    if(0 != extended_service_request_msg_test())
        exit(-1);
    printf("pass\n");
    printf("guti_reallocation_command_msg_test: ");
    if(0 != guti_reallocation_command_msg_test())
        exit(-1);
    printf("pass\n");
    printf("guti_reallocation_complete_msg_test: ");
    if(0 != guti_reallocation_complete_msg_test())
        exit(-1);
    printf("pass\n");
    printf("identity_request_msg_test: ");
    if(0 != identity_request_msg_test())
        exit(-1);
    printf("pass\n");
    printf("identity_response_msg_test: ");
    if(0 != identity_response_msg_test())
        exit(-1);
    printf("pass\n");
    printf("security_mode_command_msg_test: ");
    if(0 != security_mode_command_msg_test())
        exit(-1);
    printf("pass\n");
    printf("security_mode_complete_msg_test: ");
    if(0 != security_mode_complete_msg_test())
        exit(-1);
    printf("pass\n");
    printf("security_mode_reject_msg_test: ");
    if(0 != security_mode_reject_msg_test())
        exit(-1);
    printf("pass\n");
    printf("service_reject_msg_test: ");
    if(0 != service_reject_msg_test())
        exit(-1);
    printf("pass\n");
    printf("service_request_msg_test: ");
    if(0 != service_request_msg_test())
        exit(-1);
    printf("pass\n");
    printf("tracking_area_update_accept_msg_test: ");
    if(0 != tracking_area_update_accept_msg_test())
        exit(-1);
    printf("pass\n");
    printf("tracking_area_update_complete_msg_test: ");
    if(0 != tracking_area_update_complete_msg_test())
        exit(-1);
    printf("pass\n");
    printf("tracking_area_update_reject_msg_test: ");
    if(0 != tracking_area_update_reject_msg_test())
        exit(-1);
    printf("pass\n");
    printf("tracking_area_update_request_msg_test: ");
    if(0 != tracking_area_update_request_msg_test())
        exit(-1);
    printf("pass\n");
    printf("ul_nas_transport_msg_test: ");
    if(0 != ul_nas_transport_msg_test())
        exit(-1);
    printf("pass\n");
    printf("dl_generic_nas_transport_msg_test: ");
    if(0 != dl_generic_nas_transport_msg_test())
        exit(-1);
    printf("pass\n");
    printf("ul_generic_nas_transport_msg_test: ");
    if(0 != ul_generic_nas_transport_msg_test())
        exit(-1);
    printf("pass\n");
    printf("activate_dedicated_eps_bearer_context_accept_msg_test: ");
    if(0 != activate_dedicated_eps_bearer_context_accept_msg_test())
        exit(-1);
    printf("pass\n");
    printf("activate_dedicated_eps_bearer_context_reject_msg_test: ");
    if(0 != activate_dedicated_eps_bearer_context_reject_msg_test())
        exit(-1);
    printf("pass\n");
    printf("activate_dedicated_eps_bearer_context_request_msg_test: ");
    if(0 != activate_dedicated_eps_bearer_context_request_msg_test())
        exit(-1);
    printf("pass\n");
    printf("activate_default_eps_bearer_context_accept_msg_test: ");
    if(0 != activate_default_eps_bearer_context_accept_msg_test())
        exit(-1);
    printf("pass\n");
    printf("activate_default_eps_bearer_context_reject_msg_test: ");
    if(0 != activate_default_eps_bearer_context_reject_msg_test())
        exit(-1);
    printf("pass\n");
    printf("activate_default_eps_bearer_context_request_msg_test: ");
    if(0 != activate_default_eps_bearer_context_request_msg_test())
        exit(-1);
    printf("pass\n");
    printf("bearer_resource_allocation_reject_msg_test: ");
    if(0 != bearer_resource_allocation_reject_msg_test())
        exit(-1);
    printf("pass\n");
    printf("bearer_resource_allocation_request_msg_test: ");
    if(0 != bearer_resource_allocation_request_msg_test())
        exit(-1);
    printf("pass\n");
    printf("bearer_resource_modification_reject_msg_test: ");
    if(0 != bearer_resource_modification_reject_msg_test())
        exit(-1);
    printf("pass\n");
    printf("bearer_resource_modification_request_msg_test: ");
    if(0 != bearer_resource_modification_request_msg_test())
        exit(-1);
    printf("pass\n");
    printf("deactivate_eps_bearer_context_accept_msg_test: ");
    if(0 != deactivate_eps_bearer_context_accept_msg_test())
        exit(-1);
    printf("pass\n");
    printf("deactivate_eps_bearer_context_request_msg_test: ");
    if(0 != deactivate_eps_bearer_context_request_msg_test())
        exit(-1);
    printf("pass\n");
    printf("esm_information_request_msg_test: ");
    if(0 != esm_information_request_msg_test())
        exit(-1);
    printf("pass\n");
    printf("esm_information_response_msg_test: ");
    if(0 != esm_information_response_msg_test())
        exit(-1);
    printf("pass\n");
    printf("esm_status_msg_test: ");
    if(0 != esm_status_msg_test())
        exit(-1);
    printf("pass\n");
    printf("modify_eps_bearer_context_accept_msg_test: ");
    if(0 != modify_eps_bearer_context_accept_msg_test())
        exit(-1);
    printf("pass\n");
    printf("modify_eps_bearer_context_reject_msg_test: ");
    if(0 != modify_eps_bearer_context_reject_msg_test())
        exit(-1);
    printf("pass\n");
    printf("modify_eps_bearer_context_request_msg_test: ");
    if(0 != modify_eps_bearer_context_request_msg_test())
        exit(-1);
    printf("pass\n");
    printf("notification_msg_test: ");
    if(0 != notification_msg_test())
        exit(-1);
    printf("pass\n");
    printf("pdn_connectivity_reject_msg_test: ");
    if(0 != pdn_connectivity_reject_msg_test())
        exit(-1);
    printf("pass\n");
    printf("pdn_connectivity_request_msg_test: ");
    if(0 != pdn_connectivity_request_msg_test())
        exit(-1);
    printf("pass\n");
    printf("pdn_disconnect_reject_msg_test: ");
    if(0 != pdn_disconnect_reject_msg_test())
        exit(-1);
    printf("pass\n");
    printf("pdn_disconnect_request_msg_test: ");
    if(0 != pdn_disconnect_request_msg_test())
        exit(-1);
    printf("pass\n");
    exit(0);
}
