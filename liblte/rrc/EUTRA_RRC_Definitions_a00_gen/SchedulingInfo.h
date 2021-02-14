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

#ifndef __SchedulingInfo_H__
#define __SchedulingInfo_H__

#include "SIB_MappingInfo.h"

#include <array>
#include <cstdint>
#include <vector>

class SchedulingInfo
{
public:
    SchedulingInfo() : si_Periodicity_present{false}, sib_MappingInfo_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // si-Periodicity
public:
    enum si_Periodicity_Enum {
        k_si_Periodicity_rf8 = 0,
        k_si_Periodicity_rf16,
        k_si_Periodicity_rf32,
        k_si_Periodicity_rf64,
        k_si_Periodicity_rf128,
        k_si_Periodicity_rf256,
        k_si_Periodicity_rf512,
    };
    int si_Periodicity_Pack(std::vector<uint8_t> &bits);
    int si_Periodicity_Unpack(std::vector<uint8_t> bits);
    int si_Periodicity_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    si_Periodicity_Enum si_Periodicity_Value() const;
    int si_Periodicity_SetValue(si_Periodicity_Enum value);
    int si_Periodicity_SetValue(std::string value);
    std::string si_Periodicity_ValueToString(si_Periodicity_Enum value) const;
    uint64_t si_Periodicity_NumberOfValues() const;
    std::string si_Periodicity_ToString(uint32_t indent) const;
    std::string si_Periodicity_ToStringNoNewLines() const;
    int si_Periodicity_Clear();
    bool si_Periodicity_IsPresent() const;
private:
    bool si_Periodicity_present;
    si_Periodicity_Enum si_Periodicity_internal_value;

    // sib-MappingInfo
public:
    SIB_MappingInfo* sib_MappingInfo_Set();
    int sib_MappingInfo_Set(SIB_MappingInfo &value);
    const SIB_MappingInfo& sib_MappingInfo_Get() const;
    std::string sib_MappingInfo_ToString(uint32_t indent) const;
    std::string sib_MappingInfo_ToStringNoNewLines() const;
    int sib_MappingInfo_Clear();
    bool sib_MappingInfo_IsPresent() const;
private:
    bool sib_MappingInfo_present;
    SIB_MappingInfo sib_MappingInfo;

};

#endif
