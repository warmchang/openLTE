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

#include "PhysicalConfigDedicatedSCell_r10.h"

#include <cmath>

int PhysicalConfigDedicatedSCell_r10::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator
    bits.push_back(0);

    // Optional indicators
    bits.push_back(nonUL_Configuration_value.IsPresent());
    bits.push_back(ul_Configuration_IsPresent());

    // Fields
    if(nonUL_Configuration_value.IsPresent())
    {
        if(0 != nonUL_Configuration_value.Pack(bits))
        {
            printf("PhysicalConfigDedicatedSCell_r10:: field pack failure\n");
            return -1;
        }
    }
    if(ul_Configuration_IsPresent())
    {
        if(0 != ul_Configuration_Pack(bits))
        {
            printf("PhysicalConfigDedicatedSCell_r10:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int PhysicalConfigDedicatedSCell_r10::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int PhysicalConfigDedicatedSCell_r10::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("PhysicalConfigDedicatedSCell_r10::Unpack() index out of bounds for extension\n");
        return -1;
    }
    idx++;

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("PhysicalConfigDedicatedSCell_r10::Unpack() index out of bounds for optional indiator nonUL_Configuration\n");
        return -1;
    }
    nonUL_Configuration_value.SetPresence(bits[idx++]);
    if((idx + 1) > bits.size())
    {
        printf("PhysicalConfigDedicatedSCell_r10::Unpack() index out of bounds for optional indiator ul_Configuration\n");
        return -1;
    }
    ul_Configuration_present = bits[idx++];

    // Fields
    if(nonUL_Configuration_value.IsPresent())
    {
        if(0 != nonUL_Configuration_value.Unpack(bits, idx))
        {
            printf("PhysicalConfigDedicatedSCell_r10:: field unpack failure\n");
            return -1;
        }
    }
    if(ul_Configuration_present)
    {
        if(0 != ul_Configuration_Unpack(bits, idx))
        {
            printf("PhysicalConfigDedicatedSCell_r10:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string PhysicalConfigDedicatedSCell_r10::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "PhysicalConfigDedicatedSCell_r10:\n";
    if(nonUL_Configuration_value.IsPresent())
        out += nonUL_Configuration_value.ToString(indent+1);
    if(ul_Configuration_IsPresent())
        out += ul_Configuration_ToString(indent+1);
    return out;
}

std::string PhysicalConfigDedicatedSCell_r10::ToStringNoNewLines() const
{
    std::string out = "PhysicalConfigDedicatedSCell_r10:";
    if(nonUL_Configuration_value.IsPresent())
        out += nonUL_Configuration_value.ToStringNoNewLines();
    if(ul_Configuration_IsPresent())
        out += ul_Configuration_ToStringNoNewLines();
    return out;
}

int PhysicalConfigDedicatedSCell_r10::nonUL_Configuration::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(antennaInfo_r10_IsPresent());
    bits.push_back(crossCarrierSchedulingConfig_r10_IsPresent());
    bits.push_back(csi_RS_Config_r10_IsPresent());
    bits.push_back(pdsch_ConfigDedicated_r10_IsPresent());

    // Fields
    if(antennaInfo_r10_IsPresent())
    {
        if(0 != antennaInfo_r10.Pack(bits))
        {
            printf("PhysicalConfigDedicatedSCell_r10::nonUL_Configuration:: field pack failure\n");
            return -1;
        }
    }
    if(crossCarrierSchedulingConfig_r10_IsPresent())
    {
        if(0 != crossCarrierSchedulingConfig_r10.Pack(bits))
        {
            printf("PhysicalConfigDedicatedSCell_r10::nonUL_Configuration:: field pack failure\n");
            return -1;
        }
    }
    if(csi_RS_Config_r10_IsPresent())
    {
        if(0 != csi_RS_Config_r10.Pack(bits))
        {
            printf("PhysicalConfigDedicatedSCell_r10::nonUL_Configuration:: field pack failure\n");
            return -1;
        }
    }
    if(pdsch_ConfigDedicated_r10_IsPresent())
    {
        if(0 != pdsch_ConfigDedicated_r10.Pack(bits))
        {
            printf("PhysicalConfigDedicatedSCell_r10::nonUL_Configuration:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int PhysicalConfigDedicatedSCell_r10::nonUL_Configuration::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int PhysicalConfigDedicatedSCell_r10::nonUL_Configuration::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("nonUL_Configuration::Unpack() index out of bounds for optional indiator antennaInfo_r10\n");
        return -1;
    }
    antennaInfo_r10_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("nonUL_Configuration::Unpack() index out of bounds for optional indiator crossCarrierSchedulingConfig_r10\n");
        return -1;
    }
    crossCarrierSchedulingConfig_r10_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("nonUL_Configuration::Unpack() index out of bounds for optional indiator csi_RS_Config_r10\n");
        return -1;
    }
    csi_RS_Config_r10_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("nonUL_Configuration::Unpack() index out of bounds for optional indiator pdsch_ConfigDedicated_r10\n");
        return -1;
    }
    pdsch_ConfigDedicated_r10_present = bits[idx++];

    // Fields
    if(antennaInfo_r10_present)
    {
        if(0 != antennaInfo_r10.Unpack(bits, idx))
        {
            printf("PhysicalConfigDedicatedSCell_r10::nonUL_Configuration:: field unpack failure\n");
            return -1;
        }
    }
    if(crossCarrierSchedulingConfig_r10_present)
    {
        if(0 != crossCarrierSchedulingConfig_r10.Unpack(bits, idx))
        {
            printf("PhysicalConfigDedicatedSCell_r10::nonUL_Configuration:: field unpack failure\n");
            return -1;
        }
    }
    if(csi_RS_Config_r10_present)
    {
        if(0 != csi_RS_Config_r10.Unpack(bits, idx))
        {
            printf("PhysicalConfigDedicatedSCell_r10::nonUL_Configuration:: field unpack failure\n");
            return -1;
        }
    }
    if(pdsch_ConfigDedicated_r10_present)
    {
        if(0 != pdsch_ConfigDedicated_r10.Unpack(bits, idx))
        {
            printf("PhysicalConfigDedicatedSCell_r10::nonUL_Configuration:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string PhysicalConfigDedicatedSCell_r10::nonUL_Configuration::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "nonUL_Configuration:\n";
    if(antennaInfo_r10_IsPresent())
        out += antennaInfo_r10_ToString(indent+1);
    if(crossCarrierSchedulingConfig_r10_IsPresent())
        out += crossCarrierSchedulingConfig_r10_ToString(indent+1);
    if(csi_RS_Config_r10_IsPresent())
        out += csi_RS_Config_r10_ToString(indent+1);
    if(pdsch_ConfigDedicated_r10_IsPresent())
        out += pdsch_ConfigDedicated_r10_ToString(indent+1);
    return out;
}

std::string PhysicalConfigDedicatedSCell_r10::nonUL_Configuration::ToStringNoNewLines() const
{
    std::string out = "nonUL_Configuration:";
    if(antennaInfo_r10_IsPresent())
        out += antennaInfo_r10_ToStringNoNewLines();
    if(crossCarrierSchedulingConfig_r10_IsPresent())
        out += crossCarrierSchedulingConfig_r10_ToStringNoNewLines();
    if(csi_RS_Config_r10_IsPresent())
        out += csi_RS_Config_r10_ToStringNoNewLines();
    if(pdsch_ConfigDedicated_r10_IsPresent())
        out += pdsch_ConfigDedicated_r10_ToStringNoNewLines();
    return out;
}

int PhysicalConfigDedicatedSCell_r10::nonUL_Configuration::Set()
{
    present = true;
    return 0;
}

int PhysicalConfigDedicatedSCell_r10::nonUL_Configuration::SetPresence(bool is_present)
{
    present = is_present;
    return 0;
}

int PhysicalConfigDedicatedSCell_r10::nonUL_Configuration::Clear()
{
    present = false;
    return 0;
}

bool PhysicalConfigDedicatedSCell_r10::nonUL_Configuration::IsPresent() const
{
    return present;
}

AntennaInfoDedicated_r10* PhysicalConfigDedicatedSCell_r10::nonUL_Configuration::antennaInfo_r10_Set()
{
    antennaInfo_r10_present = true;
    return &antennaInfo_r10;
}

int PhysicalConfigDedicatedSCell_r10::nonUL_Configuration::antennaInfo_r10_Set(AntennaInfoDedicated_r10 &value)
{
    antennaInfo_r10_present = true;
    antennaInfo_r10 = value;
    return 0;
}

const AntennaInfoDedicated_r10& PhysicalConfigDedicatedSCell_r10::nonUL_Configuration::antennaInfo_r10_Get() const
{
    return antennaInfo_r10;
}

std::string PhysicalConfigDedicatedSCell_r10::nonUL_Configuration::antennaInfo_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "antennaInfo_r10:\n";
    out += antennaInfo_r10.ToString(indent+1);
    return out;
}

std::string PhysicalConfigDedicatedSCell_r10::nonUL_Configuration::antennaInfo_r10_ToStringNoNewLines() const
{
    std::string out = "antennaInfo_r10:";
    out += antennaInfo_r10.ToStringNoNewLines();
    return out;
}

int PhysicalConfigDedicatedSCell_r10::nonUL_Configuration::antennaInfo_r10_Clear()
{
    antennaInfo_r10_present = false;
    return 0;
}

bool PhysicalConfigDedicatedSCell_r10::nonUL_Configuration::antennaInfo_r10_IsPresent() const
{
    return antennaInfo_r10_present;
}

CrossCarrierSchedulingConfig_r10* PhysicalConfigDedicatedSCell_r10::nonUL_Configuration::crossCarrierSchedulingConfig_r10_Set()
{
    crossCarrierSchedulingConfig_r10_present = true;
    return &crossCarrierSchedulingConfig_r10;
}

int PhysicalConfigDedicatedSCell_r10::nonUL_Configuration::crossCarrierSchedulingConfig_r10_Set(CrossCarrierSchedulingConfig_r10 &value)
{
    crossCarrierSchedulingConfig_r10_present = true;
    crossCarrierSchedulingConfig_r10 = value;
    return 0;
}

const CrossCarrierSchedulingConfig_r10& PhysicalConfigDedicatedSCell_r10::nonUL_Configuration::crossCarrierSchedulingConfig_r10_Get() const
{
    return crossCarrierSchedulingConfig_r10;
}

std::string PhysicalConfigDedicatedSCell_r10::nonUL_Configuration::crossCarrierSchedulingConfig_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "crossCarrierSchedulingConfig_r10:\n";
    out += crossCarrierSchedulingConfig_r10.ToString(indent+1);
    return out;
}

std::string PhysicalConfigDedicatedSCell_r10::nonUL_Configuration::crossCarrierSchedulingConfig_r10_ToStringNoNewLines() const
{
    std::string out = "crossCarrierSchedulingConfig_r10:";
    out += crossCarrierSchedulingConfig_r10.ToStringNoNewLines();
    return out;
}

int PhysicalConfigDedicatedSCell_r10::nonUL_Configuration::crossCarrierSchedulingConfig_r10_Clear()
{
    crossCarrierSchedulingConfig_r10_present = false;
    return 0;
}

bool PhysicalConfigDedicatedSCell_r10::nonUL_Configuration::crossCarrierSchedulingConfig_r10_IsPresent() const
{
    return crossCarrierSchedulingConfig_r10_present;
}

CSI_RS_Config_r10* PhysicalConfigDedicatedSCell_r10::nonUL_Configuration::csi_RS_Config_r10_Set()
{
    csi_RS_Config_r10_present = true;
    return &csi_RS_Config_r10;
}

int PhysicalConfigDedicatedSCell_r10::nonUL_Configuration::csi_RS_Config_r10_Set(CSI_RS_Config_r10 &value)
{
    csi_RS_Config_r10_present = true;
    csi_RS_Config_r10 = value;
    return 0;
}

const CSI_RS_Config_r10& PhysicalConfigDedicatedSCell_r10::nonUL_Configuration::csi_RS_Config_r10_Get() const
{
    return csi_RS_Config_r10;
}

std::string PhysicalConfigDedicatedSCell_r10::nonUL_Configuration::csi_RS_Config_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "csi_RS_Config_r10:\n";
    out += csi_RS_Config_r10.ToString(indent+1);
    return out;
}

std::string PhysicalConfigDedicatedSCell_r10::nonUL_Configuration::csi_RS_Config_r10_ToStringNoNewLines() const
{
    std::string out = "csi_RS_Config_r10:";
    out += csi_RS_Config_r10.ToStringNoNewLines();
    return out;
}

int PhysicalConfigDedicatedSCell_r10::nonUL_Configuration::csi_RS_Config_r10_Clear()
{
    csi_RS_Config_r10_present = false;
    return 0;
}

bool PhysicalConfigDedicatedSCell_r10::nonUL_Configuration::csi_RS_Config_r10_IsPresent() const
{
    return csi_RS_Config_r10_present;
}

PDSCH_ConfigDedicated* PhysicalConfigDedicatedSCell_r10::nonUL_Configuration::pdsch_ConfigDedicated_r10_Set()
{
    pdsch_ConfigDedicated_r10_present = true;
    return &pdsch_ConfigDedicated_r10;
}

int PhysicalConfigDedicatedSCell_r10::nonUL_Configuration::pdsch_ConfigDedicated_r10_Set(PDSCH_ConfigDedicated &value)
{
    pdsch_ConfigDedicated_r10_present = true;
    pdsch_ConfigDedicated_r10 = value;
    return 0;
}

const PDSCH_ConfigDedicated& PhysicalConfigDedicatedSCell_r10::nonUL_Configuration::pdsch_ConfigDedicated_r10_Get() const
{
    return pdsch_ConfigDedicated_r10;
}

std::string PhysicalConfigDedicatedSCell_r10::nonUL_Configuration::pdsch_ConfigDedicated_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "pdsch_ConfigDedicated_r10:\n";
    out += pdsch_ConfigDedicated_r10.ToString(indent+1);
    return out;
}

