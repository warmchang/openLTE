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

#include "PCCH_MessageType.h"

#include <cmath>

int PCCH_MessageType::Pack(std::vector<uint8_t> &bits)
{
    if(!present)
    {
        printf("PCCH_MessageType::Pack() presence failure\n");
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
            printf("PCCH_MessageType::c1 pack failure\n");
            return -1;
        }
    }
    return 0;
}

int PCCH_MessageType::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int PCCH_MessageType::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 1) > bits.size())
    {
        printf("PCCH_MessageType::Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<1; i++)
        packed_val |= bits[idx++] << (1-i-1);

    if((PCCH_MessageType::Enum)packed_val > k_messageClassExtension)
    {
        printf("PCCH_MessageType::Unpack() choice range failure\n");
        return -1;
    }
    internal_choice = (PCCH_MessageType::Enum)packed_val;
    present = true;

    // Fields
    if(internal_choice == k_c1)
    {
        if(0 != c1_Unpack(bits, idx))
        {
            printf("PCCH_MessageType::c1 unpack failure\n");
            return -1;
        }
    }
    return 0;
}

PCCH_MessageType::Enum PCCH_MessageType::Choice() const
{
    if(present)
        return internal_choice;
    return (PCCH_MessageType::Enum)0;
}

int PCCH_MessageType::SetChoice(PCCH_MessageType::Enum choice)
{
    internal_choice = choice;
    present = true;
    return 0;
}

std::string PCCH_MessageType::ChoiceToString(Enum value) const
{
    if(k_c1 == value)
        return "c1";
    if(k_messageClassExtension == value)
        return "messageClassExtension";
    return "";
}

uint64_t PCCH_MessageType::NumberOfChoices() const
{
    return 2;
}

std::string PCCH_MessageType::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "PCCH_MessageType = " + ChoiceToString(internal_choice) + ":\n";
    if(internal_choice == k_c1)
        out += c1_ToString(indent+1);
    return out;
}

std::string PCCH_MessageType::ToStringNoNewLines() const
{
    std::string out = "PCCH_MessageType=" + ChoiceToString(internal_choice) + ",";
    if(internal_choice == k_c1)
        out += c1_ToStringNoNewLines();
    return out;
}

int PCCH_MessageType::Clear()
{
    present = false;
    return 0;
}

bool PCCH_MessageType::IsPresent() const
{
    return present;
}

int PCCH_MessageType::c1_Pack(std::vector<uint8_t> &bits)
{
    if(!c1_present)
    {
        printf("PCCH_MessageType::c1_Pack() presence failure\n");
        return -1;
    }
    // Extension indicator

    // Choice

    // Fields
    if(c1_internal_choice == k_c1_paging)
    {
        if(0 != c1_paging.Pack(bits))
        {
            printf("PCCH_MessageType::c1_paging pack failure\n");
            return -1;
        }
    }
    return 0;
}

int PCCH_MessageType::c1_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return c1_Unpack(bits, idx);
}

int PCCH_MessageType::c1_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    c1_internal_choice = (PCCH_MessageType::c1_Enum)0;
    c1_present = true;

    // Fields
    if(c1_internal_choice == k_c1_paging)
    {
        if(0 != c1_paging.Unpack(bits, idx))
        {
            printf("PCCH_MessageType::c1_paging unpack failure\n");
            return -1;
        }
    }
    return 0;
}

PCCH_MessageType::c1_Enum PCCH_MessageType::c1_Choice() const
{
    if(c1_present)
        return c1_internal_choice;
    return (PCCH_MessageType::c1_Enum)0;
}

int PCCH_MessageType::c1_SetChoice(PCCH_MessageType::c1_Enum choice)
{
    c1_internal_choice = choice;
    c1_present = true;
    return 0;
}

std::string PCCH_MessageType::c1_ChoiceToString(c1_Enum value) const
{
    if(k_c1_paging == value)
        return "c1_paging";
    return "";
}

uint64_t PCCH_MessageType::c1_NumberOfChoices() const
{
    return 1;
}

std::string PCCH_MessageType::c1_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "c1 = " + c1_ChoiceToString(c1_internal_choice) + ":\n";
    if(c1_internal_choice == k_c1_paging)
        out += c1_paging.ToString(indent+1);
    return out;
}

std::string PCCH_MessageType::c1_ToStringNoNewLines() const
{
    std::string out = "c1=" + c1_ChoiceToString(c1_internal_choice) + ",";
    if(c1_internal_choice == k_c1_paging)
        out += c1_paging.ToStringNoNewLines();
    return out;
}

int PCCH_MessageType::c1_Clear()
{
    c1_present = false;
    return 0;
}

bool PCCH_MessageType::c1_IsPresent() const
{
    return c1_present;
}

Paging* PCCH_MessageType::c1_paging_Set()
{
    c1_paging_present = true;
    return &c1_paging;
}

int PCCH_MessageType::c1_paging_Set(Paging &value)
{
    c1_paging_present = true;
    c1_paging = value;
    return 0;
}

const Paging& PCCH_MessageType::c1_paging_Get() const
{
    return c1_paging;
}

std::string PCCH_MessageType::c1_paging_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "paging:\n";
    out += c1_paging.ToString(indent+1);
    return out;
}

std::string PCCH_MessageType::c1_paging_ToStringNoNewLines() const
{
    std::string out = "paging:";
    out += c1_paging.ToStringNoNewLines();
    return out;
}

int PCCH_MessageType::c1_paging_Clear()
{
    c1_paging_present = false;
    return 0;
}

bool PCCH_MessageType::c1_paging_IsPresent() const
{
    return c1_paging_present;
}

