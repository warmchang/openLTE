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

#include "UL_ReferenceSignalsPUSCH.h"

#include <cmath>

int UL_ReferenceSignalsPUSCH::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != groupHoppingEnabled_Pack(bits))
        {
            printf("UL_ReferenceSignalsPUSCH:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != groupAssignmentPUSCH_Pack(bits))
        {
            printf("UL_ReferenceSignalsPUSCH:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != sequenceHoppingEnabled_Pack(bits))
        {
            printf("UL_ReferenceSignalsPUSCH:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != cyclicShift_Pack(bits))
        {
            printf("UL_ReferenceSignalsPUSCH:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int UL_ReferenceSignalsPUSCH::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int UL_ReferenceSignalsPUSCH::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != groupHoppingEnabled_Unpack(bits, idx))
        {
            printf("UL_ReferenceSignalsPUSCH:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != groupAssignmentPUSCH_Unpack(bits, idx))
        {
            printf("UL_ReferenceSignalsPUSCH:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != sequenceHoppingEnabled_Unpack(bits, idx))
        {
            printf("UL_ReferenceSignalsPUSCH:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != cyclicShift_Unpack(bits, idx))
        {
            printf("UL_ReferenceSignalsPUSCH:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string UL_ReferenceSignalsPUSCH::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "UL_ReferenceSignalsPUSCH:\n";
    out += groupHoppingEnabled_ToString(indent+1);
    out += groupAssignmentPUSCH_ToString(indent+1);
    out += sequenceHoppingEnabled_ToString(indent+1);
    out += cyclicShift_ToString(indent+1);
    return out;
}

std::string UL_ReferenceSignalsPUSCH::ToStringNoNewLines() const
{
    std::string out = "UL_ReferenceSignalsPUSCH:";
    out += groupHoppingEnabled_ToStringNoNewLines();
    out += groupAssignmentPUSCH_ToStringNoNewLines();
    out += sequenceHoppingEnabled_ToStringNoNewLines();
    out += cyclicShift_ToStringNoNewLines();
    return out;
}

int UL_ReferenceSignalsPUSCH::groupHoppingEnabled_Pack(std::vector<uint8_t> &bits)
{
    if(!groupHoppingEnabled_present)
    {
        printf("UL_ReferenceSignalsPUSCH::groupHoppingEnabled_Pack() presence failure\n");
        return -1;
    }
    bits.push_back(groupHoppingEnabled_internal_value);
    return 0;
}

int UL_ReferenceSignalsPUSCH::groupHoppingEnabled_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return groupHoppingEnabled_Unpack(bits, idx);
}

int UL_ReferenceSignalsPUSCH::groupHoppingEnabled_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    if((idx + 1) > bits.size())
    {
        printf("UL_ReferenceSignalsPUSCH::groupHoppingEnabled_Unpack() index out of bounds\n");
        return -1;
    }
    groupHoppingEnabled_internal_value = bits[idx++];
    groupHoppingEnabled_present = true;
    return 0;
}

bool UL_ReferenceSignalsPUSCH::groupHoppingEnabled_Value() const
{
    if(groupHoppingEnabled_present)
        return groupHoppingEnabled_internal_value;
    return false;
}

int UL_ReferenceSignalsPUSCH::groupHoppingEnabled_SetValue(bool value)
{
    groupHoppingEnabled_internal_value = value;
    groupHoppingEnabled_present = true;
    return 0;
}

std::string UL_ReferenceSignalsPUSCH::groupHoppingEnabled_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "groupHoppingEnabled = " + std::to_string(groupHoppingEnabled_internal_value) + "\n";
    return out;
}

std::string UL_ReferenceSignalsPUSCH::groupHoppingEnabled_ToStringNoNewLines() const
{
    std::string out = "groupHoppingEnabled=" + std::to_string(groupHoppingEnabled_internal_value) + ",";
    return out;
}

int UL_ReferenceSignalsPUSCH::groupHoppingEnabled_Clear()
{
    groupHoppingEnabled_present = false;
    return 0;
}

bool UL_ReferenceSignalsPUSCH::groupHoppingEnabled_IsPresent() const
{
    return groupHoppingEnabled_present;
}

int UL_ReferenceSignalsPUSCH::groupAssignmentPUSCH_Pack(std::vector<uint8_t> &bits)
{
    if(!groupAssignmentPUSCH_present)
    {
        printf("UL_ReferenceSignalsPUSCH::groupAssignmentPUSCH_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = groupAssignmentPUSCH_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (29 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int UL_ReferenceSignalsPUSCH::groupAssignmentPUSCH_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return groupAssignmentPUSCH_Unpack(bits, idx);
}

int UL_ReferenceSignalsPUSCH::groupAssignmentPUSCH_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (29 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("UL_ReferenceSignalsPUSCH::groupAssignmentPUSCH_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    groupAssignmentPUSCH_internal_value = packed_val + 0;
    groupAssignmentPUSCH_present = true;
    return 0;
}

int64_t UL_ReferenceSignalsPUSCH::groupAssignmentPUSCH_Value() const
{
    if(groupAssignmentPUSCH_present)
        return groupAssignmentPUSCH_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int UL_ReferenceSignalsPUSCH::groupAssignmentPUSCH_SetValue(int64_t value)
{
    if(value < 0 || value > 29)
    {
        printf("UL_ReferenceSignalsPUSCH::groupAssignmentPUSCH_SetValue() range failure\n");
        return -1;
    }
    groupAssignmentPUSCH_internal_value = value;
    groupAssignmentPUSCH_present = true;
    return 0;
}

std::string UL_ReferenceSignalsPUSCH::groupAssignmentPUSCH_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "groupAssignmentPUSCH = " + std::to_string(groupAssignmentPUSCH_internal_value) + "\n";
    return out;
}

std::string UL_ReferenceSignalsPUSCH::groupAssignmentPUSCH_ToStringNoNewLines() const
{
    std::string out = "groupAssignmentPUSCH=" + std::to_string(groupAssignmentPUSCH_internal_value) + ",";
    return out;
}

int UL_ReferenceSignalsPUSCH::groupAssignmentPUSCH_Clear()
{
    groupAssignmentPUSCH_present = false;
    return 0;
}

bool UL_ReferenceSignalsPUSCH::groupAssignmentPUSCH_IsPresent() const
{
    return groupAssignmentPUSCH_present;
}

int UL_ReferenceSignalsPUSCH::sequenceHoppingEnabled_Pack(std::vector<uint8_t> &bits)
{
    if(!sequenceHoppingEnabled_present)
    {
        printf("UL_ReferenceSignalsPUSCH::sequenceHoppingEnabled_Pack() presence failure\n");
        return -1;
    }
    bits.push_back(sequenceHoppingEnabled_internal_value);
    return 0;
}

int UL_ReferenceSignalsPUSCH::sequenceHoppingEnabled_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return sequenceHoppingEnabled_Unpack(bits, idx);
}

int UL_ReferenceSignalsPUSCH::sequenceHoppingEnabled_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    if((idx + 1) > bits.size())
    {
        printf("UL_ReferenceSignalsPUSCH::sequenceHoppingEnabled_Unpack() index out of bounds\n");
        return -1;
    }
    sequenceHoppingEnabled_internal_value = bits[idx++];
    sequenceHoppingEnabled_present = true;
    return 0;
}

bool UL_ReferenceSignalsPUSCH::sequenceHoppingEnabled_Value() const
{
    if(sequenceHoppingEnabled_present)
        return sequenceHoppingEnabled_internal_value;
    return false;
}

int UL_ReferenceSignalsPUSCH::sequenceHoppingEnabled_SetValue(bool value)
{
    sequenceHoppingEnabled_internal_value = value;
    sequenceHoppingEnabled_present = true;
    return 0;
}

std::string UL_ReferenceSignalsPUSCH::sequenceHoppingEnabled_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "sequenceHoppingEnabled = " + std::to_string(sequenceHoppingEnabled_internal_value) + "\n";
    return out;
}

std::string UL_ReferenceSignalsPUSCH::sequenceHoppingEnabled_ToStringNoNewLines() const
{
    std::string out = "sequenceHoppingEnabled=" + std::to_string(sequenceHoppingEnabled_internal_value) + ",";
    return out;
}

int UL_ReferenceSignalsPUSCH::sequenceHoppingEnabled_Clear()
{
    sequenceHoppingEnabled_present = false;
    return 0;
}

bool UL_ReferenceSignalsPUSCH::sequenceHoppingEnabled_IsPresent() const
{
    return sequenceHoppingEnabled_present;
}

int UL_ReferenceSignalsPUSCH::cyclicShift_Pack(std::vector<uint8_t> &bits)
{
    if(!cyclicShift_present)
    {
        printf("UL_ReferenceSignalsPUSCH::cyclicShift_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = cyclicShift_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (7 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int UL_ReferenceSignalsPUSCH::cyclicShift_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return cyclicShift_Unpack(bits, idx);
}

int UL_ReferenceSignalsPUSCH::cyclicShift_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (7 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("UL_ReferenceSignalsPUSCH::cyclicShift_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    cyclicShift_internal_value = packed_val + 0;
    cyclicShift_present = true;
    return 0;
}

int64_t UL_ReferenceSignalsPUSCH::cyclicShift_Value() const
{
    if(cyclicShift_present)
        return cyclicShift_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int UL_ReferenceSignalsPUSCH::cyclicShift_SetValue(int64_t value)
{
    if(value < 0 || value > 7)
    {
        printf("UL_ReferenceSignalsPUSCH::cyclicShift_SetValue() range failure\n");
        return -1;
    }
    cyclicShift_internal_value = value;
    cyclicShift_present = true;
    return 0;
}

std::string UL_ReferenceSignalsPUSCH::cyclicShift_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cyclicShift = " + std::to_string(cyclicShift_internal_value) + "\n";
    return out;
}

std::string UL_ReferenceSignalsPUSCH::cyclicShift_ToStringNoNewLines() const
{
    std::string out = "cyclicShift=" + std::to_string(cyclicShift_internal_value) + ",";
    return out;
}

int UL_ReferenceSignalsPUSCH::cyclicShift_Clear()
{
    cyclicShift_present = false;
    return 0;
}

bool UL_ReferenceSignalsPUSCH::cyclicShift_IsPresent() const
{
    return cyclicShift_present;
}

