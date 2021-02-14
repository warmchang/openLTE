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

#include "MeasObjectEUTRA.h"

#include <cmath>

int MeasObjectEUTRA::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator
    bits.push_back(0);

    // Optional indicators
    if(!offsetFreq_IsPresent() || offsetFreq_Get().Value() == offsetFreq_GetDefault())
    {
        bits.push_back(0);
    }else{
        bits.push_back(1);
    }
    bits.push_back(cellsToRemoveList_IsPresent());
    bits.push_back(cellsToAddModList_IsPresent());
    bits.push_back(blackCellsToRemoveList_IsPresent());
    bits.push_back(blackCellsToAddModList_IsPresent());
    bits.push_back(cellForWhichToReportCGI_IsPresent());

    // Fields
    {
        if(0 != carrierFreq.Pack(bits))
        {
            printf("MeasObjectEUTRA:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != allowedMeasBandwidth.Pack(bits))
        {
            printf("MeasObjectEUTRA:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != presenceAntennaPort1.Pack(bits))
        {
            printf("MeasObjectEUTRA:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != neighCellConfig.Pack(bits))
        {
            printf("MeasObjectEUTRA:: field pack failure\n");
            return -1;
        }
    }
    if(offsetFreq_IsPresent() || offsetFreq_Get().Value() != offsetFreq_GetDefault())
    {
        if(0 != offsetFreq.Pack(bits))
        {
            printf("MeasObjectEUTRA:: field pack failure\n");
            return -1;
        }
    }
    if(cellsToRemoveList_IsPresent())
    {
        if(0 != cellsToRemoveList.Pack(bits))
        {
            printf("MeasObjectEUTRA:: field pack failure\n");
            return -1;
        }
    }
    if(cellsToAddModList_IsPresent())
    {
        if(0 != cellsToAddModList.Pack(bits))
        {
            printf("MeasObjectEUTRA:: field pack failure\n");
            return -1;
        }
    }
    if(blackCellsToRemoveList_IsPresent())
    {
        if(0 != blackCellsToRemoveList.Pack(bits))
        {
            printf("MeasObjectEUTRA:: field pack failure\n");
            return -1;
        }
    }
    if(blackCellsToAddModList_IsPresent())
    {
        if(0 != blackCellsToAddModList.Pack(bits))
        {
            printf("MeasObjectEUTRA:: field pack failure\n");
            return -1;
        }
    }
    if(cellForWhichToReportCGI_IsPresent())
    {
        if(0 != cellForWhichToReportCGI.Pack(bits))
        {
            printf("MeasObjectEUTRA:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int MeasObjectEUTRA::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int MeasObjectEUTRA::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("MeasObjectEUTRA::Unpack() index out of bounds for extension\n");
        return -1;
    }
    idx++;

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("MeasObjectEUTRA::Unpack() index out of bounds for optional indiator offsetFreq\n");
        return -1;
    }
    offsetFreq_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("MeasObjectEUTRA::Unpack() index out of bounds for optional indiator cellsToRemoveList\n");
        return -1;
    }
    cellsToRemoveList_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("MeasObjectEUTRA::Unpack() index out of bounds for optional indiator cellsToAddModList\n");
        return -1;
    }
    cellsToAddModList_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("MeasObjectEUTRA::Unpack() index out of bounds for optional indiator blackCellsToRemoveList\n");
        return -1;
    }
    blackCellsToRemoveList_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("MeasObjectEUTRA::Unpack() index out of bounds for optional indiator blackCellsToAddModList\n");
        return -1;
    }
    blackCellsToAddModList_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("MeasObjectEUTRA::Unpack() index out of bounds for optional indiator cellForWhichToReportCGI\n");
        return -1;
    }
    cellForWhichToReportCGI_present = bits[idx++];

    // Fields
    {
        if(0 != carrierFreq.Unpack(bits, idx))
        {
            printf("MeasObjectEUTRA:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != allowedMeasBandwidth.Unpack(bits, idx))
        {
            printf("MeasObjectEUTRA:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != presenceAntennaPort1.Unpack(bits, idx))
        {
            printf("MeasObjectEUTRA:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != neighCellConfig.Unpack(bits, idx))
        {
            printf("MeasObjectEUTRA:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != offsetFreq.Unpack(bits, idx))
        {
            printf("MeasObjectEUTRA:: field unpack failure\n");
            return -1;
        }
    }
    if(cellsToRemoveList_present)
    {
        if(0 != cellsToRemoveList.Unpack(bits, idx))
        {
            printf("MeasObjectEUTRA:: field unpack failure\n");
            return -1;
        }
    }
    if(cellsToAddModList_present)
    {
        if(0 != cellsToAddModList.Unpack(bits, idx))
        {
            printf("MeasObjectEUTRA:: field unpack failure\n");
            return -1;
        }
    }
    if(blackCellsToRemoveList_present)
    {
        if(0 != blackCellsToRemoveList.Unpack(bits, idx))
        {
            printf("MeasObjectEUTRA:: field unpack failure\n");
            return -1;
        }
    }
    if(blackCellsToAddModList_present)
    {
        if(0 != blackCellsToAddModList.Unpack(bits, idx))
        {
            printf("MeasObjectEUTRA:: field unpack failure\n");
            return -1;
        }
    }
    if(cellForWhichToReportCGI_present)
    {
        if(0 != cellForWhichToReportCGI.Unpack(bits, idx))
        {
            printf("MeasObjectEUTRA:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string MeasObjectEUTRA::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "MeasObjectEUTRA:\n";
    out += carrierFreq_ToString(indent+1);
    out += allowedMeasBandwidth_ToString(indent+1);
    out += presenceAntennaPort1_ToString(indent+1);
    out += neighCellConfig_ToString(indent+1);
    out += offsetFreq_ToString(indent+1);
    if(cellsToRemoveList_IsPresent())
        out += cellsToRemoveList_ToString(indent+1);
    if(cellsToAddModList_IsPresent())
        out += cellsToAddModList_ToString(indent+1);
    if(blackCellsToRemoveList_IsPresent())
        out += blackCellsToRemoveList_ToString(indent+1);
    if(blackCellsToAddModList_IsPresent())
        out += blackCellsToAddModList_ToString(indent+1);
    if(cellForWhichToReportCGI_IsPresent())
        out += cellForWhichToReportCGI_ToString(indent+1);
    return out;
}

std::string MeasObjectEUTRA::ToStringNoNewLines() const
{
    std::string out = "MeasObjectEUTRA:";
    out += carrierFreq_ToStringNoNewLines();
    out += allowedMeasBandwidth_ToStringNoNewLines();
    out += presenceAntennaPort1_ToStringNoNewLines();
    out += neighCellConfig_ToStringNoNewLines();
    out += offsetFreq_ToStringNoNewLines();
    if(cellsToRemoveList_IsPresent())
        out += cellsToRemoveList_ToStringNoNewLines();
    if(cellsToAddModList_IsPresent())
        out += cellsToAddModList_ToStringNoNewLines();
    if(blackCellsToRemoveList_IsPresent())
        out += blackCellsToRemoveList_ToStringNoNewLines();
    if(blackCellsToAddModList_IsPresent())
        out += blackCellsToAddModList_ToStringNoNewLines();
    if(cellForWhichToReportCGI_IsPresent())
        out += cellForWhichToReportCGI_ToStringNoNewLines();
    return out;
}

ARFCN_ValueEUTRA* MeasObjectEUTRA::carrierFreq_Set()
{
    carrierFreq_present = true;
    return &carrierFreq;
}

int MeasObjectEUTRA::carrierFreq_Set(ARFCN_ValueEUTRA &value)
{
    carrierFreq_present = true;
    carrierFreq = value;
    return 0;
}

const ARFCN_ValueEUTRA& MeasObjectEUTRA::carrierFreq_Get() const
{
    return carrierFreq;
}

std::string MeasObjectEUTRA::carrierFreq_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "carrierFreq:\n";
    out += carrierFreq.ToString(indent+1);
    return out;
}

std::string MeasObjectEUTRA::carrierFreq_ToStringNoNewLines() const
{
    std::string out = "carrierFreq:";
    out += carrierFreq.ToStringNoNewLines();
    return out;
}

int MeasObjectEUTRA::carrierFreq_Clear()
{
    carrierFreq_present = false;
    return 0;
}

bool MeasObjectEUTRA::carrierFreq_IsPresent() const
{
    return carrierFreq_present;
}

AllowedMeasBandwidth* MeasObjectEUTRA::allowedMeasBandwidth_Set()
{
    allowedMeasBandwidth_present = true;
    return &allowedMeasBandwidth;
}

int MeasObjectEUTRA::allowedMeasBandwidth_Set(AllowedMeasBandwidth &value)
{
    allowedMeasBandwidth_present = true;
    allowedMeasBandwidth = value;
    return 0;
}

const AllowedMeasBandwidth& MeasObjectEUTRA::allowedMeasBandwidth_Get() const
{
    return allowedMeasBandwidth;
}

std::string MeasObjectEUTRA::allowedMeasBandwidth_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "allowedMeasBandwidth:\n";
    out += allowedMeasBandwidth.ToString(indent+1);
    return out;
}

std::string MeasObjectEUTRA::allowedMeasBandwidth_ToStringNoNewLines() const
{
    std::string out = "allowedMeasBandwidth:";
    out += allowedMeasBandwidth.ToStringNoNewLines();
    return out;
}

int MeasObjectEUTRA::allowedMeasBandwidth_Clear()
{
    allowedMeasBandwidth_present = false;
    return 0;
}

bool MeasObjectEUTRA::allowedMeasBandwidth_IsPresent() const
{
    return allowedMeasBandwidth_present;
}

PresenceAntennaPort1* MeasObjectEUTRA::presenceAntennaPort1_Set()
{
    presenceAntennaPort1_present = true;
    return &presenceAntennaPort1;
}

int MeasObjectEUTRA::presenceAntennaPort1_Set(PresenceAntennaPort1 &value)
{
    presenceAntennaPort1_present = true;
    presenceAntennaPort1 = value;
    return 0;
}

const PresenceAntennaPort1& MeasObjectEUTRA::presenceAntennaPort1_Get() const
{
    return presenceAntennaPort1;
}

std::string MeasObjectEUTRA::presenceAntennaPort1_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "presenceAntennaPort1:\n";
    out += presenceAntennaPort1.ToString(indent+1);
    return out;
}

std::string MeasObjectEUTRA::presenceAntennaPort1_ToStringNoNewLines() const
{
    std::string out = "presenceAntennaPort1:";
    out += presenceAntennaPort1.ToStringNoNewLines();
    return out;
}

int MeasObjectEUTRA::presenceAntennaPort1_Clear()
{
    presenceAntennaPort1_present = false;
    return 0;
}

bool MeasObjectEUTRA::presenceAntennaPort1_IsPresent() const
{
    return presenceAntennaPort1_present;
}

NeighCellConfig* MeasObjectEUTRA::neighCellConfig_Set()
{
    neighCellConfig_present = true;
    return &neighCellConfig;
}

int MeasObjectEUTRA::neighCellConfig_Set(NeighCellConfig &value)
{
    neighCellConfig_present = true;
    neighCellConfig = value;
    return 0;
}

const NeighCellConfig& MeasObjectEUTRA::neighCellConfig_Get() const
{
    return neighCellConfig;
}

std::string MeasObjectEUTRA::neighCellConfig_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "neighCellConfig:\n";
    out += neighCellConfig.ToString(indent+1);
    return out;
}

std::string MeasObjectEUTRA::neighCellConfig_ToStringNoNewLines() const
{
    std::string out = "neighCellConfig:";
    out += neighCellConfig.ToStringNoNewLines();
    return out;
}

int MeasObjectEUTRA::neighCellConfig_Clear()
{
    neighCellConfig_present = false;
    return 0;
}

bool MeasObjectEUTRA::neighCellConfig_IsPresent() const
{
    return neighCellConfig_present;
}

Q_OffsetRange* MeasObjectEUTRA::offsetFreq_Set()
{
    offsetFreq_present = true;
    return &offsetFreq;
}

int MeasObjectEUTRA::offsetFreq_Set(Q_OffsetRange &value)
{
    offsetFreq_present = true;
    offsetFreq = value;
    return 0;
}

const Q_OffsetRange& MeasObjectEUTRA::offsetFreq_Get() const
{
    return offsetFreq;
}

Q_OffsetRange::Enum MeasObjectEUTRA::offsetFreq_GetDefault() const
{
    return Q_OffsetRange::k_dB0;
}

std::string MeasObjectEUTRA::offsetFreq_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "offsetFreq:\n";
    out += offsetFreq.ToString(indent+1);
    return out;
}

std::string MeasObjectEUTRA::offsetFreq_ToStringNoNewLines() const
{
    std::string out = "offsetFreq:";
    out += offsetFreq.ToStringNoNewLines();
    return out;
}

int MeasObjectEUTRA::offsetFreq_Clear()
{
    offsetFreq_present = false;
    return 0;
}

bool MeasObjectEUTRA::offsetFreq_IsPresent() const
{
    return offsetFreq_present;
}

CellIndexList* MeasObjectEUTRA::cellsToRemoveList_Set()
{
    cellsToRemoveList_present = true;
    return &cellsToRemoveList;
}

int MeasObjectEUTRA::cellsToRemoveList_Set(CellIndexList &value)
{
    cellsToRemoveList_present = true;
    cellsToRemoveList = value;
    return 0;
}

const CellIndexList& MeasObjectEUTRA::cellsToRemoveList_Get() const
{
    return cellsToRemoveList;
}

std::string MeasObjectEUTRA::cellsToRemoveList_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cellsToRemoveList:\n";
    out += cellsToRemoveList.ToString(indent+1);
    return out;
}

std::string MeasObjectEUTRA::cellsToRemoveList_ToStringNoNewLines() const
{
    std::string out = "cellsToRemoveList:";
    out += cellsToRemoveList.ToStringNoNewLines();
    return out;
}

int MeasObjectEUTRA::cellsToRemoveList_Clear()
{
    cellsToRemoveList_present = false;
    return 0;
}

bool MeasObjectEUTRA::cellsToRemoveList_IsPresent() const
{
    return cellsToRemoveList_present;
}

CellsToAddModList* MeasObjectEUTRA::cellsToAddModList_Set()
{
    cellsToAddModList_present = true;
    return &cellsToAddModList;
}

int MeasObjectEUTRA::cellsToAddModList_Set(CellsToAddModList &value)
{
    cellsToAddModList_present = true;
    cellsToAddModList = value;
    return 0;
}

const CellsToAddModList& MeasObjectEUTRA::cellsToAddModList_Get() const
{
    return cellsToAddModList;
}

std::string MeasObjectEUTRA::cellsToAddModList_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cellsToAddModList:\n";
    out += cellsToAddModList.ToString(indent+1);
    return out;
}

std::string MeasObjectEUTRA::cellsToAddModList_ToStringNoNewLines() const
{
    std::string out = "cellsToAddModList:";
    out += cellsToAddModList.ToStringNoNewLines();
    return out;
}

int MeasObjectEUTRA::cellsToAddModList_Clear()
{
    cellsToAddModList_present = false;
    return 0;
}

bool MeasObjectEUTRA::cellsToAddModList_IsPresent() const
{
    return cellsToAddModList_present;
}

CellIndexList* MeasObjectEUTRA::blackCellsToRemoveList_Set()
{
    blackCellsToRemoveList_present = true;
    return &blackCellsToRemoveList;
}

int MeasObjectEUTRA::blackCellsToRemoveList_Set(CellIndexList &value)
{
    blackCellsToRemoveList_present = true;
    blackCellsToRemoveList = value;
    return 0;
}

const CellIndexList& MeasObjectEUTRA::blackCellsToRemoveList_Get() const
{
    return blackCellsToRemoveList;
}

std::string MeasObjectEUTRA::blackCellsToRemoveList_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "blackCellsToRemoveList:\n";
    out += blackCellsToRemoveList.ToString(indent+1);
    return out;
}

std::string MeasObjectEUTRA::blackCellsToRemoveList_ToStringNoNewLines() const
{
    std::string out = "blackCellsToRemoveList:";
    out += blackCellsToRemoveList.ToStringNoNewLines();
    return out;
}

int MeasObjectEUTRA::blackCellsToRemoveList_Clear()
{
    blackCellsToRemoveList_present = false;
    return 0;
}

bool MeasObjectEUTRA::blackCellsToRemoveList_IsPresent() const
{
    return blackCellsToRemoveList_present;
}

BlackCellsToAddModList* MeasObjectEUTRA::blackCellsToAddModList_Set()
{
    blackCellsToAddModList_present = true;
    return &blackCellsToAddModList;
}

int MeasObjectEUTRA::blackCellsToAddModList_Set(BlackCellsToAddModList &value)
{
    blackCellsToAddModList_present = true;
    blackCellsToAddModList = value;
    return 0;
}

const BlackCellsToAddModList& MeasObjectEUTRA::blackCellsToAddModList_Get() const
{
    return blackCellsToAddModList;
}

std::string MeasObjectEUTRA::blackCellsToAddModList_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "blackCellsToAddModList:\n";
    out += blackCellsToAddModList.ToString(indent+1);
    return out;
}

std::string MeasObjectEUTRA::blackCellsToAddModList_ToStringNoNewLines() const
{
    std::string out = "blackCellsToAddModList:";
    out += blackCellsToAddModList.ToStringNoNewLines();
    return out;
}

int MeasObjectEUTRA::blackCellsToAddModList_Clear()
{
    blackCellsToAddModList_present = false;
    return 0;
}

bool MeasObjectEUTRA::blackCellsToAddModList_IsPresent() const
{
    return blackCellsToAddModList_present;
}

PhysCellId* MeasObjectEUTRA::cellForWhichToReportCGI_Set()
{
    cellForWhichToReportCGI_present = true;
    return &cellForWhichToReportCGI;
}

int MeasObjectEUTRA::cellForWhichToReportCGI_Set(PhysCellId &value)
{
    cellForWhichToReportCGI_present = true;
    cellForWhichToReportCGI = value;
    return 0;
}

const PhysCellId& MeasObjectEUTRA::cellForWhichToReportCGI_Get() const
{
    return cellForWhichToReportCGI;
}

std::string MeasObjectEUTRA::cellForWhichToReportCGI_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cellForWhichToReportCGI:\n";
    out += cellForWhichToReportCGI.ToString(indent+1);
    return out;
}

std::string MeasObjectEUTRA::cellForWhichToReportCGI_ToStringNoNewLines() const
{
    std::string out = "cellForWhichToReportCGI:";
    out += cellForWhichToReportCGI.ToStringNoNewLines();
    return out;
}

int MeasObjectEUTRA::cellForWhichToReportCGI_Clear()
{
    cellForWhichToReportCGI_present = false;
    return 0;
}

bool MeasObjectEUTRA::cellForWhichToReportCGI_IsPresent() const
{
    return cellForWhichToReportCGI_present;
}

