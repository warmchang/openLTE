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

#ifndef __RLF_Report_r9_H__
#define __RLF_Report_r9_H__

#include "RSRP_Range.h"
#include "RSRQ_Range.h"
#include "MeasResultNeighCells.h"

#include <array>
#include <cstdint>
#include <vector>

class RLF_Report_r9
{
public:
    RLF_Report_r9() : measResultNeighCells_r9_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // measResultLastServCell-r9
public:
    class measResultLastServCell_r9
    {
    public:
        measResultLastServCell_r9() : rsrpResult_r9_present{false}, rsrqResult_r9_present{false} {};
    public:
        int Pack(std::vector<uint8_t> &bits);
        int Unpack(std::vector<uint8_t> bits);
        int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        std::string ToString(uint32_t indent) const;
        std::string ToStringNoNewLines() const;

        // rsrpResult-r9
    public:
        RSRP_Range* rsrpResult_r9_Set();
        int rsrpResult_r9_Set(RSRP_Range &value);
        const RSRP_Range& rsrpResult_r9_Get() const;
        std::string rsrpResult_r9_ToString(uint32_t indent) const;
        std::string rsrpResult_r9_ToStringNoNewLines() const;
        int rsrpResult_r9_Clear();
        bool rsrpResult_r9_IsPresent() const;
    private:
        bool rsrpResult_r9_present;
        RSRP_Range rsrpResult_r9;

        // rsrqResult-r9
    public:
        RSRQ_Range* rsrqResult_r9_Set();
        int rsrqResult_r9_Set(RSRQ_Range &value);
        const RSRQ_Range& rsrqResult_r9_Get() const;
        std::string rsrqResult_r9_ToString(uint32_t indent) const;
        std::string rsrqResult_r9_ToStringNoNewLines() const;
        int rsrqResult_r9_Clear();
        bool rsrqResult_r9_IsPresent() const;
    private:
        bool rsrqResult_r9_present;
        RSRQ_Range rsrqResult_r9;

    };

    measResultLastServCell_r9 measResultLastServCell_r9_value;

    // measResultNeighCells-r9
public:
    MeasResultNeighCells* measResultNeighCells_r9_Set();
    int measResultNeighCells_r9_Set(MeasResultNeighCells &value);
    const MeasResultNeighCells& measResultNeighCells_r9_Get() const;
    std::string measResultNeighCells_r9_ToString(uint32_t indent) const;
    std::string measResultNeighCells_r9_ToStringNoNewLines() const;
    int measResultNeighCells_r9_Clear();
    bool measResultNeighCells_r9_IsPresent() const;
private:
    bool measResultNeighCells_r9_present;
    MeasResultNeighCells measResultNeighCells_r9;

};

#endif
