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

#include "RRCConnectionReestablishment_r8_IEs.h"

#include <cmath>

int RRCConnectionReestablishment_r8_IEs::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(nonCriticalExtension_IsPresent());

    // Fields
    {
        if(0 != radioResourceConfigDedicated.Pack(bits))
        {
            printf("RRCConnectionReestablishment_r8_IEs:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != nextHopChainingCount.Pack(bits))
        {
            printf("RRCConnectionReestablishment_r8_IEs:: field pack failure\n");
            return -1;
        }
    }
    if(nonCriticalExtension_IsPresent())
    {
        if(0 != nonCriticalExtension.Pack(bits))
        {
            printf("RRCConnectionReestablishment_r8_IEs:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int RRCConnectionReestablishment_r8_IEs::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int RRCConnectionReestablishment_r8_IEs::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("RRCConnectionReestablishment_r8_IEs::Unpack() index out of bounds for optional indiator nonCriticalExtension\n");
        return -1;
    }
    nonCriticalExtension_present = bits[idx++];

    // Fields
    {
        if(0 != radioResourceConfigDedicated.Unpack(bits, idx))
        {
            printf("RRCConnectionReestablishment_r8_IEs:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != nextHopChainingCount.Unpack(bits, idx))
        {
            printf("RRCConnectionReestablishment_r8_IEs:: field unpack failure\n");
            return -1;
        }
    }
    if(nonCriticalExtension_present)
    {
        if(0 != nonCriticalExtension.Unpack(bits, idx))
        {
            printf("RRCConnectionReestablishment_r8_IEs:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string RRCConnectionReestablishment_r8_IEs::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "RRCConnectionReestablishment_r8_IEs:\n";
    out += radioResourceConfigDedicated_ToString(indent+1);
    out += nextHopChainingCount_ToString(indent+1);
    if(nonCriticalExtension_IsPresent())
        out += nonCriticalExtension_ToString(indent+1);
    return out;
}

std::string RRCConnectionReestablishment_r8_IEs::ToStringNoNewLines() const
{
    std::string out = "RRCConnectionReestablishment_r8_IEs:";
    out += radioResourceConfigDedicated_ToStringNoNewLines();
    out += nextHopChainingCount_ToStringNoNewLines();
    if(nonCriticalExtension_IsPresent())
        out += nonCriticalExtension_ToStringNoNewLines();
    return out;
}

RadioResourceConfigDedicated* RRCConnectionReestablishment_r8_IEs::radioResourceConfigDedicated_Set()
{
    radioResourceConfigDedicated_present = true;
    return &radioResourceConfigDedicated;
}

int RRCConnectionReestablishment_r8_IEs::radioResourceConfigDedicated_Set(RadioResourceConfigDedicated &value)
{
    radioResourceConfigDedicated_present = true;
    radioResourceConfigDedicated = value;
    return 0;
}

const RadioResourceConfigDedicated& RRCConnectionReestablishment_r8_IEs::radioResourceConfigDedicated_Get() const
{
    return radioResourceConfigDedicated;
}

std::string RRCConnectionReestablishment_r8_IEs::radioResourceConfigDedicated_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "radioResourceConfigDedicated:\n";
    out += radioResourceConfigDedicated.ToString(indent+1);
    return out;
}

std::string RRCConnectionReestablishment_r8_IEs::radioResourceConfigDedicated_ToStringNoNewLines() const
{
    std::string out = "radioResourceConfigDedicated:";
    out += radioResourceConfigDedicated.ToStringNoNewLines();
    return out;
}

int RRCConnectionReestablishment_r8_IEs::radioResourceConfigDedicated_Clear()
{
    radioResourceConfigDedicated_present = false;
    return 0;
}

bool RRCConnectionReestablishment_r8_IEs::radioResourceConfigDedicated_IsPresent() const
{
    return radioResourceConfigDedicated_present;
}

NextHopChainingCount* RRCConnectionReestablishment_r8_IEs::nextHopChainingCount_Set()
{
    nextHopChainingCount_present = true;
    return &nextHopChainingCount;
}

int RRCConnectionReestablishment_r8_IEs::nextHopChainingCount_Set(NextHopChainingCount &value)
{
    nextHopChainingCount_present = true;
    nextHopChainingCount = value;
    return 0;
}

const NextHopChainingCount& RRCConnectionReestablishment_r8_IEs::nextHopChainingCount_Get() const
{
    return nextHopChainingCount;
}

std::string RRCConnectionReestablishment_r8_IEs::nextHopChainingCount_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "nextHopChainingCount:\n";
    out += nextHopChainingCount.ToString(indent+1);
    return out;
}

std::string RRCConnectionReestablishment_r8_IEs::nextHopChainingCount_ToStringNoNewLines() const
{
    std::string out = "nextHopChainingCount:";
    out += nextHopChainingCount.ToStringNoNewLines();
    return out;
}

int RRCConnectionReestablishment_r8_IEs::nextHopChainingCount_Clear()
{
    nextHopChainingCount_present = false;
    return 0;
}

bool RRCConnectionReestablishment_r8_IEs::nextHopChainingCount_IsPresent() const
{
    return nextHopChainingCount_present;
}

RRCConnectionReestablishment_v8a0_IEs* RRCConnectionReestablishment_r8_IEs::nonCriticalExtension_Set()
{
    nonCriticalExtension_present = true;
    return &nonCriticalExtension;
}

int RRCConnectionReestablishment_r8_IEs::nonCriticalExtension_Set(RRCConnectionReestablishment_v8a0_IEs &value)
{
    nonCriticalExtension_present = true;
    nonCriticalExtension = value;
    return 0;
}

const RRCConnectionReestablishment_v8a0_IEs& RRCConnectionReestablishment_r8_IEs::nonCriticalExtension_Get() const
{
    return nonCriticalExtension;
}

std::string RRCConnectionReestablishment_r8_IEs::nonCriticalExtension_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "nonCriticalExtension:\n";
    out += nonCriticalExtension.ToString(indent+1);
    return out;
}

std::string RRCConnectionReestablishment_r8_IEs::nonCriticalExtension_ToStringNoNewLines() const
{
    std::string out = "nonCriticalExtension:";
    out += nonCriticalExtension.ToStringNoNewLines();
    return out;
}

int RRCConnectionReestablishment_r8_IEs::nonCriticalExtension_Clear()
{
    nonCriticalExtension_present = false;
    return 0;
}

bool RRCConnectionReestablishment_r8_IEs::nonCriticalExtension_IsPresent() const
{
    return nonCriticalExtension_present;
}

