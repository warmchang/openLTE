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

#include "CQI_ReportPeriodic.h"

#include <cmath>

int CQI_ReportPeriodic::Pack(std::vector<uint8_t> &bits)
{
    if(!present)
    {
        printf("CQI_ReportPeriodic::Pack() presence failure\n");
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
            printf("CQI_ReportPeriodic::release pack failure\n");
            return -1;
        }
    }
    if(internal_choice == k_setup)
    {
        if(0 != setup_value.Pack(bits))
        {
            printf("CQI_ReportPeriodic::setup pack failure\n");
            return -1;
        }
    }
    return 0;
}

int CQI_ReportPeriodic::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int CQI_ReportPeriodic::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 1) > bits.size())
    {
        printf("CQI_ReportPeriodic::Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<1; i++)
        packed_val |= bits[idx++] << (1-i-1);

    if((CQI_ReportPeriodic::Enum)packed_val > k_setup)
    {
        printf("CQI_ReportPeriodic::Unpack() choice range failure\n");
        return -1;
    }
    internal_choice = (CQI_ReportPeriodic::Enum)packed_val;
    present = true;

    // Fields
    if(internal_choice == k_release)
    {
        if(0 != release_Unpack(bits, idx))
        {
            printf("CQI_ReportPeriodic::release unpack failure\n");
            return -1;
        }
    }
    if(internal_choice == k_setup)
    {
        if(0 != setup_value.Unpack(bits, idx))
        {
            printf("CQI_ReportPeriodic::setup unpack failure\n");
            return -1;
        }
    }
    return 0;
}

CQI_ReportPeriodic::Enum CQI_ReportPeriodic::Choice() const
{
    if(present)
        return internal_choice;
    return (CQI_ReportPeriodic::Enum)0;
}

int CQI_ReportPeriodic::SetChoice(CQI_ReportPeriodic::Enum choice)
{
    internal_choice = choice;
    present = true;
    return 0;
}

std::string CQI_ReportPeriodic::ChoiceToString(Enum value) const
{
    if(k_release == value)
        return "release";
    if(k_setup == value)
        return "setup";
    return "";
}

uint64_t CQI_ReportPeriodic::NumberOfChoices() const
{
    return 2;
}

std::string CQI_ReportPeriodic::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "CQI_ReportPeriodic = " + ChoiceToString(internal_choice) + ":\n";
    if(internal_choice == k_setup)
        out += setup_value.ToString(indent+1);
    return out;
}

std::string CQI_ReportPeriodic::ToStringNoNewLines() const
{
    std::string out = "CQI_ReportPeriodic=" + ChoiceToString(internal_choice) + ",";
    if(internal_choice == k_setup)
        out += setup_value.ToStringNoNewLines();
    return out;
}

int CQI_ReportPeriodic::Clear()
{
    present = false;
    return 0;
}

bool CQI_ReportPeriodic::IsPresent() const
{
    return present;
}

