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

#include "CSG_ProximityIndicationParameters_r9.h"

#include <cmath>

int CSG_ProximityIndicationParameters_r9::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(intraFreqProximityIndication_r9_IsPresent());
    bits.push_back(interFreqProximityIndication_r9_IsPresent());
    bits.push_back(utran_ProximityIndication_r9_IsPresent());

    // Fields
    if(intraFreqProximityIndication_r9_IsPresent())
    {
        if(0 != intraFreqProximityIndication_r9_Pack(bits))
        {
            printf("CSG_ProximityIndicationParameters_r9:: field pack failure\n");
            return -1;
        }
    }
    if(interFreqProximityIndication_r9_IsPresent())
    {
        if(0 != interFreqProximityIndication_r9_Pack(bits))
        {
            printf("CSG_ProximityIndicationParameters_r9:: field pack failure\n");
            return -1;
        }
    }
    if(utran_ProximityIndication_r9_IsPresent())
    {
        if(0 != utran_ProximityIndication_r9_Pack(bits))
        {
            printf("CSG_ProximityIndicationParameters_r9:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int CSG_ProximityIndicationParameters_r9::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int CSG_ProximityIndicationParameters_r9::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("CSG_ProximityIndicationParameters_r9::Unpack() index out of bounds for optional indiator intraFreqProximityIndication_r9\n");
        return -1;
    }
    intraFreqProximityIndication_r9_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("CSG_ProximityIndicationParameters_r9::Unpack() index out of bounds for optional indiator interFreqProximityIndication_r9\n");
        return -1;
    }
    interFreqProximityIndication_r9_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("CSG_ProximityIndicationParameters_r9::Unpack() index out of bounds for optional indiator utran_ProximityIndication_r9\n");
        return -1;
    }
    utran_ProximityIndication_r9_present = bits[idx++];

    // Fields
    if(intraFreqProximityIndication_r9_present)
    {
        if(0 != intraFreqProximityIndication_r9_Unpack(bits, idx))
        {
            printf("CSG_ProximityIndicationParameters_r9:: field unpack failure\n");
            return -1;
        }
    }
    if(interFreqProximityIndication_r9_present)
    {
        if(0 != interFreqProximityIndication_r9_Unpack(bits, idx))
        {
            printf("CSG_ProximityIndicationParameters_r9:: field unpack failure\n");
            return -1;
        }
    }
    if(utran_ProximityIndication_r9_present)
    {
        if(0 != utran_ProximityIndication_r9_Unpack(bits, idx))
        {
            printf("CSG_ProximityIndicationParameters_r9:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string CSG_ProximityIndicationParameters_r9::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "CSG_ProximityIndicationParameters_r9:\n";
    if(intraFreqProximityIndication_r9_IsPresent())
        out += intraFreqProximityIndication_r9_ToString(indent+1);
    if(interFreqProximityIndication_r9_IsPresent())
        out += interFreqProximityIndication_r9_ToString(indent+1);
    if(utran_ProximityIndication_r9_IsPresent())
        out += utran_ProximityIndication_r9_ToString(indent+1);
    return out;
}

std::string CSG_ProximityIndicationParameters_r9::ToStringNoNewLines() const
{
    std::string out = "CSG_ProximityIndicationParameters_r9:";
    if(intraFreqProximityIndication_r9_IsPresent())
        out += intraFreqProximityIndication_r9_ToStringNoNewLines();
    if(interFreqProximityIndication_r9_IsPresent())
        out += interFreqProximityIndication_r9_ToStringNoNewLines();
    if(utran_ProximityIndication_r9_IsPresent())
        out += utran_ProximityIndication_r9_ToStringNoNewLines();
    return out;
}

int CSG_ProximityIndicationParameters_r9::intraFreqProximityIndication_r9_Pack(std::vector<uint8_t> &bits)
{
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((intraFreqProximityIndication_r9_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int CSG_ProximityIndicationParameters_r9::intraFreqProximityIndication_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return intraFreqProximityIndication_r9_Unpack(bits, idx);
}

int CSG_ProximityIndicationParameters_r9::intraFreqProximityIndication_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("CSG_ProximityIndicationParameters_r9::intraFreqProximityIndication_r9_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 0)
    {
        printf("CSG_ProximityIndicationParameters_r9::intraFreqProximityIndication_r9_Unpack() max failure\n");
        return -1;
    }
    intraFreqProximityIndication_r9_internal_value = (intraFreqProximityIndication_r9_Enum)packed_val;
    intraFreqProximityIndication_r9_present = true;
    return 0;
}

CSG_ProximityIndicationParameters_r9::intraFreqProximityIndication_r9_Enum CSG_ProximityIndicationParameters_r9::intraFreqProximityIndication_r9_Value() const
{
    if(intraFreqProximityIndication_r9_present)
        return intraFreqProximityIndication_r9_internal_value;
    return (CSG_ProximityIndicationParameters_r9::intraFreqProximityIndication_r9_Enum)0;
}

int CSG_ProximityIndicationParameters_r9::intraFreqProximityIndication_r9_SetValue(intraFreqProximityIndication_r9_Enum value)
{
    intraFreqProximityIndication_r9_internal_value = value;
    intraFreqProximityIndication_r9_present = true;
    return 0;
}

int CSG_ProximityIndicationParameters_r9::intraFreqProximityIndication_r9_SetValue(std::string value)
{
    if("supported" == value)
    {
        intraFreqProximityIndication_r9_internal_value = k_intraFreqProximityIndication_r9_supported;
        intraFreqProximityIndication_r9_present = true;
        return 0;
    }
    return 1;
}

std::string CSG_ProximityIndicationParameters_r9::intraFreqProximityIndication_r9_ValueToString(intraFreqProximityIndication_r9_Enum value) const
{
    if(k_intraFreqProximityIndication_r9_supported == value)
        return "supported";
    return "";
}

uint64_t CSG_ProximityIndicationParameters_r9::intraFreqProximityIndication_r9_NumberOfValues() const
{
    return 1;
}

std::string CSG_ProximityIndicationParameters_r9::intraFreqProximityIndication_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "intraFreqProximityIndication_r9 = " + intraFreqProximityIndication_r9_ValueToString(intraFreqProximityIndication_r9_internal_value) + "\n";
    return out;
}

std::string CSG_ProximityIndicationParameters_r9::intraFreqProximityIndication_r9_ToStringNoNewLines() const
{
    std::string out = "intraFreqProximityIndication_r9=" + intraFreqProximityIndication_r9_ValueToString(intraFreqProximityIndication_r9_internal_value) + ",";
    return out;
}

int CSG_ProximityIndicationParameters_r9::intraFreqProximityIndication_r9_Clear()
{
    intraFreqProximityIndication_r9_present = false;
    return 0;
}

bool CSG_ProximityIndicationParameters_r9::intraFreqProximityIndication_r9_IsPresent() const
{
    return intraFreqProximityIndication_r9_present;
}

int CSG_ProximityIndicationParameters_r9::interFreqProximityIndication_r9_Pack(std::vector<uint8_t> &bits)
{
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((interFreqProximityIndication_r9_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int CSG_ProximityIndicationParameters_r9::interFreqProximityIndication_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return interFreqProximityIndication_r9_Unpack(bits, idx);
}

int CSG_ProximityIndicationParameters_r9::interFreqProximityIndication_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("CSG_ProximityIndicationParameters_r9::interFreqProximityIndication_r9_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 0)
    {
        printf("CSG_ProximityIndicationParameters_r9::interFreqProximityIndication_r9_Unpack() max failure\n");
        return -1;
    }
    interFreqProximityIndication_r9_internal_value = (interFreqProximityIndication_r9_Enum)packed_val;
    interFreqProximityIndication_r9_present = true;
    return 0;
}

CSG_ProximityIndicationParameters_r9::interFreqProximityIndication_r9_Enum CSG_ProximityIndicationParameters_r9::interFreqProximityIndication_r9_Value() const
{
    if(interFreqProximityIndication_r9_present)
        return interFreqProximityIndication_r9_internal_value;
    return (CSG_ProximityIndicationParameters_r9::interFreqProximityIndication_r9_Enum)0;
}

int CSG_ProximityIndicationParameters_r9::interFreqProximityIndication_r9_SetValue(interFreqProximityIndication_r9_Enum value)
{
    interFreqProximityIndication_r9_internal_value = value;
    interFreqProximityIndication_r9_present = true;
    return 0;
}

int CSG_ProximityIndicationParameters_r9::interFreqProximityIndication_r9_SetValue(std::string value)
{
    if("supported" == value)
    {
        interFreqProximityIndication_r9_internal_value = k_interFreqProximityIndication_r9_supported;
        interFreqProximityIndication_r9_present = true;
        return 0;
    }
    return 1;
}

std::string CSG_ProximityIndicationParameters_r9::interFreqProximityIndication_r9_ValueToString(interFreqProximityIndication_r9_Enum value) const
{
    if(k_interFreqProximityIndication_r9_supported == value)
        return "supported";
    return "";
}

uint64_t CSG_ProximityIndicationParameters_r9::interFreqProximityIndication_r9_NumberOfValues() const
{
    return 1;
}

std::string CSG_ProximityIndicationParameters_r9::interFreqProximityIndication_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "interFreqProximityIndication_r9 = " + interFreqProximityIndication_r9_ValueToString(interFreqProximityIndication_r9_internal_value) + "\n";
    return out;
}

std::string CSG_ProximityIndicationParameters_r9::interFreqProximityIndication_r9_ToStringNoNewLines() const
{
    std::string out = "interFreqProximityIndication_r9=" + interFreqProximityIndication_r9_ValueToString(interFreqProximityIndication_r9_internal_value) + ",";
    return out;
}

int CSG_ProximityIndicationParameters_r9::interFreqProximityIndication_r9_Clear()
{
    interFreqProximityIndication_r9_present = false;
    return 0;
}

bool CSG_ProximityIndicationParameters_r9::interFreqProximityIndication_r9_IsPresent() const
{
    return interFreqProximityIndication_r9_present;
}

int CSG_ProximityIndicationParameters_r9::utran_ProximityIndication_r9_Pack(std::vector<uint8_t> &bits)
{
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((utran_ProximityIndication_r9_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int CSG_ProximityIndicationParameters_r9::utran_ProximityIndication_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return utran_ProximityIndication_r9_Unpack(bits, idx);
}

int CSG_ProximityIndicationParameters_r9::utran_ProximityIndication_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("CSG_ProximityIndicationParameters_r9::utran_ProximityIndication_r9_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 0)
    {
        printf("CSG_ProximityIndicationParameters_r9::utran_ProximityIndication_r9_Unpack() max failure\n");
        return -1;
    }
    utran_ProximityIndication_r9_internal_value = (utran_ProximityIndication_r9_Enum)packed_val;
    utran_ProximityIndication_r9_present = true;
    return 0;
}

CSG_ProximityIndicationParameters_r9::utran_ProximityIndication_r9_Enum CSG_ProximityIndicationParameters_r9::utran_ProximityIndication_r9_Value() const
{
    if(utran_ProximityIndication_r9_present)
        return utran_ProximityIndication_r9_internal_value;
    return (CSG_ProximityIndicationParameters_r9::utran_ProximityIndication_r9_Enum)0;
}

int CSG_ProximityIndicationParameters_r9::utran_ProximityIndication_r9_SetValue(utran_ProximityIndication_r9_Enum value)
{
    utran_ProximityIndication_r9_internal_value = value;
    utran_ProximityIndication_r9_present = true;
    return 0;
}

int CSG_ProximityIndicationParameters_r9::utran_ProximityIndication_r9_SetValue(std::string value)
{
    if("supported" == value)
    {
        utran_ProximityIndication_r9_internal_value = k_utran_ProximityIndication_r9_supported;
        utran_ProximityIndication_r9_present = true;
        return 0;
    }
    return 1;
}

std::string CSG_ProximityIndicationParameters_r9::utran_ProximityIndication_r9_ValueToString(utran_ProximityIndication_r9_Enum value) const
{
    if(k_utran_ProximityIndication_r9_supported == value)
        return "supported";
    return "";
}

uint64_t CSG_ProximityIndicationParameters_r9::utran_ProximityIndication_r9_NumberOfValues() const
{
    return 1;
}

std::string CSG_ProximityIndicationParameters_r9::utran_ProximityIndication_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "utran_ProximityIndication_r9 = " + utran_ProximityIndication_r9_ValueToString(utran_ProximityIndication_r9_internal_value) + "\n";
    return out;
}

std::string CSG_ProximityIndicationParameters_r9::utran_ProximityIndication_r9_ToStringNoNewLines() const
{
    std::string out = "utran_ProximityIndication_r9=" + utran_ProximityIndication_r9_ValueToString(utran_ProximityIndication_r9_internal_value) + ",";
    return out;
}

int CSG_ProximityIndicationParameters_r9::utran_ProximityIndication_r9_Clear()
{
    utran_ProximityIndication_r9_present = false;
    return 0;
}

bool CSG_ProximityIndicationParameters_r9::utran_ProximityIndication_r9_IsPresent() const
{
    return utran_ProximityIndication_r9_present;
}

