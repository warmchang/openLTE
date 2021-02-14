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

#include "FilterCoefficient.h"

#include <cmath>

int FilterCoefficient::Pack(std::vector<uint8_t> &bits)
{
    if(!present)
    {
        printf("FilterCoefficient::Pack() presence failure\n");
        return -1;
    }
    if(internal_value > k_spare1)
    {
        bits.push_back(1);
    }else{
        bits.push_back(0);
    }
    uint32_t N_bits = 4;
    if(internal_value > k_spare1)
        N_bits = 0;
    for(uint32_t i=0; i<N_bits; i++)
    {
        if(internal_value > k_spare1)
        {
            bits.push_back(((internal_value - k_spare1) >> (N_bits-1-i)) & 1);
        }else{
            bits.push_back((internal_value >> (N_bits-1-i)) & 1);
        }
    }
    return 0;
}

int FilterCoefficient::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int FilterCoefficient::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    if((idx + 1) > bits.size())
    {
        printf("FilterCoefficient::Unpack() index out of bounds for extension\n");
        return -1;
    }
    bool has_extension = bits[idx++];
    uint32_t packed_val = 0;
    uint32_t N_bits = 4;
    if(has_extension)
        N_bits = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("FilterCoefficient::Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(has_extension)
    {
        internal_value = (Enum)(packed_val + 16);
    }else{
        if(packed_val > 15)
        {
            printf("FilterCoefficient::Unpack() max failure\n");
            return -1;
        }
        internal_value = (Enum)packed_val;
    }
    present = true;
    return 0;
}

FilterCoefficient::Enum FilterCoefficient::Value() const
{
    if(present)
        return internal_value;
    return (FilterCoefficient::Enum)0;
}

int FilterCoefficient::SetValue(Enum value)
{
    internal_value = value;
    present = true;
    return 0;
}

int FilterCoefficient::SetValue(std::string value)
{
    if("fc0" == value)
    {
        internal_value = k_fc0;
        present = true;
        return 0;
    }
    if("fc1" == value)
    {
        internal_value = k_fc1;
        present = true;
        return 0;
    }
    if("fc2" == value)
    {
        internal_value = k_fc2;
        present = true;
        return 0;
    }
    if("fc3" == value)
    {
        internal_value = k_fc3;
        present = true;
        return 0;
    }
    if("fc4" == value)
    {
        internal_value = k_fc4;
        present = true;
        return 0;
    }
    if("fc5" == value)
    {
        internal_value = k_fc5;
        present = true;
        return 0;
    }
    if("fc6" == value)
    {
        internal_value = k_fc6;
        present = true;
        return 0;
    }
    if("fc7" == value)
    {
        internal_value = k_fc7;
        present = true;
        return 0;
    }
    if("fc8" == value)
    {
        internal_value = k_fc8;
        present = true;
        return 0;
    }
    if("fc9" == value)
    {
        internal_value = k_fc9;
        present = true;
        return 0;
    }
    if("fc11" == value)
    {
        internal_value = k_fc11;
        present = true;
        return 0;
    }
    if("fc13" == value)
    {
        internal_value = k_fc13;
        present = true;
        return 0;
    }
    if("fc15" == value)
    {
        internal_value = k_fc15;
        present = true;
        return 0;
    }
    if("fc17" == value)
    {
        internal_value = k_fc17;
        present = true;
        return 0;
    }
    if("fc19" == value)
    {
        internal_value = k_fc19;
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

std::string FilterCoefficient::ValueToString(Enum value) const
{
    if(k_fc0 == value)
        return "fc0";
    if(k_fc1 == value)
        return "fc1";
    if(k_fc2 == value)
        return "fc2";
    if(k_fc3 == value)
        return "fc3";
    if(k_fc4 == value)
        return "fc4";
    if(k_fc5 == value)
        return "fc5";
    if(k_fc6 == value)
        return "fc6";
    if(k_fc7 == value)
        return "fc7";
    if(k_fc8 == value)
        return "fc8";
    if(k_fc9 == value)
        return "fc9";
    if(k_fc11 == value)
        return "fc11";
    if(k_fc13 == value)
        return "fc13";
    if(k_fc15 == value)
        return "fc15";
    if(k_fc17 == value)
        return "fc17";
    if(k_fc19 == value)
        return "fc19";
    if(k_spare1 == value)
        return "spare1";
    return "";
}

uint64_t FilterCoefficient::NumberOfValues() const
{
    return 16;
}

std::string FilterCoefficient::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "FilterCoefficient = " + ValueToString(internal_value) + "\n";
    return out;
}

std::string FilterCoefficient::ToStringNoNewLines() const
{
    std::string out = "FilterCoefficient=" + ValueToString(internal_value) + ",";
    return out;
}

int FilterCoefficient::Clear()
{
    present = false;
    return 0;
}

bool FilterCoefficient::IsPresent() const
{
    return present;
}

