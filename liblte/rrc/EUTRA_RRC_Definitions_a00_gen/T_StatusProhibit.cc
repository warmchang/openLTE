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

#include "T_StatusProhibit.h"

#include <cmath>

int T_StatusProhibit::Pack(std::vector<uint8_t> &bits)
{
    if(!present)
    {
        printf("T_StatusProhibit::Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 6;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int T_StatusProhibit::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int T_StatusProhibit::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 6;
    if((idx + N_bits) > bits.size())
    {
        printf("T_StatusProhibit::Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 63)
    {
        printf("T_StatusProhibit::Unpack() max failure\n");
        return -1;
    }
    internal_value = (Enum)packed_val;
    present = true;
    return 0;
}

T_StatusProhibit::Enum T_StatusProhibit::Value() const
{
    if(present)
        return internal_value;
    return (T_StatusProhibit::Enum)0;
}

int T_StatusProhibit::SetValue(Enum value)
{
    internal_value = value;
    present = true;
    return 0;
}

int T_StatusProhibit::SetValue(std::string value)
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
    if("ms105" == value)
    {
        internal_value = k_ms105;
        present = true;
        return 0;
    }
    if("ms110" == value)
    {
        internal_value = k_ms110;
        present = true;
        return 0;
    }
    if("ms115" == value)
    {
        internal_value = k_ms115;
        present = true;
        return 0;
    }
    if("ms120" == value)
    {
        internal_value = k_ms120;
        present = true;
        return 0;
    }
    if("ms125" == value)
    {
        internal_value = k_ms125;
        present = true;
        return 0;
    }
    if("ms130" == value)
    {
        internal_value = k_ms130;
        present = true;
        return 0;
    }
    if("ms135" == value)
    {
        internal_value = k_ms135;
        present = true;
        return 0;
    }
    if("ms140" == value)
    {
        internal_value = k_ms140;
        present = true;
        return 0;
    }
    if("ms145" == value)
    {
        internal_value = k_ms145;
        present = true;
        return 0;
    }
    if("ms150" == value)
    {
        internal_value = k_ms150;
        present = true;
        return 0;
    }
    if("ms155" == value)
    {
        internal_value = k_ms155;
        present = true;
        return 0;
    }
    if("ms160" == value)
    {
        internal_value = k_ms160;
        present = true;
        return 0;
    }
    if("ms165" == value)
    {
        internal_value = k_ms165;
        present = true;
        return 0;
    }
    if("ms170" == value)
    {
        internal_value = k_ms170;
        present = true;
        return 0;
    }
    if("ms175" == value)
    {
        internal_value = k_ms175;
        present = true;
        return 0;
    }
    if("ms180" == value)
    {
        internal_value = k_ms180;
        present = true;
        return 0;
    }
    if("ms185" == value)
    {
        internal_value = k_ms185;
        present = true;
        return 0;
    }
    if("ms190" == value)
    {
        internal_value = k_ms190;
        present = true;
        return 0;
    }
    if("ms195" == value)
    {
        internal_value = k_ms195;
        present = true;
        return 0;
    }
    if("ms200" == value)
    {
        internal_value = k_ms200;
        present = true;
        return 0;
    }
    if("ms205" == value)
    {
        internal_value = k_ms205;
        present = true;
        return 0;
    }
    if("ms210" == value)
    {
        internal_value = k_ms210;
        present = true;
        return 0;
    }
    if("ms215" == value)
    {
        internal_value = k_ms215;
        present = true;
        return 0;
    }
    if("ms220" == value)
    {
        internal_value = k_ms220;
        present = true;
        return 0;
    }
    if("ms225" == value)
    {
        internal_value = k_ms225;
        present = true;
        return 0;
    }
    if("ms230" == value)
    {
        internal_value = k_ms230;
        present = true;
        return 0;
    }
    if("ms235" == value)
    {
        internal_value = k_ms235;
        present = true;
        return 0;
    }
    if("ms240" == value)
    {
        internal_value = k_ms240;
        present = true;
        return 0;
    }
    if("ms245" == value)
    {
        internal_value = k_ms245;
        present = true;
        return 0;
    }
    if("ms250" == value)
    {
        internal_value = k_ms250;
        present = true;
        return 0;
    }
    if("ms300" == value)
    {
        internal_value = k_ms300;
        present = true;
        return 0;
    }
    if("ms350" == value)
    {
        internal_value = k_ms350;
        present = true;
        return 0;
    }
    if("ms400" == value)
    {
        internal_value = k_ms400;
        present = true;
        return 0;
    }
    if("ms450" == value)
    {
        internal_value = k_ms450;
        present = true;
        return 0;
    }
    if("ms500" == value)
    {
        internal_value = k_ms500;
        present = true;
        return 0;
    }
    if("spare8" == value)
    {
        internal_value = k_spare8;
        present = true;
        return 0;
    }
    if("spare7" == value)
    {
        internal_value = k_spare7;
        present = true;
        return 0;
    }
    if("spare6" == value)
    {
        internal_value = k_spare6;
        present = true;
        return 0;
    }
    if("spare5" == value)
    {
        internal_value = k_spare5;
        present = true;
        return 0;
    }
    if("spare4" == value)
    {
        internal_value = k_spare4;
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

std::string T_StatusProhibit::ValueToString(Enum value) const
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
    if(k_ms105 == value)
        return "ms105";
    if(k_ms110 == value)
        return "ms110";
    if(k_ms115 == value)
        return "ms115";
    if(k_ms120 == value)
        return "ms120";
    if(k_ms125 == value)
        return "ms125";
    if(k_ms130 == value)
        return "ms130";
    if(k_ms135 == value)
        return "ms135";
    if(k_ms140 == value)
        return "ms140";
    if(k_ms145 == value)
        return "ms145";
    if(k_ms150 == value)
        return "ms150";
    if(k_ms155 == value)
        return "ms155";
    if(k_ms160 == value)
        return "ms160";
    if(k_ms165 == value)
        return "ms165";
    if(k_ms170 == value)
        return "ms170";
    if(k_ms175 == value)
        return "ms175";
    if(k_ms180 == value)
        return "ms180";
    if(k_ms185 == value)
        return "ms185";
    if(k_ms190 == value)
        return "ms190";
    if(k_ms195 == value)
        return "ms195";
    if(k_ms200 == value)
        return "ms200";
    if(k_ms205 == value)
        return "ms205";
    if(k_ms210 == value)
        return "ms210";
    if(k_ms215 == value)
        return "ms215";
    if(k_ms220 == value)
        return "ms220";
    if(k_ms225 == value)
        return "ms225";
    if(k_ms230 == value)
        return "ms230";
    if(k_ms235 == value)
        return "ms235";
    if(k_ms240 == value)
        return "ms240";
    if(k_ms245 == value)
        return "ms245";
    if(k_ms250 == value)
        return "ms250";
    if(k_ms300 == value)
        return "ms300";
    if(k_ms350 == value)
        return "ms350";
    if(k_ms400 == value)
        return "ms400";
    if(k_ms450 == value)
        return "ms450";
    if(k_ms500 == value)
        return "ms500";
    if(k_spare8 == value)
        return "spare8";
    if(k_spare7 == value)
        return "spare7";
    if(k_spare6 == value)
        return "spare6";
    if(k_spare5 == value)
        return "spare5";
    if(k_spare4 == value)
        return "spare4";
    if(k_spare3 == value)
        return "spare3";
    if(k_spare2 == value)
        return "spare2";
    if(k_spare1 == value)
        return "spare1";
    return "";
}

uint64_t T_StatusProhibit::NumberOfValues() const
{
    return 64;
}

std::string T_StatusProhibit::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "T_StatusProhibit = " + ValueToString(internal_value) + "\n";
    return out;
}

std::string T_StatusProhibit::ToStringNoNewLines() const
{
    std::string out = "T_StatusProhibit=" + ValueToString(internal_value) + ",";
    return out;
}

int T_StatusProhibit::Clear()
{
    present = false;
    return 0;
}

bool T_StatusProhibit::IsPresent() const
{
    return present;
}

