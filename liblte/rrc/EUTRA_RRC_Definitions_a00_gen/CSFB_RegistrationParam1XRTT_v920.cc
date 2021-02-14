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

#include "CSFB_RegistrationParam1XRTT_v920.h"

#include <cmath>

int CSFB_RegistrationParam1XRTT_v920::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != powerDownReg_r9_Pack(bits))
        {
            printf("CSFB_RegistrationParam1XRTT_v920:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int CSFB_RegistrationParam1XRTT_v920::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int CSFB_RegistrationParam1XRTT_v920::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != powerDownReg_r9_Unpack(bits, idx))
        {
            printf("CSFB_RegistrationParam1XRTT_v920:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string CSFB_RegistrationParam1XRTT_v920::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "CSFB_RegistrationParam1XRTT_v920:\n";
    out += powerDownReg_r9_ToString(indent+1);
    return out;
}

std::string CSFB_RegistrationParam1XRTT_v920::ToStringNoNewLines() const
{
    std::string out = "CSFB_RegistrationParam1XRTT_v920:";
    out += powerDownReg_r9_ToStringNoNewLines();
    return out;
}

int CSFB_RegistrationParam1XRTT_v920::powerDownReg_r9_Pack(std::vector<uint8_t> &bits)
{
    if(!powerDownReg_r9_present)
    {
        printf("CSFB_RegistrationParam1XRTT_v920::powerDownReg_r9_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((powerDownReg_r9_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int CSFB_RegistrationParam1XRTT_v920::powerDownReg_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return powerDownReg_r9_Unpack(bits, idx);
}

int CSFB_RegistrationParam1XRTT_v920::powerDownReg_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("CSFB_RegistrationParam1XRTT_v920::powerDownReg_r9_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 0)
    {
        printf("CSFB_RegistrationParam1XRTT_v920::powerDownReg_r9_Unpack() max failure\n");
        return -1;
    }
    powerDownReg_r9_internal_value = (powerDownReg_r9_Enum)packed_val;
    powerDownReg_r9_present = true;
    return 0;
}

CSFB_RegistrationParam1XRTT_v920::powerDownReg_r9_Enum CSFB_RegistrationParam1XRTT_v920::powerDownReg_r9_Value() const
{
    if(powerDownReg_r9_present)
        return powerDownReg_r9_internal_value;
    return (CSFB_RegistrationParam1XRTT_v920::powerDownReg_r9_Enum)0;
}

int CSFB_RegistrationParam1XRTT_v920::powerDownReg_r9_SetValue(powerDownReg_r9_Enum value)
{
    powerDownReg_r9_internal_value = value;
    powerDownReg_r9_present = true;
    return 0;
}

int CSFB_RegistrationParam1XRTT_v920::powerDownReg_r9_SetValue(std::string value)
{
    if("true" == value)
    {
        powerDownReg_r9_internal_value = k_powerDownReg_r9_true;
        powerDownReg_r9_present = true;
        return 0;
    }
    return 1;
}

std::string CSFB_RegistrationParam1XRTT_v920::powerDownReg_r9_ValueToString(powerDownReg_r9_Enum value) const
{
    if(k_powerDownReg_r9_true == value)
        return "true";
    return "";
}

uint64_t CSFB_RegistrationParam1XRTT_v920::powerDownReg_r9_NumberOfValues() const
{
    return 1;
}

std::string CSFB_RegistrationParam1XRTT_v920::powerDownReg_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "powerDownReg_r9 = " + powerDownReg_r9_ValueToString(powerDownReg_r9_internal_value) + "\n";
    return out;
}

std::string CSFB_RegistrationParam1XRTT_v920::powerDownReg_r9_ToStringNoNewLines() const
{
    std::string out = "powerDownReg_r9=" + powerDownReg_r9_ValueToString(powerDownReg_r9_internal_value) + ",";
    return out;
}

int CSFB_RegistrationParam1XRTT_v920::powerDownReg_r9_Clear()
{
    powerDownReg_r9_present = false;
    return 0;
}

bool CSFB_RegistrationParam1XRTT_v920::powerDownReg_r9_IsPresent() const
{
    return powerDownReg_r9_present;
}

