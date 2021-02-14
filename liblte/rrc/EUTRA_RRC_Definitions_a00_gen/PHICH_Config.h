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

#ifndef __PHICH_Config_H__
#define __PHICH_Config_H__

#include <array>
#include <cstdint>
#include <vector>

class PHICH_Config
{
public:
    PHICH_Config() : phich_Duration_present{false}, phich_Resource_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // phich-Duration
public:
    enum phich_Duration_Enum {
        k_phich_Duration_normal = 0,
        k_phich_Duration_extended,
    };
    int phich_Duration_Pack(std::vector<uint8_t> &bits);
    int phich_Duration_Unpack(std::vector<uint8_t> bits);
    int phich_Duration_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    phich_Duration_Enum phich_Duration_Value() const;
    int phich_Duration_SetValue(phich_Duration_Enum value);
    int phich_Duration_SetValue(std::string value);
    std::string phich_Duration_ValueToString(phich_Duration_Enum value) const;
    uint64_t phich_Duration_NumberOfValues() const;
    std::string phich_Duration_ToString(uint32_t indent) const;
    std::string phich_Duration_ToStringNoNewLines() const;
    int phich_Duration_Clear();
    bool phich_Duration_IsPresent() const;
private:
    bool phich_Duration_present;
    phich_Duration_Enum phich_Duration_internal_value;

    // phich-Resource
public:
    enum phich_Resource_Enum {
        k_phich_Resource_oneSixth = 0,
        k_phich_Resource_half,
        k_phich_Resource_one,
        k_phich_Resource_two,
    };
    int phich_Resource_Pack(std::vector<uint8_t> &bits);
    int phich_Resource_Unpack(std::vector<uint8_t> bits);
    int phich_Resource_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    phich_Resource_Enum phich_Resource_Value() const;
    int phich_Resource_SetValue(phich_Resource_Enum value);
    int phich_Resource_SetValue(std::string value);
    std::string phich_Resource_ValueToString(phich_Resource_Enum value) const;
    uint64_t phich_Resource_NumberOfValues() const;
    std::string phich_Resource_ToString(uint32_t indent) const;
    std::string phich_Resource_ToStringNoNewLines() const;
    int phich_Resource_Clear();
    bool phich_Resource_IsPresent() const;
private:
    bool phich_Resource_present;
    phich_Resource_Enum phich_Resource_internal_value;

};

#endif
