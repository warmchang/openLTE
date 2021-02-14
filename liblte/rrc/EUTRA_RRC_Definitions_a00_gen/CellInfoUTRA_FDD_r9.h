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

#ifndef __CellInfoUTRA_FDD_r9_H__
#define __CellInfoUTRA_FDD_r9_H__

#include "PhysCellIdUTRA_FDD.h"

#include <array>
#include <cstdint>
#include <vector>

class CellInfoUTRA_FDD_r9
{
public:
    CellInfoUTRA_FDD_r9() : physCellId_r9_present{false}, utra_BCCH_Container_r9_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // physCellId-r9
public:
    PhysCellIdUTRA_FDD* physCellId_r9_Set();
    int physCellId_r9_Set(PhysCellIdUTRA_FDD &value);
    const PhysCellIdUTRA_FDD& physCellId_r9_Get() const;
    std::string physCellId_r9_ToString(uint32_t indent) const;
    std::string physCellId_r9_ToStringNoNewLines() const;
    int physCellId_r9_Clear();
    bool physCellId_r9_IsPresent() const;
private:
    bool physCellId_r9_present;
    PhysCellIdUTRA_FDD physCellId_r9;

    // utra-BCCH-Container-r9
public:
    int utra_BCCH_Container_r9_Pack(std::vector<uint8_t> &bits);
    int utra_BCCH_Container_r9_Unpack(std::vector<uint8_t> bits);
    int utra_BCCH_Container_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::vector<uint8_t> utra_BCCH_Container_r9_Value() const;
    int utra_BCCH_Container_r9_SetValue(std::vector<uint8_t> value);
    std::string utra_BCCH_Container_r9_ToString(uint32_t indent) const;
    std::string utra_BCCH_Container_r9_ToStringNoNewLines() const;
    int utra_BCCH_Container_r9_Clear();
    bool utra_BCCH_Container_r9_IsPresent() const;
private:
    bool utra_BCCH_Container_r9_present;
    std::vector<uint8_t> utra_BCCH_Container_r9_internal_value;

};

#endif
