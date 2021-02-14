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

#include "PhysCellIdRange.h"

#include <cmath>

int PhysCellIdRange::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(range_IsPresent());

    // Fields
    {
        if(0 != start.Pack(bits))
        {
            printf("PhysCellIdRange:: field pack failure\n");
            return -1;
        }
    }
    if(range_IsPresent())
    {
        if(0 != range_Pack(bits))
        {
            printf("PhysCellIdRange:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int PhysCellIdRange::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int PhysCellIdRange::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("PhysCellIdRange::Unpack() index out of bounds for optional indiator range\n");
        return -1;
    }
    range_present = bits[idx++];

    // Fields
    {
        if(0 != start.Unpack(bits, idx))
        {
            printf("PhysCellIdRange:: field unpack failure\n");
            return -1;
        }
    }
    if(range_present)
    {
        if(0 != range_Unpack(bits, idx))
        {
            printf("PhysCellIdRange:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string PhysCellIdRange::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "PhysCellIdRange:\n";
    out += start_ToString(indent+1);
    if(range_IsPresent())
        out += range_ToString(indent+1);
    return out;
}

std::string PhysCellIdRange::ToStringNoNewLines() const
{
    std::string out = "PhysCellIdRange:";
    out += start_ToStringNoNewLines();
    if(range_IsPresent())
        out += range_ToStringNoNewLines();
    return out;
}

PhysCellId* PhysCellIdRange::start_Set()
{
    start_present = true;
    return &start;
}

int PhysCellIdRange::start_Set(PhysCellId &value)
{
    start_present = true;
    start = value;
    return 0;
}

const PhysCellId& PhysCellIdRange::start_Get() const
{
    return start;
}

std::string PhysCellIdRange::start_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "start:\n";
    out += start.ToString(indent+1);
    return out;
}

std::string PhysCellIdRange::start_ToStringNoNewLines() const
{
    std::string out = "start:";
    out += start.ToStringNoNewLines();
    return out;
}

int PhysCellIdRange::start_Clear()
{
    start_present = false;
    return 0;
}

bool PhysCellIdRange::start_IsPresent() const
{
    return start_present;
}

int PhysCellIdRange::range_Pack(std::vector<uint8_t> &bits)
{
    uint32_t N_bits = 4;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((range_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int PhysCellIdRange::range_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return range_Unpack(bits, idx);
}

int PhysCellIdRange::range_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 4;
    if((idx + N_bits) > bits.size())
    {
        printf("PhysCellIdRange::range_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 15)
    {
        printf("PhysCellIdRange::range_Unpack() max failure\n");
        return -1;
    }
    range_internal_value = (range_Enum)packed_val;
    range_present = true;
    return 0;
}

PhysCellIdRange::range_Enum PhysCellIdRange::range_Value() const
{
    if(range_present)
        return range_internal_value;
    return (PhysCellIdRange::range_Enum)0;
}

int PhysCellIdRange::range_SetValue(range_Enum value)
{
    range_internal_value = value;
    range_present = true;
    return 0;
}

int PhysCellIdRange::range_SetValue(std::string value)
{
    if("n4" == value)
    {
        range_internal_value = k_range_n4;
        range_present = true;
        return 0;
    }
    if("n8" == value)
    {
        range_internal_value = k_range_n8;
        range_present = true;
        return 0;
    }
    if("n12" == value)
    {
        range_internal_value = k_range_n12;
        range_present = true;
        return 0;
    }
    if("n16" == value)
    {
        range_internal_value = k_range_n16;
        range_present = true;
        return 0;
    }
    if("n24" == value)
    {
        range_internal_value = k_range_n24;
        range_present = true;
        return 0;
    }
    if("n32" == value)
    {
        range_internal_value = k_range_n32;
        range_present = true;
        return 0;
    }
    if("n48" == value)
    {
        range_internal_value = k_range_n48;
        range_present = true;
        return 0;
    }
    if("n64" == value)
    {
        range_internal_value = k_range_n64;
        range_present = true;
        return 0;
    }
    if("n84" == value)
    {
        range_internal_value = k_range_n84;
        range_present = true;
        return 0;
    }
    if("n96" == value)
    {
        range_internal_value = k_range_n96;
        range_present = true;
        return 0;
    }
    if("n128" == value)
    {
        range_internal_value = k_range_n128;
        range_present = true;
        return 0;
    }
    if("n168" == value)
    {
        range_internal_value = k_range_n168;
        range_present = true;
        return 0;
    }
    if("n252" == value)
    {
        range_internal_value = k_range_n252;
        range_present = true;
        return 0;
    }
    if("n504" == value)
    {
        range_internal_value = k_range_n504;
        range_present = true;
        return 0;
    }
    if("spare2" == value)
    {
        range_internal_value = k_range_spare2;
        range_present = true;
        return 0;
    }
    if("spare1" == value)
    {
        range_internal_value = k_range_spare1;
        range_present = true;
        return 0;
    }
    return 1;
}

std::string PhysCellIdRange::range_ValueToString(range_Enum value) const
{
    if(k_range_n4 == value)
        return "n4";
    if(k_range_n8 == value)
        return "n8";
    if(k_range_n12 == value)
        return "n12";
    if(k_range_n16 == value)
        return "n16";
    if(k_range_n24 == value)
        return "n24";
    if(k_range_n32 == value)
        return "n32";
    if(k_range_n48 == value)
        return "n48";
    if(k_range_n64 == value)
        return "n64";
    if(k_range_n84 == value)
        return "n84";
    if(k_range_n96 == value)
        return "n96";
    if(k_range_n128 == value)
        return "n128";
    if(k_range_n168 == value)
        return "n168";
    if(k_range_n252 == value)
        return "n252";
    if(k_range_n504 == value)
        return "n504";
    if(k_range_spare2 == value)
        return "spare2";
    if(k_range_spare1 == value)
        return "spare1";
    return "";
}

uint64_t PhysCellIdRange::range_NumberOfValues() const
{
    return 16;
}

std::string PhysCellIdRange::range_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "range = " + range_ValueToString(range_internal_value) + "\n";
    return out;
}

std::string PhysCellIdRange::range_ToStringNoNewLines() const
{
    std::string out = "range=" + range_ValueToString(range_internal_value) + ",";
    return out;
}

int PhysCellIdRange::range_Clear()
{
    range_present = false;
    return 0;
}

bool PhysCellIdRange::range_IsPresent() const
{
    return range_present;
}

