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

#include "CarrierBandwidthEUTRA.h"

#include <cmath>

int CarrierBandwidthEUTRA::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(ul_Bandwidth_IsPresent());

    // Fields
    {
        if(0 != dl_Bandwidth_Pack(bits))
        {
            printf("CarrierBandwidthEUTRA:: field pack failure\n");
            return -1;
        }
    }
    if(ul_Bandwidth_IsPresent())
    {
        if(0 != ul_Bandwidth_Pack(bits))
        {
            printf("CarrierBandwidthEUTRA:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int CarrierBandwidthEUTRA::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int CarrierBandwidthEUTRA::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("CarrierBandwidthEUTRA::Unpack() index out of bounds for optional indiator ul_Bandwidth\n");
        return -1;
    }
    ul_Bandwidth_present = bits[idx++];

    // Fields
    {
        if(0 != dl_Bandwidth_Unpack(bits, idx))
        {
            printf("CarrierBandwidthEUTRA:: field unpack failure\n");
            return -1;
        }
    }
    if(ul_Bandwidth_present)
    {
        if(0 != ul_Bandwidth_Unpack(bits, idx))
        {
            printf("CarrierBandwidthEUTRA:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string CarrierBandwidthEUTRA::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "CarrierBandwidthEUTRA:\n";
    out += dl_Bandwidth_ToString(indent+1);
    if(ul_Bandwidth_IsPresent())
        out += ul_Bandwidth_ToString(indent+1);
    return out;
}

std::string CarrierBandwidthEUTRA::ToStringNoNewLines() const
{
    std::string out = "CarrierBandwidthEUTRA:";
    out += dl_Bandwidth_ToStringNoNewLines();
    if(ul_Bandwidth_IsPresent())
        out += ul_Bandwidth_ToStringNoNewLines();
    return out;
}

int CarrierBandwidthEUTRA::dl_Bandwidth_Pack(std::vector<uint8_t> &bits)
{
    if(!dl_Bandwidth_present)
    {
        printf("CarrierBandwidthEUTRA::dl_Bandwidth_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 4;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((dl_Bandwidth_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int CarrierBandwidthEUTRA::dl_Bandwidth_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return dl_Bandwidth_Unpack(bits, idx);
}

int CarrierBandwidthEUTRA::dl_Bandwidth_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 4;
    if((idx + N_bits) > bits.size())
    {
        printf("CarrierBandwidthEUTRA::dl_Bandwidth_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 15)
    {
        printf("CarrierBandwidthEUTRA::dl_Bandwidth_Unpack() max failure\n");
        return -1;
    }
    dl_Bandwidth_internal_value = (dl_Bandwidth_Enum)packed_val;
    dl_Bandwidth_present = true;
    return 0;
}

CarrierBandwidthEUTRA::dl_Bandwidth_Enum CarrierBandwidthEUTRA::dl_Bandwidth_Value() const
{
    if(dl_Bandwidth_present)
        return dl_Bandwidth_internal_value;
    return (CarrierBandwidthEUTRA::dl_Bandwidth_Enum)0;
}

int CarrierBandwidthEUTRA::dl_Bandwidth_SetValue(dl_Bandwidth_Enum value)
{
    dl_Bandwidth_internal_value = value;
    dl_Bandwidth_present = true;
    return 0;
}

int CarrierBandwidthEUTRA::dl_Bandwidth_SetValue(std::string value)
{
    if("n6" == value)
    {
        dl_Bandwidth_internal_value = k_dl_Bandwidth_n6;
        dl_Bandwidth_present = true;
        return 0;
    }
    if("n15" == value)
    {
        dl_Bandwidth_internal_value = k_dl_Bandwidth_n15;
        dl_Bandwidth_present = true;
        return 0;
    }
    if("n25" == value)
    {
        dl_Bandwidth_internal_value = k_dl_Bandwidth_n25;
        dl_Bandwidth_present = true;
        return 0;
    }
    if("n50" == value)
    {
        dl_Bandwidth_internal_value = k_dl_Bandwidth_n50;
        dl_Bandwidth_present = true;
        return 0;
    }
    if("n75" == value)
    {
        dl_Bandwidth_internal_value = k_dl_Bandwidth_n75;
        dl_Bandwidth_present = true;
        return 0;
    }
    if("n100" == value)
    {
        dl_Bandwidth_internal_value = k_dl_Bandwidth_n100;
        dl_Bandwidth_present = true;
        return 0;
    }
    if("spare10" == value)
    {
        dl_Bandwidth_internal_value = k_dl_Bandwidth_spare10;
        dl_Bandwidth_present = true;
        return 0;
    }
    if("spare9" == value)
    {
        dl_Bandwidth_internal_value = k_dl_Bandwidth_spare9;
        dl_Bandwidth_present = true;
        return 0;
    }
    if("spare8" == value)
    {
        dl_Bandwidth_internal_value = k_dl_Bandwidth_spare8;
        dl_Bandwidth_present = true;
        return 0;
    }
    if("spare7" == value)
    {
        dl_Bandwidth_internal_value = k_dl_Bandwidth_spare7;
        dl_Bandwidth_present = true;
        return 0;
    }
    if("spare6" == value)
    {
        dl_Bandwidth_internal_value = k_dl_Bandwidth_spare6;
        dl_Bandwidth_present = true;
        return 0;
    }
    if("spare5" == value)
    {
        dl_Bandwidth_internal_value = k_dl_Bandwidth_spare5;
        dl_Bandwidth_present = true;
        return 0;
    }
    if("spare4" == value)
    {
        dl_Bandwidth_internal_value = k_dl_Bandwidth_spare4;
        dl_Bandwidth_present = true;
        return 0;
    }
    if("spare3" == value)
    {
        dl_Bandwidth_internal_value = k_dl_Bandwidth_spare3;
        dl_Bandwidth_present = true;
        return 0;
    }
    if("spare2" == value)
    {
        dl_Bandwidth_internal_value = k_dl_Bandwidth_spare2;
        dl_Bandwidth_present = true;
        return 0;
    }
    if("spare1" == value)
    {
        dl_Bandwidth_internal_value = k_dl_Bandwidth_spare1;
        dl_Bandwidth_present = true;
        return 0;
    }
    return 1;
}

std::string CarrierBandwidthEUTRA::dl_Bandwidth_ValueToString(dl_Bandwidth_Enum value) const
{
    if(k_dl_Bandwidth_n6 == value)
        return "n6";
    if(k_dl_Bandwidth_n15 == value)
        return "n15";
    if(k_dl_Bandwidth_n25 == value)
        return "n25";
    if(k_dl_Bandwidth_n50 == value)
        return "n50";
    if(k_dl_Bandwidth_n75 == value)
        return "n75";
    if(k_dl_Bandwidth_n100 == value)
        return "n100";
    if(k_dl_Bandwidth_spare10 == value)
        return "spare10";
    if(k_dl_Bandwidth_spare9 == value)
        return "spare9";
    if(k_dl_Bandwidth_spare8 == value)
        return "spare8";
    if(k_dl_Bandwidth_spare7 == value)
        return "spare7";
    if(k_dl_Bandwidth_spare6 == value)
        return "spare6";
    if(k_dl_Bandwidth_spare5 == value)
        return "spare5";
    if(k_dl_Bandwidth_spare4 == value)
        return "spare4";
    if(k_dl_Bandwidth_spare3 == value)
        return "spare3";
    if(k_dl_Bandwidth_spare2 == value)
        return "spare2";
    if(k_dl_Bandwidth_spare1 == value)
        return "spare1";
    return "";
}

uint64_t CarrierBandwidthEUTRA::dl_Bandwidth_NumberOfValues() const
{
    return 16;
}

std::string CarrierBandwidthEUTRA::dl_Bandwidth_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "dl_Bandwidth = " + dl_Bandwidth_ValueToString(dl_Bandwidth_internal_value) + "\n";
    return out;
}

std::string CarrierBandwidthEUTRA::dl_Bandwidth_ToStringNoNewLines() const
{
    std::string out = "dl_Bandwidth=" + dl_Bandwidth_ValueToString(dl_Bandwidth_internal_value) + ",";
    return out;
}

int CarrierBandwidthEUTRA::dl_Bandwidth_Clear()
{
    dl_Bandwidth_present = false;
    return 0;
}

bool CarrierBandwidthEUTRA::dl_Bandwidth_IsPresent() const
{
    return dl_Bandwidth_present;
}

int CarrierBandwidthEUTRA::ul_Bandwidth_Pack(std::vector<uint8_t> &bits)
{
    uint32_t N_bits = 4;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((ul_Bandwidth_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int CarrierBandwidthEUTRA::ul_Bandwidth_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return ul_Bandwidth_Unpack(bits, idx);
}

int CarrierBandwidthEUTRA::ul_Bandwidth_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 4;
    if((idx + N_bits) > bits.size())
    {
        printf("CarrierBandwidthEUTRA::ul_Bandwidth_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 15)
    {
        printf("CarrierBandwidthEUTRA::ul_Bandwidth_Unpack() max failure\n");
        return -1;
    }
    ul_Bandwidth_internal_value = (ul_Bandwidth_Enum)packed_val;
    ul_Bandwidth_present = true;
    return 0;
}

CarrierBandwidthEUTRA::ul_Bandwidth_Enum CarrierBandwidthEUTRA::ul_Bandwidth_Value() const
{
    if(ul_Bandwidth_present)
        return ul_Bandwidth_internal_value;
    return (CarrierBandwidthEUTRA::ul_Bandwidth_Enum)0;
}

int CarrierBandwidthEUTRA::ul_Bandwidth_SetValue(ul_Bandwidth_Enum value)
{
    ul_Bandwidth_internal_value = value;
    ul_Bandwidth_present = true;
    return 0;
}

int CarrierBandwidthEUTRA::ul_Bandwidth_SetValue(std::string value)
{
    if("n6" == value)
    {
        ul_Bandwidth_internal_value = k_ul_Bandwidth_n6;
        ul_Bandwidth_present = true;
        return 0;
    }
    if("n15" == value)
    {
        ul_Bandwidth_internal_value = k_ul_Bandwidth_n15;
        ul_Bandwidth_present = true;
        return 0;
    }
    if("n25" == value)
    {
        ul_Bandwidth_internal_value = k_ul_Bandwidth_n25;
        ul_Bandwidth_present = true;
        return 0;
    }
    if("n50" == value)
    {
        ul_Bandwidth_internal_value = k_ul_Bandwidth_n50;
        ul_Bandwidth_present = true;
        return 0;
    }
    if("n75" == value)
    {
        ul_Bandwidth_internal_value = k_ul_Bandwidth_n75;
        ul_Bandwidth_present = true;
        return 0;
    }
    if("n100" == value)
    {
        ul_Bandwidth_internal_value = k_ul_Bandwidth_n100;
        ul_Bandwidth_present = true;
        return 0;
    }
    if("spare10" == value)
    {
        ul_Bandwidth_internal_value = k_ul_Bandwidth_spare10;
        ul_Bandwidth_present = true;
        return 0;
    }
    if("spare9" == value)
    {
        ul_Bandwidth_internal_value = k_ul_Bandwidth_spare9;
        ul_Bandwidth_present = true;
        return 0;
    }
    if("spare8" == value)
    {
        ul_Bandwidth_internal_value = k_ul_Bandwidth_spare8;
        ul_Bandwidth_present = true;
        return 0;
    }
    if("spare7" == value)
    {
        ul_Bandwidth_internal_value = k_ul_Bandwidth_spare7;
        ul_Bandwidth_present = true;
        return 0;
    }
    if("spare6" == value)
    {
        ul_Bandwidth_internal_value = k_ul_Bandwidth_spare6;
        ul_Bandwidth_present = true;
        return 0;
    }
    if("spare5" == value)
    {
        ul_Bandwidth_internal_value = k_ul_Bandwidth_spare5;
        ul_Bandwidth_present = true;
        return 0;
    }
    if("spare4" == value)
    {
        ul_Bandwidth_internal_value = k_ul_Bandwidth_spare4;
        ul_Bandwidth_present = true;
        return 0;
    }
    if("spare3" == value)
    {
        ul_Bandwidth_internal_value = k_ul_Bandwidth_spare3;
        ul_Bandwidth_present = true;
        return 0;
    }
    if("spare2" == value)
    {
        ul_Bandwidth_internal_value = k_ul_Bandwidth_spare2;
        ul_Bandwidth_present = true;
        return 0;
    }
    if("spare1" == value)
    {
        ul_Bandwidth_internal_value = k_ul_Bandwidth_spare1;
        ul_Bandwidth_present = true;
        return 0;
    }
    return 1;
}

std::string CarrierBandwidthEUTRA::ul_Bandwidth_ValueToString(ul_Bandwidth_Enum value) const
{
    if(k_ul_Bandwidth_n6 == value)
        return "n6";
    if(k_ul_Bandwidth_n15 == value)
        return "n15";
    if(k_ul_Bandwidth_n25 == value)
        return "n25";
    if(k_ul_Bandwidth_n50 == value)
        return "n50";
    if(k_ul_Bandwidth_n75 == value)
        return "n75";
    if(k_ul_Bandwidth_n100 == value)
        return "n100";
    if(k_ul_Bandwidth_spare10 == value)
        return "spare10";
    if(k_ul_Bandwidth_spare9 == value)
        return "spare9";
    if(k_ul_Bandwidth_spare8 == value)
        return "spare8";
    if(k_ul_Bandwidth_spare7 == value)
        return "spare7";
    if(k_ul_Bandwidth_spare6 == value)
        return "spare6";
    if(k_ul_Bandwidth_spare5 == value)
        return "spare5";
    if(k_ul_Bandwidth_spare4 == value)
        return "spare4";
    if(k_ul_Bandwidth_spare3 == value)
        return "spare3";
    if(k_ul_Bandwidth_spare2 == value)
        return "spare2";
    if(k_ul_Bandwidth_spare1 == value)
        return "spare1";
    return "";
}

uint64_t CarrierBandwidthEUTRA::ul_Bandwidth_NumberOfValues() const
{
    return 16;
}

std::string CarrierBandwidthEUTRA::ul_Bandwidth_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ul_Bandwidth = " + ul_Bandwidth_ValueToString(ul_Bandwidth_internal_value) + "\n";
    return out;
}

std::string CarrierBandwidthEUTRA::ul_Bandwidth_ToStringNoNewLines() const
{
    std::string out = "ul_Bandwidth=" + ul_Bandwidth_ValueToString(ul_Bandwidth_internal_value) + ",";
    return out;
}

int CarrierBandwidthEUTRA::ul_Bandwidth_Clear()
{
    ul_Bandwidth_present = false;
    return 0;
}

bool CarrierBandwidthEUTRA::ul_Bandwidth_IsPresent() const
{
    return ul_Bandwidth_present;
}

