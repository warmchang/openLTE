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

#include "MobilityControlInfo.h"

#include <cmath>

int MobilityControlInfo::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator
    bits.push_back(0);

    // Optional indicators
    bits.push_back(carrierFreq_IsPresent());
    bits.push_back(carrierBandwidth_IsPresent());
    bits.push_back(additionalSpectrumEmission_IsPresent());
    bits.push_back(rach_ConfigDedicated_IsPresent());

    // Fields
    {
        if(0 != targetPhysCellId.Pack(bits))
        {
            printf("MobilityControlInfo:: field pack failure\n");
            return -1;
        }
    }
    if(carrierFreq_IsPresent())
    {
        if(0 != carrierFreq.Pack(bits))
        {
            printf("MobilityControlInfo:: field pack failure\n");
            return -1;
        }
    }
    if(carrierBandwidth_IsPresent())
    {
        if(0 != carrierBandwidth.Pack(bits))
        {
            printf("MobilityControlInfo:: field pack failure\n");
            return -1;
        }
    }
    if(additionalSpectrumEmission_IsPresent())
    {
        if(0 != additionalSpectrumEmission.Pack(bits))
        {
            printf("MobilityControlInfo:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != t304_Pack(bits))
        {
            printf("MobilityControlInfo:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != newUE_Identity.Pack(bits))
        {
            printf("MobilityControlInfo:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != radioResourceConfigCommon.Pack(bits))
        {
            printf("MobilityControlInfo:: field pack failure\n");
            return -1;
        }
    }
    if(rach_ConfigDedicated_IsPresent())
    {
        if(0 != rach_ConfigDedicated.Pack(bits))
        {
            printf("MobilityControlInfo:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int MobilityControlInfo::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int MobilityControlInfo::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("MobilityControlInfo::Unpack() index out of bounds for extension\n");
        return -1;
    }
    idx++;

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("MobilityControlInfo::Unpack() index out of bounds for optional indiator carrierFreq\n");
        return -1;
    }
    carrierFreq_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("MobilityControlInfo::Unpack() index out of bounds for optional indiator carrierBandwidth\n");
        return -1;
    }
    carrierBandwidth_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("MobilityControlInfo::Unpack() index out of bounds for optional indiator additionalSpectrumEmission\n");
        return -1;
    }
    additionalSpectrumEmission_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("MobilityControlInfo::Unpack() index out of bounds for optional indiator rach_ConfigDedicated\n");
        return -1;
    }
    rach_ConfigDedicated_present = bits[idx++];

    // Fields
    {
        if(0 != targetPhysCellId.Unpack(bits, idx))
        {
            printf("MobilityControlInfo:: field unpack failure\n");
            return -1;
        }
    }
    if(carrierFreq_present)
    {
        if(0 != carrierFreq.Unpack(bits, idx))
        {
            printf("MobilityControlInfo:: field unpack failure\n");
            return -1;
        }
    }
    if(carrierBandwidth_present)
    {
        if(0 != carrierBandwidth.Unpack(bits, idx))
        {
            printf("MobilityControlInfo:: field unpack failure\n");
            return -1;
        }
    }
    if(additionalSpectrumEmission_present)
    {
        if(0 != additionalSpectrumEmission.Unpack(bits, idx))
        {
            printf("MobilityControlInfo:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != t304_Unpack(bits, idx))
        {
            printf("MobilityControlInfo:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != newUE_Identity.Unpack(bits, idx))
        {
            printf("MobilityControlInfo:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != radioResourceConfigCommon.Unpack(bits, idx))
        {
            printf("MobilityControlInfo:: field unpack failure\n");
            return -1;
        }
    }
    if(rach_ConfigDedicated_present)
    {
        if(0 != rach_ConfigDedicated.Unpack(bits, idx))
        {
            printf("MobilityControlInfo:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string MobilityControlInfo::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "MobilityControlInfo:\n";
    out += targetPhysCellId_ToString(indent+1);
    if(carrierFreq_IsPresent())
        out += carrierFreq_ToString(indent+1);
    if(carrierBandwidth_IsPresent())
        out += carrierBandwidth_ToString(indent+1);
    if(additionalSpectrumEmission_IsPresent())
        out += additionalSpectrumEmission_ToString(indent+1);
    out += t304_ToString(indent+1);
    out += newUE_Identity_ToString(indent+1);
    out += radioResourceConfigCommon_ToString(indent+1);
    if(rach_ConfigDedicated_IsPresent())
        out += rach_ConfigDedicated_ToString(indent+1);
    return out;
}

std::string MobilityControlInfo::ToStringNoNewLines() const
{
    std::string out = "MobilityControlInfo:";
    out += targetPhysCellId_ToStringNoNewLines();
    if(carrierFreq_IsPresent())
        out += carrierFreq_ToStringNoNewLines();
    if(carrierBandwidth_IsPresent())
        out += carrierBandwidth_ToStringNoNewLines();
    if(additionalSpectrumEmission_IsPresent())
        out += additionalSpectrumEmission_ToStringNoNewLines();
    out += t304_ToStringNoNewLines();
    out += newUE_Identity_ToStringNoNewLines();
    out += radioResourceConfigCommon_ToStringNoNewLines();
    if(rach_ConfigDedicated_IsPresent())
        out += rach_ConfigDedicated_ToStringNoNewLines();
    return out;
}

PhysCellId* MobilityControlInfo::targetPhysCellId_Set()
{
    targetPhysCellId_present = true;
    return &targetPhysCellId;
}

int MobilityControlInfo::targetPhysCellId_Set(PhysCellId &value)
{
    targetPhysCellId_present = true;
    targetPhysCellId = value;
    return 0;
}

const PhysCellId& MobilityControlInfo::targetPhysCellId_Get() const
{
    return targetPhysCellId;
}

std::string MobilityControlInfo::targetPhysCellId_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "targetPhysCellId:\n";
    out += targetPhysCellId.ToString(indent+1);
    return out;
}

std::string MobilityControlInfo::targetPhysCellId_ToStringNoNewLines() const
{
    std::string out = "targetPhysCellId:";
    out += targetPhysCellId.ToStringNoNewLines();
    return out;
}

int MobilityControlInfo::targetPhysCellId_Clear()
{
    targetPhysCellId_present = false;
    return 0;
}

bool MobilityControlInfo::targetPhysCellId_IsPresent() const
{
    return targetPhysCellId_present;
}

CarrierFreqEUTRA* MobilityControlInfo::carrierFreq_Set()
{
    carrierFreq_present = true;
    return &carrierFreq;
}

int MobilityControlInfo::carrierFreq_Set(CarrierFreqEUTRA &value)
{
    carrierFreq_present = true;
    carrierFreq = value;
    return 0;
}

const CarrierFreqEUTRA& MobilityControlInfo::carrierFreq_Get() const
{
    return carrierFreq;
}

std::string MobilityControlInfo::carrierFreq_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "carrierFreq:\n";
    out += carrierFreq.ToString(indent+1);
    return out;
}

std::string MobilityControlInfo::carrierFreq_ToStringNoNewLines() const
{
    std::string out = "carrierFreq:";
    out += carrierFreq.ToStringNoNewLines();
    return out;
}

int MobilityControlInfo::carrierFreq_Clear()
{
    carrierFreq_present = false;
    return 0;
}

bool MobilityControlInfo::carrierFreq_IsPresent() const
{
    return carrierFreq_present;
}

CarrierBandwidthEUTRA* MobilityControlInfo::carrierBandwidth_Set()
{
    carrierBandwidth_present = true;
    return &carrierBandwidth;
}

int MobilityControlInfo::carrierBandwidth_Set(CarrierBandwidthEUTRA &value)
{
    carrierBandwidth_present = true;
    carrierBandwidth = value;
    return 0;
}

const CarrierBandwidthEUTRA& MobilityControlInfo::carrierBandwidth_Get() const
{
    return carrierBandwidth;
}

std::string MobilityControlInfo::carrierBandwidth_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "carrierBandwidth:\n";
    out += carrierBandwidth.ToString(indent+1);
    return out;
}

std::string MobilityControlInfo::carrierBandwidth_ToStringNoNewLines() const
{
    std::string out = "carrierBandwidth:";
    out += carrierBandwidth.ToStringNoNewLines();
    return out;
}

int MobilityControlInfo::carrierBandwidth_Clear()
{
    carrierBandwidth_present = false;
    return 0;
}

bool MobilityControlInfo::carrierBandwidth_IsPresent() const
{
    return carrierBandwidth_present;
}

AdditionalSpectrumEmission* MobilityControlInfo::additionalSpectrumEmission_Set()
{
    additionalSpectrumEmission_present = true;
    return &additionalSpectrumEmission;
}

int MobilityControlInfo::additionalSpectrumEmission_Set(AdditionalSpectrumEmission &value)
{
    additionalSpectrumEmission_present = true;
    additionalSpectrumEmission = value;
    return 0;
}

const AdditionalSpectrumEmission& MobilityControlInfo::additionalSpectrumEmission_Get() const
{
    return additionalSpectrumEmission;
}

std::string MobilityControlInfo::additionalSpectrumEmission_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "additionalSpectrumEmission:\n";
    out += additionalSpectrumEmission.ToString(indent+1);
    return out;
}

std::string MobilityControlInfo::additionalSpectrumEmission_ToStringNoNewLines() const
{
    std::string out = "additionalSpectrumEmission:";
    out += additionalSpectrumEmission.ToStringNoNewLines();
    return out;
}

int MobilityControlInfo::additionalSpectrumEmission_Clear()
{
    additionalSpectrumEmission_present = false;
    return 0;
}

bool MobilityControlInfo::additionalSpectrumEmission_IsPresent() const
{
    return additionalSpectrumEmission_present;
}

int MobilityControlInfo::t304_Pack(std::vector<uint8_t> &bits)
{
    if(!t304_present)
    {
        printf("MobilityControlInfo::t304_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 3;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((t304_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int MobilityControlInfo::t304_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return t304_Unpack(bits, idx);
}

int MobilityControlInfo::t304_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 3;
    if((idx + N_bits) > bits.size())
    {
        printf("MobilityControlInfo::t304_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 7)
    {
        printf("MobilityControlInfo::t304_Unpack() max failure\n");
        return -1;
    }
    t304_internal_value = (t304_Enum)packed_val;
    t304_present = true;
    return 0;
}

MobilityControlInfo::t304_Enum MobilityControlInfo::t304_Value() const
{
    if(t304_present)
        return t304_internal_value;
    return (MobilityControlInfo::t304_Enum)0;
}

int MobilityControlInfo::t304_SetValue(t304_Enum value)
{
    t304_internal_value = value;
    t304_present = true;
    return 0;
}

int MobilityControlInfo::t304_SetValue(std::string value)
{
    if("ms50" == value)
    {
        t304_internal_value = k_t304_ms50;
        t304_present = true;
        return 0;
    }
    if("ms100" == value)
    {
        t304_internal_value = k_t304_ms100;
        t304_present = true;
        return 0;
    }
    if("ms150" == value)
    {
        t304_internal_value = k_t304_ms150;
        t304_present = true;
        return 0;
    }
    if("ms200" == value)
    {
        t304_internal_value = k_t304_ms200;
        t304_present = true;
        return 0;
    }
    if("ms500" == value)
    {
        t304_internal_value = k_t304_ms500;
        t304_present = true;
        return 0;
    }
    if("ms1000" == value)
    {
        t304_internal_value = k_t304_ms1000;
        t304_present = true;
        return 0;
    }
    if("ms2000" == value)
    {
        t304_internal_value = k_t304_ms2000;
        t304_present = true;
        return 0;
    }
    if("spare1" == value)
    {
        t304_internal_value = k_t304_spare1;
        t304_present = true;
        return 0;
    }
    return 1;
}

std::string MobilityControlInfo::t304_ValueToString(t304_Enum value) const
{
    if(k_t304_ms50 == value)
        return "ms50";
    if(k_t304_ms100 == value)
        return "ms100";
    if(k_t304_ms150 == value)
        return "ms150";
    if(k_t304_ms200 == value)
        return "ms200";
    if(k_t304_ms500 == value)
        return "ms500";
    if(k_t304_ms1000 == value)
        return "ms1000";
    if(k_t304_ms2000 == value)
        return "ms2000";
    if(k_t304_spare1 == value)
        return "spare1";
    return "";
}

uint64_t MobilityControlInfo::t304_NumberOfValues() const
{
    return 8;
}

std::string MobilityControlInfo::t304_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "t304 = " + t304_ValueToString(t304_internal_value) + "\n";
    return out;
}

std::string MobilityControlInfo::t304_ToStringNoNewLines() const
{
    std::string out = "t304=" + t304_ValueToString(t304_internal_value) + ",";
    return out;
}

int MobilityControlInfo::t304_Clear()
{
    t304_present = false;
    return 0;
}

bool MobilityControlInfo::t304_IsPresent() const
{
    return t304_present;
}

C_RNTI* MobilityControlInfo::newUE_Identity_Set()
{
    newUE_Identity_present = true;
    return &newUE_Identity;
}

int MobilityControlInfo::newUE_Identity_Set(C_RNTI &value)
{
    newUE_Identity_present = true;
    newUE_Identity = value;
    return 0;
}

const C_RNTI& MobilityControlInfo::newUE_Identity_Get() const
{
    return newUE_Identity;
}

std::string MobilityControlInfo::newUE_Identity_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "newUE_Identity:\n";
    out += newUE_Identity.ToString(indent+1);
    return out;
}

std::string MobilityControlInfo::newUE_Identity_ToStringNoNewLines() const
{
    std::string out = "newUE_Identity:";
    out += newUE_Identity.ToStringNoNewLines();
    return out;
}

int MobilityControlInfo::newUE_Identity_Clear()
{
    newUE_Identity_present = false;
    return 0;
}

bool MobilityControlInfo::newUE_Identity_IsPresent() const
{
    return newUE_Identity_present;
}

RadioResourceConfigCommon* MobilityControlInfo::radioResourceConfigCommon_Set()
{
    radioResourceConfigCommon_present = true;
    return &radioResourceConfigCommon;
}

int MobilityControlInfo::radioResourceConfigCommon_Set(RadioResourceConfigCommon &value)
{
    radioResourceConfigCommon_present = true;
    radioResourceConfigCommon = value;
    return 0;
}

const RadioResourceConfigCommon& MobilityControlInfo::radioResourceConfigCommon_Get() const
{
    return radioResourceConfigCommon;
}

std::string MobilityControlInfo::radioResourceConfigCommon_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "radioResourceConfigCommon:\n";
    out += radioResourceConfigCommon.ToString(indent+1);
    return out;
}

std::string MobilityControlInfo::radioResourceConfigCommon_ToStringNoNewLines() const
{
    std::string out = "radioResourceConfigCommon:";
    out += radioResourceConfigCommon.ToStringNoNewLines();
    return out;
}

int MobilityControlInfo::radioResourceConfigCommon_Clear()
{
    radioResourceConfigCommon_present = false;
    return 0;
}

bool MobilityControlInfo::radioResourceConfigCommon_IsPresent() const
{
    return radioResourceConfigCommon_present;
}

RACH_ConfigDedicated* MobilityControlInfo::rach_ConfigDedicated_Set()
{
    rach_ConfigDedicated_present = true;
    return &rach_ConfigDedicated;
}

int MobilityControlInfo::rach_ConfigDedicated_Set(RACH_ConfigDedicated &value)
{
    rach_ConfigDedicated_present = true;
    rach_ConfigDedicated = value;
    return 0;
}

const RACH_ConfigDedicated& MobilityControlInfo::rach_ConfigDedicated_Get() const
{
    return rach_ConfigDedicated;
}

std::string MobilityControlInfo::rach_ConfigDedicated_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "rach_ConfigDedicated:\n";
    out += rach_ConfigDedicated.ToString(indent+1);
    return out;
}

std::string MobilityControlInfo::rach_ConfigDedicated_ToStringNoNewLines() const
{
    std::string out = "rach_ConfigDedicated:";
    out += rach_ConfigDedicated.ToStringNoNewLines();
    return out;
}

int MobilityControlInfo::rach_ConfigDedicated_Clear()
{
    rach_ConfigDedicated_present = false;
    return 0;
}

bool MobilityControlInfo::rach_ConfigDedicated_IsPresent() const
{
    return rach_ConfigDedicated_present;
}

