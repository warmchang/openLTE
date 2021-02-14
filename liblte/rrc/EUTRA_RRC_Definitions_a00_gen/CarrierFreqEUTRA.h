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

#ifndef __CarrierFreqEUTRA_H__
#define __CarrierFreqEUTRA_H__

#include "ARFCN_ValueEUTRA.h"
#include "ARFCN_ValueEUTRA.h"

#include <array>
#include <cstdint>
#include <vector>

class CarrierFreqEUTRA
{
public:
    CarrierFreqEUTRA() : dl_CarrierFreq_present{false}, ul_CarrierFreq_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // dl-CarrierFreq
public:
    ARFCN_ValueEUTRA* dl_CarrierFreq_Set();
    int dl_CarrierFreq_Set(ARFCN_ValueEUTRA &value);
    const ARFCN_ValueEUTRA& dl_CarrierFreq_Get() const;
    std::string dl_CarrierFreq_ToString(uint32_t indent) const;
    std::string dl_CarrierFreq_ToStringNoNewLines() const;
    int dl_CarrierFreq_Clear();
    bool dl_CarrierFreq_IsPresent() const;
private:
    bool dl_CarrierFreq_present;
    ARFCN_ValueEUTRA dl_CarrierFreq;

    // ul-CarrierFreq
public:
    ARFCN_ValueEUTRA* ul_CarrierFreq_Set();
    int ul_CarrierFreq_Set(ARFCN_ValueEUTRA &value);
    const ARFCN_ValueEUTRA& ul_CarrierFreq_Get() const;
    std::string ul_CarrierFreq_ToString(uint32_t indent) const;
    std::string ul_CarrierFreq_ToStringNoNewLines() const;
    int ul_CarrierFreq_Clear();
    bool ul_CarrierFreq_IsPresent() const;
private:
    bool ul_CarrierFreq_present;
    ARFCN_ValueEUTRA ul_CarrierFreq;

};

#endif
