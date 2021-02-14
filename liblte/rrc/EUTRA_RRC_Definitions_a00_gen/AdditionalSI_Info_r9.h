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

#ifndef __AdditionalSI_Info_r9_H__
#define __AdditionalSI_Info_r9_H__

#include "CSG_Identity.h"

#include <array>
#include <cstdint>
#include <vector>

class AdditionalSI_Info_r9
{
public:
    AdditionalSI_Info_r9() : csg_MemberStatus_r9_present{false}, csg_Identity_r9_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // csg-MemberStatus-r9
public:
    enum csg_MemberStatus_r9_Enum {
        k_csg_MemberStatus_r9_member = 0,
    };
    int csg_MemberStatus_r9_Pack(std::vector<uint8_t> &bits);
    int csg_MemberStatus_r9_Unpack(std::vector<uint8_t> bits);
    int csg_MemberStatus_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    csg_MemberStatus_r9_Enum csg_MemberStatus_r9_Value() const;
    int csg_MemberStatus_r9_SetValue(csg_MemberStatus_r9_Enum value);
    int csg_MemberStatus_r9_SetValue(std::string value);
    std::string csg_MemberStatus_r9_ValueToString(csg_MemberStatus_r9_Enum value) const;
    uint64_t csg_MemberStatus_r9_NumberOfValues() const;
    std::string csg_MemberStatus_r9_ToString(uint32_t indent) const;
    std::string csg_MemberStatus_r9_ToStringNoNewLines() const;
    int csg_MemberStatus_r9_Clear();
    bool csg_MemberStatus_r9_IsPresent() const;
private:
    bool csg_MemberStatus_r9_present;
    csg_MemberStatus_r9_Enum csg_MemberStatus_r9_internal_value;

    // csg-Identity-r9
public:
    CSG_Identity* csg_Identity_r9_Set();
    int csg_Identity_r9_Set(CSG_Identity &value);
    const CSG_Identity& csg_Identity_r9_Get() const;
    std::string csg_Identity_r9_ToString(uint32_t indent) const;
    std::string csg_Identity_r9_ToStringNoNewLines() const;
    int csg_Identity_r9_Clear();
    bool csg_Identity_r9_IsPresent() const;
private:
    bool csg_Identity_r9_present;
    CSG_Identity csg_Identity_r9;

};

#endif
