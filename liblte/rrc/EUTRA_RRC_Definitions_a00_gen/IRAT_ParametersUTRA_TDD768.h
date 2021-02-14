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

#ifndef __IRAT_ParametersUTRA_TDD768_H__
#define __IRAT_ParametersUTRA_TDD768_H__

#include "SupportedBandListUTRA_TDD768.h"

#include <array>
#include <cstdint>
#include <vector>

class IRAT_ParametersUTRA_TDD768
{
public:
    IRAT_ParametersUTRA_TDD768() : supportedBandListUTRA_TDD768_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // supportedBandListUTRA-TDD768
public:
    SupportedBandListUTRA_TDD768* supportedBandListUTRA_TDD768_Set();
    int supportedBandListUTRA_TDD768_Set(SupportedBandListUTRA_TDD768 &value);
    const SupportedBandListUTRA_TDD768& supportedBandListUTRA_TDD768_Get() const;
    std::string supportedBandListUTRA_TDD768_ToString(uint32_t indent) const;
    std::string supportedBandListUTRA_TDD768_ToStringNoNewLines() const;
    int supportedBandListUTRA_TDD768_Clear();
    bool supportedBandListUTRA_TDD768_IsPresent() const;
private:
    bool supportedBandListUTRA_TDD768_present;
    SupportedBandListUTRA_TDD768 supportedBandListUTRA_TDD768;

};

#endif
