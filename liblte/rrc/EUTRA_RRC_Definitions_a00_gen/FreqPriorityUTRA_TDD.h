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

#ifndef __FreqPriorityUTRA_TDD_H__
#define __FreqPriorityUTRA_TDD_H__

#include "ARFCN_ValueUTRA.h"
#include "CellReselectionPriority.h"

#include <array>
#include <cstdint>
#include <vector>

class FreqPriorityUTRA_TDD
{
public:
    FreqPriorityUTRA_TDD() : carrierFreq_present{false}, cellReselectionPriority_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // carrierFreq
public:
    ARFCN_ValueUTRA* carrierFreq_Set();
    int carrierFreq_Set(ARFCN_ValueUTRA &value);
    const ARFCN_ValueUTRA& carrierFreq_Get() const;
    std::string carrierFreq_ToString(uint32_t indent) const;
    std::string carrierFreq_ToStringNoNewLines() const;
    int carrierFreq_Clear();
    bool carrierFreq_IsPresent() const;
private:
    bool carrierFreq_present;
    ARFCN_ValueUTRA carrierFreq;

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
