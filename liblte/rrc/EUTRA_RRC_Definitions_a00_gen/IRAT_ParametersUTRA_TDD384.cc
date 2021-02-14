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

#include "IRAT_ParametersUTRA_TDD384.h"

#include <cmath>

int IRAT_ParametersUTRA_TDD384::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != supportedBandListUTRA_TDD384.Pack(bits))
        {
            printf("IRAT_ParametersUTRA_TDD384:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int IRAT_ParametersUTRA_TDD384::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int IRAT_ParametersUTRA_TDD384::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != supportedBandListUTRA_TDD384.Unpack(bits, idx))
        {
            printf("IRAT_ParametersUTRA_TDD384:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string IRAT_ParametersUTRA_TDD384::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "IRAT_ParametersUTRA_TDD384:\n";
    out += supportedBandListUTRA_TDD384_ToString(indent+1);
    return out;
}

std::string IRAT_ParametersUTRA_TDD384::ToStringNoNewLines() const
{
    std::string out = "IRAT_ParametersUTRA_TDD384:";
    out += supportedBandListUTRA_TDD384_ToStringNoNewLines();
    return out;
}

SupportedBandListUTRA_TDD384* IRAT_ParametersUTRA_TDD384::supportedBandListUTRA_TDD384_Set()
{
    supportedBandListUTRA_TDD384_present = true;
    return &supportedBandListUTRA_TDD384;
}

int IRAT_ParametersUTRA_TDD384::supportedBandListUTRA_TDD384_Set(SupportedBandListUTRA_TDD384 &value)
{
    supportedBandListUTRA_TDD384_present = true;
    supportedBandListUTRA_TDD384 = value;
    return 0;
}

const SupportedBandListUTRA_TDD384& IRAT_ParametersUTRA_TDD384::supportedBandListUTRA_TDD384_Get() const
{
    return supportedBandListUTRA_TDD384;
}

std::string IRAT_ParametersUTRA_TDD384::supportedBandListUTRA_TDD384_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "supportedBandListUTRA_TDD384:\n";
    out += supportedBandListUTRA_TDD384.ToString(indent+1);
    return out;
}

std::string IRAT_ParametersUTRA_TDD384::supportedBandListUTRA_TDD384_ToStringNoNewLines() const
{
    std::string out = "supportedBandListUTRA_TDD384:";
    out += supportedBandListUTRA_TDD384.ToStringNoNewLines();
    return out;
}

int IRAT_ParametersUTRA_TDD384::supportedBandListUTRA_TDD384_Clear()
{
    supportedBandListUTRA_TDD384_present = false;
    return 0;
}

bool IRAT_ParametersUTRA_TDD384::supportedBandListUTRA_TDD384_IsPresent() const
{
    return supportedBandListUTRA_TDD384_present;
}

