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

#ifndef __SpeedStateScaleFactors_H__
#define __SpeedStateScaleFactors_H__

#include <array>
#include <cstdint>
#include <vector>

class SpeedStateScaleFactors
{
public:
    SpeedStateScaleFactors() : sf_Medium_present{false}, sf_High_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // sf-Medium
public:
    enum sf_Medium_Enum {
        k_sf_Medium_oDot25 = 0,
        k_sf_Medium_oDot5,
        k_sf_Medium_oDot75,
        k_sf_Medium_lDot0,
    };
    int sf_Medium_Pack(std::vector<uint8_t> &bits);
    int sf_Medium_Unpack(std::vector<uint8_t> bits);
    int sf_Medium_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    sf_Medium_Enum sf_Medium_Value() const;
    int sf_Medium_SetValue(sf_Medium_Enum value);
    int sf_Medium_SetValue(std::string value);
    std::string sf_Medium_ValueToString(sf_Medium_Enum value) const;
    uint64_t sf_Medium_NumberOfValues() const;
    std::string sf_Medium_ToString(uint32_t indent) const;
    std::string sf_Medium_ToStringNoNewLines() const;
    int sf_Medium_Clear();
    bool sf_Medium_IsPresent() const;
private:
    bool sf_Medium_present;
    sf_Medium_Enum sf_Medium_internal_value;

    // sf-High
public:
    enum sf_High_Enum {
        k_sf_High_oDot25 = 0,
        k_sf_High_oDot5,
        k_sf_High_oDot75,
        k_sf_High_lDot0,
    };
    int sf_High_Pack(std::vector<uint8_t> &bits);
    int sf_High_Unpack(std::vector<uint8_t> bits);
    int sf_High_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    sf_High_Enum sf_High_Value() const;
    int sf_High_SetValue(sf_High_Enum value);
    int sf_High_SetValue(std::string value);
    std::string sf_High_ValueToString(sf_High_Enum value) const;
    uint64_t sf_High_NumberOfValues() const;
    std::string sf_High_ToString(uint32_t indent) const;
    std::string sf_High_ToStringNoNewLines() const;
    int sf_High_Clear();
    bool sf_High_IsPresent() const;
private:
    bool sf_High_present;
    sf_High_Enum sf_High_internal_value;

};

#endif
