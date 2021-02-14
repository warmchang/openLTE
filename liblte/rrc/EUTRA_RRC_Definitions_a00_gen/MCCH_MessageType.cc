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

#include "MCCH_MessageType.h"

#include <cmath>

int MCCH_MessageType::Pack(std::vector<uint8_t> &bits)
{
    if(!present)
    {
        printf("MCCH_MessageType::Pack() presence failure\n");
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
            printf("MCCH_MessageType::c1 pack failure\n");
            return -1;
        }
    }
    return 0;
}

int MCCH_MessageType::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int MCCH_MessageType::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 1) > bits.size())
    {
        printf("MCCH_MessageType::Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<1; i++)
        packed_val |= bits[idx++] << (1-i-1);

    if((MCCH_MessageType::Enum)packed_val > k_messageClassExtension)
    {
        printf("MCCH_MessageType::Unpack() choice range failure\n");
        return -1;
    }
    internal_choice = (MCCH_MessageType::Enum)packed_val;
    present = true;

    // Fields
    if(internal_choice == k_c1)
    {
        if(0 != c1_Unpack(bits, idx))
        {
            printf("MCCH_MessageType::c1 unpack failure\n");
            return -1;
        }
    }
    return 0;
}

MCCH_MessageType::Enum MCCH_MessageType::Choice() const
{
    if(present)
        return internal_choice;
    return (MCCH_MessageType::Enum)0;
}

int MCCH_MessageType::SetChoice(MCCH_MessageType::Enum choice)
{
    internal_choice = choice;
    present = true;
    return 0;
}

std::string MCCH_MessageType::ChoiceToString(Enum value) const
{
    if(k_c1 == value)
        return "c1";
    if(k_messageClassExtension == value)
        return "messageClassExtension";
    return "";
}

uint64_t MCCH_MessageType::NumberOfChoices() const
{
    return 2;
}

std::string MCCH_MessageType::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "MCCH_MessageType = " + ChoiceToString(internal_choice) + ":\n";
    if(internal_choice == k_c1)
        out += c1_ToString(indent+1);
    return out;
}

std::string MCCH_MessageType::ToStringNoNewLines() const
{
    std::string out = "MCCH_MessageType=" + ChoiceToString(internal_choice) + ",";
    if(internal_choice == k_c1)
        out += c1_ToStringNoNewLines();
    return out;
}

int MCCH_MessageType::Clear()
{
    present = false;
    return 0;
}

bool MCCH_MessageType::IsPresent() const
{
    return present;
}

int MCCH_MessageType::c1_Pack(std::vector<uint8_t> &bits)
{
    if(!c1_present)
    {
        printf("MCCH_MessageType::c1_Pack() presence failure\n");
        return -1;
    }
    // Extension indicator

    // Choice

    // Fields
    if(c1_internal_choice == k_c1_mbsfnAreaConfiguration_r9)
    {
        if(0 != c1_mbsfnAreaConfiguration_r9.Pack(bits))
        {
            printf("MCCH_MessageType::c1_mbsfnAreaConfiguration_r9 pack failure\n");
            return -1;
        }
    }
    return 0;
}

int MCCH_MessageType::c1_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return c1_Unpack(bits, idx);
}

int MCCH_MessageType::c1_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    c1_internal_choice = (MCCH_MessageType::c1_Enum)0;
    c1_present = true;

    // Fields
    if(c1_internal_choice == k_c1_mbsfnAreaConfiguration_r9)
    {
        if(0 != c1_mbsfnAreaConfiguration_r9.Unpack(bits, idx))
        {
            printf("MCCH_MessageType::c1_mbsfnAreaConfiguration_r9 unpack failure\n");
            return -1;
        }
    }
    return 0;
}

MCCH_MessageType::c1_Enum MCCH_MessageType::c1_Choice() const
{
    if(c1_present)
        return c1_internal_choice;
    return (MCCH_MessageType::c1_Enum)0;
}

int MCCH_MessageType::c1_SetChoice(MCCH_MessageType::c1_Enum choice)
{
    c1_internal_choice = choice;
    c1_present = true;
    return 0;
}

std::string MCCH_MessageType::c1_ChoiceToString(c1_Enum value) const
{
    if(k_c1_mbsfnAreaConfiguration_r9 == value)
        return "c1_mbsfnAreaConfiguration_r9";
    return "";
}

uint64_t MCCH_MessageType::c1_NumberOfChoices() const
{
    return 1;
}

std::string MCCH_MessageType::c1_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "c1 = " + c1_ChoiceToString(c1_internal_choice) + ":\n";
    if(c1_internal_choice == k_c1_mbsfnAreaConfiguration_r9)
        out += c1_mbsfnAreaConfiguration_r9.ToString(indent+1);
    return out;
}

std::string MCCH_MessageType::c1_ToStringNoNewLines() const
{
    std::string out = "c1=" + c1_ChoiceToString(c1_internal_choice) + ",";
    if(c1_internal_choice == k_c1_mbsfnAreaConfiguration_r9)
        out += c1_mbsfnAreaConfiguration_r9.ToStringNoNewLines();
    return out;
}

int MCCH_MessageType::c1_Clear()
{
    c1_present = false;
    return 0;
}

bool MCCH_MessageType::c1_IsPresent() const
{
    return c1_present;
}

MBSFNAreaConfiguration_r9* MCCH_MessageType::c1_mbsfnAreaConfiguration_r9_Set()
{
    c1_mbsfnAreaConfiguration_r9_present = true;
    return &c1_mbsfnAreaConfiguration_r9;
}

int MCCH_MessageType::c1_mbsfnAreaConfiguration_r9_Set(MBSFNAreaConfiguration_r9 &value)
{
    c1_mbsfnAreaConfiguration_r9_present = true;
    c1_mbsfnAreaConfiguration_r9 = value;
    return 0;
}

const MBSFNAreaConfiguration_r9& MCCH_MessageType::c1_mbsfnAreaConfiguration_r9_Get() const
{
    return c1_mbsfnAreaConfiguration_r9;
}

std::string MCCH_MessageType::c1_mbsfnAreaConfiguration_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "mbsfnAreaConfiguration_r9:\n";
    out += c1_mbsfnAreaConfiguration_r9.ToString(indent+1);
    return out;
}

std::string MCCH_MessageType::c1_mbsfnAreaConfiguration_r9_ToStringNoNewLines() const
{
    std::string out = "mbsfnAreaConfiguration_r9:";
    out += c1_mbsfnAreaConfiguration_r9.ToStringNoNewLines();
    return out;
}

int MCCH_MessageType::c1_mbsfnAreaConfiguration_r9_Clear()
{
    c1_mbsfnAreaConfiguration_r9_present = false;
    return 0;
}

bool MCCH_MessageType::c1_mbsfnAreaConfiguration_r9_IsPresent() const
{
    return c1_mbsfnAreaConfiguration_r9_present;
}

