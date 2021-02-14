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

#ifndef __PreRegistrationInfoHRPD_H__
#define __PreRegistrationInfoHRPD_H__

#include "PreRegistrationZoneIdHRPD.h"
#include "SecondaryPreRegistrationZoneIdListHRPD.h"

#include <array>
#include <cstdint>
#include <vector>

class PreRegistrationInfoHRPD
{
public:
    PreRegistrationInfoHRPD() : preRegistrationAllowed_present{false}, preRegistrationZoneId_present{false}, secondaryPreRegistrationZoneIdList_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // preRegistrationAllowed
public:
    int preRegistrationAllowed_Pack(std::vector<uint8_t> &bits);
    int preRegistrationAllowed_Unpack(std::vector<uint8_t> bits);
    int preRegistrationAllowed_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    bool preRegistrationAllowed_Value() const;
    int preRegistrationAllowed_SetValue(bool value);
    std::string preRegistrationAllowed_ToString(uint32_t indent) const;
    std::string preRegistrationAllowed_ToStringNoNewLines() const;
    int preRegistrationAllowed_Clear();
    bool preRegistrationAllowed_IsPresent() const;
private:
    bool preRegistrationAllowed_present;
    bool preRegistrationAllowed_internal_value;

    // preRegistrationZoneId
public:
    PreRegistrationZoneIdHRPD* preRegistrationZoneId_Set();
    int preRegistrationZoneId_Set(PreRegistrationZoneIdHRPD &value);
    const PreRegistrationZoneIdHRPD& preRegistrationZoneId_Get() const;
    std::string preRegistrationZoneId_ToString(uint32_t indent) const;
    std::string preRegistrationZoneId_ToStringNoNewLines() const;
    int preRegistrationZoneId_Clear();
    bool preRegistrationZoneId_IsPresent() const;
private:
    bool preRegistrationZoneId_present;
    PreRegistrationZoneIdHRPD preRegistrationZoneId;

    // secondaryPreRegistrationZoneIdList
public:
    SecondaryPreRegistrationZoneIdListHRPD* secondaryPreRegistrationZoneIdList_Set();
    int secondaryPreRegistrationZoneIdList_Set(SecondaryPreRegistrationZoneIdListHRPD &value);
    const SecondaryPreRegistrationZoneIdListHRPD& secondaryPreRegistrationZoneIdList_Get() const;
    std::string secondaryPreRegistrationZoneIdList_ToString(uint32_t indent) const;
    std::string secondaryPreRegistrationZoneIdList_ToStringNoNewLines() const;
    int secondaryPreRegistrationZoneIdList_Clear();
    bool secondaryPreRegistrationZoneIdList_IsPresent() const;
private:
    bool secondaryPreRegistrationZoneIdList_present;
    SecondaryPreRegistrationZoneIdListHRPD secondaryPreRegistrationZoneIdList;

};

#endif
