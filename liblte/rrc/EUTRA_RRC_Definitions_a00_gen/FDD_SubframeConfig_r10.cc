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

#include "FDD_SubframeConfig_r10.h"

#include <cmath>

int FDD_SubframeConfig_r10::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != subframeConfigurationPatternFDD_r10_Pack(bits))
        {
            printf("FDD_SubframeConfig_r10:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int FDD_SubframeConfig_r10::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int FDD_SubframeConfig_r10::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != subframeConfigurationPatternFDD_r10_Unpack(bits, idx))
        {
            printf("FDD_SubframeConfig_r10:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string FDD_SubframeConfig_r10::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "FDD_SubframeConfig_r10:\n";
    out += subframeConfigurationPatternFDD_r10_ToString(indent+1);
    return out;
}

std::string FDD_SubframeConfig_r10::ToStringNoNewLines() const
{
    std::string out = "FDD_SubframeConfig_r10:";
    out += subframeConfigurationPatternFDD_r10_ToStringNoNewLines();
    return out;
}

int FDD_SubframeConfig_r10::subframeConfigurationPatternFDD_r10_Pack(std::vector<uint8_t> &bits)
{
    if(!subframeConfigurationPatternFDD_r10_present)
    {
        printf("FDD_SubframeConfig_r10::subframeConfigurationPatternFDD_r10_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 8;
    if(size < 8 || size > 8)
    {
        printf("FDD_SubframeConfig_r10::subframeConfigurationPatternFDD_r10_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((subframeConfigurationPatternFDD_r10_internal_value >> (8-i-1)) & 1);
    return 0;
}

int FDD_SubframeConfig_r10::subframeConfigurationPatternFDD_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return subframeConfigurationPatternFDD_r10_Unpack(bits, idx);
}

int FDD_SubframeConfig_r10::subframeConfigurationPatternFDD_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 8;
    if(size < 8 || size > 8)
    {
        printf("FDD_SubframeConfig_r10::subframeConfigurationPatternFDD_r10_Unpack() size failure\n");
        return -1;
    }
    subframeConfigurationPatternFDD_r10_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("FDD_SubframeConfig_r10::subframeConfigurationPatternFDD_r10_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        subframeConfigurationPatternFDD_r10_internal_value |= (uint8_t)bits[idx++] << (uint8_t)(8-i-1);
    subframeConfigurationPatternFDD_r10_present = true;
    return 0;
}

uint8_t FDD_SubframeConfig_r10::subframeConfigurationPatternFDD_r10_Value() const
{
    if(subframeConfigurationPatternFDD_r10_present)
        return subframeConfigurationPatternFDD_r10_internal_value;
    uint8_t tmp = 0;
    return tmp;
}

int FDD_SubframeConfig_r10::subframeConfigurationPatternFDD_r10_SetValue(uint8_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 8)
    {
        printf("FDD_SubframeConfig_r10::subframeConfigurationPatternFDD_r10_SetValue() size failure\n");
        return -1;
    }
    subframeConfigurationPatternFDD_r10_internal_value = value;
    subframeConfigurationPatternFDD_r10_present = true;
    return 0;
}

std::string FDD_SubframeConfig_r10::subframeConfigurationPatternFDD_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "subframeConfigurationPatternFDD_r10 = ";
    out += std::to_string(subframeConfigurationPatternFDD_r10_internal_value);
    out += "\n";
    return out;
}

std::string FDD_SubframeConfig_r10::subframeConfigurationPatternFDD_r10_ToStringNoNewLines() const
{
    std::string out = "subframeConfigurationPatternFDD_r10=";
    out += std::to_string(subframeConfigurationPatternFDD_r10_internal_value);
    out += ",";
    return out;
}

int FDD_SubframeConfig_r10::subframeConfigurationPatternFDD_r10_Clear()
{
    subframeConfigurationPatternFDD_r10_present = false;
    return 0;
}

bool FDD_SubframeConfig_r10::subframeConfigurationPatternFDD_r10_IsPresent() const
{
    return subframeConfigurationPatternFDD_r10_present;
}

