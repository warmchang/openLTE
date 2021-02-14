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

#ifndef __UplinkPowerControlDedicated_H__
#define __UplinkPowerControlDedicated_H__

#include "FilterCoefficient.h"

#include <array>
#include <cstdint>
#include <vector>

class UplinkPowerControlDedicated
{
public:
    UplinkPowerControlDedicated() : p0_UE_PUSCH_present{false}, deltaMCS_Enabled_present{false}, accumulationEnabled_present{false}, p0_UE_PUCCH_present{false}, pSRS_Offset_present{false}, filterCoefficient_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // p0-UE-PUSCH
public:
    int p0_UE_PUSCH_Pack(std::vector<uint8_t> &bits);
    int p0_UE_PUSCH_Unpack(std::vector<uint8_t> bits);
    int p0_UE_PUSCH_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t p0_UE_PUSCH_Value() const;
    int p0_UE_PUSCH_SetValue(int64_t value);
    std::string p0_UE_PUSCH_ToString(uint32_t indent) const;
    std::string p0_UE_PUSCH_ToStringNoNewLines() const;
    int p0_UE_PUSCH_Clear();
    bool p0_UE_PUSCH_IsPresent() const;
private:
    bool p0_UE_PUSCH_present;
    int64_t p0_UE_PUSCH_internal_value;

    // deltaMCS-Enabled
public:
    enum deltaMCS_Enabled_Enum {
        k_deltaMCS_Enabled_en0 = 0,
        k_deltaMCS_Enabled_en1,
    };
    int deltaMCS_Enabled_Pack(std::vector<uint8_t> &bits);
    int deltaMCS_Enabled_Unpack(std::vector<uint8_t> bits);
    int deltaMCS_Enabled_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    deltaMCS_Enabled_Enum deltaMCS_Enabled_Value() const;
    int deltaMCS_Enabled_SetValue(deltaMCS_Enabled_Enum value);
    int deltaMCS_Enabled_SetValue(std::string value);
    std::string deltaMCS_Enabled_ValueToString(deltaMCS_Enabled_Enum value) const;
    uint64_t deltaMCS_Enabled_NumberOfValues() const;
    std::string deltaMCS_Enabled_ToString(uint32_t indent) const;
    std::string deltaMCS_Enabled_ToStringNoNewLines() const;
    int deltaMCS_Enabled_Clear();
    bool deltaMCS_Enabled_IsPresent() const;
private:
    bool deltaMCS_Enabled_present;
    deltaMCS_Enabled_Enum deltaMCS_Enabled_internal_value;

    // accumulationEnabled
public:
    int accumulationEnabled_Pack(std::vector<uint8_t> &bits);
    int accumulationEnabled_Unpack(std::vector<uint8_t> bits);
    int accumulationEnabled_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    bool accumulationEnabled_Value() const;
    int accumulationEnabled_SetValue(bool value);
    std::string accumulationEnabled_ToString(uint32_t indent) const;
    std::string accumulationEnabled_ToStringNoNewLines() const;
    int accumulationEnabled_Clear();
    bool accumulationEnabled_IsPresent() const;
private:
    bool accumulationEnabled_present;
    bool accumulationEnabled_internal_value;

    // p0-UE-PUCCH
public:
    int p0_UE_PUCCH_Pack(std::vector<uint8_t> &bits);
    int p0_UE_PUCCH_Unpack(std::vector<uint8_t> bits);
    int p0_UE_PUCCH_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t p0_UE_PUCCH_Value() const;
    int p0_UE_PUCCH_SetValue(int64_t value);
    std::string p0_UE_PUCCH_ToString(uint32_t indent) const;
    std::string p0_UE_PUCCH_ToStringNoNewLines() const;
    int p0_UE_PUCCH_Clear();
    bool p0_UE_PUCCH_IsPresent() const;
private:
    bool p0_UE_PUCCH_present;
    int64_t p0_UE_PUCCH_internal_value;

    // pSRS-Offset
public:
    int pSRS_Offset_Pack(std::vector<uint8_t> &bits);
    int pSRS_Offset_Unpack(std::vector<uint8_t> bits);
    int pSRS_Offset_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t pSRS_Offset_Value() const;
    int pSRS_Offset_SetValue(int64_t value);
    std::string pSRS_Offset_ToString(uint32_t indent) const;
    std::string pSRS_Offset_ToStringNoNewLines() const;
    int pSRS_Offset_Clear();
    bool pSRS_Offset_IsPresent() const;
private:
    bool pSRS_Offset_present;
    int64_t pSRS_Offset_internal_value;

    // filterCoefficient
public:
    FilterCoefficient* filterCoefficient_Set();
    int filterCoefficient_Set(FilterCoefficient &value);
    const FilterCoefficient& filterCoefficient_Get() const;
    FilterCoefficient::Enum filterCoefficient_GetDefault() const;
    std::string filterCoefficient_ToString(uint32_t indent) const;
    std::string filterCoefficient_ToStringNoNewLines() const;
    int filterCoefficient_Clear();
    bool filterCoefficient_IsPresent() const;
private:
    bool filterCoefficient_present;
    FilterCoefficient filterCoefficient;

};

#endif
