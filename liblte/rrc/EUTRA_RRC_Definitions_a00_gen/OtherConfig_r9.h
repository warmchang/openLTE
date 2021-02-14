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

#ifndef __OtherConfig_r9_H__
#define __OtherConfig_r9_H__

#include "ReportProximityConfig_r9.h"

#include <array>
#include <cstdint>
#include <vector>

class OtherConfig_r9
{
public:
    OtherConfig_r9() : reportProximityConfig_r9_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // reportProximityConfig-r9
public:
    ReportProximityConfig_r9* reportProximityConfig_r9_Set();
    int reportProximityConfig_r9_Set(ReportProximityConfig_r9 &value);
    const ReportProximityConfig_r9& reportProximityConfig_r9_Get() const;
    std::string reportProximityConfig_r9_ToString(uint32_t indent) const;
    std::string reportProximityConfig_r9_ToStringNoNewLines() const;
    int reportProximityConfig_r9_Clear();
    bool reportProximityConfig_r9_IsPresent() const;
private:
    bool reportProximityConfig_r9_present;
    ReportProximityConfig_r9 reportProximityConfig_r9;

};

#endif
