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

#ifndef __SPS_ConfigDL_H__
#define __SPS_ConfigDL_H__

#include "N1_PUCCH_AN_PersistentList.h"
#include "N1_PUCCH_AN_PersistentList.h"

#include <array>
#include <cstdint>
#include <vector>

class SPS_ConfigDL
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
        setup() : semiPersistSchedIntervalDL_present{false}, numberOfConfSPS_Processes_present{false}, n1_PUCCH_AN_PersistentList_present{false}, twoAntennaPortActivated_r10_present{false}, n1_PUCCH_AN_PersistentListP1_r10_present{false} {};
    public:
        int Pack(std::vector<uint8_t> &bits);
        int Unpack(std::vector<uint8_t> bits);
        int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        std::string ToString(uint32_t indent) const;
        std::string ToStringNoNewLines() const;

        // semiPersistSchedIntervalDL
    public:
        enum semiPersistSchedIntervalDL_Enum {
            k_semiPersistSchedIntervalDL_sf10 = 0,
            k_semiPersistSchedIntervalDL_sf20,
            k_semiPersistSchedIntervalDL_sf32,
            k_semiPersistSchedIntervalDL_sf40,
            k_semiPersistSchedIntervalDL_sf64,
            k_semiPersistSchedIntervalDL_sf80,
            k_semiPersistSchedIntervalDL_sf128,
            k_semiPersistSchedIntervalDL_sf160,
            k_semiPersistSchedIntervalDL_sf320,
            k_semiPersistSchedIntervalDL_sf640,
            k_semiPersistSchedIntervalDL_spare6,
            k_semiPersistSchedIntervalDL_spare5,
            k_semiPersistSchedIntervalDL_spare4,
            k_semiPersistSchedIntervalDL_spare3,
            k_semiPersistSchedIntervalDL_spare2,
            k_semiPersistSchedIntervalDL_spare1,
        };
        int semiPersistSchedIntervalDL_Pack(std::vector<uint8_t> &bits);
        int semiPersistSchedIntervalDL_Unpack(std::vector<uint8_t> bits);
        int semiPersistSchedIntervalDL_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        semiPersistSchedIntervalDL_Enum semiPersistSchedIntervalDL_Value() const;
        int semiPersistSchedIntervalDL_SetValue(semiPersistSchedIntervalDL_Enum value);
        int semiPersistSchedIntervalDL_SetValue(std::string value);
        std::string semiPersistSchedIntervalDL_ValueToString(semiPersistSchedIntervalDL_Enum value) const;
        uint64_t semiPersistSchedIntervalDL_NumberOfValues() const;
        std::string semiPersistSchedIntervalDL_ToString(uint32_t indent) const;
        std::string semiPersistSchedIntervalDL_ToStringNoNewLines() const;
        int semiPersistSchedIntervalDL_Clear();
        bool semiPersistSchedIntervalDL_IsPresent() const;
    private:
        bool semiPersistSchedIntervalDL_present;
        semiPersistSchedIntervalDL_Enum semiPersistSchedIntervalDL_internal_value;

        // numberOfConfSPS-Processes
    public:
        int numberOfConfSPS_Processes_Pack(std::vector<uint8_t> &bits);
        int numberOfConfSPS_Processes_Unpack(std::vector<uint8_t> bits);
        int numberOfConfSPS_Processes_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        int64_t numberOfConfSPS_Processes_Value() const;
        int numberOfConfSPS_Processes_SetValue(int64_t value);
        std::string numberOfConfSPS_Processes_ToString(uint32_t indent) const;
        std::string numberOfConfSPS_Processes_ToStringNoNewLines() const;
        int numberOfConfSPS_Processes_Clear();
        bool numberOfConfSPS_Processes_IsPresent() const;
    private:
        bool numberOfConfSPS_Processes_present;
        int64_t numberOfConfSPS_Processes_internal_value;

        // n1-PUCCH-AN-PersistentList
    public:
        N1_PUCCH_AN_PersistentList* n1_PUCCH_AN_PersistentList_Set();
        int n1_PUCCH_AN_PersistentList_Set(N1_PUCCH_AN_PersistentList &value);
        const N1_PUCCH_AN_PersistentList& n1_PUCCH_AN_PersistentList_Get() const;
        std::string n1_PUCCH_AN_PersistentList_ToString(uint32_t indent) const;
        std::string n1_PUCCH_AN_PersistentList_ToStringNoNewLines() const;
        int n1_PUCCH_AN_PersistentList_Clear();
        bool n1_PUCCH_AN_PersistentList_IsPresent() const;
    private:
        bool n1_PUCCH_AN_PersistentList_present;
        N1_PUCCH_AN_PersistentList n1_PUCCH_AN_PersistentList;

        // twoAntennaPortActivated-r10
    public:
        enum twoAntennaPortActivated_r10_Enum {
            k_twoAntennaPortActivated_r10_true = 0,
        };
        int twoAntennaPortActivated_r10_Pack(std::vector<uint8_t> &bits);
        int twoAntennaPortActivated_r10_Unpack(std::vector<uint8_t> bits);
        int twoAntennaPortActivated_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        twoAntennaPortActivated_r10_Enum twoAntennaPortActivated_r10_Value() const;
        int twoAntennaPortActivated_r10_SetValue(twoAntennaPortActivated_r10_Enum value);
        int twoAntennaPortActivated_r10_SetValue(std::string value);
        std::string twoAntennaPortActivated_r10_ValueToString(twoAntennaPortActivated_r10_Enum value) const;
        uint64_t twoAntennaPortActivated_r10_NumberOfValues() const;
        std::string twoAntennaPortActivated_r10_ToString(uint32_t indent) const;
        std::string twoAntennaPortActivated_r10_ToStringNoNewLines() const;
        int twoAntennaPortActivated_r10_Clear();
        bool twoAntennaPortActivated_r10_IsPresent() const;
    private:
        bool twoAntennaPortActivated_r10_present;
        twoAntennaPortActivated_r10_Enum twoAntennaPortActivated_r10_internal_value;

        // n1-PUCCH-AN-PersistentListP1-r10
    public:
        N1_PUCCH_AN_PersistentList* n1_PUCCH_AN_PersistentListP1_r10_Set();
        int n1_PUCCH_AN_PersistentListP1_r10_Set(N1_PUCCH_AN_PersistentList &value);
        const N1_PUCCH_AN_PersistentList& n1_PUCCH_AN_PersistentListP1_r10_Get() const;
        std::string n1_PUCCH_AN_PersistentListP1_r10_ToString(uint32_t indent) const;
        std::string n1_PUCCH_AN_PersistentListP1_r10_ToStringNoNewLines() const;
        int n1_PUCCH_AN_PersistentListP1_r10_Clear();
        bool n1_PUCCH_AN_PersistentListP1_r10_IsPresent() const;
    private:
        bool n1_PUCCH_AN_PersistentListP1_r10_present;
        N1_PUCCH_AN_PersistentList n1_PUCCH_AN_PersistentListP1_r10;

    };

    setup setup_value;

};

#endif
