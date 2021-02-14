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

#include "T_Reordering.h"

#include <cmath>

int T_Reordering::Pack(std::vector<uint8_t> &bits)
{
    if(!present)
    {
        printf("T_Reordering::Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 5;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int T_Reordering::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int T_Reordering::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 5;
    if((idx + N_bits) > bits.size())
    {
        printf("T_Reordering::Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 31)
    {
        printf("T_Reordering::Unpack() max failure\n");
        return -1;
    }
    internal_value = (Enum)packed_val;
    present = true;
    return 0;
}

T_Reordering::Enum T_Reordering::Value() const
{
    if(present)
        return internal_value;
    return (T_Reordering::Enum)0;
}

int T_Reordering::SetValue(Enum value)
{
    internal_value = value;
    present = true;
    return 0;
}

int T_Reordering::SetValue(std::string value)
{
    if("ms0" == value)
    {
        internal_value = k_ms0;
        present = true;
        return 0;
    }
    if("ms5" == value)
    {
        internal_value = k_ms5;
        present = true;
        return 0;
    }
    if("ms10" == value)
    {
        internal_value = k_ms10;
        present = true;
        return 0;
    }
    if("ms15" == value)
    {
        internal_value = k_ms15;
        present = true;
        return 0;
    }
    if("ms20" == value)
    {
        internal_value = k_ms20;
        present = true;
        return 0;
    }
    if("ms25" == value)
    {
        internal_value = k_ms25;
        present = true;
        return 0;
    }
    if("ms30" == value)
    {
        internal_value = k_ms30;
        present = true;
        return 0;
    }
    if("ms35" == value)
    {
        internal_value = k_ms35;
        present = true;
        return 0;
    }
    if("ms40" == value)
    {
        internal_value = k_ms40;
        present = true;
        return 0;
    }
    if("ms45" == value)
    {
        internal_value = k_ms45;
        present = true;
        return 0;
    }
    if("ms50" == value)
    {
        internal_value = k_ms50;
        present = true;
        return 0;
    }
    if("ms55" == value)
    {
        internal_value = k_ms55;
        present = true;
        return 0;
    }
    if("ms60" == value)
    {
        internal_value = k_ms60;
        present = true;
        return 0;
    }
    if("ms65" == value)
    {
        internal_value = k_ms65;
        present = true;
        return 0;
    }
    if("ms70" == value)
    {
        internal_value = k_ms70;
        present = true;
        return 0;
    }
    if("ms75" == value)
    {
        internal_value = k_ms75;
        present = true;
        return 0;
    }
    if("ms80" == value)
    {
        internal_value = k_ms80;
        present = true;
        return 0;
    }
    if("ms85" == value)
    {
        internal_value = k_ms85;
        present = true;
        return 0;
    }
    if("ms90" == value)
    {
        internal_value = k_ms90;
        present = true;
        return 0;
    }
    if("ms95" == value)
    {
        internal_value = k_ms95;
        present = true;
        return 0;
    }
    if("ms100" == value)
    {
        internal_value = k_ms100;
        present = true;
        return 0;
    }
    if("ms110" == value)
    {
        internal_value = k_ms110;
        present = true;
        return 0;
    }
    if("ms120" == value)
    {
        internal_value = k_ms120;
        present = true;
        return 0;
    }
    if("ms130" == value)
    {
        internal_value = k_ms130;
        present = true;
        return 0;
    }
    if("ms140" == value)
    {
        internal_value = k_ms140;
        present = true;
        return 0;
    }
    if("ms150" == value)
    {
        internal_value = k_ms150;
        present = true;
        return 0;
    }
    if("ms160" == value)
    {
        internal_value = k_ms160;
        present = true;
        return 0;
    }
    if("ms170" == value)
    {
        internal_value = k_ms170;
        present = true;
        return 0;
    }
    if("ms180" == value)
    {
        internal_value = k_ms180;
        present = true;
        return 0;
    }
    if("ms190" == value)
    {
        internal_value = k_ms190;
        present = true;
        return 0;
    }
    if("ms200" == value)
    {
        internal_value = k_ms200;
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

std::string T_Reordering::ValueToString(Enum value) const
{
    if(k_ms0 == value)
        return "ms0";
    if(k_ms5 == value)
        return "ms5";
    if(k_ms10 == value)
        return "ms10";
    if(k_ms15 == value)
        return "ms15";
    if(k_ms20 == value)
        return "ms20";
    if(k_ms25 == value)
        return "ms25";
    if(k_ms30 == value)
        return "ms30";
    if(k_ms35 == value)
        return "ms35";
    if(k_ms40 == value)
        return "ms40";
    if(k_ms45 == value)
        return "ms45";
    if(k_ms50 == value)
        return "ms50";
    if(k_ms55 == value)
        return "ms55";
    if(k_ms60 == value)
        return "ms60";
    if(k_ms65 == value)
        return "ms65";
    if(k_ms70 == value)
        return "ms70";
    if(k_ms75 == value)
        return "ms75";
    if(k_ms80 == value)
        return "ms80";
    if(k_ms85 == value)
        return "ms85";
    if(k_ms90 == value)
        return "ms90";
    if(k_ms95 == value)
        return "ms95";
    if(k_ms100 == value)
        return "ms100";
    if(k_ms110 == value)
        return "ms110";
    if(k_ms120 == value)
        return "ms120";
    if(k_ms130 == value)
        return "ms130";
    if(k_ms140 == value)
        return "ms140";
    if(k_ms150 == value)
        return "ms150";
    if(k_ms160 == value)
        return "ms160";
    if(k_ms170 == value)
        return "ms170";
    if(k_ms180 == value)
        return "ms180";
    if(k_ms190 == value)
        return "ms190";
    if(k_ms200 == value)
        return "ms200";
    if(k_spare1 == value)
        return "spare1";
    return "";
}

uint64_t T_Reordering::NumberOfValues() const
{
    return 32;
}

std::string T_Reordering::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "T_Reordering = " + ValueToString(internal_value) + "\n";
    return out;
}

std::string T_Reordering::ToStringNoNewLines() const
{
    std::string out = "T_Reordering=" + ValueToString(internal_value) + ",";
    return out;
}

int T_Reordering::Clear()
{
    present = false;
    return 0;
}

bool T_Reordering::IsPresent() const
{
    return present;
}

