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

#include "MeasResultCDMA2000.h"

#include <cmath>

int MeasResultCDMA2000::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(cgi_Info_IsPresent());

    // Fields
    {
        if(0 != physCellId.Pack(bits))
        {
            printf("MeasResultCDMA2000:: field pack failure\n");
            return -1;
        }
    }
    if(cgi_Info_IsPresent())
    {
        if(0 != cgi_Info.Pack(bits))
        {
            printf("MeasResultCDMA2000:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != measResult_value.Pack(bits))
        {
            printf("MeasResultCDMA2000:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int MeasResultCDMA2000::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int MeasResultCDMA2000::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("MeasResultCDMA2000::Unpack() index out of bounds for optional indiator cgi_Info\n");
        return -1;
    }
    cgi_Info_present = bits[idx++];

    // Fields
    {
        if(0 != physCellId.Unpack(bits, idx))
        {
            printf("MeasResultCDMA2000:: field unpack failure\n");
            return -1;
        }
    }
    if(cgi_Info_present)
    {
        if(0 != cgi_Info.Unpack(bits, idx))
        {
            printf("MeasResultCDMA2000:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != measResult_value.Unpack(bits, idx))
        {
            printf("MeasResultCDMA2000:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string MeasResultCDMA2000::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "MeasResultCDMA2000:\n";
    out += physCellId_ToString(indent+1);
    if(cgi_Info_IsPresent())
        out += cgi_Info_ToString(indent+1);
    out += measResult_value.ToString(indent+1);
    return out;
}

std::string MeasResultCDMA2000::ToStringNoNewLines() const
{
    std::string out = "MeasResultCDMA2000:";
    out += physCellId_ToStringNoNewLines();
    if(cgi_Info_IsPresent())
        out += cgi_Info_ToStringNoNewLines();
    out += measResult_value.ToStringNoNewLines();
    return out;
}

PhysCellIdCDMA2000* MeasResultCDMA2000::physCellId_Set()
{
    physCellId_present = true;
    return &physCellId;
}

int MeasResultCDMA2000::physCellId_Set(PhysCellIdCDMA2000 &value)
{
    physCellId_present = true;
    physCellId = value;
    return 0;
}

const PhysCellIdCDMA2000& MeasResultCDMA2000::physCellId_Get() const
{
    return physCellId;
}

std::string MeasResultCDMA2000::physCellId_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "physCellId:\n";
    out += physCellId.ToString(indent+1);
    return out;
}

std::string MeasResultCDMA2000::physCellId_ToStringNoNewLines() const
{
    std::string out = "physCellId:";
    out += physCellId.ToStringNoNewLines();
    return out;
}

int MeasResultCDMA2000::physCellId_Clear()
{
    physCellId_present = false;
    return 0;
}

bool MeasResultCDMA2000::physCellId_IsPresent() const
{
    return physCellId_present;
}

CellGlobalIdCDMA2000* MeasResultCDMA2000::cgi_Info_Set()
{
    cgi_Info_present = true;
    return &cgi_Info;
}

int MeasResultCDMA2000::cgi_Info_Set(CellGlobalIdCDMA2000 &value)
{
    cgi_Info_present = true;
    cgi_Info = value;
    return 0;
}

const CellGlobalIdCDMA2000& MeasResultCDMA2000::cgi_Info_Get() const
{
    return cgi_Info;
}

std::string MeasResultCDMA2000::cgi_Info_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cgi_Info:\n";
    out += cgi_Info.ToString(indent+1);
    return out;
}

std::string MeasResultCDMA2000::cgi_Info_ToStringNoNewLines() const
{
    std::string out = "cgi_Info:";
    out += cgi_Info.ToStringNoNewLines();
    return out;
}

int MeasResultCDMA2000::cgi_Info_Clear()
{
    cgi_Info_present = false;
    return 0;
}

bool MeasResultCDMA2000::cgi_Info_IsPresent() const
{
    return cgi_Info_present;
}

int MeasResultCDMA2000::measResult::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator
    bits.push_back(0);

    // Optional indicators
    bits.push_back(pilotPnPhase_IsPresent());

    // Fields
    if(pilotPnPhase_IsPresent())
    {
        if(0 != pilotPnPhase_Pack(bits))
        {
            printf("MeasResultCDMA2000::measResult:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != pilotStrength_Pack(bits))
        {
            printf("MeasResultCDMA2000::measResult:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int MeasResultCDMA2000::measResult::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int MeasResultCDMA2000::measResult::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("measResult::Unpack() index out of bounds for extension\n");
        return -1;
    }
    idx++;

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("measResult::Unpack() index out of bounds for optional indiator pilotPnPhase\n");
        return -1;
    }
    pilotPnPhase_present = bits[idx++];

    // Fields
    if(pilotPnPhase_present)
    {
        if(0 != pilotPnPhase_Unpack(bits, idx))
        {
            printf("MeasResultCDMA2000::measResult:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != pilotStrength_Unpack(bits, idx))
        {
            printf("MeasResultCDMA2000::measResult:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string MeasResultCDMA2000::measResult::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "measResult:\n";
    if(pilotPnPhase_IsPresent())
        out += pilotPnPhase_ToString(indent+1);
    out += pilotStrength_ToString(indent+1);
    return out;
}

std::string MeasResultCDMA2000::measResult::ToStringNoNewLines() const
{
    std::string out = "measResult:";
    if(pilotPnPhase_IsPresent())
        out += pilotPnPhase_ToStringNoNewLines();
    out += pilotStrength_ToStringNoNewLines();
    return out;
}

int MeasResultCDMA2000::measResult::pilotPnPhase_Pack(std::vector<uint8_t> &bits)
{
    int64_t val_to_pack = pilotPnPhase_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (32767 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int MeasResultCDMA2000::measResult::pilotPnPhase_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return pilotPnPhase_Unpack(bits, idx);
}

int MeasResultCDMA2000::measResult::pilotPnPhase_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (32767 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("MeasResultCDMA2000::measResult::pilotPnPhase_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    pilotPnPhase_internal_value = packed_val + 0;
    pilotPnPhase_present = true;
    return 0;
}

int64_t MeasResultCDMA2000::measResult::pilotPnPhase_Value() const
{
    if(pilotPnPhase_present)
        return pilotPnPhase_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int MeasResultCDMA2000::measResult::pilotPnPhase_SetValue(int64_t value)
{
    if(value < 0 || value > 32767)
    {
        printf("MeasResultCDMA2000::measResult::pilotPnPhase_SetValue() range failure\n");
        return -1;
    }
    pilotPnPhase_internal_value = value;
    pilotPnPhase_present = true;
    return 0;
}

std::string MeasResultCDMA2000::measResult::pilotPnPhase_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "pilotPnPhase = " + std::to_string(pilotPnPhase_internal_value) + "\n";
    return out;
}

std::string MeasResultCDMA2000::measResult::pilotPnPhase_ToStringNoNewLines() const
{
    std::string out = "pilotPnPhase=" + std::to_string(pilotPnPhase_internal_value) + ",";
    return out;
}

int MeasResultCDMA2000::measResult::pilotPnPhase_Clear()
{
    pilotPnPhase_present = false;
    return 0;
}

bool MeasResultCDMA2000::measResult::pilotPnPhase_IsPresent() const
{
    return pilotPnPhase_present;
}

int MeasResultCDMA2000::measResult::pilotStrength_Pack(std::vector<uint8_t> &bits)
{
    if(!pilotStrength_present)
    {
        printf("MeasResultCDMA2000::measResult::pilotStrength_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = pilotStrength_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (63 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int MeasResultCDMA2000::measResult::pilotStrength_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return pilotStrength_Unpack(bits, idx);
}

int MeasResultCDMA2000::measResult::pilotStrength_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (63 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("MeasResultCDMA2000::measResult::pilotStrength_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    pilotStrength_internal_value = packed_val + 0;
    pilotStrength_present = true;
    return 0;
}

int64_t MeasResultCDMA2000::measResult::pilotStrength_Value() const
{
    if(pilotStrength_present)
        return pilotStrength_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int MeasResultCDMA2000::measResult::pilotStrength_SetValue(int64_t value)
{
    if(value < 0 || value > 63)
    {
        printf("MeasResultCDMA2000::measResult::pilotStrength_SetValue() range failure\n");
        return -1;
    }
    pilotStrength_internal_value = value;
    pilotStrength_present = true;
    return 0;
}

std::string MeasResultCDMA2000::measResult::pilotStrength_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "pilotStrength = " + std::to_string(pilotStrength_internal_value) + "\n";
    return out;
}

std::string MeasResultCDMA2000::measResult::pilotStrength_ToStringNoNewLines() const
{
    std::string out = "pilotStrength=" + std::to_string(pilotStrength_internal_value) + ",";
    return out;
}

int MeasResultCDMA2000::measResult::pilotStrength_Clear()
{
    pilotStrength_present = false;
    return 0;
}

bool MeasResultCDMA2000::measResult::pilotStrength_IsPresent() const
{
    return pilotStrength_present;
}

