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

#include "VarMeasConfig.h"

#include <cmath>

int VarMeasConfig::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(measIdList_IsPresent());
    bits.push_back(measObjectList_IsPresent());
    bits.push_back(reportConfigList_IsPresent());
    bits.push_back(quantityConfig_IsPresent());
    bits.push_back(s_Measure_IsPresent());
    bits.push_back(speedStatePars_IsPresent());

    // Fields
    if(measIdList_IsPresent())
    {
        if(0 != measIdList.Pack(bits))
        {
            printf("VarMeasConfig:: field pack failure\n");
            return -1;
        }
    }
    if(measObjectList_IsPresent())
    {
        if(0 != measObjectList.Pack(bits))
        {
            printf("VarMeasConfig:: field pack failure\n");
            return -1;
        }
    }
    if(reportConfigList_IsPresent())
    {
        if(0 != reportConfigList.Pack(bits))
        {
            printf("VarMeasConfig:: field pack failure\n");
            return -1;
        }
    }
    if(quantityConfig_IsPresent())
    {
        if(0 != quantityConfig.Pack(bits))
        {
            printf("VarMeasConfig:: field pack failure\n");
            return -1;
        }
    }
    if(s_Measure_IsPresent())
    {
        if(0 != s_Measure.Pack(bits))
        {
            printf("VarMeasConfig:: field pack failure\n");
            return -1;
        }
    }
    if(speedStatePars_IsPresent())
    {
        if(0 != speedStatePars_Pack(bits))
        {
            printf("VarMeasConfig:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int VarMeasConfig::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int VarMeasConfig::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("VarMeasConfig::Unpack() index out of bounds for optional indiator measIdList\n");
        return -1;
    }
    measIdList_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("VarMeasConfig::Unpack() index out of bounds for optional indiator measObjectList\n");
        return -1;
    }
    measObjectList_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("VarMeasConfig::Unpack() index out of bounds for optional indiator reportConfigList\n");
        return -1;
    }
    reportConfigList_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("VarMeasConfig::Unpack() index out of bounds for optional indiator quantityConfig\n");
        return -1;
    }
    quantityConfig_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("VarMeasConfig::Unpack() index out of bounds for optional indiator s_Measure\n");
        return -1;
    }
    s_Measure_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("VarMeasConfig::Unpack() index out of bounds for optional indiator speedStatePars\n");
        return -1;
    }
    speedStatePars_present = bits[idx++];

    // Fields
    if(measIdList_present)
    {
        if(0 != measIdList.Unpack(bits, idx))
        {
            printf("VarMeasConfig:: field unpack failure\n");
            return -1;
        }
    }
    if(measObjectList_present)
    {
        if(0 != measObjectList.Unpack(bits, idx))
        {
            printf("VarMeasConfig:: field unpack failure\n");
            return -1;
        }
    }
    if(reportConfigList_present)
    {
        if(0 != reportConfigList.Unpack(bits, idx))
        {
            printf("VarMeasConfig:: field unpack failure\n");
            return -1;
        }
    }
    if(quantityConfig_present)
    {
        if(0 != quantityConfig.Unpack(bits, idx))
        {
            printf("VarMeasConfig:: field unpack failure\n");
            return -1;
        }
    }
    if(s_Measure_present)
    {
        if(0 != s_Measure.Unpack(bits, idx))
        {
            printf("VarMeasConfig:: field unpack failure\n");
            return -1;
        }
    }
    if(speedStatePars_present)
    {
        if(0 != speedStatePars_Unpack(bits, idx))
        {
            printf("VarMeasConfig:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string VarMeasConfig::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "VarMeasConfig:\n";
    if(measIdList_IsPresent())
        out += measIdList_ToString(indent+1);
    if(measObjectList_IsPresent())
        out += measObjectList_ToString(indent+1);
    if(reportConfigList_IsPresent())
        out += reportConfigList_ToString(indent+1);
    if(quantityConfig_IsPresent())
        out += quantityConfig_ToString(indent+1);
    if(s_Measure_IsPresent())
        out += s_Measure_ToString(indent+1);
    if(speedStatePars_IsPresent())
        out += speedStatePars_ToString(indent+1);
    return out;
}

std::string VarMeasConfig::ToStringNoNewLines() const
{
    std::string out = "VarMeasConfig:";
    if(measIdList_IsPresent())
        out += measIdList_ToStringNoNewLines();
    if(measObjectList_IsPresent())
        out += measObjectList_ToStringNoNewLines();
    if(reportConfigList_IsPresent())
        out += reportConfigList_ToStringNoNewLines();
    if(quantityConfig_IsPresent())
        out += quantityConfig_ToStringNoNewLines();
    if(s_Measure_IsPresent())
        out += s_Measure_ToStringNoNewLines();
    if(speedStatePars_IsPresent())
        out += speedStatePars_ToStringNoNewLines();
    return out;
}

MeasIdToAddModList* VarMeasConfig::measIdList_Set()
{
    measIdList_present = true;
    return &measIdList;
}

int VarMeasConfig::measIdList_Set(MeasIdToAddModList &value)
{
    measIdList_present = true;
    measIdList = value;
    return 0;
}

const MeasIdToAddModList& VarMeasConfig::measIdList_Get() const
{
    return measIdList;
}

std::string VarMeasConfig::measIdList_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "measIdList:\n";
    out += measIdList.ToString(indent+1);
    return out;
}

std::string VarMeasConfig::measIdList_ToStringNoNewLines() const
{
    std::string out = "measIdList:";
    out += measIdList.ToStringNoNewLines();
    return out;
}

int VarMeasConfig::measIdList_Clear()
{
    measIdList_present = false;
    return 0;
}

bool VarMeasConfig::measIdList_IsPresent() const
{
    return measIdList_present;
}

MeasObjectToAddModList* VarMeasConfig::measObjectList_Set()
{
    measObjectList_present = true;
    return &measObjectList;
}

int VarMeasConfig::measObjectList_Set(MeasObjectToAddModList &value)
{
    measObjectList_present = true;
    measObjectList = value;
    return 0;
}

const MeasObjectToAddModList& VarMeasConfig::measObjectList_Get() const
{
    return measObjectList;
}

std::string VarMeasConfig::measObjectList_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "measObjectList:\n";
    out += measObjectList.ToString(indent+1);
    return out;
}

