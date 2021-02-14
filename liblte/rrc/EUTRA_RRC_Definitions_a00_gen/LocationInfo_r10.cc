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

#include "LocationInfo_r10.h"

#include <cmath>

int LocationInfo_r10::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator
    bits.push_back(0);

    // Optional indicators
    bits.push_back(horizontalVelocity_r10_IsPresent());

    // Fields
    {
        if(0 != locationCoordinates_r10_Pack(bits))
        {
            printf("LocationInfo_r10:: field pack failure\n");
            return -1;
        }
    }
    if(horizontalVelocity_r10_IsPresent())
    {
        if(0 != horizontalVelocity_r10_Pack(bits))
        {
            printf("LocationInfo_r10:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int LocationInfo_r10::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int LocationInfo_r10::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("LocationInfo_r10::Unpack() index out of bounds for extension\n");
        return -1;
    }
    idx++;

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("LocationInfo_r10::Unpack() index out of bounds for optional indiator horizontalVelocity_r10\n");
        return -1;
    }
    horizontalVelocity_r10_present = bits[idx++];

    // Fields
    {
        if(0 != locationCoordinates_r10_Unpack(bits, idx))
        {
            printf("LocationInfo_r10:: field unpack failure\n");
            return -1;
        }
    }
    if(horizontalVelocity_r10_present)
    {
        if(0 != horizontalVelocity_r10_Unpack(bits, idx))
        {
            printf("LocationInfo_r10:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string LocationInfo_r10::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "LocationInfo_r10:\n";
    out += locationCoordinates_r10_ToString(indent+1);
    if(horizontalVelocity_r10_IsPresent())
        out += horizontalVelocity_r10_ToString(indent+1);
    return out;
}

std::string LocationInfo_r10::ToStringNoNewLines() const
{
    std::string out = "LocationInfo_r10:";
    out += locationCoordinates_r10_ToStringNoNewLines();
    if(horizontalVelocity_r10_IsPresent())
        out += horizontalVelocity_r10_ToStringNoNewLines();
    return out;
}

int LocationInfo_r10::locationCoordinates_r10_Pack(std::vector<uint8_t> &bits)
{
    if(!locationCoordinates_r10_present)
    {
        printf("LocationInfo_r10::locationCoordinates_r10_Pack() presence failure\n");
        return -1;
    }
    // Extension indicator
    bits.push_back(0);

    // Choice
    for(uint32_t i=0; i<1; i++)
        bits.push_back((locationCoordinates_r10_internal_choice >> (1-i-1)) & 1);

    // Fields
    if(locationCoordinates_r10_internal_choice == k_locationCoordinates_r10_ellipsoid_Point_r10)
    {
        if(0 != locationCoordinates_r10_ellipsoid_Point_r10_Pack(bits))
        {
            printf("LocationInfo_r10::locationCoordinates_r10_ellipsoid_Point_r10 pack failure\n");
            return -1;
        }
    }
    if(locationCoordinates_r10_internal_choice == k_locationCoordinates_r10_ellipsoidPointWithAltitude_r10)
    {
        if(0 != locationCoordinates_r10_ellipsoidPointWithAltitude_r10_Pack(bits))
        {
            printf("LocationInfo_r10::locationCoordinates_r10_ellipsoidPointWithAltitude_r10 pack failure\n");
            return -1;
        }
    }
    return 0;
}

int LocationInfo_r10::locationCoordinates_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return locationCoordinates_r10_Unpack(bits, idx);
}

int LocationInfo_r10::locationCoordinates_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("LocationInfo_r10::locationCoordinates_r10_Unpack() index out of bounds for extension\n");
        return -1;
    }
    idx++;

    // Choice
    uint32_t packed_val = 0;
    if((idx + 1) > bits.size())
    {
        printf("LocationInfo_r10::locationCoordinates_r10_Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<1; i++)
        packed_val |= bits[idx++] << (1-i-1);

    if((LocationInfo_r10::locationCoordinates_r10_Enum)packed_val > k_locationCoordinates_r10_ellipsoidPointWithAltitude_r10)
    {
        printf("LocationInfo_r10::locationCoordinates_r10_Unpack() choice range failure\n");
        return -1;
    }
    locationCoordinates_r10_internal_choice = (LocationInfo_r10::locationCoordinates_r10_Enum)packed_val;
    locationCoordinates_r10_present = true;

    // Fields
    if(locationCoordinates_r10_internal_choice == k_locationCoordinates_r10_ellipsoid_Point_r10)
    {
        if(0 != locationCoordinates_r10_ellipsoid_Point_r10_Unpack(bits, idx))
        {
            printf("LocationInfo_r10::locationCoordinates_r10_ellipsoid_Point_r10 unpack failure\n");
            return -1;
        }
    }
    if(locationCoordinates_r10_internal_choice == k_locationCoordinates_r10_ellipsoidPointWithAltitude_r10)
    {
        if(0 != locationCoordinates_r10_ellipsoidPointWithAltitude_r10_Unpack(bits, idx))
        {
            printf("LocationInfo_r10::locationCoordinates_r10_ellipsoidPointWithAltitude_r10 unpack failure\n");
            return -1;
        }
    }
    return 0;
}

LocationInfo_r10::locationCoordinates_r10_Enum LocationInfo_r10::locationCoordinates_r10_Choice() const
{
    if(locationCoordinates_r10_present)
        return locationCoordinates_r10_internal_choice;
    return (LocationInfo_r10::locationCoordinates_r10_Enum)0;
}

int LocationInfo_r10::locationCoordinates_r10_SetChoice(LocationInfo_r10::locationCoordinates_r10_Enum choice)
{
    locationCoordinates_r10_internal_choice = choice;
    locationCoordinates_r10_present = true;
    return 0;
}

std::string LocationInfo_r10::locationCoordinates_r10_ChoiceToString(locationCoordinates_r10_Enum value) const
{
    if(k_locationCoordinates_r10_ellipsoid_Point_r10 == value)
        return "locationCoordinates_r10_ellipsoid_Point_r10";
    if(k_locationCoordinates_r10_ellipsoidPointWithAltitude_r10 == value)
        return "locationCoordinates_r10_ellipsoidPointWithAltitude_r10";
    return "";
}

uint64_t LocationInfo_r10::locationCoordinates_r10_NumberOfChoices() const
{
    return 2;
}

std::string LocationInfo_r10::locationCoordinates_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "locationCoordinates_r10 = " + locationCoordinates_r10_ChoiceToString(locationCoordinates_r10_internal_choice) + ":\n";
    if(locationCoordinates_r10_internal_choice == k_locationCoordinates_r10_ellipsoid_Point_r10)
        out += locationCoordinates_r10_ellipsoid_Point_r10_ToString(indent+1);
    if(locationCoordinates_r10_internal_choice == k_locationCoordinates_r10_ellipsoidPointWithAltitude_r10)
        out += locationCoordinates_r10_ellipsoidPointWithAltitude_r10_ToString(indent+1);
    return out;
}

std::string LocationInfo_r10::locationCoordinates_r10_ToStringNoNewLines() const
{
    std::string out = "locationCoordinates_r10=" + locationCoordinates_r10_ChoiceToString(locationCoordinates_r10_internal_choice) + ",";
    if(locationCoordinates_r10_internal_choice == k_locationCoordinates_r10_ellipsoid_Point_r10)
        out += locationCoordinates_r10_ellipsoid_Point_r10_ToStringNoNewLines();
    if(locationCoordinates_r10_internal_choice == k_locationCoordinates_r10_ellipsoidPointWithAltitude_r10)
        out += locationCoordinates_r10_ellipsoidPointWithAltitude_r10_ToStringNoNewLines();
    return out;
}

int LocationInfo_r10::locationCoordinates_r10_Clear()
{
    locationCoordinates_r10_present = false;
    return 0;
}

bool LocationInfo_r10::locationCoordinates_r10_IsPresent() const
{
    return locationCoordinates_r10_present;
}

int LocationInfo_r10::locationCoordinates_r10_ellipsoid_Point_r10_Pack(std::vector<uint8_t> &bits)
{
    if(!locationCoordinates_r10_ellipsoid_Point_r10_present)
    {
        printf("LocationInfo_r10::locationCoordinates_r10_ellipsoid_Point_r10_Pack() presence failure\n");
        return -1;
    }
    uint32_t local_size_length = 0;
    uint32_t local_size = locationCoordinates_r10_ellipsoid_Point_r10_internal_value.size();
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
    for(uint32_t i=0; i<locationCoordinates_r10_ellipsoid_Point_r10_internal_value.size(); i++)
        for(uint32_t j=0; j<8; j++)
            bits.push_back((locationCoordinates_r10_ellipsoid_Point_r10_internal_value[i] >> (8-j-1)) & 1);
    return 0;
}

int LocationInfo_r10::locationCoordinates_r10_ellipsoid_Point_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return locationCoordinates_r10_ellipsoid_Point_r10_Unpack(bits, idx);
}

