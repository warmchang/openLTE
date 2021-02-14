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

#include "SchedulingInfo.h"

#include <cmath>

int SchedulingInfo::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != si_Periodicity_Pack(bits))
        {
            printf("SchedulingInfo:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != sib_MappingInfo.Pack(bits))
        {
            printf("SchedulingInfo:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int SchedulingInfo::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int SchedulingInfo::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != si_Periodicity_Unpack(bits, idx))
        {
            printf("SchedulingInfo:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != sib_MappingInfo.Unpack(bits, idx))
        {
            printf("SchedulingInfo:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string SchedulingInfo::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "SchedulingInfo:\n";
    out += si_Periodicity_ToString(indent+1);
    out += sib_MappingInfo_ToString(indent+1);
    return out;
}

std::string SchedulingInfo::ToStringNoNewLines() const
{
    std::string out = "SchedulingInfo:";
    out += si_Periodicity_ToStringNoNewLines();
    out += sib_MappingInfo_ToStringNoNewLines();
    return out;
}

int SchedulingInfo::si_Periodicity_Pack(std::vector<uint8_t> &bits)
{
    if(!si_Periodicity_present)
    {
        printf("SchedulingInfo::si_Periodicity_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 3;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((si_Periodicity_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int SchedulingInfo::si_Periodicity_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return si_Periodicity_Unpack(bits, idx);
}

int SchedulingInfo::si_Periodicity_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 3;
    if((idx + N_bits) > bits.size())
    {
        printf("SchedulingInfo::si_Periodicity_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 6)
    {
        printf("SchedulingInfo::si_Periodicity_Unpack() max failure\n");
        return -1;
    }
    si_Periodicity_internal_value = (si_Periodicity_Enum)packed_val;
    si_Periodicity_present = true;
    return 0;
}

SchedulingInfo::si_Periodicity_Enum SchedulingInfo::si_Periodicity_Value() const
{
    if(si_Periodicity_present)
        return si_Periodicity_internal_value;
    return (SchedulingInfo::si_Periodicity_Enum)0;
}

int SchedulingInfo::si_Periodicity_SetValue(si_Periodicity_Enum value)
{
    si_Periodicity_internal_value = value;
    si_Periodicity_present = true;
    return 0;
}

int SchedulingInfo::si_Periodicity_SetValue(std::string value)
{
    if("rf8" == value)
    {
        si_Periodicity_internal_value = k_si_Periodicity_rf8;
        si_Periodicity_present = true;
        return 0;
    }
    if("rf16" == value)
    {
        si_Periodicity_internal_value = k_si_Periodicity_rf16;
        si_Periodicity_present = true;
        return 0;
    }
    if("rf32" == value)
    {
        si_Periodicity_internal_value = k_si_Periodicity_rf32;
        si_Periodicity_present = true;
        return 0;
    }
    if("rf64" == value)
    {
        si_Periodicity_internal_value = k_si_Periodicity_rf64;
        si_Periodicity_present = true;
        return 0;
    }
    if("rf128" == value)
    {
        si_Periodicity_internal_value = k_si_Periodicity_rf128;
        si_Periodicity_present = true;
        return 0;
    }
    if("rf256" == value)
    {
        si_Periodicity_internal_value = k_si_Periodicity_rf256;
        si_Periodicity_present = true;
        return 0;
    }
    if("rf512" == value)
    {
        si_Periodicity_internal_value = k_si_Periodicity_rf512;
        si_Periodicity_present = true;
        return 0;
    }
    return 1;
}

std::string SchedulingInfo::si_Periodicity_ValueToString(si_Periodicity_Enum value) const
{
    if(k_si_Periodicity_rf8 == value)
        return "rf8";
    if(k_si_Periodicity_rf16 == value)
        return "rf16";
    if(k_si_Periodicity_rf32 == value)
        return "rf32";
    if(k_si_Periodicity_rf64 == value)
        return "rf64";
    if(k_si_Periodicity_rf128 == value)
        return "rf128";
    if(k_si_Periodicity_rf256 == value)
        return "rf256";
    if(k_si_Periodicity_rf512 == value)
        return "rf512";
    return "";
}

uint64_t SchedulingInfo::si_Periodicity_NumberOfValues() const
{
    return 7;
}

std::string SchedulingInfo::si_Periodicity_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "si_Periodicity = " + si_Periodicity_ValueToString(si_Periodicity_internal_value) + "\n";
    return out;
}

std::string SchedulingInfo::si_Periodicity_ToStringNoNewLines() const
{
    std::string out = "si_Periodicity=" + si_Periodicity_ValueToString(si_Periodicity_internal_value) + ",";
    return out;
}

int SchedulingInfo::si_Periodicity_Clear()
{
    si_Periodicity_present = false;
    return 0;
}

bool SchedulingInfo::si_Periodicity_IsPresent() const
{
    return si_Periodicity_present;
}

SIB_MappingInfo* SchedulingInfo::sib_MappingInfo_Set()
{
    sib_MappingInfo_present = true;
    return &sib_MappingInfo;
}

int SchedulingInfo::sib_MappingInfo_Set(SIB_MappingInfo &value)
{
    sib_MappingInfo_present = true;
    sib_MappingInfo = value;
    return 0;
}

const SIB_MappingInfo& SchedulingInfo::sib_MappingInfo_Get() const
{
    return sib_MappingInfo;
}

std::string SchedulingInfo::sib_MappingInfo_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "sib_MappingInfo:\n";
    out += sib_MappingInfo.ToString(indent+1);
    return out;
}

std::string SchedulingInfo::sib_MappingInfo_ToStringNoNewLines() const
{
    std::string out = "sib_MappingInfo:";
    out += sib_MappingInfo.ToStringNoNewLines();
    return out;
}

int SchedulingInfo::sib_MappingInfo_Clear()
{
    sib_MappingInfo_present = false;
    return 0;
}

bool SchedulingInfo::sib_MappingInfo_IsPresent() const
{
    return sib_MappingInfo_present;
}

