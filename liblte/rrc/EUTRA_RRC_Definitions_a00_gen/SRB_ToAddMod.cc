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

#include "SRB_ToAddMod.h"

#include <cmath>

int SRB_ToAddMod::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator
    bits.push_back(0);

    // Optional indicators
    bits.push_back(rlc_Config_IsPresent());
    bits.push_back(logicalChannelConfig_IsPresent());

    // Fields
    {
        if(0 != srb_Identity_Pack(bits))
        {
            printf("SRB_ToAddMod:: field pack failure\n");
            return -1;
        }
    }
    if(rlc_Config_IsPresent())
    {
        if(0 != rlc_Config_Pack(bits))
        {
            printf("SRB_ToAddMod:: field pack failure\n");
            return -1;
        }
    }
    if(logicalChannelConfig_IsPresent())
    {
        if(0 != logicalChannelConfig_Pack(bits))
        {
            printf("SRB_ToAddMod:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int SRB_ToAddMod::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int SRB_ToAddMod::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("SRB_ToAddMod::Unpack() index out of bounds for extension\n");
        return -1;
    }
    idx++;

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("SRB_ToAddMod::Unpack() index out of bounds for optional indiator rlc_Config\n");
        return -1;
    }
    rlc_Config_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("SRB_ToAddMod::Unpack() index out of bounds for optional indiator logicalChannelConfig\n");
        return -1;
    }
    logicalChannelConfig_present = bits[idx++];

    // Fields
    {
        if(0 != srb_Identity_Unpack(bits, idx))
        {
            printf("SRB_ToAddMod:: field unpack failure\n");
            return -1;
        }
    }
    if(rlc_Config_present)
    {
        if(0 != rlc_Config_Unpack(bits, idx))
        {
            printf("SRB_ToAddMod:: field unpack failure\n");
            return -1;
        }
    }
    if(logicalChannelConfig_present)
    {
        if(0 != logicalChannelConfig_Unpack(bits, idx))
        {
            printf("SRB_ToAddMod:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string SRB_ToAddMod::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "SRB_ToAddMod:\n";
    out += srb_Identity_ToString(indent+1);
    if(rlc_Config_IsPresent())
        out += rlc_Config_ToString(indent+1);
    if(logicalChannelConfig_IsPresent())
        out += logicalChannelConfig_ToString(indent+1);
    return out;
}

std::string SRB_ToAddMod::ToStringNoNewLines() const
{
    std::string out = "SRB_ToAddMod:";
    out += srb_Identity_ToStringNoNewLines();
    if(rlc_Config_IsPresent())
        out += rlc_Config_ToStringNoNewLines();
    if(logicalChannelConfig_IsPresent())
        out += logicalChannelConfig_ToStringNoNewLines();
    return out;
}

int SRB_ToAddMod::srb_Identity_Pack(std::vector<uint8_t> &bits)
{
    if(!srb_Identity_present)
    {
        printf("SRB_ToAddMod::srb_Identity_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = srb_Identity_internal_value - (1);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (2 - 1))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int SRB_ToAddMod::srb_Identity_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return srb_Identity_Unpack(bits, idx);
}

int SRB_ToAddMod::srb_Identity_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (2 - 1))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("SRB_ToAddMod::srb_Identity_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    srb_Identity_internal_value = packed_val + 1;
    srb_Identity_present = true;
    return 0;
}

int64_t SRB_ToAddMod::srb_Identity_Value() const
{
    if(srb_Identity_present)
        return srb_Identity_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int SRB_ToAddMod::srb_Identity_SetValue(int64_t value)
{
    if(value < 1 || value > 2)
    {
        printf("SRB_ToAddMod::srb_Identity_SetValue() range failure\n");
        return -1;
    }
    srb_Identity_internal_value = value;
    srb_Identity_present = true;
    return 0;
}

std::string SRB_ToAddMod::srb_Identity_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "srb_Identity = " + std::to_string(srb_Identity_internal_value) + "\n";
    return out;
}

std::string SRB_ToAddMod::srb_Identity_ToStringNoNewLines() const
{
    std::string out = "srb_Identity=" + std::to_string(srb_Identity_internal_value) + ",";
    return out;
}

int SRB_ToAddMod::srb_Identity_Clear()
{
    srb_Identity_present = false;
    return 0;
}

bool SRB_ToAddMod::srb_Identity_IsPresent() const
{
    return srb_Identity_present;
}

int SRB_ToAddMod::rlc_Config_Pack(std::vector<uint8_t> &bits)
{
    if(!rlc_Config_present)
    {
        printf("SRB_ToAddMod::rlc_Config_Pack() presence failure\n");
        return -1;
    }
    // Extension indicator

    // Choice
    for(uint32_t i=0; i<1; i++)
        bits.push_back((rlc_Config_internal_choice >> (1-i-1)) & 1);

    // Fields
    if(rlc_Config_internal_choice == k_rlc_Config_explicitValue)
    {
        if(0 != rlc_Config_explicitValue.Pack(bits))
        {
            printf("SRB_ToAddMod::rlc_Config_explicitValue pack failure\n");
            return -1;
        }
    }
    if(rlc_Config_internal_choice == k_rlc_Config_defaultValue)
    {
        if(0 != rlc_Config_defaultValue_Pack(bits))
        {
            printf("SRB_ToAddMod::rlc_Config_defaultValue pack failure\n");
            return -1;
        }
    }
    return 0;
}

int SRB_ToAddMod::rlc_Config_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return rlc_Config_Unpack(bits, idx);
}

int SRB_ToAddMod::rlc_Config_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 1) > bits.size())
    {
        printf("SRB_ToAddMod::rlc_Config_Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<1; i++)
        packed_val |= bits[idx++] << (1-i-1);

    if((SRB_ToAddMod::rlc_Config_Enum)packed_val > k_rlc_Config_defaultValue)
    {
        printf("SRB_ToAddMod::rlc_Config_Unpack() choice range failure\n");
        return -1;
    }
    rlc_Config_internal_choice = (SRB_ToAddMod::rlc_Config_Enum)packed_val;
    rlc_Config_present = true;

    // Fields
    if(rlc_Config_internal_choice == k_rlc_Config_explicitValue)
    {
        if(0 != rlc_Config_explicitValue.Unpack(bits, idx))
        {
            printf("SRB_ToAddMod::rlc_Config_explicitValue unpack failure\n");
            return -1;
        }
    }
    if(rlc_Config_internal_choice == k_rlc_Config_defaultValue)
    {
        if(0 != rlc_Config_defaultValue_Unpack(bits, idx))
        {
            printf("SRB_ToAddMod::rlc_Config_defaultValue unpack failure\n");
            return -1;
        }
    }
    return 0;
}

SRB_ToAddMod::rlc_Config_Enum SRB_ToAddMod::rlc_Config_Choice() const
{
    if(rlc_Config_present)
        return rlc_Config_internal_choice;
    return (SRB_ToAddMod::rlc_Config_Enum)0;
}

int SRB_ToAddMod::rlc_Config_SetChoice(SRB_ToAddMod::rlc_Config_Enum choice)
{
    rlc_Config_internal_choice = choice;
    rlc_Config_present = true;
    return 0;
}

std::string SRB_ToAddMod::rlc_Config_ChoiceToString(rlc_Config_Enum value) const
{
    if(k_rlc_Config_explicitValue == value)
        return "rlc_Config_explicitValue";
    if(k_rlc_Config_defaultValue == value)
        return "rlc_Config_defaultValue";
    return "";
}

uint64_t SRB_ToAddMod::rlc_Config_NumberOfChoices() const
{
    return 2;
}

std::string SRB_ToAddMod::rlc_Config_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "rlc_Config = " + rlc_Config_ChoiceToString(rlc_Config_internal_choice) + ":\n";
    if(rlc_Config_internal_choice == k_rlc_Config_explicitValue)
        out += rlc_Config_explicitValue.ToString(indent+1);
    return out;
}

