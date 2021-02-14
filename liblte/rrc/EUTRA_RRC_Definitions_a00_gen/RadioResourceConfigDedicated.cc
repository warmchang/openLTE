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

#include "RadioResourceConfigDedicated.h"

#include <cmath>

int RadioResourceConfigDedicated::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator
    bool has_extension = false;
    if(rlf_TimersAndConstants_r9_IsPresent())
    {
        bits.push_back(1);
        has_extension = true;
    }else{
        bits.push_back(0);
    }

    // Optional indicators
    bits.push_back(srb_ToAddModList_IsPresent());
    bits.push_back(drb_ToAddModList_IsPresent());
    bits.push_back(drb_ToReleaseList_IsPresent());
    bits.push_back(mac_MainConfig_IsPresent());
    bits.push_back(sps_Config_IsPresent());
    bits.push_back(physicalConfigDedicated_IsPresent());

    // Fields
    if(srb_ToAddModList_IsPresent())
    {
        if(0 != srb_ToAddModList.Pack(bits))
        {
            printf("RadioResourceConfigDedicated:: field pack failure\n");
            return -1;
        }
    }
    if(drb_ToAddModList_IsPresent())
    {
        if(0 != drb_ToAddModList.Pack(bits))
        {
            printf("RadioResourceConfigDedicated:: field pack failure\n");
            return -1;
        }
    }
    if(drb_ToReleaseList_IsPresent())
    {
        if(0 != drb_ToReleaseList.Pack(bits))
        {
            printf("RadioResourceConfigDedicated:: field pack failure\n");
            return -1;
        }
    }
    if(mac_MainConfig_IsPresent())
    {
        if(0 != mac_MainConfig_Pack(bits))
        {
            printf("RadioResourceConfigDedicated:: field pack failure\n");
            return -1;
        }
    }
    if(sps_Config_IsPresent())
    {
        if(0 != sps_Config.Pack(bits))
        {
            printf("RadioResourceConfigDedicated:: field pack failure\n");
            return -1;
        }
    }
    if(physicalConfigDedicated_IsPresent())
    {
        if(0 != physicalConfigDedicated.Pack(bits))
        {
            printf("RadioResourceConfigDedicated:: field pack failure\n");
            return -1;
        }
    }

    // Extension
    if(has_extension)
    {
        // Number of extension fields
        if(0 < 64)
        {
            bits.push_back(0);
            for(uint32_t i=0; i<6; i++)
                bits.push_back((0 >> (6-i-1)) & 1);
        }else{
            printf("RadioResourceConfigDedicated:: Extension list size too large failure\n");
            return -1;
        }

        // Extension field presence indicators
        bits.push_back(rlf_TimersAndConstants_r9_IsPresent());

        // Extension fields
        if(rlf_TimersAndConstants_r9_IsPresent())
        {
            std::vector<uint8_t> field_bits;
            if(0 != rlf_TimersAndConstants_r9.Pack(field_bits))
            {
                printf("RadioResourceConfigDedicated:: field pack failure\n");
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

int RadioResourceConfigDedicated::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int RadioResourceConfigDedicated::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("RadioResourceConfigDedicated::Unpack() index out of bounds for extension\n");
        return -1;
    }
    bool has_extension = bits[idx++];

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("RadioResourceConfigDedicated::Unpack() index out of bounds for optional indiator srb_ToAddModList\n");
        return -1;
    }
    srb_ToAddModList_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("RadioResourceConfigDedicated::Unpack() index out of bounds for optional indiator drb_ToAddModList\n");
        return -1;
    }
    drb_ToAddModList_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("RadioResourceConfigDedicated::Unpack() index out of bounds for optional indiator drb_ToReleaseList\n");
        return -1;
    }
    drb_ToReleaseList_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("RadioResourceConfigDedicated::Unpack() index out of bounds for optional indiator mac_MainConfig\n");
        return -1;
    }
    mac_MainConfig_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("RadioResourceConfigDedicated::Unpack() index out of bounds for optional indiator sps_Config\n");
        return -1;
    }
    sps_Config_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("RadioResourceConfigDedicated::Unpack() index out of bounds for optional indiator physicalConfigDedicated\n");
        return -1;
    }
    physicalConfigDedicated_present = bits[idx++];

    // Fields
    if(srb_ToAddModList_present)
    {
        if(0 != srb_ToAddModList.Unpack(bits, idx))
        {
            printf("RadioResourceConfigDedicated:: field unpack failure\n");
            return -1;
        }
    }
    if(drb_ToAddModList_present)
    {
        if(0 != drb_ToAddModList.Unpack(bits, idx))
        {
            printf("RadioResourceConfigDedicated:: field unpack failure\n");
            return -1;
        }
    }
    if(drb_ToReleaseList_present)
    {
        if(0 != drb_ToReleaseList.Unpack(bits, idx))
        {
            printf("RadioResourceConfigDedicated:: field unpack failure\n");
            return -1;
        }
    }
    if(mac_MainConfig_present)
    {
        if(0 != mac_MainConfig_Unpack(bits, idx))
        {
            printf("RadioResourceConfigDedicated:: field unpack failure\n");
            return -1;
        }
    }
    if(sps_Config_present)
    {
        if(0 != sps_Config.Unpack(bits, idx))
        {
            printf("RadioResourceConfigDedicated:: field unpack failure\n");
            return -1;
        }
    }
    if(physicalConfigDedicated_present)
    {
        if(0 != physicalConfigDedicated.Unpack(bits, idx))
        {
            printf("RadioResourceConfigDedicated:: field unpack failure\n");
            return -1;
        }
    }

    // Extension
    if(has_extension)
    {
        if((idx + 7) > bits.size())
        {
            printf("RadioResourceConfigDedicated::Unpack() index out of bounds for extension size\n");
            return -1;
        }
        // Number of extension fields
        if(bits[idx++] != 0)
        {
            printf("RadioResourceConfigDedicated:: Extension list size too large failure\n");
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
                printf("RadioResourceConfigDedicated::Unpack() index out of bounds for optional indiator rlf_TimersAndConstants_r9\n");
                return -1;
            }
            rlf_TimersAndConstants_r9_present = bits[idx++];
        }
        if((idx + (N_ext_fields - opt_ind_count)) > bits.size())
        {
            printf("RadioResourceConfigDedicated::Unpack() index out of bounds for extension optional indicators\n");
            return -1;
        }
        idx += (N_ext_fields - opt_ind_count);

        // Extension fields
        if(rlf_TimersAndConstants_r9_present)
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
            if(0 != rlf_TimersAndConstants_r9.Unpack(bits, idx))
            {
                printf("RadioResourceConfigDedicated:: field unpack failure\n");
                return -1;
            }
            idx = orig_idx + (N_octets * 8);
        }
        for(uint32_t i=1; i<N_ext_fields; i++)
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
            printf("RadioResourceConfigDedicated::Unpack() index out of bounds for extension fields\n");
            return -1;
        }
            idx += N_octets * 8;
        }
    }
    return 0;
}

