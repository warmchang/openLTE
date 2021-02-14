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

#ifndef __UE_CapabilityRAT_Container_H__
#define __UE_CapabilityRAT_Container_H__

#include "RAT_Type.h"

#include <array>
#include <cstdint>
#include <vector>

class UE_CapabilityRAT_Container
{
public:
    UE_CapabilityRAT_Container() : rat_Type_present{false}, ueCapabilityRAT_Container_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // rat-Type
public:
    RAT_Type* rat_Type_Set();
    int rat_Type_Set(RAT_Type &value);
    const RAT_Type& rat_Type_Get() const;
    std::string rat_Type_ToString(uint32_t indent) const;
    std::string rat_Type_ToStringNoNewLines() const;
    int rat_Type_Clear();
    bool rat_Type_IsPresent() const;
private:
    bool rat_Type_present;
    RAT_Type rat_Type;

    // ueCapabilityRAT-Container
public:
    int ueCapabilityRAT_Container_Pack(std::vector<uint8_t> &bits);
    int ueCapabilityRAT_Container_Unpack(std::vector<uint8_t> bits);
    int ueCapabilityRAT_Container_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::vector<uint8_t> ueCapabilityRAT_Container_Value() const;
    int ueCapabilityRAT_Container_SetValue(std::vector<uint8_t> value);
    std::string ueCapabilityRAT_Container_ToString(uint32_t indent) const;
    std::string ueCapabilityRAT_Container_ToStringNoNewLines() const;
    int ueCapabilityRAT_Container_Clear();
    bool ueCapabilityRAT_Container_IsPresent() const;
private:
    bool ueCapabilityRAT_Container_present;
    std::vector<uint8_t> ueCapabilityRAT_Container_internal_value;

};

#endif
