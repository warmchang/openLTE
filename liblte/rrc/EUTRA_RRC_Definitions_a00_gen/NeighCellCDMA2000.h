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

#ifndef __NeighCellCDMA2000_H__
#define __NeighCellCDMA2000_H__

#include "BandclassCDMA2000.h"
#include "NeighCellsPerBandclassListCDMA2000.h"

#include <array>
#include <cstdint>
#include <vector>

class NeighCellCDMA2000
{
public:
    NeighCellCDMA2000() : bandClass_present{false}, neighCellsPerFreqList_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // bandClass
public:
    BandclassCDMA2000* bandClass_Set();
    int bandClass_Set(BandclassCDMA2000 &value);
    const BandclassCDMA2000& bandClass_Get() const;
    std::string bandClass_ToString(uint32_t indent) const;
    std::string bandClass_ToStringNoNewLines() const;
    int bandClass_Clear();
    bool bandClass_IsPresent() const;
private:
    bool bandClass_present;
    BandclassCDMA2000 bandClass;

    // neighCellsPerFreqList
public:
    NeighCellsPerBandclassListCDMA2000* neighCellsPerFreqList_Set();
    int neighCellsPerFreqList_Set(NeighCellsPerBandclassListCDMA2000 &value);
    const NeighCellsPerBandclassListCDMA2000& neighCellsPerFreqList_Get() const;
    std::string neighCellsPerFreqList_ToString(uint32_t indent) const;
    std::string neighCellsPerFreqList_ToStringNoNewLines() const;
    int neighCellsPerFreqList_Clear();
    bool neighCellsPerFreqList_IsPresent() const;
private:
    bool neighCellsPerFreqList_present;
    NeighCellsPerBandclassListCDMA2000 neighCellsPerFreqList;

};

#endif
