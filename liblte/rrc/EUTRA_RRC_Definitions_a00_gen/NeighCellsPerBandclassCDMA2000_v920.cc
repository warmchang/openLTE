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

#include "NeighCellsPerBandclassCDMA2000_v920.h"

#include <cmath>

int NeighCellsPerBandclassCDMA2000_v920::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != physCellIdList_v920.Pack(bits))
        {
            printf("NeighCellsPerBandclassCDMA2000_v920:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int NeighCellsPerBandclassCDMA2000_v920::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int NeighCellsPerBandclassCDMA2000_v920::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != physCellIdList_v920.Unpack(bits, idx))
        {
            printf("NeighCellsPerBandclassCDMA2000_v920:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string NeighCellsPerBandclassCDMA2000_v920::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "NeighCellsPerBandclassCDMA2000_v920:\n";
    out += physCellIdList_v920_ToString(indent+1);
    return out;
}

std::string NeighCellsPerBandclassCDMA2000_v920::ToStringNoNewLines() const
{
    std::string out = "NeighCellsPerBandclassCDMA2000_v920:";
    out += physCellIdList_v920_ToStringNoNewLines();
    return out;
}

PhysCellIdListCDMA2000_v920* NeighCellsPerBandclassCDMA2000_v920::physCellIdList_v920_Set()
{
    physCellIdList_v920_present = true;
    return &physCellIdList_v920;
}

int NeighCellsPerBandclassCDMA2000_v920::physCellIdList_v920_Set(PhysCellIdListCDMA2000_v920 &value)
{
    physCellIdList_v920_present = true;
    physCellIdList_v920 = value;
    return 0;
}

const PhysCellIdListCDMA2000_v920& NeighCellsPerBandclassCDMA2000_v920::physCellIdList_v920_Get() const
{
    return physCellIdList_v920;
}

std::string NeighCellsPerBandclassCDMA2000_v920::physCellIdList_v920_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "physCellIdList_v920:\n";
    out += physCellIdList_v920.ToString(indent+1);
    return out;
}

std::string NeighCellsPerBandclassCDMA2000_v920::physCellIdList_v920_ToStringNoNewLines() const
{
    std::string out = "physCellIdList_v920:";
    out += physCellIdList_v920.ToStringNoNewLines();
    return out;
}

int NeighCellsPerBandclassCDMA2000_v920::physCellIdList_v920_Clear()
{
    physCellIdList_v920_present = false;
    return 0;
}

bool NeighCellsPerBandclassCDMA2000_v920::physCellIdList_v920_IsPresent() const
{
    return physCellIdList_v920_present;
}

