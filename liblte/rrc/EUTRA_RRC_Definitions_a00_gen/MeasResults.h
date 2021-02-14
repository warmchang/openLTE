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

#ifndef __MeasResults_H__
#define __MeasResults_H__

#include "MeasId.h"
#include "RSRP_Range.h"
#include "RSRQ_Range.h"
#include "MeasResultListEUTRA.h"
#include "MeasResultListUTRA.h"
#include "MeasResultListGERAN.h"
#include "MeasResultsCDMA2000.h"
#include "MeasResultForECID_r9.h"
#include "LocationInfo_r10.h"
#include "MeasResultServFreqList_r10.h"

#include <array>
#include <cstdint>
#include <vector>

class MeasResults
{
public:
    MeasResults() : measId_present{false}, measResultNeighCells_present{false}, measResultForECID_r9_present{false}, locationInfo_r10_present{false}, measResultServFreqList_r10_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // measId
public:
    MeasId* measId_Set();
    int measId_Set(MeasId &value);
    const MeasId& measId_Get() const;
    std::string measId_ToString(uint32_t indent) const;
    std::string measId_ToStringNoNewLines() const;
    int measId_Clear();
    bool measId_IsPresent() const;
private:
    bool measId_present;
    MeasId measId;

    // measResultPCell
public:
    class measResultPCell
    {
    public:
        measResultPCell() : rsrpResult_present{false}, rsrqResult_present{false} {};
    public:
        int Pack(std::vector<uint8_t> &bits);
        int Unpack(std::vector<uint8_t> bits);
        int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        std::string ToString(uint32_t indent) const;
        std::string ToStringNoNewLines() const;

        // rsrpResult
    public:
        RSRP_Range* rsrpResult_Set();
        int rsrpResult_Set(RSRP_Range &value);
        const RSRP_Range& rsrpResult_Get() const;
        std::string rsrpResult_ToString(uint32_t indent) const;
        std::string rsrpResult_ToStringNoNewLines() const;
        int rsrpResult_Clear();
        bool rsrpResult_IsPresent() const;
    private:
        bool rsrpResult_present;
        RSRP_Range rsrpResult;

        // rsrqResult
    public:
        RSRQ_Range* rsrqResult_Set();
        int rsrqResult_Set(RSRQ_Range &value);
        const RSRQ_Range& rsrqResult_Get() const;
        std::string rsrqResult_ToString(uint32_t indent) const;
        std::string rsrqResult_ToStringNoNewLines() const;
        int rsrqResult_Clear();
        bool rsrqResult_IsPresent() const;
    private:
        bool rsrqResult_present;
        RSRQ_Range rsrqResult;

    };

    measResultPCell measResultPCell_value;

    // measResultNeighCells
public:
    enum measResultNeighCells_Enum {
        k_measResultNeighCells_measResultListEUTRA = 0,
        k_measResultNeighCells_measResultListUTRA,
        k_measResultNeighCells_measResultListGERAN,
        k_measResultNeighCells_measResultsCDMA2000,
    };
    int measResultNeighCells_Pack(std::vector<uint8_t> &bits);
    int measResultNeighCells_Unpack(std::vector<uint8_t> bits);
    int measResultNeighCells_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    measResultNeighCells_Enum measResultNeighCells_Choice() const;
    int measResultNeighCells_SetChoice(measResultNeighCells_Enum choice);
    std::string measResultNeighCells_ChoiceToString(measResultNeighCells_Enum value) const;
    uint64_t measResultNeighCells_NumberOfChoices() const;
    std::string measResultNeighCells_ToString(uint32_t indent) const;
    std::string measResultNeighCells_ToStringNoNewLines() const;
    int measResultNeighCells_Clear();
    bool measResultNeighCells_IsPresent() const;
private:
    bool measResultNeighCells_present;
    measResultNeighCells_Enum measResultNeighCells_internal_choice;

