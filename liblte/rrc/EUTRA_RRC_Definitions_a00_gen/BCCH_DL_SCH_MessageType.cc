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

#include "BCCH_DL_SCH_MessageType.h"

#include <cmath>

int BCCH_DL_SCH_MessageType::Pack(std::vector<uint8_t> &bits)
{
    if(!present)
    {
        printf("BCCH_DL_SCH_MessageType::Pack() presence failure\n");
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
            printf("BCCH_DL_SCH_MessageType::c1 pack failure\n");
            return -1;
        }
    }
    return 0;
}

int BCCH_DL_SCH_MessageType::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int BCCH_DL_SCH_MessageType::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 1) > bits.size())
    {
        printf("BCCH_DL_SCH_MessageType::Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<1; i++)
        packed_val |= bits[idx++] << (1-i-1);

    if((BCCH_DL_SCH_MessageType::Enum)packed_val > k_messageClassExtension)
    {
        printf("BCCH_DL_SCH_MessageType::Unpack() choice range failure\n");
        return -1;
    }
    internal_choice = (BCCH_DL_SCH_MessageType::Enum)packed_val;
    present = true;

    // Fields
    if(internal_choice == k_c1)
    {
        if(0 != c1_Unpack(bits, idx))
        {
            printf("BCCH_DL_SCH_MessageType::c1 unpack failure\n");
            return -1;
        }
    }
    return 0;
}

BCCH_DL_SCH_MessageType::Enum BCCH_DL_SCH_MessageType::Choice() const
{
    if(present)
        return internal_choice;
    return (BCCH_DL_SCH_MessageType::Enum)0;
}

int BCCH_DL_SCH_MessageType::SetChoice(BCCH_DL_SCH_MessageType::Enum choice)
{
    internal_choice = choice;
    present = true;
    return 0;
}

std::string BCCH_DL_SCH_MessageType::ChoiceToString(Enum value) const
{
    if(k_c1 == value)
        return "c1";
    if(k_messageClassExtension == value)
        return "messageClassExtension";
    return "";
}

uint64_t BCCH_DL_SCH_MessageType::NumberOfChoices() const
{
    return 2;
}

std::string BCCH_DL_SCH_MessageType::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "BCCH_DL_SCH_MessageType = " + ChoiceToString(internal_choice) + ":\n";
    if(internal_choice == k_c1)
        out += c1_ToString(indent+1);
    return out;
}

std::string BCCH_DL_SCH_MessageType::ToStringNoNewLines() const
{
    std::string out = "BCCH_DL_SCH_MessageType=" + ChoiceToString(internal_choice) + ",";
    if(internal_choice == k_c1)
        out += c1_ToStringNoNewLines();
    return out;
}

int BCCH_DL_SCH_MessageType::Clear()
{
    present = false;
    return 0;
}

bool BCCH_DL_SCH_MessageType::IsPresent() const
{
    return present;
}

int BCCH_DL_SCH_MessageType::c1_Pack(std::vector<uint8_t> &bits)
{
    if(!c1_present)
    {
        printf("BCCH_DL_SCH_MessageType::c1_Pack() presence failure\n");
        return -1;
    }
    // Extension indicator

    // Choice
    for(uint32_t i=0; i<1; i++)
        bits.push_back((c1_internal_choice >> (1-i-1)) & 1);

    // Fields
    if(c1_internal_choice == k_c1_systemInformation)
    {
        if(0 != c1_systemInformation.Pack(bits))
        {
            printf("BCCH_DL_SCH_MessageType::c1_systemInformation pack failure\n");
            return -1;
        }
    }
    if(c1_internal_choice == k_c1_systemInformationBlockType1)
    {
        if(0 != c1_systemInformationBlockType1.Pack(bits))
        {
            printf("BCCH_DL_SCH_MessageType::c1_systemInformationBlockType1 pack failure\n");
            return -1;
        }
    }
    return 0;
}

int BCCH_DL_SCH_MessageType::c1_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return c1_Unpack(bits, idx);
}

