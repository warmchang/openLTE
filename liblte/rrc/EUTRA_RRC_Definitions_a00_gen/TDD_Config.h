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

#ifndef __TDD_Config_H__
#define __TDD_Config_H__

#include <array>
#include <cstdint>
#include <vector>

class TDD_Config
{
public:
    TDD_Config() : subframeAssignment_present{false}, specialSubframePatterns_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // subframeAssignment
public:
    enum subframeAssignment_Enum {
        k_subframeAssignment_sa0 = 0,
        k_subframeAssignment_sa1,
        k_subframeAssignment_sa2,
        k_subframeAssignment_sa3,
        k_subframeAssignment_sa4,
        k_subframeAssignment_sa5,
        k_subframeAssignment_sa6,
    };
    int subframeAssignment_Pack(std::vector<uint8_t> &bits);
    int subframeAssignment_Unpack(std::vector<uint8_t> bits);
    int subframeAssignment_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    subframeAssignment_Enum subframeAssignment_Value() const;
    int subframeAssignment_SetValue(subframeAssignment_Enum value);
    int subframeAssignment_SetValue(std::string value);
    std::string subframeAssignment_ValueToString(subframeAssignment_Enum value) const;
    uint64_t subframeAssignment_NumberOfValues() const;
    std::string subframeAssignment_ToString(uint32_t indent) const;
    std::string subframeAssignment_ToStringNoNewLines() const;
    int subframeAssignment_Clear();
    bool subframeAssignment_IsPresent() const;
private:
    bool subframeAssignment_present;
    subframeAssignment_Enum subframeAssignment_internal_value;

    // specialSubframePatterns
public:
    enum specialSubframePatterns_Enum {
        k_specialSubframePatterns_ssp0 = 0,
        k_specialSubframePatterns_ssp1,
        k_specialSubframePatterns_ssp2,
        k_specialSubframePatterns_ssp3,
        k_specialSubframePatterns_ssp4,
        k_specialSubframePatterns_ssp5,
        k_specialSubframePatterns_ssp6,
        k_specialSubframePatterns_ssp7,
        k_specialSubframePatterns_ssp8,
    };
    int specialSubframePatterns_Pack(std::vector<uint8_t> &bits);
    int specialSubframePatterns_Unpack(std::vector<uint8_t> bits);
    int specialSubframePatterns_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    specialSubframePatterns_Enum specialSubframePatterns_Value() const;
    int specialSubframePatterns_SetValue(specialSubframePatterns_Enum value);
    int specialSubframePatterns_SetValue(std::string value);
    std::string specialSubframePatterns_ValueToString(specialSubframePatterns_Enum value) const;
    uint64_t specialSubframePatterns_NumberOfValues() const;
    std::string specialSubframePatterns_ToString(uint32_t indent) const;
    std::string specialSubframePatterns_ToStringNoNewLines() const;
    int specialSubframePatterns_Clear();
    bool specialSubframePatterns_IsPresent() const;
private:
    bool specialSubframePatterns_present;
    specialSubframePatterns_Enum specialSubframePatterns_internal_value;

};

#endif
