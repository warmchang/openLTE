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

#include "CQI_ReportConfig.h"

#include <cmath>

int CQI_ReportConfig::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(cqi_ReportModeAperiodic_IsPresent());
    bits.push_back(cqi_ReportPeriodic_IsPresent());

    // Fields
    if(cqi_ReportModeAperiodic_IsPresent())
    {
        if(0 != cqi_ReportModeAperiodic_Pack(bits))
        {
            printf("CQI_ReportConfig:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != nomPDSCH_RS_EPRE_Offset_Pack(bits))
        {
            printf("CQI_ReportConfig:: field pack failure\n");
            return -1;
        }
    }
    if(cqi_ReportPeriodic_IsPresent())
    {
        if(0 != cqi_ReportPeriodic.Pack(bits))
        {
            printf("CQI_ReportConfig:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int CQI_ReportConfig::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int CQI_ReportConfig::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("CQI_ReportConfig::Unpack() index out of bounds for optional indiator cqi_ReportModeAperiodic\n");
        return -1;
    }
    cqi_ReportModeAperiodic_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("CQI_ReportConfig::Unpack() index out of bounds for optional indiator cqi_ReportPeriodic\n");
        return -1;
    }
    cqi_ReportPeriodic_present = bits[idx++];

    // Fields
    if(cqi_ReportModeAperiodic_present)
    {
        if(0 != cqi_ReportModeAperiodic_Unpack(bits, idx))
        {
            printf("CQI_ReportConfig:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != nomPDSCH_RS_EPRE_Offset_Unpack(bits, idx))
        {
            printf("CQI_ReportConfig:: field unpack failure\n");
            return -1;
        }
    }
    if(cqi_ReportPeriodic_present)
    {
        if(0 != cqi_ReportPeriodic.Unpack(bits, idx))
        {
            printf("CQI_ReportConfig:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string CQI_ReportConfig::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "CQI_ReportConfig:\n";
    if(cqi_ReportModeAperiodic_IsPresent())
        out += cqi_ReportModeAperiodic_ToString(indent+1);
    out += nomPDSCH_RS_EPRE_Offset_ToString(indent+1);
    if(cqi_ReportPeriodic_IsPresent())
        out += cqi_ReportPeriodic_ToString(indent+1);
    return out;
}

std::string CQI_ReportConfig::ToStringNoNewLines() const
{
    std::string out = "CQI_ReportConfig:";
    if(cqi_ReportModeAperiodic_IsPresent())
        out += cqi_ReportModeAperiodic_ToStringNoNewLines();
    out += nomPDSCH_RS_EPRE_Offset_ToStringNoNewLines();
    if(cqi_ReportPeriodic_IsPresent())
        out += cqi_ReportPeriodic_ToStringNoNewLines();
    return out;
}

int CQI_ReportConfig::cqi_ReportModeAperiodic_Pack(std::vector<uint8_t> &bits)
{
    uint32_t N_bits = 3;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((cqi_ReportModeAperiodic_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int CQI_ReportConfig::cqi_ReportModeAperiodic_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return cqi_ReportModeAperiodic_Unpack(bits, idx);
}

int CQI_ReportConfig::cqi_ReportModeAperiodic_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 3;
    if((idx + N_bits) > bits.size())
    {
        printf("CQI_ReportConfig::cqi_ReportModeAperiodic_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 7)
    {
        printf("CQI_ReportConfig::cqi_ReportModeAperiodic_Unpack() max failure\n");
        return -1;
    }
    cqi_ReportModeAperiodic_internal_value = (cqi_ReportModeAperiodic_Enum)packed_val;
    cqi_ReportModeAperiodic_present = true;
    return 0;
}

CQI_ReportConfig::cqi_ReportModeAperiodic_Enum CQI_ReportConfig::cqi_ReportModeAperiodic_Value() const
{
    if(cqi_ReportModeAperiodic_present)
        return cqi_ReportModeAperiodic_internal_value;
    return (CQI_ReportConfig::cqi_ReportModeAperiodic_Enum)0;
}

int CQI_ReportConfig::cqi_ReportModeAperiodic_SetValue(cqi_ReportModeAperiodic_Enum value)
{
    cqi_ReportModeAperiodic_internal_value = value;
    cqi_ReportModeAperiodic_present = true;
    return 0;
}

int CQI_ReportConfig::cqi_ReportModeAperiodic_SetValue(std::string value)
{
    if("rm12" == value)
    {
        cqi_ReportModeAperiodic_internal_value = k_cqi_ReportModeAperiodic_rm12;
        cqi_ReportModeAperiodic_present = true;
        return 0;
    }
    if("rm20" == value)
    {
        cqi_ReportModeAperiodic_internal_value = k_cqi_ReportModeAperiodic_rm20;
        cqi_ReportModeAperiodic_present = true;
        return 0;
    }
    if("rm22" == value)
    {
        cqi_ReportModeAperiodic_internal_value = k_cqi_ReportModeAperiodic_rm22;
        cqi_ReportModeAperiodic_present = true;
        return 0;
    }
    if("rm30" == value)
    {
        cqi_ReportModeAperiodic_internal_value = k_cqi_ReportModeAperiodic_rm30;
        cqi_ReportModeAperiodic_present = true;
        return 0;
    }
    if("rm31" == value)
    {
        cqi_ReportModeAperiodic_internal_value = k_cqi_ReportModeAperiodic_rm31;
        cqi_ReportModeAperiodic_present = true;
        return 0;
    }
    if("spare3" == value)
    {
        cqi_ReportModeAperiodic_internal_value = k_cqi_ReportModeAperiodic_spare3;
        cqi_ReportModeAperiodic_present = true;
        return 0;
    }
    if("spare2" == value)
    {
        cqi_ReportModeAperiodic_internal_value = k_cqi_ReportModeAperiodic_spare2;
        cqi_ReportModeAperiodic_present = true;
        return 0;
    }
    if("spare1" == value)
    {
        cqi_ReportModeAperiodic_internal_value = k_cqi_ReportModeAperiodic_spare1;
        cqi_ReportModeAperiodic_present = true;
        return 0;
    }
    return 1;
}

std::string CQI_ReportConfig::cqi_ReportModeAperiodic_ValueToString(cqi_ReportModeAperiodic_Enum value) const
{
    if(k_cqi_ReportModeAperiodic_rm12 == value)
        return "rm12";
    if(k_cqi_ReportModeAperiodic_rm20 == value)
        return "rm20";
    if(k_cqi_ReportModeAperiodic_rm22 == value)
        return "rm22";
    if(k_cqi_ReportModeAperiodic_rm30 == value)
        return "rm30";
    if(k_cqi_ReportModeAperiodic_rm31 == value)
        return "rm31";
    if(k_cqi_ReportModeAperiodic_spare3 == value)
        return "spare3";
    if(k_cqi_ReportModeAperiodic_spare2 == value)
        return "spare2";
    if(k_cqi_ReportModeAperiodic_spare1 == value)
        return "spare1";
    return "";
}

uint64_t CQI_ReportConfig::cqi_ReportModeAperiodic_NumberOfValues() const
{
    return 8;
}

std::string CQI_ReportConfig::cqi_ReportModeAperiodic_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cqi_ReportModeAperiodic = " + cqi_ReportModeAperiodic_ValueToString(cqi_ReportModeAperiodic_internal_value) + "\n";
    return out;
}

std::string CQI_ReportConfig::cqi_ReportModeAperiodic_ToStringNoNewLines() const
{
    std::string out = "cqi_ReportModeAperiodic=" + cqi_ReportModeAperiodic_ValueToString(cqi_ReportModeAperiodic_internal_value) + ",";
    return out;
}

int CQI_ReportConfig::cqi_ReportModeAperiodic_Clear()
{
    cqi_ReportModeAperiodic_present = false;
    return 0;
}

bool CQI_ReportConfig::cqi_ReportModeAperiodic_IsPresent() const
{
    return cqi_ReportModeAperiodic_present;
}

int CQI_ReportConfig::nomPDSCH_RS_EPRE_Offset_Pack(std::vector<uint8_t> &bits)
{
    if(!nomPDSCH_RS_EPRE_Offset_present)
    {
        printf("CQI_ReportConfig::nomPDSCH_RS_EPRE_Offset_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = nomPDSCH_RS_EPRE_Offset_internal_value - (-1);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (6 - -1))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int CQI_ReportConfig::nomPDSCH_RS_EPRE_Offset_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return nomPDSCH_RS_EPRE_Offset_Unpack(bits, idx);
}

int CQI_ReportConfig::nomPDSCH_RS_EPRE_Offset_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (6 - -1))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("CQI_ReportConfig::nomPDSCH_RS_EPRE_Offset_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    nomPDSCH_RS_EPRE_Offset_internal_value = packed_val + -1;
    nomPDSCH_RS_EPRE_Offset_present = true;
    return 0;
}

int64_t CQI_ReportConfig::nomPDSCH_RS_EPRE_Offset_Value() const
{
    if(nomPDSCH_RS_EPRE_Offset_present)
        return nomPDSCH_RS_EPRE_Offset_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int CQI_ReportConfig::nomPDSCH_RS_EPRE_Offset_SetValue(int64_t value)
{
    if(value < -1 || value > 6)
    {
        printf("CQI_ReportConfig::nomPDSCH_RS_EPRE_Offset_SetValue() range failure\n");
        return -1;
    }
    nomPDSCH_RS_EPRE_Offset_internal_value = value;
    nomPDSCH_RS_EPRE_Offset_present = true;
    return 0;
}

std::string CQI_ReportConfig::nomPDSCH_RS_EPRE_Offset_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "nomPDSCH_RS_EPRE_Offset = " + std::to_string(nomPDSCH_RS_EPRE_Offset_internal_value) + "\n";
    return out;
}

std::string CQI_ReportConfig::nomPDSCH_RS_EPRE_Offset_ToStringNoNewLines() const
{
    std::string out = "nomPDSCH_RS_EPRE_Offset=" + std::to_string(nomPDSCH_RS_EPRE_Offset_internal_value) + ",";
    return out;
}

int CQI_ReportConfig::nomPDSCH_RS_EPRE_Offset_Clear()
{
    nomPDSCH_RS_EPRE_Offset_present = false;
    return 0;
}

bool CQI_ReportConfig::nomPDSCH_RS_EPRE_Offset_IsPresent() const
{
    return nomPDSCH_RS_EPRE_Offset_present;
}

CQI_ReportPeriodic* CQI_ReportConfig::cqi_ReportPeriodic_Set()
{
    cqi_ReportPeriodic_present = true;
    return &cqi_ReportPeriodic;
}

int CQI_ReportConfig::cqi_ReportPeriodic_Set(CQI_ReportPeriodic &value)
{
    cqi_ReportPeriodic_present = true;
    cqi_ReportPeriodic = value;
    return 0;
}

const CQI_ReportPeriodic& CQI_ReportConfig::cqi_ReportPeriodic_Get() const
{
    return cqi_ReportPeriodic;
}

std::string CQI_ReportConfig::cqi_ReportPeriodic_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cqi_ReportPeriodic:\n";
    out += cqi_ReportPeriodic.ToString(indent+1);
    return out;
}

std::string CQI_ReportConfig::cqi_ReportPeriodic_ToStringNoNewLines() const
{
    std::string out = "cqi_ReportPeriodic:";
    out += cqi_ReportPeriodic.ToStringNoNewLines();
    return out;
}

int CQI_ReportConfig::cqi_ReportPeriodic_Clear()
{
    cqi_ReportPeriodic_present = false;
    return 0;
}

bool CQI_ReportConfig::cqi_ReportPeriodic_IsPresent() const
{
    return cqi_ReportPeriodic_present;
}

