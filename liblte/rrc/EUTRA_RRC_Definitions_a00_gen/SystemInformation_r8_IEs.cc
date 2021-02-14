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

#include "SystemInformation_r8_IEs.h"

#include <cmath>

int SystemInformation_r8_IEs::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(nonCriticalExtension_IsPresent());

    // Fields
    {
        if(0 != sib_TypeAndInfo_Pack(bits))
        {
            printf("SystemInformation_r8_IEs:: field pack failure\n");
            return -1;
        }
    }
    if(nonCriticalExtension_IsPresent())
    {
        if(0 != nonCriticalExtension.Pack(bits))
        {
            printf("SystemInformation_r8_IEs:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int SystemInformation_r8_IEs::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int SystemInformation_r8_IEs::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("SystemInformation_r8_IEs::Unpack() index out of bounds for optional indiator nonCriticalExtension\n");
        return -1;
    }
    nonCriticalExtension_present = bits[idx++];

    // Fields
    {
        if(0 != sib_TypeAndInfo_Unpack(bits, idx))
        {
            printf("SystemInformation_r8_IEs:: field unpack failure\n");
            return -1;
        }
    }
    if(nonCriticalExtension_present)
    {
        if(0 != nonCriticalExtension.Unpack(bits, idx))
        {
            printf("SystemInformation_r8_IEs:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string SystemInformation_r8_IEs::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "SystemInformation_r8_IEs:\n";
    out += sib_TypeAndInfo_ToString(indent+1);
    if(nonCriticalExtension_IsPresent())
        out += nonCriticalExtension_ToString(indent+1);
    return out;
}

std::string SystemInformation_r8_IEs::ToStringNoNewLines() const
{
    std::string out = "SystemInformation_r8_IEs:";
    out += sib_TypeAndInfo_ToStringNoNewLines();
    if(nonCriticalExtension_IsPresent())
        out += nonCriticalExtension_ToStringNoNewLines();
    return out;
}

int SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_Pack(std::vector<uint8_t> &bits)
{
    if(!sib_TypeAndInfo_present)
    {
        printf("SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_Pack() presence failure\n");
        return -1;
    }
    // Extension indicator
    bool is_extended = false;
    if(sib_TypeAndInfo_internal_choice > k_sib_TypeAndInfo_sib11)
    {
        is_extended = true;
        bits.push_back(1);
    }else{
        bits.push_back(0);
    }

    // Choice
    if(is_extended)
    {
        bits.push_back(0);
        for(uint32_t i=0; i<6; i++)
            bits.push_back(((sib_TypeAndInfo_internal_choice - k_sib_TypeAndInfo_sib12_v920) >> (6-i-1)) & 1);
    }else{
        for(uint32_t i=0; i<4; i++)
            bits.push_back((sib_TypeAndInfo_internal_choice >> (4-i-1)) & 1);
    }

    // Fields
    if(sib_TypeAndInfo_internal_choice == k_sib_TypeAndInfo_sib2)
    {
        if(0 != sib_TypeAndInfo_sib2.Pack(bits))
        {
            printf("SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib2 pack failure\n");
            return -1;
        }
    }
    if(sib_TypeAndInfo_internal_choice == k_sib_TypeAndInfo_sib3)
    {
        if(0 != sib_TypeAndInfo_sib3.Pack(bits))
        {
            printf("SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib3 pack failure\n");
            return -1;
        }
    }
    if(sib_TypeAndInfo_internal_choice == k_sib_TypeAndInfo_sib4)
    {
        if(0 != sib_TypeAndInfo_sib4.Pack(bits))
        {
            printf("SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib4 pack failure\n");
            return -1;
        }
    }
    if(sib_TypeAndInfo_internal_choice == k_sib_TypeAndInfo_sib5)
    {
        if(0 != sib_TypeAndInfo_sib5.Pack(bits))
        {
            printf("SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib5 pack failure\n");
            return -1;
        }
    }
    if(sib_TypeAndInfo_internal_choice == k_sib_TypeAndInfo_sib6)
    {
        if(0 != sib_TypeAndInfo_sib6.Pack(bits))
        {
            printf("SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib6 pack failure\n");
            return -1;
        }
    }
    if(sib_TypeAndInfo_internal_choice == k_sib_TypeAndInfo_sib7)
    {
        if(0 != sib_TypeAndInfo_sib7.Pack(bits))
        {
            printf("SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib7 pack failure\n");
            return -1;
        }
    }
    if(sib_TypeAndInfo_internal_choice == k_sib_TypeAndInfo_sib8)
    {
        if(0 != sib_TypeAndInfo_sib8.Pack(bits))
        {
            printf("SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib8 pack failure\n");
            return -1;
        }
    }
    if(sib_TypeAndInfo_internal_choice == k_sib_TypeAndInfo_sib9)
    {
        if(0 != sib_TypeAndInfo_sib9.Pack(bits))
        {
            printf("SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib9 pack failure\n");
            return -1;
        }
    }
    if(sib_TypeAndInfo_internal_choice == k_sib_TypeAndInfo_sib10)
    {
        if(0 != sib_TypeAndInfo_sib10.Pack(bits))
        {
            printf("SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib10 pack failure\n");
            return -1;
        }
    }
    if(sib_TypeAndInfo_internal_choice == k_sib_TypeAndInfo_sib11)
    {
        if(0 != sib_TypeAndInfo_sib11.Pack(bits))
        {
            printf("SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib11 pack failure\n");
            return -1;
        }
    }

    // Extension
    if(is_extended)
    {
        std::vector<uint8_t> ext_bits;
        if(sib_TypeAndInfo_internal_choice == k_sib_TypeAndInfo_sib12_v920)
        {
            if(0 != sib_TypeAndInfo_sib12_v920.Pack(ext_bits))
            {
                printf("SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib12_v920 pack failure\n");
                return -1;
            }
        }
        if(sib_TypeAndInfo_internal_choice == k_sib_TypeAndInfo_sib13_v920)
        {
            if(0 != sib_TypeAndInfo_sib13_v920.Pack(ext_bits))
            {
                printf("SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib13_v920 pack failure\n");
                return -1;
            }
        }
        while((ext_bits.size() % 8) != 0)
            ext_bits.push_back(0);
        uint32_t N_octets = ext_bits.size() / 8;
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
        for(auto b : ext_bits)
            bits.push_back(b);
    }
    return 0;
}

int SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return sib_TypeAndInfo_Unpack(bits, idx);
}

int SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_Unpack() index out of bounds for extension\n");
        return -1;
    }
    bool is_extended = bits[idx++];

    // Choice
    if(is_extended)
    {
        if((idx + 7) > bits.size())
        {
            printf("SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_Unpack() index out of bounds for extension size\n");
            return -1;
        }
        if(bits[idx++] != 0)
        {
            printf("SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_ Extension size too large failure\n");
            return -1;
        }
        uint32_t packed_val = 0;
        for(uint32_t i=0; i<6; i++)
            packed_val |= bits[idx++] << (6-i-1);
        if((SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_Enum)packed_val > k_sib_TypeAndInfo_sib13_v920)
        {
            printf("SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_Unpack choice range failure\n");
            return -1;
        }
        sib_TypeAndInfo_internal_choice = (SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_Enum)(packed_val + k_sib_TypeAndInfo_sib12_v920);
    }else{
        uint32_t packed_val = 0;
        if((idx + 4) > bits.size())
        {
            printf("SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_Unpack() index out of bounds for choice\n");
            return -1;
        }
        for(uint32_t i=0; i<4; i++)
            packed_val |= bits[idx++] << (4-i-1);

        if((SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_Enum)packed_val > k_sib_TypeAndInfo_sib13_v920)
        {
            printf("SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_Unpack choice range failure\n");
            return -1;
        }
        sib_TypeAndInfo_internal_choice = (SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_Enum)packed_val;
    }
    sib_TypeAndInfo_present = true;

    // Fields
    if(sib_TypeAndInfo_internal_choice == k_sib_TypeAndInfo_sib2)
    {
        if(0 != sib_TypeAndInfo_sib2.Unpack(bits, idx))
        {
            printf("SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib2 unpack failure\n");
            return -1;
        }
    }
    if(sib_TypeAndInfo_internal_choice == k_sib_TypeAndInfo_sib3)
    {
        if(0 != sib_TypeAndInfo_sib3.Unpack(bits, idx))
        {
            printf("SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib3 unpack failure\n");
            return -1;
        }
    }
    if(sib_TypeAndInfo_internal_choice == k_sib_TypeAndInfo_sib4)
    {
        if(0 != sib_TypeAndInfo_sib4.Unpack(bits, idx))
        {
            printf("SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib4 unpack failure\n");
            return -1;
        }
    }
    if(sib_TypeAndInfo_internal_choice == k_sib_TypeAndInfo_sib5)
    {
        if(0 != sib_TypeAndInfo_sib5.Unpack(bits, idx))
        {
            printf("SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib5 unpack failure\n");
            return -1;
        }
    }
    if(sib_TypeAndInfo_internal_choice == k_sib_TypeAndInfo_sib6)
    {
        if(0 != sib_TypeAndInfo_sib6.Unpack(bits, idx))
        {
            printf("SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib6 unpack failure\n");
            return -1;
        }
    }
    if(sib_TypeAndInfo_internal_choice == k_sib_TypeAndInfo_sib7)
    {
        if(0 != sib_TypeAndInfo_sib7.Unpack(bits, idx))
        {
            printf("SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib7 unpack failure\n");
            return -1;
        }
    }
    if(sib_TypeAndInfo_internal_choice == k_sib_TypeAndInfo_sib8)
    {
        if(0 != sib_TypeAndInfo_sib8.Unpack(bits, idx))
        {
            printf("SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib8 unpack failure\n");
            return -1;
        }
    }
    if(sib_TypeAndInfo_internal_choice == k_sib_TypeAndInfo_sib9)
    {
        if(0 != sib_TypeAndInfo_sib9.Unpack(bits, idx))
        {
            printf("SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib9 unpack failure\n");
            return -1;
        }
    }
    if(sib_TypeAndInfo_internal_choice == k_sib_TypeAndInfo_sib10)
    {
        if(0 != sib_TypeAndInfo_sib10.Unpack(bits, idx))
        {
            printf("SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib10 unpack failure\n");
            return -1;
        }
    }
    if(sib_TypeAndInfo_internal_choice == k_sib_TypeAndInfo_sib11)
    {
        if(0 != sib_TypeAndInfo_sib11.Unpack(bits, idx))
        {
            printf("SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib11 unpack failure\n");
            return -1;
        }
    }

    // Extension
    if(is_extended)
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
        if((idx + (N_octets * 8)) > bits.size())
        {
            printf("SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_Unpack() index out of bounds for choice items\n");
            return -1;
        }
        if(sib_TypeAndInfo_internal_choice == k_sib_TypeAndInfo_sib12_v920)
        {
            if(0 != sib_TypeAndInfo_sib12_v920.Unpack(bits, idx))
            {
                printf("SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib12_v920 unpack failure\n");
                return -1;
            }
        }
        if(sib_TypeAndInfo_internal_choice == k_sib_TypeAndInfo_sib13_v920)
        {
            if(0 != sib_TypeAndInfo_sib13_v920.Unpack(bits, idx))
            {
                printf("SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib13_v920 unpack failure\n");
                return -1;
            }
        }
        idx = orig_idx + (N_octets * 8);
    }
    return 0;
}

SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_Enum SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_Choice() const
{
    if(sib_TypeAndInfo_present)
        return sib_TypeAndInfo_internal_choice;
    return (SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_Enum)0;
}

int SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_SetChoice(SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_Enum choice)
{
    sib_TypeAndInfo_internal_choice = choice;
    sib_TypeAndInfo_present = true;
    return 0;
}

std::string SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_ChoiceToString(sib_TypeAndInfo_Enum value) const
{
    if(k_sib_TypeAndInfo_sib2 == value)
        return "sib_TypeAndInfo_sib2";
    if(k_sib_TypeAndInfo_sib3 == value)
        return "sib_TypeAndInfo_sib3";
    if(k_sib_TypeAndInfo_sib4 == value)
        return "sib_TypeAndInfo_sib4";
    if(k_sib_TypeAndInfo_sib5 == value)
        return "sib_TypeAndInfo_sib5";
    if(k_sib_TypeAndInfo_sib6 == value)
        return "sib_TypeAndInfo_sib6";
    if(k_sib_TypeAndInfo_sib7 == value)
        return "sib_TypeAndInfo_sib7";
    if(k_sib_TypeAndInfo_sib8 == value)
        return "sib_TypeAndInfo_sib8";
    if(k_sib_TypeAndInfo_sib9 == value)
        return "sib_TypeAndInfo_sib9";
    if(k_sib_TypeAndInfo_sib10 == value)
        return "sib_TypeAndInfo_sib10";
    if(k_sib_TypeAndInfo_sib11 == value)
        return "sib_TypeAndInfo_sib11";
    if(k_sib_TypeAndInfo_sib12_v920 == value)
        return "sib_TypeAndInfo_sib12_v920";
    if(k_sib_TypeAndInfo_sib13_v920 == value)
        return "sib_TypeAndInfo_sib13_v920";
    return "";
}

