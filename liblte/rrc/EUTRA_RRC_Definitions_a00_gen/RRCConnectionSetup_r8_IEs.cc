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

#include "RRCConnectionSetup_r8_IEs.h"

#include <cmath>

int RRCConnectionSetup_r8_IEs::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(nonCriticalExtension_IsPresent());

    // Fields
    {
        if(0 != radioResourceConfigDedicated.Pack(bits))
        {
            printf("RRCConnectionSetup_r8_IEs:: field pack failure\n");
            return -1;
        }
    }
    if(nonCriticalExtension_IsPresent())
    {
        if(0 != nonCriticalExtension.Pack(bits))
        {
            printf("RRCConnectionSetup_r8_IEs:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int RRCConnectionSetup_r8_IEs::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int RRCConnectionSetup_r8_IEs::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("RRCConnectionSetup_r8_IEs::Unpack() index out of bounds for optional indiator nonCriticalExtension\n");
        return -1;
    }
    nonCriticalExtension_present = bits[idx++];

    // Fields
    {
        if(0 != radioResourceConfigDedicated.Unpack(bits, idx))
        {
            printf("RRCConnectionSetup_r8_IEs:: field unpack failure\n");
            return -1;
        }
    }
    if(nonCriticalExtension_present)
    {
        if(0 != nonCriticalExtension.Unpack(bits, idx))
        {
            printf("RRCConnectionSetup_r8_IEs:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string RRCConnectionSetup_r8_IEs::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "RRCConnectionSetup_r8_IEs:\n";
    out += radioResourceConfigDedicated_ToString(indent+1);
    if(nonCriticalExtension_IsPresent())
        out += nonCriticalExtension_ToString(indent+1);
    return out;
}

std::string RRCConnectionSetup_r8_IEs::ToStringNoNewLines() const
{
    std::string out = "RRCConnectionSetup_r8_IEs:";
    out += radioResourceConfigDedicated_ToStringNoNewLines();
    if(nonCriticalExtension_IsPresent())
        out += nonCriticalExtension_ToStringNoNewLines();
    return out;
}

RadioResourceConfigDedicated* RRCConnectionSetup_r8_IEs::radioResourceConfigDedicated_Set()
{
    radioResourceConfigDedicated_present = true;
    return &radioResourceConfigDedicated;
}

int RRCConnectionSetup_r8_IEs::radioResourceConfigDedicated_Set(RadioResourceConfigDedicated &value)
{
    radioResourceConfigDedicated_present = true;
    radioResourceConfigDedicated = value;
    return 0;
}

const RadioResourceConfigDedicated& RRCConnectionSetup_r8_IEs::radioResourceConfigDedicated_Get() const
{
    return radioResourceConfigDedicated;
}

std::string RRCConnectionSetup_r8_IEs::radioResourceConfigDedicated_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "radioResourceConfigDedicated:\n";
    out += radioResourceConfigDedicated.ToString(indent+1);
    return out;
}

std::string RRCConnectionSetup_r8_IEs::radioResourceConfigDedicated_ToStringNoNewLines() const
{
    std::string out = "radioResourceConfigDedicated:";
    out += radioResourceConfigDedicated.ToStringNoNewLines();
    return out;
}

int RRCConnectionSetup_r8_IEs::radioResourceConfigDedicated_Clear()
{
    radioResourceConfigDedicated_present = false;
    return 0;
}

bool RRCConnectionSetup_r8_IEs::radioResourceConfigDedicated_IsPresent() const
{
    return radioResourceConfigDedicated_present;
}

RRCConnectionSetup_v8a0_IEs* RRCConnectionSetup_r8_IEs::nonCriticalExtension_Set()
{
    nonCriticalExtension_present = true;
    return &nonCriticalExtension;
}

int RRCConnectionSetup_r8_IEs::nonCriticalExtension_Set(RRCConnectionSetup_v8a0_IEs &value)
{
    nonCriticalExtension_present = true;
    nonCriticalExtension = value;
    return 0;
}

const RRCConnectionSetup_v8a0_IEs& RRCConnectionSetup_r8_IEs::nonCriticalExtension_Get() const
{
    return nonCriticalExtension;
}

std::string RRCConnectionSetup_r8_IEs::nonCriticalExtension_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "nonCriticalExtension:\n";
    out += nonCriticalExtension.ToString(indent+1);
    return out;
}

std::string RRCConnectionSetup_r8_IEs::nonCriticalExtension_ToStringNoNewLines() const
{
    std::string out = "nonCriticalExtension:";
    out += nonCriticalExtension.ToStringNoNewLines();
    return out;
}

int RRCConnectionSetup_r8_IEs::nonCriticalExtension_Clear()
{
    nonCriticalExtension_present = false;
    return 0;
}

bool RRCConnectionSetup_r8_IEs::nonCriticalExtension_IsPresent() const
{
    return nonCriticalExtension_present;
}

