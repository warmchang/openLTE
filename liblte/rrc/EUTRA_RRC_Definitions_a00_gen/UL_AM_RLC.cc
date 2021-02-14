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

#include "UL_AM_RLC.h"

#include <cmath>

int UL_AM_RLC::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != t_PollRetransmit.Pack(bits))
        {
            printf("UL_AM_RLC:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != pollPDU.Pack(bits))
        {
            printf("UL_AM_RLC:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != pollByte.Pack(bits))
        {
            printf("UL_AM_RLC:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != maxRetxThreshold_Pack(bits))
        {
            printf("UL_AM_RLC:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int UL_AM_RLC::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int UL_AM_RLC::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != t_PollRetransmit.Unpack(bits, idx))
        {
            printf("UL_AM_RLC:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != pollPDU.Unpack(bits, idx))
        {
            printf("UL_AM_RLC:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != pollByte.Unpack(bits, idx))
        {
            printf("UL_AM_RLC:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != maxRetxThreshold_Unpack(bits, idx))
        {
            printf("UL_AM_RLC:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string UL_AM_RLC::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "UL_AM_RLC:\n";
    out += t_PollRetransmit_ToString(indent+1);
    out += pollPDU_ToString(indent+1);
    out += pollByte_ToString(indent+1);
    out += maxRetxThreshold_ToString(indent+1);
    return out;
}

std::string UL_AM_RLC::ToStringNoNewLines() const
{
    std::string out = "UL_AM_RLC:";
    out += t_PollRetransmit_ToStringNoNewLines();
    out += pollPDU_ToStringNoNewLines();
    out += pollByte_ToStringNoNewLines();
    out += maxRetxThreshold_ToStringNoNewLines();
    return out;
}

T_PollRetransmit* UL_AM_RLC::t_PollRetransmit_Set()
{
    t_PollRetransmit_present = true;
    return &t_PollRetransmit;
}

int UL_AM_RLC::t_PollRetransmit_Set(T_PollRetransmit &value)
{
    t_PollRetransmit_present = true;
    t_PollRetransmit = value;
    return 0;
}

const T_PollRetransmit& UL_AM_RLC::t_PollRetransmit_Get() const
{
    return t_PollRetransmit;
}

std::string UL_AM_RLC::t_PollRetransmit_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "t_PollRetransmit:\n";
    out += t_PollRetransmit.ToString(indent+1);
    return out;
}

std::string UL_AM_RLC::t_PollRetransmit_ToStringNoNewLines() const
{
    std::string out = "t_PollRetransmit:";
    out += t_PollRetransmit.ToStringNoNewLines();
    return out;
}

int UL_AM_RLC::t_PollRetransmit_Clear()
{
    t_PollRetransmit_present = false;
    return 0;
}

bool UL_AM_RLC::t_PollRetransmit_IsPresent() const
{
    return t_PollRetransmit_present;
}

PollPDU* UL_AM_RLC::pollPDU_Set()
{
    pollPDU_present = true;
    return &pollPDU;
}

int UL_AM_RLC::pollPDU_Set(PollPDU &value)
{
    pollPDU_present = true;
    pollPDU = value;
    return 0;
}

const PollPDU& UL_AM_RLC::pollPDU_Get() const
{
    return pollPDU;
}

std::string UL_AM_RLC::pollPDU_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "pollPDU:\n";
    out += pollPDU.ToString(indent+1);
    return out;
}

std::string UL_AM_RLC::pollPDU_ToStringNoNewLines() const
{
    std::string out = "pollPDU:";
    out += pollPDU.ToStringNoNewLines();
    return out;
}

int UL_AM_RLC::pollPDU_Clear()
{
    pollPDU_present = false;
    return 0;
}

bool UL_AM_RLC::pollPDU_IsPresent() const
{
    return pollPDU_present;
}

PollByte* UL_AM_RLC::pollByte_Set()
{
    pollByte_present = true;
    return &pollByte;
}

int UL_AM_RLC::pollByte_Set(PollByte &value)
{
    pollByte_present = true;
    pollByte = value;
    return 0;
}

const PollByte& UL_AM_RLC::pollByte_Get() const
{
    return pollByte;
}

std::string UL_AM_RLC::pollByte_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "pollByte:\n";
    out += pollByte.ToString(indent+1);
    return out;
}

std::string UL_AM_RLC::pollByte_ToStringNoNewLines() const
{
    std::string out = "pollByte:";
    out += pollByte.ToStringNoNewLines();
    return out;
}

int UL_AM_RLC::pollByte_Clear()
{
    pollByte_present = false;
    return 0;
}

bool UL_AM_RLC::pollByte_IsPresent() const
{
    return pollByte_present;
}

int UL_AM_RLC::maxRetxThreshold_Pack(std::vector<uint8_t> &bits)
{
    if(!maxRetxThreshold_present)
    {
        printf("UL_AM_RLC::maxRetxThreshold_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 3;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((maxRetxThreshold_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int UL_AM_RLC::maxRetxThreshold_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return maxRetxThreshold_Unpack(bits, idx);
}

int UL_AM_RLC::maxRetxThreshold_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 3;
    if((idx + N_bits) > bits.size())
    {
        printf("UL_AM_RLC::maxRetxThreshold_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 7)
    {
        printf("UL_AM_RLC::maxRetxThreshold_Unpack() max failure\n");
        return -1;
    }
    maxRetxThreshold_internal_value = (maxRetxThreshold_Enum)packed_val;
    maxRetxThreshold_present = true;
    return 0;
}

UL_AM_RLC::maxRetxThreshold_Enum UL_AM_RLC::maxRetxThreshold_Value() const
{
    if(maxRetxThreshold_present)
        return maxRetxThreshold_internal_value;
    return (UL_AM_RLC::maxRetxThreshold_Enum)0;
}

int UL_AM_RLC::maxRetxThreshold_SetValue(maxRetxThreshold_Enum value)
{
    maxRetxThreshold_internal_value = value;
    maxRetxThreshold_present = true;
    return 0;
}

int UL_AM_RLC::maxRetxThreshold_SetValue(std::string value)
{
    if("t1" == value)
    {
        maxRetxThreshold_internal_value = k_maxRetxThreshold_t1;
        maxRetxThreshold_present = true;
        return 0;
    }
    if("t2" == value)
    {
        maxRetxThreshold_internal_value = k_maxRetxThreshold_t2;
        maxRetxThreshold_present = true;
        return 0;
    }
    if("t3" == value)
    {
        maxRetxThreshold_internal_value = k_maxRetxThreshold_t3;
        maxRetxThreshold_present = true;
        return 0;
    }
    if("t4" == value)
    {
        maxRetxThreshold_internal_value = k_maxRetxThreshold_t4;
        maxRetxThreshold_present = true;
        return 0;
    }
    if("t6" == value)
    {
        maxRetxThreshold_internal_value = k_maxRetxThreshold_t6;
        maxRetxThreshold_present = true;
        return 0;
    }
    if("t8" == value)
    {
        maxRetxThreshold_internal_value = k_maxRetxThreshold_t8;
        maxRetxThreshold_present = true;
        return 0;
    }
    if("t16" == value)
    {
        maxRetxThreshold_internal_value = k_maxRetxThreshold_t16;
        maxRetxThreshold_present = true;
        return 0;
    }
    if("t32" == value)
    {
        maxRetxThreshold_internal_value = k_maxRetxThreshold_t32;
        maxRetxThreshold_present = true;
        return 0;
    }
    return 1;
}

std::string UL_AM_RLC::maxRetxThreshold_ValueToString(maxRetxThreshold_Enum value) const
{
    if(k_maxRetxThreshold_t1 == value)
        return "t1";
    if(k_maxRetxThreshold_t2 == value)
        return "t2";
    if(k_maxRetxThreshold_t3 == value)
        return "t3";
    if(k_maxRetxThreshold_t4 == value)
        return "t4";
    if(k_maxRetxThreshold_t6 == value)
        return "t6";
    if(k_maxRetxThreshold_t8 == value)
        return "t8";
    if(k_maxRetxThreshold_t16 == value)
        return "t16";
    if(k_maxRetxThreshold_t32 == value)
        return "t32";
    return "";
}

uint64_t UL_AM_RLC::maxRetxThreshold_NumberOfValues() const
{
    return 8;
}

std::string UL_AM_RLC::maxRetxThreshold_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "maxRetxThreshold = " + maxRetxThreshold_ValueToString(maxRetxThreshold_internal_value) + "\n";
    return out;
}

std::string UL_AM_RLC::maxRetxThreshold_ToStringNoNewLines() const
{
    std::string out = "maxRetxThreshold=" + maxRetxThreshold_ValueToString(maxRetxThreshold_internal_value) + ",";
    return out;
}

int UL_AM_RLC::maxRetxThreshold_Clear()
{
    maxRetxThreshold_present = false;
    return 0;
}

bool UL_AM_RLC::maxRetxThreshold_IsPresent() const
{
    return maxRetxThreshold_present;
}

