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

#ifndef __MeasObjectToAddMod_H__
#define __MeasObjectToAddMod_H__

#include "MeasObjectId.h"
#include "MeasObjectEUTRA.h"
#include "MeasObjectUTRA.h"
#include "MeasObjectGERAN.h"
#include "MeasObjectCDMA2000.h"

#include <array>
#include <cstdint>
#include <vector>

class MeasObjectToAddMod
{
public:
    MeasObjectToAddMod() : measObjectId_present{false}, measObject_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // measObjectId
public:
    MeasObjectId* measObjectId_Set();
    int measObjectId_Set(MeasObjectId &value);
    const MeasObjectId& measObjectId_Get() const;
    std::string measObjectId_ToString(uint32_t indent) const;
    std::string measObjectId_ToStringNoNewLines() const;
    int measObjectId_Clear();
    bool measObjectId_IsPresent() const;
private:
    bool measObjectId_present;
    MeasObjectId measObjectId;

    // measObject
public:
    enum measObject_Enum {
        k_measObject_measObjectEUTRA = 0,
        k_measObject_measObjectUTRA,
        k_measObject_measObjectGERAN,
        k_measObject_measObjectCDMA2000,
    };
    int measObject_Pack(std::vector<uint8_t> &bits);
    int measObject_Unpack(std::vector<uint8_t> bits);
    int measObject_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    measObject_Enum measObject_Choice() const;
    int measObject_SetChoice(measObject_Enum choice);
    std::string measObject_ChoiceToString(measObject_Enum value) const;
    uint64_t measObject_NumberOfChoices() const;
    std::string measObject_ToString(uint32_t indent) const;
    std::string measObject_ToStringNoNewLines() const;
    int measObject_Clear();
    bool measObject_IsPresent() const;
private:
    bool measObject_present;
    measObject_Enum measObject_internal_choice;

    // measObjectEUTRA
public:
    MeasObjectEUTRA* measObject_measObjectEUTRA_Set();
    int measObject_measObjectEUTRA_Set(MeasObjectEUTRA &value);
    const MeasObjectEUTRA& measObject_measObjectEUTRA_Get() const;
    std::string measObject_measObjectEUTRA_ToString(uint32_t indent) const;
    std::string measObject_measObjectEUTRA_ToStringNoNewLines() const;
    int measObject_measObjectEUTRA_Clear();
    bool measObject_measObjectEUTRA_IsPresent() const;
private:
    bool measObject_measObjectEUTRA_present;
    MeasObjectEUTRA measObject_measObjectEUTRA;

    // measObjectUTRA
public:
    MeasObjectUTRA* measObject_measObjectUTRA_Set();
    int measObject_measObjectUTRA_Set(MeasObjectUTRA &value);
    const MeasObjectUTRA& measObject_measObjectUTRA_Get() const;
    std::string measObject_measObjectUTRA_ToString(uint32_t indent) const;
    std::string measObject_measObjectUTRA_ToStringNoNewLines() const;
    int measObject_measObjectUTRA_Clear();
    bool measObject_measObjectUTRA_IsPresent() const;
private:
    bool measObject_measObjectUTRA_present;
    MeasObjectUTRA measObject_measObjectUTRA;

    // measObjectGERAN
public:
    MeasObjectGERAN* measObject_measObjectGERAN_Set();
    int measObject_measObjectGERAN_Set(MeasObjectGERAN &value);
    const MeasObjectGERAN& measObject_measObjectGERAN_Get() const;
    std::string measObject_measObjectGERAN_ToString(uint32_t indent) const;
    std::string measObject_measObjectGERAN_ToStringNoNewLines() const;
    int measObject_measObjectGERAN_Clear();
    bool measObject_measObjectGERAN_IsPresent() const;
private:
    bool measObject_measObjectGERAN_present;
    MeasObjectGERAN measObject_measObjectGERAN;

    // measObjectCDMA2000
public:
    MeasObjectCDMA2000* measObject_measObjectCDMA2000_Set();
    int measObject_measObjectCDMA2000_Set(MeasObjectCDMA2000 &value);
    const MeasObjectCDMA2000& measObject_measObjectCDMA2000_Get() const;
    std::string measObject_measObjectCDMA2000_ToString(uint32_t indent) const;
    std::string measObject_measObjectCDMA2000_ToStringNoNewLines() const;
    int measObject_measObjectCDMA2000_Clear();
    bool measObject_measObjectCDMA2000_IsPresent() const;
private:
    bool measObject_measObjectCDMA2000_present;
    MeasObjectCDMA2000 measObject_measObjectCDMA2000;


};

#endif
