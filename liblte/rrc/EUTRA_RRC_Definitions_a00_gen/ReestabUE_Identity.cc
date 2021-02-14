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

#include "ReestabUE_Identity.h"

#include <cmath>

int ReestabUE_Identity::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != c_RNTI.Pack(bits))
        {
            printf("ReestabUE_Identity:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != physCellId.Pack(bits))
        {
            printf("ReestabUE_Identity:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != shortMAC_I.Pack(bits))
        {
            printf("ReestabUE_Identity:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int ReestabUE_Identity::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int ReestabUE_Identity::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != c_RNTI.Unpack(bits, idx))
        {
            printf("ReestabUE_Identity:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != physCellId.Unpack(bits, idx))
        {
            printf("ReestabUE_Identity:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != shortMAC_I.Unpack(bits, idx))
        {
            printf("ReestabUE_Identity:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string ReestabUE_Identity::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ReestabUE_Identity:\n";
    out += c_RNTI_ToString(indent+1);
    out += physCellId_ToString(indent+1);
    out += shortMAC_I_ToString(indent+1);
    return out;
}

std::string ReestabUE_Identity::ToStringNoNewLines() const
{
    std::string out = "ReestabUE_Identity:";
    out += c_RNTI_ToStringNoNewLines();
    out += physCellId_ToStringNoNewLines();
    out += shortMAC_I_ToStringNoNewLines();
    return out;
}

C_RNTI* ReestabUE_Identity::c_RNTI_Set()
{
    c_RNTI_present = true;
    return &c_RNTI;
}

int ReestabUE_Identity::c_RNTI_Set(C_RNTI &value)
{
    c_RNTI_present = true;
    c_RNTI = value;
    return 0;
}

const C_RNTI& ReestabUE_Identity::c_RNTI_Get() const
{
    return c_RNTI;
}

std::string ReestabUE_Identity::c_RNTI_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "c_RNTI:\n";
    out += c_RNTI.ToString(indent+1);
    return out;
}

std::string ReestabUE_Identity::c_RNTI_ToStringNoNewLines() const
{
    std::string out = "c_RNTI:";
    out += c_RNTI.ToStringNoNewLines();
    return out;
}

int ReestabUE_Identity::c_RNTI_Clear()
{
    c_RNTI_present = false;
    return 0;
}

bool ReestabUE_Identity::c_RNTI_IsPresent() const
{
    return c_RNTI_present;
}

PhysCellId* ReestabUE_Identity::physCellId_Set()
{
    physCellId_present = true;
    return &physCellId;
}

int ReestabUE_Identity::physCellId_Set(PhysCellId &value)
{
    physCellId_present = true;
    physCellId = value;
    return 0;
}

const PhysCellId& ReestabUE_Identity::physCellId_Get() const
{
    return physCellId;
}

std::string ReestabUE_Identity::physCellId_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "physCellId:\n";
    out += physCellId.ToString(indent+1);
    return out;
}

std::string ReestabUE_Identity::physCellId_ToStringNoNewLines() const
{
    std::string out = "physCellId:";
    out += physCellId.ToStringNoNewLines();
    return out;
}

int ReestabUE_Identity::physCellId_Clear()
{
    physCellId_present = false;
    return 0;
}

bool ReestabUE_Identity::physCellId_IsPresent() const
{
    return physCellId_present;
}

ShortMAC_I* ReestabUE_Identity::shortMAC_I_Set()
{
    shortMAC_I_present = true;
    return &shortMAC_I;
}

int ReestabUE_Identity::shortMAC_I_Set(ShortMAC_I &value)
{
    shortMAC_I_present = true;
    shortMAC_I = value;
    return 0;
}

const ShortMAC_I& ReestabUE_Identity::shortMAC_I_Get() const
{
    return shortMAC_I;
}

std::string ReestabUE_Identity::shortMAC_I_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "shortMAC_I:\n";
    out += shortMAC_I.ToString(indent+1);
    return out;
}

std::string ReestabUE_Identity::shortMAC_I_ToStringNoNewLines() const
{
    std::string out = "shortMAC_I:";
    out += shortMAC_I.ToStringNoNewLines();
    return out;
}

int ReestabUE_Identity::shortMAC_I_Clear()
{
    shortMAC_I_present = false;
    return 0;
}

bool ReestabUE_Identity::shortMAC_I_IsPresent() const
{
    return shortMAC_I_present;
}

