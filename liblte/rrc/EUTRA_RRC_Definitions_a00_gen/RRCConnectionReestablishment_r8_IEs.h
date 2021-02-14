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

#ifndef __RRCConnectionReestablishment_r8_IEs_H__
#define __RRCConnectionReestablishment_r8_IEs_H__

#include "RadioResourceConfigDedicated.h"
#include "NextHopChainingCount.h"
#include "RRCConnectionReestablishment_v8a0_IEs.h"

#include <array>
#include <cstdint>
#include <vector>

class RRCConnectionReestablishment_r8_IEs
{
public:
    RRCConnectionReestablishment_r8_IEs() : radioResourceConfigDedicated_present{false}, nextHopChainingCount_present{false}, nonCriticalExtension_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // radioResourceConfigDedicated
public:
    RadioResourceConfigDedicated* radioResourceConfigDedicated_Set();
    int radioResourceConfigDedicated_Set(RadioResourceConfigDedicated &value);
    const RadioResourceConfigDedicated& radioResourceConfigDedicated_Get() const;
    std::string radioResourceConfigDedicated_ToString(uint32_t indent) const;
    std::string radioResourceConfigDedicated_ToStringNoNewLines() const;
    int radioResourceConfigDedicated_Clear();
    bool radioResourceConfigDedicated_IsPresent() const;
private:
    bool radioResourceConfigDedicated_present;
    RadioResourceConfigDedicated radioResourceConfigDedicated;

    // nextHopChainingCount
public:
    NextHopChainingCount* nextHopChainingCount_Set();
    int nextHopChainingCount_Set(NextHopChainingCount &value);
    const NextHopChainingCount& nextHopChainingCount_Get() const;
    std::string nextHopChainingCount_ToString(uint32_t indent) const;
    std::string nextHopChainingCount_ToStringNoNewLines() const;
    int nextHopChainingCount_Clear();
    bool nextHopChainingCount_IsPresent() const;
private:
    bool nextHopChainingCount_present;
    NextHopChainingCount nextHopChainingCount;

    // nonCriticalExtension
public:
    RRCConnectionReestablishment_v8a0_IEs* nonCriticalExtension_Set();
    int nonCriticalExtension_Set(RRCConnectionReestablishment_v8a0_IEs &value);
    const RRCConnectionReestablishment_v8a0_IEs& nonCriticalExtension_Get() const;
    std::string nonCriticalExtension_ToString(uint32_t indent) const;
    std::string nonCriticalExtension_ToStringNoNewLines() const;
    int nonCriticalExtension_Clear();
    bool nonCriticalExtension_IsPresent() const;
private:
    bool nonCriticalExtension_present;
    RRCConnectionReestablishment_v8a0_IEs nonCriticalExtension;

};

#endif
