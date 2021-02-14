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

#ifndef __AC_BarringConfig_H__
#define __AC_BarringConfig_H__

#include <array>
#include <cstdint>
#include <vector>

class AC_BarringConfig
{
public:
    AC_BarringConfig() : ac_BarringFactor_present{false}, ac_BarringTime_present{false}, ac_BarringForSpecialAC_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // ac-BarringFactor
public:
    enum ac_BarringFactor_Enum {
        k_ac_BarringFactor_p00 = 0,
        k_ac_BarringFactor_p05,
        k_ac_BarringFactor_p10,
        k_ac_BarringFactor_p15,
        k_ac_BarringFactor_p20,
        k_ac_BarringFactor_p25,
        k_ac_BarringFactor_p30,
        k_ac_BarringFactor_p40,
        k_ac_BarringFactor_p50,
        k_ac_BarringFactor_p60,
        k_ac_BarringFactor_p70,
        k_ac_BarringFactor_p75,
        k_ac_BarringFactor_p80,
        k_ac_BarringFactor_p85,
        k_ac_BarringFactor_p90,
        k_ac_BarringFactor_p95,
    };
    int ac_BarringFactor_Pack(std::vector<uint8_t> &bits);
    int ac_BarringFactor_Unpack(std::vector<uint8_t> bits);
    int ac_BarringFactor_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    ac_BarringFactor_Enum ac_BarringFactor_Value() const;
    int ac_BarringFactor_SetValue(ac_BarringFactor_Enum value);
    int ac_BarringFactor_SetValue(std::string value);
    std::string ac_BarringFactor_ValueToString(ac_BarringFactor_Enum value) const;
    uint64_t ac_BarringFactor_NumberOfValues() const;
    std::string ac_BarringFactor_ToString(uint32_t indent) const;
    std::string ac_BarringFactor_ToStringNoNewLines() const;
    int ac_BarringFactor_Clear();
    bool ac_BarringFactor_IsPresent() const;
private:
    bool ac_BarringFactor_present;
    ac_BarringFactor_Enum ac_BarringFactor_internal_value;

    // ac-BarringTime
public:
    enum ac_BarringTime_Enum {
        k_ac_BarringTime_s4 = 0,
        k_ac_BarringTime_s8,
        k_ac_BarringTime_s16,
        k_ac_BarringTime_s32,
        k_ac_BarringTime_s64,
        k_ac_BarringTime_s128,
        k_ac_BarringTime_s256,
        k_ac_BarringTime_s512,
    };
    int ac_BarringTime_Pack(std::vector<uint8_t> &bits);
    int ac_BarringTime_Unpack(std::vector<uint8_t> bits);
    int ac_BarringTime_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    ac_BarringTime_Enum ac_BarringTime_Value() const;
    int ac_BarringTime_SetValue(ac_BarringTime_Enum value);
    int ac_BarringTime_SetValue(std::string value);
    std::string ac_BarringTime_ValueToString(ac_BarringTime_Enum value) const;
    uint64_t ac_BarringTime_NumberOfValues() const;
    std::string ac_BarringTime_ToString(uint32_t indent) const;
    std::string ac_BarringTime_ToStringNoNewLines() const;
    int ac_BarringTime_Clear();
    bool ac_BarringTime_IsPresent() const;
private:
    bool ac_BarringTime_present;
    ac_BarringTime_Enum ac_BarringTime_internal_value;

    // ac-BarringForSpecialAC
public:
    int ac_BarringForSpecialAC_Pack(std::vector<uint8_t> &bits);
    int ac_BarringForSpecialAC_Unpack(std::vector<uint8_t> bits);
    int ac_BarringForSpecialAC_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    uint8_t ac_BarringForSpecialAC_Value() const;
    int ac_BarringForSpecialAC_SetValue(uint8_t value);
    std::string ac_BarringForSpecialAC_ToString(uint32_t indent) const;
    std::string ac_BarringForSpecialAC_ToStringNoNewLines() const;
    int ac_BarringForSpecialAC_Clear();
    bool ac_BarringForSpecialAC_IsPresent() const;
private:
    bool ac_BarringForSpecialAC_present;
    uint8_t ac_BarringForSpecialAC_internal_value;

};

#endif
