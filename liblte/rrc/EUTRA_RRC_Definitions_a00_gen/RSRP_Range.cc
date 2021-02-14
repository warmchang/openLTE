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

#include "RSRP_Range.h"

#include <cmath>

int RSRP_Range::Pack(std::vector<uint8_t> &bits)
{
    if(!present)
    {
        printf("RSRP_Range::Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (97 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int RSRP_Range::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int RSRP_Range::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (97 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("RSRP_Range::Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    internal_value = packed_val + 0;
    present = true;
    return 0;
}

int64_t RSRP_Range::Value() const
{
    if(present)
        return internal_value;
    int64_t tmp = 0;
    return tmp;
}

int RSRP_Range::SetValue(int64_t value)
{
    if(value < 0 || value > 97)
    {
        printf("RSRP_Range::SetValue() range failure\n");
        return -1;
    }
    internal_value = value;
    present = true;
    return 0;
}

std::string RSRP_Range::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "RSRP_Range = " + std::to_string(internal_value) + "\n";
    return out;
}

std::string RSRP_Range::ToStringNoNewLines() const
{
    std::string out = "RSRP_Range=" + std::to_string(internal_value) + ",";
    return out;
}

int RSRP_Range::Clear()
{
    present = false;
    return 0;
}

bool RSRP_Range::IsPresent() const
{
    return present;
}

