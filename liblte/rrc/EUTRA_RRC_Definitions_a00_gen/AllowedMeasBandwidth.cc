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

#include "AllowedMeasBandwidth.h"

#include <cmath>

int AllowedMeasBandwidth::Pack(std::vector<uint8_t> &bits)
{
    if(!present)
    {
        printf("AllowedMeasBandwidth::Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 3;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int AllowedMeasBandwidth::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int AllowedMeasBandwidth::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 3;
    if((idx + N_bits) > bits.size())
    {
        printf("AllowedMeasBandwidth::Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 5)
    {
        printf("AllowedMeasBandwidth::Unpack() max failure\n");
        return -1;
    }
    internal_value = (Enum)packed_val;
    present = true;
    return 0;
}

AllowedMeasBandwidth::Enum AllowedMeasBandwidth::Value() const
{
    if(present)
        return internal_value;
    return (AllowedMeasBandwidth::Enum)0;
}

int AllowedMeasBandwidth::SetValue(Enum value)
{
    internal_value = value;
    present = true;
    return 0;
}

int AllowedMeasBandwidth::SetValue(std::string value)
{
    if("mbw6" == value)
    {
        internal_value = k_mbw6;
        present = true;
        return 0;
    }
    if("mbw15" == value)
    {
        internal_value = k_mbw15;
        present = true;
        return 0;
    }
    if("mbw25" == value)
    {
        internal_value = k_mbw25;
        present = true;
        return 0;
    }
    if("mbw50" == value)
    {
        internal_value = k_mbw50;
        present = true;
        return 0;
    }
    if("mbw75" == value)
    {
        internal_value = k_mbw75;
        present = true;
        return 0;
    }
    if("mbw100" == value)
    {
        internal_value = k_mbw100;
        present = true;
        return 0;
    }
    return 1;
}

std::string AllowedMeasBandwidth::ValueToString(Enum value) const
{
    if(k_mbw6 == value)
        return "mbw6";
    if(k_mbw15 == value)
        return "mbw15";
    if(k_mbw25 == value)
        return "mbw25";
    if(k_mbw50 == value)
        return "mbw50";
    if(k_mbw75 == value)
        return "mbw75";
    if(k_mbw100 == value)
        return "mbw100";
    return "";
}

uint64_t AllowedMeasBandwidth::NumberOfValues() const
{
    return 6;
}

std::string AllowedMeasBandwidth::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "AllowedMeasBandwidth = " + ValueToString(internal_value) + "\n";
    return out;
}

std::string AllowedMeasBandwidth::ToStringNoNewLines() const
{
    std::string out = "AllowedMeasBandwidth=" + ValueToString(internal_value) + ",";
    return out;
}

int AllowedMeasBandwidth::Clear()
{
    present = false;
    return 0;
}

bool AllowedMeasBandwidth::IsPresent() const
{
    return present;
}

