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

#ifndef __IRAT_ParametersGERAN_v920_H__
#define __IRAT_ParametersGERAN_v920_H__

#include <array>
#include <cstdint>
#include <vector>

class IRAT_ParametersGERAN_v920
{
public:
    IRAT_ParametersGERAN_v920() : dtm_r9_present{false}, e_RedirectionGERAN_r9_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // dtm-r9
public:
    enum dtm_r9_Enum {
        k_dtm_r9_supported = 0,
    };
    int dtm_r9_Pack(std::vector<uint8_t> &bits);
    int dtm_r9_Unpack(std::vector<uint8_t> bits);
    int dtm_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    dtm_r9_Enum dtm_r9_Value() const;
    int dtm_r9_SetValue(dtm_r9_Enum value);
    int dtm_r9_SetValue(std::string value);
    std::string dtm_r9_ValueToString(dtm_r9_Enum value) const;
    uint64_t dtm_r9_NumberOfValues() const;
    std::string dtm_r9_ToString(uint32_t indent) const;
    std::string dtm_r9_ToStringNoNewLines() const;
    int dtm_r9_Clear();
    bool dtm_r9_IsPresent() const;
private:
    bool dtm_r9_present;
    dtm_r9_Enum dtm_r9_internal_value;

    // e-RedirectionGERAN-r9
public:
    enum e_RedirectionGERAN_r9_Enum {
        k_e_RedirectionGERAN_r9_supported = 0,
    };
    int e_RedirectionGERAN_r9_Pack(std::vector<uint8_t> &bits);
    int e_RedirectionGERAN_r9_Unpack(std::vector<uint8_t> bits);
    int e_RedirectionGERAN_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    e_RedirectionGERAN_r9_Enum e_RedirectionGERAN_r9_Value() const;
    int e_RedirectionGERAN_r9_SetValue(e_RedirectionGERAN_r9_Enum value);
    int e_RedirectionGERAN_r9_SetValue(std::string value);
    std::string e_RedirectionGERAN_r9_ValueToString(e_RedirectionGERAN_r9_Enum value) const;
    uint64_t e_RedirectionGERAN_r9_NumberOfValues() const;
    std::string e_RedirectionGERAN_r9_ToString(uint32_t indent) const;
    std::string e_RedirectionGERAN_r9_ToStringNoNewLines() const;
    int e_RedirectionGERAN_r9_Clear();
    bool e_RedirectionGERAN_r9_IsPresent() const;
private:
    bool e_RedirectionGERAN_r9_present;
    e_RedirectionGERAN_r9_Enum e_RedirectionGERAN_r9_internal_value;

};

#endif
