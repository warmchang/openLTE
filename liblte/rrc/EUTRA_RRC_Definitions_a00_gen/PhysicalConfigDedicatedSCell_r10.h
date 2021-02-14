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

#ifndef __PhysicalConfigDedicatedSCell_r10_H__
#define __PhysicalConfigDedicatedSCell_r10_H__

#include "AntennaInfoDedicated_r10.h"
#include "CrossCarrierSchedulingConfig_r10.h"
#include "CSI_RS_Config_r10.h"
#include "PDSCH_ConfigDedicated.h"
#include "PUSCH_ConfigDedicated.h"
#include "PUSCH_ConfigDedicated_v10x0.h"
#include "UplinkPowerControlDedicatedSCell_r10.h"
#include "CQI_ReportConfigSCell_r10.h"
#include "SoundingRS_UL_ConfigDedicated.h"
#include "SoundingRS_UL_ConfigDedicated_v10x0.h"
#include "SoundingRS_UL_ConfigDedicatedAperiodic_r10.h"
#include "UL_AntennaInfo_r10.h"

#include <array>
#include <cstdint>
#include <vector>

class PhysicalConfigDedicatedSCell_r10
{
public:
    PhysicalConfigDedicatedSCell_r10() : ul_Configuration_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // nonUL-Configuration
public:
    class nonUL_Configuration
    {
    public:
        nonUL_Configuration() : present{false}, antennaInfo_r10_present{false}, crossCarrierSchedulingConfig_r10_present{false}, csi_RS_Config_r10_present{false}, pdsch_ConfigDedicated_r10_present{false} {};
    public:
        int Pack(std::vector<uint8_t> &bits);
        int Unpack(std::vector<uint8_t> bits);
        int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        std::string ToString(uint32_t indent) const;
        std::string ToStringNoNewLines() const;
        int Set();
        int SetPresence(bool is_present);
        int Clear();
        bool IsPresent() const;
    private:
        bool present;

        // antennaInfo-r10
    public:
        AntennaInfoDedicated_r10* antennaInfo_r10_Set();
        int antennaInfo_r10_Set(AntennaInfoDedicated_r10 &value);
        const AntennaInfoDedicated_r10& antennaInfo_r10_Get() const;
        std::string antennaInfo_r10_ToString(uint32_t indent) const;
        std::string antennaInfo_r10_ToStringNoNewLines() const;
        int antennaInfo_r10_Clear();
        bool antennaInfo_r10_IsPresent() const;
    private:
        bool antennaInfo_r10_present;
        AntennaInfoDedicated_r10 antennaInfo_r10;

        // crossCarrierSchedulingConfig-r10
    public:
        CrossCarrierSchedulingConfig_r10* crossCarrierSchedulingConfig_r10_Set();
        int crossCarrierSchedulingConfig_r10_Set(CrossCarrierSchedulingConfig_r10 &value);
        const CrossCarrierSchedulingConfig_r10& crossCarrierSchedulingConfig_r10_Get() const;
        std::string crossCarrierSchedulingConfig_r10_ToString(uint32_t indent) const;
        std::string crossCarrierSchedulingConfig_r10_ToStringNoNewLines() const;
        int crossCarrierSchedulingConfig_r10_Clear();
        bool crossCarrierSchedulingConfig_r10_IsPresent() const;
    private:
        bool crossCarrierSchedulingConfig_r10_present;
        CrossCarrierSchedulingConfig_r10 crossCarrierSchedulingConfig_r10;

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

        // pdsch-ConfigDedicated-r10
    public:
        PDSCH_ConfigDedicated* pdsch_ConfigDedicated_r10_Set();
        int pdsch_ConfigDedicated_r10_Set(PDSCH_ConfigDedicated &value);
        const PDSCH_ConfigDedicated& pdsch_ConfigDedicated_r10_Get() const;
        std::string pdsch_ConfigDedicated_r10_ToString(uint32_t indent) const;
        std::string pdsch_ConfigDedicated_r10_ToStringNoNewLines() const;
        int pdsch_ConfigDedicated_r10_Clear();
        bool pdsch_ConfigDedicated_r10_IsPresent() const;
    private:
        bool pdsch_ConfigDedicated_r10_present;
        PDSCH_ConfigDedicated pdsch_ConfigDedicated_r10;

    };

    nonUL_Configuration nonUL_Configuration_value;

    // ul-Configuration
public:
    enum ul_Configuration_Enum {
        k_ul_Configuration_release = 0,
        k_ul_Configuration_setup,
    };
    int ul_Configuration_Pack(std::vector<uint8_t> &bits);
    int ul_Configuration_Unpack(std::vector<uint8_t> bits);
    int ul_Configuration_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    ul_Configuration_Enum ul_Configuration_Choice() const;
    int ul_Configuration_SetChoice(ul_Configuration_Enum choice);
    std::string ul_Configuration_ChoiceToString(ul_Configuration_Enum value) const;
    uint64_t ul_Configuration_NumberOfChoices() const;
    std::string ul_Configuration_ToString(uint32_t indent) const;
    std::string ul_Configuration_ToStringNoNewLines() const;
    int ul_Configuration_Clear();
    bool ul_Configuration_IsPresent() const;
private:
    bool ul_Configuration_present;
    ul_Configuration_Enum ul_Configuration_internal_choice;

