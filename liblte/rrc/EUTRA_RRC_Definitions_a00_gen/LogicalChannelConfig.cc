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

#include "LogicalChannelConfig.h"

#include <cmath>

int LogicalChannelConfig::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator
    bool has_extension = false;
    if(logicalChannelSR_Mask_r9_IsPresent())
    {
        bits.push_back(1);
        has_extension = true;
    }else{
        bits.push_back(0);
    }

    // Optional indicators
    bits.push_back(ul_SpecificParameters_value.IsPresent());

    // Fields
    if(ul_SpecificParameters_value.IsPresent())
    {
        if(0 != ul_SpecificParameters_value.Pack(bits))
        {
            printf("LogicalChannelConfig:: field pack failure\n");
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
            printf("LogicalChannelConfig:: Extension list size too large failure\n");
            return -1;
        }

        // Extension field presence indicators
        bits.push_back(logicalChannelSR_Mask_r9_IsPresent());

        // Extension fields
        if(logicalChannelSR_Mask_r9_IsPresent())
        {
            std::vector<uint8_t> field_bits;
            if(0 != logicalChannelSR_Mask_r9_Pack(field_bits))
            {
                printf("LogicalChannelConfig:: field pack failure\n");
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

int LogicalChannelConfig::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int LogicalChannelConfig::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("LogicalChannelConfig::Unpack() index out of bounds for extension\n");
        return -1;
    }
    bool has_extension = bits[idx++];

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("LogicalChannelConfig::Unpack() index out of bounds for optional indiator ul_SpecificParameters\n");
        return -1;
    }
    ul_SpecificParameters_value.SetPresence(bits[idx++]);

    // Fields
    if(ul_SpecificParameters_value.IsPresent())
    {
        if(0 != ul_SpecificParameters_value.Unpack(bits, idx))
        {
            printf("LogicalChannelConfig:: field unpack failure\n");
            return -1;
        }
    }

    // Extension
    if(has_extension)
    {
        if((idx + 7) > bits.size())
        {
            printf("LogicalChannelConfig::Unpack() index out of bounds for extension size\n");
            return -1;
        }
        // Number of extension fields
        if(bits[idx++] != 0)
        {
            printf("LogicalChannelConfig:: Extension list size too large failure\n");
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
                printf("LogicalChannelConfig::Unpack() index out of bounds for optional indiator logicalChannelSR_Mask_r9\n");
                return -1;
            }
            logicalChannelSR_Mask_r9_present = bits[idx++];
        }
        if((idx + (N_ext_fields - opt_ind_count)) > bits.size())
        {
            printf("LogicalChannelConfig::Unpack() index out of bounds for extension optional indicators\n");
            return -1;
        }
        idx += (N_ext_fields - opt_ind_count);

        // Extension fields
        if(logicalChannelSR_Mask_r9_present)
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
            if(0 != logicalChannelSR_Mask_r9_Unpack(bits, idx))
            {
                printf("LogicalChannelConfig:: field unpack failure\n");
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
            printf("LogicalChannelConfig::Unpack() index out of bounds for extension fields\n");
            return -1;
        }
            idx += N_octets * 8;
        }
    }
    return 0;
}

std::string LogicalChannelConfig::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "LogicalChannelConfig:\n";
    if(ul_SpecificParameters_value.IsPresent())
        out += ul_SpecificParameters_value.ToString(indent+1);
    if(logicalChannelSR_Mask_r9_IsPresent())
        out += logicalChannelSR_Mask_r9_ToString(indent+1);
    return out;
}

std::string LogicalChannelConfig::ToStringNoNewLines() const
{
    std::string out = "LogicalChannelConfig:";
    if(ul_SpecificParameters_value.IsPresent())
        out += ul_SpecificParameters_value.ToStringNoNewLines();
    if(logicalChannelSR_Mask_r9_IsPresent())
        out += logicalChannelSR_Mask_r9_ToStringNoNewLines();
    return out;
}

