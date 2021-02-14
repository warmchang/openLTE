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

#include "BandClassInfoCDMA2000.h"

#include <cmath>

int BandClassInfoCDMA2000::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator
    bits.push_back(0);

    // Optional indicators
    bits.push_back(cellReselectionPriority_IsPresent());

    // Fields
    {
        if(0 != bandClass.Pack(bits))
        {
            printf("BandClassInfoCDMA2000:: field pack failure\n");
            return -1;
        }
    }
    if(cellReselectionPriority_IsPresent())
    {
        if(0 != cellReselectionPriority.Pack(bits))
        {
            printf("BandClassInfoCDMA2000:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != threshX_High_Pack(bits))
        {
            printf("BandClassInfoCDMA2000:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != threshX_Low_Pack(bits))
        {
            printf("BandClassInfoCDMA2000:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int BandClassInfoCDMA2000::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int BandClassInfoCDMA2000::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("BandClassInfoCDMA2000::Unpack() index out of bounds for extension\n");
        return -1;
    }
    idx++;

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("BandClassInfoCDMA2000::Unpack() index out of bounds for optional indiator cellReselectionPriority\n");
        return -1;
    }
    cellReselectionPriority_present = bits[idx++];

    // Fields
    {
        if(0 != bandClass.Unpack(bits, idx))
        {
            printf("BandClassInfoCDMA2000:: field unpack failure\n");
            return -1;
        }
    }
    if(cellReselectionPriority_present)
    {
        if(0 != cellReselectionPriority.Unpack(bits, idx))
        {
            printf("BandClassInfoCDMA2000:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != threshX_High_Unpack(bits, idx))
        {
            printf("BandClassInfoCDMA2000:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != threshX_Low_Unpack(bits, idx))
        {
            printf("BandClassInfoCDMA2000:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string BandClassInfoCDMA2000::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "BandClassInfoCDMA2000:\n";
    out += bandClass_ToString(indent+1);
    if(cellReselectionPriority_IsPresent())
        out += cellReselectionPriority_ToString(indent+1);
    out += threshX_High_ToString(indent+1);
    out += threshX_Low_ToString(indent+1);
    return out;
}

std::string BandClassInfoCDMA2000::ToStringNoNewLines() const
{
    std::string out = "BandClassInfoCDMA2000:";
    out += bandClass_ToStringNoNewLines();
    if(cellReselectionPriority_IsPresent())
        out += cellReselectionPriority_ToStringNoNewLines();
    out += threshX_High_ToStringNoNewLines();
    out += threshX_Low_ToStringNoNewLines();
    return out;
}

BandclassCDMA2000* BandClassInfoCDMA2000::bandClass_Set()
{
    bandClass_present = true;
    return &bandClass;
}

int BandClassInfoCDMA2000::bandClass_Set(BandclassCDMA2000 &value)
{
    bandClass_present = true;
    bandClass = value;
    return 0;
}

const BandclassCDMA2000& BandClassInfoCDMA2000::bandClass_Get() const
{
    return bandClass;
}

std::string BandClassInfoCDMA2000::bandClass_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "bandClass:\n";
    out += bandClass.ToString(indent+1);
    return out;
}

std::string BandClassInfoCDMA2000::bandClass_ToStringNoNewLines() const
{
    std::string out = "bandClass:";
    out += bandClass.ToStringNoNewLines();
    return out;
}

int BandClassInfoCDMA2000::bandClass_Clear()
{
    bandClass_present = false;
    return 0;
}

bool BandClassInfoCDMA2000::bandClass_IsPresent() const
{
    return bandClass_present;
}

CellReselectionPriority* BandClassInfoCDMA2000::cellReselectionPriority_Set()
{
    cellReselectionPriority_present = true;
    return &cellReselectionPriority;
}

int BandClassInfoCDMA2000::cellReselectionPriority_Set(CellReselectionPriority &value)
{
    cellReselectionPriority_present = true;
    cellReselectionPriority = value;
    return 0;
}

const CellReselectionPriority& BandClassInfoCDMA2000::cellReselectionPriority_Get() const
{
    return cellReselectionPriority;
}

std::string BandClassInfoCDMA2000::cellReselectionPriority_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cellReselectionPriority:\n";
    out += cellReselectionPriority.ToString(indent+1);
    return out;
}

std::string BandClassInfoCDMA2000::cellReselectionPriority_ToStringNoNewLines() const
{
    std::string out = "cellReselectionPriority:";
    out += cellReselectionPriority.ToStringNoNewLines();
    return out;
}

int BandClassInfoCDMA2000::cellReselectionPriority_Clear()
{
    cellReselectionPriority_present = false;
    return 0;
}

bool BandClassInfoCDMA2000::cellReselectionPriority_IsPresent() const
{
    return cellReselectionPriority_present;
}

int BandClassInfoCDMA2000::threshX_High_Pack(std::vector<uint8_t> &bits)
{
    if(!threshX_High_present)
    {
        printf("BandClassInfoCDMA2000::threshX_High_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = threshX_High_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (63 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int BandClassInfoCDMA2000::threshX_High_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return threshX_High_Unpack(bits, idx);
}

int BandClassInfoCDMA2000::threshX_High_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (63 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("BandClassInfoCDMA2000::threshX_High_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    threshX_High_internal_value = packed_val + 0;
    threshX_High_present = true;
    return 0;
}

int64_t BandClassInfoCDMA2000::threshX_High_Value() const
{
    if(threshX_High_present)
        return threshX_High_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int BandClassInfoCDMA2000::threshX_High_SetValue(int64_t value)
{
    if(value < 0 || value > 63)
    {
        printf("BandClassInfoCDMA2000::threshX_High_SetValue() range failure\n");
        return -1;
    }
    threshX_High_internal_value = value;
    threshX_High_present = true;
    return 0;
}

std::string BandClassInfoCDMA2000::threshX_High_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "threshX_High = " + std::to_string(threshX_High_internal_value) + "\n";
    return out;
}

std::string BandClassInfoCDMA2000::threshX_High_ToStringNoNewLines() const
{
    std::string out = "threshX_High=" + std::to_string(threshX_High_internal_value) + ",";
    return out;
}

int BandClassInfoCDMA2000::threshX_High_Clear()
{
    threshX_High_present = false;
    return 0;
}

bool BandClassInfoCDMA2000::threshX_High_IsPresent() const
{
    return threshX_High_present;
}

int BandClassInfoCDMA2000::threshX_Low_Pack(std::vector<uint8_t> &bits)
{
    if(!threshX_Low_present)
    {
        printf("BandClassInfoCDMA2000::threshX_Low_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = threshX_Low_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (63 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int BandClassInfoCDMA2000::threshX_Low_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return threshX_Low_Unpack(bits, idx);
}

int BandClassInfoCDMA2000::threshX_Low_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (63 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("BandClassInfoCDMA2000::threshX_Low_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    threshX_Low_internal_value = packed_val + 0;
    threshX_Low_present = true;
    return 0;
}

int64_t BandClassInfoCDMA2000::threshX_Low_Value() const
{
    if(threshX_Low_present)
        return threshX_Low_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int BandClassInfoCDMA2000::threshX_Low_SetValue(int64_t value)
{
    if(value < 0 || value > 63)
    {
        printf("BandClassInfoCDMA2000::threshX_Low_SetValue() range failure\n");
        return -1;
    }
    threshX_Low_internal_value = value;
    threshX_Low_present = true;
    return 0;
}

std::string BandClassInfoCDMA2000::threshX_Low_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "threshX_Low = " + std::to_string(threshX_Low_internal_value) + "\n";
    return out;
}

std::string BandClassInfoCDMA2000::threshX_Low_ToStringNoNewLines() const
{
    std::string out = "threshX_Low=" + std::to_string(threshX_Low_internal_value) + ",";
    return out;
}

int BandClassInfoCDMA2000::threshX_Low_Clear()
{
    threshX_Low_present = false;
    return 0;
}

bool BandClassInfoCDMA2000::threshX_Low_IsPresent() const
{
    return threshX_Low_present;
}