uint64_t SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_NumberOfChoices() const
{
    return 12;
}

std::string SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "sib_TypeAndInfo = " + sib_TypeAndInfo_ChoiceToString(sib_TypeAndInfo_internal_choice) + ":\n";
    if(sib_TypeAndInfo_internal_choice == k_sib_TypeAndInfo_sib2)
        out += sib_TypeAndInfo_sib2.ToString(indent+1);
    if(sib_TypeAndInfo_internal_choice == k_sib_TypeAndInfo_sib3)
        out += sib_TypeAndInfo_sib3.ToString(indent+1);
    if(sib_TypeAndInfo_internal_choice == k_sib_TypeAndInfo_sib4)
        out += sib_TypeAndInfo_sib4.ToString(indent+1);
    if(sib_TypeAndInfo_internal_choice == k_sib_TypeAndInfo_sib5)
        out += sib_TypeAndInfo_sib5.ToString(indent+1);
    if(sib_TypeAndInfo_internal_choice == k_sib_TypeAndInfo_sib6)
        out += sib_TypeAndInfo_sib6.ToString(indent+1);
    if(sib_TypeAndInfo_internal_choice == k_sib_TypeAndInfo_sib7)
        out += sib_TypeAndInfo_sib7.ToString(indent+1);
    if(sib_TypeAndInfo_internal_choice == k_sib_TypeAndInfo_sib8)
        out += sib_TypeAndInfo_sib8.ToString(indent+1);
    if(sib_TypeAndInfo_internal_choice == k_sib_TypeAndInfo_sib9)
        out += sib_TypeAndInfo_sib9.ToString(indent+1);
    if(sib_TypeAndInfo_internal_choice == k_sib_TypeAndInfo_sib10)
        out += sib_TypeAndInfo_sib10.ToString(indent+1);
    if(sib_TypeAndInfo_internal_choice == k_sib_TypeAndInfo_sib11)
        out += sib_TypeAndInfo_sib11.ToString(indent+1);
    if(sib_TypeAndInfo_internal_choice == k_sib_TypeAndInfo_sib12_v920)
        out += sib_TypeAndInfo_sib12_v920.ToString(indent+1);
    if(sib_TypeAndInfo_internal_choice == k_sib_TypeAndInfo_sib13_v920)
        out += sib_TypeAndInfo_sib13_v920.ToString(indent+1);
    return out;
}

