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

#ifndef __T_Reordering_H__
#define __T_Reordering_H__

#include <array>
#include <cstdint>
#include <vector>

class T_Reordering
{
public:
    T_Reordering() : present{false} {};
public:
    enum Enum {
        k_ms0 = 0,
        k_ms5,
        k_ms10,
        k_ms15,
        k_ms20,
        k_ms25,
        k_ms30,
        k_ms35,
        k_ms40,
        k_ms45,
        k_ms50,
        k_ms55,
        k_ms60,
        k_ms65,
        k_ms70,
        k_ms75,
        k_ms80,
        k_ms85,
        k_ms90,
        k_ms95,
        k_ms100,
        k_ms110,
        k_ms120,
        k_ms130,
        k_ms140,
        k_ms150,
        k_ms160,
        k_ms170,
        k_ms180,
        k_ms190,
        k_ms200,
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
