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

#include "UplinkPowerControlDedicated.h"

#include <cmath>

int UplinkPowerControlDedicated::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    if(!filterCoefficient_IsPresent() || filterCoefficient_Get().Value() == filterCoefficient_GetDefault())
    {
        bits.push_back(0);
    }else{
        bits.push_back(1);
    }

    // Fields
    {
        if(0 != p0_UE_PUSCH_Pack(bits))
        {
            printf("UplinkPowerControlDedicated:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != deltaMCS_Enabled_Pack(bits))
        {
            printf("UplinkPowerControlDedicated:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != accumulationEnabled_Pack(bits))
        {
            printf("UplinkPowerControlDedicated:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != p0_UE_PUCCH_Pack(bits))
        {
            printf("UplinkPowerControlDedicated:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != pSRS_Offset_Pack(bits))
        {
            printf("UplinkPowerControlDedicated:: field pack failure\n");
            return -1;
        }
    }
    if(filterCoefficient_IsPresent() || filterCoefficient_Get().Value() != filterCoefficient_GetDefault())
    {
        if(0 != filterCoefficient.Pack(bits))
        {
            printf("UplinkPowerControlDedicated:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int UplinkPowerControlDedicated::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int UplinkPowerControlDedicated::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("UplinkPowerControlDedicated::Unpack() index out of bounds for optional indiator filterCoefficient\n");
        return -1;
    }
    filterCoefficient_present = bits[idx++];

    // Fields
    {
        if(0 != p0_UE_PUSCH_Unpack(bits, idx))
        {
            printf("UplinkPowerControlDedicated:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != deltaMCS_Enabled_Unpack(bits, idx))
        {
            printf("UplinkPowerControlDedicated:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != accumulationEnabled_Unpack(bits, idx))
        {
            printf("UplinkPowerControlDedicated:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != p0_UE_PUCCH_Unpack(bits, idx))
        {
            printf("UplinkPowerControlDedicated:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != pSRS_Offset_Unpack(bits, idx))
        {
            printf("UplinkPowerControlDedicated:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != filterCoefficient.Unpack(bits, idx))
        {
            printf("UplinkPowerControlDedicated:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string UplinkPowerControlDedicated::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "UplinkPowerControlDedicated:\n";
    out += p0_UE_PUSCH_ToString(indent+1);
    out += deltaMCS_Enabled_ToString(indent+1);
    out += accumulationEnabled_ToString(indent+1);
    out += p0_UE_PUCCH_ToString(indent+1);
    out += pSRS_Offset_ToString(indent+1);
    out += filterCoefficient_ToString(indent+1);
    return out;
}

std::string UplinkPowerControlDedicated::ToStringNoNewLines() const
{
    std::string out = "UplinkPowerControlDedicated:";
    out += p0_UE_PUSCH_ToStringNoNewLines();
    out += deltaMCS_Enabled_ToStringNoNewLines();
    out += accumulationEnabled_ToStringNoNewLines();
    out += p0_UE_PUCCH_ToStringNoNewLines();
    out += pSRS_Offset_ToStringNoNewLines();
    out += filterCoefficient_ToStringNoNewLines();
    return out;
}

int UplinkPowerControlDedicated::p0_UE_PUSCH_Pack(std::vector<uint8_t> &bits)
{
    if(!p0_UE_PUSCH_present)
    {
        printf("UplinkPowerControlDedicated::p0_UE_PUSCH_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = p0_UE_PUSCH_internal_value - (-8);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (7 - -8))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int UplinkPowerControlDedicated::p0_UE_PUSCH_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return p0_UE_PUSCH_Unpack(bits, idx);
}

int UplinkPowerControlDedicated::p0_UE_PUSCH_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (7 - -8))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("UplinkPowerControlDedicated::p0_UE_PUSCH_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    p0_UE_PUSCH_internal_value = packed_val + -8;
    p0_UE_PUSCH_present = true;
    return 0;
}

int64_t UplinkPowerControlDedicated::p0_UE_PUSCH_Value() const
{
    if(p0_UE_PUSCH_present)
        return p0_UE_PUSCH_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int UplinkPowerControlDedicated::p0_UE_PUSCH_SetValue(int64_t value)
{
    if(value < -8 || value > 7)
    {
        printf("UplinkPowerControlDedicated::p0_UE_PUSCH_SetValue() range failure\n");
        return -1;
    }
    p0_UE_PUSCH_internal_value = value;
    p0_UE_PUSCH_present = true;
    return 0;
}

std::string UplinkPowerControlDedicated::p0_UE_PUSCH_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "p0_UE_PUSCH = " + std::to_string(p0_UE_PUSCH_internal_value) + "\n";
    return out;
}

std::string UplinkPowerControlDedicated::p0_UE_PUSCH_ToStringNoNewLines() const
{
    std::string out = "p0_UE_PUSCH=" + std::to_string(p0_UE_PUSCH_internal_value) + ",";
    return out;
}

int UplinkPowerControlDedicated::p0_UE_PUSCH_Clear()
{
    p0_UE_PUSCH_present = false;
    return 0;
}

bool UplinkPowerControlDedicated::p0_UE_PUSCH_IsPresent() const
{
    return p0_UE_PUSCH_present;
}

int UplinkPowerControlDedicated::deltaMCS_Enabled_Pack(std::vector<uint8_t> &bits)
{
    if(!deltaMCS_Enabled_present)
    {
        printf("UplinkPowerControlDedicated::deltaMCS_Enabled_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((deltaMCS_Enabled_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int UplinkPowerControlDedicated::deltaMCS_Enabled_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return deltaMCS_Enabled_Unpack(bits, idx);
}

int UplinkPowerControlDedicated::deltaMCS_Enabled_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("UplinkPowerControlDedicated::deltaMCS_Enabled_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 1)
    {
        printf("UplinkPowerControlDedicated::deltaMCS_Enabled_Unpack() max failure\n");
        return -1;
    }
    deltaMCS_Enabled_internal_value = (deltaMCS_Enabled_Enum)packed_val;
    deltaMCS_Enabled_present = true;
    return 0;
}

UplinkPowerControlDedicated::deltaMCS_Enabled_Enum UplinkPowerControlDedicated::deltaMCS_Enabled_Value() const
{
    if(deltaMCS_Enabled_present)
        return deltaMCS_Enabled_internal_value;
    return (UplinkPowerControlDedicated::deltaMCS_Enabled_Enum)0;
}

int UplinkPowerControlDedicated::deltaMCS_Enabled_SetValue(deltaMCS_Enabled_Enum value)
{
    deltaMCS_Enabled_internal_value = value;
    deltaMCS_Enabled_present = true;
    return 0;
}

int UplinkPowerControlDedicated::deltaMCS_Enabled_SetValue(std::string value)
{
    if("en0" == value)
    {
        deltaMCS_Enabled_internal_value = k_deltaMCS_Enabled_en0;
        deltaMCS_Enabled_present = true;
        return 0;
    }
    if("en1" == value)
    {
        deltaMCS_Enabled_internal_value = k_deltaMCS_Enabled_en1;
        deltaMCS_Enabled_present = true;
        return 0;
    }
    return 1;
}

std::string UplinkPowerControlDedicated::deltaMCS_Enabled_ValueToString(deltaMCS_Enabled_Enum value) const
{
    if(k_deltaMCS_Enabled_en0 == value)
        return "en0";
    if(k_deltaMCS_Enabled_en1 == value)
        return "en1";
    return "";
}

uint64_t UplinkPowerControlDedicated::deltaMCS_Enabled_NumberOfValues() const
{
    return 2;
}

std::string UplinkPowerControlDedicated::deltaMCS_Enabled_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "deltaMCS_Enabled = " + deltaMCS_Enabled_ValueToString(deltaMCS_Enabled_internal_value) + "\n";
    return out;
}

std::string UplinkPowerControlDedicated::deltaMCS_Enabled_ToStringNoNewLines() const
{
    std::string out = "deltaMCS_Enabled=" + deltaMCS_Enabled_ValueToString(deltaMCS_Enabled_internal_value) + ",";
    return out;
}

int UplinkPowerControlDedicated::deltaMCS_Enabled_Clear()
{
    deltaMCS_Enabled_present = false;
    return 0;
}

bool UplinkPowerControlDedicated::deltaMCS_Enabled_IsPresent() const
{
    return deltaMCS_Enabled_present;
}

int UplinkPowerControlDedicated::accumulationEnabled_Pack(std::vector<uint8_t> &bits)
{
    if(!accumulationEnabled_present)
    {
        printf("UplinkPowerControlDedicated::accumulationEnabled_Pack() presence failure\n");
        return -1;
    }
    bits.push_back(accumulationEnabled_internal_value);
    return 0;
}

int UplinkPowerControlDedicated::accumulationEnabled_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return accumulationEnabled_Unpack(bits, idx);
}

int UplinkPowerControlDedicated::accumulationEnabled_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    if((idx + 1) > bits.size())
    {
        printf("UplinkPowerControlDedicated::accumulationEnabled_Unpack() index out of bounds\n");
        return -1;
    }
    accumulationEnabled_internal_value = bits[idx++];
    accumulationEnabled_present = true;
    return 0;
}

bool UplinkPowerControlDedicated::accumulationEnabled_Value() const
{
    if(accumulationEnabled_present)
        return accumulationEnabled_internal_value;
    return false;
}

int UplinkPowerControlDedicated::accumulationEnabled_SetValue(bool value)
{
    accumulationEnabled_internal_value = value;
    accumulationEnabled_present = true;
    return 0;
}

std::string UplinkPowerControlDedicated::accumulationEnabled_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "accumulationEnabled = " + std::to_string(accumulationEnabled_internal_value) + "\n";
    return out;
}

std::string UplinkPowerControlDedicated::accumulationEnabled_ToStringNoNewLines() const
{
    std::string out = "accumulationEnabled=" + std::to_string(accumulationEnabled_internal_value) + ",";
    return out;
}

int UplinkPowerControlDedicated::accumulationEnabled_Clear()
{
    accumulationEnabled_present = false;
    return 0;
}

bool UplinkPowerControlDedicated::accumulationEnabled_IsPresent() const
{
    return accumulationEnabled_present;
}

int UplinkPowerControlDedicated::p0_UE_PUCCH_Pack(std::vector<uint8_t> &bits)
{
    if(!p0_UE_PUCCH_present)
    {
        printf("UplinkPowerControlDedicated::p0_UE_PUCCH_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = p0_UE_PUCCH_internal_value - (-8);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (7 - -8))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int UplinkPowerControlDedicated::p0_UE_PUCCH_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return p0_UE_PUCCH_Unpack(bits, idx);
}

int UplinkPowerControlDedicated::p0_UE_PUCCH_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (7 - -8))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("UplinkPowerControlDedicated::p0_UE_PUCCH_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    p0_UE_PUCCH_internal_value = packed_val + -8;
    p0_UE_PUCCH_present = true;
    return 0;
}

int64_t UplinkPowerControlDedicated::p0_UE_PUCCH_Value() const
{
    if(p0_UE_PUCCH_present)
        return p0_UE_PUCCH_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int UplinkPowerControlDedicated::p0_UE_PUCCH_SetValue(int64_t value)
{
    if(value < -8 || value > 7)
    {
        printf("UplinkPowerControlDedicated::p0_UE_PUCCH_SetValue() range failure\n");
        return -1;
    }
    p0_UE_PUCCH_internal_value = value;
    p0_UE_PUCCH_present = true;
    return 0;
}

std::string UplinkPowerControlDedicated::p0_UE_PUCCH_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "p0_UE_PUCCH = " + std::to_string(p0_UE_PUCCH_internal_value) + "\n";
    return out;
}

std::string UplinkPowerControlDedicated::p0_UE_PUCCH_ToStringNoNewLines() const
{
    std::string out = "p0_UE_PUCCH=" + std::to_string(p0_UE_PUCCH_internal_value) + ",";
    return out;
}

int UplinkPowerControlDedicated::p0_UE_PUCCH_Clear()
{
    p0_UE_PUCCH_present = false;
    return 0;
}

bool UplinkPowerControlDedicated::p0_UE_PUCCH_IsPresent() const
{
    return p0_UE_PUCCH_present;
}

int UplinkPowerControlDedicated::pSRS_Offset_Pack(std::vector<uint8_t> &bits)
{
    if(!pSRS_Offset_present)
    {
        printf("UplinkPowerControlDedicated::pSRS_Offset_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = pSRS_Offset_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (15 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int UplinkPowerControlDedicated::pSRS_Offset_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return pSRS_Offset_Unpack(bits, idx);
}

int UplinkPowerControlDedicated::pSRS_Offset_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (15 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("UplinkPowerControlDedicated::pSRS_Offset_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    pSRS_Offset_internal_value = packed_val + 0;
    pSRS_Offset_present = true;
    return 0;
}

int64_t UplinkPowerControlDedicated::pSRS_Offset_Value() const
{
    if(pSRS_Offset_present)
        return pSRS_Offset_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int UplinkPowerControlDedicated::pSRS_Offset_SetValue(int64_t value)
{
    if(value < 0 || value > 15)
    {
        printf("UplinkPowerControlDedicated::pSRS_Offset_SetValue() range failure\n");
        return -1;
    }
    pSRS_Offset_internal_value = value;
    pSRS_Offset_present = true;
    return 0;
}

std::string UplinkPowerControlDedicated::pSRS_Offset_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "pSRS_Offset = " + std::to_string(pSRS_Offset_internal_value) + "\n";
    return out;
}

std::string UplinkPowerControlDedicated::pSRS_Offset_ToStringNoNewLines() const
{
    std::string out = "pSRS_Offset=" + std::to_string(pSRS_Offset_internal_value) + ",";
    return out;
}

int UplinkPowerControlDedicated::pSRS_Offset_Clear()
{
    pSRS_Offset_present = false;
    return 0;
}

bool UplinkPowerControlDedicated::pSRS_Offset_IsPresent() const
{
    return pSRS_Offset_present;
}

FilterCoefficient* UplinkPowerControlDedicated::filterCoefficient_Set()
{
    filterCoefficient_present = true;
    return &filterCoefficient;
}

int UplinkPowerControlDedicated::filterCoefficient_Set(FilterCoefficient &value)
{
    filterCoefficient_present = true;
    filterCoefficient = value;
    return 0;
}

const FilterCoefficient& UplinkPowerControlDedicated::filterCoefficient_Get() const
{
    return filterCoefficient;
}

FilterCoefficient::Enum UplinkPowerControlDedicated::filterCoefficient_GetDefault() const
{
    return FilterCoefficient::k_fc4;
}

std::string UplinkPowerControlDedicated::filterCoefficient_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "filterCoefficient:\n";
    out += filterCoefficient.ToString(indent+1);
    return out;
}

std::string UplinkPowerControlDedicated::filterCoefficient_ToStringNoNewLines() const
{
    std::string out = "filterCoefficient:";
    out += filterCoefficient.ToStringNoNewLines();
    return out;
}

int UplinkPowerControlDedicated::filterCoefficient_Clear()
{
    filterCoefficient_present = false;
    return 0;
}

bool UplinkPowerControlDedicated::filterCoefficient_IsPresent() const
{
    return filterCoefficient_present;
}