std::string PhysicalConfigDedicatedSCell_r10::nonUL_Configuration::pdsch_ConfigDedicated_r10_ToStringNoNewLines() const
{
    std::string out = "pdsch_ConfigDedicated_r10:";
    out += pdsch_ConfigDedicated_r10.ToStringNoNewLines();
    return out;
}

int PhysicalConfigDedicatedSCell_r10::nonUL_Configuration::pdsch_ConfigDedicated_r10_Clear()
{
    pdsch_ConfigDedicated_r10_present = false;
    return 0;
}

bool PhysicalConfigDedicatedSCell_r10::nonUL_Configuration::pdsch_ConfigDedicated_r10_IsPresent() const
{
    return pdsch_ConfigDedicated_r10_present;
}

int PhysicalConfigDedicatedSCell_r10::ul_Configuration_Pack(std::vector<uint8_t> &bits)
{
    if(!ul_Configuration_present)
    {
        printf("PhysicalConfigDedicatedSCell_r10::ul_Configuration_Pack() presence failure\n");
        return -1;
    }
    // Extension indicator

    // Choice
    for(uint32_t i=0; i<1; i++)
        bits.push_back((ul_Configuration_internal_choice >> (1-i-1)) & 1);

    // Fields
    if(ul_Configuration_internal_choice == k_ul_Configuration_release)
    {
        if(0 != ul_Configuration_release_Pack(bits))
        {
            printf("PhysicalConfigDedicatedSCell_r10::ul_Configuration_release pack failure\n");
            return -1;
        }
    }
    if(ul_Configuration_internal_choice == k_ul_Configuration_setup)
    {
        if(0 != ul_Configuration_setup_value.Pack(bits))
        {
            printf("PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup pack failure\n");
            return -1;
        }
    }
    return 0;
}

