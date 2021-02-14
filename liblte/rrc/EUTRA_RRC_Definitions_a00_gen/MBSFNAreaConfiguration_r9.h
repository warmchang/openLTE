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

#ifndef __MBSFNAreaConfiguration_r9_H__
#define __MBSFNAreaConfiguration_r9_H__

#include "CommonSF_AllocPatternList_r9.h"
#include "PMCH_InfoList_r9.h"
#include "MBSFNAreaConfiguration_v930_IEs.h"

#include <array>
#include <cstdint>
#include <vector>

class MBSFNAreaConfiguration_r9
{
public:
    MBSFNAreaConfiguration_r9() : commonSF_Alloc_r9_present{false}, commonSF_AllocPeriod_r9_present{false}, pmch_InfoList_r9_present{false}, nonCriticalExtension_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // commonSF-Alloc-r9
public:
    CommonSF_AllocPatternList_r9* commonSF_Alloc_r9_Set();
    int commonSF_Alloc_r9_Set(CommonSF_AllocPatternList_r9 &value);
    const CommonSF_AllocPatternList_r9& commonSF_Alloc_r9_Get() const;
    std::string commonSF_Alloc_r9_ToString(uint32_t indent) const;
    std::string commonSF_Alloc_r9_ToStringNoNewLines() const;
    int commonSF_Alloc_r9_Clear();
    bool commonSF_Alloc_r9_IsPresent() const;
private:
    bool commonSF_Alloc_r9_present;
    CommonSF_AllocPatternList_r9 commonSF_Alloc_r9;

    // commonSF-AllocPeriod-r9
public:
    enum commonSF_AllocPeriod_r9_Enum {
        k_commonSF_AllocPeriod_r9_rf4 = 0,
        k_commonSF_AllocPeriod_r9_rf8,
        k_commonSF_AllocPeriod_r9_rf16,
        k_commonSF_AllocPeriod_r9_rf32,
        k_commonSF_AllocPeriod_r9_rf64,
        k_commonSF_AllocPeriod_r9_rf128,
        k_commonSF_AllocPeriod_r9_rf256,
    };
    int commonSF_AllocPeriod_r9_Pack(std::vector<uint8_t> &bits);
    int commonSF_AllocPeriod_r9_Unpack(std::vector<uint8_t> bits);
    int commonSF_AllocPeriod_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    commonSF_AllocPeriod_r9_Enum commonSF_AllocPeriod_r9_Value() const;
    int commonSF_AllocPeriod_r9_SetValue(commonSF_AllocPeriod_r9_Enum value);
    int commonSF_AllocPeriod_r9_SetValue(std::string value);
    std::string commonSF_AllocPeriod_r9_ValueToString(commonSF_AllocPeriod_r9_Enum value) const;
    uint64_t commonSF_AllocPeriod_r9_NumberOfValues() const;
    std::string commonSF_AllocPeriod_r9_ToString(uint32_t indent) const;
    std::string commonSF_AllocPeriod_r9_ToStringNoNewLines() const;
    int commonSF_AllocPeriod_r9_Clear();
    bool commonSF_AllocPeriod_r9_IsPresent() const;
private:
    bool commonSF_AllocPeriod_r9_present;
    commonSF_AllocPeriod_r9_Enum commonSF_AllocPeriod_r9_internal_value;

    // pmch-InfoList-r9
public:
    PMCH_InfoList_r9* pmch_InfoList_r9_Set();
    int pmch_InfoList_r9_Set(PMCH_InfoList_r9 &value);
    const PMCH_InfoList_r9& pmch_InfoList_r9_Get() const;
    std::string pmch_InfoList_r9_ToString(uint32_t indent) const;
    std::string pmch_InfoList_r9_ToStringNoNewLines() const;
    int pmch_InfoList_r9_Clear();
    bool pmch_InfoList_r9_IsPresent() const;
private:
    bool pmch_InfoList_r9_present;
    PMCH_InfoList_r9 pmch_InfoList_r9;

    // nonCriticalExtension
public:
    MBSFNAreaConfiguration_v930_IEs* nonCriticalExtension_Set();
    int nonCriticalExtension_Set(MBSFNAreaConfiguration_v930_IEs &value);
    const MBSFNAreaConfiguration_v930_IEs& nonCriticalExtension_Get() const;
    std::string nonCriticalExtension_ToString(uint32_t indent) const;
    std::string nonCriticalExtension_ToStringNoNewLines() const;
    int nonCriticalExtension_Clear();
    bool nonCriticalExtension_IsPresent() const;
private:
    bool nonCriticalExtension_present;
    MBSFNAreaConfiguration_v930_IEs nonCriticalExtension;

};

#endif
