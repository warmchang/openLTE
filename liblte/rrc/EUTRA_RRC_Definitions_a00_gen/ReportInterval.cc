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

#include "ReportInterval.h"

#include <cmath>

int ReportInterval::Pack(std::vector<uint8_t> &bits)
{
    if(!present)
    {
        printf("ReportInterval::Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 4;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int ReportInterval::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int ReportInterval::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 4;
    if((idx + N_bits) > bits.size())
    {
        printf("ReportInterval::Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 15)
    {
        printf("ReportInterval::Unpack() max failure\n");
        return -1;
    }
    internal_value = (Enum)packed_val;
    present = true;
    return 0;
}

ReportInterval::Enum ReportInterval::Value() const
{
    if(present)
        return internal_value;
    return (ReportInterval::Enum)0;
}

int ReportInterval::SetValue(Enum value)
{
    internal_value = value;
    present = true;
    return 0;
}

int ReportInterval::SetValue(std::string value)
{
    if("ms120" == value)
    {
        internal_value = k_ms120;
        present = true;
        return 0;
    }
    if("ms240" == value)
    {
        internal_value = k_ms240;
        present = true;
        return 0;
    }
    if("ms480" == value)
    {
        internal_value = k_ms480;
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
    if("ms2048" == value)
    {
        internal_value = k_ms2048;
        present = true;
        return 0;
    }
    if("ms5120" == value)
    {
        internal_value = k_ms5120;
        present = true;
        return 0;
    }
    if("ms10240" == value)
    {
        internal_value = k_ms10240;
        present = true;
        return 0;
    }
    if("min1" == value)
    {
        internal_value = k_min1;
        present = true;
        return 0;
    }
    if("min6" == value)
    {
        internal_value = k_min6;
        present = true;
        return 0;
    }
    if("min12" == value)
    {
        internal_value = k_min12;
        present = true;
        return 0;
    }
    if("min30" == value)
    {
        internal_value = k_min30;
        present = true;
        return 0;
    }
    if("min60" == value)
    {
        internal_value = k_min60;
        present = true;
        return 0;
    }
    if("spare3" == value)
    {
        internal_value = k_spare3;
        present = true;
        return 0;
    }
    if("spare2" == value)
    {
        internal_value = k_spare2;
        present = true;
        return 0;
    }
    if("spare1" == value)
    {
        internal_value = k_spare1;
        present = true;
        return 0;
    }
    return 1;
}

std::string ReportInterval::ValueToString(Enum value) const
{
    if(k_ms120 == value)
        return "ms120";
    if(k_ms240 == value)
        return "ms240";
    if(k_ms480 == value)
        return "ms480";
    if(k_ms640 == value)
        return "ms640";
    if(k_ms1024 == value)
        return "ms1024";
    if(k_ms2048 == value)
        return "ms2048";
    if(k_ms5120 == value)
        return "ms5120";
    if(k_ms10240 == value)
        return "ms10240";
    if(k_min1 == value)
        return "min1";
    if(k_min6 == value)
        return "min6";
    if(k_min12 == value)
        return "min12";
    if(k_min30 == value)
        return "min30";
    if(k_min60 == value)
        return "min60";
    if(k_spare3 == value)
        return "spare3";
    if(k_spare2 == value)
        return "spare2";
    if(k_spare1 == value)
        return "spare1";
    return "";
}

uint64_t ReportInterval::NumberOfValues() const
{
    return 16;
}

std::string ReportInterval::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ReportInterval = " + ValueToString(internal_value) + "\n";
    return out;
}

std::string ReportInterval::ToStringNoNewLines() const
{
    std::string out = "ReportInterval=" + ValueToString(internal_value) + ",";
    return out;
}

int ReportInterval::Clear()
{
    present = false;
    return 0;
}

bool ReportInterval::IsPresent() const
{
    return present;
}

