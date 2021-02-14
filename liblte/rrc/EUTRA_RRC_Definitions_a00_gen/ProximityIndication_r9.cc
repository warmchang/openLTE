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

#include "ProximityIndication_r9.h"

#include <cmath>

int ProximityIndication_r9::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != criticalExtensions_Pack(bits))
        {
            printf("ProximityIndication_r9:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int ProximityIndication_r9::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int ProximityIndication_r9::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != criticalExtensions_Unpack(bits, idx))
        {
            printf("ProximityIndication_r9:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string ProximityIndication_r9::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ProximityIndication_r9:\n";
    out += criticalExtensions_ToString(indent+1);
    return out;
}

std::string ProximityIndication_r9::ToStringNoNewLines() const
{
    std::string out = "ProximityIndication_r9:";
    out += criticalExtensions_ToStringNoNewLines();
    return out;
}

int ProximityIndication_r9::criticalExtensions_Pack(std::vector<uint8_t> &bits)
{
    if(!criticalExtensions_present)
    {
        printf("ProximityIndication_r9::criticalExtensions_Pack() presence failure\n");
        return -1;
    }
    // Extension indicator

    // Choice
    for(uint32_t i=0; i<1; i++)
        bits.push_back((criticalExtensions_internal_choice >> (1-i-1)) & 1);

    // Fields
    if(criticalExtensions_internal_choice == k_criticalExtensions_c1)
    {
        if(0 != criticalExtensions_c1_Pack(bits))
        {
            printf("ProximityIndication_r9::criticalExtensions_c1 pack failure\n");
            return -1;
        }
    }
    return 0;
}

int ProximityIndication_r9::criticalExtensions_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return criticalExtensions_Unpack(bits, idx);
}

int ProximityIndication_r9::criticalExtensions_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 1) > bits.size())
    {
        printf("ProximityIndication_r9::criticalExtensions_Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<1; i++)
        packed_val |= bits[idx++] << (1-i-1);

    if((ProximityIndication_r9::criticalExtensions_Enum)packed_val > k_criticalExtensions_criticalExtensionsFuture)
    {
        printf("ProximityIndication_r9::criticalExtensions_Unpack() choice range failure\n");
        return -1;
    }
    criticalExtensions_internal_choice = (ProximityIndication_r9::criticalExtensions_Enum)packed_val;
    criticalExtensions_present = true;

    // Fields
    if(criticalExtensions_internal_choice == k_criticalExtensions_c1)
    {
        if(0 != criticalExtensions_c1_Unpack(bits, idx))
        {
            printf("ProximityIndication_r9::criticalExtensions_c1 unpack failure\n");
            return -1;
        }
    }
    return 0;
}

ProximityIndication_r9::criticalExtensions_Enum ProximityIndication_r9::criticalExtensions_Choice() const
{
    if(criticalExtensions_present)
        return criticalExtensions_internal_choice;
    return (ProximityIndication_r9::criticalExtensions_Enum)0;
}

int ProximityIndication_r9::criticalExtensions_SetChoice(ProximityIndication_r9::criticalExtensions_Enum choice)
{
    criticalExtensions_internal_choice = choice;
    criticalExtensions_present = true;
    return 0;
}

std::string ProximityIndication_r9::criticalExtensions_ChoiceToString(criticalExtensions_Enum value) const
{
    if(k_criticalExtensions_c1 == value)
        return "criticalExtensions_c1";
    if(k_criticalExtensions_criticalExtensionsFuture == value)
        return "criticalExtensions_criticalExtensionsFuture";
    return "";
}

uint64_t ProximityIndication_r9::criticalExtensions_NumberOfChoices() const
{
    return 2;
}

std::string ProximityIndication_r9::criticalExtensions_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "criticalExtensions = " + criticalExtensions_ChoiceToString(criticalExtensions_internal_choice) + ":\n";
    if(criticalExtensions_internal_choice == k_criticalExtensions_c1)
        out += criticalExtensions_c1_ToString(indent+1);
    return out;
}

std::string ProximityIndication_r9::criticalExtensions_ToStringNoNewLines() const
{
    std::string out = "criticalExtensions=" + criticalExtensions_ChoiceToString(criticalExtensions_internal_choice) + ",";
    if(criticalExtensions_internal_choice == k_criticalExtensions_c1)
        out += criticalExtensions_c1_ToStringNoNewLines();
    return out;
}

