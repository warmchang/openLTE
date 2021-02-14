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

#ifndef __MeasParameters_H__
#define __MeasParameters_H__

#include "BandListEUTRA.h"

#include <array>
#include <cstdint>
#include <vector>

class MeasParameters
{
public:
    MeasParameters() : bandListEUTRA_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // bandListEUTRA
public:
    BandListEUTRA* bandListEUTRA_Set();
    int bandListEUTRA_Set(BandListEUTRA &value);
    const BandListEUTRA& bandListEUTRA_Get() const;
    std::string bandListEUTRA_ToString(uint32_t indent) const;
    std::string bandListEUTRA_ToStringNoNewLines() const;
    int bandListEUTRA_Clear();
    bool bandListEUTRA_IsPresent() const;
private:
    bool bandListEUTRA_present;
    BandListEUTRA bandListEUTRA;

};

#endif
