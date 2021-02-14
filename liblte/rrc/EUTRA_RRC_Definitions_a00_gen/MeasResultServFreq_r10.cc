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

#include "MeasResultServFreq_r10.h"

#include <cmath>

int MeasResultServFreq_r10::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator
    bits.push_back(0);

    // Optional indicators
    bits.push_back(measResultSCell_value.IsPresent());
    bits.push_back(measResultBestNeighCell_value.IsPresent());

    // Fields
    {
        if(0 != servFreqId.Pack(bits))
        {
            printf("MeasResultServFreq_r10:: field pack failure\n");
            return -1;
        }
    }
    if(measResultSCell_value.IsPresent())
    {
        if(0 != measResultSCell_value.Pack(bits))
        {
            printf("MeasResultServFreq_r10:: field pack failure\n");
            return -1;
        }
    }
    if(measResultBestNeighCell_value.IsPresent())
    {
        if(0 != measResultBestNeighCell_value.Pack(bits))
        {
            printf("MeasResultServFreq_r10:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int MeasResultServFreq_r10::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int MeasResultServFreq_r10::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("MeasResultServFreq_r10::Unpack() index out of bounds for extension\n");
        return -1;
    }
    idx++;

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("MeasResultServFreq_r10::Unpack() index out of bounds for optional indiator measResultSCell\n");
        return -1;
    }
    measResultSCell_value.SetPresence(bits[idx++]);
    if((idx + 1) > bits.size())
    {
        printf("MeasResultServFreq_r10::Unpack() index out of bounds for optional indiator measResultBestNeighCell\n");
        return -1;
    }
    measResultBestNeighCell_value.SetPresence(bits[idx++]);

    // Fields
    {
        if(0 != servFreqId.Unpack(bits, idx))
        {
            printf("MeasResultServFreq_r10:: field unpack failure\n");
            return -1;
        }
    }
    if(measResultSCell_value.IsPresent())
    {
        if(0 != measResultSCell_value.Unpack(bits, idx))
        {
            printf("MeasResultServFreq_r10:: field unpack failure\n");
            return -1;
        }
    }
    if(measResultBestNeighCell_value.IsPresent())
    {
        if(0 != measResultBestNeighCell_value.Unpack(bits, idx))
        {
            printf("MeasResultServFreq_r10:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string MeasResultServFreq_r10::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "MeasResultServFreq_r10:\n";
    out += servFreqId_ToString(indent+1);
    if(measResultSCell_value.IsPresent())
        out += measResultSCell_value.ToString(indent+1);
    if(measResultBestNeighCell_value.IsPresent())
        out += measResultBestNeighCell_value.ToString(indent+1);
    return out;
}

std::string MeasResultServFreq_r10::ToStringNoNewLines() const
{
    std::string out = "MeasResultServFreq_r10:";
    out += servFreqId_ToStringNoNewLines();
    if(measResultSCell_value.IsPresent())
        out += measResultSCell_value.ToStringNoNewLines();
    if(measResultBestNeighCell_value.IsPresent())
        out += measResultBestNeighCell_value.ToStringNoNewLines();
    return out;
}

ServCellIndex_r10* MeasResultServFreq_r10::servFreqId_Set()
{
    servFreqId_present = true;
    return &servFreqId;
}

int MeasResultServFreq_r10::servFreqId_Set(ServCellIndex_r10 &value)
{
    servFreqId_present = true;
    servFreqId = value;
    return 0;
}

const ServCellIndex_r10& MeasResultServFreq_r10::servFreqId_Get() const
{
    return servFreqId;
}

std::string MeasResultServFreq_r10::servFreqId_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "servFreqId:\n";
    out += servFreqId.ToString(indent+1);
    return out;
}

std::string MeasResultServFreq_r10::servFreqId_ToStringNoNewLines() const
{
    std::string out = "servFreqId:";
    out += servFreqId.ToStringNoNewLines();
    return out;
}

int MeasResultServFreq_r10::servFreqId_Clear()
{
    servFreqId_present = false;
    return 0;
}

bool MeasResultServFreq_r10::servFreqId_IsPresent() const
{
    return servFreqId_present;
}

int MeasResultServFreq_r10::measResultSCell::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != rsrpResultSCell.Pack(bits))
        {
            printf("MeasResultServFreq_r10::measResultSCell:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != rsrqResultSCell.Pack(bits))
        {
            printf("MeasResultServFreq_r10::measResultSCell:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int MeasResultServFreq_r10::measResultSCell::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int MeasResultServFreq_r10::measResultSCell::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != rsrpResultSCell.Unpack(bits, idx))
        {
            printf("MeasResultServFreq_r10::measResultSCell:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != rsrqResultSCell.Unpack(bits, idx))
        {
            printf("MeasResultServFreq_r10::measResultSCell:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string MeasResultServFreq_r10::measResultSCell::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "measResultSCell:\n";
    out += rsrpResultSCell_ToString(indent+1);
    out += rsrqResultSCell_ToString(indent+1);
    return out;
}

std::string MeasResultServFreq_r10::measResultSCell::ToStringNoNewLines() const
{
    std::string out = "measResultSCell:";
    out += rsrpResultSCell_ToStringNoNewLines();
    out += rsrqResultSCell_ToStringNoNewLines();
    return out;
}

int MeasResultServFreq_r10::measResultSCell::Set()
{
    present = true;
    return 0;
}

int MeasResultServFreq_r10::measResultSCell::SetPresence(bool is_present)
{
    present = is_present;
    return 0;
}

int MeasResultServFreq_r10::measResultSCell::Clear()
{
    present = false;
    return 0;
}

bool MeasResultServFreq_r10::measResultSCell::IsPresent() const
{
    return present;
}

RSRP_Range* MeasResultServFreq_r10::measResultSCell::rsrpResultSCell_Set()
{
    rsrpResultSCell_present = true;
    return &rsrpResultSCell;
}

int MeasResultServFreq_r10::measResultSCell::rsrpResultSCell_Set(RSRP_Range &value)
{
    rsrpResultSCell_present = true;
    rsrpResultSCell = value;
    return 0;
}

const RSRP_Range& MeasResultServFreq_r10::measResultSCell::rsrpResultSCell_Get() const
{
    return rsrpResultSCell;
}

std::string MeasResultServFreq_r10::measResultSCell::rsrpResultSCell_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "rsrpResultSCell:\n";
    out += rsrpResultSCell.ToString(indent+1);
    return out;
}

std::string MeasResultServFreq_r10::measResultSCell::rsrpResultSCell_ToStringNoNewLines() const
{
    std::string out = "rsrpResultSCell:";
    out += rsrpResultSCell.ToStringNoNewLines();
    return out;
}

int MeasResultServFreq_r10::measResultSCell::rsrpResultSCell_Clear()
{
    rsrpResultSCell_present = false;
    return 0;
}

bool MeasResultServFreq_r10::measResultSCell::rsrpResultSCell_IsPresent() const
{
    return rsrpResultSCell_present;
}

RSRQ_Range* MeasResultServFreq_r10::measResultSCell::rsrqResultSCell_Set()
{
    rsrqResultSCell_present = true;
    return &rsrqResultSCell;
}

int MeasResultServFreq_r10::measResultSCell::rsrqResultSCell_Set(RSRQ_Range &value)
{
    rsrqResultSCell_present = true;
    rsrqResultSCell = value;
    return 0;
}

const RSRQ_Range& MeasResultServFreq_r10::measResultSCell::rsrqResultSCell_Get() const
{
    return rsrqResultSCell;
}

std::string MeasResultServFreq_r10::measResultSCell::rsrqResultSCell_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "rsrqResultSCell:\n";
    out += rsrqResultSCell.ToString(indent+1);
    return out;
}

std::string MeasResultServFreq_r10::measResultSCell::rsrqResultSCell_ToStringNoNewLines() const
{
    std::string out = "rsrqResultSCell:";
    out += rsrqResultSCell.ToStringNoNewLines();
    return out;
}

int MeasResultServFreq_r10::measResultSCell::rsrqResultSCell_Clear()
{
    rsrqResultSCell_present = false;
    return 0;
}

bool MeasResultServFreq_r10::measResultSCell::rsrqResultSCell_IsPresent() const
{
    return rsrqResultSCell_present;
}

int MeasResultServFreq_r10::measResultBestNeighCell::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != physCellId.Pack(bits))
        {
            printf("MeasResultServFreq_r10::measResultBestNeighCell:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != rsrpResultNCell.Pack(bits))
        {
            printf("MeasResultServFreq_r10::measResultBestNeighCell:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != rsrqResultNCell.Pack(bits))
        {
            printf("MeasResultServFreq_r10::measResultBestNeighCell:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int MeasResultServFreq_r10::measResultBestNeighCell::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int MeasResultServFreq_r10::measResultBestNeighCell::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != physCellId.Unpack(bits, idx))
        {
            printf("MeasResultServFreq_r10::measResultBestNeighCell:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != rsrpResultNCell.Unpack(bits, idx))
        {
            printf("MeasResultServFreq_r10::measResultBestNeighCell:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != rsrqResultNCell.Unpack(bits, idx))
        {
            printf("MeasResultServFreq_r10::measResultBestNeighCell:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string MeasResultServFreq_r10::measResultBestNeighCell::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "measResultBestNeighCell:\n";
    out += physCellId_ToString(indent+1);
    out += rsrpResultNCell_ToString(indent+1);
    out += rsrqResultNCell_ToString(indent+1);
    return out;
}

std::string MeasResultServFreq_r10::measResultBestNeighCell::ToStringNoNewLines() const
{
    std::string out = "measResultBestNeighCell:";
    out += physCellId_ToStringNoNewLines();
    out += rsrpResultNCell_ToStringNoNewLines();
    out += rsrqResultNCell_ToStringNoNewLines();
    return out;
}

int MeasResultServFreq_r10::measResultBestNeighCell::Set()
{
    present = true;
    return 0;
}

int MeasResultServFreq_r10::measResultBestNeighCell::SetPresence(bool is_present)
{
    present = is_present;
    return 0;
}

int MeasResultServFreq_r10::measResultBestNeighCell::Clear()
{
    present = false;
    return 0;
}

bool MeasResultServFreq_r10::measResultBestNeighCell::IsPresent() const
{
    return present;
}

PhysCellId* MeasResultServFreq_r10::measResultBestNeighCell::physCellId_Set()
{
    physCellId_present = true;
    return &physCellId;
}

int MeasResultServFreq_r10::measResultBestNeighCell::physCellId_Set(PhysCellId &value)
{
    physCellId_present = true;
    physCellId = value;
    return 0;
}

const PhysCellId& MeasResultServFreq_r10::measResultBestNeighCell::physCellId_Get() const
{
    return physCellId;
}

std::string MeasResultServFreq_r10::measResultBestNeighCell::physCellId_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "physCellId:\n";
    out += physCellId.ToString(indent+1);
    return out;
}

std::string MeasResultServFreq_r10::measResultBestNeighCell::physCellId_ToStringNoNewLines() const
{
    std::string out = "physCellId:";
    out += physCellId.ToStringNoNewLines();
    return out;
}

int MeasResultServFreq_r10::measResultBestNeighCell::physCellId_Clear()
{
    physCellId_present = false;
    return 0;
}

bool MeasResultServFreq_r10::measResultBestNeighCell::physCellId_IsPresent() const
{
    return physCellId_present;
}

RSRP_Range* MeasResultServFreq_r10::measResultBestNeighCell::rsrpResultNCell_Set()
{
    rsrpResultNCell_present = true;
    return &rsrpResultNCell;
}

int MeasResultServFreq_r10::measResultBestNeighCell::rsrpResultNCell_Set(RSRP_Range &value)
{
    rsrpResultNCell_present = true;
    rsrpResultNCell = value;
    return 0;
}

const RSRP_Range& MeasResultServFreq_r10::measResultBestNeighCell::rsrpResultNCell_Get() const
{
    return rsrpResultNCell;
}

std::string MeasResultServFreq_r10::measResultBestNeighCell::rsrpResultNCell_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "rsrpResultNCell:\n";
    out += rsrpResultNCell.ToString(indent+1);
    return out;
}

std::string MeasResultServFreq_r10::measResultBestNeighCell::rsrpResultNCell_ToStringNoNewLines() const
{
    std::string out = "rsrpResultNCell:";
    out += rsrpResultNCell.ToStringNoNewLines();
    return out;
}

int MeasResultServFreq_r10::measResultBestNeighCell::rsrpResultNCell_Clear()
{
    rsrpResultNCell_present = false;
    return 0;
}

bool MeasResultServFreq_r10::measResultBestNeighCell::rsrpResultNCell_IsPresent() const
{
    return rsrpResultNCell_present;
}

RSRQ_Range* MeasResultServFreq_r10::measResultBestNeighCell::rsrqResultNCell_Set()
{
    rsrqResultNCell_present = true;
    return &rsrqResultNCell;
}

int MeasResultServFreq_r10::measResultBestNeighCell::rsrqResultNCell_Set(RSRQ_Range &value)
{
    rsrqResultNCell_present = true;
    rsrqResultNCell = value;
    return 0;
}

const RSRQ_Range& MeasResultServFreq_r10::measResultBestNeighCell::rsrqResultNCell_Get() const
{
    return rsrqResultNCell;
}

std::string MeasResultServFreq_r10::measResultBestNeighCell::rsrqResultNCell_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "rsrqResultNCell:\n";
    out += rsrqResultNCell.ToString(indent+1);
    return out;
}

std::string MeasResultServFreq_r10::measResultBestNeighCell::rsrqResultNCell_ToStringNoNewLines() const
{
    std::string out = "rsrqResultNCell:";
    out += rsrqResultNCell.ToStringNoNewLines();
    return out;
}

int MeasResultServFreq_r10::measResultBestNeighCell::rsrqResultNCell_Clear()
{
    rsrqResultNCell_present = false;
    return 0;
}

bool MeasResultServFreq_r10::measResultBestNeighCell::rsrqResultNCell_IsPresent() const
{
    return rsrqResultNCell_present;
}

