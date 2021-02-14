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

#ifndef __BlackCellsToAddMod_H__
#define __BlackCellsToAddMod_H__

#include "PhysCellIdRange.h"

#include <array>
#include <cstdint>
#include <vector>

class BlackCellsToAddMod
{
public:
    BlackCellsToAddMod() : cellIndex_present{false}, physCellIdRange_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // cellIndex
public:
    int cellIndex_Pack(std::vector<uint8_t> &bits);
    int cellIndex_Unpack(std::vector<uint8_t> bits);
    int cellIndex_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t cellIndex_Value() const;
    int cellIndex_SetValue(int64_t value);
    std::string cellIndex_ToString(uint32_t indent) const;
    std::string cellIndex_ToStringNoNewLines() const;
    int cellIndex_Clear();
    bool cellIndex_IsPresent() const;
private:
    bool cellIndex_present;
    int64_t cellIndex_internal_value;

    // physCellIdRange
public:
    PhysCellIdRange* physCellIdRange_Set();
    int physCellIdRange_Set(PhysCellIdRange &value);
    const PhysCellIdRange& physCellIdRange_Get() const;
    std::string physCellIdRange_ToString(uint32_t indent) const;
    std::string physCellIdRange_ToStringNoNewLines() const;
    int physCellIdRange_Clear();
    bool physCellIdRange_IsPresent() const;
private:
    bool physCellIdRange_present;
    PhysCellIdRange physCellIdRange;

};

#endif
