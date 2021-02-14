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

#include "TPC_Index.h"

#include <cmath>

int TPC_Index::Pack(std::vector<uint8_t> &bits)
{
    if(!present)
    {
        printf("TPC_Index::Pack() presence failure\n");
        return -1;
    }
    // Extension indicator

    // Choice
    for(uint32_t i=0; i<1; i++)
        bits.push_back((internal_choice >> (1-i-1)) & 1);

    // Fields
    if(internal_choice == k_indexOfFormat3)
    {
        if(0 != indexOfFormat3_Pack(bits))
        {
            printf("TPC_Index::indexOfFormat3 pack failure\n");
            return -1;
        }
    }
    if(internal_choice == k_indexOfFormat3A)
    {
        if(0 != indexOfFormat3A_Pack(bits))
        {
            printf("TPC_Index::indexOfFormat3A pack failure\n");
            return -1;
        }
    }
    return 0;
}

int TPC_Index::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int TPC_Index::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 1) > bits.size())
    {
        printf("TPC_Index::Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<1; i++)
        packed_val |= bits[idx++] << (1-i-1);

    if((TPC_Index::Enum)packed_val > k_indexOfFormat3A)
    {
        printf("TPC_Index::Unpack() choice range failure\n");
        return -1;
    }
    internal_choice = (TPC_Index::Enum)packed_val;
    present = true;

    // Fields
    if(internal_choice == k_indexOfFormat3)
    {
        if(0 != indexOfFormat3_Unpack(bits, idx))
        {
            printf("TPC_Index::indexOfFormat3 unpack failure\n");
            return -1;
        }
    }
    if(internal_choice == k_indexOfFormat3A)
    {
        if(0 != indexOfFormat3A_Unpack(bits, idx))
        {
            printf("TPC_Index::indexOfFormat3A unpack failure\n");
            return -1;
        }
    }
    return 0;
}

TPC_Index::Enum TPC_Index::Choice() const
{
    if(present)
        return internal_choice;
    return (TPC_Index::Enum)0;
}

int TPC_Index::SetChoice(TPC_Index::Enum choice)
{
    internal_choice = choice;
    present = true;
    return 0;
}

std::string TPC_Index::ChoiceToString(Enum value) const
{
    if(k_indexOfFormat3 == value)
        return "indexOfFormat3";
    if(k_indexOfFormat3A == value)
        return "indexOfFormat3A";
    return "";
}

uint64_t TPC_Index::NumberOfChoices() const
{
    return 2;
}

std::string TPC_Index::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "TPC_Index = " + ChoiceToString(internal_choice) + ":\n";
    if(internal_choice == k_indexOfFormat3)
        out += indexOfFormat3_ToString(indent+1);
    if(internal_choice == k_indexOfFormat3A)
        out += indexOfFormat3A_ToString(indent+1);
    return out;
}

std::string TPC_Index::ToStringNoNewLines() const
{
    std::string out = "TPC_Index=" + ChoiceToString(internal_choice) + ",";
    if(internal_choice == k_indexOfFormat3)
        out += indexOfFormat3_ToStringNoNewLines();
    if(internal_choice == k_indexOfFormat3A)
        out += indexOfFormat3A_ToStringNoNewLines();
    return out;
}

int TPC_Index::Clear()
{
    present = false;
    return 0;
}

bool TPC_Index::IsPresent() const
{
    return present;
}

int TPC_Index::indexOfFormat3_Pack(std::vector<uint8_t> &bits)
{
    if(!indexOfFormat3_present)
    {
        printf("TPC_Index::indexOfFormat3_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = indexOfFormat3_internal_value - (1);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (15 - 1))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int TPC_Index::indexOfFormat3_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return indexOfFormat3_Unpack(bits, idx);
}

int TPC_Index::indexOfFormat3_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (15 - 1))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("TPC_Index::indexOfFormat3_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    indexOfFormat3_internal_value = packed_val + 1;
    indexOfFormat3_present = true;
    return 0;
}

int64_t TPC_Index::indexOfFormat3_Value() const
{
    if(indexOfFormat3_present)
        return indexOfFormat3_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int TPC_Index::indexOfFormat3_SetValue(int64_t value)
{
    if(value < 1 || value > 15)
    {
        printf("TPC_Index::indexOfFormat3_SetValue() range failure\n");
        return -1;
    }
    indexOfFormat3_internal_value = value;
    indexOfFormat3_present = true;
    return 0;
}

std::string TPC_Index::indexOfFormat3_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "indexOfFormat3 = " + std::to_string(indexOfFormat3_internal_value) + "\n";
    return out;
}

std::string TPC_Index::indexOfFormat3_ToStringNoNewLines() const
{
    std::string out = "indexOfFormat3=" + std::to_string(indexOfFormat3_internal_value) + ",";
    return out;
}

int TPC_Index::indexOfFormat3_Clear()
{
    indexOfFormat3_present = false;
    return 0;
}

bool TPC_Index::indexOfFormat3_IsPresent() const
{
    return indexOfFormat3_present;
}

int TPC_Index::indexOfFormat3A_Pack(std::vector<uint8_t> &bits)
{
    if(!indexOfFormat3A_present)
    {
        printf("TPC_Index::indexOfFormat3A_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = indexOfFormat3A_internal_value - (1);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (31 - 1))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int TPC_Index::indexOfFormat3A_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return indexOfFormat3A_Unpack(bits, idx);
}

int TPC_Index::indexOfFormat3A_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (31 - 1))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("TPC_Index::indexOfFormat3A_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    indexOfFormat3A_internal_value = packed_val + 1;
    indexOfFormat3A_present = true;
    return 0;
}

int64_t TPC_Index::indexOfFormat3A_Value() const
{
    if(indexOfFormat3A_present)
        return indexOfFormat3A_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int TPC_Index::indexOfFormat3A_SetValue(int64_t value)
{
    if(value < 1 || value > 31)
    {
        printf("TPC_Index::indexOfFormat3A_SetValue() range failure\n");
        return -1;
    }
    indexOfFormat3A_internal_value = value;
    indexOfFormat3A_present = true;
    return 0;
}

std::string TPC_Index::indexOfFormat3A_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "indexOfFormat3A = " + std::to_string(indexOfFormat3A_internal_value) + "\n";
    return out;
}

std::string TPC_Index::indexOfFormat3A_ToStringNoNewLines() const
{
    std::string out = "indexOfFormat3A=" + std::to_string(indexOfFormat3A_internal_value) + ",";
    return out;
}

int TPC_Index::indexOfFormat3A_Clear()
{
    indexOfFormat3A_present = false;
    return 0;
}

bool TPC_Index::indexOfFormat3A_IsPresent() const
{
    return indexOfFormat3A_present;
}

