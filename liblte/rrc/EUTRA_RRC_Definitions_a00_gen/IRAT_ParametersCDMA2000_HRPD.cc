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

#include "IRAT_ParametersCDMA2000_HRPD.h"

#include <cmath>

int IRAT_ParametersCDMA2000_HRPD::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != supportedBandListHRPD.Pack(bits))
        {
            printf("IRAT_ParametersCDMA2000_HRPD:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != tx_ConfigHRPD_Pack(bits))
        {
            printf("IRAT_ParametersCDMA2000_HRPD:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != rx_ConfigHRPD_Pack(bits))
        {
            printf("IRAT_ParametersCDMA2000_HRPD:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int IRAT_ParametersCDMA2000_HRPD::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int IRAT_ParametersCDMA2000_HRPD::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != supportedBandListHRPD.Unpack(bits, idx))
        {
            printf("IRAT_ParametersCDMA2000_HRPD:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != tx_ConfigHRPD_Unpack(bits, idx))
        {
            printf("IRAT_ParametersCDMA2000_HRPD:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != rx_ConfigHRPD_Unpack(bits, idx))
        {
            printf("IRAT_ParametersCDMA2000_HRPD:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string IRAT_ParametersCDMA2000_HRPD::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "IRAT_ParametersCDMA2000_HRPD:\n";
    out += supportedBandListHRPD_ToString(indent+1);
    out += tx_ConfigHRPD_ToString(indent+1);
    out += rx_ConfigHRPD_ToString(indent+1);
    return out;
}

std::string IRAT_ParametersCDMA2000_HRPD::ToStringNoNewLines() const
{
    std::string out = "IRAT_ParametersCDMA2000_HRPD:";
    out += supportedBandListHRPD_ToStringNoNewLines();
    out += tx_ConfigHRPD_ToStringNoNewLines();
    out += rx_ConfigHRPD_ToStringNoNewLines();
    return out;
}

SupportedBandListHRPD* IRAT_ParametersCDMA2000_HRPD::supportedBandListHRPD_Set()
{
    supportedBandListHRPD_present = true;
    return &supportedBandListHRPD;
}

int IRAT_ParametersCDMA2000_HRPD::supportedBandListHRPD_Set(SupportedBandListHRPD &value)
{
    supportedBandListHRPD_present = true;
    supportedBandListHRPD = value;
    return 0;
}

const SupportedBandListHRPD& IRAT_ParametersCDMA2000_HRPD::supportedBandListHRPD_Get() const
{
    return supportedBandListHRPD;
}

std::string IRAT_ParametersCDMA2000_HRPD::supportedBandListHRPD_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "supportedBandListHRPD:\n";
    out += supportedBandListHRPD.ToString(indent+1);
    return out;
}

std::string IRAT_ParametersCDMA2000_HRPD::supportedBandListHRPD_ToStringNoNewLines() const
{
    std::string out = "supportedBandListHRPD:";
    out += supportedBandListHRPD.ToStringNoNewLines();
    return out;
}

int IRAT_ParametersCDMA2000_HRPD::supportedBandListHRPD_Clear()
{
    supportedBandListHRPD_present = false;
    return 0;
}

bool IRAT_ParametersCDMA2000_HRPD::supportedBandListHRPD_IsPresent() const
{
    return supportedBandListHRPD_present;
}

int IRAT_ParametersCDMA2000_HRPD::tx_ConfigHRPD_Pack(std::vector<uint8_t> &bits)
{
    if(!tx_ConfigHRPD_present)
    {
        printf("IRAT_ParametersCDMA2000_HRPD::tx_ConfigHRPD_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((tx_ConfigHRPD_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int IRAT_ParametersCDMA2000_HRPD::tx_ConfigHRPD_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return tx_ConfigHRPD_Unpack(bits, idx);
}

int IRAT_ParametersCDMA2000_HRPD::tx_ConfigHRPD_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("IRAT_ParametersCDMA2000_HRPD::tx_ConfigHRPD_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 1)
    {
        printf("IRAT_ParametersCDMA2000_HRPD::tx_ConfigHRPD_Unpack() max failure\n");
        return -1;
    }
    tx_ConfigHRPD_internal_value = (tx_ConfigHRPD_Enum)packed_val;
    tx_ConfigHRPD_present = true;
    return 0;
}

IRAT_ParametersCDMA2000_HRPD::tx_ConfigHRPD_Enum IRAT_ParametersCDMA2000_HRPD::tx_ConfigHRPD_Value() const
{
    if(tx_ConfigHRPD_present)
        return tx_ConfigHRPD_internal_value;
    return (IRAT_ParametersCDMA2000_HRPD::tx_ConfigHRPD_Enum)0;
}

int IRAT_ParametersCDMA2000_HRPD::tx_ConfigHRPD_SetValue(tx_ConfigHRPD_Enum value)
{
    tx_ConfigHRPD_internal_value = value;
    tx_ConfigHRPD_present = true;
    return 0;
}

int IRAT_ParametersCDMA2000_HRPD::tx_ConfigHRPD_SetValue(std::string value)
{
    if("single" == value)
    {
        tx_ConfigHRPD_internal_value = k_tx_ConfigHRPD_single;
        tx_ConfigHRPD_present = true;
        return 0;
    }
    if("dual" == value)
    {
        tx_ConfigHRPD_internal_value = k_tx_ConfigHRPD_dual;
        tx_ConfigHRPD_present = true;
        return 0;
    }
    return 1;
}

std::string IRAT_ParametersCDMA2000_HRPD::tx_ConfigHRPD_ValueToString(tx_ConfigHRPD_Enum value) const
{
    if(k_tx_ConfigHRPD_single == value)
        return "single";
    if(k_tx_ConfigHRPD_dual == value)
        return "dual";
    return "";
}

uint64_t IRAT_ParametersCDMA2000_HRPD::tx_ConfigHRPD_NumberOfValues() const
{
    return 2;
}

std::string IRAT_ParametersCDMA2000_HRPD::tx_ConfigHRPD_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "tx_ConfigHRPD = " + tx_ConfigHRPD_ValueToString(tx_ConfigHRPD_internal_value) + "\n";
    return out;
}

std::string IRAT_ParametersCDMA2000_HRPD::tx_ConfigHRPD_ToStringNoNewLines() const
{
    std::string out = "tx_ConfigHRPD=" + tx_ConfigHRPD_ValueToString(tx_ConfigHRPD_internal_value) + ",";
    return out;
}

int IRAT_ParametersCDMA2000_HRPD::tx_ConfigHRPD_Clear()
{
    tx_ConfigHRPD_present = false;
    return 0;
}

bool IRAT_ParametersCDMA2000_HRPD::tx_ConfigHRPD_IsPresent() const
{
    return tx_ConfigHRPD_present;
}

int IRAT_ParametersCDMA2000_HRPD::rx_ConfigHRPD_Pack(std::vector<uint8_t> &bits)
{
    if(!rx_ConfigHRPD_present)
    {
        printf("IRAT_ParametersCDMA2000_HRPD::rx_ConfigHRPD_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((rx_ConfigHRPD_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int IRAT_ParametersCDMA2000_HRPD::rx_ConfigHRPD_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return rx_ConfigHRPD_Unpack(bits, idx);
}

int IRAT_ParametersCDMA2000_HRPD::rx_ConfigHRPD_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("IRAT_ParametersCDMA2000_HRPD::rx_ConfigHRPD_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 1)
    {
        printf("IRAT_ParametersCDMA2000_HRPD::rx_ConfigHRPD_Unpack() max failure\n");
        return -1;
    }
    rx_ConfigHRPD_internal_value = (rx_ConfigHRPD_Enum)packed_val;
    rx_ConfigHRPD_present = true;
    return 0;
}

IRAT_ParametersCDMA2000_HRPD::rx_ConfigHRPD_Enum IRAT_ParametersCDMA2000_HRPD::rx_ConfigHRPD_Value() const
{
    if(rx_ConfigHRPD_present)
        return rx_ConfigHRPD_internal_value;
    return (IRAT_ParametersCDMA2000_HRPD::rx_ConfigHRPD_Enum)0;
}

int IRAT_ParametersCDMA2000_HRPD::rx_ConfigHRPD_SetValue(rx_ConfigHRPD_Enum value)
{
    rx_ConfigHRPD_internal_value = value;
    rx_ConfigHRPD_present = true;
    return 0;
}

int IRAT_ParametersCDMA2000_HRPD::rx_ConfigHRPD_SetValue(std::string value)
{
    if("single" == value)
    {
        rx_ConfigHRPD_internal_value = k_rx_ConfigHRPD_single;
        rx_ConfigHRPD_present = true;
        return 0;
    }
    if("dual" == value)
    {
        rx_ConfigHRPD_internal_value = k_rx_ConfigHRPD_dual;
        rx_ConfigHRPD_present = true;
        return 0;
    }
    return 1;
}

std::string IRAT_ParametersCDMA2000_HRPD::rx_ConfigHRPD_ValueToString(rx_ConfigHRPD_Enum value) const
{
    if(k_rx_ConfigHRPD_single == value)
        return "single";
    if(k_rx_ConfigHRPD_dual == value)
        return "dual";
    return "";
}

uint64_t IRAT_ParametersCDMA2000_HRPD::rx_ConfigHRPD_NumberOfValues() const
{
    return 2;
}

std::string IRAT_ParametersCDMA2000_HRPD::rx_ConfigHRPD_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "rx_ConfigHRPD = " + rx_ConfigHRPD_ValueToString(rx_ConfigHRPD_internal_value) + "\n";
    return out;
}

std::string IRAT_ParametersCDMA2000_HRPD::rx_ConfigHRPD_ToStringNoNewLines() const
{
    std::string out = "rx_ConfigHRPD=" + rx_ConfigHRPD_ValueToString(rx_ConfigHRPD_internal_value) + ",";
    return out;
}

int IRAT_ParametersCDMA2000_HRPD::rx_ConfigHRPD_Clear()
{
    rx_ConfigHRPD_present = false;
    return 0;
}

bool IRAT_ParametersCDMA2000_HRPD::rx_ConfigHRPD_IsPresent() const
{
    return rx_ConfigHRPD_present;
}

