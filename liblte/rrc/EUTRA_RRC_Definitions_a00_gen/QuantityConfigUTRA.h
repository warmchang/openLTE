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

#ifndef __QuantityConfigUTRA_H__
#define __QuantityConfigUTRA_H__

#include "FilterCoefficient.h"

#include <array>
#include <cstdint>
#include <vector>

class QuantityConfigUTRA
{
public:
    QuantityConfigUTRA() : measQuantityUTRA_FDD_present{false}, measQuantityUTRA_TDD_present{false}, filterCoefficient_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // measQuantityUTRA-FDD
public:
    enum measQuantityUTRA_FDD_Enum {
        k_measQuantityUTRA_FDD_cpich_RSCP = 0,
        k_measQuantityUTRA_FDD_cpich_EcN0,
    };
    int measQuantityUTRA_FDD_Pack(std::vector<uint8_t> &bits);
    int measQuantityUTRA_FDD_Unpack(std::vector<uint8_t> bits);
    int measQuantityUTRA_FDD_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    measQuantityUTRA_FDD_Enum measQuantityUTRA_FDD_Value() const;
    int measQuantityUTRA_FDD_SetValue(measQuantityUTRA_FDD_Enum value);
    int measQuantityUTRA_FDD_SetValue(std::string value);
    std::string measQuantityUTRA_FDD_ValueToString(measQuantityUTRA_FDD_Enum value) const;
    uint64_t measQuantityUTRA_FDD_NumberOfValues() const;
    std::string measQuantityUTRA_FDD_ToString(uint32_t indent) const;
    std::string measQuantityUTRA_FDD_ToStringNoNewLines() const;
    int measQuantityUTRA_FDD_Clear();
    bool measQuantityUTRA_FDD_IsPresent() const;
private:
    bool measQuantityUTRA_FDD_present;
    measQuantityUTRA_FDD_Enum measQuantityUTRA_FDD_internal_value;

    // measQuantityUTRA-TDD
public:
    enum measQuantityUTRA_TDD_Enum {
        k_measQuantityUTRA_TDD_pccpch_RSCP = 0,
    };
    int measQuantityUTRA_TDD_Pack(std::vector<uint8_t> &bits);
    int measQuantityUTRA_TDD_Unpack(std::vector<uint8_t> bits);
    int measQuantityUTRA_TDD_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    measQuantityUTRA_TDD_Enum measQuantityUTRA_TDD_Value() const;
    int measQuantityUTRA_TDD_SetValue(measQuantityUTRA_TDD_Enum value);
    int measQuantityUTRA_TDD_SetValue(std::string value);
    std::string measQuantityUTRA_TDD_ValueToString(measQuantityUTRA_TDD_Enum value) const;
    uint64_t measQuantityUTRA_TDD_NumberOfValues() const;
    std::string measQuantityUTRA_TDD_ToString(uint32_t indent) const;
    std::string measQuantityUTRA_TDD_ToStringNoNewLines() const;
    int measQuantityUTRA_TDD_Clear();
    bool measQuantityUTRA_TDD_IsPresent() const;
private:
    bool measQuantityUTRA_TDD_present;
    measQuantityUTRA_TDD_Enum measQuantityUTRA_TDD_internal_value;

    // filterCoefficient
public:
    FilterCoefficient* filterCoefficient_Set();
    int filterCoefficient_Set(FilterCoefficient &value);
    const FilterCoefficient& filterCoefficient_Get() const;
    FilterCoefficient::Enum filterCoefficient_GetDefault() const;
    std::string filterCoefficient_ToString(uint32_t indent) const;
    std::string filterCoefficient_ToStringNoNewLines() const;
    int filterCoefficient_Clear();
    bool filterCoefficient_IsPresent() const;
private:
    bool filterCoefficient_present;
    FilterCoefficient filterCoefficient;

};

#endif
