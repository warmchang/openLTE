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

#include "RRM_Config.h"

#include <cmath>

int RRM_Config::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator
    bool has_extension = false;
    if(candidateCellInfoList_r10_IsPresent())
    {
        bits.push_back(1);
        has_extension = true;
    }else{
        bits.push_back(0);
    }

    // Optional indicators
    bits.push_back(ue_InactiveTime_IsPresent());

    // Fields
    if(ue_InactiveTime_IsPresent())
    {
        if(0 != ue_InactiveTime_Pack(bits))
        {
            printf("RRM_Config:: field pack failure\n");
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
            printf("RRM_Config:: Extension list size too large failure\n");
            return -1;
        }

        // Extension field presence indicators
        bits.push_back(candidateCellInfoList_r10_IsPresent());

        // Extension fields
        if(candidateCellInfoList_r10_IsPresent())
        {
            std::vector<uint8_t> field_bits;
            if(0 != candidateCellInfoList_r10.Pack(field_bits))
            {
                printf("RRM_Config:: field pack failure\n");
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

int RRM_Config::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int RRM_Config::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("RRM_Config::Unpack() index out of bounds for extension\n");
        return -1;
    }
    bool has_extension = bits[idx++];

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("RRM_Config::Unpack() index out of bounds for optional indiator ue_InactiveTime\n");
        return -1;
    }
    ue_InactiveTime_present = bits[idx++];

    // Fields
    if(ue_InactiveTime_present)
    {
        if(0 != ue_InactiveTime_Unpack(bits, idx))
        {
            printf("RRM_Config:: field unpack failure\n");
            return -1;
        }
    }

    // Extension
    if(has_extension)
    {
        if((idx + 7) > bits.size())
        {
            printf("RRM_Config::Unpack() index out of bounds for extension size\n");
            return -1;
        }
        // Number of extension fields
        if(bits[idx++] != 0)
        {
            printf("RRM_Config:: Extension list size too large failure\n");
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
                printf("RRM_Config::Unpack() index out of bounds for optional indiator candidateCellInfoList_r10\n");
                return -1;
            }
            candidateCellInfoList_r10_present = bits[idx++];
        }
        if((idx + (N_ext_fields - opt_ind_count)) > bits.size())
        {
            printf("RRM_Config::Unpack() index out of bounds for extension optional indicators\n");
            return -1;
        }
        idx += (N_ext_fields - opt_ind_count);

        // Extension fields
        if(candidateCellInfoList_r10_present)
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
            if(0 != candidateCellInfoList_r10.Unpack(bits, idx))
            {
                printf("RRM_Config:: field unpack failure\n");
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
            printf("RRM_Config::Unpack() index out of bounds for extension fields\n");
            return -1;
        }
            idx += N_octets * 8;
        }
    }
    return 0;
}

std::string RRM_Config::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "RRM_Config:\n";
    if(ue_InactiveTime_IsPresent())
        out += ue_InactiveTime_ToString(indent+1);
    if(candidateCellInfoList_r10_IsPresent())
        out += candidateCellInfoList_r10_ToString(indent+1);
    return out;
}

std::string RRM_Config::ToStringNoNewLines() const
{
    std::string out = "RRM_Config:";
    if(ue_InactiveTime_IsPresent())
        out += ue_InactiveTime_ToStringNoNewLines();
    if(candidateCellInfoList_r10_IsPresent())
        out += candidateCellInfoList_r10_ToStringNoNewLines();
    return out;
}

