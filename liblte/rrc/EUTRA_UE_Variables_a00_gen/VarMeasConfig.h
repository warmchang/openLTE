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

#ifndef __VarMeasConfig_H__
#define __VarMeasConfig_H__

#include "MeasIdToAddModList.h"
#include "MeasObjectToAddModList.h"
#include "ReportConfigToAddModList.h"
#include "QuantityConfig.h"
#include "RSRP_Range.h"
#include "MobilityStateParameters.h"
#include "SpeedStateScaleFactors.h"

#include <array>
#include <cstdint>
#include <vector>

class VarMeasConfig
{
public:
    VarMeasConfig() : measIdList_present{false}, measObjectList_present{false}, reportConfigList_present{false}, quantityConfig_present{false}, s_Measure_present{false}, speedStatePars_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // measIdList
public:
    MeasIdToAddModList* measIdList_Set();
    int measIdList_Set(MeasIdToAddModList &value);
    const MeasIdToAddModList& measIdList_Get() const;
    std::string measIdList_ToString(uint32_t indent) const;
    std::string measIdList_ToStringNoNewLines() const;
    int measIdList_Clear();
    bool measIdList_IsPresent() const;
private:
    bool measIdList_present;
    MeasIdToAddModList measIdList;

    // measObjectList
public:
    MeasObjectToAddModList* measObjectList_Set();
    int measObjectList_Set(MeasObjectToAddModList &value);
    const MeasObjectToAddModList& measObjectList_Get() const;
    std::string measObjectList_ToString(uint32_t indent) const;
    std::string measObjectList_ToStringNoNewLines() const;
    int measObjectList_Clear();
    bool measObjectList_IsPresent() const;
private:
    bool measObjectList_present;
    MeasObjectToAddModList measObjectList;

    // reportConfigList
public:
    ReportConfigToAddModList* reportConfigList_Set();
    int reportConfigList_Set(ReportConfigToAddModList &value);
    const ReportConfigToAddModList& reportConfigList_Get() const;
    std::string reportConfigList_ToString(uint32_t indent) const;
    std::string reportConfigList_ToStringNoNewLines() const;
    int reportConfigList_Clear();
    bool reportConfigList_IsPresent() const;
private:
    bool reportConfigList_present;
    ReportConfigToAddModList reportConfigList;

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
