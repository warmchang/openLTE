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

#include "ReportProximityConfig_r9.h"

#include <cmath>

int ReportProximityConfig_r9::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(proximityIndicationEUTRA_r9_IsPresent());
    bits.push_back(proximityIndicationUTRA_r9_IsPresent());

    // Fields
    if(proximityIndicationEUTRA_r9_IsPresent())
    {
        if(0 != proximityIndicationEUTRA_r9_Pack(bits))
        {
            printf("ReportProximityConfig_r9:: field pack failure\n");
            return -1;
        }
    }
    if(proximityIndicationUTRA_r9_IsPresent())
    {
        if(0 != proximityIndicationUTRA_r9_Pack(bits))
        {
            printf("ReportProximityConfig_r9:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int ReportProximityConfig_r9::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int ReportProximityConfig_r9::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("ReportProximityConfig_r9::Unpack() index out of bounds for optional indiator proximityIndicationEUTRA_r9\n");
        return -1;
    }
    proximityIndicationEUTRA_r9_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("ReportProximityConfig_r9::Unpack() index out of bounds for optional indiator proximityIndicationUTRA_r9\n");
        return -1;
    }
    proximityIndicationUTRA_r9_present = bits[idx++];

    // Fields
    if(proximityIndicationEUTRA_r9_present)
    {
        if(0 != proximityIndicationEUTRA_r9_Unpack(bits, idx))
        {
            printf("ReportProximityConfig_r9:: field unpack failure\n");
            return -1;
        }
    }
    if(proximityIndicationUTRA_r9_present)
    {
        if(0 != proximityIndicationUTRA_r9_Unpack(bits, idx))
        {
            printf("ReportProximityConfig_r9:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string ReportProximityConfig_r9::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ReportProximityConfig_r9:\n";
    if(proximityIndicationEUTRA_r9_IsPresent())
        out += proximityIndicationEUTRA_r9_ToString(indent+1);
    if(proximityIndicationUTRA_r9_IsPresent())
        out += proximityIndicationUTRA_r9_ToString(indent+1);
    return out;
}

std::string ReportProximityConfig_r9::ToStringNoNewLines() const
{
    std::string out = "ReportProximityConfig_r9:";
    if(proximityIndicationEUTRA_r9_IsPresent())
        out += proximityIndicationEUTRA_r9_ToStringNoNewLines();
    if(proximityIndicationUTRA_r9_IsPresent())
        out += proximityIndicationUTRA_r9_ToStringNoNewLines();
    return out;
}

int ReportProximityConfig_r9::proximityIndicationEUTRA_r9_Pack(std::vector<uint8_t> &bits)
{
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((proximityIndicationEUTRA_r9_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int ReportProximityConfig_r9::proximityIndicationEUTRA_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return proximityIndicationEUTRA_r9_Unpack(bits, idx);
}

int ReportProximityConfig_r9::proximityIndicationEUTRA_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("ReportProximityConfig_r9::proximityIndicationEUTRA_r9_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 0)
    {
        printf("ReportProximityConfig_r9::proximityIndicationEUTRA_r9_Unpack() max failure\n");
        return -1;
    }
    proximityIndicationEUTRA_r9_internal_value = (proximityIndicationEUTRA_r9_Enum)packed_val;
    proximityIndicationEUTRA_r9_present = true;
    return 0;
}

ReportProximityConfig_r9::proximityIndicationEUTRA_r9_Enum ReportProximityConfig_r9::proximityIndicationEUTRA_r9_Value() const
{
    if(proximityIndicationEUTRA_r9_present)
        return proximityIndicationEUTRA_r9_internal_value;
    return (ReportProximityConfig_r9::proximityIndicationEUTRA_r9_Enum)0;
}

int ReportProximityConfig_r9::proximityIndicationEUTRA_r9_SetValue(proximityIndicationEUTRA_r9_Enum value)
{
    proximityIndicationEUTRA_r9_internal_value = value;
    proximityIndicationEUTRA_r9_present = true;
    return 0;
}

int ReportProximityConfig_r9::proximityIndicationEUTRA_r9_SetValue(std::string value)
{
    if("enabled" == value)
    {
        proximityIndicationEUTRA_r9_internal_value = k_proximityIndicationEUTRA_r9_enabled;
        proximityIndicationEUTRA_r9_present = true;
        return 0;
    }
    return 1;
}

std::string ReportProximityConfig_r9::proximityIndicationEUTRA_r9_ValueToString(proximityIndicationEUTRA_r9_Enum value) const
{
    if(k_proximityIndicationEUTRA_r9_enabled == value)
        return "enabled";
    return "";
}

uint64_t ReportProximityConfig_r9::proximityIndicationEUTRA_r9_NumberOfValues() const
{
    return 1;
}

std::string ReportProximityConfig_r9::proximityIndicationEUTRA_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "proximityIndicationEUTRA_r9 = " + proximityIndicationEUTRA_r9_ValueToString(proximityIndicationEUTRA_r9_internal_value) + "\n";
    return out;
}

std::string ReportProximityConfig_r9::proximityIndicationEUTRA_r9_ToStringNoNewLines() const
{
    std::string out = "proximityIndicationEUTRA_r9=" + proximityIndicationEUTRA_r9_ValueToString(proximityIndicationEUTRA_r9_internal_value) + ",";
    return out;
}

int ReportProximityConfig_r9::proximityIndicationEUTRA_r9_Clear()
{
    proximityIndicationEUTRA_r9_present = false;
    return 0;
}

bool ReportProximityConfig_r9::proximityIndicationEUTRA_r9_IsPresent() const
{
    return proximityIndicationEUTRA_r9_present;
}

int ReportProximityConfig_r9::proximityIndicationUTRA_r9_Pack(std::vector<uint8_t> &bits)
{
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((proximityIndicationUTRA_r9_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int ReportProximityConfig_r9::proximityIndicationUTRA_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return proximityIndicationUTRA_r9_Unpack(bits, idx);
}

int ReportProximityConfig_r9::proximityIndicationUTRA_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("ReportProximityConfig_r9::proximityIndicationUTRA_r9_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 0)
    {
        printf("ReportProximityConfig_r9::proximityIndicationUTRA_r9_Unpack() max failure\n");
        return -1;
    }
    proximityIndicationUTRA_r9_internal_value = (proximityIndicationUTRA_r9_Enum)packed_val;
    proximityIndicationUTRA_r9_present = true;
    return 0;
}

ReportProximityConfig_r9::proximityIndicationUTRA_r9_Enum ReportProximityConfig_r9::proximityIndicationUTRA_r9_Value() const
{
    if(proximityIndicationUTRA_r9_present)
        return proximityIndicationUTRA_r9_internal_value;
    return (ReportProximityConfig_r9::proximityIndicationUTRA_r9_Enum)0;
}

int ReportProximityConfig_r9::proximityIndicationUTRA_r9_SetValue(proximityIndicationUTRA_r9_Enum value)
{
    proximityIndicationUTRA_r9_internal_value = value;
    proximityIndicationUTRA_r9_present = true;
    return 0;
}

int ReportProximityConfig_r9::proximityIndicationUTRA_r9_SetValue(std::string value)
{
    if("enabled" == value)
    {
        proximityIndicationUTRA_r9_internal_value = k_proximityIndicationUTRA_r9_enabled;
        proximityIndicationUTRA_r9_present = true;
        return 0;
    }
    return 1;
}

std::string ReportProximityConfig_r9::proximityIndicationUTRA_r9_ValueToString(proximityIndicationUTRA_r9_Enum value) const
{
    if(k_proximityIndicationUTRA_r9_enabled == value)
        return "enabled";
    return "";
}

uint64_t ReportProximityConfig_r9::proximityIndicationUTRA_r9_NumberOfValues() const
{
    return 1;
}

std::string ReportProximityConfig_r9::proximityIndicationUTRA_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "proximityIndicationUTRA_r9 = " + proximityIndicationUTRA_r9_ValueToString(proximityIndicationUTRA_r9_internal_value) + "\n";
    return out;
}

std::string ReportProximityConfig_r9::proximityIndicationUTRA_r9_ToStringNoNewLines() const
{
    std::string out = "proximityIndicationUTRA_r9=" + proximityIndicationUTRA_r9_ValueToString(proximityIndicationUTRA_r9_internal_value) + ",";
    return out;
}

int ReportProximityConfig_r9::proximityIndicationUTRA_r9_Clear()
{
    proximityIndicationUTRA_r9_present = false;
    return 0;
}

bool ReportProximityConfig_r9::proximityIndicationUTRA_r9_IsPresent() const
{
    return proximityIndicationUTRA_r9_present;
}