int RRM_Config::ue_InactiveTime_Pack(std::vector<uint8_t> &bits)
{
    uint32_t N_bits = 6;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((ue_InactiveTime_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int RRM_Config::ue_InactiveTime_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return ue_InactiveTime_Unpack(bits, idx);
}

int RRM_Config::ue_InactiveTime_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 6;
    if((idx + N_bits) > bits.size())
    {
        printf("RRM_Config::ue_InactiveTime_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 63)
    {
        printf("RRM_Config::ue_InactiveTime_Unpack() max failure\n");
        return -1;
    }
    ue_InactiveTime_internal_value = (ue_InactiveTime_Enum)packed_val;
    ue_InactiveTime_present = true;
    return 0;
}

RRM_Config::ue_InactiveTime_Enum RRM_Config::ue_InactiveTime_Value() const
{
    if(ue_InactiveTime_present)
        return ue_InactiveTime_internal_value;
    return (RRM_Config::ue_InactiveTime_Enum)0;
}

int RRM_Config::ue_InactiveTime_SetValue(ue_InactiveTime_Enum value)
{
    ue_InactiveTime_internal_value = value;
    ue_InactiveTime_present = true;
    return 0;
}

int RRM_Config::ue_InactiveTime_SetValue(std::string value)
{
    if("s1" == value)
    {
        ue_InactiveTime_internal_value = k_ue_InactiveTime_s1;
        ue_InactiveTime_present = true;
        return 0;
    }
    if("s2" == value)
    {
        ue_InactiveTime_internal_value = k_ue_InactiveTime_s2;
        ue_InactiveTime_present = true;
        return 0;
    }
    if("s3" == value)
    {
        ue_InactiveTime_internal_value = k_ue_InactiveTime_s3;
        ue_InactiveTime_present = true;
        return 0;
    }
    if("s5" == value)
    {
        ue_InactiveTime_internal_value = k_ue_InactiveTime_s5;
        ue_InactiveTime_present = true;
        return 0;
    }
    if("s7" == value)
    {
        ue_InactiveTime_internal_value = k_ue_InactiveTime_s7;
        ue_InactiveTime_present = true;
        return 0;
    }
    if("s10" == value)
    {
        ue_InactiveTime_internal_value = k_ue_InactiveTime_s10;
        ue_InactiveTime_present = true;
        return 0;
    }
    if("s15" == value)
    {
        ue_InactiveTime_internal_value = k_ue_InactiveTime_s15;
        ue_InactiveTime_present = true;
        return 0;
    }
    if("s20" == value)
    {
        ue_InactiveTime_internal_value = k_ue_InactiveTime_s20;
        ue_InactiveTime_present = true;
        return 0;
    }
    if("s25" == value)
    {
        ue_InactiveTime_internal_value = k_ue_InactiveTime_s25;
        ue_InactiveTime_present = true;
        return 0;
    }
    if("s30" == value)
    {
        ue_InactiveTime_internal_value = k_ue_InactiveTime_s30;
        ue_InactiveTime_present = true;
        return 0;
    }
    if("s40" == value)
    {
        ue_InactiveTime_internal_value = k_ue_InactiveTime_s40;
        ue_InactiveTime_present = true;
        return 0;
    }
    if("s50" == value)
    {
        ue_InactiveTime_internal_value = k_ue_InactiveTime_s50;
        ue_InactiveTime_present = true;
        return 0;
    }
    if("min1" == value)
    {
        ue_InactiveTime_internal_value = k_ue_InactiveTime_min1;
        ue_InactiveTime_present = true;
        return 0;
    }
    if("min1s20c" == value)
    {
        ue_InactiveTime_internal_value = k_ue_InactiveTime_min1s20c;
        ue_InactiveTime_present = true;
        return 0;
    }
    if("min1s40" == value)
    {
        ue_InactiveTime_internal_value = k_ue_InactiveTime_min1s40;
        ue_InactiveTime_present = true;
        return 0;
    }
    if("min2" == value)
    {
        ue_InactiveTime_internal_value = k_ue_InactiveTime_min2;
        ue_InactiveTime_present = true;
        return 0;
    }
    if("min2s30" == value)
    {
        ue_InactiveTime_internal_value = k_ue_InactiveTime_min2s30;
        ue_InactiveTime_present = true;
        return 0;
    }
    if("min3" == value)
    {
        ue_InactiveTime_internal_value = k_ue_InactiveTime_min3;
        ue_InactiveTime_present = true;
        return 0;
    }
    if("min3s30" == value)
    {
        ue_InactiveTime_internal_value = k_ue_InactiveTime_min3s30;
        ue_InactiveTime_present = true;
        return 0;
    }
    if("min4" == value)
    {
        ue_InactiveTime_internal_value = k_ue_InactiveTime_min4;
        ue_InactiveTime_present = true;
        return 0;
    }
    if("min5" == value)
    {
        ue_InactiveTime_internal_value = k_ue_InactiveTime_min5;
        ue_InactiveTime_present = true;
        return 0;
    }
    if("min6" == value)
    {
        ue_InactiveTime_internal_value = k_ue_InactiveTime_min6;
        ue_InactiveTime_present = true;
        return 0;
    }
    if("min7" == value)
    {
        ue_InactiveTime_internal_value = k_ue_InactiveTime_min7;
        ue_InactiveTime_present = true;
        return 0;
    }
    if("min8" == value)
    {
        ue_InactiveTime_internal_value = k_ue_InactiveTime_min8;
        ue_InactiveTime_present = true;
        return 0;
    }
    if("min9" == value)
    {
        ue_InactiveTime_internal_value = k_ue_InactiveTime_min9;
        ue_InactiveTime_present = true;
        return 0;
    }
    if("min10" == value)
    {
        ue_InactiveTime_internal_value = k_ue_InactiveTime_min10;
        ue_InactiveTime_present = true;
        return 0;
    }
    if("min12" == value)
    {
        ue_InactiveTime_internal_value = k_ue_InactiveTime_min12;
        ue_InactiveTime_present = true;
        return 0;
    }
    if("min14" == value)
    {
        ue_InactiveTime_internal_value = k_ue_InactiveTime_min14;
        ue_InactiveTime_present = true;
        return 0;
    }
    if("min17" == value)
    {
        ue_InactiveTime_internal_value = k_ue_InactiveTime_min17;
        ue_InactiveTime_present = true;
        return 0;
    }
    if("min20" == value)
    {
        ue_InactiveTime_internal_value = k_ue_InactiveTime_min20;
        ue_InactiveTime_present = true;
        return 0;
    }
    if("min24" == value)
    {
        ue_InactiveTime_internal_value = k_ue_InactiveTime_min24;
        ue_InactiveTime_present = true;
        return 0;
    }
    if("min28" == value)
    {
        ue_InactiveTime_internal_value = k_ue_InactiveTime_min28;
        ue_InactiveTime_present = true;
        return 0;
    }
    if("min33" == value)
    {
        ue_InactiveTime_internal_value = k_ue_InactiveTime_min33;
        ue_InactiveTime_present = true;
        return 0;
    }
    if("min38" == value)
    {
        ue_InactiveTime_internal_value = k_ue_InactiveTime_min38;
        ue_InactiveTime_present = true;
        return 0;
    }
    if("min44" == value)
    {
        ue_InactiveTime_internal_value = k_ue_InactiveTime_min44;
        ue_InactiveTime_present = true;
        return 0;
    }
    if("min50" == value)
    {
        ue_InactiveTime_internal_value = k_ue_InactiveTime_min50;
        ue_InactiveTime_present = true;
        return 0;
    }
    if("hr1" == value)
    {
        ue_InactiveTime_internal_value = k_ue_InactiveTime_hr1;
        ue_InactiveTime_present = true;
        return 0;
    }
    if("hr1min30" == value)
    {
        ue_InactiveTime_internal_value = k_ue_InactiveTime_hr1min30;
        ue_InactiveTime_present = true;
        return 0;
    }
    if("hr2" == value)
    {
        ue_InactiveTime_internal_value = k_ue_InactiveTime_hr2;
        ue_InactiveTime_present = true;
        return 0;
    }
    if("hr2min30" == value)
    {
        ue_InactiveTime_internal_value = k_ue_InactiveTime_hr2min30;
        ue_InactiveTime_present = true;
        return 0;
    }
    if("hr3" == value)
    {
        ue_InactiveTime_internal_value = k_ue_InactiveTime_hr3;
        ue_InactiveTime_present = true;
        return 0;
    }
    if("hr3min30" == value)
    {
        ue_InactiveTime_internal_value = k_ue_InactiveTime_hr3min30;
        ue_InactiveTime_present = true;
        return 0;
    }
    if("hr4" == value)
    {
        ue_InactiveTime_internal_value = k_ue_InactiveTime_hr4;
        ue_InactiveTime_present = true;
        return 0;
    }
    if("hr5" == value)
    {
        ue_InactiveTime_internal_value = k_ue_InactiveTime_hr5;
        ue_InactiveTime_present = true;
        return 0;
    }
    if("hr6" == value)
    {
        ue_InactiveTime_internal_value = k_ue_InactiveTime_hr6;
        ue_InactiveTime_present = true;
        return 0;
    }
    if("hr8" == value)
    {
        ue_InactiveTime_internal_value = k_ue_InactiveTime_hr8;
        ue_InactiveTime_present = true;
        return 0;
    }
    if("hr10" == value)
    {
        ue_InactiveTime_internal_value = k_ue_InactiveTime_hr10;
        ue_InactiveTime_present = true;
        return 0;
    }
    if("hr13" == value)
    {
        ue_InactiveTime_internal_value = k_ue_InactiveTime_hr13;
        ue_InactiveTime_present = true;
        return 0;
    }
    if("hr16" == value)
    {
        ue_InactiveTime_internal_value = k_ue_InactiveTime_hr16;
        ue_InactiveTime_present = true;
        return 0;
    }
    if("hr20" == value)
    {
        ue_InactiveTime_internal_value = k_ue_InactiveTime_hr20;
        ue_InactiveTime_present = true;
        return 0;
    }
    if("day1" == value)
    {
        ue_InactiveTime_internal_value = k_ue_InactiveTime_day1;
        ue_InactiveTime_present = true;
        return 0;
    }
    if("day1hr12" == value)
    {
        ue_InactiveTime_internal_value = k_ue_InactiveTime_day1hr12;
        ue_InactiveTime_present = true;
        return 0;
    }
    if("day2" == value)
    {
        ue_InactiveTime_internal_value = k_ue_InactiveTime_day2;
        ue_InactiveTime_present = true;
        return 0;
    }
    if("day2hr12" == value)
    {
        ue_InactiveTime_internal_value = k_ue_InactiveTime_day2hr12;
        ue_InactiveTime_present = true;
        return 0;
    }
    if("day3" == value)
    {
        ue_InactiveTime_internal_value = k_ue_InactiveTime_day3;
        ue_InactiveTime_present = true;
        return 0;
    }
    if("day4" == value)
    {
        ue_InactiveTime_internal_value = k_ue_InactiveTime_day4;
        ue_InactiveTime_present = true;
        return 0;
    }
    if("day5" == value)
    {
        ue_InactiveTime_internal_value = k_ue_InactiveTime_day5;
        ue_InactiveTime_present = true;
        return 0;
    }
    if("day7" == value)
    {
        ue_InactiveTime_internal_value = k_ue_InactiveTime_day7;
        ue_InactiveTime_present = true;
        return 0;
    }
    if("day10" == value)
    {
        ue_InactiveTime_internal_value = k_ue_InactiveTime_day10;
        ue_InactiveTime_present = true;
        return 0;
    }
    if("day14" == value)
    {
        ue_InactiveTime_internal_value = k_ue_InactiveTime_day14;
        ue_InactiveTime_present = true;
        return 0;
    }
    if("day19" == value)
    {
        ue_InactiveTime_internal_value = k_ue_InactiveTime_day19;
        ue_InactiveTime_present = true;
        return 0;
    }
    if("day24" == value)
    {
        ue_InactiveTime_internal_value = k_ue_InactiveTime_day24;
        ue_InactiveTime_present = true;
        return 0;
    }
    if("day30" == value)
    {
        ue_InactiveTime_internal_value = k_ue_InactiveTime_day30;
        ue_InactiveTime_present = true;
        return 0;
    }
    if("dayMoreThan30" == value)
    {
        ue_InactiveTime_internal_value = k_ue_InactiveTime_dayMoreThan30;
        ue_InactiveTime_present = true;
        return 0;
    }
    return 1;
}

std::string RRM_Config::ue_InactiveTime_ValueToString(ue_InactiveTime_Enum value) const
{
    if(k_ue_InactiveTime_s1 == value)
        return "s1";
    if(k_ue_InactiveTime_s2 == value)
        return "s2";
    if(k_ue_InactiveTime_s3 == value)
        return "s3";
    if(k_ue_InactiveTime_s5 == value)
        return "s5";
    if(k_ue_InactiveTime_s7 == value)
        return "s7";
    if(k_ue_InactiveTime_s10 == value)
        return "s10";
    if(k_ue_InactiveTime_s15 == value)
        return "s15";
    if(k_ue_InactiveTime_s20 == value)
        return "s20";
    if(k_ue_InactiveTime_s25 == value)
        return "s25";
    if(k_ue_InactiveTime_s30 == value)
        return "s30";
    if(k_ue_InactiveTime_s40 == value)
        return "s40";
    if(k_ue_InactiveTime_s50 == value)
        return "s50";
    if(k_ue_InactiveTime_min1 == value)
        return "min1";
    if(k_ue_InactiveTime_min1s20c == value)
        return "min1s20c";
    if(k_ue_InactiveTime_min1s40 == value)
        return "min1s40";
    if(k_ue_InactiveTime_min2 == value)
        return "min2";
    if(k_ue_InactiveTime_min2s30 == value)
        return "min2s30";
    if(k_ue_InactiveTime_min3 == value)
        return "min3";
    if(k_ue_InactiveTime_min3s30 == value)
        return "min3s30";
    if(k_ue_InactiveTime_min4 == value)
        return "min4";
    if(k_ue_InactiveTime_min5 == value)
        return "min5";
    if(k_ue_InactiveTime_min6 == value)
        return "min6";
    if(k_ue_InactiveTime_min7 == value)
        return "min7";
    if(k_ue_InactiveTime_min8 == value)
        return "min8";
    if(k_ue_InactiveTime_min9 == value)
        return "min9";
    if(k_ue_InactiveTime_min10 == value)
        return "min10";
    if(k_ue_InactiveTime_min12 == value)
        return "min12";
    if(k_ue_InactiveTime_min14 == value)
        return "min14";
    if(k_ue_InactiveTime_min17 == value)
        return "min17";
    if(k_ue_InactiveTime_min20 == value)
        return "min20";
    if(k_ue_InactiveTime_min24 == value)
        return "min24";
    if(k_ue_InactiveTime_min28 == value)
        return "min28";
    if(k_ue_InactiveTime_min33 == value)
        return "min33";
    if(k_ue_InactiveTime_min38 == value)
        return "min38";
    if(k_ue_InactiveTime_min44 == value)
        return "min44";
    if(k_ue_InactiveTime_min50 == value)
        return "min50";
    if(k_ue_InactiveTime_hr1 == value)
        return "hr1";
    if(k_ue_InactiveTime_hr1min30 == value)
        return "hr1min30";
    if(k_ue_InactiveTime_hr2 == value)
        return "hr2";
    if(k_ue_InactiveTime_hr2min30 == value)
        return "hr2min30";
    if(k_ue_InactiveTime_hr3 == value)
        return "hr3";
    if(k_ue_InactiveTime_hr3min30 == value)
        return "hr3min30";
    if(k_ue_InactiveTime_hr4 == value)
        return "hr4";
    if(k_ue_InactiveTime_hr5 == value)
        return "hr5";
    if(k_ue_InactiveTime_hr6 == value)
        return "hr6";
    if(k_ue_InactiveTime_hr8 == value)
        return "hr8";
    if(k_ue_InactiveTime_hr10 == value)
        return "hr10";
    if(k_ue_InactiveTime_hr13 == value)
        return "hr13";
    if(k_ue_InactiveTime_hr16 == value)
        return "hr16";
    if(k_ue_InactiveTime_hr20 == value)
        return "hr20";
    if(k_ue_InactiveTime_day1 == value)
        return "day1";
    if(k_ue_InactiveTime_day1hr12 == value)
        return "day1hr12";
    if(k_ue_InactiveTime_day2 == value)
        return "day2";
    if(k_ue_InactiveTime_day2hr12 == value)
        return "day2hr12";
    if(k_ue_InactiveTime_day3 == value)
        return "day3";
    if(k_ue_InactiveTime_day4 == value)
        return "day4";
    if(k_ue_InactiveTime_day5 == value)
        return "day5";
    if(k_ue_InactiveTime_day7 == value)
        return "day7";
    if(k_ue_InactiveTime_day10 == value)
        return "day10";
    if(k_ue_InactiveTime_day14 == value)
        return "day14";
    if(k_ue_InactiveTime_day19 == value)
        return "day19";
    if(k_ue_InactiveTime_day24 == value)
        return "day24";
    if(k_ue_InactiveTime_day30 == value)
        return "day30";
    if(k_ue_InactiveTime_dayMoreThan30 == value)
        return "dayMoreThan30";
    return "";
}

uint64_t RRM_Config::ue_InactiveTime_NumberOfValues() const
{
    return 64;
}

std::string RRM_Config::ue_InactiveTime_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ue_InactiveTime = " + ue_InactiveTime_ValueToString(ue_InactiveTime_internal_value) + "\n";
    return out;
}

std::string RRM_Config::ue_InactiveTime_ToStringNoNewLines() const
{
    std::string out = "ue_InactiveTime=" + ue_InactiveTime_ValueToString(ue_InactiveTime_internal_value) + ",";
    return out;
}

int RRM_Config::ue_InactiveTime_Clear()
{
    ue_InactiveTime_present = false;
    return 0;
}

bool RRM_Config::ue_InactiveTime_IsPresent() const
{
    return ue_InactiveTime_present;
}

CandidateCellInfoList_r10* RRM_Config::candidateCellInfoList_r10_Set()
{
    candidateCellInfoList_r10_present = true;
    return &candidateCellInfoList_r10;
}

int RRM_Config::candidateCellInfoList_r10_Set(CandidateCellInfoList_r10 &value)
{
    candidateCellInfoList_r10_present = true;
    candidateCellInfoList_r10 = value;
    return 0;
}

const CandidateCellInfoList_r10& RRM_Config::candidateCellInfoList_r10_Get() const
{
    return candidateCellInfoList_r10;
}

std::string RRM_Config::candidateCellInfoList_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "candidateCellInfoList_r10:\n";
    out += candidateCellInfoList_r10.ToString(indent+1);
    return out;
}

std::string RRM_Config::candidateCellInfoList_r10_ToStringNoNewLines() const
{
    std::string out = "candidateCellInfoList_r10:";
    out += candidateCellInfoList_r10.ToStringNoNewLines();
    return out;
}

int RRM_Config::candidateCellInfoList_r10_Clear()
{
    candidateCellInfoList_r10_present = false;
    return 0;
}

bool RRM_Config::candidateCellInfoList_r10_IsPresent() const
{
    return candidateCellInfoList_r10_present;
}

