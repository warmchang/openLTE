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

#include "MobilityFromEUTRACommand_r8_IEs.h"

#include <cmath>

int MobilityFromEUTRACommand_r8_IEs::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(nonCriticalExtension_IsPresent());

    // Fields
    {
        if(0 != cs_FallbackIndicator_Pack(bits))
        {
            printf("MobilityFromEUTRACommand_r8_IEs:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != purpose_Pack(bits))
        {
            printf("MobilityFromEUTRACommand_r8_IEs:: field pack failure\n");
            return -1;
        }
    }
    if(nonCriticalExtension_IsPresent())
    {
        if(0 != nonCriticalExtension.Pack(bits))
        {
            printf("MobilityFromEUTRACommand_r8_IEs:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int MobilityFromEUTRACommand_r8_IEs::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int MobilityFromEUTRACommand_r8_IEs::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("MobilityFromEUTRACommand_r8_IEs::Unpack() index out of bounds for optional indiator nonCriticalExtension\n");
        return -1;
    }
    nonCriticalExtension_present = bits[idx++];

    // Fields
    {
        if(0 != cs_FallbackIndicator_Unpack(bits, idx))
        {
            printf("MobilityFromEUTRACommand_r8_IEs:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != purpose_Unpack(bits, idx))
        {
            printf("MobilityFromEUTRACommand_r8_IEs:: field unpack failure\n");
            return -1;
        }
    }
    if(nonCriticalExtension_present)
    {
        if(0 != nonCriticalExtension.Unpack(bits, idx))
        {
            printf("MobilityFromEUTRACommand_r8_IEs:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string MobilityFromEUTRACommand_r8_IEs::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "MobilityFromEUTRACommand_r8_IEs:\n";
    out += cs_FallbackIndicator_ToString(indent+1);
    out += purpose_ToString(indent+1);
    if(nonCriticalExtension_IsPresent())
        out += nonCriticalExtension_ToString(indent+1);
    return out;
}

std::string MobilityFromEUTRACommand_r8_IEs::ToStringNoNewLines() const
{
    std::string out = "MobilityFromEUTRACommand_r8_IEs:";
    out += cs_FallbackIndicator_ToStringNoNewLines();
    out += purpose_ToStringNoNewLines();
    if(nonCriticalExtension_IsPresent())
        out += nonCriticalExtension_ToStringNoNewLines();
    return out;
}

int MobilityFromEUTRACommand_r8_IEs::cs_FallbackIndicator_Pack(std::vector<uint8_t> &bits)
{
    if(!cs_FallbackIndicator_present)
    {
        printf("MobilityFromEUTRACommand_r8_IEs::cs_FallbackIndicator_Pack() presence failure\n");
        return -1;
    }
    bits.push_back(cs_FallbackIndicator_internal_value);
    return 0;
}

int MobilityFromEUTRACommand_r8_IEs::cs_FallbackIndicator_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return cs_FallbackIndicator_Unpack(bits, idx);
}

int MobilityFromEUTRACommand_r8_IEs::cs_FallbackIndicator_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    if((idx + 1) > bits.size())
    {
        printf("MobilityFromEUTRACommand_r8_IEs::cs_FallbackIndicator_Unpack() index out of bounds\n");
        return -1;
    }
    cs_FallbackIndicator_internal_value = bits[idx++];
    cs_FallbackIndicator_present = true;
    return 0;
}

bool MobilityFromEUTRACommand_r8_IEs::cs_FallbackIndicator_Value() const
{
    if(cs_FallbackIndicator_present)
        return cs_FallbackIndicator_internal_value;
    return false;
}

int MobilityFromEUTRACommand_r8_IEs::cs_FallbackIndicator_SetValue(bool value)
{
    cs_FallbackIndicator_internal_value = value;
    cs_FallbackIndicator_present = true;
    return 0;
}

std::string MobilityFromEUTRACommand_r8_IEs::cs_FallbackIndicator_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cs_FallbackIndicator = " + std::to_string(cs_FallbackIndicator_internal_value) + "\n";
    return out;
}

std::string MobilityFromEUTRACommand_r8_IEs::cs_FallbackIndicator_ToStringNoNewLines() const
{
    std::string out = "cs_FallbackIndicator=" + std::to_string(cs_FallbackIndicator_internal_value) + ",";
    return out;
}

int MobilityFromEUTRACommand_r8_IEs::cs_FallbackIndicator_Clear()
{
    cs_FallbackIndicator_present = false;
    return 0;
}

bool MobilityFromEUTRACommand_r8_IEs::cs_FallbackIndicator_IsPresent() const
{
    return cs_FallbackIndicator_present;
}

int MobilityFromEUTRACommand_r8_IEs::purpose_Pack(std::vector<uint8_t> &bits)
{
    if(!purpose_present)
    {
        printf("MobilityFromEUTRACommand_r8_IEs::purpose_Pack() presence failure\n");
        return -1;
    }
    // Extension indicator

    // Choice
    for(uint32_t i=0; i<1; i++)
        bits.push_back((purpose_internal_choice >> (1-i-1)) & 1);

    // Fields
    if(purpose_internal_choice == k_purpose_handover)
    {
        if(0 != purpose_handover.Pack(bits))
        {
            printf("MobilityFromEUTRACommand_r8_IEs::purpose_handover pack failure\n");
            return -1;
        }
    }
    if(purpose_internal_choice == k_purpose_cellChangeOrder)
    {
        if(0 != purpose_cellChangeOrder.Pack(bits))
        {
            printf("MobilityFromEUTRACommand_r8_IEs::purpose_cellChangeOrder pack failure\n");
            return -1;
        }
    }
    return 0;
}

int MobilityFromEUTRACommand_r8_IEs::purpose_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return purpose_Unpack(bits, idx);
}

int MobilityFromEUTRACommand_r8_IEs::purpose_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 1) > bits.size())
    {
        printf("MobilityFromEUTRACommand_r8_IEs::purpose_Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<1; i++)
        packed_val |= bits[idx++] << (1-i-1);

    if((MobilityFromEUTRACommand_r8_IEs::purpose_Enum)packed_val > k_purpose_cellChangeOrder)
    {
        printf("MobilityFromEUTRACommand_r8_IEs::purpose_Unpack() choice range failure\n");
        return -1;
    }
    purpose_internal_choice = (MobilityFromEUTRACommand_r8_IEs::purpose_Enum)packed_val;
    purpose_present = true;

    // Fields
    if(purpose_internal_choice == k_purpose_handover)
    {
        if(0 != purpose_handover.Unpack(bits, idx))
        {
            printf("MobilityFromEUTRACommand_r8_IEs::purpose_handover unpack failure\n");
            return -1;
        }
    }
    if(purpose_internal_choice == k_purpose_cellChangeOrder)
    {
        if(0 != purpose_cellChangeOrder.Unpack(bits, idx))
        {
            printf("MobilityFromEUTRACommand_r8_IEs::purpose_cellChangeOrder unpack failure\n");
            return -1;
        }
    }
    return 0;
}

MobilityFromEUTRACommand_r8_IEs::purpose_Enum MobilityFromEUTRACommand_r8_IEs::purpose_Choice() const
{
    if(purpose_present)
        return purpose_internal_choice;
    return (MobilityFromEUTRACommand_r8_IEs::purpose_Enum)0;
}

int MobilityFromEUTRACommand_r8_IEs::purpose_SetChoice(MobilityFromEUTRACommand_r8_IEs::purpose_Enum choice)
{
    purpose_internal_choice = choice;
    purpose_present = true;
    return 0;
}

std::string MobilityFromEUTRACommand_r8_IEs::purpose_ChoiceToString(purpose_Enum value) const
{
    if(k_purpose_handover == value)
        return "purpose_handover";
    if(k_purpose_cellChangeOrder == value)
        return "purpose_cellChangeOrder";
    return "";
}

uint64_t MobilityFromEUTRACommand_r8_IEs::purpose_NumberOfChoices() const
{
    return 2;
}

std::string MobilityFromEUTRACommand_r8_IEs::purpose_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "purpose = " + purpose_ChoiceToString(purpose_internal_choice) + ":\n";
    if(purpose_internal_choice == k_purpose_handover)
        out += purpose_handover.ToString(indent+1);
    if(purpose_internal_choice == k_purpose_cellChangeOrder)
        out += purpose_cellChangeOrder.ToString(indent+1);
    return out;
}

std::string MobilityFromEUTRACommand_r8_IEs::purpose_ToStringNoNewLines() const
{
    std::string out = "purpose=" + purpose_ChoiceToString(purpose_internal_choice) + ",";
    if(purpose_internal_choice == k_purpose_handover)
        out += purpose_handover.ToStringNoNewLines();
    if(purpose_internal_choice == k_purpose_cellChangeOrder)
        out += purpose_cellChangeOrder.ToStringNoNewLines();
    return out;
}

int MobilityFromEUTRACommand_r8_IEs::purpose_Clear()
{
    purpose_present = false;
    return 0;
}

bool MobilityFromEUTRACommand_r8_IEs::purpose_IsPresent() const
{
    return purpose_present;
}

Handover* MobilityFromEUTRACommand_r8_IEs::purpose_handover_Set()
{
    purpose_handover_present = true;
    return &purpose_handover;
}

int MobilityFromEUTRACommand_r8_IEs::purpose_handover_Set(Handover &value)
{
    purpose_handover_present = true;
    purpose_handover = value;
    return 0;
}

const Handover& MobilityFromEUTRACommand_r8_IEs::purpose_handover_Get() const
{
    return purpose_handover;
}

std::string MobilityFromEUTRACommand_r8_IEs::purpose_handover_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "handover:\n";
    out += purpose_handover.ToString(indent+1);
    return out;
}

std::string MobilityFromEUTRACommand_r8_IEs::purpose_handover_ToStringNoNewLines() const
{
    std::string out = "handover:";
    out += purpose_handover.ToStringNoNewLines();
    return out;
}

int MobilityFromEUTRACommand_r8_IEs::purpose_handover_Clear()
{
    purpose_handover_present = false;
    return 0;
}

bool MobilityFromEUTRACommand_r8_IEs::purpose_handover_IsPresent() const
{
    return purpose_handover_present;
}

CellChangeOrder* MobilityFromEUTRACommand_r8_IEs::purpose_cellChangeOrder_Set()
{
    purpose_cellChangeOrder_present = true;
    return &purpose_cellChangeOrder;
}

int MobilityFromEUTRACommand_r8_IEs::purpose_cellChangeOrder_Set(CellChangeOrder &value)
{
    purpose_cellChangeOrder_present = true;
    purpose_cellChangeOrder = value;
    return 0;
}

const CellChangeOrder& MobilityFromEUTRACommand_r8_IEs::purpose_cellChangeOrder_Get() const
{
    return purpose_cellChangeOrder;
}

std::string MobilityFromEUTRACommand_r8_IEs::purpose_cellChangeOrder_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cellChangeOrder:\n";
    out += purpose_cellChangeOrder.ToString(indent+1);
    return out;
}

