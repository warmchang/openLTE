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

#include "NeighCellConfig.h"

#include <cmath>

int NeighCellConfig::Pack(std::vector<uint8_t> &bits)
{
    if(!present)
    {
        printf("NeighCellConfig::Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 2;
    if(size < 2 || size > 2)
    {
        printf("NeighCellConfig::Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((internal_value >> (2-i-1)) & 1);
    return 0;
}

int NeighCellConfig::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int NeighCellConfig::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 2;
    if(size < 2 || size > 2)
    {
        printf("NeighCellConfig::Unpack() size failure\n");
        return -1;
    }
    internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("NeighCellConfig::Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        internal_value |= (uint8_t)bits[idx++] << (uint8_t)(2-i-1);
    present = true;
    return 0;
}

uint8_t NeighCellConfig::Value() const
{
    if(present)
        return internal_value;
    uint8_t tmp = 0;
    return tmp;
}

int NeighCellConfig::SetValue(uint8_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 2)
    {
        printf("NeighCellConfig::SetValue() size failure\n");
        return -1;
    }
    internal_value = value;
    present = true;
    return 0;
}

std::string NeighCellConfig::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "NeighCellConfig = ";
    out += std::to_string(internal_value);
    out += "\n";
    return out;
}

std::string NeighCellConfig::ToStringNoNewLines() const
{
    std::string out = "NeighCellConfig=";
    out += std::to_string(internal_value);
    out += ",";
    return out;
}

int NeighCellConfig::Clear()
{
    present = false;
    return 0;
}

bool NeighCellConfig::IsPresent() const
{
    return present;
}

