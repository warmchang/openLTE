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

#include "AntennaInfoDedicated_v920.h"

#include <cmath>

int AntennaInfoDedicated_v920::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(codebookSubsetRestriction_v920_IsPresent());

    // Fields
    if(codebookSubsetRestriction_v920_IsPresent())
    {
        if(0 != codebookSubsetRestriction_v920_Pack(bits))
        {
            printf("AntennaInfoDedicated_v920:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int AntennaInfoDedicated_v920::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int AntennaInfoDedicated_v920::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("AntennaInfoDedicated_v920::Unpack() index out of bounds for optional indiator codebookSubsetRestriction_v920\n");
        return -1;
    }
    codebookSubsetRestriction_v920_present = bits[idx++];

    // Fields
    if(codebookSubsetRestriction_v920_present)
    {
        if(0 != codebookSubsetRestriction_v920_Unpack(bits, idx))
        {
            printf("AntennaInfoDedicated_v920:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string AntennaInfoDedicated_v920::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "AntennaInfoDedicated_v920:\n";
    if(codebookSubsetRestriction_v920_IsPresent())
        out += codebookSubsetRestriction_v920_ToString(indent+1);
    return out;
}

std::string AntennaInfoDedicated_v920::ToStringNoNewLines() const
{
    std::string out = "AntennaInfoDedicated_v920:";
    if(codebookSubsetRestriction_v920_IsPresent())
        out += codebookSubsetRestriction_v920_ToStringNoNewLines();
    return out;
}

int AntennaInfoDedicated_v920::codebookSubsetRestriction_v920_Pack(std::vector<uint8_t> &bits)
{
    if(!codebookSubsetRestriction_v920_present)
    {
        printf("AntennaInfoDedicated_v920::codebookSubsetRestriction_v920_Pack() presence failure\n");
        return -1;
    }
    // Extension indicator

    // Choice
    for(uint32_t i=0; i<1; i++)
        bits.push_back((codebookSubsetRestriction_v920_internal_choice >> (1-i-1)) & 1);

    // Fields
    if(codebookSubsetRestriction_v920_internal_choice == k_codebookSubsetRestriction_v920_n2TxAntenna_tm8_r9)
    {
        if(0 != codebookSubsetRestriction_v920_n2TxAntenna_tm8_r9_Pack(bits))
        {
            printf("AntennaInfoDedicated_v920::codebookSubsetRestriction_v920_n2TxAntenna_tm8_r9 pack failure\n");
            return -1;
        }
    }
    if(codebookSubsetRestriction_v920_internal_choice == k_codebookSubsetRestriction_v920_n4TxAntenna_tm8_r9)
    {
        if(0 != codebookSubsetRestriction_v920_n4TxAntenna_tm8_r9_Pack(bits))
        {
            printf("AntennaInfoDedicated_v920::codebookSubsetRestriction_v920_n4TxAntenna_tm8_r9 pack failure\n");
            return -1;
        }
    }
    return 0;
}

int AntennaInfoDedicated_v920::codebookSubsetRestriction_v920_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return codebookSubsetRestriction_v920_Unpack(bits, idx);
}

int AntennaInfoDedicated_v920::codebookSubsetRestriction_v920_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 1) > bits.size())
    {
        printf("AntennaInfoDedicated_v920::codebookSubsetRestriction_v920_Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<1; i++)
        packed_val |= bits[idx++] << (1-i-1);

    if((AntennaInfoDedicated_v920::codebookSubsetRestriction_v920_Enum)packed_val > k_codebookSubsetRestriction_v920_n4TxAntenna_tm8_r9)
    {
        printf("AntennaInfoDedicated_v920::codebookSubsetRestriction_v920_Unpack() choice range failure\n");
        return -1;
    }
    codebookSubsetRestriction_v920_internal_choice = (AntennaInfoDedicated_v920::codebookSubsetRestriction_v920_Enum)packed_val;
    codebookSubsetRestriction_v920_present = true;

    // Fields
    if(codebookSubsetRestriction_v920_internal_choice == k_codebookSubsetRestriction_v920_n2TxAntenna_tm8_r9)
    {
        if(0 != codebookSubsetRestriction_v920_n2TxAntenna_tm8_r9_Unpack(bits, idx))
        {
            printf("AntennaInfoDedicated_v920::codebookSubsetRestriction_v920_n2TxAntenna_tm8_r9 unpack failure\n");
            return -1;
        }
    }
    if(codebookSubsetRestriction_v920_internal_choice == k_codebookSubsetRestriction_v920_n4TxAntenna_tm8_r9)
    {
        if(0 != codebookSubsetRestriction_v920_n4TxAntenna_tm8_r9_Unpack(bits, idx))
        {
            printf("AntennaInfoDedicated_v920::codebookSubsetRestriction_v920_n4TxAntenna_tm8_r9 unpack failure\n");
            return -1;
        }
    }
    return 0;
}

AntennaInfoDedicated_v920::codebookSubsetRestriction_v920_Enum AntennaInfoDedicated_v920::codebookSubsetRestriction_v920_Choice() const
{
    if(codebookSubsetRestriction_v920_present)
        return codebookSubsetRestriction_v920_internal_choice;
    return (AntennaInfoDedicated_v920::codebookSubsetRestriction_v920_Enum)0;
}

int AntennaInfoDedicated_v920::codebookSubsetRestriction_v920_SetChoice(AntennaInfoDedicated_v920::codebookSubsetRestriction_v920_Enum choice)
{
    codebookSubsetRestriction_v920_internal_choice = choice;
    codebookSubsetRestriction_v920_present = true;
    return 0;
}

std::string AntennaInfoDedicated_v920::codebookSubsetRestriction_v920_ChoiceToString(codebookSubsetRestriction_v920_Enum value) const
{
    if(k_codebookSubsetRestriction_v920_n2TxAntenna_tm8_r9 == value)
        return "codebookSubsetRestriction_v920_n2TxAntenna_tm8_r9";
    if(k_codebookSubsetRestriction_v920_n4TxAntenna_tm8_r9 == value)
        return "codebookSubsetRestriction_v920_n4TxAntenna_tm8_r9";
    return "";
}

uint64_t AntennaInfoDedicated_v920::codebookSubsetRestriction_v920_NumberOfChoices() const
{
    return 2;
}

std::string AntennaInfoDedicated_v920::codebookSubsetRestriction_v920_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "codebookSubsetRestriction_v920 = " + codebookSubsetRestriction_v920_ChoiceToString(codebookSubsetRestriction_v920_internal_choice) + ":\n";
    if(codebookSubsetRestriction_v920_internal_choice == k_codebookSubsetRestriction_v920_n2TxAntenna_tm8_r9)
        out += codebookSubsetRestriction_v920_n2TxAntenna_tm8_r9_ToString(indent+1);
    if(codebookSubsetRestriction_v920_internal_choice == k_codebookSubsetRestriction_v920_n4TxAntenna_tm8_r9)
        out += codebookSubsetRestriction_v920_n4TxAntenna_tm8_r9_ToString(indent+1);
    return out;
}

std::string AntennaInfoDedicated_v920::codebookSubsetRestriction_v920_ToStringNoNewLines() const
{
    std::string out = "codebookSubsetRestriction_v920=" + codebookSubsetRestriction_v920_ChoiceToString(codebookSubsetRestriction_v920_internal_choice) + ",";
    if(codebookSubsetRestriction_v920_internal_choice == k_codebookSubsetRestriction_v920_n2TxAntenna_tm8_r9)
        out += codebookSubsetRestriction_v920_n2TxAntenna_tm8_r9_ToStringNoNewLines();
    if(codebookSubsetRestriction_v920_internal_choice == k_codebookSubsetRestriction_v920_n4TxAntenna_tm8_r9)
        out += codebookSubsetRestriction_v920_n4TxAntenna_tm8_r9_ToStringNoNewLines();
    return out;
}

int AntennaInfoDedicated_v920::codebookSubsetRestriction_v920_Clear()
{
    codebookSubsetRestriction_v920_present = false;
    return 0;
}

bool AntennaInfoDedicated_v920::codebookSubsetRestriction_v920_IsPresent() const
{
    return codebookSubsetRestriction_v920_present;
}

int AntennaInfoDedicated_v920::codebookSubsetRestriction_v920_n2TxAntenna_tm8_r9_Pack(std::vector<uint8_t> &bits)
{
    if(!codebookSubsetRestriction_v920_n2TxAntenna_tm8_r9_present)
    {
        printf("AntennaInfoDedicated_v920::codebookSubsetRestriction_v920_n2TxAntenna_tm8_r9_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 6;
    if(size < 6 || size > 6)
    {
        printf("AntennaInfoDedicated_v920::codebookSubsetRestriction_v920_n2TxAntenna_tm8_r9_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((codebookSubsetRestriction_v920_n2TxAntenna_tm8_r9_internal_value >> (6-i-1)) & 1);
    return 0;
}

int AntennaInfoDedicated_v920::codebookSubsetRestriction_v920_n2TxAntenna_tm8_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return codebookSubsetRestriction_v920_n2TxAntenna_tm8_r9_Unpack(bits, idx);
}

int AntennaInfoDedicated_v920::codebookSubsetRestriction_v920_n2TxAntenna_tm8_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 6;
    if(size < 6 || size > 6)
    {
        printf("AntennaInfoDedicated_v920::codebookSubsetRestriction_v920_n2TxAntenna_tm8_r9_Unpack() size failure\n");
        return -1;
    }
    codebookSubsetRestriction_v920_n2TxAntenna_tm8_r9_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("AntennaInfoDedicated_v920::codebookSubsetRestriction_v920_n2TxAntenna_tm8_r9_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        codebookSubsetRestriction_v920_n2TxAntenna_tm8_r9_internal_value |= (uint8_t)bits[idx++] << (uint8_t)(6-i-1);
    codebookSubsetRestriction_v920_n2TxAntenna_tm8_r9_present = true;
    return 0;
}

uint8_t AntennaInfoDedicated_v920::codebookSubsetRestriction_v920_n2TxAntenna_tm8_r9_Value() const
{
    if(codebookSubsetRestriction_v920_n2TxAntenna_tm8_r9_present)
        return codebookSubsetRestriction_v920_n2TxAntenna_tm8_r9_internal_value;
    uint8_t tmp = 0;
    return tmp;
}

int AntennaInfoDedicated_v920::codebookSubsetRestriction_v920_n2TxAntenna_tm8_r9_SetValue(uint8_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 6)
    {
        printf("AntennaInfoDedicated_v920::codebookSubsetRestriction_v920_n2TxAntenna_tm8_r9_SetValue() size failure\n");
        return -1;
    }
    codebookSubsetRestriction_v920_n2TxAntenna_tm8_r9_internal_value = value;
    codebookSubsetRestriction_v920_n2TxAntenna_tm8_r9_present = true;
    return 0;
}

std::string AntennaInfoDedicated_v920::codebookSubsetRestriction_v920_n2TxAntenna_tm8_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "n2TxAntenna_tm8_r9 = ";
    out += std::to_string(codebookSubsetRestriction_v920_n2TxAntenna_tm8_r9_internal_value);
    out += "\n";
    return out;
}

std::string AntennaInfoDedicated_v920::codebookSubsetRestriction_v920_n2TxAntenna_tm8_r9_ToStringNoNewLines() const
{
    std::string out = "n2TxAntenna_tm8_r9=";
    out += std::to_string(codebookSubsetRestriction_v920_n2TxAntenna_tm8_r9_internal_value);
    out += ",";
    return out;
}

int AntennaInfoDedicated_v920::codebookSubsetRestriction_v920_n2TxAntenna_tm8_r9_Clear()
{
    codebookSubsetRestriction_v920_n2TxAntenna_tm8_r9_present = false;
    return 0;
}

bool AntennaInfoDedicated_v920::codebookSubsetRestriction_v920_n2TxAntenna_tm8_r9_IsPresent() const
{
    return codebookSubsetRestriction_v920_n2TxAntenna_tm8_r9_present;
}

int AntennaInfoDedicated_v920::codebookSubsetRestriction_v920_n4TxAntenna_tm8_r9_Pack(std::vector<uint8_t> &bits)
{
    if(!codebookSubsetRestriction_v920_n4TxAntenna_tm8_r9_present)
    {
        printf("AntennaInfoDedicated_v920::codebookSubsetRestriction_v920_n4TxAntenna_tm8_r9_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 32;
    if(size < 32 || size > 32)
    {
        printf("AntennaInfoDedicated_v920::codebookSubsetRestriction_v920_n4TxAntenna_tm8_r9_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((codebookSubsetRestriction_v920_n4TxAntenna_tm8_r9_internal_value >> (32-i-1)) & 1);
    return 0;
}

int AntennaInfoDedicated_v920::codebookSubsetRestriction_v920_n4TxAntenna_tm8_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return codebookSubsetRestriction_v920_n4TxAntenna_tm8_r9_Unpack(bits, idx);
}

int AntennaInfoDedicated_v920::codebookSubsetRestriction_v920_n4TxAntenna_tm8_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 32;
    if(size < 32 || size > 32)
    {
        printf("AntennaInfoDedicated_v920::codebookSubsetRestriction_v920_n4TxAntenna_tm8_r9_Unpack() size failure\n");
        return -1;
    }
    codebookSubsetRestriction_v920_n4TxAntenna_tm8_r9_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("AntennaInfoDedicated_v920::codebookSubsetRestriction_v920_n4TxAntenna_tm8_r9_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        codebookSubsetRestriction_v920_n4TxAntenna_tm8_r9_internal_value |= (uint32_t)bits[idx++] << (uint32_t)(32-i-1);
    codebookSubsetRestriction_v920_n4TxAntenna_tm8_r9_present = true;
    return 0;
}

uint32_t AntennaInfoDedicated_v920::codebookSubsetRestriction_v920_n4TxAntenna_tm8_r9_Value() const
{
    if(codebookSubsetRestriction_v920_n4TxAntenna_tm8_r9_present)
        return codebookSubsetRestriction_v920_n4TxAntenna_tm8_r9_internal_value;
    uint32_t tmp = 0;
    return tmp;
}

int AntennaInfoDedicated_v920::codebookSubsetRestriction_v920_n4TxAntenna_tm8_r9_SetValue(uint32_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 32)
    {
        printf("AntennaInfoDedicated_v920::codebookSubsetRestriction_v920_n4TxAntenna_tm8_r9_SetValue() size failure\n");
        return -1;
    }
    codebookSubsetRestriction_v920_n4TxAntenna_tm8_r9_internal_value = value;
    codebookSubsetRestriction_v920_n4TxAntenna_tm8_r9_present = true;
    return 0;
}

std::string AntennaInfoDedicated_v920::codebookSubsetRestriction_v920_n4TxAntenna_tm8_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "n4TxAntenna_tm8_r9 = ";
    out += std::to_string(codebookSubsetRestriction_v920_n4TxAntenna_tm8_r9_internal_value);
    out += "\n";
    return out;
}

std::string AntennaInfoDedicated_v920::codebookSubsetRestriction_v920_n4TxAntenna_tm8_r9_ToStringNoNewLines() const
{
    std::string out = "n4TxAntenna_tm8_r9=";
    out += std::to_string(codebookSubsetRestriction_v920_n4TxAntenna_tm8_r9_internal_value);
    out += ",";
    return out;
}

int AntennaInfoDedicated_v920::codebookSubsetRestriction_v920_n4TxAntenna_tm8_r9_Clear()
{
    codebookSubsetRestriction_v920_n4TxAntenna_tm8_r9_present = false;
    return 0;
}

bool AntennaInfoDedicated_v920::codebookSubsetRestriction_v920_n4TxAntenna_tm8_r9_IsPresent() const
{
    return codebookSubsetRestriction_v920_n4TxAntenna_tm8_r9_present;
}

