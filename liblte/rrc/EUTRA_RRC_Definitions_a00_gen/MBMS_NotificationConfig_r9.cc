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

#include "MBMS_NotificationConfig_r9.h"

#include <cmath>

int MBMS_NotificationConfig_r9::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != notificationRepetitionCoeff_r9_Pack(bits))
        {
            printf("MBMS_NotificationConfig_r9:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != notificationOffset_r9_Pack(bits))
        {
            printf("MBMS_NotificationConfig_r9:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != notificationSF_Index_r9_Pack(bits))
        {
            printf("MBMS_NotificationConfig_r9:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int MBMS_NotificationConfig_r9::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int MBMS_NotificationConfig_r9::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != notificationRepetitionCoeff_r9_Unpack(bits, idx))
        {
            printf("MBMS_NotificationConfig_r9:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != notificationOffset_r9_Unpack(bits, idx))
        {
            printf("MBMS_NotificationConfig_r9:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != notificationSF_Index_r9_Unpack(bits, idx))
        {
            printf("MBMS_NotificationConfig_r9:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string MBMS_NotificationConfig_r9::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "MBMS_NotificationConfig_r9:\n";
    out += notificationRepetitionCoeff_r9_ToString(indent+1);
    out += notificationOffset_r9_ToString(indent+1);
    out += notificationSF_Index_r9_ToString(indent+1);
    return out;
}

std::string MBMS_NotificationConfig_r9::ToStringNoNewLines() const
{
    std::string out = "MBMS_NotificationConfig_r9:";
    out += notificationRepetitionCoeff_r9_ToStringNoNewLines();
    out += notificationOffset_r9_ToStringNoNewLines();
    out += notificationSF_Index_r9_ToStringNoNewLines();
    return out;
}

int MBMS_NotificationConfig_r9::notificationRepetitionCoeff_r9_Pack(std::vector<uint8_t> &bits)
{
    if(!notificationRepetitionCoeff_r9_present)
    {
        printf("MBMS_NotificationConfig_r9::notificationRepetitionCoeff_r9_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((notificationRepetitionCoeff_r9_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int MBMS_NotificationConfig_r9::notificationRepetitionCoeff_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return notificationRepetitionCoeff_r9_Unpack(bits, idx);
}

int MBMS_NotificationConfig_r9::notificationRepetitionCoeff_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("MBMS_NotificationConfig_r9::notificationRepetitionCoeff_r9_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 1)
    {
        printf("MBMS_NotificationConfig_r9::notificationRepetitionCoeff_r9_Unpack() max failure\n");
        return -1;
    }
    notificationRepetitionCoeff_r9_internal_value = (notificationRepetitionCoeff_r9_Enum)packed_val;
    notificationRepetitionCoeff_r9_present = true;
    return 0;
}

MBMS_NotificationConfig_r9::notificationRepetitionCoeff_r9_Enum MBMS_NotificationConfig_r9::notificationRepetitionCoeff_r9_Value() const
{
    if(notificationRepetitionCoeff_r9_present)
        return notificationRepetitionCoeff_r9_internal_value;
    return (MBMS_NotificationConfig_r9::notificationRepetitionCoeff_r9_Enum)0;
}

int MBMS_NotificationConfig_r9::notificationRepetitionCoeff_r9_SetValue(notificationRepetitionCoeff_r9_Enum value)
{
    notificationRepetitionCoeff_r9_internal_value = value;
    notificationRepetitionCoeff_r9_present = true;
    return 0;
}

int MBMS_NotificationConfig_r9::notificationRepetitionCoeff_r9_SetValue(std::string value)
{
    if("n2" == value)
    {
        notificationRepetitionCoeff_r9_internal_value = k_notificationRepetitionCoeff_r9_n2;
        notificationRepetitionCoeff_r9_present = true;
        return 0;
    }
    if("n4" == value)
    {
        notificationRepetitionCoeff_r9_internal_value = k_notificationRepetitionCoeff_r9_n4;
        notificationRepetitionCoeff_r9_present = true;
        return 0;
    }
    return 1;
}

std::string MBMS_NotificationConfig_r9::notificationRepetitionCoeff_r9_ValueToString(notificationRepetitionCoeff_r9_Enum value) const
{
    if(k_notificationRepetitionCoeff_r9_n2 == value)
        return "n2";
    if(k_notificationRepetitionCoeff_r9_n4 == value)
        return "n4";
    return "";
}

uint64_t MBMS_NotificationConfig_r9::notificationRepetitionCoeff_r9_NumberOfValues() const
{
    return 2;
}

std::string MBMS_NotificationConfig_r9::notificationRepetitionCoeff_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "notificationRepetitionCoeff_r9 = " + notificationRepetitionCoeff_r9_ValueToString(notificationRepetitionCoeff_r9_internal_value) + "\n";
    return out;
}

std::string MBMS_NotificationConfig_r9::notificationRepetitionCoeff_r9_ToStringNoNewLines() const
{
    std::string out = "notificationRepetitionCoeff_r9=" + notificationRepetitionCoeff_r9_ValueToString(notificationRepetitionCoeff_r9_internal_value) + ",";
    return out;
}

int MBMS_NotificationConfig_r9::notificationRepetitionCoeff_r9_Clear()
{
    notificationRepetitionCoeff_r9_present = false;
    return 0;
}

bool MBMS_NotificationConfig_r9::notificationRepetitionCoeff_r9_IsPresent() const
{
    return notificationRepetitionCoeff_r9_present;
}

int MBMS_NotificationConfig_r9::notificationOffset_r9_Pack(std::vector<uint8_t> &bits)
{
    if(!notificationOffset_r9_present)
    {
        printf("MBMS_NotificationConfig_r9::notificationOffset_r9_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = notificationOffset_r9_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (10 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int MBMS_NotificationConfig_r9::notificationOffset_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return notificationOffset_r9_Unpack(bits, idx);
}

int MBMS_NotificationConfig_r9::notificationOffset_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (10 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("MBMS_NotificationConfig_r9::notificationOffset_r9_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    notificationOffset_r9_internal_value = packed_val + 0;
    notificationOffset_r9_present = true;
    return 0;
}

int64_t MBMS_NotificationConfig_r9::notificationOffset_r9_Value() const
{
    if(notificationOffset_r9_present)
        return notificationOffset_r9_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int MBMS_NotificationConfig_r9::notificationOffset_r9_SetValue(int64_t value)
{
    if(value < 0 || value > 10)
    {
        printf("MBMS_NotificationConfig_r9::notificationOffset_r9_SetValue() range failure\n");
        return -1;
    }
    notificationOffset_r9_internal_value = value;
    notificationOffset_r9_present = true;
    return 0;
}

std::string MBMS_NotificationConfig_r9::notificationOffset_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "notificationOffset_r9 = " + std::to_string(notificationOffset_r9_internal_value) + "\n";
    return out;
}

std::string MBMS_NotificationConfig_r9::notificationOffset_r9_ToStringNoNewLines() const
{
    std::string out = "notificationOffset_r9=" + std::to_string(notificationOffset_r9_internal_value) + ",";
    return out;
}

int MBMS_NotificationConfig_r9::notificationOffset_r9_Clear()
{
    notificationOffset_r9_present = false;
    return 0;
}

bool MBMS_NotificationConfig_r9::notificationOffset_r9_IsPresent() const
{
    return notificationOffset_r9_present;
}

int MBMS_NotificationConfig_r9::notificationSF_Index_r9_Pack(std::vector<uint8_t> &bits)
{
    if(!notificationSF_Index_r9_present)
    {
        printf("MBMS_NotificationConfig_r9::notificationSF_Index_r9_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = notificationSF_Index_r9_internal_value - (1);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (6 - 1))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int MBMS_NotificationConfig_r9::notificationSF_Index_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return notificationSF_Index_r9_Unpack(bits, idx);
}

int MBMS_NotificationConfig_r9::notificationSF_Index_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (6 - 1))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("MBMS_NotificationConfig_r9::notificationSF_Index_r9_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    notificationSF_Index_r9_internal_value = packed_val + 1;
    notificationSF_Index_r9_present = true;
    return 0;
}

int64_t MBMS_NotificationConfig_r9::notificationSF_Index_r9_Value() const
{
    if(notificationSF_Index_r9_present)
        return notificationSF_Index_r9_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int MBMS_NotificationConfig_r9::notificationSF_Index_r9_SetValue(int64_t value)
{
    if(value < 1 || value > 6)
    {
        printf("MBMS_NotificationConfig_r9::notificationSF_Index_r9_SetValue() range failure\n");
        return -1;
    }
    notificationSF_Index_r9_internal_value = value;
    notificationSF_Index_r9_present = true;
    return 0;
}

std::string MBMS_NotificationConfig_r9::notificationSF_Index_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "notificationSF_Index_r9 = " + std::to_string(notificationSF_Index_r9_internal_value) + "\n";
    return out;
}

std::string MBMS_NotificationConfig_r9::notificationSF_Index_r9_ToStringNoNewLines() const
{
    std::string out = "notificationSF_Index_r9=" + std::to_string(notificationSF_Index_r9_internal_value) + ",";
    return out;
}

int MBMS_NotificationConfig_r9::notificationSF_Index_r9_Clear()
{
    notificationSF_Index_r9_present = false;
    return 0;
}

bool MBMS_NotificationConfig_r9::notificationSF_Index_r9_IsPresent() const
{
    return notificationSF_Index_r9_present;
}

