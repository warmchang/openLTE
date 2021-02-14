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

#include "DL_CCCH_MessageType.h"

#include <cmath>

int DL_CCCH_MessageType::Pack(std::vector<uint8_t> &bits)
{
    if(!present)
    {
        printf("DL_CCCH_MessageType::Pack() presence failure\n");
        return -1;
    }
    // Extension indicator

    // Choice
    for(uint32_t i=0; i<1; i++)
        bits.push_back((internal_choice >> (1-i-1)) & 1);

    // Fields
    if(internal_choice == k_c1)
    {
        if(0 != c1_Pack(bits))
        {
            printf("DL_CCCH_MessageType::c1 pack failure\n");
            return -1;
        }
    }
    return 0;
}

int DL_CCCH_MessageType::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int DL_CCCH_MessageType::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 1) > bits.size())
    {
        printf("DL_CCCH_MessageType::Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<1; i++)
        packed_val |= bits[idx++] << (1-i-1);

    if((DL_CCCH_MessageType::Enum)packed_val > k_messageClassExtension)
    {
        printf("DL_CCCH_MessageType::Unpack() choice range failure\n");
        return -1;
    }
    internal_choice = (DL_CCCH_MessageType::Enum)packed_val;
    present = true;

    // Fields
    if(internal_choice == k_c1)
    {
        if(0 != c1_Unpack(bits, idx))
        {
            printf("DL_CCCH_MessageType::c1 unpack failure\n");
            return -1;
        }
    }
    return 0;
}

DL_CCCH_MessageType::Enum DL_CCCH_MessageType::Choice() const
{
    if(present)
        return internal_choice;
    return (DL_CCCH_MessageType::Enum)0;
}

int DL_CCCH_MessageType::SetChoice(DL_CCCH_MessageType::Enum choice)
{
    internal_choice = choice;
    present = true;
    return 0;
}

std::string DL_CCCH_MessageType::ChoiceToString(Enum value) const
{
    if(k_c1 == value)
        return "c1";
    if(k_messageClassExtension == value)
        return "messageClassExtension";
    return "";
}

uint64_t DL_CCCH_MessageType::NumberOfChoices() const
{
    return 2;
}

std::string DL_CCCH_MessageType::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "DL_CCCH_MessageType = " + ChoiceToString(internal_choice) + ":\n";
    if(internal_choice == k_c1)
        out += c1_ToString(indent+1);
    return out;
}

std::string DL_CCCH_MessageType::ToStringNoNewLines() const
{
    std::string out = "DL_CCCH_MessageType=" + ChoiceToString(internal_choice) + ",";
    if(internal_choice == k_c1)
        out += c1_ToStringNoNewLines();
    return out;
}

int DL_CCCH_MessageType::Clear()
{
    present = false;
    return 0;
}

bool DL_CCCH_MessageType::IsPresent() const
{
    return present;
}

int DL_CCCH_MessageType::c1_Pack(std::vector<uint8_t> &bits)
{
    if(!c1_present)
    {
        printf("DL_CCCH_MessageType::c1_Pack() presence failure\n");
        return -1;
    }
    // Extension indicator

    // Choice
    for(uint32_t i=0; i<2; i++)
        bits.push_back((c1_internal_choice >> (2-i-1)) & 1);

    // Fields
    if(c1_internal_choice == k_c1_rrcConnectionReestablishment)
    {
        if(0 != c1_rrcConnectionReestablishment.Pack(bits))
        {
            printf("DL_CCCH_MessageType::c1_rrcConnectionReestablishment pack failure\n");
            return -1;
        }
    }
    if(c1_internal_choice == k_c1_rrcConnectionReestablishmentReject)
    {
        if(0 != c1_rrcConnectionReestablishmentReject.Pack(bits))
        {
            printf("DL_CCCH_MessageType::c1_rrcConnectionReestablishmentReject pack failure\n");
            return -1;
        }
    }
    if(c1_internal_choice == k_c1_rrcConnectionReject)
    {
        if(0 != c1_rrcConnectionReject.Pack(bits))
        {
            printf("DL_CCCH_MessageType::c1_rrcConnectionReject pack failure\n");
            return -1;
        }
    }
    if(c1_internal_choice == k_c1_rrcConnectionSetup)
    {
        if(0 != c1_rrcConnectionSetup.Pack(bits))
        {
            printf("DL_CCCH_MessageType::c1_rrcConnectionSetup pack failure\n");
            return -1;
        }
    }
    return 0;
}

int DL_CCCH_MessageType::c1_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return c1_Unpack(bits, idx);
}

