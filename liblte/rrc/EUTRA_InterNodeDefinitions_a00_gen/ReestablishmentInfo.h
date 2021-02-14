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

#ifndef __ReestablishmentInfo_H__
#define __ReestablishmentInfo_H__

#include "PhysCellId.h"
#include "ShortMAC_I.h"
#include "AdditionalReestabInfoList.h"

#include <array>
#include <cstdint>
#include <vector>

class ReestablishmentInfo
{
public:
    ReestablishmentInfo() : sourcePhysCellId_present{false}, targetCellShortMAC_I_present{false}, additionalReestabInfoList_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // sourcePhysCellId
public:
    PhysCellId* sourcePhysCellId_Set();
    int sourcePhysCellId_Set(PhysCellId &value);
    const PhysCellId& sourcePhysCellId_Get() const;
    std::string sourcePhysCellId_ToString(uint32_t indent) const;
    std::string sourcePhysCellId_ToStringNoNewLines() const;
    int sourcePhysCellId_Clear();
    bool sourcePhysCellId_IsPresent() const;
private:
    bool sourcePhysCellId_present;
    PhysCellId sourcePhysCellId;

    // targetCellShortMAC-I
public:
    ShortMAC_I* targetCellShortMAC_I_Set();
    int targetCellShortMAC_I_Set(ShortMAC_I &value);
    const ShortMAC_I& targetCellShortMAC_I_Get() const;
    std::string targetCellShortMAC_I_ToString(uint32_t indent) const;
    std::string targetCellShortMAC_I_ToStringNoNewLines() const;
    int targetCellShortMAC_I_Clear();
    bool targetCellShortMAC_I_IsPresent() const;
private:
    bool targetCellShortMAC_I_present;
    ShortMAC_I targetCellShortMAC_I;

    // additionalReestabInfoList
public:
    AdditionalReestabInfoList* additionalReestabInfoList_Set();
    int additionalReestabInfoList_Set(AdditionalReestabInfoList &value);
    const AdditionalReestabInfoList& additionalReestabInfoList_Get() const;
    std::string additionalReestabInfoList_ToString(uint32_t indent) const;
    std::string additionalReestabInfoList_ToStringNoNewLines() const;
    int additionalReestabInfoList_Clear();
    bool additionalReestabInfoList_IsPresent() const;
private:
    bool additionalReestabInfoList_present;
    AdditionalReestabInfoList additionalReestabInfoList;

};

#endif
