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

#include "SupportedBandUTRA_FDD.h"

#include <cmath>

int SupportedBandUTRA_FDD::Pack(std::vector<uint8_t> &bits)
{
    if(!present)
    {
        printf("SupportedBandUTRA_FDD::Pack() presence failure\n");
        return -1;
    }
    if(internal_value > k_bandXVI)
    {
        bits.push_back(1);
    }else{
        bits.push_back(0);
    }
    uint32_t N_bits = 4;
    if(internal_value > k_bandXVI)
        N_bits = 4;
    for(uint32_t i=0; i<N_bits; i++)
    {
        if(internal_value > k_bandXVI)
        {
            bits.push_back(((internal_value - k_bandXVI) >> (N_bits-1-i)) & 1);
        }else{
            bits.push_back((internal_value >> (N_bits-1-i)) & 1);
        }
    }
    return 0;
}

int SupportedBandUTRA_FDD::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int SupportedBandUTRA_FDD::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    if((idx + 1) > bits.size())
    {
        printf("SupportedBandUTRA_FDD::Unpack() index out of bounds for extension\n");
        return -1;
    }
    bool has_extension = bits[idx++];
    uint32_t packed_val = 0;
    uint32_t N_bits = 4;
    if(has_extension)
        N_bits = 4;
    if((idx + N_bits) > bits.size())
    {
        printf("SupportedBandUTRA_FDD::Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(has_extension)
    {
        if(packed_val > 15)
        {
            printf("SupportedBandUTRA_FDD::Unpack() max failure\n");
            return -1;
        }
        internal_value = (Enum)(packed_val + 16);
    }else{
        if(packed_val > 15)
        {
            printf("SupportedBandUTRA_FDD::Unpack() max failure\n");
            return -1;
        }
        internal_value = (Enum)packed_val;
    }
    present = true;
    return 0;
}

SupportedBandUTRA_FDD::Enum SupportedBandUTRA_FDD::Value() const
{
    if(present)
        return internal_value;
    return (SupportedBandUTRA_FDD::Enum)0;
}

int SupportedBandUTRA_FDD::SetValue(Enum value)
{
    internal_value = value;
    present = true;
    return 0;
}

int SupportedBandUTRA_FDD::SetValue(std::string value)
{
    if("bandI" == value)
    {
        internal_value = k_bandI;
        present = true;
        return 0;
    }
    if("bandII" == value)
    {
        internal_value = k_bandII;
        present = true;
        return 0;
    }
    if("bandIII" == value)
    {
        internal_value = k_bandIII;
        present = true;
        return 0;
    }
    if("bandIV" == value)
    {
        internal_value = k_bandIV;
        present = true;
        return 0;
    }
    if("bandV" == value)
    {
        internal_value = k_bandV;
        present = true;
        return 0;
    }
    if("bandVI" == value)
    {
        internal_value = k_bandVI;
        present = true;
        return 0;
    }
    if("bandVII" == value)
    {
        internal_value = k_bandVII;
        present = true;
        return 0;
    }
    if("bandVIII" == value)
    {
        internal_value = k_bandVIII;
        present = true;
        return 0;
    }
    if("bandIX" == value)
    {
        internal_value = k_bandIX;
        present = true;
        return 0;
    }
    if("bandX" == value)
    {
        internal_value = k_bandX;
        present = true;
        return 0;
    }
    if("bandXI" == value)
    {
        internal_value = k_bandXI;
        present = true;
        return 0;
    }
    if("bandXII" == value)
    {
        internal_value = k_bandXII;
        present = true;
        return 0;
    }
    if("bandXIII" == value)
    {
        internal_value = k_bandXIII;
        present = true;
        return 0;
    }
    if("bandXIV" == value)
    {
        internal_value = k_bandXIV;
        present = true;
        return 0;
    }
    if("bandXV" == value)
    {
        internal_value = k_bandXV;
        present = true;
        return 0;
    }
    if("bandXVI" == value)
    {
        internal_value = k_bandXVI;
        present = true;
        return 0;
    }
    if("bandXVII_8a0" == value)
    {
        internal_value = k_bandXVII_8a0;
        present = true;
        return 0;
    }
    if("bandXVIII_8a0" == value)
    {
        internal_value = k_bandXVIII_8a0;
        present = true;
        return 0;
    }
    if("bandXIX_8a0" == value)
    {
        internal_value = k_bandXIX_8a0;
        present = true;
        return 0;
    }
    if("bandXX_8a0" == value)
    {
        internal_value = k_bandXX_8a0;
        present = true;
        return 0;
    }
    if("bandXXI_8a0" == value)
    {
        internal_value = k_bandXXI_8a0;
        present = true;
        return 0;
    }
    if("bandXXII_8a0" == value)
    {
        internal_value = k_bandXXII_8a0;
        present = true;
        return 0;
    }
    if("bandXXIII_8a0" == value)
    {
        internal_value = k_bandXXIII_8a0;
        present = true;
        return 0;
    }
    if("bandXXIV_8a0" == value)
    {
        internal_value = k_bandXXIV_8a0;
        present = true;
        return 0;
    }
    if("bandXXV_8a0" == value)
    {
        internal_value = k_bandXXV_8a0;
        present = true;
        return 0;
    }
    if("bandXXVI_8a0" == value)
    {
        internal_value = k_bandXXVI_8a0;
        present = true;
        return 0;
    }
    if("bandXXVII_8a0" == value)
    {
        internal_value = k_bandXXVII_8a0;
        present = true;
        return 0;
    }
    if("bandXXVIII_8a0" == value)
    {
        internal_value = k_bandXXVIII_8a0;
        present = true;
        return 0;
    }
    if("bandXXIX_8a0" == value)
    {
        internal_value = k_bandXXIX_8a0;
        present = true;
        return 0;
    }
    if("bandXXX_8a0" == value)
    {
        internal_value = k_bandXXX_8a0;
        present = true;
        return 0;
    }
    if("bandXXXI_8a0" == value)
    {
        internal_value = k_bandXXXI_8a0;
        present = true;
        return 0;
    }
    if("bandXXXII_8a0" == value)
    {
        internal_value = k_bandXXXII_8a0;
        present = true;
        return 0;
    }
    return 1;
}

std::string SupportedBandUTRA_FDD::ValueToString(Enum value) const
{
    if(k_bandI == value)
        return "bandI";
    if(k_bandII == value)
        return "bandII";
    if(k_bandIII == value)
        return "bandIII";
    if(k_bandIV == value)
        return "bandIV";
    if(k_bandV == value)
        return "bandV";
    if(k_bandVI == value)
        return "bandVI";
    if(k_bandVII == value)
        return "bandVII";
    if(k_bandVIII == value)
        return "bandVIII";
    if(k_bandIX == value)
        return "bandIX";
    if(k_bandX == value)
        return "bandX";
    if(k_bandXI == value)
        return "bandXI";
    if(k_bandXII == value)
        return "bandXII";
    if(k_bandXIII == value)
        return "bandXIII";
    if(k_bandXIV == value)
        return "bandXIV";
    if(k_bandXV == value)
        return "bandXV";
    if(k_bandXVI == value)
        return "bandXVI";
    if(k_bandXVII_8a0 == value)
        return "bandXVII_8a0";
    if(k_bandXVIII_8a0 == value)
        return "bandXVIII_8a0";
    if(k_bandXIX_8a0 == value)
        return "bandXIX_8a0";
    if(k_bandXX_8a0 == value)
        return "bandXX_8a0";
    if(k_bandXXI_8a0 == value)
        return "bandXXI_8a0";
    if(k_bandXXII_8a0 == value)
        return "bandXXII_8a0";
    if(k_bandXXIII_8a0 == value)
        return "bandXXIII_8a0";
    if(k_bandXXIV_8a0 == value)
        return "bandXXIV_8a0";
    if(k_bandXXV_8a0 == value)
        return "bandXXV_8a0";
    if(k_bandXXVI_8a0 == value)
        return "bandXXVI_8a0";
    if(k_bandXXVII_8a0 == value)
        return "bandXXVII_8a0";
    if(k_bandXXVIII_8a0 == value)
        return "bandXXVIII_8a0";
    if(k_bandXXIX_8a0 == value)
        return "bandXXIX_8a0";
    if(k_bandXXX_8a0 == value)
        return "bandXXX_8a0";
    if(k_bandXXXI_8a0 == value)
        return "bandXXXI_8a0";
    if(k_bandXXXII_8a0 == value)
        return "bandXXXII_8a0";
    return "";
}

uint64_t SupportedBandUTRA_FDD::NumberOfValues() const
{
    return 32;
}

std::string SupportedBandUTRA_FDD::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "SupportedBandUTRA_FDD = " + ValueToString(internal_value) + "\n";
    return out;
}

std::string SupportedBandUTRA_FDD::ToStringNoNewLines() const
{
    std::string out = "SupportedBandUTRA_FDD=" + ValueToString(internal_value) + ",";
    return out;
}

int SupportedBandUTRA_FDD::Clear()
{
    present = false;
    return 0;
}

bool SupportedBandUTRA_FDD::IsPresent() const
{
    return present;
}

