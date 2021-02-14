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

#ifndef __MeasObjectUTRA_H__
#define __MeasObjectUTRA_H__

#include "ARFCN_ValueUTRA.h"
#include "Q_OffsetRangeInterRAT.h"
#include "CellIndexList.h"
#include "CellsToAddModListUTRA_FDD.h"
#include "CellsToAddModListUTRA_TDD.h"
#include "PhysCellIdUTRA_FDD.h"
#include "PhysCellIdUTRA_TDD.h"
#include "CSG_AllowedReportingCells_r9.h"

#include <array>
#include <cstdint>
#include <vector>

class MeasObjectUTRA
{
public:
    MeasObjectUTRA() : carrierFreq_present{false}, offsetFreq_present{false}, cellsToRemoveList_present{false}, cellsToAddModList_present{false}, cellForWhichToReportCGI_present{false}, csg_allowedReportingCells_v930_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // carrierFreq
public:
    ARFCN_ValueUTRA* carrierFreq_Set();
    int carrierFreq_Set(ARFCN_ValueUTRA &value);
    const ARFCN_ValueUTRA& carrierFreq_Get() const;
    std::string carrierFreq_ToString(uint32_t indent) const;
    std::string carrierFreq_ToStringNoNewLines() const;
    int carrierFreq_Clear();
    bool carrierFreq_IsPresent() const;
private:
    bool carrierFreq_present;
    ARFCN_ValueUTRA carrierFreq;

    // offsetFreq
public:
    Q_OffsetRangeInterRAT* offsetFreq_Set();
    int offsetFreq_Set(Q_OffsetRangeInterRAT &value);
    const Q_OffsetRangeInterRAT& offsetFreq_Get() const;
    int64_t offsetFreq_GetDefault() const;
    std::string offsetFreq_ToString(uint32_t indent) const;
    std::string offsetFreq_ToStringNoNewLines() const;
    int offsetFreq_Clear();
    bool offsetFreq_IsPresent() const;
private:
    bool offsetFreq_present;
    Q_OffsetRangeInterRAT offsetFreq;

    // cellsToRemoveList
public:
    CellIndexList* cellsToRemoveList_Set();
    int cellsToRemoveList_Set(CellIndexList &value);
    const CellIndexList& cellsToRemoveList_Get() const;
    std::string cellsToRemoveList_ToString(uint32_t indent) const;
    std::string cellsToRemoveList_ToStringNoNewLines() const;
    int cellsToRemoveList_Clear();
    bool cellsToRemoveList_IsPresent() const;
private:
    bool cellsToRemoveList_present;
    CellIndexList cellsToRemoveList;

    // cellsToAddModList
public:
    enum cellsToAddModList_Enum {
        k_cellsToAddModList_cellsToAddModListUTRA_FDD = 0,
        k_cellsToAddModList_cellsToAddModListUTRA_TDD,
    };
    int cellsToAddModList_Pack(std::vector<uint8_t> &bits);
    int cellsToAddModList_Unpack(std::vector<uint8_t> bits);
    int cellsToAddModList_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    cellsToAddModList_Enum cellsToAddModList_Choice() const;
    int cellsToAddModList_SetChoice(cellsToAddModList_Enum choice);
    std::string cellsToAddModList_ChoiceToString(cellsToAddModList_Enum value) const;
    uint64_t cellsToAddModList_NumberOfChoices() const;
    std::string cellsToAddModList_ToString(uint32_t indent) const;
    std::string cellsToAddModList_ToStringNoNewLines() const;
    int cellsToAddModList_Clear();
    bool cellsToAddModList_IsPresent() const;
private:
    bool cellsToAddModList_present;
    cellsToAddModList_Enum cellsToAddModList_internal_choice;

    // cellsToAddModListUTRA-FDD
public:
    CellsToAddModListUTRA_FDD* cellsToAddModList_cellsToAddModListUTRA_FDD_Set();
    int cellsToAddModList_cellsToAddModListUTRA_FDD_Set(CellsToAddModListUTRA_FDD &value);
    const CellsToAddModListUTRA_FDD& cellsToAddModList_cellsToAddModListUTRA_FDD_Get() const;
    std::string cellsToAddModList_cellsToAddModListUTRA_FDD_ToString(uint32_t indent) const;
    std::string cellsToAddModList_cellsToAddModListUTRA_FDD_ToStringNoNewLines() const;
    int cellsToAddModList_cellsToAddModListUTRA_FDD_Clear();
    bool cellsToAddModList_cellsToAddModListUTRA_FDD_IsPresent() const;
private:
    bool cellsToAddModList_cellsToAddModListUTRA_FDD_present;
    CellsToAddModListUTRA_FDD cellsToAddModList_cellsToAddModListUTRA_FDD;

