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

#include "AS_Config.h"

#include <cmath>

int AS_Config::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator
    bool has_extension = false;
    if(sourceSystemInformationBlockType1Ext_IsPresent() || sourceOtherConfig_r9_IsPresent() || sourceSCellConfigList_r10_IsPresent())
    {
        bits.push_back(1);
        has_extension = true;
    }else{
        bits.push_back(0);
    }

    // Optional indicators

    // Fields
    {
        if(0 != sourceMeasConfig.Pack(bits))
        {
            printf("AS_Config:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != sourceRadioResourceConfig.Pack(bits))
        {
            printf("AS_Config:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != sourceSecurityAlgorithmConfig.Pack(bits))
        {
            printf("AS_Config:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != sourceUE_Identity.Pack(bits))
        {
            printf("AS_Config:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != sourceMasterInformationBlock.Pack(bits))
        {
            printf("AS_Config:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != sourceSystemInformationBlockType1.Pack(bits))
        {
            printf("AS_Config:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != sourceSystemInformationBlockType2.Pack(bits))
        {
            printf("AS_Config:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != antennaInfoCommon.Pack(bits))
        {
            printf("AS_Config:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != sourceDl_CarrierFreq.Pack(bits))
        {
            printf("AS_Config:: field pack failure\n");
            return -1;
        }
    }

    // Extension
    if(has_extension)
    {
        // Number of extension fields
        if(2 < 64)
        {
            bits.push_back(0);
            for(uint32_t i=0; i<6; i++)
                bits.push_back((2 >> (6-i-1)) & 1);
        }else{
            printf("AS_Config:: Extension list size too large failure\n");
            return -1;
        }

        // Extension field presence indicators
        bits.push_back(sourceSystemInformationBlockType1Ext_IsPresent());
        bits.push_back(sourceSCellConfigList_r10_IsPresent());

        // Extension fields
        if(sourceSystemInformationBlockType1Ext_IsPresent())
        {
            std::vector<uint8_t> field_bits;
            if(0 != sourceSystemInformationBlockType1Ext_Pack(field_bits))
            {
                printf("AS_Config:: field pack failure\n");
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
        {
            std::vector<uint8_t> field_bits;
            if(0 != sourceOtherConfig_r9.Pack(field_bits))
            {
                printf("AS_Config:: field pack failure\n");
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
        if(sourceSCellConfigList_r10_IsPresent())
        {
            std::vector<uint8_t> field_bits;
            if(0 != sourceSCellConfigList_r10.Pack(field_bits))
            {
                printf("AS_Config:: field pack failure\n");
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

int AS_Config::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int AS_Config::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("AS_Config::Unpack() index out of bounds for extension\n");
        return -1;
    }
    bool has_extension = bits[idx++];

    // Optional indicators

    // Fields
    {
        if(0 != sourceMeasConfig.Unpack(bits, idx))
        {
            printf("AS_Config:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != sourceRadioResourceConfig.Unpack(bits, idx))
        {
            printf("AS_Config:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != sourceSecurityAlgorithmConfig.Unpack(bits, idx))
        {
            printf("AS_Config:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != sourceUE_Identity.Unpack(bits, idx))
        {
            printf("AS_Config:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != sourceMasterInformationBlock.Unpack(bits, idx))
        {
            printf("AS_Config:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != sourceSystemInformationBlockType1.Unpack(bits, idx))
        {
            printf("AS_Config:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != sourceSystemInformationBlockType2.Unpack(bits, idx))
        {
            printf("AS_Config:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != antennaInfoCommon.Unpack(bits, idx))
        {
            printf("AS_Config:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != sourceDl_CarrierFreq.Unpack(bits, idx))
        {
            printf("AS_Config:: field unpack failure\n");
            return -1;
        }
    }

    // Extension
    if(has_extension)
    {
        if((idx + 7) > bits.size())
        {
            printf("AS_Config::Unpack() index out of bounds for extension size\n");
            return -1;
        }
        // Number of extension fields
        if(bits[idx++] != 0)
        {
            printf("AS_Config:: Extension list size too large failure\n");
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
                printf("AS_Config::Unpack() index out of bounds for optional indiator sourceSystemInformationBlockType1Ext\n");
                return -1;
            }
            sourceSystemInformationBlockType1Ext_present = bits[idx++];
        }
        if(opt_ind_count++ < N_ext_fields)
        {
        }
        if(opt_ind_count++ < N_ext_fields)
        {
            if((idx + 1) > bits.size())
            {
                printf("AS_Config::Unpack() index out of bounds for optional indiator sourceSCellConfigList_r10\n");
                return -1;
            }
            sourceSCellConfigList_r10_present = bits[idx++];
        }
        if((idx + (N_ext_fields - opt_ind_count)) > bits.size())
        {
            printf("AS_Config::Unpack() index out of bounds for extension optional indicators\n");
            return -1;
        }
        idx += (N_ext_fields - opt_ind_count);

        // Extension fields
        if(sourceSystemInformationBlockType1Ext_present)
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
            if(0 != sourceSystemInformationBlockType1Ext_Unpack(bits, idx))
            {
                printf("AS_Config:: field unpack failure\n");
                return -1;
            }
            idx = orig_idx + (N_octets * 8);
        }
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
            if(0 != sourceOtherConfig_r9.Unpack(bits, idx))
            {
                printf("AS_Config:: field unpack failure\n");
                return -1;
            }
            idx = orig_idx + (N_octets * 8);
        }
        if(sourceSCellConfigList_r10_present)
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
            if(0 != sourceSCellConfigList_r10.Unpack(bits, idx))
            {
                printf("AS_Config:: field unpack failure\n");
                return -1;
            }
            idx = orig_idx + (N_octets * 8);
        }
        for(uint32_t i=3; i<N_ext_fields; i++)
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
            printf("AS_Config::Unpack() index out of bounds for extension fields\n");
            return -1;
        }
            idx += N_octets * 8;
        }
    }
    return 0;
}

std::string AS_Config::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "AS_Config:\n";
    out += sourceMeasConfig_ToString(indent+1);
    out += sourceRadioResourceConfig_ToString(indent+1);
    out += sourceSecurityAlgorithmConfig_ToString(indent+1);
    out += sourceUE_Identity_ToString(indent+1);
    out += sourceMasterInformationBlock_ToString(indent+1);
    out += sourceSystemInformationBlockType1_ToString(indent+1);
    out += sourceSystemInformationBlockType2_ToString(indent+1);
    out += antennaInfoCommon_ToString(indent+1);
    out += sourceDl_CarrierFreq_ToString(indent+1);
    if(sourceSystemInformationBlockType1Ext_IsPresent())
        out += sourceSystemInformationBlockType1Ext_ToString(indent+1);
    out += sourceOtherConfig_r9_ToString(indent+1);
    if(sourceSCellConfigList_r10_IsPresent())
        out += sourceSCellConfigList_r10_ToString(indent+1);
    return out;
}

std::string AS_Config::ToStringNoNewLines() const
{
    std::string out = "AS_Config:";
    out += sourceMeasConfig_ToStringNoNewLines();
    out += sourceRadioResourceConfig_ToStringNoNewLines();
    out += sourceSecurityAlgorithmConfig_ToStringNoNewLines();
    out += sourceUE_Identity_ToStringNoNewLines();
    out += sourceMasterInformationBlock_ToStringNoNewLines();
    out += sourceSystemInformationBlockType1_ToStringNoNewLines();
    out += sourceSystemInformationBlockType2_ToStringNoNewLines();
    out += antennaInfoCommon_ToStringNoNewLines();
    out += sourceDl_CarrierFreq_ToStringNoNewLines();
    if(sourceSystemInformationBlockType1Ext_IsPresent())
        out += sourceSystemInformationBlockType1Ext_ToStringNoNewLines();
    out += sourceOtherConfig_r9_ToStringNoNewLines();
    if(sourceSCellConfigList_r10_IsPresent())
        out += sourceSCellConfigList_r10_ToStringNoNewLines();
    return out;
}

MeasConfig* AS_Config::sourceMeasConfig_Set()
{
    sourceMeasConfig_present = true;
    return &sourceMeasConfig;
}

int AS_Config::sourceMeasConfig_Set(MeasConfig &value)
{
    sourceMeasConfig_present = true;
    sourceMeasConfig = value;
    return 0;
}

const MeasConfig& AS_Config::sourceMeasConfig_Get() const
{
    return sourceMeasConfig;
}

std::string AS_Config::sourceMeasConfig_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "sourceMeasConfig:\n";
    out += sourceMeasConfig.ToString(indent+1);
    return out;
}

std::string AS_Config::sourceMeasConfig_ToStringNoNewLines() const
{
    std::string out = "sourceMeasConfig:";
    out += sourceMeasConfig.ToStringNoNewLines();
    return out;
}

int AS_Config::sourceMeasConfig_Clear()
{
    sourceMeasConfig_present = false;
    return 0;
}

bool AS_Config::sourceMeasConfig_IsPresent() const
{
    return sourceMeasConfig_present;
}

RadioResourceConfigDedicated* AS_Config::sourceRadioResourceConfig_Set()
{
    sourceRadioResourceConfig_present = true;
    return &sourceRadioResourceConfig;
}

int AS_Config::sourceRadioResourceConfig_Set(RadioResourceConfigDedicated &value)
{
    sourceRadioResourceConfig_present = true;
    sourceRadioResourceConfig = value;
    return 0;
}

const RadioResourceConfigDedicated& AS_Config::sourceRadioResourceConfig_Get() const
{
    return sourceRadioResourceConfig;
}

std::string AS_Config::sourceRadioResourceConfig_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "sourceRadioResourceConfig:\n";
    out += sourceRadioResourceConfig.ToString(indent+1);
    return out;
}

std::string AS_Config::sourceRadioResourceConfig_ToStringNoNewLines() const
{
    std::string out = "sourceRadioResourceConfig:";
    out += sourceRadioResourceConfig.ToStringNoNewLines();
    return out;
}

int AS_Config::sourceRadioResourceConfig_Clear()
{
    sourceRadioResourceConfig_present = false;
    return 0;
}

bool AS_Config::sourceRadioResourceConfig_IsPresent() const
{
    return sourceRadioResourceConfig_present;
}

SecurityAlgorithmConfig* AS_Config::sourceSecurityAlgorithmConfig_Set()
{
    sourceSecurityAlgorithmConfig_present = true;
    return &sourceSecurityAlgorithmConfig;
}

int AS_Config::sourceSecurityAlgorithmConfig_Set(SecurityAlgorithmConfig &value)
{
    sourceSecurityAlgorithmConfig_present = true;
    sourceSecurityAlgorithmConfig = value;
    return 0;
}

const SecurityAlgorithmConfig& AS_Config::sourceSecurityAlgorithmConfig_Get() const
{
    return sourceSecurityAlgorithmConfig;
}

std::string AS_Config::sourceSecurityAlgorithmConfig_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "sourceSecurityAlgorithmConfig:\n";
    out += sourceSecurityAlgorithmConfig.ToString(indent+1);
    return out;
}

std::string AS_Config::sourceSecurityAlgorithmConfig_ToStringNoNewLines() const
{
    std::string out = "sourceSecurityAlgorithmConfig:";
    out += sourceSecurityAlgorithmConfig.ToStringNoNewLines();
    return out;
}

int AS_Config::sourceSecurityAlgorithmConfig_Clear()
{
    sourceSecurityAlgorithmConfig_present = false;
    return 0;
}

bool AS_Config::sourceSecurityAlgorithmConfig_IsPresent() const
{
    return sourceSecurityAlgorithmConfig_present;
}

C_RNTI* AS_Config::sourceUE_Identity_Set()
{
    sourceUE_Identity_present = true;
    return &sourceUE_Identity;
}

int AS_Config::sourceUE_Identity_Set(C_RNTI &value)
{
    sourceUE_Identity_present = true;
    sourceUE_Identity = value;
    return 0;
}

const C_RNTI& AS_Config::sourceUE_Identity_Get() const
{
    return sourceUE_Identity;
}

std::string AS_Config::sourceUE_Identity_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "sourceUE_Identity:\n";
    out += sourceUE_Identity.ToString(indent+1);
    return out;
}

std::string AS_Config::sourceUE_Identity_ToStringNoNewLines() const
{
    std::string out = "sourceUE_Identity:";
    out += sourceUE_Identity.ToStringNoNewLines();
    return out;
}

int AS_Config::sourceUE_Identity_Clear()
{
    sourceUE_Identity_present = false;
    return 0;
}

bool AS_Config::sourceUE_Identity_IsPresent() const
{
    return sourceUE_Identity_present;
}

MasterInformationBlock* AS_Config::sourceMasterInformationBlock_Set()
{
    sourceMasterInformationBlock_present = true;
    return &sourceMasterInformationBlock;
}

int AS_Config::sourceMasterInformationBlock_Set(MasterInformationBlock &value)
{
    sourceMasterInformationBlock_present = true;
    sourceMasterInformationBlock = value;
    return 0;
}

const MasterInformationBlock& AS_Config::sourceMasterInformationBlock_Get() const
{
    return sourceMasterInformationBlock;
}

std::string AS_Config::sourceMasterInformationBlock_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "sourceMasterInformationBlock:\n";
    out += sourceMasterInformationBlock.ToString(indent+1);
    return out;
}

std::string AS_Config::sourceMasterInformationBlock_ToStringNoNewLines() const
{
    std::string out = "sourceMasterInformationBlock:";
    out += sourceMasterInformationBlock.ToStringNoNewLines();
    return out;
}

int AS_Config::sourceMasterInformationBlock_Clear()
{
    sourceMasterInformationBlock_present = false;
    return 0;
}

bool AS_Config::sourceMasterInformationBlock_IsPresent() const
{
    return sourceMasterInformationBlock_present;
}

SystemInformationBlockType1* AS_Config::sourceSystemInformationBlockType1_Set()
{
    sourceSystemInformationBlockType1_present = true;
    return &sourceSystemInformationBlockType1;
}

int AS_Config::sourceSystemInformationBlockType1_Set(SystemInformationBlockType1 &value)
{
    sourceSystemInformationBlockType1_present = true;
    sourceSystemInformationBlockType1 = value;
    return 0;
}

const SystemInformationBlockType1& AS_Config::sourceSystemInformationBlockType1_Get() const
{
    return sourceSystemInformationBlockType1;
}

std::string AS_Config::sourceSystemInformationBlockType1_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "sourceSystemInformationBlockType1:\n";
    out += sourceSystemInformationBlockType1.ToString(indent+1);
    return out;
}

std::string AS_Config::sourceSystemInformationBlockType1_ToStringNoNewLines() const
{
    std::string out = "sourceSystemInformationBlockType1:";
    out += sourceSystemInformationBlockType1.ToStringNoNewLines();
    return out;
}

int AS_Config::sourceSystemInformationBlockType1_Clear()
{
    sourceSystemInformationBlockType1_present = false;
    return 0;
}

bool AS_Config::sourceSystemInformationBlockType1_IsPresent() const
{
    return sourceSystemInformationBlockType1_present;
}

SystemInformationBlockType2* AS_Config::sourceSystemInformationBlockType2_Set()
{
    sourceSystemInformationBlockType2_present = true;
    return &sourceSystemInformationBlockType2;
}

int AS_Config::sourceSystemInformationBlockType2_Set(SystemInformationBlockType2 &value)
{
    sourceSystemInformationBlockType2_present = true;
    sourceSystemInformationBlockType2 = value;
    return 0;
}

const SystemInformationBlockType2& AS_Config::sourceSystemInformationBlockType2_Get() const
{
    return sourceSystemInformationBlockType2;
}

std::string AS_Config::sourceSystemInformationBlockType2_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "sourceSystemInformationBlockType2:\n";
    out += sourceSystemInformationBlockType2.ToString(indent+1);
    return out;
}

std::string AS_Config::sourceSystemInformationBlockType2_ToStringNoNewLines() const
{
    std::string out = "sourceSystemInformationBlockType2:";
    out += sourceSystemInformationBlockType2.ToStringNoNewLines();
    return out;
}

int AS_Config::sourceSystemInformationBlockType2_Clear()
{
    sourceSystemInformationBlockType2_present = false;
    return 0;
}

bool AS_Config::sourceSystemInformationBlockType2_IsPresent() const
{
    return sourceSystemInformationBlockType2_present;
}

AntennaInfoCommon* AS_Config::antennaInfoCommon_Set()
{
    antennaInfoCommon_present = true;
    return &antennaInfoCommon;
}

int AS_Config::antennaInfoCommon_Set(AntennaInfoCommon &value)
{
    antennaInfoCommon_present = true;
    antennaInfoCommon = value;
    return 0;
}

const AntennaInfoCommon& AS_Config::antennaInfoCommon_Get() const
{
    return antennaInfoCommon;
}

std::string AS_Config::antennaInfoCommon_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "antennaInfoCommon:\n";
    out += antennaInfoCommon.ToString(indent+1);
    return out;
}

std::string AS_Config::antennaInfoCommon_ToStringNoNewLines() const
{
    std::string out = "antennaInfoCommon:";
    out += antennaInfoCommon.ToStringNoNewLines();
    return out;
}

int AS_Config::antennaInfoCommon_Clear()
{
    antennaInfoCommon_present = false;
    return 0;
}

bool AS_Config::antennaInfoCommon_IsPresent() const
{
    return antennaInfoCommon_present;
}

ARFCN_ValueEUTRA* AS_Config::sourceDl_CarrierFreq_Set()
{
    sourceDl_CarrierFreq_present = true;
    return &sourceDl_CarrierFreq;
}

int AS_Config::sourceDl_CarrierFreq_Set(ARFCN_ValueEUTRA &value)
{
    sourceDl_CarrierFreq_present = true;
    sourceDl_CarrierFreq = value;
    return 0;
}

const ARFCN_ValueEUTRA& AS_Config::sourceDl_CarrierFreq_Get() const
{
    return sourceDl_CarrierFreq;
}

std::string AS_Config::sourceDl_CarrierFreq_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "sourceDl_CarrierFreq:\n";
    out += sourceDl_CarrierFreq.ToString(indent+1);
    return out;
}

std::string AS_Config::sourceDl_CarrierFreq_ToStringNoNewLines() const
{
    std::string out = "sourceDl_CarrierFreq:";
    out += sourceDl_CarrierFreq.ToStringNoNewLines();
    return out;
}

int AS_Config::sourceDl_CarrierFreq_Clear()
{
    sourceDl_CarrierFreq_present = false;
    return 0;
}

bool AS_Config::sourceDl_CarrierFreq_IsPresent() const
{
    return sourceDl_CarrierFreq_present;
}

int AS_Config::sourceSystemInformationBlockType1Ext_Pack(std::vector<uint8_t> &bits)
{
    uint32_t local_size_length = 0;
    uint32_t local_size = sourceSystemInformationBlockType1Ext_internal_value.size();
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
    for(uint32_t i=0; i<sourceSystemInformationBlockType1Ext_internal_value.size(); i++)
        for(uint32_t j=0; j<8; j++)
            bits.push_back((sourceSystemInformationBlockType1Ext_internal_value[i] >> (8-j-1)) & 1);
    return 0;
}

int AS_Config::sourceSystemInformationBlockType1Ext_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return sourceSystemInformationBlockType1Ext_Unpack(bits, idx);
}

int AS_Config::sourceSystemInformationBlockType1Ext_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t local_size_length = 0;
    uint32_t size = 0;
    if(0 == bits[idx++])
    {
        local_size_length = 7;
    }else{
        if(0 == bits[idx++])
        {
            local_size_length = 14;
        }else{
            for(uint32_t i=0; i<6; i++)
                size |= bits[idx++] << (6-i-1);
            size *= 16383;
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
        size |= bits[idx++] << (local_size_length-i-1);
    sourceSystemInformationBlockType1Ext_internal_value.clear();
    if((idx +size*8) > bits.size())
    {
        printf("AS_Config::sourceSystemInformationBlockType1Ext_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
    {
        uint8_t value = 0;
        for(uint32_t j=0; j<8; j++)
            value |= bits[idx+j] << (8-j-1);
        sourceSystemInformationBlockType1Ext_internal_value.push_back(value);
        idx += 8;
    }
    sourceSystemInformationBlockType1Ext_present = true;
    return 0;
}

std::vector<uint8_t> AS_Config::sourceSystemInformationBlockType1Ext_Value() const
{
    if(sourceSystemInformationBlockType1Ext_present)
        return sourceSystemInformationBlockType1Ext_internal_value;
    std::vector<uint8_t> tmp;
    return tmp;
}

int AS_Config::sourceSystemInformationBlockType1Ext_SetValue(std::vector<uint8_t> value)
{
    sourceSystemInformationBlockType1Ext_internal_value = value;
    sourceSystemInformationBlockType1Ext_present = true;
    return 0;
}

std::string AS_Config::sourceSystemInformationBlockType1Ext_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "sourceSystemInformationBlockType1Ext = {";
    for(auto byte : sourceSystemInformationBlockType1Ext_internal_value)
        out += std::to_string(byte) + ",";
    out = out.substr(0, out.length()-1) + "}\n";
    return out;
}

std::string AS_Config::sourceSystemInformationBlockType1Ext_ToStringNoNewLines() const
{
    std::string out = "sourceSystemInformationBlockType1Ext={";
    for(auto byte : sourceSystemInformationBlockType1Ext_internal_value)
        out += std::to_string(byte) + ",";
    out = out.substr(0, out.length()-1) + "},";
    return out;
}

int AS_Config::sourceSystemInformationBlockType1Ext_Clear()
{
    sourceSystemInformationBlockType1Ext_present = false;
    return 0;
}

bool AS_Config::sourceSystemInformationBlockType1Ext_IsPresent() const
{
    return sourceSystemInformationBlockType1Ext_present;
}

OtherConfig_r9* AS_Config::sourceOtherConfig_r9_Set()
{
    sourceOtherConfig_r9_present = true;
    return &sourceOtherConfig_r9;
}

int AS_Config::sourceOtherConfig_r9_Set(OtherConfig_r9 &value)
{
    sourceOtherConfig_r9_present = true;
    sourceOtherConfig_r9 = value;
    return 0;
}

const OtherConfig_r9& AS_Config::sourceOtherConfig_r9_Get() const
{
    return sourceOtherConfig_r9;
}

std::string AS_Config::sourceOtherConfig_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "sourceOtherConfig_r9:\n";
    out += sourceOtherConfig_r9.ToString(indent+1);
    return out;
}

std::string AS_Config::sourceOtherConfig_r9_ToStringNoNewLines() const
{
    std::string out = "sourceOtherConfig_r9:";
    out += sourceOtherConfig_r9.ToStringNoNewLines();
    return out;
}

int AS_Config::sourceOtherConfig_r9_Clear()
{
    sourceOtherConfig_r9_present = false;
    return 0;
}

bool AS_Config::sourceOtherConfig_r9_IsPresent() const
{
    return sourceOtherConfig_r9_present;
}

SCellToAddModList_r10* AS_Config::sourceSCellConfigList_r10_Set()
{
    sourceSCellConfigList_r10_present = true;
    return &sourceSCellConfigList_r10;
}

int AS_Config::sourceSCellConfigList_r10_Set(SCellToAddModList_r10 &value)
{
    sourceSCellConfigList_r10_present = true;
    sourceSCellConfigList_r10 = value;
    return 0;
}

const SCellToAddModList_r10& AS_Config::sourceSCellConfigList_r10_Get() const
{
    return sourceSCellConfigList_r10;
}

std::string AS_Config::sourceSCellConfigList_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "sourceSCellConfigList_r10:\n";
    out += sourceSCellConfigList_r10.ToString(indent+1);
    return out;
}

std::string AS_Config::sourceSCellConfigList_r10_ToStringNoNewLines() const
{
    std::string out = "sourceSCellConfigList_r10:";
    out += sourceSCellConfigList_r10.ToStringNoNewLines();
    return out;
}

int AS_Config::sourceSCellConfigList_r10_Clear()
{
    sourceSCellConfigList_r10_present = false;
    return 0;
}

bool AS_Config::sourceSCellConfigList_r10_IsPresent() const
{
    return sourceSCellConfigList_r10_present;
}

