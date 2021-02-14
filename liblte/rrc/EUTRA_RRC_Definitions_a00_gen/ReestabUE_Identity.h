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

#ifndef __ReestabUE_Identity_H__
#define __ReestabUE_Identity_H__

#include "C_RNTI.h"
#include "PhysCellId.h"
#include "ShortMAC_I.h"

#include <array>
#include <cstdint>
#include <vector>

class ReestabUE_Identity
{
public:
    ReestabUE_Identity() : c_RNTI_present{false}, physCellId_present{false}, shortMAC_I_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

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

    // shortMAC-I
public:
    ShortMAC_I* shortMAC_I_Set();
    int shortMAC_I_Set(ShortMAC_I &value);
    const ShortMAC_I& shortMAC_I_Get() const;
    std::string shortMAC_I_ToString(uint32_t indent) const;
    std::string shortMAC_I_ToStringNoNewLines() const;
    int shortMAC_I_Clear();
    bool shortMAC_I_IsPresent() const;
private:
    bool shortMAC_I_present;
    ShortMAC_I shortMAC_I;

};

#endif
