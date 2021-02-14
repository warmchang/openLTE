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

#include "CellGlobalIdCDMA2000.h"

#include <cmath>

int CellGlobalIdCDMA2000::Pack(std::vector<uint8_t> &bits)
{
    if(!present)
    {
        printf("CellGlobalIdCDMA2000::Pack() presence failure\n");
        return -1;
    }
    // Extension indicator

    // Choice
    for(uint32_t i=0; i<1; i++)
        bits.push_back((internal_choice >> (1-i-1)) & 1);

    // Fields
    if(internal_choice == k_cellGlobalId1XRTT)
    {
        if(0 != cellGlobalId1XRTT_Pack(bits))
        {
            printf("CellGlobalIdCDMA2000::cellGlobalId1XRTT pack failure\n");
            return -1;
        }
    }
    if(internal_choice == k_cellGlobalIdHRPD)
    {
        if(0 != cellGlobalIdHRPD_Pack(bits))
        {
            printf("CellGlobalIdCDMA2000::cellGlobalIdHRPD pack failure\n");
            return -1;
        }
    }
    return 0;
}

int CellGlobalIdCDMA2000::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int CellGlobalIdCDMA2000::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 1) > bits.size())
    {
        printf("CellGlobalIdCDMA2000::Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<1; i++)
        packed_val |= bits[idx++] << (1-i-1);

    if((CellGlobalIdCDMA2000::Enum)packed_val > k_cellGlobalIdHRPD)
    {
        printf("CellGlobalIdCDMA2000::Unpack() choice range failure\n");
        return -1;
    }
    internal_choice = (CellGlobalIdCDMA2000::Enum)packed_val;
    present = true;

    // Fields
    if(internal_choice == k_cellGlobalId1XRTT)
    {
        if(0 != cellGlobalId1XRTT_Unpack(bits, idx))
        {
            printf("CellGlobalIdCDMA2000::cellGlobalId1XRTT unpack failure\n");
            return -1;
        }
    }
    if(internal_choice == k_cellGlobalIdHRPD)
    {
        if(0 != cellGlobalIdHRPD_Unpack(bits, idx))
        {
            printf("CellGlobalIdCDMA2000::cellGlobalIdHRPD unpack failure\n");
            return -1;
        }
    }
    return 0;
}

CellGlobalIdCDMA2000::Enum CellGlobalIdCDMA2000::Choice() const
{
    if(present)
        return internal_choice;
    return (CellGlobalIdCDMA2000::Enum)0;
}

int CellGlobalIdCDMA2000::SetChoice(CellGlobalIdCDMA2000::Enum choice)
{
    internal_choice = choice;
    present = true;
    return 0;
}

std::string CellGlobalIdCDMA2000::ChoiceToString(Enum value) const
{
    if(k_cellGlobalId1XRTT == value)
        return "cellGlobalId1XRTT";
    if(k_cellGlobalIdHRPD == value)
        return "cellGlobalIdHRPD";
    return "";
}

uint64_t CellGlobalIdCDMA2000::NumberOfChoices() const
{
    return 2;
}

std::string CellGlobalIdCDMA2000::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "CellGlobalIdCDMA2000 = " + ChoiceToString(internal_choice) + ":\n";
    if(internal_choice == k_cellGlobalId1XRTT)
        out += cellGlobalId1XRTT_ToString(indent+1);
    if(internal_choice == k_cellGlobalIdHRPD)
        out += cellGlobalIdHRPD_ToString(indent+1);
    return out;
}

std::string CellGlobalIdCDMA2000::ToStringNoNewLines() const
{
    std::string out = "CellGlobalIdCDMA2000=" + ChoiceToString(internal_choice) + ",";
    if(internal_choice == k_cellGlobalId1XRTT)
        out += cellGlobalId1XRTT_ToStringNoNewLines();
    if(internal_choice == k_cellGlobalIdHRPD)
        out += cellGlobalIdHRPD_ToStringNoNewLines();
    return out;
}

int CellGlobalIdCDMA2000::Clear()
{
    present = false;
    return 0;
}

bool CellGlobalIdCDMA2000::IsPresent() const
{
    return present;
}

