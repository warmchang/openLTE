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

#include "AS_Context.h"

#include <cmath>

int AS_Context::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(reestablishmentInfo_IsPresent());

    // Fields
    if(reestablishmentInfo_IsPresent())
    {
        if(0 != reestablishmentInfo.Pack(bits))
        {
            printf("AS_Context:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int AS_Context::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int AS_Context::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("AS_Context::Unpack() index out of bounds for optional indiator reestablishmentInfo\n");
        return -1;
    }
    reestablishmentInfo_present = bits[idx++];

    // Fields
    if(reestablishmentInfo_present)
    {
        if(0 != reestablishmentInfo.Unpack(bits, idx))
        {
            printf("AS_Context:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string AS_Context::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "AS_Context:\n";
    if(reestablishmentInfo_IsPresent())
        out += reestablishmentInfo_ToString(indent+1);
    return out;
}

std::string AS_Context::ToStringNoNewLines() const
{
    std::string out = "AS_Context:";
    if(reestablishmentInfo_IsPresent())
        out += reestablishmentInfo_ToStringNoNewLines();
    return out;
}

ReestablishmentInfo* AS_Context::reestablishmentInfo_Set()
{
    reestablishmentInfo_present = true;
    return &reestablishmentInfo;
}

int AS_Context::reestablishmentInfo_Set(ReestablishmentInfo &value)
{
    reestablishmentInfo_present = true;
    reestablishmentInfo = value;
    return 0;
}

const ReestablishmentInfo& AS_Context::reestablishmentInfo_Get() const
{
    return reestablishmentInfo;
}

std::string AS_Context::reestablishmentInfo_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "reestablishmentInfo:\n";
    out += reestablishmentInfo.ToString(indent+1);
    return out;
}

std::string AS_Context::reestablishmentInfo_ToStringNoNewLines() const
{
    std::string out = "reestablishmentInfo:";
    out += reestablishmentInfo.ToStringNoNewLines();
    return out;
}

int AS_Context::reestablishmentInfo_Clear()
{
    reestablishmentInfo_present = false;
    return 0;
}

bool AS_Context::reestablishmentInfo_IsPresent() const
{
    return reestablishmentInfo_present;
}

