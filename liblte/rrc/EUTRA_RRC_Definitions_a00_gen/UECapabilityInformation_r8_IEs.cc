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

#include "UECapabilityInformation_r8_IEs.h"

#include <cmath>

int UECapabilityInformation_r8_IEs::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(nonCriticalExtension_IsPresent());

    // Fields
    {
        if(0 != ue_CapabilityRAT_ContainerList.Pack(bits))
        {
            printf("UECapabilityInformation_r8_IEs:: field pack failure\n");
            return -1;
        }
    }
    if(nonCriticalExtension_IsPresent())
    {
        if(0 != nonCriticalExtension.Pack(bits))
        {
            printf("UECapabilityInformation_r8_IEs:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int UECapabilityInformation_r8_IEs::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int UECapabilityInformation_r8_IEs::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("UECapabilityInformation_r8_IEs::Unpack() index out of bounds for optional indiator nonCriticalExtension\n");
        return -1;
    }
    nonCriticalExtension_present = bits[idx++];

    // Fields
    {
        if(0 != ue_CapabilityRAT_ContainerList.Unpack(bits, idx))
        {
            printf("UECapabilityInformation_r8_IEs:: field unpack failure\n");
            return -1;
        }
    }
    if(nonCriticalExtension_present)
    {
        if(0 != nonCriticalExtension.Unpack(bits, idx))
        {
            printf("UECapabilityInformation_r8_IEs:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string UECapabilityInformation_r8_IEs::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "UECapabilityInformation_r8_IEs:\n";
    out += ue_CapabilityRAT_ContainerList_ToString(indent+1);
    if(nonCriticalExtension_IsPresent())
        out += nonCriticalExtension_ToString(indent+1);
    return out;
}

std::string UECapabilityInformation_r8_IEs::ToStringNoNewLines() const
{
    std::string out = "UECapabilityInformation_r8_IEs:";
    out += ue_CapabilityRAT_ContainerList_ToStringNoNewLines();
    if(nonCriticalExtension_IsPresent())
        out += nonCriticalExtension_ToStringNoNewLines();
    return out;
}

UE_CapabilityRAT_ContainerList* UECapabilityInformation_r8_IEs::ue_CapabilityRAT_ContainerList_Set()
{
    ue_CapabilityRAT_ContainerList_present = true;
    return &ue_CapabilityRAT_ContainerList;
}

int UECapabilityInformation_r8_IEs::ue_CapabilityRAT_ContainerList_Set(UE_CapabilityRAT_ContainerList &value)
{
    ue_CapabilityRAT_ContainerList_present = true;
    ue_CapabilityRAT_ContainerList = value;
    return 0;
}

const UE_CapabilityRAT_ContainerList& UECapabilityInformation_r8_IEs::ue_CapabilityRAT_ContainerList_Get() const
{
    return ue_CapabilityRAT_ContainerList;
}

std::string UECapabilityInformation_r8_IEs::ue_CapabilityRAT_ContainerList_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ue_CapabilityRAT_ContainerList:\n";
    out += ue_CapabilityRAT_ContainerList.ToString(indent+1);
    return out;
}

std::string UECapabilityInformation_r8_IEs::ue_CapabilityRAT_ContainerList_ToStringNoNewLines() const
{
    std::string out = "ue_CapabilityRAT_ContainerList:";
    out += ue_CapabilityRAT_ContainerList.ToStringNoNewLines();
    return out;
}

int UECapabilityInformation_r8_IEs::ue_CapabilityRAT_ContainerList_Clear()
{
    ue_CapabilityRAT_ContainerList_present = false;
    return 0;
}

bool UECapabilityInformation_r8_IEs::ue_CapabilityRAT_ContainerList_IsPresent() const
{
    return ue_CapabilityRAT_ContainerList_present;
}

UECapabilityInformation_v8a0_IEs* UECapabilityInformation_r8_IEs::nonCriticalExtension_Set()
{
    nonCriticalExtension_present = true;
    return &nonCriticalExtension;
}

int UECapabilityInformation_r8_IEs::nonCriticalExtension_Set(UECapabilityInformation_v8a0_IEs &value)
{
    nonCriticalExtension_present = true;
    nonCriticalExtension = value;
    return 0;
}

const UECapabilityInformation_v8a0_IEs& UECapabilityInformation_r8_IEs::nonCriticalExtension_Get() const
{
    return nonCriticalExtension;
}

std::string UECapabilityInformation_r8_IEs::nonCriticalExtension_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "nonCriticalExtension:\n";
    out += nonCriticalExtension.ToString(indent+1);
    return out;
}

std::string UECapabilityInformation_r8_IEs::nonCriticalExtension_ToStringNoNewLines() const
{
    std::string out = "nonCriticalExtension:";
    out += nonCriticalExtension.ToStringNoNewLines();
    return out;
}

int UECapabilityInformation_r8_IEs::nonCriticalExtension_Clear()
{
    nonCriticalExtension_present = false;
    return 0;
}

bool UECapabilityInformation_r8_IEs::nonCriticalExtension_IsPresent() const
{
    return nonCriticalExtension_present;
}

