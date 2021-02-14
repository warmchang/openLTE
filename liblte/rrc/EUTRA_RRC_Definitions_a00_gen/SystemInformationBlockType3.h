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

#ifndef __SystemInformationBlockType3_H__
#define __SystemInformationBlockType3_H__

#include "MobilityStateParameters.h"
#include "ReselectionThreshold.h"
#include "ReselectionThreshold.h"
#include "CellReselectionPriority.h"
#include "Q_RxLevMin.h"
#include "P_Max.h"
#include "ReselectionThreshold.h"
#include "AllowedMeasBandwidth.h"
#include "PresenceAntennaPort1.h"
#include "NeighCellConfig.h"
#include "T_Reselection.h"
#include "SpeedStateScaleFactors.h"
#include "ReselectionThreshold.h"
#include "ReselectionThresholdQ_r9.h"
#include "ReselectionThreshold.h"
#include "ReselectionThresholdQ_r9.h"
#include "Q_QualMin_r9.h"
#include "ReselectionThresholdQ_r9.h"

#include <array>
#include <cstdint>
#include <vector>

class SystemInformationBlockType3
{
public:
    SystemInformationBlockType3() : lateNonCriticalExtension_present{false}, q_QualMin_r9_present{false}, threshServingLowQ_r9_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // cellReselectionInfoCommon
public:
    class cellReselectionInfoCommon
    {
    public:
        cellReselectionInfoCommon() : q_Hyst_present{false} {};
    public:
        int Pack(std::vector<uint8_t> &bits);
        int Unpack(std::vector<uint8_t> bits);
        int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        std::string ToString(uint32_t indent) const;
        std::string ToStringNoNewLines() const;

        // q-Hyst
    public:
        enum q_Hyst_Enum {
            k_q_Hyst_dB0 = 0,
            k_q_Hyst_dB1,
            k_q_Hyst_dB2,
            k_q_Hyst_dB3,
            k_q_Hyst_dB4,
            k_q_Hyst_dB5,
            k_q_Hyst_dB6,
            k_q_Hyst_dB8,
            k_q_Hyst_dB10,
            k_q_Hyst_dB12,
            k_q_Hyst_dB14,
            k_q_Hyst_dB16,
            k_q_Hyst_dB18,
            k_q_Hyst_dB20,
            k_q_Hyst_dB22,
            k_q_Hyst_dB24,
        };
        int q_Hyst_Pack(std::vector<uint8_t> &bits);
        int q_Hyst_Unpack(std::vector<uint8_t> bits);
        int q_Hyst_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        q_Hyst_Enum q_Hyst_Value() const;
        int q_Hyst_SetValue(q_Hyst_Enum value);
        int q_Hyst_SetValue(std::string value);
        std::string q_Hyst_ValueToString(q_Hyst_Enum value) const;
        uint64_t q_Hyst_NumberOfValues() const;
        std::string q_Hyst_ToString(uint32_t indent) const;
        std::string q_Hyst_ToStringNoNewLines() const;
        int q_Hyst_Clear();
        bool q_Hyst_IsPresent() const;
    private:
        bool q_Hyst_present;
        q_Hyst_Enum q_Hyst_internal_value;

        // speedStateReselectionPars
    public:
        class speedStateReselectionPars
        {
        public:
            speedStateReselectionPars() : present{false}, mobilityStateParameters_present{false} {};
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

            // mobilityStateParameters
        public:
            MobilityStateParameters* mobilityStateParameters_Set();
            int mobilityStateParameters_Set(MobilityStateParameters &value);
            const MobilityStateParameters& mobilityStateParameters_Get() const;
            std::string mobilityStateParameters_ToString(uint32_t indent) const;
            std::string mobilityStateParameters_ToStringNoNewLines() const;
            int mobilityStateParameters_Clear();
            bool mobilityStateParameters_IsPresent() const;
        private:
            bool mobilityStateParameters_present;
            MobilityStateParameters mobilityStateParameters;

