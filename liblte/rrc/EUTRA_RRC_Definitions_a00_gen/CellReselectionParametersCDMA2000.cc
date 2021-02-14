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

#include "CellReselectionParametersCDMA2000.h"

#include <cmath>

int CellReselectionParametersCDMA2000::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(t_ReselectionCDMA2000_SF_IsPresent());

    // Fields
    {
        if(0 != bandClassList.Pack(bits))
        {
            printf("CellReselectionParametersCDMA2000:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != neighCellList.Pack(bits))
        {
            printf("CellReselectionParametersCDMA2000:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != t_ReselectionCDMA2000.Pack(bits))
        {
            printf("CellReselectionParametersCDMA2000:: field pack failure\n");
            return -1;
        }
    }
    if(t_ReselectionCDMA2000_SF_IsPresent())
    {
        if(0 != t_ReselectionCDMA2000_SF.Pack(bits))
        {
            printf("CellReselectionParametersCDMA2000:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int CellReselectionParametersCDMA2000::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int CellReselectionParametersCDMA2000::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("CellReselectionParametersCDMA2000::Unpack() index out of bounds for optional indiator t_ReselectionCDMA2000_SF\n");
        return -1;
    }
    t_ReselectionCDMA2000_SF_present = bits[idx++];

    // Fields
    {
        if(0 != bandClassList.Unpack(bits, idx))
        {
            printf("CellReselectionParametersCDMA2000:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != neighCellList.Unpack(bits, idx))
        {
            printf("CellReselectionParametersCDMA2000:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != t_ReselectionCDMA2000.Unpack(bits, idx))
        {
            printf("CellReselectionParametersCDMA2000:: field unpack failure\n");
            return -1;
        }
    }
    if(t_ReselectionCDMA2000_SF_present)
    {
        if(0 != t_ReselectionCDMA2000_SF.Unpack(bits, idx))
        {
            printf("CellReselectionParametersCDMA2000:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string CellReselectionParametersCDMA2000::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "CellReselectionParametersCDMA2000:\n";
    out += bandClassList_ToString(indent+1);
    out += neighCellList_ToString(indent+1);
    out += t_ReselectionCDMA2000_ToString(indent+1);
    if(t_ReselectionCDMA2000_SF_IsPresent())
        out += t_ReselectionCDMA2000_SF_ToString(indent+1);
    return out;
}

std::string CellReselectionParametersCDMA2000::ToStringNoNewLines() const
{
    std::string out = "CellReselectionParametersCDMA2000:";
    out += bandClassList_ToStringNoNewLines();
    out += neighCellList_ToStringNoNewLines();
    out += t_ReselectionCDMA2000_ToStringNoNewLines();
    if(t_ReselectionCDMA2000_SF_IsPresent())
        out += t_ReselectionCDMA2000_SF_ToStringNoNewLines();
    return out;
}

BandClassListCDMA2000* CellReselectionParametersCDMA2000::bandClassList_Set()
{
    bandClassList_present = true;
    return &bandClassList;
}

int CellReselectionParametersCDMA2000::bandClassList_Set(BandClassListCDMA2000 &value)
{
    bandClassList_present = true;
    bandClassList = value;
    return 0;
}

const BandClassListCDMA2000& CellReselectionParametersCDMA2000::bandClassList_Get() const
{
    return bandClassList;
}

std::string CellReselectionParametersCDMA2000::bandClassList_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "bandClassList:\n";
    out += bandClassList.ToString(indent+1);
    return out;
}

std::string CellReselectionParametersCDMA2000::bandClassList_ToStringNoNewLines() const
{
    std::string out = "bandClassList:";
    out += bandClassList.ToStringNoNewLines();
    return out;
}

int CellReselectionParametersCDMA2000::bandClassList_Clear()
{
    bandClassList_present = false;
    return 0;
}

bool CellReselectionParametersCDMA2000::bandClassList_IsPresent() const
{
    return bandClassList_present;
}

NeighCellListCDMA2000* CellReselectionParametersCDMA2000::neighCellList_Set()
{
    neighCellList_present = true;
    return &neighCellList;
}

int CellReselectionParametersCDMA2000::neighCellList_Set(NeighCellListCDMA2000 &value)
{
    neighCellList_present = true;
    neighCellList = value;
    return 0;
}

const NeighCellListCDMA2000& CellReselectionParametersCDMA2000::neighCellList_Get() const
{
    return neighCellList;
}

std::string CellReselectionParametersCDMA2000::neighCellList_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "neighCellList:\n";
    out += neighCellList.ToString(indent+1);
    return out;
}

std::string CellReselectionParametersCDMA2000::neighCellList_ToStringNoNewLines() const
{
    std::string out = "neighCellList:";
    out += neighCellList.ToStringNoNewLines();
    return out;
}

int CellReselectionParametersCDMA2000::neighCellList_Clear()
{
    neighCellList_present = false;
    return 0;
}

bool CellReselectionParametersCDMA2000::neighCellList_IsPresent() const
{
    return neighCellList_present;
}

T_Reselection* CellReselectionParametersCDMA2000::t_ReselectionCDMA2000_Set()
{
    t_ReselectionCDMA2000_present = true;
    return &t_ReselectionCDMA2000;
}

int CellReselectionParametersCDMA2000::t_ReselectionCDMA2000_Set(T_Reselection &value)
{
    t_ReselectionCDMA2000_present = true;
    t_ReselectionCDMA2000 = value;
    return 0;
}

const T_Reselection& CellReselectionParametersCDMA2000::t_ReselectionCDMA2000_Get() const
{
    return t_ReselectionCDMA2000;
}

std::string CellReselectionParametersCDMA2000::t_ReselectionCDMA2000_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "t_ReselectionCDMA2000:\n";
    out += t_ReselectionCDMA2000.ToString(indent+1);
    return out;
}

std::string CellReselectionParametersCDMA2000::t_ReselectionCDMA2000_ToStringNoNewLines() const
{
    std::string out = "t_ReselectionCDMA2000:";
    out += t_ReselectionCDMA2000.ToStringNoNewLines();
    return out;
}

int CellReselectionParametersCDMA2000::t_ReselectionCDMA2000_Clear()
{
    t_ReselectionCDMA2000_present = false;
    return 0;
}

bool CellReselectionParametersCDMA2000::t_ReselectionCDMA2000_IsPresent() const
{
    return t_ReselectionCDMA2000_present;
}

SpeedStateScaleFactors* CellReselectionParametersCDMA2000::t_ReselectionCDMA2000_SF_Set()
{
    t_ReselectionCDMA2000_SF_present = true;
    return &t_ReselectionCDMA2000_SF;
}

int CellReselectionParametersCDMA2000::t_ReselectionCDMA2000_SF_Set(SpeedStateScaleFactors &value)
{
    t_ReselectionCDMA2000_SF_present = true;
    t_ReselectionCDMA2000_SF = value;
    return 0;
}

const SpeedStateScaleFactors& CellReselectionParametersCDMA2000::t_ReselectionCDMA2000_SF_Get() const
{
    return t_ReselectionCDMA2000_SF;
}

std::string CellReselectionParametersCDMA2000::t_ReselectionCDMA2000_SF_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "t_ReselectionCDMA2000_SF:\n";
    out += t_ReselectionCDMA2000_SF.ToString(indent+1);
    return out;
}

std::string CellReselectionParametersCDMA2000::t_ReselectionCDMA2000_SF_ToStringNoNewLines() const
{
    std::string out = "t_ReselectionCDMA2000_SF:";
    out += t_ReselectionCDMA2000_SF.ToStringNoNewLines();
    return out;
}

int CellReselectionParametersCDMA2000::t_ReselectionCDMA2000_SF_Clear()
{
    t_ReselectionCDMA2000_SF_present = false;
    return 0;
}

bool CellReselectionParametersCDMA2000::t_ReselectionCDMA2000_SF_IsPresent() const
{
    return t_ReselectionCDMA2000_SF_present;
}

