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

#include "RRCConnectionReestablishmentComplete_v10xy_IEs.h"

#include <cmath>

int RRCConnectionReestablishmentComplete_v10xy_IEs::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(logMeasAvailable_r10_IsPresent());
    bits.push_back(0);

    // Fields
    if(logMeasAvailable_r10_IsPresent())
    {
        if(0 != logMeasAvailable_r10_Pack(bits))
        {
            printf("RRCConnectionReestablishmentComplete_v10xy_IEs:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int RRCConnectionReestablishmentComplete_v10xy_IEs::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int RRCConnectionReestablishmentComplete_v10xy_IEs::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("RRCConnectionReestablishmentComplete_v10xy_IEs::Unpack() index out of bounds for optional indiator logMeasAvailable_r10\n");
        return -1;
    }
    logMeasAvailable_r10_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("RRCConnectionReestablishmentComplete_v10xy_IEs::Unpack() index out of bounds for optional indiator nonCriticalExtension\n");
        return -1;
    }
    idx++;

    // Fields
    if(logMeasAvailable_r10_present)
    {
        if(0 != logMeasAvailable_r10_Unpack(bits, idx))
        {
            printf("RRCConnectionReestablishmentComplete_v10xy_IEs:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string RRCConnectionReestablishmentComplete_v10xy_IEs::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "RRCConnectionReestablishmentComplete_v10xy_IEs:\n";
    if(logMeasAvailable_r10_IsPresent())
        out += logMeasAvailable_r10_ToString(indent+1);
    return out;
}

std::string RRCConnectionReestablishmentComplete_v10xy_IEs::ToStringNoNewLines() const
{
    std::string out = "RRCConnectionReestablishmentComplete_v10xy_IEs:";
    if(logMeasAvailable_r10_IsPresent())
        out += logMeasAvailable_r10_ToStringNoNewLines();
    return out;
}

int RRCConnectionReestablishmentComplete_v10xy_IEs::logMeasAvailable_r10_Pack(std::vector<uint8_t> &bits)
{
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((logMeasAvailable_r10_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int RRCConnectionReestablishmentComplete_v10xy_IEs::logMeasAvailable_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return logMeasAvailable_r10_Unpack(bits, idx);
}

int RRCConnectionReestablishmentComplete_v10xy_IEs::logMeasAvailable_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("RRCConnectionReestablishmentComplete_v10xy_IEs::logMeasAvailable_r10_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 0)
    {
        printf("RRCConnectionReestablishmentComplete_v10xy_IEs::logMeasAvailable_r10_Unpack() max failure\n");
        return -1;
    }
    logMeasAvailable_r10_internal_value = (logMeasAvailable_r10_Enum)packed_val;
    logMeasAvailable_r10_present = true;
    return 0;
}

RRCConnectionReestablishmentComplete_v10xy_IEs::logMeasAvailable_r10_Enum RRCConnectionReestablishmentComplete_v10xy_IEs::logMeasAvailable_r10_Value() const
{
    if(logMeasAvailable_r10_present)
        return logMeasAvailable_r10_internal_value;
    return (RRCConnectionReestablishmentComplete_v10xy_IEs::logMeasAvailable_r10_Enum)0;
}

int RRCConnectionReestablishmentComplete_v10xy_IEs::logMeasAvailable_r10_SetValue(logMeasAvailable_r10_Enum value)
{
    logMeasAvailable_r10_internal_value = value;
    logMeasAvailable_r10_present = true;
    return 0;
}

int RRCConnectionReestablishmentComplete_v10xy_IEs::logMeasAvailable_r10_SetValue(std::string value)
{
    if("true" == value)
    {
        logMeasAvailable_r10_internal_value = k_logMeasAvailable_r10_true;
        logMeasAvailable_r10_present = true;
        return 0;
    }
    return 1;
}

std::string RRCConnectionReestablishmentComplete_v10xy_IEs::logMeasAvailable_r10_ValueToString(logMeasAvailable_r10_Enum value) const
{
    if(k_logMeasAvailable_r10_true == value)
        return "true";
    return "";
}

uint64_t RRCConnectionReestablishmentComplete_v10xy_IEs::logMeasAvailable_r10_NumberOfValues() const
{
    return 1;
}

std::string RRCConnectionReestablishmentComplete_v10xy_IEs::logMeasAvailable_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "logMeasAvailable_r10 = " + logMeasAvailable_r10_ValueToString(logMeasAvailable_r10_internal_value) + "\n";
    return out;
}

std::string RRCConnectionReestablishmentComplete_v10xy_IEs::logMeasAvailable_r10_ToStringNoNewLines() const
{
    std::string out = "logMeasAvailable_r10=" + logMeasAvailable_r10_ValueToString(logMeasAvailable_r10_internal_value) + ",";
    return out;
}

int RRCConnectionReestablishmentComplete_v10xy_IEs::logMeasAvailable_r10_Clear()
{
    logMeasAvailable_r10_present = false;
    return 0;
}

bool RRCConnectionReestablishmentComplete_v10xy_IEs::logMeasAvailable_r10_IsPresent() const
{
    return logMeasAvailable_r10_present;
}

