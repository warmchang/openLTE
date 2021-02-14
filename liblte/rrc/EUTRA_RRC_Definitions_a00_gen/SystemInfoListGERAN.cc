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

#include "SystemInfoListGERAN.h"

#include <cmath>

int SystemInfoListGERAN::SystemInfoListGERAN_items::SystemInfoListGERAN_itemsPack(std::vector<uint8_t> &bits)
{
    if(!SystemInfoListGERAN_itemspresent)
    {
        printf("SystemInfoListGERAN::SystemInfoListGERAN_items::SystemInfoListGERAN_itemsPack() presence failure\n");
        return -1;
    }
    if(SystemInfoListGERAN_itemsinternal_value.size() < 1 || SystemInfoListGERAN_itemsinternal_value.size() > 23)
    {
        printf("SystemInfoListGERAN::SystemInfoListGERAN_items::SystemInfoListGERAN_itemsPack() size failure\n");
        return -1;
    }
    uint32_t N_size_bits = 1;
    while(pow(2, N_size_bits) <= (23 - 1))
        N_size_bits++;
    uint32_t local_size = SystemInfoListGERAN_itemsinternal_value.size() - 1;
    for(uint32_t i=0; i<N_size_bits; i++)
        bits.push_back((local_size >> (N_size_bits-i-1)) & 1);
    for(uint32_t i=0; i<SystemInfoListGERAN_itemsinternal_value.size(); i++)
        for(uint32_t j=0; j<8; j++)
            bits.push_back((SystemInfoListGERAN_itemsinternal_value[i] >> (8-j-1)) & 1);
    return 0;
}

int SystemInfoListGERAN::SystemInfoListGERAN_items::SystemInfoListGERAN_itemsUnpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return SystemInfoListGERAN_itemsUnpack(bits, idx);
}

int SystemInfoListGERAN::SystemInfoListGERAN_items::SystemInfoListGERAN_itemsUnpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_size_bits = 1;
    while(pow(2, N_size_bits) <= (23 - 1))
        N_size_bits++;
    uint32_t size = 0;
    for(uint32_t i=0; i<N_size_bits; i++)
        size |= bits[idx++] << (N_size_bits-i-1);
    size += 1;
    if(size < 1 || size > 23)
    {
        printf("SystemInfoListGERAN::SystemInfoListGERAN_items::SystemInfoListGERAN_itemsUnpack() size failure\n");
        return -1;
    }
    SystemInfoListGERAN_itemsinternal_value.clear();
    if((idx +size*8) > bits.size())
    {
        printf("SystemInfoListGERAN::SystemInfoListGERAN_items::SystemInfoListGERAN_itemsUnpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
    {
        uint8_t value = 0;
        for(uint32_t j=0; j<8; j++)
            value |= bits[idx+j] << (8-j-1);
        SystemInfoListGERAN_itemsinternal_value.push_back(value);
        idx += 8;
    }
    SystemInfoListGERAN_itemspresent = true;
    return 0;
}

std::vector<uint8_t> SystemInfoListGERAN::SystemInfoListGERAN_items::SystemInfoListGERAN_itemsValue() const
{
    if(SystemInfoListGERAN_itemspresent)
        return SystemInfoListGERAN_itemsinternal_value;
    std::vector<uint8_t> tmp;
    return tmp;
}

int SystemInfoListGERAN::SystemInfoListGERAN_items::SystemInfoListGERAN_itemsSetValue(std::vector<uint8_t> value)
{
    if(value.size() < 1 || value.size() > 23)
    {
        printf("SystemInfoListGERAN::SystemInfoListGERAN_items::SystemInfoListGERAN_itemsSetValue() size failure\n");
        return -1;
    }
    SystemInfoListGERAN_itemsinternal_value = value;
    SystemInfoListGERAN_itemspresent = true;
    return 0;
}

std::string SystemInfoListGERAN::SystemInfoListGERAN_items::SystemInfoListGERAN_itemsToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "SystemInfoListGERAN = {";
    for(auto byte : SystemInfoListGERAN_itemsinternal_value)
        out += std::to_string(byte) + ",";
    out = out.substr(0, out.length()-1) + "}\n";
    return out;
}

std::string SystemInfoListGERAN::SystemInfoListGERAN_items::SystemInfoListGERAN_itemsToStringNoNewLines() const
{
    std::string out = "SystemInfoListGERAN={";
    for(auto byte : SystemInfoListGERAN_itemsinternal_value)
        out += std::to_string(byte) + ",";
    out = out.substr(0, out.length()-1) + "},";
    return out;
}

int SystemInfoListGERAN::SystemInfoListGERAN_items::SystemInfoListGERAN_itemsClear()
{
    SystemInfoListGERAN_itemspresent = false;
    return 0;
}

bool SystemInfoListGERAN::SystemInfoListGERAN_items::SystemInfoListGERAN_itemsIsPresent() const
{
    return SystemInfoListGERAN_itemspresent;
}

#include "maxGERAN_SI.h"

int SystemInfoListGERAN::Pack(std::vector<uint8_t> &bits)
{
    if(!present)
    {
        printf("SystemInfoListGERAN::Pack() presence failure\n");
        return -1;
    }
    uint32_t N_size_bits = 1;
    while(pow(2, N_size_bits) <= (maxGERAN_SI - 1))
        N_size_bits++;
    uint32_t local_size = internal_value.size() - 1;
    for(uint32_t i=0; i<N_size_bits; i++)
        bits.push_back((local_size >> (N_size_bits-i-1)) & 1);
    for(auto item : internal_value)
        if(0 != item.SystemInfoListGERAN_itemsPack(bits))
        {
            printf("SystemInfoListGERAN::Pack() item_pack_failure\n");
            return -1;
        }
    return 0;
}

int SystemInfoListGERAN::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int SystemInfoListGERAN::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_size_bits = 1;
    while(pow(2, N_size_bits) <= (maxGERAN_SI - 1))
        N_size_bits++;
    uint32_t size = 0;
    for(uint32_t i=0; i<N_size_bits; i++)
        size |= bits[idx++] << (N_size_bits-i-1);
    size += 1;
    internal_value.clear();
    for(uint32_t i=0; i<size; i++)
    {
        SystemInfoListGERAN_items tmp;
        if(0 != tmp.SystemInfoListGERAN_itemsUnpack(bits, idx))
        {
            printf("SystemInfoListGERAN::Unpack() item unpack failure\n");
            return -1;
        }
        internal_value.push_back(tmp);
    }
    present = true;
    return 0;
}

std::vector<SystemInfoListGERAN::SystemInfoListGERAN_items> SystemInfoListGERAN::Value() const
{
    if(present)
        return internal_value;
    return {};
}

int SystemInfoListGERAN::SetValue(std::vector<SystemInfoListGERAN::SystemInfoListGERAN_items> value)
{
    if(value.size() < 1 || value.size() > maxGERAN_SI)
    {
        printf("SystemInfoListGERAN::SetValue() list size failure\n");
        return -1;
    }
    internal_value = value;
    present = true;
    return 0;
}

std::string SystemInfoListGERAN::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "SystemInfoListGERAN:\n";
    for(auto item : internal_value)
        out += item.SystemInfoListGERAN_itemsToString(indent+1);
    return out;
}

std::string SystemInfoListGERAN::ToStringNoNewLines() const
{
    std::string out = "SystemInfoListGERAN:";
    for(auto item : internal_value)
        out += item.SystemInfoListGERAN_itemsToStringNoNewLines();
    return out;
}

