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

#include "MeasGapConfig.h"

#include <cmath>

int MeasGapConfig::Pack(std::vector<uint8_t> &bits)
{
    if(!present)
    {
        printf("MeasGapConfig::Pack() presence failure\n");
        return -1;
    }
    // Extension indicator

    // Choice
    for(uint32_t i=0; i<1; i++)
        bits.push_back((internal_choice >> (1-i-1)) & 1);

    // Fields
    if(internal_choice == k_release)
    {
        if(0 != release_Pack(bits))
        {
            printf("MeasGapConfig::release pack failure\n");
            return -1;
        }
    }
    if(internal_choice == k_setup)
    {
        if(0 != setup_value.Pack(bits))
        {
            printf("MeasGapConfig::setup pack failure\n");
            return -1;
        }
    }
    return 0;
}

int MeasGapConfig::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int MeasGapConfig::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 1) > bits.size())
    {
        printf("MeasGapConfig::Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<1; i++)
        packed_val |= bits[idx++] << (1-i-1);

    if((MeasGapConfig::Enum)packed_val > k_setup)
    {
        printf("MeasGapConfig::Unpack() choice range failure\n");
        return -1;
    }
    internal_choice = (MeasGapConfig::Enum)packed_val;
    present = true;

    // Fields
    if(internal_choice == k_release)
    {
        if(0 != release_Unpack(bits, idx))
        {
            printf("MeasGapConfig::release unpack failure\n");
            return -1;
        }
    }
    if(internal_choice == k_setup)
    {
        if(0 != setup_value.Unpack(bits, idx))
        {
            printf("MeasGapConfig::setup unpack failure\n");
            return -1;
        }
    }
    return 0;
}

MeasGapConfig::Enum MeasGapConfig::Choice() const
{
    if(present)
        return internal_choice;
    return (MeasGapConfig::Enum)0;
}

int MeasGapConfig::SetChoice(MeasGapConfig::Enum choice)
{
    internal_choice = choice;
    present = true;
    return 0;
}

std::string MeasGapConfig::ChoiceToString(Enum value) const
{
    if(k_release == value)
        return "release";
    if(k_setup == value)
        return "setup";
    return "";
}

uint64_t MeasGapConfig::NumberOfChoices() const
{
    return 2;
}

std::string MeasGapConfig::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "MeasGapConfig = " + ChoiceToString(internal_choice) + ":\n";
    if(internal_choice == k_setup)
        out += setup_value.ToString(indent+1);
    return out;
}

std::string MeasGapConfig::ToStringNoNewLines() const
{
    std::string out = "MeasGapConfig=" + ChoiceToString(internal_choice) + ",";
    if(internal_choice == k_setup)
        out += setup_value.ToStringNoNewLines();
    return out;
}

int MeasGapConfig::Clear()
{
    present = false;
    return 0;
}

bool MeasGapConfig::IsPresent() const
{
    return present;
}

