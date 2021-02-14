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

#ifndef __SRB_ToAddMod_H__
#define __SRB_ToAddMod_H__

#include "RLC_Config.h"
#include "LogicalChannelConfig.h"

#include <array>
#include <cstdint>
#include <vector>

class SRB_ToAddMod
{
public:
    SRB_ToAddMod() : srb_Identity_present{false}, rlc_Config_present{false}, logicalChannelConfig_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // srb-Identity
public:
    int srb_Identity_Pack(std::vector<uint8_t> &bits);
    int srb_Identity_Unpack(std::vector<uint8_t> bits);
    int srb_Identity_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t srb_Identity_Value() const;
    int srb_Identity_SetValue(int64_t value);
    std::string srb_Identity_ToString(uint32_t indent) const;
    std::string srb_Identity_ToStringNoNewLines() const;
    int srb_Identity_Clear();
    bool srb_Identity_IsPresent() const;
private:
    bool srb_Identity_present;
    int64_t srb_Identity_internal_value;

    // rlc-Config
public:
    enum rlc_Config_Enum {
        k_rlc_Config_explicitValue = 0,
        k_rlc_Config_defaultValue,
    };
    int rlc_Config_Pack(std::vector<uint8_t> &bits);
    int rlc_Config_Unpack(std::vector<uint8_t> bits);
    int rlc_Config_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    rlc_Config_Enum rlc_Config_Choice() const;
    int rlc_Config_SetChoice(rlc_Config_Enum choice);
    std::string rlc_Config_ChoiceToString(rlc_Config_Enum value) const;
    uint64_t rlc_Config_NumberOfChoices() const;
    std::string rlc_Config_ToString(uint32_t indent) const;
    std::string rlc_Config_ToStringNoNewLines() const;
    int rlc_Config_Clear();
    bool rlc_Config_IsPresent() const;
private:
    bool rlc_Config_present;
    rlc_Config_Enum rlc_Config_internal_choice;

    // explicitValue
public:
    RLC_Config* rlc_Config_explicitValue_Set();
    int rlc_Config_explicitValue_Set(RLC_Config &value);
    const RLC_Config& rlc_Config_explicitValue_Get() const;
    std::string rlc_Config_explicitValue_ToString(uint32_t indent) const;
    std::string rlc_Config_explicitValue_ToStringNoNewLines() const;
    int rlc_Config_explicitValue_Clear();
    bool rlc_Config_explicitValue_IsPresent() const;
private:
    bool rlc_Config_explicitValue_present;
    RLC_Config rlc_Config_explicitValue;

    // defaultValue
public:
    int rlc_Config_defaultValue_Pack(std::vector<uint8_t> &bits) {return 0;};
    int rlc_Config_defaultValue_Unpack(std::vector<uint8_t> bits) {return 0;};
    int rlc_Config_defaultValue_Unpack(std::vector<uint8_t> bits, uint32_t &idx) {return 0;};
    bool rlc_Config_defaultValue_IsPresent() const {return true;};
    std::string rlc_Config_defaultValue_ToString(uint32_t indent) {return "";};
    std::string rlc_Config_defaultValue_ToStringNoNewLines() {return "";};


    // logicalChannelConfig
public:
    enum logicalChannelConfig_Enum {
        k_logicalChannelConfig_explicitValue = 0,
        k_logicalChannelConfig_defaultValue,
    };
    int logicalChannelConfig_Pack(std::vector<uint8_t> &bits);
    int logicalChannelConfig_Unpack(std::vector<uint8_t> bits);
    int logicalChannelConfig_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    logicalChannelConfig_Enum logicalChannelConfig_Choice() const;
    int logicalChannelConfig_SetChoice(logicalChannelConfig_Enum choice);
    std::string logicalChannelConfig_ChoiceToString(logicalChannelConfig_Enum value) const;
    uint64_t logicalChannelConfig_NumberOfChoices() const;
    std::string logicalChannelConfig_ToString(uint32_t indent) const;
    std::string logicalChannelConfig_ToStringNoNewLines() const;
    int logicalChannelConfig_Clear();
    bool logicalChannelConfig_IsPresent() const;
private:
    bool logicalChannelConfig_present;
    logicalChannelConfig_Enum logicalChannelConfig_internal_choice;

    // explicitValue
public:
    LogicalChannelConfig* logicalChannelConfig_explicitValue_Set();
    int logicalChannelConfig_explicitValue_Set(LogicalChannelConfig &value);
    const LogicalChannelConfig& logicalChannelConfig_explicitValue_Get() const;
    std::string logicalChannelConfig_explicitValue_ToString(uint32_t indent) const;
    std::string logicalChannelConfig_explicitValue_ToStringNoNewLines() const;
    int logicalChannelConfig_explicitValue_Clear();
    bool logicalChannelConfig_explicitValue_IsPresent() const;
private:
    bool logicalChannelConfig_explicitValue_present;
    LogicalChannelConfig logicalChannelConfig_explicitValue;

    // defaultValue
public:
    int logicalChannelConfig_defaultValue_Pack(std::vector<uint8_t> &bits) {return 0;};
    int logicalChannelConfig_defaultValue_Unpack(std::vector<uint8_t> bits) {return 0;};
    int logicalChannelConfig_defaultValue_Unpack(std::vector<uint8_t> bits, uint32_t &idx) {return 0;};
    bool logicalChannelConfig_defaultValue_IsPresent() const {return true;};
    std::string logicalChannelConfig_defaultValue_ToString(uint32_t indent) {return "";};
    std::string logicalChannelConfig_defaultValue_ToStringNoNewLines() {return "";};


};

#endif
