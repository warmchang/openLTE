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

#include "DLInformationTransfer_r8_IEs.h"

#include <cmath>

int DLInformationTransfer_r8_IEs::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(nonCriticalExtension_IsPresent());

    // Fields
    {
        if(0 != dedicatedInfoType_Pack(bits))
        {
            printf("DLInformationTransfer_r8_IEs:: field pack failure\n");
            return -1;
        }
    }
    if(nonCriticalExtension_IsPresent())
    {
        if(0 != nonCriticalExtension.Pack(bits))
        {
            printf("DLInformationTransfer_r8_IEs:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int DLInformationTransfer_r8_IEs::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int DLInformationTransfer_r8_IEs::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("DLInformationTransfer_r8_IEs::Unpack() index out of bounds for optional indiator nonCriticalExtension\n");
        return -1;
    }
    nonCriticalExtension_present = bits[idx++];

    // Fields
    {
        if(0 != dedicatedInfoType_Unpack(bits, idx))
        {
            printf("DLInformationTransfer_r8_IEs:: field unpack failure\n");
            return -1;
        }
    }
    if(nonCriticalExtension_present)
    {
        if(0 != nonCriticalExtension.Unpack(bits, idx))
        {
            printf("DLInformationTransfer_r8_IEs:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string DLInformationTransfer_r8_IEs::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "DLInformationTransfer_r8_IEs:\n";
    out += dedicatedInfoType_ToString(indent+1);
    if(nonCriticalExtension_IsPresent())
        out += nonCriticalExtension_ToString(indent+1);
    return out;
}

std::string DLInformationTransfer_r8_IEs::ToStringNoNewLines() const
{
    std::string out = "DLInformationTransfer_r8_IEs:";
    out += dedicatedInfoType_ToStringNoNewLines();
    if(nonCriticalExtension_IsPresent())
        out += nonCriticalExtension_ToStringNoNewLines();
    return out;
}

int DLInformationTransfer_r8_IEs::dedicatedInfoType_Pack(std::vector<uint8_t> &bits)
{
    if(!dedicatedInfoType_present)
    {
        printf("DLInformationTransfer_r8_IEs::dedicatedInfoType_Pack() presence failure\n");
        return -1;
    }
    // Extension indicator

    // Choice
    for(uint32_t i=0; i<2; i++)
        bits.push_back((dedicatedInfoType_internal_choice >> (2-i-1)) & 1);

    // Fields
    if(dedicatedInfoType_internal_choice == k_dedicatedInfoType_dedicatedInfoNAS)
    {
        if(0 != dedicatedInfoType_dedicatedInfoNAS.Pack(bits))
        {
            printf("DLInformationTransfer_r8_IEs::dedicatedInfoType_dedicatedInfoNAS pack failure\n");
            return -1;
        }
    }
    if(dedicatedInfoType_internal_choice == k_dedicatedInfoType_dedicatedInfoCDMA2000_1XRTT)
    {
        if(0 != dedicatedInfoType_dedicatedInfoCDMA2000_1XRTT.Pack(bits))
        {
            printf("DLInformationTransfer_r8_IEs::dedicatedInfoType_dedicatedInfoCDMA2000_1XRTT pack failure\n");
            return -1;
        }
    }
    if(dedicatedInfoType_internal_choice == k_dedicatedInfoType_dedicatedInfoCDMA2000_HRPD)
    {
        if(0 != dedicatedInfoType_dedicatedInfoCDMA2000_HRPD.Pack(bits))
        {
            printf("DLInformationTransfer_r8_IEs::dedicatedInfoType_dedicatedInfoCDMA2000_HRPD pack failure\n");
            return -1;
        }
    }
    return 0;
}

int DLInformationTransfer_r8_IEs::dedicatedInfoType_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return dedicatedInfoType_Unpack(bits, idx);
}

int DLInformationTransfer_r8_IEs::dedicatedInfoType_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 2) > bits.size())
    {
        printf("DLInformationTransfer_r8_IEs::dedicatedInfoType_Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<2; i++)
        packed_val |= bits[idx++] << (2-i-1);

    if((DLInformationTransfer_r8_IEs::dedicatedInfoType_Enum)packed_val > k_dedicatedInfoType_dedicatedInfoCDMA2000_HRPD)
    {
        printf("DLInformationTransfer_r8_IEs::dedicatedInfoType_Unpack() choice range failure\n");
        return -1;
    }
    dedicatedInfoType_internal_choice = (DLInformationTransfer_r8_IEs::dedicatedInfoType_Enum)packed_val;
    dedicatedInfoType_present = true;

    // Fields
    if(dedicatedInfoType_internal_choice == k_dedicatedInfoType_dedicatedInfoNAS)
    {
        if(0 != dedicatedInfoType_dedicatedInfoNAS.Unpack(bits, idx))
        {
            printf("DLInformationTransfer_r8_IEs::dedicatedInfoType_dedicatedInfoNAS unpack failure\n");
            return -1;
        }
    }
    if(dedicatedInfoType_internal_choice == k_dedicatedInfoType_dedicatedInfoCDMA2000_1XRTT)
    {
        if(0 != dedicatedInfoType_dedicatedInfoCDMA2000_1XRTT.Unpack(bits, idx))
        {
            printf("DLInformationTransfer_r8_IEs::dedicatedInfoType_dedicatedInfoCDMA2000_1XRTT unpack failure\n");
            return -1;
        }
    }
    if(dedicatedInfoType_internal_choice == k_dedicatedInfoType_dedicatedInfoCDMA2000_HRPD)
    {
        if(0 != dedicatedInfoType_dedicatedInfoCDMA2000_HRPD.Unpack(bits, idx))
        {
            printf("DLInformationTransfer_r8_IEs::dedicatedInfoType_dedicatedInfoCDMA2000_HRPD unpack failure\n");
            return -1;
        }
    }
    return 0;
}

DLInformationTransfer_r8_IEs::dedicatedInfoType_Enum DLInformationTransfer_r8_IEs::dedicatedInfoType_Choice() const
{
    if(dedicatedInfoType_present)
        return dedicatedInfoType_internal_choice;
    return (DLInformationTransfer_r8_IEs::dedicatedInfoType_Enum)0;
}

int DLInformationTransfer_r8_IEs::dedicatedInfoType_SetChoice(DLInformationTransfer_r8_IEs::dedicatedInfoType_Enum choice)
{
    dedicatedInfoType_internal_choice = choice;
    dedicatedInfoType_present = true;
    return 0;
}

std::string DLInformationTransfer_r8_IEs::dedicatedInfoType_ChoiceToString(dedicatedInfoType_Enum value) const
{
    if(k_dedicatedInfoType_dedicatedInfoNAS == value)
        return "dedicatedInfoType_dedicatedInfoNAS";
    if(k_dedicatedInfoType_dedicatedInfoCDMA2000_1XRTT == value)
        return "dedicatedInfoType_dedicatedInfoCDMA2000_1XRTT";
    if(k_dedicatedInfoType_dedicatedInfoCDMA2000_HRPD == value)
        return "dedicatedInfoType_dedicatedInfoCDMA2000_HRPD";
    return "";
}

uint64_t DLInformationTransfer_r8_IEs::dedicatedInfoType_NumberOfChoices() const
{
    return 3;
}

std::string DLInformationTransfer_r8_IEs::dedicatedInfoType_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "dedicatedInfoType = " + dedicatedInfoType_ChoiceToString(dedicatedInfoType_internal_choice) + ":\n";
    if(dedicatedInfoType_internal_choice == k_dedicatedInfoType_dedicatedInfoNAS)
        out += dedicatedInfoType_dedicatedInfoNAS.ToString(indent+1);
    if(dedicatedInfoType_internal_choice == k_dedicatedInfoType_dedicatedInfoCDMA2000_1XRTT)
        out += dedicatedInfoType_dedicatedInfoCDMA2000_1XRTT.ToString(indent+1);
    if(dedicatedInfoType_internal_choice == k_dedicatedInfoType_dedicatedInfoCDMA2000_HRPD)
        out += dedicatedInfoType_dedicatedInfoCDMA2000_HRPD.ToString(indent+1);
    return out;
}

std::string DLInformationTransfer_r8_IEs::dedicatedInfoType_ToStringNoNewLines() const
{
    std::string out = "dedicatedInfoType=" + dedicatedInfoType_ChoiceToString(dedicatedInfoType_internal_choice) + ",";
    if(dedicatedInfoType_internal_choice == k_dedicatedInfoType_dedicatedInfoNAS)
        out += dedicatedInfoType_dedicatedInfoNAS.ToStringNoNewLines();
    if(dedicatedInfoType_internal_choice == k_dedicatedInfoType_dedicatedInfoCDMA2000_1XRTT)
        out += dedicatedInfoType_dedicatedInfoCDMA2000_1XRTT.ToStringNoNewLines();
    if(dedicatedInfoType_internal_choice == k_dedicatedInfoType_dedicatedInfoCDMA2000_HRPD)
        out += dedicatedInfoType_dedicatedInfoCDMA2000_HRPD.ToStringNoNewLines();
    return out;
}

int DLInformationTransfer_r8_IEs::dedicatedInfoType_Clear()
{
    dedicatedInfoType_present = false;
    return 0;
}

bool DLInformationTransfer_r8_IEs::dedicatedInfoType_IsPresent() const
{
    return dedicatedInfoType_present;
}

DedicatedInfoNAS* DLInformationTransfer_r8_IEs::dedicatedInfoType_dedicatedInfoNAS_Set()
{
    dedicatedInfoType_dedicatedInfoNAS_present = true;
    return &dedicatedInfoType_dedicatedInfoNAS;
}

int DLInformationTransfer_r8_IEs::dedicatedInfoType_dedicatedInfoNAS_Set(DedicatedInfoNAS &value)
{
    dedicatedInfoType_dedicatedInfoNAS_present = true;
    dedicatedInfoType_dedicatedInfoNAS = value;
    return 0;
}

const DedicatedInfoNAS& DLInformationTransfer_r8_IEs::dedicatedInfoType_dedicatedInfoNAS_Get() const
{
    return dedicatedInfoType_dedicatedInfoNAS;
}

std::string DLInformationTransfer_r8_IEs::dedicatedInfoType_dedicatedInfoNAS_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "dedicatedInfoNAS:\n";
    out += dedicatedInfoType_dedicatedInfoNAS.ToString(indent+1);
    return out;
}

