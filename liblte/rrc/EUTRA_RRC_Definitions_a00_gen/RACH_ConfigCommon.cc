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

#include "RACH_ConfigCommon.h"

#include <cmath>

int RACH_ConfigCommon::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator
    bits.push_back(0);

    // Optional indicators

    // Fields
    {
        if(0 != preambleInfo_value.Pack(bits))
        {
            printf("RACH_ConfigCommon:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != powerRampingParameters_value.Pack(bits))
        {
            printf("RACH_ConfigCommon:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != ra_SupervisionInfo_value.Pack(bits))
        {
            printf("RACH_ConfigCommon:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != maxHARQ_Msg3Tx_Pack(bits))
        {
            printf("RACH_ConfigCommon:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int RACH_ConfigCommon::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int RACH_ConfigCommon::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("RACH_ConfigCommon::Unpack() index out of bounds for extension\n");
        return -1;
    }
    idx++;

    // Optional indicators

    // Fields
    {
        if(0 != preambleInfo_value.Unpack(bits, idx))
        {
            printf("RACH_ConfigCommon:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != powerRampingParameters_value.Unpack(bits, idx))
        {
            printf("RACH_ConfigCommon:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != ra_SupervisionInfo_value.Unpack(bits, idx))
        {
            printf("RACH_ConfigCommon:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != maxHARQ_Msg3Tx_Unpack(bits, idx))
        {
            printf("RACH_ConfigCommon:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string RACH_ConfigCommon::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "RACH_ConfigCommon:\n";
    out += preambleInfo_value.ToString(indent+1);
    out += powerRampingParameters_value.ToString(indent+1);
    out += ra_SupervisionInfo_value.ToString(indent+1);
    out += maxHARQ_Msg3Tx_ToString(indent+1);
    return out;
}

std::string RACH_ConfigCommon::ToStringNoNewLines() const
{
    std::string out = "RACH_ConfigCommon:";
    out += preambleInfo_value.ToStringNoNewLines();
    out += powerRampingParameters_value.ToStringNoNewLines();
    out += ra_SupervisionInfo_value.ToStringNoNewLines();
    out += maxHARQ_Msg3Tx_ToStringNoNewLines();
    return out;
}

int RACH_ConfigCommon::preambleInfo::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(preamblesGroupAConfig_value.IsPresent());

    // Fields
    {
        if(0 != numberOfRA_Preambles_Pack(bits))
        {
            printf("RACH_ConfigCommon::preambleInfo:: field pack failure\n");
            return -1;
        }
    }
    if(preamblesGroupAConfig_value.IsPresent())
    {
        if(0 != preamblesGroupAConfig_value.Pack(bits))
        {
            printf("RACH_ConfigCommon::preambleInfo:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int RACH_ConfigCommon::preambleInfo::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int RACH_ConfigCommon::preambleInfo::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("preambleInfo::Unpack() index out of bounds for optional indiator preamblesGroupAConfig\n");
        return -1;
    }
    preamblesGroupAConfig_value.SetPresence(bits[idx++]);

    // Fields
    {
        if(0 != numberOfRA_Preambles_Unpack(bits, idx))
        {
            printf("RACH_ConfigCommon::preambleInfo:: field unpack failure\n");
            return -1;
        }
    }
    if(preamblesGroupAConfig_value.IsPresent())
    {
        if(0 != preamblesGroupAConfig_value.Unpack(bits, idx))
        {
            printf("RACH_ConfigCommon::preambleInfo:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string RACH_ConfigCommon::preambleInfo::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "preambleInfo:\n";
    out += numberOfRA_Preambles_ToString(indent+1);
    if(preamblesGroupAConfig_value.IsPresent())
        out += preamblesGroupAConfig_value.ToString(indent+1);
    return out;
}

std::string RACH_ConfigCommon::preambleInfo::ToStringNoNewLines() const
{
    std::string out = "preambleInfo:";
    out += numberOfRA_Preambles_ToStringNoNewLines();
    if(preamblesGroupAConfig_value.IsPresent())
        out += preamblesGroupAConfig_value.ToStringNoNewLines();
    return out;
}

int RACH_ConfigCommon::preambleInfo::numberOfRA_Preambles_Pack(std::vector<uint8_t> &bits)
{
    if(!numberOfRA_Preambles_present)
    {
        printf("RACH_ConfigCommon::preambleInfo::numberOfRA_Preambles_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 4;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((numberOfRA_Preambles_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int RACH_ConfigCommon::preambleInfo::numberOfRA_Preambles_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return numberOfRA_Preambles_Unpack(bits, idx);
}

int RACH_ConfigCommon::preambleInfo::numberOfRA_Preambles_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 4;
    if((idx + N_bits) > bits.size())
    {
        printf("RACH_ConfigCommon::preambleInfo::numberOfRA_Preambles_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 15)
    {
        printf("RACH_ConfigCommon::preambleInfo::numberOfRA_Preambles_Unpack() max failure\n");
        return -1;
    }
    numberOfRA_Preambles_internal_value = (numberOfRA_Preambles_Enum)packed_val;
    numberOfRA_Preambles_present = true;
    return 0;
}

RACH_ConfigCommon::preambleInfo::numberOfRA_Preambles_Enum RACH_ConfigCommon::preambleInfo::numberOfRA_Preambles_Value() const
{
    if(numberOfRA_Preambles_present)
        return numberOfRA_Preambles_internal_value;
    return (RACH_ConfigCommon::preambleInfo::numberOfRA_Preambles_Enum)0;
}

int RACH_ConfigCommon::preambleInfo::numberOfRA_Preambles_SetValue(numberOfRA_Preambles_Enum value)
{
    numberOfRA_Preambles_internal_value = value;
    numberOfRA_Preambles_present = true;
    return 0;
}

int RACH_ConfigCommon::preambleInfo::numberOfRA_Preambles_SetValue(std::string value)
{
    if("n4" == value)
    {
        numberOfRA_Preambles_internal_value = k_numberOfRA_Preambles_n4;
        numberOfRA_Preambles_present = true;
        return 0;
    }
    if("n8" == value)
    {
        numberOfRA_Preambles_internal_value = k_numberOfRA_Preambles_n8;
        numberOfRA_Preambles_present = true;
        return 0;
    }
    if("n12" == value)
    {
        numberOfRA_Preambles_internal_value = k_numberOfRA_Preambles_n12;
        numberOfRA_Preambles_present = true;
        return 0;
    }
    if("n16" == value)
    {
        numberOfRA_Preambles_internal_value = k_numberOfRA_Preambles_n16;
        numberOfRA_Preambles_present = true;
        return 0;
    }
    if("n20" == value)
    {
        numberOfRA_Preambles_internal_value = k_numberOfRA_Preambles_n20;
        numberOfRA_Preambles_present = true;
        return 0;
    }
    if("n24" == value)
    {
        numberOfRA_Preambles_internal_value = k_numberOfRA_Preambles_n24;
        numberOfRA_Preambles_present = true;
        return 0;
    }
    if("n28" == value)
    {
        numberOfRA_Preambles_internal_value = k_numberOfRA_Preambles_n28;
        numberOfRA_Preambles_present = true;
        return 0;
    }
    if("n32" == value)
    {
        numberOfRA_Preambles_internal_value = k_numberOfRA_Preambles_n32;
        numberOfRA_Preambles_present = true;
        return 0;
    }
    if("n36" == value)
    {
        numberOfRA_Preambles_internal_value = k_numberOfRA_Preambles_n36;
        numberOfRA_Preambles_present = true;
        return 0;
    }
    if("n40" == value)
    {
        numberOfRA_Preambles_internal_value = k_numberOfRA_Preambles_n40;
        numberOfRA_Preambles_present = true;
        return 0;
    }
    if("n44" == value)
    {
        numberOfRA_Preambles_internal_value = k_numberOfRA_Preambles_n44;
        numberOfRA_Preambles_present = true;
        return 0;
    }
    if("n48" == value)
    {
        numberOfRA_Preambles_internal_value = k_numberOfRA_Preambles_n48;
        numberOfRA_Preambles_present = true;
        return 0;
    }
    if("n52" == value)
    {
        numberOfRA_Preambles_internal_value = k_numberOfRA_Preambles_n52;
        numberOfRA_Preambles_present = true;
        return 0;
    }
    if("n56" == value)
    {
        numberOfRA_Preambles_internal_value = k_numberOfRA_Preambles_n56;
        numberOfRA_Preambles_present = true;
        return 0;
    }
    if("n60" == value)
    {
        numberOfRA_Preambles_internal_value = k_numberOfRA_Preambles_n60;
        numberOfRA_Preambles_present = true;
        return 0;
    }
    if("n64" == value)
    {
        numberOfRA_Preambles_internal_value = k_numberOfRA_Preambles_n64;
        numberOfRA_Preambles_present = true;
        return 0;
    }
    return 1;
}

std::string RACH_ConfigCommon::preambleInfo::numberOfRA_Preambles_ValueToString(numberOfRA_Preambles_Enum value) const
{
    if(k_numberOfRA_Preambles_n4 == value)
        return "n4";
    if(k_numberOfRA_Preambles_n8 == value)
        return "n8";
    if(k_numberOfRA_Preambles_n12 == value)
        return "n12";
    if(k_numberOfRA_Preambles_n16 == value)
        return "n16";
    if(k_numberOfRA_Preambles_n20 == value)
        return "n20";
    if(k_numberOfRA_Preambles_n24 == value)
        return "n24";
    if(k_numberOfRA_Preambles_n28 == value)
        return "n28";
    if(k_numberOfRA_Preambles_n32 == value)
        return "n32";
    if(k_numberOfRA_Preambles_n36 == value)
        return "n36";
    if(k_numberOfRA_Preambles_n40 == value)
        return "n40";
    if(k_numberOfRA_Preambles_n44 == value)
        return "n44";
    if(k_numberOfRA_Preambles_n48 == value)
        return "n48";
    if(k_numberOfRA_Preambles_n52 == value)
        return "n52";
    if(k_numberOfRA_Preambles_n56 == value)
        return "n56";
    if(k_numberOfRA_Preambles_n60 == value)
        return "n60";
    if(k_numberOfRA_Preambles_n64 == value)
        return "n64";
    return "";
}

uint64_t RACH_ConfigCommon::preambleInfo::numberOfRA_Preambles_NumberOfValues() const
{
    return 16;
}

std::string RACH_ConfigCommon::preambleInfo::numberOfRA_Preambles_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "numberOfRA_Preambles = " + numberOfRA_Preambles_ValueToString(numberOfRA_Preambles_internal_value) + "\n";
    return out;
}

std::string RACH_ConfigCommon::preambleInfo::numberOfRA_Preambles_ToStringNoNewLines() const
{
    std::string out = "numberOfRA_Preambles=" + numberOfRA_Preambles_ValueToString(numberOfRA_Preambles_internal_value) + ",";
    return out;
}

int RACH_ConfigCommon::preambleInfo::numberOfRA_Preambles_Clear()
{
    numberOfRA_Preambles_present = false;
    return 0;
}

bool RACH_ConfigCommon::preambleInfo::numberOfRA_Preambles_IsPresent() const
{
    return numberOfRA_Preambles_present;
}

int RACH_ConfigCommon::preambleInfo::preamblesGroupAConfig::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator
    bits.push_back(0);

    // Optional indicators

    // Fields
    {
        if(0 != sizeOfRA_PreamblesGroupA_Pack(bits))
        {
            printf("RACH_ConfigCommon::preambleInfo::preamblesGroupAConfig:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != messageSizeGroupA_Pack(bits))
        {
            printf("RACH_ConfigCommon::preambleInfo::preamblesGroupAConfig:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != messagePowerOffsetGroupB_Pack(bits))
        {
            printf("RACH_ConfigCommon::preambleInfo::preamblesGroupAConfig:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int RACH_ConfigCommon::preambleInfo::preamblesGroupAConfig::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int RACH_ConfigCommon::preambleInfo::preamblesGroupAConfig::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("preamblesGroupAConfig::Unpack() index out of bounds for extension\n");
        return -1;
    }
    idx++;

    // Optional indicators

    // Fields
    {
        if(0 != sizeOfRA_PreamblesGroupA_Unpack(bits, idx))
        {
            printf("RACH_ConfigCommon::preambleInfo::preamblesGroupAConfig:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != messageSizeGroupA_Unpack(bits, idx))
        {
            printf("RACH_ConfigCommon::preambleInfo::preamblesGroupAConfig:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != messagePowerOffsetGroupB_Unpack(bits, idx))
        {
            printf("RACH_ConfigCommon::preambleInfo::preamblesGroupAConfig:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string RACH_ConfigCommon::preambleInfo::preamblesGroupAConfig::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "preamblesGroupAConfig:\n";
    out += sizeOfRA_PreamblesGroupA_ToString(indent+1);
    out += messageSizeGroupA_ToString(indent+1);
    out += messagePowerOffsetGroupB_ToString(indent+1);
    return out;
}

std::string RACH_ConfigCommon::preambleInfo::preamblesGroupAConfig::ToStringNoNewLines() const
{
    std::string out = "preamblesGroupAConfig:";
    out += sizeOfRA_PreamblesGroupA_ToStringNoNewLines();
    out += messageSizeGroupA_ToStringNoNewLines();
    out += messagePowerOffsetGroupB_ToStringNoNewLines();
    return out;
}

int RACH_ConfigCommon::preambleInfo::preamblesGroupAConfig::Set()
{
    present = true;
    return 0;
}

int RACH_ConfigCommon::preambleInfo::preamblesGroupAConfig::SetPresence(bool is_present)
{
    present = is_present;
    return 0;
}

int RACH_ConfigCommon::preambleInfo::preamblesGroupAConfig::Clear()
{
    present = false;
    return 0;
}

bool RACH_ConfigCommon::preambleInfo::preamblesGroupAConfig::IsPresent() const
{
    return present;
}

int RACH_ConfigCommon::preambleInfo::preamblesGroupAConfig::sizeOfRA_PreamblesGroupA_Pack(std::vector<uint8_t> &bits)
{
    if(!sizeOfRA_PreamblesGroupA_present)
    {
        printf("RACH_ConfigCommon::preambleInfo::preamblesGroupAConfig::sizeOfRA_PreamblesGroupA_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 4;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((sizeOfRA_PreamblesGroupA_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int RACH_ConfigCommon::preambleInfo::preamblesGroupAConfig::sizeOfRA_PreamblesGroupA_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return sizeOfRA_PreamblesGroupA_Unpack(bits, idx);
}

int RACH_ConfigCommon::preambleInfo::preamblesGroupAConfig::sizeOfRA_PreamblesGroupA_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 4;
    if((idx + N_bits) > bits.size())
    {
        printf("RACH_ConfigCommon::preambleInfo::preamblesGroupAConfig::sizeOfRA_PreamblesGroupA_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 14)
    {
        printf("RACH_ConfigCommon::preambleInfo::preamblesGroupAConfig::sizeOfRA_PreamblesGroupA_Unpack() max failure\n");
        return -1;
    }
    sizeOfRA_PreamblesGroupA_internal_value = (sizeOfRA_PreamblesGroupA_Enum)packed_val;
    sizeOfRA_PreamblesGroupA_present = true;
    return 0;
}

RACH_ConfigCommon::preambleInfo::preamblesGroupAConfig::sizeOfRA_PreamblesGroupA_Enum RACH_ConfigCommon::preambleInfo::preamblesGroupAConfig::sizeOfRA_PreamblesGroupA_Value() const
{
    if(sizeOfRA_PreamblesGroupA_present)
        return sizeOfRA_PreamblesGroupA_internal_value;
    return (RACH_ConfigCommon::preambleInfo::preamblesGroupAConfig::sizeOfRA_PreamblesGroupA_Enum)0;
}

int RACH_ConfigCommon::preambleInfo::preamblesGroupAConfig::sizeOfRA_PreamblesGroupA_SetValue(sizeOfRA_PreamblesGroupA_Enum value)
{
    sizeOfRA_PreamblesGroupA_internal_value = value;
    sizeOfRA_PreamblesGroupA_present = true;
    return 0;
}

int RACH_ConfigCommon::preambleInfo::preamblesGroupAConfig::sizeOfRA_PreamblesGroupA_SetValue(std::string value)
{
    if("n4" == value)
    {
        sizeOfRA_PreamblesGroupA_internal_value = k_sizeOfRA_PreamblesGroupA_n4;
        sizeOfRA_PreamblesGroupA_present = true;
        return 0;
    }
    if("n8" == value)
    {
        sizeOfRA_PreamblesGroupA_internal_value = k_sizeOfRA_PreamblesGroupA_n8;
        sizeOfRA_PreamblesGroupA_present = true;
        return 0;
    }
    if("n12" == value)
    {
        sizeOfRA_PreamblesGroupA_internal_value = k_sizeOfRA_PreamblesGroupA_n12;
        sizeOfRA_PreamblesGroupA_present = true;
        return 0;
    }
    if("n16" == value)
    {
        sizeOfRA_PreamblesGroupA_internal_value = k_sizeOfRA_PreamblesGroupA_n16;
        sizeOfRA_PreamblesGroupA_present = true;
        return 0;
    }
    if("n20" == value)
    {
        sizeOfRA_PreamblesGroupA_internal_value = k_sizeOfRA_PreamblesGroupA_n20;
        sizeOfRA_PreamblesGroupA_present = true;
        return 0;
    }
    if("n24" == value)
    {
        sizeOfRA_PreamblesGroupA_internal_value = k_sizeOfRA_PreamblesGroupA_n24;
        sizeOfRA_PreamblesGroupA_present = true;
        return 0;
    }
    if("n28" == value)
    {
        sizeOfRA_PreamblesGroupA_internal_value = k_sizeOfRA_PreamblesGroupA_n28;
        sizeOfRA_PreamblesGroupA_present = true;
        return 0;
    }
    if("n32" == value)
    {
        sizeOfRA_PreamblesGroupA_internal_value = k_sizeOfRA_PreamblesGroupA_n32;
        sizeOfRA_PreamblesGroupA_present = true;
        return 0;
    }
    if("n36" == value)
    {
        sizeOfRA_PreamblesGroupA_internal_value = k_sizeOfRA_PreamblesGroupA_n36;
        sizeOfRA_PreamblesGroupA_present = true;
        return 0;
    }
    if("n40" == value)
    {
        sizeOfRA_PreamblesGroupA_internal_value = k_sizeOfRA_PreamblesGroupA_n40;
        sizeOfRA_PreamblesGroupA_present = true;
        return 0;
    }
    if("n44" == value)
    {
        sizeOfRA_PreamblesGroupA_internal_value = k_sizeOfRA_PreamblesGroupA_n44;
        sizeOfRA_PreamblesGroupA_present = true;
        return 0;
    }
    if("n48" == value)
    {
        sizeOfRA_PreamblesGroupA_internal_value = k_sizeOfRA_PreamblesGroupA_n48;
        sizeOfRA_PreamblesGroupA_present = true;
        return 0;
    }
    if("n52" == value)
    {
        sizeOfRA_PreamblesGroupA_internal_value = k_sizeOfRA_PreamblesGroupA_n52;
        sizeOfRA_PreamblesGroupA_present = true;
        return 0;
    }
    if("n56" == value)
    {
        sizeOfRA_PreamblesGroupA_internal_value = k_sizeOfRA_PreamblesGroupA_n56;
        sizeOfRA_PreamblesGroupA_present = true;
        return 0;
    }
    if("n60" == value)
    {
        sizeOfRA_PreamblesGroupA_internal_value = k_sizeOfRA_PreamblesGroupA_n60;
        sizeOfRA_PreamblesGroupA_present = true;
        return 0;
    }
    return 1;
}

std::string RACH_ConfigCommon::preambleInfo::preamblesGroupAConfig::sizeOfRA_PreamblesGroupA_ValueToString(sizeOfRA_PreamblesGroupA_Enum value) const
{
    if(k_sizeOfRA_PreamblesGroupA_n4 == value)
        return "n4";
    if(k_sizeOfRA_PreamblesGroupA_n8 == value)
        return "n8";
    if(k_sizeOfRA_PreamblesGroupA_n12 == value)
        return "n12";
    if(k_sizeOfRA_PreamblesGroupA_n16 == value)
        return "n16";
    if(k_sizeOfRA_PreamblesGroupA_n20 == value)
        return "n20";
    if(k_sizeOfRA_PreamblesGroupA_n24 == value)
        return "n24";
    if(k_sizeOfRA_PreamblesGroupA_n28 == value)
        return "n28";
    if(k_sizeOfRA_PreamblesGroupA_n32 == value)
        return "n32";
    if(k_sizeOfRA_PreamblesGroupA_n36 == value)
        return "n36";
    if(k_sizeOfRA_PreamblesGroupA_n40 == value)
        return "n40";
    if(k_sizeOfRA_PreamblesGroupA_n44 == value)
        return "n44";
    if(k_sizeOfRA_PreamblesGroupA_n48 == value)
        return "n48";
    if(k_sizeOfRA_PreamblesGroupA_n52 == value)
        return "n52";
    if(k_sizeOfRA_PreamblesGroupA_n56 == value)
        return "n56";
    if(k_sizeOfRA_PreamblesGroupA_n60 == value)
        return "n60";
    return "";
}

uint64_t RACH_ConfigCommon::preambleInfo::preamblesGroupAConfig::sizeOfRA_PreamblesGroupA_NumberOfValues() const
{
    return 15;
}

std::string RACH_ConfigCommon::preambleInfo::preamblesGroupAConfig::sizeOfRA_PreamblesGroupA_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "sizeOfRA_PreamblesGroupA = " + sizeOfRA_PreamblesGroupA_ValueToString(sizeOfRA_PreamblesGroupA_internal_value) + "\n";
    return out;
}

std::string RACH_ConfigCommon::preambleInfo::preamblesGroupAConfig::sizeOfRA_PreamblesGroupA_ToStringNoNewLines() const
{
    std::string out = "sizeOfRA_PreamblesGroupA=" + sizeOfRA_PreamblesGroupA_ValueToString(sizeOfRA_PreamblesGroupA_internal_value) + ",";
    return out;
}

int RACH_ConfigCommon::preambleInfo::preamblesGroupAConfig::sizeOfRA_PreamblesGroupA_Clear()
{
    sizeOfRA_PreamblesGroupA_present = false;
    return 0;
}

bool RACH_ConfigCommon::preambleInfo::preamblesGroupAConfig::sizeOfRA_PreamblesGroupA_IsPresent() const
{
    return sizeOfRA_PreamblesGroupA_present;
}

int RACH_ConfigCommon::preambleInfo::preamblesGroupAConfig::messageSizeGroupA_Pack(std::vector<uint8_t> &bits)
{
    if(!messageSizeGroupA_present)
    {
        printf("RACH_ConfigCommon::preambleInfo::preamblesGroupAConfig::messageSizeGroupA_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 2;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((messageSizeGroupA_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int RACH_ConfigCommon::preambleInfo::preamblesGroupAConfig::messageSizeGroupA_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return messageSizeGroupA_Unpack(bits, idx);
}

int RACH_ConfigCommon::preambleInfo::preamblesGroupAConfig::messageSizeGroupA_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 2;
    if((idx + N_bits) > bits.size())
    {
        printf("RACH_ConfigCommon::preambleInfo::preamblesGroupAConfig::messageSizeGroupA_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 3)
    {
        printf("RACH_ConfigCommon::preambleInfo::preamblesGroupAConfig::messageSizeGroupA_Unpack() max failure\n");
        return -1;
    }
    messageSizeGroupA_internal_value = (messageSizeGroupA_Enum)packed_val;
    messageSizeGroupA_present = true;
    return 0;
}

RACH_ConfigCommon::preambleInfo::preamblesGroupAConfig::messageSizeGroupA_Enum RACH_ConfigCommon::preambleInfo::preamblesGroupAConfig::messageSizeGroupA_Value() const
{
    if(messageSizeGroupA_present)
        return messageSizeGroupA_internal_value;
    return (RACH_ConfigCommon::preambleInfo::preamblesGroupAConfig::messageSizeGroupA_Enum)0;
}

int RACH_ConfigCommon::preambleInfo::preamblesGroupAConfig::messageSizeGroupA_SetValue(messageSizeGroupA_Enum value)
{
    messageSizeGroupA_internal_value = value;
    messageSizeGroupA_present = true;
    return 0;
}

int RACH_ConfigCommon::preambleInfo::preamblesGroupAConfig::messageSizeGroupA_SetValue(std::string value)
{
    if("b56" == value)
    {
        messageSizeGroupA_internal_value = k_messageSizeGroupA_b56;
        messageSizeGroupA_present = true;
        return 0;
    }
    if("b144" == value)
    {
        messageSizeGroupA_internal_value = k_messageSizeGroupA_b144;
        messageSizeGroupA_present = true;
        return 0;
    }
    if("b208" == value)
    {
        messageSizeGroupA_internal_value = k_messageSizeGroupA_b208;
        messageSizeGroupA_present = true;
        return 0;
    }
    if("b256" == value)
    {
        messageSizeGroupA_internal_value = k_messageSizeGroupA_b256;
        messageSizeGroupA_present = true;
        return 0;
    }
    return 1;
}

std::string RACH_ConfigCommon::preambleInfo::preamblesGroupAConfig::messageSizeGroupA_ValueToString(messageSizeGroupA_Enum value) const
{
    if(k_messageSizeGroupA_b56 == value)
        return "b56";
    if(k_messageSizeGroupA_b144 == value)
        return "b144";
    if(k_messageSizeGroupA_b208 == value)
        return "b208";
    if(k_messageSizeGroupA_b256 == value)
        return "b256";
    return "";
}

uint64_t RACH_ConfigCommon::preambleInfo::preamblesGroupAConfig::messageSizeGroupA_NumberOfValues() const
{
    return 4;
}

std::string RACH_ConfigCommon::preambleInfo::preamblesGroupAConfig::messageSizeGroupA_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "messageSizeGroupA = " + messageSizeGroupA_ValueToString(messageSizeGroupA_internal_value) + "\n";
    return out;
}

std::string RACH_ConfigCommon::preambleInfo::preamblesGroupAConfig::messageSizeGroupA_ToStringNoNewLines() const
{
    std::string out = "messageSizeGroupA=" + messageSizeGroupA_ValueToString(messageSizeGroupA_internal_value) + ",";
    return out;
}

int RACH_ConfigCommon::preambleInfo::preamblesGroupAConfig::messageSizeGroupA_Clear()
{
    messageSizeGroupA_present = false;
    return 0;
}

bool RACH_ConfigCommon::preambleInfo::preamblesGroupAConfig::messageSizeGroupA_IsPresent() const
{
    return messageSizeGroupA_present;
}

int RACH_ConfigCommon::preambleInfo::preamblesGroupAConfig::messagePowerOffsetGroupB_Pack(std::vector<uint8_t> &bits)
{
    if(!messagePowerOffsetGroupB_present)
    {
        printf("RACH_ConfigCommon::preambleInfo::preamblesGroupAConfig::messagePowerOffsetGroupB_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 3;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((messagePowerOffsetGroupB_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int RACH_ConfigCommon::preambleInfo::preamblesGroupAConfig::messagePowerOffsetGroupB_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return messagePowerOffsetGroupB_Unpack(bits, idx);
}

int RACH_ConfigCommon::preambleInfo::preamblesGroupAConfig::messagePowerOffsetGroupB_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 3;
    if((idx + N_bits) > bits.size())
    {
        printf("RACH_ConfigCommon::preambleInfo::preamblesGroupAConfig::messagePowerOffsetGroupB_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 7)
    {
        printf("RACH_ConfigCommon::preambleInfo::preamblesGroupAConfig::messagePowerOffsetGroupB_Unpack() max failure\n");
        return -1;
    }
    messagePowerOffsetGroupB_internal_value = (messagePowerOffsetGroupB_Enum)packed_val;
    messagePowerOffsetGroupB_present = true;
    return 0;
}

RACH_ConfigCommon::preambleInfo::preamblesGroupAConfig::messagePowerOffsetGroupB_Enum RACH_ConfigCommon::preambleInfo::preamblesGroupAConfig::messagePowerOffsetGroupB_Value() const
{
    if(messagePowerOffsetGroupB_present)
        return messagePowerOffsetGroupB_internal_value;
    return (RACH_ConfigCommon::preambleInfo::preamblesGroupAConfig::messagePowerOffsetGroupB_Enum)0;
}

int RACH_ConfigCommon::preambleInfo::preamblesGroupAConfig::messagePowerOffsetGroupB_SetValue(messagePowerOffsetGroupB_Enum value)
{
    messagePowerOffsetGroupB_internal_value = value;
    messagePowerOffsetGroupB_present = true;
    return 0;
}

int RACH_ConfigCommon::preambleInfo::preamblesGroupAConfig::messagePowerOffsetGroupB_SetValue(std::string value)
{
    if("minusinfinity" == value)
    {
        messagePowerOffsetGroupB_internal_value = k_messagePowerOffsetGroupB_minusinfinity;
        messagePowerOffsetGroupB_present = true;
        return 0;
    }
    if("dB0" == value)
    {
        messagePowerOffsetGroupB_internal_value = k_messagePowerOffsetGroupB_dB0;
        messagePowerOffsetGroupB_present = true;
        return 0;
    }
    if("dB5" == value)
    {
        messagePowerOffsetGroupB_internal_value = k_messagePowerOffsetGroupB_dB5;
        messagePowerOffsetGroupB_present = true;
        return 0;
    }
    if("dB8" == value)
    {
        messagePowerOffsetGroupB_internal_value = k_messagePowerOffsetGroupB_dB8;
        messagePowerOffsetGroupB_present = true;
        return 0;
    }
    if("dB10" == value)
    {
        messagePowerOffsetGroupB_internal_value = k_messagePowerOffsetGroupB_dB10;
        messagePowerOffsetGroupB_present = true;
        return 0;
    }
    if("dB12" == value)
    {
        messagePowerOffsetGroupB_internal_value = k_messagePowerOffsetGroupB_dB12;
        messagePowerOffsetGroupB_present = true;
        return 0;
    }
    if("dB15" == value)
    {
        messagePowerOffsetGroupB_internal_value = k_messagePowerOffsetGroupB_dB15;
        messagePowerOffsetGroupB_present = true;
        return 0;
    }
    if("dB18" == value)
    {
        messagePowerOffsetGroupB_internal_value = k_messagePowerOffsetGroupB_dB18;
        messagePowerOffsetGroupB_present = true;
        return 0;
    }
    return 1;
}

std::string RACH_ConfigCommon::preambleInfo::preamblesGroupAConfig::messagePowerOffsetGroupB_ValueToString(messagePowerOffsetGroupB_Enum value) const
{
    if(k_messagePowerOffsetGroupB_minusinfinity == value)
        return "minusinfinity";
    if(k_messagePowerOffsetGroupB_dB0 == value)
        return "dB0";
    if(k_messagePowerOffsetGroupB_dB5 == value)
        return "dB5";
    if(k_messagePowerOffsetGroupB_dB8 == value)
        return "dB8";
    if(k_messagePowerOffsetGroupB_dB10 == value)
        return "dB10";
    if(k_messagePowerOffsetGroupB_dB12 == value)
        return "dB12";
    if(k_messagePowerOffsetGroupB_dB15 == value)
        return "dB15";
    if(k_messagePowerOffsetGroupB_dB18 == value)
        return "dB18";
    return "";
}

uint64_t RACH_ConfigCommon::preambleInfo::preamblesGroupAConfig::messagePowerOffsetGroupB_NumberOfValues() const
{
    return 8;
}

std::string RACH_ConfigCommon::preambleInfo::preamblesGroupAConfig::messagePowerOffsetGroupB_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "messagePowerOffsetGroupB = " + messagePowerOffsetGroupB_ValueToString(messagePowerOffsetGroupB_internal_value) + "\n";
    return out;
}

std::string RACH_ConfigCommon::preambleInfo::preamblesGroupAConfig::messagePowerOffsetGroupB_ToStringNoNewLines() const
{
    std::string out = "messagePowerOffsetGroupB=" + messagePowerOffsetGroupB_ValueToString(messagePowerOffsetGroupB_internal_value) + ",";
    return out;
}

int RACH_ConfigCommon::preambleInfo::preamblesGroupAConfig::messagePowerOffsetGroupB_Clear()
{
    messagePowerOffsetGroupB_present = false;
    return 0;
}

bool RACH_ConfigCommon::preambleInfo::preamblesGroupAConfig::messagePowerOffsetGroupB_IsPresent() const
{
    return messagePowerOffsetGroupB_present;
}

int RACH_ConfigCommon::powerRampingParameters::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != powerRampingStep_Pack(bits))
        {
            printf("RACH_ConfigCommon::powerRampingParameters:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != preambleInitialReceivedTargetPower_Pack(bits))
        {
            printf("RACH_ConfigCommon::powerRampingParameters:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int RACH_ConfigCommon::powerRampingParameters::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int RACH_ConfigCommon::powerRampingParameters::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != powerRampingStep_Unpack(bits, idx))
        {
            printf("RACH_ConfigCommon::powerRampingParameters:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != preambleInitialReceivedTargetPower_Unpack(bits, idx))
        {
            printf("RACH_ConfigCommon::powerRampingParameters:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string RACH_ConfigCommon::powerRampingParameters::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "powerRampingParameters:\n";
    out += powerRampingStep_ToString(indent+1);
    out += preambleInitialReceivedTargetPower_ToString(indent+1);
    return out;
}

std::string RACH_ConfigCommon::powerRampingParameters::ToStringNoNewLines() const
{
    std::string out = "powerRampingParameters:";
    out += powerRampingStep_ToStringNoNewLines();
    out += preambleInitialReceivedTargetPower_ToStringNoNewLines();
    return out;
}

int RACH_ConfigCommon::powerRampingParameters::powerRampingStep_Pack(std::vector<uint8_t> &bits)
{
    if(!powerRampingStep_present)
    {
        printf("RACH_ConfigCommon::powerRampingParameters::powerRampingStep_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 2;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((powerRampingStep_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int RACH_ConfigCommon::powerRampingParameters::powerRampingStep_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return powerRampingStep_Unpack(bits, idx);
}

int RACH_ConfigCommon::powerRampingParameters::powerRampingStep_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 2;
    if((idx + N_bits) > bits.size())
    {
        printf("RACH_ConfigCommon::powerRampingParameters::powerRampingStep_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 3)
    {
        printf("RACH_ConfigCommon::powerRampingParameters::powerRampingStep_Unpack() max failure\n");
        return -1;
    }
    powerRampingStep_internal_value = (powerRampingStep_Enum)packed_val;
    powerRampingStep_present = true;
    return 0;
}

RACH_ConfigCommon::powerRampingParameters::powerRampingStep_Enum RACH_ConfigCommon::powerRampingParameters::powerRampingStep_Value() const
{
    if(powerRampingStep_present)
        return powerRampingStep_internal_value;
    return (RACH_ConfigCommon::powerRampingParameters::powerRampingStep_Enum)0;
}

int RACH_ConfigCommon::powerRampingParameters::powerRampingStep_SetValue(powerRampingStep_Enum value)
{
    powerRampingStep_internal_value = value;
    powerRampingStep_present = true;
    return 0;
}

int RACH_ConfigCommon::powerRampingParameters::powerRampingStep_SetValue(std::string value)
{
    if("dB0" == value)
    {
        powerRampingStep_internal_value = k_powerRampingStep_dB0;
        powerRampingStep_present = true;
        return 0;
    }
    if("dB2" == value)
    {
        powerRampingStep_internal_value = k_powerRampingStep_dB2;
        powerRampingStep_present = true;
        return 0;
    }
    if("dB4" == value)
    {
        powerRampingStep_internal_value = k_powerRampingStep_dB4;
        powerRampingStep_present = true;
        return 0;
    }
    if("dB6" == value)
    {
        powerRampingStep_internal_value = k_powerRampingStep_dB6;
        powerRampingStep_present = true;
        return 0;
    }
    return 1;
}

std::string RACH_ConfigCommon::powerRampingParameters::powerRampingStep_ValueToString(powerRampingStep_Enum value) const
{
    if(k_powerRampingStep_dB0 == value)
        return "dB0";
    if(k_powerRampingStep_dB2 == value)
        return "dB2";
    if(k_powerRampingStep_dB4 == value)
        return "dB4";
    if(k_powerRampingStep_dB6 == value)
        return "dB6";
    return "";
}

uint64_t RACH_ConfigCommon::powerRampingParameters::powerRampingStep_NumberOfValues() const
{
    return 4;
}

std::string RACH_ConfigCommon::powerRampingParameters::powerRampingStep_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "powerRampingStep = " + powerRampingStep_ValueToString(powerRampingStep_internal_value) + "\n";
    return out;
}

std::string RACH_ConfigCommon::powerRampingParameters::powerRampingStep_ToStringNoNewLines() const
{
    std::string out = "powerRampingStep=" + powerRampingStep_ValueToString(powerRampingStep_internal_value) + ",";
    return out;
}

int RACH_ConfigCommon::powerRampingParameters::powerRampingStep_Clear()
{
    powerRampingStep_present = false;
    return 0;
}

bool RACH_ConfigCommon::powerRampingParameters::powerRampingStep_IsPresent() const
{
    return powerRampingStep_present;
}

int RACH_ConfigCommon::powerRampingParameters::preambleInitialReceivedTargetPower_Pack(std::vector<uint8_t> &bits)
{
    if(!preambleInitialReceivedTargetPower_present)
    {
        printf("RACH_ConfigCommon::powerRampingParameters::preambleInitialReceivedTargetPower_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 4;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((preambleInitialReceivedTargetPower_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int RACH_ConfigCommon::powerRampingParameters::preambleInitialReceivedTargetPower_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return preambleInitialReceivedTargetPower_Unpack(bits, idx);
}

int RACH_ConfigCommon::powerRampingParameters::preambleInitialReceivedTargetPower_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 4;
    if((idx + N_bits) > bits.size())
    {
        printf("RACH_ConfigCommon::powerRampingParameters::preambleInitialReceivedTargetPower_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 15)
    {
        printf("RACH_ConfigCommon::powerRampingParameters::preambleInitialReceivedTargetPower_Unpack() max failure\n");
        return -1;
    }
    preambleInitialReceivedTargetPower_internal_value = (preambleInitialReceivedTargetPower_Enum)packed_val;
    preambleInitialReceivedTargetPower_present = true;
    return 0;
}

RACH_ConfigCommon::powerRampingParameters::preambleInitialReceivedTargetPower_Enum RACH_ConfigCommon::powerRampingParameters::preambleInitialReceivedTargetPower_Value() const
{
    if(preambleInitialReceivedTargetPower_present)
        return preambleInitialReceivedTargetPower_internal_value;
    return (RACH_ConfigCommon::powerRampingParameters::preambleInitialReceivedTargetPower_Enum)0;
}

int RACH_ConfigCommon::powerRampingParameters::preambleInitialReceivedTargetPower_SetValue(preambleInitialReceivedTargetPower_Enum value)
{
    preambleInitialReceivedTargetPower_internal_value = value;
    preambleInitialReceivedTargetPower_present = true;
    return 0;
}

int RACH_ConfigCommon::powerRampingParameters::preambleInitialReceivedTargetPower_SetValue(std::string value)
{
    if("dBm_120" == value)
    {
        preambleInitialReceivedTargetPower_internal_value = k_preambleInitialReceivedTargetPower_dBm_120;
        preambleInitialReceivedTargetPower_present = true;
        return 0;
    }
    if("dBm_118" == value)
    {
        preambleInitialReceivedTargetPower_internal_value = k_preambleInitialReceivedTargetPower_dBm_118;
        preambleInitialReceivedTargetPower_present = true;
        return 0;
    }
    if("dBm_116" == value)
    {
        preambleInitialReceivedTargetPower_internal_value = k_preambleInitialReceivedTargetPower_dBm_116;
        preambleInitialReceivedTargetPower_present = true;
        return 0;
    }
    if("dBm_114" == value)
    {
        preambleInitialReceivedTargetPower_internal_value = k_preambleInitialReceivedTargetPower_dBm_114;
        preambleInitialReceivedTargetPower_present = true;
        return 0;
    }
    if("dBm_112" == value)
    {
        preambleInitialReceivedTargetPower_internal_value = k_preambleInitialReceivedTargetPower_dBm_112;
        preambleInitialReceivedTargetPower_present = true;
        return 0;
    }
    if("dBm_110" == value)
    {
        preambleInitialReceivedTargetPower_internal_value = k_preambleInitialReceivedTargetPower_dBm_110;
        preambleInitialReceivedTargetPower_present = true;
        return 0;
    }
    if("dBm_108" == value)
    {
        preambleInitialReceivedTargetPower_internal_value = k_preambleInitialReceivedTargetPower_dBm_108;
        preambleInitialReceivedTargetPower_present = true;
        return 0;
    }
    if("dBm_106" == value)
    {
        preambleInitialReceivedTargetPower_internal_value = k_preambleInitialReceivedTargetPower_dBm_106;
        preambleInitialReceivedTargetPower_present = true;
        return 0;
    }
    if("dBm_104" == value)
    {
        preambleInitialReceivedTargetPower_internal_value = k_preambleInitialReceivedTargetPower_dBm_104;
        preambleInitialReceivedTargetPower_present = true;
        return 0;
    }
    if("dBm_102" == value)
    {
        preambleInitialReceivedTargetPower_internal_value = k_preambleInitialReceivedTargetPower_dBm_102;
        preambleInitialReceivedTargetPower_present = true;
        return 0;
    }
    if("dBm_100" == value)
    {
        preambleInitialReceivedTargetPower_internal_value = k_preambleInitialReceivedTargetPower_dBm_100;
        preambleInitialReceivedTargetPower_present = true;
        return 0;
    }
    if("dBm_98" == value)
    {
        preambleInitialReceivedTargetPower_internal_value = k_preambleInitialReceivedTargetPower_dBm_98;
        preambleInitialReceivedTargetPower_present = true;
        return 0;
    }
    if("dBm_96" == value)
    {
        preambleInitialReceivedTargetPower_internal_value = k_preambleInitialReceivedTargetPower_dBm_96;
        preambleInitialReceivedTargetPower_present = true;
        return 0;
    }
    if("dBm_94" == value)
    {
        preambleInitialReceivedTargetPower_internal_value = k_preambleInitialReceivedTargetPower_dBm_94;
        preambleInitialReceivedTargetPower_present = true;
        return 0;
    }
    if("dBm_92" == value)
    {
        preambleInitialReceivedTargetPower_internal_value = k_preambleInitialReceivedTargetPower_dBm_92;
        preambleInitialReceivedTargetPower_present = true;
        return 0;
    }
    if("dBm_90" == value)
    {
        preambleInitialReceivedTargetPower_internal_value = k_preambleInitialReceivedTargetPower_dBm_90;
        preambleInitialReceivedTargetPower_present = true;
        return 0;
    }
    return 1;
}

std::string RACH_ConfigCommon::powerRampingParameters::preambleInitialReceivedTargetPower_ValueToString(preambleInitialReceivedTargetPower_Enum value) const
{
    if(k_preambleInitialReceivedTargetPower_dBm_120 == value)
        return "dBm_120";
    if(k_preambleInitialReceivedTargetPower_dBm_118 == value)
        return "dBm_118";
    if(k_preambleInitialReceivedTargetPower_dBm_116 == value)
        return "dBm_116";
    if(k_preambleInitialReceivedTargetPower_dBm_114 == value)
        return "dBm_114";
    if(k_preambleInitialReceivedTargetPower_dBm_112 == value)
        return "dBm_112";
    if(k_preambleInitialReceivedTargetPower_dBm_110 == value)
        return "dBm_110";
    if(k_preambleInitialReceivedTargetPower_dBm_108 == value)
        return "dBm_108";
    if(k_preambleInitialReceivedTargetPower_dBm_106 == value)
        return "dBm_106";
    if(k_preambleInitialReceivedTargetPower_dBm_104 == value)
        return "dBm_104";
    if(k_preambleInitialReceivedTargetPower_dBm_102 == value)
        return "dBm_102";
    if(k_preambleInitialReceivedTargetPower_dBm_100 == value)
        return "dBm_100";
    if(k_preambleInitialReceivedTargetPower_dBm_98 == value)
        return "dBm_98";
    if(k_preambleInitialReceivedTargetPower_dBm_96 == value)
        return "dBm_96";
    if(k_preambleInitialReceivedTargetPower_dBm_94 == value)
        return "dBm_94";
    if(k_preambleInitialReceivedTargetPower_dBm_92 == value)
        return "dBm_92";
    if(k_preambleInitialReceivedTargetPower_dBm_90 == value)
        return "dBm_90";
    return "";
}

uint64_t RACH_ConfigCommon::powerRampingParameters::preambleInitialReceivedTargetPower_NumberOfValues() const
{
    return 16;
}

std::string RACH_ConfigCommon::powerRampingParameters::preambleInitialReceivedTargetPower_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "preambleInitialReceivedTargetPower = " + preambleInitialReceivedTargetPower_ValueToString(preambleInitialReceivedTargetPower_internal_value) + "\n";
    return out;
}

std::string RACH_ConfigCommon::powerRampingParameters::preambleInitialReceivedTargetPower_ToStringNoNewLines() const
{
    std::string out = "preambleInitialReceivedTargetPower=" + preambleInitialReceivedTargetPower_ValueToString(preambleInitialReceivedTargetPower_internal_value) + ",";
    return out;
}

int RACH_ConfigCommon::powerRampingParameters::preambleInitialReceivedTargetPower_Clear()
{
    preambleInitialReceivedTargetPower_present = false;
    return 0;
}

bool RACH_ConfigCommon::powerRampingParameters::preambleInitialReceivedTargetPower_IsPresent() const
{
    return preambleInitialReceivedTargetPower_present;
}

int RACH_ConfigCommon::ra_SupervisionInfo::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != preambleTransMax_Pack(bits))
        {
            printf("RACH_ConfigCommon::ra_SupervisionInfo:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != ra_ResponseWindowSize_Pack(bits))
        {
            printf("RACH_ConfigCommon::ra_SupervisionInfo:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != mac_ContentionResolutionTimer_Pack(bits))
        {
            printf("RACH_ConfigCommon::ra_SupervisionInfo:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int RACH_ConfigCommon::ra_SupervisionInfo::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int RACH_ConfigCommon::ra_SupervisionInfo::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != preambleTransMax_Unpack(bits, idx))
        {
            printf("RACH_ConfigCommon::ra_SupervisionInfo:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != ra_ResponseWindowSize_Unpack(bits, idx))
        {
            printf("RACH_ConfigCommon::ra_SupervisionInfo:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != mac_ContentionResolutionTimer_Unpack(bits, idx))
        {
            printf("RACH_ConfigCommon::ra_SupervisionInfo:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string RACH_ConfigCommon::ra_SupervisionInfo::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ra_SupervisionInfo:\n";
    out += preambleTransMax_ToString(indent+1);
    out += ra_ResponseWindowSize_ToString(indent+1);
    out += mac_ContentionResolutionTimer_ToString(indent+1);
    return out;
}

std::string RACH_ConfigCommon::ra_SupervisionInfo::ToStringNoNewLines() const
{
    std::string out = "ra_SupervisionInfo:";
    out += preambleTransMax_ToStringNoNewLines();
    out += ra_ResponseWindowSize_ToStringNoNewLines();
    out += mac_ContentionResolutionTimer_ToStringNoNewLines();
    return out;
}

int RACH_ConfigCommon::ra_SupervisionInfo::preambleTransMax_Pack(std::vector<uint8_t> &bits)
{
    if(!preambleTransMax_present)
    {
        printf("RACH_ConfigCommon::ra_SupervisionInfo::preambleTransMax_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 4;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((preambleTransMax_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int RACH_ConfigCommon::ra_SupervisionInfo::preambleTransMax_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return preambleTransMax_Unpack(bits, idx);
}

int RACH_ConfigCommon::ra_SupervisionInfo::preambleTransMax_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 4;
    if((idx + N_bits) > bits.size())
    {
        printf("RACH_ConfigCommon::ra_SupervisionInfo::preambleTransMax_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 10)
    {
        printf("RACH_ConfigCommon::ra_SupervisionInfo::preambleTransMax_Unpack() max failure\n");
        return -1;
    }
    preambleTransMax_internal_value = (preambleTransMax_Enum)packed_val;
    preambleTransMax_present = true;
    return 0;
}

RACH_ConfigCommon::ra_SupervisionInfo::preambleTransMax_Enum RACH_ConfigCommon::ra_SupervisionInfo::preambleTransMax_Value() const
{
    if(preambleTransMax_present)
        return preambleTransMax_internal_value;
    return (RACH_ConfigCommon::ra_SupervisionInfo::preambleTransMax_Enum)0;
}

int RACH_ConfigCommon::ra_SupervisionInfo::preambleTransMax_SetValue(preambleTransMax_Enum value)
{
    preambleTransMax_internal_value = value;
    preambleTransMax_present = true;
    return 0;
}

int RACH_ConfigCommon::ra_SupervisionInfo::preambleTransMax_SetValue(std::string value)
{
    if("n3" == value)
    {
        preambleTransMax_internal_value = k_preambleTransMax_n3;
        preambleTransMax_present = true;
        return 0;
    }
    if("n4" == value)
    {
        preambleTransMax_internal_value = k_preambleTransMax_n4;
        preambleTransMax_present = true;
        return 0;
    }
    if("n5" == value)
    {
        preambleTransMax_internal_value = k_preambleTransMax_n5;
        preambleTransMax_present = true;
        return 0;
    }
    if("n6" == value)
    {
        preambleTransMax_internal_value = k_preambleTransMax_n6;
        preambleTransMax_present = true;
        return 0;
    }
    if("n7" == value)
    {
        preambleTransMax_internal_value = k_preambleTransMax_n7;
        preambleTransMax_present = true;
        return 0;
    }
    if("n8" == value)
    {
        preambleTransMax_internal_value = k_preambleTransMax_n8;
        preambleTransMax_present = true;
        return 0;
    }
    if("n10" == value)
    {
        preambleTransMax_internal_value = k_preambleTransMax_n10;
        preambleTransMax_present = true;
        return 0;
    }
    if("n20" == value)
    {
        preambleTransMax_internal_value = k_preambleTransMax_n20;
        preambleTransMax_present = true;
        return 0;
    }
    if("n50" == value)
    {
        preambleTransMax_internal_value = k_preambleTransMax_n50;
        preambleTransMax_present = true;
        return 0;
    }
    if("n100" == value)
    {
        preambleTransMax_internal_value = k_preambleTransMax_n100;
        preambleTransMax_present = true;
        return 0;
    }
    if("n200" == value)
    {
        preambleTransMax_internal_value = k_preambleTransMax_n200;
        preambleTransMax_present = true;
        return 0;
    }
    return 1;
}

std::string RACH_ConfigCommon::ra_SupervisionInfo::preambleTransMax_ValueToString(preambleTransMax_Enum value) const
{
    if(k_preambleTransMax_n3 == value)
        return "n3";
    if(k_preambleTransMax_n4 == value)
        return "n4";
    if(k_preambleTransMax_n5 == value)
        return "n5";
    if(k_preambleTransMax_n6 == value)
        return "n6";
    if(k_preambleTransMax_n7 == value)
        return "n7";
    if(k_preambleTransMax_n8 == value)
        return "n8";
    if(k_preambleTransMax_n10 == value)
        return "n10";
    if(k_preambleTransMax_n20 == value)
        return "n20";
    if(k_preambleTransMax_n50 == value)
        return "n50";
    if(k_preambleTransMax_n100 == value)
        return "n100";
    if(k_preambleTransMax_n200 == value)
        return "n200";
    return "";
}

uint64_t RACH_ConfigCommon::ra_SupervisionInfo::preambleTransMax_NumberOfValues() const
{
    return 11;
}

std::string RACH_ConfigCommon::ra_SupervisionInfo::preambleTransMax_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "preambleTransMax = " + preambleTransMax_ValueToString(preambleTransMax_internal_value) + "\n";
    return out;
}

std::string RACH_ConfigCommon::ra_SupervisionInfo::preambleTransMax_ToStringNoNewLines() const
{
    std::string out = "preambleTransMax=" + preambleTransMax_ValueToString(preambleTransMax_internal_value) + ",";
    return out;
}

int RACH_ConfigCommon::ra_SupervisionInfo::preambleTransMax_Clear()
{
    preambleTransMax_present = false;
    return 0;
}

bool RACH_ConfigCommon::ra_SupervisionInfo::preambleTransMax_IsPresent() const
{
    return preambleTransMax_present;
}

int RACH_ConfigCommon::ra_SupervisionInfo::ra_ResponseWindowSize_Pack(std::vector<uint8_t> &bits)
{
    if(!ra_ResponseWindowSize_present)
    {
        printf("RACH_ConfigCommon::ra_SupervisionInfo::ra_ResponseWindowSize_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 3;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((ra_ResponseWindowSize_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int RACH_ConfigCommon::ra_SupervisionInfo::ra_ResponseWindowSize_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return ra_ResponseWindowSize_Unpack(bits, idx);
}

int RACH_ConfigCommon::ra_SupervisionInfo::ra_ResponseWindowSize_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 3;
    if((idx + N_bits) > bits.size())
    {
        printf("RACH_ConfigCommon::ra_SupervisionInfo::ra_ResponseWindowSize_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 7)
    {
        printf("RACH_ConfigCommon::ra_SupervisionInfo::ra_ResponseWindowSize_Unpack() max failure\n");
        return -1;
    }
    ra_ResponseWindowSize_internal_value = (ra_ResponseWindowSize_Enum)packed_val;
    ra_ResponseWindowSize_present = true;
    return 0;
}

RACH_ConfigCommon::ra_SupervisionInfo::ra_ResponseWindowSize_Enum RACH_ConfigCommon::ra_SupervisionInfo::ra_ResponseWindowSize_Value() const
{
    if(ra_ResponseWindowSize_present)
        return ra_ResponseWindowSize_internal_value;
    return (RACH_ConfigCommon::ra_SupervisionInfo::ra_ResponseWindowSize_Enum)0;
}

int RACH_ConfigCommon::ra_SupervisionInfo::ra_ResponseWindowSize_SetValue(ra_ResponseWindowSize_Enum value)
{
    ra_ResponseWindowSize_internal_value = value;
    ra_ResponseWindowSize_present = true;
    return 0;
}

int RACH_ConfigCommon::ra_SupervisionInfo::ra_ResponseWindowSize_SetValue(std::string value)
{
    if("sf2" == value)
    {
        ra_ResponseWindowSize_internal_value = k_ra_ResponseWindowSize_sf2;
        ra_ResponseWindowSize_present = true;
        return 0;
    }
    if("sf3" == value)
    {
        ra_ResponseWindowSize_internal_value = k_ra_ResponseWindowSize_sf3;
        ra_ResponseWindowSize_present = true;
        return 0;
    }
    if("sf4" == value)
    {
        ra_ResponseWindowSize_internal_value = k_ra_ResponseWindowSize_sf4;
        ra_ResponseWindowSize_present = true;
        return 0;
    }
    if("sf5" == value)
    {
        ra_ResponseWindowSize_internal_value = k_ra_ResponseWindowSize_sf5;
        ra_ResponseWindowSize_present = true;
        return 0;
    }
    if("sf6" == value)
    {
        ra_ResponseWindowSize_internal_value = k_ra_ResponseWindowSize_sf6;
        ra_ResponseWindowSize_present = true;
        return 0;
    }
    if("sf7" == value)
    {
        ra_ResponseWindowSize_internal_value = k_ra_ResponseWindowSize_sf7;
        ra_ResponseWindowSize_present = true;
        return 0;
    }
    if("sf8" == value)
    {
        ra_ResponseWindowSize_internal_value = k_ra_ResponseWindowSize_sf8;
        ra_ResponseWindowSize_present = true;
        return 0;
    }
    if("sf10" == value)
    {
        ra_ResponseWindowSize_internal_value = k_ra_ResponseWindowSize_sf10;
        ra_ResponseWindowSize_present = true;
        return 0;
    }
    return 1;
}

std::string RACH_ConfigCommon::ra_SupervisionInfo::ra_ResponseWindowSize_ValueToString(ra_ResponseWindowSize_Enum value) const
{
    if(k_ra_ResponseWindowSize_sf2 == value)
        return "sf2";
    if(k_ra_ResponseWindowSize_sf3 == value)
        return "sf3";
    if(k_ra_ResponseWindowSize_sf4 == value)
        return "sf4";
    if(k_ra_ResponseWindowSize_sf5 == value)
        return "sf5";
    if(k_ra_ResponseWindowSize_sf6 == value)
        return "sf6";
    if(k_ra_ResponseWindowSize_sf7 == value)
        return "sf7";
    if(k_ra_ResponseWindowSize_sf8 == value)
        return "sf8";
    if(k_ra_ResponseWindowSize_sf10 == value)
        return "sf10";
    return "";
}

uint64_t RACH_ConfigCommon::ra_SupervisionInfo::ra_ResponseWindowSize_NumberOfValues() const
{
    return 8;
}

std::string RACH_ConfigCommon::ra_SupervisionInfo::ra_ResponseWindowSize_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ra_ResponseWindowSize = " + ra_ResponseWindowSize_ValueToString(ra_ResponseWindowSize_internal_value) + "\n";
    return out;
}

std::string RACH_ConfigCommon::ra_SupervisionInfo::ra_ResponseWindowSize_ToStringNoNewLines() const
{
    std::string out = "ra_ResponseWindowSize=" + ra_ResponseWindowSize_ValueToString(ra_ResponseWindowSize_internal_value) + ",";
    return out;
}

int RACH_ConfigCommon::ra_SupervisionInfo::ra_ResponseWindowSize_Clear()
{
    ra_ResponseWindowSize_present = false;
    return 0;
}

bool RACH_ConfigCommon::ra_SupervisionInfo::ra_ResponseWindowSize_IsPresent() const
{
    return ra_ResponseWindowSize_present;
}

int RACH_ConfigCommon::ra_SupervisionInfo::mac_ContentionResolutionTimer_Pack(std::vector<uint8_t> &bits)
{
    if(!mac_ContentionResolutionTimer_present)
    {
        printf("RACH_ConfigCommon::ra_SupervisionInfo::mac_ContentionResolutionTimer_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 3;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((mac_ContentionResolutionTimer_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int RACH_ConfigCommon::ra_SupervisionInfo::mac_ContentionResolutionTimer_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return mac_ContentionResolutionTimer_Unpack(bits, idx);
}

int RACH_ConfigCommon::ra_SupervisionInfo::mac_ContentionResolutionTimer_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 3;
    if((idx + N_bits) > bits.size())
    {
        printf("RACH_ConfigCommon::ra_SupervisionInfo::mac_ContentionResolutionTimer_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 7)
    {
        printf("RACH_ConfigCommon::ra_SupervisionInfo::mac_ContentionResolutionTimer_Unpack() max failure\n");
        return -1;
    }
    mac_ContentionResolutionTimer_internal_value = (mac_ContentionResolutionTimer_Enum)packed_val;
    mac_ContentionResolutionTimer_present = true;
    return 0;
}

RACH_ConfigCommon::ra_SupervisionInfo::mac_ContentionResolutionTimer_Enum RACH_ConfigCommon::ra_SupervisionInfo::mac_ContentionResolutionTimer_Value() const
{
    if(mac_ContentionResolutionTimer_present)
        return mac_ContentionResolutionTimer_internal_value;
    return (RACH_ConfigCommon::ra_SupervisionInfo::mac_ContentionResolutionTimer_Enum)0;
}

int RACH_ConfigCommon::ra_SupervisionInfo::mac_ContentionResolutionTimer_SetValue(mac_ContentionResolutionTimer_Enum value)
{
    mac_ContentionResolutionTimer_internal_value = value;
    mac_ContentionResolutionTimer_present = true;
    return 0;
}

int RACH_ConfigCommon::ra_SupervisionInfo::mac_ContentionResolutionTimer_SetValue(std::string value)
{
    if("sf8" == value)
    {
        mac_ContentionResolutionTimer_internal_value = k_mac_ContentionResolutionTimer_sf8;
        mac_ContentionResolutionTimer_present = true;
        return 0;
    }
    if("sf16" == value)
    {
        mac_ContentionResolutionTimer_internal_value = k_mac_ContentionResolutionTimer_sf16;
        mac_ContentionResolutionTimer_present = true;
        return 0;
    }
    if("sf24" == value)
    {
        mac_ContentionResolutionTimer_internal_value = k_mac_ContentionResolutionTimer_sf24;
        mac_ContentionResolutionTimer_present = true;
        return 0;
    }
    if("sf32" == value)
    {
        mac_ContentionResolutionTimer_internal_value = k_mac_ContentionResolutionTimer_sf32;
        mac_ContentionResolutionTimer_present = true;
        return 0;
    }
    if("sf40" == value)
    {
        mac_ContentionResolutionTimer_internal_value = k_mac_ContentionResolutionTimer_sf40;
        mac_ContentionResolutionTimer_present = true;
        return 0;
    }
    if("sf48" == value)
    {
        mac_ContentionResolutionTimer_internal_value = k_mac_ContentionResolutionTimer_sf48;
        mac_ContentionResolutionTimer_present = true;
        return 0;
    }
    if("sf56" == value)
    {
        mac_ContentionResolutionTimer_internal_value = k_mac_ContentionResolutionTimer_sf56;
        mac_ContentionResolutionTimer_present = true;
        return 0;
    }
    if("sf64" == value)
    {
        mac_ContentionResolutionTimer_internal_value = k_mac_ContentionResolutionTimer_sf64;
        mac_ContentionResolutionTimer_present = true;
        return 0;
    }
    return 1;
}

std::string RACH_ConfigCommon::ra_SupervisionInfo::mac_ContentionResolutionTimer_ValueToString(mac_ContentionResolutionTimer_Enum value) const
{
    if(k_mac_ContentionResolutionTimer_sf8 == value)
        return "sf8";
    if(k_mac_ContentionResolutionTimer_sf16 == value)
        return "sf16";
    if(k_mac_ContentionResolutionTimer_sf24 == value)
        return "sf24";
    if(k_mac_ContentionResolutionTimer_sf32 == value)
        return "sf32";
    if(k_mac_ContentionResolutionTimer_sf40 == value)
        return "sf40";
    if(k_mac_ContentionResolutionTimer_sf48 == value)
        return "sf48";
    if(k_mac_ContentionResolutionTimer_sf56 == value)
        return "sf56";
    if(k_mac_ContentionResolutionTimer_sf64 == value)
        return "sf64";
    return "";
}

uint64_t RACH_ConfigCommon::ra_SupervisionInfo::mac_ContentionResolutionTimer_NumberOfValues() const
{
    return 8;
}

std::string RACH_ConfigCommon::ra_SupervisionInfo::mac_ContentionResolutionTimer_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "mac_ContentionResolutionTimer = " + mac_ContentionResolutionTimer_ValueToString(mac_ContentionResolutionTimer_internal_value) + "\n";
    return out;
}

std::string RACH_ConfigCommon::ra_SupervisionInfo::mac_ContentionResolutionTimer_ToStringNoNewLines() const
{
    std::string out = "mac_ContentionResolutionTimer=" + mac_ContentionResolutionTimer_ValueToString(mac_ContentionResolutionTimer_internal_value) + ",";
    return out;
}

int RACH_ConfigCommon::ra_SupervisionInfo::mac_ContentionResolutionTimer_Clear()
{
    mac_ContentionResolutionTimer_present = false;
    return 0;
}

bool RACH_ConfigCommon::ra_SupervisionInfo::mac_ContentionResolutionTimer_IsPresent() const
{
    return mac_ContentionResolutionTimer_present;
}

int RACH_ConfigCommon::maxHARQ_Msg3Tx_Pack(std::vector<uint8_t> &bits)
{
    if(!maxHARQ_Msg3Tx_present)
    {
        printf("RACH_ConfigCommon::maxHARQ_Msg3Tx_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = maxHARQ_Msg3Tx_internal_value - (1);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (8 - 1))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int RACH_ConfigCommon::maxHARQ_Msg3Tx_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return maxHARQ_Msg3Tx_Unpack(bits, idx);
}

int RACH_ConfigCommon::maxHARQ_Msg3Tx_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (8 - 1))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("RACH_ConfigCommon::maxHARQ_Msg3Tx_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    maxHARQ_Msg3Tx_internal_value = packed_val + 1;
    maxHARQ_Msg3Tx_present = true;
    return 0;
}

int64_t RACH_ConfigCommon::maxHARQ_Msg3Tx_Value() const
{
    if(maxHARQ_Msg3Tx_present)
        return maxHARQ_Msg3Tx_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int RACH_ConfigCommon::maxHARQ_Msg3Tx_SetValue(int64_t value)
{
    if(value < 1 || value > 8)
    {
        printf("RACH_ConfigCommon::maxHARQ_Msg3Tx_SetValue() range failure\n");
        return -1;
    }
    maxHARQ_Msg3Tx_internal_value = value;
    maxHARQ_Msg3Tx_present = true;
    return 0;
}

std::string RACH_ConfigCommon::maxHARQ_Msg3Tx_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "maxHARQ_Msg3Tx = " + std::to_string(maxHARQ_Msg3Tx_internal_value) + "\n";
    return out;
}

std::string RACH_ConfigCommon::maxHARQ_Msg3Tx_ToStringNoNewLines() const
{
    std::string out = "maxHARQ_Msg3Tx=" + std::to_string(maxHARQ_Msg3Tx_internal_value) + ",";
    return out;
}

int RACH_ConfigCommon::maxHARQ_Msg3Tx_Clear()
{
    maxHARQ_Msg3Tx_present = false;
    return 0;
}

bool RACH_ConfigCommon::maxHARQ_Msg3Tx_IsPresent() const
{
    return maxHARQ_Msg3Tx_present;
}

