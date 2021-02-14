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

#ifndef __PDSCH_ConfigDedicated_H__
#define __PDSCH_ConfigDedicated_H__

#include <array>
#include <cstdint>
#include <vector>

class PDSCH_ConfigDedicated
{
public:
    PDSCH_ConfigDedicated() : p_a_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // p-a
public:
    enum p_a_Enum {
        k_p_a_dB_6 = 0,
        k_p_a_dB_4dot77,
        k_p_a_dB_3,
        k_p_a_dB_1dot77,
        k_p_a_dB0,
        k_p_a_dB1,
        k_p_a_dB2,
        k_p_a_dB3,
    };
    int p_a_Pack(std::vector<uint8_t> &bits);
    int p_a_Unpack(std::vector<uint8_t> bits);
    int p_a_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    p_a_Enum p_a_Value() const;
    int p_a_SetValue(p_a_Enum value);
    int p_a_SetValue(std::string value);
    std::string p_a_ValueToString(p_a_Enum value) const;
    uint64_t p_a_NumberOfValues() const;
    std::string p_a_ToString(uint32_t indent) const;
    std::string p_a_ToStringNoNewLines() const;
    int p_a_Clear();
    bool p_a_IsPresent() const;
private:
    bool p_a_present;
    p_a_Enum p_a_internal_value;

};

#endif
