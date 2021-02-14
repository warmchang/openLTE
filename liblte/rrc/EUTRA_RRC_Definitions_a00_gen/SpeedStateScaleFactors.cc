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

#include "SpeedStateScaleFactors.h"

#include <cmath>

int SpeedStateScaleFactors::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != sf_Medium_Pack(bits))
        {
            printf("SpeedStateScaleFactors:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != sf_High_Pack(bits))
        {
            printf("SpeedStateScaleFactors:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int SpeedStateScaleFactors::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int SpeedStateScaleFactors::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != sf_Medium_Unpack(bits, idx))
        {
            printf("SpeedStateScaleFactors:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != sf_High_Unpack(bits, idx))
        {
            printf("SpeedStateScaleFactors:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string SpeedStateScaleFactors::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "SpeedStateScaleFactors:\n";
    out += sf_Medium_ToString(indent+1);
    out += sf_High_ToString(indent+1);
    return out;
}

std::string SpeedStateScaleFactors::ToStringNoNewLines() const
{
    std::string out = "SpeedStateScaleFactors:";
    out += sf_Medium_ToStringNoNewLines();
    out += sf_High_ToStringNoNewLines();
    return out;
}

int SpeedStateScaleFactors::sf_Medium_Pack(std::vector<uint8_t> &bits)
{
    if(!sf_Medium_present)
    {
        printf("SpeedStateScaleFactors::sf_Medium_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 2;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((sf_Medium_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int SpeedStateScaleFactors::sf_Medium_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return sf_Medium_Unpack(bits, idx);
}

int SpeedStateScaleFactors::sf_Medium_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 2;
    if((idx + N_bits) > bits.size())
    {
        printf("SpeedStateScaleFactors::sf_Medium_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 3)
    {
        printf("SpeedStateScaleFactors::sf_Medium_Unpack() max failure\n");
        return -1;
    }
    sf_Medium_internal_value = (sf_Medium_Enum)packed_val;
    sf_Medium_present = true;
    return 0;
}

SpeedStateScaleFactors::sf_Medium_Enum SpeedStateScaleFactors::sf_Medium_Value() const
{
    if(sf_Medium_present)
        return sf_Medium_internal_value;
    return (SpeedStateScaleFactors::sf_Medium_Enum)0;
}

int SpeedStateScaleFactors::sf_Medium_SetValue(sf_Medium_Enum value)
{
    sf_Medium_internal_value = value;
    sf_Medium_present = true;
    return 0;
}

int SpeedStateScaleFactors::sf_Medium_SetValue(std::string value)
{
    if("oDot25" == value)
    {
        sf_Medium_internal_value = k_sf_Medium_oDot25;
        sf_Medium_present = true;
        return 0;
    }
    if("oDot5" == value)
    {
        sf_Medium_internal_value = k_sf_Medium_oDot5;
        sf_Medium_present = true;
        return 0;
    }
    if("oDot75" == value)
    {
        sf_Medium_internal_value = k_sf_Medium_oDot75;
        sf_Medium_present = true;
        return 0;
    }
    if("lDot0" == value)
    {
        sf_Medium_internal_value = k_sf_Medium_lDot0;
        sf_Medium_present = true;
        return 0;
    }
    return 1;
}

std::string SpeedStateScaleFactors::sf_Medium_ValueToString(sf_Medium_Enum value) const
{
    if(k_sf_Medium_oDot25 == value)
        return "oDot25";
    if(k_sf_Medium_oDot5 == value)
        return "oDot5";
    if(k_sf_Medium_oDot75 == value)
        return "oDot75";
    if(k_sf_Medium_lDot0 == value)
        return "lDot0";
    return "";
}

uint64_t SpeedStateScaleFactors::sf_Medium_NumberOfValues() const
{
    return 4;
}

std::string SpeedStateScaleFactors::sf_Medium_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "sf_Medium = " + sf_Medium_ValueToString(sf_Medium_internal_value) + "\n";
    return out;
}

std::string SpeedStateScaleFactors::sf_Medium_ToStringNoNewLines() const
{
    std::string out = "sf_Medium=" + sf_Medium_ValueToString(sf_Medium_internal_value) + ",";
    return out;
}

int SpeedStateScaleFactors::sf_Medium_Clear()
{
    sf_Medium_present = false;
    return 0;
}

bool SpeedStateScaleFactors::sf_Medium_IsPresent() const
{
    return sf_Medium_present;
}

int SpeedStateScaleFactors::sf_High_Pack(std::vector<uint8_t> &bits)
{
    if(!sf_High_present)
    {
        printf("SpeedStateScaleFactors::sf_High_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 2;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((sf_High_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int SpeedStateScaleFactors::sf_High_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return sf_High_Unpack(bits, idx);
}

int SpeedStateScaleFactors::sf_High_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 2;
    if((idx + N_bits) > bits.size())
    {
        printf("SpeedStateScaleFactors::sf_High_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 3)
    {
        printf("SpeedStateScaleFactors::sf_High_Unpack() max failure\n");
        return -1;
    }
    sf_High_internal_value = (sf_High_Enum)packed_val;
    sf_High_present = true;
    return 0;
}

SpeedStateScaleFactors::sf_High_Enum SpeedStateScaleFactors::sf_High_Value() const
{
    if(sf_High_present)
        return sf_High_internal_value;
    return (SpeedStateScaleFactors::sf_High_Enum)0;
}

int SpeedStateScaleFactors::sf_High_SetValue(sf_High_Enum value)
{
    sf_High_internal_value = value;
    sf_High_present = true;
    return 0;
}

int SpeedStateScaleFactors::sf_High_SetValue(std::string value)
{
    if("oDot25" == value)
    {
        sf_High_internal_value = k_sf_High_oDot25;
        sf_High_present = true;
        return 0;
    }
    if("oDot5" == value)
    {
        sf_High_internal_value = k_sf_High_oDot5;
        sf_High_present = true;
        return 0;
    }
    if("oDot75" == value)
    {
        sf_High_internal_value = k_sf_High_oDot75;
        sf_High_present = true;
        return 0;
    }
    if("lDot0" == value)
    {
        sf_High_internal_value = k_sf_High_lDot0;
        sf_High_present = true;
        return 0;
    }
    return 1;
}

std::string SpeedStateScaleFactors::sf_High_ValueToString(sf_High_Enum value) const
{
    if(k_sf_High_oDot25 == value)
        return "oDot25";
    if(k_sf_High_oDot5 == value)
        return "oDot5";
    if(k_sf_High_oDot75 == value)
        return "oDot75";
    if(k_sf_High_lDot0 == value)
        return "lDot0";
    return "";
}

uint64_t SpeedStateScaleFactors::sf_High_NumberOfValues() const
{
    return 4;
}

std::string SpeedStateScaleFactors::sf_High_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "sf_High = " + sf_High_ValueToString(sf_High_internal_value) + "\n";
    return out;
}

std::string SpeedStateScaleFactors::sf_High_ToStringNoNewLines() const
{
    std::string out = "sf_High=" + sf_High_ValueToString(sf_High_internal_value) + ",";
    return out;
}

int SpeedStateScaleFactors::sf_High_Clear()
{
    sf_High_present = false;
    return 0;
}

bool SpeedStateScaleFactors::sf_High_IsPresent() const
{
    return sf_High_present;
}

