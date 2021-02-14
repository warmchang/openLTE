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

#include "OtherConfig_r9.h"

#include <cmath>

int OtherConfig_r9::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator
    bits.push_back(0);

    // Optional indicators
    bits.push_back(reportProximityConfig_r9_IsPresent());

    // Fields
    if(reportProximityConfig_r9_IsPresent())
    {
        if(0 != reportProximityConfig_r9.Pack(bits))
        {
            printf("OtherConfig_r9:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int OtherConfig_r9::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int OtherConfig_r9::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("OtherConfig_r9::Unpack() index out of bounds for extension\n");
        return -1;
    }
    idx++;

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("OtherConfig_r9::Unpack() index out of bounds for optional indiator reportProximityConfig_r9\n");
        return -1;
    }
    reportProximityConfig_r9_present = bits[idx++];

    // Fields
    if(reportProximityConfig_r9_present)
    {
        if(0 != reportProximityConfig_r9.Unpack(bits, idx))
        {
            printf("OtherConfig_r9:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string OtherConfig_r9::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "OtherConfig_r9:\n";
    if(reportProximityConfig_r9_IsPresent())
        out += reportProximityConfig_r9_ToString(indent+1);
    return out;
}

std::string OtherConfig_r9::ToStringNoNewLines() const
{
    std::string out = "OtherConfig_r9:";
    if(reportProximityConfig_r9_IsPresent())
        out += reportProximityConfig_r9_ToStringNoNewLines();
    return out;
}

ReportProximityConfig_r9* OtherConfig_r9::reportProximityConfig_r9_Set()
{
    reportProximityConfig_r9_present = true;
    return &reportProximityConfig_r9;
}

int OtherConfig_r9::reportProximityConfig_r9_Set(ReportProximityConfig_r9 &value)
{
    reportProximityConfig_r9_present = true;
    reportProximityConfig_r9 = value;
    return 0;
}

const ReportProximityConfig_r9& OtherConfig_r9::reportProximityConfig_r9_Get() const
{
    return reportProximityConfig_r9;
}

std::string OtherConfig_r9::reportProximityConfig_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "reportProximityConfig_r9:\n";
    out += reportProximityConfig_r9.ToString(indent+1);
    return out;
}

std::string OtherConfig_r9::reportProximityConfig_r9_ToStringNoNewLines() const
{
    std::string out = "reportProximityConfig_r9:";
    out += reportProximityConfig_r9.ToStringNoNewLines();
    return out;
}

int OtherConfig_r9::reportProximityConfig_r9_Clear()
{
    reportProximityConfig_r9_present = false;
    return 0;
}

bool OtherConfig_r9::reportProximityConfig_r9_IsPresent() const
{
    return reportProximityConfig_r9_present;
}

