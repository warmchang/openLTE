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

#ifndef __IRAT_ParametersUTRA_v920_H__
#define __IRAT_ParametersUTRA_v920_H__

#include <array>
#include <cstdint>
#include <vector>

class IRAT_ParametersUTRA_v920
{
public:
    IRAT_ParametersUTRA_v920() : e_RedirectionUTRA_r9_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // e-RedirectionUTRA-r9
public:
    enum e_RedirectionUTRA_r9_Enum {
        k_e_RedirectionUTRA_r9_supported = 0,
    };
    int e_RedirectionUTRA_r9_Pack(std::vector<uint8_t> &bits);
    int e_RedirectionUTRA_r9_Unpack(std::vector<uint8_t> bits);
    int e_RedirectionUTRA_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    e_RedirectionUTRA_r9_Enum e_RedirectionUTRA_r9_Value() const;
    int e_RedirectionUTRA_r9_SetValue(e_RedirectionUTRA_r9_Enum value);
    int e_RedirectionUTRA_r9_SetValue(std::string value);
    std::string e_RedirectionUTRA_r9_ValueToString(e_RedirectionUTRA_r9_Enum value) const;
    uint64_t e_RedirectionUTRA_r9_NumberOfValues() const;
    std::string e_RedirectionUTRA_r9_ToString(uint32_t indent) const;
    std::string e_RedirectionUTRA_r9_ToStringNoNewLines() const;
    int e_RedirectionUTRA_r9_Clear();
    bool e_RedirectionUTRA_r9_IsPresent() const;
private:
    bool e_RedirectionUTRA_r9_present;
    e_RedirectionUTRA_r9_Enum e_RedirectionUTRA_r9_internal_value;

};

#endif
