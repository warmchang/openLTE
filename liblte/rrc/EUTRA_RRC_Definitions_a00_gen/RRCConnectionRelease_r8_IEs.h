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

#ifndef __RRCConnectionRelease_r8_IEs_H__
#define __RRCConnectionRelease_r8_IEs_H__

#include "ReleaseCause.h"
#include "RedirectedCarrierInfo.h"
#include "IdleModeMobilityControlInfo.h"
#include "RRCConnectionRelease_v890_IEs.h"

#include <array>
#include <cstdint>
#include <vector>

class RRCConnectionRelease_r8_IEs
{
public:
    RRCConnectionRelease_r8_IEs() : releaseCause_present{false}, redirectedCarrierInfo_present{false}, idleModeMobilityControlInfo_present{false}, nonCriticalExtension_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // releaseCause
public:
    ReleaseCause* releaseCause_Set();
    int releaseCause_Set(ReleaseCause &value);
    const ReleaseCause& releaseCause_Get() const;
    std::string releaseCause_ToString(uint32_t indent) const;
    std::string releaseCause_ToStringNoNewLines() const;
    int releaseCause_Clear();
    bool releaseCause_IsPresent() const;
private:
    bool releaseCause_present;
    ReleaseCause releaseCause;

    // redirectedCarrierInfo
public:
    RedirectedCarrierInfo* redirectedCarrierInfo_Set();
    int redirectedCarrierInfo_Set(RedirectedCarrierInfo &value);
    const RedirectedCarrierInfo& redirectedCarrierInfo_Get() const;
    std::string redirectedCarrierInfo_ToString(uint32_t indent) const;
    std::string redirectedCarrierInfo_ToStringNoNewLines() const;
    int redirectedCarrierInfo_Clear();
    bool redirectedCarrierInfo_IsPresent() const;
private:
    bool redirectedCarrierInfo_present;
    RedirectedCarrierInfo redirectedCarrierInfo;

    // idleModeMobilityControlInfo
public:
    IdleModeMobilityControlInfo* idleModeMobilityControlInfo_Set();
    int idleModeMobilityControlInfo_Set(IdleModeMobilityControlInfo &value);
    const IdleModeMobilityControlInfo& idleModeMobilityControlInfo_Get() const;
    std::string idleModeMobilityControlInfo_ToString(uint32_t indent) const;
    std::string idleModeMobilityControlInfo_ToStringNoNewLines() const;
    int idleModeMobilityControlInfo_Clear();
    bool idleModeMobilityControlInfo_IsPresent() const;
private:
    bool idleModeMobilityControlInfo_present;
    IdleModeMobilityControlInfo idleModeMobilityControlInfo;

    // nonCriticalExtension
public:
    RRCConnectionRelease_v890_IEs* nonCriticalExtension_Set();
    int nonCriticalExtension_Set(RRCConnectionRelease_v890_IEs &value);
    const RRCConnectionRelease_v890_IEs& nonCriticalExtension_Get() const;
    std::string nonCriticalExtension_ToString(uint32_t indent) const;
    std::string nonCriticalExtension_ToStringNoNewLines() const;
    int nonCriticalExtension_Clear();
    bool nonCriticalExtension_IsPresent() const;
private:
    bool nonCriticalExtension_present;
    RRCConnectionRelease_v890_IEs nonCriticalExtension;

};

#endif
