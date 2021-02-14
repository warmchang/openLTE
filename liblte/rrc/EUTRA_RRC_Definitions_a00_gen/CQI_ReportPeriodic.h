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

#ifndef __CQI_ReportPeriodic_H__
#define __CQI_ReportPeriodic_H__

#include <array>
#include <cstdint>
#include <vector>

class CQI_ReportPeriodic
{
public:
    enum Enum {
        k_release = 0,
        k_setup,
    };
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    Enum Choice() const;
    int SetChoice(Enum choice);
    std::string ChoiceToString(Enum value) const;
    uint64_t NumberOfChoices() const;
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;
    int Clear();
    bool IsPresent() const;
private:
    bool present;
    Enum internal_choice;

    // release
public:
    int release_Pack(std::vector<uint8_t> &bits) {return 0;};
    int release_Unpack(std::vector<uint8_t> bits) {return 0;};
    int release_Unpack(std::vector<uint8_t> bits, uint32_t &idx) {return 0;};
    bool release_IsPresent() const {return true;};
    std::string release_ToString(uint32_t indent) {return "";};
    std::string release_ToStringNoNewLines() {return "";};

    // setup
public:
    class setup
    {
    public:
        setup() : cqi_PUCCH_ResourceIndex_present{false}, cqi_pmi_ConfigIndex_present{false}, cqi_FormatIndicatorPeriodic_present{false}, ri_ConfigIndex_present{false}, simultaneousAckNackAndCQI_present{false} {};
    public:
        int Pack(std::vector<uint8_t> &bits);
        int Unpack(std::vector<uint8_t> bits);
        int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        std::string ToString(uint32_t indent) const;
        std::string ToStringNoNewLines() const;

        // cqi-PUCCH-ResourceIndex
    public:
        int cqi_PUCCH_ResourceIndex_Pack(std::vector<uint8_t> &bits);
        int cqi_PUCCH_ResourceIndex_Unpack(std::vector<uint8_t> bits);
        int cqi_PUCCH_ResourceIndex_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        int64_t cqi_PUCCH_ResourceIndex_Value() const;
        int cqi_PUCCH_ResourceIndex_SetValue(int64_t value);
        std::string cqi_PUCCH_ResourceIndex_ToString(uint32_t indent) const;
        std::string cqi_PUCCH_ResourceIndex_ToStringNoNewLines() const;
        int cqi_PUCCH_ResourceIndex_Clear();
        bool cqi_PUCCH_ResourceIndex_IsPresent() const;
    private:
        bool cqi_PUCCH_ResourceIndex_present;
        int64_t cqi_PUCCH_ResourceIndex_internal_value;

        // cqi-pmi-ConfigIndex
    public:
        int cqi_pmi_ConfigIndex_Pack(std::vector<uint8_t> &bits);
        int cqi_pmi_ConfigIndex_Unpack(std::vector<uint8_t> bits);
        int cqi_pmi_ConfigIndex_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        int64_t cqi_pmi_ConfigIndex_Value() const;
        int cqi_pmi_ConfigIndex_SetValue(int64_t value);
        std::string cqi_pmi_ConfigIndex_ToString(uint32_t indent) const;
        std::string cqi_pmi_ConfigIndex_ToStringNoNewLines() const;
        int cqi_pmi_ConfigIndex_Clear();
        bool cqi_pmi_ConfigIndex_IsPresent() const;
    private:
        bool cqi_pmi_ConfigIndex_present;
        int64_t cqi_pmi_ConfigIndex_internal_value;

