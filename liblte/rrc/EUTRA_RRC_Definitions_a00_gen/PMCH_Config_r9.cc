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

#include "PMCH_Config_r9.h"

#include <cmath>

int PMCH_Config_r9::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator
    bits.push_back(0);

    // Optional indicators

    // Fields
    {
        if(0 != sf_AllocEnd_r9_Pack(bits))
        {
            printf("PMCH_Config_r9:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != dataMCS_r9_Pack(bits))
        {
            printf("PMCH_Config_r9:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != mch_SchedulingPeriod_r9_Pack(bits))
        {
            printf("PMCH_Config_r9:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int PMCH_Config_r9::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int PMCH_Config_r9::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("PMCH_Config_r9::Unpack() index out of bounds for extension\n");
        return -1;
    }
    idx++;

    // Optional indicators

    // Fields
    {
        if(0 != sf_AllocEnd_r9_Unpack(bits, idx))
        {
            printf("PMCH_Config_r9:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != dataMCS_r9_Unpack(bits, idx))
        {
            printf("PMCH_Config_r9:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != mch_SchedulingPeriod_r9_Unpack(bits, idx))
        {
            printf("PMCH_Config_r9:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string PMCH_Config_r9::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "PMCH_Config_r9:\n";
    out += sf_AllocEnd_r9_ToString(indent+1);
    out += dataMCS_r9_ToString(indent+1);
    out += mch_SchedulingPeriod_r9_ToString(indent+1);
    return out;
}

std::string PMCH_Config_r9::ToStringNoNewLines() const
{
    std::string out = "PMCH_Config_r9:";
    out += sf_AllocEnd_r9_ToStringNoNewLines();
    out += dataMCS_r9_ToStringNoNewLines();
    out += mch_SchedulingPeriod_r9_ToStringNoNewLines();
    return out;
}

int PMCH_Config_r9::sf_AllocEnd_r9_Pack(std::vector<uint8_t> &bits)
{
    if(!sf_AllocEnd_r9_present)
    {
        printf("PMCH_Config_r9::sf_AllocEnd_r9_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = sf_AllocEnd_r9_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (1535 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int PMCH_Config_r9::sf_AllocEnd_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return sf_AllocEnd_r9_Unpack(bits, idx);
}

int PMCH_Config_r9::sf_AllocEnd_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (1535 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("PMCH_Config_r9::sf_AllocEnd_r9_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    sf_AllocEnd_r9_internal_value = packed_val + 0;
    sf_AllocEnd_r9_present = true;
    return 0;
}

int64_t PMCH_Config_r9::sf_AllocEnd_r9_Value() const
{
    if(sf_AllocEnd_r9_present)
        return sf_AllocEnd_r9_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int PMCH_Config_r9::sf_AllocEnd_r9_SetValue(int64_t value)
{
    if(value < 0 || value > 1535)
    {
        printf("PMCH_Config_r9::sf_AllocEnd_r9_SetValue() range failure\n");
        return -1;
    }
    sf_AllocEnd_r9_internal_value = value;
    sf_AllocEnd_r9_present = true;
    return 0;
}

std::string PMCH_Config_r9::sf_AllocEnd_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "sf_AllocEnd_r9 = " + std::to_string(sf_AllocEnd_r9_internal_value) + "\n";
    return out;
}

std::string PMCH_Config_r9::sf_AllocEnd_r9_ToStringNoNewLines() const
{
    std::string out = "sf_AllocEnd_r9=" + std::to_string(sf_AllocEnd_r9_internal_value) + ",";
    return out;
}

int PMCH_Config_r9::sf_AllocEnd_r9_Clear()
{
    sf_AllocEnd_r9_present = false;
    return 0;
}

bool PMCH_Config_r9::sf_AllocEnd_r9_IsPresent() const
{
    return sf_AllocEnd_r9_present;
}

int PMCH_Config_r9::dataMCS_r9_Pack(std::vector<uint8_t> &bits)
{
    if(!dataMCS_r9_present)
    {
        printf("PMCH_Config_r9::dataMCS_r9_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = dataMCS_r9_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (28 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int PMCH_Config_r9::dataMCS_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return dataMCS_r9_Unpack(bits, idx);
}

int PMCH_Config_r9::dataMCS_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (28 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("PMCH_Config_r9::dataMCS_r9_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    dataMCS_r9_internal_value = packed_val + 0;
    dataMCS_r9_present = true;
    return 0;
}

int64_t PMCH_Config_r9::dataMCS_r9_Value() const
{
    if(dataMCS_r9_present)
        return dataMCS_r9_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int PMCH_Config_r9::dataMCS_r9_SetValue(int64_t value)
{
    if(value < 0 || value > 28)
    {
        printf("PMCH_Config_r9::dataMCS_r9_SetValue() range failure\n");
        return -1;
    }
    dataMCS_r9_internal_value = value;
    dataMCS_r9_present = true;
    return 0;
}

std::string PMCH_Config_r9::dataMCS_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "dataMCS_r9 = " + std::to_string(dataMCS_r9_internal_value) + "\n";
    return out;
}

std::string PMCH_Config_r9::dataMCS_r9_ToStringNoNewLines() const
{
    std::string out = "dataMCS_r9=" + std::to_string(dataMCS_r9_internal_value) + ",";
    return out;
}

int PMCH_Config_r9::dataMCS_r9_Clear()
{
    dataMCS_r9_present = false;
    return 0;
}

bool PMCH_Config_r9::dataMCS_r9_IsPresent() const
{
    return dataMCS_r9_present;
}

int PMCH_Config_r9::mch_SchedulingPeriod_r9_Pack(std::vector<uint8_t> &bits)
{
    if(!mch_SchedulingPeriod_r9_present)
    {
        printf("PMCH_Config_r9::mch_SchedulingPeriod_r9_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 3;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((mch_SchedulingPeriod_r9_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int PMCH_Config_r9::mch_SchedulingPeriod_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return mch_SchedulingPeriod_r9_Unpack(bits, idx);
}

int PMCH_Config_r9::mch_SchedulingPeriod_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 3;
    if((idx + N_bits) > bits.size())
    {
        printf("PMCH_Config_r9::mch_SchedulingPeriod_r9_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 7)
    {
        printf("PMCH_Config_r9::mch_SchedulingPeriod_r9_Unpack() max failure\n");
        return -1;
    }
    mch_SchedulingPeriod_r9_internal_value = (mch_SchedulingPeriod_r9_Enum)packed_val;
    mch_SchedulingPeriod_r9_present = true;
    return 0;
}

PMCH_Config_r9::mch_SchedulingPeriod_r9_Enum PMCH_Config_r9::mch_SchedulingPeriod_r9_Value() const
{
    if(mch_SchedulingPeriod_r9_present)
        return mch_SchedulingPeriod_r9_internal_value;
    return (PMCH_Config_r9::mch_SchedulingPeriod_r9_Enum)0;
}

int PMCH_Config_r9::mch_SchedulingPeriod_r9_SetValue(mch_SchedulingPeriod_r9_Enum value)
{
    mch_SchedulingPeriod_r9_internal_value = value;
    mch_SchedulingPeriod_r9_present = true;
    return 0;
}

int PMCH_Config_r9::mch_SchedulingPeriod_r9_SetValue(std::string value)
{
    if("rf8" == value)
    {
        mch_SchedulingPeriod_r9_internal_value = k_mch_SchedulingPeriod_r9_rf8;
        mch_SchedulingPeriod_r9_present = true;
        return 0;
    }
    if("rf16" == value)
    {
        mch_SchedulingPeriod_r9_internal_value = k_mch_SchedulingPeriod_r9_rf16;
        mch_SchedulingPeriod_r9_present = true;
        return 0;
    }
    if("rf32" == value)
    {
        mch_SchedulingPeriod_r9_internal_value = k_mch_SchedulingPeriod_r9_rf32;
        mch_SchedulingPeriod_r9_present = true;
        return 0;
    }
    if("rf64" == value)
    {
        mch_SchedulingPeriod_r9_internal_value = k_mch_SchedulingPeriod_r9_rf64;
        mch_SchedulingPeriod_r9_present = true;
        return 0;
    }
    if("rf128" == value)
    {
        mch_SchedulingPeriod_r9_internal_value = k_mch_SchedulingPeriod_r9_rf128;
        mch_SchedulingPeriod_r9_present = true;
        return 0;
    }
    if("rf256" == value)
    {
        mch_SchedulingPeriod_r9_internal_value = k_mch_SchedulingPeriod_r9_rf256;
        mch_SchedulingPeriod_r9_present = true;
        return 0;
    }
    if("rf512" == value)
    {
        mch_SchedulingPeriod_r9_internal_value = k_mch_SchedulingPeriod_r9_rf512;
        mch_SchedulingPeriod_r9_present = true;
        return 0;
    }
    if("rf1024" == value)
    {
        mch_SchedulingPeriod_r9_internal_value = k_mch_SchedulingPeriod_r9_rf1024;
        mch_SchedulingPeriod_r9_present = true;
        return 0;
    }
    return 1;
}

std::string PMCH_Config_r9::mch_SchedulingPeriod_r9_ValueToString(mch_SchedulingPeriod_r9_Enum value) const
{
    if(k_mch_SchedulingPeriod_r9_rf8 == value)
        return "rf8";
    if(k_mch_SchedulingPeriod_r9_rf16 == value)
        return "rf16";
    if(k_mch_SchedulingPeriod_r9_rf32 == value)
        return "rf32";
    if(k_mch_SchedulingPeriod_r9_rf64 == value)
        return "rf64";
    if(k_mch_SchedulingPeriod_r9_rf128 == value)
        return "rf128";
    if(k_mch_SchedulingPeriod_r9_rf256 == value)
        return "rf256";
    if(k_mch_SchedulingPeriod_r9_rf512 == value)
        return "rf512";
    if(k_mch_SchedulingPeriod_r9_rf1024 == value)
        return "rf1024";
    return "";
}

uint64_t PMCH_Config_r9::mch_SchedulingPeriod_r9_NumberOfValues() const
{
    return 8;
}

std::string PMCH_Config_r9::mch_SchedulingPeriod_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "mch_SchedulingPeriod_r9 = " + mch_SchedulingPeriod_r9_ValueToString(mch_SchedulingPeriod_r9_internal_value) + "\n";
    return out;
}

std::string PMCH_Config_r9::mch_SchedulingPeriod_r9_ToStringNoNewLines() const
{
    std::string out = "mch_SchedulingPeriod_r9=" + mch_SchedulingPeriod_r9_ValueToString(mch_SchedulingPeriod_r9_internal_value) + ",";
    return out;
}

int PMCH_Config_r9::mch_SchedulingPeriod_r9_Clear()
{
    mch_SchedulingPeriod_r9_present = false;
    return 0;
}

bool PMCH_Config_r9::mch_SchedulingPeriod_r9_IsPresent() const
{
    return mch_SchedulingPeriod_r9_present;
}

