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

#include "AntennaInfoCommon.h"

#include <cmath>

int AntennaInfoCommon::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != antennaPortsCount_Pack(bits))
        {
            printf("AntennaInfoCommon:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int AntennaInfoCommon::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int AntennaInfoCommon::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != antennaPortsCount_Unpack(bits, idx))
        {
            printf("AntennaInfoCommon:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string AntennaInfoCommon::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "AntennaInfoCommon:\n";
    out += antennaPortsCount_ToString(indent+1);
    return out;
}

std::string AntennaInfoCommon::ToStringNoNewLines() const
{
    std::string out = "AntennaInfoCommon:";
    out += antennaPortsCount_ToStringNoNewLines();
    return out;
}

int AntennaInfoCommon::antennaPortsCount_Pack(std::vector<uint8_t> &bits)
{
    if(!antennaPortsCount_present)
    {
        printf("AntennaInfoCommon::antennaPortsCount_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 2;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((antennaPortsCount_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int AntennaInfoCommon::antennaPortsCount_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return antennaPortsCount_Unpack(bits, idx);
}

int AntennaInfoCommon::antennaPortsCount_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 2;
    if((idx + N_bits) > bits.size())
    {
        printf("AntennaInfoCommon::antennaPortsCount_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 3)
    {
        printf("AntennaInfoCommon::antennaPortsCount_Unpack() max failure\n");
        return -1;
    }
    antennaPortsCount_internal_value = (antennaPortsCount_Enum)packed_val;
    antennaPortsCount_present = true;
    return 0;
}

AntennaInfoCommon::antennaPortsCount_Enum AntennaInfoCommon::antennaPortsCount_Value() const
{
    if(antennaPortsCount_present)
        return antennaPortsCount_internal_value;
    return (AntennaInfoCommon::antennaPortsCount_Enum)0;
}

int AntennaInfoCommon::antennaPortsCount_SetValue(antennaPortsCount_Enum value)
{
    antennaPortsCount_internal_value = value;
    antennaPortsCount_present = true;
    return 0;
}

int AntennaInfoCommon::antennaPortsCount_SetValue(std::string value)
{
    if("an1" == value)
    {
        antennaPortsCount_internal_value = k_antennaPortsCount_an1;
        antennaPortsCount_present = true;
        return 0;
    }
    if("an2" == value)
    {
        antennaPortsCount_internal_value = k_antennaPortsCount_an2;
        antennaPortsCount_present = true;
        return 0;
    }
    if("an4" == value)
    {
        antennaPortsCount_internal_value = k_antennaPortsCount_an4;
        antennaPortsCount_present = true;
        return 0;
    }
    if("spare1" == value)
    {
        antennaPortsCount_internal_value = k_antennaPortsCount_spare1;
        antennaPortsCount_present = true;
        return 0;
    }
    return 1;
}

std::string AntennaInfoCommon::antennaPortsCount_ValueToString(antennaPortsCount_Enum value) const
{
    if(k_antennaPortsCount_an1 == value)
        return "an1";
    if(k_antennaPortsCount_an2 == value)
        return "an2";
    if(k_antennaPortsCount_an4 == value)
        return "an4";
    if(k_antennaPortsCount_spare1 == value)
        return "spare1";
    return "";
}

uint64_t AntennaInfoCommon::antennaPortsCount_NumberOfValues() const
{
    return 4;
}

std::string AntennaInfoCommon::antennaPortsCount_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "antennaPortsCount = " + antennaPortsCount_ValueToString(antennaPortsCount_internal_value) + "\n";
    return out;
}

std::string AntennaInfoCommon::antennaPortsCount_ToStringNoNewLines() const
{
    std::string out = "antennaPortsCount=" + antennaPortsCount_ValueToString(antennaPortsCount_internal_value) + ",";
    return out;
}

int AntennaInfoCommon::antennaPortsCount_Clear()
{
    antennaPortsCount_present = false;
    return 0;
}

bool AntennaInfoCommon::antennaPortsCount_IsPresent() const
{
    return antennaPortsCount_present;
}

