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

#include "QuantityConfigEUTRA.h"

#include <cmath>

int QuantityConfigEUTRA::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    if(!filterCoefficientRSRP_IsPresent() || filterCoefficientRSRP_Get().Value() == filterCoefficientRSRP_GetDefault())
    {
        bits.push_back(0);
    }else{
        bits.push_back(1);
    }
    if(!filterCoefficientRSRQ_IsPresent() || filterCoefficientRSRQ_Get().Value() == filterCoefficientRSRQ_GetDefault())
    {
        bits.push_back(0);
    }else{
        bits.push_back(1);
    }

    // Fields
    if(filterCoefficientRSRP_IsPresent() || filterCoefficientRSRP_Get().Value() != filterCoefficientRSRP_GetDefault())
    {
        if(0 != filterCoefficientRSRP.Pack(bits))
        {
            printf("QuantityConfigEUTRA:: field pack failure\n");
            return -1;
        }
    }
    if(filterCoefficientRSRQ_IsPresent() || filterCoefficientRSRQ_Get().Value() != filterCoefficientRSRQ_GetDefault())
    {
        if(0 != filterCoefficientRSRQ.Pack(bits))
        {
            printf("QuantityConfigEUTRA:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int QuantityConfigEUTRA::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int QuantityConfigEUTRA::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("QuantityConfigEUTRA::Unpack() index out of bounds for optional indiator filterCoefficientRSRP\n");
        return -1;
    }
    filterCoefficientRSRP_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("QuantityConfigEUTRA::Unpack() index out of bounds for optional indiator filterCoefficientRSRQ\n");
        return -1;
    }
    filterCoefficientRSRQ_present = bits[idx++];

    // Fields
    {
        if(0 != filterCoefficientRSRP.Unpack(bits, idx))
        {
            printf("QuantityConfigEUTRA:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != filterCoefficientRSRQ.Unpack(bits, idx))
        {
            printf("QuantityConfigEUTRA:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string QuantityConfigEUTRA::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "QuantityConfigEUTRA:\n";
    out += filterCoefficientRSRP_ToString(indent+1);
    out += filterCoefficientRSRQ_ToString(indent+1);
    return out;
}

std::string QuantityConfigEUTRA::ToStringNoNewLines() const
{
    std::string out = "QuantityConfigEUTRA:";
    out += filterCoefficientRSRP_ToStringNoNewLines();
    out += filterCoefficientRSRQ_ToStringNoNewLines();
    return out;
}

FilterCoefficient* QuantityConfigEUTRA::filterCoefficientRSRP_Set()
{
    filterCoefficientRSRP_present = true;
    return &filterCoefficientRSRP;
}

int QuantityConfigEUTRA::filterCoefficientRSRP_Set(FilterCoefficient &value)
{
    filterCoefficientRSRP_present = true;
    filterCoefficientRSRP = value;
    return 0;
}

const FilterCoefficient& QuantityConfigEUTRA::filterCoefficientRSRP_Get() const
{
    return filterCoefficientRSRP;
}

FilterCoefficient::Enum QuantityConfigEUTRA::filterCoefficientRSRP_GetDefault() const
{
    return FilterCoefficient::k_fc4;
}

std::string QuantityConfigEUTRA::filterCoefficientRSRP_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "filterCoefficientRSRP:\n";
    out += filterCoefficientRSRP.ToString(indent+1);
    return out;
}

std::string QuantityConfigEUTRA::filterCoefficientRSRP_ToStringNoNewLines() const
{
    std::string out = "filterCoefficientRSRP:";
    out += filterCoefficientRSRP.ToStringNoNewLines();
    return out;
}

int QuantityConfigEUTRA::filterCoefficientRSRP_Clear()
{
    filterCoefficientRSRP_present = false;
    return 0;
}

bool QuantityConfigEUTRA::filterCoefficientRSRP_IsPresent() const
{
    return filterCoefficientRSRP_present;
}

FilterCoefficient* QuantityConfigEUTRA::filterCoefficientRSRQ_Set()
{
    filterCoefficientRSRQ_present = true;
    return &filterCoefficientRSRQ;
}

int QuantityConfigEUTRA::filterCoefficientRSRQ_Set(FilterCoefficient &value)
{
    filterCoefficientRSRQ_present = true;
    filterCoefficientRSRQ = value;
    return 0;
}

const FilterCoefficient& QuantityConfigEUTRA::filterCoefficientRSRQ_Get() const
{
    return filterCoefficientRSRQ;
}

FilterCoefficient::Enum QuantityConfigEUTRA::filterCoefficientRSRQ_GetDefault() const
{
    return FilterCoefficient::k_fc4;
}

std::string QuantityConfigEUTRA::filterCoefficientRSRQ_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "filterCoefficientRSRQ:\n";
    out += filterCoefficientRSRQ.ToString(indent+1);
    return out;
}

std::string QuantityConfigEUTRA::filterCoefficientRSRQ_ToStringNoNewLines() const
{
    std::string out = "filterCoefficientRSRQ:";
    out += filterCoefficientRSRQ.ToStringNoNewLines();
    return out;
}

int QuantityConfigEUTRA::filterCoefficientRSRQ_Clear()
{
    filterCoefficientRSRQ_present = false;
    return 0;
}

bool QuantityConfigEUTRA::filterCoefficientRSRQ_IsPresent() const
{
    return filterCoefficientRSRQ_present;
}