std::string VarMeasConfig::measObjectList_ToStringNoNewLines() const
{
    std::string out = "measObjectList:";
    out += measObjectList.ToStringNoNewLines();
    return out;
}

int VarMeasConfig::measObjectList_Clear()
{
    measObjectList_present = false;
    return 0;
}

bool VarMeasConfig::measObjectList_IsPresent() const
{
    return measObjectList_present;
}

ReportConfigToAddModList* VarMeasConfig::reportConfigList_Set()
{
    reportConfigList_present = true;
    return &reportConfigList;
}

int VarMeasConfig::reportConfigList_Set(ReportConfigToAddModList &value)
{
    reportConfigList_present = true;
    reportConfigList = value;
    return 0;
}

const ReportConfigToAddModList& VarMeasConfig::reportConfigList_Get() const
{
    return reportConfigList;
}

std::string VarMeasConfig::reportConfigList_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "reportConfigList:\n";
    out += reportConfigList.ToString(indent+1);
    return out;
}

std::string VarMeasConfig::reportConfigList_ToStringNoNewLines() const
{
    std::string out = "reportConfigList:";
    out += reportConfigList.ToStringNoNewLines();
    return out;
}

int VarMeasConfig::reportConfigList_Clear()
{
    reportConfigList_present = false;
    return 0;
}

bool VarMeasConfig::reportConfigList_IsPresent() const
{
    return reportConfigList_present;
}

QuantityConfig* VarMeasConfig::quantityConfig_Set()
{
    quantityConfig_present = true;
    return &quantityConfig;
}

int VarMeasConfig::quantityConfig_Set(QuantityConfig &value)
{
    quantityConfig_present = true;
    quantityConfig = value;
    return 0;
}

const QuantityConfig& VarMeasConfig::quantityConfig_Get() const
{
    return quantityConfig;
}

std::string VarMeasConfig::quantityConfig_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "quantityConfig:\n";
    out += quantityConfig.ToString(indent+1);
    return out;
}

std::string VarMeasConfig::quantityConfig_ToStringNoNewLines() const
{
    std::string out = "quantityConfig:";
    out += quantityConfig.ToStringNoNewLines();
    return out;
}

int VarMeasConfig::quantityConfig_Clear()
{
    quantityConfig_present = false;
    return 0;
}

bool VarMeasConfig::quantityConfig_IsPresent() const
{
    return quantityConfig_present;
}

