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

#include "UL_CCCH_MessageType.h"

#include <cmath>

int UL_CCCH_MessageType::Pack(std::vector<uint8_t> &bits)
{
    if(!present)
    {
        printf("UL_CCCH_MessageType::Pack() presence failure\n");
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
            printf("UL_CCCH_MessageType::c1 pack failure\n");
            return -1;
        }
    }
    return 0;
}

int UL_CCCH_MessageType::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int UL_CCCH_MessageType::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 1) > bits.size())
    {
        printf("UL_CCCH_MessageType::Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<1; i++)
        packed_val |= bits[idx++] << (1-i-1);

    if((UL_CCCH_MessageType::Enum)packed_val > k_messageClassExtension)
    {
        printf("UL_CCCH_MessageType::Unpack() choice range failure\n");
        return -1;
    }
    internal_choice = (UL_CCCH_MessageType::Enum)packed_val;
    present = true;

    // Fields
    if(internal_choice == k_c1)
    {
        if(0 != c1_Unpack(bits, idx))
        {
            printf("UL_CCCH_MessageType::c1 unpack failure\n");
            return -1;
        }
    }
    return 0;
}

UL_CCCH_MessageType::Enum UL_CCCH_MessageType::Choice() const
{
    if(present)
        return internal_choice;
    return (UL_CCCH_MessageType::Enum)0;
}

int UL_CCCH_MessageType::SetChoice(UL_CCCH_MessageType::Enum choice)
{
    internal_choice = choice;
    present = true;
    return 0;
}

std::string UL_CCCH_MessageType::ChoiceToString(Enum value) const
{
    if(k_c1 == value)
        return "c1";
    if(k_messageClassExtension == value)
        return "messageClassExtension";
    return "";
}

uint64_t UL_CCCH_MessageType::NumberOfChoices() const
{
    return 2;
}

std::string UL_CCCH_MessageType::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "UL_CCCH_MessageType = " + ChoiceToString(internal_choice) + ":\n";
    if(internal_choice == k_c1)
        out += c1_ToString(indent+1);
    return out;
}

std::string UL_CCCH_MessageType::ToStringNoNewLines() const
{
    std::string out = "UL_CCCH_MessageType=" + ChoiceToString(internal_choice) + ",";
    if(internal_choice == k_c1)
        out += c1_ToStringNoNewLines();
    return out;
}

int UL_CCCH_MessageType::Clear()
{
    present = false;
    return 0;
}

bool UL_CCCH_MessageType::IsPresent() const
{
    return present;
}

int UL_CCCH_MessageType::c1_Pack(std::vector<uint8_t> &bits)
{
    if(!c1_present)
    {
        printf("UL_CCCH_MessageType::c1_Pack() presence failure\n");
        return -1;
    }
    // Extension indicator

    // Choice
    for(uint32_t i=0; i<1; i++)
        bits.push_back((c1_internal_choice >> (1-i-1)) & 1);

    // Fields
    if(c1_internal_choice == k_c1_rrcConnectionReestablishmentRequest)
    {
        if(0 != c1_rrcConnectionReestablishmentRequest.Pack(bits))
        {
            printf("UL_CCCH_MessageType::c1_rrcConnectionReestablishmentRequest pack failure\n");
            return -1;
        }
    }
    if(c1_internal_choice == k_c1_rrcConnectionRequest)
    {
        if(0 != c1_rrcConnectionRequest.Pack(bits))
        {
            printf("UL_CCCH_MessageType::c1_rrcConnectionRequest pack failure\n");
            return -1;
        }
    }
    return 0;
}

int UL_CCCH_MessageType::c1_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return c1_Unpack(bits, idx);
}

int UL_CCCH_MessageType::c1_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 1) > bits.size())
    {
        printf("UL_CCCH_MessageType::c1_Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<1; i++)
        packed_val |= bits[idx++] << (1-i-1);

    if((UL_CCCH_MessageType::c1_Enum)packed_val > k_c1_rrcConnectionRequest)
    {
        printf("UL_CCCH_MessageType::c1_Unpack() choice range failure\n");
        return -1;
    }
    c1_internal_choice = (UL_CCCH_MessageType::c1_Enum)packed_val;
    c1_present = true;

    // Fields
    if(c1_internal_choice == k_c1_rrcConnectionReestablishmentRequest)
    {
        if(0 != c1_rrcConnectionReestablishmentRequest.Unpack(bits, idx))
        {
            printf("UL_CCCH_MessageType::c1_rrcConnectionReestablishmentRequest unpack failure\n");
            return -1;
        }
    }
    if(c1_internal_choice == k_c1_rrcConnectionRequest)
    {
        if(0 != c1_rrcConnectionRequest.Unpack(bits, idx))
        {
            printf("UL_CCCH_MessageType::c1_rrcConnectionRequest unpack failure\n");
            return -1;
        }
    }
    return 0;
}

UL_CCCH_MessageType::c1_Enum UL_CCCH_MessageType::c1_Choice() const
{
    if(c1_present)
        return c1_internal_choice;
    return (UL_CCCH_MessageType::c1_Enum)0;
}

int UL_CCCH_MessageType::c1_SetChoice(UL_CCCH_MessageType::c1_Enum choice)
{
    c1_internal_choice = choice;
    c1_present = true;
    return 0;
}

std::string UL_CCCH_MessageType::c1_ChoiceToString(c1_Enum value) const
{
    if(k_c1_rrcConnectionReestablishmentRequest == value)
        return "c1_rrcConnectionReestablishmentRequest";
    if(k_c1_rrcConnectionRequest == value)
        return "c1_rrcConnectionRequest";
    return "";
}

uint64_t UL_CCCH_MessageType::c1_NumberOfChoices() const
{
    return 2;
}

std::string UL_CCCH_MessageType::c1_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "c1 = " + c1_ChoiceToString(c1_internal_choice) + ":\n";
    if(c1_internal_choice == k_c1_rrcConnectionReestablishmentRequest)
        out += c1_rrcConnectionReestablishmentRequest.ToString(indent+1);
    if(c1_internal_choice == k_c1_rrcConnectionRequest)
        out += c1_rrcConnectionRequest.ToString(indent+1);
    return out;
}

