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

#include "RRCConnectionReconfiguration_r8_IEs.h"

#include <cmath>

int RRCConnectionReconfiguration_r8_IEs::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(measConfig_IsPresent());
    bits.push_back(mobilityControlInfo_IsPresent());
    bits.push_back(dedicatedInfoNASList_IsPresent());
    bits.push_back(radioResourceConfigDedicated_IsPresent());
    bits.push_back(securityConfigHO_IsPresent());
    bits.push_back(nonCriticalExtension_IsPresent());

    // Fields
    if(measConfig_IsPresent())
    {
        if(0 != measConfig.Pack(bits))
        {
            printf("RRCConnectionReconfiguration_r8_IEs:: field pack failure\n");
            return -1;
        }
    }
    if(mobilityControlInfo_IsPresent())
    {
        if(0 != mobilityControlInfo.Pack(bits))
        {
            printf("RRCConnectionReconfiguration_r8_IEs:: field pack failure\n");
            return -1;
        }
    }
    if(dedicatedInfoNASList_IsPresent())
    {
        if(0 != dedicatedInfoNASList_Pack(bits))
        {
            printf("RRCConnectionReconfiguration_r8_IEs:: field pack failure\n");
            return -1;
        }
    }
    if(radioResourceConfigDedicated_IsPresent())
    {
        if(0 != radioResourceConfigDedicated.Pack(bits))
        {
            printf("RRCConnectionReconfiguration_r8_IEs:: field pack failure\n");
            return -1;
        }
    }
    if(securityConfigHO_IsPresent())
    {
        if(0 != securityConfigHO.Pack(bits))
        {
            printf("RRCConnectionReconfiguration_r8_IEs:: field pack failure\n");
            return -1;
        }
    }
    if(nonCriticalExtension_IsPresent())
    {
        if(0 != nonCriticalExtension.Pack(bits))
        {
            printf("RRCConnectionReconfiguration_r8_IEs:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int RRCConnectionReconfiguration_r8_IEs::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int RRCConnectionReconfiguration_r8_IEs::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("RRCConnectionReconfiguration_r8_IEs::Unpack() index out of bounds for optional indiator measConfig\n");
        return -1;
    }
    measConfig_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("RRCConnectionReconfiguration_r8_IEs::Unpack() index out of bounds for optional indiator mobilityControlInfo\n");
        return -1;
    }
    mobilityControlInfo_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("RRCConnectionReconfiguration_r8_IEs::Unpack() index out of bounds for optional indiator dedicatedInfoNASList\n");
        return -1;
    }
    dedicatedInfoNASList_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("RRCConnectionReconfiguration_r8_IEs::Unpack() index out of bounds for optional indiator radioResourceConfigDedicated\n");
        return -1;
    }
    radioResourceConfigDedicated_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("RRCConnectionReconfiguration_r8_IEs::Unpack() index out of bounds for optional indiator securityConfigHO\n");
        return -1;
    }
    securityConfigHO_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("RRCConnectionReconfiguration_r8_IEs::Unpack() index out of bounds for optional indiator nonCriticalExtension\n");
        return -1;
    }
    nonCriticalExtension_present = bits[idx++];

    // Fields
    if(measConfig_present)
    {
        if(0 != measConfig.Unpack(bits, idx))
        {
            printf("RRCConnectionReconfiguration_r8_IEs:: field unpack failure\n");
            return -1;
        }
    }
    if(mobilityControlInfo_present)
    {
        if(0 != mobilityControlInfo.Unpack(bits, idx))
        {
            printf("RRCConnectionReconfiguration_r8_IEs:: field unpack failure\n");
            return -1;
        }
    }
    if(dedicatedInfoNASList_present)
    {
        if(0 != dedicatedInfoNASList_Unpack(bits, idx))
        {
            printf("RRCConnectionReconfiguration_r8_IEs:: field unpack failure\n");
            return -1;
        }
    }
    if(radioResourceConfigDedicated_present)
    {
        if(0 != radioResourceConfigDedicated.Unpack(bits, idx))
        {
            printf("RRCConnectionReconfiguration_r8_IEs:: field unpack failure\n");
            return -1;
        }
    }
    if(securityConfigHO_present)
    {
        if(0 != securityConfigHO.Unpack(bits, idx))
        {
            printf("RRCConnectionReconfiguration_r8_IEs:: field unpack failure\n");
            return -1;
        }
    }
    if(nonCriticalExtension_present)
    {
        if(0 != nonCriticalExtension.Unpack(bits, idx))
        {
            printf("RRCConnectionReconfiguration_r8_IEs:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string RRCConnectionReconfiguration_r8_IEs::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "RRCConnectionReconfiguration_r8_IEs:\n";
    if(measConfig_IsPresent())
        out += measConfig_ToString(indent+1);
    if(mobilityControlInfo_IsPresent())
        out += mobilityControlInfo_ToString(indent+1);
    if(dedicatedInfoNASList_IsPresent())
        out += dedicatedInfoNASList_ToString(indent+1);
    if(radioResourceConfigDedicated_IsPresent())
        out += radioResourceConfigDedicated_ToString(indent+1);
    if(securityConfigHO_IsPresent())
        out += securityConfigHO_ToString(indent+1);
    if(nonCriticalExtension_IsPresent())
        out += nonCriticalExtension_ToString(indent+1);
    return out;
}

std::string RRCConnectionReconfiguration_r8_IEs::ToStringNoNewLines() const
{
    std::string out = "RRCConnectionReconfiguration_r8_IEs:";
    if(measConfig_IsPresent())
        out += measConfig_ToStringNoNewLines();
    if(mobilityControlInfo_IsPresent())
        out += mobilityControlInfo_ToStringNoNewLines();
    if(dedicatedInfoNASList_IsPresent())
        out += dedicatedInfoNASList_ToStringNoNewLines();
    if(radioResourceConfigDedicated_IsPresent())
        out += radioResourceConfigDedicated_ToStringNoNewLines();
    if(securityConfigHO_IsPresent())
        out += securityConfigHO_ToStringNoNewLines();
    if(nonCriticalExtension_IsPresent())
        out += nonCriticalExtension_ToStringNoNewLines();
    return out;
}

MeasConfig* RRCConnectionReconfiguration_r8_IEs::measConfig_Set()
{
    measConfig_present = true;
    return &measConfig;
}

int RRCConnectionReconfiguration_r8_IEs::measConfig_Set(MeasConfig &value)
{
    measConfig_present = true;
    measConfig = value;
    return 0;
}

const MeasConfig& RRCConnectionReconfiguration_r8_IEs::measConfig_Get() const
{
    return measConfig;
}

std::string RRCConnectionReconfiguration_r8_IEs::measConfig_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "measConfig:\n";
    out += measConfig.ToString(indent+1);
    return out;
}

std::string RRCConnectionReconfiguration_r8_IEs::measConfig_ToStringNoNewLines() const
{
    std::string out = "measConfig:";
    out += measConfig.ToStringNoNewLines();
    return out;
}

int RRCConnectionReconfiguration_r8_IEs::measConfig_Clear()
{
    measConfig_present = false;
    return 0;
}

bool RRCConnectionReconfiguration_r8_IEs::measConfig_IsPresent() const
{
    return measConfig_present;
}

MobilityControlInfo* RRCConnectionReconfiguration_r8_IEs::mobilityControlInfo_Set()
{
    mobilityControlInfo_present = true;
    return &mobilityControlInfo;
}

int RRCConnectionReconfiguration_r8_IEs::mobilityControlInfo_Set(MobilityControlInfo &value)
{
    mobilityControlInfo_present = true;
    mobilityControlInfo = value;
    return 0;
}

const MobilityControlInfo& RRCConnectionReconfiguration_r8_IEs::mobilityControlInfo_Get() const
{
    return mobilityControlInfo;
}

std::string RRCConnectionReconfiguration_r8_IEs::mobilityControlInfo_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "mobilityControlInfo:\n";
    out += mobilityControlInfo.ToString(indent+1);
    return out;
}

