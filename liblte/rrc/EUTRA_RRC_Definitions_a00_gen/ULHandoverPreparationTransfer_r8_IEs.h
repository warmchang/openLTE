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

#ifndef __ULHandoverPreparationTransfer_r8_IEs_H__
#define __ULHandoverPreparationTransfer_r8_IEs_H__

#include "CDMA2000_Type.h"
#include "DedicatedInfoCDMA2000.h"
#include "ULHandoverPreparationTransfer_v8a0_IEs.h"

#include <array>
#include <cstdint>
#include <vector>

class ULHandoverPreparationTransfer_r8_IEs
{
public:
    ULHandoverPreparationTransfer_r8_IEs() : cdma2000_Type_present{false}, meid_present{false}, dedicatedInfo_present{false}, nonCriticalExtension_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // cdma2000-Type
public:
    CDMA2000_Type* cdma2000_Type_Set();
    int cdma2000_Type_Set(CDMA2000_Type &value);
    const CDMA2000_Type& cdma2000_Type_Get() const;
    std::string cdma2000_Type_ToString(uint32_t indent) const;
    std::string cdma2000_Type_ToStringNoNewLines() const;
    int cdma2000_Type_Clear();
    bool cdma2000_Type_IsPresent() const;
private:
    bool cdma2000_Type_present;
    CDMA2000_Type cdma2000_Type;

    // meid
public:
    int meid_Pack(std::vector<uint8_t> &bits);
    int meid_Unpack(std::vector<uint8_t> bits);
    int meid_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    uint64_t meid_Value() const;
    int meid_SetValue(uint64_t value);
    std::string meid_ToString(uint32_t indent) const;
    std::string meid_ToStringNoNewLines() const;
    int meid_Clear();
    bool meid_IsPresent() const;
private:
    bool meid_present;
    uint64_t meid_internal_value;

    // dedicatedInfo
public:
    DedicatedInfoCDMA2000* dedicatedInfo_Set();
    int dedicatedInfo_Set(DedicatedInfoCDMA2000 &value);
    const DedicatedInfoCDMA2000& dedicatedInfo_Get() const;
    std::string dedicatedInfo_ToString(uint32_t indent) const;
    std::string dedicatedInfo_ToStringNoNewLines() const;
    int dedicatedInfo_Clear();
    bool dedicatedInfo_IsPresent() const;
private:
    bool dedicatedInfo_present;
    DedicatedInfoCDMA2000 dedicatedInfo;

    // nonCriticalExtension
public:
    ULHandoverPreparationTransfer_v8a0_IEs* nonCriticalExtension_Set();
    int nonCriticalExtension_Set(ULHandoverPreparationTransfer_v8a0_IEs &value);
    const ULHandoverPreparationTransfer_v8a0_IEs& nonCriticalExtension_Get() const;
    std::string nonCriticalExtension_ToString(uint32_t indent) const;
    std::string nonCriticalExtension_ToStringNoNewLines() const;
    int nonCriticalExtension_Clear();
    bool nonCriticalExtension_IsPresent() const;
private:
    bool nonCriticalExtension_present;
    ULHandoverPreparationTransfer_v8a0_IEs nonCriticalExtension;

};

#endif
