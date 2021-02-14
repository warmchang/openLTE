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

#ifndef __PhysicalConfigDedicated_H__
#define __PhysicalConfigDedicated_H__

#include "PDSCH_ConfigDedicated.h"
#include "PUCCH_ConfigDedicated.h"
#include "PUSCH_ConfigDedicated.h"
#include "UplinkPowerControlDedicated.h"
#include "TPC_PDCCH_Config.h"
#include "TPC_PDCCH_Config.h"
#include "CQI_ReportConfig.h"
#include "SoundingRS_UL_ConfigDedicated.h"
#include "AntennaInfoDedicated.h"
#include "SchedulingRequestConfig.h"
#include "CQI_ReportConfig_v920.h"
#include "AntennaInfoDedicated_v920.h"
#include "AntennaInfoDedicated_r10.h"
#include "CQI_ReportConfig_v10x0.h"
#include "CSI_RS_Config_r10.h"
#include "PUCCH_ConfigDedicated_v10x0.h"
#include "PUSCH_ConfigDedicated_v10x0.h"
#include "SchedulingRequestConfig_v10x0.h"
#include "SoundingRS_UL_ConfigDedicated_v10x0.h"
#include "SoundingRS_UL_ConfigDedicatedAperiodic_r10.h"
#include "UL_AntennaInfo_r10.h"

#include <array>
#include <cstdint>
#include <vector>

class PhysicalConfigDedicated
{
public:
    PhysicalConfigDedicated() : pdsch_ConfigDedicated_present{false}, pucch_ConfigDedicated_present{false}, pusch_ConfigDedicated_present{false}, uplinkPowerControlDedicated_present{false}, tpc_PDCCH_ConfigPUCCH_present{false}, tpc_PDCCH_ConfigPUSCH_present{false}, cqi_ReportConfig_present{false}, soundingRS_UL_ConfigDedicated_present{false}, antennaInfo_present{false}, schedulingRequestConfig_present{false}, cqi_ReportConfig_v920_present{false}, antennaInfo_v920_present{false}, antennaInfo_r10_present{false}, cif_Presence_present{false}, cqi_ReportConfig_v10x0_present{false}, csi_RS_Config_r10_present{false}, pucch_ConfigDedicated_v10x0_present{false}, pusch_ConfigDedicated_v10x0_present{false}, schedulingRequestConfig_v10x0_present{false}, soundingRS_UL_ConfigDedicated_v10x0_present{false}, soundingRS_UL_ConfigDedicatedAperiodic_r10_present{false}, ul_AntennaInfo_r10_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // pdsch-ConfigDedicated
public:
    PDSCH_ConfigDedicated* pdsch_ConfigDedicated_Set();
    int pdsch_ConfigDedicated_Set(PDSCH_ConfigDedicated &value);
    const PDSCH_ConfigDedicated& pdsch_ConfigDedicated_Get() const;
    std::string pdsch_ConfigDedicated_ToString(uint32_t indent) const;
    std::string pdsch_ConfigDedicated_ToStringNoNewLines() const;
    int pdsch_ConfigDedicated_Clear();
    bool pdsch_ConfigDedicated_IsPresent() const;
private:
    bool pdsch_ConfigDedicated_present;
    PDSCH_ConfigDedicated pdsch_ConfigDedicated;

    // pucch-ConfigDedicated
public:
    PUCCH_ConfigDedicated* pucch_ConfigDedicated_Set();
    int pucch_ConfigDedicated_Set(PUCCH_ConfigDedicated &value);
    const PUCCH_ConfigDedicated& pucch_ConfigDedicated_Get() const;
    std::string pucch_ConfigDedicated_ToString(uint32_t indent) const;
    std::string pucch_ConfigDedicated_ToStringNoNewLines() const;
    int pucch_ConfigDedicated_Clear();
    bool pucch_ConfigDedicated_IsPresent() const;
private:
    bool pucch_ConfigDedicated_present;
    PUCCH_ConfigDedicated pucch_ConfigDedicated;

    // pusch-ConfigDedicated
public:
    PUSCH_ConfigDedicated* pusch_ConfigDedicated_Set();
    int pusch_ConfigDedicated_Set(PUSCH_ConfigDedicated &value);
    const PUSCH_ConfigDedicated& pusch_ConfigDedicated_Get() const;
    std::string pusch_ConfigDedicated_ToString(uint32_t indent) const;
    std::string pusch_ConfigDedicated_ToStringNoNewLines() const;
    int pusch_ConfigDedicated_Clear();
    bool pusch_ConfigDedicated_IsPresent() const;
private:
    bool pusch_ConfigDedicated_present;
    PUSCH_ConfigDedicated pusch_ConfigDedicated;

