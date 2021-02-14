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

#include "BandInfoEUTRA.h"

#include <cmath>

int BandInfoEUTRA::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(interRAT_BandList_IsPresent());

    // Fields
    {
        if(0 != interFreqBandList.Pack(bits))
        {
            printf("BandInfoEUTRA:: field pack failure\n");
            return -1;
        }
    }
    if(interRAT_BandList_IsPresent())
    {
        if(0 != interRAT_BandList.Pack(bits))
        {
            printf("BandInfoEUTRA:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int BandInfoEUTRA::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int BandInfoEUTRA::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("BandInfoEUTRA::Unpack() index out of bounds for optional indiator interRAT_BandList\n");
        return -1;
    }
    interRAT_BandList_present = bits[idx++];

    // Fields
    {
        if(0 != interFreqBandList.Unpack(bits, idx))
        {
            printf("BandInfoEUTRA:: field unpack failure\n");
            return -1;
        }
    }
    if(interRAT_BandList_present)
    {
        if(0 != interRAT_BandList.Unpack(bits, idx))
        {
            printf("BandInfoEUTRA:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string BandInfoEUTRA::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "BandInfoEUTRA:\n";
    out += interFreqBandList_ToString(indent+1);
    if(interRAT_BandList_IsPresent())
        out += interRAT_BandList_ToString(indent+1);
    return out;
}

std::string BandInfoEUTRA::ToStringNoNewLines() const
{
    std::string out = "BandInfoEUTRA:";
    out += interFreqBandList_ToStringNoNewLines();
    if(interRAT_BandList_IsPresent())
        out += interRAT_BandList_ToStringNoNewLines();
    return out;
}

InterFreqBandList* BandInfoEUTRA::interFreqBandList_Set()
{
    interFreqBandList_present = true;
    return &interFreqBandList;
}

int BandInfoEUTRA::interFreqBandList_Set(InterFreqBandList &value)
{
    interFreqBandList_present = true;
    interFreqBandList = value;
    return 0;
}

const InterFreqBandList& BandInfoEUTRA::interFreqBandList_Get() const
{
    return interFreqBandList;
}

std::string BandInfoEUTRA::interFreqBandList_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "interFreqBandList:\n";
    out += interFreqBandList.ToString(indent+1);
    return out;
}

std::string BandInfoEUTRA::interFreqBandList_ToStringNoNewLines() const
{
    std::string out = "interFreqBandList:";
    out += interFreqBandList.ToStringNoNewLines();
    return out;
}

int BandInfoEUTRA::interFreqBandList_Clear()
{
    interFreqBandList_present = false;
    return 0;
}

bool BandInfoEUTRA::interFreqBandList_IsPresent() const
{
    return interFreqBandList_present;
}

InterRAT_BandList* BandInfoEUTRA::interRAT_BandList_Set()
{
    interRAT_BandList_present = true;
    return &interRAT_BandList;
}

int BandInfoEUTRA::interRAT_BandList_Set(InterRAT_BandList &value)
{
    interRAT_BandList_present = true;
    interRAT_BandList = value;
    return 0;
}

const InterRAT_BandList& BandInfoEUTRA::interRAT_BandList_Get() const
{
    return interRAT_BandList;
}

std::string BandInfoEUTRA::interRAT_BandList_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "interRAT_BandList:\n";
    out += interRAT_BandList.ToString(indent+1);
    return out;
}

std::string BandInfoEUTRA::interRAT_BandList_ToStringNoNewLines() const
{
    std::string out = "interRAT_BandList:";
    out += interRAT_BandList.ToStringNoNewLines();
    return out;
}

int BandInfoEUTRA::interRAT_BandList_Clear()
{
    interRAT_BandList_present = false;
    return 0;
}

bool BandInfoEUTRA::interRAT_BandList_IsPresent() const
{
    return interRAT_BandList_present;
}

