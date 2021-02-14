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

#include "NeighCellsPerBandclassCDMA2000.h"

#include <cmath>

int NeighCellsPerBandclassCDMA2000::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != arfcn.Pack(bits))
        {
            printf("NeighCellsPerBandclassCDMA2000:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != physCellIdList.Pack(bits))
        {
            printf("NeighCellsPerBandclassCDMA2000:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int NeighCellsPerBandclassCDMA2000::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int NeighCellsPerBandclassCDMA2000::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != arfcn.Unpack(bits, idx))
        {
            printf("NeighCellsPerBandclassCDMA2000:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != physCellIdList.Unpack(bits, idx))
        {
            printf("NeighCellsPerBandclassCDMA2000:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string NeighCellsPerBandclassCDMA2000::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "NeighCellsPerBandclassCDMA2000:\n";
    out += arfcn_ToString(indent+1);
    out += physCellIdList_ToString(indent+1);
    return out;
}

std::string NeighCellsPerBandclassCDMA2000::ToStringNoNewLines() const
{
    std::string out = "NeighCellsPerBandclassCDMA2000:";
    out += arfcn_ToStringNoNewLines();
    out += physCellIdList_ToStringNoNewLines();
    return out;
}

ARFCN_ValueCDMA2000* NeighCellsPerBandclassCDMA2000::arfcn_Set()
{
    arfcn_present = true;
    return &arfcn;
}

int NeighCellsPerBandclassCDMA2000::arfcn_Set(ARFCN_ValueCDMA2000 &value)
{
    arfcn_present = true;
    arfcn = value;
    return 0;
}

const ARFCN_ValueCDMA2000& NeighCellsPerBandclassCDMA2000::arfcn_Get() const
{
    return arfcn;
}

std::string NeighCellsPerBandclassCDMA2000::arfcn_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "arfcn:\n";
    out += arfcn.ToString(indent+1);
    return out;
}

std::string NeighCellsPerBandclassCDMA2000::arfcn_ToStringNoNewLines() const
{
    std::string out = "arfcn:";
    out += arfcn.ToStringNoNewLines();
    return out;
}

int NeighCellsPerBandclassCDMA2000::arfcn_Clear()
{
    arfcn_present = false;
    return 0;
}

bool NeighCellsPerBandclassCDMA2000::arfcn_IsPresent() const
{
    return arfcn_present;
}

PhysCellIdListCDMA2000* NeighCellsPerBandclassCDMA2000::physCellIdList_Set()
{
    physCellIdList_present = true;
    return &physCellIdList;
}

int NeighCellsPerBandclassCDMA2000::physCellIdList_Set(PhysCellIdListCDMA2000 &value)
{
    physCellIdList_present = true;
    physCellIdList = value;
    return 0;
}

const PhysCellIdListCDMA2000& NeighCellsPerBandclassCDMA2000::physCellIdList_Get() const
{
    return physCellIdList;
}

std::string NeighCellsPerBandclassCDMA2000::physCellIdList_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "physCellIdList:\n";
    out += physCellIdList.ToString(indent+1);
    return out;
}

std::string NeighCellsPerBandclassCDMA2000::physCellIdList_ToStringNoNewLines() const
{
    std::string out = "physCellIdList:";
    out += physCellIdList.ToStringNoNewLines();
    return out;
}

int NeighCellsPerBandclassCDMA2000::physCellIdList_Clear()
{
    physCellIdList_present = false;
    return 0;
}

bool NeighCellsPerBandclassCDMA2000::physCellIdList_IsPresent() const
{
    return physCellIdList_present;
}

