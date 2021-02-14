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

#include "Paging.h"

#include <cmath>

int Paging::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(pagingRecordList_IsPresent());
    bits.push_back(systemInfoModification_IsPresent());
    bits.push_back(etws_Indication_IsPresent());
    bits.push_back(nonCriticalExtension_IsPresent());

    // Fields
    if(pagingRecordList_IsPresent())
    {
        if(0 != pagingRecordList.Pack(bits))
        {
            printf("Paging:: field pack failure\n");
            return -1;
        }
    }
    if(systemInfoModification_IsPresent())
    {
        if(0 != systemInfoModification_Pack(bits))
        {
            printf("Paging:: field pack failure\n");
            return -1;
        }
    }
    if(etws_Indication_IsPresent())
    {
        if(0 != etws_Indication_Pack(bits))
        {
            printf("Paging:: field pack failure\n");
            return -1;
        }
    }
    if(nonCriticalExtension_IsPresent())
    {
        if(0 != nonCriticalExtension.Pack(bits))
        {
            printf("Paging:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int Paging::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int Paging::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("Paging::Unpack() index out of bounds for optional indiator pagingRecordList\n");
        return -1;
    }
    pagingRecordList_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("Paging::Unpack() index out of bounds for optional indiator systemInfoModification\n");
        return -1;
    }
    systemInfoModification_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("Paging::Unpack() index out of bounds for optional indiator etws_Indication\n");
        return -1;
    }
    etws_Indication_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("Paging::Unpack() index out of bounds for optional indiator nonCriticalExtension\n");
        return -1;
    }
    nonCriticalExtension_present = bits[idx++];

    // Fields
    if(pagingRecordList_present)
    {
        if(0 != pagingRecordList.Unpack(bits, idx))
        {
            printf("Paging:: field unpack failure\n");
            return -1;
        }
    }
    if(systemInfoModification_present)
    {
        if(0 != systemInfoModification_Unpack(bits, idx))
        {
            printf("Paging:: field unpack failure\n");
            return -1;
        }
    }
    if(etws_Indication_present)
    {
        if(0 != etws_Indication_Unpack(bits, idx))
        {
            printf("Paging:: field unpack failure\n");
            return -1;
        }
    }
    if(nonCriticalExtension_present)
    {
        if(0 != nonCriticalExtension.Unpack(bits, idx))
        {
            printf("Paging:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string Paging::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "Paging:\n";
    if(pagingRecordList_IsPresent())
        out += pagingRecordList_ToString(indent+1);
    if(systemInfoModification_IsPresent())
        out += systemInfoModification_ToString(indent+1);
    if(etws_Indication_IsPresent())
        out += etws_Indication_ToString(indent+1);
    if(nonCriticalExtension_IsPresent())
        out += nonCriticalExtension_ToString(indent+1);
    return out;
}

std::string Paging::ToStringNoNewLines() const
{
    std::string out = "Paging:";
    if(pagingRecordList_IsPresent())
        out += pagingRecordList_ToStringNoNewLines();
    if(systemInfoModification_IsPresent())
        out += systemInfoModification_ToStringNoNewLines();
    if(etws_Indication_IsPresent())
        out += etws_Indication_ToStringNoNewLines();
    if(nonCriticalExtension_IsPresent())
        out += nonCriticalExtension_ToStringNoNewLines();
    return out;
}

PagingRecordList* Paging::pagingRecordList_Set()
{
    pagingRecordList_present = true;
    return &pagingRecordList;
}

int Paging::pagingRecordList_Set(PagingRecordList &value)
{
    pagingRecordList_present = true;
    pagingRecordList = value;
    return 0;
}

const PagingRecordList& Paging::pagingRecordList_Get() const
{
    return pagingRecordList;
}

std::string Paging::pagingRecordList_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "pagingRecordList:\n";
    out += pagingRecordList.ToString(indent+1);
    return out;
}

std::string Paging::pagingRecordList_ToStringNoNewLines() const
{
    std::string out = "pagingRecordList:";
    out += pagingRecordList.ToStringNoNewLines();
    return out;
}

int Paging::pagingRecordList_Clear()
{
    pagingRecordList_present = false;
    return 0;
}

bool Paging::pagingRecordList_IsPresent() const
{
    return pagingRecordList_present;
}

int Paging::systemInfoModification_Pack(std::vector<uint8_t> &bits)
{
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((systemInfoModification_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int Paging::systemInfoModification_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return systemInfoModification_Unpack(bits, idx);
}

int Paging::systemInfoModification_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("Paging::systemInfoModification_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 0)
    {
        printf("Paging::systemInfoModification_Unpack() max failure\n");
        return -1;
    }
    systemInfoModification_internal_value = (systemInfoModification_Enum)packed_val;
    systemInfoModification_present = true;
    return 0;
}

Paging::systemInfoModification_Enum Paging::systemInfoModification_Value() const
{
    if(systemInfoModification_present)
        return systemInfoModification_internal_value;
    return (Paging::systemInfoModification_Enum)0;
}

int Paging::systemInfoModification_SetValue(systemInfoModification_Enum value)
{
    systemInfoModification_internal_value = value;
    systemInfoModification_present = true;
    return 0;
}

int Paging::systemInfoModification_SetValue(std::string value)
{
    if("true" == value)
    {
        systemInfoModification_internal_value = k_systemInfoModification_true;
        systemInfoModification_present = true;
        return 0;
    }
    return 1;
}

std::string Paging::systemInfoModification_ValueToString(systemInfoModification_Enum value) const
{
    if(k_systemInfoModification_true == value)
        return "true";
    return "";
}

uint64_t Paging::systemInfoModification_NumberOfValues() const
{
    return 1;
}

std::string Paging::systemInfoModification_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "systemInfoModification = " + systemInfoModification_ValueToString(systemInfoModification_internal_value) + "\n";
    return out;
}

std::string Paging::systemInfoModification_ToStringNoNewLines() const
{
    std::string out = "systemInfoModification=" + systemInfoModification_ValueToString(systemInfoModification_internal_value) + ",";
    return out;
}

int Paging::systemInfoModification_Clear()
{
    systemInfoModification_present = false;
    return 0;
}

bool Paging::systemInfoModification_IsPresent() const
{
    return systemInfoModification_present;
}

int Paging::etws_Indication_Pack(std::vector<uint8_t> &bits)
{
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((etws_Indication_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int Paging::etws_Indication_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return etws_Indication_Unpack(bits, idx);
}

int Paging::etws_Indication_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("Paging::etws_Indication_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 0)
    {
        printf("Paging::etws_Indication_Unpack() max failure\n");
        return -1;
    }
    etws_Indication_internal_value = (etws_Indication_Enum)packed_val;
    etws_Indication_present = true;
    return 0;
}

Paging::etws_Indication_Enum Paging::etws_Indication_Value() const
{
    if(etws_Indication_present)
        return etws_Indication_internal_value;
    return (Paging::etws_Indication_Enum)0;
}

int Paging::etws_Indication_SetValue(etws_Indication_Enum value)
{
    etws_Indication_internal_value = value;
    etws_Indication_present = true;
    return 0;
}

int Paging::etws_Indication_SetValue(std::string value)
{
    if("true" == value)
    {
        etws_Indication_internal_value = k_etws_Indication_true;
        etws_Indication_present = true;
        return 0;
    }
    return 1;
}

std::string Paging::etws_Indication_ValueToString(etws_Indication_Enum value) const
{
    if(k_etws_Indication_true == value)
        return "true";
    return "";
}

uint64_t Paging::etws_Indication_NumberOfValues() const
{
    return 1;
}

std::string Paging::etws_Indication_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "etws_Indication = " + etws_Indication_ValueToString(etws_Indication_internal_value) + "\n";
    return out;
}

std::string Paging::etws_Indication_ToStringNoNewLines() const
{
    std::string out = "etws_Indication=" + etws_Indication_ValueToString(etws_Indication_internal_value) + ",";
    return out;
}

int Paging::etws_Indication_Clear()
{
    etws_Indication_present = false;
    return 0;
}

bool Paging::etws_Indication_IsPresent() const
{
    return etws_Indication_present;
}

Paging_v890_IEs* Paging::nonCriticalExtension_Set()
{
    nonCriticalExtension_present = true;
    return &nonCriticalExtension;
}

int Paging::nonCriticalExtension_Set(Paging_v890_IEs &value)
{
    nonCriticalExtension_present = true;
    nonCriticalExtension = value;
    return 0;
}

const Paging_v890_IEs& Paging::nonCriticalExtension_Get() const
{
    return nonCriticalExtension;
}

std::string Paging::nonCriticalExtension_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "nonCriticalExtension:\n";
    out += nonCriticalExtension.ToString(indent+1);
    return out;
}

std::string Paging::nonCriticalExtension_ToStringNoNewLines() const
{
    std::string out = "nonCriticalExtension:";
    out += nonCriticalExtension.ToStringNoNewLines();
    return out;
}

int Paging::nonCriticalExtension_Clear()
{
    nonCriticalExtension_present = false;
    return 0;
}

bool Paging::nonCriticalExtension_IsPresent() const
{
    return nonCriticalExtension_present;
}

