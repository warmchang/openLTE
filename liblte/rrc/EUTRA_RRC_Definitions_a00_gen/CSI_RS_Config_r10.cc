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

#include "CSI_RS_Config_r10.h"

#include <cmath>

int CSI_RS_Config_r10::Pack(std::vector<uint8_t> &bits)
{
    if(!present)
    {
        printf("CSI_RS_Config_r10::Pack() presence failure\n");
        return -1;
    }
    // Extension indicator

    // Choice
    for(uint32_t i=0; i<1; i++)
        bits.push_back((internal_choice >> (1-i-1)) & 1);

    // Fields
    if(internal_choice == k_release)
    {
        if(0 != release_Pack(bits))
        {
            printf("CSI_RS_Config_r10::release pack failure\n");
            return -1;
        }
    }
    if(internal_choice == k_setup)
    {
        if(0 != setup_value.Pack(bits))
        {
            printf("CSI_RS_Config_r10::setup pack failure\n");
            return -1;
        }
    }
    return 0;
}

int CSI_RS_Config_r10::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int CSI_RS_Config_r10::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 1) > bits.size())
    {
        printf("CSI_RS_Config_r10::Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<1; i++)
        packed_val |= bits[idx++] << (1-i-1);

    if((CSI_RS_Config_r10::Enum)packed_val > k_setup)
    {
        printf("CSI_RS_Config_r10::Unpack() choice range failure\n");
        return -1;
    }
    internal_choice = (CSI_RS_Config_r10::Enum)packed_val;
    present = true;

    // Fields
    if(internal_choice == k_release)
    {
        if(0 != release_Unpack(bits, idx))
        {
            printf("CSI_RS_Config_r10::release unpack failure\n");
            return -1;
        }
    }
    if(internal_choice == k_setup)
    {
        if(0 != setup_value.Unpack(bits, idx))
        {
            printf("CSI_RS_Config_r10::setup unpack failure\n");
            return -1;
        }
    }
    return 0;
}

CSI_RS_Config_r10::Enum CSI_RS_Config_r10::Choice() const
{
    if(present)
        return internal_choice;
    return (CSI_RS_Config_r10::Enum)0;
}

int CSI_RS_Config_r10::SetChoice(CSI_RS_Config_r10::Enum choice)
{
    internal_choice = choice;
    present = true;
    return 0;
}

std::string CSI_RS_Config_r10::ChoiceToString(Enum value) const
{
    if(k_release == value)
        return "release";
    if(k_setup == value)
        return "setup";
    return "";
}

uint64_t CSI_RS_Config_r10::NumberOfChoices() const
{
    return 2;
}

std::string CSI_RS_Config_r10::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "CSI_RS_Config_r10 = " + ChoiceToString(internal_choice) + ":\n";
    if(internal_choice == k_setup)
        out += setup_value.ToString(indent+1);
    return out;
}

std::string CSI_RS_Config_r10::ToStringNoNewLines() const
{
    std::string out = "CSI_RS_Config_r10=" + ChoiceToString(internal_choice) + ",";
    if(internal_choice == k_setup)
        out += setup_value.ToStringNoNewLines();
    return out;
}

int CSI_RS_Config_r10::Clear()
{
    present = false;
    return 0;
}

bool CSI_RS_Config_r10::IsPresent() const
{
    return present;
}

