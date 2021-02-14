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

#include "PhysicalConfigDedicated.h"

#include <cmath>

int PhysicalConfigDedicated::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator
    bool has_extension = false;
    if(cqi_ReportConfig_v920_IsPresent() || antennaInfo_v920_IsPresent() || antennaInfo_r10_IsPresent() || cif_Presence_IsPresent() || cqi_ReportConfig_v10x0_IsPresent() || csi_RS_Config_r10_IsPresent() || pucch_ConfigDedicated_v10x0_IsPresent() || pusch_ConfigDedicated_v10x0_IsPresent() || schedulingRequestConfig_v10x0_IsPresent() || soundingRS_UL_ConfigDedicated_v10x0_IsPresent() || soundingRS_UL_ConfigDedicatedAperiodic_r10_IsPresent() || ul_AntennaInfo_r10_IsPresent())
    {
        bits.push_back(1);
        has_extension = true;
    }else{
        bits.push_back(0);
    }

    // Optional indicators
    bits.push_back(pdsch_ConfigDedicated_IsPresent());
    bits.push_back(pucch_ConfigDedicated_IsPresent());
    bits.push_back(pusch_ConfigDedicated_IsPresent());
    bits.push_back(uplinkPowerControlDedicated_IsPresent());
    bits.push_back(tpc_PDCCH_ConfigPUCCH_IsPresent());
    bits.push_back(tpc_PDCCH_ConfigPUSCH_IsPresent());
    bits.push_back(cqi_ReportConfig_IsPresent());
    bits.push_back(soundingRS_UL_ConfigDedicated_IsPresent());
    bits.push_back(antennaInfo_IsPresent());
    bits.push_back(schedulingRequestConfig_IsPresent());

    // Fields
    if(pdsch_ConfigDedicated_IsPresent())
    {
        if(0 != pdsch_ConfigDedicated.Pack(bits))
        {
            printf("PhysicalConfigDedicated:: field pack failure\n");
            return -1;
        }
    }
    if(pucch_ConfigDedicated_IsPresent())
    {
        if(0 != pucch_ConfigDedicated.Pack(bits))
        {
            printf("PhysicalConfigDedicated:: field pack failure\n");
            return -1;
        }
    }
    if(pusch_ConfigDedicated_IsPresent())
    {
        if(0 != pusch_ConfigDedicated.Pack(bits))
        {
            printf("PhysicalConfigDedicated:: field pack failure\n");
            return -1;
        }
    }
    if(uplinkPowerControlDedicated_IsPresent())
    {
        if(0 != uplinkPowerControlDedicated.Pack(bits))
        {
            printf("PhysicalConfigDedicated:: field pack failure\n");
            return -1;
        }
    }
    if(tpc_PDCCH_ConfigPUCCH_IsPresent())
    {
        if(0 != tpc_PDCCH_ConfigPUCCH.Pack(bits))
        {
            printf("PhysicalConfigDedicated:: field pack failure\n");
            return -1;
        }
    }
    if(tpc_PDCCH_ConfigPUSCH_IsPresent())
    {
        if(0 != tpc_PDCCH_ConfigPUSCH.Pack(bits))
        {
            printf("PhysicalConfigDedicated:: field pack failure\n");
            return -1;
        }
    }
    if(cqi_ReportConfig_IsPresent())
    {
        if(0 != cqi_ReportConfig.Pack(bits))
        {
            printf("PhysicalConfigDedicated:: field pack failure\n");
            return -1;
        }
    }
    if(soundingRS_UL_ConfigDedicated_IsPresent())
    {
        if(0 != soundingRS_UL_ConfigDedicated.Pack(bits))
        {
            printf("PhysicalConfigDedicated:: field pack failure\n");
            return -1;
        }
    }
    if(antennaInfo_IsPresent())
    {
        if(0 != antennaInfo_Pack(bits))
        {
            printf("PhysicalConfigDedicated:: field pack failure\n");
            return -1;
        }
    }
    if(schedulingRequestConfig_IsPresent())
    {
        if(0 != schedulingRequestConfig.Pack(bits))
        {
            printf("PhysicalConfigDedicated:: field pack failure\n");
            return -1;
        }
    }

    // Extension
    if(has_extension)
    {
        // Number of extension fields
        if(11 < 64)
        {
            bits.push_back(0);
            for(uint32_t i=0; i<6; i++)
                bits.push_back((11 >> (6-i-1)) & 1);
        }else{
            printf("PhysicalConfigDedicated:: Extension list size too large failure\n");
            return -1;
        }

        // Extension field presence indicators
        bits.push_back(cqi_ReportConfig_v920_IsPresent());
        bits.push_back(antennaInfo_v920_IsPresent());
        bits.push_back(antennaInfo_r10_IsPresent());
        bits.push_back(cif_Presence_IsPresent());
        bits.push_back(cqi_ReportConfig_v10x0_IsPresent());
        bits.push_back(csi_RS_Config_r10_IsPresent());
        bits.push_back(pucch_ConfigDedicated_v10x0_IsPresent());
        bits.push_back(pusch_ConfigDedicated_v10x0_IsPresent());
        bits.push_back(schedulingRequestConfig_v10x0_IsPresent());
        bits.push_back(soundingRS_UL_ConfigDedicated_v10x0_IsPresent());
        bits.push_back(soundingRS_UL_ConfigDedicatedAperiodic_r10_IsPresent());
        bits.push_back(ul_AntennaInfo_r10_IsPresent());

        // Extension fields
        if(cqi_ReportConfig_v920_IsPresent())
        {
            std::vector<uint8_t> field_bits;
            if(0 != cqi_ReportConfig_v920.Pack(field_bits))
            {
                printf("PhysicalConfigDedicated:: field pack failure\n");
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
        if(antennaInfo_v920_IsPresent())
        {
            std::vector<uint8_t> field_bits;
            if(0 != antennaInfo_v920.Pack(field_bits))
            {
                printf("PhysicalConfigDedicated:: field pack failure\n");
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
        if(antennaInfo_r10_IsPresent())
        {
            std::vector<uint8_t> field_bits;
            if(0 != antennaInfo_r10_Pack(field_bits))
            {
                printf("PhysicalConfigDedicated:: field pack failure\n");
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
        if(cif_Presence_IsPresent())
        {
            std::vector<uint8_t> field_bits;
            if(0 != cif_Presence_Pack(field_bits))
            {
                printf("PhysicalConfigDedicated:: field pack failure\n");
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
        if(cqi_ReportConfig_v10x0_IsPresent())
        {
            std::vector<uint8_t> field_bits;
            if(0 != cqi_ReportConfig_v10x0.Pack(field_bits))
            {
                printf("PhysicalConfigDedicated:: field pack failure\n");
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
        if(csi_RS_Config_r10_IsPresent())
        {
            std::vector<uint8_t> field_bits;
            if(0 != csi_RS_Config_r10.Pack(field_bits))
            {
                printf("PhysicalConfigDedicated:: field pack failure\n");
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
        if(pucch_ConfigDedicated_v10x0_IsPresent())
        {
            std::vector<uint8_t> field_bits;
            if(0 != pucch_ConfigDedicated_v10x0.Pack(field_bits))
            {
                printf("PhysicalConfigDedicated:: field pack failure\n");
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
        if(pusch_ConfigDedicated_v10x0_IsPresent())
        {
            std::vector<uint8_t> field_bits;
            if(0 != pusch_ConfigDedicated_v10x0.Pack(field_bits))
            {
                printf("PhysicalConfigDedicated:: field pack failure\n");
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
        if(schedulingRequestConfig_v10x0_IsPresent())
        {
            std::vector<uint8_t> field_bits;
            if(0 != schedulingRequestConfig_v10x0.Pack(field_bits))
            {
                printf("PhysicalConfigDedicated:: field pack failure\n");
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
        if(soundingRS_UL_ConfigDedicated_v10x0_IsPresent())
        {
            std::vector<uint8_t> field_bits;
            if(0 != soundingRS_UL_ConfigDedicated_v10x0.Pack(field_bits))
            {
                printf("PhysicalConfigDedicated:: field pack failure\n");
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
        if(soundingRS_UL_ConfigDedicatedAperiodic_r10_IsPresent())
        {
            std::vector<uint8_t> field_bits;
            if(0 != soundingRS_UL_ConfigDedicatedAperiodic_r10.Pack(field_bits))
            {
                printf("PhysicalConfigDedicated:: field pack failure\n");
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
        if(ul_AntennaInfo_r10_IsPresent())
        {
            std::vector<uint8_t> field_bits;
            if(0 != ul_AntennaInfo_r10.Pack(field_bits))
            {
                printf("PhysicalConfigDedicated:: field pack failure\n");
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

int PhysicalConfigDedicated::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int PhysicalConfigDedicated::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("PhysicalConfigDedicated::Unpack() index out of bounds for extension\n");
        return -1;
    }
    bool has_extension = bits[idx++];

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("PhysicalConfigDedicated::Unpack() index out of bounds for optional indiator pdsch_ConfigDedicated\n");
        return -1;
    }
    pdsch_ConfigDedicated_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("PhysicalConfigDedicated::Unpack() index out of bounds for optional indiator pucch_ConfigDedicated\n");
        return -1;
    }
    pucch_ConfigDedicated_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("PhysicalConfigDedicated::Unpack() index out of bounds for optional indiator pusch_ConfigDedicated\n");
        return -1;
    }
    pusch_ConfigDedicated_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("PhysicalConfigDedicated::Unpack() index out of bounds for optional indiator uplinkPowerControlDedicated\n");
        return -1;
    }
    uplinkPowerControlDedicated_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("PhysicalConfigDedicated::Unpack() index out of bounds for optional indiator tpc_PDCCH_ConfigPUCCH\n");
        return -1;
    }
    tpc_PDCCH_ConfigPUCCH_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("PhysicalConfigDedicated::Unpack() index out of bounds for optional indiator tpc_PDCCH_ConfigPUSCH\n");
        return -1;
    }
    tpc_PDCCH_ConfigPUSCH_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("PhysicalConfigDedicated::Unpack() index out of bounds for optional indiator cqi_ReportConfig\n");
        return -1;
    }
    cqi_ReportConfig_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("PhysicalConfigDedicated::Unpack() index out of bounds for optional indiator soundingRS_UL_ConfigDedicated\n");
        return -1;
    }
    soundingRS_UL_ConfigDedicated_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("PhysicalConfigDedicated::Unpack() index out of bounds for optional indiator antennaInfo\n");
        return -1;
    }
    antennaInfo_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("PhysicalConfigDedicated::Unpack() index out of bounds for optional indiator schedulingRequestConfig\n");
        return -1;
    }
    schedulingRequestConfig_present = bits[idx++];

    // Fields
    if(pdsch_ConfigDedicated_present)
    {
        if(0 != pdsch_ConfigDedicated.Unpack(bits, idx))
        {
            printf("PhysicalConfigDedicated:: field unpack failure\n");
            return -1;
        }
    }
    if(pucch_ConfigDedicated_present)
    {
        if(0 != pucch_ConfigDedicated.Unpack(bits, idx))
        {
            printf("PhysicalConfigDedicated:: field unpack failure\n");
            return -1;
        }
    }
    if(pusch_ConfigDedicated_present)
    {
        if(0 != pusch_ConfigDedicated.Unpack(bits, idx))
        {
            printf("PhysicalConfigDedicated:: field unpack failure\n");
            return -1;
        }
    }
    if(uplinkPowerControlDedicated_present)
    {
        if(0 != uplinkPowerControlDedicated.Unpack(bits, idx))
        {
            printf("PhysicalConfigDedicated:: field unpack failure\n");
            return -1;
        }
    }
    if(tpc_PDCCH_ConfigPUCCH_present)
    {
        if(0 != tpc_PDCCH_ConfigPUCCH.Unpack(bits, idx))
        {
            printf("PhysicalConfigDedicated:: field unpack failure\n");
            return -1;
        }
    }
    if(tpc_PDCCH_ConfigPUSCH_present)
    {
        if(0 != tpc_PDCCH_ConfigPUSCH.Unpack(bits, idx))
        {
            printf("PhysicalConfigDedicated:: field unpack failure\n");
            return -1;
        }
    }
    if(cqi_ReportConfig_present)
    {
        if(0 != cqi_ReportConfig.Unpack(bits, idx))
        {
            printf("PhysicalConfigDedicated:: field unpack failure\n");
            return -1;
        }
    }
    if(soundingRS_UL_ConfigDedicated_present)
    {
        if(0 != soundingRS_UL_ConfigDedicated.Unpack(bits, idx))
        {
            printf("PhysicalConfigDedicated:: field unpack failure\n");
            return -1;
        }
    }
    if(antennaInfo_present)
    {
        if(0 != antennaInfo_Unpack(bits, idx))
        {
            printf("PhysicalConfigDedicated:: field unpack failure\n");
            return -1;
        }
    }
    if(schedulingRequestConfig_present)
    {
        if(0 != schedulingRequestConfig.Unpack(bits, idx))
        {
            printf("PhysicalConfigDedicated:: field unpack failure\n");
            return -1;
        }
    }

    // Extension
    if(has_extension)
    {
        if((idx + 7) > bits.size())
        {
            printf("PhysicalConfigDedicated::Unpack() index out of bounds for extension size\n");
            return -1;
        }
        // Number of extension fields
        if(bits[idx++] != 0)
        {
            printf("PhysicalConfigDedicated:: Extension list size too large failure\n");
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
                printf("PhysicalConfigDedicated::Unpack() index out of bounds for optional indiator cqi_ReportConfig_v920\n");
                return -1;
            }
            cqi_ReportConfig_v920_present = bits[idx++];
        }
        if(opt_ind_count++ < N_ext_fields)
        {
            if((idx + 1) > bits.size())
            {
                printf("PhysicalConfigDedicated::Unpack() index out of bounds for optional indiator antennaInfo_v920\n");
                return -1;
            }
            antennaInfo_v920_present = bits[idx++];
        }
        if(opt_ind_count++ < N_ext_fields)
        {
            if((idx + 1) > bits.size())
            {
                printf("PhysicalConfigDedicated::Unpack() index out of bounds for optional indiator antennaInfo_r10\n");
                return -1;
            }
            antennaInfo_r10_present = bits[idx++];
        }
        if(opt_ind_count++ < N_ext_fields)
        {
            if((idx + 1) > bits.size())
            {
                printf("PhysicalConfigDedicated::Unpack() index out of bounds for optional indiator cif_Presence\n");
                return -1;
            }
            cif_Presence_present = bits[idx++];
        }
        if(opt_ind_count++ < N_ext_fields)
        {
            if((idx + 1) > bits.size())
            {
                printf("PhysicalConfigDedicated::Unpack() index out of bounds for optional indiator cqi_ReportConfig_v10x0\n");
                return -1;
            }
            cqi_ReportConfig_v10x0_present = bits[idx++];
        }
        if(opt_ind_count++ < N_ext_fields)
        {
            if((idx + 1) > bits.size())
            {
                printf("PhysicalConfigDedicated::Unpack() index out of bounds for optional indiator csi_RS_Config_r10\n");
                return -1;
            }
            csi_RS_Config_r10_present = bits[idx++];
        }
        if(opt_ind_count++ < N_ext_fields)
        {
            if((idx + 1) > bits.size())
            {
                printf("PhysicalConfigDedicated::Unpack() index out of bounds for optional indiator pucch_ConfigDedicated_v10x0\n");
                return -1;
            }
            pucch_ConfigDedicated_v10x0_present = bits[idx++];
        }
        if(opt_ind_count++ < N_ext_fields)
        {
            if((idx + 1) > bits.size())
            {
                printf("PhysicalConfigDedicated::Unpack() index out of bounds for optional indiator pusch_ConfigDedicated_v10x0\n");
                return -1;
            }
            pusch_ConfigDedicated_v10x0_present = bits[idx++];
        }
        if(opt_ind_count++ < N_ext_fields)
        {
            if((idx + 1) > bits.size())
            {
                printf("PhysicalConfigDedicated::Unpack() index out of bounds for optional indiator schedulingRequestConfig_v10x0\n");
                return -1;
            }
            schedulingRequestConfig_v10x0_present = bits[idx++];
        }
        if(opt_ind_count++ < N_ext_fields)
        {
            if((idx + 1) > bits.size())
            {
                printf("PhysicalConfigDedicated::Unpack() index out of bounds for optional indiator soundingRS_UL_ConfigDedicated_v10x0\n");
                return -1;
            }
            soundingRS_UL_ConfigDedicated_v10x0_present = bits[idx++];
        }
        if(opt_ind_count++ < N_ext_fields)
        {
            if((idx + 1) > bits.size())
            {
                printf("PhysicalConfigDedicated::Unpack() index out of bounds for optional indiator soundingRS_UL_ConfigDedicatedAperiodic_r10\n");
                return -1;
            }
            soundingRS_UL_ConfigDedicatedAperiodic_r10_present = bits[idx++];
        }
        if(opt_ind_count++ < N_ext_fields)
        {
            if((idx + 1) > bits.size())
            {
                printf("PhysicalConfigDedicated::Unpack() index out of bounds for optional indiator ul_AntennaInfo_r10\n");
                return -1;
            }
            ul_AntennaInfo_r10_present = bits[idx++];
        }
        if((idx + (N_ext_fields - opt_ind_count)) > bits.size())
        {
            printf("PhysicalConfigDedicated::Unpack() index out of bounds for extension optional indicators\n");
            return -1;
        }
        idx += (N_ext_fields - opt_ind_count);

        // Extension fields
        if(cqi_ReportConfig_v920_present)
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
            if(0 != cqi_ReportConfig_v920.Unpack(bits, idx))
            {
                printf("PhysicalConfigDedicated:: field unpack failure\n");
                return -1;
            }
            idx = orig_idx + (N_octets * 8);
        }
        if(antennaInfo_v920_present)
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
            if(0 != antennaInfo_v920.Unpack(bits, idx))
            {
                printf("PhysicalConfigDedicated:: field unpack failure\n");
                return -1;
            }
            idx = orig_idx + (N_octets * 8);
        }
        if(antennaInfo_r10_present)
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
            if(0 != antennaInfo_r10_Unpack(bits, idx))
            {
                printf("PhysicalConfigDedicated:: field unpack failure\n");
                return -1;
            }
            idx = orig_idx + (N_octets * 8);
        }
        if(cif_Presence_present)
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
            if(0 != cif_Presence_Unpack(bits, idx))
            {
                printf("PhysicalConfigDedicated:: field unpack failure\n");
                return -1;
            }
            idx = orig_idx + (N_octets * 8);
        }
        if(cqi_ReportConfig_v10x0_present)
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
            if(0 != cqi_ReportConfig_v10x0.Unpack(bits, idx))
            {
                printf("PhysicalConfigDedicated:: field unpack failure\n");
                return -1;
            }
            idx = orig_idx + (N_octets * 8);
        }
        if(csi_RS_Config_r10_present)
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
            if(0 != csi_RS_Config_r10.Unpack(bits, idx))
            {
                printf("PhysicalConfigDedicated:: field unpack failure\n");
                return -1;
            }
            idx = orig_idx + (N_octets * 8);
        }
        if(pucch_ConfigDedicated_v10x0_present)
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
            if(0 != pucch_ConfigDedicated_v10x0.Unpack(bits, idx))
            {
                printf("PhysicalConfigDedicated:: field unpack failure\n");
                return -1;
            }
            idx = orig_idx + (N_octets * 8);
        }
        if(pusch_ConfigDedicated_v10x0_present)
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
            if(0 != pusch_ConfigDedicated_v10x0.Unpack(bits, idx))
            {
                printf("PhysicalConfigDedicated:: field unpack failure\n");
                return -1;
            }
            idx = orig_idx + (N_octets * 8);
        }
        if(schedulingRequestConfig_v10x0_present)
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
            if(0 != schedulingRequestConfig_v10x0.Unpack(bits, idx))
            {
                printf("PhysicalConfigDedicated:: field unpack failure\n");
                return -1;
            }
            idx = orig_idx + (N_octets * 8);
        }
        if(soundingRS_UL_ConfigDedicated_v10x0_present)
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
            if(0 != soundingRS_UL_ConfigDedicated_v10x0.Unpack(bits, idx))
            {
                printf("PhysicalConfigDedicated:: field unpack failure\n");
                return -1;
            }
            idx = orig_idx + (N_octets * 8);
        }
        if(soundingRS_UL_ConfigDedicatedAperiodic_r10_present)
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
            if(0 != soundingRS_UL_ConfigDedicatedAperiodic_r10.Unpack(bits, idx))
            {
                printf("PhysicalConfigDedicated:: field unpack failure\n");
                return -1;
            }
            idx = orig_idx + (N_octets * 8);
        }
        if(ul_AntennaInfo_r10_present)
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
            if(0 != ul_AntennaInfo_r10.Unpack(bits, idx))
            {
                printf("PhysicalConfigDedicated:: field unpack failure\n");
                return -1;
            }
            idx = orig_idx + (N_octets * 8);
        }
        for(uint32_t i=12; i<N_ext_fields; i++)
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
            printf("PhysicalConfigDedicated::Unpack() index out of bounds for extension fields\n");
            return -1;
        }
            idx += N_octets * 8;
        }
    }
    return 0;
}

