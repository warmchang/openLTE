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

#ifndef __InterFreqBandInfo_H__
#define __InterFreqBandInfo_H__

#include <array>
#include <cstdint>
#include <vector>

class InterFreqBandInfo
{
public:
    InterFreqBandInfo() : interFreqNeedForGaps_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // interFreqNeedForGaps
public:
    int interFreqNeedForGaps_Pack(std::vector<uint8_t> &bits);
    int interFreqNeedForGaps_Unpack(std::vector<uint8_t> bits);
    int interFreqNeedForGaps_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    bool interFreqNeedForGaps_Value() const;
    int interFreqNeedForGaps_SetValue(bool value);
    std::string interFreqNeedForGaps_ToString(uint32_t indent) const;
    std::string interFreqNeedForGaps_ToStringNoNewLines() const;
    int interFreqNeedForGaps_Clear();
    bool interFreqNeedForGaps_IsPresent() const;
private:
    bool interFreqNeedForGaps_present;
    bool interFreqNeedForGaps_internal_value;

};

#endif
