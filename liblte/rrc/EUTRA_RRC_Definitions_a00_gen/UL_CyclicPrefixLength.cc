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

#include "UL_CyclicPrefixLength.h"

#include <cmath>

int UL_CyclicPrefixLength::Pack(std::vector<uint8_t> &bits)
{
    if(!present)
    {
        printf("UL_CyclicPrefixLength::Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int UL_CyclicPrefixLength::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int UL_CyclicPrefixLength::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("UL_CyclicPrefixLength::Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 1)
    {
        printf("UL_CyclicPrefixLength::Unpack() max failure\n");
        return -1;
    }
    internal_value = (Enum)packed_val;
    present = true;
    return 0;
}

UL_CyclicPrefixLength::Enum UL_CyclicPrefixLength::Value() const
{
    if(present)
        return internal_value;
    return (UL_CyclicPrefixLength::Enum)0;
}

int UL_CyclicPrefixLength::SetValue(Enum value)
{
    internal_value = value;
    present = true;
    return 0;
}

int UL_CyclicPrefixLength::SetValue(std::string value)
{
    if("len1" == value)
    {
        internal_value = k_len1;
        present = true;
        return 0;
    }
    if("len2" == value)
    {
        internal_value = k_len2;
        present = true;
        return 0;
    }
    return 1;
}

std::string UL_CyclicPrefixLength::ValueToString(Enum value) const
{
    if(k_len1 == value)
        return "len1";
    if(k_len2 == value)
        return "len2";
    return "";
}

uint64_t UL_CyclicPrefixLength::NumberOfValues() const
{
    return 2;
}

std::string UL_CyclicPrefixLength::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "UL_CyclicPrefixLength = " + ValueToString(internal_value) + "\n";
    return out;
}

std::string UL_CyclicPrefixLength::ToStringNoNewLines() const
{
    std::string out = "UL_CyclicPrefixLength=" + ValueToString(internal_value) + ",";
    return out;
}

int UL_CyclicPrefixLength::Clear()
{
    present = false;
    return 0;
}

bool UL_CyclicPrefixLength::IsPresent() const
{
    return present;
}

