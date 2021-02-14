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

#include "Key_eNodeB_Star.h"

#include <cmath>

int Key_eNodeB_Star::Pack(std::vector<uint8_t> &bits)
{
    if(!present)
    {
        printf("Key_eNodeB_Star::Pack() presence failure\n");
        return -1;
    }
    uint32_t size = internal_value.size();
    if(size < 256 || size > 256)
    {
        printf("Key_eNodeB_Star::Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back(internal_value[i]);
    return 0;
}

int Key_eNodeB_Star::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int Key_eNodeB_Star::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 256;
    if(size < 256 || size > 256)
    {
        printf("Key_eNodeB_Star::Unpack() size failure\n");
        return -1;
    }
    internal_value.clear();
    if((idx + size) > bits.size())
    {
        printf("Key_eNodeB_Star::Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        internal_value[i] = bits[idx++];
    present = true;
    return 0;
}

std::vector<uint8_t> Key_eNodeB_Star::Value() const
{
    if(present)
        return internal_value;
    std::vector<uint8_t> tmp;
    return tmp;
}

int Key_eNodeB_Star::SetValue(std::vector<uint8_t> value)
{
    if(value.size() < 256 || value.size() > 256)
    {
        printf("Key_eNodeB_Star::SetValue() size failure\n");
        return -1;
    }
    internal_value = value;
    present = true;
    return 0;
}

std::string Key_eNodeB_Star::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "Key_eNodeB_Star = ";
    for(auto bit : internal_value)
        out += std::to_string(bit);
    out += "\n";
    return out;
}

std::string Key_eNodeB_Star::ToStringNoNewLines() const
{
    std::string out = "Key_eNodeB_Star=";
    for(auto bit : internal_value)
        out += std::to_string(bit);
    out += ",";
    return out;
}

int Key_eNodeB_Star::Clear()
{
    present = false;
    return 0;
}

bool Key_eNodeB_Star::IsPresent() const
{
    return present;
}

