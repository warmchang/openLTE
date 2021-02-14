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

#ifndef __ReportConfigEUTRA_H__
#define __ReportConfigEUTRA_H__

#include "ThresholdEUTRA.h"
#include "ThresholdEUTRA.h"
#include "ThresholdEUTRA.h"
#include "ThresholdEUTRA.h"
#include "ThresholdEUTRA.h"
#include "Hysteresis.h"
#include "TimeToTrigger.h"
#include "ReportInterval.h"

#include <array>
#include <cstdint>
#include <vector>

class ReportConfigEUTRA
{
public:
    ReportConfigEUTRA() : triggerType_present{false}, triggerQuantity_present{false}, reportQuantity_present{false}, maxReportCells_present{false}, reportInterval_present{false}, reportAmount_present{false}, si_RequestForHO_r9_present{false}, ue_RxTxTimeDiffPeriodical_r9_present{false}, includeLocationInfo_r10_present{false}, reportAddNeighMeas_r10_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // triggerType
public:
    enum triggerType_Enum {
        k_triggerType_event = 0,
        k_triggerType_periodical,
    };
    int triggerType_Pack(std::vector<uint8_t> &bits);
    int triggerType_Unpack(std::vector<uint8_t> bits);
    int triggerType_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    triggerType_Enum triggerType_Choice() const;
    int triggerType_SetChoice(triggerType_Enum choice);
    std::string triggerType_ChoiceToString(triggerType_Enum value) const;
    uint64_t triggerType_NumberOfChoices() const;
    std::string triggerType_ToString(uint32_t indent) const;
    std::string triggerType_ToStringNoNewLines() const;
    int triggerType_Clear();
    bool triggerType_IsPresent() const;
private:
    bool triggerType_present;
    triggerType_Enum triggerType_internal_choice;

    // event
public:
    class triggerType_event
    {
    public:
        triggerType_event() : eventId_present{false}, hysteresis_present{false}, timeToTrigger_present{false} {};
    public:
        int Pack(std::vector<uint8_t> &bits);
        int Unpack(std::vector<uint8_t> bits);
        int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        std::string ToString(uint32_t indent) const;
        std::string ToStringNoNewLines() const;

        // eventId
    public:
        enum eventId_Enum {
            k_eventId_eventA1 = 0,
            k_eventId_eventA2,
            k_eventId_eventA3,
            k_eventId_eventA4,
            k_eventId_eventA5,
            k_eventId_eventA6,
        };
        int eventId_Pack(std::vector<uint8_t> &bits);
        int eventId_Unpack(std::vector<uint8_t> bits);
        int eventId_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        eventId_Enum eventId_Choice() const;
        int eventId_SetChoice(eventId_Enum choice);
        std::string eventId_ChoiceToString(eventId_Enum value) const;
        uint64_t eventId_NumberOfChoices() const;
        std::string eventId_ToString(uint32_t indent) const;
        std::string eventId_ToStringNoNewLines() const;
        int eventId_Clear();
        bool eventId_IsPresent() const;
    private:
        bool eventId_present;
        eventId_Enum eventId_internal_choice;

        // eventA1
    public:
        class eventId_eventA1
        {
        public:
            eventId_eventA1() : a1_Threshold_present{false} {};
        public:
            int Pack(std::vector<uint8_t> &bits);
            int Unpack(std::vector<uint8_t> bits);
            int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
            std::string ToString(uint32_t indent) const;
            std::string ToStringNoNewLines() const;

            // a1-Threshold
        public:
            ThresholdEUTRA* a1_Threshold_Set();
            int a1_Threshold_Set(ThresholdEUTRA &value);
            const ThresholdEUTRA& a1_Threshold_Get() const;
            std::string a1_Threshold_ToString(uint32_t indent) const;
            std::string a1_Threshold_ToStringNoNewLines() const;
            int a1_Threshold_Clear();
            bool a1_Threshold_IsPresent() const;
        private:
            bool a1_Threshold_present;
            ThresholdEUTRA a1_Threshold;

        };

        eventId_eventA1 eventId_eventA1_value;

        // eventA2
    public:
        class eventId_eventA2
        {
        public:
            eventId_eventA2() : a2_Threshold_present{false} {};
        public:
            int Pack(std::vector<uint8_t> &bits);
            int Unpack(std::vector<uint8_t> bits);
            int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
            std::string ToString(uint32_t indent) const;
            std::string ToStringNoNewLines() const;