std::string DLInformationTransfer_r8_IEs::dedicatedInfoType_dedicatedInfoNAS_ToStringNoNewLines() const
{
    std::string out = "dedicatedInfoNAS:";
    out += dedicatedInfoType_dedicatedInfoNAS.ToStringNoNewLines();
    return out;
}

int DLInformationTransfer_r8_IEs::dedicatedInfoType_dedicatedInfoNAS_Clear()
{
    dedicatedInfoType_dedicatedInfoNAS_present = false;
    return 0;
}

bool DLInformationTransfer_r8_IEs::dedicatedInfoType_dedicatedInfoNAS_IsPresent() const
{
    return dedicatedInfoType_dedicatedInfoNAS_present;
}

DedicatedInfoCDMA2000* DLInformationTransfer_r8_IEs::dedicatedInfoType_dedicatedInfoCDMA2000_1XRTT_Set()
{
    dedicatedInfoType_dedicatedInfoCDMA2000_1XRTT_present = true;
    return &dedicatedInfoType_dedicatedInfoCDMA2000_1XRTT;
}

int DLInformationTransfer_r8_IEs::dedicatedInfoType_dedicatedInfoCDMA2000_1XRTT_Set(DedicatedInfoCDMA2000 &value)
{
    dedicatedInfoType_dedicatedInfoCDMA2000_1XRTT_present = true;
    dedicatedInfoType_dedicatedInfoCDMA2000_1XRTT = value;
    return 0;
}

