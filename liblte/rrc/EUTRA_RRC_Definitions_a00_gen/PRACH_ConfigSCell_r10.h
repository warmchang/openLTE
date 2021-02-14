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

#ifndef __PRACH_ConfigSCell_r10_H__
#define __PRACH_ConfigSCell_r10_H__

#include <array>
#include <cstdint>
#include <vector>

class PRACH_ConfigSCell_r10
{
public:
    PRACH_ConfigSCell_r10() : prach_ConfigIndex_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // prach-ConfigIndex
public:
    int prach_ConfigIndex_Pack(std::vector<uint8_t> &bits);
    int prach_ConfigIndex_Unpack(std::vector<uint8_t> bits);
    int prach_ConfigIndex_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t prach_ConfigIndex_Value() const;
    int prach_ConfigIndex_SetValue(int64_t value);
    std::string prach_ConfigIndex_ToString(uint32_t indent) const;
    std::string prach_ConfigIndex_ToStringNoNewLines() const;
    int prach_ConfigIndex_Clear();
    bool prach_ConfigIndex_IsPresent() const;
private:
    bool prach_ConfigIndex_present;
    int64_t prach_ConfigIndex_internal_value;

};

#endif
