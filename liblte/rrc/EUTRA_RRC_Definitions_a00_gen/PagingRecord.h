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

#ifndef __PagingRecord_H__
#define __PagingRecord_H__

#include "PagingUE_Identity.h"

#include <array>
#include <cstdint>
#include <vector>

class PagingRecord
{
public:
    PagingRecord() : ue_Identity_present{false}, cn_Domain_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // ue-Identity
public:
    PagingUE_Identity* ue_Identity_Set();
    int ue_Identity_Set(PagingUE_Identity &value);
    const PagingUE_Identity& ue_Identity_Get() const;
    std::string ue_Identity_ToString(uint32_t indent) const;
    std::string ue_Identity_ToStringNoNewLines() const;
    int ue_Identity_Clear();
    bool ue_Identity_IsPresent() const;
private:
    bool ue_Identity_present;
    PagingUE_Identity ue_Identity;

    // cn-Domain
public:
    enum cn_Domain_Enum {
        k_cn_Domain_ps = 0,
        k_cn_Domain_cs,
    };
    int cn_Domain_Pack(std::vector<uint8_t> &bits);
    int cn_Domain_Unpack(std::vector<uint8_t> bits);
    int cn_Domain_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    cn_Domain_Enum cn_Domain_Value() const;
    int cn_Domain_SetValue(cn_Domain_Enum value);
    int cn_Domain_SetValue(std::string value);
    std::string cn_Domain_ValueToString(cn_Domain_Enum value) const;
    uint64_t cn_Domain_NumberOfValues() const;
    std::string cn_Domain_ToString(uint32_t indent) const;
    std::string cn_Domain_ToStringNoNewLines() const;
    int cn_Domain_Clear();
    bool cn_Domain_IsPresent() const;
private:
    bool cn_Domain_present;
    cn_Domain_Enum cn_Domain_internal_value;

};

#endif
