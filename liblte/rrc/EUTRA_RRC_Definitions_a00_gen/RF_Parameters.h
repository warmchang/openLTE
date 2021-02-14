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

#ifndef __RF_Parameters_H__
#define __RF_Parameters_H__

#include "SupportedBandListEUTRA.h"

#include <array>
#include <cstdint>
#include <vector>

class RF_Parameters
{
public:
    RF_Parameters() : supportedBandListEUTRA_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // supportedBandListEUTRA
public:
    SupportedBandListEUTRA* supportedBandListEUTRA_Set();
    int supportedBandListEUTRA_Set(SupportedBandListEUTRA &value);
    const SupportedBandListEUTRA& supportedBandListEUTRA_Get() const;
    std::string supportedBandListEUTRA_ToString(uint32_t indent) const;
    std::string supportedBandListEUTRA_ToStringNoNewLines() const;
    int supportedBandListEUTRA_Clear();
    bool supportedBandListEUTRA_IsPresent() const;
private:
    bool supportedBandListEUTRA_present;
    SupportedBandListEUTRA supportedBandListEUTRA;

};

#endif
