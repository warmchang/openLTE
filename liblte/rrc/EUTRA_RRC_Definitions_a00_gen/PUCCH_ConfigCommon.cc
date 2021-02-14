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

#include "PUCCH_ConfigCommon.h"

#include <cmath>

int PUCCH_ConfigCommon::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != deltaPUCCH_Shift_Pack(bits))
        {
            printf("PUCCH_ConfigCommon:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != nRB_CQI_Pack(bits))
        {
            printf("PUCCH_ConfigCommon:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != nCS_AN_Pack(bits))
        {
            printf("PUCCH_ConfigCommon:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != n1PUCCH_AN_Pack(bits))
        {
            printf("PUCCH_ConfigCommon:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int PUCCH_ConfigCommon::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int PUCCH_ConfigCommon::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != deltaPUCCH_Shift_Unpack(bits, idx))
        {
            printf("PUCCH_ConfigCommon:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != nRB_CQI_Unpack(bits, idx))
        {
            printf("PUCCH_ConfigCommon:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != nCS_AN_Unpack(bits, idx))
        {
            printf("PUCCH_ConfigCommon:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != n1PUCCH_AN_Unpack(bits, idx))
        {
            printf("PUCCH_ConfigCommon:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string PUCCH_ConfigCommon::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "PUCCH_ConfigCommon:\n";
    out += deltaPUCCH_Shift_ToString(indent+1);
    out += nRB_CQI_ToString(indent+1);
    out += nCS_AN_ToString(indent+1);
    out += n1PUCCH_AN_ToString(indent+1);
    return out;
}

std::string PUCCH_ConfigCommon::ToStringNoNewLines() const
{
    std::string out = "PUCCH_ConfigCommon:";
    out += deltaPUCCH_Shift_ToStringNoNewLines();
    out += nRB_CQI_ToStringNoNewLines();
    out += nCS_AN_ToStringNoNewLines();
    out += n1PUCCH_AN_ToStringNoNewLines();
    return out;
}

int PUCCH_ConfigCommon::deltaPUCCH_Shift_Pack(std::vector<uint8_t> &bits)
{
    if(!deltaPUCCH_Shift_present)
    {
        printf("PUCCH_ConfigCommon::deltaPUCCH_Shift_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 2;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((deltaPUCCH_Shift_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int PUCCH_ConfigCommon::deltaPUCCH_Shift_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return deltaPUCCH_Shift_Unpack(bits, idx);
}

int PUCCH_ConfigCommon::deltaPUCCH_Shift_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 2;
    if((idx + N_bits) > bits.size())
    {
        printf("PUCCH_ConfigCommon::deltaPUCCH_Shift_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 2)
    {
        printf("PUCCH_ConfigCommon::deltaPUCCH_Shift_Unpack() max failure\n");
        return -1;
    }
    deltaPUCCH_Shift_internal_value = (deltaPUCCH_Shift_Enum)packed_val;
    deltaPUCCH_Shift_present = true;
    return 0;
}

PUCCH_ConfigCommon::deltaPUCCH_Shift_Enum PUCCH_ConfigCommon::deltaPUCCH_Shift_Value() const
{
    if(deltaPUCCH_Shift_present)
        return deltaPUCCH_Shift_internal_value;
    return (PUCCH_ConfigCommon::deltaPUCCH_Shift_Enum)0;
}

int PUCCH_ConfigCommon::deltaPUCCH_Shift_SetValue(deltaPUCCH_Shift_Enum value)
{
    deltaPUCCH_Shift_internal_value = value;
    deltaPUCCH_Shift_present = true;
    return 0;
}

int PUCCH_ConfigCommon::deltaPUCCH_Shift_SetValue(std::string value)
{
    if("ds1" == value)
    {
        deltaPUCCH_Shift_internal_value = k_deltaPUCCH_Shift_ds1;
        deltaPUCCH_Shift_present = true;
        return 0;
    }
    if("ds2" == value)
    {
        deltaPUCCH_Shift_internal_value = k_deltaPUCCH_Shift_ds2;
        deltaPUCCH_Shift_present = true;
        return 0;
    }
    if("ds3" == value)
    {
        deltaPUCCH_Shift_internal_value = k_deltaPUCCH_Shift_ds3;
        deltaPUCCH_Shift_present = true;
        return 0;
    }
    return 1;
}

std::string PUCCH_ConfigCommon::deltaPUCCH_Shift_ValueToString(deltaPUCCH_Shift_Enum value) const
{
    if(k_deltaPUCCH_Shift_ds1 == value)
        return "ds1";
    if(k_deltaPUCCH_Shift_ds2 == value)
        return "ds2";
    if(k_deltaPUCCH_Shift_ds3 == value)
        return "ds3";
    return "";
}

uint64_t PUCCH_ConfigCommon::deltaPUCCH_Shift_NumberOfValues() const
{
    return 3;
}

std::string PUCCH_ConfigCommon::deltaPUCCH_Shift_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "deltaPUCCH_Shift = " + deltaPUCCH_Shift_ValueToString(deltaPUCCH_Shift_internal_value) + "\n";
    return out;
}

std::string PUCCH_ConfigCommon::deltaPUCCH_Shift_ToStringNoNewLines() const
{
    std::string out = "deltaPUCCH_Shift=" + deltaPUCCH_Shift_ValueToString(deltaPUCCH_Shift_internal_value) + ",";
    return out;
}

int PUCCH_ConfigCommon::deltaPUCCH_Shift_Clear()
{
    deltaPUCCH_Shift_present = false;
    return 0;
}

bool PUCCH_ConfigCommon::deltaPUCCH_Shift_IsPresent() const
{
    return deltaPUCCH_Shift_present;
}

int PUCCH_ConfigCommon::nRB_CQI_Pack(std::vector<uint8_t> &bits)
{
    if(!nRB_CQI_present)
    {
        printf("PUCCH_ConfigCommon::nRB_CQI_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = nRB_CQI_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (98 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int PUCCH_ConfigCommon::nRB_CQI_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return nRB_CQI_Unpack(bits, idx);
}

int PUCCH_ConfigCommon::nRB_CQI_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (98 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("PUCCH_ConfigCommon::nRB_CQI_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    nRB_CQI_internal_value = packed_val + 0;
    nRB_CQI_present = true;
    return 0;
}

int64_t PUCCH_ConfigCommon::nRB_CQI_Value() const
{
    if(nRB_CQI_present)
        return nRB_CQI_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int PUCCH_ConfigCommon::nRB_CQI_SetValue(int64_t value)
{
    if(value < 0 || value > 98)
    {
        printf("PUCCH_ConfigCommon::nRB_CQI_SetValue() range failure\n");
        return -1;
    }
    nRB_CQI_internal_value = value;
    nRB_CQI_present = true;
    return 0;
}

std::string PUCCH_ConfigCommon::nRB_CQI_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "nRB_CQI = " + std::to_string(nRB_CQI_internal_value) + "\n";
    return out;
}

std::string PUCCH_ConfigCommon::nRB_CQI_ToStringNoNewLines() const
{
    std::string out = "nRB_CQI=" + std::to_string(nRB_CQI_internal_value) + ",";
    return out;
}

int PUCCH_ConfigCommon::nRB_CQI_Clear()
{
    nRB_CQI_present = false;
    return 0;
}

bool PUCCH_ConfigCommon::nRB_CQI_IsPresent() const
{
    return nRB_CQI_present;
}

int PUCCH_ConfigCommon::nCS_AN_Pack(std::vector<uint8_t> &bits)
{
    if(!nCS_AN_present)
    {
        printf("PUCCH_ConfigCommon::nCS_AN_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = nCS_AN_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (7 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int PUCCH_ConfigCommon::nCS_AN_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return nCS_AN_Unpack(bits, idx);
}

int PUCCH_ConfigCommon::nCS_AN_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (7 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("PUCCH_ConfigCommon::nCS_AN_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    nCS_AN_internal_value = packed_val + 0;
    nCS_AN_present = true;
    return 0;
}

int64_t PUCCH_ConfigCommon::nCS_AN_Value() const
{
    if(nCS_AN_present)
        return nCS_AN_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int PUCCH_ConfigCommon::nCS_AN_SetValue(int64_t value)
{
    if(value < 0 || value > 7)
    {
        printf("PUCCH_ConfigCommon::nCS_AN_SetValue() range failure\n");
        return -1;
    }
    nCS_AN_internal_value = value;
    nCS_AN_present = true;
    return 0;
}

std::string PUCCH_ConfigCommon::nCS_AN_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "nCS_AN = " + std::to_string(nCS_AN_internal_value) + "\n";
    return out;
}

std::string PUCCH_ConfigCommon::nCS_AN_ToStringNoNewLines() const
{
    std::string out = "nCS_AN=" + std::to_string(nCS_AN_internal_value) + ",";
    return out;
}

int PUCCH_ConfigCommon::nCS_AN_Clear()
{
    nCS_AN_present = false;
    return 0;
}

bool PUCCH_ConfigCommon::nCS_AN_IsPresent() const
{
    return nCS_AN_present;
}

int PUCCH_ConfigCommon::n1PUCCH_AN_Pack(std::vector<uint8_t> &bits)
{
    if(!n1PUCCH_AN_present)
    {
        printf("PUCCH_ConfigCommon::n1PUCCH_AN_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = n1PUCCH_AN_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (2047 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int PUCCH_ConfigCommon::n1PUCCH_AN_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return n1PUCCH_AN_Unpack(bits, idx);
}

int PUCCH_ConfigCommon::n1PUCCH_AN_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (2047 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("PUCCH_ConfigCommon::n1PUCCH_AN_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    n1PUCCH_AN_internal_value = packed_val + 0;
    n1PUCCH_AN_present = true;
    return 0;
}

int64_t PUCCH_ConfigCommon::n1PUCCH_AN_Value() const
{
    if(n1PUCCH_AN_present)
        return n1PUCCH_AN_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int PUCCH_ConfigCommon::n1PUCCH_AN_SetValue(int64_t value)
{
    if(value < 0 || value > 2047)
    {
        printf("PUCCH_ConfigCommon::n1PUCCH_AN_SetValue() range failure\n");
        return -1;
    }
    n1PUCCH_AN_internal_value = value;
    n1PUCCH_AN_present = true;
    return 0;
}

std::string PUCCH_ConfigCommon::n1PUCCH_AN_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "n1PUCCH_AN = " + std::to_string(n1PUCCH_AN_internal_value) + "\n";
    return out;
}

std::string PUCCH_ConfigCommon::n1PUCCH_AN_ToStringNoNewLines() const
{
    std::string out = "n1PUCCH_AN=" + std::to_string(n1PUCCH_AN_internal_value) + ",";
    return out;
}

int PUCCH_ConfigCommon::n1PUCCH_AN_Clear()
{
    n1PUCCH_AN_present = false;
    return 0;
}

bool PUCCH_ConfigCommon::n1PUCCH_AN_IsPresent() const
{
    return n1PUCCH_AN_present;
}

