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

#include "RRCConnectionRequest_r8_IEs.h"

#include <cmath>

int RRCConnectionRequest_r8_IEs::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != ue_Identity.Pack(bits))
        {
            printf("RRCConnectionRequest_r8_IEs:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != establishmentCause.Pack(bits))
        {
            printf("RRCConnectionRequest_r8_IEs:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != spare_Pack(bits))
        {
            printf("RRCConnectionRequest_r8_IEs:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int RRCConnectionRequest_r8_IEs::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int RRCConnectionRequest_r8_IEs::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != ue_Identity.Unpack(bits, idx))
        {
            printf("RRCConnectionRequest_r8_IEs:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != establishmentCause.Unpack(bits, idx))
        {
            printf("RRCConnectionRequest_r8_IEs:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != spare_Unpack(bits, idx))
        {
            printf("RRCConnectionRequest_r8_IEs:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string RRCConnectionRequest_r8_IEs::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "RRCConnectionRequest_r8_IEs:\n";
    out += ue_Identity_ToString(indent+1);
    out += establishmentCause_ToString(indent+1);
    out += spare_ToString(indent+1);
    return out;
}

std::string RRCConnectionRequest_r8_IEs::ToStringNoNewLines() const
{
    std::string out = "RRCConnectionRequest_r8_IEs:";
    out += ue_Identity_ToStringNoNewLines();
    out += establishmentCause_ToStringNoNewLines();
    out += spare_ToStringNoNewLines();
    return out;
}

InitialUE_Identity* RRCConnectionRequest_r8_IEs::ue_Identity_Set()
{
    ue_Identity_present = true;
    return &ue_Identity;
}

int RRCConnectionRequest_r8_IEs::ue_Identity_Set(InitialUE_Identity &value)
{
    ue_Identity_present = true;
    ue_Identity = value;
    return 0;
}

const InitialUE_Identity& RRCConnectionRequest_r8_IEs::ue_Identity_Get() const
{
    return ue_Identity;
}

std::string RRCConnectionRequest_r8_IEs::ue_Identity_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ue_Identity:\n";
    out += ue_Identity.ToString(indent+1);
    return out;
}

std::string RRCConnectionRequest_r8_IEs::ue_Identity_ToStringNoNewLines() const
{
    std::string out = "ue_Identity:";
    out += ue_Identity.ToStringNoNewLines();
    return out;
}

int RRCConnectionRequest_r8_IEs::ue_Identity_Clear()
{
    ue_Identity_present = false;
    return 0;
}

bool RRCConnectionRequest_r8_IEs::ue_Identity_IsPresent() const
{
    return ue_Identity_present;
}

EstablishmentCause* RRCConnectionRequest_r8_IEs::establishmentCause_Set()
{
    establishmentCause_present = true;
    return &establishmentCause;
}

int RRCConnectionRequest_r8_IEs::establishmentCause_Set(EstablishmentCause &value)
{
    establishmentCause_present = true;
    establishmentCause = value;
    return 0;
}

const EstablishmentCause& RRCConnectionRequest_r8_IEs::establishmentCause_Get() const
{
    return establishmentCause;
}

std::string RRCConnectionRequest_r8_IEs::establishmentCause_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "establishmentCause:\n";
    out += establishmentCause.ToString(indent+1);
    return out;
}

std::string RRCConnectionRequest_r8_IEs::establishmentCause_ToStringNoNewLines() const
{
    std::string out = "establishmentCause:";
    out += establishmentCause.ToStringNoNewLines();
    return out;
}

int RRCConnectionRequest_r8_IEs::establishmentCause_Clear()
{
    establishmentCause_present = false;
    return 0;
}

bool RRCConnectionRequest_r8_IEs::establishmentCause_IsPresent() const
{
    return establishmentCause_present;
}

int RRCConnectionRequest_r8_IEs::spare_Pack(std::vector<uint8_t> &bits)
{
    if(!spare_present)
    {
        printf("RRCConnectionRequest_r8_IEs::spare_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 1;
    if(size < 1 || size > 1)
    {
        printf("RRCConnectionRequest_r8_IEs::spare_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((spare_internal_value >> (1-i-1)) & 1);
    return 0;
}

int RRCConnectionRequest_r8_IEs::spare_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return spare_Unpack(bits, idx);
}

int RRCConnectionRequest_r8_IEs::spare_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 1;
    if(size < 1 || size > 1)
    {
        printf("RRCConnectionRequest_r8_IEs::spare_Unpack() size failure\n");
        return -1;
    }
    spare_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("RRCConnectionRequest_r8_IEs::spare_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        spare_internal_value |= (uint8_t)bits[idx++] << (uint8_t)(1-i-1);
    spare_present = true;
    return 0;
}

uint8_t RRCConnectionRequest_r8_IEs::spare_Value() const
{
    if(spare_present)
        return spare_internal_value;
    uint8_t tmp = 0;
    return tmp;
}

int RRCConnectionRequest_r8_IEs::spare_SetValue(uint8_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 1)
    {
        printf("RRCConnectionRequest_r8_IEs::spare_SetValue() size failure\n");
        return -1;
    }
    spare_internal_value = value;
    spare_present = true;
    return 0;
}

std::string RRCConnectionRequest_r8_IEs::spare_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "spare = ";
    out += std::to_string(spare_internal_value);
    out += "\n";
    return out;
}

std::string RRCConnectionRequest_r8_IEs::spare_ToStringNoNewLines() const
{
    std::string out = "spare=";
    out += std::to_string(spare_internal_value);
    out += ",";
    return out;
}

int RRCConnectionRequest_r8_IEs::spare_Clear()
{
    spare_present = false;
    return 0;
}

bool RRCConnectionRequest_r8_IEs::spare_IsPresent() const
{
    return spare_present;
}

