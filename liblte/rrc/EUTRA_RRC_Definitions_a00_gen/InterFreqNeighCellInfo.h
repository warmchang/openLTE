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

#ifndef __InterFreqNeighCellInfo_H__
#define __InterFreqNeighCellInfo_H__

#include "PhysCellId.h"
#include "Q_OffsetRange.h"

#include <array>
#include <cstdint>
#include <vector>

class InterFreqNeighCellInfo
{
public:
    InterFreqNeighCellInfo() : physCellId_present{false}, q_OffsetCell_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

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

    // q-OffsetCell
public:
    Q_OffsetRange* q_OffsetCell_Set();
    int q_OffsetCell_Set(Q_OffsetRange &value);
    const Q_OffsetRange& q_OffsetCell_Get() const;
    std::string q_OffsetCell_ToString(uint32_t indent) const;
    std::string q_OffsetCell_ToStringNoNewLines() const;
    int q_OffsetCell_Clear();
    bool q_OffsetCell_IsPresent() const;
private:
    bool q_OffsetCell_present;
    Q_OffsetRange q_OffsetCell;

};

#endif
