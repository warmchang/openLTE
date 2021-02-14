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

#ifndef __DL_CCCH_MessageType_H__
#define __DL_CCCH_MessageType_H__

#include "RRCConnectionReestablishment.h"
#include "RRCConnectionReestablishmentReject.h"
#include "RRCConnectionReject.h"
#include "RRCConnectionSetup.h"

#include <array>
#include <cstdint>
#include <vector>

class DL_CCCH_MessageType
{
public:
    enum Enum {
        k_c1 = 0,
        k_messageClassExtension,
    };
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    Enum Choice() const;
    int SetChoice(Enum choice);
    std::string ChoiceToString(Enum value) const;
    uint64_t NumberOfChoices() const;
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;
    int Clear();
    bool IsPresent() const;
private:
    bool present;
    Enum internal_choice;

    // c1
public:
    enum c1_Enum {
        k_c1_rrcConnectionReestablishment = 0,
        k_c1_rrcConnectionReestablishmentReject,
        k_c1_rrcConnectionReject,
        k_c1_rrcConnectionSetup,
    };
    int c1_Pack(std::vector<uint8_t> &bits);
    int c1_Unpack(std::vector<uint8_t> bits);
    int c1_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    c1_Enum c1_Choice() const;
    int c1_SetChoice(c1_Enum choice);
    std::string c1_ChoiceToString(c1_Enum value) const;
    uint64_t c1_NumberOfChoices() const;
    std::string c1_ToString(uint32_t indent) const;
    std::string c1_ToStringNoNewLines() const;
    int c1_Clear();
    bool c1_IsPresent() const;
private:
    bool c1_present;
    c1_Enum c1_internal_choice;

    // rrcConnectionReestablishment
public:
    RRCConnectionReestablishment* c1_rrcConnectionReestablishment_Set();
    int c1_rrcConnectionReestablishment_Set(RRCConnectionReestablishment &value);
    const RRCConnectionReestablishment& c1_rrcConnectionReestablishment_Get() const;
    std::string c1_rrcConnectionReestablishment_ToString(uint32_t indent) const;
    std::string c1_rrcConnectionReestablishment_ToStringNoNewLines() const;
    int c1_rrcConnectionReestablishment_Clear();
    bool c1_rrcConnectionReestablishment_IsPresent() const;
private:
    bool c1_rrcConnectionReestablishment_present;
    RRCConnectionReestablishment c1_rrcConnectionReestablishment;

    // rrcConnectionReestablishmentReject
public:
    RRCConnectionReestablishmentReject* c1_rrcConnectionReestablishmentReject_Set();
    int c1_rrcConnectionReestablishmentReject_Set(RRCConnectionReestablishmentReject &value);
    const RRCConnectionReestablishmentReject& c1_rrcConnectionReestablishmentReject_Get() const;
    std::string c1_rrcConnectionReestablishmentReject_ToString(uint32_t indent) const;
    std::string c1_rrcConnectionReestablishmentReject_ToStringNoNewLines() const;
    int c1_rrcConnectionReestablishmentReject_Clear();
    bool c1_rrcConnectionReestablishmentReject_IsPresent() const;
private:
    bool c1_rrcConnectionReestablishmentReject_present;
    RRCConnectionReestablishmentReject c1_rrcConnectionReestablishmentReject;

    // rrcConnectionReject
public:
    RRCConnectionReject* c1_rrcConnectionReject_Set();
    int c1_rrcConnectionReject_Set(RRCConnectionReject &value);
    const RRCConnectionReject& c1_rrcConnectionReject_Get() const;
    std::string c1_rrcConnectionReject_ToString(uint32_t indent) const;
    std::string c1_rrcConnectionReject_ToStringNoNewLines() const;
    int c1_rrcConnectionReject_Clear();
    bool c1_rrcConnectionReject_IsPresent() const;
private:
    bool c1_rrcConnectionReject_present;
    RRCConnectionReject c1_rrcConnectionReject;

    // rrcConnectionSetup
public:
    RRCConnectionSetup* c1_rrcConnectionSetup_Set();
    int c1_rrcConnectionSetup_Set(RRCConnectionSetup &value);
    const RRCConnectionSetup& c1_rrcConnectionSetup_Get() const;
    std::string c1_rrcConnectionSetup_ToString(uint32_t indent) const;
    std::string c1_rrcConnectionSetup_ToStringNoNewLines() const;
    int c1_rrcConnectionSetup_Clear();
    bool c1_rrcConnectionSetup_IsPresent() const;
private:
    bool c1_rrcConnectionSetup_present;
    RRCConnectionSetup c1_rrcConnectionSetup;


    // messageClassExtension

};

#endif
