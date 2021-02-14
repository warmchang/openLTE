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

#include "DL_AM_RLC.h"

#include <cmath>

int DL_AM_RLC::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != t_Reordering.Pack(bits))
        {
            printf("DL_AM_RLC:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != t_StatusProhibit.Pack(bits))
        {
            printf("DL_AM_RLC:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int DL_AM_RLC::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int DL_AM_RLC::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != t_Reordering.Unpack(bits, idx))
        {
            printf("DL_AM_RLC:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != t_StatusProhibit.Unpack(bits, idx))
        {
            printf("DL_AM_RLC:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string DL_AM_RLC::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "DL_AM_RLC:\n";
    out += t_Reordering_ToString(indent+1);
    out += t_StatusProhibit_ToString(indent+1);
    return out;
}

std::string DL_AM_RLC::ToStringNoNewLines() const
{
    std::string out = "DL_AM_RLC:";
    out += t_Reordering_ToStringNoNewLines();
    out += t_StatusProhibit_ToStringNoNewLines();
    return out;
}

T_Reordering* DL_AM_RLC::t_Reordering_Set()
{
    t_Reordering_present = true;
    return &t_Reordering;
}

int DL_AM_RLC::t_Reordering_Set(T_Reordering &value)
{
    t_Reordering_present = true;
    t_Reordering = value;
    return 0;
}

const T_Reordering& DL_AM_RLC::t_Reordering_Get() const
{
    return t_Reordering;
}

std::string DL_AM_RLC::t_Reordering_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "t_Reordering:\n";
    out += t_Reordering.ToString(indent+1);
    return out;
}

std::string DL_AM_RLC::t_Reordering_ToStringNoNewLines() const
{
    std::string out = "t_Reordering:";
    out += t_Reordering.ToStringNoNewLines();
    return out;
}

int DL_AM_RLC::t_Reordering_Clear()
{
    t_Reordering_present = false;
    return 0;
}

bool DL_AM_RLC::t_Reordering_IsPresent() const
{
    return t_Reordering_present;
}

T_StatusProhibit* DL_AM_RLC::t_StatusProhibit_Set()
{
    t_StatusProhibit_present = true;
    return &t_StatusProhibit;
}

int DL_AM_RLC::t_StatusProhibit_Set(T_StatusProhibit &value)
{
    t_StatusProhibit_present = true;
    t_StatusProhibit = value;
    return 0;
}

const T_StatusProhibit& DL_AM_RLC::t_StatusProhibit_Get() const
{
    return t_StatusProhibit;
}

std::string DL_AM_RLC::t_StatusProhibit_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "t_StatusProhibit:\n";
    out += t_StatusProhibit.ToString(indent+1);
    return out;
}

std::string DL_AM_RLC::t_StatusProhibit_ToStringNoNewLines() const
{
    std::string out = "t_StatusProhibit:";
    out += t_StatusProhibit.ToStringNoNewLines();
    return out;
}

int DL_AM_RLC::t_StatusProhibit_Clear()
{
    t_StatusProhibit_present = false;
    return 0;
}

bool DL_AM_RLC::t_StatusProhibit_IsPresent() const
{
    return t_StatusProhibit_present;
}

