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

#include "ThresholdUTRA.h"

#include <cmath>

int ThresholdUTRA::Pack(std::vector<uint8_t> &bits)
{
    if(!present)
    {
        printf("ThresholdUTRA::Pack() presence failure\n");
        return -1;
    }
    // Extension indicator

    // Choice
    for(uint32_t i=0; i<1; i++)
        bits.push_back((internal_choice >> (1-i-1)) & 1);

    // Fields
    if(internal_choice == k_utra_RSCP)
    {
        if(0 != utra_RSCP_Pack(bits))
        {
            printf("ThresholdUTRA::utra_RSCP pack failure\n");
            return -1;
        }
    }
    if(internal_choice == k_utra_EcN0)
    {
        if(0 != utra_EcN0_Pack(bits))
        {
            printf("ThresholdUTRA::utra_EcN0 pack failure\n");
            return -1;
        }
    }
    return 0;
}

int ThresholdUTRA::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int ThresholdUTRA::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 1) > bits.size())
    {
        printf("ThresholdUTRA::Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<1; i++)
        packed_val |= bits[idx++] << (1-i-1);

    if((ThresholdUTRA::Enum)packed_val > k_utra_EcN0)
    {
        printf("ThresholdUTRA::Unpack() choice range failure\n");
        return -1;
    }
    internal_choice = (ThresholdUTRA::Enum)packed_val;
    present = true;

    // Fields
    if(internal_choice == k_utra_RSCP)
    {
        if(0 != utra_RSCP_Unpack(bits, idx))
        {
            printf("ThresholdUTRA::utra_RSCP unpack failure\n");
            return -1;
        }
    }
    if(internal_choice == k_utra_EcN0)
    {
        if(0 != utra_EcN0_Unpack(bits, idx))
        {
            printf("ThresholdUTRA::utra_EcN0 unpack failure\n");
            return -1;
        }
    }
    return 0;
}

ThresholdUTRA::Enum ThresholdUTRA::Choice() const
{
    if(present)
        return internal_choice;
    return (ThresholdUTRA::Enum)0;
}

int ThresholdUTRA::SetChoice(ThresholdUTRA::Enum choice)
{
    internal_choice = choice;
    present = true;
    return 0;
}

std::string ThresholdUTRA::ChoiceToString(Enum value) const
{
    if(k_utra_RSCP == value)
        return "utra_RSCP";
    if(k_utra_EcN0 == value)
        return "utra_EcN0";
    return "";
}

uint64_t ThresholdUTRA::NumberOfChoices() const
{
    return 2;
}

std::string ThresholdUTRA::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ThresholdUTRA = " + ChoiceToString(internal_choice) + ":\n";
    if(internal_choice == k_utra_RSCP)
        out += utra_RSCP_ToString(indent+1);
    if(internal_choice == k_utra_EcN0)
        out += utra_EcN0_ToString(indent+1);
    return out;
}

std::string ThresholdUTRA::ToStringNoNewLines() const
{
    std::string out = "ThresholdUTRA=" + ChoiceToString(internal_choice) + ",";
    if(internal_choice == k_utra_RSCP)
        out += utra_RSCP_ToStringNoNewLines();
    if(internal_choice == k_utra_EcN0)
        out += utra_EcN0_ToStringNoNewLines();
    return out;
}

int ThresholdUTRA::Clear()
{
    present = false;
    return 0;
}

bool ThresholdUTRA::IsPresent() const
{
    return present;
}

int ThresholdUTRA::utra_RSCP_Pack(std::vector<uint8_t> &bits)
{
    if(!utra_RSCP_present)
    {
        printf("ThresholdUTRA::utra_RSCP_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = utra_RSCP_internal_value - (-5);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (91 - -5))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int ThresholdUTRA::utra_RSCP_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return utra_RSCP_Unpack(bits, idx);
}

int ThresholdUTRA::utra_RSCP_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (91 - -5))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("ThresholdUTRA::utra_RSCP_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    utra_RSCP_internal_value = packed_val + -5;
    utra_RSCP_present = true;
    return 0;
}

int64_t ThresholdUTRA::utra_RSCP_Value() const
{
    if(utra_RSCP_present)
        return utra_RSCP_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int ThresholdUTRA::utra_RSCP_SetValue(int64_t value)
{
    if(value < -5 || value > 91)
    {
        printf("ThresholdUTRA::utra_RSCP_SetValue() range failure\n");
        return -1;
    }
    utra_RSCP_internal_value = value;
    utra_RSCP_present = true;
    return 0;
}

std::string ThresholdUTRA::utra_RSCP_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "utra_RSCP = " + std::to_string(utra_RSCP_internal_value) + "\n";
    return out;
}

std::string ThresholdUTRA::utra_RSCP_ToStringNoNewLines() const
{
    std::string out = "utra_RSCP=" + std::to_string(utra_RSCP_internal_value) + ",";
    return out;
}

int ThresholdUTRA::utra_RSCP_Clear()
{
    utra_RSCP_present = false;
    return 0;
}

bool ThresholdUTRA::utra_RSCP_IsPresent() const
{
    return utra_RSCP_present;
}

int ThresholdUTRA::utra_EcN0_Pack(std::vector<uint8_t> &bits)
{
    if(!utra_EcN0_present)
    {
        printf("ThresholdUTRA::utra_EcN0_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = utra_EcN0_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (49 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int ThresholdUTRA::utra_EcN0_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return utra_EcN0_Unpack(bits, idx);
}

int ThresholdUTRA::utra_EcN0_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (49 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("ThresholdUTRA::utra_EcN0_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    utra_EcN0_internal_value = packed_val + 0;
    utra_EcN0_present = true;
    return 0;
}

int64_t ThresholdUTRA::utra_EcN0_Value() const
{
    if(utra_EcN0_present)
        return utra_EcN0_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int ThresholdUTRA::utra_EcN0_SetValue(int64_t value)
{
    if(value < 0 || value > 49)
    {
        printf("ThresholdUTRA::utra_EcN0_SetValue() range failure\n");
        return -1;
    }
    utra_EcN0_internal_value = value;
    utra_EcN0_present = true;
    return 0;
}

std::string ThresholdUTRA::utra_EcN0_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "utra_EcN0 = " + std::to_string(utra_EcN0_internal_value) + "\n";
    return out;
}

std::string ThresholdUTRA::utra_EcN0_ToStringNoNewLines() const
{
    std::string out = "utra_EcN0=" + std::to_string(utra_EcN0_internal_value) + ",";
    return out;
}

int ThresholdUTRA::utra_EcN0_Clear()
{
    utra_EcN0_present = false;
    return 0;
}

bool ThresholdUTRA::utra_EcN0_IsPresent() const
{
    return utra_EcN0_present;
}

