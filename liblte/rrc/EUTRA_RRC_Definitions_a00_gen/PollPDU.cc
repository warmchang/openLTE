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

#include "PollPDU.h"

#include <cmath>

int PollPDU::Pack(std::vector<uint8_t> &bits)
{
    if(!present)
    {
        printf("PollPDU::Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 3;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int PollPDU::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int PollPDU::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 3;
    if((idx + N_bits) > bits.size())
    {
        printf("PollPDU::Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 7)
    {
        printf("PollPDU::Unpack() max failure\n");
        return -1;
    }
    internal_value = (Enum)packed_val;
    present = true;
    return 0;
}

PollPDU::Enum PollPDU::Value() const
{
    if(present)
        return internal_value;
    return (PollPDU::Enum)0;
}

int PollPDU::SetValue(Enum value)
{
    internal_value = value;
    present = true;
    return 0;
}

int PollPDU::SetValue(std::string value)
{
    if("p4" == value)
    {
        internal_value = k_p4;
        present = true;
        return 0;
    }
    if("p8" == value)
    {
        internal_value = k_p8;
        present = true;
        return 0;
    }
    if("p16" == value)
    {
        internal_value = k_p16;
        present = true;
        return 0;
    }
    if("p32" == value)
    {
        internal_value = k_p32;
        present = true;
        return 0;
    }
    if("p64" == value)
    {
        internal_value = k_p64;
        present = true;
        return 0;
    }
    if("p128" == value)
    {
        internal_value = k_p128;
        present = true;
        return 0;
    }
    if("p256" == value)
    {
        internal_value = k_p256;
        present = true;
        return 0;
    }
    if("pInfinity" == value)
    {
        internal_value = k_pInfinity;
        present = true;
        return 0;
    }
    return 1;
}

std::string PollPDU::ValueToString(Enum value) const
{
    if(k_p4 == value)
        return "p4";
    if(k_p8 == value)
        return "p8";
    if(k_p16 == value)
        return "p16";
    if(k_p32 == value)
        return "p32";
    if(k_p64 == value)
        return "p64";
    if(k_p128 == value)
        return "p128";
    if(k_p256 == value)
        return "p256";
    if(k_pInfinity == value)
        return "pInfinity";
    return "";
}

uint64_t PollPDU::NumberOfValues() const
{
    return 8;
}

std::string PollPDU::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "PollPDU = " + ValueToString(internal_value) + "\n";
    return out;
}

std::string PollPDU::ToStringNoNewLines() const
{
    std::string out = "PollPDU=" + ValueToString(internal_value) + ",";
    return out;
}

int PollPDU::Clear()
{
    present = false;
    return 0;
}

bool PollPDU::IsPresent() const
{
    return present;
}