int LocationInfo_r10::locationCoordinates_r10_ellipsoid_Point_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
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
    locationCoordinates_r10_ellipsoid_Point_r10_internal_value.clear();
    if((idx +size*8) > bits.size())
    {
        printf("LocationInfo_r10::locationCoordinates_r10_ellipsoid_Point_r10_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
    {
        uint8_t value = 0;
        for(uint32_t j=0; j<8; j++)
            value |= bits[idx+j] << (8-j-1);
        locationCoordinates_r10_ellipsoid_Point_r10_internal_value.push_back(value);
        idx += 8;
    }
    locationCoordinates_r10_ellipsoid_Point_r10_present = true;
    return 0;
}

std::vector<uint8_t> LocationInfo_r10::locationCoordinates_r10_ellipsoid_Point_r10_Value() const
{
    if(locationCoordinates_r10_ellipsoid_Point_r10_present)
        return locationCoordinates_r10_ellipsoid_Point_r10_internal_value;
    std::vector<uint8_t> tmp;
    return tmp;
}

int LocationInfo_r10::locationCoordinates_r10_ellipsoid_Point_r10_SetValue(std::vector<uint8_t> value)
{
    locationCoordinates_r10_ellipsoid_Point_r10_internal_value = value;
    locationCoordinates_r10_ellipsoid_Point_r10_present = true;
    return 0;
}

std::string LocationInfo_r10::locationCoordinates_r10_ellipsoid_Point_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ellipsoid_Point_r10 = {";
    for(auto byte : locationCoordinates_r10_ellipsoid_Point_r10_internal_value)
        out += std::to_string(byte) + ",";
    out = out.substr(0, out.length()-1) + "}\n";
    return out;
}

std::string LocationInfo_r10::locationCoordinates_r10_ellipsoid_Point_r10_ToStringNoNewLines() const
{
    std::string out = "ellipsoid_Point_r10={";
    for(auto byte : locationCoordinates_r10_ellipsoid_Point_r10_internal_value)
        out += std::to_string(byte) + ",";
    out = out.substr(0, out.length()-1) + "},";
    return out;
}

int LocationInfo_r10::locationCoordinates_r10_ellipsoid_Point_r10_Clear()
{
    locationCoordinates_r10_ellipsoid_Point_r10_present = false;
    return 0;
}

bool LocationInfo_r10::locationCoordinates_r10_ellipsoid_Point_r10_IsPresent() const
{
    return locationCoordinates_r10_ellipsoid_Point_r10_present;
}

int LocationInfo_r10::locationCoordinates_r10_ellipsoidPointWithAltitude_r10_Pack(std::vector<uint8_t> &bits)
{
    if(!locationCoordinates_r10_ellipsoidPointWithAltitude_r10_present)
    {
        printf("LocationInfo_r10::locationCoordinates_r10_ellipsoidPointWithAltitude_r10_Pack() presence failure\n");
        return -1;
    }
    uint32_t local_size_length = 0;
    uint32_t local_size = locationCoordinates_r10_ellipsoidPointWithAltitude_r10_internal_value.size();
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
    for(uint32_t i=0; i<locationCoordinates_r10_ellipsoidPointWithAltitude_r10_internal_value.size(); i++)
        for(uint32_t j=0; j<8; j++)
            bits.push_back((locationCoordinates_r10_ellipsoidPointWithAltitude_r10_internal_value[i] >> (8-j-1)) & 1);
    return 0;
}

int LocationInfo_r10::locationCoordinates_r10_ellipsoidPointWithAltitude_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return locationCoordinates_r10_ellipsoidPointWithAltitude_r10_Unpack(bits, idx);
}

