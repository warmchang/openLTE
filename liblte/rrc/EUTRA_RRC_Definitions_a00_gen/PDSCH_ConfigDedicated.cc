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

#include "PDSCH_ConfigDedicated.h"

#include <cmath>

int PDSCH_ConfigDedicated::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != p_a_Pack(bits))
        {
            printf("PDSCH_ConfigDedicated:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int PDSCH_ConfigDedicated::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int PDSCH_ConfigDedicated::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != p_a_Unpack(bits, idx))
        {
            printf("PDSCH_ConfigDedicated:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string PDSCH_ConfigDedicated::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "PDSCH_ConfigDedicated:\n";
    out += p_a_ToString(indent+1);
    return out;
}

std::string PDSCH_ConfigDedicated::ToStringNoNewLines() const
{
    std::string out = "PDSCH_ConfigDedicated:";
    out += p_a_ToStringNoNewLines();
    return out;
}

int PDSCH_ConfigDedicated::p_a_Pack(std::vector<uint8_t> &bits)
{
    if(!p_a_present)
    {
        printf("PDSCH_ConfigDedicated::p_a_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 3;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((p_a_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int PDSCH_ConfigDedicated::p_a_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return p_a_Unpack(bits, idx);
}

int PDSCH_ConfigDedicated::p_a_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 3;
    if((idx + N_bits) > bits.size())
    {
        printf("PDSCH_ConfigDedicated::p_a_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 7)
    {
        printf("PDSCH_ConfigDedicated::p_a_Unpack() max failure\n");
        return -1;
    }
    p_a_internal_value = (p_a_Enum)packed_val;
    p_a_present = true;
    return 0;
}

PDSCH_ConfigDedicated::p_a_Enum PDSCH_ConfigDedicated::p_a_Value() const
{
    if(p_a_present)
        return p_a_internal_value;
    return (PDSCH_ConfigDedicated::p_a_Enum)0;
}

int PDSCH_ConfigDedicated::p_a_SetValue(p_a_Enum value)
{
    p_a_internal_value = value;
    p_a_present = true;
    return 0;
}

int PDSCH_ConfigDedicated::p_a_SetValue(std::string value)
{
    if("dB_6" == value)
    {
        p_a_internal_value = k_p_a_dB_6;
        p_a_present = true;
        return 0;
    }
    if("dB_4dot77" == value)
    {
        p_a_internal_value = k_p_a_dB_4dot77;
        p_a_present = true;
        return 0;
    }
    if("dB_3" == value)
    {
        p_a_internal_value = k_p_a_dB_3;
        p_a_present = true;
        return 0;
    }
    if("dB_1dot77" == value)
    {
        p_a_internal_value = k_p_a_dB_1dot77;
        p_a_present = true;
        return 0;
    }
    if("dB0" == value)
    {
        p_a_internal_value = k_p_a_dB0;
        p_a_present = true;
        return 0;
    }
    if("dB1" == value)
    {
        p_a_internal_value = k_p_a_dB1;
        p_a_present = true;
        return 0;
    }
    if("dB2" == value)
    {
        p_a_internal_value = k_p_a_dB2;
        p_a_present = true;
        return 0;
    }
    if("dB3" == value)
    {
        p_a_internal_value = k_p_a_dB3;
        p_a_present = true;
        return 0;
    }
    return 1;
}

std::string PDSCH_ConfigDedicated::p_a_ValueToString(p_a_Enum value) const
{
    if(k_p_a_dB_6 == value)
        return "dB_6";
    if(k_p_a_dB_4dot77 == value)
        return "dB_4dot77";
    if(k_p_a_dB_3 == value)
        return "dB_3";
    if(k_p_a_dB_1dot77 == value)
        return "dB_1dot77";
    if(k_p_a_dB0 == value)
        return "dB0";
    if(k_p_a_dB1 == value)
        return "dB1";
    if(k_p_a_dB2 == value)
        return "dB2";
    if(k_p_a_dB3 == value)
        return "dB3";
    return "";
}

uint64_t PDSCH_ConfigDedicated::p_a_NumberOfValues() const
{
    return 8;
}

std::string PDSCH_ConfigDedicated::p_a_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "p_a = " + p_a_ValueToString(p_a_internal_value) + "\n";
    return out;
}

std::string PDSCH_ConfigDedicated::p_a_ToStringNoNewLines() const
{
    std::string out = "p_a=" + p_a_ValueToString(p_a_internal_value) + ",";
    return out;
}

int PDSCH_ConfigDedicated::p_a_Clear()
{
    p_a_present = false;
    return 0;
}

bool PDSCH_ConfigDedicated::p_a_IsPresent() const
{
    return p_a_present;
}

