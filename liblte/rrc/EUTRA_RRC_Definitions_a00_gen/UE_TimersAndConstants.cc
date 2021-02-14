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

#include "UE_TimersAndConstants.h"

#include <cmath>

int UE_TimersAndConstants::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator
    bits.push_back(0);

    // Optional indicators

    // Fields
    {
        if(0 != t300_Pack(bits))
        {
            printf("UE_TimersAndConstants:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != t301_Pack(bits))
        {
            printf("UE_TimersAndConstants:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != t310_Pack(bits))
        {
            printf("UE_TimersAndConstants:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != n310_Pack(bits))
        {
            printf("UE_TimersAndConstants:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != t311_Pack(bits))
        {
            printf("UE_TimersAndConstants:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != n311_Pack(bits))
        {
            printf("UE_TimersAndConstants:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int UE_TimersAndConstants::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int UE_TimersAndConstants::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("UE_TimersAndConstants::Unpack() index out of bounds for extension\n");
        return -1;
    }
    idx++;

    // Optional indicators

    // Fields
    {
        if(0 != t300_Unpack(bits, idx))
        {
            printf("UE_TimersAndConstants:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != t301_Unpack(bits, idx))
        {
            printf("UE_TimersAndConstants:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != t310_Unpack(bits, idx))
        {
            printf("UE_TimersAndConstants:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != n310_Unpack(bits, idx))
        {
            printf("UE_TimersAndConstants:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != t311_Unpack(bits, idx))
        {
            printf("UE_TimersAndConstants:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != n311_Unpack(bits, idx))
        {
            printf("UE_TimersAndConstants:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string UE_TimersAndConstants::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "UE_TimersAndConstants:\n";
    out += t300_ToString(indent+1);
    out += t301_ToString(indent+1);
    out += t310_ToString(indent+1);
    out += n310_ToString(indent+1);
    out += t311_ToString(indent+1);
    out += n311_ToString(indent+1);
    return out;
}

std::string UE_TimersAndConstants::ToStringNoNewLines() const
{
    std::string out = "UE_TimersAndConstants:";
    out += t300_ToStringNoNewLines();
    out += t301_ToStringNoNewLines();
    out += t310_ToStringNoNewLines();
    out += n310_ToStringNoNewLines();
    out += t311_ToStringNoNewLines();
    out += n311_ToStringNoNewLines();
    return out;
}

int UE_TimersAndConstants::t300_Pack(std::vector<uint8_t> &bits)
{
    if(!t300_present)
    {
        printf("UE_TimersAndConstants::t300_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 3;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((t300_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int UE_TimersAndConstants::t300_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return t300_Unpack(bits, idx);
}

int UE_TimersAndConstants::t300_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 3;
    if((idx + N_bits) > bits.size())
    {
        printf("UE_TimersAndConstants::t300_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 7)
    {
        printf("UE_TimersAndConstants::t300_Unpack() max failure\n");
        return -1;
    }
    t300_internal_value = (t300_Enum)packed_val;
    t300_present = true;
    return 0;
}

UE_TimersAndConstants::t300_Enum UE_TimersAndConstants::t300_Value() const
{
    if(t300_present)
        return t300_internal_value;
    return (UE_TimersAndConstants::t300_Enum)0;
}

int UE_TimersAndConstants::t300_SetValue(t300_Enum value)
{
    t300_internal_value = value;
    t300_present = true;
    return 0;
}

int UE_TimersAndConstants::t300_SetValue(std::string value)
{
    if("ms100" == value)
    {
        t300_internal_value = k_t300_ms100;
        t300_present = true;
        return 0;
    }
    if("ms200" == value)
    {
        t300_internal_value = k_t300_ms200;
        t300_present = true;
        return 0;
    }
    if("ms300" == value)
    {
        t300_internal_value = k_t300_ms300;
        t300_present = true;
        return 0;
    }
    if("ms400" == value)
    {
        t300_internal_value = k_t300_ms400;
        t300_present = true;
        return 0;
    }
    if("ms600" == value)
    {
        t300_internal_value = k_t300_ms600;
        t300_present = true;
        return 0;
    }
    if("ms1000" == value)
    {
        t300_internal_value = k_t300_ms1000;
        t300_present = true;
        return 0;
    }
    if("ms1500" == value)
    {
        t300_internal_value = k_t300_ms1500;
        t300_present = true;
        return 0;
    }
    if("ms2000" == value)
    {
        t300_internal_value = k_t300_ms2000;
        t300_present = true;
        return 0;
    }
    return 1;
}

std::string UE_TimersAndConstants::t300_ValueToString(t300_Enum value) const
{
    if(k_t300_ms100 == value)
        return "ms100";
    if(k_t300_ms200 == value)
        return "ms200";
    if(k_t300_ms300 == value)
        return "ms300";
    if(k_t300_ms400 == value)
        return "ms400";
    if(k_t300_ms600 == value)
        return "ms600";
    if(k_t300_ms1000 == value)
        return "ms1000";
    if(k_t300_ms1500 == value)
        return "ms1500";
    if(k_t300_ms2000 == value)
        return "ms2000";
    return "";
}

uint64_t UE_TimersAndConstants::t300_NumberOfValues() const
{
    return 8;
}

std::string UE_TimersAndConstants::t300_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "t300 = " + t300_ValueToString(t300_internal_value) + "\n";
    return out;
}

std::string UE_TimersAndConstants::t300_ToStringNoNewLines() const
{
    std::string out = "t300=" + t300_ValueToString(t300_internal_value) + ",";
    return out;
}

int UE_TimersAndConstants::t300_Clear()
{
    t300_present = false;
    return 0;
}

bool UE_TimersAndConstants::t300_IsPresent() const
{
    return t300_present;
}

int UE_TimersAndConstants::t301_Pack(std::vector<uint8_t> &bits)
{
    if(!t301_present)
    {
        printf("UE_TimersAndConstants::t301_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 3;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((t301_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int UE_TimersAndConstants::t301_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return t301_Unpack(bits, idx);
}

int UE_TimersAndConstants::t301_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 3;
    if((idx + N_bits) > bits.size())
    {
        printf("UE_TimersAndConstants::t301_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 7)
    {
        printf("UE_TimersAndConstants::t301_Unpack() max failure\n");
        return -1;
    }
    t301_internal_value = (t301_Enum)packed_val;
    t301_present = true;
    return 0;
}

UE_TimersAndConstants::t301_Enum UE_TimersAndConstants::t301_Value() const
{
    if(t301_present)
        return t301_internal_value;
    return (UE_TimersAndConstants::t301_Enum)0;
}

int UE_TimersAndConstants::t301_SetValue(t301_Enum value)
{
    t301_internal_value = value;
    t301_present = true;
    return 0;
}

int UE_TimersAndConstants::t301_SetValue(std::string value)
{
    if("ms100" == value)
    {
        t301_internal_value = k_t301_ms100;
        t301_present = true;
        return 0;
    }
    if("ms200" == value)
    {
        t301_internal_value = k_t301_ms200;
        t301_present = true;
        return 0;
    }
    if("ms300" == value)
    {
        t301_internal_value = k_t301_ms300;
        t301_present = true;
        return 0;
    }
    if("ms400" == value)
    {
        t301_internal_value = k_t301_ms400;
        t301_present = true;
        return 0;
    }
    if("ms600" == value)
    {
        t301_internal_value = k_t301_ms600;
        t301_present = true;
        return 0;
    }
    if("ms1000" == value)
    {
        t301_internal_value = k_t301_ms1000;
        t301_present = true;
        return 0;
    }
    if("ms1500" == value)
    {
        t301_internal_value = k_t301_ms1500;
        t301_present = true;
        return 0;
    }
    if("ms2000" == value)
    {
        t301_internal_value = k_t301_ms2000;
        t301_present = true;
        return 0;
    }
    return 1;
}

std::string UE_TimersAndConstants::t301_ValueToString(t301_Enum value) const
{
    if(k_t301_ms100 == value)
        return "ms100";
    if(k_t301_ms200 == value)
        return "ms200";
    if(k_t301_ms300 == value)
        return "ms300";
    if(k_t301_ms400 == value)
        return "ms400";
    if(k_t301_ms600 == value)
        return "ms600";
    if(k_t301_ms1000 == value)
        return "ms1000";
    if(k_t301_ms1500 == value)
        return "ms1500";
    if(k_t301_ms2000 == value)
        return "ms2000";
    return "";
}

uint64_t UE_TimersAndConstants::t301_NumberOfValues() const
{
    return 8;
}

std::string UE_TimersAndConstants::t301_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "t301 = " + t301_ValueToString(t301_internal_value) + "\n";
    return out;
}

std::string UE_TimersAndConstants::t301_ToStringNoNewLines() const
{
    std::string out = "t301=" + t301_ValueToString(t301_internal_value) + ",";
    return out;
}

int UE_TimersAndConstants::t301_Clear()
{
    t301_present = false;
    return 0;
}

bool UE_TimersAndConstants::t301_IsPresent() const
{
    return t301_present;
}

int UE_TimersAndConstants::t310_Pack(std::vector<uint8_t> &bits)
{
    if(!t310_present)
    {
        printf("UE_TimersAndConstants::t310_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 3;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((t310_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int UE_TimersAndConstants::t310_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return t310_Unpack(bits, idx);
}

int UE_TimersAndConstants::t310_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 3;
    if((idx + N_bits) > bits.size())
    {
        printf("UE_TimersAndConstants::t310_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 6)
    {
        printf("UE_TimersAndConstants::t310_Unpack() max failure\n");
        return -1;
    }
    t310_internal_value = (t310_Enum)packed_val;
    t310_present = true;
    return 0;
}

UE_TimersAndConstants::t310_Enum UE_TimersAndConstants::t310_Value() const
{
    if(t310_present)
        return t310_internal_value;
    return (UE_TimersAndConstants::t310_Enum)0;
}

int UE_TimersAndConstants::t310_SetValue(t310_Enum value)
{
    t310_internal_value = value;
    t310_present = true;
    return 0;
}

int UE_TimersAndConstants::t310_SetValue(std::string value)
{
    if("ms0" == value)
    {
        t310_internal_value = k_t310_ms0;
        t310_present = true;
        return 0;
    }
    if("ms50" == value)
    {
        t310_internal_value = k_t310_ms50;
        t310_present = true;
        return 0;
    }
    if("ms100" == value)
    {
        t310_internal_value = k_t310_ms100;
        t310_present = true;
        return 0;
    }
    if("ms200" == value)
    {
        t310_internal_value = k_t310_ms200;
        t310_present = true;
        return 0;
    }
    if("ms500" == value)
    {
        t310_internal_value = k_t310_ms500;
        t310_present = true;
        return 0;
    }
    if("ms1000" == value)
    {
        t310_internal_value = k_t310_ms1000;
        t310_present = true;
        return 0;
    }
    if("ms2000" == value)
    {
        t310_internal_value = k_t310_ms2000;
        t310_present = true;
        return 0;
    }
    return 1;
}

std::string UE_TimersAndConstants::t310_ValueToString(t310_Enum value) const
{
    if(k_t310_ms0 == value)
        return "ms0";
    if(k_t310_ms50 == value)
        return "ms50";
    if(k_t310_ms100 == value)
        return "ms100";
    if(k_t310_ms200 == value)
        return "ms200";
    if(k_t310_ms500 == value)
        return "ms500";
    if(k_t310_ms1000 == value)
        return "ms1000";
    if(k_t310_ms2000 == value)
        return "ms2000";
    return "";
}

uint64_t UE_TimersAndConstants::t310_NumberOfValues() const
{
    return 7;
}

std::string UE_TimersAndConstants::t310_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "t310 = " + t310_ValueToString(t310_internal_value) + "\n";
    return out;
}

std::string UE_TimersAndConstants::t310_ToStringNoNewLines() const
{
    std::string out = "t310=" + t310_ValueToString(t310_internal_value) + ",";
    return out;
}

int UE_TimersAndConstants::t310_Clear()
{
    t310_present = false;
    return 0;
}

bool UE_TimersAndConstants::t310_IsPresent() const
{
    return t310_present;
}

int UE_TimersAndConstants::n310_Pack(std::vector<uint8_t> &bits)
{
    if(!n310_present)
    {
        printf("UE_TimersAndConstants::n310_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 3;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((n310_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int UE_TimersAndConstants::n310_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return n310_Unpack(bits, idx);
}

int UE_TimersAndConstants::n310_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 3;
    if((idx + N_bits) > bits.size())
    {
        printf("UE_TimersAndConstants::n310_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 7)
    {
        printf("UE_TimersAndConstants::n310_Unpack() max failure\n");
        return -1;
    }
    n310_internal_value = (n310_Enum)packed_val;
    n310_present = true;
    return 0;
}

UE_TimersAndConstants::n310_Enum UE_TimersAndConstants::n310_Value() const
{
    if(n310_present)
        return n310_internal_value;
    return (UE_TimersAndConstants::n310_Enum)0;
}

int UE_TimersAndConstants::n310_SetValue(n310_Enum value)
{
    n310_internal_value = value;
    n310_present = true;
    return 0;
}

int UE_TimersAndConstants::n310_SetValue(std::string value)
{
    if("n1" == value)
    {
        n310_internal_value = k_n310_n1;
        n310_present = true;
        return 0;
    }
    if("n2" == value)
    {
        n310_internal_value = k_n310_n2;
        n310_present = true;
        return 0;
    }
    if("n3" == value)
    {
        n310_internal_value = k_n310_n3;
        n310_present = true;
        return 0;
    }
    if("n4" == value)
    {
        n310_internal_value = k_n310_n4;
        n310_present = true;
        return 0;
    }
    if("n6" == value)
    {
        n310_internal_value = k_n310_n6;
        n310_present = true;
        return 0;
    }
    if("n8" == value)
    {
        n310_internal_value = k_n310_n8;
        n310_present = true;
        return 0;
    }
    if("n10" == value)
    {
        n310_internal_value = k_n310_n10;
        n310_present = true;
        return 0;
    }
    if("n20" == value)
    {
        n310_internal_value = k_n310_n20;
        n310_present = true;
        return 0;
    }
    return 1;
}

std::string UE_TimersAndConstants::n310_ValueToString(n310_Enum value) const
{
    if(k_n310_n1 == value)
        return "n1";
    if(k_n310_n2 == value)
        return "n2";
    if(k_n310_n3 == value)
        return "n3";
    if(k_n310_n4 == value)
        return "n4";
    if(k_n310_n6 == value)
        return "n6";
    if(k_n310_n8 == value)
        return "n8";
    if(k_n310_n10 == value)
        return "n10";
    if(k_n310_n20 == value)
        return "n20";
    return "";
}

uint64_t UE_TimersAndConstants::n310_NumberOfValues() const
{
    return 8;
}

std::string UE_TimersAndConstants::n310_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "n310 = " + n310_ValueToString(n310_internal_value) + "\n";
    return out;
}

std::string UE_TimersAndConstants::n310_ToStringNoNewLines() const
{
    std::string out = "n310=" + n310_ValueToString(n310_internal_value) + ",";
    return out;
}

int UE_TimersAndConstants::n310_Clear()
{
    n310_present = false;
    return 0;
}

bool UE_TimersAndConstants::n310_IsPresent() const
{
    return n310_present;
}

int UE_TimersAndConstants::t311_Pack(std::vector<uint8_t> &bits)
{
    if(!t311_present)
    {
        printf("UE_TimersAndConstants::t311_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 3;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((t311_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int UE_TimersAndConstants::t311_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return t311_Unpack(bits, idx);
}

int UE_TimersAndConstants::t311_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 3;
    if((idx + N_bits) > bits.size())
    {
        printf("UE_TimersAndConstants::t311_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 6)
    {
        printf("UE_TimersAndConstants::t311_Unpack() max failure\n");
        return -1;
    }
    t311_internal_value = (t311_Enum)packed_val;
    t311_present = true;
    return 0;
}

UE_TimersAndConstants::t311_Enum UE_TimersAndConstants::t311_Value() const
{
    if(t311_present)
        return t311_internal_value;
    return (UE_TimersAndConstants::t311_Enum)0;
}

int UE_TimersAndConstants::t311_SetValue(t311_Enum value)
{
    t311_internal_value = value;
    t311_present = true;
    return 0;
}

int UE_TimersAndConstants::t311_SetValue(std::string value)
{
    if("ms1000" == value)
    {
        t311_internal_value = k_t311_ms1000;
        t311_present = true;
        return 0;
    }
    if("ms3000" == value)
    {
        t311_internal_value = k_t311_ms3000;
        t311_present = true;
        return 0;
    }
    if("ms5000" == value)
    {
        t311_internal_value = k_t311_ms5000;
        t311_present = true;
        return 0;
    }
    if("ms10000" == value)
    {
        t311_internal_value = k_t311_ms10000;
        t311_present = true;
        return 0;
    }
    if("ms15000" == value)
    {
        t311_internal_value = k_t311_ms15000;
        t311_present = true;
        return 0;
    }
    if("ms20000" == value)
    {
        t311_internal_value = k_t311_ms20000;
        t311_present = true;
        return 0;
    }
    if("ms30000" == value)
    {
        t311_internal_value = k_t311_ms30000;
        t311_present = true;
        return 0;
    }
    return 1;
}

std::string UE_TimersAndConstants::t311_ValueToString(t311_Enum value) const
{
    if(k_t311_ms1000 == value)
        return "ms1000";
    if(k_t311_ms3000 == value)
        return "ms3000";
    if(k_t311_ms5000 == value)
        return "ms5000";
    if(k_t311_ms10000 == value)
        return "ms10000";
    if(k_t311_ms15000 == value)
        return "ms15000";
    if(k_t311_ms20000 == value)
        return "ms20000";
    if(k_t311_ms30000 == value)
        return "ms30000";
    return "";
}

uint64_t UE_TimersAndConstants::t311_NumberOfValues() const
{
    return 7;
}

std::string UE_TimersAndConstants::t311_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "t311 = " + t311_ValueToString(t311_internal_value) + "\n";
    return out;
}

std::string UE_TimersAndConstants::t311_ToStringNoNewLines() const
{
    std::string out = "t311=" + t311_ValueToString(t311_internal_value) + ",";
    return out;
}

int UE_TimersAndConstants::t311_Clear()
{
    t311_present = false;
    return 0;
}

bool UE_TimersAndConstants::t311_IsPresent() const
{
    return t311_present;
}

int UE_TimersAndConstants::n311_Pack(std::vector<uint8_t> &bits)
{
    if(!n311_present)
    {
        printf("UE_TimersAndConstants::n311_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 3;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((n311_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int UE_TimersAndConstants::n311_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return n311_Unpack(bits, idx);
}

int UE_TimersAndConstants::n311_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 3;
    if((idx + N_bits) > bits.size())
    {
        printf("UE_TimersAndConstants::n311_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 7)
    {
        printf("UE_TimersAndConstants::n311_Unpack() max failure\n");
        return -1;
    }
    n311_internal_value = (n311_Enum)packed_val;
    n311_present = true;
    return 0;
}

UE_TimersAndConstants::n311_Enum UE_TimersAndConstants::n311_Value() const
{
    if(n311_present)
        return n311_internal_value;
    return (UE_TimersAndConstants::n311_Enum)0;
}

int UE_TimersAndConstants::n311_SetValue(n311_Enum value)
{
    n311_internal_value = value;
    n311_present = true;
    return 0;
}

int UE_TimersAndConstants::n311_SetValue(std::string value)
{
    if("n1" == value)
    {
        n311_internal_value = k_n311_n1;
        n311_present = true;
        return 0;
    }
    if("n2" == value)
    {
        n311_internal_value = k_n311_n2;
        n311_present = true;
        return 0;
    }
    if("n3" == value)
    {
        n311_internal_value = k_n311_n3;
        n311_present = true;
        return 0;
    }
    if("n4" == value)
    {
        n311_internal_value = k_n311_n4;
        n311_present = true;
        return 0;
    }
    if("n5" == value)
    {
        n311_internal_value = k_n311_n5;
        n311_present = true;
        return 0;
    }
    if("n6" == value)
    {
        n311_internal_value = k_n311_n6;
        n311_present = true;
        return 0;
    }
    if("n8" == value)
    {
        n311_internal_value = k_n311_n8;
        n311_present = true;
        return 0;
    }
    if("n10" == value)
    {
        n311_internal_value = k_n311_n10;
        n311_present = true;
        return 0;
    }
    return 1;
}

std::string UE_TimersAndConstants::n311_ValueToString(n311_Enum value) const
{
    if(k_n311_n1 == value)
        return "n1";
    if(k_n311_n2 == value)
        return "n2";
    if(k_n311_n3 == value)
        return "n3";
    if(k_n311_n4 == value)
        return "n4";
    if(k_n311_n5 == value)
        return "n5";
    if(k_n311_n6 == value)
        return "n6";
    if(k_n311_n8 == value)
        return "n8";
    if(k_n311_n10 == value)
        return "n10";
    return "";
}

uint64_t UE_TimersAndConstants::n311_NumberOfValues() const
{
    return 8;
}

std::string UE_TimersAndConstants::n311_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "n311 = " + n311_ValueToString(n311_internal_value) + "\n";
    return out;
}

std::string UE_TimersAndConstants::n311_ToStringNoNewLines() const
{
    std::string out = "n311=" + n311_ValueToString(n311_internal_value) + ",";
    return out;
}

int UE_TimersAndConstants::n311_Clear()
{
    n311_present = false;
    return 0;
}

bool UE_TimersAndConstants::n311_IsPresent() const
{
    return n311_present;
}

