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

#include "MeasConfig.h"

#include <cmath>

int MeasConfig::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator
    bits.push_back(0);

    // Optional indicators
    bits.push_back(measObjectToRemoveList_IsPresent());
    bits.push_back(measObjectToAddModList_IsPresent());
    bits.push_back(reportConfigToRemoveList_IsPresent());
    bits.push_back(reportConfigToAddModList_IsPresent());
    bits.push_back(measIdToRemoveList_IsPresent());
    bits.push_back(measIdToAddModList_IsPresent());
    bits.push_back(quantityConfig_IsPresent());
    bits.push_back(measGapConfig_IsPresent());
    bits.push_back(s_Measure_IsPresent());
    bits.push_back(preRegistrationInfoHRPD_IsPresent());
    bits.push_back(speedStatePars_IsPresent());

    // Fields
    if(measObjectToRemoveList_IsPresent())
    {
        if(0 != measObjectToRemoveList.Pack(bits))
        {
            printf("MeasConfig:: field pack failure\n");
            return -1;
        }
    }
    if(measObjectToAddModList_IsPresent())
    {
        if(0 != measObjectToAddModList.Pack(bits))
        {
            printf("MeasConfig:: field pack failure\n");
            return -1;
        }
    }
    if(reportConfigToRemoveList_IsPresent())
    {
        if(0 != reportConfigToRemoveList.Pack(bits))
        {
            printf("MeasConfig:: field pack failure\n");
            return -1;
        }
    }
    if(reportConfigToAddModList_IsPresent())
    {
        if(0 != reportConfigToAddModList.Pack(bits))
        {
            printf("MeasConfig:: field pack failure\n");
            return -1;
        }
    }
    if(measIdToRemoveList_IsPresent())
    {
        if(0 != measIdToRemoveList.Pack(bits))
        {
            printf("MeasConfig:: field pack failure\n");
            return -1;
        }
    }
    if(measIdToAddModList_IsPresent())
    {
        if(0 != measIdToAddModList.Pack(bits))
        {
            printf("MeasConfig:: field pack failure\n");
            return -1;
        }
    }
    if(quantityConfig_IsPresent())
    {
        if(0 != quantityConfig.Pack(bits))
        {
            printf("MeasConfig:: field pack failure\n");
            return -1;
        }
    }
    if(measGapConfig_IsPresent())
    {
        if(0 != measGapConfig.Pack(bits))
        {
            printf("MeasConfig:: field pack failure\n");
            return -1;
        }
    }
    if(s_Measure_IsPresent())
    {
        if(0 != s_Measure.Pack(bits))
        {
            printf("MeasConfig:: field pack failure\n");
            return -1;
        }
    }
    if(preRegistrationInfoHRPD_IsPresent())
    {
        if(0 != preRegistrationInfoHRPD.Pack(bits))
        {
            printf("MeasConfig:: field pack failure\n");
            return -1;
        }
    }
    if(speedStatePars_IsPresent())
    {
        if(0 != speedStatePars_Pack(bits))
        {
            printf("MeasConfig:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int MeasConfig::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int MeasConfig::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("MeasConfig::Unpack() index out of bounds for extension\n");
        return -1;
    }
    idx++;

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("MeasConfig::Unpack() index out of bounds for optional indiator measObjectToRemoveList\n");
        return -1;
    }
    measObjectToRemoveList_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("MeasConfig::Unpack() index out of bounds for optional indiator measObjectToAddModList\n");
        return -1;
    }
    measObjectToAddModList_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("MeasConfig::Unpack() index out of bounds for optional indiator reportConfigToRemoveList\n");
        return -1;
    }
    reportConfigToRemoveList_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("MeasConfig::Unpack() index out of bounds for optional indiator reportConfigToAddModList\n");
        return -1;
    }
    reportConfigToAddModList_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("MeasConfig::Unpack() index out of bounds for optional indiator measIdToRemoveList\n");
        return -1;
    }
    measIdToRemoveList_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("MeasConfig::Unpack() index out of bounds for optional indiator measIdToAddModList\n");
        return -1;
    }
    measIdToAddModList_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("MeasConfig::Unpack() index out of bounds for optional indiator quantityConfig\n");
        return -1;
    }
    quantityConfig_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("MeasConfig::Unpack() index out of bounds for optional indiator measGapConfig\n");
        return -1;
    }
    measGapConfig_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("MeasConfig::Unpack() index out of bounds for optional indiator s_Measure\n");
        return -1;
    }
    s_Measure_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("MeasConfig::Unpack() index out of bounds for optional indiator preRegistrationInfoHRPD\n");
        return -1;
    }
    preRegistrationInfoHRPD_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("MeasConfig::Unpack() index out of bounds for optional indiator speedStatePars\n");
        return -1;
    }
    speedStatePars_present = bits[idx++];

    // Fields
    if(measObjectToRemoveList_present)
    {
        if(0 != measObjectToRemoveList.Unpack(bits, idx))
        {
            printf("MeasConfig:: field unpack failure\n");
            return -1;
        }
    }
    if(measObjectToAddModList_present)
    {
        if(0 != measObjectToAddModList.Unpack(bits, idx))
        {
            printf("MeasConfig:: field unpack failure\n");
            return -1;
        }
    }
    if(reportConfigToRemoveList_present)
    {
        if(0 != reportConfigToRemoveList.Unpack(bits, idx))
        {
            printf("MeasConfig:: field unpack failure\n");
            return -1;
        }
    }
    if(reportConfigToAddModList_present)
    {
        if(0 != reportConfigToAddModList.Unpack(bits, idx))
        {
            printf("MeasConfig:: field unpack failure\n");
            return -1;
        }
    }
    if(measIdToRemoveList_present)
    {
        if(0 != measIdToRemoveList.Unpack(bits, idx))
        {
            printf("MeasConfig:: field unpack failure\n");
            return -1;
        }
    }
    if(measIdToAddModList_present)
    {
        if(0 != measIdToAddModList.Unpack(bits, idx))
        {
            printf("MeasConfig:: field unpack failure\n");
            return -1;
        }
    }
    if(quantityConfig_present)
    {
        if(0 != quantityConfig.Unpack(bits, idx))
        {
            printf("MeasConfig:: field unpack failure\n");
            return -1;
        }
    }
    if(measGapConfig_present)
    {
        if(0 != measGapConfig.Unpack(bits, idx))
        {
            printf("MeasConfig:: field unpack failure\n");
            return -1;
        }
    }
    if(s_Measure_present)
    {
        if(0 != s_Measure.Unpack(bits, idx))
        {
            printf("MeasConfig:: field unpack failure\n");
            return -1;
        }
    }
    if(preRegistrationInfoHRPD_present)
    {
        if(0 != preRegistrationInfoHRPD.Unpack(bits, idx))
        {
            printf("MeasConfig:: field unpack failure\n");
            return -1;
        }
    }
    if(speedStatePars_present)
    {
        if(0 != speedStatePars_Unpack(bits, idx))
        {
            printf("MeasConfig:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string MeasConfig::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "MeasConfig:\n";
    if(measObjectToRemoveList_IsPresent())
        out += measObjectToRemoveList_ToString(indent+1);
    if(measObjectToAddModList_IsPresent())
        out += measObjectToAddModList_ToString(indent+1);
    if(reportConfigToRemoveList_IsPresent())
        out += reportConfigToRemoveList_ToString(indent+1);
    if(reportConfigToAddModList_IsPresent())
        out += reportConfigToAddModList_ToString(indent+1);
    if(measIdToRemoveList_IsPresent())
        out += measIdToRemoveList_ToString(indent+1);
    if(measIdToAddModList_IsPresent())
        out += measIdToAddModList_ToString(indent+1);
    if(quantityConfig_IsPresent())
        out += quantityConfig_ToString(indent+1);
    if(measGapConfig_IsPresent())
        out += measGapConfig_ToString(indent+1);
    if(s_Measure_IsPresent())
        out += s_Measure_ToString(indent+1);
    if(preRegistrationInfoHRPD_IsPresent())
        out += preRegistrationInfoHRPD_ToString(indent+1);
    if(speedStatePars_IsPresent())
        out += speedStatePars_ToString(indent+1);
    return out;
}

std::string MeasConfig::ToStringNoNewLines() const
{
    std::string out = "MeasConfig:";
    if(measObjectToRemoveList_IsPresent())
        out += measObjectToRemoveList_ToStringNoNewLines();
    if(measObjectToAddModList_IsPresent())
        out += measObjectToAddModList_ToStringNoNewLines();
    if(reportConfigToRemoveList_IsPresent())
        out += reportConfigToRemoveList_ToStringNoNewLines();
    if(reportConfigToAddModList_IsPresent())
        out += reportConfigToAddModList_ToStringNoNewLines();
    if(measIdToRemoveList_IsPresent())
        out += measIdToRemoveList_ToStringNoNewLines();
    if(measIdToAddModList_IsPresent())
        out += measIdToAddModList_ToStringNoNewLines();
    if(quantityConfig_IsPresent())
        out += quantityConfig_ToStringNoNewLines();
    if(measGapConfig_IsPresent())
        out += measGapConfig_ToStringNoNewLines();
    if(s_Measure_IsPresent())
        out += s_Measure_ToStringNoNewLines();
    if(preRegistrationInfoHRPD_IsPresent())
        out += preRegistrationInfoHRPD_ToStringNoNewLines();
    if(speedStatePars_IsPresent())
        out += speedStatePars_ToStringNoNewLines();
    return out;
}

MeasObjectToRemoveList* MeasConfig::measObjectToRemoveList_Set()
{
    measObjectToRemoveList_present = true;
    return &measObjectToRemoveList;
}

int MeasConfig::measObjectToRemoveList_Set(MeasObjectToRemoveList &value)
{
    measObjectToRemoveList_present = true;
    measObjectToRemoveList = value;
    return 0;
}

const MeasObjectToRemoveList& MeasConfig::measObjectToRemoveList_Get() const
{
    return measObjectToRemoveList;
}

std::string MeasConfig::measObjectToRemoveList_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "measObjectToRemoveList:\n";
    out += measObjectToRemoveList.ToString(indent+1);
    return out;
}

std::string MeasConfig::measObjectToRemoveList_ToStringNoNewLines() const
{
    std::string out = "measObjectToRemoveList:";
    out += measObjectToRemoveList.ToStringNoNewLines();
    return out;
}

int MeasConfig::measObjectToRemoveList_Clear()
{
    measObjectToRemoveList_present = false;
    return 0;
}

bool MeasConfig::measObjectToRemoveList_IsPresent() const
{
    return measObjectToRemoveList_present;
}

MeasObjectToAddModList* MeasConfig::measObjectToAddModList_Set()
{
    measObjectToAddModList_present = true;
    return &measObjectToAddModList;
}

int MeasConfig::measObjectToAddModList_Set(MeasObjectToAddModList &value)
{
    measObjectToAddModList_present = true;
    measObjectToAddModList = value;
    return 0;
}

const MeasObjectToAddModList& MeasConfig::measObjectToAddModList_Get() const
{
    return measObjectToAddModList;
}

std::string MeasConfig::measObjectToAddModList_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "measObjectToAddModList:\n";
    out += measObjectToAddModList.ToString(indent+1);
    return out;
}

