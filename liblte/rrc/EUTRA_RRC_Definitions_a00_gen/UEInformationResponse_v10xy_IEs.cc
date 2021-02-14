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

#include "UEInformationResponse_v10xy_IEs.h"

#include <cmath>

int UEInformationResponse_v10xy_IEs::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(logMeasReport_r10_IsPresent());
    bits.push_back(0);

    // Fields
    if(logMeasReport_r10_IsPresent())
    {
        if(0 != logMeasReport_r10.Pack(bits))
        {
            printf("UEInformationResponse_v10xy_IEs:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int UEInformationResponse_v10xy_IEs::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int UEInformationResponse_v10xy_IEs::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("UEInformationResponse_v10xy_IEs::Unpack() index out of bounds for optional indiator logMeasReport_r10\n");
        return -1;
    }
    logMeasReport_r10_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("UEInformationResponse_v10xy_IEs::Unpack() index out of bounds for optional indiator nonCriticalExtension\n");
        return -1;
    }
    idx++;

    // Fields
    if(logMeasReport_r10_present)
    {
        if(0 != logMeasReport_r10.Unpack(bits, idx))
        {
            printf("UEInformationResponse_v10xy_IEs:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string UEInformationResponse_v10xy_IEs::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "UEInformationResponse_v10xy_IEs:\n";
    if(logMeasReport_r10_IsPresent())
        out += logMeasReport_r10_ToString(indent+1);
    return out;
}

std::string UEInformationResponse_v10xy_IEs::ToStringNoNewLines() const
{
    std::string out = "UEInformationResponse_v10xy_IEs:";
    if(logMeasReport_r10_IsPresent())
        out += logMeasReport_r10_ToStringNoNewLines();
    return out;
}

LogMeasReport_r10* UEInformationResponse_v10xy_IEs::logMeasReport_r10_Set()
{
    logMeasReport_r10_present = true;
    return &logMeasReport_r10;
}

int UEInformationResponse_v10xy_IEs::logMeasReport_r10_Set(LogMeasReport_r10 &value)
{
    logMeasReport_r10_present = true;
    logMeasReport_r10 = value;
    return 0;
}

const LogMeasReport_r10& UEInformationResponse_v10xy_IEs::logMeasReport_r10_Get() const
{
    return logMeasReport_r10;
}

std::string UEInformationResponse_v10xy_IEs::logMeasReport_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "logMeasReport_r10:\n";
    out += logMeasReport_r10.ToString(indent+1);
    return out;
}

std::string UEInformationResponse_v10xy_IEs::logMeasReport_r10_ToStringNoNewLines() const
{
    std::string out = "logMeasReport_r10:";
    out += logMeasReport_r10.ToStringNoNewLines();
    return out;
}

int UEInformationResponse_v10xy_IEs::logMeasReport_r10_Clear()
{
    logMeasReport_r10_present = false;
    return 0;
}

bool UEInformationResponse_v10xy_IEs::logMeasReport_r10_IsPresent() const
{
    return logMeasReport_r10_present;
}