int PhysicalConfigDedicatedSCell_r10::ul_Configuration_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return ul_Configuration_Unpack(bits, idx);
}

int PhysicalConfigDedicatedSCell_r10::ul_Configuration_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 1) > bits.size())
    {
        printf("PhysicalConfigDedicatedSCell_r10::ul_Configuration_Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<1; i++)
        packed_val |= bits[idx++] << (1-i-1);

    if((PhysicalConfigDedicatedSCell_r10::ul_Configuration_Enum)packed_val > k_ul_Configuration_setup)
    {
        printf("PhysicalConfigDedicatedSCell_r10::ul_Configuration_Unpack() choice range failure\n");
        return -1;
    }
    ul_Configuration_internal_choice = (PhysicalConfigDedicatedSCell_r10::ul_Configuration_Enum)packed_val;
    ul_Configuration_present = true;

    // Fields
    if(ul_Configuration_internal_choice == k_ul_Configuration_release)
    {
        if(0 != ul_Configuration_release_Unpack(bits, idx))
        {
            printf("PhysicalConfigDedicatedSCell_r10::ul_Configuration_release unpack failure\n");
            return -1;
        }
    }
    if(ul_Configuration_internal_choice == k_ul_Configuration_setup)
    {
        if(0 != ul_Configuration_setup_value.Unpack(bits, idx))
        {
            printf("PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup unpack failure\n");
            return -1;
        }
    }
    return 0;
}

PhysicalConfigDedicatedSCell_r10::ul_Configuration_Enum PhysicalConfigDedicatedSCell_r10::ul_Configuration_Choice() const
{
    if(ul_Configuration_present)
        return ul_Configuration_internal_choice;
    return (PhysicalConfigDedicatedSCell_r10::ul_Configuration_Enum)0;
}

int PhysicalConfigDedicatedSCell_r10::ul_Configuration_SetChoice(PhysicalConfigDedicatedSCell_r10::ul_Configuration_Enum choice)
{
    ul_Configuration_internal_choice = choice;
    ul_Configuration_present = true;
    return 0;
}

std::string PhysicalConfigDedicatedSCell_r10::ul_Configuration_ChoiceToString(ul_Configuration_Enum value) const
{
    if(k_ul_Configuration_release == value)
        return "ul_Configuration_release";
    if(k_ul_Configuration_setup == value)
        return "ul_Configuration_setup";
    return "";
}

uint64_t PhysicalConfigDedicatedSCell_r10::ul_Configuration_NumberOfChoices() const
{
    return 2;
}

std::string PhysicalConfigDedicatedSCell_r10::ul_Configuration_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ul_Configuration = " + ul_Configuration_ChoiceToString(ul_Configuration_internal_choice) + ":\n";
    if(ul_Configuration_internal_choice == k_ul_Configuration_setup)
        out += ul_Configuration_setup_value.ToString(indent+1);
    return out;
}

