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

#ifndef __SystemInformationBlockType1_H__
#define __SystemInformationBlockType1_H__

#include "PLMN_IdentityList.h"
#include "TrackingAreaCode.h"
#include "CellIdentity.h"
#include "CSG_Identity.h"
#include "Q_RxLevMin.h"
#include "P_Max.h"
#include "SchedulingInfoList.h"
#include "TDD_Config.h"
#include "SystemInformationBlockType1_v890_IEs.h"

#include <array>
#include <cstdint>
#include <vector>

class SystemInformationBlockType1
{
public:
    SystemInformationBlockType1() : p_Max_present{false}, freqBandIndicator_present{false}, schedulingInfoList_present{false}, tdd_Config_present{false}, si_WindowLength_present{false}, systemInfoValueTag_present{false}, nonCriticalExtension_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // cellAccessRelatedInfo
public:
    class cellAccessRelatedInfo
    {
    public:
        cellAccessRelatedInfo() : plmn_IdentityList_present{false}, trackingAreaCode_present{false}, cellIdentity_present{false}, cellBarred_present{false}, intraFreqReselection_present{false}, csg_Indication_present{false}, csg_Identity_present{false} {};
    public:
        int Pack(std::vector<uint8_t> &bits);
        int Unpack(std::vector<uint8_t> bits);
        int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        std::string ToString(uint32_t indent) const;
        std::string ToStringNoNewLines() const;

        // plmn-IdentityList
    public:
        PLMN_IdentityList* plmn_IdentityList_Set();
        int plmn_IdentityList_Set(PLMN_IdentityList &value);
        const PLMN_IdentityList& plmn_IdentityList_Get() const;
        std::string plmn_IdentityList_ToString(uint32_t indent) const;
        std::string plmn_IdentityList_ToStringNoNewLines() const;
        int plmn_IdentityList_Clear();
        bool plmn_IdentityList_IsPresent() const;
    private:
        bool plmn_IdentityList_present;
        PLMN_IdentityList plmn_IdentityList;

        // trackingAreaCode
    public:
        TrackingAreaCode* trackingAreaCode_Set();
        int trackingAreaCode_Set(TrackingAreaCode &value);
        const TrackingAreaCode& trackingAreaCode_Get() const;
        std::string trackingAreaCode_ToString(uint32_t indent) const;
        std::string trackingAreaCode_ToStringNoNewLines() const;
        int trackingAreaCode_Clear();
        bool trackingAreaCode_IsPresent() const;
    private:
        bool trackingAreaCode_present;
        TrackingAreaCode trackingAreaCode;

        // cellIdentity
    public:
        CellIdentity* cellIdentity_Set();
        int cellIdentity_Set(CellIdentity &value);
        const CellIdentity& cellIdentity_Get() const;
        std::string cellIdentity_ToString(uint32_t indent) const;
        std::string cellIdentity_ToStringNoNewLines() const;
        int cellIdentity_Clear();
        bool cellIdentity_IsPresent() const;
    private:
        bool cellIdentity_present;
        CellIdentity cellIdentity;

        // cellBarred
    public:
        enum cellBarred_Enum {
            k_cellBarred_barred = 0,
            k_cellBarred_notBarred,
        };
        int cellBarred_Pack(std::vector<uint8_t> &bits);
        int cellBarred_Unpack(std::vector<uint8_t> bits);
        int cellBarred_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        cellBarred_Enum cellBarred_Value() const;
        int cellBarred_SetValue(cellBarred_Enum value);
        int cellBarred_SetValue(std::string value);
        std::string cellBarred_ValueToString(cellBarred_Enum value) const;
        uint64_t cellBarred_NumberOfValues() const;
        std::string cellBarred_ToString(uint32_t indent) const;
        std::string cellBarred_ToStringNoNewLines() const;
        int cellBarred_Clear();
        bool cellBarred_IsPresent() const;
    private:
        bool cellBarred_present;
        cellBarred_Enum cellBarred_internal_value;

        // intraFreqReselection
    public:
        enum intraFreqReselection_Enum {
            k_intraFreqReselection_allowed = 0,
            k_intraFreqReselection_notAllowed,
        };
        int intraFreqReselection_Pack(std::vector<uint8_t> &bits);
        int intraFreqReselection_Unpack(std::vector<uint8_t> bits);
        int intraFreqReselection_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        intraFreqReselection_Enum intraFreqReselection_Value() const;
        int intraFreqReselection_SetValue(intraFreqReselection_Enum value);
        int intraFreqReselection_SetValue(std::string value);
        std::string intraFreqReselection_ValueToString(intraFreqReselection_Enum value) const;
        uint64_t intraFreqReselection_NumberOfValues() const;
        std::string intraFreqReselection_ToString(uint32_t indent) const;
        std::string intraFreqReselection_ToStringNoNewLines() const;
        int intraFreqReselection_Clear();
        bool intraFreqReselection_IsPresent() const;
    private:
        bool intraFreqReselection_present;
        intraFreqReselection_Enum intraFreqReselection_internal_value;

        // csg-Indication
    public:
        int csg_Indication_Pack(std::vector<uint8_t> &bits);
        int csg_Indication_Unpack(std::vector<uint8_t> bits);
        int csg_Indication_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        bool csg_Indication_Value() const;
        int csg_Indication_SetValue(bool value);
        std::string csg_Indication_ToString(uint32_t indent) const;
        std::string csg_Indication_ToStringNoNewLines() const;
        int csg_Indication_Clear();
        bool csg_Indication_IsPresent() const;
    private:
        bool csg_Indication_present;
        bool csg_Indication_internal_value;