std::string MobilityFromEUTRACommand_r8_IEs::purpose_cellChangeOrder_ToStringNoNewLines() const
{
    std::string out = "cellChangeOrder:";
    out += purpose_cellChangeOrder.ToStringNoNewLines();
    return out;
}

int MobilityFromEUTRACommand_r8_IEs::purpose_cellChangeOrder_Clear()
{
    purpose_cellChangeOrder_present = false;
    return 0;
}

bool MobilityFromEUTRACommand_r8_IEs::purpose_cellChangeOrder_IsPresent() const
{
    return purpose_cellChangeOrder_present;
}

MobilityFromEUTRACommand_v8a0_IEs* MobilityFromEUTRACommand_r8_IEs::nonCriticalExtension_Set()
{
    nonCriticalExtension_present = true;
    return &nonCriticalExtension;
}

int MobilityFromEUTRACommand_r8_IEs::nonCriticalExtension_Set(MobilityFromEUTRACommand_v8a0_IEs &value)
{
    nonCriticalExtension_present = true;
    nonCriticalExtension = value;
    return 0;
}

const MobilityFromEUTRACommand_v8a0_IEs& MobilityFromEUTRACommand_r8_IEs::nonCriticalExtension_Get() const
{
    return nonCriticalExtension;
}

std::string MobilityFromEUTRACommand_r8_IEs::nonCriticalExtension_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "nonCriticalExtension:\n";
    out += nonCriticalExtension.ToString(indent+1);
    return out;
}

std::string MobilityFromEUTRACommand_r8_IEs::nonCriticalExtension_ToStringNoNewLines() const
{
    std::string out = "nonCriticalExtension:";
    out += nonCriticalExtension.ToStringNoNewLines();
    return out;
}

int MobilityFromEUTRACommand_r8_IEs::nonCriticalExtension_Clear()
{
    nonCriticalExtension_present = false;
    return 0;
}

bool MobilityFromEUTRACommand_r8_IEs::nonCriticalExtension_IsPresent() const
{
    return nonCriticalExtension_present;
}

