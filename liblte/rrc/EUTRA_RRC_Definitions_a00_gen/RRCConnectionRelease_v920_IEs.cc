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

#include "RRCConnectionRelease_v920_IEs.h"

#include <cmath>

int RRCConnectionRelease_v920_IEs::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(cellInfoList_r9_IsPresent());
    bits.push_back(0);

    // Fields
    if(cellInfoList_r9_IsPresent())
    {
        if(0 != cellInfoList_r9_Pack(bits))
        {
            printf("RRCConnectionRelease_v920_IEs:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int RRCConnectionRelease_v920_IEs::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int RRCConnectionRelease_v920_IEs::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("RRCConnectionRelease_v920_IEs::Unpack() index out of bounds for optional indiator cellInfoList_r9\n");
        return -1;
    }
    cellInfoList_r9_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("RRCConnectionRelease_v920_IEs::Unpack() index out of bounds for optional indiator nonCriticalExtension\n");
        return -1;
    }
    idx++;

    // Fields
    if(cellInfoList_r9_present)
    {
        if(0 != cellInfoList_r9_Unpack(bits, idx))
        {
            printf("RRCConnectionRelease_v920_IEs:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string RRCConnectionRelease_v920_IEs::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "RRCConnectionRelease_v920_IEs:\n";
    if(cellInfoList_r9_IsPresent())
        out += cellInfoList_r9_ToString(indent+1);
    return out;
}

std::string RRCConnectionRelease_v920_IEs::ToStringNoNewLines() const
{
    std::string out = "RRCConnectionRelease_v920_IEs:";
    if(cellInfoList_r9_IsPresent())
        out += cellInfoList_r9_ToStringNoNewLines();
    return out;
}

int RRCConnectionRelease_v920_IEs::cellInfoList_r9_Pack(std::vector<uint8_t> &bits)
{
    if(!cellInfoList_r9_present)
    {
        printf("RRCConnectionRelease_v920_IEs::cellInfoList_r9_Pack() presence failure\n");
        return -1;
    }
    // Extension indicator
    bits.push_back(0);

    // Choice
    for(uint32_t i=0; i<2; i++)
        bits.push_back((cellInfoList_r9_internal_choice >> (2-i-1)) & 1);

    // Fields
    if(cellInfoList_r9_internal_choice == k_cellInfoList_r9_geran_r9)
    {
        if(0 != cellInfoList_r9_geran_r9.Pack(bits))
        {
            printf("RRCConnectionRelease_v920_IEs::cellInfoList_r9_geran_r9 pack failure\n");
            return -1;
        }
    }
    if(cellInfoList_r9_internal_choice == k_cellInfoList_r9_utra_FDD_r9)
    {
        if(0 != cellInfoList_r9_utra_FDD_r9.Pack(bits))
        {
            printf("RRCConnectionRelease_v920_IEs::cellInfoList_r9_utra_FDD_r9 pack failure\n");
            return -1;
        }
    }
    if(cellInfoList_r9_internal_choice == k_cellInfoList_r9_utra_TDD_r9)
    {
        if(0 != cellInfoList_r9_utra_TDD_r9.Pack(bits))
        {
            printf("RRCConnectionRelease_v920_IEs::cellInfoList_r9_utra_TDD_r9 pack failure\n");
            return -1;
        }
    }
    return 0;
}

int RRCConnectionRelease_v920_IEs::cellInfoList_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return cellInfoList_r9_Unpack(bits, idx);
}

int RRCConnectionRelease_v920_IEs::cellInfoList_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("RRCConnectionRelease_v920_IEs::cellInfoList_r9_Unpack() index out of bounds for extension\n");
        return -1;
    }
    idx++;

    // Choice
    uint32_t packed_val = 0;
    if((idx + 2) > bits.size())
    {
        printf("RRCConnectionRelease_v920_IEs::cellInfoList_r9_Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<2; i++)
        packed_val |= bits[idx++] << (2-i-1);

    if((RRCConnectionRelease_v920_IEs::cellInfoList_r9_Enum)packed_val > k_cellInfoList_r9_utra_TDD_r9)
    {
        printf("RRCConnectionRelease_v920_IEs::cellInfoList_r9_Unpack() choice range failure\n");
        return -1;
    }
    cellInfoList_r9_internal_choice = (RRCConnectionRelease_v920_IEs::cellInfoList_r9_Enum)packed_val;
    cellInfoList_r9_present = true;

    // Fields
    if(cellInfoList_r9_internal_choice == k_cellInfoList_r9_geran_r9)
    {
        if(0 != cellInfoList_r9_geran_r9.Unpack(bits, idx))
        {
            printf("RRCConnectionRelease_v920_IEs::cellInfoList_r9_geran_r9 unpack failure\n");
            return -1;
        }
    }
    if(cellInfoList_r9_internal_choice == k_cellInfoList_r9_utra_FDD_r9)
    {
        if(0 != cellInfoList_r9_utra_FDD_r9.Unpack(bits, idx))
        {
            printf("RRCConnectionRelease_v920_IEs::cellInfoList_r9_utra_FDD_r9 unpack failure\n");
            return -1;
        }
    }
    if(cellInfoList_r9_internal_choice == k_cellInfoList_r9_utra_TDD_r9)
    {
        if(0 != cellInfoList_r9_utra_TDD_r9.Unpack(bits, idx))
        {
            printf("RRCConnectionRelease_v920_IEs::cellInfoList_r9_utra_TDD_r9 unpack failure\n");
            return -1;
        }
    }
    return 0;
}

RRCConnectionRelease_v920_IEs::cellInfoList_r9_Enum RRCConnectionRelease_v920_IEs::cellInfoList_r9_Choice() const
{
    if(cellInfoList_r9_present)
        return cellInfoList_r9_internal_choice;
    return (RRCConnectionRelease_v920_IEs::cellInfoList_r9_Enum)0;
}

int RRCConnectionRelease_v920_IEs::cellInfoList_r9_SetChoice(RRCConnectionRelease_v920_IEs::cellInfoList_r9_Enum choice)
{
    cellInfoList_r9_internal_choice = choice;
    cellInfoList_r9_present = true;
    return 0;
}

std::string RRCConnectionRelease_v920_IEs::cellInfoList_r9_ChoiceToString(cellInfoList_r9_Enum value) const
{
    if(k_cellInfoList_r9_geran_r9 == value)
        return "cellInfoList_r9_geran_r9";
    if(k_cellInfoList_r9_utra_FDD_r9 == value)
        return "cellInfoList_r9_utra_FDD_r9";
    if(k_cellInfoList_r9_utra_TDD_r9 == value)
        return "cellInfoList_r9_utra_TDD_r9";
    return "";
}

uint64_t RRCConnectionRelease_v920_IEs::cellInfoList_r9_NumberOfChoices() const
{
    return 3;
}

std::string RRCConnectionRelease_v920_IEs::cellInfoList_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cellInfoList_r9 = " + cellInfoList_r9_ChoiceToString(cellInfoList_r9_internal_choice) + ":\n";
    if(cellInfoList_r9_internal_choice == k_cellInfoList_r9_geran_r9)
        out += cellInfoList_r9_geran_r9.ToString(indent+1);
    if(cellInfoList_r9_internal_choice == k_cellInfoList_r9_utra_FDD_r9)
        out += cellInfoList_r9_utra_FDD_r9.ToString(indent+1);
    if(cellInfoList_r9_internal_choice == k_cellInfoList_r9_utra_TDD_r9)
        out += cellInfoList_r9_utra_TDD_r9.ToString(indent+1);
    return out;
}

std::string RRCConnectionRelease_v920_IEs::cellInfoList_r9_ToStringNoNewLines() const
{
    std::string out = "cellInfoList_r9=" + cellInfoList_r9_ChoiceToString(cellInfoList_r9_internal_choice) + ",";
    if(cellInfoList_r9_internal_choice == k_cellInfoList_r9_geran_r9)
        out += cellInfoList_r9_geran_r9.ToStringNoNewLines();
    if(cellInfoList_r9_internal_choice == k_cellInfoList_r9_utra_FDD_r9)
        out += cellInfoList_r9_utra_FDD_r9.ToStringNoNewLines();
    if(cellInfoList_r9_internal_choice == k_cellInfoList_r9_utra_TDD_r9)
        out += cellInfoList_r9_utra_TDD_r9.ToStringNoNewLines();
    return out;
}

int RRCConnectionRelease_v920_IEs::cellInfoList_r9_Clear()
{
    cellInfoList_r9_present = false;
    return 0;
}

bool RRCConnectionRelease_v920_IEs::cellInfoList_r9_IsPresent() const
{
    return cellInfoList_r9_present;
}

CellInfoListGERAN_r9* RRCConnectionRelease_v920_IEs::cellInfoList_r9_geran_r9_Set()
{
    cellInfoList_r9_geran_r9_present = true;
    return &cellInfoList_r9_geran_r9;
}

int RRCConnectionRelease_v920_IEs::cellInfoList_r9_geran_r9_Set(CellInfoListGERAN_r9 &value)
{
    cellInfoList_r9_geran_r9_present = true;
    cellInfoList_r9_geran_r9 = value;
    return 0;
}

const CellInfoListGERAN_r9& RRCConnectionRelease_v920_IEs::cellInfoList_r9_geran_r9_Get() const
{
    return cellInfoList_r9_geran_r9;
}

std::string RRCConnectionRelease_v920_IEs::cellInfoList_r9_geran_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "geran_r9:\n";
    out += cellInfoList_r9_geran_r9.ToString(indent+1);
    return out;
}

