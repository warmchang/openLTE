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

#ifndef __HandoverFromEUTRAPreparationRequest_v920_IEs_H__
#define __HandoverFromEUTRAPreparationRequest_v920_IEs_H__

#include "HandoverFromEUTRAPreparationRequest_r10_IEs.h"

#include <array>
#include <cstdint>
#include <vector>

class HandoverFromEUTRAPreparationRequest_v920_IEs
{
public:
    HandoverFromEUTRAPreparationRequest_v920_IEs() : concurrPrepCDMA2000_HRPD_r9_present{false}, nonCriticalExtension_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // concurrPrepCDMA2000-HRPD-r9
public:
    int concurrPrepCDMA2000_HRPD_r9_Pack(std::vector<uint8_t> &bits);
    int concurrPrepCDMA2000_HRPD_r9_Unpack(std::vector<uint8_t> bits);
    int concurrPrepCDMA2000_HRPD_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    bool concurrPrepCDMA2000_HRPD_r9_Value() const;
    int concurrPrepCDMA2000_HRPD_r9_SetValue(bool value);
    std::string concurrPrepCDMA2000_HRPD_r9_ToString(uint32_t indent) const;
    std::string concurrPrepCDMA2000_HRPD_r9_ToStringNoNewLines() const;
    int concurrPrepCDMA2000_HRPD_r9_Clear();
    bool concurrPrepCDMA2000_HRPD_r9_IsPresent() const;
private:
    bool concurrPrepCDMA2000_HRPD_r9_present;
    bool concurrPrepCDMA2000_HRPD_r9_internal_value;

    // nonCriticalExtension
public:
    HandoverFromEUTRAPreparationRequest_r10_IEs* nonCriticalExtension_Set();
    int nonCriticalExtension_Set(HandoverFromEUTRAPreparationRequest_r10_IEs &value);
    const HandoverFromEUTRAPreparationRequest_r10_IEs& nonCriticalExtension_Get() const;
    std::string nonCriticalExtension_ToString(uint32_t indent) const;
    std::string nonCriticalExtension_ToStringNoNewLines() const;
    int nonCriticalExtension_Clear();
    bool nonCriticalExtension_IsPresent() const;
private:
    bool nonCriticalExtension_present;
    HandoverFromEUTRAPreparationRequest_r10_IEs nonCriticalExtension;

};

#endif