const DedicatedInfoCDMA2000& DLInformationTransfer_r8_IEs::dedicatedInfoType_dedicatedInfoCDMA2000_1XRTT_Get() const
{
    return dedicatedInfoType_dedicatedInfoCDMA2000_1XRTT;
}

std::string DLInformationTransfer_r8_IEs::dedicatedInfoType_dedicatedInfoCDMA2000_1XRTT_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "dedicatedInfoCDMA2000_1XRTT:\n";
    out += dedicatedInfoType_dedicatedInfoCDMA2000_1XRTT.ToString(indent+1);
    return out;
}

std::string DLInformationTransfer_r8_IEs::dedicatedInfoType_dedicatedInfoCDMA2000_1XRTT_ToStringNoNewLines() const
{
    std::string out = "dedicatedInfoCDMA2000_1XRTT:";
    out += dedicatedInfoType_dedicatedInfoCDMA2000_1XRTT.ToStringNoNewLines();
    return out;
}

int DLInformationTransfer_r8_IEs::dedicatedInfoType_dedicatedInfoCDMA2000_1XRTT_Clear()
{
    dedicatedInfoType_dedicatedInfoCDMA2000_1XRTT_present = false;
    return 0;
}

bool DLInformationTransfer_r8_IEs::dedicatedInfoType_dedicatedInfoCDMA2000_1XRTT_IsPresent() const
{
    return dedicatedInfoType_dedicatedInfoCDMA2000_1XRTT_present;
}