std::string SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_ToStringNoNewLines() const
{
    std::string out = "sib_TypeAndInfo=" + sib_TypeAndInfo_ChoiceToString(sib_TypeAndInfo_internal_choice) + ",";
    if(sib_TypeAndInfo_internal_choice == k_sib_TypeAndInfo_sib2)
        out += sib_TypeAndInfo_sib2.ToStringNoNewLines();
    if(sib_TypeAndInfo_internal_choice == k_sib_TypeAndInfo_sib3)
        out += sib_TypeAndInfo_sib3.ToStringNoNewLines();
    if(sib_TypeAndInfo_internal_choice == k_sib_TypeAndInfo_sib4)
        out += sib_TypeAndInfo_sib4.ToStringNoNewLines();
    if(sib_TypeAndInfo_internal_choice == k_sib_TypeAndInfo_sib5)
        out += sib_TypeAndInfo_sib5.ToStringNoNewLines();
    if(sib_TypeAndInfo_internal_choice == k_sib_TypeAndInfo_sib6)
        out += sib_TypeAndInfo_sib6.ToStringNoNewLines();
    if(sib_TypeAndInfo_internal_choice == k_sib_TypeAndInfo_sib7)
        out += sib_TypeAndInfo_sib7.ToStringNoNewLines();
    if(sib_TypeAndInfo_internal_choice == k_sib_TypeAndInfo_sib8)
        out += sib_TypeAndInfo_sib8.ToStringNoNewLines();
    if(sib_TypeAndInfo_internal_choice == k_sib_TypeAndInfo_sib9)
        out += sib_TypeAndInfo_sib9.ToStringNoNewLines();
    if(sib_TypeAndInfo_internal_choice == k_sib_TypeAndInfo_sib10)
        out += sib_TypeAndInfo_sib10.ToStringNoNewLines();
    if(sib_TypeAndInfo_internal_choice == k_sib_TypeAndInfo_sib11)
        out += sib_TypeAndInfo_sib11.ToStringNoNewLines();
    if(sib_TypeAndInfo_internal_choice == k_sib_TypeAndInfo_sib12_v920)
        out += sib_TypeAndInfo_sib12_v920.ToStringNoNewLines();
    if(sib_TypeAndInfo_internal_choice == k_sib_TypeAndInfo_sib13_v920)
        out += sib_TypeAndInfo_sib13_v920.ToStringNoNewLines();
    return out;
}

int SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_Clear()
{
    sib_TypeAndInfo_present = false;
    return 0;
}

bool SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_IsPresent() const
{
    return sib_TypeAndInfo_present;
}

SystemInformationBlockType2* SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib2_Set()
{
    sib_TypeAndInfo_sib2_present = true;
    return &sib_TypeAndInfo_sib2;
}

int SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib2_Set(SystemInformationBlockType2 &value)
{
    sib_TypeAndInfo_sib2_present = true;
    sib_TypeAndInfo_sib2 = value;
    return 0;
}

const SystemInformationBlockType2& SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib2_Get() const
{
    return sib_TypeAndInfo_sib2;
}

std::string SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib2_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "sib2:\n";
    out += sib_TypeAndInfo_sib2.ToString(indent+1);
    return out;
}

std::string SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib2_ToStringNoNewLines() const
{
    std::string out = "sib2:";
    out += sib_TypeAndInfo_sib2.ToStringNoNewLines();
    return out;
}

int SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib2_Clear()
{
    sib_TypeAndInfo_sib2_present = false;
    return 0;
}

bool SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib2_IsPresent() const
{
    return sib_TypeAndInfo_sib2_present;
}

SystemInformationBlockType3* SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib3_Set()
{
    sib_TypeAndInfo_sib3_present = true;
    return &sib_TypeAndInfo_sib3;
}

int SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib3_Set(SystemInformationBlockType3 &value)
{
    sib_TypeAndInfo_sib3_present = true;
    sib_TypeAndInfo_sib3 = value;
    return 0;
}

const SystemInformationBlockType3& SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib3_Get() const
{
    return sib_TypeAndInfo_sib3;
}

std::string SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib3_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "sib3:\n";
    out += sib_TypeAndInfo_sib3.ToString(indent+1);
    return out;
}

std::string SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib3_ToStringNoNewLines() const
{
    std::string out = "sib3:";
    out += sib_TypeAndInfo_sib3.ToStringNoNewLines();
    return out;
}

int SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib3_Clear()
{
    sib_TypeAndInfo_sib3_present = false;
    return 0;
}

bool SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib3_IsPresent() const
{
    return sib_TypeAndInfo_sib3_present;
}

SystemInformationBlockType4* SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib4_Set()
{
    sib_TypeAndInfo_sib4_present = true;
    return &sib_TypeAndInfo_sib4;
}

int SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib4_Set(SystemInformationBlockType4 &value)
{
    sib_TypeAndInfo_sib4_present = true;
    sib_TypeAndInfo_sib4 = value;
    return 0;
}

const SystemInformationBlockType4& SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib4_Get() const
{
    return sib_TypeAndInfo_sib4;
}

std::string SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib4_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "sib4:\n";
    out += sib_TypeAndInfo_sib4.ToString(indent+1);
    return out;
}

std::string SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib4_ToStringNoNewLines() const
{
    std::string out = "sib4:";
    out += sib_TypeAndInfo_sib4.ToStringNoNewLines();
    return out;
}

int SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib4_Clear()
{
    sib_TypeAndInfo_sib4_present = false;
    return 0;
}

bool SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib4_IsPresent() const
{
    return sib_TypeAndInfo_sib4_present;
}

SystemInformationBlockType5* SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib5_Set()
{
    sib_TypeAndInfo_sib5_present = true;
    return &sib_TypeAndInfo_sib5;
}

int SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib5_Set(SystemInformationBlockType5 &value)
{
    sib_TypeAndInfo_sib5_present = true;
    sib_TypeAndInfo_sib5 = value;
    return 0;
}

const SystemInformationBlockType5& SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib5_Get() const
{
    return sib_TypeAndInfo_sib5;
}

std::string SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib5_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "sib5:\n";
    out += sib_TypeAndInfo_sib5.ToString(indent+1);
    return out;
}

std::string SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib5_ToStringNoNewLines() const
{
    std::string out = "sib5:";
    out += sib_TypeAndInfo_sib5.ToStringNoNewLines();
    return out;
}

int SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib5_Clear()
{
    sib_TypeAndInfo_sib5_present = false;
    return 0;
}

bool SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib5_IsPresent() const
{
    return sib_TypeAndInfo_sib5_present;
}

SystemInformationBlockType6* SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib6_Set()
{
    sib_TypeAndInfo_sib6_present = true;
    return &sib_TypeAndInfo_sib6;
}

int SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib6_Set(SystemInformationBlockType6 &value)
{
    sib_TypeAndInfo_sib6_present = true;
    sib_TypeAndInfo_sib6 = value;
    return 0;
}

const SystemInformationBlockType6& SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib6_Get() const
{
    return sib_TypeAndInfo_sib6;
}

std::string SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib6_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "sib6:\n";
    out += sib_TypeAndInfo_sib6.ToString(indent+1);
    return out;
}

std::string SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib6_ToStringNoNewLines() const
{
    std::string out = "sib6:";
    out += sib_TypeAndInfo_sib6.ToStringNoNewLines();
    return out;
}

int SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib6_Clear()
{
    sib_TypeAndInfo_sib6_present = false;
    return 0;
}

bool SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib6_IsPresent() const
{
    return sib_TypeAndInfo_sib6_present;
}

SystemInformationBlockType7* SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib7_Set()
{
    sib_TypeAndInfo_sib7_present = true;
    return &sib_TypeAndInfo_sib7;
}

int SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib7_Set(SystemInformationBlockType7 &value)
{
    sib_TypeAndInfo_sib7_present = true;
    sib_TypeAndInfo_sib7 = value;
    return 0;
}

const SystemInformationBlockType7& SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib7_Get() const
{
    return sib_TypeAndInfo_sib7;
}

std::string SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib7_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "sib7:\n";
    out += sib_TypeAndInfo_sib7.ToString(indent+1);
    return out;
}

std::string SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib7_ToStringNoNewLines() const
{
    std::string out = "sib7:";
    out += sib_TypeAndInfo_sib7.ToStringNoNewLines();
    return out;
}

int SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib7_Clear()
{
    sib_TypeAndInfo_sib7_present = false;
    return 0;
}

bool SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib7_IsPresent() const
{
    return sib_TypeAndInfo_sib7_present;
}

SystemInformationBlockType8* SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib8_Set()
{
    sib_TypeAndInfo_sib8_present = true;
    return &sib_TypeAndInfo_sib8;
}

int SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib8_Set(SystemInformationBlockType8 &value)
{
    sib_TypeAndInfo_sib8_present = true;
    sib_TypeAndInfo_sib8 = value;
    return 0;
}

const SystemInformationBlockType8& SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib8_Get() const
{
    return sib_TypeAndInfo_sib8;
}

std::string SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib8_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "sib8:\n";
    out += sib_TypeAndInfo_sib8.ToString(indent+1);
    return out;
}

std::string SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib8_ToStringNoNewLines() const
{
    std::string out = "sib8:";
    out += sib_TypeAndInfo_sib8.ToStringNoNewLines();
    return out;
}

int SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib8_Clear()
{
    sib_TypeAndInfo_sib8_present = false;
    return 0;
}

bool SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib8_IsPresent() const
{
    return sib_TypeAndInfo_sib8_present;
}

SystemInformationBlockType9* SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib9_Set()
{
    sib_TypeAndInfo_sib9_present = true;
    return &sib_TypeAndInfo_sib9;
}

int SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib9_Set(SystemInformationBlockType9 &value)
{
    sib_TypeAndInfo_sib9_present = true;
    sib_TypeAndInfo_sib9 = value;
    return 0;
}

const SystemInformationBlockType9& SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib9_Get() const
{
    return sib_TypeAndInfo_sib9;
}

std::string SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "sib9:\n";
    out += sib_TypeAndInfo_sib9.ToString(indent+1);
    return out;
}

std::string SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib9_ToStringNoNewLines() const
{
    std::string out = "sib9:";
    out += sib_TypeAndInfo_sib9.ToStringNoNewLines();
    return out;
}

int SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib9_Clear()
{
    sib_TypeAndInfo_sib9_present = false;
    return 0;
}

bool SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib9_IsPresent() const
{
    return sib_TypeAndInfo_sib9_present;
}

