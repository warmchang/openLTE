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

#ifndef __ReportConfigInterRAT_H__
#define __ReportConfigInterRAT_H__

#include "ThresholdUTRA.h"
#include "ThresholdGERAN.h"
#include "ThresholdCDMA2000.h"
#include "ThresholdEUTRA.h"
#include "ThresholdUTRA.h"
#include "ThresholdGERAN.h"
#include "ThresholdCDMA2000.h"
#include "Hysteresis.h"
#include "TimeToTrigger.h"
#include "ReportInterval.h"

#include <array>
#include <cstdint>
#include <vector>

class ReportConfigInterRAT
{
public:
    ReportConfigInterRAT() : triggerType_present{false}, maxReportCells_present{false}, reportInterval_present{false}, reportAmount_present{false}, si_RequestForHO_r9_present{false}, reportQuantityUTRA_FDD_r10_present{false} {};
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
            k_eventId_eventB1 = 0,
            k_eventId_eventB2,
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

        // eventB1
    public:
        class eventId_eventB1
        {
        public:
            eventId_eventB1() : b1_Threshold_present{false} {};
        public:
            int Pack(std::vector<uint8_t> &bits);
            int Unpack(std::vector<uint8_t> bits);
            int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
            std::string ToString(uint32_t indent) const;
            std::string ToStringNoNewLines() const;

            // b1-Threshold
        public:
            enum b1_Threshold_Enum {
                k_b1_Threshold_b1_ThresholdUTRA = 0,
                k_b1_Threshold_b1_ThresholdGERAN,
                k_b1_Threshold_b1_ThresholdCDMA2000,
            };
            int b1_Threshold_Pack(std::vector<uint8_t> &bits);
            int b1_Threshold_Unpack(std::vector<uint8_t> bits);
            int b1_Threshold_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
            b1_Threshold_Enum b1_Threshold_Choice() const;
            int b1_Threshold_SetChoice(b1_Threshold_Enum choice);
            std::string b1_Threshold_ChoiceToString(b1_Threshold_Enum value) const;
            uint64_t b1_Threshold_NumberOfChoices() const;
            std::string b1_Threshold_ToString(uint32_t indent) const;
            std::string b1_Threshold_ToStringNoNewLines() const;
            int b1_Threshold_Clear();
            bool b1_Threshold_IsPresent() const;
        private:
            bool b1_Threshold_present;
            b1_Threshold_Enum b1_Threshold_internal_choice;

            // b1-ThresholdUTRA
        public:
            ThresholdUTRA* b1_Threshold_b1_ThresholdUTRA_Set();
            int b1_Threshold_b1_ThresholdUTRA_Set(ThresholdUTRA &value);
            const ThresholdUTRA& b1_Threshold_b1_ThresholdUTRA_Get() const;
            std::string b1_Threshold_b1_ThresholdUTRA_ToString(uint32_t indent) const;
            std::string b1_Threshold_b1_ThresholdUTRA_ToStringNoNewLines() const;
            int b1_Threshold_b1_ThresholdUTRA_Clear();
            bool b1_Threshold_b1_ThresholdUTRA_IsPresent() const;
        private:
            bool b1_Threshold_b1_ThresholdUTRA_present;
            ThresholdUTRA b1_Threshold_b1_ThresholdUTRA;

            // b1-ThresholdGERAN
        public:
            ThresholdGERAN* b1_Threshold_b1_ThresholdGERAN_Set();
            int b1_Threshold_b1_ThresholdGERAN_Set(ThresholdGERAN &value);
            const ThresholdGERAN& b1_Threshold_b1_ThresholdGERAN_Get() const;
            std::string b1_Threshold_b1_ThresholdGERAN_ToString(uint32_t indent) const;
            std::string b1_Threshold_b1_ThresholdGERAN_ToStringNoNewLines() const;
            int b1_Threshold_b1_ThresholdGERAN_Clear();
            bool b1_Threshold_b1_ThresholdGERAN_IsPresent() const;
        private:
            bool b1_Threshold_b1_ThresholdGERAN_present;
            ThresholdGERAN b1_Threshold_b1_ThresholdGERAN;

            // b1-ThresholdCDMA2000
        public:
            ThresholdCDMA2000* b1_Threshold_b1_ThresholdCDMA2000_Set();
            int b1_Threshold_b1_ThresholdCDMA2000_Set(ThresholdCDMA2000 &value);
            const ThresholdCDMA2000& b1_Threshold_b1_ThresholdCDMA2000_Get() const;
            std::string b1_Threshold_b1_ThresholdCDMA2000_ToString(uint32_t indent) const;
            std::string b1_Threshold_b1_ThresholdCDMA2000_ToStringNoNewLines() const;
            int b1_Threshold_b1_ThresholdCDMA2000_Clear();
            bool b1_Threshold_b1_ThresholdCDMA2000_IsPresent() const;
        private:
            bool b1_Threshold_b1_ThresholdCDMA2000_present;
            ThresholdCDMA2000 b1_Threshold_b1_ThresholdCDMA2000;


        };

        eventId_eventB1 eventId_eventB1_value;

        // eventB2
    public:
        class eventId_eventB2
        {
        public:
            eventId_eventB2() : b2_Threshold1_present{false}, b2_Threshold2_present{false} {};
        public:
            int Pack(std::vector<uint8_t> &bits);
            int Unpack(std::vector<uint8_t> bits);
            int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
            std::string ToString(uint32_t indent) const;
            std::string ToStringNoNewLines() const;

