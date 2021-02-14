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

#include "MAC_MainConfig.h"

#include <cmath>

int MAC_MainConfig::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator
    bool has_extension = false;
    if(sr_ProhibitTimer_r9_IsPresent() || sCellDeactivationTimer_r10_IsPresent() || extendedBSR_Sizes_r10_IsPresent() || extendedPHR_r10_IsPresent())
    {
        bits.push_back(1);
        has_extension = true;
    }else{
        bits.push_back(0);
    }

    // Optional indicators
    bits.push_back(ul_SCH_Config_value.IsPresent());
    bits.push_back(drx_Config_IsPresent());
    bits.push_back(phr_Config_IsPresent());

    // Fields
    if(ul_SCH_Config_value.IsPresent())
    {
        if(0 != ul_SCH_Config_value.Pack(bits))
        {
            printf("MAC_MainConfig:: field pack failure\n");
            return -1;
        }
    }
    if(drx_Config_IsPresent())
    {
        if(0 != drx_Config.Pack(bits))
        {
            printf("MAC_MainConfig:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != timeAlignmentTimerDedicated.Pack(bits))
        {
            printf("MAC_MainConfig:: field pack failure\n");
            return -1;
        }
    }
    if(phr_Config_IsPresent())
    {
        if(0 != phr_Config_Pack(bits))
        {
            printf("MAC_MainConfig:: field pack failure\n");
            return -1;
        }
    }

    // Extension
    if(has_extension)
    {
        // Number of extension fields
        if(3 < 64)
        {
            bits.push_back(0);
            for(uint32_t i=0; i<6; i++)
                bits.push_back((3 >> (6-i-1)) & 1);
        }else{
            printf("MAC_MainConfig:: Extension list size too large failure\n");
            return -1;
        }

        // Extension field presence indicators
        bits.push_back(sr_ProhibitTimer_r9_IsPresent());
        bits.push_back(sCellDeactivationTimer_r10_IsPresent());
        bits.push_back(extendedBSR_Sizes_r10_IsPresent());
        bits.push_back(extendedPHR_r10_IsPresent());

        // Extension fields
        if(sr_ProhibitTimer_r9_IsPresent())
        {
            std::vector<uint8_t> field_bits;
            if(0 != sr_ProhibitTimer_r9_Pack(field_bits))
            {
                printf("MAC_MainConfig:: field pack failure\n");
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
        if(sCellDeactivationTimer_r10_IsPresent())
        {
            std::vector<uint8_t> field_bits;
            if(0 != sCellDeactivationTimer_r10_Pack(field_bits))
            {
                printf("MAC_MainConfig:: field pack failure\n");
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
        if(extendedBSR_Sizes_r10_IsPresent())
        {
            std::vector<uint8_t> field_bits;
            if(0 != extendedBSR_Sizes_r10_Pack(field_bits))
            {
                printf("MAC_MainConfig:: field pack failure\n");
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
        if(extendedPHR_r10_IsPresent())
        {
            std::vector<uint8_t> field_bits;
            if(0 != extendedPHR_r10_Pack(field_bits))
            {
                printf("MAC_MainConfig:: field pack failure\n");
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

int MAC_MainConfig::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int MAC_MainConfig::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("MAC_MainConfig::Unpack() index out of bounds for extension\n");
        return -1;
    }
    bool has_extension = bits[idx++];

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("MAC_MainConfig::Unpack() index out of bounds for optional indiator ul_SCH_Config\n");
        return -1;
    }
    ul_SCH_Config_value.SetPresence(bits[idx++]);
    if((idx + 1) > bits.size())
    {
        printf("MAC_MainConfig::Unpack() index out of bounds for optional indiator drx_Config\n");
        return -1;
    }
    drx_Config_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("MAC_MainConfig::Unpack() index out of bounds for optional indiator phr_Config\n");
        return -1;
    }
    phr_Config_present = bits[idx++];

    // Fields
    if(ul_SCH_Config_value.IsPresent())
    {
        if(0 != ul_SCH_Config_value.Unpack(bits, idx))
        {
            printf("MAC_MainConfig:: field unpack failure\n");
            return -1;
        }
    }
    if(drx_Config_present)
    {
        if(0 != drx_Config.Unpack(bits, idx))
        {
            printf("MAC_MainConfig:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != timeAlignmentTimerDedicated.Unpack(bits, idx))
        {
            printf("MAC_MainConfig:: field unpack failure\n");
            return -1;
        }
    }
    if(phr_Config_present)
    {
        if(0 != phr_Config_Unpack(bits, idx))
        {
            printf("MAC_MainConfig:: field unpack failure\n");
            return -1;
        }
    }

    // Extension
    if(has_extension)
    {
        if((idx + 7) > bits.size())
        {
            printf("MAC_MainConfig::Unpack() index out of bounds for extension size\n");
            return -1;
        }
        // Number of extension fields
        if(bits[idx++] != 0)
        {
            printf("MAC_MainConfig:: Extension list size too large failure\n");
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
                printf("MAC_MainConfig::Unpack() index out of bounds for optional indiator sr_ProhibitTimer_r9\n");
                return -1;
            }
            sr_ProhibitTimer_r9_present = bits[idx++];
        }
        if(opt_ind_count++ < N_ext_fields)
        {
            if((idx + 1) > bits.size())
            {
                printf("MAC_MainConfig::Unpack() index out of bounds for optional indiator sCellDeactivationTimer_r10\n");
                return -1;
            }
            sCellDeactivationTimer_r10_present = bits[idx++];
        }
        if(opt_ind_count++ < N_ext_fields)
        {
            if((idx + 1) > bits.size())
            {
                printf("MAC_MainConfig::Unpack() index out of bounds for optional indiator extendedBSR_Sizes_r10\n");
                return -1;
            }
            extendedBSR_Sizes_r10_present = bits[idx++];
        }
        if(opt_ind_count++ < N_ext_fields)
        {
            if((idx + 1) > bits.size())
            {
                printf("MAC_MainConfig::Unpack() index out of bounds for optional indiator extendedPHR_r10\n");
                return -1;
            }
            extendedPHR_r10_present = bits[idx++];
        }
        if((idx + (N_ext_fields - opt_ind_count)) > bits.size())
        {
            printf("MAC_MainConfig::Unpack() index out of bounds for extension optional indicators\n");
            return -1;
        }
        idx += (N_ext_fields - opt_ind_count);

        // Extension fields
        if(sr_ProhibitTimer_r9_present)
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
            if(0 != sr_ProhibitTimer_r9_Unpack(bits, idx))
            {
                printf("MAC_MainConfig:: field unpack failure\n");
                return -1;
            }
            idx = orig_idx + (N_octets * 8);
        }
        if(sCellDeactivationTimer_r10_present)
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
            if(0 != sCellDeactivationTimer_r10_Unpack(bits, idx))
            {
                printf("MAC_MainConfig:: field unpack failure\n");
                return -1;
            }
            idx = orig_idx + (N_octets * 8);
        }
        if(extendedBSR_Sizes_r10_present)
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
            if(0 != extendedBSR_Sizes_r10_Unpack(bits, idx))
            {
                printf("MAC_MainConfig:: field unpack failure\n");
                return -1;
            }
            idx = orig_idx + (N_octets * 8);
        }
        if(extendedPHR_r10_present)
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
            if(0 != extendedPHR_r10_Unpack(bits, idx))
            {
                printf("MAC_MainConfig:: field unpack failure\n");
                return -1;
            }
            idx = orig_idx + (N_octets * 8);
        }
        for(uint32_t i=4; i<N_ext_fields; i++)
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
            printf("MAC_MainConfig::Unpack() index out of bounds for extension fields\n");
            return -1;
        }
            idx += N_octets * 8;
        }
    }
    return 0;
}

std::string MAC_MainConfig::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "MAC_MainConfig:\n";
    if(ul_SCH_Config_value.IsPresent())
        out += ul_SCH_Config_value.ToString(indent+1);
    if(drx_Config_IsPresent())
        out += drx_Config_ToString(indent+1);
    out += timeAlignmentTimerDedicated_ToString(indent+1);
    if(phr_Config_IsPresent())
        out += phr_Config_ToString(indent+1);
    if(sr_ProhibitTimer_r9_IsPresent())
        out += sr_ProhibitTimer_r9_ToString(indent+1);
    if(sCellDeactivationTimer_r10_IsPresent())
        out += sCellDeactivationTimer_r10_ToString(indent+1);
    if(extendedBSR_Sizes_r10_IsPresent())
        out += extendedBSR_Sizes_r10_ToString(indent+1);
    if(extendedPHR_r10_IsPresent())
        out += extendedPHR_r10_ToString(indent+1);
    return out;
}

std::string MAC_MainConfig::ToStringNoNewLines() const
{
    std::string out = "MAC_MainConfig:";
    if(ul_SCH_Config_value.IsPresent())
        out += ul_SCH_Config_value.ToStringNoNewLines();
    if(drx_Config_IsPresent())
        out += drx_Config_ToStringNoNewLines();
    out += timeAlignmentTimerDedicated_ToStringNoNewLines();
    if(phr_Config_IsPresent())
        out += phr_Config_ToStringNoNewLines();
    if(sr_ProhibitTimer_r9_IsPresent())
        out += sr_ProhibitTimer_r9_ToStringNoNewLines();
    if(sCellDeactivationTimer_r10_IsPresent())
        out += sCellDeactivationTimer_r10_ToStringNoNewLines();
    if(extendedBSR_Sizes_r10_IsPresent())
        out += extendedBSR_Sizes_r10_ToStringNoNewLines();
    if(extendedPHR_r10_IsPresent())
        out += extendedPHR_r10_ToStringNoNewLines();
    return out;
}

int MAC_MainConfig::ul_SCH_Config::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(maxHARQ_Tx_IsPresent());
    bits.push_back(periodicBSR_Timer_IsPresent());

    // Fields
    if(maxHARQ_Tx_IsPresent())
    {
        if(0 != maxHARQ_Tx_Pack(bits))
        {
            printf("MAC_MainConfig::ul_SCH_Config:: field pack failure\n");
            return -1;
        }
    }
    if(periodicBSR_Timer_IsPresent())
    {
        if(0 != periodicBSR_Timer_Pack(bits))
        {
            printf("MAC_MainConfig::ul_SCH_Config:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != retxBSR_Timer_Pack(bits))
        {
            printf("MAC_MainConfig::ul_SCH_Config:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != ttiBundling_Pack(bits))
        {
            printf("MAC_MainConfig::ul_SCH_Config:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int MAC_MainConfig::ul_SCH_Config::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int MAC_MainConfig::ul_SCH_Config::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("ul_SCH_Config::Unpack() index out of bounds for optional indiator maxHARQ_Tx\n");
        return -1;
    }
    maxHARQ_Tx_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("ul_SCH_Config::Unpack() index out of bounds for optional indiator periodicBSR_Timer\n");
        return -1;
    }
    periodicBSR_Timer_present = bits[idx++];

    // Fields
    if(maxHARQ_Tx_present)
    {
        if(0 != maxHARQ_Tx_Unpack(bits, idx))
        {
            printf("MAC_MainConfig::ul_SCH_Config:: field unpack failure\n");
            return -1;
        }
    }
    if(periodicBSR_Timer_present)
    {
        if(0 != periodicBSR_Timer_Unpack(bits, idx))
        {
            printf("MAC_MainConfig::ul_SCH_Config:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != retxBSR_Timer_Unpack(bits, idx))
        {
            printf("MAC_MainConfig::ul_SCH_Config:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != ttiBundling_Unpack(bits, idx))
        {
            printf("MAC_MainConfig::ul_SCH_Config:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string MAC_MainConfig::ul_SCH_Config::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ul_SCH_Config:\n";
    if(maxHARQ_Tx_IsPresent())
        out += maxHARQ_Tx_ToString(indent+1);
    if(periodicBSR_Timer_IsPresent())
        out += periodicBSR_Timer_ToString(indent+1);
    out += retxBSR_Timer_ToString(indent+1);
    out += ttiBundling_ToString(indent+1);
    return out;
}

std::string MAC_MainConfig::ul_SCH_Config::ToStringNoNewLines() const
{
    std::string out = "ul_SCH_Config:";
    if(maxHARQ_Tx_IsPresent())
        out += maxHARQ_Tx_ToStringNoNewLines();
    if(periodicBSR_Timer_IsPresent())
        out += periodicBSR_Timer_ToStringNoNewLines();
    out += retxBSR_Timer_ToStringNoNewLines();
    out += ttiBundling_ToStringNoNewLines();
    return out;
}

int MAC_MainConfig::ul_SCH_Config::Set()
{
    present = true;
    return 0;
}

int MAC_MainConfig::ul_SCH_Config::SetPresence(bool is_present)
{
    present = is_present;
    return 0;
}

int MAC_MainConfig::ul_SCH_Config::Clear()
{
    present = false;
    return 0;
}

bool MAC_MainConfig::ul_SCH_Config::IsPresent() const
{
    return present;
}

int MAC_MainConfig::ul_SCH_Config::maxHARQ_Tx_Pack(std::vector<uint8_t> &bits)
{
    uint32_t N_bits = 4;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((maxHARQ_Tx_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int MAC_MainConfig::ul_SCH_Config::maxHARQ_Tx_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return maxHARQ_Tx_Unpack(bits, idx);
}

int MAC_MainConfig::ul_SCH_Config::maxHARQ_Tx_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 4;
    if((idx + N_bits) > bits.size())
    {
        printf("MAC_MainConfig::ul_SCH_Config::maxHARQ_Tx_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 15)
    {
        printf("MAC_MainConfig::ul_SCH_Config::maxHARQ_Tx_Unpack() max failure\n");
        return -1;
    }
    maxHARQ_Tx_internal_value = (maxHARQ_Tx_Enum)packed_val;
    maxHARQ_Tx_present = true;
    return 0;
}

MAC_MainConfig::ul_SCH_Config::maxHARQ_Tx_Enum MAC_MainConfig::ul_SCH_Config::maxHARQ_Tx_Value() const
{
    if(maxHARQ_Tx_present)
        return maxHARQ_Tx_internal_value;
    return (MAC_MainConfig::ul_SCH_Config::maxHARQ_Tx_Enum)0;
}

int MAC_MainConfig::ul_SCH_Config::maxHARQ_Tx_SetValue(maxHARQ_Tx_Enum value)
{
    maxHARQ_Tx_internal_value = value;
    maxHARQ_Tx_present = true;
    return 0;
}

int MAC_MainConfig::ul_SCH_Config::maxHARQ_Tx_SetValue(std::string value)
{
    if("n1" == value)
    {
        maxHARQ_Tx_internal_value = k_maxHARQ_Tx_n1;
        maxHARQ_Tx_present = true;
        return 0;
    }
    if("n2" == value)
    {
        maxHARQ_Tx_internal_value = k_maxHARQ_Tx_n2;
        maxHARQ_Tx_present = true;
        return 0;
    }
    if("n3" == value)
    {
        maxHARQ_Tx_internal_value = k_maxHARQ_Tx_n3;
        maxHARQ_Tx_present = true;
        return 0;
    }
    if("n4" == value)
    {
        maxHARQ_Tx_internal_value = k_maxHARQ_Tx_n4;
        maxHARQ_Tx_present = true;
        return 0;
    }
    if("n5" == value)
    {
        maxHARQ_Tx_internal_value = k_maxHARQ_Tx_n5;
        maxHARQ_Tx_present = true;
        return 0;
    }
    if("n6" == value)
    {
        maxHARQ_Tx_internal_value = k_maxHARQ_Tx_n6;
        maxHARQ_Tx_present = true;
        return 0;
    }
    if("n7" == value)
    {
        maxHARQ_Tx_internal_value = k_maxHARQ_Tx_n7;
        maxHARQ_Tx_present = true;
        return 0;
    }
    if("n8" == value)
    {
        maxHARQ_Tx_internal_value = k_maxHARQ_Tx_n8;
        maxHARQ_Tx_present = true;
        return 0;
    }
    if("n10" == value)
    {
        maxHARQ_Tx_internal_value = k_maxHARQ_Tx_n10;
        maxHARQ_Tx_present = true;
        return 0;
    }
    if("n12" == value)
    {
        maxHARQ_Tx_internal_value = k_maxHARQ_Tx_n12;
        maxHARQ_Tx_present = true;
        return 0;
    }
    if("n16" == value)
    {
        maxHARQ_Tx_internal_value = k_maxHARQ_Tx_n16;
        maxHARQ_Tx_present = true;
        return 0;
    }
    if("n20" == value)
    {
        maxHARQ_Tx_internal_value = k_maxHARQ_Tx_n20;
        maxHARQ_Tx_present = true;
        return 0;
    }
    if("n24" == value)
    {
        maxHARQ_Tx_internal_value = k_maxHARQ_Tx_n24;
        maxHARQ_Tx_present = true;
        return 0;
    }
    if("n28" == value)
    {
        maxHARQ_Tx_internal_value = k_maxHARQ_Tx_n28;
        maxHARQ_Tx_present = true;
        return 0;
    }
    if("spare2" == value)
    {
        maxHARQ_Tx_internal_value = k_maxHARQ_Tx_spare2;
        maxHARQ_Tx_present = true;
        return 0;
    }
    if("spare1" == value)
    {
        maxHARQ_Tx_internal_value = k_maxHARQ_Tx_spare1;
        maxHARQ_Tx_present = true;
        return 0;
    }
    return 1;
}

std::string MAC_MainConfig::ul_SCH_Config::maxHARQ_Tx_ValueToString(maxHARQ_Tx_Enum value) const
{
    if(k_maxHARQ_Tx_n1 == value)
        return "n1";
    if(k_maxHARQ_Tx_n2 == value)
        return "n2";
    if(k_maxHARQ_Tx_n3 == value)
        return "n3";
    if(k_maxHARQ_Tx_n4 == value)
        return "n4";
    if(k_maxHARQ_Tx_n5 == value)
        return "n5";
    if(k_maxHARQ_Tx_n6 == value)
        return "n6";
    if(k_maxHARQ_Tx_n7 == value)
        return "n7";
    if(k_maxHARQ_Tx_n8 == value)
        return "n8";
    if(k_maxHARQ_Tx_n10 == value)
        return "n10";
    if(k_maxHARQ_Tx_n12 == value)
        return "n12";
    if(k_maxHARQ_Tx_n16 == value)
        return "n16";
    if(k_maxHARQ_Tx_n20 == value)
        return "n20";
    if(k_maxHARQ_Tx_n24 == value)
        return "n24";
    if(k_maxHARQ_Tx_n28 == value)
        return "n28";
    if(k_maxHARQ_Tx_spare2 == value)
        return "spare2";
    if(k_maxHARQ_Tx_spare1 == value)
        return "spare1";
    return "";
}

uint64_t MAC_MainConfig::ul_SCH_Config::maxHARQ_Tx_NumberOfValues() const
{
    return 16;
}

std::string MAC_MainConfig::ul_SCH_Config::maxHARQ_Tx_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "maxHARQ_Tx = " + maxHARQ_Tx_ValueToString(maxHARQ_Tx_internal_value) + "\n";
    return out;
}

std::string MAC_MainConfig::ul_SCH_Config::maxHARQ_Tx_ToStringNoNewLines() const
{
    std::string out = "maxHARQ_Tx=" + maxHARQ_Tx_ValueToString(maxHARQ_Tx_internal_value) + ",";
    return out;
}

int MAC_MainConfig::ul_SCH_Config::maxHARQ_Tx_Clear()
{
    maxHARQ_Tx_present = false;
    return 0;
}

bool MAC_MainConfig::ul_SCH_Config::maxHARQ_Tx_IsPresent() const
{
    return maxHARQ_Tx_present;
}

int MAC_MainConfig::ul_SCH_Config::periodicBSR_Timer_Pack(std::vector<uint8_t> &bits)
{
    uint32_t N_bits = 4;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((periodicBSR_Timer_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int MAC_MainConfig::ul_SCH_Config::periodicBSR_Timer_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return periodicBSR_Timer_Unpack(bits, idx);
}

int MAC_MainConfig::ul_SCH_Config::periodicBSR_Timer_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 4;
    if((idx + N_bits) > bits.size())
    {
        printf("MAC_MainConfig::ul_SCH_Config::periodicBSR_Timer_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 15)
    {
        printf("MAC_MainConfig::ul_SCH_Config::periodicBSR_Timer_Unpack() max failure\n");
        return -1;
    }
    periodicBSR_Timer_internal_value = (periodicBSR_Timer_Enum)packed_val;
    periodicBSR_Timer_present = true;
    return 0;
}

MAC_MainConfig::ul_SCH_Config::periodicBSR_Timer_Enum MAC_MainConfig::ul_SCH_Config::periodicBSR_Timer_Value() const
{
    if(periodicBSR_Timer_present)
        return periodicBSR_Timer_internal_value;
    return (MAC_MainConfig::ul_SCH_Config::periodicBSR_Timer_Enum)0;
}

int MAC_MainConfig::ul_SCH_Config::periodicBSR_Timer_SetValue(periodicBSR_Timer_Enum value)
{
    periodicBSR_Timer_internal_value = value;
    periodicBSR_Timer_present = true;
    return 0;
}

int MAC_MainConfig::ul_SCH_Config::periodicBSR_Timer_SetValue(std::string value)
{
    if("sf5" == value)
    {
        periodicBSR_Timer_internal_value = k_periodicBSR_Timer_sf5;
        periodicBSR_Timer_present = true;
        return 0;
    }
    if("sf10" == value)
    {
        periodicBSR_Timer_internal_value = k_periodicBSR_Timer_sf10;
        periodicBSR_Timer_present = true;
        return 0;
    }
    if("sf16" == value)
    {
        periodicBSR_Timer_internal_value = k_periodicBSR_Timer_sf16;
        periodicBSR_Timer_present = true;
        return 0;
    }
    if("sf20" == value)
    {
        periodicBSR_Timer_internal_value = k_periodicBSR_Timer_sf20;
        periodicBSR_Timer_present = true;
        return 0;
    }
    if("sf32" == value)
    {
        periodicBSR_Timer_internal_value = k_periodicBSR_Timer_sf32;
        periodicBSR_Timer_present = true;
        return 0;
    }
    if("sf40" == value)
    {
        periodicBSR_Timer_internal_value = k_periodicBSR_Timer_sf40;
        periodicBSR_Timer_present = true;
        return 0;
    }
    if("sf64" == value)
    {
        periodicBSR_Timer_internal_value = k_periodicBSR_Timer_sf64;
        periodicBSR_Timer_present = true;
        return 0;
    }
    if("sf80" == value)
    {
        periodicBSR_Timer_internal_value = k_periodicBSR_Timer_sf80;
        periodicBSR_Timer_present = true;
        return 0;
    }
    if("sf128" == value)
    {
        periodicBSR_Timer_internal_value = k_periodicBSR_Timer_sf128;
        periodicBSR_Timer_present = true;
        return 0;
    }
    if("sf160" == value)
    {
        periodicBSR_Timer_internal_value = k_periodicBSR_Timer_sf160;
        periodicBSR_Timer_present = true;
        return 0;
    }
    if("sf320" == value)
    {
        periodicBSR_Timer_internal_value = k_periodicBSR_Timer_sf320;
        periodicBSR_Timer_present = true;
        return 0;
    }
    if("sf640" == value)
    {
        periodicBSR_Timer_internal_value = k_periodicBSR_Timer_sf640;
        periodicBSR_Timer_present = true;
        return 0;
    }
    if("sf1280" == value)
    {
        periodicBSR_Timer_internal_value = k_periodicBSR_Timer_sf1280;
        periodicBSR_Timer_present = true;
        return 0;
    }
    if("sf2560" == value)
    {
        periodicBSR_Timer_internal_value = k_periodicBSR_Timer_sf2560;
        periodicBSR_Timer_present = true;
        return 0;
    }
    if("infinity" == value)
    {
        periodicBSR_Timer_internal_value = k_periodicBSR_Timer_infinity;
        periodicBSR_Timer_present = true;
        return 0;
    }
    if("spare1" == value)
    {
        periodicBSR_Timer_internal_value = k_periodicBSR_Timer_spare1;
        periodicBSR_Timer_present = true;
        return 0;
    }
    return 1;
}

std::string MAC_MainConfig::ul_SCH_Config::periodicBSR_Timer_ValueToString(periodicBSR_Timer_Enum value) const
{
    if(k_periodicBSR_Timer_sf5 == value)
        return "sf5";
    if(k_periodicBSR_Timer_sf10 == value)
        return "sf10";
    if(k_periodicBSR_Timer_sf16 == value)
        return "sf16";
    if(k_periodicBSR_Timer_sf20 == value)
        return "sf20";
    if(k_periodicBSR_Timer_sf32 == value)
        return "sf32";
    if(k_periodicBSR_Timer_sf40 == value)
        return "sf40";
    if(k_periodicBSR_Timer_sf64 == value)
        return "sf64";
    if(k_periodicBSR_Timer_sf80 == value)
        return "sf80";
    if(k_periodicBSR_Timer_sf128 == value)
        return "sf128";
    if(k_periodicBSR_Timer_sf160 == value)
        return "sf160";
    if(k_periodicBSR_Timer_sf320 == value)
        return "sf320";
    if(k_periodicBSR_Timer_sf640 == value)
        return "sf640";
    if(k_periodicBSR_Timer_sf1280 == value)
        return "sf1280";
    if(k_periodicBSR_Timer_sf2560 == value)
        return "sf2560";
    if(k_periodicBSR_Timer_infinity == value)
        return "infinity";
    if(k_periodicBSR_Timer_spare1 == value)
        return "spare1";
    return "";
}

uint64_t MAC_MainConfig::ul_SCH_Config::periodicBSR_Timer_NumberOfValues() const
{
    return 16;
}

std::string MAC_MainConfig::ul_SCH_Config::periodicBSR_Timer_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "periodicBSR_Timer = " + periodicBSR_Timer_ValueToString(periodicBSR_Timer_internal_value) + "\n";
    return out;
}

std::string MAC_MainConfig::ul_SCH_Config::periodicBSR_Timer_ToStringNoNewLines() const
{
    std::string out = "periodicBSR_Timer=" + periodicBSR_Timer_ValueToString(periodicBSR_Timer_internal_value) + ",";
    return out;
}

int MAC_MainConfig::ul_SCH_Config::periodicBSR_Timer_Clear()
{
    periodicBSR_Timer_present = false;
    return 0;
}

bool MAC_MainConfig::ul_SCH_Config::periodicBSR_Timer_IsPresent() const
{
    return periodicBSR_Timer_present;
}

int MAC_MainConfig::ul_SCH_Config::retxBSR_Timer_Pack(std::vector<uint8_t> &bits)
{
    if(!retxBSR_Timer_present)
    {
        printf("MAC_MainConfig::ul_SCH_Config::retxBSR_Timer_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 3;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((retxBSR_Timer_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int MAC_MainConfig::ul_SCH_Config::retxBSR_Timer_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return retxBSR_Timer_Unpack(bits, idx);
}

int MAC_MainConfig::ul_SCH_Config::retxBSR_Timer_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 3;
    if((idx + N_bits) > bits.size())
    {
        printf("MAC_MainConfig::ul_SCH_Config::retxBSR_Timer_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 7)
    {
        printf("MAC_MainConfig::ul_SCH_Config::retxBSR_Timer_Unpack() max failure\n");
        return -1;
    }
    retxBSR_Timer_internal_value = (retxBSR_Timer_Enum)packed_val;
    retxBSR_Timer_present = true;
    return 0;
}

MAC_MainConfig::ul_SCH_Config::retxBSR_Timer_Enum MAC_MainConfig::ul_SCH_Config::retxBSR_Timer_Value() const
{
    if(retxBSR_Timer_present)
        return retxBSR_Timer_internal_value;
    return (MAC_MainConfig::ul_SCH_Config::retxBSR_Timer_Enum)0;
}

int MAC_MainConfig::ul_SCH_Config::retxBSR_Timer_SetValue(retxBSR_Timer_Enum value)
{
    retxBSR_Timer_internal_value = value;
    retxBSR_Timer_present = true;
    return 0;
}

int MAC_MainConfig::ul_SCH_Config::retxBSR_Timer_SetValue(std::string value)
{
    if("sf320" == value)
    {
        retxBSR_Timer_internal_value = k_retxBSR_Timer_sf320;
        retxBSR_Timer_present = true;
        return 0;
    }
    if("sf640" == value)
    {
        retxBSR_Timer_internal_value = k_retxBSR_Timer_sf640;
        retxBSR_Timer_present = true;
        return 0;
    }
    if("sf1280" == value)
    {
        retxBSR_Timer_internal_value = k_retxBSR_Timer_sf1280;
        retxBSR_Timer_present = true;
        return 0;
    }
    if("sf2560" == value)
    {
        retxBSR_Timer_internal_value = k_retxBSR_Timer_sf2560;
        retxBSR_Timer_present = true;
        return 0;
    }
    if("sf5120" == value)
    {
        retxBSR_Timer_internal_value = k_retxBSR_Timer_sf5120;
        retxBSR_Timer_present = true;
        return 0;
    }
    if("sf10240" == value)
    {
        retxBSR_Timer_internal_value = k_retxBSR_Timer_sf10240;
        retxBSR_Timer_present = true;
        return 0;
    }
    if("spare2" == value)
    {
        retxBSR_Timer_internal_value = k_retxBSR_Timer_spare2;
        retxBSR_Timer_present = true;
        return 0;
    }
    if("spare1" == value)
    {
        retxBSR_Timer_internal_value = k_retxBSR_Timer_spare1;
        retxBSR_Timer_present = true;
        return 0;
    }
    return 1;
}

std::string MAC_MainConfig::ul_SCH_Config::retxBSR_Timer_ValueToString(retxBSR_Timer_Enum value) const
{
    if(k_retxBSR_Timer_sf320 == value)
        return "sf320";
    if(k_retxBSR_Timer_sf640 == value)
        return "sf640";
    if(k_retxBSR_Timer_sf1280 == value)
        return "sf1280";
    if(k_retxBSR_Timer_sf2560 == value)
        return "sf2560";
    if(k_retxBSR_Timer_sf5120 == value)
        return "sf5120";
    if(k_retxBSR_Timer_sf10240 == value)
        return "sf10240";
    if(k_retxBSR_Timer_spare2 == value)
        return "spare2";
    if(k_retxBSR_Timer_spare1 == value)
        return "spare1";
    return "";
}

uint64_t MAC_MainConfig::ul_SCH_Config::retxBSR_Timer_NumberOfValues() const
{
    return 8;
}

std::string MAC_MainConfig::ul_SCH_Config::retxBSR_Timer_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "retxBSR_Timer = " + retxBSR_Timer_ValueToString(retxBSR_Timer_internal_value) + "\n";
    return out;
}

std::string MAC_MainConfig::ul_SCH_Config::retxBSR_Timer_ToStringNoNewLines() const
{
    std::string out = "retxBSR_Timer=" + retxBSR_Timer_ValueToString(retxBSR_Timer_internal_value) + ",";
    return out;
}

int MAC_MainConfig::ul_SCH_Config::retxBSR_Timer_Clear()
{
    retxBSR_Timer_present = false;
    return 0;
}

bool MAC_MainConfig::ul_SCH_Config::retxBSR_Timer_IsPresent() const
{
    return retxBSR_Timer_present;
}

int MAC_MainConfig::ul_SCH_Config::ttiBundling_Pack(std::vector<uint8_t> &bits)
{
    if(!ttiBundling_present)
    {
        printf("MAC_MainConfig::ul_SCH_Config::ttiBundling_Pack() presence failure\n");
        return -1;
    }
    bits.push_back(ttiBundling_internal_value);
    return 0;
}

int MAC_MainConfig::ul_SCH_Config::ttiBundling_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return ttiBundling_Unpack(bits, idx);
}

int MAC_MainConfig::ul_SCH_Config::ttiBundling_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    if((idx + 1) > bits.size())
    {
        printf("MAC_MainConfig::ul_SCH_Config::ttiBundling_Unpack() index out of bounds\n");
        return -1;
    }
    ttiBundling_internal_value = bits[idx++];
    ttiBundling_present = true;
    return 0;
}

bool MAC_MainConfig::ul_SCH_Config::ttiBundling_Value() const
{
    if(ttiBundling_present)
        return ttiBundling_internal_value;
    return false;
}

int MAC_MainConfig::ul_SCH_Config::ttiBundling_SetValue(bool value)
{
    ttiBundling_internal_value = value;
    ttiBundling_present = true;
    return 0;
}

std::string MAC_MainConfig::ul_SCH_Config::ttiBundling_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ttiBundling = " + std::to_string(ttiBundling_internal_value) + "\n";
    return out;
}

std::string MAC_MainConfig::ul_SCH_Config::ttiBundling_ToStringNoNewLines() const
{
    std::string out = "ttiBundling=" + std::to_string(ttiBundling_internal_value) + ",";
    return out;
}

int MAC_MainConfig::ul_SCH_Config::ttiBundling_Clear()
{
    ttiBundling_present = false;
    return 0;
}

bool MAC_MainConfig::ul_SCH_Config::ttiBundling_IsPresent() const
{
    return ttiBundling_present;
}

DRX_Config* MAC_MainConfig::drx_Config_Set()
{
    drx_Config_present = true;
    return &drx_Config;
}

int MAC_MainConfig::drx_Config_Set(DRX_Config &value)
{
    drx_Config_present = true;
    drx_Config = value;
    return 0;
}

const DRX_Config& MAC_MainConfig::drx_Config_Get() const
{
    return drx_Config;
}

std::string MAC_MainConfig::drx_Config_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "drx_Config:\n";
    out += drx_Config.ToString(indent+1);
    return out;
}

std::string MAC_MainConfig::drx_Config_ToStringNoNewLines() const
{
    std::string out = "drx_Config:";
    out += drx_Config.ToStringNoNewLines();
    return out;
}

int MAC_MainConfig::drx_Config_Clear()
{
    drx_Config_present = false;
    return 0;
}

bool MAC_MainConfig::drx_Config_IsPresent() const
{
    return drx_Config_present;
}

TimeAlignmentTimer* MAC_MainConfig::timeAlignmentTimerDedicated_Set()
{
    timeAlignmentTimerDedicated_present = true;
    return &timeAlignmentTimerDedicated;
}

int MAC_MainConfig::timeAlignmentTimerDedicated_Set(TimeAlignmentTimer &value)
{
    timeAlignmentTimerDedicated_present = true;
    timeAlignmentTimerDedicated = value;
    return 0;
}

const TimeAlignmentTimer& MAC_MainConfig::timeAlignmentTimerDedicated_Get() const
{
    return timeAlignmentTimerDedicated;
}

std::string MAC_MainConfig::timeAlignmentTimerDedicated_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "timeAlignmentTimerDedicated:\n";
    out += timeAlignmentTimerDedicated.ToString(indent+1);
    return out;
}

std::string MAC_MainConfig::timeAlignmentTimerDedicated_ToStringNoNewLines() const
{
    std::string out = "timeAlignmentTimerDedicated:";
    out += timeAlignmentTimerDedicated.ToStringNoNewLines();
    return out;
}

int MAC_MainConfig::timeAlignmentTimerDedicated_Clear()
{
    timeAlignmentTimerDedicated_present = false;
    return 0;
}

bool MAC_MainConfig::timeAlignmentTimerDedicated_IsPresent() const
{
    return timeAlignmentTimerDedicated_present;
}

int MAC_MainConfig::phr_Config_Pack(std::vector<uint8_t> &bits)
{
    if(!phr_Config_present)
    {
        printf("MAC_MainConfig::phr_Config_Pack() presence failure\n");
        return -1;
    }
    // Extension indicator

    // Choice
    for(uint32_t i=0; i<1; i++)
        bits.push_back((phr_Config_internal_choice >> (1-i-1)) & 1);

    // Fields
    if(phr_Config_internal_choice == k_phr_Config_release)
    {
        if(0 != phr_Config_release_Pack(bits))
        {
            printf("MAC_MainConfig::phr_Config_release pack failure\n");
            return -1;
        }
    }
    if(phr_Config_internal_choice == k_phr_Config_setup)
    {
        if(0 != phr_Config_setup_value.Pack(bits))
        {
            printf("MAC_MainConfig::phr_Config_setup pack failure\n");
            return -1;
        }
    }
    return 0;
}

int MAC_MainConfig::phr_Config_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return phr_Config_Unpack(bits, idx);
}

int MAC_MainConfig::phr_Config_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 1) > bits.size())
    {
        printf("MAC_MainConfig::phr_Config_Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<1; i++)
        packed_val |= bits[idx++] << (1-i-1);

    if((MAC_MainConfig::phr_Config_Enum)packed_val > k_phr_Config_setup)
    {
        printf("MAC_MainConfig::phr_Config_Unpack() choice range failure\n");
        return -1;
    }
    phr_Config_internal_choice = (MAC_MainConfig::phr_Config_Enum)packed_val;
    phr_Config_present = true;

    // Fields
    if(phr_Config_internal_choice == k_phr_Config_release)
    {
        if(0 != phr_Config_release_Unpack(bits, idx))
        {
            printf("MAC_MainConfig::phr_Config_release unpack failure\n");
            return -1;
        }
    }
    if(phr_Config_internal_choice == k_phr_Config_setup)
    {
        if(0 != phr_Config_setup_value.Unpack(bits, idx))
        {
            printf("MAC_MainConfig::phr_Config_setup unpack failure\n");
            return -1;
        }
    }
    return 0;
}

MAC_MainConfig::phr_Config_Enum MAC_MainConfig::phr_Config_Choice() const
{
    if(phr_Config_present)
        return phr_Config_internal_choice;
    return (MAC_MainConfig::phr_Config_Enum)0;
}

int MAC_MainConfig::phr_Config_SetChoice(MAC_MainConfig::phr_Config_Enum choice)
{
    phr_Config_internal_choice = choice;
    phr_Config_present = true;
    return 0;
}

std::string MAC_MainConfig::phr_Config_ChoiceToString(phr_Config_Enum value) const
{
    if(k_phr_Config_release == value)
        return "phr_Config_release";
    if(k_phr_Config_setup == value)
        return "phr_Config_setup";
    return "";
}

uint64_t MAC_MainConfig::phr_Config_NumberOfChoices() const
{
    return 2;
}

std::string MAC_MainConfig::phr_Config_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "phr_Config = " + phr_Config_ChoiceToString(phr_Config_internal_choice) + ":\n";
    if(phr_Config_internal_choice == k_phr_Config_setup)
        out += phr_Config_setup_value.ToString(indent+1);
    return out;
}

std::string MAC_MainConfig::phr_Config_ToStringNoNewLines() const
{
    std::string out = "phr_Config=" + phr_Config_ChoiceToString(phr_Config_internal_choice) + ",";
    if(phr_Config_internal_choice == k_phr_Config_setup)
        out += phr_Config_setup_value.ToStringNoNewLines();
    return out;
}

int MAC_MainConfig::phr_Config_Clear()
{
    phr_Config_present = false;
    return 0;
}

bool MAC_MainConfig::phr_Config_IsPresent() const
{
    return phr_Config_present;
}

int MAC_MainConfig::phr_Config_setup::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != periodicPHR_Timer_Pack(bits))
        {
            printf("MAC_MainConfig::phr_Config_setup:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != prohibitPHR_Timer_Pack(bits))
        {
            printf("MAC_MainConfig::phr_Config_setup:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != dl_PathlossChange_Pack(bits))
        {
            printf("MAC_MainConfig::phr_Config_setup:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int MAC_MainConfig::phr_Config_setup::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int MAC_MainConfig::phr_Config_setup::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != periodicPHR_Timer_Unpack(bits, idx))
        {
            printf("MAC_MainConfig::phr_Config_setup:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != prohibitPHR_Timer_Unpack(bits, idx))
        {
            printf("MAC_MainConfig::phr_Config_setup:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != dl_PathlossChange_Unpack(bits, idx))
        {
            printf("MAC_MainConfig::phr_Config_setup:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string MAC_MainConfig::phr_Config_setup::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "setup:\n";
    out += periodicPHR_Timer_ToString(indent+1);
    out += prohibitPHR_Timer_ToString(indent+1);
    out += dl_PathlossChange_ToString(indent+1);
    return out;
}

std::string MAC_MainConfig::phr_Config_setup::ToStringNoNewLines() const
{
    std::string out = "setup:";
    out += periodicPHR_Timer_ToStringNoNewLines();
    out += prohibitPHR_Timer_ToStringNoNewLines();
    out += dl_PathlossChange_ToStringNoNewLines();
    return out;
}

int MAC_MainConfig::phr_Config_setup::periodicPHR_Timer_Pack(std::vector<uint8_t> &bits)
{
    if(!periodicPHR_Timer_present)
    {
        printf("MAC_MainConfig::phr_Config_setup::periodicPHR_Timer_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 3;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((periodicPHR_Timer_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int MAC_MainConfig::phr_Config_setup::periodicPHR_Timer_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return periodicPHR_Timer_Unpack(bits, idx);
}

int MAC_MainConfig::phr_Config_setup::periodicPHR_Timer_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 3;
    if((idx + N_bits) > bits.size())
    {
        printf("MAC_MainConfig::phr_Config_setup::periodicPHR_Timer_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 7)
    {
        printf("MAC_MainConfig::phr_Config_setup::periodicPHR_Timer_Unpack() max failure\n");
        return -1;
    }
    periodicPHR_Timer_internal_value = (periodicPHR_Timer_Enum)packed_val;
    periodicPHR_Timer_present = true;
    return 0;
}

MAC_MainConfig::phr_Config_setup::periodicPHR_Timer_Enum MAC_MainConfig::phr_Config_setup::periodicPHR_Timer_Value() const
{
    if(periodicPHR_Timer_present)
        return periodicPHR_Timer_internal_value;
    return (MAC_MainConfig::phr_Config_setup::periodicPHR_Timer_Enum)0;
}

int MAC_MainConfig::phr_Config_setup::periodicPHR_Timer_SetValue(periodicPHR_Timer_Enum value)
{
    periodicPHR_Timer_internal_value = value;
    periodicPHR_Timer_present = true;
    return 0;
}

int MAC_MainConfig::phr_Config_setup::periodicPHR_Timer_SetValue(std::string value)
{
    if("sf10" == value)
    {
        periodicPHR_Timer_internal_value = k_periodicPHR_Timer_sf10;
        periodicPHR_Timer_present = true;
        return 0;
    }
    if("sf20" == value)
    {
        periodicPHR_Timer_internal_value = k_periodicPHR_Timer_sf20;
        periodicPHR_Timer_present = true;
        return 0;
    }
    if("sf50" == value)
    {
        periodicPHR_Timer_internal_value = k_periodicPHR_Timer_sf50;
        periodicPHR_Timer_present = true;
        return 0;
    }
    if("sf100" == value)
    {
        periodicPHR_Timer_internal_value = k_periodicPHR_Timer_sf100;
        periodicPHR_Timer_present = true;
        return 0;
    }
    if("sf200" == value)
    {
        periodicPHR_Timer_internal_value = k_periodicPHR_Timer_sf200;
        periodicPHR_Timer_present = true;
        return 0;
    }
    if("sf500" == value)
    {
        periodicPHR_Timer_internal_value = k_periodicPHR_Timer_sf500;
        periodicPHR_Timer_present = true;
        return 0;
    }
    if("sf1000" == value)
    {
        periodicPHR_Timer_internal_value = k_periodicPHR_Timer_sf1000;
        periodicPHR_Timer_present = true;
        return 0;
    }
    if("infinity" == value)
    {
        periodicPHR_Timer_internal_value = k_periodicPHR_Timer_infinity;
        periodicPHR_Timer_present = true;
        return 0;
    }
    return 1;
}

std::string MAC_MainConfig::phr_Config_setup::periodicPHR_Timer_ValueToString(periodicPHR_Timer_Enum value) const
{
    if(k_periodicPHR_Timer_sf10 == value)
        return "sf10";
    if(k_periodicPHR_Timer_sf20 == value)
        return "sf20";
    if(k_periodicPHR_Timer_sf50 == value)
        return "sf50";
    if(k_periodicPHR_Timer_sf100 == value)
        return "sf100";
    if(k_periodicPHR_Timer_sf200 == value)
        return "sf200";
    if(k_periodicPHR_Timer_sf500 == value)
        return "sf500";
    if(k_periodicPHR_Timer_sf1000 == value)
        return "sf1000";
    if(k_periodicPHR_Timer_infinity == value)
        return "infinity";
    return "";
}

uint64_t MAC_MainConfig::phr_Config_setup::periodicPHR_Timer_NumberOfValues() const
{
    return 8;
}

std::string MAC_MainConfig::phr_Config_setup::periodicPHR_Timer_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "periodicPHR_Timer = " + periodicPHR_Timer_ValueToString(periodicPHR_Timer_internal_value) + "\n";
    return out;
}

std::string MAC_MainConfig::phr_Config_setup::periodicPHR_Timer_ToStringNoNewLines() const
{
    std::string out = "periodicPHR_Timer=" + periodicPHR_Timer_ValueToString(periodicPHR_Timer_internal_value) + ",";
    return out;
}

int MAC_MainConfig::phr_Config_setup::periodicPHR_Timer_Clear()
{
    periodicPHR_Timer_present = false;
    return 0;
}

bool MAC_MainConfig::phr_Config_setup::periodicPHR_Timer_IsPresent() const
{
    return periodicPHR_Timer_present;
}

int MAC_MainConfig::phr_Config_setup::prohibitPHR_Timer_Pack(std::vector<uint8_t> &bits)
{
    if(!prohibitPHR_Timer_present)
    {
        printf("MAC_MainConfig::phr_Config_setup::prohibitPHR_Timer_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 3;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((prohibitPHR_Timer_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int MAC_MainConfig::phr_Config_setup::prohibitPHR_Timer_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return prohibitPHR_Timer_Unpack(bits, idx);
}

int MAC_MainConfig::phr_Config_setup::prohibitPHR_Timer_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 3;
    if((idx + N_bits) > bits.size())
    {
        printf("MAC_MainConfig::phr_Config_setup::prohibitPHR_Timer_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 7)
    {
        printf("MAC_MainConfig::phr_Config_setup::prohibitPHR_Timer_Unpack() max failure\n");
        return -1;
    }
    prohibitPHR_Timer_internal_value = (prohibitPHR_Timer_Enum)packed_val;
    prohibitPHR_Timer_present = true;
    return 0;
}

MAC_MainConfig::phr_Config_setup::prohibitPHR_Timer_Enum MAC_MainConfig::phr_Config_setup::prohibitPHR_Timer_Value() const
{
    if(prohibitPHR_Timer_present)
        return prohibitPHR_Timer_internal_value;
    return (MAC_MainConfig::phr_Config_setup::prohibitPHR_Timer_Enum)0;
}

int MAC_MainConfig::phr_Config_setup::prohibitPHR_Timer_SetValue(prohibitPHR_Timer_Enum value)
{
    prohibitPHR_Timer_internal_value = value;
    prohibitPHR_Timer_present = true;
    return 0;
}

int MAC_MainConfig::phr_Config_setup::prohibitPHR_Timer_SetValue(std::string value)
{
    if("sf0" == value)
    {
        prohibitPHR_Timer_internal_value = k_prohibitPHR_Timer_sf0;
        prohibitPHR_Timer_present = true;
        return 0;
    }
    if("sf10" == value)
    {
        prohibitPHR_Timer_internal_value = k_prohibitPHR_Timer_sf10;
        prohibitPHR_Timer_present = true;
        return 0;
    }
    if("sf20" == value)
    {
        prohibitPHR_Timer_internal_value = k_prohibitPHR_Timer_sf20;
        prohibitPHR_Timer_present = true;
        return 0;
    }
    if("sf50" == value)
    {
        prohibitPHR_Timer_internal_value = k_prohibitPHR_Timer_sf50;
        prohibitPHR_Timer_present = true;
        return 0;
    }
    if("sf100" == value)
    {
        prohibitPHR_Timer_internal_value = k_prohibitPHR_Timer_sf100;
        prohibitPHR_Timer_present = true;
        return 0;
    }
    if("sf200" == value)
    {
        prohibitPHR_Timer_internal_value = k_prohibitPHR_Timer_sf200;
        prohibitPHR_Timer_present = true;
        return 0;
    }
    if("sf500" == value)
    {
        prohibitPHR_Timer_internal_value = k_prohibitPHR_Timer_sf500;
        prohibitPHR_Timer_present = true;
        return 0;
    }
    if("sf1000" == value)
    {
        prohibitPHR_Timer_internal_value = k_prohibitPHR_Timer_sf1000;
        prohibitPHR_Timer_present = true;
        return 0;
    }
    return 1;
}

std::string MAC_MainConfig::phr_Config_setup::prohibitPHR_Timer_ValueToString(prohibitPHR_Timer_Enum value) const
{
    if(k_prohibitPHR_Timer_sf0 == value)
        return "sf0";
    if(k_prohibitPHR_Timer_sf10 == value)
        return "sf10";
    if(k_prohibitPHR_Timer_sf20 == value)
        return "sf20";
    if(k_prohibitPHR_Timer_sf50 == value)
        return "sf50";
    if(k_prohibitPHR_Timer_sf100 == value)
        return "sf100";
    if(k_prohibitPHR_Timer_sf200 == value)
        return "sf200";
    if(k_prohibitPHR_Timer_sf500 == value)
        return "sf500";
    if(k_prohibitPHR_Timer_sf1000 == value)
        return "sf1000";
    return "";
}

uint64_t MAC_MainConfig::phr_Config_setup::prohibitPHR_Timer_NumberOfValues() const
{
    return 8;
}

std::string MAC_MainConfig::phr_Config_setup::prohibitPHR_Timer_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "prohibitPHR_Timer = " + prohibitPHR_Timer_ValueToString(prohibitPHR_Timer_internal_value) + "\n";
    return out;
}

std::string MAC_MainConfig::phr_Config_setup::prohibitPHR_Timer_ToStringNoNewLines() const
{
    std::string out = "prohibitPHR_Timer=" + prohibitPHR_Timer_ValueToString(prohibitPHR_Timer_internal_value) + ",";
    return out;
}

int MAC_MainConfig::phr_Config_setup::prohibitPHR_Timer_Clear()
{
    prohibitPHR_Timer_present = false;
    return 0;
}

bool MAC_MainConfig::phr_Config_setup::prohibitPHR_Timer_IsPresent() const
{
    return prohibitPHR_Timer_present;
}

int MAC_MainConfig::phr_Config_setup::dl_PathlossChange_Pack(std::vector<uint8_t> &bits)
{
    if(!dl_PathlossChange_present)
    {
        printf("MAC_MainConfig::phr_Config_setup::dl_PathlossChange_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 2;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((dl_PathlossChange_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int MAC_MainConfig::phr_Config_setup::dl_PathlossChange_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return dl_PathlossChange_Unpack(bits, idx);
}

int MAC_MainConfig::phr_Config_setup::dl_PathlossChange_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 2;
    if((idx + N_bits) > bits.size())
    {
        printf("MAC_MainConfig::phr_Config_setup::dl_PathlossChange_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 3)
    {
        printf("MAC_MainConfig::phr_Config_setup::dl_PathlossChange_Unpack() max failure\n");
        return -1;
    }
    dl_PathlossChange_internal_value = (dl_PathlossChange_Enum)packed_val;
    dl_PathlossChange_present = true;
    return 0;
}

MAC_MainConfig::phr_Config_setup::dl_PathlossChange_Enum MAC_MainConfig::phr_Config_setup::dl_PathlossChange_Value() const
{
    if(dl_PathlossChange_present)
        return dl_PathlossChange_internal_value;
    return (MAC_MainConfig::phr_Config_setup::dl_PathlossChange_Enum)0;
}

int MAC_MainConfig::phr_Config_setup::dl_PathlossChange_SetValue(dl_PathlossChange_Enum value)
{
    dl_PathlossChange_internal_value = value;
    dl_PathlossChange_present = true;
    return 0;
}

int MAC_MainConfig::phr_Config_setup::dl_PathlossChange_SetValue(std::string value)
{
    if("dB1" == value)
    {
        dl_PathlossChange_internal_value = k_dl_PathlossChange_dB1;
        dl_PathlossChange_present = true;
        return 0;
    }
    if("dB3" == value)
    {
        dl_PathlossChange_internal_value = k_dl_PathlossChange_dB3;
        dl_PathlossChange_present = true;
        return 0;
    }
    if("dB6" == value)
    {
        dl_PathlossChange_internal_value = k_dl_PathlossChange_dB6;
        dl_PathlossChange_present = true;
        return 0;
    }
    if("infinity" == value)
    {
        dl_PathlossChange_internal_value = k_dl_PathlossChange_infinity;
        dl_PathlossChange_present = true;
        return 0;
    }
    return 1;
}

std::string MAC_MainConfig::phr_Config_setup::dl_PathlossChange_ValueToString(dl_PathlossChange_Enum value) const
{
    if(k_dl_PathlossChange_dB1 == value)
        return "dB1";
    if(k_dl_PathlossChange_dB3 == value)
        return "dB3";
    if(k_dl_PathlossChange_dB6 == value)
        return "dB6";
    if(k_dl_PathlossChange_infinity == value)
        return "infinity";
    return "";
}

uint64_t MAC_MainConfig::phr_Config_setup::dl_PathlossChange_NumberOfValues() const
{
    return 4;
}

std::string MAC_MainConfig::phr_Config_setup::dl_PathlossChange_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "dl_PathlossChange = " + dl_PathlossChange_ValueToString(dl_PathlossChange_internal_value) + "\n";
    return out;
}

std::string MAC_MainConfig::phr_Config_setup::dl_PathlossChange_ToStringNoNewLines() const
{
    std::string out = "dl_PathlossChange=" + dl_PathlossChange_ValueToString(dl_PathlossChange_internal_value) + ",";
    return out;
}

int MAC_MainConfig::phr_Config_setup::dl_PathlossChange_Clear()
{
    dl_PathlossChange_present = false;
    return 0;
}

bool MAC_MainConfig::phr_Config_setup::dl_PathlossChange_IsPresent() const
{
    return dl_PathlossChange_present;
}

int MAC_MainConfig::sr_ProhibitTimer_r9_Pack(std::vector<uint8_t> &bits)
{
    int64_t val_to_pack = sr_ProhibitTimer_r9_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (7 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int MAC_MainConfig::sr_ProhibitTimer_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return sr_ProhibitTimer_r9_Unpack(bits, idx);
}

int MAC_MainConfig::sr_ProhibitTimer_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (7 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("MAC_MainConfig::sr_ProhibitTimer_r9_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    sr_ProhibitTimer_r9_internal_value = packed_val + 0;
    sr_ProhibitTimer_r9_present = true;
    return 0;
}

int64_t MAC_MainConfig::sr_ProhibitTimer_r9_Value() const
{
    if(sr_ProhibitTimer_r9_present)
        return sr_ProhibitTimer_r9_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int MAC_MainConfig::sr_ProhibitTimer_r9_SetValue(int64_t value)
{
    if(value < 0 || value > 7)
    {
        printf("MAC_MainConfig::sr_ProhibitTimer_r9_SetValue() range failure\n");
        return -1;
    }
    sr_ProhibitTimer_r9_internal_value = value;
    sr_ProhibitTimer_r9_present = true;
    return 0;
}

std::string MAC_MainConfig::sr_ProhibitTimer_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "sr_ProhibitTimer_r9 = " + std::to_string(sr_ProhibitTimer_r9_internal_value) + "\n";
    return out;
}

std::string MAC_MainConfig::sr_ProhibitTimer_r9_ToStringNoNewLines() const
{
    std::string out = "sr_ProhibitTimer_r9=" + std::to_string(sr_ProhibitTimer_r9_internal_value) + ",";
    return out;
}

int MAC_MainConfig::sr_ProhibitTimer_r9_Clear()
{
    sr_ProhibitTimer_r9_present = false;
    return 0;
}

bool MAC_MainConfig::sr_ProhibitTimer_r9_IsPresent() const
{
    return sr_ProhibitTimer_r9_present;
}

int MAC_MainConfig::sCellDeactivationTimer_r10_Pack(std::vector<uint8_t> &bits)
{
    uint32_t N_bits = 3;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((sCellDeactivationTimer_r10_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int MAC_MainConfig::sCellDeactivationTimer_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return sCellDeactivationTimer_r10_Unpack(bits, idx);
}

int MAC_MainConfig::sCellDeactivationTimer_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 3;
    if((idx + N_bits) > bits.size())
    {
        printf("MAC_MainConfig::sCellDeactivationTimer_r10_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 7)
    {
        printf("MAC_MainConfig::sCellDeactivationTimer_r10_Unpack() max failure\n");
        return -1;
    }
    sCellDeactivationTimer_r10_internal_value = (sCellDeactivationTimer_r10_Enum)packed_val;
    sCellDeactivationTimer_r10_present = true;
    return 0;
}

MAC_MainConfig::sCellDeactivationTimer_r10_Enum MAC_MainConfig::sCellDeactivationTimer_r10_Value() const
{
    if(sCellDeactivationTimer_r10_present)
        return sCellDeactivationTimer_r10_internal_value;
    return (MAC_MainConfig::sCellDeactivationTimer_r10_Enum)0;
}

int MAC_MainConfig::sCellDeactivationTimer_r10_SetValue(sCellDeactivationTimer_r10_Enum value)
{
    sCellDeactivationTimer_r10_internal_value = value;
    sCellDeactivationTimer_r10_present = true;
    return 0;
}

int MAC_MainConfig::sCellDeactivationTimer_r10_SetValue(std::string value)
{
    if("rf2" == value)
    {
        sCellDeactivationTimer_r10_internal_value = k_sCellDeactivationTimer_r10_rf2;
        sCellDeactivationTimer_r10_present = true;
        return 0;
    }
    if("rf4" == value)
    {
        sCellDeactivationTimer_r10_internal_value = k_sCellDeactivationTimer_r10_rf4;
        sCellDeactivationTimer_r10_present = true;
        return 0;
    }
    if("rf8" == value)
    {
        sCellDeactivationTimer_r10_internal_value = k_sCellDeactivationTimer_r10_rf8;
        sCellDeactivationTimer_r10_present = true;
        return 0;
    }
    if("rf16" == value)
    {
        sCellDeactivationTimer_r10_internal_value = k_sCellDeactivationTimer_r10_rf16;
        sCellDeactivationTimer_r10_present = true;
        return 0;
    }
    if("rf32" == value)
    {
        sCellDeactivationTimer_r10_internal_value = k_sCellDeactivationTimer_r10_rf32;
        sCellDeactivationTimer_r10_present = true;
        return 0;
    }
    if("rf64" == value)
    {
        sCellDeactivationTimer_r10_internal_value = k_sCellDeactivationTimer_r10_rf64;
        sCellDeactivationTimer_r10_present = true;
        return 0;
    }
    if("rf128" == value)
    {
        sCellDeactivationTimer_r10_internal_value = k_sCellDeactivationTimer_r10_rf128;
        sCellDeactivationTimer_r10_present = true;
        return 0;
    }
    if("infinity" == value)
    {
        sCellDeactivationTimer_r10_internal_value = k_sCellDeactivationTimer_r10_infinity;
        sCellDeactivationTimer_r10_present = true;
        return 0;
    }
    return 1;
}

std::string MAC_MainConfig::sCellDeactivationTimer_r10_ValueToString(sCellDeactivationTimer_r10_Enum value) const
{
    if(k_sCellDeactivationTimer_r10_rf2 == value)
        return "rf2";
    if(k_sCellDeactivationTimer_r10_rf4 == value)
        return "rf4";
    if(k_sCellDeactivationTimer_r10_rf8 == value)
        return "rf8";
    if(k_sCellDeactivationTimer_r10_rf16 == value)
        return "rf16";
    if(k_sCellDeactivationTimer_r10_rf32 == value)
        return "rf32";
    if(k_sCellDeactivationTimer_r10_rf64 == value)
        return "rf64";
    if(k_sCellDeactivationTimer_r10_rf128 == value)
        return "rf128";
    if(k_sCellDeactivationTimer_r10_infinity == value)
        return "infinity";
    return "";
}

uint64_t MAC_MainConfig::sCellDeactivationTimer_r10_NumberOfValues() const
{
    return 8;
}

std::string MAC_MainConfig::sCellDeactivationTimer_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "sCellDeactivationTimer_r10 = " + sCellDeactivationTimer_r10_ValueToString(sCellDeactivationTimer_r10_internal_value) + "\n";
    return out;
}

std::string MAC_MainConfig::sCellDeactivationTimer_r10_ToStringNoNewLines() const
{
    std::string out = "sCellDeactivationTimer_r10=" + sCellDeactivationTimer_r10_ValueToString(sCellDeactivationTimer_r10_internal_value) + ",";
    return out;
}

int MAC_MainConfig::sCellDeactivationTimer_r10_Clear()
{
    sCellDeactivationTimer_r10_present = false;
    return 0;
}

bool MAC_MainConfig::sCellDeactivationTimer_r10_IsPresent() const
{
    return sCellDeactivationTimer_r10_present;
}

int MAC_MainConfig::extendedBSR_Sizes_r10_Pack(std::vector<uint8_t> &bits)
{
    bits.push_back(extendedBSR_Sizes_r10_internal_value);
    return 0;
}

int MAC_MainConfig::extendedBSR_Sizes_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return extendedBSR_Sizes_r10_Unpack(bits, idx);
}

int MAC_MainConfig::extendedBSR_Sizes_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    if((idx + 1) > bits.size())
    {
        printf("MAC_MainConfig::extendedBSR_Sizes_r10_Unpack() index out of bounds\n");
        return -1;
    }
    extendedBSR_Sizes_r10_internal_value = bits[idx++];
    extendedBSR_Sizes_r10_present = true;
    return 0;
}

bool MAC_MainConfig::extendedBSR_Sizes_r10_Value() const
{
    if(extendedBSR_Sizes_r10_present)
        return extendedBSR_Sizes_r10_internal_value;
    return false;
}

int MAC_MainConfig::extendedBSR_Sizes_r10_SetValue(bool value)
{
    extendedBSR_Sizes_r10_internal_value = value;
    extendedBSR_Sizes_r10_present = true;
    return 0;
}

std::string MAC_MainConfig::extendedBSR_Sizes_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "extendedBSR_Sizes_r10 = " + std::to_string(extendedBSR_Sizes_r10_internal_value) + "\n";
    return out;
}

std::string MAC_MainConfig::extendedBSR_Sizes_r10_ToStringNoNewLines() const
{
    std::string out = "extendedBSR_Sizes_r10=" + std::to_string(extendedBSR_Sizes_r10_internal_value) + ",";
    return out;
}

int MAC_MainConfig::extendedBSR_Sizes_r10_Clear()
{
    extendedBSR_Sizes_r10_present = false;
    return 0;
}

bool MAC_MainConfig::extendedBSR_Sizes_r10_IsPresent() const
{
    return extendedBSR_Sizes_r10_present;
}

int MAC_MainConfig::extendedPHR_r10_Pack(std::vector<uint8_t> &bits)
{
    bits.push_back(extendedPHR_r10_internal_value);
    return 0;
}

int MAC_MainConfig::extendedPHR_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return extendedPHR_r10_Unpack(bits, idx);
}

int MAC_MainConfig::extendedPHR_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    if((idx + 1) > bits.size())
    {
        printf("MAC_MainConfig::extendedPHR_r10_Unpack() index out of bounds\n");
        return -1;
    }
    extendedPHR_r10_internal_value = bits[idx++];
    extendedPHR_r10_present = true;
    return 0;
}

bool MAC_MainConfig::extendedPHR_r10_Value() const
{
    if(extendedPHR_r10_present)
        return extendedPHR_r10_internal_value;
    return false;
}

int MAC_MainConfig::extendedPHR_r10_SetValue(bool value)
{
    extendedPHR_r10_internal_value = value;
    extendedPHR_r10_present = true;
    return 0;
}

std::string MAC_MainConfig::extendedPHR_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "extendedPHR_r10 = " + std::to_string(extendedPHR_r10_internal_value) + "\n";
    return out;
}

std::string MAC_MainConfig::extendedPHR_r10_ToStringNoNewLines() const
{
    std::string out = "extendedPHR_r10=" + std::to_string(extendedPHR_r10_internal_value) + ",";
    return out;
}

int MAC_MainConfig::extendedPHR_r10_Clear()
{
    extendedPHR_r10_present = false;
    return 0;
}

bool MAC_MainConfig::extendedPHR_r10_IsPresent() const
{
    return extendedPHR_r10_present;
}

