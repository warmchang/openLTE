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

#include "CellReselectionParametersCDMA2000_v920.h"

#include <cmath>

int CellReselectionParametersCDMA2000_v920::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != neighCellList_v920.Pack(bits))
        {
            printf("CellReselectionParametersCDMA2000_v920:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int CellReselectionParametersCDMA2000_v920::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int CellReselectionParametersCDMA2000_v920::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != neighCellList_v920.Unpack(bits, idx))
        {
            printf("CellReselectionParametersCDMA2000_v920:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string CellReselectionParametersCDMA2000_v920::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "CellReselectionParametersCDMA2000_v920:\n";
    out += neighCellList_v920_ToString(indent+1);
    return out;
}

std::string CellReselectionParametersCDMA2000_v920::ToStringNoNewLines() const
{
    std::string out = "CellReselectionParametersCDMA2000_v920:";
    out += neighCellList_v920_ToStringNoNewLines();
    return out;
}

NeighCellListCDMA2000_v920* CellReselectionParametersCDMA2000_v920::neighCellList_v920_Set()
{
    neighCellList_v920_present = true;
    return &neighCellList_v920;
}

int CellReselectionParametersCDMA2000_v920::neighCellList_v920_Set(NeighCellListCDMA2000_v920 &value)
{
    neighCellList_v920_present = true;
    neighCellList_v920 = value;
    return 0;
}

const NeighCellListCDMA2000_v920& CellReselectionParametersCDMA2000_v920::neighCellList_v920_Get() const
{
    return neighCellList_v920;
}

std::string CellReselectionParametersCDMA2000_v920::neighCellList_v920_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "neighCellList_v920:\n";
    out += neighCellList_v920.ToString(indent+1);
    return out;
}

std::string CellReselectionParametersCDMA2000_v920::neighCellList_v920_ToStringNoNewLines() const
{
    std::string out = "neighCellList_v920:";
    out += neighCellList_v920.ToStringNoNewLines();
    return out;
}

int CellReselectionParametersCDMA2000_v920::neighCellList_v920_Clear()
{
    neighCellList_v920_present = false;
    return 0;
}

bool CellReselectionParametersCDMA2000_v920::neighCellList_v920_IsPresent() const
{
    return neighCellList_v920_present;
}

