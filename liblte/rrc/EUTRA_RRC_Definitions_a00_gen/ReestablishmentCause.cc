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

#include "ReestablishmentCause.h"

#include <cmath>

int ReestablishmentCause::Pack(std::vector<uint8_t> &bits)
{
    if(!present)
    {
        printf("ReestablishmentCause::Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 2;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int ReestablishmentCause::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int ReestablishmentCause::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 2;
    if((idx + N_bits) > bits.size())
    {
        printf("ReestablishmentCause::Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 3)
    {
        printf("ReestablishmentCause::Unpack() max failure\n");
        return -1;
    }
    internal_value = (Enum)packed_val;
    present = true;
    return 0;
}

ReestablishmentCause::Enum ReestablishmentCause::Value() const
{
    if(present)
        return internal_value;
    return (ReestablishmentCause::Enum)0;
}

int ReestablishmentCause::SetValue(Enum value)
{
    internal_value = value;
    present = true;
    return 0;
}

int ReestablishmentCause::SetValue(std::string value)
{
    if("reconfigurationFailure" == value)
    {
        internal_value = k_reconfigurationFailure;
        present = true;
        return 0;
    }
    if("handoverFailure" == value)
    {
        internal_value = k_handoverFailure;
        present = true;
        return 0;
    }
    if("otherFailure" == value)
    {
        internal_value = k_otherFailure;
        present = true;
        return 0;
    }
    if("spare1" == value)
    {
        internal_value = k_spare1;
        present = true;
        return 0;
    }
    return 1;
}

std::string ReestablishmentCause::ValueToString(Enum value) const
{
    if(k_reconfigurationFailure == value)
        return "reconfigurationFailure";
    if(k_handoverFailure == value)
        return "handoverFailure";
    if(k_otherFailure == value)
        return "otherFailure";
    if(k_spare1 == value)
        return "spare1";
    return "";
}

uint64_t ReestablishmentCause::NumberOfValues() const
{
    return 4;
}

std::string ReestablishmentCause::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ReestablishmentCause = " + ValueToString(internal_value) + "\n";
    return out;
}

std::string ReestablishmentCause::ToStringNoNewLines() const
{
    std::string out = "ReestablishmentCause=" + ValueToString(internal_value) + ",";
    return out;
}

int ReestablishmentCause::Clear()
{
    present = false;
    return 0;
}

bool ReestablishmentCause::IsPresent() const
{
    return present;
}