        // csg-Identity
    public:
        CSG_Identity* csg_Identity_Set();
        int csg_Identity_Set(CSG_Identity &value);
        const CSG_Identity& csg_Identity_Get() const;
        std::string csg_Identity_ToString(uint32_t indent) const;
        std::string csg_Identity_ToStringNoNewLines() const;
        int csg_Identity_Clear();
        bool csg_Identity_IsPresent() const;
    private:
        bool csg_Identity_present;
        CSG_Identity csg_Identity;

    };

    cellAccessRelatedInfo cellAccessRelatedInfo_value;

    // cellSelectionInfo
public:
    class cellSelectionInfo
    {
    public:
        cellSelectionInfo() : q_RxLevMin_present{false}, q_RxLevMinOffset_present{false} {};
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

        // q-RxLevMinOffset
    public:
        int q_RxLevMinOffset_Pack(std::vector<uint8_t> &bits);
        int q_RxLevMinOffset_Unpack(std::vector<uint8_t> bits);
        int q_RxLevMinOffset_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        int64_t q_RxLevMinOffset_Value() const;
        int q_RxLevMinOffset_SetValue(int64_t value);
        std::string q_RxLevMinOffset_ToString(uint32_t indent) const;
        std::string q_RxLevMinOffset_ToStringNoNewLines() const;
        int q_RxLevMinOffset_Clear();
        bool q_RxLevMinOffset_IsPresent() const;
    private:
        bool q_RxLevMinOffset_present;
        int64_t q_RxLevMinOffset_internal_value;

    };

    cellSelectionInfo cellSelectionInfo_value;

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

    // freqBandIndicator
public:
    int freqBandIndicator_Pack(std::vector<uint8_t> &bits);
    int freqBandIndicator_Unpack(std::vector<uint8_t> bits);
    int freqBandIndicator_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t freqBandIndicator_Value() const;
    int freqBandIndicator_SetValue(int64_t value);
    std::string freqBandIndicator_ToString(uint32_t indent) const;
    std::string freqBandIndicator_ToStringNoNewLines() const;
    int freqBandIndicator_Clear();
    bool freqBandIndicator_IsPresent() const;
private:
    bool freqBandIndicator_present;
    int64_t freqBandIndicator_internal_value;

    // schedulingInfoList
public:
    SchedulingInfoList* schedulingInfoList_Set();
    int schedulingInfoList_Set(SchedulingInfoList &value);
    const SchedulingInfoList& schedulingInfoList_Get() const;
    std::string schedulingInfoList_ToString(uint32_t indent) const;
    std::string schedulingInfoList_ToStringNoNewLines() const;
    int schedulingInfoList_Clear();
    bool schedulingInfoList_IsPresent() const;
private:
    bool schedulingInfoList_present;
    SchedulingInfoList schedulingInfoList;

    // tdd-Config
public:
    TDD_Config* tdd_Config_Set();
    int tdd_Config_Set(TDD_Config &value);
    const TDD_Config& tdd_Config_Get() const;
    std::string tdd_Config_ToString(uint32_t indent) const;
    std::string tdd_Config_ToStringNoNewLines() const;
    int tdd_Config_Clear();
    bool tdd_Config_IsPresent() const;
private:
    bool tdd_Config_present;
    TDD_Config tdd_Config;

    // si-WindowLength
public:
    enum si_WindowLength_Enum {
        k_si_WindowLength_ms1 = 0,
        k_si_WindowLength_ms2,
        k_si_WindowLength_ms5,
        k_si_WindowLength_ms10,
        k_si_WindowLength_ms15,
        k_si_WindowLength_ms20,
        k_si_WindowLength_ms40,
    };
    int si_WindowLength_Pack(std::vector<uint8_t> &bits);
    int si_WindowLength_Unpack(std::vector<uint8_t> bits);
    int si_WindowLength_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    si_WindowLength_Enum si_WindowLength_Value() const;
    int si_WindowLength_SetValue(si_WindowLength_Enum value);
    int si_WindowLength_SetValue(std::string value);
    std::string si_WindowLength_ValueToString(si_WindowLength_Enum value) const;
    uint64_t si_WindowLength_NumberOfValues() const;
    std::string si_WindowLength_ToString(uint32_t indent) const;
    std::string si_WindowLength_ToStringNoNewLines() const;
    int si_WindowLength_Clear();
    bool si_WindowLength_IsPresent() const;
private:
    bool si_WindowLength_present;
    si_WindowLength_Enum si_WindowLength_internal_value;

    // systemInfoValueTag
public:
    int systemInfoValueTag_Pack(std::vector<uint8_t> &bits);
    int systemInfoValueTag_Unpack(std::vector<uint8_t> bits);
    int systemInfoValueTag_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t systemInfoValueTag_Value() const;
    int systemInfoValueTag_SetValue(int64_t value);
    std::string systemInfoValueTag_ToString(uint32_t indent) const;
    std::string systemInfoValueTag_ToStringNoNewLines() const;
    int systemInfoValueTag_Clear();
    bool systemInfoValueTag_IsPresent() const;
private:
    bool systemInfoValueTag_present;
    int64_t systemInfoValueTag_internal_value;

    // nonCriticalExtension
public:
    SystemInformationBlockType1_v890_IEs* nonCriticalExtension_Set();
    int nonCriticalExtension_Set(SystemInformationBlockType1_v890_IEs &value);
    const SystemInformationBlockType1_v890_IEs& nonCriticalExtension_Get() const;
    std::string nonCriticalExtension_ToString(uint32_t indent) const;
    std::string nonCriticalExtension_ToStringNoNewLines() const;
    int nonCriticalExtension_Clear();
    bool nonCriticalExtension_IsPresent() const;
private:
    bool nonCriticalExtension_present;
    SystemInformationBlockType1_v890_IEs nonCriticalExtension;

};

#endif
