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

#include "ReleaseCause.h"

#include <cmath>

int ReleaseCause::Pack(std::vector<uint8_t> &bits)
{
    if(!present)
    {
        printf("ReleaseCause::Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 2;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int ReleaseCause::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int ReleaseCause::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 2;
    if((idx + N_bits) > bits.size())
    {
        printf("ReleaseCause::Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 3)
    {
        printf("ReleaseCause::Unpack() max failure\n");
        return -1;
    }
    internal_value = (Enum)packed_val;
    present = true;
    return 0;
}

ReleaseCause::Enum ReleaseCause::Value() const
{
    if(present)
        return internal_value;
    return (ReleaseCause::Enum)0;
}

int ReleaseCause::SetValue(Enum value)
{
    internal_value = value;
    present = true;
    return 0;
}

int ReleaseCause::SetValue(std::string value)
{
    if("loadBalancingTAUrequired" == value)
    {
        internal_value = k_loadBalancingTAUrequired;
        present = true;
        return 0;
    }
    if("other" == value)
    {
        internal_value = k_other;
        present = true;
        return 0;
    }
    if("cs_FallbackHighPriority" == value)
    {
        internal_value = k_cs_FallbackHighPriority;
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

std::string ReleaseCause::ValueToString(Enum value) const
{
    if(k_loadBalancingTAUrequired == value)
        return "loadBalancingTAUrequired";
    if(k_other == value)
        return "other";
    if(k_cs_FallbackHighPriority == value)
        return "cs_FallbackHighPriority";
    if(k_spare1 == value)
        return "spare1";
    return "";
}

uint64_t ReleaseCause::NumberOfValues() const
{
    return 4;
}

std::string ReleaseCause::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ReleaseCause = " + ValueToString(internal_value) + "\n";
    return out;
}

std::string ReleaseCause::ToStringNoNewLines() const
{
    std::string out = "ReleaseCause=" + ValueToString(internal_value) + ",";
    return out;
}

int ReleaseCause::Clear()
{
    present = false;
    return 0;
}

bool ReleaseCause::IsPresent() const
{
    return present;
}

