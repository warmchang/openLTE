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

#ifndef __BandInfoEUTRA_H__
#define __BandInfoEUTRA_H__

#include "InterFreqBandList.h"
#include "InterRAT_BandList.h"

#include <array>
#include <cstdint>
#include <vector>

class BandInfoEUTRA
{
public:
    BandInfoEUTRA() : interFreqBandList_present{false}, interRAT_BandList_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // interFreqBandList
public:
    InterFreqBandList* interFreqBandList_Set();
    int interFreqBandList_Set(InterFreqBandList &value);
    const InterFreqBandList& interFreqBandList_Get() const;
    std::string interFreqBandList_ToString(uint32_t indent) const;
    std::string interFreqBandList_ToStringNoNewLines() const;
    int interFreqBandList_Clear();
    bool interFreqBandList_IsPresent() const;
private:
    bool interFreqBandList_present;
    InterFreqBandList interFreqBandList;

    // interRAT-BandList
public:
    InterRAT_BandList* interRAT_BandList_Set();
    int interRAT_BandList_Set(InterRAT_BandList &value);
    const InterRAT_BandList& interRAT_BandList_Get() const;
    std::string interRAT_BandList_ToString(uint32_t indent) const;
    std::string interRAT_BandList_ToStringNoNewLines() const;
    int interRAT_BandList_Clear();
    bool interRAT_BandList_IsPresent() const;
private:
    bool interRAT_BandList_present;
    InterRAT_BandList interRAT_BandList;

};

#endif
