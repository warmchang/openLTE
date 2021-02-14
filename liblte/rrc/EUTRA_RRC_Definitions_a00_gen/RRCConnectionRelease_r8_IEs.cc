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

#include "RRCConnectionRelease_r8_IEs.h"

#include <cmath>

int RRCConnectionRelease_r8_IEs::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(redirectedCarrierInfo_IsPresent());
    bits.push_back(idleModeMobilityControlInfo_IsPresent());
    bits.push_back(nonCriticalExtension_IsPresent());

    // Fields
    {
        if(0 != releaseCause.Pack(bits))
        {
            printf("RRCConnectionRelease_r8_IEs:: field pack failure\n");
            return -1;
        }
    }
    if(redirectedCarrierInfo_IsPresent())
    {
        if(0 != redirectedCarrierInfo.Pack(bits))
        {
            printf("RRCConnectionRelease_r8_IEs:: field pack failure\n");
            return -1;
        }
    }
    if(idleModeMobilityControlInfo_IsPresent())
    {
        if(0 != idleModeMobilityControlInfo.Pack(bits))
        {
            printf("RRCConnectionRelease_r8_IEs:: field pack failure\n");
            return -1;
        }
    }
    if(nonCriticalExtension_IsPresent())
    {
        if(0 != nonCriticalExtension.Pack(bits))
        {
            printf("RRCConnectionRelease_r8_IEs:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int RRCConnectionRelease_r8_IEs::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int RRCConnectionRelease_r8_IEs::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("RRCConnectionRelease_r8_IEs::Unpack() index out of bounds for optional indiator redirectedCarrierInfo\n");
        return -1;
    }
    redirectedCarrierInfo_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("RRCConnectionRelease_r8_IEs::Unpack() index out of bounds for optional indiator idleModeMobilityControlInfo\n");
        return -1;
    }
    idleModeMobilityControlInfo_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("RRCConnectionRelease_r8_IEs::Unpack() index out of bounds for optional indiator nonCriticalExtension\n");
        return -1;
    }
    nonCriticalExtension_present = bits[idx++];

    // Fields
    {
        if(0 != releaseCause.Unpack(bits, idx))
        {
            printf("RRCConnectionRelease_r8_IEs:: field unpack failure\n");
            return -1;
        }
    }
    if(redirectedCarrierInfo_present)
    {
        if(0 != redirectedCarrierInfo.Unpack(bits, idx))
        {
            printf("RRCConnectionRelease_r8_IEs:: field unpack failure\n");
            return -1;
        }
    }
    if(idleModeMobilityControlInfo_present)
    {
        if(0 != idleModeMobilityControlInfo.Unpack(bits, idx))
        {
            printf("RRCConnectionRelease_r8_IEs:: field unpack failure\n");
            return -1;
        }
    }
    if(nonCriticalExtension_present)
    {
        if(0 != nonCriticalExtension.Unpack(bits, idx))
        {
            printf("RRCConnectionRelease_r8_IEs:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string RRCConnectionRelease_r8_IEs::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "RRCConnectionRelease_r8_IEs:\n";
    out += releaseCause_ToString(indent+1);
    if(redirectedCarrierInfo_IsPresent())
        out += redirectedCarrierInfo_ToString(indent+1);
    if(idleModeMobilityControlInfo_IsPresent())
        out += idleModeMobilityControlInfo_ToString(indent+1);
    if(nonCriticalExtension_IsPresent())
        out += nonCriticalExtension_ToString(indent+1);
    return out;
}

std::string RRCConnectionRelease_r8_IEs::ToStringNoNewLines() const
{
    std::string out = "RRCConnectionRelease_r8_IEs:";
    out += releaseCause_ToStringNoNewLines();
    if(redirectedCarrierInfo_IsPresent())
        out += redirectedCarrierInfo_ToStringNoNewLines();
    if(idleModeMobilityControlInfo_IsPresent())
        out += idleModeMobilityControlInfo_ToStringNoNewLines();
    if(nonCriticalExtension_IsPresent())
        out += nonCriticalExtension_ToStringNoNewLines();
    return out;
}

ReleaseCause* RRCConnectionRelease_r8_IEs::releaseCause_Set()
{
    releaseCause_present = true;
    return &releaseCause;
}

int RRCConnectionRelease_r8_IEs::releaseCause_Set(ReleaseCause &value)
{
    releaseCause_present = true;
    releaseCause = value;
    return 0;
}

const ReleaseCause& RRCConnectionRelease_r8_IEs::releaseCause_Get() const
{
    return releaseCause;
}

std::string RRCConnectionRelease_r8_IEs::releaseCause_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "releaseCause:\n";
    out += releaseCause.ToString(indent+1);
    return out;
}

std::string RRCConnectionRelease_r8_IEs::releaseCause_ToStringNoNewLines() const
{
    std::string out = "releaseCause:";
    out += releaseCause.ToStringNoNewLines();
    return out;
}

int RRCConnectionRelease_r8_IEs::releaseCause_Clear()
{
    releaseCause_present = false;
    return 0;
}

bool RRCConnectionRelease_r8_IEs::releaseCause_IsPresent() const
{
    return releaseCause_present;
}

RedirectedCarrierInfo* RRCConnectionRelease_r8_IEs::redirectedCarrierInfo_Set()
{
    redirectedCarrierInfo_present = true;
    return &redirectedCarrierInfo;
}

int RRCConnectionRelease_r8_IEs::redirectedCarrierInfo_Set(RedirectedCarrierInfo &value)
{
    redirectedCarrierInfo_present = true;
    redirectedCarrierInfo = value;
    return 0;
}

const RedirectedCarrierInfo& RRCConnectionRelease_r8_IEs::redirectedCarrierInfo_Get() const
{
    return redirectedCarrierInfo;
}

std::string RRCConnectionRelease_r8_IEs::redirectedCarrierInfo_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "redirectedCarrierInfo:\n";
    out += redirectedCarrierInfo.ToString(indent+1);
    return out;
}

