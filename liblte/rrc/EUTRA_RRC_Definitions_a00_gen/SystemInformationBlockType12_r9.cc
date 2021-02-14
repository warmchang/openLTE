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

#include "SystemInformationBlockType12_r9.h"

#include <cmath>

int SystemInformationBlockType12_r9::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator
    bits.push_back(0);

    // Optional indicators
    bits.push_back(dataCodingScheme_r9_IsPresent());
    bits.push_back(lateNonCriticalExtension_IsPresent());

    // Fields
    {
        if(0 != messageIdentifier_r9_Pack(bits))
        {
            printf("SystemInformationBlockType12_r9:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != serialNumber_r9_Pack(bits))
        {
            printf("SystemInformationBlockType12_r9:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != warningMessageSegmentType_r9_Pack(bits))
        {
            printf("SystemInformationBlockType12_r9:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != warningMessageSegmentNumber_r9_Pack(bits))
        {
            printf("SystemInformationBlockType12_r9:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != warningMessageSegment_r9_Pack(bits))
        {
            printf("SystemInformationBlockType12_r9:: field pack failure\n");
            return -1;
        }
    }
    if(dataCodingScheme_r9_IsPresent())
    {
        if(0 != dataCodingScheme_r9_Pack(bits))
        {
            printf("SystemInformationBlockType12_r9:: field pack failure\n");
            return -1;
        }
    }
    if(lateNonCriticalExtension_IsPresent())
    {
        if(0 != lateNonCriticalExtension_Pack(bits))
        {
            printf("SystemInformationBlockType12_r9:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int SystemInformationBlockType12_r9::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int SystemInformationBlockType12_r9::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("SystemInformationBlockType12_r9::Unpack() index out of bounds for extension\n");
        return -1;
    }
    idx++;

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("SystemInformationBlockType12_r9::Unpack() index out of bounds for optional indiator dataCodingScheme_r9\n");
        return -1;
    }
    dataCodingScheme_r9_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("SystemInformationBlockType12_r9::Unpack() index out of bounds for optional indiator lateNonCriticalExtension\n");
        return -1;
    }
    lateNonCriticalExtension_present = bits[idx++];

    // Fields
    {
        if(0 != messageIdentifier_r9_Unpack(bits, idx))
        {
            printf("SystemInformationBlockType12_r9:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != serialNumber_r9_Unpack(bits, idx))
        {
            printf("SystemInformationBlockType12_r9:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != warningMessageSegmentType_r9_Unpack(bits, idx))
        {
            printf("SystemInformationBlockType12_r9:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != warningMessageSegmentNumber_r9_Unpack(bits, idx))
        {
            printf("SystemInformationBlockType12_r9:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != warningMessageSegment_r9_Unpack(bits, idx))
        {
            printf("SystemInformationBlockType12_r9:: field unpack failure\n");
            return -1;
        }
    }
    if(dataCodingScheme_r9_present)
    {
        if(0 != dataCodingScheme_r9_Unpack(bits, idx))
        {
            printf("SystemInformationBlockType12_r9:: field unpack failure\n");
            return -1;
        }
    }
    if(lateNonCriticalExtension_present)
    {
        if(0 != lateNonCriticalExtension_Unpack(bits, idx))
        {
            printf("SystemInformationBlockType12_r9:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string SystemInformationBlockType12_r9::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "SystemInformationBlockType12_r9:\n";
    out += messageIdentifier_r9_ToString(indent+1);
    out += serialNumber_r9_ToString(indent+1);
    out += warningMessageSegmentType_r9_ToString(indent+1);
    out += warningMessageSegmentNumber_r9_ToString(indent+1);
    out += warningMessageSegment_r9_ToString(indent+1);
    if(dataCodingScheme_r9_IsPresent())
        out += dataCodingScheme_r9_ToString(indent+1);
    if(lateNonCriticalExtension_IsPresent())
        out += lateNonCriticalExtension_ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType12_r9::ToStringNoNewLines() const
{
    std::string out = "SystemInformationBlockType12_r9:";
    out += messageIdentifier_r9_ToStringNoNewLines();
    out += serialNumber_r9_ToStringNoNewLines();
    out += warningMessageSegmentType_r9_ToStringNoNewLines();
    out += warningMessageSegmentNumber_r9_ToStringNoNewLines();
    out += warningMessageSegment_r9_ToStringNoNewLines();
    if(dataCodingScheme_r9_IsPresent())
        out += dataCodingScheme_r9_ToStringNoNewLines();
    if(lateNonCriticalExtension_IsPresent())
        out += lateNonCriticalExtension_ToStringNoNewLines();
    return out;
}

int SystemInformationBlockType12_r9::messageIdentifier_r9_Pack(std::vector<uint8_t> &bits)
{
    if(!messageIdentifier_r9_present)
    {
        printf("SystemInformationBlockType12_r9::messageIdentifier_r9_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 16;
    if(size < 16 || size > 16)
    {
        printf("SystemInformationBlockType12_r9::messageIdentifier_r9_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((messageIdentifier_r9_internal_value >> (16-i-1)) & 1);
    return 0;
}

int SystemInformationBlockType12_r9::messageIdentifier_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return messageIdentifier_r9_Unpack(bits, idx);
}

int SystemInformationBlockType12_r9::messageIdentifier_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 16;
    if(size < 16 || size > 16)
    {
        printf("SystemInformationBlockType12_r9::messageIdentifier_r9_Unpack() size failure\n");
        return -1;
    }
    messageIdentifier_r9_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("SystemInformationBlockType12_r9::messageIdentifier_r9_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        messageIdentifier_r9_internal_value |= (uint16_t)bits[idx++] << (uint16_t)(16-i-1);
    messageIdentifier_r9_present = true;
    return 0;
}

uint16_t SystemInformationBlockType12_r9::messageIdentifier_r9_Value() const
{
    if(messageIdentifier_r9_present)
        return messageIdentifier_r9_internal_value;
    uint16_t tmp = 0;
    return tmp;
}

int SystemInformationBlockType12_r9::messageIdentifier_r9_SetValue(uint16_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 16)
    {
        printf("SystemInformationBlockType12_r9::messageIdentifier_r9_SetValue() size failure\n");
        return -1;
    }
    messageIdentifier_r9_internal_value = value;
    messageIdentifier_r9_present = true;
    return 0;
}

std::string SystemInformationBlockType12_r9::messageIdentifier_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "messageIdentifier_r9 = ";
    out += std::to_string(messageIdentifier_r9_internal_value);
    out += "\n";
    return out;
}

std::string SystemInformationBlockType12_r9::messageIdentifier_r9_ToStringNoNewLines() const
{
    std::string out = "messageIdentifier_r9=";
    out += std::to_string(messageIdentifier_r9_internal_value);
    out += ",";
    return out;
}

int SystemInformationBlockType12_r9::messageIdentifier_r9_Clear()
{
    messageIdentifier_r9_present = false;
    return 0;
}

bool SystemInformationBlockType12_r9::messageIdentifier_r9_IsPresent() const
{
    return messageIdentifier_r9_present;
}

int SystemInformationBlockType12_r9::serialNumber_r9_Pack(std::vector<uint8_t> &bits)
{
    if(!serialNumber_r9_present)
    {
        printf("SystemInformationBlockType12_r9::serialNumber_r9_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 16;
    if(size < 16 || size > 16)
    {
        printf("SystemInformationBlockType12_r9::serialNumber_r9_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((serialNumber_r9_internal_value >> (16-i-1)) & 1);
    return 0;
}

int SystemInformationBlockType12_r9::serialNumber_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return serialNumber_r9_Unpack(bits, idx);
}

int SystemInformationBlockType12_r9::serialNumber_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 16;
    if(size < 16 || size > 16)
    {
        printf("SystemInformationBlockType12_r9::serialNumber_r9_Unpack() size failure\n");
        return -1;
    }
    serialNumber_r9_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("SystemInformationBlockType12_r9::serialNumber_r9_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        serialNumber_r9_internal_value |= (uint16_t)bits[idx++] << (uint16_t)(16-i-1);
    serialNumber_r9_present = true;
    return 0;
}

uint16_t SystemInformationBlockType12_r9::serialNumber_r9_Value() const
{
    if(serialNumber_r9_present)
        return serialNumber_r9_internal_value;
    uint16_t tmp = 0;
    return tmp;
}

int SystemInformationBlockType12_r9::serialNumber_r9_SetValue(uint16_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 16)
    {
        printf("SystemInformationBlockType12_r9::serialNumber_r9_SetValue() size failure\n");
        return -1;
    }
    serialNumber_r9_internal_value = value;
    serialNumber_r9_present = true;
    return 0;
}

std::string SystemInformationBlockType12_r9::serialNumber_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "serialNumber_r9 = ";
    out += std::to_string(serialNumber_r9_internal_value);
    out += "\n";
    return out;
}

std::string SystemInformationBlockType12_r9::serialNumber_r9_ToStringNoNewLines() const
{
    std::string out = "serialNumber_r9=";
    out += std::to_string(serialNumber_r9_internal_value);
    out += ",";
    return out;
}

int SystemInformationBlockType12_r9::serialNumber_r9_Clear()
{
    serialNumber_r9_present = false;
    return 0;
}

bool SystemInformationBlockType12_r9::serialNumber_r9_IsPresent() const
{
    return serialNumber_r9_present;
}

int SystemInformationBlockType12_r9::warningMessageSegmentType_r9_Pack(std::vector<uint8_t> &bits)
{
    if(!warningMessageSegmentType_r9_present)
    {
        printf("SystemInformationBlockType12_r9::warningMessageSegmentType_r9_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((warningMessageSegmentType_r9_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int SystemInformationBlockType12_r9::warningMessageSegmentType_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return warningMessageSegmentType_r9_Unpack(bits, idx);
}

int SystemInformationBlockType12_r9::warningMessageSegmentType_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("SystemInformationBlockType12_r9::warningMessageSegmentType_r9_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 1)
    {
        printf("SystemInformationBlockType12_r9::warningMessageSegmentType_r9_Unpack() max failure\n");
        return -1;
    }
    warningMessageSegmentType_r9_internal_value = (warningMessageSegmentType_r9_Enum)packed_val;
    warningMessageSegmentType_r9_present = true;
    return 0;
}

SystemInformationBlockType12_r9::warningMessageSegmentType_r9_Enum SystemInformationBlockType12_r9::warningMessageSegmentType_r9_Value() const
{
    if(warningMessageSegmentType_r9_present)
        return warningMessageSegmentType_r9_internal_value;
    return (SystemInformationBlockType12_r9::warningMessageSegmentType_r9_Enum)0;
}

int SystemInformationBlockType12_r9::warningMessageSegmentType_r9_SetValue(warningMessageSegmentType_r9_Enum value)
{
    warningMessageSegmentType_r9_internal_value = value;
    warningMessageSegmentType_r9_present = true;
    return 0;
}

int SystemInformationBlockType12_r9::warningMessageSegmentType_r9_SetValue(std::string value)
{
    if("notLastSegment" == value)
    {
        warningMessageSegmentType_r9_internal_value = k_warningMessageSegmentType_r9_notLastSegment;
        warningMessageSegmentType_r9_present = true;
        return 0;
    }
    if("lastSegment" == value)
    {
        warningMessageSegmentType_r9_internal_value = k_warningMessageSegmentType_r9_lastSegment;
        warningMessageSegmentType_r9_present = true;
        return 0;
    }
    return 1;
}

std::string SystemInformationBlockType12_r9::warningMessageSegmentType_r9_ValueToString(warningMessageSegmentType_r9_Enum value) const
{
    if(k_warningMessageSegmentType_r9_notLastSegment == value)
        return "notLastSegment";
    if(k_warningMessageSegmentType_r9_lastSegment == value)
        return "lastSegment";
    return "";
}

uint64_t SystemInformationBlockType12_r9::warningMessageSegmentType_r9_NumberOfValues() const
{
    return 2;
}

std::string SystemInformationBlockType12_r9::warningMessageSegmentType_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "warningMessageSegmentType_r9 = " + warningMessageSegmentType_r9_ValueToString(warningMessageSegmentType_r9_internal_value) + "\n";
    return out;
}

std::string SystemInformationBlockType12_r9::warningMessageSegmentType_r9_ToStringNoNewLines() const
{
    std::string out = "warningMessageSegmentType_r9=" + warningMessageSegmentType_r9_ValueToString(warningMessageSegmentType_r9_internal_value) + ",";
    return out;
}

int SystemInformationBlockType12_r9::warningMessageSegmentType_r9_Clear()
{
    warningMessageSegmentType_r9_present = false;
    return 0;
}

bool SystemInformationBlockType12_r9::warningMessageSegmentType_r9_IsPresent() const
{
    return warningMessageSegmentType_r9_present;
}

int SystemInformationBlockType12_r9::warningMessageSegmentNumber_r9_Pack(std::vector<uint8_t> &bits)
{
    if(!warningMessageSegmentNumber_r9_present)
    {
        printf("SystemInformationBlockType12_r9::warningMessageSegmentNumber_r9_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = warningMessageSegmentNumber_r9_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (63 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int SystemInformationBlockType12_r9::warningMessageSegmentNumber_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return warningMessageSegmentNumber_r9_Unpack(bits, idx);
}

int SystemInformationBlockType12_r9::warningMessageSegmentNumber_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (63 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("SystemInformationBlockType12_r9::warningMessageSegmentNumber_r9_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    warningMessageSegmentNumber_r9_internal_value = packed_val + 0;
    warningMessageSegmentNumber_r9_present = true;
    return 0;
}

int64_t SystemInformationBlockType12_r9::warningMessageSegmentNumber_r9_Value() const
{
    if(warningMessageSegmentNumber_r9_present)
        return warningMessageSegmentNumber_r9_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int SystemInformationBlockType12_r9::warningMessageSegmentNumber_r9_SetValue(int64_t value)
{
    if(value < 0 || value > 63)
    {
        printf("SystemInformationBlockType12_r9::warningMessageSegmentNumber_r9_SetValue() range failure\n");
        return -1;
    }
    warningMessageSegmentNumber_r9_internal_value = value;
    warningMessageSegmentNumber_r9_present = true;
    return 0;
}

std::string SystemInformationBlockType12_r9::warningMessageSegmentNumber_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "warningMessageSegmentNumber_r9 = " + std::to_string(warningMessageSegmentNumber_r9_internal_value) + "\n";
    return out;
}

std::string SystemInformationBlockType12_r9::warningMessageSegmentNumber_r9_ToStringNoNewLines() const
{
    std::string out = "warningMessageSegmentNumber_r9=" + std::to_string(warningMessageSegmentNumber_r9_internal_value) + ",";
    return out;
}

int SystemInformationBlockType12_r9::warningMessageSegmentNumber_r9_Clear()
{
    warningMessageSegmentNumber_r9_present = false;
    return 0;
}

bool SystemInformationBlockType12_r9::warningMessageSegmentNumber_r9_IsPresent() const
{
    return warningMessageSegmentNumber_r9_present;
}

int SystemInformationBlockType12_r9::warningMessageSegment_r9_Pack(std::vector<uint8_t> &bits)
{
    if(!warningMessageSegment_r9_present)
    {
        printf("SystemInformationBlockType12_r9::warningMessageSegment_r9_Pack() presence failure\n");
        return -1;
    }
    uint32_t local_size_length = 0;
    uint32_t local_size = warningMessageSegment_r9_internal_value.size();
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
    for(uint32_t i=0; i<warningMessageSegment_r9_internal_value.size(); i++)
        for(uint32_t j=0; j<8; j++)
            bits.push_back((warningMessageSegment_r9_internal_value[i] >> (8-j-1)) & 1);
    return 0;
}

int SystemInformationBlockType12_r9::warningMessageSegment_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return warningMessageSegment_r9_Unpack(bits, idx);
}

int SystemInformationBlockType12_r9::warningMessageSegment_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
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
    warningMessageSegment_r9_internal_value.clear();
    if((idx +size*8) > bits.size())
    {
        printf("SystemInformationBlockType12_r9::warningMessageSegment_r9_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
    {
        uint8_t value = 0;
        for(uint32_t j=0; j<8; j++)
            value |= bits[idx+j] << (8-j-1);
        warningMessageSegment_r9_internal_value.push_back(value);
        idx += 8;
    }
    warningMessageSegment_r9_present = true;
    return 0;
}

std::vector<uint8_t> SystemInformationBlockType12_r9::warningMessageSegment_r9_Value() const
{
    if(warningMessageSegment_r9_present)
        return warningMessageSegment_r9_internal_value;
    std::vector<uint8_t> tmp;
    return tmp;
}

int SystemInformationBlockType12_r9::warningMessageSegment_r9_SetValue(std::vector<uint8_t> value)
{
    warningMessageSegment_r9_internal_value = value;
    warningMessageSegment_r9_present = true;
    return 0;
}

std::string SystemInformationBlockType12_r9::warningMessageSegment_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "warningMessageSegment_r9 = {";
    for(auto byte : warningMessageSegment_r9_internal_value)
        out += std::to_string(byte) + ",";
    out = out.substr(0, out.length()-1) + "}\n";
    return out;
}

std::string SystemInformationBlockType12_r9::warningMessageSegment_r9_ToStringNoNewLines() const
{
    std::string out = "warningMessageSegment_r9={";
    for(auto byte : warningMessageSegment_r9_internal_value)
        out += std::to_string(byte) + ",";
    out = out.substr(0, out.length()-1) + "},";
    return out;
}

int SystemInformationBlockType12_r9::warningMessageSegment_r9_Clear()
{
    warningMessageSegment_r9_present = false;
    return 0;
}

bool SystemInformationBlockType12_r9::warningMessageSegment_r9_IsPresent() const
{
    return warningMessageSegment_r9_present;
}

int SystemInformationBlockType12_r9::dataCodingScheme_r9_Pack(std::vector<uint8_t> &bits)
{
    if(dataCodingScheme_r9_internal_value.size() < 1 || dataCodingScheme_r9_internal_value.size() > 1)
    {
        printf("SystemInformationBlockType12_r9::dataCodingScheme_r9_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<dataCodingScheme_r9_internal_value.size(); i++)
        for(uint32_t j=0; j<8; j++)
            bits.push_back((dataCodingScheme_r9_internal_value[i] >> (8-j-1)) & 1);
    return 0;
}

int SystemInformationBlockType12_r9::dataCodingScheme_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return dataCodingScheme_r9_Unpack(bits, idx);
}

int SystemInformationBlockType12_r9::dataCodingScheme_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 1;
    if(size < 1 || size > 1)
    {
        printf("SystemInformationBlockType12_r9::dataCodingScheme_r9_Unpack() size failure\n");
        return -1;
    }
    dataCodingScheme_r9_internal_value.clear();
    if((idx +size*8) > bits.size())
    {
        printf("SystemInformationBlockType12_r9::dataCodingScheme_r9_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
    {
        uint8_t value = 0;
        for(uint32_t j=0; j<8; j++)
            value |= bits[idx+j] << (8-j-1);
        dataCodingScheme_r9_internal_value.push_back(value);
        idx += 8;
    }
    dataCodingScheme_r9_present = true;
    return 0;
}

std::vector<uint8_t> SystemInformationBlockType12_r9::dataCodingScheme_r9_Value() const
{
    if(dataCodingScheme_r9_present)
        return dataCodingScheme_r9_internal_value;
    std::vector<uint8_t> tmp;
    return tmp;
}

int SystemInformationBlockType12_r9::dataCodingScheme_r9_SetValue(std::vector<uint8_t> value)
{
    if(value.size() < 1 || value.size() > 1)
    {
        printf("SystemInformationBlockType12_r9::dataCodingScheme_r9_SetValue() size failure\n");
        return -1;
    }
    dataCodingScheme_r9_internal_value = value;
    dataCodingScheme_r9_present = true;
    return 0;
}

std::string SystemInformationBlockType12_r9::dataCodingScheme_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "dataCodingScheme_r9 = {";
    for(auto byte : dataCodingScheme_r9_internal_value)
        out += std::to_string(byte) + ",";
    out = out.substr(0, out.length()-1) + "}\n";
    return out;
}

std::string SystemInformationBlockType12_r9::dataCodingScheme_r9_ToStringNoNewLines() const
{
    std::string out = "dataCodingScheme_r9={";
    for(auto byte : dataCodingScheme_r9_internal_value)
        out += std::to_string(byte) + ",";
    out = out.substr(0, out.length()-1) + "},";
    return out;
}

int SystemInformationBlockType12_r9::dataCodingScheme_r9_Clear()
{
    dataCodingScheme_r9_present = false;
    return 0;
}

bool SystemInformationBlockType12_r9::dataCodingScheme_r9_IsPresent() const
{
    return dataCodingScheme_r9_present;
}

int SystemInformationBlockType12_r9::lateNonCriticalExtension_Pack(std::vector<uint8_t> &bits)
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

int SystemInformationBlockType12_r9::lateNonCriticalExtension_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return lateNonCriticalExtension_Unpack(bits, idx);
}

int SystemInformationBlockType12_r9::lateNonCriticalExtension_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
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
        printf("SystemInformationBlockType12_r9::lateNonCriticalExtension_Unpack() index out of bounds\n");
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

std::vector<uint8_t> SystemInformationBlockType12_r9::lateNonCriticalExtension_Value() const
{
    if(lateNonCriticalExtension_present)
        return lateNonCriticalExtension_internal_value;
    std::vector<uint8_t> tmp;
    return tmp;
}

int SystemInformationBlockType12_r9::lateNonCriticalExtension_SetValue(std::vector<uint8_t> value)
{
    lateNonCriticalExtension_internal_value = value;
    lateNonCriticalExtension_present = true;
    return 0;
}

std::string SystemInformationBlockType12_r9::lateNonCriticalExtension_ToString(uint32_t indent) const
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

std::string SystemInformationBlockType12_r9::lateNonCriticalExtension_ToStringNoNewLines() const
{
    std::string out = "lateNonCriticalExtension={";
    for(auto byte : lateNonCriticalExtension_internal_value)
        out += std::to_string(byte) + ",";
    out = out.substr(0, out.length()-1) + "},";
    return out;
}

int SystemInformationBlockType12_r9::lateNonCriticalExtension_Clear()
{
    lateNonCriticalExtension_present = false;
    return 0;
}

bool SystemInformationBlockType12_r9::lateNonCriticalExtension_IsPresent() const
{
    return lateNonCriticalExtension_present;
}

