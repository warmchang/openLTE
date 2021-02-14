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

#ifndef __FreqsPriorityGERAN_H__
#define __FreqsPriorityGERAN_H__

#include "CarrierFreqsGERAN.h"
#include "CellReselectionPriority.h"

#include <array>
#include <cstdint>
#include <vector>

class FreqsPriorityGERAN
{
public:
    FreqsPriorityGERAN() : carrierFreqs_present{false}, cellReselectionPriority_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // carrierFreqs
public:
    CarrierFreqsGERAN* carrierFreqs_Set();
    int carrierFreqs_Set(CarrierFreqsGERAN &value);
    const CarrierFreqsGERAN& carrierFreqs_Get() const;
    std::string carrierFreqs_ToString(uint32_t indent) const;
    std::string carrierFreqs_ToStringNoNewLines() const;
    int carrierFreqs_Clear();
    bool carrierFreqs_IsPresent() const;
private:
    bool carrierFreqs_present;
    CarrierFreqsGERAN carrierFreqs;

    // cellReselectionPriority
public:
    CellReselectionPriority* cellReselectionPriority_Set();
    int cellReselectionPriority_Set(CellReselectionPriority &value);
    const CellReselectionPriority& cellReselectionPriority_Get() const;
    std::string cellReselectionPriority_ToString(uint32_t indent) const;
    std::string cellReselectionPriority_ToStringNoNewLines() const;
    int cellReselectionPriority_Clear();
    bool cellReselectionPriority_IsPresent() const;
private:
    bool cellReselectionPriority_present;
    CellReselectionPriority cellReselectionPriority;

};

#endif