std::string RadioResourceConfigDedicated::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "RadioResourceConfigDedicated:\n";
    if(srb_ToAddModList_IsPresent())
        out += srb_ToAddModList_ToString(indent+1);
    if(drb_ToAddModList_IsPresent())
        out += drb_ToAddModList_ToString(indent+1);
    if(drb_ToReleaseList_IsPresent())
        out += drb_ToReleaseList_ToString(indent+1);
    if(mac_MainConfig_IsPresent())
        out += mac_MainConfig_ToString(indent+1);
    if(sps_Config_IsPresent())
        out += sps_Config_ToString(indent+1);
    if(physicalConfigDedicated_IsPresent())
        out += physicalConfigDedicated_ToString(indent+1);
    if(rlf_TimersAndConstants_r9_IsPresent())
        out += rlf_TimersAndConstants_r9_ToString(indent+1);
    return out;
}

std::string RadioResourceConfigDedicated::ToStringNoNewLines() const
{
    std::string out = "RadioResourceConfigDedicated:";
    if(srb_ToAddModList_IsPresent())
        out += srb_ToAddModList_ToStringNoNewLines();
    if(drb_ToAddModList_IsPresent())
        out += drb_ToAddModList_ToStringNoNewLines();
    if(drb_ToReleaseList_IsPresent())
        out += drb_ToReleaseList_ToStringNoNewLines();
    if(mac_MainConfig_IsPresent())
        out += mac_MainConfig_ToStringNoNewLines();
    if(sps_Config_IsPresent())
        out += sps_Config_ToStringNoNewLines();
    if(physicalConfigDedicated_IsPresent())
        out += physicalConfigDedicated_ToStringNoNewLines();
    if(rlf_TimersAndConstants_r9_IsPresent())
        out += rlf_TimersAndConstants_r9_ToStringNoNewLines();
    return out;
}

SRB_ToAddModList* RadioResourceConfigDedicated::srb_ToAddModList_Set()
{
    srb_ToAddModList_present = true;
    return &srb_ToAddModList;
}

