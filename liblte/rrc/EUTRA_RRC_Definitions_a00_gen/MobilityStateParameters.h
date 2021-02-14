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

#ifndef __MobilityStateParameters_H__
#define __MobilityStateParameters_H__

#include <array>
#include <cstdint>
#include <vector>

class MobilityStateParameters
{
public:
    MobilityStateParameters() : t_Evaluation_present{false}, t_HystNormal_present{false}, n_CellChangeMedium_present{false}, n_CellChangeHigh_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // t-Evaluation
public:
    enum t_Evaluation_Enum {
        k_t_Evaluation_s30 = 0,
        k_t_Evaluation_s60,
        k_t_Evaluation_s120,
        k_t_Evaluation_s180,
        k_t_Evaluation_s240,
        k_t_Evaluation_spare3,
        k_t_Evaluation_spare2,
        k_t_Evaluation_spare1,
    };
    int t_Evaluation_Pack(std::vector<uint8_t> &bits);
    int t_Evaluation_Unpack(std::vector<uint8_t> bits);
    int t_Evaluation_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    t_Evaluation_Enum t_Evaluation_Value() const;
    int t_Evaluation_SetValue(t_Evaluation_Enum value);
    int t_Evaluation_SetValue(std::string value);
    std::string t_Evaluation_ValueToString(t_Evaluation_Enum value) const;
    uint64_t t_Evaluation_NumberOfValues() const;
    std::string t_Evaluation_ToString(uint32_t indent) const;
    std::string t_Evaluation_ToStringNoNewLines() const;
    int t_Evaluation_Clear();
    bool t_Evaluation_IsPresent() const;
private:
    bool t_Evaluation_present;
    t_Evaluation_Enum t_Evaluation_internal_value;

    // t-HystNormal
public:
    enum t_HystNormal_Enum {
        k_t_HystNormal_s30 = 0,
        k_t_HystNormal_s60,
        k_t_HystNormal_s120,
        k_t_HystNormal_s180,
        k_t_HystNormal_s240,
        k_t_HystNormal_spare3,
        k_t_HystNormal_spare2,
        k_t_HystNormal_spare1,
    };
    int t_HystNormal_Pack(std::vector<uint8_t> &bits);
    int t_HystNormal_Unpack(std::vector<uint8_t> bits);
    int t_HystNormal_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    t_HystNormal_Enum t_HystNormal_Value() const;
    int t_HystNormal_SetValue(t_HystNormal_Enum value);
    int t_HystNormal_SetValue(std::string value);
    std::string t_HystNormal_ValueToString(t_HystNormal_Enum value) const;
    uint64_t t_HystNormal_NumberOfValues() const;
    std::string t_HystNormal_ToString(uint32_t indent) const;
    std::string t_HystNormal_ToStringNoNewLines() const;
    int t_HystNormal_Clear();
    bool t_HystNormal_IsPresent() const;
private:
    bool t_HystNormal_present;
    t_HystNormal_Enum t_HystNormal_internal_value;

    // n-CellChangeMedium
public:
    int n_CellChangeMedium_Pack(std::vector<uint8_t> &bits);
    int n_CellChangeMedium_Unpack(std::vector<uint8_t> bits);
    int n_CellChangeMedium_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t n_CellChangeMedium_Value() const;
    int n_CellChangeMedium_SetValue(int64_t value);
    std::string n_CellChangeMedium_ToString(uint32_t indent) const;
    std::string n_CellChangeMedium_ToStringNoNewLines() const;
    int n_CellChangeMedium_Clear();
    bool n_CellChangeMedium_IsPresent() const;
private:
    bool n_CellChangeMedium_present;
    int64_t n_CellChangeMedium_internal_value;

    // n-CellChangeHigh
public:
    int n_CellChangeHigh_Pack(std::vector<uint8_t> &bits);
    int n_CellChangeHigh_Unpack(std::vector<uint8_t> bits);
    int n_CellChangeHigh_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t n_CellChangeHigh_Value() const;
    int n_CellChangeHigh_SetValue(int64_t value);
    std::string n_CellChangeHigh_ToString(uint32_t indent) const;
    std::string n_CellChangeHigh_ToStringNoNewLines() const;
    int n_CellChangeHigh_Clear();
    bool n_CellChangeHigh_IsPresent() const;
private:
    bool n_CellChangeHigh_present;
    int64_t n_CellChangeHigh_internal_value;

};

#endif
