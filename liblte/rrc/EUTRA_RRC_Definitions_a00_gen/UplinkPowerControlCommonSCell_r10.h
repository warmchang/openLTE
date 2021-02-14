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

#ifndef __UplinkPowerControlCommonSCell_r10_H__
#define __UplinkPowerControlCommonSCell_r10_H__

#include <array>
#include <cstdint>
#include <vector>

class UplinkPowerControlCommonSCell_r10
{
public:
    UplinkPowerControlCommonSCell_r10() : p0_NominalPUSCH_r10_present{false}, alpha_r10_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // p0-NominalPUSCH-r10
public:
    int p0_NominalPUSCH_r10_Pack(std::vector<uint8_t> &bits);
    int p0_NominalPUSCH_r10_Unpack(std::vector<uint8_t> bits);
    int p0_NominalPUSCH_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t p0_NominalPUSCH_r10_Value() const;
    int p0_NominalPUSCH_r10_SetValue(int64_t value);
    std::string p0_NominalPUSCH_r10_ToString(uint32_t indent) const;
    std::string p0_NominalPUSCH_r10_ToStringNoNewLines() const;
    int p0_NominalPUSCH_r10_Clear();
    bool p0_NominalPUSCH_r10_IsPresent() const;
private:
    bool p0_NominalPUSCH_r10_present;
    int64_t p0_NominalPUSCH_r10_internal_value;

    // alpha-r10
public:
    enum alpha_r10_Enum {
        k_alpha_r10_al0 = 0,
        k_alpha_r10_al04,
        k_alpha_r10_al05,
        k_alpha_r10_al06,
        k_alpha_r10_al07,
        k_alpha_r10_al08,
        k_alpha_r10_al09,
        k_alpha_r10_al1,
    };
    int alpha_r10_Pack(std::vector<uint8_t> &bits);
    int alpha_r10_Unpack(std::vector<uint8_t> bits);
    int alpha_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    alpha_r10_Enum alpha_r10_Value() const;
    int alpha_r10_SetValue(alpha_r10_Enum value);
    int alpha_r10_SetValue(std::string value);
    std::string alpha_r10_ValueToString(alpha_r10_Enum value) const;
    uint64_t alpha_r10_NumberOfValues() const;
    std::string alpha_r10_ToString(uint32_t indent) const;
    std::string alpha_r10_ToStringNoNewLines() const;
    int alpha_r10_Clear();
    bool alpha_r10_IsPresent() const;
private:
    bool alpha_r10_present;
    alpha_r10_Enum alpha_r10_internal_value;

};

#endif
