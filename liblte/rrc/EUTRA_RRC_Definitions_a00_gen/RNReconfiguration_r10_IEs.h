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

#ifndef __RNReconfiguration_r10_IEs_H__
#define __RNReconfiguration_r10_IEs_H__

#include "SystemInfoChange_r10.h"
#include "RN_SubframeConfig_r10.h"

#include <array>
#include <cstdint>
#include <vector>

class RNReconfiguration_r10_IEs
{
public:
    RNReconfiguration_r10_IEs() : systemInfoChange_r10_present{false}, rn_SubframeConfig_r10_present{false}, lateNonCriticalExtension_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // systemInfoChange-r10
public:
    SystemInfoChange_r10* systemInfoChange_r10_Set();
    int systemInfoChange_r10_Set(SystemInfoChange_r10 &value);
    const SystemInfoChange_r10& systemInfoChange_r10_Get() const;
    std::string systemInfoChange_r10_ToString(uint32_t indent) const;
    std::string systemInfoChange_r10_ToStringNoNewLines() const;
    int systemInfoChange_r10_Clear();
    bool systemInfoChange_r10_IsPresent() const;
private:
    bool systemInfoChange_r10_present;
    SystemInfoChange_r10 systemInfoChange_r10;

    // rn-SubframeConfig-r10
public:
    RN_SubframeConfig_r10* rn_SubframeConfig_r10_Set();
    int rn_SubframeConfig_r10_Set(RN_SubframeConfig_r10 &value);
    const RN_SubframeConfig_r10& rn_SubframeConfig_r10_Get() const;
    std::string rn_SubframeConfig_r10_ToString(uint32_t indent) const;
    std::string rn_SubframeConfig_r10_ToStringNoNewLines() const;
    int rn_SubframeConfig_r10_Clear();
    bool rn_SubframeConfig_r10_IsPresent() const;
private:
    bool rn_SubframeConfig_r10_present;
    RN_SubframeConfig_r10 rn_SubframeConfig_r10;

    // lateNonCriticalExtension
public:
    int lateNonCriticalExtension_Pack(std::vector<uint8_t> &bits);
    int lateNonCriticalExtension_Unpack(std::vector<uint8_t> bits);
    int lateNonCriticalExtension_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::vector<uint8_t> lateNonCriticalExtension_Value() const;
    int lateNonCriticalExtension_SetValue(std::vector<uint8_t> value);
    std::string lateNonCriticalExtension_ToString(uint32_t indent) const;
    std::string lateNonCriticalExtension_ToStringNoNewLines() const;
    int lateNonCriticalExtension_Clear();
    bool lateNonCriticalExtension_IsPresent() const;
private:
    bool lateNonCriticalExtension_present;
    std::vector<uint8_t> lateNonCriticalExtension_internal_value;

    // nonCriticalExtension

};

#endif
