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

#ifndef __PUCCH_ConfigDedicated_H__
#define __PUCCH_ConfigDedicated_H__

#include <array>
#include <cstdint>
#include <vector>

class PUCCH_ConfigDedicated
{
public:
    PUCCH_ConfigDedicated() : ackNackRepetition_present{false}, tdd_AckNackFeedbackMode_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // ackNackRepetition
public:
    enum ackNackRepetition_Enum {
        k_ackNackRepetition_release = 0,
        k_ackNackRepetition_setup,
    };
    int ackNackRepetition_Pack(std::vector<uint8_t> &bits);
    int ackNackRepetition_Unpack(std::vector<uint8_t> bits);
    int ackNackRepetition_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    ackNackRepetition_Enum ackNackRepetition_Choice() const;
    int ackNackRepetition_SetChoice(ackNackRepetition_Enum choice);
    std::string ackNackRepetition_ChoiceToString(ackNackRepetition_Enum value) const;
    uint64_t ackNackRepetition_NumberOfChoices() const;
    std::string ackNackRepetition_ToString(uint32_t indent) const;
    std::string ackNackRepetition_ToStringNoNewLines() const;
    int ackNackRepetition_Clear();
    bool ackNackRepetition_IsPresent() const;
private:
    bool ackNackRepetition_present;
    ackNackRepetition_Enum ackNackRepetition_internal_choice;

    // release
public:
    int ackNackRepetition_release_Pack(std::vector<uint8_t> &bits) {return 0;};
    int ackNackRepetition_release_Unpack(std::vector<uint8_t> bits) {return 0;};
    int ackNackRepetition_release_Unpack(std::vector<uint8_t> bits, uint32_t &idx) {return 0;};
    bool ackNackRepetition_release_IsPresent() const {return true;};
    std::string ackNackRepetition_release_ToString(uint32_t indent) {return "";};
    std::string ackNackRepetition_release_ToStringNoNewLines() {return "";};

    // setup
public:
    class ackNackRepetition_setup
    {
    public:
        ackNackRepetition_setup() : repetitionFactor_present{false}, n1PUCCH_AN_Rep_present{false} {};
    public:
        int Pack(std::vector<uint8_t> &bits);
        int Unpack(std::vector<uint8_t> bits);
        int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        std::string ToString(uint32_t indent) const;
        std::string ToStringNoNewLines() const;

        // repetitionFactor
    public:
        enum repetitionFactor_Enum {
            k_repetitionFactor_n2 = 0,
            k_repetitionFactor_n4,
            k_repetitionFactor_n6,
            k_repetitionFactor_spare1,
        };
        int repetitionFactor_Pack(std::vector<uint8_t> &bits);
        int repetitionFactor_Unpack(std::vector<uint8_t> bits);
        int repetitionFactor_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        repetitionFactor_Enum repetitionFactor_Value() const;
        int repetitionFactor_SetValue(repetitionFactor_Enum value);
        int repetitionFactor_SetValue(std::string value);
        std::string repetitionFactor_ValueToString(repetitionFactor_Enum value) const;
        uint64_t repetitionFactor_NumberOfValues() const;
        std::string repetitionFactor_ToString(uint32_t indent) const;
        std::string repetitionFactor_ToStringNoNewLines() const;
        int repetitionFactor_Clear();
        bool repetitionFactor_IsPresent() const;
    private:
        bool repetitionFactor_present;
        repetitionFactor_Enum repetitionFactor_internal_value;

        // n1PUCCH-AN-Rep
    public:
        int n1PUCCH_AN_Rep_Pack(std::vector<uint8_t> &bits);
        int n1PUCCH_AN_Rep_Unpack(std::vector<uint8_t> bits);
        int n1PUCCH_AN_Rep_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        int64_t n1PUCCH_AN_Rep_Value() const;
        int n1PUCCH_AN_Rep_SetValue(int64_t value);
        std::string n1PUCCH_AN_Rep_ToString(uint32_t indent) const;
        std::string n1PUCCH_AN_Rep_ToStringNoNewLines() const;
        int n1PUCCH_AN_Rep_Clear();
        bool n1PUCCH_AN_Rep_IsPresent() const;
    private:
        bool n1PUCCH_AN_Rep_present;
        int64_t n1PUCCH_AN_Rep_internal_value;

    };

    ackNackRepetition_setup ackNackRepetition_setup_value;


    // tdd-AckNackFeedbackMode
public:
    enum tdd_AckNackFeedbackMode_Enum {
        k_tdd_AckNackFeedbackMode_bundling = 0,
        k_tdd_AckNackFeedbackMode_multiplexing,
    };
    int tdd_AckNackFeedbackMode_Pack(std::vector<uint8_t> &bits);
    int tdd_AckNackFeedbackMode_Unpack(std::vector<uint8_t> bits);
    int tdd_AckNackFeedbackMode_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    tdd_AckNackFeedbackMode_Enum tdd_AckNackFeedbackMode_Value() const;
    int tdd_AckNackFeedbackMode_SetValue(tdd_AckNackFeedbackMode_Enum value);
    int tdd_AckNackFeedbackMode_SetValue(std::string value);
    std::string tdd_AckNackFeedbackMode_ValueToString(tdd_AckNackFeedbackMode_Enum value) const;
    uint64_t tdd_AckNackFeedbackMode_NumberOfValues() const;
    std::string tdd_AckNackFeedbackMode_ToString(uint32_t indent) const;
    std::string tdd_AckNackFeedbackMode_ToStringNoNewLines() const;
    int tdd_AckNackFeedbackMode_Clear();
    bool tdd_AckNackFeedbackMode_IsPresent() const;
private:
    bool tdd_AckNackFeedbackMode_present;
    tdd_AckNackFeedbackMode_Enum tdd_AckNackFeedbackMode_internal_value;

};

#endif
