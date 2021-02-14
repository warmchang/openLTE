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

#include "HandoverPreparationInformation_r8_IEs.h"

#include <cmath>

int HandoverPreparationInformation_r8_IEs::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(as_Config_IsPresent());
    bits.push_back(rrm_Config_IsPresent());
    bits.push_back(as_Context_IsPresent());
    bits.push_back(nonCriticalExtension_IsPresent());

    // Fields
    {
        if(0 != ue_RadioAccessCapabilityInfo.Pack(bits))
        {
            printf("HandoverPreparationInformation_r8_IEs:: field pack failure\n");
            return -1;
        }
    }
    if(as_Config_IsPresent())
    {
        if(0 != as_Config.Pack(bits))
        {
            printf("HandoverPreparationInformation_r8_IEs:: field pack failure\n");
            return -1;
        }
    }
    if(rrm_Config_IsPresent())
    {
        if(0 != rrm_Config.Pack(bits))
        {
            printf("HandoverPreparationInformation_r8_IEs:: field pack failure\n");
            return -1;
        }
    }
    if(as_Context_IsPresent())
    {
        if(0 != as_Context.Pack(bits))
        {
            printf("HandoverPreparationInformation_r8_IEs:: field pack failure\n");
            return -1;
        }
    }
    if(nonCriticalExtension_IsPresent())
    {
        if(0 != nonCriticalExtension.Pack(bits))
        {
            printf("HandoverPreparationInformation_r8_IEs:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int HandoverPreparationInformation_r8_IEs::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int HandoverPreparationInformation_r8_IEs::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("HandoverPreparationInformation_r8_IEs::Unpack() index out of bounds for optional indiator as_Config\n");
        return -1;
    }
    as_Config_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("HandoverPreparationInformation_r8_IEs::Unpack() index out of bounds for optional indiator rrm_Config\n");
        return -1;
    }
    rrm_Config_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("HandoverPreparationInformation_r8_IEs::Unpack() index out of bounds for optional indiator as_Context\n");
        return -1;
    }
    as_Context_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("HandoverPreparationInformation_r8_IEs::Unpack() index out of bounds for optional indiator nonCriticalExtension\n");
        return -1;
    }
    nonCriticalExtension_present = bits[idx++];

    // Fields
    {
        if(0 != ue_RadioAccessCapabilityInfo.Unpack(bits, idx))
        {
            printf("HandoverPreparationInformation_r8_IEs:: field unpack failure\n");
            return -1;
        }
    }
    if(as_Config_present)
    {
        if(0 != as_Config.Unpack(bits, idx))
        {
            printf("HandoverPreparationInformation_r8_IEs:: field unpack failure\n");
            return -1;
        }
    }
    if(rrm_Config_present)
    {
        if(0 != rrm_Config.Unpack(bits, idx))
        {
            printf("HandoverPreparationInformation_r8_IEs:: field unpack failure\n");
            return -1;
        }
    }
    if(as_Context_present)
    {
        if(0 != as_Context.Unpack(bits, idx))
        {
            printf("HandoverPreparationInformation_r8_IEs:: field unpack failure\n");
            return -1;
        }
    }
    if(nonCriticalExtension_present)
    {
        if(0 != nonCriticalExtension.Unpack(bits, idx))
        {
            printf("HandoverPreparationInformation_r8_IEs:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string HandoverPreparationInformation_r8_IEs::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "HandoverPreparationInformation_r8_IEs:\n";
    out += ue_RadioAccessCapabilityInfo_ToString(indent+1);
    if(as_Config_IsPresent())
        out += as_Config_ToString(indent+1);
    if(rrm_Config_IsPresent())
        out += rrm_Config_ToString(indent+1);
    if(as_Context_IsPresent())
        out += as_Context_ToString(indent+1);
    if(nonCriticalExtension_IsPresent())
        out += nonCriticalExtension_ToString(indent+1);
    return out;
}

std::string HandoverPreparationInformation_r8_IEs::ToStringNoNewLines() const
{
    std::string out = "HandoverPreparationInformation_r8_IEs:";
    out += ue_RadioAccessCapabilityInfo_ToStringNoNewLines();
    if(as_Config_IsPresent())
        out += as_Config_ToStringNoNewLines();
    if(rrm_Config_IsPresent())
        out += rrm_Config_ToStringNoNewLines();
    if(as_Context_IsPresent())
        out += as_Context_ToStringNoNewLines();
    if(nonCriticalExtension_IsPresent())
        out += nonCriticalExtension_ToStringNoNewLines();
    return out;
}

UE_CapabilityRAT_ContainerList* HandoverPreparationInformation_r8_IEs::ue_RadioAccessCapabilityInfo_Set()
{
    ue_RadioAccessCapabilityInfo_present = true;
    return &ue_RadioAccessCapabilityInfo;
}

int HandoverPreparationInformation_r8_IEs::ue_RadioAccessCapabilityInfo_Set(UE_CapabilityRAT_ContainerList &value)
{
    ue_RadioAccessCapabilityInfo_present = true;
    ue_RadioAccessCapabilityInfo = value;
    return 0;
}

const UE_CapabilityRAT_ContainerList& HandoverPreparationInformation_r8_IEs::ue_RadioAccessCapabilityInfo_Get() const
{
    return ue_RadioAccessCapabilityInfo;
}

std::string HandoverPreparationInformation_r8_IEs::ue_RadioAccessCapabilityInfo_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ue_RadioAccessCapabilityInfo:\n";
    out += ue_RadioAccessCapabilityInfo.ToString(indent+1);
    return out;
}

std::string HandoverPreparationInformation_r8_IEs::ue_RadioAccessCapabilityInfo_ToStringNoNewLines() const
{
    std::string out = "ue_RadioAccessCapabilityInfo:";
    out += ue_RadioAccessCapabilityInfo.ToStringNoNewLines();
    return out;
}

int HandoverPreparationInformation_r8_IEs::ue_RadioAccessCapabilityInfo_Clear()
{
    ue_RadioAccessCapabilityInfo_present = false;
    return 0;
}

bool HandoverPreparationInformation_r8_IEs::ue_RadioAccessCapabilityInfo_IsPresent() const
{
    return ue_RadioAccessCapabilityInfo_present;
}

AS_Config* HandoverPreparationInformation_r8_IEs::as_Config_Set()
{
    as_Config_present = true;
    return &as_Config;
}

int HandoverPreparationInformation_r8_IEs::as_Config_Set(AS_Config &value)
{
    as_Config_present = true;
    as_Config = value;
    return 0;
}

const AS_Config& HandoverPreparationInformation_r8_IEs::as_Config_Get() const
{
    return as_Config;
}

std::string HandoverPreparationInformation_r8_IEs::as_Config_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "as_Config:\n";
    out += as_Config.ToString(indent+1);
    return out;
}

