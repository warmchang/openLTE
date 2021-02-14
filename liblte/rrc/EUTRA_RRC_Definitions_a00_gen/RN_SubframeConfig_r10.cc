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

#include "RN_SubframeConfig_r10.h"

#include <cmath>

int RN_SubframeConfig_r10::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator
    bits.push_back(0);

    // Optional indicators
    bits.push_back(rpdcch_Config_r10_value.IsPresent());

    // Fields
    {
        if(0 != frameStructureType_r10_Pack(bits))
        {
            printf("RN_SubframeConfig_r10:: field pack failure\n");
            return -1;
        }
    }
    if(rpdcch_Config_r10_value.IsPresent())
    {
        if(0 != rpdcch_Config_r10_value.Pack(bits))
        {
            printf("RN_SubframeConfig_r10:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int RN_SubframeConfig_r10::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int RN_SubframeConfig_r10::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("RN_SubframeConfig_r10::Unpack() index out of bounds for extension\n");
        return -1;
    }
    idx++;

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("RN_SubframeConfig_r10::Unpack() index out of bounds for optional indiator rpdcch_Config_r10\n");
        return -1;
    }
    rpdcch_Config_r10_value.SetPresence(bits[idx++]);

    // Fields
    {
        if(0 != frameStructureType_r10_Unpack(bits, idx))
        {
            printf("RN_SubframeConfig_r10:: field unpack failure\n");
            return -1;
        }
    }
    if(rpdcch_Config_r10_value.IsPresent())
    {
        if(0 != rpdcch_Config_r10_value.Unpack(bits, idx))
        {
            printf("RN_SubframeConfig_r10:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string RN_SubframeConfig_r10::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "RN_SubframeConfig_r10:\n";
    out += frameStructureType_r10_ToString(indent+1);
    if(rpdcch_Config_r10_value.IsPresent())
        out += rpdcch_Config_r10_value.ToString(indent+1);
    return out;
}

std::string RN_SubframeConfig_r10::ToStringNoNewLines() const
{
    std::string out = "RN_SubframeConfig_r10:";
    out += frameStructureType_r10_ToStringNoNewLines();
    if(rpdcch_Config_r10_value.IsPresent())
        out += rpdcch_Config_r10_value.ToStringNoNewLines();
    return out;
}

int RN_SubframeConfig_r10::frameStructureType_r10_Pack(std::vector<uint8_t> &bits)
{
    if(!frameStructureType_r10_present)
    {
        printf("RN_SubframeConfig_r10::frameStructureType_r10_Pack() presence failure\n");
        return -1;
    }
    // Extension indicator

    // Choice
    for(uint32_t i=0; i<1; i++)
        bits.push_back((frameStructureType_r10_internal_choice >> (1-i-1)) & 1);

    // Fields
    if(frameStructureType_r10_internal_choice == k_frameStructureType_r10_fdd_r10)
    {
        if(0 != frameStructureType_r10_fdd_r10.Pack(bits))
        {
            printf("RN_SubframeConfig_r10::frameStructureType_r10_fdd_r10 pack failure\n");
            return -1;
        }
    }
    if(frameStructureType_r10_internal_choice == k_frameStructureType_r10_tdd_r10)
    {
        if(0 != frameStructureType_r10_tdd_r10.Pack(bits))
        {
            printf("RN_SubframeConfig_r10::frameStructureType_r10_tdd_r10 pack failure\n");
            return -1;
        }
    }
    return 0;
}

int RN_SubframeConfig_r10::frameStructureType_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return frameStructureType_r10_Unpack(bits, idx);
}

int RN_SubframeConfig_r10::frameStructureType_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 1) > bits.size())
    {
        printf("RN_SubframeConfig_r10::frameStructureType_r10_Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<1; i++)
        packed_val |= bits[idx++] << (1-i-1);

    if((RN_SubframeConfig_r10::frameStructureType_r10_Enum)packed_val > k_frameStructureType_r10_tdd_r10)
    {
        printf("RN_SubframeConfig_r10::frameStructureType_r10_Unpack() choice range failure\n");
        return -1;
    }
    frameStructureType_r10_internal_choice = (RN_SubframeConfig_r10::frameStructureType_r10_Enum)packed_val;
    frameStructureType_r10_present = true;

    // Fields
    if(frameStructureType_r10_internal_choice == k_frameStructureType_r10_fdd_r10)
    {
        if(0 != frameStructureType_r10_fdd_r10.Unpack(bits, idx))
        {
            printf("RN_SubframeConfig_r10::frameStructureType_r10_fdd_r10 unpack failure\n");
            return -1;
        }
    }
    if(frameStructureType_r10_internal_choice == k_frameStructureType_r10_tdd_r10)
    {
        if(0 != frameStructureType_r10_tdd_r10.Unpack(bits, idx))
        {
            printf("RN_SubframeConfig_r10::frameStructureType_r10_tdd_r10 unpack failure\n");
            return -1;
        }
    }
    return 0;
}

RN_SubframeConfig_r10::frameStructureType_r10_Enum RN_SubframeConfig_r10::frameStructureType_r10_Choice() const
{
    if(frameStructureType_r10_present)
        return frameStructureType_r10_internal_choice;
    return (RN_SubframeConfig_r10::frameStructureType_r10_Enum)0;
}

int RN_SubframeConfig_r10::frameStructureType_r10_SetChoice(RN_SubframeConfig_r10::frameStructureType_r10_Enum choice)
{
    frameStructureType_r10_internal_choice = choice;
    frameStructureType_r10_present = true;
    return 0;
}

std::string RN_SubframeConfig_r10::frameStructureType_r10_ChoiceToString(frameStructureType_r10_Enum value) const
{
    if(k_frameStructureType_r10_fdd_r10 == value)
        return "frameStructureType_r10_fdd_r10";
    if(k_frameStructureType_r10_tdd_r10 == value)
        return "frameStructureType_r10_tdd_r10";
    return "";
}

uint64_t RN_SubframeConfig_r10::frameStructureType_r10_NumberOfChoices() const
{
    return 2;
}

std::string RN_SubframeConfig_r10::frameStructureType_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "frameStructureType_r10 = " + frameStructureType_r10_ChoiceToString(frameStructureType_r10_internal_choice) + ":\n";
    if(frameStructureType_r10_internal_choice == k_frameStructureType_r10_fdd_r10)
        out += frameStructureType_r10_fdd_r10.ToString(indent+1);
    if(frameStructureType_r10_internal_choice == k_frameStructureType_r10_tdd_r10)
        out += frameStructureType_r10_tdd_r10.ToString(indent+1);
    return out;
}

std::string RN_SubframeConfig_r10::frameStructureType_r10_ToStringNoNewLines() const
{
    std::string out = "frameStructureType_r10=" + frameStructureType_r10_ChoiceToString(frameStructureType_r10_internal_choice) + ",";
    if(frameStructureType_r10_internal_choice == k_frameStructureType_r10_fdd_r10)
        out += frameStructureType_r10_fdd_r10.ToStringNoNewLines();
    if(frameStructureType_r10_internal_choice == k_frameStructureType_r10_tdd_r10)
        out += frameStructureType_r10_tdd_r10.ToStringNoNewLines();
    return out;
}

int RN_SubframeConfig_r10::frameStructureType_r10_Clear()
{
    frameStructureType_r10_present = false;
    return 0;
}

bool RN_SubframeConfig_r10::frameStructureType_r10_IsPresent() const
{
    return frameStructureType_r10_present;
}

FDD_SubframeConfig_r10* RN_SubframeConfig_r10::frameStructureType_r10_fdd_r10_Set()
{
    frameStructureType_r10_fdd_r10_present = true;
    return &frameStructureType_r10_fdd_r10;
}

int RN_SubframeConfig_r10::frameStructureType_r10_fdd_r10_Set(FDD_SubframeConfig_r10 &value)
{
    frameStructureType_r10_fdd_r10_present = true;
    frameStructureType_r10_fdd_r10 = value;
    return 0;
}

const FDD_SubframeConfig_r10& RN_SubframeConfig_r10::frameStructureType_r10_fdd_r10_Get() const
{
    return frameStructureType_r10_fdd_r10;
}

std::string RN_SubframeConfig_r10::frameStructureType_r10_fdd_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "fdd_r10:\n";
    out += frameStructureType_r10_fdd_r10.ToString(indent+1);
    return out;
}

std::string RN_SubframeConfig_r10::frameStructureType_r10_fdd_r10_ToStringNoNewLines() const
{
    std::string out = "fdd_r10:";
    out += frameStructureType_r10_fdd_r10.ToStringNoNewLines();
    return out;
}

int RN_SubframeConfig_r10::frameStructureType_r10_fdd_r10_Clear()
{
    frameStructureType_r10_fdd_r10_present = false;
    return 0;
}

bool RN_SubframeConfig_r10::frameStructureType_r10_fdd_r10_IsPresent() const
{
    return frameStructureType_r10_fdd_r10_present;
}

TDD_SubframeConfig_r10* RN_SubframeConfig_r10::frameStructureType_r10_tdd_r10_Set()
{
    frameStructureType_r10_tdd_r10_present = true;
    return &frameStructureType_r10_tdd_r10;
}

int RN_SubframeConfig_r10::frameStructureType_r10_tdd_r10_Set(TDD_SubframeConfig_r10 &value)
{
    frameStructureType_r10_tdd_r10_present = true;
    frameStructureType_r10_tdd_r10 = value;
    return 0;
}

const TDD_SubframeConfig_r10& RN_SubframeConfig_r10::frameStructureType_r10_tdd_r10_Get() const
{
    return frameStructureType_r10_tdd_r10;
}

std::string RN_SubframeConfig_r10::frameStructureType_r10_tdd_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "tdd_r10:\n";
    out += frameStructureType_r10_tdd_r10.ToString(indent+1);
    return out;
}

std::string RN_SubframeConfig_r10::frameStructureType_r10_tdd_r10_ToStringNoNewLines() const
{
    std::string out = "tdd_r10:";
    out += frameStructureType_r10_tdd_r10.ToStringNoNewLines();
    return out;
}

int RN_SubframeConfig_r10::frameStructureType_r10_tdd_r10_Clear()
{
    frameStructureType_r10_tdd_r10_present = false;
    return 0;
}