std::string PhysicalConfigDedicated::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "PhysicalConfigDedicated:\n";
    if(pdsch_ConfigDedicated_IsPresent())
        out += pdsch_ConfigDedicated_ToString(indent+1);
    if(pucch_ConfigDedicated_IsPresent())
        out += pucch_ConfigDedicated_ToString(indent+1);
    if(pusch_ConfigDedicated_IsPresent())
        out += pusch_ConfigDedicated_ToString(indent+1);
    if(uplinkPowerControlDedicated_IsPresent())
        out += uplinkPowerControlDedicated_ToString(indent+1);
    if(tpc_PDCCH_ConfigPUCCH_IsPresent())
        out += tpc_PDCCH_ConfigPUCCH_ToString(indent+1);
    if(tpc_PDCCH_ConfigPUSCH_IsPresent())
        out += tpc_PDCCH_ConfigPUSCH_ToString(indent+1);
    if(cqi_ReportConfig_IsPresent())
        out += cqi_ReportConfig_ToString(indent+1);
    if(soundingRS_UL_ConfigDedicated_IsPresent())
        out += soundingRS_UL_ConfigDedicated_ToString(indent+1);
    if(antennaInfo_IsPresent())
        out += antennaInfo_ToString(indent+1);
    if(schedulingRequestConfig_IsPresent())
        out += schedulingRequestConfig_ToString(indent+1);
    if(cqi_ReportConfig_v920_IsPresent())
        out += cqi_ReportConfig_v920_ToString(indent+1);
    if(antennaInfo_v920_IsPresent())
        out += antennaInfo_v920_ToString(indent+1);
    if(antennaInfo_r10_IsPresent())
        out += antennaInfo_r10_ToString(indent+1);
    if(cif_Presence_IsPresent())
        out += cif_Presence_ToString(indent+1);
    if(cqi_ReportConfig_v10x0_IsPresent())
        out += cqi_ReportConfig_v10x0_ToString(indent+1);
    if(csi_RS_Config_r10_IsPresent())
        out += csi_RS_Config_r10_ToString(indent+1);
    if(pucch_ConfigDedicated_v10x0_IsPresent())
        out += pucch_ConfigDedicated_v10x0_ToString(indent+1);
    if(pusch_ConfigDedicated_v10x0_IsPresent())
        out += pusch_ConfigDedicated_v10x0_ToString(indent+1);
    if(schedulingRequestConfig_v10x0_IsPresent())
        out += schedulingRequestConfig_v10x0_ToString(indent+1);
    if(soundingRS_UL_ConfigDedicated_v10x0_IsPresent())
        out += soundingRS_UL_ConfigDedicated_v10x0_ToString(indent+1);
    if(soundingRS_UL_ConfigDedicatedAperiodic_r10_IsPresent())
        out += soundingRS_UL_ConfigDedicatedAperiodic_r10_ToString(indent+1);
    if(ul_AntennaInfo_r10_IsPresent())
        out += ul_AntennaInfo_r10_ToString(indent+1);
    return out;
}