int CQI_ReportPeriodic::setup::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(ri_ConfigIndex_IsPresent());

    // Fields
    {
        if(0 != cqi_PUCCH_ResourceIndex_Pack(bits))
        {
            printf("CQI_ReportPeriodic::setup:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != cqi_pmi_ConfigIndex_Pack(bits))
        {
            printf("CQI_ReportPeriodic::setup:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != cqi_FormatIndicatorPeriodic_Pack(bits))
        {
            printf("CQI_ReportPeriodic::setup:: field pack failure\n");
            return -1;
        }
    }
    if(ri_ConfigIndex_IsPresent())
    {
        if(0 != ri_ConfigIndex_Pack(bits))
        {
            printf("CQI_ReportPeriodic::setup:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != simultaneousAckNackAndCQI_Pack(bits))
        {
            printf("CQI_ReportPeriodic::setup:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int CQI_ReportPeriodic::setup::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int CQI_ReportPeriodic::setup::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("setup::Unpack() index out of bounds for optional indiator ri_ConfigIndex\n");
        return -1;
    }
    ri_ConfigIndex_present = bits[idx++];

    // Fields
    {
        if(0 != cqi_PUCCH_ResourceIndex_Unpack(bits, idx))
        {
            printf("CQI_ReportPeriodic::setup:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != cqi_pmi_ConfigIndex_Unpack(bits, idx))
        {
            printf("CQI_ReportPeriodic::setup:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != cqi_FormatIndicatorPeriodic_Unpack(bits, idx))
        {
            printf("CQI_ReportPeriodic::setup:: field unpack failure\n");
            return -1;
        }
    }
    if(ri_ConfigIndex_present)
    {
        if(0 != ri_ConfigIndex_Unpack(bits, idx))
        {
            printf("CQI_ReportPeriodic::setup:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != simultaneousAckNackAndCQI_Unpack(bits, idx))
        {
            printf("CQI_ReportPeriodic::setup:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string CQI_ReportPeriodic::setup::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "setup:\n";
    out += cqi_PUCCH_ResourceIndex_ToString(indent+1);
    out += cqi_pmi_ConfigIndex_ToString(indent+1);
    out += cqi_FormatIndicatorPeriodic_ToString(indent+1);
    if(ri_ConfigIndex_IsPresent())
        out += ri_ConfigIndex_ToString(indent+1);
    out += simultaneousAckNackAndCQI_ToString(indent+1);
    return out;
}

std::string CQI_ReportPeriodic::setup::ToStringNoNewLines() const
{
    std::string out = "setup:";
    out += cqi_PUCCH_ResourceIndex_ToStringNoNewLines();
    out += cqi_pmi_ConfigIndex_ToStringNoNewLines();
    out += cqi_FormatIndicatorPeriodic_ToStringNoNewLines();
    if(ri_ConfigIndex_IsPresent())
        out += ri_ConfigIndex_ToStringNoNewLines();
    out += simultaneousAckNackAndCQI_ToStringNoNewLines();
    return out;
}

int CQI_ReportPeriodic::setup::cqi_PUCCH_ResourceIndex_Pack(std::vector<uint8_t> &bits)
{
    if(!cqi_PUCCH_ResourceIndex_present)
    {
        printf("CQI_ReportPeriodic::setup::cqi_PUCCH_ResourceIndex_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = cqi_PUCCH_ResourceIndex_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (1185 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int CQI_ReportPeriodic::setup::cqi_PUCCH_ResourceIndex_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return cqi_PUCCH_ResourceIndex_Unpack(bits, idx);
}

int CQI_ReportPeriodic::setup::cqi_PUCCH_ResourceIndex_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (1185 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("CQI_ReportPeriodic::setup::cqi_PUCCH_ResourceIndex_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    cqi_PUCCH_ResourceIndex_internal_value = packed_val + 0;
    cqi_PUCCH_ResourceIndex_present = true;
    return 0;
}

int64_t CQI_ReportPeriodic::setup::cqi_PUCCH_ResourceIndex_Value() const
{
    if(cqi_PUCCH_ResourceIndex_present)
        return cqi_PUCCH_ResourceIndex_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int CQI_ReportPeriodic::setup::cqi_PUCCH_ResourceIndex_SetValue(int64_t value)
{
    if(value < 0 || value > 1185)
    {
        printf("CQI_ReportPeriodic::setup::cqi_PUCCH_ResourceIndex_SetValue() range failure\n");
        return -1;
    }
    cqi_PUCCH_ResourceIndex_internal_value = value;
    cqi_PUCCH_ResourceIndex_present = true;
    return 0;
}

std::string CQI_ReportPeriodic::setup::cqi_PUCCH_ResourceIndex_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cqi_PUCCH_ResourceIndex = " + std::to_string(cqi_PUCCH_ResourceIndex_internal_value) + "\n";
    return out;
}

std::string CQI_ReportPeriodic::setup::cqi_PUCCH_ResourceIndex_ToStringNoNewLines() const
{
    std::string out = "cqi_PUCCH_ResourceIndex=" + std::to_string(cqi_PUCCH_ResourceIndex_internal_value) + ",";
    return out;
}

int CQI_ReportPeriodic::setup::cqi_PUCCH_ResourceIndex_Clear()
{
    cqi_PUCCH_ResourceIndex_present = false;
    return 0;
}

bool CQI_ReportPeriodic::setup::cqi_PUCCH_ResourceIndex_IsPresent() const
{
    return cqi_PUCCH_ResourceIndex_present;
}

int CQI_ReportPeriodic::setup::cqi_pmi_ConfigIndex_Pack(std::vector<uint8_t> &bits)
{
    if(!cqi_pmi_ConfigIndex_present)
    {
        printf("CQI_ReportPeriodic::setup::cqi_pmi_ConfigIndex_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = cqi_pmi_ConfigIndex_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (1023 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int CQI_ReportPeriodic::setup::cqi_pmi_ConfigIndex_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return cqi_pmi_ConfigIndex_Unpack(bits, idx);
}

int CQI_ReportPeriodic::setup::cqi_pmi_ConfigIndex_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (1023 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("CQI_ReportPeriodic::setup::cqi_pmi_ConfigIndex_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    cqi_pmi_ConfigIndex_internal_value = packed_val + 0;
    cqi_pmi_ConfigIndex_present = true;
    return 0;
}

int64_t CQI_ReportPeriodic::setup::cqi_pmi_ConfigIndex_Value() const
{
    if(cqi_pmi_ConfigIndex_present)
        return cqi_pmi_ConfigIndex_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int CQI_ReportPeriodic::setup::cqi_pmi_ConfigIndex_SetValue(int64_t value)
{
    if(value < 0 || value > 1023)
    {
        printf("CQI_ReportPeriodic::setup::cqi_pmi_ConfigIndex_SetValue() range failure\n");
        return -1;
    }
    cqi_pmi_ConfigIndex_internal_value = value;
    cqi_pmi_ConfigIndex_present = true;
    return 0;
}

std::string CQI_ReportPeriodic::setup::cqi_pmi_ConfigIndex_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cqi_pmi_ConfigIndex = " + std::to_string(cqi_pmi_ConfigIndex_internal_value) + "\n";
    return out;
}

std::string CQI_ReportPeriodic::setup::cqi_pmi_ConfigIndex_ToStringNoNewLines() const
{
    std::string out = "cqi_pmi_ConfigIndex=" + std::to_string(cqi_pmi_ConfigIndex_internal_value) + ",";
    return out;
}

int CQI_ReportPeriodic::setup::cqi_pmi_ConfigIndex_Clear()
{
    cqi_pmi_ConfigIndex_present = false;
    return 0;
}

bool CQI_ReportPeriodic::setup::cqi_pmi_ConfigIndex_IsPresent() const
{
    return cqi_pmi_ConfigIndex_present;
}

int CQI_ReportPeriodic::setup::cqi_FormatIndicatorPeriodic_Pack(std::vector<uint8_t> &bits)
{
    if(!cqi_FormatIndicatorPeriodic_present)
    {
        printf("CQI_ReportPeriodic::setup::cqi_FormatIndicatorPeriodic_Pack() presence failure\n");
        return -1;
    }
    // Extension indicator

    // Choice
    for(uint32_t i=0; i<1; i++)
        bits.push_back((cqi_FormatIndicatorPeriodic_internal_choice >> (1-i-1)) & 1);

    // Fields
    if(cqi_FormatIndicatorPeriodic_internal_choice == k_cqi_FormatIndicatorPeriodic_widebandCQI)
    {
        if(0 != cqi_FormatIndicatorPeriodic_widebandCQI_Pack(bits))
        {
            printf("CQI_ReportPeriodic::setup::cqi_FormatIndicatorPeriodic_widebandCQI pack failure\n");
            return -1;
        }
    }
    if(cqi_FormatIndicatorPeriodic_internal_choice == k_cqi_FormatIndicatorPeriodic_subbandCQI)
    {
        if(0 != cqi_FormatIndicatorPeriodic_subbandCQI_value.Pack(bits))
        {
            printf("CQI_ReportPeriodic::setup::cqi_FormatIndicatorPeriodic_subbandCQI pack failure\n");
            return -1;
        }
    }
    return 0;
}

int CQI_ReportPeriodic::setup::cqi_FormatIndicatorPeriodic_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return cqi_FormatIndicatorPeriodic_Unpack(bits, idx);
}

int CQI_ReportPeriodic::setup::cqi_FormatIndicatorPeriodic_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 1) > bits.size())
    {
        printf("CQI_ReportPeriodic::setup::cqi_FormatIndicatorPeriodic_Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<1; i++)
        packed_val |= bits[idx++] << (1-i-1);

    if((CQI_ReportPeriodic::setup::cqi_FormatIndicatorPeriodic_Enum)packed_val > k_cqi_FormatIndicatorPeriodic_subbandCQI)
    {
        printf("CQI_ReportPeriodic::setup::cqi_FormatIndicatorPeriodic_Unpack() choice range failure\n");
        return -1;
    }
    cqi_FormatIndicatorPeriodic_internal_choice = (CQI_ReportPeriodic::setup::cqi_FormatIndicatorPeriodic_Enum)packed_val;
    cqi_FormatIndicatorPeriodic_present = true;

    // Fields
    if(cqi_FormatIndicatorPeriodic_internal_choice == k_cqi_FormatIndicatorPeriodic_widebandCQI)
    {
        if(0 != cqi_FormatIndicatorPeriodic_widebandCQI_Unpack(bits, idx))
        {
            printf("CQI_ReportPeriodic::setup::cqi_FormatIndicatorPeriodic_widebandCQI unpack failure\n");
            return -1;
        }
    }
    if(cqi_FormatIndicatorPeriodic_internal_choice == k_cqi_FormatIndicatorPeriodic_subbandCQI)
    {
        if(0 != cqi_FormatIndicatorPeriodic_subbandCQI_value.Unpack(bits, idx))
        {
            printf("CQI_ReportPeriodic::setup::cqi_FormatIndicatorPeriodic_subbandCQI unpack failure\n");
            return -1;
        }
    }
    return 0;
}

CQI_ReportPeriodic::setup::cqi_FormatIndicatorPeriodic_Enum CQI_ReportPeriodic::setup::cqi_FormatIndicatorPeriodic_Choice() const
{
    if(cqi_FormatIndicatorPeriodic_present)
        return cqi_FormatIndicatorPeriodic_internal_choice;
    return (CQI_ReportPeriodic::setup::cqi_FormatIndicatorPeriodic_Enum)0;
}

int CQI_ReportPeriodic::setup::cqi_FormatIndicatorPeriodic_SetChoice(CQI_ReportPeriodic::setup::cqi_FormatIndicatorPeriodic_Enum choice)
{
    cqi_FormatIndicatorPeriodic_internal_choice = choice;
    cqi_FormatIndicatorPeriodic_present = true;
    return 0;
}

std::string CQI_ReportPeriodic::setup::cqi_FormatIndicatorPeriodic_ChoiceToString(cqi_FormatIndicatorPeriodic_Enum value) const
{
    if(k_cqi_FormatIndicatorPeriodic_widebandCQI == value)
        return "cqi_FormatIndicatorPeriodic_widebandCQI";
    if(k_cqi_FormatIndicatorPeriodic_subbandCQI == value)
        return "cqi_FormatIndicatorPeriodic_subbandCQI";
    return "";
}

uint64_t CQI_ReportPeriodic::setup::cqi_FormatIndicatorPeriodic_NumberOfChoices() const
{
    return 2;
}

std::string CQI_ReportPeriodic::setup::cqi_FormatIndicatorPeriodic_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cqi_FormatIndicatorPeriodic = " + cqi_FormatIndicatorPeriodic_ChoiceToString(cqi_FormatIndicatorPeriodic_internal_choice) + ":\n";
    if(cqi_FormatIndicatorPeriodic_internal_choice == k_cqi_FormatIndicatorPeriodic_subbandCQI)
        out += cqi_FormatIndicatorPeriodic_subbandCQI_value.ToString(indent+1);
    return out;
}

std::string CQI_ReportPeriodic::setup::cqi_FormatIndicatorPeriodic_ToStringNoNewLines() const
{
    std::string out = "cqi_FormatIndicatorPeriodic=" + cqi_FormatIndicatorPeriodic_ChoiceToString(cqi_FormatIndicatorPeriodic_internal_choice) + ",";
    if(cqi_FormatIndicatorPeriodic_internal_choice == k_cqi_FormatIndicatorPeriodic_subbandCQI)
        out += cqi_FormatIndicatorPeriodic_subbandCQI_value.ToStringNoNewLines();
    return out;
}

int CQI_ReportPeriodic::setup::cqi_FormatIndicatorPeriodic_Clear()
{
    cqi_FormatIndicatorPeriodic_present = false;
    return 0;
}

bool CQI_ReportPeriodic::setup::cqi_FormatIndicatorPeriodic_IsPresent() const
{
    return cqi_FormatIndicatorPeriodic_present;
}

int CQI_ReportPeriodic::setup::cqi_FormatIndicatorPeriodic_subbandCQI::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != k_Pack(bits))
        {
            printf("CQI_ReportPeriodic::setup::cqi_FormatIndicatorPeriodic_subbandCQI:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int CQI_ReportPeriodic::setup::cqi_FormatIndicatorPeriodic_subbandCQI::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int CQI_ReportPeriodic::setup::cqi_FormatIndicatorPeriodic_subbandCQI::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != k_Unpack(bits, idx))
        {
            printf("CQI_ReportPeriodic::setup::cqi_FormatIndicatorPeriodic_subbandCQI:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string CQI_ReportPeriodic::setup::cqi_FormatIndicatorPeriodic_subbandCQI::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "subbandCQI:\n";
    out += k_ToString(indent+1);
    return out;
}

std::string CQI_ReportPeriodic::setup::cqi_FormatIndicatorPeriodic_subbandCQI::ToStringNoNewLines() const
{
    std::string out = "subbandCQI:";
    out += k_ToStringNoNewLines();
    return out;
}

int CQI_ReportPeriodic::setup::cqi_FormatIndicatorPeriodic_subbandCQI::k_Pack(std::vector<uint8_t> &bits)
{
    if(!k_present)
    {
        printf("CQI_ReportPeriodic::setup::cqi_FormatIndicatorPeriodic_subbandCQI::k_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = k_internal_value - (1);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (4 - 1))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int CQI_ReportPeriodic::setup::cqi_FormatIndicatorPeriodic_subbandCQI::k_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return k_Unpack(bits, idx);
}

int CQI_ReportPeriodic::setup::cqi_FormatIndicatorPeriodic_subbandCQI::k_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (4 - 1))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("CQI_ReportPeriodic::setup::cqi_FormatIndicatorPeriodic_subbandCQI::k_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    k_internal_value = packed_val + 1;
    k_present = true;
    return 0;
}

int64_t CQI_ReportPeriodic::setup::cqi_FormatIndicatorPeriodic_subbandCQI::k_Value() const
{
    if(k_present)
        return k_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int CQI_ReportPeriodic::setup::cqi_FormatIndicatorPeriodic_subbandCQI::k_SetValue(int64_t value)
{
    if(value < 1 || value > 4)
    {
        printf("CQI_ReportPeriodic::setup::cqi_FormatIndicatorPeriodic_subbandCQI::k_SetValue() range failure\n");
        return -1;
    }
    k_internal_value = value;
    k_present = true;
    return 0;
}

std::string CQI_ReportPeriodic::setup::cqi_FormatIndicatorPeriodic_subbandCQI::k_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "k = " + std::to_string(k_internal_value) + "\n";
    return out;
}

std::string CQI_ReportPeriodic::setup::cqi_FormatIndicatorPeriodic_subbandCQI::k_ToStringNoNewLines() const
{
    std::string out = "k=" + std::to_string(k_internal_value) + ",";
    return out;
}

int CQI_ReportPeriodic::setup::cqi_FormatIndicatorPeriodic_subbandCQI::k_Clear()
{
    k_present = false;
    return 0;
}

bool CQI_ReportPeriodic::setup::cqi_FormatIndicatorPeriodic_subbandCQI::k_IsPresent() const
{
    return k_present;
}

int CQI_ReportPeriodic::setup::ri_ConfigIndex_Pack(std::vector<uint8_t> &bits)
{
    int64_t val_to_pack = ri_ConfigIndex_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (1023 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int CQI_ReportPeriodic::setup::ri_ConfigIndex_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return ri_ConfigIndex_Unpack(bits, idx);
}

int CQI_ReportPeriodic::setup::ri_ConfigIndex_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (1023 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("CQI_ReportPeriodic::setup::ri_ConfigIndex_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    ri_ConfigIndex_internal_value = packed_val + 0;
    ri_ConfigIndex_present = true;
    return 0;
}

int64_t CQI_ReportPeriodic::setup::ri_ConfigIndex_Value() const
{
    if(ri_ConfigIndex_present)
        return ri_ConfigIndex_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int CQI_ReportPeriodic::setup::ri_ConfigIndex_SetValue(int64_t value)
{
    if(value < 0 || value > 1023)
    {
        printf("CQI_ReportPeriodic::setup::ri_ConfigIndex_SetValue() range failure\n");
        return -1;
    }
    ri_ConfigIndex_internal_value = value;
    ri_ConfigIndex_present = true;
    return 0;
}

std::string CQI_ReportPeriodic::setup::ri_ConfigIndex_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ri_ConfigIndex = " + std::to_string(ri_ConfigIndex_internal_value) + "\n";
    return out;
}

std::string CQI_ReportPeriodic::setup::ri_ConfigIndex_ToStringNoNewLines() const
{
    std::string out = "ri_ConfigIndex=" + std::to_string(ri_ConfigIndex_internal_value) + ",";
    return out;
}

int CQI_ReportPeriodic::setup::ri_ConfigIndex_Clear()
{
    ri_ConfigIndex_present = false;
    return 0;
}

bool CQI_ReportPeriodic::setup::ri_ConfigIndex_IsPresent() const
{
    return ri_ConfigIndex_present;
}

int CQI_ReportPeriodic::setup::simultaneousAckNackAndCQI_Pack(std::vector<uint8_t> &bits)
{
    if(!simultaneousAckNackAndCQI_present)
    {
        printf("CQI_ReportPeriodic::setup::simultaneousAckNackAndCQI_Pack() presence failure\n");
        return -1;
    }
    bits.push_back(simultaneousAckNackAndCQI_internal_value);
    return 0;
}

int CQI_ReportPeriodic::setup::simultaneousAckNackAndCQI_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return simultaneousAckNackAndCQI_Unpack(bits, idx);
}

int CQI_ReportPeriodic::setup::simultaneousAckNackAndCQI_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    if((idx + 1) > bits.size())
    {
        printf("CQI_ReportPeriodic::setup::simultaneousAckNackAndCQI_Unpack() index out of bounds\n");
        return -1;
    }
    simultaneousAckNackAndCQI_internal_value = bits[idx++];
    simultaneousAckNackAndCQI_present = true;
    return 0;
}

bool CQI_ReportPeriodic::setup::simultaneousAckNackAndCQI_Value() const
{
    if(simultaneousAckNackAndCQI_present)
        return simultaneousAckNackAndCQI_internal_value;
    return false;
}

int CQI_ReportPeriodic::setup::simultaneousAckNackAndCQI_SetValue(bool value)
{
    simultaneousAckNackAndCQI_internal_value = value;
    simultaneousAckNackAndCQI_present = true;
    return 0;
}

std::string CQI_ReportPeriodic::setup::simultaneousAckNackAndCQI_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "simultaneousAckNackAndCQI = " + std::to_string(simultaneousAckNackAndCQI_internal_value) + "\n";
    return out;
}

std::string CQI_ReportPeriodic::setup::simultaneousAckNackAndCQI_ToStringNoNewLines() const
{
    std::string out = "simultaneousAckNackAndCQI=" + std::to_string(simultaneousAckNackAndCQI_internal_value) + ",";
    return out;
}

int CQI_ReportPeriodic::setup::simultaneousAckNackAndCQI_Clear()
{
    simultaneousAckNackAndCQI_present = false;
    return 0;
}

bool CQI_ReportPeriodic::setup::simultaneousAckNackAndCQI_IsPresent() const
{
    return simultaneousAckNackAndCQI_present;
}

