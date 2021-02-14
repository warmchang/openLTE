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

#include "MeasParameters.h"

#include <cmath>

int MeasParameters::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != bandListEUTRA.Pack(bits))
        {
            printf("MeasParameters:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int MeasParameters::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int MeasParameters::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != bandListEUTRA.Unpack(bits, idx))
        {
            printf("MeasParameters:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string MeasParameters::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "MeasParameters:\n";
    out += bandListEUTRA_ToString(indent+1);
    return out;
}

std::string MeasParameters::ToStringNoNewLines() const
{
    std::string out = "MeasParameters:";
    out += bandListEUTRA_ToStringNoNewLines();
    return out;
}

BandListEUTRA* MeasParameters::bandListEUTRA_Set()
{
    bandListEUTRA_present = true;
    return &bandListEUTRA;
}

int MeasParameters::bandListEUTRA_Set(BandListEUTRA &value)
{
    bandListEUTRA_present = true;
    bandListEUTRA = value;
    return 0;
}

const BandListEUTRA& MeasParameters::bandListEUTRA_Get() const
{
    return bandListEUTRA;
}

std::string MeasParameters::bandListEUTRA_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "bandListEUTRA:\n";
    out += bandListEUTRA.ToString(indent+1);
    return out;
}

std::string MeasParameters::bandListEUTRA_ToStringNoNewLines() const
{
    std::string out = "bandListEUTRA:";
    out += bandListEUTRA.ToStringNoNewLines();
    return out;
}

int MeasParameters::bandListEUTRA_Clear()
{
    bandListEUTRA_present = false;
    return 0;
}

bool MeasParameters::bandListEUTRA_IsPresent() const
{
    return bandListEUTRA_present;
}

