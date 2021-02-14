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

#ifndef __PUCCH_ConfigCommon_H__
#define __PUCCH_ConfigCommon_H__

#include <array>
#include <cstdint>
#include <vector>

class PUCCH_ConfigCommon
{
public:
    PUCCH_ConfigCommon() : deltaPUCCH_Shift_present{false}, nRB_CQI_present{false}, nCS_AN_present{false}, n1PUCCH_AN_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // deltaPUCCH-Shift
public:
    enum deltaPUCCH_Shift_Enum {
        k_deltaPUCCH_Shift_ds1 = 0,
        k_deltaPUCCH_Shift_ds2,
        k_deltaPUCCH_Shift_ds3,
    };
    int deltaPUCCH_Shift_Pack(std::vector<uint8_t> &bits);
    int deltaPUCCH_Shift_Unpack(std::vector<uint8_t> bits);
    int deltaPUCCH_Shift_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    deltaPUCCH_Shift_Enum deltaPUCCH_Shift_Value() const;
    int deltaPUCCH_Shift_SetValue(deltaPUCCH_Shift_Enum value);
    int deltaPUCCH_Shift_SetValue(std::string value);
    std::string deltaPUCCH_Shift_ValueToString(deltaPUCCH_Shift_Enum value) const;
    uint64_t deltaPUCCH_Shift_NumberOfValues() const;
    std::string deltaPUCCH_Shift_ToString(uint32_t indent) const;
    std::string deltaPUCCH_Shift_ToStringNoNewLines() const;
    int deltaPUCCH_Shift_Clear();
    bool deltaPUCCH_Shift_IsPresent() const;
private:
    bool deltaPUCCH_Shift_present;
    deltaPUCCH_Shift_Enum deltaPUCCH_Shift_internal_value;

    // nRB-CQI
public:
    int nRB_CQI_Pack(std::vector<uint8_t> &bits);
    int nRB_CQI_Unpack(std::vector<uint8_t> bits);
    int nRB_CQI_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t nRB_CQI_Value() const;
    int nRB_CQI_SetValue(int64_t value);
    std::string nRB_CQI_ToString(uint32_t indent) const;
    std::string nRB_CQI_ToStringNoNewLines() const;
    int nRB_CQI_Clear();
    bool nRB_CQI_IsPresent() const;
private:
    bool nRB_CQI_present;
    int64_t nRB_CQI_internal_value;

    // nCS-AN
public:
    int nCS_AN_Pack(std::vector<uint8_t> &bits);
    int nCS_AN_Unpack(std::vector<uint8_t> bits);
    int nCS_AN_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t nCS_AN_Value() const;
    int nCS_AN_SetValue(int64_t value);
    std::string nCS_AN_ToString(uint32_t indent) const;
    std::string nCS_AN_ToStringNoNewLines() const;
    int nCS_AN_Clear();
    bool nCS_AN_IsPresent() const;
private:
    bool nCS_AN_present;
    int64_t nCS_AN_internal_value;

    // n1PUCCH-AN
public:
    int n1PUCCH_AN_Pack(std::vector<uint8_t> &bits);
    int n1PUCCH_AN_Unpack(std::vector<uint8_t> bits);
    int n1PUCCH_AN_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t n1PUCCH_AN_Value() const;
    int n1PUCCH_AN_SetValue(int64_t value);
    std::string n1PUCCH_AN_ToString(uint32_t indent) const;
    std::string n1PUCCH_AN_ToStringNoNewLines() const;
    int n1PUCCH_AN_Clear();
    bool n1PUCCH_AN_IsPresent() const;
private:
    bool n1PUCCH_AN_present;
    int64_t n1PUCCH_AN_internal_value;

};

#endif
