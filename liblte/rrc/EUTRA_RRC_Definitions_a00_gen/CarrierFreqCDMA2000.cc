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

#include "CarrierFreqCDMA2000.h"

#include <cmath>

int CarrierFreqCDMA2000::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != bandClass.Pack(bits))
        {
            printf("CarrierFreqCDMA2000:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != arfcn.Pack(bits))
        {
            printf("CarrierFreqCDMA2000:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int CarrierFreqCDMA2000::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int CarrierFreqCDMA2000::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != bandClass.Unpack(bits, idx))
        {
            printf("CarrierFreqCDMA2000:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != arfcn.Unpack(bits, idx))
        {
            printf("CarrierFreqCDMA2000:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string CarrierFreqCDMA2000::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "CarrierFreqCDMA2000:\n";
    out += bandClass_ToString(indent+1);
    out += arfcn_ToString(indent+1);
    return out;
}

std::string CarrierFreqCDMA2000::ToStringNoNewLines() const
{
    std::string out = "CarrierFreqCDMA2000:";
    out += bandClass_ToStringNoNewLines();
    out += arfcn_ToStringNoNewLines();
    return out;
}

BandclassCDMA2000* CarrierFreqCDMA2000::bandClass_Set()
{
    bandClass_present = true;
    return &bandClass;
}

int CarrierFreqCDMA2000::bandClass_Set(BandclassCDMA2000 &value)
{
    bandClass_present = true;
    bandClass = value;
    return 0;
}

const BandclassCDMA2000& CarrierFreqCDMA2000::bandClass_Get() const
{
    return bandClass;
}

std::string CarrierFreqCDMA2000::bandClass_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "bandClass:\n";
    out += bandClass.ToString(indent+1);
    return out;
}

std::string CarrierFreqCDMA2000::bandClass_ToStringNoNewLines() const
{
    std::string out = "bandClass:";
    out += bandClass.ToStringNoNewLines();
    return out;
}

int CarrierFreqCDMA2000::bandClass_Clear()
{
    bandClass_present = false;
    return 0;
}

bool CarrierFreqCDMA2000::bandClass_IsPresent() const
{
    return bandClass_present;
}

ARFCN_ValueCDMA2000* CarrierFreqCDMA2000::arfcn_Set()
{
    arfcn_present = true;
    return &arfcn;
}

int CarrierFreqCDMA2000::arfcn_Set(ARFCN_ValueCDMA2000 &value)
{
    arfcn_present = true;
    arfcn = value;
    return 0;
}

const ARFCN_ValueCDMA2000& CarrierFreqCDMA2000::arfcn_Get() const
{
    return arfcn;
}

std::string CarrierFreqCDMA2000::arfcn_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "arfcn:\n";
    out += arfcn.ToString(indent+1);
    return out;
}

std::string CarrierFreqCDMA2000::arfcn_ToStringNoNewLines() const
{
    std::string out = "arfcn:";
    out += arfcn.ToStringNoNewLines();
    return out;
}

int CarrierFreqCDMA2000::arfcn_Clear()
{
    arfcn_present = false;
    return 0;
}

bool CarrierFreqCDMA2000::arfcn_IsPresent() const
{
    return arfcn_present;
}

