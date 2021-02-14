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

#include "RLF_TimersAndConstants_r9.h"

#include <cmath>

int RLF_TimersAndConstants_r9::Pack(std::vector<uint8_t> &bits)
{
    if(!present)
    {
        printf("RLF_TimersAndConstants_r9::Pack() presence failure\n");
        return -1;
    }
    // Extension indicator

    // Choice
    for(uint32_t i=0; i<1; i++)
        bits.push_back((internal_choice >> (1-i-1)) & 1);

    // Fields
    if(internal_choice == k_release)
    {
        if(0 != release_Pack(bits))
        {
            printf("RLF_TimersAndConstants_r9::release pack failure\n");
            return -1;
        }
    }
    if(internal_choice == k_setup)
    {
        if(0 != setup_value.Pack(bits))
        {
            printf("RLF_TimersAndConstants_r9::setup pack failure\n");
            return -1;
        }
    }
    return 0;
}

int RLF_TimersAndConstants_r9::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int RLF_TimersAndConstants_r9::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 1) > bits.size())
    {
        printf("RLF_TimersAndConstants_r9::Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<1; i++)
        packed_val |= bits[idx++] << (1-i-1);

    if((RLF_TimersAndConstants_r9::Enum)packed_val > k_setup)
    {
        printf("RLF_TimersAndConstants_r9::Unpack() choice range failure\n");
        return -1;
    }
    internal_choice = (RLF_TimersAndConstants_r9::Enum)packed_val;
    present = true;

    // Fields
    if(internal_choice == k_release)
    {
        if(0 != release_Unpack(bits, idx))
        {
            printf("RLF_TimersAndConstants_r9::release unpack failure\n");
            return -1;
        }
    }
    if(internal_choice == k_setup)
    {
        if(0 != setup_value.Unpack(bits, idx))
        {
            printf("RLF_TimersAndConstants_r9::setup unpack failure\n");
            return -1;
        }
    }
    return 0;
}

RLF_TimersAndConstants_r9::Enum RLF_TimersAndConstants_r9::Choice() const
{
    if(present)
        return internal_choice;
    return (RLF_TimersAndConstants_r9::Enum)0;
}

int RLF_TimersAndConstants_r9::SetChoice(RLF_TimersAndConstants_r9::Enum choice)
{
    internal_choice = choice;
    present = true;
    return 0;
}

std::string RLF_TimersAndConstants_r9::ChoiceToString(Enum value) const
{
    if(k_release == value)
        return "release";
    if(k_setup == value)
        return "setup";
    return "";
}

uint64_t RLF_TimersAndConstants_r9::NumberOfChoices() const
{
    return 2;
}

std::string RLF_TimersAndConstants_r9::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "RLF_TimersAndConstants_r9 = " + ChoiceToString(internal_choice) + ":\n";
    if(internal_choice == k_setup)
        out += setup_value.ToString(indent+1);
    return out;
}

std::string RLF_TimersAndConstants_r9::ToStringNoNewLines() const
{
    std::string out = "RLF_TimersAndConstants_r9=" + ChoiceToString(internal_choice) + ",";
    if(internal_choice == k_setup)
        out += setup_value.ToStringNoNewLines();
    return out;
}

int RLF_TimersAndConstants_r9::Clear()
{
    present = false;
    return 0;
}

bool RLF_TimersAndConstants_r9::IsPresent() const
{
    return present;
}

