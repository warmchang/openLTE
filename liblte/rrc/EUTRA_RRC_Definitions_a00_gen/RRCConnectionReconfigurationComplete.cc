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

#include "RRCConnectionReconfigurationComplete.h"

#include <cmath>

int RRCConnectionReconfigurationComplete::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != rrc_TransactionIdentifier.Pack(bits))
        {
            printf("RRCConnectionReconfigurationComplete:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != criticalExtensions_Pack(bits))
        {
            printf("RRCConnectionReconfigurationComplete:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int RRCConnectionReconfigurationComplete::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int RRCConnectionReconfigurationComplete::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != rrc_TransactionIdentifier.Unpack(bits, idx))
        {
            printf("RRCConnectionReconfigurationComplete:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != criticalExtensions_Unpack(bits, idx))
        {
            printf("RRCConnectionReconfigurationComplete:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string RRCConnectionReconfigurationComplete::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "RRCConnectionReconfigurationComplete:\n";
    out += rrc_TransactionIdentifier_ToString(indent+1);
    out += criticalExtensions_ToString(indent+1);
    return out;
}

std::string RRCConnectionReconfigurationComplete::ToStringNoNewLines() const
{
    std::string out = "RRCConnectionReconfigurationComplete:";
    out += rrc_TransactionIdentifier_ToStringNoNewLines();
    out += criticalExtensions_ToStringNoNewLines();
    return out;
}

RRC_TransactionIdentifier* RRCConnectionReconfigurationComplete::rrc_TransactionIdentifier_Set()
{
    rrc_TransactionIdentifier_present = true;
    return &rrc_TransactionIdentifier;
}

int RRCConnectionReconfigurationComplete::rrc_TransactionIdentifier_Set(RRC_TransactionIdentifier &value)
{
    rrc_TransactionIdentifier_present = true;
    rrc_TransactionIdentifier = value;
    return 0;
}

const RRC_TransactionIdentifier& RRCConnectionReconfigurationComplete::rrc_TransactionIdentifier_Get() const
{
    return rrc_TransactionIdentifier;
}

std::string RRCConnectionReconfigurationComplete::rrc_TransactionIdentifier_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "rrc_TransactionIdentifier:\n";
    out += rrc_TransactionIdentifier.ToString(indent+1);
    return out;
}

std::string RRCConnectionReconfigurationComplete::rrc_TransactionIdentifier_ToStringNoNewLines() const
{
    std::string out = "rrc_TransactionIdentifier:";
    out += rrc_TransactionIdentifier.ToStringNoNewLines();
    return out;
}

int RRCConnectionReconfigurationComplete::rrc_TransactionIdentifier_Clear()
{
    rrc_TransactionIdentifier_present = false;
    return 0;
}

bool RRCConnectionReconfigurationComplete::rrc_TransactionIdentifier_IsPresent() const
{
    return rrc_TransactionIdentifier_present;
}

int RRCConnectionReconfigurationComplete::criticalExtensions_Pack(std::vector<uint8_t> &bits)
{
    if(!criticalExtensions_present)
    {
        printf("RRCConnectionReconfigurationComplete::criticalExtensions_Pack() presence failure\n");
        return -1;
    }
    // Extension indicator

    // Choice
    for(uint32_t i=0; i<1; i++)
        bits.push_back((criticalExtensions_internal_choice >> (1-i-1)) & 1);

    // Fields
    if(criticalExtensions_internal_choice == k_criticalExtensions_rrcConnectionReconfigurationComplete_r8)
    {
        if(0 != criticalExtensions_rrcConnectionReconfigurationComplete_r8.Pack(bits))
        {
            printf("RRCConnectionReconfigurationComplete::criticalExtensions_rrcConnectionReconfigurationComplete_r8 pack failure\n");
            return -1;
        }
    }
    return 0;
}

int RRCConnectionReconfigurationComplete::criticalExtensions_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return criticalExtensions_Unpack(bits, idx);
}

int RRCConnectionReconfigurationComplete::criticalExtensions_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 1) > bits.size())
    {
        printf("RRCConnectionReconfigurationComplete::criticalExtensions_Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<1; i++)
        packed_val |= bits[idx++] << (1-i-1);

    if((RRCConnectionReconfigurationComplete::criticalExtensions_Enum)packed_val > k_criticalExtensions_criticalExtensionsFuture)
    {
        printf("RRCConnectionReconfigurationComplete::criticalExtensions_Unpack() choice range failure\n");
        return -1;
    }
    criticalExtensions_internal_choice = (RRCConnectionReconfigurationComplete::criticalExtensions_Enum)packed_val;
    criticalExtensions_present = true;

    // Fields
    if(criticalExtensions_internal_choice == k_criticalExtensions_rrcConnectionReconfigurationComplete_r8)
    {
        if(0 != criticalExtensions_rrcConnectionReconfigurationComplete_r8.Unpack(bits, idx))
        {
            printf("RRCConnectionReconfigurationComplete::criticalExtensions_rrcConnectionReconfigurationComplete_r8 unpack failure\n");
            return -1;
        }
    }
    return 0;
}

RRCConnectionReconfigurationComplete::criticalExtensions_Enum RRCConnectionReconfigurationComplete::criticalExtensions_Choice() const
{
    if(criticalExtensions_present)
        return criticalExtensions_internal_choice;
    return (RRCConnectionReconfigurationComplete::criticalExtensions_Enum)0;
}

int RRCConnectionReconfigurationComplete::criticalExtensions_SetChoice(RRCConnectionReconfigurationComplete::criticalExtensions_Enum choice)
{
    criticalExtensions_internal_choice = choice;
    criticalExtensions_present = true;
    return 0;
}

std::string RRCConnectionReconfigurationComplete::criticalExtensions_ChoiceToString(criticalExtensions_Enum value) const
{
    if(k_criticalExtensions_rrcConnectionReconfigurationComplete_r8 == value)
        return "criticalExtensions_rrcConnectionReconfigurationComplete_r8";
    if(k_criticalExtensions_criticalExtensionsFuture == value)
        return "criticalExtensions_criticalExtensionsFuture";
    return "";
}

uint64_t RRCConnectionReconfigurationComplete::criticalExtensions_NumberOfChoices() const
{
    return 2;
}

std::string RRCConnectionReconfigurationComplete::criticalExtensions_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "criticalExtensions = " + criticalExtensions_ChoiceToString(criticalExtensions_internal_choice) + ":\n";
    if(criticalExtensions_internal_choice == k_criticalExtensions_rrcConnectionReconfigurationComplete_r8)
        out += criticalExtensions_rrcConnectionReconfigurationComplete_r8.ToString(indent+1);
    return out;
}

std::string RRCConnectionReconfigurationComplete::criticalExtensions_ToStringNoNewLines() const
{
    std::string out = "criticalExtensions=" + criticalExtensions_ChoiceToString(criticalExtensions_internal_choice) + ",";
    if(criticalExtensions_internal_choice == k_criticalExtensions_rrcConnectionReconfigurationComplete_r8)
        out += criticalExtensions_rrcConnectionReconfigurationComplete_r8.ToStringNoNewLines();
    return out;
}

int RRCConnectionReconfigurationComplete::criticalExtensions_Clear()
{
    criticalExtensions_present = false;
    return 0;
}

bool RRCConnectionReconfigurationComplete::criticalExtensions_IsPresent() const
{
    return criticalExtensions_present;
}

RRCConnectionReconfigurationComplete_r8_IEs* RRCConnectionReconfigurationComplete::criticalExtensions_rrcConnectionReconfigurationComplete_r8_Set()
{
    criticalExtensions_rrcConnectionReconfigurationComplete_r8_present = true;
    return &criticalExtensions_rrcConnectionReconfigurationComplete_r8;
}

int RRCConnectionReconfigurationComplete::criticalExtensions_rrcConnectionReconfigurationComplete_r8_Set(RRCConnectionReconfigurationComplete_r8_IEs &value)
{
    criticalExtensions_rrcConnectionReconfigurationComplete_r8_present = true;
    criticalExtensions_rrcConnectionReconfigurationComplete_r8 = value;
    return 0;
}

const RRCConnectionReconfigurationComplete_r8_IEs& RRCConnectionReconfigurationComplete::criticalExtensions_rrcConnectionReconfigurationComplete_r8_Get() const
{
    return criticalExtensions_rrcConnectionReconfigurationComplete_r8;
}

std::string RRCConnectionReconfigurationComplete::criticalExtensions_rrcConnectionReconfigurationComplete_r8_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "rrcConnectionReconfigurationComplete_r8:\n";
    out += criticalExtensions_rrcConnectionReconfigurationComplete_r8.ToString(indent+1);
    return out;
}

std::string RRCConnectionReconfigurationComplete::criticalExtensions_rrcConnectionReconfigurationComplete_r8_ToStringNoNewLines() const
{
    std::string out = "rrcConnectionReconfigurationComplete_r8:";
    out += criticalExtensions_rrcConnectionReconfigurationComplete_r8.ToStringNoNewLines();
    return out;
}

int RRCConnectionReconfigurationComplete::criticalExtensions_rrcConnectionReconfigurationComplete_r8_Clear()
{
    criticalExtensions_rrcConnectionReconfigurationComplete_r8_present = false;
    return 0;
}

bool RRCConnectionReconfigurationComplete::criticalExtensions_rrcConnectionReconfigurationComplete_r8_IsPresent() const
{
    return criticalExtensions_rrcConnectionReconfigurationComplete_r8_present;
}

