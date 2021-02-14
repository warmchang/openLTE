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

#include "SoundingRS_UL_ConfigDedicated_v10x0.h"

#include <cmath>

int SoundingRS_UL_ConfigDedicated_v10x0::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != srs_AntennaPort_r10_Pack(bits))
        {
            printf("SoundingRS_UL_ConfigDedicated_v10x0:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int SoundingRS_UL_ConfigDedicated_v10x0::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int SoundingRS_UL_ConfigDedicated_v10x0::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != srs_AntennaPort_r10_Unpack(bits, idx))
        {
            printf("SoundingRS_UL_ConfigDedicated_v10x0:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string SoundingRS_UL_ConfigDedicated_v10x0::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "SoundingRS_UL_ConfigDedicated_v10x0:\n";
    out += srs_AntennaPort_r10_ToString(indent+1);
    return out;
}

std::string SoundingRS_UL_ConfigDedicated_v10x0::ToStringNoNewLines() const
{
    std::string out = "SoundingRS_UL_ConfigDedicated_v10x0:";
    out += srs_AntennaPort_r10_ToStringNoNewLines();
    return out;
}

int SoundingRS_UL_ConfigDedicated_v10x0::srs_AntennaPort_r10_Pack(std::vector<uint8_t> &bits)
{
    if(!srs_AntennaPort_r10_present)
    {
        printf("SoundingRS_UL_ConfigDedicated_v10x0::srs_AntennaPort_r10_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 2;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((srs_AntennaPort_r10_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int SoundingRS_UL_ConfigDedicated_v10x0::srs_AntennaPort_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return srs_AntennaPort_r10_Unpack(bits, idx);
}

int SoundingRS_UL_ConfigDedicated_v10x0::srs_AntennaPort_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 2;
    if((idx + N_bits) > bits.size())
    {
        printf("SoundingRS_UL_ConfigDedicated_v10x0::srs_AntennaPort_r10_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 3)
    {
        printf("SoundingRS_UL_ConfigDedicated_v10x0::srs_AntennaPort_r10_Unpack() max failure\n");
        return -1;
    }
    srs_AntennaPort_r10_internal_value = (srs_AntennaPort_r10_Enum)packed_val;
    srs_AntennaPort_r10_present = true;
    return 0;
}

SoundingRS_UL_ConfigDedicated_v10x0::srs_AntennaPort_r10_Enum SoundingRS_UL_ConfigDedicated_v10x0::srs_AntennaPort_r10_Value() const
{
    if(srs_AntennaPort_r10_present)
        return srs_AntennaPort_r10_internal_value;
    return (SoundingRS_UL_ConfigDedicated_v10x0::srs_AntennaPort_r10_Enum)0;
}

int SoundingRS_UL_ConfigDedicated_v10x0::srs_AntennaPort_r10_SetValue(srs_AntennaPort_r10_Enum value)
{
    srs_AntennaPort_r10_internal_value = value;
    srs_AntennaPort_r10_present = true;
    return 0;
}

int SoundingRS_UL_ConfigDedicated_v10x0::srs_AntennaPort_r10_SetValue(std::string value)
{
    if("an1" == value)
    {
        srs_AntennaPort_r10_internal_value = k_srs_AntennaPort_r10_an1;
        srs_AntennaPort_r10_present = true;
        return 0;
    }
    if("an2" == value)
    {
        srs_AntennaPort_r10_internal_value = k_srs_AntennaPort_r10_an2;
        srs_AntennaPort_r10_present = true;
        return 0;
    }
    if("an4" == value)
    {
        srs_AntennaPort_r10_internal_value = k_srs_AntennaPort_r10_an4;
        srs_AntennaPort_r10_present = true;
        return 0;
    }
    if("spare1" == value)
    {
        srs_AntennaPort_r10_internal_value = k_srs_AntennaPort_r10_spare1;
        srs_AntennaPort_r10_present = true;
        return 0;
    }
    return 1;
}

std::string SoundingRS_UL_ConfigDedicated_v10x0::srs_AntennaPort_r10_ValueToString(srs_AntennaPort_r10_Enum value) const
{
    if(k_srs_AntennaPort_r10_an1 == value)
        return "an1";
    if(k_srs_AntennaPort_r10_an2 == value)
        return "an2";
    if(k_srs_AntennaPort_r10_an4 == value)
        return "an4";
    if(k_srs_AntennaPort_r10_spare1 == value)
        return "spare1";
    return "";
}

uint64_t SoundingRS_UL_ConfigDedicated_v10x0::srs_AntennaPort_r10_NumberOfValues() const
{
    return 4;
}

std::string SoundingRS_UL_ConfigDedicated_v10x0::srs_AntennaPort_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "srs_AntennaPort_r10 = " + srs_AntennaPort_r10_ValueToString(srs_AntennaPort_r10_internal_value) + "\n";
    return out;
}

std::string SoundingRS_UL_ConfigDedicated_v10x0::srs_AntennaPort_r10_ToStringNoNewLines() const
{
    std::string out = "srs_AntennaPort_r10=" + srs_AntennaPort_r10_ValueToString(srs_AntennaPort_r10_internal_value) + ",";
    return out;
}

int SoundingRS_UL_ConfigDedicated_v10x0::srs_AntennaPort_r10_Clear()
{
    srs_AntennaPort_r10_present = false;
    return 0;
}

bool SoundingRS_UL_ConfigDedicated_v10x0::srs_AntennaPort_r10_IsPresent() const
{
    return srs_AntennaPort_r10_present;
}

