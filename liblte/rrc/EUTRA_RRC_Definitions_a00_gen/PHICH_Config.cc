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

#include "PHICH_Config.h"

#include <cmath>

int PHICH_Config::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != phich_Duration_Pack(bits))
        {
            printf("PHICH_Config:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != phich_Resource_Pack(bits))
        {
            printf("PHICH_Config:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int PHICH_Config::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int PHICH_Config::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != phich_Duration_Unpack(bits, idx))
        {
            printf("PHICH_Config:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != phich_Resource_Unpack(bits, idx))
        {
            printf("PHICH_Config:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string PHICH_Config::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "PHICH_Config:\n";
    out += phich_Duration_ToString(indent+1);
    out += phich_Resource_ToString(indent+1);
    return out;
}

std::string PHICH_Config::ToStringNoNewLines() const
{
    std::string out = "PHICH_Config:";
    out += phich_Duration_ToStringNoNewLines();
    out += phich_Resource_ToStringNoNewLines();
    return out;
}

int PHICH_Config::phich_Duration_Pack(std::vector<uint8_t> &bits)
{
    if(!phich_Duration_present)
    {
        printf("PHICH_Config::phich_Duration_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((phich_Duration_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int PHICH_Config::phich_Duration_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return phich_Duration_Unpack(bits, idx);
}

int PHICH_Config::phich_Duration_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("PHICH_Config::phich_Duration_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 1)
    {
        printf("PHICH_Config::phich_Duration_Unpack() max failure\n");
        return -1;
    }
    phich_Duration_internal_value = (phich_Duration_Enum)packed_val;
    phich_Duration_present = true;
    return 0;
}

PHICH_Config::phich_Duration_Enum PHICH_Config::phich_Duration_Value() const
{
    if(phich_Duration_present)
        return phich_Duration_internal_value;
    return (PHICH_Config::phich_Duration_Enum)0;
}

int PHICH_Config::phich_Duration_SetValue(phich_Duration_Enum value)
{
    phich_Duration_internal_value = value;
    phich_Duration_present = true;
    return 0;
}

int PHICH_Config::phich_Duration_SetValue(std::string value)
{
    if("normal" == value)
    {
        phich_Duration_internal_value = k_phich_Duration_normal;
        phich_Duration_present = true;
        return 0;
    }
    if("extended" == value)
    {
        phich_Duration_internal_value = k_phich_Duration_extended;
        phich_Duration_present = true;
        return 0;
    }
    return 1;
}

std::string PHICH_Config::phich_Duration_ValueToString(phich_Duration_Enum value) const
{
    if(k_phich_Duration_normal == value)
        return "normal";
    if(k_phich_Duration_extended == value)
        return "extended";
    return "";
}

uint64_t PHICH_Config::phich_Duration_NumberOfValues() const
{
    return 2;
}

std::string PHICH_Config::phich_Duration_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "phich_Duration = " + phich_Duration_ValueToString(phich_Duration_internal_value) + "\n";
    return out;
}

std::string PHICH_Config::phich_Duration_ToStringNoNewLines() const
{
    std::string out = "phich_Duration=" + phich_Duration_ValueToString(phich_Duration_internal_value) + ",";
    return out;
}

int PHICH_Config::phich_Duration_Clear()
{
    phich_Duration_present = false;
    return 0;
}

bool PHICH_Config::phich_Duration_IsPresent() const
{
    return phich_Duration_present;
}

int PHICH_Config::phich_Resource_Pack(std::vector<uint8_t> &bits)
{
    if(!phich_Resource_present)
    {
        printf("PHICH_Config::phich_Resource_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 2;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((phich_Resource_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int PHICH_Config::phich_Resource_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return phich_Resource_Unpack(bits, idx);
}

int PHICH_Config::phich_Resource_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 2;
    if((idx + N_bits) > bits.size())
    {
        printf("PHICH_Config::phich_Resource_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 3)
    {
        printf("PHICH_Config::phich_Resource_Unpack() max failure\n");
        return -1;
    }
    phich_Resource_internal_value = (phich_Resource_Enum)packed_val;
    phich_Resource_present = true;
    return 0;
}

PHICH_Config::phich_Resource_Enum PHICH_Config::phich_Resource_Value() const
{
    if(phich_Resource_present)
        return phich_Resource_internal_value;
    return (PHICH_Config::phich_Resource_Enum)0;
}

int PHICH_Config::phich_Resource_SetValue(phich_Resource_Enum value)
{
    phich_Resource_internal_value = value;
    phich_Resource_present = true;
    return 0;
}

int PHICH_Config::phich_Resource_SetValue(std::string value)
{
    if("oneSixth" == value)
    {
        phich_Resource_internal_value = k_phich_Resource_oneSixth;
        phich_Resource_present = true;
        return 0;
    }
    if("half" == value)
    {
        phich_Resource_internal_value = k_phich_Resource_half;
        phich_Resource_present = true;
        return 0;
    }
    if("one" == value)
    {
        phich_Resource_internal_value = k_phich_Resource_one;
        phich_Resource_present = true;
        return 0;
    }
    if("two" == value)
    {
        phich_Resource_internal_value = k_phich_Resource_two;
        phich_Resource_present = true;
        return 0;
    }
    return 1;
}

std::string PHICH_Config::phich_Resource_ValueToString(phich_Resource_Enum value) const
{
    if(k_phich_Resource_oneSixth == value)
        return "oneSixth";
    if(k_phich_Resource_half == value)
        return "half";
    if(k_phich_Resource_one == value)
        return "one";
    if(k_phich_Resource_two == value)
        return "two";
    return "";
}

uint64_t PHICH_Config::phich_Resource_NumberOfValues() const
{
    return 4;
}

std::string PHICH_Config::phich_Resource_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "phich_Resource = " + phich_Resource_ValueToString(phich_Resource_internal_value) + "\n";
    return out;
}

std::string PHICH_Config::phich_Resource_ToStringNoNewLines() const
{
    std::string out = "phich_Resource=" + phich_Resource_ValueToString(phich_Resource_internal_value) + ",";
    return out;
}

int PHICH_Config::phich_Resource_Clear()
{
    phich_Resource_present = false;
    return 0;
}

bool PHICH_Config::phich_Resource_IsPresent() const
{
    return phich_Resource_present;
}