std::string MeasConfig::measObjectToAddModList_ToStringNoNewLines() const
{
    std::string out = "measObjectToAddModList:";
    out += measObjectToAddModList.ToStringNoNewLines();
    return out;
}

int MeasConfig::measObjectToAddModList_Clear()
{
    measObjectToAddModList_present = false;
    return 0;
}

bool MeasConfig::measObjectToAddModList_IsPresent() const
{
    return measObjectToAddModList_present;
}

ReportConfigToRemoveList* MeasConfig::reportConfigToRemoveList_Set()
{
    reportConfigToRemoveList_present = true;
    return &reportConfigToRemoveList;
}

int MeasConfig::reportConfigToRemoveList_Set(ReportConfigToRemoveList &value)
{
    reportConfigToRemoveList_present = true;
    reportConfigToRemoveList = value;
    return 0;
}

const ReportConfigToRemoveList& MeasConfig::reportConfigToRemoveList_Get() const
{
    return reportConfigToRemoveList;
}

std::string MeasConfig::reportConfigToRemoveList_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "reportConfigToRemoveList:\n";
    out += reportConfigToRemoveList.ToString(indent+1);
    return out;
}

std::string MeasConfig::reportConfigToRemoveList_ToStringNoNewLines() const
{
    std::string out = "reportConfigToRemoveList:";
    out += reportConfigToRemoveList.ToStringNoNewLines();
    return out;
}