    // uplinkPowerControlDedicated
public:
    UplinkPowerControlDedicated* uplinkPowerControlDedicated_Set();
    int uplinkPowerControlDedicated_Set(UplinkPowerControlDedicated &value);
    const UplinkPowerControlDedicated& uplinkPowerControlDedicated_Get() const;
    std::string uplinkPowerControlDedicated_ToString(uint32_t indent) const;
    std::string uplinkPowerControlDedicated_ToStringNoNewLines() const;
    int uplinkPowerControlDedicated_Clear();
    bool uplinkPowerControlDedicated_IsPresent() const;
private:
    bool uplinkPowerControlDedicated_present;
    UplinkPowerControlDedicated uplinkPowerControlDedicated;

    // tpc-PDCCH-ConfigPUCCH
public:
    TPC_PDCCH_Config* tpc_PDCCH_ConfigPUCCH_Set();
    int tpc_PDCCH_ConfigPUCCH_Set(TPC_PDCCH_Config &value);
    const TPC_PDCCH_Config& tpc_PDCCH_ConfigPUCCH_Get() const;
    std::string tpc_PDCCH_ConfigPUCCH_ToString(uint32_t indent) const;
    std::string tpc_PDCCH_ConfigPUCCH_ToStringNoNewLines() const;
    int tpc_PDCCH_ConfigPUCCH_Clear();
    bool tpc_PDCCH_ConfigPUCCH_IsPresent() const;
private:
    bool tpc_PDCCH_ConfigPUCCH_present;
    TPC_PDCCH_Config tpc_PDCCH_ConfigPUCCH;

    // tpc-PDCCH-ConfigPUSCH
public:
    TPC_PDCCH_Config* tpc_PDCCH_ConfigPUSCH_Set();
    int tpc_PDCCH_ConfigPUSCH_Set(TPC_PDCCH_Config &value);
    const TPC_PDCCH_Config& tpc_PDCCH_ConfigPUSCH_Get() const;
    std::string tpc_PDCCH_ConfigPUSCH_ToString(uint32_t indent) const;
    std::string tpc_PDCCH_ConfigPUSCH_ToStringNoNewLines() const;
    int tpc_PDCCH_ConfigPUSCH_Clear();
    bool tpc_PDCCH_ConfigPUSCH_IsPresent() const;
private:
    bool tpc_PDCCH_ConfigPUSCH_present;
    TPC_PDCCH_Config tpc_PDCCH_ConfigPUSCH;

    // cqi-ReportConfig
public:
    CQI_ReportConfig* cqi_ReportConfig_Set();
    int cqi_ReportConfig_Set(CQI_ReportConfig &value);
    const CQI_ReportConfig& cqi_ReportConfig_Get() const;
    std::string cqi_ReportConfig_ToString(uint32_t indent) const;
    std::string cqi_ReportConfig_ToStringNoNewLines() const;
    int cqi_ReportConfig_Clear();
    bool cqi_ReportConfig_IsPresent() const;
private:
    bool cqi_ReportConfig_present;
    CQI_ReportConfig cqi_ReportConfig;

    // soundingRS-UL-ConfigDedicated
public:
    SoundingRS_UL_ConfigDedicated* soundingRS_UL_ConfigDedicated_Set();
    int soundingRS_UL_ConfigDedicated_Set(SoundingRS_UL_ConfigDedicated &value);
    const SoundingRS_UL_ConfigDedicated& soundingRS_UL_ConfigDedicated_Get() const;
    std::string soundingRS_UL_ConfigDedicated_ToString(uint32_t indent) const;
    std::string soundingRS_UL_ConfigDedicated_ToStringNoNewLines() const;
    int soundingRS_UL_ConfigDedicated_Clear();
    bool soundingRS_UL_ConfigDedicated_IsPresent() const;
private:
    bool soundingRS_UL_ConfigDedicated_present;
    SoundingRS_UL_ConfigDedicated soundingRS_UL_ConfigDedicated;

    // antennaInfo
public:
    enum antennaInfo_Enum {
        k_antennaInfo_explicitValue = 0,
        k_antennaInfo_defaultValue,
    };
    int antennaInfo_Pack(std::vector<uint8_t> &bits);
    int antennaInfo_Unpack(std::vector<uint8_t> bits);
    int antennaInfo_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    antennaInfo_Enum antennaInfo_Choice() const;
    int antennaInfo_SetChoice(antennaInfo_Enum choice);
    std::string antennaInfo_ChoiceToString(antennaInfo_Enum value) const;
    uint64_t antennaInfo_NumberOfChoices() const;
    std::string antennaInfo_ToString(uint32_t indent) const;
    std::string antennaInfo_ToStringNoNewLines() const;
    int antennaInfo_Clear();
    bool antennaInfo_IsPresent() const;
private:
    bool antennaInfo_present;
    antennaInfo_Enum antennaInfo_internal_choice;

