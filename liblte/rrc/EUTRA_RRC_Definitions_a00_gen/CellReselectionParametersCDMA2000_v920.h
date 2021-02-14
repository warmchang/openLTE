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

#ifndef __CellReselectionParametersCDMA2000_v920_H__
#define __CellReselectionParametersCDMA2000_v920_H__

#include "NeighCellListCDMA2000_v920.h"

#include <array>
#include <cstdint>
#include <vector>

class CellReselectionParametersCDMA2000_v920
{
public:
    CellReselectionParametersCDMA2000_v920() : neighCellList_v920_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // neighCellList-v920
public:
    NeighCellListCDMA2000_v920* neighCellList_v920_Set();
    int neighCellList_v920_Set(NeighCellListCDMA2000_v920 &value);
    const NeighCellListCDMA2000_v920& neighCellList_v920_Get() const;
    std::string neighCellList_v920_ToString(uint32_t indent) const;
    std::string neighCellList_v920_ToStringNoNewLines() const;
    int neighCellList_v920_Clear();
    bool neighCellList_v920_IsPresent() const;
private:
    bool neighCellList_v920_present;
    NeighCellListCDMA2000_v920 neighCellList_v920;

};

#endif
