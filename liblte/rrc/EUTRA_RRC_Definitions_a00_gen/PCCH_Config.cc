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

#include "PCCH_Config.h"

#include <cmath>

int PCCH_Config::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != defaultPagingCycle_Pack(bits))
        {
            printf("PCCH_Config:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != nB_Pack(bits))
        {
            printf("PCCH_Config:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int PCCH_Config::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int PCCH_Config::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != defaultPagingCycle_Unpack(bits, idx))
        {
            printf("PCCH_Config:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != nB_Unpack(bits, idx))
        {
            printf("PCCH_Config:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string PCCH_Config::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "PCCH_Config:\n";
    out += defaultPagingCycle_ToString(indent+1);
    out += nB_ToString(indent+1);
    return out;
}

std::string PCCH_Config::ToStringNoNewLines() const
{
    std::string out = "PCCH_Config:";
    out += defaultPagingCycle_ToStringNoNewLines();
    out += nB_ToStringNoNewLines();
    return out;
}

int PCCH_Config::defaultPagingCycle_Pack(std::vector<uint8_t> &bits)
{
    if(!defaultPagingCycle_present)
    {
        printf("PCCH_Config::defaultPagingCycle_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 2;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((defaultPagingCycle_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int PCCH_Config::defaultPagingCycle_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return defaultPagingCycle_Unpack(bits, idx);
}

int PCCH_Config::defaultPagingCycle_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 2;
    if((idx + N_bits) > bits.size())
    {
        printf("PCCH_Config::defaultPagingCycle_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 3)
    {
        printf("PCCH_Config::defaultPagingCycle_Unpack() max failure\n");
        return -1;
    }
    defaultPagingCycle_internal_value = (defaultPagingCycle_Enum)packed_val;
    defaultPagingCycle_present = true;
    return 0;
}

PCCH_Config::defaultPagingCycle_Enum PCCH_Config::defaultPagingCycle_Value() const
{
    if(defaultPagingCycle_present)
        return defaultPagingCycle_internal_value;
    return (PCCH_Config::defaultPagingCycle_Enum)0;
}

int PCCH_Config::defaultPagingCycle_SetValue(defaultPagingCycle_Enum value)
{
    defaultPagingCycle_internal_value = value;
    defaultPagingCycle_present = true;
    return 0;
}

int PCCH_Config::defaultPagingCycle_SetValue(std::string value)
{
    if("rf32" == value)
    {
        defaultPagingCycle_internal_value = k_defaultPagingCycle_rf32;
        defaultPagingCycle_present = true;
        return 0;
    }
    if("rf64" == value)
    {
        defaultPagingCycle_internal_value = k_defaultPagingCycle_rf64;
        defaultPagingCycle_present = true;
        return 0;
    }
    if("rf128" == value)
    {
        defaultPagingCycle_internal_value = k_defaultPagingCycle_rf128;
        defaultPagingCycle_present = true;
        return 0;
    }
    if("rf256" == value)
    {
        defaultPagingCycle_internal_value = k_defaultPagingCycle_rf256;
        defaultPagingCycle_present = true;
        return 0;
    }
    return 1;
}

std::string PCCH_Config::defaultPagingCycle_ValueToString(defaultPagingCycle_Enum value) const
{
    if(k_defaultPagingCycle_rf32 == value)
        return "rf32";
    if(k_defaultPagingCycle_rf64 == value)
        return "rf64";
    if(k_defaultPagingCycle_rf128 == value)
        return "rf128";
    if(k_defaultPagingCycle_rf256 == value)
        return "rf256";
    return "";
}

uint64_t PCCH_Config::defaultPagingCycle_NumberOfValues() const
{
    return 4;
}

std::string PCCH_Config::defaultPagingCycle_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "defaultPagingCycle = " + defaultPagingCycle_ValueToString(defaultPagingCycle_internal_value) + "\n";
    return out;
}

std::string PCCH_Config::defaultPagingCycle_ToStringNoNewLines() const
{
    std::string out = "defaultPagingCycle=" + defaultPagingCycle_ValueToString(defaultPagingCycle_internal_value) + ",";
    return out;
}

int PCCH_Config::defaultPagingCycle_Clear()
{
    defaultPagingCycle_present = false;
    return 0;
}

bool PCCH_Config::defaultPagingCycle_IsPresent() const
{
    return defaultPagingCycle_present;
}

int PCCH_Config::nB_Pack(std::vector<uint8_t> &bits)
{
    if(!nB_present)
    {
        printf("PCCH_Config::nB_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 3;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((nB_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int PCCH_Config::nB_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return nB_Unpack(bits, idx);
}

int PCCH_Config::nB_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 3;
    if((idx + N_bits) > bits.size())
    {
        printf("PCCH_Config::nB_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 7)
    {
        printf("PCCH_Config::nB_Unpack() max failure\n");
        return -1;
    }
    nB_internal_value = (nB_Enum)packed_val;
    nB_present = true;
    return 0;
}

PCCH_Config::nB_Enum PCCH_Config::nB_Value() const
{
    if(nB_present)
        return nB_internal_value;
    return (PCCH_Config::nB_Enum)0;
}

int PCCH_Config::nB_SetValue(nB_Enum value)
{
    nB_internal_value = value;
    nB_present = true;
    return 0;
}

int PCCH_Config::nB_SetValue(std::string value)
{
    if("fourT" == value)
    {
        nB_internal_value = k_nB_fourT;
        nB_present = true;
        return 0;
    }
    if("twoT" == value)
    {
        nB_internal_value = k_nB_twoT;
        nB_present = true;
        return 0;
    }
    if("oneT" == value)
    {
        nB_internal_value = k_nB_oneT;
        nB_present = true;
        return 0;
    }
    if("halfT" == value)
    {
        nB_internal_value = k_nB_halfT;
        nB_present = true;
        return 0;
    }
    if("quarterT" == value)
    {
        nB_internal_value = k_nB_quarterT;
        nB_present = true;
        return 0;
    }
    if("oneEighthT" == value)
    {
        nB_internal_value = k_nB_oneEighthT;
        nB_present = true;
        return 0;
    }
    if("oneSixteenthT" == value)
    {
        nB_internal_value = k_nB_oneSixteenthT;
        nB_present = true;
        return 0;
    }
    if("oneThirtySecondT" == value)
    {
        nB_internal_value = k_nB_oneThirtySecondT;
        nB_present = true;
        return 0;
    }
    return 1;
}

std::string PCCH_Config::nB_ValueToString(nB_Enum value) const
{
    if(k_nB_fourT == value)
        return "fourT";
    if(k_nB_twoT == value)
        return "twoT";
    if(k_nB_oneT == value)
        return "oneT";
    if(k_nB_halfT == value)
        return "halfT";
    if(k_nB_quarterT == value)
        return "quarterT";
    if(k_nB_oneEighthT == value)
        return "oneEighthT";
    if(k_nB_oneSixteenthT == value)
        return "oneSixteenthT";
    if(k_nB_oneThirtySecondT == value)
        return "oneThirtySecondT";
    return "";
}

uint64_t PCCH_Config::nB_NumberOfValues() const
{
    return 8;
}

std::string PCCH_Config::nB_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "nB = " + nB_ValueToString(nB_internal_value) + "\n";
    return out;
}

std::string PCCH_Config::nB_ToStringNoNewLines() const
{
    std::string out = "nB=" + nB_ValueToString(nB_internal_value) + ",";
    return out;
}

int PCCH_Config::nB_Clear()
{
    nB_present = false;
    return 0;
}

bool PCCH_Config::nB_IsPresent() const
{
    return nB_present;
}

