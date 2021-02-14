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

#include "CellsToAddMod.h"

#include <cmath>

int CellsToAddMod::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != cellIndex_Pack(bits))
        {
            printf("CellsToAddMod:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != physCellId.Pack(bits))
        {
            printf("CellsToAddMod:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != cellIndividualOffset.Pack(bits))
        {
            printf("CellsToAddMod:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int CellsToAddMod::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int CellsToAddMod::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != cellIndex_Unpack(bits, idx))
        {
            printf("CellsToAddMod:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != physCellId.Unpack(bits, idx))
        {
            printf("CellsToAddMod:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != cellIndividualOffset.Unpack(bits, idx))
        {
            printf("CellsToAddMod:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string CellsToAddMod::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "CellsToAddMod:\n";
    out += cellIndex_ToString(indent+1);
    out += physCellId_ToString(indent+1);
    out += cellIndividualOffset_ToString(indent+1);
    return out;
}

std::string CellsToAddMod::ToStringNoNewLines() const
{
    std::string out = "CellsToAddMod:";
    out += cellIndex_ToStringNoNewLines();
    out += physCellId_ToStringNoNewLines();
    out += cellIndividualOffset_ToStringNoNewLines();
    return out;
}

#include "maxCellMeas.h"

int CellsToAddMod::cellIndex_Pack(std::vector<uint8_t> &bits)
{
    if(!cellIndex_present)
    {
        printf("CellsToAddMod::cellIndex_Pack() presence failure\n");
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

int CellsToAddMod::cellIndex_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return cellIndex_Unpack(bits, idx);
}

int CellsToAddMod::cellIndex_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (maxCellMeas - 1))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("CellsToAddMod::cellIndex_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    cellIndex_internal_value = packed_val + 1;
    cellIndex_present = true;
    return 0;
}

int64_t CellsToAddMod::cellIndex_Value() const
{
    if(cellIndex_present)
        return cellIndex_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int CellsToAddMod::cellIndex_SetValue(int64_t value)
{
    if(value < 1 || value > maxCellMeas)
    {
        printf("CellsToAddMod::cellIndex_SetValue() range failure\n");
        return -1;
    }
    cellIndex_internal_value = value;
    cellIndex_present = true;
    return 0;
}

std::string CellsToAddMod::cellIndex_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cellIndex = " + std::to_string(cellIndex_internal_value) + "\n";
    return out;
}

std::string CellsToAddMod::cellIndex_ToStringNoNewLines() const
{
    std::string out = "cellIndex=" + std::to_string(cellIndex_internal_value) + ",";
    return out;
}

int CellsToAddMod::cellIndex_Clear()
{
    cellIndex_present = false;
    return 0;
}

bool CellsToAddMod::cellIndex_IsPresent() const
{
    return cellIndex_present;
}

PhysCellId* CellsToAddMod::physCellId_Set()
{
    physCellId_present = true;
    return &physCellId;
}

int CellsToAddMod::physCellId_Set(PhysCellId &value)
{
    physCellId_present = true;
    physCellId = value;
    return 0;
}

const PhysCellId& CellsToAddMod::physCellId_Get() const
{
    return physCellId;
}

std::string CellsToAddMod::physCellId_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "physCellId:\n";
    out += physCellId.ToString(indent+1);
    return out;
}

std::string CellsToAddMod::physCellId_ToStringNoNewLines() const
{
    std::string out = "physCellId:";
    out += physCellId.ToStringNoNewLines();
    return out;
}

int CellsToAddMod::physCellId_Clear()
{
    physCellId_present = false;
    return 0;
}

bool CellsToAddMod::physCellId_IsPresent() const
{
    return physCellId_present;
}

Q_OffsetRange* CellsToAddMod::cellIndividualOffset_Set()
{
    cellIndividualOffset_present = true;
    return &cellIndividualOffset;
}

int CellsToAddMod::cellIndividualOffset_Set(Q_OffsetRange &value)
{
    cellIndividualOffset_present = true;
    cellIndividualOffset = value;
    return 0;
}

const Q_OffsetRange& CellsToAddMod::cellIndividualOffset_Get() const
{
    return cellIndividualOffset;
}

std::string CellsToAddMod::cellIndividualOffset_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cellIndividualOffset:\n";
    out += cellIndividualOffset.ToString(indent+1);
    return out;
}

std::string CellsToAddMod::cellIndividualOffset_ToStringNoNewLines() const
{
    std::string out = "cellIndividualOffset:";
    out += cellIndividualOffset.ToStringNoNewLines();
    return out;
}

int CellsToAddMod::cellIndividualOffset_Clear()
{
    cellIndividualOffset_present = false;
    return 0;
}

bool CellsToAddMod::cellIndividualOffset_IsPresent() const
{
    return cellIndividualOffset_present;
}