int MeasConfig::reportConfigToRemoveList_Clear()
{
    reportConfigToRemoveList_present = false;
    return 0;
}

bool MeasConfig::reportConfigToRemoveList_IsPresent() const
{
    return reportConfigToRemoveList_present;
}

ReportConfigToAddModList* MeasConfig::reportConfigToAddModList_Set()
{
    reportConfigToAddModList_present = true;
    return &reportConfigToAddModList;
}

int MeasConfig::reportConfigToAddModList_Set(ReportConfigToAddModList &value)
{
    reportConfigToAddModList_present = true;
    reportConfigToAddModList = value;
    return 0;
}

const ReportConfigToAddModList& MeasConfig::reportConfigToAddModList_Get() const
{
    return reportConfigToAddModList;
}

std::string MeasConfig::reportConfigToAddModList_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "reportConfigToAddModList:\n";
    out += reportConfigToAddModList.ToString(indent+1);
    return out;
}

std::string MeasConfig::reportConfigToAddModList_ToStringNoNewLines() const
{
    std::string out = "reportConfigToAddModList:";
    out += reportConfigToAddModList.ToStringNoNewLines();
    return out;
}

int MeasConfig::reportConfigToAddModList_Clear()
{
    reportConfigToAddModList_present = false;
    return 0;
}