std::string RRCConnectionReconfiguration_r8_IEs::mobilityControlInfo_ToStringNoNewLines() const
{
    std::string out = "mobilityControlInfo:";
    out += mobilityControlInfo.ToStringNoNewLines();
    return out;
}

int RRCConnectionReconfiguration_r8_IEs::mobilityControlInfo_Clear()
{
    mobilityControlInfo_present = false;
    return 0;
}

bool RRCConnectionReconfiguration_r8_IEs::mobilityControlInfo_IsPresent() const
{
    return mobilityControlInfo_present;
}

#include "maxDRB.h"

int RRCConnectionReconfiguration_r8_IEs::dedicatedInfoNASList_Pack(std::vector<uint8_t> &bits)
{
    uint32_t N_size_bits = 1;
    while(pow(2, N_size_bits) <= (maxDRB - 1))
        N_size_bits++;
    uint32_t local_size = dedicatedInfoNASList_internal_value.size() - 1;
    for(uint32_t i=0; i<N_size_bits; i++)
        bits.push_back((local_size >> (N_size_bits-i-1)) & 1);
    for(auto item : dedicatedInfoNASList_internal_value)
        if(0 != item.Pack(bits))
        {
            printf("RRCConnectionReconfiguration_r8_IEs::dedicatedInfoNASList_Pack() item_pack_failure\n");
            return -1;
        }
    return 0;
}