    // explicitValue
public:
    AntennaInfoDedicated* antennaInfo_explicitValue_Set();
    int antennaInfo_explicitValue_Set(AntennaInfoDedicated &value);
    const AntennaInfoDedicated& antennaInfo_explicitValue_Get() const;
    std::string antennaInfo_explicitValue_ToString(uint32_t indent) const;
    std::string antennaInfo_explicitValue_ToStringNoNewLines() const;
    int antennaInfo_explicitValue_Clear();
    bool antennaInfo_explicitValue_IsPresent() const;
private:
    bool antennaInfo_explicitValue_present;
    AntennaInfoDedicated antennaInfo_explicitValue;

    // defaultValue
public:
    int antennaInfo_defaultValue_Pack(std::vector<uint8_t> &bits) {return 0;};
    int antennaInfo_defaultValue_Unpack(std::vector<uint8_t> bits) {return 0;};
    int antennaInfo_defaultValue_Unpack(std::vector<uint8_t> bits, uint32_t &idx) {return 0;};
    bool antennaInfo_defaultValue_IsPresent() const {return true;};
    std::string antennaInfo_defaultValue_ToString(uint32_t indent) {return "";};
    std::string antennaInfo_defaultValue_ToStringNoNewLines() {return "";};


    // schedulingRequestConfig
public:
    SchedulingRequestConfig* schedulingRequestConfig_Set();
    int schedulingRequestConfig_Set(SchedulingRequestConfig &value);
    const SchedulingRequestConfig& schedulingRequestConfig_Get() const;
    std::string schedulingRequestConfig_ToString(uint32_t indent) const;
    std::string schedulingRequestConfig_ToStringNoNewLines() const;
    int schedulingRequestConfig_Clear();
    bool schedulingRequestConfig_IsPresent() const;
private:
    bool schedulingRequestConfig_present;
    SchedulingRequestConfig schedulingRequestConfig;

    // cqi-ReportConfig-v920
public:
    CQI_ReportConfig_v920* cqi_ReportConfig_v920_Set();
    int cqi_ReportConfig_v920_Set(CQI_ReportConfig_v920 &value);
    const CQI_ReportConfig_v920& cqi_ReportConfig_v920_Get() const;
    std::string cqi_ReportConfig_v920_ToString(uint32_t indent) const;
    std::string cqi_ReportConfig_v920_ToStringNoNewLines() const;
    int cqi_ReportConfig_v920_Clear();
    bool cqi_ReportConfig_v920_IsPresent() const;
private:
    bool cqi_ReportConfig_v920_present;
    CQI_ReportConfig_v920 cqi_ReportConfig_v920;

    // antennaInfo-v920
public:
    AntennaInfoDedicated_v920* antennaInfo_v920_Set();
    int antennaInfo_v920_Set(AntennaInfoDedicated_v920 &value);
    const AntennaInfoDedicated_v920& antennaInfo_v920_Get() const;
    std::string antennaInfo_v920_ToString(uint32_t indent) const;
    std::string antennaInfo_v920_ToStringNoNewLines() const;
    int antennaInfo_v920_Clear();
    bool antennaInfo_v920_IsPresent() const;
private:
    bool antennaInfo_v920_present;
    AntennaInfoDedicated_v920 antennaInfo_v920;

    // antennaInfo-r10
public:
    enum antennaInfo_r10_Enum {
        k_antennaInfo_r10_explicitValue = 0,
        k_antennaInfo_r10_defaultValue,
    };
    int antennaInfo_r10_Pack(std::vector<uint8_t> &bits);
    int antennaInfo_r10_Unpack(std::vector<uint8_t> bits);
    int antennaInfo_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    antennaInfo_r10_Enum antennaInfo_r10_Choice() const;
    int antennaInfo_r10_SetChoice(antennaInfo_r10_Enum choice);
    std::string antennaInfo_r10_ChoiceToString(antennaInfo_r10_Enum value) const;
    uint64_t antennaInfo_r10_NumberOfChoices() const;
    std::string antennaInfo_r10_ToString(uint32_t indent) const;
    std::string antennaInfo_r10_ToStringNoNewLines() const;
    int antennaInfo_r10_Clear();
    bool antennaInfo_r10_IsPresent() const;
private:
    bool antennaInfo_r10_present;
    antennaInfo_r10_Enum antennaInfo_r10_internal_choice;

