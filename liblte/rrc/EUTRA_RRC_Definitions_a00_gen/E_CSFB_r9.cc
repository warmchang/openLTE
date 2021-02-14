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

#include "E_CSFB_r9.h"

#include <cmath>

int E_CSFB_r9::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(messageContCDMA2000_1XRTT_r9_IsPresent());
    bits.push_back(mobilityCDMA2000_HRPD_r9_IsPresent());
    bits.push_back(messageContCDMA2000_HRPD_r9_IsPresent());
    bits.push_back(redirectCarrierCDMA2000_HRPD_r9_IsPresent());

    // Fields
    if(messageContCDMA2000_1XRTT_r9_IsPresent())
    {
        if(0 != messageContCDMA2000_1XRTT_r9_Pack(bits))
        {
            printf("E_CSFB_r9:: field pack failure\n");
            return -1;
        }
    }
    if(mobilityCDMA2000_HRPD_r9_IsPresent())
    {
        if(0 != mobilityCDMA2000_HRPD_r9_Pack(bits))
        {
            printf("E_CSFB_r9:: field pack failure\n");
            return -1;
        }
    }
    if(messageContCDMA2000_HRPD_r9_IsPresent())
    {
        if(0 != messageContCDMA2000_HRPD_r9_Pack(bits))
        {
            printf("E_CSFB_r9:: field pack failure\n");
            return -1;
        }
    }
    if(redirectCarrierCDMA2000_HRPD_r9_IsPresent())
    {
        if(0 != redirectCarrierCDMA2000_HRPD_r9.Pack(bits))
        {
            printf("E_CSFB_r9:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int E_CSFB_r9::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int E_CSFB_r9::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("E_CSFB_r9::Unpack() index out of bounds for optional indiator messageContCDMA2000_1XRTT_r9\n");
        return -1;
    }
    messageContCDMA2000_1XRTT_r9_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("E_CSFB_r9::Unpack() index out of bounds for optional indiator mobilityCDMA2000_HRPD_r9\n");
        return -1;
    }
    mobilityCDMA2000_HRPD_r9_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("E_CSFB_r9::Unpack() index out of bounds for optional indiator messageContCDMA2000_HRPD_r9\n");
        return -1;
    }
    messageContCDMA2000_HRPD_r9_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("E_CSFB_r9::Unpack() index out of bounds for optional indiator redirectCarrierCDMA2000_HRPD_r9\n");
        return -1;
    }
    redirectCarrierCDMA2000_HRPD_r9_present = bits[idx++];

    // Fields
    if(messageContCDMA2000_1XRTT_r9_present)
    {
        if(0 != messageContCDMA2000_1XRTT_r9_Unpack(bits, idx))
        {
            printf("E_CSFB_r9:: field unpack failure\n");
            return -1;
        }
    }
    if(mobilityCDMA2000_HRPD_r9_present)
    {
        if(0 != mobilityCDMA2000_HRPD_r9_Unpack(bits, idx))
        {
            printf("E_CSFB_r9:: field unpack failure\n");
            return -1;
        }
    }
    if(messageContCDMA2000_HRPD_r9_present)
    {
        if(0 != messageContCDMA2000_HRPD_r9_Unpack(bits, idx))
        {
            printf("E_CSFB_r9:: field unpack failure\n");
            return -1;
        }
    }
    if(redirectCarrierCDMA2000_HRPD_r9_present)
    {
        if(0 != redirectCarrierCDMA2000_HRPD_r9.Unpack(bits, idx))
        {
            printf("E_CSFB_r9:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string E_CSFB_r9::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "E_CSFB_r9:\n";
    if(messageContCDMA2000_1XRTT_r9_IsPresent())
        out += messageContCDMA2000_1XRTT_r9_ToString(indent+1);
    if(mobilityCDMA2000_HRPD_r9_IsPresent())
        out += mobilityCDMA2000_HRPD_r9_ToString(indent+1);
    if(messageContCDMA2000_HRPD_r9_IsPresent())
        out += messageContCDMA2000_HRPD_r9_ToString(indent+1);
    if(redirectCarrierCDMA2000_HRPD_r9_IsPresent())
        out += redirectCarrierCDMA2000_HRPD_r9_ToString(indent+1);
    return out;
}

std::string E_CSFB_r9::ToStringNoNewLines() const
{
    std::string out = "E_CSFB_r9:";
    if(messageContCDMA2000_1XRTT_r9_IsPresent())
        out += messageContCDMA2000_1XRTT_r9_ToStringNoNewLines();
    if(mobilityCDMA2000_HRPD_r9_IsPresent())
        out += mobilityCDMA2000_HRPD_r9_ToStringNoNewLines();
    if(messageContCDMA2000_HRPD_r9_IsPresent())
        out += messageContCDMA2000_HRPD_r9_ToStringNoNewLines();
    if(redirectCarrierCDMA2000_HRPD_r9_IsPresent())
        out += redirectCarrierCDMA2000_HRPD_r9_ToStringNoNewLines();
    return out;
}

int E_CSFB_r9::messageContCDMA2000_1XRTT_r9_Pack(std::vector<uint8_t> &bits)
{
    uint32_t local_size_length = 0;
    uint32_t local_size = messageContCDMA2000_1XRTT_r9_internal_value.size();
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
    for(uint32_t i=0; i<messageContCDMA2000_1XRTT_r9_internal_value.size(); i++)
        for(uint32_t j=0; j<8; j++)
            bits.push_back((messageContCDMA2000_1XRTT_r9_internal_value[i] >> (8-j-1)) & 1);
    return 0;
}

int E_CSFB_r9::messageContCDMA2000_1XRTT_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return messageContCDMA2000_1XRTT_r9_Unpack(bits, idx);
}

int E_CSFB_r9::messageContCDMA2000_1XRTT_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
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
    messageContCDMA2000_1XRTT_r9_internal_value.clear();
    if((idx +size*8) > bits.size())
    {
        printf("E_CSFB_r9::messageContCDMA2000_1XRTT_r9_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
    {
        uint8_t value = 0;
        for(uint32_t j=0; j<8; j++)
            value |= bits[idx+j] << (8-j-1);
        messageContCDMA2000_1XRTT_r9_internal_value.push_back(value);
        idx += 8;
    }
    messageContCDMA2000_1XRTT_r9_present = true;
    return 0;
}

std::vector<uint8_t> E_CSFB_r9::messageContCDMA2000_1XRTT_r9_Value() const
{
    if(messageContCDMA2000_1XRTT_r9_present)
        return messageContCDMA2000_1XRTT_r9_internal_value;
    std::vector<uint8_t> tmp;
    return tmp;
}

int E_CSFB_r9::messageContCDMA2000_1XRTT_r9_SetValue(std::vector<uint8_t> value)
{
    messageContCDMA2000_1XRTT_r9_internal_value = value;
    messageContCDMA2000_1XRTT_r9_present = true;
    return 0;
}

std::string E_CSFB_r9::messageContCDMA2000_1XRTT_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "messageContCDMA2000_1XRTT_r9 = {";
    for(auto byte : messageContCDMA2000_1XRTT_r9_internal_value)
        out += std::to_string(byte) + ",";
    out = out.substr(0, out.length()-1) + "}\n";
    return out;
}

std::string E_CSFB_r9::messageContCDMA2000_1XRTT_r9_ToStringNoNewLines() const
{
    std::string out = "messageContCDMA2000_1XRTT_r9={";
    for(auto byte : messageContCDMA2000_1XRTT_r9_internal_value)
        out += std::to_string(byte) + ",";
    out = out.substr(0, out.length()-1) + "},";
    return out;
}

int E_CSFB_r9::messageContCDMA2000_1XRTT_r9_Clear()
{
    messageContCDMA2000_1XRTT_r9_present = false;
    return 0;
}

bool E_CSFB_r9::messageContCDMA2000_1XRTT_r9_IsPresent() const
{
    return messageContCDMA2000_1XRTT_r9_present;
}

int E_CSFB_r9::mobilityCDMA2000_HRPD_r9_Pack(std::vector<uint8_t> &bits)
{
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((mobilityCDMA2000_HRPD_r9_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int E_CSFB_r9::mobilityCDMA2000_HRPD_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return mobilityCDMA2000_HRPD_r9_Unpack(bits, idx);
}

int E_CSFB_r9::mobilityCDMA2000_HRPD_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("E_CSFB_r9::mobilityCDMA2000_HRPD_r9_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 1)
    {
        printf("E_CSFB_r9::mobilityCDMA2000_HRPD_r9_Unpack() max failure\n");
        return -1;
    }
    mobilityCDMA2000_HRPD_r9_internal_value = (mobilityCDMA2000_HRPD_r9_Enum)packed_val;
    mobilityCDMA2000_HRPD_r9_present = true;
    return 0;
}

E_CSFB_r9::mobilityCDMA2000_HRPD_r9_Enum E_CSFB_r9::mobilityCDMA2000_HRPD_r9_Value() const
{
    if(mobilityCDMA2000_HRPD_r9_present)
        return mobilityCDMA2000_HRPD_r9_internal_value;
    return (E_CSFB_r9::mobilityCDMA2000_HRPD_r9_Enum)0;
}

int E_CSFB_r9::mobilityCDMA2000_HRPD_r9_SetValue(mobilityCDMA2000_HRPD_r9_Enum value)
{
    mobilityCDMA2000_HRPD_r9_internal_value = value;
    mobilityCDMA2000_HRPD_r9_present = true;
    return 0;
}

int E_CSFB_r9::mobilityCDMA2000_HRPD_r9_SetValue(std::string value)
{
    if("handover" == value)
    {
        mobilityCDMA2000_HRPD_r9_internal_value = k_mobilityCDMA2000_HRPD_r9_handover;
        mobilityCDMA2000_HRPD_r9_present = true;
        return 0;
    }
    if("redirection" == value)
    {
        mobilityCDMA2000_HRPD_r9_internal_value = k_mobilityCDMA2000_HRPD_r9_redirection;
        mobilityCDMA2000_HRPD_r9_present = true;
        return 0;
    }
    return 1;
}

std::string E_CSFB_r9::mobilityCDMA2000_HRPD_r9_ValueToString(mobilityCDMA2000_HRPD_r9_Enum value) const
{
    if(k_mobilityCDMA2000_HRPD_r9_handover == value)
        return "handover";
    if(k_mobilityCDMA2000_HRPD_r9_redirection == value)
        return "redirection";
    return "";
}

uint64_t E_CSFB_r9::mobilityCDMA2000_HRPD_r9_NumberOfValues() const
{
    return 2;
}

std::string E_CSFB_r9::mobilityCDMA2000_HRPD_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "mobilityCDMA2000_HRPD_r9 = " + mobilityCDMA2000_HRPD_r9_ValueToString(mobilityCDMA2000_HRPD_r9_internal_value) + "\n";
    return out;
}

std::string E_CSFB_r9::mobilityCDMA2000_HRPD_r9_ToStringNoNewLines() const
{
    std::string out = "mobilityCDMA2000_HRPD_r9=" + mobilityCDMA2000_HRPD_r9_ValueToString(mobilityCDMA2000_HRPD_r9_internal_value) + ",";
    return out;
}

int E_CSFB_r9::mobilityCDMA2000_HRPD_r9_Clear()
{
    mobilityCDMA2000_HRPD_r9_present = false;
    return 0;
}

bool E_CSFB_r9::mobilityCDMA2000_HRPD_r9_IsPresent() const
{
    return mobilityCDMA2000_HRPD_r9_present;
}

int E_CSFB_r9::messageContCDMA2000_HRPD_r9_Pack(std::vector<uint8_t> &bits)
{
    uint32_t local_size_length = 0;
    uint32_t local_size = messageContCDMA2000_HRPD_r9_internal_value.size();
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
    for(uint32_t i=0; i<messageContCDMA2000_HRPD_r9_internal_value.size(); i++)
        for(uint32_t j=0; j<8; j++)
            bits.push_back((messageContCDMA2000_HRPD_r9_internal_value[i] >> (8-j-1)) & 1);
    return 0;
}

int E_CSFB_r9::messageContCDMA2000_HRPD_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return messageContCDMA2000_HRPD_r9_Unpack(bits, idx);
}

int E_CSFB_r9::messageContCDMA2000_HRPD_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
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
    messageContCDMA2000_HRPD_r9_internal_value.clear();
    if((idx +size*8) > bits.size())
    {
        printf("E_CSFB_r9::messageContCDMA2000_HRPD_r9_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
    {
        uint8_t value = 0;
        for(uint32_t j=0; j<8; j++)
            value |= bits[idx+j] << (8-j-1);
        messageContCDMA2000_HRPD_r9_internal_value.push_back(value);
        idx += 8;
    }
    messageContCDMA2000_HRPD_r9_present = true;
    return 0;
}

std::vector<uint8_t> E_CSFB_r9::messageContCDMA2000_HRPD_r9_Value() const
{
    if(messageContCDMA2000_HRPD_r9_present)
        return messageContCDMA2000_HRPD_r9_internal_value;
    std::vector<uint8_t> tmp;
    return tmp;
}

int E_CSFB_r9::messageContCDMA2000_HRPD_r9_SetValue(std::vector<uint8_t> value)
{
    messageContCDMA2000_HRPD_r9_internal_value = value;
    messageContCDMA2000_HRPD_r9_present = true;
    return 0;
}

std::string E_CSFB_r9::messageContCDMA2000_HRPD_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "messageContCDMA2000_HRPD_r9 = {";
    for(auto byte : messageContCDMA2000_HRPD_r9_internal_value)
        out += std::to_string(byte) + ",";
    out = out.substr(0, out.length()-1) + "}\n";
    return out;
}

std::string E_CSFB_r9::messageContCDMA2000_HRPD_r9_ToStringNoNewLines() const
{
    std::string out = "messageContCDMA2000_HRPD_r9={";
    for(auto byte : messageContCDMA2000_HRPD_r9_internal_value)
        out += std::to_string(byte) + ",";
    out = out.substr(0, out.length()-1) + "},";
    return out;
}

int E_CSFB_r9::messageContCDMA2000_HRPD_r9_Clear()
{
    messageContCDMA2000_HRPD_r9_present = false;
    return 0;
}

bool E_CSFB_r9::messageContCDMA2000_HRPD_r9_IsPresent() const
{
    return messageContCDMA2000_HRPD_r9_present;
}

CarrierFreqCDMA2000* E_CSFB_r9::redirectCarrierCDMA2000_HRPD_r9_Set()
{
    redirectCarrierCDMA2000_HRPD_r9_present = true;
    return &redirectCarrierCDMA2000_HRPD_r9;
}

int E_CSFB_r9::redirectCarrierCDMA2000_HRPD_r9_Set(CarrierFreqCDMA2000 &value)
{
    redirectCarrierCDMA2000_HRPD_r9_present = true;
    redirectCarrierCDMA2000_HRPD_r9 = value;
    return 0;
}

const CarrierFreqCDMA2000& E_CSFB_r9::redirectCarrierCDMA2000_HRPD_r9_Get() const
{
    return redirectCarrierCDMA2000_HRPD_r9;
}

std::string E_CSFB_r9::redirectCarrierCDMA2000_HRPD_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "redirectCarrierCDMA2000_HRPD_r9:\n";
    out += redirectCarrierCDMA2000_HRPD_r9.ToString(indent+1);
    return out;
}

std::string E_CSFB_r9::redirectCarrierCDMA2000_HRPD_r9_ToStringNoNewLines() const
{
    std::string out = "redirectCarrierCDMA2000_HRPD_r9:";
    out += redirectCarrierCDMA2000_HRPD_r9.ToStringNoNewLines();
    return out;
}

int E_CSFB_r9::redirectCarrierCDMA2000_HRPD_r9_Clear()
{
    redirectCarrierCDMA2000_HRPD_r9_present = false;
    return 0;
}

bool E_CSFB_r9::redirectCarrierCDMA2000_HRPD_r9_IsPresent() const
{
    return redirectCarrierCDMA2000_HRPD_r9_present;
}

