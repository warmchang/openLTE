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

#include "DeltaFList_PUCCH.h"

#include <cmath>

int DeltaFList_PUCCH::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != deltaF_PUCCH_Format1_Pack(bits))
        {
            printf("DeltaFList_PUCCH:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != deltaF_PUCCH_Format1b_Pack(bits))
        {
            printf("DeltaFList_PUCCH:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != deltaF_PUCCH_Format2_Pack(bits))
        {
            printf("DeltaFList_PUCCH:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != deltaF_PUCCH_Format2a_Pack(bits))
        {
            printf("DeltaFList_PUCCH:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != deltaF_PUCCH_Format2b_Pack(bits))
        {
            printf("DeltaFList_PUCCH:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int DeltaFList_PUCCH::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int DeltaFList_PUCCH::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != deltaF_PUCCH_Format1_Unpack(bits, idx))
        {
            printf("DeltaFList_PUCCH:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != deltaF_PUCCH_Format1b_Unpack(bits, idx))
        {
            printf("DeltaFList_PUCCH:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != deltaF_PUCCH_Format2_Unpack(bits, idx))
        {
            printf("DeltaFList_PUCCH:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != deltaF_PUCCH_Format2a_Unpack(bits, idx))
        {
            printf("DeltaFList_PUCCH:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != deltaF_PUCCH_Format2b_Unpack(bits, idx))
        {
            printf("DeltaFList_PUCCH:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string DeltaFList_PUCCH::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "DeltaFList_PUCCH:\n";
    out += deltaF_PUCCH_Format1_ToString(indent+1);
    out += deltaF_PUCCH_Format1b_ToString(indent+1);
    out += deltaF_PUCCH_Format2_ToString(indent+1);
    out += deltaF_PUCCH_Format2a_ToString(indent+1);
    out += deltaF_PUCCH_Format2b_ToString(indent+1);
    return out;
}

std::string DeltaFList_PUCCH::ToStringNoNewLines() const
{
    std::string out = "DeltaFList_PUCCH:";
    out += deltaF_PUCCH_Format1_ToStringNoNewLines();
    out += deltaF_PUCCH_Format1b_ToStringNoNewLines();
    out += deltaF_PUCCH_Format2_ToStringNoNewLines();
    out += deltaF_PUCCH_Format2a_ToStringNoNewLines();
    out += deltaF_PUCCH_Format2b_ToStringNoNewLines();
    return out;
}

int DeltaFList_PUCCH::deltaF_PUCCH_Format1_Pack(std::vector<uint8_t> &bits)
{
    if(!deltaF_PUCCH_Format1_present)
    {
        printf("DeltaFList_PUCCH::deltaF_PUCCH_Format1_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 2;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((deltaF_PUCCH_Format1_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int DeltaFList_PUCCH::deltaF_PUCCH_Format1_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return deltaF_PUCCH_Format1_Unpack(bits, idx);
}

int DeltaFList_PUCCH::deltaF_PUCCH_Format1_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 2;
    if((idx + N_bits) > bits.size())
    {
        printf("DeltaFList_PUCCH::deltaF_PUCCH_Format1_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 2)
    {
        printf("DeltaFList_PUCCH::deltaF_PUCCH_Format1_Unpack() max failure\n");
        return -1;
    }
    deltaF_PUCCH_Format1_internal_value = (deltaF_PUCCH_Format1_Enum)packed_val;
    deltaF_PUCCH_Format1_present = true;
    return 0;
}

DeltaFList_PUCCH::deltaF_PUCCH_Format1_Enum DeltaFList_PUCCH::deltaF_PUCCH_Format1_Value() const
{
    if(deltaF_PUCCH_Format1_present)
        return deltaF_PUCCH_Format1_internal_value;
    return (DeltaFList_PUCCH::deltaF_PUCCH_Format1_Enum)0;
}

int DeltaFList_PUCCH::deltaF_PUCCH_Format1_SetValue(deltaF_PUCCH_Format1_Enum value)
{
    deltaF_PUCCH_Format1_internal_value = value;
    deltaF_PUCCH_Format1_present = true;
    return 0;
}

int DeltaFList_PUCCH::deltaF_PUCCH_Format1_SetValue(std::string value)
{
    if("deltaF_2" == value)
    {
        deltaF_PUCCH_Format1_internal_value = k_deltaF_PUCCH_Format1_deltaF_2;
        deltaF_PUCCH_Format1_present = true;
        return 0;
    }
    if("deltaF0" == value)
    {
        deltaF_PUCCH_Format1_internal_value = k_deltaF_PUCCH_Format1_deltaF0;
        deltaF_PUCCH_Format1_present = true;
        return 0;
    }
    if("deltaF2" == value)
    {
        deltaF_PUCCH_Format1_internal_value = k_deltaF_PUCCH_Format1_deltaF2;
        deltaF_PUCCH_Format1_present = true;
        return 0;
    }
    return 1;
}

std::string DeltaFList_PUCCH::deltaF_PUCCH_Format1_ValueToString(deltaF_PUCCH_Format1_Enum value) const
{
    if(k_deltaF_PUCCH_Format1_deltaF_2 == value)
        return "deltaF_2";
    if(k_deltaF_PUCCH_Format1_deltaF0 == value)
        return "deltaF0";
    if(k_deltaF_PUCCH_Format1_deltaF2 == value)
        return "deltaF2";
    return "";
}

uint64_t DeltaFList_PUCCH::deltaF_PUCCH_Format1_NumberOfValues() const
{
    return 3;
}

std::string DeltaFList_PUCCH::deltaF_PUCCH_Format1_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "deltaF_PUCCH_Format1 = " + deltaF_PUCCH_Format1_ValueToString(deltaF_PUCCH_Format1_internal_value) + "\n";
    return out;
}

std::string DeltaFList_PUCCH::deltaF_PUCCH_Format1_ToStringNoNewLines() const
{
    std::string out = "deltaF_PUCCH_Format1=" + deltaF_PUCCH_Format1_ValueToString(deltaF_PUCCH_Format1_internal_value) + ",";
    return out;
}

int DeltaFList_PUCCH::deltaF_PUCCH_Format1_Clear()
{
    deltaF_PUCCH_Format1_present = false;
    return 0;
}

bool DeltaFList_PUCCH::deltaF_PUCCH_Format1_IsPresent() const
{
    return deltaF_PUCCH_Format1_present;
}

int DeltaFList_PUCCH::deltaF_PUCCH_Format1b_Pack(std::vector<uint8_t> &bits)
{
    if(!deltaF_PUCCH_Format1b_present)
    {
        printf("DeltaFList_PUCCH::deltaF_PUCCH_Format1b_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 2;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((deltaF_PUCCH_Format1b_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int DeltaFList_PUCCH::deltaF_PUCCH_Format1b_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return deltaF_PUCCH_Format1b_Unpack(bits, idx);
}

int DeltaFList_PUCCH::deltaF_PUCCH_Format1b_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 2;
    if((idx + N_bits) > bits.size())
    {
        printf("DeltaFList_PUCCH::deltaF_PUCCH_Format1b_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 2)
    {
        printf("DeltaFList_PUCCH::deltaF_PUCCH_Format1b_Unpack() max failure\n");
        return -1;
    }
    deltaF_PUCCH_Format1b_internal_value = (deltaF_PUCCH_Format1b_Enum)packed_val;
    deltaF_PUCCH_Format1b_present = true;
    return 0;
}

DeltaFList_PUCCH::deltaF_PUCCH_Format1b_Enum DeltaFList_PUCCH::deltaF_PUCCH_Format1b_Value() const
{
    if(deltaF_PUCCH_Format1b_present)
        return deltaF_PUCCH_Format1b_internal_value;
    return (DeltaFList_PUCCH::deltaF_PUCCH_Format1b_Enum)0;
}

int DeltaFList_PUCCH::deltaF_PUCCH_Format1b_SetValue(deltaF_PUCCH_Format1b_Enum value)
{
    deltaF_PUCCH_Format1b_internal_value = value;
    deltaF_PUCCH_Format1b_present = true;
    return 0;
}

int DeltaFList_PUCCH::deltaF_PUCCH_Format1b_SetValue(std::string value)
{
    if("deltaF1" == value)
    {
        deltaF_PUCCH_Format1b_internal_value = k_deltaF_PUCCH_Format1b_deltaF1;
        deltaF_PUCCH_Format1b_present = true;
        return 0;
    }
    if("deltaF3" == value)
    {
        deltaF_PUCCH_Format1b_internal_value = k_deltaF_PUCCH_Format1b_deltaF3;
        deltaF_PUCCH_Format1b_present = true;
        return 0;
    }
    if("deltaF5" == value)
    {
        deltaF_PUCCH_Format1b_internal_value = k_deltaF_PUCCH_Format1b_deltaF5;
        deltaF_PUCCH_Format1b_present = true;
        return 0;
    }
    return 1;
}

std::string DeltaFList_PUCCH::deltaF_PUCCH_Format1b_ValueToString(deltaF_PUCCH_Format1b_Enum value) const
{
    if(k_deltaF_PUCCH_Format1b_deltaF1 == value)
        return "deltaF1";
    if(k_deltaF_PUCCH_Format1b_deltaF3 == value)
        return "deltaF3";
    if(k_deltaF_PUCCH_Format1b_deltaF5 == value)
        return "deltaF5";
    return "";
}

uint64_t DeltaFList_PUCCH::deltaF_PUCCH_Format1b_NumberOfValues() const
{
    return 3;
}

std::string DeltaFList_PUCCH::deltaF_PUCCH_Format1b_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "deltaF_PUCCH_Format1b = " + deltaF_PUCCH_Format1b_ValueToString(deltaF_PUCCH_Format1b_internal_value) + "\n";
    return out;
}

std::string DeltaFList_PUCCH::deltaF_PUCCH_Format1b_ToStringNoNewLines() const
{
    std::string out = "deltaF_PUCCH_Format1b=" + deltaF_PUCCH_Format1b_ValueToString(deltaF_PUCCH_Format1b_internal_value) + ",";
    return out;
}

int DeltaFList_PUCCH::deltaF_PUCCH_Format1b_Clear()
{
    deltaF_PUCCH_Format1b_present = false;
    return 0;
}

bool DeltaFList_PUCCH::deltaF_PUCCH_Format1b_IsPresent() const
{
    return deltaF_PUCCH_Format1b_present;
}

int DeltaFList_PUCCH::deltaF_PUCCH_Format2_Pack(std::vector<uint8_t> &bits)
{
    if(!deltaF_PUCCH_Format2_present)
    {
        printf("DeltaFList_PUCCH::deltaF_PUCCH_Format2_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 2;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((deltaF_PUCCH_Format2_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int DeltaFList_PUCCH::deltaF_PUCCH_Format2_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return deltaF_PUCCH_Format2_Unpack(bits, idx);
}

int DeltaFList_PUCCH::deltaF_PUCCH_Format2_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 2;
    if((idx + N_bits) > bits.size())
    {
        printf("DeltaFList_PUCCH::deltaF_PUCCH_Format2_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 3)
    {
        printf("DeltaFList_PUCCH::deltaF_PUCCH_Format2_Unpack() max failure\n");
        return -1;
    }
    deltaF_PUCCH_Format2_internal_value = (deltaF_PUCCH_Format2_Enum)packed_val;
    deltaF_PUCCH_Format2_present = true;
    return 0;
}

DeltaFList_PUCCH::deltaF_PUCCH_Format2_Enum DeltaFList_PUCCH::deltaF_PUCCH_Format2_Value() const
{
    if(deltaF_PUCCH_Format2_present)
        return deltaF_PUCCH_Format2_internal_value;
    return (DeltaFList_PUCCH::deltaF_PUCCH_Format2_Enum)0;
}

int DeltaFList_PUCCH::deltaF_PUCCH_Format2_SetValue(deltaF_PUCCH_Format2_Enum value)
{
    deltaF_PUCCH_Format2_internal_value = value;
    deltaF_PUCCH_Format2_present = true;
    return 0;
}

int DeltaFList_PUCCH::deltaF_PUCCH_Format2_SetValue(std::string value)
{
    if("deltaF_2" == value)
    {
        deltaF_PUCCH_Format2_internal_value = k_deltaF_PUCCH_Format2_deltaF_2;
        deltaF_PUCCH_Format2_present = true;
        return 0;
    }
    if("deltaF0" == value)
    {
        deltaF_PUCCH_Format2_internal_value = k_deltaF_PUCCH_Format2_deltaF0;
        deltaF_PUCCH_Format2_present = true;
        return 0;
    }
    if("deltaF1" == value)
    {
        deltaF_PUCCH_Format2_internal_value = k_deltaF_PUCCH_Format2_deltaF1;
        deltaF_PUCCH_Format2_present = true;
        return 0;
    }
    if("deltaF2" == value)
    {
        deltaF_PUCCH_Format2_internal_value = k_deltaF_PUCCH_Format2_deltaF2;
        deltaF_PUCCH_Format2_present = true;
        return 0;
    }
    return 1;
}

std::string DeltaFList_PUCCH::deltaF_PUCCH_Format2_ValueToString(deltaF_PUCCH_Format2_Enum value) const
{
    if(k_deltaF_PUCCH_Format2_deltaF_2 == value)
        return "deltaF_2";
    if(k_deltaF_PUCCH_Format2_deltaF0 == value)
        return "deltaF0";
    if(k_deltaF_PUCCH_Format2_deltaF1 == value)
        return "deltaF1";
    if(k_deltaF_PUCCH_Format2_deltaF2 == value)
        return "deltaF2";
    return "";
}

uint64_t DeltaFList_PUCCH::deltaF_PUCCH_Format2_NumberOfValues() const
{
    return 4;
}

std::string DeltaFList_PUCCH::deltaF_PUCCH_Format2_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "deltaF_PUCCH_Format2 = " + deltaF_PUCCH_Format2_ValueToString(deltaF_PUCCH_Format2_internal_value) + "\n";
    return out;
}

std::string DeltaFList_PUCCH::deltaF_PUCCH_Format2_ToStringNoNewLines() const
{
    std::string out = "deltaF_PUCCH_Format2=" + deltaF_PUCCH_Format2_ValueToString(deltaF_PUCCH_Format2_internal_value) + ",";
    return out;
}

int DeltaFList_PUCCH::deltaF_PUCCH_Format2_Clear()
{
    deltaF_PUCCH_Format2_present = false;
    return 0;
}

bool DeltaFList_PUCCH::deltaF_PUCCH_Format2_IsPresent() const
{
    return deltaF_PUCCH_Format2_present;
}

int DeltaFList_PUCCH::deltaF_PUCCH_Format2a_Pack(std::vector<uint8_t> &bits)
{
    if(!deltaF_PUCCH_Format2a_present)
    {
        printf("DeltaFList_PUCCH::deltaF_PUCCH_Format2a_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 2;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((deltaF_PUCCH_Format2a_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int DeltaFList_PUCCH::deltaF_PUCCH_Format2a_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return deltaF_PUCCH_Format2a_Unpack(bits, idx);
}

int DeltaFList_PUCCH::deltaF_PUCCH_Format2a_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 2;
    if((idx + N_bits) > bits.size())
    {
        printf("DeltaFList_PUCCH::deltaF_PUCCH_Format2a_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 2)
    {
        printf("DeltaFList_PUCCH::deltaF_PUCCH_Format2a_Unpack() max failure\n");
        return -1;
    }
    deltaF_PUCCH_Format2a_internal_value = (deltaF_PUCCH_Format2a_Enum)packed_val;
    deltaF_PUCCH_Format2a_present = true;
    return 0;
}

DeltaFList_PUCCH::deltaF_PUCCH_Format2a_Enum DeltaFList_PUCCH::deltaF_PUCCH_Format2a_Value() const
{
    if(deltaF_PUCCH_Format2a_present)
        return deltaF_PUCCH_Format2a_internal_value;
    return (DeltaFList_PUCCH::deltaF_PUCCH_Format2a_Enum)0;
}

int DeltaFList_PUCCH::deltaF_PUCCH_Format2a_SetValue(deltaF_PUCCH_Format2a_Enum value)
{
    deltaF_PUCCH_Format2a_internal_value = value;
    deltaF_PUCCH_Format2a_present = true;
    return 0;
}

int DeltaFList_PUCCH::deltaF_PUCCH_Format2a_SetValue(std::string value)
{
    if("deltaF_2" == value)
    {
        deltaF_PUCCH_Format2a_internal_value = k_deltaF_PUCCH_Format2a_deltaF_2;
        deltaF_PUCCH_Format2a_present = true;
        return 0;
    }
    if("deltaF0" == value)
    {
        deltaF_PUCCH_Format2a_internal_value = k_deltaF_PUCCH_Format2a_deltaF0;
        deltaF_PUCCH_Format2a_present = true;
        return 0;
    }
    if("deltaF2" == value)
    {
        deltaF_PUCCH_Format2a_internal_value = k_deltaF_PUCCH_Format2a_deltaF2;
        deltaF_PUCCH_Format2a_present = true;
        return 0;
    }
    return 1;
}

std::string DeltaFList_PUCCH::deltaF_PUCCH_Format2a_ValueToString(deltaF_PUCCH_Format2a_Enum value) const
{
    if(k_deltaF_PUCCH_Format2a_deltaF_2 == value)
        return "deltaF_2";
    if(k_deltaF_PUCCH_Format2a_deltaF0 == value)
        return "deltaF0";
    if(k_deltaF_PUCCH_Format2a_deltaF2 == value)
        return "deltaF2";
    return "";
}

uint64_t DeltaFList_PUCCH::deltaF_PUCCH_Format2a_NumberOfValues() const
{
    return 3;
}

std::string DeltaFList_PUCCH::deltaF_PUCCH_Format2a_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "deltaF_PUCCH_Format2a = " + deltaF_PUCCH_Format2a_ValueToString(deltaF_PUCCH_Format2a_internal_value) + "\n";
    return out;
}

std::string DeltaFList_PUCCH::deltaF_PUCCH_Format2a_ToStringNoNewLines() const
{
    std::string out = "deltaF_PUCCH_Format2a=" + deltaF_PUCCH_Format2a_ValueToString(deltaF_PUCCH_Format2a_internal_value) + ",";
    return out;
}

int DeltaFList_PUCCH::deltaF_PUCCH_Format2a_Clear()
{
    deltaF_PUCCH_Format2a_present = false;
    return 0;
}

bool DeltaFList_PUCCH::deltaF_PUCCH_Format2a_IsPresent() const
{
    return deltaF_PUCCH_Format2a_present;
}

int DeltaFList_PUCCH::deltaF_PUCCH_Format2b_Pack(std::vector<uint8_t> &bits)
{
    if(!deltaF_PUCCH_Format2b_present)
    {
        printf("DeltaFList_PUCCH::deltaF_PUCCH_Format2b_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 2;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((deltaF_PUCCH_Format2b_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int DeltaFList_PUCCH::deltaF_PUCCH_Format2b_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return deltaF_PUCCH_Format2b_Unpack(bits, idx);
}

int DeltaFList_PUCCH::deltaF_PUCCH_Format2b_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 2;
    if((idx + N_bits) > bits.size())
    {
        printf("DeltaFList_PUCCH::deltaF_PUCCH_Format2b_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 2)
    {
        printf("DeltaFList_PUCCH::deltaF_PUCCH_Format2b_Unpack() max failure\n");
        return -1;
    }
    deltaF_PUCCH_Format2b_internal_value = (deltaF_PUCCH_Format2b_Enum)packed_val;
    deltaF_PUCCH_Format2b_present = true;
    return 0;
}

DeltaFList_PUCCH::deltaF_PUCCH_Format2b_Enum DeltaFList_PUCCH::deltaF_PUCCH_Format2b_Value() const
{
    if(deltaF_PUCCH_Format2b_present)
        return deltaF_PUCCH_Format2b_internal_value;
    return (DeltaFList_PUCCH::deltaF_PUCCH_Format2b_Enum)0;
}

int DeltaFList_PUCCH::deltaF_PUCCH_Format2b_SetValue(deltaF_PUCCH_Format2b_Enum value)
{
    deltaF_PUCCH_Format2b_internal_value = value;
    deltaF_PUCCH_Format2b_present = true;
    return 0;
}

int DeltaFList_PUCCH::deltaF_PUCCH_Format2b_SetValue(std::string value)
{
    if("deltaF_2" == value)
    {
        deltaF_PUCCH_Format2b_internal_value = k_deltaF_PUCCH_Format2b_deltaF_2;
        deltaF_PUCCH_Format2b_present = true;
        return 0;
    }
    if("deltaF0" == value)
    {
        deltaF_PUCCH_Format2b_internal_value = k_deltaF_PUCCH_Format2b_deltaF0;
        deltaF_PUCCH_Format2b_present = true;
        return 0;
    }
    if("deltaF2" == value)
    {
        deltaF_PUCCH_Format2b_internal_value = k_deltaF_PUCCH_Format2b_deltaF2;
        deltaF_PUCCH_Format2b_present = true;
        return 0;
    }
    return 1;
}

std::string DeltaFList_PUCCH::deltaF_PUCCH_Format2b_ValueToString(deltaF_PUCCH_Format2b_Enum value) const
{
    if(k_deltaF_PUCCH_Format2b_deltaF_2 == value)
        return "deltaF_2";
    if(k_deltaF_PUCCH_Format2b_deltaF0 == value)
        return "deltaF0";
    if(k_deltaF_PUCCH_Format2b_deltaF2 == value)
        return "deltaF2";
    return "";
}

uint64_t DeltaFList_PUCCH::deltaF_PUCCH_Format2b_NumberOfValues() const
{
    return 3;
}

std::string DeltaFList_PUCCH::deltaF_PUCCH_Format2b_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "deltaF_PUCCH_Format2b = " + deltaF_PUCCH_Format2b_ValueToString(deltaF_PUCCH_Format2b_internal_value) + "\n";
    return out;
}

std::string DeltaFList_PUCCH::deltaF_PUCCH_Format2b_ToStringNoNewLines() const
{
    std::string out = "deltaF_PUCCH_Format2b=" + deltaF_PUCCH_Format2b_ValueToString(deltaF_PUCCH_Format2b_internal_value) + ",";
    return out;
}

int DeltaFList_PUCCH::deltaF_PUCCH_Format2b_Clear()
{
    deltaF_PUCCH_Format2b_present = false;
    return 0;
}

bool DeltaFList_PUCCH::deltaF_PUCCH_Format2b_IsPresent() const
{
    return deltaF_PUCCH_Format2b_present;
}