std::string PhysicalConfigDedicated::ToStringNoNewLines() const
{
    std::string out = "PhysicalConfigDedicated:";
    if(pdsch_ConfigDedicated_IsPresent())
        out += pdsch_ConfigDedicated_ToStringNoNewLines();
    if(pucch_ConfigDedicated_IsPresent())
        out += pucch_ConfigDedicated_ToStringNoNewLines();
    if(pusch_ConfigDedicated_IsPresent())
        out += pusch_ConfigDedicated_ToStringNoNewLines();
    if(uplinkPowerControlDedicated_IsPresent())
        out += uplinkPowerControlDedicated_ToStringNoNewLines();
    if(tpc_PDCCH_ConfigPUCCH_IsPresent())
        out += tpc_PDCCH_ConfigPUCCH_ToStringNoNewLines();
    if(tpc_PDCCH_ConfigPUSCH_IsPresent())
        out += tpc_PDCCH_ConfigPUSCH_ToStringNoNewLines();
    if(cqi_ReportConfig_IsPresent())
        out += cqi_ReportConfig_ToStringNoNewLines();
    if(soundingRS_UL_ConfigDedicated_IsPresent())
        out += soundingRS_UL_ConfigDedicated_ToStringNoNewLines();
    if(antennaInfo_IsPresent())
        out += antennaInfo_ToStringNoNewLines();
    if(schedulingRequestConfig_IsPresent())
        out += schedulingRequestConfig_ToStringNoNewLines();
    if(cqi_ReportConfig_v920_IsPresent())
        out += cqi_ReportConfig_v920_ToStringNoNewLines();
    if(antennaInfo_v920_IsPresent())
        out += antennaInfo_v920_ToStringNoNewLines();
    if(antennaInfo_r10_IsPresent())
        out += antennaInfo_r10_ToStringNoNewLines();
    if(cif_Presence_IsPresent())
        out += cif_Presence_ToStringNoNewLines();
    if(cqi_ReportConfig_v10x0_IsPresent())
        out += cqi_ReportConfig_v10x0_ToStringNoNewLines();
    if(csi_RS_Config_r10_IsPresent())
        out += csi_RS_Config_r10_ToStringNoNewLines();
    if(pucch_ConfigDedicated_v10x0_IsPresent())
        out += pucch_ConfigDedicated_v10x0_ToStringNoNewLines();
    if(pusch_ConfigDedicated_v10x0_IsPresent())
        out += pusch_ConfigDedicated_v10x0_ToStringNoNewLines();
    if(schedulingRequestConfig_v10x0_IsPresent())
        out += schedulingRequestConfig_v10x0_ToStringNoNewLines();
    if(soundingRS_UL_ConfigDedicated_v10x0_IsPresent())
        out += soundingRS_UL_ConfigDedicated_v10x0_ToStringNoNewLines();
    if(soundingRS_UL_ConfigDedicatedAperiodic_r10_IsPresent())
        out += soundingRS_UL_ConfigDedicatedAperiodic_r10_ToStringNoNewLines();
    if(ul_AntennaInfo_r10_IsPresent())
        out += ul_AntennaInfo_r10_ToStringNoNewLines();
    return out;
}

