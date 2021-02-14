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

#include "QuantityConfigUTRA_v10x0.h"

#include <cmath>

int QuantityConfigUTRA_v10x0::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    if(!filterCoefficient2_FDD_r10_IsPresent() || filterCoefficient2_FDD_r10_Get().Value() == filterCoefficient2_FDD_r10_GetDefault())
    {
        bits.push_back(0);
    }else{
        bits.push_back(1);
    }

    // Fields
    if(filterCoefficient2_FDD_r10_IsPresent() || filterCoefficient2_FDD_r10_Get().Value() != filterCoefficient2_FDD_r10_GetDefault())
    {
        if(0 != filterCoefficient2_FDD_r10.Pack(bits))
        {
            printf("QuantityConfigUTRA_v10x0:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int QuantityConfigUTRA_v10x0::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int QuantityConfigUTRA_v10x0::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("QuantityConfigUTRA_v10x0::Unpack() index out of bounds for optional indiator filterCoefficient2_FDD_r10\n");
        return -1;
    }
    filterCoefficient2_FDD_r10_present = bits[idx++];

    // Fields
    {
        if(0 != filterCoefficient2_FDD_r10.Unpack(bits, idx))
        {
            printf("QuantityConfigUTRA_v10x0:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string QuantityConfigUTRA_v10x0::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "QuantityConfigUTRA_v10x0:\n";
    out += filterCoefficient2_FDD_r10_ToString(indent+1);
    return out;
}

std::string QuantityConfigUTRA_v10x0::ToStringNoNewLines() const
{
    std::string out = "QuantityConfigUTRA_v10x0:";
    out += filterCoefficient2_FDD_r10_ToStringNoNewLines();
    return out;
}

FilterCoefficient* QuantityConfigUTRA_v10x0::filterCoefficient2_FDD_r10_Set()
{
    filterCoefficient2_FDD_r10_present = true;
    return &filterCoefficient2_FDD_r10;
}

int QuantityConfigUTRA_v10x0::filterCoefficient2_FDD_r10_Set(FilterCoefficient &value)
{
    filterCoefficient2_FDD_r10_present = true;
    filterCoefficient2_FDD_r10 = value;
    return 0;
}

const FilterCoefficient& QuantityConfigUTRA_v10x0::filterCoefficient2_FDD_r10_Get() const
{
    return filterCoefficient2_FDD_r10;
}

FilterCoefficient::Enum QuantityConfigUTRA_v10x0::filterCoefficient2_FDD_r10_GetDefault() const
{
    return FilterCoefficient::k_fc4;
}

std::string QuantityConfigUTRA_v10x0::filterCoefficient2_FDD_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "filterCoefficient2_FDD_r10:\n";
    out += filterCoefficient2_FDD_r10.ToString(indent+1);
    return out;
}

std::string QuantityConfigUTRA_v10x0::filterCoefficient2_FDD_r10_ToStringNoNewLines() const
{
    std::string out = "filterCoefficient2_FDD_r10:";
    out += filterCoefficient2_FDD_r10.ToStringNoNewLines();
    return out;
}

int QuantityConfigUTRA_v10x0::filterCoefficient2_FDD_r10_Clear()
{
    filterCoefficient2_FDD_r10_present = false;
    return 0;
}

bool QuantityConfigUTRA_v10x0::filterCoefficient2_FDD_r10_IsPresent() const
{
    return filterCoefficient2_FDD_r10_present;
}

