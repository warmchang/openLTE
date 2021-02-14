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

#include "Paging_v920_IEs.h"

#include <cmath>

int Paging_v920_IEs::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(cmas_Indication_r9_IsPresent());
    bits.push_back(0);

    // Fields
    if(cmas_Indication_r9_IsPresent())
    {
        if(0 != cmas_Indication_r9_Pack(bits))
        {
            printf("Paging_v920_IEs:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int Paging_v920_IEs::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int Paging_v920_IEs::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("Paging_v920_IEs::Unpack() index out of bounds for optional indiator cmas_Indication_r9\n");
        return -1;
    }
    cmas_Indication_r9_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("Paging_v920_IEs::Unpack() index out of bounds for optional indiator nonCriticalExtension\n");
        return -1;
    }
    idx++;

    // Fields
    if(cmas_Indication_r9_present)
    {
        if(0 != cmas_Indication_r9_Unpack(bits, idx))
        {
            printf("Paging_v920_IEs:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string Paging_v920_IEs::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "Paging_v920_IEs:\n";
    if(cmas_Indication_r9_IsPresent())
        out += cmas_Indication_r9_ToString(indent+1);
    return out;
}

std::string Paging_v920_IEs::ToStringNoNewLines() const
{
    std::string out = "Paging_v920_IEs:";
    if(cmas_Indication_r9_IsPresent())
        out += cmas_Indication_r9_ToStringNoNewLines();
    return out;
}

int Paging_v920_IEs::cmas_Indication_r9_Pack(std::vector<uint8_t> &bits)
{
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((cmas_Indication_r9_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int Paging_v920_IEs::cmas_Indication_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return cmas_Indication_r9_Unpack(bits, idx);
}

int Paging_v920_IEs::cmas_Indication_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("Paging_v920_IEs::cmas_Indication_r9_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 0)
    {
        printf("Paging_v920_IEs::cmas_Indication_r9_Unpack() max failure\n");
        return -1;
    }
    cmas_Indication_r9_internal_value = (cmas_Indication_r9_Enum)packed_val;
    cmas_Indication_r9_present = true;
    return 0;
}

Paging_v920_IEs::cmas_Indication_r9_Enum Paging_v920_IEs::cmas_Indication_r9_Value() const
{
    if(cmas_Indication_r9_present)
        return cmas_Indication_r9_internal_value;
    return (Paging_v920_IEs::cmas_Indication_r9_Enum)0;
}

int Paging_v920_IEs::cmas_Indication_r9_SetValue(cmas_Indication_r9_Enum value)
{
    cmas_Indication_r9_internal_value = value;
    cmas_Indication_r9_present = true;
    return 0;
}

int Paging_v920_IEs::cmas_Indication_r9_SetValue(std::string value)
{
    if("true" == value)
    {
        cmas_Indication_r9_internal_value = k_cmas_Indication_r9_true;
        cmas_Indication_r9_present = true;
        return 0;
    }
    return 1;
}

std::string Paging_v920_IEs::cmas_Indication_r9_ValueToString(cmas_Indication_r9_Enum value) const
{
    if(k_cmas_Indication_r9_true == value)
        return "true";
    return "";
}

uint64_t Paging_v920_IEs::cmas_Indication_r9_NumberOfValues() const
{
    return 1;
}

std::string Paging_v920_IEs::cmas_Indication_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cmas_Indication_r9 = " + cmas_Indication_r9_ValueToString(cmas_Indication_r9_internal_value) + "\n";
    return out;
}

std::string Paging_v920_IEs::cmas_Indication_r9_ToStringNoNewLines() const
{
    std::string out = "cmas_Indication_r9=" + cmas_Indication_r9_ValueToString(cmas_Indication_r9_internal_value) + ",";
    return out;
}

int Paging_v920_IEs::cmas_Indication_r9_Clear()
{
    cmas_Indication_r9_present = false;
    return 0;
}

bool Paging_v920_IEs::cmas_Indication_r9_IsPresent() const
{
    return cmas_Indication_r9_present;
}

