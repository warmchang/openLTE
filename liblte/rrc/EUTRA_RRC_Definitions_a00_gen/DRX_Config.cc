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

#include "DRX_Config.h"

#include <cmath>

int DRX_Config::Pack(std::vector<uint8_t> &bits)
{
    if(!present)
    {
        printf("DRX_Config::Pack() presence failure\n");
        return -1;
    }
    // Extension indicator

    // Choice
    for(uint32_t i=0; i<1; i++)
        bits.push_back((internal_choice >> (1-i-1)) & 1);

    // Fields
    if(internal_choice == k_release)
    {
        if(0 != release_Pack(bits))
        {
            printf("DRX_Config::release pack failure\n");
            return -1;
        }
    }
    if(internal_choice == k_setup)
    {
        if(0 != setup_value.Pack(bits))
        {
            printf("DRX_Config::setup pack failure\n");
            return -1;
        }
    }
    return 0;
}

int DRX_Config::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int DRX_Config::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 1) > bits.size())
    {
        printf("DRX_Config::Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<1; i++)
        packed_val |= bits[idx++] << (1-i-1);

    if((DRX_Config::Enum)packed_val > k_setup)
    {
        printf("DRX_Config::Unpack() choice range failure\n");
        return -1;
    }
    internal_choice = (DRX_Config::Enum)packed_val;
    present = true;

    // Fields
    if(internal_choice == k_release)
    {
        if(0 != release_Unpack(bits, idx))
        {
            printf("DRX_Config::release unpack failure\n");
            return -1;
        }
    }
    if(internal_choice == k_setup)
    {
        if(0 != setup_value.Unpack(bits, idx))
        {
            printf("DRX_Config::setup unpack failure\n");
            return -1;
        }
    }
    return 0;
}

DRX_Config::Enum DRX_Config::Choice() const
{
    if(present)
        return internal_choice;
    return (DRX_Config::Enum)0;
}

int DRX_Config::SetChoice(DRX_Config::Enum choice)
{
    internal_choice = choice;
    present = true;
    return 0;
}

std::string DRX_Config::ChoiceToString(Enum value) const
{
    if(k_release == value)
        return "release";
    if(k_setup == value)
        return "setup";
    return "";
}

uint64_t DRX_Config::NumberOfChoices() const
{
    return 2;
}

std::string DRX_Config::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "DRX_Config = " + ChoiceToString(internal_choice) + ":\n";
    if(internal_choice == k_setup)
        out += setup_value.ToString(indent+1);
    return out;
}

std::string DRX_Config::ToStringNoNewLines() const
{
    std::string out = "DRX_Config=" + ChoiceToString(internal_choice) + ",";
    if(internal_choice == k_setup)
        out += setup_value.ToStringNoNewLines();
    return out;
}

int DRX_Config::Clear()
{
    present = false;
    return 0;
}

bool DRX_Config::IsPresent() const
{
    return present;
}

