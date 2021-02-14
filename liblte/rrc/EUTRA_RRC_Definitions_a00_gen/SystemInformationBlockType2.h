// Copyright 2021 Ben Wojtowicz
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef __SystemInformationBlockType2_H__
#define __SystemInformationBlockType2_H__

#include "AC_BarringConfig.h"
#include "AC_BarringConfig.h"
#include "RadioResourceConfigCommonSIB.h"
#include "UE_TimersAndConstants.h"
#include "ARFCN_ValueEUTRA.h"
#include "AdditionalSpectrumEmission.h"
#include "MBSFN_SubframeConfigList.h"
#include "TimeAlignmentTimer.h"
#include "AC_BarringConfig.h"
#include "AC_BarringConfig.h"
#include "AC_BarringConfig.h"

#include <array>
#include <cstdint>
#include <vector>

class SystemInformationBlockType2
{
public:
    SystemInformationBlockType2() : radioResourceConfigCommon_present{false}, ue_TimersAndConstants_present{false}, mbsfn_SubframeConfigList_present{false}, timeAlignmentTimerCommon_present{false}, lateNonCriticalExtension_present{false}, ssac_BarringForMMTEL_Voice_r9_present{false}, ssac_BarringForMMTEL_Video_r9_present{false}, ac_BarringForCSFB_r10_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // ac-BarringInfo
public:
    class ac_BarringInfo
    {
    public:
        ac_BarringInfo() : present{false}, ac_BarringForEmergency_present{false}, ac_BarringForMO_Signalling_present{false}, ac_BarringForMO_Data_present{false} {};
    public:
        int Pack(std::vector<uint8_t> &bits);
        int Unpack(std::vector<uint8_t> bits);
        int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        std::string ToString(uint32_t indent) const;
        std::string ToStringNoNewLines() const;
        int Set();
        int SetPresence(bool is_present);
        int Clear();
        bool IsPresent() const;
    private:
        bool present;

        // ac-BarringForEmergency
    public:
        int ac_BarringForEmergency_Pack(std::vector<uint8_t> &bits);
        int ac_BarringForEmergency_Unpack(std::vector<uint8_t> bits);
        int ac_BarringForEmergency_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        bool ac_BarringForEmergency_Value() const;
        int ac_BarringForEmergency_SetValue(bool value);
        std::string ac_BarringForEmergency_ToString(uint32_t indent) const;
        std::string ac_BarringForEmergency_ToStringNoNewLines() const;
        int ac_BarringForEmergency_Clear();
        bool ac_BarringForEmergency_IsPresent() const;
    private:
        bool ac_BarringForEmergency_present;
        bool ac_BarringForEmergency_internal_value;

        // ac-BarringForMO-Signalling
    public:
        AC_BarringConfig* ac_BarringForMO_Signalling_Set();
        int ac_BarringForMO_Signalling_Set(AC_BarringConfig &value);
        const AC_BarringConfig& ac_BarringForMO_Signalling_Get() const;
        std::string ac_BarringForMO_Signalling_ToString(uint32_t indent) const;
        std::string ac_BarringForMO_Signalling_ToStringNoNewLines() const;
        int ac_BarringForMO_Signalling_Clear();
        bool ac_BarringForMO_Signalling_IsPresent() const;
    private:
        bool ac_BarringForMO_Signalling_present;
        AC_BarringConfig ac_BarringForMO_Signalling;

        // ac-BarringForMO-Data
    public:
        AC_BarringConfig* ac_BarringForMO_Data_Set();
        int ac_BarringForMO_Data_Set(AC_BarringConfig &value);
        const AC_BarringConfig& ac_BarringForMO_Data_Get() const;
        std::string ac_BarringForMO_Data_ToString(uint32_t indent) const;
        std::string ac_BarringForMO_Data_ToStringNoNewLines() const;
        int ac_BarringForMO_Data_Clear();
        bool ac_BarringForMO_Data_IsPresent() const;
    private:
        bool ac_BarringForMO_Data_present;
        AC_BarringConfig ac_BarringForMO_Data;

    };

    ac_BarringInfo ac_BarringInfo_value;