bool RN_SubframeConfig_r10::frameStructureType_r10_tdd_r10_IsPresent() const
{
    return frameStructureType_r10_tdd_r10_present;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator
    bits.push_back(0);

    // Optional indicators

    // Fields
    {
        if(0 != resourceAllocationType_r10_Pack(bits))
        {
            printf("RN_SubframeConfig_r10::rpdcch_Config_r10:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != resourceBlockAssignment_r10_Pack(bits))
        {
            printf("RN_SubframeConfig_r10::rpdcch_Config_r10:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != demodulationRS_r10_Pack(bits))
        {
            printf("RN_SubframeConfig_r10::rpdcch_Config_r10:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != pdsch_Start_r10_Pack(bits))
        {
            printf("RN_SubframeConfig_r10::rpdcch_Config_r10:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != pucch_Config_r10_value.Pack(bits))
        {
            printf("RN_SubframeConfig_r10::rpdcch_Config_r10:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("rpdcch_Config_r10::Unpack() index out of bounds for extension\n");
        return -1;
    }
    idx++;

    // Optional indicators

    // Fields
    {
        if(0 != resourceAllocationType_r10_Unpack(bits, idx))
        {
            printf("RN_SubframeConfig_r10::rpdcch_Config_r10:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != resourceBlockAssignment_r10_Unpack(bits, idx))
        {
            printf("RN_SubframeConfig_r10::rpdcch_Config_r10:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != demodulationRS_r10_Unpack(bits, idx))
        {
            printf("RN_SubframeConfig_r10::rpdcch_Config_r10:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != pdsch_Start_r10_Unpack(bits, idx))
        {
            printf("RN_SubframeConfig_r10::rpdcch_Config_r10:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != pucch_Config_r10_value.Unpack(bits, idx))
        {
            printf("RN_SubframeConfig_r10::rpdcch_Config_r10:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string RN_SubframeConfig_r10::rpdcch_Config_r10::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "rpdcch_Config_r10:\n";
    out += resourceAllocationType_r10_ToString(indent+1);
    out += resourceBlockAssignment_r10_ToString(indent+1);
    out += demodulationRS_r10_ToString(indent+1);
    out += pdsch_Start_r10_ToString(indent+1);
    out += pucch_Config_r10_value.ToString(indent+1);
    return out;
}

std::string RN_SubframeConfig_r10::rpdcch_Config_r10::ToStringNoNewLines() const
{
    std::string out = "rpdcch_Config_r10:";
    out += resourceAllocationType_r10_ToStringNoNewLines();
    out += resourceBlockAssignment_r10_ToStringNoNewLines();
    out += demodulationRS_r10_ToStringNoNewLines();
    out += pdsch_Start_r10_ToStringNoNewLines();
    out += pucch_Config_r10_value.ToStringNoNewLines();
    return out;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::Set()
{
    present = true;
    return 0;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::SetPresence(bool is_present)
{
    present = is_present;
    return 0;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::Clear()
{
    present = false;
    return 0;
}

bool RN_SubframeConfig_r10::rpdcch_Config_r10::IsPresent() const
{
    return present;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceAllocationType_r10_Pack(std::vector<uint8_t> &bits)
{
    if(!resourceAllocationType_r10_present)
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceAllocationType_r10_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 2;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((resourceAllocationType_r10_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceAllocationType_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return resourceAllocationType_r10_Unpack(bits, idx);
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceAllocationType_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 2;
    if((idx + N_bits) > bits.size())
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceAllocationType_r10_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 3)
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceAllocationType_r10_Unpack() max failure\n");
        return -1;
    }
    resourceAllocationType_r10_internal_value = (resourceAllocationType_r10_Enum)packed_val;
    resourceAllocationType_r10_present = true;
    return 0;
}

RN_SubframeConfig_r10::rpdcch_Config_r10::resourceAllocationType_r10_Enum RN_SubframeConfig_r10::rpdcch_Config_r10::resourceAllocationType_r10_Value() const
{
    if(resourceAllocationType_r10_present)
        return resourceAllocationType_r10_internal_value;
    return (RN_SubframeConfig_r10::rpdcch_Config_r10::resourceAllocationType_r10_Enum)0;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceAllocationType_r10_SetValue(resourceAllocationType_r10_Enum value)
{
    resourceAllocationType_r10_internal_value = value;
    resourceAllocationType_r10_present = true;
    return 0;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceAllocationType_r10_SetValue(std::string value)
{
    if("type0" == value)
    {
        resourceAllocationType_r10_internal_value = k_resourceAllocationType_r10_type0;
        resourceAllocationType_r10_present = true;
        return 0;
    }
    if("type1" == value)
    {
        resourceAllocationType_r10_internal_value = k_resourceAllocationType_r10_type1;
        resourceAllocationType_r10_present = true;
        return 0;
    }
    if("type2Localized" == value)
    {
        resourceAllocationType_r10_internal_value = k_resourceAllocationType_r10_type2Localized;
        resourceAllocationType_r10_present = true;
        return 0;
    }
    if("type2Distributed" == value)
    {
        resourceAllocationType_r10_internal_value = k_resourceAllocationType_r10_type2Distributed;
        resourceAllocationType_r10_present = true;
        return 0;
    }
    return 1;
}

std::string RN_SubframeConfig_r10::rpdcch_Config_r10::resourceAllocationType_r10_ValueToString(resourceAllocationType_r10_Enum value) const
{
    if(k_resourceAllocationType_r10_type0 == value)
        return "type0";
    if(k_resourceAllocationType_r10_type1 == value)
        return "type1";
    if(k_resourceAllocationType_r10_type2Localized == value)
        return "type2Localized";
    if(k_resourceAllocationType_r10_type2Distributed == value)
        return "type2Distributed";
    return "";
}

uint64_t RN_SubframeConfig_r10::rpdcch_Config_r10::resourceAllocationType_r10_NumberOfValues() const
{
    return 4;
}

std::string RN_SubframeConfig_r10::rpdcch_Config_r10::resourceAllocationType_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "resourceAllocationType_r10 = " + resourceAllocationType_r10_ValueToString(resourceAllocationType_r10_internal_value) + "\n";
    return out;
}

std::string RN_SubframeConfig_r10::rpdcch_Config_r10::resourceAllocationType_r10_ToStringNoNewLines() const
{
    std::string out = "resourceAllocationType_r10=" + resourceAllocationType_r10_ValueToString(resourceAllocationType_r10_internal_value) + ",";
    return out;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceAllocationType_r10_Clear()
{
    resourceAllocationType_r10_present = false;
    return 0;
}

bool RN_SubframeConfig_r10::rpdcch_Config_r10::resourceAllocationType_r10_IsPresent() const
{
    return resourceAllocationType_r10_present;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_Pack(std::vector<uint8_t> &bits)
{
    if(!resourceBlockAssignment_r10_present)
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_Pack() presence failure\n");
        return -1;
    }
    // Extension indicator

    // Choice
    for(uint32_t i=0; i<1; i++)
        bits.push_back((resourceBlockAssignment_r10_internal_choice >> (1-i-1)) & 1);

    // Fields
    if(resourceBlockAssignment_r10_internal_choice == k_resourceBlockAssignment_r10_type01_r10)
    {
        if(0 != resourceBlockAssignment_r10_type01_r10_Pack(bits))
        {
            printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10 pack failure\n");
            return -1;
        }
    }
    if(resourceBlockAssignment_r10_internal_choice == k_resourceBlockAssignment_r10_type2_r10)
    {
        if(0 != resourceBlockAssignment_r10_type2_r10_Pack(bits))
        {
            printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10 pack failure\n");
            return -1;
        }
    }
    return 0;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return resourceBlockAssignment_r10_Unpack(bits, idx);
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 1) > bits.size())
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<1; i++)
        packed_val |= bits[idx++] << (1-i-1);

    if((RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_Enum)packed_val > k_resourceBlockAssignment_r10_type2_r10)
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_Unpack() choice range failure\n");
        return -1;
    }
    resourceBlockAssignment_r10_internal_choice = (RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_Enum)packed_val;
    resourceBlockAssignment_r10_present = true;

    // Fields
    if(resourceBlockAssignment_r10_internal_choice == k_resourceBlockAssignment_r10_type01_r10)
    {
        if(0 != resourceBlockAssignment_r10_type01_r10_Unpack(bits, idx))
        {
            printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10 unpack failure\n");
            return -1;
        }
    }
    if(resourceBlockAssignment_r10_internal_choice == k_resourceBlockAssignment_r10_type2_r10)
    {
        if(0 != resourceBlockAssignment_r10_type2_r10_Unpack(bits, idx))
        {
            printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10 unpack failure\n");
            return -1;
        }
    }
    return 0;
}

RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_Enum RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_Choice() const
{
    if(resourceBlockAssignment_r10_present)
        return resourceBlockAssignment_r10_internal_choice;
    return (RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_Enum)0;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_SetChoice(RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_Enum choice)
{
    resourceBlockAssignment_r10_internal_choice = choice;
    resourceBlockAssignment_r10_present = true;
    return 0;
}

std::string RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_ChoiceToString(resourceBlockAssignment_r10_Enum value) const
{
    if(k_resourceBlockAssignment_r10_type01_r10 == value)
        return "resourceBlockAssignment_r10_type01_r10";
    if(k_resourceBlockAssignment_r10_type2_r10 == value)
        return "resourceBlockAssignment_r10_type2_r10";
    return "";
}

uint64_t RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_NumberOfChoices() const
{
    return 2;
}

std::string RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "resourceBlockAssignment_r10 = " + resourceBlockAssignment_r10_ChoiceToString(resourceBlockAssignment_r10_internal_choice) + ":\n";
    if(resourceBlockAssignment_r10_internal_choice == k_resourceBlockAssignment_r10_type01_r10)
        out += resourceBlockAssignment_r10_type01_r10_ToString(indent+1);
    if(resourceBlockAssignment_r10_internal_choice == k_resourceBlockAssignment_r10_type2_r10)
        out += resourceBlockAssignment_r10_type2_r10_ToString(indent+1);
    return out;
}

std::string RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_ToStringNoNewLines() const
{
    std::string out = "resourceBlockAssignment_r10=" + resourceBlockAssignment_r10_ChoiceToString(resourceBlockAssignment_r10_internal_choice) + ",";
    if(resourceBlockAssignment_r10_internal_choice == k_resourceBlockAssignment_r10_type01_r10)
        out += resourceBlockAssignment_r10_type01_r10_ToStringNoNewLines();
    if(resourceBlockAssignment_r10_internal_choice == k_resourceBlockAssignment_r10_type2_r10)
        out += resourceBlockAssignment_r10_type2_r10_ToStringNoNewLines();
    return out;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_Clear()
{
    resourceBlockAssignment_r10_present = false;
    return 0;
}

bool RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_IsPresent() const
{
    return resourceBlockAssignment_r10_present;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_Pack(std::vector<uint8_t> &bits)
{
    if(!resourceBlockAssignment_r10_type01_r10_present)
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_Pack() presence failure\n");
        return -1;
    }
    // Extension indicator

    // Choice
    for(uint32_t i=0; i<3; i++)
        bits.push_back((resourceBlockAssignment_r10_type01_r10_internal_choice >> (3-i-1)) & 1);

    // Fields
    if(resourceBlockAssignment_r10_type01_r10_internal_choice == k_resourceBlockAssignment_r10_type01_r10_nrb6_r10)
    {
        if(0 != resourceBlockAssignment_r10_type01_r10_nrb6_r10_Pack(bits))
        {
            printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb6_r10 pack failure\n");
            return -1;
        }
    }
    if(resourceBlockAssignment_r10_type01_r10_internal_choice == k_resourceBlockAssignment_r10_type01_r10_nrb15_r10)
    {
        if(0 != resourceBlockAssignment_r10_type01_r10_nrb15_r10_Pack(bits))
        {
            printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb15_r10 pack failure\n");
            return -1;
        }
    }
    if(resourceBlockAssignment_r10_type01_r10_internal_choice == k_resourceBlockAssignment_r10_type01_r10_nrb25_r10)
    {
        if(0 != resourceBlockAssignment_r10_type01_r10_nrb25_r10_Pack(bits))
        {
            printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb25_r10 pack failure\n");
            return -1;
        }
    }
    if(resourceBlockAssignment_r10_type01_r10_internal_choice == k_resourceBlockAssignment_r10_type01_r10_nrb50_r10)
    {
        if(0 != resourceBlockAssignment_r10_type01_r10_nrb50_r10_Pack(bits))
        {
            printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb50_r10 pack failure\n");
            return -1;
        }
    }
    if(resourceBlockAssignment_r10_type01_r10_internal_choice == k_resourceBlockAssignment_r10_type01_r10_nrb75_r10)
    {
        if(0 != resourceBlockAssignment_r10_type01_r10_nrb75_r10_Pack(bits))
        {
            printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb75_r10 pack failure\n");
            return -1;
        }
    }
    if(resourceBlockAssignment_r10_type01_r10_internal_choice == k_resourceBlockAssignment_r10_type01_r10_nrb100_r10)
    {
        if(0 != resourceBlockAssignment_r10_type01_r10_nrb100_r10_Pack(bits))
        {
            printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb100_r10 pack failure\n");
            return -1;
        }
    }
    return 0;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return resourceBlockAssignment_r10_type01_r10_Unpack(bits, idx);
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 3) > bits.size())
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<3; i++)
        packed_val |= bits[idx++] << (3-i-1);

    if((RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_Enum)packed_val > k_resourceBlockAssignment_r10_type01_r10_nrb100_r10)
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_Unpack() choice range failure\n");
        return -1;
    }
    resourceBlockAssignment_r10_type01_r10_internal_choice = (RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_Enum)packed_val;
    resourceBlockAssignment_r10_type01_r10_present = true;

    // Fields
    if(resourceBlockAssignment_r10_type01_r10_internal_choice == k_resourceBlockAssignment_r10_type01_r10_nrb6_r10)
    {
        if(0 != resourceBlockAssignment_r10_type01_r10_nrb6_r10_Unpack(bits, idx))
        {
            printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb6_r10 unpack failure\n");
            return -1;
        }
    }
    if(resourceBlockAssignment_r10_type01_r10_internal_choice == k_resourceBlockAssignment_r10_type01_r10_nrb15_r10)
    {
        if(0 != resourceBlockAssignment_r10_type01_r10_nrb15_r10_Unpack(bits, idx))
        {
            printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb15_r10 unpack failure\n");
            return -1;
        }
    }
    if(resourceBlockAssignment_r10_type01_r10_internal_choice == k_resourceBlockAssignment_r10_type01_r10_nrb25_r10)
    {
        if(0 != resourceBlockAssignment_r10_type01_r10_nrb25_r10_Unpack(bits, idx))
        {
            printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb25_r10 unpack failure\n");
            return -1;
        }
    }
    if(resourceBlockAssignment_r10_type01_r10_internal_choice == k_resourceBlockAssignment_r10_type01_r10_nrb50_r10)
    {
        if(0 != resourceBlockAssignment_r10_type01_r10_nrb50_r10_Unpack(bits, idx))
        {
            printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb50_r10 unpack failure\n");
            return -1;
        }
    }
    if(resourceBlockAssignment_r10_type01_r10_internal_choice == k_resourceBlockAssignment_r10_type01_r10_nrb75_r10)
    {
        if(0 != resourceBlockAssignment_r10_type01_r10_nrb75_r10_Unpack(bits, idx))
        {
            printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb75_r10 unpack failure\n");
            return -1;
        }
    }
    if(resourceBlockAssignment_r10_type01_r10_internal_choice == k_resourceBlockAssignment_r10_type01_r10_nrb100_r10)
    {
        if(0 != resourceBlockAssignment_r10_type01_r10_nrb100_r10_Unpack(bits, idx))
        {
            printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb100_r10 unpack failure\n");
            return -1;
        }
    }
    return 0;
}

RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_Enum RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_Choice() const
{
    if(resourceBlockAssignment_r10_type01_r10_present)
        return resourceBlockAssignment_r10_type01_r10_internal_choice;
    return (RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_Enum)0;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_SetChoice(RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_Enum choice)
{
    resourceBlockAssignment_r10_type01_r10_internal_choice = choice;
    resourceBlockAssignment_r10_type01_r10_present = true;
    return 0;
}

std::string RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_ChoiceToString(resourceBlockAssignment_r10_type01_r10_Enum value) const
{
    if(k_resourceBlockAssignment_r10_type01_r10_nrb6_r10 == value)
        return "resourceBlockAssignment_r10_type01_r10_nrb6_r10";
    if(k_resourceBlockAssignment_r10_type01_r10_nrb15_r10 == value)
        return "resourceBlockAssignment_r10_type01_r10_nrb15_r10";
    if(k_resourceBlockAssignment_r10_type01_r10_nrb25_r10 == value)
        return "resourceBlockAssignment_r10_type01_r10_nrb25_r10";
    if(k_resourceBlockAssignment_r10_type01_r10_nrb50_r10 == value)
        return "resourceBlockAssignment_r10_type01_r10_nrb50_r10";
    if(k_resourceBlockAssignment_r10_type01_r10_nrb75_r10 == value)
        return "resourceBlockAssignment_r10_type01_r10_nrb75_r10";
    if(k_resourceBlockAssignment_r10_type01_r10_nrb100_r10 == value)
        return "resourceBlockAssignment_r10_type01_r10_nrb100_r10";
    return "";
}

uint64_t RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_NumberOfChoices() const
{
    return 6;
}

std::string RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "type01_r10 = " + resourceBlockAssignment_r10_type01_r10_ChoiceToString(resourceBlockAssignment_r10_type01_r10_internal_choice) + ":\n";
    if(resourceBlockAssignment_r10_type01_r10_internal_choice == k_resourceBlockAssignment_r10_type01_r10_nrb6_r10)
        out += resourceBlockAssignment_r10_type01_r10_nrb6_r10_ToString(indent+1);
    if(resourceBlockAssignment_r10_type01_r10_internal_choice == k_resourceBlockAssignment_r10_type01_r10_nrb15_r10)
        out += resourceBlockAssignment_r10_type01_r10_nrb15_r10_ToString(indent+1);
    if(resourceBlockAssignment_r10_type01_r10_internal_choice == k_resourceBlockAssignment_r10_type01_r10_nrb25_r10)
        out += resourceBlockAssignment_r10_type01_r10_nrb25_r10_ToString(indent+1);
    if(resourceBlockAssignment_r10_type01_r10_internal_choice == k_resourceBlockAssignment_r10_type01_r10_nrb50_r10)
        out += resourceBlockAssignment_r10_type01_r10_nrb50_r10_ToString(indent+1);
    if(resourceBlockAssignment_r10_type01_r10_internal_choice == k_resourceBlockAssignment_r10_type01_r10_nrb75_r10)
        out += resourceBlockAssignment_r10_type01_r10_nrb75_r10_ToString(indent+1);
    if(resourceBlockAssignment_r10_type01_r10_internal_choice == k_resourceBlockAssignment_r10_type01_r10_nrb100_r10)
        out += resourceBlockAssignment_r10_type01_r10_nrb100_r10_ToString(indent+1);
    return out;
}

std::string RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_ToStringNoNewLines() const
{
    std::string out = "type01_r10=" + resourceBlockAssignment_r10_type01_r10_ChoiceToString(resourceBlockAssignment_r10_type01_r10_internal_choice) + ",";
    if(resourceBlockAssignment_r10_type01_r10_internal_choice == k_resourceBlockAssignment_r10_type01_r10_nrb6_r10)
        out += resourceBlockAssignment_r10_type01_r10_nrb6_r10_ToStringNoNewLines();
    if(resourceBlockAssignment_r10_type01_r10_internal_choice == k_resourceBlockAssignment_r10_type01_r10_nrb15_r10)
        out += resourceBlockAssignment_r10_type01_r10_nrb15_r10_ToStringNoNewLines();
    if(resourceBlockAssignment_r10_type01_r10_internal_choice == k_resourceBlockAssignment_r10_type01_r10_nrb25_r10)
        out += resourceBlockAssignment_r10_type01_r10_nrb25_r10_ToStringNoNewLines();
    if(resourceBlockAssignment_r10_type01_r10_internal_choice == k_resourceBlockAssignment_r10_type01_r10_nrb50_r10)
        out += resourceBlockAssignment_r10_type01_r10_nrb50_r10_ToStringNoNewLines();
    if(resourceBlockAssignment_r10_type01_r10_internal_choice == k_resourceBlockAssignment_r10_type01_r10_nrb75_r10)
        out += resourceBlockAssignment_r10_type01_r10_nrb75_r10_ToStringNoNewLines();
    if(resourceBlockAssignment_r10_type01_r10_internal_choice == k_resourceBlockAssignment_r10_type01_r10_nrb100_r10)
        out += resourceBlockAssignment_r10_type01_r10_nrb100_r10_ToStringNoNewLines();
    return out;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_Clear()
{
    resourceBlockAssignment_r10_type01_r10_present = false;
    return 0;
}

bool RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_IsPresent() const
{
    return resourceBlockAssignment_r10_type01_r10_present;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb6_r10_Pack(std::vector<uint8_t> &bits)
{
    if(!resourceBlockAssignment_r10_type01_r10_nrb6_r10_present)
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb6_r10_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 6;
    if(size < 6 || size > 6)
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb6_r10_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((resourceBlockAssignment_r10_type01_r10_nrb6_r10_internal_value >> (6-i-1)) & 1);
    return 0;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb6_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return resourceBlockAssignment_r10_type01_r10_nrb6_r10_Unpack(bits, idx);
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb6_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 6;
    if(size < 6 || size > 6)
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb6_r10_Unpack() size failure\n");
        return -1;
    }
    resourceBlockAssignment_r10_type01_r10_nrb6_r10_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb6_r10_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        resourceBlockAssignment_r10_type01_r10_nrb6_r10_internal_value |= (uint8_t)bits[idx++] << (uint8_t)(6-i-1);
    resourceBlockAssignment_r10_type01_r10_nrb6_r10_present = true;
    return 0;
}

uint8_t RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb6_r10_Value() const
{
    if(resourceBlockAssignment_r10_type01_r10_nrb6_r10_present)
        return resourceBlockAssignment_r10_type01_r10_nrb6_r10_internal_value;
    uint8_t tmp = 0;
    return tmp;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb6_r10_SetValue(uint8_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 6)
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb6_r10_SetValue() size failure\n");
        return -1;
    }
    resourceBlockAssignment_r10_type01_r10_nrb6_r10_internal_value = value;
    resourceBlockAssignment_r10_type01_r10_nrb6_r10_present = true;
    return 0;
}

std::string RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb6_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "nrb6_r10 = ";
    out += std::to_string(resourceBlockAssignment_r10_type01_r10_nrb6_r10_internal_value);
    out += "\n";
    return out;
}

std::string RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb6_r10_ToStringNoNewLines() const
{
    std::string out = "nrb6_r10=";
    out += std::to_string(resourceBlockAssignment_r10_type01_r10_nrb6_r10_internal_value);
    out += ",";
    return out;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb6_r10_Clear()
{
    resourceBlockAssignment_r10_type01_r10_nrb6_r10_present = false;
    return 0;
}

bool RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb6_r10_IsPresent() const
{
    return resourceBlockAssignment_r10_type01_r10_nrb6_r10_present;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb15_r10_Pack(std::vector<uint8_t> &bits)
{
    if(!resourceBlockAssignment_r10_type01_r10_nrb15_r10_present)
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb15_r10_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 8;
    if(size < 8 || size > 8)
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb15_r10_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((resourceBlockAssignment_r10_type01_r10_nrb15_r10_internal_value >> (8-i-1)) & 1);
    return 0;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb15_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return resourceBlockAssignment_r10_type01_r10_nrb15_r10_Unpack(bits, idx);
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb15_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 8;
    if(size < 8 || size > 8)
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb15_r10_Unpack() size failure\n");
        return -1;
    }
    resourceBlockAssignment_r10_type01_r10_nrb15_r10_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb15_r10_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        resourceBlockAssignment_r10_type01_r10_nrb15_r10_internal_value |= (uint8_t)bits[idx++] << (uint8_t)(8-i-1);
    resourceBlockAssignment_r10_type01_r10_nrb15_r10_present = true;
    return 0;
}

uint8_t RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb15_r10_Value() const
{
    if(resourceBlockAssignment_r10_type01_r10_nrb15_r10_present)
        return resourceBlockAssignment_r10_type01_r10_nrb15_r10_internal_value;
    uint8_t tmp = 0;
    return tmp;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb15_r10_SetValue(uint8_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 8)
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb15_r10_SetValue() size failure\n");
        return -1;
    }
    resourceBlockAssignment_r10_type01_r10_nrb15_r10_internal_value = value;
    resourceBlockAssignment_r10_type01_r10_nrb15_r10_present = true;
    return 0;
}

std::string RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb15_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "nrb15_r10 = ";
    out += std::to_string(resourceBlockAssignment_r10_type01_r10_nrb15_r10_internal_value);
    out += "\n";
    return out;
}

std::string RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb15_r10_ToStringNoNewLines() const
{
    std::string out = "nrb15_r10=";
    out += std::to_string(resourceBlockAssignment_r10_type01_r10_nrb15_r10_internal_value);
    out += ",";
    return out;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb15_r10_Clear()
{
    resourceBlockAssignment_r10_type01_r10_nrb15_r10_present = false;
    return 0;
}

bool RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb15_r10_IsPresent() const
{
    return resourceBlockAssignment_r10_type01_r10_nrb15_r10_present;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb25_r10_Pack(std::vector<uint8_t> &bits)
{
    if(!resourceBlockAssignment_r10_type01_r10_nrb25_r10_present)
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb25_r10_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 13;
    if(size < 13 || size > 13)
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb25_r10_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((resourceBlockAssignment_r10_type01_r10_nrb25_r10_internal_value >> (13-i-1)) & 1);
    return 0;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb25_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return resourceBlockAssignment_r10_type01_r10_nrb25_r10_Unpack(bits, idx);
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb25_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 13;
    if(size < 13 || size > 13)
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb25_r10_Unpack() size failure\n");
        return -1;
    }
    resourceBlockAssignment_r10_type01_r10_nrb25_r10_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb25_r10_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        resourceBlockAssignment_r10_type01_r10_nrb25_r10_internal_value |= (uint16_t)bits[idx++] << (uint16_t)(13-i-1);
    resourceBlockAssignment_r10_type01_r10_nrb25_r10_present = true;
    return 0;
}

uint16_t RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb25_r10_Value() const
{
    if(resourceBlockAssignment_r10_type01_r10_nrb25_r10_present)
        return resourceBlockAssignment_r10_type01_r10_nrb25_r10_internal_value;
    uint16_t tmp = 0;
    return tmp;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb25_r10_SetValue(uint16_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 13)
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb25_r10_SetValue() size failure\n");
        return -1;
    }
    resourceBlockAssignment_r10_type01_r10_nrb25_r10_internal_value = value;
    resourceBlockAssignment_r10_type01_r10_nrb25_r10_present = true;
    return 0;
}

std::string RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb25_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "nrb25_r10 = ";
    out += std::to_string(resourceBlockAssignment_r10_type01_r10_nrb25_r10_internal_value);
    out += "\n";
    return out;
}

std::string RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb25_r10_ToStringNoNewLines() const
{
    std::string out = "nrb25_r10=";
    out += std::to_string(resourceBlockAssignment_r10_type01_r10_nrb25_r10_internal_value);
    out += ",";
    return out;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb25_r10_Clear()
{
    resourceBlockAssignment_r10_type01_r10_nrb25_r10_present = false;
    return 0;
}

bool RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb25_r10_IsPresent() const
{
    return resourceBlockAssignment_r10_type01_r10_nrb25_r10_present;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb50_r10_Pack(std::vector<uint8_t> &bits)
{
    if(!resourceBlockAssignment_r10_type01_r10_nrb50_r10_present)
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb50_r10_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 17;
    if(size < 17 || size > 17)
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb50_r10_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((resourceBlockAssignment_r10_type01_r10_nrb50_r10_internal_value >> (17-i-1)) & 1);
    return 0;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb50_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return resourceBlockAssignment_r10_type01_r10_nrb50_r10_Unpack(bits, idx);
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb50_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 17;
    if(size < 17 || size > 17)
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb50_r10_Unpack() size failure\n");
        return -1;
    }
    resourceBlockAssignment_r10_type01_r10_nrb50_r10_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb50_r10_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        resourceBlockAssignment_r10_type01_r10_nrb50_r10_internal_value |= (uint32_t)bits[idx++] << (uint32_t)(17-i-1);
    resourceBlockAssignment_r10_type01_r10_nrb50_r10_present = true;
    return 0;
}

uint32_t RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb50_r10_Value() const
{
    if(resourceBlockAssignment_r10_type01_r10_nrb50_r10_present)
        return resourceBlockAssignment_r10_type01_r10_nrb50_r10_internal_value;
    uint32_t tmp = 0;
    return tmp;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb50_r10_SetValue(uint32_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 17)
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb50_r10_SetValue() size failure\n");
        return -1;
    }
    resourceBlockAssignment_r10_type01_r10_nrb50_r10_internal_value = value;
    resourceBlockAssignment_r10_type01_r10_nrb50_r10_present = true;
    return 0;
}

std::string RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb50_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "nrb50_r10 = ";
    out += std::to_string(resourceBlockAssignment_r10_type01_r10_nrb50_r10_internal_value);
    out += "\n";
    return out;
}

std::string RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb50_r10_ToStringNoNewLines() const
{
    std::string out = "nrb50_r10=";
    out += std::to_string(resourceBlockAssignment_r10_type01_r10_nrb50_r10_internal_value);
    out += ",";
    return out;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb50_r10_Clear()
{
    resourceBlockAssignment_r10_type01_r10_nrb50_r10_present = false;
    return 0;
}

bool RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb50_r10_IsPresent() const
{
    return resourceBlockAssignment_r10_type01_r10_nrb50_r10_present;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb75_r10_Pack(std::vector<uint8_t> &bits)
{
    if(!resourceBlockAssignment_r10_type01_r10_nrb75_r10_present)
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb75_r10_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 19;
    if(size < 19 || size > 19)
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb75_r10_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((resourceBlockAssignment_r10_type01_r10_nrb75_r10_internal_value >> (19-i-1)) & 1);
    return 0;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb75_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return resourceBlockAssignment_r10_type01_r10_nrb75_r10_Unpack(bits, idx);
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb75_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 19;
    if(size < 19 || size > 19)
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb75_r10_Unpack() size failure\n");
        return -1;
    }
    resourceBlockAssignment_r10_type01_r10_nrb75_r10_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb75_r10_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        resourceBlockAssignment_r10_type01_r10_nrb75_r10_internal_value |= (uint32_t)bits[idx++] << (uint32_t)(19-i-1);
    resourceBlockAssignment_r10_type01_r10_nrb75_r10_present = true;
    return 0;
}

uint32_t RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb75_r10_Value() const
{
    if(resourceBlockAssignment_r10_type01_r10_nrb75_r10_present)
        return resourceBlockAssignment_r10_type01_r10_nrb75_r10_internal_value;
    uint32_t tmp = 0;
    return tmp;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb75_r10_SetValue(uint32_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 19)
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb75_r10_SetValue() size failure\n");
        return -1;
    }
    resourceBlockAssignment_r10_type01_r10_nrb75_r10_internal_value = value;
    resourceBlockAssignment_r10_type01_r10_nrb75_r10_present = true;
    return 0;
}

std::string RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb75_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "nrb75_r10 = ";
    out += std::to_string(resourceBlockAssignment_r10_type01_r10_nrb75_r10_internal_value);
    out += "\n";
    return out;
}

std::string RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb75_r10_ToStringNoNewLines() const
{
    std::string out = "nrb75_r10=";
    out += std::to_string(resourceBlockAssignment_r10_type01_r10_nrb75_r10_internal_value);
    out += ",";
    return out;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb75_r10_Clear()
{
    resourceBlockAssignment_r10_type01_r10_nrb75_r10_present = false;
    return 0;
}

bool RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb75_r10_IsPresent() const
{
    return resourceBlockAssignment_r10_type01_r10_nrb75_r10_present;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb100_r10_Pack(std::vector<uint8_t> &bits)
{
    if(!resourceBlockAssignment_r10_type01_r10_nrb100_r10_present)
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb100_r10_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 25;
    if(size < 25 || size > 25)
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb100_r10_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((resourceBlockAssignment_r10_type01_r10_nrb100_r10_internal_value >> (25-i-1)) & 1);
    return 0;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb100_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return resourceBlockAssignment_r10_type01_r10_nrb100_r10_Unpack(bits, idx);
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb100_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 25;
    if(size < 25 || size > 25)
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb100_r10_Unpack() size failure\n");
        return -1;
    }
    resourceBlockAssignment_r10_type01_r10_nrb100_r10_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb100_r10_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        resourceBlockAssignment_r10_type01_r10_nrb100_r10_internal_value |= (uint32_t)bits[idx++] << (uint32_t)(25-i-1);
    resourceBlockAssignment_r10_type01_r10_nrb100_r10_present = true;
    return 0;
}

uint32_t RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb100_r10_Value() const
{
    if(resourceBlockAssignment_r10_type01_r10_nrb100_r10_present)
        return resourceBlockAssignment_r10_type01_r10_nrb100_r10_internal_value;
    uint32_t tmp = 0;
    return tmp;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb100_r10_SetValue(uint32_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 25)
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb100_r10_SetValue() size failure\n");
        return -1;
    }
    resourceBlockAssignment_r10_type01_r10_nrb100_r10_internal_value = value;
    resourceBlockAssignment_r10_type01_r10_nrb100_r10_present = true;
    return 0;
}

std::string RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb100_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "nrb100_r10 = ";
    out += std::to_string(resourceBlockAssignment_r10_type01_r10_nrb100_r10_internal_value);
    out += "\n";
    return out;
}

std::string RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb100_r10_ToStringNoNewLines() const
{
    std::string out = "nrb100_r10=";
    out += std::to_string(resourceBlockAssignment_r10_type01_r10_nrb100_r10_internal_value);
    out += ",";
    return out;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb100_r10_Clear()
{
    resourceBlockAssignment_r10_type01_r10_nrb100_r10_present = false;
    return 0;
}

bool RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type01_r10_nrb100_r10_IsPresent() const
{
    return resourceBlockAssignment_r10_type01_r10_nrb100_r10_present;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_Pack(std::vector<uint8_t> &bits)
{
    if(!resourceBlockAssignment_r10_type2_r10_present)
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_Pack() presence failure\n");
        return -1;
    }
    // Extension indicator

    // Choice
    for(uint32_t i=0; i<3; i++)
        bits.push_back((resourceBlockAssignment_r10_type2_r10_internal_choice >> (3-i-1)) & 1);

    // Fields
    if(resourceBlockAssignment_r10_type2_r10_internal_choice == k_resourceBlockAssignment_r10_type2_r10_nrb6_r10)
    {
        if(0 != resourceBlockAssignment_r10_type2_r10_nrb6_r10_Pack(bits))
        {
            printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb6_r10 pack failure\n");
            return -1;
        }
    }
    if(resourceBlockAssignment_r10_type2_r10_internal_choice == k_resourceBlockAssignment_r10_type2_r10_nrb15_r10)
    {
        if(0 != resourceBlockAssignment_r10_type2_r10_nrb15_r10_Pack(bits))
        {
            printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb15_r10 pack failure\n");
            return -1;
        }
    }
    if(resourceBlockAssignment_r10_type2_r10_internal_choice == k_resourceBlockAssignment_r10_type2_r10_nrb25_r10)
    {
        if(0 != resourceBlockAssignment_r10_type2_r10_nrb25_r10_Pack(bits))
        {
            printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb25_r10 pack failure\n");
            return -1;
        }
    }
    if(resourceBlockAssignment_r10_type2_r10_internal_choice == k_resourceBlockAssignment_r10_type2_r10_nrb50_r10)
    {
        if(0 != resourceBlockAssignment_r10_type2_r10_nrb50_r10_Pack(bits))
        {
            printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb50_r10 pack failure\n");
            return -1;
        }
    }
    if(resourceBlockAssignment_r10_type2_r10_internal_choice == k_resourceBlockAssignment_r10_type2_r10_nrb75_r10)
    {
        if(0 != resourceBlockAssignment_r10_type2_r10_nrb75_r10_Pack(bits))
        {
            printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb75_r10 pack failure\n");
            return -1;
        }
    }
    if(resourceBlockAssignment_r10_type2_r10_internal_choice == k_resourceBlockAssignment_r10_type2_r10_nrb100_r10)
    {
        if(0 != resourceBlockAssignment_r10_type2_r10_nrb100_r10_Pack(bits))
        {
            printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb100_r10 pack failure\n");
            return -1;
        }
    }
    return 0;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return resourceBlockAssignment_r10_type2_r10_Unpack(bits, idx);
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 3) > bits.size())
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<3; i++)
        packed_val |= bits[idx++] << (3-i-1);

    if((RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_Enum)packed_val > k_resourceBlockAssignment_r10_type2_r10_nrb100_r10)
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_Unpack() choice range failure\n");
        return -1;
    }
    resourceBlockAssignment_r10_type2_r10_internal_choice = (RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_Enum)packed_val;
    resourceBlockAssignment_r10_type2_r10_present = true;

    // Fields
    if(resourceBlockAssignment_r10_type2_r10_internal_choice == k_resourceBlockAssignment_r10_type2_r10_nrb6_r10)
    {
        if(0 != resourceBlockAssignment_r10_type2_r10_nrb6_r10_Unpack(bits, idx))
        {
            printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb6_r10 unpack failure\n");
            return -1;
        }
    }
    if(resourceBlockAssignment_r10_type2_r10_internal_choice == k_resourceBlockAssignment_r10_type2_r10_nrb15_r10)
    {
        if(0 != resourceBlockAssignment_r10_type2_r10_nrb15_r10_Unpack(bits, idx))
        {
            printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb15_r10 unpack failure\n");
            return -1;
        }
    }
    if(resourceBlockAssignment_r10_type2_r10_internal_choice == k_resourceBlockAssignment_r10_type2_r10_nrb25_r10)
    {
        if(0 != resourceBlockAssignment_r10_type2_r10_nrb25_r10_Unpack(bits, idx))
        {
            printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb25_r10 unpack failure\n");
            return -1;
        }
    }
    if(resourceBlockAssignment_r10_type2_r10_internal_choice == k_resourceBlockAssignment_r10_type2_r10_nrb50_r10)
    {
        if(0 != resourceBlockAssignment_r10_type2_r10_nrb50_r10_Unpack(bits, idx))
        {
            printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb50_r10 unpack failure\n");
            return -1;
        }
    }
    if(resourceBlockAssignment_r10_type2_r10_internal_choice == k_resourceBlockAssignment_r10_type2_r10_nrb75_r10)
    {
        if(0 != resourceBlockAssignment_r10_type2_r10_nrb75_r10_Unpack(bits, idx))
        {
            printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb75_r10 unpack failure\n");
            return -1;
        }
    }
    if(resourceBlockAssignment_r10_type2_r10_internal_choice == k_resourceBlockAssignment_r10_type2_r10_nrb100_r10)
    {
        if(0 != resourceBlockAssignment_r10_type2_r10_nrb100_r10_Unpack(bits, idx))
        {
            printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb100_r10 unpack failure\n");
            return -1;
        }
    }
    return 0;
}

RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_Enum RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_Choice() const
{
    if(resourceBlockAssignment_r10_type2_r10_present)
        return resourceBlockAssignment_r10_type2_r10_internal_choice;
    return (RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_Enum)0;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_SetChoice(RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_Enum choice)
{
    resourceBlockAssignment_r10_type2_r10_internal_choice = choice;
    resourceBlockAssignment_r10_type2_r10_present = true;
    return 0;
}

std::string RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_ChoiceToString(resourceBlockAssignment_r10_type2_r10_Enum value) const
{
    if(k_resourceBlockAssignment_r10_type2_r10_nrb6_r10 == value)
        return "resourceBlockAssignment_r10_type2_r10_nrb6_r10";
    if(k_resourceBlockAssignment_r10_type2_r10_nrb15_r10 == value)
        return "resourceBlockAssignment_r10_type2_r10_nrb15_r10";
    if(k_resourceBlockAssignment_r10_type2_r10_nrb25_r10 == value)
        return "resourceBlockAssignment_r10_type2_r10_nrb25_r10";
    if(k_resourceBlockAssignment_r10_type2_r10_nrb50_r10 == value)
        return "resourceBlockAssignment_r10_type2_r10_nrb50_r10";
    if(k_resourceBlockAssignment_r10_type2_r10_nrb75_r10 == value)
        return "resourceBlockAssignment_r10_type2_r10_nrb75_r10";
    if(k_resourceBlockAssignment_r10_type2_r10_nrb100_r10 == value)
        return "resourceBlockAssignment_r10_type2_r10_nrb100_r10";
    return "";
}

uint64_t RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_NumberOfChoices() const
{
    return 6;
}

std::string RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "type2_r10 = " + resourceBlockAssignment_r10_type2_r10_ChoiceToString(resourceBlockAssignment_r10_type2_r10_internal_choice) + ":\n";
    if(resourceBlockAssignment_r10_type2_r10_internal_choice == k_resourceBlockAssignment_r10_type2_r10_nrb6_r10)
        out += resourceBlockAssignment_r10_type2_r10_nrb6_r10_ToString(indent+1);
    if(resourceBlockAssignment_r10_type2_r10_internal_choice == k_resourceBlockAssignment_r10_type2_r10_nrb15_r10)
        out += resourceBlockAssignment_r10_type2_r10_nrb15_r10_ToString(indent+1);
    if(resourceBlockAssignment_r10_type2_r10_internal_choice == k_resourceBlockAssignment_r10_type2_r10_nrb25_r10)
        out += resourceBlockAssignment_r10_type2_r10_nrb25_r10_ToString(indent+1);
    if(resourceBlockAssignment_r10_type2_r10_internal_choice == k_resourceBlockAssignment_r10_type2_r10_nrb50_r10)
        out += resourceBlockAssignment_r10_type2_r10_nrb50_r10_ToString(indent+1);
    if(resourceBlockAssignment_r10_type2_r10_internal_choice == k_resourceBlockAssignment_r10_type2_r10_nrb75_r10)
        out += resourceBlockAssignment_r10_type2_r10_nrb75_r10_ToString(indent+1);
    if(resourceBlockAssignment_r10_type2_r10_internal_choice == k_resourceBlockAssignment_r10_type2_r10_nrb100_r10)
        out += resourceBlockAssignment_r10_type2_r10_nrb100_r10_ToString(indent+1);
    return out;
}

std::string RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_ToStringNoNewLines() const
{
    std::string out = "type2_r10=" + resourceBlockAssignment_r10_type2_r10_ChoiceToString(resourceBlockAssignment_r10_type2_r10_internal_choice) + ",";
    if(resourceBlockAssignment_r10_type2_r10_internal_choice == k_resourceBlockAssignment_r10_type2_r10_nrb6_r10)
        out += resourceBlockAssignment_r10_type2_r10_nrb6_r10_ToStringNoNewLines();
    if(resourceBlockAssignment_r10_type2_r10_internal_choice == k_resourceBlockAssignment_r10_type2_r10_nrb15_r10)
        out += resourceBlockAssignment_r10_type2_r10_nrb15_r10_ToStringNoNewLines();
    if(resourceBlockAssignment_r10_type2_r10_internal_choice == k_resourceBlockAssignment_r10_type2_r10_nrb25_r10)
        out += resourceBlockAssignment_r10_type2_r10_nrb25_r10_ToStringNoNewLines();
    if(resourceBlockAssignment_r10_type2_r10_internal_choice == k_resourceBlockAssignment_r10_type2_r10_nrb50_r10)
        out += resourceBlockAssignment_r10_type2_r10_nrb50_r10_ToStringNoNewLines();
    if(resourceBlockAssignment_r10_type2_r10_internal_choice == k_resourceBlockAssignment_r10_type2_r10_nrb75_r10)
        out += resourceBlockAssignment_r10_type2_r10_nrb75_r10_ToStringNoNewLines();
    if(resourceBlockAssignment_r10_type2_r10_internal_choice == k_resourceBlockAssignment_r10_type2_r10_nrb100_r10)
        out += resourceBlockAssignment_r10_type2_r10_nrb100_r10_ToStringNoNewLines();
    return out;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_Clear()
{
    resourceBlockAssignment_r10_type2_r10_present = false;
    return 0;
}

bool RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_IsPresent() const
{
    return resourceBlockAssignment_r10_type2_r10_present;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb6_r10_Pack(std::vector<uint8_t> &bits)
{
    if(!resourceBlockAssignment_r10_type2_r10_nrb6_r10_present)
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb6_r10_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 5;
    if(size < 5 || size > 5)
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb6_r10_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((resourceBlockAssignment_r10_type2_r10_nrb6_r10_internal_value >> (5-i-1)) & 1);
    return 0;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb6_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return resourceBlockAssignment_r10_type2_r10_nrb6_r10_Unpack(bits, idx);
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb6_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 5;
    if(size < 5 || size > 5)
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb6_r10_Unpack() size failure\n");
        return -1;
    }
    resourceBlockAssignment_r10_type2_r10_nrb6_r10_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb6_r10_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        resourceBlockAssignment_r10_type2_r10_nrb6_r10_internal_value |= (uint8_t)bits[idx++] << (uint8_t)(5-i-1);
    resourceBlockAssignment_r10_type2_r10_nrb6_r10_present = true;
    return 0;
}

uint8_t RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb6_r10_Value() const
{
    if(resourceBlockAssignment_r10_type2_r10_nrb6_r10_present)
        return resourceBlockAssignment_r10_type2_r10_nrb6_r10_internal_value;
    uint8_t tmp = 0;
    return tmp;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb6_r10_SetValue(uint8_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 5)
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb6_r10_SetValue() size failure\n");
        return -1;
    }
    resourceBlockAssignment_r10_type2_r10_nrb6_r10_internal_value = value;
    resourceBlockAssignment_r10_type2_r10_nrb6_r10_present = true;
    return 0;
}

std::string RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb6_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "nrb6_r10 = ";
    out += std::to_string(resourceBlockAssignment_r10_type2_r10_nrb6_r10_internal_value);
    out += "\n";
    return out;
}

std::string RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb6_r10_ToStringNoNewLines() const
{
    std::string out = "nrb6_r10=";
    out += std::to_string(resourceBlockAssignment_r10_type2_r10_nrb6_r10_internal_value);
    out += ",";
    return out;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb6_r10_Clear()
{
    resourceBlockAssignment_r10_type2_r10_nrb6_r10_present = false;
    return 0;
}

bool RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb6_r10_IsPresent() const
{
    return resourceBlockAssignment_r10_type2_r10_nrb6_r10_present;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb15_r10_Pack(std::vector<uint8_t> &bits)
{
    if(!resourceBlockAssignment_r10_type2_r10_nrb15_r10_present)
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb15_r10_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 7;
    if(size < 7 || size > 7)
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb15_r10_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((resourceBlockAssignment_r10_type2_r10_nrb15_r10_internal_value >> (7-i-1)) & 1);
    return 0;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb15_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return resourceBlockAssignment_r10_type2_r10_nrb15_r10_Unpack(bits, idx);
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb15_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 7;
    if(size < 7 || size > 7)
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb15_r10_Unpack() size failure\n");
        return -1;
    }
    resourceBlockAssignment_r10_type2_r10_nrb15_r10_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb15_r10_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        resourceBlockAssignment_r10_type2_r10_nrb15_r10_internal_value |= (uint8_t)bits[idx++] << (uint8_t)(7-i-1);
    resourceBlockAssignment_r10_type2_r10_nrb15_r10_present = true;
    return 0;
}

uint8_t RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb15_r10_Value() const
{
    if(resourceBlockAssignment_r10_type2_r10_nrb15_r10_present)
        return resourceBlockAssignment_r10_type2_r10_nrb15_r10_internal_value;
    uint8_t tmp = 0;
    return tmp;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb15_r10_SetValue(uint8_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 7)
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb15_r10_SetValue() size failure\n");
        return -1;
    }
    resourceBlockAssignment_r10_type2_r10_nrb15_r10_internal_value = value;
    resourceBlockAssignment_r10_type2_r10_nrb15_r10_present = true;
    return 0;
}

std::string RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb15_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "nrb15_r10 = ";
    out += std::to_string(resourceBlockAssignment_r10_type2_r10_nrb15_r10_internal_value);
    out += "\n";
    return out;
}

std::string RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb15_r10_ToStringNoNewLines() const
{
    std::string out = "nrb15_r10=";
    out += std::to_string(resourceBlockAssignment_r10_type2_r10_nrb15_r10_internal_value);
    out += ",";
    return out;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb15_r10_Clear()
{
    resourceBlockAssignment_r10_type2_r10_nrb15_r10_present = false;
    return 0;
}

bool RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb15_r10_IsPresent() const
{
    return resourceBlockAssignment_r10_type2_r10_nrb15_r10_present;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb25_r10_Pack(std::vector<uint8_t> &bits)
{
    if(!resourceBlockAssignment_r10_type2_r10_nrb25_r10_present)
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb25_r10_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 9;
    if(size < 9 || size > 9)
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb25_r10_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((resourceBlockAssignment_r10_type2_r10_nrb25_r10_internal_value >> (9-i-1)) & 1);
    return 0;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb25_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return resourceBlockAssignment_r10_type2_r10_nrb25_r10_Unpack(bits, idx);
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb25_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 9;
    if(size < 9 || size > 9)
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb25_r10_Unpack() size failure\n");
        return -1;
    }
    resourceBlockAssignment_r10_type2_r10_nrb25_r10_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb25_r10_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        resourceBlockAssignment_r10_type2_r10_nrb25_r10_internal_value |= (uint16_t)bits[idx++] << (uint16_t)(9-i-1);
    resourceBlockAssignment_r10_type2_r10_nrb25_r10_present = true;
    return 0;
}

uint16_t RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb25_r10_Value() const
{
    if(resourceBlockAssignment_r10_type2_r10_nrb25_r10_present)
        return resourceBlockAssignment_r10_type2_r10_nrb25_r10_internal_value;
    uint16_t tmp = 0;
    return tmp;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb25_r10_SetValue(uint16_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 9)
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb25_r10_SetValue() size failure\n");
        return -1;
    }
    resourceBlockAssignment_r10_type2_r10_nrb25_r10_internal_value = value;
    resourceBlockAssignment_r10_type2_r10_nrb25_r10_present = true;
    return 0;
}

std::string RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb25_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "nrb25_r10 = ";
    out += std::to_string(resourceBlockAssignment_r10_type2_r10_nrb25_r10_internal_value);
    out += "\n";
    return out;
}

std::string RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb25_r10_ToStringNoNewLines() const
{
    std::string out = "nrb25_r10=";
    out += std::to_string(resourceBlockAssignment_r10_type2_r10_nrb25_r10_internal_value);
    out += ",";
    return out;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb25_r10_Clear()
{
    resourceBlockAssignment_r10_type2_r10_nrb25_r10_present = false;
    return 0;
}

bool RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb25_r10_IsPresent() const
{
    return resourceBlockAssignment_r10_type2_r10_nrb25_r10_present;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb50_r10_Pack(std::vector<uint8_t> &bits)
{
    if(!resourceBlockAssignment_r10_type2_r10_nrb50_r10_present)
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb50_r10_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 11;
    if(size < 11 || size > 11)
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb50_r10_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((resourceBlockAssignment_r10_type2_r10_nrb50_r10_internal_value >> (11-i-1)) & 1);
    return 0;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb50_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return resourceBlockAssignment_r10_type2_r10_nrb50_r10_Unpack(bits, idx);
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb50_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 11;
    if(size < 11 || size > 11)
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb50_r10_Unpack() size failure\n");
        return -1;
    }
    resourceBlockAssignment_r10_type2_r10_nrb50_r10_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb50_r10_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        resourceBlockAssignment_r10_type2_r10_nrb50_r10_internal_value |= (uint16_t)bits[idx++] << (uint16_t)(11-i-1);
    resourceBlockAssignment_r10_type2_r10_nrb50_r10_present = true;
    return 0;
}

uint16_t RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb50_r10_Value() const
{
    if(resourceBlockAssignment_r10_type2_r10_nrb50_r10_present)
        return resourceBlockAssignment_r10_type2_r10_nrb50_r10_internal_value;
    uint16_t tmp = 0;
    return tmp;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb50_r10_SetValue(uint16_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 11)
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb50_r10_SetValue() size failure\n");
        return -1;
    }
    resourceBlockAssignment_r10_type2_r10_nrb50_r10_internal_value = value;
    resourceBlockAssignment_r10_type2_r10_nrb50_r10_present = true;
    return 0;
}

std::string RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb50_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "nrb50_r10 = ";
    out += std::to_string(resourceBlockAssignment_r10_type2_r10_nrb50_r10_internal_value);
    out += "\n";
    return out;
}

std::string RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb50_r10_ToStringNoNewLines() const
{
    std::string out = "nrb50_r10=";
    out += std::to_string(resourceBlockAssignment_r10_type2_r10_nrb50_r10_internal_value);
    out += ",";
    return out;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb50_r10_Clear()
{
    resourceBlockAssignment_r10_type2_r10_nrb50_r10_present = false;
    return 0;
}

bool RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb50_r10_IsPresent() const
{
    return resourceBlockAssignment_r10_type2_r10_nrb50_r10_present;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb75_r10_Pack(std::vector<uint8_t> &bits)
{
    if(!resourceBlockAssignment_r10_type2_r10_nrb75_r10_present)
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb75_r10_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 12;
    if(size < 12 || size > 12)
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb75_r10_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((resourceBlockAssignment_r10_type2_r10_nrb75_r10_internal_value >> (12-i-1)) & 1);
    return 0;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb75_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return resourceBlockAssignment_r10_type2_r10_nrb75_r10_Unpack(bits, idx);
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb75_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 12;
    if(size < 12 || size > 12)
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb75_r10_Unpack() size failure\n");
        return -1;
    }
    resourceBlockAssignment_r10_type2_r10_nrb75_r10_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb75_r10_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        resourceBlockAssignment_r10_type2_r10_nrb75_r10_internal_value |= (uint16_t)bits[idx++] << (uint16_t)(12-i-1);
    resourceBlockAssignment_r10_type2_r10_nrb75_r10_present = true;
    return 0;
}

uint16_t RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb75_r10_Value() const
{
    if(resourceBlockAssignment_r10_type2_r10_nrb75_r10_present)
        return resourceBlockAssignment_r10_type2_r10_nrb75_r10_internal_value;
    uint16_t tmp = 0;
    return tmp;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb75_r10_SetValue(uint16_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 12)
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb75_r10_SetValue() size failure\n");
        return -1;
    }
    resourceBlockAssignment_r10_type2_r10_nrb75_r10_internal_value = value;
    resourceBlockAssignment_r10_type2_r10_nrb75_r10_present = true;
    return 0;
}

std::string RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb75_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "nrb75_r10 = ";
    out += std::to_string(resourceBlockAssignment_r10_type2_r10_nrb75_r10_internal_value);
    out += "\n";
    return out;
}

std::string RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb75_r10_ToStringNoNewLines() const
{
    std::string out = "nrb75_r10=";
    out += std::to_string(resourceBlockAssignment_r10_type2_r10_nrb75_r10_internal_value);
    out += ",";
    return out;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb75_r10_Clear()
{
    resourceBlockAssignment_r10_type2_r10_nrb75_r10_present = false;
    return 0;
}

bool RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb75_r10_IsPresent() const
{
    return resourceBlockAssignment_r10_type2_r10_nrb75_r10_present;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb100_r10_Pack(std::vector<uint8_t> &bits)
{
    if(!resourceBlockAssignment_r10_type2_r10_nrb100_r10_present)
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb100_r10_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 13;
    if(size < 13 || size > 13)
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb100_r10_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((resourceBlockAssignment_r10_type2_r10_nrb100_r10_internal_value >> (13-i-1)) & 1);
    return 0;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb100_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return resourceBlockAssignment_r10_type2_r10_nrb100_r10_Unpack(bits, idx);
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb100_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 13;
    if(size < 13 || size > 13)
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb100_r10_Unpack() size failure\n");
        return -1;
    }
    resourceBlockAssignment_r10_type2_r10_nrb100_r10_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb100_r10_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        resourceBlockAssignment_r10_type2_r10_nrb100_r10_internal_value |= (uint16_t)bits[idx++] << (uint16_t)(13-i-1);
    resourceBlockAssignment_r10_type2_r10_nrb100_r10_present = true;
    return 0;
}

uint16_t RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb100_r10_Value() const
{
    if(resourceBlockAssignment_r10_type2_r10_nrb100_r10_present)
        return resourceBlockAssignment_r10_type2_r10_nrb100_r10_internal_value;
    uint16_t tmp = 0;
    return tmp;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb100_r10_SetValue(uint16_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 13)
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb100_r10_SetValue() size failure\n");
        return -1;
    }
    resourceBlockAssignment_r10_type2_r10_nrb100_r10_internal_value = value;
    resourceBlockAssignment_r10_type2_r10_nrb100_r10_present = true;
    return 0;
}

std::string RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb100_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "nrb100_r10 = ";
    out += std::to_string(resourceBlockAssignment_r10_type2_r10_nrb100_r10_internal_value);
    out += "\n";
    return out;
}

std::string RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb100_r10_ToStringNoNewLines() const
{
    std::string out = "nrb100_r10=";
    out += std::to_string(resourceBlockAssignment_r10_type2_r10_nrb100_r10_internal_value);
    out += ",";
    return out;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb100_r10_Clear()
{
    resourceBlockAssignment_r10_type2_r10_nrb100_r10_present = false;
    return 0;
}

bool RN_SubframeConfig_r10::rpdcch_Config_r10::resourceBlockAssignment_r10_type2_r10_nrb100_r10_IsPresent() const
{
    return resourceBlockAssignment_r10_type2_r10_nrb100_r10_present;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::demodulationRS_r10_Pack(std::vector<uint8_t> &bits)
{
    if(!demodulationRS_r10_present)
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::demodulationRS_r10_Pack() presence failure\n");
        return -1;
    }
    // Extension indicator

    // Choice
    for(uint32_t i=0; i<1; i++)
        bits.push_back((demodulationRS_r10_internal_choice >> (1-i-1)) & 1);

    // Fields
    if(demodulationRS_r10_internal_choice == k_demodulationRS_r10_interleaving_r10)
    {
        if(0 != demodulationRS_r10_interleaving_r10_Pack(bits))
        {
            printf("RN_SubframeConfig_r10::rpdcch_Config_r10::demodulationRS_r10_interleaving_r10 pack failure\n");
            return -1;
        }
    }
    if(demodulationRS_r10_internal_choice == k_demodulationRS_r10_noInterleaving_r10)
    {
        if(0 != demodulationRS_r10_noInterleaving_r10_Pack(bits))
        {
            printf("RN_SubframeConfig_r10::rpdcch_Config_r10::demodulationRS_r10_noInterleaving_r10 pack failure\n");
            return -1;
        }
    }
    return 0;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::demodulationRS_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return demodulationRS_r10_Unpack(bits, idx);
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::demodulationRS_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 1) > bits.size())
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::demodulationRS_r10_Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<1; i++)
        packed_val |= bits[idx++] << (1-i-1);

    if((RN_SubframeConfig_r10::rpdcch_Config_r10::demodulationRS_r10_Enum)packed_val > k_demodulationRS_r10_noInterleaving_r10)
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::demodulationRS_r10_Unpack() choice range failure\n");
        return -1;
    }
    demodulationRS_r10_internal_choice = (RN_SubframeConfig_r10::rpdcch_Config_r10::demodulationRS_r10_Enum)packed_val;
    demodulationRS_r10_present = true;

    // Fields
    if(demodulationRS_r10_internal_choice == k_demodulationRS_r10_interleaving_r10)
    {
        if(0 != demodulationRS_r10_interleaving_r10_Unpack(bits, idx))
        {
            printf("RN_SubframeConfig_r10::rpdcch_Config_r10::demodulationRS_r10_interleaving_r10 unpack failure\n");
            return -1;
        }
    }
    if(demodulationRS_r10_internal_choice == k_demodulationRS_r10_noInterleaving_r10)
    {
        if(0 != demodulationRS_r10_noInterleaving_r10_Unpack(bits, idx))
        {
            printf("RN_SubframeConfig_r10::rpdcch_Config_r10::demodulationRS_r10_noInterleaving_r10 unpack failure\n");
            return -1;
        }
    }
    return 0;
}

RN_SubframeConfig_r10::rpdcch_Config_r10::demodulationRS_r10_Enum RN_SubframeConfig_r10::rpdcch_Config_r10::demodulationRS_r10_Choice() const
{
    if(demodulationRS_r10_present)
        return demodulationRS_r10_internal_choice;
    return (RN_SubframeConfig_r10::rpdcch_Config_r10::demodulationRS_r10_Enum)0;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::demodulationRS_r10_SetChoice(RN_SubframeConfig_r10::rpdcch_Config_r10::demodulationRS_r10_Enum choice)
{
    demodulationRS_r10_internal_choice = choice;
    demodulationRS_r10_present = true;
    return 0;
}

std::string RN_SubframeConfig_r10::rpdcch_Config_r10::demodulationRS_r10_ChoiceToString(demodulationRS_r10_Enum value) const
{
    if(k_demodulationRS_r10_interleaving_r10 == value)
        return "demodulationRS_r10_interleaving_r10";
    if(k_demodulationRS_r10_noInterleaving_r10 == value)
        return "demodulationRS_r10_noInterleaving_r10";
    return "";
}

uint64_t RN_SubframeConfig_r10::rpdcch_Config_r10::demodulationRS_r10_NumberOfChoices() const
{
    return 2;
}

std::string RN_SubframeConfig_r10::rpdcch_Config_r10::demodulationRS_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "demodulationRS_r10 = " + demodulationRS_r10_ChoiceToString(demodulationRS_r10_internal_choice) + ":\n";
    if(demodulationRS_r10_internal_choice == k_demodulationRS_r10_interleaving_r10)
        out += demodulationRS_r10_interleaving_r10_ToString(indent+1);
    if(demodulationRS_r10_internal_choice == k_demodulationRS_r10_noInterleaving_r10)
        out += demodulationRS_r10_noInterleaving_r10_ToString(indent+1);
    return out;
}

std::string RN_SubframeConfig_r10::rpdcch_Config_r10::demodulationRS_r10_ToStringNoNewLines() const
{
    std::string out = "demodulationRS_r10=" + demodulationRS_r10_ChoiceToString(demodulationRS_r10_internal_choice) + ",";
    if(demodulationRS_r10_internal_choice == k_demodulationRS_r10_interleaving_r10)
        out += demodulationRS_r10_interleaving_r10_ToStringNoNewLines();
    if(demodulationRS_r10_internal_choice == k_demodulationRS_r10_noInterleaving_r10)
        out += demodulationRS_r10_noInterleaving_r10_ToStringNoNewLines();
    return out;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::demodulationRS_r10_Clear()
{
    demodulationRS_r10_present = false;
    return 0;
}

bool RN_SubframeConfig_r10::rpdcch_Config_r10::demodulationRS_r10_IsPresent() const
{
    return demodulationRS_r10_present;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::demodulationRS_r10_interleaving_r10_Pack(std::vector<uint8_t> &bits)
{
    if(!demodulationRS_r10_interleaving_r10_present)
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::demodulationRS_r10_interleaving_r10_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((demodulationRS_r10_interleaving_r10_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::demodulationRS_r10_interleaving_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return demodulationRS_r10_interleaving_r10_Unpack(bits, idx);
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::demodulationRS_r10_interleaving_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::demodulationRS_r10_interleaving_r10_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 0)
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::demodulationRS_r10_interleaving_r10_Unpack() max failure\n");
        return -1;
    }
    demodulationRS_r10_interleaving_r10_internal_value = (demodulationRS_r10_interleaving_r10_Enum)packed_val;
    demodulationRS_r10_interleaving_r10_present = true;
    return 0;
}

RN_SubframeConfig_r10::rpdcch_Config_r10::demodulationRS_r10_interleaving_r10_Enum RN_SubframeConfig_r10::rpdcch_Config_r10::demodulationRS_r10_interleaving_r10_Value() const
{
    if(demodulationRS_r10_interleaving_r10_present)
        return demodulationRS_r10_interleaving_r10_internal_value;
    return (RN_SubframeConfig_r10::rpdcch_Config_r10::demodulationRS_r10_interleaving_r10_Enum)0;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::demodulationRS_r10_interleaving_r10_SetValue(demodulationRS_r10_interleaving_r10_Enum value)
{
    demodulationRS_r10_interleaving_r10_internal_value = value;
    demodulationRS_r10_interleaving_r10_present = true;
    return 0;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::demodulationRS_r10_interleaving_r10_SetValue(std::string value)
{
    if("crs" == value)
    {
        demodulationRS_r10_interleaving_r10_internal_value = k_demodulationRS_r10_interleaving_r10_crs;
        demodulationRS_r10_interleaving_r10_present = true;
        return 0;
    }
    return 1;
}

std::string RN_SubframeConfig_r10::rpdcch_Config_r10::demodulationRS_r10_interleaving_r10_ValueToString(demodulationRS_r10_interleaving_r10_Enum value) const
{
    if(k_demodulationRS_r10_interleaving_r10_crs == value)
        return "crs";
    return "";
}

uint64_t RN_SubframeConfig_r10::rpdcch_Config_r10::demodulationRS_r10_interleaving_r10_NumberOfValues() const
{
    return 1;
}

std::string RN_SubframeConfig_r10::rpdcch_Config_r10::demodulationRS_r10_interleaving_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "interleaving_r10 = " + demodulationRS_r10_interleaving_r10_ValueToString(demodulationRS_r10_interleaving_r10_internal_value) + "\n";
    return out;
}

std::string RN_SubframeConfig_r10::rpdcch_Config_r10::demodulationRS_r10_interleaving_r10_ToStringNoNewLines() const
{
    std::string out = "interleaving_r10=" + demodulationRS_r10_interleaving_r10_ValueToString(demodulationRS_r10_interleaving_r10_internal_value) + ",";
    return out;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::demodulationRS_r10_interleaving_r10_Clear()
{
    demodulationRS_r10_interleaving_r10_present = false;
    return 0;
}

bool RN_SubframeConfig_r10::rpdcch_Config_r10::demodulationRS_r10_interleaving_r10_IsPresent() const
{
    return demodulationRS_r10_interleaving_r10_present;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::demodulationRS_r10_noInterleaving_r10_Pack(std::vector<uint8_t> &bits)
{
    if(!demodulationRS_r10_noInterleaving_r10_present)
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::demodulationRS_r10_noInterleaving_r10_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((demodulationRS_r10_noInterleaving_r10_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::demodulationRS_r10_noInterleaving_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return demodulationRS_r10_noInterleaving_r10_Unpack(bits, idx);
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::demodulationRS_r10_noInterleaving_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::demodulationRS_r10_noInterleaving_r10_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 1)
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::demodulationRS_r10_noInterleaving_r10_Unpack() max failure\n");
        return -1;
    }
    demodulationRS_r10_noInterleaving_r10_internal_value = (demodulationRS_r10_noInterleaving_r10_Enum)packed_val;
    demodulationRS_r10_noInterleaving_r10_present = true;
    return 0;
}

RN_SubframeConfig_r10::rpdcch_Config_r10::demodulationRS_r10_noInterleaving_r10_Enum RN_SubframeConfig_r10::rpdcch_Config_r10::demodulationRS_r10_noInterleaving_r10_Value() const
{
    if(demodulationRS_r10_noInterleaving_r10_present)
        return demodulationRS_r10_noInterleaving_r10_internal_value;
    return (RN_SubframeConfig_r10::rpdcch_Config_r10::demodulationRS_r10_noInterleaving_r10_Enum)0;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::demodulationRS_r10_noInterleaving_r10_SetValue(demodulationRS_r10_noInterleaving_r10_Enum value)
{
    demodulationRS_r10_noInterleaving_r10_internal_value = value;
    demodulationRS_r10_noInterleaving_r10_present = true;
    return 0;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::demodulationRS_r10_noInterleaving_r10_SetValue(std::string value)
{
    if("crs" == value)
    {
        demodulationRS_r10_noInterleaving_r10_internal_value = k_demodulationRS_r10_noInterleaving_r10_crs;
        demodulationRS_r10_noInterleaving_r10_present = true;
        return 0;
    }
    if("dmrs" == value)
    {
        demodulationRS_r10_noInterleaving_r10_internal_value = k_demodulationRS_r10_noInterleaving_r10_dmrs;
        demodulationRS_r10_noInterleaving_r10_present = true;
        return 0;
    }
    return 1;
}

std::string RN_SubframeConfig_r10::rpdcch_Config_r10::demodulationRS_r10_noInterleaving_r10_ValueToString(demodulationRS_r10_noInterleaving_r10_Enum value) const
{
    if(k_demodulationRS_r10_noInterleaving_r10_crs == value)
        return "crs";
    if(k_demodulationRS_r10_noInterleaving_r10_dmrs == value)
        return "dmrs";
    return "";
}

uint64_t RN_SubframeConfig_r10::rpdcch_Config_r10::demodulationRS_r10_noInterleaving_r10_NumberOfValues() const
{
    return 2;
}

std::string RN_SubframeConfig_r10::rpdcch_Config_r10::demodulationRS_r10_noInterleaving_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "noInterleaving_r10 = " + demodulationRS_r10_noInterleaving_r10_ValueToString(demodulationRS_r10_noInterleaving_r10_internal_value) + "\n";
    return out;
}

std::string RN_SubframeConfig_r10::rpdcch_Config_r10::demodulationRS_r10_noInterleaving_r10_ToStringNoNewLines() const
{
    std::string out = "noInterleaving_r10=" + demodulationRS_r10_noInterleaving_r10_ValueToString(demodulationRS_r10_noInterleaving_r10_internal_value) + ",";
    return out;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::demodulationRS_r10_noInterleaving_r10_Clear()
{
    demodulationRS_r10_noInterleaving_r10_present = false;
    return 0;
}

bool RN_SubframeConfig_r10::rpdcch_Config_r10::demodulationRS_r10_noInterleaving_r10_IsPresent() const
{
    return demodulationRS_r10_noInterleaving_r10_present;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::pdsch_Start_r10_Pack(std::vector<uint8_t> &bits)
{
    if(!pdsch_Start_r10_present)
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::pdsch_Start_r10_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = pdsch_Start_r10_internal_value - (1);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (3 - 1))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::pdsch_Start_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return pdsch_Start_r10_Unpack(bits, idx);
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::pdsch_Start_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (3 - 1))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::pdsch_Start_r10_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    pdsch_Start_r10_internal_value = packed_val + 1;
    pdsch_Start_r10_present = true;
    return 0;
}

int64_t RN_SubframeConfig_r10::rpdcch_Config_r10::pdsch_Start_r10_Value() const
{
    if(pdsch_Start_r10_present)
        return pdsch_Start_r10_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::pdsch_Start_r10_SetValue(int64_t value)
{
    if(value < 1 || value > 3)
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::pdsch_Start_r10_SetValue() range failure\n");
        return -1;
    }
    pdsch_Start_r10_internal_value = value;
    pdsch_Start_r10_present = true;
    return 0;
}

std::string RN_SubframeConfig_r10::rpdcch_Config_r10::pdsch_Start_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "pdsch_Start_r10 = " + std::to_string(pdsch_Start_r10_internal_value) + "\n";
    return out;
}

std::string RN_SubframeConfig_r10::rpdcch_Config_r10::pdsch_Start_r10_ToStringNoNewLines() const
{
    std::string out = "pdsch_Start_r10=" + std::to_string(pdsch_Start_r10_internal_value) + ",";
    return out;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::pdsch_Start_r10_Clear()
{
    pdsch_Start_r10_present = false;
    return 0;
}

bool RN_SubframeConfig_r10::rpdcch_Config_r10::pdsch_Start_r10_IsPresent() const
{
    return pdsch_Start_r10_present;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::pucch_Config_r10::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != n1_PUCCH_AN_port0_r10_Pack(bits))
        {
            printf("RN_SubframeConfig_r10::rpdcch_Config_r10::pucch_Config_r10:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != n1_PUCCH_AN_port1_r10_Pack(bits))
        {
            printf("RN_SubframeConfig_r10::rpdcch_Config_r10::pucch_Config_r10:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::pucch_Config_r10::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::pucch_Config_r10::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != n1_PUCCH_AN_port0_r10_Unpack(bits, idx))
        {
            printf("RN_SubframeConfig_r10::rpdcch_Config_r10::pucch_Config_r10:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != n1_PUCCH_AN_port1_r10_Unpack(bits, idx))
        {
            printf("RN_SubframeConfig_r10::rpdcch_Config_r10::pucch_Config_r10:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string RN_SubframeConfig_r10::rpdcch_Config_r10::pucch_Config_r10::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "pucch_Config_r10:\n";
    out += n1_PUCCH_AN_port0_r10_ToString(indent+1);
    out += n1_PUCCH_AN_port1_r10_ToString(indent+1);
    return out;
}

std::string RN_SubframeConfig_r10::rpdcch_Config_r10::pucch_Config_r10::ToStringNoNewLines() const
{
    std::string out = "pucch_Config_r10:";
    out += n1_PUCCH_AN_port0_r10_ToStringNoNewLines();
    out += n1_PUCCH_AN_port1_r10_ToStringNoNewLines();
    return out;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::pucch_Config_r10::n1_PUCCH_AN_port0_r10_Pack(std::vector<uint8_t> &bits)
{
    if(!n1_PUCCH_AN_port0_r10_present)
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::pucch_Config_r10::n1_PUCCH_AN_port0_r10_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = n1_PUCCH_AN_port0_r10_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (2047 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::pucch_Config_r10::n1_PUCCH_AN_port0_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return n1_PUCCH_AN_port0_r10_Unpack(bits, idx);
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::pucch_Config_r10::n1_PUCCH_AN_port0_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (2047 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::pucch_Config_r10::n1_PUCCH_AN_port0_r10_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    n1_PUCCH_AN_port0_r10_internal_value = packed_val + 0;
    n1_PUCCH_AN_port0_r10_present = true;
    return 0;
}

int64_t RN_SubframeConfig_r10::rpdcch_Config_r10::pucch_Config_r10::n1_PUCCH_AN_port0_r10_Value() const
{
    if(n1_PUCCH_AN_port0_r10_present)
        return n1_PUCCH_AN_port0_r10_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::pucch_Config_r10::n1_PUCCH_AN_port0_r10_SetValue(int64_t value)
{
    if(value < 0 || value > 2047)
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::pucch_Config_r10::n1_PUCCH_AN_port0_r10_SetValue() range failure\n");
        return -1;
    }
    n1_PUCCH_AN_port0_r10_internal_value = value;
    n1_PUCCH_AN_port0_r10_present = true;
    return 0;
}

std::string RN_SubframeConfig_r10::rpdcch_Config_r10::pucch_Config_r10::n1_PUCCH_AN_port0_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "n1_PUCCH_AN_port0_r10 = " + std::to_string(n1_PUCCH_AN_port0_r10_internal_value) + "\n";
    return out;
}

std::string RN_SubframeConfig_r10::rpdcch_Config_r10::pucch_Config_r10::n1_PUCCH_AN_port0_r10_ToStringNoNewLines() const
{
    std::string out = "n1_PUCCH_AN_port0_r10=" + std::to_string(n1_PUCCH_AN_port0_r10_internal_value) + ",";
    return out;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::pucch_Config_r10::n1_PUCCH_AN_port0_r10_Clear()
{
    n1_PUCCH_AN_port0_r10_present = false;
    return 0;
}

bool RN_SubframeConfig_r10::rpdcch_Config_r10::pucch_Config_r10::n1_PUCCH_AN_port0_r10_IsPresent() const
{
    return n1_PUCCH_AN_port0_r10_present;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::pucch_Config_r10::n1_PUCCH_AN_port1_r10_Pack(std::vector<uint8_t> &bits)
{
    if(!n1_PUCCH_AN_port1_r10_present)
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::pucch_Config_r10::n1_PUCCH_AN_port1_r10_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = n1_PUCCH_AN_port1_r10_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (2047 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::pucch_Config_r10::n1_PUCCH_AN_port1_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return n1_PUCCH_AN_port1_r10_Unpack(bits, idx);
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::pucch_Config_r10::n1_PUCCH_AN_port1_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (2047 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::pucch_Config_r10::n1_PUCCH_AN_port1_r10_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    n1_PUCCH_AN_port1_r10_internal_value = packed_val + 0;
    n1_PUCCH_AN_port1_r10_present = true;
    return 0;
}

int64_t RN_SubframeConfig_r10::rpdcch_Config_r10::pucch_Config_r10::n1_PUCCH_AN_port1_r10_Value() const
{
    if(n1_PUCCH_AN_port1_r10_present)
        return n1_PUCCH_AN_port1_r10_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::pucch_Config_r10::n1_PUCCH_AN_port1_r10_SetValue(int64_t value)
{
    if(value < 0 || value > 2047)
    {
        printf("RN_SubframeConfig_r10::rpdcch_Config_r10::pucch_Config_r10::n1_PUCCH_AN_port1_r10_SetValue() range failure\n");
        return -1;
    }
    n1_PUCCH_AN_port1_r10_internal_value = value;
    n1_PUCCH_AN_port1_r10_present = true;
    return 0;
}

std::string RN_SubframeConfig_r10::rpdcch_Config_r10::pucch_Config_r10::n1_PUCCH_AN_port1_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "n1_PUCCH_AN_port1_r10 = " + std::to_string(n1_PUCCH_AN_port1_r10_internal_value) + "\n";
    return out;
}

std::string RN_SubframeConfig_r10::rpdcch_Config_r10::pucch_Config_r10::n1_PUCCH_AN_port1_r10_ToStringNoNewLines() const
{
    std::string out = "n1_PUCCH_AN_port1_r10=" + std::to_string(n1_PUCCH_AN_port1_r10_internal_value) + ",";
    return out;
}

int RN_SubframeConfig_r10::rpdcch_Config_r10::pucch_Config_r10::n1_PUCCH_AN_port1_r10_Clear()
{
    n1_PUCCH_AN_port1_r10_present = false;
    return 0;
}

bool RN_SubframeConfig_r10::rpdcch_Config_r10::pucch_Config_r10::n1_PUCCH_AN_port1_r10_IsPresent() const
{
    return n1_PUCCH_AN_port1_r10_present;
}

