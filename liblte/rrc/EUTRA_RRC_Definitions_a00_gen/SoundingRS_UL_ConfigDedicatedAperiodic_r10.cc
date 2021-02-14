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

#include "SoundingRS_UL_ConfigDedicatedAperiodic_r10.h"

#include <cmath>

int SoundingRS_UL_ConfigDedicatedAperiodic_r10::Pack(std::vector<uint8_t> &bits)
{
    if(!present)
    {
        printf("SoundingRS_UL_ConfigDedicatedAperiodic_r10::Pack() presence failure\n");
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
            printf("SoundingRS_UL_ConfigDedicatedAperiodic_r10::release pack failure\n");
            return -1;
        }
    }
    if(internal_choice == k_setup)
    {
        if(0 != setup_value.Pack(bits))
        {
            printf("SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup pack failure\n");
            return -1;
        }
    }
    return 0;
}

int SoundingRS_UL_ConfigDedicatedAperiodic_r10::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int SoundingRS_UL_ConfigDedicatedAperiodic_r10::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 1) > bits.size())
    {
        printf("SoundingRS_UL_ConfigDedicatedAperiodic_r10::Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<1; i++)
        packed_val |= bits[idx++] << (1-i-1);

    if((SoundingRS_UL_ConfigDedicatedAperiodic_r10::Enum)packed_val > k_setup)
    {
        printf("SoundingRS_UL_ConfigDedicatedAperiodic_r10::Unpack() choice range failure\n");
        return -1;
    }
    internal_choice = (SoundingRS_UL_ConfigDedicatedAperiodic_r10::Enum)packed_val;
    present = true;

    // Fields
    if(internal_choice == k_release)
    {
        if(0 != release_Unpack(bits, idx))
        {
            printf("SoundingRS_UL_ConfigDedicatedAperiodic_r10::release unpack failure\n");
            return -1;
        }
    }
    if(internal_choice == k_setup)
    {
        if(0 != setup_value.Unpack(bits, idx))
        {
            printf("SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup unpack failure\n");
            return -1;
        }
    }
    return 0;
}

SoundingRS_UL_ConfigDedicatedAperiodic_r10::Enum SoundingRS_UL_ConfigDedicatedAperiodic_r10::Choice() const
{
    if(present)
        return internal_choice;
    return (SoundingRS_UL_ConfigDedicatedAperiodic_r10::Enum)0;
}

int SoundingRS_UL_ConfigDedicatedAperiodic_r10::SetChoice(SoundingRS_UL_ConfigDedicatedAperiodic_r10::Enum choice)
{
    internal_choice = choice;
    present = true;
    return 0;
}

std::string SoundingRS_UL_ConfigDedicatedAperiodic_r10::ChoiceToString(Enum value) const
{
    if(k_release == value)
        return "release";
    if(k_setup == value)
        return "setup";
    return "";
}

uint64_t SoundingRS_UL_ConfigDedicatedAperiodic_r10::NumberOfChoices() const
{
    return 2;
}

std::string SoundingRS_UL_ConfigDedicatedAperiodic_r10::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "SoundingRS_UL_ConfigDedicatedAperiodic_r10 = " + ChoiceToString(internal_choice) + ":\n";
    if(internal_choice == k_setup)
        out += setup_value.ToString(indent+1);
    return out;
}

std::string SoundingRS_UL_ConfigDedicatedAperiodic_r10::ToStringNoNewLines() const
{
    std::string out = "SoundingRS_UL_ConfigDedicatedAperiodic_r10=" + ChoiceToString(internal_choice) + ",";
    if(internal_choice == k_setup)
        out += setup_value.ToStringNoNewLines();
    return out;
}

int SoundingRS_UL_ConfigDedicatedAperiodic_r10::Clear()
{
    present = false;
    return 0;
}

bool SoundingRS_UL_ConfigDedicatedAperiodic_r10::IsPresent() const
{
    return present;
}

int SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != srs_AntennaPortAp_r10_Pack(bits))
        {
            printf("SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != srs_BandwidthAp_r10_Pack(bits))
        {
            printf("SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != srs_HoppingBandwidthAp_r10_Pack(bits))
        {
            printf("SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != freqDomainPositionAp_r10_Pack(bits))
        {
            printf("SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != transmissionCombAp_r10_Pack(bits))
        {
            printf("SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != cyclicShiftAp_r10_Pack(bits))
        {
            printf("SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != srs_AntennaPortAp_r10_Unpack(bits, idx))
        {
            printf("SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != srs_BandwidthAp_r10_Unpack(bits, idx))
        {
            printf("SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != srs_HoppingBandwidthAp_r10_Unpack(bits, idx))
        {
            printf("SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != freqDomainPositionAp_r10_Unpack(bits, idx))
        {
            printf("SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != transmissionCombAp_r10_Unpack(bits, idx))
        {
            printf("SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != cyclicShiftAp_r10_Unpack(bits, idx))
        {
            printf("SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "setup:\n";
    out += srs_AntennaPortAp_r10_ToString(indent+1);
    out += srs_BandwidthAp_r10_ToString(indent+1);
    out += srs_HoppingBandwidthAp_r10_ToString(indent+1);
    out += freqDomainPositionAp_r10_ToString(indent+1);
    out += transmissionCombAp_r10_ToString(indent+1);
    out += cyclicShiftAp_r10_ToString(indent+1);
    return out;
}

std::string SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::ToStringNoNewLines() const
{
    std::string out = "setup:";
    out += srs_AntennaPortAp_r10_ToStringNoNewLines();
    out += srs_BandwidthAp_r10_ToStringNoNewLines();
    out += srs_HoppingBandwidthAp_r10_ToStringNoNewLines();
    out += freqDomainPositionAp_r10_ToStringNoNewLines();
    out += transmissionCombAp_r10_ToStringNoNewLines();
    out += cyclicShiftAp_r10_ToStringNoNewLines();
    return out;
}

int SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::srs_AntennaPortAp_r10_Pack(std::vector<uint8_t> &bits)
{
    if(!srs_AntennaPortAp_r10_present)
    {
        printf("SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::srs_AntennaPortAp_r10_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 2;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((srs_AntennaPortAp_r10_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::srs_AntennaPortAp_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return srs_AntennaPortAp_r10_Unpack(bits, idx);
}

int SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::srs_AntennaPortAp_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 2;
    if((idx + N_bits) > bits.size())
    {
        printf("SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::srs_AntennaPortAp_r10_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 3)
    {
        printf("SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::srs_AntennaPortAp_r10_Unpack() max failure\n");
        return -1;
    }
    srs_AntennaPortAp_r10_internal_value = (srs_AntennaPortAp_r10_Enum)packed_val;
    srs_AntennaPortAp_r10_present = true;
    return 0;
}

SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::srs_AntennaPortAp_r10_Enum SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::srs_AntennaPortAp_r10_Value() const
{
    if(srs_AntennaPortAp_r10_present)
        return srs_AntennaPortAp_r10_internal_value;
    return (SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::srs_AntennaPortAp_r10_Enum)0;
}

int SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::srs_AntennaPortAp_r10_SetValue(srs_AntennaPortAp_r10_Enum value)
{
    srs_AntennaPortAp_r10_internal_value = value;
    srs_AntennaPortAp_r10_present = true;
    return 0;
}

int SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::srs_AntennaPortAp_r10_SetValue(std::string value)
{
    if("an1" == value)
    {
        srs_AntennaPortAp_r10_internal_value = k_srs_AntennaPortAp_r10_an1;
        srs_AntennaPortAp_r10_present = true;
        return 0;
    }
    if("an2" == value)
    {
        srs_AntennaPortAp_r10_internal_value = k_srs_AntennaPortAp_r10_an2;
        srs_AntennaPortAp_r10_present = true;
        return 0;
    }
    if("an4" == value)
    {
        srs_AntennaPortAp_r10_internal_value = k_srs_AntennaPortAp_r10_an4;
        srs_AntennaPortAp_r10_present = true;
        return 0;
    }
    if("spare1" == value)
    {
        srs_AntennaPortAp_r10_internal_value = k_srs_AntennaPortAp_r10_spare1;
        srs_AntennaPortAp_r10_present = true;
        return 0;
    }
    return 1;
}

std::string SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::srs_AntennaPortAp_r10_ValueToString(srs_AntennaPortAp_r10_Enum value) const
{
    if(k_srs_AntennaPortAp_r10_an1 == value)
        return "an1";
    if(k_srs_AntennaPortAp_r10_an2 == value)
        return "an2";
    if(k_srs_AntennaPortAp_r10_an4 == value)
        return "an4";
    if(k_srs_AntennaPortAp_r10_spare1 == value)
        return "spare1";
    return "";
}

uint64_t SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::srs_AntennaPortAp_r10_NumberOfValues() const
{
    return 4;
}

std::string SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::srs_AntennaPortAp_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "srs_AntennaPortAp_r10 = " + srs_AntennaPortAp_r10_ValueToString(srs_AntennaPortAp_r10_internal_value) + "\n";
    return out;
}

std::string SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::srs_AntennaPortAp_r10_ToStringNoNewLines() const
{
    std::string out = "srs_AntennaPortAp_r10=" + srs_AntennaPortAp_r10_ValueToString(srs_AntennaPortAp_r10_internal_value) + ",";
    return out;
}

int SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::srs_AntennaPortAp_r10_Clear()
{
    srs_AntennaPortAp_r10_present = false;
    return 0;
}

bool SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::srs_AntennaPortAp_r10_IsPresent() const
{
    return srs_AntennaPortAp_r10_present;
}

int SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::srs_BandwidthAp_r10_Pack(std::vector<uint8_t> &bits)
{
    if(!srs_BandwidthAp_r10_present)
    {
        printf("SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::srs_BandwidthAp_r10_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 2;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((srs_BandwidthAp_r10_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::srs_BandwidthAp_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return srs_BandwidthAp_r10_Unpack(bits, idx);
}

int SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::srs_BandwidthAp_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 2;
    if((idx + N_bits) > bits.size())
    {
        printf("SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::srs_BandwidthAp_r10_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 3)
    {
        printf("SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::srs_BandwidthAp_r10_Unpack() max failure\n");
        return -1;
    }
    srs_BandwidthAp_r10_internal_value = (srs_BandwidthAp_r10_Enum)packed_val;
    srs_BandwidthAp_r10_present = true;
    return 0;
}

SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::srs_BandwidthAp_r10_Enum SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::srs_BandwidthAp_r10_Value() const
{
    if(srs_BandwidthAp_r10_present)
        return srs_BandwidthAp_r10_internal_value;
    return (SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::srs_BandwidthAp_r10_Enum)0;
}

int SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::srs_BandwidthAp_r10_SetValue(srs_BandwidthAp_r10_Enum value)
{
    srs_BandwidthAp_r10_internal_value = value;
    srs_BandwidthAp_r10_present = true;
    return 0;
}

int SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::srs_BandwidthAp_r10_SetValue(std::string value)
{
    if("bw0" == value)
    {
        srs_BandwidthAp_r10_internal_value = k_srs_BandwidthAp_r10_bw0;
        srs_BandwidthAp_r10_present = true;
        return 0;
    }
    if("bw1" == value)
    {
        srs_BandwidthAp_r10_internal_value = k_srs_BandwidthAp_r10_bw1;
        srs_BandwidthAp_r10_present = true;
        return 0;
    }
    if("bw2" == value)
    {
        srs_BandwidthAp_r10_internal_value = k_srs_BandwidthAp_r10_bw2;
        srs_BandwidthAp_r10_present = true;
        return 0;
    }
    if("bw3" == value)
    {
        srs_BandwidthAp_r10_internal_value = k_srs_BandwidthAp_r10_bw3;
        srs_BandwidthAp_r10_present = true;
        return 0;
    }
    return 1;
}

std::string SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::srs_BandwidthAp_r10_ValueToString(srs_BandwidthAp_r10_Enum value) const
{
    if(k_srs_BandwidthAp_r10_bw0 == value)
        return "bw0";
    if(k_srs_BandwidthAp_r10_bw1 == value)
        return "bw1";
    if(k_srs_BandwidthAp_r10_bw2 == value)
        return "bw2";
    if(k_srs_BandwidthAp_r10_bw3 == value)
        return "bw3";
    return "";
}

uint64_t SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::srs_BandwidthAp_r10_NumberOfValues() const
{
    return 4;
}

std::string SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::srs_BandwidthAp_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "srs_BandwidthAp_r10 = " + srs_BandwidthAp_r10_ValueToString(srs_BandwidthAp_r10_internal_value) + "\n";
    return out;
}

std::string SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::srs_BandwidthAp_r10_ToStringNoNewLines() const
{
    std::string out = "srs_BandwidthAp_r10=" + srs_BandwidthAp_r10_ValueToString(srs_BandwidthAp_r10_internal_value) + ",";
    return out;
}

int SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::srs_BandwidthAp_r10_Clear()
{
    srs_BandwidthAp_r10_present = false;
    return 0;
}

bool SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::srs_BandwidthAp_r10_IsPresent() const
{
    return srs_BandwidthAp_r10_present;
}

int SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::srs_HoppingBandwidthAp_r10_Pack(std::vector<uint8_t> &bits)
{
    if(!srs_HoppingBandwidthAp_r10_present)
    {
        printf("SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::srs_HoppingBandwidthAp_r10_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 2;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((srs_HoppingBandwidthAp_r10_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::srs_HoppingBandwidthAp_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return srs_HoppingBandwidthAp_r10_Unpack(bits, idx);
}

int SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::srs_HoppingBandwidthAp_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 2;
    if((idx + N_bits) > bits.size())
    {
        printf("SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::srs_HoppingBandwidthAp_r10_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 3)
    {
        printf("SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::srs_HoppingBandwidthAp_r10_Unpack() max failure\n");
        return -1;
    }
    srs_HoppingBandwidthAp_r10_internal_value = (srs_HoppingBandwidthAp_r10_Enum)packed_val;
    srs_HoppingBandwidthAp_r10_present = true;
    return 0;
}

SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::srs_HoppingBandwidthAp_r10_Enum SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::srs_HoppingBandwidthAp_r10_Value() const
{
    if(srs_HoppingBandwidthAp_r10_present)
        return srs_HoppingBandwidthAp_r10_internal_value;
    return (SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::srs_HoppingBandwidthAp_r10_Enum)0;
}

int SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::srs_HoppingBandwidthAp_r10_SetValue(srs_HoppingBandwidthAp_r10_Enum value)
{
    srs_HoppingBandwidthAp_r10_internal_value = value;
    srs_HoppingBandwidthAp_r10_present = true;
    return 0;
}

int SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::srs_HoppingBandwidthAp_r10_SetValue(std::string value)
{
    if("hbw0" == value)
    {
        srs_HoppingBandwidthAp_r10_internal_value = k_srs_HoppingBandwidthAp_r10_hbw0;
        srs_HoppingBandwidthAp_r10_present = true;
        return 0;
    }
    if("hbw1" == value)
    {
        srs_HoppingBandwidthAp_r10_internal_value = k_srs_HoppingBandwidthAp_r10_hbw1;
        srs_HoppingBandwidthAp_r10_present = true;
        return 0;
    }
    if("hbw2" == value)
    {
        srs_HoppingBandwidthAp_r10_internal_value = k_srs_HoppingBandwidthAp_r10_hbw2;
        srs_HoppingBandwidthAp_r10_present = true;
        return 0;
    }
    if("hbw3" == value)
    {
        srs_HoppingBandwidthAp_r10_internal_value = k_srs_HoppingBandwidthAp_r10_hbw3;
        srs_HoppingBandwidthAp_r10_present = true;
        return 0;
    }
    return 1;
}

std::string SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::srs_HoppingBandwidthAp_r10_ValueToString(srs_HoppingBandwidthAp_r10_Enum value) const
{
    if(k_srs_HoppingBandwidthAp_r10_hbw0 == value)
        return "hbw0";
    if(k_srs_HoppingBandwidthAp_r10_hbw1 == value)
        return "hbw1";
    if(k_srs_HoppingBandwidthAp_r10_hbw2 == value)
        return "hbw2";
    if(k_srs_HoppingBandwidthAp_r10_hbw3 == value)
        return "hbw3";
    return "";
}

uint64_t SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::srs_HoppingBandwidthAp_r10_NumberOfValues() const
{
    return 4;
}

std::string SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::srs_HoppingBandwidthAp_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "srs_HoppingBandwidthAp_r10 = " + srs_HoppingBandwidthAp_r10_ValueToString(srs_HoppingBandwidthAp_r10_internal_value) + "\n";
    return out;
}

std::string SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::srs_HoppingBandwidthAp_r10_ToStringNoNewLines() const
{
    std::string out = "srs_HoppingBandwidthAp_r10=" + srs_HoppingBandwidthAp_r10_ValueToString(srs_HoppingBandwidthAp_r10_internal_value) + ",";
    return out;
}

int SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::srs_HoppingBandwidthAp_r10_Clear()
{
    srs_HoppingBandwidthAp_r10_present = false;
    return 0;
}

bool SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::srs_HoppingBandwidthAp_r10_IsPresent() const
{
    return srs_HoppingBandwidthAp_r10_present;
}

int SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::freqDomainPositionAp_r10_Pack(std::vector<uint8_t> &bits)
{
    if(!freqDomainPositionAp_r10_present)
    {
        printf("SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::freqDomainPositionAp_r10_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = freqDomainPositionAp_r10_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (23 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::freqDomainPositionAp_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return freqDomainPositionAp_r10_Unpack(bits, idx);
}

int SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::freqDomainPositionAp_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (23 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::freqDomainPositionAp_r10_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    freqDomainPositionAp_r10_internal_value = packed_val + 0;
    freqDomainPositionAp_r10_present = true;
    return 0;
}

int64_t SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::freqDomainPositionAp_r10_Value() const
{
    if(freqDomainPositionAp_r10_present)
        return freqDomainPositionAp_r10_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::freqDomainPositionAp_r10_SetValue(int64_t value)
{
    if(value < 0 || value > 23)
    {
        printf("SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::freqDomainPositionAp_r10_SetValue() range failure\n");
        return -1;
    }
    freqDomainPositionAp_r10_internal_value = value;
    freqDomainPositionAp_r10_present = true;
    return 0;
}

std::string SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::freqDomainPositionAp_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "freqDomainPositionAp_r10 = " + std::to_string(freqDomainPositionAp_r10_internal_value) + "\n";
    return out;
}

std::string SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::freqDomainPositionAp_r10_ToStringNoNewLines() const
{
    std::string out = "freqDomainPositionAp_r10=" + std::to_string(freqDomainPositionAp_r10_internal_value) + ",";
    return out;
}

int SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::freqDomainPositionAp_r10_Clear()
{
    freqDomainPositionAp_r10_present = false;
    return 0;
}

bool SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::freqDomainPositionAp_r10_IsPresent() const
{
    return freqDomainPositionAp_r10_present;
}

int SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::transmissionCombAp_r10_Pack(std::vector<uint8_t> &bits)
{
    if(!transmissionCombAp_r10_present)
    {
        printf("SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::transmissionCombAp_r10_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = transmissionCombAp_r10_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (1 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::transmissionCombAp_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return transmissionCombAp_r10_Unpack(bits, idx);
}

int SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::transmissionCombAp_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (1 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::transmissionCombAp_r10_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    transmissionCombAp_r10_internal_value = packed_val + 0;
    transmissionCombAp_r10_present = true;
    return 0;
}

int64_t SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::transmissionCombAp_r10_Value() const
{
    if(transmissionCombAp_r10_present)
        return transmissionCombAp_r10_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::transmissionCombAp_r10_SetValue(int64_t value)
{
    if(value < 0 || value > 1)
    {
        printf("SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::transmissionCombAp_r10_SetValue() range failure\n");
        return -1;
    }
    transmissionCombAp_r10_internal_value = value;
    transmissionCombAp_r10_present = true;
    return 0;
}

std::string SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::transmissionCombAp_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "transmissionCombAp_r10 = " + std::to_string(transmissionCombAp_r10_internal_value) + "\n";
    return out;
}

std::string SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::transmissionCombAp_r10_ToStringNoNewLines() const
{
    std::string out = "transmissionCombAp_r10=" + std::to_string(transmissionCombAp_r10_internal_value) + ",";
    return out;
}

int SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::transmissionCombAp_r10_Clear()
{
    transmissionCombAp_r10_present = false;
    return 0;
}

bool SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::transmissionCombAp_r10_IsPresent() const
{
    return transmissionCombAp_r10_present;
}

int SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::cyclicShiftAp_r10_Pack(std::vector<uint8_t> &bits)
{
    if(!cyclicShiftAp_r10_present)
    {
        printf("SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::cyclicShiftAp_r10_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 3;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((cyclicShiftAp_r10_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::cyclicShiftAp_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return cyclicShiftAp_r10_Unpack(bits, idx);
}

int SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::cyclicShiftAp_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 3;
    if((idx + N_bits) > bits.size())
    {
        printf("SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::cyclicShiftAp_r10_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 7)
    {
        printf("SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::cyclicShiftAp_r10_Unpack() max failure\n");
        return -1;
    }
    cyclicShiftAp_r10_internal_value = (cyclicShiftAp_r10_Enum)packed_val;
    cyclicShiftAp_r10_present = true;
    return 0;
}

SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::cyclicShiftAp_r10_Enum SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::cyclicShiftAp_r10_Value() const
{
    if(cyclicShiftAp_r10_present)
        return cyclicShiftAp_r10_internal_value;
    return (SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::cyclicShiftAp_r10_Enum)0;
}

int SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::cyclicShiftAp_r10_SetValue(cyclicShiftAp_r10_Enum value)
{
    cyclicShiftAp_r10_internal_value = value;
    cyclicShiftAp_r10_present = true;
    return 0;
}

int SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::cyclicShiftAp_r10_SetValue(std::string value)
{
    if("cs0" == value)
    {
        cyclicShiftAp_r10_internal_value = k_cyclicShiftAp_r10_cs0;
        cyclicShiftAp_r10_present = true;
        return 0;
    }
    if("cs1" == value)
    {
        cyclicShiftAp_r10_internal_value = k_cyclicShiftAp_r10_cs1;
        cyclicShiftAp_r10_present = true;
        return 0;
    }
    if("cs2" == value)
    {
        cyclicShiftAp_r10_internal_value = k_cyclicShiftAp_r10_cs2;
        cyclicShiftAp_r10_present = true;
        return 0;
    }
    if("cs3" == value)
    {
        cyclicShiftAp_r10_internal_value = k_cyclicShiftAp_r10_cs3;
        cyclicShiftAp_r10_present = true;
        return 0;
    }
    if("cs4" == value)
    {
        cyclicShiftAp_r10_internal_value = k_cyclicShiftAp_r10_cs4;
        cyclicShiftAp_r10_present = true;
        return 0;
    }
    if("cs5" == value)
    {
        cyclicShiftAp_r10_internal_value = k_cyclicShiftAp_r10_cs5;
        cyclicShiftAp_r10_present = true;
        return 0;
    }
    if("cs6" == value)
    {
        cyclicShiftAp_r10_internal_value = k_cyclicShiftAp_r10_cs6;
        cyclicShiftAp_r10_present = true;
        return 0;
    }
    if("cs7" == value)
    {
        cyclicShiftAp_r10_internal_value = k_cyclicShiftAp_r10_cs7;
        cyclicShiftAp_r10_present = true;
        return 0;
    }
    return 1;
}

std::string SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::cyclicShiftAp_r10_ValueToString(cyclicShiftAp_r10_Enum value) const
{
    if(k_cyclicShiftAp_r10_cs0 == value)
        return "cs0";
    if(k_cyclicShiftAp_r10_cs1 == value)
        return "cs1";
    if(k_cyclicShiftAp_r10_cs2 == value)
        return "cs2";
    if(k_cyclicShiftAp_r10_cs3 == value)
        return "cs3";
    if(k_cyclicShiftAp_r10_cs4 == value)
        return "cs4";
    if(k_cyclicShiftAp_r10_cs5 == value)
        return "cs5";
    if(k_cyclicShiftAp_r10_cs6 == value)
        return "cs6";
    if(k_cyclicShiftAp_r10_cs7 == value)
        return "cs7";
    return "";
}

uint64_t SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::cyclicShiftAp_r10_NumberOfValues() const
{
    return 8;
}

std::string SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::cyclicShiftAp_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cyclicShiftAp_r10 = " + cyclicShiftAp_r10_ValueToString(cyclicShiftAp_r10_internal_value) + "\n";
    return out;
}

std::string SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::cyclicShiftAp_r10_ToStringNoNewLines() const
{
    std::string out = "cyclicShiftAp_r10=" + cyclicShiftAp_r10_ValueToString(cyclicShiftAp_r10_internal_value) + ",";
    return out;
}

int SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::cyclicShiftAp_r10_Clear()
{
    cyclicShiftAp_r10_present = false;
    return 0;
}

bool SoundingRS_UL_ConfigDedicatedAperiodic_r10::setup::cyclicShiftAp_r10_IsPresent() const
{
    return cyclicShiftAp_r10_present;
}

