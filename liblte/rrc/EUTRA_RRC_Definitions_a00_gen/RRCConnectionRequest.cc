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

#include "RRCConnectionRequest.h"

#include <cmath>

int RRCConnectionRequest::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != criticalExtensions_Pack(bits))
        {
            printf("RRCConnectionRequest:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int RRCConnectionRequest::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int RRCConnectionRequest::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != criticalExtensions_Unpack(bits, idx))
        {
            printf("RRCConnectionRequest:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string RRCConnectionRequest::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "RRCConnectionRequest:\n";
    out += criticalExtensions_ToString(indent+1);
    return out;
}

std::string RRCConnectionRequest::ToStringNoNewLines() const
{
    std::string out = "RRCConnectionRequest:";
    out += criticalExtensions_ToStringNoNewLines();
    return out;
}

int RRCConnectionRequest::criticalExtensions_Pack(std::vector<uint8_t> &bits)
{
    if(!criticalExtensions_present)
    {
        printf("RRCConnectionRequest::criticalExtensions_Pack() presence failure\n");
        return -1;
    }
    // Extension indicator

    // Choice
    for(uint32_t i=0; i<1; i++)
        bits.push_back((criticalExtensions_internal_choice >> (1-i-1)) & 1);

    // Fields
    if(criticalExtensions_internal_choice == k_criticalExtensions_rrcConnectionRequest_r8)
    {
        if(0 != criticalExtensions_rrcConnectionRequest_r8.Pack(bits))
        {
            printf("RRCConnectionRequest::criticalExtensions_rrcConnectionRequest_r8 pack failure\n");
            return -1;
        }
    }
    return 0;
}

int RRCConnectionRequest::criticalExtensions_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return criticalExtensions_Unpack(bits, idx);
}

int RRCConnectionRequest::criticalExtensions_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 1) > bits.size())
    {
        printf("RRCConnectionRequest::criticalExtensions_Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<1; i++)
        packed_val |= bits[idx++] << (1-i-1);

    if((RRCConnectionRequest::criticalExtensions_Enum)packed_val > k_criticalExtensions_criticalExtensionsFuture)
    {
        printf("RRCConnectionRequest::criticalExtensions_Unpack() choice range failure\n");
        return -1;
    }
    criticalExtensions_internal_choice = (RRCConnectionRequest::criticalExtensions_Enum)packed_val;
    criticalExtensions_present = true;

    // Fields
    if(criticalExtensions_internal_choice == k_criticalExtensions_rrcConnectionRequest_r8)
    {
        if(0 != criticalExtensions_rrcConnectionRequest_r8.Unpack(bits, idx))
        {
            printf("RRCConnectionRequest::criticalExtensions_rrcConnectionRequest_r8 unpack failure\n");
            return -1;
        }
    }
    return 0;
}

RRCConnectionRequest::criticalExtensions_Enum RRCConnectionRequest::criticalExtensions_Choice() const
{
    if(criticalExtensions_present)
        return criticalExtensions_internal_choice;
    return (RRCConnectionRequest::criticalExtensions_Enum)0;
}

int RRCConnectionRequest::criticalExtensions_SetChoice(RRCConnectionRequest::criticalExtensions_Enum choice)
{
    criticalExtensions_internal_choice = choice;
    criticalExtensions_present = true;
    return 0;
}

std::string RRCConnectionRequest::criticalExtensions_ChoiceToString(criticalExtensions_Enum value) const
{
    if(k_criticalExtensions_rrcConnectionRequest_r8 == value)
        return "criticalExtensions_rrcConnectionRequest_r8";
    if(k_criticalExtensions_criticalExtensionsFuture == value)
        return "criticalExtensions_criticalExtensionsFuture";
    return "";
}

uint64_t RRCConnectionRequest::criticalExtensions_NumberOfChoices() const
{
    return 2;
}

std::string RRCConnectionRequest::criticalExtensions_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "criticalExtensions = " + criticalExtensions_ChoiceToString(criticalExtensions_internal_choice) + ":\n";
    if(criticalExtensions_internal_choice == k_criticalExtensions_rrcConnectionRequest_r8)
        out += criticalExtensions_rrcConnectionRequest_r8.ToString(indent+1);
    return out;
}

std::string RRCConnectionRequest::criticalExtensions_ToStringNoNewLines() const
{
    std::string out = "criticalExtensions=" + criticalExtensions_ChoiceToString(criticalExtensions_internal_choice) + ",";
    if(criticalExtensions_internal_choice == k_criticalExtensions_rrcConnectionRequest_r8)
        out += criticalExtensions_rrcConnectionRequest_r8.ToStringNoNewLines();
    return out;
}

int RRCConnectionRequest::criticalExtensions_Clear()
{
    criticalExtensions_present = false;
    return 0;
}

bool RRCConnectionRequest::criticalExtensions_IsPresent() const
{
    return criticalExtensions_present;
}

RRCConnectionRequest_r8_IEs* RRCConnectionRequest::criticalExtensions_rrcConnectionRequest_r8_Set()
{
    criticalExtensions_rrcConnectionRequest_r8_present = true;
    return &criticalExtensions_rrcConnectionRequest_r8;
}

int RRCConnectionRequest::criticalExtensions_rrcConnectionRequest_r8_Set(RRCConnectionRequest_r8_IEs &value)
{
    criticalExtensions_rrcConnectionRequest_r8_present = true;
    criticalExtensions_rrcConnectionRequest_r8 = value;
    return 0;
}

const RRCConnectionRequest_r8_IEs& RRCConnectionRequest::criticalExtensions_rrcConnectionRequest_r8_Get() const
{
    return criticalExtensions_rrcConnectionRequest_r8;
}

std::string RRCConnectionRequest::criticalExtensions_rrcConnectionRequest_r8_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "rrcConnectionRequest_r8:\n";
    out += criticalExtensions_rrcConnectionRequest_r8.ToString(indent+1);
    return out;
}

std::string RRCConnectionRequest::criticalExtensions_rrcConnectionRequest_r8_ToStringNoNewLines() const
{
    std::string out = "rrcConnectionRequest_r8:";
    out += criticalExtensions_rrcConnectionRequest_r8.ToStringNoNewLines();
    return out;
}

int RRCConnectionRequest::criticalExtensions_rrcConnectionRequest_r8_Clear()
{
    criticalExtensions_rrcConnectionRequest_r8_present = false;
    return 0;
}

bool RRCConnectionRequest::criticalExtensions_rrcConnectionRequest_r8_IsPresent() const
{
    return criticalExtensions_rrcConnectionRequest_r8_present;
}