            // q-HystSF
        public:
            class q_HystSF
            {
            public:
                q_HystSF() : sf_Medium_present{false}, sf_High_present{false} {};
            public:
                int Pack(std::vector<uint8_t> &bits);
                int Unpack(std::vector<uint8_t> bits);
                int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
                std::string ToString(uint32_t indent) const;
                std::string ToStringNoNewLines() const;

                // sf-Medium
            public:
                enum sf_Medium_Enum {
                    k_sf_Medium_dB_6 = 0,
                    k_sf_Medium_dB_4,
                    k_sf_Medium_dB_2,
                    k_sf_Medium_dB0,
                };
                int sf_Medium_Pack(std::vector<uint8_t> &bits);
                int sf_Medium_Unpack(std::vector<uint8_t> bits);
                int sf_Medium_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
                sf_Medium_Enum sf_Medium_Value() const;
                int sf_Medium_SetValue(sf_Medium_Enum value);
                int sf_Medium_SetValue(std::string value);
                std::string sf_Medium_ValueToString(sf_Medium_Enum value) const;
                uint64_t sf_Medium_NumberOfValues() const;
                std::string sf_Medium_ToString(uint32_t indent) const;
                std::string sf_Medium_ToStringNoNewLines() const;
                int sf_Medium_Clear();
                bool sf_Medium_IsPresent() const;
            private:
                bool sf_Medium_present;
                sf_Medium_Enum sf_Medium_internal_value;

                // sf-High
            public:
                enum sf_High_Enum {
                    k_sf_High_dB_6 = 0,
                    k_sf_High_dB_4,
                    k_sf_High_dB_2,
                    k_sf_High_dB0,
                };
                int sf_High_Pack(std::vector<uint8_t> &bits);
                int sf_High_Unpack(std::vector<uint8_t> bits);
                int sf_High_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
                sf_High_Enum sf_High_Value() const;
                int sf_High_SetValue(sf_High_Enum value);
                int sf_High_SetValue(std::string value);
                std::string sf_High_ValueToString(sf_High_Enum value) const;
                uint64_t sf_High_NumberOfValues() const;
                std::string sf_High_ToString(uint32_t indent) const;
                std::string sf_High_ToStringNoNewLines() const;
                int sf_High_Clear();
                bool sf_High_IsPresent() const;
            private:
                bool sf_High_present;
                sf_High_Enum sf_High_internal_value;

            };

            q_HystSF q_HystSF_value;

        };

        speedStateReselectionPars speedStateReselectionPars_value;

    };

    cellReselectionInfoCommon cellReselectionInfoCommon_value;

    // cellReselectionServingFreqInfo
public:
    class cellReselectionServingFreqInfo
    {
    public:
        cellReselectionServingFreqInfo() : s_NonIntraSearch_present{false}, threshServingLow_present{false}, cellReselectionPriority_present{false} {};
    public:
        int Pack(std::vector<uint8_t> &bits);
        int Unpack(std::vector<uint8_t> bits);
        int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        std::string ToString(uint32_t indent) const;
        std::string ToStringNoNewLines() const;

        // s-NonIntraSearch
    public:
        ReselectionThreshold* s_NonIntraSearch_Set();
        int s_NonIntraSearch_Set(ReselectionThreshold &value);
        const ReselectionThreshold& s_NonIntraSearch_Get() const;
        std::string s_NonIntraSearch_ToString(uint32_t indent) const;
        std::string s_NonIntraSearch_ToStringNoNewLines() const;
        int s_NonIntraSearch_Clear();
        bool s_NonIntraSearch_IsPresent() const;
    private:
        bool s_NonIntraSearch_present;
        ReselectionThreshold s_NonIntraSearch;

        // threshServingLow
    public:
        ReselectionThreshold* threshServingLow_Set();
        int threshServingLow_Set(ReselectionThreshold &value);
        const ReselectionThreshold& threshServingLow_Get() const;
        std::string threshServingLow_ToString(uint32_t indent) const;
        std::string threshServingLow_ToStringNoNewLines() const;
        int threshServingLow_Clear();
        bool threshServingLow_IsPresent() const;
    private:
        bool threshServingLow_present;
        ReselectionThreshold threshServingLow;

