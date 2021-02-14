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

#ifndef __RadioResourceConfigDedicatedSCell_r10_H__
#define __RadioResourceConfigDedicatedSCell_r10_H__

#include "PhysicalConfigDedicatedSCell_r10.h"

#include <array>
#include <cstdint>
#include <vector>

class RadioResourceConfigDedicatedSCell_r10
{
public:
    RadioResourceConfigDedicatedSCell_r10() : physicalConfigDedicated_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // physicalConfigDedicated
public:
    PhysicalConfigDedicatedSCell_r10* physicalConfigDedicated_Set();
    int physicalConfigDedicated_Set(PhysicalConfigDedicatedSCell_r10 &value);
    const PhysicalConfigDedicatedSCell_r10& physicalConfigDedicated_Get() const;
    std::string physicalConfigDedicated_ToString(uint32_t indent) const;
    std::string physicalConfigDedicated_ToStringNoNewLines() const;
    int physicalConfigDedicated_Clear();
    bool physicalConfigDedicated_IsPresent() const;
private:
    bool physicalConfigDedicated_present;
    PhysicalConfigDedicatedSCell_r10 physicalConfigDedicated;

};

#endif
