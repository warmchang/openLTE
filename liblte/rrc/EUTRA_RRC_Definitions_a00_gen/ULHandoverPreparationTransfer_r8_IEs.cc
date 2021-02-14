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

#include "ULHandoverPreparationTransfer_r8_IEs.h"

#include <cmath>

int ULHandoverPreparationTransfer_r8_IEs::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(meid_IsPresent());
    bits.push_back(nonCriticalExtension_IsPresent());

    // Fields
    {
        if(0 != cdma2000_Type.Pack(bits))
        {
            printf("ULHandoverPreparationTransfer_r8_IEs:: field pack failure\n");
            return -1;
        }
    }
    if(meid_IsPresent())
    {
        if(0 != meid_Pack(bits))
        {
            printf("ULHandoverPreparationTransfer_r8_IEs:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != dedicatedInfo.Pack(bits))
        {
            printf("ULHandoverPreparationTransfer_r8_IEs:: field pack failure\n");
            return -1;
        }
    }
    if(nonCriticalExtension_IsPresent())
    {
        if(0 != nonCriticalExtension.Pack(bits))
        {
            printf("ULHandoverPreparationTransfer_r8_IEs:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int ULHandoverPreparationTransfer_r8_IEs::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int ULHandoverPreparationTransfer_r8_IEs::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("ULHandoverPreparationTransfer_r8_IEs::Unpack() index out of bounds for optional indiator meid\n");
        return -1;
    }
    meid_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("ULHandoverPreparationTransfer_r8_IEs::Unpack() index out of bounds for optional indiator nonCriticalExtension\n");
        return -1;
    }
    nonCriticalExtension_present = bits[idx++];

    // Fields
    {
        if(0 != cdma2000_Type.Unpack(bits, idx))
        {
            printf("ULHandoverPreparationTransfer_r8_IEs:: field unpack failure\n");
            return -1;
        }
    }
    if(meid_present)
    {
        if(0 != meid_Unpack(bits, idx))
        {
            printf("ULHandoverPreparationTransfer_r8_IEs:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != dedicatedInfo.Unpack(bits, idx))
        {
            printf("ULHandoverPreparationTransfer_r8_IEs:: field unpack failure\n");
            return -1;
        }
    }
    if(nonCriticalExtension_present)
    {
        if(0 != nonCriticalExtension.Unpack(bits, idx))
        {
            printf("ULHandoverPreparationTransfer_r8_IEs:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string ULHandoverPreparationTransfer_r8_IEs::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ULHandoverPreparationTransfer_r8_IEs:\n";
    out += cdma2000_Type_ToString(indent+1);
    if(meid_IsPresent())
        out += meid_ToString(indent+1);
    out += dedicatedInfo_ToString(indent+1);
    if(nonCriticalExtension_IsPresent())
        out += nonCriticalExtension_ToString(indent+1);
    return out;
}

std::string ULHandoverPreparationTransfer_r8_IEs::ToStringNoNewLines() const
{
    std::string out = "ULHandoverPreparationTransfer_r8_IEs:";
    out += cdma2000_Type_ToStringNoNewLines();
    if(meid_IsPresent())
        out += meid_ToStringNoNewLines();
    out += dedicatedInfo_ToStringNoNewLines();
    if(nonCriticalExtension_IsPresent())
        out += nonCriticalExtension_ToStringNoNewLines();
    return out;
}

CDMA2000_Type* ULHandoverPreparationTransfer_r8_IEs::cdma2000_Type_Set()
{
    cdma2000_Type_present = true;
    return &cdma2000_Type;
}

int ULHandoverPreparationTransfer_r8_IEs::cdma2000_Type_Set(CDMA2000_Type &value)
{
    cdma2000_Type_present = true;
    cdma2000_Type = value;
    return 0;
}

const CDMA2000_Type& ULHandoverPreparationTransfer_r8_IEs::cdma2000_Type_Get() const
{
    return cdma2000_Type;
}

std::string ULHandoverPreparationTransfer_r8_IEs::cdma2000_Type_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cdma2000_Type:\n";
    out += cdma2000_Type.ToString(indent+1);
    return out;
}

std::string ULHandoverPreparationTransfer_r8_IEs::cdma2000_Type_ToStringNoNewLines() const
{
    std::string out = "cdma2000_Type:";
    out += cdma2000_Type.ToStringNoNewLines();
    return out;
}

int ULHandoverPreparationTransfer_r8_IEs::cdma2000_Type_Clear()
{
    cdma2000_Type_present = false;
    return 0;
}

bool ULHandoverPreparationTransfer_r8_IEs::cdma2000_Type_IsPresent() const
{
    return cdma2000_Type_present;
}

int ULHandoverPreparationTransfer_r8_IEs::meid_Pack(std::vector<uint8_t> &bits)
{
    uint32_t size = 56;
    if(size < 56 || size > 56)
    {
        printf("ULHandoverPreparationTransfer_r8_IEs::meid_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((meid_internal_value >> (56-i-1)) & 1);
    return 0;
}

int ULHandoverPreparationTransfer_r8_IEs::meid_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return meid_Unpack(bits, idx);
}

int ULHandoverPreparationTransfer_r8_IEs::meid_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 56;
    if(size < 56 || size > 56)
    {
        printf("ULHandoverPreparationTransfer_r8_IEs::meid_Unpack() size failure\n");
        return -1;
    }
    meid_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("ULHandoverPreparationTransfer_r8_IEs::meid_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        meid_internal_value |= (uint64_t)bits[idx++] << (uint64_t)(56-i-1);
    meid_present = true;
    return 0;
}

uint64_t ULHandoverPreparationTransfer_r8_IEs::meid_Value() const
{
    if(meid_present)
        return meid_internal_value;
    uint64_t tmp = 0;
    return tmp;
}

int ULHandoverPreparationTransfer_r8_IEs::meid_SetValue(uint64_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 56)
    {
        printf("ULHandoverPreparationTransfer_r8_IEs::meid_SetValue() size failure\n");
        return -1;
    }
    meid_internal_value = value;
    meid_present = true;
    return 0;
}

std::string ULHandoverPreparationTransfer_r8_IEs::meid_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "meid = ";
    out += std::to_string(meid_internal_value);
    out += "\n";
    return out;
}

std::string ULHandoverPreparationTransfer_r8_IEs::meid_ToStringNoNewLines() const
{
    std::string out = "meid=";
    out += std::to_string(meid_internal_value);
    out += ",";
    return out;
}

int ULHandoverPreparationTransfer_r8_IEs::meid_Clear()
{
    meid_present = false;
    return 0;
}

bool ULHandoverPreparationTransfer_r8_IEs::meid_IsPresent() const
{
    return meid_present;
}

DedicatedInfoCDMA2000* ULHandoverPreparationTransfer_r8_IEs::dedicatedInfo_Set()
{
    dedicatedInfo_present = true;
    return &dedicatedInfo;
}

int ULHandoverPreparationTransfer_r8_IEs::dedicatedInfo_Set(DedicatedInfoCDMA2000 &value)
{
    dedicatedInfo_present = true;
    dedicatedInfo = value;
    return 0;
}

const DedicatedInfoCDMA2000& ULHandoverPreparationTransfer_r8_IEs::dedicatedInfo_Get() const
{
    return dedicatedInfo;
}

std::string ULHandoverPreparationTransfer_r8_IEs::dedicatedInfo_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "dedicatedInfo:\n";
    out += dedicatedInfo.ToString(indent+1);
    return out;
}

std::string ULHandoverPreparationTransfer_r8_IEs::dedicatedInfo_ToStringNoNewLines() const
{
    std::string out = "dedicatedInfo:";
    out += dedicatedInfo.ToStringNoNewLines();
    return out;
}

int ULHandoverPreparationTransfer_r8_IEs::dedicatedInfo_Clear()
{
    dedicatedInfo_present = false;
    return 0;
}

bool ULHandoverPreparationTransfer_r8_IEs::dedicatedInfo_IsPresent() const
{
    return dedicatedInfo_present;
}

ULHandoverPreparationTransfer_v8a0_IEs* ULHandoverPreparationTransfer_r8_IEs::nonCriticalExtension_Set()
{
    nonCriticalExtension_present = true;
    return &nonCriticalExtension;
}

int ULHandoverPreparationTransfer_r8_IEs::nonCriticalExtension_Set(ULHandoverPreparationTransfer_v8a0_IEs &value)
{
    nonCriticalExtension_present = true;
    nonCriticalExtension = value;
    return 0;
}

const ULHandoverPreparationTransfer_v8a0_IEs& ULHandoverPreparationTransfer_r8_IEs::nonCriticalExtension_Get() const
{
    return nonCriticalExtension;
}

std::string ULHandoverPreparationTransfer_r8_IEs::nonCriticalExtension_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "nonCriticalExtension:\n";
    out += nonCriticalExtension.ToString(indent+1);
    return out;
}

std::string ULHandoverPreparationTransfer_r8_IEs::nonCriticalExtension_ToStringNoNewLines() const
{
    std::string out = "nonCriticalExtension:";
    out += nonCriticalExtension.ToStringNoNewLines();
    return out;
}

int ULHandoverPreparationTransfer_r8_IEs::nonCriticalExtension_Clear()
{
    nonCriticalExtension_present = false;
    return 0;
}

bool ULHandoverPreparationTransfer_r8_IEs::nonCriticalExtension_IsPresent() const
{
    return nonCriticalExtension_present;
}

