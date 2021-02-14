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

#include "RACH_ConfigDedicated.h"

#include <cmath>

int RACH_ConfigDedicated::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != ra_PreambleIndex_Pack(bits))
        {
            printf("RACH_ConfigDedicated:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != ra_PRACH_MaskIndex_Pack(bits))
        {
            printf("RACH_ConfigDedicated:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int RACH_ConfigDedicated::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int RACH_ConfigDedicated::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != ra_PreambleIndex_Unpack(bits, idx))
        {
            printf("RACH_ConfigDedicated:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != ra_PRACH_MaskIndex_Unpack(bits, idx))
        {
            printf("RACH_ConfigDedicated:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string RACH_ConfigDedicated::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "RACH_ConfigDedicated:\n";
    out += ra_PreambleIndex_ToString(indent+1);
    out += ra_PRACH_MaskIndex_ToString(indent+1);
    return out;
}

std::string RACH_ConfigDedicated::ToStringNoNewLines() const
{
    std::string out = "RACH_ConfigDedicated:";
    out += ra_PreambleIndex_ToStringNoNewLines();
    out += ra_PRACH_MaskIndex_ToStringNoNewLines();
    return out;
}

int RACH_ConfigDedicated::ra_PreambleIndex_Pack(std::vector<uint8_t> &bits)
{
    if(!ra_PreambleIndex_present)
    {
        printf("RACH_ConfigDedicated::ra_PreambleIndex_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = ra_PreambleIndex_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (63 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int RACH_ConfigDedicated::ra_PreambleIndex_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return ra_PreambleIndex_Unpack(bits, idx);
}

int RACH_ConfigDedicated::ra_PreambleIndex_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (63 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("RACH_ConfigDedicated::ra_PreambleIndex_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    ra_PreambleIndex_internal_value = packed_val + 0;
    ra_PreambleIndex_present = true;
    return 0;
}

int64_t RACH_ConfigDedicated::ra_PreambleIndex_Value() const
{
    if(ra_PreambleIndex_present)
        return ra_PreambleIndex_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int RACH_ConfigDedicated::ra_PreambleIndex_SetValue(int64_t value)
{
    if(value < 0 || value > 63)
    {
        printf("RACH_ConfigDedicated::ra_PreambleIndex_SetValue() range failure\n");
        return -1;
    }
    ra_PreambleIndex_internal_value = value;
    ra_PreambleIndex_present = true;
    return 0;
}

std::string RACH_ConfigDedicated::ra_PreambleIndex_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ra_PreambleIndex = " + std::to_string(ra_PreambleIndex_internal_value) + "\n";
    return out;
}

std::string RACH_ConfigDedicated::ra_PreambleIndex_ToStringNoNewLines() const
{
    std::string out = "ra_PreambleIndex=" + std::to_string(ra_PreambleIndex_internal_value) + ",";
    return out;
}

int RACH_ConfigDedicated::ra_PreambleIndex_Clear()
{
    ra_PreambleIndex_present = false;
    return 0;
}

bool RACH_ConfigDedicated::ra_PreambleIndex_IsPresent() const
{
    return ra_PreambleIndex_present;
}

int RACH_ConfigDedicated::ra_PRACH_MaskIndex_Pack(std::vector<uint8_t> &bits)
{
    if(!ra_PRACH_MaskIndex_present)
    {
        printf("RACH_ConfigDedicated::ra_PRACH_MaskIndex_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = ra_PRACH_MaskIndex_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (15 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int RACH_ConfigDedicated::ra_PRACH_MaskIndex_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return ra_PRACH_MaskIndex_Unpack(bits, idx);
}

int RACH_ConfigDedicated::ra_PRACH_MaskIndex_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (15 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("RACH_ConfigDedicated::ra_PRACH_MaskIndex_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    ra_PRACH_MaskIndex_internal_value = packed_val + 0;
    ra_PRACH_MaskIndex_present = true;
    return 0;
}

int64_t RACH_ConfigDedicated::ra_PRACH_MaskIndex_Value() const
{
    if(ra_PRACH_MaskIndex_present)
        return ra_PRACH_MaskIndex_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int RACH_ConfigDedicated::ra_PRACH_MaskIndex_SetValue(int64_t value)
{
    if(value < 0 || value > 15)
    {
        printf("RACH_ConfigDedicated::ra_PRACH_MaskIndex_SetValue() range failure\n");
        return -1;
    }
    ra_PRACH_MaskIndex_internal_value = value;
    ra_PRACH_MaskIndex_present = true;
    return 0;
}

std::string RACH_ConfigDedicated::ra_PRACH_MaskIndex_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ra_PRACH_MaskIndex = " + std::to_string(ra_PRACH_MaskIndex_internal_value) + "\n";
    return out;
}

std::string RACH_ConfigDedicated::ra_PRACH_MaskIndex_ToStringNoNewLines() const
{
    std::string out = "ra_PRACH_MaskIndex=" + std::to_string(ra_PRACH_MaskIndex_internal_value) + ",";
    return out;
}

int RACH_ConfigDedicated::ra_PRACH_MaskIndex_Clear()
{
    ra_PRACH_MaskIndex_present = false;
    return 0;
}

bool RACH_ConfigDedicated::ra_PRACH_MaskIndex_IsPresent() const
{
    return ra_PRACH_MaskIndex_present;
}

