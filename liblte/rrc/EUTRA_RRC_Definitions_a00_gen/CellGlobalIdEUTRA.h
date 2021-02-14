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

#ifndef __CellGlobalIdEUTRA_H__
#define __CellGlobalIdEUTRA_H__

#include "PLMN_Identity.h"
#include "CellIdentity.h"

#include <array>
#include <cstdint>
#include <vector>

class CellGlobalIdEUTRA
{
public:
    CellGlobalIdEUTRA() : plmn_Identity_present{false}, cellIdentity_present{false} {};
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

    // cellIdentity
public:
    CellIdentity* cellIdentity_Set();
    int cellIdentity_Set(CellIdentity &value);
    const CellIdentity& cellIdentity_Get() const;
    std::string cellIdentity_ToString(uint32_t indent) const;
    std::string cellIdentity_ToStringNoNewLines() const;
    int cellIdentity_Clear();
    bool cellIdentity_IsPresent() const;
private:
    bool cellIdentity_present;
    CellIdentity cellIdentity;

};

#endif
