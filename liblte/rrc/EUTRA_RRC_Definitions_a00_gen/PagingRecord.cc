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

#include "PagingRecord.h"

#include <cmath>

int PagingRecord::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator
    bits.push_back(0);

    // Optional indicators

    // Fields
    {
        if(0 != ue_Identity.Pack(bits))
        {
            printf("PagingRecord:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != cn_Domain_Pack(bits))
        {
            printf("PagingRecord:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int PagingRecord::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int PagingRecord::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("PagingRecord::Unpack() index out of bounds for extension\n");
        return -1;
    }
    idx++;

    // Optional indicators

    // Fields
    {
        if(0 != ue_Identity.Unpack(bits, idx))
        {
            printf("PagingRecord:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != cn_Domain_Unpack(bits, idx))
        {
            printf("PagingRecord:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string PagingRecord::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "PagingRecord:\n";
    out += ue_Identity_ToString(indent+1);
    out += cn_Domain_ToString(indent+1);
    return out;
}

std::string PagingRecord::ToStringNoNewLines() const
{
    std::string out = "PagingRecord:";
    out += ue_Identity_ToStringNoNewLines();
    out += cn_Domain_ToStringNoNewLines();
    return out;
}

PagingUE_Identity* PagingRecord::ue_Identity_Set()
{
    ue_Identity_present = true;
    return &ue_Identity;
}

int PagingRecord::ue_Identity_Set(PagingUE_Identity &value)
{
    ue_Identity_present = true;
    ue_Identity = value;
    return 0;
}

const PagingUE_Identity& PagingRecord::ue_Identity_Get() const
{
    return ue_Identity;
}

std::string PagingRecord::ue_Identity_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ue_Identity:\n";
    out += ue_Identity.ToString(indent+1);
    return out;
}

std::string PagingRecord::ue_Identity_ToStringNoNewLines() const
{
    std::string out = "ue_Identity:";
    out += ue_Identity.ToStringNoNewLines();
    return out;
}

int PagingRecord::ue_Identity_Clear()
{
    ue_Identity_present = false;
    return 0;
}

bool PagingRecord::ue_Identity_IsPresent() const
{
    return ue_Identity_present;
}

int PagingRecord::cn_Domain_Pack(std::vector<uint8_t> &bits)
{
    if(!cn_Domain_present)
    {
        printf("PagingRecord::cn_Domain_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((cn_Domain_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int PagingRecord::cn_Domain_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return cn_Domain_Unpack(bits, idx);
}

int PagingRecord::cn_Domain_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("PagingRecord::cn_Domain_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 1)
    {
        printf("PagingRecord::cn_Domain_Unpack() max failure\n");
        return -1;
    }
    cn_Domain_internal_value = (cn_Domain_Enum)packed_val;
    cn_Domain_present = true;
    return 0;
}

PagingRecord::cn_Domain_Enum PagingRecord::cn_Domain_Value() const
{
    if(cn_Domain_present)
        return cn_Domain_internal_value;
    return (PagingRecord::cn_Domain_Enum)0;
}

int PagingRecord::cn_Domain_SetValue(cn_Domain_Enum value)
{
    cn_Domain_internal_value = value;
    cn_Domain_present = true;
    return 0;
}

int PagingRecord::cn_Domain_SetValue(std::string value)
{
    if("ps" == value)
    {
        cn_Domain_internal_value = k_cn_Domain_ps;
        cn_Domain_present = true;
        return 0;
    }
    if("cs" == value)
    {
        cn_Domain_internal_value = k_cn_Domain_cs;
        cn_Domain_present = true;
        return 0;
    }
    return 1;
}

std::string PagingRecord::cn_Domain_ValueToString(cn_Domain_Enum value) const
{
    if(k_cn_Domain_ps == value)
        return "ps";
    if(k_cn_Domain_cs == value)
        return "cs";
    return "";
}

uint64_t PagingRecord::cn_Domain_NumberOfValues() const
{
    return 2;
}

std::string PagingRecord::cn_Domain_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cn_Domain = " + cn_Domain_ValueToString(cn_Domain_internal_value) + "\n";
    return out;
}

std::string PagingRecord::cn_Domain_ToStringNoNewLines() const
{
    std::string out = "cn_Domain=" + cn_Domain_ValueToString(cn_Domain_internal_value) + ",";
    return out;
}

int PagingRecord::cn_Domain_Clear()
{
    cn_Domain_present = false;
    return 0;
}

bool PagingRecord::cn_Domain_IsPresent() const
{
    return cn_Domain_present;
}