        // cqi-FormatIndicatorPeriodic
    public:
        enum cqi_FormatIndicatorPeriodic_Enum {
            k_cqi_FormatIndicatorPeriodic_widebandCQI = 0,
            k_cqi_FormatIndicatorPeriodic_subbandCQI,
        };
        int cqi_FormatIndicatorPeriodic_Pack(std::vector<uint8_t> &bits);
        int cqi_FormatIndicatorPeriodic_Unpack(std::vector<uint8_t> bits);
        int cqi_FormatIndicatorPeriodic_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        cqi_FormatIndicatorPeriodic_Enum cqi_FormatIndicatorPeriodic_Choice() const;
        int cqi_FormatIndicatorPeriodic_SetChoice(cqi_FormatIndicatorPeriodic_Enum choice);
        std::string cqi_FormatIndicatorPeriodic_ChoiceToString(cqi_FormatIndicatorPeriodic_Enum value) const;
        uint64_t cqi_FormatIndicatorPeriodic_NumberOfChoices() const;
        std::string cqi_FormatIndicatorPeriodic_ToString(uint32_t indent) const;
        std::string cqi_FormatIndicatorPeriodic_ToStringNoNewLines() const;
        int cqi_FormatIndicatorPeriodic_Clear();
        bool cqi_FormatIndicatorPeriodic_IsPresent() const;
    private:
        bool cqi_FormatIndicatorPeriodic_present;
        cqi_FormatIndicatorPeriodic_Enum cqi_FormatIndicatorPeriodic_internal_choice;

        // widebandCQI
    public:
        int cqi_FormatIndicatorPeriodic_widebandCQI_Pack(std::vector<uint8_t> &bits) {return 0;};
        int cqi_FormatIndicatorPeriodic_widebandCQI_Unpack(std::vector<uint8_t> bits) {return 0;};
        int cqi_FormatIndicatorPeriodic_widebandCQI_Unpack(std::vector<uint8_t> bits, uint32_t &idx) {return 0;};
        bool cqi_FormatIndicatorPeriodic_widebandCQI_IsPresent() const {return true;};
        std::string cqi_FormatIndicatorPeriodic_widebandCQI_ToString(uint32_t indent) {return "";};
        std::string cqi_FormatIndicatorPeriodic_widebandCQI_ToStringNoNewLines() {return "";};

        // subbandCQI
    public:
        class cqi_FormatIndicatorPeriodic_subbandCQI
        {
        public:
            cqi_FormatIndicatorPeriodic_subbandCQI() : k_present{false} {};
        public:
            int Pack(std::vector<uint8_t> &bits);
            int Unpack(std::vector<uint8_t> bits);
            int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
            std::string ToString(uint32_t indent) const;
            std::string ToStringNoNewLines() const;

            // k
        public:
            int k_Pack(std::vector<uint8_t> &bits);
            int k_Unpack(std::vector<uint8_t> bits);
            int k_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
            int64_t k_Value() const;
            int k_SetValue(int64_t value);
            std::string k_ToString(uint32_t indent) const;
            std::string k_ToStringNoNewLines() const;
            int k_Clear();
            bool k_IsPresent() const;
        private:
            bool k_present;
            int64_t k_internal_value;

        };

        cqi_FormatIndicatorPeriodic_subbandCQI cqi_FormatIndicatorPeriodic_subbandCQI_value;


        // ri-ConfigIndex
    public:
        int ri_ConfigIndex_Pack(std::vector<uint8_t> &bits);
        int ri_ConfigIndex_Unpack(std::vector<uint8_t> bits);
        int ri_ConfigIndex_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        int64_t ri_ConfigIndex_Value() const;
        int ri_ConfigIndex_SetValue(int64_t value);
        std::string ri_ConfigIndex_ToString(uint32_t indent) const;
        std::string ri_ConfigIndex_ToStringNoNewLines() const;
        int ri_ConfigIndex_Clear();
        bool ri_ConfigIndex_IsPresent() const;
    private:
        bool ri_ConfigIndex_present;
        int64_t ri_ConfigIndex_internal_value;

        // simultaneousAckNackAndCQI
    public:
        int simultaneousAckNackAndCQI_Pack(std::vector<uint8_t> &bits);
        int simultaneousAckNackAndCQI_Unpack(std::vector<uint8_t> bits);
        int simultaneousAckNackAndCQI_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        bool simultaneousAckNackAndCQI_Value() const;
        int simultaneousAckNackAndCQI_SetValue(bool value);
        std::string simultaneousAckNackAndCQI_ToString(uint32_t indent) const;
        std::string simultaneousAckNackAndCQI_ToStringNoNewLines() const;
        int simultaneousAckNackAndCQI_Clear();
        bool simultaneousAckNackAndCQI_IsPresent() const;
    private:
        bool simultaneousAckNackAndCQI_present;
        bool simultaneousAckNackAndCQI_internal_value;

    };

    setup setup_value;

};

#endif
