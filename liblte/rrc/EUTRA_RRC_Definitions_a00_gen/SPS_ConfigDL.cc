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

#include "SPS_ConfigDL.h"

#include <cmath>

int SPS_ConfigDL::Pack(std::vector<uint8_t> &bits)
{
    if(!present)
    {
        printf("SPS_ConfigDL::Pack() presence failure\n");
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
            printf("SPS_ConfigDL::release pack failure\n");
            return -1;
        }
    }
    if(internal_choice == k_setup)
    {
        if(0 != setup_value.Pack(bits))
        {
            printf("SPS_ConfigDL::setup pack failure\n");
            return -1;
        }
    }
    return 0;
}

int SPS_ConfigDL::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int SPS_ConfigDL::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 1) > bits.size())
    {
        printf("SPS_ConfigDL::Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<1; i++)
        packed_val |= bits[idx++] << (1-i-1);

    if((SPS_ConfigDL::Enum)packed_val > k_setup)
    {
        printf("SPS_ConfigDL::Unpack() choice range failure\n");
        return -1;
    }
    internal_choice = (SPS_ConfigDL::Enum)packed_val;
    present = true;

    // Fields
    if(internal_choice == k_release)
    {
        if(0 != release_Unpack(bits, idx))
        {
            printf("SPS_ConfigDL::release unpack failure\n");
            return -1;
        }
    }
    if(internal_choice == k_setup)
    {
        if(0 != setup_value.Unpack(bits, idx))
        {
            printf("SPS_ConfigDL::setup unpack failure\n");
            return -1;
        }
    }
    return 0;
}

SPS_ConfigDL::Enum SPS_ConfigDL::Choice() const
{
    if(present)
        return internal_choice;
    return (SPS_ConfigDL::Enum)0;
}

int SPS_ConfigDL::SetChoice(SPS_ConfigDL::Enum choice)
{
    internal_choice = choice;
    present = true;
    return 0;
}

std::string SPS_ConfigDL::ChoiceToString(Enum value) const
{
    if(k_release == value)
        return "release";
    if(k_setup == value)
        return "setup";
    return "";
}

uint64_t SPS_ConfigDL::NumberOfChoices() const
{
    return 2;
}

std::string SPS_ConfigDL::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "SPS_ConfigDL = " + ChoiceToString(internal_choice) + ":\n";
    if(internal_choice == k_setup)
        out += setup_value.ToString(indent+1);
    return out;
}

std::string SPS_ConfigDL::ToStringNoNewLines() const
{
    std::string out = "SPS_ConfigDL=" + ChoiceToString(internal_choice) + ",";
    if(internal_choice == k_setup)
        out += setup_value.ToStringNoNewLines();
    return out;
}

int SPS_ConfigDL::Clear()
{
    present = false;
    return 0;
}

bool SPS_ConfigDL::IsPresent() const
{
    return present;
}

