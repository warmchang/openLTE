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

#include "SchedulingRequestConfig.h"

#include <cmath>

int SchedulingRequestConfig::Pack(std::vector<uint8_t> &bits)
{
    if(!present)
    {
        printf("SchedulingRequestConfig::Pack() presence failure\n");
        return -1;
    }
    // Extension indicator

    // Choice
    for(uint32_t i=0; i<1; i++)
        bits.push_back((internal_choice >> (1-i-1)) & 1);

    // Fields
    if(internal_choice == k_release)
    {
        if(0 != release_Pack(bits))
        {
            printf("SchedulingRequestConfig::release pack failure\n");
            return -1;
        }
    }
    if(internal_choice == k_setup)
    {
        if(0 != setup_value.Pack(bits))
        {
            printf("SchedulingRequestConfig::setup pack failure\n");
            return -1;
        }
    }
    return 0;
}

int SchedulingRequestConfig::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int SchedulingRequestConfig::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 1) > bits.size())
    {
        printf("SchedulingRequestConfig::Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<1; i++)
        packed_val |= bits[idx++] << (1-i-1);

    if((SchedulingRequestConfig::Enum)packed_val > k_setup)
    {
        printf("SchedulingRequestConfig::Unpack() choice range failure\n");
        return -1;
    }
    internal_choice = (SchedulingRequestConfig::Enum)packed_val;
    present = true;

    // Fields
    if(internal_choice == k_release)
    {
        if(0 != release_Unpack(bits, idx))
        {
            printf("SchedulingRequestConfig::release unpack failure\n");
            return -1;
        }
    }
    if(internal_choice == k_setup)
    {
        if(0 != setup_value.Unpack(bits, idx))
        {
            printf("SchedulingRequestConfig::setup unpack failure\n");
            return -1;
        }
    }
    return 0;
}

SchedulingRequestConfig::Enum SchedulingRequestConfig::Choice() const
{
    if(present)
        return internal_choice;
    return (SchedulingRequestConfig::Enum)0;
}

int SchedulingRequestConfig::SetChoice(SchedulingRequestConfig::Enum choice)
{
    internal_choice = choice;
    present = true;
    return 0;
}

std::string SchedulingRequestConfig::ChoiceToString(Enum value) const
{
    if(k_release == value)
        return "release";
    if(k_setup == value)
        return "setup";
    return "";
}

uint64_t SchedulingRequestConfig::NumberOfChoices() const
{
    return 2;
}

std::string SchedulingRequestConfig::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "SchedulingRequestConfig = " + ChoiceToString(internal_choice) + ":\n";
    if(internal_choice == k_setup)
        out += setup_value.ToString(indent+1);
    return out;
}

std::string SchedulingRequestConfig::ToStringNoNewLines() const
{
    std::string out = "SchedulingRequestConfig=" + ChoiceToString(internal_choice) + ",";
    if(internal_choice == k_setup)
        out += setup_value.ToStringNoNewLines();
    return out;
}

int SchedulingRequestConfig::Clear()
{
    present = false;
    return 0;
}

bool SchedulingRequestConfig::IsPresent() const
{
    return present;
}

