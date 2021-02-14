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

#include "PLMN_Identity.h"

#include <cmath>

int PLMN_Identity::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(mcc_IsPresent());

    // Fields
    if(mcc_IsPresent())
    {
        if(0 != mcc.Pack(bits))
        {
            printf("PLMN_Identity:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != mnc.Pack(bits))
        {
            printf("PLMN_Identity:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int PLMN_Identity::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int PLMN_Identity::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("PLMN_Identity::Unpack() index out of bounds for optional indiator mcc\n");
        return -1;
    }
    mcc_present = bits[idx++];

    // Fields
    if(mcc_present)
    {
        if(0 != mcc.Unpack(bits, idx))
        {
            printf("PLMN_Identity:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != mnc.Unpack(bits, idx))
        {
            printf("PLMN_Identity:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string PLMN_Identity::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "PLMN_Identity:\n";
    if(mcc_IsPresent())
        out += mcc_ToString(indent+1);
    out += mnc_ToString(indent+1);
    return out;
}

std::string PLMN_Identity::ToStringNoNewLines() const
{
    std::string out = "PLMN_Identity:";
    if(mcc_IsPresent())
        out += mcc_ToStringNoNewLines();
    out += mnc_ToStringNoNewLines();
    return out;
}

MCC* PLMN_Identity::mcc_Set()
{
    mcc_present = true;
    return &mcc;
}

int PLMN_Identity::mcc_Set(MCC &value)
{
    mcc_present = true;
    mcc = value;
    return 0;
}

const MCC& PLMN_Identity::mcc_Get() const
{
    return mcc;
}

std::string PLMN_Identity::mcc_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "mcc:\n";
    out += mcc.ToString(indent+1);
    return out;
}

std::string PLMN_Identity::mcc_ToStringNoNewLines() const
{
    std::string out = "mcc:";
    out += mcc.ToStringNoNewLines();
    return out;
}

int PLMN_Identity::mcc_Clear()
{
    mcc_present = false;
    return 0;
}

bool PLMN_Identity::mcc_IsPresent() const
{
    return mcc_present;
}

MNC* PLMN_Identity::mnc_Set()
{
    mnc_present = true;
    return &mnc;
}

int PLMN_Identity::mnc_Set(MNC &value)
{
    mnc_present = true;
    mnc = value;
    return 0;
}

const MNC& PLMN_Identity::mnc_Get() const
{
    return mnc;
}

std::string PLMN_Identity::mnc_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "mnc:\n";
    out += mnc.ToString(indent+1);
    return out;
}

std::string PLMN_Identity::mnc_ToStringNoNewLines() const
{
    std::string out = "mnc:";
    out += mnc.ToStringNoNewLines();
    return out;
}

int PLMN_Identity::mnc_Clear()
{
    mnc_present = false;
    return 0;
}

bool PLMN_Identity::mnc_IsPresent() const
{
    return mnc_present;
}