    // radioResourceConfigCommon
public:
    RadioResourceConfigCommonSIB* radioResourceConfigCommon_Set();
    int radioResourceConfigCommon_Set(RadioResourceConfigCommonSIB &value);
    const RadioResourceConfigCommonSIB& radioResourceConfigCommon_Get() const;
    std::string radioResourceConfigCommon_ToString(uint32_t indent) const;
    std::string radioResourceConfigCommon_ToStringNoNewLines() const;
    int radioResourceConfigCommon_Clear();
    bool radioResourceConfigCommon_IsPresent() const;
private:
    bool radioResourceConfigCommon_present;
    RadioResourceConfigCommonSIB radioResourceConfigCommon;

    // ue-TimersAndConstants
public:
    UE_TimersAndConstants* ue_TimersAndConstants_Set();
    int ue_TimersAndConstants_Set(UE_TimersAndConstants &value);
    const UE_TimersAndConstants& ue_TimersAndConstants_Get() const;
    std::string ue_TimersAndConstants_ToString(uint32_t indent) const;
    std::string ue_TimersAndConstants_ToStringNoNewLines() const;
    int ue_TimersAndConstants_Clear();
    bool ue_TimersAndConstants_IsPresent() const;
private:
    bool ue_TimersAndConstants_present;
    UE_TimersAndConstants ue_TimersAndConstants;

    // freqInfo
public:
    class freqInfo
    {
    public:
        freqInfo() : ul_CarrierFreq_present{false}, ul_Bandwidth_present{false}, additionalSpectrumEmission_present{false} {};
    public:
        int Pack(std::vector<uint8_t> &bits);
        int Unpack(std::vector<uint8_t> bits);
        int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        std::string ToString(uint32_t indent) const;
        std::string ToStringNoNewLines() const;

        // ul-CarrierFreq
    public:
        ARFCN_ValueEUTRA* ul_CarrierFreq_Set();
        int ul_CarrierFreq_Set(ARFCN_ValueEUTRA &value);
        const ARFCN_ValueEUTRA& ul_CarrierFreq_Get() const;
        std::string ul_CarrierFreq_ToString(uint32_t indent) const;
        std::string ul_CarrierFreq_ToStringNoNewLines() const;
        int ul_CarrierFreq_Clear();
        bool ul_CarrierFreq_IsPresent() const;
    private:
        bool ul_CarrierFreq_present;
        ARFCN_ValueEUTRA ul_CarrierFreq;

        // ul-Bandwidth
    public:
        enum ul_Bandwidth_Enum {
            k_ul_Bandwidth_n6 = 0,
            k_ul_Bandwidth_n15,
            k_ul_Bandwidth_n25,
            k_ul_Bandwidth_n50,
            k_ul_Bandwidth_n75,
            k_ul_Bandwidth_n100,
        };
        int ul_Bandwidth_Pack(std::vector<uint8_t> &bits);
        int ul_Bandwidth_Unpack(std::vector<uint8_t> bits);
        int ul_Bandwidth_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        ul_Bandwidth_Enum ul_Bandwidth_Value() const;
        int ul_Bandwidth_SetValue(ul_Bandwidth_Enum value);
        int ul_Bandwidth_SetValue(std::string value);
        std::string ul_Bandwidth_ValueToString(ul_Bandwidth_Enum value) const;
        uint64_t ul_Bandwidth_NumberOfValues() const;
        std::string ul_Bandwidth_ToString(uint32_t indent) const;
        std::string ul_Bandwidth_ToStringNoNewLines() const;
        int ul_Bandwidth_Clear();
        bool ul_Bandwidth_IsPresent() const;
    private:
        bool ul_Bandwidth_present;
        ul_Bandwidth_Enum ul_Bandwidth_internal_value;

        // additionalSpectrumEmission
    public:
        AdditionalSpectrumEmission* additionalSpectrumEmission_Set();
        int additionalSpectrumEmission_Set(AdditionalSpectrumEmission &value);
        const AdditionalSpectrumEmission& additionalSpectrumEmission_Get() const;
        std::string additionalSpectrumEmission_ToString(uint32_t indent) const;
        std::string additionalSpectrumEmission_ToStringNoNewLines() const;
        int additionalSpectrumEmission_Clear();
        bool additionalSpectrumEmission_IsPresent() const;
    private:
        bool additionalSpectrumEmission_present;
        AdditionalSpectrumEmission additionalSpectrumEmission;

    };

    freqInfo freqInfo_value;

