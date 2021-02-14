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

#include "RadioResourceConfigCommonSCell_r10.h"

#include <cmath>

int RadioResourceConfigCommonSCell_r10::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator
    bits.push_back(0);

    // Optional indicators
    bits.push_back(ul_Configuration_value.IsPresent());

    // Fields
    {
        if(0 != nonUL_Configuration_value.Pack(bits))
        {
            printf("RadioResourceConfigCommonSCell_r10:: field pack failure\n");
            return -1;
        }
    }
    if(ul_Configuration_value.IsPresent())
    {
        if(0 != ul_Configuration_value.Pack(bits))
        {
            printf("RadioResourceConfigCommonSCell_r10:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int RadioResourceConfigCommonSCell_r10::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int RadioResourceConfigCommonSCell_r10::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("RadioResourceConfigCommonSCell_r10::Unpack() index out of bounds for extension\n");
        return -1;
    }
    idx++;

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("RadioResourceConfigCommonSCell_r10::Unpack() index out of bounds for optional indiator ul_Configuration\n");
        return -1;
    }
    ul_Configuration_value.SetPresence(bits[idx++]);

    // Fields
    {
        if(0 != nonUL_Configuration_value.Unpack(bits, idx))
        {
            printf("RadioResourceConfigCommonSCell_r10:: field unpack failure\n");
            return -1;
        }
    }
    if(ul_Configuration_value.IsPresent())
    {
        if(0 != ul_Configuration_value.Unpack(bits, idx))
        {
            printf("RadioResourceConfigCommonSCell_r10:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string RadioResourceConfigCommonSCell_r10::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "RadioResourceConfigCommonSCell_r10:\n";
    out += nonUL_Configuration_value.ToString(indent+1);
    if(ul_Configuration_value.IsPresent())
        out += ul_Configuration_value.ToString(indent+1);
    return out;
}

std::string RadioResourceConfigCommonSCell_r10::ToStringNoNewLines() const
{
    std::string out = "RadioResourceConfigCommonSCell_r10:";
    out += nonUL_Configuration_value.ToStringNoNewLines();
    if(ul_Configuration_value.IsPresent())
        out += ul_Configuration_value.ToStringNoNewLines();
    return out;
}

int RadioResourceConfigCommonSCell_r10::nonUL_Configuration::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(mbsfn_SubframeConfigList_r10_IsPresent());

    // Fields
    {
        if(0 != dl_Bandwidth_r10_Pack(bits))
        {
            printf("RadioResourceConfigCommonSCell_r10::nonUL_Configuration:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != antennaInfoCommon_r10.Pack(bits))
        {
            printf("RadioResourceConfigCommonSCell_r10::nonUL_Configuration:: field pack failure\n");
            return -1;
        }
    }
    if(mbsfn_SubframeConfigList_r10_IsPresent())
    {
        if(0 != mbsfn_SubframeConfigList_r10.Pack(bits))
        {
            printf("RadioResourceConfigCommonSCell_r10::nonUL_Configuration:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != phich_Config_r10.Pack(bits))
        {
            printf("RadioResourceConfigCommonSCell_r10::nonUL_Configuration:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != pdsch_ConfigCommon_r10.Pack(bits))
        {
            printf("RadioResourceConfigCommonSCell_r10::nonUL_Configuration:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int RadioResourceConfigCommonSCell_r10::nonUL_Configuration::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int RadioResourceConfigCommonSCell_r10::nonUL_Configuration::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("nonUL_Configuration::Unpack() index out of bounds for optional indiator mbsfn_SubframeConfigList_r10\n");
        return -1;
    }
    mbsfn_SubframeConfigList_r10_present = bits[idx++];

    // Fields
    {
        if(0 != dl_Bandwidth_r10_Unpack(bits, idx))
        {
            printf("RadioResourceConfigCommonSCell_r10::nonUL_Configuration:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != antennaInfoCommon_r10.Unpack(bits, idx))
        {
            printf("RadioResourceConfigCommonSCell_r10::nonUL_Configuration:: field unpack failure\n");
            return -1;
        }
    }
    if(mbsfn_SubframeConfigList_r10_present)
    {
        if(0 != mbsfn_SubframeConfigList_r10.Unpack(bits, idx))
        {
            printf("RadioResourceConfigCommonSCell_r10::nonUL_Configuration:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != phich_Config_r10.Unpack(bits, idx))
        {
            printf("RadioResourceConfigCommonSCell_r10::nonUL_Configuration:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != pdsch_ConfigCommon_r10.Unpack(bits, idx))
        {
            printf("RadioResourceConfigCommonSCell_r10::nonUL_Configuration:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string RadioResourceConfigCommonSCell_r10::nonUL_Configuration::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "nonUL_Configuration:\n";
    out += dl_Bandwidth_r10_ToString(indent+1);
    out += antennaInfoCommon_r10_ToString(indent+1);
    if(mbsfn_SubframeConfigList_r10_IsPresent())
        out += mbsfn_SubframeConfigList_r10_ToString(indent+1);
    out += phich_Config_r10_ToString(indent+1);
    out += pdsch_ConfigCommon_r10_ToString(indent+1);
    return out;
}

std::string RadioResourceConfigCommonSCell_r10::nonUL_Configuration::ToStringNoNewLines() const
{
    std::string out = "nonUL_Configuration:";
    out += dl_Bandwidth_r10_ToStringNoNewLines();
    out += antennaInfoCommon_r10_ToStringNoNewLines();
    if(mbsfn_SubframeConfigList_r10_IsPresent())
        out += mbsfn_SubframeConfigList_r10_ToStringNoNewLines();
    out += phich_Config_r10_ToStringNoNewLines();
    out += pdsch_ConfigCommon_r10_ToStringNoNewLines();
    return out;
}

int RadioResourceConfigCommonSCell_r10::nonUL_Configuration::dl_Bandwidth_r10_Pack(std::vector<uint8_t> &bits)
{
    if(!dl_Bandwidth_r10_present)
    {
        printf("RadioResourceConfigCommonSCell_r10::nonUL_Configuration::dl_Bandwidth_r10_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 3;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((dl_Bandwidth_r10_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int RadioResourceConfigCommonSCell_r10::nonUL_Configuration::dl_Bandwidth_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return dl_Bandwidth_r10_Unpack(bits, idx);
}

int RadioResourceConfigCommonSCell_r10::nonUL_Configuration::dl_Bandwidth_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 3;
    if((idx + N_bits) > bits.size())
    {
        printf("RadioResourceConfigCommonSCell_r10::nonUL_Configuration::dl_Bandwidth_r10_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 5)
    {
        printf("RadioResourceConfigCommonSCell_r10::nonUL_Configuration::dl_Bandwidth_r10_Unpack() max failure\n");
        return -1;
    }
    dl_Bandwidth_r10_internal_value = (dl_Bandwidth_r10_Enum)packed_val;
    dl_Bandwidth_r10_present = true;
    return 0;
}

RadioResourceConfigCommonSCell_r10::nonUL_Configuration::dl_Bandwidth_r10_Enum RadioResourceConfigCommonSCell_r10::nonUL_Configuration::dl_Bandwidth_r10_Value() const
{
    if(dl_Bandwidth_r10_present)
        return dl_Bandwidth_r10_internal_value;
    return (RadioResourceConfigCommonSCell_r10::nonUL_Configuration::dl_Bandwidth_r10_Enum)0;
}

int RadioResourceConfigCommonSCell_r10::nonUL_Configuration::dl_Bandwidth_r10_SetValue(dl_Bandwidth_r10_Enum value)
{
    dl_Bandwidth_r10_internal_value = value;
    dl_Bandwidth_r10_present = true;
    return 0;
}

int RadioResourceConfigCommonSCell_r10::nonUL_Configuration::dl_Bandwidth_r10_SetValue(std::string value)
{
    if("n6" == value)
    {
        dl_Bandwidth_r10_internal_value = k_dl_Bandwidth_r10_n6;
        dl_Bandwidth_r10_present = true;
        return 0;
    }
    if("n15" == value)
    {
        dl_Bandwidth_r10_internal_value = k_dl_Bandwidth_r10_n15;
        dl_Bandwidth_r10_present = true;
        return 0;
    }
    if("n25" == value)
    {
        dl_Bandwidth_r10_internal_value = k_dl_Bandwidth_r10_n25;
        dl_Bandwidth_r10_present = true;
        return 0;
    }
    if("n50" == value)
    {
        dl_Bandwidth_r10_internal_value = k_dl_Bandwidth_r10_n50;
        dl_Bandwidth_r10_present = true;
        return 0;
    }
    if("n75" == value)
    {
        dl_Bandwidth_r10_internal_value = k_dl_Bandwidth_r10_n75;
        dl_Bandwidth_r10_present = true;
        return 0;
    }
    if("n100" == value)
    {
        dl_Bandwidth_r10_internal_value = k_dl_Bandwidth_r10_n100;
        dl_Bandwidth_r10_present = true;
        return 0;
    }
    return 1;
}

std::string RadioResourceConfigCommonSCell_r10::nonUL_Configuration::dl_Bandwidth_r10_ValueToString(dl_Bandwidth_r10_Enum value) const
{
    if(k_dl_Bandwidth_r10_n6 == value)
        return "n6";
    if(k_dl_Bandwidth_r10_n15 == value)
        return "n15";
    if(k_dl_Bandwidth_r10_n25 == value)
        return "n25";
    if(k_dl_Bandwidth_r10_n50 == value)
        return "n50";
    if(k_dl_Bandwidth_r10_n75 == value)
        return "n75";
    if(k_dl_Bandwidth_r10_n100 == value)
        return "n100";
    return "";
}

uint64_t RadioResourceConfigCommonSCell_r10::nonUL_Configuration::dl_Bandwidth_r10_NumberOfValues() const
{
    return 6;
}

std::string RadioResourceConfigCommonSCell_r10::nonUL_Configuration::dl_Bandwidth_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "dl_Bandwidth_r10 = " + dl_Bandwidth_r10_ValueToString(dl_Bandwidth_r10_internal_value) + "\n";
    return out;
}

std::string RadioResourceConfigCommonSCell_r10::nonUL_Configuration::dl_Bandwidth_r10_ToStringNoNewLines() const
{
    std::string out = "dl_Bandwidth_r10=" + dl_Bandwidth_r10_ValueToString(dl_Bandwidth_r10_internal_value) + ",";
    return out;
}

int RadioResourceConfigCommonSCell_r10::nonUL_Configuration::dl_Bandwidth_r10_Clear()
{
    dl_Bandwidth_r10_present = false;
    return 0;
}

bool RadioResourceConfigCommonSCell_r10::nonUL_Configuration::dl_Bandwidth_r10_IsPresent() const
{
    return dl_Bandwidth_r10_present;
}

AntennaInfoCommon* RadioResourceConfigCommonSCell_r10::nonUL_Configuration::antennaInfoCommon_r10_Set()
{
    antennaInfoCommon_r10_present = true;
    return &antennaInfoCommon_r10;
}

int RadioResourceConfigCommonSCell_r10::nonUL_Configuration::antennaInfoCommon_r10_Set(AntennaInfoCommon &value)
{
    antennaInfoCommon_r10_present = true;
    antennaInfoCommon_r10 = value;
    return 0;
}

const AntennaInfoCommon& RadioResourceConfigCommonSCell_r10::nonUL_Configuration::antennaInfoCommon_r10_Get() const
{
    return antennaInfoCommon_r10;
}

std::string RadioResourceConfigCommonSCell_r10::nonUL_Configuration::antennaInfoCommon_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "antennaInfoCommon_r10:\n";
    out += antennaInfoCommon_r10.ToString(indent+1);
    return out;
}

std::string RadioResourceConfigCommonSCell_r10::nonUL_Configuration::antennaInfoCommon_r10_ToStringNoNewLines() const
{
    std::string out = "antennaInfoCommon_r10:";
    out += antennaInfoCommon_r10.ToStringNoNewLines();
    return out;
}

int RadioResourceConfigCommonSCell_r10::nonUL_Configuration::antennaInfoCommon_r10_Clear()
{
    antennaInfoCommon_r10_present = false;
    return 0;
}

bool RadioResourceConfigCommonSCell_r10::nonUL_Configuration::antennaInfoCommon_r10_IsPresent() const
{
    return antennaInfoCommon_r10_present;
}

MBSFN_SubframeConfigList* RadioResourceConfigCommonSCell_r10::nonUL_Configuration::mbsfn_SubframeConfigList_r10_Set()
{
    mbsfn_SubframeConfigList_r10_present = true;
    return &mbsfn_SubframeConfigList_r10;
}

int RadioResourceConfigCommonSCell_r10::nonUL_Configuration::mbsfn_SubframeConfigList_r10_Set(MBSFN_SubframeConfigList &value)
{
    mbsfn_SubframeConfigList_r10_present = true;
    mbsfn_SubframeConfigList_r10 = value;
    return 0;
}

const MBSFN_SubframeConfigList& RadioResourceConfigCommonSCell_r10::nonUL_Configuration::mbsfn_SubframeConfigList_r10_Get() const
{
    return mbsfn_SubframeConfigList_r10;
}

std::string RadioResourceConfigCommonSCell_r10::nonUL_Configuration::mbsfn_SubframeConfigList_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "mbsfn_SubframeConfigList_r10:\n";
    out += mbsfn_SubframeConfigList_r10.ToString(indent+1);
    return out;
}

std::string RadioResourceConfigCommonSCell_r10::nonUL_Configuration::mbsfn_SubframeConfigList_r10_ToStringNoNewLines() const
{
    std::string out = "mbsfn_SubframeConfigList_r10:";
    out += mbsfn_SubframeConfigList_r10.ToStringNoNewLines();
    return out;
}

int RadioResourceConfigCommonSCell_r10::nonUL_Configuration::mbsfn_SubframeConfigList_r10_Clear()
{
    mbsfn_SubframeConfigList_r10_present = false;
    return 0;
}

bool RadioResourceConfigCommonSCell_r10::nonUL_Configuration::mbsfn_SubframeConfigList_r10_IsPresent() const
{
    return mbsfn_SubframeConfigList_r10_present;
}

PHICH_Config* RadioResourceConfigCommonSCell_r10::nonUL_Configuration::phich_Config_r10_Set()
{
    phich_Config_r10_present = true;
    return &phich_Config_r10;
}

int RadioResourceConfigCommonSCell_r10::nonUL_Configuration::phich_Config_r10_Set(PHICH_Config &value)
{
    phich_Config_r10_present = true;
    phich_Config_r10 = value;
    return 0;
}

const PHICH_Config& RadioResourceConfigCommonSCell_r10::nonUL_Configuration::phich_Config_r10_Get() const
{
    return phich_Config_r10;
}

std::string RadioResourceConfigCommonSCell_r10::nonUL_Configuration::phich_Config_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "phich_Config_r10:\n";
    out += phich_Config_r10.ToString(indent+1);
    return out;
}

std::string RadioResourceConfigCommonSCell_r10::nonUL_Configuration::phich_Config_r10_ToStringNoNewLines() const
{
    std::string out = "phich_Config_r10:";
    out += phich_Config_r10.ToStringNoNewLines();
    return out;
}

int RadioResourceConfigCommonSCell_r10::nonUL_Configuration::phich_Config_r10_Clear()
{
    phich_Config_r10_present = false;
    return 0;
}

bool RadioResourceConfigCommonSCell_r10::nonUL_Configuration::phich_Config_r10_IsPresent() const
{
    return phich_Config_r10_present;
}

PDSCH_ConfigCommon* RadioResourceConfigCommonSCell_r10::nonUL_Configuration::pdsch_ConfigCommon_r10_Set()
{
    pdsch_ConfigCommon_r10_present = true;
    return &pdsch_ConfigCommon_r10;
}

int RadioResourceConfigCommonSCell_r10::nonUL_Configuration::pdsch_ConfigCommon_r10_Set(PDSCH_ConfigCommon &value)
{
    pdsch_ConfigCommon_r10_present = true;
    pdsch_ConfigCommon_r10 = value;
    return 0;
}

const PDSCH_ConfigCommon& RadioResourceConfigCommonSCell_r10::nonUL_Configuration::pdsch_ConfigCommon_r10_Get() const
{
    return pdsch_ConfigCommon_r10;
}

std::string RadioResourceConfigCommonSCell_r10::nonUL_Configuration::pdsch_ConfigCommon_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "pdsch_ConfigCommon_r10:\n";
    out += pdsch_ConfigCommon_r10.ToString(indent+1);
    return out;
}

std::string RadioResourceConfigCommonSCell_r10::nonUL_Configuration::pdsch_ConfigCommon_r10_ToStringNoNewLines() const
{
    std::string out = "pdsch_ConfigCommon_r10:";
    out += pdsch_ConfigCommon_r10.ToStringNoNewLines();
    return out;
}

int RadioResourceConfigCommonSCell_r10::nonUL_Configuration::pdsch_ConfigCommon_r10_Clear()
{
    pdsch_ConfigCommon_r10_present = false;
    return 0;
}

bool RadioResourceConfigCommonSCell_r10::nonUL_Configuration::pdsch_ConfigCommon_r10_IsPresent() const
{
    return pdsch_ConfigCommon_r10_present;
}

int RadioResourceConfigCommonSCell_r10::ul_Configuration::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(p_Max_r10_IsPresent());
    bits.push_back(prach_Config_IsPresent());

    // Fields
    {
        if(0 != ul_FreqInfo_r10_value.Pack(bits))
        {
            printf("RadioResourceConfigCommonSCell_r10::ul_Configuration:: field pack failure\n");
            return -1;
        }
    }
    if(p_Max_r10_IsPresent())
    {
        if(0 != p_Max_r10.Pack(bits))
        {
            printf("RadioResourceConfigCommonSCell_r10::ul_Configuration:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != uplinkPowerControlCommon_r10.Pack(bits))
        {
            printf("RadioResourceConfigCommonSCell_r10::ul_Configuration:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != soundingRS_UL_ConfigCommon_r10.Pack(bits))
        {
            printf("RadioResourceConfigCommonSCell_r10::ul_Configuration:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != ul_CyclicPrefixLength_r10.Pack(bits))
        {
            printf("RadioResourceConfigCommonSCell_r10::ul_Configuration:: field pack failure\n");
            return -1;
        }
    }
    if(prach_Config_IsPresent())
    {
        if(0 != prach_Config.Pack(bits))
        {
            printf("RadioResourceConfigCommonSCell_r10::ul_Configuration:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != pusch_ConfigCommon_r10.Pack(bits))
        {
            printf("RadioResourceConfigCommonSCell_r10::ul_Configuration:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int RadioResourceConfigCommonSCell_r10::ul_Configuration::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int RadioResourceConfigCommonSCell_r10::ul_Configuration::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("ul_Configuration::Unpack() index out of bounds for optional indiator p_Max_r10\n");
        return -1;
    }
    p_Max_r10_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("ul_Configuration::Unpack() index out of bounds for optional indiator prach_Config\n");
        return -1;
    }
    prach_Config_present = bits[idx++];

    // Fields
    {
        if(0 != ul_FreqInfo_r10_value.Unpack(bits, idx))
        {
            printf("RadioResourceConfigCommonSCell_r10::ul_Configuration:: field unpack failure\n");
            return -1;
        }
    }
    if(p_Max_r10_present)
    {
        if(0 != p_Max_r10.Unpack(bits, idx))
        {
            printf("RadioResourceConfigCommonSCell_r10::ul_Configuration:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != uplinkPowerControlCommon_r10.Unpack(bits, idx))
        {
            printf("RadioResourceConfigCommonSCell_r10::ul_Configuration:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != soundingRS_UL_ConfigCommon_r10.Unpack(bits, idx))
        {
            printf("RadioResourceConfigCommonSCell_r10::ul_Configuration:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != ul_CyclicPrefixLength_r10.Unpack(bits, idx))
        {
            printf("RadioResourceConfigCommonSCell_r10::ul_Configuration:: field unpack failure\n");
            return -1;
        }
    }
    if(prach_Config_present)
    {
        if(0 != prach_Config.Unpack(bits, idx))
        {
            printf("RadioResourceConfigCommonSCell_r10::ul_Configuration:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != pusch_ConfigCommon_r10.Unpack(bits, idx))
        {
            printf("RadioResourceConfigCommonSCell_r10::ul_Configuration:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string RadioResourceConfigCommonSCell_r10::ul_Configuration::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ul_Configuration:\n";
    out += ul_FreqInfo_r10_value.ToString(indent+1);
    if(p_Max_r10_IsPresent())
        out += p_Max_r10_ToString(indent+1);
    out += uplinkPowerControlCommon_r10_ToString(indent+1);
    out += soundingRS_UL_ConfigCommon_r10_ToString(indent+1);
    out += ul_CyclicPrefixLength_r10_ToString(indent+1);
    if(prach_Config_IsPresent())
        out += prach_Config_ToString(indent+1);
    out += pusch_ConfigCommon_r10_ToString(indent+1);
    return out;
}

std::string RadioResourceConfigCommonSCell_r10::ul_Configuration::ToStringNoNewLines() const
{
    std::string out = "ul_Configuration:";
    out += ul_FreqInfo_r10_value.ToStringNoNewLines();
    if(p_Max_r10_IsPresent())
        out += p_Max_r10_ToStringNoNewLines();
    out += uplinkPowerControlCommon_r10_ToStringNoNewLines();
    out += soundingRS_UL_ConfigCommon_r10_ToStringNoNewLines();
    out += ul_CyclicPrefixLength_r10_ToStringNoNewLines();
    if(prach_Config_IsPresent())
        out += prach_Config_ToStringNoNewLines();
    out += pusch_ConfigCommon_r10_ToStringNoNewLines();
    return out;
}

int RadioResourceConfigCommonSCell_r10::ul_Configuration::Set()
{
    present = true;
    return 0;
}

int RadioResourceConfigCommonSCell_r10::ul_Configuration::SetPresence(bool is_present)
{
    present = is_present;
    return 0;
}

int RadioResourceConfigCommonSCell_r10::ul_Configuration::Clear()
{
    present = false;
    return 0;
}

bool RadioResourceConfigCommonSCell_r10::ul_Configuration::IsPresent() const
{
    return present;
}

int RadioResourceConfigCommonSCell_r10::ul_Configuration::ul_FreqInfo_r10::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(ul_CarrierFreq_r10_IsPresent());
    bits.push_back(ul_Bandwidth_r10_IsPresent());

    // Fields
    if(ul_CarrierFreq_r10_IsPresent())
    {
        if(0 != ul_CarrierFreq_r10.Pack(bits))
        {
            printf("RadioResourceConfigCommonSCell_r10::ul_Configuration::ul_FreqInfo_r10:: field pack failure\n");
            return -1;
        }
    }
    if(ul_Bandwidth_r10_IsPresent())
    {
        if(0 != ul_Bandwidth_r10_Pack(bits))
        {
            printf("RadioResourceConfigCommonSCell_r10::ul_Configuration::ul_FreqInfo_r10:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != additionalSpectrumEmission_r10.Pack(bits))
        {
            printf("RadioResourceConfigCommonSCell_r10::ul_Configuration::ul_FreqInfo_r10:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int RadioResourceConfigCommonSCell_r10::ul_Configuration::ul_FreqInfo_r10::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int RadioResourceConfigCommonSCell_r10::ul_Configuration::ul_FreqInfo_r10::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("ul_FreqInfo_r10::Unpack() index out of bounds for optional indiator ul_CarrierFreq_r10\n");
        return -1;
    }
    ul_CarrierFreq_r10_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("ul_FreqInfo_r10::Unpack() index out of bounds for optional indiator ul_Bandwidth_r10\n");
        return -1;
    }
    ul_Bandwidth_r10_present = bits[idx++];

    // Fields
    if(ul_CarrierFreq_r10_present)
    {
        if(0 != ul_CarrierFreq_r10.Unpack(bits, idx))
        {
            printf("RadioResourceConfigCommonSCell_r10::ul_Configuration::ul_FreqInfo_r10:: field unpack failure\n");
            return -1;
        }
    }
    if(ul_Bandwidth_r10_present)
    {
        if(0 != ul_Bandwidth_r10_Unpack(bits, idx))
        {
            printf("RadioResourceConfigCommonSCell_r10::ul_Configuration::ul_FreqInfo_r10:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != additionalSpectrumEmission_r10.Unpack(bits, idx))
        {
            printf("RadioResourceConfigCommonSCell_r10::ul_Configuration::ul_FreqInfo_r10:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string RadioResourceConfigCommonSCell_r10::ul_Configuration::ul_FreqInfo_r10::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ul_FreqInfo_r10:\n";
    if(ul_CarrierFreq_r10_IsPresent())
        out += ul_CarrierFreq_r10_ToString(indent+1);
    if(ul_Bandwidth_r10_IsPresent())
        out += ul_Bandwidth_r10_ToString(indent+1);
    out += additionalSpectrumEmission_r10_ToString(indent+1);
    return out;
}

std::string RadioResourceConfigCommonSCell_r10::ul_Configuration::ul_FreqInfo_r10::ToStringNoNewLines() const
{
    std::string out = "ul_FreqInfo_r10:";
    if(ul_CarrierFreq_r10_IsPresent())
        out += ul_CarrierFreq_r10_ToStringNoNewLines();
    if(ul_Bandwidth_r10_IsPresent())
        out += ul_Bandwidth_r10_ToStringNoNewLines();
    out += additionalSpectrumEmission_r10_ToStringNoNewLines();
    return out;
}

ARFCN_ValueEUTRA* RadioResourceConfigCommonSCell_r10::ul_Configuration::ul_FreqInfo_r10::ul_CarrierFreq_r10_Set()
{
    ul_CarrierFreq_r10_present = true;
    return &ul_CarrierFreq_r10;
}

int RadioResourceConfigCommonSCell_r10::ul_Configuration::ul_FreqInfo_r10::ul_CarrierFreq_r10_Set(ARFCN_ValueEUTRA &value)
{
    ul_CarrierFreq_r10_present = true;
    ul_CarrierFreq_r10 = value;
    return 0;
}

const ARFCN_ValueEUTRA& RadioResourceConfigCommonSCell_r10::ul_Configuration::ul_FreqInfo_r10::ul_CarrierFreq_r10_Get() const
{
    return ul_CarrierFreq_r10;
}

std::string RadioResourceConfigCommonSCell_r10::ul_Configuration::ul_FreqInfo_r10::ul_CarrierFreq_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ul_CarrierFreq_r10:\n";
    out += ul_CarrierFreq_r10.ToString(indent+1);
    return out;
}

std::string RadioResourceConfigCommonSCell_r10::ul_Configuration::ul_FreqInfo_r10::ul_CarrierFreq_r10_ToStringNoNewLines() const
{
    std::string out = "ul_CarrierFreq_r10:";
    out += ul_CarrierFreq_r10.ToStringNoNewLines();
    return out;
}

int RadioResourceConfigCommonSCell_r10::ul_Configuration::ul_FreqInfo_r10::ul_CarrierFreq_r10_Clear()
{
    ul_CarrierFreq_r10_present = false;
    return 0;
}

bool RadioResourceConfigCommonSCell_r10::ul_Configuration::ul_FreqInfo_r10::ul_CarrierFreq_r10_IsPresent() const
{
    return ul_CarrierFreq_r10_present;
}

int RadioResourceConfigCommonSCell_r10::ul_Configuration::ul_FreqInfo_r10::ul_Bandwidth_r10_Pack(std::vector<uint8_t> &bits)
{
    uint32_t N_bits = 3;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((ul_Bandwidth_r10_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int RadioResourceConfigCommonSCell_r10::ul_Configuration::ul_FreqInfo_r10::ul_Bandwidth_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return ul_Bandwidth_r10_Unpack(bits, idx);
}

int RadioResourceConfigCommonSCell_r10::ul_Configuration::ul_FreqInfo_r10::ul_Bandwidth_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 3;
    if((idx + N_bits) > bits.size())
    {
        printf("RadioResourceConfigCommonSCell_r10::ul_Configuration::ul_FreqInfo_r10::ul_Bandwidth_r10_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 5)
    {
        printf("RadioResourceConfigCommonSCell_r10::ul_Configuration::ul_FreqInfo_r10::ul_Bandwidth_r10_Unpack() max failure\n");
        return -1;
    }
    ul_Bandwidth_r10_internal_value = (ul_Bandwidth_r10_Enum)packed_val;
    ul_Bandwidth_r10_present = true;
    return 0;
}

RadioResourceConfigCommonSCell_r10::ul_Configuration::ul_FreqInfo_r10::ul_Bandwidth_r10_Enum RadioResourceConfigCommonSCell_r10::ul_Configuration::ul_FreqInfo_r10::ul_Bandwidth_r10_Value() const
{
    if(ul_Bandwidth_r10_present)
        return ul_Bandwidth_r10_internal_value;
    return (RadioResourceConfigCommonSCell_r10::ul_Configuration::ul_FreqInfo_r10::ul_Bandwidth_r10_Enum)0;
}

int RadioResourceConfigCommonSCell_r10::ul_Configuration::ul_FreqInfo_r10::ul_Bandwidth_r10_SetValue(ul_Bandwidth_r10_Enum value)
{
    ul_Bandwidth_r10_internal_value = value;
    ul_Bandwidth_r10_present = true;
    return 0;
}

int RadioResourceConfigCommonSCell_r10::ul_Configuration::ul_FreqInfo_r10::ul_Bandwidth_r10_SetValue(std::string value)
{
    if("n6" == value)
    {
        ul_Bandwidth_r10_internal_value = k_ul_Bandwidth_r10_n6;
        ul_Bandwidth_r10_present = true;
        return 0;
    }
    if("n15" == value)
    {
        ul_Bandwidth_r10_internal_value = k_ul_Bandwidth_r10_n15;
        ul_Bandwidth_r10_present = true;
        return 0;
    }
    if("n25" == value)
    {
        ul_Bandwidth_r10_internal_value = k_ul_Bandwidth_r10_n25;
        ul_Bandwidth_r10_present = true;
        return 0;
    }
    if("n50" == value)
    {
        ul_Bandwidth_r10_internal_value = k_ul_Bandwidth_r10_n50;
        ul_Bandwidth_r10_present = true;
        return 0;
    }
    if("n75" == value)
    {
        ul_Bandwidth_r10_internal_value = k_ul_Bandwidth_r10_n75;
        ul_Bandwidth_r10_present = true;
        return 0;
    }
    if("n100" == value)
    {
        ul_Bandwidth_r10_internal_value = k_ul_Bandwidth_r10_n100;
        ul_Bandwidth_r10_present = true;
        return 0;
    }
    return 1;
}

std::string RadioResourceConfigCommonSCell_r10::ul_Configuration::ul_FreqInfo_r10::ul_Bandwidth_r10_ValueToString(ul_Bandwidth_r10_Enum value) const
{
    if(k_ul_Bandwidth_r10_n6 == value)
        return "n6";
    if(k_ul_Bandwidth_r10_n15 == value)
        return "n15";
    if(k_ul_Bandwidth_r10_n25 == value)
        return "n25";
    if(k_ul_Bandwidth_r10_n50 == value)
        return "n50";
    if(k_ul_Bandwidth_r10_n75 == value)
        return "n75";
    if(k_ul_Bandwidth_r10_n100 == value)
        return "n100";
    return "";
}

uint64_t RadioResourceConfigCommonSCell_r10::ul_Configuration::ul_FreqInfo_r10::ul_Bandwidth_r10_NumberOfValues() const
{
    return 6;
}

std::string RadioResourceConfigCommonSCell_r10::ul_Configuration::ul_FreqInfo_r10::ul_Bandwidth_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ul_Bandwidth_r10 = " + ul_Bandwidth_r10_ValueToString(ul_Bandwidth_r10_internal_value) + "\n";
    return out;
}

std::string RadioResourceConfigCommonSCell_r10::ul_Configuration::ul_FreqInfo_r10::ul_Bandwidth_r10_ToStringNoNewLines() const
{
    std::string out = "ul_Bandwidth_r10=" + ul_Bandwidth_r10_ValueToString(ul_Bandwidth_r10_internal_value) + ",";
    return out;
}

int RadioResourceConfigCommonSCell_r10::ul_Configuration::ul_FreqInfo_r10::ul_Bandwidth_r10_Clear()
{
    ul_Bandwidth_r10_present = false;
    return 0;
}

bool RadioResourceConfigCommonSCell_r10::ul_Configuration::ul_FreqInfo_r10::ul_Bandwidth_r10_IsPresent() const
{
    return ul_Bandwidth_r10_present;
}

AdditionalSpectrumEmission* RadioResourceConfigCommonSCell_r10::ul_Configuration::ul_FreqInfo_r10::additionalSpectrumEmission_r10_Set()
{
    additionalSpectrumEmission_r10_present = true;
    return &additionalSpectrumEmission_r10;
}

int RadioResourceConfigCommonSCell_r10::ul_Configuration::ul_FreqInfo_r10::additionalSpectrumEmission_r10_Set(AdditionalSpectrumEmission &value)
{
    additionalSpectrumEmission_r10_present = true;
    additionalSpectrumEmission_r10 = value;
    return 0;
}

const AdditionalSpectrumEmission& RadioResourceConfigCommonSCell_r10::ul_Configuration::ul_FreqInfo_r10::additionalSpectrumEmission_r10_Get() const
{
    return additionalSpectrumEmission_r10;
}

std::string RadioResourceConfigCommonSCell_r10::ul_Configuration::ul_FreqInfo_r10::additionalSpectrumEmission_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "additionalSpectrumEmission_r10:\n";
    out += additionalSpectrumEmission_r10.ToString(indent+1);
    return out;
}

std::string RadioResourceConfigCommonSCell_r10::ul_Configuration::ul_FreqInfo_r10::additionalSpectrumEmission_r10_ToStringNoNewLines() const
{
    std::string out = "additionalSpectrumEmission_r10:";
    out += additionalSpectrumEmission_r10.ToStringNoNewLines();
    return out;
}

int RadioResourceConfigCommonSCell_r10::ul_Configuration::ul_FreqInfo_r10::additionalSpectrumEmission_r10_Clear()
{
    additionalSpectrumEmission_r10_present = false;
    return 0;
}

bool RadioResourceConfigCommonSCell_r10::ul_Configuration::ul_FreqInfo_r10::additionalSpectrumEmission_r10_IsPresent() const
{
    return additionalSpectrumEmission_r10_present;
}

P_Max* RadioResourceConfigCommonSCell_r10::ul_Configuration::p_Max_r10_Set()
{
    p_Max_r10_present = true;
    return &p_Max_r10;
}

int RadioResourceConfigCommonSCell_r10::ul_Configuration::p_Max_r10_Set(P_Max &value)
{
    p_Max_r10_present = true;
    p_Max_r10 = value;
    return 0;
}

const P_Max& RadioResourceConfigCommonSCell_r10::ul_Configuration::p_Max_r10_Get() const
{
    return p_Max_r10;
}

std::string RadioResourceConfigCommonSCell_r10::ul_Configuration::p_Max_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "p_Max_r10:\n";
    out += p_Max_r10.ToString(indent+1);
    return out;
}

std::string RadioResourceConfigCommonSCell_r10::ul_Configuration::p_Max_r10_ToStringNoNewLines() const
{
    std::string out = "p_Max_r10:";
    out += p_Max_r10.ToStringNoNewLines();
    return out;
}

int RadioResourceConfigCommonSCell_r10::ul_Configuration::p_Max_r10_Clear()
{
    p_Max_r10_present = false;
    return 0;
}

bool RadioResourceConfigCommonSCell_r10::ul_Configuration::p_Max_r10_IsPresent() const
{
    return p_Max_r10_present;
}

UplinkPowerControlCommonSCell_r10* RadioResourceConfigCommonSCell_r10::ul_Configuration::uplinkPowerControlCommon_r10_Set()
{
    uplinkPowerControlCommon_r10_present = true;
    return &uplinkPowerControlCommon_r10;
}

int RadioResourceConfigCommonSCell_r10::ul_Configuration::uplinkPowerControlCommon_r10_Set(UplinkPowerControlCommonSCell_r10 &value)
{
    uplinkPowerControlCommon_r10_present = true;
    uplinkPowerControlCommon_r10 = value;
    return 0;
}

const UplinkPowerControlCommonSCell_r10& RadioResourceConfigCommonSCell_r10::ul_Configuration::uplinkPowerControlCommon_r10_Get() const
{
    return uplinkPowerControlCommon_r10;
}

std::string RadioResourceConfigCommonSCell_r10::ul_Configuration::uplinkPowerControlCommon_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "uplinkPowerControlCommon_r10:\n";
    out += uplinkPowerControlCommon_r10.ToString(indent+1);
    return out;
}

std::string RadioResourceConfigCommonSCell_r10::ul_Configuration::uplinkPowerControlCommon_r10_ToStringNoNewLines() const
{
    std::string out = "uplinkPowerControlCommon_r10:";
    out += uplinkPowerControlCommon_r10.ToStringNoNewLines();
    return out;
}

int RadioResourceConfigCommonSCell_r10::ul_Configuration::uplinkPowerControlCommon_r10_Clear()
{
    uplinkPowerControlCommon_r10_present = false;
    return 0;
}

bool RadioResourceConfigCommonSCell_r10::ul_Configuration::uplinkPowerControlCommon_r10_IsPresent() const
{
    return uplinkPowerControlCommon_r10_present;
}

SoundingRS_UL_ConfigCommon* RadioResourceConfigCommonSCell_r10::ul_Configuration::soundingRS_UL_ConfigCommon_r10_Set()
{
    soundingRS_UL_ConfigCommon_r10_present = true;
    return &soundingRS_UL_ConfigCommon_r10;
}

int RadioResourceConfigCommonSCell_r10::ul_Configuration::soundingRS_UL_ConfigCommon_r10_Set(SoundingRS_UL_ConfigCommon &value)
{
    soundingRS_UL_ConfigCommon_r10_present = true;
    soundingRS_UL_ConfigCommon_r10 = value;
    return 0;
}

const SoundingRS_UL_ConfigCommon& RadioResourceConfigCommonSCell_r10::ul_Configuration::soundingRS_UL_ConfigCommon_r10_Get() const
{
    return soundingRS_UL_ConfigCommon_r10;
}

std::string RadioResourceConfigCommonSCell_r10::ul_Configuration::soundingRS_UL_ConfigCommon_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "soundingRS_UL_ConfigCommon_r10:\n";
    out += soundingRS_UL_ConfigCommon_r10.ToString(indent+1);
    return out;
}

std::string RadioResourceConfigCommonSCell_r10::ul_Configuration::soundingRS_UL_ConfigCommon_r10_ToStringNoNewLines() const
{
    std::string out = "soundingRS_UL_ConfigCommon_r10:";
    out += soundingRS_UL_ConfigCommon_r10.ToStringNoNewLines();
    return out;
}

int RadioResourceConfigCommonSCell_r10::ul_Configuration::soundingRS_UL_ConfigCommon_r10_Clear()
{
    soundingRS_UL_ConfigCommon_r10_present = false;
    return 0;
}

bool RadioResourceConfigCommonSCell_r10::ul_Configuration::soundingRS_UL_ConfigCommon_r10_IsPresent() const
{
    return soundingRS_UL_ConfigCommon_r10_present;
}

UL_CyclicPrefixLength* RadioResourceConfigCommonSCell_r10::ul_Configuration::ul_CyclicPrefixLength_r10_Set()
{
    ul_CyclicPrefixLength_r10_present = true;
    return &ul_CyclicPrefixLength_r10;
}

int RadioResourceConfigCommonSCell_r10::ul_Configuration::ul_CyclicPrefixLength_r10_Set(UL_CyclicPrefixLength &value)
{
    ul_CyclicPrefixLength_r10_present = true;
    ul_CyclicPrefixLength_r10 = value;
    return 0;
}

const UL_CyclicPrefixLength& RadioResourceConfigCommonSCell_r10::ul_Configuration::ul_CyclicPrefixLength_r10_Get() const
{
    return ul_CyclicPrefixLength_r10;
}

std::string RadioResourceConfigCommonSCell_r10::ul_Configuration::ul_CyclicPrefixLength_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ul_CyclicPrefixLength_r10:\n";
    out += ul_CyclicPrefixLength_r10.ToString(indent+1);
    return out;
}

std::string RadioResourceConfigCommonSCell_r10::ul_Configuration::ul_CyclicPrefixLength_r10_ToStringNoNewLines() const
{
    std::string out = "ul_CyclicPrefixLength_r10:";
    out += ul_CyclicPrefixLength_r10.ToStringNoNewLines();
    return out;
}

int RadioResourceConfigCommonSCell_r10::ul_Configuration::ul_CyclicPrefixLength_r10_Clear()
{
    ul_CyclicPrefixLength_r10_present = false;
    return 0;
}

bool RadioResourceConfigCommonSCell_r10::ul_Configuration::ul_CyclicPrefixLength_r10_IsPresent() const
{
    return ul_CyclicPrefixLength_r10_present;
}

PRACH_ConfigSCell_r10* RadioResourceConfigCommonSCell_r10::ul_Configuration::prach_Config_Set()
{
    prach_Config_present = true;
    return &prach_Config;
}

int RadioResourceConfigCommonSCell_r10::ul_Configuration::prach_Config_Set(PRACH_ConfigSCell_r10 &value)
{
    prach_Config_present = true;
    prach_Config = value;
    return 0;
}

const PRACH_ConfigSCell_r10& RadioResourceConfigCommonSCell_r10::ul_Configuration::prach_Config_Get() const
{
    return prach_Config;
}

std::string RadioResourceConfigCommonSCell_r10::ul_Configuration::prach_Config_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "prach_Config:\n";
    out += prach_Config.ToString(indent+1);
    return out;
}

std::string RadioResourceConfigCommonSCell_r10::ul_Configuration::prach_Config_ToStringNoNewLines() const
{
    std::string out = "prach_Config:";
    out += prach_Config.ToStringNoNewLines();
    return out;
}

int RadioResourceConfigCommonSCell_r10::ul_Configuration::prach_Config_Clear()
{
    prach_Config_present = false;
    return 0;
}

bool RadioResourceConfigCommonSCell_r10::ul_Configuration::prach_Config_IsPresent() const
{
    return prach_Config_present;
}

PUSCH_ConfigCommon* RadioResourceConfigCommonSCell_r10::ul_Configuration::pusch_ConfigCommon_r10_Set()
{
    pusch_ConfigCommon_r10_present = true;
    return &pusch_ConfigCommon_r10;
}

int RadioResourceConfigCommonSCell_r10::ul_Configuration::pusch_ConfigCommon_r10_Set(PUSCH_ConfigCommon &value)
{
    pusch_ConfigCommon_r10_present = true;
    pusch_ConfigCommon_r10 = value;
    return 0;
}

const PUSCH_ConfigCommon& RadioResourceConfigCommonSCell_r10::ul_Configuration::pusch_ConfigCommon_r10_Get() const
{
    return pusch_ConfigCommon_r10;
}

std::string RadioResourceConfigCommonSCell_r10::ul_Configuration::pusch_ConfigCommon_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "pusch_ConfigCommon_r10:\n";
    out += pusch_ConfigCommon_r10.ToString(indent+1);
    return out;
}

std::string RadioResourceConfigCommonSCell_r10::ul_Configuration::pusch_ConfigCommon_r10_ToStringNoNewLines() const
{
    std::string out = "pusch_ConfigCommon_r10:";
    out += pusch_ConfigCommon_r10.ToStringNoNewLines();
    return out;
}

int RadioResourceConfigCommonSCell_r10::ul_Configuration::pusch_ConfigCommon_r10_Clear()
{
    pusch_ConfigCommon_r10_present = false;
    return 0;
}

bool RadioResourceConfigCommonSCell_r10::ul_Configuration::pusch_ConfigCommon_r10_IsPresent() const
{
    return pusch_ConfigCommon_r10_present;
}

