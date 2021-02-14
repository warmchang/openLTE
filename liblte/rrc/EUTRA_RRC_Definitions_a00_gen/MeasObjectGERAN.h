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

#ifndef __MeasObjectGERAN_H__
#define __MeasObjectGERAN_H__

#include "CarrierFreqsGERAN.h"
#include "Q_OffsetRangeInterRAT.h"
#include "PhysCellIdGERAN.h"

#include <array>
#include <cstdint>
#include <vector>

class MeasObjectGERAN
{
public:
    MeasObjectGERAN() : carrierFreqs_present{false}, offsetFreq_present{false}, ncc_Permitted_present{false}, cellForWhichToReportCGI_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // carrierFreqs
public:
    CarrierFreqsGERAN* carrierFreqs_Set();
    int carrierFreqs_Set(CarrierFreqsGERAN &value);
    const CarrierFreqsGERAN& carrierFreqs_Get() const;
    std::string carrierFreqs_ToString(uint32_t indent) const;
    std::string carrierFreqs_ToStringNoNewLines() const;
    int carrierFreqs_Clear();
    bool carrierFreqs_IsPresent() const;
private:
    bool carrierFreqs_present;
    CarrierFreqsGERAN carrierFreqs;

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

    // ncc-Permitted
public:
    int ncc_Permitted_Pack(std::vector<uint8_t> &bits);
    int ncc_Permitted_Unpack(std::vector<uint8_t> bits);
    int ncc_Permitted_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    uint8_t ncc_Permitted_Value() const;
    int ncc_Permitted_SetValue(uint8_t value);
    uint8_t ncc_Permitted_GetDefault() const;
    std::string ncc_Permitted_ToString(uint32_t indent) const;
    std::string ncc_Permitted_ToStringNoNewLines() const;
    int ncc_Permitted_Clear();
    bool ncc_Permitted_IsPresent() const;
private:
    bool ncc_Permitted_present;
    uint8_t ncc_Permitted_internal_value;

    // cellForWhichToReportCGI
public:
    PhysCellIdGERAN* cellForWhichToReportCGI_Set();
    int cellForWhichToReportCGI_Set(PhysCellIdGERAN &value);
    const PhysCellIdGERAN& cellForWhichToReportCGI_Get() const;
    std::string cellForWhichToReportCGI_ToString(uint32_t indent) const;
    std::string cellForWhichToReportCGI_ToStringNoNewLines() const;
    int cellForWhichToReportCGI_Clear();
    bool cellForWhichToReportCGI_IsPresent() const;
private:
    bool cellForWhichToReportCGI_present;
    PhysCellIdGERAN cellForWhichToReportCGI;

};

#endif
