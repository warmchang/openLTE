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

#ifndef __MeasObjectEUTRA_H__
#define __MeasObjectEUTRA_H__

#include "ARFCN_ValueEUTRA.h"
#include "AllowedMeasBandwidth.h"
#include "PresenceAntennaPort1.h"
#include "NeighCellConfig.h"
#include "Q_OffsetRange.h"
#include "CellIndexList.h"
#include "CellsToAddModList.h"
#include "CellIndexList.h"
#include "BlackCellsToAddModList.h"
#include "PhysCellId.h"

#include <array>
#include <cstdint>
#include <vector>

class MeasObjectEUTRA
{
public:
    MeasObjectEUTRA() : carrierFreq_present{false}, allowedMeasBandwidth_present{false}, presenceAntennaPort1_present{false}, neighCellConfig_present{false}, offsetFreq_present{false}, cellsToRemoveList_present{false}, cellsToAddModList_present{false}, blackCellsToRemoveList_present{false}, blackCellsToAddModList_present{false}, cellForWhichToReportCGI_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // carrierFreq
public:
    ARFCN_ValueEUTRA* carrierFreq_Set();
    int carrierFreq_Set(ARFCN_ValueEUTRA &value);
    const ARFCN_ValueEUTRA& carrierFreq_Get() const;
    std::string carrierFreq_ToString(uint32_t indent) const;
    std::string carrierFreq_ToStringNoNewLines() const;
    int carrierFreq_Clear();
    bool carrierFreq_IsPresent() const;
private:
    bool carrierFreq_present;
    ARFCN_ValueEUTRA carrierFreq;

    // allowedMeasBandwidth
public:
    AllowedMeasBandwidth* allowedMeasBandwidth_Set();
    int allowedMeasBandwidth_Set(AllowedMeasBandwidth &value);
    const AllowedMeasBandwidth& allowedMeasBandwidth_Get() const;
    std::string allowedMeasBandwidth_ToString(uint32_t indent) const;
    std::string allowedMeasBandwidth_ToStringNoNewLines() const;
    int allowedMeasBandwidth_Clear();
    bool allowedMeasBandwidth_IsPresent() const;
private:
    bool allowedMeasBandwidth_present;
    AllowedMeasBandwidth allowedMeasBandwidth;

    // presenceAntennaPort1
public:
    PresenceAntennaPort1* presenceAntennaPort1_Set();
    int presenceAntennaPort1_Set(PresenceAntennaPort1 &value);
    const PresenceAntennaPort1& presenceAntennaPort1_Get() const;
    std::string presenceAntennaPort1_ToString(uint32_t indent) const;
    std::string presenceAntennaPort1_ToStringNoNewLines() const;
    int presenceAntennaPort1_Clear();
    bool presenceAntennaPort1_IsPresent() const;
private:
    bool presenceAntennaPort1_present;
    PresenceAntennaPort1 presenceAntennaPort1;

    // neighCellConfig
public:
    NeighCellConfig* neighCellConfig_Set();
    int neighCellConfig_Set(NeighCellConfig &value);
    const NeighCellConfig& neighCellConfig_Get() const;
    std::string neighCellConfig_ToString(uint32_t indent) const;
    std::string neighCellConfig_ToStringNoNewLines() const;
    int neighCellConfig_Clear();
    bool neighCellConfig_IsPresent() const;
private:
    bool neighCellConfig_present;
    NeighCellConfig neighCellConfig;

    // offsetFreq
public:
    Q_OffsetRange* offsetFreq_Set();
    int offsetFreq_Set(Q_OffsetRange &value);
    const Q_OffsetRange& offsetFreq_Get() const;
    Q_OffsetRange::Enum offsetFreq_GetDefault() const;
    std::string offsetFreq_ToString(uint32_t indent) const;
    std::string offsetFreq_ToStringNoNewLines() const;
    int offsetFreq_Clear();
    bool offsetFreq_IsPresent() const;
private:
    bool offsetFreq_present;
    Q_OffsetRange offsetFreq;

    // cellsToRemoveList
public:
    CellIndexList* cellsToRemoveList_Set();
    int cellsToRemoveList_Set(CellIndexList &value);
    const CellIndexList& cellsToRemoveList_Get() const;
    std::string cellsToRemoveList_ToString(uint32_t indent) const;
    std::string cellsToRemoveList_ToStringNoNewLines() const;
    int cellsToRemoveList_Clear();
    bool cellsToRemoveList_IsPresent() const;
private:
    bool cellsToRemoveList_present;
    CellIndexList cellsToRemoveList;

    // cellsToAddModList
public:
    CellsToAddModList* cellsToAddModList_Set();
    int cellsToAddModList_Set(CellsToAddModList &value);
    const CellsToAddModList& cellsToAddModList_Get() const;
    std::string cellsToAddModList_ToString(uint32_t indent) const;
    std::string cellsToAddModList_ToStringNoNewLines() const;
    int cellsToAddModList_Clear();
    bool cellsToAddModList_IsPresent() const;
private:
    bool cellsToAddModList_present;
    CellsToAddModList cellsToAddModList;

    // blackCellsToRemoveList
public:
    CellIndexList* blackCellsToRemoveList_Set();
    int blackCellsToRemoveList_Set(CellIndexList &value);
    const CellIndexList& blackCellsToRemoveList_Get() const;
    std::string blackCellsToRemoveList_ToString(uint32_t indent) const;
    std::string blackCellsToRemoveList_ToStringNoNewLines() const;
    int blackCellsToRemoveList_Clear();
    bool blackCellsToRemoveList_IsPresent() const;
private:
    bool blackCellsToRemoveList_present;
    CellIndexList blackCellsToRemoveList;

    // blackCellsToAddModList
public:
    BlackCellsToAddModList* blackCellsToAddModList_Set();
    int blackCellsToAddModList_Set(BlackCellsToAddModList &value);
    const BlackCellsToAddModList& blackCellsToAddModList_Get() const;
    std::string blackCellsToAddModList_ToString(uint32_t indent) const;
    std::string blackCellsToAddModList_ToStringNoNewLines() const;
    int blackCellsToAddModList_Clear();
    bool blackCellsToAddModList_IsPresent() const;
private:
    bool blackCellsToAddModList_present;
    BlackCellsToAddModList blackCellsToAddModList;

    // cellForWhichToReportCGI
public:
    PhysCellId* cellForWhichToReportCGI_Set();
    int cellForWhichToReportCGI_Set(PhysCellId &value);
    const PhysCellId& cellForWhichToReportCGI_Get() const;
    std::string cellForWhichToReportCGI_ToString(uint32_t indent) const;
    std::string cellForWhichToReportCGI_ToStringNoNewLines() const;
    int cellForWhichToReportCGI_Clear();
    bool cellForWhichToReportCGI_IsPresent() const;
private:
    bool cellForWhichToReportCGI_present;
    PhysCellId cellForWhichToReportCGI;

};

#endif
