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

#include "HandoverFromEUTRAPreparationRequest_v920_IEs.h"

#include <cmath>

int HandoverFromEUTRAPreparationRequest_v920_IEs::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(concurrPrepCDMA2000_HRPD_r9_IsPresent());
    bits.push_back(nonCriticalExtension_IsPresent());

    // Fields
    if(concurrPrepCDMA2000_HRPD_r9_IsPresent())
    {
        if(0 != concurrPrepCDMA2000_HRPD_r9_Pack(bits))
        {
            printf("HandoverFromEUTRAPreparationRequest_v920_IEs:: field pack failure\n");
            return -1;
        }
    }
    if(nonCriticalExtension_IsPresent())
    {
        if(0 != nonCriticalExtension.Pack(bits))
        {
            printf("HandoverFromEUTRAPreparationRequest_v920_IEs:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int HandoverFromEUTRAPreparationRequest_v920_IEs::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int HandoverFromEUTRAPreparationRequest_v920_IEs::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("HandoverFromEUTRAPreparationRequest_v920_IEs::Unpack() index out of bounds for optional indiator concurrPrepCDMA2000_HRPD_r9\n");
        return -1;
    }
    concurrPrepCDMA2000_HRPD_r9_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("HandoverFromEUTRAPreparationRequest_v920_IEs::Unpack() index out of bounds for optional indiator nonCriticalExtension\n");
        return -1;
    }
    nonCriticalExtension_present = bits[idx++];

    // Fields
    if(concurrPrepCDMA2000_HRPD_r9_present)
    {
        if(0 != concurrPrepCDMA2000_HRPD_r9_Unpack(bits, idx))
        {
            printf("HandoverFromEUTRAPreparationRequest_v920_IEs:: field unpack failure\n");
            return -1;
        }
    }
    if(nonCriticalExtension_present)
    {
        if(0 != nonCriticalExtension.Unpack(bits, idx))
        {
            printf("HandoverFromEUTRAPreparationRequest_v920_IEs:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string HandoverFromEUTRAPreparationRequest_v920_IEs::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "HandoverFromEUTRAPreparationRequest_v920_IEs:\n";
    if(concurrPrepCDMA2000_HRPD_r9_IsPresent())
        out += concurrPrepCDMA2000_HRPD_r9_ToString(indent+1);
    if(nonCriticalExtension_IsPresent())
        out += nonCriticalExtension_ToString(indent+1);
    return out;
}

std::string HandoverFromEUTRAPreparationRequest_v920_IEs::ToStringNoNewLines() const
{
    std::string out = "HandoverFromEUTRAPreparationRequest_v920_IEs:";
    if(concurrPrepCDMA2000_HRPD_r9_IsPresent())
        out += concurrPrepCDMA2000_HRPD_r9_ToStringNoNewLines();
    if(nonCriticalExtension_IsPresent())
        out += nonCriticalExtension_ToStringNoNewLines();
    return out;
}

int HandoverFromEUTRAPreparationRequest_v920_IEs::concurrPrepCDMA2000_HRPD_r9_Pack(std::vector<uint8_t> &bits)
{
    bits.push_back(concurrPrepCDMA2000_HRPD_r9_internal_value);
    return 0;
}

int HandoverFromEUTRAPreparationRequest_v920_IEs::concurrPrepCDMA2000_HRPD_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return concurrPrepCDMA2000_HRPD_r9_Unpack(bits, idx);
}

int HandoverFromEUTRAPreparationRequest_v920_IEs::concurrPrepCDMA2000_HRPD_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    if((idx + 1) > bits.size())
    {
        printf("HandoverFromEUTRAPreparationRequest_v920_IEs::concurrPrepCDMA2000_HRPD_r9_Unpack() index out of bounds\n");
        return -1;
    }
    concurrPrepCDMA2000_HRPD_r9_internal_value = bits[idx++];
    concurrPrepCDMA2000_HRPD_r9_present = true;
    return 0;
}

bool HandoverFromEUTRAPreparationRequest_v920_IEs::concurrPrepCDMA2000_HRPD_r9_Value() const
{
    if(concurrPrepCDMA2000_HRPD_r9_present)
        return concurrPrepCDMA2000_HRPD_r9_internal_value;
    return false;
}

int HandoverFromEUTRAPreparationRequest_v920_IEs::concurrPrepCDMA2000_HRPD_r9_SetValue(bool value)
{
    concurrPrepCDMA2000_HRPD_r9_internal_value = value;
    concurrPrepCDMA2000_HRPD_r9_present = true;
    return 0;
}

std::string HandoverFromEUTRAPreparationRequest_v920_IEs::concurrPrepCDMA2000_HRPD_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "concurrPrepCDMA2000_HRPD_r9 = " + std::to_string(concurrPrepCDMA2000_HRPD_r9_internal_value) + "\n";
    return out;
}

std::string HandoverFromEUTRAPreparationRequest_v920_IEs::concurrPrepCDMA2000_HRPD_r9_ToStringNoNewLines() const
{
    std::string out = "concurrPrepCDMA2000_HRPD_r9=" + std::to_string(concurrPrepCDMA2000_HRPD_r9_internal_value) + ",";
    return out;
}

int HandoverFromEUTRAPreparationRequest_v920_IEs::concurrPrepCDMA2000_HRPD_r9_Clear()
{
    concurrPrepCDMA2000_HRPD_r9_present = false;
    return 0;
}

bool HandoverFromEUTRAPreparationRequest_v920_IEs::concurrPrepCDMA2000_HRPD_r9_IsPresent() const
{
    return concurrPrepCDMA2000_HRPD_r9_present;
}

HandoverFromEUTRAPreparationRequest_r10_IEs* HandoverFromEUTRAPreparationRequest_v920_IEs::nonCriticalExtension_Set()
{
    nonCriticalExtension_present = true;
    return &nonCriticalExtension;
}

int HandoverFromEUTRAPreparationRequest_v920_IEs::nonCriticalExtension_Set(HandoverFromEUTRAPreparationRequest_r10_IEs &value)
{
    nonCriticalExtension_present = true;
    nonCriticalExtension = value;
    return 0;
}

const HandoverFromEUTRAPreparationRequest_r10_IEs& HandoverFromEUTRAPreparationRequest_v920_IEs::nonCriticalExtension_Get() const
{
    return nonCriticalExtension;
}

std::string HandoverFromEUTRAPreparationRequest_v920_IEs::nonCriticalExtension_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "nonCriticalExtension:\n";
    out += nonCriticalExtension.ToString(indent+1);
    return out;
}

std::string HandoverFromEUTRAPreparationRequest_v920_IEs::nonCriticalExtension_ToStringNoNewLines() const
{
    std::string out = "nonCriticalExtension:";
    out += nonCriticalExtension.ToStringNoNewLines();
    return out;
}

int HandoverFromEUTRAPreparationRequest_v920_IEs::nonCriticalExtension_Clear()
{
    nonCriticalExtension_present = false;
    return 0;
}

bool HandoverFromEUTRAPreparationRequest_v920_IEs::nonCriticalExtension_IsPresent() const
{
    return nonCriticalExtension_present;
}