    // explicitValue
public:
    AntennaInfoDedicated_r10* antennaInfo_r10_explicitValue_Set();
    int antennaInfo_r10_explicitValue_Set(AntennaInfoDedicated_r10 &value);
    const AntennaInfoDedicated_r10& antennaInfo_r10_explicitValue_Get() const;
    std::string antennaInfo_r10_explicitValue_ToString(uint32_t indent) const;
    std::string antennaInfo_r10_explicitValue_ToStringNoNewLines() const;
    int antennaInfo_r10_explicitValue_Clear();
    bool antennaInfo_r10_explicitValue_IsPresent() const;
private:
    bool antennaInfo_r10_explicitValue_present;
    AntennaInfoDedicated_r10 antennaInfo_r10_explicitValue;

    // defaultValue
public:
    int antennaInfo_r10_defaultValue_Pack(std::vector<uint8_t> &bits) {return 0;};
    int antennaInfo_r10_defaultValue_Unpack(std::vector<uint8_t> bits) {return 0;};
    int antennaInfo_r10_defaultValue_Unpack(std::vector<uint8_t> bits, uint32_t &idx) {return 0;};
    bool antennaInfo_r10_defaultValue_IsPresent() const {return true;};
    std::string antennaInfo_r10_defaultValue_ToString(uint32_t indent) {return "";};
    std::string antennaInfo_r10_defaultValue_ToStringNoNewLines() {return "";};


    // cif-Presence
public:
    int cif_Presence_Pack(std::vector<uint8_t> &bits);
    int cif_Presence_Unpack(std::vector<uint8_t> bits);
    int cif_Presence_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    bool cif_Presence_Value() const;
    int cif_Presence_SetValue(bool value);
    std::string cif_Presence_ToString(uint32_t indent) const;
    std::string cif_Presence_ToStringNoNewLines() const;
    int cif_Presence_Clear();
    bool cif_Presence_IsPresent() const;
private:
    bool cif_Presence_present;
    bool cif_Presence_internal_value;

    // cqi-ReportConfig-v10x0
public:
    CQI_ReportConfig_v10x0* cqi_ReportConfig_v10x0_Set();
    int cqi_ReportConfig_v10x0_Set(CQI_ReportConfig_v10x0 &value);
    const CQI_ReportConfig_v10x0& cqi_ReportConfig_v10x0_Get() const;
    std::string cqi_ReportConfig_v10x0_ToString(uint32_t indent) const;
    std::string cqi_ReportConfig_v10x0_ToStringNoNewLines() const;
    int cqi_ReportConfig_v10x0_Clear();
    bool cqi_ReportConfig_v10x0_IsPresent() const;
private:
    bool cqi_ReportConfig_v10x0_present;
    CQI_ReportConfig_v10x0 cqi_ReportConfig_v10x0;

    // csi-RS-Config-r10
public:
    CSI_RS_Config_r10* csi_RS_Config_r10_Set();
    int csi_RS_Config_r10_Set(CSI_RS_Config_r10 &value);
    const CSI_RS_Config_r10& csi_RS_Config_r10_Get() const;
    std::string csi_RS_Config_r10_ToString(uint32_t indent) const;
    std::string csi_RS_Config_r10_ToStringNoNewLines() const;
    int csi_RS_Config_r10_Clear();
    bool csi_RS_Config_r10_IsPresent() const;
private:
    bool csi_RS_Config_r10_present;
    CSI_RS_Config_r10 csi_RS_Config_r10;

    // pucch-ConfigDedicated-v10x0
public:
    PUCCH_ConfigDedicated_v10x0* pucch_ConfigDedicated_v10x0_Set();
    int pucch_ConfigDedicated_v10x0_Set(PUCCH_ConfigDedicated_v10x0 &value);
    const PUCCH_ConfigDedicated_v10x0& pucch_ConfigDedicated_v10x0_Get() const;
    std::string pucch_ConfigDedicated_v10x0_ToString(uint32_t indent) const;
    std::string pucch_ConfigDedicated_v10x0_ToStringNoNewLines() const;
    int pucch_ConfigDedicated_v10x0_Clear();
    bool pucch_ConfigDedicated_v10x0_IsPresent() const;
private:
    bool pucch_ConfigDedicated_v10x0_present;
    PUCCH_ConfigDedicated_v10x0 pucch_ConfigDedicated_v10x0;

