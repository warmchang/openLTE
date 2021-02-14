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

#include "VarShortMAC_Input.h"

#include <cmath>

int VarShortMAC_Input::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != cellIdentity.Pack(bits))
        {
            printf("VarShortMAC_Input:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != physCellId.Pack(bits))
        {
            printf("VarShortMAC_Input:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != c_RNTI.Pack(bits))
        {
            printf("VarShortMAC_Input:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int VarShortMAC_Input::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int VarShortMAC_Input::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != cellIdentity.Unpack(bits, idx))
        {
            printf("VarShortMAC_Input:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != physCellId.Unpack(bits, idx))
        {
            printf("VarShortMAC_Input:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != c_RNTI.Unpack(bits, idx))
        {
            printf("VarShortMAC_Input:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string VarShortMAC_Input::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "VarShortMAC_Input:\n";
    out += cellIdentity_ToString(indent+1);
    out += physCellId_ToString(indent+1);
    out += c_RNTI_ToString(indent+1);
    return out;
}

std::string VarShortMAC_Input::ToStringNoNewLines() const
{
    std::string out = "VarShortMAC_Input:";
    out += cellIdentity_ToStringNoNewLines();
    out += physCellId_ToStringNoNewLines();
    out += c_RNTI_ToStringNoNewLines();
    return out;
}

CellIdentity* VarShortMAC_Input::cellIdentity_Set()
{
    cellIdentity_present = true;
    return &cellIdentity;
}

int VarShortMAC_Input::cellIdentity_Set(CellIdentity &value)
{
    cellIdentity_present = true;
    cellIdentity = value;
    return 0;
}

const CellIdentity& VarShortMAC_Input::cellIdentity_Get() const
{
    return cellIdentity;
}

std::string VarShortMAC_Input::cellIdentity_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cellIdentity:\n";
    out += cellIdentity.ToString(indent+1);
    return out;
}

std::string VarShortMAC_Input::cellIdentity_ToStringNoNewLines() const
{
    std::string out = "cellIdentity:";
    out += cellIdentity.ToStringNoNewLines();
    return out;
}

int VarShortMAC_Input::cellIdentity_Clear()
{
    cellIdentity_present = false;
    return 0;
}

bool VarShortMAC_Input::cellIdentity_IsPresent() const
{
    return cellIdentity_present;
}

PhysCellId* VarShortMAC_Input::physCellId_Set()
{
    physCellId_present = true;
    return &physCellId;
}

int VarShortMAC_Input::physCellId_Set(PhysCellId &value)
{
    physCellId_present = true;
    physCellId = value;
    return 0;
}

const PhysCellId& VarShortMAC_Input::physCellId_Get() const
{
    return physCellId;
}

std::string VarShortMAC_Input::physCellId_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "physCellId:\n";
    out += physCellId.ToString(indent+1);
    return out;
}

std::string VarShortMAC_Input::physCellId_ToStringNoNewLines() const
{
    std::string out = "physCellId:";
    out += physCellId.ToStringNoNewLines();
    return out;
}

int VarShortMAC_Input::physCellId_Clear()
{
    physCellId_present = false;
    return 0;
}

bool VarShortMAC_Input::physCellId_IsPresent() const
{
    return physCellId_present;
}

C_RNTI* VarShortMAC_Input::c_RNTI_Set()
{
    c_RNTI_present = true;
    return &c_RNTI;
}

int VarShortMAC_Input::c_RNTI_Set(C_RNTI &value)
{
    c_RNTI_present = true;
    c_RNTI = value;
    return 0;
}

const C_RNTI& VarShortMAC_Input::c_RNTI_Get() const
{
    return c_RNTI;
}

std::string VarShortMAC_Input::c_RNTI_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "c_RNTI:\n";
    out += c_RNTI.ToString(indent+1);
    return out;
}

std::string VarShortMAC_Input::c_RNTI_ToStringNoNewLines() const
{
    std::string out = "c_RNTI:";
    out += c_RNTI.ToStringNoNewLines();
    return out;
}

int VarShortMAC_Input::c_RNTI_Clear()
{
    c_RNTI_present = false;
    return 0;
}

bool VarShortMAC_Input::c_RNTI_IsPresent() const
{
    return c_RNTI_present;
}

