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

#ifndef __CellGlobalIdGERAN_H__
#define __CellGlobalIdGERAN_H__

#include "PLMN_Identity.h"

#include <array>
#include <cstdint>
#include <vector>

class CellGlobalIdGERAN
{
public:
    CellGlobalIdGERAN() : plmn_Identity_present{false}, locationAreaCode_present{false}, cellIdentity_present{false} {};
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

    // locationAreaCode
public:
    int locationAreaCode_Pack(std::vector<uint8_t> &bits);
    int locationAreaCode_Unpack(std::vector<uint8_t> bits);
    int locationAreaCode_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    uint16_t locationAreaCode_Value() const;
    int locationAreaCode_SetValue(uint16_t value);
    std::string locationAreaCode_ToString(uint32_t indent) const;
    std::string locationAreaCode_ToStringNoNewLines() const;
    int locationAreaCode_Clear();
    bool locationAreaCode_IsPresent() const;
private:
    bool locationAreaCode_present;
    uint16_t locationAreaCode_internal_value;

    // cellIdentity
public:
    int cellIdentity_Pack(std::vector<uint8_t> &bits);
    int cellIdentity_Unpack(std::vector<uint8_t> bits);
    int cellIdentity_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    uint16_t cellIdentity_Value() const;
    int cellIdentity_SetValue(uint16_t value);
    std::string cellIdentity_ToString(uint32_t indent) const;
    std::string cellIdentity_ToStringNoNewLines() const;
    int cellIdentity_Clear();
    bool cellIdentity_IsPresent() const;
private:
    bool cellIdentity_present;
    uint16_t cellIdentity_internal_value;

};

#endif
