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

#ifndef __QuantityConfigEUTRA_H__
#define __QuantityConfigEUTRA_H__

#include "FilterCoefficient.h"
#include "FilterCoefficient.h"

#include <array>
#include <cstdint>
#include <vector>

class QuantityConfigEUTRA
{
public:
    QuantityConfigEUTRA() : filterCoefficientRSRP_present{false}, filterCoefficientRSRQ_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // filterCoefficientRSRP
public:
    FilterCoefficient* filterCoefficientRSRP_Set();
    int filterCoefficientRSRP_Set(FilterCoefficient &value);
    const FilterCoefficient& filterCoefficientRSRP_Get() const;
    FilterCoefficient::Enum filterCoefficientRSRP_GetDefault() const;
    std::string filterCoefficientRSRP_ToString(uint32_t indent) const;
    std::string filterCoefficientRSRP_ToStringNoNewLines() const;
    int filterCoefficientRSRP_Clear();
    bool filterCoefficientRSRP_IsPresent() const;
private:
    bool filterCoefficientRSRP_present;
    FilterCoefficient filterCoefficientRSRP;

    // filterCoefficientRSRQ
public:
    FilterCoefficient* filterCoefficientRSRQ_Set();
    int filterCoefficientRSRQ_Set(FilterCoefficient &value);
    const FilterCoefficient& filterCoefficientRSRQ_Get() const;
    FilterCoefficient::Enum filterCoefficientRSRQ_GetDefault() const;
    std::string filterCoefficientRSRQ_ToString(uint32_t indent) const;
    std::string filterCoefficientRSRQ_ToStringNoNewLines() const;
    int filterCoefficientRSRQ_Clear();
    bool filterCoefficientRSRQ_IsPresent() const;
private:
    bool filterCoefficientRSRQ_present;
    FilterCoefficient filterCoefficientRSRQ;

};

#endif
