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

#include "UL_AntennaInfo_r10.h"

#include <cmath>

int UL_AntennaInfo_r10::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator
    bits.push_back(0);

    // Optional indicators

    // Fields
    {
        if(0 != ul_TransmissionMode_r10_Pack(bits))
        {
            printf("UL_AntennaInfo_r10:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != fourAntennaPortActivated_r10_Pack(bits))
        {
            printf("UL_AntennaInfo_r10:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int UL_AntennaInfo_r10::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int UL_AntennaInfo_r10::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("UL_AntennaInfo_r10::Unpack() index out of bounds for extension\n");
        return -1;
    }
    idx++;

    // Optional indicators

    // Fields
    {
        if(0 != ul_TransmissionMode_r10_Unpack(bits, idx))
        {
            printf("UL_AntennaInfo_r10:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != fourAntennaPortActivated_r10_Unpack(bits, idx))
        {
            printf("UL_AntennaInfo_r10:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string UL_AntennaInfo_r10::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "UL_AntennaInfo_r10:\n";
    out += ul_TransmissionMode_r10_ToString(indent+1);
    out += fourAntennaPortActivated_r10_ToString(indent+1);
    return out;
}

std::string UL_AntennaInfo_r10::ToStringNoNewLines() const
{
    std::string out = "UL_AntennaInfo_r10:";
    out += ul_TransmissionMode_r10_ToStringNoNewLines();
    out += fourAntennaPortActivated_r10_ToStringNoNewLines();
    return out;
}

int UL_AntennaInfo_r10::ul_TransmissionMode_r10_Pack(std::vector<uint8_t> &bits)
{
    if(!ul_TransmissionMode_r10_present)
    {
        printf("UL_AntennaInfo_r10::ul_TransmissionMode_r10_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 3;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((ul_TransmissionMode_r10_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int UL_AntennaInfo_r10::ul_TransmissionMode_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return ul_TransmissionMode_r10_Unpack(bits, idx);
}

int UL_AntennaInfo_r10::ul_TransmissionMode_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 3;
    if((idx + N_bits) > bits.size())
    {
        printf("UL_AntennaInfo_r10::ul_TransmissionMode_r10_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 7)
    {
        printf("UL_AntennaInfo_r10::ul_TransmissionMode_r10_Unpack() max failure\n");
        return -1;
    }
    ul_TransmissionMode_r10_internal_value = (ul_TransmissionMode_r10_Enum)packed_val;
    ul_TransmissionMode_r10_present = true;
    return 0;
}

UL_AntennaInfo_r10::ul_TransmissionMode_r10_Enum UL_AntennaInfo_r10::ul_TransmissionMode_r10_Value() const
{
    if(ul_TransmissionMode_r10_present)
        return ul_TransmissionMode_r10_internal_value;
    return (UL_AntennaInfo_r10::ul_TransmissionMode_r10_Enum)0;
}

int UL_AntennaInfo_r10::ul_TransmissionMode_r10_SetValue(ul_TransmissionMode_r10_Enum value)
{
    ul_TransmissionMode_r10_internal_value = value;
    ul_TransmissionMode_r10_present = true;
    return 0;
}

int UL_AntennaInfo_r10::ul_TransmissionMode_r10_SetValue(std::string value)
{
    if("tm1" == value)
    {
        ul_TransmissionMode_r10_internal_value = k_ul_TransmissionMode_r10_tm1;
        ul_TransmissionMode_r10_present = true;
        return 0;
    }
    if("tm2" == value)
    {
        ul_TransmissionMode_r10_internal_value = k_ul_TransmissionMode_r10_tm2;
        ul_TransmissionMode_r10_present = true;
        return 0;
    }
    if("spare6" == value)
    {
        ul_TransmissionMode_r10_internal_value = k_ul_TransmissionMode_r10_spare6;
        ul_TransmissionMode_r10_present = true;
        return 0;
    }
    if("spare5" == value)
    {
        ul_TransmissionMode_r10_internal_value = k_ul_TransmissionMode_r10_spare5;
        ul_TransmissionMode_r10_present = true;
        return 0;
    }
    if("spare4" == value)
    {
        ul_TransmissionMode_r10_internal_value = k_ul_TransmissionMode_r10_spare4;
        ul_TransmissionMode_r10_present = true;
        return 0;
    }
    if("spare3" == value)
    {
        ul_TransmissionMode_r10_internal_value = k_ul_TransmissionMode_r10_spare3;
        ul_TransmissionMode_r10_present = true;
        return 0;
    }
    if("spare2" == value)
    {
        ul_TransmissionMode_r10_internal_value = k_ul_TransmissionMode_r10_spare2;
        ul_TransmissionMode_r10_present = true;
        return 0;
    }
    if("spare1" == value)
    {
        ul_TransmissionMode_r10_internal_value = k_ul_TransmissionMode_r10_spare1;
        ul_TransmissionMode_r10_present = true;
        return 0;
    }
    return 1;
}

std::string UL_AntennaInfo_r10::ul_TransmissionMode_r10_ValueToString(ul_TransmissionMode_r10_Enum value) const
{
    if(k_ul_TransmissionMode_r10_tm1 == value)
        return "tm1";
    if(k_ul_TransmissionMode_r10_tm2 == value)
        return "tm2";
    if(k_ul_TransmissionMode_r10_spare6 == value)
        return "spare6";
    if(k_ul_TransmissionMode_r10_spare5 == value)
        return "spare5";
    if(k_ul_TransmissionMode_r10_spare4 == value)
        return "spare4";
    if(k_ul_TransmissionMode_r10_spare3 == value)
        return "spare3";
    if(k_ul_TransmissionMode_r10_spare2 == value)
        return "spare2";
    if(k_ul_TransmissionMode_r10_spare1 == value)
        return "spare1";
    return "";
}

uint64_t UL_AntennaInfo_r10::ul_TransmissionMode_r10_NumberOfValues() const
{
    return 8;
}

std::string UL_AntennaInfo_r10::ul_TransmissionMode_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ul_TransmissionMode_r10 = " + ul_TransmissionMode_r10_ValueToString(ul_TransmissionMode_r10_internal_value) + "\n";
    return out;
}

std::string UL_AntennaInfo_r10::ul_TransmissionMode_r10_ToStringNoNewLines() const
{
    std::string out = "ul_TransmissionMode_r10=" + ul_TransmissionMode_r10_ValueToString(ul_TransmissionMode_r10_internal_value) + ",";
    return out;
}

int UL_AntennaInfo_r10::ul_TransmissionMode_r10_Clear()
{
    ul_TransmissionMode_r10_present = false;
    return 0;
}

bool UL_AntennaInfo_r10::ul_TransmissionMode_r10_IsPresent() const
{
    return ul_TransmissionMode_r10_present;
}

int UL_AntennaInfo_r10::fourAntennaPortActivated_r10_Pack(std::vector<uint8_t> &bits)
{
    if(!fourAntennaPortActivated_r10_present)
    {
        printf("UL_AntennaInfo_r10::fourAntennaPortActivated_r10_Pack() presence failure\n");
        return -1;
    }
    bits.push_back(fourAntennaPortActivated_r10_internal_value);
    return 0;
}

int UL_AntennaInfo_r10::fourAntennaPortActivated_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return fourAntennaPortActivated_r10_Unpack(bits, idx);
}

int UL_AntennaInfo_r10::fourAntennaPortActivated_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    if((idx + 1) > bits.size())
    {
        printf("UL_AntennaInfo_r10::fourAntennaPortActivated_r10_Unpack() index out of bounds\n");
        return -1;
    }
    fourAntennaPortActivated_r10_internal_value = bits[idx++];
    fourAntennaPortActivated_r10_present = true;
    return 0;
}

bool UL_AntennaInfo_r10::fourAntennaPortActivated_r10_Value() const
{
    if(fourAntennaPortActivated_r10_present)
        return fourAntennaPortActivated_r10_internal_value;
    return false;
}

int UL_AntennaInfo_r10::fourAntennaPortActivated_r10_SetValue(bool value)
{
    fourAntennaPortActivated_r10_internal_value = value;
    fourAntennaPortActivated_r10_present = true;
    return 0;
}

std::string UL_AntennaInfo_r10::fourAntennaPortActivated_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "fourAntennaPortActivated_r10 = " + std::to_string(fourAntennaPortActivated_r10_internal_value) + "\n";
    return out;
}

std::string UL_AntennaInfo_r10::fourAntennaPortActivated_r10_ToStringNoNewLines() const
{
    std::string out = "fourAntennaPortActivated_r10=" + std::to_string(fourAntennaPortActivated_r10_internal_value) + ",";
    return out;
}

int UL_AntennaInfo_r10::fourAntennaPortActivated_r10_Clear()
{
    fourAntennaPortActivated_r10_present = false;
    return 0;
}

bool UL_AntennaInfo_r10::fourAntennaPortActivated_r10_IsPresent() const
{
    return fourAntennaPortActivated_r10_present;
}

