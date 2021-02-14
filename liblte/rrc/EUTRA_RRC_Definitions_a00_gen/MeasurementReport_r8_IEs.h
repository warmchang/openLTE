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

#ifndef __MeasurementReport_r8_IEs_H__
#define __MeasurementReport_r8_IEs_H__

#include "MeasResults.h"
#include "MeasurementReport_v8a0_IEs.h"

#include <array>
#include <cstdint>
#include <vector>

class MeasurementReport_r8_IEs
{
public:
    MeasurementReport_r8_IEs() : measResults_present{false}, nonCriticalExtension_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // measResults
public:
    MeasResults* measResults_Set();
    int measResults_Set(MeasResults &value);
    const MeasResults& measResults_Get() const;
    std::string measResults_ToString(uint32_t indent) const;
    std::string measResults_ToStringNoNewLines() const;
    int measResults_Clear();
    bool measResults_IsPresent() const;
private:
    bool measResults_present;
    MeasResults measResults;

    // nonCriticalExtension
public:
    MeasurementReport_v8a0_IEs* nonCriticalExtension_Set();
    int nonCriticalExtension_Set(MeasurementReport_v8a0_IEs &value);
    const MeasurementReport_v8a0_IEs& nonCriticalExtension_Get() const;
    std::string nonCriticalExtension_ToString(uint32_t indent) const;
    std::string nonCriticalExtension_ToStringNoNewLines() const;
    int nonCriticalExtension_Clear();
    bool nonCriticalExtension_IsPresent() const;
private:
    bool nonCriticalExtension_present;
    MeasurementReport_v8a0_IEs nonCriticalExtension;

};

#endif
