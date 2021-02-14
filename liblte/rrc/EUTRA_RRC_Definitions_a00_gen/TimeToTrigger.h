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

#ifndef __TimeToTrigger_H__
#define __TimeToTrigger_H__

#include <array>
#include <cstdint>
#include <vector>

class TimeToTrigger
{
public:
    TimeToTrigger() : present{false} {};
public:
    enum Enum {
        k_ms0 = 0,
        k_ms40,
        k_ms64,
        k_ms80,
        k_ms100,
        k_ms128,
        k_ms160,
        k_ms256,
        k_ms320,
        k_ms480,
        k_ms512,
        k_ms640,
        k_ms1024,
        k_ms1280,
        k_ms2560,
        k_ms5120,
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
