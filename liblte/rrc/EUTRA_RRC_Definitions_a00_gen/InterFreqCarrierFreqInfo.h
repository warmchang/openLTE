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

#ifndef __InterFreqCarrierFreqInfo_H__
#define __InterFreqCarrierFreqInfo_H__

#include "ARFCN_ValueEUTRA.h"
#include "Q_RxLevMin.h"
#include "P_Max.h"
#include "T_Reselection.h"
#include "SpeedStateScaleFactors.h"
#include "ReselectionThreshold.h"
#include "ReselectionThreshold.h"
#include "AllowedMeasBandwidth.h"
#include "PresenceAntennaPort1.h"
#include "CellReselectionPriority.h"
#include "NeighCellConfig.h"
#include "Q_OffsetRange.h"
#include "InterFreqNeighCellList.h"
#include "InterFreqBlackCellList.h"
#include "Q_QualMin_r9.h"
#include "ReselectionThresholdQ_r9.h"
#include "ReselectionThresholdQ_r9.h"

#include <array>
#include <cstdint>
#include <vector>

class InterFreqCarrierFreqInfo
{
public:
    InterFreqCarrierFreqInfo() : dl_CarrierFreq_present{false}, q_RxLevMin_present{false}, p_Max_present{false}, t_ReselectionEUTRA_present{false}, t_ReselectionEUTRA_SF_present{false}, threshX_High_present{false}, threshX_Low_present{false}, allowedMeasBandwidth_present{false}, presenceAntennaPort1_present{false}, cellReselectionPriority_present{false}, neighCellConfig_present{false}, q_OffsetFreq_present{false}, interFreqNeighCellList_present{false}, interFreqBlackCellList_present{false}, q_QualMin_r9_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // dl-CarrierFreq
public:
    ARFCN_ValueEUTRA* dl_CarrierFreq_Set();
    int dl_CarrierFreq_Set(ARFCN_ValueEUTRA &value);
    const ARFCN_ValueEUTRA& dl_CarrierFreq_Get() const;
    std::string dl_CarrierFreq_ToString(uint32_t indent) const;
    std::string dl_CarrierFreq_ToStringNoNewLines() const;
    int dl_CarrierFreq_Clear();
    bool dl_CarrierFreq_IsPresent() const;
private:
    bool dl_CarrierFreq_present;
    ARFCN_ValueEUTRA dl_CarrierFreq;

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

    // threshX-High
public:
    ReselectionThreshold* threshX_High_Set();
    int threshX_High_Set(ReselectionThreshold &value);
    const ReselectionThreshold& threshX_High_Get() const;
    std::string threshX_High_ToString(uint32_t indent) const;
    std::string threshX_High_ToStringNoNewLines() const;
    int threshX_High_Clear();
    bool threshX_High_IsPresent() const;
private:
    bool threshX_High_present;
    ReselectionThreshold threshX_High;

    // threshX-Low
public:
    ReselectionThreshold* threshX_Low_Set();
    int threshX_Low_Set(ReselectionThreshold &value);
    const ReselectionThreshold& threshX_Low_Get() const;
    std::string threshX_Low_ToString(uint32_t indent) const;
    std::string threshX_Low_ToStringNoNewLines() const;
    int threshX_Low_Clear();
    bool threshX_Low_IsPresent() const;
private:
    bool threshX_Low_present;
    ReselectionThreshold threshX_Low;

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

    // q-OffsetFreq
public:
    Q_OffsetRange* q_OffsetFreq_Set();
    int q_OffsetFreq_Set(Q_OffsetRange &value);
    const Q_OffsetRange& q_OffsetFreq_Get() const;
    Q_OffsetRange::Enum q_OffsetFreq_GetDefault() const;
    std::string q_OffsetFreq_ToString(uint32_t indent) const;
    std::string q_OffsetFreq_ToStringNoNewLines() const;
    int q_OffsetFreq_Clear();
    bool q_OffsetFreq_IsPresent() const;
private:
    bool q_OffsetFreq_present;
    Q_OffsetRange q_OffsetFreq;

    // interFreqNeighCellList
public:
    InterFreqNeighCellList* interFreqNeighCellList_Set();
    int interFreqNeighCellList_Set(InterFreqNeighCellList &value);
    const InterFreqNeighCellList& interFreqNeighCellList_Get() const;
    std::string interFreqNeighCellList_ToString(uint32_t indent) const;
    std::string interFreqNeighCellList_ToStringNoNewLines() const;
    int interFreqNeighCellList_Clear();
    bool interFreqNeighCellList_IsPresent() const;
private:
    bool interFreqNeighCellList_present;
    InterFreqNeighCellList interFreqNeighCellList;

    // interFreqBlackCellList
public:
    InterFreqBlackCellList* interFreqBlackCellList_Set();
    int interFreqBlackCellList_Set(InterFreqBlackCellList &value);
    const InterFreqBlackCellList& interFreqBlackCellList_Get() const;
    std::string interFreqBlackCellList_ToString(uint32_t indent) const;
    std::string interFreqBlackCellList_ToStringNoNewLines() const;
    int interFreqBlackCellList_Clear();
    bool interFreqBlackCellList_IsPresent() const;
private:
    bool interFreqBlackCellList_present;
    InterFreqBlackCellList interFreqBlackCellList;

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

    // threshX-Q-r9
public:
    class threshX_Q_r9
    {
    public:
        threshX_Q_r9() : present{false}, threshX_HighQ_r9_present{false}, threshX_LowQ_r9_present{false} {};
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

        // threshX-HighQ-r9
    public:
        ReselectionThresholdQ_r9* threshX_HighQ_r9_Set();
        int threshX_HighQ_r9_Set(ReselectionThresholdQ_r9 &value);
        const ReselectionThresholdQ_r9& threshX_HighQ_r9_Get() const;
        std::string threshX_HighQ_r9_ToString(uint32_t indent) const;
        std::string threshX_HighQ_r9_ToStringNoNewLines() const;
        int threshX_HighQ_r9_Clear();
        bool threshX_HighQ_r9_IsPresent() const;
    private:
        bool threshX_HighQ_r9_present;
        ReselectionThresholdQ_r9 threshX_HighQ_r9;

        // threshX-LowQ-r9
    public:
        ReselectionThresholdQ_r9* threshX_LowQ_r9_Set();
        int threshX_LowQ_r9_Set(ReselectionThresholdQ_r9 &value);
        const ReselectionThresholdQ_r9& threshX_LowQ_r9_Get() const;
        std::string threshX_LowQ_r9_ToString(uint32_t indent) const;
        std::string threshX_LowQ_r9_ToStringNoNewLines() const;
        int threshX_LowQ_r9_Clear();
        bool threshX_LowQ_r9_IsPresent() const;
    private:
        bool threshX_LowQ_r9_present;
        ReselectionThresholdQ_r9 threshX_LowQ_r9;

    };

    threshX_Q_r9 threshX_Q_r9_value;

};

#endif
