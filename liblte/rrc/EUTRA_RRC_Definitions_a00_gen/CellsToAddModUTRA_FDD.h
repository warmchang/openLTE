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

#ifndef __CellsToAddModUTRA_FDD_H__
#define __CellsToAddModUTRA_FDD_H__

#include "PhysCellIdUTRA_FDD.h"

#include <array>
#include <cstdint>
#include <vector>

class CellsToAddModUTRA_FDD
{
public:
    CellsToAddModUTRA_FDD() : cellIndex_present{false}, physCellId_present{false} {};
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
    PhysCellIdUTRA_FDD* physCellId_Set();
    int physCellId_Set(PhysCellIdUTRA_FDD &value);
    const PhysCellIdUTRA_FDD& physCellId_Get() const;
    std::string physCellId_ToString(uint32_t indent) const;
    std::string physCellId_ToStringNoNewLines() const;
    int physCellId_Clear();
    bool physCellId_IsPresent() const;
private:
    bool physCellId_present;
    PhysCellIdUTRA_FDD physCellId;

};

#endif
