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

#ifndef __UEInformationResponse_v10xy_IEs_H__
#define __UEInformationResponse_v10xy_IEs_H__

#include "LogMeasReport_r10.h"

#include <array>
#include <cstdint>
#include <vector>

class UEInformationResponse_v10xy_IEs
{
public:
    UEInformationResponse_v10xy_IEs() : logMeasReport_r10_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // logMeasReport-r10
public:
    LogMeasReport_r10* logMeasReport_r10_Set();
    int logMeasReport_r10_Set(LogMeasReport_r10 &value);
    const LogMeasReport_r10& logMeasReport_r10_Get() const;
    std::string logMeasReport_r10_ToString(uint32_t indent) const;
    std::string logMeasReport_r10_ToStringNoNewLines() const;
    int logMeasReport_r10_Clear();
    bool logMeasReport_r10_IsPresent() const;
private:
    bool logMeasReport_r10_present;
    LogMeasReport_r10 logMeasReport_r10;

    // nonCriticalExtension

};

#endif
