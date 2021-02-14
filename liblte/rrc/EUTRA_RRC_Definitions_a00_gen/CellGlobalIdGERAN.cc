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

#include "CellGlobalIdGERAN.h"

#include <cmath>

int CellGlobalIdGERAN::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != plmn_Identity.Pack(bits))
        {
            printf("CellGlobalIdGERAN:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != locationAreaCode_Pack(bits))
        {
            printf("CellGlobalIdGERAN:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != cellIdentity_Pack(bits))
        {
            printf("CellGlobalIdGERAN:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int CellGlobalIdGERAN::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int CellGlobalIdGERAN::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != plmn_Identity.Unpack(bits, idx))
        {
            printf("CellGlobalIdGERAN:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != locationAreaCode_Unpack(bits, idx))
        {
            printf("CellGlobalIdGERAN:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != cellIdentity_Unpack(bits, idx))
        {
            printf("CellGlobalIdGERAN:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string CellGlobalIdGERAN::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "CellGlobalIdGERAN:\n";
    out += plmn_Identity_ToString(indent+1);
    out += locationAreaCode_ToString(indent+1);
    out += cellIdentity_ToString(indent+1);
    return out;
}

std::string CellGlobalIdGERAN::ToStringNoNewLines() const
{
    std::string out = "CellGlobalIdGERAN:";
    out += plmn_Identity_ToStringNoNewLines();
    out += locationAreaCode_ToStringNoNewLines();
    out += cellIdentity_ToStringNoNewLines();
    return out;
}

PLMN_Identity* CellGlobalIdGERAN::plmn_Identity_Set()
{
    plmn_Identity_present = true;
    return &plmn_Identity;
}

int CellGlobalIdGERAN::plmn_Identity_Set(PLMN_Identity &value)
{
    plmn_Identity_present = true;
    plmn_Identity = value;
    return 0;
}

const PLMN_Identity& CellGlobalIdGERAN::plmn_Identity_Get() const
{
    return plmn_Identity;
}

std::string CellGlobalIdGERAN::plmn_Identity_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "plmn_Identity:\n";
    out += plmn_Identity.ToString(indent+1);
    return out;
}

std::string CellGlobalIdGERAN::plmn_Identity_ToStringNoNewLines() const
{
    std::string out = "plmn_Identity:";
    out += plmn_Identity.ToStringNoNewLines();
    return out;
}

int CellGlobalIdGERAN::plmn_Identity_Clear()
{
    plmn_Identity_present = false;
    return 0;
}

bool CellGlobalIdGERAN::plmn_Identity_IsPresent() const
{
    return plmn_Identity_present;
}

int CellGlobalIdGERAN::locationAreaCode_Pack(std::vector<uint8_t> &bits)
{
    if(!locationAreaCode_present)
    {
        printf("CellGlobalIdGERAN::locationAreaCode_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 16;
    if(size < 16 || size > 16)
    {
        printf("CellGlobalIdGERAN::locationAreaCode_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((locationAreaCode_internal_value >> (16-i-1)) & 1);
    return 0;
}

int CellGlobalIdGERAN::locationAreaCode_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return locationAreaCode_Unpack(bits, idx);
}

int CellGlobalIdGERAN::locationAreaCode_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 16;
    if(size < 16 || size > 16)
    {
        printf("CellGlobalIdGERAN::locationAreaCode_Unpack() size failure\n");
        return -1;
    }
    locationAreaCode_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("CellGlobalIdGERAN::locationAreaCode_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        locationAreaCode_internal_value |= (uint16_t)bits[idx++] << (uint16_t)(16-i-1);
    locationAreaCode_present = true;
    return 0;
}

uint16_t CellGlobalIdGERAN::locationAreaCode_Value() const
{
    if(locationAreaCode_present)
        return locationAreaCode_internal_value;
    uint16_t tmp = 0;
    return tmp;
}

int CellGlobalIdGERAN::locationAreaCode_SetValue(uint16_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 16)
    {
        printf("CellGlobalIdGERAN::locationAreaCode_SetValue() size failure\n");
        return -1;
    }
    locationAreaCode_internal_value = value;
    locationAreaCode_present = true;
    return 0;
}

std::string CellGlobalIdGERAN::locationAreaCode_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "locationAreaCode = ";
    out += std::to_string(locationAreaCode_internal_value);
    out += "\n";
    return out;
}

std::string CellGlobalIdGERAN::locationAreaCode_ToStringNoNewLines() const
{
    std::string out = "locationAreaCode=";
    out += std::to_string(locationAreaCode_internal_value);
    out += ",";
    return out;
}

int CellGlobalIdGERAN::locationAreaCode_Clear()
{
    locationAreaCode_present = false;
    return 0;
}

bool CellGlobalIdGERAN::locationAreaCode_IsPresent() const
{
    return locationAreaCode_present;
}

int CellGlobalIdGERAN::cellIdentity_Pack(std::vector<uint8_t> &bits)
{
    if(!cellIdentity_present)
    {
        printf("CellGlobalIdGERAN::cellIdentity_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 16;
    if(size < 16 || size > 16)
    {
        printf("CellGlobalIdGERAN::cellIdentity_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((cellIdentity_internal_value >> (16-i-1)) & 1);
    return 0;
}

int CellGlobalIdGERAN::cellIdentity_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return cellIdentity_Unpack(bits, idx);
}

int CellGlobalIdGERAN::cellIdentity_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 16;
    if(size < 16 || size > 16)
    {
        printf("CellGlobalIdGERAN::cellIdentity_Unpack() size failure\n");
        return -1;
    }
    cellIdentity_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("CellGlobalIdGERAN::cellIdentity_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        cellIdentity_internal_value |= (uint16_t)bits[idx++] << (uint16_t)(16-i-1);
    cellIdentity_present = true;
    return 0;
}

uint16_t CellGlobalIdGERAN::cellIdentity_Value() const
{
    if(cellIdentity_present)
        return cellIdentity_internal_value;
    uint16_t tmp = 0;
    return tmp;
}

int CellGlobalIdGERAN::cellIdentity_SetValue(uint16_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 16)
    {
        printf("CellGlobalIdGERAN::cellIdentity_SetValue() size failure\n");
        return -1;
    }
    cellIdentity_internal_value = value;
    cellIdentity_present = true;
    return 0;
}

std::string CellGlobalIdGERAN::cellIdentity_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cellIdentity = ";
    out += std::to_string(cellIdentity_internal_value);
    out += "\n";
    return out;
}

std::string CellGlobalIdGERAN::cellIdentity_ToStringNoNewLines() const
{
    std::string out = "cellIdentity=";
    out += std::to_string(cellIdentity_internal_value);
    out += ",";
    return out;
}

int CellGlobalIdGERAN::cellIdentity_Clear()
{
    cellIdentity_present = false;
    return 0;
}

bool CellGlobalIdGERAN::cellIdentity_IsPresent() const
{
    return cellIdentity_present;
}

