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

#include "MeasResult2EUTRA_r9.h"

#include <cmath>

int MeasResult2EUTRA_r9::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != carrierFreq_r9.Pack(bits))
        {
            printf("MeasResult2EUTRA_r9:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != measResultList_r9.Pack(bits))
        {
            printf("MeasResult2EUTRA_r9:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int MeasResult2EUTRA_r9::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int MeasResult2EUTRA_r9::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != carrierFreq_r9.Unpack(bits, idx))
        {
            printf("MeasResult2EUTRA_r9:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != measResultList_r9.Unpack(bits, idx))
        {
            printf("MeasResult2EUTRA_r9:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string MeasResult2EUTRA_r9::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "MeasResult2EUTRA_r9:\n";
    out += carrierFreq_r9_ToString(indent+1);
    out += measResultList_r9_ToString(indent+1);
    return out;
}

std::string MeasResult2EUTRA_r9::ToStringNoNewLines() const
{
    std::string out = "MeasResult2EUTRA_r9:";
    out += carrierFreq_r9_ToStringNoNewLines();
    out += measResultList_r9_ToStringNoNewLines();
    return out;
}

ARFCN_ValueEUTRA* MeasResult2EUTRA_r9::carrierFreq_r9_Set()
{
    carrierFreq_r9_present = true;
    return &carrierFreq_r9;
}

int MeasResult2EUTRA_r9::carrierFreq_r9_Set(ARFCN_ValueEUTRA &value)
{
    carrierFreq_r9_present = true;
    carrierFreq_r9 = value;
    return 0;
}

const ARFCN_ValueEUTRA& MeasResult2EUTRA_r9::carrierFreq_r9_Get() const
{
    return carrierFreq_r9;
}

std::string MeasResult2EUTRA_r9::carrierFreq_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "carrierFreq_r9:\n";
    out += carrierFreq_r9.ToString(indent+1);
    return out;
}

std::string MeasResult2EUTRA_r9::carrierFreq_r9_ToStringNoNewLines() const
{
    std::string out = "carrierFreq_r9:";
    out += carrierFreq_r9.ToStringNoNewLines();
    return out;
}

int MeasResult2EUTRA_r9::carrierFreq_r9_Clear()
{
    carrierFreq_r9_present = false;
    return 0;
}

bool MeasResult2EUTRA_r9::carrierFreq_r9_IsPresent() const
{
    return carrierFreq_r9_present;
}

MeasResultListEUTRA* MeasResult2EUTRA_r9::measResultList_r9_Set()
{
    measResultList_r9_present = true;
    return &measResultList_r9;
}

int MeasResult2EUTRA_r9::measResultList_r9_Set(MeasResultListEUTRA &value)
{
    measResultList_r9_present = true;
    measResultList_r9 = value;
    return 0;
}

const MeasResultListEUTRA& MeasResult2EUTRA_r9::measResultList_r9_Get() const
{
    return measResultList_r9;
}

std::string MeasResult2EUTRA_r9::measResultList_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "measResultList_r9:\n";
    out += measResultList_r9.ToString(indent+1);
    return out;
}

std::string MeasResult2EUTRA_r9::measResultList_r9_ToStringNoNewLines() const
{
    std::string out = "measResultList_r9:";
    out += measResultList_r9.ToStringNoNewLines();
    return out;
}

int MeasResult2EUTRA_r9::measResultList_r9_Clear()
{
    measResultList_r9_present = false;
    return 0;
}

bool MeasResult2EUTRA_r9::measResultList_r9_IsPresent() const
{
    return measResultList_r9_present;
}

