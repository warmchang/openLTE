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

#include "MCC.h"

#include <cmath>

int MCC::Pack(std::vector<uint8_t> &bits)
{
    if(!present)
    {
        printf("MCC::Pack() presence failure\n");
        return -1;
    }
    for(auto item : internal_value)
        if(0 != item.Pack(bits))
        {
            printf("MCC::Pack() item_pack_failure\n");
            return -1;
        }
    return 0;
}

int MCC::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int MCC::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 3;
    internal_value.clear();
    for(uint32_t i=0; i<size; i++)
    {
        MCC_MNC_Digit tmp;
        if(0 != tmp.Unpack(bits, idx))
        {
            printf("MCC::Unpack() item unpack failure\n");
            return -1;
        }
        internal_value.push_back(tmp);
    }
    present = true;
    return 0;
}

std::vector<MCC_MNC_Digit> MCC::Value() const
{
    if(present)
        return internal_value;
    return {};
}

int MCC::SetValue(std::vector<MCC_MNC_Digit> value)
{
    if(value.size() < 3 || value.size() > 3)
    {
        printf("MCC::SetValue() list size failure\n");
        return -1;
    }
    internal_value = value;
    present = true;
    return 0;
}

std::string MCC::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "MCC:\n";
    for(auto item : internal_value)
        out += item.ToString(indent+1);
    return out;
}

std::string MCC::ToStringNoNewLines() const
{
    std::string out = "MCC:";
    for(auto item : internal_value)
        out += item.ToStringNoNewLines();
    return out;
}