        // cellReselectionPriority
    public:
        CellReselectionPriority* cellReselectionPriority_Set();
        int cellReselectionPriority_Set(CellReselectionPriority &value);
        const CellReselectionPriority& cellReselectionPriority_Get() const;
        std::string cellReselectionPriority_ToString(uint32_t indent) const;
        std::string cellReselectionPriority_ToStringNoNewLines() const;
        int cellReselectionPriority_Clear();
        bool cellReselectionPriority_IsPresent() const;
    private:
        bool cellReselectionPriority_present;
        CellReselectionPriority cellReselectionPriority;

    };

    cellReselectionServingFreqInfo cellReselectionServingFreqInfo_value;

    // intraFreqCellReselectionInfo
public:
    class intraFreqCellReselectionInfo
    {
    public:
        intraFreqCellReselectionInfo() : q_RxLevMin_present{false}, p_Max_present{false}, s_IntraSearch_present{false}, allowedMeasBandwidth_present{false}, presenceAntennaPort1_present{false}, neighCellConfig_present{false}, t_ReselectionEUTRA_present{false}, t_ReselectionEUTRA_SF_present{false} {};
    public:
        int Pack(std::vector<uint8_t> &bits);
        int Unpack(std::vector<uint8_t> bits);
        int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        std::string ToString(uint32_t indent) const;
        std::string ToStringNoNewLines() const;

        // q-RxLevMin
    public:
        Q_RxLevMin* q_RxLevMin_Set();
        int q_RxLevMin_Set(Q_RxLevMin &value);
        const Q_RxLevMin& q_RxLevMin_Get() const;
        std::string q_RxLevMin_ToString(uint32_t indent) const;
        std::string q_RxLevMin_ToStringNoNewLines() const;
        int q_RxLevMin_Clear();
        bool q_RxLevMin_IsPresent() const;
    private:
        bool q_RxLevMin_present;
        Q_RxLevMin q_RxLevMin;

        // p-Max
    public:
        P_Max* p_Max_Set();
        int p_Max_Set(P_Max &value);
        const P_Max& p_Max_Get() const;
        std::string p_Max_ToString(uint32_t indent) const;
        std::string p_Max_ToStringNoNewLines() const;
        int p_Max_Clear();
        bool p_Max_IsPresent() const;
    private:
        bool p_Max_present;
        P_Max p_Max;

        // s-IntraSearch
    public:
        ReselectionThreshold* s_IntraSearch_Set();
        int s_IntraSearch_Set(ReselectionThreshold &value);
        const ReselectionThreshold& s_IntraSearch_Get() const;
        std::string s_IntraSearch_ToString(uint32_t indent) const;
        std::string s_IntraSearch_ToStringNoNewLines() const;
        int s_IntraSearch_Clear();
        bool s_IntraSearch_IsPresent() const;
    private:
        bool s_IntraSearch_present;
        ReselectionThreshold s_IntraSearch;

        // allowedMeasBandwidth
    public:
        AllowedMeasBandwidth* allowedMeasBandwidth_Set();
        int allowedMeasBandwidth_Set(AllowedMeasBandwidth &value);
        const AllowedMeasBandwidth& allowedMeasBandwidth_Get() const;
        std::string allowedMeasBandwidth_ToString(uint32_t indent) const;
        std::string allowedMeasBandwidth_ToStringNoNewLines() const;
        int allowedMeasBandwidth_Clear();
        bool allowedMeasBandwidth_IsPresent() const;
    private:
        bool allowedMeasBandwidth_present;
        AllowedMeasBandwidth allowedMeasBandwidth;

        // presenceAntennaPort1
    public:
        PresenceAntennaPort1* presenceAntennaPort1_Set();
        int presenceAntennaPort1_Set(PresenceAntennaPort1 &value);
        const PresenceAntennaPort1& presenceAntennaPort1_Get() const;
        std::string presenceAntennaPort1_ToString(uint32_t indent) const;
        std::string presenceAntennaPort1_ToStringNoNewLines() const;
        int presenceAntennaPort1_Clear();
        bool presenceAntennaPort1_IsPresent() const;
    private:
        bool presenceAntennaPort1_present;
        PresenceAntennaPort1 presenceAntennaPort1;

