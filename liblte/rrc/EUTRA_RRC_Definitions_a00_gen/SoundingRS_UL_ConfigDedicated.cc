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

#include "SoundingRS_UL_ConfigDedicated.h"

#include <cmath>

int SoundingRS_UL_ConfigDedicated::Pack(std::vector<uint8_t> &bits)
{
    if(!present)
    {
        printf("SoundingRS_UL_ConfigDedicated::Pack() presence failure\n");
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
            printf("SoundingRS_UL_ConfigDedicated::release pack failure\n");
            return -1;
        }
    }
    if(internal_choice == k_setup)
    {
        if(0 != setup_value.Pack(bits))
        {
            printf("SoundingRS_UL_ConfigDedicated::setup pack failure\n");
            return -1;
        }
    }
    return 0;
}

int SoundingRS_UL_ConfigDedicated::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int SoundingRS_UL_ConfigDedicated::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 1) > bits.size())
    {
        printf("SoundingRS_UL_ConfigDedicated::Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<1; i++)
        packed_val |= bits[idx++] << (1-i-1);

    if((SoundingRS_UL_ConfigDedicated::Enum)packed_val > k_setup)
    {
        printf("SoundingRS_UL_ConfigDedicated::Unpack() choice range failure\n");
        return -1;
    }
    internal_choice = (SoundingRS_UL_ConfigDedicated::Enum)packed_val;
    present = true;

    // Fields
    if(internal_choice == k_release)
    {
        if(0 != release_Unpack(bits, idx))
        {
            printf("SoundingRS_UL_ConfigDedicated::release unpack failure\n");
            return -1;
        }
    }
    if(internal_choice == k_setup)
    {
        if(0 != setup_value.Unpack(bits, idx))
        {
            printf("SoundingRS_UL_ConfigDedicated::setup unpack failure\n");
            return -1;
        }
    }
    return 0;
}

SoundingRS_UL_ConfigDedicated::Enum SoundingRS_UL_ConfigDedicated::Choice() const
{
    if(present)
        return internal_choice;
    return (SoundingRS_UL_ConfigDedicated::Enum)0;
}

int SoundingRS_UL_ConfigDedicated::SetChoice(SoundingRS_UL_ConfigDedicated::Enum choice)
{
    internal_choice = choice;
    present = true;
    return 0;
}

std::string SoundingRS_UL_ConfigDedicated::ChoiceToString(Enum value) const
{
    if(k_release == value)
        return "release";
    if(k_setup == value)
        return "setup";
    return "";
}

uint64_t SoundingRS_UL_ConfigDedicated::NumberOfChoices() const
{
    return 2;
}

std::string SoundingRS_UL_ConfigDedicated::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "SoundingRS_UL_ConfigDedicated = " + ChoiceToString(internal_choice) + ":\n";
    if(internal_choice == k_setup)
        out += setup_value.ToString(indent+1);
    return out;
}

std::string SoundingRS_UL_ConfigDedicated::ToStringNoNewLines() const
{
    std::string out = "SoundingRS_UL_ConfigDedicated=" + ChoiceToString(internal_choice) + ",";
    if(internal_choice == k_setup)
        out += setup_value.ToStringNoNewLines();
    return out;
}

int SoundingRS_UL_ConfigDedicated::Clear()
{
    present = false;
    return 0;
}

bool SoundingRS_UL_ConfigDedicated::IsPresent() const
{
    return present;
}