std::string PhysicalConfigDedicatedSCell_r10::ul_Configuration_ToStringNoNewLines() const
{
    std::string out = "ul_Configuration=" + ul_Configuration_ChoiceToString(ul_Configuration_internal_choice) + ",";
    if(ul_Configuration_internal_choice == k_ul_Configuration_setup)
        out += ul_Configuration_setup_value.ToStringNoNewLines();
    return out;
}

int PhysicalConfigDedicatedSCell_r10::ul_Configuration_Clear()
{
    ul_Configuration_present = false;
    return 0;
}

bool PhysicalConfigDedicatedSCell_r10::ul_Configuration_IsPresent() const
{
    return ul_Configuration_present;
}

int PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(pusch_ConfigDedicated_r10_IsPresent());
    bits.push_back(pusch_ConfigDedicated_v10x0_IsPresent());
    bits.push_back(uplinkPowerControlDedicated_r10_IsPresent());
    bits.push_back(cqi_ReportConfig_r10_IsPresent());
    bits.push_back(soundingRS_UL_ConfigDedicated_r10_IsPresent());
    bits.push_back(soundingRS_UL_ConfigDedicated_v10x0_IsPresent());
    bits.push_back(soundingRS_UL_ConfigDedicatedAperiodic_r10_IsPresent());
    bits.push_back(ul_AntennaInfo_r10_IsPresent());

    // Fields
    if(pusch_ConfigDedicated_r10_IsPresent())
    {
        if(0 != pusch_ConfigDedicated_r10.Pack(bits))
        {
            printf("PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup:: field pack failure\n");
            return -1;
        }
    }
    if(pusch_ConfigDedicated_v10x0_IsPresent())
    {
        if(0 != pusch_ConfigDedicated_v10x0.Pack(bits))
        {
            printf("PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup:: field pack failure\n");
            return -1;
        }
    }
    if(uplinkPowerControlDedicated_r10_IsPresent())
    {
        if(0 != uplinkPowerControlDedicated_r10.Pack(bits))
        {
            printf("PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup:: field pack failure\n");
            return -1;
        }
    }
    if(cqi_ReportConfig_r10_IsPresent())
    {
        if(0 != cqi_ReportConfig_r10.Pack(bits))
        {
            printf("PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup:: field pack failure\n");
            return -1;
        }
    }
    if(soundingRS_UL_ConfigDedicated_r10_IsPresent())
    {
        if(0 != soundingRS_UL_ConfigDedicated_r10.Pack(bits))
        {
            printf("PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup:: field pack failure\n");
            return -1;
        }
    }
    if(soundingRS_UL_ConfigDedicated_v10x0_IsPresent())
    {
        if(0 != soundingRS_UL_ConfigDedicated_v10x0.Pack(bits))
        {
            printf("PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup:: field pack failure\n");
            return -1;
        }
    }
    if(soundingRS_UL_ConfigDedicatedAperiodic_r10_IsPresent())
    {
        if(0 != soundingRS_UL_ConfigDedicatedAperiodic_r10.Pack(bits))
        {
            printf("PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup:: field pack failure\n");
            return -1;
        }
    }
    if(ul_AntennaInfo_r10_IsPresent())
    {
        if(0 != ul_AntennaInfo_r10.Pack(bits))
        {
            printf("PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("ul_Configuration_setup::Unpack() index out of bounds for optional indiator pusch_ConfigDedicated_r10\n");
        return -1;
    }
    pusch_ConfigDedicated_r10_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("ul_Configuration_setup::Unpack() index out of bounds for optional indiator pusch_ConfigDedicated_v10x0\n");
        return -1;
    }
    pusch_ConfigDedicated_v10x0_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("ul_Configuration_setup::Unpack() index out of bounds for optional indiator uplinkPowerControlDedicated_r10\n");
        return -1;
    }
    uplinkPowerControlDedicated_r10_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("ul_Configuration_setup::Unpack() index out of bounds for optional indiator cqi_ReportConfig_r10\n");
        return -1;
    }
    cqi_ReportConfig_r10_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("ul_Configuration_setup::Unpack() index out of bounds for optional indiator soundingRS_UL_ConfigDedicated_r10\n");
        return -1;
    }
    soundingRS_UL_ConfigDedicated_r10_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("ul_Configuration_setup::Unpack() index out of bounds for optional indiator soundingRS_UL_ConfigDedicated_v10x0\n");
        return -1;
    }
    soundingRS_UL_ConfigDedicated_v10x0_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("ul_Configuration_setup::Unpack() index out of bounds for optional indiator soundingRS_UL_ConfigDedicatedAperiodic_r10\n");
        return -1;
    }
    soundingRS_UL_ConfigDedicatedAperiodic_r10_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("ul_Configuration_setup::Unpack() index out of bounds for optional indiator ul_AntennaInfo_r10\n");
        return -1;
    }
    ul_AntennaInfo_r10_present = bits[idx++];

    // Fields
    if(pusch_ConfigDedicated_r10_present)
    {
        if(0 != pusch_ConfigDedicated_r10.Unpack(bits, idx))
        {
            printf("PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup:: field unpack failure\n");
            return -1;
        }
    }
    if(pusch_ConfigDedicated_v10x0_present)
    {
        if(0 != pusch_ConfigDedicated_v10x0.Unpack(bits, idx))
        {
            printf("PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup:: field unpack failure\n");
            return -1;
        }
    }
    if(uplinkPowerControlDedicated_r10_present)
    {
        if(0 != uplinkPowerControlDedicated_r10.Unpack(bits, idx))
        {
            printf("PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup:: field unpack failure\n");
            return -1;
        }
    }
    if(cqi_ReportConfig_r10_present)
    {
        if(0 != cqi_ReportConfig_r10.Unpack(bits, idx))
        {
            printf("PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup:: field unpack failure\n");
            return -1;
        }
    }
    if(soundingRS_UL_ConfigDedicated_r10_present)
    {
        if(0 != soundingRS_UL_ConfigDedicated_r10.Unpack(bits, idx))
        {
            printf("PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup:: field unpack failure\n");
            return -1;
        }
    }
    if(soundingRS_UL_ConfigDedicated_v10x0_present)
    {
        if(0 != soundingRS_UL_ConfigDedicated_v10x0.Unpack(bits, idx))
        {
            printf("PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup:: field unpack failure\n");
            return -1;
        }
    }
    if(soundingRS_UL_ConfigDedicatedAperiodic_r10_present)
    {
        if(0 != soundingRS_UL_ConfigDedicatedAperiodic_r10.Unpack(bits, idx))
        {
            printf("PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup:: field unpack failure\n");
            return -1;
        }
    }
    if(ul_AntennaInfo_r10_present)
    {
        if(0 != ul_AntennaInfo_r10.Unpack(bits, idx))
        {
            printf("PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "setup:\n";
    if(pusch_ConfigDedicated_r10_IsPresent())
        out += pusch_ConfigDedicated_r10_ToString(indent+1);
    if(pusch_ConfigDedicated_v10x0_IsPresent())
        out += pusch_ConfigDedicated_v10x0_ToString(indent+1);
    if(uplinkPowerControlDedicated_r10_IsPresent())
        out += uplinkPowerControlDedicated_r10_ToString(indent+1);
    if(cqi_ReportConfig_r10_IsPresent())
        out += cqi_ReportConfig_r10_ToString(indent+1);
    if(soundingRS_UL_ConfigDedicated_r10_IsPresent())
        out += soundingRS_UL_ConfigDedicated_r10_ToString(indent+1);
    if(soundingRS_UL_ConfigDedicated_v10x0_IsPresent())
        out += soundingRS_UL_ConfigDedicated_v10x0_ToString(indent+1);
    if(soundingRS_UL_ConfigDedicatedAperiodic_r10_IsPresent())
        out += soundingRS_UL_ConfigDedicatedAperiodic_r10_ToString(indent+1);
    if(ul_AntennaInfo_r10_IsPresent())
        out += ul_AntennaInfo_r10_ToString(indent+1);
    return out;
}

std::string PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup::ToStringNoNewLines() const
{
    std::string out = "setup:";
    if(pusch_ConfigDedicated_r10_IsPresent())
        out += pusch_ConfigDedicated_r10_ToStringNoNewLines();
    if(pusch_ConfigDedicated_v10x0_IsPresent())
        out += pusch_ConfigDedicated_v10x0_ToStringNoNewLines();
    if(uplinkPowerControlDedicated_r10_IsPresent())
        out += uplinkPowerControlDedicated_r10_ToStringNoNewLines();
    if(cqi_ReportConfig_r10_IsPresent())
        out += cqi_ReportConfig_r10_ToStringNoNewLines();
    if(soundingRS_UL_ConfigDedicated_r10_IsPresent())
        out += soundingRS_UL_ConfigDedicated_r10_ToStringNoNewLines();
    if(soundingRS_UL_ConfigDedicated_v10x0_IsPresent())
        out += soundingRS_UL_ConfigDedicated_v10x0_ToStringNoNewLines();
    if(soundingRS_UL_ConfigDedicatedAperiodic_r10_IsPresent())
        out += soundingRS_UL_ConfigDedicatedAperiodic_r10_ToStringNoNewLines();
    if(ul_AntennaInfo_r10_IsPresent())
        out += ul_AntennaInfo_r10_ToStringNoNewLines();
    return out;
}

PUSCH_ConfigDedicated* PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup::pusch_ConfigDedicated_r10_Set()
{
    pusch_ConfigDedicated_r10_present = true;
    return &pusch_ConfigDedicated_r10;
}

int PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup::pusch_ConfigDedicated_r10_Set(PUSCH_ConfigDedicated &value)
{
    pusch_ConfigDedicated_r10_present = true;
    pusch_ConfigDedicated_r10 = value;
    return 0;
}

const PUSCH_ConfigDedicated& PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup::pusch_ConfigDedicated_r10_Get() const
{
    return pusch_ConfigDedicated_r10;
}

std::string PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup::pusch_ConfigDedicated_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "pusch_ConfigDedicated_r10:\n";
    out += pusch_ConfigDedicated_r10.ToString(indent+1);
    return out;
}

std::string PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup::pusch_ConfigDedicated_r10_ToStringNoNewLines() const
{
    std::string out = "pusch_ConfigDedicated_r10:";
    out += pusch_ConfigDedicated_r10.ToStringNoNewLines();
    return out;
}

int PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup::pusch_ConfigDedicated_r10_Clear()
{
    pusch_ConfigDedicated_r10_present = false;
    return 0;
}

bool PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup::pusch_ConfigDedicated_r10_IsPresent() const
{
    return pusch_ConfigDedicated_r10_present;
}

PUSCH_ConfigDedicated_v10x0* PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup::pusch_ConfigDedicated_v10x0_Set()
{
    pusch_ConfigDedicated_v10x0_present = true;
    return &pusch_ConfigDedicated_v10x0;
}

int PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup::pusch_ConfigDedicated_v10x0_Set(PUSCH_ConfigDedicated_v10x0 &value)
{
    pusch_ConfigDedicated_v10x0_present = true;
    pusch_ConfigDedicated_v10x0 = value;
    return 0;
}

const PUSCH_ConfigDedicated_v10x0& PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup::pusch_ConfigDedicated_v10x0_Get() const
{
    return pusch_ConfigDedicated_v10x0;
}

std::string PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup::pusch_ConfigDedicated_v10x0_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "pusch_ConfigDedicated_v10x0:\n";
    out += pusch_ConfigDedicated_v10x0.ToString(indent+1);
    return out;
}

