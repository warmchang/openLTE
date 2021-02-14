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

#include "BandIndicatorGERAN.h"

#include <cmath>

int BandIndicatorGERAN::Pack(std::vector<uint8_t> &bits)
{
    if(!present)
    {
        printf("BandIndicatorGERAN::Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int BandIndicatorGERAN::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int BandIndicatorGERAN::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("BandIndicatorGERAN::Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 1)
    {
        printf("BandIndicatorGERAN::Unpack() max failure\n");
        return -1;
    }
    internal_value = (Enum)packed_val;
    present = true;
    return 0;
}

BandIndicatorGERAN::Enum BandIndicatorGERAN::Value() const
{
    if(present)
        return internal_value;
    return (BandIndicatorGERAN::Enum)0;
}

int BandIndicatorGERAN::SetValue(Enum value)
{
    internal_value = value;
    present = true;
    return 0;
}

int BandIndicatorGERAN::SetValue(std::string value)
{
    if("dcs1800" == value)
    {
        internal_value = k_dcs1800;
        present = true;
        return 0;
    }
    if("pcs1900" == value)
    {
        internal_value = k_pcs1900;
        present = true;
        return 0;
    }
    return 1;
}

std::string BandIndicatorGERAN::ValueToString(Enum value) const
{
    if(k_dcs1800 == value)
        return "dcs1800";
    if(k_pcs1900 == value)
        return "pcs1900";
    return "";
}

uint64_t BandIndicatorGERAN::NumberOfValues() const
{
    return 2;
}

std::string BandIndicatorGERAN::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "BandIndicatorGERAN = " + ValueToString(internal_value) + "\n";
    return out;
}

std::string BandIndicatorGERAN::ToStringNoNewLines() const
{
    std::string out = "BandIndicatorGERAN=" + ValueToString(internal_value) + ",";
    return out;
}

int BandIndicatorGERAN::Clear()
{
    present = false;
    return 0;
}

bool BandIndicatorGERAN::IsPresent() const
{
    return present;
}

