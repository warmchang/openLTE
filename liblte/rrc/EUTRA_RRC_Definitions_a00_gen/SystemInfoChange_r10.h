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

#ifndef __SystemInfoChange_r10_H__
#define __SystemInfoChange_r10_H__

#include "SystemInformationBlockType2.h"

#include <array>
#include <cstdint>
#include <vector>

class SystemInfoChange_r10
{
public:
    SystemInfoChange_r10() : systemInformationBlockType1_r10_present{false}, systemInformationBlockType2_r10_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // systemInformationBlockType1-r10
public:
    int systemInformationBlockType1_r10_Pack(std::vector<uint8_t> &bits);
    int systemInformationBlockType1_r10_Unpack(std::vector<uint8_t> bits);
    int systemInformationBlockType1_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::vector<uint8_t> systemInformationBlockType1_r10_Value() const;
    int systemInformationBlockType1_r10_SetValue(std::vector<uint8_t> value);
    std::string systemInformationBlockType1_r10_ToString(uint32_t indent) const;
    std::string systemInformationBlockType1_r10_ToStringNoNewLines() const;
    int systemInformationBlockType1_r10_Clear();
    bool systemInformationBlockType1_r10_IsPresent() const;
private:
    bool systemInformationBlockType1_r10_present;
    std::vector<uint8_t> systemInformationBlockType1_r10_internal_value;

    // systemInformationBlockType2-r10
public:
    SystemInformationBlockType2* systemInformationBlockType2_r10_Set();
    int systemInformationBlockType2_r10_Set(SystemInformationBlockType2 &value);
    const SystemInformationBlockType2& systemInformationBlockType2_r10_Get() const;
    std::string systemInformationBlockType2_r10_ToString(uint32_t indent) const;
    std::string systemInformationBlockType2_r10_ToStringNoNewLines() const;
    int systemInformationBlockType2_r10_Clear();
    bool systemInformationBlockType2_r10_IsPresent() const;
private:
    bool systemInformationBlockType2_r10_present;
    SystemInformationBlockType2 systemInformationBlockType2_r10;

};

#endif
