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

#include "N1_PUCCH_AN_PersistentList.h"

#include <cmath>

int N1_PUCCH_AN_PersistentList::N1_PUCCH_AN_PersistentList_items::N1_PUCCH_AN_PersistentList_itemsPack(std::vector<uint8_t> &bits)
{
    if(!N1_PUCCH_AN_PersistentList_itemspresent)
    {
        printf("N1_PUCCH_AN_PersistentList::N1_PUCCH_AN_PersistentList_items::N1_PUCCH_AN_PersistentList_itemsPack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = N1_PUCCH_AN_PersistentList_itemsinternal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (2047 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int N1_PUCCH_AN_PersistentList::N1_PUCCH_AN_PersistentList_items::N1_PUCCH_AN_PersistentList_itemsUnpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return N1_PUCCH_AN_PersistentList_itemsUnpack(bits, idx);
}

int N1_PUCCH_AN_PersistentList::N1_PUCCH_AN_PersistentList_items::N1_PUCCH_AN_PersistentList_itemsUnpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (2047 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("N1_PUCCH_AN_PersistentList::N1_PUCCH_AN_PersistentList_items::N1_PUCCH_AN_PersistentList_itemsUnpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    N1_PUCCH_AN_PersistentList_itemsinternal_value = packed_val + 0;
    N1_PUCCH_AN_PersistentList_itemspresent = true;
    return 0;
}

int64_t N1_PUCCH_AN_PersistentList::N1_PUCCH_AN_PersistentList_items::N1_PUCCH_AN_PersistentList_itemsValue() const
{
    if(N1_PUCCH_AN_PersistentList_itemspresent)
        return N1_PUCCH_AN_PersistentList_itemsinternal_value;
    int64_t tmp = 0;
    return tmp;
}

int N1_PUCCH_AN_PersistentList::N1_PUCCH_AN_PersistentList_items::N1_PUCCH_AN_PersistentList_itemsSetValue(int64_t value)
{
    if(value < 0 || value > 2047)
    {
        printf("N1_PUCCH_AN_PersistentList::N1_PUCCH_AN_PersistentList_items::N1_PUCCH_AN_PersistentList_itemsSetValue() range failure\n");
        return -1;
    }
    N1_PUCCH_AN_PersistentList_itemsinternal_value = value;
    N1_PUCCH_AN_PersistentList_itemspresent = true;
    return 0;
}

std::string N1_PUCCH_AN_PersistentList::N1_PUCCH_AN_PersistentList_items::N1_PUCCH_AN_PersistentList_itemsToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += " = " + std::to_string(N1_PUCCH_AN_PersistentList_itemsinternal_value) + "\n";
    return out;
}

std::string N1_PUCCH_AN_PersistentList::N1_PUCCH_AN_PersistentList_items::N1_PUCCH_AN_PersistentList_itemsToStringNoNewLines() const
{
    std::string out = "=" + std::to_string(N1_PUCCH_AN_PersistentList_itemsinternal_value) + ",";
    return out;
}

int N1_PUCCH_AN_PersistentList::N1_PUCCH_AN_PersistentList_items::N1_PUCCH_AN_PersistentList_itemsClear()
{
    N1_PUCCH_AN_PersistentList_itemspresent = false;
    return 0;
}

bool N1_PUCCH_AN_PersistentList::N1_PUCCH_AN_PersistentList_items::N1_PUCCH_AN_PersistentList_itemsIsPresent() const
{
    return N1_PUCCH_AN_PersistentList_itemspresent;
}

int N1_PUCCH_AN_PersistentList::Pack(std::vector<uint8_t> &bits)
{
    if(!present)
    {
        printf("N1_PUCCH_AN_PersistentList::Pack() presence failure\n");
        return -1;
    }
    uint32_t N_size_bits = 1;
    while(pow(2, N_size_bits) <= (4 - 1))
        N_size_bits++;
    uint32_t local_size = internal_value.size() - 1;
    for(uint32_t i=0; i<N_size_bits; i++)
        bits.push_back((local_size >> (N_size_bits-i-1)) & 1);
    for(auto item : internal_value)
        if(0 != item.N1_PUCCH_AN_PersistentList_itemsPack(bits))
        {
            printf("N1_PUCCH_AN_PersistentList::Pack() item_pack_failure\n");
            return -1;
        }
    return 0;
}

int N1_PUCCH_AN_PersistentList::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int N1_PUCCH_AN_PersistentList::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_size_bits = 1;
    while(pow(2, N_size_bits) <= (4 - 1))
        N_size_bits++;
    uint32_t size = 0;
    for(uint32_t i=0; i<N_size_bits; i++)
        size |= bits[idx++] << (N_size_bits-i-1);
    size += 1;
    internal_value.clear();
    for(uint32_t i=0; i<size; i++)
    {
        N1_PUCCH_AN_PersistentList_items tmp;
        if(0 != tmp.N1_PUCCH_AN_PersistentList_itemsUnpack(bits, idx))
        {
            printf("N1_PUCCH_AN_PersistentList::Unpack() item unpack failure\n");
            return -1;
        }
        internal_value.push_back(tmp);
    }
    present = true;
    return 0;
}

std::vector<N1_PUCCH_AN_PersistentList::N1_PUCCH_AN_PersistentList_items> N1_PUCCH_AN_PersistentList::Value() const
{
    if(present)
        return internal_value;
    return {};
}

int N1_PUCCH_AN_PersistentList::SetValue(std::vector<N1_PUCCH_AN_PersistentList::N1_PUCCH_AN_PersistentList_items> value)
{
    if(value.size() < 1 || value.size() > 4)
    {
        printf("N1_PUCCH_AN_PersistentList::SetValue() list size failure\n");
        return -1;
    }
    internal_value = value;
    present = true;
    return 0;
}

std::string N1_PUCCH_AN_PersistentList::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "N1_PUCCH_AN_PersistentList:\n";
    for(auto item : internal_value)
        out += item.N1_PUCCH_AN_PersistentList_itemsToString(indent+1);
    return out;
}

std::string N1_PUCCH_AN_PersistentList::ToStringNoNewLines() const
{
    std::string out = "N1_PUCCH_AN_PersistentList:";
    for(auto item : internal_value)
        out += item.N1_PUCCH_AN_PersistentList_itemsToStringNoNewLines();
    return out;
}

