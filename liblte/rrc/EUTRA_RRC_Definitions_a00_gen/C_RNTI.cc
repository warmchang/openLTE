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

#include "C_RNTI.h"

#include <cmath>

int C_RNTI::Pack(std::vector<uint8_t> &bits)
{
    if(!present)
    {
        printf("C_RNTI::Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 16;
    if(size < 16 || size > 16)
    {
        printf("C_RNTI::Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((internal_value >> (16-i-1)) & 1);
    return 0;
}

int C_RNTI::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int C_RNTI::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 16;
    if(size < 16 || size > 16)
    {
        printf("C_RNTI::Unpack() size failure\n");
        return -1;
    }
    internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("C_RNTI::Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        internal_value |= (uint16_t)bits[idx++] << (uint16_t)(16-i-1);
    present = true;
    return 0;
}

uint16_t C_RNTI::Value() const
{
    if(present)
        return internal_value;
    uint16_t tmp = 0;
    return tmp;
}

int C_RNTI::SetValue(uint16_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 16)
    {
        printf("C_RNTI::SetValue() size failure\n");
        return -1;
    }
    internal_value = value;
    present = true;
    return 0;
}

std::string C_RNTI::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "C_RNTI = ";
    out += std::to_string(internal_value);
    out += "\n";
    return out;
}

std::string C_RNTI::ToStringNoNewLines() const
{
    std::string out = "C_RNTI=";
    out += std::to_string(internal_value);
    out += ",";
    return out;
}

int C_RNTI::Clear()
{
    present = false;
    return 0;
}

bool C_RNTI::IsPresent() const
{
    return present;
}

