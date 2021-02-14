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

#include "TMGI_r9.h"

#include <cmath>

int TMGI_r9::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != plmn_Id_r9_Pack(bits))
        {
            printf("TMGI_r9:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != serviceId_r9_Pack(bits))
        {
            printf("TMGI_r9:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int TMGI_r9::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int TMGI_r9::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != plmn_Id_r9_Unpack(bits, idx))
        {
            printf("TMGI_r9:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != serviceId_r9_Unpack(bits, idx))
        {
            printf("TMGI_r9:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string TMGI_r9::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "TMGI_r9:\n";
    out += plmn_Id_r9_ToString(indent+1);
    out += serviceId_r9_ToString(indent+1);
    return out;
}

std::string TMGI_r9::ToStringNoNewLines() const
{
    std::string out = "TMGI_r9:";
    out += plmn_Id_r9_ToStringNoNewLines();
    out += serviceId_r9_ToStringNoNewLines();
    return out;
}

int TMGI_r9::plmn_Id_r9_Pack(std::vector<uint8_t> &bits)
{
    if(!plmn_Id_r9_present)
    {
        printf("TMGI_r9::plmn_Id_r9_Pack() presence failure\n");
        return -1;
    }
    // Extension indicator

    // Choice
    for(uint32_t i=0; i<1; i++)
        bits.push_back((plmn_Id_r9_internal_choice >> (1-i-1)) & 1);

    // Fields
    if(plmn_Id_r9_internal_choice == k_plmn_Id_r9_plmn_Index_r9)
    {
        if(0 != plmn_Id_r9_plmn_Index_r9_Pack(bits))
        {
            printf("TMGI_r9::plmn_Id_r9_plmn_Index_r9 pack failure\n");
            return -1;
        }
    }
    if(plmn_Id_r9_internal_choice == k_plmn_Id_r9_explicitValue_r9)
    {
        if(0 != plmn_Id_r9_explicitValue_r9.Pack(bits))
        {
            printf("TMGI_r9::plmn_Id_r9_explicitValue_r9 pack failure\n");
            return -1;
        }
    }
    return 0;
}

int TMGI_r9::plmn_Id_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return plmn_Id_r9_Unpack(bits, idx);
}

int TMGI_r9::plmn_Id_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 1) > bits.size())
    {
        printf("TMGI_r9::plmn_Id_r9_Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<1; i++)
        packed_val |= bits[idx++] << (1-i-1);

    if((TMGI_r9::plmn_Id_r9_Enum)packed_val > k_plmn_Id_r9_explicitValue_r9)
    {
        printf("TMGI_r9::plmn_Id_r9_Unpack() choice range failure\n");
        return -1;
    }
    plmn_Id_r9_internal_choice = (TMGI_r9::plmn_Id_r9_Enum)packed_val;
    plmn_Id_r9_present = true;

    // Fields
    if(plmn_Id_r9_internal_choice == k_plmn_Id_r9_plmn_Index_r9)
    {
        if(0 != plmn_Id_r9_plmn_Index_r9_Unpack(bits, idx))
        {
            printf("TMGI_r9::plmn_Id_r9_plmn_Index_r9 unpack failure\n");
            return -1;
        }
    }
    if(plmn_Id_r9_internal_choice == k_plmn_Id_r9_explicitValue_r9)
    {
        if(0 != plmn_Id_r9_explicitValue_r9.Unpack(bits, idx))
        {
            printf("TMGI_r9::plmn_Id_r9_explicitValue_r9 unpack failure\n");
            return -1;
        }
    }
    return 0;
}

TMGI_r9::plmn_Id_r9_Enum TMGI_r9::plmn_Id_r9_Choice() const
{
    if(plmn_Id_r9_present)
        return plmn_Id_r9_internal_choice;
    return (TMGI_r9::plmn_Id_r9_Enum)0;
}

int TMGI_r9::plmn_Id_r9_SetChoice(TMGI_r9::plmn_Id_r9_Enum choice)
{
    plmn_Id_r9_internal_choice = choice;
    plmn_Id_r9_present = true;
    return 0;
}

std::string TMGI_r9::plmn_Id_r9_ChoiceToString(plmn_Id_r9_Enum value) const
{
    if(k_plmn_Id_r9_plmn_Index_r9 == value)
        return "plmn_Id_r9_plmn_Index_r9";
    if(k_plmn_Id_r9_explicitValue_r9 == value)
        return "plmn_Id_r9_explicitValue_r9";
    return "";
}

uint64_t TMGI_r9::plmn_Id_r9_NumberOfChoices() const
{
    return 2;
}

std::string TMGI_r9::plmn_Id_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "plmn_Id_r9 = " + plmn_Id_r9_ChoiceToString(plmn_Id_r9_internal_choice) + ":\n";
    if(plmn_Id_r9_internal_choice == k_plmn_Id_r9_plmn_Index_r9)
        out += plmn_Id_r9_plmn_Index_r9_ToString(indent+1);
    if(plmn_Id_r9_internal_choice == k_plmn_Id_r9_explicitValue_r9)
        out += plmn_Id_r9_explicitValue_r9.ToString(indent+1);
    return out;
}

std::string TMGI_r9::plmn_Id_r9_ToStringNoNewLines() const
{
    std::string out = "plmn_Id_r9=" + plmn_Id_r9_ChoiceToString(plmn_Id_r9_internal_choice) + ",";
    if(plmn_Id_r9_internal_choice == k_plmn_Id_r9_plmn_Index_r9)
        out += plmn_Id_r9_plmn_Index_r9_ToStringNoNewLines();
    if(plmn_Id_r9_internal_choice == k_plmn_Id_r9_explicitValue_r9)
        out += plmn_Id_r9_explicitValue_r9.ToStringNoNewLines();
    return out;
}

int TMGI_r9::plmn_Id_r9_Clear()
{
    plmn_Id_r9_present = false;
    return 0;
}

bool TMGI_r9::plmn_Id_r9_IsPresent() const
{
    return plmn_Id_r9_present;
}

int TMGI_r9::plmn_Id_r9_plmn_Index_r9_Pack(std::vector<uint8_t> &bits)
{
    if(!plmn_Id_r9_plmn_Index_r9_present)
    {
        printf("TMGI_r9::plmn_Id_r9_plmn_Index_r9_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = plmn_Id_r9_plmn_Index_r9_internal_value - (1);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (6 - 1))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int TMGI_r9::plmn_Id_r9_plmn_Index_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return plmn_Id_r9_plmn_Index_r9_Unpack(bits, idx);
}

int TMGI_r9::plmn_Id_r9_plmn_Index_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (6 - 1))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("TMGI_r9::plmn_Id_r9_plmn_Index_r9_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    plmn_Id_r9_plmn_Index_r9_internal_value = packed_val + 1;
    plmn_Id_r9_plmn_Index_r9_present = true;
    return 0;
}

int64_t TMGI_r9::plmn_Id_r9_plmn_Index_r9_Value() const
{
    if(plmn_Id_r9_plmn_Index_r9_present)
        return plmn_Id_r9_plmn_Index_r9_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int TMGI_r9::plmn_Id_r9_plmn_Index_r9_SetValue(int64_t value)
{
    if(value < 1 || value > 6)
    {
        printf("TMGI_r9::plmn_Id_r9_plmn_Index_r9_SetValue() range failure\n");
        return -1;
    }
    plmn_Id_r9_plmn_Index_r9_internal_value = value;
    plmn_Id_r9_plmn_Index_r9_present = true;
    return 0;
}

std::string TMGI_r9::plmn_Id_r9_plmn_Index_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "plmn_Index_r9 = " + std::to_string(plmn_Id_r9_plmn_Index_r9_internal_value) + "\n";
    return out;
}

std::string TMGI_r9::plmn_Id_r9_plmn_Index_r9_ToStringNoNewLines() const
{
    std::string out = "plmn_Index_r9=" + std::to_string(plmn_Id_r9_plmn_Index_r9_internal_value) + ",";
    return out;
}

int TMGI_r9::plmn_Id_r9_plmn_Index_r9_Clear()
{
    plmn_Id_r9_plmn_Index_r9_present = false;
    return 0;
}

bool TMGI_r9::plmn_Id_r9_plmn_Index_r9_IsPresent() const
{
    return plmn_Id_r9_plmn_Index_r9_present;
}

PLMN_Identity* TMGI_r9::plmn_Id_r9_explicitValue_r9_Set()
{
    plmn_Id_r9_explicitValue_r9_present = true;
    return &plmn_Id_r9_explicitValue_r9;
}

int TMGI_r9::plmn_Id_r9_explicitValue_r9_Set(PLMN_Identity &value)
{
    plmn_Id_r9_explicitValue_r9_present = true;
    plmn_Id_r9_explicitValue_r9 = value;
    return 0;
}

const PLMN_Identity& TMGI_r9::plmn_Id_r9_explicitValue_r9_Get() const
{
    return plmn_Id_r9_explicitValue_r9;
}

std::string TMGI_r9::plmn_Id_r9_explicitValue_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "explicitValue_r9:\n";
    out += plmn_Id_r9_explicitValue_r9.ToString(indent+1);
    return out;
}

std::string TMGI_r9::plmn_Id_r9_explicitValue_r9_ToStringNoNewLines() const
{
    std::string out = "explicitValue_r9:";
    out += plmn_Id_r9_explicitValue_r9.ToStringNoNewLines();
    return out;
}

int TMGI_r9::plmn_Id_r9_explicitValue_r9_Clear()
{
    plmn_Id_r9_explicitValue_r9_present = false;
    return 0;
}

bool TMGI_r9::plmn_Id_r9_explicitValue_r9_IsPresent() const
{
    return plmn_Id_r9_explicitValue_r9_present;
}

int TMGI_r9::serviceId_r9_Pack(std::vector<uint8_t> &bits)
{
    if(!serviceId_r9_present)
    {
        printf("TMGI_r9::serviceId_r9_Pack() presence failure\n");
        return -1;
    }
    if(serviceId_r9_internal_value.size() < 3 || serviceId_r9_internal_value.size() > 3)
    {
        printf("TMGI_r9::serviceId_r9_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<serviceId_r9_internal_value.size(); i++)
        for(uint32_t j=0; j<8; j++)
            bits.push_back((serviceId_r9_internal_value[i] >> (8-j-1)) & 1);
    return 0;
}

int TMGI_r9::serviceId_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return serviceId_r9_Unpack(bits, idx);
}

int TMGI_r9::serviceId_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 3;
    if(size < 3 || size > 3)
    {
        printf("TMGI_r9::serviceId_r9_Unpack() size failure\n");
        return -1;
    }
    serviceId_r9_internal_value.clear();
    if((idx +size*8) > bits.size())
    {
        printf("TMGI_r9::serviceId_r9_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
    {
        uint8_t value = 0;
        for(uint32_t j=0; j<8; j++)
            value |= bits[idx+j] << (8-j-1);
        serviceId_r9_internal_value.push_back(value);
        idx += 8;
    }
    serviceId_r9_present = true;
    return 0;
}

std::vector<uint8_t> TMGI_r9::serviceId_r9_Value() const
{
    if(serviceId_r9_present)
        return serviceId_r9_internal_value;
    std::vector<uint8_t> tmp;
    return tmp;
}

int TMGI_r9::serviceId_r9_SetValue(std::vector<uint8_t> value)
{
    if(value.size() < 3 || value.size() > 3)
    {
        printf("TMGI_r9::serviceId_r9_SetValue() size failure\n");
        return -1;
    }
    serviceId_r9_internal_value = value;
    serviceId_r9_present = true;
    return 0;
}

std::string TMGI_r9::serviceId_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "serviceId_r9 = {";
    for(auto byte : serviceId_r9_internal_value)
        out += std::to_string(byte) + ",";
    out = out.substr(0, out.length()-1) + "}\n";
    return out;
}

std::string TMGI_r9::serviceId_r9_ToStringNoNewLines() const
{
    std::string out = "serviceId_r9={";
    for(auto byte : serviceId_r9_internal_value)
        out += std::to_string(byte) + ",";
    out = out.substr(0, out.length()-1) + "},";
    return out;
}

int TMGI_r9::serviceId_r9_Clear()
{
    serviceId_r9_present = false;
    return 0;
}

bool TMGI_r9::serviceId_r9_IsPresent() const
{
    return serviceId_r9_present;
}

