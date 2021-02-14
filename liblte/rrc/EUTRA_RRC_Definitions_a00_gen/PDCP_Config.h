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

#ifndef __PDCP_Config_H__
#define __PDCP_Config_H__

#include <array>
#include <cstdint>
#include <vector>

class PDCP_Config
{
public:
    PDCP_Config() : discardTimer_present{false}, headerCompression_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // discardTimer
public:
    enum discardTimer_Enum {
        k_discardTimer_ms50 = 0,
        k_discardTimer_ms100,
        k_discardTimer_ms150,
        k_discardTimer_ms300,
        k_discardTimer_ms500,
        k_discardTimer_ms750,
        k_discardTimer_ms1500,
        k_discardTimer_infinity,
    };
    int discardTimer_Pack(std::vector<uint8_t> &bits);
    int discardTimer_Unpack(std::vector<uint8_t> bits);
    int discardTimer_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    discardTimer_Enum discardTimer_Value() const;
    int discardTimer_SetValue(discardTimer_Enum value);
    int discardTimer_SetValue(std::string value);
    std::string discardTimer_ValueToString(discardTimer_Enum value) const;
    uint64_t discardTimer_NumberOfValues() const;
    std::string discardTimer_ToString(uint32_t indent) const;
    std::string discardTimer_ToStringNoNewLines() const;
    int discardTimer_Clear();
    bool discardTimer_IsPresent() const;
private:
    bool discardTimer_present;
    discardTimer_Enum discardTimer_internal_value;

    // rlc-AM
public:
    class rlc_AM
    {
    public:
        rlc_AM() : present{false}, statusReportRequired_present{false} {};
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

        // statusReportRequired
    public:
        int statusReportRequired_Pack(std::vector<uint8_t> &bits);
        int statusReportRequired_Unpack(std::vector<uint8_t> bits);
        int statusReportRequired_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        bool statusReportRequired_Value() const;
        int statusReportRequired_SetValue(bool value);
        std::string statusReportRequired_ToString(uint32_t indent) const;
        std::string statusReportRequired_ToStringNoNewLines() const;
        int statusReportRequired_Clear();
        bool statusReportRequired_IsPresent() const;
    private:
        bool statusReportRequired_present;
        bool statusReportRequired_internal_value;

    };

    rlc_AM rlc_AM_value;

    // rlc-UM
public:
    class rlc_UM
    {
    public:
        rlc_UM() : present{false}, pdcp_SN_Size_present{false} {};
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

        // pdcp-SN-Size
    public:
        enum pdcp_SN_Size_Enum {
            k_pdcp_SN_Size_len7bits = 0,
            k_pdcp_SN_Size_len12bits,
        };
        int pdcp_SN_Size_Pack(std::vector<uint8_t> &bits);
        int pdcp_SN_Size_Unpack(std::vector<uint8_t> bits);
        int pdcp_SN_Size_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        pdcp_SN_Size_Enum pdcp_SN_Size_Value() const;
        int pdcp_SN_Size_SetValue(pdcp_SN_Size_Enum value);
        int pdcp_SN_Size_SetValue(std::string value);
        std::string pdcp_SN_Size_ValueToString(pdcp_SN_Size_Enum value) const;
        uint64_t pdcp_SN_Size_NumberOfValues() const;
        std::string pdcp_SN_Size_ToString(uint32_t indent) const;
        std::string pdcp_SN_Size_ToStringNoNewLines() const;
        int pdcp_SN_Size_Clear();
        bool pdcp_SN_Size_IsPresent() const;
    private:
        bool pdcp_SN_Size_present;
        pdcp_SN_Size_Enum pdcp_SN_Size_internal_value;

    };

    rlc_UM rlc_UM_value;

