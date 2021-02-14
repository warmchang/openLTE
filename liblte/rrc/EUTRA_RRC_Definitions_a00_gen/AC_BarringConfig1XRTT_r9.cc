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

#include "AC_BarringConfig1XRTT_r9.h"

#include <cmath>

int AC_BarringConfig1XRTT_r9::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != ac_Barring0to9_r9_Pack(bits))
        {
            printf("AC_BarringConfig1XRTT_r9:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != ac_Barring10_r9_Pack(bits))
        {
            printf("AC_BarringConfig1XRTT_r9:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != ac_Barring11_r9_Pack(bits))
        {
            printf("AC_BarringConfig1XRTT_r9:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != ac_Barring12_r9_Pack(bits))
        {
            printf("AC_BarringConfig1XRTT_r9:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != ac_Barring13_r9_Pack(bits))
        {
            printf("AC_BarringConfig1XRTT_r9:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != ac_Barring14_r9_Pack(bits))
        {
            printf("AC_BarringConfig1XRTT_r9:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != ac_Barring15_r9_Pack(bits))
        {
            printf("AC_BarringConfig1XRTT_r9:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != ac_BarringMsg_r9_Pack(bits))
        {
            printf("AC_BarringConfig1XRTT_r9:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != ac_BarringReg_r9_Pack(bits))
        {
            printf("AC_BarringConfig1XRTT_r9:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != ac_BarringEmg_r9_Pack(bits))
        {
            printf("AC_BarringConfig1XRTT_r9:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int AC_BarringConfig1XRTT_r9::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int AC_BarringConfig1XRTT_r9::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != ac_Barring0to9_r9_Unpack(bits, idx))
        {
            printf("AC_BarringConfig1XRTT_r9:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != ac_Barring10_r9_Unpack(bits, idx))
        {
            printf("AC_BarringConfig1XRTT_r9:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != ac_Barring11_r9_Unpack(bits, idx))
        {
            printf("AC_BarringConfig1XRTT_r9:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != ac_Barring12_r9_Unpack(bits, idx))
        {
            printf("AC_BarringConfig1XRTT_r9:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != ac_Barring13_r9_Unpack(bits, idx))
        {
            printf("AC_BarringConfig1XRTT_r9:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != ac_Barring14_r9_Unpack(bits, idx))
        {
            printf("AC_BarringConfig1XRTT_r9:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != ac_Barring15_r9_Unpack(bits, idx))
        {
            printf("AC_BarringConfig1XRTT_r9:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != ac_BarringMsg_r9_Unpack(bits, idx))
        {
            printf("AC_BarringConfig1XRTT_r9:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != ac_BarringReg_r9_Unpack(bits, idx))
        {
            printf("AC_BarringConfig1XRTT_r9:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != ac_BarringEmg_r9_Unpack(bits, idx))
        {
            printf("AC_BarringConfig1XRTT_r9:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string AC_BarringConfig1XRTT_r9::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "AC_BarringConfig1XRTT_r9:\n";
    out += ac_Barring0to9_r9_ToString(indent+1);
    out += ac_Barring10_r9_ToString(indent+1);
    out += ac_Barring11_r9_ToString(indent+1);
    out += ac_Barring12_r9_ToString(indent+1);
    out += ac_Barring13_r9_ToString(indent+1);
    out += ac_Barring14_r9_ToString(indent+1);
    out += ac_Barring15_r9_ToString(indent+1);
    out += ac_BarringMsg_r9_ToString(indent+1);
    out += ac_BarringReg_r9_ToString(indent+1);
    out += ac_BarringEmg_r9_ToString(indent+1);
    return out;
}

std::string AC_BarringConfig1XRTT_r9::ToStringNoNewLines() const
{
    std::string out = "AC_BarringConfig1XRTT_r9:";
    out += ac_Barring0to9_r9_ToStringNoNewLines();
    out += ac_Barring10_r9_ToStringNoNewLines();
    out += ac_Barring11_r9_ToStringNoNewLines();
    out += ac_Barring12_r9_ToStringNoNewLines();
    out += ac_Barring13_r9_ToStringNoNewLines();
    out += ac_Barring14_r9_ToStringNoNewLines();
    out += ac_Barring15_r9_ToStringNoNewLines();
    out += ac_BarringMsg_r9_ToStringNoNewLines();
    out += ac_BarringReg_r9_ToStringNoNewLines();
    out += ac_BarringEmg_r9_ToStringNoNewLines();
    return out;
}

int AC_BarringConfig1XRTT_r9::ac_Barring0to9_r9_Pack(std::vector<uint8_t> &bits)
{
    if(!ac_Barring0to9_r9_present)
    {
        printf("AC_BarringConfig1XRTT_r9::ac_Barring0to9_r9_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = ac_Barring0to9_r9_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (63 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int AC_BarringConfig1XRTT_r9::ac_Barring0to9_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return ac_Barring0to9_r9_Unpack(bits, idx);
}

int AC_BarringConfig1XRTT_r9::ac_Barring0to9_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (63 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("AC_BarringConfig1XRTT_r9::ac_Barring0to9_r9_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    ac_Barring0to9_r9_internal_value = packed_val + 0;
    ac_Barring0to9_r9_present = true;
    return 0;
}

int64_t AC_BarringConfig1XRTT_r9::ac_Barring0to9_r9_Value() const
{
    if(ac_Barring0to9_r9_present)
        return ac_Barring0to9_r9_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int AC_BarringConfig1XRTT_r9::ac_Barring0to9_r9_SetValue(int64_t value)
{
    if(value < 0 || value > 63)
    {
        printf("AC_BarringConfig1XRTT_r9::ac_Barring0to9_r9_SetValue() range failure\n");
        return -1;
    }
    ac_Barring0to9_r9_internal_value = value;
    ac_Barring0to9_r9_present = true;
    return 0;
}

std::string AC_BarringConfig1XRTT_r9::ac_Barring0to9_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ac_Barring0to9_r9 = " + std::to_string(ac_Barring0to9_r9_internal_value) + "\n";
    return out;
}

std::string AC_BarringConfig1XRTT_r9::ac_Barring0to9_r9_ToStringNoNewLines() const
{
    std::string out = "ac_Barring0to9_r9=" + std::to_string(ac_Barring0to9_r9_internal_value) + ",";
    return out;
}

int AC_BarringConfig1XRTT_r9::ac_Barring0to9_r9_Clear()
{
    ac_Barring0to9_r9_present = false;
    return 0;
}

bool AC_BarringConfig1XRTT_r9::ac_Barring0to9_r9_IsPresent() const
{
    return ac_Barring0to9_r9_present;
}

int AC_BarringConfig1XRTT_r9::ac_Barring10_r9_Pack(std::vector<uint8_t> &bits)
{
    if(!ac_Barring10_r9_present)
    {
        printf("AC_BarringConfig1XRTT_r9::ac_Barring10_r9_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = ac_Barring10_r9_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (7 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int AC_BarringConfig1XRTT_r9::ac_Barring10_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return ac_Barring10_r9_Unpack(bits, idx);
}

int AC_BarringConfig1XRTT_r9::ac_Barring10_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (7 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("AC_BarringConfig1XRTT_r9::ac_Barring10_r9_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    ac_Barring10_r9_internal_value = packed_val + 0;
    ac_Barring10_r9_present = true;
    return 0;
}

int64_t AC_BarringConfig1XRTT_r9::ac_Barring10_r9_Value() const
{
    if(ac_Barring10_r9_present)
        return ac_Barring10_r9_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int AC_BarringConfig1XRTT_r9::ac_Barring10_r9_SetValue(int64_t value)
{
    if(value < 0 || value > 7)
    {
        printf("AC_BarringConfig1XRTT_r9::ac_Barring10_r9_SetValue() range failure\n");
        return -1;
    }
    ac_Barring10_r9_internal_value = value;
    ac_Barring10_r9_present = true;
    return 0;
}

std::string AC_BarringConfig1XRTT_r9::ac_Barring10_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ac_Barring10_r9 = " + std::to_string(ac_Barring10_r9_internal_value) + "\n";
    return out;
}

std::string AC_BarringConfig1XRTT_r9::ac_Barring10_r9_ToStringNoNewLines() const
{
    std::string out = "ac_Barring10_r9=" + std::to_string(ac_Barring10_r9_internal_value) + ",";
    return out;
}

int AC_BarringConfig1XRTT_r9::ac_Barring10_r9_Clear()
{
    ac_Barring10_r9_present = false;
    return 0;
}

bool AC_BarringConfig1XRTT_r9::ac_Barring10_r9_IsPresent() const
{
    return ac_Barring10_r9_present;
}

int AC_BarringConfig1XRTT_r9::ac_Barring11_r9_Pack(std::vector<uint8_t> &bits)
{
    if(!ac_Barring11_r9_present)
    {
        printf("AC_BarringConfig1XRTT_r9::ac_Barring11_r9_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = ac_Barring11_r9_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (7 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int AC_BarringConfig1XRTT_r9::ac_Barring11_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return ac_Barring11_r9_Unpack(bits, idx);
}

int AC_BarringConfig1XRTT_r9::ac_Barring11_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (7 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("AC_BarringConfig1XRTT_r9::ac_Barring11_r9_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    ac_Barring11_r9_internal_value = packed_val + 0;
    ac_Barring11_r9_present = true;
    return 0;
}

int64_t AC_BarringConfig1XRTT_r9::ac_Barring11_r9_Value() const
{
    if(ac_Barring11_r9_present)
        return ac_Barring11_r9_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int AC_BarringConfig1XRTT_r9::ac_Barring11_r9_SetValue(int64_t value)
{
    if(value < 0 || value > 7)
    {
        printf("AC_BarringConfig1XRTT_r9::ac_Barring11_r9_SetValue() range failure\n");
        return -1;
    }
    ac_Barring11_r9_internal_value = value;
    ac_Barring11_r9_present = true;
    return 0;
}

std::string AC_BarringConfig1XRTT_r9::ac_Barring11_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ac_Barring11_r9 = " + std::to_string(ac_Barring11_r9_internal_value) + "\n";
    return out;
}

std::string AC_BarringConfig1XRTT_r9::ac_Barring11_r9_ToStringNoNewLines() const
{
    std::string out = "ac_Barring11_r9=" + std::to_string(ac_Barring11_r9_internal_value) + ",";
    return out;
}

int AC_BarringConfig1XRTT_r9::ac_Barring11_r9_Clear()
{
    ac_Barring11_r9_present = false;
    return 0;
}

bool AC_BarringConfig1XRTT_r9::ac_Barring11_r9_IsPresent() const
{
    return ac_Barring11_r9_present;
}

int AC_BarringConfig1XRTT_r9::ac_Barring12_r9_Pack(std::vector<uint8_t> &bits)
{
    if(!ac_Barring12_r9_present)
    {
        printf("AC_BarringConfig1XRTT_r9::ac_Barring12_r9_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = ac_Barring12_r9_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (7 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int AC_BarringConfig1XRTT_r9::ac_Barring12_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return ac_Barring12_r9_Unpack(bits, idx);
}

int AC_BarringConfig1XRTT_r9::ac_Barring12_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (7 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("AC_BarringConfig1XRTT_r9::ac_Barring12_r9_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    ac_Barring12_r9_internal_value = packed_val + 0;
    ac_Barring12_r9_present = true;
    return 0;
}

int64_t AC_BarringConfig1XRTT_r9::ac_Barring12_r9_Value() const
{
    if(ac_Barring12_r9_present)
        return ac_Barring12_r9_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int AC_BarringConfig1XRTT_r9::ac_Barring12_r9_SetValue(int64_t value)
{
    if(value < 0 || value > 7)
    {
        printf("AC_BarringConfig1XRTT_r9::ac_Barring12_r9_SetValue() range failure\n");
        return -1;
    }
    ac_Barring12_r9_internal_value = value;
    ac_Barring12_r9_present = true;
    return 0;
}

std::string AC_BarringConfig1XRTT_r9::ac_Barring12_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ac_Barring12_r9 = " + std::to_string(ac_Barring12_r9_internal_value) + "\n";
    return out;
}

std::string AC_BarringConfig1XRTT_r9::ac_Barring12_r9_ToStringNoNewLines() const
{
    std::string out = "ac_Barring12_r9=" + std::to_string(ac_Barring12_r9_internal_value) + ",";
    return out;
}

int AC_BarringConfig1XRTT_r9::ac_Barring12_r9_Clear()
{
    ac_Barring12_r9_present = false;
    return 0;
}

bool AC_BarringConfig1XRTT_r9::ac_Barring12_r9_IsPresent() const
{
    return ac_Barring12_r9_present;
}

int AC_BarringConfig1XRTT_r9::ac_Barring13_r9_Pack(std::vector<uint8_t> &bits)
{
    if(!ac_Barring13_r9_present)
    {
        printf("AC_BarringConfig1XRTT_r9::ac_Barring13_r9_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = ac_Barring13_r9_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (7 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int AC_BarringConfig1XRTT_r9::ac_Barring13_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return ac_Barring13_r9_Unpack(bits, idx);
}

int AC_BarringConfig1XRTT_r9::ac_Barring13_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (7 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("AC_BarringConfig1XRTT_r9::ac_Barring13_r9_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    ac_Barring13_r9_internal_value = packed_val + 0;
    ac_Barring13_r9_present = true;
    return 0;
}

int64_t AC_BarringConfig1XRTT_r9::ac_Barring13_r9_Value() const
{
    if(ac_Barring13_r9_present)
        return ac_Barring13_r9_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int AC_BarringConfig1XRTT_r9::ac_Barring13_r9_SetValue(int64_t value)
{
    if(value < 0 || value > 7)
    {
        printf("AC_BarringConfig1XRTT_r9::ac_Barring13_r9_SetValue() range failure\n");
        return -1;
    }
    ac_Barring13_r9_internal_value = value;
    ac_Barring13_r9_present = true;
    return 0;
}

std::string AC_BarringConfig1XRTT_r9::ac_Barring13_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ac_Barring13_r9 = " + std::to_string(ac_Barring13_r9_internal_value) + "\n";
    return out;
}

std::string AC_BarringConfig1XRTT_r9::ac_Barring13_r9_ToStringNoNewLines() const
{
    std::string out = "ac_Barring13_r9=" + std::to_string(ac_Barring13_r9_internal_value) + ",";
    return out;
}

int AC_BarringConfig1XRTT_r9::ac_Barring13_r9_Clear()
{
    ac_Barring13_r9_present = false;
    return 0;
}

bool AC_BarringConfig1XRTT_r9::ac_Barring13_r9_IsPresent() const
{
    return ac_Barring13_r9_present;
}

int AC_BarringConfig1XRTT_r9::ac_Barring14_r9_Pack(std::vector<uint8_t> &bits)
{
    if(!ac_Barring14_r9_present)
    {
        printf("AC_BarringConfig1XRTT_r9::ac_Barring14_r9_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = ac_Barring14_r9_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (7 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int AC_BarringConfig1XRTT_r9::ac_Barring14_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return ac_Barring14_r9_Unpack(bits, idx);
}

int AC_BarringConfig1XRTT_r9::ac_Barring14_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (7 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("AC_BarringConfig1XRTT_r9::ac_Barring14_r9_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    ac_Barring14_r9_internal_value = packed_val + 0;
    ac_Barring14_r9_present = true;
    return 0;
}

int64_t AC_BarringConfig1XRTT_r9::ac_Barring14_r9_Value() const
{
    if(ac_Barring14_r9_present)
        return ac_Barring14_r9_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int AC_BarringConfig1XRTT_r9::ac_Barring14_r9_SetValue(int64_t value)
{
    if(value < 0 || value > 7)
    {
        printf("AC_BarringConfig1XRTT_r9::ac_Barring14_r9_SetValue() range failure\n");
        return -1;
    }
    ac_Barring14_r9_internal_value = value;
    ac_Barring14_r9_present = true;
    return 0;
}

std::string AC_BarringConfig1XRTT_r9::ac_Barring14_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ac_Barring14_r9 = " + std::to_string(ac_Barring14_r9_internal_value) + "\n";
    return out;
}

std::string AC_BarringConfig1XRTT_r9::ac_Barring14_r9_ToStringNoNewLines() const
{
    std::string out = "ac_Barring14_r9=" + std::to_string(ac_Barring14_r9_internal_value) + ",";
    return out;
}

int AC_BarringConfig1XRTT_r9::ac_Barring14_r9_Clear()
{
    ac_Barring14_r9_present = false;
    return 0;
}

bool AC_BarringConfig1XRTT_r9::ac_Barring14_r9_IsPresent() const
{
    return ac_Barring14_r9_present;
}

int AC_BarringConfig1XRTT_r9::ac_Barring15_r9_Pack(std::vector<uint8_t> &bits)
{
    if(!ac_Barring15_r9_present)
    {
        printf("AC_BarringConfig1XRTT_r9::ac_Barring15_r9_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = ac_Barring15_r9_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (7 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int AC_BarringConfig1XRTT_r9::ac_Barring15_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return ac_Barring15_r9_Unpack(bits, idx);
}

int AC_BarringConfig1XRTT_r9::ac_Barring15_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (7 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("AC_BarringConfig1XRTT_r9::ac_Barring15_r9_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    ac_Barring15_r9_internal_value = packed_val + 0;
    ac_Barring15_r9_present = true;
    return 0;
}

int64_t AC_BarringConfig1XRTT_r9::ac_Barring15_r9_Value() const
{
    if(ac_Barring15_r9_present)
        return ac_Barring15_r9_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int AC_BarringConfig1XRTT_r9::ac_Barring15_r9_SetValue(int64_t value)
{
    if(value < 0 || value > 7)
    {
        printf("AC_BarringConfig1XRTT_r9::ac_Barring15_r9_SetValue() range failure\n");
        return -1;
    }
    ac_Barring15_r9_internal_value = value;
    ac_Barring15_r9_present = true;
    return 0;
}

std::string AC_BarringConfig1XRTT_r9::ac_Barring15_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ac_Barring15_r9 = " + std::to_string(ac_Barring15_r9_internal_value) + "\n";
    return out;
}

std::string AC_BarringConfig1XRTT_r9::ac_Barring15_r9_ToStringNoNewLines() const
{
    std::string out = "ac_Barring15_r9=" + std::to_string(ac_Barring15_r9_internal_value) + ",";
    return out;
}

int AC_BarringConfig1XRTT_r9::ac_Barring15_r9_Clear()
{
    ac_Barring15_r9_present = false;
    return 0;
}

bool AC_BarringConfig1XRTT_r9::ac_Barring15_r9_IsPresent() const
{
    return ac_Barring15_r9_present;
}

int AC_BarringConfig1XRTT_r9::ac_BarringMsg_r9_Pack(std::vector<uint8_t> &bits)
{
    if(!ac_BarringMsg_r9_present)
    {
        printf("AC_BarringConfig1XRTT_r9::ac_BarringMsg_r9_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = ac_BarringMsg_r9_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (7 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int AC_BarringConfig1XRTT_r9::ac_BarringMsg_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return ac_BarringMsg_r9_Unpack(bits, idx);
}

int AC_BarringConfig1XRTT_r9::ac_BarringMsg_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (7 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("AC_BarringConfig1XRTT_r9::ac_BarringMsg_r9_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    ac_BarringMsg_r9_internal_value = packed_val + 0;
    ac_BarringMsg_r9_present = true;
    return 0;
}

int64_t AC_BarringConfig1XRTT_r9::ac_BarringMsg_r9_Value() const
{
    if(ac_BarringMsg_r9_present)
        return ac_BarringMsg_r9_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int AC_BarringConfig1XRTT_r9::ac_BarringMsg_r9_SetValue(int64_t value)
{
    if(value < 0 || value > 7)
    {
        printf("AC_BarringConfig1XRTT_r9::ac_BarringMsg_r9_SetValue() range failure\n");
        return -1;
    }
    ac_BarringMsg_r9_internal_value = value;
    ac_BarringMsg_r9_present = true;
    return 0;
}

std::string AC_BarringConfig1XRTT_r9::ac_BarringMsg_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ac_BarringMsg_r9 = " + std::to_string(ac_BarringMsg_r9_internal_value) + "\n";
    return out;
}

std::string AC_BarringConfig1XRTT_r9::ac_BarringMsg_r9_ToStringNoNewLines() const
{
    std::string out = "ac_BarringMsg_r9=" + std::to_string(ac_BarringMsg_r9_internal_value) + ",";
    return out;
}

int AC_BarringConfig1XRTT_r9::ac_BarringMsg_r9_Clear()
{
    ac_BarringMsg_r9_present = false;
    return 0;
}

bool AC_BarringConfig1XRTT_r9::ac_BarringMsg_r9_IsPresent() const
{
    return ac_BarringMsg_r9_present;
}

int AC_BarringConfig1XRTT_r9::ac_BarringReg_r9_Pack(std::vector<uint8_t> &bits)
{
    if(!ac_BarringReg_r9_present)
    {
        printf("AC_BarringConfig1XRTT_r9::ac_BarringReg_r9_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = ac_BarringReg_r9_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (7 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int AC_BarringConfig1XRTT_r9::ac_BarringReg_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return ac_BarringReg_r9_Unpack(bits, idx);
}

int AC_BarringConfig1XRTT_r9::ac_BarringReg_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (7 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("AC_BarringConfig1XRTT_r9::ac_BarringReg_r9_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    ac_BarringReg_r9_internal_value = packed_val + 0;
    ac_BarringReg_r9_present = true;
    return 0;
}

int64_t AC_BarringConfig1XRTT_r9::ac_BarringReg_r9_Value() const
{
    if(ac_BarringReg_r9_present)
        return ac_BarringReg_r9_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int AC_BarringConfig1XRTT_r9::ac_BarringReg_r9_SetValue(int64_t value)
{
    if(value < 0 || value > 7)
    {
        printf("AC_BarringConfig1XRTT_r9::ac_BarringReg_r9_SetValue() range failure\n");
        return -1;
    }
    ac_BarringReg_r9_internal_value = value;
    ac_BarringReg_r9_present = true;
    return 0;
}

std::string AC_BarringConfig1XRTT_r9::ac_BarringReg_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ac_BarringReg_r9 = " + std::to_string(ac_BarringReg_r9_internal_value) + "\n";
    return out;
}

std::string AC_BarringConfig1XRTT_r9::ac_BarringReg_r9_ToStringNoNewLines() const
{
    std::string out = "ac_BarringReg_r9=" + std::to_string(ac_BarringReg_r9_internal_value) + ",";
    return out;
}

int AC_BarringConfig1XRTT_r9::ac_BarringReg_r9_Clear()
{
    ac_BarringReg_r9_present = false;
    return 0;
}

bool AC_BarringConfig1XRTT_r9::ac_BarringReg_r9_IsPresent() const
{
    return ac_BarringReg_r9_present;
}

int AC_BarringConfig1XRTT_r9::ac_BarringEmg_r9_Pack(std::vector<uint8_t> &bits)
{
    if(!ac_BarringEmg_r9_present)
    {
        printf("AC_BarringConfig1XRTT_r9::ac_BarringEmg_r9_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = ac_BarringEmg_r9_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (7 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int AC_BarringConfig1XRTT_r9::ac_BarringEmg_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return ac_BarringEmg_r9_Unpack(bits, idx);
}

int AC_BarringConfig1XRTT_r9::ac_BarringEmg_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (7 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("AC_BarringConfig1XRTT_r9::ac_BarringEmg_r9_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    ac_BarringEmg_r9_internal_value = packed_val + 0;
    ac_BarringEmg_r9_present = true;
    return 0;
}

int64_t AC_BarringConfig1XRTT_r9::ac_BarringEmg_r9_Value() const
{
    if(ac_BarringEmg_r9_present)
        return ac_BarringEmg_r9_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int AC_BarringConfig1XRTT_r9::ac_BarringEmg_r9_SetValue(int64_t value)
{
    if(value < 0 || value > 7)
    {
        printf("AC_BarringConfig1XRTT_r9::ac_BarringEmg_r9_SetValue() range failure\n");
        return -1;
    }
    ac_BarringEmg_r9_internal_value = value;
    ac_BarringEmg_r9_present = true;
    return 0;
}

std::string AC_BarringConfig1XRTT_r9::ac_BarringEmg_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ac_BarringEmg_r9 = " + std::to_string(ac_BarringEmg_r9_internal_value) + "\n";
    return out;
}

std::string AC_BarringConfig1XRTT_r9::ac_BarringEmg_r9_ToStringNoNewLines() const
{
    std::string out = "ac_BarringEmg_r9=" + std::to_string(ac_BarringEmg_r9_internal_value) + ",";
    return out;
}

int AC_BarringConfig1XRTT_r9::ac_BarringEmg_r9_Clear()
{
    ac_BarringEmg_r9_present = false;
    return 0;
}

bool AC_BarringConfig1XRTT_r9::ac_BarringEmg_r9_IsPresent() const
{
    return ac_BarringEmg_r9_present;
}

