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

#include "PresenceAntennaPort1.h"

#include <cmath>

int PresenceAntennaPort1::Pack(std::vector<uint8_t> &bits)
{
    if(!present)
    {
        printf("PresenceAntennaPort1::Pack() presence failure\n");
        return -1;
    }
    bits.push_back(internal_value);
    return 0;
}

int PresenceAntennaPort1::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int PresenceAntennaPort1::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    if((idx + 1) > bits.size())
    {
        printf("PresenceAntennaPort1::Unpack() index out of bounds\n");
        return -1;
    }
    internal_value = bits[idx++];
    present = true;
    return 0;
}

bool PresenceAntennaPort1::Value() const
{
    if(present)
        return internal_value;
    return false;
}

int PresenceAntennaPort1::SetValue(bool value)
{
    internal_value = value;
    present = true;
    return 0;
}

std::string PresenceAntennaPort1::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "PresenceAntennaPort1 = " + std::to_string(internal_value) + "\n";
    return out;
}

std::string PresenceAntennaPort1::ToStringNoNewLines() const
{
    std::string out = "PresenceAntennaPort1=" + std::to_string(internal_value) + ",";
    return out;
}

int PresenceAntennaPort1::Clear()
{
    present = false;
    return 0;
}

bool PresenceAntennaPort1::IsPresent() const
{
    return present;
}

