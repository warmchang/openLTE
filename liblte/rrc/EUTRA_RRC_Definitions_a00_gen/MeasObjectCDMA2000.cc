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

#include "MeasObjectCDMA2000.h"

#include <cmath>

int MeasObjectCDMA2000::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator
    bits.push_back(0);

    // Optional indicators
    bits.push_back(searchWindowSize_IsPresent());
    if(!offsetFreq_IsPresent() || offsetFreq_Get().Value() == offsetFreq_GetDefault())
    {
        bits.push_back(0);
    }else{
        bits.push_back(1);
    }
    bits.push_back(cellsToRemoveList_IsPresent());
    bits.push_back(cellsToAddModList_IsPresent());
    bits.push_back(cellForWhichToReportCGI_IsPresent());

    // Fields
    {
        if(0 != cdma2000_Type.Pack(bits))
        {
            printf("MeasObjectCDMA2000:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != carrierFreq.Pack(bits))
        {
            printf("MeasObjectCDMA2000:: field pack failure\n");
            return -1;
        }
    }
    if(searchWindowSize_IsPresent())
    {
        if(0 != searchWindowSize_Pack(bits))
        {
            printf("MeasObjectCDMA2000:: field pack failure\n");
            return -1;
        }
    }
    if(offsetFreq_IsPresent() || offsetFreq_Get().Value() != offsetFreq_GetDefault())
    {
        if(0 != offsetFreq.Pack(bits))
        {
            printf("MeasObjectCDMA2000:: field pack failure\n");
            return -1;
        }
    }
    if(cellsToRemoveList_IsPresent())
    {
        if(0 != cellsToRemoveList.Pack(bits))
        {
            printf("MeasObjectCDMA2000:: field pack failure\n");
            return -1;
        }
    }
    if(cellsToAddModList_IsPresent())
    {
        if(0 != cellsToAddModList.Pack(bits))
        {
            printf("MeasObjectCDMA2000:: field pack failure\n");
            return -1;
        }
    }
    if(cellForWhichToReportCGI_IsPresent())
    {
        if(0 != cellForWhichToReportCGI.Pack(bits))
        {
            printf("MeasObjectCDMA2000:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int MeasObjectCDMA2000::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int MeasObjectCDMA2000::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("MeasObjectCDMA2000::Unpack() index out of bounds for extension\n");
        return -1;
    }
    idx++;

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("MeasObjectCDMA2000::Unpack() index out of bounds for optional indiator searchWindowSize\n");
        return -1;
    }
    searchWindowSize_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("MeasObjectCDMA2000::Unpack() index out of bounds for optional indiator offsetFreq\n");
        return -1;
    }
    offsetFreq_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("MeasObjectCDMA2000::Unpack() index out of bounds for optional indiator cellsToRemoveList\n");
        return -1;
    }
    cellsToRemoveList_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("MeasObjectCDMA2000::Unpack() index out of bounds for optional indiator cellsToAddModList\n");
        return -1;
    }
    cellsToAddModList_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("MeasObjectCDMA2000::Unpack() index out of bounds for optional indiator cellForWhichToReportCGI\n");
        return -1;
    }
    cellForWhichToReportCGI_present = bits[idx++];

    // Fields
    {
        if(0 != cdma2000_Type.Unpack(bits, idx))
        {
            printf("MeasObjectCDMA2000:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != carrierFreq.Unpack(bits, idx))
        {
            printf("MeasObjectCDMA2000:: field unpack failure\n");
            return -1;
        }
    }
    if(searchWindowSize_present)
    {
        if(0 != searchWindowSize_Unpack(bits, idx))
        {
            printf("MeasObjectCDMA2000:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != offsetFreq.Unpack(bits, idx))
        {
            printf("MeasObjectCDMA2000:: field unpack failure\n");
            return -1;
        }
    }
    if(cellsToRemoveList_present)
    {
        if(0 != cellsToRemoveList.Unpack(bits, idx))
        {
            printf("MeasObjectCDMA2000:: field unpack failure\n");
            return -1;
        }
    }
    if(cellsToAddModList_present)
    {
        if(0 != cellsToAddModList.Unpack(bits, idx))
        {
            printf("MeasObjectCDMA2000:: field unpack failure\n");
            return -1;
        }
    }
    if(cellForWhichToReportCGI_present)
    {
        if(0 != cellForWhichToReportCGI.Unpack(bits, idx))
        {
            printf("MeasObjectCDMA2000:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string MeasObjectCDMA2000::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "MeasObjectCDMA2000:\n";
    out += cdma2000_Type_ToString(indent+1);
    out += carrierFreq_ToString(indent+1);
    if(searchWindowSize_IsPresent())
        out += searchWindowSize_ToString(indent+1);
    out += offsetFreq_ToString(indent+1);
    if(cellsToRemoveList_IsPresent())
        out += cellsToRemoveList_ToString(indent+1);
    if(cellsToAddModList_IsPresent())
        out += cellsToAddModList_ToString(indent+1);
    if(cellForWhichToReportCGI_IsPresent())
        out += cellForWhichToReportCGI_ToString(indent+1);
    return out;
}

std::string MeasObjectCDMA2000::ToStringNoNewLines() const
{
    std::string out = "MeasObjectCDMA2000:";
    out += cdma2000_Type_ToStringNoNewLines();
    out += carrierFreq_ToStringNoNewLines();
    if(searchWindowSize_IsPresent())
        out += searchWindowSize_ToStringNoNewLines();
    out += offsetFreq_ToStringNoNewLines();
    if(cellsToRemoveList_IsPresent())
        out += cellsToRemoveList_ToStringNoNewLines();
    if(cellsToAddModList_IsPresent())
        out += cellsToAddModList_ToStringNoNewLines();
    if(cellForWhichToReportCGI_IsPresent())
        out += cellForWhichToReportCGI_ToStringNoNewLines();
    return out;
}

CDMA2000_Type* MeasObjectCDMA2000::cdma2000_Type_Set()
{
    cdma2000_Type_present = true;
    return &cdma2000_Type;
}

int MeasObjectCDMA2000::cdma2000_Type_Set(CDMA2000_Type &value)
{
    cdma2000_Type_present = true;
    cdma2000_Type = value;
    return 0;
}

const CDMA2000_Type& MeasObjectCDMA2000::cdma2000_Type_Get() const
{
    return cdma2000_Type;
}

std::string MeasObjectCDMA2000::cdma2000_Type_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cdma2000_Type:\n";
    out += cdma2000_Type.ToString(indent+1);
    return out;
}

std::string MeasObjectCDMA2000::cdma2000_Type_ToStringNoNewLines() const
{
    std::string out = "cdma2000_Type:";
    out += cdma2000_Type.ToStringNoNewLines();
    return out;
}

int MeasObjectCDMA2000::cdma2000_Type_Clear()
{
    cdma2000_Type_present = false;
    return 0;
}

bool MeasObjectCDMA2000::cdma2000_Type_IsPresent() const
{
    return cdma2000_Type_present;
}

CarrierFreqCDMA2000* MeasObjectCDMA2000::carrierFreq_Set()
{
    carrierFreq_present = true;
    return &carrierFreq;
}

int MeasObjectCDMA2000::carrierFreq_Set(CarrierFreqCDMA2000 &value)
{
    carrierFreq_present = true;
    carrierFreq = value;
    return 0;
}

const CarrierFreqCDMA2000& MeasObjectCDMA2000::carrierFreq_Get() const
{
    return carrierFreq;
}

std::string MeasObjectCDMA2000::carrierFreq_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "carrierFreq:\n";
    out += carrierFreq.ToString(indent+1);
    return out;
}

std::string MeasObjectCDMA2000::carrierFreq_ToStringNoNewLines() const
{
    std::string out = "carrierFreq:";
    out += carrierFreq.ToStringNoNewLines();
    return out;
}

int MeasObjectCDMA2000::carrierFreq_Clear()
{
    carrierFreq_present = false;
    return 0;
}

bool MeasObjectCDMA2000::carrierFreq_IsPresent() const
{
    return carrierFreq_present;
}

int MeasObjectCDMA2000::searchWindowSize_Pack(std::vector<uint8_t> &bits)
{
    int64_t val_to_pack = searchWindowSize_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (15 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int MeasObjectCDMA2000::searchWindowSize_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return searchWindowSize_Unpack(bits, idx);
}

int MeasObjectCDMA2000::searchWindowSize_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (15 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("MeasObjectCDMA2000::searchWindowSize_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    searchWindowSize_internal_value = packed_val + 0;
    searchWindowSize_present = true;
    return 0;
}

int64_t MeasObjectCDMA2000::searchWindowSize_Value() const
{
    if(searchWindowSize_present)
        return searchWindowSize_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int MeasObjectCDMA2000::searchWindowSize_SetValue(int64_t value)
{
    if(value < 0 || value > 15)
    {
        printf("MeasObjectCDMA2000::searchWindowSize_SetValue() range failure\n");
        return -1;
    }
    searchWindowSize_internal_value = value;
    searchWindowSize_present = true;
    return 0;
}

std::string MeasObjectCDMA2000::searchWindowSize_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "searchWindowSize = " + std::to_string(searchWindowSize_internal_value) + "\n";
    return out;
}

std::string MeasObjectCDMA2000::searchWindowSize_ToStringNoNewLines() const
{
    std::string out = "searchWindowSize=" + std::to_string(searchWindowSize_internal_value) + ",";
    return out;
}

int MeasObjectCDMA2000::searchWindowSize_Clear()
{
    searchWindowSize_present = false;
    return 0;
}

bool MeasObjectCDMA2000::searchWindowSize_IsPresent() const
{
    return searchWindowSize_present;
}

Q_OffsetRangeInterRAT* MeasObjectCDMA2000::offsetFreq_Set()
{
    offsetFreq_present = true;
    return &offsetFreq;
}

int MeasObjectCDMA2000::offsetFreq_Set(Q_OffsetRangeInterRAT &value)
{
    offsetFreq_present = true;
    offsetFreq = value;
    return 0;
}

const Q_OffsetRangeInterRAT& MeasObjectCDMA2000::offsetFreq_Get() const
{
    return offsetFreq;
}

int64_t MeasObjectCDMA2000::offsetFreq_GetDefault() const
{
    return 0;
}

std::string MeasObjectCDMA2000::offsetFreq_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "offsetFreq:\n";
    out += offsetFreq.ToString(indent+1);
    return out;
}

std::string MeasObjectCDMA2000::offsetFreq_ToStringNoNewLines() const
{
    std::string out = "offsetFreq:";
    out += offsetFreq.ToStringNoNewLines();
    return out;
}

int MeasObjectCDMA2000::offsetFreq_Clear()
{
    offsetFreq_present = false;
    return 0;
}

bool MeasObjectCDMA2000::offsetFreq_IsPresent() const
{
    return offsetFreq_present;
}

CellIndexList* MeasObjectCDMA2000::cellsToRemoveList_Set()
{
    cellsToRemoveList_present = true;
    return &cellsToRemoveList;
}

int MeasObjectCDMA2000::cellsToRemoveList_Set(CellIndexList &value)
{
    cellsToRemoveList_present = true;
    cellsToRemoveList = value;
    return 0;
}

const CellIndexList& MeasObjectCDMA2000::cellsToRemoveList_Get() const
{
    return cellsToRemoveList;
}

std::string MeasObjectCDMA2000::cellsToRemoveList_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cellsToRemoveList:\n";
    out += cellsToRemoveList.ToString(indent+1);
    return out;
}

std::string MeasObjectCDMA2000::cellsToRemoveList_ToStringNoNewLines() const
{
    std::string out = "cellsToRemoveList:";
    out += cellsToRemoveList.ToStringNoNewLines();
    return out;
}

int MeasObjectCDMA2000::cellsToRemoveList_Clear()
{
    cellsToRemoveList_present = false;
    return 0;
}

bool MeasObjectCDMA2000::cellsToRemoveList_IsPresent() const
{
    return cellsToRemoveList_present;
}

CellsToAddModListCDMA2000* MeasObjectCDMA2000::cellsToAddModList_Set()
{
    cellsToAddModList_present = true;
    return &cellsToAddModList;
}

int MeasObjectCDMA2000::cellsToAddModList_Set(CellsToAddModListCDMA2000 &value)
{
    cellsToAddModList_present = true;
    cellsToAddModList = value;
    return 0;
}

const CellsToAddModListCDMA2000& MeasObjectCDMA2000::cellsToAddModList_Get() const
{
    return cellsToAddModList;
}

std::string MeasObjectCDMA2000::cellsToAddModList_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cellsToAddModList:\n";
    out += cellsToAddModList.ToString(indent+1);
    return out;
}

std::string MeasObjectCDMA2000::cellsToAddModList_ToStringNoNewLines() const
{
    std::string out = "cellsToAddModList:";
    out += cellsToAddModList.ToStringNoNewLines();
    return out;
}

int MeasObjectCDMA2000::cellsToAddModList_Clear()
{
    cellsToAddModList_present = false;
    return 0;
}

bool MeasObjectCDMA2000::cellsToAddModList_IsPresent() const
{
    return cellsToAddModList_present;
}

PhysCellIdCDMA2000* MeasObjectCDMA2000::cellForWhichToReportCGI_Set()
{
    cellForWhichToReportCGI_present = true;
    return &cellForWhichToReportCGI;
}

int MeasObjectCDMA2000::cellForWhichToReportCGI_Set(PhysCellIdCDMA2000 &value)
{
    cellForWhichToReportCGI_present = true;
    cellForWhichToReportCGI = value;
    return 0;
}

const PhysCellIdCDMA2000& MeasObjectCDMA2000::cellForWhichToReportCGI_Get() const
{
    return cellForWhichToReportCGI;
}

std::string MeasObjectCDMA2000::cellForWhichToReportCGI_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cellForWhichToReportCGI:\n";
    out += cellForWhichToReportCGI.ToString(indent+1);
    return out;
}

std::string MeasObjectCDMA2000::cellForWhichToReportCGI_ToStringNoNewLines() const
{
    std::string out = "cellForWhichToReportCGI:";
    out += cellForWhichToReportCGI.ToStringNoNewLines();
    return out;
}

int MeasObjectCDMA2000::cellForWhichToReportCGI_Clear()
{
    cellForWhichToReportCGI_present = false;
    return 0;
}

bool MeasObjectCDMA2000::cellForWhichToReportCGI_IsPresent() const
{
    return cellForWhichToReportCGI_present;
}

