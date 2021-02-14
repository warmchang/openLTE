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

#include "SecurityConfigSMC.h"

#include <cmath>

int SecurityConfigSMC::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator
    bits.push_back(0);

    // Optional indicators

    // Fields
    {
        if(0 != securityAlgorithmConfig.Pack(bits))
        {
            printf("SecurityConfigSMC:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int SecurityConfigSMC::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int SecurityConfigSMC::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("SecurityConfigSMC::Unpack() index out of bounds for extension\n");
        return -1;
    }
    idx++;

    // Optional indicators

    // Fields
    {
        if(0 != securityAlgorithmConfig.Unpack(bits, idx))
        {
            printf("SecurityConfigSMC:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string SecurityConfigSMC::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "SecurityConfigSMC:\n";
    out += securityAlgorithmConfig_ToString(indent+1);
    return out;
}

std::string SecurityConfigSMC::ToStringNoNewLines() const
{
    std::string out = "SecurityConfigSMC:";
    out += securityAlgorithmConfig_ToStringNoNewLines();
    return out;
}

SecurityAlgorithmConfig* SecurityConfigSMC::securityAlgorithmConfig_Set()
{
    securityAlgorithmConfig_present = true;
    return &securityAlgorithmConfig;
}

int SecurityConfigSMC::securityAlgorithmConfig_Set(SecurityAlgorithmConfig &value)
{
    securityAlgorithmConfig_present = true;
    securityAlgorithmConfig = value;
    return 0;
}

const SecurityAlgorithmConfig& SecurityConfigSMC::securityAlgorithmConfig_Get() const
{
    return securityAlgorithmConfig;
}

std::string SecurityConfigSMC::securityAlgorithmConfig_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "securityAlgorithmConfig:\n";
    out += securityAlgorithmConfig.ToString(indent+1);
    return out;
}

std::string SecurityConfigSMC::securityAlgorithmConfig_ToStringNoNewLines() const
{
    std::string out = "securityAlgorithmConfig:";
    out += securityAlgorithmConfig.ToStringNoNewLines();
    return out;
}

int SecurityConfigSMC::securityAlgorithmConfig_Clear()
{
    securityAlgorithmConfig_present = false;
    return 0;
}

bool SecurityConfigSMC::securityAlgorithmConfig_IsPresent() const
{
    return securityAlgorithmConfig_present;
}