int BCCH_DL_SCH_MessageType::c1_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 1) > bits.size())
    {
        printf("BCCH_DL_SCH_MessageType::c1_Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<1; i++)
        packed_val |= bits[idx++] << (1-i-1);

    if((BCCH_DL_SCH_MessageType::c1_Enum)packed_val > k_c1_systemInformationBlockType1)
    {
        printf("BCCH_DL_SCH_MessageType::c1_Unpack() choice range failure\n");
        return -1;
    }
    c1_internal_choice = (BCCH_DL_SCH_MessageType::c1_Enum)packed_val;
    c1_present = true;

    // Fields
    if(c1_internal_choice == k_c1_systemInformation)
    {
        if(0 != c1_systemInformation.Unpack(bits, idx))
        {
            printf("BCCH_DL_SCH_MessageType::c1_systemInformation unpack failure\n");
            return -1;
        }
    }
    if(c1_internal_choice == k_c1_systemInformationBlockType1)
    {
        if(0 != c1_systemInformationBlockType1.Unpack(bits, idx))
        {
            printf("BCCH_DL_SCH_MessageType::c1_systemInformationBlockType1 unpack failure\n");
            return -1;
        }
    }
    return 0;
}

BCCH_DL_SCH_MessageType::c1_Enum BCCH_DL_SCH_MessageType::c1_Choice() const
{
    if(c1_present)
        return c1_internal_choice;
    return (BCCH_DL_SCH_MessageType::c1_Enum)0;
}

int BCCH_DL_SCH_MessageType::c1_SetChoice(BCCH_DL_SCH_MessageType::c1_Enum choice)
{
    c1_internal_choice = choice;
    c1_present = true;
    return 0;
}

std::string BCCH_DL_SCH_MessageType::c1_ChoiceToString(c1_Enum value) const
{
    if(k_c1_systemInformation == value)
        return "c1_systemInformation";
    if(k_c1_systemInformationBlockType1 == value)
        return "c1_systemInformationBlockType1";
    return "";
}

uint64_t BCCH_DL_SCH_MessageType::c1_NumberOfChoices() const
{
    return 2;
}

std::string BCCH_DL_SCH_MessageType::c1_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "c1 = " + c1_ChoiceToString(c1_internal_choice) + ":\n";
    if(c1_internal_choice == k_c1_systemInformation)
        out += c1_systemInformation.ToString(indent+1);
    if(c1_internal_choice == k_c1_systemInformationBlockType1)
        out += c1_systemInformationBlockType1.ToString(indent+1);
    return out;
}

std::string BCCH_DL_SCH_MessageType::c1_ToStringNoNewLines() const
{
    std::string out = "c1=" + c1_ChoiceToString(c1_internal_choice) + ",";
    if(c1_internal_choice == k_c1_systemInformation)
        out += c1_systemInformation.ToStringNoNewLines();
    if(c1_internal_choice == k_c1_systemInformationBlockType1)
        out += c1_systemInformationBlockType1.ToStringNoNewLines();
    return out;
}

int BCCH_DL_SCH_MessageType::c1_Clear()
{
    c1_present = false;
    return 0;
}

bool BCCH_DL_SCH_MessageType::c1_IsPresent() const
{
    return c1_present;
}

SystemInformation* BCCH_DL_SCH_MessageType::c1_systemInformation_Set()
{
    c1_systemInformation_present = true;
    return &c1_systemInformation;
}

int BCCH_DL_SCH_MessageType::c1_systemInformation_Set(SystemInformation &value)
{
    c1_systemInformation_present = true;
    c1_systemInformation = value;
    return 0;
}

const SystemInformation& BCCH_DL_SCH_MessageType::c1_systemInformation_Get() const
{
    return c1_systemInformation;
}

std::string BCCH_DL_SCH_MessageType::c1_systemInformation_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "systemInformation:\n";
    out += c1_systemInformation.ToString(indent+1);
    return out;
}

std::string BCCH_DL_SCH_MessageType::c1_systemInformation_ToStringNoNewLines() const
{
    std::string out = "systemInformation:";
    out += c1_systemInformation.ToStringNoNewLines();
    return out;
}

int BCCH_DL_SCH_MessageType::c1_systemInformation_Clear()
{
    c1_systemInformation_present = false;
    return 0;
}

bool BCCH_DL_SCH_MessageType::c1_systemInformation_IsPresent() const
{
    return c1_systemInformation_present;
}

SystemInformationBlockType1* BCCH_DL_SCH_MessageType::c1_systemInformationBlockType1_Set()
{
    c1_systemInformationBlockType1_present = true;
    return &c1_systemInformationBlockType1;
}

int BCCH_DL_SCH_MessageType::c1_systemInformationBlockType1_Set(SystemInformationBlockType1 &value)
{
    c1_systemInformationBlockType1_present = true;
    c1_systemInformationBlockType1 = value;
    return 0;
}

const SystemInformationBlockType1& BCCH_DL_SCH_MessageType::c1_systemInformationBlockType1_Get() const
{
    return c1_systemInformationBlockType1;
}

std::string BCCH_DL_SCH_MessageType::c1_systemInformationBlockType1_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "systemInformationBlockType1:\n";
    out += c1_systemInformationBlockType1.ToString(indent+1);
    return out;
}

std::string BCCH_DL_SCH_MessageType::c1_systemInformationBlockType1_ToStringNoNewLines() const
{
    std::string out = "systemInformationBlockType1:";
    out += c1_systemInformationBlockType1.ToStringNoNewLines();
    return out;
}

int BCCH_DL_SCH_MessageType::c1_systemInformationBlockType1_Clear()
{
    c1_systemInformationBlockType1_present = false;
    return 0;
}

bool BCCH_DL_SCH_MessageType::c1_systemInformationBlockType1_IsPresent() const
{
    return c1_systemInformationBlockType1_present;
}

