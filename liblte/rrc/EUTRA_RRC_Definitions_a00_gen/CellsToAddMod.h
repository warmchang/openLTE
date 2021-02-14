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

#ifndef __CellsToAddMod_H__
#define __CellsToAddMod_H__

#include "PhysCellId.h"
#include "Q_OffsetRange.h"

#include <array>
#include <cstdint>
#include <vector>

class CellsToAddMod
{
public:
    CellsToAddMod() : cellIndex_present{false}, physCellId_present{false}, cellIndividualOffset_present{false} {};
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
    PhysCellId* physCellId_Set();
    int physCellId_Set(PhysCellId &value);
    const PhysCellId& physCellId_Get() const;
    std::string physCellId_ToString(uint32_t indent) const;
    std::string physCellId_ToStringNoNewLines() const;
    int physCellId_Clear();
    bool physCellId_IsPresent() const;
private:
    bool physCellId_present;
    PhysCellId physCellId;

    // cellIndividualOffset
public:
    Q_OffsetRange* cellIndividualOffset_Set();
    int cellIndividualOffset_Set(Q_OffsetRange &value);
    const Q_OffsetRange& cellIndividualOffset_Get() const;
    std::string cellIndividualOffset_ToString(uint32_t indent) const;
    std::string cellIndividualOffset_ToStringNoNewLines() const;
    int cellIndividualOffset_Clear();
    bool cellIndividualOffset_IsPresent() const;
private:
    bool cellIndividualOffset_present;
    Q_OffsetRange cellIndividualOffset;

};

#endif