    // measResultListEUTRA
public:
    MeasResultListEUTRA* measResultNeighCells_measResultListEUTRA_Set();
    int measResultNeighCells_measResultListEUTRA_Set(MeasResultListEUTRA &value);
    const MeasResultListEUTRA& measResultNeighCells_measResultListEUTRA_Get() const;
    std::string measResultNeighCells_measResultListEUTRA_ToString(uint32_t indent) const;
    std::string measResultNeighCells_measResultListEUTRA_ToStringNoNewLines() const;
    int measResultNeighCells_measResultListEUTRA_Clear();
    bool measResultNeighCells_measResultListEUTRA_IsPresent() const;
private:
    bool measResultNeighCells_measResultListEUTRA_present;
    MeasResultListEUTRA measResultNeighCells_measResultListEUTRA;

    // measResultListUTRA
public:
    MeasResultListUTRA* measResultNeighCells_measResultListUTRA_Set();
    int measResultNeighCells_measResultListUTRA_Set(MeasResultListUTRA &value);
    const MeasResultListUTRA& measResultNeighCells_measResultListUTRA_Get() const;
    std::string measResultNeighCells_measResultListUTRA_ToString(uint32_t indent) const;
    std::string measResultNeighCells_measResultListUTRA_ToStringNoNewLines() const;
    int measResultNeighCells_measResultListUTRA_Clear();
    bool measResultNeighCells_measResultListUTRA_IsPresent() const;
private:
    bool measResultNeighCells_measResultListUTRA_present;
    MeasResultListUTRA measResultNeighCells_measResultListUTRA;

    // measResultListGERAN
public:
    MeasResultListGERAN* measResultNeighCells_measResultListGERAN_Set();
    int measResultNeighCells_measResultListGERAN_Set(MeasResultListGERAN &value);
    const MeasResultListGERAN& measResultNeighCells_measResultListGERAN_Get() const;
    std::string measResultNeighCells_measResultListGERAN_ToString(uint32_t indent) const;
    std::string measResultNeighCells_measResultListGERAN_ToStringNoNewLines() const;
    int measResultNeighCells_measResultListGERAN_Clear();
    bool measResultNeighCells_measResultListGERAN_IsPresent() const;
private:
    bool measResultNeighCells_measResultListGERAN_present;
    MeasResultListGERAN measResultNeighCells_measResultListGERAN;

    // measResultsCDMA2000
public:
    MeasResultsCDMA2000* measResultNeighCells_measResultsCDMA2000_Set();
    int measResultNeighCells_measResultsCDMA2000_Set(MeasResultsCDMA2000 &value);
    const MeasResultsCDMA2000& measResultNeighCells_measResultsCDMA2000_Get() const;
    std::string measResultNeighCells_measResultsCDMA2000_ToString(uint32_t indent) const;
    std::string measResultNeighCells_measResultsCDMA2000_ToStringNoNewLines() const;
    int measResultNeighCells_measResultsCDMA2000_Clear();
    bool measResultNeighCells_measResultsCDMA2000_IsPresent() const;
private:
    bool measResultNeighCells_measResultsCDMA2000_present;
    MeasResultsCDMA2000 measResultNeighCells_measResultsCDMA2000;


    // measResultForECID-r9
public:
    MeasResultForECID_r9* measResultForECID_r9_Set();
    int measResultForECID_r9_Set(MeasResultForECID_r9 &value);
    const MeasResultForECID_r9& measResultForECID_r9_Get() const;
    std::string measResultForECID_r9_ToString(uint32_t indent) const;
    std::string measResultForECID_r9_ToStringNoNewLines() const;
    int measResultForECID_r9_Clear();
    bool measResultForECID_r9_IsPresent() const;
private:
    bool measResultForECID_r9_present;
    MeasResultForECID_r9 measResultForECID_r9;

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

    // measResultServFreqList-r10
public:
    MeasResultServFreqList_r10* measResultServFreqList_r10_Set();
    int measResultServFreqList_r10_Set(MeasResultServFreqList_r10 &value);
    const MeasResultServFreqList_r10& measResultServFreqList_r10_Get() const;
    std::string measResultServFreqList_r10_ToString(uint32_t indent) const;
    std::string measResultServFreqList_r10_ToStringNoNewLines() const;
    int measResultServFreqList_r10_Clear();
    bool measResultServFreqList_r10_IsPresent() const;
private:
    bool measResultServFreqList_r10_present;
    MeasResultServFreqList_r10 measResultServFreqList_r10;

};

#endif
