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

#include "FreqsPriorityGERAN.h"

#include <cmath>

int FreqsPriorityGERAN::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != carrierFreqs.Pack(bits))
        {
            printf("FreqsPriorityGERAN:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != cellReselectionPriority.Pack(bits))
        {
            printf("FreqsPriorityGERAN:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int FreqsPriorityGERAN::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int FreqsPriorityGERAN::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != carrierFreqs.Unpack(bits, idx))
        {
            printf("FreqsPriorityGERAN:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != cellReselectionPriority.Unpack(bits, idx))
        {
            printf("FreqsPriorityGERAN:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string FreqsPriorityGERAN::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "FreqsPriorityGERAN:\n";
    out += carrierFreqs_ToString(indent+1);
    out += cellReselectionPriority_ToString(indent+1);
    return out;
}

std::string FreqsPriorityGERAN::ToStringNoNewLines() const
{
    std::string out = "FreqsPriorityGERAN:";
    out += carrierFreqs_ToStringNoNewLines();
    out += cellReselectionPriority_ToStringNoNewLines();
    return out;
}

CarrierFreqsGERAN* FreqsPriorityGERAN::carrierFreqs_Set()
{
    carrierFreqs_present = true;
    return &carrierFreqs;
}

int FreqsPriorityGERAN::carrierFreqs_Set(CarrierFreqsGERAN &value)
{
    carrierFreqs_present = true;
    carrierFreqs = value;
    return 0;
}

const CarrierFreqsGERAN& FreqsPriorityGERAN::carrierFreqs_Get() const
{
    return carrierFreqs;
}

std::string FreqsPriorityGERAN::carrierFreqs_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "carrierFreqs:\n";
    out += carrierFreqs.ToString(indent+1);
    return out;
}

std::string FreqsPriorityGERAN::carrierFreqs_ToStringNoNewLines() const
{
    std::string out = "carrierFreqs:";
    out += carrierFreqs.ToStringNoNewLines();
    return out;
}

int FreqsPriorityGERAN::carrierFreqs_Clear()
{
    carrierFreqs_present = false;
    return 0;
}

bool FreqsPriorityGERAN::carrierFreqs_IsPresent() const
{
    return carrierFreqs_present;
}

CellReselectionPriority* FreqsPriorityGERAN::cellReselectionPriority_Set()
{
    cellReselectionPriority_present = true;
    return &cellReselectionPriority;
}

int FreqsPriorityGERAN::cellReselectionPriority_Set(CellReselectionPriority &value)
{
    cellReselectionPriority_present = true;
    cellReselectionPriority = value;
    return 0;
}

const CellReselectionPriority& FreqsPriorityGERAN::cellReselectionPriority_Get() const
{
    return cellReselectionPriority;
}

std::string FreqsPriorityGERAN::cellReselectionPriority_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cellReselectionPriority:\n";
    out += cellReselectionPriority.ToString(indent+1);
    return out;
}

std::string FreqsPriorityGERAN::cellReselectionPriority_ToStringNoNewLines() const
{
    std::string out = "cellReselectionPriority:";
    out += cellReselectionPriority.ToStringNoNewLines();
    return out;
}

int FreqsPriorityGERAN::cellReselectionPriority_Clear()
{
    cellReselectionPriority_present = false;
    return 0;
}

bool FreqsPriorityGERAN::cellReselectionPriority_IsPresent() const
{
    return cellReselectionPriority_present;
}