int LocationInfo_r10::locationCoordinates_r10_ellipsoidPointWithAltitude_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
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
    locationCoordinates_r10_ellipsoidPointWithAltitude_r10_internal_value.clear();
    if((idx +size*8) > bits.size())
    {
        printf("LocationInfo_r10::locationCoordinates_r10_ellipsoidPointWithAltitude_r10_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
    {
        uint8_t value = 0;
        for(uint32_t j=0; j<8; j++)
            value |= bits[idx+j] << (8-j-1);
        locationCoordinates_r10_ellipsoidPointWithAltitude_r10_internal_value.push_back(value);
        idx += 8;
    }
    locationCoordinates_r10_ellipsoidPointWithAltitude_r10_present = true;
    return 0;
}

std::vector<uint8_t> LocationInfo_r10::locationCoordinates_r10_ellipsoidPointWithAltitude_r10_Value() const
{
    if(locationCoordinates_r10_ellipsoidPointWithAltitude_r10_present)
        return locationCoordinates_r10_ellipsoidPointWithAltitude_r10_internal_value;
    std::vector<uint8_t> tmp;
    return tmp;
}

int LocationInfo_r10::locationCoordinates_r10_ellipsoidPointWithAltitude_r10_SetValue(std::vector<uint8_t> value)
{
    locationCoordinates_r10_ellipsoidPointWithAltitude_r10_internal_value = value;
    locationCoordinates_r10_ellipsoidPointWithAltitude_r10_present = true;
    return 0;
}

std::string LocationInfo_r10::locationCoordinates_r10_ellipsoidPointWithAltitude_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ellipsoidPointWithAltitude_r10 = {";
    for(auto byte : locationCoordinates_r10_ellipsoidPointWithAltitude_r10_internal_value)
        out += std::to_string(byte) + ",";
    out = out.substr(0, out.length()-1) + "}\n";
    return out;
}

std::string LocationInfo_r10::locationCoordinates_r10_ellipsoidPointWithAltitude_r10_ToStringNoNewLines() const
{
    std::string out = "ellipsoidPointWithAltitude_r10={";
    for(auto byte : locationCoordinates_r10_ellipsoidPointWithAltitude_r10_internal_value)
        out += std::to_string(byte) + ",";
    out = out.substr(0, out.length()-1) + "},";
    return out;
}

int LocationInfo_r10::locationCoordinates_r10_ellipsoidPointWithAltitude_r10_Clear()
{
    locationCoordinates_r10_ellipsoidPointWithAltitude_r10_present = false;
    return 0;
}

bool LocationInfo_r10::locationCoordinates_r10_ellipsoidPointWithAltitude_r10_IsPresent() const
{
    return locationCoordinates_r10_ellipsoidPointWithAltitude_r10_present;
}

int LocationInfo_r10::horizontalVelocity_r10_Pack(std::vector<uint8_t> &bits)
{
    uint32_t local_size_length = 0;
    uint32_t local_size = horizontalVelocity_r10_internal_value.size();
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
    for(uint32_t i=0; i<horizontalVelocity_r10_internal_value.size(); i++)
        for(uint32_t j=0; j<8; j++)
            bits.push_back((horizontalVelocity_r10_internal_value[i] >> (8-j-1)) & 1);
    return 0;
}

int LocationInfo_r10::horizontalVelocity_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return horizontalVelocity_r10_Unpack(bits, idx);
}

