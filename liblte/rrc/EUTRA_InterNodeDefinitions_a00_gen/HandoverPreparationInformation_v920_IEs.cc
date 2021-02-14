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

#include "HandoverPreparationInformation_v920_IEs.h"

#include <cmath>

int HandoverPreparationInformation_v920_IEs::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(ue_ConfigRelease_r9_IsPresent());
    bits.push_back(0);

    // Fields
    if(ue_ConfigRelease_r9_IsPresent())
    {
        if(0 != ue_ConfigRelease_r9_Pack(bits))
        {
            printf("HandoverPreparationInformation_v920_IEs:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int HandoverPreparationInformation_v920_IEs::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int HandoverPreparationInformation_v920_IEs::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("HandoverPreparationInformation_v920_IEs::Unpack() index out of bounds for optional indiator ue_ConfigRelease_r9\n");
        return -1;
    }
    ue_ConfigRelease_r9_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("HandoverPreparationInformation_v920_IEs::Unpack() index out of bounds for optional indiator nonCriticalExtension\n");
        return -1;
    }
    idx++;

    // Fields
    if(ue_ConfigRelease_r9_present)
    {
        if(0 != ue_ConfigRelease_r9_Unpack(bits, idx))
        {
            printf("HandoverPreparationInformation_v920_IEs:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string HandoverPreparationInformation_v920_IEs::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "HandoverPreparationInformation_v920_IEs:\n";
    if(ue_ConfigRelease_r9_IsPresent())
        out += ue_ConfigRelease_r9_ToString(indent+1);
    return out;
}

std::string HandoverPreparationInformation_v920_IEs::ToStringNoNewLines() const
{
    std::string out = "HandoverPreparationInformation_v920_IEs:";
    if(ue_ConfigRelease_r9_IsPresent())
        out += ue_ConfigRelease_r9_ToStringNoNewLines();
    return out;
}

int HandoverPreparationInformation_v920_IEs::ue_ConfigRelease_r9_Pack(std::vector<uint8_t> &bits)
{
    if(ue_ConfigRelease_r9_internal_value > k_ue_ConfigRelease_r9_spare1)
    {
        bits.push_back(1);
    }else{
        bits.push_back(0);
    }
    uint32_t N_bits = 3;
    if(ue_ConfigRelease_r9_internal_value > k_ue_ConfigRelease_r9_spare1)
        N_bits = 0;
    for(uint32_t i=0; i<N_bits; i++)
    {
        if(ue_ConfigRelease_r9_internal_value > k_ue_ConfigRelease_r9_spare1)
        {
            bits.push_back(((ue_ConfigRelease_r9_internal_value - k_ue_ConfigRelease_r9_spare1) >> (N_bits-1-i)) & 1);
        }else{
            bits.push_back((ue_ConfigRelease_r9_internal_value >> (N_bits-1-i)) & 1);
        }
    }
    return 0;
}

int HandoverPreparationInformation_v920_IEs::ue_ConfigRelease_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return ue_ConfigRelease_r9_Unpack(bits, idx);
}

int HandoverPreparationInformation_v920_IEs::ue_ConfigRelease_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    if((idx + 1) > bits.size())
    {
        printf("HandoverPreparationInformation_v920_IEs::ue_ConfigRelease_r9_Unpack() index out of bounds for extension\n");
        return -1;
    }
    bool has_extension = bits[idx++];
    uint32_t packed_val = 0;
    uint32_t N_bits = 3;
    if(has_extension)
        N_bits = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("HandoverPreparationInformation_v920_IEs::ue_ConfigRelease_r9_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(has_extension)
    {
        ue_ConfigRelease_r9_internal_value = (ue_ConfigRelease_r9_Enum)(packed_val + 8);
    }else{
        if(packed_val > 7)
        {
            printf("HandoverPreparationInformation_v920_IEs::ue_ConfigRelease_r9_Unpack() max failure\n");
            return -1;
        }
        ue_ConfigRelease_r9_internal_value = (ue_ConfigRelease_r9_Enum)packed_val;
    }
    ue_ConfigRelease_r9_present = true;
    return 0;
}

HandoverPreparationInformation_v920_IEs::ue_ConfigRelease_r9_Enum HandoverPreparationInformation_v920_IEs::ue_ConfigRelease_r9_Value() const
{
    if(ue_ConfigRelease_r9_present)
        return ue_ConfigRelease_r9_internal_value;
    return (HandoverPreparationInformation_v920_IEs::ue_ConfigRelease_r9_Enum)0;
}

int HandoverPreparationInformation_v920_IEs::ue_ConfigRelease_r9_SetValue(ue_ConfigRelease_r9_Enum value)
{
    ue_ConfigRelease_r9_internal_value = value;
    ue_ConfigRelease_r9_present = true;
    return 0;
}

int HandoverPreparationInformation_v920_IEs::ue_ConfigRelease_r9_SetValue(std::string value)
{
    if("rel9" == value)
    {
        ue_ConfigRelease_r9_internal_value = k_ue_ConfigRelease_r9_rel9;
        ue_ConfigRelease_r9_present = true;
        return 0;
    }
    if("spare7" == value)
    {
        ue_ConfigRelease_r9_internal_value = k_ue_ConfigRelease_r9_spare7;
        ue_ConfigRelease_r9_present = true;
        return 0;
    }
    if("spare6" == value)
    {
        ue_ConfigRelease_r9_internal_value = k_ue_ConfigRelease_r9_spare6;
        ue_ConfigRelease_r9_present = true;
        return 0;
    }
    if("spare5" == value)
    {
        ue_ConfigRelease_r9_internal_value = k_ue_ConfigRelease_r9_spare5;
        ue_ConfigRelease_r9_present = true;
        return 0;
    }
    if("spare4" == value)
    {
        ue_ConfigRelease_r9_internal_value = k_ue_ConfigRelease_r9_spare4;
        ue_ConfigRelease_r9_present = true;
        return 0;
    }
    if("spare3" == value)
    {
        ue_ConfigRelease_r9_internal_value = k_ue_ConfigRelease_r9_spare3;
        ue_ConfigRelease_r9_present = true;
        return 0;
    }
    if("spare2" == value)
    {
        ue_ConfigRelease_r9_internal_value = k_ue_ConfigRelease_r9_spare2;
        ue_ConfigRelease_r9_present = true;
        return 0;
    }
    if("spare1" == value)
    {
        ue_ConfigRelease_r9_internal_value = k_ue_ConfigRelease_r9_spare1;
        ue_ConfigRelease_r9_present = true;
        return 0;
    }
    return 1;
}

std::string HandoverPreparationInformation_v920_IEs::ue_ConfigRelease_r9_ValueToString(ue_ConfigRelease_r9_Enum value) const
{
    if(k_ue_ConfigRelease_r9_rel9 == value)
        return "rel9";
    if(k_ue_ConfigRelease_r9_spare7 == value)
        return "spare7";
    if(k_ue_ConfigRelease_r9_spare6 == value)
        return "spare6";
    if(k_ue_ConfigRelease_r9_spare5 == value)
        return "spare5";
    if(k_ue_ConfigRelease_r9_spare4 == value)
        return "spare4";
    if(k_ue_ConfigRelease_r9_spare3 == value)
        return "spare3";
    if(k_ue_ConfigRelease_r9_spare2 == value)
        return "spare2";
    if(k_ue_ConfigRelease_r9_spare1 == value)
        return "spare1";
    return "";
}

uint64_t HandoverPreparationInformation_v920_IEs::ue_ConfigRelease_r9_NumberOfValues() const
{
    return 8;
}

std::string HandoverPreparationInformation_v920_IEs::ue_ConfigRelease_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ue_ConfigRelease_r9 = " + ue_ConfigRelease_r9_ValueToString(ue_ConfigRelease_r9_internal_value) + "\n";
    return out;
}

std::string HandoverPreparationInformation_v920_IEs::ue_ConfigRelease_r9_ToStringNoNewLines() const
{
    std::string out = "ue_ConfigRelease_r9=" + ue_ConfigRelease_r9_ValueToString(ue_ConfigRelease_r9_internal_value) + ",";
    return out;
}

int HandoverPreparationInformation_v920_IEs::ue_ConfigRelease_r9_Clear()
{
    ue_ConfigRelease_r9_present = false;
    return 0;
}

bool HandoverPreparationInformation_v920_IEs::ue_ConfigRelease_r9_IsPresent() const
{
    return ue_ConfigRelease_r9_present;
}

