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

#ifndef __DRB_CountInfo_H__
#define __DRB_CountInfo_H__

#include "DRB_Identity.h"

#include <array>
#include <cstdint>
#include <vector>

class DRB_CountInfo
{
public:
    DRB_CountInfo() : drb_Identity_present{false}, count_Uplink_present{false}, count_Downlink_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // drb-Identity
public:
    DRB_Identity* drb_Identity_Set();
    int drb_Identity_Set(DRB_Identity &value);
    const DRB_Identity& drb_Identity_Get() const;
    std::string drb_Identity_ToString(uint32_t indent) const;
    std::string drb_Identity_ToStringNoNewLines() const;
    int drb_Identity_Clear();
    bool drb_Identity_IsPresent() const;
private:
    bool drb_Identity_present;
    DRB_Identity drb_Identity;

    // count-Uplink
public:
    int count_Uplink_Pack(std::vector<uint8_t> &bits);
    int count_Uplink_Unpack(std::vector<uint8_t> bits);
    int count_Uplink_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t count_Uplink_Value() const;
    int count_Uplink_SetValue(int64_t value);
    std::string count_Uplink_ToString(uint32_t indent) const;
    std::string count_Uplink_ToStringNoNewLines() const;
    int count_Uplink_Clear();
    bool count_Uplink_IsPresent() const;
private:
    bool count_Uplink_present;
    int64_t count_Uplink_internal_value;

    // count-Downlink
public:
    int count_Downlink_Pack(std::vector<uint8_t> &bits);
    int count_Downlink_Unpack(std::vector<uint8_t> bits);
    int count_Downlink_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t count_Downlink_Value() const;
    int count_Downlink_SetValue(int64_t value);
    std::string count_Downlink_ToString(uint32_t indent) const;
    std::string count_Downlink_ToStringNoNewLines() const;
    int count_Downlink_Clear();
    bool count_Downlink_IsPresent() const;
private:
    bool count_Downlink_present;
    int64_t count_Downlink_internal_value;

};

#endif
