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

#include "HandoverFromEUTRAPreparationRequest.h"

#include <cmath>

int HandoverFromEUTRAPreparationRequest::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != rrc_TransactionIdentifier.Pack(bits))
        {
            printf("HandoverFromEUTRAPreparationRequest:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != criticalExtensions_Pack(bits))
        {
            printf("HandoverFromEUTRAPreparationRequest:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int HandoverFromEUTRAPreparationRequest::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int HandoverFromEUTRAPreparationRequest::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != rrc_TransactionIdentifier.Unpack(bits, idx))
        {
            printf("HandoverFromEUTRAPreparationRequest:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != criticalExtensions_Unpack(bits, idx))
        {
            printf("HandoverFromEUTRAPreparationRequest:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string HandoverFromEUTRAPreparationRequest::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "HandoverFromEUTRAPreparationRequest:\n";
    out += rrc_TransactionIdentifier_ToString(indent+1);
    out += criticalExtensions_ToString(indent+1);
    return out;
}

std::string HandoverFromEUTRAPreparationRequest::ToStringNoNewLines() const
{
    std::string out = "HandoverFromEUTRAPreparationRequest:";
    out += rrc_TransactionIdentifier_ToStringNoNewLines();
    out += criticalExtensions_ToStringNoNewLines();
    return out;
}

RRC_TransactionIdentifier* HandoverFromEUTRAPreparationRequest::rrc_TransactionIdentifier_Set()
{
    rrc_TransactionIdentifier_present = true;
    return &rrc_TransactionIdentifier;
}

int HandoverFromEUTRAPreparationRequest::rrc_TransactionIdentifier_Set(RRC_TransactionIdentifier &value)
{
    rrc_TransactionIdentifier_present = true;
    rrc_TransactionIdentifier = value;
    return 0;
}

const RRC_TransactionIdentifier& HandoverFromEUTRAPreparationRequest::rrc_TransactionIdentifier_Get() const
{
    return rrc_TransactionIdentifier;
}

std::string HandoverFromEUTRAPreparationRequest::rrc_TransactionIdentifier_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "rrc_TransactionIdentifier:\n";
    out += rrc_TransactionIdentifier.ToString(indent+1);
    return out;
}

std::string HandoverFromEUTRAPreparationRequest::rrc_TransactionIdentifier_ToStringNoNewLines() const
{
    std::string out = "rrc_TransactionIdentifier:";
    out += rrc_TransactionIdentifier.ToStringNoNewLines();
    return out;
}

int HandoverFromEUTRAPreparationRequest::rrc_TransactionIdentifier_Clear()
{
    rrc_TransactionIdentifier_present = false;
    return 0;
}

bool HandoverFromEUTRAPreparationRequest::rrc_TransactionIdentifier_IsPresent() const
{
    return rrc_TransactionIdentifier_present;
}

int HandoverFromEUTRAPreparationRequest::criticalExtensions_Pack(std::vector<uint8_t> &bits)
{
    if(!criticalExtensions_present)
    {
        printf("HandoverFromEUTRAPreparationRequest::criticalExtensions_Pack() presence failure\n");
        return -1;
    }
    // Extension indicator

    // Choice
    for(uint32_t i=0; i<1; i++)
        bits.push_back((criticalExtensions_internal_choice >> (1-i-1)) & 1);

    // Fields
    if(criticalExtensions_internal_choice == k_criticalExtensions_c1)
    {
        if(0 != criticalExtensions_c1_Pack(bits))
        {
            printf("HandoverFromEUTRAPreparationRequest::criticalExtensions_c1 pack failure\n");
            return -1;
        }
    }
    return 0;
}

int HandoverFromEUTRAPreparationRequest::criticalExtensions_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return criticalExtensions_Unpack(bits, idx);
}

int HandoverFromEUTRAPreparationRequest::criticalExtensions_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 1) > bits.size())
    {
        printf("HandoverFromEUTRAPreparationRequest::criticalExtensions_Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<1; i++)
        packed_val |= bits[idx++] << (1-i-1);

    if((HandoverFromEUTRAPreparationRequest::criticalExtensions_Enum)packed_val > k_criticalExtensions_criticalExtensionsFuture)
    {
        printf("HandoverFromEUTRAPreparationRequest::criticalExtensions_Unpack() choice range failure\n");
        return -1;
    }
    criticalExtensions_internal_choice = (HandoverFromEUTRAPreparationRequest::criticalExtensions_Enum)packed_val;
    criticalExtensions_present = true;

    // Fields
    if(criticalExtensions_internal_choice == k_criticalExtensions_c1)
    {
        if(0 != criticalExtensions_c1_Unpack(bits, idx))
        {
            printf("HandoverFromEUTRAPreparationRequest::criticalExtensions_c1 unpack failure\n");
            return -1;
        }
    }
    return 0;
}

HandoverFromEUTRAPreparationRequest::criticalExtensions_Enum HandoverFromEUTRAPreparationRequest::criticalExtensions_Choice() const
{
    if(criticalExtensions_present)
        return criticalExtensions_internal_choice;
    return (HandoverFromEUTRAPreparationRequest::criticalExtensions_Enum)0;
}

int HandoverFromEUTRAPreparationRequest::criticalExtensions_SetChoice(HandoverFromEUTRAPreparationRequest::criticalExtensions_Enum choice)
{
    criticalExtensions_internal_choice = choice;
    criticalExtensions_present = true;
    return 0;
}

std::string HandoverFromEUTRAPreparationRequest::criticalExtensions_ChoiceToString(criticalExtensions_Enum value) const
{
    if(k_criticalExtensions_c1 == value)
        return "criticalExtensions_c1";
    if(k_criticalExtensions_criticalExtensionsFuture == value)
        return "criticalExtensions_criticalExtensionsFuture";
    return "";
}

uint64_t HandoverFromEUTRAPreparationRequest::criticalExtensions_NumberOfChoices() const
{
    return 2;
}

std::string HandoverFromEUTRAPreparationRequest::criticalExtensions_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "criticalExtensions = " + criticalExtensions_ChoiceToString(criticalExtensions_internal_choice) + ":\n";
    if(criticalExtensions_internal_choice == k_criticalExtensions_c1)
        out += criticalExtensions_c1_ToString(indent+1);
    return out;
}

std::string HandoverFromEUTRAPreparationRequest::criticalExtensions_ToStringNoNewLines() const
{
    std::string out = "criticalExtensions=" + criticalExtensions_ChoiceToString(criticalExtensions_internal_choice) + ",";
    if(criticalExtensions_internal_choice == k_criticalExtensions_c1)
        out += criticalExtensions_c1_ToStringNoNewLines();
    return out;
}

int HandoverFromEUTRAPreparationRequest::criticalExtensions_Clear()
{
    criticalExtensions_present = false;
    return 0;
}

bool HandoverFromEUTRAPreparationRequest::criticalExtensions_IsPresent() const
{
    return criticalExtensions_present;
}

int HandoverFromEUTRAPreparationRequest::criticalExtensions_c1_Pack(std::vector<uint8_t> &bits)
{
    if(!criticalExtensions_c1_present)
    {
        printf("HandoverFromEUTRAPreparationRequest::criticalExtensions_c1_Pack() presence failure\n");
        return -1;
    }
    // Extension indicator

    // Choice
    for(uint32_t i=0; i<2; i++)
        bits.push_back((criticalExtensions_c1_internal_choice >> (2-i-1)) & 1);

    // Fields
    if(criticalExtensions_c1_internal_choice == k_criticalExtensions_c1_handoverFromEUTRAPreparationRequest_r8)
    {
        if(0 != criticalExtensions_c1_handoverFromEUTRAPreparationRequest_r8.Pack(bits))
        {
            printf("HandoverFromEUTRAPreparationRequest::criticalExtensions_c1_handoverFromEUTRAPreparationRequest_r8 pack failure\n");
            return -1;
        }
    }
    if(criticalExtensions_c1_internal_choice == k_criticalExtensions_c1_spare3)
    {
        if(0 != criticalExtensions_c1_spare3_Pack(bits))
        {
            printf("HandoverFromEUTRAPreparationRequest::criticalExtensions_c1_spare3 pack failure\n");
            return -1;
        }
    }
    if(criticalExtensions_c1_internal_choice == k_criticalExtensions_c1_spare2)
    {
        if(0 != criticalExtensions_c1_spare2_Pack(bits))
        {
            printf("HandoverFromEUTRAPreparationRequest::criticalExtensions_c1_spare2 pack failure\n");
            return -1;
        }
    }
    if(criticalExtensions_c1_internal_choice == k_criticalExtensions_c1_spare1)
    {
        if(0 != criticalExtensions_c1_spare1_Pack(bits))
        {
            printf("HandoverFromEUTRAPreparationRequest::criticalExtensions_c1_spare1 pack failure\n");
            return -1;
        }
    }
    return 0;
}

int HandoverFromEUTRAPreparationRequest::criticalExtensions_c1_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return criticalExtensions_c1_Unpack(bits, idx);
}

int HandoverFromEUTRAPreparationRequest::criticalExtensions_c1_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 2) > bits.size())
    {
        printf("HandoverFromEUTRAPreparationRequest::criticalExtensions_c1_Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<2; i++)
        packed_val |= bits[idx++] << (2-i-1);

    if((HandoverFromEUTRAPreparationRequest::criticalExtensions_c1_Enum)packed_val > k_criticalExtensions_c1_spare1)
    {
        printf("HandoverFromEUTRAPreparationRequest::criticalExtensions_c1_Unpack() choice range failure\n");
        return -1;
    }
    criticalExtensions_c1_internal_choice = (HandoverFromEUTRAPreparationRequest::criticalExtensions_c1_Enum)packed_val;
    criticalExtensions_c1_present = true;

    // Fields
    if(criticalExtensions_c1_internal_choice == k_criticalExtensions_c1_handoverFromEUTRAPreparationRequest_r8)
    {
        if(0 != criticalExtensions_c1_handoverFromEUTRAPreparationRequest_r8.Unpack(bits, idx))
        {
            printf("HandoverFromEUTRAPreparationRequest::criticalExtensions_c1_handoverFromEUTRAPreparationRequest_r8 unpack failure\n");
            return -1;
        }
    }
    if(criticalExtensions_c1_internal_choice == k_criticalExtensions_c1_spare3)
    {
        if(0 != criticalExtensions_c1_spare3_Unpack(bits, idx))
        {
            printf("HandoverFromEUTRAPreparationRequest::criticalExtensions_c1_spare3 unpack failure\n");
            return -1;
        }
    }
    if(criticalExtensions_c1_internal_choice == k_criticalExtensions_c1_spare2)
    {
        if(0 != criticalExtensions_c1_spare2_Unpack(bits, idx))
        {
            printf("HandoverFromEUTRAPreparationRequest::criticalExtensions_c1_spare2 unpack failure\n");
            return -1;
        }
    }
    if(criticalExtensions_c1_internal_choice == k_criticalExtensions_c1_spare1)
    {
        if(0 != criticalExtensions_c1_spare1_Unpack(bits, idx))
        {
            printf("HandoverFromEUTRAPreparationRequest::criticalExtensions_c1_spare1 unpack failure\n");
            return -1;
        }
    }
    return 0;
}

HandoverFromEUTRAPreparationRequest::criticalExtensions_c1_Enum HandoverFromEUTRAPreparationRequest::criticalExtensions_c1_Choice() const
{
    if(criticalExtensions_c1_present)
        return criticalExtensions_c1_internal_choice;
    return (HandoverFromEUTRAPreparationRequest::criticalExtensions_c1_Enum)0;
}

int HandoverFromEUTRAPreparationRequest::criticalExtensions_c1_SetChoice(HandoverFromEUTRAPreparationRequest::criticalExtensions_c1_Enum choice)
{
    criticalExtensions_c1_internal_choice = choice;
    criticalExtensions_c1_present = true;
    return 0;
}

std::string HandoverFromEUTRAPreparationRequest::criticalExtensions_c1_ChoiceToString(criticalExtensions_c1_Enum value) const
{
    if(k_criticalExtensions_c1_handoverFromEUTRAPreparationRequest_r8 == value)
        return "criticalExtensions_c1_handoverFromEUTRAPreparationRequest_r8";
    if(k_criticalExtensions_c1_spare3 == value)
        return "criticalExtensions_c1_spare3";
    if(k_criticalExtensions_c1_spare2 == value)
        return "criticalExtensions_c1_spare2";
    if(k_criticalExtensions_c1_spare1 == value)
        return "criticalExtensions_c1_spare1";
    return "";
}

uint64_t HandoverFromEUTRAPreparationRequest::criticalExtensions_c1_NumberOfChoices() const
{
    return 4;
}

std::string HandoverFromEUTRAPreparationRequest::criticalExtensions_c1_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "c1 = " + criticalExtensions_c1_ChoiceToString(criticalExtensions_c1_internal_choice) + ":\n";
    if(criticalExtensions_c1_internal_choice == k_criticalExtensions_c1_handoverFromEUTRAPreparationRequest_r8)
        out += criticalExtensions_c1_handoverFromEUTRAPreparationRequest_r8.ToString(indent+1);
    return out;
}

