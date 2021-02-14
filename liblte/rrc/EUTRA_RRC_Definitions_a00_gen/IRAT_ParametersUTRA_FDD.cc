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

#include "IRAT_ParametersUTRA_FDD.h"

#include <cmath>

int IRAT_ParametersUTRA_FDD::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != supportedBandListUTRA_FDD.Pack(bits))
        {
            printf("IRAT_ParametersUTRA_FDD:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int IRAT_ParametersUTRA_FDD::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int IRAT_ParametersUTRA_FDD::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != supportedBandListUTRA_FDD.Unpack(bits, idx))
        {
            printf("IRAT_ParametersUTRA_FDD:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string IRAT_ParametersUTRA_FDD::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "IRAT_ParametersUTRA_FDD:\n";
    out += supportedBandListUTRA_FDD_ToString(indent+1);
    return out;
}

std::string IRAT_ParametersUTRA_FDD::ToStringNoNewLines() const
{
    std::string out = "IRAT_ParametersUTRA_FDD:";
    out += supportedBandListUTRA_FDD_ToStringNoNewLines();
    return out;
}

SupportedBandListUTRA_FDD* IRAT_ParametersUTRA_FDD::supportedBandListUTRA_FDD_Set()
{
    supportedBandListUTRA_FDD_present = true;
    return &supportedBandListUTRA_FDD;
}

int IRAT_ParametersUTRA_FDD::supportedBandListUTRA_FDD_Set(SupportedBandListUTRA_FDD &value)
{
    supportedBandListUTRA_FDD_present = true;
    supportedBandListUTRA_FDD = value;
    return 0;
}

const SupportedBandListUTRA_FDD& IRAT_ParametersUTRA_FDD::supportedBandListUTRA_FDD_Get() const
{
    return supportedBandListUTRA_FDD;
}

std::string IRAT_ParametersUTRA_FDD::supportedBandListUTRA_FDD_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "supportedBandListUTRA_FDD:\n";
    out += supportedBandListUTRA_FDD.ToString(indent+1);
    return out;
}

std::string IRAT_ParametersUTRA_FDD::supportedBandListUTRA_FDD_ToStringNoNewLines() const
{
    std::string out = "supportedBandListUTRA_FDD:";
    out += supportedBandListUTRA_FDD.ToStringNoNewLines();
    return out;
}

int IRAT_ParametersUTRA_FDD::supportedBandListUTRA_FDD_Clear()
{
    supportedBandListUTRA_FDD_present = false;
    return 0;
}

bool IRAT_ParametersUTRA_FDD::supportedBandListUTRA_FDD_IsPresent() const
{
    return supportedBandListUTRA_FDD_present;
}

