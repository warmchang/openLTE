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

#include "PUSCH_ConfigCommon.h"

#include <cmath>

int PUSCH_ConfigCommon::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != pusch_ConfigBasic_value.Pack(bits))
        {
            printf("PUSCH_ConfigCommon:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != ul_ReferenceSignalsPUSCH.Pack(bits))
        {
            printf("PUSCH_ConfigCommon:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int PUSCH_ConfigCommon::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int PUSCH_ConfigCommon::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != pusch_ConfigBasic_value.Unpack(bits, idx))
        {
            printf("PUSCH_ConfigCommon:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != ul_ReferenceSignalsPUSCH.Unpack(bits, idx))
        {
            printf("PUSCH_ConfigCommon:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string PUSCH_ConfigCommon::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "PUSCH_ConfigCommon:\n";
    out += pusch_ConfigBasic_value.ToString(indent+1);
    out += ul_ReferenceSignalsPUSCH_ToString(indent+1);
    return out;
}

std::string PUSCH_ConfigCommon::ToStringNoNewLines() const
{
    std::string out = "PUSCH_ConfigCommon:";
    out += pusch_ConfigBasic_value.ToStringNoNewLines();
    out += ul_ReferenceSignalsPUSCH_ToStringNoNewLines();
    return out;
}

int PUSCH_ConfigCommon::pusch_ConfigBasic::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != n_SB_Pack(bits))
        {
            printf("PUSCH_ConfigCommon::pusch_ConfigBasic:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != hoppingMode_Pack(bits))
        {
            printf("PUSCH_ConfigCommon::pusch_ConfigBasic:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != pusch_HoppingOffset_Pack(bits))
        {
            printf("PUSCH_ConfigCommon::pusch_ConfigBasic:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != enable64QAM_Pack(bits))
        {
            printf("PUSCH_ConfigCommon::pusch_ConfigBasic:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int PUSCH_ConfigCommon::pusch_ConfigBasic::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int PUSCH_ConfigCommon::pusch_ConfigBasic::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != n_SB_Unpack(bits, idx))
        {
            printf("PUSCH_ConfigCommon::pusch_ConfigBasic:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != hoppingMode_Unpack(bits, idx))
        {
            printf("PUSCH_ConfigCommon::pusch_ConfigBasic:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != pusch_HoppingOffset_Unpack(bits, idx))
        {
            printf("PUSCH_ConfigCommon::pusch_ConfigBasic:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != enable64QAM_Unpack(bits, idx))
        {
            printf("PUSCH_ConfigCommon::pusch_ConfigBasic:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string PUSCH_ConfigCommon::pusch_ConfigBasic::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "pusch_ConfigBasic:\n";
    out += n_SB_ToString(indent+1);
    out += hoppingMode_ToString(indent+1);
    out += pusch_HoppingOffset_ToString(indent+1);
    out += enable64QAM_ToString(indent+1);
    return out;
}

std::string PUSCH_ConfigCommon::pusch_ConfigBasic::ToStringNoNewLines() const
{
    std::string out = "pusch_ConfigBasic:";
    out += n_SB_ToStringNoNewLines();
    out += hoppingMode_ToStringNoNewLines();
    out += pusch_HoppingOffset_ToStringNoNewLines();
    out += enable64QAM_ToStringNoNewLines();
    return out;
}

int PUSCH_ConfigCommon::pusch_ConfigBasic::n_SB_Pack(std::vector<uint8_t> &bits)
{
    if(!n_SB_present)
    {
        printf("PUSCH_ConfigCommon::pusch_ConfigBasic::n_SB_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = n_SB_internal_value - (1);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (4 - 1))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int PUSCH_ConfigCommon::pusch_ConfigBasic::n_SB_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return n_SB_Unpack(bits, idx);
}

int PUSCH_ConfigCommon::pusch_ConfigBasic::n_SB_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (4 - 1))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("PUSCH_ConfigCommon::pusch_ConfigBasic::n_SB_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    n_SB_internal_value = packed_val + 1;
    n_SB_present = true;
    return 0;
}

int64_t PUSCH_ConfigCommon::pusch_ConfigBasic::n_SB_Value() const
{
    if(n_SB_present)
        return n_SB_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int PUSCH_ConfigCommon::pusch_ConfigBasic::n_SB_SetValue(int64_t value)
{
    if(value < 1 || value > 4)
    {
        printf("PUSCH_ConfigCommon::pusch_ConfigBasic::n_SB_SetValue() range failure\n");
        return -1;
    }
    n_SB_internal_value = value;
    n_SB_present = true;
    return 0;
}

std::string PUSCH_ConfigCommon::pusch_ConfigBasic::n_SB_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "n_SB = " + std::to_string(n_SB_internal_value) + "\n";
    return out;
}

std::string PUSCH_ConfigCommon::pusch_ConfigBasic::n_SB_ToStringNoNewLines() const
{
    std::string out = "n_SB=" + std::to_string(n_SB_internal_value) + ",";
    return out;
}

int PUSCH_ConfigCommon::pusch_ConfigBasic::n_SB_Clear()
{
    n_SB_present = false;
    return 0;
}

bool PUSCH_ConfigCommon::pusch_ConfigBasic::n_SB_IsPresent() const
{
    return n_SB_present;
}

int PUSCH_ConfigCommon::pusch_ConfigBasic::hoppingMode_Pack(std::vector<uint8_t> &bits)
{
    if(!hoppingMode_present)
    {
        printf("PUSCH_ConfigCommon::pusch_ConfigBasic::hoppingMode_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((hoppingMode_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int PUSCH_ConfigCommon::pusch_ConfigBasic::hoppingMode_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return hoppingMode_Unpack(bits, idx);
}

int PUSCH_ConfigCommon::pusch_ConfigBasic::hoppingMode_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("PUSCH_ConfigCommon::pusch_ConfigBasic::hoppingMode_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 1)
    {
        printf("PUSCH_ConfigCommon::pusch_ConfigBasic::hoppingMode_Unpack() max failure\n");
        return -1;
    }
    hoppingMode_internal_value = (hoppingMode_Enum)packed_val;
    hoppingMode_present = true;
    return 0;
}

PUSCH_ConfigCommon::pusch_ConfigBasic::hoppingMode_Enum PUSCH_ConfigCommon::pusch_ConfigBasic::hoppingMode_Value() const
{
    if(hoppingMode_present)
        return hoppingMode_internal_value;
    return (PUSCH_ConfigCommon::pusch_ConfigBasic::hoppingMode_Enum)0;
}

int PUSCH_ConfigCommon::pusch_ConfigBasic::hoppingMode_SetValue(hoppingMode_Enum value)
{
    hoppingMode_internal_value = value;
    hoppingMode_present = true;
    return 0;
}

int PUSCH_ConfigCommon::pusch_ConfigBasic::hoppingMode_SetValue(std::string value)
{
    if("interSubFrame" == value)
    {
        hoppingMode_internal_value = k_hoppingMode_interSubFrame;
        hoppingMode_present = true;
        return 0;
    }
    if("intraAndInterSubFrame" == value)
    {
        hoppingMode_internal_value = k_hoppingMode_intraAndInterSubFrame;
        hoppingMode_present = true;
        return 0;
    }
    return 1;
}

std::string PUSCH_ConfigCommon::pusch_ConfigBasic::hoppingMode_ValueToString(hoppingMode_Enum value) const
{
    if(k_hoppingMode_interSubFrame == value)
        return "interSubFrame";
    if(k_hoppingMode_intraAndInterSubFrame == value)
        return "intraAndInterSubFrame";
    return "";
}

uint64_t PUSCH_ConfigCommon::pusch_ConfigBasic::hoppingMode_NumberOfValues() const
{
    return 2;
}

std::string PUSCH_ConfigCommon::pusch_ConfigBasic::hoppingMode_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "hoppingMode = " + hoppingMode_ValueToString(hoppingMode_internal_value) + "\n";
    return out;
}

std::string PUSCH_ConfigCommon::pusch_ConfigBasic::hoppingMode_ToStringNoNewLines() const
{
    std::string out = "hoppingMode=" + hoppingMode_ValueToString(hoppingMode_internal_value) + ",";
    return out;
}

int PUSCH_ConfigCommon::pusch_ConfigBasic::hoppingMode_Clear()
{
    hoppingMode_present = false;
    return 0;
}

bool PUSCH_ConfigCommon::pusch_ConfigBasic::hoppingMode_IsPresent() const
{
    return hoppingMode_present;
}

int PUSCH_ConfigCommon::pusch_ConfigBasic::pusch_HoppingOffset_Pack(std::vector<uint8_t> &bits)
{
    if(!pusch_HoppingOffset_present)
    {
        printf("PUSCH_ConfigCommon::pusch_ConfigBasic::pusch_HoppingOffset_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = pusch_HoppingOffset_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (98 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int PUSCH_ConfigCommon::pusch_ConfigBasic::pusch_HoppingOffset_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return pusch_HoppingOffset_Unpack(bits, idx);
}

int PUSCH_ConfigCommon::pusch_ConfigBasic::pusch_HoppingOffset_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (98 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("PUSCH_ConfigCommon::pusch_ConfigBasic::pusch_HoppingOffset_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    pusch_HoppingOffset_internal_value = packed_val + 0;
    pusch_HoppingOffset_present = true;
    return 0;
}

int64_t PUSCH_ConfigCommon::pusch_ConfigBasic::pusch_HoppingOffset_Value() const
{
    if(pusch_HoppingOffset_present)
        return pusch_HoppingOffset_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int PUSCH_ConfigCommon::pusch_ConfigBasic::pusch_HoppingOffset_SetValue(int64_t value)
{
    if(value < 0 || value > 98)
    {
        printf("PUSCH_ConfigCommon::pusch_ConfigBasic::pusch_HoppingOffset_SetValue() range failure\n");
        return -1;
    }
    pusch_HoppingOffset_internal_value = value;
    pusch_HoppingOffset_present = true;
    return 0;
}

std::string PUSCH_ConfigCommon::pusch_ConfigBasic::pusch_HoppingOffset_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "pusch_HoppingOffset = " + std::to_string(pusch_HoppingOffset_internal_value) + "\n";
    return out;
}

std::string PUSCH_ConfigCommon::pusch_ConfigBasic::pusch_HoppingOffset_ToStringNoNewLines() const
{
    std::string out = "pusch_HoppingOffset=" + std::to_string(pusch_HoppingOffset_internal_value) + ",";
    return out;
}

int PUSCH_ConfigCommon::pusch_ConfigBasic::pusch_HoppingOffset_Clear()
{
    pusch_HoppingOffset_present = false;
    return 0;
}

bool PUSCH_ConfigCommon::pusch_ConfigBasic::pusch_HoppingOffset_IsPresent() const
{
    return pusch_HoppingOffset_present;
}

int PUSCH_ConfigCommon::pusch_ConfigBasic::enable64QAM_Pack(std::vector<uint8_t> &bits)
{
    if(!enable64QAM_present)
    {
        printf("PUSCH_ConfigCommon::pusch_ConfigBasic::enable64QAM_Pack() presence failure\n");
        return -1;
    }
    bits.push_back(enable64QAM_internal_value);
    return 0;
}

int PUSCH_ConfigCommon::pusch_ConfigBasic::enable64QAM_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return enable64QAM_Unpack(bits, idx);
}

int PUSCH_ConfigCommon::pusch_ConfigBasic::enable64QAM_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    if((idx + 1) > bits.size())
    {
        printf("PUSCH_ConfigCommon::pusch_ConfigBasic::enable64QAM_Unpack() index out of bounds\n");
        return -1;
    }
    enable64QAM_internal_value = bits[idx++];
    enable64QAM_present = true;
    return 0;
}

bool PUSCH_ConfigCommon::pusch_ConfigBasic::enable64QAM_Value() const
{
    if(enable64QAM_present)
        return enable64QAM_internal_value;
    return false;
}

int PUSCH_ConfigCommon::pusch_ConfigBasic::enable64QAM_SetValue(bool value)
{
    enable64QAM_internal_value = value;
    enable64QAM_present = true;
    return 0;
}

std::string PUSCH_ConfigCommon::pusch_ConfigBasic::enable64QAM_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "enable64QAM = " + std::to_string(enable64QAM_internal_value) + "\n";
    return out;
}

std::string PUSCH_ConfigCommon::pusch_ConfigBasic::enable64QAM_ToStringNoNewLines() const
{
    std::string out = "enable64QAM=" + std::to_string(enable64QAM_internal_value) + ",";
    return out;
}

int PUSCH_ConfigCommon::pusch_ConfigBasic::enable64QAM_Clear()
{
    enable64QAM_present = false;
    return 0;
}

bool PUSCH_ConfigCommon::pusch_ConfigBasic::enable64QAM_IsPresent() const
{
    return enable64QAM_present;
}

UL_ReferenceSignalsPUSCH* PUSCH_ConfigCommon::ul_ReferenceSignalsPUSCH_Set()
{
    ul_ReferenceSignalsPUSCH_present = true;
    return &ul_ReferenceSignalsPUSCH;
}

int PUSCH_ConfigCommon::ul_ReferenceSignalsPUSCH_Set(UL_ReferenceSignalsPUSCH &value)
{
    ul_ReferenceSignalsPUSCH_present = true;
    ul_ReferenceSignalsPUSCH = value;
    return 0;
}

const UL_ReferenceSignalsPUSCH& PUSCH_ConfigCommon::ul_ReferenceSignalsPUSCH_Get() const
{
    return ul_ReferenceSignalsPUSCH;
}

std::string PUSCH_ConfigCommon::ul_ReferenceSignalsPUSCH_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ul_ReferenceSignalsPUSCH:\n";
    out += ul_ReferenceSignalsPUSCH.ToString(indent+1);
    return out;
}

std::string PUSCH_ConfigCommon::ul_ReferenceSignalsPUSCH_ToStringNoNewLines() const
{
    std::string out = "ul_ReferenceSignalsPUSCH:";
    out += ul_ReferenceSignalsPUSCH.ToStringNoNewLines();
    return out;
}

int PUSCH_ConfigCommon::ul_ReferenceSignalsPUSCH_Clear()
{
    ul_ReferenceSignalsPUSCH_present = false;
    return 0;
}

bool PUSCH_ConfigCommon::ul_ReferenceSignalsPUSCH_IsPresent() const
{
    return ul_ReferenceSignalsPUSCH_present;
}

