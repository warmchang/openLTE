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

#ifndef __SupportedBandUTRA_TDD128_H__
#define __SupportedBandUTRA_TDD128_H__

#include <array>
#include <cstdint>
#include <vector>

class SupportedBandUTRA_TDD128
{
public:
    SupportedBandUTRA_TDD128() : present{false} {};
public:
    enum Enum {
        k_a = 0,
        k_b,
        k_c,
        k_d,
        k_e,
        k_f,
        k_g,
        k_h,
        k_i,
        k_j,
        k_k,
        k_l,
        k_m,
        k_n,
        k_o,
        k_p,
    };
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    Enum Value() const;
    int SetValue(Enum value);
    int SetValue(std::string value);
    std::string ValueToString(Enum value) const;
    uint64_t NumberOfValues() const;
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;
    int Clear();
    bool IsPresent() const;
private:
    bool present;
    Enum internal_value;
};

#endif