bool MeasConfig::reportConfigToAddModList_IsPresent() const
{
    return reportConfigToAddModList_present;
}

MeasIdToRemoveList* MeasConfig::measIdToRemoveList_Set()
{
    measIdToRemoveList_present = true;
    return &measIdToRemoveList;
}

int MeasConfig::measIdToRemoveList_Set(MeasIdToRemoveList &value)
{
    measIdToRemoveList_present = true;
    measIdToRemoveList = value;
    return 0;
}

const MeasIdToRemoveList& MeasConfig::measIdToRemoveList_Get() const
{
    return measIdToRemoveList;
}

std::string MeasConfig::measIdToRemoveList_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "measIdToRemoveList:\n";
    out += measIdToRemoveList.ToString(indent+1);
    return out;
}

std::string MeasConfig::measIdToRemoveList_ToStringNoNewLines() const
{
    std::string out = "measIdToRemoveList:";
    out += measIdToRemoveList.ToStringNoNewLines();
    return out;
}

int MeasConfig::measIdToRemoveList_Clear()
{
    measIdToRemoveList_present = false;
    return 0;
}

bool MeasConfig::measIdToRemoveList_IsPresent() const
{
    return measIdToRemoveList_present;
}

MeasIdToAddModList* MeasConfig::measIdToAddModList_Set()
{
    measIdToAddModList_present = true;
    return &measIdToAddModList;
}

int MeasConfig::measIdToAddModList_Set(MeasIdToAddModList &value)
{
    measIdToAddModList_present = true;
    measIdToAddModList = value;
    return 0;
}

const MeasIdToAddModList& MeasConfig::measIdToAddModList_Get() const
{
    return measIdToAddModList;
}

