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

#include "AC_BarringConfig.h"

#include <cmath>

int AC_BarringConfig::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != ac_BarringFactor_Pack(bits))
        {
            printf("AC_BarringConfig:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != ac_BarringTime_Pack(bits))
        {
            printf("AC_BarringConfig:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != ac_BarringForSpecialAC_Pack(bits))
        {
            printf("AC_BarringConfig:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int AC_BarringConfig::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int AC_BarringConfig::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != ac_BarringFactor_Unpack(bits, idx))
        {
            printf("AC_BarringConfig:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != ac_BarringTime_Unpack(bits, idx))
        {
            printf("AC_BarringConfig:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != ac_BarringForSpecialAC_Unpack(bits, idx))
        {
            printf("AC_BarringConfig:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string AC_BarringConfig::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "AC_BarringConfig:\n";
    out += ac_BarringFactor_ToString(indent+1);
    out += ac_BarringTime_ToString(indent+1);
    out += ac_BarringForSpecialAC_ToString(indent+1);
    return out;
}

std::string AC_BarringConfig::ToStringNoNewLines() const
{
    std::string out = "AC_BarringConfig:";
    out += ac_BarringFactor_ToStringNoNewLines();
    out += ac_BarringTime_ToStringNoNewLines();
    out += ac_BarringForSpecialAC_ToStringNoNewLines();
    return out;
}

int AC_BarringConfig::ac_BarringFactor_Pack(std::vector<uint8_t> &bits)
{
    if(!ac_BarringFactor_present)
    {
        printf("AC_BarringConfig::ac_BarringFactor_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 4;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((ac_BarringFactor_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int AC_BarringConfig::ac_BarringFactor_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return ac_BarringFactor_Unpack(bits, idx);
}

int AC_BarringConfig::ac_BarringFactor_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 4;
    if((idx + N_bits) > bits.size())
    {
        printf("AC_BarringConfig::ac_BarringFactor_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 15)
    {
        printf("AC_BarringConfig::ac_BarringFactor_Unpack() max failure\n");
        return -1;
    }
    ac_BarringFactor_internal_value = (ac_BarringFactor_Enum)packed_val;
    ac_BarringFactor_present = true;
    return 0;
}

AC_BarringConfig::ac_BarringFactor_Enum AC_BarringConfig::ac_BarringFactor_Value() const
{
    if(ac_BarringFactor_present)
        return ac_BarringFactor_internal_value;
    return (AC_BarringConfig::ac_BarringFactor_Enum)0;
}

int AC_BarringConfig::ac_BarringFactor_SetValue(ac_BarringFactor_Enum value)
{
    ac_BarringFactor_internal_value = value;
    ac_BarringFactor_present = true;
    return 0;
}

int AC_BarringConfig::ac_BarringFactor_SetValue(std::string value)
{
    if("p00" == value)
    {
        ac_BarringFactor_internal_value = k_ac_BarringFactor_p00;
        ac_BarringFactor_present = true;
        return 0;
    }
    if("p05" == value)
    {
        ac_BarringFactor_internal_value = k_ac_BarringFactor_p05;
        ac_BarringFactor_present = true;
        return 0;
    }
    if("p10" == value)
    {
        ac_BarringFactor_internal_value = k_ac_BarringFactor_p10;
        ac_BarringFactor_present = true;
        return 0;
    }
    if("p15" == value)
    {
        ac_BarringFactor_internal_value = k_ac_BarringFactor_p15;
        ac_BarringFactor_present = true;
        return 0;
    }
    if("p20" == value)
    {
        ac_BarringFactor_internal_value = k_ac_BarringFactor_p20;
        ac_BarringFactor_present = true;
        return 0;
    }
    if("p25" == value)
    {
        ac_BarringFactor_internal_value = k_ac_BarringFactor_p25;
        ac_BarringFactor_present = true;
        return 0;
    }
    if("p30" == value)
    {
        ac_BarringFactor_internal_value = k_ac_BarringFactor_p30;
        ac_BarringFactor_present = true;
        return 0;
    }
    if("p40" == value)
    {
        ac_BarringFactor_internal_value = k_ac_BarringFactor_p40;
        ac_BarringFactor_present = true;
        return 0;
    }
    if("p50" == value)
    {
        ac_BarringFactor_internal_value = k_ac_BarringFactor_p50;
        ac_BarringFactor_present = true;
        return 0;
    }
    if("p60" == value)
    {
        ac_BarringFactor_internal_value = k_ac_BarringFactor_p60;
        ac_BarringFactor_present = true;
        return 0;
    }
    if("p70" == value)
    {
        ac_BarringFactor_internal_value = k_ac_BarringFactor_p70;
        ac_BarringFactor_present = true;
        return 0;
    }
    if("p75" == value)
    {
        ac_BarringFactor_internal_value = k_ac_BarringFactor_p75;
        ac_BarringFactor_present = true;
        return 0;
    }
    if("p80" == value)
    {
        ac_BarringFactor_internal_value = k_ac_BarringFactor_p80;
        ac_BarringFactor_present = true;
        return 0;
    }
    if("p85" == value)
    {
        ac_BarringFactor_internal_value = k_ac_BarringFactor_p85;
        ac_BarringFactor_present = true;
        return 0;
    }
    if("p90" == value)
    {
        ac_BarringFactor_internal_value = k_ac_BarringFactor_p90;
        ac_BarringFactor_present = true;
        return 0;
    }
    if("p95" == value)
    {
        ac_BarringFactor_internal_value = k_ac_BarringFactor_p95;
        ac_BarringFactor_present = true;
        return 0;
    }
    return 1;
}

std::string AC_BarringConfig::ac_BarringFactor_ValueToString(ac_BarringFactor_Enum value) const
{
    if(k_ac_BarringFactor_p00 == value)
        return "p00";
    if(k_ac_BarringFactor_p05 == value)
        return "p05";
    if(k_ac_BarringFactor_p10 == value)
        return "p10";
    if(k_ac_BarringFactor_p15 == value)
        return "p15";
    if(k_ac_BarringFactor_p20 == value)
        return "p20";
    if(k_ac_BarringFactor_p25 == value)
        return "p25";
    if(k_ac_BarringFactor_p30 == value)
        return "p30";
    if(k_ac_BarringFactor_p40 == value)
        return "p40";
    if(k_ac_BarringFactor_p50 == value)
        return "p50";
    if(k_ac_BarringFactor_p60 == value)
        return "p60";
    if(k_ac_BarringFactor_p70 == value)
        return "p70";
    if(k_ac_BarringFactor_p75 == value)
        return "p75";
    if(k_ac_BarringFactor_p80 == value)
        return "p80";
    if(k_ac_BarringFactor_p85 == value)
        return "p85";
    if(k_ac_BarringFactor_p90 == value)
        return "p90";
    if(k_ac_BarringFactor_p95 == value)
        return "p95";
    return "";
}

uint64_t AC_BarringConfig::ac_BarringFactor_NumberOfValues() const
{
    return 16;
}

std::string AC_BarringConfig::ac_BarringFactor_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ac_BarringFactor = " + ac_BarringFactor_ValueToString(ac_BarringFactor_internal_value) + "\n";
    return out;
}

std::string AC_BarringConfig::ac_BarringFactor_ToStringNoNewLines() const
{
    std::string out = "ac_BarringFactor=" + ac_BarringFactor_ValueToString(ac_BarringFactor_internal_value) + ",";
    return out;
}

int AC_BarringConfig::ac_BarringFactor_Clear()
{
    ac_BarringFactor_present = false;
    return 0;
}

bool AC_BarringConfig::ac_BarringFactor_IsPresent() const
{
    return ac_BarringFactor_present;
}

int AC_BarringConfig::ac_BarringTime_Pack(std::vector<uint8_t> &bits)
{
    if(!ac_BarringTime_present)
    {
        printf("AC_BarringConfig::ac_BarringTime_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 3;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((ac_BarringTime_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int AC_BarringConfig::ac_BarringTime_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return ac_BarringTime_Unpack(bits, idx);
}

int AC_BarringConfig::ac_BarringTime_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 3;
    if((idx + N_bits) > bits.size())
    {
        printf("AC_BarringConfig::ac_BarringTime_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 7)
    {
        printf("AC_BarringConfig::ac_BarringTime_Unpack() max failure\n");
        return -1;
    }
    ac_BarringTime_internal_value = (ac_BarringTime_Enum)packed_val;
    ac_BarringTime_present = true;
    return 0;
}

AC_BarringConfig::ac_BarringTime_Enum AC_BarringConfig::ac_BarringTime_Value() const
{
    if(ac_BarringTime_present)
        return ac_BarringTime_internal_value;
    return (AC_BarringConfig::ac_BarringTime_Enum)0;
}

int AC_BarringConfig::ac_BarringTime_SetValue(ac_BarringTime_Enum value)
{
    ac_BarringTime_internal_value = value;
    ac_BarringTime_present = true;
    return 0;
}

int AC_BarringConfig::ac_BarringTime_SetValue(std::string value)
{
    if("s4" == value)
    {
        ac_BarringTime_internal_value = k_ac_BarringTime_s4;
        ac_BarringTime_present = true;
        return 0;
    }
    if("s8" == value)
    {
        ac_BarringTime_internal_value = k_ac_BarringTime_s8;
        ac_BarringTime_present = true;
        return 0;
    }
    if("s16" == value)
    {
        ac_BarringTime_internal_value = k_ac_BarringTime_s16;
        ac_BarringTime_present = true;
        return 0;
    }
    if("s32" == value)
    {
        ac_BarringTime_internal_value = k_ac_BarringTime_s32;
        ac_BarringTime_present = true;
        return 0;
    }
    if("s64" == value)
    {
        ac_BarringTime_internal_value = k_ac_BarringTime_s64;
        ac_BarringTime_present = true;
        return 0;
    }
    if("s128" == value)
    {
        ac_BarringTime_internal_value = k_ac_BarringTime_s128;
        ac_BarringTime_present = true;
        return 0;
    }
    if("s256" == value)
    {
        ac_BarringTime_internal_value = k_ac_BarringTime_s256;
        ac_BarringTime_present = true;
        return 0;
    }
    if("s512" == value)
    {
        ac_BarringTime_internal_value = k_ac_BarringTime_s512;
        ac_BarringTime_present = true;
        return 0;
    }
    return 1;
}

std::string AC_BarringConfig::ac_BarringTime_ValueToString(ac_BarringTime_Enum value) const
{
    if(k_ac_BarringTime_s4 == value)
        return "s4";
    if(k_ac_BarringTime_s8 == value)
        return "s8";
    if(k_ac_BarringTime_s16 == value)
        return "s16";
    if(k_ac_BarringTime_s32 == value)
        return "s32";
    if(k_ac_BarringTime_s64 == value)
        return "s64";
    if(k_ac_BarringTime_s128 == value)
        return "s128";
    if(k_ac_BarringTime_s256 == value)
        return "s256";
    if(k_ac_BarringTime_s512 == value)
        return "s512";
    return "";
}

uint64_t AC_BarringConfig::ac_BarringTime_NumberOfValues() const
{
    return 8;
}

std::string AC_BarringConfig::ac_BarringTime_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ac_BarringTime = " + ac_BarringTime_ValueToString(ac_BarringTime_internal_value) + "\n";
    return out;
}

std::string AC_BarringConfig::ac_BarringTime_ToStringNoNewLines() const
{
    std::string out = "ac_BarringTime=" + ac_BarringTime_ValueToString(ac_BarringTime_internal_value) + ",";
    return out;
}

int AC_BarringConfig::ac_BarringTime_Clear()
{
    ac_BarringTime_present = false;
    return 0;
}

bool AC_BarringConfig::ac_BarringTime_IsPresent() const
{
    return ac_BarringTime_present;
}

int AC_BarringConfig::ac_BarringForSpecialAC_Pack(std::vector<uint8_t> &bits)
{
    if(!ac_BarringForSpecialAC_present)
    {
        printf("AC_BarringConfig::ac_BarringForSpecialAC_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 5;
    if(size < 5 || size > 5)
    {
        printf("AC_BarringConfig::ac_BarringForSpecialAC_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((ac_BarringForSpecialAC_internal_value >> (5-i-1)) & 1);
    return 0;
}

int AC_BarringConfig::ac_BarringForSpecialAC_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return ac_BarringForSpecialAC_Unpack(bits, idx);
}

int AC_BarringConfig::ac_BarringForSpecialAC_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 5;
    if(size < 5 || size > 5)
    {
        printf("AC_BarringConfig::ac_BarringForSpecialAC_Unpack() size failure\n");
        return -1;
    }
    ac_BarringForSpecialAC_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("AC_BarringConfig::ac_BarringForSpecialAC_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        ac_BarringForSpecialAC_internal_value |= (uint8_t)bits[idx++] << (uint8_t)(5-i-1);
    ac_BarringForSpecialAC_present = true;
    return 0;
}

uint8_t AC_BarringConfig::ac_BarringForSpecialAC_Value() const
{
    if(ac_BarringForSpecialAC_present)
        return ac_BarringForSpecialAC_internal_value;
    uint8_t tmp = 0;
    return tmp;
}

int AC_BarringConfig::ac_BarringForSpecialAC_SetValue(uint8_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 5)
    {
        printf("AC_BarringConfig::ac_BarringForSpecialAC_SetValue() size failure\n");
        return -1;
    }
    ac_BarringForSpecialAC_internal_value = value;
    ac_BarringForSpecialAC_present = true;
    return 0;
}

std::string AC_BarringConfig::ac_BarringForSpecialAC_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ac_BarringForSpecialAC = ";
    out += std::to_string(ac_BarringForSpecialAC_internal_value);
    out += "\n";
    return out;
}

std::string AC_BarringConfig::ac_BarringForSpecialAC_ToStringNoNewLines() const
{
    std::string out = "ac_BarringForSpecialAC=";
    out += std::to_string(ac_BarringForSpecialAC_internal_value);
    out += ",";
    return out;
}

int AC_BarringConfig::ac_BarringForSpecialAC_Clear()
{
    ac_BarringForSpecialAC_present = false;
    return 0;
}

bool AC_BarringConfig::ac_BarringForSpecialAC_IsPresent() const
{
    return ac_BarringForSpecialAC_present;
}