SystemInformationBlockType10* SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib10_Set()
{
    sib_TypeAndInfo_sib10_present = true;
    return &sib_TypeAndInfo_sib10;
}

int SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib10_Set(SystemInformationBlockType10 &value)
{
    sib_TypeAndInfo_sib10_present = true;
    sib_TypeAndInfo_sib10 = value;
    return 0;
}

const SystemInformationBlockType10& SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib10_Get() const
{
    return sib_TypeAndInfo_sib10;
}

std::string SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "sib10:\n";
    out += sib_TypeAndInfo_sib10.ToString(indent+1);
    return out;
}

std::string SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib10_ToStringNoNewLines() const
{
    std::string out = "sib10:";
    out += sib_TypeAndInfo_sib10.ToStringNoNewLines();
    return out;
}

int SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib10_Clear()
{
    sib_TypeAndInfo_sib10_present = false;
    return 0;
}

bool SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib10_IsPresent() const
{
    return sib_TypeAndInfo_sib10_present;
}

SystemInformationBlockType11* SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib11_Set()
{
    sib_TypeAndInfo_sib11_present = true;
    return &sib_TypeAndInfo_sib11;
}

int SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib11_Set(SystemInformationBlockType11 &value)
{
    sib_TypeAndInfo_sib11_present = true;
    sib_TypeAndInfo_sib11 = value;
    return 0;
}

const SystemInformationBlockType11& SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib11_Get() const
{
    return sib_TypeAndInfo_sib11;
}

std::string SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib11_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "sib11:\n";
    out += sib_TypeAndInfo_sib11.ToString(indent+1);
    return out;
}

std::string SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib11_ToStringNoNewLines() const
{
    std::string out = "sib11:";
    out += sib_TypeAndInfo_sib11.ToStringNoNewLines();
    return out;
}

int SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib11_Clear()
{
    sib_TypeAndInfo_sib11_present = false;
    return 0;
}

bool SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib11_IsPresent() const
{
    return sib_TypeAndInfo_sib11_present;
}

SystemInformationBlockType12_r9* SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib12_v920_Set()
{
    sib_TypeAndInfo_sib12_v920_present = true;
    return &sib_TypeAndInfo_sib12_v920;
}

int SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib12_v920_Set(SystemInformationBlockType12_r9 &value)
{
    sib_TypeAndInfo_sib12_v920_present = true;
    sib_TypeAndInfo_sib12_v920 = value;
    return 0;
}

const SystemInformationBlockType12_r9& SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib12_v920_Get() const
{
    return sib_TypeAndInfo_sib12_v920;
}

std::string SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib12_v920_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "sib12_v920:\n";
    out += sib_TypeAndInfo_sib12_v920.ToString(indent+1);
    return out;
}

std::string SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib12_v920_ToStringNoNewLines() const
{
    std::string out = "sib12_v920:";
    out += sib_TypeAndInfo_sib12_v920.ToStringNoNewLines();
    return out;
}

int SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib12_v920_Clear()
{
    sib_TypeAndInfo_sib12_v920_present = false;
    return 0;
}

bool SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib12_v920_IsPresent() const
{
    return sib_TypeAndInfo_sib12_v920_present;
}

SystemInformationBlockType13_r9* SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib13_v920_Set()
{
    sib_TypeAndInfo_sib13_v920_present = true;
    return &sib_TypeAndInfo_sib13_v920;
}

int SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib13_v920_Set(SystemInformationBlockType13_r9 &value)
{
    sib_TypeAndInfo_sib13_v920_present = true;
    sib_TypeAndInfo_sib13_v920 = value;
    return 0;
}

const SystemInformationBlockType13_r9& SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib13_v920_Get() const
{
    return sib_TypeAndInfo_sib13_v920;
}

std::string SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib13_v920_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "sib13_v920:\n";
    out += sib_TypeAndInfo_sib13_v920.ToString(indent+1);
    return out;
}

std::string SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib13_v920_ToStringNoNewLines() const
{
    std::string out = "sib13_v920:";
    out += sib_TypeAndInfo_sib13_v920.ToStringNoNewLines();
    return out;
}

int SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib13_v920_Clear()
{
    sib_TypeAndInfo_sib13_v920_present = false;
    return 0;
}

bool SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_sib13_v920_IsPresent() const
{
    return sib_TypeAndInfo_sib13_v920_present;
}

#include "maxSIB.h"

