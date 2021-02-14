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

#include "BCCH_Config.h"

#include <cmath>

int BCCH_Config::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != modificationPeriodCoeff_Pack(bits))
        {
            printf("BCCH_Config:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int BCCH_Config::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int BCCH_Config::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != modificationPeriodCoeff_Unpack(bits, idx))
        {
            printf("BCCH_Config:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string BCCH_Config::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "BCCH_Config:\n";
    out += modificationPeriodCoeff_ToString(indent+1);
    return out;
}

std::string BCCH_Config::ToStringNoNewLines() const
{
    std::string out = "BCCH_Config:";
    out += modificationPeriodCoeff_ToStringNoNewLines();
    return out;
}

int BCCH_Config::modificationPeriodCoeff_Pack(std::vector<uint8_t> &bits)
{
    if(!modificationPeriodCoeff_present)
    {
        printf("BCCH_Config::modificationPeriodCoeff_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 2;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((modificationPeriodCoeff_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int BCCH_Config::modificationPeriodCoeff_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return modificationPeriodCoeff_Unpack(bits, idx);
}

int BCCH_Config::modificationPeriodCoeff_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 2;
    if((idx + N_bits) > bits.size())
    {
        printf("BCCH_Config::modificationPeriodCoeff_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 3)
    {
        printf("BCCH_Config::modificationPeriodCoeff_Unpack() max failure\n");
        return -1;
    }
    modificationPeriodCoeff_internal_value = (modificationPeriodCoeff_Enum)packed_val;
    modificationPeriodCoeff_present = true;
    return 0;
}

BCCH_Config::modificationPeriodCoeff_Enum BCCH_Config::modificationPeriodCoeff_Value() const
{
    if(modificationPeriodCoeff_present)
        return modificationPeriodCoeff_internal_value;
    return (BCCH_Config::modificationPeriodCoeff_Enum)0;
}

int BCCH_Config::modificationPeriodCoeff_SetValue(modificationPeriodCoeff_Enum value)
{
    modificationPeriodCoeff_internal_value = value;
    modificationPeriodCoeff_present = true;
    return 0;
}

int BCCH_Config::modificationPeriodCoeff_SetValue(std::string value)
{
    if("n2" == value)
    {
        modificationPeriodCoeff_internal_value = k_modificationPeriodCoeff_n2;
        modificationPeriodCoeff_present = true;
        return 0;
    }
    if("n4" == value)
    {
        modificationPeriodCoeff_internal_value = k_modificationPeriodCoeff_n4;
        modificationPeriodCoeff_present = true;
        return 0;
    }
    if("n8" == value)
    {
        modificationPeriodCoeff_internal_value = k_modificationPeriodCoeff_n8;
        modificationPeriodCoeff_present = true;
        return 0;
    }
    if("n16" == value)
    {
        modificationPeriodCoeff_internal_value = k_modificationPeriodCoeff_n16;
        modificationPeriodCoeff_present = true;
        return 0;
    }
    return 1;
}

std::string BCCH_Config::modificationPeriodCoeff_ValueToString(modificationPeriodCoeff_Enum value) const
{
    if(k_modificationPeriodCoeff_n2 == value)
        return "n2";
    if(k_modificationPeriodCoeff_n4 == value)
        return "n4";
    if(k_modificationPeriodCoeff_n8 == value)
        return "n8";
    if(k_modificationPeriodCoeff_n16 == value)
        return "n16";
    return "";
}

uint64_t BCCH_Config::modificationPeriodCoeff_NumberOfValues() const
{
    return 4;
}

std::string BCCH_Config::modificationPeriodCoeff_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "modificationPeriodCoeff = " + modificationPeriodCoeff_ValueToString(modificationPeriodCoeff_internal_value) + "\n";
    return out;
}

std::string BCCH_Config::modificationPeriodCoeff_ToStringNoNewLines() const
{
    std::string out = "modificationPeriodCoeff=" + modificationPeriodCoeff_ValueToString(modificationPeriodCoeff_internal_value) + ",";
    return out;
}

int BCCH_Config::modificationPeriodCoeff_Clear()
{
    modificationPeriodCoeff_present = false;
    return 0;
}

bool BCCH_Config::modificationPeriodCoeff_IsPresent() const
{
    return modificationPeriodCoeff_present;
}

