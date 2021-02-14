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

#include "VarMeasReport.h"

#include <cmath>

int VarMeasReport::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(cellsTriggeredList_IsPresent());

    // Fields
    {
        if(0 != measId.Pack(bits))
        {
            printf("VarMeasReport:: field pack failure\n");
            return -1;
        }
    }
    if(cellsTriggeredList_IsPresent())
    {
        if(0 != cellsTriggeredList.Pack(bits))
        {
            printf("VarMeasReport:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != numberOfReportsSent_Pack(bits))
        {
            printf("VarMeasReport:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int VarMeasReport::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int VarMeasReport::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("VarMeasReport::Unpack() index out of bounds for optional indiator cellsTriggeredList\n");
        return -1;
    }
    cellsTriggeredList_present = bits[idx++];

    // Fields
    {
        if(0 != measId.Unpack(bits, idx))
        {
            printf("VarMeasReport:: field unpack failure\n");
            return -1;
        }
    }
    if(cellsTriggeredList_present)
    {
        if(0 != cellsTriggeredList.Unpack(bits, idx))
        {
            printf("VarMeasReport:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != numberOfReportsSent_Unpack(bits, idx))
        {
            printf("VarMeasReport:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string VarMeasReport::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "VarMeasReport:\n";
    out += measId_ToString(indent+1);
    if(cellsTriggeredList_IsPresent())
        out += cellsTriggeredList_ToString(indent+1);
    out += numberOfReportsSent_ToString(indent+1);
    return out;
}

std::string VarMeasReport::ToStringNoNewLines() const
{
    std::string out = "VarMeasReport:";
    out += measId_ToStringNoNewLines();
    if(cellsTriggeredList_IsPresent())
        out += cellsTriggeredList_ToStringNoNewLines();
    out += numberOfReportsSent_ToStringNoNewLines();
    return out;
}

MeasId* VarMeasReport::measId_Set()
{
    measId_present = true;
    return &measId;
}

int VarMeasReport::measId_Set(MeasId &value)
{
    measId_present = true;
    measId = value;
    return 0;
}

const MeasId& VarMeasReport::measId_Get() const
{
    return measId;
}

std::string VarMeasReport::measId_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "measId:\n";
    out += measId.ToString(indent+1);
    return out;
}

std::string VarMeasReport::measId_ToStringNoNewLines() const
{
    std::string out = "measId:";
    out += measId.ToStringNoNewLines();
    return out;
}

int VarMeasReport::measId_Clear()
{
    measId_present = false;
    return 0;
}

bool VarMeasReport::measId_IsPresent() const
{
    return measId_present;
}

CellsTriggeredList* VarMeasReport::cellsTriggeredList_Set()
{
    cellsTriggeredList_present = true;
    return &cellsTriggeredList;
}

int VarMeasReport::cellsTriggeredList_Set(CellsTriggeredList &value)
{
    cellsTriggeredList_present = true;
    cellsTriggeredList = value;
    return 0;
}

const CellsTriggeredList& VarMeasReport::cellsTriggeredList_Get() const
{
    return cellsTriggeredList;
}

std::string VarMeasReport::cellsTriggeredList_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cellsTriggeredList:\n";
    out += cellsTriggeredList.ToString(indent+1);
    return out;
}

std::string VarMeasReport::cellsTriggeredList_ToStringNoNewLines() const
{
    std::string out = "cellsTriggeredList:";
    out += cellsTriggeredList.ToStringNoNewLines();
    return out;
}

int VarMeasReport::cellsTriggeredList_Clear()
{
    cellsTriggeredList_present = false;
    return 0;
}

bool VarMeasReport::cellsTriggeredList_IsPresent() const
{
    return cellsTriggeredList_present;
}

int VarMeasReport::numberOfReportsSent_Pack(std::vector<uint8_t> &bits)
{
    if(!numberOfReportsSent_present)
    {
        printf("VarMeasReport::numberOfReportsSent_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = numberOfReportsSent_internal_value;
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= val_to_pack)
        N_bits++;
    uint32_t N_octets = N_bits / 8;
    if((N_bits % 8) != 0)
        N_octets++;
    N_bits = N_octets * 8;
    uint32_t local_size_length = 0;
    uint32_t local_size = N_octets;
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
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int VarMeasReport::numberOfReportsSent_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return numberOfReportsSent_Unpack(bits, idx);
}

int VarMeasReport::numberOfReportsSent_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t local_size_length = 0;
    uint32_t N_octets = 0;
    if(0 == bits[idx++])
    {
        local_size_length = 7;
    }else{
        if(0 == bits[idx++])
        {
            local_size_length = 14;
        }else{
            for(uint32_t i=0; i<6; i++)
                N_octets |= bits[idx++] << (6-i-1);
            N_octets *= 16383;
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
        N_octets |= bits[idx++] << (local_size_length-i-1);
    uint32_t N_bits = N_octets * 8;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("VarMeasReport::numberOfReportsSent_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    numberOfReportsSent_internal_value = packed_val;
    numberOfReportsSent_present = true;
    return 0;
}

int64_t VarMeasReport::numberOfReportsSent_Value() const
{
    if(numberOfReportsSent_present)
        return numberOfReportsSent_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int VarMeasReport::numberOfReportsSent_SetValue(int64_t value)
{
    numberOfReportsSent_internal_value = value;
    numberOfReportsSent_present = true;
    return 0;
}

std::string VarMeasReport::numberOfReportsSent_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "numberOfReportsSent = " + std::to_string(numberOfReportsSent_internal_value) + "\n";
    return out;
}

std::string VarMeasReport::numberOfReportsSent_ToStringNoNewLines() const
{
    std::string out = "numberOfReportsSent=" + std::to_string(numberOfReportsSent_internal_value) + ",";
    return out;
}

int VarMeasReport::numberOfReportsSent_Clear()
{
    numberOfReportsSent_present = false;
    return 0;
}

bool VarMeasReport::numberOfReportsSent_IsPresent() const
{
    return numberOfReportsSent_present;
}

