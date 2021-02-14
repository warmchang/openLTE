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

#include "IRAT_ParametersGERAN.h"

#include <cmath>

int IRAT_ParametersGERAN::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != supportedBandListGERAN.Pack(bits))
        {
            printf("IRAT_ParametersGERAN:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != interRAT_PS_HO_ToGERAN_Pack(bits))
        {
            printf("IRAT_ParametersGERAN:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int IRAT_ParametersGERAN::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int IRAT_ParametersGERAN::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != supportedBandListGERAN.Unpack(bits, idx))
        {
            printf("IRAT_ParametersGERAN:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != interRAT_PS_HO_ToGERAN_Unpack(bits, idx))
        {
            printf("IRAT_ParametersGERAN:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string IRAT_ParametersGERAN::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "IRAT_ParametersGERAN:\n";
    out += supportedBandListGERAN_ToString(indent+1);
    out += interRAT_PS_HO_ToGERAN_ToString(indent+1);
    return out;
}

std::string IRAT_ParametersGERAN::ToStringNoNewLines() const
{
    std::string out = "IRAT_ParametersGERAN:";
    out += supportedBandListGERAN_ToStringNoNewLines();
    out += interRAT_PS_HO_ToGERAN_ToStringNoNewLines();
    return out;
}

SupportedBandListGERAN* IRAT_ParametersGERAN::supportedBandListGERAN_Set()
{
    supportedBandListGERAN_present = true;
    return &supportedBandListGERAN;
}

int IRAT_ParametersGERAN::supportedBandListGERAN_Set(SupportedBandListGERAN &value)
{
    supportedBandListGERAN_present = true;
    supportedBandListGERAN = value;
    return 0;
}

const SupportedBandListGERAN& IRAT_ParametersGERAN::supportedBandListGERAN_Get() const
{
    return supportedBandListGERAN;
}

std::string IRAT_ParametersGERAN::supportedBandListGERAN_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "supportedBandListGERAN:\n";
    out += supportedBandListGERAN.ToString(indent+1);
    return out;
}

std::string IRAT_ParametersGERAN::supportedBandListGERAN_ToStringNoNewLines() const
{
    std::string out = "supportedBandListGERAN:";
    out += supportedBandListGERAN.ToStringNoNewLines();
    return out;
}

int IRAT_ParametersGERAN::supportedBandListGERAN_Clear()
{
    supportedBandListGERAN_present = false;
    return 0;
}

bool IRAT_ParametersGERAN::supportedBandListGERAN_IsPresent() const
{
    return supportedBandListGERAN_present;
}

int IRAT_ParametersGERAN::interRAT_PS_HO_ToGERAN_Pack(std::vector<uint8_t> &bits)
{
    if(!interRAT_PS_HO_ToGERAN_present)
    {
        printf("IRAT_ParametersGERAN::interRAT_PS_HO_ToGERAN_Pack() presence failure\n");
        return -1;
    }
    bits.push_back(interRAT_PS_HO_ToGERAN_internal_value);
    return 0;
}

int IRAT_ParametersGERAN::interRAT_PS_HO_ToGERAN_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return interRAT_PS_HO_ToGERAN_Unpack(bits, idx);
}

int IRAT_ParametersGERAN::interRAT_PS_HO_ToGERAN_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    if((idx + 1) > bits.size())
    {
        printf("IRAT_ParametersGERAN::interRAT_PS_HO_ToGERAN_Unpack() index out of bounds\n");
        return -1;
    }
    interRAT_PS_HO_ToGERAN_internal_value = bits[idx++];
    interRAT_PS_HO_ToGERAN_present = true;
    return 0;
}

bool IRAT_ParametersGERAN::interRAT_PS_HO_ToGERAN_Value() const
{
    if(interRAT_PS_HO_ToGERAN_present)
        return interRAT_PS_HO_ToGERAN_internal_value;
    return false;
}

int IRAT_ParametersGERAN::interRAT_PS_HO_ToGERAN_SetValue(bool value)
{
    interRAT_PS_HO_ToGERAN_internal_value = value;
    interRAT_PS_HO_ToGERAN_present = true;
    return 0;
}

std::string IRAT_ParametersGERAN::interRAT_PS_HO_ToGERAN_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "interRAT_PS_HO_ToGERAN = " + std::to_string(interRAT_PS_HO_ToGERAN_internal_value) + "\n";
    return out;
}

std::string IRAT_ParametersGERAN::interRAT_PS_HO_ToGERAN_ToStringNoNewLines() const
{
    std::string out = "interRAT_PS_HO_ToGERAN=" + std::to_string(interRAT_PS_HO_ToGERAN_internal_value) + ",";
    return out;
}

int IRAT_ParametersGERAN::interRAT_PS_HO_ToGERAN_Clear()
{
    interRAT_PS_HO_ToGERAN_present = false;
    return 0;
}

bool IRAT_ParametersGERAN::interRAT_PS_HO_ToGERAN_IsPresent() const
{
    return interRAT_PS_HO_ToGERAN_present;
}

