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

#ifndef __RadioResourceConfigCommonSIB_H__
#define __RadioResourceConfigCommonSIB_H__

#include "RACH_ConfigCommon.h"
#include "BCCH_Config.h"
#include "PCCH_Config.h"
#include "PRACH_ConfigSIB.h"
#include "PDSCH_ConfigCommon.h"
#include "PUSCH_ConfigCommon.h"
#include "PUCCH_ConfigCommon.h"
#include "SoundingRS_UL_ConfigCommon.h"
#include "UplinkPowerControlCommon.h"
#include "UL_CyclicPrefixLength.h"
#include "UplinkPowerControlCommon_v10x0.h"

#include <array>
#include <cstdint>
#include <vector>

class RadioResourceConfigCommonSIB
{
public:
    RadioResourceConfigCommonSIB() : rach_ConfigCommon_present{false}, bcch_Config_present{false}, pcch_Config_present{false}, prach_Config_present{false}, pdsch_ConfigCommon_present{false}, pusch_ConfigCommon_present{false}, pucch_ConfigCommon_present{false}, soundingRS_UL_ConfigCommon_present{false}, uplinkPowerControlCommon_present{false}, ul_CyclicPrefixLength_present{false}, uplinkPowerControlCommon_v10x0_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // rach-ConfigCommon
public:
    RACH_ConfigCommon* rach_ConfigCommon_Set();
    int rach_ConfigCommon_Set(RACH_ConfigCommon &value);
    const RACH_ConfigCommon& rach_ConfigCommon_Get() const;
    std::string rach_ConfigCommon_ToString(uint32_t indent) const;
    std::string rach_ConfigCommon_ToStringNoNewLines() const;
    int rach_ConfigCommon_Clear();
    bool rach_ConfigCommon_IsPresent() const;
private:
    bool rach_ConfigCommon_present;
    RACH_ConfigCommon rach_ConfigCommon;

    // bcch-Config
public:
    BCCH_Config* bcch_Config_Set();
    int bcch_Config_Set(BCCH_Config &value);
    const BCCH_Config& bcch_Config_Get() const;
    std::string bcch_Config_ToString(uint32_t indent) const;
    std::string bcch_Config_ToStringNoNewLines() const;
    int bcch_Config_Clear();
    bool bcch_Config_IsPresent() const;
private:
    bool bcch_Config_present;
    BCCH_Config bcch_Config;

    // pcch-Config
public:
    PCCH_Config* pcch_Config_Set();
    int pcch_Config_Set(PCCH_Config &value);
    const PCCH_Config& pcch_Config_Get() const;
    std::string pcch_Config_ToString(uint32_t indent) const;
    std::string pcch_Config_ToStringNoNewLines() const;
    int pcch_Config_Clear();
    bool pcch_Config_IsPresent() const;
private:
    bool pcch_Config_present;
    PCCH_Config pcch_Config;

    // prach-Config
public:
    PRACH_ConfigSIB* prach_Config_Set();
    int prach_Config_Set(PRACH_ConfigSIB &value);
    const PRACH_ConfigSIB& prach_Config_Get() const;
    std::string prach_Config_ToString(uint32_t indent) const;
    std::string prach_Config_ToStringNoNewLines() const;
    int prach_Config_Clear();
    bool prach_Config_IsPresent() const;
private:
    bool prach_Config_present;
    PRACH_ConfigSIB prach_Config;

    // pdsch-ConfigCommon
public:
    PDSCH_ConfigCommon* pdsch_ConfigCommon_Set();
    int pdsch_ConfigCommon_Set(PDSCH_ConfigCommon &value);
    const PDSCH_ConfigCommon& pdsch_ConfigCommon_Get() const;
    std::string pdsch_ConfigCommon_ToString(uint32_t indent) const;
    std::string pdsch_ConfigCommon_ToStringNoNewLines() const;
    int pdsch_ConfigCommon_Clear();
    bool pdsch_ConfigCommon_IsPresent() const;
private:
    bool pdsch_ConfigCommon_present;
    PDSCH_ConfigCommon pdsch_ConfigCommon;

