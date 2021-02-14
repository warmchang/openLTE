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

#include "UL_UM_RLC.h"

#include <cmath>

int UL_UM_RLC::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != sn_FieldLength.Pack(bits))
        {
            printf("UL_UM_RLC:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int UL_UM_RLC::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int UL_UM_RLC::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != sn_FieldLength.Unpack(bits, idx))
        {
            printf("UL_UM_RLC:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string UL_UM_RLC::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "UL_UM_RLC:\n";
    out += sn_FieldLength_ToString(indent+1);
    return out;
}

std::string UL_UM_RLC::ToStringNoNewLines() const
{
    std::string out = "UL_UM_RLC:";
    out += sn_FieldLength_ToStringNoNewLines();
    return out;
}

SN_FieldLength* UL_UM_RLC::sn_FieldLength_Set()
{
    sn_FieldLength_present = true;
    return &sn_FieldLength;
}

int UL_UM_RLC::sn_FieldLength_Set(SN_FieldLength &value)
{
    sn_FieldLength_present = true;
    sn_FieldLength = value;
    return 0;
}

const SN_FieldLength& UL_UM_RLC::sn_FieldLength_Get() const
{
    return sn_FieldLength;
}

std::string UL_UM_RLC::sn_FieldLength_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "sn_FieldLength:\n";
    out += sn_FieldLength.ToString(indent+1);
    return out;
}

std::string UL_UM_RLC::sn_FieldLength_ToStringNoNewLines() const
{
    std::string out = "sn_FieldLength:";
    out += sn_FieldLength.ToStringNoNewLines();
    return out;
}

int UL_UM_RLC::sn_FieldLength_Clear()
{
    sn_FieldLength_present = false;
    return 0;
}

bool UL_UM_RLC::sn_FieldLength_IsPresent() const
{
    return sn_FieldLength_present;
}

