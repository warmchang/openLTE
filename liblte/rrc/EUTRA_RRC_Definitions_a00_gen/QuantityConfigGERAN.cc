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

#include "QuantityConfigGERAN.h"

#include <cmath>

int QuantityConfigGERAN::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    if(!filterCoefficient_IsPresent() || filterCoefficient_Get().Value() == filterCoefficient_GetDefault())
    {
        bits.push_back(0);
    }else{
        bits.push_back(1);
    }

    // Fields
    {
        if(0 != measQuantityGERAN_Pack(bits))
        {
            printf("QuantityConfigGERAN:: field pack failure\n");
            return -1;
        }
    }
    if(filterCoefficient_IsPresent() || filterCoefficient_Get().Value() != filterCoefficient_GetDefault())
    {
        if(0 != filterCoefficient.Pack(bits))
        {
            printf("QuantityConfigGERAN:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int QuantityConfigGERAN::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int QuantityConfigGERAN::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("QuantityConfigGERAN::Unpack() index out of bounds for optional indiator filterCoefficient\n");
        return -1;
    }
    filterCoefficient_present = bits[idx++];

    // Fields
    {
        if(0 != measQuantityGERAN_Unpack(bits, idx))
        {
            printf("QuantityConfigGERAN:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != filterCoefficient.Unpack(bits, idx))
        {
            printf("QuantityConfigGERAN:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string QuantityConfigGERAN::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "QuantityConfigGERAN:\n";
    out += measQuantityGERAN_ToString(indent+1);
    out += filterCoefficient_ToString(indent+1);
    return out;
}

std::string QuantityConfigGERAN::ToStringNoNewLines() const
{
    std::string out = "QuantityConfigGERAN:";
    out += measQuantityGERAN_ToStringNoNewLines();
    out += filterCoefficient_ToStringNoNewLines();
    return out;
}

int QuantityConfigGERAN::measQuantityGERAN_Pack(std::vector<uint8_t> &bits)
{
    if(!measQuantityGERAN_present)
    {
        printf("QuantityConfigGERAN::measQuantityGERAN_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((measQuantityGERAN_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int QuantityConfigGERAN::measQuantityGERAN_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return measQuantityGERAN_Unpack(bits, idx);
}

int QuantityConfigGERAN::measQuantityGERAN_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("QuantityConfigGERAN::measQuantityGERAN_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 0)
    {
        printf("QuantityConfigGERAN::measQuantityGERAN_Unpack() max failure\n");
        return -1;
    }
    measQuantityGERAN_internal_value = (measQuantityGERAN_Enum)packed_val;
    measQuantityGERAN_present = true;
    return 0;
}

QuantityConfigGERAN::measQuantityGERAN_Enum QuantityConfigGERAN::measQuantityGERAN_Value() const
{
    if(measQuantityGERAN_present)
        return measQuantityGERAN_internal_value;
    return (QuantityConfigGERAN::measQuantityGERAN_Enum)0;
}

int QuantityConfigGERAN::measQuantityGERAN_SetValue(measQuantityGERAN_Enum value)
{
    measQuantityGERAN_internal_value = value;
    measQuantityGERAN_present = true;
    return 0;
}

int QuantityConfigGERAN::measQuantityGERAN_SetValue(std::string value)
{
    if("rssi" == value)
    {
        measQuantityGERAN_internal_value = k_measQuantityGERAN_rssi;
        measQuantityGERAN_present = true;
        return 0;
    }
    return 1;
}

std::string QuantityConfigGERAN::measQuantityGERAN_ValueToString(measQuantityGERAN_Enum value) const
{
    if(k_measQuantityGERAN_rssi == value)
        return "rssi";
    return "";
}

uint64_t QuantityConfigGERAN::measQuantityGERAN_NumberOfValues() const
{
    return 1;
}

std::string QuantityConfigGERAN::measQuantityGERAN_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "measQuantityGERAN = " + measQuantityGERAN_ValueToString(measQuantityGERAN_internal_value) + "\n";
    return out;
}

std::string QuantityConfigGERAN::measQuantityGERAN_ToStringNoNewLines() const
{
    std::string out = "measQuantityGERAN=" + measQuantityGERAN_ValueToString(measQuantityGERAN_internal_value) + ",";
    return out;
}

int QuantityConfigGERAN::measQuantityGERAN_Clear()
{
    measQuantityGERAN_present = false;
    return 0;
}

bool QuantityConfigGERAN::measQuantityGERAN_IsPresent() const
{
    return measQuantityGERAN_present;
}

FilterCoefficient* QuantityConfigGERAN::filterCoefficient_Set()
{
    filterCoefficient_present = true;
    return &filterCoefficient;
}

int QuantityConfigGERAN::filterCoefficient_Set(FilterCoefficient &value)
{
    filterCoefficient_present = true;
    filterCoefficient = value;
    return 0;
}

const FilterCoefficient& QuantityConfigGERAN::filterCoefficient_Get() const
{
    return filterCoefficient;
}

FilterCoefficient::Enum QuantityConfigGERAN::filterCoefficient_GetDefault() const
{
    return FilterCoefficient::k_fc2;
}

std::string QuantityConfigGERAN::filterCoefficient_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "filterCoefficient:\n";
    out += filterCoefficient.ToString(indent+1);
    return out;
}

std::string QuantityConfigGERAN::filterCoefficient_ToStringNoNewLines() const
{
    std::string out = "filterCoefficient:";
    out += filterCoefficient.ToStringNoNewLines();
    return out;
}

int QuantityConfigGERAN::filterCoefficient_Clear()
{
    filterCoefficient_present = false;
    return 0;
}

bool QuantityConfigGERAN::filterCoefficient_IsPresent() const
{
    return filterCoefficient_present;
}