int SoundingRS_UL_ConfigDedicated::setup::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != srs_Bandwidth_Pack(bits))
        {
            printf("SoundingRS_UL_ConfigDedicated::setup:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != srs_HoppingBandwidth_Pack(bits))
        {
            printf("SoundingRS_UL_ConfigDedicated::setup:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != freqDomainPosition_Pack(bits))
        {
            printf("SoundingRS_UL_ConfigDedicated::setup:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != duration_Pack(bits))
        {
            printf("SoundingRS_UL_ConfigDedicated::setup:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != srs_ConfigIndex_Pack(bits))
        {
            printf("SoundingRS_UL_ConfigDedicated::setup:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != transmissionComb_Pack(bits))
        {
            printf("SoundingRS_UL_ConfigDedicated::setup:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != cyclicShift_Pack(bits))
        {
            printf("SoundingRS_UL_ConfigDedicated::setup:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int SoundingRS_UL_ConfigDedicated::setup::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int SoundingRS_UL_ConfigDedicated::setup::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != srs_Bandwidth_Unpack(bits, idx))
        {
            printf("SoundingRS_UL_ConfigDedicated::setup:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != srs_HoppingBandwidth_Unpack(bits, idx))
        {
            printf("SoundingRS_UL_ConfigDedicated::setup:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != freqDomainPosition_Unpack(bits, idx))
        {
            printf("SoundingRS_UL_ConfigDedicated::setup:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != duration_Unpack(bits, idx))
        {
            printf("SoundingRS_UL_ConfigDedicated::setup:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != srs_ConfigIndex_Unpack(bits, idx))
        {
            printf("SoundingRS_UL_ConfigDedicated::setup:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != transmissionComb_Unpack(bits, idx))
        {
            printf("SoundingRS_UL_ConfigDedicated::setup:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != cyclicShift_Unpack(bits, idx))
        {
            printf("SoundingRS_UL_ConfigDedicated::setup:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string SoundingRS_UL_ConfigDedicated::setup::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "setup:\n";
    out += srs_Bandwidth_ToString(indent+1);
    out += srs_HoppingBandwidth_ToString(indent+1);
    out += freqDomainPosition_ToString(indent+1);
    out += duration_ToString(indent+1);
    out += srs_ConfigIndex_ToString(indent+1);
    out += transmissionComb_ToString(indent+1);
    out += cyclicShift_ToString(indent+1);
    return out;
}

std::string SoundingRS_UL_ConfigDedicated::setup::ToStringNoNewLines() const
{
    std::string out = "setup:";
    out += srs_Bandwidth_ToStringNoNewLines();
    out += srs_HoppingBandwidth_ToStringNoNewLines();
    out += freqDomainPosition_ToStringNoNewLines();
    out += duration_ToStringNoNewLines();
    out += srs_ConfigIndex_ToStringNoNewLines();
    out += transmissionComb_ToStringNoNewLines();
    out += cyclicShift_ToStringNoNewLines();
    return out;
}

int SoundingRS_UL_ConfigDedicated::setup::srs_Bandwidth_Pack(std::vector<uint8_t> &bits)
{
    if(!srs_Bandwidth_present)
    {
        printf("SoundingRS_UL_ConfigDedicated::setup::srs_Bandwidth_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 2;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((srs_Bandwidth_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int SoundingRS_UL_ConfigDedicated::setup::srs_Bandwidth_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return srs_Bandwidth_Unpack(bits, idx);
}

int SoundingRS_UL_ConfigDedicated::setup::srs_Bandwidth_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 2;
    if((idx + N_bits) > bits.size())
    {
        printf("SoundingRS_UL_ConfigDedicated::setup::srs_Bandwidth_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 3)
    {
        printf("SoundingRS_UL_ConfigDedicated::setup::srs_Bandwidth_Unpack() max failure\n");
        return -1;
    }
    srs_Bandwidth_internal_value = (srs_Bandwidth_Enum)packed_val;
    srs_Bandwidth_present = true;
    return 0;
}

SoundingRS_UL_ConfigDedicated::setup::srs_Bandwidth_Enum SoundingRS_UL_ConfigDedicated::setup::srs_Bandwidth_Value() const
{
    if(srs_Bandwidth_present)
        return srs_Bandwidth_internal_value;
    return (SoundingRS_UL_ConfigDedicated::setup::srs_Bandwidth_Enum)0;
}

int SoundingRS_UL_ConfigDedicated::setup::srs_Bandwidth_SetValue(srs_Bandwidth_Enum value)
{
    srs_Bandwidth_internal_value = value;
    srs_Bandwidth_present = true;
    return 0;
}

int SoundingRS_UL_ConfigDedicated::setup::srs_Bandwidth_SetValue(std::string value)
{
    if("bw0" == value)
    {
        srs_Bandwidth_internal_value = k_srs_Bandwidth_bw0;
        srs_Bandwidth_present = true;
        return 0;
    }
    if("bw1" == value)
    {
        srs_Bandwidth_internal_value = k_srs_Bandwidth_bw1;
        srs_Bandwidth_present = true;
        return 0;
    }
    if("bw2" == value)
    {
        srs_Bandwidth_internal_value = k_srs_Bandwidth_bw2;
        srs_Bandwidth_present = true;
        return 0;
    }
    if("bw3" == value)
    {
        srs_Bandwidth_internal_value = k_srs_Bandwidth_bw3;
        srs_Bandwidth_present = true;
        return 0;
    }
    return 1;
}

std::string SoundingRS_UL_ConfigDedicated::setup::srs_Bandwidth_ValueToString(srs_Bandwidth_Enum value) const
{
    if(k_srs_Bandwidth_bw0 == value)
        return "bw0";
    if(k_srs_Bandwidth_bw1 == value)
        return "bw1";
    if(k_srs_Bandwidth_bw2 == value)
        return "bw2";
    if(k_srs_Bandwidth_bw3 == value)
        return "bw3";
    return "";
}

uint64_t SoundingRS_UL_ConfigDedicated::setup::srs_Bandwidth_NumberOfValues() const
{
    return 4;
}

std::string SoundingRS_UL_ConfigDedicated::setup::srs_Bandwidth_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "srs_Bandwidth = " + srs_Bandwidth_ValueToString(srs_Bandwidth_internal_value) + "\n";
    return out;
}

std::string SoundingRS_UL_ConfigDedicated::setup::srs_Bandwidth_ToStringNoNewLines() const
{
    std::string out = "srs_Bandwidth=" + srs_Bandwidth_ValueToString(srs_Bandwidth_internal_value) + ",";
    return out;
}

int SoundingRS_UL_ConfigDedicated::setup::srs_Bandwidth_Clear()
{
    srs_Bandwidth_present = false;
    return 0;
}

bool SoundingRS_UL_ConfigDedicated::setup::srs_Bandwidth_IsPresent() const
{
    return srs_Bandwidth_present;
}

int SoundingRS_UL_ConfigDedicated::setup::srs_HoppingBandwidth_Pack(std::vector<uint8_t> &bits)
{
    if(!srs_HoppingBandwidth_present)
    {
        printf("SoundingRS_UL_ConfigDedicated::setup::srs_HoppingBandwidth_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 2;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((srs_HoppingBandwidth_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int SoundingRS_UL_ConfigDedicated::setup::srs_HoppingBandwidth_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return srs_HoppingBandwidth_Unpack(bits, idx);
}

int SoundingRS_UL_ConfigDedicated::setup::srs_HoppingBandwidth_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 2;
    if((idx + N_bits) > bits.size())
    {
        printf("SoundingRS_UL_ConfigDedicated::setup::srs_HoppingBandwidth_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 3)
    {
        printf("SoundingRS_UL_ConfigDedicated::setup::srs_HoppingBandwidth_Unpack() max failure\n");
        return -1;
    }
    srs_HoppingBandwidth_internal_value = (srs_HoppingBandwidth_Enum)packed_val;
    srs_HoppingBandwidth_present = true;
    return 0;
}

SoundingRS_UL_ConfigDedicated::setup::srs_HoppingBandwidth_Enum SoundingRS_UL_ConfigDedicated::setup::srs_HoppingBandwidth_Value() const
{
    if(srs_HoppingBandwidth_present)
        return srs_HoppingBandwidth_internal_value;
    return (SoundingRS_UL_ConfigDedicated::setup::srs_HoppingBandwidth_Enum)0;
}

int SoundingRS_UL_ConfigDedicated::setup::srs_HoppingBandwidth_SetValue(srs_HoppingBandwidth_Enum value)
{
    srs_HoppingBandwidth_internal_value = value;
    srs_HoppingBandwidth_present = true;
    return 0;
}

int SoundingRS_UL_ConfigDedicated::setup::srs_HoppingBandwidth_SetValue(std::string value)
{
    if("hbw0" == value)
    {
        srs_HoppingBandwidth_internal_value = k_srs_HoppingBandwidth_hbw0;
        srs_HoppingBandwidth_present = true;
        return 0;
    }
    if("hbw1" == value)
    {
        srs_HoppingBandwidth_internal_value = k_srs_HoppingBandwidth_hbw1;
        srs_HoppingBandwidth_present = true;
        return 0;
    }
    if("hbw2" == value)
    {
        srs_HoppingBandwidth_internal_value = k_srs_HoppingBandwidth_hbw2;
        srs_HoppingBandwidth_present = true;
        return 0;
    }
    if("hbw3" == value)
    {
        srs_HoppingBandwidth_internal_value = k_srs_HoppingBandwidth_hbw3;
        srs_HoppingBandwidth_present = true;
        return 0;
    }
    return 1;
}

std::string SoundingRS_UL_ConfigDedicated::setup::srs_HoppingBandwidth_ValueToString(srs_HoppingBandwidth_Enum value) const
{
    if(k_srs_HoppingBandwidth_hbw0 == value)
        return "hbw0";
    if(k_srs_HoppingBandwidth_hbw1 == value)
        return "hbw1";
    if(k_srs_HoppingBandwidth_hbw2 == value)
        return "hbw2";
    if(k_srs_HoppingBandwidth_hbw3 == value)
        return "hbw3";
    return "";
}

uint64_t SoundingRS_UL_ConfigDedicated::setup::srs_HoppingBandwidth_NumberOfValues() const
{
    return 4;
}

std::string SoundingRS_UL_ConfigDedicated::setup::srs_HoppingBandwidth_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "srs_HoppingBandwidth = " + srs_HoppingBandwidth_ValueToString(srs_HoppingBandwidth_internal_value) + "\n";
    return out;
}

std::string SoundingRS_UL_ConfigDedicated::setup::srs_HoppingBandwidth_ToStringNoNewLines() const
{
    std::string out = "srs_HoppingBandwidth=" + srs_HoppingBandwidth_ValueToString(srs_HoppingBandwidth_internal_value) + ",";
    return out;
}

int SoundingRS_UL_ConfigDedicated::setup::srs_HoppingBandwidth_Clear()
{
    srs_HoppingBandwidth_present = false;
    return 0;
}

bool SoundingRS_UL_ConfigDedicated::setup::srs_HoppingBandwidth_IsPresent() const
{
    return srs_HoppingBandwidth_present;
}

int SoundingRS_UL_ConfigDedicated::setup::freqDomainPosition_Pack(std::vector<uint8_t> &bits)
{
    if(!freqDomainPosition_present)
    {
        printf("SoundingRS_UL_ConfigDedicated::setup::freqDomainPosition_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = freqDomainPosition_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (23 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int SoundingRS_UL_ConfigDedicated::setup::freqDomainPosition_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return freqDomainPosition_Unpack(bits, idx);
}

int SoundingRS_UL_ConfigDedicated::setup::freqDomainPosition_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (23 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("SoundingRS_UL_ConfigDedicated::setup::freqDomainPosition_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    freqDomainPosition_internal_value = packed_val + 0;
    freqDomainPosition_present = true;
    return 0;
}

int64_t SoundingRS_UL_ConfigDedicated::setup::freqDomainPosition_Value() const
{
    if(freqDomainPosition_present)
        return freqDomainPosition_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int SoundingRS_UL_ConfigDedicated::setup::freqDomainPosition_SetValue(int64_t value)
{
    if(value < 0 || value > 23)
    {
        printf("SoundingRS_UL_ConfigDedicated::setup::freqDomainPosition_SetValue() range failure\n");
        return -1;
    }
    freqDomainPosition_internal_value = value;
    freqDomainPosition_present = true;
    return 0;
}

std::string SoundingRS_UL_ConfigDedicated::setup::freqDomainPosition_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "freqDomainPosition = " + std::to_string(freqDomainPosition_internal_value) + "\n";
    return out;
}

std::string SoundingRS_UL_ConfigDedicated::setup::freqDomainPosition_ToStringNoNewLines() const
{
    std::string out = "freqDomainPosition=" + std::to_string(freqDomainPosition_internal_value) + ",";
    return out;
}

int SoundingRS_UL_ConfigDedicated::setup::freqDomainPosition_Clear()
{
    freqDomainPosition_present = false;
    return 0;
}

bool SoundingRS_UL_ConfigDedicated::setup::freqDomainPosition_IsPresent() const
{
    return freqDomainPosition_present;
}

int SoundingRS_UL_ConfigDedicated::setup::duration_Pack(std::vector<uint8_t> &bits)
{
    if(!duration_present)
    {
        printf("SoundingRS_UL_ConfigDedicated::setup::duration_Pack() presence failure\n");
        return -1;
    }
    bits.push_back(duration_internal_value);
    return 0;
}

int SoundingRS_UL_ConfigDedicated::setup::duration_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return duration_Unpack(bits, idx);
}

int SoundingRS_UL_ConfigDedicated::setup::duration_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    if((idx + 1) > bits.size())
    {
        printf("SoundingRS_UL_ConfigDedicated::setup::duration_Unpack() index out of bounds\n");
        return -1;
    }
    duration_internal_value = bits[idx++];
    duration_present = true;
    return 0;
}

bool SoundingRS_UL_ConfigDedicated::setup::duration_Value() const
{
    if(duration_present)
        return duration_internal_value;
    return false;
}

int SoundingRS_UL_ConfigDedicated::setup::duration_SetValue(bool value)
{
    duration_internal_value = value;
    duration_present = true;
    return 0;
}

std::string SoundingRS_UL_ConfigDedicated::setup::duration_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "duration = " + std::to_string(duration_internal_value) + "\n";
    return out;
}

std::string SoundingRS_UL_ConfigDedicated::setup::duration_ToStringNoNewLines() const
{
    std::string out = "duration=" + std::to_string(duration_internal_value) + ",";
    return out;
}

int SoundingRS_UL_ConfigDedicated::setup::duration_Clear()
{
    duration_present = false;
    return 0;
}

bool SoundingRS_UL_ConfigDedicated::setup::duration_IsPresent() const
{
    return duration_present;
}

int SoundingRS_UL_ConfigDedicated::setup::srs_ConfigIndex_Pack(std::vector<uint8_t> &bits)
{
    if(!srs_ConfigIndex_present)
    {
        printf("SoundingRS_UL_ConfigDedicated::setup::srs_ConfigIndex_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = srs_ConfigIndex_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (1023 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int SoundingRS_UL_ConfigDedicated::setup::srs_ConfigIndex_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return srs_ConfigIndex_Unpack(bits, idx);
}

int SoundingRS_UL_ConfigDedicated::setup::srs_ConfigIndex_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (1023 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("SoundingRS_UL_ConfigDedicated::setup::srs_ConfigIndex_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    srs_ConfigIndex_internal_value = packed_val + 0;
    srs_ConfigIndex_present = true;
    return 0;
}

int64_t SoundingRS_UL_ConfigDedicated::setup::srs_ConfigIndex_Value() const
{
    if(srs_ConfigIndex_present)
        return srs_ConfigIndex_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int SoundingRS_UL_ConfigDedicated::setup::srs_ConfigIndex_SetValue(int64_t value)
{
    if(value < 0 || value > 1023)
    {
        printf("SoundingRS_UL_ConfigDedicated::setup::srs_ConfigIndex_SetValue() range failure\n");
        return -1;
    }
    srs_ConfigIndex_internal_value = value;
    srs_ConfigIndex_present = true;
    return 0;
}

std::string SoundingRS_UL_ConfigDedicated::setup::srs_ConfigIndex_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "srs_ConfigIndex = " + std::to_string(srs_ConfigIndex_internal_value) + "\n";
    return out;
}

std::string SoundingRS_UL_ConfigDedicated::setup::srs_ConfigIndex_ToStringNoNewLines() const
{
    std::string out = "srs_ConfigIndex=" + std::to_string(srs_ConfigIndex_internal_value) + ",";
    return out;
}

int SoundingRS_UL_ConfigDedicated::setup::srs_ConfigIndex_Clear()
{
    srs_ConfigIndex_present = false;
    return 0;
}

bool SoundingRS_UL_ConfigDedicated::setup::srs_ConfigIndex_IsPresent() const
{
    return srs_ConfigIndex_present;
}

int SoundingRS_UL_ConfigDedicated::setup::transmissionComb_Pack(std::vector<uint8_t> &bits)
{
    if(!transmissionComb_present)
    {
        printf("SoundingRS_UL_ConfigDedicated::setup::transmissionComb_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = transmissionComb_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (1 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int SoundingRS_UL_ConfigDedicated::setup::transmissionComb_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return transmissionComb_Unpack(bits, idx);
}

int SoundingRS_UL_ConfigDedicated::setup::transmissionComb_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (1 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("SoundingRS_UL_ConfigDedicated::setup::transmissionComb_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    transmissionComb_internal_value = packed_val + 0;
    transmissionComb_present = true;
    return 0;
}

int64_t SoundingRS_UL_ConfigDedicated::setup::transmissionComb_Value() const
{
    if(transmissionComb_present)
        return transmissionComb_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int SoundingRS_UL_ConfigDedicated::setup::transmissionComb_SetValue(int64_t value)
{
    if(value < 0 || value > 1)
    {
        printf("SoundingRS_UL_ConfigDedicated::setup::transmissionComb_SetValue() range failure\n");
        return -1;
    }
    transmissionComb_internal_value = value;
    transmissionComb_present = true;
    return 0;
}

std::string SoundingRS_UL_ConfigDedicated::setup::transmissionComb_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "transmissionComb = " + std::to_string(transmissionComb_internal_value) + "\n";
    return out;
}

std::string SoundingRS_UL_ConfigDedicated::setup::transmissionComb_ToStringNoNewLines() const
{
    std::string out = "transmissionComb=" + std::to_string(transmissionComb_internal_value) + ",";
    return out;
}

int SoundingRS_UL_ConfigDedicated::setup::transmissionComb_Clear()
{
    transmissionComb_present = false;
    return 0;
}

bool SoundingRS_UL_ConfigDedicated::setup::transmissionComb_IsPresent() const
{
    return transmissionComb_present;
}

int SoundingRS_UL_ConfigDedicated::setup::cyclicShift_Pack(std::vector<uint8_t> &bits)
{
    if(!cyclicShift_present)
    {
        printf("SoundingRS_UL_ConfigDedicated::setup::cyclicShift_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 3;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((cyclicShift_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int SoundingRS_UL_ConfigDedicated::setup::cyclicShift_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return cyclicShift_Unpack(bits, idx);
}

int SoundingRS_UL_ConfigDedicated::setup::cyclicShift_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 3;
    if((idx + N_bits) > bits.size())
    {
        printf("SoundingRS_UL_ConfigDedicated::setup::cyclicShift_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 7)
    {
        printf("SoundingRS_UL_ConfigDedicated::setup::cyclicShift_Unpack() max failure\n");
        return -1;
    }
    cyclicShift_internal_value = (cyclicShift_Enum)packed_val;
    cyclicShift_present = true;
    return 0;
}

SoundingRS_UL_ConfigDedicated::setup::cyclicShift_Enum SoundingRS_UL_ConfigDedicated::setup::cyclicShift_Value() const
{
    if(cyclicShift_present)
        return cyclicShift_internal_value;
    return (SoundingRS_UL_ConfigDedicated::setup::cyclicShift_Enum)0;
}

int SoundingRS_UL_ConfigDedicated::setup::cyclicShift_SetValue(cyclicShift_Enum value)
{
    cyclicShift_internal_value = value;
    cyclicShift_present = true;
    return 0;
}

int SoundingRS_UL_ConfigDedicated::setup::cyclicShift_SetValue(std::string value)
{
    if("cs0" == value)
    {
        cyclicShift_internal_value = k_cyclicShift_cs0;
        cyclicShift_present = true;
        return 0;
    }
    if("cs1" == value)
    {
        cyclicShift_internal_value = k_cyclicShift_cs1;
        cyclicShift_present = true;
        return 0;
    }
    if("cs2" == value)
    {
        cyclicShift_internal_value = k_cyclicShift_cs2;
        cyclicShift_present = true;
        return 0;
    }
    if("cs3" == value)
    {
        cyclicShift_internal_value = k_cyclicShift_cs3;
        cyclicShift_present = true;
        return 0;
    }
    if("cs4" == value)
    {
        cyclicShift_internal_value = k_cyclicShift_cs4;
        cyclicShift_present = true;
        return 0;
    }
    if("cs5" == value)
    {
        cyclicShift_internal_value = k_cyclicShift_cs5;
        cyclicShift_present = true;
        return 0;
    }
    if("cs6" == value)
    {
        cyclicShift_internal_value = k_cyclicShift_cs6;
        cyclicShift_present = true;
        return 0;
    }
    if("cs7" == value)
    {
        cyclicShift_internal_value = k_cyclicShift_cs7;
        cyclicShift_present = true;
        return 0;
    }
    return 1;
}

std::string SoundingRS_UL_ConfigDedicated::setup::cyclicShift_ValueToString(cyclicShift_Enum value) const
{
    if(k_cyclicShift_cs0 == value)
        return "cs0";
    if(k_cyclicShift_cs1 == value)
        return "cs1";
    if(k_cyclicShift_cs2 == value)
        return "cs2";
    if(k_cyclicShift_cs3 == value)
        return "cs3";
    if(k_cyclicShift_cs4 == value)
        return "cs4";
    if(k_cyclicShift_cs5 == value)
        return "cs5";
    if(k_cyclicShift_cs6 == value)
        return "cs6";
    if(k_cyclicShift_cs7 == value)
        return "cs7";
    return "";
}

uint64_t SoundingRS_UL_ConfigDedicated::setup::cyclicShift_NumberOfValues() const
{
    return 8;
}

std::string SoundingRS_UL_ConfigDedicated::setup::cyclicShift_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cyclicShift = " + cyclicShift_ValueToString(cyclicShift_internal_value) + "\n";
    return out;
}

std::string SoundingRS_UL_ConfigDedicated::setup::cyclicShift_ToStringNoNewLines() const
{
    std::string out = "cyclicShift=" + cyclicShift_ValueToString(cyclicShift_internal_value) + ",";
    return out;
}

int SoundingRS_UL_ConfigDedicated::setup::cyclicShift_Clear()
{
    cyclicShift_present = false;
    return 0;
}

bool SoundingRS_UL_ConfigDedicated::setup::cyclicShift_IsPresent() const
{
    return cyclicShift_present;
}