int DL_CCCH_MessageType::c1_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 2) > bits.size())
    {
        printf("DL_CCCH_MessageType::c1_Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<2; i++)
        packed_val |= bits[idx++] << (2-i-1);

    if((DL_CCCH_MessageType::c1_Enum)packed_val > k_c1_rrcConnectionSetup)
    {
        printf("DL_CCCH_MessageType::c1_Unpack() choice range failure\n");
        return -1;
    }
    c1_internal_choice = (DL_CCCH_MessageType::c1_Enum)packed_val;
    c1_present = true;

    // Fields
    if(c1_internal_choice == k_c1_rrcConnectionReestablishment)
    {
        if(0 != c1_rrcConnectionReestablishment.Unpack(bits, idx))
        {
            printf("DL_CCCH_MessageType::c1_rrcConnectionReestablishment unpack failure\n");
            return -1;
        }
    }
    if(c1_internal_choice == k_c1_rrcConnectionReestablishmentReject)
    {
        if(0 != c1_rrcConnectionReestablishmentReject.Unpack(bits, idx))
        {
            printf("DL_CCCH_MessageType::c1_rrcConnectionReestablishmentReject unpack failure\n");
            return -1;
        }
    }
    if(c1_internal_choice == k_c1_rrcConnectionReject)
    {
        if(0 != c1_rrcConnectionReject.Unpack(bits, idx))
        {
            printf("DL_CCCH_MessageType::c1_rrcConnectionReject unpack failure\n");
            return -1;
        }
    }
    if(c1_internal_choice == k_c1_rrcConnectionSetup)
    {
        if(0 != c1_rrcConnectionSetup.Unpack(bits, idx))
        {
            printf("DL_CCCH_MessageType::c1_rrcConnectionSetup unpack failure\n");
            return -1;
        }
    }
    return 0;
}

DL_CCCH_MessageType::c1_Enum DL_CCCH_MessageType::c1_Choice() const
{
    if(c1_present)
        return c1_internal_choice;
    return (DL_CCCH_MessageType::c1_Enum)0;
}

int DL_CCCH_MessageType::c1_SetChoice(DL_CCCH_MessageType::c1_Enum choice)
{
    c1_internal_choice = choice;
    c1_present = true;
    return 0;
}

std::string DL_CCCH_MessageType::c1_ChoiceToString(c1_Enum value) const
{
    if(k_c1_rrcConnectionReestablishment == value)
        return "c1_rrcConnectionReestablishment";
    if(k_c1_rrcConnectionReestablishmentReject == value)
        return "c1_rrcConnectionReestablishmentReject";
    if(k_c1_rrcConnectionReject == value)
        return "c1_rrcConnectionReject";
    if(k_c1_rrcConnectionSetup == value)
        return "c1_rrcConnectionSetup";
    return "";
}

uint64_t DL_CCCH_MessageType::c1_NumberOfChoices() const
{
    return 4;
}

std::string DL_CCCH_MessageType::c1_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "c1 = " + c1_ChoiceToString(c1_internal_choice) + ":\n";
    if(c1_internal_choice == k_c1_rrcConnectionReestablishment)
        out += c1_rrcConnectionReestablishment.ToString(indent+1);
    if(c1_internal_choice == k_c1_rrcConnectionReestablishmentReject)
        out += c1_rrcConnectionReestablishmentReject.ToString(indent+1);
    if(c1_internal_choice == k_c1_rrcConnectionReject)
        out += c1_rrcConnectionReject.ToString(indent+1);
    if(c1_internal_choice == k_c1_rrcConnectionSetup)
        out += c1_rrcConnectionSetup.ToString(indent+1);
    return out;
}

std::string DL_CCCH_MessageType::c1_ToStringNoNewLines() const
{
    std::string out = "c1=" + c1_ChoiceToString(c1_internal_choice) + ",";
    if(c1_internal_choice == k_c1_rrcConnectionReestablishment)
        out += c1_rrcConnectionReestablishment.ToStringNoNewLines();
    if(c1_internal_choice == k_c1_rrcConnectionReestablishmentReject)
        out += c1_rrcConnectionReestablishmentReject.ToStringNoNewLines();
    if(c1_internal_choice == k_c1_rrcConnectionReject)
        out += c1_rrcConnectionReject.ToStringNoNewLines();
    if(c1_internal_choice == k_c1_rrcConnectionSetup)
        out += c1_rrcConnectionSetup.ToStringNoNewLines();
    return out;
}

int DL_CCCH_MessageType::c1_Clear()
{
    c1_present = false;
    return 0;
}

bool DL_CCCH_MessageType::c1_IsPresent() const
{
    return c1_present;
}

RRCConnectionReestablishment* DL_CCCH_MessageType::c1_rrcConnectionReestablishment_Set()
{
    c1_rrcConnectionReestablishment_present = true;
    return &c1_rrcConnectionReestablishment;
}

int DL_CCCH_MessageType::c1_rrcConnectionReestablishment_Set(RRCConnectionReestablishment &value)
{
    c1_rrcConnectionReestablishment_present = true;
    c1_rrcConnectionReestablishment = value;
    return 0;
}

const RRCConnectionReestablishment& DL_CCCH_MessageType::c1_rrcConnectionReestablishment_Get() const
{
    return c1_rrcConnectionReestablishment;
}

std::string DL_CCCH_MessageType::c1_rrcConnectionReestablishment_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "rrcConnectionReestablishment:\n";
    out += c1_rrcConnectionReestablishment.ToString(indent+1);
    return out;
}

