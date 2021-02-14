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

#ifndef __CSG_AllowedReportingCells_r9_H__
#define __CSG_AllowedReportingCells_r9_H__

#include "PhysCellIdRangeUTRA_FDDList_r9.h"

#include <array>
#include <cstdint>
#include <vector>

class CSG_AllowedReportingCells_r9
{
public:
    CSG_AllowedReportingCells_r9() : physCellIdRangeUTRA_FDDList_r9_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // physCellIdRangeUTRA-FDDList-r9
public:
    PhysCellIdRangeUTRA_FDDList_r9* physCellIdRangeUTRA_FDDList_r9_Set();
    int physCellIdRangeUTRA_FDDList_r9_Set(PhysCellIdRangeUTRA_FDDList_r9 &value);
    const PhysCellIdRangeUTRA_FDDList_r9& physCellIdRangeUTRA_FDDList_r9_Get() const;
    std::string physCellIdRangeUTRA_FDDList_r9_ToString(uint32_t indent) const;
    std::string physCellIdRangeUTRA_FDDList_r9_ToStringNoNewLines() const;
    int physCellIdRangeUTRA_FDDList_r9_Clear();
    bool physCellIdRangeUTRA_FDDList_r9_IsPresent() const;
private:
    bool physCellIdRangeUTRA_FDDList_r9_present;
    PhysCellIdRangeUTRA_FDDList_r9 physCellIdRangeUTRA_FDDList_r9;

};

#endif
