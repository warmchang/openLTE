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

#ifndef __MeasResultsCDMA2000_H__
#define __MeasResultsCDMA2000_H__

#include "MeasResultListCDMA2000.h"

#include <array>
#include <cstdint>
#include <vector>

class MeasResultsCDMA2000
{
public:
    MeasResultsCDMA2000() : preRegistrationStatusHRPD_present{false}, measResultListCDMA2000_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // preRegistrationStatusHRPD
public:
    int preRegistrationStatusHRPD_Pack(std::vector<uint8_t> &bits);
    int preRegistrationStatusHRPD_Unpack(std::vector<uint8_t> bits);
    int preRegistrationStatusHRPD_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    bool preRegistrationStatusHRPD_Value() const;
    int preRegistrationStatusHRPD_SetValue(bool value);
    std::string preRegistrationStatusHRPD_ToString(uint32_t indent) const;
    std::string preRegistrationStatusHRPD_ToStringNoNewLines() const;
    int preRegistrationStatusHRPD_Clear();
    bool preRegistrationStatusHRPD_IsPresent() const;
private:
    bool preRegistrationStatusHRPD_present;
    bool preRegistrationStatusHRPD_internal_value;

    // measResultListCDMA2000
public:
    MeasResultListCDMA2000* measResultListCDMA2000_Set();
    int measResultListCDMA2000_Set(MeasResultListCDMA2000 &value);
    const MeasResultListCDMA2000& measResultListCDMA2000_Get() const;
    std::string measResultListCDMA2000_ToString(uint32_t indent) const;
    std::string measResultListCDMA2000_ToStringNoNewLines() const;
    int measResultListCDMA2000_Clear();
    bool measResultListCDMA2000_IsPresent() const;
private:
    bool measResultListCDMA2000_present;
    MeasResultListCDMA2000 measResultListCDMA2000;

};

#endif
