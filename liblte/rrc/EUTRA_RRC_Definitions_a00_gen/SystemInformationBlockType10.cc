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

#include "SystemInformationBlockType10.h"

#include <cmath>

int SystemInformationBlockType10::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator
    bool has_extension = false;
    if(lateNonCriticalExtension_IsPresent())
    {
        bits.push_back(1);
        has_extension = true;
    }else{
        bits.push_back(0);
    }

    // Optional indicators
    bits.push_back(warningSecurityInfo_IsPresent());

    // Fields
    {
        if(0 != messageIdentifier_Pack(bits))
        {
            printf("SystemInformationBlockType10:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != serialNumber_Pack(bits))
        {
            printf("SystemInformationBlockType10:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != warningType_Pack(bits))
        {
            printf("SystemInformationBlockType10:: field pack failure\n");
            return -1;
        }
    }
    if(warningSecurityInfo_IsPresent())
    {
        if(0 != warningSecurityInfo_Pack(bits))
        {
            printf("SystemInformationBlockType10:: field pack failure\n");
            return -1;
        }
    }

    // Extension
    if(has_extension)
    {
        // Number of extension fields
        if(0 < 64)
        {
            bits.push_back(0);
            for(uint32_t i=0; i<6; i++)
                bits.push_back((0 >> (6-i-1)) & 1);
        }else{
            printf("SystemInformationBlockType10:: Extension list size too large failure\n");
            return -1;
        }

        // Extension field presence indicators
        bits.push_back(lateNonCriticalExtension_IsPresent());

        // Extension fields
        if(lateNonCriticalExtension_IsPresent())
        {
            std::vector<uint8_t> field_bits;
            if(0 != lateNonCriticalExtension_Pack(field_bits))
            {
                printf("SystemInformationBlockType10:: field pack failure\n");
                return -1;
            }
            while((field_bits.size() % 8) != 0)
                field_bits.push_back(0);
            uint32_t N_octets = field_bits.size() / 8;
            uint32_t local_size_length = 0;
            uint32_t local_size = N_octets;
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
            for(auto b : field_bits)
                bits.push_back(b);
        }
    }
    return 0;
}

int SystemInformationBlockType10::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int SystemInformationBlockType10::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("SystemInformationBlockType10::Unpack() index out of bounds for extension\n");
        return -1;
    }
    bool has_extension = bits[idx++];

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("SystemInformationBlockType10::Unpack() index out of bounds for optional indiator warningSecurityInfo\n");
        return -1;
    }
    warningSecurityInfo_present = bits[idx++];

    // Fields
    {
        if(0 != messageIdentifier_Unpack(bits, idx))
        {
            printf("SystemInformationBlockType10:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != serialNumber_Unpack(bits, idx))
        {
            printf("SystemInformationBlockType10:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != warningType_Unpack(bits, idx))
        {
            printf("SystemInformationBlockType10:: field unpack failure\n");
            return -1;
        }
    }
    if(warningSecurityInfo_present)
    {
        if(0 != warningSecurityInfo_Unpack(bits, idx))
        {
            printf("SystemInformationBlockType10:: field unpack failure\n");
            return -1;
        }
    }

    // Extension
    if(has_extension)
    {
        if((idx + 7) > bits.size())
        {
            printf("SystemInformationBlockType10::Unpack() index out of bounds for extension size\n");
            return -1;
        }
        // Number of extension fields
        if(bits[idx++] != 0)
        {
            printf("SystemInformationBlockType10:: Extension list size too large failure\n");
            return -1;
        }
        uint32_t N_ext_fields = 0;
        for(uint32_t i=0; i<6; i++)
            N_ext_fields |= bits[idx++] << (6-i-1);
        N_ext_fields++;

        // Extension field presence indicators
        uint32_t opt_ind_count = 0;
        if(opt_ind_count++ < N_ext_fields)
        {
            if((idx + 1) > bits.size())
            {
                printf("SystemInformationBlockType10::Unpack() index out of bounds for optional indiator lateNonCriticalExtension\n");
                return -1;
            }
            lateNonCriticalExtension_present = bits[idx++];
        }
        if((idx + (N_ext_fields - opt_ind_count)) > bits.size())
        {
            printf("SystemInformationBlockType10::Unpack() index out of bounds for extension optional indicators\n");
            return -1;
        }
        idx += (N_ext_fields - opt_ind_count);

        // Extension fields
        if(lateNonCriticalExtension_present)
        {
            uint32_t local_size_length = 0;
            uint32_t N_octets = 0;
            if(0 == bits[idx++])
            {
                local_size_length = 7;
            }else{
                if(0 == bits[idx++])
                {
                    local_size_length = 14;
                }else{
                    for(uint32_t i=0; i<6; i++)
                        N_octets |= bits[idx++] << (6-i-1);
                    N_octets *= 16383;
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
                N_octets |= bits[idx++] << (local_size_length-i-1);
            uint32_t orig_idx = idx;
            if(0 != lateNonCriticalExtension_Unpack(bits, idx))
            {
                printf("SystemInformationBlockType10:: field unpack failure\n");
                return -1;
            }
            idx = orig_idx + (N_octets * 8);
        }
        for(uint32_t i=1; i<N_ext_fields; i++)
        {
            uint32_t local_size_length = 0;
            uint32_t N_octets = 0;
            if(0 == bits[idx++])
            {
                local_size_length = 7;
            }else{
                if(0 == bits[idx++])
                {
                    local_size_length = 14;
                }else{
                    for(uint32_t i=0; i<6; i++)
                        N_octets |= bits[idx++] << (6-i-1);
                    N_octets *= 16383;
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
                N_octets |= bits[idx++] << (local_size_length-i-1);
        if((idx + (N_octets * 8)) > bits.size())
        {
            printf("SystemInformationBlockType10::Unpack() index out of bounds for extension fields\n");
            return -1;
        }
            idx += N_octets * 8;
        }
    }
    return 0;
}

std::string SystemInformationBlockType10::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "SystemInformationBlockType10:\n";
    out += messageIdentifier_ToString(indent+1);
    out += serialNumber_ToString(indent+1);
    out += warningType_ToString(indent+1);
    if(warningSecurityInfo_IsPresent())
        out += warningSecurityInfo_ToString(indent+1);
    if(lateNonCriticalExtension_IsPresent())
        out += lateNonCriticalExtension_ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType10::ToStringNoNewLines() const
{
    std::string out = "SystemInformationBlockType10:";
    out += messageIdentifier_ToStringNoNewLines();
    out += serialNumber_ToStringNoNewLines();
    out += warningType_ToStringNoNewLines();
    if(warningSecurityInfo_IsPresent())
        out += warningSecurityInfo_ToStringNoNewLines();
    if(lateNonCriticalExtension_IsPresent())
        out += lateNonCriticalExtension_ToStringNoNewLines();
    return out;
}

int SystemInformationBlockType10::messageIdentifier_Pack(std::vector<uint8_t> &bits)
{
    if(!messageIdentifier_present)
    {
        printf("SystemInformationBlockType10::messageIdentifier_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 16;
    if(size < 16 || size > 16)
    {
        printf("SystemInformationBlockType10::messageIdentifier_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((messageIdentifier_internal_value >> (16-i-1)) & 1);
    return 0;
}

int SystemInformationBlockType10::messageIdentifier_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return messageIdentifier_Unpack(bits, idx);
}

int SystemInformationBlockType10::messageIdentifier_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 16;
    if(size < 16 || size > 16)
    {
        printf("SystemInformationBlockType10::messageIdentifier_Unpack() size failure\n");
        return -1;
    }
    messageIdentifier_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("SystemInformationBlockType10::messageIdentifier_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        messageIdentifier_internal_value |= (uint16_t)bits[idx++] << (uint16_t)(16-i-1);
    messageIdentifier_present = true;
    return 0;
}

uint16_t SystemInformationBlockType10::messageIdentifier_Value() const
{
    if(messageIdentifier_present)
        return messageIdentifier_internal_value;
    uint16_t tmp = 0;
    return tmp;
}

int SystemInformationBlockType10::messageIdentifier_SetValue(uint16_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 16)
    {
        printf("SystemInformationBlockType10::messageIdentifier_SetValue() size failure\n");
        return -1;
    }
    messageIdentifier_internal_value = value;
    messageIdentifier_present = true;
    return 0;
}

std::string SystemInformationBlockType10::messageIdentifier_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "messageIdentifier = ";
    out += std::to_string(messageIdentifier_internal_value);
    out += "\n";
    return out;
}

std::string SystemInformationBlockType10::messageIdentifier_ToStringNoNewLines() const
{
    std::string out = "messageIdentifier=";
    out += std::to_string(messageIdentifier_internal_value);
    out += ",";
    return out;
}

int SystemInformationBlockType10::messageIdentifier_Clear()
{
    messageIdentifier_present = false;
    return 0;
}

bool SystemInformationBlockType10::messageIdentifier_IsPresent() const
{
    return messageIdentifier_present;
}

int SystemInformationBlockType10::serialNumber_Pack(std::vector<uint8_t> &bits)
{
    if(!serialNumber_present)
    {
        printf("SystemInformationBlockType10::serialNumber_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 16;
    if(size < 16 || size > 16)
    {
        printf("SystemInformationBlockType10::serialNumber_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((serialNumber_internal_value >> (16-i-1)) & 1);
    return 0;
}

int SystemInformationBlockType10::serialNumber_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return serialNumber_Unpack(bits, idx);
}

int SystemInformationBlockType10::serialNumber_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 16;
    if(size < 16 || size > 16)
    {
        printf("SystemInformationBlockType10::serialNumber_Unpack() size failure\n");
        return -1;
    }
    serialNumber_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("SystemInformationBlockType10::serialNumber_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        serialNumber_internal_value |= (uint16_t)bits[idx++] << (uint16_t)(16-i-1);
    serialNumber_present = true;
    return 0;
}

uint16_t SystemInformationBlockType10::serialNumber_Value() const
{
    if(serialNumber_present)
        return serialNumber_internal_value;
    uint16_t tmp = 0;
    return tmp;
}

int SystemInformationBlockType10::serialNumber_SetValue(uint16_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 16)
    {
        printf("SystemInformationBlockType10::serialNumber_SetValue() size failure\n");
        return -1;
    }
    serialNumber_internal_value = value;
    serialNumber_present = true;
    return 0;
}

std::string SystemInformationBlockType10::serialNumber_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "serialNumber = ";
    out += std::to_string(serialNumber_internal_value);
    out += "\n";
    return out;
}

std::string SystemInformationBlockType10::serialNumber_ToStringNoNewLines() const
{
    std::string out = "serialNumber=";
    out += std::to_string(serialNumber_internal_value);
    out += ",";
    return out;
}

int SystemInformationBlockType10::serialNumber_Clear()
{
    serialNumber_present = false;
    return 0;
}

bool SystemInformationBlockType10::serialNumber_IsPresent() const
{
    return serialNumber_present;
}

int SystemInformationBlockType10::warningType_Pack(std::vector<uint8_t> &bits)
{
    if(!warningType_present)
    {
        printf("SystemInformationBlockType10::warningType_Pack() presence failure\n");
        return -1;
    }
    if(warningType_internal_value.size() < 2 || warningType_internal_value.size() > 2)
    {
        printf("SystemInformationBlockType10::warningType_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<warningType_internal_value.size(); i++)
        for(uint32_t j=0; j<8; j++)
            bits.push_back((warningType_internal_value[i] >> (8-j-1)) & 1);
    return 0;
}

int SystemInformationBlockType10::warningType_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return warningType_Unpack(bits, idx);
}

int SystemInformationBlockType10::warningType_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 2;
    if(size < 2 || size > 2)
    {
        printf("SystemInformationBlockType10::warningType_Unpack() size failure\n");
        return -1;
    }
    warningType_internal_value.clear();
    if((idx +size*8) > bits.size())
    {
        printf("SystemInformationBlockType10::warningType_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
    {
        uint8_t value = 0;
        for(uint32_t j=0; j<8; j++)
            value |= bits[idx+j] << (8-j-1);
        warningType_internal_value.push_back(value);
        idx += 8;
    }
    warningType_present = true;
    return 0;
}

std::vector<uint8_t> SystemInformationBlockType10::warningType_Value() const
{
    if(warningType_present)
        return warningType_internal_value;
    std::vector<uint8_t> tmp;
    return tmp;
}

int SystemInformationBlockType10::warningType_SetValue(std::vector<uint8_t> value)
{
    if(value.size() < 2 || value.size() > 2)
    {
        printf("SystemInformationBlockType10::warningType_SetValue() size failure\n");
        return -1;
    }
    warningType_internal_value = value;
    warningType_present = true;
    return 0;
}

std::string SystemInformationBlockType10::warningType_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "warningType = {";
    for(auto byte : warningType_internal_value)
        out += std::to_string(byte) + ",";
    out = out.substr(0, out.length()-1) + "}\n";
    return out;
}

std::string SystemInformationBlockType10::warningType_ToStringNoNewLines() const
{
    std::string out = "warningType={";
    for(auto byte : warningType_internal_value)
        out += std::to_string(byte) + ",";
    out = out.substr(0, out.length()-1) + "},";
    return out;
}

int SystemInformationBlockType10::warningType_Clear()
{
    warningType_present = false;
    return 0;
}

bool SystemInformationBlockType10::warningType_IsPresent() const
{
    return warningType_present;
}

int SystemInformationBlockType10::warningSecurityInfo_Pack(std::vector<uint8_t> &bits)
{
    if(warningSecurityInfo_internal_value.size() < 50 || warningSecurityInfo_internal_value.size() > 50)
    {
        printf("SystemInformationBlockType10::warningSecurityInfo_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<warningSecurityInfo_internal_value.size(); i++)
        for(uint32_t j=0; j<8; j++)
            bits.push_back((warningSecurityInfo_internal_value[i] >> (8-j-1)) & 1);
    return 0;
}

int SystemInformationBlockType10::warningSecurityInfo_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return warningSecurityInfo_Unpack(bits, idx);
}

int SystemInformationBlockType10::warningSecurityInfo_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 50;
    if(size < 50 || size > 50)
    {
        printf("SystemInformationBlockType10::warningSecurityInfo_Unpack() size failure\n");
        return -1;
    }
    warningSecurityInfo_internal_value.clear();
    if((idx +size*8) > bits.size())
    {
        printf("SystemInformationBlockType10::warningSecurityInfo_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
    {
        uint8_t value = 0;
        for(uint32_t j=0; j<8; j++)
            value |= bits[idx+j] << (8-j-1);
        warningSecurityInfo_internal_value.push_back(value);
        idx += 8;
    }
    warningSecurityInfo_present = true;
    return 0;
}

std::vector<uint8_t> SystemInformationBlockType10::warningSecurityInfo_Value() const
{
    if(warningSecurityInfo_present)
        return warningSecurityInfo_internal_value;
    std::vector<uint8_t> tmp;
    return tmp;
}

int SystemInformationBlockType10::warningSecurityInfo_SetValue(std::vector<uint8_t> value)
{
    if(value.size() < 50 || value.size() > 50)
    {
        printf("SystemInformationBlockType10::warningSecurityInfo_SetValue() size failure\n");
        return -1;
    }
    warningSecurityInfo_internal_value = value;
    warningSecurityInfo_present = true;
    return 0;
}

std::string SystemInformationBlockType10::warningSecurityInfo_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "warningSecurityInfo = {";
    for(auto byte : warningSecurityInfo_internal_value)
        out += std::to_string(byte) + ",";
    out = out.substr(0, out.length()-1) + "}\n";
    return out;
}

std::string SystemInformationBlockType10::warningSecurityInfo_ToStringNoNewLines() const
{
    std::string out = "warningSecurityInfo={";
    for(auto byte : warningSecurityInfo_internal_value)
        out += std::to_string(byte) + ",";
    out = out.substr(0, out.length()-1) + "},";
    return out;
}

int SystemInformationBlockType10::warningSecurityInfo_Clear()
{
    warningSecurityInfo_present = false;
    return 0;
}

bool SystemInformationBlockType10::warningSecurityInfo_IsPresent() const
{
    return warningSecurityInfo_present;
}

int SystemInformationBlockType10::lateNonCriticalExtension_Pack(std::vector<uint8_t> &bits)
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

int SystemInformationBlockType10::lateNonCriticalExtension_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return lateNonCriticalExtension_Unpack(bits, idx);
}

int SystemInformationBlockType10::lateNonCriticalExtension_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
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
        printf("SystemInformationBlockType10::lateNonCriticalExtension_Unpack() index out of bounds\n");
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

std::vector<uint8_t> SystemInformationBlockType10::lateNonCriticalExtension_Value() const
{
    if(lateNonCriticalExtension_present)
        return lateNonCriticalExtension_internal_value;
    std::vector<uint8_t> tmp;
    return tmp;
}

int SystemInformationBlockType10::lateNonCriticalExtension_SetValue(std::vector<uint8_t> value)
{
    lateNonCriticalExtension_internal_value = value;
    lateNonCriticalExtension_present = true;
    return 0;
}

std::string SystemInformationBlockType10::lateNonCriticalExtension_ToString(uint32_t indent) const
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

std::string SystemInformationBlockType10::lateNonCriticalExtension_ToStringNoNewLines() const
{
    std::string out = "lateNonCriticalExtension={";
    for(auto byte : lateNonCriticalExtension_internal_value)
        out += std::to_string(byte) + ",";
    out = out.substr(0, out.length()-1) + "},";
    return out;
}

int SystemInformationBlockType10::lateNonCriticalExtension_Clear()
{
    lateNonCriticalExtension_present = false;
    return 0;
}

bool SystemInformationBlockType10::lateNonCriticalExtension_IsPresent() const
{
    return lateNonCriticalExtension_present;
}

