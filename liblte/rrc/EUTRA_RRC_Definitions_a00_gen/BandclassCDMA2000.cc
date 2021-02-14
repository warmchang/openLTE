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

#include "BandclassCDMA2000.h"

#include <cmath>

int BandclassCDMA2000::Pack(std::vector<uint8_t> &bits)
{
    if(!present)
    {
        printf("BandclassCDMA2000::Pack() presence failure\n");
        return -1;
    }
    if(internal_value > k_spare1)
    {
        bits.push_back(1);
    }else{
        bits.push_back(0);
    }
    uint32_t N_bits = 5;
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

int BandclassCDMA2000::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int BandclassCDMA2000::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    if((idx + 1) > bits.size())
    {
        printf("BandclassCDMA2000::Unpack() index out of bounds for extension\n");
        return -1;
    }
    bool has_extension = bits[idx++];
    uint32_t packed_val = 0;
    uint32_t N_bits = 5;
    if(has_extension)
        N_bits = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("BandclassCDMA2000::Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(has_extension)
    {
        internal_value = (Enum)(packed_val + 32);
    }else{
        if(packed_val > 31)
        {
            printf("BandclassCDMA2000::Unpack() max failure\n");
            return -1;
        }
        internal_value = (Enum)packed_val;
    }
    present = true;
    return 0;
}

BandclassCDMA2000::Enum BandclassCDMA2000::Value() const
{
    if(present)
        return internal_value;
    return (BandclassCDMA2000::Enum)0;
}

int BandclassCDMA2000::SetValue(Enum value)
{
    internal_value = value;
    present = true;
    return 0;
}

int BandclassCDMA2000::SetValue(std::string value)
{
    if("bc0" == value)
    {
        internal_value = k_bc0;
        present = true;
        return 0;
    }
    if("bc1" == value)
    {
        internal_value = k_bc1;
        present = true;
        return 0;
    }
    if("bc2" == value)
    {
        internal_value = k_bc2;
        present = true;
        return 0;
    }
    if("bc3" == value)
    {
        internal_value = k_bc3;
        present = true;
        return 0;
    }
    if("bc4" == value)
    {
        internal_value = k_bc4;
        present = true;
        return 0;
    }
    if("bc5" == value)
    {
        internal_value = k_bc5;
        present = true;
        return 0;
    }
    if("bc6" == value)
    {
        internal_value = k_bc6;
        present = true;
        return 0;
    }
    if("bc7" == value)
    {
        internal_value = k_bc7;
        present = true;
        return 0;
    }
    if("bc8" == value)
    {
        internal_value = k_bc8;
        present = true;
        return 0;
    }
    if("bc9" == value)
    {
        internal_value = k_bc9;
        present = true;
        return 0;
    }
    if("bc10" == value)
    {
        internal_value = k_bc10;
        present = true;
        return 0;
    }
    if("bc11" == value)
    {
        internal_value = k_bc11;
        present = true;
        return 0;
    }
    if("bc12" == value)
    {
        internal_value = k_bc12;
        present = true;
        return 0;
    }
    if("bc13" == value)
    {
        internal_value = k_bc13;
        present = true;
        return 0;
    }
    if("bc14" == value)
    {
        internal_value = k_bc14;
        present = true;
        return 0;
    }
    if("bc15" == value)
    {
        internal_value = k_bc15;
        present = true;
        return 0;
    }
    if("bc16" == value)
    {
        internal_value = k_bc16;
        present = true;
        return 0;
    }
    if("bc17" == value)
    {
        internal_value = k_bc17;
        present = true;
        return 0;
    }
    if("spare14" == value)
    {
        internal_value = k_spare14;
        present = true;
        return 0;
    }
    if("spare13" == value)
    {
        internal_value = k_spare13;
        present = true;
        return 0;
    }
    if("spare12" == value)
    {
        internal_value = k_spare12;
        present = true;
        return 0;
    }
    if("spare11" == value)
    {
        internal_value = k_spare11;
        present = true;
        return 0;
    }
    if("spare10" == value)
    {
        internal_value = k_spare10;
        present = true;
        return 0;
    }
    if("spare9" == value)
    {
        internal_value = k_spare9;
        present = true;
        return 0;
    }
    if("spare8" == value)
    {
        internal_value = k_spare8;
        present = true;
        return 0;
    }
    if("spare7" == value)
    {
        internal_value = k_spare7;
        present = true;
        return 0;
    }
    if("spare6" == value)
    {
        internal_value = k_spare6;
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

std::string BandclassCDMA2000::ValueToString(Enum value) const
{
    if(k_bc0 == value)
        return "bc0";
    if(k_bc1 == value)
        return "bc1";
    if(k_bc2 == value)
        return "bc2";
    if(k_bc3 == value)
        return "bc3";
    if(k_bc4 == value)
        return "bc4";
    if(k_bc5 == value)
        return "bc5";
    if(k_bc6 == value)
        return "bc6";
    if(k_bc7 == value)
        return "bc7";
    if(k_bc8 == value)
        return "bc8";
    if(k_bc9 == value)
        return "bc9";
    if(k_bc10 == value)
        return "bc10";
    if(k_bc11 == value)
        return "bc11";
    if(k_bc12 == value)
        return "bc12";
    if(k_bc13 == value)
        return "bc13";
    if(k_bc14 == value)
        return "bc14";
    if(k_bc15 == value)
        return "bc15";
    if(k_bc16 == value)
        return "bc16";
    if(k_bc17 == value)
        return "bc17";
    if(k_spare14 == value)
        return "spare14";
    if(k_spare13 == value)
        return "spare13";
    if(k_spare12 == value)
        return "spare12";
    if(k_spare11 == value)
        return "spare11";
    if(k_spare10 == value)
        return "spare10";
    if(k_spare9 == value)
        return "spare9";
    if(k_spare8 == value)
        return "spare8";
    if(k_spare7 == value)
        return "spare7";
    if(k_spare6 == value)
        return "spare6";
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

uint64_t BandclassCDMA2000::NumberOfValues() const
{
    return 32;
}

std::string BandclassCDMA2000::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "BandclassCDMA2000 = " + ValueToString(internal_value) + "\n";
    return out;
}

std::string BandclassCDMA2000::ToStringNoNewLines() const
{
    std::string out = "BandclassCDMA2000=" + ValueToString(internal_value) + ",";
    return out;
}

int BandclassCDMA2000::Clear()
{
    present = false;
    return 0;
}

bool BandclassCDMA2000::IsPresent() const
{
    return present;
}

