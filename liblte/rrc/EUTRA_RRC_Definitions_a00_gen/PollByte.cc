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

#include "PollByte.h"

#include <cmath>

int PollByte::Pack(std::vector<uint8_t> &bits)
{
    if(!present)
    {
        printf("PollByte::Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 4;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int PollByte::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int PollByte::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 4;
    if((idx + N_bits) > bits.size())
    {
        printf("PollByte::Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 15)
    {
        printf("PollByte::Unpack() max failure\n");
        return -1;
    }
    internal_value = (Enum)packed_val;
    present = true;
    return 0;
}

PollByte::Enum PollByte::Value() const
{
    if(present)
        return internal_value;
    return (PollByte::Enum)0;
}

int PollByte::SetValue(Enum value)
{
    internal_value = value;
    present = true;
    return 0;
}

int PollByte::SetValue(std::string value)
{
    if("kB25" == value)
    {
        internal_value = k_kB25;
        present = true;
        return 0;
    }
    if("kB50" == value)
    {
        internal_value = k_kB50;
        present = true;
        return 0;
    }
    if("kB75" == value)
    {
        internal_value = k_kB75;
        present = true;
        return 0;
    }
    if("kB100" == value)
    {
        internal_value = k_kB100;
        present = true;
        return 0;
    }
    if("kB125" == value)
    {
        internal_value = k_kB125;
        present = true;
        return 0;
    }
    if("kB250" == value)
    {
        internal_value = k_kB250;
        present = true;
        return 0;
    }
    if("kB375" == value)
    {
        internal_value = k_kB375;
        present = true;
        return 0;
    }
    if("kB500" == value)
    {
        internal_value = k_kB500;
        present = true;
        return 0;
    }
    if("kB750" == value)
    {
        internal_value = k_kB750;
        present = true;
        return 0;
    }
    if("kB1000" == value)
    {
        internal_value = k_kB1000;
        present = true;
        return 0;
    }
    if("kB1250" == value)
    {
        internal_value = k_kB1250;
        present = true;
        return 0;
    }
    if("kB1500" == value)
    {
        internal_value = k_kB1500;
        present = true;
        return 0;
    }
    if("kB2000" == value)
    {
        internal_value = k_kB2000;
        present = true;
        return 0;
    }
    if("kB3000" == value)
    {
        internal_value = k_kB3000;
        present = true;
        return 0;
    }
    if("kBinfinity" == value)
    {
        internal_value = k_kBinfinity;
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

std::string PollByte::ValueToString(Enum value) const
{
    if(k_kB25 == value)
        return "kB25";
    if(k_kB50 == value)
        return "kB50";
    if(k_kB75 == value)
        return "kB75";
    if(k_kB100 == value)
        return "kB100";
    if(k_kB125 == value)
        return "kB125";
    if(k_kB250 == value)
        return "kB250";
    if(k_kB375 == value)
        return "kB375";
    if(k_kB500 == value)
        return "kB500";
    if(k_kB750 == value)
        return "kB750";
    if(k_kB1000 == value)
        return "kB1000";
    if(k_kB1250 == value)
        return "kB1250";
    if(k_kB1500 == value)
        return "kB1500";
    if(k_kB2000 == value)
        return "kB2000";
    if(k_kB3000 == value)
        return "kB3000";
    if(k_kBinfinity == value)
        return "kBinfinity";
    if(k_spare1 == value)
        return "spare1";
    return "";
}

uint64_t PollByte::NumberOfValues() const
{
    return 16;
}

std::string PollByte::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "PollByte = " + ValueToString(internal_value) + "\n";
    return out;
}

std::string PollByte::ToStringNoNewLines() const
{
    std::string out = "PollByte=" + ValueToString(internal_value) + ",";
    return out;
}

int PollByte::Clear()
{
    present = false;
    return 0;
}

bool PollByte::IsPresent() const
{
    return present;
}

