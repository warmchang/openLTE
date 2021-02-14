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

#ifndef __PhysCellIdRange_H__
#define __PhysCellIdRange_H__

#include "PhysCellId.h"

#include <array>
#include <cstdint>
#include <vector>

class PhysCellIdRange
{
public:
    PhysCellIdRange() : start_present{false}, range_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // start
public:
    PhysCellId* start_Set();
    int start_Set(PhysCellId &value);
    const PhysCellId& start_Get() const;
    std::string start_ToString(uint32_t indent) const;
    std::string start_ToStringNoNewLines() const;
    int start_Clear();
    bool start_IsPresent() const;
private:
    bool start_present;
    PhysCellId start;

    // range
public:
    enum range_Enum {
        k_range_n4 = 0,
        k_range_n8,
        k_range_n12,
        k_range_n16,
        k_range_n24,
        k_range_n32,
        k_range_n48,
        k_range_n64,
        k_range_n84,
        k_range_n96,
        k_range_n128,
        k_range_n168,
        k_range_n252,
        k_range_n504,
        k_range_spare2,
        k_range_spare1,
    };
    int range_Pack(std::vector<uint8_t> &bits);
    int range_Unpack(std::vector<uint8_t> bits);
    int range_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    range_Enum range_Value() const;
    int range_SetValue(range_Enum value);
    int range_SetValue(std::string value);
    std::string range_ValueToString(range_Enum value) const;
    uint64_t range_NumberOfValues() const;
    std::string range_ToString(uint32_t indent) const;
    std::string range_ToStringNoNewLines() const;
    int range_Clear();
    bool range_IsPresent() const;
private:
    bool range_present;
    range_Enum range_internal_value;

};

#endif
