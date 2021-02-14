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

#include "CounterCheckResponse.h"

#include <cmath>

int CounterCheckResponse::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != rrc_TransactionIdentifier.Pack(bits))
        {
            printf("CounterCheckResponse:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != criticalExtensions_Pack(bits))
        {
            printf("CounterCheckResponse:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int CounterCheckResponse::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int CounterCheckResponse::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != rrc_TransactionIdentifier.Unpack(bits, idx))
        {
            printf("CounterCheckResponse:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != criticalExtensions_Unpack(bits, idx))
        {
            printf("CounterCheckResponse:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string CounterCheckResponse::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "CounterCheckResponse:\n";
    out += rrc_TransactionIdentifier_ToString(indent+1);
    out += criticalExtensions_ToString(indent+1);
    return out;
}

std::string CounterCheckResponse::ToStringNoNewLines() const
{
    std::string out = "CounterCheckResponse:";
    out += rrc_TransactionIdentifier_ToStringNoNewLines();
    out += criticalExtensions_ToStringNoNewLines();
    return out;
}

RRC_TransactionIdentifier* CounterCheckResponse::rrc_TransactionIdentifier_Set()
{
    rrc_TransactionIdentifier_present = true;
    return &rrc_TransactionIdentifier;
}

int CounterCheckResponse::rrc_TransactionIdentifier_Set(RRC_TransactionIdentifier &value)
{
    rrc_TransactionIdentifier_present = true;
    rrc_TransactionIdentifier = value;
    return 0;
}

const RRC_TransactionIdentifier& CounterCheckResponse::rrc_TransactionIdentifier_Get() const
{
    return rrc_TransactionIdentifier;
}

std::string CounterCheckResponse::rrc_TransactionIdentifier_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "rrc_TransactionIdentifier:\n";
    out += rrc_TransactionIdentifier.ToString(indent+1);
    return out;
}

std::string CounterCheckResponse::rrc_TransactionIdentifier_ToStringNoNewLines() const
{
    std::string out = "rrc_TransactionIdentifier:";
    out += rrc_TransactionIdentifier.ToStringNoNewLines();
    return out;
}

int CounterCheckResponse::rrc_TransactionIdentifier_Clear()
{
    rrc_TransactionIdentifier_present = false;
    return 0;
}

bool CounterCheckResponse::rrc_TransactionIdentifier_IsPresent() const
{
    return rrc_TransactionIdentifier_present;
}

int CounterCheckResponse::criticalExtensions_Pack(std::vector<uint8_t> &bits)
{
    if(!criticalExtensions_present)
    {
        printf("CounterCheckResponse::criticalExtensions_Pack() presence failure\n");
        return -1;
    }
    // Extension indicator

    // Choice
    for(uint32_t i=0; i<1; i++)
        bits.push_back((criticalExtensions_internal_choice >> (1-i-1)) & 1);

    // Fields
    if(criticalExtensions_internal_choice == k_criticalExtensions_counterCheckResponse_r8)
    {
        if(0 != criticalExtensions_counterCheckResponse_r8.Pack(bits))
        {
            printf("CounterCheckResponse::criticalExtensions_counterCheckResponse_r8 pack failure\n");
            return -1;
        }
    }
    return 0;
}

int CounterCheckResponse::criticalExtensions_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return criticalExtensions_Unpack(bits, idx);
}

int CounterCheckResponse::criticalExtensions_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 1) > bits.size())
    {
        printf("CounterCheckResponse::criticalExtensions_Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<1; i++)
        packed_val |= bits[idx++] << (1-i-1);

    if((CounterCheckResponse::criticalExtensions_Enum)packed_val > k_criticalExtensions_criticalExtensionsFuture)
    {
        printf("CounterCheckResponse::criticalExtensions_Unpack() choice range failure\n");
        return -1;
    }
    criticalExtensions_internal_choice = (CounterCheckResponse::criticalExtensions_Enum)packed_val;
    criticalExtensions_present = true;

    // Fields
    if(criticalExtensions_internal_choice == k_criticalExtensions_counterCheckResponse_r8)
    {
        if(0 != criticalExtensions_counterCheckResponse_r8.Unpack(bits, idx))
        {
            printf("CounterCheckResponse::criticalExtensions_counterCheckResponse_r8 unpack failure\n");
            return -1;
        }
    }
    return 0;
}

CounterCheckResponse::criticalExtensions_Enum CounterCheckResponse::criticalExtensions_Choice() const
{
    if(criticalExtensions_present)
        return criticalExtensions_internal_choice;
    return (CounterCheckResponse::criticalExtensions_Enum)0;
}

int CounterCheckResponse::criticalExtensions_SetChoice(CounterCheckResponse::criticalExtensions_Enum choice)
{
    criticalExtensions_internal_choice = choice;
    criticalExtensions_present = true;
    return 0;
}

std::string CounterCheckResponse::criticalExtensions_ChoiceToString(criticalExtensions_Enum value) const
{
    if(k_criticalExtensions_counterCheckResponse_r8 == value)
        return "criticalExtensions_counterCheckResponse_r8";
    if(k_criticalExtensions_criticalExtensionsFuture == value)
        return "criticalExtensions_criticalExtensionsFuture";
    return "";
}

uint64_t CounterCheckResponse::criticalExtensions_NumberOfChoices() const
{
    return 2;
}

std::string CounterCheckResponse::criticalExtensions_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "criticalExtensions = " + criticalExtensions_ChoiceToString(criticalExtensions_internal_choice) + ":\n";
    if(criticalExtensions_internal_choice == k_criticalExtensions_counterCheckResponse_r8)
        out += criticalExtensions_counterCheckResponse_r8.ToString(indent+1);
    return out;
}

std::string CounterCheckResponse::criticalExtensions_ToStringNoNewLines() const
{
    std::string out = "criticalExtensions=" + criticalExtensions_ChoiceToString(criticalExtensions_internal_choice) + ",";
    if(criticalExtensions_internal_choice == k_criticalExtensions_counterCheckResponse_r8)
        out += criticalExtensions_counterCheckResponse_r8.ToStringNoNewLines();
    return out;
}

int CounterCheckResponse::criticalExtensions_Clear()
{
    criticalExtensions_present = false;
    return 0;
}

bool CounterCheckResponse::criticalExtensions_IsPresent() const
{
    return criticalExtensions_present;
}

CounterCheckResponse_r8_IEs* CounterCheckResponse::criticalExtensions_counterCheckResponse_r8_Set()
{
    criticalExtensions_counterCheckResponse_r8_present = true;
    return &criticalExtensions_counterCheckResponse_r8;
}

int CounterCheckResponse::criticalExtensions_counterCheckResponse_r8_Set(CounterCheckResponse_r8_IEs &value)
{
    criticalExtensions_counterCheckResponse_r8_present = true;
    criticalExtensions_counterCheckResponse_r8 = value;
    return 0;
}

const CounterCheckResponse_r8_IEs& CounterCheckResponse::criticalExtensions_counterCheckResponse_r8_Get() const
{
    return criticalExtensions_counterCheckResponse_r8;
}

std::string CounterCheckResponse::criticalExtensions_counterCheckResponse_r8_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "counterCheckResponse_r8:\n";
    out += criticalExtensions_counterCheckResponse_r8.ToString(indent+1);
    return out;
}

std::string CounterCheckResponse::criticalExtensions_counterCheckResponse_r8_ToStringNoNewLines() const
{
    std::string out = "counterCheckResponse_r8:";
    out += criticalExtensions_counterCheckResponse_r8.ToStringNoNewLines();
    return out;
}

int CounterCheckResponse::criticalExtensions_counterCheckResponse_r8_Clear()
{
    criticalExtensions_counterCheckResponse_r8_present = false;
    return 0;
}

bool CounterCheckResponse::criticalExtensions_counterCheckResponse_r8_IsPresent() const
{
    return criticalExtensions_counterCheckResponse_r8_present;
}