int CellGlobalIdCDMA2000::cellGlobalId1XRTT_Pack(std::vector<uint8_t> &bits)
{
    if(!cellGlobalId1XRTT_present)
    {
        printf("CellGlobalIdCDMA2000::cellGlobalId1XRTT_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 47;
    if(size < 47 || size > 47)
    {
        printf("CellGlobalIdCDMA2000::cellGlobalId1XRTT_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((cellGlobalId1XRTT_internal_value >> (47-i-1)) & 1);
    return 0;
}

int CellGlobalIdCDMA2000::cellGlobalId1XRTT_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return cellGlobalId1XRTT_Unpack(bits, idx);
}

int CellGlobalIdCDMA2000::cellGlobalId1XRTT_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 47;
    if(size < 47 || size > 47)
    {
        printf("CellGlobalIdCDMA2000::cellGlobalId1XRTT_Unpack() size failure\n");
        return -1;
    }
    cellGlobalId1XRTT_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("CellGlobalIdCDMA2000::cellGlobalId1XRTT_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        cellGlobalId1XRTT_internal_value |= (uint64_t)bits[idx++] << (uint64_t)(47-i-1);
    cellGlobalId1XRTT_present = true;
    return 0;
}

uint64_t CellGlobalIdCDMA2000::cellGlobalId1XRTT_Value() const
{
    if(cellGlobalId1XRTT_present)
        return cellGlobalId1XRTT_internal_value;
    uint64_t tmp = 0;
    return tmp;
}

int CellGlobalIdCDMA2000::cellGlobalId1XRTT_SetValue(uint64_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 47)
    {
        printf("CellGlobalIdCDMA2000::cellGlobalId1XRTT_SetValue() size failure\n");
        return -1;
    }
    cellGlobalId1XRTT_internal_value = value;
    cellGlobalId1XRTT_present = true;
    return 0;
}

std::string CellGlobalIdCDMA2000::cellGlobalId1XRTT_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cellGlobalId1XRTT = ";
    out += std::to_string(cellGlobalId1XRTT_internal_value);
    out += "\n";
    return out;
}

std::string CellGlobalIdCDMA2000::cellGlobalId1XRTT_ToStringNoNewLines() const
{
    std::string out = "cellGlobalId1XRTT=";
    out += std::to_string(cellGlobalId1XRTT_internal_value);
    out += ",";
    return out;
}

int CellGlobalIdCDMA2000::cellGlobalId1XRTT_Clear()
{
    cellGlobalId1XRTT_present = false;
    return 0;
}

bool CellGlobalIdCDMA2000::cellGlobalId1XRTT_IsPresent() const
{
    return cellGlobalId1XRTT_present;
}

int CellGlobalIdCDMA2000::cellGlobalIdHRPD_Pack(std::vector<uint8_t> &bits)
{
    if(!cellGlobalIdHRPD_present)
    {
        printf("CellGlobalIdCDMA2000::cellGlobalIdHRPD_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = cellGlobalIdHRPD_internal_value.size();
    if(size < 128 || size > 128)
    {
        printf("CellGlobalIdCDMA2000::cellGlobalIdHRPD_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back(cellGlobalIdHRPD_internal_value[i]);
    return 0;
}

int CellGlobalIdCDMA2000::cellGlobalIdHRPD_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return cellGlobalIdHRPD_Unpack(bits, idx);
}

int CellGlobalIdCDMA2000::cellGlobalIdHRPD_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 128;
    if(size < 128 || size > 128)
    {
        printf("CellGlobalIdCDMA2000::cellGlobalIdHRPD_Unpack() size failure\n");
        return -1;
    }
    cellGlobalIdHRPD_internal_value.clear();
    if((idx + size) > bits.size())
    {
        printf("CellGlobalIdCDMA2000::cellGlobalIdHRPD_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        cellGlobalIdHRPD_internal_value[i] = bits[idx++];
    cellGlobalIdHRPD_present = true;
    return 0;
}

std::vector<uint8_t> CellGlobalIdCDMA2000::cellGlobalIdHRPD_Value() const
{
    if(cellGlobalIdHRPD_present)
        return cellGlobalIdHRPD_internal_value;
    std::vector<uint8_t> tmp;
    return tmp;
}

int CellGlobalIdCDMA2000::cellGlobalIdHRPD_SetValue(std::vector<uint8_t> value)
{
    if(value.size() < 128 || value.size() > 128)
    {
        printf("CellGlobalIdCDMA2000::cellGlobalIdHRPD_SetValue() size failure\n");
        return -1;
    }
    cellGlobalIdHRPD_internal_value = value;
    cellGlobalIdHRPD_present = true;
    return 0;
}

std::string CellGlobalIdCDMA2000::cellGlobalIdHRPD_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cellGlobalIdHRPD = ";
    for(auto bit : cellGlobalIdHRPD_internal_value)
        out += std::to_string(bit);
    out += "\n";
    return out;
}

std::string CellGlobalIdCDMA2000::cellGlobalIdHRPD_ToStringNoNewLines() const
{
    std::string out = "cellGlobalIdHRPD=";
    for(auto bit : cellGlobalIdHRPD_internal_value)
        out += std::to_string(bit);
    out += ",";
    return out;
}

int CellGlobalIdCDMA2000::cellGlobalIdHRPD_Clear()
{
    cellGlobalIdHRPD_present = false;
    return 0;
}

bool CellGlobalIdCDMA2000::cellGlobalIdHRPD_IsPresent() const
{
    return cellGlobalIdHRPD_present;
}

