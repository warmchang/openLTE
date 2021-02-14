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

#include "RLF_Report_r9.h"

#include <cmath>

int RLF_Report_r9::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator
    bits.push_back(0);

    // Optional indicators
    bits.push_back(measResultNeighCells_r9_IsPresent());

    // Fields
    {
        if(0 != measResultLastServCell_r9_value.Pack(bits))
        {
            printf("RLF_Report_r9:: field pack failure\n");
            return -1;
        }
    }
    if(measResultNeighCells_r9_IsPresent())
    {
        if(0 != measResultNeighCells_r9.Pack(bits))
        {
            printf("RLF_Report_r9:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int RLF_Report_r9::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int RLF_Report_r9::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("RLF_Report_r9::Unpack() index out of bounds for extension\n");
        return -1;
    }
    idx++;

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("RLF_Report_r9::Unpack() index out of bounds for optional indiator measResultNeighCells_r9\n");
        return -1;
    }
    measResultNeighCells_r9_present = bits[idx++];

    // Fields
    {
        if(0 != measResultLastServCell_r9_value.Unpack(bits, idx))
        {
            printf("RLF_Report_r9:: field unpack failure\n");
            return -1;
        }
    }
    if(measResultNeighCells_r9_present)
    {
        if(0 != measResultNeighCells_r9.Unpack(bits, idx))
        {
            printf("RLF_Report_r9:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string RLF_Report_r9::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "RLF_Report_r9:\n";
    out += measResultLastServCell_r9_value.ToString(indent+1);
    if(measResultNeighCells_r9_IsPresent())
        out += measResultNeighCells_r9_ToString(indent+1);
    return out;
}

std::string RLF_Report_r9::ToStringNoNewLines() const
{
    std::string out = "RLF_Report_r9:";
    out += measResultLastServCell_r9_value.ToStringNoNewLines();
    if(measResultNeighCells_r9_IsPresent())
        out += measResultNeighCells_r9_ToStringNoNewLines();
    return out;
}

int RLF_Report_r9::measResultLastServCell_r9::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(rsrqResult_r9_IsPresent());

    // Fields
    {
        if(0 != rsrpResult_r9.Pack(bits))
        {
            printf("RLF_Report_r9::measResultLastServCell_r9:: field pack failure\n");
            return -1;
        }
    }
    if(rsrqResult_r9_IsPresent())
    {
        if(0 != rsrqResult_r9.Pack(bits))
        {
            printf("RLF_Report_r9::measResultLastServCell_r9:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int RLF_Report_r9::measResultLastServCell_r9::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int RLF_Report_r9::measResultLastServCell_r9::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("measResultLastServCell_r9::Unpack() index out of bounds for optional indiator rsrqResult_r9\n");
        return -1;
    }
    rsrqResult_r9_present = bits[idx++];

    // Fields
    {
        if(0 != rsrpResult_r9.Unpack(bits, idx))
        {
            printf("RLF_Report_r9::measResultLastServCell_r9:: field unpack failure\n");
            return -1;
        }
    }
    if(rsrqResult_r9_present)
    {
        if(0 != rsrqResult_r9.Unpack(bits, idx))
        {
            printf("RLF_Report_r9::measResultLastServCell_r9:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string RLF_Report_r9::measResultLastServCell_r9::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "measResultLastServCell_r9:\n";
    out += rsrpResult_r9_ToString(indent+1);
    if(rsrqResult_r9_IsPresent())
        out += rsrqResult_r9_ToString(indent+1);
    return out;
}

std::string RLF_Report_r9::measResultLastServCell_r9::ToStringNoNewLines() const
{
    std::string out = "measResultLastServCell_r9:";
    out += rsrpResult_r9_ToStringNoNewLines();
    if(rsrqResult_r9_IsPresent())
        out += rsrqResult_r9_ToStringNoNewLines();
    return out;
}

RSRP_Range* RLF_Report_r9::measResultLastServCell_r9::rsrpResult_r9_Set()
{
    rsrpResult_r9_present = true;
    return &rsrpResult_r9;
}

int RLF_Report_r9::measResultLastServCell_r9::rsrpResult_r9_Set(RSRP_Range &value)
{
    rsrpResult_r9_present = true;
    rsrpResult_r9 = value;
    return 0;
}

const RSRP_Range& RLF_Report_r9::measResultLastServCell_r9::rsrpResult_r9_Get() const
{
    return rsrpResult_r9;
}

std::string RLF_Report_r9::measResultLastServCell_r9::rsrpResult_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "rsrpResult_r9:\n";
    out += rsrpResult_r9.ToString(indent+1);
    return out;
}

std::string RLF_Report_r9::measResultLastServCell_r9::rsrpResult_r9_ToStringNoNewLines() const
{
    std::string out = "rsrpResult_r9:";
    out += rsrpResult_r9.ToStringNoNewLines();
    return out;
}

int RLF_Report_r9::measResultLastServCell_r9::rsrpResult_r9_Clear()
{
    rsrpResult_r9_present = false;
    return 0;
}

bool RLF_Report_r9::measResultLastServCell_r9::rsrpResult_r9_IsPresent() const
{
    return rsrpResult_r9_present;
}

RSRQ_Range* RLF_Report_r9::measResultLastServCell_r9::rsrqResult_r9_Set()
{
    rsrqResult_r9_present = true;
    return &rsrqResult_r9;
}

int RLF_Report_r9::measResultLastServCell_r9::rsrqResult_r9_Set(RSRQ_Range &value)
{
    rsrqResult_r9_present = true;
    rsrqResult_r9 = value;
    return 0;
}

const RSRQ_Range& RLF_Report_r9::measResultLastServCell_r9::rsrqResult_r9_Get() const
{
    return rsrqResult_r9;
}

std::string RLF_Report_r9::measResultLastServCell_r9::rsrqResult_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "rsrqResult_r9:\n";
    out += rsrqResult_r9.ToString(indent+1);
    return out;
}

std::string RLF_Report_r9::measResultLastServCell_r9::rsrqResult_r9_ToStringNoNewLines() const
{
    std::string out = "rsrqResult_r9:";
    out += rsrqResult_r9.ToStringNoNewLines();
    return out;
}

int RLF_Report_r9::measResultLastServCell_r9::rsrqResult_r9_Clear()
{
    rsrqResult_r9_present = false;
    return 0;
}

bool RLF_Report_r9::measResultLastServCell_r9::rsrqResult_r9_IsPresent() const
{
    return rsrqResult_r9_present;
}

MeasResultNeighCells* RLF_Report_r9::measResultNeighCells_r9_Set()
{
    measResultNeighCells_r9_present = true;
    return &measResultNeighCells_r9;
}

int RLF_Report_r9::measResultNeighCells_r9_Set(MeasResultNeighCells &value)
{
    measResultNeighCells_r9_present = true;
    measResultNeighCells_r9 = value;
    return 0;
}

const MeasResultNeighCells& RLF_Report_r9::measResultNeighCells_r9_Get() const
{
    return measResultNeighCells_r9;
}

std::string RLF_Report_r9::measResultNeighCells_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "measResultNeighCells_r9:\n";
    out += measResultNeighCells_r9.ToString(indent+1);
    return out;
}

std::string RLF_Report_r9::measResultNeighCells_r9_ToStringNoNewLines() const
{
    std::string out = "measResultNeighCells_r9:";
    out += measResultNeighCells_r9.ToStringNoNewLines();
    return out;
}

int RLF_Report_r9::measResultNeighCells_r9_Clear()
{
    measResultNeighCells_r9_present = false;
    return 0;
}

bool RLF_Report_r9::measResultNeighCells_r9_IsPresent() const
{
    return measResultNeighCells_r9_present;
}