std::string PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup::pusch_ConfigDedicated_v10x0_ToStringNoNewLines() const
{
    std::string out = "pusch_ConfigDedicated_v10x0:";
    out += pusch_ConfigDedicated_v10x0.ToStringNoNewLines();
    return out;
}

int PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup::pusch_ConfigDedicated_v10x0_Clear()
{
    pusch_ConfigDedicated_v10x0_present = false;
    return 0;
}

bool PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup::pusch_ConfigDedicated_v10x0_IsPresent() const
{
    return pusch_ConfigDedicated_v10x0_present;
}

UplinkPowerControlDedicatedSCell_r10* PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup::uplinkPowerControlDedicated_r10_Set()
{
    uplinkPowerControlDedicated_r10_present = true;
    return &uplinkPowerControlDedicated_r10;
}

int PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup::uplinkPowerControlDedicated_r10_Set(UplinkPowerControlDedicatedSCell_r10 &value)
{
    uplinkPowerControlDedicated_r10_present = true;
    uplinkPowerControlDedicated_r10 = value;
    return 0;
}

const UplinkPowerControlDedicatedSCell_r10& PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup::uplinkPowerControlDedicated_r10_Get() const
{
    return uplinkPowerControlDedicated_r10;
}

std::string PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup::uplinkPowerControlDedicated_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "uplinkPowerControlDedicated_r10:\n";
    out += uplinkPowerControlDedicated_r10.ToString(indent+1);
    return out;
}

