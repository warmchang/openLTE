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

#include "QuantityConfigCDMA2000.h"

#include <cmath>

int QuantityConfigCDMA2000::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != measQuantityCDMA2000_Pack(bits))
        {
            printf("QuantityConfigCDMA2000:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int QuantityConfigCDMA2000::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int QuantityConfigCDMA2000::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != measQuantityCDMA2000_Unpack(bits, idx))
        {
            printf("QuantityConfigCDMA2000:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string QuantityConfigCDMA2000::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "QuantityConfigCDMA2000:\n";
    out += measQuantityCDMA2000_ToString(indent+1);
    return out;
}

std::string QuantityConfigCDMA2000::ToStringNoNewLines() const
{
    std::string out = "QuantityConfigCDMA2000:";
    out += measQuantityCDMA2000_ToStringNoNewLines();
    return out;
}

int QuantityConfigCDMA2000::measQuantityCDMA2000_Pack(std::vector<uint8_t> &bits)
{
    if(!measQuantityCDMA2000_present)
    {
        printf("QuantityConfigCDMA2000::measQuantityCDMA2000_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((measQuantityCDMA2000_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int QuantityConfigCDMA2000::measQuantityCDMA2000_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return measQuantityCDMA2000_Unpack(bits, idx);
}

int QuantityConfigCDMA2000::measQuantityCDMA2000_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("QuantityConfigCDMA2000::measQuantityCDMA2000_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 1)
    {
        printf("QuantityConfigCDMA2000::measQuantityCDMA2000_Unpack() max failure\n");
        return -1;
    }
    measQuantityCDMA2000_internal_value = (measQuantityCDMA2000_Enum)packed_val;
    measQuantityCDMA2000_present = true;
    return 0;
}

QuantityConfigCDMA2000::measQuantityCDMA2000_Enum QuantityConfigCDMA2000::measQuantityCDMA2000_Value() const
{
    if(measQuantityCDMA2000_present)
        return measQuantityCDMA2000_internal_value;
    return (QuantityConfigCDMA2000::measQuantityCDMA2000_Enum)0;
}

int QuantityConfigCDMA2000::measQuantityCDMA2000_SetValue(measQuantityCDMA2000_Enum value)
{
    measQuantityCDMA2000_internal_value = value;
    measQuantityCDMA2000_present = true;
    return 0;
}

int QuantityConfigCDMA2000::measQuantityCDMA2000_SetValue(std::string value)
{
    if("pilotStrength" == value)
    {
        measQuantityCDMA2000_internal_value = k_measQuantityCDMA2000_pilotStrength;
        measQuantityCDMA2000_present = true;
        return 0;
    }
    if("pilotPnPhaseAndPilotStrength" == value)
    {
        measQuantityCDMA2000_internal_value = k_measQuantityCDMA2000_pilotPnPhaseAndPilotStrength;
        measQuantityCDMA2000_present = true;
        return 0;
    }
    return 1;
}

std::string QuantityConfigCDMA2000::measQuantityCDMA2000_ValueToString(measQuantityCDMA2000_Enum value) const
{
    if(k_measQuantityCDMA2000_pilotStrength == value)
        return "pilotStrength";
    if(k_measQuantityCDMA2000_pilotPnPhaseAndPilotStrength == value)
        return "pilotPnPhaseAndPilotStrength";
    return "";
}

uint64_t QuantityConfigCDMA2000::measQuantityCDMA2000_NumberOfValues() const
{
    return 2;
}

std::string QuantityConfigCDMA2000::measQuantityCDMA2000_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "measQuantityCDMA2000 = " + measQuantityCDMA2000_ValueToString(measQuantityCDMA2000_internal_value) + "\n";
    return out;
}

std::string QuantityConfigCDMA2000::measQuantityCDMA2000_ToStringNoNewLines() const
{
    std::string out = "measQuantityCDMA2000=" + measQuantityCDMA2000_ValueToString(measQuantityCDMA2000_internal_value) + ",";
    return out;
}

int QuantityConfigCDMA2000::measQuantityCDMA2000_Clear()
{
    measQuantityCDMA2000_present = false;
    return 0;
}

bool QuantityConfigCDMA2000::measQuantityCDMA2000_IsPresent() const
{
    return measQuantityCDMA2000_present;
}

