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

#include "CarrierFreqEUTRA.h"

#include <cmath>

int CarrierFreqEUTRA::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(ul_CarrierFreq_IsPresent());

    // Fields
    {
        if(0 != dl_CarrierFreq.Pack(bits))
        {
            printf("CarrierFreqEUTRA:: field pack failure\n");
            return -1;
        }
    }
    if(ul_CarrierFreq_IsPresent())
    {
        if(0 != ul_CarrierFreq.Pack(bits))
        {
            printf("CarrierFreqEUTRA:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int CarrierFreqEUTRA::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int CarrierFreqEUTRA::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("CarrierFreqEUTRA::Unpack() index out of bounds for optional indiator ul_CarrierFreq\n");
        return -1;
    }
    ul_CarrierFreq_present = bits[idx++];

    // Fields
    {
        if(0 != dl_CarrierFreq.Unpack(bits, idx))
        {
            printf("CarrierFreqEUTRA:: field unpack failure\n");
            return -1;
        }
    }
    if(ul_CarrierFreq_present)
    {
        if(0 != ul_CarrierFreq.Unpack(bits, idx))
        {
            printf("CarrierFreqEUTRA:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string CarrierFreqEUTRA::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "CarrierFreqEUTRA:\n";
    out += dl_CarrierFreq_ToString(indent+1);
    if(ul_CarrierFreq_IsPresent())
        out += ul_CarrierFreq_ToString(indent+1);
    return out;
}

std::string CarrierFreqEUTRA::ToStringNoNewLines() const
{
    std::string out = "CarrierFreqEUTRA:";
    out += dl_CarrierFreq_ToStringNoNewLines();
    if(ul_CarrierFreq_IsPresent())
        out += ul_CarrierFreq_ToStringNoNewLines();
    return out;
}

ARFCN_ValueEUTRA* CarrierFreqEUTRA::dl_CarrierFreq_Set()
{
    dl_CarrierFreq_present = true;
    return &dl_CarrierFreq;
}

int CarrierFreqEUTRA::dl_CarrierFreq_Set(ARFCN_ValueEUTRA &value)
{
    dl_CarrierFreq_present = true;
    dl_CarrierFreq = value;
    return 0;
}

const ARFCN_ValueEUTRA& CarrierFreqEUTRA::dl_CarrierFreq_Get() const
{
    return dl_CarrierFreq;
}

std::string CarrierFreqEUTRA::dl_CarrierFreq_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "dl_CarrierFreq:\n";
    out += dl_CarrierFreq.ToString(indent+1);
    return out;
}

std::string CarrierFreqEUTRA::dl_CarrierFreq_ToStringNoNewLines() const
{
    std::string out = "dl_CarrierFreq:";
    out += dl_CarrierFreq.ToStringNoNewLines();
    return out;
}

int CarrierFreqEUTRA::dl_CarrierFreq_Clear()
{
    dl_CarrierFreq_present = false;
    return 0;
}

bool CarrierFreqEUTRA::dl_CarrierFreq_IsPresent() const
{
    return dl_CarrierFreq_present;
}

ARFCN_ValueEUTRA* CarrierFreqEUTRA::ul_CarrierFreq_Set()
{
    ul_CarrierFreq_present = true;
    return &ul_CarrierFreq;
}

int CarrierFreqEUTRA::ul_CarrierFreq_Set(ARFCN_ValueEUTRA &value)
{
    ul_CarrierFreq_present = true;
    ul_CarrierFreq = value;
    return 0;
}

const ARFCN_ValueEUTRA& CarrierFreqEUTRA::ul_CarrierFreq_Get() const
{
    return ul_CarrierFreq;
}

std::string CarrierFreqEUTRA::ul_CarrierFreq_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ul_CarrierFreq:\n";
    out += ul_CarrierFreq.ToString(indent+1);
    return out;
}

std::string CarrierFreqEUTRA::ul_CarrierFreq_ToStringNoNewLines() const
{
    std::string out = "ul_CarrierFreq:";
    out += ul_CarrierFreq.ToStringNoNewLines();
    return out;
}

int CarrierFreqEUTRA::ul_CarrierFreq_Clear()
{
    ul_CarrierFreq_present = false;
    return 0;
}

bool CarrierFreqEUTRA::ul_CarrierFreq_IsPresent() const
{
    return ul_CarrierFreq_present;
}

