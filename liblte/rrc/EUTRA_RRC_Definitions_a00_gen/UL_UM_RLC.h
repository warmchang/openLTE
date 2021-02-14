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

#ifndef __UL_UM_RLC_H__
#define __UL_UM_RLC_H__

#include "SN_FieldLength.h"

#include <array>
#include <cstdint>
#include <vector>

class UL_UM_RLC
{
public:
    UL_UM_RLC() : sn_FieldLength_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // sn-FieldLength
public:
    SN_FieldLength* sn_FieldLength_Set();
    int sn_FieldLength_Set(SN_FieldLength &value);
    const SN_FieldLength& sn_FieldLength_Get() const;
    std::string sn_FieldLength_ToString(uint32_t indent) const;
    std::string sn_FieldLength_ToStringNoNewLines() const;
    int sn_FieldLength_Clear();
    bool sn_FieldLength_IsPresent() const;
private:
    bool sn_FieldLength_present;
    SN_FieldLength sn_FieldLength;

};

#endif
