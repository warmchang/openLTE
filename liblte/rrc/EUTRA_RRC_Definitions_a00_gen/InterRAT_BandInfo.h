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

#ifndef __InterRAT_BandInfo_H__
#define __InterRAT_BandInfo_H__

#include <array>
#include <cstdint>
#include <vector>

class InterRAT_BandInfo
{
public:
    InterRAT_BandInfo() : interRAT_NeedForGaps_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // interRAT-NeedForGaps
public:
    int interRAT_NeedForGaps_Pack(std::vector<uint8_t> &bits);
    int interRAT_NeedForGaps_Unpack(std::vector<uint8_t> bits);
    int interRAT_NeedForGaps_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    bool interRAT_NeedForGaps_Value() const;
    int interRAT_NeedForGaps_SetValue(bool value);
    std::string interRAT_NeedForGaps_ToString(uint32_t indent) const;
    std::string interRAT_NeedForGaps_ToStringNoNewLines() const;
    int interRAT_NeedForGaps_Clear();
    bool interRAT_NeedForGaps_IsPresent() const;
private:
    bool interRAT_NeedForGaps_present;
    bool interRAT_NeedForGaps_internal_value;

};

#endif
