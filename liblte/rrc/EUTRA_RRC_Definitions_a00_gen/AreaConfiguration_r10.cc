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

#include "AreaConfiguration_r10.h"

#include <cmath>

int AreaConfiguration_r10::Pack(std::vector<uint8_t> &bits)
{
    if(!present)
    {
        printf("AreaConfiguration_r10::Pack() presence failure\n");
        return -1;
    }
    // Extension indicator

    // Choice
    for(uint32_t i=0; i<1; i++)
        bits.push_back((internal_choice >> (1-i-1)) & 1);

    // Fields
    if(internal_choice == k_cellGlobalIdList_r10)
    {
        if(0 != cellGlobalIdList_r10.Pack(bits))
        {
            printf("AreaConfiguration_r10::cellGlobalIdList_r10 pack failure\n");
            return -1;
        }
    }
    if(internal_choice == k_trackingAreaCodeList_r10)
    {
        if(0 != trackingAreaCodeList_r10.Pack(bits))
        {
            printf("AreaConfiguration_r10::trackingAreaCodeList_r10 pack failure\n");
            return -1;
        }
    }
    return 0;
}

int AreaConfiguration_r10::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int AreaConfiguration_r10::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 1) > bits.size())
    {
        printf("AreaConfiguration_r10::Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<1; i++)
        packed_val |= bits[idx++] << (1-i-1);

    if((AreaConfiguration_r10::Enum)packed_val > k_trackingAreaCodeList_r10)
    {
        printf("AreaConfiguration_r10::Unpack() choice range failure\n");
        return -1;
    }
    internal_choice = (AreaConfiguration_r10::Enum)packed_val;
    present = true;

    // Fields
    if(internal_choice == k_cellGlobalIdList_r10)
    {
        if(0 != cellGlobalIdList_r10.Unpack(bits, idx))
        {
            printf("AreaConfiguration_r10::cellGlobalIdList_r10 unpack failure\n");
            return -1;
        }
    }
    if(internal_choice == k_trackingAreaCodeList_r10)
    {
        if(0 != trackingAreaCodeList_r10.Unpack(bits, idx))
        {
            printf("AreaConfiguration_r10::trackingAreaCodeList_r10 unpack failure\n");
            return -1;
        }
    }
    return 0;
}

AreaConfiguration_r10::Enum AreaConfiguration_r10::Choice() const
{
    if(present)
        return internal_choice;
    return (AreaConfiguration_r10::Enum)0;
}

int AreaConfiguration_r10::SetChoice(AreaConfiguration_r10::Enum choice)
{
    internal_choice = choice;
    present = true;
    return 0;
}

std::string AreaConfiguration_r10::ChoiceToString(Enum value) const
{
    if(k_cellGlobalIdList_r10 == value)
        return "cellGlobalIdList_r10";
    if(k_trackingAreaCodeList_r10 == value)
        return "trackingAreaCodeList_r10";
    return "";
}

uint64_t AreaConfiguration_r10::NumberOfChoices() const
{
    return 2;
}

std::string AreaConfiguration_r10::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "AreaConfiguration_r10 = " + ChoiceToString(internal_choice) + ":\n";
    if(internal_choice == k_cellGlobalIdList_r10)
        out += cellGlobalIdList_r10.ToString(indent+1);
    if(internal_choice == k_trackingAreaCodeList_r10)
        out += trackingAreaCodeList_r10.ToString(indent+1);
    return out;
}

std::string AreaConfiguration_r10::ToStringNoNewLines() const
{
    std::string out = "AreaConfiguration_r10=" + ChoiceToString(internal_choice) + ",";
    if(internal_choice == k_cellGlobalIdList_r10)
        out += cellGlobalIdList_r10.ToStringNoNewLines();
    if(internal_choice == k_trackingAreaCodeList_r10)
        out += trackingAreaCodeList_r10.ToStringNoNewLines();
    return out;
}

int AreaConfiguration_r10::Clear()
{
    present = false;
    return 0;
}

bool AreaConfiguration_r10::IsPresent() const
{
    return present;
}

CellGlobalIdList_r10* AreaConfiguration_r10::cellGlobalIdList_r10_Set()
{
    cellGlobalIdList_r10_present = true;
    return &cellGlobalIdList_r10;
}

int AreaConfiguration_r10::cellGlobalIdList_r10_Set(CellGlobalIdList_r10 &value)
{
    cellGlobalIdList_r10_present = true;
    cellGlobalIdList_r10 = value;
    return 0;
}

const CellGlobalIdList_r10& AreaConfiguration_r10::cellGlobalIdList_r10_Get() const
{
    return cellGlobalIdList_r10;
}

std::string AreaConfiguration_r10::cellGlobalIdList_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cellGlobalIdList_r10:\n";
    out += cellGlobalIdList_r10.ToString(indent+1);
    return out;
}

std::string AreaConfiguration_r10::cellGlobalIdList_r10_ToStringNoNewLines() const
{
    std::string out = "cellGlobalIdList_r10:";
    out += cellGlobalIdList_r10.ToStringNoNewLines();
    return out;
}

int AreaConfiguration_r10::cellGlobalIdList_r10_Clear()
{
    cellGlobalIdList_r10_present = false;
    return 0;
}

bool AreaConfiguration_r10::cellGlobalIdList_r10_IsPresent() const
{
    return cellGlobalIdList_r10_present;
}

TrackingAreaCodeList_r10* AreaConfiguration_r10::trackingAreaCodeList_r10_Set()
{
    trackingAreaCodeList_r10_present = true;
    return &trackingAreaCodeList_r10;
}

int AreaConfiguration_r10::trackingAreaCodeList_r10_Set(TrackingAreaCodeList_r10 &value)
{
    trackingAreaCodeList_r10_present = true;
    trackingAreaCodeList_r10 = value;
    return 0;
}

const TrackingAreaCodeList_r10& AreaConfiguration_r10::trackingAreaCodeList_r10_Get() const
{
    return trackingAreaCodeList_r10;
}

std::string AreaConfiguration_r10::trackingAreaCodeList_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "trackingAreaCodeList_r10:\n";
    out += trackingAreaCodeList_r10.ToString(indent+1);
    return out;
}

std::string AreaConfiguration_r10::trackingAreaCodeList_r10_ToStringNoNewLines() const
{
    std::string out = "trackingAreaCodeList_r10:";
    out += trackingAreaCodeList_r10.ToStringNoNewLines();
    return out;
}

int AreaConfiguration_r10::trackingAreaCodeList_r10_Clear()
{
    trackingAreaCodeList_r10_present = false;
    return 0;
}

bool AreaConfiguration_r10::trackingAreaCodeList_r10_IsPresent() const
{
    return trackingAreaCodeList_r10_present;
}

