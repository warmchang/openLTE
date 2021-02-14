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

#ifndef __UECapabilityInformation_r8_IEs_H__
#define __UECapabilityInformation_r8_IEs_H__

#include "UE_CapabilityRAT_ContainerList.h"
#include "UECapabilityInformation_v8a0_IEs.h"

#include <array>
#include <cstdint>
#include <vector>

class UECapabilityInformation_r8_IEs
{
public:
    UECapabilityInformation_r8_IEs() : ue_CapabilityRAT_ContainerList_present{false}, nonCriticalExtension_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // ue-CapabilityRAT-ContainerList
public:
    UE_CapabilityRAT_ContainerList* ue_CapabilityRAT_ContainerList_Set();
    int ue_CapabilityRAT_ContainerList_Set(UE_CapabilityRAT_ContainerList &value);
    const UE_CapabilityRAT_ContainerList& ue_CapabilityRAT_ContainerList_Get() const;
    std::string ue_CapabilityRAT_ContainerList_ToString(uint32_t indent) const;
    std::string ue_CapabilityRAT_ContainerList_ToStringNoNewLines() const;
    int ue_CapabilityRAT_ContainerList_Clear();
    bool ue_CapabilityRAT_ContainerList_IsPresent() const;
private:
    bool ue_CapabilityRAT_ContainerList_present;
    UE_CapabilityRAT_ContainerList ue_CapabilityRAT_ContainerList;

    // nonCriticalExtension
public:
    UECapabilityInformation_v8a0_IEs* nonCriticalExtension_Set();
    int nonCriticalExtension_Set(UECapabilityInformation_v8a0_IEs &value);
    const UECapabilityInformation_v8a0_IEs& nonCriticalExtension_Get() const;
    std::string nonCriticalExtension_ToString(uint32_t indent) const;
    std::string nonCriticalExtension_ToStringNoNewLines() const;
    int nonCriticalExtension_Clear();
    bool nonCriticalExtension_IsPresent() const;
private:
    bool nonCriticalExtension_present;
    UECapabilityInformation_v8a0_IEs nonCriticalExtension;

};

#endif
