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

#include "InitialUE_Identity.h"

#include <cmath>

int InitialUE_Identity::Pack(std::vector<uint8_t> &bits)
{
    if(!present)
    {
        printf("InitialUE_Identity::Pack() presence failure\n");
        return -1;
    }
    // Extension indicator

    // Choice
    for(uint32_t i=0; i<1; i++)
        bits.push_back((internal_choice >> (1-i-1)) & 1);

    // Fields
    if(internal_choice == k_s_TMSI)
    {
        if(0 != s_TMSI.Pack(bits))
        {
            printf("InitialUE_Identity::s_TMSI pack failure\n");
            return -1;
        }
    }
    if(internal_choice == k_randomValue)
    {
        if(0 != randomValue_Pack(bits))
        {
            printf("InitialUE_Identity::randomValue pack failure\n");
            return -1;
        }
    }
    return 0;
}

int InitialUE_Identity::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int InitialUE_Identity::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 1) > bits.size())
    {
        printf("InitialUE_Identity::Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<1; i++)
        packed_val |= bits[idx++] << (1-i-1);

    if((InitialUE_Identity::Enum)packed_val > k_randomValue)
    {
        printf("InitialUE_Identity::Unpack() choice range failure\n");
        return -1;
    }
    internal_choice = (InitialUE_Identity::Enum)packed_val;
    present = true;

    // Fields
    if(internal_choice == k_s_TMSI)
    {
        if(0 != s_TMSI.Unpack(bits, idx))
        {
            printf("InitialUE_Identity::s_TMSI unpack failure\n");
            return -1;
        }
    }
    if(internal_choice == k_randomValue)
    {
        if(0 != randomValue_Unpack(bits, idx))
        {
            printf("InitialUE_Identity::randomValue unpack failure\n");
            return -1;
        }
    }
    return 0;
}

InitialUE_Identity::Enum InitialUE_Identity::Choice() const
{
    if(present)
        return internal_choice;
    return (InitialUE_Identity::Enum)0;
}

int InitialUE_Identity::SetChoice(InitialUE_Identity::Enum choice)
{
    internal_choice = choice;
    present = true;
    return 0;
}

std::string InitialUE_Identity::ChoiceToString(Enum value) const
{
    if(k_s_TMSI == value)
        return "s_TMSI";
    if(k_randomValue == value)
        return "randomValue";
    return "";
}

uint64_t InitialUE_Identity::NumberOfChoices() const
{
    return 2;
}

std::string InitialUE_Identity::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "InitialUE_Identity = " + ChoiceToString(internal_choice) + ":\n";
    if(internal_choice == k_s_TMSI)
        out += s_TMSI.ToString(indent+1);
    if(internal_choice == k_randomValue)
        out += randomValue_ToString(indent+1);
    return out;
}

std::string InitialUE_Identity::ToStringNoNewLines() const
{
    std::string out = "InitialUE_Identity=" + ChoiceToString(internal_choice) + ",";
    if(internal_choice == k_s_TMSI)
        out += s_TMSI.ToStringNoNewLines();
    if(internal_choice == k_randomValue)
        out += randomValue_ToStringNoNewLines();
    return out;
}

int InitialUE_Identity::Clear()
{
    present = false;
    return 0;
}

bool InitialUE_Identity::IsPresent() const
{
    return present;
}

S_TMSI* InitialUE_Identity::s_TMSI_Set()
{
    s_TMSI_present = true;
    return &s_TMSI;
}

int InitialUE_Identity::s_TMSI_Set(S_TMSI &value)
{
    s_TMSI_present = true;
    s_TMSI = value;
    return 0;
}

const S_TMSI& InitialUE_Identity::s_TMSI_Get() const
{
    return s_TMSI;
}

std::string InitialUE_Identity::s_TMSI_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "s_TMSI:\n";
    out += s_TMSI.ToString(indent+1);
    return out;
}

std::string InitialUE_Identity::s_TMSI_ToStringNoNewLines() const
{
    std::string out = "s_TMSI:";
    out += s_TMSI.ToStringNoNewLines();
    return out;
}

int InitialUE_Identity::s_TMSI_Clear()
{
    s_TMSI_present = false;
    return 0;
}

bool InitialUE_Identity::s_TMSI_IsPresent() const
{
    return s_TMSI_present;
}

int InitialUE_Identity::randomValue_Pack(std::vector<uint8_t> &bits)
{
    if(!randomValue_present)
    {
        printf("InitialUE_Identity::randomValue_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 40;
    if(size < 40 || size > 40)
    {
        printf("InitialUE_Identity::randomValue_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((randomValue_internal_value >> (40-i-1)) & 1);
    return 0;
}

int InitialUE_Identity::randomValue_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return randomValue_Unpack(bits, idx);
}

int InitialUE_Identity::randomValue_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 40;
    if(size < 40 || size > 40)
    {
        printf("InitialUE_Identity::randomValue_Unpack() size failure\n");
        return -1;
    }
    randomValue_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("InitialUE_Identity::randomValue_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        randomValue_internal_value |= (uint64_t)bits[idx++] << (uint64_t)(40-i-1);
    randomValue_present = true;
    return 0;
}

uint64_t InitialUE_Identity::randomValue_Value() const
{
    if(randomValue_present)
        return randomValue_internal_value;
    uint64_t tmp = 0;
    return tmp;
}

int InitialUE_Identity::randomValue_SetValue(uint64_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 40)
    {
        printf("InitialUE_Identity::randomValue_SetValue() size failure\n");
        return -1;
    }
    randomValue_internal_value = value;
    randomValue_present = true;
    return 0;
}

std::string InitialUE_Identity::randomValue_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "randomValue = ";
    out += std::to_string(randomValue_internal_value);
    out += "\n";
    return out;
}

std::string InitialUE_Identity::randomValue_ToStringNoNewLines() const
{
    std::string out = "randomValue=";
    out += std::to_string(randomValue_internal_value);
    out += ",";
    return out;
}

int InitialUE_Identity::randomValue_Clear()
{
    randomValue_present = false;
    return 0;
}

bool InitialUE_Identity::randomValue_IsPresent() const
{
    return randomValue_present;
}

