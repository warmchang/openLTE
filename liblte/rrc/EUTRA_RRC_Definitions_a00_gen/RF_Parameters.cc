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

#include "RF_Parameters.h"

#include <cmath>

int RF_Parameters::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != supportedBandListEUTRA.Pack(bits))
        {
            printf("RF_Parameters:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int RF_Parameters::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int RF_Parameters::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != supportedBandListEUTRA.Unpack(bits, idx))
        {
            printf("RF_Parameters:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string RF_Parameters::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "RF_Parameters:\n";
    out += supportedBandListEUTRA_ToString(indent+1);
    return out;
}

std::string RF_Parameters::ToStringNoNewLines() const
{
    std::string out = "RF_Parameters:";
    out += supportedBandListEUTRA_ToStringNoNewLines();
    return out;
}

SupportedBandListEUTRA* RF_Parameters::supportedBandListEUTRA_Set()
{
    supportedBandListEUTRA_present = true;
    return &supportedBandListEUTRA;
}

int RF_Parameters::supportedBandListEUTRA_Set(SupportedBandListEUTRA &value)
{
    supportedBandListEUTRA_present = true;
    supportedBandListEUTRA = value;
    return 0;
}

const SupportedBandListEUTRA& RF_Parameters::supportedBandListEUTRA_Get() const
{
    return supportedBandListEUTRA;
}

std::string RF_Parameters::supportedBandListEUTRA_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "supportedBandListEUTRA:\n";
    out += supportedBandListEUTRA.ToString(indent+1);
    return out;
}

std::string RF_Parameters::supportedBandListEUTRA_ToStringNoNewLines() const
{
    std::string out = "supportedBandListEUTRA:";
    out += supportedBandListEUTRA.ToStringNoNewLines();
    return out;
}

int RF_Parameters::supportedBandListEUTRA_Clear()
{
    supportedBandListEUTRA_present = false;
    return 0;
}

bool RF_Parameters::supportedBandListEUTRA_IsPresent() const
{
    return supportedBandListEUTRA_present;
}

