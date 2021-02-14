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

#include "TDD_Config.h"

#include <cmath>

int TDD_Config::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != subframeAssignment_Pack(bits))
        {
            printf("TDD_Config:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != specialSubframePatterns_Pack(bits))
        {
            printf("TDD_Config:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int TDD_Config::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int TDD_Config::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != subframeAssignment_Unpack(bits, idx))
        {
            printf("TDD_Config:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != specialSubframePatterns_Unpack(bits, idx))
        {
            printf("TDD_Config:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string TDD_Config::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "TDD_Config:\n";
    out += subframeAssignment_ToString(indent+1);
    out += specialSubframePatterns_ToString(indent+1);
    return out;
}

std::string TDD_Config::ToStringNoNewLines() const
{
    std::string out = "TDD_Config:";
    out += subframeAssignment_ToStringNoNewLines();
    out += specialSubframePatterns_ToStringNoNewLines();
    return out;
}

int TDD_Config::subframeAssignment_Pack(std::vector<uint8_t> &bits)
{
    if(!subframeAssignment_present)
    {
        printf("TDD_Config::subframeAssignment_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 3;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((subframeAssignment_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int TDD_Config::subframeAssignment_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return subframeAssignment_Unpack(bits, idx);
}

int TDD_Config::subframeAssignment_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 3;
    if((idx + N_bits) > bits.size())
    {
        printf("TDD_Config::subframeAssignment_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 6)
    {
        printf("TDD_Config::subframeAssignment_Unpack() max failure\n");
        return -1;
    }
    subframeAssignment_internal_value = (subframeAssignment_Enum)packed_val;
    subframeAssignment_present = true;
    return 0;
}

TDD_Config::subframeAssignment_Enum TDD_Config::subframeAssignment_Value() const
{
    if(subframeAssignment_present)
        return subframeAssignment_internal_value;
    return (TDD_Config::subframeAssignment_Enum)0;
}

int TDD_Config::subframeAssignment_SetValue(subframeAssignment_Enum value)
{
    subframeAssignment_internal_value = value;
    subframeAssignment_present = true;
    return 0;
}

int TDD_Config::subframeAssignment_SetValue(std::string value)
{
    if("sa0" == value)
    {
        subframeAssignment_internal_value = k_subframeAssignment_sa0;
        subframeAssignment_present = true;
        return 0;
    }
    if("sa1" == value)
    {
        subframeAssignment_internal_value = k_subframeAssignment_sa1;
        subframeAssignment_present = true;
        return 0;
    }
    if("sa2" == value)
    {
        subframeAssignment_internal_value = k_subframeAssignment_sa2;
        subframeAssignment_present = true;
        return 0;
    }
    if("sa3" == value)
    {
        subframeAssignment_internal_value = k_subframeAssignment_sa3;
        subframeAssignment_present = true;
        return 0;
    }
    if("sa4" == value)
    {
        subframeAssignment_internal_value = k_subframeAssignment_sa4;
        subframeAssignment_present = true;
        return 0;
    }
    if("sa5" == value)
    {
        subframeAssignment_internal_value = k_subframeAssignment_sa5;
        subframeAssignment_present = true;
        return 0;
    }
    if("sa6" == value)
    {
        subframeAssignment_internal_value = k_subframeAssignment_sa6;
        subframeAssignment_present = true;
        return 0;
    }
    return 1;
}

std::string TDD_Config::subframeAssignment_ValueToString(subframeAssignment_Enum value) const
{
    if(k_subframeAssignment_sa0 == value)
        return "sa0";
    if(k_subframeAssignment_sa1 == value)
        return "sa1";
    if(k_subframeAssignment_sa2 == value)
        return "sa2";
    if(k_subframeAssignment_sa3 == value)
        return "sa3";
    if(k_subframeAssignment_sa4 == value)
        return "sa4";
    if(k_subframeAssignment_sa5 == value)
        return "sa5";
    if(k_subframeAssignment_sa6 == value)
        return "sa6";
    return "";
}

uint64_t TDD_Config::subframeAssignment_NumberOfValues() const
{
    return 7;
}

std::string TDD_Config::subframeAssignment_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "subframeAssignment = " + subframeAssignment_ValueToString(subframeAssignment_internal_value) + "\n";
    return out;
}

std::string TDD_Config::subframeAssignment_ToStringNoNewLines() const
{
    std::string out = "subframeAssignment=" + subframeAssignment_ValueToString(subframeAssignment_internal_value) + ",";
    return out;
}

int TDD_Config::subframeAssignment_Clear()
{
    subframeAssignment_present = false;
    return 0;
}

bool TDD_Config::subframeAssignment_IsPresent() const
{
    return subframeAssignment_present;
}

int TDD_Config::specialSubframePatterns_Pack(std::vector<uint8_t> &bits)
{
    if(!specialSubframePatterns_present)
    {
        printf("TDD_Config::specialSubframePatterns_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 4;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((specialSubframePatterns_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int TDD_Config::specialSubframePatterns_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return specialSubframePatterns_Unpack(bits, idx);
}

int TDD_Config::specialSubframePatterns_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 4;
    if((idx + N_bits) > bits.size())
    {
        printf("TDD_Config::specialSubframePatterns_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 8)
    {
        printf("TDD_Config::specialSubframePatterns_Unpack() max failure\n");
        return -1;
    }
    specialSubframePatterns_internal_value = (specialSubframePatterns_Enum)packed_val;
    specialSubframePatterns_present = true;
    return 0;
}

TDD_Config::specialSubframePatterns_Enum TDD_Config::specialSubframePatterns_Value() const
{
    if(specialSubframePatterns_present)
        return specialSubframePatterns_internal_value;
    return (TDD_Config::specialSubframePatterns_Enum)0;
}

int TDD_Config::specialSubframePatterns_SetValue(specialSubframePatterns_Enum value)
{
    specialSubframePatterns_internal_value = value;
    specialSubframePatterns_present = true;
    return 0;
}

int TDD_Config::specialSubframePatterns_SetValue(std::string value)
{
    if("ssp0" == value)
    {
        specialSubframePatterns_internal_value = k_specialSubframePatterns_ssp0;
        specialSubframePatterns_present = true;
        return 0;
    }
    if("ssp1" == value)
    {
        specialSubframePatterns_internal_value = k_specialSubframePatterns_ssp1;
        specialSubframePatterns_present = true;
        return 0;
    }
    if("ssp2" == value)
    {
        specialSubframePatterns_internal_value = k_specialSubframePatterns_ssp2;
        specialSubframePatterns_present = true;
        return 0;
    }
    if("ssp3" == value)
    {
        specialSubframePatterns_internal_value = k_specialSubframePatterns_ssp3;
        specialSubframePatterns_present = true;
        return 0;
    }
    if("ssp4" == value)
    {
        specialSubframePatterns_internal_value = k_specialSubframePatterns_ssp4;
        specialSubframePatterns_present = true;
        return 0;
    }
    if("ssp5" == value)
    {
        specialSubframePatterns_internal_value = k_specialSubframePatterns_ssp5;
        specialSubframePatterns_present = true;
        return 0;
    }
    if("ssp6" == value)
    {
        specialSubframePatterns_internal_value = k_specialSubframePatterns_ssp6;
        specialSubframePatterns_present = true;
        return 0;
    }
    if("ssp7" == value)
    {
        specialSubframePatterns_internal_value = k_specialSubframePatterns_ssp7;
        specialSubframePatterns_present = true;
        return 0;
    }
    if("ssp8" == value)
    {
        specialSubframePatterns_internal_value = k_specialSubframePatterns_ssp8;
        specialSubframePatterns_present = true;
        return 0;
    }
    return 1;
}

std::string TDD_Config::specialSubframePatterns_ValueToString(specialSubframePatterns_Enum value) const
{
    if(k_specialSubframePatterns_ssp0 == value)
        return "ssp0";
    if(k_specialSubframePatterns_ssp1 == value)
        return "ssp1";
    if(k_specialSubframePatterns_ssp2 == value)
        return "ssp2";
    if(k_specialSubframePatterns_ssp3 == value)
        return "ssp3";
    if(k_specialSubframePatterns_ssp4 == value)
        return "ssp4";
    if(k_specialSubframePatterns_ssp5 == value)
        return "ssp5";
    if(k_specialSubframePatterns_ssp6 == value)
        return "ssp6";
    if(k_specialSubframePatterns_ssp7 == value)
        return "ssp7";
    if(k_specialSubframePatterns_ssp8 == value)
        return "ssp8";
    return "";
}

uint64_t TDD_Config::specialSubframePatterns_NumberOfValues() const
{
    return 9;
}

std::string TDD_Config::specialSubframePatterns_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "specialSubframePatterns = " + specialSubframePatterns_ValueToString(specialSubframePatterns_internal_value) + "\n";
    return out;
}

std::string TDD_Config::specialSubframePatterns_ToStringNoNewLines() const
{
    std::string out = "specialSubframePatterns=" + specialSubframePatterns_ValueToString(specialSubframePatterns_internal_value) + ",";
    return out;
}

int TDD_Config::specialSubframePatterns_Clear()
{
    specialSubframePatterns_present = false;
    return 0;
}

bool TDD_Config::specialSubframePatterns_IsPresent() const
{
    return specialSubframePatterns_present;
}

