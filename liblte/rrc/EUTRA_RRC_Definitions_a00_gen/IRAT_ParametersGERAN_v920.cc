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

#include "IRAT_ParametersGERAN_v920.h"

#include <cmath>

int IRAT_ParametersGERAN_v920::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(dtm_r9_IsPresent());
    bits.push_back(e_RedirectionGERAN_r9_IsPresent());

    // Fields
    if(dtm_r9_IsPresent())
    {
        if(0 != dtm_r9_Pack(bits))
        {
            printf("IRAT_ParametersGERAN_v920:: field pack failure\n");
            return -1;
        }
    }
    if(e_RedirectionGERAN_r9_IsPresent())
    {
        if(0 != e_RedirectionGERAN_r9_Pack(bits))
        {
            printf("IRAT_ParametersGERAN_v920:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int IRAT_ParametersGERAN_v920::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int IRAT_ParametersGERAN_v920::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("IRAT_ParametersGERAN_v920::Unpack() index out of bounds for optional indiator dtm_r9\n");
        return -1;
    }
    dtm_r9_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("IRAT_ParametersGERAN_v920::Unpack() index out of bounds for optional indiator e_RedirectionGERAN_r9\n");
        return -1;
    }
    e_RedirectionGERAN_r9_present = bits[idx++];

    // Fields
    if(dtm_r9_present)
    {
        if(0 != dtm_r9_Unpack(bits, idx))
        {
            printf("IRAT_ParametersGERAN_v920:: field unpack failure\n");
            return -1;
        }
    }
    if(e_RedirectionGERAN_r9_present)
    {
        if(0 != e_RedirectionGERAN_r9_Unpack(bits, idx))
        {
            printf("IRAT_ParametersGERAN_v920:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string IRAT_ParametersGERAN_v920::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "IRAT_ParametersGERAN_v920:\n";
    if(dtm_r9_IsPresent())
        out += dtm_r9_ToString(indent+1);
    if(e_RedirectionGERAN_r9_IsPresent())
        out += e_RedirectionGERAN_r9_ToString(indent+1);
    return out;
}

std::string IRAT_ParametersGERAN_v920::ToStringNoNewLines() const
{
    std::string out = "IRAT_ParametersGERAN_v920:";
    if(dtm_r9_IsPresent())
        out += dtm_r9_ToStringNoNewLines();
    if(e_RedirectionGERAN_r9_IsPresent())
        out += e_RedirectionGERAN_r9_ToStringNoNewLines();
    return out;
}

int IRAT_ParametersGERAN_v920::dtm_r9_Pack(std::vector<uint8_t> &bits)
{
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((dtm_r9_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int IRAT_ParametersGERAN_v920::dtm_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return dtm_r9_Unpack(bits, idx);
}

int IRAT_ParametersGERAN_v920::dtm_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("IRAT_ParametersGERAN_v920::dtm_r9_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 0)
    {
        printf("IRAT_ParametersGERAN_v920::dtm_r9_Unpack() max failure\n");
        return -1;
    }
    dtm_r9_internal_value = (dtm_r9_Enum)packed_val;
    dtm_r9_present = true;
    return 0;
}

IRAT_ParametersGERAN_v920::dtm_r9_Enum IRAT_ParametersGERAN_v920::dtm_r9_Value() const
{
    if(dtm_r9_present)
        return dtm_r9_internal_value;
    return (IRAT_ParametersGERAN_v920::dtm_r9_Enum)0;
}

int IRAT_ParametersGERAN_v920::dtm_r9_SetValue(dtm_r9_Enum value)
{
    dtm_r9_internal_value = value;
    dtm_r9_present = true;
    return 0;
}

int IRAT_ParametersGERAN_v920::dtm_r9_SetValue(std::string value)
{
    if("supported" == value)
    {
        dtm_r9_internal_value = k_dtm_r9_supported;
        dtm_r9_present = true;
        return 0;
    }
    return 1;
}

std::string IRAT_ParametersGERAN_v920::dtm_r9_ValueToString(dtm_r9_Enum value) const
{
    if(k_dtm_r9_supported == value)
        return "supported";
    return "";
}

uint64_t IRAT_ParametersGERAN_v920::dtm_r9_NumberOfValues() const
{
    return 1;
}

std::string IRAT_ParametersGERAN_v920::dtm_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "dtm_r9 = " + dtm_r9_ValueToString(dtm_r9_internal_value) + "\n";
    return out;
}

std::string IRAT_ParametersGERAN_v920::dtm_r9_ToStringNoNewLines() const
{
    std::string out = "dtm_r9=" + dtm_r9_ValueToString(dtm_r9_internal_value) + ",";
    return out;
}

int IRAT_ParametersGERAN_v920::dtm_r9_Clear()
{
    dtm_r9_present = false;
    return 0;
}

bool IRAT_ParametersGERAN_v920::dtm_r9_IsPresent() const
{
    return dtm_r9_present;
}

int IRAT_ParametersGERAN_v920::e_RedirectionGERAN_r9_Pack(std::vector<uint8_t> &bits)
{
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((e_RedirectionGERAN_r9_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int IRAT_ParametersGERAN_v920::e_RedirectionGERAN_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return e_RedirectionGERAN_r9_Unpack(bits, idx);
}

int IRAT_ParametersGERAN_v920::e_RedirectionGERAN_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("IRAT_ParametersGERAN_v920::e_RedirectionGERAN_r9_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 0)
    {
        printf("IRAT_ParametersGERAN_v920::e_RedirectionGERAN_r9_Unpack() max failure\n");
        return -1;
    }
    e_RedirectionGERAN_r9_internal_value = (e_RedirectionGERAN_r9_Enum)packed_val;
    e_RedirectionGERAN_r9_present = true;
    return 0;
}

IRAT_ParametersGERAN_v920::e_RedirectionGERAN_r9_Enum IRAT_ParametersGERAN_v920::e_RedirectionGERAN_r9_Value() const
{
    if(e_RedirectionGERAN_r9_present)
        return e_RedirectionGERAN_r9_internal_value;
    return (IRAT_ParametersGERAN_v920::e_RedirectionGERAN_r9_Enum)0;
}

int IRAT_ParametersGERAN_v920::e_RedirectionGERAN_r9_SetValue(e_RedirectionGERAN_r9_Enum value)
{
    e_RedirectionGERAN_r9_internal_value = value;
    e_RedirectionGERAN_r9_present = true;
    return 0;
}

int IRAT_ParametersGERAN_v920::e_RedirectionGERAN_r9_SetValue(std::string value)
{
    if("supported" == value)
    {
        e_RedirectionGERAN_r9_internal_value = k_e_RedirectionGERAN_r9_supported;
        e_RedirectionGERAN_r9_present = true;
        return 0;
    }
    return 1;
}

std::string IRAT_ParametersGERAN_v920::e_RedirectionGERAN_r9_ValueToString(e_RedirectionGERAN_r9_Enum value) const
{
    if(k_e_RedirectionGERAN_r9_supported == value)
        return "supported";
    return "";
}

uint64_t IRAT_ParametersGERAN_v920::e_RedirectionGERAN_r9_NumberOfValues() const
{
    return 1;
}

std::string IRAT_ParametersGERAN_v920::e_RedirectionGERAN_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "e_RedirectionGERAN_r9 = " + e_RedirectionGERAN_r9_ValueToString(e_RedirectionGERAN_r9_internal_value) + "\n";
    return out;
}

std::string IRAT_ParametersGERAN_v920::e_RedirectionGERAN_r9_ToStringNoNewLines() const
{
    std::string out = "e_RedirectionGERAN_r9=" + e_RedirectionGERAN_r9_ValueToString(e_RedirectionGERAN_r9_internal_value) + ",";
    return out;
}

int IRAT_ParametersGERAN_v920::e_RedirectionGERAN_r9_Clear()
{
    e_RedirectionGERAN_r9_present = false;
    return 0;
}

bool IRAT_ParametersGERAN_v920::e_RedirectionGERAN_r9_IsPresent() const
{
    return e_RedirectionGERAN_r9_present;
}