std::string DL_CCCH_MessageType::c1_rrcConnectionReestablishment_ToStringNoNewLines() const
{
    std::string out = "rrcConnectionReestablishment:";
    out += c1_rrcConnectionReestablishment.ToStringNoNewLines();
    return out;
}

int DL_CCCH_MessageType::c1_rrcConnectionReestablishment_Clear()
{
    c1_rrcConnectionReestablishment_present = false;
    return 0;
}

bool DL_CCCH_MessageType::c1_rrcConnectionReestablishment_IsPresent() const
{
    return c1_rrcConnectionReestablishment_present;
}

RRCConnectionReestablishmentReject* DL_CCCH_MessageType::c1_rrcConnectionReestablishmentReject_Set()
{
    c1_rrcConnectionReestablishmentReject_present = true;
    return &c1_rrcConnectionReestablishmentReject;
}

int DL_CCCH_MessageType::c1_rrcConnectionReestablishmentReject_Set(RRCConnectionReestablishmentReject &value)
{
    c1_rrcConnectionReestablishmentReject_present = true;
    c1_rrcConnectionReestablishmentReject = value;
    return 0;
}

const RRCConnectionReestablishmentReject& DL_CCCH_MessageType::c1_rrcConnectionReestablishmentReject_Get() const
{
    return c1_rrcConnectionReestablishmentReject;
}

std::string DL_CCCH_MessageType::c1_rrcConnectionReestablishmentReject_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "rrcConnectionReestablishmentReject:\n";
    out += c1_rrcConnectionReestablishmentReject.ToString(indent+1);
    return out;
}

std::string DL_CCCH_MessageType::c1_rrcConnectionReestablishmentReject_ToStringNoNewLines() const
{
    std::string out = "rrcConnectionReestablishmentReject:";
    out += c1_rrcConnectionReestablishmentReject.ToStringNoNewLines();
    return out;
}

int DL_CCCH_MessageType::c1_rrcConnectionReestablishmentReject_Clear()
{
    c1_rrcConnectionReestablishmentReject_present = false;
    return 0;
}

bool DL_CCCH_MessageType::c1_rrcConnectionReestablishmentReject_IsPresent() const
{
    return c1_rrcConnectionReestablishmentReject_present;
}

RRCConnectionReject* DL_CCCH_MessageType::c1_rrcConnectionReject_Set()
{
    c1_rrcConnectionReject_present = true;
    return &c1_rrcConnectionReject;
}

int DL_CCCH_MessageType::c1_rrcConnectionReject_Set(RRCConnectionReject &value)
{
    c1_rrcConnectionReject_present = true;
    c1_rrcConnectionReject = value;
    return 0;
}

const RRCConnectionReject& DL_CCCH_MessageType::c1_rrcConnectionReject_Get() const
{
    return c1_rrcConnectionReject;
}

std::string DL_CCCH_MessageType::c1_rrcConnectionReject_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "rrcConnectionReject:\n";
    out += c1_rrcConnectionReject.ToString(indent+1);
    return out;
}

std::string DL_CCCH_MessageType::c1_rrcConnectionReject_ToStringNoNewLines() const
{
    std::string out = "rrcConnectionReject:";
    out += c1_rrcConnectionReject.ToStringNoNewLines();
    return out;
}

int DL_CCCH_MessageType::c1_rrcConnectionReject_Clear()
{
    c1_rrcConnectionReject_present = false;
    return 0;
}

bool DL_CCCH_MessageType::c1_rrcConnectionReject_IsPresent() const
{
    return c1_rrcConnectionReject_present;
}

RRCConnectionSetup* DL_CCCH_MessageType::c1_rrcConnectionSetup_Set()
{
    c1_rrcConnectionSetup_present = true;
    return &c1_rrcConnectionSetup;
}

int DL_CCCH_MessageType::c1_rrcConnectionSetup_Set(RRCConnectionSetup &value)
{
    c1_rrcConnectionSetup_present = true;
    c1_rrcConnectionSetup = value;
    return 0;
}

const RRCConnectionSetup& DL_CCCH_MessageType::c1_rrcConnectionSetup_Get() const
{
    return c1_rrcConnectionSetup;
}

std::string DL_CCCH_MessageType::c1_rrcConnectionSetup_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "rrcConnectionSetup:\n";
    out += c1_rrcConnectionSetup.ToString(indent+1);
    return out;
}

std::string DL_CCCH_MessageType::c1_rrcConnectionSetup_ToStringNoNewLines() const
{
    std::string out = "rrcConnectionSetup:";
    out += c1_rrcConnectionSetup.ToStringNoNewLines();
    return out;
}

int DL_CCCH_MessageType::c1_rrcConnectionSetup_Clear()
{
    c1_rrcConnectionSetup_present = false;
    return 0;
}

bool DL_CCCH_MessageType::c1_rrcConnectionSetup_IsPresent() const
{
    return c1_rrcConnectionSetup_present;
}