PDSCH_ConfigDedicated* PhysicalConfigDedicated::pdsch_ConfigDedicated_Set()
{
    pdsch_ConfigDedicated_present = true;
    return &pdsch_ConfigDedicated;
}

int PhysicalConfigDedicated::pdsch_ConfigDedicated_Set(PDSCH_ConfigDedicated &value)
{
    pdsch_ConfigDedicated_present = true;
    pdsch_ConfigDedicated = value;
    return 0;
}

const PDSCH_ConfigDedicated& PhysicalConfigDedicated::pdsch_ConfigDedicated_Get() const
{
    return pdsch_ConfigDedicated;
}

std::string PhysicalConfigDedicated::pdsch_ConfigDedicated_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "pdsch_ConfigDedicated:\n";
    out += pdsch_ConfigDedicated.ToString(indent+1);
    return out;
}

std::string PhysicalConfigDedicated::pdsch_ConfigDedicated_ToStringNoNewLines() const
{
    std::string out = "pdsch_ConfigDedicated:";
    out += pdsch_ConfigDedicated.ToStringNoNewLines();
    return out;
}

int PhysicalConfigDedicated::pdsch_ConfigDedicated_Clear()
{
    pdsch_ConfigDedicated_present = false;
    return 0;
}

bool PhysicalConfigDedicated::pdsch_ConfigDedicated_IsPresent() const
{
    return pdsch_ConfigDedicated_present;
}

PUCCH_ConfigDedicated* PhysicalConfigDedicated::pucch_ConfigDedicated_Set()
{
    pucch_ConfigDedicated_present = true;
    return &pucch_ConfigDedicated;
}

int PhysicalConfigDedicated::pucch_ConfigDedicated_Set(PUCCH_ConfigDedicated &value)
{
    pucch_ConfigDedicated_present = true;
    pucch_ConfigDedicated = value;
    return 0;
}

const PUCCH_ConfigDedicated& PhysicalConfigDedicated::pucch_ConfigDedicated_Get() const
{
    return pucch_ConfigDedicated;
}

std::string PhysicalConfigDedicated::pucch_ConfigDedicated_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "pucch_ConfigDedicated:\n";
    out += pucch_ConfigDedicated.ToString(indent+1);
    return out;
}

std::string PhysicalConfigDedicated::pucch_ConfigDedicated_ToStringNoNewLines() const
{
    std::string out = "pucch_ConfigDedicated:";
    out += pucch_ConfigDedicated.ToStringNoNewLines();
    return out;
}

int PhysicalConfigDedicated::pucch_ConfigDedicated_Clear()
{
    pucch_ConfigDedicated_present = false;
    return 0;
}

bool PhysicalConfigDedicated::pucch_ConfigDedicated_IsPresent() const
{
    return pucch_ConfigDedicated_present;
}

PUSCH_ConfigDedicated* PhysicalConfigDedicated::pusch_ConfigDedicated_Set()
{
    pusch_ConfigDedicated_present = true;
    return &pusch_ConfigDedicated;
}

int PhysicalConfigDedicated::pusch_ConfigDedicated_Set(PUSCH_ConfigDedicated &value)
{
    pusch_ConfigDedicated_present = true;
    pusch_ConfigDedicated = value;
    return 0;
}

const PUSCH_ConfigDedicated& PhysicalConfigDedicated::pusch_ConfigDedicated_Get() const
{
    return pusch_ConfigDedicated;
}

std::string PhysicalConfigDedicated::pusch_ConfigDedicated_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "pusch_ConfigDedicated:\n";
    out += pusch_ConfigDedicated.ToString(indent+1);
    return out;
}

std::string PhysicalConfigDedicated::pusch_ConfigDedicated_ToStringNoNewLines() const
{
    std::string out = "pusch_ConfigDedicated:";
    out += pusch_ConfigDedicated.ToStringNoNewLines();
    return out;
}

int PhysicalConfigDedicated::pusch_ConfigDedicated_Clear()
{
    pusch_ConfigDedicated_present = false;
    return 0;
}

bool PhysicalConfigDedicated::pusch_ConfigDedicated_IsPresent() const
{
    return pusch_ConfigDedicated_present;
}

UplinkPowerControlDedicated* PhysicalConfigDedicated::uplinkPowerControlDedicated_Set()
{
    uplinkPowerControlDedicated_present = true;
    return &uplinkPowerControlDedicated;
}

int PhysicalConfigDedicated::uplinkPowerControlDedicated_Set(UplinkPowerControlDedicated &value)
{
    uplinkPowerControlDedicated_present = true;
    uplinkPowerControlDedicated = value;
    return 0;
}

const UplinkPowerControlDedicated& PhysicalConfigDedicated::uplinkPowerControlDedicated_Get() const
{
    return uplinkPowerControlDedicated;
}

std::string PhysicalConfigDedicated::uplinkPowerControlDedicated_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "uplinkPowerControlDedicated:\n";
    out += uplinkPowerControlDedicated.ToString(indent+1);
    return out;
}

std::string PhysicalConfigDedicated::uplinkPowerControlDedicated_ToStringNoNewLines() const
{
    std::string out = "uplinkPowerControlDedicated:";
    out += uplinkPowerControlDedicated.ToStringNoNewLines();
    return out;
}

int PhysicalConfigDedicated::uplinkPowerControlDedicated_Clear()
{
    uplinkPowerControlDedicated_present = false;
    return 0;
}

bool PhysicalConfigDedicated::uplinkPowerControlDedicated_IsPresent() const
{
    return uplinkPowerControlDedicated_present;
}

TPC_PDCCH_Config* PhysicalConfigDedicated::tpc_PDCCH_ConfigPUCCH_Set()
{
    tpc_PDCCH_ConfigPUCCH_present = true;
    return &tpc_PDCCH_ConfigPUCCH;
}

int PhysicalConfigDedicated::tpc_PDCCH_ConfigPUCCH_Set(TPC_PDCCH_Config &value)
{
    tpc_PDCCH_ConfigPUCCH_present = true;
    tpc_PDCCH_ConfigPUCCH = value;
    return 0;
}

const TPC_PDCCH_Config& PhysicalConfigDedicated::tpc_PDCCH_ConfigPUCCH_Get() const
{
    return tpc_PDCCH_ConfigPUCCH;
}

std::string PhysicalConfigDedicated::tpc_PDCCH_ConfigPUCCH_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "tpc_PDCCH_ConfigPUCCH:\n";
    out += tpc_PDCCH_ConfigPUCCH.ToString(indent+1);
    return out;
}

std::string PhysicalConfigDedicated::tpc_PDCCH_ConfigPUCCH_ToStringNoNewLines() const
{
    std::string out = "tpc_PDCCH_ConfigPUCCH:";
    out += tpc_PDCCH_ConfigPUCCH.ToStringNoNewLines();
    return out;
}

int PhysicalConfigDedicated::tpc_PDCCH_ConfigPUCCH_Clear()
{
    tpc_PDCCH_ConfigPUCCH_present = false;
    return 0;
}