    // release
public:
    int ul_Configuration_release_Pack(std::vector<uint8_t> &bits) {return 0;};
    int ul_Configuration_release_Unpack(std::vector<uint8_t> bits) {return 0;};
    int ul_Configuration_release_Unpack(std::vector<uint8_t> bits, uint32_t &idx) {return 0;};
    bool ul_Configuration_release_IsPresent() const {return true;};
    std::string ul_Configuration_release_ToString(uint32_t indent) {return "";};
    std::string ul_Configuration_release_ToStringNoNewLines() {return "";};

    // setup
public:
    class ul_Configuration_setup
    {
    public:
        ul_Configuration_setup() : pusch_ConfigDedicated_r10_present{false}, pusch_ConfigDedicated_v10x0_present{false}, uplinkPowerControlDedicated_r10_present{false}, cqi_ReportConfig_r10_present{false}, soundingRS_UL_ConfigDedicated_r10_present{false}, soundingRS_UL_ConfigDedicated_v10x0_present{false}, soundingRS_UL_ConfigDedicatedAperiodic_r10_present{false}, ul_AntennaInfo_r10_present{false} {};
    public:
        int Pack(std::vector<uint8_t> &bits);
        int Unpack(std::vector<uint8_t> bits);
        int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        std::string ToString(uint32_t indent) const;
        std::string ToStringNoNewLines() const;

        // pusch-ConfigDedicated-r10
    public:
        PUSCH_ConfigDedicated* pusch_ConfigDedicated_r10_Set();
        int pusch_ConfigDedicated_r10_Set(PUSCH_ConfigDedicated &value);
        const PUSCH_ConfigDedicated& pusch_ConfigDedicated_r10_Get() const;
        std::string pusch_ConfigDedicated_r10_ToString(uint32_t indent) const;
        std::string pusch_ConfigDedicated_r10_ToStringNoNewLines() const;
        int pusch_ConfigDedicated_r10_Clear();
        bool pusch_ConfigDedicated_r10_IsPresent() const;
    private:
        bool pusch_ConfigDedicated_r10_present;
        PUSCH_ConfigDedicated pusch_ConfigDedicated_r10;

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

        // uplinkPowerControlDedicated-r10
    public:
        UplinkPowerControlDedicatedSCell_r10* uplinkPowerControlDedicated_r10_Set();
        int uplinkPowerControlDedicated_r10_Set(UplinkPowerControlDedicatedSCell_r10 &value);
        const UplinkPowerControlDedicatedSCell_r10& uplinkPowerControlDedicated_r10_Get() const;
        std::string uplinkPowerControlDedicated_r10_ToString(uint32_t indent) const;
        std::string uplinkPowerControlDedicated_r10_ToStringNoNewLines() const;
        int uplinkPowerControlDedicated_r10_Clear();
        bool uplinkPowerControlDedicated_r10_IsPresent() const;
    private:
        bool uplinkPowerControlDedicated_r10_present;
        UplinkPowerControlDedicatedSCell_r10 uplinkPowerControlDedicated_r10;

        // cqi-ReportConfig-r10
    public:
        CQI_ReportConfigSCell_r10* cqi_ReportConfig_r10_Set();
        int cqi_ReportConfig_r10_Set(CQI_ReportConfigSCell_r10 &value);
        const CQI_ReportConfigSCell_r10& cqi_ReportConfig_r10_Get() const;
        std::string cqi_ReportConfig_r10_ToString(uint32_t indent) const;
        std::string cqi_ReportConfig_r10_ToStringNoNewLines() const;
        int cqi_ReportConfig_r10_Clear();
        bool cqi_ReportConfig_r10_IsPresent() const;
    private:
        bool cqi_ReportConfig_r10_present;
        CQI_ReportConfigSCell_r10 cqi_ReportConfig_r10;

        // soundingRS-UL-ConfigDedicated-r10
    public:
        SoundingRS_UL_ConfigDedicated* soundingRS_UL_ConfigDedicated_r10_Set();
        int soundingRS_UL_ConfigDedicated_r10_Set(SoundingRS_UL_ConfigDedicated &value);
        const SoundingRS_UL_ConfigDedicated& soundingRS_UL_ConfigDedicated_r10_Get() const;
        std::string soundingRS_UL_ConfigDedicated_r10_ToString(uint32_t indent) const;
        std::string soundingRS_UL_ConfigDedicated_r10_ToStringNoNewLines() const;
        int soundingRS_UL_ConfigDedicated_r10_Clear();
        bool soundingRS_UL_ConfigDedicated_r10_IsPresent() const;
    private:
        bool soundingRS_UL_ConfigDedicated_r10_present;
        SoundingRS_UL_ConfigDedicated soundingRS_UL_ConfigDedicated_r10;

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

    ul_Configuration_setup ul_Configuration_setup_value;


};

#endif
