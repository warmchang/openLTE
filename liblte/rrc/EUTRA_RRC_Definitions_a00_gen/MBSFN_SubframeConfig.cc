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

#include "MBSFN_SubframeConfig.h"

#include <cmath>

int MBSFN_SubframeConfig::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != radioframeAllocationPeriod_Pack(bits))
        {
            printf("MBSFN_SubframeConfig:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != radioframeAllocationOffset_Pack(bits))
        {
            printf("MBSFN_SubframeConfig:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != subframeAllocation_Pack(bits))
        {
            printf("MBSFN_SubframeConfig:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int MBSFN_SubframeConfig::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int MBSFN_SubframeConfig::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != radioframeAllocationPeriod_Unpack(bits, idx))
        {
            printf("MBSFN_SubframeConfig:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != radioframeAllocationOffset_Unpack(bits, idx))
        {
            printf("MBSFN_SubframeConfig:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != subframeAllocation_Unpack(bits, idx))
        {
            printf("MBSFN_SubframeConfig:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string MBSFN_SubframeConfig::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "MBSFN_SubframeConfig:\n";
    out += radioframeAllocationPeriod_ToString(indent+1);
    out += radioframeAllocationOffset_ToString(indent+1);
    out += subframeAllocation_ToString(indent+1);
    return out;
}

std::string MBSFN_SubframeConfig::ToStringNoNewLines() const
{
    std::string out = "MBSFN_SubframeConfig:";
    out += radioframeAllocationPeriod_ToStringNoNewLines();
    out += radioframeAllocationOffset_ToStringNoNewLines();
    out += subframeAllocation_ToStringNoNewLines();
    return out;
}

int MBSFN_SubframeConfig::radioframeAllocationPeriod_Pack(std::vector<uint8_t> &bits)
{
    if(!radioframeAllocationPeriod_present)
    {
        printf("MBSFN_SubframeConfig::radioframeAllocationPeriod_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 3;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((radioframeAllocationPeriod_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int MBSFN_SubframeConfig::radioframeAllocationPeriod_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return radioframeAllocationPeriod_Unpack(bits, idx);
}

int MBSFN_SubframeConfig::radioframeAllocationPeriod_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 3;
    if((idx + N_bits) > bits.size())
    {
        printf("MBSFN_SubframeConfig::radioframeAllocationPeriod_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 5)
    {
        printf("MBSFN_SubframeConfig::radioframeAllocationPeriod_Unpack() max failure\n");
        return -1;
    }
    radioframeAllocationPeriod_internal_value = (radioframeAllocationPeriod_Enum)packed_val;
    radioframeAllocationPeriod_present = true;
    return 0;
}

MBSFN_SubframeConfig::radioframeAllocationPeriod_Enum MBSFN_SubframeConfig::radioframeAllocationPeriod_Value() const
{
    if(radioframeAllocationPeriod_present)
        return radioframeAllocationPeriod_internal_value;
    return (MBSFN_SubframeConfig::radioframeAllocationPeriod_Enum)0;
}

int MBSFN_SubframeConfig::radioframeAllocationPeriod_SetValue(radioframeAllocationPeriod_Enum value)
{
    radioframeAllocationPeriod_internal_value = value;
    radioframeAllocationPeriod_present = true;
    return 0;
}

int MBSFN_SubframeConfig::radioframeAllocationPeriod_SetValue(std::string value)
{
    if("n1" == value)
    {
        radioframeAllocationPeriod_internal_value = k_radioframeAllocationPeriod_n1;
        radioframeAllocationPeriod_present = true;
        return 0;
    }
    if("n2" == value)
    {
        radioframeAllocationPeriod_internal_value = k_radioframeAllocationPeriod_n2;
        radioframeAllocationPeriod_present = true;
        return 0;
    }
    if("n4" == value)
    {
        radioframeAllocationPeriod_internal_value = k_radioframeAllocationPeriod_n4;
        radioframeAllocationPeriod_present = true;
        return 0;
    }
    if("n8" == value)
    {
        radioframeAllocationPeriod_internal_value = k_radioframeAllocationPeriod_n8;
        radioframeAllocationPeriod_present = true;
        return 0;
    }
    if("n16" == value)
    {
        radioframeAllocationPeriod_internal_value = k_radioframeAllocationPeriod_n16;
        radioframeAllocationPeriod_present = true;
        return 0;
    }
    if("n32" == value)
    {
        radioframeAllocationPeriod_internal_value = k_radioframeAllocationPeriod_n32;
        radioframeAllocationPeriod_present = true;
        return 0;
    }
    return 1;
}

std::string MBSFN_SubframeConfig::radioframeAllocationPeriod_ValueToString(radioframeAllocationPeriod_Enum value) const
{
    if(k_radioframeAllocationPeriod_n1 == value)
        return "n1";
    if(k_radioframeAllocationPeriod_n2 == value)
        return "n2";
    if(k_radioframeAllocationPeriod_n4 == value)
        return "n4";
    if(k_radioframeAllocationPeriod_n8 == value)
        return "n8";
    if(k_radioframeAllocationPeriod_n16 == value)
        return "n16";
    if(k_radioframeAllocationPeriod_n32 == value)
        return "n32";
    return "";
}

uint64_t MBSFN_SubframeConfig::radioframeAllocationPeriod_NumberOfValues() const
{
    return 6;
}

std::string MBSFN_SubframeConfig::radioframeAllocationPeriod_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "radioframeAllocationPeriod = " + radioframeAllocationPeriod_ValueToString(radioframeAllocationPeriod_internal_value) + "\n";
    return out;
}

std::string MBSFN_SubframeConfig::radioframeAllocationPeriod_ToStringNoNewLines() const
{
    std::string out = "radioframeAllocationPeriod=" + radioframeAllocationPeriod_ValueToString(radioframeAllocationPeriod_internal_value) + ",";
    return out;
}

int MBSFN_SubframeConfig::radioframeAllocationPeriod_Clear()
{
    radioframeAllocationPeriod_present = false;
    return 0;
}

bool MBSFN_SubframeConfig::radioframeAllocationPeriod_IsPresent() const
{
    return radioframeAllocationPeriod_present;
}

int MBSFN_SubframeConfig::radioframeAllocationOffset_Pack(std::vector<uint8_t> &bits)
{
    if(!radioframeAllocationOffset_present)
    {
        printf("MBSFN_SubframeConfig::radioframeAllocationOffset_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = radioframeAllocationOffset_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (7 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int MBSFN_SubframeConfig::radioframeAllocationOffset_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return radioframeAllocationOffset_Unpack(bits, idx);
}

int MBSFN_SubframeConfig::radioframeAllocationOffset_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (7 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("MBSFN_SubframeConfig::radioframeAllocationOffset_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    radioframeAllocationOffset_internal_value = packed_val + 0;
    radioframeAllocationOffset_present = true;
    return 0;
}

int64_t MBSFN_SubframeConfig::radioframeAllocationOffset_Value() const
{
    if(radioframeAllocationOffset_present)
        return radioframeAllocationOffset_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int MBSFN_SubframeConfig::radioframeAllocationOffset_SetValue(int64_t value)
{
    if(value < 0 || value > 7)
    {
        printf("MBSFN_SubframeConfig::radioframeAllocationOffset_SetValue() range failure\n");
        return -1;
    }
    radioframeAllocationOffset_internal_value = value;
    radioframeAllocationOffset_present = true;
    return 0;
}

std::string MBSFN_SubframeConfig::radioframeAllocationOffset_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "radioframeAllocationOffset = " + std::to_string(radioframeAllocationOffset_internal_value) + "\n";
    return out;
}

std::string MBSFN_SubframeConfig::radioframeAllocationOffset_ToStringNoNewLines() const
{
    std::string out = "radioframeAllocationOffset=" + std::to_string(radioframeAllocationOffset_internal_value) + ",";
    return out;
}

int MBSFN_SubframeConfig::radioframeAllocationOffset_Clear()
{
    radioframeAllocationOffset_present = false;
    return 0;
}

bool MBSFN_SubframeConfig::radioframeAllocationOffset_IsPresent() const
{
    return radioframeAllocationOffset_present;
}

int MBSFN_SubframeConfig::subframeAllocation_Pack(std::vector<uint8_t> &bits)
{
    if(!subframeAllocation_present)
    {
        printf("MBSFN_SubframeConfig::subframeAllocation_Pack() presence failure\n");
        return -1;
    }
    // Extension indicator

    // Choice
    for(uint32_t i=0; i<1; i++)
        bits.push_back((subframeAllocation_internal_choice >> (1-i-1)) & 1);

    // Fields
    if(subframeAllocation_internal_choice == k_subframeAllocation_oneFrame)
    {
        if(0 != subframeAllocation_oneFrame_Pack(bits))
        {
            printf("MBSFN_SubframeConfig::subframeAllocation_oneFrame pack failure\n");
            return -1;
        }
    }
    if(subframeAllocation_internal_choice == k_subframeAllocation_fourFrames)
    {
        if(0 != subframeAllocation_fourFrames_Pack(bits))
        {
            printf("MBSFN_SubframeConfig::subframeAllocation_fourFrames pack failure\n");
            return -1;
        }
    }
    return 0;
}

int MBSFN_SubframeConfig::subframeAllocation_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return subframeAllocation_Unpack(bits, idx);
}

int MBSFN_SubframeConfig::subframeAllocation_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 1) > bits.size())
    {
        printf("MBSFN_SubframeConfig::subframeAllocation_Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<1; i++)
        packed_val |= bits[idx++] << (1-i-1);

    if((MBSFN_SubframeConfig::subframeAllocation_Enum)packed_val > k_subframeAllocation_fourFrames)
    {
        printf("MBSFN_SubframeConfig::subframeAllocation_Unpack() choice range failure\n");
        return -1;
    }
    subframeAllocation_internal_choice = (MBSFN_SubframeConfig::subframeAllocation_Enum)packed_val;
    subframeAllocation_present = true;

    // Fields
    if(subframeAllocation_internal_choice == k_subframeAllocation_oneFrame)
    {
        if(0 != subframeAllocation_oneFrame_Unpack(bits, idx))
        {
            printf("MBSFN_SubframeConfig::subframeAllocation_oneFrame unpack failure\n");
            return -1;
        }
    }
    if(subframeAllocation_internal_choice == k_subframeAllocation_fourFrames)
    {
        if(0 != subframeAllocation_fourFrames_Unpack(bits, idx))
        {
            printf("MBSFN_SubframeConfig::subframeAllocation_fourFrames unpack failure\n");
            return -1;
        }
    }
    return 0;
}

MBSFN_SubframeConfig::subframeAllocation_Enum MBSFN_SubframeConfig::subframeAllocation_Choice() const
{
    if(subframeAllocation_present)
        return subframeAllocation_internal_choice;
    return (MBSFN_SubframeConfig::subframeAllocation_Enum)0;
}

int MBSFN_SubframeConfig::subframeAllocation_SetChoice(MBSFN_SubframeConfig::subframeAllocation_Enum choice)
{
    subframeAllocation_internal_choice = choice;
    subframeAllocation_present = true;
    return 0;
}

std::string MBSFN_SubframeConfig::subframeAllocation_ChoiceToString(subframeAllocation_Enum value) const
{
    if(k_subframeAllocation_oneFrame == value)
        return "subframeAllocation_oneFrame";
    if(k_subframeAllocation_fourFrames == value)
        return "subframeAllocation_fourFrames";
    return "";
}

uint64_t MBSFN_SubframeConfig::subframeAllocation_NumberOfChoices() const
{
    return 2;
}

std::string MBSFN_SubframeConfig::subframeAllocation_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "subframeAllocation = " + subframeAllocation_ChoiceToString(subframeAllocation_internal_choice) + ":\n";
    if(subframeAllocation_internal_choice == k_subframeAllocation_oneFrame)
        out += subframeAllocation_oneFrame_ToString(indent+1);
    if(subframeAllocation_internal_choice == k_subframeAllocation_fourFrames)
        out += subframeAllocation_fourFrames_ToString(indent+1);
    return out;
}

std::string MBSFN_SubframeConfig::subframeAllocation_ToStringNoNewLines() const
{
    std::string out = "subframeAllocation=" + subframeAllocation_ChoiceToString(subframeAllocation_internal_choice) + ",";
    if(subframeAllocation_internal_choice == k_subframeAllocation_oneFrame)
        out += subframeAllocation_oneFrame_ToStringNoNewLines();
    if(subframeAllocation_internal_choice == k_subframeAllocation_fourFrames)
        out += subframeAllocation_fourFrames_ToStringNoNewLines();
    return out;
}

int MBSFN_SubframeConfig::subframeAllocation_Clear()
{
    subframeAllocation_present = false;
    return 0;
}

bool MBSFN_SubframeConfig::subframeAllocation_IsPresent() const
{
    return subframeAllocation_present;
}

int MBSFN_SubframeConfig::subframeAllocation_oneFrame_Pack(std::vector<uint8_t> &bits)
{
    if(!subframeAllocation_oneFrame_present)
    {
        printf("MBSFN_SubframeConfig::subframeAllocation_oneFrame_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 6;
    if(size < 6 || size > 6)
    {
        printf("MBSFN_SubframeConfig::subframeAllocation_oneFrame_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((subframeAllocation_oneFrame_internal_value >> (6-i-1)) & 1);
    return 0;
}

int MBSFN_SubframeConfig::subframeAllocation_oneFrame_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return subframeAllocation_oneFrame_Unpack(bits, idx);
}

int MBSFN_SubframeConfig::subframeAllocation_oneFrame_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 6;
    if(size < 6 || size > 6)
    {
        printf("MBSFN_SubframeConfig::subframeAllocation_oneFrame_Unpack() size failure\n");
        return -1;
    }
    subframeAllocation_oneFrame_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("MBSFN_SubframeConfig::subframeAllocation_oneFrame_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        subframeAllocation_oneFrame_internal_value |= (uint8_t)bits[idx++] << (uint8_t)(6-i-1);
    subframeAllocation_oneFrame_present = true;
    return 0;
}

uint8_t MBSFN_SubframeConfig::subframeAllocation_oneFrame_Value() const
{
    if(subframeAllocation_oneFrame_present)
        return subframeAllocation_oneFrame_internal_value;
    uint8_t tmp = 0;
    return tmp;
}

int MBSFN_SubframeConfig::subframeAllocation_oneFrame_SetValue(uint8_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 6)
    {
        printf("MBSFN_SubframeConfig::subframeAllocation_oneFrame_SetValue() size failure\n");
        return -1;
    }
    subframeAllocation_oneFrame_internal_value = value;
    subframeAllocation_oneFrame_present = true;
    return 0;
}

std::string MBSFN_SubframeConfig::subframeAllocation_oneFrame_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "oneFrame = ";
    out += std::to_string(subframeAllocation_oneFrame_internal_value);
    out += "\n";
    return out;
}

std::string MBSFN_SubframeConfig::subframeAllocation_oneFrame_ToStringNoNewLines() const
{
    std::string out = "oneFrame=";
    out += std::to_string(subframeAllocation_oneFrame_internal_value);
    out += ",";
    return out;
}

int MBSFN_SubframeConfig::subframeAllocation_oneFrame_Clear()
{
    subframeAllocation_oneFrame_present = false;
    return 0;
}

bool MBSFN_SubframeConfig::subframeAllocation_oneFrame_IsPresent() const
{
    return subframeAllocation_oneFrame_present;
}

int MBSFN_SubframeConfig::subframeAllocation_fourFrames_Pack(std::vector<uint8_t> &bits)
{
    if(!subframeAllocation_fourFrames_present)
    {
        printf("MBSFN_SubframeConfig::subframeAllocation_fourFrames_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 24;
    if(size < 24 || size > 24)
    {
        printf("MBSFN_SubframeConfig::subframeAllocation_fourFrames_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((subframeAllocation_fourFrames_internal_value >> (24-i-1)) & 1);
    return 0;
}

int MBSFN_SubframeConfig::subframeAllocation_fourFrames_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return subframeAllocation_fourFrames_Unpack(bits, idx);
}

int MBSFN_SubframeConfig::subframeAllocation_fourFrames_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 24;
    if(size < 24 || size > 24)
    {
        printf("MBSFN_SubframeConfig::subframeAllocation_fourFrames_Unpack() size failure\n");
        return -1;
    }
    subframeAllocation_fourFrames_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("MBSFN_SubframeConfig::subframeAllocation_fourFrames_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        subframeAllocation_fourFrames_internal_value |= (uint32_t)bits[idx++] << (uint32_t)(24-i-1);
    subframeAllocation_fourFrames_present = true;
    return 0;
}

uint32_t MBSFN_SubframeConfig::subframeAllocation_fourFrames_Value() const
{
    if(subframeAllocation_fourFrames_present)
        return subframeAllocation_fourFrames_internal_value;
    uint32_t tmp = 0;
    return tmp;
}

int MBSFN_SubframeConfig::subframeAllocation_fourFrames_SetValue(uint32_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 24)
    {
        printf("MBSFN_SubframeConfig::subframeAllocation_fourFrames_SetValue() size failure\n");
        return -1;
    }
    subframeAllocation_fourFrames_internal_value = value;
    subframeAllocation_fourFrames_present = true;
    return 0;
}

std::string MBSFN_SubframeConfig::subframeAllocation_fourFrames_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "fourFrames = ";
    out += std::to_string(subframeAllocation_fourFrames_internal_value);
    out += "\n";
    return out;
}

std::string MBSFN_SubframeConfig::subframeAllocation_fourFrames_ToStringNoNewLines() const
{
    std::string out = "fourFrames=";
    out += std::to_string(subframeAllocation_fourFrames_internal_value);
    out += ",";
    return out;
}

int MBSFN_SubframeConfig::subframeAllocation_fourFrames_Clear()
{
    subframeAllocation_fourFrames_present = false;
    return 0;
}

bool MBSFN_SubframeConfig::subframeAllocation_fourFrames_IsPresent() const
{
    return subframeAllocation_fourFrames_present;
}

