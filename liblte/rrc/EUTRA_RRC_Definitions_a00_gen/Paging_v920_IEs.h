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

#ifndef __Paging_v920_IEs_H__
#define __Paging_v920_IEs_H__

#include <array>
#include <cstdint>
#include <vector>

class Paging_v920_IEs
{
public:
    Paging_v920_IEs() : cmas_Indication_r9_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // cmas-Indication-r9
public:
    enum cmas_Indication_r9_Enum {
        k_cmas_Indication_r9_true = 0,
    };
    int cmas_Indication_r9_Pack(std::vector<uint8_t> &bits);
    int cmas_Indication_r9_Unpack(std::vector<uint8_t> bits);
    int cmas_Indication_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    cmas_Indication_r9_Enum cmas_Indication_r9_Value() const;
    int cmas_Indication_r9_SetValue(cmas_Indication_r9_Enum value);
    int cmas_Indication_r9_SetValue(std::string value);
    std::string cmas_Indication_r9_ValueToString(cmas_Indication_r9_Enum value) const;
    uint64_t cmas_Indication_r9_NumberOfValues() const;
    std::string cmas_Indication_r9_ToString(uint32_t indent) const;
    std::string cmas_Indication_r9_ToStringNoNewLines() const;
    int cmas_Indication_r9_Clear();
    bool cmas_Indication_r9_IsPresent() const;
private:
    bool cmas_Indication_r9_present;
    cmas_Indication_r9_Enum cmas_Indication_r9_internal_value;

    // nonCriticalExtension

};

#endif
