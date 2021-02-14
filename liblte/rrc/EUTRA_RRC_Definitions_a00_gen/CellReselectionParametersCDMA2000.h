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

#ifndef __CellReselectionParametersCDMA2000_H__
#define __CellReselectionParametersCDMA2000_H__

#include "BandClassListCDMA2000.h"
#include "NeighCellListCDMA2000.h"
#include "T_Reselection.h"
#include "SpeedStateScaleFactors.h"

#include <array>
#include <cstdint>
#include <vector>

class CellReselectionParametersCDMA2000
{
public:
    CellReselectionParametersCDMA2000() : bandClassList_present{false}, neighCellList_present{false}, t_ReselectionCDMA2000_present{false}, t_ReselectionCDMA2000_SF_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // bandClassList
public:
    BandClassListCDMA2000* bandClassList_Set();
    int bandClassList_Set(BandClassListCDMA2000 &value);
    const BandClassListCDMA2000& bandClassList_Get() const;
    std::string bandClassList_ToString(uint32_t indent) const;
    std::string bandClassList_ToStringNoNewLines() const;
    int bandClassList_Clear();
    bool bandClassList_IsPresent() const;
private:
    bool bandClassList_present;
    BandClassListCDMA2000 bandClassList;

    // neighCellList
public:
    NeighCellListCDMA2000* neighCellList_Set();
    int neighCellList_Set(NeighCellListCDMA2000 &value);
    const NeighCellListCDMA2000& neighCellList_Get() const;
    std::string neighCellList_ToString(uint32_t indent) const;
    std::string neighCellList_ToStringNoNewLines() const;
    int neighCellList_Clear();
    bool neighCellList_IsPresent() const;
private:
    bool neighCellList_present;
    NeighCellListCDMA2000 neighCellList;

    // t-ReselectionCDMA2000
public:
    T_Reselection* t_ReselectionCDMA2000_Set();
    int t_ReselectionCDMA2000_Set(T_Reselection &value);
    const T_Reselection& t_ReselectionCDMA2000_Get() const;
    std::string t_ReselectionCDMA2000_ToString(uint32_t indent) const;
    std::string t_ReselectionCDMA2000_ToStringNoNewLines() const;
    int t_ReselectionCDMA2000_Clear();
    bool t_ReselectionCDMA2000_IsPresent() const;
private:
    bool t_ReselectionCDMA2000_present;
    T_Reselection t_ReselectionCDMA2000;

    // t-ReselectionCDMA2000-SF
public:
    SpeedStateScaleFactors* t_ReselectionCDMA2000_SF_Set();
    int t_ReselectionCDMA2000_SF_Set(SpeedStateScaleFactors &value);
    const SpeedStateScaleFactors& t_ReselectionCDMA2000_SF_Get() const;
    std::string t_ReselectionCDMA2000_SF_ToString(uint32_t indent) const;
    std::string t_ReselectionCDMA2000_SF_ToStringNoNewLines() const;
    int t_ReselectionCDMA2000_SF_Clear();
    bool t_ReselectionCDMA2000_SF_IsPresent() const;
private:
    bool t_ReselectionCDMA2000_SF_present;
    SpeedStateScaleFactors t_ReselectionCDMA2000_SF;

};

#endif
