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

#include "PhysCellIdRangeUTRA_FDD_r9.h"

#include <cmath>

int PhysCellIdRangeUTRA_FDD_r9::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(range_r9_IsPresent());

    // Fields
    {
        if(0 != start_r9.Pack(bits))
        {
            printf("PhysCellIdRangeUTRA_FDD_r9:: field pack failure\n");
            return -1;
        }
    }
    if(range_r9_IsPresent())
    {
        if(0 != range_r9_Pack(bits))
        {
            printf("PhysCellIdRangeUTRA_FDD_r9:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int PhysCellIdRangeUTRA_FDD_r9::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int PhysCellIdRangeUTRA_FDD_r9::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("PhysCellIdRangeUTRA_FDD_r9::Unpack() index out of bounds for optional indiator range_r9\n");
        return -1;
    }
    range_r9_present = bits[idx++];

    // Fields
    {
        if(0 != start_r9.Unpack(bits, idx))
        {
            printf("PhysCellIdRangeUTRA_FDD_r9:: field unpack failure\n");
            return -1;
        }
    }
    if(range_r9_present)
    {
        if(0 != range_r9_Unpack(bits, idx))
        {
            printf("PhysCellIdRangeUTRA_FDD_r9:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string PhysCellIdRangeUTRA_FDD_r9::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "PhysCellIdRangeUTRA_FDD_r9:\n";
    out += start_r9_ToString(indent+1);
    if(range_r9_IsPresent())
        out += range_r9_ToString(indent+1);
    return out;
}

std::string PhysCellIdRangeUTRA_FDD_r9::ToStringNoNewLines() const
{
    std::string out = "PhysCellIdRangeUTRA_FDD_r9:";
    out += start_r9_ToStringNoNewLines();
    if(range_r9_IsPresent())
        out += range_r9_ToStringNoNewLines();
    return out;
}

PhysCellIdUTRA_FDD* PhysCellIdRangeUTRA_FDD_r9::start_r9_Set()
{
    start_r9_present = true;
    return &start_r9;
}

int PhysCellIdRangeUTRA_FDD_r9::start_r9_Set(PhysCellIdUTRA_FDD &value)
{
    start_r9_present = true;
    start_r9 = value;
    return 0;
}

const PhysCellIdUTRA_FDD& PhysCellIdRangeUTRA_FDD_r9::start_r9_Get() const
{
    return start_r9;
}

std::string PhysCellIdRangeUTRA_FDD_r9::start_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "start_r9:\n";
    out += start_r9.ToString(indent+1);
    return out;
}

std::string PhysCellIdRangeUTRA_FDD_r9::start_r9_ToStringNoNewLines() const
{
    std::string out = "start_r9:";
    out += start_r9.ToStringNoNewLines();
    return out;
}

int PhysCellIdRangeUTRA_FDD_r9::start_r9_Clear()
{
    start_r9_present = false;
    return 0;
}

bool PhysCellIdRangeUTRA_FDD_r9::start_r9_IsPresent() const
{
    return start_r9_present;
}

int PhysCellIdRangeUTRA_FDD_r9::range_r9_Pack(std::vector<uint8_t> &bits)
{
    int64_t val_to_pack = range_r9_internal_value - (2);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (512 - 2))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int PhysCellIdRangeUTRA_FDD_r9::range_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return range_r9_Unpack(bits, idx);
}

int PhysCellIdRangeUTRA_FDD_r9::range_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (512 - 2))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("PhysCellIdRangeUTRA_FDD_r9::range_r9_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    range_r9_internal_value = packed_val + 2;
    range_r9_present = true;
    return 0;
}

int64_t PhysCellIdRangeUTRA_FDD_r9::range_r9_Value() const
{
    if(range_r9_present)
        return range_r9_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int PhysCellIdRangeUTRA_FDD_r9::range_r9_SetValue(int64_t value)
{
    if(value < 2 || value > 512)
    {
        printf("PhysCellIdRangeUTRA_FDD_r9::range_r9_SetValue() range failure\n");
        return -1;
    }
    range_r9_internal_value = value;
    range_r9_present = true;
    return 0;
}

std::string PhysCellIdRangeUTRA_FDD_r9::range_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "range_r9 = " + std::to_string(range_r9_internal_value) + "\n";
    return out;
}

std::string PhysCellIdRangeUTRA_FDD_r9::range_r9_ToStringNoNewLines() const
{
    std::string out = "range_r9=" + std::to_string(range_r9_internal_value) + ",";
    return out;
}

int PhysCellIdRangeUTRA_FDD_r9::range_r9_Clear()
{
    range_r9_present = false;
    return 0;
}

bool PhysCellIdRangeUTRA_FDD_r9::range_r9_IsPresent() const
{
    return range_r9_present;
}