std::string MeasConfig::measIdToAddModList_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "measIdToAddModList:\n";
    out += measIdToAddModList.ToString(indent+1);
    return out;
}

std::string MeasConfig::measIdToAddModList_ToStringNoNewLines() const
{
    std::string out = "measIdToAddModList:";
    out += measIdToAddModList.ToStringNoNewLines();
    return out;
}

int MeasConfig::measIdToAddModList_Clear()
{
    measIdToAddModList_present = false;
    return 0;
}

bool MeasConfig::measIdToAddModList_IsPresent() const
{
    return measIdToAddModList_present;
}

QuantityConfig* MeasConfig::quantityConfig_Set()
{
    quantityConfig_present = true;
    return &quantityConfig;
}

int MeasConfig::quantityConfig_Set(QuantityConfig &value)
{
    quantityConfig_present = true;
    quantityConfig = value;
    return 0;
}

const QuantityConfig& MeasConfig::quantityConfig_Get() const
{
    return quantityConfig;
}

std::string MeasConfig::quantityConfig_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "quantityConfig:\n";
    out += quantityConfig.ToString(indent+1);
    return out;
}

std::string MeasConfig::quantityConfig_ToStringNoNewLines() const
{
    std::string out = "quantityConfig:";
    out += quantityConfig.ToStringNoNewLines();
    return out;
}

int MeasConfig::quantityConfig_Clear()
{
    quantityConfig_present = false;
    return 0;
}

bool MeasConfig::quantityConfig_IsPresent() const
{
    return quantityConfig_present;
}

MeasGapConfig* MeasConfig::measGapConfig_Set()
{
    measGapConfig_present = true;
    return &measGapConfig;
}

int MeasConfig::measGapConfig_Set(MeasGapConfig &value)
{
    measGapConfig_present = true;
    measGapConfig = value;
    return 0;
}

const MeasGapConfig& MeasConfig::measGapConfig_Get() const
{
    return measGapConfig;
}

std::string MeasConfig::measGapConfig_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "measGapConfig:\n";
    out += measGapConfig.ToString(indent+1);
    return out;
}

std::string MeasConfig::measGapConfig_ToStringNoNewLines() const
{
    std::string out = "measGapConfig:";
    out += measGapConfig.ToStringNoNewLines();
    return out;
}

int MeasConfig::measGapConfig_Clear()
{
    measGapConfig_present = false;
    return 0;
}

bool MeasConfig::measGapConfig_IsPresent() const
{
    return measGapConfig_present;
}

RSRP_Range* MeasConfig::s_Measure_Set()
{
    s_Measure_present = true;
    return &s_Measure;
}

int MeasConfig::s_Measure_Set(RSRP_Range &value)
{
    s_Measure_present = true;
    s_Measure = value;
    return 0;
}

const RSRP_Range& MeasConfig::s_Measure_Get() const
{
    return s_Measure;
}

std::string MeasConfig::s_Measure_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "s_Measure:\n";
    out += s_Measure.ToString(indent+1);
    return out;
}

std::string MeasConfig::s_Measure_ToStringNoNewLines() const
{
    std::string out = "s_Measure:";
    out += s_Measure.ToStringNoNewLines();
    return out;
}

int MeasConfig::s_Measure_Clear()
{
    s_Measure_present = false;
    return 0;
}

bool MeasConfig::s_Measure_IsPresent() const
{
    return s_Measure_present;
}

PreRegistrationInfoHRPD* MeasConfig::preRegistrationInfoHRPD_Set()
{
    preRegistrationInfoHRPD_present = true;
    return &preRegistrationInfoHRPD;
}

int MeasConfig::preRegistrationInfoHRPD_Set(PreRegistrationInfoHRPD &value)
{
    preRegistrationInfoHRPD_present = true;
    preRegistrationInfoHRPD = value;
    return 0;
}

const PreRegistrationInfoHRPD& MeasConfig::preRegistrationInfoHRPD_Get() const
{
    return preRegistrationInfoHRPD;
}

