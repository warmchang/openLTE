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

#include "MobilityFromEUTRACommand.h"

#include <cmath>

int MobilityFromEUTRACommand::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != rrc_TransactionIdentifier.Pack(bits))
        {
            printf("MobilityFromEUTRACommand:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != criticalExtensions_Pack(bits))
        {
            printf("MobilityFromEUTRACommand:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int MobilityFromEUTRACommand::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int MobilityFromEUTRACommand::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != rrc_TransactionIdentifier.Unpack(bits, idx))
        {
            printf("MobilityFromEUTRACommand:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != criticalExtensions_Unpack(bits, idx))
        {
            printf("MobilityFromEUTRACommand:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string MobilityFromEUTRACommand::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "MobilityFromEUTRACommand:\n";
    out += rrc_TransactionIdentifier_ToString(indent+1);
    out += criticalExtensions_ToString(indent+1);
    return out;
}

std::string MobilityFromEUTRACommand::ToStringNoNewLines() const
{
    std::string out = "MobilityFromEUTRACommand:";
    out += rrc_TransactionIdentifier_ToStringNoNewLines();
    out += criticalExtensions_ToStringNoNewLines();
    return out;
}

RRC_TransactionIdentifier* MobilityFromEUTRACommand::rrc_TransactionIdentifier_Set()
{
    rrc_TransactionIdentifier_present = true;
    return &rrc_TransactionIdentifier;
}

int MobilityFromEUTRACommand::rrc_TransactionIdentifier_Set(RRC_TransactionIdentifier &value)
{
    rrc_TransactionIdentifier_present = true;
    rrc_TransactionIdentifier = value;
    return 0;
}

const RRC_TransactionIdentifier& MobilityFromEUTRACommand::rrc_TransactionIdentifier_Get() const
{
    return rrc_TransactionIdentifier;
}

std::string MobilityFromEUTRACommand::rrc_TransactionIdentifier_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "rrc_TransactionIdentifier:\n";
    out += rrc_TransactionIdentifier.ToString(indent+1);
    return out;
}

std::string MobilityFromEUTRACommand::rrc_TransactionIdentifier_ToStringNoNewLines() const
{
    std::string out = "rrc_TransactionIdentifier:";
    out += rrc_TransactionIdentifier.ToStringNoNewLines();
    return out;
}

int MobilityFromEUTRACommand::rrc_TransactionIdentifier_Clear()
{
    rrc_TransactionIdentifier_present = false;
    return 0;
}

bool MobilityFromEUTRACommand::rrc_TransactionIdentifier_IsPresent() const
{
    return rrc_TransactionIdentifier_present;
}

int MobilityFromEUTRACommand::criticalExtensions_Pack(std::vector<uint8_t> &bits)
{
    if(!criticalExtensions_present)
    {
        printf("MobilityFromEUTRACommand::criticalExtensions_Pack() presence failure\n");
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
            printf("MobilityFromEUTRACommand::criticalExtensions_c1 pack failure\n");
            return -1;
        }
    }
    return 0;
}

int MobilityFromEUTRACommand::criticalExtensions_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return criticalExtensions_Unpack(bits, idx);
}

int MobilityFromEUTRACommand::criticalExtensions_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 1) > bits.size())
    {
        printf("MobilityFromEUTRACommand::criticalExtensions_Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<1; i++)
        packed_val |= bits[idx++] << (1-i-1);

    if((MobilityFromEUTRACommand::criticalExtensions_Enum)packed_val > k_criticalExtensions_criticalExtensionsFuture)
    {
        printf("MobilityFromEUTRACommand::criticalExtensions_Unpack() choice range failure\n");
        return -1;
    }
    criticalExtensions_internal_choice = (MobilityFromEUTRACommand::criticalExtensions_Enum)packed_val;
    criticalExtensions_present = true;

    // Fields
    if(criticalExtensions_internal_choice == k_criticalExtensions_c1)
    {
        if(0 != criticalExtensions_c1_Unpack(bits, idx))
        {
            printf("MobilityFromEUTRACommand::criticalExtensions_c1 unpack failure\n");
            return -1;
        }
    }
    return 0;
}

MobilityFromEUTRACommand::criticalExtensions_Enum MobilityFromEUTRACommand::criticalExtensions_Choice() const
{
    if(criticalExtensions_present)
        return criticalExtensions_internal_choice;
    return (MobilityFromEUTRACommand::criticalExtensions_Enum)0;
}

int MobilityFromEUTRACommand::criticalExtensions_SetChoice(MobilityFromEUTRACommand::criticalExtensions_Enum choice)
{
    criticalExtensions_internal_choice = choice;
    criticalExtensions_present = true;
    return 0;
}

std::string MobilityFromEUTRACommand::criticalExtensions_ChoiceToString(criticalExtensions_Enum value) const
{
    if(k_criticalExtensions_c1 == value)
        return "criticalExtensions_c1";
    if(k_criticalExtensions_criticalExtensionsFuture == value)
        return "criticalExtensions_criticalExtensionsFuture";
    return "";
}

uint64_t MobilityFromEUTRACommand::criticalExtensions_NumberOfChoices() const
{
    return 2;
}

std::string MobilityFromEUTRACommand::criticalExtensions_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "criticalExtensions = " + criticalExtensions_ChoiceToString(criticalExtensions_internal_choice) + ":\n";
    if(criticalExtensions_internal_choice == k_criticalExtensions_c1)
        out += criticalExtensions_c1_ToString(indent+1);
    return out;
}

std::string MobilityFromEUTRACommand::criticalExtensions_ToStringNoNewLines() const
{
    std::string out = "criticalExtensions=" + criticalExtensions_ChoiceToString(criticalExtensions_internal_choice) + ",";
    if(criticalExtensions_internal_choice == k_criticalExtensions_c1)
        out += criticalExtensions_c1_ToStringNoNewLines();
    return out;
}

int MobilityFromEUTRACommand::criticalExtensions_Clear()
{
    criticalExtensions_present = false;
    return 0;
}

bool MobilityFromEUTRACommand::criticalExtensions_IsPresent() const
{
    return criticalExtensions_present;
}

int MobilityFromEUTRACommand::criticalExtensions_c1_Pack(std::vector<uint8_t> &bits)
{
    if(!criticalExtensions_c1_present)
    {
        printf("MobilityFromEUTRACommand::criticalExtensions_c1_Pack() presence failure\n");
        return -1;
    }
    // Extension indicator

    // Choice
    for(uint32_t i=0; i<2; i++)
        bits.push_back((criticalExtensions_c1_internal_choice >> (2-i-1)) & 1);

    // Fields
    if(criticalExtensions_c1_internal_choice == k_criticalExtensions_c1_mobilityFromEUTRACommand_r8)
    {
        if(0 != criticalExtensions_c1_mobilityFromEUTRACommand_r8.Pack(bits))
        {
            printf("MobilityFromEUTRACommand::criticalExtensions_c1_mobilityFromEUTRACommand_r8 pack failure\n");
            return -1;
        }
    }
    if(criticalExtensions_c1_internal_choice == k_criticalExtensions_c1_mobilityFromEUTRACommand_r9)
    {
        if(0 != criticalExtensions_c1_mobilityFromEUTRACommand_r9.Pack(bits))
        {
            printf("MobilityFromEUTRACommand::criticalExtensions_c1_mobilityFromEUTRACommand_r9 pack failure\n");
            return -1;
        }
    }
    if(criticalExtensions_c1_internal_choice == k_criticalExtensions_c1_spare2)
    {
        if(0 != criticalExtensions_c1_spare2_Pack(bits))
        {
            printf("MobilityFromEUTRACommand::criticalExtensions_c1_spare2 pack failure\n");
            return -1;
        }
    }
    if(criticalExtensions_c1_internal_choice == k_criticalExtensions_c1_spare1)
    {
        if(0 != criticalExtensions_c1_spare1_Pack(bits))
        {
            printf("MobilityFromEUTRACommand::criticalExtensions_c1_spare1 pack failure\n");
            return -1;
        }
    }
    return 0;
}

int MobilityFromEUTRACommand::criticalExtensions_c1_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return criticalExtensions_c1_Unpack(bits, idx);
}

int MobilityFromEUTRACommand::criticalExtensions_c1_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 2) > bits.size())
    {
        printf("MobilityFromEUTRACommand::criticalExtensions_c1_Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<2; i++)
        packed_val |= bits[idx++] << (2-i-1);

    if((MobilityFromEUTRACommand::criticalExtensions_c1_Enum)packed_val > k_criticalExtensions_c1_spare1)
    {
        printf("MobilityFromEUTRACommand::criticalExtensions_c1_Unpack() choice range failure\n");
        return -1;
    }
    criticalExtensions_c1_internal_choice = (MobilityFromEUTRACommand::criticalExtensions_c1_Enum)packed_val;
    criticalExtensions_c1_present = true;

    // Fields
    if(criticalExtensions_c1_internal_choice == k_criticalExtensions_c1_mobilityFromEUTRACommand_r8)
    {
        if(0 != criticalExtensions_c1_mobilityFromEUTRACommand_r8.Unpack(bits, idx))
        {
            printf("MobilityFromEUTRACommand::criticalExtensions_c1_mobilityFromEUTRACommand_r8 unpack failure\n");
            return -1;
        }
    }
    if(criticalExtensions_c1_internal_choice == k_criticalExtensions_c1_mobilityFromEUTRACommand_r9)
    {
        if(0 != criticalExtensions_c1_mobilityFromEUTRACommand_r9.Unpack(bits, idx))
        {
            printf("MobilityFromEUTRACommand::criticalExtensions_c1_mobilityFromEUTRACommand_r9 unpack failure\n");
            return -1;
        }
    }
    if(criticalExtensions_c1_internal_choice == k_criticalExtensions_c1_spare2)
    {
        if(0 != criticalExtensions_c1_spare2_Unpack(bits, idx))
        {
            printf("MobilityFromEUTRACommand::criticalExtensions_c1_spare2 unpack failure\n");
            return -1;
        }
    }
    if(criticalExtensions_c1_internal_choice == k_criticalExtensions_c1_spare1)
    {
        if(0 != criticalExtensions_c1_spare1_Unpack(bits, idx))
        {
            printf("MobilityFromEUTRACommand::criticalExtensions_c1_spare1 unpack failure\n");
            return -1;
        }
    }
    return 0;
}

MobilityFromEUTRACommand::criticalExtensions_c1_Enum MobilityFromEUTRACommand::criticalExtensions_c1_Choice() const
{
    if(criticalExtensions_c1_present)
        return criticalExtensions_c1_internal_choice;
    return (MobilityFromEUTRACommand::criticalExtensions_c1_Enum)0;
}

int MobilityFromEUTRACommand::criticalExtensions_c1_SetChoice(MobilityFromEUTRACommand::criticalExtensions_c1_Enum choice)
{
    criticalExtensions_c1_internal_choice = choice;
    criticalExtensions_c1_present = true;
    return 0;
}

std::string MobilityFromEUTRACommand::criticalExtensions_c1_ChoiceToString(criticalExtensions_c1_Enum value) const
{
    if(k_criticalExtensions_c1_mobilityFromEUTRACommand_r8 == value)
        return "criticalExtensions_c1_mobilityFromEUTRACommand_r8";
    if(k_criticalExtensions_c1_mobilityFromEUTRACommand_r9 == value)
        return "criticalExtensions_c1_mobilityFromEUTRACommand_r9";
    if(k_criticalExtensions_c1_spare2 == value)
        return "criticalExtensions_c1_spare2";
    if(k_criticalExtensions_c1_spare1 == value)
        return "criticalExtensions_c1_spare1";
    return "";
}

uint64_t MobilityFromEUTRACommand::criticalExtensions_c1_NumberOfChoices() const
{
    return 4;
}

std::string MobilityFromEUTRACommand::criticalExtensions_c1_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "c1 = " + criticalExtensions_c1_ChoiceToString(criticalExtensions_c1_internal_choice) + ":\n";
    if(criticalExtensions_c1_internal_choice == k_criticalExtensions_c1_mobilityFromEUTRACommand_r8)
        out += criticalExtensions_c1_mobilityFromEUTRACommand_r8.ToString(indent+1);
    if(criticalExtensions_c1_internal_choice == k_criticalExtensions_c1_mobilityFromEUTRACommand_r9)
        out += criticalExtensions_c1_mobilityFromEUTRACommand_r9.ToString(indent+1);
    return out;
}

