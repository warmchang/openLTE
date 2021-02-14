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

#include "Handover.h"

#include <cmath>

int Handover::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(nas_SecurityParamFromEUTRA_IsPresent());
    bits.push_back(systemInformation_IsPresent());

    // Fields
    {
        if(0 != targetRAT_Type_Pack(bits))
        {
            printf("Handover:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != targetRAT_MessageContainer_Pack(bits))
        {
            printf("Handover:: field pack failure\n");
            return -1;
        }
    }
    if(nas_SecurityParamFromEUTRA_IsPresent())
    {
        if(0 != nas_SecurityParamFromEUTRA_Pack(bits))
        {
            printf("Handover:: field pack failure\n");
            return -1;
        }
    }
    if(systemInformation_IsPresent())
    {
        if(0 != systemInformation.Pack(bits))
        {
            printf("Handover:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int Handover::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int Handover::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("Handover::Unpack() index out of bounds for optional indiator nas_SecurityParamFromEUTRA\n");
        return -1;
    }
    nas_SecurityParamFromEUTRA_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("Handover::Unpack() index out of bounds for optional indiator systemInformation\n");
        return -1;
    }
    systemInformation_present = bits[idx++];

    // Fields
    {
        if(0 != targetRAT_Type_Unpack(bits, idx))
        {
            printf("Handover:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != targetRAT_MessageContainer_Unpack(bits, idx))
        {
            printf("Handover:: field unpack failure\n");
            return -1;
        }
    }
    if(nas_SecurityParamFromEUTRA_present)
    {
        if(0 != nas_SecurityParamFromEUTRA_Unpack(bits, idx))
        {
            printf("Handover:: field unpack failure\n");
            return -1;
        }
    }
    if(systemInformation_present)
    {
        if(0 != systemInformation.Unpack(bits, idx))
        {
            printf("Handover:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string Handover::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "Handover:\n";
    out += targetRAT_Type_ToString(indent+1);
    out += targetRAT_MessageContainer_ToString(indent+1);
    if(nas_SecurityParamFromEUTRA_IsPresent())
        out += nas_SecurityParamFromEUTRA_ToString(indent+1);
    if(systemInformation_IsPresent())
        out += systemInformation_ToString(indent+1);
    return out;
}

std::string Handover::ToStringNoNewLines() const
{
    std::string out = "Handover:";
    out += targetRAT_Type_ToStringNoNewLines();
    out += targetRAT_MessageContainer_ToStringNoNewLines();
    if(nas_SecurityParamFromEUTRA_IsPresent())
        out += nas_SecurityParamFromEUTRA_ToStringNoNewLines();
    if(systemInformation_IsPresent())
        out += systemInformation_ToStringNoNewLines();
    return out;
}

int Handover::targetRAT_Type_Pack(std::vector<uint8_t> &bits)
{
    if(!targetRAT_Type_present)
    {
        printf("Handover::targetRAT_Type_Pack() presence failure\n");
        return -1;
    }
    if(targetRAT_Type_internal_value > k_targetRAT_Type_spare1)
    {
        bits.push_back(1);
    }else{
        bits.push_back(0);
    }
    uint32_t N_bits = 3;
    if(targetRAT_Type_internal_value > k_targetRAT_Type_spare1)
        N_bits = 0;
    for(uint32_t i=0; i<N_bits; i++)
    {
        if(targetRAT_Type_internal_value > k_targetRAT_Type_spare1)
        {
            bits.push_back(((targetRAT_Type_internal_value - k_targetRAT_Type_spare1) >> (N_bits-1-i)) & 1);
        }else{
            bits.push_back((targetRAT_Type_internal_value >> (N_bits-1-i)) & 1);
        }
    }
    return 0;
}

int Handover::targetRAT_Type_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return targetRAT_Type_Unpack(bits, idx);
}

int Handover::targetRAT_Type_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    if((idx + 1) > bits.size())
    {
        printf("Handover::targetRAT_Type_Unpack() index out of bounds for extension\n");
        return -1;
    }
    bool has_extension = bits[idx++];
    uint32_t packed_val = 0;
    uint32_t N_bits = 3;
    if(has_extension)
        N_bits = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("Handover::targetRAT_Type_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(has_extension)
    {
        targetRAT_Type_internal_value = (targetRAT_Type_Enum)(packed_val + 8);
    }else{
        if(packed_val > 7)
        {
            printf("Handover::targetRAT_Type_Unpack() max failure\n");
            return -1;
        }
        targetRAT_Type_internal_value = (targetRAT_Type_Enum)packed_val;
    }
    targetRAT_Type_present = true;
    return 0;
}

Handover::targetRAT_Type_Enum Handover::targetRAT_Type_Value() const
{
    if(targetRAT_Type_present)
        return targetRAT_Type_internal_value;
    return (Handover::targetRAT_Type_Enum)0;
}

int Handover::targetRAT_Type_SetValue(targetRAT_Type_Enum value)
{
    targetRAT_Type_internal_value = value;
    targetRAT_Type_present = true;
    return 0;
}

int Handover::targetRAT_Type_SetValue(std::string value)
{
    if("utra" == value)
    {
        targetRAT_Type_internal_value = k_targetRAT_Type_utra;
        targetRAT_Type_present = true;
        return 0;
    }
    if("geran" == value)
    {
        targetRAT_Type_internal_value = k_targetRAT_Type_geran;
        targetRAT_Type_present = true;
        return 0;
    }
    if("cdma2000_1XRTT" == value)
    {
        targetRAT_Type_internal_value = k_targetRAT_Type_cdma2000_1XRTT;
        targetRAT_Type_present = true;
        return 0;
    }
    if("cdma2000_HRPD" == value)
    {
        targetRAT_Type_internal_value = k_targetRAT_Type_cdma2000_HRPD;
        targetRAT_Type_present = true;
        return 0;
    }
    if("spare4" == value)
    {
        targetRAT_Type_internal_value = k_targetRAT_Type_spare4;
        targetRAT_Type_present = true;
        return 0;
    }
    if("spare3" == value)
    {
        targetRAT_Type_internal_value = k_targetRAT_Type_spare3;
        targetRAT_Type_present = true;
        return 0;
    }
    if("spare2" == value)
    {
        targetRAT_Type_internal_value = k_targetRAT_Type_spare2;
        targetRAT_Type_present = true;
        return 0;
    }
    if("spare1" == value)
    {
        targetRAT_Type_internal_value = k_targetRAT_Type_spare1;
        targetRAT_Type_present = true;
        return 0;
    }
    return 1;
}

std::string Handover::targetRAT_Type_ValueToString(targetRAT_Type_Enum value) const
{
    if(k_targetRAT_Type_utra == value)
        return "utra";
    if(k_targetRAT_Type_geran == value)
        return "geran";
    if(k_targetRAT_Type_cdma2000_1XRTT == value)
        return "cdma2000_1XRTT";
    if(k_targetRAT_Type_cdma2000_HRPD == value)
        return "cdma2000_HRPD";
    if(k_targetRAT_Type_spare4 == value)
        return "spare4";
    if(k_targetRAT_Type_spare3 == value)
        return "spare3";
    if(k_targetRAT_Type_spare2 == value)
        return "spare2";
    if(k_targetRAT_Type_spare1 == value)
        return "spare1";
    return "";
}

uint64_t Handover::targetRAT_Type_NumberOfValues() const
{
    return 8;
}

std::string Handover::targetRAT_Type_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "targetRAT_Type = " + targetRAT_Type_ValueToString(targetRAT_Type_internal_value) + "\n";
    return out;
}

std::string Handover::targetRAT_Type_ToStringNoNewLines() const
{
    std::string out = "targetRAT_Type=" + targetRAT_Type_ValueToString(targetRAT_Type_internal_value) + ",";
    return out;
}

int Handover::targetRAT_Type_Clear()
{
    targetRAT_Type_present = false;
    return 0;
}

bool Handover::targetRAT_Type_IsPresent() const
{
    return targetRAT_Type_present;
}

int Handover::targetRAT_MessageContainer_Pack(std::vector<uint8_t> &bits)
{
    if(!targetRAT_MessageContainer_present)
    {
        printf("Handover::targetRAT_MessageContainer_Pack() presence failure\n");
        return -1;
    }
    uint32_t local_size_length = 0;
    uint32_t local_size = targetRAT_MessageContainer_internal_value.size();
    if(local_size < 128)
    {
        bits.push_back(0);
        local_size_length = 7;
    }else if(local_size < 16383){
        bits.push_back(1);
        bits.push_back(0);
        local_size_length = 14;
    }else{
        bits.push_back(1);
        bits.push_back(1);
        uint32_t N_16k_blocks = local_size / 16383;
        for(uint32_t i=0; i<6; i++)
            bits.push_back((N_16k_blocks >> (6-i-1)) & 1);
        local_size %= 16383;
        if(local_size < 128)
        {
            bits.push_back(0);
            local_size_length = 7;
        }else{
            bits.push_back(1);
            bits.push_back(0);
            local_size_length = 14;
        }
    }
    for(uint32_t i=0; i<local_size_length; i++)
        bits.push_back((local_size >> (local_size_length-i-1)) & 1);
    for(uint32_t i=0; i<targetRAT_MessageContainer_internal_value.size(); i++)
        for(uint32_t j=0; j<8; j++)
            bits.push_back((targetRAT_MessageContainer_internal_value[i] >> (8-j-1)) & 1);
    return 0;
}

int Handover::targetRAT_MessageContainer_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return targetRAT_MessageContainer_Unpack(bits, idx);
}

int Handover::targetRAT_MessageContainer_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t local_size_length = 0;
    uint32_t size = 0;
    if(0 == bits[idx++])
    {
        local_size_length = 7;
    }else{
        if(0 == bits[idx++])
        {
            local_size_length = 14;
        }else{
            for(uint32_t i=0; i<6; i++)
                size |= bits[idx++] << (6-i-1);
            size *= 16383;
            if(0 == bits[idx++])
            {
                local_size_length = 7;
            }else{
                idx++;
                local_size_length = 14;
            }
        }
    }
    for(uint32_t i=0; i<local_size_length; i++)
        size |= bits[idx++] << (local_size_length-i-1);
    targetRAT_MessageContainer_internal_value.clear();
    if((idx +size*8) > bits.size())
    {
        printf("Handover::targetRAT_MessageContainer_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
    {
        uint8_t value = 0;
        for(uint32_t j=0; j<8; j++)
            value |= bits[idx+j] << (8-j-1);
        targetRAT_MessageContainer_internal_value.push_back(value);
        idx += 8;
    }
    targetRAT_MessageContainer_present = true;
    return 0;
}

std::vector<uint8_t> Handover::targetRAT_MessageContainer_Value() const
{
    if(targetRAT_MessageContainer_present)
        return targetRAT_MessageContainer_internal_value;
    std::vector<uint8_t> tmp;
    return tmp;
}

int Handover::targetRAT_MessageContainer_SetValue(std::vector<uint8_t> value)
{
    targetRAT_MessageContainer_internal_value = value;
    targetRAT_MessageContainer_present = true;
    return 0;
}

std::string Handover::targetRAT_MessageContainer_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "targetRAT_MessageContainer = {";
    for(auto byte : targetRAT_MessageContainer_internal_value)
        out += std::to_string(byte) + ",";
    out = out.substr(0, out.length()-1) + "}\n";
    return out;
}

std::string Handover::targetRAT_MessageContainer_ToStringNoNewLines() const
{
    std::string out = "targetRAT_MessageContainer={";
    for(auto byte : targetRAT_MessageContainer_internal_value)
        out += std::to_string(byte) + ",";
    out = out.substr(0, out.length()-1) + "},";
    return out;
}

int Handover::targetRAT_MessageContainer_Clear()
{
    targetRAT_MessageContainer_present = false;
    return 0;
}

bool Handover::targetRAT_MessageContainer_IsPresent() const
{
    return targetRAT_MessageContainer_present;
}

int Handover::nas_SecurityParamFromEUTRA_Pack(std::vector<uint8_t> &bits)
{
    if(nas_SecurityParamFromEUTRA_internal_value.size() < 1 || nas_SecurityParamFromEUTRA_internal_value.size() > 1)
    {
        printf("Handover::nas_SecurityParamFromEUTRA_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<nas_SecurityParamFromEUTRA_internal_value.size(); i++)
        for(uint32_t j=0; j<8; j++)
            bits.push_back((nas_SecurityParamFromEUTRA_internal_value[i] >> (8-j-1)) & 1);
    return 0;
}

int Handover::nas_SecurityParamFromEUTRA_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return nas_SecurityParamFromEUTRA_Unpack(bits, idx);
}

int Handover::nas_SecurityParamFromEUTRA_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 1;
    if(size < 1 || size > 1)
    {
        printf("Handover::nas_SecurityParamFromEUTRA_Unpack() size failure\n");
        return -1;
    }
    nas_SecurityParamFromEUTRA_internal_value.clear();
    if((idx +size*8) > bits.size())
    {
        printf("Handover::nas_SecurityParamFromEUTRA_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
    {
        uint8_t value = 0;
        for(uint32_t j=0; j<8; j++)
            value |= bits[idx+j] << (8-j-1);
        nas_SecurityParamFromEUTRA_internal_value.push_back(value);
        idx += 8;
    }
    nas_SecurityParamFromEUTRA_present = true;
    return 0;
}

std::vector<uint8_t> Handover::nas_SecurityParamFromEUTRA_Value() const
{
    if(nas_SecurityParamFromEUTRA_present)
        return nas_SecurityParamFromEUTRA_internal_value;
    std::vector<uint8_t> tmp;
    return tmp;
}

int Handover::nas_SecurityParamFromEUTRA_SetValue(std::vector<uint8_t> value)
{
    if(value.size() < 1 || value.size() > 1)
    {
        printf("Handover::nas_SecurityParamFromEUTRA_SetValue() size failure\n");
        return -1;
    }
    nas_SecurityParamFromEUTRA_internal_value = value;
    nas_SecurityParamFromEUTRA_present = true;
    return 0;
}

std::string Handover::nas_SecurityParamFromEUTRA_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "nas_SecurityParamFromEUTRA = {";
    for(auto byte : nas_SecurityParamFromEUTRA_internal_value)
        out += std::to_string(byte) + ",";
    out = out.substr(0, out.length()-1) + "}\n";
    return out;
}

std::string Handover::nas_SecurityParamFromEUTRA_ToStringNoNewLines() const
{
    std::string out = "nas_SecurityParamFromEUTRA={";
    for(auto byte : nas_SecurityParamFromEUTRA_internal_value)
        out += std::to_string(byte) + ",";
    out = out.substr(0, out.length()-1) + "},";
    return out;
}

int Handover::nas_SecurityParamFromEUTRA_Clear()
{
    nas_SecurityParamFromEUTRA_present = false;
    return 0;
}

bool Handover::nas_SecurityParamFromEUTRA_IsPresent() const
{
    return nas_SecurityParamFromEUTRA_present;
}

SI_OrPSI_GERAN* Handover::systemInformation_Set()
{
    systemInformation_present = true;
    return &systemInformation;
}

int Handover::systemInformation_Set(SI_OrPSI_GERAN &value)
{
    systemInformation_present = true;
    systemInformation = value;
    return 0;
}

const SI_OrPSI_GERAN& Handover::systemInformation_Get() const
{
    return systemInformation;
}

std::string Handover::systemInformation_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "systemInformation:\n";
    out += systemInformation.ToString(indent+1);
    return out;
}

std::string Handover::systemInformation_ToStringNoNewLines() const
{
    std::string out = "systemInformation:";
    out += systemInformation.ToStringNoNewLines();
    return out;
}

int Handover::systemInformation_Clear()
{
    systemInformation_present = false;
    return 0;
}

bool Handover::systemInformation_IsPresent() const
{
    return systemInformation_present;
}