DedicatedInfoCDMA2000* DLInformationTransfer_r8_IEs::dedicatedInfoType_dedicatedInfoCDMA2000_HRPD_Set()
{
    dedicatedInfoType_dedicatedInfoCDMA2000_HRPD_present = true;
    return &dedicatedInfoType_dedicatedInfoCDMA2000_HRPD;
}

int DLInformationTransfer_r8_IEs::dedicatedInfoType_dedicatedInfoCDMA2000_HRPD_Set(DedicatedInfoCDMA2000 &value)
{
    dedicatedInfoType_dedicatedInfoCDMA2000_HRPD_present = true;
    dedicatedInfoType_dedicatedInfoCDMA2000_HRPD = value;
    return 0;
}

const DedicatedInfoCDMA2000& DLInformationTransfer_r8_IEs::dedicatedInfoType_dedicatedInfoCDMA2000_HRPD_Get() const
{
    return dedicatedInfoType_dedicatedInfoCDMA2000_HRPD;
}

std::string DLInformationTransfer_r8_IEs::dedicatedInfoType_dedicatedInfoCDMA2000_HRPD_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "dedicatedInfoCDMA2000_HRPD:\n";
    out += dedicatedInfoType_dedicatedInfoCDMA2000_HRPD.ToString(indent+1);
    return out;
}

std::string DLInformationTransfer_r8_IEs::dedicatedInfoType_dedicatedInfoCDMA2000_HRPD_ToStringNoNewLines() const
{
    std::string out = "dedicatedInfoCDMA2000_HRPD:";
    out += dedicatedInfoType_dedicatedInfoCDMA2000_HRPD.ToStringNoNewLines();
    return out;
}

int DLInformationTransfer_r8_IEs::dedicatedInfoType_dedicatedInfoCDMA2000_HRPD_Clear()
{
    dedicatedInfoType_dedicatedInfoCDMA2000_HRPD_present = false;
    return 0;
}

bool DLInformationTransfer_r8_IEs::dedicatedInfoType_dedicatedInfoCDMA2000_HRPD_IsPresent() const
{
    return dedicatedInfoType_dedicatedInfoCDMA2000_HRPD_present;
}

DLInformationTransfer_v8a0_IEs* DLInformationTransfer_r8_IEs::nonCriticalExtension_Set()
{
    nonCriticalExtension_present = true;
    return &nonCriticalExtension;
}

int DLInformationTransfer_r8_IEs::nonCriticalExtension_Set(DLInformationTransfer_v8a0_IEs &value)
{
    nonCriticalExtension_present = true;
    nonCriticalExtension = value;
    return 0;
}

const DLInformationTransfer_v8a0_IEs& DLInformationTransfer_r8_IEs::nonCriticalExtension_Get() const
{
    return nonCriticalExtension;
}

std::string DLInformationTransfer_r8_IEs::nonCriticalExtension_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "nonCriticalExtension:\n";
    out += nonCriticalExtension.ToString(indent+1);
    return out;
}

std::string DLInformationTransfer_r8_IEs::nonCriticalExtension_ToStringNoNewLines() const
{
    std::string out = "nonCriticalExtension:";
    out += nonCriticalExtension.ToStringNoNewLines();
    return out;
}

int DLInformationTransfer_r8_IEs::nonCriticalExtension_Clear()
{
    nonCriticalExtension_present = false;
    return 0;
}

bool DLInformationTransfer_r8_IEs::nonCriticalExtension_IsPresent() const
{
    return nonCriticalExtension_present;
}