std::string MobilityFromEUTRACommand::criticalExtensions_c1_ToStringNoNewLines() const
{
    std::string out = "c1=" + criticalExtensions_c1_ChoiceToString(criticalExtensions_c1_internal_choice) + ",";
    if(criticalExtensions_c1_internal_choice == k_criticalExtensions_c1_mobilityFromEUTRACommand_r8)
        out += criticalExtensions_c1_mobilityFromEUTRACommand_r8.ToStringNoNewLines();
    if(criticalExtensions_c1_internal_choice == k_criticalExtensions_c1_mobilityFromEUTRACommand_r9)
        out += criticalExtensions_c1_mobilityFromEUTRACommand_r9.ToStringNoNewLines();
    return out;
}

int MobilityFromEUTRACommand::criticalExtensions_c1_Clear()
{
    criticalExtensions_c1_present = false;
    return 0;
}

bool MobilityFromEUTRACommand::criticalExtensions_c1_IsPresent() const
{
    return criticalExtensions_c1_present;
}

MobilityFromEUTRACommand_r8_IEs* MobilityFromEUTRACommand::criticalExtensions_c1_mobilityFromEUTRACommand_r8_Set()
{
    criticalExtensions_c1_mobilityFromEUTRACommand_r8_present = true;
    return &criticalExtensions_c1_mobilityFromEUTRACommand_r8;
}