    // mbsfn-SubframeConfigList
public:
    MBSFN_SubframeConfigList* mbsfn_SubframeConfigList_Set();
    int mbsfn_SubframeConfigList_Set(MBSFN_SubframeConfigList &value);
    const MBSFN_SubframeConfigList& mbsfn_SubframeConfigList_Get() const;
    std::string mbsfn_SubframeConfigList_ToString(uint32_t indent) const;
    std::string mbsfn_SubframeConfigList_ToStringNoNewLines() const;
    int mbsfn_SubframeConfigList_Clear();
    bool mbsfn_SubframeConfigList_IsPresent() const;
private:
    bool mbsfn_SubframeConfigList_present;
    MBSFN_SubframeConfigList mbsfn_SubframeConfigList;

    // timeAlignmentTimerCommon
public:
    TimeAlignmentTimer* timeAlignmentTimerCommon_Set();
    int timeAlignmentTimerCommon_Set(TimeAlignmentTimer &value);
    const TimeAlignmentTimer& timeAlignmentTimerCommon_Get() const;
    std::string timeAlignmentTimerCommon_ToString(uint32_t indent) const;
    std::string timeAlignmentTimerCommon_ToStringNoNewLines() const;
    int timeAlignmentTimerCommon_Clear();
    bool timeAlignmentTimerCommon_IsPresent() const;
private:
    bool timeAlignmentTimerCommon_present;
    TimeAlignmentTimer timeAlignmentTimerCommon;

    // lateNonCriticalExtension
public:
    int lateNonCriticalExtension_Pack(std::vector<uint8_t> &bits);
    int lateNonCriticalExtension_Unpack(std::vector<uint8_t> bits);
    int lateNonCriticalExtension_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::vector<uint8_t> lateNonCriticalExtension_Value() const;
    int lateNonCriticalExtension_SetValue(std::vector<uint8_t> value);
    std::string lateNonCriticalExtension_ToString(uint32_t indent) const;
    std::string lateNonCriticalExtension_ToStringNoNewLines() const;
    int lateNonCriticalExtension_Clear();
    bool lateNonCriticalExtension_IsPresent() const;
private:
    bool lateNonCriticalExtension_present;
    std::vector<uint8_t> lateNonCriticalExtension_internal_value;

    // ssac-BarringForMMTEL-Voice-r9
public:
    AC_BarringConfig* ssac_BarringForMMTEL_Voice_r9_Set();
    int ssac_BarringForMMTEL_Voice_r9_Set(AC_BarringConfig &value);
    const AC_BarringConfig& ssac_BarringForMMTEL_Voice_r9_Get() const;
    std::string ssac_BarringForMMTEL_Voice_r9_ToString(uint32_t indent) const;
    std::string ssac_BarringForMMTEL_Voice_r9_ToStringNoNewLines() const;
    int ssac_BarringForMMTEL_Voice_r9_Clear();
    bool ssac_BarringForMMTEL_Voice_r9_IsPresent() const;
private:
    bool ssac_BarringForMMTEL_Voice_r9_present;
    AC_BarringConfig ssac_BarringForMMTEL_Voice_r9;

    // ssac-BarringForMMTEL-Video-r9
public:
    AC_BarringConfig* ssac_BarringForMMTEL_Video_r9_Set();
    int ssac_BarringForMMTEL_Video_r9_Set(AC_BarringConfig &value);
    const AC_BarringConfig& ssac_BarringForMMTEL_Video_r9_Get() const;
    std::string ssac_BarringForMMTEL_Video_r9_ToString(uint32_t indent) const;
    std::string ssac_BarringForMMTEL_Video_r9_ToStringNoNewLines() const;
    int ssac_BarringForMMTEL_Video_r9_Clear();
    bool ssac_BarringForMMTEL_Video_r9_IsPresent() const;
private:
    bool ssac_BarringForMMTEL_Video_r9_present;
    AC_BarringConfig ssac_BarringForMMTEL_Video_r9;

    // ac-BarringForCSFB-r10
public:
    AC_BarringConfig* ac_BarringForCSFB_r10_Set();
    int ac_BarringForCSFB_r10_Set(AC_BarringConfig &value);
    const AC_BarringConfig& ac_BarringForCSFB_r10_Get() const;
    std::string ac_BarringForCSFB_r10_ToString(uint32_t indent) const;
    std::string ac_BarringForCSFB_r10_ToStringNoNewLines() const;
    int ac_BarringForCSFB_r10_Clear();
    bool ac_BarringForCSFB_r10_IsPresent() const;
private:
    bool ac_BarringForCSFB_r10_present;
    AC_BarringConfig ac_BarringForCSFB_r10;

};

#endif
