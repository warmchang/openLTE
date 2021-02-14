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

#include "SON_Parameters_r9.h"

#include <cmath>

int SON_Parameters_r9::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(rach_Report_r9_IsPresent());

    // Fields
    if(rach_Report_r9_IsPresent())
    {
        if(0 != rach_Report_r9_Pack(bits))
        {
            printf("SON_Parameters_r9:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int SON_Parameters_r9::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int SON_Parameters_r9::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("SON_Parameters_r9::Unpack() index out of bounds for optional indiator rach_Report_r9\n");
        return -1;
    }
    rach_Report_r9_present = bits[idx++];

    // Fields
    if(rach_Report_r9_present)
    {
        if(0 != rach_Report_r9_Unpack(bits, idx))
        {
            printf("SON_Parameters_r9:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string SON_Parameters_r9::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "SON_Parameters_r9:\n";
    if(rach_Report_r9_IsPresent())
        out += rach_Report_r9_ToString(indent+1);
    return out;
}

std::string SON_Parameters_r9::ToStringNoNewLines() const
{
    std::string out = "SON_Parameters_r9:";
    if(rach_Report_r9_IsPresent())
        out += rach_Report_r9_ToStringNoNewLines();
    return out;
}

int SON_Parameters_r9::rach_Report_r9_Pack(std::vector<uint8_t> &bits)
{
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((rach_Report_r9_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int SON_Parameters_r9::rach_Report_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return rach_Report_r9_Unpack(bits, idx);
}

int SON_Parameters_r9::rach_Report_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("SON_Parameters_r9::rach_Report_r9_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 0)
    {
        printf("SON_Parameters_r9::rach_Report_r9_Unpack() max failure\n");
        return -1;
    }
    rach_Report_r9_internal_value = (rach_Report_r9_Enum)packed_val;
    rach_Report_r9_present = true;
    return 0;
}

SON_Parameters_r9::rach_Report_r9_Enum SON_Parameters_r9::rach_Report_r9_Value() const
{
    if(rach_Report_r9_present)
        return rach_Report_r9_internal_value;
    return (SON_Parameters_r9::rach_Report_r9_Enum)0;
}

int SON_Parameters_r9::rach_Report_r9_SetValue(rach_Report_r9_Enum value)
{
    rach_Report_r9_internal_value = value;
    rach_Report_r9_present = true;
    return 0;
}

int SON_Parameters_r9::rach_Report_r9_SetValue(std::string value)
{
    if("supported" == value)
    {
        rach_Report_r9_internal_value = k_rach_Report_r9_supported;
        rach_Report_r9_present = true;
        return 0;
    }
    return 1;
}

std::string SON_Parameters_r9::rach_Report_r9_ValueToString(rach_Report_r9_Enum value) const
{
    if(k_rach_Report_r9_supported == value)
        return "supported";
    return "";
}

uint64_t SON_Parameters_r9::rach_Report_r9_NumberOfValues() const
{
    return 1;
}

std::string SON_Parameters_r9::rach_Report_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "rach_Report_r9 = " + rach_Report_r9_ValueToString(rach_Report_r9_internal_value) + "\n";
    return out;
}

std::string SON_Parameters_r9::rach_Report_r9_ToStringNoNewLines() const
{
    std::string out = "rach_Report_r9=" + rach_Report_r9_ValueToString(rach_Report_r9_internal_value) + ",";
    return out;
}

int SON_Parameters_r9::rach_Report_r9_Clear()
{
    rach_Report_r9_present = false;
    return 0;
}

bool SON_Parameters_r9::rach_Report_r9_IsPresent() const
{
    return rach_Report_r9_present;
}

