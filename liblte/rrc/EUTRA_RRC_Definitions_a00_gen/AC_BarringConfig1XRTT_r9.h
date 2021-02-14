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

#ifndef __AC_BarringConfig1XRTT_r9_H__
#define __AC_BarringConfig1XRTT_r9_H__

#include <array>
#include <cstdint>
#include <vector>

class AC_BarringConfig1XRTT_r9
{
public:
    AC_BarringConfig1XRTT_r9() : ac_Barring0to9_r9_present{false}, ac_Barring10_r9_present{false}, ac_Barring11_r9_present{false}, ac_Barring12_r9_present{false}, ac_Barring13_r9_present{false}, ac_Barring14_r9_present{false}, ac_Barring15_r9_present{false}, ac_BarringMsg_r9_present{false}, ac_BarringReg_r9_present{false}, ac_BarringEmg_r9_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // ac-Barring0to9-r9
public:
    int ac_Barring0to9_r9_Pack(std::vector<uint8_t> &bits);
    int ac_Barring0to9_r9_Unpack(std::vector<uint8_t> bits);
    int ac_Barring0to9_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t ac_Barring0to9_r9_Value() const;
    int ac_Barring0to9_r9_SetValue(int64_t value);
    std::string ac_Barring0to9_r9_ToString(uint32_t indent) const;
    std::string ac_Barring0to9_r9_ToStringNoNewLines() const;
    int ac_Barring0to9_r9_Clear();
    bool ac_Barring0to9_r9_IsPresent() const;
private:
    bool ac_Barring0to9_r9_present;
    int64_t ac_Barring0to9_r9_internal_value;

    // ac-Barring10-r9
public:
    int ac_Barring10_r9_Pack(std::vector<uint8_t> &bits);
    int ac_Barring10_r9_Unpack(std::vector<uint8_t> bits);
    int ac_Barring10_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t ac_Barring10_r9_Value() const;
    int ac_Barring10_r9_SetValue(int64_t value);
    std::string ac_Barring10_r9_ToString(uint32_t indent) const;
    std::string ac_Barring10_r9_ToStringNoNewLines() const;
    int ac_Barring10_r9_Clear();
    bool ac_Barring10_r9_IsPresent() const;
private:
    bool ac_Barring10_r9_present;
    int64_t ac_Barring10_r9_internal_value;

    // ac-Barring11-r9
public:
    int ac_Barring11_r9_Pack(std::vector<uint8_t> &bits);
    int ac_Barring11_r9_Unpack(std::vector<uint8_t> bits);
    int ac_Barring11_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t ac_Barring11_r9_Value() const;
    int ac_Barring11_r9_SetValue(int64_t value);
    std::string ac_Barring11_r9_ToString(uint32_t indent) const;
    std::string ac_Barring11_r9_ToStringNoNewLines() const;
    int ac_Barring11_r9_Clear();
    bool ac_Barring11_r9_IsPresent() const;
private:
    bool ac_Barring11_r9_present;
    int64_t ac_Barring11_r9_internal_value;

    // ac-Barring12-r9
public:
    int ac_Barring12_r9_Pack(std::vector<uint8_t> &bits);
    int ac_Barring12_r9_Unpack(std::vector<uint8_t> bits);
    int ac_Barring12_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t ac_Barring12_r9_Value() const;
    int ac_Barring12_r9_SetValue(int64_t value);
    std::string ac_Barring12_r9_ToString(uint32_t indent) const;
    std::string ac_Barring12_r9_ToStringNoNewLines() const;
    int ac_Barring12_r9_Clear();
    bool ac_Barring12_r9_IsPresent() const;
private:
    bool ac_Barring12_r9_present;
    int64_t ac_Barring12_r9_internal_value;

