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

#include "PRACH_ConfigSCell_r10.h"

#include <cmath>

int PRACH_ConfigSCell_r10::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != prach_ConfigIndex_Pack(bits))
        {
            printf("PRACH_ConfigSCell_r10:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int PRACH_ConfigSCell_r10::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int PRACH_ConfigSCell_r10::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != prach_ConfigIndex_Unpack(bits, idx))
        {
            printf("PRACH_ConfigSCell_r10:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string PRACH_ConfigSCell_r10::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "PRACH_ConfigSCell_r10:\n";
    out += prach_ConfigIndex_ToString(indent+1);
    return out;
}

std::string PRACH_ConfigSCell_r10::ToStringNoNewLines() const
{
    std::string out = "PRACH_ConfigSCell_r10:";
    out += prach_ConfigIndex_ToStringNoNewLines();
    return out;
}

int PRACH_ConfigSCell_r10::prach_ConfigIndex_Pack(std::vector<uint8_t> &bits)
{
    if(!prach_ConfigIndex_present)
    {
        printf("PRACH_ConfigSCell_r10::prach_ConfigIndex_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = prach_ConfigIndex_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (63 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int PRACH_ConfigSCell_r10::prach_ConfigIndex_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return prach_ConfigIndex_Unpack(bits, idx);
}

int PRACH_ConfigSCell_r10::prach_ConfigIndex_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (63 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("PRACH_ConfigSCell_r10::prach_ConfigIndex_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    prach_ConfigIndex_internal_value = packed_val + 0;
    prach_ConfigIndex_present = true;
    return 0;
}

int64_t PRACH_ConfigSCell_r10::prach_ConfigIndex_Value() const
{
    if(prach_ConfigIndex_present)
        return prach_ConfigIndex_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int PRACH_ConfigSCell_r10::prach_ConfigIndex_SetValue(int64_t value)
{
    if(value < 0 || value > 63)
    {
        printf("PRACH_ConfigSCell_r10::prach_ConfigIndex_SetValue() range failure\n");
        return -1;
    }
    prach_ConfigIndex_internal_value = value;
    prach_ConfigIndex_present = true;
    return 0;
}

std::string PRACH_ConfigSCell_r10::prach_ConfigIndex_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "prach_ConfigIndex = " + std::to_string(prach_ConfigIndex_internal_value) + "\n";
    return out;
}

std::string PRACH_ConfigSCell_r10::prach_ConfigIndex_ToStringNoNewLines() const
{
    std::string out = "prach_ConfigIndex=" + std::to_string(prach_ConfigIndex_internal_value) + ",";
    return out;
}

int PRACH_ConfigSCell_r10::prach_ConfigIndex_Clear()
{
    prach_ConfigIndex_present = false;
    return 0;
}

bool PRACH_ConfigSCell_r10::prach_ConfigIndex_IsPresent() const
{
    return prach_ConfigIndex_present;
}