int RadioResourceConfigDedicated::srb_ToAddModList_Set(SRB_ToAddModList &value)
{
    srb_ToAddModList_present = true;
    srb_ToAddModList = value;
    return 0;
}

const SRB_ToAddModList& RadioResourceConfigDedicated::srb_ToAddModList_Get() const
{
    return srb_ToAddModList;
}

std::string RadioResourceConfigDedicated::srb_ToAddModList_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "srb_ToAddModList:\n";
    out += srb_ToAddModList.ToString(indent+1);
    return out;
}

std::string RadioResourceConfigDedicated::srb_ToAddModList_ToStringNoNewLines() const
{
    std::string out = "srb_ToAddModList:";
    out += srb_ToAddModList.ToStringNoNewLines();
    return out;
}

int RadioResourceConfigDedicated::srb_ToAddModList_Clear()
{
    srb_ToAddModList_present = false;
    return 0;
}

bool RadioResourceConfigDedicated::srb_ToAddModList_IsPresent() const
{
    return srb_ToAddModList_present;
}

DRB_ToAddModList* RadioResourceConfigDedicated::drb_ToAddModList_Set()
{
    drb_ToAddModList_present = true;
    return &drb_ToAddModList;
}

int RadioResourceConfigDedicated::drb_ToAddModList_Set(DRB_ToAddModList &value)
{
    drb_ToAddModList_present = true;
    drb_ToAddModList = value;
    return 0;
}

const DRB_ToAddModList& RadioResourceConfigDedicated::drb_ToAddModList_Get() const
{
    return drb_ToAddModList;
}

std::string RadioResourceConfigDedicated::drb_ToAddModList_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "drb_ToAddModList:\n";
    out += drb_ToAddModList.ToString(indent+1);
    return out;
}

std::string RadioResourceConfigDedicated::drb_ToAddModList_ToStringNoNewLines() const
{
    std::string out = "drb_ToAddModList:";
    out += drb_ToAddModList.ToStringNoNewLines();
    return out;
}

int RadioResourceConfigDedicated::drb_ToAddModList_Clear()
{
    drb_ToAddModList_present = false;
    return 0;
}

bool RadioResourceConfigDedicated::drb_ToAddModList_IsPresent() const
{
    return drb_ToAddModList_present;
}

DRB_ToReleaseList* RadioResourceConfigDedicated::drb_ToReleaseList_Set()
{
    drb_ToReleaseList_present = true;
    return &drb_ToReleaseList;
}

int RadioResourceConfigDedicated::drb_ToReleaseList_Set(DRB_ToReleaseList &value)
{
    drb_ToReleaseList_present = true;
    drb_ToReleaseList = value;
    return 0;
}

const DRB_ToReleaseList& RadioResourceConfigDedicated::drb_ToReleaseList_Get() const
{
    return drb_ToReleaseList;
}

std::string RadioResourceConfigDedicated::drb_ToReleaseList_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "drb_ToReleaseList:\n";
    out += drb_ToReleaseList.ToString(indent+1);
    return out;
}

std::string RadioResourceConfigDedicated::drb_ToReleaseList_ToStringNoNewLines() const
{
    std::string out = "drb_ToReleaseList:";
    out += drb_ToReleaseList.ToStringNoNewLines();
    return out;
}

int RadioResourceConfigDedicated::drb_ToReleaseList_Clear()
{
    drb_ToReleaseList_present = false;
    return 0;
}

bool RadioResourceConfigDedicated::drb_ToReleaseList_IsPresent() const
{
    return drb_ToReleaseList_present;
}

int RadioResourceConfigDedicated::mac_MainConfig_Pack(std::vector<uint8_t> &bits)
{
    if(!mac_MainConfig_present)
    {
        printf("RadioResourceConfigDedicated::mac_MainConfig_Pack() presence failure\n");
        return -1;
    }
    // Extension indicator

    // Choice
    for(uint32_t i=0; i<1; i++)
        bits.push_back((mac_MainConfig_internal_choice >> (1-i-1)) & 1);

    // Fields
    if(mac_MainConfig_internal_choice == k_mac_MainConfig_explicitValue)
    {
        if(0 != mac_MainConfig_explicitValue.Pack(bits))
        {
            printf("RadioResourceConfigDedicated::mac_MainConfig_explicitValue pack failure\n");
            return -1;
        }
    }
    if(mac_MainConfig_internal_choice == k_mac_MainConfig_defaultValue)
    {
        if(0 != mac_MainConfig_defaultValue_Pack(bits))
        {
            printf("RadioResourceConfigDedicated::mac_MainConfig_defaultValue pack failure\n");
            return -1;
        }
    }
    return 0;
}

