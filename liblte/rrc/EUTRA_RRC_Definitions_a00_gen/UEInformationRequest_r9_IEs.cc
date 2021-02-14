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

#include "UEInformationRequest_r9_IEs.h"

#include <cmath>

int UEInformationRequest_r9_IEs::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(nonCriticalExtension_IsPresent());

    // Fields
    {
        if(0 != rach_ReportReq_r9_Pack(bits))
        {
            printf("UEInformationRequest_r9_IEs:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != rlf_ReportReq_r9_Pack(bits))
        {
            printf("UEInformationRequest_r9_IEs:: field pack failure\n");
            return -1;
        }
    }
    if(nonCriticalExtension_IsPresent())
    {
        if(0 != nonCriticalExtension.Pack(bits))
        {
            printf("UEInformationRequest_r9_IEs:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int UEInformationRequest_r9_IEs::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int UEInformationRequest_r9_IEs::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("UEInformationRequest_r9_IEs::Unpack() index out of bounds for optional indiator nonCriticalExtension\n");
        return -1;
    }
    nonCriticalExtension_present = bits[idx++];

    // Fields
    {
        if(0 != rach_ReportReq_r9_Unpack(bits, idx))
        {
            printf("UEInformationRequest_r9_IEs:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != rlf_ReportReq_r9_Unpack(bits, idx))
        {
            printf("UEInformationRequest_r9_IEs:: field unpack failure\n");
            return -1;
        }
    }
    if(nonCriticalExtension_present)
    {
        if(0 != nonCriticalExtension.Unpack(bits, idx))
        {
            printf("UEInformationRequest_r9_IEs:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string UEInformationRequest_r9_IEs::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "UEInformationRequest_r9_IEs:\n";
    out += rach_ReportReq_r9_ToString(indent+1);
    out += rlf_ReportReq_r9_ToString(indent+1);
    if(nonCriticalExtension_IsPresent())
        out += nonCriticalExtension_ToString(indent+1);
    return out;
}

std::string UEInformationRequest_r9_IEs::ToStringNoNewLines() const
{
    std::string out = "UEInformationRequest_r9_IEs:";
    out += rach_ReportReq_r9_ToStringNoNewLines();
    out += rlf_ReportReq_r9_ToStringNoNewLines();
    if(nonCriticalExtension_IsPresent())
        out += nonCriticalExtension_ToStringNoNewLines();
    return out;
}

int UEInformationRequest_r9_IEs::rach_ReportReq_r9_Pack(std::vector<uint8_t> &bits)
{
    if(!rach_ReportReq_r9_present)
    {
        printf("UEInformationRequest_r9_IEs::rach_ReportReq_r9_Pack() presence failure\n");
        return -1;
    }
    bits.push_back(rach_ReportReq_r9_internal_value);
    return 0;
}

int UEInformationRequest_r9_IEs::rach_ReportReq_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return rach_ReportReq_r9_Unpack(bits, idx);
}

int UEInformationRequest_r9_IEs::rach_ReportReq_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    if((idx + 1) > bits.size())
    {
        printf("UEInformationRequest_r9_IEs::rach_ReportReq_r9_Unpack() index out of bounds\n");
        return -1;
    }
    rach_ReportReq_r9_internal_value = bits[idx++];
    rach_ReportReq_r9_present = true;
    return 0;
}

bool UEInformationRequest_r9_IEs::rach_ReportReq_r9_Value() const
{
    if(rach_ReportReq_r9_present)
        return rach_ReportReq_r9_internal_value;
    return false;
}

int UEInformationRequest_r9_IEs::rach_ReportReq_r9_SetValue(bool value)
{
    rach_ReportReq_r9_internal_value = value;
    rach_ReportReq_r9_present = true;
    return 0;
}

std::string UEInformationRequest_r9_IEs::rach_ReportReq_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "rach_ReportReq_r9 = " + std::to_string(rach_ReportReq_r9_internal_value) + "\n";
    return out;
}

std::string UEInformationRequest_r9_IEs::rach_ReportReq_r9_ToStringNoNewLines() const
{
    std::string out = "rach_ReportReq_r9=" + std::to_string(rach_ReportReq_r9_internal_value) + ",";
    return out;
}

int UEInformationRequest_r9_IEs::rach_ReportReq_r9_Clear()
{
    rach_ReportReq_r9_present = false;
    return 0;
}

bool UEInformationRequest_r9_IEs::rach_ReportReq_r9_IsPresent() const
{
    return rach_ReportReq_r9_present;
}

int UEInformationRequest_r9_IEs::rlf_ReportReq_r9_Pack(std::vector<uint8_t> &bits)
{
    if(!rlf_ReportReq_r9_present)
    {
        printf("UEInformationRequest_r9_IEs::rlf_ReportReq_r9_Pack() presence failure\n");
        return -1;
    }
    bits.push_back(rlf_ReportReq_r9_internal_value);
    return 0;
}

int UEInformationRequest_r9_IEs::rlf_ReportReq_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return rlf_ReportReq_r9_Unpack(bits, idx);
}

int UEInformationRequest_r9_IEs::rlf_ReportReq_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    if((idx + 1) > bits.size())
    {
        printf("UEInformationRequest_r9_IEs::rlf_ReportReq_r9_Unpack() index out of bounds\n");
        return -1;
    }
    rlf_ReportReq_r9_internal_value = bits[idx++];
    rlf_ReportReq_r9_present = true;
    return 0;
}

bool UEInformationRequest_r9_IEs::rlf_ReportReq_r9_Value() const
{
    if(rlf_ReportReq_r9_present)
        return rlf_ReportReq_r9_internal_value;
    return false;
}

int UEInformationRequest_r9_IEs::rlf_ReportReq_r9_SetValue(bool value)
{
    rlf_ReportReq_r9_internal_value = value;
    rlf_ReportReq_r9_present = true;
    return 0;
}

std::string UEInformationRequest_r9_IEs::rlf_ReportReq_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "rlf_ReportReq_r9 = " + std::to_string(rlf_ReportReq_r9_internal_value) + "\n";
    return out;
}

std::string UEInformationRequest_r9_IEs::rlf_ReportReq_r9_ToStringNoNewLines() const
{
    std::string out = "rlf_ReportReq_r9=" + std::to_string(rlf_ReportReq_r9_internal_value) + ",";
    return out;
}

int UEInformationRequest_r9_IEs::rlf_ReportReq_r9_Clear()
{
    rlf_ReportReq_r9_present = false;
    return 0;
}

bool UEInformationRequest_r9_IEs::rlf_ReportReq_r9_IsPresent() const
{
    return rlf_ReportReq_r9_present;
}

UEInformationRequest_v930_IEs* UEInformationRequest_r9_IEs::nonCriticalExtension_Set()
{
    nonCriticalExtension_present = true;
    return &nonCriticalExtension;
}

int UEInformationRequest_r9_IEs::nonCriticalExtension_Set(UEInformationRequest_v930_IEs &value)
{
    nonCriticalExtension_present = true;
    nonCriticalExtension = value;
    return 0;
}

const UEInformationRequest_v930_IEs& UEInformationRequest_r9_IEs::nonCriticalExtension_Get() const
{
    return nonCriticalExtension;
}

std::string UEInformationRequest_r9_IEs::nonCriticalExtension_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "nonCriticalExtension:\n";
    out += nonCriticalExtension.ToString(indent+1);
    return out;
}

std::string UEInformationRequest_r9_IEs::nonCriticalExtension_ToStringNoNewLines() const
{
    std::string out = "nonCriticalExtension:";
    out += nonCriticalExtension.ToStringNoNewLines();
    return out;
}

int UEInformationRequest_r9_IEs::nonCriticalExtension_Clear()
{
    nonCriticalExtension_present = false;
    return 0;
}

bool UEInformationRequest_r9_IEs::nonCriticalExtension_IsPresent() const
{
    return nonCriticalExtension_present;
}

