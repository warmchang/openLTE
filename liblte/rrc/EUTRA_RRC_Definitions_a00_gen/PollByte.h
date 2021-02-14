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

#ifndef __PollByte_H__
#define __PollByte_H__

#include <array>
#include <cstdint>
#include <vector>

class PollByte
{
public:
    PollByte() : present{false} {};
public:
    enum Enum {
        k_kB25 = 0,
        k_kB50,
        k_kB75,
        k_kB100,
        k_kB125,
        k_kB250,
        k_kB375,
        k_kB500,
        k_kB750,
        k_kB1000,
        k_kB1250,
        k_kB1500,
        k_kB2000,
        k_kB3000,
        k_kBinfinity,
        k_spare1,
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
