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

#include "SecurityModeCommand_r8_IEs.h"

#include <cmath>

int SecurityModeCommand_r8_IEs::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(nonCriticalExtension_IsPresent());

    // Fields
    {
        if(0 != securityConfigSMC.Pack(bits))
        {
            printf("SecurityModeCommand_r8_IEs:: field pack failure\n");
            return -1;
        }
    }
    if(nonCriticalExtension_IsPresent())
    {
        if(0 != nonCriticalExtension.Pack(bits))
        {
            printf("SecurityModeCommand_r8_IEs:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int SecurityModeCommand_r8_IEs::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int SecurityModeCommand_r8_IEs::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("SecurityModeCommand_r8_IEs::Unpack() index out of bounds for optional indiator nonCriticalExtension\n");
        return -1;
    }
    nonCriticalExtension_present = bits[idx++];

    // Fields
    {
        if(0 != securityConfigSMC.Unpack(bits, idx))
        {
            printf("SecurityModeCommand_r8_IEs:: field unpack failure\n");
            return -1;
        }
    }
    if(nonCriticalExtension_present)
    {
        if(0 != nonCriticalExtension.Unpack(bits, idx))
        {
            printf("SecurityModeCommand_r8_IEs:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string SecurityModeCommand_r8_IEs::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "SecurityModeCommand_r8_IEs:\n";
    out += securityConfigSMC_ToString(indent+1);
    if(nonCriticalExtension_IsPresent())
        out += nonCriticalExtension_ToString(indent+1);
    return out;
}

std::string SecurityModeCommand_r8_IEs::ToStringNoNewLines() const
{
    std::string out = "SecurityModeCommand_r8_IEs:";
    out += securityConfigSMC_ToStringNoNewLines();
    if(nonCriticalExtension_IsPresent())
        out += nonCriticalExtension_ToStringNoNewLines();
    return out;
}

SecurityConfigSMC* SecurityModeCommand_r8_IEs::securityConfigSMC_Set()
{
    securityConfigSMC_present = true;
    return &securityConfigSMC;
}

int SecurityModeCommand_r8_IEs::securityConfigSMC_Set(SecurityConfigSMC &value)
{
    securityConfigSMC_present = true;
    securityConfigSMC = value;
    return 0;
}

const SecurityConfigSMC& SecurityModeCommand_r8_IEs::securityConfigSMC_Get() const
{
    return securityConfigSMC;
}

std::string SecurityModeCommand_r8_IEs::securityConfigSMC_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "securityConfigSMC:\n";
    out += securityConfigSMC.ToString(indent+1);
    return out;
}

std::string SecurityModeCommand_r8_IEs::securityConfigSMC_ToStringNoNewLines() const
{
    std::string out = "securityConfigSMC:";
    out += securityConfigSMC.ToStringNoNewLines();
    return out;
}

int SecurityModeCommand_r8_IEs::securityConfigSMC_Clear()
{
    securityConfigSMC_present = false;
    return 0;
}

bool SecurityModeCommand_r8_IEs::securityConfigSMC_IsPresent() const
{
    return securityConfigSMC_present;
}

SecurityModeCommand_v8a0_IEs* SecurityModeCommand_r8_IEs::nonCriticalExtension_Set()
{
    nonCriticalExtension_present = true;
    return &nonCriticalExtension;
}

int SecurityModeCommand_r8_IEs::nonCriticalExtension_Set(SecurityModeCommand_v8a0_IEs &value)
{
    nonCriticalExtension_present = true;
    nonCriticalExtension = value;
    return 0;
}

const SecurityModeCommand_v8a0_IEs& SecurityModeCommand_r8_IEs::nonCriticalExtension_Get() const
{
    return nonCriticalExtension;
}

std::string SecurityModeCommand_r8_IEs::nonCriticalExtension_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "nonCriticalExtension:\n";
    out += nonCriticalExtension.ToString(indent+1);
    return out;
}

std::string SecurityModeCommand_r8_IEs::nonCriticalExtension_ToStringNoNewLines() const
{
    std::string out = "nonCriticalExtension:";
    out += nonCriticalExtension.ToStringNoNewLines();
    return out;
}

int SecurityModeCommand_r8_IEs::nonCriticalExtension_Clear()
{
    nonCriticalExtension_present = false;
    return 0;
}

bool SecurityModeCommand_r8_IEs::nonCriticalExtension_IsPresent() const
{
    return nonCriticalExtension_present;
}

