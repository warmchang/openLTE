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

#include "PUSCH_ConfigDedicated_v10x0.h"

#include <cmath>

int PUSCH_ConfigDedicated_v10x0::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(groupHoppingDisabled_r10_IsPresent());
    bits.push_back(dmrs_WithOCC_Activated_r10_IsPresent());

    // Fields
    {
        if(0 != betaOffset_ACK_Index_MC_r10_Pack(bits))
        {
            printf("PUSCH_ConfigDedicated_v10x0:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != betaOffset_RI_Index_MC_r10_Pack(bits))
        {
            printf("PUSCH_ConfigDedicated_v10x0:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != betaOffset_CQI_Index_MC_r10_Pack(bits))
        {
            printf("PUSCH_ConfigDedicated_v10x0:: field pack failure\n");
            return -1;
        }
    }
    if(groupHoppingDisabled_r10_IsPresent())
    {
        if(0 != groupHoppingDisabled_r10_Pack(bits))
        {
            printf("PUSCH_ConfigDedicated_v10x0:: field pack failure\n");
            return -1;
        }
    }
    if(dmrs_WithOCC_Activated_r10_IsPresent())
    {
        if(0 != dmrs_WithOCC_Activated_r10_Pack(bits))
        {
            printf("PUSCH_ConfigDedicated_v10x0:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int PUSCH_ConfigDedicated_v10x0::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int PUSCH_ConfigDedicated_v10x0::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("PUSCH_ConfigDedicated_v10x0::Unpack() index out of bounds for optional indiator groupHoppingDisabled_r10\n");
        return -1;
    }
    groupHoppingDisabled_r10_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("PUSCH_ConfigDedicated_v10x0::Unpack() index out of bounds for optional indiator dmrs_WithOCC_Activated_r10\n");
        return -1;
    }
    dmrs_WithOCC_Activated_r10_present = bits[idx++];

    // Fields
    {
        if(0 != betaOffset_ACK_Index_MC_r10_Unpack(bits, idx))
        {
            printf("PUSCH_ConfigDedicated_v10x0:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != betaOffset_RI_Index_MC_r10_Unpack(bits, idx))
        {
            printf("PUSCH_ConfigDedicated_v10x0:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != betaOffset_CQI_Index_MC_r10_Unpack(bits, idx))
        {
            printf("PUSCH_ConfigDedicated_v10x0:: field unpack failure\n");
            return -1;
        }
    }
    if(groupHoppingDisabled_r10_present)
    {
        if(0 != groupHoppingDisabled_r10_Unpack(bits, idx))
        {
            printf("PUSCH_ConfigDedicated_v10x0:: field unpack failure\n");
            return -1;
        }
    }
    if(dmrs_WithOCC_Activated_r10_present)
    {
        if(0 != dmrs_WithOCC_Activated_r10_Unpack(bits, idx))
        {
            printf("PUSCH_ConfigDedicated_v10x0:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string PUSCH_ConfigDedicated_v10x0::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "PUSCH_ConfigDedicated_v10x0:\n";
    out += betaOffset_ACK_Index_MC_r10_ToString(indent+1);
    out += betaOffset_RI_Index_MC_r10_ToString(indent+1);
    out += betaOffset_CQI_Index_MC_r10_ToString(indent+1);
    if(groupHoppingDisabled_r10_IsPresent())
        out += groupHoppingDisabled_r10_ToString(indent+1);
    if(dmrs_WithOCC_Activated_r10_IsPresent())
        out += dmrs_WithOCC_Activated_r10_ToString(indent+1);
    return out;
}

std::string PUSCH_ConfigDedicated_v10x0::ToStringNoNewLines() const
{
    std::string out = "PUSCH_ConfigDedicated_v10x0:";
    out += betaOffset_ACK_Index_MC_r10_ToStringNoNewLines();
    out += betaOffset_RI_Index_MC_r10_ToStringNoNewLines();
    out += betaOffset_CQI_Index_MC_r10_ToStringNoNewLines();
    if(groupHoppingDisabled_r10_IsPresent())
        out += groupHoppingDisabled_r10_ToStringNoNewLines();
    if(dmrs_WithOCC_Activated_r10_IsPresent())
        out += dmrs_WithOCC_Activated_r10_ToStringNoNewLines();
    return out;
}

int PUSCH_ConfigDedicated_v10x0::betaOffset_ACK_Index_MC_r10_Pack(std::vector<uint8_t> &bits)
{
    if(!betaOffset_ACK_Index_MC_r10_present)
    {
        printf("PUSCH_ConfigDedicated_v10x0::betaOffset_ACK_Index_MC_r10_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = betaOffset_ACK_Index_MC_r10_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (0 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int PUSCH_ConfigDedicated_v10x0::betaOffset_ACK_Index_MC_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return betaOffset_ACK_Index_MC_r10_Unpack(bits, idx);
}

int PUSCH_ConfigDedicated_v10x0::betaOffset_ACK_Index_MC_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (0 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("PUSCH_ConfigDedicated_v10x0::betaOffset_ACK_Index_MC_r10_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    betaOffset_ACK_Index_MC_r10_internal_value = packed_val + 0;
    betaOffset_ACK_Index_MC_r10_present = true;
    return 0;
}

int64_t PUSCH_ConfigDedicated_v10x0::betaOffset_ACK_Index_MC_r10_Value() const
{
    if(betaOffset_ACK_Index_MC_r10_present)
        return betaOffset_ACK_Index_MC_r10_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int PUSCH_ConfigDedicated_v10x0::betaOffset_ACK_Index_MC_r10_SetValue(int64_t value)
{
    if(value < 0 || value > 0)
    {
        printf("PUSCH_ConfigDedicated_v10x0::betaOffset_ACK_Index_MC_r10_SetValue() range failure\n");
        return -1;
    }
    betaOffset_ACK_Index_MC_r10_internal_value = value;
    betaOffset_ACK_Index_MC_r10_present = true;
    return 0;
}

std::string PUSCH_ConfigDedicated_v10x0::betaOffset_ACK_Index_MC_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "betaOffset_ACK_Index_MC_r10 = " + std::to_string(betaOffset_ACK_Index_MC_r10_internal_value) + "\n";
    return out;
}

std::string PUSCH_ConfigDedicated_v10x0::betaOffset_ACK_Index_MC_r10_ToStringNoNewLines() const
{
    std::string out = "betaOffset_ACK_Index_MC_r10=" + std::to_string(betaOffset_ACK_Index_MC_r10_internal_value) + ",";
    return out;
}

int PUSCH_ConfigDedicated_v10x0::betaOffset_ACK_Index_MC_r10_Clear()
{
    betaOffset_ACK_Index_MC_r10_present = false;
    return 0;
}

bool PUSCH_ConfigDedicated_v10x0::betaOffset_ACK_Index_MC_r10_IsPresent() const
{
    return betaOffset_ACK_Index_MC_r10_present;
}

int PUSCH_ConfigDedicated_v10x0::betaOffset_RI_Index_MC_r10_Pack(std::vector<uint8_t> &bits)
{
    if(!betaOffset_RI_Index_MC_r10_present)
    {
        printf("PUSCH_ConfigDedicated_v10x0::betaOffset_RI_Index_MC_r10_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = betaOffset_RI_Index_MC_r10_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (0 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int PUSCH_ConfigDedicated_v10x0::betaOffset_RI_Index_MC_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return betaOffset_RI_Index_MC_r10_Unpack(bits, idx);
}

int PUSCH_ConfigDedicated_v10x0::betaOffset_RI_Index_MC_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (0 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("PUSCH_ConfigDedicated_v10x0::betaOffset_RI_Index_MC_r10_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    betaOffset_RI_Index_MC_r10_internal_value = packed_val + 0;
    betaOffset_RI_Index_MC_r10_present = true;
    return 0;
}

int64_t PUSCH_ConfigDedicated_v10x0::betaOffset_RI_Index_MC_r10_Value() const
{
    if(betaOffset_RI_Index_MC_r10_present)
        return betaOffset_RI_Index_MC_r10_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int PUSCH_ConfigDedicated_v10x0::betaOffset_RI_Index_MC_r10_SetValue(int64_t value)
{
    if(value < 0 || value > 0)
    {
        printf("PUSCH_ConfigDedicated_v10x0::betaOffset_RI_Index_MC_r10_SetValue() range failure\n");
        return -1;
    }
    betaOffset_RI_Index_MC_r10_internal_value = value;
    betaOffset_RI_Index_MC_r10_present = true;
    return 0;
}

std::string PUSCH_ConfigDedicated_v10x0::betaOffset_RI_Index_MC_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "betaOffset_RI_Index_MC_r10 = " + std::to_string(betaOffset_RI_Index_MC_r10_internal_value) + "\n";
    return out;
}

std::string PUSCH_ConfigDedicated_v10x0::betaOffset_RI_Index_MC_r10_ToStringNoNewLines() const
{
    std::string out = "betaOffset_RI_Index_MC_r10=" + std::to_string(betaOffset_RI_Index_MC_r10_internal_value) + ",";
    return out;
}

int PUSCH_ConfigDedicated_v10x0::betaOffset_RI_Index_MC_r10_Clear()
{
    betaOffset_RI_Index_MC_r10_present = false;
    return 0;
}

bool PUSCH_ConfigDedicated_v10x0::betaOffset_RI_Index_MC_r10_IsPresent() const
{
    return betaOffset_RI_Index_MC_r10_present;
}

int PUSCH_ConfigDedicated_v10x0::betaOffset_CQI_Index_MC_r10_Pack(std::vector<uint8_t> &bits)
{
    if(!betaOffset_CQI_Index_MC_r10_present)
    {
        printf("PUSCH_ConfigDedicated_v10x0::betaOffset_CQI_Index_MC_r10_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = betaOffset_CQI_Index_MC_r10_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (0 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int PUSCH_ConfigDedicated_v10x0::betaOffset_CQI_Index_MC_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return betaOffset_CQI_Index_MC_r10_Unpack(bits, idx);
}

int PUSCH_ConfigDedicated_v10x0::betaOffset_CQI_Index_MC_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (0 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("PUSCH_ConfigDedicated_v10x0::betaOffset_CQI_Index_MC_r10_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    betaOffset_CQI_Index_MC_r10_internal_value = packed_val + 0;
    betaOffset_CQI_Index_MC_r10_present = true;
    return 0;
}

int64_t PUSCH_ConfigDedicated_v10x0::betaOffset_CQI_Index_MC_r10_Value() const
{
    if(betaOffset_CQI_Index_MC_r10_present)
        return betaOffset_CQI_Index_MC_r10_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int PUSCH_ConfigDedicated_v10x0::betaOffset_CQI_Index_MC_r10_SetValue(int64_t value)
{
    if(value < 0 || value > 0)
    {
        printf("PUSCH_ConfigDedicated_v10x0::betaOffset_CQI_Index_MC_r10_SetValue() range failure\n");
        return -1;
    }
    betaOffset_CQI_Index_MC_r10_internal_value = value;
    betaOffset_CQI_Index_MC_r10_present = true;
    return 0;
}

std::string PUSCH_ConfigDedicated_v10x0::betaOffset_CQI_Index_MC_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "betaOffset_CQI_Index_MC_r10 = " + std::to_string(betaOffset_CQI_Index_MC_r10_internal_value) + "\n";
    return out;
}

std::string PUSCH_ConfigDedicated_v10x0::betaOffset_CQI_Index_MC_r10_ToStringNoNewLines() const
{
    std::string out = "betaOffset_CQI_Index_MC_r10=" + std::to_string(betaOffset_CQI_Index_MC_r10_internal_value) + ",";
    return out;
}

int PUSCH_ConfigDedicated_v10x0::betaOffset_CQI_Index_MC_r10_Clear()
{
    betaOffset_CQI_Index_MC_r10_present = false;
    return 0;
}

bool PUSCH_ConfigDedicated_v10x0::betaOffset_CQI_Index_MC_r10_IsPresent() const
{
    return betaOffset_CQI_Index_MC_r10_present;
}

int PUSCH_ConfigDedicated_v10x0::groupHoppingDisabled_r10_Pack(std::vector<uint8_t> &bits)
{
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((groupHoppingDisabled_r10_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int PUSCH_ConfigDedicated_v10x0::groupHoppingDisabled_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return groupHoppingDisabled_r10_Unpack(bits, idx);
}

int PUSCH_ConfigDedicated_v10x0::groupHoppingDisabled_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("PUSCH_ConfigDedicated_v10x0::groupHoppingDisabled_r10_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 0)
    {
        printf("PUSCH_ConfigDedicated_v10x0::groupHoppingDisabled_r10_Unpack() max failure\n");
        return -1;
    }
    groupHoppingDisabled_r10_internal_value = (groupHoppingDisabled_r10_Enum)packed_val;
    groupHoppingDisabled_r10_present = true;
    return 0;
}

PUSCH_ConfigDedicated_v10x0::groupHoppingDisabled_r10_Enum PUSCH_ConfigDedicated_v10x0::groupHoppingDisabled_r10_Value() const
{
    if(groupHoppingDisabled_r10_present)
        return groupHoppingDisabled_r10_internal_value;
    return (PUSCH_ConfigDedicated_v10x0::groupHoppingDisabled_r10_Enum)0;
}

int PUSCH_ConfigDedicated_v10x0::groupHoppingDisabled_r10_SetValue(groupHoppingDisabled_r10_Enum value)
{
    groupHoppingDisabled_r10_internal_value = value;
    groupHoppingDisabled_r10_present = true;
    return 0;
}

int PUSCH_ConfigDedicated_v10x0::groupHoppingDisabled_r10_SetValue(std::string value)
{
    if("true" == value)
    {
        groupHoppingDisabled_r10_internal_value = k_groupHoppingDisabled_r10_true;
        groupHoppingDisabled_r10_present = true;
        return 0;
    }
    return 1;
}

std::string PUSCH_ConfigDedicated_v10x0::groupHoppingDisabled_r10_ValueToString(groupHoppingDisabled_r10_Enum value) const
{
    if(k_groupHoppingDisabled_r10_true == value)
        return "true";
    return "";
}

uint64_t PUSCH_ConfigDedicated_v10x0::groupHoppingDisabled_r10_NumberOfValues() const
{
    return 1;
}

std::string PUSCH_ConfigDedicated_v10x0::groupHoppingDisabled_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "groupHoppingDisabled_r10 = " + groupHoppingDisabled_r10_ValueToString(groupHoppingDisabled_r10_internal_value) + "\n";
    return out;
}

std::string PUSCH_ConfigDedicated_v10x0::groupHoppingDisabled_r10_ToStringNoNewLines() const
{
    std::string out = "groupHoppingDisabled_r10=" + groupHoppingDisabled_r10_ValueToString(groupHoppingDisabled_r10_internal_value) + ",";
    return out;
}

int PUSCH_ConfigDedicated_v10x0::groupHoppingDisabled_r10_Clear()
{
    groupHoppingDisabled_r10_present = false;
    return 0;
}

bool PUSCH_ConfigDedicated_v10x0::groupHoppingDisabled_r10_IsPresent() const
{
    return groupHoppingDisabled_r10_present;
}

int PUSCH_ConfigDedicated_v10x0::dmrs_WithOCC_Activated_r10_Pack(std::vector<uint8_t> &bits)
{
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((dmrs_WithOCC_Activated_r10_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int PUSCH_ConfigDedicated_v10x0::dmrs_WithOCC_Activated_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return dmrs_WithOCC_Activated_r10_Unpack(bits, idx);
}

int PUSCH_ConfigDedicated_v10x0::dmrs_WithOCC_Activated_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("PUSCH_ConfigDedicated_v10x0::dmrs_WithOCC_Activated_r10_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 0)
    {
        printf("PUSCH_ConfigDedicated_v10x0::dmrs_WithOCC_Activated_r10_Unpack() max failure\n");
        return -1;
    }
    dmrs_WithOCC_Activated_r10_internal_value = (dmrs_WithOCC_Activated_r10_Enum)packed_val;
    dmrs_WithOCC_Activated_r10_present = true;
    return 0;
}

PUSCH_ConfigDedicated_v10x0::dmrs_WithOCC_Activated_r10_Enum PUSCH_ConfigDedicated_v10x0::dmrs_WithOCC_Activated_r10_Value() const
{
    if(dmrs_WithOCC_Activated_r10_present)
        return dmrs_WithOCC_Activated_r10_internal_value;
    return (PUSCH_ConfigDedicated_v10x0::dmrs_WithOCC_Activated_r10_Enum)0;
}

int PUSCH_ConfigDedicated_v10x0::dmrs_WithOCC_Activated_r10_SetValue(dmrs_WithOCC_Activated_r10_Enum value)
{
    dmrs_WithOCC_Activated_r10_internal_value = value;
    dmrs_WithOCC_Activated_r10_present = true;
    return 0;
}

int PUSCH_ConfigDedicated_v10x0::dmrs_WithOCC_Activated_r10_SetValue(std::string value)
{
    if("true" == value)
    {
        dmrs_WithOCC_Activated_r10_internal_value = k_dmrs_WithOCC_Activated_r10_true;
        dmrs_WithOCC_Activated_r10_present = true;
        return 0;
    }
    return 1;
}

std::string PUSCH_ConfigDedicated_v10x0::dmrs_WithOCC_Activated_r10_ValueToString(dmrs_WithOCC_Activated_r10_Enum value) const
{
    if(k_dmrs_WithOCC_Activated_r10_true == value)
        return "true";
    return "";
}

uint64_t PUSCH_ConfigDedicated_v10x0::dmrs_WithOCC_Activated_r10_NumberOfValues() const
{
    return 1;
}

std::string PUSCH_ConfigDedicated_v10x0::dmrs_WithOCC_Activated_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "dmrs_WithOCC_Activated_r10 = " + dmrs_WithOCC_Activated_r10_ValueToString(dmrs_WithOCC_Activated_r10_internal_value) + "\n";
    return out;
}

std::string PUSCH_ConfigDedicated_v10x0::dmrs_WithOCC_Activated_r10_ToStringNoNewLines() const
{
    std::string out = "dmrs_WithOCC_Activated_r10=" + dmrs_WithOCC_Activated_r10_ValueToString(dmrs_WithOCC_Activated_r10_internal_value) + ",";
    return out;
}

int PUSCH_ConfigDedicated_v10x0::dmrs_WithOCC_Activated_r10_Clear()
{
    dmrs_WithOCC_Activated_r10_present = false;
    return 0;
}

bool PUSCH_ConfigDedicated_v10x0::dmrs_WithOCC_Activated_r10_IsPresent() const
{
    return dmrs_WithOCC_Activated_r10_present;
}

