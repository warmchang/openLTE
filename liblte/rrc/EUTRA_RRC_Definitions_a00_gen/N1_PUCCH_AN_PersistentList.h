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

#ifndef __N1_PUCCH_AN_PersistentList_H__
#define __N1_PUCCH_AN_PersistentList_H__

#include <array>
#include <cstdint>
#include <vector>

class N1_PUCCH_AN_PersistentList
{
public:
    class N1_PUCCH_AN_PersistentList_items
    {
    public:
        int N1_PUCCH_AN_PersistentList_itemsPack(std::vector<uint8_t> &bits);
        int N1_PUCCH_AN_PersistentList_itemsUnpack(std::vector<uint8_t> bits);
        int N1_PUCCH_AN_PersistentList_itemsUnpack(std::vector<uint8_t> bits, uint32_t &idx);
        int64_t N1_PUCCH_AN_PersistentList_itemsValue() const;
        int N1_PUCCH_AN_PersistentList_itemsSetValue(int64_t value);
        std::string N1_PUCCH_AN_PersistentList_itemsToString(uint32_t indent) const;
        std::string N1_PUCCH_AN_PersistentList_itemsToStringNoNewLines() const;
        int N1_PUCCH_AN_PersistentList_itemsClear();
        bool N1_PUCCH_AN_PersistentList_itemsIsPresent() const;
    private:
        bool N1_PUCCH_AN_PersistentList_itemspresent;
        int64_t N1_PUCCH_AN_PersistentList_itemsinternal_value;
    };

public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::vector<N1_PUCCH_AN_PersistentList_items> Value() const;
    int SetValue(std::vector<N1_PUCCH_AN_PersistentList_items>);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;
private:
    std::vector<N1_PUCCH_AN_PersistentList_items> internal_value;
    bool present;
};

#endif
