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

#include "RegisteredMME.h"

#include <cmath>

int RegisteredMME::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(plmn_Identity_IsPresent());

    // Fields
    if(plmn_Identity_IsPresent())
    {
        if(0 != plmn_Identity.Pack(bits))
        {
            printf("RegisteredMME:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != mmegi_Pack(bits))
        {
            printf("RegisteredMME:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != mmec.Pack(bits))
        {
            printf("RegisteredMME:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int RegisteredMME::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int RegisteredMME::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("RegisteredMME::Unpack() index out of bounds for optional indiator plmn_Identity\n");
        return -1;
    }
    plmn_Identity_present = bits[idx++];

    // Fields
    if(plmn_Identity_present)
    {
        if(0 != plmn_Identity.Unpack(bits, idx))
        {
            printf("RegisteredMME:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != mmegi_Unpack(bits, idx))
        {
            printf("RegisteredMME:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != mmec.Unpack(bits, idx))
        {
            printf("RegisteredMME:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string RegisteredMME::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "RegisteredMME:\n";
    if(plmn_Identity_IsPresent())
        out += plmn_Identity_ToString(indent+1);
    out += mmegi_ToString(indent+1);
    out += mmec_ToString(indent+1);
    return out;
}

std::string RegisteredMME::ToStringNoNewLines() const
{
    std::string out = "RegisteredMME:";
    if(plmn_Identity_IsPresent())
        out += plmn_Identity_ToStringNoNewLines();
    out += mmegi_ToStringNoNewLines();
    out += mmec_ToStringNoNewLines();
    return out;
}

PLMN_Identity* RegisteredMME::plmn_Identity_Set()
{
    plmn_Identity_present = true;
    return &plmn_Identity;
}

int RegisteredMME::plmn_Identity_Set(PLMN_Identity &value)
{
    plmn_Identity_present = true;
    plmn_Identity = value;
    return 0;
}

const PLMN_Identity& RegisteredMME::plmn_Identity_Get() const
{
    return plmn_Identity;
}

std::string RegisteredMME::plmn_Identity_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "plmn_Identity:\n";
    out += plmn_Identity.ToString(indent+1);
    return out;
}

std::string RegisteredMME::plmn_Identity_ToStringNoNewLines() const
{
    std::string out = "plmn_Identity:";
    out += plmn_Identity.ToStringNoNewLines();
    return out;
}

int RegisteredMME::plmn_Identity_Clear()
{
    plmn_Identity_present = false;
    return 0;
}

bool RegisteredMME::plmn_Identity_IsPresent() const
{
    return plmn_Identity_present;
}

int RegisteredMME::mmegi_Pack(std::vector<uint8_t> &bits)
{
    if(!mmegi_present)
    {
        printf("RegisteredMME::mmegi_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 16;
    if(size < 16 || size > 16)
    {
        printf("RegisteredMME::mmegi_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((mmegi_internal_value >> (16-i-1)) & 1);
    return 0;
}

int RegisteredMME::mmegi_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return mmegi_Unpack(bits, idx);
}

int RegisteredMME::mmegi_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 16;
    if(size < 16 || size > 16)
    {
        printf("RegisteredMME::mmegi_Unpack() size failure\n");
        return -1;
    }
    mmegi_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("RegisteredMME::mmegi_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        mmegi_internal_value |= (uint16_t)bits[idx++] << (uint16_t)(16-i-1);
    mmegi_present = true;
    return 0;
}

uint16_t RegisteredMME::mmegi_Value() const
{
    if(mmegi_present)
        return mmegi_internal_value;
    uint16_t tmp = 0;
    return tmp;
}

int RegisteredMME::mmegi_SetValue(uint16_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 16)
    {
        printf("RegisteredMME::mmegi_SetValue() size failure\n");
        return -1;
    }
    mmegi_internal_value = value;
    mmegi_present = true;
    return 0;
}

std::string RegisteredMME::mmegi_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "mmegi = ";
    out += std::to_string(mmegi_internal_value);
    out += "\n";
    return out;
}

std::string RegisteredMME::mmegi_ToStringNoNewLines() const
{
    std::string out = "mmegi=";
    out += std::to_string(mmegi_internal_value);
    out += ",";
    return out;
}

int RegisteredMME::mmegi_Clear()
{
    mmegi_present = false;
    return 0;
}

bool RegisteredMME::mmegi_IsPresent() const
{
    return mmegi_present;
}

MMEC* RegisteredMME::mmec_Set()
{
    mmec_present = true;
    return &mmec;
}

int RegisteredMME::mmec_Set(MMEC &value)
{
    mmec_present = true;
    mmec = value;
    return 0;
}

const MMEC& RegisteredMME::mmec_Get() const
{
    return mmec;
}

std::string RegisteredMME::mmec_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "mmec:\n";
    out += mmec.ToString(indent+1);
    return out;
}

std::string RegisteredMME::mmec_ToStringNoNewLines() const
{
    std::string out = "mmec:";
    out += mmec.ToStringNoNewLines();
    return out;
}

int RegisteredMME::mmec_Clear()
{
    mmec_present = false;
    return 0;
}

bool RegisteredMME::mmec_IsPresent() const
{
    return mmec_present;
}

