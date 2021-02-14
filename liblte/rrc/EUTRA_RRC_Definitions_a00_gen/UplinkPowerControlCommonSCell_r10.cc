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

#include "UplinkPowerControlCommonSCell_r10.h"

#include <cmath>

int UplinkPowerControlCommonSCell_r10::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != p0_NominalPUSCH_r10_Pack(bits))
        {
            printf("UplinkPowerControlCommonSCell_r10:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != alpha_r10_Pack(bits))
        {
            printf("UplinkPowerControlCommonSCell_r10:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int UplinkPowerControlCommonSCell_r10::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int UplinkPowerControlCommonSCell_r10::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != p0_NominalPUSCH_r10_Unpack(bits, idx))
        {
            printf("UplinkPowerControlCommonSCell_r10:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != alpha_r10_Unpack(bits, idx))
        {
            printf("UplinkPowerControlCommonSCell_r10:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string UplinkPowerControlCommonSCell_r10::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "UplinkPowerControlCommonSCell_r10:\n";
    out += p0_NominalPUSCH_r10_ToString(indent+1);
    out += alpha_r10_ToString(indent+1);
    return out;
}

std::string UplinkPowerControlCommonSCell_r10::ToStringNoNewLines() const
{
    std::string out = "UplinkPowerControlCommonSCell_r10:";
    out += p0_NominalPUSCH_r10_ToStringNoNewLines();
    out += alpha_r10_ToStringNoNewLines();
    return out;
}

int UplinkPowerControlCommonSCell_r10::p0_NominalPUSCH_r10_Pack(std::vector<uint8_t> &bits)
{
    if(!p0_NominalPUSCH_r10_present)
    {
        printf("UplinkPowerControlCommonSCell_r10::p0_NominalPUSCH_r10_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = p0_NominalPUSCH_r10_internal_value - (-126);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (24 - -126))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int UplinkPowerControlCommonSCell_r10::p0_NominalPUSCH_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return p0_NominalPUSCH_r10_Unpack(bits, idx);
}

int UplinkPowerControlCommonSCell_r10::p0_NominalPUSCH_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (24 - -126))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("UplinkPowerControlCommonSCell_r10::p0_NominalPUSCH_r10_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    p0_NominalPUSCH_r10_internal_value = packed_val + -126;
    p0_NominalPUSCH_r10_present = true;
    return 0;
}

int64_t UplinkPowerControlCommonSCell_r10::p0_NominalPUSCH_r10_Value() const
{
    if(p0_NominalPUSCH_r10_present)
        return p0_NominalPUSCH_r10_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int UplinkPowerControlCommonSCell_r10::p0_NominalPUSCH_r10_SetValue(int64_t value)
{
    if(value < -126 || value > 24)
    {
        printf("UplinkPowerControlCommonSCell_r10::p0_NominalPUSCH_r10_SetValue() range failure\n");
        return -1;
    }
    p0_NominalPUSCH_r10_internal_value = value;
    p0_NominalPUSCH_r10_present = true;
    return 0;
}

std::string UplinkPowerControlCommonSCell_r10::p0_NominalPUSCH_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "p0_NominalPUSCH_r10 = " + std::to_string(p0_NominalPUSCH_r10_internal_value) + "\n";
    return out;
}

std::string UplinkPowerControlCommonSCell_r10::p0_NominalPUSCH_r10_ToStringNoNewLines() const
{
    std::string out = "p0_NominalPUSCH_r10=" + std::to_string(p0_NominalPUSCH_r10_internal_value) + ",";
    return out;
}

int UplinkPowerControlCommonSCell_r10::p0_NominalPUSCH_r10_Clear()
{
    p0_NominalPUSCH_r10_present = false;
    return 0;
}

bool UplinkPowerControlCommonSCell_r10::p0_NominalPUSCH_r10_IsPresent() const
{
    return p0_NominalPUSCH_r10_present;
}

int UplinkPowerControlCommonSCell_r10::alpha_r10_Pack(std::vector<uint8_t> &bits)
{
    if(!alpha_r10_present)
    {
        printf("UplinkPowerControlCommonSCell_r10::alpha_r10_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 3;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((alpha_r10_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int UplinkPowerControlCommonSCell_r10::alpha_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return alpha_r10_Unpack(bits, idx);
}

int UplinkPowerControlCommonSCell_r10::alpha_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 3;
    if((idx + N_bits) > bits.size())
    {
        printf("UplinkPowerControlCommonSCell_r10::alpha_r10_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 7)
    {
        printf("UplinkPowerControlCommonSCell_r10::alpha_r10_Unpack() max failure\n");
        return -1;
    }
    alpha_r10_internal_value = (alpha_r10_Enum)packed_val;
    alpha_r10_present = true;
    return 0;
}

UplinkPowerControlCommonSCell_r10::alpha_r10_Enum UplinkPowerControlCommonSCell_r10::alpha_r10_Value() const
{
    if(alpha_r10_present)
        return alpha_r10_internal_value;
    return (UplinkPowerControlCommonSCell_r10::alpha_r10_Enum)0;
}

int UplinkPowerControlCommonSCell_r10::alpha_r10_SetValue(alpha_r10_Enum value)
{
    alpha_r10_internal_value = value;
    alpha_r10_present = true;
    return 0;
}

int UplinkPowerControlCommonSCell_r10::alpha_r10_SetValue(std::string value)
{
    if("al0" == value)
    {
        alpha_r10_internal_value = k_alpha_r10_al0;
        alpha_r10_present = true;
        return 0;
    }
    if("al04" == value)
    {
        alpha_r10_internal_value = k_alpha_r10_al04;
        alpha_r10_present = true;
        return 0;
    }
    if("al05" == value)
    {
        alpha_r10_internal_value = k_alpha_r10_al05;
        alpha_r10_present = true;
        return 0;
    }
    if("al06" == value)
    {
        alpha_r10_internal_value = k_alpha_r10_al06;
        alpha_r10_present = true;
        return 0;
    }
    if("al07" == value)
    {
        alpha_r10_internal_value = k_alpha_r10_al07;
        alpha_r10_present = true;
        return 0;
    }
    if("al08" == value)
    {
        alpha_r10_internal_value = k_alpha_r10_al08;
        alpha_r10_present = true;
        return 0;
    }
    if("al09" == value)
    {
        alpha_r10_internal_value = k_alpha_r10_al09;
        alpha_r10_present = true;
        return 0;
    }
    if("al1" == value)
    {
        alpha_r10_internal_value = k_alpha_r10_al1;
        alpha_r10_present = true;
        return 0;
    }
    return 1;
}

std::string UplinkPowerControlCommonSCell_r10::alpha_r10_ValueToString(alpha_r10_Enum value) const
{
    if(k_alpha_r10_al0 == value)
        return "al0";
    if(k_alpha_r10_al04 == value)
        return "al04";
    if(k_alpha_r10_al05 == value)
        return "al05";
    if(k_alpha_r10_al06 == value)
        return "al06";
    if(k_alpha_r10_al07 == value)
        return "al07";
    if(k_alpha_r10_al08 == value)
        return "al08";
    if(k_alpha_r10_al09 == value)
        return "al09";
    if(k_alpha_r10_al1 == value)
        return "al1";
    return "";
}

uint64_t UplinkPowerControlCommonSCell_r10::alpha_r10_NumberOfValues() const
{
    return 8;
}

std::string UplinkPowerControlCommonSCell_r10::alpha_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "alpha_r10 = " + alpha_r10_ValueToString(alpha_r10_internal_value) + "\n";
    return out;
}

std::string UplinkPowerControlCommonSCell_r10::alpha_r10_ToStringNoNewLines() const
{
    std::string out = "alpha_r10=" + alpha_r10_ValueToString(alpha_r10_internal_value) + ",";
    return out;
}

int UplinkPowerControlCommonSCell_r10::alpha_r10_Clear()
{
    alpha_r10_present = false;
    return 0;
}

bool UplinkPowerControlCommonSCell_r10::alpha_r10_IsPresent() const
{
    return alpha_r10_present;
}

