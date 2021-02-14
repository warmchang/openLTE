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

#include "AdditionalReestabInfo.h"

#include <cmath>

int AdditionalReestabInfo::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != cellIdentity.Pack(bits))
        {
            printf("AdditionalReestabInfo:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != key_eNodeB_Star.Pack(bits))
        {
            printf("AdditionalReestabInfo:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != shortMAC_I.Pack(bits))
        {
            printf("AdditionalReestabInfo:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int AdditionalReestabInfo::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int AdditionalReestabInfo::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != cellIdentity.Unpack(bits, idx))
        {
            printf("AdditionalReestabInfo:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != key_eNodeB_Star.Unpack(bits, idx))
        {
            printf("AdditionalReestabInfo:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != shortMAC_I.Unpack(bits, idx))
        {
            printf("AdditionalReestabInfo:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string AdditionalReestabInfo::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "AdditionalReestabInfo:\n";
    out += cellIdentity_ToString(indent+1);
    out += key_eNodeB_Star_ToString(indent+1);
    out += shortMAC_I_ToString(indent+1);
    return out;
}

std::string AdditionalReestabInfo::ToStringNoNewLines() const
{
    std::string out = "AdditionalReestabInfo:";
    out += cellIdentity_ToStringNoNewLines();
    out += key_eNodeB_Star_ToStringNoNewLines();
    out += shortMAC_I_ToStringNoNewLines();
    return out;
}

CellIdentity* AdditionalReestabInfo::cellIdentity_Set()
{
    cellIdentity_present = true;
    return &cellIdentity;
}

int AdditionalReestabInfo::cellIdentity_Set(CellIdentity &value)
{
    cellIdentity_present = true;
    cellIdentity = value;
    return 0;
}

const CellIdentity& AdditionalReestabInfo::cellIdentity_Get() const
{
    return cellIdentity;
}

std::string AdditionalReestabInfo::cellIdentity_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cellIdentity:\n";
    out += cellIdentity.ToString(indent+1);
    return out;
}

std::string AdditionalReestabInfo::cellIdentity_ToStringNoNewLines() const
{
    std::string out = "cellIdentity:";
    out += cellIdentity.ToStringNoNewLines();
    return out;
}

int AdditionalReestabInfo::cellIdentity_Clear()
{
    cellIdentity_present = false;
    return 0;
}

bool AdditionalReestabInfo::cellIdentity_IsPresent() const
{
    return cellIdentity_present;
}

Key_eNodeB_Star* AdditionalReestabInfo::key_eNodeB_Star_Set()
{
    key_eNodeB_Star_present = true;
    return &key_eNodeB_Star;
}

int AdditionalReestabInfo::key_eNodeB_Star_Set(Key_eNodeB_Star &value)
{
    key_eNodeB_Star_present = true;
    key_eNodeB_Star = value;
    return 0;
}

const Key_eNodeB_Star& AdditionalReestabInfo::key_eNodeB_Star_Get() const
{
    return key_eNodeB_Star;
}

std::string AdditionalReestabInfo::key_eNodeB_Star_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "key_eNodeB_Star:\n";
    out += key_eNodeB_Star.ToString(indent+1);
    return out;
}

std::string AdditionalReestabInfo::key_eNodeB_Star_ToStringNoNewLines() const
{
    std::string out = "key_eNodeB_Star:";
    out += key_eNodeB_Star.ToStringNoNewLines();
    return out;
}

int AdditionalReestabInfo::key_eNodeB_Star_Clear()
{
    key_eNodeB_Star_present = false;
    return 0;
}

bool AdditionalReestabInfo::key_eNodeB_Star_IsPresent() const
{
    return key_eNodeB_Star_present;
}

ShortMAC_I* AdditionalReestabInfo::shortMAC_I_Set()
{
    shortMAC_I_present = true;
    return &shortMAC_I;
}

int AdditionalReestabInfo::shortMAC_I_Set(ShortMAC_I &value)
{
    shortMAC_I_present = true;
    shortMAC_I = value;
    return 0;
}

const ShortMAC_I& AdditionalReestabInfo::shortMAC_I_Get() const
{
    return shortMAC_I;
}

std::string AdditionalReestabInfo::shortMAC_I_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "shortMAC_I:\n";
    out += shortMAC_I.ToString(indent+1);
    return out;
}

std::string AdditionalReestabInfo::shortMAC_I_ToStringNoNewLines() const
{
    std::string out = "shortMAC_I:";
    out += shortMAC_I.ToStringNoNewLines();
    return out;
}

int AdditionalReestabInfo::shortMAC_I_Clear()
{
    shortMAC_I_present = false;
    return 0;
}

bool AdditionalReestabInfo::shortMAC_I_IsPresent() const
{
    return shortMAC_I_present;
}

