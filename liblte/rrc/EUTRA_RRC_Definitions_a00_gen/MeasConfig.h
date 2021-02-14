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

#ifndef __MeasConfig_H__
#define __MeasConfig_H__

#include "MeasObjectToRemoveList.h"
#include "MeasObjectToAddModList.h"
#include "ReportConfigToRemoveList.h"
#include "ReportConfigToAddModList.h"
#include "MeasIdToRemoveList.h"
#include "MeasIdToAddModList.h"
#include "QuantityConfig.h"
#include "MeasGapConfig.h"
#include "RSRP_Range.h"
#include "PreRegistrationInfoHRPD.h"
#include "MobilityStateParameters.h"
#include "SpeedStateScaleFactors.h"

#include <array>
#include <cstdint>
#include <vector>

class MeasConfig
{
public:
    MeasConfig() : measObjectToRemoveList_present{false}, measObjectToAddModList_present{false}, reportConfigToRemoveList_present{false}, reportConfigToAddModList_present{false}, measIdToRemoveList_present{false}, measIdToAddModList_present{false}, quantityConfig_present{false}, measGapConfig_present{false}, s_Measure_present{false}, preRegistrationInfoHRPD_present{false}, speedStatePars_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // measObjectToRemoveList
public:
    MeasObjectToRemoveList* measObjectToRemoveList_Set();
    int measObjectToRemoveList_Set(MeasObjectToRemoveList &value);
    const MeasObjectToRemoveList& measObjectToRemoveList_Get() const;
    std::string measObjectToRemoveList_ToString(uint32_t indent) const;
    std::string measObjectToRemoveList_ToStringNoNewLines() const;
    int measObjectToRemoveList_Clear();
    bool measObjectToRemoveList_IsPresent() const;
private:
    bool measObjectToRemoveList_present;
    MeasObjectToRemoveList measObjectToRemoveList;

    // measObjectToAddModList
public:
    MeasObjectToAddModList* measObjectToAddModList_Set();
    int measObjectToAddModList_Set(MeasObjectToAddModList &value);
    const MeasObjectToAddModList& measObjectToAddModList_Get() const;
    std::string measObjectToAddModList_ToString(uint32_t indent) const;
    std::string measObjectToAddModList_ToStringNoNewLines() const;
    int measObjectToAddModList_Clear();
    bool measObjectToAddModList_IsPresent() const;
private:
    bool measObjectToAddModList_present;
    MeasObjectToAddModList measObjectToAddModList;

    // reportConfigToRemoveList
public:
    ReportConfigToRemoveList* reportConfigToRemoveList_Set();
    int reportConfigToRemoveList_Set(ReportConfigToRemoveList &value);
    const ReportConfigToRemoveList& reportConfigToRemoveList_Get() const;
    std::string reportConfigToRemoveList_ToString(uint32_t indent) const;
    std::string reportConfigToRemoveList_ToStringNoNewLines() const;
    int reportConfigToRemoveList_Clear();
    bool reportConfigToRemoveList_IsPresent() const;
private:
    bool reportConfigToRemoveList_present;
    ReportConfigToRemoveList reportConfigToRemoveList;

    // reportConfigToAddModList
public:
    ReportConfigToAddModList* reportConfigToAddModList_Set();
    int reportConfigToAddModList_Set(ReportConfigToAddModList &value);
    const ReportConfigToAddModList& reportConfigToAddModList_Get() const;
    std::string reportConfigToAddModList_ToString(uint32_t indent) const;
    std::string reportConfigToAddModList_ToStringNoNewLines() const;
    int reportConfigToAddModList_Clear();
    bool reportConfigToAddModList_IsPresent() const;
private:
    bool reportConfigToAddModList_present;
    ReportConfigToAddModList reportConfigToAddModList;

    // measIdToRemoveList
public:
    MeasIdToRemoveList* measIdToRemoveList_Set();
    int measIdToRemoveList_Set(MeasIdToRemoveList &value);
    const MeasIdToRemoveList& measIdToRemoveList_Get() const;
    std::string measIdToRemoveList_ToString(uint32_t indent) const;
    std::string measIdToRemoveList_ToStringNoNewLines() const;
    int measIdToRemoveList_Clear();
    bool measIdToRemoveList_IsPresent() const;
private:
    bool measIdToRemoveList_present;
    MeasIdToRemoveList measIdToRemoveList;

    // measIdToAddModList
public:
    MeasIdToAddModList* measIdToAddModList_Set();
    int measIdToAddModList_Set(MeasIdToAddModList &value);
    const MeasIdToAddModList& measIdToAddModList_Get() const;
    std::string measIdToAddModList_ToString(uint32_t indent) const;
    std::string measIdToAddModList_ToStringNoNewLines() const;
    int measIdToAddModList_Clear();
    bool measIdToAddModList_IsPresent() const;
private:
    bool measIdToAddModList_present;
    MeasIdToAddModList measIdToAddModList;