int LocationInfo_r10::horizontalVelocity_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
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
    horizontalVelocity_r10_internal_value.clear();
    if((idx +size*8) > bits.size())
    {
        printf("LocationInfo_r10::horizontalVelocity_r10_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
    {
        uint8_t value = 0;
        for(uint32_t j=0; j<8; j++)
            value |= bits[idx+j] << (8-j-1);
        horizontalVelocity_r10_internal_value.push_back(value);
        idx += 8;
    }
    horizontalVelocity_r10_present = true;
    return 0;
}

std::vector<uint8_t> LocationInfo_r10::horizontalVelocity_r10_Value() const
{
    if(horizontalVelocity_r10_present)
        return horizontalVelocity_r10_internal_value;
    std::vector<uint8_t> tmp;
    return tmp;
}

int LocationInfo_r10::horizontalVelocity_r10_SetValue(std::vector<uint8_t> value)
{
    horizontalVelocity_r10_internal_value = value;
    horizontalVelocity_r10_present = true;
    return 0;
}

std::string LocationInfo_r10::horizontalVelocity_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "horizontalVelocity_r10 = {";
    for(auto byte : horizontalVelocity_r10_internal_value)
        out += std::to_string(byte) + ",";
    out = out.substr(0, out.length()-1) + "}\n";
    return out;
}

std::string LocationInfo_r10::horizontalVelocity_r10_ToStringNoNewLines() const
{
    std::string out = "horizontalVelocity_r10={";
    for(auto byte : horizontalVelocity_r10_internal_value)
        out += std::to_string(byte) + ",";
    out = out.substr(0, out.length()-1) + "},";
    return out;
}

int LocationInfo_r10::horizontalVelocity_r10_Clear()
{
    horizontalVelocity_r10_present = false;
    return 0;
}

bool LocationInfo_r10::horizontalVelocity_r10_IsPresent() const
{
    return horizontalVelocity_r10_present;
}

