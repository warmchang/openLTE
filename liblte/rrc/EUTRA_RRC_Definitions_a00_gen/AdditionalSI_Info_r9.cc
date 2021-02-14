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

#include "AdditionalSI_Info_r9.h"

#include <cmath>

int AdditionalSI_Info_r9::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(csg_MemberStatus_r9_IsPresent());
    bits.push_back(csg_Identity_r9_IsPresent());

    // Fields
    if(csg_MemberStatus_r9_IsPresent())
    {
        if(0 != csg_MemberStatus_r9_Pack(bits))
        {
            printf("AdditionalSI_Info_r9:: field pack failure\n");
            return -1;
        }
    }
    if(csg_Identity_r9_IsPresent())
    {
        if(0 != csg_Identity_r9.Pack(bits))
        {
            printf("AdditionalSI_Info_r9:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int AdditionalSI_Info_r9::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int AdditionalSI_Info_r9::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("AdditionalSI_Info_r9::Unpack() index out of bounds for optional indiator csg_MemberStatus_r9\n");
        return -1;
    }
    csg_MemberStatus_r9_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("AdditionalSI_Info_r9::Unpack() index out of bounds for optional indiator csg_Identity_r9\n");
        return -1;
    }
    csg_Identity_r9_present = bits[idx++];

    // Fields
    if(csg_MemberStatus_r9_present)
    {
        if(0 != csg_MemberStatus_r9_Unpack(bits, idx))
        {
            printf("AdditionalSI_Info_r9:: field unpack failure\n");
            return -1;
        }
    }
    if(csg_Identity_r9_present)
    {
        if(0 != csg_Identity_r9.Unpack(bits, idx))
        {
            printf("AdditionalSI_Info_r9:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string AdditionalSI_Info_r9::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "AdditionalSI_Info_r9:\n";
    if(csg_MemberStatus_r9_IsPresent())
        out += csg_MemberStatus_r9_ToString(indent+1);
    if(csg_Identity_r9_IsPresent())
        out += csg_Identity_r9_ToString(indent+1);
    return out;
}

std::string AdditionalSI_Info_r9::ToStringNoNewLines() const
{
    std::string out = "AdditionalSI_Info_r9:";
    if(csg_MemberStatus_r9_IsPresent())
        out += csg_MemberStatus_r9_ToStringNoNewLines();
    if(csg_Identity_r9_IsPresent())
        out += csg_Identity_r9_ToStringNoNewLines();
    return out;
}

int AdditionalSI_Info_r9::csg_MemberStatus_r9_Pack(std::vector<uint8_t> &bits)
{
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((csg_MemberStatus_r9_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int AdditionalSI_Info_r9::csg_MemberStatus_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return csg_MemberStatus_r9_Unpack(bits, idx);
}

int AdditionalSI_Info_r9::csg_MemberStatus_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("AdditionalSI_Info_r9::csg_MemberStatus_r9_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 0)
    {
        printf("AdditionalSI_Info_r9::csg_MemberStatus_r9_Unpack() max failure\n");
        return -1;
    }
    csg_MemberStatus_r9_internal_value = (csg_MemberStatus_r9_Enum)packed_val;
    csg_MemberStatus_r9_present = true;
    return 0;
}

AdditionalSI_Info_r9::csg_MemberStatus_r9_Enum AdditionalSI_Info_r9::csg_MemberStatus_r9_Value() const
{
    if(csg_MemberStatus_r9_present)
        return csg_MemberStatus_r9_internal_value;
    return (AdditionalSI_Info_r9::csg_MemberStatus_r9_Enum)0;
}

int AdditionalSI_Info_r9::csg_MemberStatus_r9_SetValue(csg_MemberStatus_r9_Enum value)
{
    csg_MemberStatus_r9_internal_value = value;
    csg_MemberStatus_r9_present = true;
    return 0;
}

int AdditionalSI_Info_r9::csg_MemberStatus_r9_SetValue(std::string value)
{
    if("member" == value)
    {
        csg_MemberStatus_r9_internal_value = k_csg_MemberStatus_r9_member;
        csg_MemberStatus_r9_present = true;
        return 0;
    }
    return 1;
}

std::string AdditionalSI_Info_r9::csg_MemberStatus_r9_ValueToString(csg_MemberStatus_r9_Enum value) const
{
    if(k_csg_MemberStatus_r9_member == value)
        return "member";
    return "";
}

uint64_t AdditionalSI_Info_r9::csg_MemberStatus_r9_NumberOfValues() const
{
    return 1;
}

std::string AdditionalSI_Info_r9::csg_MemberStatus_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "csg_MemberStatus_r9 = " + csg_MemberStatus_r9_ValueToString(csg_MemberStatus_r9_internal_value) + "\n";
    return out;
}

std::string AdditionalSI_Info_r9::csg_MemberStatus_r9_ToStringNoNewLines() const
{
    std::string out = "csg_MemberStatus_r9=" + csg_MemberStatus_r9_ValueToString(csg_MemberStatus_r9_internal_value) + ",";
    return out;
}

int AdditionalSI_Info_r9::csg_MemberStatus_r9_Clear()
{
    csg_MemberStatus_r9_present = false;
    return 0;
}

bool AdditionalSI_Info_r9::csg_MemberStatus_r9_IsPresent() const
{
    return csg_MemberStatus_r9_present;
}

CSG_Identity* AdditionalSI_Info_r9::csg_Identity_r9_Set()
{
    csg_Identity_r9_present = true;
    return &csg_Identity_r9;
}

int AdditionalSI_Info_r9::csg_Identity_r9_Set(CSG_Identity &value)
{
    csg_Identity_r9_present = true;
    csg_Identity_r9 = value;
    return 0;
}

const CSG_Identity& AdditionalSI_Info_r9::csg_Identity_r9_Get() const
{
    return csg_Identity_r9;
}

std::string AdditionalSI_Info_r9::csg_Identity_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "csg_Identity_r9:\n";
    out += csg_Identity_r9.ToString(indent+1);
    return out;
}

std::string AdditionalSI_Info_r9::csg_Identity_r9_ToStringNoNewLines() const
{
    std::string out = "csg_Identity_r9:";
    out += csg_Identity_r9.ToStringNoNewLines();
    return out;
}

int AdditionalSI_Info_r9::csg_Identity_r9_Clear()
{
    csg_Identity_r9_present = false;
    return 0;
}

bool AdditionalSI_Info_r9::csg_Identity_r9_IsPresent() const
{
    return csg_Identity_r9_present;
}