    // pusch-ConfigCommon
public:
    PUSCH_ConfigCommon* pusch_ConfigCommon_Set();
    int pusch_ConfigCommon_Set(PUSCH_ConfigCommon &value);
    const PUSCH_ConfigCommon& pusch_ConfigCommon_Get() const;
    std::string pusch_ConfigCommon_ToString(uint32_t indent) const;
    std::string pusch_ConfigCommon_ToStringNoNewLines() const;
    int pusch_ConfigCommon_Clear();
    bool pusch_ConfigCommon_IsPresent() const;
private:
    bool pusch_ConfigCommon_present;
    PUSCH_ConfigCommon pusch_ConfigCommon;

    // pucch-ConfigCommon
public:
    PUCCH_ConfigCommon* pucch_ConfigCommon_Set();
    int pucch_ConfigCommon_Set(PUCCH_ConfigCommon &value);
    const PUCCH_ConfigCommon& pucch_ConfigCommon_Get() const;
    std::string pucch_ConfigCommon_ToString(uint32_t indent) const;
    std::string pucch_ConfigCommon_ToStringNoNewLines() const;
    int pucch_ConfigCommon_Clear();
    bool pucch_ConfigCommon_IsPresent() const;
private:
    bool pucch_ConfigCommon_present;
    PUCCH_ConfigCommon pucch_ConfigCommon;

    // soundingRS-UL-ConfigCommon
public:
    SoundingRS_UL_ConfigCommon* soundingRS_UL_ConfigCommon_Set();
    int soundingRS_UL_ConfigCommon_Set(SoundingRS_UL_ConfigCommon &value);
    const SoundingRS_UL_ConfigCommon& soundingRS_UL_ConfigCommon_Get() const;
    std::string soundingRS_UL_ConfigCommon_ToString(uint32_t indent) const;
    std::string soundingRS_UL_ConfigCommon_ToStringNoNewLines() const;
    int soundingRS_UL_ConfigCommon_Clear();
    bool soundingRS_UL_ConfigCommon_IsPresent() const;
private:
    bool soundingRS_UL_ConfigCommon_present;
    SoundingRS_UL_ConfigCommon soundingRS_UL_ConfigCommon;

    // uplinkPowerControlCommon
public:
    UplinkPowerControlCommon* uplinkPowerControlCommon_Set();
    int uplinkPowerControlCommon_Set(UplinkPowerControlCommon &value);
    const UplinkPowerControlCommon& uplinkPowerControlCommon_Get() const;
    std::string uplinkPowerControlCommon_ToString(uint32_t indent) const;
    std::string uplinkPowerControlCommon_ToStringNoNewLines() const;
    int uplinkPowerControlCommon_Clear();
    bool uplinkPowerControlCommon_IsPresent() const;
private:
    bool uplinkPowerControlCommon_present;
    UplinkPowerControlCommon uplinkPowerControlCommon;

    // ul-CyclicPrefixLength
public:
    UL_CyclicPrefixLength* ul_CyclicPrefixLength_Set();
    int ul_CyclicPrefixLength_Set(UL_CyclicPrefixLength &value);
    const UL_CyclicPrefixLength& ul_CyclicPrefixLength_Get() const;
    std::string ul_CyclicPrefixLength_ToString(uint32_t indent) const;
    std::string ul_CyclicPrefixLength_ToStringNoNewLines() const;
    int ul_CyclicPrefixLength_Clear();
    bool ul_CyclicPrefixLength_IsPresent() const;
private:
    bool ul_CyclicPrefixLength_present;
    UL_CyclicPrefixLength ul_CyclicPrefixLength;

    // uplinkPowerControlCommon-v10x0
public:
    UplinkPowerControlCommon_v10x0* uplinkPowerControlCommon_v10x0_Set();
    int uplinkPowerControlCommon_v10x0_Set(UplinkPowerControlCommon_v10x0 &value);
    const UplinkPowerControlCommon_v10x0& uplinkPowerControlCommon_v10x0_Get() const;
    std::string uplinkPowerControlCommon_v10x0_ToString(uint32_t indent) const;
    std::string uplinkPowerControlCommon_v10x0_ToStringNoNewLines() const;
    int uplinkPowerControlCommon_v10x0_Clear();
    bool uplinkPowerControlCommon_v10x0_IsPresent() const;
private:
    bool uplinkPowerControlCommon_v10x0_present;
    UplinkPowerControlCommon_v10x0 uplinkPowerControlCommon_v10x0;

};

#endif