    // cellsToAddModListUTRA-TDD
public:
    CellsToAddModListUTRA_TDD* cellsToAddModList_cellsToAddModListUTRA_TDD_Set();
    int cellsToAddModList_cellsToAddModListUTRA_TDD_Set(CellsToAddModListUTRA_TDD &value);
    const CellsToAddModListUTRA_TDD& cellsToAddModList_cellsToAddModListUTRA_TDD_Get() const;
    std::string cellsToAddModList_cellsToAddModListUTRA_TDD_ToString(uint32_t indent) const;
    std::string cellsToAddModList_cellsToAddModListUTRA_TDD_ToStringNoNewLines() const;
    int cellsToAddModList_cellsToAddModListUTRA_TDD_Clear();
    bool cellsToAddModList_cellsToAddModListUTRA_TDD_IsPresent() const;
private:
    bool cellsToAddModList_cellsToAddModListUTRA_TDD_present;
    CellsToAddModListUTRA_TDD cellsToAddModList_cellsToAddModListUTRA_TDD;


    // cellForWhichToReportCGI
public:
    enum cellForWhichToReportCGI_Enum {
        k_cellForWhichToReportCGI_utra_FDD = 0,
        k_cellForWhichToReportCGI_utra_TDD,
    };
    int cellForWhichToReportCGI_Pack(std::vector<uint8_t> &bits);
    int cellForWhichToReportCGI_Unpack(std::vector<uint8_t> bits);
    int cellForWhichToReportCGI_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    cellForWhichToReportCGI_Enum cellForWhichToReportCGI_Choice() const;
    int cellForWhichToReportCGI_SetChoice(cellForWhichToReportCGI_Enum choice);
    std::string cellForWhichToReportCGI_ChoiceToString(cellForWhichToReportCGI_Enum value) const;
    uint64_t cellForWhichToReportCGI_NumberOfChoices() const;
    std::string cellForWhichToReportCGI_ToString(uint32_t indent) const;
    std::string cellForWhichToReportCGI_ToStringNoNewLines() const;
    int cellForWhichToReportCGI_Clear();
    bool cellForWhichToReportCGI_IsPresent() const;
private:
    bool cellForWhichToReportCGI_present;
    cellForWhichToReportCGI_Enum cellForWhichToReportCGI_internal_choice;

    // utra-FDD
public:
    PhysCellIdUTRA_FDD* cellForWhichToReportCGI_utra_FDD_Set();
    int cellForWhichToReportCGI_utra_FDD_Set(PhysCellIdUTRA_FDD &value);
    const PhysCellIdUTRA_FDD& cellForWhichToReportCGI_utra_FDD_Get() const;
    std::string cellForWhichToReportCGI_utra_FDD_ToString(uint32_t indent) const;
    std::string cellForWhichToReportCGI_utra_FDD_ToStringNoNewLines() const;
    int cellForWhichToReportCGI_utra_FDD_Clear();
    bool cellForWhichToReportCGI_utra_FDD_IsPresent() const;
private:
    bool cellForWhichToReportCGI_utra_FDD_present;
    PhysCellIdUTRA_FDD cellForWhichToReportCGI_utra_FDD;

    // utra-TDD
public:
    PhysCellIdUTRA_TDD* cellForWhichToReportCGI_utra_TDD_Set();
    int cellForWhichToReportCGI_utra_TDD_Set(PhysCellIdUTRA_TDD &value);
    const PhysCellIdUTRA_TDD& cellForWhichToReportCGI_utra_TDD_Get() const;
    std::string cellForWhichToReportCGI_utra_TDD_ToString(uint32_t indent) const;
    std::string cellForWhichToReportCGI_utra_TDD_ToStringNoNewLines() const;
    int cellForWhichToReportCGI_utra_TDD_Clear();
    bool cellForWhichToReportCGI_utra_TDD_IsPresent() const;
private:
    bool cellForWhichToReportCGI_utra_TDD_present;
    PhysCellIdUTRA_TDD cellForWhichToReportCGI_utra_TDD;


    // csg-allowedReportingCells-v930
public:
    CSG_AllowedReportingCells_r9* csg_allowedReportingCells_v930_Set();
    int csg_allowedReportingCells_v930_Set(CSG_AllowedReportingCells_r9 &value);
    const CSG_AllowedReportingCells_r9& csg_allowedReportingCells_v930_Get() const;
    std::string csg_allowedReportingCells_v930_ToString(uint32_t indent) const;
    std::string csg_allowedReportingCells_v930_ToStringNoNewLines() const;
    int csg_allowedReportingCells_v930_Clear();
    bool csg_allowedReportingCells_v930_IsPresent() const;
private:
    bool csg_allowedReportingCells_v930_present;
    CSG_AllowedReportingCells_r9 csg_allowedReportingCells_v930;

};

#endif
