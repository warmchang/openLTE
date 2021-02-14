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

#include "MeasId.h"

#include <cmath>

#include "maxMeasId.h"

int MeasId::Pack(std::vector<uint8_t> &bits)
{
    if(!present)
    {
        printf("MeasId::Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = internal_value - (1);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (maxMeasId - 1))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int MeasId::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int MeasId::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (maxMeasId - 1))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("MeasId::Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    internal_value = packed_val + 1;
    present = true;
    return 0;
}

int64_t MeasId::Value() const
{
    if(present)
        return internal_value;
    int64_t tmp = 0;
    return tmp;
}

int MeasId::SetValue(int64_t value)
{
    if(value < 1 || value > maxMeasId)
    {
        printf("MeasId::SetValue() range failure\n");
        return -1;
    }
    internal_value = value;
    present = true;
    return 0;
}

std::string MeasId::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "MeasId = " + std::to_string(internal_value) + "\n";
    return out;
}

std::string MeasId::ToStringNoNewLines() const
{
    std::string out = "MeasId=" + std::to_string(internal_value) + ",";
    return out;
}

int MeasId::Clear()
{
    present = false;
    return 0;
}

bool MeasId::IsPresent() const
{
    return present;
}

