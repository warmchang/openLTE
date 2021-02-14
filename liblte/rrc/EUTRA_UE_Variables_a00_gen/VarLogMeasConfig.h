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

#ifndef __VarLogMeasConfig_H__
#define __VarLogMeasConfig_H__

#include "LoggedMeasurementsConfiguration_r10.h"
#include "PLMN_Identity.h"

#include <array>
#include <cstdint>
#include <vector>

class VarLogMeasConfig
{
public:
    VarLogMeasConfig() : loggedMeasurementsConfiguration_r10_present{false}, plmn_Identity_r10_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // loggedMeasurementsConfiguration-r10
public:
    LoggedMeasurementsConfiguration_r10* loggedMeasurementsConfiguration_r10_Set();
    int loggedMeasurementsConfiguration_r10_Set(LoggedMeasurementsConfiguration_r10 &value);
    const LoggedMeasurementsConfiguration_r10& loggedMeasurementsConfiguration_r10_Get() const;
    std::string loggedMeasurementsConfiguration_r10_ToString(uint32_t indent) const;
    std::string loggedMeasurementsConfiguration_r10_ToStringNoNewLines() const;
    int loggedMeasurementsConfiguration_r10_Clear();
    bool loggedMeasurementsConfiguration_r10_IsPresent() const;
private:
    bool loggedMeasurementsConfiguration_r10_present;
    LoggedMeasurementsConfiguration_r10 loggedMeasurementsConfiguration_r10;

    // plmn-Identity-r10
public:
    PLMN_Identity* plmn_Identity_r10_Set();
    int plmn_Identity_r10_Set(PLMN_Identity &value);
    const PLMN_Identity& plmn_Identity_r10_Get() const;
    std::string plmn_Identity_r10_ToString(uint32_t indent) const;
    std::string plmn_Identity_r10_ToStringNoNewLines() const;
    int plmn_Identity_r10_Clear();
    bool plmn_Identity_r10_IsPresent() const;
private:
    bool plmn_Identity_r10_present;
    PLMN_Identity plmn_Identity_r10;

};

#endif
