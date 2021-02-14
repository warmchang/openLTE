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

#include "RRCConnectionReconfiguration_v10xy_IEs.h"

#include <cmath>

int RRCConnectionReconfiguration_v10xy_IEs::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(sCellToReleaseList_r10_IsPresent());
    bits.push_back(sCellToAddModList_r10_IsPresent());
    bits.push_back(0);

    // Fields
    if(sCellToReleaseList_r10_IsPresent())
    {
        if(0 != sCellToReleaseList_r10.Pack(bits))
        {
            printf("RRCConnectionReconfiguration_v10xy_IEs:: field pack failure\n");
            return -1;
        }
    }
    if(sCellToAddModList_r10_IsPresent())
    {
        if(0 != sCellToAddModList_r10.Pack(bits))
        {
            printf("RRCConnectionReconfiguration_v10xy_IEs:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int RRCConnectionReconfiguration_v10xy_IEs::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int RRCConnectionReconfiguration_v10xy_IEs::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("RRCConnectionReconfiguration_v10xy_IEs::Unpack() index out of bounds for optional indiator sCellToReleaseList_r10\n");
        return -1;
    }
    sCellToReleaseList_r10_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("RRCConnectionReconfiguration_v10xy_IEs::Unpack() index out of bounds for optional indiator sCellToAddModList_r10\n");
        return -1;
    }
    sCellToAddModList_r10_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("RRCConnectionReconfiguration_v10xy_IEs::Unpack() index out of bounds for optional indiator nonCriticalExtension\n");
        return -1;
    }
    idx++;

    // Fields
    if(sCellToReleaseList_r10_present)
    {
        if(0 != sCellToReleaseList_r10.Unpack(bits, idx))
        {
            printf("RRCConnectionReconfiguration_v10xy_IEs:: field unpack failure\n");
            return -1;
        }
    }
    if(sCellToAddModList_r10_present)
    {
        if(0 != sCellToAddModList_r10.Unpack(bits, idx))
        {
            printf("RRCConnectionReconfiguration_v10xy_IEs:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string RRCConnectionReconfiguration_v10xy_IEs::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "RRCConnectionReconfiguration_v10xy_IEs:\n";
    if(sCellToReleaseList_r10_IsPresent())
        out += sCellToReleaseList_r10_ToString(indent+1);
    if(sCellToAddModList_r10_IsPresent())
        out += sCellToAddModList_r10_ToString(indent+1);
    return out;
}

std::string RRCConnectionReconfiguration_v10xy_IEs::ToStringNoNewLines() const
{
    std::string out = "RRCConnectionReconfiguration_v10xy_IEs:";
    if(sCellToReleaseList_r10_IsPresent())
        out += sCellToReleaseList_r10_ToStringNoNewLines();
    if(sCellToAddModList_r10_IsPresent())
        out += sCellToAddModList_r10_ToStringNoNewLines();
    return out;
}

SCellToReleaseList_r10* RRCConnectionReconfiguration_v10xy_IEs::sCellToReleaseList_r10_Set()
{
    sCellToReleaseList_r10_present = true;
    return &sCellToReleaseList_r10;
}

int RRCConnectionReconfiguration_v10xy_IEs::sCellToReleaseList_r10_Set(SCellToReleaseList_r10 &value)
{
    sCellToReleaseList_r10_present = true;
    sCellToReleaseList_r10 = value;
    return 0;
}

const SCellToReleaseList_r10& RRCConnectionReconfiguration_v10xy_IEs::sCellToReleaseList_r10_Get() const
{
    return sCellToReleaseList_r10;
}

std::string RRCConnectionReconfiguration_v10xy_IEs::sCellToReleaseList_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "sCellToReleaseList_r10:\n";
    out += sCellToReleaseList_r10.ToString(indent+1);
    return out;
}

std::string RRCConnectionReconfiguration_v10xy_IEs::sCellToReleaseList_r10_ToStringNoNewLines() const
{
    std::string out = "sCellToReleaseList_r10:";
    out += sCellToReleaseList_r10.ToStringNoNewLines();
    return out;
}

int RRCConnectionReconfiguration_v10xy_IEs::sCellToReleaseList_r10_Clear()
{
    sCellToReleaseList_r10_present = false;
    return 0;
}

bool RRCConnectionReconfiguration_v10xy_IEs::sCellToReleaseList_r10_IsPresent() const
{
    return sCellToReleaseList_r10_present;
}

SCellToAddModList_r10* RRCConnectionReconfiguration_v10xy_IEs::sCellToAddModList_r10_Set()
{
    sCellToAddModList_r10_present = true;
    return &sCellToAddModList_r10;
}

int RRCConnectionReconfiguration_v10xy_IEs::sCellToAddModList_r10_Set(SCellToAddModList_r10 &value)
{
    sCellToAddModList_r10_present = true;
    sCellToAddModList_r10 = value;
    return 0;
}

const SCellToAddModList_r10& RRCConnectionReconfiguration_v10xy_IEs::sCellToAddModList_r10_Get() const
{
    return sCellToAddModList_r10;
}

std::string RRCConnectionReconfiguration_v10xy_IEs::sCellToAddModList_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "sCellToAddModList_r10:\n";
    out += sCellToAddModList_r10.ToString(indent+1);
    return out;
}

std::string RRCConnectionReconfiguration_v10xy_IEs::sCellToAddModList_r10_ToStringNoNewLines() const
{
    std::string out = "sCellToAddModList_r10:";
    out += sCellToAddModList_r10.ToStringNoNewLines();
    return out;
}

int RRCConnectionReconfiguration_v10xy_IEs::sCellToAddModList_r10_Clear()
{
    sCellToAddModList_r10_present = false;
    return 0;
}

bool RRCConnectionReconfiguration_v10xy_IEs::sCellToAddModList_r10_IsPresent() const
{
    return sCellToAddModList_r10_present;
}

