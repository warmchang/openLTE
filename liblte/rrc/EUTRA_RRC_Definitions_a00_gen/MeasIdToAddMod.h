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

#ifndef __MeasIdToAddMod_H__
#define __MeasIdToAddMod_H__

#include "MeasId.h"
#include "MeasObjectId.h"
#include "ReportConfigId.h"

#include <array>
#include <cstdint>
#include <vector>

class MeasIdToAddMod
{
public:
    MeasIdToAddMod() : measId_present{false}, measObjectId_present{false}, reportConfigId_present{false} {};
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

    // measObjectId
public:
    MeasObjectId* measObjectId_Set();
    int measObjectId_Set(MeasObjectId &value);
    const MeasObjectId& measObjectId_Get() const;
    std::string measObjectId_ToString(uint32_t indent) const;
    std::string measObjectId_ToStringNoNewLines() const;
    int measObjectId_Clear();
    bool measObjectId_IsPresent() const;
private:
    bool measObjectId_present;
    MeasObjectId measObjectId;

    // reportConfigId
public:
    ReportConfigId* reportConfigId_Set();
    int reportConfigId_Set(ReportConfigId &value);
    const ReportConfigId& reportConfigId_Get() const;
    std::string reportConfigId_ToString(uint32_t indent) const;
    std::string reportConfigId_ToStringNoNewLines() const;
    int reportConfigId_Clear();
    bool reportConfigId_IsPresent() const;
private:
    bool reportConfigId_present;
    ReportConfigId reportConfigId;

};

#endif
