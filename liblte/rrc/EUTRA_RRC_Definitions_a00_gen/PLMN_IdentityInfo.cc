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

#include "PLMN_IdentityInfo.h"

#include <cmath>

int PLMN_IdentityInfo::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != plmn_Identity.Pack(bits))
        {
            printf("PLMN_IdentityInfo:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != cellReservedForOperatorUse_Pack(bits))
        {
            printf("PLMN_IdentityInfo:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int PLMN_IdentityInfo::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int PLMN_IdentityInfo::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != plmn_Identity.Unpack(bits, idx))
        {
            printf("PLMN_IdentityInfo:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != cellReservedForOperatorUse_Unpack(bits, idx))
        {
            printf("PLMN_IdentityInfo:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string PLMN_IdentityInfo::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "PLMN_IdentityInfo:\n";
    out += plmn_Identity_ToString(indent+1);
    out += cellReservedForOperatorUse_ToString(indent+1);
    return out;
}

std::string PLMN_IdentityInfo::ToStringNoNewLines() const
{
    std::string out = "PLMN_IdentityInfo:";
    out += plmn_Identity_ToStringNoNewLines();
    out += cellReservedForOperatorUse_ToStringNoNewLines();
    return out;
}

PLMN_Identity* PLMN_IdentityInfo::plmn_Identity_Set()
{
    plmn_Identity_present = true;
    return &plmn_Identity;
}

int PLMN_IdentityInfo::plmn_Identity_Set(PLMN_Identity &value)
{
    plmn_Identity_present = true;
    plmn_Identity = value;
    return 0;
}

const PLMN_Identity& PLMN_IdentityInfo::plmn_Identity_Get() const
{
    return plmn_Identity;
}

std::string PLMN_IdentityInfo::plmn_Identity_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "plmn_Identity:\n";
    out += plmn_Identity.ToString(indent+1);
    return out;
}

std::string PLMN_IdentityInfo::plmn_Identity_ToStringNoNewLines() const
{
    std::string out = "plmn_Identity:";
    out += plmn_Identity.ToStringNoNewLines();
    return out;
}

int PLMN_IdentityInfo::plmn_Identity_Clear()
{
    plmn_Identity_present = false;
    return 0;
}

bool PLMN_IdentityInfo::plmn_Identity_IsPresent() const
{
    return plmn_Identity_present;
}

int PLMN_IdentityInfo::cellReservedForOperatorUse_Pack(std::vector<uint8_t> &bits)
{
    if(!cellReservedForOperatorUse_present)
    {
        printf("PLMN_IdentityInfo::cellReservedForOperatorUse_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((cellReservedForOperatorUse_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int PLMN_IdentityInfo::cellReservedForOperatorUse_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return cellReservedForOperatorUse_Unpack(bits, idx);
}

int PLMN_IdentityInfo::cellReservedForOperatorUse_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("PLMN_IdentityInfo::cellReservedForOperatorUse_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 1)
    {
        printf("PLMN_IdentityInfo::cellReservedForOperatorUse_Unpack() max failure\n");
        return -1;
    }
    cellReservedForOperatorUse_internal_value = (cellReservedForOperatorUse_Enum)packed_val;
    cellReservedForOperatorUse_present = true;
    return 0;
}

PLMN_IdentityInfo::cellReservedForOperatorUse_Enum PLMN_IdentityInfo::cellReservedForOperatorUse_Value() const
{
    if(cellReservedForOperatorUse_present)
        return cellReservedForOperatorUse_internal_value;
    return (PLMN_IdentityInfo::cellReservedForOperatorUse_Enum)0;
}

int PLMN_IdentityInfo::cellReservedForOperatorUse_SetValue(cellReservedForOperatorUse_Enum value)
{
    cellReservedForOperatorUse_internal_value = value;
    cellReservedForOperatorUse_present = true;
    return 0;
}

int PLMN_IdentityInfo::cellReservedForOperatorUse_SetValue(std::string value)
{
    if("reserved" == value)
    {
        cellReservedForOperatorUse_internal_value = k_cellReservedForOperatorUse_reserved;
        cellReservedForOperatorUse_present = true;
        return 0;
    }
    if("notReserved" == value)
    {
        cellReservedForOperatorUse_internal_value = k_cellReservedForOperatorUse_notReserved;
        cellReservedForOperatorUse_present = true;
        return 0;
    }
    return 1;
}

std::string PLMN_IdentityInfo::cellReservedForOperatorUse_ValueToString(cellReservedForOperatorUse_Enum value) const
{
    if(k_cellReservedForOperatorUse_reserved == value)
        return "reserved";
    if(k_cellReservedForOperatorUse_notReserved == value)
        return "notReserved";
    return "";
}

uint64_t PLMN_IdentityInfo::cellReservedForOperatorUse_NumberOfValues() const
{
    return 2;
}

std::string PLMN_IdentityInfo::cellReservedForOperatorUse_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cellReservedForOperatorUse = " + cellReservedForOperatorUse_ValueToString(cellReservedForOperatorUse_internal_value) + "\n";
    return out;
}

std::string PLMN_IdentityInfo::cellReservedForOperatorUse_ToStringNoNewLines() const
{
    std::string out = "cellReservedForOperatorUse=" + cellReservedForOperatorUse_ValueToString(cellReservedForOperatorUse_internal_value) + ",";
    return out;
}

int PLMN_IdentityInfo::cellReservedForOperatorUse_Clear()
{
    cellReservedForOperatorUse_present = false;
    return 0;
}

bool PLMN_IdentityInfo::cellReservedForOperatorUse_IsPresent() const
{
    return cellReservedForOperatorUse_present;
}

