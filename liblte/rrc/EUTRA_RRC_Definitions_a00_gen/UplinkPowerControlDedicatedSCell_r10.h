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

#ifndef __UplinkPowerControlDedicatedSCell_r10_H__
#define __UplinkPowerControlDedicatedSCell_r10_H__

#include "FilterCoefficient.h"

#include <array>
#include <cstdint>
#include <vector>

class UplinkPowerControlDedicatedSCell_r10
{
public:
    UplinkPowerControlDedicatedSCell_r10() : p0_UE_PUSCH_r10_present{false}, deltaMCS_Enabled_r10_present{false}, accumulationEnabled_r10_present{false}, pSRS_Offset_r10_present{false}, filterCoefficient_r10_present{false}, pathlossReference_r10_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // p0-UE-PUSCH-r10
public:
    int p0_UE_PUSCH_r10_Pack(std::vector<uint8_t> &bits);
    int p0_UE_PUSCH_r10_Unpack(std::vector<uint8_t> bits);
    int p0_UE_PUSCH_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t p0_UE_PUSCH_r10_Value() const;
    int p0_UE_PUSCH_r10_SetValue(int64_t value);
    std::string p0_UE_PUSCH_r10_ToString(uint32_t indent) const;
    std::string p0_UE_PUSCH_r10_ToStringNoNewLines() const;
    int p0_UE_PUSCH_r10_Clear();
    bool p0_UE_PUSCH_r10_IsPresent() const;
private:
    bool p0_UE_PUSCH_r10_present;
    int64_t p0_UE_PUSCH_r10_internal_value;

    // deltaMCS-Enabled-r10
public:
    enum deltaMCS_Enabled_r10_Enum {
        k_deltaMCS_Enabled_r10_en0 = 0,
        k_deltaMCS_Enabled_r10_en1,
    };
    int deltaMCS_Enabled_r10_Pack(std::vector<uint8_t> &bits);
    int deltaMCS_Enabled_r10_Unpack(std::vector<uint8_t> bits);
    int deltaMCS_Enabled_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    deltaMCS_Enabled_r10_Enum deltaMCS_Enabled_r10_Value() const;
    int deltaMCS_Enabled_r10_SetValue(deltaMCS_Enabled_r10_Enum value);
    int deltaMCS_Enabled_r10_SetValue(std::string value);
    std::string deltaMCS_Enabled_r10_ValueToString(deltaMCS_Enabled_r10_Enum value) const;
    uint64_t deltaMCS_Enabled_r10_NumberOfValues() const;
    std::string deltaMCS_Enabled_r10_ToString(uint32_t indent) const;
    std::string deltaMCS_Enabled_r10_ToStringNoNewLines() const;
    int deltaMCS_Enabled_r10_Clear();
    bool deltaMCS_Enabled_r10_IsPresent() const;
private:
    bool deltaMCS_Enabled_r10_present;
    deltaMCS_Enabled_r10_Enum deltaMCS_Enabled_r10_internal_value;

    // accumulationEnabled-r10
public:
    int accumulationEnabled_r10_Pack(std::vector<uint8_t> &bits);
    int accumulationEnabled_r10_Unpack(std::vector<uint8_t> bits);
    int accumulationEnabled_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    bool accumulationEnabled_r10_Value() const;
    int accumulationEnabled_r10_SetValue(bool value);
    std::string accumulationEnabled_r10_ToString(uint32_t indent) const;
    std::string accumulationEnabled_r10_ToStringNoNewLines() const;
    int accumulationEnabled_r10_Clear();
    bool accumulationEnabled_r10_IsPresent() const;
private:
    bool accumulationEnabled_r10_present;
    bool accumulationEnabled_r10_internal_value;

    // pSRS-Offset-r10
public:
    int pSRS_Offset_r10_Pack(std::vector<uint8_t> &bits);
    int pSRS_Offset_r10_Unpack(std::vector<uint8_t> bits);
    int pSRS_Offset_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t pSRS_Offset_r10_Value() const;
    int pSRS_Offset_r10_SetValue(int64_t value);
    std::string pSRS_Offset_r10_ToString(uint32_t indent) const;
    std::string pSRS_Offset_r10_ToStringNoNewLines() const;
    int pSRS_Offset_r10_Clear();
    bool pSRS_Offset_r10_IsPresent() const;
private:
    bool pSRS_Offset_r10_present;
    int64_t pSRS_Offset_r10_internal_value;

    // filterCoefficient-r10
public:
    FilterCoefficient* filterCoefficient_r10_Set();
    int filterCoefficient_r10_Set(FilterCoefficient &value);
    const FilterCoefficient& filterCoefficient_r10_Get() const;
    FilterCoefficient::Enum filterCoefficient_r10_GetDefault() const;
    std::string filterCoefficient_r10_ToString(uint32_t indent) const;
    std::string filterCoefficient_r10_ToStringNoNewLines() const;
    int filterCoefficient_r10_Clear();
    bool filterCoefficient_r10_IsPresent() const;
private:
    bool filterCoefficient_r10_present;
    FilterCoefficient filterCoefficient_r10;

    // pathlossReference-r10
public:
    enum pathlossReference_r10_Enum {
        k_pathlossReference_r10_pCell = 0,
        k_pathlossReference_r10_sCell,
    };
    int pathlossReference_r10_Pack(std::vector<uint8_t> &bits);
    int pathlossReference_r10_Unpack(std::vector<uint8_t> bits);
    int pathlossReference_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    pathlossReference_r10_Enum pathlossReference_r10_Value() const;
    int pathlossReference_r10_SetValue(pathlossReference_r10_Enum value);
    int pathlossReference_r10_SetValue(std::string value);
    std::string pathlossReference_r10_ValueToString(pathlossReference_r10_Enum value) const;
    uint64_t pathlossReference_r10_NumberOfValues() const;
    std::string pathlossReference_r10_ToString(uint32_t indent) const;
    std::string pathlossReference_r10_ToStringNoNewLines() const;
    int pathlossReference_r10_Clear();
    bool pathlossReference_r10_IsPresent() const;
private:
    bool pathlossReference_r10_present;
    pathlossReference_r10_Enum pathlossReference_r10_internal_value;

};

#endif
