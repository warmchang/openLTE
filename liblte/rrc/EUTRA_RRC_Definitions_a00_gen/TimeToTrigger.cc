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

#include "TimeToTrigger.h"

#include <cmath>

int TimeToTrigger::Pack(std::vector<uint8_t> &bits)
{
    if(!present)
    {
        printf("TimeToTrigger::Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 4;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int TimeToTrigger::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int TimeToTrigger::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 4;
    if((idx + N_bits) > bits.size())
    {
        printf("TimeToTrigger::Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 15)
    {
        printf("TimeToTrigger::Unpack() max failure\n");
        return -1;
    }
    internal_value = (Enum)packed_val;
    present = true;
    return 0;
}

TimeToTrigger::Enum TimeToTrigger::Value() const
{
    if(present)
        return internal_value;
    return (TimeToTrigger::Enum)0;
}

int TimeToTrigger::SetValue(Enum value)
{
    internal_value = value;
    present = true;
    return 0;
}

int TimeToTrigger::SetValue(std::string value)
{
    if("ms0" == value)
    {
        internal_value = k_ms0;
        present = true;
        return 0;
    }
    if("ms40" == value)
    {
        internal_value = k_ms40;
        present = true;
        return 0;
    }
    if("ms64" == value)
    {
        internal_value = k_ms64;
        present = true;
        return 0;
    }
    if("ms80" == value)
    {
        internal_value = k_ms80;
        present = true;
        return 0;
    }
    if("ms100" == value)
    {
        internal_value = k_ms100;
        present = true;
        return 0;
    }
    if("ms128" == value)
    {
        internal_value = k_ms128;
        present = true;
        return 0;
    }
    if("ms160" == value)
    {
        internal_value = k_ms160;
        present = true;
        return 0;
    }
    if("ms256" == value)
    {
        internal_value = k_ms256;
        present = true;
        return 0;
    }
    if("ms320" == value)
    {
        internal_value = k_ms320;
        present = true;
        return 0;
    }
    if("ms480" == value)
    {
        internal_value = k_ms480;
        present = true;
        return 0;
    }
    if("ms512" == value)
    {
        internal_value = k_ms512;
        present = true;
        return 0;
    }
    if("ms640" == value)
    {
        internal_value = k_ms640;
        present = true;
        return 0;
    }
    if("ms1024" == value)
    {
        internal_value = k_ms1024;
        present = true;
        return 0;
    }
    if("ms1280" == value)
    {
        internal_value = k_ms1280;
        present = true;
        return 0;
    }
    if("ms2560" == value)
    {
        internal_value = k_ms2560;
        present = true;
        return 0;
    }
    if("ms5120" == value)
    {
        internal_value = k_ms5120;
        present = true;
        return 0;
    }
    return 1;
}

std::string TimeToTrigger::ValueToString(Enum value) const
{
    if(k_ms0 == value)
        return "ms0";
    if(k_ms40 == value)
        return "ms40";
    if(k_ms64 == value)
        return "ms64";
    if(k_ms80 == value)
        return "ms80";
    if(k_ms100 == value)
        return "ms100";
    if(k_ms128 == value)
        return "ms128";
    if(k_ms160 == value)
        return "ms160";
    if(k_ms256 == value)
        return "ms256";
    if(k_ms320 == value)
        return "ms320";
    if(k_ms480 == value)
        return "ms480";
    if(k_ms512 == value)
        return "ms512";
    if(k_ms640 == value)
        return "ms640";
    if(k_ms1024 == value)
        return "ms1024";
    if(k_ms1280 == value)
        return "ms1280";
    if(k_ms2560 == value)
        return "ms2560";
    if(k_ms5120 == value)
        return "ms5120";
    return "";
}

uint64_t TimeToTrigger::NumberOfValues() const
{
    return 16;
}

std::string TimeToTrigger::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "TimeToTrigger = " + ValueToString(internal_value) + "\n";
    return out;
}

std::string TimeToTrigger::ToStringNoNewLines() const
{
    std::string out = "TimeToTrigger=" + ValueToString(internal_value) + ",";
    return out;
}

int TimeToTrigger::Clear()
{
    present = false;
    return 0;
}

bool TimeToTrigger::IsPresent() const
{
    return present;
}

