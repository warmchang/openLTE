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

#ifndef __RadioResourceConfigCommonSCell_r10_H__
#define __RadioResourceConfigCommonSCell_r10_H__

#include "AntennaInfoCommon.h"
#include "MBSFN_SubframeConfigList.h"
#include "PHICH_Config.h"
#include "PDSCH_ConfigCommon.h"
#include "ARFCN_ValueEUTRA.h"
#include "AdditionalSpectrumEmission.h"
#include "P_Max.h"
#include "UplinkPowerControlCommonSCell_r10.h"
#include "SoundingRS_UL_ConfigCommon.h"
#include "UL_CyclicPrefixLength.h"
#include "PRACH_ConfigSCell_r10.h"
#include "PUSCH_ConfigCommon.h"

#include <array>
#include <cstdint>
#include <vector>

class RadioResourceConfigCommonSCell_r10
{
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
        nonUL_Configuration() : dl_Bandwidth_r10_present{false}, antennaInfoCommon_r10_present{false}, mbsfn_SubframeConfigList_r10_present{false}, phich_Config_r10_present{false}, pdsch_ConfigCommon_r10_present{false} {};
    public:
        int Pack(std::vector<uint8_t> &bits);
        int Unpack(std::vector<uint8_t> bits);
        int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        std::string ToString(uint32_t indent) const;
        std::string ToStringNoNewLines() const;

        // dl-Bandwidth-r10
    public:
        enum dl_Bandwidth_r10_Enum {
            k_dl_Bandwidth_r10_n6 = 0,
            k_dl_Bandwidth_r10_n15,
            k_dl_Bandwidth_r10_n25,
            k_dl_Bandwidth_r10_n50,
            k_dl_Bandwidth_r10_n75,
            k_dl_Bandwidth_r10_n100,
        };
        int dl_Bandwidth_r10_Pack(std::vector<uint8_t> &bits);
        int dl_Bandwidth_r10_Unpack(std::vector<uint8_t> bits);
        int dl_Bandwidth_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        dl_Bandwidth_r10_Enum dl_Bandwidth_r10_Value() const;
        int dl_Bandwidth_r10_SetValue(dl_Bandwidth_r10_Enum value);
        int dl_Bandwidth_r10_SetValue(std::string value);
        std::string dl_Bandwidth_r10_ValueToString(dl_Bandwidth_r10_Enum value) const;
        uint64_t dl_Bandwidth_r10_NumberOfValues() const;
        std::string dl_Bandwidth_r10_ToString(uint32_t indent) const;
        std::string dl_Bandwidth_r10_ToStringNoNewLines() const;
        int dl_Bandwidth_r10_Clear();
        bool dl_Bandwidth_r10_IsPresent() const;
    private:
        bool dl_Bandwidth_r10_present;
        dl_Bandwidth_r10_Enum dl_Bandwidth_r10_internal_value;

        // antennaInfoCommon-r10
    public:
        AntennaInfoCommon* antennaInfoCommon_r10_Set();
        int antennaInfoCommon_r10_Set(AntennaInfoCommon &value);
        const AntennaInfoCommon& antennaInfoCommon_r10_Get() const;
        std::string antennaInfoCommon_r10_ToString(uint32_t indent) const;
        std::string antennaInfoCommon_r10_ToStringNoNewLines() const;
        int antennaInfoCommon_r10_Clear();
        bool antennaInfoCommon_r10_IsPresent() const;
    private:
        bool antennaInfoCommon_r10_present;
        AntennaInfoCommon antennaInfoCommon_r10;

        // mbsfn-SubframeConfigList-r10
    public:
        MBSFN_SubframeConfigList* mbsfn_SubframeConfigList_r10_Set();
        int mbsfn_SubframeConfigList_r10_Set(MBSFN_SubframeConfigList &value);
        const MBSFN_SubframeConfigList& mbsfn_SubframeConfigList_r10_Get() const;
        std::string mbsfn_SubframeConfigList_r10_ToString(uint32_t indent) const;
        std::string mbsfn_SubframeConfigList_r10_ToStringNoNewLines() const;
        int mbsfn_SubframeConfigList_r10_Clear();
        bool mbsfn_SubframeConfigList_r10_IsPresent() const;
    private:
        bool mbsfn_SubframeConfigList_r10_present;
        MBSFN_SubframeConfigList mbsfn_SubframeConfigList_r10;

        // phich-Config-r10
    public:
        PHICH_Config* phich_Config_r10_Set();
        int phich_Config_r10_Set(PHICH_Config &value);
        const PHICH_Config& phich_Config_r10_Get() const;
        std::string phich_Config_r10_ToString(uint32_t indent) const;
        std::string phich_Config_r10_ToStringNoNewLines() const;
        int phich_Config_r10_Clear();
        bool phich_Config_r10_IsPresent() const;
    private:
        bool phich_Config_r10_present;
        PHICH_Config phich_Config_r10;

