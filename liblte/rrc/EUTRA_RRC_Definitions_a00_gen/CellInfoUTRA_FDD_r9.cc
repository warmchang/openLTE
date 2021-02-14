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

#include "CellInfoUTRA_FDD_r9.h"

#include <cmath>

int CellInfoUTRA_FDD_r9::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != physCellId_r9.Pack(bits))
        {
            printf("CellInfoUTRA_FDD_r9:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != utra_BCCH_Container_r9_Pack(bits))
        {
            printf("CellInfoUTRA_FDD_r9:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int CellInfoUTRA_FDD_r9::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int CellInfoUTRA_FDD_r9::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != physCellId_r9.Unpack(bits, idx))
        {
            printf("CellInfoUTRA_FDD_r9:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != utra_BCCH_Container_r9_Unpack(bits, idx))
        {
            printf("CellInfoUTRA_FDD_r9:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string CellInfoUTRA_FDD_r9::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "CellInfoUTRA_FDD_r9:\n";
    out += physCellId_r9_ToString(indent+1);
    out += utra_BCCH_Container_r9_ToString(indent+1);
    return out;
}

std::string CellInfoUTRA_FDD_r9::ToStringNoNewLines() const
{
    std::string out = "CellInfoUTRA_FDD_r9:";
    out += physCellId_r9_ToStringNoNewLines();
    out += utra_BCCH_Container_r9_ToStringNoNewLines();
    return out;
}

PhysCellIdUTRA_FDD* CellInfoUTRA_FDD_r9::physCellId_r9_Set()
{
    physCellId_r9_present = true;
    return &physCellId_r9;
}

int CellInfoUTRA_FDD_r9::physCellId_r9_Set(PhysCellIdUTRA_FDD &value)
{
    physCellId_r9_present = true;
    physCellId_r9 = value;
    return 0;
}

const PhysCellIdUTRA_FDD& CellInfoUTRA_FDD_r9::physCellId_r9_Get() const
{
    return physCellId_r9;
}

std::string CellInfoUTRA_FDD_r9::physCellId_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "physCellId_r9:\n";
    out += physCellId_r9.ToString(indent+1);
    return out;
}

std::string CellInfoUTRA_FDD_r9::physCellId_r9_ToStringNoNewLines() const
{
    std::string out = "physCellId_r9:";
    out += physCellId_r9.ToStringNoNewLines();
    return out;
}

int CellInfoUTRA_FDD_r9::physCellId_r9_Clear()
{
    physCellId_r9_present = false;
    return 0;
}

bool CellInfoUTRA_FDD_r9::physCellId_r9_IsPresent() const
{
    return physCellId_r9_present;
}

int CellInfoUTRA_FDD_r9::utra_BCCH_Container_r9_Pack(std::vector<uint8_t> &bits)
{
    if(!utra_BCCH_Container_r9_present)
    {
        printf("CellInfoUTRA_FDD_r9::utra_BCCH_Container_r9_Pack() presence failure\n");
        return -1;
    }
    uint32_t local_size_length = 0;
    uint32_t local_size = utra_BCCH_Container_r9_internal_value.size();
    if(local_size < 128)
    {
        bits.push_back(0);
        local_size_length = 7;
    }else if(local_size < 16383){
        bits.push_back(1);
        bits.push_back(0);
        local_size_length = 14;
    }else{
        bits.push_back(1);
        bits.push_back(1);
        uint32_t N_16k_blocks = local_size / 16383;
        for(uint32_t i=0; i<6; i++)
            bits.push_back((N_16k_blocks >> (6-i-1)) & 1);
        local_size %= 16383;
        if(local_size < 128)
        {
            bits.push_back(0);
            local_size_length = 7;
        }else{
            bits.push_back(1);
            bits.push_back(0);
            local_size_length = 14;
        }
    }
    for(uint32_t i=0; i<local_size_length; i++)
        bits.push_back((local_size >> (local_size_length-i-1)) & 1);
    for(uint32_t i=0; i<utra_BCCH_Container_r9_internal_value.size(); i++)
        for(uint32_t j=0; j<8; j++)
            bits.push_back((utra_BCCH_Container_r9_internal_value[i] >> (8-j-1)) & 1);
    return 0;
}

int CellInfoUTRA_FDD_r9::utra_BCCH_Container_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return utra_BCCH_Container_r9_Unpack(bits, idx);
}

int CellInfoUTRA_FDD_r9::utra_BCCH_Container_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t local_size_length = 0;
    uint32_t size = 0;
    if(0 == bits[idx++])
    {
        local_size_length = 7;
    }else{
        if(0 == bits[idx++])
        {
            local_size_length = 14;
        }else{
            for(uint32_t i=0; i<6; i++)
                size |= bits[idx++] << (6-i-1);
            size *= 16383;
            if(0 == bits[idx++])
            {
                local_size_length = 7;
            }else{
                idx++;
                local_size_length = 14;
            }
        }
    }
    for(uint32_t i=0; i<local_size_length; i++)
        size |= bits[idx++] << (local_size_length-i-1);
    utra_BCCH_Container_r9_internal_value.clear();
    if((idx +size*8) > bits.size())
    {
        printf("CellInfoUTRA_FDD_r9::utra_BCCH_Container_r9_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
    {
        uint8_t value = 0;
        for(uint32_t j=0; j<8; j++)
            value |= bits[idx+j] << (8-j-1);
        utra_BCCH_Container_r9_internal_value.push_back(value);
        idx += 8;
    }
    utra_BCCH_Container_r9_present = true;
    return 0;
}

std::vector<uint8_t> CellInfoUTRA_FDD_r9::utra_BCCH_Container_r9_Value() const
{
    if(utra_BCCH_Container_r9_present)
        return utra_BCCH_Container_r9_internal_value;
    std::vector<uint8_t> tmp;
    return tmp;
}

int CellInfoUTRA_FDD_r9::utra_BCCH_Container_r9_SetValue(std::vector<uint8_t> value)
{
    utra_BCCH_Container_r9_internal_value = value;
    utra_BCCH_Container_r9_present = true;
    return 0;
}

std::string CellInfoUTRA_FDD_r9::utra_BCCH_Container_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "utra_BCCH_Container_r9 = {";
    for(auto byte : utra_BCCH_Container_r9_internal_value)
        out += std::to_string(byte) + ",";
    out = out.substr(0, out.length()-1) + "}\n";
    return out;
}

std::string CellInfoUTRA_FDD_r9::utra_BCCH_Container_r9_ToStringNoNewLines() const
{
    std::string out = "utra_BCCH_Container_r9={";
    for(auto byte : utra_BCCH_Container_r9_internal_value)
        out += std::to_string(byte) + ",";
    out = out.substr(0, out.length()-1) + "},";
    return out;
}

int CellInfoUTRA_FDD_r9::utra_BCCH_Container_r9_Clear()
{
    utra_BCCH_Container_r9_present = false;
    return 0;
}

bool CellInfoUTRA_FDD_r9::utra_BCCH_Container_r9_IsPresent() const
{
    return utra_BCCH_Container_r9_present;
}

