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

#include "UplinkPowerControlCommon.h"

#include <cmath>

int UplinkPowerControlCommon::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != p0_NominalPUSCH_Pack(bits))
        {
            printf("UplinkPowerControlCommon:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != alpha_Pack(bits))
        {
            printf("UplinkPowerControlCommon:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != p0_NominalPUCCH_Pack(bits))
        {
            printf("UplinkPowerControlCommon:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != deltaFList_PUCCH.Pack(bits))
        {
            printf("UplinkPowerControlCommon:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != deltaPreambleMsg3_Pack(bits))
        {
            printf("UplinkPowerControlCommon:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int UplinkPowerControlCommon::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int UplinkPowerControlCommon::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != p0_NominalPUSCH_Unpack(bits, idx))
        {
            printf("UplinkPowerControlCommon:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != alpha_Unpack(bits, idx))
        {
            printf("UplinkPowerControlCommon:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != p0_NominalPUCCH_Unpack(bits, idx))
        {
            printf("UplinkPowerControlCommon:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != deltaFList_PUCCH.Unpack(bits, idx))
        {
            printf("UplinkPowerControlCommon:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != deltaPreambleMsg3_Unpack(bits, idx))
        {
            printf("UplinkPowerControlCommon:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string UplinkPowerControlCommon::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "UplinkPowerControlCommon:\n";
    out += p0_NominalPUSCH_ToString(indent+1);
    out += alpha_ToString(indent+1);
    out += p0_NominalPUCCH_ToString(indent+1);
    out += deltaFList_PUCCH_ToString(indent+1);
    out += deltaPreambleMsg3_ToString(indent+1);
    return out;
}

std::string UplinkPowerControlCommon::ToStringNoNewLines() const
{
    std::string out = "UplinkPowerControlCommon:";
    out += p0_NominalPUSCH_ToStringNoNewLines();
    out += alpha_ToStringNoNewLines();
    out += p0_NominalPUCCH_ToStringNoNewLines();
    out += deltaFList_PUCCH_ToStringNoNewLines();
    out += deltaPreambleMsg3_ToStringNoNewLines();
    return out;
}

int UplinkPowerControlCommon::p0_NominalPUSCH_Pack(std::vector<uint8_t> &bits)
{
    if(!p0_NominalPUSCH_present)
    {
        printf("UplinkPowerControlCommon::p0_NominalPUSCH_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = p0_NominalPUSCH_internal_value - (-126);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (24 - -126))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int UplinkPowerControlCommon::p0_NominalPUSCH_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return p0_NominalPUSCH_Unpack(bits, idx);
}

int UplinkPowerControlCommon::p0_NominalPUSCH_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (24 - -126))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("UplinkPowerControlCommon::p0_NominalPUSCH_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    p0_NominalPUSCH_internal_value = packed_val + -126;
    p0_NominalPUSCH_present = true;
    return 0;
}

int64_t UplinkPowerControlCommon::p0_NominalPUSCH_Value() const
{
    if(p0_NominalPUSCH_present)
        return p0_NominalPUSCH_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int UplinkPowerControlCommon::p0_NominalPUSCH_SetValue(int64_t value)
{
    if(value < -126 || value > 24)
    {
        printf("UplinkPowerControlCommon::p0_NominalPUSCH_SetValue() range failure\n");
        return -1;
    }
    p0_NominalPUSCH_internal_value = value;
    p0_NominalPUSCH_present = true;
    return 0;
}

std::string UplinkPowerControlCommon::p0_NominalPUSCH_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "p0_NominalPUSCH = " + std::to_string(p0_NominalPUSCH_internal_value) + "\n";
    return out;
}

std::string UplinkPowerControlCommon::p0_NominalPUSCH_ToStringNoNewLines() const
{
    std::string out = "p0_NominalPUSCH=" + std::to_string(p0_NominalPUSCH_internal_value) + ",";
    return out;
}

int UplinkPowerControlCommon::p0_NominalPUSCH_Clear()
{
    p0_NominalPUSCH_present = false;
    return 0;
}

bool UplinkPowerControlCommon::p0_NominalPUSCH_IsPresent() const
{
    return p0_NominalPUSCH_present;
}

int UplinkPowerControlCommon::alpha_Pack(std::vector<uint8_t> &bits)
{
    if(!alpha_present)
    {
        printf("UplinkPowerControlCommon::alpha_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 3;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((alpha_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int UplinkPowerControlCommon::alpha_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return alpha_Unpack(bits, idx);
}

int UplinkPowerControlCommon::alpha_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 3;
    if((idx + N_bits) > bits.size())
    {
        printf("UplinkPowerControlCommon::alpha_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 7)
    {
        printf("UplinkPowerControlCommon::alpha_Unpack() max failure\n");
        return -1;
    }
    alpha_internal_value = (alpha_Enum)packed_val;
    alpha_present = true;
    return 0;
}

UplinkPowerControlCommon::alpha_Enum UplinkPowerControlCommon::alpha_Value() const
{
    if(alpha_present)
        return alpha_internal_value;
    return (UplinkPowerControlCommon::alpha_Enum)0;
}

int UplinkPowerControlCommon::alpha_SetValue(alpha_Enum value)
{
    alpha_internal_value = value;
    alpha_present = true;
    return 0;
}

int UplinkPowerControlCommon::alpha_SetValue(std::string value)
{
    if("al0" == value)
    {
        alpha_internal_value = k_alpha_al0;
        alpha_present = true;
        return 0;
    }
    if("al04" == value)
    {
        alpha_internal_value = k_alpha_al04;
        alpha_present = true;
        return 0;
    }
    if("al05" == value)
    {
        alpha_internal_value = k_alpha_al05;
        alpha_present = true;
        return 0;
    }
    if("al06" == value)
    {
        alpha_internal_value = k_alpha_al06;
        alpha_present = true;
        return 0;
    }
    if("al07" == value)
    {
        alpha_internal_value = k_alpha_al07;
        alpha_present = true;
        return 0;
    }
    if("al08" == value)
    {
        alpha_internal_value = k_alpha_al08;
        alpha_present = true;
        return 0;
    }
    if("al09" == value)
    {
        alpha_internal_value = k_alpha_al09;
        alpha_present = true;
        return 0;
    }
    if("al1" == value)
    {
        alpha_internal_value = k_alpha_al1;
        alpha_present = true;
        return 0;
    }
    return 1;
}

std::string UplinkPowerControlCommon::alpha_ValueToString(alpha_Enum value) const
{
    if(k_alpha_al0 == value)
        return "al0";
    if(k_alpha_al04 == value)
        return "al04";
    if(k_alpha_al05 == value)
        return "al05";
    if(k_alpha_al06 == value)
        return "al06";
    if(k_alpha_al07 == value)
        return "al07";
    if(k_alpha_al08 == value)
        return "al08";
    if(k_alpha_al09 == value)
        return "al09";
    if(k_alpha_al1 == value)
        return "al1";
    return "";
}

uint64_t UplinkPowerControlCommon::alpha_NumberOfValues() const
{
    return 8;
}

std::string UplinkPowerControlCommon::alpha_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "alpha = " + alpha_ValueToString(alpha_internal_value) + "\n";
    return out;
}

std::string UplinkPowerControlCommon::alpha_ToStringNoNewLines() const
{
    std::string out = "alpha=" + alpha_ValueToString(alpha_internal_value) + ",";
    return out;
}

int UplinkPowerControlCommon::alpha_Clear()
{
    alpha_present = false;
    return 0;
}

bool UplinkPowerControlCommon::alpha_IsPresent() const
{
    return alpha_present;
}

int UplinkPowerControlCommon::p0_NominalPUCCH_Pack(std::vector<uint8_t> &bits)
{
    if(!p0_NominalPUCCH_present)
    {
        printf("UplinkPowerControlCommon::p0_NominalPUCCH_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = p0_NominalPUCCH_internal_value - (-127);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (-96 - -127))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int UplinkPowerControlCommon::p0_NominalPUCCH_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return p0_NominalPUCCH_Unpack(bits, idx);
}

int UplinkPowerControlCommon::p0_NominalPUCCH_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (-96 - -127))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("UplinkPowerControlCommon::p0_NominalPUCCH_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    p0_NominalPUCCH_internal_value = packed_val + -127;
    p0_NominalPUCCH_present = true;
    return 0;
}

int64_t UplinkPowerControlCommon::p0_NominalPUCCH_Value() const
{
    if(p0_NominalPUCCH_present)
        return p0_NominalPUCCH_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int UplinkPowerControlCommon::p0_NominalPUCCH_SetValue(int64_t value)
{
    if(value < -127 || value > -96)
    {
        printf("UplinkPowerControlCommon::p0_NominalPUCCH_SetValue() range failure\n");
        return -1;
    }
    p0_NominalPUCCH_internal_value = value;
    p0_NominalPUCCH_present = true;
    return 0;
}

std::string UplinkPowerControlCommon::p0_NominalPUCCH_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "p0_NominalPUCCH = " + std::to_string(p0_NominalPUCCH_internal_value) + "\n";
    return out;
}

std::string UplinkPowerControlCommon::p0_NominalPUCCH_ToStringNoNewLines() const
{
    std::string out = "p0_NominalPUCCH=" + std::to_string(p0_NominalPUCCH_internal_value) + ",";
    return out;
}

int UplinkPowerControlCommon::p0_NominalPUCCH_Clear()
{
    p0_NominalPUCCH_present = false;
    return 0;
}

bool UplinkPowerControlCommon::p0_NominalPUCCH_IsPresent() const
{
    return p0_NominalPUCCH_present;
}

DeltaFList_PUCCH* UplinkPowerControlCommon::deltaFList_PUCCH_Set()
{
    deltaFList_PUCCH_present = true;
    return &deltaFList_PUCCH;
}

int UplinkPowerControlCommon::deltaFList_PUCCH_Set(DeltaFList_PUCCH &value)
{
    deltaFList_PUCCH_present = true;
    deltaFList_PUCCH = value;
    return 0;
}

const DeltaFList_PUCCH& UplinkPowerControlCommon::deltaFList_PUCCH_Get() const
{
    return deltaFList_PUCCH;
}

std::string UplinkPowerControlCommon::deltaFList_PUCCH_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "deltaFList_PUCCH:\n";
    out += deltaFList_PUCCH.ToString(indent+1);
    return out;
}

std::string UplinkPowerControlCommon::deltaFList_PUCCH_ToStringNoNewLines() const
{
    std::string out = "deltaFList_PUCCH:";
    out += deltaFList_PUCCH.ToStringNoNewLines();
    return out;
}

int UplinkPowerControlCommon::deltaFList_PUCCH_Clear()
{
    deltaFList_PUCCH_present = false;
    return 0;
}

bool UplinkPowerControlCommon::deltaFList_PUCCH_IsPresent() const
{
    return deltaFList_PUCCH_present;
}

int UplinkPowerControlCommon::deltaPreambleMsg3_Pack(std::vector<uint8_t> &bits)
{
    if(!deltaPreambleMsg3_present)
    {
        printf("UplinkPowerControlCommon::deltaPreambleMsg3_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = deltaPreambleMsg3_internal_value - (-1);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (6 - -1))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int UplinkPowerControlCommon::deltaPreambleMsg3_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return deltaPreambleMsg3_Unpack(bits, idx);
}

int UplinkPowerControlCommon::deltaPreambleMsg3_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (6 - -1))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("UplinkPowerControlCommon::deltaPreambleMsg3_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    deltaPreambleMsg3_internal_value = packed_val + -1;
    deltaPreambleMsg3_present = true;
    return 0;
}

int64_t UplinkPowerControlCommon::deltaPreambleMsg3_Value() const
{
    if(deltaPreambleMsg3_present)
        return deltaPreambleMsg3_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int UplinkPowerControlCommon::deltaPreambleMsg3_SetValue(int64_t value)
{
    if(value < -1 || value > 6)
    {
        printf("UplinkPowerControlCommon::deltaPreambleMsg3_SetValue() range failure\n");
        return -1;
    }
    deltaPreambleMsg3_internal_value = value;
    deltaPreambleMsg3_present = true;
    return 0;
}

std::string UplinkPowerControlCommon::deltaPreambleMsg3_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "deltaPreambleMsg3 = " + std::to_string(deltaPreambleMsg3_internal_value) + "\n";
    return out;
}

std::string UplinkPowerControlCommon::deltaPreambleMsg3_ToStringNoNewLines() const
{
    std::string out = "deltaPreambleMsg3=" + std::to_string(deltaPreambleMsg3_internal_value) + ",";
    return out;
}

int UplinkPowerControlCommon::deltaPreambleMsg3_Clear()
{
    deltaPreambleMsg3_present = false;
    return 0;
}

bool UplinkPowerControlCommon::deltaPreambleMsg3_IsPresent() const
{
    return deltaPreambleMsg3_present;
}