std::string SRB_ToAddMod::rlc_Config_ToStringNoNewLines() const
{
    std::string out = "rlc_Config=" + rlc_Config_ChoiceToString(rlc_Config_internal_choice) + ",";
    if(rlc_Config_internal_choice == k_rlc_Config_explicitValue)
        out += rlc_Config_explicitValue.ToStringNoNewLines();
    return out;
}

int SRB_ToAddMod::rlc_Config_Clear()
{
    rlc_Config_present = false;
    return 0;
}

bool SRB_ToAddMod::rlc_Config_IsPresent() const
{
    return rlc_Config_present;
}

RLC_Config* SRB_ToAddMod::rlc_Config_explicitValue_Set()
{
    rlc_Config_explicitValue_present = true;
    return &rlc_Config_explicitValue;
}

int SRB_ToAddMod::rlc_Config_explicitValue_Set(RLC_Config &value)
{
    rlc_Config_explicitValue_present = true;
    rlc_Config_explicitValue = value;
    return 0;
}

const RLC_Config& SRB_ToAddMod::rlc_Config_explicitValue_Get() const
{
    return rlc_Config_explicitValue;
}

std::string SRB_ToAddMod::rlc_Config_explicitValue_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "explicitValue:\n";
    out += rlc_Config_explicitValue.ToString(indent+1);
    return out;
}

