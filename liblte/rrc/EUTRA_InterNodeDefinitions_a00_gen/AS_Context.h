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

#ifndef __AS_Context_H__
#define __AS_Context_H__

#include "ReestablishmentInfo.h"

#include <array>
#include <cstdint>
#include <vector>

class AS_Context
{
public:
    AS_Context() : reestablishmentInfo_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // reestablishmentInfo
public:
    ReestablishmentInfo* reestablishmentInfo_Set();
    int reestablishmentInfo_Set(ReestablishmentInfo &value);
    const ReestablishmentInfo& reestablishmentInfo_Get() const;
    std::string reestablishmentInfo_ToString(uint32_t indent) const;
    std::string reestablishmentInfo_ToStringNoNewLines() const;
    int reestablishmentInfo_Clear();
    bool reestablishmentInfo_IsPresent() const;
private:
    bool reestablishmentInfo_present;
    ReestablishmentInfo reestablishmentInfo;

};

#endif
