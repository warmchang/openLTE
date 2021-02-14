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

#include "SystemInfoChange_r10.h"

#include <cmath>

int SystemInfoChange_r10::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator
    bits.push_back(0);

    // Optional indicators
    bits.push_back(systemInformationBlockType1_r10_IsPresent());
    bits.push_back(systemInformationBlockType2_r10_IsPresent());

    // Fields
    if(systemInformationBlockType1_r10_IsPresent())
    {
        if(0 != systemInformationBlockType1_r10_Pack(bits))
        {
            printf("SystemInfoChange_r10:: field pack failure\n");
            return -1;
        }
    }
    if(systemInformationBlockType2_r10_IsPresent())
    {
        if(0 != systemInformationBlockType2_r10.Pack(bits))
        {
            printf("SystemInfoChange_r10:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int SystemInfoChange_r10::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int SystemInfoChange_r10::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("SystemInfoChange_r10::Unpack() index out of bounds for extension\n");
        return -1;
    }
    idx++;

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("SystemInfoChange_r10::Unpack() index out of bounds for optional indiator systemInformationBlockType1_r10\n");
        return -1;
    }
    systemInformationBlockType1_r10_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("SystemInfoChange_r10::Unpack() index out of bounds for optional indiator systemInformationBlockType2_r10\n");
        return -1;
    }
    systemInformationBlockType2_r10_present = bits[idx++];

    // Fields
    if(systemInformationBlockType1_r10_present)
    {
        if(0 != systemInformationBlockType1_r10_Unpack(bits, idx))
        {
            printf("SystemInfoChange_r10:: field unpack failure\n");
            return -1;
        }
    }
    if(systemInformationBlockType2_r10_present)
    {
        if(0 != systemInformationBlockType2_r10.Unpack(bits, idx))
        {
            printf("SystemInfoChange_r10:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string SystemInfoChange_r10::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "SystemInfoChange_r10:\n";
    if(systemInformationBlockType1_r10_IsPresent())
        out += systemInformationBlockType1_r10_ToString(indent+1);
    if(systemInformationBlockType2_r10_IsPresent())
        out += systemInformationBlockType2_r10_ToString(indent+1);
    return out;
}

std::string SystemInfoChange_r10::ToStringNoNewLines() const
{
    std::string out = "SystemInfoChange_r10:";
    if(systemInformationBlockType1_r10_IsPresent())
        out += systemInformationBlockType1_r10_ToStringNoNewLines();
    if(systemInformationBlockType2_r10_IsPresent())
        out += systemInformationBlockType2_r10_ToStringNoNewLines();
    return out;
}

int SystemInfoChange_r10::systemInformationBlockType1_r10_Pack(std::vector<uint8_t> &bits)
{
    uint32_t local_size_length = 0;
    uint32_t local_size = systemInformationBlockType1_r10_internal_value.size();
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
    for(uint32_t i=0; i<systemInformationBlockType1_r10_internal_value.size(); i++)
        for(uint32_t j=0; j<8; j++)
            bits.push_back((systemInformationBlockType1_r10_internal_value[i] >> (8-j-1)) & 1);
    return 0;
}

int SystemInfoChange_r10::systemInformationBlockType1_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return systemInformationBlockType1_r10_Unpack(bits, idx);
}

int SystemInfoChange_r10::systemInformationBlockType1_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
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
    systemInformationBlockType1_r10_internal_value.clear();
    if((idx +size*8) > bits.size())
    {
        printf("SystemInfoChange_r10::systemInformationBlockType1_r10_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
    {
        uint8_t value = 0;
        for(uint32_t j=0; j<8; j++)
            value |= bits[idx+j] << (8-j-1);
        systemInformationBlockType1_r10_internal_value.push_back(value);
        idx += 8;
    }
    systemInformationBlockType1_r10_present = true;
    return 0;
}

std::vector<uint8_t> SystemInfoChange_r10::systemInformationBlockType1_r10_Value() const
{
    if(systemInformationBlockType1_r10_present)
        return systemInformationBlockType1_r10_internal_value;
    std::vector<uint8_t> tmp;
    return tmp;
}

int SystemInfoChange_r10::systemInformationBlockType1_r10_SetValue(std::vector<uint8_t> value)
{
    systemInformationBlockType1_r10_internal_value = value;
    systemInformationBlockType1_r10_present = true;
    return 0;
}

std::string SystemInfoChange_r10::systemInformationBlockType1_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "systemInformationBlockType1_r10 = {";
    for(auto byte : systemInformationBlockType1_r10_internal_value)
        out += std::to_string(byte) + ",";
    out = out.substr(0, out.length()-1) + "}\n";
    return out;
}

std::string SystemInfoChange_r10::systemInformationBlockType1_r10_ToStringNoNewLines() const
{
    std::string out = "systemInformationBlockType1_r10={";
    for(auto byte : systemInformationBlockType1_r10_internal_value)
        out += std::to_string(byte) + ",";
    out = out.substr(0, out.length()-1) + "},";
    return out;
}

int SystemInfoChange_r10::systemInformationBlockType1_r10_Clear()
{
    systemInformationBlockType1_r10_present = false;
    return 0;
}

bool SystemInfoChange_r10::systemInformationBlockType1_r10_IsPresent() const
{
    return systemInformationBlockType1_r10_present;
}

SystemInformationBlockType2* SystemInfoChange_r10::systemInformationBlockType2_r10_Set()
{
    systemInformationBlockType2_r10_present = true;
    return &systemInformationBlockType2_r10;
}

int SystemInfoChange_r10::systemInformationBlockType2_r10_Set(SystemInformationBlockType2 &value)
{
    systemInformationBlockType2_r10_present = true;
    systemInformationBlockType2_r10 = value;
    return 0;
}

const SystemInformationBlockType2& SystemInfoChange_r10::systemInformationBlockType2_r10_Get() const
{
    return systemInformationBlockType2_r10;
}

std::string SystemInfoChange_r10::systemInformationBlockType2_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "systemInformationBlockType2_r10:\n";
    out += systemInformationBlockType2_r10.ToString(indent+1);
    return out;
}

std::string SystemInfoChange_r10::systemInformationBlockType2_r10_ToStringNoNewLines() const
{
    std::string out = "systemInformationBlockType2_r10:";
    out += systemInformationBlockType2_r10.ToStringNoNewLines();
    return out;
}

int SystemInfoChange_r10::systemInformationBlockType2_r10_Clear()
{
    systemInformationBlockType2_r10_present = false;
    return 0;
}

bool SystemInfoChange_r10::systemInformationBlockType2_r10_IsPresent() const
{
    return systemInformationBlockType2_r10_present;
}

