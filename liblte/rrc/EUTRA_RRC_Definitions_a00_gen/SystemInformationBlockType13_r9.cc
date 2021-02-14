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

#include "SystemInformationBlockType13_r9.h"

#include <cmath>

int SystemInformationBlockType13_r9::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator
    bits.push_back(0);

    // Optional indicators
    bits.push_back(lateNonCriticalExtension_IsPresent());

    // Fields
    {
        if(0 != mbsfn_AreaInfoList_r9.Pack(bits))
        {
            printf("SystemInformationBlockType13_r9:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != notificationConfig_r9.Pack(bits))
        {
            printf("SystemInformationBlockType13_r9:: field pack failure\n");
            return -1;
        }
    }
    if(lateNonCriticalExtension_IsPresent())
    {
        if(0 != lateNonCriticalExtension_Pack(bits))
        {
            printf("SystemInformationBlockType13_r9:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int SystemInformationBlockType13_r9::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int SystemInformationBlockType13_r9::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("SystemInformationBlockType13_r9::Unpack() index out of bounds for extension\n");
        return -1;
    }
    idx++;

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("SystemInformationBlockType13_r9::Unpack() index out of bounds for optional indiator lateNonCriticalExtension\n");
        return -1;
    }
    lateNonCriticalExtension_present = bits[idx++];

    // Fields
    {
        if(0 != mbsfn_AreaInfoList_r9.Unpack(bits, idx))
        {
            printf("SystemInformationBlockType13_r9:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != notificationConfig_r9.Unpack(bits, idx))
        {
            printf("SystemInformationBlockType13_r9:: field unpack failure\n");
            return -1;
        }
    }
    if(lateNonCriticalExtension_present)
    {
        if(0 != lateNonCriticalExtension_Unpack(bits, idx))
        {
            printf("SystemInformationBlockType13_r9:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string SystemInformationBlockType13_r9::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "SystemInformationBlockType13_r9:\n";
    out += mbsfn_AreaInfoList_r9_ToString(indent+1);
    out += notificationConfig_r9_ToString(indent+1);
    if(lateNonCriticalExtension_IsPresent())
        out += lateNonCriticalExtension_ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType13_r9::ToStringNoNewLines() const
{
    std::string out = "SystemInformationBlockType13_r9:";
    out += mbsfn_AreaInfoList_r9_ToStringNoNewLines();
    out += notificationConfig_r9_ToStringNoNewLines();
    if(lateNonCriticalExtension_IsPresent())
        out += lateNonCriticalExtension_ToStringNoNewLines();
    return out;
}

MBSFN_AreaInfoList_r9* SystemInformationBlockType13_r9::mbsfn_AreaInfoList_r9_Set()
{
    mbsfn_AreaInfoList_r9_present = true;
    return &mbsfn_AreaInfoList_r9;
}

int SystemInformationBlockType13_r9::mbsfn_AreaInfoList_r9_Set(MBSFN_AreaInfoList_r9 &value)
{
    mbsfn_AreaInfoList_r9_present = true;
    mbsfn_AreaInfoList_r9 = value;
    return 0;
}

const MBSFN_AreaInfoList_r9& SystemInformationBlockType13_r9::mbsfn_AreaInfoList_r9_Get() const
{
    return mbsfn_AreaInfoList_r9;
}

std::string SystemInformationBlockType13_r9::mbsfn_AreaInfoList_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "mbsfn_AreaInfoList_r9:\n";
    out += mbsfn_AreaInfoList_r9.ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType13_r9::mbsfn_AreaInfoList_r9_ToStringNoNewLines() const
{
    std::string out = "mbsfn_AreaInfoList_r9:";
    out += mbsfn_AreaInfoList_r9.ToStringNoNewLines();
    return out;
}

int SystemInformationBlockType13_r9::mbsfn_AreaInfoList_r9_Clear()
{
    mbsfn_AreaInfoList_r9_present = false;
    return 0;
}

bool SystemInformationBlockType13_r9::mbsfn_AreaInfoList_r9_IsPresent() const
{
    return mbsfn_AreaInfoList_r9_present;
}

MBMS_NotificationConfig_r9* SystemInformationBlockType13_r9::notificationConfig_r9_Set()
{
    notificationConfig_r9_present = true;
    return &notificationConfig_r9;
}

int SystemInformationBlockType13_r9::notificationConfig_r9_Set(MBMS_NotificationConfig_r9 &value)
{
    notificationConfig_r9_present = true;
    notificationConfig_r9 = value;
    return 0;
}

const MBMS_NotificationConfig_r9& SystemInformationBlockType13_r9::notificationConfig_r9_Get() const
{
    return notificationConfig_r9;
}

std::string SystemInformationBlockType13_r9::notificationConfig_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "notificationConfig_r9:\n";
    out += notificationConfig_r9.ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType13_r9::notificationConfig_r9_ToStringNoNewLines() const
{
    std::string out = "notificationConfig_r9:";
    out += notificationConfig_r9.ToStringNoNewLines();
    return out;
}

int SystemInformationBlockType13_r9::notificationConfig_r9_Clear()
{
    notificationConfig_r9_present = false;
    return 0;
}

bool SystemInformationBlockType13_r9::notificationConfig_r9_IsPresent() const
{
    return notificationConfig_r9_present;
}

int SystemInformationBlockType13_r9::lateNonCriticalExtension_Pack(std::vector<uint8_t> &bits)
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

int SystemInformationBlockType13_r9::lateNonCriticalExtension_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return lateNonCriticalExtension_Unpack(bits, idx);
}

int SystemInformationBlockType13_r9::lateNonCriticalExtension_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
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
        printf("SystemInformationBlockType13_r9::lateNonCriticalExtension_Unpack() index out of bounds\n");
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

std::vector<uint8_t> SystemInformationBlockType13_r9::lateNonCriticalExtension_Value() const
{
    if(lateNonCriticalExtension_present)
        return lateNonCriticalExtension_internal_value;
    std::vector<uint8_t> tmp;
    return tmp;
}

int SystemInformationBlockType13_r9::lateNonCriticalExtension_SetValue(std::vector<uint8_t> value)
{
    lateNonCriticalExtension_internal_value = value;
    lateNonCriticalExtension_present = true;
    return 0;
}

std::string SystemInformationBlockType13_r9::lateNonCriticalExtension_ToString(uint32_t indent) const
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

std::string SystemInformationBlockType13_r9::lateNonCriticalExtension_ToStringNoNewLines() const
{
    std::string out = "lateNonCriticalExtension={";
    for(auto byte : lateNonCriticalExtension_internal_value)
        out += std::to_string(byte) + ",";
    out = out.substr(0, out.length()-1) + "},";
    return out;
}

int SystemInformationBlockType13_r9::lateNonCriticalExtension_Clear()
{
    lateNonCriticalExtension_present = false;
    return 0;
}

bool SystemInformationBlockType13_r9::lateNonCriticalExtension_IsPresent() const
{
    return lateNonCriticalExtension_present;
}

