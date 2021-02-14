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

#ifndef __PRACH_ConfigSIB_H__
#define __PRACH_ConfigSIB_H__

#include "PRACH_ConfigInfo.h"

#include <array>
#include <cstdint>
#include <vector>

class PRACH_ConfigSIB
{
public:
    PRACH_ConfigSIB() : rootSequenceIndex_present{false}, prach_ConfigInfo_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // rootSequenceIndex
public:
    int rootSequenceIndex_Pack(std::vector<uint8_t> &bits);
    int rootSequenceIndex_Unpack(std::vector<uint8_t> bits);
    int rootSequenceIndex_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t rootSequenceIndex_Value() const;
    int rootSequenceIndex_SetValue(int64_t value);
    std::string rootSequenceIndex_ToString(uint32_t indent) const;
    std::string rootSequenceIndex_ToStringNoNewLines() const;
    int rootSequenceIndex_Clear();
    bool rootSequenceIndex_IsPresent() const;
private:
    bool rootSequenceIndex_present;
    int64_t rootSequenceIndex_internal_value;

    // prach-ConfigInfo
public:
    PRACH_ConfigInfo* prach_ConfigInfo_Set();
    int prach_ConfigInfo_Set(PRACH_ConfigInfo &value);
    const PRACH_ConfigInfo& prach_ConfigInfo_Get() const;
    std::string prach_ConfigInfo_ToString(uint32_t indent) const;
    std::string prach_ConfigInfo_ToStringNoNewLines() const;
    int prach_ConfigInfo_Clear();
    bool prach_ConfigInfo_IsPresent() const;
private:
    bool prach_ConfigInfo_present;
    PRACH_ConfigInfo prach_ConfigInfo;

};

#endif
