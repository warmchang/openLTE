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

#ifndef __Q_OffsetRange_H__
#define __Q_OffsetRange_H__

#include <array>
#include <cstdint>
#include <vector>

class Q_OffsetRange
{
public:
    Q_OffsetRange() : present{false} {};
public:
    enum Enum {
        k_dB_24 = 0,
        k_dB_22,
        k_dB_20,
        k_dB_18,
        k_dB_16,
        k_dB_14,
        k_dB_12,
        k_dB_10,
        k_dB_8,
        k_dB_6,
        k_dB_5,
        k_dB_4,
        k_dB_3,
        k_dB_2,
        k_dB_1,
        k_dB0,
        k_dB1,
        k_dB2,
        k_dB3,
        k_dB4,
        k_dB5,
        k_dB6,
        k_dB8,
        k_dB10,
        k_dB12,
        k_dB14,
        k_dB16,
        k_dB18,
        k_dB20,
        k_dB22,
        k_dB24,
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