    // pusch-ConfigDedicated-v10x0
public:
    PUSCH_ConfigDedicated_v10x0* pusch_ConfigDedicated_v10x0_Set();
    int pusch_ConfigDedicated_v10x0_Set(PUSCH_ConfigDedicated_v10x0 &value);
    const PUSCH_ConfigDedicated_v10x0& pusch_ConfigDedicated_v10x0_Get() const;
    std::string pusch_ConfigDedicated_v10x0_ToString(uint32_t indent) const;
    std::string pusch_ConfigDedicated_v10x0_ToStringNoNewLines() const;
    int pusch_ConfigDedicated_v10x0_Clear();
    bool pusch_ConfigDedicated_v10x0_IsPresent() const;
private:
    bool pusch_ConfigDedicated_v10x0_present;
    PUSCH_ConfigDedicated_v10x0 pusch_ConfigDedicated_v10x0;

    // schedulingRequestConfig-v10x0
public:
    SchedulingRequestConfig_v10x0* schedulingRequestConfig_v10x0_Set();
    int schedulingRequestConfig_v10x0_Set(SchedulingRequestConfig_v10x0 &value);
    const SchedulingRequestConfig_v10x0& schedulingRequestConfig_v10x0_Get() const;
    std::string schedulingRequestConfig_v10x0_ToString(uint32_t indent) const;
    std::string schedulingRequestConfig_v10x0_ToStringNoNewLines() const;
    int schedulingRequestConfig_v10x0_Clear();
    bool schedulingRequestConfig_v10x0_IsPresent() const;
private:
    bool schedulingRequestConfig_v10x0_present;
    SchedulingRequestConfig_v10x0 schedulingRequestConfig_v10x0;

    // soundingRS-UL-ConfigDedicated-v10x0
public:
    SoundingRS_UL_ConfigDedicated_v10x0* soundingRS_UL_ConfigDedicated_v10x0_Set();
    int soundingRS_UL_ConfigDedicated_v10x0_Set(SoundingRS_UL_ConfigDedicated_v10x0 &value);
    const SoundingRS_UL_ConfigDedicated_v10x0& soundingRS_UL_ConfigDedicated_v10x0_Get() const;
    std::string soundingRS_UL_ConfigDedicated_v10x0_ToString(uint32_t indent) const;
    std::string soundingRS_UL_ConfigDedicated_v10x0_ToStringNoNewLines() const;
    int soundingRS_UL_ConfigDedicated_v10x0_Clear();
    bool soundingRS_UL_ConfigDedicated_v10x0_IsPresent() const;
private:
    bool soundingRS_UL_ConfigDedicated_v10x0_present;
    SoundingRS_UL_ConfigDedicated_v10x0 soundingRS_UL_ConfigDedicated_v10x0;

    // soundingRS-UL-ConfigDedicatedAperiodic-r10
public:
    SoundingRS_UL_ConfigDedicatedAperiodic_r10* soundingRS_UL_ConfigDedicatedAperiodic_r10_Set();
    int soundingRS_UL_ConfigDedicatedAperiodic_r10_Set(SoundingRS_UL_ConfigDedicatedAperiodic_r10 &value);
    const SoundingRS_UL_ConfigDedicatedAperiodic_r10& soundingRS_UL_ConfigDedicatedAperiodic_r10_Get() const;
    std::string soundingRS_UL_ConfigDedicatedAperiodic_r10_ToString(uint32_t indent) const;
    std::string soundingRS_UL_ConfigDedicatedAperiodic_r10_ToStringNoNewLines() const;
    int soundingRS_UL_ConfigDedicatedAperiodic_r10_Clear();
    bool soundingRS_UL_ConfigDedicatedAperiodic_r10_IsPresent() const;
private:
    bool soundingRS_UL_ConfigDedicatedAperiodic_r10_present;
    SoundingRS_UL_ConfigDedicatedAperiodic_r10 soundingRS_UL_ConfigDedicatedAperiodic_r10;

    // ul-AntennaInfo-r10
public:
    UL_AntennaInfo_r10* ul_AntennaInfo_r10_Set();
    int ul_AntennaInfo_r10_Set(UL_AntennaInfo_r10 &value);
    const UL_AntennaInfo_r10& ul_AntennaInfo_r10_Get() const;
    std::string ul_AntennaInfo_r10_ToString(uint32_t indent) const;
    std::string ul_AntennaInfo_r10_ToStringNoNewLines() const;
    int ul_AntennaInfo_r10_Clear();
    bool ul_AntennaInfo_r10_IsPresent() const;
private:
    bool ul_AntennaInfo_r10_present;
    UL_AntennaInfo_r10 ul_AntennaInfo_r10;

};

#endif
