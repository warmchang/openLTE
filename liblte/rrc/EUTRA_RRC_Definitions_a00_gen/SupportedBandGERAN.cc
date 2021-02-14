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

#include "SupportedBandGERAN.h"

#include <cmath>

int SupportedBandGERAN::Pack(std::vector<uint8_t> &bits)
{
    if(!present)
    {
        printf("SupportedBandGERAN::Pack() presence failure\n");
        return -1;
    }
    if(internal_value > k_spare1)
    {
        bits.push_back(1);
    }else{
        bits.push_back(0);
    }
    uint32_t N_bits = 4;
    if(internal_value > k_spare1)
        N_bits = 0;
    for(uint32_t i=0; i<N_bits; i++)
    {
        if(internal_value > k_spare1)
        {
            bits.push_back(((internal_value - k_spare1) >> (N_bits-1-i)) & 1);
        }else{
            bits.push_back((internal_value >> (N_bits-1-i)) & 1);
        }
    }
    return 0;
}

int SupportedBandGERAN::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int SupportedBandGERAN::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    if((idx + 1) > bits.size())
    {
        printf("SupportedBandGERAN::Unpack() index out of bounds for extension\n");
        return -1;
    }
    bool has_extension = bits[idx++];
    uint32_t packed_val = 0;
    uint32_t N_bits = 4;
    if(has_extension)
        N_bits = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("SupportedBandGERAN::Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(has_extension)
    {
        internal_value = (Enum)(packed_val + 16);
    }else{
        if(packed_val > 15)
        {
            printf("SupportedBandGERAN::Unpack() max failure\n");
            return -1;
        }
        internal_value = (Enum)packed_val;
    }
    present = true;
    return 0;
}

SupportedBandGERAN::Enum SupportedBandGERAN::Value() const
{
    if(present)
        return internal_value;
    return (SupportedBandGERAN::Enum)0;
}

int SupportedBandGERAN::SetValue(Enum value)
{
    internal_value = value;
    present = true;
    return 0;
}

int SupportedBandGERAN::SetValue(std::string value)
{
    if("gsm450" == value)
    {
        internal_value = k_gsm450;
        present = true;
        return 0;
    }
    if("gsm480" == value)
    {
        internal_value = k_gsm480;
        present = true;
        return 0;
    }
    if("gsm710" == value)
    {
        internal_value = k_gsm710;
        present = true;
        return 0;
    }
    if("gsm750" == value)
    {
        internal_value = k_gsm750;
        present = true;
        return 0;
    }
    if("gsm810" == value)
    {
        internal_value = k_gsm810;
        present = true;
        return 0;
    }
    if("gsm850" == value)
    {
        internal_value = k_gsm850;
        present = true;
        return 0;
    }
    if("gsm900P" == value)
    {
        internal_value = k_gsm900P;
        present = true;
        return 0;
    }
    if("gsm900E" == value)
    {
        internal_value = k_gsm900E;
        present = true;
        return 0;
    }
    if("gsm900R" == value)
    {
        internal_value = k_gsm900R;
        present = true;
        return 0;
    }
    if("gsm1800" == value)
    {
        internal_value = k_gsm1800;
        present = true;
        return 0;
    }
    if("gsm1900" == value)
    {
        internal_value = k_gsm1900;
        present = true;
        return 0;
    }
    if("spare5" == value)
    {
        internal_value = k_spare5;
        present = true;
        return 0;
    }
    if("spare4" == value)
    {
        internal_value = k_spare4;
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

std::string SupportedBandGERAN::ValueToString(Enum value) const
{
    if(k_gsm450 == value)
        return "gsm450";
    if(k_gsm480 == value)
        return "gsm480";
    if(k_gsm710 == value)
        return "gsm710";
    if(k_gsm750 == value)
        return "gsm750";
    if(k_gsm810 == value)
        return "gsm810";
    if(k_gsm850 == value)
        return "gsm850";
    if(k_gsm900P == value)
        return "gsm900P";
    if(k_gsm900E == value)
        return "gsm900E";
    if(k_gsm900R == value)
        return "gsm900R";
    if(k_gsm1800 == value)
        return "gsm1800";
    if(k_gsm1900 == value)
        return "gsm1900";
    if(k_spare5 == value)
        return "spare5";
    if(k_spare4 == value)
        return "spare4";
    if(k_spare3 == value)
        return "spare3";
    if(k_spare2 == value)
        return "spare2";
    if(k_spare1 == value)
        return "spare1";
    return "";
}

uint64_t SupportedBandGERAN::NumberOfValues() const
{
    return 16;
}

std::string SupportedBandGERAN::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "SupportedBandGERAN = " + ValueToString(internal_value) + "\n";
    return out;
}

std::string SupportedBandGERAN::ToStringNoNewLines() const
{
    std::string out = "SupportedBandGERAN=" + ValueToString(internal_value) + ",";
    return out;
}

int SupportedBandGERAN::Clear()
{
    present = false;
    return 0;
}

bool SupportedBandGERAN::IsPresent() const
{
    return present;
}