int RLF_TimersAndConstants_r9::setup::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator
    bits.push_back(0);

    // Optional indicators

    // Fields
    {
        if(0 != t301_r9_Pack(bits))
        {
            printf("RLF_TimersAndConstants_r9::setup:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != t310_r9_Pack(bits))
        {
            printf("RLF_TimersAndConstants_r9::setup:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != n310_r9_Pack(bits))
        {
            printf("RLF_TimersAndConstants_r9::setup:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != t311_r9_Pack(bits))
        {
            printf("RLF_TimersAndConstants_r9::setup:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != n311_r9_Pack(bits))
        {
            printf("RLF_TimersAndConstants_r9::setup:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int RLF_TimersAndConstants_r9::setup::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int RLF_TimersAndConstants_r9::setup::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("setup::Unpack() index out of bounds for extension\n");
        return -1;
    }
    idx++;

    // Optional indicators

    // Fields
    {
        if(0 != t301_r9_Unpack(bits, idx))
        {
            printf("RLF_TimersAndConstants_r9::setup:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != t310_r9_Unpack(bits, idx))
        {
            printf("RLF_TimersAndConstants_r9::setup:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != n310_r9_Unpack(bits, idx))
        {
            printf("RLF_TimersAndConstants_r9::setup:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != t311_r9_Unpack(bits, idx))
        {
            printf("RLF_TimersAndConstants_r9::setup:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != n311_r9_Unpack(bits, idx))
        {
            printf("RLF_TimersAndConstants_r9::setup:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string RLF_TimersAndConstants_r9::setup::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "setup:\n";
    out += t301_r9_ToString(indent+1);
    out += t310_r9_ToString(indent+1);
    out += n310_r9_ToString(indent+1);
    out += t311_r9_ToString(indent+1);
    out += n311_r9_ToString(indent+1);
    return out;
}

std::string RLF_TimersAndConstants_r9::setup::ToStringNoNewLines() const
{
    std::string out = "setup:";
    out += t301_r9_ToStringNoNewLines();
    out += t310_r9_ToStringNoNewLines();
    out += n310_r9_ToStringNoNewLines();
    out += t311_r9_ToStringNoNewLines();
    out += n311_r9_ToStringNoNewLines();
    return out;
}

int RLF_TimersAndConstants_r9::setup::t301_r9_Pack(std::vector<uint8_t> &bits)
{
    if(!t301_r9_present)
    {
        printf("RLF_TimersAndConstants_r9::setup::t301_r9_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 3;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((t301_r9_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int RLF_TimersAndConstants_r9::setup::t301_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return t301_r9_Unpack(bits, idx);
}

int RLF_TimersAndConstants_r9::setup::t301_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 3;
    if((idx + N_bits) > bits.size())
    {
        printf("RLF_TimersAndConstants_r9::setup::t301_r9_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 7)
    {
        printf("RLF_TimersAndConstants_r9::setup::t301_r9_Unpack() max failure\n");
        return -1;
    }
    t301_r9_internal_value = (t301_r9_Enum)packed_val;
    t301_r9_present = true;
    return 0;
}

RLF_TimersAndConstants_r9::setup::t301_r9_Enum RLF_TimersAndConstants_r9::setup::t301_r9_Value() const
{
    if(t301_r9_present)
        return t301_r9_internal_value;
    return (RLF_TimersAndConstants_r9::setup::t301_r9_Enum)0;
}

int RLF_TimersAndConstants_r9::setup::t301_r9_SetValue(t301_r9_Enum value)
{
    t301_r9_internal_value = value;
    t301_r9_present = true;
    return 0;
}

int RLF_TimersAndConstants_r9::setup::t301_r9_SetValue(std::string value)
{
    if("ms100" == value)
    {
        t301_r9_internal_value = k_t301_r9_ms100;
        t301_r9_present = true;
        return 0;
    }
    if("ms200" == value)
    {
        t301_r9_internal_value = k_t301_r9_ms200;
        t301_r9_present = true;
        return 0;
    }
    if("ms300" == value)
    {
        t301_r9_internal_value = k_t301_r9_ms300;
        t301_r9_present = true;
        return 0;
    }
    if("ms400" == value)
    {
        t301_r9_internal_value = k_t301_r9_ms400;
        t301_r9_present = true;
        return 0;
    }
    if("ms600" == value)
    {
        t301_r9_internal_value = k_t301_r9_ms600;
        t301_r9_present = true;
        return 0;
    }
    if("ms1000" == value)
    {
        t301_r9_internal_value = k_t301_r9_ms1000;
        t301_r9_present = true;
        return 0;
    }
    if("ms1500" == value)
    {
        t301_r9_internal_value = k_t301_r9_ms1500;
        t301_r9_present = true;
        return 0;
    }
    if("ms2000" == value)
    {
        t301_r9_internal_value = k_t301_r9_ms2000;
        t301_r9_present = true;
        return 0;
    }
    return 1;
}

std::string RLF_TimersAndConstants_r9::setup::t301_r9_ValueToString(t301_r9_Enum value) const
{
    if(k_t301_r9_ms100 == value)
        return "ms100";
    if(k_t301_r9_ms200 == value)
        return "ms200";
    if(k_t301_r9_ms300 == value)
        return "ms300";
    if(k_t301_r9_ms400 == value)
        return "ms400";
    if(k_t301_r9_ms600 == value)
        return "ms600";
    if(k_t301_r9_ms1000 == value)
        return "ms1000";
    if(k_t301_r9_ms1500 == value)
        return "ms1500";
    if(k_t301_r9_ms2000 == value)
        return "ms2000";
    return "";
}

uint64_t RLF_TimersAndConstants_r9::setup::t301_r9_NumberOfValues() const
{
    return 8;
}

std::string RLF_TimersAndConstants_r9::setup::t301_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "t301_r9 = " + t301_r9_ValueToString(t301_r9_internal_value) + "\n";
    return out;
}

std::string RLF_TimersAndConstants_r9::setup::t301_r9_ToStringNoNewLines() const
{
    std::string out = "t301_r9=" + t301_r9_ValueToString(t301_r9_internal_value) + ",";
    return out;
}

int RLF_TimersAndConstants_r9::setup::t301_r9_Clear()
{
    t301_r9_present = false;
    return 0;
}

bool RLF_TimersAndConstants_r9::setup::t301_r9_IsPresent() const
{
    return t301_r9_present;
}

int RLF_TimersAndConstants_r9::setup::t310_r9_Pack(std::vector<uint8_t> &bits)
{
    if(!t310_r9_present)
    {
        printf("RLF_TimersAndConstants_r9::setup::t310_r9_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 3;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((t310_r9_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int RLF_TimersAndConstants_r9::setup::t310_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return t310_r9_Unpack(bits, idx);
}

int RLF_TimersAndConstants_r9::setup::t310_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 3;
    if((idx + N_bits) > bits.size())
    {
        printf("RLF_TimersAndConstants_r9::setup::t310_r9_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 6)
    {
        printf("RLF_TimersAndConstants_r9::setup::t310_r9_Unpack() max failure\n");
        return -1;
    }
    t310_r9_internal_value = (t310_r9_Enum)packed_val;
    t310_r9_present = true;
    return 0;
}

RLF_TimersAndConstants_r9::setup::t310_r9_Enum RLF_TimersAndConstants_r9::setup::t310_r9_Value() const
{
    if(t310_r9_present)
        return t310_r9_internal_value;
    return (RLF_TimersAndConstants_r9::setup::t310_r9_Enum)0;
}

int RLF_TimersAndConstants_r9::setup::t310_r9_SetValue(t310_r9_Enum value)
{
    t310_r9_internal_value = value;
    t310_r9_present = true;
    return 0;
}

int RLF_TimersAndConstants_r9::setup::t310_r9_SetValue(std::string value)
{
    if("ms0" == value)
    {
        t310_r9_internal_value = k_t310_r9_ms0;
        t310_r9_present = true;
        return 0;
    }
    if("ms50" == value)
    {
        t310_r9_internal_value = k_t310_r9_ms50;
        t310_r9_present = true;
        return 0;
    }
    if("ms100" == value)
    {
        t310_r9_internal_value = k_t310_r9_ms100;
        t310_r9_present = true;
        return 0;
    }
    if("ms200" == value)
    {
        t310_r9_internal_value = k_t310_r9_ms200;
        t310_r9_present = true;
        return 0;
    }
    if("ms500" == value)
    {
        t310_r9_internal_value = k_t310_r9_ms500;
        t310_r9_present = true;
        return 0;
    }
    if("ms1000" == value)
    {
        t310_r9_internal_value = k_t310_r9_ms1000;
        t310_r9_present = true;
        return 0;
    }
    if("ms2000" == value)
    {
        t310_r9_internal_value = k_t310_r9_ms2000;
        t310_r9_present = true;
        return 0;
    }
    return 1;
}

std::string RLF_TimersAndConstants_r9::setup::t310_r9_ValueToString(t310_r9_Enum value) const
{
    if(k_t310_r9_ms0 == value)
        return "ms0";
    if(k_t310_r9_ms50 == value)
        return "ms50";
    if(k_t310_r9_ms100 == value)
        return "ms100";
    if(k_t310_r9_ms200 == value)
        return "ms200";
    if(k_t310_r9_ms500 == value)
        return "ms500";
    if(k_t310_r9_ms1000 == value)
        return "ms1000";
    if(k_t310_r9_ms2000 == value)
        return "ms2000";
    return "";
}

uint64_t RLF_TimersAndConstants_r9::setup::t310_r9_NumberOfValues() const
{
    return 7;
}

std::string RLF_TimersAndConstants_r9::setup::t310_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "t310_r9 = " + t310_r9_ValueToString(t310_r9_internal_value) + "\n";
    return out;
}

std::string RLF_TimersAndConstants_r9::setup::t310_r9_ToStringNoNewLines() const
{
    std::string out = "t310_r9=" + t310_r9_ValueToString(t310_r9_internal_value) + ",";
    return out;
}

int RLF_TimersAndConstants_r9::setup::t310_r9_Clear()
{
    t310_r9_present = false;
    return 0;
}

bool RLF_TimersAndConstants_r9::setup::t310_r9_IsPresent() const
{
    return t310_r9_present;
}

int RLF_TimersAndConstants_r9::setup::n310_r9_Pack(std::vector<uint8_t> &bits)
{
    if(!n310_r9_present)
    {
        printf("RLF_TimersAndConstants_r9::setup::n310_r9_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 3;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((n310_r9_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int RLF_TimersAndConstants_r9::setup::n310_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return n310_r9_Unpack(bits, idx);
}

int RLF_TimersAndConstants_r9::setup::n310_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 3;
    if((idx + N_bits) > bits.size())
    {
        printf("RLF_TimersAndConstants_r9::setup::n310_r9_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 7)
    {
        printf("RLF_TimersAndConstants_r9::setup::n310_r9_Unpack() max failure\n");
        return -1;
    }
    n310_r9_internal_value = (n310_r9_Enum)packed_val;
    n310_r9_present = true;
    return 0;
}

RLF_TimersAndConstants_r9::setup::n310_r9_Enum RLF_TimersAndConstants_r9::setup::n310_r9_Value() const
{
    if(n310_r9_present)
        return n310_r9_internal_value;
    return (RLF_TimersAndConstants_r9::setup::n310_r9_Enum)0;
}

int RLF_TimersAndConstants_r9::setup::n310_r9_SetValue(n310_r9_Enum value)
{
    n310_r9_internal_value = value;
    n310_r9_present = true;
    return 0;
}

int RLF_TimersAndConstants_r9::setup::n310_r9_SetValue(std::string value)
{
    if("n1" == value)
    {
        n310_r9_internal_value = k_n310_r9_n1;
        n310_r9_present = true;
        return 0;
    }
    if("n2" == value)
    {
        n310_r9_internal_value = k_n310_r9_n2;
        n310_r9_present = true;
        return 0;
    }
    if("n3" == value)
    {
        n310_r9_internal_value = k_n310_r9_n3;
        n310_r9_present = true;
        return 0;
    }
    if("n4" == value)
    {
        n310_r9_internal_value = k_n310_r9_n4;
        n310_r9_present = true;
        return 0;
    }
    if("n6" == value)
    {
        n310_r9_internal_value = k_n310_r9_n6;
        n310_r9_present = true;
        return 0;
    }
    if("n8" == value)
    {
        n310_r9_internal_value = k_n310_r9_n8;
        n310_r9_present = true;
        return 0;
    }
    if("n10" == value)
    {
        n310_r9_internal_value = k_n310_r9_n10;
        n310_r9_present = true;
        return 0;
    }
    if("n20" == value)
    {
        n310_r9_internal_value = k_n310_r9_n20;
        n310_r9_present = true;
        return 0;
    }
    return 1;
}

std::string RLF_TimersAndConstants_r9::setup::n310_r9_ValueToString(n310_r9_Enum value) const
{
    if(k_n310_r9_n1 == value)
        return "n1";
    if(k_n310_r9_n2 == value)
        return "n2";
    if(k_n310_r9_n3 == value)
        return "n3";
    if(k_n310_r9_n4 == value)
        return "n4";
    if(k_n310_r9_n6 == value)
        return "n6";
    if(k_n310_r9_n8 == value)
        return "n8";
    if(k_n310_r9_n10 == value)
        return "n10";
    if(k_n310_r9_n20 == value)
        return "n20";
    return "";
}

uint64_t RLF_TimersAndConstants_r9::setup::n310_r9_NumberOfValues() const
{
    return 8;
}

std::string RLF_TimersAndConstants_r9::setup::n310_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "n310_r9 = " + n310_r9_ValueToString(n310_r9_internal_value) + "\n";
    return out;
}

std::string RLF_TimersAndConstants_r9::setup::n310_r9_ToStringNoNewLines() const
{
    std::string out = "n310_r9=" + n310_r9_ValueToString(n310_r9_internal_value) + ",";
    return out;
}

int RLF_TimersAndConstants_r9::setup::n310_r9_Clear()
{
    n310_r9_present = false;
    return 0;
}

bool RLF_TimersAndConstants_r9::setup::n310_r9_IsPresent() const
{
    return n310_r9_present;
}

int RLF_TimersAndConstants_r9::setup::t311_r9_Pack(std::vector<uint8_t> &bits)
{
    if(!t311_r9_present)
    {
        printf("RLF_TimersAndConstants_r9::setup::t311_r9_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 3;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((t311_r9_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int RLF_TimersAndConstants_r9::setup::t311_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return t311_r9_Unpack(bits, idx);
}

int RLF_TimersAndConstants_r9::setup::t311_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 3;
    if((idx + N_bits) > bits.size())
    {
        printf("RLF_TimersAndConstants_r9::setup::t311_r9_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 6)
    {
        printf("RLF_TimersAndConstants_r9::setup::t311_r9_Unpack() max failure\n");
        return -1;
    }
    t311_r9_internal_value = (t311_r9_Enum)packed_val;
    t311_r9_present = true;
    return 0;
}

RLF_TimersAndConstants_r9::setup::t311_r9_Enum RLF_TimersAndConstants_r9::setup::t311_r9_Value() const
{
    if(t311_r9_present)
        return t311_r9_internal_value;
    return (RLF_TimersAndConstants_r9::setup::t311_r9_Enum)0;
}

int RLF_TimersAndConstants_r9::setup::t311_r9_SetValue(t311_r9_Enum value)
{
    t311_r9_internal_value = value;
    t311_r9_present = true;
    return 0;
}

int RLF_TimersAndConstants_r9::setup::t311_r9_SetValue(std::string value)
{
    if("ms1000" == value)
    {
        t311_r9_internal_value = k_t311_r9_ms1000;
        t311_r9_present = true;
        return 0;
    }
    if("ms3000" == value)
    {
        t311_r9_internal_value = k_t311_r9_ms3000;
        t311_r9_present = true;
        return 0;
    }
    if("ms5000" == value)
    {
        t311_r9_internal_value = k_t311_r9_ms5000;
        t311_r9_present = true;
        return 0;
    }
    if("ms10000" == value)
    {
        t311_r9_internal_value = k_t311_r9_ms10000;
        t311_r9_present = true;
        return 0;
    }
    if("ms15000" == value)
    {
        t311_r9_internal_value = k_t311_r9_ms15000;
        t311_r9_present = true;
        return 0;
    }
    if("ms20000" == value)
    {
        t311_r9_internal_value = k_t311_r9_ms20000;
        t311_r9_present = true;
        return 0;
    }
    if("ms30000" == value)
    {
        t311_r9_internal_value = k_t311_r9_ms30000;
        t311_r9_present = true;
        return 0;
    }
    return 1;
}

std::string RLF_TimersAndConstants_r9::setup::t311_r9_ValueToString(t311_r9_Enum value) const
{
    if(k_t311_r9_ms1000 == value)
        return "ms1000";
    if(k_t311_r9_ms3000 == value)
        return "ms3000";
    if(k_t311_r9_ms5000 == value)
        return "ms5000";
    if(k_t311_r9_ms10000 == value)
        return "ms10000";
    if(k_t311_r9_ms15000 == value)
        return "ms15000";
    if(k_t311_r9_ms20000 == value)
        return "ms20000";
    if(k_t311_r9_ms30000 == value)
        return "ms30000";
    return "";
}

uint64_t RLF_TimersAndConstants_r9::setup::t311_r9_NumberOfValues() const
{
    return 7;
}

std::string RLF_TimersAndConstants_r9::setup::t311_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "t311_r9 = " + t311_r9_ValueToString(t311_r9_internal_value) + "\n";
    return out;
}

std::string RLF_TimersAndConstants_r9::setup::t311_r9_ToStringNoNewLines() const
{
    std::string out = "t311_r9=" + t311_r9_ValueToString(t311_r9_internal_value) + ",";
    return out;
}

int RLF_TimersAndConstants_r9::setup::t311_r9_Clear()
{
    t311_r9_present = false;
    return 0;
}

bool RLF_TimersAndConstants_r9::setup::t311_r9_IsPresent() const
{
    return t311_r9_present;
}

int RLF_TimersAndConstants_r9::setup::n311_r9_Pack(std::vector<uint8_t> &bits)
{
    if(!n311_r9_present)
    {
        printf("RLF_TimersAndConstants_r9::setup::n311_r9_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 3;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((n311_r9_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int RLF_TimersAndConstants_r9::setup::n311_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return n311_r9_Unpack(bits, idx);
}

int RLF_TimersAndConstants_r9::setup::n311_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 3;
    if((idx + N_bits) > bits.size())
    {
        printf("RLF_TimersAndConstants_r9::setup::n311_r9_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 7)
    {
        printf("RLF_TimersAndConstants_r9::setup::n311_r9_Unpack() max failure\n");
        return -1;
    }
    n311_r9_internal_value = (n311_r9_Enum)packed_val;
    n311_r9_present = true;
    return 0;
}

RLF_TimersAndConstants_r9::setup::n311_r9_Enum RLF_TimersAndConstants_r9::setup::n311_r9_Value() const
{
    if(n311_r9_present)
        return n311_r9_internal_value;
    return (RLF_TimersAndConstants_r9::setup::n311_r9_Enum)0;
}

int RLF_TimersAndConstants_r9::setup::n311_r9_SetValue(n311_r9_Enum value)
{
    n311_r9_internal_value = value;
    n311_r9_present = true;
    return 0;
}

int RLF_TimersAndConstants_r9::setup::n311_r9_SetValue(std::string value)
{
    if("n1" == value)
    {
        n311_r9_internal_value = k_n311_r9_n1;
        n311_r9_present = true;
        return 0;
    }
    if("n2" == value)
    {
        n311_r9_internal_value = k_n311_r9_n2;
        n311_r9_present = true;
        return 0;
    }
    if("n3" == value)
    {
        n311_r9_internal_value = k_n311_r9_n3;
        n311_r9_present = true;
        return 0;
    }
    if("n4" == value)
    {
        n311_r9_internal_value = k_n311_r9_n4;
        n311_r9_present = true;
        return 0;
    }
    if("n5" == value)
    {
        n311_r9_internal_value = k_n311_r9_n5;
        n311_r9_present = true;
        return 0;
    }
    if("n6" == value)
    {
        n311_r9_internal_value = k_n311_r9_n6;
        n311_r9_present = true;
        return 0;
    }
    if("n8" == value)
    {
        n311_r9_internal_value = k_n311_r9_n8;
        n311_r9_present = true;
        return 0;
    }
    if("n10" == value)
    {
        n311_r9_internal_value = k_n311_r9_n10;
        n311_r9_present = true;
        return 0;
    }
    return 1;
}

std::string RLF_TimersAndConstants_r9::setup::n311_r9_ValueToString(n311_r9_Enum value) const
{
    if(k_n311_r9_n1 == value)
        return "n1";
    if(k_n311_r9_n2 == value)
        return "n2";
    if(k_n311_r9_n3 == value)
        return "n3";
    if(k_n311_r9_n4 == value)
        return "n4";
    if(k_n311_r9_n5 == value)
        return "n5";
    if(k_n311_r9_n6 == value)
        return "n6";
    if(k_n311_r9_n8 == value)
        return "n8";
    if(k_n311_r9_n10 == value)
        return "n10";
    return "";
}

uint64_t RLF_TimersAndConstants_r9::setup::n311_r9_NumberOfValues() const
{
    return 8;
}

std::string RLF_TimersAndConstants_r9::setup::n311_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "n311_r9 = " + n311_r9_ValueToString(n311_r9_internal_value) + "\n";
    return out;
}

std::string RLF_TimersAndConstants_r9::setup::n311_r9_ToStringNoNewLines() const
{
    std::string out = "n311_r9=" + n311_r9_ValueToString(n311_r9_internal_value) + ",";
    return out;
}

int RLF_TimersAndConstants_r9::setup::n311_r9_Clear()
{
    n311_r9_present = false;
    return 0;
}

bool RLF_TimersAndConstants_r9::setup::n311_r9_IsPresent() const
{
    return n311_r9_present;
}

