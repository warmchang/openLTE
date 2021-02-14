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

#ifndef __RadioResourceConfigDedicated_H__
#define __RadioResourceConfigDedicated_H__

#include "SRB_ToAddModList.h"
#include "DRB_ToAddModList.h"
#include "DRB_ToReleaseList.h"
#include "MAC_MainConfig.h"
#include "SPS_Config.h"
#include "PhysicalConfigDedicated.h"
#include "RLF_TimersAndConstants_r9.h"

#include <array>
#include <cstdint>
#include <vector>

class RadioResourceConfigDedicated
{
public:
    RadioResourceConfigDedicated() : srb_ToAddModList_present{false}, drb_ToAddModList_present{false}, drb_ToReleaseList_present{false}, mac_MainConfig_present{false}, sps_Config_present{false}, physicalConfigDedicated_present{false}, rlf_TimersAndConstants_r9_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // srb-ToAddModList
public:
    SRB_ToAddModList* srb_ToAddModList_Set();
    int srb_ToAddModList_Set(SRB_ToAddModList &value);
    const SRB_ToAddModList& srb_ToAddModList_Get() const;
    std::string srb_ToAddModList_ToString(uint32_t indent) const;
    std::string srb_ToAddModList_ToStringNoNewLines() const;
    int srb_ToAddModList_Clear();
    bool srb_ToAddModList_IsPresent() const;
private:
    bool srb_ToAddModList_present;
    SRB_ToAddModList srb_ToAddModList;

    // drb-ToAddModList
public:
    DRB_ToAddModList* drb_ToAddModList_Set();
    int drb_ToAddModList_Set(DRB_ToAddModList &value);
    const DRB_ToAddModList& drb_ToAddModList_Get() const;
    std::string drb_ToAddModList_ToString(uint32_t indent) const;
    std::string drb_ToAddModList_ToStringNoNewLines() const;
    int drb_ToAddModList_Clear();
    bool drb_ToAddModList_IsPresent() const;
private:
    bool drb_ToAddModList_present;
    DRB_ToAddModList drb_ToAddModList;

    // drb-ToReleaseList
public:
    DRB_ToReleaseList* drb_ToReleaseList_Set();
    int drb_ToReleaseList_Set(DRB_ToReleaseList &value);
    const DRB_ToReleaseList& drb_ToReleaseList_Get() const;
    std::string drb_ToReleaseList_ToString(uint32_t indent) const;
    std::string drb_ToReleaseList_ToStringNoNewLines() const;
    int drb_ToReleaseList_Clear();
    bool drb_ToReleaseList_IsPresent() const;
private:
    bool drb_ToReleaseList_present;
    DRB_ToReleaseList drb_ToReleaseList;

    // mac-MainConfig
public:
    enum mac_MainConfig_Enum {
        k_mac_MainConfig_explicitValue = 0,
        k_mac_MainConfig_defaultValue,
    };
    int mac_MainConfig_Pack(std::vector<uint8_t> &bits);
    int mac_MainConfig_Unpack(std::vector<uint8_t> bits);
    int mac_MainConfig_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    mac_MainConfig_Enum mac_MainConfig_Choice() const;
    int mac_MainConfig_SetChoice(mac_MainConfig_Enum choice);
    std::string mac_MainConfig_ChoiceToString(mac_MainConfig_Enum value) const;
    uint64_t mac_MainConfig_NumberOfChoices() const;
    std::string mac_MainConfig_ToString(uint32_t indent) const;
    std::string mac_MainConfig_ToStringNoNewLines() const;
    int mac_MainConfig_Clear();
    bool mac_MainConfig_IsPresent() const;
private:
    bool mac_MainConfig_present;
    mac_MainConfig_Enum mac_MainConfig_internal_choice;

    // explicitValue
public:
    MAC_MainConfig* mac_MainConfig_explicitValue_Set();
    int mac_MainConfig_explicitValue_Set(MAC_MainConfig &value);
    const MAC_MainConfig& mac_MainConfig_explicitValue_Get() const;
    std::string mac_MainConfig_explicitValue_ToString(uint32_t indent) const;
    std::string mac_MainConfig_explicitValue_ToStringNoNewLines() const;
    int mac_MainConfig_explicitValue_Clear();
    bool mac_MainConfig_explicitValue_IsPresent() const;
private:
    bool mac_MainConfig_explicitValue_present;
    MAC_MainConfig mac_MainConfig_explicitValue;

    // defaultValue
public:
    int mac_MainConfig_defaultValue_Pack(std::vector<uint8_t> &bits) {return 0;};
    int mac_MainConfig_defaultValue_Unpack(std::vector<uint8_t> bits) {return 0;};
    int mac_MainConfig_defaultValue_Unpack(std::vector<uint8_t> bits, uint32_t &idx) {return 0;};
    bool mac_MainConfig_defaultValue_IsPresent() const {return true;};
    std::string mac_MainConfig_defaultValue_ToString(uint32_t indent) {return "";};
    std::string mac_MainConfig_defaultValue_ToStringNoNewLines() {return "";};


    // sps-Config
public:
    SPS_Config* sps_Config_Set();
    int sps_Config_Set(SPS_Config &value);
    const SPS_Config& sps_Config_Get() const;
    std::string sps_Config_ToString(uint32_t indent) const;
    std::string sps_Config_ToStringNoNewLines() const;
    int sps_Config_Clear();
    bool sps_Config_IsPresent() const;
private:
    bool sps_Config_present;
    SPS_Config sps_Config;

    // physicalConfigDedicated
public:
    PhysicalConfigDedicated* physicalConfigDedicated_Set();
    int physicalConfigDedicated_Set(PhysicalConfigDedicated &value);
    const PhysicalConfigDedicated& physicalConfigDedicated_Get() const;
    std::string physicalConfigDedicated_ToString(uint32_t indent) const;
    std::string physicalConfigDedicated_ToStringNoNewLines() const;
    int physicalConfigDedicated_Clear();
    bool physicalConfigDedicated_IsPresent() const;
private:
    bool physicalConfigDedicated_present;
    PhysicalConfigDedicated physicalConfigDedicated;

    // rlf-TimersAndConstants-r9
public:
    RLF_TimersAndConstants_r9* rlf_TimersAndConstants_r9_Set();
    int rlf_TimersAndConstants_r9_Set(RLF_TimersAndConstants_r9 &value);
    const RLF_TimersAndConstants_r9& rlf_TimersAndConstants_r9_Get() const;
    std::string rlf_TimersAndConstants_r9_ToString(uint32_t indent) const;
    std::string rlf_TimersAndConstants_r9_ToStringNoNewLines() const;
    int rlf_TimersAndConstants_r9_Clear();
    bool rlf_TimersAndConstants_r9_IsPresent() const;
private:
    bool rlf_TimersAndConstants_r9_present;
    RLF_TimersAndConstants_r9 rlf_TimersAndConstants_r9;

};

#endif