            // b2-Threshold1
        public:
            ThresholdEUTRA* b2_Threshold1_Set();
            int b2_Threshold1_Set(ThresholdEUTRA &value);
            const ThresholdEUTRA& b2_Threshold1_Get() const;
            std::string b2_Threshold1_ToString(uint32_t indent) const;
            std::string b2_Threshold1_ToStringNoNewLines() const;
            int b2_Threshold1_Clear();
            bool b2_Threshold1_IsPresent() const;
        private:
            bool b2_Threshold1_present;
            ThresholdEUTRA b2_Threshold1;

            // b2-Threshold2
        public:
            enum b2_Threshold2_Enum {
                k_b2_Threshold2_b2_Threshold2UTRA = 0,
                k_b2_Threshold2_b2_Threshold2GERAN,
                k_b2_Threshold2_b2_Threshold2CDMA2000,
            };
            int b2_Threshold2_Pack(std::vector<uint8_t> &bits);
            int b2_Threshold2_Unpack(std::vector<uint8_t> bits);
            int b2_Threshold2_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
            b2_Threshold2_Enum b2_Threshold2_Choice() const;
            int b2_Threshold2_SetChoice(b2_Threshold2_Enum choice);
            std::string b2_Threshold2_ChoiceToString(b2_Threshold2_Enum value) const;
            uint64_t b2_Threshold2_NumberOfChoices() const;
            std::string b2_Threshold2_ToString(uint32_t indent) const;
            std::string b2_Threshold2_ToStringNoNewLines() const;
            int b2_Threshold2_Clear();
            bool b2_Threshold2_IsPresent() const;
        private:
            bool b2_Threshold2_present;
            b2_Threshold2_Enum b2_Threshold2_internal_choice;

            // b2-Threshold2UTRA
        public:
            ThresholdUTRA* b2_Threshold2_b2_Threshold2UTRA_Set();
            int b2_Threshold2_b2_Threshold2UTRA_Set(ThresholdUTRA &value);
            const ThresholdUTRA& b2_Threshold2_b2_Threshold2UTRA_Get() const;
            std::string b2_Threshold2_b2_Threshold2UTRA_ToString(uint32_t indent) const;
            std::string b2_Threshold2_b2_Threshold2UTRA_ToStringNoNewLines() const;
            int b2_Threshold2_b2_Threshold2UTRA_Clear();
            bool b2_Threshold2_b2_Threshold2UTRA_IsPresent() const;
        private:
            bool b2_Threshold2_b2_Threshold2UTRA_present;
            ThresholdUTRA b2_Threshold2_b2_Threshold2UTRA;

            // b2-Threshold2GERAN
        public:
            ThresholdGERAN* b2_Threshold2_b2_Threshold2GERAN_Set();
            int b2_Threshold2_b2_Threshold2GERAN_Set(ThresholdGERAN &value);
            const ThresholdGERAN& b2_Threshold2_b2_Threshold2GERAN_Get() const;
            std::string b2_Threshold2_b2_Threshold2GERAN_ToString(uint32_t indent) const;
            std::string b2_Threshold2_b2_Threshold2GERAN_ToStringNoNewLines() const;
            int b2_Threshold2_b2_Threshold2GERAN_Clear();
            bool b2_Threshold2_b2_Threshold2GERAN_IsPresent() const;
        private:
            bool b2_Threshold2_b2_Threshold2GERAN_present;
            ThresholdGERAN b2_Threshold2_b2_Threshold2GERAN;

            // b2-Threshold2CDMA2000
        public:
            ThresholdCDMA2000* b2_Threshold2_b2_Threshold2CDMA2000_Set();
            int b2_Threshold2_b2_Threshold2CDMA2000_Set(ThresholdCDMA2000 &value);
            const ThresholdCDMA2000& b2_Threshold2_b2_Threshold2CDMA2000_Get() const;
            std::string b2_Threshold2_b2_Threshold2CDMA2000_ToString(uint32_t indent) const;
            std::string b2_Threshold2_b2_Threshold2CDMA2000_ToStringNoNewLines() const;
            int b2_Threshold2_b2_Threshold2CDMA2000_Clear();
            bool b2_Threshold2_b2_Threshold2CDMA2000_IsPresent() const;
        private:
            bool b2_Threshold2_b2_Threshold2CDMA2000_present;
            ThresholdCDMA2000 b2_Threshold2_b2_Threshold2CDMA2000;


        };

        eventId_eventB2 eventId_eventB2_value;


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
            k_purpose_reportStrongestCellsForSON,
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

    // reportQuantityUTRA-FDD-r10
public:
    enum reportQuantityUTRA_FDD_r10_Enum {
        k_reportQuantityUTRA_FDD_r10_both = 0,
    };
    int reportQuantityUTRA_FDD_r10_Pack(std::vector<uint8_t> &bits);
    int reportQuantityUTRA_FDD_r10_Unpack(std::vector<uint8_t> bits);
    int reportQuantityUTRA_FDD_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    reportQuantityUTRA_FDD_r10_Enum reportQuantityUTRA_FDD_r10_Value() const;
    int reportQuantityUTRA_FDD_r10_SetValue(reportQuantityUTRA_FDD_r10_Enum value);
    int reportQuantityUTRA_FDD_r10_SetValue(std::string value);
    std::string reportQuantityUTRA_FDD_r10_ValueToString(reportQuantityUTRA_FDD_r10_Enum value) const;
    uint64_t reportQuantityUTRA_FDD_r10_NumberOfValues() const;
    std::string reportQuantityUTRA_FDD_r10_ToString(uint32_t indent) const;
    std::string reportQuantityUTRA_FDD_r10_ToStringNoNewLines() const;
    int reportQuantityUTRA_FDD_r10_Clear();
    bool reportQuantityUTRA_FDD_r10_IsPresent() const;
private:
    bool reportQuantityUTRA_FDD_r10_present;
    reportQuantityUTRA_FDD_r10_Enum reportQuantityUTRA_FDD_r10_internal_value;

};

#endif
