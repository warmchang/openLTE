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

#ifndef __NeighCellCDMA2000_v920_H__
#define __NeighCellCDMA2000_v920_H__

#include "NeighCellsPerBandclassListCDMA2000_v920.h"

#include <array>
#include <cstdint>
#include <vector>

class NeighCellCDMA2000_v920
{
public:
    NeighCellCDMA2000_v920() : neighCellsPerFreqList_v920_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // neighCellsPerFreqList-v920
public:
    NeighCellsPerBandclassListCDMA2000_v920* neighCellsPerFreqList_v920_Set();
    int neighCellsPerFreqList_v920_Set(NeighCellsPerBandclassListCDMA2000_v920 &value);
    const NeighCellsPerBandclassListCDMA2000_v920& neighCellsPerFreqList_v920_Get() const;
    std::string neighCellsPerFreqList_v920_ToString(uint32_t indent) const;
    std::string neighCellsPerFreqList_v920_ToStringNoNewLines() const;
    int neighCellsPerFreqList_v920_Clear();
    bool neighCellsPerFreqList_v920_IsPresent() const;
private:
    bool neighCellsPerFreqList_v920_present;
    NeighCellsPerBandclassListCDMA2000_v920 neighCellsPerFreqList_v920;

};

#endif
