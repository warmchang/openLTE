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

#include "CellSelectionInfo_v920.h"

#include <cmath>

int CellSelectionInfo_v920::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(q_QualMinOffset_r9_IsPresent());

    // Fields
    {
        if(0 != q_QualMin_r9.Pack(bits))
        {
            printf("CellSelectionInfo_v920:: field pack failure\n");
            return -1;
        }
    }
    if(q_QualMinOffset_r9_IsPresent())
    {
        if(0 != q_QualMinOffset_r9_Pack(bits))
        {
            printf("CellSelectionInfo_v920:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int CellSelectionInfo_v920::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int CellSelectionInfo_v920::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("CellSelectionInfo_v920::Unpack() index out of bounds for optional indiator q_QualMinOffset_r9\n");
        return -1;
    }
    q_QualMinOffset_r9_present = bits[idx++];

    // Fields
    {
        if(0 != q_QualMin_r9.Unpack(bits, idx))
        {
            printf("CellSelectionInfo_v920:: field unpack failure\n");
            return -1;
        }
    }
    if(q_QualMinOffset_r9_present)
    {
        if(0 != q_QualMinOffset_r9_Unpack(bits, idx))
        {
            printf("CellSelectionInfo_v920:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string CellSelectionInfo_v920::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "CellSelectionInfo_v920:\n";
    out += q_QualMin_r9_ToString(indent+1);
    if(q_QualMinOffset_r9_IsPresent())
        out += q_QualMinOffset_r9_ToString(indent+1);
    return out;
}

std::string CellSelectionInfo_v920::ToStringNoNewLines() const
{
    std::string out = "CellSelectionInfo_v920:";
    out += q_QualMin_r9_ToStringNoNewLines();
    if(q_QualMinOffset_r9_IsPresent())
        out += q_QualMinOffset_r9_ToStringNoNewLines();
    return out;
}

Q_QualMin_r9* CellSelectionInfo_v920::q_QualMin_r9_Set()
{
    q_QualMin_r9_present = true;
    return &q_QualMin_r9;
}

int CellSelectionInfo_v920::q_QualMin_r9_Set(Q_QualMin_r9 &value)
{
    q_QualMin_r9_present = true;
    q_QualMin_r9 = value;
    return 0;
}

const Q_QualMin_r9& CellSelectionInfo_v920::q_QualMin_r9_Get() const
{
    return q_QualMin_r9;
}

std::string CellSelectionInfo_v920::q_QualMin_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "q_QualMin_r9:\n";
    out += q_QualMin_r9.ToString(indent+1);
    return out;
}

std::string CellSelectionInfo_v920::q_QualMin_r9_ToStringNoNewLines() const
{
    std::string out = "q_QualMin_r9:";
    out += q_QualMin_r9.ToStringNoNewLines();
    return out;
}

int CellSelectionInfo_v920::q_QualMin_r9_Clear()
{
    q_QualMin_r9_present = false;
    return 0;
}

bool CellSelectionInfo_v920::q_QualMin_r9_IsPresent() const
{
    return q_QualMin_r9_present;
}

int CellSelectionInfo_v920::q_QualMinOffset_r9_Pack(std::vector<uint8_t> &bits)
{
    int64_t val_to_pack = q_QualMinOffset_r9_internal_value - (1);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (8 - 1))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int CellSelectionInfo_v920::q_QualMinOffset_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return q_QualMinOffset_r9_Unpack(bits, idx);
}

int CellSelectionInfo_v920::q_QualMinOffset_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (8 - 1))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("CellSelectionInfo_v920::q_QualMinOffset_r9_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    q_QualMinOffset_r9_internal_value = packed_val + 1;
    q_QualMinOffset_r9_present = true;
    return 0;
}

int64_t CellSelectionInfo_v920::q_QualMinOffset_r9_Value() const
{
    if(q_QualMinOffset_r9_present)
        return q_QualMinOffset_r9_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int CellSelectionInfo_v920::q_QualMinOffset_r9_SetValue(int64_t value)
{
    if(value < 1 || value > 8)
    {
        printf("CellSelectionInfo_v920::q_QualMinOffset_r9_SetValue() range failure\n");
        return -1;
    }
    q_QualMinOffset_r9_internal_value = value;
    q_QualMinOffset_r9_present = true;
    return 0;
}

std::string CellSelectionInfo_v920::q_QualMinOffset_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "q_QualMinOffset_r9 = " + std::to_string(q_QualMinOffset_r9_internal_value) + "\n";
    return out;
}

std::string CellSelectionInfo_v920::q_QualMinOffset_r9_ToStringNoNewLines() const
{
    std::string out = "q_QualMinOffset_r9=" + std::to_string(q_QualMinOffset_r9_internal_value) + ",";
    return out;
}

int CellSelectionInfo_v920::q_QualMinOffset_r9_Clear()
{
    q_QualMinOffset_r9_present = false;
    return 0;
}

bool CellSelectionInfo_v920::q_QualMinOffset_r9_IsPresent() const
{
    return q_QualMinOffset_r9_present;
}