    // ac-Barring13-r9
public:
    int ac_Barring13_r9_Pack(std::vector<uint8_t> &bits);
    int ac_Barring13_r9_Unpack(std::vector<uint8_t> bits);
    int ac_Barring13_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t ac_Barring13_r9_Value() const;
    int ac_Barring13_r9_SetValue(int64_t value);
    std::string ac_Barring13_r9_ToString(uint32_t indent) const;
    std::string ac_Barring13_r9_ToStringNoNewLines() const;
    int ac_Barring13_r9_Clear();
    bool ac_Barring13_r9_IsPresent() const;
private:
    bool ac_Barring13_r9_present;
    int64_t ac_Barring13_r9_internal_value;

    // ac-Barring14-r9
public:
    int ac_Barring14_r9_Pack(std::vector<uint8_t> &bits);
    int ac_Barring14_r9_Unpack(std::vector<uint8_t> bits);
    int ac_Barring14_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t ac_Barring14_r9_Value() const;
    int ac_Barring14_r9_SetValue(int64_t value);
    std::string ac_Barring14_r9_ToString(uint32_t indent) const;
    std::string ac_Barring14_r9_ToStringNoNewLines() const;
    int ac_Barring14_r9_Clear();
    bool ac_Barring14_r9_IsPresent() const;
private:
    bool ac_Barring14_r9_present;
    int64_t ac_Barring14_r9_internal_value;

    // ac-Barring15-r9
public:
    int ac_Barring15_r9_Pack(std::vector<uint8_t> &bits);
    int ac_Barring15_r9_Unpack(std::vector<uint8_t> bits);
    int ac_Barring15_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t ac_Barring15_r9_Value() const;
    int ac_Barring15_r9_SetValue(int64_t value);
    std::string ac_Barring15_r9_ToString(uint32_t indent) const;
    std::string ac_Barring15_r9_ToStringNoNewLines() const;
    int ac_Barring15_r9_Clear();
    bool ac_Barring15_r9_IsPresent() const;
private:
    bool ac_Barring15_r9_present;
    int64_t ac_Barring15_r9_internal_value;

    // ac-BarringMsg-r9
public:
    int ac_BarringMsg_r9_Pack(std::vector<uint8_t> &bits);
    int ac_BarringMsg_r9_Unpack(std::vector<uint8_t> bits);
    int ac_BarringMsg_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t ac_BarringMsg_r9_Value() const;
    int ac_BarringMsg_r9_SetValue(int64_t value);
    std::string ac_BarringMsg_r9_ToString(uint32_t indent) const;
    std::string ac_BarringMsg_r9_ToStringNoNewLines() const;
    int ac_BarringMsg_r9_Clear();
    bool ac_BarringMsg_r9_IsPresent() const;
private:
    bool ac_BarringMsg_r9_present;
    int64_t ac_BarringMsg_r9_internal_value;

    // ac-BarringReg-r9
public:
    int ac_BarringReg_r9_Pack(std::vector<uint8_t> &bits);
    int ac_BarringReg_r9_Unpack(std::vector<uint8_t> bits);
    int ac_BarringReg_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t ac_BarringReg_r9_Value() const;
    int ac_BarringReg_r9_SetValue(int64_t value);
    std::string ac_BarringReg_r9_ToString(uint32_t indent) const;
    std::string ac_BarringReg_r9_ToStringNoNewLines() const;
    int ac_BarringReg_r9_Clear();
    bool ac_BarringReg_r9_IsPresent() const;
private:
    bool ac_BarringReg_r9_present;
    int64_t ac_BarringReg_r9_internal_value;

    // ac-BarringEmg-r9
public:
    int ac_BarringEmg_r9_Pack(std::vector<uint8_t> &bits);
    int ac_BarringEmg_r9_Unpack(std::vector<uint8_t> bits);
    int ac_BarringEmg_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t ac_BarringEmg_r9_Value() const;
    int ac_BarringEmg_r9_SetValue(int64_t value);
    std::string ac_BarringEmg_r9_ToString(uint32_t indent) const;
    std::string ac_BarringEmg_r9_ToStringNoNewLines() const;
    int ac_BarringEmg_r9_Clear();
    bool ac_BarringEmg_r9_IsPresent() const;
private:
    bool ac_BarringEmg_r9_present;
    int64_t ac_BarringEmg_r9_internal_value;

};

#endif
