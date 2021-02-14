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

#ifndef __PCCH_Config_H__
#define __PCCH_Config_H__

#include <array>
#include <cstdint>
#include <vector>

class PCCH_Config
{
public:
    PCCH_Config() : defaultPagingCycle_present{false}, nB_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // defaultPagingCycle
public:
    enum defaultPagingCycle_Enum {
        k_defaultPagingCycle_rf32 = 0,
        k_defaultPagingCycle_rf64,
        k_defaultPagingCycle_rf128,
        k_defaultPagingCycle_rf256,
    };
    int defaultPagingCycle_Pack(std::vector<uint8_t> &bits);
    int defaultPagingCycle_Unpack(std::vector<uint8_t> bits);
    int defaultPagingCycle_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    defaultPagingCycle_Enum defaultPagingCycle_Value() const;
    int defaultPagingCycle_SetValue(defaultPagingCycle_Enum value);
    int defaultPagingCycle_SetValue(std::string value);
    std::string defaultPagingCycle_ValueToString(defaultPagingCycle_Enum value) const;
    uint64_t defaultPagingCycle_NumberOfValues() const;
    std::string defaultPagingCycle_ToString(uint32_t indent) const;
    std::string defaultPagingCycle_ToStringNoNewLines() const;
    int defaultPagingCycle_Clear();
    bool defaultPagingCycle_IsPresent() const;
private:
    bool defaultPagingCycle_present;
    defaultPagingCycle_Enum defaultPagingCycle_internal_value;

    // nB
public:
    enum nB_Enum {
        k_nB_fourT = 0,
        k_nB_twoT,
        k_nB_oneT,
        k_nB_halfT,
        k_nB_quarterT,
        k_nB_oneEighthT,
        k_nB_oneSixteenthT,
        k_nB_oneThirtySecondT,
    };
    int nB_Pack(std::vector<uint8_t> &bits);
    int nB_Unpack(std::vector<uint8_t> bits);
    int nB_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    nB_Enum nB_Value() const;
    int nB_SetValue(nB_Enum value);
    int nB_SetValue(std::string value);
    std::string nB_ValueToString(nB_Enum value) const;
    uint64_t nB_NumberOfValues() const;
    std::string nB_ToString(uint32_t indent) const;
    std::string nB_ToStringNoNewLines() const;
    int nB_Clear();
    bool nB_IsPresent() const;
private:
    bool nB_present;
    nB_Enum nB_internal_value;

};

#endif
