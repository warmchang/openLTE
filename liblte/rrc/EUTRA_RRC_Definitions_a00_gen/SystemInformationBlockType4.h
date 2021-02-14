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

#ifndef __SystemInformationBlockType4_H__
#define __SystemInformationBlockType4_H__

#include "IntraFreqNeighCellList.h"
#include "IntraFreqBlackCellList.h"
#include "PhysCellIdRange.h"

#include <array>
#include <cstdint>
#include <vector>

class SystemInformationBlockType4
{
public:
    SystemInformationBlockType4() : intraFreqNeighCellList_present{false}, intraFreqBlackCellList_present{false}, csg_PhysCellIdRange_present{false}, lateNonCriticalExtension_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // intraFreqNeighCellList
public:
    IntraFreqNeighCellList* intraFreqNeighCellList_Set();
    int intraFreqNeighCellList_Set(IntraFreqNeighCellList &value);
    const IntraFreqNeighCellList& intraFreqNeighCellList_Get() const;
    std::string intraFreqNeighCellList_ToString(uint32_t indent) const;
    std::string intraFreqNeighCellList_ToStringNoNewLines() const;
    int intraFreqNeighCellList_Clear();
    bool intraFreqNeighCellList_IsPresent() const;
private:
    bool intraFreqNeighCellList_present;
    IntraFreqNeighCellList intraFreqNeighCellList;

    // intraFreqBlackCellList
public:
    IntraFreqBlackCellList* intraFreqBlackCellList_Set();
    int intraFreqBlackCellList_Set(IntraFreqBlackCellList &value);
    const IntraFreqBlackCellList& intraFreqBlackCellList_Get() const;
    std::string intraFreqBlackCellList_ToString(uint32_t indent) const;
    std::string intraFreqBlackCellList_ToStringNoNewLines() const;
    int intraFreqBlackCellList_Clear();
    bool intraFreqBlackCellList_IsPresent() const;
private:
    bool intraFreqBlackCellList_present;
    IntraFreqBlackCellList intraFreqBlackCellList;

    // csg-PhysCellIdRange
public:
    PhysCellIdRange* csg_PhysCellIdRange_Set();
    int csg_PhysCellIdRange_Set(PhysCellIdRange &value);
    const PhysCellIdRange& csg_PhysCellIdRange_Get() const;
    std::string csg_PhysCellIdRange_ToString(uint32_t indent) const;
    std::string csg_PhysCellIdRange_ToStringNoNewLines() const;
    int csg_PhysCellIdRange_Clear();
    bool csg_PhysCellIdRange_IsPresent() const;
private:
    bool csg_PhysCellIdRange_present;
    PhysCellIdRange csg_PhysCellIdRange;

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
