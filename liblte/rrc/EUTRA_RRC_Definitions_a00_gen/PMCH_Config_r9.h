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

#ifndef __PMCH_Config_r9_H__
#define __PMCH_Config_r9_H__

#include <array>
#include <cstdint>
#include <vector>

class PMCH_Config_r9
{
public:
    PMCH_Config_r9() : sf_AllocEnd_r9_present{false}, dataMCS_r9_present{false}, mch_SchedulingPeriod_r9_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // sf-AllocEnd-r9
public:
    int sf_AllocEnd_r9_Pack(std::vector<uint8_t> &bits);
    int sf_AllocEnd_r9_Unpack(std::vector<uint8_t> bits);
    int sf_AllocEnd_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t sf_AllocEnd_r9_Value() const;
    int sf_AllocEnd_r9_SetValue(int64_t value);
    std::string sf_AllocEnd_r9_ToString(uint32_t indent) const;
    std::string sf_AllocEnd_r9_ToStringNoNewLines() const;
    int sf_AllocEnd_r9_Clear();
    bool sf_AllocEnd_r9_IsPresent() const;
private:
    bool sf_AllocEnd_r9_present;
    int64_t sf_AllocEnd_r9_internal_value;

    // dataMCS-r9
public:
    int dataMCS_r9_Pack(std::vector<uint8_t> &bits);
    int dataMCS_r9_Unpack(std::vector<uint8_t> bits);
    int dataMCS_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t dataMCS_r9_Value() const;
    int dataMCS_r9_SetValue(int64_t value);
    std::string dataMCS_r9_ToString(uint32_t indent) const;
    std::string dataMCS_r9_ToStringNoNewLines() const;
    int dataMCS_r9_Clear();
    bool dataMCS_r9_IsPresent() const;
private:
    bool dataMCS_r9_present;
    int64_t dataMCS_r9_internal_value;

    // mch-SchedulingPeriod-r9
public:
    enum mch_SchedulingPeriod_r9_Enum {
        k_mch_SchedulingPeriod_r9_rf8 = 0,
        k_mch_SchedulingPeriod_r9_rf16,
        k_mch_SchedulingPeriod_r9_rf32,
        k_mch_SchedulingPeriod_r9_rf64,
        k_mch_SchedulingPeriod_r9_rf128,
        k_mch_SchedulingPeriod_r9_rf256,
        k_mch_SchedulingPeriod_r9_rf512,
        k_mch_SchedulingPeriod_r9_rf1024,
    };
    int mch_SchedulingPeriod_r9_Pack(std::vector<uint8_t> &bits);
    int mch_SchedulingPeriod_r9_Unpack(std::vector<uint8_t> bits);
    int mch_SchedulingPeriod_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    mch_SchedulingPeriod_r9_Enum mch_SchedulingPeriod_r9_Value() const;
    int mch_SchedulingPeriod_r9_SetValue(mch_SchedulingPeriod_r9_Enum value);
    int mch_SchedulingPeriod_r9_SetValue(std::string value);
    std::string mch_SchedulingPeriod_r9_ValueToString(mch_SchedulingPeriod_r9_Enum value) const;
    uint64_t mch_SchedulingPeriod_r9_NumberOfValues() const;
    std::string mch_SchedulingPeriod_r9_ToString(uint32_t indent) const;
    std::string mch_SchedulingPeriod_r9_ToStringNoNewLines() const;
    int mch_SchedulingPeriod_r9_Clear();
    bool mch_SchedulingPeriod_r9_IsPresent() const;
private:
    bool mch_SchedulingPeriod_r9_present;
    mch_SchedulingPeriod_r9_Enum mch_SchedulingPeriod_r9_internal_value;

};

#endif