            // a2-Threshold
        public:
            ThresholdEUTRA* a2_Threshold_Set();
            int a2_Threshold_Set(ThresholdEUTRA &value);
            const ThresholdEUTRA& a2_Threshold_Get() const;
            std::string a2_Threshold_ToString(uint32_t indent) const;
            std::string a2_Threshold_ToStringNoNewLines() const;
            int a2_Threshold_Clear();
            bool a2_Threshold_IsPresent() const;
        private:
            bool a2_Threshold_present;
            ThresholdEUTRA a2_Threshold;

        };

        eventId_eventA2 eventId_eventA2_value;

        // eventA3
    public:
        class eventId_eventA3
        {
        public:
            eventId_eventA3() : a3_Offset_present{false}, reportOnLeave_present{false} {};
        public:
            int Pack(std::vector<uint8_t> &bits);
            int Unpack(std::vector<uint8_t> bits);
            int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
            std::string ToString(uint32_t indent) const;
            std::string ToStringNoNewLines() const;

            // a3-Offset
        public:
            int a3_Offset_Pack(std::vector<uint8_t> &bits);
            int a3_Offset_Unpack(std::vector<uint8_t> bits);
            int a3_Offset_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
            int64_t a3_Offset_Value() const;
            int a3_Offset_SetValue(int64_t value);
            std::string a3_Offset_ToString(uint32_t indent) const;
            std::string a3_Offset_ToStringNoNewLines() const;
            int a3_Offset_Clear();
            bool a3_Offset_IsPresent() const;
        private:
            bool a3_Offset_present;
            int64_t a3_Offset_internal_value;

            // reportOnLeave
        public:
            int reportOnLeave_Pack(std::vector<uint8_t> &bits);
            int reportOnLeave_Unpack(std::vector<uint8_t> bits);
            int reportOnLeave_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
            bool reportOnLeave_Value() const;
            int reportOnLeave_SetValue(bool value);
            std::string reportOnLeave_ToString(uint32_t indent) const;
            std::string reportOnLeave_ToStringNoNewLines() const;
            int reportOnLeave_Clear();
            bool reportOnLeave_IsPresent() const;
        private:
            bool reportOnLeave_present;
            bool reportOnLeave_internal_value;

        };

        eventId_eventA3 eventId_eventA3_value;

        // eventA4
    public:
        class eventId_eventA4
        {
        public:
            eventId_eventA4() : a4_Threshold_present{false} {};
        public:
            int Pack(std::vector<uint8_t> &bits);
            int Unpack(std::vector<uint8_t> bits);
            int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
            std::string ToString(uint32_t indent) const;
            std::string ToStringNoNewLines() const;

            // a4-Threshold
        public:
            ThresholdEUTRA* a4_Threshold_Set();
            int a4_Threshold_Set(ThresholdEUTRA &value);
            const ThresholdEUTRA& a4_Threshold_Get() const;
            std::string a4_Threshold_ToString(uint32_t indent) const;
            std::string a4_Threshold_ToStringNoNewLines() const;
            int a4_Threshold_Clear();
            bool a4_Threshold_IsPresent() const;
        private:
            bool a4_Threshold_present;
            ThresholdEUTRA a4_Threshold;

        };

        eventId_eventA4 eventId_eventA4_value;

        // eventA5
    public:
        class eventId_eventA5
        {
        public:
            eventId_eventA5() : a5_Threshold1_present{false}, a5_Threshold2_present{false} {};
        public:
            int Pack(std::vector<uint8_t> &bits);
            int Unpack(std::vector<uint8_t> bits);
            int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
            std::string ToString(uint32_t indent) const;
            std::string ToStringNoNewLines() const;

            // a5-Threshold1
        public:
            ThresholdEUTRA* a5_Threshold1_Set();
            int a5_Threshold1_Set(ThresholdEUTRA &value);
            const ThresholdEUTRA& a5_Threshold1_Get() const;
            std::string a5_Threshold1_ToString(uint32_t indent) const;
            std::string a5_Threshold1_ToStringNoNewLines() const;
            int a5_Threshold1_Clear();
            bool a5_Threshold1_IsPresent() const;
        private:
            bool a5_Threshold1_present;
            ThresholdEUTRA a5_Threshold1;

            // a5-Threshold2
        public:
            ThresholdEUTRA* a5_Threshold2_Set();
            int a5_Threshold2_Set(ThresholdEUTRA &value);
            const ThresholdEUTRA& a5_Threshold2_Get() const;
            std::string a5_Threshold2_ToString(uint32_t indent) const;
            std::string a5_Threshold2_ToStringNoNewLines() const;
            int a5_Threshold2_Clear();
            bool a5_Threshold2_IsPresent() const;
        private:
            bool a5_Threshold2_present;
            ThresholdEUTRA a5_Threshold2;

        };

