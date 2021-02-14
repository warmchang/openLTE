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

#ifndef __UplinkPowerControlCommon_H__
#define __UplinkPowerControlCommon_H__

#include "DeltaFList_PUCCH.h"

#include <array>
#include <cstdint>
#include <vector>

class UplinkPowerControlCommon
{
public:
    UplinkPowerControlCommon() : p0_NominalPUSCH_present{false}, alpha_present{false}, p0_NominalPUCCH_present{false}, deltaFList_PUCCH_present{false}, deltaPreambleMsg3_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // p0-NominalPUSCH
public:
    int p0_NominalPUSCH_Pack(std::vector<uint8_t> &bits);
    int p0_NominalPUSCH_Unpack(std::vector<uint8_t> bits);
    int p0_NominalPUSCH_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t p0_NominalPUSCH_Value() const;
    int p0_NominalPUSCH_SetValue(int64_t value);
    std::string p0_NominalPUSCH_ToString(uint32_t indent) const;
    std::string p0_NominalPUSCH_ToStringNoNewLines() const;
    int p0_NominalPUSCH_Clear();
    bool p0_NominalPUSCH_IsPresent() const;
private:
    bool p0_NominalPUSCH_present;
    int64_t p0_NominalPUSCH_internal_value;

    // alpha
public:
    enum alpha_Enum {
        k_alpha_al0 = 0,
        k_alpha_al04,
        k_alpha_al05,
        k_alpha_al06,
        k_alpha_al07,
        k_alpha_al08,
        k_alpha_al09,
        k_alpha_al1,
    };
    int alpha_Pack(std::vector<uint8_t> &bits);
    int alpha_Unpack(std::vector<uint8_t> bits);
    int alpha_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    alpha_Enum alpha_Value() const;
    int alpha_SetValue(alpha_Enum value);
    int alpha_SetValue(std::string value);
    std::string alpha_ValueToString(alpha_Enum value) const;
    uint64_t alpha_NumberOfValues() const;
    std::string alpha_ToString(uint32_t indent) const;
    std::string alpha_ToStringNoNewLines() const;
    int alpha_Clear();
    bool alpha_IsPresent() const;
private:
    bool alpha_present;
    alpha_Enum alpha_internal_value;

    // p0-NominalPUCCH
public:
    int p0_NominalPUCCH_Pack(std::vector<uint8_t> &bits);
    int p0_NominalPUCCH_Unpack(std::vector<uint8_t> bits);
    int p0_NominalPUCCH_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t p0_NominalPUCCH_Value() const;
    int p0_NominalPUCCH_SetValue(int64_t value);
    std::string p0_NominalPUCCH_ToString(uint32_t indent) const;
    std::string p0_NominalPUCCH_ToStringNoNewLines() const;
    int p0_NominalPUCCH_Clear();
    bool p0_NominalPUCCH_IsPresent() const;
private:
    bool p0_NominalPUCCH_present;
    int64_t p0_NominalPUCCH_internal_value;

    // deltaFList-PUCCH
public:
    DeltaFList_PUCCH* deltaFList_PUCCH_Set();
    int deltaFList_PUCCH_Set(DeltaFList_PUCCH &value);
    const DeltaFList_PUCCH& deltaFList_PUCCH_Get() const;
    std::string deltaFList_PUCCH_ToString(uint32_t indent) const;
    std::string deltaFList_PUCCH_ToStringNoNewLines() const;
    int deltaFList_PUCCH_Clear();
    bool deltaFList_PUCCH_IsPresent() const;
private:
    bool deltaFList_PUCCH_present;
    DeltaFList_PUCCH deltaFList_PUCCH;

    // deltaPreambleMsg3
public:
    int deltaPreambleMsg3_Pack(std::vector<uint8_t> &bits);
    int deltaPreambleMsg3_Unpack(std::vector<uint8_t> bits);
    int deltaPreambleMsg3_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t deltaPreambleMsg3_Value() const;
    int deltaPreambleMsg3_SetValue(int64_t value);
    std::string deltaPreambleMsg3_ToString(uint32_t indent) const;
    std::string deltaPreambleMsg3_ToStringNoNewLines() const;
    int deltaPreambleMsg3_Clear();
    bool deltaPreambleMsg3_IsPresent() const;
private:
    bool deltaPreambleMsg3_present;
    int64_t deltaPreambleMsg3_internal_value;

};

#endif
