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

#include "MeasResultGERAN.h"

#include <cmath>

int MeasResultGERAN::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(cgi_Info_value.IsPresent());

    // Fields
    {
        if(0 != carrierFreq.Pack(bits))
        {
            printf("MeasResultGERAN:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != physCellId.Pack(bits))
        {
            printf("MeasResultGERAN:: field pack failure\n");
            return -1;
        }
    }
    if(cgi_Info_value.IsPresent())
    {
        if(0 != cgi_Info_value.Pack(bits))
        {
            printf("MeasResultGERAN:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != measResult_value.Pack(bits))
        {
            printf("MeasResultGERAN:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int MeasResultGERAN::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int MeasResultGERAN::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("MeasResultGERAN::Unpack() index out of bounds for optional indiator cgi_Info\n");
        return -1;
    }
    cgi_Info_value.SetPresence(bits[idx++]);

    // Fields
    {
        if(0 != carrierFreq.Unpack(bits, idx))
        {
            printf("MeasResultGERAN:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != physCellId.Unpack(bits, idx))
        {
            printf("MeasResultGERAN:: field unpack failure\n");
            return -1;
        }
    }
    if(cgi_Info_value.IsPresent())
    {
        if(0 != cgi_Info_value.Unpack(bits, idx))
        {
            printf("MeasResultGERAN:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != measResult_value.Unpack(bits, idx))
        {
            printf("MeasResultGERAN:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string MeasResultGERAN::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "MeasResultGERAN:\n";
    out += carrierFreq_ToString(indent+1);
    out += physCellId_ToString(indent+1);
    if(cgi_Info_value.IsPresent())
        out += cgi_Info_value.ToString(indent+1);
    out += measResult_value.ToString(indent+1);
    return out;
}

std::string MeasResultGERAN::ToStringNoNewLines() const
{
    std::string out = "MeasResultGERAN:";
    out += carrierFreq_ToStringNoNewLines();
    out += physCellId_ToStringNoNewLines();
    if(cgi_Info_value.IsPresent())
        out += cgi_Info_value.ToStringNoNewLines();
    out += measResult_value.ToStringNoNewLines();
    return out;
}

CarrierFreqGERAN* MeasResultGERAN::carrierFreq_Set()
{
    carrierFreq_present = true;
    return &carrierFreq;
}

int MeasResultGERAN::carrierFreq_Set(CarrierFreqGERAN &value)
{
    carrierFreq_present = true;
    carrierFreq = value;
    return 0;
}

const CarrierFreqGERAN& MeasResultGERAN::carrierFreq_Get() const
{
    return carrierFreq;
}

std::string MeasResultGERAN::carrierFreq_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "carrierFreq:\n";
    out += carrierFreq.ToString(indent+1);
    return out;
}

std::string MeasResultGERAN::carrierFreq_ToStringNoNewLines() const
{
    std::string out = "carrierFreq:";
    out += carrierFreq.ToStringNoNewLines();
    return out;
}

int MeasResultGERAN::carrierFreq_Clear()
{
    carrierFreq_present = false;
    return 0;
}

bool MeasResultGERAN::carrierFreq_IsPresent() const
{
    return carrierFreq_present;
}

PhysCellIdGERAN* MeasResultGERAN::physCellId_Set()
{
    physCellId_present = true;
    return &physCellId;
}

int MeasResultGERAN::physCellId_Set(PhysCellIdGERAN &value)
{
    physCellId_present = true;
    physCellId = value;
    return 0;
}

const PhysCellIdGERAN& MeasResultGERAN::physCellId_Get() const
{
    return physCellId;
}

std::string MeasResultGERAN::physCellId_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "physCellId:\n";
    out += physCellId.ToString(indent+1);
    return out;
}

std::string MeasResultGERAN::physCellId_ToStringNoNewLines() const
{
    std::string out = "physCellId:";
    out += physCellId.ToStringNoNewLines();
    return out;
}

int MeasResultGERAN::physCellId_Clear()
{
    physCellId_present = false;
    return 0;
}

bool MeasResultGERAN::physCellId_IsPresent() const
{
    return physCellId_present;
}

int MeasResultGERAN::cgi_Info::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(routingAreaCode_IsPresent());

    // Fields
    {
        if(0 != cellGlobalId.Pack(bits))
        {
            printf("MeasResultGERAN::cgi_Info:: field pack failure\n");
            return -1;
        }
    }
    if(routingAreaCode_IsPresent())
    {
        if(0 != routingAreaCode_Pack(bits))
        {
            printf("MeasResultGERAN::cgi_Info:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int MeasResultGERAN::cgi_Info::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int MeasResultGERAN::cgi_Info::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("cgi_Info::Unpack() index out of bounds for optional indiator routingAreaCode\n");
        return -1;
    }
    routingAreaCode_present = bits[idx++];

    // Fields
    {
        if(0 != cellGlobalId.Unpack(bits, idx))
        {
            printf("MeasResultGERAN::cgi_Info:: field unpack failure\n");
            return -1;
        }
    }
    if(routingAreaCode_present)
    {
        if(0 != routingAreaCode_Unpack(bits, idx))
        {
            printf("MeasResultGERAN::cgi_Info:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string MeasResultGERAN::cgi_Info::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cgi_Info:\n";
    out += cellGlobalId_ToString(indent+1);
    if(routingAreaCode_IsPresent())
        out += routingAreaCode_ToString(indent+1);
    return out;
}

std::string MeasResultGERAN::cgi_Info::ToStringNoNewLines() const
{
    std::string out = "cgi_Info:";
    out += cellGlobalId_ToStringNoNewLines();
    if(routingAreaCode_IsPresent())
        out += routingAreaCode_ToStringNoNewLines();
    return out;
}

int MeasResultGERAN::cgi_Info::Set()
{
    present = true;
    return 0;
}

int MeasResultGERAN::cgi_Info::SetPresence(bool is_present)
{
    present = is_present;
    return 0;
}

int MeasResultGERAN::cgi_Info::Clear()
{
    present = false;
    return 0;
}

bool MeasResultGERAN::cgi_Info::IsPresent() const
{
    return present;
}

CellGlobalIdGERAN* MeasResultGERAN::cgi_Info::cellGlobalId_Set()
{
    cellGlobalId_present = true;
    return &cellGlobalId;
}

int MeasResultGERAN::cgi_Info::cellGlobalId_Set(CellGlobalIdGERAN &value)
{
    cellGlobalId_present = true;
    cellGlobalId = value;
    return 0;
}

const CellGlobalIdGERAN& MeasResultGERAN::cgi_Info::cellGlobalId_Get() const
{
    return cellGlobalId;
}

std::string MeasResultGERAN::cgi_Info::cellGlobalId_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cellGlobalId:\n";
    out += cellGlobalId.ToString(indent+1);
    return out;
}

std::string MeasResultGERAN::cgi_Info::cellGlobalId_ToStringNoNewLines() const
{
    std::string out = "cellGlobalId:";
    out += cellGlobalId.ToStringNoNewLines();
    return out;
}

int MeasResultGERAN::cgi_Info::cellGlobalId_Clear()
{
    cellGlobalId_present = false;
    return 0;
}

bool MeasResultGERAN::cgi_Info::cellGlobalId_IsPresent() const
{
    return cellGlobalId_present;
}

int MeasResultGERAN::cgi_Info::routingAreaCode_Pack(std::vector<uint8_t> &bits)
{
    uint32_t size = 8;
    if(size < 8 || size > 8)
    {
        printf("MeasResultGERAN::cgi_Info::routingAreaCode_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((routingAreaCode_internal_value >> (8-i-1)) & 1);
    return 0;
}

int MeasResultGERAN::cgi_Info::routingAreaCode_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return routingAreaCode_Unpack(bits, idx);
}

int MeasResultGERAN::cgi_Info::routingAreaCode_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 8;
    if(size < 8 || size > 8)
    {
        printf("MeasResultGERAN::cgi_Info::routingAreaCode_Unpack() size failure\n");
        return -1;
    }
    routingAreaCode_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("MeasResultGERAN::cgi_Info::routingAreaCode_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        routingAreaCode_internal_value |= (uint8_t)bits[idx++] << (uint8_t)(8-i-1);
    routingAreaCode_present = true;
    return 0;
}

uint8_t MeasResultGERAN::cgi_Info::routingAreaCode_Value() const
{
    if(routingAreaCode_present)
        return routingAreaCode_internal_value;
    uint8_t tmp = 0;
    return tmp;
}

int MeasResultGERAN::cgi_Info::routingAreaCode_SetValue(uint8_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 8)
    {
        printf("MeasResultGERAN::cgi_Info::routingAreaCode_SetValue() size failure\n");
        return -1;
    }
    routingAreaCode_internal_value = value;
    routingAreaCode_present = true;
    return 0;
}

std::string MeasResultGERAN::cgi_Info::routingAreaCode_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "routingAreaCode = ";
    out += std::to_string(routingAreaCode_internal_value);
    out += "\n";
    return out;
}

std::string MeasResultGERAN::cgi_Info::routingAreaCode_ToStringNoNewLines() const
{
    std::string out = "routingAreaCode=";
    out += std::to_string(routingAreaCode_internal_value);
    out += ",";
    return out;
}

int MeasResultGERAN::cgi_Info::routingAreaCode_Clear()
{
    routingAreaCode_present = false;
    return 0;
}

bool MeasResultGERAN::cgi_Info::routingAreaCode_IsPresent() const
{
    return routingAreaCode_present;
}

int MeasResultGERAN::measResult::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator
    bits.push_back(0);

    // Optional indicators

    // Fields
    {
        if(0 != rssi_Pack(bits))
        {
            printf("MeasResultGERAN::measResult:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int MeasResultGERAN::measResult::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int MeasResultGERAN::measResult::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("measResult::Unpack() index out of bounds for extension\n");
        return -1;
    }
    idx++;

    // Optional indicators

    // Fields
    {
        if(0 != rssi_Unpack(bits, idx))
        {
            printf("MeasResultGERAN::measResult:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string MeasResultGERAN::measResult::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "measResult:\n";
    out += rssi_ToString(indent+1);
    return out;
}

std::string MeasResultGERAN::measResult::ToStringNoNewLines() const
{
    std::string out = "measResult:";
    out += rssi_ToStringNoNewLines();
    return out;
}

int MeasResultGERAN::measResult::rssi_Pack(std::vector<uint8_t> &bits)
{
    if(!rssi_present)
    {
        printf("MeasResultGERAN::measResult::rssi_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = rssi_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (63 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int MeasResultGERAN::measResult::rssi_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return rssi_Unpack(bits, idx);
}

int MeasResultGERAN::measResult::rssi_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (63 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("MeasResultGERAN::measResult::rssi_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    rssi_internal_value = packed_val + 0;
    rssi_present = true;
    return 0;
}

int64_t MeasResultGERAN::measResult::rssi_Value() const
{
    if(rssi_present)
        return rssi_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int MeasResultGERAN::measResult::rssi_SetValue(int64_t value)
{
    if(value < 0 || value > 63)
    {
        printf("MeasResultGERAN::measResult::rssi_SetValue() range failure\n");
        return -1;
    }
    rssi_internal_value = value;
    rssi_present = true;
    return 0;
}

std::string MeasResultGERAN::measResult::rssi_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "rssi = " + std::to_string(rssi_internal_value) + "\n";
    return out;
}

std::string MeasResultGERAN::measResult::rssi_ToStringNoNewLines() const
{
    std::string out = "rssi=" + std::to_string(rssi_internal_value) + ",";
    return out;
}

int MeasResultGERAN::measResult::rssi_Clear()
{
    rssi_present = false;
    return 0;
}

bool MeasResultGERAN::measResult::rssi_IsPresent() const
{
    return rssi_present;
}

