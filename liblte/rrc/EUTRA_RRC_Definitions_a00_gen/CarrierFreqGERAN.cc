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

#include "CarrierFreqGERAN.h"

#include <cmath>

int CarrierFreqGERAN::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != arfcn.Pack(bits))
        {
            printf("CarrierFreqGERAN:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != bandIndicator.Pack(bits))
        {
            printf("CarrierFreqGERAN:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int CarrierFreqGERAN::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int CarrierFreqGERAN::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != arfcn.Unpack(bits, idx))
        {
            printf("CarrierFreqGERAN:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != bandIndicator.Unpack(bits, idx))
        {
            printf("CarrierFreqGERAN:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string CarrierFreqGERAN::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "CarrierFreqGERAN:\n";
    out += arfcn_ToString(indent+1);
    out += bandIndicator_ToString(indent+1);
    return out;
}

std::string CarrierFreqGERAN::ToStringNoNewLines() const
{
    std::string out = "CarrierFreqGERAN:";
    out += arfcn_ToStringNoNewLines();
    out += bandIndicator_ToStringNoNewLines();
    return out;
}

ARFCN_ValueGERAN* CarrierFreqGERAN::arfcn_Set()
{
    arfcn_present = true;
    return &arfcn;
}

int CarrierFreqGERAN::arfcn_Set(ARFCN_ValueGERAN &value)
{
    arfcn_present = true;
    arfcn = value;
    return 0;
}

const ARFCN_ValueGERAN& CarrierFreqGERAN::arfcn_Get() const
{
    return arfcn;
}

std::string CarrierFreqGERAN::arfcn_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "arfcn:\n";
    out += arfcn.ToString(indent+1);
    return out;
}

std::string CarrierFreqGERAN::arfcn_ToStringNoNewLines() const
{
    std::string out = "arfcn:";
    out += arfcn.ToStringNoNewLines();
    return out;
}

int CarrierFreqGERAN::arfcn_Clear()
{
    arfcn_present = false;
    return 0;
}

bool CarrierFreqGERAN::arfcn_IsPresent() const
{
    return arfcn_present;
}

BandIndicatorGERAN* CarrierFreqGERAN::bandIndicator_Set()
{
    bandIndicator_present = true;
    return &bandIndicator;
}

int CarrierFreqGERAN::bandIndicator_Set(BandIndicatorGERAN &value)
{
    bandIndicator_present = true;
    bandIndicator = value;
    return 0;
}

const BandIndicatorGERAN& CarrierFreqGERAN::bandIndicator_Get() const
{
    return bandIndicator;
}

std::string CarrierFreqGERAN::bandIndicator_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "bandIndicator:\n";
    out += bandIndicator.ToString(indent+1);
    return out;
}

std::string CarrierFreqGERAN::bandIndicator_ToStringNoNewLines() const
{
    std::string out = "bandIndicator:";
    out += bandIndicator.ToStringNoNewLines();
    return out;
}

int CarrierFreqGERAN::bandIndicator_Clear()
{
    bandIndicator_present = false;
    return 0;
}

bool CarrierFreqGERAN::bandIndicator_IsPresent() const
{
    return bandIndicator_present;
}

