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

#ifndef __VarShortMAC_Input_H__
#define __VarShortMAC_Input_H__

#include "CellIdentity.h"
#include "PhysCellId.h"
#include "C_RNTI.h"

#include <array>
#include <cstdint>
#include <vector>

class VarShortMAC_Input
{
public:
    VarShortMAC_Input() : cellIdentity_present{false}, physCellId_present{false}, c_RNTI_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

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

    // physCellId
public:
    PhysCellId* physCellId_Set();
    int physCellId_Set(PhysCellId &value);
    const PhysCellId& physCellId_Get() const;
    std::string physCellId_ToString(uint32_t indent) const;
    std::string physCellId_ToStringNoNewLines() const;
    int physCellId_Clear();
    bool physCellId_IsPresent() const;
private:
    bool physCellId_present;
    PhysCellId physCellId;

    // c-RNTI
public:
    C_RNTI* c_RNTI_Set();
    int c_RNTI_Set(C_RNTI &value);
    const C_RNTI& c_RNTI_Get() const;
    std::string c_RNTI_ToString(uint32_t indent) const;
    std::string c_RNTI_ToStringNoNewLines() const;
    int c_RNTI_Clear();
    bool c_RNTI_IsPresent() const;
private:
    bool c_RNTI_present;
    C_RNTI c_RNTI;

};

#endif