RSRP_Range* VarMeasConfig::s_Measure_Set()
{
    s_Measure_present = true;
    return &s_Measure;
}

int VarMeasConfig::s_Measure_Set(RSRP_Range &value)
{
    s_Measure_present = true;
    s_Measure = value;
    return 0;
}

const RSRP_Range& VarMeasConfig::s_Measure_Get() const
{
    return s_Measure;
}

std::string VarMeasConfig::s_Measure_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "s_Measure:\n";
    out += s_Measure.ToString(indent+1);
    return out;
}

std::string VarMeasConfig::s_Measure_ToStringNoNewLines() const
{
    std::string out = "s_Measure:";
    out += s_Measure.ToStringNoNewLines();
    return out;
}

int VarMeasConfig::s_Measure_Clear()
{
    s_Measure_present = false;
    return 0;
}

bool VarMeasConfig::s_Measure_IsPresent() const
{
    return s_Measure_present;
}

int VarMeasConfig::speedStatePars_Pack(std::vector<uint8_t> &bits)
{
    if(!speedStatePars_present)
    {
        printf("VarMeasConfig::speedStatePars_Pack() presence failure\n");
        return -1;
    }
    // Extension indicator

    // Choice
    for(uint32_t i=0; i<1; i++)
        bits.push_back((speedStatePars_internal_choice >> (1-i-1)) & 1);

    // Fields
    if(speedStatePars_internal_choice == k_speedStatePars_release)
    {
        if(0 != speedStatePars_release_Pack(bits))
        {
            printf("VarMeasConfig::speedStatePars_release pack failure\n");
            return -1;
        }
    }
    if(speedStatePars_internal_choice == k_speedStatePars_setup)
    {
        if(0 != speedStatePars_setup_value.Pack(bits))
        {
            printf("VarMeasConfig::speedStatePars_setup pack failure\n");
            return -1;
        }
    }
    return 0;
}

int VarMeasConfig::speedStatePars_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return speedStatePars_Unpack(bits, idx);
}

int VarMeasConfig::speedStatePars_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 1) > bits.size())
    {
        printf("VarMeasConfig::speedStatePars_Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<1; i++)
        packed_val |= bits[idx++] << (1-i-1);

    if((VarMeasConfig::speedStatePars_Enum)packed_val > k_speedStatePars_setup)
    {
        printf("VarMeasConfig::speedStatePars_Unpack() choice range failure\n");
        return -1;
    }
    speedStatePars_internal_choice = (VarMeasConfig::speedStatePars_Enum)packed_val;
    speedStatePars_present = true;

    // Fields
    if(speedStatePars_internal_choice == k_speedStatePars_release)
    {
        if(0 != speedStatePars_release_Unpack(bits, idx))
        {
            printf("VarMeasConfig::speedStatePars_release unpack failure\n");
            return -1;
        }
    }
    if(speedStatePars_internal_choice == k_speedStatePars_setup)
    {
        if(0 != speedStatePars_setup_value.Unpack(bits, idx))
        {
            printf("VarMeasConfig::speedStatePars_setup unpack failure\n");
            return -1;
        }
    }
    return 0;
}

VarMeasConfig::speedStatePars_Enum VarMeasConfig::speedStatePars_Choice() const
{
    if(speedStatePars_present)
        return speedStatePars_internal_choice;
    return (VarMeasConfig::speedStatePars_Enum)0;
}

int VarMeasConfig::speedStatePars_SetChoice(VarMeasConfig::speedStatePars_Enum choice)
{
    speedStatePars_internal_choice = choice;
    speedStatePars_present = true;
    return 0;
}

std::string VarMeasConfig::speedStatePars_ChoiceToString(speedStatePars_Enum value) const
{
    if(k_speedStatePars_release == value)
        return "speedStatePars_release";
    if(k_speedStatePars_setup == value)
        return "speedStatePars_setup";
    return "";
}

uint64_t VarMeasConfig::speedStatePars_NumberOfChoices() const
{
    return 2;
}

std::string VarMeasConfig::speedStatePars_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "speedStatePars = " + speedStatePars_ChoiceToString(speedStatePars_internal_choice) + ":\n";
    if(speedStatePars_internal_choice == k_speedStatePars_setup)
        out += speedStatePars_setup_value.ToString(indent+1);
    return out;
}