        eventId_eventA5 eventId_eventA5_value;

        // eventA6
    public:
        class eventId_eventA6
        {
        public:
            eventId_eventA6() : a6_Offset_present{false}, a6_ReportOnLeave_present{false} {};
        public:
            int Pack(std::vector<uint8_t> &bits);
            int Unpack(std::vector<uint8_t> bits);
            int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
            std::string ToString(uint32_t indent) const;
            std::string ToStringNoNewLines() const;

            // a6-Offset
        public:
            int a6_Offset_Pack(std::vector<uint8_t> &bits);
            int a6_Offset_Unpack(std::vector<uint8_t> bits);
            int a6_Offset_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
            int64_t a6_Offset_Value() const;
            int a6_Offset_SetValue(int64_t value);
            std::string a6_Offset_ToString(uint32_t indent) const;
            std::string a6_Offset_ToStringNoNewLines() const;
            int a6_Offset_Clear();
            bool a6_Offset_IsPresent() const;
        private:
            bool a6_Offset_present;
            int64_t a6_Offset_internal_value;

            // a6-ReportOnLeave
        public:
            int a6_ReportOnLeave_Pack(std::vector<uint8_t> &bits);
            int a6_ReportOnLeave_Unpack(std::vector<uint8_t> bits);
            int a6_ReportOnLeave_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
            bool a6_ReportOnLeave_Value() const;
            int a6_ReportOnLeave_SetValue(bool value);
            std::string a6_ReportOnLeave_ToString(uint32_t indent) const;
            std::string a6_ReportOnLeave_ToStringNoNewLines() const;
            int a6_ReportOnLeave_Clear();
            bool a6_ReportOnLeave_IsPresent() const;
        private:
            bool a6_ReportOnLeave_present;
            bool a6_ReportOnLeave_internal_value;

        };

        eventId_eventA6 eventId_eventA6_value;


        // hysteresis
    public:
        Hysteresis* hysteresis_Set();
        int hysteresis_Set(Hysteresis &value);
        const Hysteresis& hysteresis_Get() const;
        std::string hysteresis_ToString(uint32_t indent) const;
        std::string hysteresis_ToStringNoNewLines() const;
        int hysteresis_Clear();
        bool hysteresis_IsPresent() const;
    private:
        bool hysteresis_present;
        Hysteresis hysteresis;

        // timeToTrigger
    public:
        TimeToTrigger* timeToTrigger_Set();
        int timeToTrigger_Set(TimeToTrigger &value);
        const TimeToTrigger& timeToTrigger_Get() const;
        std::string timeToTrigger_ToString(uint32_t indent) const;
        std::string timeToTrigger_ToStringNoNewLines() const;
        int timeToTrigger_Clear();
        bool timeToTrigger_IsPresent() const;
    private:
        bool timeToTrigger_present;
        TimeToTrigger timeToTrigger;

    };

    triggerType_event triggerType_event_value;

    // periodical
public:
    class triggerType_periodical
    {
    public:
        triggerType_periodical() : purpose_present{false} {};
    public:
        int Pack(std::vector<uint8_t> &bits);
        int Unpack(std::vector<uint8_t> bits);
        int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        std::string ToString(uint32_t indent) const;
        std::string ToStringNoNewLines() const;

        // purpose
    public:
        enum purpose_Enum {
            k_purpose_reportStrongestCells = 0,
            k_purpose_reportCGI,
        };
        int purpose_Pack(std::vector<uint8_t> &bits);
        int purpose_Unpack(std::vector<uint8_t> bits);
        int purpose_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        purpose_Enum purpose_Value() const;
        int purpose_SetValue(purpose_Enum value);
        int purpose_SetValue(std::string value);
        std::string purpose_ValueToString(purpose_Enum value) const;
        uint64_t purpose_NumberOfValues() const;
        std::string purpose_ToString(uint32_t indent) const;
        std::string purpose_ToStringNoNewLines() const;
        int purpose_Clear();
        bool purpose_IsPresent() const;
    private:
        bool purpose_present;
        purpose_Enum purpose_internal_value;

    };

    triggerType_periodical triggerType_periodical_value;