    // headerCompression
public:
    enum headerCompression_Enum {
        k_headerCompression_notUsed = 0,
        k_headerCompression_rohc,
    };
    int headerCompression_Pack(std::vector<uint8_t> &bits);
    int headerCompression_Unpack(std::vector<uint8_t> bits);
    int headerCompression_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    headerCompression_Enum headerCompression_Choice() const;
    int headerCompression_SetChoice(headerCompression_Enum choice);
    std::string headerCompression_ChoiceToString(headerCompression_Enum value) const;
    uint64_t headerCompression_NumberOfChoices() const;
    std::string headerCompression_ToString(uint32_t indent) const;
    std::string headerCompression_ToStringNoNewLines() const;
    int headerCompression_Clear();
    bool headerCompression_IsPresent() const;
private:
    bool headerCompression_present;
    headerCompression_Enum headerCompression_internal_choice;

    // notUsed
public:
    int headerCompression_notUsed_Pack(std::vector<uint8_t> &bits) {return 0;};
    int headerCompression_notUsed_Unpack(std::vector<uint8_t> bits) {return 0;};
    int headerCompression_notUsed_Unpack(std::vector<uint8_t> bits, uint32_t &idx) {return 0;};
    bool headerCompression_notUsed_IsPresent() const {return true;};
    std::string headerCompression_notUsed_ToString(uint32_t indent) {return "";};
    std::string headerCompression_notUsed_ToStringNoNewLines() {return "";};

    // rohc
public:
    class headerCompression_rohc
    {
    public:
        headerCompression_rohc() : maxCID_present{false} {};
    public:
        int Pack(std::vector<uint8_t> &bits);
        int Unpack(std::vector<uint8_t> bits);
        int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        std::string ToString(uint32_t indent) const;
        std::string ToStringNoNewLines() const;

        // maxCID
    public:
        int maxCID_Pack(std::vector<uint8_t> &bits);
        int maxCID_Unpack(std::vector<uint8_t> bits);
        int maxCID_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        int64_t maxCID_Value() const;
        int maxCID_SetValue(int64_t value);
        int maxCID_GetDefault() const;
        std::string maxCID_ToString(uint32_t indent) const;
        std::string maxCID_ToStringNoNewLines() const;
        int maxCID_Clear();
        bool maxCID_IsPresent() const;
    private:
        bool maxCID_present;
        int64_t maxCID_internal_value;

        // profiles
    public:
        class profiles
        {
        public:
            profiles() : profile0x0001_present{false}, profile0x0002_present{false}, profile0x0003_present{false}, profile0x0004_present{false}, profile0x0006_present{false}, profile0x0101_present{false}, profile0x0102_present{false}, profile0x0103_present{false}, profile0x0104_present{false} {};
        public:
            int Pack(std::vector<uint8_t> &bits);
            int Unpack(std::vector<uint8_t> bits);
            int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
            std::string ToString(uint32_t indent) const;
            std::string ToStringNoNewLines() const;

            // profile0x0001
        public:
            int profile0x0001_Pack(std::vector<uint8_t> &bits);
            int profile0x0001_Unpack(std::vector<uint8_t> bits);
            int profile0x0001_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
            bool profile0x0001_Value() const;
            int profile0x0001_SetValue(bool value);
            std::string profile0x0001_ToString(uint32_t indent) const;
            std::string profile0x0001_ToStringNoNewLines() const;
            int profile0x0001_Clear();
            bool profile0x0001_IsPresent() const;
        private:
            bool profile0x0001_present;
            bool profile0x0001_internal_value;

            // profile0x0002
        public:
            int profile0x0002_Pack(std::vector<uint8_t> &bits);
            int profile0x0002_Unpack(std::vector<uint8_t> bits);
            int profile0x0002_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
            bool profile0x0002_Value() const;
            int profile0x0002_SetValue(bool value);
            std::string profile0x0002_ToString(uint32_t indent) const;
            std::string profile0x0002_ToStringNoNewLines() const;
            int profile0x0002_Clear();
            bool profile0x0002_IsPresent() const;
        private:
            bool profile0x0002_present;
            bool profile0x0002_internal_value;

