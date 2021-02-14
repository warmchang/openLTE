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

#ifndef __SPS_ConfigUL_H__
#define __SPS_ConfigUL_H__

#include <array>
#include <cstdint>
#include <vector>

class SPS_ConfigUL
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
        setup() : semiPersistSchedIntervalUL_present{false}, implicitReleaseAfter_present{false}, twoIntervalsConfig_present{false} {};
    public:
        int Pack(std::vector<uint8_t> &bits);
        int Unpack(std::vector<uint8_t> bits);
        int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        std::string ToString(uint32_t indent) const;
        std::string ToStringNoNewLines() const;

        // semiPersistSchedIntervalUL
    public:
        enum semiPersistSchedIntervalUL_Enum {
            k_semiPersistSchedIntervalUL_sf10 = 0,
            k_semiPersistSchedIntervalUL_sf20,
            k_semiPersistSchedIntervalUL_sf32,
            k_semiPersistSchedIntervalUL_sf40,
            k_semiPersistSchedIntervalUL_sf64,
            k_semiPersistSchedIntervalUL_sf80,
            k_semiPersistSchedIntervalUL_sf128,
            k_semiPersistSchedIntervalUL_sf160,
            k_semiPersistSchedIntervalUL_sf320,
            k_semiPersistSchedIntervalUL_sf640,
            k_semiPersistSchedIntervalUL_spare6,
            k_semiPersistSchedIntervalUL_spare5,
            k_semiPersistSchedIntervalUL_spare4,
            k_semiPersistSchedIntervalUL_spare3,
            k_semiPersistSchedIntervalUL_spare2,
            k_semiPersistSchedIntervalUL_spare1,
        };
        int semiPersistSchedIntervalUL_Pack(std::vector<uint8_t> &bits);
        int semiPersistSchedIntervalUL_Unpack(std::vector<uint8_t> bits);
        int semiPersistSchedIntervalUL_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        semiPersistSchedIntervalUL_Enum semiPersistSchedIntervalUL_Value() const;
        int semiPersistSchedIntervalUL_SetValue(semiPersistSchedIntervalUL_Enum value);
        int semiPersistSchedIntervalUL_SetValue(std::string value);
        std::string semiPersistSchedIntervalUL_ValueToString(semiPersistSchedIntervalUL_Enum value) const;
        uint64_t semiPersistSchedIntervalUL_NumberOfValues() const;
        std::string semiPersistSchedIntervalUL_ToString(uint32_t indent) const;
        std::string semiPersistSchedIntervalUL_ToStringNoNewLines() const;
        int semiPersistSchedIntervalUL_Clear();
        bool semiPersistSchedIntervalUL_IsPresent() const;
    private:
        bool semiPersistSchedIntervalUL_present;
        semiPersistSchedIntervalUL_Enum semiPersistSchedIntervalUL_internal_value;

        // implicitReleaseAfter
    public:
        enum implicitReleaseAfter_Enum {
            k_implicitReleaseAfter_e2 = 0,
            k_implicitReleaseAfter_e3,
            k_implicitReleaseAfter_e4,
            k_implicitReleaseAfter_e8,
        };
        int implicitReleaseAfter_Pack(std::vector<uint8_t> &bits);
        int implicitReleaseAfter_Unpack(std::vector<uint8_t> bits);
        int implicitReleaseAfter_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        implicitReleaseAfter_Enum implicitReleaseAfter_Value() const;
        int implicitReleaseAfter_SetValue(implicitReleaseAfter_Enum value);
        int implicitReleaseAfter_SetValue(std::string value);
        std::string implicitReleaseAfter_ValueToString(implicitReleaseAfter_Enum value) const;
        uint64_t implicitReleaseAfter_NumberOfValues() const;
        std::string implicitReleaseAfter_ToString(uint32_t indent) const;
        std::string implicitReleaseAfter_ToStringNoNewLines() const;
        int implicitReleaseAfter_Clear();
        bool implicitReleaseAfter_IsPresent() const;
    private:
        bool implicitReleaseAfter_present;
        implicitReleaseAfter_Enum implicitReleaseAfter_internal_value;

        // p0-Persistent
    public:
        class p0_Persistent
        {
        public:
            p0_Persistent() : present{false}, p0_NominalPUSCH_Persistent_present{false}, p0_UE_PUSCH_Persistent_present{false} {};
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

            // p0-NominalPUSCH-Persistent
        public:
            int p0_NominalPUSCH_Persistent_Pack(std::vector<uint8_t> &bits);
            int p0_NominalPUSCH_Persistent_Unpack(std::vector<uint8_t> bits);
            int p0_NominalPUSCH_Persistent_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
            int64_t p0_NominalPUSCH_Persistent_Value() const;
            int p0_NominalPUSCH_Persistent_SetValue(int64_t value);
            std::string p0_NominalPUSCH_Persistent_ToString(uint32_t indent) const;
            std::string p0_NominalPUSCH_Persistent_ToStringNoNewLines() const;
            int p0_NominalPUSCH_Persistent_Clear();
            bool p0_NominalPUSCH_Persistent_IsPresent() const;
        private:
            bool p0_NominalPUSCH_Persistent_present;
            int64_t p0_NominalPUSCH_Persistent_internal_value;

            // p0-UE-PUSCH-Persistent
        public:
            int p0_UE_PUSCH_Persistent_Pack(std::vector<uint8_t> &bits);
            int p0_UE_PUSCH_Persistent_Unpack(std::vector<uint8_t> bits);
            int p0_UE_PUSCH_Persistent_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
            int64_t p0_UE_PUSCH_Persistent_Value() const;
            int p0_UE_PUSCH_Persistent_SetValue(int64_t value);
            std::string p0_UE_PUSCH_Persistent_ToString(uint32_t indent) const;
            std::string p0_UE_PUSCH_Persistent_ToStringNoNewLines() const;
            int p0_UE_PUSCH_Persistent_Clear();
            bool p0_UE_PUSCH_Persistent_IsPresent() const;
        private:
            bool p0_UE_PUSCH_Persistent_present;
            int64_t p0_UE_PUSCH_Persistent_internal_value;

        };

        p0_Persistent p0_Persistent_value;

        // twoIntervalsConfig
    public:
        enum twoIntervalsConfig_Enum {
            k_twoIntervalsConfig_true = 0,
        };
        int twoIntervalsConfig_Pack(std::vector<uint8_t> &bits);
        int twoIntervalsConfig_Unpack(std::vector<uint8_t> bits);
        int twoIntervalsConfig_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        twoIntervalsConfig_Enum twoIntervalsConfig_Value() const;
        int twoIntervalsConfig_SetValue(twoIntervalsConfig_Enum value);
        int twoIntervalsConfig_SetValue(std::string value);
        std::string twoIntervalsConfig_ValueToString(twoIntervalsConfig_Enum value) const;
        uint64_t twoIntervalsConfig_NumberOfValues() const;
        std::string twoIntervalsConfig_ToString(uint32_t indent) const;
        std::string twoIntervalsConfig_ToStringNoNewLines() const;
        int twoIntervalsConfig_Clear();
        bool twoIntervalsConfig_IsPresent() const;
    private:
        bool twoIntervalsConfig_present;
        twoIntervalsConfig_Enum twoIntervalsConfig_internal_value;

    };

    setup setup_value;

};

#endif