int MobilityFromEUTRACommand::criticalExtensions_c1_mobilityFromEUTRACommand_r8_Set(MobilityFromEUTRACommand_r8_IEs &value)
{
    criticalExtensions_c1_mobilityFromEUTRACommand_r8_present = true;
    criticalExtensions_c1_mobilityFromEUTRACommand_r8 = value;
    return 0;
}

const MobilityFromEUTRACommand_r8_IEs& MobilityFromEUTRACommand::criticalExtensions_c1_mobilityFromEUTRACommand_r8_Get() const
{
    return criticalExtensions_c1_mobilityFromEUTRACommand_r8;
}

std::string MobilityFromEUTRACommand::criticalExtensions_c1_mobilityFromEUTRACommand_r8_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "mobilityFromEUTRACommand_r8:\n";
    out += criticalExtensions_c1_mobilityFromEUTRACommand_r8.ToString(indent+1);
    return out;
}

std::string MobilityFromEUTRACommand::criticalExtensions_c1_mobilityFromEUTRACommand_r8_ToStringNoNewLines() const
{
    std::string out = "mobilityFromEUTRACommand_r8:";
    out += criticalExtensions_c1_mobilityFromEUTRACommand_r8.ToStringNoNewLines();
    return out;
}

int MobilityFromEUTRACommand::criticalExtensions_c1_mobilityFromEUTRACommand_r8_Clear()
{
    criticalExtensions_c1_mobilityFromEUTRACommand_r8_present = false;
    return 0;
}

