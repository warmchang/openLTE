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

#include "NeighCellCDMA2000.h"

#include <cmath>

int NeighCellCDMA2000::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != bandClass.Pack(bits))
        {
            printf("NeighCellCDMA2000:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != neighCellsPerFreqList.Pack(bits))
        {
            printf("NeighCellCDMA2000:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int NeighCellCDMA2000::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int NeighCellCDMA2000::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != bandClass.Unpack(bits, idx))
        {
            printf("NeighCellCDMA2000:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != neighCellsPerFreqList.Unpack(bits, idx))
        {
            printf("NeighCellCDMA2000:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string NeighCellCDMA2000::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "NeighCellCDMA2000:\n";
    out += bandClass_ToString(indent+1);
    out += neighCellsPerFreqList_ToString(indent+1);
    return out;
}

std::string NeighCellCDMA2000::ToStringNoNewLines() const
{
    std::string out = "NeighCellCDMA2000:";
    out += bandClass_ToStringNoNewLines();
    out += neighCellsPerFreqList_ToStringNoNewLines();
    return out;
}

BandclassCDMA2000* NeighCellCDMA2000::bandClass_Set()
{
    bandClass_present = true;
    return &bandClass;
}

int NeighCellCDMA2000::bandClass_Set(BandclassCDMA2000 &value)
{
    bandClass_present = true;
    bandClass = value;
    return 0;
}

const BandclassCDMA2000& NeighCellCDMA2000::bandClass_Get() const
{
    return bandClass;
}

std::string NeighCellCDMA2000::bandClass_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "bandClass:\n";
    out += bandClass.ToString(indent+1);
    return out;
}

std::string NeighCellCDMA2000::bandClass_ToStringNoNewLines() const
{
    std::string out = "bandClass:";
    out += bandClass.ToStringNoNewLines();
    return out;
}

int NeighCellCDMA2000::bandClass_Clear()
{
    bandClass_present = false;
    return 0;
}

bool NeighCellCDMA2000::bandClass_IsPresent() const
{
    return bandClass_present;
}

NeighCellsPerBandclassListCDMA2000* NeighCellCDMA2000::neighCellsPerFreqList_Set()
{
    neighCellsPerFreqList_present = true;
    return &neighCellsPerFreqList;
}

int NeighCellCDMA2000::neighCellsPerFreqList_Set(NeighCellsPerBandclassListCDMA2000 &value)
{
    neighCellsPerFreqList_present = true;
    neighCellsPerFreqList = value;
    return 0;
}

const NeighCellsPerBandclassListCDMA2000& NeighCellCDMA2000::neighCellsPerFreqList_Get() const
{
    return neighCellsPerFreqList;
}

std::string NeighCellCDMA2000::neighCellsPerFreqList_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "neighCellsPerFreqList:\n";
    out += neighCellsPerFreqList.ToString(indent+1);
    return out;
}

std::string NeighCellCDMA2000::neighCellsPerFreqList_ToStringNoNewLines() const
{
    std::string out = "neighCellsPerFreqList:";
    out += neighCellsPerFreqList.ToStringNoNewLines();
    return out;
}

int NeighCellCDMA2000::neighCellsPerFreqList_Clear()
{
    neighCellsPerFreqList_present = false;
    return 0;
}

bool NeighCellCDMA2000::neighCellsPerFreqList_IsPresent() const
{
    return neighCellsPerFreqList_present;
}