std::string RRCConnectionRelease_r8_IEs::redirectedCarrierInfo_ToStringNoNewLines() const
{
    std::string out = "redirectedCarrierInfo:";
    out += redirectedCarrierInfo.ToStringNoNewLines();
    return out;
}

int RRCConnectionRelease_r8_IEs::redirectedCarrierInfo_Clear()
{
    redirectedCarrierInfo_present = false;
    return 0;
}

bool RRCConnectionRelease_r8_IEs::redirectedCarrierInfo_IsPresent() const
{
    return redirectedCarrierInfo_present;
}

IdleModeMobilityControlInfo* RRCConnectionRelease_r8_IEs::idleModeMobilityControlInfo_Set()
{
    idleModeMobilityControlInfo_present = true;
    return &idleModeMobilityControlInfo;
}

int RRCConnectionRelease_r8_IEs::idleModeMobilityControlInfo_Set(IdleModeMobilityControlInfo &value)
{
    idleModeMobilityControlInfo_present = true;
    idleModeMobilityControlInfo = value;
    return 0;
}

const IdleModeMobilityControlInfo& RRCConnectionRelease_r8_IEs::idleModeMobilityControlInfo_Get() const
{
    return idleModeMobilityControlInfo;
}

std::string RRCConnectionRelease_r8_IEs::idleModeMobilityControlInfo_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "idleModeMobilityControlInfo:\n";
    out += idleModeMobilityControlInfo.ToString(indent+1);
    return out;
}

std::string RRCConnectionRelease_r8_IEs::idleModeMobilityControlInfo_ToStringNoNewLines() const
{
    std::string out = "idleModeMobilityControlInfo:";
    out += idleModeMobilityControlInfo.ToStringNoNewLines();
    return out;
}

int RRCConnectionRelease_r8_IEs::idleModeMobilityControlInfo_Clear()
{
    idleModeMobilityControlInfo_present = false;
    return 0;
}

bool RRCConnectionRelease_r8_IEs::idleModeMobilityControlInfo_IsPresent() const
{
    return idleModeMobilityControlInfo_present;
}

RRCConnectionRelease_v890_IEs* RRCConnectionRelease_r8_IEs::nonCriticalExtension_Set()
{
    nonCriticalExtension_present = true;
    return &nonCriticalExtension;
}

int RRCConnectionRelease_r8_IEs::nonCriticalExtension_Set(RRCConnectionRelease_v890_IEs &value)
{
    nonCriticalExtension_present = true;
    nonCriticalExtension = value;
    return 0;
}

const RRCConnectionRelease_v890_IEs& RRCConnectionRelease_r8_IEs::nonCriticalExtension_Get() const
{
    return nonCriticalExtension;
}

std::string RRCConnectionRelease_r8_IEs::nonCriticalExtension_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "nonCriticalExtension:\n";
    out += nonCriticalExtension.ToString(indent+1);
    return out;
}

std::string RRCConnectionRelease_r8_IEs::nonCriticalExtension_ToStringNoNewLines() const
{
    std::string out = "nonCriticalExtension:";
    out += nonCriticalExtension.ToStringNoNewLines();
    return out;
}

int RRCConnectionRelease_r8_IEs::nonCriticalExtension_Clear()
{
    nonCriticalExtension_present = false;
    return 0;
}

bool RRCConnectionRelease_r8_IEs::nonCriticalExtension_IsPresent() const
{
    return nonCriticalExtension_present;
}

