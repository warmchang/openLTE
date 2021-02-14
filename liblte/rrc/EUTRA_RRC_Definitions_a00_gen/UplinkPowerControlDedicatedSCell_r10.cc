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

#include "UplinkPowerControlDedicatedSCell_r10.h"

#include <cmath>

int UplinkPowerControlDedicatedSCell_r10::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    if(!filterCoefficient_r10_IsPresent() || filterCoefficient_r10_Get().Value() == filterCoefficient_r10_GetDefault())
    {
        bits.push_back(0);
    }else{
        bits.push_back(1);
    }

    // Fields
    {
        if(0 != p0_UE_PUSCH_r10_Pack(bits))
        {
            printf("UplinkPowerControlDedicatedSCell_r10:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != deltaMCS_Enabled_r10_Pack(bits))
        {
            printf("UplinkPowerControlDedicatedSCell_r10:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != accumulationEnabled_r10_Pack(bits))
        {
            printf("UplinkPowerControlDedicatedSCell_r10:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != pSRS_Offset_r10_Pack(bits))
        {
            printf("UplinkPowerControlDedicatedSCell_r10:: field pack failure\n");
            return -1;
        }
    }
    if(filterCoefficient_r10_IsPresent() || filterCoefficient_r10_Get().Value() != filterCoefficient_r10_GetDefault())
    {
        if(0 != filterCoefficient_r10.Pack(bits))
        {
            printf("UplinkPowerControlDedicatedSCell_r10:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != pathlossReference_r10_Pack(bits))
        {
            printf("UplinkPowerControlDedicatedSCell_r10:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int UplinkPowerControlDedicatedSCell_r10::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int UplinkPowerControlDedicatedSCell_r10::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("UplinkPowerControlDedicatedSCell_r10::Unpack() index out of bounds for optional indiator filterCoefficient_r10\n");
        return -1;
    }
    filterCoefficient_r10_present = bits[idx++];

    // Fields
    {
        if(0 != p0_UE_PUSCH_r10_Unpack(bits, idx))
        {
            printf("UplinkPowerControlDedicatedSCell_r10:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != deltaMCS_Enabled_r10_Unpack(bits, idx))
        {
            printf("UplinkPowerControlDedicatedSCell_r10:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != accumulationEnabled_r10_Unpack(bits, idx))
        {
            printf("UplinkPowerControlDedicatedSCell_r10:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != pSRS_Offset_r10_Unpack(bits, idx))
        {
            printf("UplinkPowerControlDedicatedSCell_r10:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != filterCoefficient_r10.Unpack(bits, idx))
        {
            printf("UplinkPowerControlDedicatedSCell_r10:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != pathlossReference_r10_Unpack(bits, idx))
        {
            printf("UplinkPowerControlDedicatedSCell_r10:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string UplinkPowerControlDedicatedSCell_r10::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "UplinkPowerControlDedicatedSCell_r10:\n";
    out += p0_UE_PUSCH_r10_ToString(indent+1);
    out += deltaMCS_Enabled_r10_ToString(indent+1);
    out += accumulationEnabled_r10_ToString(indent+1);
    out += pSRS_Offset_r10_ToString(indent+1);
    out += filterCoefficient_r10_ToString(indent+1);
    out += pathlossReference_r10_ToString(indent+1);
    return out;
}

std::string UplinkPowerControlDedicatedSCell_r10::ToStringNoNewLines() const
{
    std::string out = "UplinkPowerControlDedicatedSCell_r10:";
    out += p0_UE_PUSCH_r10_ToStringNoNewLines();
    out += deltaMCS_Enabled_r10_ToStringNoNewLines();
    out += accumulationEnabled_r10_ToStringNoNewLines();
    out += pSRS_Offset_r10_ToStringNoNewLines();
    out += filterCoefficient_r10_ToStringNoNewLines();
    out += pathlossReference_r10_ToStringNoNewLines();
    return out;
}

int UplinkPowerControlDedicatedSCell_r10::p0_UE_PUSCH_r10_Pack(std::vector<uint8_t> &bits)
{
    if(!p0_UE_PUSCH_r10_present)
    {
        printf("UplinkPowerControlDedicatedSCell_r10::p0_UE_PUSCH_r10_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = p0_UE_PUSCH_r10_internal_value - (-8);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (7 - -8))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int UplinkPowerControlDedicatedSCell_r10::p0_UE_PUSCH_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return p0_UE_PUSCH_r10_Unpack(bits, idx);
}

int UplinkPowerControlDedicatedSCell_r10::p0_UE_PUSCH_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (7 - -8))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("UplinkPowerControlDedicatedSCell_r10::p0_UE_PUSCH_r10_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    p0_UE_PUSCH_r10_internal_value = packed_val + -8;
    p0_UE_PUSCH_r10_present = true;
    return 0;
}

int64_t UplinkPowerControlDedicatedSCell_r10::p0_UE_PUSCH_r10_Value() const
{
    if(p0_UE_PUSCH_r10_present)
        return p0_UE_PUSCH_r10_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int UplinkPowerControlDedicatedSCell_r10::p0_UE_PUSCH_r10_SetValue(int64_t value)
{
    if(value < -8 || value > 7)
    {
        printf("UplinkPowerControlDedicatedSCell_r10::p0_UE_PUSCH_r10_SetValue() range failure\n");
        return -1;
    }
    p0_UE_PUSCH_r10_internal_value = value;
    p0_UE_PUSCH_r10_present = true;
    return 0;
}

std::string UplinkPowerControlDedicatedSCell_r10::p0_UE_PUSCH_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "p0_UE_PUSCH_r10 = " + std::to_string(p0_UE_PUSCH_r10_internal_value) + "\n";
    return out;
}

std::string UplinkPowerControlDedicatedSCell_r10::p0_UE_PUSCH_r10_ToStringNoNewLines() const
{
    std::string out = "p0_UE_PUSCH_r10=" + std::to_string(p0_UE_PUSCH_r10_internal_value) + ",";
    return out;
}

int UplinkPowerControlDedicatedSCell_r10::p0_UE_PUSCH_r10_Clear()
{
    p0_UE_PUSCH_r10_present = false;
    return 0;
}

bool UplinkPowerControlDedicatedSCell_r10::p0_UE_PUSCH_r10_IsPresent() const
{
    return p0_UE_PUSCH_r10_present;
}

int UplinkPowerControlDedicatedSCell_r10::deltaMCS_Enabled_r10_Pack(std::vector<uint8_t> &bits)
{
    if(!deltaMCS_Enabled_r10_present)
    {
        printf("UplinkPowerControlDedicatedSCell_r10::deltaMCS_Enabled_r10_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((deltaMCS_Enabled_r10_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int UplinkPowerControlDedicatedSCell_r10::deltaMCS_Enabled_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return deltaMCS_Enabled_r10_Unpack(bits, idx);
}

int UplinkPowerControlDedicatedSCell_r10::deltaMCS_Enabled_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("UplinkPowerControlDedicatedSCell_r10::deltaMCS_Enabled_r10_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 1)
    {
        printf("UplinkPowerControlDedicatedSCell_r10::deltaMCS_Enabled_r10_Unpack() max failure\n");
        return -1;
    }
    deltaMCS_Enabled_r10_internal_value = (deltaMCS_Enabled_r10_Enum)packed_val;
    deltaMCS_Enabled_r10_present = true;
    return 0;
}

UplinkPowerControlDedicatedSCell_r10::deltaMCS_Enabled_r10_Enum UplinkPowerControlDedicatedSCell_r10::deltaMCS_Enabled_r10_Value() const
{
    if(deltaMCS_Enabled_r10_present)
        return deltaMCS_Enabled_r10_internal_value;
    return (UplinkPowerControlDedicatedSCell_r10::deltaMCS_Enabled_r10_Enum)0;
}

int UplinkPowerControlDedicatedSCell_r10::deltaMCS_Enabled_r10_SetValue(deltaMCS_Enabled_r10_Enum value)
{
    deltaMCS_Enabled_r10_internal_value = value;
    deltaMCS_Enabled_r10_present = true;
    return 0;
}

int UplinkPowerControlDedicatedSCell_r10::deltaMCS_Enabled_r10_SetValue(std::string value)
{
    if("en0" == value)
    {
        deltaMCS_Enabled_r10_internal_value = k_deltaMCS_Enabled_r10_en0;
        deltaMCS_Enabled_r10_present = true;
        return 0;
    }
    if("en1" == value)
    {
        deltaMCS_Enabled_r10_internal_value = k_deltaMCS_Enabled_r10_en1;
        deltaMCS_Enabled_r10_present = true;
        return 0;
    }
    return 1;
}

std::string UplinkPowerControlDedicatedSCell_r10::deltaMCS_Enabled_r10_ValueToString(deltaMCS_Enabled_r10_Enum value) const
{
    if(k_deltaMCS_Enabled_r10_en0 == value)
        return "en0";
    if(k_deltaMCS_Enabled_r10_en1 == value)
        return "en1";
    return "";
}

uint64_t UplinkPowerControlDedicatedSCell_r10::deltaMCS_Enabled_r10_NumberOfValues() const
{
    return 2;
}

std::string UplinkPowerControlDedicatedSCell_r10::deltaMCS_Enabled_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "deltaMCS_Enabled_r10 = " + deltaMCS_Enabled_r10_ValueToString(deltaMCS_Enabled_r10_internal_value) + "\n";
    return out;
}

std::string UplinkPowerControlDedicatedSCell_r10::deltaMCS_Enabled_r10_ToStringNoNewLines() const
{
    std::string out = "deltaMCS_Enabled_r10=" + deltaMCS_Enabled_r10_ValueToString(deltaMCS_Enabled_r10_internal_value) + ",";
    return out;
}

int UplinkPowerControlDedicatedSCell_r10::deltaMCS_Enabled_r10_Clear()
{
    deltaMCS_Enabled_r10_present = false;
    return 0;
}

bool UplinkPowerControlDedicatedSCell_r10::deltaMCS_Enabled_r10_IsPresent() const
{
    return deltaMCS_Enabled_r10_present;
}

int UplinkPowerControlDedicatedSCell_r10::accumulationEnabled_r10_Pack(std::vector<uint8_t> &bits)
{
    if(!accumulationEnabled_r10_present)
    {
        printf("UplinkPowerControlDedicatedSCell_r10::accumulationEnabled_r10_Pack() presence failure\n");
        return -1;
    }
    bits.push_back(accumulationEnabled_r10_internal_value);
    return 0;
}

int UplinkPowerControlDedicatedSCell_r10::accumulationEnabled_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return accumulationEnabled_r10_Unpack(bits, idx);
}

int UplinkPowerControlDedicatedSCell_r10::accumulationEnabled_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    if((idx + 1) > bits.size())
    {
        printf("UplinkPowerControlDedicatedSCell_r10::accumulationEnabled_r10_Unpack() index out of bounds\n");
        return -1;
    }
    accumulationEnabled_r10_internal_value = bits[idx++];
    accumulationEnabled_r10_present = true;
    return 0;
}

bool UplinkPowerControlDedicatedSCell_r10::accumulationEnabled_r10_Value() const
{
    if(accumulationEnabled_r10_present)
        return accumulationEnabled_r10_internal_value;
    return false;
}

int UplinkPowerControlDedicatedSCell_r10::accumulationEnabled_r10_SetValue(bool value)
{
    accumulationEnabled_r10_internal_value = value;
    accumulationEnabled_r10_present = true;
    return 0;
}

std::string UplinkPowerControlDedicatedSCell_r10::accumulationEnabled_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "accumulationEnabled_r10 = " + std::to_string(accumulationEnabled_r10_internal_value) + "\n";
    return out;
}

std::string UplinkPowerControlDedicatedSCell_r10::accumulationEnabled_r10_ToStringNoNewLines() const
{
    std::string out = "accumulationEnabled_r10=" + std::to_string(accumulationEnabled_r10_internal_value) + ",";
    return out;
}

int UplinkPowerControlDedicatedSCell_r10::accumulationEnabled_r10_Clear()
{
    accumulationEnabled_r10_present = false;
    return 0;
}

bool UplinkPowerControlDedicatedSCell_r10::accumulationEnabled_r10_IsPresent() const
{
    return accumulationEnabled_r10_present;
}

int UplinkPowerControlDedicatedSCell_r10::pSRS_Offset_r10_Pack(std::vector<uint8_t> &bits)
{
    if(!pSRS_Offset_r10_present)
    {
        printf("UplinkPowerControlDedicatedSCell_r10::pSRS_Offset_r10_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = pSRS_Offset_r10_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (15 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int UplinkPowerControlDedicatedSCell_r10::pSRS_Offset_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return pSRS_Offset_r10_Unpack(bits, idx);
}

int UplinkPowerControlDedicatedSCell_r10::pSRS_Offset_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (15 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("UplinkPowerControlDedicatedSCell_r10::pSRS_Offset_r10_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    pSRS_Offset_r10_internal_value = packed_val + 0;
    pSRS_Offset_r10_present = true;
    return 0;
}

int64_t UplinkPowerControlDedicatedSCell_r10::pSRS_Offset_r10_Value() const
{
    if(pSRS_Offset_r10_present)
        return pSRS_Offset_r10_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int UplinkPowerControlDedicatedSCell_r10::pSRS_Offset_r10_SetValue(int64_t value)
{
    if(value < 0 || value > 15)
    {
        printf("UplinkPowerControlDedicatedSCell_r10::pSRS_Offset_r10_SetValue() range failure\n");
        return -1;
    }
    pSRS_Offset_r10_internal_value = value;
    pSRS_Offset_r10_present = true;
    return 0;
}

std::string UplinkPowerControlDedicatedSCell_r10::pSRS_Offset_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "pSRS_Offset_r10 = " + std::to_string(pSRS_Offset_r10_internal_value) + "\n";
    return out;
}

std::string UplinkPowerControlDedicatedSCell_r10::pSRS_Offset_r10_ToStringNoNewLines() const
{
    std::string out = "pSRS_Offset_r10=" + std::to_string(pSRS_Offset_r10_internal_value) + ",";
    return out;
}

int UplinkPowerControlDedicatedSCell_r10::pSRS_Offset_r10_Clear()
{
    pSRS_Offset_r10_present = false;
    return 0;
}

bool UplinkPowerControlDedicatedSCell_r10::pSRS_Offset_r10_IsPresent() const
{
    return pSRS_Offset_r10_present;
}

FilterCoefficient* UplinkPowerControlDedicatedSCell_r10::filterCoefficient_r10_Set()
{
    filterCoefficient_r10_present = true;
    return &filterCoefficient_r10;
}

int UplinkPowerControlDedicatedSCell_r10::filterCoefficient_r10_Set(FilterCoefficient &value)
{
    filterCoefficient_r10_present = true;
    filterCoefficient_r10 = value;
    return 0;
}

const FilterCoefficient& UplinkPowerControlDedicatedSCell_r10::filterCoefficient_r10_Get() const
{
    return filterCoefficient_r10;
}

FilterCoefficient::Enum UplinkPowerControlDedicatedSCell_r10::filterCoefficient_r10_GetDefault() const
{
    return FilterCoefficient::k_fc4;
}

std::string UplinkPowerControlDedicatedSCell_r10::filterCoefficient_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "filterCoefficient_r10:\n";
    out += filterCoefficient_r10.ToString(indent+1);
    return out;
}

std::string UplinkPowerControlDedicatedSCell_r10::filterCoefficient_r10_ToStringNoNewLines() const
{
    std::string out = "filterCoefficient_r10:";
    out += filterCoefficient_r10.ToStringNoNewLines();
    return out;
}

int UplinkPowerControlDedicatedSCell_r10::filterCoefficient_r10_Clear()
{
    filterCoefficient_r10_present = false;
    return 0;
}

bool UplinkPowerControlDedicatedSCell_r10::filterCoefficient_r10_IsPresent() const
{
    return filterCoefficient_r10_present;
}

int UplinkPowerControlDedicatedSCell_r10::pathlossReference_r10_Pack(std::vector<uint8_t> &bits)
{
    if(!pathlossReference_r10_present)
    {
        printf("UplinkPowerControlDedicatedSCell_r10::pathlossReference_r10_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((pathlossReference_r10_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int UplinkPowerControlDedicatedSCell_r10::pathlossReference_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return pathlossReference_r10_Unpack(bits, idx);
}

int UplinkPowerControlDedicatedSCell_r10::pathlossReference_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("UplinkPowerControlDedicatedSCell_r10::pathlossReference_r10_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 1)
    {
        printf("UplinkPowerControlDedicatedSCell_r10::pathlossReference_r10_Unpack() max failure\n");
        return -1;
    }
    pathlossReference_r10_internal_value = (pathlossReference_r10_Enum)packed_val;
    pathlossReference_r10_present = true;
    return 0;
}

UplinkPowerControlDedicatedSCell_r10::pathlossReference_r10_Enum UplinkPowerControlDedicatedSCell_r10::pathlossReference_r10_Value() const
{
    if(pathlossReference_r10_present)
        return pathlossReference_r10_internal_value;
    return (UplinkPowerControlDedicatedSCell_r10::pathlossReference_r10_Enum)0;
}

int UplinkPowerControlDedicatedSCell_r10::pathlossReference_r10_SetValue(pathlossReference_r10_Enum value)
{
    pathlossReference_r10_internal_value = value;
    pathlossReference_r10_present = true;
    return 0;
}

int UplinkPowerControlDedicatedSCell_r10::pathlossReference_r10_SetValue(std::string value)
{
    if("pCell" == value)
    {
        pathlossReference_r10_internal_value = k_pathlossReference_r10_pCell;
        pathlossReference_r10_present = true;
        return 0;
    }
    if("sCell" == value)
    {
        pathlossReference_r10_internal_value = k_pathlossReference_r10_sCell;
        pathlossReference_r10_present = true;
        return 0;
    }
    return 1;
}

std::string UplinkPowerControlDedicatedSCell_r10::pathlossReference_r10_ValueToString(pathlossReference_r10_Enum value) const
{
    if(k_pathlossReference_r10_pCell == value)
        return "pCell";
    if(k_pathlossReference_r10_sCell == value)
        return "sCell";
    return "";
}

uint64_t UplinkPowerControlDedicatedSCell_r10::pathlossReference_r10_NumberOfValues() const
{
    return 2;
}

std::string UplinkPowerControlDedicatedSCell_r10::pathlossReference_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "pathlossReference_r10 = " + pathlossReference_r10_ValueToString(pathlossReference_r10_internal_value) + "\n";
    return out;
}

std::string UplinkPowerControlDedicatedSCell_r10::pathlossReference_r10_ToStringNoNewLines() const
{
    std::string out = "pathlossReference_r10=" + pathlossReference_r10_ValueToString(pathlossReference_r10_internal_value) + ",";
    return out;
}

int UplinkPowerControlDedicatedSCell_r10::pathlossReference_r10_Clear()
{
    pathlossReference_r10_present = false;
    return 0;
}

bool UplinkPowerControlDedicatedSCell_r10::pathlossReference_r10_IsPresent() const
{
    return pathlossReference_r10_present;
}

