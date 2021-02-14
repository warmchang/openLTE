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

#include "SystemInformationBlockType11.h"

#include <cmath>

int SystemInformationBlockType11::Pack(std::vector<uint8_t> &bits)
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
    bits.push_back(dataCodingScheme_IsPresent());

    // Fields
    {
        if(0 != messageIdentifier_Pack(bits))
        {
            printf("SystemInformationBlockType11:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != serialNumber_Pack(bits))
        {
            printf("SystemInformationBlockType11:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != warningMessageSegmentType_Pack(bits))
        {
            printf("SystemInformationBlockType11:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != warningMessageSegmentNumber_Pack(bits))
        {
            printf("SystemInformationBlockType11:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != warningMessageSegment_Pack(bits))
        {
            printf("SystemInformationBlockType11:: field pack failure\n");
            return -1;
        }
    }
    if(dataCodingScheme_IsPresent())
    {
        if(0 != dataCodingScheme_Pack(bits))
        {
            printf("SystemInformationBlockType11:: field pack failure\n");
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
            printf("SystemInformationBlockType11:: Extension list size too large failure\n");
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
                printf("SystemInformationBlockType11:: field pack failure\n");
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

int SystemInformationBlockType11::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int SystemInformationBlockType11::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("SystemInformationBlockType11::Unpack() index out of bounds for extension\n");
        return -1;
    }
    bool has_extension = bits[idx++];

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("SystemInformationBlockType11::Unpack() index out of bounds for optional indiator dataCodingScheme\n");
        return -1;
    }
    dataCodingScheme_present = bits[idx++];

    // Fields
    {
        if(0 != messageIdentifier_Unpack(bits, idx))
        {
            printf("SystemInformationBlockType11:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != serialNumber_Unpack(bits, idx))
        {
            printf("SystemInformationBlockType11:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != warningMessageSegmentType_Unpack(bits, idx))
        {
            printf("SystemInformationBlockType11:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != warningMessageSegmentNumber_Unpack(bits, idx))
        {
            printf("SystemInformationBlockType11:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != warningMessageSegment_Unpack(bits, idx))
        {
            printf("SystemInformationBlockType11:: field unpack failure\n");
            return -1;
        }
    }
    if(dataCodingScheme_present)
    {
        if(0 != dataCodingScheme_Unpack(bits, idx))
        {
            printf("SystemInformationBlockType11:: field unpack failure\n");
            return -1;
        }
    }

    // Extension
    if(has_extension)
    {
        if((idx + 7) > bits.size())
        {
            printf("SystemInformationBlockType11::Unpack() index out of bounds for extension size\n");
            return -1;
        }
        // Number of extension fields
        if(bits[idx++] != 0)
        {
            printf("SystemInformationBlockType11:: Extension list size too large failure\n");
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
                printf("SystemInformationBlockType11::Unpack() index out of bounds for optional indiator lateNonCriticalExtension\n");
                return -1;
            }
            lateNonCriticalExtension_present = bits[idx++];
        }
        if((idx + (N_ext_fields - opt_ind_count)) > bits.size())
        {
            printf("SystemInformationBlockType11::Unpack() index out of bounds for extension optional indicators\n");
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
                printf("SystemInformationBlockType11:: field unpack failure\n");
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
            printf("SystemInformationBlockType11::Unpack() index out of bounds for extension fields\n");
            return -1;
        }
            idx += N_octets * 8;
        }
    }
    return 0;
}

std::string SystemInformationBlockType11::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "SystemInformationBlockType11:\n";
    out += messageIdentifier_ToString(indent+1);
    out += serialNumber_ToString(indent+1);
    out += warningMessageSegmentType_ToString(indent+1);
    out += warningMessageSegmentNumber_ToString(indent+1);
    out += warningMessageSegment_ToString(indent+1);
    if(dataCodingScheme_IsPresent())
        out += dataCodingScheme_ToString(indent+1);
    if(lateNonCriticalExtension_IsPresent())
        out += lateNonCriticalExtension_ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType11::ToStringNoNewLines() const
{
    std::string out = "SystemInformationBlockType11:";
    out += messageIdentifier_ToStringNoNewLines();
    out += serialNumber_ToStringNoNewLines();
    out += warningMessageSegmentType_ToStringNoNewLines();
    out += warningMessageSegmentNumber_ToStringNoNewLines();
    out += warningMessageSegment_ToStringNoNewLines();
    if(dataCodingScheme_IsPresent())
        out += dataCodingScheme_ToStringNoNewLines();
    if(lateNonCriticalExtension_IsPresent())
        out += lateNonCriticalExtension_ToStringNoNewLines();
    return out;
}

int SystemInformationBlockType11::messageIdentifier_Pack(std::vector<uint8_t> &bits)
{
    if(!messageIdentifier_present)
    {
        printf("SystemInformationBlockType11::messageIdentifier_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 16;
    if(size < 16 || size > 16)
    {
        printf("SystemInformationBlockType11::messageIdentifier_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((messageIdentifier_internal_value >> (16-i-1)) & 1);
    return 0;
}

int SystemInformationBlockType11::messageIdentifier_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return messageIdentifier_Unpack(bits, idx);
}

int SystemInformationBlockType11::messageIdentifier_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 16;
    if(size < 16 || size > 16)
    {
        printf("SystemInformationBlockType11::messageIdentifier_Unpack() size failure\n");
        return -1;
    }
    messageIdentifier_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("SystemInformationBlockType11::messageIdentifier_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        messageIdentifier_internal_value |= (uint16_t)bits[idx++] << (uint16_t)(16-i-1);
    messageIdentifier_present = true;
    return 0;
}

uint16_t SystemInformationBlockType11::messageIdentifier_Value() const
{
    if(messageIdentifier_present)
        return messageIdentifier_internal_value;
    uint16_t tmp = 0;
    return tmp;
}

int SystemInformationBlockType11::messageIdentifier_SetValue(uint16_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 16)
    {
        printf("SystemInformationBlockType11::messageIdentifier_SetValue() size failure\n");
        return -1;
    }
    messageIdentifier_internal_value = value;
    messageIdentifier_present = true;
    return 0;
}

std::string SystemInformationBlockType11::messageIdentifier_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "messageIdentifier = ";
    out += std::to_string(messageIdentifier_internal_value);
    out += "\n";
    return out;
}

std::string SystemInformationBlockType11::messageIdentifier_ToStringNoNewLines() const
{
    std::string out = "messageIdentifier=";
    out += std::to_string(messageIdentifier_internal_value);
    out += ",";
    return out;
}

int SystemInformationBlockType11::messageIdentifier_Clear()
{
    messageIdentifier_present = false;
    return 0;
}

bool SystemInformationBlockType11::messageIdentifier_IsPresent() const
{
    return messageIdentifier_present;
}

int SystemInformationBlockType11::serialNumber_Pack(std::vector<uint8_t> &bits)
{
    if(!serialNumber_present)
    {
        printf("SystemInformationBlockType11::serialNumber_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 16;
    if(size < 16 || size > 16)
    {
        printf("SystemInformationBlockType11::serialNumber_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((serialNumber_internal_value >> (16-i-1)) & 1);
    return 0;
}

int SystemInformationBlockType11::serialNumber_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return serialNumber_Unpack(bits, idx);
}

int SystemInformationBlockType11::serialNumber_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 16;
    if(size < 16 || size > 16)
    {
        printf("SystemInformationBlockType11::serialNumber_Unpack() size failure\n");
        return -1;
    }
    serialNumber_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("SystemInformationBlockType11::serialNumber_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        serialNumber_internal_value |= (uint16_t)bits[idx++] << (uint16_t)(16-i-1);
    serialNumber_present = true;
    return 0;
}

uint16_t SystemInformationBlockType11::serialNumber_Value() const
{
    if(serialNumber_present)
        return serialNumber_internal_value;
    uint16_t tmp = 0;
    return tmp;
}

int SystemInformationBlockType11::serialNumber_SetValue(uint16_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 16)
    {
        printf("SystemInformationBlockType11::serialNumber_SetValue() size failure\n");
        return -1;
    }
    serialNumber_internal_value = value;
    serialNumber_present = true;
    return 0;
}

std::string SystemInformationBlockType11::serialNumber_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "serialNumber = ";
    out += std::to_string(serialNumber_internal_value);
    out += "\n";
    return out;
}

std::string SystemInformationBlockType11::serialNumber_ToStringNoNewLines() const
{
    std::string out = "serialNumber=";
    out += std::to_string(serialNumber_internal_value);
    out += ",";
    return out;
}

int SystemInformationBlockType11::serialNumber_Clear()
{
    serialNumber_present = false;
    return 0;
}

bool SystemInformationBlockType11::serialNumber_IsPresent() const
{
    return serialNumber_present;
}

int SystemInformationBlockType11::warningMessageSegmentType_Pack(std::vector<uint8_t> &bits)
{
    if(!warningMessageSegmentType_present)
    {
        printf("SystemInformationBlockType11::warningMessageSegmentType_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((warningMessageSegmentType_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int SystemInformationBlockType11::warningMessageSegmentType_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return warningMessageSegmentType_Unpack(bits, idx);
}

int SystemInformationBlockType11::warningMessageSegmentType_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("SystemInformationBlockType11::warningMessageSegmentType_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 1)
    {
        printf("SystemInformationBlockType11::warningMessageSegmentType_Unpack() max failure\n");
        return -1;
    }
    warningMessageSegmentType_internal_value = (warningMessageSegmentType_Enum)packed_val;
    warningMessageSegmentType_present = true;
    return 0;
}

SystemInformationBlockType11::warningMessageSegmentType_Enum SystemInformationBlockType11::warningMessageSegmentType_Value() const
{
    if(warningMessageSegmentType_present)
        return warningMessageSegmentType_internal_value;
    return (SystemInformationBlockType11::warningMessageSegmentType_Enum)0;
}

int SystemInformationBlockType11::warningMessageSegmentType_SetValue(warningMessageSegmentType_Enum value)
{
    warningMessageSegmentType_internal_value = value;
    warningMessageSegmentType_present = true;
    return 0;
}

int SystemInformationBlockType11::warningMessageSegmentType_SetValue(std::string value)
{
    if("notLastSegment" == value)
    {
        warningMessageSegmentType_internal_value = k_warningMessageSegmentType_notLastSegment;
        warningMessageSegmentType_present = true;
        return 0;
    }
    if("lastSegment" == value)
    {
        warningMessageSegmentType_internal_value = k_warningMessageSegmentType_lastSegment;
        warningMessageSegmentType_present = true;
        return 0;
    }
    return 1;
}

std::string SystemInformationBlockType11::warningMessageSegmentType_ValueToString(warningMessageSegmentType_Enum value) const
{
    if(k_warningMessageSegmentType_notLastSegment == value)
        return "notLastSegment";
    if(k_warningMessageSegmentType_lastSegment == value)
        return "lastSegment";
    return "";
}

uint64_t SystemInformationBlockType11::warningMessageSegmentType_NumberOfValues() const
{
    return 2;
}

std::string SystemInformationBlockType11::warningMessageSegmentType_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "warningMessageSegmentType = " + warningMessageSegmentType_ValueToString(warningMessageSegmentType_internal_value) + "\n";
    return out;
}

std::string SystemInformationBlockType11::warningMessageSegmentType_ToStringNoNewLines() const
{
    std::string out = "warningMessageSegmentType=" + warningMessageSegmentType_ValueToString(warningMessageSegmentType_internal_value) + ",";
    return out;
}

int SystemInformationBlockType11::warningMessageSegmentType_Clear()
{
    warningMessageSegmentType_present = false;
    return 0;
}

bool SystemInformationBlockType11::warningMessageSegmentType_IsPresent() const
{
    return warningMessageSegmentType_present;
}

int SystemInformationBlockType11::warningMessageSegmentNumber_Pack(std::vector<uint8_t> &bits)
{
    if(!warningMessageSegmentNumber_present)
    {
        printf("SystemInformationBlockType11::warningMessageSegmentNumber_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = warningMessageSegmentNumber_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (63 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int SystemInformationBlockType11::warningMessageSegmentNumber_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return warningMessageSegmentNumber_Unpack(bits, idx);
}

int SystemInformationBlockType11::warningMessageSegmentNumber_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (63 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("SystemInformationBlockType11::warningMessageSegmentNumber_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    warningMessageSegmentNumber_internal_value = packed_val + 0;
    warningMessageSegmentNumber_present = true;
    return 0;
}

int64_t SystemInformationBlockType11::warningMessageSegmentNumber_Value() const
{
    if(warningMessageSegmentNumber_present)
        return warningMessageSegmentNumber_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int SystemInformationBlockType11::warningMessageSegmentNumber_SetValue(int64_t value)
{
    if(value < 0 || value > 63)
    {
        printf("SystemInformationBlockType11::warningMessageSegmentNumber_SetValue() range failure\n");
        return -1;
    }
    warningMessageSegmentNumber_internal_value = value;
    warningMessageSegmentNumber_present = true;
    return 0;
}

std::string SystemInformationBlockType11::warningMessageSegmentNumber_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "warningMessageSegmentNumber = " + std::to_string(warningMessageSegmentNumber_internal_value) + "\n";
    return out;
}

std::string SystemInformationBlockType11::warningMessageSegmentNumber_ToStringNoNewLines() const
{
    std::string out = "warningMessageSegmentNumber=" + std::to_string(warningMessageSegmentNumber_internal_value) + ",";
    return out;
}

int SystemInformationBlockType11::warningMessageSegmentNumber_Clear()
{
    warningMessageSegmentNumber_present = false;
    return 0;
}

bool SystemInformationBlockType11::warningMessageSegmentNumber_IsPresent() const
{
    return warningMessageSegmentNumber_present;
}

int SystemInformationBlockType11::warningMessageSegment_Pack(std::vector<uint8_t> &bits)
{
    if(!warningMessageSegment_present)
    {
        printf("SystemInformationBlockType11::warningMessageSegment_Pack() presence failure\n");
        return -1;
    }
    uint32_t local_size_length = 0;
    uint32_t local_size = warningMessageSegment_internal_value.size();
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
    for(uint32_t i=0; i<warningMessageSegment_internal_value.size(); i++)
        for(uint32_t j=0; j<8; j++)
            bits.push_back((warningMessageSegment_internal_value[i] >> (8-j-1)) & 1);
    return 0;
}

int SystemInformationBlockType11::warningMessageSegment_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return warningMessageSegment_Unpack(bits, idx);
}

int SystemInformationBlockType11::warningMessageSegment_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
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
    warningMessageSegment_internal_value.clear();
    if((idx +size*8) > bits.size())
    {
        printf("SystemInformationBlockType11::warningMessageSegment_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
    {
        uint8_t value = 0;
        for(uint32_t j=0; j<8; j++)
            value |= bits[idx+j] << (8-j-1);
        warningMessageSegment_internal_value.push_back(value);
        idx += 8;
    }
    warningMessageSegment_present = true;
    return 0;
}

std::vector<uint8_t> SystemInformationBlockType11::warningMessageSegment_Value() const
{
    if(warningMessageSegment_present)
        return warningMessageSegment_internal_value;
    std::vector<uint8_t> tmp;
    return tmp;
}

int SystemInformationBlockType11::warningMessageSegment_SetValue(std::vector<uint8_t> value)
{
    warningMessageSegment_internal_value = value;
    warningMessageSegment_present = true;
    return 0;
}

std::string SystemInformationBlockType11::warningMessageSegment_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "warningMessageSegment = {";
    for(auto byte : warningMessageSegment_internal_value)
        out += std::to_string(byte) + ",";
    out = out.substr(0, out.length()-1) + "}\n";
    return out;
}

std::string SystemInformationBlockType11::warningMessageSegment_ToStringNoNewLines() const
{
    std::string out = "warningMessageSegment={";
    for(auto byte : warningMessageSegment_internal_value)
        out += std::to_string(byte) + ",";
    out = out.substr(0, out.length()-1) + "},";
    return out;
}

int SystemInformationBlockType11::warningMessageSegment_Clear()
{
    warningMessageSegment_present = false;
    return 0;
}

bool SystemInformationBlockType11::warningMessageSegment_IsPresent() const
{
    return warningMessageSegment_present;
}

int SystemInformationBlockType11::dataCodingScheme_Pack(std::vector<uint8_t> &bits)
{
    if(dataCodingScheme_internal_value.size() < 1 || dataCodingScheme_internal_value.size() > 1)
    {
        printf("SystemInformationBlockType11::dataCodingScheme_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<dataCodingScheme_internal_value.size(); i++)
        for(uint32_t j=0; j<8; j++)
            bits.push_back((dataCodingScheme_internal_value[i] >> (8-j-1)) & 1);
    return 0;
}

int SystemInformationBlockType11::dataCodingScheme_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return dataCodingScheme_Unpack(bits, idx);
}

int SystemInformationBlockType11::dataCodingScheme_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 1;
    if(size < 1 || size > 1)
    {
        printf("SystemInformationBlockType11::dataCodingScheme_Unpack() size failure\n");
        return -1;
    }
    dataCodingScheme_internal_value.clear();
    if((idx +size*8) > bits.size())
    {
        printf("SystemInformationBlockType11::dataCodingScheme_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
    {
        uint8_t value = 0;
        for(uint32_t j=0; j<8; j++)
            value |= bits[idx+j] << (8-j-1);
        dataCodingScheme_internal_value.push_back(value);
        idx += 8;
    }
    dataCodingScheme_present = true;
    return 0;
}

std::vector<uint8_t> SystemInformationBlockType11::dataCodingScheme_Value() const
{
    if(dataCodingScheme_present)
        return dataCodingScheme_internal_value;
    std::vector<uint8_t> tmp;
    return tmp;
}

int SystemInformationBlockType11::dataCodingScheme_SetValue(std::vector<uint8_t> value)
{
    if(value.size() < 1 || value.size() > 1)
    {
        printf("SystemInformationBlockType11::dataCodingScheme_SetValue() size failure\n");
        return -1;
    }
    dataCodingScheme_internal_value = value;
    dataCodingScheme_present = true;
    return 0;
}

std::string SystemInformationBlockType11::dataCodingScheme_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "dataCodingScheme = {";
    for(auto byte : dataCodingScheme_internal_value)
        out += std::to_string(byte) + ",";
    out = out.substr(0, out.length()-1) + "}\n";
    return out;
}

std::string SystemInformationBlockType11::dataCodingScheme_ToStringNoNewLines() const
{
    std::string out = "dataCodingScheme={";
    for(auto byte : dataCodingScheme_internal_value)
        out += std::to_string(byte) + ",";
    out = out.substr(0, out.length()-1) + "},";
    return out;
}

int SystemInformationBlockType11::dataCodingScheme_Clear()
{
    dataCodingScheme_present = false;
    return 0;
}

bool SystemInformationBlockType11::dataCodingScheme_IsPresent() const
{
    return dataCodingScheme_present;
}

int SystemInformationBlockType11::lateNonCriticalExtension_Pack(std::vector<uint8_t> &bits)
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

int SystemInformationBlockType11::lateNonCriticalExtension_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return lateNonCriticalExtension_Unpack(bits, idx);
}

int SystemInformationBlockType11::lateNonCriticalExtension_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
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
        printf("SystemInformationBlockType11::lateNonCriticalExtension_Unpack() index out of bounds\n");
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

std::vector<uint8_t> SystemInformationBlockType11::lateNonCriticalExtension_Value() const
{
    if(lateNonCriticalExtension_present)
        return lateNonCriticalExtension_internal_value;
    std::vector<uint8_t> tmp;
    return tmp;
}

int SystemInformationBlockType11::lateNonCriticalExtension_SetValue(std::vector<uint8_t> value)
{
    lateNonCriticalExtension_internal_value = value;
    lateNonCriticalExtension_present = true;
    return 0;
}

std::string SystemInformationBlockType11::lateNonCriticalExtension_ToString(uint32_t indent) const
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

std::string SystemInformationBlockType11::lateNonCriticalExtension_ToStringNoNewLines() const
{
    std::string out = "lateNonCriticalExtension={";
    for(auto byte : lateNonCriticalExtension_internal_value)
        out += std::to_string(byte) + ",";
    out = out.substr(0, out.length()-1) + "},";
    return out;
}

int SystemInformationBlockType11::lateNonCriticalExtension_Clear()
{
    lateNonCriticalExtension_present = false;
    return 0;
}

bool SystemInformationBlockType11::lateNonCriticalExtension_IsPresent() const
{
    return lateNonCriticalExtension_present;
}