std::string SRB_ToAddMod::rlc_Config_explicitValue_ToStringNoNewLines() const
{
    std::string out = "explicitValue:";
    out += rlc_Config_explicitValue.ToStringNoNewLines();
    return out;
}

int SRB_ToAddMod::rlc_Config_explicitValue_Clear()
{
    rlc_Config_explicitValue_present = false;
    return 0;
}

bool SRB_ToAddMod::rlc_Config_explicitValue_IsPresent() const
{
    return rlc_Config_explicitValue_present;
}

int SRB_ToAddMod::logicalChannelConfig_Pack(std::vector<uint8_t> &bits)
{
    if(!logicalChannelConfig_present)
    {
        printf("SRB_ToAddMod::logicalChannelConfig_Pack() presence failure\n");
        return -1;
    }
    // Extension indicator

    // Choice
    for(uint32_t i=0; i<1; i++)
        bits.push_back((logicalChannelConfig_internal_choice >> (1-i-1)) & 1);

    // Fields
    if(logicalChannelConfig_internal_choice == k_logicalChannelConfig_explicitValue)
    {
        if(0 != logicalChannelConfig_explicitValue.Pack(bits))
        {
            printf("SRB_ToAddMod::logicalChannelConfig_explicitValue pack failure\n");
            return -1;
        }
    }
    if(logicalChannelConfig_internal_choice == k_logicalChannelConfig_defaultValue)
    {
        if(0 != logicalChannelConfig_defaultValue_Pack(bits))
        {
            printf("SRB_ToAddMod::logicalChannelConfig_defaultValue pack failure\n");
            return -1;
        }
    }
    return 0;
}

int SRB_ToAddMod::logicalChannelConfig_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return logicalChannelConfig_Unpack(bits, idx);
}

