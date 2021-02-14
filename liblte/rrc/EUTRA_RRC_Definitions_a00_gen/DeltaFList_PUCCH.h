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

#ifndef __DeltaFList_PUCCH_H__
#define __DeltaFList_PUCCH_H__

#include <array>
#include <cstdint>
#include <vector>

class DeltaFList_PUCCH
{
public:
    DeltaFList_PUCCH() : deltaF_PUCCH_Format1_present{false}, deltaF_PUCCH_Format1b_present{false}, deltaF_PUCCH_Format2_present{false}, deltaF_PUCCH_Format2a_present{false}, deltaF_PUCCH_Format2b_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // deltaF-PUCCH-Format1
public:
    enum deltaF_PUCCH_Format1_Enum {
        k_deltaF_PUCCH_Format1_deltaF_2 = 0,
        k_deltaF_PUCCH_Format1_deltaF0,
        k_deltaF_PUCCH_Format1_deltaF2,
    };
    int deltaF_PUCCH_Format1_Pack(std::vector<uint8_t> &bits);
    int deltaF_PUCCH_Format1_Unpack(std::vector<uint8_t> bits);
    int deltaF_PUCCH_Format1_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    deltaF_PUCCH_Format1_Enum deltaF_PUCCH_Format1_Value() const;
    int deltaF_PUCCH_Format1_SetValue(deltaF_PUCCH_Format1_Enum value);
    int deltaF_PUCCH_Format1_SetValue(std::string value);
    std::string deltaF_PUCCH_Format1_ValueToString(deltaF_PUCCH_Format1_Enum value) const;
    uint64_t deltaF_PUCCH_Format1_NumberOfValues() const;
    std::string deltaF_PUCCH_Format1_ToString(uint32_t indent) const;
    std::string deltaF_PUCCH_Format1_ToStringNoNewLines() const;
    int deltaF_PUCCH_Format1_Clear();
    bool deltaF_PUCCH_Format1_IsPresent() const;
private:
    bool deltaF_PUCCH_Format1_present;
    deltaF_PUCCH_Format1_Enum deltaF_PUCCH_Format1_internal_value;

    // deltaF-PUCCH-Format1b
public:
    enum deltaF_PUCCH_Format1b_Enum {
        k_deltaF_PUCCH_Format1b_deltaF1 = 0,
        k_deltaF_PUCCH_Format1b_deltaF3,
        k_deltaF_PUCCH_Format1b_deltaF5,
    };
    int deltaF_PUCCH_Format1b_Pack(std::vector<uint8_t> &bits);
    int deltaF_PUCCH_Format1b_Unpack(std::vector<uint8_t> bits);
    int deltaF_PUCCH_Format1b_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    deltaF_PUCCH_Format1b_Enum deltaF_PUCCH_Format1b_Value() const;
    int deltaF_PUCCH_Format1b_SetValue(deltaF_PUCCH_Format1b_Enum value);
    int deltaF_PUCCH_Format1b_SetValue(std::string value);
    std::string deltaF_PUCCH_Format1b_ValueToString(deltaF_PUCCH_Format1b_Enum value) const;
    uint64_t deltaF_PUCCH_Format1b_NumberOfValues() const;
    std::string deltaF_PUCCH_Format1b_ToString(uint32_t indent) const;
    std::string deltaF_PUCCH_Format1b_ToStringNoNewLines() const;
    int deltaF_PUCCH_Format1b_Clear();
    bool deltaF_PUCCH_Format1b_IsPresent() const;
private:
    bool deltaF_PUCCH_Format1b_present;
    deltaF_PUCCH_Format1b_Enum deltaF_PUCCH_Format1b_internal_value;

