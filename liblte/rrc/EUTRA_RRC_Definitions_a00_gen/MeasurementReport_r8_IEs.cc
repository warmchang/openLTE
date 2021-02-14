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

#include "MeasurementReport_r8_IEs.h"

#include <cmath>

int MeasurementReport_r8_IEs::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(nonCriticalExtension_IsPresent());

    // Fields
    {
        if(0 != measResults.Pack(bits))
        {
            printf("MeasurementReport_r8_IEs:: field pack failure\n");
            return -1;
        }
    }
    if(nonCriticalExtension_IsPresent())
    {
        if(0 != nonCriticalExtension.Pack(bits))
        {
            printf("MeasurementReport_r8_IEs:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int MeasurementReport_r8_IEs::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int MeasurementReport_r8_IEs::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("MeasurementReport_r8_IEs::Unpack() index out of bounds for optional indiator nonCriticalExtension\n");
        return -1;
    }
    nonCriticalExtension_present = bits[idx++];

    // Fields
    {
        if(0 != measResults.Unpack(bits, idx))
        {
            printf("MeasurementReport_r8_IEs:: field unpack failure\n");
            return -1;
        }
    }
    if(nonCriticalExtension_present)
    {
        if(0 != nonCriticalExtension.Unpack(bits, idx))
        {
            printf("MeasurementReport_r8_IEs:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string MeasurementReport_r8_IEs::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "MeasurementReport_r8_IEs:\n";
    out += measResults_ToString(indent+1);
    if(nonCriticalExtension_IsPresent())
        out += nonCriticalExtension_ToString(indent+1);
    return out;
}

std::string MeasurementReport_r8_IEs::ToStringNoNewLines() const
{
    std::string out = "MeasurementReport_r8_IEs:";
    out += measResults_ToStringNoNewLines();
    if(nonCriticalExtension_IsPresent())
        out += nonCriticalExtension_ToStringNoNewLines();
    return out;
}

MeasResults* MeasurementReport_r8_IEs::measResults_Set()
{
    measResults_present = true;
    return &measResults;
}

int MeasurementReport_r8_IEs::measResults_Set(MeasResults &value)
{
    measResults_present = true;
    measResults = value;
    return 0;
}

const MeasResults& MeasurementReport_r8_IEs::measResults_Get() const
{
    return measResults;
}

std::string MeasurementReport_r8_IEs::measResults_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "measResults:\n";
    out += measResults.ToString(indent+1);
    return out;
}

std::string MeasurementReport_r8_IEs::measResults_ToStringNoNewLines() const
{
    std::string out = "measResults:";
    out += measResults.ToStringNoNewLines();
    return out;
}

int MeasurementReport_r8_IEs::measResults_Clear()
{
    measResults_present = false;
    return 0;
}

bool MeasurementReport_r8_IEs::measResults_IsPresent() const
{
    return measResults_present;
}

MeasurementReport_v8a0_IEs* MeasurementReport_r8_IEs::nonCriticalExtension_Set()
{
    nonCriticalExtension_present = true;
    return &nonCriticalExtension;
}

int MeasurementReport_r8_IEs::nonCriticalExtension_Set(MeasurementReport_v8a0_IEs &value)
{
    nonCriticalExtension_present = true;
    nonCriticalExtension = value;
    return 0;
}

const MeasurementReport_v8a0_IEs& MeasurementReport_r8_IEs::nonCriticalExtension_Get() const
{
    return nonCriticalExtension;
}

std::string MeasurementReport_r8_IEs::nonCriticalExtension_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "nonCriticalExtension:\n";
    out += nonCriticalExtension.ToString(indent+1);
    return out;
}

std::string MeasurementReport_r8_IEs::nonCriticalExtension_ToStringNoNewLines() const
{
    std::string out = "nonCriticalExtension:";
    out += nonCriticalExtension.ToStringNoNewLines();
    return out;
}

int MeasurementReport_r8_IEs::nonCriticalExtension_Clear()
{
    nonCriticalExtension_present = false;
    return 0;
}

bool MeasurementReport_r8_IEs::nonCriticalExtension_IsPresent() const
{
    return nonCriticalExtension_present;
}

