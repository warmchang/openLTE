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

#ifndef __CandidateCellInfo_r10_H__
#define __CandidateCellInfo_r10_H__

#include "PhysCellId.h"
#include "ARFCN_ValueEUTRA.h"
#include "RSRP_Range.h"
#include "RSRQ_Range.h"

#include <array>
#include <cstdint>
#include <vector>

class CandidateCellInfo_r10
{
public:
    CandidateCellInfo_r10() : physCellId_r10_present{false}, dl_CarrierFreq_r10_present{false}, rsrpResult_r10_present{false}, rsrqResult_r10_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // physCellId-r10
public:
    PhysCellId* physCellId_r10_Set();
    int physCellId_r10_Set(PhysCellId &value);
    const PhysCellId& physCellId_r10_Get() const;
    std::string physCellId_r10_ToString(uint32_t indent) const;
    std::string physCellId_r10_ToStringNoNewLines() const;
    int physCellId_r10_Clear();
    bool physCellId_r10_IsPresent() const;
private:
    bool physCellId_r10_present;
    PhysCellId physCellId_r10;

    // dl-CarrierFreq-r10
public:
    ARFCN_ValueEUTRA* dl_CarrierFreq_r10_Set();
    int dl_CarrierFreq_r10_Set(ARFCN_ValueEUTRA &value);
    const ARFCN_ValueEUTRA& dl_CarrierFreq_r10_Get() const;
    std::string dl_CarrierFreq_r10_ToString(uint32_t indent) const;
    std::string dl_CarrierFreq_r10_ToStringNoNewLines() const;
    int dl_CarrierFreq_r10_Clear();
    bool dl_CarrierFreq_r10_IsPresent() const;
private:
    bool dl_CarrierFreq_r10_present;
    ARFCN_ValueEUTRA dl_CarrierFreq_r10;

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

#endif
