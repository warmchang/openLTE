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

#include "MBSFN_AreaInfo_r9.h"

#include <cmath>

int MBSFN_AreaInfo_r9::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator
    bits.push_back(0);

    // Optional indicators

    // Fields
    {
        if(0 != mbsfn_AreaId_r9_Pack(bits))
        {
            printf("MBSFN_AreaInfo_r9:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != non_MBSFNregionLength_Pack(bits))
        {
            printf("MBSFN_AreaInfo_r9:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != notificationIndicator_r9_Pack(bits))
        {
            printf("MBSFN_AreaInfo_r9:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != mcch_Config_r9_value.Pack(bits))
        {
            printf("MBSFN_AreaInfo_r9:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int MBSFN_AreaInfo_r9::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int MBSFN_AreaInfo_r9::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("MBSFN_AreaInfo_r9::Unpack() index out of bounds for extension\n");
        return -1;
    }
    idx++;

    // Optional indicators

    // Fields
    {
        if(0 != mbsfn_AreaId_r9_Unpack(bits, idx))
        {
            printf("MBSFN_AreaInfo_r9:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != non_MBSFNregionLength_Unpack(bits, idx))
        {
            printf("MBSFN_AreaInfo_r9:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != notificationIndicator_r9_Unpack(bits, idx))
        {
            printf("MBSFN_AreaInfo_r9:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != mcch_Config_r9_value.Unpack(bits, idx))
        {
            printf("MBSFN_AreaInfo_r9:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string MBSFN_AreaInfo_r9::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "MBSFN_AreaInfo_r9:\n";
    out += mbsfn_AreaId_r9_ToString(indent+1);
    out += non_MBSFNregionLength_ToString(indent+1);
    out += notificationIndicator_r9_ToString(indent+1);
    out += mcch_Config_r9_value.ToString(indent+1);
    return out;
}

std::string MBSFN_AreaInfo_r9::ToStringNoNewLines() const
{
    std::string out = "MBSFN_AreaInfo_r9:";
    out += mbsfn_AreaId_r9_ToStringNoNewLines();
    out += non_MBSFNregionLength_ToStringNoNewLines();
    out += notificationIndicator_r9_ToStringNoNewLines();
    out += mcch_Config_r9_value.ToStringNoNewLines();
    return out;
}

int MBSFN_AreaInfo_r9::mbsfn_AreaId_r9_Pack(std::vector<uint8_t> &bits)
{
    if(!mbsfn_AreaId_r9_present)
    {
        printf("MBSFN_AreaInfo_r9::mbsfn_AreaId_r9_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = mbsfn_AreaId_r9_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (255 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int MBSFN_AreaInfo_r9::mbsfn_AreaId_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return mbsfn_AreaId_r9_Unpack(bits, idx);
}

int MBSFN_AreaInfo_r9::mbsfn_AreaId_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (255 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("MBSFN_AreaInfo_r9::mbsfn_AreaId_r9_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    mbsfn_AreaId_r9_internal_value = packed_val + 0;
    mbsfn_AreaId_r9_present = true;
    return 0;
}

int64_t MBSFN_AreaInfo_r9::mbsfn_AreaId_r9_Value() const
{
    if(mbsfn_AreaId_r9_present)
        return mbsfn_AreaId_r9_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int MBSFN_AreaInfo_r9::mbsfn_AreaId_r9_SetValue(int64_t value)
{
    if(value < 0 || value > 255)
    {
        printf("MBSFN_AreaInfo_r9::mbsfn_AreaId_r9_SetValue() range failure\n");
        return -1;
    }
    mbsfn_AreaId_r9_internal_value = value;
    mbsfn_AreaId_r9_present = true;
    return 0;
}

std::string MBSFN_AreaInfo_r9::mbsfn_AreaId_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "mbsfn_AreaId_r9 = " + std::to_string(mbsfn_AreaId_r9_internal_value) + "\n";
    return out;
}

std::string MBSFN_AreaInfo_r9::mbsfn_AreaId_r9_ToStringNoNewLines() const
{
    std::string out = "mbsfn_AreaId_r9=" + std::to_string(mbsfn_AreaId_r9_internal_value) + ",";
    return out;
}

int MBSFN_AreaInfo_r9::mbsfn_AreaId_r9_Clear()
{
    mbsfn_AreaId_r9_present = false;
    return 0;
}

bool MBSFN_AreaInfo_r9::mbsfn_AreaId_r9_IsPresent() const
{
    return mbsfn_AreaId_r9_present;
}

int MBSFN_AreaInfo_r9::non_MBSFNregionLength_Pack(std::vector<uint8_t> &bits)
{
    if(!non_MBSFNregionLength_present)
    {
        printf("MBSFN_AreaInfo_r9::non_MBSFNregionLength_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((non_MBSFNregionLength_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int MBSFN_AreaInfo_r9::non_MBSFNregionLength_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return non_MBSFNregionLength_Unpack(bits, idx);
}

int MBSFN_AreaInfo_r9::non_MBSFNregionLength_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("MBSFN_AreaInfo_r9::non_MBSFNregionLength_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 1)
    {
        printf("MBSFN_AreaInfo_r9::non_MBSFNregionLength_Unpack() max failure\n");
        return -1;
    }
    non_MBSFNregionLength_internal_value = (non_MBSFNregionLength_Enum)packed_val;
    non_MBSFNregionLength_present = true;
    return 0;
}

MBSFN_AreaInfo_r9::non_MBSFNregionLength_Enum MBSFN_AreaInfo_r9::non_MBSFNregionLength_Value() const
{
    if(non_MBSFNregionLength_present)
        return non_MBSFNregionLength_internal_value;
    return (MBSFN_AreaInfo_r9::non_MBSFNregionLength_Enum)0;
}

int MBSFN_AreaInfo_r9::non_MBSFNregionLength_SetValue(non_MBSFNregionLength_Enum value)
{
    non_MBSFNregionLength_internal_value = value;
    non_MBSFNregionLength_present = true;
    return 0;
}

int MBSFN_AreaInfo_r9::non_MBSFNregionLength_SetValue(std::string value)
{
    if("s1" == value)
    {
        non_MBSFNregionLength_internal_value = k_non_MBSFNregionLength_s1;
        non_MBSFNregionLength_present = true;
        return 0;
    }
    if("s2" == value)
    {
        non_MBSFNregionLength_internal_value = k_non_MBSFNregionLength_s2;
        non_MBSFNregionLength_present = true;
        return 0;
    }
    return 1;
}

std::string MBSFN_AreaInfo_r9::non_MBSFNregionLength_ValueToString(non_MBSFNregionLength_Enum value) const
{
    if(k_non_MBSFNregionLength_s1 == value)
        return "s1";
    if(k_non_MBSFNregionLength_s2 == value)
        return "s2";
    return "";
}

uint64_t MBSFN_AreaInfo_r9::non_MBSFNregionLength_NumberOfValues() const
{
    return 2;
}

std::string MBSFN_AreaInfo_r9::non_MBSFNregionLength_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "non_MBSFNregionLength = " + non_MBSFNregionLength_ValueToString(non_MBSFNregionLength_internal_value) + "\n";
    return out;
}

std::string MBSFN_AreaInfo_r9::non_MBSFNregionLength_ToStringNoNewLines() const
{
    std::string out = "non_MBSFNregionLength=" + non_MBSFNregionLength_ValueToString(non_MBSFNregionLength_internal_value) + ",";
    return out;
}

int MBSFN_AreaInfo_r9::non_MBSFNregionLength_Clear()
{
    non_MBSFNregionLength_present = false;
    return 0;
}

bool MBSFN_AreaInfo_r9::non_MBSFNregionLength_IsPresent() const
{
    return non_MBSFNregionLength_present;
}

int MBSFN_AreaInfo_r9::notificationIndicator_r9_Pack(std::vector<uint8_t> &bits)
{
    if(!notificationIndicator_r9_present)
    {
        printf("MBSFN_AreaInfo_r9::notificationIndicator_r9_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = notificationIndicator_r9_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (7 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int MBSFN_AreaInfo_r9::notificationIndicator_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return notificationIndicator_r9_Unpack(bits, idx);
}

int MBSFN_AreaInfo_r9::notificationIndicator_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (7 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("MBSFN_AreaInfo_r9::notificationIndicator_r9_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    notificationIndicator_r9_internal_value = packed_val + 0;
    notificationIndicator_r9_present = true;
    return 0;
}

int64_t MBSFN_AreaInfo_r9::notificationIndicator_r9_Value() const
{
    if(notificationIndicator_r9_present)
        return notificationIndicator_r9_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int MBSFN_AreaInfo_r9::notificationIndicator_r9_SetValue(int64_t value)
{
    if(value < 0 || value > 7)
    {
        printf("MBSFN_AreaInfo_r9::notificationIndicator_r9_SetValue() range failure\n");
        return -1;
    }
    notificationIndicator_r9_internal_value = value;
    notificationIndicator_r9_present = true;
    return 0;
}

std::string MBSFN_AreaInfo_r9::notificationIndicator_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "notificationIndicator_r9 = " + std::to_string(notificationIndicator_r9_internal_value) + "\n";
    return out;
}

std::string MBSFN_AreaInfo_r9::notificationIndicator_r9_ToStringNoNewLines() const
{
    std::string out = "notificationIndicator_r9=" + std::to_string(notificationIndicator_r9_internal_value) + ",";
    return out;
}

int MBSFN_AreaInfo_r9::notificationIndicator_r9_Clear()
{
    notificationIndicator_r9_present = false;
    return 0;
}

bool MBSFN_AreaInfo_r9::notificationIndicator_r9_IsPresent() const
{
    return notificationIndicator_r9_present;
}

int MBSFN_AreaInfo_r9::mcch_Config_r9::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != mcch_RepetitionPeriod_r9_Pack(bits))
        {
            printf("MBSFN_AreaInfo_r9::mcch_Config_r9:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != mcch_Offset_r9_Pack(bits))
        {
            printf("MBSFN_AreaInfo_r9::mcch_Config_r9:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != mcch_ModificationPeriod_r9_Pack(bits))
        {
            printf("MBSFN_AreaInfo_r9::mcch_Config_r9:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != sf_AllocInfo_r9_Pack(bits))
        {
            printf("MBSFN_AreaInfo_r9::mcch_Config_r9:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != signallingMCS_r9_Pack(bits))
        {
            printf("MBSFN_AreaInfo_r9::mcch_Config_r9:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int MBSFN_AreaInfo_r9::mcch_Config_r9::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int MBSFN_AreaInfo_r9::mcch_Config_r9::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != mcch_RepetitionPeriod_r9_Unpack(bits, idx))
        {
            printf("MBSFN_AreaInfo_r9::mcch_Config_r9:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != mcch_Offset_r9_Unpack(bits, idx))
        {
            printf("MBSFN_AreaInfo_r9::mcch_Config_r9:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != mcch_ModificationPeriod_r9_Unpack(bits, idx))
        {
            printf("MBSFN_AreaInfo_r9::mcch_Config_r9:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != sf_AllocInfo_r9_Unpack(bits, idx))
        {
            printf("MBSFN_AreaInfo_r9::mcch_Config_r9:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != signallingMCS_r9_Unpack(bits, idx))
        {
            printf("MBSFN_AreaInfo_r9::mcch_Config_r9:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string MBSFN_AreaInfo_r9::mcch_Config_r9::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "mcch_Config_r9:\n";
    out += mcch_RepetitionPeriod_r9_ToString(indent+1);
    out += mcch_Offset_r9_ToString(indent+1);
    out += mcch_ModificationPeriod_r9_ToString(indent+1);
    out += sf_AllocInfo_r9_ToString(indent+1);
    out += signallingMCS_r9_ToString(indent+1);
    return out;
}

std::string MBSFN_AreaInfo_r9::mcch_Config_r9::ToStringNoNewLines() const
{
    std::string out = "mcch_Config_r9:";
    out += mcch_RepetitionPeriod_r9_ToStringNoNewLines();
    out += mcch_Offset_r9_ToStringNoNewLines();
    out += mcch_ModificationPeriod_r9_ToStringNoNewLines();
    out += sf_AllocInfo_r9_ToStringNoNewLines();
    out += signallingMCS_r9_ToStringNoNewLines();
    return out;
}

int MBSFN_AreaInfo_r9::mcch_Config_r9::mcch_RepetitionPeriod_r9_Pack(std::vector<uint8_t> &bits)
{
    if(!mcch_RepetitionPeriod_r9_present)
    {
        printf("MBSFN_AreaInfo_r9::mcch_Config_r9::mcch_RepetitionPeriod_r9_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 2;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((mcch_RepetitionPeriod_r9_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int MBSFN_AreaInfo_r9::mcch_Config_r9::mcch_RepetitionPeriod_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return mcch_RepetitionPeriod_r9_Unpack(bits, idx);
}

int MBSFN_AreaInfo_r9::mcch_Config_r9::mcch_RepetitionPeriod_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 2;
    if((idx + N_bits) > bits.size())
    {
        printf("MBSFN_AreaInfo_r9::mcch_Config_r9::mcch_RepetitionPeriod_r9_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 3)
    {
        printf("MBSFN_AreaInfo_r9::mcch_Config_r9::mcch_RepetitionPeriod_r9_Unpack() max failure\n");
        return -1;
    }
    mcch_RepetitionPeriod_r9_internal_value = (mcch_RepetitionPeriod_r9_Enum)packed_val;
    mcch_RepetitionPeriod_r9_present = true;
    return 0;
}

MBSFN_AreaInfo_r9::mcch_Config_r9::mcch_RepetitionPeriod_r9_Enum MBSFN_AreaInfo_r9::mcch_Config_r9::mcch_RepetitionPeriod_r9_Value() const
{
    if(mcch_RepetitionPeriod_r9_present)
        return mcch_RepetitionPeriod_r9_internal_value;
    return (MBSFN_AreaInfo_r9::mcch_Config_r9::mcch_RepetitionPeriod_r9_Enum)0;
}

int MBSFN_AreaInfo_r9::mcch_Config_r9::mcch_RepetitionPeriod_r9_SetValue(mcch_RepetitionPeriod_r9_Enum value)
{
    mcch_RepetitionPeriod_r9_internal_value = value;
    mcch_RepetitionPeriod_r9_present = true;
    return 0;
}

int MBSFN_AreaInfo_r9::mcch_Config_r9::mcch_RepetitionPeriod_r9_SetValue(std::string value)
{
    if("rf32" == value)
    {
        mcch_RepetitionPeriod_r9_internal_value = k_mcch_RepetitionPeriod_r9_rf32;
        mcch_RepetitionPeriod_r9_present = true;
        return 0;
    }
    if("rf64" == value)
    {
        mcch_RepetitionPeriod_r9_internal_value = k_mcch_RepetitionPeriod_r9_rf64;
        mcch_RepetitionPeriod_r9_present = true;
        return 0;
    }
    if("rf128" == value)
    {
        mcch_RepetitionPeriod_r9_internal_value = k_mcch_RepetitionPeriod_r9_rf128;
        mcch_RepetitionPeriod_r9_present = true;
        return 0;
    }
    if("rf256" == value)
    {
        mcch_RepetitionPeriod_r9_internal_value = k_mcch_RepetitionPeriod_r9_rf256;
        mcch_RepetitionPeriod_r9_present = true;
        return 0;
    }
    return 1;
}

std::string MBSFN_AreaInfo_r9::mcch_Config_r9::mcch_RepetitionPeriod_r9_ValueToString(mcch_RepetitionPeriod_r9_Enum value) const
{
    if(k_mcch_RepetitionPeriod_r9_rf32 == value)
        return "rf32";
    if(k_mcch_RepetitionPeriod_r9_rf64 == value)
        return "rf64";
    if(k_mcch_RepetitionPeriod_r9_rf128 == value)
        return "rf128";
    if(k_mcch_RepetitionPeriod_r9_rf256 == value)
        return "rf256";
    return "";
}

uint64_t MBSFN_AreaInfo_r9::mcch_Config_r9::mcch_RepetitionPeriod_r9_NumberOfValues() const
{
    return 4;
}

std::string MBSFN_AreaInfo_r9::mcch_Config_r9::mcch_RepetitionPeriod_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "mcch_RepetitionPeriod_r9 = " + mcch_RepetitionPeriod_r9_ValueToString(mcch_RepetitionPeriod_r9_internal_value) + "\n";
    return out;
}

std::string MBSFN_AreaInfo_r9::mcch_Config_r9::mcch_RepetitionPeriod_r9_ToStringNoNewLines() const
{
    std::string out = "mcch_RepetitionPeriod_r9=" + mcch_RepetitionPeriod_r9_ValueToString(mcch_RepetitionPeriod_r9_internal_value) + ",";
    return out;
}

int MBSFN_AreaInfo_r9::mcch_Config_r9::mcch_RepetitionPeriod_r9_Clear()
{
    mcch_RepetitionPeriod_r9_present = false;
    return 0;
}

bool MBSFN_AreaInfo_r9::mcch_Config_r9::mcch_RepetitionPeriod_r9_IsPresent() const
{
    return mcch_RepetitionPeriod_r9_present;
}

int MBSFN_AreaInfo_r9::mcch_Config_r9::mcch_Offset_r9_Pack(std::vector<uint8_t> &bits)
{
    if(!mcch_Offset_r9_present)
    {
        printf("MBSFN_AreaInfo_r9::mcch_Config_r9::mcch_Offset_r9_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = mcch_Offset_r9_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (10 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int MBSFN_AreaInfo_r9::mcch_Config_r9::mcch_Offset_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return mcch_Offset_r9_Unpack(bits, idx);
}

int MBSFN_AreaInfo_r9::mcch_Config_r9::mcch_Offset_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (10 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("MBSFN_AreaInfo_r9::mcch_Config_r9::mcch_Offset_r9_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    mcch_Offset_r9_internal_value = packed_val + 0;
    mcch_Offset_r9_present = true;
    return 0;
}

int64_t MBSFN_AreaInfo_r9::mcch_Config_r9::mcch_Offset_r9_Value() const
{
    if(mcch_Offset_r9_present)
        return mcch_Offset_r9_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int MBSFN_AreaInfo_r9::mcch_Config_r9::mcch_Offset_r9_SetValue(int64_t value)
{
    if(value < 0 || value > 10)
    {
        printf("MBSFN_AreaInfo_r9::mcch_Config_r9::mcch_Offset_r9_SetValue() range failure\n");
        return -1;
    }
    mcch_Offset_r9_internal_value = value;
    mcch_Offset_r9_present = true;
    return 0;
}

std::string MBSFN_AreaInfo_r9::mcch_Config_r9::mcch_Offset_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "mcch_Offset_r9 = " + std::to_string(mcch_Offset_r9_internal_value) + "\n";
    return out;
}

std::string MBSFN_AreaInfo_r9::mcch_Config_r9::mcch_Offset_r9_ToStringNoNewLines() const
{
    std::string out = "mcch_Offset_r9=" + std::to_string(mcch_Offset_r9_internal_value) + ",";
    return out;
}

int MBSFN_AreaInfo_r9::mcch_Config_r9::mcch_Offset_r9_Clear()
{
    mcch_Offset_r9_present = false;
    return 0;
}

bool MBSFN_AreaInfo_r9::mcch_Config_r9::mcch_Offset_r9_IsPresent() const
{
    return mcch_Offset_r9_present;
}

int MBSFN_AreaInfo_r9::mcch_Config_r9::mcch_ModificationPeriod_r9_Pack(std::vector<uint8_t> &bits)
{
    if(!mcch_ModificationPeriod_r9_present)
    {
        printf("MBSFN_AreaInfo_r9::mcch_Config_r9::mcch_ModificationPeriod_r9_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((mcch_ModificationPeriod_r9_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int MBSFN_AreaInfo_r9::mcch_Config_r9::mcch_ModificationPeriod_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return mcch_ModificationPeriod_r9_Unpack(bits, idx);
}

int MBSFN_AreaInfo_r9::mcch_Config_r9::mcch_ModificationPeriod_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("MBSFN_AreaInfo_r9::mcch_Config_r9::mcch_ModificationPeriod_r9_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 1)
    {
        printf("MBSFN_AreaInfo_r9::mcch_Config_r9::mcch_ModificationPeriod_r9_Unpack() max failure\n");
        return -1;
    }
    mcch_ModificationPeriod_r9_internal_value = (mcch_ModificationPeriod_r9_Enum)packed_val;
    mcch_ModificationPeriod_r9_present = true;
    return 0;
}

MBSFN_AreaInfo_r9::mcch_Config_r9::mcch_ModificationPeriod_r9_Enum MBSFN_AreaInfo_r9::mcch_Config_r9::mcch_ModificationPeriod_r9_Value() const
{
    if(mcch_ModificationPeriod_r9_present)
        return mcch_ModificationPeriod_r9_internal_value;
    return (MBSFN_AreaInfo_r9::mcch_Config_r9::mcch_ModificationPeriod_r9_Enum)0;
}

int MBSFN_AreaInfo_r9::mcch_Config_r9::mcch_ModificationPeriod_r9_SetValue(mcch_ModificationPeriod_r9_Enum value)
{
    mcch_ModificationPeriod_r9_internal_value = value;
    mcch_ModificationPeriod_r9_present = true;
    return 0;
}

int MBSFN_AreaInfo_r9::mcch_Config_r9::mcch_ModificationPeriod_r9_SetValue(std::string value)
{
    if("rf512" == value)
    {
        mcch_ModificationPeriod_r9_internal_value = k_mcch_ModificationPeriod_r9_rf512;
        mcch_ModificationPeriod_r9_present = true;
        return 0;
    }
    if("rf1024" == value)
    {
        mcch_ModificationPeriod_r9_internal_value = k_mcch_ModificationPeriod_r9_rf1024;
        mcch_ModificationPeriod_r9_present = true;
        return 0;
    }
    return 1;
}

std::string MBSFN_AreaInfo_r9::mcch_Config_r9::mcch_ModificationPeriod_r9_ValueToString(mcch_ModificationPeriod_r9_Enum value) const
{
    if(k_mcch_ModificationPeriod_r9_rf512 == value)
        return "rf512";
    if(k_mcch_ModificationPeriod_r9_rf1024 == value)
        return "rf1024";
    return "";
}

uint64_t MBSFN_AreaInfo_r9::mcch_Config_r9::mcch_ModificationPeriod_r9_NumberOfValues() const
{
    return 2;
}

std::string MBSFN_AreaInfo_r9::mcch_Config_r9::mcch_ModificationPeriod_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "mcch_ModificationPeriod_r9 = " + mcch_ModificationPeriod_r9_ValueToString(mcch_ModificationPeriod_r9_internal_value) + "\n";
    return out;
}

std::string MBSFN_AreaInfo_r9::mcch_Config_r9::mcch_ModificationPeriod_r9_ToStringNoNewLines() const
{
    std::string out = "mcch_ModificationPeriod_r9=" + mcch_ModificationPeriod_r9_ValueToString(mcch_ModificationPeriod_r9_internal_value) + ",";
    return out;
}

int MBSFN_AreaInfo_r9::mcch_Config_r9::mcch_ModificationPeriod_r9_Clear()
{
    mcch_ModificationPeriod_r9_present = false;
    return 0;
}

bool MBSFN_AreaInfo_r9::mcch_Config_r9::mcch_ModificationPeriod_r9_IsPresent() const
{
    return mcch_ModificationPeriod_r9_present;
}

int MBSFN_AreaInfo_r9::mcch_Config_r9::sf_AllocInfo_r9_Pack(std::vector<uint8_t> &bits)
{
    if(!sf_AllocInfo_r9_present)
    {
        printf("MBSFN_AreaInfo_r9::mcch_Config_r9::sf_AllocInfo_r9_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 6;
    if(size < 6 || size > 6)
    {
        printf("MBSFN_AreaInfo_r9::mcch_Config_r9::sf_AllocInfo_r9_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((sf_AllocInfo_r9_internal_value >> (6-i-1)) & 1);
    return 0;
}

int MBSFN_AreaInfo_r9::mcch_Config_r9::sf_AllocInfo_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return sf_AllocInfo_r9_Unpack(bits, idx);
}

int MBSFN_AreaInfo_r9::mcch_Config_r9::sf_AllocInfo_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 6;
    if(size < 6 || size > 6)
    {
        printf("MBSFN_AreaInfo_r9::mcch_Config_r9::sf_AllocInfo_r9_Unpack() size failure\n");
        return -1;
    }
    sf_AllocInfo_r9_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("MBSFN_AreaInfo_r9::mcch_Config_r9::sf_AllocInfo_r9_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        sf_AllocInfo_r9_internal_value |= (uint8_t)bits[idx++] << (uint8_t)(6-i-1);
    sf_AllocInfo_r9_present = true;
    return 0;
}

uint8_t MBSFN_AreaInfo_r9::mcch_Config_r9::sf_AllocInfo_r9_Value() const
{
    if(sf_AllocInfo_r9_present)
        return sf_AllocInfo_r9_internal_value;
    uint8_t tmp = 0;
    return tmp;
}

int MBSFN_AreaInfo_r9::mcch_Config_r9::sf_AllocInfo_r9_SetValue(uint8_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 6)
    {
        printf("MBSFN_AreaInfo_r9::mcch_Config_r9::sf_AllocInfo_r9_SetValue() size failure\n");
        return -1;
    }
    sf_AllocInfo_r9_internal_value = value;
    sf_AllocInfo_r9_present = true;
    return 0;
}

std::string MBSFN_AreaInfo_r9::mcch_Config_r9::sf_AllocInfo_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "sf_AllocInfo_r9 = ";
    out += std::to_string(sf_AllocInfo_r9_internal_value);
    out += "\n";
    return out;
}

std::string MBSFN_AreaInfo_r9::mcch_Config_r9::sf_AllocInfo_r9_ToStringNoNewLines() const
{
    std::string out = "sf_AllocInfo_r9=";
    out += std::to_string(sf_AllocInfo_r9_internal_value);
    out += ",";
    return out;
}

int MBSFN_AreaInfo_r9::mcch_Config_r9::sf_AllocInfo_r9_Clear()
{
    sf_AllocInfo_r9_present = false;
    return 0;
}

bool MBSFN_AreaInfo_r9::mcch_Config_r9::sf_AllocInfo_r9_IsPresent() const
{
    return sf_AllocInfo_r9_present;
}

int MBSFN_AreaInfo_r9::mcch_Config_r9::signallingMCS_r9_Pack(std::vector<uint8_t> &bits)
{
    if(!signallingMCS_r9_present)
    {
        printf("MBSFN_AreaInfo_r9::mcch_Config_r9::signallingMCS_r9_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 2;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((signallingMCS_r9_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int MBSFN_AreaInfo_r9::mcch_Config_r9::signallingMCS_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return signallingMCS_r9_Unpack(bits, idx);
}

int MBSFN_AreaInfo_r9::mcch_Config_r9::signallingMCS_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 2;
    if((idx + N_bits) > bits.size())
    {
        printf("MBSFN_AreaInfo_r9::mcch_Config_r9::signallingMCS_r9_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 3)
    {
        printf("MBSFN_AreaInfo_r9::mcch_Config_r9::signallingMCS_r9_Unpack() max failure\n");
        return -1;
    }
    signallingMCS_r9_internal_value = (signallingMCS_r9_Enum)packed_val;
    signallingMCS_r9_present = true;
    return 0;
}

MBSFN_AreaInfo_r9::mcch_Config_r9::signallingMCS_r9_Enum MBSFN_AreaInfo_r9::mcch_Config_r9::signallingMCS_r9_Value() const
{
    if(signallingMCS_r9_present)
        return signallingMCS_r9_internal_value;
    return (MBSFN_AreaInfo_r9::mcch_Config_r9::signallingMCS_r9_Enum)0;
}

int MBSFN_AreaInfo_r9::mcch_Config_r9::signallingMCS_r9_SetValue(signallingMCS_r9_Enum value)
{
    signallingMCS_r9_internal_value = value;
    signallingMCS_r9_present = true;
    return 0;
}

int MBSFN_AreaInfo_r9::mcch_Config_r9::signallingMCS_r9_SetValue(std::string value)
{
    if("n2" == value)
    {
        signallingMCS_r9_internal_value = k_signallingMCS_r9_n2;
        signallingMCS_r9_present = true;
        return 0;
    }
    if("n7" == value)
    {
        signallingMCS_r9_internal_value = k_signallingMCS_r9_n7;
        signallingMCS_r9_present = true;
        return 0;
    }
    if("n13" == value)
    {
        signallingMCS_r9_internal_value = k_signallingMCS_r9_n13;
        signallingMCS_r9_present = true;
        return 0;
    }
    if("n19" == value)
    {
        signallingMCS_r9_internal_value = k_signallingMCS_r9_n19;
        signallingMCS_r9_present = true;
        return 0;
    }
    return 1;
}

std::string MBSFN_AreaInfo_r9::mcch_Config_r9::signallingMCS_r9_ValueToString(signallingMCS_r9_Enum value) const
{
    if(k_signallingMCS_r9_n2 == value)
        return "n2";
    if(k_signallingMCS_r9_n7 == value)
        return "n7";
    if(k_signallingMCS_r9_n13 == value)
        return "n13";
    if(k_signallingMCS_r9_n19 == value)
        return "n19";
    return "";
}

uint64_t MBSFN_AreaInfo_r9::mcch_Config_r9::signallingMCS_r9_NumberOfValues() const
{
    return 4;
}

std::string MBSFN_AreaInfo_r9::mcch_Config_r9::signallingMCS_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "signallingMCS_r9 = " + signallingMCS_r9_ValueToString(signallingMCS_r9_internal_value) + "\n";
    return out;
}

std::string MBSFN_AreaInfo_r9::mcch_Config_r9::signallingMCS_r9_ToStringNoNewLines() const
{
    std::string out = "signallingMCS_r9=" + signallingMCS_r9_ValueToString(signallingMCS_r9_internal_value) + ",";
    return out;
}

int MBSFN_AreaInfo_r9::mcch_Config_r9::signallingMCS_r9_Clear()
{
    signallingMCS_r9_present = false;
    return 0;
}

bool MBSFN_AreaInfo_r9::mcch_Config_r9::signallingMCS_r9_IsPresent() const
{
    return signallingMCS_r9_present;
}

