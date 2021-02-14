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

#ifndef __PhysCellIdRangeUTRA_FDD_r9_H__
#define __PhysCellIdRangeUTRA_FDD_r9_H__

#include "PhysCellIdUTRA_FDD.h"

#include <array>
#include <cstdint>
#include <vector>

class PhysCellIdRangeUTRA_FDD_r9
{
public:
    PhysCellIdRangeUTRA_FDD_r9() : start_r9_present{false}, range_r9_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // start-r9
public:
    PhysCellIdUTRA_FDD* start_r9_Set();
    int start_r9_Set(PhysCellIdUTRA_FDD &value);
    const PhysCellIdUTRA_FDD& start_r9_Get() const;
    std::string start_r9_ToString(uint32_t indent) const;
    std::string start_r9_ToStringNoNewLines() const;
    int start_r9_Clear();
    bool start_r9_IsPresent() const;
private:
    bool start_r9_present;
    PhysCellIdUTRA_FDD start_r9;

    // range-r9
public:
    int range_r9_Pack(std::vector<uint8_t> &bits);
    int range_r9_Unpack(std::vector<uint8_t> bits);
    int range_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t range_r9_Value() const;
    int range_r9_SetValue(int64_t value);
    std::string range_r9_ToString(uint32_t indent) const;
    std::string range_r9_ToStringNoNewLines() const;
    int range_r9_Clear();
    bool range_r9_IsPresent() const;
private:
    bool range_r9_present;
    int64_t range_r9_internal_value;

};

#endif
