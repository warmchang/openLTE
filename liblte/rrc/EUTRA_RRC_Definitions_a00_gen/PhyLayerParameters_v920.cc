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

#include "PhyLayerParameters_v920.h"

#include <cmath>

int PhyLayerParameters_v920::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(enhancedDualLayerFDD_r9_IsPresent());
    bits.push_back(enhancedDualLayerTDD_r9_IsPresent());

    // Fields
    if(enhancedDualLayerFDD_r9_IsPresent())
    {
        if(0 != enhancedDualLayerFDD_r9_Pack(bits))
        {
            printf("PhyLayerParameters_v920:: field pack failure\n");
            return -1;
        }
    }
    if(enhancedDualLayerTDD_r9_IsPresent())
    {
        if(0 != enhancedDualLayerTDD_r9_Pack(bits))
        {
            printf("PhyLayerParameters_v920:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int PhyLayerParameters_v920::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int PhyLayerParameters_v920::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("PhyLayerParameters_v920::Unpack() index out of bounds for optional indiator enhancedDualLayerFDD_r9\n");
        return -1;
    }
    enhancedDualLayerFDD_r9_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("PhyLayerParameters_v920::Unpack() index out of bounds for optional indiator enhancedDualLayerTDD_r9\n");
        return -1;
    }
    enhancedDualLayerTDD_r9_present = bits[idx++];

    // Fields
    if(enhancedDualLayerFDD_r9_present)
    {
        if(0 != enhancedDualLayerFDD_r9_Unpack(bits, idx))
        {
            printf("PhyLayerParameters_v920:: field unpack failure\n");
            return -1;
        }
    }
    if(enhancedDualLayerTDD_r9_present)
    {
        if(0 != enhancedDualLayerTDD_r9_Unpack(bits, idx))
        {
            printf("PhyLayerParameters_v920:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string PhyLayerParameters_v920::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "PhyLayerParameters_v920:\n";
    if(enhancedDualLayerFDD_r9_IsPresent())
        out += enhancedDualLayerFDD_r9_ToString(indent+1);
    if(enhancedDualLayerTDD_r9_IsPresent())
        out += enhancedDualLayerTDD_r9_ToString(indent+1);
    return out;
}

std::string PhyLayerParameters_v920::ToStringNoNewLines() const
{
    std::string out = "PhyLayerParameters_v920:";
    if(enhancedDualLayerFDD_r9_IsPresent())
        out += enhancedDualLayerFDD_r9_ToStringNoNewLines();
    if(enhancedDualLayerTDD_r9_IsPresent())
        out += enhancedDualLayerTDD_r9_ToStringNoNewLines();
    return out;
}

int PhyLayerParameters_v920::enhancedDualLayerFDD_r9_Pack(std::vector<uint8_t> &bits)
{
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((enhancedDualLayerFDD_r9_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int PhyLayerParameters_v920::enhancedDualLayerFDD_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return enhancedDualLayerFDD_r9_Unpack(bits, idx);
}

int PhyLayerParameters_v920::enhancedDualLayerFDD_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("PhyLayerParameters_v920::enhancedDualLayerFDD_r9_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 0)
    {
        printf("PhyLayerParameters_v920::enhancedDualLayerFDD_r9_Unpack() max failure\n");
        return -1;
    }
    enhancedDualLayerFDD_r9_internal_value = (enhancedDualLayerFDD_r9_Enum)packed_val;
    enhancedDualLayerFDD_r9_present = true;
    return 0;
}

PhyLayerParameters_v920::enhancedDualLayerFDD_r9_Enum PhyLayerParameters_v920::enhancedDualLayerFDD_r9_Value() const
{
    if(enhancedDualLayerFDD_r9_present)
        return enhancedDualLayerFDD_r9_internal_value;
    return (PhyLayerParameters_v920::enhancedDualLayerFDD_r9_Enum)0;
}

int PhyLayerParameters_v920::enhancedDualLayerFDD_r9_SetValue(enhancedDualLayerFDD_r9_Enum value)
{
    enhancedDualLayerFDD_r9_internal_value = value;
    enhancedDualLayerFDD_r9_present = true;
    return 0;
}

int PhyLayerParameters_v920::enhancedDualLayerFDD_r9_SetValue(std::string value)
{
    if("supported" == value)
    {
        enhancedDualLayerFDD_r9_internal_value = k_enhancedDualLayerFDD_r9_supported;
        enhancedDualLayerFDD_r9_present = true;
        return 0;
    }
    return 1;
}

std::string PhyLayerParameters_v920::enhancedDualLayerFDD_r9_ValueToString(enhancedDualLayerFDD_r9_Enum value) const
{
    if(k_enhancedDualLayerFDD_r9_supported == value)
        return "supported";
    return "";
}

uint64_t PhyLayerParameters_v920::enhancedDualLayerFDD_r9_NumberOfValues() const
{
    return 1;
}

std::string PhyLayerParameters_v920::enhancedDualLayerFDD_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "enhancedDualLayerFDD_r9 = " + enhancedDualLayerFDD_r9_ValueToString(enhancedDualLayerFDD_r9_internal_value) + "\n";
    return out;
}

std::string PhyLayerParameters_v920::enhancedDualLayerFDD_r9_ToStringNoNewLines() const
{
    std::string out = "enhancedDualLayerFDD_r9=" + enhancedDualLayerFDD_r9_ValueToString(enhancedDualLayerFDD_r9_internal_value) + ",";
    return out;
}

int PhyLayerParameters_v920::enhancedDualLayerFDD_r9_Clear()
{
    enhancedDualLayerFDD_r9_present = false;
    return 0;
}

bool PhyLayerParameters_v920::enhancedDualLayerFDD_r9_IsPresent() const
{
    return enhancedDualLayerFDD_r9_present;
}

int PhyLayerParameters_v920::enhancedDualLayerTDD_r9_Pack(std::vector<uint8_t> &bits)
{
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((enhancedDualLayerTDD_r9_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int PhyLayerParameters_v920::enhancedDualLayerTDD_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return enhancedDualLayerTDD_r9_Unpack(bits, idx);
}

int PhyLayerParameters_v920::enhancedDualLayerTDD_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("PhyLayerParameters_v920::enhancedDualLayerTDD_r9_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 0)
    {
        printf("PhyLayerParameters_v920::enhancedDualLayerTDD_r9_Unpack() max failure\n");
        return -1;
    }
    enhancedDualLayerTDD_r9_internal_value = (enhancedDualLayerTDD_r9_Enum)packed_val;
    enhancedDualLayerTDD_r9_present = true;
    return 0;
}

PhyLayerParameters_v920::enhancedDualLayerTDD_r9_Enum PhyLayerParameters_v920::enhancedDualLayerTDD_r9_Value() const
{
    if(enhancedDualLayerTDD_r9_present)
        return enhancedDualLayerTDD_r9_internal_value;
    return (PhyLayerParameters_v920::enhancedDualLayerTDD_r9_Enum)0;
}

int PhyLayerParameters_v920::enhancedDualLayerTDD_r9_SetValue(enhancedDualLayerTDD_r9_Enum value)
{
    enhancedDualLayerTDD_r9_internal_value = value;
    enhancedDualLayerTDD_r9_present = true;
    return 0;
}

int PhyLayerParameters_v920::enhancedDualLayerTDD_r9_SetValue(std::string value)
{
    if("supported" == value)
    {
        enhancedDualLayerTDD_r9_internal_value = k_enhancedDualLayerTDD_r9_supported;
        enhancedDualLayerTDD_r9_present = true;
        return 0;
    }
    return 1;
}

std::string PhyLayerParameters_v920::enhancedDualLayerTDD_r9_ValueToString(enhancedDualLayerTDD_r9_Enum value) const
{
    if(k_enhancedDualLayerTDD_r9_supported == value)
        return "supported";
    return "";
}

uint64_t PhyLayerParameters_v920::enhancedDualLayerTDD_r9_NumberOfValues() const
{
    return 1;
}

std::string PhyLayerParameters_v920::enhancedDualLayerTDD_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "enhancedDualLayerTDD_r9 = " + enhancedDualLayerTDD_r9_ValueToString(enhancedDualLayerTDD_r9_internal_value) + "\n";
    return out;
}

std::string PhyLayerParameters_v920::enhancedDualLayerTDD_r9_ToStringNoNewLines() const
{
    std::string out = "enhancedDualLayerTDD_r9=" + enhancedDualLayerTDD_r9_ValueToString(enhancedDualLayerTDD_r9_internal_value) + ",";
    return out;
}

int PhyLayerParameters_v920::enhancedDualLayerTDD_r9_Clear()
{
    enhancedDualLayerTDD_r9_present = false;
    return 0;
}

bool PhyLayerParameters_v920::enhancedDualLayerTDD_r9_IsPresent() const
{
    return enhancedDualLayerTDD_r9_present;
}

