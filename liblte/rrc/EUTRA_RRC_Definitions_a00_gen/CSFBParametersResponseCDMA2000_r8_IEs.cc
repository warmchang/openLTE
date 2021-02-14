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

#include "CSFBParametersResponseCDMA2000_r8_IEs.h"

#include <cmath>

int CSFBParametersResponseCDMA2000_r8_IEs::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(nonCriticalExtension_IsPresent());

    // Fields
    {
        if(0 != rand.Pack(bits))
        {
            printf("CSFBParametersResponseCDMA2000_r8_IEs:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != mobilityParameters.Pack(bits))
        {
            printf("CSFBParametersResponseCDMA2000_r8_IEs:: field pack failure\n");
            return -1;
        }
    }
    if(nonCriticalExtension_IsPresent())
    {
        if(0 != nonCriticalExtension.Pack(bits))
        {
            printf("CSFBParametersResponseCDMA2000_r8_IEs:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int CSFBParametersResponseCDMA2000_r8_IEs::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int CSFBParametersResponseCDMA2000_r8_IEs::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("CSFBParametersResponseCDMA2000_r8_IEs::Unpack() index out of bounds for optional indiator nonCriticalExtension\n");
        return -1;
    }
    nonCriticalExtension_present = bits[idx++];

    // Fields
    {
        if(0 != rand.Unpack(bits, idx))
        {
            printf("CSFBParametersResponseCDMA2000_r8_IEs:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != mobilityParameters.Unpack(bits, idx))
        {
            printf("CSFBParametersResponseCDMA2000_r8_IEs:: field unpack failure\n");
            return -1;
        }
    }
    if(nonCriticalExtension_present)
    {
        if(0 != nonCriticalExtension.Unpack(bits, idx))
        {
            printf("CSFBParametersResponseCDMA2000_r8_IEs:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string CSFBParametersResponseCDMA2000_r8_IEs::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "CSFBParametersResponseCDMA2000_r8_IEs:\n";
    out += rand_ToString(indent+1);
    out += mobilityParameters_ToString(indent+1);
    if(nonCriticalExtension_IsPresent())
        out += nonCriticalExtension_ToString(indent+1);
    return out;
}

std::string CSFBParametersResponseCDMA2000_r8_IEs::ToStringNoNewLines() const
{
    std::string out = "CSFBParametersResponseCDMA2000_r8_IEs:";
    out += rand_ToStringNoNewLines();
    out += mobilityParameters_ToStringNoNewLines();
    if(nonCriticalExtension_IsPresent())
        out += nonCriticalExtension_ToStringNoNewLines();
    return out;
}

RAND_CDMA2000* CSFBParametersResponseCDMA2000_r8_IEs::rand_Set()
{
    rand_present = true;
    return &rand;
}

int CSFBParametersResponseCDMA2000_r8_IEs::rand_Set(RAND_CDMA2000 &value)
{
    rand_present = true;
    rand = value;
    return 0;
}

const RAND_CDMA2000& CSFBParametersResponseCDMA2000_r8_IEs::rand_Get() const
{
    return rand;
}

std::string CSFBParametersResponseCDMA2000_r8_IEs::rand_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "rand:\n";
    out += rand.ToString(indent+1);
    return out;
}

std::string CSFBParametersResponseCDMA2000_r8_IEs::rand_ToStringNoNewLines() const
{
    std::string out = "rand:";
    out += rand.ToStringNoNewLines();
    return out;
}

int CSFBParametersResponseCDMA2000_r8_IEs::rand_Clear()
{
    rand_present = false;
    return 0;
}

bool CSFBParametersResponseCDMA2000_r8_IEs::rand_IsPresent() const
{
    return rand_present;
}

MobilityParametersCDMA2000* CSFBParametersResponseCDMA2000_r8_IEs::mobilityParameters_Set()
{
    mobilityParameters_present = true;
    return &mobilityParameters;
}

int CSFBParametersResponseCDMA2000_r8_IEs::mobilityParameters_Set(MobilityParametersCDMA2000 &value)
{
    mobilityParameters_present = true;
    mobilityParameters = value;
    return 0;
}

const MobilityParametersCDMA2000& CSFBParametersResponseCDMA2000_r8_IEs::mobilityParameters_Get() const
{
    return mobilityParameters;
}

std::string CSFBParametersResponseCDMA2000_r8_IEs::mobilityParameters_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "mobilityParameters:\n";
    out += mobilityParameters.ToString(indent+1);
    return out;
}

std::string CSFBParametersResponseCDMA2000_r8_IEs::mobilityParameters_ToStringNoNewLines() const
{
    std::string out = "mobilityParameters:";
    out += mobilityParameters.ToStringNoNewLines();
    return out;
}

int CSFBParametersResponseCDMA2000_r8_IEs::mobilityParameters_Clear()
{
    mobilityParameters_present = false;
    return 0;
}

bool CSFBParametersResponseCDMA2000_r8_IEs::mobilityParameters_IsPresent() const
{
    return mobilityParameters_present;
}

CSFBParametersResponseCDMA2000_v8a0_IEs* CSFBParametersResponseCDMA2000_r8_IEs::nonCriticalExtension_Set()
{
    nonCriticalExtension_present = true;
    return &nonCriticalExtension;
}

int CSFBParametersResponseCDMA2000_r8_IEs::nonCriticalExtension_Set(CSFBParametersResponseCDMA2000_v8a0_IEs &value)
{
    nonCriticalExtension_present = true;
    nonCriticalExtension = value;
    return 0;
}

const CSFBParametersResponseCDMA2000_v8a0_IEs& CSFBParametersResponseCDMA2000_r8_IEs::nonCriticalExtension_Get() const
{
    return nonCriticalExtension;
}

std::string CSFBParametersResponseCDMA2000_r8_IEs::nonCriticalExtension_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "nonCriticalExtension:\n";
    out += nonCriticalExtension.ToString(indent+1);
    return out;
}

std::string CSFBParametersResponseCDMA2000_r8_IEs::nonCriticalExtension_ToStringNoNewLines() const
{
    std::string out = "nonCriticalExtension:";
    out += nonCriticalExtension.ToStringNoNewLines();
    return out;
}

int CSFBParametersResponseCDMA2000_r8_IEs::nonCriticalExtension_Clear()
{
    nonCriticalExtension_present = false;
    return 0;
}

bool CSFBParametersResponseCDMA2000_r8_IEs::nonCriticalExtension_IsPresent() const
{
    return nonCriticalExtension_present;
}

