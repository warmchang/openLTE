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

#include "RRCConnectionReestablishmentComplete_v920_IEs.h"

#include <cmath>

int RRCConnectionReestablishmentComplete_v920_IEs::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(rlf_InfoAvailable_r9_IsPresent());
    bits.push_back(nonCriticalExtension_IsPresent());

    // Fields
    if(rlf_InfoAvailable_r9_IsPresent())
    {
        if(0 != rlf_InfoAvailable_r9_Pack(bits))
        {
            printf("RRCConnectionReestablishmentComplete_v920_IEs:: field pack failure\n");
            return -1;
        }
    }
    if(nonCriticalExtension_IsPresent())
    {
        if(0 != nonCriticalExtension.Pack(bits))
        {
            printf("RRCConnectionReestablishmentComplete_v920_IEs:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int RRCConnectionReestablishmentComplete_v920_IEs::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int RRCConnectionReestablishmentComplete_v920_IEs::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("RRCConnectionReestablishmentComplete_v920_IEs::Unpack() index out of bounds for optional indiator rlf_InfoAvailable_r9\n");
        return -1;
    }
    rlf_InfoAvailable_r9_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("RRCConnectionReestablishmentComplete_v920_IEs::Unpack() index out of bounds for optional indiator nonCriticalExtension\n");
        return -1;
    }
    nonCriticalExtension_present = bits[idx++];

    // Fields
    if(rlf_InfoAvailable_r9_present)
    {
        if(0 != rlf_InfoAvailable_r9_Unpack(bits, idx))
        {
            printf("RRCConnectionReestablishmentComplete_v920_IEs:: field unpack failure\n");
            return -1;
        }
    }
    if(nonCriticalExtension_present)
    {
        if(0 != nonCriticalExtension.Unpack(bits, idx))
        {
            printf("RRCConnectionReestablishmentComplete_v920_IEs:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string RRCConnectionReestablishmentComplete_v920_IEs::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "RRCConnectionReestablishmentComplete_v920_IEs:\n";
    if(rlf_InfoAvailable_r9_IsPresent())
        out += rlf_InfoAvailable_r9_ToString(indent+1);
    if(nonCriticalExtension_IsPresent())
        out += nonCriticalExtension_ToString(indent+1);
    return out;
}

std::string RRCConnectionReestablishmentComplete_v920_IEs::ToStringNoNewLines() const
{
    std::string out = "RRCConnectionReestablishmentComplete_v920_IEs:";
    if(rlf_InfoAvailable_r9_IsPresent())
        out += rlf_InfoAvailable_r9_ToStringNoNewLines();
    if(nonCriticalExtension_IsPresent())
        out += nonCriticalExtension_ToStringNoNewLines();
    return out;
}

int RRCConnectionReestablishmentComplete_v920_IEs::rlf_InfoAvailable_r9_Pack(std::vector<uint8_t> &bits)
{
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((rlf_InfoAvailable_r9_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int RRCConnectionReestablishmentComplete_v920_IEs::rlf_InfoAvailable_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return rlf_InfoAvailable_r9_Unpack(bits, idx);
}

int RRCConnectionReestablishmentComplete_v920_IEs::rlf_InfoAvailable_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("RRCConnectionReestablishmentComplete_v920_IEs::rlf_InfoAvailable_r9_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 0)
    {
        printf("RRCConnectionReestablishmentComplete_v920_IEs::rlf_InfoAvailable_r9_Unpack() max failure\n");
        return -1;
    }
    rlf_InfoAvailable_r9_internal_value = (rlf_InfoAvailable_r9_Enum)packed_val;
    rlf_InfoAvailable_r9_present = true;
    return 0;
}

RRCConnectionReestablishmentComplete_v920_IEs::rlf_InfoAvailable_r9_Enum RRCConnectionReestablishmentComplete_v920_IEs::rlf_InfoAvailable_r9_Value() const
{
    if(rlf_InfoAvailable_r9_present)
        return rlf_InfoAvailable_r9_internal_value;
    return (RRCConnectionReestablishmentComplete_v920_IEs::rlf_InfoAvailable_r9_Enum)0;
}

int RRCConnectionReestablishmentComplete_v920_IEs::rlf_InfoAvailable_r9_SetValue(rlf_InfoAvailable_r9_Enum value)
{
    rlf_InfoAvailable_r9_internal_value = value;
    rlf_InfoAvailable_r9_present = true;
    return 0;
}

int RRCConnectionReestablishmentComplete_v920_IEs::rlf_InfoAvailable_r9_SetValue(std::string value)
{
    if("true" == value)
    {
        rlf_InfoAvailable_r9_internal_value = k_rlf_InfoAvailable_r9_true;
        rlf_InfoAvailable_r9_present = true;
        return 0;
    }
    return 1;
}

std::string RRCConnectionReestablishmentComplete_v920_IEs::rlf_InfoAvailable_r9_ValueToString(rlf_InfoAvailable_r9_Enum value) const
{
    if(k_rlf_InfoAvailable_r9_true == value)
        return "true";
    return "";
}

uint64_t RRCConnectionReestablishmentComplete_v920_IEs::rlf_InfoAvailable_r9_NumberOfValues() const
{
    return 1;
}

std::string RRCConnectionReestablishmentComplete_v920_IEs::rlf_InfoAvailable_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "rlf_InfoAvailable_r9 = " + rlf_InfoAvailable_r9_ValueToString(rlf_InfoAvailable_r9_internal_value) + "\n";
    return out;
}

std::string RRCConnectionReestablishmentComplete_v920_IEs::rlf_InfoAvailable_r9_ToStringNoNewLines() const
{
    std::string out = "rlf_InfoAvailable_r9=" + rlf_InfoAvailable_r9_ValueToString(rlf_InfoAvailable_r9_internal_value) + ",";
    return out;
}

int RRCConnectionReestablishmentComplete_v920_IEs::rlf_InfoAvailable_r9_Clear()
{
    rlf_InfoAvailable_r9_present = false;
    return 0;
}

bool RRCConnectionReestablishmentComplete_v920_IEs::rlf_InfoAvailable_r9_IsPresent() const
{
    return rlf_InfoAvailable_r9_present;
}

RRCConnectionReestablishmentComplete_v8a0_IEs* RRCConnectionReestablishmentComplete_v920_IEs::nonCriticalExtension_Set()
{
    nonCriticalExtension_present = true;
    return &nonCriticalExtension;
}

int RRCConnectionReestablishmentComplete_v920_IEs::nonCriticalExtension_Set(RRCConnectionReestablishmentComplete_v8a0_IEs &value)
{
    nonCriticalExtension_present = true;
    nonCriticalExtension = value;
    return 0;
}

const RRCConnectionReestablishmentComplete_v8a0_IEs& RRCConnectionReestablishmentComplete_v920_IEs::nonCriticalExtension_Get() const
{
    return nonCriticalExtension;
}

std::string RRCConnectionReestablishmentComplete_v920_IEs::nonCriticalExtension_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "nonCriticalExtension:\n";
    out += nonCriticalExtension.ToString(indent+1);
    return out;
}

std::string RRCConnectionReestablishmentComplete_v920_IEs::nonCriticalExtension_ToStringNoNewLines() const
{
    std::string out = "nonCriticalExtension:";
    out += nonCriticalExtension.ToStringNoNewLines();
    return out;
}

int RRCConnectionReestablishmentComplete_v920_IEs::nonCriticalExtension_Clear()
{
    nonCriticalExtension_present = false;
    return 0;
}

bool RRCConnectionReestablishmentComplete_v920_IEs::nonCriticalExtension_IsPresent() const
{
    return nonCriticalExtension_present;
}