    // deltaF-PUCCH-Format2
public:
    enum deltaF_PUCCH_Format2_Enum {
        k_deltaF_PUCCH_Format2_deltaF_2 = 0,
        k_deltaF_PUCCH_Format2_deltaF0,
        k_deltaF_PUCCH_Format2_deltaF1,
        k_deltaF_PUCCH_Format2_deltaF2,
    };
    int deltaF_PUCCH_Format2_Pack(std::vector<uint8_t> &bits);
    int deltaF_PUCCH_Format2_Unpack(std::vector<uint8_t> bits);
    int deltaF_PUCCH_Format2_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    deltaF_PUCCH_Format2_Enum deltaF_PUCCH_Format2_Value() const;
    int deltaF_PUCCH_Format2_SetValue(deltaF_PUCCH_Format2_Enum value);
    int deltaF_PUCCH_Format2_SetValue(std::string value);
    std::string deltaF_PUCCH_Format2_ValueToString(deltaF_PUCCH_Format2_Enum value) const;
    uint64_t deltaF_PUCCH_Format2_NumberOfValues() const;
    std::string deltaF_PUCCH_Format2_ToString(uint32_t indent) const;
    std::string deltaF_PUCCH_Format2_ToStringNoNewLines() const;
    int deltaF_PUCCH_Format2_Clear();
    bool deltaF_PUCCH_Format2_IsPresent() const;
private:
    bool deltaF_PUCCH_Format2_present;
    deltaF_PUCCH_Format2_Enum deltaF_PUCCH_Format2_internal_value;

    // deltaF-PUCCH-Format2a
public:
    enum deltaF_PUCCH_Format2a_Enum {
        k_deltaF_PUCCH_Format2a_deltaF_2 = 0,
        k_deltaF_PUCCH_Format2a_deltaF0,
        k_deltaF_PUCCH_Format2a_deltaF2,
    };
    int deltaF_PUCCH_Format2a_Pack(std::vector<uint8_t> &bits);
    int deltaF_PUCCH_Format2a_Unpack(std::vector<uint8_t> bits);
    int deltaF_PUCCH_Format2a_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    deltaF_PUCCH_Format2a_Enum deltaF_PUCCH_Format2a_Value() const;
    int deltaF_PUCCH_Format2a_SetValue(deltaF_PUCCH_Format2a_Enum value);
    int deltaF_PUCCH_Format2a_SetValue(std::string value);
    std::string deltaF_PUCCH_Format2a_ValueToString(deltaF_PUCCH_Format2a_Enum value) const;
    uint64_t deltaF_PUCCH_Format2a_NumberOfValues() const;
    std::string deltaF_PUCCH_Format2a_ToString(uint32_t indent) const;
    std::string deltaF_PUCCH_Format2a_ToStringNoNewLines() const;
    int deltaF_PUCCH_Format2a_Clear();
    bool deltaF_PUCCH_Format2a_IsPresent() const;
private:
    bool deltaF_PUCCH_Format2a_present;
    deltaF_PUCCH_Format2a_Enum deltaF_PUCCH_Format2a_internal_value;

    // deltaF-PUCCH-Format2b
public:
    enum deltaF_PUCCH_Format2b_Enum {
        k_deltaF_PUCCH_Format2b_deltaF_2 = 0,
        k_deltaF_PUCCH_Format2b_deltaF0,
        k_deltaF_PUCCH_Format2b_deltaF2,
    };
    int deltaF_PUCCH_Format2b_Pack(std::vector<uint8_t> &bits);
    int deltaF_PUCCH_Format2b_Unpack(std::vector<uint8_t> bits);
    int deltaF_PUCCH_Format2b_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    deltaF_PUCCH_Format2b_Enum deltaF_PUCCH_Format2b_Value() const;
    int deltaF_PUCCH_Format2b_SetValue(deltaF_PUCCH_Format2b_Enum value);
    int deltaF_PUCCH_Format2b_SetValue(std::string value);
    std::string deltaF_PUCCH_Format2b_ValueToString(deltaF_PUCCH_Format2b_Enum value) const;
    uint64_t deltaF_PUCCH_Format2b_NumberOfValues() const;
    std::string deltaF_PUCCH_Format2b_ToString(uint32_t indent) const;
    std::string deltaF_PUCCH_Format2b_ToStringNoNewLines() const;
    int deltaF_PUCCH_Format2b_Clear();
    bool deltaF_PUCCH_Format2b_IsPresent() const;
private:
    bool deltaF_PUCCH_Format2b_present;
    deltaF_PUCCH_Format2b_Enum deltaF_PUCCH_Format2b_internal_value;

};

#endif
