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

#include "PhysCellIdGERAN.h"

#include <cmath>

int PhysCellIdGERAN::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != networkColourCode_Pack(bits))
        {
            printf("PhysCellIdGERAN:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != baseStationColourCode_Pack(bits))
        {
            printf("PhysCellIdGERAN:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int PhysCellIdGERAN::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int PhysCellIdGERAN::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != networkColourCode_Unpack(bits, idx))
        {
            printf("PhysCellIdGERAN:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != baseStationColourCode_Unpack(bits, idx))
        {
            printf("PhysCellIdGERAN:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string PhysCellIdGERAN::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "PhysCellIdGERAN:\n";
    out += networkColourCode_ToString(indent+1);
    out += baseStationColourCode_ToString(indent+1);
    return out;
}

std::string PhysCellIdGERAN::ToStringNoNewLines() const
{
    std::string out = "PhysCellIdGERAN:";
    out += networkColourCode_ToStringNoNewLines();
    out += baseStationColourCode_ToStringNoNewLines();
    return out;
}

int PhysCellIdGERAN::networkColourCode_Pack(std::vector<uint8_t> &bits)
{
    if(!networkColourCode_present)
    {
        printf("PhysCellIdGERAN::networkColourCode_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 3;
    if(size < 3 || size > 3)
    {
        printf("PhysCellIdGERAN::networkColourCode_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((networkColourCode_internal_value >> (3-i-1)) & 1);
    return 0;
}

int PhysCellIdGERAN::networkColourCode_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return networkColourCode_Unpack(bits, idx);
}

int PhysCellIdGERAN::networkColourCode_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 3;
    if(size < 3 || size > 3)
    {
        printf("PhysCellIdGERAN::networkColourCode_Unpack() size failure\n");
        return -1;
    }
    networkColourCode_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("PhysCellIdGERAN::networkColourCode_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        networkColourCode_internal_value |= (uint8_t)bits[idx++] << (uint8_t)(3-i-1);
    networkColourCode_present = true;
    return 0;
}

uint8_t PhysCellIdGERAN::networkColourCode_Value() const
{
    if(networkColourCode_present)
        return networkColourCode_internal_value;
    uint8_t tmp = 0;
    return tmp;
}

int PhysCellIdGERAN::networkColourCode_SetValue(uint8_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 3)
    {
        printf("PhysCellIdGERAN::networkColourCode_SetValue() size failure\n");
        return -1;
    }
    networkColourCode_internal_value = value;
    networkColourCode_present = true;
    return 0;
}

std::string PhysCellIdGERAN::networkColourCode_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "networkColourCode = ";
    out += std::to_string(networkColourCode_internal_value);
    out += "\n";
    return out;
}

std::string PhysCellIdGERAN::networkColourCode_ToStringNoNewLines() const
{
    std::string out = "networkColourCode=";
    out += std::to_string(networkColourCode_internal_value);
    out += ",";
    return out;
}

int PhysCellIdGERAN::networkColourCode_Clear()
{
    networkColourCode_present = false;
    return 0;
}

bool PhysCellIdGERAN::networkColourCode_IsPresent() const
{
    return networkColourCode_present;
}

int PhysCellIdGERAN::baseStationColourCode_Pack(std::vector<uint8_t> &bits)
{
    if(!baseStationColourCode_present)
    {
        printf("PhysCellIdGERAN::baseStationColourCode_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 3;
    if(size < 3 || size > 3)
    {
        printf("PhysCellIdGERAN::baseStationColourCode_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((baseStationColourCode_internal_value >> (3-i-1)) & 1);
    return 0;
}

int PhysCellIdGERAN::baseStationColourCode_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return baseStationColourCode_Unpack(bits, idx);
}

int PhysCellIdGERAN::baseStationColourCode_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 3;
    if(size < 3 || size > 3)
    {
        printf("PhysCellIdGERAN::baseStationColourCode_Unpack() size failure\n");
        return -1;
    }
    baseStationColourCode_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("PhysCellIdGERAN::baseStationColourCode_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        baseStationColourCode_internal_value |= (uint8_t)bits[idx++] << (uint8_t)(3-i-1);
    baseStationColourCode_present = true;
    return 0;
}

uint8_t PhysCellIdGERAN::baseStationColourCode_Value() const
{
    if(baseStationColourCode_present)
        return baseStationColourCode_internal_value;
    uint8_t tmp = 0;
    return tmp;
}

int PhysCellIdGERAN::baseStationColourCode_SetValue(uint8_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 3)
    {
        printf("PhysCellIdGERAN::baseStationColourCode_SetValue() size failure\n");
        return -1;
    }
    baseStationColourCode_internal_value = value;
    baseStationColourCode_present = true;
    return 0;
}

std::string PhysCellIdGERAN::baseStationColourCode_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "baseStationColourCode = ";
    out += std::to_string(baseStationColourCode_internal_value);
    out += "\n";
    return out;
}

std::string PhysCellIdGERAN::baseStationColourCode_ToStringNoNewLines() const
{
    std::string out = "baseStationColourCode=";
    out += std::to_string(baseStationColourCode_internal_value);
    out += ",";
    return out;
}

int PhysCellIdGERAN::baseStationColourCode_Clear()
{
    baseStationColourCode_present = false;
    return 0;
}

bool PhysCellIdGERAN::baseStationColourCode_IsPresent() const
{
    return baseStationColourCode_present;
}

