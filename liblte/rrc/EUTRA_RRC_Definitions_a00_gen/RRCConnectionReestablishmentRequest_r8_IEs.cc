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

#include "RRCConnectionReestablishmentRequest_r8_IEs.h"

#include <cmath>

int RRCConnectionReestablishmentRequest_r8_IEs::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != ue_Identity.Pack(bits))
        {
            printf("RRCConnectionReestablishmentRequest_r8_IEs:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != reestablishmentCause.Pack(bits))
        {
            printf("RRCConnectionReestablishmentRequest_r8_IEs:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != spare_Pack(bits))
        {
            printf("RRCConnectionReestablishmentRequest_r8_IEs:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int RRCConnectionReestablishmentRequest_r8_IEs::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int RRCConnectionReestablishmentRequest_r8_IEs::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != ue_Identity.Unpack(bits, idx))
        {
            printf("RRCConnectionReestablishmentRequest_r8_IEs:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != reestablishmentCause.Unpack(bits, idx))
        {
            printf("RRCConnectionReestablishmentRequest_r8_IEs:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != spare_Unpack(bits, idx))
        {
            printf("RRCConnectionReestablishmentRequest_r8_IEs:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string RRCConnectionReestablishmentRequest_r8_IEs::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "RRCConnectionReestablishmentRequest_r8_IEs:\n";
    out += ue_Identity_ToString(indent+1);
    out += reestablishmentCause_ToString(indent+1);
    out += spare_ToString(indent+1);
    return out;
}

std::string RRCConnectionReestablishmentRequest_r8_IEs::ToStringNoNewLines() const
{
    std::string out = "RRCConnectionReestablishmentRequest_r8_IEs:";
    out += ue_Identity_ToStringNoNewLines();
    out += reestablishmentCause_ToStringNoNewLines();
    out += spare_ToStringNoNewLines();
    return out;
}

ReestabUE_Identity* RRCConnectionReestablishmentRequest_r8_IEs::ue_Identity_Set()
{
    ue_Identity_present = true;
    return &ue_Identity;
}

int RRCConnectionReestablishmentRequest_r8_IEs::ue_Identity_Set(ReestabUE_Identity &value)
{
    ue_Identity_present = true;
    ue_Identity = value;
    return 0;
}

const ReestabUE_Identity& RRCConnectionReestablishmentRequest_r8_IEs::ue_Identity_Get() const
{
    return ue_Identity;
}

std::string RRCConnectionReestablishmentRequest_r8_IEs::ue_Identity_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ue_Identity:\n";
    out += ue_Identity.ToString(indent+1);
    return out;
}

std::string RRCConnectionReestablishmentRequest_r8_IEs::ue_Identity_ToStringNoNewLines() const
{
    std::string out = "ue_Identity:";
    out += ue_Identity.ToStringNoNewLines();
    return out;
}

int RRCConnectionReestablishmentRequest_r8_IEs::ue_Identity_Clear()
{
    ue_Identity_present = false;
    return 0;
}

bool RRCConnectionReestablishmentRequest_r8_IEs::ue_Identity_IsPresent() const
{
    return ue_Identity_present;
}

ReestablishmentCause* RRCConnectionReestablishmentRequest_r8_IEs::reestablishmentCause_Set()
{
    reestablishmentCause_present = true;
    return &reestablishmentCause;
}

int RRCConnectionReestablishmentRequest_r8_IEs::reestablishmentCause_Set(ReestablishmentCause &value)
{
    reestablishmentCause_present = true;
    reestablishmentCause = value;
    return 0;
}

const ReestablishmentCause& RRCConnectionReestablishmentRequest_r8_IEs::reestablishmentCause_Get() const
{
    return reestablishmentCause;
}

std::string RRCConnectionReestablishmentRequest_r8_IEs::reestablishmentCause_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "reestablishmentCause:\n";
    out += reestablishmentCause.ToString(indent+1);
    return out;
}

std::string RRCConnectionReestablishmentRequest_r8_IEs::reestablishmentCause_ToStringNoNewLines() const
{
    std::string out = "reestablishmentCause:";
    out += reestablishmentCause.ToStringNoNewLines();
    return out;
}

int RRCConnectionReestablishmentRequest_r8_IEs::reestablishmentCause_Clear()
{
    reestablishmentCause_present = false;
    return 0;
}

bool RRCConnectionReestablishmentRequest_r8_IEs::reestablishmentCause_IsPresent() const
{
    return reestablishmentCause_present;
}

int RRCConnectionReestablishmentRequest_r8_IEs::spare_Pack(std::vector<uint8_t> &bits)
{
    if(!spare_present)
    {
        printf("RRCConnectionReestablishmentRequest_r8_IEs::spare_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 2;
    if(size < 2 || size > 2)
    {
        printf("RRCConnectionReestablishmentRequest_r8_IEs::spare_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((spare_internal_value >> (2-i-1)) & 1);
    return 0;
}

int RRCConnectionReestablishmentRequest_r8_IEs::spare_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return spare_Unpack(bits, idx);
}

int RRCConnectionReestablishmentRequest_r8_IEs::spare_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 2;
    if(size < 2 || size > 2)
    {
        printf("RRCConnectionReestablishmentRequest_r8_IEs::spare_Unpack() size failure\n");
        return -1;
    }
    spare_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("RRCConnectionReestablishmentRequest_r8_IEs::spare_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        spare_internal_value |= (uint8_t)bits[idx++] << (uint8_t)(2-i-1);
    spare_present = true;
    return 0;
}

uint8_t RRCConnectionReestablishmentRequest_r8_IEs::spare_Value() const
{
    if(spare_present)
        return spare_internal_value;
    uint8_t tmp = 0;
    return tmp;
}

int RRCConnectionReestablishmentRequest_r8_IEs::spare_SetValue(uint8_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 2)
    {
        printf("RRCConnectionReestablishmentRequest_r8_IEs::spare_SetValue() size failure\n");
        return -1;
    }
    spare_internal_value = value;
    spare_present = true;
    return 0;
}

std::string RRCConnectionReestablishmentRequest_r8_IEs::spare_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "spare = ";
    out += std::to_string(spare_internal_value);
    out += "\n";
    return out;
}

std::string RRCConnectionReestablishmentRequest_r8_IEs::spare_ToStringNoNewLines() const
{
    std::string out = "spare=";
    out += std::to_string(spare_internal_value);
    out += ",";
    return out;
}

int RRCConnectionReestablishmentRequest_r8_IEs::spare_Clear()
{
    spare_present = false;
    return 0;
}

bool RRCConnectionReestablishmentRequest_r8_IEs::spare_IsPresent() const
{
    return spare_present;
}

