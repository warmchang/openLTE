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

#include "HandoverFromEUTRAPreparationRequest_r10_IEs.h"

#include <cmath>

int HandoverFromEUTRAPreparationRequest_r10_IEs::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(dualRxTxRedirectIndicator_r10_IsPresent());
    bits.push_back(redirectCarrierCDMA2000_1XRTT_r10_IsPresent());
    bits.push_back(0);

    // Fields
    if(dualRxTxRedirectIndicator_r10_IsPresent())
    {
        if(0 != dualRxTxRedirectIndicator_r10_Pack(bits))
        {
            printf("HandoverFromEUTRAPreparationRequest_r10_IEs:: field pack failure\n");
            return -1;
        }
    }
    if(redirectCarrierCDMA2000_1XRTT_r10_IsPresent())
    {
        if(0 != redirectCarrierCDMA2000_1XRTT_r10.Pack(bits))
        {
            printf("HandoverFromEUTRAPreparationRequest_r10_IEs:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int HandoverFromEUTRAPreparationRequest_r10_IEs::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int HandoverFromEUTRAPreparationRequest_r10_IEs::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("HandoverFromEUTRAPreparationRequest_r10_IEs::Unpack() index out of bounds for optional indiator dualRxTxRedirectIndicator_r10\n");
        return -1;
    }
    dualRxTxRedirectIndicator_r10_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("HandoverFromEUTRAPreparationRequest_r10_IEs::Unpack() index out of bounds for optional indiator redirectCarrierCDMA2000_1XRTT_r10\n");
        return -1;
    }
    redirectCarrierCDMA2000_1XRTT_r10_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("HandoverFromEUTRAPreparationRequest_r10_IEs::Unpack() index out of bounds for optional indiator nonCriticalExtension\n");
        return -1;
    }
    idx++;

    // Fields
    if(dualRxTxRedirectIndicator_r10_present)
    {
        if(0 != dualRxTxRedirectIndicator_r10_Unpack(bits, idx))
        {
            printf("HandoverFromEUTRAPreparationRequest_r10_IEs:: field unpack failure\n");
            return -1;
        }
    }
    if(redirectCarrierCDMA2000_1XRTT_r10_present)
    {
        if(0 != redirectCarrierCDMA2000_1XRTT_r10.Unpack(bits, idx))
        {
            printf("HandoverFromEUTRAPreparationRequest_r10_IEs:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string HandoverFromEUTRAPreparationRequest_r10_IEs::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "HandoverFromEUTRAPreparationRequest_r10_IEs:\n";
    if(dualRxTxRedirectIndicator_r10_IsPresent())
        out += dualRxTxRedirectIndicator_r10_ToString(indent+1);
    if(redirectCarrierCDMA2000_1XRTT_r10_IsPresent())
        out += redirectCarrierCDMA2000_1XRTT_r10_ToString(indent+1);
    return out;
}

std::string HandoverFromEUTRAPreparationRequest_r10_IEs::ToStringNoNewLines() const
{
    std::string out = "HandoverFromEUTRAPreparationRequest_r10_IEs:";
    if(dualRxTxRedirectIndicator_r10_IsPresent())
        out += dualRxTxRedirectIndicator_r10_ToStringNoNewLines();
    if(redirectCarrierCDMA2000_1XRTT_r10_IsPresent())
        out += redirectCarrierCDMA2000_1XRTT_r10_ToStringNoNewLines();
    return out;
}

int HandoverFromEUTRAPreparationRequest_r10_IEs::dualRxTxRedirectIndicator_r10_Pack(std::vector<uint8_t> &bits)
{
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((dualRxTxRedirectIndicator_r10_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int HandoverFromEUTRAPreparationRequest_r10_IEs::dualRxTxRedirectIndicator_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return dualRxTxRedirectIndicator_r10_Unpack(bits, idx);
}

int HandoverFromEUTRAPreparationRequest_r10_IEs::dualRxTxRedirectIndicator_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("HandoverFromEUTRAPreparationRequest_r10_IEs::dualRxTxRedirectIndicator_r10_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 0)
    {
        printf("HandoverFromEUTRAPreparationRequest_r10_IEs::dualRxTxRedirectIndicator_r10_Unpack() max failure\n");
        return -1;
    }
    dualRxTxRedirectIndicator_r10_internal_value = (dualRxTxRedirectIndicator_r10_Enum)packed_val;
    dualRxTxRedirectIndicator_r10_present = true;
    return 0;
}

HandoverFromEUTRAPreparationRequest_r10_IEs::dualRxTxRedirectIndicator_r10_Enum HandoverFromEUTRAPreparationRequest_r10_IEs::dualRxTxRedirectIndicator_r10_Value() const
{
    if(dualRxTxRedirectIndicator_r10_present)
        return dualRxTxRedirectIndicator_r10_internal_value;
    return (HandoverFromEUTRAPreparationRequest_r10_IEs::dualRxTxRedirectIndicator_r10_Enum)0;
}

int HandoverFromEUTRAPreparationRequest_r10_IEs::dualRxTxRedirectIndicator_r10_SetValue(dualRxTxRedirectIndicator_r10_Enum value)
{
    dualRxTxRedirectIndicator_r10_internal_value = value;
    dualRxTxRedirectIndicator_r10_present = true;
    return 0;
}

int HandoverFromEUTRAPreparationRequest_r10_IEs::dualRxTxRedirectIndicator_r10_SetValue(std::string value)
{
    if("true" == value)
    {
        dualRxTxRedirectIndicator_r10_internal_value = k_dualRxTxRedirectIndicator_r10_true;
        dualRxTxRedirectIndicator_r10_present = true;
        return 0;
    }
    return 1;
}

std::string HandoverFromEUTRAPreparationRequest_r10_IEs::dualRxTxRedirectIndicator_r10_ValueToString(dualRxTxRedirectIndicator_r10_Enum value) const
{
    if(k_dualRxTxRedirectIndicator_r10_true == value)
        return "true";
    return "";
}

uint64_t HandoverFromEUTRAPreparationRequest_r10_IEs::dualRxTxRedirectIndicator_r10_NumberOfValues() const
{
    return 1;
}

std::string HandoverFromEUTRAPreparationRequest_r10_IEs::dualRxTxRedirectIndicator_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "dualRxTxRedirectIndicator_r10 = " + dualRxTxRedirectIndicator_r10_ValueToString(dualRxTxRedirectIndicator_r10_internal_value) + "\n";
    return out;
}

std::string HandoverFromEUTRAPreparationRequest_r10_IEs::dualRxTxRedirectIndicator_r10_ToStringNoNewLines() const
{
    std::string out = "dualRxTxRedirectIndicator_r10=" + dualRxTxRedirectIndicator_r10_ValueToString(dualRxTxRedirectIndicator_r10_internal_value) + ",";
    return out;
}

int HandoverFromEUTRAPreparationRequest_r10_IEs::dualRxTxRedirectIndicator_r10_Clear()
{
    dualRxTxRedirectIndicator_r10_present = false;
    return 0;
}

bool HandoverFromEUTRAPreparationRequest_r10_IEs::dualRxTxRedirectIndicator_r10_IsPresent() const
{
    return dualRxTxRedirectIndicator_r10_present;
}

CarrierFreqCDMA2000* HandoverFromEUTRAPreparationRequest_r10_IEs::redirectCarrierCDMA2000_1XRTT_r10_Set()
{
    redirectCarrierCDMA2000_1XRTT_r10_present = true;
    return &redirectCarrierCDMA2000_1XRTT_r10;
}

int HandoverFromEUTRAPreparationRequest_r10_IEs::redirectCarrierCDMA2000_1XRTT_r10_Set(CarrierFreqCDMA2000 &value)
{
    redirectCarrierCDMA2000_1XRTT_r10_present = true;
    redirectCarrierCDMA2000_1XRTT_r10 = value;
    return 0;
}

const CarrierFreqCDMA2000& HandoverFromEUTRAPreparationRequest_r10_IEs::redirectCarrierCDMA2000_1XRTT_r10_Get() const
{
    return redirectCarrierCDMA2000_1XRTT_r10;
}

std::string HandoverFromEUTRAPreparationRequest_r10_IEs::redirectCarrierCDMA2000_1XRTT_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "redirectCarrierCDMA2000_1XRTT_r10:\n";
    out += redirectCarrierCDMA2000_1XRTT_r10.ToString(indent+1);
    return out;
}

std::string HandoverFromEUTRAPreparationRequest_r10_IEs::redirectCarrierCDMA2000_1XRTT_r10_ToStringNoNewLines() const
{
    std::string out = "redirectCarrierCDMA2000_1XRTT_r10:";
    out += redirectCarrierCDMA2000_1XRTT_r10.ToStringNoNewLines();
    return out;
}

int HandoverFromEUTRAPreparationRequest_r10_IEs::redirectCarrierCDMA2000_1XRTT_r10_Clear()
{
    redirectCarrierCDMA2000_1XRTT_r10_present = false;
    return 0;
}

bool HandoverFromEUTRAPreparationRequest_r10_IEs::redirectCarrierCDMA2000_1XRTT_r10_IsPresent() const
{
    return redirectCarrierCDMA2000_1XRTT_r10_present;
}