int SRB_ToAddMod::logicalChannelConfig_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 1) > bits.size())
    {
        printf("SRB_ToAddMod::logicalChannelConfig_Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<1; i++)
        packed_val |= bits[idx++] << (1-i-1);

    if((SRB_ToAddMod::logicalChannelConfig_Enum)packed_val > k_logicalChannelConfig_defaultValue)
    {
        printf("SRB_ToAddMod::logicalChannelConfig_Unpack() choice range failure\n");
        return -1;
    }
    logicalChannelConfig_internal_choice = (SRB_ToAddMod::logicalChannelConfig_Enum)packed_val;
    logicalChannelConfig_present = true;

    // Fields
    if(logicalChannelConfig_internal_choice == k_logicalChannelConfig_explicitValue)
    {
        if(0 != logicalChannelConfig_explicitValue.Unpack(bits, idx))
        {
            printf("SRB_ToAddMod::logicalChannelConfig_explicitValue unpack failure\n");
            return -1;
        }
    }
    if(logicalChannelConfig_internal_choice == k_logicalChannelConfig_defaultValue)
    {
        if(0 != logicalChannelConfig_defaultValue_Unpack(bits, idx))
        {
            printf("SRB_ToAddMod::logicalChannelConfig_defaultValue unpack failure\n");
            return -1;
        }
    }
    return 0;
}

SRB_ToAddMod::logicalChannelConfig_Enum SRB_ToAddMod::logicalChannelConfig_Choice() const
{
    if(logicalChannelConfig_present)
        return logicalChannelConfig_internal_choice;
    return (SRB_ToAddMod::logicalChannelConfig_Enum)0;
}

int SRB_ToAddMod::logicalChannelConfig_SetChoice(SRB_ToAddMod::logicalChannelConfig_Enum choice)
{
    logicalChannelConfig_internal_choice = choice;
    logicalChannelConfig_present = true;
    return 0;
}

std::string SRB_ToAddMod::logicalChannelConfig_ChoiceToString(logicalChannelConfig_Enum value) const
{
    if(k_logicalChannelConfig_explicitValue == value)
        return "logicalChannelConfig_explicitValue";
    if(k_logicalChannelConfig_defaultValue == value)
        return "logicalChannelConfig_defaultValue";
    return "";
}

uint64_t SRB_ToAddMod::logicalChannelConfig_NumberOfChoices() const
{
    return 2;
}

std::string SRB_ToAddMod::logicalChannelConfig_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "logicalChannelConfig = " + logicalChannelConfig_ChoiceToString(logicalChannelConfig_internal_choice) + ":\n";
    if(logicalChannelConfig_internal_choice == k_logicalChannelConfig_explicitValue)
        out += logicalChannelConfig_explicitValue.ToString(indent+1);
    return out;
}

std::string SRB_ToAddMod::logicalChannelConfig_ToStringNoNewLines() const
{
    std::string out = "logicalChannelConfig=" + logicalChannelConfig_ChoiceToString(logicalChannelConfig_internal_choice) + ",";
    if(logicalChannelConfig_internal_choice == k_logicalChannelConfig_explicitValue)
        out += logicalChannelConfig_explicitValue.ToStringNoNewLines();
    return out;
}

int SRB_ToAddMod::logicalChannelConfig_Clear()
{
    logicalChannelConfig_present = false;
    return 0;
}

bool SRB_ToAddMod::logicalChannelConfig_IsPresent() const
{
    return logicalChannelConfig_present;
}

LogicalChannelConfig* SRB_ToAddMod::logicalChannelConfig_explicitValue_Set()
{
    logicalChannelConfig_explicitValue_present = true;
    return &logicalChannelConfig_explicitValue;
}

int SRB_ToAddMod::logicalChannelConfig_explicitValue_Set(LogicalChannelConfig &value)
{
    logicalChannelConfig_explicitValue_present = true;
    logicalChannelConfig_explicitValue = value;
    return 0;
}

const LogicalChannelConfig& SRB_ToAddMod::logicalChannelConfig_explicitValue_Get() const
{
    return logicalChannelConfig_explicitValue;
}

std::string SRB_ToAddMod::logicalChannelConfig_explicitValue_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "explicitValue:\n";
    out += logicalChannelConfig_explicitValue.ToString(indent+1);
    return out;
}

std::string SRB_ToAddMod::logicalChannelConfig_explicitValue_ToStringNoNewLines() const
{
    std::string out = "explicitValue:";
    out += logicalChannelConfig_explicitValue.ToStringNoNewLines();
    return out;
}

int SRB_ToAddMod::logicalChannelConfig_explicitValue_Clear()
{
    logicalChannelConfig_explicitValue_present = false;
    return 0;
}

bool SRB_ToAddMod::logicalChannelConfig_explicitValue_IsPresent() const
{
    return logicalChannelConfig_explicitValue_present;
}