int CSI_RS_Config_r10::setup::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != csi_RS_Ports_r10_Pack(bits))
        {
            printf("CSI_RS_Config_r10::setup:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != locationIndex_r10_Pack(bits))
        {
            printf("CSI_RS_Config_r10::setup:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != csi_RS_SubframeConfig_r10_Pack(bits))
        {
            printf("CSI_RS_Config_r10::setup:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != rho_C_r10_Pack(bits))
        {
            printf("CSI_RS_Config_r10::setup:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != csi_RS_WithZeroTransmissionPower_r10_Pack(bits))
        {
            printf("CSI_RS_Config_r10::setup:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int CSI_RS_Config_r10::setup::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int CSI_RS_Config_r10::setup::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != csi_RS_Ports_r10_Unpack(bits, idx))
        {
            printf("CSI_RS_Config_r10::setup:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != locationIndex_r10_Unpack(bits, idx))
        {
            printf("CSI_RS_Config_r10::setup:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != csi_RS_SubframeConfig_r10_Unpack(bits, idx))
        {
            printf("CSI_RS_Config_r10::setup:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != rho_C_r10_Unpack(bits, idx))
        {
            printf("CSI_RS_Config_r10::setup:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != csi_RS_WithZeroTransmissionPower_r10_Unpack(bits, idx))
        {
            printf("CSI_RS_Config_r10::setup:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string CSI_RS_Config_r10::setup::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "setup:\n";
    out += csi_RS_Ports_r10_ToString(indent+1);
    out += locationIndex_r10_ToString(indent+1);
    out += csi_RS_SubframeConfig_r10_ToString(indent+1);
    out += rho_C_r10_ToString(indent+1);
    out += csi_RS_WithZeroTransmissionPower_r10_ToString(indent+1);
    return out;
}

std::string CSI_RS_Config_r10::setup::ToStringNoNewLines() const
{
    std::string out = "setup:";
    out += csi_RS_Ports_r10_ToStringNoNewLines();
    out += locationIndex_r10_ToStringNoNewLines();
    out += csi_RS_SubframeConfig_r10_ToStringNoNewLines();
    out += rho_C_r10_ToStringNoNewLines();
    out += csi_RS_WithZeroTransmissionPower_r10_ToStringNoNewLines();
    return out;
}

int CSI_RS_Config_r10::setup::csi_RS_Ports_r10_Pack(std::vector<uint8_t> &bits)
{
    if(!csi_RS_Ports_r10_present)
    {
        printf("CSI_RS_Config_r10::setup::csi_RS_Ports_r10_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 2;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((csi_RS_Ports_r10_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int CSI_RS_Config_r10::setup::csi_RS_Ports_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return csi_RS_Ports_r10_Unpack(bits, idx);
}

int CSI_RS_Config_r10::setup::csi_RS_Ports_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 2;
    if((idx + N_bits) > bits.size())
    {
        printf("CSI_RS_Config_r10::setup::csi_RS_Ports_r10_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 3)
    {
        printf("CSI_RS_Config_r10::setup::csi_RS_Ports_r10_Unpack() max failure\n");
        return -1;
    }
    csi_RS_Ports_r10_internal_value = (csi_RS_Ports_r10_Enum)packed_val;
    csi_RS_Ports_r10_present = true;
    return 0;
}

CSI_RS_Config_r10::setup::csi_RS_Ports_r10_Enum CSI_RS_Config_r10::setup::csi_RS_Ports_r10_Value() const
{
    if(csi_RS_Ports_r10_present)
        return csi_RS_Ports_r10_internal_value;
    return (CSI_RS_Config_r10::setup::csi_RS_Ports_r10_Enum)0;
}

int CSI_RS_Config_r10::setup::csi_RS_Ports_r10_SetValue(csi_RS_Ports_r10_Enum value)
{
    csi_RS_Ports_r10_internal_value = value;
    csi_RS_Ports_r10_present = true;
    return 0;
}

int CSI_RS_Config_r10::setup::csi_RS_Ports_r10_SetValue(std::string value)
{
    if("an1" == value)
    {
        csi_RS_Ports_r10_internal_value = k_csi_RS_Ports_r10_an1;
        csi_RS_Ports_r10_present = true;
        return 0;
    }
    if("an2" == value)
    {
        csi_RS_Ports_r10_internal_value = k_csi_RS_Ports_r10_an2;
        csi_RS_Ports_r10_present = true;
        return 0;
    }
    if("an4" == value)
    {
        csi_RS_Ports_r10_internal_value = k_csi_RS_Ports_r10_an4;
        csi_RS_Ports_r10_present = true;
        return 0;
    }
    if("an8" == value)
    {
        csi_RS_Ports_r10_internal_value = k_csi_RS_Ports_r10_an8;
        csi_RS_Ports_r10_present = true;
        return 0;
    }
    return 1;
}

std::string CSI_RS_Config_r10::setup::csi_RS_Ports_r10_ValueToString(csi_RS_Ports_r10_Enum value) const
{
    if(k_csi_RS_Ports_r10_an1 == value)
        return "an1";
    if(k_csi_RS_Ports_r10_an2 == value)
        return "an2";
    if(k_csi_RS_Ports_r10_an4 == value)
        return "an4";
    if(k_csi_RS_Ports_r10_an8 == value)
        return "an8";
    return "";
}

uint64_t CSI_RS_Config_r10::setup::csi_RS_Ports_r10_NumberOfValues() const
{
    return 4;
}

std::string CSI_RS_Config_r10::setup::csi_RS_Ports_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "csi_RS_Ports_r10 = " + csi_RS_Ports_r10_ValueToString(csi_RS_Ports_r10_internal_value) + "\n";
    return out;
}

std::string CSI_RS_Config_r10::setup::csi_RS_Ports_r10_ToStringNoNewLines() const
{
    std::string out = "csi_RS_Ports_r10=" + csi_RS_Ports_r10_ValueToString(csi_RS_Ports_r10_internal_value) + ",";
    return out;
}

int CSI_RS_Config_r10::setup::csi_RS_Ports_r10_Clear()
{
    csi_RS_Ports_r10_present = false;
    return 0;
}

bool CSI_RS_Config_r10::setup::csi_RS_Ports_r10_IsPresent() const
{
    return csi_RS_Ports_r10_present;
}

int CSI_RS_Config_r10::setup::locationIndex_r10_Pack(std::vector<uint8_t> &bits)
{
    if(!locationIndex_r10_present)
    {
        printf("CSI_RS_Config_r10::setup::locationIndex_r10_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = locationIndex_r10_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (31 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int CSI_RS_Config_r10::setup::locationIndex_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return locationIndex_r10_Unpack(bits, idx);
}

int CSI_RS_Config_r10::setup::locationIndex_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (31 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("CSI_RS_Config_r10::setup::locationIndex_r10_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    locationIndex_r10_internal_value = packed_val + 0;
    locationIndex_r10_present = true;
    return 0;
}

int64_t CSI_RS_Config_r10::setup::locationIndex_r10_Value() const
{
    if(locationIndex_r10_present)
        return locationIndex_r10_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int CSI_RS_Config_r10::setup::locationIndex_r10_SetValue(int64_t value)
{
    if(value < 0 || value > 31)
    {
        printf("CSI_RS_Config_r10::setup::locationIndex_r10_SetValue() range failure\n");
        return -1;
    }
    locationIndex_r10_internal_value = value;
    locationIndex_r10_present = true;
    return 0;
}

std::string CSI_RS_Config_r10::setup::locationIndex_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "locationIndex_r10 = " + std::to_string(locationIndex_r10_internal_value) + "\n";
    return out;
}

std::string CSI_RS_Config_r10::setup::locationIndex_r10_ToStringNoNewLines() const
{
    std::string out = "locationIndex_r10=" + std::to_string(locationIndex_r10_internal_value) + ",";
    return out;
}

int CSI_RS_Config_r10::setup::locationIndex_r10_Clear()
{
    locationIndex_r10_present = false;
    return 0;
}

bool CSI_RS_Config_r10::setup::locationIndex_r10_IsPresent() const
{
    return locationIndex_r10_present;
}

int CSI_RS_Config_r10::setup::csi_RS_SubframeConfig_r10_Pack(std::vector<uint8_t> &bits)
{
    if(!csi_RS_SubframeConfig_r10_present)
    {
        printf("CSI_RS_Config_r10::setup::csi_RS_SubframeConfig_r10_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = csi_RS_SubframeConfig_r10_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (154 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int CSI_RS_Config_r10::setup::csi_RS_SubframeConfig_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return csi_RS_SubframeConfig_r10_Unpack(bits, idx);
}

int CSI_RS_Config_r10::setup::csi_RS_SubframeConfig_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (154 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("CSI_RS_Config_r10::setup::csi_RS_SubframeConfig_r10_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    csi_RS_SubframeConfig_r10_internal_value = packed_val + 0;
    csi_RS_SubframeConfig_r10_present = true;
    return 0;
}

int64_t CSI_RS_Config_r10::setup::csi_RS_SubframeConfig_r10_Value() const
{
    if(csi_RS_SubframeConfig_r10_present)
        return csi_RS_SubframeConfig_r10_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int CSI_RS_Config_r10::setup::csi_RS_SubframeConfig_r10_SetValue(int64_t value)
{
    if(value < 0 || value > 154)
    {
        printf("CSI_RS_Config_r10::setup::csi_RS_SubframeConfig_r10_SetValue() range failure\n");
        return -1;
    }
    csi_RS_SubframeConfig_r10_internal_value = value;
    csi_RS_SubframeConfig_r10_present = true;
    return 0;
}

std::string CSI_RS_Config_r10::setup::csi_RS_SubframeConfig_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "csi_RS_SubframeConfig_r10 = " + std::to_string(csi_RS_SubframeConfig_r10_internal_value) + "\n";
    return out;
}

std::string CSI_RS_Config_r10::setup::csi_RS_SubframeConfig_r10_ToStringNoNewLines() const
{
    std::string out = "csi_RS_SubframeConfig_r10=" + std::to_string(csi_RS_SubframeConfig_r10_internal_value) + ",";
    return out;
}

int CSI_RS_Config_r10::setup::csi_RS_SubframeConfig_r10_Clear()
{
    csi_RS_SubframeConfig_r10_present = false;
    return 0;
}

bool CSI_RS_Config_r10::setup::csi_RS_SubframeConfig_r10_IsPresent() const
{
    return csi_RS_SubframeConfig_r10_present;
}

int CSI_RS_Config_r10::setup::rho_C_r10_Pack(std::vector<uint8_t> &bits)
{
    if(!rho_C_r10_present)
    {
        printf("CSI_RS_Config_r10::setup::rho_C_r10_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 16;
    if(size < 16 || size > 16)
    {
        printf("CSI_RS_Config_r10::setup::rho_C_r10_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((rho_C_r10_internal_value >> (16-i-1)) & 1);
    return 0;
}

int CSI_RS_Config_r10::setup::rho_C_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return rho_C_r10_Unpack(bits, idx);
}

int CSI_RS_Config_r10::setup::rho_C_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 16;
    if(size < 16 || size > 16)
    {
        printf("CSI_RS_Config_r10::setup::rho_C_r10_Unpack() size failure\n");
        return -1;
    }
    rho_C_r10_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("CSI_RS_Config_r10::setup::rho_C_r10_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        rho_C_r10_internal_value |= (uint16_t)bits[idx++] << (uint16_t)(16-i-1);
    rho_C_r10_present = true;
    return 0;
}

uint16_t CSI_RS_Config_r10::setup::rho_C_r10_Value() const
{
    if(rho_C_r10_present)
        return rho_C_r10_internal_value;
    uint16_t tmp = 0;
    return tmp;
}

int CSI_RS_Config_r10::setup::rho_C_r10_SetValue(uint16_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 16)
    {
        printf("CSI_RS_Config_r10::setup::rho_C_r10_SetValue() size failure\n");
        return -1;
    }
    rho_C_r10_internal_value = value;
    rho_C_r10_present = true;
    return 0;
}

std::string CSI_RS_Config_r10::setup::rho_C_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "rho_C_r10 = ";
    out += std::to_string(rho_C_r10_internal_value);
    out += "\n";
    return out;
}

std::string CSI_RS_Config_r10::setup::rho_C_r10_ToStringNoNewLines() const
{
    std::string out = "rho_C_r10=";
    out += std::to_string(rho_C_r10_internal_value);
    out += ",";
    return out;
}

int CSI_RS_Config_r10::setup::rho_C_r10_Clear()
{
    rho_C_r10_present = false;
    return 0;
}

bool CSI_RS_Config_r10::setup::rho_C_r10_IsPresent() const
{
    return rho_C_r10_present;
}

int CSI_RS_Config_r10::setup::csi_RS_WithZeroTransmissionPower_r10_Pack(std::vector<uint8_t> &bits)
{
    if(!csi_RS_WithZeroTransmissionPower_r10_present)
    {
        printf("CSI_RS_Config_r10::setup::csi_RS_WithZeroTransmissionPower_r10_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 16;
    if(size < 16 || size > 16)
    {
        printf("CSI_RS_Config_r10::setup::csi_RS_WithZeroTransmissionPower_r10_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((csi_RS_WithZeroTransmissionPower_r10_internal_value >> (16-i-1)) & 1);
    return 0;
}

int CSI_RS_Config_r10::setup::csi_RS_WithZeroTransmissionPower_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return csi_RS_WithZeroTransmissionPower_r10_Unpack(bits, idx);
}

int CSI_RS_Config_r10::setup::csi_RS_WithZeroTransmissionPower_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 16;
    if(size < 16 || size > 16)
    {
        printf("CSI_RS_Config_r10::setup::csi_RS_WithZeroTransmissionPower_r10_Unpack() size failure\n");
        return -1;
    }
    csi_RS_WithZeroTransmissionPower_r10_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("CSI_RS_Config_r10::setup::csi_RS_WithZeroTransmissionPower_r10_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        csi_RS_WithZeroTransmissionPower_r10_internal_value |= (uint16_t)bits[idx++] << (uint16_t)(16-i-1);
    csi_RS_WithZeroTransmissionPower_r10_present = true;
    return 0;
}

uint16_t CSI_RS_Config_r10::setup::csi_RS_WithZeroTransmissionPower_r10_Value() const
{
    if(csi_RS_WithZeroTransmissionPower_r10_present)
        return csi_RS_WithZeroTransmissionPower_r10_internal_value;
    uint16_t tmp = 0;
    return tmp;
}

int CSI_RS_Config_r10::setup::csi_RS_WithZeroTransmissionPower_r10_SetValue(uint16_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 16)
    {
        printf("CSI_RS_Config_r10::setup::csi_RS_WithZeroTransmissionPower_r10_SetValue() size failure\n");
        return -1;
    }
    csi_RS_WithZeroTransmissionPower_r10_internal_value = value;
    csi_RS_WithZeroTransmissionPower_r10_present = true;
    return 0;
}

std::string CSI_RS_Config_r10::setup::csi_RS_WithZeroTransmissionPower_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "csi_RS_WithZeroTransmissionPower_r10 = ";
    out += std::to_string(csi_RS_WithZeroTransmissionPower_r10_internal_value);
    out += "\n";
    return out;
}

std::string CSI_RS_Config_r10::setup::csi_RS_WithZeroTransmissionPower_r10_ToStringNoNewLines() const
{
    std::string out = "csi_RS_WithZeroTransmissionPower_r10=";
    out += std::to_string(csi_RS_WithZeroTransmissionPower_r10_internal_value);
    out += ",";
    return out;
}

int CSI_RS_Config_r10::setup::csi_RS_WithZeroTransmissionPower_r10_Clear()
{
    csi_RS_WithZeroTransmissionPower_r10_present = false;
    return 0;
}

bool CSI_RS_Config_r10::setup::csi_RS_WithZeroTransmissionPower_r10_IsPresent() const
{
    return csi_RS_WithZeroTransmissionPower_r10_present;
}