bool PhysicalConfigDedicated::tpc_PDCCH_ConfigPUCCH_IsPresent() const
{
    return tpc_PDCCH_ConfigPUCCH_present;
}

TPC_PDCCH_Config* PhysicalConfigDedicated::tpc_PDCCH_ConfigPUSCH_Set()
{
    tpc_PDCCH_ConfigPUSCH_present = true;
    return &tpc_PDCCH_ConfigPUSCH;
}

int PhysicalConfigDedicated::tpc_PDCCH_ConfigPUSCH_Set(TPC_PDCCH_Config &value)
{
    tpc_PDCCH_ConfigPUSCH_present = true;
    tpc_PDCCH_ConfigPUSCH = value;
    return 0;
}

const TPC_PDCCH_Config& PhysicalConfigDedicated::tpc_PDCCH_ConfigPUSCH_Get() const
{
    return tpc_PDCCH_ConfigPUSCH;
}

std::string PhysicalConfigDedicated::tpc_PDCCH_ConfigPUSCH_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "tpc_PDCCH_ConfigPUSCH:\n";
    out += tpc_PDCCH_ConfigPUSCH.ToString(indent+1);
    return out;
}

std::string PhysicalConfigDedicated::tpc_PDCCH_ConfigPUSCH_ToStringNoNewLines() const
{
    std::string out = "tpc_PDCCH_ConfigPUSCH:";
    out += tpc_PDCCH_ConfigPUSCH.ToStringNoNewLines();
    return out;
}

int PhysicalConfigDedicated::tpc_PDCCH_ConfigPUSCH_Clear()
{
    tpc_PDCCH_ConfigPUSCH_present = false;
    return 0;
}

bool PhysicalConfigDedicated::tpc_PDCCH_ConfigPUSCH_IsPresent() const
{
    return tpc_PDCCH_ConfigPUSCH_present;
}

CQI_ReportConfig* PhysicalConfigDedicated::cqi_ReportConfig_Set()
{
    cqi_ReportConfig_present = true;
    return &cqi_ReportConfig;
}

int PhysicalConfigDedicated::cqi_ReportConfig_Set(CQI_ReportConfig &value)
{
    cqi_ReportConfig_present = true;
    cqi_ReportConfig = value;
    return 0;
}

const CQI_ReportConfig& PhysicalConfigDedicated::cqi_ReportConfig_Get() const
{
    return cqi_ReportConfig;
}

std::string PhysicalConfigDedicated::cqi_ReportConfig_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cqi_ReportConfig:\n";
    out += cqi_ReportConfig.ToString(indent+1);
    return out;
}

std::string PhysicalConfigDedicated::cqi_ReportConfig_ToStringNoNewLines() const
{
    std::string out = "cqi_ReportConfig:";
    out += cqi_ReportConfig.ToStringNoNewLines();
    return out;
}

int PhysicalConfigDedicated::cqi_ReportConfig_Clear()
{
    cqi_ReportConfig_present = false;
    return 0;
}

bool PhysicalConfigDedicated::cqi_ReportConfig_IsPresent() const
{
    return cqi_ReportConfig_present;
}

SoundingRS_UL_ConfigDedicated* PhysicalConfigDedicated::soundingRS_UL_ConfigDedicated_Set()
{
    soundingRS_UL_ConfigDedicated_present = true;
    return &soundingRS_UL_ConfigDedicated;
}

int PhysicalConfigDedicated::soundingRS_UL_ConfigDedicated_Set(SoundingRS_UL_ConfigDedicated &value)
{
    soundingRS_UL_ConfigDedicated_present = true;
    soundingRS_UL_ConfigDedicated = value;
    return 0;
}

const SoundingRS_UL_ConfigDedicated& PhysicalConfigDedicated::soundingRS_UL_ConfigDedicated_Get() const
{
    return soundingRS_UL_ConfigDedicated;
}

std::string PhysicalConfigDedicated::soundingRS_UL_ConfigDedicated_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "soundingRS_UL_ConfigDedicated:\n";
    out += soundingRS_UL_ConfigDedicated.ToString(indent+1);
    return out;
}

std::string PhysicalConfigDedicated::soundingRS_UL_ConfigDedicated_ToStringNoNewLines() const
{
    std::string out = "soundingRS_UL_ConfigDedicated:";
    out += soundingRS_UL_ConfigDedicated.ToStringNoNewLines();
    return out;
}

int PhysicalConfigDedicated::soundingRS_UL_ConfigDedicated_Clear()
{
    soundingRS_UL_ConfigDedicated_present = false;
    return 0;
}

bool PhysicalConfigDedicated::soundingRS_UL_ConfigDedicated_IsPresent() const
{
    return soundingRS_UL_ConfigDedicated_present;
}

int PhysicalConfigDedicated::antennaInfo_Pack(std::vector<uint8_t> &bits)
{
    if(!antennaInfo_present)
    {
        printf("PhysicalConfigDedicated::antennaInfo_Pack() presence failure\n");
        return -1;
    }
    // Extension indicator

    // Choice
    for(uint32_t i=0; i<1; i++)
        bits.push_back((antennaInfo_internal_choice >> (1-i-1)) & 1);

    // Fields
    if(antennaInfo_internal_choice == k_antennaInfo_explicitValue)
    {
        if(0 != antennaInfo_explicitValue.Pack(bits))
        {
            printf("PhysicalConfigDedicated::antennaInfo_explicitValue pack failure\n");
            return -1;
        }
    }
    if(antennaInfo_internal_choice == k_antennaInfo_defaultValue)
    {
        if(0 != antennaInfo_defaultValue_Pack(bits))
        {
            printf("PhysicalConfigDedicated::antennaInfo_defaultValue pack failure\n");
            return -1;
        }
    }
    return 0;
}

int PhysicalConfigDedicated::antennaInfo_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return antennaInfo_Unpack(bits, idx);
}

int PhysicalConfigDedicated::antennaInfo_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 1) > bits.size())
    {
        printf("PhysicalConfigDedicated::antennaInfo_Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<1; i++)
        packed_val |= bits[idx++] << (1-i-1);

    if((PhysicalConfigDedicated::antennaInfo_Enum)packed_val > k_antennaInfo_defaultValue)
    {
        printf("PhysicalConfigDedicated::antennaInfo_Unpack() choice range failure\n");
        return -1;
    }
    antennaInfo_internal_choice = (PhysicalConfigDedicated::antennaInfo_Enum)packed_val;
    antennaInfo_present = true;

    // Fields
    if(antennaInfo_internal_choice == k_antennaInfo_explicitValue)
    {
        if(0 != antennaInfo_explicitValue.Unpack(bits, idx))
        {
            printf("PhysicalConfigDedicated::antennaInfo_explicitValue unpack failure\n");
            return -1;
        }
    }
    if(antennaInfo_internal_choice == k_antennaInfo_defaultValue)
    {
        if(0 != antennaInfo_defaultValue_Unpack(bits, idx))
        {
            printf("PhysicalConfigDedicated::antennaInfo_defaultValue unpack failure\n");
            return -1;
        }
    }
    return 0;
}

PhysicalConfigDedicated::antennaInfo_Enum PhysicalConfigDedicated::antennaInfo_Choice() const
{
    if(antennaInfo_present)
        return antennaInfo_internal_choice;
    return (PhysicalConfigDedicated::antennaInfo_Enum)0;
}

int PhysicalConfigDedicated::antennaInfo_SetChoice(PhysicalConfigDedicated::antennaInfo_Enum choice)
{
    antennaInfo_internal_choice = choice;
    antennaInfo_present = true;
    return 0;
}

std::string PhysicalConfigDedicated::antennaInfo_ChoiceToString(antennaInfo_Enum value) const
{
    if(k_antennaInfo_explicitValue == value)
        return "antennaInfo_explicitValue";
    if(k_antennaInfo_defaultValue == value)
        return "antennaInfo_defaultValue";
    return "";
}

uint64_t PhysicalConfigDedicated::antennaInfo_NumberOfChoices() const
{
    return 2;
}

std::string PhysicalConfigDedicated::antennaInfo_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "antennaInfo = " + antennaInfo_ChoiceToString(antennaInfo_internal_choice) + ":\n";
    if(antennaInfo_internal_choice == k_antennaInfo_explicitValue)
        out += antennaInfo_explicitValue.ToString(indent+1);
    return out;
}

std::string PhysicalConfigDedicated::antennaInfo_ToStringNoNewLines() const
{
    std::string out = "antennaInfo=" + antennaInfo_ChoiceToString(antennaInfo_internal_choice) + ",";
    if(antennaInfo_internal_choice == k_antennaInfo_explicitValue)
        out += antennaInfo_explicitValue.ToStringNoNewLines();
    return out;
}

