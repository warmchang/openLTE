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

#ifndef __CSFB_RegistrationParam1XRTT_v920_H__
#define __CSFB_RegistrationParam1XRTT_v920_H__

#include <array>
#include <cstdint>
#include <vector>

class CSFB_RegistrationParam1XRTT_v920
{
public:
    CSFB_RegistrationParam1XRTT_v920() : powerDownReg_r9_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // powerDownReg-r9
public:
    enum powerDownReg_r9_Enum {
        k_powerDownReg_r9_true = 0,
    };
    int powerDownReg_r9_Pack(std::vector<uint8_t> &bits);
    int powerDownReg_r9_Unpack(std::vector<uint8_t> bits);
    int powerDownReg_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    powerDownReg_r9_Enum powerDownReg_r9_Value() const;
    int powerDownReg_r9_SetValue(powerDownReg_r9_Enum value);
    int powerDownReg_r9_SetValue(std::string value);
    std::string powerDownReg_r9_ValueToString(powerDownReg_r9_Enum value) const;
    uint64_t powerDownReg_r9_NumberOfValues() const;
    std::string powerDownReg_r9_ToString(uint32_t indent) const;
    std::string powerDownReg_r9_ToStringNoNewLines() const;
    int powerDownReg_r9_Clear();
    bool powerDownReg_r9_IsPresent() const;
private:
    bool powerDownReg_r9_present;
    powerDownReg_r9_Enum powerDownReg_r9_internal_value;

};

#endif
