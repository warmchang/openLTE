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

#ifndef __QuantityConfigUTRA_v10x0_H__
#define __QuantityConfigUTRA_v10x0_H__

#include "FilterCoefficient.h"

#include <array>
#include <cstdint>
#include <vector>

class QuantityConfigUTRA_v10x0
{
public:
    QuantityConfigUTRA_v10x0() : filterCoefficient2_FDD_r10_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // filterCoefficient2-FDD-r10
public:
    FilterCoefficient* filterCoefficient2_FDD_r10_Set();
    int filterCoefficient2_FDD_r10_Set(FilterCoefficient &value);
    const FilterCoefficient& filterCoefficient2_FDD_r10_Get() const;
    FilterCoefficient::Enum filterCoefficient2_FDD_r10_GetDefault() const;
    std::string filterCoefficient2_FDD_r10_ToString(uint32_t indent) const;
    std::string filterCoefficient2_FDD_r10_ToStringNoNewLines() const;
    int filterCoefficient2_FDD_r10_Clear();
    bool filterCoefficient2_FDD_r10_IsPresent() const;
private:
    bool filterCoefficient2_FDD_r10_present;
    FilterCoefficient filterCoefficient2_FDD_r10;

};

#endif
