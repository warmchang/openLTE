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

#include "MeasResultsCDMA2000.h"

#include <cmath>

int MeasResultsCDMA2000::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != preRegistrationStatusHRPD_Pack(bits))
        {
            printf("MeasResultsCDMA2000:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != measResultListCDMA2000.Pack(bits))
        {
            printf("MeasResultsCDMA2000:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int MeasResultsCDMA2000::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int MeasResultsCDMA2000::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != preRegistrationStatusHRPD_Unpack(bits, idx))
        {
            printf("MeasResultsCDMA2000:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != measResultListCDMA2000.Unpack(bits, idx))
        {
            printf("MeasResultsCDMA2000:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string MeasResultsCDMA2000::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "MeasResultsCDMA2000:\n";
    out += preRegistrationStatusHRPD_ToString(indent+1);
    out += measResultListCDMA2000_ToString(indent+1);
    return out;
}

std::string MeasResultsCDMA2000::ToStringNoNewLines() const
{
    std::string out = "MeasResultsCDMA2000:";
    out += preRegistrationStatusHRPD_ToStringNoNewLines();
    out += measResultListCDMA2000_ToStringNoNewLines();
    return out;
}

int MeasResultsCDMA2000::preRegistrationStatusHRPD_Pack(std::vector<uint8_t> &bits)
{
    if(!preRegistrationStatusHRPD_present)
    {
        printf("MeasResultsCDMA2000::preRegistrationStatusHRPD_Pack() presence failure\n");
        return -1;
    }
    bits.push_back(preRegistrationStatusHRPD_internal_value);
    return 0;
}

int MeasResultsCDMA2000::preRegistrationStatusHRPD_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return preRegistrationStatusHRPD_Unpack(bits, idx);
}

int MeasResultsCDMA2000::preRegistrationStatusHRPD_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    if((idx + 1) > bits.size())
    {
        printf("MeasResultsCDMA2000::preRegistrationStatusHRPD_Unpack() index out of bounds\n");
        return -1;
    }
    preRegistrationStatusHRPD_internal_value = bits[idx++];
    preRegistrationStatusHRPD_present = true;
    return 0;
}

bool MeasResultsCDMA2000::preRegistrationStatusHRPD_Value() const
{
    if(preRegistrationStatusHRPD_present)
        return preRegistrationStatusHRPD_internal_value;
    return false;
}

int MeasResultsCDMA2000::preRegistrationStatusHRPD_SetValue(bool value)
{
    preRegistrationStatusHRPD_internal_value = value;
    preRegistrationStatusHRPD_present = true;
    return 0;
}

std::string MeasResultsCDMA2000::preRegistrationStatusHRPD_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "preRegistrationStatusHRPD = " + std::to_string(preRegistrationStatusHRPD_internal_value) + "\n";
    return out;
}

std::string MeasResultsCDMA2000::preRegistrationStatusHRPD_ToStringNoNewLines() const
{
    std::string out = "preRegistrationStatusHRPD=" + std::to_string(preRegistrationStatusHRPD_internal_value) + ",";
    return out;
}

int MeasResultsCDMA2000::preRegistrationStatusHRPD_Clear()
{
    preRegistrationStatusHRPD_present = false;
    return 0;
}

bool MeasResultsCDMA2000::preRegistrationStatusHRPD_IsPresent() const
{
    return preRegistrationStatusHRPD_present;
}

MeasResultListCDMA2000* MeasResultsCDMA2000::measResultListCDMA2000_Set()
{
    measResultListCDMA2000_present = true;
    return &measResultListCDMA2000;
}

int MeasResultsCDMA2000::measResultListCDMA2000_Set(MeasResultListCDMA2000 &value)
{
    measResultListCDMA2000_present = true;
    measResultListCDMA2000 = value;
    return 0;
}

const MeasResultListCDMA2000& MeasResultsCDMA2000::measResultListCDMA2000_Get() const
{
    return measResultListCDMA2000;
}

std::string MeasResultsCDMA2000::measResultListCDMA2000_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "measResultListCDMA2000:\n";
    out += measResultListCDMA2000.ToString(indent+1);
    return out;
}

std::string MeasResultsCDMA2000::measResultListCDMA2000_ToStringNoNewLines() const
{
    std::string out = "measResultListCDMA2000:";
    out += measResultListCDMA2000.ToStringNoNewLines();
    return out;
}

int MeasResultsCDMA2000::measResultListCDMA2000_Clear()
{
    measResultListCDMA2000_present = false;
    return 0;
}

bool MeasResultsCDMA2000::measResultListCDMA2000_IsPresent() const
{
    return measResultListCDMA2000_present;
}