std::string HandoverFromEUTRAPreparationRequest::criticalExtensions_c1_ToStringNoNewLines() const
{
    std::string out = "c1=" + criticalExtensions_c1_ChoiceToString(criticalExtensions_c1_internal_choice) + ",";
    if(criticalExtensions_c1_internal_choice == k_criticalExtensions_c1_handoverFromEUTRAPreparationRequest_r8)
        out += criticalExtensions_c1_handoverFromEUTRAPreparationRequest_r8.ToStringNoNewLines();
    return out;
}

int HandoverFromEUTRAPreparationRequest::criticalExtensions_c1_Clear()
{
    criticalExtensions_c1_present = false;
    return 0;
}

bool HandoverFromEUTRAPreparationRequest::criticalExtensions_c1_IsPresent() const
{
    return criticalExtensions_c1_present;
}

HandoverFromEUTRAPreparationRequest_r8_IEs* HandoverFromEUTRAPreparationRequest::criticalExtensions_c1_handoverFromEUTRAPreparationRequest_r8_Set()
{
    criticalExtensions_c1_handoverFromEUTRAPreparationRequest_r8_present = true;
    return &criticalExtensions_c1_handoverFromEUTRAPreparationRequest_r8;
}

int HandoverFromEUTRAPreparationRequest::criticalExtensions_c1_handoverFromEUTRAPreparationRequest_r8_Set(HandoverFromEUTRAPreparationRequest_r8_IEs &value)
{
    criticalExtensions_c1_handoverFromEUTRAPreparationRequest_r8_present = true;
    criticalExtensions_c1_handoverFromEUTRAPreparationRequest_r8 = value;
    return 0;
}

