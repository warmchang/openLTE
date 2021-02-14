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

#include "SupportedBandUTRA_TDD768.h"

#include <cmath>

int SupportedBandUTRA_TDD768::Pack(std::vector<uint8_t> &bits)
{
    if(!present)
    {
        printf("SupportedBandUTRA_TDD768::Pack() presence failure\n");
        return -1;
    }
    if(internal_value > k_p)
    {
        bits.push_back(1);
    }else{
        bits.push_back(0);
    }
    uint32_t N_bits = 4;
    if(internal_value > k_p)
        N_bits = 0;
    for(uint32_t i=0; i<N_bits; i++)
    {
        if(internal_value > k_p)
        {
            bits.push_back(((internal_value - k_p) >> (N_bits-1-i)) & 1);
        }else{
            bits.push_back((internal_value >> (N_bits-1-i)) & 1);
        }
    }
    return 0;
}

int SupportedBandUTRA_TDD768::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int SupportedBandUTRA_TDD768::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    if((idx + 1) > bits.size())
    {
        printf("SupportedBandUTRA_TDD768::Unpack() index out of bounds for extension\n");
        return -1;
    }
    bool has_extension = bits[idx++];
    uint32_t packed_val = 0;
    uint32_t N_bits = 4;
    if(has_extension)
        N_bits = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("SupportedBandUTRA_TDD768::Unpack() index out of bounds for value\n");
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
            printf("SupportedBandUTRA_TDD768::Unpack() max failure\n");
            return -1;
        }
        internal_value = (Enum)packed_val;
    }
    present = true;
    return 0;
}

SupportedBandUTRA_TDD768::Enum SupportedBandUTRA_TDD768::Value() const
{
    if(present)
        return internal_value;
    return (SupportedBandUTRA_TDD768::Enum)0;
}

int SupportedBandUTRA_TDD768::SetValue(Enum value)
{
    internal_value = value;
    present = true;
    return 0;
}

int SupportedBandUTRA_TDD768::SetValue(std::string value)
{
    if("a" == value)
    {
        internal_value = k_a;
        present = true;
        return 0;
    }
    if("b" == value)
    {
        internal_value = k_b;
        present = true;
        return 0;
    }
    if("c" == value)
    {
        internal_value = k_c;
        present = true;
        return 0;
    }
    if("d" == value)
    {
        internal_value = k_d;
        present = true;
        return 0;
    }
    if("e" == value)
    {
        internal_value = k_e;
        present = true;
        return 0;
    }
    if("f" == value)
    {
        internal_value = k_f;
        present = true;
        return 0;
    }
    if("g" == value)
    {
        internal_value = k_g;
        present = true;
        return 0;
    }
    if("h" == value)
    {
        internal_value = k_h;
        present = true;
        return 0;
    }
    if("i" == value)
    {
        internal_value = k_i;
        present = true;
        return 0;
    }
    if("j" == value)
    {
        internal_value = k_j;
        present = true;
        return 0;
    }
    if("k" == value)
    {
        internal_value = k_k;
        present = true;
        return 0;
    }
    if("l" == value)
    {
        internal_value = k_l;
        present = true;
        return 0;
    }
    if("m" == value)
    {
        internal_value = k_m;
        present = true;
        return 0;
    }
    if("n" == value)
    {
        internal_value = k_n;
        present = true;
        return 0;
    }
    if("o" == value)
    {
        internal_value = k_o;
        present = true;
        return 0;
    }
    if("p" == value)
    {
        internal_value = k_p;
        present = true;
        return 0;
    }
    return 1;
}

std::string SupportedBandUTRA_TDD768::ValueToString(Enum value) const
{
    if(k_a == value)
        return "a";
    if(k_b == value)
        return "b";
    if(k_c == value)
        return "c";
    if(k_d == value)
        return "d";
    if(k_e == value)
        return "e";
    if(k_f == value)
        return "f";
    if(k_g == value)
        return "g";
    if(k_h == value)
        return "h";
    if(k_i == value)
        return "i";
    if(k_j == value)
        return "j";
    if(k_k == value)
        return "k";
    if(k_l == value)
        return "l";
    if(k_m == value)
        return "m";
    if(k_n == value)
        return "n";
    if(k_o == value)
        return "o";
    if(k_p == value)
        return "p";
    return "";
}

uint64_t SupportedBandUTRA_TDD768::NumberOfValues() const
{
    return 16;
}

std::string SupportedBandUTRA_TDD768::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "SupportedBandUTRA_TDD768 = " + ValueToString(internal_value) + "\n";
    return out;
}

std::string SupportedBandUTRA_TDD768::ToStringNoNewLines() const
{
    std::string out = "SupportedBandUTRA_TDD768=" + ValueToString(internal_value) + ",";
    return out;
}

int SupportedBandUTRA_TDD768::Clear()
{
    present = false;
    return 0;
}

bool SupportedBandUTRA_TDD768::IsPresent() const
{
    return present;
}