        // neighCellConfig
    public:
        NeighCellConfig* neighCellConfig_Set();
        int neighCellConfig_Set(NeighCellConfig &value);
        const NeighCellConfig& neighCellConfig_Get() const;
        std::string neighCellConfig_ToString(uint32_t indent) const;
        std::string neighCellConfig_ToStringNoNewLines() const;
        int neighCellConfig_Clear();
        bool neighCellConfig_IsPresent() const;
    private:
        bool neighCellConfig_present;
        NeighCellConfig neighCellConfig;

        // t-ReselectionEUTRA
    public:
        T_Reselection* t_ReselectionEUTRA_Set();
        int t_ReselectionEUTRA_Set(T_Reselection &value);
        const T_Reselection& t_ReselectionEUTRA_Get() const;
        std::string t_ReselectionEUTRA_ToString(uint32_t indent) const;
        std::string t_ReselectionEUTRA_ToStringNoNewLines() const;
        int t_ReselectionEUTRA_Clear();
        bool t_ReselectionEUTRA_IsPresent() const;
    private:
        bool t_ReselectionEUTRA_present;
        T_Reselection t_ReselectionEUTRA;

        // t-ReselectionEUTRA-SF
    public:
        SpeedStateScaleFactors* t_ReselectionEUTRA_SF_Set();
        int t_ReselectionEUTRA_SF_Set(SpeedStateScaleFactors &value);
        const SpeedStateScaleFactors& t_ReselectionEUTRA_SF_Get() const;
        std::string t_ReselectionEUTRA_SF_ToString(uint32_t indent) const;
        std::string t_ReselectionEUTRA_SF_ToStringNoNewLines() const;
        int t_ReselectionEUTRA_SF_Clear();
        bool t_ReselectionEUTRA_SF_IsPresent() const;
    private:
        bool t_ReselectionEUTRA_SF_present;
        SpeedStateScaleFactors t_ReselectionEUTRA_SF;

    };

    intraFreqCellReselectionInfo intraFreqCellReselectionInfo_value;

    // lateNonCriticalExtension
public:
    int lateNonCriticalExtension_Pack(std::vector<uint8_t> &bits);
    int lateNonCriticalExtension_Unpack(std::vector<uint8_t> bits);
    int lateNonCriticalExtension_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::vector<uint8_t> lateNonCriticalExtension_Value() const;
    int lateNonCriticalExtension_SetValue(std::vector<uint8_t> value);
    std::string lateNonCriticalExtension_ToString(uint32_t indent) const;
    std::string lateNonCriticalExtension_ToStringNoNewLines() const;
    int lateNonCriticalExtension_Clear();
    bool lateNonCriticalExtension_IsPresent() const;
private:
    bool lateNonCriticalExtension_present;
    std::vector<uint8_t> lateNonCriticalExtension_internal_value;

    // s-IntraSearch-v920
public:
    class s_IntraSearch_v920
    {
    public:
        s_IntraSearch_v920() : present{false}, s_IntraSearchP_r9_present{false}, s_IntraSearchQ_r9_present{false} {};
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

        // s-IntraSearchP-r9
    public:
        ReselectionThreshold* s_IntraSearchP_r9_Set();
        int s_IntraSearchP_r9_Set(ReselectionThreshold &value);
        const ReselectionThreshold& s_IntraSearchP_r9_Get() const;
        std::string s_IntraSearchP_r9_ToString(uint32_t indent) const;
        std::string s_IntraSearchP_r9_ToStringNoNewLines() const;
        int s_IntraSearchP_r9_Clear();
        bool s_IntraSearchP_r9_IsPresent() const;
    private:
        bool s_IntraSearchP_r9_present;
        ReselectionThreshold s_IntraSearchP_r9;