int SystemInformation_r8_IEs::sib_TypeAndInfo_Pack(std::vector<uint8_t> &bits)
{
    if(!sib_TypeAndInfo_present)
    {
        printf("SystemInformation_r8_IEs::sib_TypeAndInfo_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_size_bits = 1;
    while(pow(2, N_size_bits) <= (maxSIB - 1))
        N_size_bits++;
    uint32_t local_size = sib_TypeAndInfo_internal_value.size() - 1;
    for(uint32_t i=0; i<N_size_bits; i++)
        bits.push_back((local_size >> (N_size_bits-i-1)) & 1);
    for(auto item : sib_TypeAndInfo_internal_value)
        if(0 != item.sib_TypeAndInfo_Pack(bits))
        {
            printf("SystemInformation_r8_IEs::sib_TypeAndInfo_Pack() item_pack_failure\n");
            return -1;
        }
    return 0;
}

int SystemInformation_r8_IEs::sib_TypeAndInfo_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return sib_TypeAndInfo_Unpack(bits, idx);
}

int SystemInformation_r8_IEs::sib_TypeAndInfo_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_size_bits = 1;
    while(pow(2, N_size_bits) <= (maxSIB - 1))
        N_size_bits++;
    uint32_t size = 0;
    for(uint32_t i=0; i<N_size_bits; i++)
        size |= bits[idx++] << (N_size_bits-i-1);
    size += 1;
    sib_TypeAndInfo_internal_value.clear();
    for(uint32_t i=0; i<size; i++)
    {
        sib_TypeAndInfo_ tmp;
        if(0 != tmp.sib_TypeAndInfo_Unpack(bits, idx))
        {
            printf("SystemInformation_r8_IEs::sib_TypeAndInfo_Unpack() item unpack failure\n");
            return -1;
        }
        sib_TypeAndInfo_internal_value.push_back(tmp);
    }
    sib_TypeAndInfo_present = true;
    return 0;
}

std::vector<SystemInformation_r8_IEs::sib_TypeAndInfo_> SystemInformation_r8_IEs::sib_TypeAndInfo_Value() const
{
    if(sib_TypeAndInfo_present)
        return sib_TypeAndInfo_internal_value;
    return {};
}

int SystemInformation_r8_IEs::sib_TypeAndInfo_SetValue(std::vector<SystemInformation_r8_IEs::sib_TypeAndInfo_> value)
{
    if(value.size() < 1 || value.size() > maxSIB)
    {
        printf("SystemInformation_r8_IEs::sib_TypeAndInfo_SetValue() list size failure\n");
        return -1;
    }
    sib_TypeAndInfo_internal_value = value;
    sib_TypeAndInfo_present = true;
    return 0;
}

std::string SystemInformation_r8_IEs::sib_TypeAndInfo_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "sib_TypeAndInfo:\n";
    for(auto item : sib_TypeAndInfo_internal_value)
        out += item.sib_TypeAndInfo_ToString(indent+1);
    return out;
}

std::string SystemInformation_r8_IEs::sib_TypeAndInfo_ToStringNoNewLines() const
{
    std::string out = "sib_TypeAndInfo:";
    for(auto item : sib_TypeAndInfo_internal_value)
        out += item.sib_TypeAndInfo_ToStringNoNewLines();
    return out;
}

SystemInformation_v8a0_IEs* SystemInformation_r8_IEs::nonCriticalExtension_Set()
{
    nonCriticalExtension_present = true;
    return &nonCriticalExtension;
}

int SystemInformation_r8_IEs::nonCriticalExtension_Set(SystemInformation_v8a0_IEs &value)
{
    nonCriticalExtension_present = true;
    nonCriticalExtension = value;
    return 0;
}

const SystemInformation_v8a0_IEs& SystemInformation_r8_IEs::nonCriticalExtension_Get() const
{
    return nonCriticalExtension;
}

std::string SystemInformation_r8_IEs::nonCriticalExtension_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "nonCriticalExtension:\n";
    out += nonCriticalExtension.ToString(indent+1);
    return out;
}

std::string SystemInformation_r8_IEs::nonCriticalExtension_ToStringNoNewLines() const
{
    std::string out = "nonCriticalExtension:";
    out += nonCriticalExtension.ToStringNoNewLines();
    return out;
}

int SystemInformation_r8_IEs::nonCriticalExtension_Clear()
{
    nonCriticalExtension_present = false;
    return 0;
}

bool SystemInformation_r8_IEs::nonCriticalExtension_IsPresent() const
{
    return nonCriticalExtension_present;
}

