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

#ifndef __AreaConfiguration_r10_H__
#define __AreaConfiguration_r10_H__

#include "CellGlobalIdList_r10.h"
#include "TrackingAreaCodeList_r10.h"

#include <array>
#include <cstdint>
#include <vector>

class AreaConfiguration_r10
{
public:
    enum Enum {
        k_cellGlobalIdList_r10 = 0,
        k_trackingAreaCodeList_r10,
    };
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    Enum Choice() const;
    int SetChoice(Enum choice);
    std::string ChoiceToString(Enum value) const;
    uint64_t NumberOfChoices() const;
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;
    int Clear();
    bool IsPresent() const;
private:
    bool present;
    Enum internal_choice;

    // cellGlobalIdList-r10
public:
    CellGlobalIdList_r10* cellGlobalIdList_r10_Set();
    int cellGlobalIdList_r10_Set(CellGlobalIdList_r10 &value);
    const CellGlobalIdList_r10& cellGlobalIdList_r10_Get() const;
    std::string cellGlobalIdList_r10_ToString(uint32_t indent) const;
    std::string cellGlobalIdList_r10_ToStringNoNewLines() const;
    int cellGlobalIdList_r10_Clear();
    bool cellGlobalIdList_r10_IsPresent() const;
private:
    bool cellGlobalIdList_r10_present;
    CellGlobalIdList_r10 cellGlobalIdList_r10;

    // trackingAreaCodeList-r10
public:
    TrackingAreaCodeList_r10* trackingAreaCodeList_r10_Set();
    int trackingAreaCodeList_r10_Set(TrackingAreaCodeList_r10 &value);
    const TrackingAreaCodeList_r10& trackingAreaCodeList_r10_Get() const;
    std::string trackingAreaCodeList_r10_ToString(uint32_t indent) const;
    std::string trackingAreaCodeList_r10_ToStringNoNewLines() const;
    int trackingAreaCodeList_r10_Clear();
    bool trackingAreaCodeList_r10_IsPresent() const;
private:
    bool trackingAreaCodeList_r10_present;
    TrackingAreaCodeList_r10 trackingAreaCodeList_r10;

};

#endif
