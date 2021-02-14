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

#include "SupportedBandEUTRA.h"

#include <cmath>

int SupportedBandEUTRA::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != bandEUTRA_Pack(bits))
        {
            printf("SupportedBandEUTRA:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != halfDuplex_Pack(bits))
        {
            printf("SupportedBandEUTRA:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int SupportedBandEUTRA::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int SupportedBandEUTRA::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != bandEUTRA_Unpack(bits, idx))
        {
            printf("SupportedBandEUTRA:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != halfDuplex_Unpack(bits, idx))
        {
            printf("SupportedBandEUTRA:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string SupportedBandEUTRA::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "SupportedBandEUTRA:\n";
    out += bandEUTRA_ToString(indent+1);
    out += halfDuplex_ToString(indent+1);
    return out;
}

std::string SupportedBandEUTRA::ToStringNoNewLines() const
{
    std::string out = "SupportedBandEUTRA:";
    out += bandEUTRA_ToStringNoNewLines();
    out += halfDuplex_ToStringNoNewLines();
    return out;
}

int SupportedBandEUTRA::bandEUTRA_Pack(std::vector<uint8_t> &bits)
{
    if(!bandEUTRA_present)
    {
        printf("SupportedBandEUTRA::bandEUTRA_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = bandEUTRA_internal_value - (1);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (64 - 1))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int SupportedBandEUTRA::bandEUTRA_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return bandEUTRA_Unpack(bits, idx);
}

int SupportedBandEUTRA::bandEUTRA_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (64 - 1))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("SupportedBandEUTRA::bandEUTRA_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    bandEUTRA_internal_value = packed_val + 1;
    bandEUTRA_present = true;
    return 0;
}

int64_t SupportedBandEUTRA::bandEUTRA_Value() const
{
    if(bandEUTRA_present)
        return bandEUTRA_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int SupportedBandEUTRA::bandEUTRA_SetValue(int64_t value)
{
    if(value < 1 || value > 64)
    {
        printf("SupportedBandEUTRA::bandEUTRA_SetValue() range failure\n");
        return -1;
    }
    bandEUTRA_internal_value = value;
    bandEUTRA_present = true;
    return 0;
}

std::string SupportedBandEUTRA::bandEUTRA_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "bandEUTRA = " + std::to_string(bandEUTRA_internal_value) + "\n";
    return out;
}

std::string SupportedBandEUTRA::bandEUTRA_ToStringNoNewLines() const
{
    std::string out = "bandEUTRA=" + std::to_string(bandEUTRA_internal_value) + ",";
    return out;
}

int SupportedBandEUTRA::bandEUTRA_Clear()
{
    bandEUTRA_present = false;
    return 0;
}

bool SupportedBandEUTRA::bandEUTRA_IsPresent() const
{
    return bandEUTRA_present;
}

int SupportedBandEUTRA::halfDuplex_Pack(std::vector<uint8_t> &bits)
{
    if(!halfDuplex_present)
    {
        printf("SupportedBandEUTRA::halfDuplex_Pack() presence failure\n");
        return -1;
    }
    bits.push_back(halfDuplex_internal_value);
    return 0;
}

int SupportedBandEUTRA::halfDuplex_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return halfDuplex_Unpack(bits, idx);
}

int SupportedBandEUTRA::halfDuplex_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    if((idx + 1) > bits.size())
    {
        printf("SupportedBandEUTRA::halfDuplex_Unpack() index out of bounds\n");
        return -1;
    }
    halfDuplex_internal_value = bits[idx++];
    halfDuplex_present = true;
    return 0;
}

bool SupportedBandEUTRA::halfDuplex_Value() const
{
    if(halfDuplex_present)
        return halfDuplex_internal_value;
    return false;
}

int SupportedBandEUTRA::halfDuplex_SetValue(bool value)
{
    halfDuplex_internal_value = value;
    halfDuplex_present = true;
    return 0;
}

std::string SupportedBandEUTRA::halfDuplex_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "halfDuplex = " + std::to_string(halfDuplex_internal_value) + "\n";
    return out;
}

std::string SupportedBandEUTRA::halfDuplex_ToStringNoNewLines() const
{
    std::string out = "halfDuplex=" + std::to_string(halfDuplex_internal_value) + ",";
    return out;
}

int SupportedBandEUTRA::halfDuplex_Clear()
{
    halfDuplex_present = false;
    return 0;
}

bool SupportedBandEUTRA::halfDuplex_IsPresent() const
{
    return halfDuplex_present;
}

