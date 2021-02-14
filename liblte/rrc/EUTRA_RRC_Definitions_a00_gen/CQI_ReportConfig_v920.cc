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

#include "CQI_ReportConfig_v920.h"

#include <cmath>

int CQI_ReportConfig_v920::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(cqi_Mask_r9_IsPresent());
    bits.push_back(pmi_RI_Report_r9_IsPresent());

    // Fields
    if(cqi_Mask_r9_IsPresent())
    {
        if(0 != cqi_Mask_r9_Pack(bits))
        {
            printf("CQI_ReportConfig_v920:: field pack failure\n");
            return -1;
        }
    }
    if(pmi_RI_Report_r9_IsPresent())
    {
        if(0 != pmi_RI_Report_r9_Pack(bits))
        {
            printf("CQI_ReportConfig_v920:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int CQI_ReportConfig_v920::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int CQI_ReportConfig_v920::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("CQI_ReportConfig_v920::Unpack() index out of bounds for optional indiator cqi_Mask_r9\n");
        return -1;
    }
    cqi_Mask_r9_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("CQI_ReportConfig_v920::Unpack() index out of bounds for optional indiator pmi_RI_Report_r9\n");
        return -1;
    }
    pmi_RI_Report_r9_present = bits[idx++];

    // Fields
    if(cqi_Mask_r9_present)
    {
        if(0 != cqi_Mask_r9_Unpack(bits, idx))
        {
            printf("CQI_ReportConfig_v920:: field unpack failure\n");
            return -1;
        }
    }
    if(pmi_RI_Report_r9_present)
    {
        if(0 != pmi_RI_Report_r9_Unpack(bits, idx))
        {
            printf("CQI_ReportConfig_v920:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string CQI_ReportConfig_v920::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "CQI_ReportConfig_v920:\n";
    if(cqi_Mask_r9_IsPresent())
        out += cqi_Mask_r9_ToString(indent+1);
    if(pmi_RI_Report_r9_IsPresent())
        out += pmi_RI_Report_r9_ToString(indent+1);
    return out;
}

std::string CQI_ReportConfig_v920::ToStringNoNewLines() const
{
    std::string out = "CQI_ReportConfig_v920:";
    if(cqi_Mask_r9_IsPresent())
        out += cqi_Mask_r9_ToStringNoNewLines();
    if(pmi_RI_Report_r9_IsPresent())
        out += pmi_RI_Report_r9_ToStringNoNewLines();
    return out;
}

int CQI_ReportConfig_v920::cqi_Mask_r9_Pack(std::vector<uint8_t> &bits)
{
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((cqi_Mask_r9_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int CQI_ReportConfig_v920::cqi_Mask_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return cqi_Mask_r9_Unpack(bits, idx);
}

int CQI_ReportConfig_v920::cqi_Mask_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("CQI_ReportConfig_v920::cqi_Mask_r9_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 0)
    {
        printf("CQI_ReportConfig_v920::cqi_Mask_r9_Unpack() max failure\n");
        return -1;
    }
    cqi_Mask_r9_internal_value = (cqi_Mask_r9_Enum)packed_val;
    cqi_Mask_r9_present = true;
    return 0;
}

CQI_ReportConfig_v920::cqi_Mask_r9_Enum CQI_ReportConfig_v920::cqi_Mask_r9_Value() const
{
    if(cqi_Mask_r9_present)
        return cqi_Mask_r9_internal_value;
    return (CQI_ReportConfig_v920::cqi_Mask_r9_Enum)0;
}

int CQI_ReportConfig_v920::cqi_Mask_r9_SetValue(cqi_Mask_r9_Enum value)
{
    cqi_Mask_r9_internal_value = value;
    cqi_Mask_r9_present = true;
    return 0;
}

int CQI_ReportConfig_v920::cqi_Mask_r9_SetValue(std::string value)
{
    if("setup" == value)
    {
        cqi_Mask_r9_internal_value = k_cqi_Mask_r9_setup;
        cqi_Mask_r9_present = true;
        return 0;
    }
    return 1;
}

std::string CQI_ReportConfig_v920::cqi_Mask_r9_ValueToString(cqi_Mask_r9_Enum value) const
{
    if(k_cqi_Mask_r9_setup == value)
        return "setup";
    return "";
}

uint64_t CQI_ReportConfig_v920::cqi_Mask_r9_NumberOfValues() const
{
    return 1;
}

std::string CQI_ReportConfig_v920::cqi_Mask_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cqi_Mask_r9 = " + cqi_Mask_r9_ValueToString(cqi_Mask_r9_internal_value) + "\n";
    return out;
}

std::string CQI_ReportConfig_v920::cqi_Mask_r9_ToStringNoNewLines() const
{
    std::string out = "cqi_Mask_r9=" + cqi_Mask_r9_ValueToString(cqi_Mask_r9_internal_value) + ",";
    return out;
}

int CQI_ReportConfig_v920::cqi_Mask_r9_Clear()
{
    cqi_Mask_r9_present = false;
    return 0;
}

bool CQI_ReportConfig_v920::cqi_Mask_r9_IsPresent() const
{
    return cqi_Mask_r9_present;
}

int CQI_ReportConfig_v920::pmi_RI_Report_r9_Pack(std::vector<uint8_t> &bits)
{
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((pmi_RI_Report_r9_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int CQI_ReportConfig_v920::pmi_RI_Report_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return pmi_RI_Report_r9_Unpack(bits, idx);
}

int CQI_ReportConfig_v920::pmi_RI_Report_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("CQI_ReportConfig_v920::pmi_RI_Report_r9_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 0)
    {
        printf("CQI_ReportConfig_v920::pmi_RI_Report_r9_Unpack() max failure\n");
        return -1;
    }
    pmi_RI_Report_r9_internal_value = (pmi_RI_Report_r9_Enum)packed_val;
    pmi_RI_Report_r9_present = true;
    return 0;
}

CQI_ReportConfig_v920::pmi_RI_Report_r9_Enum CQI_ReportConfig_v920::pmi_RI_Report_r9_Value() const
{
    if(pmi_RI_Report_r9_present)
        return pmi_RI_Report_r9_internal_value;
    return (CQI_ReportConfig_v920::pmi_RI_Report_r9_Enum)0;
}

int CQI_ReportConfig_v920::pmi_RI_Report_r9_SetValue(pmi_RI_Report_r9_Enum value)
{
    pmi_RI_Report_r9_internal_value = value;
    pmi_RI_Report_r9_present = true;
    return 0;
}

int CQI_ReportConfig_v920::pmi_RI_Report_r9_SetValue(std::string value)
{
    if("setup" == value)
    {
        pmi_RI_Report_r9_internal_value = k_pmi_RI_Report_r9_setup;
        pmi_RI_Report_r9_present = true;
        return 0;
    }
    return 1;
}

std::string CQI_ReportConfig_v920::pmi_RI_Report_r9_ValueToString(pmi_RI_Report_r9_Enum value) const
{
    if(k_pmi_RI_Report_r9_setup == value)
        return "setup";
    return "";
}

uint64_t CQI_ReportConfig_v920::pmi_RI_Report_r9_NumberOfValues() const
{
    return 1;
}

std::string CQI_ReportConfig_v920::pmi_RI_Report_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "pmi_RI_Report_r9 = " + pmi_RI_Report_r9_ValueToString(pmi_RI_Report_r9_internal_value) + "\n";
    return out;
}

std::string CQI_ReportConfig_v920::pmi_RI_Report_r9_ToStringNoNewLines() const
{
    std::string out = "pmi_RI_Report_r9=" + pmi_RI_Report_r9_ValueToString(pmi_RI_Report_r9_internal_value) + ",";
    return out;
}

int CQI_ReportConfig_v920::pmi_RI_Report_r9_Clear()
{
    pmi_RI_Report_r9_present = false;
    return 0;
}

bool CQI_ReportConfig_v920::pmi_RI_Report_r9_IsPresent() const
{
    return pmi_RI_Report_r9_present;
}

