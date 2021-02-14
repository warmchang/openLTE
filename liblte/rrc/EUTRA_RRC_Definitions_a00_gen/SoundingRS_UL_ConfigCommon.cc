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

#include "SoundingRS_UL_ConfigCommon.h"

#include <cmath>

int SoundingRS_UL_ConfigCommon::Pack(std::vector<uint8_t> &bits)
{
    if(!present)
    {
        printf("SoundingRS_UL_ConfigCommon::Pack() presence failure\n");
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
            printf("SoundingRS_UL_ConfigCommon::release pack failure\n");
            return -1;
        }
    }
    if(internal_choice == k_setup)
    {
        if(0 != setup_value.Pack(bits))
        {
            printf("SoundingRS_UL_ConfigCommon::setup pack failure\n");
            return -1;
        }
    }
    return 0;
}

int SoundingRS_UL_ConfigCommon::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int SoundingRS_UL_ConfigCommon::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 1) > bits.size())
    {
        printf("SoundingRS_UL_ConfigCommon::Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<1; i++)
        packed_val |= bits[idx++] << (1-i-1);

    if((SoundingRS_UL_ConfigCommon::Enum)packed_val > k_setup)
    {
        printf("SoundingRS_UL_ConfigCommon::Unpack() choice range failure\n");
        return -1;
    }
    internal_choice = (SoundingRS_UL_ConfigCommon::Enum)packed_val;
    present = true;

    // Fields
    if(internal_choice == k_release)
    {
        if(0 != release_Unpack(bits, idx))
        {
            printf("SoundingRS_UL_ConfigCommon::release unpack failure\n");
            return -1;
        }
    }
    if(internal_choice == k_setup)
    {
        if(0 != setup_value.Unpack(bits, idx))
        {
            printf("SoundingRS_UL_ConfigCommon::setup unpack failure\n");
            return -1;
        }
    }
    return 0;
}

SoundingRS_UL_ConfigCommon::Enum SoundingRS_UL_ConfigCommon::Choice() const
{
    if(present)
        return internal_choice;
    return (SoundingRS_UL_ConfigCommon::Enum)0;
}

int SoundingRS_UL_ConfigCommon::SetChoice(SoundingRS_UL_ConfigCommon::Enum choice)
{
    internal_choice = choice;
    present = true;
    return 0;
}

std::string SoundingRS_UL_ConfigCommon::ChoiceToString(Enum value) const
{
    if(k_release == value)
        return "release";
    if(k_setup == value)
        return "setup";
    return "";
}

uint64_t SoundingRS_UL_ConfigCommon::NumberOfChoices() const
{
    return 2;
}

std::string SoundingRS_UL_ConfigCommon::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "SoundingRS_UL_ConfigCommon = " + ChoiceToString(internal_choice) + ":\n";
    if(internal_choice == k_setup)
        out += setup_value.ToString(indent+1);
    return out;
}

std::string SoundingRS_UL_ConfigCommon::ToStringNoNewLines() const
{
    std::string out = "SoundingRS_UL_ConfigCommon=" + ChoiceToString(internal_choice) + ",";
    if(internal_choice == k_setup)
        out += setup_value.ToStringNoNewLines();
    return out;
}

int SoundingRS_UL_ConfigCommon::Clear()
{
    present = false;
    return 0;
}

bool SoundingRS_UL_ConfigCommon::IsPresent() const
{
    return present;
}

