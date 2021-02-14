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

#ifndef __UE_TimersAndConstants_H__
#define __UE_TimersAndConstants_H__

#include <array>
#include <cstdint>
#include <vector>

class UE_TimersAndConstants
{
public:
    UE_TimersAndConstants() : t300_present{false}, t301_present{false}, t310_present{false}, n310_present{false}, t311_present{false}, n311_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // t300
public:
    enum t300_Enum {
        k_t300_ms100 = 0,
        k_t300_ms200,
        k_t300_ms300,
        k_t300_ms400,
        k_t300_ms600,
        k_t300_ms1000,
        k_t300_ms1500,
        k_t300_ms2000,
    };
    int t300_Pack(std::vector<uint8_t> &bits);
    int t300_Unpack(std::vector<uint8_t> bits);
    int t300_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    t300_Enum t300_Value() const;
    int t300_SetValue(t300_Enum value);
    int t300_SetValue(std::string value);
    std::string t300_ValueToString(t300_Enum value) const;
    uint64_t t300_NumberOfValues() const;
    std::string t300_ToString(uint32_t indent) const;
    std::string t300_ToStringNoNewLines() const;
    int t300_Clear();
    bool t300_IsPresent() const;
private:
    bool t300_present;
    t300_Enum t300_internal_value;

    // t301
public:
    enum t301_Enum {
        k_t301_ms100 = 0,
        k_t301_ms200,
        k_t301_ms300,
        k_t301_ms400,
        k_t301_ms600,
        k_t301_ms1000,
        k_t301_ms1500,
        k_t301_ms2000,
    };
    int t301_Pack(std::vector<uint8_t> &bits);
    int t301_Unpack(std::vector<uint8_t> bits);
    int t301_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    t301_Enum t301_Value() const;
    int t301_SetValue(t301_Enum value);
    int t301_SetValue(std::string value);
    std::string t301_ValueToString(t301_Enum value) const;
    uint64_t t301_NumberOfValues() const;
    std::string t301_ToString(uint32_t indent) const;
    std::string t301_ToStringNoNewLines() const;
    int t301_Clear();
    bool t301_IsPresent() const;
private:
    bool t301_present;
    t301_Enum t301_internal_value;

    // t310
public:
    enum t310_Enum {
        k_t310_ms0 = 0,
        k_t310_ms50,
        k_t310_ms100,
        k_t310_ms200,
        k_t310_ms500,
        k_t310_ms1000,
        k_t310_ms2000,
    };
    int t310_Pack(std::vector<uint8_t> &bits);
    int t310_Unpack(std::vector<uint8_t> bits);
    int t310_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    t310_Enum t310_Value() const;
    int t310_SetValue(t310_Enum value);
    int t310_SetValue(std::string value);
    std::string t310_ValueToString(t310_Enum value) const;
    uint64_t t310_NumberOfValues() const;
    std::string t310_ToString(uint32_t indent) const;
    std::string t310_ToStringNoNewLines() const;
    int t310_Clear();
    bool t310_IsPresent() const;
private:
    bool t310_present;
    t310_Enum t310_internal_value;

    // n310
public:
    enum n310_Enum {
        k_n310_n1 = 0,
        k_n310_n2,
        k_n310_n3,
        k_n310_n4,
        k_n310_n6,
        k_n310_n8,
        k_n310_n10,
        k_n310_n20,
    };
    int n310_Pack(std::vector<uint8_t> &bits);
    int n310_Unpack(std::vector<uint8_t> bits);
    int n310_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    n310_Enum n310_Value() const;
    int n310_SetValue(n310_Enum value);
    int n310_SetValue(std::string value);
    std::string n310_ValueToString(n310_Enum value) const;
    uint64_t n310_NumberOfValues() const;
    std::string n310_ToString(uint32_t indent) const;
    std::string n310_ToStringNoNewLines() const;
    int n310_Clear();
    bool n310_IsPresent() const;
private:
    bool n310_present;
    n310_Enum n310_internal_value;

    // t311
public:
    enum t311_Enum {
        k_t311_ms1000 = 0,
        k_t311_ms3000,
        k_t311_ms5000,
        k_t311_ms10000,
        k_t311_ms15000,
        k_t311_ms20000,
        k_t311_ms30000,
    };
    int t311_Pack(std::vector<uint8_t> &bits);
    int t311_Unpack(std::vector<uint8_t> bits);
    int t311_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    t311_Enum t311_Value() const;
    int t311_SetValue(t311_Enum value);
    int t311_SetValue(std::string value);
    std::string t311_ValueToString(t311_Enum value) const;
    uint64_t t311_NumberOfValues() const;
    std::string t311_ToString(uint32_t indent) const;
    std::string t311_ToStringNoNewLines() const;
    int t311_Clear();
    bool t311_IsPresent() const;
private:
    bool t311_present;
    t311_Enum t311_internal_value;

    // n311
public:
    enum n311_Enum {
        k_n311_n1 = 0,
        k_n311_n2,
        k_n311_n3,
        k_n311_n4,
        k_n311_n5,
        k_n311_n6,
        k_n311_n8,
        k_n311_n10,
    };
    int n311_Pack(std::vector<uint8_t> &bits);
    int n311_Unpack(std::vector<uint8_t> bits);
    int n311_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    n311_Enum n311_Value() const;
    int n311_SetValue(n311_Enum value);
    int n311_SetValue(std::string value);
    std::string n311_ValueToString(n311_Enum value) const;
    uint64_t n311_NumberOfValues() const;
    std::string n311_ToString(uint32_t indent) const;
    std::string n311_ToStringNoNewLines() const;
    int n311_Clear();
    bool n311_IsPresent() const;
private:
    bool n311_present;
    n311_Enum n311_internal_value;

};

#endif
