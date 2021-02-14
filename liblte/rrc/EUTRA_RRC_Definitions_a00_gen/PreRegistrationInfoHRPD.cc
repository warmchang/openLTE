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

#include "PreRegistrationInfoHRPD.h"

#include <cmath>

int PreRegistrationInfoHRPD::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(preRegistrationZoneId_IsPresent());
    bits.push_back(secondaryPreRegistrationZoneIdList_IsPresent());

    // Fields
    {
        if(0 != preRegistrationAllowed_Pack(bits))
        {
            printf("PreRegistrationInfoHRPD:: field pack failure\n");
            return -1;
        }
    }
    if(preRegistrationZoneId_IsPresent())
    {
        if(0 != preRegistrationZoneId.Pack(bits))
        {
            printf("PreRegistrationInfoHRPD:: field pack failure\n");
            return -1;
        }
    }
    if(secondaryPreRegistrationZoneIdList_IsPresent())
    {
        if(0 != secondaryPreRegistrationZoneIdList.Pack(bits))
        {
            printf("PreRegistrationInfoHRPD:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int PreRegistrationInfoHRPD::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int PreRegistrationInfoHRPD::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("PreRegistrationInfoHRPD::Unpack() index out of bounds for optional indiator preRegistrationZoneId\n");
        return -1;
    }
    preRegistrationZoneId_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("PreRegistrationInfoHRPD::Unpack() index out of bounds for optional indiator secondaryPreRegistrationZoneIdList\n");
        return -1;
    }
    secondaryPreRegistrationZoneIdList_present = bits[idx++];

    // Fields
    {
        if(0 != preRegistrationAllowed_Unpack(bits, idx))
        {
            printf("PreRegistrationInfoHRPD:: field unpack failure\n");
            return -1;
        }
    }
    if(preRegistrationZoneId_present)
    {
        if(0 != preRegistrationZoneId.Unpack(bits, idx))
        {
            printf("PreRegistrationInfoHRPD:: field unpack failure\n");
            return -1;
        }
    }
    if(secondaryPreRegistrationZoneIdList_present)
    {
        if(0 != secondaryPreRegistrationZoneIdList.Unpack(bits, idx))
        {
            printf("PreRegistrationInfoHRPD:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string PreRegistrationInfoHRPD::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "PreRegistrationInfoHRPD:\n";
    out += preRegistrationAllowed_ToString(indent+1);
    if(preRegistrationZoneId_IsPresent())
        out += preRegistrationZoneId_ToString(indent+1);
    if(secondaryPreRegistrationZoneIdList_IsPresent())
        out += secondaryPreRegistrationZoneIdList_ToString(indent+1);
    return out;
}

std::string PreRegistrationInfoHRPD::ToStringNoNewLines() const
{
    std::string out = "PreRegistrationInfoHRPD:";
    out += preRegistrationAllowed_ToStringNoNewLines();
    if(preRegistrationZoneId_IsPresent())
        out += preRegistrationZoneId_ToStringNoNewLines();
    if(secondaryPreRegistrationZoneIdList_IsPresent())
        out += secondaryPreRegistrationZoneIdList_ToStringNoNewLines();
    return out;
}

int PreRegistrationInfoHRPD::preRegistrationAllowed_Pack(std::vector<uint8_t> &bits)
{
    if(!preRegistrationAllowed_present)
    {
        printf("PreRegistrationInfoHRPD::preRegistrationAllowed_Pack() presence failure\n");
        return -1;
    }
    bits.push_back(preRegistrationAllowed_internal_value);
    return 0;
}

int PreRegistrationInfoHRPD::preRegistrationAllowed_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return preRegistrationAllowed_Unpack(bits, idx);
}

int PreRegistrationInfoHRPD::preRegistrationAllowed_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    if((idx + 1) > bits.size())
    {
        printf("PreRegistrationInfoHRPD::preRegistrationAllowed_Unpack() index out of bounds\n");
        return -1;
    }
    preRegistrationAllowed_internal_value = bits[idx++];
    preRegistrationAllowed_present = true;
    return 0;
}

bool PreRegistrationInfoHRPD::preRegistrationAllowed_Value() const
{
    if(preRegistrationAllowed_present)
        return preRegistrationAllowed_internal_value;
    return false;
}

int PreRegistrationInfoHRPD::preRegistrationAllowed_SetValue(bool value)
{
    preRegistrationAllowed_internal_value = value;
    preRegistrationAllowed_present = true;
    return 0;
}

std::string PreRegistrationInfoHRPD::preRegistrationAllowed_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "preRegistrationAllowed = " + std::to_string(preRegistrationAllowed_internal_value) + "\n";
    return out;
}