int LogicalChannelConfig::ul_SpecificParameters::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(logicalChannelGroup_IsPresent());

    // Fields
    {
        if(0 != priority_Pack(bits))
        {
            printf("LogicalChannelConfig::ul_SpecificParameters:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != prioritisedBitRate_Pack(bits))
        {
            printf("LogicalChannelConfig::ul_SpecificParameters:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != bucketSizeDuration_Pack(bits))
        {
            printf("LogicalChannelConfig::ul_SpecificParameters:: field pack failure\n");
            return -1;
        }
    }
    if(logicalChannelGroup_IsPresent())
    {
        if(0 != logicalChannelGroup_Pack(bits))
        {
            printf("LogicalChannelConfig::ul_SpecificParameters:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int LogicalChannelConfig::ul_SpecificParameters::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int LogicalChannelConfig::ul_SpecificParameters::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("ul_SpecificParameters::Unpack() index out of bounds for optional indiator logicalChannelGroup\n");
        return -1;
    }
    logicalChannelGroup_present = bits[idx++];

    // Fields
    {
        if(0 != priority_Unpack(bits, idx))
        {
            printf("LogicalChannelConfig::ul_SpecificParameters:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != prioritisedBitRate_Unpack(bits, idx))
        {
            printf("LogicalChannelConfig::ul_SpecificParameters:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != bucketSizeDuration_Unpack(bits, idx))
        {
            printf("LogicalChannelConfig::ul_SpecificParameters:: field unpack failure\n");
            return -1;
        }
    }
    if(logicalChannelGroup_present)
    {
        if(0 != logicalChannelGroup_Unpack(bits, idx))
        {
            printf("LogicalChannelConfig::ul_SpecificParameters:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string LogicalChannelConfig::ul_SpecificParameters::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ul_SpecificParameters:\n";
    out += priority_ToString(indent+1);
    out += prioritisedBitRate_ToString(indent+1);
    out += bucketSizeDuration_ToString(indent+1);
    if(logicalChannelGroup_IsPresent())
        out += logicalChannelGroup_ToString(indent+1);
    return out;
}

std::string LogicalChannelConfig::ul_SpecificParameters::ToStringNoNewLines() const
{
    std::string out = "ul_SpecificParameters:";
    out += priority_ToStringNoNewLines();
    out += prioritisedBitRate_ToStringNoNewLines();
    out += bucketSizeDuration_ToStringNoNewLines();
    if(logicalChannelGroup_IsPresent())
        out += logicalChannelGroup_ToStringNoNewLines();
    return out;
}

int LogicalChannelConfig::ul_SpecificParameters::Set()
{
    present = true;
    return 0;
}

int LogicalChannelConfig::ul_SpecificParameters::SetPresence(bool is_present)
{
    present = is_present;
    return 0;
}

int LogicalChannelConfig::ul_SpecificParameters::Clear()
{
    present = false;
    return 0;
}

bool LogicalChannelConfig::ul_SpecificParameters::IsPresent() const
{
    return present;
}

int LogicalChannelConfig::ul_SpecificParameters::priority_Pack(std::vector<uint8_t> &bits)
{
    if(!priority_present)
    {
        printf("LogicalChannelConfig::ul_SpecificParameters::priority_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = priority_internal_value - (1);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (16 - 1))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int LogicalChannelConfig::ul_SpecificParameters::priority_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return priority_Unpack(bits, idx);
}

int LogicalChannelConfig::ul_SpecificParameters::priority_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (16 - 1))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("LogicalChannelConfig::ul_SpecificParameters::priority_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    priority_internal_value = packed_val + 1;
    priority_present = true;
    return 0;
}

int64_t LogicalChannelConfig::ul_SpecificParameters::priority_Value() const
{
    if(priority_present)
        return priority_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int LogicalChannelConfig::ul_SpecificParameters::priority_SetValue(int64_t value)
{
    if(value < 1 || value > 16)
    {
        printf("LogicalChannelConfig::ul_SpecificParameters::priority_SetValue() range failure\n");
        return -1;
    }
    priority_internal_value = value;
    priority_present = true;
    return 0;
}

std::string LogicalChannelConfig::ul_SpecificParameters::priority_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "priority = " + std::to_string(priority_internal_value) + "\n";
    return out;
}

std::string LogicalChannelConfig::ul_SpecificParameters::priority_ToStringNoNewLines() const
{
    std::string out = "priority=" + std::to_string(priority_internal_value) + ",";
    return out;
}

int LogicalChannelConfig::ul_SpecificParameters::priority_Clear()
{
    priority_present = false;
    return 0;
}

bool LogicalChannelConfig::ul_SpecificParameters::priority_IsPresent() const
{
    return priority_present;
}

int LogicalChannelConfig::ul_SpecificParameters::prioritisedBitRate_Pack(std::vector<uint8_t> &bits)
{
    if(!prioritisedBitRate_present)
    {
        printf("LogicalChannelConfig::ul_SpecificParameters::prioritisedBitRate_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 4;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((prioritisedBitRate_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int LogicalChannelConfig::ul_SpecificParameters::prioritisedBitRate_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return prioritisedBitRate_Unpack(bits, idx);
}

int LogicalChannelConfig::ul_SpecificParameters::prioritisedBitRate_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 4;
    if((idx + N_bits) > bits.size())
    {
        printf("LogicalChannelConfig::ul_SpecificParameters::prioritisedBitRate_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 15)
    {
        printf("LogicalChannelConfig::ul_SpecificParameters::prioritisedBitRate_Unpack() max failure\n");
        return -1;
    }
    prioritisedBitRate_internal_value = (prioritisedBitRate_Enum)packed_val;
    prioritisedBitRate_present = true;
    return 0;
}

LogicalChannelConfig::ul_SpecificParameters::prioritisedBitRate_Enum LogicalChannelConfig::ul_SpecificParameters::prioritisedBitRate_Value() const
{
    if(prioritisedBitRate_present)
        return prioritisedBitRate_internal_value;
    return (LogicalChannelConfig::ul_SpecificParameters::prioritisedBitRate_Enum)0;
}

int LogicalChannelConfig::ul_SpecificParameters::prioritisedBitRate_SetValue(prioritisedBitRate_Enum value)
{
    prioritisedBitRate_internal_value = value;
    prioritisedBitRate_present = true;
    return 0;
}

int LogicalChannelConfig::ul_SpecificParameters::prioritisedBitRate_SetValue(std::string value)
{
    if("kBps0" == value)
    {
        prioritisedBitRate_internal_value = k_prioritisedBitRate_kBps0;
        prioritisedBitRate_present = true;
        return 0;
    }
    if("kBps8" == value)
    {
        prioritisedBitRate_internal_value = k_prioritisedBitRate_kBps8;
        prioritisedBitRate_present = true;
        return 0;
    }
    if("kBps16" == value)
    {
        prioritisedBitRate_internal_value = k_prioritisedBitRate_kBps16;
        prioritisedBitRate_present = true;
        return 0;
    }
    if("kBps32" == value)
    {
        prioritisedBitRate_internal_value = k_prioritisedBitRate_kBps32;
        prioritisedBitRate_present = true;
        return 0;
    }
    if("kBps64" == value)
    {
        prioritisedBitRate_internal_value = k_prioritisedBitRate_kBps64;
        prioritisedBitRate_present = true;
        return 0;
    }
    if("kBps128" == value)
    {
        prioritisedBitRate_internal_value = k_prioritisedBitRate_kBps128;
        prioritisedBitRate_present = true;
        return 0;
    }
    if("kBps256" == value)
    {
        prioritisedBitRate_internal_value = k_prioritisedBitRate_kBps256;
        prioritisedBitRate_present = true;
        return 0;
    }
    if("infinity" == value)
    {
        prioritisedBitRate_internal_value = k_prioritisedBitRate_infinity;
        prioritisedBitRate_present = true;
        return 0;
    }
    if("spare8" == value)
    {
        prioritisedBitRate_internal_value = k_prioritisedBitRate_spare8;
        prioritisedBitRate_present = true;
        return 0;
    }
    if("spare7" == value)
    {
        prioritisedBitRate_internal_value = k_prioritisedBitRate_spare7;
        prioritisedBitRate_present = true;
        return 0;
    }
    if("spare6" == value)
    {
        prioritisedBitRate_internal_value = k_prioritisedBitRate_spare6;
        prioritisedBitRate_present = true;
        return 0;
    }
    if("spare5" == value)
    {
        prioritisedBitRate_internal_value = k_prioritisedBitRate_spare5;
        prioritisedBitRate_present = true;
        return 0;
    }
    if("spare4" == value)
    {
        prioritisedBitRate_internal_value = k_prioritisedBitRate_spare4;
        prioritisedBitRate_present = true;
        return 0;
    }
    if("spare3" == value)
    {
        prioritisedBitRate_internal_value = k_prioritisedBitRate_spare3;
        prioritisedBitRate_present = true;
        return 0;
    }
    if("spare2" == value)
    {
        prioritisedBitRate_internal_value = k_prioritisedBitRate_spare2;
        prioritisedBitRate_present = true;
        return 0;
    }
    if("spare1" == value)
    {
        prioritisedBitRate_internal_value = k_prioritisedBitRate_spare1;
        prioritisedBitRate_present = true;
        return 0;
    }
    return 1;
}

std::string LogicalChannelConfig::ul_SpecificParameters::prioritisedBitRate_ValueToString(prioritisedBitRate_Enum value) const
{
    if(k_prioritisedBitRate_kBps0 == value)
        return "kBps0";
    if(k_prioritisedBitRate_kBps8 == value)
        return "kBps8";
    if(k_prioritisedBitRate_kBps16 == value)
        return "kBps16";
    if(k_prioritisedBitRate_kBps32 == value)
        return "kBps32";
    if(k_prioritisedBitRate_kBps64 == value)
        return "kBps64";
    if(k_prioritisedBitRate_kBps128 == value)
        return "kBps128";
    if(k_prioritisedBitRate_kBps256 == value)
        return "kBps256";
    if(k_prioritisedBitRate_infinity == value)
        return "infinity";
    if(k_prioritisedBitRate_spare8 == value)
        return "spare8";
    if(k_prioritisedBitRate_spare7 == value)
        return "spare7";
    if(k_prioritisedBitRate_spare6 == value)
        return "spare6";
    if(k_prioritisedBitRate_spare5 == value)
        return "spare5";
    if(k_prioritisedBitRate_spare4 == value)
        return "spare4";
    if(k_prioritisedBitRate_spare3 == value)
        return "spare3";
    if(k_prioritisedBitRate_spare2 == value)
        return "spare2";
    if(k_prioritisedBitRate_spare1 == value)
        return "spare1";
    return "";
}

uint64_t LogicalChannelConfig::ul_SpecificParameters::prioritisedBitRate_NumberOfValues() const
{
    return 16;
}

std::string LogicalChannelConfig::ul_SpecificParameters::prioritisedBitRate_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "prioritisedBitRate = " + prioritisedBitRate_ValueToString(prioritisedBitRate_internal_value) + "\n";
    return out;
}

std::string LogicalChannelConfig::ul_SpecificParameters::prioritisedBitRate_ToStringNoNewLines() const
{
    std::string out = "prioritisedBitRate=" + prioritisedBitRate_ValueToString(prioritisedBitRate_internal_value) + ",";
    return out;
}

int LogicalChannelConfig::ul_SpecificParameters::prioritisedBitRate_Clear()
{
    prioritisedBitRate_present = false;
    return 0;
}

bool LogicalChannelConfig::ul_SpecificParameters::prioritisedBitRate_IsPresent() const
{
    return prioritisedBitRate_present;
}

int LogicalChannelConfig::ul_SpecificParameters::bucketSizeDuration_Pack(std::vector<uint8_t> &bits)
{
    if(!bucketSizeDuration_present)
    {
        printf("LogicalChannelConfig::ul_SpecificParameters::bucketSizeDuration_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 3;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((bucketSizeDuration_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int LogicalChannelConfig::ul_SpecificParameters::bucketSizeDuration_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return bucketSizeDuration_Unpack(bits, idx);
}

int LogicalChannelConfig::ul_SpecificParameters::bucketSizeDuration_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 3;
    if((idx + N_bits) > bits.size())
    {
        printf("LogicalChannelConfig::ul_SpecificParameters::bucketSizeDuration_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 7)
    {
        printf("LogicalChannelConfig::ul_SpecificParameters::bucketSizeDuration_Unpack() max failure\n");
        return -1;
    }
    bucketSizeDuration_internal_value = (bucketSizeDuration_Enum)packed_val;
    bucketSizeDuration_present = true;
    return 0;
}

LogicalChannelConfig::ul_SpecificParameters::bucketSizeDuration_Enum LogicalChannelConfig::ul_SpecificParameters::bucketSizeDuration_Value() const
{
    if(bucketSizeDuration_present)
        return bucketSizeDuration_internal_value;
    return (LogicalChannelConfig::ul_SpecificParameters::bucketSizeDuration_Enum)0;
}

int LogicalChannelConfig::ul_SpecificParameters::bucketSizeDuration_SetValue(bucketSizeDuration_Enum value)
{
    bucketSizeDuration_internal_value = value;
    bucketSizeDuration_present = true;
    return 0;
}

int LogicalChannelConfig::ul_SpecificParameters::bucketSizeDuration_SetValue(std::string value)
{
    if("ms50" == value)
    {
        bucketSizeDuration_internal_value = k_bucketSizeDuration_ms50;
        bucketSizeDuration_present = true;
        return 0;
    }
    if("ms100" == value)
    {
        bucketSizeDuration_internal_value = k_bucketSizeDuration_ms100;
        bucketSizeDuration_present = true;
        return 0;
    }
    if("ms150" == value)
    {
        bucketSizeDuration_internal_value = k_bucketSizeDuration_ms150;
        bucketSizeDuration_present = true;
        return 0;
    }
    if("ms300" == value)
    {
        bucketSizeDuration_internal_value = k_bucketSizeDuration_ms300;
        bucketSizeDuration_present = true;
        return 0;
    }
    if("ms500" == value)
    {
        bucketSizeDuration_internal_value = k_bucketSizeDuration_ms500;
        bucketSizeDuration_present = true;
        return 0;
    }
    if("ms1000" == value)
    {
        bucketSizeDuration_internal_value = k_bucketSizeDuration_ms1000;
        bucketSizeDuration_present = true;
        return 0;
    }
    if("spare2" == value)
    {
        bucketSizeDuration_internal_value = k_bucketSizeDuration_spare2;
        bucketSizeDuration_present = true;
        return 0;
    }
    if("spare1" == value)
    {
        bucketSizeDuration_internal_value = k_bucketSizeDuration_spare1;
        bucketSizeDuration_present = true;
        return 0;
    }
    return 1;
}

std::string LogicalChannelConfig::ul_SpecificParameters::bucketSizeDuration_ValueToString(bucketSizeDuration_Enum value) const
{
    if(k_bucketSizeDuration_ms50 == value)
        return "ms50";
    if(k_bucketSizeDuration_ms100 == value)
        return "ms100";
    if(k_bucketSizeDuration_ms150 == value)
        return "ms150";
    if(k_bucketSizeDuration_ms300 == value)
        return "ms300";
    if(k_bucketSizeDuration_ms500 == value)
        return "ms500";
    if(k_bucketSizeDuration_ms1000 == value)
        return "ms1000";
    if(k_bucketSizeDuration_spare2 == value)
        return "spare2";
    if(k_bucketSizeDuration_spare1 == value)
        return "spare1";
    return "";
}

uint64_t LogicalChannelConfig::ul_SpecificParameters::bucketSizeDuration_NumberOfValues() const
{
    return 8;
}

std::string LogicalChannelConfig::ul_SpecificParameters::bucketSizeDuration_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "bucketSizeDuration = " + bucketSizeDuration_ValueToString(bucketSizeDuration_internal_value) + "\n";
    return out;
}

std::string LogicalChannelConfig::ul_SpecificParameters::bucketSizeDuration_ToStringNoNewLines() const
{
    std::string out = "bucketSizeDuration=" + bucketSizeDuration_ValueToString(bucketSizeDuration_internal_value) + ",";
    return out;
}

int LogicalChannelConfig::ul_SpecificParameters::bucketSizeDuration_Clear()
{
    bucketSizeDuration_present = false;
    return 0;
}

bool LogicalChannelConfig::ul_SpecificParameters::bucketSizeDuration_IsPresent() const
{
    return bucketSizeDuration_present;
}

int LogicalChannelConfig::ul_SpecificParameters::logicalChannelGroup_Pack(std::vector<uint8_t> &bits)
{
    int64_t val_to_pack = logicalChannelGroup_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (3 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int LogicalChannelConfig::ul_SpecificParameters::logicalChannelGroup_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return logicalChannelGroup_Unpack(bits, idx);
}

int LogicalChannelConfig::ul_SpecificParameters::logicalChannelGroup_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (3 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("LogicalChannelConfig::ul_SpecificParameters::logicalChannelGroup_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    logicalChannelGroup_internal_value = packed_val + 0;
    logicalChannelGroup_present = true;
    return 0;
}

int64_t LogicalChannelConfig::ul_SpecificParameters::logicalChannelGroup_Value() const
{
    if(logicalChannelGroup_present)
        return logicalChannelGroup_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int LogicalChannelConfig::ul_SpecificParameters::logicalChannelGroup_SetValue(int64_t value)
{
    if(value < 0 || value > 3)
    {
        printf("LogicalChannelConfig::ul_SpecificParameters::logicalChannelGroup_SetValue() range failure\n");
        return -1;
    }
    logicalChannelGroup_internal_value = value;
    logicalChannelGroup_present = true;
    return 0;
}

std::string LogicalChannelConfig::ul_SpecificParameters::logicalChannelGroup_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "logicalChannelGroup = " + std::to_string(logicalChannelGroup_internal_value) + "\n";
    return out;
}

std::string LogicalChannelConfig::ul_SpecificParameters::logicalChannelGroup_ToStringNoNewLines() const
{
    std::string out = "logicalChannelGroup=" + std::to_string(logicalChannelGroup_internal_value) + ",";
    return out;
}

int LogicalChannelConfig::ul_SpecificParameters::logicalChannelGroup_Clear()
{
    logicalChannelGroup_present = false;
    return 0;
}

bool LogicalChannelConfig::ul_SpecificParameters::logicalChannelGroup_IsPresent() const
{
    return logicalChannelGroup_present;
}

int LogicalChannelConfig::logicalChannelSR_Mask_r9_Pack(std::vector<uint8_t> &bits)
{
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((logicalChannelSR_Mask_r9_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int LogicalChannelConfig::logicalChannelSR_Mask_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return logicalChannelSR_Mask_r9_Unpack(bits, idx);
}

int LogicalChannelConfig::logicalChannelSR_Mask_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("LogicalChannelConfig::logicalChannelSR_Mask_r9_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 0)
    {
        printf("LogicalChannelConfig::logicalChannelSR_Mask_r9_Unpack() max failure\n");
        return -1;
    }
    logicalChannelSR_Mask_r9_internal_value = (logicalChannelSR_Mask_r9_Enum)packed_val;
    logicalChannelSR_Mask_r9_present = true;
    return 0;
}

LogicalChannelConfig::logicalChannelSR_Mask_r9_Enum LogicalChannelConfig::logicalChannelSR_Mask_r9_Value() const
{
    if(logicalChannelSR_Mask_r9_present)
        return logicalChannelSR_Mask_r9_internal_value;
    return (LogicalChannelConfig::logicalChannelSR_Mask_r9_Enum)0;
}

int LogicalChannelConfig::logicalChannelSR_Mask_r9_SetValue(logicalChannelSR_Mask_r9_Enum value)
{
    logicalChannelSR_Mask_r9_internal_value = value;
    logicalChannelSR_Mask_r9_present = true;
    return 0;
}

int LogicalChannelConfig::logicalChannelSR_Mask_r9_SetValue(std::string value)
{
    if("setup" == value)
    {
        logicalChannelSR_Mask_r9_internal_value = k_logicalChannelSR_Mask_r9_setup;
        logicalChannelSR_Mask_r9_present = true;
        return 0;
    }
    return 1;
}

std::string LogicalChannelConfig::logicalChannelSR_Mask_r9_ValueToString(logicalChannelSR_Mask_r9_Enum value) const
{
    if(k_logicalChannelSR_Mask_r9_setup == value)
        return "setup";
    return "";
}

uint64_t LogicalChannelConfig::logicalChannelSR_Mask_r9_NumberOfValues() const
{
    return 1;
}

std::string LogicalChannelConfig::logicalChannelSR_Mask_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "logicalChannelSR_Mask_r9 = " + logicalChannelSR_Mask_r9_ValueToString(logicalChannelSR_Mask_r9_internal_value) + "\n";
    return out;
}

std::string LogicalChannelConfig::logicalChannelSR_Mask_r9_ToStringNoNewLines() const
{
    std::string out = "logicalChannelSR_Mask_r9=" + logicalChannelSR_Mask_r9_ValueToString(logicalChannelSR_Mask_r9_internal_value) + ",";
    return out;
}

int LogicalChannelConfig::logicalChannelSR_Mask_r9_Clear()
{
    logicalChannelSR_Mask_r9_present = false;
    return 0;
}

bool LogicalChannelConfig::logicalChannelSR_Mask_r9_IsPresent() const
{
    return logicalChannelSR_Mask_r9_present;
}

