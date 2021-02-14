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

#include "CQI_ReportConfig_v10x0.h"

#include <cmath>

int CQI_ReportConfig_v10x0::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(ri_ReportMode_r10_IsPresent());
    bits.push_back(twoAntennaPortActivated_r10_IsPresent());
    bits.push_back(cqi_PUCCH_ResourceIndexP1_r10_IsPresent());

    // Fields
    if(ri_ReportMode_r10_IsPresent())
    {
        if(0 != ri_ReportMode_r10_Pack(bits))
        {
            printf("CQI_ReportConfig_v10x0:: field pack failure\n");
            return -1;
        }
    }
    if(twoAntennaPortActivated_r10_IsPresent())
    {
        if(0 != twoAntennaPortActivated_r10_Pack(bits))
        {
            printf("CQI_ReportConfig_v10x0:: field pack failure\n");
            return -1;
        }
    }
    if(cqi_PUCCH_ResourceIndexP1_r10_IsPresent())
    {
        if(0 != cqi_PUCCH_ResourceIndexP1_r10_Pack(bits))
        {
            printf("CQI_ReportConfig_v10x0:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int CQI_ReportConfig_v10x0::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int CQI_ReportConfig_v10x0::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("CQI_ReportConfig_v10x0::Unpack() index out of bounds for optional indiator ri_ReportMode_r10\n");
        return -1;
    }
    ri_ReportMode_r10_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("CQI_ReportConfig_v10x0::Unpack() index out of bounds for optional indiator twoAntennaPortActivated_r10\n");
        return -1;
    }
    twoAntennaPortActivated_r10_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("CQI_ReportConfig_v10x0::Unpack() index out of bounds for optional indiator cqi_PUCCH_ResourceIndexP1_r10\n");
        return -1;
    }
    cqi_PUCCH_ResourceIndexP1_r10_present = bits[idx++];

    // Fields
    if(ri_ReportMode_r10_present)
    {
        if(0 != ri_ReportMode_r10_Unpack(bits, idx))
        {
            printf("CQI_ReportConfig_v10x0:: field unpack failure\n");
            return -1;
        }
    }
    if(twoAntennaPortActivated_r10_present)
    {
        if(0 != twoAntennaPortActivated_r10_Unpack(bits, idx))
        {
            printf("CQI_ReportConfig_v10x0:: field unpack failure\n");
            return -1;
        }
    }
    if(cqi_PUCCH_ResourceIndexP1_r10_present)
    {
        if(0 != cqi_PUCCH_ResourceIndexP1_r10_Unpack(bits, idx))
        {
            printf("CQI_ReportConfig_v10x0:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string CQI_ReportConfig_v10x0::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "CQI_ReportConfig_v10x0:\n";
    if(ri_ReportMode_r10_IsPresent())
        out += ri_ReportMode_r10_ToString(indent+1);
    if(twoAntennaPortActivated_r10_IsPresent())
        out += twoAntennaPortActivated_r10_ToString(indent+1);
    if(cqi_PUCCH_ResourceIndexP1_r10_IsPresent())
        out += cqi_PUCCH_ResourceIndexP1_r10_ToString(indent+1);
    return out;
}

std::string CQI_ReportConfig_v10x0::ToStringNoNewLines() const
{
    std::string out = "CQI_ReportConfig_v10x0:";
    if(ri_ReportMode_r10_IsPresent())
        out += ri_ReportMode_r10_ToStringNoNewLines();
    if(twoAntennaPortActivated_r10_IsPresent())
        out += twoAntennaPortActivated_r10_ToStringNoNewLines();
    if(cqi_PUCCH_ResourceIndexP1_r10_IsPresent())
        out += cqi_PUCCH_ResourceIndexP1_r10_ToStringNoNewLines();
    return out;
}

int CQI_ReportConfig_v10x0::ri_ReportMode_r10_Pack(std::vector<uint8_t> &bits)
{
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((ri_ReportMode_r10_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int CQI_ReportConfig_v10x0::ri_ReportMode_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return ri_ReportMode_r10_Unpack(bits, idx);
}

int CQI_ReportConfig_v10x0::ri_ReportMode_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("CQI_ReportConfig_v10x0::ri_ReportMode_r10_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 1)
    {
        printf("CQI_ReportConfig_v10x0::ri_ReportMode_r10_Unpack() max failure\n");
        return -1;
    }
    ri_ReportMode_r10_internal_value = (ri_ReportMode_r10_Enum)packed_val;
    ri_ReportMode_r10_present = true;
    return 0;
}

CQI_ReportConfig_v10x0::ri_ReportMode_r10_Enum CQI_ReportConfig_v10x0::ri_ReportMode_r10_Value() const
{
    if(ri_ReportMode_r10_present)
        return ri_ReportMode_r10_internal_value;
    return (CQI_ReportConfig_v10x0::ri_ReportMode_r10_Enum)0;
}

int CQI_ReportConfig_v10x0::ri_ReportMode_r10_SetValue(ri_ReportMode_r10_Enum value)
{
    ri_ReportMode_r10_internal_value = value;
    ri_ReportMode_r10_present = true;
    return 0;
}

int CQI_ReportConfig_v10x0::ri_ReportMode_r10_SetValue(std::string value)
{
    if("riWithW1" == value)
    {
        ri_ReportMode_r10_internal_value = k_ri_ReportMode_r10_riWithW1;
        ri_ReportMode_r10_present = true;
        return 0;
    }
    if("riWithoutW1" == value)
    {
        ri_ReportMode_r10_internal_value = k_ri_ReportMode_r10_riWithoutW1;
        ri_ReportMode_r10_present = true;
        return 0;
    }
    return 1;
}

std::string CQI_ReportConfig_v10x0::ri_ReportMode_r10_ValueToString(ri_ReportMode_r10_Enum value) const
{
    if(k_ri_ReportMode_r10_riWithW1 == value)
        return "riWithW1";
    if(k_ri_ReportMode_r10_riWithoutW1 == value)
        return "riWithoutW1";
    return "";
}

uint64_t CQI_ReportConfig_v10x0::ri_ReportMode_r10_NumberOfValues() const
{
    return 2;
}

std::string CQI_ReportConfig_v10x0::ri_ReportMode_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ri_ReportMode_r10 = " + ri_ReportMode_r10_ValueToString(ri_ReportMode_r10_internal_value) + "\n";
    return out;
}

std::string CQI_ReportConfig_v10x0::ri_ReportMode_r10_ToStringNoNewLines() const
{
    std::string out = "ri_ReportMode_r10=" + ri_ReportMode_r10_ValueToString(ri_ReportMode_r10_internal_value) + ",";
    return out;
}

int CQI_ReportConfig_v10x0::ri_ReportMode_r10_Clear()
{
    ri_ReportMode_r10_present = false;
    return 0;
}

bool CQI_ReportConfig_v10x0::ri_ReportMode_r10_IsPresent() const
{
    return ri_ReportMode_r10_present;
}

int CQI_ReportConfig_v10x0::twoAntennaPortActivated_r10_Pack(std::vector<uint8_t> &bits)
{
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((twoAntennaPortActivated_r10_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int CQI_ReportConfig_v10x0::twoAntennaPortActivated_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return twoAntennaPortActivated_r10_Unpack(bits, idx);
}

int CQI_ReportConfig_v10x0::twoAntennaPortActivated_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("CQI_ReportConfig_v10x0::twoAntennaPortActivated_r10_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 0)
    {
        printf("CQI_ReportConfig_v10x0::twoAntennaPortActivated_r10_Unpack() max failure\n");
        return -1;
    }
    twoAntennaPortActivated_r10_internal_value = (twoAntennaPortActivated_r10_Enum)packed_val;
    twoAntennaPortActivated_r10_present = true;
    return 0;
}

CQI_ReportConfig_v10x0::twoAntennaPortActivated_r10_Enum CQI_ReportConfig_v10x0::twoAntennaPortActivated_r10_Value() const
{
    if(twoAntennaPortActivated_r10_present)
        return twoAntennaPortActivated_r10_internal_value;
    return (CQI_ReportConfig_v10x0::twoAntennaPortActivated_r10_Enum)0;
}

int CQI_ReportConfig_v10x0::twoAntennaPortActivated_r10_SetValue(twoAntennaPortActivated_r10_Enum value)
{
    twoAntennaPortActivated_r10_internal_value = value;
    twoAntennaPortActivated_r10_present = true;
    return 0;
}

int CQI_ReportConfig_v10x0::twoAntennaPortActivated_r10_SetValue(std::string value)
{
    if("true" == value)
    {
        twoAntennaPortActivated_r10_internal_value = k_twoAntennaPortActivated_r10_true;
        twoAntennaPortActivated_r10_present = true;
        return 0;
    }
    return 1;
}

std::string CQI_ReportConfig_v10x0::twoAntennaPortActivated_r10_ValueToString(twoAntennaPortActivated_r10_Enum value) const
{
    if(k_twoAntennaPortActivated_r10_true == value)
        return "true";
    return "";
}

uint64_t CQI_ReportConfig_v10x0::twoAntennaPortActivated_r10_NumberOfValues() const
{
    return 1;
}

std::string CQI_ReportConfig_v10x0::twoAntennaPortActivated_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "twoAntennaPortActivated_r10 = " + twoAntennaPortActivated_r10_ValueToString(twoAntennaPortActivated_r10_internal_value) + "\n";
    return out;
}

std::string CQI_ReportConfig_v10x0::twoAntennaPortActivated_r10_ToStringNoNewLines() const
{
    std::string out = "twoAntennaPortActivated_r10=" + twoAntennaPortActivated_r10_ValueToString(twoAntennaPortActivated_r10_internal_value) + ",";
    return out;
}

int CQI_ReportConfig_v10x0::twoAntennaPortActivated_r10_Clear()
{
    twoAntennaPortActivated_r10_present = false;
    return 0;
}

bool CQI_ReportConfig_v10x0::twoAntennaPortActivated_r10_IsPresent() const
{
    return twoAntennaPortActivated_r10_present;
}

int CQI_ReportConfig_v10x0::cqi_PUCCH_ResourceIndexP1_r10_Pack(std::vector<uint8_t> &bits)
{
    int64_t val_to_pack = cqi_PUCCH_ResourceIndexP1_r10_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (1185 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int CQI_ReportConfig_v10x0::cqi_PUCCH_ResourceIndexP1_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return cqi_PUCCH_ResourceIndexP1_r10_Unpack(bits, idx);
}

int CQI_ReportConfig_v10x0::cqi_PUCCH_ResourceIndexP1_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (1185 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("CQI_ReportConfig_v10x0::cqi_PUCCH_ResourceIndexP1_r10_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    cqi_PUCCH_ResourceIndexP1_r10_internal_value = packed_val + 0;
    cqi_PUCCH_ResourceIndexP1_r10_present = true;
    return 0;
}

int64_t CQI_ReportConfig_v10x0::cqi_PUCCH_ResourceIndexP1_r10_Value() const
{
    if(cqi_PUCCH_ResourceIndexP1_r10_present)
        return cqi_PUCCH_ResourceIndexP1_r10_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int CQI_ReportConfig_v10x0::cqi_PUCCH_ResourceIndexP1_r10_SetValue(int64_t value)
{
    if(value < 0 || value > 1185)
    {
        printf("CQI_ReportConfig_v10x0::cqi_PUCCH_ResourceIndexP1_r10_SetValue() range failure\n");
        return -1;
    }
    cqi_PUCCH_ResourceIndexP1_r10_internal_value = value;
    cqi_PUCCH_ResourceIndexP1_r10_present = true;
    return 0;
}

std::string CQI_ReportConfig_v10x0::cqi_PUCCH_ResourceIndexP1_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cqi_PUCCH_ResourceIndexP1_r10 = " + std::to_string(cqi_PUCCH_ResourceIndexP1_r10_internal_value) + "\n";
    return out;
}

std::string CQI_ReportConfig_v10x0::cqi_PUCCH_ResourceIndexP1_r10_ToStringNoNewLines() const
{
    std::string out = "cqi_PUCCH_ResourceIndexP1_r10=" + std::to_string(cqi_PUCCH_ResourceIndexP1_r10_internal_value) + ",";
    return out;
}

int CQI_ReportConfig_v10x0::cqi_PUCCH_ResourceIndexP1_r10_Clear()
{
    cqi_PUCCH_ResourceIndexP1_r10_present = false;
    return 0;
}

bool CQI_ReportConfig_v10x0::cqi_PUCCH_ResourceIndexP1_r10_IsPresent() const
{
    return cqi_PUCCH_ResourceIndexP1_r10_present;
}

