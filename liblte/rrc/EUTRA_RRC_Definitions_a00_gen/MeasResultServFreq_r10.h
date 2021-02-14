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

#ifndef __MeasResultServFreq_r10_H__
#define __MeasResultServFreq_r10_H__

#include "ServCellIndex_r10.h"
#include "RSRP_Range.h"
#include "RSRQ_Range.h"
#include "PhysCellId.h"
#include "RSRP_Range.h"
#include "RSRQ_Range.h"

#include <array>
#include <cstdint>
#include <vector>

class MeasResultServFreq_r10
{
public:
    MeasResultServFreq_r10() : servFreqId_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // servFreqId
public:
    ServCellIndex_r10* servFreqId_Set();
    int servFreqId_Set(ServCellIndex_r10 &value);
    const ServCellIndex_r10& servFreqId_Get() const;
    std::string servFreqId_ToString(uint32_t indent) const;
    std::string servFreqId_ToStringNoNewLines() const;
    int servFreqId_Clear();
    bool servFreqId_IsPresent() const;
private:
    bool servFreqId_present;
    ServCellIndex_r10 servFreqId;

    // measResultSCell
public:
    class measResultSCell
    {
    public:
        measResultSCell() : present{false}, rsrpResultSCell_present{false}, rsrqResultSCell_present{false} {};
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

        // rsrpResultSCell
    public:
        RSRP_Range* rsrpResultSCell_Set();
        int rsrpResultSCell_Set(RSRP_Range &value);
        const RSRP_Range& rsrpResultSCell_Get() const;
        std::string rsrpResultSCell_ToString(uint32_t indent) const;
        std::string rsrpResultSCell_ToStringNoNewLines() const;
        int rsrpResultSCell_Clear();
        bool rsrpResultSCell_IsPresent() const;
    private:
        bool rsrpResultSCell_present;
        RSRP_Range rsrpResultSCell;

        // rsrqResultSCell
    public:
        RSRQ_Range* rsrqResultSCell_Set();
        int rsrqResultSCell_Set(RSRQ_Range &value);
        const RSRQ_Range& rsrqResultSCell_Get() const;
        std::string rsrqResultSCell_ToString(uint32_t indent) const;
        std::string rsrqResultSCell_ToStringNoNewLines() const;
        int rsrqResultSCell_Clear();
        bool rsrqResultSCell_IsPresent() const;
    private:
        bool rsrqResultSCell_present;
        RSRQ_Range rsrqResultSCell;

    };

    measResultSCell measResultSCell_value;

    // measResultBestNeighCell
public:
    class measResultBestNeighCell
    {
    public:
        measResultBestNeighCell() : present{false}, physCellId_present{false}, rsrpResultNCell_present{false}, rsrqResultNCell_present{false} {};
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

        // physCellId
    public:
        PhysCellId* physCellId_Set();
        int physCellId_Set(PhysCellId &value);
        const PhysCellId& physCellId_Get() const;
        std::string physCellId_ToString(uint32_t indent) const;
        std::string physCellId_ToStringNoNewLines() const;
        int physCellId_Clear();
        bool physCellId_IsPresent() const;
    private:
        bool physCellId_present;
        PhysCellId physCellId;

        // rsrpResultNCell
    public:
        RSRP_Range* rsrpResultNCell_Set();
        int rsrpResultNCell_Set(RSRP_Range &value);
        const RSRP_Range& rsrpResultNCell_Get() const;
        std::string rsrpResultNCell_ToString(uint32_t indent) const;
        std::string rsrpResultNCell_ToStringNoNewLines() const;
        int rsrpResultNCell_Clear();
        bool rsrpResultNCell_IsPresent() const;
    private:
        bool rsrpResultNCell_present;
        RSRP_Range rsrpResultNCell;

        // rsrqResultNCell
    public:
        RSRQ_Range* rsrqResultNCell_Set();
        int rsrqResultNCell_Set(RSRQ_Range &value);
        const RSRQ_Range& rsrqResultNCell_Get() const;
        std::string rsrqResultNCell_ToString(uint32_t indent) const;
        std::string rsrqResultNCell_ToStringNoNewLines() const;
        int rsrqResultNCell_Clear();
        bool rsrqResultNCell_IsPresent() const;
    private:
        bool rsrqResultNCell_present;
        RSRQ_Range rsrqResultNCell;

    };

    measResultBestNeighCell measResultBestNeighCell_value;

};

#endif