std::string PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup::uplinkPowerControlDedicated_r10_ToStringNoNewLines() const
{
    std::string out = "uplinkPowerControlDedicated_r10:";
    out += uplinkPowerControlDedicated_r10.ToStringNoNewLines();
    return out;
}

int PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup::uplinkPowerControlDedicated_r10_Clear()
{
    uplinkPowerControlDedicated_r10_present = false;
    return 0;
}

bool PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup::uplinkPowerControlDedicated_r10_IsPresent() const
{
    return uplinkPowerControlDedicated_r10_present;
}

CQI_ReportConfigSCell_r10* PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup::cqi_ReportConfig_r10_Set()
{
    cqi_ReportConfig_r10_present = true;
    return &cqi_ReportConfig_r10;
}

int PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup::cqi_ReportConfig_r10_Set(CQI_ReportConfigSCell_r10 &value)
{
    cqi_ReportConfig_r10_present = true;
    cqi_ReportConfig_r10 = value;
    return 0;
}

const CQI_ReportConfigSCell_r10& PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup::cqi_ReportConfig_r10_Get() const
{
    return cqi_ReportConfig_r10;
}

std::string PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup::cqi_ReportConfig_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cqi_ReportConfig_r10:\n";
    out += cqi_ReportConfig_r10.ToString(indent+1);
    return out;
}

