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

#include "SecurityConfigHO.h"

#include <cmath>

int SecurityConfigHO::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator
    bits.push_back(0);

    // Optional indicators

    // Fields
    {
        if(0 != handoverType_Pack(bits))
        {
            printf("SecurityConfigHO:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int SecurityConfigHO::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int SecurityConfigHO::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("SecurityConfigHO::Unpack() index out of bounds for extension\n");
        return -1;
    }
    idx++;

    // Optional indicators

    // Fields
    {
        if(0 != handoverType_Unpack(bits, idx))
        {
            printf("SecurityConfigHO:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string SecurityConfigHO::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "SecurityConfigHO:\n";
    out += handoverType_ToString(indent+1);
    return out;
}

std::string SecurityConfigHO::ToStringNoNewLines() const
{
    std::string out = "SecurityConfigHO:";
    out += handoverType_ToStringNoNewLines();
    return out;
}

int SecurityConfigHO::handoverType_Pack(std::vector<uint8_t> &bits)
{
    if(!handoverType_present)
    {
        printf("SecurityConfigHO::handoverType_Pack() presence failure\n");
        return -1;
    }
    // Extension indicator

    // Choice
    for(uint32_t i=0; i<1; i++)
        bits.push_back((handoverType_internal_choice >> (1-i-1)) & 1);

    // Fields
    if(handoverType_internal_choice == k_handoverType_intraLTE)
    {
        if(0 != handoverType_intraLTE_value.Pack(bits))
        {
            printf("SecurityConfigHO::handoverType_intraLTE pack failure\n");
            return -1;
        }
    }
    if(handoverType_internal_choice == k_handoverType_interRAT)
    {
        if(0 != handoverType_interRAT_value.Pack(bits))
        {
            printf("SecurityConfigHO::handoverType_interRAT pack failure\n");
            return -1;
        }
    }
    return 0;
}

int SecurityConfigHO::handoverType_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return handoverType_Unpack(bits, idx);
}

int SecurityConfigHO::handoverType_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 1) > bits.size())
    {
        printf("SecurityConfigHO::handoverType_Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<1; i++)
        packed_val |= bits[idx++] << (1-i-1);

    if((SecurityConfigHO::handoverType_Enum)packed_val > k_handoverType_interRAT)
    {
        printf("SecurityConfigHO::handoverType_Unpack() choice range failure\n");
        return -1;
    }
    handoverType_internal_choice = (SecurityConfigHO::handoverType_Enum)packed_val;
    handoverType_present = true;

    // Fields
    if(handoverType_internal_choice == k_handoverType_intraLTE)
    {
        if(0 != handoverType_intraLTE_value.Unpack(bits, idx))
        {
            printf("SecurityConfigHO::handoverType_intraLTE unpack failure\n");
            return -1;
        }
    }
    if(handoverType_internal_choice == k_handoverType_interRAT)
    {
        if(0 != handoverType_interRAT_value.Unpack(bits, idx))
        {
            printf("SecurityConfigHO::handoverType_interRAT unpack failure\n");
            return -1;
        }
    }
    return 0;
}

SecurityConfigHO::handoverType_Enum SecurityConfigHO::handoverType_Choice() const
{
    if(handoverType_present)
        return handoverType_internal_choice;
    return (SecurityConfigHO::handoverType_Enum)0;
}

int SecurityConfigHO::handoverType_SetChoice(SecurityConfigHO::handoverType_Enum choice)
{
    handoverType_internal_choice = choice;
    handoverType_present = true;
    return 0;
}

std::string SecurityConfigHO::handoverType_ChoiceToString(handoverType_Enum value) const
{
    if(k_handoverType_intraLTE == value)
        return "handoverType_intraLTE";
    if(k_handoverType_interRAT == value)
        return "handoverType_interRAT";
    return "";
}

uint64_t SecurityConfigHO::handoverType_NumberOfChoices() const
{
    return 2;
}

std::string SecurityConfigHO::handoverType_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "handoverType = " + handoverType_ChoiceToString(handoverType_internal_choice) + ":\n";
    if(handoverType_internal_choice == k_handoverType_intraLTE)
        out += handoverType_intraLTE_value.ToString(indent+1);
    if(handoverType_internal_choice == k_handoverType_interRAT)
        out += handoverType_interRAT_value.ToString(indent+1);
    return out;
}

std::string SecurityConfigHO::handoverType_ToStringNoNewLines() const
{
    std::string out = "handoverType=" + handoverType_ChoiceToString(handoverType_internal_choice) + ",";
    if(handoverType_internal_choice == k_handoverType_intraLTE)
        out += handoverType_intraLTE_value.ToStringNoNewLines();
    if(handoverType_internal_choice == k_handoverType_interRAT)
        out += handoverType_interRAT_value.ToStringNoNewLines();
    return out;
}

int SecurityConfigHO::handoverType_Clear()
{
    handoverType_present = false;
    return 0;
}

bool SecurityConfigHO::handoverType_IsPresent() const
{
    return handoverType_present;
}

int SecurityConfigHO::handoverType_intraLTE::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(securityAlgorithmConfig_IsPresent());

    // Fields
    if(securityAlgorithmConfig_IsPresent())
    {
        if(0 != securityAlgorithmConfig.Pack(bits))
        {
            printf("SecurityConfigHO::handoverType_intraLTE:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != keyChangeIndicator_Pack(bits))
        {
            printf("SecurityConfigHO::handoverType_intraLTE:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != nextHopChainingCount.Pack(bits))
        {
            printf("SecurityConfigHO::handoverType_intraLTE:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int SecurityConfigHO::handoverType_intraLTE::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int SecurityConfigHO::handoverType_intraLTE::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("handoverType_intraLTE::Unpack() index out of bounds for optional indiator securityAlgorithmConfig\n");
        return -1;
    }
    securityAlgorithmConfig_present = bits[idx++];

    // Fields
    if(securityAlgorithmConfig_present)
    {
        if(0 != securityAlgorithmConfig.Unpack(bits, idx))
        {
            printf("SecurityConfigHO::handoverType_intraLTE:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != keyChangeIndicator_Unpack(bits, idx))
        {
            printf("SecurityConfigHO::handoverType_intraLTE:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != nextHopChainingCount.Unpack(bits, idx))
        {
            printf("SecurityConfigHO::handoverType_intraLTE:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string SecurityConfigHO::handoverType_intraLTE::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "intraLTE:\n";
    if(securityAlgorithmConfig_IsPresent())
        out += securityAlgorithmConfig_ToString(indent+1);
    out += keyChangeIndicator_ToString(indent+1);
    out += nextHopChainingCount_ToString(indent+1);
    return out;
}

std::string SecurityConfigHO::handoverType_intraLTE::ToStringNoNewLines() const
{
    std::string out = "intraLTE:";
    if(securityAlgorithmConfig_IsPresent())
        out += securityAlgorithmConfig_ToStringNoNewLines();
    out += keyChangeIndicator_ToStringNoNewLines();
    out += nextHopChainingCount_ToStringNoNewLines();
    return out;
}

SecurityAlgorithmConfig* SecurityConfigHO::handoverType_intraLTE::securityAlgorithmConfig_Set()
{
    securityAlgorithmConfig_present = true;
    return &securityAlgorithmConfig;
}

int SecurityConfigHO::handoverType_intraLTE::securityAlgorithmConfig_Set(SecurityAlgorithmConfig &value)
{
    securityAlgorithmConfig_present = true;
    securityAlgorithmConfig = value;
    return 0;
}

const SecurityAlgorithmConfig& SecurityConfigHO::handoverType_intraLTE::securityAlgorithmConfig_Get() const
{
    return securityAlgorithmConfig;
}

std::string SecurityConfigHO::handoverType_intraLTE::securityAlgorithmConfig_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "securityAlgorithmConfig:\n";
    out += securityAlgorithmConfig.ToString(indent+1);
    return out;
}

std::string SecurityConfigHO::handoverType_intraLTE::securityAlgorithmConfig_ToStringNoNewLines() const
{
    std::string out = "securityAlgorithmConfig:";
    out += securityAlgorithmConfig.ToStringNoNewLines();
    return out;
}

int SecurityConfigHO::handoverType_intraLTE::securityAlgorithmConfig_Clear()
{
    securityAlgorithmConfig_present = false;
    return 0;
}

bool SecurityConfigHO::handoverType_intraLTE::securityAlgorithmConfig_IsPresent() const
{
    return securityAlgorithmConfig_present;
}

int SecurityConfigHO::handoverType_intraLTE::keyChangeIndicator_Pack(std::vector<uint8_t> &bits)
{
    if(!keyChangeIndicator_present)
    {
        printf("SecurityConfigHO::handoverType_intraLTE::keyChangeIndicator_Pack() presence failure\n");
        return -1;
    }
    bits.push_back(keyChangeIndicator_internal_value);
    return 0;
}

int SecurityConfigHO::handoverType_intraLTE::keyChangeIndicator_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return keyChangeIndicator_Unpack(bits, idx);
}

int SecurityConfigHO::handoverType_intraLTE::keyChangeIndicator_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    if((idx + 1) > bits.size())
    {
        printf("SecurityConfigHO::handoverType_intraLTE::keyChangeIndicator_Unpack() index out of bounds\n");
        return -1;
    }
    keyChangeIndicator_internal_value = bits[idx++];
    keyChangeIndicator_present = true;
    return 0;
}

bool SecurityConfigHO::handoverType_intraLTE::keyChangeIndicator_Value() const
{
    if(keyChangeIndicator_present)
        return keyChangeIndicator_internal_value;
    return false;
}

int SecurityConfigHO::handoverType_intraLTE::keyChangeIndicator_SetValue(bool value)
{
    keyChangeIndicator_internal_value = value;
    keyChangeIndicator_present = true;
    return 0;
}

std::string SecurityConfigHO::handoverType_intraLTE::keyChangeIndicator_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "keyChangeIndicator = " + std::to_string(keyChangeIndicator_internal_value) + "\n";
    return out;
}

std::string SecurityConfigHO::handoverType_intraLTE::keyChangeIndicator_ToStringNoNewLines() const
{
    std::string out = "keyChangeIndicator=" + std::to_string(keyChangeIndicator_internal_value) + ",";
    return out;
}

int SecurityConfigHO::handoverType_intraLTE::keyChangeIndicator_Clear()
{
    keyChangeIndicator_present = false;
    return 0;
}

bool SecurityConfigHO::handoverType_intraLTE::keyChangeIndicator_IsPresent() const
{
    return keyChangeIndicator_present;
}

NextHopChainingCount* SecurityConfigHO::handoverType_intraLTE::nextHopChainingCount_Set()
{
    nextHopChainingCount_present = true;
    return &nextHopChainingCount;
}

int SecurityConfigHO::handoverType_intraLTE::nextHopChainingCount_Set(NextHopChainingCount &value)
{
    nextHopChainingCount_present = true;
    nextHopChainingCount = value;
    return 0;
}

const NextHopChainingCount& SecurityConfigHO::handoverType_intraLTE::nextHopChainingCount_Get() const
{
    return nextHopChainingCount;
}

std::string SecurityConfigHO::handoverType_intraLTE::nextHopChainingCount_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "nextHopChainingCount:\n";
    out += nextHopChainingCount.ToString(indent+1);
    return out;
}

std::string SecurityConfigHO::handoverType_intraLTE::nextHopChainingCount_ToStringNoNewLines() const
{
    std::string out = "nextHopChainingCount:";
    out += nextHopChainingCount.ToStringNoNewLines();
    return out;
}

int SecurityConfigHO::handoverType_intraLTE::nextHopChainingCount_Clear()
{
    nextHopChainingCount_present = false;
    return 0;
}

bool SecurityConfigHO::handoverType_intraLTE::nextHopChainingCount_IsPresent() const
{
    return nextHopChainingCount_present;
}

int SecurityConfigHO::handoverType_interRAT::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != securityAlgorithmConfig.Pack(bits))
        {
            printf("SecurityConfigHO::handoverType_interRAT:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != nas_SecurityParamToEUTRA_Pack(bits))
        {
            printf("SecurityConfigHO::handoverType_interRAT:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int SecurityConfigHO::handoverType_interRAT::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int SecurityConfigHO::handoverType_interRAT::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != securityAlgorithmConfig.Unpack(bits, idx))
        {
            printf("SecurityConfigHO::handoverType_interRAT:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != nas_SecurityParamToEUTRA_Unpack(bits, idx))
        {
            printf("SecurityConfigHO::handoverType_interRAT:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string SecurityConfigHO::handoverType_interRAT::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "interRAT:\n";
    out += securityAlgorithmConfig_ToString(indent+1);
    out += nas_SecurityParamToEUTRA_ToString(indent+1);
    return out;
}

std::string SecurityConfigHO::handoverType_interRAT::ToStringNoNewLines() const
{
    std::string out = "interRAT:";
    out += securityAlgorithmConfig_ToStringNoNewLines();
    out += nas_SecurityParamToEUTRA_ToStringNoNewLines();
    return out;
}

SecurityAlgorithmConfig* SecurityConfigHO::handoverType_interRAT::securityAlgorithmConfig_Set()
{
    securityAlgorithmConfig_present = true;
    return &securityAlgorithmConfig;
}

int SecurityConfigHO::handoverType_interRAT::securityAlgorithmConfig_Set(SecurityAlgorithmConfig &value)
{
    securityAlgorithmConfig_present = true;
    securityAlgorithmConfig = value;
    return 0;
}

const SecurityAlgorithmConfig& SecurityConfigHO::handoverType_interRAT::securityAlgorithmConfig_Get() const
{
    return securityAlgorithmConfig;
}

std::string SecurityConfigHO::handoverType_interRAT::securityAlgorithmConfig_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "securityAlgorithmConfig:\n";
    out += securityAlgorithmConfig.ToString(indent+1);
    return out;
}

std::string SecurityConfigHO::handoverType_interRAT::securityAlgorithmConfig_ToStringNoNewLines() const
{
    std::string out = "securityAlgorithmConfig:";
    out += securityAlgorithmConfig.ToStringNoNewLines();
    return out;
}

int SecurityConfigHO::handoverType_interRAT::securityAlgorithmConfig_Clear()
{
    securityAlgorithmConfig_present = false;
    return 0;
}

bool SecurityConfigHO::handoverType_interRAT::securityAlgorithmConfig_IsPresent() const
{
    return securityAlgorithmConfig_present;
}

int SecurityConfigHO::handoverType_interRAT::nas_SecurityParamToEUTRA_Pack(std::vector<uint8_t> &bits)
{
    if(!nas_SecurityParamToEUTRA_present)
    {
        printf("SecurityConfigHO::handoverType_interRAT::nas_SecurityParamToEUTRA_Pack() presence failure\n");
        return -1;
    }
    if(nas_SecurityParamToEUTRA_internal_value.size() < 6 || nas_SecurityParamToEUTRA_internal_value.size() > 6)
    {
        printf("SecurityConfigHO::handoverType_interRAT::nas_SecurityParamToEUTRA_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<nas_SecurityParamToEUTRA_internal_value.size(); i++)
        for(uint32_t j=0; j<8; j++)
            bits.push_back((nas_SecurityParamToEUTRA_internal_value[i] >> (8-j-1)) & 1);
    return 0;
}

int SecurityConfigHO::handoverType_interRAT::nas_SecurityParamToEUTRA_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return nas_SecurityParamToEUTRA_Unpack(bits, idx);
}

int SecurityConfigHO::handoverType_interRAT::nas_SecurityParamToEUTRA_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 6;
    if(size < 6 || size > 6)
    {
        printf("SecurityConfigHO::handoverType_interRAT::nas_SecurityParamToEUTRA_Unpack() size failure\n");
        return -1;
    }
    nas_SecurityParamToEUTRA_internal_value.clear();
    if((idx +size*8) > bits.size())
    {
        printf("SecurityConfigHO::handoverType_interRAT::nas_SecurityParamToEUTRA_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
    {
        uint8_t value = 0;
        for(uint32_t j=0; j<8; j++)
            value |= bits[idx+j] << (8-j-1);
        nas_SecurityParamToEUTRA_internal_value.push_back(value);
        idx += 8;
    }
    nas_SecurityParamToEUTRA_present = true;
    return 0;
}

std::vector<uint8_t> SecurityConfigHO::handoverType_interRAT::nas_SecurityParamToEUTRA_Value() const
{
    if(nas_SecurityParamToEUTRA_present)
        return nas_SecurityParamToEUTRA_internal_value;
    std::vector<uint8_t> tmp;
    return tmp;
}

int SecurityConfigHO::handoverType_interRAT::nas_SecurityParamToEUTRA_SetValue(std::vector<uint8_t> value)
{
    if(value.size() < 6 || value.size() > 6)
    {
        printf("SecurityConfigHO::handoverType_interRAT::nas_SecurityParamToEUTRA_SetValue() size failure\n");
        return -1;
    }
    nas_SecurityParamToEUTRA_internal_value = value;
    nas_SecurityParamToEUTRA_present = true;
    return 0;
}

std::string SecurityConfigHO::handoverType_interRAT::nas_SecurityParamToEUTRA_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "nas_SecurityParamToEUTRA = {";
    for(auto byte : nas_SecurityParamToEUTRA_internal_value)
        out += std::to_string(byte) + ",";
    out = out.substr(0, out.length()-1) + "}\n";
    return out;
}

std::string SecurityConfigHO::handoverType_interRAT::nas_SecurityParamToEUTRA_ToStringNoNewLines() const
{
    std::string out = "nas_SecurityParamToEUTRA={";
    for(auto byte : nas_SecurityParamToEUTRA_internal_value)
        out += std::to_string(byte) + ",";
    out = out.substr(0, out.length()-1) + "},";
    return out;
}

int SecurityConfigHO::handoverType_interRAT::nas_SecurityParamToEUTRA_Clear()
{
    nas_SecurityParamToEUTRA_present = false;
    return 0;
}

bool SecurityConfigHO::handoverType_interRAT::nas_SecurityParamToEUTRA_IsPresent() const
{
    return nas_SecurityParamToEUTRA_present;
}

