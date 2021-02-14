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

#include "DRB_CountMSB_Info.h"

#include <cmath>

int DRB_CountMSB_Info::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != drb_Identity.Pack(bits))
        {
            printf("DRB_CountMSB_Info:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != countMSB_Uplink_Pack(bits))
        {
            printf("DRB_CountMSB_Info:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != countMSB_Downlink_Pack(bits))
        {
            printf("DRB_CountMSB_Info:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int DRB_CountMSB_Info::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int DRB_CountMSB_Info::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != drb_Identity.Unpack(bits, idx))
        {
            printf("DRB_CountMSB_Info:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != countMSB_Uplink_Unpack(bits, idx))
        {
            printf("DRB_CountMSB_Info:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != countMSB_Downlink_Unpack(bits, idx))
        {
            printf("DRB_CountMSB_Info:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string DRB_CountMSB_Info::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "DRB_CountMSB_Info:\n";
    out += drb_Identity_ToString(indent+1);
    out += countMSB_Uplink_ToString(indent+1);
    out += countMSB_Downlink_ToString(indent+1);
    return out;
}

std::string DRB_CountMSB_Info::ToStringNoNewLines() const
{
    std::string out = "DRB_CountMSB_Info:";
    out += drb_Identity_ToStringNoNewLines();
    out += countMSB_Uplink_ToStringNoNewLines();
    out += countMSB_Downlink_ToStringNoNewLines();
    return out;
}

DRB_Identity* DRB_CountMSB_Info::drb_Identity_Set()
{
    drb_Identity_present = true;
    return &drb_Identity;
}

int DRB_CountMSB_Info::drb_Identity_Set(DRB_Identity &value)
{
    drb_Identity_present = true;
    drb_Identity = value;
    return 0;
}

const DRB_Identity& DRB_CountMSB_Info::drb_Identity_Get() const
{
    return drb_Identity;
}

std::string DRB_CountMSB_Info::drb_Identity_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "drb_Identity:\n";
    out += drb_Identity.ToString(indent+1);
    return out;
}

std::string DRB_CountMSB_Info::drb_Identity_ToStringNoNewLines() const
{
    std::string out = "drb_Identity:";
    out += drb_Identity.ToStringNoNewLines();
    return out;
}

int DRB_CountMSB_Info::drb_Identity_Clear()
{
    drb_Identity_present = false;
    return 0;
}

bool DRB_CountMSB_Info::drb_Identity_IsPresent() const
{
    return drb_Identity_present;
}

int DRB_CountMSB_Info::countMSB_Uplink_Pack(std::vector<uint8_t> &bits)
{
    if(!countMSB_Uplink_present)
    {
        printf("DRB_CountMSB_Info::countMSB_Uplink_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = countMSB_Uplink_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (33554431 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int DRB_CountMSB_Info::countMSB_Uplink_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return countMSB_Uplink_Unpack(bits, idx);
}

int DRB_CountMSB_Info::countMSB_Uplink_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (33554431 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("DRB_CountMSB_Info::countMSB_Uplink_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    countMSB_Uplink_internal_value = packed_val + 0;
    countMSB_Uplink_present = true;
    return 0;
}

int64_t DRB_CountMSB_Info::countMSB_Uplink_Value() const
{
    if(countMSB_Uplink_present)
        return countMSB_Uplink_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int DRB_CountMSB_Info::countMSB_Uplink_SetValue(int64_t value)
{
    if(value < 0 || value > 33554431)
    {
        printf("DRB_CountMSB_Info::countMSB_Uplink_SetValue() range failure\n");
        return -1;
    }
    countMSB_Uplink_internal_value = value;
    countMSB_Uplink_present = true;
    return 0;
}

std::string DRB_CountMSB_Info::countMSB_Uplink_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "countMSB_Uplink = " + std::to_string(countMSB_Uplink_internal_value) + "\n";
    return out;
}

std::string DRB_CountMSB_Info::countMSB_Uplink_ToStringNoNewLines() const
{
    std::string out = "countMSB_Uplink=" + std::to_string(countMSB_Uplink_internal_value) + ",";
    return out;
}

int DRB_CountMSB_Info::countMSB_Uplink_Clear()
{
    countMSB_Uplink_present = false;
    return 0;
}

bool DRB_CountMSB_Info::countMSB_Uplink_IsPresent() const
{
    return countMSB_Uplink_present;
}

int DRB_CountMSB_Info::countMSB_Downlink_Pack(std::vector<uint8_t> &bits)
{
    if(!countMSB_Downlink_present)
    {
        printf("DRB_CountMSB_Info::countMSB_Downlink_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = countMSB_Downlink_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (33554431 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int DRB_CountMSB_Info::countMSB_Downlink_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return countMSB_Downlink_Unpack(bits, idx);
}

int DRB_CountMSB_Info::countMSB_Downlink_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (33554431 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("DRB_CountMSB_Info::countMSB_Downlink_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    countMSB_Downlink_internal_value = packed_val + 0;
    countMSB_Downlink_present = true;
    return 0;
}

int64_t DRB_CountMSB_Info::countMSB_Downlink_Value() const
{
    if(countMSB_Downlink_present)
        return countMSB_Downlink_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int DRB_CountMSB_Info::countMSB_Downlink_SetValue(int64_t value)
{
    if(value < 0 || value > 33554431)
    {
        printf("DRB_CountMSB_Info::countMSB_Downlink_SetValue() range failure\n");
        return -1;
    }
    countMSB_Downlink_internal_value = value;
    countMSB_Downlink_present = true;
    return 0;
}

std::string DRB_CountMSB_Info::countMSB_Downlink_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "countMSB_Downlink = " + std::to_string(countMSB_Downlink_internal_value) + "\n";
    return out;
}

std::string DRB_CountMSB_Info::countMSB_Downlink_ToStringNoNewLines() const
{
    std::string out = "countMSB_Downlink=" + std::to_string(countMSB_Downlink_internal_value) + ",";
    return out;
}

int DRB_CountMSB_Info::countMSB_Downlink_Clear()
{
    countMSB_Downlink_present = false;
    return 0;
}

bool DRB_CountMSB_Info::countMSB_Downlink_IsPresent() const
{
    return countMSB_Downlink_present;
}