int RadioResourceConfigDedicated::mac_MainConfig_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return mac_MainConfig_Unpack(bits, idx);
}

int RadioResourceConfigDedicated::mac_MainConfig_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 1) > bits.size())
    {
        printf("RadioResourceConfigDedicated::mac_MainConfig_Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<1; i++)
        packed_val |= bits[idx++] << (1-i-1);

    if((RadioResourceConfigDedicated::mac_MainConfig_Enum)packed_val > k_mac_MainConfig_defaultValue)
    {
        printf("RadioResourceConfigDedicated::mac_MainConfig_Unpack() choice range failure\n");
        return -1;
    }
    mac_MainConfig_internal_choice = (RadioResourceConfigDedicated::mac_MainConfig_Enum)packed_val;
    mac_MainConfig_present = true;

    // Fields
    if(mac_MainConfig_internal_choice == k_mac_MainConfig_explicitValue)
    {
        if(0 != mac_MainConfig_explicitValue.Unpack(bits, idx))
        {
            printf("RadioResourceConfigDedicated::mac_MainConfig_explicitValue unpack failure\n");
            return -1;
        }
    }
    if(mac_MainConfig_internal_choice == k_mac_MainConfig_defaultValue)
    {
        if(0 != mac_MainConfig_defaultValue_Unpack(bits, idx))
        {
            printf("RadioResourceConfigDedicated::mac_MainConfig_defaultValue unpack failure\n");
            return -1;
        }
    }
    return 0;
}

RadioResourceConfigDedicated::mac_MainConfig_Enum RadioResourceConfigDedicated::mac_MainConfig_Choice() const
{
    if(mac_MainConfig_present)
        return mac_MainConfig_internal_choice;
    return (RadioResourceConfigDedicated::mac_MainConfig_Enum)0;
}

int RadioResourceConfigDedicated::mac_MainConfig_SetChoice(RadioResourceConfigDedicated::mac_MainConfig_Enum choice)
{
    mac_MainConfig_internal_choice = choice;
    mac_MainConfig_present = true;
    return 0;
}

std::string RadioResourceConfigDedicated::mac_MainConfig_ChoiceToString(mac_MainConfig_Enum value) const
{
    if(k_mac_MainConfig_explicitValue == value)
        return "mac_MainConfig_explicitValue";
    if(k_mac_MainConfig_defaultValue == value)
        return "mac_MainConfig_defaultValue";
    return "";
}

uint64_t RadioResourceConfigDedicated::mac_MainConfig_NumberOfChoices() const
{
    return 2;
}

std::string RadioResourceConfigDedicated::mac_MainConfig_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "mac_MainConfig = " + mac_MainConfig_ChoiceToString(mac_MainConfig_internal_choice) + ":\n";
    if(mac_MainConfig_internal_choice == k_mac_MainConfig_explicitValue)
        out += mac_MainConfig_explicitValue.ToString(indent+1);
    return out;
}

std::string RadioResourceConfigDedicated::mac_MainConfig_ToStringNoNewLines() const
{
    std::string out = "mac_MainConfig=" + mac_MainConfig_ChoiceToString(mac_MainConfig_internal_choice) + ",";
    if(mac_MainConfig_internal_choice == k_mac_MainConfig_explicitValue)
        out += mac_MainConfig_explicitValue.ToStringNoNewLines();
    return out;
}

int RadioResourceConfigDedicated::mac_MainConfig_Clear()
{
    mac_MainConfig_present = false;
    return 0;
}

bool RadioResourceConfigDedicated::mac_MainConfig_IsPresent() const
{
    return mac_MainConfig_present;
}

MAC_MainConfig* RadioResourceConfigDedicated::mac_MainConfig_explicitValue_Set()
{
    mac_MainConfig_explicitValue_present = true;
    return &mac_MainConfig_explicitValue;
}

int RadioResourceConfigDedicated::mac_MainConfig_explicitValue_Set(MAC_MainConfig &value)
{
    mac_MainConfig_explicitValue_present = true;
    mac_MainConfig_explicitValue = value;
    return 0;
}

const MAC_MainConfig& RadioResourceConfigDedicated::mac_MainConfig_explicitValue_Get() const
{
    return mac_MainConfig_explicitValue;
}