int MeasGapConfig::setup::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != gapOffset_Pack(bits))
        {
            printf("MeasGapConfig::setup:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int MeasGapConfig::setup::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int MeasGapConfig::setup::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != gapOffset_Unpack(bits, idx))
        {
            printf("MeasGapConfig::setup:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string MeasGapConfig::setup::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "setup:\n";
    out += gapOffset_ToString(indent+1);
    return out;
}

std::string MeasGapConfig::setup::ToStringNoNewLines() const
{
    std::string out = "setup:";
    out += gapOffset_ToStringNoNewLines();
    return out;
}

int MeasGapConfig::setup::gapOffset_Pack(std::vector<uint8_t> &bits)
{
    if(!gapOffset_present)
    {
        printf("MeasGapConfig::setup::gapOffset_Pack() presence failure\n");
        return -1;
    }
    // Extension indicator
    bits.push_back(0);

    // Choice
    for(uint32_t i=0; i<1; i++)
        bits.push_back((gapOffset_internal_choice >> (1-i-1)) & 1);

    // Fields
    if(gapOffset_internal_choice == k_gapOffset_gp0)
    {
        if(0 != gapOffset_gp0_Pack(bits))
        {
            printf("MeasGapConfig::setup::gapOffset_gp0 pack failure\n");
            return -1;
        }
    }
    if(gapOffset_internal_choice == k_gapOffset_gp1)
    {
        if(0 != gapOffset_gp1_Pack(bits))
        {
            printf("MeasGapConfig::setup::gapOffset_gp1 pack failure\n");
            return -1;
        }
    }
    return 0;
}

int MeasGapConfig::setup::gapOffset_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return gapOffset_Unpack(bits, idx);
}

int MeasGapConfig::setup::gapOffset_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("MeasGapConfig::setup::gapOffset_Unpack() index out of bounds for extension\n");
        return -1;
    }
    idx++;

    // Choice
    uint32_t packed_val = 0;
    if((idx + 1) > bits.size())
    {
        printf("MeasGapConfig::setup::gapOffset_Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<1; i++)
        packed_val |= bits[idx++] << (1-i-1);

    if((MeasGapConfig::setup::gapOffset_Enum)packed_val > k_gapOffset_gp1)
    {
        printf("MeasGapConfig::setup::gapOffset_Unpack() choice range failure\n");
        return -1;
    }
    gapOffset_internal_choice = (MeasGapConfig::setup::gapOffset_Enum)packed_val;
    gapOffset_present = true;

    // Fields
    if(gapOffset_internal_choice == k_gapOffset_gp0)
    {
        if(0 != gapOffset_gp0_Unpack(bits, idx))
        {
            printf("MeasGapConfig::setup::gapOffset_gp0 unpack failure\n");
            return -1;
        }
    }
    if(gapOffset_internal_choice == k_gapOffset_gp1)
    {
        if(0 != gapOffset_gp1_Unpack(bits, idx))
        {
            printf("MeasGapConfig::setup::gapOffset_gp1 unpack failure\n");
            return -1;
        }
    }
    return 0;
}

MeasGapConfig::setup::gapOffset_Enum MeasGapConfig::setup::gapOffset_Choice() const
{
    if(gapOffset_present)
        return gapOffset_internal_choice;
    return (MeasGapConfig::setup::gapOffset_Enum)0;
}

int MeasGapConfig::setup::gapOffset_SetChoice(MeasGapConfig::setup::gapOffset_Enum choice)
{
    gapOffset_internal_choice = choice;
    gapOffset_present = true;
    return 0;
}

std::string MeasGapConfig::setup::gapOffset_ChoiceToString(gapOffset_Enum value) const
{
    if(k_gapOffset_gp0 == value)
        return "gapOffset_gp0";
    if(k_gapOffset_gp1 == value)
        return "gapOffset_gp1";
    return "";
}

uint64_t MeasGapConfig::setup::gapOffset_NumberOfChoices() const
{
    return 2;
}

std::string MeasGapConfig::setup::gapOffset_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "gapOffset = " + gapOffset_ChoiceToString(gapOffset_internal_choice) + ":\n";
    if(gapOffset_internal_choice == k_gapOffset_gp0)
        out += gapOffset_gp0_ToString(indent+1);
    if(gapOffset_internal_choice == k_gapOffset_gp1)
        out += gapOffset_gp1_ToString(indent+1);
    return out;
}

std::string MeasGapConfig::setup::gapOffset_ToStringNoNewLines() const
{
    std::string out = "gapOffset=" + gapOffset_ChoiceToString(gapOffset_internal_choice) + ",";
    if(gapOffset_internal_choice == k_gapOffset_gp0)
        out += gapOffset_gp0_ToStringNoNewLines();
    if(gapOffset_internal_choice == k_gapOffset_gp1)
        out += gapOffset_gp1_ToStringNoNewLines();
    return out;
}

int MeasGapConfig::setup::gapOffset_Clear()
{
    gapOffset_present = false;
    return 0;
}

bool MeasGapConfig::setup::gapOffset_IsPresent() const
{
    return gapOffset_present;
}

int MeasGapConfig::setup::gapOffset_gp0_Pack(std::vector<uint8_t> &bits)
{
    if(!gapOffset_gp0_present)
    {
        printf("MeasGapConfig::setup::gapOffset_gp0_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = gapOffset_gp0_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (39 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int MeasGapConfig::setup::gapOffset_gp0_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return gapOffset_gp0_Unpack(bits, idx);
}

int MeasGapConfig::setup::gapOffset_gp0_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (39 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("MeasGapConfig::setup::gapOffset_gp0_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    gapOffset_gp0_internal_value = packed_val + 0;
    gapOffset_gp0_present = true;
    return 0;
}

int64_t MeasGapConfig::setup::gapOffset_gp0_Value() const
{
    if(gapOffset_gp0_present)
        return gapOffset_gp0_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int MeasGapConfig::setup::gapOffset_gp0_SetValue(int64_t value)
{
    if(value < 0 || value > 39)
    {
        printf("MeasGapConfig::setup::gapOffset_gp0_SetValue() range failure\n");
        return -1;
    }
    gapOffset_gp0_internal_value = value;
    gapOffset_gp0_present = true;
    return 0;
}

std::string MeasGapConfig::setup::gapOffset_gp0_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "gp0 = " + std::to_string(gapOffset_gp0_internal_value) + "\n";
    return out;
}

std::string MeasGapConfig::setup::gapOffset_gp0_ToStringNoNewLines() const
{
    std::string out = "gp0=" + std::to_string(gapOffset_gp0_internal_value) + ",";
    return out;
}

int MeasGapConfig::setup::gapOffset_gp0_Clear()
{
    gapOffset_gp0_present = false;
    return 0;
}

bool MeasGapConfig::setup::gapOffset_gp0_IsPresent() const
{
    return gapOffset_gp0_present;
}

int MeasGapConfig::setup::gapOffset_gp1_Pack(std::vector<uint8_t> &bits)
{
    if(!gapOffset_gp1_present)
    {
        printf("MeasGapConfig::setup::gapOffset_gp1_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = gapOffset_gp1_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (79 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int MeasGapConfig::setup::gapOffset_gp1_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return gapOffset_gp1_Unpack(bits, idx);
}

int MeasGapConfig::setup::gapOffset_gp1_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (79 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("MeasGapConfig::setup::gapOffset_gp1_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    gapOffset_gp1_internal_value = packed_val + 0;
    gapOffset_gp1_present = true;
    return 0;
}

int64_t MeasGapConfig::setup::gapOffset_gp1_Value() const
{
    if(gapOffset_gp1_present)
        return gapOffset_gp1_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int MeasGapConfig::setup::gapOffset_gp1_SetValue(int64_t value)
{
    if(value < 0 || value > 79)
    {
        printf("MeasGapConfig::setup::gapOffset_gp1_SetValue() range failure\n");
        return -1;
    }
    gapOffset_gp1_internal_value = value;
    gapOffset_gp1_present = true;
    return 0;
}

std::string MeasGapConfig::setup::gapOffset_gp1_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "gp1 = " + std::to_string(gapOffset_gp1_internal_value) + "\n";
    return out;
}

std::string MeasGapConfig::setup::gapOffset_gp1_ToStringNoNewLines() const
{
    std::string out = "gp1=" + std::to_string(gapOffset_gp1_internal_value) + ",";
    return out;
}

int MeasGapConfig::setup::gapOffset_gp1_Clear()
{
    gapOffset_gp1_present = false;
    return 0;
}

bool MeasGapConfig::setup::gapOffset_gp1_IsPresent() const
{
    return gapOffset_gp1_present;
}

