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

#include "MeasResultNeighCells.h"

#include <cmath>

int MeasResultNeighCells::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(measResultListEUTRA_IsPresent());
    bits.push_back(measResultListUTRA_IsPresent());
    bits.push_back(measResultListGERAN_IsPresent());
    bits.push_back(measResultsCDMA2000_IsPresent());

    // Fields
    if(measResultListEUTRA_IsPresent())
    {
        if(0 != measResultListEUTRA.Pack(bits))
        {
            printf("MeasResultNeighCells:: field pack failure\n");
            return -1;
        }
    }
    if(measResultListUTRA_IsPresent())
    {
        if(0 != measResultListUTRA.Pack(bits))
        {
            printf("MeasResultNeighCells:: field pack failure\n");
            return -1;
        }
    }
    if(measResultListGERAN_IsPresent())
    {
        if(0 != measResultListGERAN.Pack(bits))
        {
            printf("MeasResultNeighCells:: field pack failure\n");
            return -1;
        }
    }
    if(measResultsCDMA2000_IsPresent())
    {
        if(0 != measResultsCDMA2000.Pack(bits))
        {
            printf("MeasResultNeighCells:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int MeasResultNeighCells::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int MeasResultNeighCells::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("MeasResultNeighCells::Unpack() index out of bounds for optional indiator measResultListEUTRA\n");
        return -1;
    }
    measResultListEUTRA_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("MeasResultNeighCells::Unpack() index out of bounds for optional indiator measResultListUTRA\n");
        return -1;
    }
    measResultListUTRA_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("MeasResultNeighCells::Unpack() index out of bounds for optional indiator measResultListGERAN\n");
        return -1;
    }
    measResultListGERAN_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("MeasResultNeighCells::Unpack() index out of bounds for optional indiator measResultsCDMA2000\n");
        return -1;
    }
    measResultsCDMA2000_present = bits[idx++];

    // Fields
    if(measResultListEUTRA_present)
    {
        if(0 != measResultListEUTRA.Unpack(bits, idx))
        {
            printf("MeasResultNeighCells:: field unpack failure\n");
            return -1;
        }
    }
    if(measResultListUTRA_present)
    {
        if(0 != measResultListUTRA.Unpack(bits, idx))
        {
            printf("MeasResultNeighCells:: field unpack failure\n");
            return -1;
        }
    }
    if(measResultListGERAN_present)
    {
        if(0 != measResultListGERAN.Unpack(bits, idx))
        {
            printf("MeasResultNeighCells:: field unpack failure\n");
            return -1;
        }
    }
    if(measResultsCDMA2000_present)
    {
        if(0 != measResultsCDMA2000.Unpack(bits, idx))
        {
            printf("MeasResultNeighCells:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string MeasResultNeighCells::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "MeasResultNeighCells:\n";
    if(measResultListEUTRA_IsPresent())
        out += measResultListEUTRA_ToString(indent+1);
    if(measResultListUTRA_IsPresent())
        out += measResultListUTRA_ToString(indent+1);
    if(measResultListGERAN_IsPresent())
        out += measResultListGERAN_ToString(indent+1);
    if(measResultsCDMA2000_IsPresent())
        out += measResultsCDMA2000_ToString(indent+1);
    return out;
}

std::string MeasResultNeighCells::ToStringNoNewLines() const
{
    std::string out = "MeasResultNeighCells:";
    if(measResultListEUTRA_IsPresent())
        out += measResultListEUTRA_ToStringNoNewLines();
    if(measResultListUTRA_IsPresent())
        out += measResultListUTRA_ToStringNoNewLines();
    if(measResultListGERAN_IsPresent())
        out += measResultListGERAN_ToStringNoNewLines();
    if(measResultsCDMA2000_IsPresent())
        out += measResultsCDMA2000_ToStringNoNewLines();
    return out;
}

MeasResultList2EUTRA_r9* MeasResultNeighCells::measResultListEUTRA_Set()
{
    measResultListEUTRA_present = true;
    return &measResultListEUTRA;
}

int MeasResultNeighCells::measResultListEUTRA_Set(MeasResultList2EUTRA_r9 &value)
{
    measResultListEUTRA_present = true;
    measResultListEUTRA = value;
    return 0;
}

const MeasResultList2EUTRA_r9& MeasResultNeighCells::measResultListEUTRA_Get() const
{
    return measResultListEUTRA;
}

std::string MeasResultNeighCells::measResultListEUTRA_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "measResultListEUTRA:\n";
    out += measResultListEUTRA.ToString(indent+1);
    return out;
}

std::string MeasResultNeighCells::measResultListEUTRA_ToStringNoNewLines() const
{
    std::string out = "measResultListEUTRA:";
    out += measResultListEUTRA.ToStringNoNewLines();
    return out;
}

int MeasResultNeighCells::measResultListEUTRA_Clear()
{
    measResultListEUTRA_present = false;
    return 0;
}

bool MeasResultNeighCells::measResultListEUTRA_IsPresent() const
{
    return measResultListEUTRA_present;
}

MeasResultList2UTRA_r9* MeasResultNeighCells::measResultListUTRA_Set()
{
    measResultListUTRA_present = true;
    return &measResultListUTRA;
}

int MeasResultNeighCells::measResultListUTRA_Set(MeasResultList2UTRA_r9 &value)
{
    measResultListUTRA_present = true;
    measResultListUTRA = value;
    return 0;
}

const MeasResultList2UTRA_r9& MeasResultNeighCells::measResultListUTRA_Get() const
{
    return measResultListUTRA;
}

std::string MeasResultNeighCells::measResultListUTRA_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "measResultListUTRA:\n";
    out += measResultListUTRA.ToString(indent+1);
    return out;
}

