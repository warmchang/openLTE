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

#include "CellGlobalIdEUTRA.h"

#include <cmath>

int CellGlobalIdEUTRA::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != plmn_Identity.Pack(bits))
        {
            printf("CellGlobalIdEUTRA:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != cellIdentity.Pack(bits))
        {
            printf("CellGlobalIdEUTRA:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int CellGlobalIdEUTRA::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int CellGlobalIdEUTRA::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != plmn_Identity.Unpack(bits, idx))
        {
            printf("CellGlobalIdEUTRA:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != cellIdentity.Unpack(bits, idx))
        {
            printf("CellGlobalIdEUTRA:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string CellGlobalIdEUTRA::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "CellGlobalIdEUTRA:\n";
    out += plmn_Identity_ToString(indent+1);
    out += cellIdentity_ToString(indent+1);
    return out;
}

std::string CellGlobalIdEUTRA::ToStringNoNewLines() const
{
    std::string out = "CellGlobalIdEUTRA:";
    out += plmn_Identity_ToStringNoNewLines();
    out += cellIdentity_ToStringNoNewLines();
    return out;
}

PLMN_Identity* CellGlobalIdEUTRA::plmn_Identity_Set()
{
    plmn_Identity_present = true;
    return &plmn_Identity;
}

int CellGlobalIdEUTRA::plmn_Identity_Set(PLMN_Identity &value)
{
    plmn_Identity_present = true;
    plmn_Identity = value;
    return 0;
}

const PLMN_Identity& CellGlobalIdEUTRA::plmn_Identity_Get() const
{
    return plmn_Identity;
}

std::string CellGlobalIdEUTRA::plmn_Identity_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "plmn_Identity:\n";
    out += plmn_Identity.ToString(indent+1);
    return out;
}

std::string CellGlobalIdEUTRA::plmn_Identity_ToStringNoNewLines() const
{
    std::string out = "plmn_Identity:";
    out += plmn_Identity.ToStringNoNewLines();
    return out;
}

int CellGlobalIdEUTRA::plmn_Identity_Clear()
{
    plmn_Identity_present = false;
    return 0;
}

bool CellGlobalIdEUTRA::plmn_Identity_IsPresent() const
{
    return plmn_Identity_present;
}

CellIdentity* CellGlobalIdEUTRA::cellIdentity_Set()
{
    cellIdentity_present = true;
    return &cellIdentity;
}

int CellGlobalIdEUTRA::cellIdentity_Set(CellIdentity &value)
{
    cellIdentity_present = true;
    cellIdentity = value;
    return 0;
}

const CellIdentity& CellGlobalIdEUTRA::cellIdentity_Get() const
{
    return cellIdentity;
}

std::string CellGlobalIdEUTRA::cellIdentity_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cellIdentity:\n";
    out += cellIdentity.ToString(indent+1);
    return out;
}

std::string CellGlobalIdEUTRA::cellIdentity_ToStringNoNewLines() const
{
    std::string out = "cellIdentity:";
    out += cellIdentity.ToStringNoNewLines();
    return out;
}

int CellGlobalIdEUTRA::cellIdentity_Clear()
{
    cellIdentity_present = false;
    return 0;
}

bool CellGlobalIdEUTRA::cellIdentity_IsPresent() const
{
    return cellIdentity_present;
}

