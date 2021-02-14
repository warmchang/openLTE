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

#ifndef __PMCH_Info_r9_H__
#define __PMCH_Info_r9_H__

#include "PMCH_Config_r9.h"
#include "MBMS_SessionInfoList_r9.h"

#include <array>
#include <cstdint>
#include <vector>

class PMCH_Info_r9
{
public:
    PMCH_Info_r9() : pmch_Config_r9_present{false}, mbms_SessionInfoList_r9_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // pmch-Config-r9
public:
    PMCH_Config_r9* pmch_Config_r9_Set();
    int pmch_Config_r9_Set(PMCH_Config_r9 &value);
    const PMCH_Config_r9& pmch_Config_r9_Get() const;
    std::string pmch_Config_r9_ToString(uint32_t indent) const;
    std::string pmch_Config_r9_ToStringNoNewLines() const;
    int pmch_Config_r9_Clear();
    bool pmch_Config_r9_IsPresent() const;
private:
    bool pmch_Config_r9_present;
    PMCH_Config_r9 pmch_Config_r9;

    // mbms-SessionInfoList-r9
public:
    MBMS_SessionInfoList_r9* mbms_SessionInfoList_r9_Set();
    int mbms_SessionInfoList_r9_Set(MBMS_SessionInfoList_r9 &value);
    const MBMS_SessionInfoList_r9& mbms_SessionInfoList_r9_Get() const;
    std::string mbms_SessionInfoList_r9_ToString(uint32_t indent) const;
    std::string mbms_SessionInfoList_r9_ToStringNoNewLines() const;
    int mbms_SessionInfoList_r9_Clear();
    bool mbms_SessionInfoList_r9_IsPresent() const;
private:
    bool mbms_SessionInfoList_r9_present;
    MBMS_SessionInfoList_r9 mbms_SessionInfoList_r9;

};

#endif
