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

#include "UEInformationResponse_r9_IEs.h"

#include <cmath>

int UEInformationResponse_r9_IEs::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(rach_Report_r9_value.IsPresent());
    bits.push_back(rlfReport_r9_IsPresent());
    bits.push_back(nonCriticalExtension_IsPresent());

    // Fields
    if(rach_Report_r9_value.IsPresent())
    {
        if(0 != rach_Report_r9_value.Pack(bits))
        {
            printf("UEInformationResponse_r9_IEs:: field pack failure\n");
            return -1;
        }
    }
    if(rlfReport_r9_IsPresent())
    {
        if(0 != rlfReport_r9.Pack(bits))
        {
            printf("UEInformationResponse_r9_IEs:: field pack failure\n");
            return -1;
        }
    }
    if(nonCriticalExtension_IsPresent())
    {
        if(0 != nonCriticalExtension.Pack(bits))
        {
            printf("UEInformationResponse_r9_IEs:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int UEInformationResponse_r9_IEs::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int UEInformationResponse_r9_IEs::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("UEInformationResponse_r9_IEs::Unpack() index out of bounds for optional indiator rach_Report_r9\n");
        return -1;
    }
    rach_Report_r9_value.SetPresence(bits[idx++]);
    if((idx + 1) > bits.size())
    {
        printf("UEInformationResponse_r9_IEs::Unpack() index out of bounds for optional indiator rlfReport_r9\n");
        return -1;
    }
    rlfReport_r9_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("UEInformationResponse_r9_IEs::Unpack() index out of bounds for optional indiator nonCriticalExtension\n");
        return -1;
    }
    nonCriticalExtension_present = bits[idx++];

    // Fields
    if(rach_Report_r9_value.IsPresent())
    {
        if(0 != rach_Report_r9_value.Unpack(bits, idx))
        {
            printf("UEInformationResponse_r9_IEs:: field unpack failure\n");
            return -1;
        }
    }
    if(rlfReport_r9_present)
    {
        if(0 != rlfReport_r9.Unpack(bits, idx))
        {
            printf("UEInformationResponse_r9_IEs:: field unpack failure\n");
            return -1;
        }
    }
    if(nonCriticalExtension_present)
    {
        if(0 != nonCriticalExtension.Unpack(bits, idx))
        {
            printf("UEInformationResponse_r9_IEs:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string UEInformationResponse_r9_IEs::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "UEInformationResponse_r9_IEs:\n";
    if(rach_Report_r9_value.IsPresent())
        out += rach_Report_r9_value.ToString(indent+1);
    if(rlfReport_r9_IsPresent())
        out += rlfReport_r9_ToString(indent+1);
    if(nonCriticalExtension_IsPresent())
        out += nonCriticalExtension_ToString(indent+1);
    return out;
}

std::string UEInformationResponse_r9_IEs::ToStringNoNewLines() const
{
    std::string out = "UEInformationResponse_r9_IEs:";
    if(rach_Report_r9_value.IsPresent())
        out += rach_Report_r9_value.ToStringNoNewLines();
    if(rlfReport_r9_IsPresent())
        out += rlfReport_r9_ToStringNoNewLines();
    if(nonCriticalExtension_IsPresent())
        out += nonCriticalExtension_ToStringNoNewLines();
    return out;
}

int UEInformationResponse_r9_IEs::rach_Report_r9::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != numberOfPreamblesSent_r9_Pack(bits))
        {
            printf("UEInformationResponse_r9_IEs::rach_Report_r9:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != contentionDetected_r9_Pack(bits))
        {
            printf("UEInformationResponse_r9_IEs::rach_Report_r9:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int UEInformationResponse_r9_IEs::rach_Report_r9::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int UEInformationResponse_r9_IEs::rach_Report_r9::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != numberOfPreamblesSent_r9_Unpack(bits, idx))
        {
            printf("UEInformationResponse_r9_IEs::rach_Report_r9:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != contentionDetected_r9_Unpack(bits, idx))
        {
            printf("UEInformationResponse_r9_IEs::rach_Report_r9:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string UEInformationResponse_r9_IEs::rach_Report_r9::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "rach_Report_r9:\n";
    out += numberOfPreamblesSent_r9_ToString(indent+1);
    out += contentionDetected_r9_ToString(indent+1);
    return out;
}

std::string UEInformationResponse_r9_IEs::rach_Report_r9::ToStringNoNewLines() const
{
    std::string out = "rach_Report_r9:";
    out += numberOfPreamblesSent_r9_ToStringNoNewLines();
    out += contentionDetected_r9_ToStringNoNewLines();
    return out;
}

int UEInformationResponse_r9_IEs::rach_Report_r9::Set()
{
    present = true;
    return 0;
}

int UEInformationResponse_r9_IEs::rach_Report_r9::SetPresence(bool is_present)
{
    present = is_present;
    return 0;
}

int UEInformationResponse_r9_IEs::rach_Report_r9::Clear()
{
    present = false;
    return 0;
}

bool UEInformationResponse_r9_IEs::rach_Report_r9::IsPresent() const
{
    return present;
}

int UEInformationResponse_r9_IEs::rach_Report_r9::numberOfPreamblesSent_r9_Pack(std::vector<uint8_t> &bits)
{
    if(!numberOfPreamblesSent_r9_present)
    {
        printf("UEInformationResponse_r9_IEs::rach_Report_r9::numberOfPreamblesSent_r9_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = numberOfPreamblesSent_r9_internal_value - (1);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (200 - 1))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int UEInformationResponse_r9_IEs::rach_Report_r9::numberOfPreamblesSent_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return numberOfPreamblesSent_r9_Unpack(bits, idx);
}

int UEInformationResponse_r9_IEs::rach_Report_r9::numberOfPreamblesSent_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (200 - 1))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("UEInformationResponse_r9_IEs::rach_Report_r9::numberOfPreamblesSent_r9_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    numberOfPreamblesSent_r9_internal_value = packed_val + 1;
    numberOfPreamblesSent_r9_present = true;
    return 0;
}

int64_t UEInformationResponse_r9_IEs::rach_Report_r9::numberOfPreamblesSent_r9_Value() const
{
    if(numberOfPreamblesSent_r9_present)
        return numberOfPreamblesSent_r9_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int UEInformationResponse_r9_IEs::rach_Report_r9::numberOfPreamblesSent_r9_SetValue(int64_t value)
{
    if(value < 1 || value > 200)
    {
        printf("UEInformationResponse_r9_IEs::rach_Report_r9::numberOfPreamblesSent_r9_SetValue() range failure\n");
        return -1;
    }
    numberOfPreamblesSent_r9_internal_value = value;
    numberOfPreamblesSent_r9_present = true;
    return 0;
}

std::string UEInformationResponse_r9_IEs::rach_Report_r9::numberOfPreamblesSent_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "numberOfPreamblesSent_r9 = " + std::to_string(numberOfPreamblesSent_r9_internal_value) + "\n";
    return out;
}

std::string UEInformationResponse_r9_IEs::rach_Report_r9::numberOfPreamblesSent_r9_ToStringNoNewLines() const
{
    std::string out = "numberOfPreamblesSent_r9=" + std::to_string(numberOfPreamblesSent_r9_internal_value) + ",";
    return out;
}

int UEInformationResponse_r9_IEs::rach_Report_r9::numberOfPreamblesSent_r9_Clear()
{
    numberOfPreamblesSent_r9_present = false;
    return 0;
}

bool UEInformationResponse_r9_IEs::rach_Report_r9::numberOfPreamblesSent_r9_IsPresent() const
{
    return numberOfPreamblesSent_r9_present;
}

int UEInformationResponse_r9_IEs::rach_Report_r9::contentionDetected_r9_Pack(std::vector<uint8_t> &bits)
{
    if(!contentionDetected_r9_present)
    {
        printf("UEInformationResponse_r9_IEs::rach_Report_r9::contentionDetected_r9_Pack() presence failure\n");
        return -1;
    }
    bits.push_back(contentionDetected_r9_internal_value);
    return 0;
}

int UEInformationResponse_r9_IEs::rach_Report_r9::contentionDetected_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return contentionDetected_r9_Unpack(bits, idx);
}

int UEInformationResponse_r9_IEs::rach_Report_r9::contentionDetected_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    if((idx + 1) > bits.size())
    {
        printf("UEInformationResponse_r9_IEs::rach_Report_r9::contentionDetected_r9_Unpack() index out of bounds\n");
        return -1;
    }
    contentionDetected_r9_internal_value = bits[idx++];
    contentionDetected_r9_present = true;
    return 0;
}

bool UEInformationResponse_r9_IEs::rach_Report_r9::contentionDetected_r9_Value() const
{
    if(contentionDetected_r9_present)
        return contentionDetected_r9_internal_value;
    return false;
}

int UEInformationResponse_r9_IEs::rach_Report_r9::contentionDetected_r9_SetValue(bool value)
{
    contentionDetected_r9_internal_value = value;
    contentionDetected_r9_present = true;
    return 0;
}

std::string UEInformationResponse_r9_IEs::rach_Report_r9::contentionDetected_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "contentionDetected_r9 = " + std::to_string(contentionDetected_r9_internal_value) + "\n";
    return out;
}

std::string UEInformationResponse_r9_IEs::rach_Report_r9::contentionDetected_r9_ToStringNoNewLines() const
{
    std::string out = "contentionDetected_r9=" + std::to_string(contentionDetected_r9_internal_value) + ",";
    return out;
}

int UEInformationResponse_r9_IEs::rach_Report_r9::contentionDetected_r9_Clear()
{
    contentionDetected_r9_present = false;
    return 0;
}

bool UEInformationResponse_r9_IEs::rach_Report_r9::contentionDetected_r9_IsPresent() const
{
    return contentionDetected_r9_present;
}

RLF_Report_r9* UEInformationResponse_r9_IEs::rlfReport_r9_Set()
{
    rlfReport_r9_present = true;
    return &rlfReport_r9;
}

int UEInformationResponse_r9_IEs::rlfReport_r9_Set(RLF_Report_r9 &value)
{
    rlfReport_r9_present = true;
    rlfReport_r9 = value;
    return 0;
}

const RLF_Report_r9& UEInformationResponse_r9_IEs::rlfReport_r9_Get() const
{
    return rlfReport_r9;
}

std::string UEInformationResponse_r9_IEs::rlfReport_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "rlfReport_r9:\n";
    out += rlfReport_r9.ToString(indent+1);
    return out;
}

std::string UEInformationResponse_r9_IEs::rlfReport_r9_ToStringNoNewLines() const
{
    std::string out = "rlfReport_r9:";
    out += rlfReport_r9.ToStringNoNewLines();
    return out;
}

int UEInformationResponse_r9_IEs::rlfReport_r9_Clear()
{
    rlfReport_r9_present = false;
    return 0;
}

bool UEInformationResponse_r9_IEs::rlfReport_r9_IsPresent() const
{
    return rlfReport_r9_present;
}

UEInformationResponse_v930_IEs* UEInformationResponse_r9_IEs::nonCriticalExtension_Set()
{
    nonCriticalExtension_present = true;
    return &nonCriticalExtension;
}

int UEInformationResponse_r9_IEs::nonCriticalExtension_Set(UEInformationResponse_v930_IEs &value)
{
    nonCriticalExtension_present = true;
    nonCriticalExtension = value;
    return 0;
}

const UEInformationResponse_v930_IEs& UEInformationResponse_r9_IEs::nonCriticalExtension_Get() const
{
    return nonCriticalExtension;
}

std::string UEInformationResponse_r9_IEs::nonCriticalExtension_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "nonCriticalExtension:\n";
    out += nonCriticalExtension.ToString(indent+1);
    return out;
}

std::string UEInformationResponse_r9_IEs::nonCriticalExtension_ToStringNoNewLines() const
{
    std::string out = "nonCriticalExtension:";
    out += nonCriticalExtension.ToStringNoNewLines();
    return out;
}

int UEInformationResponse_r9_IEs::nonCriticalExtension_Clear()
{
    nonCriticalExtension_present = false;
    return 0;
}

bool UEInformationResponse_r9_IEs::nonCriticalExtension_IsPresent() const
{
    return nonCriticalExtension_present;
}

