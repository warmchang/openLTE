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

#include "ReestablishmentInfo.h"

#include <cmath>

int ReestablishmentInfo::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator
    bits.push_back(0);

    // Optional indicators
    bits.push_back(additionalReestabInfoList_IsPresent());

    // Fields
    {
        if(0 != sourcePhysCellId.Pack(bits))
        {
            printf("ReestablishmentInfo:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != targetCellShortMAC_I.Pack(bits))
        {
            printf("ReestablishmentInfo:: field pack failure\n");
            return -1;
        }
    }
    if(additionalReestabInfoList_IsPresent())
    {
        if(0 != additionalReestabInfoList.Pack(bits))
        {
            printf("ReestablishmentInfo:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int ReestablishmentInfo::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int ReestablishmentInfo::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("ReestablishmentInfo::Unpack() index out of bounds for extension\n");
        return -1;
    }
    idx++;

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("ReestablishmentInfo::Unpack() index out of bounds for optional indiator additionalReestabInfoList\n");
        return -1;
    }
    additionalReestabInfoList_present = bits[idx++];

    // Fields
    {
        if(0 != sourcePhysCellId.Unpack(bits, idx))
        {
            printf("ReestablishmentInfo:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != targetCellShortMAC_I.Unpack(bits, idx))
        {
            printf("ReestablishmentInfo:: field unpack failure\n");
            return -1;
        }
    }
    if(additionalReestabInfoList_present)
    {
        if(0 != additionalReestabInfoList.Unpack(bits, idx))
        {
            printf("ReestablishmentInfo:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string ReestablishmentInfo::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ReestablishmentInfo:\n";
    out += sourcePhysCellId_ToString(indent+1);
    out += targetCellShortMAC_I_ToString(indent+1);
    if(additionalReestabInfoList_IsPresent())
        out += additionalReestabInfoList_ToString(indent+1);
    return out;
}

std::string ReestablishmentInfo::ToStringNoNewLines() const
{
    std::string out = "ReestablishmentInfo:";
    out += sourcePhysCellId_ToStringNoNewLines();
    out += targetCellShortMAC_I_ToStringNoNewLines();
    if(additionalReestabInfoList_IsPresent())
        out += additionalReestabInfoList_ToStringNoNewLines();
    return out;
}

PhysCellId* ReestablishmentInfo::sourcePhysCellId_Set()
{
    sourcePhysCellId_present = true;
    return &sourcePhysCellId;
}

int ReestablishmentInfo::sourcePhysCellId_Set(PhysCellId &value)
{
    sourcePhysCellId_present = true;
    sourcePhysCellId = value;
    return 0;
}

const PhysCellId& ReestablishmentInfo::sourcePhysCellId_Get() const
{
    return sourcePhysCellId;
}

std::string ReestablishmentInfo::sourcePhysCellId_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "sourcePhysCellId:\n";
    out += sourcePhysCellId.ToString(indent+1);
    return out;
}

std::string ReestablishmentInfo::sourcePhysCellId_ToStringNoNewLines() const
{
    std::string out = "sourcePhysCellId:";
    out += sourcePhysCellId.ToStringNoNewLines();
    return out;
}

int ReestablishmentInfo::sourcePhysCellId_Clear()
{
    sourcePhysCellId_present = false;
    return 0;
}

bool ReestablishmentInfo::sourcePhysCellId_IsPresent() const
{
    return sourcePhysCellId_present;
}

ShortMAC_I* ReestablishmentInfo::targetCellShortMAC_I_Set()
{
    targetCellShortMAC_I_present = true;
    return &targetCellShortMAC_I;
}

int ReestablishmentInfo::targetCellShortMAC_I_Set(ShortMAC_I &value)
{
    targetCellShortMAC_I_present = true;
    targetCellShortMAC_I = value;
    return 0;
}

const ShortMAC_I& ReestablishmentInfo::targetCellShortMAC_I_Get() const
{
    return targetCellShortMAC_I;
}

std::string ReestablishmentInfo::targetCellShortMAC_I_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "targetCellShortMAC_I:\n";
    out += targetCellShortMAC_I.ToString(indent+1);
    return out;
}

std::string ReestablishmentInfo::targetCellShortMAC_I_ToStringNoNewLines() const
{
    std::string out = "targetCellShortMAC_I:";
    out += targetCellShortMAC_I.ToStringNoNewLines();
    return out;
}

int ReestablishmentInfo::targetCellShortMAC_I_Clear()
{
    targetCellShortMAC_I_present = false;
    return 0;
}

bool ReestablishmentInfo::targetCellShortMAC_I_IsPresent() const
{
    return targetCellShortMAC_I_present;
}

AdditionalReestabInfoList* ReestablishmentInfo::additionalReestabInfoList_Set()
{
    additionalReestabInfoList_present = true;
    return &additionalReestabInfoList;
}

int ReestablishmentInfo::additionalReestabInfoList_Set(AdditionalReestabInfoList &value)
{
    additionalReestabInfoList_present = true;
    additionalReestabInfoList = value;
    return 0;
}

const AdditionalReestabInfoList& ReestablishmentInfo::additionalReestabInfoList_Get() const
{
    return additionalReestabInfoList;
}

std::string ReestablishmentInfo::additionalReestabInfoList_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "additionalReestabInfoList:\n";
    out += additionalReestabInfoList.ToString(indent+1);
    return out;
}

std::string ReestablishmentInfo::additionalReestabInfoList_ToStringNoNewLines() const
{
    std::string out = "additionalReestabInfoList:";
    out += additionalReestabInfoList.ToStringNoNewLines();
    return out;
}

int ReestablishmentInfo::additionalReestabInfoList_Clear()
{
    additionalReestabInfoList_present = false;
    return 0;
}

bool ReestablishmentInfo::additionalReestabInfoList_IsPresent() const
{
    return additionalReestabInfoList_present;
}

