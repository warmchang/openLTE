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

#ifndef __RRCConnectionReestablishmentComplete_v920_IEs_H__
#define __RRCConnectionReestablishmentComplete_v920_IEs_H__

#include "RRCConnectionReestablishmentComplete_v8a0_IEs.h"

#include <array>
#include <cstdint>
#include <vector>

class RRCConnectionReestablishmentComplete_v920_IEs
{
public:
    RRCConnectionReestablishmentComplete_v920_IEs() : rlf_InfoAvailable_r9_present{false}, nonCriticalExtension_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // rlf-InfoAvailable-r9
public:
    enum rlf_InfoAvailable_r9_Enum {
        k_rlf_InfoAvailable_r9_true = 0,
    };
    int rlf_InfoAvailable_r9_Pack(std::vector<uint8_t> &bits);
    int rlf_InfoAvailable_r9_Unpack(std::vector<uint8_t> bits);
    int rlf_InfoAvailable_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    rlf_InfoAvailable_r9_Enum rlf_InfoAvailable_r9_Value() const;
    int rlf_InfoAvailable_r9_SetValue(rlf_InfoAvailable_r9_Enum value);
    int rlf_InfoAvailable_r9_SetValue(std::string value);
    std::string rlf_InfoAvailable_r9_ValueToString(rlf_InfoAvailable_r9_Enum value) const;
    uint64_t rlf_InfoAvailable_r9_NumberOfValues() const;
    std::string rlf_InfoAvailable_r9_ToString(uint32_t indent) const;
    std::string rlf_InfoAvailable_r9_ToStringNoNewLines() const;
    int rlf_InfoAvailable_r9_Clear();
    bool rlf_InfoAvailable_r9_IsPresent() const;
private:
    bool rlf_InfoAvailable_r9_present;
    rlf_InfoAvailable_r9_Enum rlf_InfoAvailable_r9_internal_value;

    // nonCriticalExtension
public:
    RRCConnectionReestablishmentComplete_v8a0_IEs* nonCriticalExtension_Set();
    int nonCriticalExtension_Set(RRCConnectionReestablishmentComplete_v8a0_IEs &value);
    const RRCConnectionReestablishmentComplete_v8a0_IEs& nonCriticalExtension_Get() const;
    std::string nonCriticalExtension_ToString(uint32_t indent) const;
    std::string nonCriticalExtension_ToStringNoNewLines() const;
    int nonCriticalExtension_Clear();
    bool nonCriticalExtension_IsPresent() const;
private:
    bool nonCriticalExtension_present;
    RRCConnectionReestablishmentComplete_v8a0_IEs nonCriticalExtension;

};

#endif
