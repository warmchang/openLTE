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

#ifndef __SystemInfoListGERAN_H__
#define __SystemInfoListGERAN_H__

#include <array>
#include <cstdint>
#include <vector>

class SystemInfoListGERAN
{
public:
    class SystemInfoListGERAN_items
    {
    public:
        int SystemInfoListGERAN_itemsPack(std::vector<uint8_t> &bits);
        int SystemInfoListGERAN_itemsUnpack(std::vector<uint8_t> bits);
        int SystemInfoListGERAN_itemsUnpack(std::vector<uint8_t> bits, uint32_t &idx);
        std::vector<uint8_t> SystemInfoListGERAN_itemsValue() const;
        int SystemInfoListGERAN_itemsSetValue(std::vector<uint8_t> value);
        std::string SystemInfoListGERAN_itemsToString(uint32_t indent) const;
        std::string SystemInfoListGERAN_itemsToStringNoNewLines() const;
        int SystemInfoListGERAN_itemsClear();
        bool SystemInfoListGERAN_itemsIsPresent() const;
    private:
        bool SystemInfoListGERAN_itemspresent;
        std::vector<uint8_t> SystemInfoListGERAN_itemsinternal_value;
    };

public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::vector<SystemInfoListGERAN_items> Value() const;
    int SetValue(std::vector<SystemInfoListGERAN_items>);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;
private:
    std::vector<SystemInfoListGERAN_items> internal_value;
    bool present;
};

#endif
