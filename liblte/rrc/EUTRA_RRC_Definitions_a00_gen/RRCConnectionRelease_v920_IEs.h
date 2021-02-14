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

#ifndef __RRCConnectionRelease_v920_IEs_H__
#define __RRCConnectionRelease_v920_IEs_H__

#include "CellInfoListGERAN_r9.h"
#include "CellInfoListUTRA_FDD_r9.h"
#include "CellInfoListUTRA_TDD_r9.h"

#include <array>
#include <cstdint>
#include <vector>

class RRCConnectionRelease_v920_IEs
{
public:
    RRCConnectionRelease_v920_IEs() : cellInfoList_r9_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // cellInfoList-r9
public:
    enum cellInfoList_r9_Enum {
        k_cellInfoList_r9_geran_r9 = 0,
        k_cellInfoList_r9_utra_FDD_r9,
        k_cellInfoList_r9_utra_TDD_r9,
    };
    int cellInfoList_r9_Pack(std::vector<uint8_t> &bits);
    int cellInfoList_r9_Unpack(std::vector<uint8_t> bits);
    int cellInfoList_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    cellInfoList_r9_Enum cellInfoList_r9_Choice() const;
    int cellInfoList_r9_SetChoice(cellInfoList_r9_Enum choice);
    std::string cellInfoList_r9_ChoiceToString(cellInfoList_r9_Enum value) const;
    uint64_t cellInfoList_r9_NumberOfChoices() const;
    std::string cellInfoList_r9_ToString(uint32_t indent) const;
    std::string cellInfoList_r9_ToStringNoNewLines() const;
    int cellInfoList_r9_Clear();
    bool cellInfoList_r9_IsPresent() const;
private:
    bool cellInfoList_r9_present;
    cellInfoList_r9_Enum cellInfoList_r9_internal_choice;

    // geran-r9
public:
    CellInfoListGERAN_r9* cellInfoList_r9_geran_r9_Set();
    int cellInfoList_r9_geran_r9_Set(CellInfoListGERAN_r9 &value);
    const CellInfoListGERAN_r9& cellInfoList_r9_geran_r9_Get() const;
    std::string cellInfoList_r9_geran_r9_ToString(uint32_t indent) const;
    std::string cellInfoList_r9_geran_r9_ToStringNoNewLines() const;
    int cellInfoList_r9_geran_r9_Clear();
    bool cellInfoList_r9_geran_r9_IsPresent() const;
private:
    bool cellInfoList_r9_geran_r9_present;
    CellInfoListGERAN_r9 cellInfoList_r9_geran_r9;

    // utra-FDD-r9
public:
    CellInfoListUTRA_FDD_r9* cellInfoList_r9_utra_FDD_r9_Set();
    int cellInfoList_r9_utra_FDD_r9_Set(CellInfoListUTRA_FDD_r9 &value);
    const CellInfoListUTRA_FDD_r9& cellInfoList_r9_utra_FDD_r9_Get() const;
    std::string cellInfoList_r9_utra_FDD_r9_ToString(uint32_t indent) const;
    std::string cellInfoList_r9_utra_FDD_r9_ToStringNoNewLines() const;
    int cellInfoList_r9_utra_FDD_r9_Clear();
    bool cellInfoList_r9_utra_FDD_r9_IsPresent() const;
private:
    bool cellInfoList_r9_utra_FDD_r9_present;
    CellInfoListUTRA_FDD_r9 cellInfoList_r9_utra_FDD_r9;

    // utra-TDD-r9
public:
    CellInfoListUTRA_TDD_r9* cellInfoList_r9_utra_TDD_r9_Set();
    int cellInfoList_r9_utra_TDD_r9_Set(CellInfoListUTRA_TDD_r9 &value);
    const CellInfoListUTRA_TDD_r9& cellInfoList_r9_utra_TDD_r9_Get() const;
    std::string cellInfoList_r9_utra_TDD_r9_ToString(uint32_t indent) const;
    std::string cellInfoList_r9_utra_TDD_r9_ToStringNoNewLines() const;
    int cellInfoList_r9_utra_TDD_r9_Clear();
    bool cellInfoList_r9_utra_TDD_r9_IsPresent() const;
private:
    bool cellInfoList_r9_utra_TDD_r9_present;
    CellInfoListUTRA_TDD_r9 cellInfoList_r9_utra_TDD_r9;


    // nonCriticalExtension

};

#endif