std::string MeasConfig::preRegistrationInfoHRPD_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "preRegistrationInfoHRPD:\n";
    out += preRegistrationInfoHRPD.ToString(indent+1);
    return out;
}

std::string MeasConfig::preRegistrationInfoHRPD_ToStringNoNewLines() const
{
    std::string out = "preRegistrationInfoHRPD:";
    out += preRegistrationInfoHRPD.ToStringNoNewLines();
    return out;
}

int MeasConfig::preRegistrationInfoHRPD_Clear()
{
    preRegistrationInfoHRPD_present = false;
    return 0;
}

bool MeasConfig::preRegistrationInfoHRPD_IsPresent() const
{
    return preRegistrationInfoHRPD_present;
}

int MeasConfig::speedStatePars_Pack(std::vector<uint8_t> &bits)
{
    if(!speedStatePars_present)
    {
        printf("MeasConfig::speedStatePars_Pack() presence failure\n");
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
            printf("MeasConfig::speedStatePars_release pack failure\n");
            return -1;
        }
    }
    if(speedStatePars_internal_choice == k_speedStatePars_setup)
    {
        if(0 != speedStatePars_setup_value.Pack(bits))
        {
            printf("MeasConfig::speedStatePars_setup pack failure\n");
            return -1;
        }
    }
    return 0;
}

int MeasConfig::speedStatePars_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return speedStatePars_Unpack(bits, idx);
}

int MeasConfig::speedStatePars_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 1) > bits.size())
    {
        printf("MeasConfig::speedStatePars_Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<1; i++)
        packed_val |= bits[idx++] << (1-i-1);

    if((MeasConfig::speedStatePars_Enum)packed_val > k_speedStatePars_setup)
    {
        printf("MeasConfig::speedStatePars_Unpack() choice range failure\n");
        return -1;
    }
    speedStatePars_internal_choice = (MeasConfig::speedStatePars_Enum)packed_val;
    speedStatePars_present = true;

    // Fields
    if(speedStatePars_internal_choice == k_speedStatePars_release)
    {
        if(0 != speedStatePars_release_Unpack(bits, idx))
        {
            printf("MeasConfig::speedStatePars_release unpack failure\n");
            return -1;
        }
    }
    if(speedStatePars_internal_choice == k_speedStatePars_setup)
    {
        if(0 != speedStatePars_setup_value.Unpack(bits, idx))
        {
            printf("MeasConfig::speedStatePars_setup unpack failure\n");
            return -1;
        }
    }
    return 0;
}

MeasConfig::speedStatePars_Enum MeasConfig::speedStatePars_Choice() const
{
    if(speedStatePars_present)
        return speedStatePars_internal_choice;
    return (MeasConfig::speedStatePars_Enum)0;
}

int MeasConfig::speedStatePars_SetChoice(MeasConfig::speedStatePars_Enum choice)
{
    speedStatePars_internal_choice = choice;
    speedStatePars_present = true;
    return 0;
}

std::string MeasConfig::speedStatePars_ChoiceToString(speedStatePars_Enum value) const
{
    if(k_speedStatePars_release == value)
        return "speedStatePars_release";
    if(k_speedStatePars_setup == value)
        return "speedStatePars_setup";
    return "";
}

uint64_t MeasConfig::speedStatePars_NumberOfChoices() const
{
    return 2;
}

std::string MeasConfig::speedStatePars_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "speedStatePars = " + speedStatePars_ChoiceToString(speedStatePars_internal_choice) + ":\n";
    if(speedStatePars_internal_choice == k_speedStatePars_setup)
        out += speedStatePars_setup_value.ToString(indent+1);
    return out;
}

std::string MeasConfig::speedStatePars_ToStringNoNewLines() const
{
    std::string out = "speedStatePars=" + speedStatePars_ChoiceToString(speedStatePars_internal_choice) + ",";
    if(speedStatePars_internal_choice == k_speedStatePars_setup)
        out += speedStatePars_setup_value.ToStringNoNewLines();
    return out;
}