int SPS_ConfigDL::setup::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator
    bool has_extension = false;
    if(twoAntennaPortActivated_r10_IsPresent() || n1_PUCCH_AN_PersistentListP1_r10_IsPresent())
    {
        bits.push_back(1);
        has_extension = true;
    }else{
        bits.push_back(0);
    }

    // Optional indicators

    // Fields
    {
        if(0 != semiPersistSchedIntervalDL_Pack(bits))
        {
            printf("SPS_ConfigDL::setup:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != numberOfConfSPS_Processes_Pack(bits))
        {
            printf("SPS_ConfigDL::setup:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != n1_PUCCH_AN_PersistentList.Pack(bits))
        {
            printf("SPS_ConfigDL::setup:: field pack failure\n");
            return -1;
        }
    }

    // Extension
    if(has_extension)
    {
        // Number of extension fields
        if(1 < 64)
        {
            bits.push_back(0);
            for(uint32_t i=0; i<6; i++)
                bits.push_back((1 >> (6-i-1)) & 1);
        }else{
            printf("setup:: Extension list size too large failure\n");
            return -1;
        }

        // Extension field presence indicators
        bits.push_back(twoAntennaPortActivated_r10_IsPresent());
        bits.push_back(n1_PUCCH_AN_PersistentListP1_r10_IsPresent());

        // Extension fields
        if(twoAntennaPortActivated_r10_IsPresent())
        {
            std::vector<uint8_t> field_bits;
            if(0 != twoAntennaPortActivated_r10_Pack(field_bits))
            {
                printf("SPS_ConfigDL::setup:: field pack failure\n");
                return -1;
            }
            while((field_bits.size() % 8) != 0)
                field_bits.push_back(0);
            uint32_t N_octets = field_bits.size() / 8;
            uint32_t local_size_length = 0;
            uint32_t local_size = N_octets;
            if(local_size < 128)
            {
                bits.push_back(0);
                local_size_length = 7;
            }else if(local_size < 16383){
                bits.push_back(1);
                bits.push_back(0);
                local_size_length = 14;
            }else{
                bits.push_back(1);
                bits.push_back(1);
                uint32_t N_16k_blocks = local_size / 16383;
                for(uint32_t i=0; i<6; i++)
                    bits.push_back((N_16k_blocks >> (6-i-1)) & 1);
                local_size %= 16383;
                if(local_size < 128)
                {
                    bits.push_back(0);
                    local_size_length = 7;
                }else{
                    bits.push_back(1);
                    bits.push_back(0);
                    local_size_length = 14;
                }
            }
            for(uint32_t i=0; i<local_size_length; i++)
                bits.push_back((local_size >> (local_size_length-i-1)) & 1);
            for(auto b : field_bits)
                bits.push_back(b);
        }
        if(n1_PUCCH_AN_PersistentListP1_r10_IsPresent())
        {
            std::vector<uint8_t> field_bits;
            if(0 != n1_PUCCH_AN_PersistentListP1_r10.Pack(field_bits))
            {
                printf("SPS_ConfigDL::setup:: field pack failure\n");
                return -1;
            }
            while((field_bits.size() % 8) != 0)
                field_bits.push_back(0);
            uint32_t N_octets = field_bits.size() / 8;
            uint32_t local_size_length = 0;
            uint32_t local_size = N_octets;
            if(local_size < 128)
            {
                bits.push_back(0);
                local_size_length = 7;
            }else if(local_size < 16383){
                bits.push_back(1);
                bits.push_back(0);
                local_size_length = 14;
            }else{
                bits.push_back(1);
                bits.push_back(1);
                uint32_t N_16k_blocks = local_size / 16383;
                for(uint32_t i=0; i<6; i++)
                    bits.push_back((N_16k_blocks >> (6-i-1)) & 1);
                local_size %= 16383;
                if(local_size < 128)
                {
                    bits.push_back(0);
                    local_size_length = 7;
                }else{
                    bits.push_back(1);
                    bits.push_back(0);
                    local_size_length = 14;
                }
            }
            for(uint32_t i=0; i<local_size_length; i++)
                bits.push_back((local_size >> (local_size_length-i-1)) & 1);
            for(auto b : field_bits)
                bits.push_back(b);
        }
    }
    return 0;
}

int SPS_ConfigDL::setup::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int SPS_ConfigDL::setup::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("setup::Unpack() index out of bounds for extension\n");
        return -1;
    }
    bool has_extension = bits[idx++];

    // Optional indicators

    // Fields
    {
        if(0 != semiPersistSchedIntervalDL_Unpack(bits, idx))
        {
            printf("SPS_ConfigDL::setup:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != numberOfConfSPS_Processes_Unpack(bits, idx))
        {
            printf("SPS_ConfigDL::setup:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != n1_PUCCH_AN_PersistentList.Unpack(bits, idx))
        {
            printf("SPS_ConfigDL::setup:: field unpack failure\n");
            return -1;
        }
    }

    // Extension
    if(has_extension)
    {
        if((idx + 7) > bits.size())
        {
            printf("setup::Unpack() index out of bounds for extension size\n");
            return -1;
        }
        // Number of extension fields
        if(bits[idx++] != 0)
        {
            printf("setup:: Extension list size too large failure\n");
            return -1;
        }
        uint32_t N_ext_fields = 0;
        for(uint32_t i=0; i<6; i++)
            N_ext_fields |= bits[idx++] << (6-i-1);
        N_ext_fields++;

        // Extension field presence indicators
        uint32_t opt_ind_count = 0;
        if(opt_ind_count++ < N_ext_fields)
        {
            if((idx + 1) > bits.size())
            {
                printf("setup::Unpack() index out of bounds for optional indiator twoAntennaPortActivated_r10\n");
                return -1;
            }
            twoAntennaPortActivated_r10_present = bits[idx++];
        }
        if(opt_ind_count++ < N_ext_fields)
        {
            if((idx + 1) > bits.size())
            {
                printf("setup::Unpack() index out of bounds for optional indiator n1_PUCCH_AN_PersistentListP1_r10\n");
                return -1;
            }
            n1_PUCCH_AN_PersistentListP1_r10_present = bits[idx++];
        }
        if((idx + (N_ext_fields - opt_ind_count)) > bits.size())
        {
            printf("setup::Unpack() index out of bounds for extension optional indicators\n");
            return -1;
        }
        idx += (N_ext_fields - opt_ind_count);

        // Extension fields
        if(twoAntennaPortActivated_r10_present)
        {
            uint32_t local_size_length = 0;
            uint32_t N_octets = 0;
            if(0 == bits[idx++])
            {
                local_size_length = 7;
            }else{
                if(0 == bits[idx++])
                {
                    local_size_length = 14;
                }else{
                    for(uint32_t i=0; i<6; i++)
                        N_octets |= bits[idx++] << (6-i-1);
                    N_octets *= 16383;
                    if(0 == bits[idx++])
                    {
                        local_size_length = 7;
                    }else{
                        idx++;
                        local_size_length = 14;
                    }
                }
            }
            for(uint32_t i=0; i<local_size_length; i++)
                N_octets |= bits[idx++] << (local_size_length-i-1);
            uint32_t orig_idx = idx;
            if(0 != twoAntennaPortActivated_r10_Unpack(bits, idx))
            {
                printf("SPS_ConfigDL::setup:: field unpack failure\n");
                return -1;
            }
            idx = orig_idx + (N_octets * 8);
        }
        if(n1_PUCCH_AN_PersistentListP1_r10_present)
        {
            uint32_t local_size_length = 0;
            uint32_t N_octets = 0;
            if(0 == bits[idx++])
            {
                local_size_length = 7;
            }else{
                if(0 == bits[idx++])
                {
                    local_size_length = 14;
                }else{
                    for(uint32_t i=0; i<6; i++)
                        N_octets |= bits[idx++] << (6-i-1);
                    N_octets *= 16383;
                    if(0 == bits[idx++])
                    {
                        local_size_length = 7;
                    }else{
                        idx++;
                        local_size_length = 14;
                    }
                }
            }
            for(uint32_t i=0; i<local_size_length; i++)
                N_octets |= bits[idx++] << (local_size_length-i-1);
            uint32_t orig_idx = idx;
            if(0 != n1_PUCCH_AN_PersistentListP1_r10.Unpack(bits, idx))
            {
                printf("SPS_ConfigDL::setup:: field unpack failure\n");
                return -1;
            }
            idx = orig_idx + (N_octets * 8);
        }
        for(uint32_t i=2; i<N_ext_fields; i++)
        {
            uint32_t local_size_length = 0;
            uint32_t N_octets = 0;
            if(0 == bits[idx++])
            {
                local_size_length = 7;
            }else{
                if(0 == bits[idx++])
                {
                    local_size_length = 14;
                }else{
                    for(uint32_t i=0; i<6; i++)
                        N_octets |= bits[idx++] << (6-i-1);
                    N_octets *= 16383;
                    if(0 == bits[idx++])
                    {
                        local_size_length = 7;
                    }else{
                        idx++;
                        local_size_length = 14;
                    }
                }
            }
            for(uint32_t i=0; i<local_size_length; i++)
                N_octets |= bits[idx++] << (local_size_length-i-1);
        if((idx + (N_octets * 8)) > bits.size())
        {
            printf("setup::Unpack() index out of bounds for extension fields\n");
            return -1;
        }
            idx += N_octets * 8;
        }
    }
    return 0;
}

std::string SPS_ConfigDL::setup::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "setup:\n";
    out += semiPersistSchedIntervalDL_ToString(indent+1);
    out += numberOfConfSPS_Processes_ToString(indent+1);
    out += n1_PUCCH_AN_PersistentList_ToString(indent+1);
    if(twoAntennaPortActivated_r10_IsPresent())
        out += twoAntennaPortActivated_r10_ToString(indent+1);
    if(n1_PUCCH_AN_PersistentListP1_r10_IsPresent())
        out += n1_PUCCH_AN_PersistentListP1_r10_ToString(indent+1);
    return out;
}

std::string SPS_ConfigDL::setup::ToStringNoNewLines() const
{
    std::string out = "setup:";
    out += semiPersistSchedIntervalDL_ToStringNoNewLines();
    out += numberOfConfSPS_Processes_ToStringNoNewLines();
    out += n1_PUCCH_AN_PersistentList_ToStringNoNewLines();
    if(twoAntennaPortActivated_r10_IsPresent())
        out += twoAntennaPortActivated_r10_ToStringNoNewLines();
    if(n1_PUCCH_AN_PersistentListP1_r10_IsPresent())
        out += n1_PUCCH_AN_PersistentListP1_r10_ToStringNoNewLines();
    return out;
}

int SPS_ConfigDL::setup::semiPersistSchedIntervalDL_Pack(std::vector<uint8_t> &bits)
{
    if(!semiPersistSchedIntervalDL_present)
    {
        printf("SPS_ConfigDL::setup::semiPersistSchedIntervalDL_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 4;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((semiPersistSchedIntervalDL_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int SPS_ConfigDL::setup::semiPersistSchedIntervalDL_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return semiPersistSchedIntervalDL_Unpack(bits, idx);
}

int SPS_ConfigDL::setup::semiPersistSchedIntervalDL_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 4;
    if((idx + N_bits) > bits.size())
    {
        printf("SPS_ConfigDL::setup::semiPersistSchedIntervalDL_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 15)
    {
        printf("SPS_ConfigDL::setup::semiPersistSchedIntervalDL_Unpack() max failure\n");
        return -1;
    }
    semiPersistSchedIntervalDL_internal_value = (semiPersistSchedIntervalDL_Enum)packed_val;
    semiPersistSchedIntervalDL_present = true;
    return 0;
}

SPS_ConfigDL::setup::semiPersistSchedIntervalDL_Enum SPS_ConfigDL::setup::semiPersistSchedIntervalDL_Value() const
{
    if(semiPersistSchedIntervalDL_present)
        return semiPersistSchedIntervalDL_internal_value;
    return (SPS_ConfigDL::setup::semiPersistSchedIntervalDL_Enum)0;
}

int SPS_ConfigDL::setup::semiPersistSchedIntervalDL_SetValue(semiPersistSchedIntervalDL_Enum value)
{
    semiPersistSchedIntervalDL_internal_value = value;
    semiPersistSchedIntervalDL_present = true;
    return 0;
}

int SPS_ConfigDL::setup::semiPersistSchedIntervalDL_SetValue(std::string value)
{
    if("sf10" == value)
    {
        semiPersistSchedIntervalDL_internal_value = k_semiPersistSchedIntervalDL_sf10;
        semiPersistSchedIntervalDL_present = true;
        return 0;
    }
    if("sf20" == value)
    {
        semiPersistSchedIntervalDL_internal_value = k_semiPersistSchedIntervalDL_sf20;
        semiPersistSchedIntervalDL_present = true;
        return 0;
    }
    if("sf32" == value)
    {
        semiPersistSchedIntervalDL_internal_value = k_semiPersistSchedIntervalDL_sf32;
        semiPersistSchedIntervalDL_present = true;
        return 0;
    }
    if("sf40" == value)
    {
        semiPersistSchedIntervalDL_internal_value = k_semiPersistSchedIntervalDL_sf40;
        semiPersistSchedIntervalDL_present = true;
        return 0;
    }
    if("sf64" == value)
    {
        semiPersistSchedIntervalDL_internal_value = k_semiPersistSchedIntervalDL_sf64;
        semiPersistSchedIntervalDL_present = true;
        return 0;
    }
    if("sf80" == value)
    {
        semiPersistSchedIntervalDL_internal_value = k_semiPersistSchedIntervalDL_sf80;
        semiPersistSchedIntervalDL_present = true;
        return 0;
    }
    if("sf128" == value)
    {
        semiPersistSchedIntervalDL_internal_value = k_semiPersistSchedIntervalDL_sf128;
        semiPersistSchedIntervalDL_present = true;
        return 0;
    }
    if("sf160" == value)
    {
        semiPersistSchedIntervalDL_internal_value = k_semiPersistSchedIntervalDL_sf160;
        semiPersistSchedIntervalDL_present = true;
        return 0;
    }
    if("sf320" == value)
    {
        semiPersistSchedIntervalDL_internal_value = k_semiPersistSchedIntervalDL_sf320;
        semiPersistSchedIntervalDL_present = true;
        return 0;
    }
    if("sf640" == value)
    {
        semiPersistSchedIntervalDL_internal_value = k_semiPersistSchedIntervalDL_sf640;
        semiPersistSchedIntervalDL_present = true;
        return 0;
    }
    if("spare6" == value)
    {
        semiPersistSchedIntervalDL_internal_value = k_semiPersistSchedIntervalDL_spare6;
        semiPersistSchedIntervalDL_present = true;
        return 0;
    }
    if("spare5" == value)
    {
        semiPersistSchedIntervalDL_internal_value = k_semiPersistSchedIntervalDL_spare5;
        semiPersistSchedIntervalDL_present = true;
        return 0;
    }
    if("spare4" == value)
    {
        semiPersistSchedIntervalDL_internal_value = k_semiPersistSchedIntervalDL_spare4;
        semiPersistSchedIntervalDL_present = true;
        return 0;
    }
    if("spare3" == value)
    {
        semiPersistSchedIntervalDL_internal_value = k_semiPersistSchedIntervalDL_spare3;
        semiPersistSchedIntervalDL_present = true;
        return 0;
    }
    if("spare2" == value)
    {
        semiPersistSchedIntervalDL_internal_value = k_semiPersistSchedIntervalDL_spare2;
        semiPersistSchedIntervalDL_present = true;
        return 0;
    }
    if("spare1" == value)
    {
        semiPersistSchedIntervalDL_internal_value = k_semiPersistSchedIntervalDL_spare1;
        semiPersistSchedIntervalDL_present = true;
        return 0;
    }
    return 1;
}

std::string SPS_ConfigDL::setup::semiPersistSchedIntervalDL_ValueToString(semiPersistSchedIntervalDL_Enum value) const
{
    if(k_semiPersistSchedIntervalDL_sf10 == value)
        return "sf10";
    if(k_semiPersistSchedIntervalDL_sf20 == value)
        return "sf20";
    if(k_semiPersistSchedIntervalDL_sf32 == value)
        return "sf32";
    if(k_semiPersistSchedIntervalDL_sf40 == value)
        return "sf40";
    if(k_semiPersistSchedIntervalDL_sf64 == value)
        return "sf64";
    if(k_semiPersistSchedIntervalDL_sf80 == value)
        return "sf80";
    if(k_semiPersistSchedIntervalDL_sf128 == value)
        return "sf128";
    if(k_semiPersistSchedIntervalDL_sf160 == value)
        return "sf160";
    if(k_semiPersistSchedIntervalDL_sf320 == value)
        return "sf320";
    if(k_semiPersistSchedIntervalDL_sf640 == value)
        return "sf640";
    if(k_semiPersistSchedIntervalDL_spare6 == value)
        return "spare6";
    if(k_semiPersistSchedIntervalDL_spare5 == value)
        return "spare5";
    if(k_semiPersistSchedIntervalDL_spare4 == value)
        return "spare4";
    if(k_semiPersistSchedIntervalDL_spare3 == value)
        return "spare3";
    if(k_semiPersistSchedIntervalDL_spare2 == value)
        return "spare2";
    if(k_semiPersistSchedIntervalDL_spare1 == value)
        return "spare1";
    return "";
}

uint64_t SPS_ConfigDL::setup::semiPersistSchedIntervalDL_NumberOfValues() const
{
    return 16;
}

std::string SPS_ConfigDL::setup::semiPersistSchedIntervalDL_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "semiPersistSchedIntervalDL = " + semiPersistSchedIntervalDL_ValueToString(semiPersistSchedIntervalDL_internal_value) + "\n";
    return out;
}

std::string SPS_ConfigDL::setup::semiPersistSchedIntervalDL_ToStringNoNewLines() const
{
    std::string out = "semiPersistSchedIntervalDL=" + semiPersistSchedIntervalDL_ValueToString(semiPersistSchedIntervalDL_internal_value) + ",";
    return out;
}

int SPS_ConfigDL::setup::semiPersistSchedIntervalDL_Clear()
{
    semiPersistSchedIntervalDL_present = false;
    return 0;
}

bool SPS_ConfigDL::setup::semiPersistSchedIntervalDL_IsPresent() const
{
    return semiPersistSchedIntervalDL_present;
}

int SPS_ConfigDL::setup::numberOfConfSPS_Processes_Pack(std::vector<uint8_t> &bits)
{
    if(!numberOfConfSPS_Processes_present)
    {
        printf("SPS_ConfigDL::setup::numberOfConfSPS_Processes_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = numberOfConfSPS_Processes_internal_value - (1);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (8 - 1))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int SPS_ConfigDL::setup::numberOfConfSPS_Processes_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return numberOfConfSPS_Processes_Unpack(bits, idx);
}

int SPS_ConfigDL::setup::numberOfConfSPS_Processes_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (8 - 1))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("SPS_ConfigDL::setup::numberOfConfSPS_Processes_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    numberOfConfSPS_Processes_internal_value = packed_val + 1;
    numberOfConfSPS_Processes_present = true;
    return 0;
}

int64_t SPS_ConfigDL::setup::numberOfConfSPS_Processes_Value() const
{
    if(numberOfConfSPS_Processes_present)
        return numberOfConfSPS_Processes_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int SPS_ConfigDL::setup::numberOfConfSPS_Processes_SetValue(int64_t value)
{
    if(value < 1 || value > 8)
    {
        printf("SPS_ConfigDL::setup::numberOfConfSPS_Processes_SetValue() range failure\n");
        return -1;
    }
    numberOfConfSPS_Processes_internal_value = value;
    numberOfConfSPS_Processes_present = true;
    return 0;
}

std::string SPS_ConfigDL::setup::numberOfConfSPS_Processes_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "numberOfConfSPS_Processes = " + std::to_string(numberOfConfSPS_Processes_internal_value) + "\n";
    return out;
}

std::string SPS_ConfigDL::setup::numberOfConfSPS_Processes_ToStringNoNewLines() const
{
    std::string out = "numberOfConfSPS_Processes=" + std::to_string(numberOfConfSPS_Processes_internal_value) + ",";
    return out;
}

int SPS_ConfigDL::setup::numberOfConfSPS_Processes_Clear()
{
    numberOfConfSPS_Processes_present = false;
    return 0;
}

bool SPS_ConfigDL::setup::numberOfConfSPS_Processes_IsPresent() const
{
    return numberOfConfSPS_Processes_present;
}

N1_PUCCH_AN_PersistentList* SPS_ConfigDL::setup::n1_PUCCH_AN_PersistentList_Set()
{
    n1_PUCCH_AN_PersistentList_present = true;
    return &n1_PUCCH_AN_PersistentList;
}

int SPS_ConfigDL::setup::n1_PUCCH_AN_PersistentList_Set(N1_PUCCH_AN_PersistentList &value)
{
    n1_PUCCH_AN_PersistentList_present = true;
    n1_PUCCH_AN_PersistentList = value;
    return 0;
}

const N1_PUCCH_AN_PersistentList& SPS_ConfigDL::setup::n1_PUCCH_AN_PersistentList_Get() const
{
    return n1_PUCCH_AN_PersistentList;
}

std::string SPS_ConfigDL::setup::n1_PUCCH_AN_PersistentList_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "n1_PUCCH_AN_PersistentList:\n";
    out += n1_PUCCH_AN_PersistentList.ToString(indent+1);
    return out;
}

std::string SPS_ConfigDL::setup::n1_PUCCH_AN_PersistentList_ToStringNoNewLines() const
{
    std::string out = "n1_PUCCH_AN_PersistentList:";
    out += n1_PUCCH_AN_PersistentList.ToStringNoNewLines();
    return out;
}

int SPS_ConfigDL::setup::n1_PUCCH_AN_PersistentList_Clear()
{
    n1_PUCCH_AN_PersistentList_present = false;
    return 0;
}

bool SPS_ConfigDL::setup::n1_PUCCH_AN_PersistentList_IsPresent() const
{
    return n1_PUCCH_AN_PersistentList_present;
}

int SPS_ConfigDL::setup::twoAntennaPortActivated_r10_Pack(std::vector<uint8_t> &bits)
{
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((twoAntennaPortActivated_r10_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int SPS_ConfigDL::setup::twoAntennaPortActivated_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return twoAntennaPortActivated_r10_Unpack(bits, idx);
}

int SPS_ConfigDL::setup::twoAntennaPortActivated_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("SPS_ConfigDL::setup::twoAntennaPortActivated_r10_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 0)
    {
        printf("SPS_ConfigDL::setup::twoAntennaPortActivated_r10_Unpack() max failure\n");
        return -1;
    }
    twoAntennaPortActivated_r10_internal_value = (twoAntennaPortActivated_r10_Enum)packed_val;
    twoAntennaPortActivated_r10_present = true;
    return 0;
}

SPS_ConfigDL::setup::twoAntennaPortActivated_r10_Enum SPS_ConfigDL::setup::twoAntennaPortActivated_r10_Value() const
{
    if(twoAntennaPortActivated_r10_present)
        return twoAntennaPortActivated_r10_internal_value;
    return (SPS_ConfigDL::setup::twoAntennaPortActivated_r10_Enum)0;
}

int SPS_ConfigDL::setup::twoAntennaPortActivated_r10_SetValue(twoAntennaPortActivated_r10_Enum value)
{
    twoAntennaPortActivated_r10_internal_value = value;
    twoAntennaPortActivated_r10_present = true;
    return 0;
}

int SPS_ConfigDL::setup::twoAntennaPortActivated_r10_SetValue(std::string value)
{
    if("true" == value)
    {
        twoAntennaPortActivated_r10_internal_value = k_twoAntennaPortActivated_r10_true;
        twoAntennaPortActivated_r10_present = true;
        return 0;
    }
    return 1;
}

std::string SPS_ConfigDL::setup::twoAntennaPortActivated_r10_ValueToString(twoAntennaPortActivated_r10_Enum value) const
{
    if(k_twoAntennaPortActivated_r10_true == value)
        return "true";
    return "";
}

uint64_t SPS_ConfigDL::setup::twoAntennaPortActivated_r10_NumberOfValues() const
{
    return 1;
}

std::string SPS_ConfigDL::setup::twoAntennaPortActivated_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "twoAntennaPortActivated_r10 = " + twoAntennaPortActivated_r10_ValueToString(twoAntennaPortActivated_r10_internal_value) + "\n";
    return out;
}

std::string SPS_ConfigDL::setup::twoAntennaPortActivated_r10_ToStringNoNewLines() const
{
    std::string out = "twoAntennaPortActivated_r10=" + twoAntennaPortActivated_r10_ValueToString(twoAntennaPortActivated_r10_internal_value) + ",";
    return out;
}

int SPS_ConfigDL::setup::twoAntennaPortActivated_r10_Clear()
{
    twoAntennaPortActivated_r10_present = false;
    return 0;
}

bool SPS_ConfigDL::setup::twoAntennaPortActivated_r10_IsPresent() const
{
    return twoAntennaPortActivated_r10_present;
}

N1_PUCCH_AN_PersistentList* SPS_ConfigDL::setup::n1_PUCCH_AN_PersistentListP1_r10_Set()
{
    n1_PUCCH_AN_PersistentListP1_r10_present = true;
    return &n1_PUCCH_AN_PersistentListP1_r10;
}

int SPS_ConfigDL::setup::n1_PUCCH_AN_PersistentListP1_r10_Set(N1_PUCCH_AN_PersistentList &value)
{
    n1_PUCCH_AN_PersistentListP1_r10_present = true;
    n1_PUCCH_AN_PersistentListP1_r10 = value;
    return 0;
}

const N1_PUCCH_AN_PersistentList& SPS_ConfigDL::setup::n1_PUCCH_AN_PersistentListP1_r10_Get() const
{
    return n1_PUCCH_AN_PersistentListP1_r10;
}

std::string SPS_ConfigDL::setup::n1_PUCCH_AN_PersistentListP1_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "n1_PUCCH_AN_PersistentListP1_r10:\n";
    out += n1_PUCCH_AN_PersistentListP1_r10.ToString(indent+1);
    return out;
}

std::string SPS_ConfigDL::setup::n1_PUCCH_AN_PersistentListP1_r10_ToStringNoNewLines() const
{
    std::string out = "n1_PUCCH_AN_PersistentListP1_r10:";
    out += n1_PUCCH_AN_PersistentListP1_r10.ToStringNoNewLines();
    return out;
}

int SPS_ConfigDL::setup::n1_PUCCH_AN_PersistentListP1_r10_Clear()
{
    n1_PUCCH_AN_PersistentListP1_r10_present = false;
    return 0;
}

bool SPS_ConfigDL::setup::n1_PUCCH_AN_PersistentListP1_r10_IsPresent() const
{
    return n1_PUCCH_AN_PersistentListP1_r10_present;
}