std::string HandoverPreparationInformation_r8_IEs::as_Config_ToStringNoNewLines() const
{
    std::string out = "as_Config:";
    out += as_Config.ToStringNoNewLines();
    return out;
}

int HandoverPreparationInformation_r8_IEs::as_Config_Clear()
{
    as_Config_present = false;
    return 0;
}

bool HandoverPreparationInformation_r8_IEs::as_Config_IsPresent() const
{
    return as_Config_present;
}

RRM_Config* HandoverPreparationInformation_r8_IEs::rrm_Config_Set()
{
    rrm_Config_present = true;
    return &rrm_Config;
}

int HandoverPreparationInformation_r8_IEs::rrm_Config_Set(RRM_Config &value)
{
    rrm_Config_present = true;
    rrm_Config = value;
    return 0;
}

const RRM_Config& HandoverPreparationInformation_r8_IEs::rrm_Config_Get() const
{
    return rrm_Config;
}

std::string HandoverPreparationInformation_r8_IEs::rrm_Config_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "rrm_Config:\n";
    out += rrm_Config.ToString(indent+1);
    return out;
}

std::string HandoverPreparationInformation_r8_IEs::rrm_Config_ToStringNoNewLines() const
{
    std::string out = "rrm_Config:";
    out += rrm_Config.ToStringNoNewLines();
    return out;
}

int HandoverPreparationInformation_r8_IEs::rrm_Config_Clear()
{
    rrm_Config_present = false;
    return 0;
}

bool HandoverPreparationInformation_r8_IEs::rrm_Config_IsPresent() const
{
    return rrm_Config_present;
}

AS_Context* HandoverPreparationInformation_r8_IEs::as_Context_Set()
{
    as_Context_present = true;
    return &as_Context;
}

int HandoverPreparationInformation_r8_IEs::as_Context_Set(AS_Context &value)
{
    as_Context_present = true;
    as_Context = value;
    return 0;
}

const AS_Context& HandoverPreparationInformation_r8_IEs::as_Context_Get() const
{
    return as_Context;
}

std::string HandoverPreparationInformation_r8_IEs::as_Context_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "as_Context:\n";
    out += as_Context.ToString(indent+1);
    return out;
}

std::string HandoverPreparationInformation_r8_IEs::as_Context_ToStringNoNewLines() const
{
    std::string out = "as_Context:";
    out += as_Context.ToStringNoNewLines();
    return out;
}

int HandoverPreparationInformation_r8_IEs::as_Context_Clear()
{
    as_Context_present = false;
    return 0;
}

bool HandoverPreparationInformation_r8_IEs::as_Context_IsPresent() const
{
    return as_Context_present;
}

HandoverPreparationInformation_v920_IEs* HandoverPreparationInformation_r8_IEs::nonCriticalExtension_Set()
{
    nonCriticalExtension_present = true;
    return &nonCriticalExtension;
}

int HandoverPreparationInformation_r8_IEs::nonCriticalExtension_Set(HandoverPreparationInformation_v920_IEs &value)
{
    nonCriticalExtension_present = true;
    nonCriticalExtension = value;
    return 0;
}

const HandoverPreparationInformation_v920_IEs& HandoverPreparationInformation_r8_IEs::nonCriticalExtension_Get() const
{
    return nonCriticalExtension;
}

std::string HandoverPreparationInformation_r8_IEs::nonCriticalExtension_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "nonCriticalExtension:\n";
    out += nonCriticalExtension.ToString(indent+1);
    return out;
}

std::string HandoverPreparationInformation_r8_IEs::nonCriticalExtension_ToStringNoNewLines() const
{
    std::string out = "nonCriticalExtension:";
    out += nonCriticalExtension.ToStringNoNewLines();
    return out;
}

int HandoverPreparationInformation_r8_IEs::nonCriticalExtension_Clear()
{
    nonCriticalExtension_present = false;
    return 0;
}

bool HandoverPreparationInformation_r8_IEs::nonCriticalExtension_IsPresent() const
{
    return nonCriticalExtension_present;
}