std::string VarMeasConfig::speedStatePars_ToStringNoNewLines() const
{
    std::string out = "speedStatePars=" + speedStatePars_ChoiceToString(speedStatePars_internal_choice) + ",";
    if(speedStatePars_internal_choice == k_speedStatePars_setup)
        out += speedStatePars_setup_value.ToStringNoNewLines();
    return out;
}

int VarMeasConfig::speedStatePars_Clear()
{
    speedStatePars_present = false;
    return 0;
}

bool VarMeasConfig::speedStatePars_IsPresent() const
{
    return speedStatePars_present;
}

int VarMeasConfig::speedStatePars_setup::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != mobilityStateParameters.Pack(bits))
        {
            printf("VarMeasConfig::speedStatePars_setup:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != timeToTrigger_SF.Pack(bits))
        {
            printf("VarMeasConfig::speedStatePars_setup:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int VarMeasConfig::speedStatePars_setup::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int VarMeasConfig::speedStatePars_setup::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != mobilityStateParameters.Unpack(bits, idx))
        {
            printf("VarMeasConfig::speedStatePars_setup:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != timeToTrigger_SF.Unpack(bits, idx))
        {
            printf("VarMeasConfig::speedStatePars_setup:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string VarMeasConfig::speedStatePars_setup::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "setup:\n";
    out += mobilityStateParameters_ToString(indent+1);
    out += timeToTrigger_SF_ToString(indent+1);
    return out;
}

std::string VarMeasConfig::speedStatePars_setup::ToStringNoNewLines() const
{
    std::string out = "setup:";
    out += mobilityStateParameters_ToStringNoNewLines();
    out += timeToTrigger_SF_ToStringNoNewLines();
    return out;
}

MobilityStateParameters* VarMeasConfig::speedStatePars_setup::mobilityStateParameters_Set()
{
    mobilityStateParameters_present = true;
    return &mobilityStateParameters;
}

int VarMeasConfig::speedStatePars_setup::mobilityStateParameters_Set(MobilityStateParameters &value)
{
    mobilityStateParameters_present = true;
    mobilityStateParameters = value;
    return 0;
}

const MobilityStateParameters& VarMeasConfig::speedStatePars_setup::mobilityStateParameters_Get() const
{
    return mobilityStateParameters;
}

std::string VarMeasConfig::speedStatePars_setup::mobilityStateParameters_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "mobilityStateParameters:\n";
    out += mobilityStateParameters.ToString(indent+1);
    return out;
}

std::string VarMeasConfig::speedStatePars_setup::mobilityStateParameters_ToStringNoNewLines() const
{
    std::string out = "mobilityStateParameters:";
    out += mobilityStateParameters.ToStringNoNewLines();
    return out;
}

int VarMeasConfig::speedStatePars_setup::mobilityStateParameters_Clear()
{
    mobilityStateParameters_present = false;
    return 0;
}

bool VarMeasConfig::speedStatePars_setup::mobilityStateParameters_IsPresent() const
{
    return mobilityStateParameters_present;
}

SpeedStateScaleFactors* VarMeasConfig::speedStatePars_setup::timeToTrigger_SF_Set()
{
    timeToTrigger_SF_present = true;
    return &timeToTrigger_SF;
}

int VarMeasConfig::speedStatePars_setup::timeToTrigger_SF_Set(SpeedStateScaleFactors &value)
{
    timeToTrigger_SF_present = true;
    timeToTrigger_SF = value;
    return 0;
}

const SpeedStateScaleFactors& VarMeasConfig::speedStatePars_setup::timeToTrigger_SF_Get() const
{
    return timeToTrigger_SF;
}

std::string VarMeasConfig::speedStatePars_setup::timeToTrigger_SF_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "timeToTrigger_SF:\n";
    out += timeToTrigger_SF.ToString(indent+1);
    return out;
}

std::string VarMeasConfig::speedStatePars_setup::timeToTrigger_SF_ToStringNoNewLines() const
{
    std::string out = "timeToTrigger_SF:";
    out += timeToTrigger_SF.ToStringNoNewLines();
    return out;
}

int VarMeasConfig::speedStatePars_setup::timeToTrigger_SF_Clear()
{
    timeToTrigger_SF_present = false;
    return 0;
}

bool VarMeasConfig::speedStatePars_setup::timeToTrigger_SF_IsPresent() const
{
    return timeToTrigger_SF_present;
}

