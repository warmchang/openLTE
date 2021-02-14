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

#ifndef __SIB_Type_H__
#define __SIB_Type_H__

#include <array>
#include <cstdint>
#include <vector>

class SIB_Type
{
public:
    SIB_Type() : present{false} {};
public:
    enum Enum {
        k_sibType3 = 0,
        k_sibType4,
        k_sibType5,
        k_sibType6,
        k_sibType7,
        k_sibType8,
        k_sibType9,
        k_sibType10,
        k_sibType11,
        k_sibType12_v920,
        k_sibType13_v920,
        k_spare5,
        k_spare4,
        k_spare3,
        k_spare2,
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