std::string UL_CCCH_MessageType::c1_ToStringNoNewLines() const
{
    std::string out = "c1=" + c1_ChoiceToString(c1_internal_choice) + ",";
    if(c1_internal_choice == k_c1_rrcConnectionReestablishmentRequest)
        out += c1_rrcConnectionReestablishmentRequest.ToStringNoNewLines();
    if(c1_internal_choice == k_c1_rrcConnectionRequest)
        out += c1_rrcConnectionRequest.ToStringNoNewLines();
    return out;
}

int UL_CCCH_MessageType::c1_Clear()
{
    c1_present = false;
    return 0;
}

bool UL_CCCH_MessageType::c1_IsPresent() const
{
    return c1_present;
}

RRCConnectionReestablishmentRequest* UL_CCCH_MessageType::c1_rrcConnectionReestablishmentRequest_Set()
{
    c1_rrcConnectionReestablishmentRequest_present = true;
    return &c1_rrcConnectionReestablishmentRequest;
}

int UL_CCCH_MessageType::c1_rrcConnectionReestablishmentRequest_Set(RRCConnectionReestablishmentRequest &value)
{
    c1_rrcConnectionReestablishmentRequest_present = true;
    c1_rrcConnectionReestablishmentRequest = value;
    return 0;
}

const RRCConnectionReestablishmentRequest& UL_CCCH_MessageType::c1_rrcConnectionReestablishmentRequest_Get() const
{
    return c1_rrcConnectionReestablishmentRequest;
}

std::string UL_CCCH_MessageType::c1_rrcConnectionReestablishmentRequest_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "rrcConnectionReestablishmentRequest:\n";
    out += c1_rrcConnectionReestablishmentRequest.ToString(indent+1);
    return out;
}

std::string UL_CCCH_MessageType::c1_rrcConnectionReestablishmentRequest_ToStringNoNewLines() const
{
    std::string out = "rrcConnectionReestablishmentRequest:";
    out += c1_rrcConnectionReestablishmentRequest.ToStringNoNewLines();
    return out;
}

int UL_CCCH_MessageType::c1_rrcConnectionReestablishmentRequest_Clear()
{
    c1_rrcConnectionReestablishmentRequest_present = false;
    return 0;
}

bool UL_CCCH_MessageType::c1_rrcConnectionReestablishmentRequest_IsPresent() const
{
    return c1_rrcConnectionReestablishmentRequest_present;
}

RRCConnectionRequest* UL_CCCH_MessageType::c1_rrcConnectionRequest_Set()
{
    c1_rrcConnectionRequest_present = true;
    return &c1_rrcConnectionRequest;
}

int UL_CCCH_MessageType::c1_rrcConnectionRequest_Set(RRCConnectionRequest &value)
{
    c1_rrcConnectionRequest_present = true;
    c1_rrcConnectionRequest = value;
    return 0;
}

const RRCConnectionRequest& UL_CCCH_MessageType::c1_rrcConnectionRequest_Get() const
{
    return c1_rrcConnectionRequest;
}

std::string UL_CCCH_MessageType::c1_rrcConnectionRequest_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "rrcConnectionRequest:\n";
    out += c1_rrcConnectionRequest.ToString(indent+1);
    return out;
}

std::string UL_CCCH_MessageType::c1_rrcConnectionRequest_ToStringNoNewLines() const
{
    std::string out = "rrcConnectionRequest:";
    out += c1_rrcConnectionRequest.ToStringNoNewLines();
    return out;
}

int UL_CCCH_MessageType::c1_rrcConnectionRequest_Clear()
{
    c1_rrcConnectionRequest_present = false;
    return 0;
}

bool UL_CCCH_MessageType::c1_rrcConnectionRequest_IsPresent() const
{
    return c1_rrcConnectionRequest_present;
}

