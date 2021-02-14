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

#ifndef __CarrierFreqGERAN_H__
#define __CarrierFreqGERAN_H__

#include "ARFCN_ValueGERAN.h"
#include "BandIndicatorGERAN.h"

#include <array>
#include <cstdint>
#include <vector>

class CarrierFreqGERAN
{
public:
    CarrierFreqGERAN() : arfcn_present{false}, bandIndicator_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // arfcn
public:
    ARFCN_ValueGERAN* arfcn_Set();
    int arfcn_Set(ARFCN_ValueGERAN &value);
    const ARFCN_ValueGERAN& arfcn_Get() const;
    std::string arfcn_ToString(uint32_t indent) const;
    std::string arfcn_ToStringNoNewLines() const;
    int arfcn_Clear();
    bool arfcn_IsPresent() const;
private:
    bool arfcn_present;
    ARFCN_ValueGERAN arfcn;

    // bandIndicator
public:
    BandIndicatorGERAN* bandIndicator_Set();
    int bandIndicator_Set(BandIndicatorGERAN &value);
    const BandIndicatorGERAN& bandIndicator_Get() const;
    std::string bandIndicator_ToString(uint32_t indent) const;
    std::string bandIndicator_ToStringNoNewLines() const;
    int bandIndicator_Clear();
    bool bandIndicator_IsPresent() const;
private:
    bool bandIndicator_present;
    BandIndicatorGERAN bandIndicator;

};

#endif
