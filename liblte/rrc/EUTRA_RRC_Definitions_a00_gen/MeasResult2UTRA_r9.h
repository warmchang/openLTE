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

#ifndef __MeasResult2UTRA_r9_H__
#define __MeasResult2UTRA_r9_H__

#include "ARFCN_ValueUTRA.h"
#include "MeasResultListUTRA.h"

#include <array>
#include <cstdint>
#include <vector>

class MeasResult2UTRA_r9
{
public:
    MeasResult2UTRA_r9() : carrierFreq_r9_present{false}, measResultList_r9_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // carrierFreq-r9
public:
    ARFCN_ValueUTRA* carrierFreq_r9_Set();
    int carrierFreq_r9_Set(ARFCN_ValueUTRA &value);
    const ARFCN_ValueUTRA& carrierFreq_r9_Get() const;
    std::string carrierFreq_r9_ToString(uint32_t indent) const;
    std::string carrierFreq_r9_ToStringNoNewLines() const;
    int carrierFreq_r9_Clear();
    bool carrierFreq_r9_IsPresent() const;
private:
    bool carrierFreq_r9_present;
    ARFCN_ValueUTRA carrierFreq_r9;

    // measResultList-r9
public:
    MeasResultListUTRA* measResultList_r9_Set();
    int measResultList_r9_Set(MeasResultListUTRA &value);
    const MeasResultListUTRA& measResultList_r9_Get() const;
    std::string measResultList_r9_ToString(uint32_t indent) const;
    std::string measResultList_r9_ToStringNoNewLines() const;
    int measResultList_r9_Clear();
    bool measResultList_r9_IsPresent() const;
private:
    bool measResultList_r9_present;
    MeasResultListUTRA measResultList_r9;

};

#endif
