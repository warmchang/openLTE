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

#ifndef __UEInformationRequest_v930_IEs_H__
#define __UEInformationRequest_v930_IEs_H__

#include "UEInformationRequest_v10xy_IEs.h"

#include <array>
#include <cstdint>
#include <vector>

class UEInformationRequest_v930_IEs
{
public:
    UEInformationRequest_v930_IEs() : lateNonCriticalExtension_present{false}, nonCriticalExtension_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // lateNonCriticalExtension
public:
    int lateNonCriticalExtension_Pack(std::vector<uint8_t> &bits);
    int lateNonCriticalExtension_Unpack(std::vector<uint8_t> bits);
    int lateNonCriticalExtension_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::vector<uint8_t> lateNonCriticalExtension_Value() const;
    int lateNonCriticalExtension_SetValue(std::vector<uint8_t> value);
    std::string lateNonCriticalExtension_ToString(uint32_t indent) const;
    std::string lateNonCriticalExtension_ToStringNoNewLines() const;
    int lateNonCriticalExtension_Clear();
    bool lateNonCriticalExtension_IsPresent() const;
private:
    bool lateNonCriticalExtension_present;
    std::vector<uint8_t> lateNonCriticalExtension_internal_value;

    // nonCriticalExtension
public:
    UEInformationRequest_v10xy_IEs* nonCriticalExtension_Set();
    int nonCriticalExtension_Set(UEInformationRequest_v10xy_IEs &value);
    const UEInformationRequest_v10xy_IEs& nonCriticalExtension_Get() const;
    std::string nonCriticalExtension_ToString(uint32_t indent) const;
    std::string nonCriticalExtension_ToStringNoNewLines() const;
    int nonCriticalExtension_Clear();
    bool nonCriticalExtension_IsPresent() const;
private:
    bool nonCriticalExtension_present;
    UEInformationRequest_v10xy_IEs nonCriticalExtension;

};

#endif