    // quantityConfig
public:
    QuantityConfig* quantityConfig_Set();
    int quantityConfig_Set(QuantityConfig &value);
    const QuantityConfig& quantityConfig_Get() const;
    std::string quantityConfig_ToString(uint32_t indent) const;
    std::string quantityConfig_ToStringNoNewLines() const;
    int quantityConfig_Clear();
    bool quantityConfig_IsPresent() const;
private:
    bool quantityConfig_present;
    QuantityConfig quantityConfig;

    // measGapConfig
public:
    MeasGapConfig* measGapConfig_Set();
    int measGapConfig_Set(MeasGapConfig &value);
    const MeasGapConfig& measGapConfig_Get() const;
    std::string measGapConfig_ToString(uint32_t indent) const;
    std::string measGapConfig_ToStringNoNewLines() const;
    int measGapConfig_Clear();
    bool measGapConfig_IsPresent() const;
private:
    bool measGapConfig_present;
    MeasGapConfig measGapConfig;

    // s-Measure
public:
    RSRP_Range* s_Measure_Set();
    int s_Measure_Set(RSRP_Range &value);
    const RSRP_Range& s_Measure_Get() const;
    std::string s_Measure_ToString(uint32_t indent) const;
    std::string s_Measure_ToStringNoNewLines() const;
    int s_Measure_Clear();
    bool s_Measure_IsPresent() const;
private:
    bool s_Measure_present;
    RSRP_Range s_Measure;

    // preRegistrationInfoHRPD
public:
    PreRegistrationInfoHRPD* preRegistrationInfoHRPD_Set();
    int preRegistrationInfoHRPD_Set(PreRegistrationInfoHRPD &value);
    const PreRegistrationInfoHRPD& preRegistrationInfoHRPD_Get() const;
    std::string preRegistrationInfoHRPD_ToString(uint32_t indent) const;
    std::string preRegistrationInfoHRPD_ToStringNoNewLines() const;
    int preRegistrationInfoHRPD_Clear();
    bool preRegistrationInfoHRPD_IsPresent() const;
private:
    bool preRegistrationInfoHRPD_present;
    PreRegistrationInfoHRPD preRegistrationInfoHRPD;

    // speedStatePars
public:
    enum speedStatePars_Enum {
        k_speedStatePars_release = 0,
        k_speedStatePars_setup,
    };
    int speedStatePars_Pack(std::vector<uint8_t> &bits);
    int speedStatePars_Unpack(std::vector<uint8_t> bits);
    int speedStatePars_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    speedStatePars_Enum speedStatePars_Choice() const;
    int speedStatePars_SetChoice(speedStatePars_Enum choice);
    std::string speedStatePars_ChoiceToString(speedStatePars_Enum value) const;
    uint64_t speedStatePars_NumberOfChoices() const;
    std::string speedStatePars_ToString(uint32_t indent) const;
    std::string speedStatePars_ToStringNoNewLines() const;
    int speedStatePars_Clear();
    bool speedStatePars_IsPresent() const;
private:
    bool speedStatePars_present;
    speedStatePars_Enum speedStatePars_internal_choice;

    // release
public:
    int speedStatePars_release_Pack(std::vector<uint8_t> &bits) {return 0;};
    int speedStatePars_release_Unpack(std::vector<uint8_t> bits) {return 0;};
    int speedStatePars_release_Unpack(std::vector<uint8_t> bits, uint32_t &idx) {return 0;};
    bool speedStatePars_release_IsPresent() const {return true;};
    std::string speedStatePars_release_ToString(uint32_t indent) {return "";};
    std::string speedStatePars_release_ToStringNoNewLines() {return "";};

    // setup
public:
    class speedStatePars_setup
    {
    public:
        speedStatePars_setup() : mobilityStateParameters_present{false}, timeToTrigger_SF_present{false} {};
    public:
        int Pack(std::vector<uint8_t> &bits);
        int Unpack(std::vector<uint8_t> bits);
        int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        std::string ToString(uint32_t indent) const;
        std::string ToStringNoNewLines() const;

        // mobilityStateParameters
    public:
        MobilityStateParameters* mobilityStateParameters_Set();
        int mobilityStateParameters_Set(MobilityStateParameters &value);
        const MobilityStateParameters& mobilityStateParameters_Get() const;
        std::string mobilityStateParameters_ToString(uint32_t indent) const;
        std::string mobilityStateParameters_ToStringNoNewLines() const;
        int mobilityStateParameters_Clear();
        bool mobilityStateParameters_IsPresent() const;
    private:
        bool mobilityStateParameters_present;
        MobilityStateParameters mobilityStateParameters;

        // timeToTrigger-SF
    public:
        SpeedStateScaleFactors* timeToTrigger_SF_Set();
        int timeToTrigger_SF_Set(SpeedStateScaleFactors &value);
        const SpeedStateScaleFactors& timeToTrigger_SF_Get() const;
        std::string timeToTrigger_SF_ToString(uint32_t indent) const;
        std::string timeToTrigger_SF_ToStringNoNewLines() const;
        int timeToTrigger_SF_Clear();
        bool timeToTrigger_SF_IsPresent() const;
    private:
        bool timeToTrigger_SF_present;
        SpeedStateScaleFactors timeToTrigger_SF;

    };

    speedStatePars_setup speedStatePars_setup_value;


};

#endif
