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

#ifndef __RRCConnectionReconfiguration_v10xy_IEs_H__
#define __RRCConnectionReconfiguration_v10xy_IEs_H__

#include "SCellToReleaseList_r10.h"
#include "SCellToAddModList_r10.h"

#include <array>
#include <cstdint>
#include <vector>

class RRCConnectionReconfiguration_v10xy_IEs
{
public:
    RRCConnectionReconfiguration_v10xy_IEs() : sCellToReleaseList_r10_present{false}, sCellToAddModList_r10_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // sCellToReleaseList-r10
public:
    SCellToReleaseList_r10* sCellToReleaseList_r10_Set();
    int sCellToReleaseList_r10_Set(SCellToReleaseList_r10 &value);
    const SCellToReleaseList_r10& sCellToReleaseList_r10_Get() const;
    std::string sCellToReleaseList_r10_ToString(uint32_t indent) const;
    std::string sCellToReleaseList_r10_ToStringNoNewLines() const;
    int sCellToReleaseList_r10_Clear();
    bool sCellToReleaseList_r10_IsPresent() const;
private:
    bool sCellToReleaseList_r10_present;
    SCellToReleaseList_r10 sCellToReleaseList_r10;

    // sCellToAddModList-r10
public:
    SCellToAddModList_r10* sCellToAddModList_r10_Set();
    int sCellToAddModList_r10_Set(SCellToAddModList_r10 &value);
    const SCellToAddModList_r10& sCellToAddModList_r10_Get() const;
    std::string sCellToAddModList_r10_ToString(uint32_t indent) const;
    std::string sCellToAddModList_r10_ToStringNoNewLines() const;
    int sCellToAddModList_r10_Clear();
    bool sCellToAddModList_r10_IsPresent() const;
private:
    bool sCellToAddModList_r10_present;
    SCellToAddModList_r10 sCellToAddModList_r10;

    // nonCriticalExtension

};

#endif
