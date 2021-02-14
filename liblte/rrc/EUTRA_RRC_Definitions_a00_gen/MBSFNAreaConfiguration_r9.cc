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

#include "MBSFNAreaConfiguration_r9.h"

#include <cmath>

int MBSFNAreaConfiguration_r9::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(nonCriticalExtension_IsPresent());

    // Fields
    {
        if(0 != commonSF_Alloc_r9.Pack(bits))
        {
            printf("MBSFNAreaConfiguration_r9:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != commonSF_AllocPeriod_r9_Pack(bits))
        {
            printf("MBSFNAreaConfiguration_r9:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != pmch_InfoList_r9.Pack(bits))
        {
            printf("MBSFNAreaConfiguration_r9:: field pack failure\n");
            return -1;
        }
    }
    if(nonCriticalExtension_IsPresent())
    {
        if(0 != nonCriticalExtension.Pack(bits))
        {
            printf("MBSFNAreaConfiguration_r9:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int MBSFNAreaConfiguration_r9::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int MBSFNAreaConfiguration_r9::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("MBSFNAreaConfiguration_r9::Unpack() index out of bounds for optional indiator nonCriticalExtension\n");
        return -1;
    }
    nonCriticalExtension_present = bits[idx++];

    // Fields
    {
        if(0 != commonSF_Alloc_r9.Unpack(bits, idx))
        {
            printf("MBSFNAreaConfiguration_r9:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != commonSF_AllocPeriod_r9_Unpack(bits, idx))
        {
            printf("MBSFNAreaConfiguration_r9:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != pmch_InfoList_r9.Unpack(bits, idx))
        {
            printf("MBSFNAreaConfiguration_r9:: field unpack failure\n");
            return -1;
        }
    }
    if(nonCriticalExtension_present)
    {
        if(0 != nonCriticalExtension.Unpack(bits, idx))
        {
            printf("MBSFNAreaConfiguration_r9:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string MBSFNAreaConfiguration_r9::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "MBSFNAreaConfiguration_r9:\n";
    out += commonSF_Alloc_r9_ToString(indent+1);
    out += commonSF_AllocPeriod_r9_ToString(indent+1);
    out += pmch_InfoList_r9_ToString(indent+1);
    if(nonCriticalExtension_IsPresent())
        out += nonCriticalExtension_ToString(indent+1);
    return out;
}

std::string MBSFNAreaConfiguration_r9::ToStringNoNewLines() const
{
    std::string out = "MBSFNAreaConfiguration_r9:";
    out += commonSF_Alloc_r9_ToStringNoNewLines();
    out += commonSF_AllocPeriod_r9_ToStringNoNewLines();
    out += pmch_InfoList_r9_ToStringNoNewLines();
    if(nonCriticalExtension_IsPresent())
        out += nonCriticalExtension_ToStringNoNewLines();
    return out;
}

CommonSF_AllocPatternList_r9* MBSFNAreaConfiguration_r9::commonSF_Alloc_r9_Set()
{
    commonSF_Alloc_r9_present = true;
    return &commonSF_Alloc_r9;
}

int MBSFNAreaConfiguration_r9::commonSF_Alloc_r9_Set(CommonSF_AllocPatternList_r9 &value)
{
    commonSF_Alloc_r9_present = true;
    commonSF_Alloc_r9 = value;
    return 0;
}

const CommonSF_AllocPatternList_r9& MBSFNAreaConfiguration_r9::commonSF_Alloc_r9_Get() const
{
    return commonSF_Alloc_r9;
}

std::string MBSFNAreaConfiguration_r9::commonSF_Alloc_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "commonSF_Alloc_r9:\n";
    out += commonSF_Alloc_r9.ToString(indent+1);
    return out;
}

std::string MBSFNAreaConfiguration_r9::commonSF_Alloc_r9_ToStringNoNewLines() const
{
    std::string out = "commonSF_Alloc_r9:";
    out += commonSF_Alloc_r9.ToStringNoNewLines();
    return out;
}

int MBSFNAreaConfiguration_r9::commonSF_Alloc_r9_Clear()
{
    commonSF_Alloc_r9_present = false;
    return 0;
}

bool MBSFNAreaConfiguration_r9::commonSF_Alloc_r9_IsPresent() const
{
    return commonSF_Alloc_r9_present;
}

int MBSFNAreaConfiguration_r9::commonSF_AllocPeriod_r9_Pack(std::vector<uint8_t> &bits)
{
    if(!commonSF_AllocPeriod_r9_present)
    {
        printf("MBSFNAreaConfiguration_r9::commonSF_AllocPeriod_r9_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 3;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((commonSF_AllocPeriod_r9_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int MBSFNAreaConfiguration_r9::commonSF_AllocPeriod_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return commonSF_AllocPeriod_r9_Unpack(bits, idx);
}

int MBSFNAreaConfiguration_r9::commonSF_AllocPeriod_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 3;
    if((idx + N_bits) > bits.size())
    {
        printf("MBSFNAreaConfiguration_r9::commonSF_AllocPeriod_r9_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 6)
    {
        printf("MBSFNAreaConfiguration_r9::commonSF_AllocPeriod_r9_Unpack() max failure\n");
        return -1;
    }
    commonSF_AllocPeriod_r9_internal_value = (commonSF_AllocPeriod_r9_Enum)packed_val;
    commonSF_AllocPeriod_r9_present = true;
    return 0;
}

MBSFNAreaConfiguration_r9::commonSF_AllocPeriod_r9_Enum MBSFNAreaConfiguration_r9::commonSF_AllocPeriod_r9_Value() const
{
    if(commonSF_AllocPeriod_r9_present)
        return commonSF_AllocPeriod_r9_internal_value;
    return (MBSFNAreaConfiguration_r9::commonSF_AllocPeriod_r9_Enum)0;
}

int MBSFNAreaConfiguration_r9::commonSF_AllocPeriod_r9_SetValue(commonSF_AllocPeriod_r9_Enum value)
{
    commonSF_AllocPeriod_r9_internal_value = value;
    commonSF_AllocPeriod_r9_present = true;
    return 0;
}

int MBSFNAreaConfiguration_r9::commonSF_AllocPeriod_r9_SetValue(std::string value)
{
    if("rf4" == value)
    {
        commonSF_AllocPeriod_r9_internal_value = k_commonSF_AllocPeriod_r9_rf4;
        commonSF_AllocPeriod_r9_present = true;
        return 0;
    }
    if("rf8" == value)
    {
        commonSF_AllocPeriod_r9_internal_value = k_commonSF_AllocPeriod_r9_rf8;
        commonSF_AllocPeriod_r9_present = true;
        return 0;
    }
    if("rf16" == value)
    {
        commonSF_AllocPeriod_r9_internal_value = k_commonSF_AllocPeriod_r9_rf16;
        commonSF_AllocPeriod_r9_present = true;
        return 0;
    }
    if("rf32" == value)
    {
        commonSF_AllocPeriod_r9_internal_value = k_commonSF_AllocPeriod_r9_rf32;
        commonSF_AllocPeriod_r9_present = true;
        return 0;
    }
    if("rf64" == value)
    {
        commonSF_AllocPeriod_r9_internal_value = k_commonSF_AllocPeriod_r9_rf64;
        commonSF_AllocPeriod_r9_present = true;
        return 0;
    }
    if("rf128" == value)
    {
        commonSF_AllocPeriod_r9_internal_value = k_commonSF_AllocPeriod_r9_rf128;
        commonSF_AllocPeriod_r9_present = true;
        return 0;
    }
    if("rf256" == value)
    {
        commonSF_AllocPeriod_r9_internal_value = k_commonSF_AllocPeriod_r9_rf256;
        commonSF_AllocPeriod_r9_present = true;
        return 0;
    }
    return 1;
}

std::string MBSFNAreaConfiguration_r9::commonSF_AllocPeriod_r9_ValueToString(commonSF_AllocPeriod_r9_Enum value) const
{
    if(k_commonSF_AllocPeriod_r9_rf4 == value)
        return "rf4";
    if(k_commonSF_AllocPeriod_r9_rf8 == value)
        return "rf8";
    if(k_commonSF_AllocPeriod_r9_rf16 == value)
        return "rf16";
    if(k_commonSF_AllocPeriod_r9_rf32 == value)
        return "rf32";
    if(k_commonSF_AllocPeriod_r9_rf64 == value)
        return "rf64";
    if(k_commonSF_AllocPeriod_r9_rf128 == value)
        return "rf128";
    if(k_commonSF_AllocPeriod_r9_rf256 == value)
        return "rf256";
    return "";
}

uint64_t MBSFNAreaConfiguration_r9::commonSF_AllocPeriod_r9_NumberOfValues() const
{
    return 7;
}

std::string MBSFNAreaConfiguration_r9::commonSF_AllocPeriod_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "commonSF_AllocPeriod_r9 = " + commonSF_AllocPeriod_r9_ValueToString(commonSF_AllocPeriod_r9_internal_value) + "\n";
    return out;
}

std::string MBSFNAreaConfiguration_r9::commonSF_AllocPeriod_r9_ToStringNoNewLines() const
{
    std::string out = "commonSF_AllocPeriod_r9=" + commonSF_AllocPeriod_r9_ValueToString(commonSF_AllocPeriod_r9_internal_value) + ",";
    return out;
}

int MBSFNAreaConfiguration_r9::commonSF_AllocPeriod_r9_Clear()
{
    commonSF_AllocPeriod_r9_present = false;
    return 0;
}

bool MBSFNAreaConfiguration_r9::commonSF_AllocPeriod_r9_IsPresent() const
{
    return commonSF_AllocPeriod_r9_present;
}

PMCH_InfoList_r9* MBSFNAreaConfiguration_r9::pmch_InfoList_r9_Set()
{
    pmch_InfoList_r9_present = true;
    return &pmch_InfoList_r9;
}

int MBSFNAreaConfiguration_r9::pmch_InfoList_r9_Set(PMCH_InfoList_r9 &value)
{
    pmch_InfoList_r9_present = true;
    pmch_InfoList_r9 = value;
    return 0;
}

const PMCH_InfoList_r9& MBSFNAreaConfiguration_r9::pmch_InfoList_r9_Get() const
{
    return pmch_InfoList_r9;
}

std::string MBSFNAreaConfiguration_r9::pmch_InfoList_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "pmch_InfoList_r9:\n";
    out += pmch_InfoList_r9.ToString(indent+1);
    return out;
}

std::string MBSFNAreaConfiguration_r9::pmch_InfoList_r9_ToStringNoNewLines() const
{
    std::string out = "pmch_InfoList_r9:";
    out += pmch_InfoList_r9.ToStringNoNewLines();
    return out;
}

int MBSFNAreaConfiguration_r9::pmch_InfoList_r9_Clear()
{
    pmch_InfoList_r9_present = false;
    return 0;
}

bool MBSFNAreaConfiguration_r9::pmch_InfoList_r9_IsPresent() const
{
    return pmch_InfoList_r9_present;
}

MBSFNAreaConfiguration_v930_IEs* MBSFNAreaConfiguration_r9::nonCriticalExtension_Set()
{
    nonCriticalExtension_present = true;
    return &nonCriticalExtension;
}

int MBSFNAreaConfiguration_r9::nonCriticalExtension_Set(MBSFNAreaConfiguration_v930_IEs &value)
{
    nonCriticalExtension_present = true;
    nonCriticalExtension = value;
    return 0;
}

const MBSFNAreaConfiguration_v930_IEs& MBSFNAreaConfiguration_r9::nonCriticalExtension_Get() const
{
    return nonCriticalExtension;
}

std::string MBSFNAreaConfiguration_r9::nonCriticalExtension_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "nonCriticalExtension:\n";
    out += nonCriticalExtension.ToString(indent+1);
    return out;
}

std::string MBSFNAreaConfiguration_r9::nonCriticalExtension_ToStringNoNewLines() const
{
    std::string out = "nonCriticalExtension:";
    out += nonCriticalExtension.ToStringNoNewLines();
    return out;
}

int MBSFNAreaConfiguration_r9::nonCriticalExtension_Clear()
{
    nonCriticalExtension_present = false;
    return 0;
}

bool MBSFNAreaConfiguration_r9::nonCriticalExtension_IsPresent() const
{
    return nonCriticalExtension_present;
}

