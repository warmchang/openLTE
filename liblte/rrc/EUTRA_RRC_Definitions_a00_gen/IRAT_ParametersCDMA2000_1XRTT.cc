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

#include "IRAT_ParametersCDMA2000_1XRTT.h"

#include <cmath>

int IRAT_ParametersCDMA2000_1XRTT::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != supportedBandList1XRTT.Pack(bits))
        {
            printf("IRAT_ParametersCDMA2000_1XRTT:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != tx_Config1XRTT_Pack(bits))
        {
            printf("IRAT_ParametersCDMA2000_1XRTT:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != rx_Config1XRTT_Pack(bits))
        {
            printf("IRAT_ParametersCDMA2000_1XRTT:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int IRAT_ParametersCDMA2000_1XRTT::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int IRAT_ParametersCDMA2000_1XRTT::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != supportedBandList1XRTT.Unpack(bits, idx))
        {
            printf("IRAT_ParametersCDMA2000_1XRTT:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != tx_Config1XRTT_Unpack(bits, idx))
        {
            printf("IRAT_ParametersCDMA2000_1XRTT:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != rx_Config1XRTT_Unpack(bits, idx))
        {
            printf("IRAT_ParametersCDMA2000_1XRTT:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string IRAT_ParametersCDMA2000_1XRTT::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "IRAT_ParametersCDMA2000_1XRTT:\n";
    out += supportedBandList1XRTT_ToString(indent+1);
    out += tx_Config1XRTT_ToString(indent+1);
    out += rx_Config1XRTT_ToString(indent+1);
    return out;
}

std::string IRAT_ParametersCDMA2000_1XRTT::ToStringNoNewLines() const
{
    std::string out = "IRAT_ParametersCDMA2000_1XRTT:";
    out += supportedBandList1XRTT_ToStringNoNewLines();
    out += tx_Config1XRTT_ToStringNoNewLines();
    out += rx_Config1XRTT_ToStringNoNewLines();
    return out;
}

SupportedBandList1XRTT* IRAT_ParametersCDMA2000_1XRTT::supportedBandList1XRTT_Set()
{
    supportedBandList1XRTT_present = true;
    return &supportedBandList1XRTT;
}

int IRAT_ParametersCDMA2000_1XRTT::supportedBandList1XRTT_Set(SupportedBandList1XRTT &value)
{
    supportedBandList1XRTT_present = true;
    supportedBandList1XRTT = value;
    return 0;
}

const SupportedBandList1XRTT& IRAT_ParametersCDMA2000_1XRTT::supportedBandList1XRTT_Get() const
{
    return supportedBandList1XRTT;
}

std::string IRAT_ParametersCDMA2000_1XRTT::supportedBandList1XRTT_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "supportedBandList1XRTT:\n";
    out += supportedBandList1XRTT.ToString(indent+1);
    return out;
}

std::string IRAT_ParametersCDMA2000_1XRTT::supportedBandList1XRTT_ToStringNoNewLines() const
{
    std::string out = "supportedBandList1XRTT:";
    out += supportedBandList1XRTT.ToStringNoNewLines();
    return out;
}

int IRAT_ParametersCDMA2000_1XRTT::supportedBandList1XRTT_Clear()
{
    supportedBandList1XRTT_present = false;
    return 0;
}

bool IRAT_ParametersCDMA2000_1XRTT::supportedBandList1XRTT_IsPresent() const
{
    return supportedBandList1XRTT_present;
}

int IRAT_ParametersCDMA2000_1XRTT::tx_Config1XRTT_Pack(std::vector<uint8_t> &bits)
{
    if(!tx_Config1XRTT_present)
    {
        printf("IRAT_ParametersCDMA2000_1XRTT::tx_Config1XRTT_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((tx_Config1XRTT_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int IRAT_ParametersCDMA2000_1XRTT::tx_Config1XRTT_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return tx_Config1XRTT_Unpack(bits, idx);
}

int IRAT_ParametersCDMA2000_1XRTT::tx_Config1XRTT_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("IRAT_ParametersCDMA2000_1XRTT::tx_Config1XRTT_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 1)
    {
        printf("IRAT_ParametersCDMA2000_1XRTT::tx_Config1XRTT_Unpack() max failure\n");
        return -1;
    }
    tx_Config1XRTT_internal_value = (tx_Config1XRTT_Enum)packed_val;
    tx_Config1XRTT_present = true;
    return 0;
}

IRAT_ParametersCDMA2000_1XRTT::tx_Config1XRTT_Enum IRAT_ParametersCDMA2000_1XRTT::tx_Config1XRTT_Value() const
{
    if(tx_Config1XRTT_present)
        return tx_Config1XRTT_internal_value;
    return (IRAT_ParametersCDMA2000_1XRTT::tx_Config1XRTT_Enum)0;
}

int IRAT_ParametersCDMA2000_1XRTT::tx_Config1XRTT_SetValue(tx_Config1XRTT_Enum value)
{
    tx_Config1XRTT_internal_value = value;
    tx_Config1XRTT_present = true;
    return 0;
}

int IRAT_ParametersCDMA2000_1XRTT::tx_Config1XRTT_SetValue(std::string value)
{
    if("single" == value)
    {
        tx_Config1XRTT_internal_value = k_tx_Config1XRTT_single;
        tx_Config1XRTT_present = true;
        return 0;
    }
    if("dual" == value)
    {
        tx_Config1XRTT_internal_value = k_tx_Config1XRTT_dual;
        tx_Config1XRTT_present = true;
        return 0;
    }
    return 1;
}

std::string IRAT_ParametersCDMA2000_1XRTT::tx_Config1XRTT_ValueToString(tx_Config1XRTT_Enum value) const
{
    if(k_tx_Config1XRTT_single == value)
        return "single";
    if(k_tx_Config1XRTT_dual == value)
        return "dual";
    return "";
}

uint64_t IRAT_ParametersCDMA2000_1XRTT::tx_Config1XRTT_NumberOfValues() const
{
    return 2;
}

std::string IRAT_ParametersCDMA2000_1XRTT::tx_Config1XRTT_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "tx_Config1XRTT = " + tx_Config1XRTT_ValueToString(tx_Config1XRTT_internal_value) + "\n";
    return out;
}

std::string IRAT_ParametersCDMA2000_1XRTT::tx_Config1XRTT_ToStringNoNewLines() const
{
    std::string out = "tx_Config1XRTT=" + tx_Config1XRTT_ValueToString(tx_Config1XRTT_internal_value) + ",";
    return out;
}

int IRAT_ParametersCDMA2000_1XRTT::tx_Config1XRTT_Clear()
{
    tx_Config1XRTT_present = false;
    return 0;
}

bool IRAT_ParametersCDMA2000_1XRTT::tx_Config1XRTT_IsPresent() const
{
    return tx_Config1XRTT_present;
}

int IRAT_ParametersCDMA2000_1XRTT::rx_Config1XRTT_Pack(std::vector<uint8_t> &bits)
{
    if(!rx_Config1XRTT_present)
    {
        printf("IRAT_ParametersCDMA2000_1XRTT::rx_Config1XRTT_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((rx_Config1XRTT_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int IRAT_ParametersCDMA2000_1XRTT::rx_Config1XRTT_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return rx_Config1XRTT_Unpack(bits, idx);
}

int IRAT_ParametersCDMA2000_1XRTT::rx_Config1XRTT_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("IRAT_ParametersCDMA2000_1XRTT::rx_Config1XRTT_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 1)
    {
        printf("IRAT_ParametersCDMA2000_1XRTT::rx_Config1XRTT_Unpack() max failure\n");
        return -1;
    }
    rx_Config1XRTT_internal_value = (rx_Config1XRTT_Enum)packed_val;
    rx_Config1XRTT_present = true;
    return 0;
}

IRAT_ParametersCDMA2000_1XRTT::rx_Config1XRTT_Enum IRAT_ParametersCDMA2000_1XRTT::rx_Config1XRTT_Value() const
{
    if(rx_Config1XRTT_present)
        return rx_Config1XRTT_internal_value;
    return (IRAT_ParametersCDMA2000_1XRTT::rx_Config1XRTT_Enum)0;
}

int IRAT_ParametersCDMA2000_1XRTT::rx_Config1XRTT_SetValue(rx_Config1XRTT_Enum value)
{
    rx_Config1XRTT_internal_value = value;
    rx_Config1XRTT_present = true;
    return 0;
}

int IRAT_ParametersCDMA2000_1XRTT::rx_Config1XRTT_SetValue(std::string value)
{
    if("single" == value)
    {
        rx_Config1XRTT_internal_value = k_rx_Config1XRTT_single;
        rx_Config1XRTT_present = true;
        return 0;
    }
    if("dual" == value)
    {
        rx_Config1XRTT_internal_value = k_rx_Config1XRTT_dual;
        rx_Config1XRTT_present = true;
        return 0;
    }
    return 1;
}

std::string IRAT_ParametersCDMA2000_1XRTT::rx_Config1XRTT_ValueToString(rx_Config1XRTT_Enum value) const
{
    if(k_rx_Config1XRTT_single == value)
        return "single";
    if(k_rx_Config1XRTT_dual == value)
        return "dual";
    return "";
}

uint64_t IRAT_ParametersCDMA2000_1XRTT::rx_Config1XRTT_NumberOfValues() const
{
    return 2;
}

std::string IRAT_ParametersCDMA2000_1XRTT::rx_Config1XRTT_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "rx_Config1XRTT = " + rx_Config1XRTT_ValueToString(rx_Config1XRTT_internal_value) + "\n";
    return out;
}

std::string IRAT_ParametersCDMA2000_1XRTT::rx_Config1XRTT_ToStringNoNewLines() const
{
    std::string out = "rx_Config1XRTT=" + rx_Config1XRTT_ValueToString(rx_Config1XRTT_internal_value) + ",";
    return out;
}

int IRAT_ParametersCDMA2000_1XRTT::rx_Config1XRTT_Clear()
{
    rx_Config1XRTT_present = false;
    return 0;
}

bool IRAT_ParametersCDMA2000_1XRTT::rx_Config1XRTT_IsPresent() const
{
    return rx_Config1XRTT_present;
}

