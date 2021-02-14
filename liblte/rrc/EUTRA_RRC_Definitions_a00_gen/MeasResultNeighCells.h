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

#ifndef __MeasResultNeighCells_H__
#define __MeasResultNeighCells_H__

#include "MeasResultList2EUTRA_r9.h"
#include "MeasResultList2UTRA_r9.h"
#include "MeasResultListGERAN.h"
#include "MeasResultList2CDMA2000_r9.h"

#include <array>
#include <cstdint>
#include <vector>

class MeasResultNeighCells
{
public:
    MeasResultNeighCells() : measResultListEUTRA_present{false}, measResultListUTRA_present{false}, measResultListGERAN_present{false}, measResultsCDMA2000_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // measResultListEUTRA
public:
    MeasResultList2EUTRA_r9* measResultListEUTRA_Set();
    int measResultListEUTRA_Set(MeasResultList2EUTRA_r9 &value);
    const MeasResultList2EUTRA_r9& measResultListEUTRA_Get() const;
    std::string measResultListEUTRA_ToString(uint32_t indent) const;
    std::string measResultListEUTRA_ToStringNoNewLines() const;
    int measResultListEUTRA_Clear();
    bool measResultListEUTRA_IsPresent() const;
private:
    bool measResultListEUTRA_present;
    MeasResultList2EUTRA_r9 measResultListEUTRA;

    // measResultListUTRA
public:
    MeasResultList2UTRA_r9* measResultListUTRA_Set();
    int measResultListUTRA_Set(MeasResultList2UTRA_r9 &value);
    const MeasResultList2UTRA_r9& measResultListUTRA_Get() const;
    std::string measResultListUTRA_ToString(uint32_t indent) const;
    std::string measResultListUTRA_ToStringNoNewLines() const;
    int measResultListUTRA_Clear();
    bool measResultListUTRA_IsPresent() const;
private:
    bool measResultListUTRA_present;
    MeasResultList2UTRA_r9 measResultListUTRA;

    // measResultListGERAN
public:
    MeasResultListGERAN* measResultListGERAN_Set();
    int measResultListGERAN_Set(MeasResultListGERAN &value);
    const MeasResultListGERAN& measResultListGERAN_Get() const;
    std::string measResultListGERAN_ToString(uint32_t indent) const;
    std::string measResultListGERAN_ToStringNoNewLines() const;
    int measResultListGERAN_Clear();
    bool measResultListGERAN_IsPresent() const;
private:
    bool measResultListGERAN_present;
    MeasResultListGERAN measResultListGERAN;

    // measResultsCDMA2000
public:
    MeasResultList2CDMA2000_r9* measResultsCDMA2000_Set();
    int measResultsCDMA2000_Set(MeasResultList2CDMA2000_r9 &value);
    const MeasResultList2CDMA2000_r9& measResultsCDMA2000_Get() const;
    std::string measResultsCDMA2000_ToString(uint32_t indent) const;
    std::string measResultsCDMA2000_ToStringNoNewLines() const;
    int measResultsCDMA2000_Clear();
    bool measResultsCDMA2000_IsPresent() const;
private:
    bool measResultsCDMA2000_present;
    MeasResultList2CDMA2000_r9 measResultsCDMA2000;

};

#endif
