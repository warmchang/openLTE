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

#include "SPS_ConfigUL.h"

#include <cmath>

int SPS_ConfigUL::Pack(std::vector<uint8_t> &bits)
{
    if(!present)
    {
        printf("SPS_ConfigUL::Pack() presence failure\n");
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
            printf("SPS_ConfigUL::release pack failure\n");
            return -1;
        }
    }
    if(internal_choice == k_setup)
    {
        if(0 != setup_value.Pack(bits))
        {
            printf("SPS_ConfigUL::setup pack failure\n");
            return -1;
        }
    }
    return 0;
}

int SPS_ConfigUL::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int SPS_ConfigUL::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 1) > bits.size())
    {
        printf("SPS_ConfigUL::Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<1; i++)
        packed_val |= bits[idx++] << (1-i-1);

    if((SPS_ConfigUL::Enum)packed_val > k_setup)
    {
        printf("SPS_ConfigUL::Unpack() choice range failure\n");
        return -1;
    }
    internal_choice = (SPS_ConfigUL::Enum)packed_val;
    present = true;

    // Fields
    if(internal_choice == k_release)
    {
        if(0 != release_Unpack(bits, idx))
        {
            printf("SPS_ConfigUL::release unpack failure\n");
            return -1;
        }
    }
    if(internal_choice == k_setup)
    {
        if(0 != setup_value.Unpack(bits, idx))
        {
            printf("SPS_ConfigUL::setup unpack failure\n");
            return -1;
        }
    }
    return 0;
}

SPS_ConfigUL::Enum SPS_ConfigUL::Choice() const
{
    if(present)
        return internal_choice;
    return (SPS_ConfigUL::Enum)0;
}

int SPS_ConfigUL::SetChoice(SPS_ConfigUL::Enum choice)
{
    internal_choice = choice;
    present = true;
    return 0;
}

std::string SPS_ConfigUL::ChoiceToString(Enum value) const
{
    if(k_release == value)
        return "release";
    if(k_setup == value)
        return "setup";
    return "";
}

uint64_t SPS_ConfigUL::NumberOfChoices() const
{
    return 2;
}

std::string SPS_ConfigUL::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "SPS_ConfigUL = " + ChoiceToString(internal_choice) + ":\n";
    if(internal_choice == k_setup)
        out += setup_value.ToString(indent+1);
    return out;
}

std::string SPS_ConfigUL::ToStringNoNewLines() const
{
    std::string out = "SPS_ConfigUL=" + ChoiceToString(internal_choice) + ",";
    if(internal_choice == k_setup)
        out += setup_value.ToStringNoNewLines();
    return out;
}

int SPS_ConfigUL::Clear()
{
    present = false;
    return 0;
}

bool SPS_ConfigUL::IsPresent() const
{
    return present;
}

