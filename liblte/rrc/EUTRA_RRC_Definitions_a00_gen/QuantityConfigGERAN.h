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

#ifndef __QuantityConfigGERAN_H__
#define __QuantityConfigGERAN_H__

#include "FilterCoefficient.h"

#include <array>
#include <cstdint>
#include <vector>

class QuantityConfigGERAN
{
public:
    QuantityConfigGERAN() : measQuantityGERAN_present{false}, filterCoefficient_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // measQuantityGERAN
public:
    enum measQuantityGERAN_Enum {
        k_measQuantityGERAN_rssi = 0,
    };
    int measQuantityGERAN_Pack(std::vector<uint8_t> &bits);
    int measQuantityGERAN_Unpack(std::vector<uint8_t> bits);
    int measQuantityGERAN_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    measQuantityGERAN_Enum measQuantityGERAN_Value() const;
    int measQuantityGERAN_SetValue(measQuantityGERAN_Enum value);
    int measQuantityGERAN_SetValue(std::string value);
    std::string measQuantityGERAN_ValueToString(measQuantityGERAN_Enum value) const;
    uint64_t measQuantityGERAN_NumberOfValues() const;
    std::string measQuantityGERAN_ToString(uint32_t indent) const;
    std::string measQuantityGERAN_ToStringNoNewLines() const;
    int measQuantityGERAN_Clear();
    bool measQuantityGERAN_IsPresent() const;
private:
    bool measQuantityGERAN_present;
    measQuantityGERAN_Enum measQuantityGERAN_internal_value;

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
