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

#include "MobilityStateParameters.h"

#include <cmath>

int MobilityStateParameters::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != t_Evaluation_Pack(bits))
        {
            printf("MobilityStateParameters:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != t_HystNormal_Pack(bits))
        {
            printf("MobilityStateParameters:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != n_CellChangeMedium_Pack(bits))
        {
            printf("MobilityStateParameters:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != n_CellChangeHigh_Pack(bits))
        {
            printf("MobilityStateParameters:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int MobilityStateParameters::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int MobilityStateParameters::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != t_Evaluation_Unpack(bits, idx))
        {
            printf("MobilityStateParameters:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != t_HystNormal_Unpack(bits, idx))
        {
            printf("MobilityStateParameters:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != n_CellChangeMedium_Unpack(bits, idx))
        {
            printf("MobilityStateParameters:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != n_CellChangeHigh_Unpack(bits, idx))
        {
            printf("MobilityStateParameters:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string MobilityStateParameters::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "MobilityStateParameters:\n";
    out += t_Evaluation_ToString(indent+1);
    out += t_HystNormal_ToString(indent+1);
    out += n_CellChangeMedium_ToString(indent+1);
    out += n_CellChangeHigh_ToString(indent+1);
    return out;
}

std::string MobilityStateParameters::ToStringNoNewLines() const
{
    std::string out = "MobilityStateParameters:";
    out += t_Evaluation_ToStringNoNewLines();
    out += t_HystNormal_ToStringNoNewLines();
    out += n_CellChangeMedium_ToStringNoNewLines();
    out += n_CellChangeHigh_ToStringNoNewLines();
    return out;
}

int MobilityStateParameters::t_Evaluation_Pack(std::vector<uint8_t> &bits)
{
    if(!t_Evaluation_present)
    {
        printf("MobilityStateParameters::t_Evaluation_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 3;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((t_Evaluation_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int MobilityStateParameters::t_Evaluation_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return t_Evaluation_Unpack(bits, idx);
}

int MobilityStateParameters::t_Evaluation_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 3;
    if((idx + N_bits) > bits.size())
    {
        printf("MobilityStateParameters::t_Evaluation_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 7)
    {
        printf("MobilityStateParameters::t_Evaluation_Unpack() max failure\n");
        return -1;
    }
    t_Evaluation_internal_value = (t_Evaluation_Enum)packed_val;
    t_Evaluation_present = true;
    return 0;
}

MobilityStateParameters::t_Evaluation_Enum MobilityStateParameters::t_Evaluation_Value() const
{
    if(t_Evaluation_present)
        return t_Evaluation_internal_value;
    return (MobilityStateParameters::t_Evaluation_Enum)0;
}

int MobilityStateParameters::t_Evaluation_SetValue(t_Evaluation_Enum value)
{
    t_Evaluation_internal_value = value;
    t_Evaluation_present = true;
    return 0;
}

int MobilityStateParameters::t_Evaluation_SetValue(std::string value)
{
    if("s30" == value)
    {
        t_Evaluation_internal_value = k_t_Evaluation_s30;
        t_Evaluation_present = true;
        return 0;
    }
    if("s60" == value)
    {
        t_Evaluation_internal_value = k_t_Evaluation_s60;
        t_Evaluation_present = true;
        return 0;
    }
    if("s120" == value)
    {
        t_Evaluation_internal_value = k_t_Evaluation_s120;
        t_Evaluation_present = true;
        return 0;
    }
    if("s180" == value)
    {
        t_Evaluation_internal_value = k_t_Evaluation_s180;
        t_Evaluation_present = true;
        return 0;
    }
    if("s240" == value)
    {
        t_Evaluation_internal_value = k_t_Evaluation_s240;
        t_Evaluation_present = true;
        return 0;
    }
    if("spare3" == value)
    {
        t_Evaluation_internal_value = k_t_Evaluation_spare3;
        t_Evaluation_present = true;
        return 0;
    }
    if("spare2" == value)
    {
        t_Evaluation_internal_value = k_t_Evaluation_spare2;
        t_Evaluation_present = true;
        return 0;
    }
    if("spare1" == value)
    {
        t_Evaluation_internal_value = k_t_Evaluation_spare1;
        t_Evaluation_present = true;
        return 0;
    }
    return 1;
}

std::string MobilityStateParameters::t_Evaluation_ValueToString(t_Evaluation_Enum value) const
{
    if(k_t_Evaluation_s30 == value)
        return "s30";
    if(k_t_Evaluation_s60 == value)
        return "s60";
    if(k_t_Evaluation_s120 == value)
        return "s120";
    if(k_t_Evaluation_s180 == value)
        return "s180";
    if(k_t_Evaluation_s240 == value)
        return "s240";
    if(k_t_Evaluation_spare3 == value)
        return "spare3";
    if(k_t_Evaluation_spare2 == value)
        return "spare2";
    if(k_t_Evaluation_spare1 == value)
        return "spare1";
    return "";
}

uint64_t MobilityStateParameters::t_Evaluation_NumberOfValues() const
{
    return 8;
}

std::string MobilityStateParameters::t_Evaluation_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "t_Evaluation = " + t_Evaluation_ValueToString(t_Evaluation_internal_value) + "\n";
    return out;
}

std::string MobilityStateParameters::t_Evaluation_ToStringNoNewLines() const
{
    std::string out = "t_Evaluation=" + t_Evaluation_ValueToString(t_Evaluation_internal_value) + ",";
    return out;
}

int MobilityStateParameters::t_Evaluation_Clear()
{
    t_Evaluation_present = false;
    return 0;
}

bool MobilityStateParameters::t_Evaluation_IsPresent() const
{
    return t_Evaluation_present;
}

int MobilityStateParameters::t_HystNormal_Pack(std::vector<uint8_t> &bits)
{
    if(!t_HystNormal_present)
    {
        printf("MobilityStateParameters::t_HystNormal_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 3;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((t_HystNormal_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int MobilityStateParameters::t_HystNormal_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return t_HystNormal_Unpack(bits, idx);
}

int MobilityStateParameters::t_HystNormal_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 3;
    if((idx + N_bits) > bits.size())
    {
        printf("MobilityStateParameters::t_HystNormal_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 7)
    {
        printf("MobilityStateParameters::t_HystNormal_Unpack() max failure\n");
        return -1;
    }
    t_HystNormal_internal_value = (t_HystNormal_Enum)packed_val;
    t_HystNormal_present = true;
    return 0;
}

MobilityStateParameters::t_HystNormal_Enum MobilityStateParameters::t_HystNormal_Value() const
{
    if(t_HystNormal_present)
        return t_HystNormal_internal_value;
    return (MobilityStateParameters::t_HystNormal_Enum)0;
}

int MobilityStateParameters::t_HystNormal_SetValue(t_HystNormal_Enum value)
{
    t_HystNormal_internal_value = value;
    t_HystNormal_present = true;
    return 0;
}

int MobilityStateParameters::t_HystNormal_SetValue(std::string value)
{
    if("s30" == value)
    {
        t_HystNormal_internal_value = k_t_HystNormal_s30;
        t_HystNormal_present = true;
        return 0;
    }
    if("s60" == value)
    {
        t_HystNormal_internal_value = k_t_HystNormal_s60;
        t_HystNormal_present = true;
        return 0;
    }
    if("s120" == value)
    {
        t_HystNormal_internal_value = k_t_HystNormal_s120;
        t_HystNormal_present = true;
        return 0;
    }
    if("s180" == value)
    {
        t_HystNormal_internal_value = k_t_HystNormal_s180;
        t_HystNormal_present = true;
        return 0;
    }
    if("s240" == value)
    {
        t_HystNormal_internal_value = k_t_HystNormal_s240;
        t_HystNormal_present = true;
        return 0;
    }
    if("spare3" == value)
    {
        t_HystNormal_internal_value = k_t_HystNormal_spare3;
        t_HystNormal_present = true;
        return 0;
    }
    if("spare2" == value)
    {
        t_HystNormal_internal_value = k_t_HystNormal_spare2;
        t_HystNormal_present = true;
        return 0;
    }
    if("spare1" == value)
    {
        t_HystNormal_internal_value = k_t_HystNormal_spare1;
        t_HystNormal_present = true;
        return 0;
    }
    return 1;
}

std::string MobilityStateParameters::t_HystNormal_ValueToString(t_HystNormal_Enum value) const
{
    if(k_t_HystNormal_s30 == value)
        return "s30";
    if(k_t_HystNormal_s60 == value)
        return "s60";
    if(k_t_HystNormal_s120 == value)
        return "s120";
    if(k_t_HystNormal_s180 == value)
        return "s180";
    if(k_t_HystNormal_s240 == value)
        return "s240";
    if(k_t_HystNormal_spare3 == value)
        return "spare3";
    if(k_t_HystNormal_spare2 == value)
        return "spare2";
    if(k_t_HystNormal_spare1 == value)
        return "spare1";
    return "";
}

uint64_t MobilityStateParameters::t_HystNormal_NumberOfValues() const
{
    return 8;
}

std::string MobilityStateParameters::t_HystNormal_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "t_HystNormal = " + t_HystNormal_ValueToString(t_HystNormal_internal_value) + "\n";
    return out;
}

std::string MobilityStateParameters::t_HystNormal_ToStringNoNewLines() const
{
    std::string out = "t_HystNormal=" + t_HystNormal_ValueToString(t_HystNormal_internal_value) + ",";
    return out;
}

int MobilityStateParameters::t_HystNormal_Clear()
{
    t_HystNormal_present = false;
    return 0;
}

bool MobilityStateParameters::t_HystNormal_IsPresent() const
{
    return t_HystNormal_present;
}

int MobilityStateParameters::n_CellChangeMedium_Pack(std::vector<uint8_t> &bits)
{
    if(!n_CellChangeMedium_present)
    {
        printf("MobilityStateParameters::n_CellChangeMedium_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = n_CellChangeMedium_internal_value - (1);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (16 - 1))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int MobilityStateParameters::n_CellChangeMedium_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return n_CellChangeMedium_Unpack(bits, idx);
}

int MobilityStateParameters::n_CellChangeMedium_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (16 - 1))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("MobilityStateParameters::n_CellChangeMedium_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    n_CellChangeMedium_internal_value = packed_val + 1;
    n_CellChangeMedium_present = true;
    return 0;
}

int64_t MobilityStateParameters::n_CellChangeMedium_Value() const
{
    if(n_CellChangeMedium_present)
        return n_CellChangeMedium_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int MobilityStateParameters::n_CellChangeMedium_SetValue(int64_t value)
{
    if(value < 1 || value > 16)
    {
        printf("MobilityStateParameters::n_CellChangeMedium_SetValue() range failure\n");
        return -1;
    }
    n_CellChangeMedium_internal_value = value;
    n_CellChangeMedium_present = true;
    return 0;
}

std::string MobilityStateParameters::n_CellChangeMedium_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "n_CellChangeMedium = " + std::to_string(n_CellChangeMedium_internal_value) + "\n";
    return out;
}

std::string MobilityStateParameters::n_CellChangeMedium_ToStringNoNewLines() const
{
    std::string out = "n_CellChangeMedium=" + std::to_string(n_CellChangeMedium_internal_value) + ",";
    return out;
}

int MobilityStateParameters::n_CellChangeMedium_Clear()
{
    n_CellChangeMedium_present = false;
    return 0;
}

bool MobilityStateParameters::n_CellChangeMedium_IsPresent() const
{
    return n_CellChangeMedium_present;
}

int MobilityStateParameters::n_CellChangeHigh_Pack(std::vector<uint8_t> &bits)
{
    if(!n_CellChangeHigh_present)
    {
        printf("MobilityStateParameters::n_CellChangeHigh_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = n_CellChangeHigh_internal_value - (1);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (16 - 1))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int MobilityStateParameters::n_CellChangeHigh_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return n_CellChangeHigh_Unpack(bits, idx);
}

int MobilityStateParameters::n_CellChangeHigh_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (16 - 1))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("MobilityStateParameters::n_CellChangeHigh_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    n_CellChangeHigh_internal_value = packed_val + 1;
    n_CellChangeHigh_present = true;
    return 0;
}

int64_t MobilityStateParameters::n_CellChangeHigh_Value() const
{
    if(n_CellChangeHigh_present)
        return n_CellChangeHigh_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int MobilityStateParameters::n_CellChangeHigh_SetValue(int64_t value)
{
    if(value < 1 || value > 16)
    {
        printf("MobilityStateParameters::n_CellChangeHigh_SetValue() range failure\n");
        return -1;
    }
    n_CellChangeHigh_internal_value = value;
    n_CellChangeHigh_present = true;
    return 0;
}

std::string MobilityStateParameters::n_CellChangeHigh_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "n_CellChangeHigh = " + std::to_string(n_CellChangeHigh_internal_value) + "\n";
    return out;
}

std::string MobilityStateParameters::n_CellChangeHigh_ToStringNoNewLines() const
{
    std::string out = "n_CellChangeHigh=" + std::to_string(n_CellChangeHigh_internal_value) + ",";
    return out;
}

int MobilityStateParameters::n_CellChangeHigh_Clear()
{
    n_CellChangeHigh_present = false;
    return 0;
}

bool MobilityStateParameters::n_CellChangeHigh_IsPresent() const
{
    return n_CellChangeHigh_present;
}

