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

#include "MeasObjectGERAN.h"

#include <cmath>

int MeasObjectGERAN::Pack(std::vector<uint8_t> &bits)
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
    if(!ncc_Permitted_IsPresent() || ncc_Permitted_Value() == ncc_Permitted_GetDefault())
    {
        bits.push_back(0);
    }else{
        bits.push_back(1);
    }
    bits.push_back(cellForWhichToReportCGI_IsPresent());

    // Fields
    {
        if(0 != carrierFreqs.Pack(bits))
        {
            printf("MeasObjectGERAN:: field pack failure\n");
            return -1;
        }
    }
    if(offsetFreq_IsPresent() || offsetFreq_Get().Value() != offsetFreq_GetDefault())
    {
        if(0 != offsetFreq.Pack(bits))
        {
            printf("MeasObjectGERAN:: field pack failure\n");
            return -1;
        }
    }
    if(ncc_Permitted_IsPresent() || ncc_Permitted_Value() != ncc_Permitted_GetDefault())
    {
        if(0 != ncc_Permitted_Pack(bits))
        {
            printf("MeasObjectGERAN:: field pack failure\n");
            return -1;
        }
    }
    if(cellForWhichToReportCGI_IsPresent())
    {
        if(0 != cellForWhichToReportCGI.Pack(bits))
        {
            printf("MeasObjectGERAN:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int MeasObjectGERAN::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int MeasObjectGERAN::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("MeasObjectGERAN::Unpack() index out of bounds for extension\n");
        return -1;
    }
    idx++;

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("MeasObjectGERAN::Unpack() index out of bounds for optional indiator offsetFreq\n");
        return -1;
    }
    offsetFreq_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("MeasObjectGERAN::Unpack() index out of bounds for optional indiator ncc_Permitted\n");
        return -1;
    }
    ncc_Permitted_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("MeasObjectGERAN::Unpack() index out of bounds for optional indiator cellForWhichToReportCGI\n");
        return -1;
    }
    cellForWhichToReportCGI_present = bits[idx++];

    // Fields
    {
        if(0 != carrierFreqs.Unpack(bits, idx))
        {
            printf("MeasObjectGERAN:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != offsetFreq.Unpack(bits, idx))
        {
            printf("MeasObjectGERAN:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != ncc_Permitted_Unpack(bits, idx))
        {
            printf("MeasObjectGERAN:: field unpack failure\n");
            return -1;
        }
    }
    if(cellForWhichToReportCGI_present)
    {
        if(0 != cellForWhichToReportCGI.Unpack(bits, idx))
        {
            printf("MeasObjectGERAN:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string MeasObjectGERAN::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "MeasObjectGERAN:\n";
    out += carrierFreqs_ToString(indent+1);
    out += offsetFreq_ToString(indent+1);
    out += ncc_Permitted_ToString(indent+1);
    if(cellForWhichToReportCGI_IsPresent())
        out += cellForWhichToReportCGI_ToString(indent+1);
    return out;
}

std::string MeasObjectGERAN::ToStringNoNewLines() const
{
    std::string out = "MeasObjectGERAN:";
    out += carrierFreqs_ToStringNoNewLines();
    out += offsetFreq_ToStringNoNewLines();
    out += ncc_Permitted_ToStringNoNewLines();
    if(cellForWhichToReportCGI_IsPresent())
        out += cellForWhichToReportCGI_ToStringNoNewLines();
    return out;
}

CarrierFreqsGERAN* MeasObjectGERAN::carrierFreqs_Set()
{
    carrierFreqs_present = true;
    return &carrierFreqs;
}

int MeasObjectGERAN::carrierFreqs_Set(CarrierFreqsGERAN &value)
{
    carrierFreqs_present = true;
    carrierFreqs = value;
    return 0;
}

const CarrierFreqsGERAN& MeasObjectGERAN::carrierFreqs_Get() const
{
    return carrierFreqs;
}

std::string MeasObjectGERAN::carrierFreqs_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "carrierFreqs:\n";
    out += carrierFreqs.ToString(indent+1);
    return out;
}

std::string MeasObjectGERAN::carrierFreqs_ToStringNoNewLines() const
{
    std::string out = "carrierFreqs:";
    out += carrierFreqs.ToStringNoNewLines();
    return out;
}

int MeasObjectGERAN::carrierFreqs_Clear()
{
    carrierFreqs_present = false;
    return 0;
}

bool MeasObjectGERAN::carrierFreqs_IsPresent() const
{
    return carrierFreqs_present;
}

Q_OffsetRangeInterRAT* MeasObjectGERAN::offsetFreq_Set()
{
    offsetFreq_present = true;
    return &offsetFreq;
}

int MeasObjectGERAN::offsetFreq_Set(Q_OffsetRangeInterRAT &value)
{
    offsetFreq_present = true;
    offsetFreq = value;
    return 0;
}

const Q_OffsetRangeInterRAT& MeasObjectGERAN::offsetFreq_Get() const
{
    return offsetFreq;
}

int64_t MeasObjectGERAN::offsetFreq_GetDefault() const
{
    return 0;
}

std::string MeasObjectGERAN::offsetFreq_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "offsetFreq:\n";
    out += offsetFreq.ToString(indent+1);
    return out;
}

std::string MeasObjectGERAN::offsetFreq_ToStringNoNewLines() const
{
    std::string out = "offsetFreq:";
    out += offsetFreq.ToStringNoNewLines();
    return out;
}

int MeasObjectGERAN::offsetFreq_Clear()
{
    offsetFreq_present = false;
    return 0;
}

bool MeasObjectGERAN::offsetFreq_IsPresent() const
{
    return offsetFreq_present;
}

int MeasObjectGERAN::ncc_Permitted_Pack(std::vector<uint8_t> &bits)
{
    if(!ncc_Permitted_present)
    {
        ncc_Permitted_present = true;
        ncc_Permitted_internal_value = ncc_Permitted_GetDefault();
    }
    if(!ncc_Permitted_present)
    {
        printf("MeasObjectGERAN::ncc_Permitted_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 8;
    if(size < 8 || size > 8)
    {
        printf("MeasObjectGERAN::ncc_Permitted_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((ncc_Permitted_internal_value >> (8-i-1)) & 1);
    return 0;
}

int MeasObjectGERAN::ncc_Permitted_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return ncc_Permitted_Unpack(bits, idx);
}

int MeasObjectGERAN::ncc_Permitted_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 8;
    if(size < 8 || size > 8)
    {
        printf("MeasObjectGERAN::ncc_Permitted_Unpack() size failure\n");
        return -1;
    }
    ncc_Permitted_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("MeasObjectGERAN::ncc_Permitted_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        ncc_Permitted_internal_value |= (uint8_t)bits[idx++] << (uint8_t)(8-i-1);
    ncc_Permitted_present = true;
    return 0;
}

uint8_t MeasObjectGERAN::ncc_Permitted_Value() const
{
    if(ncc_Permitted_present)
        return ncc_Permitted_internal_value;
    uint8_t tmp = 0;
    return tmp;
}

int MeasObjectGERAN::ncc_Permitted_SetValue(uint8_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 8)
    {
        printf("MeasObjectGERAN::ncc_Permitted_SetValue() size failure\n");
        return -1;
    }
    ncc_Permitted_internal_value = value;
    ncc_Permitted_present = true;
    return 0;
}

uint8_t MeasObjectGERAN::ncc_Permitted_GetDefault() const
{
    return 255;
}

std::string MeasObjectGERAN::ncc_Permitted_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ncc_Permitted = ";
    out += std::to_string(ncc_Permitted_internal_value);
    out += "\n";
    return out;
}

std::string MeasObjectGERAN::ncc_Permitted_ToStringNoNewLines() const
{
    std::string out = "ncc_Permitted=";
    out += std::to_string(ncc_Permitted_internal_value);
    out += ",";
    return out;
}

int MeasObjectGERAN::ncc_Permitted_Clear()
{
    ncc_Permitted_present = false;
    return 0;
}

bool MeasObjectGERAN::ncc_Permitted_IsPresent() const
{
    return ncc_Permitted_present;
}

PhysCellIdGERAN* MeasObjectGERAN::cellForWhichToReportCGI_Set()
{
    cellForWhichToReportCGI_present = true;
    return &cellForWhichToReportCGI;
}

int MeasObjectGERAN::cellForWhichToReportCGI_Set(PhysCellIdGERAN &value)
{
    cellForWhichToReportCGI_present = true;
    cellForWhichToReportCGI = value;
    return 0;
}

const PhysCellIdGERAN& MeasObjectGERAN::cellForWhichToReportCGI_Get() const
{
    return cellForWhichToReportCGI;
}

std::string MeasObjectGERAN::cellForWhichToReportCGI_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cellForWhichToReportCGI:\n";
    out += cellForWhichToReportCGI.ToString(indent+1);
    return out;
}

std::string MeasObjectGERAN::cellForWhichToReportCGI_ToStringNoNewLines() const
{
    std::string out = "cellForWhichToReportCGI:";
    out += cellForWhichToReportCGI.ToStringNoNewLines();
    return out;
}

int MeasObjectGERAN::cellForWhichToReportCGI_Clear()
{
    cellForWhichToReportCGI_present = false;
    return 0;
}

bool MeasObjectGERAN::cellForWhichToReportCGI_IsPresent() const
{
    return cellForWhichToReportCGI_present;
}

