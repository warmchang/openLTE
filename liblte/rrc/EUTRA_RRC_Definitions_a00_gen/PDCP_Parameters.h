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

#ifndef __PDCP_Parameters_H__
#define __PDCP_Parameters_H__

#include <array>
#include <cstdint>
#include <vector>

class PDCP_Parameters
{
public:
    PDCP_Parameters() : maxNumberROHC_ContextSessions_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // supportedROHC-Profiles
public:
    class supportedROHC_Profiles
    {
    public:
        supportedROHC_Profiles() : profile0x0001_present{false}, profile0x0002_present{false}, profile0x0003_present{false}, profile0x0004_present{false}, profile0x0006_present{false}, profile0x0101_present{false}, profile0x0102_present{false}, profile0x0103_present{false}, profile0x0104_present{false} {};
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

    supportedROHC_Profiles supportedROHC_Profiles_value;

    // maxNumberROHC-ContextSessions
public:
    enum maxNumberROHC_ContextSessions_Enum {
        k_maxNumberROHC_ContextSessions_cs2 = 0,
        k_maxNumberROHC_ContextSessions_cs4,
        k_maxNumberROHC_ContextSessions_cs8,
        k_maxNumberROHC_ContextSessions_cs12,
        k_maxNumberROHC_ContextSessions_cs16,
        k_maxNumberROHC_ContextSessions_cs24,
        k_maxNumberROHC_ContextSessions_cs32,
        k_maxNumberROHC_ContextSessions_cs48,
        k_maxNumberROHC_ContextSessions_cs64,
        k_maxNumberROHC_ContextSessions_cs128,
        k_maxNumberROHC_ContextSessions_cs256,
        k_maxNumberROHC_ContextSessions_cs512,
        k_maxNumberROHC_ContextSessions_cs1024,
        k_maxNumberROHC_ContextSessions_cs16384,
        k_maxNumberROHC_ContextSessions_spare2,
        k_maxNumberROHC_ContextSessions_spare1,
    };
    int maxNumberROHC_ContextSessions_Pack(std::vector<uint8_t> &bits);
    int maxNumberROHC_ContextSessions_Unpack(std::vector<uint8_t> bits);
    int maxNumberROHC_ContextSessions_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    maxNumberROHC_ContextSessions_Enum maxNumberROHC_ContextSessions_Value() const;
    int maxNumberROHC_ContextSessions_SetValue(maxNumberROHC_ContextSessions_Enum value);
    int maxNumberROHC_ContextSessions_SetValue(std::string value);
    std::string maxNumberROHC_ContextSessions_ValueToString(maxNumberROHC_ContextSessions_Enum value) const;
    uint64_t maxNumberROHC_ContextSessions_NumberOfValues() const;
    maxNumberROHC_ContextSessions_Enum maxNumberROHC_ContextSessions_GetDefault() const;
    std::string maxNumberROHC_ContextSessions_ToString(uint32_t indent) const;
    std::string maxNumberROHC_ContextSessions_ToStringNoNewLines() const;
    int maxNumberROHC_ContextSessions_Clear();
    bool maxNumberROHC_ContextSessions_IsPresent() const;
private:
    bool maxNumberROHC_ContextSessions_present;
    maxNumberROHC_ContextSessions_Enum maxNumberROHC_ContextSessions_internal_value;

};

#endif