    // triggerQuantity
public:
    enum triggerQuantity_Enum {
        k_triggerQuantity_rsrp = 0,
        k_triggerQuantity_rsrq,
    };
    int triggerQuantity_Pack(std::vector<uint8_t> &bits);
    int triggerQuantity_Unpack(std::vector<uint8_t> bits);
    int triggerQuantity_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    triggerQuantity_Enum triggerQuantity_Value() const;
    int triggerQuantity_SetValue(triggerQuantity_Enum value);
    int triggerQuantity_SetValue(std::string value);
    std::string triggerQuantity_ValueToString(triggerQuantity_Enum value) const;
    uint64_t triggerQuantity_NumberOfValues() const;
    std::string triggerQuantity_ToString(uint32_t indent) const;
    std::string triggerQuantity_ToStringNoNewLines() const;
    int triggerQuantity_Clear();
    bool triggerQuantity_IsPresent() const;
private:
    bool triggerQuantity_present;
    triggerQuantity_Enum triggerQuantity_internal_value;

    // reportQuantity
public:
    enum reportQuantity_Enum {
        k_reportQuantity_sameAsTriggerQuantity = 0,
        k_reportQuantity_both,
    };
    int reportQuantity_Pack(std::vector<uint8_t> &bits);
    int reportQuantity_Unpack(std::vector<uint8_t> bits);
    int reportQuantity_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    reportQuantity_Enum reportQuantity_Value() const;
    int reportQuantity_SetValue(reportQuantity_Enum value);
    int reportQuantity_SetValue(std::string value);
    std::string reportQuantity_ValueToString(reportQuantity_Enum value) const;
    uint64_t reportQuantity_NumberOfValues() const;
    std::string reportQuantity_ToString(uint32_t indent) const;
    std::string reportQuantity_ToStringNoNewLines() const;
    int reportQuantity_Clear();
    bool reportQuantity_IsPresent() const;
private:
    bool reportQuantity_present;
    reportQuantity_Enum reportQuantity_internal_value;

    // maxReportCells
public:
    int maxReportCells_Pack(std::vector<uint8_t> &bits);
    int maxReportCells_Unpack(std::vector<uint8_t> bits);
    int maxReportCells_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t maxReportCells_Value() const;
    int maxReportCells_SetValue(int64_t value);
    std::string maxReportCells_ToString(uint32_t indent) const;
    std::string maxReportCells_ToStringNoNewLines() const;
    int maxReportCells_Clear();
    bool maxReportCells_IsPresent() const;
private:
    bool maxReportCells_present;
    int64_t maxReportCells_internal_value;

    // reportInterval
public:
    ReportInterval* reportInterval_Set();
    int reportInterval_Set(ReportInterval &value);
    const ReportInterval& reportInterval_Get() const;
    std::string reportInterval_ToString(uint32_t indent) const;
    std::string reportInterval_ToStringNoNewLines() const;
    int reportInterval_Clear();
    bool reportInterval_IsPresent() const;
private:
    bool reportInterval_present;
    ReportInterval reportInterval;

    // reportAmount
public:
    enum reportAmount_Enum {
        k_reportAmount_r1 = 0,
        k_reportAmount_r2,
        k_reportAmount_r4,
        k_reportAmount_r8,
        k_reportAmount_r16,
        k_reportAmount_r32,
        k_reportAmount_r64,
        k_reportAmount_infinity,
    };
    int reportAmount_Pack(std::vector<uint8_t> &bits);
    int reportAmount_Unpack(std::vector<uint8_t> bits);
    int reportAmount_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    reportAmount_Enum reportAmount_Value() const;
    int reportAmount_SetValue(reportAmount_Enum value);
    int reportAmount_SetValue(std::string value);
    std::string reportAmount_ValueToString(reportAmount_Enum value) const;
    uint64_t reportAmount_NumberOfValues() const;
    std::string reportAmount_ToString(uint32_t indent) const;
    std::string reportAmount_ToStringNoNewLines() const;
    int reportAmount_Clear();
    bool reportAmount_IsPresent() const;
private:
    bool reportAmount_present;
    reportAmount_Enum reportAmount_internal_value;

    // si-RequestForHO-r9
public:
    enum si_RequestForHO_r9_Enum {
        k_si_RequestForHO_r9_setup = 0,
    };
    int si_RequestForHO_r9_Pack(std::vector<uint8_t> &bits);
    int si_RequestForHO_r9_Unpack(std::vector<uint8_t> bits);
    int si_RequestForHO_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    si_RequestForHO_r9_Enum si_RequestForHO_r9_Value() const;
    int si_RequestForHO_r9_SetValue(si_RequestForHO_r9_Enum value);
    int si_RequestForHO_r9_SetValue(std::string value);
    std::string si_RequestForHO_r9_ValueToString(si_RequestForHO_r9_Enum value) const;
    uint64_t si_RequestForHO_r9_NumberOfValues() const;
    std::string si_RequestForHO_r9_ToString(uint32_t indent) const;
    std::string si_RequestForHO_r9_ToStringNoNewLines() const;
    int si_RequestForHO_r9_Clear();
    bool si_RequestForHO_r9_IsPresent() const;
private:
    bool si_RequestForHO_r9_present;
    si_RequestForHO_r9_Enum si_RequestForHO_r9_internal_value;

