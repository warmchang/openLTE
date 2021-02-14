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

#include "InterFreqNeighCellInfo.h"

#include <cmath>

int InterFreqNeighCellInfo::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != physCellId.Pack(bits))
        {
            printf("InterFreqNeighCellInfo:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != q_OffsetCell.Pack(bits))
        {
            printf("InterFreqNeighCellInfo:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int InterFreqNeighCellInfo::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int InterFreqNeighCellInfo::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != physCellId.Unpack(bits, idx))
        {
            printf("InterFreqNeighCellInfo:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != q_OffsetCell.Unpack(bits, idx))
        {
            printf("InterFreqNeighCellInfo:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string InterFreqNeighCellInfo::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "InterFreqNeighCellInfo:\n";
    out += physCellId_ToString(indent+1);
    out += q_OffsetCell_ToString(indent+1);
    return out;
}

std::string InterFreqNeighCellInfo::ToStringNoNewLines() const
{
    std::string out = "InterFreqNeighCellInfo:";
    out += physCellId_ToStringNoNewLines();
    out += q_OffsetCell_ToStringNoNewLines();
    return out;
}

PhysCellId* InterFreqNeighCellInfo::physCellId_Set()
{
    physCellId_present = true;
    return &physCellId;
}

int InterFreqNeighCellInfo::physCellId_Set(PhysCellId &value)
{
    physCellId_present = true;
    physCellId = value;
    return 0;
}

const PhysCellId& InterFreqNeighCellInfo::physCellId_Get() const
{
    return physCellId;
}

std::string InterFreqNeighCellInfo::physCellId_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "physCellId:\n";
    out += physCellId.ToString(indent+1);
    return out;
}

std::string InterFreqNeighCellInfo::physCellId_ToStringNoNewLines() const
{
    std::string out = "physCellId:";
    out += physCellId.ToStringNoNewLines();
    return out;
}

int InterFreqNeighCellInfo::physCellId_Clear()
{
    physCellId_present = false;
    return 0;
}

bool InterFreqNeighCellInfo::physCellId_IsPresent() const
{
    return physCellId_present;
}

Q_OffsetRange* InterFreqNeighCellInfo::q_OffsetCell_Set()
{
    q_OffsetCell_present = true;
    return &q_OffsetCell;
}

int InterFreqNeighCellInfo::q_OffsetCell_Set(Q_OffsetRange &value)
{
    q_OffsetCell_present = true;
    q_OffsetCell = value;
    return 0;
}

const Q_OffsetRange& InterFreqNeighCellInfo::q_OffsetCell_Get() const
{
    return q_OffsetCell;
}

std::string InterFreqNeighCellInfo::q_OffsetCell_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "q_OffsetCell:\n";
    out += q_OffsetCell.ToString(indent+1);
    return out;
}

std::string InterFreqNeighCellInfo::q_OffsetCell_ToStringNoNewLines() const
{
    std::string out = "q_OffsetCell:";
    out += q_OffsetCell.ToStringNoNewLines();
    return out;
}

int InterFreqNeighCellInfo::q_OffsetCell_Clear()
{
    q_OffsetCell_present = false;
    return 0;
}

bool InterFreqNeighCellInfo::q_OffsetCell_IsPresent() const
{
    return q_OffsetCell_present;
}