bool MobilityFromEUTRACommand::criticalExtensions_c1_mobilityFromEUTRACommand_r8_IsPresent() const
{
    return criticalExtensions_c1_mobilityFromEUTRACommand_r8_present;
}

MobilityFromEUTRACommand_r9_IEs* MobilityFromEUTRACommand::criticalExtensions_c1_mobilityFromEUTRACommand_r9_Set()
{
    criticalExtensions_c1_mobilityFromEUTRACommand_r9_present = true;
    return &criticalExtensions_c1_mobilityFromEUTRACommand_r9;
}

int MobilityFromEUTRACommand::criticalExtensions_c1_mobilityFromEUTRACommand_r9_Set(MobilityFromEUTRACommand_r9_IEs &value)
{
    criticalExtensions_c1_mobilityFromEUTRACommand_r9_present = true;
    criticalExtensions_c1_mobilityFromEUTRACommand_r9 = value;
    return 0;
}

const MobilityFromEUTRACommand_r9_IEs& MobilityFromEUTRACommand::criticalExtensions_c1_mobilityFromEUTRACommand_r9_Get() const
{
    return criticalExtensions_c1_mobilityFromEUTRACommand_r9;
}

std::string MobilityFromEUTRACommand::criticalExtensions_c1_mobilityFromEUTRACommand_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "mobilityFromEUTRACommand_r9:\n";
    out += criticalExtensions_c1_mobilityFromEUTRACommand_r9.ToString(indent+1);
    return out;
}

std::string MobilityFromEUTRACommand::criticalExtensions_c1_mobilityFromEUTRACommand_r9_ToStringNoNewLines() const
{
    std::string out = "mobilityFromEUTRACommand_r9:";
    out += criticalExtensions_c1_mobilityFromEUTRACommand_r9.ToStringNoNewLines();
    return out;
}

int MobilityFromEUTRACommand::criticalExtensions_c1_mobilityFromEUTRACommand_r9_Clear()
{
    criticalExtensions_c1_mobilityFromEUTRACommand_r9_present = false;
    return 0;
}

bool MobilityFromEUTRACommand::criticalExtensions_c1_mobilityFromEUTRACommand_r9_IsPresent() const
{
    return criticalExtensions_c1_mobilityFromEUTRACommand_r9_present;
}

