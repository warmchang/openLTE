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

#include "ProximityIndication_r9_IEs.h"

#include <cmath>

int ProximityIndication_r9_IEs::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(nonCriticalExtension_IsPresent());

    // Fields
    {
        if(0 != type_r9_Pack(bits))
        {
            printf("ProximityIndication_r9_IEs:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != carrierFreq_r9_Pack(bits))
        {
            printf("ProximityIndication_r9_IEs:: field pack failure\n");
            return -1;
        }
    }
    if(nonCriticalExtension_IsPresent())
    {
        if(0 != nonCriticalExtension.Pack(bits))
        {
            printf("ProximityIndication_r9_IEs:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int ProximityIndication_r9_IEs::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int ProximityIndication_r9_IEs::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("ProximityIndication_r9_IEs::Unpack() index out of bounds for optional indiator nonCriticalExtension\n");
        return -1;
    }
    nonCriticalExtension_present = bits[idx++];

    // Fields
    {
        if(0 != type_r9_Unpack(bits, idx))
        {
            printf("ProximityIndication_r9_IEs:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != carrierFreq_r9_Unpack(bits, idx))
        {
            printf("ProximityIndication_r9_IEs:: field unpack failure\n");
            return -1;
        }
    }
    if(nonCriticalExtension_present)
    {
        if(0 != nonCriticalExtension.Unpack(bits, idx))
        {
            printf("ProximityIndication_r9_IEs:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string ProximityIndication_r9_IEs::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ProximityIndication_r9_IEs:\n";
    out += type_r9_ToString(indent+1);
    out += carrierFreq_r9_ToString(indent+1);
    if(nonCriticalExtension_IsPresent())
        out += nonCriticalExtension_ToString(indent+1);
    return out;
}

std::string ProximityIndication_r9_IEs::ToStringNoNewLines() const
{
    std::string out = "ProximityIndication_r9_IEs:";
    out += type_r9_ToStringNoNewLines();
    out += carrierFreq_r9_ToStringNoNewLines();
    if(nonCriticalExtension_IsPresent())
        out += nonCriticalExtension_ToStringNoNewLines();
    return out;
}

int ProximityIndication_r9_IEs::type_r9_Pack(std::vector<uint8_t> &bits)
{
    if(!type_r9_present)
    {
        printf("ProximityIndication_r9_IEs::type_r9_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((type_r9_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int ProximityIndication_r9_IEs::type_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return type_r9_Unpack(bits, idx);
}

int ProximityIndication_r9_IEs::type_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("ProximityIndication_r9_IEs::type_r9_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 1)
    {
        printf("ProximityIndication_r9_IEs::type_r9_Unpack() max failure\n");
        return -1;
    }
    type_r9_internal_value = (type_r9_Enum)packed_val;
    type_r9_present = true;
    return 0;
}

ProximityIndication_r9_IEs::type_r9_Enum ProximityIndication_r9_IEs::type_r9_Value() const
{
    if(type_r9_present)
        return type_r9_internal_value;
    return (ProximityIndication_r9_IEs::type_r9_Enum)0;
}

int ProximityIndication_r9_IEs::type_r9_SetValue(type_r9_Enum value)
{
    type_r9_internal_value = value;
    type_r9_present = true;
    return 0;
}

int ProximityIndication_r9_IEs::type_r9_SetValue(std::string value)
{
    if("entering" == value)
    {
        type_r9_internal_value = k_type_r9_entering;
        type_r9_present = true;
        return 0;
    }
    if("leaving" == value)
    {
        type_r9_internal_value = k_type_r9_leaving;
        type_r9_present = true;
        return 0;
    }
    return 1;
}

std::string ProximityIndication_r9_IEs::type_r9_ValueToString(type_r9_Enum value) const
{
    if(k_type_r9_entering == value)
        return "entering";
    if(k_type_r9_leaving == value)
        return "leaving";
    return "";
}

uint64_t ProximityIndication_r9_IEs::type_r9_NumberOfValues() const
{
    return 2;
}

std::string ProximityIndication_r9_IEs::type_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "type_r9 = " + type_r9_ValueToString(type_r9_internal_value) + "\n";
    return out;
}

std::string ProximityIndication_r9_IEs::type_r9_ToStringNoNewLines() const
{
    std::string out = "type_r9=" + type_r9_ValueToString(type_r9_internal_value) + ",";
    return out;
}

int ProximityIndication_r9_IEs::type_r9_Clear()
{
    type_r9_present = false;
    return 0;
}

bool ProximityIndication_r9_IEs::type_r9_IsPresent() const
{
    return type_r9_present;
}

int ProximityIndication_r9_IEs::carrierFreq_r9_Pack(std::vector<uint8_t> &bits)
{
    if(!carrierFreq_r9_present)
    {
        printf("ProximityIndication_r9_IEs::carrierFreq_r9_Pack() presence failure\n");
        return -1;
    }
    // Extension indicator
    bits.push_back(0);

    // Choice
    for(uint32_t i=0; i<1; i++)
        bits.push_back((carrierFreq_r9_internal_choice >> (1-i-1)) & 1);

    // Fields
    if(carrierFreq_r9_internal_choice == k_carrierFreq_r9_eutra_r9)
    {
        if(0 != carrierFreq_r9_eutra_r9.Pack(bits))
        {
            printf("ProximityIndication_r9_IEs::carrierFreq_r9_eutra_r9 pack failure\n");
            return -1;
        }
    }
    if(carrierFreq_r9_internal_choice == k_carrierFreq_r9_utra_r9)
    {
        if(0 != carrierFreq_r9_utra_r9.Pack(bits))
        {
            printf("ProximityIndication_r9_IEs::carrierFreq_r9_utra_r9 pack failure\n");
            return -1;
        }
    }
    return 0;
}

int ProximityIndication_r9_IEs::carrierFreq_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return carrierFreq_r9_Unpack(bits, idx);
}

int ProximityIndication_r9_IEs::carrierFreq_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("ProximityIndication_r9_IEs::carrierFreq_r9_Unpack() index out of bounds for extension\n");
        return -1;
    }
    idx++;

    // Choice
    uint32_t packed_val = 0;
    if((idx + 1) > bits.size())
    {
        printf("ProximityIndication_r9_IEs::carrierFreq_r9_Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<1; i++)
        packed_val |= bits[idx++] << (1-i-1);

    if((ProximityIndication_r9_IEs::carrierFreq_r9_Enum)packed_val > k_carrierFreq_r9_utra_r9)
    {
        printf("ProximityIndication_r9_IEs::carrierFreq_r9_Unpack() choice range failure\n");
        return -1;
    }
    carrierFreq_r9_internal_choice = (ProximityIndication_r9_IEs::carrierFreq_r9_Enum)packed_val;
    carrierFreq_r9_present = true;

    // Fields
    if(carrierFreq_r9_internal_choice == k_carrierFreq_r9_eutra_r9)
    {
        if(0 != carrierFreq_r9_eutra_r9.Unpack(bits, idx))
        {
            printf("ProximityIndication_r9_IEs::carrierFreq_r9_eutra_r9 unpack failure\n");
            return -1;
        }
    }
    if(carrierFreq_r9_internal_choice == k_carrierFreq_r9_utra_r9)
    {
        if(0 != carrierFreq_r9_utra_r9.Unpack(bits, idx))
        {
            printf("ProximityIndication_r9_IEs::carrierFreq_r9_utra_r9 unpack failure\n");
            return -1;
        }
    }
    return 0;
}

ProximityIndication_r9_IEs::carrierFreq_r9_Enum ProximityIndication_r9_IEs::carrierFreq_r9_Choice() const
{
    if(carrierFreq_r9_present)
        return carrierFreq_r9_internal_choice;
    return (ProximityIndication_r9_IEs::carrierFreq_r9_Enum)0;
}

int ProximityIndication_r9_IEs::carrierFreq_r9_SetChoice(ProximityIndication_r9_IEs::carrierFreq_r9_Enum choice)
{
    carrierFreq_r9_internal_choice = choice;
    carrierFreq_r9_present = true;
    return 0;
}

std::string ProximityIndication_r9_IEs::carrierFreq_r9_ChoiceToString(carrierFreq_r9_Enum value) const
{
    if(k_carrierFreq_r9_eutra_r9 == value)
        return "carrierFreq_r9_eutra_r9";
    if(k_carrierFreq_r9_utra_r9 == value)
        return "carrierFreq_r9_utra_r9";
    return "";
}

uint64_t ProximityIndication_r9_IEs::carrierFreq_r9_NumberOfChoices() const
{
    return 2;
}

std::string ProximityIndication_r9_IEs::carrierFreq_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "carrierFreq_r9 = " + carrierFreq_r9_ChoiceToString(carrierFreq_r9_internal_choice) + ":\n";
    if(carrierFreq_r9_internal_choice == k_carrierFreq_r9_eutra_r9)
        out += carrierFreq_r9_eutra_r9.ToString(indent+1);
    if(carrierFreq_r9_internal_choice == k_carrierFreq_r9_utra_r9)
        out += carrierFreq_r9_utra_r9.ToString(indent+1);
    return out;
}

std::string ProximityIndication_r9_IEs::carrierFreq_r9_ToStringNoNewLines() const
{
    std::string out = "carrierFreq_r9=" + carrierFreq_r9_ChoiceToString(carrierFreq_r9_internal_choice) + ",";
    if(carrierFreq_r9_internal_choice == k_carrierFreq_r9_eutra_r9)
        out += carrierFreq_r9_eutra_r9.ToStringNoNewLines();
    if(carrierFreq_r9_internal_choice == k_carrierFreq_r9_utra_r9)
        out += carrierFreq_r9_utra_r9.ToStringNoNewLines();
    return out;
}

int ProximityIndication_r9_IEs::carrierFreq_r9_Clear()
{
    carrierFreq_r9_present = false;
    return 0;
}

bool ProximityIndication_r9_IEs::carrierFreq_r9_IsPresent() const
{
    return carrierFreq_r9_present;
}

ARFCN_ValueEUTRA* ProximityIndication_r9_IEs::carrierFreq_r9_eutra_r9_Set()
{
    carrierFreq_r9_eutra_r9_present = true;
    return &carrierFreq_r9_eutra_r9;
}

int ProximityIndication_r9_IEs::carrierFreq_r9_eutra_r9_Set(ARFCN_ValueEUTRA &value)
{
    carrierFreq_r9_eutra_r9_present = true;
    carrierFreq_r9_eutra_r9 = value;
    return 0;
}

const ARFCN_ValueEUTRA& ProximityIndication_r9_IEs::carrierFreq_r9_eutra_r9_Get() const
{
    return carrierFreq_r9_eutra_r9;
}

std::string ProximityIndication_r9_IEs::carrierFreq_r9_eutra_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "eutra_r9:\n";
    out += carrierFreq_r9_eutra_r9.ToString(indent+1);
    return out;
}

std::string ProximityIndication_r9_IEs::carrierFreq_r9_eutra_r9_ToStringNoNewLines() const
{
    std::string out = "eutra_r9:";
    out += carrierFreq_r9_eutra_r9.ToStringNoNewLines();
    return out;
}

int ProximityIndication_r9_IEs::carrierFreq_r9_eutra_r9_Clear()
{
    carrierFreq_r9_eutra_r9_present = false;
    return 0;
}

bool ProximityIndication_r9_IEs::carrierFreq_r9_eutra_r9_IsPresent() const
{
    return carrierFreq_r9_eutra_r9_present;
}

ARFCN_ValueUTRA* ProximityIndication_r9_IEs::carrierFreq_r9_utra_r9_Set()
{
    carrierFreq_r9_utra_r9_present = true;
    return &carrierFreq_r9_utra_r9;
}

int ProximityIndication_r9_IEs::carrierFreq_r9_utra_r9_Set(ARFCN_ValueUTRA &value)
{
    carrierFreq_r9_utra_r9_present = true;
    carrierFreq_r9_utra_r9 = value;
    return 0;
}

const ARFCN_ValueUTRA& ProximityIndication_r9_IEs::carrierFreq_r9_utra_r9_Get() const
{
    return carrierFreq_r9_utra_r9;
}

std::string ProximityIndication_r9_IEs::carrierFreq_r9_utra_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "utra_r9:\n";
    out += carrierFreq_r9_utra_r9.ToString(indent+1);
    return out;
}

std::string ProximityIndication_r9_IEs::carrierFreq_r9_utra_r9_ToStringNoNewLines() const
{
    std::string out = "utra_r9:";
    out += carrierFreq_r9_utra_r9.ToStringNoNewLines();
    return out;
}

int ProximityIndication_r9_IEs::carrierFreq_r9_utra_r9_Clear()
{
    carrierFreq_r9_utra_r9_present = false;
    return 0;
}

bool ProximityIndication_r9_IEs::carrierFreq_r9_utra_r9_IsPresent() const
{
    return carrierFreq_r9_utra_r9_present;
}

ProximityIndication_v930_IEs* ProximityIndication_r9_IEs::nonCriticalExtension_Set()
{
    nonCriticalExtension_present = true;
    return &nonCriticalExtension;
}

int ProximityIndication_r9_IEs::nonCriticalExtension_Set(ProximityIndication_v930_IEs &value)
{
    nonCriticalExtension_present = true;
    nonCriticalExtension = value;
    return 0;
}

const ProximityIndication_v930_IEs& ProximityIndication_r9_IEs::nonCriticalExtension_Get() const
{
    return nonCriticalExtension;
}

std::string ProximityIndication_r9_IEs::nonCriticalExtension_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "nonCriticalExtension:\n";
    out += nonCriticalExtension.ToString(indent+1);
    return out;
}

std::string ProximityIndication_r9_IEs::nonCriticalExtension_ToStringNoNewLines() const
{
    std::string out = "nonCriticalExtension:";
    out += nonCriticalExtension.ToStringNoNewLines();
    return out;
}

int ProximityIndication_r9_IEs::nonCriticalExtension_Clear()
{
    nonCriticalExtension_present = false;
    return 0;
}

bool ProximityIndication_r9_IEs::nonCriticalExtension_IsPresent() const
{
    return nonCriticalExtension_present;
}

