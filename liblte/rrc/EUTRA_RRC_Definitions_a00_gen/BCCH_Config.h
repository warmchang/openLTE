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

#ifndef __BCCH_Config_H__
#define __BCCH_Config_H__

#include <array>
#include <cstdint>
#include <vector>

class BCCH_Config
{
public:
    BCCH_Config() : modificationPeriodCoeff_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // modificationPeriodCoeff
public:
    enum modificationPeriodCoeff_Enum {
        k_modificationPeriodCoeff_n2 = 0,
        k_modificationPeriodCoeff_n4,
        k_modificationPeriodCoeff_n8,
        k_modificationPeriodCoeff_n16,
    };
    int modificationPeriodCoeff_Pack(std::vector<uint8_t> &bits);
    int modificationPeriodCoeff_Unpack(std::vector<uint8_t> bits);
    int modificationPeriodCoeff_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    modificationPeriodCoeff_Enum modificationPeriodCoeff_Value() const;
    int modificationPeriodCoeff_SetValue(modificationPeriodCoeff_Enum value);
    int modificationPeriodCoeff_SetValue(std::string value);
    std::string modificationPeriodCoeff_ValueToString(modificationPeriodCoeff_Enum value) const;
    uint64_t modificationPeriodCoeff_NumberOfValues() const;
    std::string modificationPeriodCoeff_ToString(uint32_t indent) const;
    std::string modificationPeriodCoeff_ToStringNoNewLines() const;
    int modificationPeriodCoeff_Clear();
    bool modificationPeriodCoeff_IsPresent() const;
private:
    bool modificationPeriodCoeff_present;
    modificationPeriodCoeff_Enum modificationPeriodCoeff_internal_value;

};

#endif
