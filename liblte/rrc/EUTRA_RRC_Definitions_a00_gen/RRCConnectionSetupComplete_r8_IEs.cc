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

#include "RRCConnectionSetupComplete_r8_IEs.h"

#include <cmath>

int RRCConnectionSetupComplete_r8_IEs::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(registeredMME_IsPresent());
    bits.push_back(nonCriticalExtension_IsPresent());

    // Fields
    {
        if(0 != selectedPLMN_Identity_Pack(bits))
        {
            printf("RRCConnectionSetupComplete_r8_IEs:: field pack failure\n");
            return -1;
        }
    }
    if(registeredMME_IsPresent())
    {
        if(0 != registeredMME.Pack(bits))
        {
            printf("RRCConnectionSetupComplete_r8_IEs:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != dedicatedInfoNAS.Pack(bits))
        {
            printf("RRCConnectionSetupComplete_r8_IEs:: field pack failure\n");
            return -1;
        }
    }
    if(nonCriticalExtension_IsPresent())
    {
        if(0 != nonCriticalExtension.Pack(bits))
        {
            printf("RRCConnectionSetupComplete_r8_IEs:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int RRCConnectionSetupComplete_r8_IEs::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int RRCConnectionSetupComplete_r8_IEs::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("RRCConnectionSetupComplete_r8_IEs::Unpack() index out of bounds for optional indiator registeredMME\n");
        return -1;
    }
    registeredMME_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("RRCConnectionSetupComplete_r8_IEs::Unpack() index out of bounds for optional indiator nonCriticalExtension\n");
        return -1;
    }
    nonCriticalExtension_present = bits[idx++];

    // Fields
    {
        if(0 != selectedPLMN_Identity_Unpack(bits, idx))
        {
            printf("RRCConnectionSetupComplete_r8_IEs:: field unpack failure\n");
            return -1;
        }
    }
    if(registeredMME_present)
    {
        if(0 != registeredMME.Unpack(bits, idx))
        {
            printf("RRCConnectionSetupComplete_r8_IEs:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != dedicatedInfoNAS.Unpack(bits, idx))
        {
            printf("RRCConnectionSetupComplete_r8_IEs:: field unpack failure\n");
            return -1;
        }
    }
    if(nonCriticalExtension_present)
    {
        if(0 != nonCriticalExtension.Unpack(bits, idx))
        {
            printf("RRCConnectionSetupComplete_r8_IEs:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string RRCConnectionSetupComplete_r8_IEs::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "RRCConnectionSetupComplete_r8_IEs:\n";
    out += selectedPLMN_Identity_ToString(indent+1);
    if(registeredMME_IsPresent())
        out += registeredMME_ToString(indent+1);
    out += dedicatedInfoNAS_ToString(indent+1);
    if(nonCriticalExtension_IsPresent())
        out += nonCriticalExtension_ToString(indent+1);
    return out;
}

std::string RRCConnectionSetupComplete_r8_IEs::ToStringNoNewLines() const
{
    std::string out = "RRCConnectionSetupComplete_r8_IEs:";
    out += selectedPLMN_Identity_ToStringNoNewLines();
    if(registeredMME_IsPresent())
        out += registeredMME_ToStringNoNewLines();
    out += dedicatedInfoNAS_ToStringNoNewLines();
    if(nonCriticalExtension_IsPresent())
        out += nonCriticalExtension_ToStringNoNewLines();
    return out;
}

int RRCConnectionSetupComplete_r8_IEs::selectedPLMN_Identity_Pack(std::vector<uint8_t> &bits)
{
    if(!selectedPLMN_Identity_present)
    {
        printf("RRCConnectionSetupComplete_r8_IEs::selectedPLMN_Identity_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = selectedPLMN_Identity_internal_value - (1);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (6 - 1))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int RRCConnectionSetupComplete_r8_IEs::selectedPLMN_Identity_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return selectedPLMN_Identity_Unpack(bits, idx);
}

int RRCConnectionSetupComplete_r8_IEs::selectedPLMN_Identity_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (6 - 1))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("RRCConnectionSetupComplete_r8_IEs::selectedPLMN_Identity_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    selectedPLMN_Identity_internal_value = packed_val + 1;
    selectedPLMN_Identity_present = true;
    return 0;
}

int64_t RRCConnectionSetupComplete_r8_IEs::selectedPLMN_Identity_Value() const
{
    if(selectedPLMN_Identity_present)
        return selectedPLMN_Identity_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int RRCConnectionSetupComplete_r8_IEs::selectedPLMN_Identity_SetValue(int64_t value)
{
    if(value < 1 || value > 6)
    {
        printf("RRCConnectionSetupComplete_r8_IEs::selectedPLMN_Identity_SetValue() range failure\n");
        return -1;
    }
    selectedPLMN_Identity_internal_value = value;
    selectedPLMN_Identity_present = true;
    return 0;
}

std::string RRCConnectionSetupComplete_r8_IEs::selectedPLMN_Identity_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "selectedPLMN_Identity = " + std::to_string(selectedPLMN_Identity_internal_value) + "\n";
    return out;
}

std::string RRCConnectionSetupComplete_r8_IEs::selectedPLMN_Identity_ToStringNoNewLines() const
{
    std::string out = "selectedPLMN_Identity=" + std::to_string(selectedPLMN_Identity_internal_value) + ",";
    return out;
}

int RRCConnectionSetupComplete_r8_IEs::selectedPLMN_Identity_Clear()
{
    selectedPLMN_Identity_present = false;
    return 0;
}

bool RRCConnectionSetupComplete_r8_IEs::selectedPLMN_Identity_IsPresent() const
{
    return selectedPLMN_Identity_present;
}

RegisteredMME* RRCConnectionSetupComplete_r8_IEs::registeredMME_Set()
{
    registeredMME_present = true;
    return &registeredMME;
}

int RRCConnectionSetupComplete_r8_IEs::registeredMME_Set(RegisteredMME &value)
{
    registeredMME_present = true;
    registeredMME = value;
    return 0;
}

const RegisteredMME& RRCConnectionSetupComplete_r8_IEs::registeredMME_Get() const
{
    return registeredMME;
}

std::string RRCConnectionSetupComplete_r8_IEs::registeredMME_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "registeredMME:\n";
    out += registeredMME.ToString(indent+1);
    return out;
}

std::string RRCConnectionSetupComplete_r8_IEs::registeredMME_ToStringNoNewLines() const
{
    std::string out = "registeredMME:";
    out += registeredMME.ToStringNoNewLines();
    return out;
}

int RRCConnectionSetupComplete_r8_IEs::registeredMME_Clear()
{
    registeredMME_present = false;
    return 0;
}

bool RRCConnectionSetupComplete_r8_IEs::registeredMME_IsPresent() const
{
    return registeredMME_present;
}

DedicatedInfoNAS* RRCConnectionSetupComplete_r8_IEs::dedicatedInfoNAS_Set()
{
    dedicatedInfoNAS_present = true;
    return &dedicatedInfoNAS;
}

int RRCConnectionSetupComplete_r8_IEs::dedicatedInfoNAS_Set(DedicatedInfoNAS &value)
{
    dedicatedInfoNAS_present = true;
    dedicatedInfoNAS = value;
    return 0;
}

const DedicatedInfoNAS& RRCConnectionSetupComplete_r8_IEs::dedicatedInfoNAS_Get() const
{
    return dedicatedInfoNAS;
}

std::string RRCConnectionSetupComplete_r8_IEs::dedicatedInfoNAS_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "dedicatedInfoNAS:\n";
    out += dedicatedInfoNAS.ToString(indent+1);
    return out;
}

std::string RRCConnectionSetupComplete_r8_IEs::dedicatedInfoNAS_ToStringNoNewLines() const
{
    std::string out = "dedicatedInfoNAS:";
    out += dedicatedInfoNAS.ToStringNoNewLines();
    return out;
}

int RRCConnectionSetupComplete_r8_IEs::dedicatedInfoNAS_Clear()
{
    dedicatedInfoNAS_present = false;
    return 0;
}

bool RRCConnectionSetupComplete_r8_IEs::dedicatedInfoNAS_IsPresent() const
{
    return dedicatedInfoNAS_present;
}

RRCConnectionSetupComplete_v8a0_IEs* RRCConnectionSetupComplete_r8_IEs::nonCriticalExtension_Set()
{
    nonCriticalExtension_present = true;
    return &nonCriticalExtension;
}

int RRCConnectionSetupComplete_r8_IEs::nonCriticalExtension_Set(RRCConnectionSetupComplete_v8a0_IEs &value)
{
    nonCriticalExtension_present = true;
    nonCriticalExtension = value;
    return 0;
}

const RRCConnectionSetupComplete_v8a0_IEs& RRCConnectionSetupComplete_r8_IEs::nonCriticalExtension_Get() const
{
    return nonCriticalExtension;
}

std::string RRCConnectionSetupComplete_r8_IEs::nonCriticalExtension_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "nonCriticalExtension:\n";
    out += nonCriticalExtension.ToString(indent+1);
    return out;
}

std::string RRCConnectionSetupComplete_r8_IEs::nonCriticalExtension_ToStringNoNewLines() const
{
    std::string out = "nonCriticalExtension:";
    out += nonCriticalExtension.ToStringNoNewLines();
    return out;
}

int RRCConnectionSetupComplete_r8_IEs::nonCriticalExtension_Clear()
{
    nonCriticalExtension_present = false;
    return 0;
}

bool RRCConnectionSetupComplete_r8_IEs::nonCriticalExtension_IsPresent() const
{
    return nonCriticalExtension_present;
}

