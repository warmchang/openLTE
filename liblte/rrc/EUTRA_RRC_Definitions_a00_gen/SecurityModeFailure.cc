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

#include "SecurityModeFailure.h"

#include <cmath>

int SecurityModeFailure::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != rrc_TransactionIdentifier.Pack(bits))
        {
            printf("SecurityModeFailure:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != criticalExtensions_Pack(bits))
        {
            printf("SecurityModeFailure:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int SecurityModeFailure::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int SecurityModeFailure::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != rrc_TransactionIdentifier.Unpack(bits, idx))
        {
            printf("SecurityModeFailure:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != criticalExtensions_Unpack(bits, idx))
        {
            printf("SecurityModeFailure:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string SecurityModeFailure::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "SecurityModeFailure:\n";
    out += rrc_TransactionIdentifier_ToString(indent+1);
    out += criticalExtensions_ToString(indent+1);
    return out;
}

std::string SecurityModeFailure::ToStringNoNewLines() const
{
    std::string out = "SecurityModeFailure:";
    out += rrc_TransactionIdentifier_ToStringNoNewLines();
    out += criticalExtensions_ToStringNoNewLines();
    return out;
}

RRC_TransactionIdentifier* SecurityModeFailure::rrc_TransactionIdentifier_Set()
{
    rrc_TransactionIdentifier_present = true;
    return &rrc_TransactionIdentifier;
}

int SecurityModeFailure::rrc_TransactionIdentifier_Set(RRC_TransactionIdentifier &value)
{
    rrc_TransactionIdentifier_present = true;
    rrc_TransactionIdentifier = value;
    return 0;
}

const RRC_TransactionIdentifier& SecurityModeFailure::rrc_TransactionIdentifier_Get() const
{
    return rrc_TransactionIdentifier;
}

std::string SecurityModeFailure::rrc_TransactionIdentifier_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "rrc_TransactionIdentifier:\n";
    out += rrc_TransactionIdentifier.ToString(indent+1);
    return out;
}

std::string SecurityModeFailure::rrc_TransactionIdentifier_ToStringNoNewLines() const
{
    std::string out = "rrc_TransactionIdentifier:";
    out += rrc_TransactionIdentifier.ToStringNoNewLines();
    return out;
}

int SecurityModeFailure::rrc_TransactionIdentifier_Clear()
{
    rrc_TransactionIdentifier_present = false;
    return 0;
}

bool SecurityModeFailure::rrc_TransactionIdentifier_IsPresent() const
{
    return rrc_TransactionIdentifier_present;
}

int SecurityModeFailure::criticalExtensions_Pack(std::vector<uint8_t> &bits)
{
    if(!criticalExtensions_present)
    {
        printf("SecurityModeFailure::criticalExtensions_Pack() presence failure\n");
        return -1;
    }
    // Extension indicator

    // Choice
    for(uint32_t i=0; i<1; i++)
        bits.push_back((criticalExtensions_internal_choice >> (1-i-1)) & 1);

    // Fields
    if(criticalExtensions_internal_choice == k_criticalExtensions_securityModeFailure_r8)
    {
        if(0 != criticalExtensions_securityModeFailure_r8.Pack(bits))
        {
            printf("SecurityModeFailure::criticalExtensions_securityModeFailure_r8 pack failure\n");
            return -1;
        }
    }
    return 0;
}

int SecurityModeFailure::criticalExtensions_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return criticalExtensions_Unpack(bits, idx);
}

int SecurityModeFailure::criticalExtensions_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 1) > bits.size())
    {
        printf("SecurityModeFailure::criticalExtensions_Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<1; i++)
        packed_val |= bits[idx++] << (1-i-1);

    if((SecurityModeFailure::criticalExtensions_Enum)packed_val > k_criticalExtensions_criticalExtensionsFuture)
    {
        printf("SecurityModeFailure::criticalExtensions_Unpack() choice range failure\n");
        return -1;
    }
    criticalExtensions_internal_choice = (SecurityModeFailure::criticalExtensions_Enum)packed_val;
    criticalExtensions_present = true;

    // Fields
    if(criticalExtensions_internal_choice == k_criticalExtensions_securityModeFailure_r8)
    {
        if(0 != criticalExtensions_securityModeFailure_r8.Unpack(bits, idx))
        {
            printf("SecurityModeFailure::criticalExtensions_securityModeFailure_r8 unpack failure\n");
            return -1;
        }
    }
    return 0;
}

SecurityModeFailure::criticalExtensions_Enum SecurityModeFailure::criticalExtensions_Choice() const
{
    if(criticalExtensions_present)
        return criticalExtensions_internal_choice;
    return (SecurityModeFailure::criticalExtensions_Enum)0;
}

int SecurityModeFailure::criticalExtensions_SetChoice(SecurityModeFailure::criticalExtensions_Enum choice)
{
    criticalExtensions_internal_choice = choice;
    criticalExtensions_present = true;
    return 0;
}

std::string SecurityModeFailure::criticalExtensions_ChoiceToString(criticalExtensions_Enum value) const
{
    if(k_criticalExtensions_securityModeFailure_r8 == value)
        return "criticalExtensions_securityModeFailure_r8";
    if(k_criticalExtensions_criticalExtensionsFuture == value)
        return "criticalExtensions_criticalExtensionsFuture";
    return "";
}

uint64_t SecurityModeFailure::criticalExtensions_NumberOfChoices() const
{
    return 2;
}

std::string SecurityModeFailure::criticalExtensions_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "criticalExtensions = " + criticalExtensions_ChoiceToString(criticalExtensions_internal_choice) + ":\n";
    if(criticalExtensions_internal_choice == k_criticalExtensions_securityModeFailure_r8)
        out += criticalExtensions_securityModeFailure_r8.ToString(indent+1);
    return out;
}

std::string SecurityModeFailure::criticalExtensions_ToStringNoNewLines() const
{
    std::string out = "criticalExtensions=" + criticalExtensions_ChoiceToString(criticalExtensions_internal_choice) + ",";
    if(criticalExtensions_internal_choice == k_criticalExtensions_securityModeFailure_r8)
        out += criticalExtensions_securityModeFailure_r8.ToStringNoNewLines();
    return out;
}

int SecurityModeFailure::criticalExtensions_Clear()
{
    criticalExtensions_present = false;
    return 0;
}

bool SecurityModeFailure::criticalExtensions_IsPresent() const
{
    return criticalExtensions_present;
}

SecurityModeFailure_r8_IEs* SecurityModeFailure::criticalExtensions_securityModeFailure_r8_Set()
{
    criticalExtensions_securityModeFailure_r8_present = true;
    return &criticalExtensions_securityModeFailure_r8;
}

int SecurityModeFailure::criticalExtensions_securityModeFailure_r8_Set(SecurityModeFailure_r8_IEs &value)
{
    criticalExtensions_securityModeFailure_r8_present = true;
    criticalExtensions_securityModeFailure_r8 = value;
    return 0;
}

const SecurityModeFailure_r8_IEs& SecurityModeFailure::criticalExtensions_securityModeFailure_r8_Get() const
{
    return criticalExtensions_securityModeFailure_r8;
}

std::string SecurityModeFailure::criticalExtensions_securityModeFailure_r8_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "securityModeFailure_r8:\n";
    out += criticalExtensions_securityModeFailure_r8.ToString(indent+1);
    return out;
}

std::string SecurityModeFailure::criticalExtensions_securityModeFailure_r8_ToStringNoNewLines() const
{
    std::string out = "securityModeFailure_r8:";
    out += criticalExtensions_securityModeFailure_r8.ToStringNoNewLines();
    return out;
}

int SecurityModeFailure::criticalExtensions_securityModeFailure_r8_Clear()
{
    criticalExtensions_securityModeFailure_r8_present = false;
    return 0;
}

bool SecurityModeFailure::criticalExtensions_securityModeFailure_r8_IsPresent() const
{
    return criticalExtensions_securityModeFailure_r8_present;
}