std::string RRCConnectionRelease_v920_IEs::cellInfoList_r9_geran_r9_ToStringNoNewLines() const
{
    std::string out = "geran_r9:";
    out += cellInfoList_r9_geran_r9.ToStringNoNewLines();
    return out;
}

int RRCConnectionRelease_v920_IEs::cellInfoList_r9_geran_r9_Clear()
{
    cellInfoList_r9_geran_r9_present = false;
    return 0;
}

bool RRCConnectionRelease_v920_IEs::cellInfoList_r9_geran_r9_IsPresent() const
{
    return cellInfoList_r9_geran_r9_present;
}

CellInfoListUTRA_FDD_r9* RRCConnectionRelease_v920_IEs::cellInfoList_r9_utra_FDD_r9_Set()
{
    cellInfoList_r9_utra_FDD_r9_present = true;
    return &cellInfoList_r9_utra_FDD_r9;
}

int RRCConnectionRelease_v920_IEs::cellInfoList_r9_utra_FDD_r9_Set(CellInfoListUTRA_FDD_r9 &value)
{
    cellInfoList_r9_utra_FDD_r9_present = true;
    cellInfoList_r9_utra_FDD_r9 = value;
    return 0;
}

const CellInfoListUTRA_FDD_r9& RRCConnectionRelease_v920_IEs::cellInfoList_r9_utra_FDD_r9_Get() const
{
    return cellInfoList_r9_utra_FDD_r9;
}

