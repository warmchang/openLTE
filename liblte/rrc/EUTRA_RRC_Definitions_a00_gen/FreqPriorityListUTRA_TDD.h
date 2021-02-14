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

#ifndef __FreqPriorityListUTRA_TDD_H__
#define __FreqPriorityListUTRA_TDD_H__

#include "FreqPriorityUTRA_TDD.h"

#include <array>
#include <cstdint>
#include <vector>

class FreqPriorityListUTRA_TDD
{
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::vector<FreqPriorityUTRA_TDD> Value() const;
    int SetValue(std::vector<FreqPriorityUTRA_TDD>);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;
private:
    std::vector<FreqPriorityUTRA_TDD> internal_value;
    bool present;
};

#endif
