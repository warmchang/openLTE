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

#ifndef __RRM_Config_H__
#define __RRM_Config_H__

#include "CandidateCellInfoList_r10.h"

#include <array>
#include <cstdint>
#include <vector>

class RRM_Config
{
public:
    RRM_Config() : ue_InactiveTime_present{false}, candidateCellInfoList_r10_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // ue-InactiveTime
public:
    enum ue_InactiveTime_Enum {
        k_ue_InactiveTime_s1 = 0,
        k_ue_InactiveTime_s2,
        k_ue_InactiveTime_s3,
        k_ue_InactiveTime_s5,
        k_ue_InactiveTime_s7,
        k_ue_InactiveTime_s10,
        k_ue_InactiveTime_s15,
        k_ue_InactiveTime_s20,
        k_ue_InactiveTime_s25,
        k_ue_InactiveTime_s30,
        k_ue_InactiveTime_s40,
        k_ue_InactiveTime_s50,
        k_ue_InactiveTime_min1,
        k_ue_InactiveTime_min1s20c,
        k_ue_InactiveTime_min1s40,
        k_ue_InactiveTime_min2,
        k_ue_InactiveTime_min2s30,
        k_ue_InactiveTime_min3,
        k_ue_InactiveTime_min3s30,
        k_ue_InactiveTime_min4,
        k_ue_InactiveTime_min5,
        k_ue_InactiveTime_min6,
        k_ue_InactiveTime_min7,
        k_ue_InactiveTime_min8,
        k_ue_InactiveTime_min9,
        k_ue_InactiveTime_min10,
        k_ue_InactiveTime_min12,
        k_ue_InactiveTime_min14,
        k_ue_InactiveTime_min17,
        k_ue_InactiveTime_min20,
        k_ue_InactiveTime_min24,
        k_ue_InactiveTime_min28,
        k_ue_InactiveTime_min33,
        k_ue_InactiveTime_min38,
        k_ue_InactiveTime_min44,
        k_ue_InactiveTime_min50,
        k_ue_InactiveTime_hr1,
        k_ue_InactiveTime_hr1min30,
        k_ue_InactiveTime_hr2,
        k_ue_InactiveTime_hr2min30,
        k_ue_InactiveTime_hr3,
        k_ue_InactiveTime_hr3min30,
        k_ue_InactiveTime_hr4,
        k_ue_InactiveTime_hr5,
        k_ue_InactiveTime_hr6,
        k_ue_InactiveTime_hr8,
        k_ue_InactiveTime_hr10,
        k_ue_InactiveTime_hr13,
        k_ue_InactiveTime_hr16,
        k_ue_InactiveTime_hr20,
        k_ue_InactiveTime_day1,
        k_ue_InactiveTime_day1hr12,
        k_ue_InactiveTime_day2,
        k_ue_InactiveTime_day2hr12,
        k_ue_InactiveTime_day3,
        k_ue_InactiveTime_day4,
        k_ue_InactiveTime_day5,
        k_ue_InactiveTime_day7,
        k_ue_InactiveTime_day10,
        k_ue_InactiveTime_day14,
        k_ue_InactiveTime_day19,
        k_ue_InactiveTime_day24,
        k_ue_InactiveTime_day30,
        k_ue_InactiveTime_dayMoreThan30,
    };
    int ue_InactiveTime_Pack(std::vector<uint8_t> &bits);
    int ue_InactiveTime_Unpack(std::vector<uint8_t> bits);
    int ue_InactiveTime_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    ue_InactiveTime_Enum ue_InactiveTime_Value() const;
    int ue_InactiveTime_SetValue(ue_InactiveTime_Enum value);
    int ue_InactiveTime_SetValue(std::string value);
    std::string ue_InactiveTime_ValueToString(ue_InactiveTime_Enum value) const;
    uint64_t ue_InactiveTime_NumberOfValues() const;
    std::string ue_InactiveTime_ToString(uint32_t indent) const;
    std::string ue_InactiveTime_ToStringNoNewLines() const;
    int ue_InactiveTime_Clear();
    bool ue_InactiveTime_IsPresent() const;
private:
    bool ue_InactiveTime_present;
    ue_InactiveTime_Enum ue_InactiveTime_internal_value;

    // candidateCellInfoList-r10
public:
    CandidateCellInfoList_r10* candidateCellInfoList_r10_Set();
    int candidateCellInfoList_r10_Set(CandidateCellInfoList_r10 &value);
    const CandidateCellInfoList_r10& candidateCellInfoList_r10_Get() const;
    std::string candidateCellInfoList_r10_ToString(uint32_t indent) const;
    std::string candidateCellInfoList_r10_ToStringNoNewLines() const;
    int candidateCellInfoList_r10_Clear();
    bool candidateCellInfoList_r10_IsPresent() const;
private:
    bool candidateCellInfoList_r10_present;
    CandidateCellInfoList_r10 candidateCellInfoList_r10;

};

#endif
