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

#include "RRCConnectionSetupComplete_v10xy_IEs.h"

#include <cmath>

int RRCConnectionSetupComplete_v10xy_IEs::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(logMeasAvailable_r10_IsPresent());
    bits.push_back(rn_SubframeConfigReq_r10_IsPresent());
    bits.push_back(0);

    // Fields
    if(logMeasAvailable_r10_IsPresent())
    {
        if(0 != logMeasAvailable_r10_Pack(bits))
        {
            printf("RRCConnectionSetupComplete_v10xy_IEs:: field pack failure\n");
            return -1;
        }
    }
    if(rn_SubframeConfigReq_r10_IsPresent())
    {
        if(0 != rn_SubframeConfigReq_r10_Pack(bits))
        {
            printf("RRCConnectionSetupComplete_v10xy_IEs:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int RRCConnectionSetupComplete_v10xy_IEs::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int RRCConnectionSetupComplete_v10xy_IEs::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("RRCConnectionSetupComplete_v10xy_IEs::Unpack() index out of bounds for optional indiator logMeasAvailable_r10\n");
        return -1;
    }
    logMeasAvailable_r10_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("RRCConnectionSetupComplete_v10xy_IEs::Unpack() index out of bounds for optional indiator rn_SubframeConfigReq_r10\n");
        return -1;
    }
    rn_SubframeConfigReq_r10_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("RRCConnectionSetupComplete_v10xy_IEs::Unpack() index out of bounds for optional indiator nonCriticalExtension\n");
        return -1;
    }
    idx++;

    // Fields
    if(logMeasAvailable_r10_present)
    {
        if(0 != logMeasAvailable_r10_Unpack(bits, idx))
        {
            printf("RRCConnectionSetupComplete_v10xy_IEs:: field unpack failure\n");
            return -1;
        }
    }
    if(rn_SubframeConfigReq_r10_present)
    {
        if(0 != rn_SubframeConfigReq_r10_Unpack(bits, idx))
        {
            printf("RRCConnectionSetupComplete_v10xy_IEs:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string RRCConnectionSetupComplete_v10xy_IEs::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "RRCConnectionSetupComplete_v10xy_IEs:\n";
    if(logMeasAvailable_r10_IsPresent())
        out += logMeasAvailable_r10_ToString(indent+1);
    if(rn_SubframeConfigReq_r10_IsPresent())
        out += rn_SubframeConfigReq_r10_ToString(indent+1);
    return out;
}

std::string RRCConnectionSetupComplete_v10xy_IEs::ToStringNoNewLines() const
{
    std::string out = "RRCConnectionSetupComplete_v10xy_IEs:";
    if(logMeasAvailable_r10_IsPresent())
        out += logMeasAvailable_r10_ToStringNoNewLines();
    if(rn_SubframeConfigReq_r10_IsPresent())
        out += rn_SubframeConfigReq_r10_ToStringNoNewLines();
    return out;
}

int RRCConnectionSetupComplete_v10xy_IEs::logMeasAvailable_r10_Pack(std::vector<uint8_t> &bits)
{
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((logMeasAvailable_r10_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int RRCConnectionSetupComplete_v10xy_IEs::logMeasAvailable_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return logMeasAvailable_r10_Unpack(bits, idx);
}

int RRCConnectionSetupComplete_v10xy_IEs::logMeasAvailable_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("RRCConnectionSetupComplete_v10xy_IEs::logMeasAvailable_r10_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 0)
    {
        printf("RRCConnectionSetupComplete_v10xy_IEs::logMeasAvailable_r10_Unpack() max failure\n");
        return -1;
    }
    logMeasAvailable_r10_internal_value = (logMeasAvailable_r10_Enum)packed_val;
    logMeasAvailable_r10_present = true;
    return 0;
}

RRCConnectionSetupComplete_v10xy_IEs::logMeasAvailable_r10_Enum RRCConnectionSetupComplete_v10xy_IEs::logMeasAvailable_r10_Value() const
{
    if(logMeasAvailable_r10_present)
        return logMeasAvailable_r10_internal_value;
    return (RRCConnectionSetupComplete_v10xy_IEs::logMeasAvailable_r10_Enum)0;
}

int RRCConnectionSetupComplete_v10xy_IEs::logMeasAvailable_r10_SetValue(logMeasAvailable_r10_Enum value)
{
    logMeasAvailable_r10_internal_value = value;
    logMeasAvailable_r10_present = true;
    return 0;
}

int RRCConnectionSetupComplete_v10xy_IEs::logMeasAvailable_r10_SetValue(std::string value)
{
    if("true" == value)
    {
        logMeasAvailable_r10_internal_value = k_logMeasAvailable_r10_true;
        logMeasAvailable_r10_present = true;
        return 0;
    }
    return 1;
}

std::string RRCConnectionSetupComplete_v10xy_IEs::logMeasAvailable_r10_ValueToString(logMeasAvailable_r10_Enum value) const
{
    if(k_logMeasAvailable_r10_true == value)
        return "true";
    return "";
}

uint64_t RRCConnectionSetupComplete_v10xy_IEs::logMeasAvailable_r10_NumberOfValues() const
{
    return 1;
}

std::string RRCConnectionSetupComplete_v10xy_IEs::logMeasAvailable_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "logMeasAvailable_r10 = " + logMeasAvailable_r10_ValueToString(logMeasAvailable_r10_internal_value) + "\n";
    return out;
}

std::string RRCConnectionSetupComplete_v10xy_IEs::logMeasAvailable_r10_ToStringNoNewLines() const
{
    std::string out = "logMeasAvailable_r10=" + logMeasAvailable_r10_ValueToString(logMeasAvailable_r10_internal_value) + ",";
    return out;
}

int RRCConnectionSetupComplete_v10xy_IEs::logMeasAvailable_r10_Clear()
{
    logMeasAvailable_r10_present = false;
    return 0;
}

bool RRCConnectionSetupComplete_v10xy_IEs::logMeasAvailable_r10_IsPresent() const
{
    return logMeasAvailable_r10_present;
}

int RRCConnectionSetupComplete_v10xy_IEs::rn_SubframeConfigReq_r10_Pack(std::vector<uint8_t> &bits)
{
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((rn_SubframeConfigReq_r10_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int RRCConnectionSetupComplete_v10xy_IEs::rn_SubframeConfigReq_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return rn_SubframeConfigReq_r10_Unpack(bits, idx);
}

int RRCConnectionSetupComplete_v10xy_IEs::rn_SubframeConfigReq_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("RRCConnectionSetupComplete_v10xy_IEs::rn_SubframeConfigReq_r10_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 1)
    {
        printf("RRCConnectionSetupComplete_v10xy_IEs::rn_SubframeConfigReq_r10_Unpack() max failure\n");
        return -1;
    }
    rn_SubframeConfigReq_r10_internal_value = (rn_SubframeConfigReq_r10_Enum)packed_val;
    rn_SubframeConfigReq_r10_present = true;
    return 0;
}

RRCConnectionSetupComplete_v10xy_IEs::rn_SubframeConfigReq_r10_Enum RRCConnectionSetupComplete_v10xy_IEs::rn_SubframeConfigReq_r10_Value() const
{
    if(rn_SubframeConfigReq_r10_present)
        return rn_SubframeConfigReq_r10_internal_value;
    return (RRCConnectionSetupComplete_v10xy_IEs::rn_SubframeConfigReq_r10_Enum)0;
}

int RRCConnectionSetupComplete_v10xy_IEs::rn_SubframeConfigReq_r10_SetValue(rn_SubframeConfigReq_r10_Enum value)
{
    rn_SubframeConfigReq_r10_internal_value = value;
    rn_SubframeConfigReq_r10_present = true;
    return 0;
}

int RRCConnectionSetupComplete_v10xy_IEs::rn_SubframeConfigReq_r10_SetValue(std::string value)
{
    if("required" == value)
    {
        rn_SubframeConfigReq_r10_internal_value = k_rn_SubframeConfigReq_r10_required;
        rn_SubframeConfigReq_r10_present = true;
        return 0;
    }
    if("notRequired" == value)
    {
        rn_SubframeConfigReq_r10_internal_value = k_rn_SubframeConfigReq_r10_notRequired;
        rn_SubframeConfigReq_r10_present = true;
        return 0;
    }
    return 1;
}

std::string RRCConnectionSetupComplete_v10xy_IEs::rn_SubframeConfigReq_r10_ValueToString(rn_SubframeConfigReq_r10_Enum value) const
{
    if(k_rn_SubframeConfigReq_r10_required == value)
        return "required";
    if(k_rn_SubframeConfigReq_r10_notRequired == value)
        return "notRequired";
    return "";
}

uint64_t RRCConnectionSetupComplete_v10xy_IEs::rn_SubframeConfigReq_r10_NumberOfValues() const
{
    return 2;
}

std::string RRCConnectionSetupComplete_v10xy_IEs::rn_SubframeConfigReq_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "rn_SubframeConfigReq_r10 = " + rn_SubframeConfigReq_r10_ValueToString(rn_SubframeConfigReq_r10_internal_value) + "\n";
    return out;
}

std::string RRCConnectionSetupComplete_v10xy_IEs::rn_SubframeConfigReq_r10_ToStringNoNewLines() const
{
    std::string out = "rn_SubframeConfigReq_r10=" + rn_SubframeConfigReq_r10_ValueToString(rn_SubframeConfigReq_r10_internal_value) + ",";
    return out;
}

int RRCConnectionSetupComplete_v10xy_IEs::rn_SubframeConfigReq_r10_Clear()
{
    rn_SubframeConfigReq_r10_present = false;
    return 0;
}

bool RRCConnectionSetupComplete_v10xy_IEs::rn_SubframeConfigReq_r10_IsPresent() const
{
    return rn_SubframeConfigReq_r10_present;
}