int PhysicalConfigDedicated::antennaInfo_Clear()
{
    antennaInfo_present = false;
    return 0;
}

bool PhysicalConfigDedicated::antennaInfo_IsPresent() const
{
    return antennaInfo_present;
}

AntennaInfoDedicated* PhysicalConfigDedicated::antennaInfo_explicitValue_Set()
{
    antennaInfo_explicitValue_present = true;
    return &antennaInfo_explicitValue;
}

int PhysicalConfigDedicated::antennaInfo_explicitValue_Set(AntennaInfoDedicated &value)
{
    antennaInfo_explicitValue_present = true;
    antennaInfo_explicitValue = value;
    return 0;
}

const AntennaInfoDedicated& PhysicalConfigDedicated::antennaInfo_explicitValue_Get() const
{
    return antennaInfo_explicitValue;
}

std::string PhysicalConfigDedicated::antennaInfo_explicitValue_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "explicitValue:\n";
    out += antennaInfo_explicitValue.ToString(indent+1);
    return out;
}

std::string PhysicalConfigDedicated::antennaInfo_explicitValue_ToStringNoNewLines() const
{
    std::string out = "explicitValue:";
    out += antennaInfo_explicitValue.ToStringNoNewLines();
    return out;
}

int PhysicalConfigDedicated::antennaInfo_explicitValue_Clear()
{
    antennaInfo_explicitValue_present = false;
    return 0;
}

bool PhysicalConfigDedicated::antennaInfo_explicitValue_IsPresent() const
{
    return antennaInfo_explicitValue_present;
}

SchedulingRequestConfig* PhysicalConfigDedicated::schedulingRequestConfig_Set()
{
    schedulingRequestConfig_present = true;
    return &schedulingRequestConfig;
}

int PhysicalConfigDedicated::schedulingRequestConfig_Set(SchedulingRequestConfig &value)
{
    schedulingRequestConfig_present = true;
    schedulingRequestConfig = value;
    return 0;
}

const SchedulingRequestConfig& PhysicalConfigDedicated::schedulingRequestConfig_Get() const
{
    return schedulingRequestConfig;
}

std::string PhysicalConfigDedicated::schedulingRequestConfig_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "schedulingRequestConfig:\n";
    out += schedulingRequestConfig.ToString(indent+1);
    return out;
}

std::string PhysicalConfigDedicated::schedulingRequestConfig_ToStringNoNewLines() const
{
    std::string out = "schedulingRequestConfig:";
    out += schedulingRequestConfig.ToStringNoNewLines();
    return out;
}

int PhysicalConfigDedicated::schedulingRequestConfig_Clear()
{
    schedulingRequestConfig_present = false;
    return 0;
}

bool PhysicalConfigDedicated::schedulingRequestConfig_IsPresent() const
{
    return schedulingRequestConfig_present;
}

CQI_ReportConfig_v920* PhysicalConfigDedicated::cqi_ReportConfig_v920_Set()
{
    cqi_ReportConfig_v920_present = true;
    return &cqi_ReportConfig_v920;
}

int PhysicalConfigDedicated::cqi_ReportConfig_v920_Set(CQI_ReportConfig_v920 &value)
{
    cqi_ReportConfig_v920_present = true;
    cqi_ReportConfig_v920 = value;
    return 0;
}

const CQI_ReportConfig_v920& PhysicalConfigDedicated::cqi_ReportConfig_v920_Get() const
{
    return cqi_ReportConfig_v920;
}

std::string PhysicalConfigDedicated::cqi_ReportConfig_v920_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cqi_ReportConfig_v920:\n";
    out += cqi_ReportConfig_v920.ToString(indent+1);
    return out;
}

std::string PhysicalConfigDedicated::cqi_ReportConfig_v920_ToStringNoNewLines() const
{
    std::string out = "cqi_ReportConfig_v920:";
    out += cqi_ReportConfig_v920.ToStringNoNewLines();
    return out;
}

int PhysicalConfigDedicated::cqi_ReportConfig_v920_Clear()
{
    cqi_ReportConfig_v920_present = false;
    return 0;
}

bool PhysicalConfigDedicated::cqi_ReportConfig_v920_IsPresent() const
{
    return cqi_ReportConfig_v920_present;
}

AntennaInfoDedicated_v920* PhysicalConfigDedicated::antennaInfo_v920_Set()
{
    antennaInfo_v920_present = true;
    return &antennaInfo_v920;
}

int PhysicalConfigDedicated::antennaInfo_v920_Set(AntennaInfoDedicated_v920 &value)
{
    antennaInfo_v920_present = true;
    antennaInfo_v920 = value;
    return 0;
}

const AntennaInfoDedicated_v920& PhysicalConfigDedicated::antennaInfo_v920_Get() const
{
    return antennaInfo_v920;
}

std::string PhysicalConfigDedicated::antennaInfo_v920_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "antennaInfo_v920:\n";
    out += antennaInfo_v920.ToString(indent+1);
    return out;
}

std::string PhysicalConfigDedicated::antennaInfo_v920_ToStringNoNewLines() const
{
    std::string out = "antennaInfo_v920:";
    out += antennaInfo_v920.ToStringNoNewLines();
    return out;
}

int PhysicalConfigDedicated::antennaInfo_v920_Clear()
{
    antennaInfo_v920_present = false;
    return 0;
}

bool PhysicalConfigDedicated::antennaInfo_v920_IsPresent() const
{
    return antennaInfo_v920_present;
}

int PhysicalConfigDedicated::antennaInfo_r10_Pack(std::vector<uint8_t> &bits)
{
    if(!antennaInfo_r10_present)
    {
        printf("PhysicalConfigDedicated::antennaInfo_r10_Pack() presence failure\n");
        return -1;
    }
    // Extension indicator

    // Choice
    for(uint32_t i=0; i<1; i++)
        bits.push_back((antennaInfo_r10_internal_choice >> (1-i-1)) & 1);

    // Fields
    if(antennaInfo_r10_internal_choice == k_antennaInfo_r10_explicitValue)
    {
        if(0 != antennaInfo_r10_explicitValue.Pack(bits))
        {
            printf("PhysicalConfigDedicated::antennaInfo_r10_explicitValue pack failure\n");
            return -1;
        }
    }
    if(antennaInfo_r10_internal_choice == k_antennaInfo_r10_defaultValue)
    {
        if(0 != antennaInfo_r10_defaultValue_Pack(bits))
        {
            printf("PhysicalConfigDedicated::antennaInfo_r10_defaultValue pack failure\n");
            return -1;
        }
    }
    return 0;
}

int PhysicalConfigDedicated::antennaInfo_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return antennaInfo_r10_Unpack(bits, idx);
}

int PhysicalConfigDedicated::antennaInfo_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 1) > bits.size())
    {
        printf("PhysicalConfigDedicated::antennaInfo_r10_Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<1; i++)
        packed_val |= bits[idx++] << (1-i-1);

    if((PhysicalConfigDedicated::antennaInfo_r10_Enum)packed_val > k_antennaInfo_r10_defaultValue)
    {
        printf("PhysicalConfigDedicated::antennaInfo_r10_Unpack() choice range failure\n");
        return -1;
    }
    antennaInfo_r10_internal_choice = (PhysicalConfigDedicated::antennaInfo_r10_Enum)packed_val;
    antennaInfo_r10_present = true;

    // Fields
    if(antennaInfo_r10_internal_choice == k_antennaInfo_r10_explicitValue)
    {
        if(0 != antennaInfo_r10_explicitValue.Unpack(bits, idx))
        {
            printf("PhysicalConfigDedicated::antennaInfo_r10_explicitValue unpack failure\n");
            return -1;
        }
    }
    if(antennaInfo_r10_internal_choice == k_antennaInfo_r10_defaultValue)
    {
        if(0 != antennaInfo_r10_defaultValue_Unpack(bits, idx))
        {
            printf("PhysicalConfigDedicated::antennaInfo_r10_defaultValue unpack failure\n");
            return -1;
        }
    }
    return 0;
}

PhysicalConfigDedicated::antennaInfo_r10_Enum PhysicalConfigDedicated::antennaInfo_r10_Choice() const
{
    if(antennaInfo_r10_present)
        return antennaInfo_r10_internal_choice;
    return (PhysicalConfigDedicated::antennaInfo_r10_Enum)0;
}

int PhysicalConfigDedicated::antennaInfo_r10_SetChoice(PhysicalConfigDedicated::antennaInfo_r10_Enum choice)
{
    antennaInfo_r10_internal_choice = choice;
    antennaInfo_r10_present = true;
    return 0;
}

std::string PhysicalConfigDedicated::antennaInfo_r10_ChoiceToString(antennaInfo_r10_Enum value) const
{
    if(k_antennaInfo_r10_explicitValue == value)
        return "antennaInfo_r10_explicitValue";
    if(k_antennaInfo_r10_defaultValue == value)
        return "antennaInfo_r10_defaultValue";
    return "";
}

uint64_t PhysicalConfigDedicated::antennaInfo_r10_NumberOfChoices() const
{
    return 2;
}

std::string PhysicalConfigDedicated::antennaInfo_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "antennaInfo_r10 = " + antennaInfo_r10_ChoiceToString(antennaInfo_r10_internal_choice) + ":\n";
    if(antennaInfo_r10_internal_choice == k_antennaInfo_r10_explicitValue)
        out += antennaInfo_r10_explicitValue.ToString(indent+1);
    return out;
}