std::string RRCConnectionRelease_v920_IEs::cellInfoList_r9_utra_FDD_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "utra_FDD_r9:\n";
    out += cellInfoList_r9_utra_FDD_r9.ToString(indent+1);
    return out;
}

std::string RRCConnectionRelease_v920_IEs::cellInfoList_r9_utra_FDD_r9_ToStringNoNewLines() const
{
    std::string out = "utra_FDD_r9:";
    out += cellInfoList_r9_utra_FDD_r9.ToStringNoNewLines();
    return out;
}

int RRCConnectionRelease_v920_IEs::cellInfoList_r9_utra_FDD_r9_Clear()
{
    cellInfoList_r9_utra_FDD_r9_present = false;
    return 0;
}

bool RRCConnectionRelease_v920_IEs::cellInfoList_r9_utra_FDD_r9_IsPresent() const
{
    return cellInfoList_r9_utra_FDD_r9_present;
}

CellInfoListUTRA_TDD_r9* RRCConnectionRelease_v920_IEs::cellInfoList_r9_utra_TDD_r9_Set()
{
    cellInfoList_r9_utra_TDD_r9_present = true;
    return &cellInfoList_r9_utra_TDD_r9;
}

int RRCConnectionRelease_v920_IEs::cellInfoList_r9_utra_TDD_r9_Set(CellInfoListUTRA_TDD_r9 &value)
{
    cellInfoList_r9_utra_TDD_r9_present = true;
    cellInfoList_r9_utra_TDD_r9 = value;
    return 0;
}

const CellInfoListUTRA_TDD_r9& RRCConnectionRelease_v920_IEs::cellInfoList_r9_utra_TDD_r9_Get() const
{
    return cellInfoList_r9_utra_TDD_r9;
}

std::string RRCConnectionRelease_v920_IEs::cellInfoList_r9_utra_TDD_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "utra_TDD_r9:\n";
    out += cellInfoList_r9_utra_TDD_r9.ToString(indent+1);
    return out;
}

std::string RRCConnectionRelease_v920_IEs::cellInfoList_r9_utra_TDD_r9_ToStringNoNewLines() const
{
    std::string out = "utra_TDD_r9:";
    out += cellInfoList_r9_utra_TDD_r9.ToStringNoNewLines();
    return out;
}

int RRCConnectionRelease_v920_IEs::cellInfoList_r9_utra_TDD_r9_Clear()
{
    cellInfoList_r9_utra_TDD_r9_present = false;
    return 0;
}

bool RRCConnectionRelease_v920_IEs::cellInfoList_r9_utra_TDD_r9_IsPresent() const
{
    return cellInfoList_r9_utra_TDD_r9_present;
}

