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

#ifndef __RRCConnectionSetupComplete_r8_IEs_H__
#define __RRCConnectionSetupComplete_r8_IEs_H__

#include "RegisteredMME.h"
#include "DedicatedInfoNAS.h"
#include "RRCConnectionSetupComplete_v8a0_IEs.h"

#include <array>
#include <cstdint>
#include <vector>

class RRCConnectionSetupComplete_r8_IEs
{
public:
    RRCConnectionSetupComplete_r8_IEs() : selectedPLMN_Identity_present{false}, registeredMME_present{false}, dedicatedInfoNAS_present{false}, nonCriticalExtension_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // selectedPLMN-Identity
public:
    int selectedPLMN_Identity_Pack(std::vector<uint8_t> &bits);
    int selectedPLMN_Identity_Unpack(std::vector<uint8_t> bits);
    int selectedPLMN_Identity_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t selectedPLMN_Identity_Value() const;
    int selectedPLMN_Identity_SetValue(int64_t value);
    std::string selectedPLMN_Identity_ToString(uint32_t indent) const;
    std::string selectedPLMN_Identity_ToStringNoNewLines() const;
    int selectedPLMN_Identity_Clear();
    bool selectedPLMN_Identity_IsPresent() const;
private:
    bool selectedPLMN_Identity_present;
    int64_t selectedPLMN_Identity_internal_value;

    // registeredMME
public:
    RegisteredMME* registeredMME_Set();
    int registeredMME_Set(RegisteredMME &value);
    const RegisteredMME& registeredMME_Get() const;
    std::string registeredMME_ToString(uint32_t indent) const;
    std::string registeredMME_ToStringNoNewLines() const;
    int registeredMME_Clear();
    bool registeredMME_IsPresent() const;
private:
    bool registeredMME_present;
    RegisteredMME registeredMME;

    // dedicatedInfoNAS
public:
    DedicatedInfoNAS* dedicatedInfoNAS_Set();
    int dedicatedInfoNAS_Set(DedicatedInfoNAS &value);
    const DedicatedInfoNAS& dedicatedInfoNAS_Get() const;
    std::string dedicatedInfoNAS_ToString(uint32_t indent) const;
    std::string dedicatedInfoNAS_ToStringNoNewLines() const;
    int dedicatedInfoNAS_Clear();
    bool dedicatedInfoNAS_IsPresent() const;
private:
    bool dedicatedInfoNAS_present;
    DedicatedInfoNAS dedicatedInfoNAS;

    // nonCriticalExtension
public:
    RRCConnectionSetupComplete_v8a0_IEs* nonCriticalExtension_Set();
    int nonCriticalExtension_Set(RRCConnectionSetupComplete_v8a0_IEs &value);
    const RRCConnectionSetupComplete_v8a0_IEs& nonCriticalExtension_Get() const;
    std::string nonCriticalExtension_ToString(uint32_t indent) const;
    std::string nonCriticalExtension_ToStringNoNewLines() const;
    int nonCriticalExtension_Clear();
    bool nonCriticalExtension_IsPresent() const;
private:
    bool nonCriticalExtension_present;
    RRCConnectionSetupComplete_v8a0_IEs nonCriticalExtension;

};

#endif