    // ue-RxTxTimeDiffPeriodical-r9
public:
    enum ue_RxTxTimeDiffPeriodical_r9_Enum {
        k_ue_RxTxTimeDiffPeriodical_r9_setup = 0,
    };
    int ue_RxTxTimeDiffPeriodical_r9_Pack(std::vector<uint8_t> &bits);
    int ue_RxTxTimeDiffPeriodical_r9_Unpack(std::vector<uint8_t> bits);
    int ue_RxTxTimeDiffPeriodical_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    ue_RxTxTimeDiffPeriodical_r9_Enum ue_RxTxTimeDiffPeriodical_r9_Value() const;
    int ue_RxTxTimeDiffPeriodical_r9_SetValue(ue_RxTxTimeDiffPeriodical_r9_Enum value);
    int ue_RxTxTimeDiffPeriodical_r9_SetValue(std::string value);
    std::string ue_RxTxTimeDiffPeriodical_r9_ValueToString(ue_RxTxTimeDiffPeriodical_r9_Enum value) const;
    uint64_t ue_RxTxTimeDiffPeriodical_r9_NumberOfValues() const;
    std::string ue_RxTxTimeDiffPeriodical_r9_ToString(uint32_t indent) const;
    std::string ue_RxTxTimeDiffPeriodical_r9_ToStringNoNewLines() const;
    int ue_RxTxTimeDiffPeriodical_r9_Clear();
    bool ue_RxTxTimeDiffPeriodical_r9_IsPresent() const;
private:
    bool ue_RxTxTimeDiffPeriodical_r9_present;
    ue_RxTxTimeDiffPeriodical_r9_Enum ue_RxTxTimeDiffPeriodical_r9_internal_value;

    // includeLocationInfo-r10
public:
    enum includeLocationInfo_r10_Enum {
        k_includeLocationInfo_r10_true = 0,
    };
    int includeLocationInfo_r10_Pack(std::vector<uint8_t> &bits);
    int includeLocationInfo_r10_Unpack(std::vector<uint8_t> bits);
    int includeLocationInfo_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    includeLocationInfo_r10_Enum includeLocationInfo_r10_Value() const;
    int includeLocationInfo_r10_SetValue(includeLocationInfo_r10_Enum value);
    int includeLocationInfo_r10_SetValue(std::string value);
    std::string includeLocationInfo_r10_ValueToString(includeLocationInfo_r10_Enum value) const;
    uint64_t includeLocationInfo_r10_NumberOfValues() const;
    std::string includeLocationInfo_r10_ToString(uint32_t indent) const;
    std::string includeLocationInfo_r10_ToStringNoNewLines() const;
    int includeLocationInfo_r10_Clear();
    bool includeLocationInfo_r10_IsPresent() const;
private:
    bool includeLocationInfo_r10_present;
    includeLocationInfo_r10_Enum includeLocationInfo_r10_internal_value;

    // reportAddNeighMeas-r10
public:
    enum reportAddNeighMeas_r10_Enum {
        k_reportAddNeighMeas_r10_setup = 0,
    };
    int reportAddNeighMeas_r10_Pack(std::vector<uint8_t> &bits);
    int reportAddNeighMeas_r10_Unpack(std::vector<uint8_t> bits);
    int reportAddNeighMeas_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    reportAddNeighMeas_r10_Enum reportAddNeighMeas_r10_Value() const;
    int reportAddNeighMeas_r10_SetValue(reportAddNeighMeas_r10_Enum value);
    int reportAddNeighMeas_r10_SetValue(std::string value);
    std::string reportAddNeighMeas_r10_ValueToString(reportAddNeighMeas_r10_Enum value) const;
    uint64_t reportAddNeighMeas_r10_NumberOfValues() const;
    std::string reportAddNeighMeas_r10_ToString(uint32_t indent) const;
    std::string reportAddNeighMeas_r10_ToStringNoNewLines() const;
    int reportAddNeighMeas_r10_Clear();
    bool reportAddNeighMeas_r10_IsPresent() const;
private:
    bool reportAddNeighMeas_r10_present;
    reportAddNeighMeas_r10_Enum reportAddNeighMeas_r10_internal_value;

};

#endif
