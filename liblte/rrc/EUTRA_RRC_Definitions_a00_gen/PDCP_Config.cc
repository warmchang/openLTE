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

#include "PDCP_Config.h"

#include <cmath>

int PDCP_Config::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator
    bits.push_back(0);

    // Optional indicators
    bits.push_back(discardTimer_IsPresent());
    bits.push_back(rlc_AM_value.IsPresent());
    bits.push_back(rlc_UM_value.IsPresent());

    // Fields
    if(discardTimer_IsPresent())
    {
        if(0 != discardTimer_Pack(bits))
        {
            printf("PDCP_Config:: field pack failure\n");
            return -1;
        }
    }
    if(rlc_AM_value.IsPresent())
    {
        if(0 != rlc_AM_value.Pack(bits))
        {
            printf("PDCP_Config:: field pack failure\n");
            return -1;
        }
    }
    if(rlc_UM_value.IsPresent())
    {
        if(0 != rlc_UM_value.Pack(bits))
        {
            printf("PDCP_Config:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != headerCompression_Pack(bits))
        {
            printf("PDCP_Config:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int PDCP_Config::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int PDCP_Config::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("PDCP_Config::Unpack() index out of bounds for extension\n");
        return -1;
    }
    idx++;

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("PDCP_Config::Unpack() index out of bounds for optional indiator discardTimer\n");
        return -1;
    }
    discardTimer_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("PDCP_Config::Unpack() index out of bounds for optional indiator rlc_AM\n");
        return -1;
    }
    rlc_AM_value.SetPresence(bits[idx++]);
    if((idx + 1) > bits.size())
    {
        printf("PDCP_Config::Unpack() index out of bounds for optional indiator rlc_UM\n");
        return -1;
    }
    rlc_UM_value.SetPresence(bits[idx++]);

    // Fields
    if(discardTimer_present)
    {
        if(0 != discardTimer_Unpack(bits, idx))
        {
            printf("PDCP_Config:: field unpack failure\n");
            return -1;
        }
    }
    if(rlc_AM_value.IsPresent())
    {
        if(0 != rlc_AM_value.Unpack(bits, idx))
        {
            printf("PDCP_Config:: field unpack failure\n");
            return -1;
        }
    }
    if(rlc_UM_value.IsPresent())
    {
        if(0 != rlc_UM_value.Unpack(bits, idx))
        {
            printf("PDCP_Config:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != headerCompression_Unpack(bits, idx))
        {
            printf("PDCP_Config:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string PDCP_Config::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "PDCP_Config:\n";
    if(discardTimer_IsPresent())
        out += discardTimer_ToString(indent+1);
    if(rlc_AM_value.IsPresent())
        out += rlc_AM_value.ToString(indent+1);
    if(rlc_UM_value.IsPresent())
        out += rlc_UM_value.ToString(indent+1);
    out += headerCompression_ToString(indent+1);
    return out;
}

std::string PDCP_Config::ToStringNoNewLines() const
{
    std::string out = "PDCP_Config:";
    if(discardTimer_IsPresent())
        out += discardTimer_ToStringNoNewLines();
    if(rlc_AM_value.IsPresent())
        out += rlc_AM_value.ToStringNoNewLines();
    if(rlc_UM_value.IsPresent())
        out += rlc_UM_value.ToStringNoNewLines();
    out += headerCompression_ToStringNoNewLines();
    return out;
}

int PDCP_Config::discardTimer_Pack(std::vector<uint8_t> &bits)
{
    uint32_t N_bits = 3;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((discardTimer_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int PDCP_Config::discardTimer_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return discardTimer_Unpack(bits, idx);
}

int PDCP_Config::discardTimer_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 3;
    if((idx + N_bits) > bits.size())
    {
        printf("PDCP_Config::discardTimer_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 7)
    {
        printf("PDCP_Config::discardTimer_Unpack() max failure\n");
        return -1;
    }
    discardTimer_internal_value = (discardTimer_Enum)packed_val;
    discardTimer_present = true;
    return 0;
}

PDCP_Config::discardTimer_Enum PDCP_Config::discardTimer_Value() const
{
    if(discardTimer_present)
        return discardTimer_internal_value;
    return (PDCP_Config::discardTimer_Enum)0;
}

int PDCP_Config::discardTimer_SetValue(discardTimer_Enum value)
{
    discardTimer_internal_value = value;
    discardTimer_present = true;
    return 0;
}

int PDCP_Config::discardTimer_SetValue(std::string value)
{
    if("ms50" == value)
    {
        discardTimer_internal_value = k_discardTimer_ms50;
        discardTimer_present = true;
        return 0;
    }
    if("ms100" == value)
    {
        discardTimer_internal_value = k_discardTimer_ms100;
        discardTimer_present = true;
        return 0;
    }
    if("ms150" == value)
    {
        discardTimer_internal_value = k_discardTimer_ms150;
        discardTimer_present = true;
        return 0;
    }
    if("ms300" == value)
    {
        discardTimer_internal_value = k_discardTimer_ms300;
        discardTimer_present = true;
        return 0;
    }
    if("ms500" == value)
    {
        discardTimer_internal_value = k_discardTimer_ms500;
        discardTimer_present = true;
        return 0;
    }
    if("ms750" == value)
    {
        discardTimer_internal_value = k_discardTimer_ms750;
        discardTimer_present = true;
        return 0;
    }
    if("ms1500" == value)
    {
        discardTimer_internal_value = k_discardTimer_ms1500;
        discardTimer_present = true;
        return 0;
    }
    if("infinity" == value)
    {
        discardTimer_internal_value = k_discardTimer_infinity;
        discardTimer_present = true;
        return 0;
    }
    return 1;
}

std::string PDCP_Config::discardTimer_ValueToString(discardTimer_Enum value) const
{
    if(k_discardTimer_ms50 == value)
        return "ms50";
    if(k_discardTimer_ms100 == value)
        return "ms100";
    if(k_discardTimer_ms150 == value)
        return "ms150";
    if(k_discardTimer_ms300 == value)
        return "ms300";
    if(k_discardTimer_ms500 == value)
        return "ms500";
    if(k_discardTimer_ms750 == value)
        return "ms750";
    if(k_discardTimer_ms1500 == value)
        return "ms1500";
    if(k_discardTimer_infinity == value)
        return "infinity";
    return "";
}

uint64_t PDCP_Config::discardTimer_NumberOfValues() const
{
    return 8;
}

std::string PDCP_Config::discardTimer_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "discardTimer = " + discardTimer_ValueToString(discardTimer_internal_value) + "\n";
    return out;
}

std::string PDCP_Config::discardTimer_ToStringNoNewLines() const
{
    std::string out = "discardTimer=" + discardTimer_ValueToString(discardTimer_internal_value) + ",";
    return out;
}

int PDCP_Config::discardTimer_Clear()
{
    discardTimer_present = false;
    return 0;
}

bool PDCP_Config::discardTimer_IsPresent() const
{
    return discardTimer_present;
}

int PDCP_Config::rlc_AM::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != statusReportRequired_Pack(bits))
        {
            printf("PDCP_Config::rlc_AM:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int PDCP_Config::rlc_AM::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int PDCP_Config::rlc_AM::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != statusReportRequired_Unpack(bits, idx))
        {
            printf("PDCP_Config::rlc_AM:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string PDCP_Config::rlc_AM::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "rlc_AM:\n";
    out += statusReportRequired_ToString(indent+1);
    return out;
}

std::string PDCP_Config::rlc_AM::ToStringNoNewLines() const
{
    std::string out = "rlc_AM:";
    out += statusReportRequired_ToStringNoNewLines();
    return out;
}

int PDCP_Config::rlc_AM::Set()
{
    present = true;
    return 0;
}

int PDCP_Config::rlc_AM::SetPresence(bool is_present)
{
    present = is_present;
    return 0;
}

int PDCP_Config::rlc_AM::Clear()
{
    present = false;
    return 0;
}

bool PDCP_Config::rlc_AM::IsPresent() const
{
    return present;
}

int PDCP_Config::rlc_AM::statusReportRequired_Pack(std::vector<uint8_t> &bits)
{
    if(!statusReportRequired_present)
    {
        printf("PDCP_Config::rlc_AM::statusReportRequired_Pack() presence failure\n");
        return -1;
    }
    bits.push_back(statusReportRequired_internal_value);
    return 0;
}

int PDCP_Config::rlc_AM::statusReportRequired_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return statusReportRequired_Unpack(bits, idx);
}

int PDCP_Config::rlc_AM::statusReportRequired_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    if((idx + 1) > bits.size())
    {
        printf("PDCP_Config::rlc_AM::statusReportRequired_Unpack() index out of bounds\n");
        return -1;
    }
    statusReportRequired_internal_value = bits[idx++];
    statusReportRequired_present = true;
    return 0;
}

bool PDCP_Config::rlc_AM::statusReportRequired_Value() const
{
    if(statusReportRequired_present)
        return statusReportRequired_internal_value;
    return false;
}

int PDCP_Config::rlc_AM::statusReportRequired_SetValue(bool value)
{
    statusReportRequired_internal_value = value;
    statusReportRequired_present = true;
    return 0;
}

std::string PDCP_Config::rlc_AM::statusReportRequired_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "statusReportRequired = " + std::to_string(statusReportRequired_internal_value) + "\n";
    return out;
}

std::string PDCP_Config::rlc_AM::statusReportRequired_ToStringNoNewLines() const
{
    std::string out = "statusReportRequired=" + std::to_string(statusReportRequired_internal_value) + ",";
    return out;
}

int PDCP_Config::rlc_AM::statusReportRequired_Clear()
{
    statusReportRequired_present = false;
    return 0;
}

bool PDCP_Config::rlc_AM::statusReportRequired_IsPresent() const
{
    return statusReportRequired_present;
}

int PDCP_Config::rlc_UM::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != pdcp_SN_Size_Pack(bits))
        {
            printf("PDCP_Config::rlc_UM:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int PDCP_Config::rlc_UM::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int PDCP_Config::rlc_UM::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != pdcp_SN_Size_Unpack(bits, idx))
        {
            printf("PDCP_Config::rlc_UM:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string PDCP_Config::rlc_UM::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "rlc_UM:\n";
    out += pdcp_SN_Size_ToString(indent+1);
    return out;
}

std::string PDCP_Config::rlc_UM::ToStringNoNewLines() const
{
    std::string out = "rlc_UM:";
    out += pdcp_SN_Size_ToStringNoNewLines();
    return out;
}

int PDCP_Config::rlc_UM::Set()
{
    present = true;
    return 0;
}

int PDCP_Config::rlc_UM::SetPresence(bool is_present)
{
    present = is_present;
    return 0;
}

int PDCP_Config::rlc_UM::Clear()
{
    present = false;
    return 0;
}

bool PDCP_Config::rlc_UM::IsPresent() const
{
    return present;
}

int PDCP_Config::rlc_UM::pdcp_SN_Size_Pack(std::vector<uint8_t> &bits)
{
    if(!pdcp_SN_Size_present)
    {
        printf("PDCP_Config::rlc_UM::pdcp_SN_Size_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((pdcp_SN_Size_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int PDCP_Config::rlc_UM::pdcp_SN_Size_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return pdcp_SN_Size_Unpack(bits, idx);
}

int PDCP_Config::rlc_UM::pdcp_SN_Size_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("PDCP_Config::rlc_UM::pdcp_SN_Size_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 1)
    {
        printf("PDCP_Config::rlc_UM::pdcp_SN_Size_Unpack() max failure\n");
        return -1;
    }
    pdcp_SN_Size_internal_value = (pdcp_SN_Size_Enum)packed_val;
    pdcp_SN_Size_present = true;
    return 0;
}

PDCP_Config::rlc_UM::pdcp_SN_Size_Enum PDCP_Config::rlc_UM::pdcp_SN_Size_Value() const
{
    if(pdcp_SN_Size_present)
        return pdcp_SN_Size_internal_value;
    return (PDCP_Config::rlc_UM::pdcp_SN_Size_Enum)0;
}

int PDCP_Config::rlc_UM::pdcp_SN_Size_SetValue(pdcp_SN_Size_Enum value)
{
    pdcp_SN_Size_internal_value = value;
    pdcp_SN_Size_present = true;
    return 0;
}

int PDCP_Config::rlc_UM::pdcp_SN_Size_SetValue(std::string value)
{
    if("len7bits" == value)
    {
        pdcp_SN_Size_internal_value = k_pdcp_SN_Size_len7bits;
        pdcp_SN_Size_present = true;
        return 0;
    }
    if("len12bits" == value)
    {
        pdcp_SN_Size_internal_value = k_pdcp_SN_Size_len12bits;
        pdcp_SN_Size_present = true;
        return 0;
    }
    return 1;
}

std::string PDCP_Config::rlc_UM::pdcp_SN_Size_ValueToString(pdcp_SN_Size_Enum value) const
{
    if(k_pdcp_SN_Size_len7bits == value)
        return "len7bits";
    if(k_pdcp_SN_Size_len12bits == value)
        return "len12bits";
    return "";
}

uint64_t PDCP_Config::rlc_UM::pdcp_SN_Size_NumberOfValues() const
{
    return 2;
}

std::string PDCP_Config::rlc_UM::pdcp_SN_Size_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "pdcp_SN_Size = " + pdcp_SN_Size_ValueToString(pdcp_SN_Size_internal_value) + "\n";
    return out;
}

std::string PDCP_Config::rlc_UM::pdcp_SN_Size_ToStringNoNewLines() const
{
    std::string out = "pdcp_SN_Size=" + pdcp_SN_Size_ValueToString(pdcp_SN_Size_internal_value) + ",";
    return out;
}

int PDCP_Config::rlc_UM::pdcp_SN_Size_Clear()
{
    pdcp_SN_Size_present = false;
    return 0;
}

bool PDCP_Config::rlc_UM::pdcp_SN_Size_IsPresent() const
{
    return pdcp_SN_Size_present;
}

int PDCP_Config::headerCompression_Pack(std::vector<uint8_t> &bits)
{
    if(!headerCompression_present)
    {
        printf("PDCP_Config::headerCompression_Pack() presence failure\n");
        return -1;
    }
    // Extension indicator

    // Choice
    for(uint32_t i=0; i<1; i++)
        bits.push_back((headerCompression_internal_choice >> (1-i-1)) & 1);

    // Fields
    if(headerCompression_internal_choice == k_headerCompression_notUsed)
    {
        if(0 != headerCompression_notUsed_Pack(bits))
        {
            printf("PDCP_Config::headerCompression_notUsed pack failure\n");
            return -1;
        }
    }
    if(headerCompression_internal_choice == k_headerCompression_rohc)
    {
        if(0 != headerCompression_rohc_value.Pack(bits))
        {
            printf("PDCP_Config::headerCompression_rohc pack failure\n");
            return -1;
        }
    }
    return 0;
}

int PDCP_Config::headerCompression_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return headerCompression_Unpack(bits, idx);
}

int PDCP_Config::headerCompression_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 1) > bits.size())
    {
        printf("PDCP_Config::headerCompression_Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<1; i++)
        packed_val |= bits[idx++] << (1-i-1);

    if((PDCP_Config::headerCompression_Enum)packed_val > k_headerCompression_rohc)
    {
        printf("PDCP_Config::headerCompression_Unpack() choice range failure\n");
        return -1;
    }
    headerCompression_internal_choice = (PDCP_Config::headerCompression_Enum)packed_val;
    headerCompression_present = true;

    // Fields
    if(headerCompression_internal_choice == k_headerCompression_notUsed)
    {
        if(0 != headerCompression_notUsed_Unpack(bits, idx))
        {
            printf("PDCP_Config::headerCompression_notUsed unpack failure\n");
            return -1;
        }
    }
    if(headerCompression_internal_choice == k_headerCompression_rohc)
    {
        if(0 != headerCompression_rohc_value.Unpack(bits, idx))
        {
            printf("PDCP_Config::headerCompression_rohc unpack failure\n");
            return -1;
        }
    }
    return 0;
}

PDCP_Config::headerCompression_Enum PDCP_Config::headerCompression_Choice() const
{
    if(headerCompression_present)
        return headerCompression_internal_choice;
    return (PDCP_Config::headerCompression_Enum)0;
}

int PDCP_Config::headerCompression_SetChoice(PDCP_Config::headerCompression_Enum choice)
{
    headerCompression_internal_choice = choice;
    headerCompression_present = true;
    return 0;
}

std::string PDCP_Config::headerCompression_ChoiceToString(headerCompression_Enum value) const
{
    if(k_headerCompression_notUsed == value)
        return "headerCompression_notUsed";
    if(k_headerCompression_rohc == value)
        return "headerCompression_rohc";
    return "";
}

uint64_t PDCP_Config::headerCompression_NumberOfChoices() const
{
    return 2;
}

std::string PDCP_Config::headerCompression_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "headerCompression = " + headerCompression_ChoiceToString(headerCompression_internal_choice) + ":\n";
    if(headerCompression_internal_choice == k_headerCompression_rohc)
        out += headerCompression_rohc_value.ToString(indent+1);
    return out;
}

std::string PDCP_Config::headerCompression_ToStringNoNewLines() const
{
    std::string out = "headerCompression=" + headerCompression_ChoiceToString(headerCompression_internal_choice) + ",";
    if(headerCompression_internal_choice == k_headerCompression_rohc)
        out += headerCompression_rohc_value.ToStringNoNewLines();
    return out;
}

int PDCP_Config::headerCompression_Clear()
{
    headerCompression_present = false;
    return 0;
}

bool PDCP_Config::headerCompression_IsPresent() const
{
    return headerCompression_present;
}

int PDCP_Config::headerCompression_rohc::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator
    bits.push_back(0);

    // Optional indicators
    if(!maxCID_IsPresent() || maxCID_Value() == maxCID_GetDefault())
    {
        bits.push_back(0);
    }else{
        bits.push_back(1);
    }

    // Fields
    if(maxCID_IsPresent() || maxCID_Value() != maxCID_GetDefault())
    {
        if(0 != maxCID_Pack(bits))
        {
            printf("PDCP_Config::headerCompression_rohc:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != profiles_value.Pack(bits))
        {
            printf("PDCP_Config::headerCompression_rohc:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int PDCP_Config::headerCompression_rohc::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int PDCP_Config::headerCompression_rohc::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("headerCompression_rohc::Unpack() index out of bounds for extension\n");
        return -1;
    }
    idx++;

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("headerCompression_rohc::Unpack() index out of bounds for optional indiator maxCID\n");
        return -1;
    }
    maxCID_present = bits[idx++];

    // Fields
    {
        if(0 != maxCID_Unpack(bits, idx))
        {
            printf("PDCP_Config::headerCompression_rohc:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != profiles_value.Unpack(bits, idx))
        {
            printf("PDCP_Config::headerCompression_rohc:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string PDCP_Config::headerCompression_rohc::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "rohc:\n";
    out += maxCID_ToString(indent+1);
    out += profiles_value.ToString(indent+1);
    return out;
}

std::string PDCP_Config::headerCompression_rohc::ToStringNoNewLines() const
{
    std::string out = "rohc:";
    out += maxCID_ToStringNoNewLines();
    out += profiles_value.ToStringNoNewLines();
    return out;
}

int PDCP_Config::headerCompression_rohc::maxCID_Pack(std::vector<uint8_t> &bits)
{
    if(!maxCID_present)
    {
        maxCID_present = true;
        maxCID_internal_value = maxCID_GetDefault();
    }
    if(!maxCID_present)
    {
        printf("PDCP_Config::headerCompression_rohc::maxCID_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = maxCID_internal_value - (1);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (16383 - 1))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int PDCP_Config::headerCompression_rohc::maxCID_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return maxCID_Unpack(bits, idx);
}

int PDCP_Config::headerCompression_rohc::maxCID_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (16383 - 1))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("PDCP_Config::headerCompression_rohc::maxCID_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    maxCID_internal_value = packed_val + 1;
    maxCID_present = true;
    return 0;
}

int64_t PDCP_Config::headerCompression_rohc::maxCID_Value() const
{
    if(maxCID_present)
        return maxCID_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int PDCP_Config::headerCompression_rohc::maxCID_SetValue(int64_t value)
{
    if(value < 1 || value > 16383)
    {
        printf("PDCP_Config::headerCompression_rohc::maxCID_SetValue() range failure\n");
        return -1;
    }
    maxCID_internal_value = value;
    maxCID_present = true;
    return 0;
}

int PDCP_Config::headerCompression_rohc::maxCID_GetDefault() const
{
    return 15;
}

std::string PDCP_Config::headerCompression_rohc::maxCID_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "maxCID = " + std::to_string(maxCID_internal_value) + "\n";
    return out;
}

std::string PDCP_Config::headerCompression_rohc::maxCID_ToStringNoNewLines() const
{
    std::string out = "maxCID=" + std::to_string(maxCID_internal_value) + ",";
    return out;
}

int PDCP_Config::headerCompression_rohc::maxCID_Clear()
{
    maxCID_present = false;
    return 0;
}

bool PDCP_Config::headerCompression_rohc::maxCID_IsPresent() const
{
    return maxCID_present;
}

int PDCP_Config::headerCompression_rohc::profiles::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != profile0x0001_Pack(bits))
        {
            printf("PDCP_Config::headerCompression_rohc::profiles:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != profile0x0002_Pack(bits))
        {
            printf("PDCP_Config::headerCompression_rohc::profiles:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != profile0x0003_Pack(bits))
        {
            printf("PDCP_Config::headerCompression_rohc::profiles:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != profile0x0004_Pack(bits))
        {
            printf("PDCP_Config::headerCompression_rohc::profiles:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != profile0x0006_Pack(bits))
        {
            printf("PDCP_Config::headerCompression_rohc::profiles:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != profile0x0101_Pack(bits))
        {
            printf("PDCP_Config::headerCompression_rohc::profiles:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != profile0x0102_Pack(bits))
        {
            printf("PDCP_Config::headerCompression_rohc::profiles:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != profile0x0103_Pack(bits))
        {
            printf("PDCP_Config::headerCompression_rohc::profiles:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != profile0x0104_Pack(bits))
        {
            printf("PDCP_Config::headerCompression_rohc::profiles:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int PDCP_Config::headerCompression_rohc::profiles::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int PDCP_Config::headerCompression_rohc::profiles::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != profile0x0001_Unpack(bits, idx))
        {
            printf("PDCP_Config::headerCompression_rohc::profiles:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != profile0x0002_Unpack(bits, idx))
        {
            printf("PDCP_Config::headerCompression_rohc::profiles:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != profile0x0003_Unpack(bits, idx))
        {
            printf("PDCP_Config::headerCompression_rohc::profiles:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != profile0x0004_Unpack(bits, idx))
        {
            printf("PDCP_Config::headerCompression_rohc::profiles:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != profile0x0006_Unpack(bits, idx))
        {
            printf("PDCP_Config::headerCompression_rohc::profiles:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != profile0x0101_Unpack(bits, idx))
        {
            printf("PDCP_Config::headerCompression_rohc::profiles:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != profile0x0102_Unpack(bits, idx))
        {
            printf("PDCP_Config::headerCompression_rohc::profiles:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != profile0x0103_Unpack(bits, idx))
        {
            printf("PDCP_Config::headerCompression_rohc::profiles:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != profile0x0104_Unpack(bits, idx))
        {
            printf("PDCP_Config::headerCompression_rohc::profiles:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string PDCP_Config::headerCompression_rohc::profiles::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "profiles:\n";
    out += profile0x0001_ToString(indent+1);
    out += profile0x0002_ToString(indent+1);
    out += profile0x0003_ToString(indent+1);
    out += profile0x0004_ToString(indent+1);
    out += profile0x0006_ToString(indent+1);
    out += profile0x0101_ToString(indent+1);
    out += profile0x0102_ToString(indent+1);
    out += profile0x0103_ToString(indent+1);
    out += profile0x0104_ToString(indent+1);
    return out;
}

std::string PDCP_Config::headerCompression_rohc::profiles::ToStringNoNewLines() const
{
    std::string out = "profiles:";
    out += profile0x0001_ToStringNoNewLines();
    out += profile0x0002_ToStringNoNewLines();
    out += profile0x0003_ToStringNoNewLines();
    out += profile0x0004_ToStringNoNewLines();
    out += profile0x0006_ToStringNoNewLines();
    out += profile0x0101_ToStringNoNewLines();
    out += profile0x0102_ToStringNoNewLines();
    out += profile0x0103_ToStringNoNewLines();
    out += profile0x0104_ToStringNoNewLines();
    return out;
}

int PDCP_Config::headerCompression_rohc::profiles::profile0x0001_Pack(std::vector<uint8_t> &bits)
{
    if(!profile0x0001_present)
    {
        printf("PDCP_Config::headerCompression_rohc::profiles::profile0x0001_Pack() presence failure\n");
        return -1;
    }
    bits.push_back(profile0x0001_internal_value);
    return 0;
}

int PDCP_Config::headerCompression_rohc::profiles::profile0x0001_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return profile0x0001_Unpack(bits, idx);
}

int PDCP_Config::headerCompression_rohc::profiles::profile0x0001_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    if((idx + 1) > bits.size())
    {
        printf("PDCP_Config::headerCompression_rohc::profiles::profile0x0001_Unpack() index out of bounds\n");
        return -1;
    }
    profile0x0001_internal_value = bits[idx++];
    profile0x0001_present = true;
    return 0;
}

bool PDCP_Config::headerCompression_rohc::profiles::profile0x0001_Value() const
{
    if(profile0x0001_present)
        return profile0x0001_internal_value;
    return false;
}

int PDCP_Config::headerCompression_rohc::profiles::profile0x0001_SetValue(bool value)
{
    profile0x0001_internal_value = value;
    profile0x0001_present = true;
    return 0;
}

std::string PDCP_Config::headerCompression_rohc::profiles::profile0x0001_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "profile0x0001 = " + std::to_string(profile0x0001_internal_value) + "\n";
    return out;
}

std::string PDCP_Config::headerCompression_rohc::profiles::profile0x0001_ToStringNoNewLines() const
{
    std::string out = "profile0x0001=" + std::to_string(profile0x0001_internal_value) + ",";
    return out;
}

int PDCP_Config::headerCompression_rohc::profiles::profile0x0001_Clear()
{
    profile0x0001_present = false;
    return 0;
}

bool PDCP_Config::headerCompression_rohc::profiles::profile0x0001_IsPresent() const
{
    return profile0x0001_present;
}

int PDCP_Config::headerCompression_rohc::profiles::profile0x0002_Pack(std::vector<uint8_t> &bits)
{
    if(!profile0x0002_present)
    {
        printf("PDCP_Config::headerCompression_rohc::profiles::profile0x0002_Pack() presence failure\n");
        return -1;
    }
    bits.push_back(profile0x0002_internal_value);
    return 0;
}

int PDCP_Config::headerCompression_rohc::profiles::profile0x0002_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return profile0x0002_Unpack(bits, idx);
}

int PDCP_Config::headerCompression_rohc::profiles::profile0x0002_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    if((idx + 1) > bits.size())
    {
        printf("PDCP_Config::headerCompression_rohc::profiles::profile0x0002_Unpack() index out of bounds\n");
        return -1;
    }
    profile0x0002_internal_value = bits[idx++];
    profile0x0002_present = true;
    return 0;
}

bool PDCP_Config::headerCompression_rohc::profiles::profile0x0002_Value() const
{
    if(profile0x0002_present)
        return profile0x0002_internal_value;
    return false;
}

int PDCP_Config::headerCompression_rohc::profiles::profile0x0002_SetValue(bool value)
{
    profile0x0002_internal_value = value;
    profile0x0002_present = true;
    return 0;
}

std::string PDCP_Config::headerCompression_rohc::profiles::profile0x0002_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "profile0x0002 = " + std::to_string(profile0x0002_internal_value) + "\n";
    return out;
}

std::string PDCP_Config::headerCompression_rohc::profiles::profile0x0002_ToStringNoNewLines() const
{
    std::string out = "profile0x0002=" + std::to_string(profile0x0002_internal_value) + ",";
    return out;
}

int PDCP_Config::headerCompression_rohc::profiles::profile0x0002_Clear()
{
    profile0x0002_present = false;
    return 0;
}

bool PDCP_Config::headerCompression_rohc::profiles::profile0x0002_IsPresent() const
{
    return profile0x0002_present;
}

int PDCP_Config::headerCompression_rohc::profiles::profile0x0003_Pack(std::vector<uint8_t> &bits)
{
    if(!profile0x0003_present)
    {
        printf("PDCP_Config::headerCompression_rohc::profiles::profile0x0003_Pack() presence failure\n");
        return -1;
    }
    bits.push_back(profile0x0003_internal_value);
    return 0;
}

int PDCP_Config::headerCompression_rohc::profiles::profile0x0003_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return profile0x0003_Unpack(bits, idx);
}

int PDCP_Config::headerCompression_rohc::profiles::profile0x0003_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    if((idx + 1) > bits.size())
    {
        printf("PDCP_Config::headerCompression_rohc::profiles::profile0x0003_Unpack() index out of bounds\n");
        return -1;
    }
    profile0x0003_internal_value = bits[idx++];
    profile0x0003_present = true;
    return 0;
}

bool PDCP_Config::headerCompression_rohc::profiles::profile0x0003_Value() const
{
    if(profile0x0003_present)
        return profile0x0003_internal_value;
    return false;
}

int PDCP_Config::headerCompression_rohc::profiles::profile0x0003_SetValue(bool value)
{
    profile0x0003_internal_value = value;
    profile0x0003_present = true;
    return 0;
}

std::string PDCP_Config::headerCompression_rohc::profiles::profile0x0003_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "profile0x0003 = " + std::to_string(profile0x0003_internal_value) + "\n";
    return out;
}

std::string PDCP_Config::headerCompression_rohc::profiles::profile0x0003_ToStringNoNewLines() const
{
    std::string out = "profile0x0003=" + std::to_string(profile0x0003_internal_value) + ",";
    return out;
}

int PDCP_Config::headerCompression_rohc::profiles::profile0x0003_Clear()
{
    profile0x0003_present = false;
    return 0;
}

bool PDCP_Config::headerCompression_rohc::profiles::profile0x0003_IsPresent() const
{
    return profile0x0003_present;
}

int PDCP_Config::headerCompression_rohc::profiles::profile0x0004_Pack(std::vector<uint8_t> &bits)
{
    if(!profile0x0004_present)
    {
        printf("PDCP_Config::headerCompression_rohc::profiles::profile0x0004_Pack() presence failure\n");
        return -1;
    }
    bits.push_back(profile0x0004_internal_value);
    return 0;
}

int PDCP_Config::headerCompression_rohc::profiles::profile0x0004_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return profile0x0004_Unpack(bits, idx);
}

int PDCP_Config::headerCompression_rohc::profiles::profile0x0004_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    if((idx + 1) > bits.size())
    {
        printf("PDCP_Config::headerCompression_rohc::profiles::profile0x0004_Unpack() index out of bounds\n");
        return -1;
    }
    profile0x0004_internal_value = bits[idx++];
    profile0x0004_present = true;
    return 0;
}

bool PDCP_Config::headerCompression_rohc::profiles::profile0x0004_Value() const
{
    if(profile0x0004_present)
        return profile0x0004_internal_value;
    return false;
}

int PDCP_Config::headerCompression_rohc::profiles::profile0x0004_SetValue(bool value)
{
    profile0x0004_internal_value = value;
    profile0x0004_present = true;
    return 0;
}

std::string PDCP_Config::headerCompression_rohc::profiles::profile0x0004_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "profile0x0004 = " + std::to_string(profile0x0004_internal_value) + "\n";
    return out;
}

std::string PDCP_Config::headerCompression_rohc::profiles::profile0x0004_ToStringNoNewLines() const
{
    std::string out = "profile0x0004=" + std::to_string(profile0x0004_internal_value) + ",";
    return out;
}

int PDCP_Config::headerCompression_rohc::profiles::profile0x0004_Clear()
{
    profile0x0004_present = false;
    return 0;
}

bool PDCP_Config::headerCompression_rohc::profiles::profile0x0004_IsPresent() const
{
    return profile0x0004_present;
}

int PDCP_Config::headerCompression_rohc::profiles::profile0x0006_Pack(std::vector<uint8_t> &bits)
{
    if(!profile0x0006_present)
    {
        printf("PDCP_Config::headerCompression_rohc::profiles::profile0x0006_Pack() presence failure\n");
        return -1;
    }
    bits.push_back(profile0x0006_internal_value);
    return 0;
}

int PDCP_Config::headerCompression_rohc::profiles::profile0x0006_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return profile0x0006_Unpack(bits, idx);
}

int PDCP_Config::headerCompression_rohc::profiles::profile0x0006_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    if((idx + 1) > bits.size())
    {
        printf("PDCP_Config::headerCompression_rohc::profiles::profile0x0006_Unpack() index out of bounds\n");
        return -1;
    }
    profile0x0006_internal_value = bits[idx++];
    profile0x0006_present = true;
    return 0;
}

bool PDCP_Config::headerCompression_rohc::profiles::profile0x0006_Value() const
{
    if(profile0x0006_present)
        return profile0x0006_internal_value;
    return false;
}

int PDCP_Config::headerCompression_rohc::profiles::profile0x0006_SetValue(bool value)
{
    profile0x0006_internal_value = value;
    profile0x0006_present = true;
    return 0;
}

std::string PDCP_Config::headerCompression_rohc::profiles::profile0x0006_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "profile0x0006 = " + std::to_string(profile0x0006_internal_value) + "\n";
    return out;
}

std::string PDCP_Config::headerCompression_rohc::profiles::profile0x0006_ToStringNoNewLines() const
{
    std::string out = "profile0x0006=" + std::to_string(profile0x0006_internal_value) + ",";
    return out;
}

int PDCP_Config::headerCompression_rohc::profiles::profile0x0006_Clear()
{
    profile0x0006_present = false;
    return 0;
}

bool PDCP_Config::headerCompression_rohc::profiles::profile0x0006_IsPresent() const
{
    return profile0x0006_present;
}

int PDCP_Config::headerCompression_rohc::profiles::profile0x0101_Pack(std::vector<uint8_t> &bits)
{
    if(!profile0x0101_present)
    {
        printf("PDCP_Config::headerCompression_rohc::profiles::profile0x0101_Pack() presence failure\n");
        return -1;
    }
    bits.push_back(profile0x0101_internal_value);
    return 0;
}

int PDCP_Config::headerCompression_rohc::profiles::profile0x0101_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return profile0x0101_Unpack(bits, idx);
}

int PDCP_Config::headerCompression_rohc::profiles::profile0x0101_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    if((idx + 1) > bits.size())
    {
        printf("PDCP_Config::headerCompression_rohc::profiles::profile0x0101_Unpack() index out of bounds\n");
        return -1;
    }
    profile0x0101_internal_value = bits[idx++];
    profile0x0101_present = true;
    return 0;
}

bool PDCP_Config::headerCompression_rohc::profiles::profile0x0101_Value() const
{
    if(profile0x0101_present)
        return profile0x0101_internal_value;
    return false;
}

int PDCP_Config::headerCompression_rohc::profiles::profile0x0101_SetValue(bool value)
{
    profile0x0101_internal_value = value;
    profile0x0101_present = true;
    return 0;
}

std::string PDCP_Config::headerCompression_rohc::profiles::profile0x0101_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "profile0x0101 = " + std::to_string(profile0x0101_internal_value) + "\n";
    return out;
}

std::string PDCP_Config::headerCompression_rohc::profiles::profile0x0101_ToStringNoNewLines() const
{
    std::string out = "profile0x0101=" + std::to_string(profile0x0101_internal_value) + ",";
    return out;
}

int PDCP_Config::headerCompression_rohc::profiles::profile0x0101_Clear()
{
    profile0x0101_present = false;
    return 0;
}

bool PDCP_Config::headerCompression_rohc::profiles::profile0x0101_IsPresent() const
{
    return profile0x0101_present;
}

int PDCP_Config::headerCompression_rohc::profiles::profile0x0102_Pack(std::vector<uint8_t> &bits)
{
    if(!profile0x0102_present)
    {
        printf("PDCP_Config::headerCompression_rohc::profiles::profile0x0102_Pack() presence failure\n");
        return -1;
    }
    bits.push_back(profile0x0102_internal_value);
    return 0;
}

int PDCP_Config::headerCompression_rohc::profiles::profile0x0102_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return profile0x0102_Unpack(bits, idx);
}

int PDCP_Config::headerCompression_rohc::profiles::profile0x0102_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    if((idx + 1) > bits.size())
    {
        printf("PDCP_Config::headerCompression_rohc::profiles::profile0x0102_Unpack() index out of bounds\n");
        return -1;
    }
    profile0x0102_internal_value = bits[idx++];
    profile0x0102_present = true;
    return 0;
}

bool PDCP_Config::headerCompression_rohc::profiles::profile0x0102_Value() const
{
    if(profile0x0102_present)
        return profile0x0102_internal_value;
    return false;
}

int PDCP_Config::headerCompression_rohc::profiles::profile0x0102_SetValue(bool value)
{
    profile0x0102_internal_value = value;
    profile0x0102_present = true;
    return 0;
}

std::string PDCP_Config::headerCompression_rohc::profiles::profile0x0102_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "profile0x0102 = " + std::to_string(profile0x0102_internal_value) + "\n";
    return out;
}

std::string PDCP_Config::headerCompression_rohc::profiles::profile0x0102_ToStringNoNewLines() const
{
    std::string out = "profile0x0102=" + std::to_string(profile0x0102_internal_value) + ",";
    return out;
}

int PDCP_Config::headerCompression_rohc::profiles::profile0x0102_Clear()
{
    profile0x0102_present = false;
    return 0;
}

bool PDCP_Config::headerCompression_rohc::profiles::profile0x0102_IsPresent() const
{
    return profile0x0102_present;
}

int PDCP_Config::headerCompression_rohc::profiles::profile0x0103_Pack(std::vector<uint8_t> &bits)
{
    if(!profile0x0103_present)
    {
        printf("PDCP_Config::headerCompression_rohc::profiles::profile0x0103_Pack() presence failure\n");
        return -1;
    }
    bits.push_back(profile0x0103_internal_value);
    return 0;
}

int PDCP_Config::headerCompression_rohc::profiles::profile0x0103_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return profile0x0103_Unpack(bits, idx);
}

int PDCP_Config::headerCompression_rohc::profiles::profile0x0103_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    if((idx + 1) > bits.size())
    {
        printf("PDCP_Config::headerCompression_rohc::profiles::profile0x0103_Unpack() index out of bounds\n");
        return -1;
    }
    profile0x0103_internal_value = bits[idx++];
    profile0x0103_present = true;
    return 0;
}

bool PDCP_Config::headerCompression_rohc::profiles::profile0x0103_Value() const
{
    if(profile0x0103_present)
        return profile0x0103_internal_value;
    return false;
}

int PDCP_Config::headerCompression_rohc::profiles::profile0x0103_SetValue(bool value)
{
    profile0x0103_internal_value = value;
    profile0x0103_present = true;
    return 0;
}

std::string PDCP_Config::headerCompression_rohc::profiles::profile0x0103_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "profile0x0103 = " + std::to_string(profile0x0103_internal_value) + "\n";
    return out;
}

std::string PDCP_Config::headerCompression_rohc::profiles::profile0x0103_ToStringNoNewLines() const
{
    std::string out = "profile0x0103=" + std::to_string(profile0x0103_internal_value) + ",";
    return out;
}

int PDCP_Config::headerCompression_rohc::profiles::profile0x0103_Clear()
{
    profile0x0103_present = false;
    return 0;
}

bool PDCP_Config::headerCompression_rohc::profiles::profile0x0103_IsPresent() const
{
    return profile0x0103_present;
}

int PDCP_Config::headerCompression_rohc::profiles::profile0x0104_Pack(std::vector<uint8_t> &bits)
{
    if(!profile0x0104_present)
    {
        printf("PDCP_Config::headerCompression_rohc::profiles::profile0x0104_Pack() presence failure\n");
        return -1;
    }
    bits.push_back(profile0x0104_internal_value);
    return 0;
}

int PDCP_Config::headerCompression_rohc::profiles::profile0x0104_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return profile0x0104_Unpack(bits, idx);
}

int PDCP_Config::headerCompression_rohc::profiles::profile0x0104_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    if((idx + 1) > bits.size())
    {
        printf("PDCP_Config::headerCompression_rohc::profiles::profile0x0104_Unpack() index out of bounds\n");
        return -1;
    }
    profile0x0104_internal_value = bits[idx++];
    profile0x0104_present = true;
    return 0;
}

bool PDCP_Config::headerCompression_rohc::profiles::profile0x0104_Value() const
{
    if(profile0x0104_present)
        return profile0x0104_internal_value;
    return false;
}

int PDCP_Config::headerCompression_rohc::profiles::profile0x0104_SetValue(bool value)
{
    profile0x0104_internal_value = value;
    profile0x0104_present = true;
    return 0;
}

std::string PDCP_Config::headerCompression_rohc::profiles::profile0x0104_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "profile0x0104 = " + std::to_string(profile0x0104_internal_value) + "\n";
    return out;
}

std::string PDCP_Config::headerCompression_rohc::profiles::profile0x0104_ToStringNoNewLines() const
{
    std::string out = "profile0x0104=" + std::to_string(profile0x0104_internal_value) + ",";
    return out;
}

int PDCP_Config::headerCompression_rohc::profiles::profile0x0104_Clear()
{
    profile0x0104_present = false;
    return 0;
}

bool PDCP_Config::headerCompression_rohc::profiles::profile0x0104_IsPresent() const
{
    return profile0x0104_present;
}