        // pdsch-ConfigCommon-r10
    public:
        PDSCH_ConfigCommon* pdsch_ConfigCommon_r10_Set();
        int pdsch_ConfigCommon_r10_Set(PDSCH_ConfigCommon &value);
        const PDSCH_ConfigCommon& pdsch_ConfigCommon_r10_Get() const;
        std::string pdsch_ConfigCommon_r10_ToString(uint32_t indent) const;
        std::string pdsch_ConfigCommon_r10_ToStringNoNewLines() const;
        int pdsch_ConfigCommon_r10_Clear();
        bool pdsch_ConfigCommon_r10_IsPresent() const;
    private:
        bool pdsch_ConfigCommon_r10_present;
        PDSCH_ConfigCommon pdsch_ConfigCommon_r10;

    };

    nonUL_Configuration nonUL_Configuration_value;

    // ul-Configuration
public:
    class ul_Configuration
    {
    public:
        ul_Configuration() : present{false}, p_Max_r10_present{false}, uplinkPowerControlCommon_r10_present{false}, soundingRS_UL_ConfigCommon_r10_present{false}, ul_CyclicPrefixLength_r10_present{false}, prach_Config_present{false}, pusch_ConfigCommon_r10_present{false} {};
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

        // ul-FreqInfo-r10
    public:
        class ul_FreqInfo_r10
        {
        public:
            ul_FreqInfo_r10() : ul_CarrierFreq_r10_present{false}, ul_Bandwidth_r10_present{false}, additionalSpectrumEmission_r10_present{false} {};
        public:
            int Pack(std::vector<uint8_t> &bits);
            int Unpack(std::vector<uint8_t> bits);
            int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
            std::string ToString(uint32_t indent) const;
            std::string ToStringNoNewLines() const;

            // ul-CarrierFreq-r10
        public:
            ARFCN_ValueEUTRA* ul_CarrierFreq_r10_Set();
            int ul_CarrierFreq_r10_Set(ARFCN_ValueEUTRA &value);
            const ARFCN_ValueEUTRA& ul_CarrierFreq_r10_Get() const;
            std::string ul_CarrierFreq_r10_ToString(uint32_t indent) const;
            std::string ul_CarrierFreq_r10_ToStringNoNewLines() const;
            int ul_CarrierFreq_r10_Clear();
            bool ul_CarrierFreq_r10_IsPresent() const;
        private:
            bool ul_CarrierFreq_r10_present;
            ARFCN_ValueEUTRA ul_CarrierFreq_r10;

            // ul-Bandwidth-r10
        public:
            enum ul_Bandwidth_r10_Enum {
                k_ul_Bandwidth_r10_n6 = 0,
                k_ul_Bandwidth_r10_n15,
                k_ul_Bandwidth_r10_n25,
                k_ul_Bandwidth_r10_n50,
                k_ul_Bandwidth_r10_n75,
                k_ul_Bandwidth_r10_n100,
            };
            int ul_Bandwidth_r10_Pack(std::vector<uint8_t> &bits);
            int ul_Bandwidth_r10_Unpack(std::vector<uint8_t> bits);
            int ul_Bandwidth_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
            ul_Bandwidth_r10_Enum ul_Bandwidth_r10_Value() const;
            int ul_Bandwidth_r10_SetValue(ul_Bandwidth_r10_Enum value);
            int ul_Bandwidth_r10_SetValue(std::string value);
            std::string ul_Bandwidth_r10_ValueToString(ul_Bandwidth_r10_Enum value) const;
            uint64_t ul_Bandwidth_r10_NumberOfValues() const;
            std::string ul_Bandwidth_r10_ToString(uint32_t indent) const;
            std::string ul_Bandwidth_r10_ToStringNoNewLines() const;
            int ul_Bandwidth_r10_Clear();
            bool ul_Bandwidth_r10_IsPresent() const;
        private:
            bool ul_Bandwidth_r10_present;
            ul_Bandwidth_r10_Enum ul_Bandwidth_r10_internal_value;

            // additionalSpectrumEmission-r10
        public:
            AdditionalSpectrumEmission* additionalSpectrumEmission_r10_Set();
            int additionalSpectrumEmission_r10_Set(AdditionalSpectrumEmission &value);
            const AdditionalSpectrumEmission& additionalSpectrumEmission_r10_Get() const;
            std::string additionalSpectrumEmission_r10_ToString(uint32_t indent) const;
            std::string additionalSpectrumEmission_r10_ToStringNoNewLines() const;
            int additionalSpectrumEmission_r10_Clear();
            bool additionalSpectrumEmission_r10_IsPresent() const;
        private:
            bool additionalSpectrumEmission_r10_present;
            AdditionalSpectrumEmission additionalSpectrumEmission_r10;

        };

        ul_FreqInfo_r10 ul_FreqInfo_r10_value;

        // p-Max-r10
    public:
        P_Max* p_Max_r10_Set();
        int p_Max_r10_Set(P_Max &value);
        const P_Max& p_Max_r10_Get() const;
        std::string p_Max_r10_ToString(uint32_t indent) const;
        std::string p_Max_r10_ToStringNoNewLines() const;
        int p_Max_r10_Clear();
        bool p_Max_r10_IsPresent() const;
    private:
        bool p_Max_r10_present;
        P_Max p_Max_r10;

        // uplinkPowerControlCommon-r10
    public:
        UplinkPowerControlCommonSCell_r10* uplinkPowerControlCommon_r10_Set();
        int uplinkPowerControlCommon_r10_Set(UplinkPowerControlCommonSCell_r10 &value);
        const UplinkPowerControlCommonSCell_r10& uplinkPowerControlCommon_r10_Get() const;
        std::string uplinkPowerControlCommon_r10_ToString(uint32_t indent) const;
        std::string uplinkPowerControlCommon_r10_ToStringNoNewLines() const;
        int uplinkPowerControlCommon_r10_Clear();
        bool uplinkPowerControlCommon_r10_IsPresent() const;
    private:
        bool uplinkPowerControlCommon_r10_present;
        UplinkPowerControlCommonSCell_r10 uplinkPowerControlCommon_r10;

        // soundingRS-UL-ConfigCommon-r10
    public:
        SoundingRS_UL_ConfigCommon* soundingRS_UL_ConfigCommon_r10_Set();
        int soundingRS_UL_ConfigCommon_r10_Set(SoundingRS_UL_ConfigCommon &value);
        const SoundingRS_UL_ConfigCommon& soundingRS_UL_ConfigCommon_r10_Get() const;
        std::string soundingRS_UL_ConfigCommon_r10_ToString(uint32_t indent) const;
        std::string soundingRS_UL_ConfigCommon_r10_ToStringNoNewLines() const;
        int soundingRS_UL_ConfigCommon_r10_Clear();
        bool soundingRS_UL_ConfigCommon_r10_IsPresent() const;
    private:
        bool soundingRS_UL_ConfigCommon_r10_present;
        SoundingRS_UL_ConfigCommon soundingRS_UL_ConfigCommon_r10;

        // ul-CyclicPrefixLength-r10
    public:
        UL_CyclicPrefixLength* ul_CyclicPrefixLength_r10_Set();
        int ul_CyclicPrefixLength_r10_Set(UL_CyclicPrefixLength &value);
        const UL_CyclicPrefixLength& ul_CyclicPrefixLength_r10_Get() const;
        std::string ul_CyclicPrefixLength_r10_ToString(uint32_t indent) const;
        std::string ul_CyclicPrefixLength_r10_ToStringNoNewLines() const;
        int ul_CyclicPrefixLength_r10_Clear();
        bool ul_CyclicPrefixLength_r10_IsPresent() const;
    private:
        bool ul_CyclicPrefixLength_r10_present;
        UL_CyclicPrefixLength ul_CyclicPrefixLength_r10;

        // prach-Config
    public:
        PRACH_ConfigSCell_r10* prach_Config_Set();
        int prach_Config_Set(PRACH_ConfigSCell_r10 &value);
        const PRACH_ConfigSCell_r10& prach_Config_Get() const;
        std::string prach_Config_ToString(uint32_t indent) const;
        std::string prach_Config_ToStringNoNewLines() const;
        int prach_Config_Clear();
        bool prach_Config_IsPresent() const;
    private:
        bool prach_Config_present;
        PRACH_ConfigSCell_r10 prach_Config;

        // pusch-ConfigCommon-r10
    public:
        PUSCH_ConfigCommon* pusch_ConfigCommon_r10_Set();
        int pusch_ConfigCommon_r10_Set(PUSCH_ConfigCommon &value);
        const PUSCH_ConfigCommon& pusch_ConfigCommon_r10_Get() const;
        std::string pusch_ConfigCommon_r10_ToString(uint32_t indent) const;
        std::string pusch_ConfigCommon_r10_ToStringNoNewLines() const;
        int pusch_ConfigCommon_r10_Clear();
        bool pusch_ConfigCommon_r10_IsPresent() const;
    private:
        bool pusch_ConfigCommon_r10_present;
        PUSCH_ConfigCommon pusch_ConfigCommon_r10;

    };

    ul_Configuration ul_Configuration_value;

};

#endif
