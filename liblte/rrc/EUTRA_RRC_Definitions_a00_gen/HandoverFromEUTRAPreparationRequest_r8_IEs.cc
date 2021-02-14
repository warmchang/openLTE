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

#include "HandoverFromEUTRAPreparationRequest_r8_IEs.h"

#include <cmath>

int HandoverFromEUTRAPreparationRequest_r8_IEs::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(rand_IsPresent());
    bits.push_back(mobilityParameters_IsPresent());
    bits.push_back(nonCriticalExtension_IsPresent());

    // Fields
    {
        if(0 != cdma2000_Type.Pack(bits))
        {
            printf("HandoverFromEUTRAPreparationRequest_r8_IEs:: field pack failure\n");
            return -1;
        }
    }
    if(rand_IsPresent())
    {
        if(0 != rand.Pack(bits))
        {
            printf("HandoverFromEUTRAPreparationRequest_r8_IEs:: field pack failure\n");
            return -1;
        }
    }
    if(mobilityParameters_IsPresent())
    {
        if(0 != mobilityParameters.Pack(bits))
        {
            printf("HandoverFromEUTRAPreparationRequest_r8_IEs:: field pack failure\n");
            return -1;
        }
    }
    if(nonCriticalExtension_IsPresent())
    {
        if(0 != nonCriticalExtension.Pack(bits))
        {
            printf("HandoverFromEUTRAPreparationRequest_r8_IEs:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int HandoverFromEUTRAPreparationRequest_r8_IEs::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int HandoverFromEUTRAPreparationRequest_r8_IEs::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("HandoverFromEUTRAPreparationRequest_r8_IEs::Unpack() index out of bounds for optional indiator rand\n");
        return -1;
    }
    rand_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("HandoverFromEUTRAPreparationRequest_r8_IEs::Unpack() index out of bounds for optional indiator mobilityParameters\n");
        return -1;
    }
    mobilityParameters_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("HandoverFromEUTRAPreparationRequest_r8_IEs::Unpack() index out of bounds for optional indiator nonCriticalExtension\n");
        return -1;
    }
    nonCriticalExtension_present = bits[idx++];

    // Fields
    {
        if(0 != cdma2000_Type.Unpack(bits, idx))
        {
            printf("HandoverFromEUTRAPreparationRequest_r8_IEs:: field unpack failure\n");
            return -1;
        }
    }
    if(rand_present)
    {
        if(0 != rand.Unpack(bits, idx))
        {
            printf("HandoverFromEUTRAPreparationRequest_r8_IEs:: field unpack failure\n");
            return -1;
        }
    }
    if(mobilityParameters_present)
    {
        if(0 != mobilityParameters.Unpack(bits, idx))
        {
            printf("HandoverFromEUTRAPreparationRequest_r8_IEs:: field unpack failure\n");
            return -1;
        }
    }
    if(nonCriticalExtension_present)
    {
        if(0 != nonCriticalExtension.Unpack(bits, idx))
        {
            printf("HandoverFromEUTRAPreparationRequest_r8_IEs:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string HandoverFromEUTRAPreparationRequest_r8_IEs::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "HandoverFromEUTRAPreparationRequest_r8_IEs:\n";
    out += cdma2000_Type_ToString(indent+1);
    if(rand_IsPresent())
        out += rand_ToString(indent+1);
    if(mobilityParameters_IsPresent())
        out += mobilityParameters_ToString(indent+1);
    if(nonCriticalExtension_IsPresent())
        out += nonCriticalExtension_ToString(indent+1);
    return out;
}

std::string HandoverFromEUTRAPreparationRequest_r8_IEs::ToStringNoNewLines() const
{
    std::string out = "HandoverFromEUTRAPreparationRequest_r8_IEs:";
    out += cdma2000_Type_ToStringNoNewLines();
    if(rand_IsPresent())
        out += rand_ToStringNoNewLines();
    if(mobilityParameters_IsPresent())
        out += mobilityParameters_ToStringNoNewLines();
    if(nonCriticalExtension_IsPresent())
        out += nonCriticalExtension_ToStringNoNewLines();
    return out;
}

CDMA2000_Type* HandoverFromEUTRAPreparationRequest_r8_IEs::cdma2000_Type_Set()
{
    cdma2000_Type_present = true;
    return &cdma2000_Type;
}

int HandoverFromEUTRAPreparationRequest_r8_IEs::cdma2000_Type_Set(CDMA2000_Type &value)
{
    cdma2000_Type_present = true;
    cdma2000_Type = value;
    return 0;
}

const CDMA2000_Type& HandoverFromEUTRAPreparationRequest_r8_IEs::cdma2000_Type_Get() const
{
    return cdma2000_Type;
}

std::string HandoverFromEUTRAPreparationRequest_r8_IEs::cdma2000_Type_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cdma2000_Type:\n";
    out += cdma2000_Type.ToString(indent+1);
    return out;
}

std::string HandoverFromEUTRAPreparationRequest_r8_IEs::cdma2000_Type_ToStringNoNewLines() const
{
    std::string out = "cdma2000_Type:";
    out += cdma2000_Type.ToStringNoNewLines();
    return out;
}

int HandoverFromEUTRAPreparationRequest_r8_IEs::cdma2000_Type_Clear()
{
    cdma2000_Type_present = false;
    return 0;
}

bool HandoverFromEUTRAPreparationRequest_r8_IEs::cdma2000_Type_IsPresent() const
{
    return cdma2000_Type_present;
}

RAND_CDMA2000* HandoverFromEUTRAPreparationRequest_r8_IEs::rand_Set()
{
    rand_present = true;
    return &rand;
}

int HandoverFromEUTRAPreparationRequest_r8_IEs::rand_Set(RAND_CDMA2000 &value)
{
    rand_present = true;
    rand = value;
    return 0;
}

const RAND_CDMA2000& HandoverFromEUTRAPreparationRequest_r8_IEs::rand_Get() const
{
    return rand;
}

std::string HandoverFromEUTRAPreparationRequest_r8_IEs::rand_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "rand:\n";
    out += rand.ToString(indent+1);
    return out;
}

