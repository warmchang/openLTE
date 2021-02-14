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

#include "CrossCarrierSchedulingConfig_r10.h"

#include <cmath>

int CrossCarrierSchedulingConfig_r10::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator
    bits.push_back(0);

    // Optional indicators

    // Fields
    {
        if(0 != schedulingCellInfo_Pack(bits))
        {
            printf("CrossCarrierSchedulingConfig_r10:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int CrossCarrierSchedulingConfig_r10::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int CrossCarrierSchedulingConfig_r10::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("CrossCarrierSchedulingConfig_r10::Unpack() index out of bounds for extension\n");
        return -1;
    }
    idx++;

    // Optional indicators

    // Fields
    {
        if(0 != schedulingCellInfo_Unpack(bits, idx))
        {
            printf("CrossCarrierSchedulingConfig_r10:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string CrossCarrierSchedulingConfig_r10::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "CrossCarrierSchedulingConfig_r10:\n";
    out += schedulingCellInfo_ToString(indent+1);
    return out;
}

std::string CrossCarrierSchedulingConfig_r10::ToStringNoNewLines() const
{
    std::string out = "CrossCarrierSchedulingConfig_r10:";
    out += schedulingCellInfo_ToStringNoNewLines();
    return out;
}

int CrossCarrierSchedulingConfig_r10::schedulingCellInfo_Pack(std::vector<uint8_t> &bits)
{
    if(!schedulingCellInfo_present)
    {
        printf("CrossCarrierSchedulingConfig_r10::schedulingCellInfo_Pack() presence failure\n");
        return -1;
    }
    // Extension indicator

    // Choice
    for(uint32_t i=0; i<1; i++)
        bits.push_back((schedulingCellInfo_internal_choice >> (1-i-1)) & 1);

    // Fields
    if(schedulingCellInfo_internal_choice == k_schedulingCellInfo_own)
    {
        if(0 != schedulingCellInfo_own_value.Pack(bits))
        {
            printf("CrossCarrierSchedulingConfig_r10::schedulingCellInfo_own pack failure\n");
            return -1;
        }
    }
    if(schedulingCellInfo_internal_choice == k_schedulingCellInfo_other)
    {
        if(0 != schedulingCellInfo_other_value.Pack(bits))
        {
            printf("CrossCarrierSchedulingConfig_r10::schedulingCellInfo_other pack failure\n");
            return -1;
        }
    }
    return 0;
}

int CrossCarrierSchedulingConfig_r10::schedulingCellInfo_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return schedulingCellInfo_Unpack(bits, idx);
}

int CrossCarrierSchedulingConfig_r10::schedulingCellInfo_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 1) > bits.size())
    {
        printf("CrossCarrierSchedulingConfig_r10::schedulingCellInfo_Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<1; i++)
        packed_val |= bits[idx++] << (1-i-1);

    if((CrossCarrierSchedulingConfig_r10::schedulingCellInfo_Enum)packed_val > k_schedulingCellInfo_other)
    {
        printf("CrossCarrierSchedulingConfig_r10::schedulingCellInfo_Unpack() choice range failure\n");
        return -1;
    }
    schedulingCellInfo_internal_choice = (CrossCarrierSchedulingConfig_r10::schedulingCellInfo_Enum)packed_val;
    schedulingCellInfo_present = true;

    // Fields
    if(schedulingCellInfo_internal_choice == k_schedulingCellInfo_own)
    {
        if(0 != schedulingCellInfo_own_value.Unpack(bits, idx))
        {
            printf("CrossCarrierSchedulingConfig_r10::schedulingCellInfo_own unpack failure\n");
            return -1;
        }
    }
    if(schedulingCellInfo_internal_choice == k_schedulingCellInfo_other)
    {
        if(0 != schedulingCellInfo_other_value.Unpack(bits, idx))
        {
            printf("CrossCarrierSchedulingConfig_r10::schedulingCellInfo_other unpack failure\n");
            return -1;
        }
    }
    return 0;
}

CrossCarrierSchedulingConfig_r10::schedulingCellInfo_Enum CrossCarrierSchedulingConfig_r10::schedulingCellInfo_Choice() const
{
    if(schedulingCellInfo_present)
        return schedulingCellInfo_internal_choice;
    return (CrossCarrierSchedulingConfig_r10::schedulingCellInfo_Enum)0;
}

int CrossCarrierSchedulingConfig_r10::schedulingCellInfo_SetChoice(CrossCarrierSchedulingConfig_r10::schedulingCellInfo_Enum choice)
{
    schedulingCellInfo_internal_choice = choice;
    schedulingCellInfo_present = true;
    return 0;
}

std::string CrossCarrierSchedulingConfig_r10::schedulingCellInfo_ChoiceToString(schedulingCellInfo_Enum value) const
{
    if(k_schedulingCellInfo_own == value)
        return "schedulingCellInfo_own";
    if(k_schedulingCellInfo_other == value)
        return "schedulingCellInfo_other";
    return "";
}

uint64_t CrossCarrierSchedulingConfig_r10::schedulingCellInfo_NumberOfChoices() const
{
    return 2;
}

std::string CrossCarrierSchedulingConfig_r10::schedulingCellInfo_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "schedulingCellInfo = " + schedulingCellInfo_ChoiceToString(schedulingCellInfo_internal_choice) + ":\n";
    if(schedulingCellInfo_internal_choice == k_schedulingCellInfo_own)
        out += schedulingCellInfo_own_value.ToString(indent+1);
    if(schedulingCellInfo_internal_choice == k_schedulingCellInfo_other)
        out += schedulingCellInfo_other_value.ToString(indent+1);
    return out;
}

std::string CrossCarrierSchedulingConfig_r10::schedulingCellInfo_ToStringNoNewLines() const
{
    std::string out = "schedulingCellInfo=" + schedulingCellInfo_ChoiceToString(schedulingCellInfo_internal_choice) + ",";
    if(schedulingCellInfo_internal_choice == k_schedulingCellInfo_own)
        out += schedulingCellInfo_own_value.ToStringNoNewLines();
    if(schedulingCellInfo_internal_choice == k_schedulingCellInfo_other)
        out += schedulingCellInfo_other_value.ToStringNoNewLines();
    return out;
}

int CrossCarrierSchedulingConfig_r10::schedulingCellInfo_Clear()
{
    schedulingCellInfo_present = false;
    return 0;
}

bool CrossCarrierSchedulingConfig_r10::schedulingCellInfo_IsPresent() const
{
    return schedulingCellInfo_present;
}

int CrossCarrierSchedulingConfig_r10::schedulingCellInfo_own::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != cif_Presence_Pack(bits))
        {
            printf("CrossCarrierSchedulingConfig_r10::schedulingCellInfo_own:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int CrossCarrierSchedulingConfig_r10::schedulingCellInfo_own::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int CrossCarrierSchedulingConfig_r10::schedulingCellInfo_own::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != cif_Presence_Unpack(bits, idx))
        {
            printf("CrossCarrierSchedulingConfig_r10::schedulingCellInfo_own:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string CrossCarrierSchedulingConfig_r10::schedulingCellInfo_own::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "own:\n";
    out += cif_Presence_ToString(indent+1);
    return out;
}

std::string CrossCarrierSchedulingConfig_r10::schedulingCellInfo_own::ToStringNoNewLines() const
{
    std::string out = "own:";
    out += cif_Presence_ToStringNoNewLines();
    return out;
}

int CrossCarrierSchedulingConfig_r10::schedulingCellInfo_own::cif_Presence_Pack(std::vector<uint8_t> &bits)
{
    if(!cif_Presence_present)
    {
        printf("CrossCarrierSchedulingConfig_r10::schedulingCellInfo_own::cif_Presence_Pack() presence failure\n");
        return -1;
    }
    bits.push_back(cif_Presence_internal_value);
    return 0;
}

int CrossCarrierSchedulingConfig_r10::schedulingCellInfo_own::cif_Presence_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return cif_Presence_Unpack(bits, idx);
}

int CrossCarrierSchedulingConfig_r10::schedulingCellInfo_own::cif_Presence_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    if((idx + 1) > bits.size())
    {
        printf("CrossCarrierSchedulingConfig_r10::schedulingCellInfo_own::cif_Presence_Unpack() index out of bounds\n");
        return -1;
    }
    cif_Presence_internal_value = bits[idx++];
    cif_Presence_present = true;
    return 0;
}

bool CrossCarrierSchedulingConfig_r10::schedulingCellInfo_own::cif_Presence_Value() const
{
    if(cif_Presence_present)
        return cif_Presence_internal_value;
    return false;
}

int CrossCarrierSchedulingConfig_r10::schedulingCellInfo_own::cif_Presence_SetValue(bool value)
{
    cif_Presence_internal_value = value;
    cif_Presence_present = true;
    return 0;
}

std::string CrossCarrierSchedulingConfig_r10::schedulingCellInfo_own::cif_Presence_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cif_Presence = " + std::to_string(cif_Presence_internal_value) + "\n";
    return out;
}

