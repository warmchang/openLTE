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

#ifndef __RLF_TimersAndConstants_r9_H__
#define __RLF_TimersAndConstants_r9_H__

#include <array>
#include <cstdint>
#include <vector>

class RLF_TimersAndConstants_r9
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
        setup() : t301_r9_present{false}, t310_r9_present{false}, n310_r9_present{false}, t311_r9_present{false}, n311_r9_present{false} {};
    public:
        int Pack(std::vector<uint8_t> &bits);
        int Unpack(std::vector<uint8_t> bits);
        int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        std::string ToString(uint32_t indent) const;
        std::string ToStringNoNewLines() const;

        // t301-r9
    public:
        enum t301_r9_Enum {
            k_t301_r9_ms100 = 0,
            k_t301_r9_ms200,
            k_t301_r9_ms300,
            k_t301_r9_ms400,
            k_t301_r9_ms600,
            k_t301_r9_ms1000,
            k_t301_r9_ms1500,
            k_t301_r9_ms2000,
        };
        int t301_r9_Pack(std::vector<uint8_t> &bits);
        int t301_r9_Unpack(std::vector<uint8_t> bits);
        int t301_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        t301_r9_Enum t301_r9_Value() const;
        int t301_r9_SetValue(t301_r9_Enum value);
        int t301_r9_SetValue(std::string value);
        std::string t301_r9_ValueToString(t301_r9_Enum value) const;
        uint64_t t301_r9_NumberOfValues() const;
        std::string t301_r9_ToString(uint32_t indent) const;
        std::string t301_r9_ToStringNoNewLines() const;
        int t301_r9_Clear();
        bool t301_r9_IsPresent() const;
    private:
        bool t301_r9_present;
        t301_r9_Enum t301_r9_internal_value;

        // t310-r9
    public:
        enum t310_r9_Enum {
            k_t310_r9_ms0 = 0,
            k_t310_r9_ms50,
            k_t310_r9_ms100,
            k_t310_r9_ms200,
            k_t310_r9_ms500,
            k_t310_r9_ms1000,
            k_t310_r9_ms2000,
        };
        int t310_r9_Pack(std::vector<uint8_t> &bits);
        int t310_r9_Unpack(std::vector<uint8_t> bits);
        int t310_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        t310_r9_Enum t310_r9_Value() const;
        int t310_r9_SetValue(t310_r9_Enum value);
        int t310_r9_SetValue(std::string value);
        std::string t310_r9_ValueToString(t310_r9_Enum value) const;
        uint64_t t310_r9_NumberOfValues() const;
        std::string t310_r9_ToString(uint32_t indent) const;
        std::string t310_r9_ToStringNoNewLines() const;
        int t310_r9_Clear();
        bool t310_r9_IsPresent() const;
    private:
        bool t310_r9_present;
        t310_r9_Enum t310_r9_internal_value;

        // n310-r9
    public:
        enum n310_r9_Enum {
            k_n310_r9_n1 = 0,
            k_n310_r9_n2,
            k_n310_r9_n3,
            k_n310_r9_n4,
            k_n310_r9_n6,
            k_n310_r9_n8,
            k_n310_r9_n10,
            k_n310_r9_n20,
        };
        int n310_r9_Pack(std::vector<uint8_t> &bits);
        int n310_r9_Unpack(std::vector<uint8_t> bits);
        int n310_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        n310_r9_Enum n310_r9_Value() const;
        int n310_r9_SetValue(n310_r9_Enum value);
        int n310_r9_SetValue(std::string value);
        std::string n310_r9_ValueToString(n310_r9_Enum value) const;
        uint64_t n310_r9_NumberOfValues() const;
        std::string n310_r9_ToString(uint32_t indent) const;
        std::string n310_r9_ToStringNoNewLines() const;
        int n310_r9_Clear();
        bool n310_r9_IsPresent() const;
    private:
        bool n310_r9_present;
        n310_r9_Enum n310_r9_internal_value;

        // t311-r9
    public:
        enum t311_r9_Enum {
            k_t311_r9_ms1000 = 0,
            k_t311_r9_ms3000,
            k_t311_r9_ms5000,
            k_t311_r9_ms10000,
            k_t311_r9_ms15000,
            k_t311_r9_ms20000,
            k_t311_r9_ms30000,
        };
        int t311_r9_Pack(std::vector<uint8_t> &bits);
        int t311_r9_Unpack(std::vector<uint8_t> bits);
        int t311_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        t311_r9_Enum t311_r9_Value() const;
        int t311_r9_SetValue(t311_r9_Enum value);
        int t311_r9_SetValue(std::string value);
        std::string t311_r9_ValueToString(t311_r9_Enum value) const;
        uint64_t t311_r9_NumberOfValues() const;
        std::string t311_r9_ToString(uint32_t indent) const;
        std::string t311_r9_ToStringNoNewLines() const;
        int t311_r9_Clear();
        bool t311_r9_IsPresent() const;
    private:
        bool t311_r9_present;
        t311_r9_Enum t311_r9_internal_value;

        // n311-r9
    public:
        enum n311_r9_Enum {
            k_n311_r9_n1 = 0,
            k_n311_r9_n2,
            k_n311_r9_n3,
            k_n311_r9_n4,
            k_n311_r9_n5,
            k_n311_r9_n6,
            k_n311_r9_n8,
            k_n311_r9_n10,
        };
        int n311_r9_Pack(std::vector<uint8_t> &bits);
        int n311_r9_Unpack(std::vector<uint8_t> bits);
        int n311_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        n311_r9_Enum n311_r9_Value() const;
        int n311_r9_SetValue(n311_r9_Enum value);
        int n311_r9_SetValue(std::string value);
        std::string n311_r9_ValueToString(n311_r9_Enum value) const;
        uint64_t n311_r9_NumberOfValues() const;
        std::string n311_r9_ToString(uint32_t indent) const;
        std::string n311_r9_ToStringNoNewLines() const;
        int n311_r9_Clear();
        bool n311_r9_IsPresent() const;
    private:
        bool n311_r9_present;
        n311_r9_Enum n311_r9_internal_value;

    };

    setup setup_value;

};

#endif
