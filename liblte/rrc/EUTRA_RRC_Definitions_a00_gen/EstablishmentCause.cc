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

#include "EstablishmentCause.h"

#include <cmath>

int EstablishmentCause::Pack(std::vector<uint8_t> &bits)
{
    if(!present)
    {
        printf("EstablishmentCause::Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 3;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int EstablishmentCause::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int EstablishmentCause::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 3;
    if((idx + N_bits) > bits.size())
    {
        printf("EstablishmentCause::Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 7)
    {
        printf("EstablishmentCause::Unpack() max failure\n");
        return -1;
    }
    internal_value = (Enum)packed_val;
    present = true;
    return 0;
}

EstablishmentCause::Enum EstablishmentCause::Value() const
{
    if(present)
        return internal_value;
    return (EstablishmentCause::Enum)0;
}

int EstablishmentCause::SetValue(Enum value)
{
    internal_value = value;
    present = true;
    return 0;
}

int EstablishmentCause::SetValue(std::string value)
{
    if("emergency" == value)
    {
        internal_value = k_emergency;
        present = true;
        return 0;
    }
    if("highPriorityAccess" == value)
    {
        internal_value = k_highPriorityAccess;
        present = true;
        return 0;
    }
    if("mt_Access" == value)
    {
        internal_value = k_mt_Access;
        present = true;
        return 0;
    }
    if("mo_Signalling" == value)
    {
        internal_value = k_mo_Signalling;
        present = true;
        return 0;
    }
    if("mo_Data" == value)
    {
        internal_value = k_mo_Data;
        present = true;
        return 0;
    }
    if("spare3" == value)
    {
        internal_value = k_spare3;
        present = true;
        return 0;
    }
    if("spare2" == value)
    {
        internal_value = k_spare2;
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

std::string EstablishmentCause::ValueToString(Enum value) const
{
    if(k_emergency == value)
        return "emergency";
    if(k_highPriorityAccess == value)
        return "highPriorityAccess";
    if(k_mt_Access == value)
        return "mt_Access";
    if(k_mo_Signalling == value)
        return "mo_Signalling";
    if(k_mo_Data == value)
        return "mo_Data";
    if(k_spare3 == value)
        return "spare3";
    if(k_spare2 == value)
        return "spare2";
    if(k_spare1 == value)
        return "spare1";
    return "";
}

uint64_t EstablishmentCause::NumberOfValues() const
{
    return 8;
}

std::string EstablishmentCause::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "EstablishmentCause = " + ValueToString(internal_value) + "\n";
    return out;
}

std::string EstablishmentCause::ToStringNoNewLines() const
{
    std::string out = "EstablishmentCause=" + ValueToString(internal_value) + ",";
    return out;
}

int EstablishmentCause::Clear()
{
    present = false;
    return 0;
}

bool EstablishmentCause::IsPresent() const
{
    return present;
}