std::string PhysicalConfigDedicated::antennaInfo_r10_ToStringNoNewLines() const
{
    std::string out = "antennaInfo_r10=" + antennaInfo_r10_ChoiceToString(antennaInfo_r10_internal_choice) + ",";
    if(antennaInfo_r10_internal_choice == k_antennaInfo_r10_explicitValue)
        out += antennaInfo_r10_explicitValue.ToStringNoNewLines();
    return out;
}

int PhysicalConfigDedicated::antennaInfo_r10_Clear()
{
    antennaInfo_r10_present = false;
    return 0;
}

bool PhysicalConfigDedicated::antennaInfo_r10_IsPresent() const
{
    return antennaInfo_r10_present;
}

AntennaInfoDedicated_r10* PhysicalConfigDedicated::antennaInfo_r10_explicitValue_Set()
{
    antennaInfo_r10_explicitValue_present = true;
    return &antennaInfo_r10_explicitValue;
}

int PhysicalConfigDedicated::antennaInfo_r10_explicitValue_Set(AntennaInfoDedicated_r10 &value)
{
    antennaInfo_r10_explicitValue_present = true;
    antennaInfo_r10_explicitValue = value;
    return 0;
}

const AntennaInfoDedicated_r10& PhysicalConfigDedicated::antennaInfo_r10_explicitValue_Get() const
{
    return antennaInfo_r10_explicitValue;
}

std::string PhysicalConfigDedicated::antennaInfo_r10_explicitValue_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "explicitValue:\n";
    out += antennaInfo_r10_explicitValue.ToString(indent+1);
    return out;
}

std::string PhysicalConfigDedicated::antennaInfo_r10_explicitValue_ToStringNoNewLines() const
{
    std::string out = "explicitValue:";
    out += antennaInfo_r10_explicitValue.ToStringNoNewLines();
    return out;
}

int PhysicalConfigDedicated::antennaInfo_r10_explicitValue_Clear()
{
    antennaInfo_r10_explicitValue_present = false;
    return 0;
}

bool PhysicalConfigDedicated::antennaInfo_r10_explicitValue_IsPresent() const
{
    return antennaInfo_r10_explicitValue_present;
}

int PhysicalConfigDedicated::cif_Presence_Pack(std::vector<uint8_t> &bits)
{
    bits.push_back(cif_Presence_internal_value);
    return 0;
}

int PhysicalConfigDedicated::cif_Presence_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return cif_Presence_Unpack(bits, idx);
}

int PhysicalConfigDedicated::cif_Presence_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    if((idx + 1) > bits.size())
    {
        printf("PhysicalConfigDedicated::cif_Presence_Unpack() index out of bounds\n");
        return -1;
    }
    cif_Presence_internal_value = bits[idx++];
    cif_Presence_present = true;
    return 0;
}

bool PhysicalConfigDedicated::cif_Presence_Value() const
{
    if(cif_Presence_present)
        return cif_Presence_internal_value;
    return false;
}

int PhysicalConfigDedicated::cif_Presence_SetValue(bool value)
{
    cif_Presence_internal_value = value;
    cif_Presence_present = true;
    return 0;
}

std::string PhysicalConfigDedicated::cif_Presence_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cif_Presence = " + std::to_string(cif_Presence_internal_value) + "\n";
    return out;
}

std::string PhysicalConfigDedicated::cif_Presence_ToStringNoNewLines() const
{
    std::string out = "cif_Presence=" + std::to_string(cif_Presence_internal_value) + ",";
    return out;
}

int PhysicalConfigDedicated::cif_Presence_Clear()
{
    cif_Presence_present = false;
    return 0;
}

bool PhysicalConfigDedicated::cif_Presence_IsPresent() const
{
    return cif_Presence_present;
}

CQI_ReportConfig_v10x0* PhysicalConfigDedicated::cqi_ReportConfig_v10x0_Set()
{
    cqi_ReportConfig_v10x0_present = true;
    return &cqi_ReportConfig_v10x0;
}

int PhysicalConfigDedicated::cqi_ReportConfig_v10x0_Set(CQI_ReportConfig_v10x0 &value)
{
    cqi_ReportConfig_v10x0_present = true;
    cqi_ReportConfig_v10x0 = value;
    return 0;
}

const CQI_ReportConfig_v10x0& PhysicalConfigDedicated::cqi_ReportConfig_v10x0_Get() const
{
    return cqi_ReportConfig_v10x0;
}

std::string PhysicalConfigDedicated::cqi_ReportConfig_v10x0_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cqi_ReportConfig_v10x0:\n";
    out += cqi_ReportConfig_v10x0.ToString(indent+1);
    return out;
}

std::string PhysicalConfigDedicated::cqi_ReportConfig_v10x0_ToStringNoNewLines() const
{
    std::string out = "cqi_ReportConfig_v10x0:";
    out += cqi_ReportConfig_v10x0.ToStringNoNewLines();
    return out;
}

int PhysicalConfigDedicated::cqi_ReportConfig_v10x0_Clear()
{
    cqi_ReportConfig_v10x0_present = false;
    return 0;
}

bool PhysicalConfigDedicated::cqi_ReportConfig_v10x0_IsPresent() const
{
    return cqi_ReportConfig_v10x0_present;
}

CSI_RS_Config_r10* PhysicalConfigDedicated::csi_RS_Config_r10_Set()
{
    csi_RS_Config_r10_present = true;
    return &csi_RS_Config_r10;
}

int PhysicalConfigDedicated::csi_RS_Config_r10_Set(CSI_RS_Config_r10 &value)
{
    csi_RS_Config_r10_present = true;
    csi_RS_Config_r10 = value;
    return 0;
}

const CSI_RS_Config_r10& PhysicalConfigDedicated::csi_RS_Config_r10_Get() const
{
    return csi_RS_Config_r10;
}

std::string PhysicalConfigDedicated::csi_RS_Config_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "csi_RS_Config_r10:\n";
    out += csi_RS_Config_r10.ToString(indent+1);
    return out;
}

std::string PhysicalConfigDedicated::csi_RS_Config_r10_ToStringNoNewLines() const
{
    std::string out = "csi_RS_Config_r10:";
    out += csi_RS_Config_r10.ToStringNoNewLines();
    return out;
}

int PhysicalConfigDedicated::csi_RS_Config_r10_Clear()
{
    csi_RS_Config_r10_present = false;
    return 0;
}

bool PhysicalConfigDedicated::csi_RS_Config_r10_IsPresent() const
{
    return csi_RS_Config_r10_present;
}

PUCCH_ConfigDedicated_v10x0* PhysicalConfigDedicated::pucch_ConfigDedicated_v10x0_Set()
{
    pucch_ConfigDedicated_v10x0_present = true;
    return &pucch_ConfigDedicated_v10x0;
}

int PhysicalConfigDedicated::pucch_ConfigDedicated_v10x0_Set(PUCCH_ConfigDedicated_v10x0 &value)
{
    pucch_ConfigDedicated_v10x0_present = true;
    pucch_ConfigDedicated_v10x0 = value;
    return 0;
}

const PUCCH_ConfigDedicated_v10x0& PhysicalConfigDedicated::pucch_ConfigDedicated_v10x0_Get() const
{
    return pucch_ConfigDedicated_v10x0;
}

std::string PhysicalConfigDedicated::pucch_ConfigDedicated_v10x0_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "pucch_ConfigDedicated_v10x0:\n";
    out += pucch_ConfigDedicated_v10x0.ToString(indent+1);
    return out;
}

std::string PhysicalConfigDedicated::pucch_ConfigDedicated_v10x0_ToStringNoNewLines() const
{
    std::string out = "pucch_ConfigDedicated_v10x0:";
    out += pucch_ConfigDedicated_v10x0.ToStringNoNewLines();
    return out;
}

int PhysicalConfigDedicated::pucch_ConfigDedicated_v10x0_Clear()
{
    pucch_ConfigDedicated_v10x0_present = false;
    return 0;
}