int SPS_ConfigUL::setup::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator
    bits.push_back(0);

    // Optional indicators
    bits.push_back(p0_Persistent_value.IsPresent());
    bits.push_back(twoIntervalsConfig_IsPresent());

    // Fields
    {
        if(0 != semiPersistSchedIntervalUL_Pack(bits))
        {
            printf("SPS_ConfigUL::setup:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != implicitReleaseAfter_Pack(bits))
        {
            printf("SPS_ConfigUL::setup:: field pack failure\n");
            return -1;
        }
    }
    if(p0_Persistent_value.IsPresent())
    {
        if(0 != p0_Persistent_value.Pack(bits))
        {
            printf("SPS_ConfigUL::setup:: field pack failure\n");
            return -1;
        }
    }
    if(twoIntervalsConfig_IsPresent())
    {
        if(0 != twoIntervalsConfig_Pack(bits))
        {
            printf("SPS_ConfigUL::setup:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int SPS_ConfigUL::setup::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int SPS_ConfigUL::setup::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("setup::Unpack() index out of bounds for extension\n");
        return -1;
    }
    idx++;

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("setup::Unpack() index out of bounds for optional indiator p0_Persistent\n");
        return -1;
    }
    p0_Persistent_value.SetPresence(bits[idx++]);
    if((idx + 1) > bits.size())
    {
        printf("setup::Unpack() index out of bounds for optional indiator twoIntervalsConfig\n");
        return -1;
    }
    twoIntervalsConfig_present = bits[idx++];

    // Fields
    {
        if(0 != semiPersistSchedIntervalUL_Unpack(bits, idx))
        {
            printf("SPS_ConfigUL::setup:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != implicitReleaseAfter_Unpack(bits, idx))
        {
            printf("SPS_ConfigUL::setup:: field unpack failure\n");
            return -1;
        }
    }
    if(p0_Persistent_value.IsPresent())
    {
        if(0 != p0_Persistent_value.Unpack(bits, idx))
        {
            printf("SPS_ConfigUL::setup:: field unpack failure\n");
            return -1;
        }
    }
    if(twoIntervalsConfig_present)
    {
        if(0 != twoIntervalsConfig_Unpack(bits, idx))
        {
            printf("SPS_ConfigUL::setup:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string SPS_ConfigUL::setup::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "setup:\n";
    out += semiPersistSchedIntervalUL_ToString(indent+1);
    out += implicitReleaseAfter_ToString(indent+1);
    if(p0_Persistent_value.IsPresent())
        out += p0_Persistent_value.ToString(indent+1);
    if(twoIntervalsConfig_IsPresent())
        out += twoIntervalsConfig_ToString(indent+1);
    return out;
}

std::string SPS_ConfigUL::setup::ToStringNoNewLines() const
{
    std::string out = "setup:";
    out += semiPersistSchedIntervalUL_ToStringNoNewLines();
    out += implicitReleaseAfter_ToStringNoNewLines();
    if(p0_Persistent_value.IsPresent())
        out += p0_Persistent_value.ToStringNoNewLines();
    if(twoIntervalsConfig_IsPresent())
        out += twoIntervalsConfig_ToStringNoNewLines();
    return out;
}

int SPS_ConfigUL::setup::semiPersistSchedIntervalUL_Pack(std::vector<uint8_t> &bits)
{
    if(!semiPersistSchedIntervalUL_present)
    {
        printf("SPS_ConfigUL::setup::semiPersistSchedIntervalUL_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 4;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((semiPersistSchedIntervalUL_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int SPS_ConfigUL::setup::semiPersistSchedIntervalUL_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return semiPersistSchedIntervalUL_Unpack(bits, idx);
}

int SPS_ConfigUL::setup::semiPersistSchedIntervalUL_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 4;
    if((idx + N_bits) > bits.size())
    {
        printf("SPS_ConfigUL::setup::semiPersistSchedIntervalUL_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 15)
    {
        printf("SPS_ConfigUL::setup::semiPersistSchedIntervalUL_Unpack() max failure\n");
        return -1;
    }
    semiPersistSchedIntervalUL_internal_value = (semiPersistSchedIntervalUL_Enum)packed_val;
    semiPersistSchedIntervalUL_present = true;
    return 0;
}

SPS_ConfigUL::setup::semiPersistSchedIntervalUL_Enum SPS_ConfigUL::setup::semiPersistSchedIntervalUL_Value() const
{
    if(semiPersistSchedIntervalUL_present)
        return semiPersistSchedIntervalUL_internal_value;
    return (SPS_ConfigUL::setup::semiPersistSchedIntervalUL_Enum)0;
}

int SPS_ConfigUL::setup::semiPersistSchedIntervalUL_SetValue(semiPersistSchedIntervalUL_Enum value)
{
    semiPersistSchedIntervalUL_internal_value = value;
    semiPersistSchedIntervalUL_present = true;
    return 0;
}

int SPS_ConfigUL::setup::semiPersistSchedIntervalUL_SetValue(std::string value)
{
    if("sf10" == value)
    {
        semiPersistSchedIntervalUL_internal_value = k_semiPersistSchedIntervalUL_sf10;
        semiPersistSchedIntervalUL_present = true;
        return 0;
    }
    if("sf20" == value)
    {
        semiPersistSchedIntervalUL_internal_value = k_semiPersistSchedIntervalUL_sf20;
        semiPersistSchedIntervalUL_present = true;
        return 0;
    }
    if("sf32" == value)
    {
        semiPersistSchedIntervalUL_internal_value = k_semiPersistSchedIntervalUL_sf32;
        semiPersistSchedIntervalUL_present = true;
        return 0;
    }
    if("sf40" == value)
    {
        semiPersistSchedIntervalUL_internal_value = k_semiPersistSchedIntervalUL_sf40;
        semiPersistSchedIntervalUL_present = true;
        return 0;
    }
    if("sf64" == value)
    {
        semiPersistSchedIntervalUL_internal_value = k_semiPersistSchedIntervalUL_sf64;
        semiPersistSchedIntervalUL_present = true;
        return 0;
    }
    if("sf80" == value)
    {
        semiPersistSchedIntervalUL_internal_value = k_semiPersistSchedIntervalUL_sf80;
        semiPersistSchedIntervalUL_present = true;
        return 0;
    }
    if("sf128" == value)
    {
        semiPersistSchedIntervalUL_internal_value = k_semiPersistSchedIntervalUL_sf128;
        semiPersistSchedIntervalUL_present = true;
        return 0;
    }
    if("sf160" == value)
    {
        semiPersistSchedIntervalUL_internal_value = k_semiPersistSchedIntervalUL_sf160;
        semiPersistSchedIntervalUL_present = true;
        return 0;
    }
    if("sf320" == value)
    {
        semiPersistSchedIntervalUL_internal_value = k_semiPersistSchedIntervalUL_sf320;
        semiPersistSchedIntervalUL_present = true;
        return 0;
    }
    if("sf640" == value)
    {
        semiPersistSchedIntervalUL_internal_value = k_semiPersistSchedIntervalUL_sf640;
        semiPersistSchedIntervalUL_present = true;
        return 0;
    }
    if("spare6" == value)
    {
        semiPersistSchedIntervalUL_internal_value = k_semiPersistSchedIntervalUL_spare6;
        semiPersistSchedIntervalUL_present = true;
        return 0;
    }
    if("spare5" == value)
    {
        semiPersistSchedIntervalUL_internal_value = k_semiPersistSchedIntervalUL_spare5;
        semiPersistSchedIntervalUL_present = true;
        return 0;
    }
    if("spare4" == value)
    {
        semiPersistSchedIntervalUL_internal_value = k_semiPersistSchedIntervalUL_spare4;
        semiPersistSchedIntervalUL_present = true;
        return 0;
    }
    if("spare3" == value)
    {
        semiPersistSchedIntervalUL_internal_value = k_semiPersistSchedIntervalUL_spare3;
        semiPersistSchedIntervalUL_present = true;
        return 0;
    }
    if("spare2" == value)
    {
        semiPersistSchedIntervalUL_internal_value = k_semiPersistSchedIntervalUL_spare2;
        semiPersistSchedIntervalUL_present = true;
        return 0;
    }
    if("spare1" == value)
    {
        semiPersistSchedIntervalUL_internal_value = k_semiPersistSchedIntervalUL_spare1;
        semiPersistSchedIntervalUL_present = true;
        return 0;
    }
    return 1;
}

std::string SPS_ConfigUL::setup::semiPersistSchedIntervalUL_ValueToString(semiPersistSchedIntervalUL_Enum value) const
{
    if(k_semiPersistSchedIntervalUL_sf10 == value)
        return "sf10";
    if(k_semiPersistSchedIntervalUL_sf20 == value)
        return "sf20";
    if(k_semiPersistSchedIntervalUL_sf32 == value)
        return "sf32";
    if(k_semiPersistSchedIntervalUL_sf40 == value)
        return "sf40";
    if(k_semiPersistSchedIntervalUL_sf64 == value)
        return "sf64";
    if(k_semiPersistSchedIntervalUL_sf80 == value)
        return "sf80";
    if(k_semiPersistSchedIntervalUL_sf128 == value)
        return "sf128";
    if(k_semiPersistSchedIntervalUL_sf160 == value)
        return "sf160";
    if(k_semiPersistSchedIntervalUL_sf320 == value)
        return "sf320";
    if(k_semiPersistSchedIntervalUL_sf640 == value)
        return "sf640";
    if(k_semiPersistSchedIntervalUL_spare6 == value)
        return "spare6";
    if(k_semiPersistSchedIntervalUL_spare5 == value)
        return "spare5";
    if(k_semiPersistSchedIntervalUL_spare4 == value)
        return "spare4";
    if(k_semiPersistSchedIntervalUL_spare3 == value)
        return "spare3";
    if(k_semiPersistSchedIntervalUL_spare2 == value)
        return "spare2";
    if(k_semiPersistSchedIntervalUL_spare1 == value)
        return "spare1";
    return "";
}

uint64_t SPS_ConfigUL::setup::semiPersistSchedIntervalUL_NumberOfValues() const
{
    return 16;
}

std::string SPS_ConfigUL::setup::semiPersistSchedIntervalUL_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "semiPersistSchedIntervalUL = " + semiPersistSchedIntervalUL_ValueToString(semiPersistSchedIntervalUL_internal_value) + "\n";
    return out;
}

std::string SPS_ConfigUL::setup::semiPersistSchedIntervalUL_ToStringNoNewLines() const
{
    std::string out = "semiPersistSchedIntervalUL=" + semiPersistSchedIntervalUL_ValueToString(semiPersistSchedIntervalUL_internal_value) + ",";
    return out;
}

int SPS_ConfigUL::setup::semiPersistSchedIntervalUL_Clear()
{
    semiPersistSchedIntervalUL_present = false;
    return 0;
}

bool SPS_ConfigUL::setup::semiPersistSchedIntervalUL_IsPresent() const
{
    return semiPersistSchedIntervalUL_present;
}

int SPS_ConfigUL::setup::implicitReleaseAfter_Pack(std::vector<uint8_t> &bits)
{
    if(!implicitReleaseAfter_present)
    {
        printf("SPS_ConfigUL::setup::implicitReleaseAfter_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 2;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((implicitReleaseAfter_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int SPS_ConfigUL::setup::implicitReleaseAfter_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return implicitReleaseAfter_Unpack(bits, idx);
}

int SPS_ConfigUL::setup::implicitReleaseAfter_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 2;
    if((idx + N_bits) > bits.size())
    {
        printf("SPS_ConfigUL::setup::implicitReleaseAfter_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 3)
    {
        printf("SPS_ConfigUL::setup::implicitReleaseAfter_Unpack() max failure\n");
        return -1;
    }
    implicitReleaseAfter_internal_value = (implicitReleaseAfter_Enum)packed_val;
    implicitReleaseAfter_present = true;
    return 0;
}

SPS_ConfigUL::setup::implicitReleaseAfter_Enum SPS_ConfigUL::setup::implicitReleaseAfter_Value() const
{
    if(implicitReleaseAfter_present)
        return implicitReleaseAfter_internal_value;
    return (SPS_ConfigUL::setup::implicitReleaseAfter_Enum)0;
}

int SPS_ConfigUL::setup::implicitReleaseAfter_SetValue(implicitReleaseAfter_Enum value)
{
    implicitReleaseAfter_internal_value = value;
    implicitReleaseAfter_present = true;
    return 0;
}

int SPS_ConfigUL::setup::implicitReleaseAfter_SetValue(std::string value)
{
    if("e2" == value)
    {
        implicitReleaseAfter_internal_value = k_implicitReleaseAfter_e2;
        implicitReleaseAfter_present = true;
        return 0;
    }
    if("e3" == value)
    {
        implicitReleaseAfter_internal_value = k_implicitReleaseAfter_e3;
        implicitReleaseAfter_present = true;
        return 0;
    }
    if("e4" == value)
    {
        implicitReleaseAfter_internal_value = k_implicitReleaseAfter_e4;
        implicitReleaseAfter_present = true;
        return 0;
    }
    if("e8" == value)
    {
        implicitReleaseAfter_internal_value = k_implicitReleaseAfter_e8;
        implicitReleaseAfter_present = true;
        return 0;
    }
    return 1;
}

std::string SPS_ConfigUL::setup::implicitReleaseAfter_ValueToString(implicitReleaseAfter_Enum value) const
{
    if(k_implicitReleaseAfter_e2 == value)
        return "e2";
    if(k_implicitReleaseAfter_e3 == value)
        return "e3";
    if(k_implicitReleaseAfter_e4 == value)
        return "e4";
    if(k_implicitReleaseAfter_e8 == value)
        return "e8";
    return "";
}

uint64_t SPS_ConfigUL::setup::implicitReleaseAfter_NumberOfValues() const
{
    return 4;
}

std::string SPS_ConfigUL::setup::implicitReleaseAfter_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "implicitReleaseAfter = " + implicitReleaseAfter_ValueToString(implicitReleaseAfter_internal_value) + "\n";
    return out;
}

std::string SPS_ConfigUL::setup::implicitReleaseAfter_ToStringNoNewLines() const
{
    std::string out = "implicitReleaseAfter=" + implicitReleaseAfter_ValueToString(implicitReleaseAfter_internal_value) + ",";
    return out;
}

int SPS_ConfigUL::setup::implicitReleaseAfter_Clear()
{
    implicitReleaseAfter_present = false;
    return 0;
}

bool SPS_ConfigUL::setup::implicitReleaseAfter_IsPresent() const
{
    return implicitReleaseAfter_present;
}

int SPS_ConfigUL::setup::p0_Persistent::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != p0_NominalPUSCH_Persistent_Pack(bits))
        {
            printf("SPS_ConfigUL::setup::p0_Persistent:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != p0_UE_PUSCH_Persistent_Pack(bits))
        {
            printf("SPS_ConfigUL::setup::p0_Persistent:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int SPS_ConfigUL::setup::p0_Persistent::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int SPS_ConfigUL::setup::p0_Persistent::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != p0_NominalPUSCH_Persistent_Unpack(bits, idx))
        {
            printf("SPS_ConfigUL::setup::p0_Persistent:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != p0_UE_PUSCH_Persistent_Unpack(bits, idx))
        {
            printf("SPS_ConfigUL::setup::p0_Persistent:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string SPS_ConfigUL::setup::p0_Persistent::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "p0_Persistent:\n";
    out += p0_NominalPUSCH_Persistent_ToString(indent+1);
    out += p0_UE_PUSCH_Persistent_ToString(indent+1);
    return out;
}

std::string SPS_ConfigUL::setup::p0_Persistent::ToStringNoNewLines() const
{
    std::string out = "p0_Persistent:";
    out += p0_NominalPUSCH_Persistent_ToStringNoNewLines();
    out += p0_UE_PUSCH_Persistent_ToStringNoNewLines();
    return out;
}

int SPS_ConfigUL::setup::p0_Persistent::Set()
{
    present = true;
    return 0;
}

int SPS_ConfigUL::setup::p0_Persistent::SetPresence(bool is_present)
{
    present = is_present;
    return 0;
}

int SPS_ConfigUL::setup::p0_Persistent::Clear()
{
    present = false;
    return 0;
}

bool SPS_ConfigUL::setup::p0_Persistent::IsPresent() const
{
    return present;
}

int SPS_ConfigUL::setup::p0_Persistent::p0_NominalPUSCH_Persistent_Pack(std::vector<uint8_t> &bits)
{
    if(!p0_NominalPUSCH_Persistent_present)
    {
        printf("SPS_ConfigUL::setup::p0_Persistent::p0_NominalPUSCH_Persistent_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = p0_NominalPUSCH_Persistent_internal_value - (-126);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (24 - -126))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int SPS_ConfigUL::setup::p0_Persistent::p0_NominalPUSCH_Persistent_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return p0_NominalPUSCH_Persistent_Unpack(bits, idx);
}

int SPS_ConfigUL::setup::p0_Persistent::p0_NominalPUSCH_Persistent_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (24 - -126))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("SPS_ConfigUL::setup::p0_Persistent::p0_NominalPUSCH_Persistent_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    p0_NominalPUSCH_Persistent_internal_value = packed_val + -126;
    p0_NominalPUSCH_Persistent_present = true;
    return 0;
}

int64_t SPS_ConfigUL::setup::p0_Persistent::p0_NominalPUSCH_Persistent_Value() const
{
    if(p0_NominalPUSCH_Persistent_present)
        return p0_NominalPUSCH_Persistent_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int SPS_ConfigUL::setup::p0_Persistent::p0_NominalPUSCH_Persistent_SetValue(int64_t value)
{
    if(value < -126 || value > 24)
    {
        printf("SPS_ConfigUL::setup::p0_Persistent::p0_NominalPUSCH_Persistent_SetValue() range failure\n");
        return -1;
    }
    p0_NominalPUSCH_Persistent_internal_value = value;
    p0_NominalPUSCH_Persistent_present = true;
    return 0;
}

std::string SPS_ConfigUL::setup::p0_Persistent::p0_NominalPUSCH_Persistent_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "p0_NominalPUSCH_Persistent = " + std::to_string(p0_NominalPUSCH_Persistent_internal_value) + "\n";
    return out;
}

std::string SPS_ConfigUL::setup::p0_Persistent::p0_NominalPUSCH_Persistent_ToStringNoNewLines() const
{
    std::string out = "p0_NominalPUSCH_Persistent=" + std::to_string(p0_NominalPUSCH_Persistent_internal_value) + ",";
    return out;
}

int SPS_ConfigUL::setup::p0_Persistent::p0_NominalPUSCH_Persistent_Clear()
{
    p0_NominalPUSCH_Persistent_present = false;
    return 0;
}

bool SPS_ConfigUL::setup::p0_Persistent::p0_NominalPUSCH_Persistent_IsPresent() const
{
    return p0_NominalPUSCH_Persistent_present;
}

int SPS_ConfigUL::setup::p0_Persistent::p0_UE_PUSCH_Persistent_Pack(std::vector<uint8_t> &bits)
{
    if(!p0_UE_PUSCH_Persistent_present)
    {
        printf("SPS_ConfigUL::setup::p0_Persistent::p0_UE_PUSCH_Persistent_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = p0_UE_PUSCH_Persistent_internal_value - (-8);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (7 - -8))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int SPS_ConfigUL::setup::p0_Persistent::p0_UE_PUSCH_Persistent_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return p0_UE_PUSCH_Persistent_Unpack(bits, idx);
}

int SPS_ConfigUL::setup::p0_Persistent::p0_UE_PUSCH_Persistent_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (7 - -8))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("SPS_ConfigUL::setup::p0_Persistent::p0_UE_PUSCH_Persistent_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    p0_UE_PUSCH_Persistent_internal_value = packed_val + -8;
    p0_UE_PUSCH_Persistent_present = true;
    return 0;
}

int64_t SPS_ConfigUL::setup::p0_Persistent::p0_UE_PUSCH_Persistent_Value() const
{
    if(p0_UE_PUSCH_Persistent_present)
        return p0_UE_PUSCH_Persistent_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int SPS_ConfigUL::setup::p0_Persistent::p0_UE_PUSCH_Persistent_SetValue(int64_t value)
{
    if(value < -8 || value > 7)
    {
        printf("SPS_ConfigUL::setup::p0_Persistent::p0_UE_PUSCH_Persistent_SetValue() range failure\n");
        return -1;
    }
    p0_UE_PUSCH_Persistent_internal_value = value;
    p0_UE_PUSCH_Persistent_present = true;
    return 0;
}

std::string SPS_ConfigUL::setup::p0_Persistent::p0_UE_PUSCH_Persistent_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "p0_UE_PUSCH_Persistent = " + std::to_string(p0_UE_PUSCH_Persistent_internal_value) + "\n";
    return out;
}

std::string SPS_ConfigUL::setup::p0_Persistent::p0_UE_PUSCH_Persistent_ToStringNoNewLines() const
{
    std::string out = "p0_UE_PUSCH_Persistent=" + std::to_string(p0_UE_PUSCH_Persistent_internal_value) + ",";
    return out;
}

int SPS_ConfigUL::setup::p0_Persistent::p0_UE_PUSCH_Persistent_Clear()
{
    p0_UE_PUSCH_Persistent_present = false;
    return 0;
}

bool SPS_ConfigUL::setup::p0_Persistent::p0_UE_PUSCH_Persistent_IsPresent() const
{
    return p0_UE_PUSCH_Persistent_present;
}

int SPS_ConfigUL::setup::twoIntervalsConfig_Pack(std::vector<uint8_t> &bits)
{
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((twoIntervalsConfig_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int SPS_ConfigUL::setup::twoIntervalsConfig_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return twoIntervalsConfig_Unpack(bits, idx);
}

int SPS_ConfigUL::setup::twoIntervalsConfig_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("SPS_ConfigUL::setup::twoIntervalsConfig_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 0)
    {
        printf("SPS_ConfigUL::setup::twoIntervalsConfig_Unpack() max failure\n");
        return -1;
    }
    twoIntervalsConfig_internal_value = (twoIntervalsConfig_Enum)packed_val;
    twoIntervalsConfig_present = true;
    return 0;
}

SPS_ConfigUL::setup::twoIntervalsConfig_Enum SPS_ConfigUL::setup::twoIntervalsConfig_Value() const
{
    if(twoIntervalsConfig_present)
        return twoIntervalsConfig_internal_value;
    return (SPS_ConfigUL::setup::twoIntervalsConfig_Enum)0;
}

int SPS_ConfigUL::setup::twoIntervalsConfig_SetValue(twoIntervalsConfig_Enum value)
{
    twoIntervalsConfig_internal_value = value;
    twoIntervalsConfig_present = true;
    return 0;
}

int SPS_ConfigUL::setup::twoIntervalsConfig_SetValue(std::string value)
{
    if("true" == value)
    {
        twoIntervalsConfig_internal_value = k_twoIntervalsConfig_true;
        twoIntervalsConfig_present = true;
        return 0;
    }
    return 1;
}

std::string SPS_ConfigUL::setup::twoIntervalsConfig_ValueToString(twoIntervalsConfig_Enum value) const
{
    if(k_twoIntervalsConfig_true == value)
        return "true";
    return "";
}

uint64_t SPS_ConfigUL::setup::twoIntervalsConfig_NumberOfValues() const
{
    return 1;
}

std::string SPS_ConfigUL::setup::twoIntervalsConfig_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "twoIntervalsConfig = " + twoIntervalsConfig_ValueToString(twoIntervalsConfig_internal_value) + "\n";
    return out;
}

std::string SPS_ConfigUL::setup::twoIntervalsConfig_ToStringNoNewLines() const
{
    std::string out = "twoIntervalsConfig=" + twoIntervalsConfig_ValueToString(twoIntervalsConfig_internal_value) + ",";
    return out;
}

int SPS_ConfigUL::setup::twoIntervalsConfig_Clear()
{
    twoIntervalsConfig_present = false;
    return 0;
}

bool SPS_ConfigUL::setup::twoIntervalsConfig_IsPresent() const
{
    return twoIntervalsConfig_present;
}

