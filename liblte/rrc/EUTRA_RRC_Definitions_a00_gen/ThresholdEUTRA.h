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

#ifndef __ThresholdEUTRA_H__
#define __ThresholdEUTRA_H__

#include "RSRP_Range.h"
#include "RSRQ_Range.h"

#include <array>
#include <cstdint>
#include <vector>

class ThresholdEUTRA
{
public:
    enum Enum {
        k_threshold_RSRP = 0,
        k_threshold_RSRQ,
    };
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    Enum Choice() const;
    int SetChoice(Enum choice);
    std::string ChoiceToString(Enum value) const;
    uint64_t NumberOfChoices() const;
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;
    int Clear();
    bool IsPresent() const;
private:
    bool present;
    Enum internal_choice;

    // threshold-RSRP
public:
    RSRP_Range* threshold_RSRP_Set();
    int threshold_RSRP_Set(RSRP_Range &value);
    const RSRP_Range& threshold_RSRP_Get() const;
    std::string threshold_RSRP_ToString(uint32_t indent) const;
    std::string threshold_RSRP_ToStringNoNewLines() const;
    int threshold_RSRP_Clear();
    bool threshold_RSRP_IsPresent() const;
private:
    bool threshold_RSRP_present;
    RSRP_Range threshold_RSRP;

    // threshold-RSRQ
public:
    RSRQ_Range* threshold_RSRQ_Set();
    int threshold_RSRQ_Set(RSRQ_Range &value);
    const RSRQ_Range& threshold_RSRQ_Get() const;
    std::string threshold_RSRQ_ToString(uint32_t indent) const;
    std::string threshold_RSRQ_ToStringNoNewLines() const;
    int threshold_RSRQ_Clear();
    bool threshold_RSRQ_IsPresent() const;
private:
    bool threshold_RSRQ_present;
    RSRQ_Range threshold_RSRQ;

};

#endif