int MeasConfig::speedStatePars_Clear()
{
    speedStatePars_present = false;
    return 0;
}

bool MeasConfig::speedStatePars_IsPresent() const
{
    return speedStatePars_present;
}

int MeasConfig::speedStatePars_setup::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != mobilityStateParameters.Pack(bits))
        {
            printf("MeasConfig::speedStatePars_setup:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != timeToTrigger_SF.Pack(bits))
        {
            printf("MeasConfig::speedStatePars_setup:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int MeasConfig::speedStatePars_setup::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int MeasConfig::speedStatePars_setup::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != mobilityStateParameters.Unpack(bits, idx))
        {
            printf("MeasConfig::speedStatePars_setup:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != timeToTrigger_SF.Unpack(bits, idx))
        {
            printf("MeasConfig::speedStatePars_setup:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string MeasConfig::speedStatePars_setup::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "setup:\n";
    out += mobilityStateParameters_ToString(indent+1);
    out += timeToTrigger_SF_ToString(indent+1);
    return out;
}

std::string MeasConfig::speedStatePars_setup::ToStringNoNewLines() const
{
    std::string out = "setup:";
    out += mobilityStateParameters_ToStringNoNewLines();
    out += timeToTrigger_SF_ToStringNoNewLines();
    return out;
}

MobilityStateParameters* MeasConfig::speedStatePars_setup::mobilityStateParameters_Set()
{
    mobilityStateParameters_present = true;
    return &mobilityStateParameters;
}

int MeasConfig::speedStatePars_setup::mobilityStateParameters_Set(MobilityStateParameters &value)
{
    mobilityStateParameters_present = true;
    mobilityStateParameters = value;
    return 0;
}

const MobilityStateParameters& MeasConfig::speedStatePars_setup::mobilityStateParameters_Get() const
{
    return mobilityStateParameters;
}

std::string MeasConfig::speedStatePars_setup::mobilityStateParameters_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "mobilityStateParameters:\n";
    out += mobilityStateParameters.ToString(indent+1);
    return out;
}

std::string MeasConfig::speedStatePars_setup::mobilityStateParameters_ToStringNoNewLines() const
{
    std::string out = "mobilityStateParameters:";
    out += mobilityStateParameters.ToStringNoNewLines();
    return out;
}

int MeasConfig::speedStatePars_setup::mobilityStateParameters_Clear()
{
    mobilityStateParameters_present = false;
    return 0;
}

bool MeasConfig::speedStatePars_setup::mobilityStateParameters_IsPresent() const
{
    return mobilityStateParameters_present;
}

SpeedStateScaleFactors* MeasConfig::speedStatePars_setup::timeToTrigger_SF_Set()
{
    timeToTrigger_SF_present = true;
    return &timeToTrigger_SF;
}

int MeasConfig::speedStatePars_setup::timeToTrigger_SF_Set(SpeedStateScaleFactors &value)
{
    timeToTrigger_SF_present = true;
    timeToTrigger_SF = value;
    return 0;
}

const SpeedStateScaleFactors& MeasConfig::speedStatePars_setup::timeToTrigger_SF_Get() const
{
    return timeToTrigger_SF;
}

std::string MeasConfig::speedStatePars_setup::timeToTrigger_SF_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "timeToTrigger_SF:\n";
    out += timeToTrigger_SF.ToString(indent+1);
    return out;
}

std::string MeasConfig::speedStatePars_setup::timeToTrigger_SF_ToStringNoNewLines() const
{
    std::string out = "timeToTrigger_SF:";
    out += timeToTrigger_SF.ToStringNoNewLines();
    return out;
}

int MeasConfig::speedStatePars_setup::timeToTrigger_SF_Clear()
{
    timeToTrigger_SF_present = false;
    return 0;
}

bool MeasConfig::speedStatePars_setup::timeToTrigger_SF_IsPresent() const
{
    return timeToTrigger_SF_present;
}