std::string HandoverFromEUTRAPreparationRequest_r8_IEs::rand_ToStringNoNewLines() const
{
    std::string out = "rand:";
    out += rand.ToStringNoNewLines();
    return out;
}

int HandoverFromEUTRAPreparationRequest_r8_IEs::rand_Clear()
{
    rand_present = false;
    return 0;
}

bool HandoverFromEUTRAPreparationRequest_r8_IEs::rand_IsPresent() const
{
    return rand_present;
}

MobilityParametersCDMA2000* HandoverFromEUTRAPreparationRequest_r8_IEs::mobilityParameters_Set()
{
    mobilityParameters_present = true;
    return &mobilityParameters;
}

int HandoverFromEUTRAPreparationRequest_r8_IEs::mobilityParameters_Set(MobilityParametersCDMA2000 &value)
{
    mobilityParameters_present = true;
    mobilityParameters = value;
    return 0;
}

const MobilityParametersCDMA2000& HandoverFromEUTRAPreparationRequest_r8_IEs::mobilityParameters_Get() const
{
    return mobilityParameters;
}

std::string HandoverFromEUTRAPreparationRequest_r8_IEs::mobilityParameters_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "mobilityParameters:\n";
    out += mobilityParameters.ToString(indent+1);
    return out;
}

std::string HandoverFromEUTRAPreparationRequest_r8_IEs::mobilityParameters_ToStringNoNewLines() const
{
    std::string out = "mobilityParameters:";
    out += mobilityParameters.ToStringNoNewLines();
    return out;
}

int HandoverFromEUTRAPreparationRequest_r8_IEs::mobilityParameters_Clear()
{
    mobilityParameters_present = false;
    return 0;
}

bool HandoverFromEUTRAPreparationRequest_r8_IEs::mobilityParameters_IsPresent() const
{
    return mobilityParameters_present;
}

HandoverFromEUTRAPreparationRequest_v890_IEs* HandoverFromEUTRAPreparationRequest_r8_IEs::nonCriticalExtension_Set()
{
    nonCriticalExtension_present = true;
    return &nonCriticalExtension;
}

int HandoverFromEUTRAPreparationRequest_r8_IEs::nonCriticalExtension_Set(HandoverFromEUTRAPreparationRequest_v890_IEs &value)
{
    nonCriticalExtension_present = true;
    nonCriticalExtension = value;
    return 0;
}

const HandoverFromEUTRAPreparationRequest_v890_IEs& HandoverFromEUTRAPreparationRequest_r8_IEs::nonCriticalExtension_Get() const
{
    return nonCriticalExtension;
}

std::string HandoverFromEUTRAPreparationRequest_r8_IEs::nonCriticalExtension_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "nonCriticalExtension:\n";
    out += nonCriticalExtension.ToString(indent+1);
    return out;
}

std::string HandoverFromEUTRAPreparationRequest_r8_IEs::nonCriticalExtension_ToStringNoNewLines() const
{
    std::string out = "nonCriticalExtension:";
    out += nonCriticalExtension.ToStringNoNewLines();
    return out;
}

int HandoverFromEUTRAPreparationRequest_r8_IEs::nonCriticalExtension_Clear()
{
    nonCriticalExtension_present = false;
    return 0;
}

bool HandoverFromEUTRAPreparationRequest_r8_IEs::nonCriticalExtension_IsPresent() const
{
    return nonCriticalExtension_present;
}

