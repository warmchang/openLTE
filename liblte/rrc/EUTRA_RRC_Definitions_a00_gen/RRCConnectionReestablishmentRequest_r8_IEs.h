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

#ifndef __RRCConnectionReestablishmentRequest_r8_IEs_H__
#define __RRCConnectionReestablishmentRequest_r8_IEs_H__

#include "ReestabUE_Identity.h"
#include "ReestablishmentCause.h"

#include <array>
#include <cstdint>
#include <vector>

class RRCConnectionReestablishmentRequest_r8_IEs
{
public:
    RRCConnectionReestablishmentRequest_r8_IEs() : ue_Identity_present{false}, reestablishmentCause_present{false}, spare_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // ue-Identity
public:
    ReestabUE_Identity* ue_Identity_Set();
    int ue_Identity_Set(ReestabUE_Identity &value);
    const ReestabUE_Identity& ue_Identity_Get() const;
    std::string ue_Identity_ToString(uint32_t indent) const;
    std::string ue_Identity_ToStringNoNewLines() const;
    int ue_Identity_Clear();
    bool ue_Identity_IsPresent() const;
private:
    bool ue_Identity_present;
    ReestabUE_Identity ue_Identity;

    // reestablishmentCause
public:
    ReestablishmentCause* reestablishmentCause_Set();
    int reestablishmentCause_Set(ReestablishmentCause &value);
    const ReestablishmentCause& reestablishmentCause_Get() const;
    std::string reestablishmentCause_ToString(uint32_t indent) const;
    std::string reestablishmentCause_ToStringNoNewLines() const;
    int reestablishmentCause_Clear();
    bool reestablishmentCause_IsPresent() const;
private:
    bool reestablishmentCause_present;
    ReestablishmentCause reestablishmentCause;

    // spare
public:
    int spare_Pack(std::vector<uint8_t> &bits);
    int spare_Unpack(std::vector<uint8_t> bits);
    int spare_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    uint8_t spare_Value() const;
    int spare_SetValue(uint8_t value);
    std::string spare_ToString(uint32_t indent) const;
    std::string spare_ToStringNoNewLines() const;
    int spare_Clear();
    bool spare_IsPresent() const;
private:
    bool spare_present;
    uint8_t spare_internal_value;

};

#endif
