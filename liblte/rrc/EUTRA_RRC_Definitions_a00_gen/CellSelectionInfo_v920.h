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

#ifndef __CellSelectionInfo_v920_H__
#define __CellSelectionInfo_v920_H__

#include "Q_QualMin_r9.h"

#include <array>
#include <cstdint>
#include <vector>

class CellSelectionInfo_v920
{
public:
    CellSelectionInfo_v920() : q_QualMin_r9_present{false}, q_QualMinOffset_r9_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // q-QualMin-r9
public:
    Q_QualMin_r9* q_QualMin_r9_Set();
    int q_QualMin_r9_Set(Q_QualMin_r9 &value);
    const Q_QualMin_r9& q_QualMin_r9_Get() const;
    std::string q_QualMin_r9_ToString(uint32_t indent) const;
    std::string q_QualMin_r9_ToStringNoNewLines() const;
    int q_QualMin_r9_Clear();
    bool q_QualMin_r9_IsPresent() const;
private:
    bool q_QualMin_r9_present;
    Q_QualMin_r9 q_QualMin_r9;

    // q-QualMinOffset-r9
public:
    int q_QualMinOffset_r9_Pack(std::vector<uint8_t> &bits);
    int q_QualMinOffset_r9_Unpack(std::vector<uint8_t> bits);
    int q_QualMinOffset_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t q_QualMinOffset_r9_Value() const;
    int q_QualMinOffset_r9_SetValue(int64_t value);
    std::string q_QualMinOffset_r9_ToString(uint32_t indent) const;
    std::string q_QualMinOffset_r9_ToStringNoNewLines() const;
    int q_QualMinOffset_r9_Clear();
    bool q_QualMinOffset_r9_IsPresent() const;
private:
    bool q_QualMinOffset_r9_present;
    int64_t q_QualMinOffset_r9_internal_value;

};

#endif