        // s-IntraSearchQ-r9
    public:
        ReselectionThresholdQ_r9* s_IntraSearchQ_r9_Set();
        int s_IntraSearchQ_r9_Set(ReselectionThresholdQ_r9 &value);
        const ReselectionThresholdQ_r9& s_IntraSearchQ_r9_Get() const;
        std::string s_IntraSearchQ_r9_ToString(uint32_t indent) const;
        std::string s_IntraSearchQ_r9_ToStringNoNewLines() const;
        int s_IntraSearchQ_r9_Clear();
        bool s_IntraSearchQ_r9_IsPresent() const;
    private:
        bool s_IntraSearchQ_r9_present;
        ReselectionThresholdQ_r9 s_IntraSearchQ_r9;

    };

    s_IntraSearch_v920 s_IntraSearch_v920_value;

    // s-NonIntraSearch-v920
public:
    class s_NonIntraSearch_v920
    {
    public:
        s_NonIntraSearch_v920() : present{false}, s_NonIntraSearchP_r9_present{false}, s_NonIntraSearchQ_r9_present{false} {};
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

        // s-NonIntraSearchP-r9
    public:
        ReselectionThreshold* s_NonIntraSearchP_r9_Set();
        int s_NonIntraSearchP_r9_Set(ReselectionThreshold &value);
        const ReselectionThreshold& s_NonIntraSearchP_r9_Get() const;
        std::string s_NonIntraSearchP_r9_ToString(uint32_t indent) const;
        std::string s_NonIntraSearchP_r9_ToStringNoNewLines() const;
        int s_NonIntraSearchP_r9_Clear();
        bool s_NonIntraSearchP_r9_IsPresent() const;
    private:
        bool s_NonIntraSearchP_r9_present;
        ReselectionThreshold s_NonIntraSearchP_r9;

        // s-NonIntraSearchQ-r9
    public:
        ReselectionThresholdQ_r9* s_NonIntraSearchQ_r9_Set();
        int s_NonIntraSearchQ_r9_Set(ReselectionThresholdQ_r9 &value);
        const ReselectionThresholdQ_r9& s_NonIntraSearchQ_r9_Get() const;
        std::string s_NonIntraSearchQ_r9_ToString(uint32_t indent) const;
        std::string s_NonIntraSearchQ_r9_ToStringNoNewLines() const;
        int s_NonIntraSearchQ_r9_Clear();
        bool s_NonIntraSearchQ_r9_IsPresent() const;
    private:
        bool s_NonIntraSearchQ_r9_present;
        ReselectionThresholdQ_r9 s_NonIntraSearchQ_r9;

    };

    s_NonIntraSearch_v920 s_NonIntraSearch_v920_value;

    // q-QualMin-r9
public:
    Q_QualMin_r9* q_QualMin_r9_Set();
    int q_QualMin_r9_Set(Q_QualMin_r9 &value);
    const Q_QualMin_r9& q_QualMin_r9_Get() const;
    std::string q_QualMin_r9_ToString(uint32_t indent) const;
    std::string q_QualMin_r9_ToStringNoNewLines() const;
    int q_QualMin_r9_Clear();
    bool q_QualMin_r9_IsPresent() const;
private:
    bool q_QualMin_r9_present;
    Q_QualMin_r9 q_QualMin_r9;

    // threshServingLowQ-r9
public:
    ReselectionThresholdQ_r9* threshServingLowQ_r9_Set();
    int threshServingLowQ_r9_Set(ReselectionThresholdQ_r9 &value);
    const ReselectionThresholdQ_r9& threshServingLowQ_r9_Get() const;
    std::string threshServingLowQ_r9_ToString(uint32_t indent) const;
    std::string threshServingLowQ_r9_ToStringNoNewLines() const;
    int threshServingLowQ_r9_Clear();
    bool threshServingLowQ_r9_IsPresent() const;
private:
    bool threshServingLowQ_r9_present;
    ReselectionThresholdQ_r9 threshServingLowQ_r9;

};

#endif
