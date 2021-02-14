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

#include "FreqPriorityUTRA_FDD.h"

#include <cmath>

int FreqPriorityUTRA_FDD::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != carrierFreq.Pack(bits))
        {
            printf("FreqPriorityUTRA_FDD:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != cellReselectionPriority.Pack(bits))
        {
            printf("FreqPriorityUTRA_FDD:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int FreqPriorityUTRA_FDD::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int FreqPriorityUTRA_FDD::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != carrierFreq.Unpack(bits, idx))
        {
            printf("FreqPriorityUTRA_FDD:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != cellReselectionPriority.Unpack(bits, idx))
        {
            printf("FreqPriorityUTRA_FDD:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string FreqPriorityUTRA_FDD::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "FreqPriorityUTRA_FDD:\n";
    out += carrierFreq_ToString(indent+1);
    out += cellReselectionPriority_ToString(indent+1);
    return out;
}

std::string FreqPriorityUTRA_FDD::ToStringNoNewLines() const
{
    std::string out = "FreqPriorityUTRA_FDD:";
    out += carrierFreq_ToStringNoNewLines();
    out += cellReselectionPriority_ToStringNoNewLines();
    return out;
}

ARFCN_ValueUTRA* FreqPriorityUTRA_FDD::carrierFreq_Set()
{
    carrierFreq_present = true;
    return &carrierFreq;
}

int FreqPriorityUTRA_FDD::carrierFreq_Set(ARFCN_ValueUTRA &value)
{
    carrierFreq_present = true;
    carrierFreq = value;
    return 0;
}

const ARFCN_ValueUTRA& FreqPriorityUTRA_FDD::carrierFreq_Get() const
{
    return carrierFreq;
}

std::string FreqPriorityUTRA_FDD::carrierFreq_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "carrierFreq:\n";
    out += carrierFreq.ToString(indent+1);
    return out;
}

std::string FreqPriorityUTRA_FDD::carrierFreq_ToStringNoNewLines() const
{
    std::string out = "carrierFreq:";
    out += carrierFreq.ToStringNoNewLines();
    return out;
}

int FreqPriorityUTRA_FDD::carrierFreq_Clear()
{
    carrierFreq_present = false;
    return 0;
}

bool FreqPriorityUTRA_FDD::carrierFreq_IsPresent() const
{
    return carrierFreq_present;
}

CellReselectionPriority* FreqPriorityUTRA_FDD::cellReselectionPriority_Set()
{
    cellReselectionPriority_present = true;
    return &cellReselectionPriority;
}

int FreqPriorityUTRA_FDD::cellReselectionPriority_Set(CellReselectionPriority &value)
{
    cellReselectionPriority_present = true;
    cellReselectionPriority = value;
    return 0;
}

const CellReselectionPriority& FreqPriorityUTRA_FDD::cellReselectionPriority_Get() const
{
    return cellReselectionPriority;
}

std::string FreqPriorityUTRA_FDD::cellReselectionPriority_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cellReselectionPriority:\n";
    out += cellReselectionPriority.ToString(indent+1);
    return out;
}

std::string FreqPriorityUTRA_FDD::cellReselectionPriority_ToStringNoNewLines() const
{
    std::string out = "cellReselectionPriority:";
    out += cellReselectionPriority.ToStringNoNewLines();
    return out;
}

int FreqPriorityUTRA_FDD::cellReselectionPriority_Clear()
{
    cellReselectionPriority_present = false;
    return 0;
}

bool FreqPriorityUTRA_FDD::cellReselectionPriority_IsPresent() const
{
    return cellReselectionPriority_present;
}