int ProximityIndication_r9::criticalExtensions_Clear()
{
    criticalExtensions_present = false;
    return 0;
}

bool ProximityIndication_r9::criticalExtensions_IsPresent() const
{
    return criticalExtensions_present;
}

int ProximityIndication_r9::criticalExtensions_c1_Pack(std::vector<uint8_t> &bits)
{
    if(!criticalExtensions_c1_present)
    {
        printf("ProximityIndication_r9::criticalExtensions_c1_Pack() presence failure\n");
        return -1;
    }
    // Extension indicator

    // Choice
    for(uint32_t i=0; i<2; i++)
        bits.push_back((criticalExtensions_c1_internal_choice >> (2-i-1)) & 1);

    // Fields
    if(criticalExtensions_c1_internal_choice == k_criticalExtensions_c1_proximityIndication_r9)
    {
        if(0 != criticalExtensions_c1_proximityIndication_r9.Pack(bits))
        {
            printf("ProximityIndication_r9::criticalExtensions_c1_proximityIndication_r9 pack failure\n");
            return -1;
        }
    }
    if(criticalExtensions_c1_internal_choice == k_criticalExtensions_c1_spare3)
    {
        if(0 != criticalExtensions_c1_spare3_Pack(bits))
        {
            printf("ProximityIndication_r9::criticalExtensions_c1_spare3 pack failure\n");
            return -1;
        }
    }
    if(criticalExtensions_c1_internal_choice == k_criticalExtensions_c1_spare2)
    {
        if(0 != criticalExtensions_c1_spare2_Pack(bits))
        {
            printf("ProximityIndication_r9::criticalExtensions_c1_spare2 pack failure\n");
            return -1;
        }
    }
    if(criticalExtensions_c1_internal_choice == k_criticalExtensions_c1_spare1)
    {
        if(0 != criticalExtensions_c1_spare1_Pack(bits))
        {
            printf("ProximityIndication_r9::criticalExtensions_c1_spare1 pack failure\n");
            return -1;
        }
    }
    return 0;
}

int ProximityIndication_r9::criticalExtensions_c1_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return criticalExtensions_c1_Unpack(bits, idx);
}

int ProximityIndication_r9::criticalExtensions_c1_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 2) > bits.size())
    {
        printf("ProximityIndication_r9::criticalExtensions_c1_Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<2; i++)
        packed_val |= bits[idx++] << (2-i-1);

    if((ProximityIndication_r9::criticalExtensions_c1_Enum)packed_val > k_criticalExtensions_c1_spare1)
    {
        printf("ProximityIndication_r9::criticalExtensions_c1_Unpack() choice range failure\n");
        return -1;
    }
    criticalExtensions_c1_internal_choice = (ProximityIndication_r9::criticalExtensions_c1_Enum)packed_val;
    criticalExtensions_c1_present = true;

    // Fields
    if(criticalExtensions_c1_internal_choice == k_criticalExtensions_c1_proximityIndication_r9)
    {
        if(0 != criticalExtensions_c1_proximityIndication_r9.Unpack(bits, idx))
        {
            printf("ProximityIndication_r9::criticalExtensions_c1_proximityIndication_r9 unpack failure\n");
            return -1;
        }
    }
    if(criticalExtensions_c1_internal_choice == k_criticalExtensions_c1_spare3)
    {
        if(0 != criticalExtensions_c1_spare3_Unpack(bits, idx))
        {
            printf("ProximityIndication_r9::criticalExtensions_c1_spare3 unpack failure\n");
            return -1;
        }
    }
    if(criticalExtensions_c1_internal_choice == k_criticalExtensions_c1_spare2)
    {
        if(0 != criticalExtensions_c1_spare2_Unpack(bits, idx))
        {
            printf("ProximityIndication_r9::criticalExtensions_c1_spare2 unpack failure\n");
            return -1;
        }
    }
    if(criticalExtensions_c1_internal_choice == k_criticalExtensions_c1_spare1)
    {
        if(0 != criticalExtensions_c1_spare1_Unpack(bits, idx))
        {
            printf("ProximityIndication_r9::criticalExtensions_c1_spare1 unpack failure\n");
            return -1;
        }
    }
    return 0;
}

ProximityIndication_r9::criticalExtensions_c1_Enum ProximityIndication_r9::criticalExtensions_c1_Choice() const
{
    if(criticalExtensions_c1_present)
        return criticalExtensions_c1_internal_choice;
    return (ProximityIndication_r9::criticalExtensions_c1_Enum)0;
}

int ProximityIndication_r9::criticalExtensions_c1_SetChoice(ProximityIndication_r9::criticalExtensions_c1_Enum choice)
{
    criticalExtensions_c1_internal_choice = choice;
    criticalExtensions_c1_present = true;
    return 0;
}

std::string ProximityIndication_r9::criticalExtensions_c1_ChoiceToString(criticalExtensions_c1_Enum value) const
{
    if(k_criticalExtensions_c1_proximityIndication_r9 == value)
        return "criticalExtensions_c1_proximityIndication_r9";
    if(k_criticalExtensions_c1_spare3 == value)
        return "criticalExtensions_c1_spare3";
    if(k_criticalExtensions_c1_spare2 == value)
        return "criticalExtensions_c1_spare2";
    if(k_criticalExtensions_c1_spare1 == value)
        return "criticalExtensions_c1_spare1";
    return "";
}

uint64_t ProximityIndication_r9::criticalExtensions_c1_NumberOfChoices() const
{
    return 4;
}

std::string ProximityIndication_r9::criticalExtensions_c1_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "c1 = " + criticalExtensions_c1_ChoiceToString(criticalExtensions_c1_internal_choice) + ":\n";
    if(criticalExtensions_c1_internal_choice == k_criticalExtensions_c1_proximityIndication_r9)
        out += criticalExtensions_c1_proximityIndication_r9.ToString(indent+1);
    return out;
}

