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

#ifndef __HandoverPreparationInformation_r8_IEs_H__
#define __HandoverPreparationInformation_r8_IEs_H__

#include "UE_CapabilityRAT_ContainerList.h"
#include "AS_Config.h"
#include "RRM_Config.h"
#include "AS_Context.h"
#include "HandoverPreparationInformation_v920_IEs.h"

#include <array>
#include <cstdint>
#include <vector>

class HandoverPreparationInformation_r8_IEs
{
public:
    HandoverPreparationInformation_r8_IEs() : ue_RadioAccessCapabilityInfo_present{false}, as_Config_present{false}, rrm_Config_present{false}, as_Context_present{false}, nonCriticalExtension_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // ue-RadioAccessCapabilityInfo
public:
    UE_CapabilityRAT_ContainerList* ue_RadioAccessCapabilityInfo_Set();
    int ue_RadioAccessCapabilityInfo_Set(UE_CapabilityRAT_ContainerList &value);
    const UE_CapabilityRAT_ContainerList& ue_RadioAccessCapabilityInfo_Get() const;
    std::string ue_RadioAccessCapabilityInfo_ToString(uint32_t indent) const;
    std::string ue_RadioAccessCapabilityInfo_ToStringNoNewLines() const;
    int ue_RadioAccessCapabilityInfo_Clear();
    bool ue_RadioAccessCapabilityInfo_IsPresent() const;
private:
    bool ue_RadioAccessCapabilityInfo_present;
    UE_CapabilityRAT_ContainerList ue_RadioAccessCapabilityInfo;

    // as-Config
public:
    AS_Config* as_Config_Set();
    int as_Config_Set(AS_Config &value);
    const AS_Config& as_Config_Get() const;
    std::string as_Config_ToString(uint32_t indent) const;
    std::string as_Config_ToStringNoNewLines() const;
    int as_Config_Clear();
    bool as_Config_IsPresent() const;
private:
    bool as_Config_present;
    AS_Config as_Config;

    // rrm-Config
public:
    RRM_Config* rrm_Config_Set();
    int rrm_Config_Set(RRM_Config &value);
    const RRM_Config& rrm_Config_Get() const;
    std::string rrm_Config_ToString(uint32_t indent) const;
    std::string rrm_Config_ToStringNoNewLines() const;
    int rrm_Config_Clear();
    bool rrm_Config_IsPresent() const;
private:
    bool rrm_Config_present;
    RRM_Config rrm_Config;

    // as-Context
public:
    AS_Context* as_Context_Set();
    int as_Context_Set(AS_Context &value);
    const AS_Context& as_Context_Get() const;
    std::string as_Context_ToString(uint32_t indent) const;
    std::string as_Context_ToStringNoNewLines() const;
    int as_Context_Clear();
    bool as_Context_IsPresent() const;
private:
    bool as_Context_present;
    AS_Context as_Context;

    // nonCriticalExtension
public:
    HandoverPreparationInformation_v920_IEs* nonCriticalExtension_Set();
    int nonCriticalExtension_Set(HandoverPreparationInformation_v920_IEs &value);
    const HandoverPreparationInformation_v920_IEs& nonCriticalExtension_Get() const;
    std::string nonCriticalExtension_ToString(uint32_t indent) const;
    std::string nonCriticalExtension_ToStringNoNewLines() const;
    int nonCriticalExtension_Clear();
    bool nonCriticalExtension_IsPresent() const;
private:
    bool nonCriticalExtension_present;
    HandoverPreparationInformation_v920_IEs nonCriticalExtension;

};

#endif
