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

#include "CellsToAddModUTRA_FDD.h"

#include <cmath>

int CellsToAddModUTRA_FDD::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != cellIndex_Pack(bits))
        {
            printf("CellsToAddModUTRA_FDD:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != physCellId.Pack(bits))
        {
            printf("CellsToAddModUTRA_FDD:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int CellsToAddModUTRA_FDD::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int CellsToAddModUTRA_FDD::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != cellIndex_Unpack(bits, idx))
        {
            printf("CellsToAddModUTRA_FDD:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != physCellId.Unpack(bits, idx))
        {
            printf("CellsToAddModUTRA_FDD:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string CellsToAddModUTRA_FDD::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "CellsToAddModUTRA_FDD:\n";
    out += cellIndex_ToString(indent+1);
    out += physCellId_ToString(indent+1);
    return out;
}

std::string CellsToAddModUTRA_FDD::ToStringNoNewLines() const
{
    std::string out = "CellsToAddModUTRA_FDD:";
    out += cellIndex_ToStringNoNewLines();
    out += physCellId_ToStringNoNewLines();
    return out;
}

#include "maxCellMeas.h"

int CellsToAddModUTRA_FDD::cellIndex_Pack(std::vector<uint8_t> &bits)
{
    if(!cellIndex_present)
    {
        printf("CellsToAddModUTRA_FDD::cellIndex_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = cellIndex_internal_value - (1);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (maxCellMeas - 1))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int CellsToAddModUTRA_FDD::cellIndex_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return cellIndex_Unpack(bits, idx);
}

int CellsToAddModUTRA_FDD::cellIndex_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (maxCellMeas - 1))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("CellsToAddModUTRA_FDD::cellIndex_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    cellIndex_internal_value = packed_val + 1;
    cellIndex_present = true;
    return 0;
}

int64_t CellsToAddModUTRA_FDD::cellIndex_Value() const
{
    if(cellIndex_present)
        return cellIndex_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int CellsToAddModUTRA_FDD::cellIndex_SetValue(int64_t value)
{
    if(value < 1 || value > maxCellMeas)
    {
        printf("CellsToAddModUTRA_FDD::cellIndex_SetValue() range failure\n");
        return -1;
    }
    cellIndex_internal_value = value;
    cellIndex_present = true;
    return 0;
}

std::string CellsToAddModUTRA_FDD::cellIndex_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cellIndex = " + std::to_string(cellIndex_internal_value) + "\n";
    return out;
}

std::string CellsToAddModUTRA_FDD::cellIndex_ToStringNoNewLines() const
{
    std::string out = "cellIndex=" + std::to_string(cellIndex_internal_value) + ",";
    return out;
}

int CellsToAddModUTRA_FDD::cellIndex_Clear()
{
    cellIndex_present = false;
    return 0;
}

bool CellsToAddModUTRA_FDD::cellIndex_IsPresent() const
{
    return cellIndex_present;
}

PhysCellIdUTRA_FDD* CellsToAddModUTRA_FDD::physCellId_Set()
{
    physCellId_present = true;
    return &physCellId;
}

int CellsToAddModUTRA_FDD::physCellId_Set(PhysCellIdUTRA_FDD &value)
{
    physCellId_present = true;
    physCellId = value;
    return 0;
}

const PhysCellIdUTRA_FDD& CellsToAddModUTRA_FDD::physCellId_Get() const
{
    return physCellId;
}

std::string CellsToAddModUTRA_FDD::physCellId_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "physCellId:\n";
    out += physCellId.ToString(indent+1);
    return out;
}

std::string CellsToAddModUTRA_FDD::physCellId_ToStringNoNewLines() const
{
    std::string out = "physCellId:";
    out += physCellId.ToStringNoNewLines();
    return out;
}

int CellsToAddModUTRA_FDD::physCellId_Clear()
{
    physCellId_present = false;
    return 0;
}

bool CellsToAddModUTRA_FDD::physCellId_IsPresent() const
{
    return physCellId_present;
}

