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

#include "IRAT_ParametersUTRA_TDD128.h"

#include <cmath>

int IRAT_ParametersUTRA_TDD128::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != supportedBandListUTRA_TDD128.Pack(bits))
        {
            printf("IRAT_ParametersUTRA_TDD128:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int IRAT_ParametersUTRA_TDD128::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int IRAT_ParametersUTRA_TDD128::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != supportedBandListUTRA_TDD128.Unpack(bits, idx))
        {
            printf("IRAT_ParametersUTRA_TDD128:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string IRAT_ParametersUTRA_TDD128::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "IRAT_ParametersUTRA_TDD128:\n";
    out += supportedBandListUTRA_TDD128_ToString(indent+1);
    return out;
}

std::string IRAT_ParametersUTRA_TDD128::ToStringNoNewLines() const
{
    std::string out = "IRAT_ParametersUTRA_TDD128:";
    out += supportedBandListUTRA_TDD128_ToStringNoNewLines();
    return out;
}

SupportedBandListUTRA_TDD128* IRAT_ParametersUTRA_TDD128::supportedBandListUTRA_TDD128_Set()
{
    supportedBandListUTRA_TDD128_present = true;
    return &supportedBandListUTRA_TDD128;
}

int IRAT_ParametersUTRA_TDD128::supportedBandListUTRA_TDD128_Set(SupportedBandListUTRA_TDD128 &value)
{
    supportedBandListUTRA_TDD128_present = true;
    supportedBandListUTRA_TDD128 = value;
    return 0;
}

const SupportedBandListUTRA_TDD128& IRAT_ParametersUTRA_TDD128::supportedBandListUTRA_TDD128_Get() const
{
    return supportedBandListUTRA_TDD128;
}

std::string IRAT_ParametersUTRA_TDD128::supportedBandListUTRA_TDD128_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "supportedBandListUTRA_TDD128:\n";
    out += supportedBandListUTRA_TDD128.ToString(indent+1);
    return out;
}

std::string IRAT_ParametersUTRA_TDD128::supportedBandListUTRA_TDD128_ToStringNoNewLines() const
{
    std::string out = "supportedBandListUTRA_TDD128:";
    out += supportedBandListUTRA_TDD128.ToStringNoNewLines();
    return out;
}

int IRAT_ParametersUTRA_TDD128::supportedBandListUTRA_TDD128_Clear()
{
    supportedBandListUTRA_TDD128_present = false;
    return 0;
}

bool IRAT_ParametersUTRA_TDD128::supportedBandListUTRA_TDD128_IsPresent() const
{
    return supportedBandListUTRA_TDD128_present;
}