const HandoverFromEUTRAPreparationRequest_r8_IEs& HandoverFromEUTRAPreparationRequest::criticalExtensions_c1_handoverFromEUTRAPreparationRequest_r8_Get() const
{
    return criticalExtensions_c1_handoverFromEUTRAPreparationRequest_r8;
}

std::string HandoverFromEUTRAPreparationRequest::criticalExtensions_c1_handoverFromEUTRAPreparationRequest_r8_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "handoverFromEUTRAPreparationRequest_r8:\n";
    out += criticalExtensions_c1_handoverFromEUTRAPreparationRequest_r8.ToString(indent+1);
    return out;
}

std::string HandoverFromEUTRAPreparationRequest::criticalExtensions_c1_handoverFromEUTRAPreparationRequest_r8_ToStringNoNewLines() const
{
    std::string out = "handoverFromEUTRAPreparationRequest_r8:";
    out += criticalExtensions_c1_handoverFromEUTRAPreparationRequest_r8.ToStringNoNewLines();
    return out;
}

int HandoverFromEUTRAPreparationRequest::criticalExtensions_c1_handoverFromEUTRAPreparationRequest_r8_Clear()
{
    criticalExtensions_c1_handoverFromEUTRAPreparationRequest_r8_present = false;
    return 0;
}

bool HandoverFromEUTRAPreparationRequest::criticalExtensions_c1_handoverFromEUTRAPreparationRequest_r8_IsPresent() const
{
    return criticalExtensions_c1_handoverFromEUTRAPreparationRequest_r8_present;
}

