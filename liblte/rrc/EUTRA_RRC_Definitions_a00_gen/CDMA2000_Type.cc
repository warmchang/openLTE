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

#include "CDMA2000_Type.h"

#include <cmath>

int CDMA2000_Type::Pack(std::vector<uint8_t> &bits)
{
    if(!present)
    {
        printf("CDMA2000_Type::Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int CDMA2000_Type::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int CDMA2000_Type::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("CDMA2000_Type::Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 1)
    {
        printf("CDMA2000_Type::Unpack() max failure\n");
        return -1;
    }
    internal_value = (Enum)packed_val;
    present = true;
    return 0;
}

CDMA2000_Type::Enum CDMA2000_Type::Value() const
{
    if(present)
        return internal_value;
    return (CDMA2000_Type::Enum)0;
}

int CDMA2000_Type::SetValue(Enum value)
{
    internal_value = value;
    present = true;
    return 0;
}

int CDMA2000_Type::SetValue(std::string value)
{
    if("type1XRTT" == value)
    {
        internal_value = k_type1XRTT;
        present = true;
        return 0;
    }
    if("typeHRPD" == value)
    {
        internal_value = k_typeHRPD;
        present = true;
        return 0;
    }
    return 1;
}

std::string CDMA2000_Type::ValueToString(Enum value) const
{
    if(k_type1XRTT == value)
        return "type1XRTT";
    if(k_typeHRPD == value)
        return "typeHRPD";
    return "";
}

uint64_t CDMA2000_Type::NumberOfValues() const
{
    return 2;
}

std::string CDMA2000_Type::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "CDMA2000_Type = " + ValueToString(internal_value) + "\n";
    return out;
}

std::string CDMA2000_Type::ToStringNoNewLines() const
{
    std::string out = "CDMA2000_Type=" + ValueToString(internal_value) + ",";
    return out;
}

int CDMA2000_Type::Clear()
{
    present = false;
    return 0;
}

bool CDMA2000_Type::IsPresent() const
{
    return present;
}

