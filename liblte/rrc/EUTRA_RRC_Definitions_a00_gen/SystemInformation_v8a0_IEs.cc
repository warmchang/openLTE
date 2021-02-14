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

#include "SystemInformation_v8a0_IEs.h"

#include <cmath>

int SystemInformation_v8a0_IEs::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(lateNonCriticalExtension_IsPresent());
    bits.push_back(0);

    // Fields
    if(lateNonCriticalExtension_IsPresent())
    {
        if(0 != lateNonCriticalExtension_Pack(bits))
        {
            printf("SystemInformation_v8a0_IEs:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int SystemInformation_v8a0_IEs::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int SystemInformation_v8a0_IEs::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("SystemInformation_v8a0_IEs::Unpack() index out of bounds for optional indiator lateNonCriticalExtension\n");
        return -1;
    }
    lateNonCriticalExtension_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("SystemInformation_v8a0_IEs::Unpack() index out of bounds for optional indiator nonCriticalExtension\n");
        return -1;
    }
    idx++;

    // Fields
    if(lateNonCriticalExtension_present)
    {
        if(0 != lateNonCriticalExtension_Unpack(bits, idx))
        {
            printf("SystemInformation_v8a0_IEs:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string SystemInformation_v8a0_IEs::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "SystemInformation_v8a0_IEs:\n";
    if(lateNonCriticalExtension_IsPresent())
        out += lateNonCriticalExtension_ToString(indent+1);
    return out;
}

std::string SystemInformation_v8a0_IEs::ToStringNoNewLines() const
{
    std::string out = "SystemInformation_v8a0_IEs:";
    if(lateNonCriticalExtension_IsPresent())
        out += lateNonCriticalExtension_ToStringNoNewLines();
    return out;
}

int SystemInformation_v8a0_IEs::lateNonCriticalExtension_Pack(std::vector<uint8_t> &bits)
{
    uint32_t local_size_length = 0;
    uint32_t local_size = lateNonCriticalExtension_internal_value.size();
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
    for(uint32_t i=0; i<lateNonCriticalExtension_internal_value.size(); i++)
        for(uint32_t j=0; j<8; j++)
            bits.push_back((lateNonCriticalExtension_internal_value[i] >> (8-j-1)) & 1);
    return 0;
}

int SystemInformation_v8a0_IEs::lateNonCriticalExtension_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return lateNonCriticalExtension_Unpack(bits, idx);
}

int SystemInformation_v8a0_IEs::lateNonCriticalExtension_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
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
    lateNonCriticalExtension_internal_value.clear();
    if((idx +size*8) > bits.size())
    {
        printf("SystemInformation_v8a0_IEs::lateNonCriticalExtension_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
    {
        uint8_t value = 0;
        for(uint32_t j=0; j<8; j++)
            value |= bits[idx+j] << (8-j-1);
        lateNonCriticalExtension_internal_value.push_back(value);
        idx += 8;
    }
    lateNonCriticalExtension_present = true;
    return 0;
}

std::vector<uint8_t> SystemInformation_v8a0_IEs::lateNonCriticalExtension_Value() const
{
    if(lateNonCriticalExtension_present)
        return lateNonCriticalExtension_internal_value;
    std::vector<uint8_t> tmp;
    return tmp;
}

int SystemInformation_v8a0_IEs::lateNonCriticalExtension_SetValue(std::vector<uint8_t> value)
{
    lateNonCriticalExtension_internal_value = value;
    lateNonCriticalExtension_present = true;
    return 0;
}

std::string SystemInformation_v8a0_IEs::lateNonCriticalExtension_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "lateNonCriticalExtension = {";
    for(auto byte : lateNonCriticalExtension_internal_value)
        out += std::to_string(byte) + ",";
    out = out.substr(0, out.length()-1) + "}\n";
    return out;
}

std::string SystemInformation_v8a0_IEs::lateNonCriticalExtension_ToStringNoNewLines() const
{
    std::string out = "lateNonCriticalExtension={";
    for(auto byte : lateNonCriticalExtension_internal_value)
        out += std::to_string(byte) + ",";
    out = out.substr(0, out.length()-1) + "},";
    return out;
}

int SystemInformation_v8a0_IEs::lateNonCriticalExtension_Clear()
{
    lateNonCriticalExtension_present = false;
    return 0;
}

bool SystemInformation_v8a0_IEs::lateNonCriticalExtension_IsPresent() const
{
    return lateNonCriticalExtension_present;
}

