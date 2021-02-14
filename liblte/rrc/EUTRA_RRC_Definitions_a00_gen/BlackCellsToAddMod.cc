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

#include "BlackCellsToAddMod.h"

#include <cmath>

int BlackCellsToAddMod::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != cellIndex_Pack(bits))
        {
            printf("BlackCellsToAddMod:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != physCellIdRange.Pack(bits))
        {
            printf("BlackCellsToAddMod:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int BlackCellsToAddMod::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int BlackCellsToAddMod::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != cellIndex_Unpack(bits, idx))
        {
            printf("BlackCellsToAddMod:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != physCellIdRange.Unpack(bits, idx))
        {
            printf("BlackCellsToAddMod:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string BlackCellsToAddMod::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "BlackCellsToAddMod:\n";
    out += cellIndex_ToString(indent+1);
    out += physCellIdRange_ToString(indent+1);
    return out;
}

std::string BlackCellsToAddMod::ToStringNoNewLines() const
{
    std::string out = "BlackCellsToAddMod:";
    out += cellIndex_ToStringNoNewLines();
    out += physCellIdRange_ToStringNoNewLines();
    return out;
}

#include "maxCellMeas.h"

int BlackCellsToAddMod::cellIndex_Pack(std::vector<uint8_t> &bits)
{
    if(!cellIndex_present)
    {
        printf("BlackCellsToAddMod::cellIndex_Pack() presence failure\n");
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

int BlackCellsToAddMod::cellIndex_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return cellIndex_Unpack(bits, idx);
}

int BlackCellsToAddMod::cellIndex_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (maxCellMeas - 1))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("BlackCellsToAddMod::cellIndex_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    cellIndex_internal_value = packed_val + 1;
    cellIndex_present = true;
    return 0;
}

int64_t BlackCellsToAddMod::cellIndex_Value() const
{
    if(cellIndex_present)
        return cellIndex_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int BlackCellsToAddMod::cellIndex_SetValue(int64_t value)
{
    if(value < 1 || value > maxCellMeas)
    {
        printf("BlackCellsToAddMod::cellIndex_SetValue() range failure\n");
        return -1;
    }
    cellIndex_internal_value = value;
    cellIndex_present = true;
    return 0;
}

std::string BlackCellsToAddMod::cellIndex_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cellIndex = " + std::to_string(cellIndex_internal_value) + "\n";
    return out;
}

std::string BlackCellsToAddMod::cellIndex_ToStringNoNewLines() const
{
    std::string out = "cellIndex=" + std::to_string(cellIndex_internal_value) + ",";
    return out;
}

int BlackCellsToAddMod::cellIndex_Clear()
{
    cellIndex_present = false;
    return 0;
}

bool BlackCellsToAddMod::cellIndex_IsPresent() const
{
    return cellIndex_present;
}

PhysCellIdRange* BlackCellsToAddMod::physCellIdRange_Set()
{
    physCellIdRange_present = true;
    return &physCellIdRange;
}

int BlackCellsToAddMod::physCellIdRange_Set(PhysCellIdRange &value)
{
    physCellIdRange_present = true;
    physCellIdRange = value;
    return 0;
}

const PhysCellIdRange& BlackCellsToAddMod::physCellIdRange_Get() const
{
    return physCellIdRange;
}

std::string BlackCellsToAddMod::physCellIdRange_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "physCellIdRange:\n";
    out += physCellIdRange.ToString(indent+1);
    return out;
}

std::string BlackCellsToAddMod::physCellIdRange_ToStringNoNewLines() const
{
    std::string out = "physCellIdRange:";
    out += physCellIdRange.ToStringNoNewLines();
    return out;
}

int BlackCellsToAddMod::physCellIdRange_Clear()
{
    physCellIdRange_present = false;
    return 0;
}

bool BlackCellsToAddMod::physCellIdRange_IsPresent() const
{
    return physCellIdRange_present;
}

