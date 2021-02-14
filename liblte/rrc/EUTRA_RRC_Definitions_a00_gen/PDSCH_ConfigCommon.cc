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

#include "PDSCH_ConfigCommon.h"

#include <cmath>

int PDSCH_ConfigCommon::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != referenceSignalPower_Pack(bits))
        {
            printf("PDSCH_ConfigCommon:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != p_b_Pack(bits))
        {
            printf("PDSCH_ConfigCommon:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int PDSCH_ConfigCommon::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int PDSCH_ConfigCommon::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != referenceSignalPower_Unpack(bits, idx))
        {
            printf("PDSCH_ConfigCommon:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != p_b_Unpack(bits, idx))
        {
            printf("PDSCH_ConfigCommon:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string PDSCH_ConfigCommon::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "PDSCH_ConfigCommon:\n";
    out += referenceSignalPower_ToString(indent+1);
    out += p_b_ToString(indent+1);
    return out;
}

std::string PDSCH_ConfigCommon::ToStringNoNewLines() const
{
    std::string out = "PDSCH_ConfigCommon:";
    out += referenceSignalPower_ToStringNoNewLines();
    out += p_b_ToStringNoNewLines();
    return out;
}

int PDSCH_ConfigCommon::referenceSignalPower_Pack(std::vector<uint8_t> &bits)
{
    if(!referenceSignalPower_present)
    {
        printf("PDSCH_ConfigCommon::referenceSignalPower_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = referenceSignalPower_internal_value - (-60);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (50 - -60))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int PDSCH_ConfigCommon::referenceSignalPower_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return referenceSignalPower_Unpack(bits, idx);
}

int PDSCH_ConfigCommon::referenceSignalPower_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (50 - -60))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("PDSCH_ConfigCommon::referenceSignalPower_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    referenceSignalPower_internal_value = packed_val + -60;
    referenceSignalPower_present = true;
    return 0;
}

int64_t PDSCH_ConfigCommon::referenceSignalPower_Value() const
{
    if(referenceSignalPower_present)
        return referenceSignalPower_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int PDSCH_ConfigCommon::referenceSignalPower_SetValue(int64_t value)
{
    if(value < -60 || value > 50)
    {
        printf("PDSCH_ConfigCommon::referenceSignalPower_SetValue() range failure\n");
        return -1;
    }
    referenceSignalPower_internal_value = value;
    referenceSignalPower_present = true;
    return 0;
}

std::string PDSCH_ConfigCommon::referenceSignalPower_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "referenceSignalPower = " + std::to_string(referenceSignalPower_internal_value) + "\n";
    return out;
}

std::string PDSCH_ConfigCommon::referenceSignalPower_ToStringNoNewLines() const
{
    std::string out = "referenceSignalPower=" + std::to_string(referenceSignalPower_internal_value) + ",";
    return out;
}

int PDSCH_ConfigCommon::referenceSignalPower_Clear()
{
    referenceSignalPower_present = false;
    return 0;
}

bool PDSCH_ConfigCommon::referenceSignalPower_IsPresent() const
{
    return referenceSignalPower_present;
}

int PDSCH_ConfigCommon::p_b_Pack(std::vector<uint8_t> &bits)
{
    if(!p_b_present)
    {
        printf("PDSCH_ConfigCommon::p_b_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = p_b_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (3 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int PDSCH_ConfigCommon::p_b_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return p_b_Unpack(bits, idx);
}

int PDSCH_ConfigCommon::p_b_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (3 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("PDSCH_ConfigCommon::p_b_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    p_b_internal_value = packed_val + 0;
    p_b_present = true;
    return 0;
}

int64_t PDSCH_ConfigCommon::p_b_Value() const
{
    if(p_b_present)
        return p_b_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int PDSCH_ConfigCommon::p_b_SetValue(int64_t value)
{
    if(value < 0 || value > 3)
    {
        printf("PDSCH_ConfigCommon::p_b_SetValue() range failure\n");
        return -1;
    }
    p_b_internal_value = value;
    p_b_present = true;
    return 0;
}

std::string PDSCH_ConfigCommon::p_b_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "p_b = " + std::to_string(p_b_internal_value) + "\n";
    return out;
}

std::string PDSCH_ConfigCommon::p_b_ToStringNoNewLines() const
{
    std::string out = "p_b=" + std::to_string(p_b_internal_value) + ",";
    return out;
}

int PDSCH_ConfigCommon::p_b_Clear()
{
    p_b_present = false;
    return 0;
}

bool PDSCH_ConfigCommon::p_b_IsPresent() const
{
    return p_b_present;
}

