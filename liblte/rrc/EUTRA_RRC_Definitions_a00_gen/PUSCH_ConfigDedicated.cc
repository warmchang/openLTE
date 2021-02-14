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

#include "PUSCH_ConfigDedicated.h"

#include <cmath>

int PUSCH_ConfigDedicated::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != betaOffset_ACK_Index_Pack(bits))
        {
            printf("PUSCH_ConfigDedicated:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != betaOffset_RI_Index_Pack(bits))
        {
            printf("PUSCH_ConfigDedicated:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != betaOffset_CQI_Index_Pack(bits))
        {
            printf("PUSCH_ConfigDedicated:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int PUSCH_ConfigDedicated::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int PUSCH_ConfigDedicated::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != betaOffset_ACK_Index_Unpack(bits, idx))
        {
            printf("PUSCH_ConfigDedicated:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != betaOffset_RI_Index_Unpack(bits, idx))
        {
            printf("PUSCH_ConfigDedicated:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != betaOffset_CQI_Index_Unpack(bits, idx))
        {
            printf("PUSCH_ConfigDedicated:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string PUSCH_ConfigDedicated::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "PUSCH_ConfigDedicated:\n";
    out += betaOffset_ACK_Index_ToString(indent+1);
    out += betaOffset_RI_Index_ToString(indent+1);
    out += betaOffset_CQI_Index_ToString(indent+1);
    return out;
}

std::string PUSCH_ConfigDedicated::ToStringNoNewLines() const
{
    std::string out = "PUSCH_ConfigDedicated:";
    out += betaOffset_ACK_Index_ToStringNoNewLines();
    out += betaOffset_RI_Index_ToStringNoNewLines();
    out += betaOffset_CQI_Index_ToStringNoNewLines();
    return out;
}

int PUSCH_ConfigDedicated::betaOffset_ACK_Index_Pack(std::vector<uint8_t> &bits)
{
    if(!betaOffset_ACK_Index_present)
    {
        printf("PUSCH_ConfigDedicated::betaOffset_ACK_Index_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = betaOffset_ACK_Index_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (15 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int PUSCH_ConfigDedicated::betaOffset_ACK_Index_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return betaOffset_ACK_Index_Unpack(bits, idx);
}

int PUSCH_ConfigDedicated::betaOffset_ACK_Index_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (15 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("PUSCH_ConfigDedicated::betaOffset_ACK_Index_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    betaOffset_ACK_Index_internal_value = packed_val + 0;
    betaOffset_ACK_Index_present = true;
    return 0;
}

int64_t PUSCH_ConfigDedicated::betaOffset_ACK_Index_Value() const
{
    if(betaOffset_ACK_Index_present)
        return betaOffset_ACK_Index_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int PUSCH_ConfigDedicated::betaOffset_ACK_Index_SetValue(int64_t value)
{
    if(value < 0 || value > 15)
    {
        printf("PUSCH_ConfigDedicated::betaOffset_ACK_Index_SetValue() range failure\n");
        return -1;
    }
    betaOffset_ACK_Index_internal_value = value;
    betaOffset_ACK_Index_present = true;
    return 0;
}

std::string PUSCH_ConfigDedicated::betaOffset_ACK_Index_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "betaOffset_ACK_Index = " + std::to_string(betaOffset_ACK_Index_internal_value) + "\n";
    return out;
}

std::string PUSCH_ConfigDedicated::betaOffset_ACK_Index_ToStringNoNewLines() const
{
    std::string out = "betaOffset_ACK_Index=" + std::to_string(betaOffset_ACK_Index_internal_value) + ",";
    return out;
}

int PUSCH_ConfigDedicated::betaOffset_ACK_Index_Clear()
{
    betaOffset_ACK_Index_present = false;
    return 0;
}

bool PUSCH_ConfigDedicated::betaOffset_ACK_Index_IsPresent() const
{
    return betaOffset_ACK_Index_present;
}

int PUSCH_ConfigDedicated::betaOffset_RI_Index_Pack(std::vector<uint8_t> &bits)
{
    if(!betaOffset_RI_Index_present)
    {
        printf("PUSCH_ConfigDedicated::betaOffset_RI_Index_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = betaOffset_RI_Index_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (15 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int PUSCH_ConfigDedicated::betaOffset_RI_Index_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return betaOffset_RI_Index_Unpack(bits, idx);
}

int PUSCH_ConfigDedicated::betaOffset_RI_Index_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (15 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("PUSCH_ConfigDedicated::betaOffset_RI_Index_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    betaOffset_RI_Index_internal_value = packed_val + 0;
    betaOffset_RI_Index_present = true;
    return 0;
}

int64_t PUSCH_ConfigDedicated::betaOffset_RI_Index_Value() const
{
    if(betaOffset_RI_Index_present)
        return betaOffset_RI_Index_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int PUSCH_ConfigDedicated::betaOffset_RI_Index_SetValue(int64_t value)
{
    if(value < 0 || value > 15)
    {
        printf("PUSCH_ConfigDedicated::betaOffset_RI_Index_SetValue() range failure\n");
        return -1;
    }
    betaOffset_RI_Index_internal_value = value;
    betaOffset_RI_Index_present = true;
    return 0;
}

std::string PUSCH_ConfigDedicated::betaOffset_RI_Index_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "betaOffset_RI_Index = " + std::to_string(betaOffset_RI_Index_internal_value) + "\n";
    return out;
}

std::string PUSCH_ConfigDedicated::betaOffset_RI_Index_ToStringNoNewLines() const
{
    std::string out = "betaOffset_RI_Index=" + std::to_string(betaOffset_RI_Index_internal_value) + ",";
    return out;
}

int PUSCH_ConfigDedicated::betaOffset_RI_Index_Clear()
{
    betaOffset_RI_Index_present = false;
    return 0;
}

bool PUSCH_ConfigDedicated::betaOffset_RI_Index_IsPresent() const
{
    return betaOffset_RI_Index_present;
}

int PUSCH_ConfigDedicated::betaOffset_CQI_Index_Pack(std::vector<uint8_t> &bits)
{
    if(!betaOffset_CQI_Index_present)
    {
        printf("PUSCH_ConfigDedicated::betaOffset_CQI_Index_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = betaOffset_CQI_Index_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (15 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int PUSCH_ConfigDedicated::betaOffset_CQI_Index_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return betaOffset_CQI_Index_Unpack(bits, idx);
}

int PUSCH_ConfigDedicated::betaOffset_CQI_Index_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (15 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("PUSCH_ConfigDedicated::betaOffset_CQI_Index_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    betaOffset_CQI_Index_internal_value = packed_val + 0;
    betaOffset_CQI_Index_present = true;
    return 0;
}

int64_t PUSCH_ConfigDedicated::betaOffset_CQI_Index_Value() const
{
    if(betaOffset_CQI_Index_present)
        return betaOffset_CQI_Index_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int PUSCH_ConfigDedicated::betaOffset_CQI_Index_SetValue(int64_t value)
{
    if(value < 0 || value > 15)
    {
        printf("PUSCH_ConfigDedicated::betaOffset_CQI_Index_SetValue() range failure\n");
        return -1;
    }
    betaOffset_CQI_Index_internal_value = value;
    betaOffset_CQI_Index_present = true;
    return 0;
}

std::string PUSCH_ConfigDedicated::betaOffset_CQI_Index_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "betaOffset_CQI_Index = " + std::to_string(betaOffset_CQI_Index_internal_value) + "\n";
    return out;
}

std::string PUSCH_ConfigDedicated::betaOffset_CQI_Index_ToStringNoNewLines() const
{
    std::string out = "betaOffset_CQI_Index=" + std::to_string(betaOffset_CQI_Index_internal_value) + ",";
    return out;
}

int PUSCH_ConfigDedicated::betaOffset_CQI_Index_Clear()
{
    betaOffset_CQI_Index_present = false;
    return 0;
}

bool PUSCH_ConfigDedicated::betaOffset_CQI_Index_IsPresent() const
{
    return betaOffset_CQI_Index_present;
}

