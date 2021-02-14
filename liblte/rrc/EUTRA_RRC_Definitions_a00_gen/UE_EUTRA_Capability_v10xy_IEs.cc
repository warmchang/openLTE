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

#include "UE_EUTRA_Capability_v10xy_IEs.h"

#include <cmath>

int UE_EUTRA_Capability_v10xy_IEs::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(ue_Category_v10xy_IsPresent());
    bits.push_back(rf_Parameters_v10xy_IsPresent());
    bits.push_back(0);

    // Fields
    if(ue_Category_v10xy_IsPresent())
    {
        if(0 != ue_Category_v10xy_Pack(bits))
        {
            printf("UE_EUTRA_Capability_v10xy_IEs:: field pack failure\n");
            return -1;
        }
    }
    if(rf_Parameters_v10xy_IsPresent())
    {
        if(0 != rf_Parameters_v10xy.Pack(bits))
        {
            printf("UE_EUTRA_Capability_v10xy_IEs:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int UE_EUTRA_Capability_v10xy_IEs::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int UE_EUTRA_Capability_v10xy_IEs::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("UE_EUTRA_Capability_v10xy_IEs::Unpack() index out of bounds for optional indiator ue_Category_v10xy\n");
        return -1;
    }
    ue_Category_v10xy_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("UE_EUTRA_Capability_v10xy_IEs::Unpack() index out of bounds for optional indiator rf_Parameters_v10xy\n");
        return -1;
    }
    rf_Parameters_v10xy_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("UE_EUTRA_Capability_v10xy_IEs::Unpack() index out of bounds for optional indiator nonCriticalExtension\n");
        return -1;
    }
    idx++;

    // Fields
    if(ue_Category_v10xy_present)
    {
        if(0 != ue_Category_v10xy_Unpack(bits, idx))
        {
            printf("UE_EUTRA_Capability_v10xy_IEs:: field unpack failure\n");
            return -1;
        }
    }
    if(rf_Parameters_v10xy_present)
    {
        if(0 != rf_Parameters_v10xy.Unpack(bits, idx))
        {
            printf("UE_EUTRA_Capability_v10xy_IEs:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string UE_EUTRA_Capability_v10xy_IEs::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "UE_EUTRA_Capability_v10xy_IEs:\n";
    if(ue_Category_v10xy_IsPresent())
        out += ue_Category_v10xy_ToString(indent+1);
    if(rf_Parameters_v10xy_IsPresent())
        out += rf_Parameters_v10xy_ToString(indent+1);
    return out;
}

std::string UE_EUTRA_Capability_v10xy_IEs::ToStringNoNewLines() const
{
    std::string out = "UE_EUTRA_Capability_v10xy_IEs:";
    if(ue_Category_v10xy_IsPresent())
        out += ue_Category_v10xy_ToStringNoNewLines();
    if(rf_Parameters_v10xy_IsPresent())
        out += rf_Parameters_v10xy_ToStringNoNewLines();
    return out;
}

int UE_EUTRA_Capability_v10xy_IEs::ue_Category_v10xy_Pack(std::vector<uint8_t> &bits)
{
    int64_t val_to_pack = ue_Category_v10xy_internal_value - (6);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (8 - 6))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int UE_EUTRA_Capability_v10xy_IEs::ue_Category_v10xy_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return ue_Category_v10xy_Unpack(bits, idx);
}

int UE_EUTRA_Capability_v10xy_IEs::ue_Category_v10xy_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (8 - 6))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("UE_EUTRA_Capability_v10xy_IEs::ue_Category_v10xy_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    ue_Category_v10xy_internal_value = packed_val + 6;
    ue_Category_v10xy_present = true;
    return 0;
}

int64_t UE_EUTRA_Capability_v10xy_IEs::ue_Category_v10xy_Value() const
{
    if(ue_Category_v10xy_present)
        return ue_Category_v10xy_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int UE_EUTRA_Capability_v10xy_IEs::ue_Category_v10xy_SetValue(int64_t value)
{
    if(value < 6 || value > 8)
    {
        printf("UE_EUTRA_Capability_v10xy_IEs::ue_Category_v10xy_SetValue() range failure\n");
        return -1;
    }
    ue_Category_v10xy_internal_value = value;
    ue_Category_v10xy_present = true;
    return 0;
}

std::string UE_EUTRA_Capability_v10xy_IEs::ue_Category_v10xy_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ue_Category_v10xy = " + std::to_string(ue_Category_v10xy_internal_value) + "\n";
    return out;
}

std::string UE_EUTRA_Capability_v10xy_IEs::ue_Category_v10xy_ToStringNoNewLines() const
{
    std::string out = "ue_Category_v10xy=" + std::to_string(ue_Category_v10xy_internal_value) + ",";
    return out;
}

int UE_EUTRA_Capability_v10xy_IEs::ue_Category_v10xy_Clear()
{
    ue_Category_v10xy_present = false;
    return 0;
}

bool UE_EUTRA_Capability_v10xy_IEs::ue_Category_v10xy_IsPresent() const
{
    return ue_Category_v10xy_present;
}

RF_Parameters_v10xy* UE_EUTRA_Capability_v10xy_IEs::rf_Parameters_v10xy_Set()
{
    rf_Parameters_v10xy_present = true;
    return &rf_Parameters_v10xy;
}

int UE_EUTRA_Capability_v10xy_IEs::rf_Parameters_v10xy_Set(RF_Parameters_v10xy &value)
{
    rf_Parameters_v10xy_present = true;
    rf_Parameters_v10xy = value;
    return 0;
}

const RF_Parameters_v10xy& UE_EUTRA_Capability_v10xy_IEs::rf_Parameters_v10xy_Get() const
{
    return rf_Parameters_v10xy;
}

std::string UE_EUTRA_Capability_v10xy_IEs::rf_Parameters_v10xy_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "rf_Parameters_v10xy:\n";
    out += rf_Parameters_v10xy.ToString(indent+1);
    return out;
}

std::string UE_EUTRA_Capability_v10xy_IEs::rf_Parameters_v10xy_ToStringNoNewLines() const
{
    std::string out = "rf_Parameters_v10xy:";
    out += rf_Parameters_v10xy.ToStringNoNewLines();
    return out;
}

int UE_EUTRA_Capability_v10xy_IEs::rf_Parameters_v10xy_Clear()
{
    rf_Parameters_v10xy_present = false;
    return 0;
}

bool UE_EUTRA_Capability_v10xy_IEs::rf_Parameters_v10xy_IsPresent() const
{
    return rf_Parameters_v10xy_present;
}