std::string PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup::cqi_ReportConfig_r10_ToStringNoNewLines() const
{
    std::string out = "cqi_ReportConfig_r10:";
    out += cqi_ReportConfig_r10.ToStringNoNewLines();
    return out;
}

int PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup::cqi_ReportConfig_r10_Clear()
{
    cqi_ReportConfig_r10_present = false;
    return 0;
}

bool PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup::cqi_ReportConfig_r10_IsPresent() const
{
    return cqi_ReportConfig_r10_present;
}

SoundingRS_UL_ConfigDedicated* PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup::soundingRS_UL_ConfigDedicated_r10_Set()
{
    soundingRS_UL_ConfigDedicated_r10_present = true;
    return &soundingRS_UL_ConfigDedicated_r10;
}

int PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup::soundingRS_UL_ConfigDedicated_r10_Set(SoundingRS_UL_ConfigDedicated &value)
{
    soundingRS_UL_ConfigDedicated_r10_present = true;
    soundingRS_UL_ConfigDedicated_r10 = value;
    return 0;
}

const SoundingRS_UL_ConfigDedicated& PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup::soundingRS_UL_ConfigDedicated_r10_Get() const
{
    return soundingRS_UL_ConfigDedicated_r10;
}

std::string PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup::soundingRS_UL_ConfigDedicated_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "soundingRS_UL_ConfigDedicated_r10:\n";
    out += soundingRS_UL_ConfigDedicated_r10.ToString(indent+1);
    return out;
}

std::string PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup::soundingRS_UL_ConfigDedicated_r10_ToStringNoNewLines() const
{
    std::string out = "soundingRS_UL_ConfigDedicated_r10:";
    out += soundingRS_UL_ConfigDedicated_r10.ToStringNoNewLines();
    return out;
}

int PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup::soundingRS_UL_ConfigDedicated_r10_Clear()
{
    soundingRS_UL_ConfigDedicated_r10_present = false;
    return 0;
}

bool PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup::soundingRS_UL_ConfigDedicated_r10_IsPresent() const
{
    return soundingRS_UL_ConfigDedicated_r10_present;
}

