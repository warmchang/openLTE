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

#ifndef __SystemInformationBlockType5_H__
#define __SystemInformationBlockType5_H__

#include "InterFreqCarrierFreqList.h"

#include <array>
#include <cstdint>
#include <vector>

class SystemInformationBlockType5
{
public:
    SystemInformationBlockType5() : interFreqCarrierFreqList_present{false}, lateNonCriticalExtension_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // interFreqCarrierFreqList
public:
    InterFreqCarrierFreqList* interFreqCarrierFreqList_Set();
    int interFreqCarrierFreqList_Set(InterFreqCarrierFreqList &value);
    const InterFreqCarrierFreqList& interFreqCarrierFreqList_Get() const;
    std::string interFreqCarrierFreqList_ToString(uint32_t indent) const;
    std::string interFreqCarrierFreqList_ToStringNoNewLines() const;
    int interFreqCarrierFreqList_Clear();
    bool interFreqCarrierFreqList_IsPresent() const;
private:
    bool interFreqCarrierFreqList_present;
    InterFreqCarrierFreqList interFreqCarrierFreqList;

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

};

#endif
