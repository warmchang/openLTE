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

#ifndef __SystemInformationBlockType13_r9_H__
#define __SystemInformationBlockType13_r9_H__

#include "MBSFN_AreaInfoList_r9.h"
#include "MBMS_NotificationConfig_r9.h"

#include <array>
#include <cstdint>
#include <vector>

class SystemInformationBlockType13_r9
{
public:
    SystemInformationBlockType13_r9() : mbsfn_AreaInfoList_r9_present{false}, notificationConfig_r9_present{false}, lateNonCriticalExtension_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // mbsfn-AreaInfoList-r9
public:
    MBSFN_AreaInfoList_r9* mbsfn_AreaInfoList_r9_Set();
    int mbsfn_AreaInfoList_r9_Set(MBSFN_AreaInfoList_r9 &value);
    const MBSFN_AreaInfoList_r9& mbsfn_AreaInfoList_r9_Get() const;
    std::string mbsfn_AreaInfoList_r9_ToString(uint32_t indent) const;
    std::string mbsfn_AreaInfoList_r9_ToStringNoNewLines() const;
    int mbsfn_AreaInfoList_r9_Clear();
    bool mbsfn_AreaInfoList_r9_IsPresent() const;
private:
    bool mbsfn_AreaInfoList_r9_present;
    MBSFN_AreaInfoList_r9 mbsfn_AreaInfoList_r9;

    // notificationConfig-r9
public:
    MBMS_NotificationConfig_r9* notificationConfig_r9_Set();
    int notificationConfig_r9_Set(MBMS_NotificationConfig_r9 &value);
    const MBMS_NotificationConfig_r9& notificationConfig_r9_Get() const;
    std::string notificationConfig_r9_ToString(uint32_t indent) const;
    std::string notificationConfig_r9_ToStringNoNewLines() const;
    int notificationConfig_r9_Clear();
    bool notificationConfig_r9_IsPresent() const;
private:
    bool notificationConfig_r9_present;
    MBMS_NotificationConfig_r9 notificationConfig_r9;

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

};

#endif
