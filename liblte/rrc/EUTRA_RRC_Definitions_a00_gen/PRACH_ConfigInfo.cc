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

#include "PRACH_ConfigInfo.h"

#include <cmath>

int PRACH_ConfigInfo::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != prach_ConfigIndex_Pack(bits))
        {
            printf("PRACH_ConfigInfo:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != highSpeedFlag_Pack(bits))
        {
            printf("PRACH_ConfigInfo:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != zeroCorrelationZoneConfig_Pack(bits))
        {
            printf("PRACH_ConfigInfo:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != prach_FreqOffset_Pack(bits))
        {
            printf("PRACH_ConfigInfo:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int PRACH_ConfigInfo::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int PRACH_ConfigInfo::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != prach_ConfigIndex_Unpack(bits, idx))
        {
            printf("PRACH_ConfigInfo:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != highSpeedFlag_Unpack(bits, idx))
        {
            printf("PRACH_ConfigInfo:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != zeroCorrelationZoneConfig_Unpack(bits, idx))
        {
            printf("PRACH_ConfigInfo:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != prach_FreqOffset_Unpack(bits, idx))
        {
            printf("PRACH_ConfigInfo:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string PRACH_ConfigInfo::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "PRACH_ConfigInfo:\n";
    out += prach_ConfigIndex_ToString(indent+1);
    out += highSpeedFlag_ToString(indent+1);
    out += zeroCorrelationZoneConfig_ToString(indent+1);
    out += prach_FreqOffset_ToString(indent+1);
    return out;
}

std::string PRACH_ConfigInfo::ToStringNoNewLines() const
{
    std::string out = "PRACH_ConfigInfo:";
    out += prach_ConfigIndex_ToStringNoNewLines();
    out += highSpeedFlag_ToStringNoNewLines();
    out += zeroCorrelationZoneConfig_ToStringNoNewLines();
    out += prach_FreqOffset_ToStringNoNewLines();
    return out;
}

int PRACH_ConfigInfo::prach_ConfigIndex_Pack(std::vector<uint8_t> &bits)
{
    if(!prach_ConfigIndex_present)
    {
        printf("PRACH_ConfigInfo::prach_ConfigIndex_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = prach_ConfigIndex_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (63 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int PRACH_ConfigInfo::prach_ConfigIndex_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return prach_ConfigIndex_Unpack(bits, idx);
}

int PRACH_ConfigInfo::prach_ConfigIndex_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (63 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("PRACH_ConfigInfo::prach_ConfigIndex_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    prach_ConfigIndex_internal_value = packed_val + 0;
    prach_ConfigIndex_present = true;
    return 0;
}

int64_t PRACH_ConfigInfo::prach_ConfigIndex_Value() const
{
    if(prach_ConfigIndex_present)
        return prach_ConfigIndex_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int PRACH_ConfigInfo::prach_ConfigIndex_SetValue(int64_t value)
{
    if(value < 0 || value > 63)
    {
        printf("PRACH_ConfigInfo::prach_ConfigIndex_SetValue() range failure\n");
        return -1;
    }
    prach_ConfigIndex_internal_value = value;
    prach_ConfigIndex_present = true;
    return 0;
}

std::string PRACH_ConfigInfo::prach_ConfigIndex_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "prach_ConfigIndex = " + std::to_string(prach_ConfigIndex_internal_value) + "\n";
    return out;
}

std::string PRACH_ConfigInfo::prach_ConfigIndex_ToStringNoNewLines() const
{
    std::string out = "prach_ConfigIndex=" + std::to_string(prach_ConfigIndex_internal_value) + ",";
    return out;
}

int PRACH_ConfigInfo::prach_ConfigIndex_Clear()
{
    prach_ConfigIndex_present = false;
    return 0;
}

bool PRACH_ConfigInfo::prach_ConfigIndex_IsPresent() const
{
    return prach_ConfigIndex_present;
}

int PRACH_ConfigInfo::highSpeedFlag_Pack(std::vector<uint8_t> &bits)
{
    if(!highSpeedFlag_present)
    {
        printf("PRACH_ConfigInfo::highSpeedFlag_Pack() presence failure\n");
        return -1;
    }
    bits.push_back(highSpeedFlag_internal_value);
    return 0;
}

int PRACH_ConfigInfo::highSpeedFlag_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return highSpeedFlag_Unpack(bits, idx);
}

int PRACH_ConfigInfo::highSpeedFlag_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    if((idx + 1) > bits.size())
    {
        printf("PRACH_ConfigInfo::highSpeedFlag_Unpack() index out of bounds\n");
        return -1;
    }
    highSpeedFlag_internal_value = bits[idx++];
    highSpeedFlag_present = true;
    return 0;
}

bool PRACH_ConfigInfo::highSpeedFlag_Value() const
{
    if(highSpeedFlag_present)
        return highSpeedFlag_internal_value;
    return false;
}

int PRACH_ConfigInfo::highSpeedFlag_SetValue(bool value)
{
    highSpeedFlag_internal_value = value;
    highSpeedFlag_present = true;
    return 0;
}

std::string PRACH_ConfigInfo::highSpeedFlag_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "highSpeedFlag = " + std::to_string(highSpeedFlag_internal_value) + "\n";
    return out;
}

std::string PRACH_ConfigInfo::highSpeedFlag_ToStringNoNewLines() const
{
    std::string out = "highSpeedFlag=" + std::to_string(highSpeedFlag_internal_value) + ",";
    return out;
}

int PRACH_ConfigInfo::highSpeedFlag_Clear()
{
    highSpeedFlag_present = false;
    return 0;
}

bool PRACH_ConfigInfo::highSpeedFlag_IsPresent() const
{
    return highSpeedFlag_present;
}

int PRACH_ConfigInfo::zeroCorrelationZoneConfig_Pack(std::vector<uint8_t> &bits)
{
    if(!zeroCorrelationZoneConfig_present)
    {
        printf("PRACH_ConfigInfo::zeroCorrelationZoneConfig_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = zeroCorrelationZoneConfig_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (15 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int PRACH_ConfigInfo::zeroCorrelationZoneConfig_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return zeroCorrelationZoneConfig_Unpack(bits, idx);
}

int PRACH_ConfigInfo::zeroCorrelationZoneConfig_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (15 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("PRACH_ConfigInfo::zeroCorrelationZoneConfig_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    zeroCorrelationZoneConfig_internal_value = packed_val + 0;
    zeroCorrelationZoneConfig_present = true;
    return 0;
}

int64_t PRACH_ConfigInfo::zeroCorrelationZoneConfig_Value() const
{
    if(zeroCorrelationZoneConfig_present)
        return zeroCorrelationZoneConfig_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int PRACH_ConfigInfo::zeroCorrelationZoneConfig_SetValue(int64_t value)
{
    if(value < 0 || value > 15)
    {
        printf("PRACH_ConfigInfo::zeroCorrelationZoneConfig_SetValue() range failure\n");
        return -1;
    }
    zeroCorrelationZoneConfig_internal_value = value;
    zeroCorrelationZoneConfig_present = true;
    return 0;
}

std::string PRACH_ConfigInfo::zeroCorrelationZoneConfig_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "zeroCorrelationZoneConfig = " + std::to_string(zeroCorrelationZoneConfig_internal_value) + "\n";
    return out;
}

std::string PRACH_ConfigInfo::zeroCorrelationZoneConfig_ToStringNoNewLines() const
{
    std::string out = "zeroCorrelationZoneConfig=" + std::to_string(zeroCorrelationZoneConfig_internal_value) + ",";
    return out;
}

int PRACH_ConfigInfo::zeroCorrelationZoneConfig_Clear()
{
    zeroCorrelationZoneConfig_present = false;
    return 0;
}

bool PRACH_ConfigInfo::zeroCorrelationZoneConfig_IsPresent() const
{
    return zeroCorrelationZoneConfig_present;
}

int PRACH_ConfigInfo::prach_FreqOffset_Pack(std::vector<uint8_t> &bits)
{
    if(!prach_FreqOffset_present)
    {
        printf("PRACH_ConfigInfo::prach_FreqOffset_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = prach_FreqOffset_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (94 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int PRACH_ConfigInfo::prach_FreqOffset_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return prach_FreqOffset_Unpack(bits, idx);
}

int PRACH_ConfigInfo::prach_FreqOffset_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (94 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("PRACH_ConfigInfo::prach_FreqOffset_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    prach_FreqOffset_internal_value = packed_val + 0;
    prach_FreqOffset_present = true;
    return 0;
}

int64_t PRACH_ConfigInfo::prach_FreqOffset_Value() const
{
    if(prach_FreqOffset_present)
        return prach_FreqOffset_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int PRACH_ConfigInfo::prach_FreqOffset_SetValue(int64_t value)
{
    if(value < 0 || value > 94)
    {
        printf("PRACH_ConfigInfo::prach_FreqOffset_SetValue() range failure\n");
        return -1;
    }
    prach_FreqOffset_internal_value = value;
    prach_FreqOffset_present = true;
    return 0;
}

std::string PRACH_ConfigInfo::prach_FreqOffset_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "prach_FreqOffset = " + std::to_string(prach_FreqOffset_internal_value) + "\n";
    return out;
}

std::string PRACH_ConfigInfo::prach_FreqOffset_ToStringNoNewLines() const
{
    std::string out = "prach_FreqOffset=" + std::to_string(prach_FreqOffset_internal_value) + ",";
    return out;
}

int PRACH_ConfigInfo::prach_FreqOffset_Clear()
{
    prach_FreqOffset_present = false;
    return 0;
}

bool PRACH_ConfigInfo::prach_FreqOffset_IsPresent() const
{
    return prach_FreqOffset_present;
}

