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

#include "CounterCheckResponse_r8_IEs.h"

#include <cmath>

int CounterCheckResponse_r8_IEs::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(nonCriticalExtension_IsPresent());

    // Fields
    {
        if(0 != drb_CountInfoList.Pack(bits))
        {
            printf("CounterCheckResponse_r8_IEs:: field pack failure\n");
            return -1;
        }
    }
    if(nonCriticalExtension_IsPresent())
    {
        if(0 != nonCriticalExtension.Pack(bits))
        {
            printf("CounterCheckResponse_r8_IEs:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int CounterCheckResponse_r8_IEs::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int CounterCheckResponse_r8_IEs::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("CounterCheckResponse_r8_IEs::Unpack() index out of bounds for optional indiator nonCriticalExtension\n");
        return -1;
    }
    nonCriticalExtension_present = bits[idx++];

    // Fields
    {
        if(0 != drb_CountInfoList.Unpack(bits, idx))
        {
            printf("CounterCheckResponse_r8_IEs:: field unpack failure\n");
            return -1;
        }
    }
    if(nonCriticalExtension_present)
    {
        if(0 != nonCriticalExtension.Unpack(bits, idx))
        {
            printf("CounterCheckResponse_r8_IEs:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string CounterCheckResponse_r8_IEs::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "CounterCheckResponse_r8_IEs:\n";
    out += drb_CountInfoList_ToString(indent+1);
    if(nonCriticalExtension_IsPresent())
        out += nonCriticalExtension_ToString(indent+1);
    return out;
}

std::string CounterCheckResponse_r8_IEs::ToStringNoNewLines() const
{
    std::string out = "CounterCheckResponse_r8_IEs:";
    out += drb_CountInfoList_ToStringNoNewLines();
    if(nonCriticalExtension_IsPresent())
        out += nonCriticalExtension_ToStringNoNewLines();
    return out;
}

DRB_CountInfoList* CounterCheckResponse_r8_IEs::drb_CountInfoList_Set()
{
    drb_CountInfoList_present = true;
    return &drb_CountInfoList;
}

int CounterCheckResponse_r8_IEs::drb_CountInfoList_Set(DRB_CountInfoList &value)
{
    drb_CountInfoList_present = true;
    drb_CountInfoList = value;
    return 0;
}

const DRB_CountInfoList& CounterCheckResponse_r8_IEs::drb_CountInfoList_Get() const
{
    return drb_CountInfoList;
}

std::string CounterCheckResponse_r8_IEs::drb_CountInfoList_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "drb_CountInfoList:\n";
    out += drb_CountInfoList.ToString(indent+1);
    return out;
}

std::string CounterCheckResponse_r8_IEs::drb_CountInfoList_ToStringNoNewLines() const
{
    std::string out = "drb_CountInfoList:";
    out += drb_CountInfoList.ToStringNoNewLines();
    return out;
}

int CounterCheckResponse_r8_IEs::drb_CountInfoList_Clear()
{
    drb_CountInfoList_present = false;
    return 0;
}

bool CounterCheckResponse_r8_IEs::drb_CountInfoList_IsPresent() const
{
    return drb_CountInfoList_present;
}

CounterCheckResponse_v8a0_IEs* CounterCheckResponse_r8_IEs::nonCriticalExtension_Set()
{
    nonCriticalExtension_present = true;
    return &nonCriticalExtension;
}

int CounterCheckResponse_r8_IEs::nonCriticalExtension_Set(CounterCheckResponse_v8a0_IEs &value)
{
    nonCriticalExtension_present = true;
    nonCriticalExtension = value;
    return 0;
}

const CounterCheckResponse_v8a0_IEs& CounterCheckResponse_r8_IEs::nonCriticalExtension_Get() const
{
    return nonCriticalExtension;
}

std::string CounterCheckResponse_r8_IEs::nonCriticalExtension_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "nonCriticalExtension:\n";
    out += nonCriticalExtension.ToString(indent+1);
    return out;
}

std::string CounterCheckResponse_r8_IEs::nonCriticalExtension_ToStringNoNewLines() const
{
    std::string out = "nonCriticalExtension:";
    out += nonCriticalExtension.ToStringNoNewLines();
    return out;
}

int CounterCheckResponse_r8_IEs::nonCriticalExtension_Clear()
{
    nonCriticalExtension_present = false;
    return 0;
}

bool CounterCheckResponse_r8_IEs::nonCriticalExtension_IsPresent() const
{
    return nonCriticalExtension_present;
}