bool PhysicalConfigDedicated::pucch_ConfigDedicated_v10x0_IsPresent() const
{
    return pucch_ConfigDedicated_v10x0_present;
}

PUSCH_ConfigDedicated_v10x0* PhysicalConfigDedicated::pusch_ConfigDedicated_v10x0_Set()
{
    pusch_ConfigDedicated_v10x0_present = true;
    return &pusch_ConfigDedicated_v10x0;
}

int PhysicalConfigDedicated::pusch_ConfigDedicated_v10x0_Set(PUSCH_ConfigDedicated_v10x0 &value)
{
    pusch_ConfigDedicated_v10x0_present = true;
    pusch_ConfigDedicated_v10x0 = value;
    return 0;
}

const PUSCH_ConfigDedicated_v10x0& PhysicalConfigDedicated::pusch_ConfigDedicated_v10x0_Get() const
{
    return pusch_ConfigDedicated_v10x0;
}

std::string PhysicalConfigDedicated::pusch_ConfigDedicated_v10x0_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "pusch_ConfigDedicated_v10x0:\n";
    out += pusch_ConfigDedicated_v10x0.ToString(indent+1);
    return out;
}

std::string PhysicalConfigDedicated::pusch_ConfigDedicated_v10x0_ToStringNoNewLines() const
{
    std::string out = "pusch_ConfigDedicated_v10x0:";
    out += pusch_ConfigDedicated_v10x0.ToStringNoNewLines();
    return out;
}

int PhysicalConfigDedicated::pusch_ConfigDedicated_v10x0_Clear()
{
    pusch_ConfigDedicated_v10x0_present = false;
    return 0;
}

bool PhysicalConfigDedicated::pusch_ConfigDedicated_v10x0_IsPresent() const
{
    return pusch_ConfigDedicated_v10x0_present;
}

SchedulingRequestConfig_v10x0* PhysicalConfigDedicated::schedulingRequestConfig_v10x0_Set()
{
    schedulingRequestConfig_v10x0_present = true;
    return &schedulingRequestConfig_v10x0;
}

int PhysicalConfigDedicated::schedulingRequestConfig_v10x0_Set(SchedulingRequestConfig_v10x0 &value)
{
    schedulingRequestConfig_v10x0_present = true;
    schedulingRequestConfig_v10x0 = value;
    return 0;
}

const SchedulingRequestConfig_v10x0& PhysicalConfigDedicated::schedulingRequestConfig_v10x0_Get() const
{
    return schedulingRequestConfig_v10x0;
}

std::string PhysicalConfigDedicated::schedulingRequestConfig_v10x0_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "schedulingRequestConfig_v10x0:\n";
    out += schedulingRequestConfig_v10x0.ToString(indent+1);
    return out;
}

std::string PhysicalConfigDedicated::schedulingRequestConfig_v10x0_ToStringNoNewLines() const
{
    std::string out = "schedulingRequestConfig_v10x0:";
    out += schedulingRequestConfig_v10x0.ToStringNoNewLines();
    return out;
}

int PhysicalConfigDedicated::schedulingRequestConfig_v10x0_Clear()
{
    schedulingRequestConfig_v10x0_present = false;
    return 0;
}

bool PhysicalConfigDedicated::schedulingRequestConfig_v10x0_IsPresent() const
{
    return schedulingRequestConfig_v10x0_present;
}

SoundingRS_UL_ConfigDedicated_v10x0* PhysicalConfigDedicated::soundingRS_UL_ConfigDedicated_v10x0_Set()
{
    soundingRS_UL_ConfigDedicated_v10x0_present = true;
    return &soundingRS_UL_ConfigDedicated_v10x0;
}

int PhysicalConfigDedicated::soundingRS_UL_ConfigDedicated_v10x0_Set(SoundingRS_UL_ConfigDedicated_v10x0 &value)
{
    soundingRS_UL_ConfigDedicated_v10x0_present = true;
    soundingRS_UL_ConfigDedicated_v10x0 = value;
    return 0;
}

const SoundingRS_UL_ConfigDedicated_v10x0& PhysicalConfigDedicated::soundingRS_UL_ConfigDedicated_v10x0_Get() const
{
    return soundingRS_UL_ConfigDedicated_v10x0;
}

std::string PhysicalConfigDedicated::soundingRS_UL_ConfigDedicated_v10x0_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "soundingRS_UL_ConfigDedicated_v10x0:\n";
    out += soundingRS_UL_ConfigDedicated_v10x0.ToString(indent+1);
    return out;
}

std::string PhysicalConfigDedicated::soundingRS_UL_ConfigDedicated_v10x0_ToStringNoNewLines() const
{
    std::string out = "soundingRS_UL_ConfigDedicated_v10x0:";
    out += soundingRS_UL_ConfigDedicated_v10x0.ToStringNoNewLines();
    return out;
}

int PhysicalConfigDedicated::soundingRS_UL_ConfigDedicated_v10x0_Clear()
{
    soundingRS_UL_ConfigDedicated_v10x0_present = false;
    return 0;
}

bool PhysicalConfigDedicated::soundingRS_UL_ConfigDedicated_v10x0_IsPresent() const
{
    return soundingRS_UL_ConfigDedicated_v10x0_present;
}

SoundingRS_UL_ConfigDedicatedAperiodic_r10* PhysicalConfigDedicated::soundingRS_UL_ConfigDedicatedAperiodic_r10_Set()
{
    soundingRS_UL_ConfigDedicatedAperiodic_r10_present = true;
    return &soundingRS_UL_ConfigDedicatedAperiodic_r10;
}

int PhysicalConfigDedicated::soundingRS_UL_ConfigDedicatedAperiodic_r10_Set(SoundingRS_UL_ConfigDedicatedAperiodic_r10 &value)
{
    soundingRS_UL_ConfigDedicatedAperiodic_r10_present = true;
    soundingRS_UL_ConfigDedicatedAperiodic_r10 = value;
    return 0;
}

const SoundingRS_UL_ConfigDedicatedAperiodic_r10& PhysicalConfigDedicated::soundingRS_UL_ConfigDedicatedAperiodic_r10_Get() const
{
    return soundingRS_UL_ConfigDedicatedAperiodic_r10;
}

std::string PhysicalConfigDedicated::soundingRS_UL_ConfigDedicatedAperiodic_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "soundingRS_UL_ConfigDedicatedAperiodic_r10:\n";
    out += soundingRS_UL_ConfigDedicatedAperiodic_r10.ToString(indent+1);
    return out;
}

std::string PhysicalConfigDedicated::soundingRS_UL_ConfigDedicatedAperiodic_r10_ToStringNoNewLines() const
{
    std::string out = "soundingRS_UL_ConfigDedicatedAperiodic_r10:";
    out += soundingRS_UL_ConfigDedicatedAperiodic_r10.ToStringNoNewLines();
    return out;
}

int PhysicalConfigDedicated::soundingRS_UL_ConfigDedicatedAperiodic_r10_Clear()
{
    soundingRS_UL_ConfigDedicatedAperiodic_r10_present = false;
    return 0;
}

bool PhysicalConfigDedicated::soundingRS_UL_ConfigDedicatedAperiodic_r10_IsPresent() const
{
    return soundingRS_UL_ConfigDedicatedAperiodic_r10_present;
}

UL_AntennaInfo_r10* PhysicalConfigDedicated::ul_AntennaInfo_r10_Set()
{
    ul_AntennaInfo_r10_present = true;
    return &ul_AntennaInfo_r10;
}

int PhysicalConfigDedicated::ul_AntennaInfo_r10_Set(UL_AntennaInfo_r10 &value)
{
    ul_AntennaInfo_r10_present = true;
    ul_AntennaInfo_r10 = value;
    return 0;
}

const UL_AntennaInfo_r10& PhysicalConfigDedicated::ul_AntennaInfo_r10_Get() const
{
    return ul_AntennaInfo_r10;
}

std::string PhysicalConfigDedicated::ul_AntennaInfo_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ul_AntennaInfo_r10:\n";
    out += ul_AntennaInfo_r10.ToString(indent+1);
    return out;
}

std::string PhysicalConfigDedicated::ul_AntennaInfo_r10_ToStringNoNewLines() const
{
    std::string out = "ul_AntennaInfo_r10:";
    out += ul_AntennaInfo_r10.ToStringNoNewLines();
    return out;
}

int PhysicalConfigDedicated::ul_AntennaInfo_r10_Clear()
{
    ul_AntennaInfo_r10_present = false;
    return 0;
}

bool PhysicalConfigDedicated::ul_AntennaInfo_r10_IsPresent() const
{
    return ul_AntennaInfo_r10_present;
}

