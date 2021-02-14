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

#ifndef __DL_AM_RLC_H__
#define __DL_AM_RLC_H__

#include "T_Reordering.h"
#include "T_StatusProhibit.h"

#include <array>
#include <cstdint>
#include <vector>

class DL_AM_RLC
{
public:
    DL_AM_RLC() : t_Reordering_present{false}, t_StatusProhibit_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // t-Reordering
public:
    T_Reordering* t_Reordering_Set();
    int t_Reordering_Set(T_Reordering &value);
    const T_Reordering& t_Reordering_Get() const;
    std::string t_Reordering_ToString(uint32_t indent) const;
    std::string t_Reordering_ToStringNoNewLines() const;
    int t_Reordering_Clear();
    bool t_Reordering_IsPresent() const;
private:
    bool t_Reordering_present;
    T_Reordering t_Reordering;

    // t-StatusProhibit
public:
    T_StatusProhibit* t_StatusProhibit_Set();
    int t_StatusProhibit_Set(T_StatusProhibit &value);
    const T_StatusProhibit& t_StatusProhibit_Get() const;
    std::string t_StatusProhibit_ToString(uint32_t indent) const;
    std::string t_StatusProhibit_ToStringNoNewLines() const;
    int t_StatusProhibit_Clear();
    bool t_StatusProhibit_IsPresent() const;
private:
    bool t_StatusProhibit_present;
    T_StatusProhibit t_StatusProhibit;

};

#endif
