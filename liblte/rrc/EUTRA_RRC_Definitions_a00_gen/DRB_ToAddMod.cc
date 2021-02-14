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

#include "DRB_ToAddMod.h"

#include <cmath>

int DRB_ToAddMod::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator
    bits.push_back(0);

    // Optional indicators
    bits.push_back(eps_BearerIdentity_IsPresent());
    bits.push_back(pdcp_Config_IsPresent());
    bits.push_back(rlc_Config_IsPresent());
    bits.push_back(logicalChannelIdentity_IsPresent());
    bits.push_back(logicalChannelConfig_IsPresent());

    // Fields
    if(eps_BearerIdentity_IsPresent())
    {
        if(0 != eps_BearerIdentity_Pack(bits))
        {
            printf("DRB_ToAddMod:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != drb_Identity.Pack(bits))
        {
            printf("DRB_ToAddMod:: field pack failure\n");
            return -1;
        }
    }
    if(pdcp_Config_IsPresent())
    {
        if(0 != pdcp_Config.Pack(bits))
        {
            printf("DRB_ToAddMod:: field pack failure\n");
            return -1;
        }
    }
    if(rlc_Config_IsPresent())
    {
        if(0 != rlc_Config.Pack(bits))
        {
            printf("DRB_ToAddMod:: field pack failure\n");
            return -1;
        }
    }
    if(logicalChannelIdentity_IsPresent())
    {
        if(0 != logicalChannelIdentity_Pack(bits))
        {
            printf("DRB_ToAddMod:: field pack failure\n");
            return -1;
        }
    }
    if(logicalChannelConfig_IsPresent())
    {
        if(0 != logicalChannelConfig.Pack(bits))
        {
            printf("DRB_ToAddMod:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int DRB_ToAddMod::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int DRB_ToAddMod::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("DRB_ToAddMod::Unpack() index out of bounds for extension\n");
        return -1;
    }
    idx++;

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("DRB_ToAddMod::Unpack() index out of bounds for optional indiator eps_BearerIdentity\n");
        return -1;
    }
    eps_BearerIdentity_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("DRB_ToAddMod::Unpack() index out of bounds for optional indiator pdcp_Config\n");
        return -1;
    }
    pdcp_Config_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("DRB_ToAddMod::Unpack() index out of bounds for optional indiator rlc_Config\n");
        return -1;
    }
    rlc_Config_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("DRB_ToAddMod::Unpack() index out of bounds for optional indiator logicalChannelIdentity\n");
        return -1;
    }
    logicalChannelIdentity_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("DRB_ToAddMod::Unpack() index out of bounds for optional indiator logicalChannelConfig\n");
        return -1;
    }
    logicalChannelConfig_present = bits[idx++];

    // Fields
    if(eps_BearerIdentity_present)
    {
        if(0 != eps_BearerIdentity_Unpack(bits, idx))
        {
            printf("DRB_ToAddMod:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != drb_Identity.Unpack(bits, idx))
        {
            printf("DRB_ToAddMod:: field unpack failure\n");
            return -1;
        }
    }
    if(pdcp_Config_present)
    {
        if(0 != pdcp_Config.Unpack(bits, idx))
        {
            printf("DRB_ToAddMod:: field unpack failure\n");
            return -1;
        }
    }
    if(rlc_Config_present)
    {
        if(0 != rlc_Config.Unpack(bits, idx))
        {
            printf("DRB_ToAddMod:: field unpack failure\n");
            return -1;
        }
    }
    if(logicalChannelIdentity_present)
    {
        if(0 != logicalChannelIdentity_Unpack(bits, idx))
        {
            printf("DRB_ToAddMod:: field unpack failure\n");
            return -1;
        }
    }
    if(logicalChannelConfig_present)
    {
        if(0 != logicalChannelConfig.Unpack(bits, idx))
        {
            printf("DRB_ToAddMod:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string DRB_ToAddMod::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "DRB_ToAddMod:\n";
    if(eps_BearerIdentity_IsPresent())
        out += eps_BearerIdentity_ToString(indent+1);
    out += drb_Identity_ToString(indent+1);
    if(pdcp_Config_IsPresent())
        out += pdcp_Config_ToString(indent+1);
    if(rlc_Config_IsPresent())
        out += rlc_Config_ToString(indent+1);
    if(logicalChannelIdentity_IsPresent())
        out += logicalChannelIdentity_ToString(indent+1);
    if(logicalChannelConfig_IsPresent())
        out += logicalChannelConfig_ToString(indent+1);
    return out;
}

std::string DRB_ToAddMod::ToStringNoNewLines() const
{
    std::string out = "DRB_ToAddMod:";
    if(eps_BearerIdentity_IsPresent())
        out += eps_BearerIdentity_ToStringNoNewLines();
    out += drb_Identity_ToStringNoNewLines();
    if(pdcp_Config_IsPresent())
        out += pdcp_Config_ToStringNoNewLines();
    if(rlc_Config_IsPresent())
        out += rlc_Config_ToStringNoNewLines();
    if(logicalChannelIdentity_IsPresent())
        out += logicalChannelIdentity_ToStringNoNewLines();
    if(logicalChannelConfig_IsPresent())
        out += logicalChannelConfig_ToStringNoNewLines();
    return out;
}

int DRB_ToAddMod::eps_BearerIdentity_Pack(std::vector<uint8_t> &bits)
{
    int64_t val_to_pack = eps_BearerIdentity_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (15 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int DRB_ToAddMod::eps_BearerIdentity_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return eps_BearerIdentity_Unpack(bits, idx);
}

int DRB_ToAddMod::eps_BearerIdentity_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (15 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("DRB_ToAddMod::eps_BearerIdentity_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    eps_BearerIdentity_internal_value = packed_val + 0;
    eps_BearerIdentity_present = true;
    return 0;
}

int64_t DRB_ToAddMod::eps_BearerIdentity_Value() const
{
    if(eps_BearerIdentity_present)
        return eps_BearerIdentity_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int DRB_ToAddMod::eps_BearerIdentity_SetValue(int64_t value)
{
    if(value < 0 || value > 15)
    {
        printf("DRB_ToAddMod::eps_BearerIdentity_SetValue() range failure\n");
        return -1;
    }
    eps_BearerIdentity_internal_value = value;
    eps_BearerIdentity_present = true;
    return 0;
}

std::string DRB_ToAddMod::eps_BearerIdentity_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "eps_BearerIdentity = " + std::to_string(eps_BearerIdentity_internal_value) + "\n";
    return out;
}

std::string DRB_ToAddMod::eps_BearerIdentity_ToStringNoNewLines() const
{
    std::string out = "eps_BearerIdentity=" + std::to_string(eps_BearerIdentity_internal_value) + ",";
    return out;
}

int DRB_ToAddMod::eps_BearerIdentity_Clear()
{
    eps_BearerIdentity_present = false;
    return 0;
}

bool DRB_ToAddMod::eps_BearerIdentity_IsPresent() const
{
    return eps_BearerIdentity_present;
}

DRB_Identity* DRB_ToAddMod::drb_Identity_Set()
{
    drb_Identity_present = true;
    return &drb_Identity;
}

int DRB_ToAddMod::drb_Identity_Set(DRB_Identity &value)
{
    drb_Identity_present = true;
    drb_Identity = value;
    return 0;
}

const DRB_Identity& DRB_ToAddMod::drb_Identity_Get() const
{
    return drb_Identity;
}

std::string DRB_ToAddMod::drb_Identity_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "drb_Identity:\n";
    out += drb_Identity.ToString(indent+1);
    return out;
}

std::string DRB_ToAddMod::drb_Identity_ToStringNoNewLines() const
{
    std::string out = "drb_Identity:";
    out += drb_Identity.ToStringNoNewLines();
    return out;
}

int DRB_ToAddMod::drb_Identity_Clear()
{
    drb_Identity_present = false;
    return 0;
}

bool DRB_ToAddMod::drb_Identity_IsPresent() const
{
    return drb_Identity_present;
}

PDCP_Config* DRB_ToAddMod::pdcp_Config_Set()
{
    pdcp_Config_present = true;
    return &pdcp_Config;
}

int DRB_ToAddMod::pdcp_Config_Set(PDCP_Config &value)
{
    pdcp_Config_present = true;
    pdcp_Config = value;
    return 0;
}

const PDCP_Config& DRB_ToAddMod::pdcp_Config_Get() const
{
    return pdcp_Config;
}

std::string DRB_ToAddMod::pdcp_Config_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "pdcp_Config:\n";
    out += pdcp_Config.ToString(indent+1);
    return out;
}

std::string DRB_ToAddMod::pdcp_Config_ToStringNoNewLines() const
{
    std::string out = "pdcp_Config:";
    out += pdcp_Config.ToStringNoNewLines();
    return out;
}

int DRB_ToAddMod::pdcp_Config_Clear()
{
    pdcp_Config_present = false;
    return 0;
}

bool DRB_ToAddMod::pdcp_Config_IsPresent() const
{
    return pdcp_Config_present;
}

RLC_Config* DRB_ToAddMod::rlc_Config_Set()
{
    rlc_Config_present = true;
    return &rlc_Config;
}

int DRB_ToAddMod::rlc_Config_Set(RLC_Config &value)
{
    rlc_Config_present = true;
    rlc_Config = value;
    return 0;
}

const RLC_Config& DRB_ToAddMod::rlc_Config_Get() const
{
    return rlc_Config;
}

std::string DRB_ToAddMod::rlc_Config_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "rlc_Config:\n";
    out += rlc_Config.ToString(indent+1);
    return out;
}

std::string DRB_ToAddMod::rlc_Config_ToStringNoNewLines() const
{
    std::string out = "rlc_Config:";
    out += rlc_Config.ToStringNoNewLines();
    return out;
}

int DRB_ToAddMod::rlc_Config_Clear()
{
    rlc_Config_present = false;
    return 0;
}

bool DRB_ToAddMod::rlc_Config_IsPresent() const
{
    return rlc_Config_present;
}

int DRB_ToAddMod::logicalChannelIdentity_Pack(std::vector<uint8_t> &bits)
{
    int64_t val_to_pack = logicalChannelIdentity_internal_value - (3);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (10 - 3))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int DRB_ToAddMod::logicalChannelIdentity_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return logicalChannelIdentity_Unpack(bits, idx);
}

int DRB_ToAddMod::logicalChannelIdentity_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (10 - 3))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("DRB_ToAddMod::logicalChannelIdentity_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    logicalChannelIdentity_internal_value = packed_val + 3;
    logicalChannelIdentity_present = true;
    return 0;
}

int64_t DRB_ToAddMod::logicalChannelIdentity_Value() const
{
    if(logicalChannelIdentity_present)
        return logicalChannelIdentity_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int DRB_ToAddMod::logicalChannelIdentity_SetValue(int64_t value)
{
    if(value < 3 || value > 10)
    {
        printf("DRB_ToAddMod::logicalChannelIdentity_SetValue() range failure\n");
        return -1;
    }
    logicalChannelIdentity_internal_value = value;
    logicalChannelIdentity_present = true;
    return 0;
}

std::string DRB_ToAddMod::logicalChannelIdentity_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "logicalChannelIdentity = " + std::to_string(logicalChannelIdentity_internal_value) + "\n";
    return out;
}

std::string DRB_ToAddMod::logicalChannelIdentity_ToStringNoNewLines() const
{
    std::string out = "logicalChannelIdentity=" + std::to_string(logicalChannelIdentity_internal_value) + ",";
    return out;
}

int DRB_ToAddMod::logicalChannelIdentity_Clear()
{
    logicalChannelIdentity_present = false;
    return 0;
}

bool DRB_ToAddMod::logicalChannelIdentity_IsPresent() const
{
    return logicalChannelIdentity_present;
}

LogicalChannelConfig* DRB_ToAddMod::logicalChannelConfig_Set()
{
    logicalChannelConfig_present = true;
    return &logicalChannelConfig;
}

int DRB_ToAddMod::logicalChannelConfig_Set(LogicalChannelConfig &value)
{
    logicalChannelConfig_present = true;
    logicalChannelConfig = value;
    return 0;
}

const LogicalChannelConfig& DRB_ToAddMod::logicalChannelConfig_Get() const
{
    return logicalChannelConfig;
}

std::string DRB_ToAddMod::logicalChannelConfig_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "logicalChannelConfig:\n";
    out += logicalChannelConfig.ToString(indent+1);
    return out;
}

std::string DRB_ToAddMod::logicalChannelConfig_ToStringNoNewLines() const
{
    std::string out = "logicalChannelConfig:";
    out += logicalChannelConfig.ToStringNoNewLines();
    return out;
}

int DRB_ToAddMod::logicalChannelConfig_Clear()
{
    logicalChannelConfig_present = false;
    return 0;
}

bool DRB_ToAddMod::logicalChannelConfig_IsPresent() const
{
    return logicalChannelConfig_present;
}