            // profile0x0003
        public:
            int profile0x0003_Pack(std::vector<uint8_t> &bits);
            int profile0x0003_Unpack(std::vector<uint8_t> bits);
            int profile0x0003_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
            bool profile0x0003_Value() const;
            int profile0x0003_SetValue(bool value);
            std::string profile0x0003_ToString(uint32_t indent) const;
            std::string profile0x0003_ToStringNoNewLines() const;
            int profile0x0003_Clear();
            bool profile0x0003_IsPresent() const;
        private:
            bool profile0x0003_present;
            bool profile0x0003_internal_value;

            // profile0x0004
        public:
            int profile0x0004_Pack(std::vector<uint8_t> &bits);
            int profile0x0004_Unpack(std::vector<uint8_t> bits);
            int profile0x0004_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
            bool profile0x0004_Value() const;
            int profile0x0004_SetValue(bool value);
            std::string profile0x0004_ToString(uint32_t indent) const;
            std::string profile0x0004_ToStringNoNewLines() const;
            int profile0x0004_Clear();
            bool profile0x0004_IsPresent() const;
        private:
            bool profile0x0004_present;
            bool profile0x0004_internal_value;

            // profile0x0006
        public:
            int profile0x0006_Pack(std::vector<uint8_t> &bits);
            int profile0x0006_Unpack(std::vector<uint8_t> bits);
            int profile0x0006_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
            bool profile0x0006_Value() const;
            int profile0x0006_SetValue(bool value);
            std::string profile0x0006_ToString(uint32_t indent) const;
            std::string profile0x0006_ToStringNoNewLines() const;
            int profile0x0006_Clear();
            bool profile0x0006_IsPresent() const;
        private:
            bool profile0x0006_present;
            bool profile0x0006_internal_value;

            // profile0x0101
        public:
            int profile0x0101_Pack(std::vector<uint8_t> &bits);
            int profile0x0101_Unpack(std::vector<uint8_t> bits);
            int profile0x0101_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
            bool profile0x0101_Value() const;
            int profile0x0101_SetValue(bool value);
            std::string profile0x0101_ToString(uint32_t indent) const;
            std::string profile0x0101_ToStringNoNewLines() const;
            int profile0x0101_Clear();
            bool profile0x0101_IsPresent() const;
        private:
            bool profile0x0101_present;
            bool profile0x0101_internal_value;

            // profile0x0102
        public:
            int profile0x0102_Pack(std::vector<uint8_t> &bits);
            int profile0x0102_Unpack(std::vector<uint8_t> bits);
            int profile0x0102_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
            bool profile0x0102_Value() const;
            int profile0x0102_SetValue(bool value);
            std::string profile0x0102_ToString(uint32_t indent) const;
            std::string profile0x0102_ToStringNoNewLines() const;
            int profile0x0102_Clear();
            bool profile0x0102_IsPresent() const;
        private:
            bool profile0x0102_present;
            bool profile0x0102_internal_value;

            // profile0x0103
        public:
            int profile0x0103_Pack(std::vector<uint8_t> &bits);
            int profile0x0103_Unpack(std::vector<uint8_t> bits);
            int profile0x0103_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
            bool profile0x0103_Value() const;
            int profile0x0103_SetValue(bool value);
            std::string profile0x0103_ToString(uint32_t indent) const;
            std::string profile0x0103_ToStringNoNewLines() const;
            int profile0x0103_Clear();
            bool profile0x0103_IsPresent() const;
        private:
            bool profile0x0103_present;
            bool profile0x0103_internal_value;

            // profile0x0104
        public:
            int profile0x0104_Pack(std::vector<uint8_t> &bits);
            int profile0x0104_Unpack(std::vector<uint8_t> bits);
            int profile0x0104_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
            bool profile0x0104_Value() const;
            int profile0x0104_SetValue(bool value);
            std::string profile0x0104_ToString(uint32_t indent) const;
            std::string profile0x0104_ToStringNoNewLines() const;
            int profile0x0104_Clear();
            bool profile0x0104_IsPresent() const;
        private:
            bool profile0x0104_present;
            bool profile0x0104_internal_value;

        };

        profiles profiles_value;

    };

    headerCompression_rohc headerCompression_rohc_value;


};

#endif