std::string PreRegistrationInfoHRPD::preRegistrationAllowed_ToStringNoNewLines() const
{
    std::string out = "preRegistrationAllowed=" + std::to_string(preRegistrationAllowed_internal_value) + ",";
    return out;
}

int PreRegistrationInfoHRPD::preRegistrationAllowed_Clear()
{
    preRegistrationAllowed_present = false;
    return 0;
}

bool PreRegistrationInfoHRPD::preRegistrationAllowed_IsPresent() const
{
    return preRegistrationAllowed_present;
}

PreRegistrationZoneIdHRPD* PreRegistrationInfoHRPD::preRegistrationZoneId_Set()
{
    preRegistrationZoneId_present = true;
    return &preRegistrationZoneId;
}

int PreRegistrationInfoHRPD::preRegistrationZoneId_Set(PreRegistrationZoneIdHRPD &value)
{
    preRegistrationZoneId_present = true;
    preRegistrationZoneId = value;
    return 0;
}

const PreRegistrationZoneIdHRPD& PreRegistrationInfoHRPD::preRegistrationZoneId_Get() const
{
    return preRegistrationZoneId;
}

std::string PreRegistrationInfoHRPD::preRegistrationZoneId_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "preRegistrationZoneId:\n";
    out += preRegistrationZoneId.ToString(indent+1);
    return out;
}

std::string PreRegistrationInfoHRPD::preRegistrationZoneId_ToStringNoNewLines() const
{
    std::string out = "preRegistrationZoneId:";
    out += preRegistrationZoneId.ToStringNoNewLines();
    return out;
}

int PreRegistrationInfoHRPD::preRegistrationZoneId_Clear()
{
    preRegistrationZoneId_present = false;
    return 0;
}

bool PreRegistrationInfoHRPD::preRegistrationZoneId_IsPresent() const
{
    return preRegistrationZoneId_present;
}

SecondaryPreRegistrationZoneIdListHRPD* PreRegistrationInfoHRPD::secondaryPreRegistrationZoneIdList_Set()
{
    secondaryPreRegistrationZoneIdList_present = true;
    return &secondaryPreRegistrationZoneIdList;
}

int PreRegistrationInfoHRPD::secondaryPreRegistrationZoneIdList_Set(SecondaryPreRegistrationZoneIdListHRPD &value)
{
    secondaryPreRegistrationZoneIdList_present = true;
    secondaryPreRegistrationZoneIdList = value;
    return 0;
}

const SecondaryPreRegistrationZoneIdListHRPD& PreRegistrationInfoHRPD::secondaryPreRegistrationZoneIdList_Get() const
{
    return secondaryPreRegistrationZoneIdList;
}

std::string PreRegistrationInfoHRPD::secondaryPreRegistrationZoneIdList_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "secondaryPreRegistrationZoneIdList:\n";
    out += secondaryPreRegistrationZoneIdList.ToString(indent+1);
    return out;
}

std::string PreRegistrationInfoHRPD::secondaryPreRegistrationZoneIdList_ToStringNoNewLines() const
{
    std::string out = "secondaryPreRegistrationZoneIdList:";
    out += secondaryPreRegistrationZoneIdList.ToStringNoNewLines();
    return out;
}

int PreRegistrationInfoHRPD::secondaryPreRegistrationZoneIdList_Clear()
{
    secondaryPreRegistrationZoneIdList_present = false;
    return 0;
}

bool PreRegistrationInfoHRPD::secondaryPreRegistrationZoneIdList_IsPresent() const
{
    return secondaryPreRegistrationZoneIdList_present;
}

