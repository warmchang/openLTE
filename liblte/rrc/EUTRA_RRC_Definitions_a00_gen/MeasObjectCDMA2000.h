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

#ifndef __MeasObjectCDMA2000_H__
#define __MeasObjectCDMA2000_H__

#include "CDMA2000_Type.h"
#include "CarrierFreqCDMA2000.h"
#include "Q_OffsetRangeInterRAT.h"
#include "CellIndexList.h"
#include "CellsToAddModListCDMA2000.h"
#include "PhysCellIdCDMA2000.h"

#include <array>
#include <cstdint>
#include <vector>

class MeasObjectCDMA2000
{
public:
    MeasObjectCDMA2000() : cdma2000_Type_present{false}, carrierFreq_present{false}, searchWindowSize_present{false}, offsetFreq_present{false}, cellsToRemoveList_present{false}, cellsToAddModList_present{false}, cellForWhichToReportCGI_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // cdma2000-Type
public:
    CDMA2000_Type* cdma2000_Type_Set();
    int cdma2000_Type_Set(CDMA2000_Type &value);
    const CDMA2000_Type& cdma2000_Type_Get() const;
    std::string cdma2000_Type_ToString(uint32_t indent) const;
    std::string cdma2000_Type_ToStringNoNewLines() const;
    int cdma2000_Type_Clear();
    bool cdma2000_Type_IsPresent() const;
private:
    bool cdma2000_Type_present;
    CDMA2000_Type cdma2000_Type;

    // carrierFreq
public:
    CarrierFreqCDMA2000* carrierFreq_Set();
    int carrierFreq_Set(CarrierFreqCDMA2000 &value);
    const CarrierFreqCDMA2000& carrierFreq_Get() const;
    std::string carrierFreq_ToString(uint32_t indent) const;
    std::string carrierFreq_ToStringNoNewLines() const;
    int carrierFreq_Clear();
    bool carrierFreq_IsPresent() const;
private:
    bool carrierFreq_present;
    CarrierFreqCDMA2000 carrierFreq;

    // searchWindowSize
public:
    int searchWindowSize_Pack(std::vector<uint8_t> &bits);
    int searchWindowSize_Unpack(std::vector<uint8_t> bits);
    int searchWindowSize_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t searchWindowSize_Value() const;
    int searchWindowSize_SetValue(int64_t value);
    std::string searchWindowSize_ToString(uint32_t indent) const;
    std::string searchWindowSize_ToStringNoNewLines() const;
    int searchWindowSize_Clear();
    bool searchWindowSize_IsPresent() const;
private:
    bool searchWindowSize_present;
    int64_t searchWindowSize_internal_value;

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
    CellsToAddModListCDMA2000* cellsToAddModList_Set();
    int cellsToAddModList_Set(CellsToAddModListCDMA2000 &value);
    const CellsToAddModListCDMA2000& cellsToAddModList_Get() const;
    std::string cellsToAddModList_ToString(uint32_t indent) const;
    std::string cellsToAddModList_ToStringNoNewLines() const;
    int cellsToAddModList_Clear();
    bool cellsToAddModList_IsPresent() const;
private:
    bool cellsToAddModList_present;
    CellsToAddModListCDMA2000 cellsToAddModList;

    // cellForWhichToReportCGI
public:
    PhysCellIdCDMA2000* cellForWhichToReportCGI_Set();
    int cellForWhichToReportCGI_Set(PhysCellIdCDMA2000 &value);
    const PhysCellIdCDMA2000& cellForWhichToReportCGI_Get() const;
    std::string cellForWhichToReportCGI_ToString(uint32_t indent) const;
    std::string cellForWhichToReportCGI_ToStringNoNewLines() const;
    int cellForWhichToReportCGI_Clear();
    bool cellForWhichToReportCGI_IsPresent() const;
private:
    bool cellForWhichToReportCGI_present;
    PhysCellIdCDMA2000 cellForWhichToReportCGI;

};

#endif