int DRX_Config::setup::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(shortDRX_value.IsPresent());

    // Fields
    {
        if(0 != onDurationTimer_Pack(bits))
        {
            printf("DRX_Config::setup:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != drx_InactivityTimer_Pack(bits))
        {
            printf("DRX_Config::setup:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != drx_RetransmissionTimer_Pack(bits))
        {
            printf("DRX_Config::setup:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != longDRX_CycleStartOffset_Pack(bits))
        {
            printf("DRX_Config::setup:: field pack failure\n");
            return -1;
        }
    }
    if(shortDRX_value.IsPresent())
    {
        if(0 != shortDRX_value.Pack(bits))
        {
            printf("DRX_Config::setup:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int DRX_Config::setup::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int DRX_Config::setup::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("setup::Unpack() index out of bounds for optional indiator shortDRX\n");
        return -1;
    }
    shortDRX_value.SetPresence(bits[idx++]);

    // Fields
    {
        if(0 != onDurationTimer_Unpack(bits, idx))
        {
            printf("DRX_Config::setup:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != drx_InactivityTimer_Unpack(bits, idx))
        {
            printf("DRX_Config::setup:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != drx_RetransmissionTimer_Unpack(bits, idx))
        {
            printf("DRX_Config::setup:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != longDRX_CycleStartOffset_Unpack(bits, idx))
        {
            printf("DRX_Config::setup:: field unpack failure\n");
            return -1;
        }
    }
    if(shortDRX_value.IsPresent())
    {
        if(0 != shortDRX_value.Unpack(bits, idx))
        {
            printf("DRX_Config::setup:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string DRX_Config::setup::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "setup:\n";
    out += onDurationTimer_ToString(indent+1);
    out += drx_InactivityTimer_ToString(indent+1);
    out += drx_RetransmissionTimer_ToString(indent+1);
    out += longDRX_CycleStartOffset_ToString(indent+1);
    if(shortDRX_value.IsPresent())
        out += shortDRX_value.ToString(indent+1);
    return out;
}

std::string DRX_Config::setup::ToStringNoNewLines() const
{
    std::string out = "setup:";
    out += onDurationTimer_ToStringNoNewLines();
    out += drx_InactivityTimer_ToStringNoNewLines();
    out += drx_RetransmissionTimer_ToStringNoNewLines();
    out += longDRX_CycleStartOffset_ToStringNoNewLines();
    if(shortDRX_value.IsPresent())
        out += shortDRX_value.ToStringNoNewLines();
    return out;
}

int DRX_Config::setup::onDurationTimer_Pack(std::vector<uint8_t> &bits)
{
    if(!onDurationTimer_present)
    {
        printf("DRX_Config::setup::onDurationTimer_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 4;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((onDurationTimer_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int DRX_Config::setup::onDurationTimer_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return onDurationTimer_Unpack(bits, idx);
}

int DRX_Config::setup::onDurationTimer_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 4;
    if((idx + N_bits) > bits.size())
    {
        printf("DRX_Config::setup::onDurationTimer_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 15)
    {
        printf("DRX_Config::setup::onDurationTimer_Unpack() max failure\n");
        return -1;
    }
    onDurationTimer_internal_value = (onDurationTimer_Enum)packed_val;
    onDurationTimer_present = true;
    return 0;
}

DRX_Config::setup::onDurationTimer_Enum DRX_Config::setup::onDurationTimer_Value() const
{
    if(onDurationTimer_present)
        return onDurationTimer_internal_value;
    return (DRX_Config::setup::onDurationTimer_Enum)0;
}

int DRX_Config::setup::onDurationTimer_SetValue(onDurationTimer_Enum value)
{
    onDurationTimer_internal_value = value;
    onDurationTimer_present = true;
    return 0;
}

int DRX_Config::setup::onDurationTimer_SetValue(std::string value)
{
    if("psf1" == value)
    {
        onDurationTimer_internal_value = k_onDurationTimer_psf1;
        onDurationTimer_present = true;
        return 0;
    }
    if("psf2" == value)
    {
        onDurationTimer_internal_value = k_onDurationTimer_psf2;
        onDurationTimer_present = true;
        return 0;
    }
    if("psf3" == value)
    {
        onDurationTimer_internal_value = k_onDurationTimer_psf3;
        onDurationTimer_present = true;
        return 0;
    }
    if("psf4" == value)
    {
        onDurationTimer_internal_value = k_onDurationTimer_psf4;
        onDurationTimer_present = true;
        return 0;
    }
    if("psf5" == value)
    {
        onDurationTimer_internal_value = k_onDurationTimer_psf5;
        onDurationTimer_present = true;
        return 0;
    }
    if("psf6" == value)
    {
        onDurationTimer_internal_value = k_onDurationTimer_psf6;
        onDurationTimer_present = true;
        return 0;
    }
    if("psf8" == value)
    {
        onDurationTimer_internal_value = k_onDurationTimer_psf8;
        onDurationTimer_present = true;
        return 0;
    }
    if("psf10" == value)
    {
        onDurationTimer_internal_value = k_onDurationTimer_psf10;
        onDurationTimer_present = true;
        return 0;
    }
    if("psf20" == value)
    {
        onDurationTimer_internal_value = k_onDurationTimer_psf20;
        onDurationTimer_present = true;
        return 0;
    }
    if("psf30" == value)
    {
        onDurationTimer_internal_value = k_onDurationTimer_psf30;
        onDurationTimer_present = true;
        return 0;
    }
    if("psf40" == value)
    {
        onDurationTimer_internal_value = k_onDurationTimer_psf40;
        onDurationTimer_present = true;
        return 0;
    }
    if("psf50" == value)
    {
        onDurationTimer_internal_value = k_onDurationTimer_psf50;
        onDurationTimer_present = true;
        return 0;
    }
    if("psf60" == value)
    {
        onDurationTimer_internal_value = k_onDurationTimer_psf60;
        onDurationTimer_present = true;
        return 0;
    }
    if("psf80" == value)
    {
        onDurationTimer_internal_value = k_onDurationTimer_psf80;
        onDurationTimer_present = true;
        return 0;
    }
    if("psf100" == value)
    {
        onDurationTimer_internal_value = k_onDurationTimer_psf100;
        onDurationTimer_present = true;
        return 0;
    }
    if("psf200" == value)
    {
        onDurationTimer_internal_value = k_onDurationTimer_psf200;
        onDurationTimer_present = true;
        return 0;
    }
    return 1;
}

std::string DRX_Config::setup::onDurationTimer_ValueToString(onDurationTimer_Enum value) const
{
    if(k_onDurationTimer_psf1 == value)
        return "psf1";
    if(k_onDurationTimer_psf2 == value)
        return "psf2";
    if(k_onDurationTimer_psf3 == value)
        return "psf3";
    if(k_onDurationTimer_psf4 == value)
        return "psf4";
    if(k_onDurationTimer_psf5 == value)
        return "psf5";
    if(k_onDurationTimer_psf6 == value)
        return "psf6";
    if(k_onDurationTimer_psf8 == value)
        return "psf8";
    if(k_onDurationTimer_psf10 == value)
        return "psf10";
    if(k_onDurationTimer_psf20 == value)
        return "psf20";
    if(k_onDurationTimer_psf30 == value)
        return "psf30";
    if(k_onDurationTimer_psf40 == value)
        return "psf40";
    if(k_onDurationTimer_psf50 == value)
        return "psf50";
    if(k_onDurationTimer_psf60 == value)
        return "psf60";
    if(k_onDurationTimer_psf80 == value)
        return "psf80";
    if(k_onDurationTimer_psf100 == value)
        return "psf100";
    if(k_onDurationTimer_psf200 == value)
        return "psf200";
    return "";
}

uint64_t DRX_Config::setup::onDurationTimer_NumberOfValues() const
{
    return 16;
}

std::string DRX_Config::setup::onDurationTimer_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "onDurationTimer = " + onDurationTimer_ValueToString(onDurationTimer_internal_value) + "\n";
    return out;
}

std::string DRX_Config::setup::onDurationTimer_ToStringNoNewLines() const
{
    std::string out = "onDurationTimer=" + onDurationTimer_ValueToString(onDurationTimer_internal_value) + ",";
    return out;
}

int DRX_Config::setup::onDurationTimer_Clear()
{
    onDurationTimer_present = false;
    return 0;
}

bool DRX_Config::setup::onDurationTimer_IsPresent() const
{
    return onDurationTimer_present;
}

int DRX_Config::setup::drx_InactivityTimer_Pack(std::vector<uint8_t> &bits)
{
    if(!drx_InactivityTimer_present)
    {
        printf("DRX_Config::setup::drx_InactivityTimer_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 5;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((drx_InactivityTimer_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int DRX_Config::setup::drx_InactivityTimer_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return drx_InactivityTimer_Unpack(bits, idx);
}

int DRX_Config::setup::drx_InactivityTimer_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 5;
    if((idx + N_bits) > bits.size())
    {
        printf("DRX_Config::setup::drx_InactivityTimer_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 31)
    {
        printf("DRX_Config::setup::drx_InactivityTimer_Unpack() max failure\n");
        return -1;
    }
    drx_InactivityTimer_internal_value = (drx_InactivityTimer_Enum)packed_val;
    drx_InactivityTimer_present = true;
    return 0;
}

DRX_Config::setup::drx_InactivityTimer_Enum DRX_Config::setup::drx_InactivityTimer_Value() const
{
    if(drx_InactivityTimer_present)
        return drx_InactivityTimer_internal_value;
    return (DRX_Config::setup::drx_InactivityTimer_Enum)0;
}

int DRX_Config::setup::drx_InactivityTimer_SetValue(drx_InactivityTimer_Enum value)
{
    drx_InactivityTimer_internal_value = value;
    drx_InactivityTimer_present = true;
    return 0;
}

int DRX_Config::setup::drx_InactivityTimer_SetValue(std::string value)
{
    if("psf1" == value)
    {
        drx_InactivityTimer_internal_value = k_drx_InactivityTimer_psf1;
        drx_InactivityTimer_present = true;
        return 0;
    }
    if("psf2" == value)
    {
        drx_InactivityTimer_internal_value = k_drx_InactivityTimer_psf2;
        drx_InactivityTimer_present = true;
        return 0;
    }
    if("psf3" == value)
    {
        drx_InactivityTimer_internal_value = k_drx_InactivityTimer_psf3;
        drx_InactivityTimer_present = true;
        return 0;
    }
    if("psf4" == value)
    {
        drx_InactivityTimer_internal_value = k_drx_InactivityTimer_psf4;
        drx_InactivityTimer_present = true;
        return 0;
    }
    if("psf5" == value)
    {
        drx_InactivityTimer_internal_value = k_drx_InactivityTimer_psf5;
        drx_InactivityTimer_present = true;
        return 0;
    }
    if("psf6" == value)
    {
        drx_InactivityTimer_internal_value = k_drx_InactivityTimer_psf6;
        drx_InactivityTimer_present = true;
        return 0;
    }
    if("psf8" == value)
    {
        drx_InactivityTimer_internal_value = k_drx_InactivityTimer_psf8;
        drx_InactivityTimer_present = true;
        return 0;
    }
    if("psf10" == value)
    {
        drx_InactivityTimer_internal_value = k_drx_InactivityTimer_psf10;
        drx_InactivityTimer_present = true;
        return 0;
    }
    if("psf20" == value)
    {
        drx_InactivityTimer_internal_value = k_drx_InactivityTimer_psf20;
        drx_InactivityTimer_present = true;
        return 0;
    }
    if("psf30" == value)
    {
        drx_InactivityTimer_internal_value = k_drx_InactivityTimer_psf30;
        drx_InactivityTimer_present = true;
        return 0;
    }
    if("psf40" == value)
    {
        drx_InactivityTimer_internal_value = k_drx_InactivityTimer_psf40;
        drx_InactivityTimer_present = true;
        return 0;
    }
    if("psf50" == value)
    {
        drx_InactivityTimer_internal_value = k_drx_InactivityTimer_psf50;
        drx_InactivityTimer_present = true;
        return 0;
    }
    if("psf60" == value)
    {
        drx_InactivityTimer_internal_value = k_drx_InactivityTimer_psf60;
        drx_InactivityTimer_present = true;
        return 0;
    }
    if("psf80" == value)
    {
        drx_InactivityTimer_internal_value = k_drx_InactivityTimer_psf80;
        drx_InactivityTimer_present = true;
        return 0;
    }
    if("psf100" == value)
    {
        drx_InactivityTimer_internal_value = k_drx_InactivityTimer_psf100;
        drx_InactivityTimer_present = true;
        return 0;
    }
    if("psf200" == value)
    {
        drx_InactivityTimer_internal_value = k_drx_InactivityTimer_psf200;
        drx_InactivityTimer_present = true;
        return 0;
    }
    if("psf300" == value)
    {
        drx_InactivityTimer_internal_value = k_drx_InactivityTimer_psf300;
        drx_InactivityTimer_present = true;
        return 0;
    }
    if("psf500" == value)
    {
        drx_InactivityTimer_internal_value = k_drx_InactivityTimer_psf500;
        drx_InactivityTimer_present = true;
        return 0;
    }
    if("psf750" == value)
    {
        drx_InactivityTimer_internal_value = k_drx_InactivityTimer_psf750;
        drx_InactivityTimer_present = true;
        return 0;
    }
    if("psf1280" == value)
    {
        drx_InactivityTimer_internal_value = k_drx_InactivityTimer_psf1280;
        drx_InactivityTimer_present = true;
        return 0;
    }
    if("psf1920" == value)
    {
        drx_InactivityTimer_internal_value = k_drx_InactivityTimer_psf1920;
        drx_InactivityTimer_present = true;
        return 0;
    }
    if("psf2560" == value)
    {
        drx_InactivityTimer_internal_value = k_drx_InactivityTimer_psf2560;
        drx_InactivityTimer_present = true;
        return 0;
    }
    if("spare10" == value)
    {
        drx_InactivityTimer_internal_value = k_drx_InactivityTimer_spare10;
        drx_InactivityTimer_present = true;
        return 0;
    }
    if("spare9" == value)
    {
        drx_InactivityTimer_internal_value = k_drx_InactivityTimer_spare9;
        drx_InactivityTimer_present = true;
        return 0;
    }
    if("spare8" == value)
    {
        drx_InactivityTimer_internal_value = k_drx_InactivityTimer_spare8;
        drx_InactivityTimer_present = true;
        return 0;
    }
    if("spare7" == value)
    {
        drx_InactivityTimer_internal_value = k_drx_InactivityTimer_spare7;
        drx_InactivityTimer_present = true;
        return 0;
    }
    if("spare6" == value)
    {
        drx_InactivityTimer_internal_value = k_drx_InactivityTimer_spare6;
        drx_InactivityTimer_present = true;
        return 0;
    }
    if("spare5" == value)
    {
        drx_InactivityTimer_internal_value = k_drx_InactivityTimer_spare5;
        drx_InactivityTimer_present = true;
        return 0;
    }
    if("spare4" == value)
    {
        drx_InactivityTimer_internal_value = k_drx_InactivityTimer_spare4;
        drx_InactivityTimer_present = true;
        return 0;
    }
    if("spare3" == value)
    {
        drx_InactivityTimer_internal_value = k_drx_InactivityTimer_spare3;
        drx_InactivityTimer_present = true;
        return 0;
    }
    if("spare2" == value)
    {
        drx_InactivityTimer_internal_value = k_drx_InactivityTimer_spare2;
        drx_InactivityTimer_present = true;
        return 0;
    }
    if("spare1" == value)
    {
        drx_InactivityTimer_internal_value = k_drx_InactivityTimer_spare1;
        drx_InactivityTimer_present = true;
        return 0;
    }
    return 1;
}

std::string DRX_Config::setup::drx_InactivityTimer_ValueToString(drx_InactivityTimer_Enum value) const
{
    if(k_drx_InactivityTimer_psf1 == value)
        return "psf1";
    if(k_drx_InactivityTimer_psf2 == value)
        return "psf2";
    if(k_drx_InactivityTimer_psf3 == value)
        return "psf3";
    if(k_drx_InactivityTimer_psf4 == value)
        return "psf4";
    if(k_drx_InactivityTimer_psf5 == value)
        return "psf5";
    if(k_drx_InactivityTimer_psf6 == value)
        return "psf6";
    if(k_drx_InactivityTimer_psf8 == value)
        return "psf8";
    if(k_drx_InactivityTimer_psf10 == value)
        return "psf10";
    if(k_drx_InactivityTimer_psf20 == value)
        return "psf20";
    if(k_drx_InactivityTimer_psf30 == value)
        return "psf30";
    if(k_drx_InactivityTimer_psf40 == value)
        return "psf40";
    if(k_drx_InactivityTimer_psf50 == value)
        return "psf50";
    if(k_drx_InactivityTimer_psf60 == value)
        return "psf60";
    if(k_drx_InactivityTimer_psf80 == value)
        return "psf80";
    if(k_drx_InactivityTimer_psf100 == value)
        return "psf100";
    if(k_drx_InactivityTimer_psf200 == value)
        return "psf200";
    if(k_drx_InactivityTimer_psf300 == value)
        return "psf300";
    if(k_drx_InactivityTimer_psf500 == value)
        return "psf500";
    if(k_drx_InactivityTimer_psf750 == value)
        return "psf750";
    if(k_drx_InactivityTimer_psf1280 == value)
        return "psf1280";
    if(k_drx_InactivityTimer_psf1920 == value)
        return "psf1920";
    if(k_drx_InactivityTimer_psf2560 == value)
        return "psf2560";
    if(k_drx_InactivityTimer_spare10 == value)
        return "spare10";
    if(k_drx_InactivityTimer_spare9 == value)
        return "spare9";
    if(k_drx_InactivityTimer_spare8 == value)
        return "spare8";
    if(k_drx_InactivityTimer_spare7 == value)
        return "spare7";
    if(k_drx_InactivityTimer_spare6 == value)
        return "spare6";
    if(k_drx_InactivityTimer_spare5 == value)
        return "spare5";
    if(k_drx_InactivityTimer_spare4 == value)
        return "spare4";
    if(k_drx_InactivityTimer_spare3 == value)
        return "spare3";
    if(k_drx_InactivityTimer_spare2 == value)
        return "spare2";
    if(k_drx_InactivityTimer_spare1 == value)
        return "spare1";
    return "";
}

uint64_t DRX_Config::setup::drx_InactivityTimer_NumberOfValues() const
{
    return 32;
}

std::string DRX_Config::setup::drx_InactivityTimer_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "drx_InactivityTimer = " + drx_InactivityTimer_ValueToString(drx_InactivityTimer_internal_value) + "\n";
    return out;
}

std::string DRX_Config::setup::drx_InactivityTimer_ToStringNoNewLines() const
{
    std::string out = "drx_InactivityTimer=" + drx_InactivityTimer_ValueToString(drx_InactivityTimer_internal_value) + ",";
    return out;
}

int DRX_Config::setup::drx_InactivityTimer_Clear()
{
    drx_InactivityTimer_present = false;
    return 0;
}

bool DRX_Config::setup::drx_InactivityTimer_IsPresent() const
{
    return drx_InactivityTimer_present;
}

int DRX_Config::setup::drx_RetransmissionTimer_Pack(std::vector<uint8_t> &bits)
{
    if(!drx_RetransmissionTimer_present)
    {
        printf("DRX_Config::setup::drx_RetransmissionTimer_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 3;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((drx_RetransmissionTimer_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int DRX_Config::setup::drx_RetransmissionTimer_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return drx_RetransmissionTimer_Unpack(bits, idx);
}

int DRX_Config::setup::drx_RetransmissionTimer_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 3;
    if((idx + N_bits) > bits.size())
    {
        printf("DRX_Config::setup::drx_RetransmissionTimer_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 7)
    {
        printf("DRX_Config::setup::drx_RetransmissionTimer_Unpack() max failure\n");
        return -1;
    }
    drx_RetransmissionTimer_internal_value = (drx_RetransmissionTimer_Enum)packed_val;
    drx_RetransmissionTimer_present = true;
    return 0;
}

DRX_Config::setup::drx_RetransmissionTimer_Enum DRX_Config::setup::drx_RetransmissionTimer_Value() const
{
    if(drx_RetransmissionTimer_present)
        return drx_RetransmissionTimer_internal_value;
    return (DRX_Config::setup::drx_RetransmissionTimer_Enum)0;
}

int DRX_Config::setup::drx_RetransmissionTimer_SetValue(drx_RetransmissionTimer_Enum value)
{
    drx_RetransmissionTimer_internal_value = value;
    drx_RetransmissionTimer_present = true;
    return 0;
}

int DRX_Config::setup::drx_RetransmissionTimer_SetValue(std::string value)
{
    if("psf1" == value)
    {
        drx_RetransmissionTimer_internal_value = k_drx_RetransmissionTimer_psf1;
        drx_RetransmissionTimer_present = true;
        return 0;
    }
    if("psf2" == value)
    {
        drx_RetransmissionTimer_internal_value = k_drx_RetransmissionTimer_psf2;
        drx_RetransmissionTimer_present = true;
        return 0;
    }
    if("psf4" == value)
    {
        drx_RetransmissionTimer_internal_value = k_drx_RetransmissionTimer_psf4;
        drx_RetransmissionTimer_present = true;
        return 0;
    }
    if("psf6" == value)
    {
        drx_RetransmissionTimer_internal_value = k_drx_RetransmissionTimer_psf6;
        drx_RetransmissionTimer_present = true;
        return 0;
    }
    if("psf8" == value)
    {
        drx_RetransmissionTimer_internal_value = k_drx_RetransmissionTimer_psf8;
        drx_RetransmissionTimer_present = true;
        return 0;
    }
    if("psf16" == value)
    {
        drx_RetransmissionTimer_internal_value = k_drx_RetransmissionTimer_psf16;
        drx_RetransmissionTimer_present = true;
        return 0;
    }
    if("psf24" == value)
    {
        drx_RetransmissionTimer_internal_value = k_drx_RetransmissionTimer_psf24;
        drx_RetransmissionTimer_present = true;
        return 0;
    }
    if("psf33" == value)
    {
        drx_RetransmissionTimer_internal_value = k_drx_RetransmissionTimer_psf33;
        drx_RetransmissionTimer_present = true;
        return 0;
    }
    return 1;
}

std::string DRX_Config::setup::drx_RetransmissionTimer_ValueToString(drx_RetransmissionTimer_Enum value) const
{
    if(k_drx_RetransmissionTimer_psf1 == value)
        return "psf1";
    if(k_drx_RetransmissionTimer_psf2 == value)
        return "psf2";
    if(k_drx_RetransmissionTimer_psf4 == value)
        return "psf4";
    if(k_drx_RetransmissionTimer_psf6 == value)
        return "psf6";
    if(k_drx_RetransmissionTimer_psf8 == value)
        return "psf8";
    if(k_drx_RetransmissionTimer_psf16 == value)
        return "psf16";
    if(k_drx_RetransmissionTimer_psf24 == value)
        return "psf24";
    if(k_drx_RetransmissionTimer_psf33 == value)
        return "psf33";
    return "";
}

uint64_t DRX_Config::setup::drx_RetransmissionTimer_NumberOfValues() const
{
    return 8;
}

std::string DRX_Config::setup::drx_RetransmissionTimer_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "drx_RetransmissionTimer = " + drx_RetransmissionTimer_ValueToString(drx_RetransmissionTimer_internal_value) + "\n";
    return out;
}

std::string DRX_Config::setup::drx_RetransmissionTimer_ToStringNoNewLines() const
{
    std::string out = "drx_RetransmissionTimer=" + drx_RetransmissionTimer_ValueToString(drx_RetransmissionTimer_internal_value) + ",";
    return out;
}

int DRX_Config::setup::drx_RetransmissionTimer_Clear()
{
    drx_RetransmissionTimer_present = false;
    return 0;
}

bool DRX_Config::setup::drx_RetransmissionTimer_IsPresent() const
{
    return drx_RetransmissionTimer_present;
}

int DRX_Config::setup::longDRX_CycleStartOffset_Pack(std::vector<uint8_t> &bits)
{
    if(!longDRX_CycleStartOffset_present)
    {
        printf("DRX_Config::setup::longDRX_CycleStartOffset_Pack() presence failure\n");
        return -1;
    }
    // Extension indicator

    // Choice
    for(uint32_t i=0; i<4; i++)
        bits.push_back((longDRX_CycleStartOffset_internal_choice >> (4-i-1)) & 1);

    // Fields
    if(longDRX_CycleStartOffset_internal_choice == k_longDRX_CycleStartOffset_sf10)
    {
        if(0 != longDRX_CycleStartOffset_sf10_Pack(bits))
        {
            printf("DRX_Config::setup::longDRX_CycleStartOffset_sf10 pack failure\n");
            return -1;
        }
    }
    if(longDRX_CycleStartOffset_internal_choice == k_longDRX_CycleStartOffset_sf20)
    {
        if(0 != longDRX_CycleStartOffset_sf20_Pack(bits))
        {
            printf("DRX_Config::setup::longDRX_CycleStartOffset_sf20 pack failure\n");
            return -1;
        }
    }
    if(longDRX_CycleStartOffset_internal_choice == k_longDRX_CycleStartOffset_sf32)
    {
        if(0 != longDRX_CycleStartOffset_sf32_Pack(bits))
        {
            printf("DRX_Config::setup::longDRX_CycleStartOffset_sf32 pack failure\n");
            return -1;
        }
    }
    if(longDRX_CycleStartOffset_internal_choice == k_longDRX_CycleStartOffset_sf40)
    {
        if(0 != longDRX_CycleStartOffset_sf40_Pack(bits))
        {
            printf("DRX_Config::setup::longDRX_CycleStartOffset_sf40 pack failure\n");
            return -1;
        }
    }
    if(longDRX_CycleStartOffset_internal_choice == k_longDRX_CycleStartOffset_sf64)
    {
        if(0 != longDRX_CycleStartOffset_sf64_Pack(bits))
        {
            printf("DRX_Config::setup::longDRX_CycleStartOffset_sf64 pack failure\n");
            return -1;
        }
    }
    if(longDRX_CycleStartOffset_internal_choice == k_longDRX_CycleStartOffset_sf80)
    {
        if(0 != longDRX_CycleStartOffset_sf80_Pack(bits))
        {
            printf("DRX_Config::setup::longDRX_CycleStartOffset_sf80 pack failure\n");
            return -1;
        }
    }
    if(longDRX_CycleStartOffset_internal_choice == k_longDRX_CycleStartOffset_sf128)
    {
        if(0 != longDRX_CycleStartOffset_sf128_Pack(bits))
        {
            printf("DRX_Config::setup::longDRX_CycleStartOffset_sf128 pack failure\n");
            return -1;
        }
    }
    if(longDRX_CycleStartOffset_internal_choice == k_longDRX_CycleStartOffset_sf160)
    {
        if(0 != longDRX_CycleStartOffset_sf160_Pack(bits))
        {
            printf("DRX_Config::setup::longDRX_CycleStartOffset_sf160 pack failure\n");
            return -1;
        }
    }
    if(longDRX_CycleStartOffset_internal_choice == k_longDRX_CycleStartOffset_sf256)
    {
        if(0 != longDRX_CycleStartOffset_sf256_Pack(bits))
        {
            printf("DRX_Config::setup::longDRX_CycleStartOffset_sf256 pack failure\n");
            return -1;
        }
    }
    if(longDRX_CycleStartOffset_internal_choice == k_longDRX_CycleStartOffset_sf320)
    {
        if(0 != longDRX_CycleStartOffset_sf320_Pack(bits))
        {
            printf("DRX_Config::setup::longDRX_CycleStartOffset_sf320 pack failure\n");
            return -1;
        }
    }
    if(longDRX_CycleStartOffset_internal_choice == k_longDRX_CycleStartOffset_sf512)
    {
        if(0 != longDRX_CycleStartOffset_sf512_Pack(bits))
        {
            printf("DRX_Config::setup::longDRX_CycleStartOffset_sf512 pack failure\n");
            return -1;
        }
    }
    if(longDRX_CycleStartOffset_internal_choice == k_longDRX_CycleStartOffset_sf640)
    {
        if(0 != longDRX_CycleStartOffset_sf640_Pack(bits))
        {
            printf("DRX_Config::setup::longDRX_CycleStartOffset_sf640 pack failure\n");
            return -1;
        }
    }
    if(longDRX_CycleStartOffset_internal_choice == k_longDRX_CycleStartOffset_sf1024)
    {
        if(0 != longDRX_CycleStartOffset_sf1024_Pack(bits))
        {
            printf("DRX_Config::setup::longDRX_CycleStartOffset_sf1024 pack failure\n");
            return -1;
        }
    }
    if(longDRX_CycleStartOffset_internal_choice == k_longDRX_CycleStartOffset_sf1280)
    {
        if(0 != longDRX_CycleStartOffset_sf1280_Pack(bits))
        {
            printf("DRX_Config::setup::longDRX_CycleStartOffset_sf1280 pack failure\n");
            return -1;
        }
    }
    if(longDRX_CycleStartOffset_internal_choice == k_longDRX_CycleStartOffset_sf2048)
    {
        if(0 != longDRX_CycleStartOffset_sf2048_Pack(bits))
        {
            printf("DRX_Config::setup::longDRX_CycleStartOffset_sf2048 pack failure\n");
            return -1;
        }
    }
    if(longDRX_CycleStartOffset_internal_choice == k_longDRX_CycleStartOffset_sf2560)
    {
        if(0 != longDRX_CycleStartOffset_sf2560_Pack(bits))
        {
            printf("DRX_Config::setup::longDRX_CycleStartOffset_sf2560 pack failure\n");
            return -1;
        }
    }
    return 0;
}

int DRX_Config::setup::longDRX_CycleStartOffset_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return longDRX_CycleStartOffset_Unpack(bits, idx);
}

int DRX_Config::setup::longDRX_CycleStartOffset_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 4) > bits.size())
    {
        printf("DRX_Config::setup::longDRX_CycleStartOffset_Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<4; i++)
        packed_val |= bits[idx++] << (4-i-1);

    if((DRX_Config::setup::longDRX_CycleStartOffset_Enum)packed_val > k_longDRX_CycleStartOffset_sf2560)
    {
        printf("DRX_Config::setup::longDRX_CycleStartOffset_Unpack() choice range failure\n");
        return -1;
    }
    longDRX_CycleStartOffset_internal_choice = (DRX_Config::setup::longDRX_CycleStartOffset_Enum)packed_val;
    longDRX_CycleStartOffset_present = true;

    // Fields
    if(longDRX_CycleStartOffset_internal_choice == k_longDRX_CycleStartOffset_sf10)
    {
        if(0 != longDRX_CycleStartOffset_sf10_Unpack(bits, idx))
        {
            printf("DRX_Config::setup::longDRX_CycleStartOffset_sf10 unpack failure\n");
            return -1;
        }
    }
    if(longDRX_CycleStartOffset_internal_choice == k_longDRX_CycleStartOffset_sf20)
    {
        if(0 != longDRX_CycleStartOffset_sf20_Unpack(bits, idx))
        {
            printf("DRX_Config::setup::longDRX_CycleStartOffset_sf20 unpack failure\n");
            return -1;
        }
    }
    if(longDRX_CycleStartOffset_internal_choice == k_longDRX_CycleStartOffset_sf32)
    {
        if(0 != longDRX_CycleStartOffset_sf32_Unpack(bits, idx))
        {
            printf("DRX_Config::setup::longDRX_CycleStartOffset_sf32 unpack failure\n");
            return -1;
        }
    }
    if(longDRX_CycleStartOffset_internal_choice == k_longDRX_CycleStartOffset_sf40)
    {
        if(0 != longDRX_CycleStartOffset_sf40_Unpack(bits, idx))
        {
            printf("DRX_Config::setup::longDRX_CycleStartOffset_sf40 unpack failure\n");
            return -1;
        }
    }
    if(longDRX_CycleStartOffset_internal_choice == k_longDRX_CycleStartOffset_sf64)
    {
        if(0 != longDRX_CycleStartOffset_sf64_Unpack(bits, idx))
        {
            printf("DRX_Config::setup::longDRX_CycleStartOffset_sf64 unpack failure\n");
            return -1;
        }
    }
    if(longDRX_CycleStartOffset_internal_choice == k_longDRX_CycleStartOffset_sf80)
    {
        if(0 != longDRX_CycleStartOffset_sf80_Unpack(bits, idx))
        {
            printf("DRX_Config::setup::longDRX_CycleStartOffset_sf80 unpack failure\n");
            return -1;
        }
    }
    if(longDRX_CycleStartOffset_internal_choice == k_longDRX_CycleStartOffset_sf128)
    {
        if(0 != longDRX_CycleStartOffset_sf128_Unpack(bits, idx))
        {
            printf("DRX_Config::setup::longDRX_CycleStartOffset_sf128 unpack failure\n");
            return -1;
        }
    }
    if(longDRX_CycleStartOffset_internal_choice == k_longDRX_CycleStartOffset_sf160)
    {
        if(0 != longDRX_CycleStartOffset_sf160_Unpack(bits, idx))
        {
            printf("DRX_Config::setup::longDRX_CycleStartOffset_sf160 unpack failure\n");
            return -1;
        }
    }
    if(longDRX_CycleStartOffset_internal_choice == k_longDRX_CycleStartOffset_sf256)
    {
        if(0 != longDRX_CycleStartOffset_sf256_Unpack(bits, idx))
        {
            printf("DRX_Config::setup::longDRX_CycleStartOffset_sf256 unpack failure\n");
            return -1;
        }
    }
    if(longDRX_CycleStartOffset_internal_choice == k_longDRX_CycleStartOffset_sf320)
    {
        if(0 != longDRX_CycleStartOffset_sf320_Unpack(bits, idx))
        {
            printf("DRX_Config::setup::longDRX_CycleStartOffset_sf320 unpack failure\n");
            return -1;
        }
    }
    if(longDRX_CycleStartOffset_internal_choice == k_longDRX_CycleStartOffset_sf512)
    {
        if(0 != longDRX_CycleStartOffset_sf512_Unpack(bits, idx))
        {
            printf("DRX_Config::setup::longDRX_CycleStartOffset_sf512 unpack failure\n");
            return -1;
        }
    }
    if(longDRX_CycleStartOffset_internal_choice == k_longDRX_CycleStartOffset_sf640)
    {
        if(0 != longDRX_CycleStartOffset_sf640_Unpack(bits, idx))
        {
            printf("DRX_Config::setup::longDRX_CycleStartOffset_sf640 unpack failure\n");
            return -1;
        }
    }
    if(longDRX_CycleStartOffset_internal_choice == k_longDRX_CycleStartOffset_sf1024)
    {
        if(0 != longDRX_CycleStartOffset_sf1024_Unpack(bits, idx))
        {
            printf("DRX_Config::setup::longDRX_CycleStartOffset_sf1024 unpack failure\n");
            return -1;
        }
    }
    if(longDRX_CycleStartOffset_internal_choice == k_longDRX_CycleStartOffset_sf1280)
    {
        if(0 != longDRX_CycleStartOffset_sf1280_Unpack(bits, idx))
        {
            printf("DRX_Config::setup::longDRX_CycleStartOffset_sf1280 unpack failure\n");
            return -1;
        }
    }
    if(longDRX_CycleStartOffset_internal_choice == k_longDRX_CycleStartOffset_sf2048)
    {
        if(0 != longDRX_CycleStartOffset_sf2048_Unpack(bits, idx))
        {
            printf("DRX_Config::setup::longDRX_CycleStartOffset_sf2048 unpack failure\n");
            return -1;
        }
    }
    if(longDRX_CycleStartOffset_internal_choice == k_longDRX_CycleStartOffset_sf2560)
    {
        if(0 != longDRX_CycleStartOffset_sf2560_Unpack(bits, idx))
        {
            printf("DRX_Config::setup::longDRX_CycleStartOffset_sf2560 unpack failure\n");
            return -1;
        }
    }
    return 0;
}

DRX_Config::setup::longDRX_CycleStartOffset_Enum DRX_Config::setup::longDRX_CycleStartOffset_Choice() const
{
    if(longDRX_CycleStartOffset_present)
        return longDRX_CycleStartOffset_internal_choice;
    return (DRX_Config::setup::longDRX_CycleStartOffset_Enum)0;
}

int DRX_Config::setup::longDRX_CycleStartOffset_SetChoice(DRX_Config::setup::longDRX_CycleStartOffset_Enum choice)
{
    longDRX_CycleStartOffset_internal_choice = choice;
    longDRX_CycleStartOffset_present = true;
    return 0;
}

std::string DRX_Config::setup::longDRX_CycleStartOffset_ChoiceToString(longDRX_CycleStartOffset_Enum value) const
{
    if(k_longDRX_CycleStartOffset_sf10 == value)
        return "longDRX_CycleStartOffset_sf10";
    if(k_longDRX_CycleStartOffset_sf20 == value)
        return "longDRX_CycleStartOffset_sf20";
    if(k_longDRX_CycleStartOffset_sf32 == value)
        return "longDRX_CycleStartOffset_sf32";
    if(k_longDRX_CycleStartOffset_sf40 == value)
        return "longDRX_CycleStartOffset_sf40";
    if(k_longDRX_CycleStartOffset_sf64 == value)
        return "longDRX_CycleStartOffset_sf64";
    if(k_longDRX_CycleStartOffset_sf80 == value)
        return "longDRX_CycleStartOffset_sf80";
    if(k_longDRX_CycleStartOffset_sf128 == value)
        return "longDRX_CycleStartOffset_sf128";
    if(k_longDRX_CycleStartOffset_sf160 == value)
        return "longDRX_CycleStartOffset_sf160";
    if(k_longDRX_CycleStartOffset_sf256 == value)
        return "longDRX_CycleStartOffset_sf256";
    if(k_longDRX_CycleStartOffset_sf320 == value)
        return "longDRX_CycleStartOffset_sf320";
    if(k_longDRX_CycleStartOffset_sf512 == value)
        return "longDRX_CycleStartOffset_sf512";
    if(k_longDRX_CycleStartOffset_sf640 == value)
        return "longDRX_CycleStartOffset_sf640";
    if(k_longDRX_CycleStartOffset_sf1024 == value)
        return "longDRX_CycleStartOffset_sf1024";
    if(k_longDRX_CycleStartOffset_sf1280 == value)
        return "longDRX_CycleStartOffset_sf1280";
    if(k_longDRX_CycleStartOffset_sf2048 == value)
        return "longDRX_CycleStartOffset_sf2048";
    if(k_longDRX_CycleStartOffset_sf2560 == value)
        return "longDRX_CycleStartOffset_sf2560";
    return "";
}

uint64_t DRX_Config::setup::longDRX_CycleStartOffset_NumberOfChoices() const
{
    return 16;
}

std::string DRX_Config::setup::longDRX_CycleStartOffset_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "longDRX_CycleStartOffset = " + longDRX_CycleStartOffset_ChoiceToString(longDRX_CycleStartOffset_internal_choice) + ":\n";
    if(longDRX_CycleStartOffset_internal_choice == k_longDRX_CycleStartOffset_sf10)
        out += longDRX_CycleStartOffset_sf10_ToString(indent+1);
    if(longDRX_CycleStartOffset_internal_choice == k_longDRX_CycleStartOffset_sf20)
        out += longDRX_CycleStartOffset_sf20_ToString(indent+1);
    if(longDRX_CycleStartOffset_internal_choice == k_longDRX_CycleStartOffset_sf32)
        out += longDRX_CycleStartOffset_sf32_ToString(indent+1);
    if(longDRX_CycleStartOffset_internal_choice == k_longDRX_CycleStartOffset_sf40)
        out += longDRX_CycleStartOffset_sf40_ToString(indent+1);
    if(longDRX_CycleStartOffset_internal_choice == k_longDRX_CycleStartOffset_sf64)
        out += longDRX_CycleStartOffset_sf64_ToString(indent+1);
    if(longDRX_CycleStartOffset_internal_choice == k_longDRX_CycleStartOffset_sf80)
        out += longDRX_CycleStartOffset_sf80_ToString(indent+1);
    if(longDRX_CycleStartOffset_internal_choice == k_longDRX_CycleStartOffset_sf128)
        out += longDRX_CycleStartOffset_sf128_ToString(indent+1);
    if(longDRX_CycleStartOffset_internal_choice == k_longDRX_CycleStartOffset_sf160)
        out += longDRX_CycleStartOffset_sf160_ToString(indent+1);
    if(longDRX_CycleStartOffset_internal_choice == k_longDRX_CycleStartOffset_sf256)
        out += longDRX_CycleStartOffset_sf256_ToString(indent+1);
    if(longDRX_CycleStartOffset_internal_choice == k_longDRX_CycleStartOffset_sf320)
        out += longDRX_CycleStartOffset_sf320_ToString(indent+1);
    if(longDRX_CycleStartOffset_internal_choice == k_longDRX_CycleStartOffset_sf512)
        out += longDRX_CycleStartOffset_sf512_ToString(indent+1);
    if(longDRX_CycleStartOffset_internal_choice == k_longDRX_CycleStartOffset_sf640)
        out += longDRX_CycleStartOffset_sf640_ToString(indent+1);
    if(longDRX_CycleStartOffset_internal_choice == k_longDRX_CycleStartOffset_sf1024)
        out += longDRX_CycleStartOffset_sf1024_ToString(indent+1);
    if(longDRX_CycleStartOffset_internal_choice == k_longDRX_CycleStartOffset_sf1280)
        out += longDRX_CycleStartOffset_sf1280_ToString(indent+1);
    if(longDRX_CycleStartOffset_internal_choice == k_longDRX_CycleStartOffset_sf2048)
        out += longDRX_CycleStartOffset_sf2048_ToString(indent+1);
    if(longDRX_CycleStartOffset_internal_choice == k_longDRX_CycleStartOffset_sf2560)
        out += longDRX_CycleStartOffset_sf2560_ToString(indent+1);
    return out;
}

std::string DRX_Config::setup::longDRX_CycleStartOffset_ToStringNoNewLines() const
{
    std::string out = "longDRX_CycleStartOffset=" + longDRX_CycleStartOffset_ChoiceToString(longDRX_CycleStartOffset_internal_choice) + ",";
    if(longDRX_CycleStartOffset_internal_choice == k_longDRX_CycleStartOffset_sf10)
        out += longDRX_CycleStartOffset_sf10_ToStringNoNewLines();
    if(longDRX_CycleStartOffset_internal_choice == k_longDRX_CycleStartOffset_sf20)
        out += longDRX_CycleStartOffset_sf20_ToStringNoNewLines();
    if(longDRX_CycleStartOffset_internal_choice == k_longDRX_CycleStartOffset_sf32)
        out += longDRX_CycleStartOffset_sf32_ToStringNoNewLines();
    if(longDRX_CycleStartOffset_internal_choice == k_longDRX_CycleStartOffset_sf40)
        out += longDRX_CycleStartOffset_sf40_ToStringNoNewLines();
    if(longDRX_CycleStartOffset_internal_choice == k_longDRX_CycleStartOffset_sf64)
        out += longDRX_CycleStartOffset_sf64_ToStringNoNewLines();
    if(longDRX_CycleStartOffset_internal_choice == k_longDRX_CycleStartOffset_sf80)
        out += longDRX_CycleStartOffset_sf80_ToStringNoNewLines();
    if(longDRX_CycleStartOffset_internal_choice == k_longDRX_CycleStartOffset_sf128)
        out += longDRX_CycleStartOffset_sf128_ToStringNoNewLines();
    if(longDRX_CycleStartOffset_internal_choice == k_longDRX_CycleStartOffset_sf160)
        out += longDRX_CycleStartOffset_sf160_ToStringNoNewLines();
    if(longDRX_CycleStartOffset_internal_choice == k_longDRX_CycleStartOffset_sf256)
        out += longDRX_CycleStartOffset_sf256_ToStringNoNewLines();
    if(longDRX_CycleStartOffset_internal_choice == k_longDRX_CycleStartOffset_sf320)
        out += longDRX_CycleStartOffset_sf320_ToStringNoNewLines();
    if(longDRX_CycleStartOffset_internal_choice == k_longDRX_CycleStartOffset_sf512)
        out += longDRX_CycleStartOffset_sf512_ToStringNoNewLines();
    if(longDRX_CycleStartOffset_internal_choice == k_longDRX_CycleStartOffset_sf640)
        out += longDRX_CycleStartOffset_sf640_ToStringNoNewLines();
    if(longDRX_CycleStartOffset_internal_choice == k_longDRX_CycleStartOffset_sf1024)
        out += longDRX_CycleStartOffset_sf1024_ToStringNoNewLines();
    if(longDRX_CycleStartOffset_internal_choice == k_longDRX_CycleStartOffset_sf1280)
        out += longDRX_CycleStartOffset_sf1280_ToStringNoNewLines();
    if(longDRX_CycleStartOffset_internal_choice == k_longDRX_CycleStartOffset_sf2048)
        out += longDRX_CycleStartOffset_sf2048_ToStringNoNewLines();
    if(longDRX_CycleStartOffset_internal_choice == k_longDRX_CycleStartOffset_sf2560)
        out += longDRX_CycleStartOffset_sf2560_ToStringNoNewLines();
    return out;
}

int DRX_Config::setup::longDRX_CycleStartOffset_Clear()
{
    longDRX_CycleStartOffset_present = false;
    return 0;
}

bool DRX_Config::setup::longDRX_CycleStartOffset_IsPresent() const
{
    return longDRX_CycleStartOffset_present;
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf10_Pack(std::vector<uint8_t> &bits)
{
    if(!longDRX_CycleStartOffset_sf10_present)
    {
        printf("DRX_Config::setup::longDRX_CycleStartOffset_sf10_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = longDRX_CycleStartOffset_sf10_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (9 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return longDRX_CycleStartOffset_sf10_Unpack(bits, idx);
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (9 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("DRX_Config::setup::longDRX_CycleStartOffset_sf10_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    longDRX_CycleStartOffset_sf10_internal_value = packed_val + 0;
    longDRX_CycleStartOffset_sf10_present = true;
    return 0;
}

int64_t DRX_Config::setup::longDRX_CycleStartOffset_sf10_Value() const
{
    if(longDRX_CycleStartOffset_sf10_present)
        return longDRX_CycleStartOffset_sf10_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf10_SetValue(int64_t value)
{
    if(value < 0 || value > 9)
    {
        printf("DRX_Config::setup::longDRX_CycleStartOffset_sf10_SetValue() range failure\n");
        return -1;
    }
    longDRX_CycleStartOffset_sf10_internal_value = value;
    longDRX_CycleStartOffset_sf10_present = true;
    return 0;
}

std::string DRX_Config::setup::longDRX_CycleStartOffset_sf10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "sf10 = " + std::to_string(longDRX_CycleStartOffset_sf10_internal_value) + "\n";
    return out;
}

std::string DRX_Config::setup::longDRX_CycleStartOffset_sf10_ToStringNoNewLines() const
{
    std::string out = "sf10=" + std::to_string(longDRX_CycleStartOffset_sf10_internal_value) + ",";
    return out;
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf10_Clear()
{
    longDRX_CycleStartOffset_sf10_present = false;
    return 0;
}

bool DRX_Config::setup::longDRX_CycleStartOffset_sf10_IsPresent() const
{
    return longDRX_CycleStartOffset_sf10_present;
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf20_Pack(std::vector<uint8_t> &bits)
{
    if(!longDRX_CycleStartOffset_sf20_present)
    {
        printf("DRX_Config::setup::longDRX_CycleStartOffset_sf20_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = longDRX_CycleStartOffset_sf20_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (19 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf20_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return longDRX_CycleStartOffset_sf20_Unpack(bits, idx);
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf20_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (19 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("DRX_Config::setup::longDRX_CycleStartOffset_sf20_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    longDRX_CycleStartOffset_sf20_internal_value = packed_val + 0;
    longDRX_CycleStartOffset_sf20_present = true;
    return 0;
}

int64_t DRX_Config::setup::longDRX_CycleStartOffset_sf20_Value() const
{
    if(longDRX_CycleStartOffset_sf20_present)
        return longDRX_CycleStartOffset_sf20_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf20_SetValue(int64_t value)
{
    if(value < 0 || value > 19)
    {
        printf("DRX_Config::setup::longDRX_CycleStartOffset_sf20_SetValue() range failure\n");
        return -1;
    }
    longDRX_CycleStartOffset_sf20_internal_value = value;
    longDRX_CycleStartOffset_sf20_present = true;
    return 0;
}

std::string DRX_Config::setup::longDRX_CycleStartOffset_sf20_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "sf20 = " + std::to_string(longDRX_CycleStartOffset_sf20_internal_value) + "\n";
    return out;
}

std::string DRX_Config::setup::longDRX_CycleStartOffset_sf20_ToStringNoNewLines() const
{
    std::string out = "sf20=" + std::to_string(longDRX_CycleStartOffset_sf20_internal_value) + ",";
    return out;
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf20_Clear()
{
    longDRX_CycleStartOffset_sf20_present = false;
    return 0;
}

bool DRX_Config::setup::longDRX_CycleStartOffset_sf20_IsPresent() const
{
    return longDRX_CycleStartOffset_sf20_present;
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf32_Pack(std::vector<uint8_t> &bits)
{
    if(!longDRX_CycleStartOffset_sf32_present)
    {
        printf("DRX_Config::setup::longDRX_CycleStartOffset_sf32_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = longDRX_CycleStartOffset_sf32_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (31 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf32_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return longDRX_CycleStartOffset_sf32_Unpack(bits, idx);
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf32_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (31 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("DRX_Config::setup::longDRX_CycleStartOffset_sf32_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    longDRX_CycleStartOffset_sf32_internal_value = packed_val + 0;
    longDRX_CycleStartOffset_sf32_present = true;
    return 0;
}

int64_t DRX_Config::setup::longDRX_CycleStartOffset_sf32_Value() const
{
    if(longDRX_CycleStartOffset_sf32_present)
        return longDRX_CycleStartOffset_sf32_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf32_SetValue(int64_t value)
{
    if(value < 0 || value > 31)
    {
        printf("DRX_Config::setup::longDRX_CycleStartOffset_sf32_SetValue() range failure\n");
        return -1;
    }
    longDRX_CycleStartOffset_sf32_internal_value = value;
    longDRX_CycleStartOffset_sf32_present = true;
    return 0;
}

std::string DRX_Config::setup::longDRX_CycleStartOffset_sf32_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "sf32 = " + std::to_string(longDRX_CycleStartOffset_sf32_internal_value) + "\n";
    return out;
}

std::string DRX_Config::setup::longDRX_CycleStartOffset_sf32_ToStringNoNewLines() const
{
    std::string out = "sf32=" + std::to_string(longDRX_CycleStartOffset_sf32_internal_value) + ",";
    return out;
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf32_Clear()
{
    longDRX_CycleStartOffset_sf32_present = false;
    return 0;
}

bool DRX_Config::setup::longDRX_CycleStartOffset_sf32_IsPresent() const
{
    return longDRX_CycleStartOffset_sf32_present;
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf40_Pack(std::vector<uint8_t> &bits)
{
    if(!longDRX_CycleStartOffset_sf40_present)
    {
        printf("DRX_Config::setup::longDRX_CycleStartOffset_sf40_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = longDRX_CycleStartOffset_sf40_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (39 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf40_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return longDRX_CycleStartOffset_sf40_Unpack(bits, idx);
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf40_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (39 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("DRX_Config::setup::longDRX_CycleStartOffset_sf40_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    longDRX_CycleStartOffset_sf40_internal_value = packed_val + 0;
    longDRX_CycleStartOffset_sf40_present = true;
    return 0;
}

int64_t DRX_Config::setup::longDRX_CycleStartOffset_sf40_Value() const
{
    if(longDRX_CycleStartOffset_sf40_present)
        return longDRX_CycleStartOffset_sf40_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf40_SetValue(int64_t value)
{
    if(value < 0 || value > 39)
    {
        printf("DRX_Config::setup::longDRX_CycleStartOffset_sf40_SetValue() range failure\n");
        return -1;
    }
    longDRX_CycleStartOffset_sf40_internal_value = value;
    longDRX_CycleStartOffset_sf40_present = true;
    return 0;
}

std::string DRX_Config::setup::longDRX_CycleStartOffset_sf40_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "sf40 = " + std::to_string(longDRX_CycleStartOffset_sf40_internal_value) + "\n";
    return out;
}

std::string DRX_Config::setup::longDRX_CycleStartOffset_sf40_ToStringNoNewLines() const
{
    std::string out = "sf40=" + std::to_string(longDRX_CycleStartOffset_sf40_internal_value) + ",";
    return out;
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf40_Clear()
{
    longDRX_CycleStartOffset_sf40_present = false;
    return 0;
}

bool DRX_Config::setup::longDRX_CycleStartOffset_sf40_IsPresent() const
{
    return longDRX_CycleStartOffset_sf40_present;
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf64_Pack(std::vector<uint8_t> &bits)
{
    if(!longDRX_CycleStartOffset_sf64_present)
    {
        printf("DRX_Config::setup::longDRX_CycleStartOffset_sf64_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = longDRX_CycleStartOffset_sf64_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (63 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf64_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return longDRX_CycleStartOffset_sf64_Unpack(bits, idx);
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf64_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (63 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("DRX_Config::setup::longDRX_CycleStartOffset_sf64_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    longDRX_CycleStartOffset_sf64_internal_value = packed_val + 0;
    longDRX_CycleStartOffset_sf64_present = true;
    return 0;
}

int64_t DRX_Config::setup::longDRX_CycleStartOffset_sf64_Value() const
{
    if(longDRX_CycleStartOffset_sf64_present)
        return longDRX_CycleStartOffset_sf64_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf64_SetValue(int64_t value)
{
    if(value < 0 || value > 63)
    {
        printf("DRX_Config::setup::longDRX_CycleStartOffset_sf64_SetValue() range failure\n");
        return -1;
    }
    longDRX_CycleStartOffset_sf64_internal_value = value;
    longDRX_CycleStartOffset_sf64_present = true;
    return 0;
}

std::string DRX_Config::setup::longDRX_CycleStartOffset_sf64_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "sf64 = " + std::to_string(longDRX_CycleStartOffset_sf64_internal_value) + "\n";
    return out;
}

std::string DRX_Config::setup::longDRX_CycleStartOffset_sf64_ToStringNoNewLines() const
{
    std::string out = "sf64=" + std::to_string(longDRX_CycleStartOffset_sf64_internal_value) + ",";
    return out;
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf64_Clear()
{
    longDRX_CycleStartOffset_sf64_present = false;
    return 0;
}

bool DRX_Config::setup::longDRX_CycleStartOffset_sf64_IsPresent() const
{
    return longDRX_CycleStartOffset_sf64_present;
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf80_Pack(std::vector<uint8_t> &bits)
{
    if(!longDRX_CycleStartOffset_sf80_present)
    {
        printf("DRX_Config::setup::longDRX_CycleStartOffset_sf80_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = longDRX_CycleStartOffset_sf80_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (79 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf80_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return longDRX_CycleStartOffset_sf80_Unpack(bits, idx);
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf80_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (79 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("DRX_Config::setup::longDRX_CycleStartOffset_sf80_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    longDRX_CycleStartOffset_sf80_internal_value = packed_val + 0;
    longDRX_CycleStartOffset_sf80_present = true;
    return 0;
}

int64_t DRX_Config::setup::longDRX_CycleStartOffset_sf80_Value() const
{
    if(longDRX_CycleStartOffset_sf80_present)
        return longDRX_CycleStartOffset_sf80_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf80_SetValue(int64_t value)
{
    if(value < 0 || value > 79)
    {
        printf("DRX_Config::setup::longDRX_CycleStartOffset_sf80_SetValue() range failure\n");
        return -1;
    }
    longDRX_CycleStartOffset_sf80_internal_value = value;
    longDRX_CycleStartOffset_sf80_present = true;
    return 0;
}

std::string DRX_Config::setup::longDRX_CycleStartOffset_sf80_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "sf80 = " + std::to_string(longDRX_CycleStartOffset_sf80_internal_value) + "\n";
    return out;
}

std::string DRX_Config::setup::longDRX_CycleStartOffset_sf80_ToStringNoNewLines() const
{
    std::string out = "sf80=" + std::to_string(longDRX_CycleStartOffset_sf80_internal_value) + ",";
    return out;
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf80_Clear()
{
    longDRX_CycleStartOffset_sf80_present = false;
    return 0;
}

bool DRX_Config::setup::longDRX_CycleStartOffset_sf80_IsPresent() const
{
    return longDRX_CycleStartOffset_sf80_present;
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf128_Pack(std::vector<uint8_t> &bits)
{
    if(!longDRX_CycleStartOffset_sf128_present)
    {
        printf("DRX_Config::setup::longDRX_CycleStartOffset_sf128_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = longDRX_CycleStartOffset_sf128_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (127 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf128_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return longDRX_CycleStartOffset_sf128_Unpack(bits, idx);
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf128_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (127 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("DRX_Config::setup::longDRX_CycleStartOffset_sf128_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    longDRX_CycleStartOffset_sf128_internal_value = packed_val + 0;
    longDRX_CycleStartOffset_sf128_present = true;
    return 0;
}

int64_t DRX_Config::setup::longDRX_CycleStartOffset_sf128_Value() const
{
    if(longDRX_CycleStartOffset_sf128_present)
        return longDRX_CycleStartOffset_sf128_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf128_SetValue(int64_t value)
{
    if(value < 0 || value > 127)
    {
        printf("DRX_Config::setup::longDRX_CycleStartOffset_sf128_SetValue() range failure\n");
        return -1;
    }
    longDRX_CycleStartOffset_sf128_internal_value = value;
    longDRX_CycleStartOffset_sf128_present = true;
    return 0;
}

std::string DRX_Config::setup::longDRX_CycleStartOffset_sf128_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "sf128 = " + std::to_string(longDRX_CycleStartOffset_sf128_internal_value) + "\n";
    return out;
}

std::string DRX_Config::setup::longDRX_CycleStartOffset_sf128_ToStringNoNewLines() const
{
    std::string out = "sf128=" + std::to_string(longDRX_CycleStartOffset_sf128_internal_value) + ",";
    return out;
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf128_Clear()
{
    longDRX_CycleStartOffset_sf128_present = false;
    return 0;
}

bool DRX_Config::setup::longDRX_CycleStartOffset_sf128_IsPresent() const
{
    return longDRX_CycleStartOffset_sf128_present;
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf160_Pack(std::vector<uint8_t> &bits)
{
    if(!longDRX_CycleStartOffset_sf160_present)
    {
        printf("DRX_Config::setup::longDRX_CycleStartOffset_sf160_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = longDRX_CycleStartOffset_sf160_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (159 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf160_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return longDRX_CycleStartOffset_sf160_Unpack(bits, idx);
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf160_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (159 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("DRX_Config::setup::longDRX_CycleStartOffset_sf160_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    longDRX_CycleStartOffset_sf160_internal_value = packed_val + 0;
    longDRX_CycleStartOffset_sf160_present = true;
    return 0;
}

int64_t DRX_Config::setup::longDRX_CycleStartOffset_sf160_Value() const
{
    if(longDRX_CycleStartOffset_sf160_present)
        return longDRX_CycleStartOffset_sf160_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf160_SetValue(int64_t value)
{
    if(value < 0 || value > 159)
    {
        printf("DRX_Config::setup::longDRX_CycleStartOffset_sf160_SetValue() range failure\n");
        return -1;
    }
    longDRX_CycleStartOffset_sf160_internal_value = value;
    longDRX_CycleStartOffset_sf160_present = true;
    return 0;
}

std::string DRX_Config::setup::longDRX_CycleStartOffset_sf160_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "sf160 = " + std::to_string(longDRX_CycleStartOffset_sf160_internal_value) + "\n";
    return out;
}

std::string DRX_Config::setup::longDRX_CycleStartOffset_sf160_ToStringNoNewLines() const
{
    std::string out = "sf160=" + std::to_string(longDRX_CycleStartOffset_sf160_internal_value) + ",";
    return out;
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf160_Clear()
{
    longDRX_CycleStartOffset_sf160_present = false;
    return 0;
}

bool DRX_Config::setup::longDRX_CycleStartOffset_sf160_IsPresent() const
{
    return longDRX_CycleStartOffset_sf160_present;
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf256_Pack(std::vector<uint8_t> &bits)
{
    if(!longDRX_CycleStartOffset_sf256_present)
    {
        printf("DRX_Config::setup::longDRX_CycleStartOffset_sf256_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = longDRX_CycleStartOffset_sf256_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (255 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf256_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return longDRX_CycleStartOffset_sf256_Unpack(bits, idx);
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf256_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (255 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("DRX_Config::setup::longDRX_CycleStartOffset_sf256_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    longDRX_CycleStartOffset_sf256_internal_value = packed_val + 0;
    longDRX_CycleStartOffset_sf256_present = true;
    return 0;
}

int64_t DRX_Config::setup::longDRX_CycleStartOffset_sf256_Value() const
{
    if(longDRX_CycleStartOffset_sf256_present)
        return longDRX_CycleStartOffset_sf256_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf256_SetValue(int64_t value)
{
    if(value < 0 || value > 255)
    {
        printf("DRX_Config::setup::longDRX_CycleStartOffset_sf256_SetValue() range failure\n");
        return -1;
    }
    longDRX_CycleStartOffset_sf256_internal_value = value;
    longDRX_CycleStartOffset_sf256_present = true;
    return 0;
}

std::string DRX_Config::setup::longDRX_CycleStartOffset_sf256_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "sf256 = " + std::to_string(longDRX_CycleStartOffset_sf256_internal_value) + "\n";
    return out;
}

std::string DRX_Config::setup::longDRX_CycleStartOffset_sf256_ToStringNoNewLines() const
{
    std::string out = "sf256=" + std::to_string(longDRX_CycleStartOffset_sf256_internal_value) + ",";
    return out;
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf256_Clear()
{
    longDRX_CycleStartOffset_sf256_present = false;
    return 0;
}

bool DRX_Config::setup::longDRX_CycleStartOffset_sf256_IsPresent() const
{
    return longDRX_CycleStartOffset_sf256_present;
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf320_Pack(std::vector<uint8_t> &bits)
{
    if(!longDRX_CycleStartOffset_sf320_present)
    {
        printf("DRX_Config::setup::longDRX_CycleStartOffset_sf320_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = longDRX_CycleStartOffset_sf320_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (319 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf320_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return longDRX_CycleStartOffset_sf320_Unpack(bits, idx);
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf320_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (319 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("DRX_Config::setup::longDRX_CycleStartOffset_sf320_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    longDRX_CycleStartOffset_sf320_internal_value = packed_val + 0;
    longDRX_CycleStartOffset_sf320_present = true;
    return 0;
}

int64_t DRX_Config::setup::longDRX_CycleStartOffset_sf320_Value() const
{
    if(longDRX_CycleStartOffset_sf320_present)
        return longDRX_CycleStartOffset_sf320_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf320_SetValue(int64_t value)
{
    if(value < 0 || value > 319)
    {
        printf("DRX_Config::setup::longDRX_CycleStartOffset_sf320_SetValue() range failure\n");
        return -1;
    }
    longDRX_CycleStartOffset_sf320_internal_value = value;
    longDRX_CycleStartOffset_sf320_present = true;
    return 0;
}

std::string DRX_Config::setup::longDRX_CycleStartOffset_sf320_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "sf320 = " + std::to_string(longDRX_CycleStartOffset_sf320_internal_value) + "\n";
    return out;
}

std::string DRX_Config::setup::longDRX_CycleStartOffset_sf320_ToStringNoNewLines() const
{
    std::string out = "sf320=" + std::to_string(longDRX_CycleStartOffset_sf320_internal_value) + ",";
    return out;
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf320_Clear()
{
    longDRX_CycleStartOffset_sf320_present = false;
    return 0;
}

bool DRX_Config::setup::longDRX_CycleStartOffset_sf320_IsPresent() const
{
    return longDRX_CycleStartOffset_sf320_present;
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf512_Pack(std::vector<uint8_t> &bits)
{
    if(!longDRX_CycleStartOffset_sf512_present)
    {
        printf("DRX_Config::setup::longDRX_CycleStartOffset_sf512_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = longDRX_CycleStartOffset_sf512_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (511 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf512_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return longDRX_CycleStartOffset_sf512_Unpack(bits, idx);
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf512_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (511 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("DRX_Config::setup::longDRX_CycleStartOffset_sf512_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    longDRX_CycleStartOffset_sf512_internal_value = packed_val + 0;
    longDRX_CycleStartOffset_sf512_present = true;
    return 0;
}

int64_t DRX_Config::setup::longDRX_CycleStartOffset_sf512_Value() const
{
    if(longDRX_CycleStartOffset_sf512_present)
        return longDRX_CycleStartOffset_sf512_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf512_SetValue(int64_t value)
{
    if(value < 0 || value > 511)
    {
        printf("DRX_Config::setup::longDRX_CycleStartOffset_sf512_SetValue() range failure\n");
        return -1;
    }
    longDRX_CycleStartOffset_sf512_internal_value = value;
    longDRX_CycleStartOffset_sf512_present = true;
    return 0;
}

std::string DRX_Config::setup::longDRX_CycleStartOffset_sf512_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "sf512 = " + std::to_string(longDRX_CycleStartOffset_sf512_internal_value) + "\n";
    return out;
}

std::string DRX_Config::setup::longDRX_CycleStartOffset_sf512_ToStringNoNewLines() const
{
    std::string out = "sf512=" + std::to_string(longDRX_CycleStartOffset_sf512_internal_value) + ",";
    return out;
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf512_Clear()
{
    longDRX_CycleStartOffset_sf512_present = false;
    return 0;
}

bool DRX_Config::setup::longDRX_CycleStartOffset_sf512_IsPresent() const
{
    return longDRX_CycleStartOffset_sf512_present;
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf640_Pack(std::vector<uint8_t> &bits)
{
    if(!longDRX_CycleStartOffset_sf640_present)
    {
        printf("DRX_Config::setup::longDRX_CycleStartOffset_sf640_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = longDRX_CycleStartOffset_sf640_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (639 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf640_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return longDRX_CycleStartOffset_sf640_Unpack(bits, idx);
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf640_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (639 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("DRX_Config::setup::longDRX_CycleStartOffset_sf640_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    longDRX_CycleStartOffset_sf640_internal_value = packed_val + 0;
    longDRX_CycleStartOffset_sf640_present = true;
    return 0;
}

int64_t DRX_Config::setup::longDRX_CycleStartOffset_sf640_Value() const
{
    if(longDRX_CycleStartOffset_sf640_present)
        return longDRX_CycleStartOffset_sf640_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf640_SetValue(int64_t value)
{
    if(value < 0 || value > 639)
    {
        printf("DRX_Config::setup::longDRX_CycleStartOffset_sf640_SetValue() range failure\n");
        return -1;
    }
    longDRX_CycleStartOffset_sf640_internal_value = value;
    longDRX_CycleStartOffset_sf640_present = true;
    return 0;
}

std::string DRX_Config::setup::longDRX_CycleStartOffset_sf640_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "sf640 = " + std::to_string(longDRX_CycleStartOffset_sf640_internal_value) + "\n";
    return out;
}

std::string DRX_Config::setup::longDRX_CycleStartOffset_sf640_ToStringNoNewLines() const
{
    std::string out = "sf640=" + std::to_string(longDRX_CycleStartOffset_sf640_internal_value) + ",";
    return out;
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf640_Clear()
{
    longDRX_CycleStartOffset_sf640_present = false;
    return 0;
}

bool DRX_Config::setup::longDRX_CycleStartOffset_sf640_IsPresent() const
{
    return longDRX_CycleStartOffset_sf640_present;
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf1024_Pack(std::vector<uint8_t> &bits)
{
    if(!longDRX_CycleStartOffset_sf1024_present)
    {
        printf("DRX_Config::setup::longDRX_CycleStartOffset_sf1024_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = longDRX_CycleStartOffset_sf1024_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (1023 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf1024_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return longDRX_CycleStartOffset_sf1024_Unpack(bits, idx);
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf1024_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (1023 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("DRX_Config::setup::longDRX_CycleStartOffset_sf1024_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    longDRX_CycleStartOffset_sf1024_internal_value = packed_val + 0;
    longDRX_CycleStartOffset_sf1024_present = true;
    return 0;
}

int64_t DRX_Config::setup::longDRX_CycleStartOffset_sf1024_Value() const
{
    if(longDRX_CycleStartOffset_sf1024_present)
        return longDRX_CycleStartOffset_sf1024_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf1024_SetValue(int64_t value)
{
    if(value < 0 || value > 1023)
    {
        printf("DRX_Config::setup::longDRX_CycleStartOffset_sf1024_SetValue() range failure\n");
        return -1;
    }
    longDRX_CycleStartOffset_sf1024_internal_value = value;
    longDRX_CycleStartOffset_sf1024_present = true;
    return 0;
}

std::string DRX_Config::setup::longDRX_CycleStartOffset_sf1024_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "sf1024 = " + std::to_string(longDRX_CycleStartOffset_sf1024_internal_value) + "\n";
    return out;
}

std::string DRX_Config::setup::longDRX_CycleStartOffset_sf1024_ToStringNoNewLines() const
{
    std::string out = "sf1024=" + std::to_string(longDRX_CycleStartOffset_sf1024_internal_value) + ",";
    return out;
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf1024_Clear()
{
    longDRX_CycleStartOffset_sf1024_present = false;
    return 0;
}

bool DRX_Config::setup::longDRX_CycleStartOffset_sf1024_IsPresent() const
{
    return longDRX_CycleStartOffset_sf1024_present;
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf1280_Pack(std::vector<uint8_t> &bits)
{
    if(!longDRX_CycleStartOffset_sf1280_present)
    {
        printf("DRX_Config::setup::longDRX_CycleStartOffset_sf1280_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = longDRX_CycleStartOffset_sf1280_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (1279 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf1280_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return longDRX_CycleStartOffset_sf1280_Unpack(bits, idx);
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf1280_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (1279 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("DRX_Config::setup::longDRX_CycleStartOffset_sf1280_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    longDRX_CycleStartOffset_sf1280_internal_value = packed_val + 0;
    longDRX_CycleStartOffset_sf1280_present = true;
    return 0;
}

int64_t DRX_Config::setup::longDRX_CycleStartOffset_sf1280_Value() const
{
    if(longDRX_CycleStartOffset_sf1280_present)
        return longDRX_CycleStartOffset_sf1280_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf1280_SetValue(int64_t value)
{
    if(value < 0 || value > 1279)
    {
        printf("DRX_Config::setup::longDRX_CycleStartOffset_sf1280_SetValue() range failure\n");
        return -1;
    }
    longDRX_CycleStartOffset_sf1280_internal_value = value;
    longDRX_CycleStartOffset_sf1280_present = true;
    return 0;
}

std::string DRX_Config::setup::longDRX_CycleStartOffset_sf1280_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "sf1280 = " + std::to_string(longDRX_CycleStartOffset_sf1280_internal_value) + "\n";
    return out;
}

std::string DRX_Config::setup::longDRX_CycleStartOffset_sf1280_ToStringNoNewLines() const
{
    std::string out = "sf1280=" + std::to_string(longDRX_CycleStartOffset_sf1280_internal_value) + ",";
    return out;
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf1280_Clear()
{
    longDRX_CycleStartOffset_sf1280_present = false;
    return 0;
}

bool DRX_Config::setup::longDRX_CycleStartOffset_sf1280_IsPresent() const
{
    return longDRX_CycleStartOffset_sf1280_present;
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf2048_Pack(std::vector<uint8_t> &bits)
{
    if(!longDRX_CycleStartOffset_sf2048_present)
    {
        printf("DRX_Config::setup::longDRX_CycleStartOffset_sf2048_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = longDRX_CycleStartOffset_sf2048_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (2047 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf2048_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return longDRX_CycleStartOffset_sf2048_Unpack(bits, idx);
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf2048_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (2047 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("DRX_Config::setup::longDRX_CycleStartOffset_sf2048_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    longDRX_CycleStartOffset_sf2048_internal_value = packed_val + 0;
    longDRX_CycleStartOffset_sf2048_present = true;
    return 0;
}

int64_t DRX_Config::setup::longDRX_CycleStartOffset_sf2048_Value() const
{
    if(longDRX_CycleStartOffset_sf2048_present)
        return longDRX_CycleStartOffset_sf2048_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf2048_SetValue(int64_t value)
{
    if(value < 0 || value > 2047)
    {
        printf("DRX_Config::setup::longDRX_CycleStartOffset_sf2048_SetValue() range failure\n");
        return -1;
    }
    longDRX_CycleStartOffset_sf2048_internal_value = value;
    longDRX_CycleStartOffset_sf2048_present = true;
    return 0;
}

std::string DRX_Config::setup::longDRX_CycleStartOffset_sf2048_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "sf2048 = " + std::to_string(longDRX_CycleStartOffset_sf2048_internal_value) + "\n";
    return out;
}

std::string DRX_Config::setup::longDRX_CycleStartOffset_sf2048_ToStringNoNewLines() const
{
    std::string out = "sf2048=" + std::to_string(longDRX_CycleStartOffset_sf2048_internal_value) + ",";
    return out;
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf2048_Clear()
{
    longDRX_CycleStartOffset_sf2048_present = false;
    return 0;
}

bool DRX_Config::setup::longDRX_CycleStartOffset_sf2048_IsPresent() const
{
    return longDRX_CycleStartOffset_sf2048_present;
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf2560_Pack(std::vector<uint8_t> &bits)
{
    if(!longDRX_CycleStartOffset_sf2560_present)
    {
        printf("DRX_Config::setup::longDRX_CycleStartOffset_sf2560_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = longDRX_CycleStartOffset_sf2560_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (2559 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf2560_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return longDRX_CycleStartOffset_sf2560_Unpack(bits, idx);
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf2560_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (2559 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("DRX_Config::setup::longDRX_CycleStartOffset_sf2560_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    longDRX_CycleStartOffset_sf2560_internal_value = packed_val + 0;
    longDRX_CycleStartOffset_sf2560_present = true;
    return 0;
}

int64_t DRX_Config::setup::longDRX_CycleStartOffset_sf2560_Value() const
{
    if(longDRX_CycleStartOffset_sf2560_present)
        return longDRX_CycleStartOffset_sf2560_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf2560_SetValue(int64_t value)
{
    if(value < 0 || value > 2559)
    {
        printf("DRX_Config::setup::longDRX_CycleStartOffset_sf2560_SetValue() range failure\n");
        return -1;
    }
    longDRX_CycleStartOffset_sf2560_internal_value = value;
    longDRX_CycleStartOffset_sf2560_present = true;
    return 0;
}

std::string DRX_Config::setup::longDRX_CycleStartOffset_sf2560_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "sf2560 = " + std::to_string(longDRX_CycleStartOffset_sf2560_internal_value) + "\n";
    return out;
}

std::string DRX_Config::setup::longDRX_CycleStartOffset_sf2560_ToStringNoNewLines() const
{
    std::string out = "sf2560=" + std::to_string(longDRX_CycleStartOffset_sf2560_internal_value) + ",";
    return out;
}

int DRX_Config::setup::longDRX_CycleStartOffset_sf2560_Clear()
{
    longDRX_CycleStartOffset_sf2560_present = false;
    return 0;
}

bool DRX_Config::setup::longDRX_CycleStartOffset_sf2560_IsPresent() const
{
    return longDRX_CycleStartOffset_sf2560_present;
}

int DRX_Config::setup::shortDRX::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != shortDRX_Cycle_Pack(bits))
        {
            printf("DRX_Config::setup::shortDRX:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != drxShortCycleTimer_Pack(bits))
        {
            printf("DRX_Config::setup::shortDRX:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int DRX_Config::setup::shortDRX::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int DRX_Config::setup::shortDRX::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != shortDRX_Cycle_Unpack(bits, idx))
        {
            printf("DRX_Config::setup::shortDRX:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != drxShortCycleTimer_Unpack(bits, idx))
        {
            printf("DRX_Config::setup::shortDRX:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string DRX_Config::setup::shortDRX::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "shortDRX:\n";
    out += shortDRX_Cycle_ToString(indent+1);
    out += drxShortCycleTimer_ToString(indent+1);
    return out;
}

std::string DRX_Config::setup::shortDRX::ToStringNoNewLines() const
{
    std::string out = "shortDRX:";
    out += shortDRX_Cycle_ToStringNoNewLines();
    out += drxShortCycleTimer_ToStringNoNewLines();
    return out;
}

int DRX_Config::setup::shortDRX::Set()
{
    present = true;
    return 0;
}

int DRX_Config::setup::shortDRX::SetPresence(bool is_present)
{
    present = is_present;
    return 0;
}

int DRX_Config::setup::shortDRX::Clear()
{
    present = false;
    return 0;
}

bool DRX_Config::setup::shortDRX::IsPresent() const
{
    return present;
}

int DRX_Config::setup::shortDRX::shortDRX_Cycle_Pack(std::vector<uint8_t> &bits)
{
    if(!shortDRX_Cycle_present)
    {
        printf("DRX_Config::setup::shortDRX::shortDRX_Cycle_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 4;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((shortDRX_Cycle_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int DRX_Config::setup::shortDRX::shortDRX_Cycle_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return shortDRX_Cycle_Unpack(bits, idx);
}

int DRX_Config::setup::shortDRX::shortDRX_Cycle_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 4;
    if((idx + N_bits) > bits.size())
    {
        printf("DRX_Config::setup::shortDRX::shortDRX_Cycle_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 15)
    {
        printf("DRX_Config::setup::shortDRX::shortDRX_Cycle_Unpack() max failure\n");
        return -1;
    }
    shortDRX_Cycle_internal_value = (shortDRX_Cycle_Enum)packed_val;
    shortDRX_Cycle_present = true;
    return 0;
}

DRX_Config::setup::shortDRX::shortDRX_Cycle_Enum DRX_Config::setup::shortDRX::shortDRX_Cycle_Value() const
{
    if(shortDRX_Cycle_present)
        return shortDRX_Cycle_internal_value;
    return (DRX_Config::setup::shortDRX::shortDRX_Cycle_Enum)0;
}

int DRX_Config::setup::shortDRX::shortDRX_Cycle_SetValue(shortDRX_Cycle_Enum value)
{
    shortDRX_Cycle_internal_value = value;
    shortDRX_Cycle_present = true;
    return 0;
}

int DRX_Config::setup::shortDRX::shortDRX_Cycle_SetValue(std::string value)
{
    if("sf2" == value)
    {
        shortDRX_Cycle_internal_value = k_shortDRX_Cycle_sf2;
        shortDRX_Cycle_present = true;
        return 0;
    }
    if("sf5" == value)
    {
        shortDRX_Cycle_internal_value = k_shortDRX_Cycle_sf5;
        shortDRX_Cycle_present = true;
        return 0;
    }
    if("sf8" == value)
    {
        shortDRX_Cycle_internal_value = k_shortDRX_Cycle_sf8;
        shortDRX_Cycle_present = true;
        return 0;
    }
    if("sf10" == value)
    {
        shortDRX_Cycle_internal_value = k_shortDRX_Cycle_sf10;
        shortDRX_Cycle_present = true;
        return 0;
    }
    if("sf16" == value)
    {
        shortDRX_Cycle_internal_value = k_shortDRX_Cycle_sf16;
        shortDRX_Cycle_present = true;
        return 0;
    }
    if("sf20" == value)
    {
        shortDRX_Cycle_internal_value = k_shortDRX_Cycle_sf20;
        shortDRX_Cycle_present = true;
        return 0;
    }
    if("sf32" == value)
    {
        shortDRX_Cycle_internal_value = k_shortDRX_Cycle_sf32;
        shortDRX_Cycle_present = true;
        return 0;
    }
    if("sf40" == value)
    {
        shortDRX_Cycle_internal_value = k_shortDRX_Cycle_sf40;
        shortDRX_Cycle_present = true;
        return 0;
    }
    if("sf64" == value)
    {
        shortDRX_Cycle_internal_value = k_shortDRX_Cycle_sf64;
        shortDRX_Cycle_present = true;
        return 0;
    }
    if("sf80" == value)
    {
        shortDRX_Cycle_internal_value = k_shortDRX_Cycle_sf80;
        shortDRX_Cycle_present = true;
        return 0;
    }
    if("sf128" == value)
    {
        shortDRX_Cycle_internal_value = k_shortDRX_Cycle_sf128;
        shortDRX_Cycle_present = true;
        return 0;
    }
    if("sf160" == value)
    {
        shortDRX_Cycle_internal_value = k_shortDRX_Cycle_sf160;
        shortDRX_Cycle_present = true;
        return 0;
    }
    if("sf256" == value)
    {
        shortDRX_Cycle_internal_value = k_shortDRX_Cycle_sf256;
        shortDRX_Cycle_present = true;
        return 0;
    }
    if("sf320" == value)
    {
        shortDRX_Cycle_internal_value = k_shortDRX_Cycle_sf320;
        shortDRX_Cycle_present = true;
        return 0;
    }
    if("sf512" == value)
    {
        shortDRX_Cycle_internal_value = k_shortDRX_Cycle_sf512;
        shortDRX_Cycle_present = true;
        return 0;
    }
    if("sf640" == value)
    {
        shortDRX_Cycle_internal_value = k_shortDRX_Cycle_sf640;
        shortDRX_Cycle_present = true;
        return 0;
    }
    return 1;
}

std::string DRX_Config::setup::shortDRX::shortDRX_Cycle_ValueToString(shortDRX_Cycle_Enum value) const
{
    if(k_shortDRX_Cycle_sf2 == value)
        return "sf2";
    if(k_shortDRX_Cycle_sf5 == value)
        return "sf5";
    if(k_shortDRX_Cycle_sf8 == value)
        return "sf8";
    if(k_shortDRX_Cycle_sf10 == value)
        return "sf10";
    if(k_shortDRX_Cycle_sf16 == value)
        return "sf16";
    if(k_shortDRX_Cycle_sf20 == value)
        return "sf20";
    if(k_shortDRX_Cycle_sf32 == value)
        return "sf32";
    if(k_shortDRX_Cycle_sf40 == value)
        return "sf40";
    if(k_shortDRX_Cycle_sf64 == value)
        return "sf64";
    if(k_shortDRX_Cycle_sf80 == value)
        return "sf80";
    if(k_shortDRX_Cycle_sf128 == value)
        return "sf128";
    if(k_shortDRX_Cycle_sf160 == value)
        return "sf160";
    if(k_shortDRX_Cycle_sf256 == value)
        return "sf256";
    if(k_shortDRX_Cycle_sf320 == value)
        return "sf320";
    if(k_shortDRX_Cycle_sf512 == value)
        return "sf512";
    if(k_shortDRX_Cycle_sf640 == value)
        return "sf640";
    return "";
}

uint64_t DRX_Config::setup::shortDRX::shortDRX_Cycle_NumberOfValues() const
{
    return 16;
}

std::string DRX_Config::setup::shortDRX::shortDRX_Cycle_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "shortDRX_Cycle = " + shortDRX_Cycle_ValueToString(shortDRX_Cycle_internal_value) + "\n";
    return out;
}

std::string DRX_Config::setup::shortDRX::shortDRX_Cycle_ToStringNoNewLines() const
{
    std::string out = "shortDRX_Cycle=" + shortDRX_Cycle_ValueToString(shortDRX_Cycle_internal_value) + ",";
    return out;
}

int DRX_Config::setup::shortDRX::shortDRX_Cycle_Clear()
{
    shortDRX_Cycle_present = false;
    return 0;
}

bool DRX_Config::setup::shortDRX::shortDRX_Cycle_IsPresent() const
{
    return shortDRX_Cycle_present;
}

int DRX_Config::setup::shortDRX::drxShortCycleTimer_Pack(std::vector<uint8_t> &bits)
{
    if(!drxShortCycleTimer_present)
    {
        printf("DRX_Config::setup::shortDRX::drxShortCycleTimer_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = drxShortCycleTimer_internal_value - (1);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (16 - 1))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int DRX_Config::setup::shortDRX::drxShortCycleTimer_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return drxShortCycleTimer_Unpack(bits, idx);
}

int DRX_Config::setup::shortDRX::drxShortCycleTimer_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (16 - 1))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("DRX_Config::setup::shortDRX::drxShortCycleTimer_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    drxShortCycleTimer_internal_value = packed_val + 1;
    drxShortCycleTimer_present = true;
    return 0;
}

int64_t DRX_Config::setup::shortDRX::drxShortCycleTimer_Value() const
{
    if(drxShortCycleTimer_present)
        return drxShortCycleTimer_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int DRX_Config::setup::shortDRX::drxShortCycleTimer_SetValue(int64_t value)
{
    if(value < 1 || value > 16)
    {
        printf("DRX_Config::setup::shortDRX::drxShortCycleTimer_SetValue() range failure\n");
        return -1;
    }
    drxShortCycleTimer_internal_value = value;
    drxShortCycleTimer_present = true;
    return 0;
}

std::string DRX_Config::setup::shortDRX::drxShortCycleTimer_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "drxShortCycleTimer = " + std::to_string(drxShortCycleTimer_internal_value) + "\n";
    return out;
}

std::string DRX_Config::setup::shortDRX::drxShortCycleTimer_ToStringNoNewLines() const
{
    std::string out = "drxShortCycleTimer=" + std::to_string(drxShortCycleTimer_internal_value) + ",";
    return out;
}

int DRX_Config::setup::shortDRX::drxShortCycleTimer_Clear()
{
    drxShortCycleTimer_present = false;
    return 0;
}

bool DRX_Config::setup::shortDRX::drxShortCycleTimer_IsPresent() const
{
    return drxShortCycleTimer_present;
}

