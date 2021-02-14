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

#ifndef __CarrierFreqListUTRA_FDD_H__
#define __CarrierFreqListUTRA_FDD_H__

#include "CarrierFreqUTRA_FDD.h"

#include <array>
#include <cstdint>
#include <vector>

class CarrierFreqListUTRA_FDD
{
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::vector<CarrierFreqUTRA_FDD> Value() const;
    int SetValue(std::vector<CarrierFreqUTRA_FDD>);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;
private:
    std::vector<CarrierFreqUTRA_FDD> internal_value;
    bool present;
};

#endif