std::string MeasResultNeighCells::measResultListUTRA_ToStringNoNewLines() const
{
    std::string out = "measResultListUTRA:";
    out += measResultListUTRA.ToStringNoNewLines();
    return out;
}

int MeasResultNeighCells::measResultListUTRA_Clear()
{
    measResultListUTRA_present = false;
    return 0;
}

bool MeasResultNeighCells::measResultListUTRA_IsPresent() const
{
    return measResultListUTRA_present;
}

MeasResultListGERAN* MeasResultNeighCells::measResultListGERAN_Set()
{
    measResultListGERAN_present = true;
    return &measResultListGERAN;
}

int MeasResultNeighCells::measResultListGERAN_Set(MeasResultListGERAN &value)
{
    measResultListGERAN_present = true;
    measResultListGERAN = value;
    return 0;
}

const MeasResultListGERAN& MeasResultNeighCells::measResultListGERAN_Get() const
{
    return measResultListGERAN;
}

std::string MeasResultNeighCells::measResultListGERAN_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "measResultListGERAN:\n";
    out += measResultListGERAN.ToString(indent+1);
    return out;
}

std::string MeasResultNeighCells::measResultListGERAN_ToStringNoNewLines() const
{
    std::string out = "measResultListGERAN:";
    out += measResultListGERAN.ToStringNoNewLines();
    return out;
}

int MeasResultNeighCells::measResultListGERAN_Clear()
{
    measResultListGERAN_present = false;
    return 0;
}

bool MeasResultNeighCells::measResultListGERAN_IsPresent() const
{
    return measResultListGERAN_present;
}

MeasResultList2CDMA2000_r9* MeasResultNeighCells::measResultsCDMA2000_Set()
{
    measResultsCDMA2000_present = true;
    return &measResultsCDMA2000;
}

int MeasResultNeighCells::measResultsCDMA2000_Set(MeasResultList2CDMA2000_r9 &value)
{
    measResultsCDMA2000_present = true;
    measResultsCDMA2000 = value;
    return 0;
}

const MeasResultList2CDMA2000_r9& MeasResultNeighCells::measResultsCDMA2000_Get() const
{
    return measResultsCDMA2000;
}

std::string MeasResultNeighCells::measResultsCDMA2000_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "measResultsCDMA2000:\n";
    out += measResultsCDMA2000.ToString(indent+1);
    return out;
}

std::string MeasResultNeighCells::measResultsCDMA2000_ToStringNoNewLines() const
{
    std::string out = "measResultsCDMA2000:";
    out += measResultsCDMA2000.ToStringNoNewLines();
    return out;
}

int MeasResultNeighCells::measResultsCDMA2000_Clear()
{
    measResultsCDMA2000_present = false;
    return 0;
}

bool MeasResultNeighCells::measResultsCDMA2000_IsPresent() const
{
    return measResultsCDMA2000_present;
}

