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

#include "RRCConnectionReconfiguration_v920_IEs.h"

#include <cmath>

int RRCConnectionReconfiguration_v920_IEs::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(otherConfig_r9_IsPresent());
    bits.push_back(fullConfig_r9_IsPresent());
    bits.push_back(nonCriticalExtension_IsPresent());

    // Fields
    if(otherConfig_r9_IsPresent())
    {
        if(0 != otherConfig_r9.Pack(bits))
        {
            printf("RRCConnectionReconfiguration_v920_IEs:: field pack failure\n");
            return -1;
        }
    }
    if(fullConfig_r9_IsPresent())
    {
        if(0 != fullConfig_r9_Pack(bits))
        {
            printf("RRCConnectionReconfiguration_v920_IEs:: field pack failure\n");
            return -1;
        }
    }
    if(nonCriticalExtension_IsPresent())
    {
        if(0 != nonCriticalExtension.Pack(bits))
        {
            printf("RRCConnectionReconfiguration_v920_IEs:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int RRCConnectionReconfiguration_v920_IEs::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int RRCConnectionReconfiguration_v920_IEs::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("RRCConnectionReconfiguration_v920_IEs::Unpack() index out of bounds for optional indiator otherConfig_r9\n");
        return -1;
    }
    otherConfig_r9_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("RRCConnectionReconfiguration_v920_IEs::Unpack() index out of bounds for optional indiator fullConfig_r9\n");
        return -1;
    }
    fullConfig_r9_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("RRCConnectionReconfiguration_v920_IEs::Unpack() index out of bounds for optional indiator nonCriticalExtension\n");
        return -1;
    }
    nonCriticalExtension_present = bits[idx++];

    // Fields
    if(otherConfig_r9_present)
    {
        if(0 != otherConfig_r9.Unpack(bits, idx))
        {
            printf("RRCConnectionReconfiguration_v920_IEs:: field unpack failure\n");
            return -1;
        }
    }
    if(fullConfig_r9_present)
    {
        if(0 != fullConfig_r9_Unpack(bits, idx))
        {
            printf("RRCConnectionReconfiguration_v920_IEs:: field unpack failure\n");
            return -1;
        }
    }
    if(nonCriticalExtension_present)
    {
        if(0 != nonCriticalExtension.Unpack(bits, idx))
        {
            printf("RRCConnectionReconfiguration_v920_IEs:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string RRCConnectionReconfiguration_v920_IEs::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "RRCConnectionReconfiguration_v920_IEs:\n";
    if(otherConfig_r9_IsPresent())
        out += otherConfig_r9_ToString(indent+1);
    if(fullConfig_r9_IsPresent())
        out += fullConfig_r9_ToString(indent+1);
    if(nonCriticalExtension_IsPresent())
        out += nonCriticalExtension_ToString(indent+1);
    return out;
}

std::string RRCConnectionReconfiguration_v920_IEs::ToStringNoNewLines() const
{
    std::string out = "RRCConnectionReconfiguration_v920_IEs:";
    if(otherConfig_r9_IsPresent())
        out += otherConfig_r9_ToStringNoNewLines();
    if(fullConfig_r9_IsPresent())
        out += fullConfig_r9_ToStringNoNewLines();
    if(nonCriticalExtension_IsPresent())
        out += nonCriticalExtension_ToStringNoNewLines();
    return out;
}

OtherConfig_r9* RRCConnectionReconfiguration_v920_IEs::otherConfig_r9_Set()
{
    otherConfig_r9_present = true;
    return &otherConfig_r9;
}

int RRCConnectionReconfiguration_v920_IEs::otherConfig_r9_Set(OtherConfig_r9 &value)
{
    otherConfig_r9_present = true;
    otherConfig_r9 = value;
    return 0;
}

const OtherConfig_r9& RRCConnectionReconfiguration_v920_IEs::otherConfig_r9_Get() const
{
    return otherConfig_r9;
}

std::string RRCConnectionReconfiguration_v920_IEs::otherConfig_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "otherConfig_r9:\n";
    out += otherConfig_r9.ToString(indent+1);
    return out;
}

std::string RRCConnectionReconfiguration_v920_IEs::otherConfig_r9_ToStringNoNewLines() const
{
    std::string out = "otherConfig_r9:";
    out += otherConfig_r9.ToStringNoNewLines();
    return out;
}

int RRCConnectionReconfiguration_v920_IEs::otherConfig_r9_Clear()
{
    otherConfig_r9_present = false;
    return 0;
}

bool RRCConnectionReconfiguration_v920_IEs::otherConfig_r9_IsPresent() const
{
    return otherConfig_r9_present;
}

int RRCConnectionReconfiguration_v920_IEs::fullConfig_r9_Pack(std::vector<uint8_t> &bits)
{
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((fullConfig_r9_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int RRCConnectionReconfiguration_v920_IEs::fullConfig_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return fullConfig_r9_Unpack(bits, idx);
}

int RRCConnectionReconfiguration_v920_IEs::fullConfig_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("RRCConnectionReconfiguration_v920_IEs::fullConfig_r9_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 0)
    {
        printf("RRCConnectionReconfiguration_v920_IEs::fullConfig_r9_Unpack() max failure\n");
        return -1;
    }
    fullConfig_r9_internal_value = (fullConfig_r9_Enum)packed_val;
    fullConfig_r9_present = true;
    return 0;
}

RRCConnectionReconfiguration_v920_IEs::fullConfig_r9_Enum RRCConnectionReconfiguration_v920_IEs::fullConfig_r9_Value() const
{
    if(fullConfig_r9_present)
        return fullConfig_r9_internal_value;
    return (RRCConnectionReconfiguration_v920_IEs::fullConfig_r9_Enum)0;
}

int RRCConnectionReconfiguration_v920_IEs::fullConfig_r9_SetValue(fullConfig_r9_Enum value)
{
    fullConfig_r9_internal_value = value;
    fullConfig_r9_present = true;
    return 0;
}

int RRCConnectionReconfiguration_v920_IEs::fullConfig_r9_SetValue(std::string value)
{
    if("true" == value)
    {
        fullConfig_r9_internal_value = k_fullConfig_r9_true;
        fullConfig_r9_present = true;
        return 0;
    }
    return 1;
}

std::string RRCConnectionReconfiguration_v920_IEs::fullConfig_r9_ValueToString(fullConfig_r9_Enum value) const
{
    if(k_fullConfig_r9_true == value)
        return "true";
    return "";
}

uint64_t RRCConnectionReconfiguration_v920_IEs::fullConfig_r9_NumberOfValues() const
{
    return 1;
}

std::string RRCConnectionReconfiguration_v920_IEs::fullConfig_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "fullConfig_r9 = " + fullConfig_r9_ValueToString(fullConfig_r9_internal_value) + "\n";
    return out;
}

std::string RRCConnectionReconfiguration_v920_IEs::fullConfig_r9_ToStringNoNewLines() const
{
    std::string out = "fullConfig_r9=" + fullConfig_r9_ValueToString(fullConfig_r9_internal_value) + ",";
    return out;
}

int RRCConnectionReconfiguration_v920_IEs::fullConfig_r9_Clear()
{
    fullConfig_r9_present = false;
    return 0;
}

bool RRCConnectionReconfiguration_v920_IEs::fullConfig_r9_IsPresent() const
{
    return fullConfig_r9_present;
}

RRCConnectionReconfiguration_v10xy_IEs* RRCConnectionReconfiguration_v920_IEs::nonCriticalExtension_Set()
{
    nonCriticalExtension_present = true;
    return &nonCriticalExtension;
}

int RRCConnectionReconfiguration_v920_IEs::nonCriticalExtension_Set(RRCConnectionReconfiguration_v10xy_IEs &value)
{
    nonCriticalExtension_present = true;
    nonCriticalExtension = value;
    return 0;
}

const RRCConnectionReconfiguration_v10xy_IEs& RRCConnectionReconfiguration_v920_IEs::nonCriticalExtension_Get() const
{
    return nonCriticalExtension;
}

std::string RRCConnectionReconfiguration_v920_IEs::nonCriticalExtension_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "nonCriticalExtension:\n";
    out += nonCriticalExtension.ToString(indent+1);
    return out;
}

std::string RRCConnectionReconfiguration_v920_IEs::nonCriticalExtension_ToStringNoNewLines() const
{
    std::string out = "nonCriticalExtension:";
    out += nonCriticalExtension.ToStringNoNewLines();
    return out;
}

int RRCConnectionReconfiguration_v920_IEs::nonCriticalExtension_Clear()
{
    nonCriticalExtension_present = false;
    return 0;
}

bool RRCConnectionReconfiguration_v920_IEs::nonCriticalExtension_IsPresent() const
{
    return nonCriticalExtension_present;
}