int RRCConnectionReconfiguration_r8_IEs::dedicatedInfoNASList_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return dedicatedInfoNASList_Unpack(bits, idx);
}

int RRCConnectionReconfiguration_r8_IEs::dedicatedInfoNASList_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_size_bits = 1;
    while(pow(2, N_size_bits) <= (maxDRB - 1))
        N_size_bits++;
    uint32_t size = 0;
    for(uint32_t i=0; i<N_size_bits; i++)
        size |= bits[idx++] << (N_size_bits-i-1);
    size += 1;
    dedicatedInfoNASList_internal_value.clear();
    for(uint32_t i=0; i<size; i++)
    {
        DedicatedInfoNAS tmp;
        if(0 != tmp.Unpack(bits, idx))
        {
            printf("RRCConnectionReconfiguration_r8_IEs::dedicatedInfoNASList_Unpack() item unpack failure\n");
            return -1;
        }
        dedicatedInfoNASList_internal_value.push_back(tmp);
    }
    dedicatedInfoNASList_present = true;
    return 0;
}

std::vector<DedicatedInfoNAS> RRCConnectionReconfiguration_r8_IEs::dedicatedInfoNASList_Value() const
{
    if(dedicatedInfoNASList_present)
        return dedicatedInfoNASList_internal_value;
    return {};
}

int RRCConnectionReconfiguration_r8_IEs::dedicatedInfoNASList_SetValue(std::vector<DedicatedInfoNAS> value)
{
    if(value.size() < 1 || value.size() > maxDRB)
    {
        printf("RRCConnectionReconfiguration_r8_IEs::dedicatedInfoNASList_SetValue() list size failure\n");
        return -1;
    }
    dedicatedInfoNASList_internal_value = value;
    dedicatedInfoNASList_present = true;
    return 0;
}

int RRCConnectionReconfiguration_r8_IEs::dedicatedInfoNASList_Clear()
{
    dedicatedInfoNASList_present = false;
    dedicatedInfoNASList_internal_value.clear();
    return 0;
}

bool RRCConnectionReconfiguration_r8_IEs::dedicatedInfoNASList_IsPresent() const
{
    return dedicatedInfoNASList_present;
}

std::string RRCConnectionReconfiguration_r8_IEs::dedicatedInfoNASList_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "dedicatedInfoNASList:\n";
    for(auto item : dedicatedInfoNASList_internal_value)
        out += item.ToString(indent+1);
    return out;
}

std::string RRCConnectionReconfiguration_r8_IEs::dedicatedInfoNASList_ToStringNoNewLines() const
{
    std::string out = "dedicatedInfoNASList:";
    for(auto item : dedicatedInfoNASList_internal_value)
        out += item.ToStringNoNewLines();
    return out;
}

