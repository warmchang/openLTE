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

#include "AccessStratumRelease.h"

#include <cmath>

int AccessStratumRelease::Pack(std::vector<uint8_t> &bits)
{
    if(!present)
    {
        printf("AccessStratumRelease::Pack() presence failure\n");
        return -1;
    }
    if(internal_value > k_spare1)
    {
        bits.push_back(1);
    }else{
        bits.push_back(0);
    }
    uint32_t N_bits = 3;
    if(internal_value > k_spare1)
        N_bits = 0;
    for(uint32_t i=0; i<N_bits; i++)
    {
        if(internal_value > k_spare1)
        {
            bits.push_back(((internal_value - k_spare1) >> (N_bits-1-i)) & 1);
        }else{
            bits.push_back((internal_value >> (N_bits-1-i)) & 1);
        }
    }
    return 0;
}

int AccessStratumRelease::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int AccessStratumRelease::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    if((idx + 1) > bits.size())
    {
        printf("AccessStratumRelease::Unpack() index out of bounds for extension\n");
        return -1;
    }
    bool has_extension = bits[idx++];
    uint32_t packed_val = 0;
    uint32_t N_bits = 3;
    if(has_extension)
        N_bits = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("AccessStratumRelease::Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(has_extension)
    {
        internal_value = (Enum)(packed_val + 8);
    }else{
        if(packed_val > 7)
        {
            printf("AccessStratumRelease::Unpack() max failure\n");
            return -1;
        }
        internal_value = (Enum)packed_val;
    }
    present = true;
    return 0;
}

AccessStratumRelease::Enum AccessStratumRelease::Value() const
{
    if(present)
        return internal_value;
    return (AccessStratumRelease::Enum)0;
}

int AccessStratumRelease::SetValue(Enum value)
{
    internal_value = value;
    present = true;
    return 0;
}

int AccessStratumRelease::SetValue(std::string value)
{
    if("rel8" == value)
    {
        internal_value = k_rel8;
        present = true;
        return 0;
    }
    if("rel9" == value)
    {
        internal_value = k_rel9;
        present = true;
        return 0;
    }
    if("spare6" == value)
    {
        internal_value = k_spare6;
        present = true;
        return 0;
    }
    if("spare5" == value)
    {
        internal_value = k_spare5;
        present = true;
        return 0;
    }
    if("spare4" == value)
    {
        internal_value = k_spare4;
        present = true;
        return 0;
    }
    if("spare3" == value)
    {
        internal_value = k_spare3;
        present = true;
        return 0;
    }
    if("spare2" == value)
    {
        internal_value = k_spare2;
        present = true;
        return 0;
    }
    if("spare1" == value)
    {
        internal_value = k_spare1;
        present = true;
        return 0;
    }
    return 1;
}

std::string AccessStratumRelease::ValueToString(Enum value) const
{
    if(k_rel8 == value)
        return "rel8";
    if(k_rel9 == value)
        return "rel9";
    if(k_spare6 == value)
        return "spare6";
    if(k_spare5 == value)
        return "spare5";
    if(k_spare4 == value)
        return "spare4";
    if(k_spare3 == value)
        return "spare3";
    if(k_spare2 == value)
        return "spare2";
    if(k_spare1 == value)
        return "spare1";
    return "";
}

uint64_t AccessStratumRelease::NumberOfValues() const
{
    return 8;
}

std::string AccessStratumRelease::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "AccessStratumRelease = " + ValueToString(internal_value) + "\n";
    return out;
}

std::string AccessStratumRelease::ToStringNoNewLines() const
{
    std::string out = "AccessStratumRelease=" + ValueToString(internal_value) + ",";
    return out;
}

int AccessStratumRelease::Clear()
{
    present = false;
    return 0;
}

bool AccessStratumRelease::IsPresent() const
{
    return present;
}