int SoundingRS_UL_ConfigCommon::setup::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(srs_MaxUpPts_IsPresent());

    // Fields
    {
        if(0 != srs_BandwidthConfig_Pack(bits))
        {
            printf("SoundingRS_UL_ConfigCommon::setup:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != srs_SubframeConfig_Pack(bits))
        {
            printf("SoundingRS_UL_ConfigCommon::setup:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != ackNackSRS_SimultaneousTransmission_Pack(bits))
        {
            printf("SoundingRS_UL_ConfigCommon::setup:: field pack failure\n");
            return -1;
        }
    }
    if(srs_MaxUpPts_IsPresent())
    {
        if(0 != srs_MaxUpPts_Pack(bits))
        {
            printf("SoundingRS_UL_ConfigCommon::setup:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int SoundingRS_UL_ConfigCommon::setup::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int SoundingRS_UL_ConfigCommon::setup::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("setup::Unpack() index out of bounds for optional indiator srs_MaxUpPts\n");
        return -1;
    }
    srs_MaxUpPts_present = bits[idx++];

    // Fields
    {
        if(0 != srs_BandwidthConfig_Unpack(bits, idx))
        {
            printf("SoundingRS_UL_ConfigCommon::setup:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != srs_SubframeConfig_Unpack(bits, idx))
        {
            printf("SoundingRS_UL_ConfigCommon::setup:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != ackNackSRS_SimultaneousTransmission_Unpack(bits, idx))
        {
            printf("SoundingRS_UL_ConfigCommon::setup:: field unpack failure\n");
            return -1;
        }
    }
    if(srs_MaxUpPts_present)
    {
        if(0 != srs_MaxUpPts_Unpack(bits, idx))
        {
            printf("SoundingRS_UL_ConfigCommon::setup:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string SoundingRS_UL_ConfigCommon::setup::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "setup:\n";
    out += srs_BandwidthConfig_ToString(indent+1);
    out += srs_SubframeConfig_ToString(indent+1);
    out += ackNackSRS_SimultaneousTransmission_ToString(indent+1);
    if(srs_MaxUpPts_IsPresent())
        out += srs_MaxUpPts_ToString(indent+1);
    return out;
}

std::string SoundingRS_UL_ConfigCommon::setup::ToStringNoNewLines() const
{
    std::string out = "setup:";
    out += srs_BandwidthConfig_ToStringNoNewLines();
    out += srs_SubframeConfig_ToStringNoNewLines();
    out += ackNackSRS_SimultaneousTransmission_ToStringNoNewLines();
    if(srs_MaxUpPts_IsPresent())
        out += srs_MaxUpPts_ToStringNoNewLines();
    return out;
}

int SoundingRS_UL_ConfigCommon::setup::srs_BandwidthConfig_Pack(std::vector<uint8_t> &bits)
{
    if(!srs_BandwidthConfig_present)
    {
        printf("SoundingRS_UL_ConfigCommon::setup::srs_BandwidthConfig_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 3;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((srs_BandwidthConfig_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int SoundingRS_UL_ConfigCommon::setup::srs_BandwidthConfig_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return srs_BandwidthConfig_Unpack(bits, idx);
}

int SoundingRS_UL_ConfigCommon::setup::srs_BandwidthConfig_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 3;
    if((idx + N_bits) > bits.size())
    {
        printf("SoundingRS_UL_ConfigCommon::setup::srs_BandwidthConfig_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 7)
    {
        printf("SoundingRS_UL_ConfigCommon::setup::srs_BandwidthConfig_Unpack() max failure\n");
        return -1;
    }
    srs_BandwidthConfig_internal_value = (srs_BandwidthConfig_Enum)packed_val;
    srs_BandwidthConfig_present = true;
    return 0;
}

SoundingRS_UL_ConfigCommon::setup::srs_BandwidthConfig_Enum SoundingRS_UL_ConfigCommon::setup::srs_BandwidthConfig_Value() const
{
    if(srs_BandwidthConfig_present)
        return srs_BandwidthConfig_internal_value;
    return (SoundingRS_UL_ConfigCommon::setup::srs_BandwidthConfig_Enum)0;
}

int SoundingRS_UL_ConfigCommon::setup::srs_BandwidthConfig_SetValue(srs_BandwidthConfig_Enum value)
{
    srs_BandwidthConfig_internal_value = value;
    srs_BandwidthConfig_present = true;
    return 0;
}

int SoundingRS_UL_ConfigCommon::setup::srs_BandwidthConfig_SetValue(std::string value)
{
    if("bw0" == value)
    {
        srs_BandwidthConfig_internal_value = k_srs_BandwidthConfig_bw0;
        srs_BandwidthConfig_present = true;
        return 0;
    }
    if("bw1" == value)
    {
        srs_BandwidthConfig_internal_value = k_srs_BandwidthConfig_bw1;
        srs_BandwidthConfig_present = true;
        return 0;
    }
    if("bw2" == value)
    {
        srs_BandwidthConfig_internal_value = k_srs_BandwidthConfig_bw2;
        srs_BandwidthConfig_present = true;
        return 0;
    }
    if("bw3" == value)
    {
        srs_BandwidthConfig_internal_value = k_srs_BandwidthConfig_bw3;
        srs_BandwidthConfig_present = true;
        return 0;
    }
    if("bw4" == value)
    {
        srs_BandwidthConfig_internal_value = k_srs_BandwidthConfig_bw4;
        srs_BandwidthConfig_present = true;
        return 0;
    }
    if("bw5" == value)
    {
        srs_BandwidthConfig_internal_value = k_srs_BandwidthConfig_bw5;
        srs_BandwidthConfig_present = true;
        return 0;
    }
    if("bw6" == value)
    {
        srs_BandwidthConfig_internal_value = k_srs_BandwidthConfig_bw6;
        srs_BandwidthConfig_present = true;
        return 0;
    }
    if("bw7" == value)
    {
        srs_BandwidthConfig_internal_value = k_srs_BandwidthConfig_bw7;
        srs_BandwidthConfig_present = true;
        return 0;
    }
    return 1;
}

std::string SoundingRS_UL_ConfigCommon::setup::srs_BandwidthConfig_ValueToString(srs_BandwidthConfig_Enum value) const
{
    if(k_srs_BandwidthConfig_bw0 == value)
        return "bw0";
    if(k_srs_BandwidthConfig_bw1 == value)
        return "bw1";
    if(k_srs_BandwidthConfig_bw2 == value)
        return "bw2";
    if(k_srs_BandwidthConfig_bw3 == value)
        return "bw3";
    if(k_srs_BandwidthConfig_bw4 == value)
        return "bw4";
    if(k_srs_BandwidthConfig_bw5 == value)
        return "bw5";
    if(k_srs_BandwidthConfig_bw6 == value)
        return "bw6";
    if(k_srs_BandwidthConfig_bw7 == value)
        return "bw7";
    return "";
}

uint64_t SoundingRS_UL_ConfigCommon::setup::srs_BandwidthConfig_NumberOfValues() const
{
    return 8;
}

std::string SoundingRS_UL_ConfigCommon::setup::srs_BandwidthConfig_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "srs_BandwidthConfig = " + srs_BandwidthConfig_ValueToString(srs_BandwidthConfig_internal_value) + "\n";
    return out;
}

std::string SoundingRS_UL_ConfigCommon::setup::srs_BandwidthConfig_ToStringNoNewLines() const
{
    std::string out = "srs_BandwidthConfig=" + srs_BandwidthConfig_ValueToString(srs_BandwidthConfig_internal_value) + ",";
    return out;
}

int SoundingRS_UL_ConfigCommon::setup::srs_BandwidthConfig_Clear()
{
    srs_BandwidthConfig_present = false;
    return 0;
}

bool SoundingRS_UL_ConfigCommon::setup::srs_BandwidthConfig_IsPresent() const
{
    return srs_BandwidthConfig_present;
}

int SoundingRS_UL_ConfigCommon::setup::srs_SubframeConfig_Pack(std::vector<uint8_t> &bits)
{
    if(!srs_SubframeConfig_present)
    {
        printf("SoundingRS_UL_ConfigCommon::setup::srs_SubframeConfig_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 4;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((srs_SubframeConfig_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int SoundingRS_UL_ConfigCommon::setup::srs_SubframeConfig_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return srs_SubframeConfig_Unpack(bits, idx);
}

int SoundingRS_UL_ConfigCommon::setup::srs_SubframeConfig_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 4;
    if((idx + N_bits) > bits.size())
    {
        printf("SoundingRS_UL_ConfigCommon::setup::srs_SubframeConfig_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 15)
    {
        printf("SoundingRS_UL_ConfigCommon::setup::srs_SubframeConfig_Unpack() max failure\n");
        return -1;
    }
    srs_SubframeConfig_internal_value = (srs_SubframeConfig_Enum)packed_val;
    srs_SubframeConfig_present = true;
    return 0;
}

SoundingRS_UL_ConfigCommon::setup::srs_SubframeConfig_Enum SoundingRS_UL_ConfigCommon::setup::srs_SubframeConfig_Value() const
{
    if(srs_SubframeConfig_present)
        return srs_SubframeConfig_internal_value;
    return (SoundingRS_UL_ConfigCommon::setup::srs_SubframeConfig_Enum)0;
}

int SoundingRS_UL_ConfigCommon::setup::srs_SubframeConfig_SetValue(srs_SubframeConfig_Enum value)
{
    srs_SubframeConfig_internal_value = value;
    srs_SubframeConfig_present = true;
    return 0;
}

int SoundingRS_UL_ConfigCommon::setup::srs_SubframeConfig_SetValue(std::string value)
{
    if("sc0" == value)
    {
        srs_SubframeConfig_internal_value = k_srs_SubframeConfig_sc0;
        srs_SubframeConfig_present = true;
        return 0;
    }
    if("sc1" == value)
    {
        srs_SubframeConfig_internal_value = k_srs_SubframeConfig_sc1;
        srs_SubframeConfig_present = true;
        return 0;
    }
    if("sc2" == value)
    {
        srs_SubframeConfig_internal_value = k_srs_SubframeConfig_sc2;
        srs_SubframeConfig_present = true;
        return 0;
    }
    if("sc3" == value)
    {
        srs_SubframeConfig_internal_value = k_srs_SubframeConfig_sc3;
        srs_SubframeConfig_present = true;
        return 0;
    }
    if("sc4" == value)
    {
        srs_SubframeConfig_internal_value = k_srs_SubframeConfig_sc4;
        srs_SubframeConfig_present = true;
        return 0;
    }
    if("sc5" == value)
    {
        srs_SubframeConfig_internal_value = k_srs_SubframeConfig_sc5;
        srs_SubframeConfig_present = true;
        return 0;
    }
    if("sc6" == value)
    {
        srs_SubframeConfig_internal_value = k_srs_SubframeConfig_sc6;
        srs_SubframeConfig_present = true;
        return 0;
    }
    if("sc7" == value)
    {
        srs_SubframeConfig_internal_value = k_srs_SubframeConfig_sc7;
        srs_SubframeConfig_present = true;
        return 0;
    }
    if("sc8" == value)
    {
        srs_SubframeConfig_internal_value = k_srs_SubframeConfig_sc8;
        srs_SubframeConfig_present = true;
        return 0;
    }
    if("sc9" == value)
    {
        srs_SubframeConfig_internal_value = k_srs_SubframeConfig_sc9;
        srs_SubframeConfig_present = true;
        return 0;
    }
    if("sc10" == value)
    {
        srs_SubframeConfig_internal_value = k_srs_SubframeConfig_sc10;
        srs_SubframeConfig_present = true;
        return 0;
    }
    if("sc11" == value)
    {
        srs_SubframeConfig_internal_value = k_srs_SubframeConfig_sc11;
        srs_SubframeConfig_present = true;
        return 0;
    }
    if("sc12" == value)
    {
        srs_SubframeConfig_internal_value = k_srs_SubframeConfig_sc12;
        srs_SubframeConfig_present = true;
        return 0;
    }
    if("sc13" == value)
    {
        srs_SubframeConfig_internal_value = k_srs_SubframeConfig_sc13;
        srs_SubframeConfig_present = true;
        return 0;
    }
    if("sc14" == value)
    {
        srs_SubframeConfig_internal_value = k_srs_SubframeConfig_sc14;
        srs_SubframeConfig_present = true;
        return 0;
    }
    if("sc15" == value)
    {
        srs_SubframeConfig_internal_value = k_srs_SubframeConfig_sc15;
        srs_SubframeConfig_present = true;
        return 0;
    }
    return 1;
}

std::string SoundingRS_UL_ConfigCommon::setup::srs_SubframeConfig_ValueToString(srs_SubframeConfig_Enum value) const
{
    if(k_srs_SubframeConfig_sc0 == value)
        return "sc0";
    if(k_srs_SubframeConfig_sc1 == value)
        return "sc1";
    if(k_srs_SubframeConfig_sc2 == value)
        return "sc2";
    if(k_srs_SubframeConfig_sc3 == value)
        return "sc3";
    if(k_srs_SubframeConfig_sc4 == value)
        return "sc4";
    if(k_srs_SubframeConfig_sc5 == value)
        return "sc5";
    if(k_srs_SubframeConfig_sc6 == value)
        return "sc6";
    if(k_srs_SubframeConfig_sc7 == value)
        return "sc7";
    if(k_srs_SubframeConfig_sc8 == value)
        return "sc8";
    if(k_srs_SubframeConfig_sc9 == value)
        return "sc9";
    if(k_srs_SubframeConfig_sc10 == value)
        return "sc10";
    if(k_srs_SubframeConfig_sc11 == value)
        return "sc11";
    if(k_srs_SubframeConfig_sc12 == value)
        return "sc12";
    if(k_srs_SubframeConfig_sc13 == value)
        return "sc13";
    if(k_srs_SubframeConfig_sc14 == value)
        return "sc14";
    if(k_srs_SubframeConfig_sc15 == value)
        return "sc15";
    return "";
}

uint64_t SoundingRS_UL_ConfigCommon::setup::srs_SubframeConfig_NumberOfValues() const
{
    return 16;
}

std::string SoundingRS_UL_ConfigCommon::setup::srs_SubframeConfig_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "srs_SubframeConfig = " + srs_SubframeConfig_ValueToString(srs_SubframeConfig_internal_value) + "\n";
    return out;
}

std::string SoundingRS_UL_ConfigCommon::setup::srs_SubframeConfig_ToStringNoNewLines() const
{
    std::string out = "srs_SubframeConfig=" + srs_SubframeConfig_ValueToString(srs_SubframeConfig_internal_value) + ",";
    return out;
}

int SoundingRS_UL_ConfigCommon::setup::srs_SubframeConfig_Clear()
{
    srs_SubframeConfig_present = false;
    return 0;
}

bool SoundingRS_UL_ConfigCommon::setup::srs_SubframeConfig_IsPresent() const
{
    return srs_SubframeConfig_present;
}

int SoundingRS_UL_ConfigCommon::setup::ackNackSRS_SimultaneousTransmission_Pack(std::vector<uint8_t> &bits)
{
    if(!ackNackSRS_SimultaneousTransmission_present)
    {
        printf("SoundingRS_UL_ConfigCommon::setup::ackNackSRS_SimultaneousTransmission_Pack() presence failure\n");
        return -1;
    }
    bits.push_back(ackNackSRS_SimultaneousTransmission_internal_value);
    return 0;
}

int SoundingRS_UL_ConfigCommon::setup::ackNackSRS_SimultaneousTransmission_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return ackNackSRS_SimultaneousTransmission_Unpack(bits, idx);
}

int SoundingRS_UL_ConfigCommon::setup::ackNackSRS_SimultaneousTransmission_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    if((idx + 1) > bits.size())
    {
        printf("SoundingRS_UL_ConfigCommon::setup::ackNackSRS_SimultaneousTransmission_Unpack() index out of bounds\n");
        return -1;
    }
    ackNackSRS_SimultaneousTransmission_internal_value = bits[idx++];
    ackNackSRS_SimultaneousTransmission_present = true;
    return 0;
}

bool SoundingRS_UL_ConfigCommon::setup::ackNackSRS_SimultaneousTransmission_Value() const
{
    if(ackNackSRS_SimultaneousTransmission_present)
        return ackNackSRS_SimultaneousTransmission_internal_value;
    return false;
}

int SoundingRS_UL_ConfigCommon::setup::ackNackSRS_SimultaneousTransmission_SetValue(bool value)
{
    ackNackSRS_SimultaneousTransmission_internal_value = value;
    ackNackSRS_SimultaneousTransmission_present = true;
    return 0;
}

std::string SoundingRS_UL_ConfigCommon::setup::ackNackSRS_SimultaneousTransmission_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ackNackSRS_SimultaneousTransmission = " + std::to_string(ackNackSRS_SimultaneousTransmission_internal_value) + "\n";
    return out;
}

std::string SoundingRS_UL_ConfigCommon::setup::ackNackSRS_SimultaneousTransmission_ToStringNoNewLines() const
{
    std::string out = "ackNackSRS_SimultaneousTransmission=" + std::to_string(ackNackSRS_SimultaneousTransmission_internal_value) + ",";
    return out;
}

int SoundingRS_UL_ConfigCommon::setup::ackNackSRS_SimultaneousTransmission_Clear()
{
    ackNackSRS_SimultaneousTransmission_present = false;
    return 0;
}

bool SoundingRS_UL_ConfigCommon::setup::ackNackSRS_SimultaneousTransmission_IsPresent() const
{
    return ackNackSRS_SimultaneousTransmission_present;
}

int SoundingRS_UL_ConfigCommon::setup::srs_MaxUpPts_Pack(std::vector<uint8_t> &bits)
{
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((srs_MaxUpPts_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int SoundingRS_UL_ConfigCommon::setup::srs_MaxUpPts_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return srs_MaxUpPts_Unpack(bits, idx);
}

int SoundingRS_UL_ConfigCommon::setup::srs_MaxUpPts_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("SoundingRS_UL_ConfigCommon::setup::srs_MaxUpPts_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 0)
    {
        printf("SoundingRS_UL_ConfigCommon::setup::srs_MaxUpPts_Unpack() max failure\n");
        return -1;
    }
    srs_MaxUpPts_internal_value = (srs_MaxUpPts_Enum)packed_val;
    srs_MaxUpPts_present = true;
    return 0;
}

SoundingRS_UL_ConfigCommon::setup::srs_MaxUpPts_Enum SoundingRS_UL_ConfigCommon::setup::srs_MaxUpPts_Value() const
{
    if(srs_MaxUpPts_present)
        return srs_MaxUpPts_internal_value;
    return (SoundingRS_UL_ConfigCommon::setup::srs_MaxUpPts_Enum)0;
}

int SoundingRS_UL_ConfigCommon::setup::srs_MaxUpPts_SetValue(srs_MaxUpPts_Enum value)
{
    srs_MaxUpPts_internal_value = value;
    srs_MaxUpPts_present = true;
    return 0;
}

int SoundingRS_UL_ConfigCommon::setup::srs_MaxUpPts_SetValue(std::string value)
{
    if("true" == value)
    {
        srs_MaxUpPts_internal_value = k_srs_MaxUpPts_true;
        srs_MaxUpPts_present = true;
        return 0;
    }
    return 1;
}

std::string SoundingRS_UL_ConfigCommon::setup::srs_MaxUpPts_ValueToString(srs_MaxUpPts_Enum value) const
{
    if(k_srs_MaxUpPts_true == value)
        return "true";
    return "";
}

uint64_t SoundingRS_UL_ConfigCommon::setup::srs_MaxUpPts_NumberOfValues() const
{
    return 1;
}

std::string SoundingRS_UL_ConfigCommon::setup::srs_MaxUpPts_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "srs_MaxUpPts = " + srs_MaxUpPts_ValueToString(srs_MaxUpPts_internal_value) + "\n";
    return out;
}

std::string SoundingRS_UL_ConfigCommon::setup::srs_MaxUpPts_ToStringNoNewLines() const
{
    std::string out = "srs_MaxUpPts=" + srs_MaxUpPts_ValueToString(srs_MaxUpPts_internal_value) + ",";
    return out;
}

int SoundingRS_UL_ConfigCommon::setup::srs_MaxUpPts_Clear()
{
    srs_MaxUpPts_present = false;
    return 0;
}

bool SoundingRS_UL_ConfigCommon::setup::srs_MaxUpPts_IsPresent() const
{
    return srs_MaxUpPts_present;
}

