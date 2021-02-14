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

#ifndef __SCellToAddMod_r10_H__
#define __SCellToAddMod_r10_H__

#include "SCellIndex_r10.h"
#include "PhysCellId.h"
#include "ARFCN_ValueEUTRA.h"
#include "RadioResourceConfigCommonSCell_r10.h"
#include "RadioResourceConfigDedicatedSCell_r10.h"

#include <array>
#include <cstdint>
#include <vector>

class SCellToAddMod_r10
{
public:
    SCellToAddMod_r10() : sCellIndex_r10_present{false}, radioResourceConfigCommon_r10_present{false}, radioResourceConfigDedicated_r10_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // sCellIndex-r10
public:
    SCellIndex_r10* sCellIndex_r10_Set();
    int sCellIndex_r10_Set(SCellIndex_r10 &value);
    const SCellIndex_r10& sCellIndex_r10_Get() const;
    std::string sCellIndex_r10_ToString(uint32_t indent) const;
    std::string sCellIndex_r10_ToStringNoNewLines() const;
    int sCellIndex_r10_Clear();
    bool sCellIndex_r10_IsPresent() const;
private:
    bool sCellIndex_r10_present;
    SCellIndex_r10 sCellIndex_r10;

    // cellIdentification
public:
    class cellIdentification
    {
    public:
        cellIdentification() : present{false}, physCellId_r10_present{false}, dl_CarrierFreq_present{false} {};
    public:
        int Pack(std::vector<uint8_t> &bits);
        int Unpack(std::vector<uint8_t> bits);
        int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        std::string ToString(uint32_t indent) const;
        std::string ToStringNoNewLines() const;
        int Set();
        int SetPresence(bool is_present);
        int Clear();
        bool IsPresent() const;
    private:
        bool present;

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

        // dl-CarrierFreq
    public:
        ARFCN_ValueEUTRA* dl_CarrierFreq_Set();
        int dl_CarrierFreq_Set(ARFCN_ValueEUTRA &value);
        const ARFCN_ValueEUTRA& dl_CarrierFreq_Get() const;
        std::string dl_CarrierFreq_ToString(uint32_t indent) const;
        std::string dl_CarrierFreq_ToStringNoNewLines() const;
        int dl_CarrierFreq_Clear();
        bool dl_CarrierFreq_IsPresent() const;
    private:
        bool dl_CarrierFreq_present;
        ARFCN_ValueEUTRA dl_CarrierFreq;

    };

    cellIdentification cellIdentification_value;

    // radioResourceConfigCommon-r10
public:
    RadioResourceConfigCommonSCell_r10* radioResourceConfigCommon_r10_Set();
    int radioResourceConfigCommon_r10_Set(RadioResourceConfigCommonSCell_r10 &value);
    const RadioResourceConfigCommonSCell_r10& radioResourceConfigCommon_r10_Get() const;
    std::string radioResourceConfigCommon_r10_ToString(uint32_t indent) const;
    std::string radioResourceConfigCommon_r10_ToStringNoNewLines() const;
    int radioResourceConfigCommon_r10_Clear();
    bool radioResourceConfigCommon_r10_IsPresent() const;
private:
    bool radioResourceConfigCommon_r10_present;
    RadioResourceConfigCommonSCell_r10 radioResourceConfigCommon_r10;

    // radioResourceConfigDedicated-r10
public:
    RadioResourceConfigDedicatedSCell_r10* radioResourceConfigDedicated_r10_Set();
    int radioResourceConfigDedicated_r10_Set(RadioResourceConfigDedicatedSCell_r10 &value);
    const RadioResourceConfigDedicatedSCell_r10& radioResourceConfigDedicated_r10_Get() const;
    std::string radioResourceConfigDedicated_r10_ToString(uint32_t indent) const;
    std::string radioResourceConfigDedicated_r10_ToStringNoNewLines() const;
    int radioResourceConfigDedicated_r10_Clear();
    bool radioResourceConfigDedicated_r10_IsPresent() const;
private:
    bool radioResourceConfigDedicated_r10_present;
    RadioResourceConfigDedicatedSCell_r10 radioResourceConfigDedicated_r10;

};

#endif
