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

#include "RadioResourceConfigDedicatedSCell_r10.h"

#include <cmath>

int RadioResourceConfigDedicatedSCell_r10::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator
    bits.push_back(0);

    // Optional indicators
    bits.push_back(physicalConfigDedicated_IsPresent());

    // Fields
    if(physicalConfigDedicated_IsPresent())
    {
        if(0 != physicalConfigDedicated.Pack(bits))
        {
            printf("RadioResourceConfigDedicatedSCell_r10:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int RadioResourceConfigDedicatedSCell_r10::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int RadioResourceConfigDedicatedSCell_r10::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("RadioResourceConfigDedicatedSCell_r10::Unpack() index out of bounds for extension\n");
        return -1;
    }
    idx++;

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("RadioResourceConfigDedicatedSCell_r10::Unpack() index out of bounds for optional indiator physicalConfigDedicated\n");
        return -1;
    }
    physicalConfigDedicated_present = bits[idx++];

    // Fields
    if(physicalConfigDedicated_present)
    {
        if(0 != physicalConfigDedicated.Unpack(bits, idx))
        {
            printf("RadioResourceConfigDedicatedSCell_r10:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string RadioResourceConfigDedicatedSCell_r10::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "RadioResourceConfigDedicatedSCell_r10:\n";
    if(physicalConfigDedicated_IsPresent())
        out += physicalConfigDedicated_ToString(indent+1);
    return out;
}

std::string RadioResourceConfigDedicatedSCell_r10::ToStringNoNewLines() const
{
    std::string out = "RadioResourceConfigDedicatedSCell_r10:";
    if(physicalConfigDedicated_IsPresent())
        out += physicalConfigDedicated_ToStringNoNewLines();
    return out;
}

PhysicalConfigDedicatedSCell_r10* RadioResourceConfigDedicatedSCell_r10::physicalConfigDedicated_Set()
{
    physicalConfigDedicated_present = true;
    return &physicalConfigDedicated;
}

int RadioResourceConfigDedicatedSCell_r10::physicalConfigDedicated_Set(PhysicalConfigDedicatedSCell_r10 &value)
{
    physicalConfigDedicated_present = true;
    physicalConfigDedicated = value;
    return 0;
}

const PhysicalConfigDedicatedSCell_r10& RadioResourceConfigDedicatedSCell_r10::physicalConfigDedicated_Get() const
{
    return physicalConfigDedicated;
}

std::string RadioResourceConfigDedicatedSCell_r10::physicalConfigDedicated_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "physicalConfigDedicated:\n";
    out += physicalConfigDedicated.ToString(indent+1);
    return out;
}

std::string RadioResourceConfigDedicatedSCell_r10::physicalConfigDedicated_ToStringNoNewLines() const
{
    std::string out = "physicalConfigDedicated:";
    out += physicalConfigDedicated.ToStringNoNewLines();
    return out;
}

int RadioResourceConfigDedicatedSCell_r10::physicalConfigDedicated_Clear()
{
    physicalConfigDedicated_present = false;
    return 0;
}

bool RadioResourceConfigDedicatedSCell_r10::physicalConfigDedicated_IsPresent() const
{
    return physicalConfigDedicated_present;
}