RadioResourceConfigDedicated* RRCConnectionReconfiguration_r8_IEs::radioResourceConfigDedicated_Set()
{
    radioResourceConfigDedicated_present = true;
    return &radioResourceConfigDedicated;
}

int RRCConnectionReconfiguration_r8_IEs::radioResourceConfigDedicated_Set(RadioResourceConfigDedicated &value)
{
    radioResourceConfigDedicated_present = true;
    radioResourceConfigDedicated = value;
    return 0;
}

const RadioResourceConfigDedicated& RRCConnectionReconfiguration_r8_IEs::radioResourceConfigDedicated_Get() const
{
    return radioResourceConfigDedicated;
}

std::string RRCConnectionReconfiguration_r8_IEs::radioResourceConfigDedicated_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "radioResourceConfigDedicated:\n";
    out += radioResourceConfigDedicated.ToString(indent+1);
    return out;
}

std::string RRCConnectionReconfiguration_r8_IEs::radioResourceConfigDedicated_ToStringNoNewLines() const
{
    std::string out = "radioResourceConfigDedicated:";
    out += radioResourceConfigDedicated.ToStringNoNewLines();
    return out;
}

int RRCConnectionReconfiguration_r8_IEs::radioResourceConfigDedicated_Clear()
{
    radioResourceConfigDedicated_present = false;
    return 0;
}

bool RRCConnectionReconfiguration_r8_IEs::radioResourceConfigDedicated_IsPresent() const
{
    return radioResourceConfigDedicated_present;
}

SecurityConfigHO* RRCConnectionReconfiguration_r8_IEs::securityConfigHO_Set()
{
    securityConfigHO_present = true;
    return &securityConfigHO;
}

int RRCConnectionReconfiguration_r8_IEs::securityConfigHO_Set(SecurityConfigHO &value)
{
    securityConfigHO_present = true;
    securityConfigHO = value;
    return 0;
}

const SecurityConfigHO& RRCConnectionReconfiguration_r8_IEs::securityConfigHO_Get() const
{
    return securityConfigHO;
}

std::string RRCConnectionReconfiguration_r8_IEs::securityConfigHO_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "securityConfigHO:\n";
    out += securityConfigHO.ToString(indent+1);
    return out;
}

std::string RRCConnectionReconfiguration_r8_IEs::securityConfigHO_ToStringNoNewLines() const
{
    std::string out = "securityConfigHO:";
    out += securityConfigHO.ToStringNoNewLines();
    return out;
}

int RRCConnectionReconfiguration_r8_IEs::securityConfigHO_Clear()
{
    securityConfigHO_present = false;
    return 0;
}

bool RRCConnectionReconfiguration_r8_IEs::securityConfigHO_IsPresent() const
{
    return securityConfigHO_present;
}

RRCConnectionReconfiguration_v890_IEs* RRCConnectionReconfiguration_r8_IEs::nonCriticalExtension_Set()
{
    nonCriticalExtension_present = true;
    return &nonCriticalExtension;
}

int RRCConnectionReconfiguration_r8_IEs::nonCriticalExtension_Set(RRCConnectionReconfiguration_v890_IEs &value)
{
    nonCriticalExtension_present = true;
    nonCriticalExtension = value;
    return 0;
}

const RRCConnectionReconfiguration_v890_IEs& RRCConnectionReconfiguration_r8_IEs::nonCriticalExtension_Get() const
{
    return nonCriticalExtension;
}

std::string RRCConnectionReconfiguration_r8_IEs::nonCriticalExtension_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "nonCriticalExtension:\n";
    out += nonCriticalExtension.ToString(indent+1);
    return out;
}

std::string RRCConnectionReconfiguration_r8_IEs::nonCriticalExtension_ToStringNoNewLines() const
{
    std::string out = "nonCriticalExtension:";
    out += nonCriticalExtension.ToStringNoNewLines();
    return out;
}

int RRCConnectionReconfiguration_r8_IEs::nonCriticalExtension_Clear()
{
    nonCriticalExtension_present = false;
    return 0;
}

bool RRCConnectionReconfiguration_r8_IEs::nonCriticalExtension_IsPresent() const
{
    return nonCriticalExtension_present;
}

