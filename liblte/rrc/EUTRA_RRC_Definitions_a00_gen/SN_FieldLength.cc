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

#include "SN_FieldLength.h"

#include <cmath>

int SN_FieldLength::Pack(std::vector<uint8_t> &bits)
{
    if(!present)
    {
        printf("SN_FieldLength::Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int SN_FieldLength::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int SN_FieldLength::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("SN_FieldLength::Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 1)
    {
        printf("SN_FieldLength::Unpack() max failure\n");
        return -1;
    }
    internal_value = (Enum)packed_val;
    present = true;
    return 0;
}

SN_FieldLength::Enum SN_FieldLength::Value() const
{
    if(present)
        return internal_value;
    return (SN_FieldLength::Enum)0;
}

int SN_FieldLength::SetValue(Enum value)
{
    internal_value = value;
    present = true;
    return 0;
}

int SN_FieldLength::SetValue(std::string value)
{
    if("size5" == value)
    {
        internal_value = k_size5;
        present = true;
        return 0;
    }
    if("size10" == value)
    {
        internal_value = k_size10;
        present = true;
        return 0;
    }
    return 1;
}

std::string SN_FieldLength::ValueToString(Enum value) const
{
    if(k_size5 == value)
        return "size5";
    if(k_size10 == value)
        return "size10";
    return "";
}

uint64_t SN_FieldLength::NumberOfValues() const
{
    return 2;
}

std::string SN_FieldLength::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "SN_FieldLength = " + ValueToString(internal_value) + "\n";
    return out;
}

std::string SN_FieldLength::ToStringNoNewLines() const
{
    std::string out = "SN_FieldLength=" + ValueToString(internal_value) + ",";
    return out;
}

int SN_FieldLength::Clear()
{
    present = false;
    return 0;
}

bool SN_FieldLength::IsPresent() const
{
    return present;
}

