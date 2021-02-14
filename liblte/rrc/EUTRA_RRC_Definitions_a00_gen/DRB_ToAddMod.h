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

#ifndef __DRB_ToAddMod_H__
#define __DRB_ToAddMod_H__

#include "DRB_Identity.h"
#include "PDCP_Config.h"
#include "RLC_Config.h"
#include "LogicalChannelConfig.h"

#include <array>
#include <cstdint>
#include <vector>

class DRB_ToAddMod
{
public:
    DRB_ToAddMod() : eps_BearerIdentity_present{false}, drb_Identity_present{false}, pdcp_Config_present{false}, rlc_Config_present{false}, logicalChannelIdentity_present{false}, logicalChannelConfig_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // eps-BearerIdentity
public:
    int eps_BearerIdentity_Pack(std::vector<uint8_t> &bits);
    int eps_BearerIdentity_Unpack(std::vector<uint8_t> bits);
    int eps_BearerIdentity_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t eps_BearerIdentity_Value() const;
    int eps_BearerIdentity_SetValue(int64_t value);
    std::string eps_BearerIdentity_ToString(uint32_t indent) const;
    std::string eps_BearerIdentity_ToStringNoNewLines() const;
    int eps_BearerIdentity_Clear();
    bool eps_BearerIdentity_IsPresent() const;
private:
    bool eps_BearerIdentity_present;
    int64_t eps_BearerIdentity_internal_value;

    // drb-Identity
public:
    DRB_Identity* drb_Identity_Set();
    int drb_Identity_Set(DRB_Identity &value);
    const DRB_Identity& drb_Identity_Get() const;
    std::string drb_Identity_ToString(uint32_t indent) const;
    std::string drb_Identity_ToStringNoNewLines() const;
    int drb_Identity_Clear();
    bool drb_Identity_IsPresent() const;
private:
    bool drb_Identity_present;
    DRB_Identity drb_Identity;

    // pdcp-Config
public:
    PDCP_Config* pdcp_Config_Set();
    int pdcp_Config_Set(PDCP_Config &value);
    const PDCP_Config& pdcp_Config_Get() const;
    std::string pdcp_Config_ToString(uint32_t indent) const;
    std::string pdcp_Config_ToStringNoNewLines() const;
    int pdcp_Config_Clear();
    bool pdcp_Config_IsPresent() const;
private:
    bool pdcp_Config_present;
    PDCP_Config pdcp_Config;

    // rlc-Config
public:
    RLC_Config* rlc_Config_Set();
    int rlc_Config_Set(RLC_Config &value);
    const RLC_Config& rlc_Config_Get() const;
    std::string rlc_Config_ToString(uint32_t indent) const;
    std::string rlc_Config_ToStringNoNewLines() const;
    int rlc_Config_Clear();
    bool rlc_Config_IsPresent() const;
private:
    bool rlc_Config_present;
    RLC_Config rlc_Config;

    // logicalChannelIdentity
public:
    int logicalChannelIdentity_Pack(std::vector<uint8_t> &bits);
    int logicalChannelIdentity_Unpack(std::vector<uint8_t> bits);
    int logicalChannelIdentity_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t logicalChannelIdentity_Value() const;
    int logicalChannelIdentity_SetValue(int64_t value);
    std::string logicalChannelIdentity_ToString(uint32_t indent) const;
    std::string logicalChannelIdentity_ToStringNoNewLines() const;
    int logicalChannelIdentity_Clear();
    bool logicalChannelIdentity_IsPresent() const;
private:
    bool logicalChannelIdentity_present;
    int64_t logicalChannelIdentity_internal_value;

    // logicalChannelConfig
public:
    LogicalChannelConfig* logicalChannelConfig_Set();
    int logicalChannelConfig_Set(LogicalChannelConfig &value);
    const LogicalChannelConfig& logicalChannelConfig_Get() const;
    std::string logicalChannelConfig_ToString(uint32_t indent) const;
    std::string logicalChannelConfig_ToStringNoNewLines() const;
    int logicalChannelConfig_Clear();
    bool logicalChannelConfig_IsPresent() const;
private:
    bool logicalChannelConfig_present;
    LogicalChannelConfig logicalChannelConfig;

};

#endif
