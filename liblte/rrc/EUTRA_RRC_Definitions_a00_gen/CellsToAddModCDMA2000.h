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

#ifndef __CellsToAddModCDMA2000_H__
#define __CellsToAddModCDMA2000_H__

#include "PhysCellIdCDMA2000.h"

#include <array>
#include <cstdint>
#include <vector>

class CellsToAddModCDMA2000
{
public:
    CellsToAddModCDMA2000() : cellIndex_present{false}, physCellId_present{false} {};
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

    // physCellId
public:
    PhysCellIdCDMA2000* physCellId_Set();
    int physCellId_Set(PhysCellIdCDMA2000 &value);
    const PhysCellIdCDMA2000& physCellId_Get() const;
    std::string physCellId_ToString(uint32_t indent) const;
    std::string physCellId_ToStringNoNewLines() const;
    int physCellId_Clear();
    bool physCellId_IsPresent() const;
private:
    bool physCellId_present;
    PhysCellIdCDMA2000 physCellId;

};

#endif
