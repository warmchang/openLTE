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

#include "SystemInformation.h"

#include <cmath>

int SystemInformation::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != criticalExtensions_Pack(bits))
        {
            printf("SystemInformation:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int SystemInformation::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int SystemInformation::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != criticalExtensions_Unpack(bits, idx))
        {
            printf("SystemInformation:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string SystemInformation::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "SystemInformation:\n";
    out += criticalExtensions_ToString(indent+1);
    return out;
}

std::string SystemInformation::ToStringNoNewLines() const
{
    std::string out = "SystemInformation:";
    out += criticalExtensions_ToStringNoNewLines();
    return out;
}

int SystemInformation::criticalExtensions_Pack(std::vector<uint8_t> &bits)
{
    if(!criticalExtensions_present)
    {
        printf("SystemInformation::criticalExtensions_Pack() presence failure\n");
        return -1;
    }
    // Extension indicator

    // Choice
    for(uint32_t i=0; i<1; i++)
        bits.push_back((criticalExtensions_internal_choice >> (1-i-1)) & 1);

    // Fields
    if(criticalExtensions_internal_choice == k_criticalExtensions_systemInformation_r8)
    {
        if(0 != criticalExtensions_systemInformation_r8.Pack(bits))
        {
            printf("SystemInformation::criticalExtensions_systemInformation_r8 pack failure\n");
            return -1;
        }
    }
    return 0;
}

int SystemInformation::criticalExtensions_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return criticalExtensions_Unpack(bits, idx);
}

int SystemInformation::criticalExtensions_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 1) > bits.size())
    {
        printf("SystemInformation::criticalExtensions_Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<1; i++)
        packed_val |= bits[idx++] << (1-i-1);

    if((SystemInformation::criticalExtensions_Enum)packed_val > k_criticalExtensions_criticalExtensionsFuture)
    {
        printf("SystemInformation::criticalExtensions_Unpack() choice range failure\n");
        return -1;
    }
    criticalExtensions_internal_choice = (SystemInformation::criticalExtensions_Enum)packed_val;
    criticalExtensions_present = true;

    // Fields
    if(criticalExtensions_internal_choice == k_criticalExtensions_systemInformation_r8)
    {
        if(0 != criticalExtensions_systemInformation_r8.Unpack(bits, idx))
        {
            printf("SystemInformation::criticalExtensions_systemInformation_r8 unpack failure\n");
            return -1;
        }
    }
    return 0;
}

SystemInformation::criticalExtensions_Enum SystemInformation::criticalExtensions_Choice() const
{
    if(criticalExtensions_present)
        return criticalExtensions_internal_choice;
    return (SystemInformation::criticalExtensions_Enum)0;
}

int SystemInformation::criticalExtensions_SetChoice(SystemInformation::criticalExtensions_Enum choice)
{
    criticalExtensions_internal_choice = choice;
    criticalExtensions_present = true;
    return 0;
}

std::string SystemInformation::criticalExtensions_ChoiceToString(criticalExtensions_Enum value) const
{
    if(k_criticalExtensions_systemInformation_r8 == value)
        return "criticalExtensions_systemInformation_r8";
    if(k_criticalExtensions_criticalExtensionsFuture == value)
        return "criticalExtensions_criticalExtensionsFuture";
    return "";
}

uint64_t SystemInformation::criticalExtensions_NumberOfChoices() const
{
    return 2;
}

std::string SystemInformation::criticalExtensions_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "criticalExtensions = " + criticalExtensions_ChoiceToString(criticalExtensions_internal_choice) + ":\n";
    if(criticalExtensions_internal_choice == k_criticalExtensions_systemInformation_r8)
        out += criticalExtensions_systemInformation_r8.ToString(indent+1);
    return out;
}

std::string SystemInformation::criticalExtensions_ToStringNoNewLines() const
{
    std::string out = "criticalExtensions=" + criticalExtensions_ChoiceToString(criticalExtensions_internal_choice) + ",";
    if(criticalExtensions_internal_choice == k_criticalExtensions_systemInformation_r8)
        out += criticalExtensions_systemInformation_r8.ToStringNoNewLines();
    return out;
}

int SystemInformation::criticalExtensions_Clear()
{
    criticalExtensions_present = false;
    return 0;
}

bool SystemInformation::criticalExtensions_IsPresent() const
{
    return criticalExtensions_present;
}

SystemInformation_r8_IEs* SystemInformation::criticalExtensions_systemInformation_r8_Set()
{
    criticalExtensions_systemInformation_r8_present = true;
    return &criticalExtensions_systemInformation_r8;
}

int SystemInformation::criticalExtensions_systemInformation_r8_Set(SystemInformation_r8_IEs &value)
{
    criticalExtensions_systemInformation_r8_present = true;
    criticalExtensions_systemInformation_r8 = value;
    return 0;
}

const SystemInformation_r8_IEs& SystemInformation::criticalExtensions_systemInformation_r8_Get() const
{
    return criticalExtensions_systemInformation_r8;
}

std::string SystemInformation::criticalExtensions_systemInformation_r8_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "systemInformation_r8:\n";
    out += criticalExtensions_systemInformation_r8.ToString(indent+1);
    return out;
}

std::string SystemInformation::criticalExtensions_systemInformation_r8_ToStringNoNewLines() const
{
    std::string out = "systemInformation_r8:";
    out += criticalExtensions_systemInformation_r8.ToStringNoNewLines();
    return out;
}

int SystemInformation::criticalExtensions_systemInformation_r8_Clear()
{
    criticalExtensions_systemInformation_r8_present = false;
    return 0;
}

bool SystemInformation::criticalExtensions_systemInformation_r8_IsPresent() const
{
    return criticalExtensions_systemInformation_r8_present;
}

