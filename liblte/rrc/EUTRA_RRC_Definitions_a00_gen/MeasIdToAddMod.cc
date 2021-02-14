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

#include "MeasIdToAddMod.h"

#include <cmath>

int MeasIdToAddMod::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != measId.Pack(bits))
        {
            printf("MeasIdToAddMod:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != measObjectId.Pack(bits))
        {
            printf("MeasIdToAddMod:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != reportConfigId.Pack(bits))
        {
            printf("MeasIdToAddMod:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int MeasIdToAddMod::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int MeasIdToAddMod::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != measId.Unpack(bits, idx))
        {
            printf("MeasIdToAddMod:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != measObjectId.Unpack(bits, idx))
        {
            printf("MeasIdToAddMod:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != reportConfigId.Unpack(bits, idx))
        {
            printf("MeasIdToAddMod:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string MeasIdToAddMod::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "MeasIdToAddMod:\n";
    out += measId_ToString(indent+1);
    out += measObjectId_ToString(indent+1);
    out += reportConfigId_ToString(indent+1);
    return out;
}

std::string MeasIdToAddMod::ToStringNoNewLines() const
{
    std::string out = "MeasIdToAddMod:";
    out += measId_ToStringNoNewLines();
    out += measObjectId_ToStringNoNewLines();
    out += reportConfigId_ToStringNoNewLines();
    return out;
}

MeasId* MeasIdToAddMod::measId_Set()
{
    measId_present = true;
    return &measId;
}

int MeasIdToAddMod::measId_Set(MeasId &value)
{
    measId_present = true;
    measId = value;
    return 0;
}

const MeasId& MeasIdToAddMod::measId_Get() const
{
    return measId;
}

std::string MeasIdToAddMod::measId_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "measId:\n";
    out += measId.ToString(indent+1);
    return out;
}

std::string MeasIdToAddMod::measId_ToStringNoNewLines() const
{
    std::string out = "measId:";
    out += measId.ToStringNoNewLines();
    return out;
}

int MeasIdToAddMod::measId_Clear()
{
    measId_present = false;
    return 0;
}

bool MeasIdToAddMod::measId_IsPresent() const
{
    return measId_present;
}

MeasObjectId* MeasIdToAddMod::measObjectId_Set()
{
    measObjectId_present = true;
    return &measObjectId;
}

int MeasIdToAddMod::measObjectId_Set(MeasObjectId &value)
{
    measObjectId_present = true;
    measObjectId = value;
    return 0;
}

const MeasObjectId& MeasIdToAddMod::measObjectId_Get() const
{
    return measObjectId;
}

std::string MeasIdToAddMod::measObjectId_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "measObjectId:\n";
    out += measObjectId.ToString(indent+1);
    return out;
}

std::string MeasIdToAddMod::measObjectId_ToStringNoNewLines() const
{
    std::string out = "measObjectId:";
    out += measObjectId.ToStringNoNewLines();
    return out;
}

int MeasIdToAddMod::measObjectId_Clear()
{
    measObjectId_present = false;
    return 0;
}

bool MeasIdToAddMod::measObjectId_IsPresent() const
{
    return measObjectId_present;
}

ReportConfigId* MeasIdToAddMod::reportConfigId_Set()
{
    reportConfigId_present = true;
    return &reportConfigId;
}

int MeasIdToAddMod::reportConfigId_Set(ReportConfigId &value)
{
    reportConfigId_present = true;
    reportConfigId = value;
    return 0;
}

const ReportConfigId& MeasIdToAddMod::reportConfigId_Get() const
{
    return reportConfigId;
}

std::string MeasIdToAddMod::reportConfigId_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "reportConfigId:\n";
    out += reportConfigId.ToString(indent+1);
    return out;
}

std::string MeasIdToAddMod::reportConfigId_ToStringNoNewLines() const
{
    std::string out = "reportConfigId:";
    out += reportConfigId.ToStringNoNewLines();
    return out;
}

int MeasIdToAddMod::reportConfigId_Clear()
{
    reportConfigId_present = false;
    return 0;
}

bool MeasIdToAddMod::reportConfigId_IsPresent() const
{
    return reportConfigId_present;
}