int SchedulingRequestConfig::setup::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != sr_PUCCH_ResourceIndex_Pack(bits))
        {
            printf("SchedulingRequestConfig::setup:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != sr_ConfigIndex_Pack(bits))
        {
            printf("SchedulingRequestConfig::setup:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != dsr_TransMax_Pack(bits))
        {
            printf("SchedulingRequestConfig::setup:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int SchedulingRequestConfig::setup::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int SchedulingRequestConfig::setup::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != sr_PUCCH_ResourceIndex_Unpack(bits, idx))
        {
            printf("SchedulingRequestConfig::setup:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != sr_ConfigIndex_Unpack(bits, idx))
        {
            printf("SchedulingRequestConfig::setup:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != dsr_TransMax_Unpack(bits, idx))
        {
            printf("SchedulingRequestConfig::setup:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string SchedulingRequestConfig::setup::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "setup:\n";
    out += sr_PUCCH_ResourceIndex_ToString(indent+1);
    out += sr_ConfigIndex_ToString(indent+1);
    out += dsr_TransMax_ToString(indent+1);
    return out;
}

std::string SchedulingRequestConfig::setup::ToStringNoNewLines() const
{
    std::string out = "setup:";
    out += sr_PUCCH_ResourceIndex_ToStringNoNewLines();
    out += sr_ConfigIndex_ToStringNoNewLines();
    out += dsr_TransMax_ToStringNoNewLines();
    return out;
}

int SchedulingRequestConfig::setup::sr_PUCCH_ResourceIndex_Pack(std::vector<uint8_t> &bits)
{
    if(!sr_PUCCH_ResourceIndex_present)
    {
        printf("SchedulingRequestConfig::setup::sr_PUCCH_ResourceIndex_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = sr_PUCCH_ResourceIndex_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (2047 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int SchedulingRequestConfig::setup::sr_PUCCH_ResourceIndex_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return sr_PUCCH_ResourceIndex_Unpack(bits, idx);
}

int SchedulingRequestConfig::setup::sr_PUCCH_ResourceIndex_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (2047 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("SchedulingRequestConfig::setup::sr_PUCCH_ResourceIndex_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    sr_PUCCH_ResourceIndex_internal_value = packed_val + 0;
    sr_PUCCH_ResourceIndex_present = true;
    return 0;
}

int64_t SchedulingRequestConfig::setup::sr_PUCCH_ResourceIndex_Value() const
{
    if(sr_PUCCH_ResourceIndex_present)
        return sr_PUCCH_ResourceIndex_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int SchedulingRequestConfig::setup::sr_PUCCH_ResourceIndex_SetValue(int64_t value)
{
    if(value < 0 || value > 2047)
    {
        printf("SchedulingRequestConfig::setup::sr_PUCCH_ResourceIndex_SetValue() range failure\n");
        return -1;
    }
    sr_PUCCH_ResourceIndex_internal_value = value;
    sr_PUCCH_ResourceIndex_present = true;
    return 0;
}

std::string SchedulingRequestConfig::setup::sr_PUCCH_ResourceIndex_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "sr_PUCCH_ResourceIndex = " + std::to_string(sr_PUCCH_ResourceIndex_internal_value) + "\n";
    return out;
}

std::string SchedulingRequestConfig::setup::sr_PUCCH_ResourceIndex_ToStringNoNewLines() const
{
    std::string out = "sr_PUCCH_ResourceIndex=" + std::to_string(sr_PUCCH_ResourceIndex_internal_value) + ",";
    return out;
}

int SchedulingRequestConfig::setup::sr_PUCCH_ResourceIndex_Clear()
{
    sr_PUCCH_ResourceIndex_present = false;
    return 0;
}

bool SchedulingRequestConfig::setup::sr_PUCCH_ResourceIndex_IsPresent() const
{
    return sr_PUCCH_ResourceIndex_present;
}

int SchedulingRequestConfig::setup::sr_ConfigIndex_Pack(std::vector<uint8_t> &bits)
{
    if(!sr_ConfigIndex_present)
    {
        printf("SchedulingRequestConfig::setup::sr_ConfigIndex_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = sr_ConfigIndex_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (157 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int SchedulingRequestConfig::setup::sr_ConfigIndex_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return sr_ConfigIndex_Unpack(bits, idx);
}

int SchedulingRequestConfig::setup::sr_ConfigIndex_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (157 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("SchedulingRequestConfig::setup::sr_ConfigIndex_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    sr_ConfigIndex_internal_value = packed_val + 0;
    sr_ConfigIndex_present = true;
    return 0;
}

int64_t SchedulingRequestConfig::setup::sr_ConfigIndex_Value() const
{
    if(sr_ConfigIndex_present)
        return sr_ConfigIndex_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int SchedulingRequestConfig::setup::sr_ConfigIndex_SetValue(int64_t value)
{
    if(value < 0 || value > 157)
    {
        printf("SchedulingRequestConfig::setup::sr_ConfigIndex_SetValue() range failure\n");
        return -1;
    }
    sr_ConfigIndex_internal_value = value;
    sr_ConfigIndex_present = true;
    return 0;
}

std::string SchedulingRequestConfig::setup::sr_ConfigIndex_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "sr_ConfigIndex = " + std::to_string(sr_ConfigIndex_internal_value) + "\n";
    return out;
}

std::string SchedulingRequestConfig::setup::sr_ConfigIndex_ToStringNoNewLines() const
{
    std::string out = "sr_ConfigIndex=" + std::to_string(sr_ConfigIndex_internal_value) + ",";
    return out;
}

int SchedulingRequestConfig::setup::sr_ConfigIndex_Clear()
{
    sr_ConfigIndex_present = false;
    return 0;
}

bool SchedulingRequestConfig::setup::sr_ConfigIndex_IsPresent() const
{
    return sr_ConfigIndex_present;
}

int SchedulingRequestConfig::setup::dsr_TransMax_Pack(std::vector<uint8_t> &bits)
{
    if(!dsr_TransMax_present)
    {
        printf("SchedulingRequestConfig::setup::dsr_TransMax_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 3;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((dsr_TransMax_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int SchedulingRequestConfig::setup::dsr_TransMax_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return dsr_TransMax_Unpack(bits, idx);
}

int SchedulingRequestConfig::setup::dsr_TransMax_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 3;
    if((idx + N_bits) > bits.size())
    {
        printf("SchedulingRequestConfig::setup::dsr_TransMax_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 7)
    {
        printf("SchedulingRequestConfig::setup::dsr_TransMax_Unpack() max failure\n");
        return -1;
    }
    dsr_TransMax_internal_value = (dsr_TransMax_Enum)packed_val;
    dsr_TransMax_present = true;
    return 0;
}

SchedulingRequestConfig::setup::dsr_TransMax_Enum SchedulingRequestConfig::setup::dsr_TransMax_Value() const
{
    if(dsr_TransMax_present)
        return dsr_TransMax_internal_value;
    return (SchedulingRequestConfig::setup::dsr_TransMax_Enum)0;
}

int SchedulingRequestConfig::setup::dsr_TransMax_SetValue(dsr_TransMax_Enum value)
{
    dsr_TransMax_internal_value = value;
    dsr_TransMax_present = true;
    return 0;
}

int SchedulingRequestConfig::setup::dsr_TransMax_SetValue(std::string value)
{
    if("n4" == value)
    {
        dsr_TransMax_internal_value = k_dsr_TransMax_n4;
        dsr_TransMax_present = true;
        return 0;
    }
    if("n8" == value)
    {
        dsr_TransMax_internal_value = k_dsr_TransMax_n8;
        dsr_TransMax_present = true;
        return 0;
    }
    if("n16" == value)
    {
        dsr_TransMax_internal_value = k_dsr_TransMax_n16;
        dsr_TransMax_present = true;
        return 0;
    }
    if("n32" == value)
    {
        dsr_TransMax_internal_value = k_dsr_TransMax_n32;
        dsr_TransMax_present = true;
        return 0;
    }
    if("n64" == value)
    {
        dsr_TransMax_internal_value = k_dsr_TransMax_n64;
        dsr_TransMax_present = true;
        return 0;
    }
    if("spare3" == value)
    {
        dsr_TransMax_internal_value = k_dsr_TransMax_spare3;
        dsr_TransMax_present = true;
        return 0;
    }
    if("spare2" == value)
    {
        dsr_TransMax_internal_value = k_dsr_TransMax_spare2;
        dsr_TransMax_present = true;
        return 0;
    }
    if("spare1" == value)
    {
        dsr_TransMax_internal_value = k_dsr_TransMax_spare1;
        dsr_TransMax_present = true;
        return 0;
    }
    return 1;
}

std::string SchedulingRequestConfig::setup::dsr_TransMax_ValueToString(dsr_TransMax_Enum value) const
{
    if(k_dsr_TransMax_n4 == value)
        return "n4";
    if(k_dsr_TransMax_n8 == value)
        return "n8";
    if(k_dsr_TransMax_n16 == value)
        return "n16";
    if(k_dsr_TransMax_n32 == value)
        return "n32";
    if(k_dsr_TransMax_n64 == value)
        return "n64";
    if(k_dsr_TransMax_spare3 == value)
        return "spare3";
    if(k_dsr_TransMax_spare2 == value)
        return "spare2";
    if(k_dsr_TransMax_spare1 == value)
        return "spare1";
    return "";
}

uint64_t SchedulingRequestConfig::setup::dsr_TransMax_NumberOfValues() const
{
    return 8;
}

std::string SchedulingRequestConfig::setup::dsr_TransMax_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "dsr_TransMax = " + dsr_TransMax_ValueToString(dsr_TransMax_internal_value) + "\n";
    return out;
}

std::string SchedulingRequestConfig::setup::dsr_TransMax_ToStringNoNewLines() const
{
    std::string out = "dsr_TransMax=" + dsr_TransMax_ValueToString(dsr_TransMax_internal_value) + ",";
    return out;
}

int SchedulingRequestConfig::setup::dsr_TransMax_Clear()
{
    dsr_TransMax_present = false;
    return 0;
}

bool SchedulingRequestConfig::setup::dsr_TransMax_IsPresent() const
{
    return dsr_TransMax_present;
}

