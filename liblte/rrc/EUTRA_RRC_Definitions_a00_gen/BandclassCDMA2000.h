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

#ifndef __BandclassCDMA2000_H__
#define __BandclassCDMA2000_H__

#include <array>
#include <cstdint>
#include <vector>

class BandclassCDMA2000
{
public:
    BandclassCDMA2000() : present{false} {};
public:
    enum Enum {
        k_bc0 = 0,
        k_bc1,
        k_bc2,
        k_bc3,
        k_bc4,
        k_bc5,
        k_bc6,
        k_bc7,
        k_bc8,
        k_bc9,
        k_bc10,
        k_bc11,
        k_bc12,
        k_bc13,
        k_bc14,
        k_bc15,
        k_bc16,
        k_bc17,
        k_spare14,
        k_spare13,
        k_spare12,
        k_spare11,
        k_spare10,
        k_spare9,
        k_spare8,
        k_spare7,
        k_spare6,
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
