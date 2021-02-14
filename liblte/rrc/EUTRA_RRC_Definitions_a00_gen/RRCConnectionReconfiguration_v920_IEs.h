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

#ifndef __RRCConnectionReconfiguration_v920_IEs_H__
#define __RRCConnectionReconfiguration_v920_IEs_H__

#include "OtherConfig_r9.h"
#include "RRCConnectionReconfiguration_v10xy_IEs.h"

#include <array>
#include <cstdint>
#include <vector>

class RRCConnectionReconfiguration_v920_IEs
{
public:
    RRCConnectionReconfiguration_v920_IEs() : otherConfig_r9_present{false}, fullConfig_r9_present{false}, nonCriticalExtension_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // otherConfig-r9
public:
    OtherConfig_r9* otherConfig_r9_Set();
    int otherConfig_r9_Set(OtherConfig_r9 &value);
    const OtherConfig_r9& otherConfig_r9_Get() const;
    std::string otherConfig_r9_ToString(uint32_t indent) const;
    std::string otherConfig_r9_ToStringNoNewLines() const;
    int otherConfig_r9_Clear();
    bool otherConfig_r9_IsPresent() const;
private:
    bool otherConfig_r9_present;
    OtherConfig_r9 otherConfig_r9;

    // fullConfig-r9
public:
    enum fullConfig_r9_Enum {
        k_fullConfig_r9_true = 0,
    };
    int fullConfig_r9_Pack(std::vector<uint8_t> &bits);
    int fullConfig_r9_Unpack(std::vector<uint8_t> bits);
    int fullConfig_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    fullConfig_r9_Enum fullConfig_r9_Value() const;
    int fullConfig_r9_SetValue(fullConfig_r9_Enum value);
    int fullConfig_r9_SetValue(std::string value);
    std::string fullConfig_r9_ValueToString(fullConfig_r9_Enum value) const;
    uint64_t fullConfig_r9_NumberOfValues() const;
    std::string fullConfig_r9_ToString(uint32_t indent) const;
    std::string fullConfig_r9_ToStringNoNewLines() const;
    int fullConfig_r9_Clear();
    bool fullConfig_r9_IsPresent() const;
private:
    bool fullConfig_r9_present;
    fullConfig_r9_Enum fullConfig_r9_internal_value;

    // nonCriticalExtension
public:
    RRCConnectionReconfiguration_v10xy_IEs* nonCriticalExtension_Set();
    int nonCriticalExtension_Set(RRCConnectionReconfiguration_v10xy_IEs &value);
    const RRCConnectionReconfiguration_v10xy_IEs& nonCriticalExtension_Get() const;
    std::string nonCriticalExtension_ToString(uint32_t indent) const;
    std::string nonCriticalExtension_ToStringNoNewLines() const;
    int nonCriticalExtension_Clear();
    bool nonCriticalExtension_IsPresent() const;
private:
    bool nonCriticalExtension_present;
    RRCConnectionReconfiguration_v10xy_IEs nonCriticalExtension;

};

#endif
