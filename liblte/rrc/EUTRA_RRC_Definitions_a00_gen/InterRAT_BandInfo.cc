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

#include "InterRAT_BandInfo.h"

#include <cmath>

int InterRAT_BandInfo::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != interRAT_NeedForGaps_Pack(bits))
        {
            printf("InterRAT_BandInfo:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int InterRAT_BandInfo::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int InterRAT_BandInfo::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != interRAT_NeedForGaps_Unpack(bits, idx))
        {
            printf("InterRAT_BandInfo:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string InterRAT_BandInfo::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "InterRAT_BandInfo:\n";
    out += interRAT_NeedForGaps_ToString(indent+1);
    return out;
}

std::string InterRAT_BandInfo::ToStringNoNewLines() const
{
    std::string out = "InterRAT_BandInfo:";
    out += interRAT_NeedForGaps_ToStringNoNewLines();
    return out;
}

int InterRAT_BandInfo::interRAT_NeedForGaps_Pack(std::vector<uint8_t> &bits)
{
    if(!interRAT_NeedForGaps_present)
    {
        printf("InterRAT_BandInfo::interRAT_NeedForGaps_Pack() presence failure\n");
        return -1;
    }
    bits.push_back(interRAT_NeedForGaps_internal_value);
    return 0;
}

int InterRAT_BandInfo::interRAT_NeedForGaps_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return interRAT_NeedForGaps_Unpack(bits, idx);
}

int InterRAT_BandInfo::interRAT_NeedForGaps_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    if((idx + 1) > bits.size())
    {
        printf("InterRAT_BandInfo::interRAT_NeedForGaps_Unpack() index out of bounds\n");
        return -1;
    }
    interRAT_NeedForGaps_internal_value = bits[idx++];
    interRAT_NeedForGaps_present = true;
    return 0;
}

bool InterRAT_BandInfo::interRAT_NeedForGaps_Value() const
{
    if(interRAT_NeedForGaps_present)
        return interRAT_NeedForGaps_internal_value;
    return false;
}

int InterRAT_BandInfo::interRAT_NeedForGaps_SetValue(bool value)
{
    interRAT_NeedForGaps_internal_value = value;
    interRAT_NeedForGaps_present = true;
    return 0;
}

std::string InterRAT_BandInfo::interRAT_NeedForGaps_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "interRAT_NeedForGaps = " + std::to_string(interRAT_NeedForGaps_internal_value) + "\n";
    return out;
}

std::string InterRAT_BandInfo::interRAT_NeedForGaps_ToStringNoNewLines() const
{
    std::string out = "interRAT_NeedForGaps=" + std::to_string(interRAT_NeedForGaps_internal_value) + ",";
    return out;
}

int InterRAT_BandInfo::interRAT_NeedForGaps_Clear()
{
    interRAT_NeedForGaps_present = false;
    return 0;
}

bool InterRAT_BandInfo::interRAT_NeedForGaps_IsPresent() const
{
    return interRAT_NeedForGaps_present;
}