SoundingRS_UL_ConfigDedicated_v10x0* PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup::soundingRS_UL_ConfigDedicated_v10x0_Set()
{
    soundingRS_UL_ConfigDedicated_v10x0_present = true;
    return &soundingRS_UL_ConfigDedicated_v10x0;
}

int PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup::soundingRS_UL_ConfigDedicated_v10x0_Set(SoundingRS_UL_ConfigDedicated_v10x0 &value)
{
    soundingRS_UL_ConfigDedicated_v10x0_present = true;
    soundingRS_UL_ConfigDedicated_v10x0 = value;
    return 0;
}

const SoundingRS_UL_ConfigDedicated_v10x0& PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup::soundingRS_UL_ConfigDedicated_v10x0_Get() const
{
    return soundingRS_UL_ConfigDedicated_v10x0;
}

std::string PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup::soundingRS_UL_ConfigDedicated_v10x0_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "soundingRS_UL_ConfigDedicated_v10x0:\n";
    out += soundingRS_UL_ConfigDedicated_v10x0.ToString(indent+1);
    return out;
}

std::string PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup::soundingRS_UL_ConfigDedicated_v10x0_ToStringNoNewLines() const
{
    std::string out = "soundingRS_UL_ConfigDedicated_v10x0:";
    out += soundingRS_UL_ConfigDedicated_v10x0.ToStringNoNewLines();
    return out;
}

int PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup::soundingRS_UL_ConfigDedicated_v10x0_Clear()
{
    soundingRS_UL_ConfigDedicated_v10x0_present = false;
    return 0;
}

bool PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup::soundingRS_UL_ConfigDedicated_v10x0_IsPresent() const
{
    return soundingRS_UL_ConfigDedicated_v10x0_present;
}

SoundingRS_UL_ConfigDedicatedAperiodic_r10* PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup::soundingRS_UL_ConfigDedicatedAperiodic_r10_Set()
{
    soundingRS_UL_ConfigDedicatedAperiodic_r10_present = true;
    return &soundingRS_UL_ConfigDedicatedAperiodic_r10;
}

int PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup::soundingRS_UL_ConfigDedicatedAperiodic_r10_Set(SoundingRS_UL_ConfigDedicatedAperiodic_r10 &value)
{
    soundingRS_UL_ConfigDedicatedAperiodic_r10_present = true;
    soundingRS_UL_ConfigDedicatedAperiodic_r10 = value;
    return 0;
}

const SoundingRS_UL_ConfigDedicatedAperiodic_r10& PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup::soundingRS_UL_ConfigDedicatedAperiodic_r10_Get() const
{
    return soundingRS_UL_ConfigDedicatedAperiodic_r10;
}

std::string PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup::soundingRS_UL_ConfigDedicatedAperiodic_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "soundingRS_UL_ConfigDedicatedAperiodic_r10:\n";
    out += soundingRS_UL_ConfigDedicatedAperiodic_r10.ToString(indent+1);
    return out;
}

std::string PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup::soundingRS_UL_ConfigDedicatedAperiodic_r10_ToStringNoNewLines() const
{
    std::string out = "soundingRS_UL_ConfigDedicatedAperiodic_r10:";
    out += soundingRS_UL_ConfigDedicatedAperiodic_r10.ToStringNoNewLines();
    return out;
}

int PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup::soundingRS_UL_ConfigDedicatedAperiodic_r10_Clear()
{
    soundingRS_UL_ConfigDedicatedAperiodic_r10_present = false;
    return 0;
}

bool PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup::soundingRS_UL_ConfigDedicatedAperiodic_r10_IsPresent() const
{
    return soundingRS_UL_ConfigDedicatedAperiodic_r10_present;
}

UL_AntennaInfo_r10* PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup::ul_AntennaInfo_r10_Set()
{
    ul_AntennaInfo_r10_present = true;
    return &ul_AntennaInfo_r10;
}

int PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup::ul_AntennaInfo_r10_Set(UL_AntennaInfo_r10 &value)
{
    ul_AntennaInfo_r10_present = true;
    ul_AntennaInfo_r10 = value;
    return 0;
}

const UL_AntennaInfo_r10& PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup::ul_AntennaInfo_r10_Get() const
{
    return ul_AntennaInfo_r10;
}

std::string PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup::ul_AntennaInfo_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ul_AntennaInfo_r10:\n";
    out += ul_AntennaInfo_r10.ToString(indent+1);
    return out;
}

std::string PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup::ul_AntennaInfo_r10_ToStringNoNewLines() const
{
    std::string out = "ul_AntennaInfo_r10:";
    out += ul_AntennaInfo_r10.ToStringNoNewLines();
    return out;
}

int PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup::ul_AntennaInfo_r10_Clear()
{
    ul_AntennaInfo_r10_present = false;
    return 0;
}

bool PhysicalConfigDedicatedSCell_r10::ul_Configuration_setup::ul_AntennaInfo_r10_IsPresent() const
{
    return ul_AntennaInfo_r10_present;
}

