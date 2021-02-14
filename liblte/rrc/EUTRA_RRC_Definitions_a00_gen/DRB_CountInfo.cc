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

#include "DRB_CountInfo.h"

#include <cmath>

int DRB_CountInfo::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != drb_Identity.Pack(bits))
        {
            printf("DRB_CountInfo:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != count_Uplink_Pack(bits))
        {
            printf("DRB_CountInfo:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != count_Downlink_Pack(bits))
        {
            printf("DRB_CountInfo:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int DRB_CountInfo::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int DRB_CountInfo::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != drb_Identity.Unpack(bits, idx))
        {
            printf("DRB_CountInfo:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != count_Uplink_Unpack(bits, idx))
        {
            printf("DRB_CountInfo:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != count_Downlink_Unpack(bits, idx))
        {
            printf("DRB_CountInfo:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string DRB_CountInfo::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "DRB_CountInfo:\n";
    out += drb_Identity_ToString(indent+1);
    out += count_Uplink_ToString(indent+1);
    out += count_Downlink_ToString(indent+1);
    return out;
}

std::string DRB_CountInfo::ToStringNoNewLines() const
{
    std::string out = "DRB_CountInfo:";
    out += drb_Identity_ToStringNoNewLines();
    out += count_Uplink_ToStringNoNewLines();
    out += count_Downlink_ToStringNoNewLines();
    return out;
}

DRB_Identity* DRB_CountInfo::drb_Identity_Set()
{
    drb_Identity_present = true;
    return &drb_Identity;
}

int DRB_CountInfo::drb_Identity_Set(DRB_Identity &value)
{
    drb_Identity_present = true;
    drb_Identity = value;
    return 0;
}

const DRB_Identity& DRB_CountInfo::drb_Identity_Get() const
{
    return drb_Identity;
}

std::string DRB_CountInfo::drb_Identity_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "drb_Identity:\n";
    out += drb_Identity.ToString(indent+1);
    return out;
}

std::string DRB_CountInfo::drb_Identity_ToStringNoNewLines() const
{
    std::string out = "drb_Identity:";
    out += drb_Identity.ToStringNoNewLines();
    return out;
}

int DRB_CountInfo::drb_Identity_Clear()
{
    drb_Identity_present = false;
    return 0;
}

bool DRB_CountInfo::drb_Identity_IsPresent() const
{
    return drb_Identity_present;
}

int DRB_CountInfo::count_Uplink_Pack(std::vector<uint8_t> &bits)
{
    if(!count_Uplink_present)
    {
        printf("DRB_CountInfo::count_Uplink_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = count_Uplink_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (4294967295 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int DRB_CountInfo::count_Uplink_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return count_Uplink_Unpack(bits, idx);
}

int DRB_CountInfo::count_Uplink_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (4294967295 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("DRB_CountInfo::count_Uplink_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    count_Uplink_internal_value = packed_val + 0;
    count_Uplink_present = true;
    return 0;
}

int64_t DRB_CountInfo::count_Uplink_Value() const
{
    if(count_Uplink_present)
        return count_Uplink_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int DRB_CountInfo::count_Uplink_SetValue(int64_t value)
{
    if(value < 0 || value > 4294967295)
    {
        printf("DRB_CountInfo::count_Uplink_SetValue() range failure\n");
        return -1;
    }
    count_Uplink_internal_value = value;
    count_Uplink_present = true;
    return 0;
}

std::string DRB_CountInfo::count_Uplink_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "count_Uplink = " + std::to_string(count_Uplink_internal_value) + "\n";
    return out;
}

std::string DRB_CountInfo::count_Uplink_ToStringNoNewLines() const
{
    std::string out = "count_Uplink=" + std::to_string(count_Uplink_internal_value) + ",";
    return out;
}

int DRB_CountInfo::count_Uplink_Clear()
{
    count_Uplink_present = false;
    return 0;
}

bool DRB_CountInfo::count_Uplink_IsPresent() const
{
    return count_Uplink_present;
}

int DRB_CountInfo::count_Downlink_Pack(std::vector<uint8_t> &bits)
{
    if(!count_Downlink_present)
    {
        printf("DRB_CountInfo::count_Downlink_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = count_Downlink_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (4294967295 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int DRB_CountInfo::count_Downlink_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return count_Downlink_Unpack(bits, idx);
}

int DRB_CountInfo::count_Downlink_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (4294967295 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("DRB_CountInfo::count_Downlink_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    count_Downlink_internal_value = packed_val + 0;
    count_Downlink_present = true;
    return 0;
}

int64_t DRB_CountInfo::count_Downlink_Value() const
{
    if(count_Downlink_present)
        return count_Downlink_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int DRB_CountInfo::count_Downlink_SetValue(int64_t value)
{
    if(value < 0 || value > 4294967295)
    {
        printf("DRB_CountInfo::count_Downlink_SetValue() range failure\n");
        return -1;
    }
    count_Downlink_internal_value = value;
    count_Downlink_present = true;
    return 0;
}

std::string DRB_CountInfo::count_Downlink_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "count_Downlink = " + std::to_string(count_Downlink_internal_value) + "\n";
    return out;
}

std::string DRB_CountInfo::count_Downlink_ToStringNoNewLines() const
{
    std::string out = "count_Downlink=" + std::to_string(count_Downlink_internal_value) + ",";
    return out;
}

int DRB_CountInfo::count_Downlink_Clear()
{
    count_Downlink_present = false;
    return 0;
}

bool DRB_CountInfo::count_Downlink_IsPresent() const
{
    return count_Downlink_present;
}

