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

#include "PMCH_Info_r9.h"

#include <cmath>

int PMCH_Info_r9::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator
    bits.push_back(0);

    // Optional indicators

    // Fields
    {
        if(0 != pmch_Config_r9.Pack(bits))
        {
            printf("PMCH_Info_r9:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != mbms_SessionInfoList_r9.Pack(bits))
        {
            printf("PMCH_Info_r9:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int PMCH_Info_r9::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int PMCH_Info_r9::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("PMCH_Info_r9::Unpack() index out of bounds for extension\n");
        return -1;
    }
    idx++;

    // Optional indicators

    // Fields
    {
        if(0 != pmch_Config_r9.Unpack(bits, idx))
        {
            printf("PMCH_Info_r9:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != mbms_SessionInfoList_r9.Unpack(bits, idx))
        {
            printf("PMCH_Info_r9:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string PMCH_Info_r9::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "PMCH_Info_r9:\n";
    out += pmch_Config_r9_ToString(indent+1);
    out += mbms_SessionInfoList_r9_ToString(indent+1);
    return out;
}

std::string PMCH_Info_r9::ToStringNoNewLines() const
{
    std::string out = "PMCH_Info_r9:";
    out += pmch_Config_r9_ToStringNoNewLines();
    out += mbms_SessionInfoList_r9_ToStringNoNewLines();
    return out;
}

PMCH_Config_r9* PMCH_Info_r9::pmch_Config_r9_Set()
{
    pmch_Config_r9_present = true;
    return &pmch_Config_r9;
}

int PMCH_Info_r9::pmch_Config_r9_Set(PMCH_Config_r9 &value)
{
    pmch_Config_r9_present = true;
    pmch_Config_r9 = value;
    return 0;
}

const PMCH_Config_r9& PMCH_Info_r9::pmch_Config_r9_Get() const
{
    return pmch_Config_r9;
}

std::string PMCH_Info_r9::pmch_Config_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "pmch_Config_r9:\n";
    out += pmch_Config_r9.ToString(indent+1);
    return out;
}

std::string PMCH_Info_r9::pmch_Config_r9_ToStringNoNewLines() const
{
    std::string out = "pmch_Config_r9:";
    out += pmch_Config_r9.ToStringNoNewLines();
    return out;
}

int PMCH_Info_r9::pmch_Config_r9_Clear()
{
    pmch_Config_r9_present = false;
    return 0;
}

bool PMCH_Info_r9::pmch_Config_r9_IsPresent() const
{
    return pmch_Config_r9_present;
}

MBMS_SessionInfoList_r9* PMCH_Info_r9::mbms_SessionInfoList_r9_Set()
{
    mbms_SessionInfoList_r9_present = true;
    return &mbms_SessionInfoList_r9;
}

int PMCH_Info_r9::mbms_SessionInfoList_r9_Set(MBMS_SessionInfoList_r9 &value)
{
    mbms_SessionInfoList_r9_present = true;
    mbms_SessionInfoList_r9 = value;
    return 0;
}

const MBMS_SessionInfoList_r9& PMCH_Info_r9::mbms_SessionInfoList_r9_Get() const
{
    return mbms_SessionInfoList_r9;
}

std::string PMCH_Info_r9::mbms_SessionInfoList_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "mbms_SessionInfoList_r9:\n";
    out += mbms_SessionInfoList_r9.ToString(indent+1);
    return out;
}

std::string PMCH_Info_r9::mbms_SessionInfoList_r9_ToStringNoNewLines() const
{
    std::string out = "mbms_SessionInfoList_r9:";
    out += mbms_SessionInfoList_r9.ToStringNoNewLines();
    return out;
}

int PMCH_Info_r9::mbms_SessionInfoList_r9_Clear()
{
    mbms_SessionInfoList_r9_present = false;
    return 0;
}

bool PMCH_Info_r9::mbms_SessionInfoList_r9_IsPresent() const
{
    return mbms_SessionInfoList_r9_present;
}

