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

#include "InterFreqBandInfo.h"

#include <cmath>

int InterFreqBandInfo::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != interFreqNeedForGaps_Pack(bits))
        {
            printf("InterFreqBandInfo:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int InterFreqBandInfo::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int InterFreqBandInfo::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != interFreqNeedForGaps_Unpack(bits, idx))
        {
            printf("InterFreqBandInfo:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string InterFreqBandInfo::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "InterFreqBandInfo:\n";
    out += interFreqNeedForGaps_ToString(indent+1);
    return out;
}

std::string InterFreqBandInfo::ToStringNoNewLines() const
{
    std::string out = "InterFreqBandInfo:";
    out += interFreqNeedForGaps_ToStringNoNewLines();
    return out;
}

int InterFreqBandInfo::interFreqNeedForGaps_Pack(std::vector<uint8_t> &bits)
{
    if(!interFreqNeedForGaps_present)
    {
        printf("InterFreqBandInfo::interFreqNeedForGaps_Pack() presence failure\n");
        return -1;
    }
    bits.push_back(interFreqNeedForGaps_internal_value);
    return 0;
}

int InterFreqBandInfo::interFreqNeedForGaps_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return interFreqNeedForGaps_Unpack(bits, idx);
}

int InterFreqBandInfo::interFreqNeedForGaps_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    if((idx + 1) > bits.size())
    {
        printf("InterFreqBandInfo::interFreqNeedForGaps_Unpack() index out of bounds\n");
        return -1;
    }
    interFreqNeedForGaps_internal_value = bits[idx++];
    interFreqNeedForGaps_present = true;
    return 0;
}

bool InterFreqBandInfo::interFreqNeedForGaps_Value() const
{
    if(interFreqNeedForGaps_present)
        return interFreqNeedForGaps_internal_value;
    return false;
}

int InterFreqBandInfo::interFreqNeedForGaps_SetValue(bool value)
{
    interFreqNeedForGaps_internal_value = value;
    interFreqNeedForGaps_present = true;
    return 0;
}

std::string InterFreqBandInfo::interFreqNeedForGaps_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "interFreqNeedForGaps = " + std::to_string(interFreqNeedForGaps_internal_value) + "\n";
    return out;
}

std::string InterFreqBandInfo::interFreqNeedForGaps_ToStringNoNewLines() const
{
    std::string out = "interFreqNeedForGaps=" + std::to_string(interFreqNeedForGaps_internal_value) + ",";
    return out;
}

int InterFreqBandInfo::interFreqNeedForGaps_Clear()
{
    interFreqNeedForGaps_present = false;
    return 0;
}

bool InterFreqBandInfo::interFreqNeedForGaps_IsPresent() const
{
    return interFreqNeedForGaps_present;
}

