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

#ifndef __MDT_MeasurementInfo_r10_H__
#define __MDT_MeasurementInfo_r10_H__

#include "LocationInfo_r10.h"
#include "CellGlobalIdEUTRA.h"
#include "ARFCN_ValueEUTRA.h"
#include "RSRP_Range.h"
#include "RSRQ_Range.h"
#include "MeasResultNeighCells.h"

#include <array>
#include <cstdint>
#include <vector>

class MDT_MeasurementInfo_r10
{
public:
    MDT_MeasurementInfo_r10() : locationInfo_r10_present{false}, relativeTimeStamp_r10_present{false}, servCellIdentity_r10_present{false}, servCarrierFreq_r10_present{false}, measResultNeighCells_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // locationInfo-r10
public:
    LocationInfo_r10* locationInfo_r10_Set();
    int locationInfo_r10_Set(LocationInfo_r10 &value);
    const LocationInfo_r10& locationInfo_r10_Get() const;
    std::string locationInfo_r10_ToString(uint32_t indent) const;
    std::string locationInfo_r10_ToStringNoNewLines() const;
    int locationInfo_r10_Clear();
    bool locationInfo_r10_IsPresent() const;
private:
    bool locationInfo_r10_present;
    LocationInfo_r10 locationInfo_r10;

    // relativeTimeStamp-r10
public:
    int relativeTimeStamp_r10_Pack(std::vector<uint8_t> &bits);
    int relativeTimeStamp_r10_Unpack(std::vector<uint8_t> bits);
    int relativeTimeStamp_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t relativeTimeStamp_r10_Value() const;
    int relativeTimeStamp_r10_SetValue(int64_t value);
    std::string relativeTimeStamp_r10_ToString(uint32_t indent) const;
    std::string relativeTimeStamp_r10_ToStringNoNewLines() const;
    int relativeTimeStamp_r10_Clear();
    bool relativeTimeStamp_r10_IsPresent() const;
private:
    bool relativeTimeStamp_r10_present;
    int64_t relativeTimeStamp_r10_internal_value;

    // servCellIdentity-r10
public:
    CellGlobalIdEUTRA* servCellIdentity_r10_Set();
    int servCellIdentity_r10_Set(CellGlobalIdEUTRA &value);
    const CellGlobalIdEUTRA& servCellIdentity_r10_Get() const;
    std::string servCellIdentity_r10_ToString(uint32_t indent) const;
    std::string servCellIdentity_r10_ToStringNoNewLines() const;
    int servCellIdentity_r10_Clear();
    bool servCellIdentity_r10_IsPresent() const;
private:
    bool servCellIdentity_r10_present;
    CellGlobalIdEUTRA servCellIdentity_r10;

    // servCarrierFreq-r10
public:
    ARFCN_ValueEUTRA* servCarrierFreq_r10_Set();
    int servCarrierFreq_r10_Set(ARFCN_ValueEUTRA &value);
    const ARFCN_ValueEUTRA& servCarrierFreq_r10_Get() const;
    std::string servCarrierFreq_r10_ToString(uint32_t indent) const;
    std::string servCarrierFreq_r10_ToStringNoNewLines() const;
    int servCarrierFreq_r10_Clear();
    bool servCarrierFreq_r10_IsPresent() const;
private:
    bool servCarrierFreq_r10_present;
    ARFCN_ValueEUTRA servCarrierFreq_r10;

    // measResultServCell-r10
public:
    class measResultServCell_r10
    {
    public:
        measResultServCell_r10() : rsrpResult_r10_present{false}, rsrqResult_r10_present{false} {};
    public:
        int Pack(std::vector<uint8_t> &bits);
        int Unpack(std::vector<uint8_t> bits);
        int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        std::string ToString(uint32_t indent) const;
        std::string ToStringNoNewLines() const;

        // rsrpResult-r10
    public:
        RSRP_Range* rsrpResult_r10_Set();
        int rsrpResult_r10_Set(RSRP_Range &value);
        const RSRP_Range& rsrpResult_r10_Get() const;
        std::string rsrpResult_r10_ToString(uint32_t indent) const;
        std::string rsrpResult_r10_ToStringNoNewLines() const;
        int rsrpResult_r10_Clear();
        bool rsrpResult_r10_IsPresent() const;
    private:
        bool rsrpResult_r10_present;
        RSRP_Range rsrpResult_r10;

        // rsrqResult-r10
    public:
        RSRQ_Range* rsrqResult_r10_Set();
        int rsrqResult_r10_Set(RSRQ_Range &value);
        const RSRQ_Range& rsrqResult_r10_Get() const;
        std::string rsrqResult_r10_ToString(uint32_t indent) const;
        std::string rsrqResult_r10_ToStringNoNewLines() const;
        int rsrqResult_r10_Clear();
        bool rsrqResult_r10_IsPresent() const;
    private:
        bool rsrqResult_r10_present;
        RSRQ_Range rsrqResult_r10;

    };

    measResultServCell_r10 measResultServCell_r10_value;

    // measResultNeighCells
public:
    MeasResultNeighCells* measResultNeighCells_Set();
    int measResultNeighCells_Set(MeasResultNeighCells &value);
    const MeasResultNeighCells& measResultNeighCells_Get() const;
    std::string measResultNeighCells_ToString(uint32_t indent) const;
    std::string measResultNeighCells_ToStringNoNewLines() const;
    int measResultNeighCells_Clear();
    bool measResultNeighCells_IsPresent() const;
private:
    bool measResultNeighCells_present;
    MeasResultNeighCells measResultNeighCells;

};

#endif
