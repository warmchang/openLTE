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

#include "UplinkPowerControlCommon_v10x0.h"

#include <cmath>

int UplinkPowerControlCommon_v10x0::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != deltaF_PUCCH_Format3_r10_Pack(bits))
        {
            printf("UplinkPowerControlCommon_v10x0:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int UplinkPowerControlCommon_v10x0::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int UplinkPowerControlCommon_v10x0::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != deltaF_PUCCH_Format3_r10_Unpack(bits, idx))
        {
            printf("UplinkPowerControlCommon_v10x0:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string UplinkPowerControlCommon_v10x0::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "UplinkPowerControlCommon_v10x0:\n";
    out += deltaF_PUCCH_Format3_r10_ToString(indent+1);
    return out;
}

std::string UplinkPowerControlCommon_v10x0::ToStringNoNewLines() const
{
    std::string out = "UplinkPowerControlCommon_v10x0:";
    out += deltaF_PUCCH_Format3_r10_ToStringNoNewLines();
    return out;
}

int UplinkPowerControlCommon_v10x0::deltaF_PUCCH_Format3_r10_Pack(std::vector<uint8_t> &bits)
{
    if(!deltaF_PUCCH_Format3_r10_present)
    {
        printf("UplinkPowerControlCommon_v10x0::deltaF_PUCCH_Format3_r10_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((deltaF_PUCCH_Format3_r10_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int UplinkPowerControlCommon_v10x0::deltaF_PUCCH_Format3_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return deltaF_PUCCH_Format3_r10_Unpack(bits, idx);
}

int UplinkPowerControlCommon_v10x0::deltaF_PUCCH_Format3_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("UplinkPowerControlCommon_v10x0::deltaF_PUCCH_Format3_r10_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 0)
    {
        printf("UplinkPowerControlCommon_v10x0::deltaF_PUCCH_Format3_r10_Unpack() max failure\n");
        return -1;
    }
    deltaF_PUCCH_Format3_r10_internal_value = (deltaF_PUCCH_Format3_r10_Enum)packed_val;
    deltaF_PUCCH_Format3_r10_present = true;
    return 0;
}

UplinkPowerControlCommon_v10x0::deltaF_PUCCH_Format3_r10_Enum UplinkPowerControlCommon_v10x0::deltaF_PUCCH_Format3_r10_Value() const
{
    if(deltaF_PUCCH_Format3_r10_present)
        return deltaF_PUCCH_Format3_r10_internal_value;
    return (UplinkPowerControlCommon_v10x0::deltaF_PUCCH_Format3_r10_Enum)0;
}

int UplinkPowerControlCommon_v10x0::deltaF_PUCCH_Format3_r10_SetValue(deltaF_PUCCH_Format3_r10_Enum value)
{
    deltaF_PUCCH_Format3_r10_internal_value = value;
    deltaF_PUCCH_Format3_r10_present = true;
    return 0;
}

int UplinkPowerControlCommon_v10x0::deltaF_PUCCH_Format3_r10_SetValue(std::string value)
{
    if("ffs" == value)
    {
        deltaF_PUCCH_Format3_r10_internal_value = k_deltaF_PUCCH_Format3_r10_ffs;
        deltaF_PUCCH_Format3_r10_present = true;
        return 0;
    }
    return 1;
}

std::string UplinkPowerControlCommon_v10x0::deltaF_PUCCH_Format3_r10_ValueToString(deltaF_PUCCH_Format3_r10_Enum value) const
{
    if(k_deltaF_PUCCH_Format3_r10_ffs == value)
        return "ffs";
    return "";
}

uint64_t UplinkPowerControlCommon_v10x0::deltaF_PUCCH_Format3_r10_NumberOfValues() const
{
    return 1;
}

std::string UplinkPowerControlCommon_v10x0::deltaF_PUCCH_Format3_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "deltaF_PUCCH_Format3_r10 = " + deltaF_PUCCH_Format3_r10_ValueToString(deltaF_PUCCH_Format3_r10_internal_value) + "\n";
    return out;
}

std::string UplinkPowerControlCommon_v10x0::deltaF_PUCCH_Format3_r10_ToStringNoNewLines() const
{
    std::string out = "deltaF_PUCCH_Format3_r10=" + deltaF_PUCCH_Format3_r10_ValueToString(deltaF_PUCCH_Format3_r10_internal_value) + ",";
    return out;
}

int UplinkPowerControlCommon_v10x0::deltaF_PUCCH_Format3_r10_Clear()
{
    deltaF_PUCCH_Format3_r10_present = false;
    return 0;
}

bool UplinkPowerControlCommon_v10x0::deltaF_PUCCH_Format3_r10_IsPresent() const
{
    return deltaF_PUCCH_Format3_r10_present;
}

