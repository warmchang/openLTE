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

#include "MDT_MeasurementInfo_r10.h"

#include <cmath>

int MDT_MeasurementInfo_r10::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator
    bits.push_back(0);

    // Optional indicators
    bits.push_back(locationInfo_r10_IsPresent());
    bits.push_back(measResultNeighCells_IsPresent());

    // Fields
    if(locationInfo_r10_IsPresent())
    {
        if(0 != locationInfo_r10.Pack(bits))
        {
            printf("MDT_MeasurementInfo_r10:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != relativeTimeStamp_r10_Pack(bits))
        {
            printf("MDT_MeasurementInfo_r10:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != servCellIdentity_r10.Pack(bits))
        {
            printf("MDT_MeasurementInfo_r10:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != servCarrierFreq_r10.Pack(bits))
        {
            printf("MDT_MeasurementInfo_r10:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != measResultServCell_r10_value.Pack(bits))
        {
            printf("MDT_MeasurementInfo_r10:: field pack failure\n");
            return -1;
        }
    }
    if(measResultNeighCells_IsPresent())
    {
        if(0 != measResultNeighCells.Pack(bits))
        {
            printf("MDT_MeasurementInfo_r10:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int MDT_MeasurementInfo_r10::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int MDT_MeasurementInfo_r10::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("MDT_MeasurementInfo_r10::Unpack() index out of bounds for extension\n");
        return -1;
    }
    idx++;

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("MDT_MeasurementInfo_r10::Unpack() index out of bounds for optional indiator locationInfo_r10\n");
        return -1;
    }
    locationInfo_r10_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("MDT_MeasurementInfo_r10::Unpack() index out of bounds for optional indiator measResultNeighCells\n");
        return -1;
    }
    measResultNeighCells_present = bits[idx++];

    // Fields
    if(locationInfo_r10_present)
    {
        if(0 != locationInfo_r10.Unpack(bits, idx))
        {
            printf("MDT_MeasurementInfo_r10:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != relativeTimeStamp_r10_Unpack(bits, idx))
        {
            printf("MDT_MeasurementInfo_r10:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != servCellIdentity_r10.Unpack(bits, idx))
        {
            printf("MDT_MeasurementInfo_r10:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != servCarrierFreq_r10.Unpack(bits, idx))
        {
            printf("MDT_MeasurementInfo_r10:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != measResultServCell_r10_value.Unpack(bits, idx))
        {
            printf("MDT_MeasurementInfo_r10:: field unpack failure\n");
            return -1;
        }
    }
    if(measResultNeighCells_present)
    {
        if(0 != measResultNeighCells.Unpack(bits, idx))
        {
            printf("MDT_MeasurementInfo_r10:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string MDT_MeasurementInfo_r10::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "MDT_MeasurementInfo_r10:\n";
    if(locationInfo_r10_IsPresent())
        out += locationInfo_r10_ToString(indent+1);
    out += relativeTimeStamp_r10_ToString(indent+1);
    out += servCellIdentity_r10_ToString(indent+1);
    out += servCarrierFreq_r10_ToString(indent+1);
    out += measResultServCell_r10_value.ToString(indent+1);
    if(measResultNeighCells_IsPresent())
        out += measResultNeighCells_ToString(indent+1);
    return out;
}

std::string MDT_MeasurementInfo_r10::ToStringNoNewLines() const
{
    std::string out = "MDT_MeasurementInfo_r10:";
    if(locationInfo_r10_IsPresent())
        out += locationInfo_r10_ToStringNoNewLines();
    out += relativeTimeStamp_r10_ToStringNoNewLines();
    out += servCellIdentity_r10_ToStringNoNewLines();
    out += servCarrierFreq_r10_ToStringNoNewLines();
    out += measResultServCell_r10_value.ToStringNoNewLines();
    if(measResultNeighCells_IsPresent())
        out += measResultNeighCells_ToStringNoNewLines();
    return out;
}

LocationInfo_r10* MDT_MeasurementInfo_r10::locationInfo_r10_Set()
{
    locationInfo_r10_present = true;
    return &locationInfo_r10;
}

int MDT_MeasurementInfo_r10::locationInfo_r10_Set(LocationInfo_r10 &value)
{
    locationInfo_r10_present = true;
    locationInfo_r10 = value;
    return 0;
}

const LocationInfo_r10& MDT_MeasurementInfo_r10::locationInfo_r10_Get() const
{
    return locationInfo_r10;
}

std::string MDT_MeasurementInfo_r10::locationInfo_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "locationInfo_r10:\n";
    out += locationInfo_r10.ToString(indent+1);
    return out;
}

std::string MDT_MeasurementInfo_r10::locationInfo_r10_ToStringNoNewLines() const
{
    std::string out = "locationInfo_r10:";
    out += locationInfo_r10.ToStringNoNewLines();
    return out;
}

int MDT_MeasurementInfo_r10::locationInfo_r10_Clear()
{
    locationInfo_r10_present = false;
    return 0;
}

bool MDT_MeasurementInfo_r10::locationInfo_r10_IsPresent() const
{
    return locationInfo_r10_present;
}

int MDT_MeasurementInfo_r10::relativeTimeStamp_r10_Pack(std::vector<uint8_t> &bits)
{
    if(!relativeTimeStamp_r10_present)
    {
        printf("MDT_MeasurementInfo_r10::relativeTimeStamp_r10_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = relativeTimeStamp_r10_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (7200 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int MDT_MeasurementInfo_r10::relativeTimeStamp_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return relativeTimeStamp_r10_Unpack(bits, idx);
}

int MDT_MeasurementInfo_r10::relativeTimeStamp_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (7200 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("MDT_MeasurementInfo_r10::relativeTimeStamp_r10_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    relativeTimeStamp_r10_internal_value = packed_val + 0;
    relativeTimeStamp_r10_present = true;
    return 0;
}

int64_t MDT_MeasurementInfo_r10::relativeTimeStamp_r10_Value() const
{
    if(relativeTimeStamp_r10_present)
        return relativeTimeStamp_r10_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int MDT_MeasurementInfo_r10::relativeTimeStamp_r10_SetValue(int64_t value)
{
    if(value < 0 || value > 7200)
    {
        printf("MDT_MeasurementInfo_r10::relativeTimeStamp_r10_SetValue() range failure\n");
        return -1;
    }
    relativeTimeStamp_r10_internal_value = value;
    relativeTimeStamp_r10_present = true;
    return 0;
}

std::string MDT_MeasurementInfo_r10::relativeTimeStamp_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "relativeTimeStamp_r10 = " + std::to_string(relativeTimeStamp_r10_internal_value) + "\n";
    return out;
}

std::string MDT_MeasurementInfo_r10::relativeTimeStamp_r10_ToStringNoNewLines() const
{
    std::string out = "relativeTimeStamp_r10=" + std::to_string(relativeTimeStamp_r10_internal_value) + ",";
    return out;
}

int MDT_MeasurementInfo_r10::relativeTimeStamp_r10_Clear()
{
    relativeTimeStamp_r10_present = false;
    return 0;
}

bool MDT_MeasurementInfo_r10::relativeTimeStamp_r10_IsPresent() const
{
    return relativeTimeStamp_r10_present;
}

CellGlobalIdEUTRA* MDT_MeasurementInfo_r10::servCellIdentity_r10_Set()
{
    servCellIdentity_r10_present = true;
    return &servCellIdentity_r10;
}

int MDT_MeasurementInfo_r10::servCellIdentity_r10_Set(CellGlobalIdEUTRA &value)
{
    servCellIdentity_r10_present = true;
    servCellIdentity_r10 = value;
    return 0;
}

const CellGlobalIdEUTRA& MDT_MeasurementInfo_r10::servCellIdentity_r10_Get() const
{
    return servCellIdentity_r10;
}

std::string MDT_MeasurementInfo_r10::servCellIdentity_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "servCellIdentity_r10:\n";
    out += servCellIdentity_r10.ToString(indent+1);
    return out;
}

std::string MDT_MeasurementInfo_r10::servCellIdentity_r10_ToStringNoNewLines() const
{
    std::string out = "servCellIdentity_r10:";
    out += servCellIdentity_r10.ToStringNoNewLines();
    return out;
}

int MDT_MeasurementInfo_r10::servCellIdentity_r10_Clear()
{
    servCellIdentity_r10_present = false;
    return 0;
}

bool MDT_MeasurementInfo_r10::servCellIdentity_r10_IsPresent() const
{
    return servCellIdentity_r10_present;
}

ARFCN_ValueEUTRA* MDT_MeasurementInfo_r10::servCarrierFreq_r10_Set()
{
    servCarrierFreq_r10_present = true;
    return &servCarrierFreq_r10;
}

int MDT_MeasurementInfo_r10::servCarrierFreq_r10_Set(ARFCN_ValueEUTRA &value)
{
    servCarrierFreq_r10_present = true;
    servCarrierFreq_r10 = value;
    return 0;
}

const ARFCN_ValueEUTRA& MDT_MeasurementInfo_r10::servCarrierFreq_r10_Get() const
{
    return servCarrierFreq_r10;
}

std::string MDT_MeasurementInfo_r10::servCarrierFreq_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "servCarrierFreq_r10:\n";
    out += servCarrierFreq_r10.ToString(indent+1);
    return out;
}

std::string MDT_MeasurementInfo_r10::servCarrierFreq_r10_ToStringNoNewLines() const
{
    std::string out = "servCarrierFreq_r10:";
    out += servCarrierFreq_r10.ToStringNoNewLines();
    return out;
}

int MDT_MeasurementInfo_r10::servCarrierFreq_r10_Clear()
{
    servCarrierFreq_r10_present = false;
    return 0;
}

bool MDT_MeasurementInfo_r10::servCarrierFreq_r10_IsPresent() const
{
    return servCarrierFreq_r10_present;
}

int MDT_MeasurementInfo_r10::measResultServCell_r10::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != rsrpResult_r10.Pack(bits))
        {
            printf("MDT_MeasurementInfo_r10::measResultServCell_r10:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != rsrqResult_r10.Pack(bits))
        {
            printf("MDT_MeasurementInfo_r10::measResultServCell_r10:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int MDT_MeasurementInfo_r10::measResultServCell_r10::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int MDT_MeasurementInfo_r10::measResultServCell_r10::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != rsrpResult_r10.Unpack(bits, idx))
        {
            printf("MDT_MeasurementInfo_r10::measResultServCell_r10:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != rsrqResult_r10.Unpack(bits, idx))
        {
            printf("MDT_MeasurementInfo_r10::measResultServCell_r10:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string MDT_MeasurementInfo_r10::measResultServCell_r10::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "measResultServCell_r10:\n";
    out += rsrpResult_r10_ToString(indent+1);
    out += rsrqResult_r10_ToString(indent+1);
    return out;
}

std::string MDT_MeasurementInfo_r10::measResultServCell_r10::ToStringNoNewLines() const
{
    std::string out = "measResultServCell_r10:";
    out += rsrpResult_r10_ToStringNoNewLines();
    out += rsrqResult_r10_ToStringNoNewLines();
    return out;
}

RSRP_Range* MDT_MeasurementInfo_r10::measResultServCell_r10::rsrpResult_r10_Set()
{
    rsrpResult_r10_present = true;
    return &rsrpResult_r10;
}

int MDT_MeasurementInfo_r10::measResultServCell_r10::rsrpResult_r10_Set(RSRP_Range &value)
{
    rsrpResult_r10_present = true;
    rsrpResult_r10 = value;
    return 0;
}

const RSRP_Range& MDT_MeasurementInfo_r10::measResultServCell_r10::rsrpResult_r10_Get() const
{
    return rsrpResult_r10;
}

std::string MDT_MeasurementInfo_r10::measResultServCell_r10::rsrpResult_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "rsrpResult_r10:\n";
    out += rsrpResult_r10.ToString(indent+1);
    return out;
}

std::string MDT_MeasurementInfo_r10::measResultServCell_r10::rsrpResult_r10_ToStringNoNewLines() const
{
    std::string out = "rsrpResult_r10:";
    out += rsrpResult_r10.ToStringNoNewLines();
    return out;
}

int MDT_MeasurementInfo_r10::measResultServCell_r10::rsrpResult_r10_Clear()
{
    rsrpResult_r10_present = false;
    return 0;
}

bool MDT_MeasurementInfo_r10::measResultServCell_r10::rsrpResult_r10_IsPresent() const
{
    return rsrpResult_r10_present;
}

RSRQ_Range* MDT_MeasurementInfo_r10::measResultServCell_r10::rsrqResult_r10_Set()
{
    rsrqResult_r10_present = true;
    return &rsrqResult_r10;
}

int MDT_MeasurementInfo_r10::measResultServCell_r10::rsrqResult_r10_Set(RSRQ_Range &value)
{
    rsrqResult_r10_present = true;
    rsrqResult_r10 = value;
    return 0;
}

const RSRQ_Range& MDT_MeasurementInfo_r10::measResultServCell_r10::rsrqResult_r10_Get() const
{
    return rsrqResult_r10;
}

std::string MDT_MeasurementInfo_r10::measResultServCell_r10::rsrqResult_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "rsrqResult_r10:\n";
    out += rsrqResult_r10.ToString(indent+1);
    return out;
}

std::string MDT_MeasurementInfo_r10::measResultServCell_r10::rsrqResult_r10_ToStringNoNewLines() const
{
    std::string out = "rsrqResult_r10:";
    out += rsrqResult_r10.ToStringNoNewLines();
    return out;
}

int MDT_MeasurementInfo_r10::measResultServCell_r10::rsrqResult_r10_Clear()
{
    rsrqResult_r10_present = false;
    return 0;
}

bool MDT_MeasurementInfo_r10::measResultServCell_r10::rsrqResult_r10_IsPresent() const
{
    return rsrqResult_r10_present;
}

MeasResultNeighCells* MDT_MeasurementInfo_r10::measResultNeighCells_Set()
{
    measResultNeighCells_present = true;
    return &measResultNeighCells;
}

int MDT_MeasurementInfo_r10::measResultNeighCells_Set(MeasResultNeighCells &value)
{
    measResultNeighCells_present = true;
    measResultNeighCells = value;
    return 0;
}

const MeasResultNeighCells& MDT_MeasurementInfo_r10::measResultNeighCells_Get() const
{
    return measResultNeighCells;
}

std::string MDT_MeasurementInfo_r10::measResultNeighCells_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "measResultNeighCells:\n";
    out += measResultNeighCells.ToString(indent+1);
    return out;
}

std::string MDT_MeasurementInfo_r10::measResultNeighCells_ToStringNoNewLines() const
{
    std::string out = "measResultNeighCells:";
    out += measResultNeighCells.ToStringNoNewLines();
    return out;
}

int MDT_MeasurementInfo_r10::measResultNeighCells_Clear()
{
    measResultNeighCells_present = false;
    return 0;
}

bool MDT_MeasurementInfo_r10::measResultNeighCells_IsPresent() const
{
    return measResultNeighCells_present;
}