std::string CrossCarrierSchedulingConfig_r10::schedulingCellInfo_own::cif_Presence_ToStringNoNewLines() const
{
    std::string out = "cif_Presence=" + std::to_string(cif_Presence_internal_value) + ",";
    return out;
}

int CrossCarrierSchedulingConfig_r10::schedulingCellInfo_own::cif_Presence_Clear()
{
    cif_Presence_present = false;
    return 0;
}

bool CrossCarrierSchedulingConfig_r10::schedulingCellInfo_own::cif_Presence_IsPresent() const
{
    return cif_Presence_present;
}

int CrossCarrierSchedulingConfig_r10::schedulingCellInfo_other::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != schedulingCellId_r10.Pack(bits))
        {
            printf("CrossCarrierSchedulingConfig_r10::schedulingCellInfo_other:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != pdsch_Start_r10_Pack(bits))
        {
            printf("CrossCarrierSchedulingConfig_r10::schedulingCellInfo_other:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int CrossCarrierSchedulingConfig_r10::schedulingCellInfo_other::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int CrossCarrierSchedulingConfig_r10::schedulingCellInfo_other::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != schedulingCellId_r10.Unpack(bits, idx))
        {
            printf("CrossCarrierSchedulingConfig_r10::schedulingCellInfo_other:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != pdsch_Start_r10_Unpack(bits, idx))
        {
            printf("CrossCarrierSchedulingConfig_r10::schedulingCellInfo_other:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string CrossCarrierSchedulingConfig_r10::schedulingCellInfo_other::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "other:\n";
    out += schedulingCellId_r10_ToString(indent+1);
    out += pdsch_Start_r10_ToString(indent+1);
    return out;
}

std::string CrossCarrierSchedulingConfig_r10::schedulingCellInfo_other::ToStringNoNewLines() const
{
    std::string out = "other:";
    out += schedulingCellId_r10_ToStringNoNewLines();
    out += pdsch_Start_r10_ToStringNoNewLines();
    return out;
}

ServCellIndex_r10* CrossCarrierSchedulingConfig_r10::schedulingCellInfo_other::schedulingCellId_r10_Set()
{
    schedulingCellId_r10_present = true;
    return &schedulingCellId_r10;
}

int CrossCarrierSchedulingConfig_r10::schedulingCellInfo_other::schedulingCellId_r10_Set(ServCellIndex_r10 &value)
{
    schedulingCellId_r10_present = true;
    schedulingCellId_r10 = value;
    return 0;
}

const ServCellIndex_r10& CrossCarrierSchedulingConfig_r10::schedulingCellInfo_other::schedulingCellId_r10_Get() const
{
    return schedulingCellId_r10;
}

std::string CrossCarrierSchedulingConfig_r10::schedulingCellInfo_other::schedulingCellId_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "schedulingCellId_r10:\n";
    out += schedulingCellId_r10.ToString(indent+1);
    return out;
}

std::string CrossCarrierSchedulingConfig_r10::schedulingCellInfo_other::schedulingCellId_r10_ToStringNoNewLines() const
{
    std::string out = "schedulingCellId_r10:";
    out += schedulingCellId_r10.ToStringNoNewLines();
    return out;
}

int CrossCarrierSchedulingConfig_r10::schedulingCellInfo_other::schedulingCellId_r10_Clear()
{
    schedulingCellId_r10_present = false;
    return 0;
}

bool CrossCarrierSchedulingConfig_r10::schedulingCellInfo_other::schedulingCellId_r10_IsPresent() const
{
    return schedulingCellId_r10_present;
}

int CrossCarrierSchedulingConfig_r10::schedulingCellInfo_other::pdsch_Start_r10_Pack(std::vector<uint8_t> &bits)
{
    if(!pdsch_Start_r10_present)
    {
        printf("CrossCarrierSchedulingConfig_r10::schedulingCellInfo_other::pdsch_Start_r10_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = pdsch_Start_r10_internal_value - (1);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (4 - 1))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int CrossCarrierSchedulingConfig_r10::schedulingCellInfo_other::pdsch_Start_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return pdsch_Start_r10_Unpack(bits, idx);
}

int CrossCarrierSchedulingConfig_r10::schedulingCellInfo_other::pdsch_Start_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (4 - 1))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("CrossCarrierSchedulingConfig_r10::schedulingCellInfo_other::pdsch_Start_r10_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    pdsch_Start_r10_internal_value = packed_val + 1;
    pdsch_Start_r10_present = true;
    return 0;
}

int64_t CrossCarrierSchedulingConfig_r10::schedulingCellInfo_other::pdsch_Start_r10_Value() const
{
    if(pdsch_Start_r10_present)
        return pdsch_Start_r10_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int CrossCarrierSchedulingConfig_r10::schedulingCellInfo_other::pdsch_Start_r10_SetValue(int64_t value)
{
    if(value < 1 || value > 4)
    {
        printf("CrossCarrierSchedulingConfig_r10::schedulingCellInfo_other::pdsch_Start_r10_SetValue() range failure\n");
        return -1;
    }
    pdsch_Start_r10_internal_value = value;
    pdsch_Start_r10_present = true;
    return 0;
}

std::string CrossCarrierSchedulingConfig_r10::schedulingCellInfo_other::pdsch_Start_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "pdsch_Start_r10 = " + std::to_string(pdsch_Start_r10_internal_value) + "\n";
    return out;
}

std::string CrossCarrierSchedulingConfig_r10::schedulingCellInfo_other::pdsch_Start_r10_ToStringNoNewLines() const
{
    std::string out = "pdsch_Start_r10=" + std::to_string(pdsch_Start_r10_internal_value) + ",";
    return out;
}

int CrossCarrierSchedulingConfig_r10::schedulingCellInfo_other::pdsch_Start_r10_Clear()
{
    pdsch_Start_r10_present = false;
    return 0;
}

bool CrossCarrierSchedulingConfig_r10::schedulingCellInfo_other::pdsch_Start_r10_IsPresent() const
{
    return pdsch_Start_r10_present;
}