std::string ProximityIndication_r9::criticalExtensions_c1_ToStringNoNewLines() const
{
    std::string out = "c1=" + criticalExtensions_c1_ChoiceToString(criticalExtensions_c1_internal_choice) + ",";
    if(criticalExtensions_c1_internal_choice == k_criticalExtensions_c1_proximityIndication_r9)
        out += criticalExtensions_c1_proximityIndication_r9.ToStringNoNewLines();
    return out;
}

int ProximityIndication_r9::criticalExtensions_c1_Clear()
{
    criticalExtensions_c1_present = false;
    return 0;
}

bool ProximityIndication_r9::criticalExtensions_c1_IsPresent() const
{
    return criticalExtensions_c1_present;
}

ProximityIndication_r9_IEs* ProximityIndication_r9::criticalExtensions_c1_proximityIndication_r9_Set()
{
    criticalExtensions_c1_proximityIndication_r9_present = true;
    return &criticalExtensions_c1_proximityIndication_r9;
}

int ProximityIndication_r9::criticalExtensions_c1_proximityIndication_r9_Set(ProximityIndication_r9_IEs &value)
{
    criticalExtensions_c1_proximityIndication_r9_present = true;
    criticalExtensions_c1_proximityIndication_r9 = value;
    return 0;
}

const ProximityIndication_r9_IEs& ProximityIndication_r9::criticalExtensions_c1_proximityIndication_r9_Get() const
{
    return criticalExtensions_c1_proximityIndication_r9;
}

std::string ProximityIndication_r9::criticalExtensions_c1_proximityIndication_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "proximityIndication_r9:\n";
    out += criticalExtensions_c1_proximityIndication_r9.ToString(indent+1);
    return out;
}

std::string ProximityIndication_r9::criticalExtensions_c1_proximityIndication_r9_ToStringNoNewLines() const
{
    std::string out = "proximityIndication_r9:";
    out += criticalExtensions_c1_proximityIndication_r9.ToStringNoNewLines();
    return out;
}

int ProximityIndication_r9::criticalExtensions_c1_proximityIndication_r9_Clear()
{
    criticalExtensions_c1_proximityIndication_r9_present = false;
    return 0;
}

bool ProximityIndication_r9::criticalExtensions_c1_proximityIndication_r9_IsPresent() const
{
    return criticalExtensions_c1_proximityIndication_r9_present;
}

