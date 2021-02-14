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

#ifndef __IRAT_ParametersUTRA_FDD_H__
#define __IRAT_ParametersUTRA_FDD_H__

#include "SupportedBandListUTRA_FDD.h"

#include <array>
#include <cstdint>
#include <vector>

class IRAT_ParametersUTRA_FDD
{
public:
    IRAT_ParametersUTRA_FDD() : supportedBandListUTRA_FDD_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // supportedBandListUTRA-FDD
public:
    SupportedBandListUTRA_FDD* supportedBandListUTRA_FDD_Set();
    int supportedBandListUTRA_FDD_Set(SupportedBandListUTRA_FDD &value);
    const SupportedBandListUTRA_FDD& supportedBandListUTRA_FDD_Get() const;
    std::string supportedBandListUTRA_FDD_ToString(uint32_t indent) const;
    std::string supportedBandListUTRA_FDD_ToStringNoNewLines() const;
    int supportedBandListUTRA_FDD_Clear();
    bool supportedBandListUTRA_FDD_IsPresent() const;
private:
    bool supportedBandListUTRA_FDD_present;
    SupportedBandListUTRA_FDD supportedBandListUTRA_FDD;

};

#endif
