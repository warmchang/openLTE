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

#include "RRCConnectionReject_r8_IEs.h"

#include <cmath>

int RRCConnectionReject_r8_IEs::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(nonCriticalExtension_IsPresent());

    // Fields
    {
        if(0 != waitTime_Pack(bits))
        {
            printf("RRCConnectionReject_r8_IEs:: field pack failure\n");
            return -1;
        }
    }
    if(nonCriticalExtension_IsPresent())
    {
        if(0 != nonCriticalExtension.Pack(bits))
        {
            printf("RRCConnectionReject_r8_IEs:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int RRCConnectionReject_r8_IEs::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int RRCConnectionReject_r8_IEs::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("RRCConnectionReject_r8_IEs::Unpack() index out of bounds for optional indiator nonCriticalExtension\n");
        return -1;
    }
    nonCriticalExtension_present = bits[idx++];

    // Fields
    {
        if(0 != waitTime_Unpack(bits, idx))
        {
            printf("RRCConnectionReject_r8_IEs:: field unpack failure\n");
            return -1;
        }
    }
    if(nonCriticalExtension_present)
    {
        if(0 != nonCriticalExtension.Unpack(bits, idx))
        {
            printf("RRCConnectionReject_r8_IEs:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string RRCConnectionReject_r8_IEs::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "RRCConnectionReject_r8_IEs:\n";
    out += waitTime_ToString(indent+1);
    if(nonCriticalExtension_IsPresent())
        out += nonCriticalExtension_ToString(indent+1);
    return out;
}

std::string RRCConnectionReject_r8_IEs::ToStringNoNewLines() const
{
    std::string out = "RRCConnectionReject_r8_IEs:";
    out += waitTime_ToStringNoNewLines();
    if(nonCriticalExtension_IsPresent())
        out += nonCriticalExtension_ToStringNoNewLines();
    return out;
}

int RRCConnectionReject_r8_IEs::waitTime_Pack(std::vector<uint8_t> &bits)
{
    if(!waitTime_present)
    {
        printf("RRCConnectionReject_r8_IEs::waitTime_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = waitTime_internal_value - (1);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (16 - 1))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int RRCConnectionReject_r8_IEs::waitTime_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return waitTime_Unpack(bits, idx);
}

int RRCConnectionReject_r8_IEs::waitTime_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (16 - 1))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("RRCConnectionReject_r8_IEs::waitTime_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    waitTime_internal_value = packed_val + 1;
    waitTime_present = true;
    return 0;
}

int64_t RRCConnectionReject_r8_IEs::waitTime_Value() const
{
    if(waitTime_present)
        return waitTime_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int RRCConnectionReject_r8_IEs::waitTime_SetValue(int64_t value)
{
    if(value < 1 || value > 16)
    {
        printf("RRCConnectionReject_r8_IEs::waitTime_SetValue() range failure\n");
        return -1;
    }
    waitTime_internal_value = value;
    waitTime_present = true;
    return 0;
}

std::string RRCConnectionReject_r8_IEs::waitTime_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "waitTime = " + std::to_string(waitTime_internal_value) + "\n";
    return out;
}

std::string RRCConnectionReject_r8_IEs::waitTime_ToStringNoNewLines() const
{
    std::string out = "waitTime=" + std::to_string(waitTime_internal_value) + ",";
    return out;
}

int RRCConnectionReject_r8_IEs::waitTime_Clear()
{
    waitTime_present = false;
    return 0;
}

bool RRCConnectionReject_r8_IEs::waitTime_IsPresent() const
{
    return waitTime_present;
}

RRCConnectionReject_v8a0_IEs* RRCConnectionReject_r8_IEs::nonCriticalExtension_Set()
{
    nonCriticalExtension_present = true;
    return &nonCriticalExtension;
}

int RRCConnectionReject_r8_IEs::nonCriticalExtension_Set(RRCConnectionReject_v8a0_IEs &value)
{
    nonCriticalExtension_present = true;
    nonCriticalExtension = value;
    return 0;
}

const RRCConnectionReject_v8a0_IEs& RRCConnectionReject_r8_IEs::nonCriticalExtension_Get() const
{
    return nonCriticalExtension;
}

std::string RRCConnectionReject_r8_IEs::nonCriticalExtension_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "nonCriticalExtension:\n";
    out += nonCriticalExtension.ToString(indent+1);
    return out;
}

std::string RRCConnectionReject_r8_IEs::nonCriticalExtension_ToStringNoNewLines() const
{
    std::string out = "nonCriticalExtension:";
    out += nonCriticalExtension.ToStringNoNewLines();
    return out;
}

int RRCConnectionReject_r8_IEs::nonCriticalExtension_Clear()
{
    nonCriticalExtension_present = false;
    return 0;
}

bool RRCConnectionReject_r8_IEs::nonCriticalExtension_IsPresent() const
{
    return nonCriticalExtension_present;
}

