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

#ifndef __PLMN_IdentityInfo_H__
#define __PLMN_IdentityInfo_H__

#include "PLMN_Identity.h"

#include <array>
#include <cstdint>
#include <vector>

class PLMN_IdentityInfo
{
public:
    PLMN_IdentityInfo() : plmn_Identity_present{false}, cellReservedForOperatorUse_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // plmn-Identity
public:
    PLMN_Identity* plmn_Identity_Set();
    int plmn_Identity_Set(PLMN_Identity &value);
    const PLMN_Identity& plmn_Identity_Get() const;
    std::string plmn_Identity_ToString(uint32_t indent) const;
    std::string plmn_Identity_ToStringNoNewLines() const;
    int plmn_Identity_Clear();
    bool plmn_Identity_IsPresent() const;
private:
    bool plmn_Identity_present;
    PLMN_Identity plmn_Identity;

    // cellReservedForOperatorUse
public:
    enum cellReservedForOperatorUse_Enum {
        k_cellReservedForOperatorUse_reserved = 0,
        k_cellReservedForOperatorUse_notReserved,
    };
    int cellReservedForOperatorUse_Pack(std::vector<uint8_t> &bits);
    int cellReservedForOperatorUse_Unpack(std::vector<uint8_t> bits);
    int cellReservedForOperatorUse_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    cellReservedForOperatorUse_Enum cellReservedForOperatorUse_Value() const;
    int cellReservedForOperatorUse_SetValue(cellReservedForOperatorUse_Enum value);
    int cellReservedForOperatorUse_SetValue(std::string value);
    std::string cellReservedForOperatorUse_ValueToString(cellReservedForOperatorUse_Enum value) const;
    uint64_t cellReservedForOperatorUse_NumberOfValues() const;
    std::string cellReservedForOperatorUse_ToString(uint32_t indent) const;
    std::string cellReservedForOperatorUse_ToStringNoNewLines() const;
    int cellReservedForOperatorUse_Clear();
    bool cellReservedForOperatorUse_IsPresent() const;
private:
    bool cellReservedForOperatorUse_present;
    cellReservedForOperatorUse_Enum cellReservedForOperatorUse_internal_value;

};

#endif
