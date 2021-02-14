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

#include "TimeAlignmentTimer.h"

#include <cmath>

int TimeAlignmentTimer::Pack(std::vector<uint8_t> &bits)
{
    if(!present)
    {
        printf("TimeAlignmentTimer::Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 3;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int TimeAlignmentTimer::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int TimeAlignmentTimer::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 3;
    if((idx + N_bits) > bits.size())
    {
        printf("TimeAlignmentTimer::Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 7)
    {
        printf("TimeAlignmentTimer::Unpack() max failure\n");
        return -1;
    }
    internal_value = (Enum)packed_val;
    present = true;
    return 0;
}

TimeAlignmentTimer::Enum TimeAlignmentTimer::Value() const
{
    if(present)
        return internal_value;
    return (TimeAlignmentTimer::Enum)0;
}

int TimeAlignmentTimer::SetValue(Enum value)
{
    internal_value = value;
    present = true;
    return 0;
}

int TimeAlignmentTimer::SetValue(std::string value)
{
    if("sf500" == value)
    {
        internal_value = k_sf500;
        present = true;
        return 0;
    }
    if("sf750" == value)
    {
        internal_value = k_sf750;
        present = true;
        return 0;
    }
    if("sf1280" == value)
    {
        internal_value = k_sf1280;
        present = true;
        return 0;
    }
    if("sf1920" == value)
    {
        internal_value = k_sf1920;
        present = true;
        return 0;
    }
    if("sf2560" == value)
    {
        internal_value = k_sf2560;
        present = true;
        return 0;
    }
    if("sf5120" == value)
    {
        internal_value = k_sf5120;
        present = true;
        return 0;
    }
    if("sf10240" == value)
    {
        internal_value = k_sf10240;
        present = true;
        return 0;
    }
    if("infinity" == value)
    {
        internal_value = k_infinity;
        present = true;
        return 0;
    }
    return 1;
}

std::string TimeAlignmentTimer::ValueToString(Enum value) const
{
    if(k_sf500 == value)
        return "sf500";
    if(k_sf750 == value)
        return "sf750";
    if(k_sf1280 == value)
        return "sf1280";
    if(k_sf1920 == value)
        return "sf1920";
    if(k_sf2560 == value)
        return "sf2560";
    if(k_sf5120 == value)
        return "sf5120";
    if(k_sf10240 == value)
        return "sf10240";
    if(k_infinity == value)
        return "infinity";
    return "";
}

uint64_t TimeAlignmentTimer::NumberOfValues() const
{
    return 8;
}

std::string TimeAlignmentTimer::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "TimeAlignmentTimer = " + ValueToString(internal_value) + "\n";
    return out;
}

std::string TimeAlignmentTimer::ToStringNoNewLines() const
{
    std::string out = "TimeAlignmentTimer=" + ValueToString(internal_value) + ",";
    return out;
}

int TimeAlignmentTimer::Clear()
{
    present = false;
    return 0;
}

bool TimeAlignmentTimer::IsPresent() const
{
    return present;
}

