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

#include "Q_OffsetRange.h"

#include <cmath>

int Q_OffsetRange::Pack(std::vector<uint8_t> &bits)
{
    if(!present)
    {
        printf("Q_OffsetRange::Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 5;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int Q_OffsetRange::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int Q_OffsetRange::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 5;
    if((idx + N_bits) > bits.size())
    {
        printf("Q_OffsetRange::Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 30)
    {
        printf("Q_OffsetRange::Unpack() max failure\n");
        return -1;
    }
    internal_value = (Enum)packed_val;
    present = true;
    return 0;
}

Q_OffsetRange::Enum Q_OffsetRange::Value() const
{
    if(present)
        return internal_value;
    return (Q_OffsetRange::Enum)0;
}

int Q_OffsetRange::SetValue(Enum value)
{
    internal_value = value;
    present = true;
    return 0;
}

int Q_OffsetRange::SetValue(std::string value)
{
    if("dB_24" == value)
    {
        internal_value = k_dB_24;
        present = true;
        return 0;
    }
    if("dB_22" == value)
    {
        internal_value = k_dB_22;
        present = true;
        return 0;
    }
    if("dB_20" == value)
    {
        internal_value = k_dB_20;
        present = true;
        return 0;
    }
    if("dB_18" == value)
    {
        internal_value = k_dB_18;
        present = true;
        return 0;
    }
    if("dB_16" == value)
    {
        internal_value = k_dB_16;
        present = true;
        return 0;
    }
    if("dB_14" == value)
    {
        internal_value = k_dB_14;
        present = true;
        return 0;
    }
    if("dB_12" == value)
    {
        internal_value = k_dB_12;
        present = true;
        return 0;
    }
    if("dB_10" == value)
    {
        internal_value = k_dB_10;
        present = true;
        return 0;
    }
    if("dB_8" == value)
    {
        internal_value = k_dB_8;
        present = true;
        return 0;
    }
    if("dB_6" == value)
    {
        internal_value = k_dB_6;
        present = true;
        return 0;
    }
    if("dB_5" == value)
    {
        internal_value = k_dB_5;
        present = true;
        return 0;
    }
    if("dB_4" == value)
    {
        internal_value = k_dB_4;
        present = true;
        return 0;
    }
    if("dB_3" == value)
    {
        internal_value = k_dB_3;
        present = true;
        return 0;
    }
    if("dB_2" == value)
    {
        internal_value = k_dB_2;
        present = true;
        return 0;
    }
    if("dB_1" == value)
    {
        internal_value = k_dB_1;
        present = true;
        return 0;
    }
    if("dB0" == value)
    {
        internal_value = k_dB0;
        present = true;
        return 0;
    }
    if("dB1" == value)
    {
        internal_value = k_dB1;
        present = true;
        return 0;
    }
    if("dB2" == value)
    {
        internal_value = k_dB2;
        present = true;
        return 0;
    }
    if("dB3" == value)
    {
        internal_value = k_dB3;
        present = true;
        return 0;
    }
    if("dB4" == value)
    {
        internal_value = k_dB4;
        present = true;
        return 0;
    }
    if("dB5" == value)
    {
        internal_value = k_dB5;
        present = true;
        return 0;
    }
    if("dB6" == value)
    {
        internal_value = k_dB6;
        present = true;
        return 0;
    }
    if("dB8" == value)
    {
        internal_value = k_dB8;
        present = true;
        return 0;
    }
    if("dB10" == value)
    {
        internal_value = k_dB10;
        present = true;
        return 0;
    }
    if("dB12" == value)
    {
        internal_value = k_dB12;
        present = true;
        return 0;
    }
    if("dB14" == value)
    {
        internal_value = k_dB14;
        present = true;
        return 0;
    }
    if("dB16" == value)
    {
        internal_value = k_dB16;
        present = true;
        return 0;
    }
    if("dB18" == value)
    {
        internal_value = k_dB18;
        present = true;
        return 0;
    }
    if("dB20" == value)
    {
        internal_value = k_dB20;
        present = true;
        return 0;
    }
    if("dB22" == value)
    {
        internal_value = k_dB22;
        present = true;
        return 0;
    }
    if("dB24" == value)
    {
        internal_value = k_dB24;
        present = true;
        return 0;
    }
    return 1;
}

std::string Q_OffsetRange::ValueToString(Enum value) const
{
    if(k_dB_24 == value)
        return "dB_24";
    if(k_dB_22 == value)
        return "dB_22";
    if(k_dB_20 == value)
        return "dB_20";
    if(k_dB_18 == value)
        return "dB_18";
    if(k_dB_16 == value)
        return "dB_16";
    if(k_dB_14 == value)
        return "dB_14";
    if(k_dB_12 == value)
        return "dB_12";
    if(k_dB_10 == value)
        return "dB_10";
    if(k_dB_8 == value)
        return "dB_8";
    if(k_dB_6 == value)
        return "dB_6";
    if(k_dB_5 == value)
        return "dB_5";
    if(k_dB_4 == value)
        return "dB_4";
    if(k_dB_3 == value)
        return "dB_3";
    if(k_dB_2 == value)
        return "dB_2";
    if(k_dB_1 == value)
        return "dB_1";
    if(k_dB0 == value)
        return "dB0";
    if(k_dB1 == value)
        return "dB1";
    if(k_dB2 == value)
        return "dB2";
    if(k_dB3 == value)
        return "dB3";
    if(k_dB4 == value)
        return "dB4";
    if(k_dB5 == value)
        return "dB5";
    if(k_dB6 == value)
        return "dB6";
    if(k_dB8 == value)
        return "dB8";
    if(k_dB10 == value)
        return "dB10";
    if(k_dB12 == value)
        return "dB12";
    if(k_dB14 == value)
        return "dB14";
    if(k_dB16 == value)
        return "dB16";
    if(k_dB18 == value)
        return "dB18";
    if(k_dB20 == value)
        return "dB20";
    if(k_dB22 == value)
        return "dB22";
    if(k_dB24 == value)
        return "dB24";
    return "";
}

uint64_t Q_OffsetRange::NumberOfValues() const
{
    return 31;
}

std::string Q_OffsetRange::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "Q_OffsetRange = " + ValueToString(internal_value) + "\n";
    return out;
}

std::string Q_OffsetRange::ToStringNoNewLines() const
{
    std::string out = "Q_OffsetRange=" + ValueToString(internal_value) + ",";
    return out;
}

int Q_OffsetRange::Clear()
{
    present = false;
    return 0;
}

bool Q_OffsetRange::IsPresent() const
{
    return present;
}

