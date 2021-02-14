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

#ifndef __NeighCellsPerBandclassCDMA2000_H__
#define __NeighCellsPerBandclassCDMA2000_H__

#include "ARFCN_ValueCDMA2000.h"
#include "PhysCellIdListCDMA2000.h"

#include <array>
#include <cstdint>
#include <vector>

class NeighCellsPerBandclassCDMA2000
{
public:
    NeighCellsPerBandclassCDMA2000() : arfcn_present{false}, physCellIdList_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // arfcn
public:
    ARFCN_ValueCDMA2000* arfcn_Set();
    int arfcn_Set(ARFCN_ValueCDMA2000 &value);
    const ARFCN_ValueCDMA2000& arfcn_Get() const;
    std::string arfcn_ToString(uint32_t indent) const;
    std::string arfcn_ToStringNoNewLines() const;
    int arfcn_Clear();
    bool arfcn_IsPresent() const;
private:
    bool arfcn_present;
    ARFCN_ValueCDMA2000 arfcn;

    // physCellIdList
public:
    PhysCellIdListCDMA2000* physCellIdList_Set();
    int physCellIdList_Set(PhysCellIdListCDMA2000 &value);
    const PhysCellIdListCDMA2000& physCellIdList_Get() const;
    std::string physCellIdList_ToString(uint32_t indent) const;
    std::string physCellIdList_ToStringNoNewLines() const;
    int physCellIdList_Clear();
    bool physCellIdList_IsPresent() const;
private:
    bool physCellIdList_present;
    PhysCellIdListCDMA2000 physCellIdList;

};

#endif
