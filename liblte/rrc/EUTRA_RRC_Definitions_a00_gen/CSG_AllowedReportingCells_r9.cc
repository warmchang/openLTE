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

#include "CSG_AllowedReportingCells_r9.h"

#include <cmath>

int CSG_AllowedReportingCells_r9::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(physCellIdRangeUTRA_FDDList_r9_IsPresent());

    // Fields
    if(physCellIdRangeUTRA_FDDList_r9_IsPresent())
    {
        if(0 != physCellIdRangeUTRA_FDDList_r9.Pack(bits))
        {
            printf("CSG_AllowedReportingCells_r9:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int CSG_AllowedReportingCells_r9::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int CSG_AllowedReportingCells_r9::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("CSG_AllowedReportingCells_r9::Unpack() index out of bounds for optional indiator physCellIdRangeUTRA_FDDList_r9\n");
        return -1;
    }
    physCellIdRangeUTRA_FDDList_r9_present = bits[idx++];

    // Fields
    if(physCellIdRangeUTRA_FDDList_r9_present)
    {
        if(0 != physCellIdRangeUTRA_FDDList_r9.Unpack(bits, idx))
        {
            printf("CSG_AllowedReportingCells_r9:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string CSG_AllowedReportingCells_r9::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "CSG_AllowedReportingCells_r9:\n";
    if(physCellIdRangeUTRA_FDDList_r9_IsPresent())
        out += physCellIdRangeUTRA_FDDList_r9_ToString(indent+1);
    return out;
}

std::string CSG_AllowedReportingCells_r9::ToStringNoNewLines() const
{
    std::string out = "CSG_AllowedReportingCells_r9:";
    if(physCellIdRangeUTRA_FDDList_r9_IsPresent())
        out += physCellIdRangeUTRA_FDDList_r9_ToStringNoNewLines();
    return out;
}

PhysCellIdRangeUTRA_FDDList_r9* CSG_AllowedReportingCells_r9::physCellIdRangeUTRA_FDDList_r9_Set()
{
    physCellIdRangeUTRA_FDDList_r9_present = true;
    return &physCellIdRangeUTRA_FDDList_r9;
}

int CSG_AllowedReportingCells_r9::physCellIdRangeUTRA_FDDList_r9_Set(PhysCellIdRangeUTRA_FDDList_r9 &value)
{
    physCellIdRangeUTRA_FDDList_r9_present = true;
    physCellIdRangeUTRA_FDDList_r9 = value;
    return 0;
}

const PhysCellIdRangeUTRA_FDDList_r9& CSG_AllowedReportingCells_r9::physCellIdRangeUTRA_FDDList_r9_Get() const
{
    return physCellIdRangeUTRA_FDDList_r9;
}

std::string CSG_AllowedReportingCells_r9::physCellIdRangeUTRA_FDDList_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "physCellIdRangeUTRA_FDDList_r9:\n";
    out += physCellIdRangeUTRA_FDDList_r9.ToString(indent+1);
    return out;
}

std::string CSG_AllowedReportingCells_r9::physCellIdRangeUTRA_FDDList_r9_ToStringNoNewLines() const
{
    std::string out = "physCellIdRangeUTRA_FDDList_r9:";
    out += physCellIdRangeUTRA_FDDList_r9.ToStringNoNewLines();
    return out;
}

int CSG_AllowedReportingCells_r9::physCellIdRangeUTRA_FDDList_r9_Clear()
{
    physCellIdRangeUTRA_FDDList_r9_present = false;
    return 0;
}

bool CSG_AllowedReportingCells_r9::physCellIdRangeUTRA_FDDList_r9_IsPresent() const
{
    return physCellIdRangeUTRA_FDDList_r9_present;
}