std::string RadioResourceConfigDedicated::mac_MainConfig_explicitValue_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "explicitValue:\n";
    out += mac_MainConfig_explicitValue.ToString(indent+1);
    return out;
}

std::string RadioResourceConfigDedicated::mac_MainConfig_explicitValue_ToStringNoNewLines() const
{
    std::string out = "explicitValue:";
    out += mac_MainConfig_explicitValue.ToStringNoNewLines();
    return out;
}

int RadioResourceConfigDedicated::mac_MainConfig_explicitValue_Clear()
{
    mac_MainConfig_explicitValue_present = false;
    return 0;
}

bool RadioResourceConfigDedicated::mac_MainConfig_explicitValue_IsPresent() const
{
    return mac_MainConfig_explicitValue_present;
}

SPS_Config* RadioResourceConfigDedicated::sps_Config_Set()
{
    sps_Config_present = true;
    return &sps_Config;
}

int RadioResourceConfigDedicated::sps_Config_Set(SPS_Config &value)
{
    sps_Config_present = true;
    sps_Config = value;
    return 0;
}

const SPS_Config& RadioResourceConfigDedicated::sps_Config_Get() const
{
    return sps_Config;
}

std::string RadioResourceConfigDedicated::sps_Config_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "sps_Config:\n";
    out += sps_Config.ToString(indent+1);
    return out;
}

std::string RadioResourceConfigDedicated::sps_Config_ToStringNoNewLines() const
{
    std::string out = "sps_Config:";
    out += sps_Config.ToStringNoNewLines();
    return out;
}

int RadioResourceConfigDedicated::sps_Config_Clear()
{
    sps_Config_present = false;
    return 0;
}

bool RadioResourceConfigDedicated::sps_Config_IsPresent() const
{
    return sps_Config_present;
}

PhysicalConfigDedicated* RadioResourceConfigDedicated::physicalConfigDedicated_Set()
{
    physicalConfigDedicated_present = true;
    return &physicalConfigDedicated;
}

int RadioResourceConfigDedicated::physicalConfigDedicated_Set(PhysicalConfigDedicated &value)
{
    physicalConfigDedicated_present = true;
    physicalConfigDedicated = value;
    return 0;
}

const PhysicalConfigDedicated& RadioResourceConfigDedicated::physicalConfigDedicated_Get() const
{
    return physicalConfigDedicated;
}

std::string RadioResourceConfigDedicated::physicalConfigDedicated_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "physicalConfigDedicated:\n";
    out += physicalConfigDedicated.ToString(indent+1);
    return out;
}

std::string RadioResourceConfigDedicated::physicalConfigDedicated_ToStringNoNewLines() const
{
    std::string out = "physicalConfigDedicated:";
    out += physicalConfigDedicated.ToStringNoNewLines();
    return out;
}

int RadioResourceConfigDedicated::physicalConfigDedicated_Clear()
{
    physicalConfigDedicated_present = false;
    return 0;
}

bool RadioResourceConfigDedicated::physicalConfigDedicated_IsPresent() const
{
    return physicalConfigDedicated_present;
}

RLF_TimersAndConstants_r9* RadioResourceConfigDedicated::rlf_TimersAndConstants_r9_Set()
{
    rlf_TimersAndConstants_r9_present = true;
    return &rlf_TimersAndConstants_r9;
}

int RadioResourceConfigDedicated::rlf_TimersAndConstants_r9_Set(RLF_TimersAndConstants_r9 &value)
{
    rlf_TimersAndConstants_r9_present = true;
    rlf_TimersAndConstants_r9 = value;
    return 0;
}

const RLF_TimersAndConstants_r9& RadioResourceConfigDedicated::rlf_TimersAndConstants_r9_Get() const
{
    return rlf_TimersAndConstants_r9;
}

std::string RadioResourceConfigDedicated::rlf_TimersAndConstants_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "rlf_TimersAndConstants_r9:\n";
    out += rlf_TimersAndConstants_r9.ToString(indent+1);
    return out;
}

std::string RadioResourceConfigDedicated::rlf_TimersAndConstants_r9_ToStringNoNewLines() const
{
    std::string out = "rlf_TimersAndConstants_r9:";
    out += rlf_TimersAndConstants_r9.ToStringNoNewLines();
    return out;
}

int RadioResourceConfigDedicated::rlf_TimersAndConstants_r9_Clear()
{
    rlf_TimersAndConstants_r9_present = false;
    return 0;
}

bool RadioResourceConfigDedicated::rlf_TimersAndConstants_r9_IsPresent() const
{
    return rlf_TimersAndConstants_r9_present;
}

