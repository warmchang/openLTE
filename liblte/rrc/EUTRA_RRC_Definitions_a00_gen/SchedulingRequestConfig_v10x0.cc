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

#include "SchedulingRequestConfig_v10x0.h"

#include <cmath>

int SchedulingRequestConfig_v10x0::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(twoAntennaPortActivated_r10_IsPresent());
    bits.push_back(sr_PUCCH_ResourceIndexP1_r10_IsPresent());

    // Fields
    if(twoAntennaPortActivated_r10_IsPresent())
    {
        if(0 != twoAntennaPortActivated_r10_Pack(bits))
        {
            printf("SchedulingRequestConfig_v10x0:: field pack failure\n");
            return -1;
        }
    }
    if(sr_PUCCH_ResourceIndexP1_r10_IsPresent())
    {
        if(0 != sr_PUCCH_ResourceIndexP1_r10_Pack(bits))
        {
            printf("SchedulingRequestConfig_v10x0:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int SchedulingRequestConfig_v10x0::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int SchedulingRequestConfig_v10x0::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("SchedulingRequestConfig_v10x0::Unpack() index out of bounds for optional indiator twoAntennaPortActivated_r10\n");
        return -1;
    }
    twoAntennaPortActivated_r10_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("SchedulingRequestConfig_v10x0::Unpack() index out of bounds for optional indiator sr_PUCCH_ResourceIndexP1_r10\n");
        return -1;
    }
    sr_PUCCH_ResourceIndexP1_r10_present = bits[idx++];

    // Fields
    if(twoAntennaPortActivated_r10_present)
    {
        if(0 != twoAntennaPortActivated_r10_Unpack(bits, idx))
        {
            printf("SchedulingRequestConfig_v10x0:: field unpack failure\n");
            return -1;
        }
    }
    if(sr_PUCCH_ResourceIndexP1_r10_present)
    {
        if(0 != sr_PUCCH_ResourceIndexP1_r10_Unpack(bits, idx))
        {
            printf("SchedulingRequestConfig_v10x0:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string SchedulingRequestConfig_v10x0::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "SchedulingRequestConfig_v10x0:\n";
    if(twoAntennaPortActivated_r10_IsPresent())
        out += twoAntennaPortActivated_r10_ToString(indent+1);
    if(sr_PUCCH_ResourceIndexP1_r10_IsPresent())
        out += sr_PUCCH_ResourceIndexP1_r10_ToString(indent+1);
    return out;
}

std::string SchedulingRequestConfig_v10x0::ToStringNoNewLines() const
{
    std::string out = "SchedulingRequestConfig_v10x0:";
    if(twoAntennaPortActivated_r10_IsPresent())
        out += twoAntennaPortActivated_r10_ToStringNoNewLines();
    if(sr_PUCCH_ResourceIndexP1_r10_IsPresent())
        out += sr_PUCCH_ResourceIndexP1_r10_ToStringNoNewLines();
    return out;
}

int SchedulingRequestConfig_v10x0::twoAntennaPortActivated_r10_Pack(std::vector<uint8_t> &bits)
{
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((twoAntennaPortActivated_r10_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int SchedulingRequestConfig_v10x0::twoAntennaPortActivated_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return twoAntennaPortActivated_r10_Unpack(bits, idx);
}

int SchedulingRequestConfig_v10x0::twoAntennaPortActivated_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("SchedulingRequestConfig_v10x0::twoAntennaPortActivated_r10_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 0)
    {
        printf("SchedulingRequestConfig_v10x0::twoAntennaPortActivated_r10_Unpack() max failure\n");
        return -1;
    }
    twoAntennaPortActivated_r10_internal_value = (twoAntennaPortActivated_r10_Enum)packed_val;
    twoAntennaPortActivated_r10_present = true;
    return 0;
}

SchedulingRequestConfig_v10x0::twoAntennaPortActivated_r10_Enum SchedulingRequestConfig_v10x0::twoAntennaPortActivated_r10_Value() const
{
    if(twoAntennaPortActivated_r10_present)
        return twoAntennaPortActivated_r10_internal_value;
    return (SchedulingRequestConfig_v10x0::twoAntennaPortActivated_r10_Enum)0;
}

int SchedulingRequestConfig_v10x0::twoAntennaPortActivated_r10_SetValue(twoAntennaPortActivated_r10_Enum value)
{
    twoAntennaPortActivated_r10_internal_value = value;
    twoAntennaPortActivated_r10_present = true;
    return 0;
}

int SchedulingRequestConfig_v10x0::twoAntennaPortActivated_r10_SetValue(std::string value)
{
    if("true" == value)
    {
        twoAntennaPortActivated_r10_internal_value = k_twoAntennaPortActivated_r10_true;
        twoAntennaPortActivated_r10_present = true;
        return 0;
    }
    return 1;
}

std::string SchedulingRequestConfig_v10x0::twoAntennaPortActivated_r10_ValueToString(twoAntennaPortActivated_r10_Enum value) const
{
    if(k_twoAntennaPortActivated_r10_true == value)
        return "true";
    return "";
}

uint64_t SchedulingRequestConfig_v10x0::twoAntennaPortActivated_r10_NumberOfValues() const
{
    return 1;
}

std::string SchedulingRequestConfig_v10x0::twoAntennaPortActivated_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "twoAntennaPortActivated_r10 = " + twoAntennaPortActivated_r10_ValueToString(twoAntennaPortActivated_r10_internal_value) + "\n";
    return out;
}

std::string SchedulingRequestConfig_v10x0::twoAntennaPortActivated_r10_ToStringNoNewLines() const
{
    std::string out = "twoAntennaPortActivated_r10=" + twoAntennaPortActivated_r10_ValueToString(twoAntennaPortActivated_r10_internal_value) + ",";
    return out;
}

int SchedulingRequestConfig_v10x0::twoAntennaPortActivated_r10_Clear()
{
    twoAntennaPortActivated_r10_present = false;
    return 0;
}

bool SchedulingRequestConfig_v10x0::twoAntennaPortActivated_r10_IsPresent() const
{
    return twoAntennaPortActivated_r10_present;
}

int SchedulingRequestConfig_v10x0::sr_PUCCH_ResourceIndexP1_r10_Pack(std::vector<uint8_t> &bits)
{
    int64_t val_to_pack = sr_PUCCH_ResourceIndexP1_r10_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (2047 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int SchedulingRequestConfig_v10x0::sr_PUCCH_ResourceIndexP1_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return sr_PUCCH_ResourceIndexP1_r10_Unpack(bits, idx);
}

int SchedulingRequestConfig_v10x0::sr_PUCCH_ResourceIndexP1_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (2047 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("SchedulingRequestConfig_v10x0::sr_PUCCH_ResourceIndexP1_r10_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    sr_PUCCH_ResourceIndexP1_r10_internal_value = packed_val + 0;
    sr_PUCCH_ResourceIndexP1_r10_present = true;
    return 0;
}

int64_t SchedulingRequestConfig_v10x0::sr_PUCCH_ResourceIndexP1_r10_Value() const
{
    if(sr_PUCCH_ResourceIndexP1_r10_present)
        return sr_PUCCH_ResourceIndexP1_r10_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int SchedulingRequestConfig_v10x0::sr_PUCCH_ResourceIndexP1_r10_SetValue(int64_t value)
{
    if(value < 0 || value > 2047)
    {
        printf("SchedulingRequestConfig_v10x0::sr_PUCCH_ResourceIndexP1_r10_SetValue() range failure\n");
        return -1;
    }
    sr_PUCCH_ResourceIndexP1_r10_internal_value = value;
    sr_PUCCH_ResourceIndexP1_r10_present = true;
    return 0;
}

std::string SchedulingRequestConfig_v10x0::sr_PUCCH_ResourceIndexP1_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "sr_PUCCH_ResourceIndexP1_r10 = " + std::to_string(sr_PUCCH_ResourceIndexP1_r10_internal_value) + "\n";
    return out;
}

std::string SchedulingRequestConfig_v10x0::sr_PUCCH_ResourceIndexP1_r10_ToStringNoNewLines() const
{
    std::string out = "sr_PUCCH_ResourceIndexP1_r10=" + std::to_string(sr_PUCCH_ResourceIndexP1_r10_internal_value) + ",";
    return out;
}

int SchedulingRequestConfig_v10x0::sr_PUCCH_ResourceIndexP1_r10_Clear()
{
    sr_PUCCH_ResourceIndexP1_r10_present = false;
    return 0;
}

bool SchedulingRequestConfig_v10x0::sr_PUCCH_ResourceIndexP1_r10_IsPresent() const
{
    return sr_PUCCH_ResourceIndexP1_r10_present;
}

