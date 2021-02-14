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

#include "SystemInformationBlockType3.h"

#include <cmath>

int SystemInformationBlockType3::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator
    bool has_extension = false;
    if(lateNonCriticalExtension_IsPresent() || s_IntraSearch_v920_value.IsPresent() || s_NonIntraSearch_v920_value.IsPresent() || q_QualMin_r9_IsPresent() || threshServingLowQ_r9_IsPresent())
    {
        bits.push_back(1);
        has_extension = true;
    }else{
        bits.push_back(0);
    }

    // Optional indicators

    // Fields
    {
        if(0 != cellReselectionInfoCommon_value.Pack(bits))
        {
            printf("SystemInformationBlockType3:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != cellReselectionServingFreqInfo_value.Pack(bits))
        {
            printf("SystemInformationBlockType3:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != intraFreqCellReselectionInfo_value.Pack(bits))
        {
            printf("SystemInformationBlockType3:: field pack failure\n");
            return -1;
        }
    }

    // Extension
    if(has_extension)
    {
        // Number of extension fields
        if(4 < 64)
        {
            bits.push_back(0);
            for(uint32_t i=0; i<6; i++)
                bits.push_back((4 >> (6-i-1)) & 1);
        }else{
            printf("SystemInformationBlockType3:: Extension list size too large failure\n");
            return -1;
        }

        // Extension field presence indicators
        bits.push_back(lateNonCriticalExtension_IsPresent());
        bits.push_back(s_IntraSearch_v920_value.IsPresent());
        bits.push_back(s_NonIntraSearch_v920_value.IsPresent());
        bits.push_back(q_QualMin_r9_IsPresent());
        bits.push_back(threshServingLowQ_r9_IsPresent());

        // Extension fields
        if(lateNonCriticalExtension_IsPresent())
        {
            std::vector<uint8_t> field_bits;
            if(0 != lateNonCriticalExtension_Pack(field_bits))
            {
                printf("SystemInformationBlockType3:: field pack failure\n");
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
        if(s_IntraSearch_v920_value.IsPresent())
        {
            std::vector<uint8_t> field_bits;
            if(0 != s_IntraSearch_v920_value.Pack(field_bits))
            {
                printf("SystemInformationBlockType3:: field pack failure\n");
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
        if(s_NonIntraSearch_v920_value.IsPresent())
        {
            std::vector<uint8_t> field_bits;
            if(0 != s_NonIntraSearch_v920_value.Pack(field_bits))
            {
                printf("SystemInformationBlockType3:: field pack failure\n");
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
        if(q_QualMin_r9_IsPresent())
        {
            std::vector<uint8_t> field_bits;
            if(0 != q_QualMin_r9.Pack(field_bits))
            {
                printf("SystemInformationBlockType3:: field pack failure\n");
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
        if(threshServingLowQ_r9_IsPresent())
        {
            std::vector<uint8_t> field_bits;
            if(0 != threshServingLowQ_r9.Pack(field_bits))
            {
                printf("SystemInformationBlockType3:: field pack failure\n");
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

int SystemInformationBlockType3::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int SystemInformationBlockType3::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("SystemInformationBlockType3::Unpack() index out of bounds for extension\n");
        return -1;
    }
    bool has_extension = bits[idx++];

    // Optional indicators

    // Fields
    {
        if(0 != cellReselectionInfoCommon_value.Unpack(bits, idx))
        {
            printf("SystemInformationBlockType3:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != cellReselectionServingFreqInfo_value.Unpack(bits, idx))
        {
            printf("SystemInformationBlockType3:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != intraFreqCellReselectionInfo_value.Unpack(bits, idx))
        {
            printf("SystemInformationBlockType3:: field unpack failure\n");
            return -1;
        }
    }

    // Extension
    if(has_extension)
    {
        if((idx + 7) > bits.size())
        {
            printf("SystemInformationBlockType3::Unpack() index out of bounds for extension size\n");
            return -1;
        }
        // Number of extension fields
        if(bits[idx++] != 0)
        {
            printf("SystemInformationBlockType3:: Extension list size too large failure\n");
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
                printf("SystemInformationBlockType3::Unpack() index out of bounds for optional indiator lateNonCriticalExtension\n");
                return -1;
            }
            lateNonCriticalExtension_present = bits[idx++];
        }
        if(opt_ind_count++ < N_ext_fields)
        {
            if((idx + 1) > bits.size())
            {
                printf("SystemInformationBlockType3::Unpack() index out of bounds for optional indiator s_IntraSearch_v920\n");
                return -1;
            }
            s_IntraSearch_v920_value.SetPresence(bits[idx++]);
        }
        if(opt_ind_count++ < N_ext_fields)
        {
            if((idx + 1) > bits.size())
            {
                printf("SystemInformationBlockType3::Unpack() index out of bounds for optional indiator s_NonIntraSearch_v920\n");
                return -1;
            }
            s_NonIntraSearch_v920_value.SetPresence(bits[idx++]);
        }
        if(opt_ind_count++ < N_ext_fields)
        {
            if((idx + 1) > bits.size())
            {
                printf("SystemInformationBlockType3::Unpack() index out of bounds for optional indiator q_QualMin_r9\n");
                return -1;
            }
            q_QualMin_r9_present = bits[idx++];
        }
        if(opt_ind_count++ < N_ext_fields)
        {
            if((idx + 1) > bits.size())
            {
                printf("SystemInformationBlockType3::Unpack() index out of bounds for optional indiator threshServingLowQ_r9\n");
                return -1;
            }
            threshServingLowQ_r9_present = bits[idx++];
        }
        if((idx + (N_ext_fields - opt_ind_count)) > bits.size())
        {
            printf("SystemInformationBlockType3::Unpack() index out of bounds for extension optional indicators\n");
            return -1;
        }
        idx += (N_ext_fields - opt_ind_count);

        // Extension fields
        if(lateNonCriticalExtension_present)
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
            if(0 != lateNonCriticalExtension_Unpack(bits, idx))
            {
                printf("SystemInformationBlockType3:: field unpack failure\n");
                return -1;
            }
            idx = orig_idx + (N_octets * 8);
        }
        if(s_IntraSearch_v920_value.IsPresent())
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
            if(0 != s_IntraSearch_v920_value.Unpack(bits, idx))
            {
                printf("SystemInformationBlockType3:: field unpack failure\n");
                return -1;
            }
            idx = orig_idx + (N_octets * 8);
        }
        if(s_NonIntraSearch_v920_value.IsPresent())
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
            if(0 != s_NonIntraSearch_v920_value.Unpack(bits, idx))
            {
                printf("SystemInformationBlockType3:: field unpack failure\n");
                return -1;
            }
            idx = orig_idx + (N_octets * 8);
        }
        if(q_QualMin_r9_present)
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
            if(0 != q_QualMin_r9.Unpack(bits, idx))
            {
                printf("SystemInformationBlockType3:: field unpack failure\n");
                return -1;
            }
            idx = orig_idx + (N_octets * 8);
        }
        if(threshServingLowQ_r9_present)
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
            if(0 != threshServingLowQ_r9.Unpack(bits, idx))
            {
                printf("SystemInformationBlockType3:: field unpack failure\n");
                return -1;
            }
            idx = orig_idx + (N_octets * 8);
        }
        for(uint32_t i=5; i<N_ext_fields; i++)
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
            printf("SystemInformationBlockType3::Unpack() index out of bounds for extension fields\n");
            return -1;
        }
            idx += N_octets * 8;
        }
    }
    return 0;
}

std::string SystemInformationBlockType3::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "SystemInformationBlockType3:\n";
    out += cellReselectionInfoCommon_value.ToString(indent+1);
    out += cellReselectionServingFreqInfo_value.ToString(indent+1);
    out += intraFreqCellReselectionInfo_value.ToString(indent+1);
    if(lateNonCriticalExtension_IsPresent())
        out += lateNonCriticalExtension_ToString(indent+1);
    if(s_IntraSearch_v920_value.IsPresent())
        out += s_IntraSearch_v920_value.ToString(indent+1);
    if(s_NonIntraSearch_v920_value.IsPresent())
        out += s_NonIntraSearch_v920_value.ToString(indent+1);
    if(q_QualMin_r9_IsPresent())
        out += q_QualMin_r9_ToString(indent+1);
    if(threshServingLowQ_r9_IsPresent())
        out += threshServingLowQ_r9_ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType3::ToStringNoNewLines() const
{
    std::string out = "SystemInformationBlockType3:";
    out += cellReselectionInfoCommon_value.ToStringNoNewLines();
    out += cellReselectionServingFreqInfo_value.ToStringNoNewLines();
    out += intraFreqCellReselectionInfo_value.ToStringNoNewLines();
    if(lateNonCriticalExtension_IsPresent())
        out += lateNonCriticalExtension_ToStringNoNewLines();
    if(s_IntraSearch_v920_value.IsPresent())
        out += s_IntraSearch_v920_value.ToStringNoNewLines();
    if(s_NonIntraSearch_v920_value.IsPresent())
        out += s_NonIntraSearch_v920_value.ToStringNoNewLines();
    if(q_QualMin_r9_IsPresent())
        out += q_QualMin_r9_ToStringNoNewLines();
    if(threshServingLowQ_r9_IsPresent())
        out += threshServingLowQ_r9_ToStringNoNewLines();
    return out;
}

int SystemInformationBlockType3::cellReselectionInfoCommon::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(speedStateReselectionPars_value.IsPresent());

    // Fields
    {
        if(0 != q_Hyst_Pack(bits))
        {
            printf("SystemInformationBlockType3::cellReselectionInfoCommon:: field pack failure\n");
            return -1;
        }
    }
    if(speedStateReselectionPars_value.IsPresent())
    {
        if(0 != speedStateReselectionPars_value.Pack(bits))
        {
            printf("SystemInformationBlockType3::cellReselectionInfoCommon:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int SystemInformationBlockType3::cellReselectionInfoCommon::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int SystemInformationBlockType3::cellReselectionInfoCommon::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("cellReselectionInfoCommon::Unpack() index out of bounds for optional indiator speedStateReselectionPars\n");
        return -1;
    }
    speedStateReselectionPars_value.SetPresence(bits[idx++]);

    // Fields
    {
        if(0 != q_Hyst_Unpack(bits, idx))
        {
            printf("SystemInformationBlockType3::cellReselectionInfoCommon:: field unpack failure\n");
            return -1;
        }
    }
    if(speedStateReselectionPars_value.IsPresent())
    {
        if(0 != speedStateReselectionPars_value.Unpack(bits, idx))
        {
            printf("SystemInformationBlockType3::cellReselectionInfoCommon:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string SystemInformationBlockType3::cellReselectionInfoCommon::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cellReselectionInfoCommon:\n";
    out += q_Hyst_ToString(indent+1);
    if(speedStateReselectionPars_value.IsPresent())
        out += speedStateReselectionPars_value.ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType3::cellReselectionInfoCommon::ToStringNoNewLines() const
{
    std::string out = "cellReselectionInfoCommon:";
    out += q_Hyst_ToStringNoNewLines();
    if(speedStateReselectionPars_value.IsPresent())
        out += speedStateReselectionPars_value.ToStringNoNewLines();
    return out;
}

int SystemInformationBlockType3::cellReselectionInfoCommon::q_Hyst_Pack(std::vector<uint8_t> &bits)
{
    if(!q_Hyst_present)
    {
        printf("SystemInformationBlockType3::cellReselectionInfoCommon::q_Hyst_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 4;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((q_Hyst_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int SystemInformationBlockType3::cellReselectionInfoCommon::q_Hyst_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return q_Hyst_Unpack(bits, idx);
}

int SystemInformationBlockType3::cellReselectionInfoCommon::q_Hyst_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 4;
    if((idx + N_bits) > bits.size())
    {
        printf("SystemInformationBlockType3::cellReselectionInfoCommon::q_Hyst_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 15)
    {
        printf("SystemInformationBlockType3::cellReselectionInfoCommon::q_Hyst_Unpack() max failure\n");
        return -1;
    }
    q_Hyst_internal_value = (q_Hyst_Enum)packed_val;
    q_Hyst_present = true;
    return 0;
}

SystemInformationBlockType3::cellReselectionInfoCommon::q_Hyst_Enum SystemInformationBlockType3::cellReselectionInfoCommon::q_Hyst_Value() const
{
    if(q_Hyst_present)
        return q_Hyst_internal_value;
    return (SystemInformationBlockType3::cellReselectionInfoCommon::q_Hyst_Enum)0;
}

int SystemInformationBlockType3::cellReselectionInfoCommon::q_Hyst_SetValue(q_Hyst_Enum value)
{
    q_Hyst_internal_value = value;
    q_Hyst_present = true;
    return 0;
}

int SystemInformationBlockType3::cellReselectionInfoCommon::q_Hyst_SetValue(std::string value)
{
    if("dB0" == value)
    {
        q_Hyst_internal_value = k_q_Hyst_dB0;
        q_Hyst_present = true;
        return 0;
    }
    if("dB1" == value)
    {
        q_Hyst_internal_value = k_q_Hyst_dB1;
        q_Hyst_present = true;
        return 0;
    }
    if("dB2" == value)
    {
        q_Hyst_internal_value = k_q_Hyst_dB2;
        q_Hyst_present = true;
        return 0;
    }
    if("dB3" == value)
    {
        q_Hyst_internal_value = k_q_Hyst_dB3;
        q_Hyst_present = true;
        return 0;
    }
    if("dB4" == value)
    {
        q_Hyst_internal_value = k_q_Hyst_dB4;
        q_Hyst_present = true;
        return 0;
    }
    if("dB5" == value)
    {
        q_Hyst_internal_value = k_q_Hyst_dB5;
        q_Hyst_present = true;
        return 0;
    }
    if("dB6" == value)
    {
        q_Hyst_internal_value = k_q_Hyst_dB6;
        q_Hyst_present = true;
        return 0;
    }
    if("dB8" == value)
    {
        q_Hyst_internal_value = k_q_Hyst_dB8;
        q_Hyst_present = true;
        return 0;
    }
    if("dB10" == value)
    {
        q_Hyst_internal_value = k_q_Hyst_dB10;
        q_Hyst_present = true;
        return 0;
    }
    if("dB12" == value)
    {
        q_Hyst_internal_value = k_q_Hyst_dB12;
        q_Hyst_present = true;
        return 0;
    }
    if("dB14" == value)
    {
        q_Hyst_internal_value = k_q_Hyst_dB14;
        q_Hyst_present = true;
        return 0;
    }
    if("dB16" == value)
    {
        q_Hyst_internal_value = k_q_Hyst_dB16;
        q_Hyst_present = true;
        return 0;
    }
    if("dB18" == value)
    {
        q_Hyst_internal_value = k_q_Hyst_dB18;
        q_Hyst_present = true;
        return 0;
    }
    if("dB20" == value)
    {
        q_Hyst_internal_value = k_q_Hyst_dB20;
        q_Hyst_present = true;
        return 0;
    }
    if("dB22" == value)
    {
        q_Hyst_internal_value = k_q_Hyst_dB22;
        q_Hyst_present = true;
        return 0;
    }
    if("dB24" == value)
    {
        q_Hyst_internal_value = k_q_Hyst_dB24;
        q_Hyst_present = true;
        return 0;
    }
    return 1;
}

std::string SystemInformationBlockType3::cellReselectionInfoCommon::q_Hyst_ValueToString(q_Hyst_Enum value) const
{
    if(k_q_Hyst_dB0 == value)
        return "dB0";
    if(k_q_Hyst_dB1 == value)
        return "dB1";
    if(k_q_Hyst_dB2 == value)
        return "dB2";
    if(k_q_Hyst_dB3 == value)
        return "dB3";
    if(k_q_Hyst_dB4 == value)
        return "dB4";
    if(k_q_Hyst_dB5 == value)
        return "dB5";
    if(k_q_Hyst_dB6 == value)
        return "dB6";
    if(k_q_Hyst_dB8 == value)
        return "dB8";
    if(k_q_Hyst_dB10 == value)
        return "dB10";
    if(k_q_Hyst_dB12 == value)
        return "dB12";
    if(k_q_Hyst_dB14 == value)
        return "dB14";
    if(k_q_Hyst_dB16 == value)
        return "dB16";
    if(k_q_Hyst_dB18 == value)
        return "dB18";
    if(k_q_Hyst_dB20 == value)
        return "dB20";
    if(k_q_Hyst_dB22 == value)
        return "dB22";
    if(k_q_Hyst_dB24 == value)
        return "dB24";
    return "";
}

uint64_t SystemInformationBlockType3::cellReselectionInfoCommon::q_Hyst_NumberOfValues() const
{
    return 16;
}

std::string SystemInformationBlockType3::cellReselectionInfoCommon::q_Hyst_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "q_Hyst = " + q_Hyst_ValueToString(q_Hyst_internal_value) + "\n";
    return out;
}

std::string SystemInformationBlockType3::cellReselectionInfoCommon::q_Hyst_ToStringNoNewLines() const
{
    std::string out = "q_Hyst=" + q_Hyst_ValueToString(q_Hyst_internal_value) + ",";
    return out;
}

int SystemInformationBlockType3::cellReselectionInfoCommon::q_Hyst_Clear()
{
    q_Hyst_present = false;
    return 0;
}

bool SystemInformationBlockType3::cellReselectionInfoCommon::q_Hyst_IsPresent() const
{
    return q_Hyst_present;
}

int SystemInformationBlockType3::cellReselectionInfoCommon::speedStateReselectionPars::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != mobilityStateParameters.Pack(bits))
        {
            printf("SystemInformationBlockType3::cellReselectionInfoCommon::speedStateReselectionPars:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != q_HystSF_value.Pack(bits))
        {
            printf("SystemInformationBlockType3::cellReselectionInfoCommon::speedStateReselectionPars:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int SystemInformationBlockType3::cellReselectionInfoCommon::speedStateReselectionPars::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int SystemInformationBlockType3::cellReselectionInfoCommon::speedStateReselectionPars::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != mobilityStateParameters.Unpack(bits, idx))
        {
            printf("SystemInformationBlockType3::cellReselectionInfoCommon::speedStateReselectionPars:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != q_HystSF_value.Unpack(bits, idx))
        {
            printf("SystemInformationBlockType3::cellReselectionInfoCommon::speedStateReselectionPars:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string SystemInformationBlockType3::cellReselectionInfoCommon::speedStateReselectionPars::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "speedStateReselectionPars:\n";
    out += mobilityStateParameters_ToString(indent+1);
    out += q_HystSF_value.ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType3::cellReselectionInfoCommon::speedStateReselectionPars::ToStringNoNewLines() const
{
    std::string out = "speedStateReselectionPars:";
    out += mobilityStateParameters_ToStringNoNewLines();
    out += q_HystSF_value.ToStringNoNewLines();
    return out;
}

int SystemInformationBlockType3::cellReselectionInfoCommon::speedStateReselectionPars::Set()
{
    present = true;
    return 0;
}

int SystemInformationBlockType3::cellReselectionInfoCommon::speedStateReselectionPars::SetPresence(bool is_present)
{
    present = is_present;
    return 0;
}

int SystemInformationBlockType3::cellReselectionInfoCommon::speedStateReselectionPars::Clear()
{
    present = false;
    return 0;
}

bool SystemInformationBlockType3::cellReselectionInfoCommon::speedStateReselectionPars::IsPresent() const
{
    return present;
}

MobilityStateParameters* SystemInformationBlockType3::cellReselectionInfoCommon::speedStateReselectionPars::mobilityStateParameters_Set()
{
    mobilityStateParameters_present = true;
    return &mobilityStateParameters;
}

int SystemInformationBlockType3::cellReselectionInfoCommon::speedStateReselectionPars::mobilityStateParameters_Set(MobilityStateParameters &value)
{
    mobilityStateParameters_present = true;
    mobilityStateParameters = value;
    return 0;
}

const MobilityStateParameters& SystemInformationBlockType3::cellReselectionInfoCommon::speedStateReselectionPars::mobilityStateParameters_Get() const
{
    return mobilityStateParameters;
}

std::string SystemInformationBlockType3::cellReselectionInfoCommon::speedStateReselectionPars::mobilityStateParameters_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "mobilityStateParameters:\n";
    out += mobilityStateParameters.ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType3::cellReselectionInfoCommon::speedStateReselectionPars::mobilityStateParameters_ToStringNoNewLines() const
{
    std::string out = "mobilityStateParameters:";
    out += mobilityStateParameters.ToStringNoNewLines();
    return out;
}

int SystemInformationBlockType3::cellReselectionInfoCommon::speedStateReselectionPars::mobilityStateParameters_Clear()
{
    mobilityStateParameters_present = false;
    return 0;
}

bool SystemInformationBlockType3::cellReselectionInfoCommon::speedStateReselectionPars::mobilityStateParameters_IsPresent() const
{
    return mobilityStateParameters_present;
}

int SystemInformationBlockType3::cellReselectionInfoCommon::speedStateReselectionPars::q_HystSF::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != sf_Medium_Pack(bits))
        {
            printf("SystemInformationBlockType3::cellReselectionInfoCommon::speedStateReselectionPars::q_HystSF:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != sf_High_Pack(bits))
        {
            printf("SystemInformationBlockType3::cellReselectionInfoCommon::speedStateReselectionPars::q_HystSF:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int SystemInformationBlockType3::cellReselectionInfoCommon::speedStateReselectionPars::q_HystSF::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int SystemInformationBlockType3::cellReselectionInfoCommon::speedStateReselectionPars::q_HystSF::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != sf_Medium_Unpack(bits, idx))
        {
            printf("SystemInformationBlockType3::cellReselectionInfoCommon::speedStateReselectionPars::q_HystSF:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != sf_High_Unpack(bits, idx))
        {
            printf("SystemInformationBlockType3::cellReselectionInfoCommon::speedStateReselectionPars::q_HystSF:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string SystemInformationBlockType3::cellReselectionInfoCommon::speedStateReselectionPars::q_HystSF::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "q_HystSF:\n";
    out += sf_Medium_ToString(indent+1);
    out += sf_High_ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType3::cellReselectionInfoCommon::speedStateReselectionPars::q_HystSF::ToStringNoNewLines() const
{
    std::string out = "q_HystSF:";
    out += sf_Medium_ToStringNoNewLines();
    out += sf_High_ToStringNoNewLines();
    return out;
}

int SystemInformationBlockType3::cellReselectionInfoCommon::speedStateReselectionPars::q_HystSF::sf_Medium_Pack(std::vector<uint8_t> &bits)
{
    if(!sf_Medium_present)
    {
        printf("SystemInformationBlockType3::cellReselectionInfoCommon::speedStateReselectionPars::q_HystSF::sf_Medium_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 2;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((sf_Medium_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int SystemInformationBlockType3::cellReselectionInfoCommon::speedStateReselectionPars::q_HystSF::sf_Medium_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return sf_Medium_Unpack(bits, idx);
}

int SystemInformationBlockType3::cellReselectionInfoCommon::speedStateReselectionPars::q_HystSF::sf_Medium_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 2;
    if((idx + N_bits) > bits.size())
    {
        printf("SystemInformationBlockType3::cellReselectionInfoCommon::speedStateReselectionPars::q_HystSF::sf_Medium_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 3)
    {
        printf("SystemInformationBlockType3::cellReselectionInfoCommon::speedStateReselectionPars::q_HystSF::sf_Medium_Unpack() max failure\n");
        return -1;
    }
    sf_Medium_internal_value = (sf_Medium_Enum)packed_val;
    sf_Medium_present = true;
    return 0;
}

SystemInformationBlockType3::cellReselectionInfoCommon::speedStateReselectionPars::q_HystSF::sf_Medium_Enum SystemInformationBlockType3::cellReselectionInfoCommon::speedStateReselectionPars::q_HystSF::sf_Medium_Value() const
{
    if(sf_Medium_present)
        return sf_Medium_internal_value;
    return (SystemInformationBlockType3::cellReselectionInfoCommon::speedStateReselectionPars::q_HystSF::sf_Medium_Enum)0;
}

int SystemInformationBlockType3::cellReselectionInfoCommon::speedStateReselectionPars::q_HystSF::sf_Medium_SetValue(sf_Medium_Enum value)
{
    sf_Medium_internal_value = value;
    sf_Medium_present = true;
    return 0;
}

int SystemInformationBlockType3::cellReselectionInfoCommon::speedStateReselectionPars::q_HystSF::sf_Medium_SetValue(std::string value)
{
    if("dB_6" == value)
    {
        sf_Medium_internal_value = k_sf_Medium_dB_6;
        sf_Medium_present = true;
        return 0;
    }
    if("dB_4" == value)
    {
        sf_Medium_internal_value = k_sf_Medium_dB_4;
        sf_Medium_present = true;
        return 0;
    }
    if("dB_2" == value)
    {
        sf_Medium_internal_value = k_sf_Medium_dB_2;
        sf_Medium_present = true;
        return 0;
    }
    if("dB0" == value)
    {
        sf_Medium_internal_value = k_sf_Medium_dB0;
        sf_Medium_present = true;
        return 0;
    }
    return 1;
}

std::string SystemInformationBlockType3::cellReselectionInfoCommon::speedStateReselectionPars::q_HystSF::sf_Medium_ValueToString(sf_Medium_Enum value) const
{
    if(k_sf_Medium_dB_6 == value)
        return "dB_6";
    if(k_sf_Medium_dB_4 == value)
        return "dB_4";
    if(k_sf_Medium_dB_2 == value)
        return "dB_2";
    if(k_sf_Medium_dB0 == value)
        return "dB0";
    return "";
}

uint64_t SystemInformationBlockType3::cellReselectionInfoCommon::speedStateReselectionPars::q_HystSF::sf_Medium_NumberOfValues() const
{
    return 4;
}

std::string SystemInformationBlockType3::cellReselectionInfoCommon::speedStateReselectionPars::q_HystSF::sf_Medium_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "sf_Medium = " + sf_Medium_ValueToString(sf_Medium_internal_value) + "\n";
    return out;
}

std::string SystemInformationBlockType3::cellReselectionInfoCommon::speedStateReselectionPars::q_HystSF::sf_Medium_ToStringNoNewLines() const
{
    std::string out = "sf_Medium=" + sf_Medium_ValueToString(sf_Medium_internal_value) + ",";
    return out;
}

int SystemInformationBlockType3::cellReselectionInfoCommon::speedStateReselectionPars::q_HystSF::sf_Medium_Clear()
{
    sf_Medium_present = false;
    return 0;
}

bool SystemInformationBlockType3::cellReselectionInfoCommon::speedStateReselectionPars::q_HystSF::sf_Medium_IsPresent() const
{
    return sf_Medium_present;
}

int SystemInformationBlockType3::cellReselectionInfoCommon::speedStateReselectionPars::q_HystSF::sf_High_Pack(std::vector<uint8_t> &bits)
{
    if(!sf_High_present)
    {
        printf("SystemInformationBlockType3::cellReselectionInfoCommon::speedStateReselectionPars::q_HystSF::sf_High_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 2;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((sf_High_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int SystemInformationBlockType3::cellReselectionInfoCommon::speedStateReselectionPars::q_HystSF::sf_High_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return sf_High_Unpack(bits, idx);
}

int SystemInformationBlockType3::cellReselectionInfoCommon::speedStateReselectionPars::q_HystSF::sf_High_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 2;
    if((idx + N_bits) > bits.size())
    {
        printf("SystemInformationBlockType3::cellReselectionInfoCommon::speedStateReselectionPars::q_HystSF::sf_High_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 3)
    {
        printf("SystemInformationBlockType3::cellReselectionInfoCommon::speedStateReselectionPars::q_HystSF::sf_High_Unpack() max failure\n");
        return -1;
    }
    sf_High_internal_value = (sf_High_Enum)packed_val;
    sf_High_present = true;
    return 0;
}

SystemInformationBlockType3::cellReselectionInfoCommon::speedStateReselectionPars::q_HystSF::sf_High_Enum SystemInformationBlockType3::cellReselectionInfoCommon::speedStateReselectionPars::q_HystSF::sf_High_Value() const
{
    if(sf_High_present)
        return sf_High_internal_value;
    return (SystemInformationBlockType3::cellReselectionInfoCommon::speedStateReselectionPars::q_HystSF::sf_High_Enum)0;
}

int SystemInformationBlockType3::cellReselectionInfoCommon::speedStateReselectionPars::q_HystSF::sf_High_SetValue(sf_High_Enum value)
{
    sf_High_internal_value = value;
    sf_High_present = true;
    return 0;
}

int SystemInformationBlockType3::cellReselectionInfoCommon::speedStateReselectionPars::q_HystSF::sf_High_SetValue(std::string value)
{
    if("dB_6" == value)
    {
        sf_High_internal_value = k_sf_High_dB_6;
        sf_High_present = true;
        return 0;
    }
    if("dB_4" == value)
    {
        sf_High_internal_value = k_sf_High_dB_4;
        sf_High_present = true;
        return 0;
    }
    if("dB_2" == value)
    {
        sf_High_internal_value = k_sf_High_dB_2;
        sf_High_present = true;
        return 0;
    }
    if("dB0" == value)
    {
        sf_High_internal_value = k_sf_High_dB0;
        sf_High_present = true;
        return 0;
    }
    return 1;
}

std::string SystemInformationBlockType3::cellReselectionInfoCommon::speedStateReselectionPars::q_HystSF::sf_High_ValueToString(sf_High_Enum value) const
{
    if(k_sf_High_dB_6 == value)
        return "dB_6";
    if(k_sf_High_dB_4 == value)
        return "dB_4";
    if(k_sf_High_dB_2 == value)
        return "dB_2";
    if(k_sf_High_dB0 == value)
        return "dB0";
    return "";
}

uint64_t SystemInformationBlockType3::cellReselectionInfoCommon::speedStateReselectionPars::q_HystSF::sf_High_NumberOfValues() const
{
    return 4;
}

std::string SystemInformationBlockType3::cellReselectionInfoCommon::speedStateReselectionPars::q_HystSF::sf_High_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "sf_High = " + sf_High_ValueToString(sf_High_internal_value) + "\n";
    return out;
}

std::string SystemInformationBlockType3::cellReselectionInfoCommon::speedStateReselectionPars::q_HystSF::sf_High_ToStringNoNewLines() const
{
    std::string out = "sf_High=" + sf_High_ValueToString(sf_High_internal_value) + ",";
    return out;
}

int SystemInformationBlockType3::cellReselectionInfoCommon::speedStateReselectionPars::q_HystSF::sf_High_Clear()
{
    sf_High_present = false;
    return 0;
}

bool SystemInformationBlockType3::cellReselectionInfoCommon::speedStateReselectionPars::q_HystSF::sf_High_IsPresent() const
{
    return sf_High_present;
}

int SystemInformationBlockType3::cellReselectionServingFreqInfo::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(s_NonIntraSearch_IsPresent());

    // Fields
    if(s_NonIntraSearch_IsPresent())
    {
        if(0 != s_NonIntraSearch.Pack(bits))
        {
            printf("SystemInformationBlockType3::cellReselectionServingFreqInfo:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != threshServingLow.Pack(bits))
        {
            printf("SystemInformationBlockType3::cellReselectionServingFreqInfo:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != cellReselectionPriority.Pack(bits))
        {
            printf("SystemInformationBlockType3::cellReselectionServingFreqInfo:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int SystemInformationBlockType3::cellReselectionServingFreqInfo::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int SystemInformationBlockType3::cellReselectionServingFreqInfo::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("cellReselectionServingFreqInfo::Unpack() index out of bounds for optional indiator s_NonIntraSearch\n");
        return -1;
    }
    s_NonIntraSearch_present = bits[idx++];

    // Fields
    if(s_NonIntraSearch_present)
    {
        if(0 != s_NonIntraSearch.Unpack(bits, idx))
        {
            printf("SystemInformationBlockType3::cellReselectionServingFreqInfo:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != threshServingLow.Unpack(bits, idx))
        {
            printf("SystemInformationBlockType3::cellReselectionServingFreqInfo:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != cellReselectionPriority.Unpack(bits, idx))
        {
            printf("SystemInformationBlockType3::cellReselectionServingFreqInfo:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string SystemInformationBlockType3::cellReselectionServingFreqInfo::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cellReselectionServingFreqInfo:\n";
    if(s_NonIntraSearch_IsPresent())
        out += s_NonIntraSearch_ToString(indent+1);
    out += threshServingLow_ToString(indent+1);
    out += cellReselectionPriority_ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType3::cellReselectionServingFreqInfo::ToStringNoNewLines() const
{
    std::string out = "cellReselectionServingFreqInfo:";
    if(s_NonIntraSearch_IsPresent())
        out += s_NonIntraSearch_ToStringNoNewLines();
    out += threshServingLow_ToStringNoNewLines();
    out += cellReselectionPriority_ToStringNoNewLines();
    return out;
}

ReselectionThreshold* SystemInformationBlockType3::cellReselectionServingFreqInfo::s_NonIntraSearch_Set()
{
    s_NonIntraSearch_present = true;
    return &s_NonIntraSearch;
}

int SystemInformationBlockType3::cellReselectionServingFreqInfo::s_NonIntraSearch_Set(ReselectionThreshold &value)
{
    s_NonIntraSearch_present = true;
    s_NonIntraSearch = value;
    return 0;
}

const ReselectionThreshold& SystemInformationBlockType3::cellReselectionServingFreqInfo::s_NonIntraSearch_Get() const
{
    return s_NonIntraSearch;
}

std::string SystemInformationBlockType3::cellReselectionServingFreqInfo::s_NonIntraSearch_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "s_NonIntraSearch:\n";
    out += s_NonIntraSearch.ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType3::cellReselectionServingFreqInfo::s_NonIntraSearch_ToStringNoNewLines() const
{
    std::string out = "s_NonIntraSearch:";
    out += s_NonIntraSearch.ToStringNoNewLines();
    return out;
}

int SystemInformationBlockType3::cellReselectionServingFreqInfo::s_NonIntraSearch_Clear()
{
    s_NonIntraSearch_present = false;
    return 0;
}

bool SystemInformationBlockType3::cellReselectionServingFreqInfo::s_NonIntraSearch_IsPresent() const
{
    return s_NonIntraSearch_present;
}

ReselectionThreshold* SystemInformationBlockType3::cellReselectionServingFreqInfo::threshServingLow_Set()
{
    threshServingLow_present = true;
    return &threshServingLow;
}

int SystemInformationBlockType3::cellReselectionServingFreqInfo::threshServingLow_Set(ReselectionThreshold &value)
{
    threshServingLow_present = true;
    threshServingLow = value;
    return 0;
}

const ReselectionThreshold& SystemInformationBlockType3::cellReselectionServingFreqInfo::threshServingLow_Get() const
{
    return threshServingLow;
}

std::string SystemInformationBlockType3::cellReselectionServingFreqInfo::threshServingLow_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "threshServingLow:\n";
    out += threshServingLow.ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType3::cellReselectionServingFreqInfo::threshServingLow_ToStringNoNewLines() const
{
    std::string out = "threshServingLow:";
    out += threshServingLow.ToStringNoNewLines();
    return out;
}

int SystemInformationBlockType3::cellReselectionServingFreqInfo::threshServingLow_Clear()
{
    threshServingLow_present = false;
    return 0;
}

bool SystemInformationBlockType3::cellReselectionServingFreqInfo::threshServingLow_IsPresent() const
{
    return threshServingLow_present;
}

CellReselectionPriority* SystemInformationBlockType3::cellReselectionServingFreqInfo::cellReselectionPriority_Set()
{
    cellReselectionPriority_present = true;
    return &cellReselectionPriority;
}

int SystemInformationBlockType3::cellReselectionServingFreqInfo::cellReselectionPriority_Set(CellReselectionPriority &value)
{
    cellReselectionPriority_present = true;
    cellReselectionPriority = value;
    return 0;
}

const CellReselectionPriority& SystemInformationBlockType3::cellReselectionServingFreqInfo::cellReselectionPriority_Get() const
{
    return cellReselectionPriority;
}

std::string SystemInformationBlockType3::cellReselectionServingFreqInfo::cellReselectionPriority_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cellReselectionPriority:\n";
    out += cellReselectionPriority.ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType3::cellReselectionServingFreqInfo::cellReselectionPriority_ToStringNoNewLines() const
{
    std::string out = "cellReselectionPriority:";
    out += cellReselectionPriority.ToStringNoNewLines();
    return out;
}

int SystemInformationBlockType3::cellReselectionServingFreqInfo::cellReselectionPriority_Clear()
{
    cellReselectionPriority_present = false;
    return 0;
}

bool SystemInformationBlockType3::cellReselectionServingFreqInfo::cellReselectionPriority_IsPresent() const
{
    return cellReselectionPriority_present;
}

int SystemInformationBlockType3::intraFreqCellReselectionInfo::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(p_Max_IsPresent());
    bits.push_back(s_IntraSearch_IsPresent());
    bits.push_back(allowedMeasBandwidth_IsPresent());
    bits.push_back(t_ReselectionEUTRA_SF_IsPresent());

    // Fields
    {
        if(0 != q_RxLevMin.Pack(bits))
        {
            printf("SystemInformationBlockType3::intraFreqCellReselectionInfo:: field pack failure\n");
            return -1;
        }
    }
    if(p_Max_IsPresent())
    {
        if(0 != p_Max.Pack(bits))
        {
            printf("SystemInformationBlockType3::intraFreqCellReselectionInfo:: field pack failure\n");
            return -1;
        }
    }
    if(s_IntraSearch_IsPresent())
    {
        if(0 != s_IntraSearch.Pack(bits))
        {
            printf("SystemInformationBlockType3::intraFreqCellReselectionInfo:: field pack failure\n");
            return -1;
        }
    }
    if(allowedMeasBandwidth_IsPresent())
    {
        if(0 != allowedMeasBandwidth.Pack(bits))
        {
            printf("SystemInformationBlockType3::intraFreqCellReselectionInfo:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != presenceAntennaPort1.Pack(bits))
        {
            printf("SystemInformationBlockType3::intraFreqCellReselectionInfo:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != neighCellConfig.Pack(bits))
        {
            printf("SystemInformationBlockType3::intraFreqCellReselectionInfo:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != t_ReselectionEUTRA.Pack(bits))
        {
            printf("SystemInformationBlockType3::intraFreqCellReselectionInfo:: field pack failure\n");
            return -1;
        }
    }
    if(t_ReselectionEUTRA_SF_IsPresent())
    {
        if(0 != t_ReselectionEUTRA_SF.Pack(bits))
        {
            printf("SystemInformationBlockType3::intraFreqCellReselectionInfo:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int SystemInformationBlockType3::intraFreqCellReselectionInfo::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int SystemInformationBlockType3::intraFreqCellReselectionInfo::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("intraFreqCellReselectionInfo::Unpack() index out of bounds for optional indiator p_Max\n");
        return -1;
    }
    p_Max_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("intraFreqCellReselectionInfo::Unpack() index out of bounds for optional indiator s_IntraSearch\n");
        return -1;
    }
    s_IntraSearch_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("intraFreqCellReselectionInfo::Unpack() index out of bounds for optional indiator allowedMeasBandwidth\n");
        return -1;
    }
    allowedMeasBandwidth_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("intraFreqCellReselectionInfo::Unpack() index out of bounds for optional indiator t_ReselectionEUTRA_SF\n");
        return -1;
    }
    t_ReselectionEUTRA_SF_present = bits[idx++];

    // Fields
    {
        if(0 != q_RxLevMin.Unpack(bits, idx))
        {
            printf("SystemInformationBlockType3::intraFreqCellReselectionInfo:: field unpack failure\n");
            return -1;
        }
    }
    if(p_Max_present)
    {
        if(0 != p_Max.Unpack(bits, idx))
        {
            printf("SystemInformationBlockType3::intraFreqCellReselectionInfo:: field unpack failure\n");
            return -1;
        }
    }
    if(s_IntraSearch_present)
    {
        if(0 != s_IntraSearch.Unpack(bits, idx))
        {
            printf("SystemInformationBlockType3::intraFreqCellReselectionInfo:: field unpack failure\n");
            return -1;
        }
    }
    if(allowedMeasBandwidth_present)
    {
        if(0 != allowedMeasBandwidth.Unpack(bits, idx))
        {
            printf("SystemInformationBlockType3::intraFreqCellReselectionInfo:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != presenceAntennaPort1.Unpack(bits, idx))
        {
            printf("SystemInformationBlockType3::intraFreqCellReselectionInfo:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != neighCellConfig.Unpack(bits, idx))
        {
            printf("SystemInformationBlockType3::intraFreqCellReselectionInfo:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != t_ReselectionEUTRA.Unpack(bits, idx))
        {
            printf("SystemInformationBlockType3::intraFreqCellReselectionInfo:: field unpack failure\n");
            return -1;
        }
    }
    if(t_ReselectionEUTRA_SF_present)
    {
        if(0 != t_ReselectionEUTRA_SF.Unpack(bits, idx))
        {
            printf("SystemInformationBlockType3::intraFreqCellReselectionInfo:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string SystemInformationBlockType3::intraFreqCellReselectionInfo::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "intraFreqCellReselectionInfo:\n";
    out += q_RxLevMin_ToString(indent+1);
    if(p_Max_IsPresent())
        out += p_Max_ToString(indent+1);
    if(s_IntraSearch_IsPresent())
        out += s_IntraSearch_ToString(indent+1);
    if(allowedMeasBandwidth_IsPresent())
        out += allowedMeasBandwidth_ToString(indent+1);
    out += presenceAntennaPort1_ToString(indent+1);
    out += neighCellConfig_ToString(indent+1);
    out += t_ReselectionEUTRA_ToString(indent+1);
    if(t_ReselectionEUTRA_SF_IsPresent())
        out += t_ReselectionEUTRA_SF_ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType3::intraFreqCellReselectionInfo::ToStringNoNewLines() const
{
    std::string out = "intraFreqCellReselectionInfo:";
    out += q_RxLevMin_ToStringNoNewLines();
    if(p_Max_IsPresent())
        out += p_Max_ToStringNoNewLines();
    if(s_IntraSearch_IsPresent())
        out += s_IntraSearch_ToStringNoNewLines();
    if(allowedMeasBandwidth_IsPresent())
        out += allowedMeasBandwidth_ToStringNoNewLines();
    out += presenceAntennaPort1_ToStringNoNewLines();
    out += neighCellConfig_ToStringNoNewLines();
    out += t_ReselectionEUTRA_ToStringNoNewLines();
    if(t_ReselectionEUTRA_SF_IsPresent())
        out += t_ReselectionEUTRA_SF_ToStringNoNewLines();
    return out;
}

Q_RxLevMin* SystemInformationBlockType3::intraFreqCellReselectionInfo::q_RxLevMin_Set()
{
    q_RxLevMin_present = true;
    return &q_RxLevMin;
}

int SystemInformationBlockType3::intraFreqCellReselectionInfo::q_RxLevMin_Set(Q_RxLevMin &value)
{
    q_RxLevMin_present = true;
    q_RxLevMin = value;
    return 0;
}

const Q_RxLevMin& SystemInformationBlockType3::intraFreqCellReselectionInfo::q_RxLevMin_Get() const
{
    return q_RxLevMin;
}

std::string SystemInformationBlockType3::intraFreqCellReselectionInfo::q_RxLevMin_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "q_RxLevMin:\n";
    out += q_RxLevMin.ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType3::intraFreqCellReselectionInfo::q_RxLevMin_ToStringNoNewLines() const
{
    std::string out = "q_RxLevMin:";
    out += q_RxLevMin.ToStringNoNewLines();
    return out;
}

int SystemInformationBlockType3::intraFreqCellReselectionInfo::q_RxLevMin_Clear()
{
    q_RxLevMin_present = false;
    return 0;
}

bool SystemInformationBlockType3::intraFreqCellReselectionInfo::q_RxLevMin_IsPresent() const
{
    return q_RxLevMin_present;
}

P_Max* SystemInformationBlockType3::intraFreqCellReselectionInfo::p_Max_Set()
{
    p_Max_present = true;
    return &p_Max;
}

int SystemInformationBlockType3::intraFreqCellReselectionInfo::p_Max_Set(P_Max &value)
{
    p_Max_present = true;
    p_Max = value;
    return 0;
}

const P_Max& SystemInformationBlockType3::intraFreqCellReselectionInfo::p_Max_Get() const
{
    return p_Max;
}

std::string SystemInformationBlockType3::intraFreqCellReselectionInfo::p_Max_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "p_Max:\n";
    out += p_Max.ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType3::intraFreqCellReselectionInfo::p_Max_ToStringNoNewLines() const
{
    std::string out = "p_Max:";
    out += p_Max.ToStringNoNewLines();
    return out;
}

int SystemInformationBlockType3::intraFreqCellReselectionInfo::p_Max_Clear()
{
    p_Max_present = false;
    return 0;
}

bool SystemInformationBlockType3::intraFreqCellReselectionInfo::p_Max_IsPresent() const
{
    return p_Max_present;
}

ReselectionThreshold* SystemInformationBlockType3::intraFreqCellReselectionInfo::s_IntraSearch_Set()
{
    s_IntraSearch_present = true;
    return &s_IntraSearch;
}

int SystemInformationBlockType3::intraFreqCellReselectionInfo::s_IntraSearch_Set(ReselectionThreshold &value)
{
    s_IntraSearch_present = true;
    s_IntraSearch = value;
    return 0;
}

const ReselectionThreshold& SystemInformationBlockType3::intraFreqCellReselectionInfo::s_IntraSearch_Get() const
{
    return s_IntraSearch;
}

std::string SystemInformationBlockType3::intraFreqCellReselectionInfo::s_IntraSearch_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "s_IntraSearch:\n";
    out += s_IntraSearch.ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType3::intraFreqCellReselectionInfo::s_IntraSearch_ToStringNoNewLines() const
{
    std::string out = "s_IntraSearch:";
    out += s_IntraSearch.ToStringNoNewLines();
    return out;
}

int SystemInformationBlockType3::intraFreqCellReselectionInfo::s_IntraSearch_Clear()
{
    s_IntraSearch_present = false;
    return 0;
}

bool SystemInformationBlockType3::intraFreqCellReselectionInfo::s_IntraSearch_IsPresent() const
{
    return s_IntraSearch_present;
}

AllowedMeasBandwidth* SystemInformationBlockType3::intraFreqCellReselectionInfo::allowedMeasBandwidth_Set()
{
    allowedMeasBandwidth_present = true;
    return &allowedMeasBandwidth;
}

int SystemInformationBlockType3::intraFreqCellReselectionInfo::allowedMeasBandwidth_Set(AllowedMeasBandwidth &value)
{
    allowedMeasBandwidth_present = true;
    allowedMeasBandwidth = value;
    return 0;
}

const AllowedMeasBandwidth& SystemInformationBlockType3::intraFreqCellReselectionInfo::allowedMeasBandwidth_Get() const
{
    return allowedMeasBandwidth;
}

std::string SystemInformationBlockType3::intraFreqCellReselectionInfo::allowedMeasBandwidth_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "allowedMeasBandwidth:\n";
    out += allowedMeasBandwidth.ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType3::intraFreqCellReselectionInfo::allowedMeasBandwidth_ToStringNoNewLines() const
{
    std::string out = "allowedMeasBandwidth:";
    out += allowedMeasBandwidth.ToStringNoNewLines();
    return out;
}

int SystemInformationBlockType3::intraFreqCellReselectionInfo::allowedMeasBandwidth_Clear()
{
    allowedMeasBandwidth_present = false;
    return 0;
}

bool SystemInformationBlockType3::intraFreqCellReselectionInfo::allowedMeasBandwidth_IsPresent() const
{
    return allowedMeasBandwidth_present;
}

PresenceAntennaPort1* SystemInformationBlockType3::intraFreqCellReselectionInfo::presenceAntennaPort1_Set()
{
    presenceAntennaPort1_present = true;
    return &presenceAntennaPort1;
}

int SystemInformationBlockType3::intraFreqCellReselectionInfo::presenceAntennaPort1_Set(PresenceAntennaPort1 &value)
{
    presenceAntennaPort1_present = true;
    presenceAntennaPort1 = value;
    return 0;
}

const PresenceAntennaPort1& SystemInformationBlockType3::intraFreqCellReselectionInfo::presenceAntennaPort1_Get() const
{
    return presenceAntennaPort1;
}

std::string SystemInformationBlockType3::intraFreqCellReselectionInfo::presenceAntennaPort1_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "presenceAntennaPort1:\n";
    out += presenceAntennaPort1.ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType3::intraFreqCellReselectionInfo::presenceAntennaPort1_ToStringNoNewLines() const
{
    std::string out = "presenceAntennaPort1:";
    out += presenceAntennaPort1.ToStringNoNewLines();
    return out;
}

int SystemInformationBlockType3::intraFreqCellReselectionInfo::presenceAntennaPort1_Clear()
{
    presenceAntennaPort1_present = false;
    return 0;
}

bool SystemInformationBlockType3::intraFreqCellReselectionInfo::presenceAntennaPort1_IsPresent() const
{
    return presenceAntennaPort1_present;
}

NeighCellConfig* SystemInformationBlockType3::intraFreqCellReselectionInfo::neighCellConfig_Set()
{
    neighCellConfig_present = true;
    return &neighCellConfig;
}

int SystemInformationBlockType3::intraFreqCellReselectionInfo::neighCellConfig_Set(NeighCellConfig &value)
{
    neighCellConfig_present = true;
    neighCellConfig = value;
    return 0;
}

const NeighCellConfig& SystemInformationBlockType3::intraFreqCellReselectionInfo::neighCellConfig_Get() const
{
    return neighCellConfig;
}

std::string SystemInformationBlockType3::intraFreqCellReselectionInfo::neighCellConfig_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "neighCellConfig:\n";
    out += neighCellConfig.ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType3::intraFreqCellReselectionInfo::neighCellConfig_ToStringNoNewLines() const
{
    std::string out = "neighCellConfig:";
    out += neighCellConfig.ToStringNoNewLines();
    return out;
}

int SystemInformationBlockType3::intraFreqCellReselectionInfo::neighCellConfig_Clear()
{
    neighCellConfig_present = false;
    return 0;
}

bool SystemInformationBlockType3::intraFreqCellReselectionInfo::neighCellConfig_IsPresent() const
{
    return neighCellConfig_present;
}

T_Reselection* SystemInformationBlockType3::intraFreqCellReselectionInfo::t_ReselectionEUTRA_Set()
{
    t_ReselectionEUTRA_present = true;
    return &t_ReselectionEUTRA;
}

int SystemInformationBlockType3::intraFreqCellReselectionInfo::t_ReselectionEUTRA_Set(T_Reselection &value)
{
    t_ReselectionEUTRA_present = true;
    t_ReselectionEUTRA = value;
    return 0;
}

const T_Reselection& SystemInformationBlockType3::intraFreqCellReselectionInfo::t_ReselectionEUTRA_Get() const
{
    return t_ReselectionEUTRA;
}

std::string SystemInformationBlockType3::intraFreqCellReselectionInfo::t_ReselectionEUTRA_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "t_ReselectionEUTRA:\n";
    out += t_ReselectionEUTRA.ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType3::intraFreqCellReselectionInfo::t_ReselectionEUTRA_ToStringNoNewLines() const
{
    std::string out = "t_ReselectionEUTRA:";
    out += t_ReselectionEUTRA.ToStringNoNewLines();
    return out;
}

int SystemInformationBlockType3::intraFreqCellReselectionInfo::t_ReselectionEUTRA_Clear()
{
    t_ReselectionEUTRA_present = false;
    return 0;
}

bool SystemInformationBlockType3::intraFreqCellReselectionInfo::t_ReselectionEUTRA_IsPresent() const
{
    return t_ReselectionEUTRA_present;
}

SpeedStateScaleFactors* SystemInformationBlockType3::intraFreqCellReselectionInfo::t_ReselectionEUTRA_SF_Set()
{
    t_ReselectionEUTRA_SF_present = true;
    return &t_ReselectionEUTRA_SF;
}

int SystemInformationBlockType3::intraFreqCellReselectionInfo::t_ReselectionEUTRA_SF_Set(SpeedStateScaleFactors &value)
{
    t_ReselectionEUTRA_SF_present = true;
    t_ReselectionEUTRA_SF = value;
    return 0;
}

const SpeedStateScaleFactors& SystemInformationBlockType3::intraFreqCellReselectionInfo::t_ReselectionEUTRA_SF_Get() const
{
    return t_ReselectionEUTRA_SF;
}

std::string SystemInformationBlockType3::intraFreqCellReselectionInfo::t_ReselectionEUTRA_SF_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "t_ReselectionEUTRA_SF:\n";
    out += t_ReselectionEUTRA_SF.ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType3::intraFreqCellReselectionInfo::t_ReselectionEUTRA_SF_ToStringNoNewLines() const
{
    std::string out = "t_ReselectionEUTRA_SF:";
    out += t_ReselectionEUTRA_SF.ToStringNoNewLines();
    return out;
}

int SystemInformationBlockType3::intraFreqCellReselectionInfo::t_ReselectionEUTRA_SF_Clear()
{
    t_ReselectionEUTRA_SF_present = false;
    return 0;
}

bool SystemInformationBlockType3::intraFreqCellReselectionInfo::t_ReselectionEUTRA_SF_IsPresent() const
{
    return t_ReselectionEUTRA_SF_present;
}

int SystemInformationBlockType3::lateNonCriticalExtension_Pack(std::vector<uint8_t> &bits)
{
    uint32_t local_size_length = 0;
    uint32_t local_size = lateNonCriticalExtension_internal_value.size();
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
    for(uint32_t i=0; i<lateNonCriticalExtension_internal_value.size(); i++)
        for(uint32_t j=0; j<8; j++)
            bits.push_back((lateNonCriticalExtension_internal_value[i] >> (8-j-1)) & 1);
    return 0;
}

int SystemInformationBlockType3::lateNonCriticalExtension_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return lateNonCriticalExtension_Unpack(bits, idx);
}

int SystemInformationBlockType3::lateNonCriticalExtension_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
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
    lateNonCriticalExtension_internal_value.clear();
    if((idx +size*8) > bits.size())
    {
        printf("SystemInformationBlockType3::lateNonCriticalExtension_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
    {
        uint8_t value = 0;
        for(uint32_t j=0; j<8; j++)
            value |= bits[idx+j] << (8-j-1);
        lateNonCriticalExtension_internal_value.push_back(value);
        idx += 8;
    }
    lateNonCriticalExtension_present = true;
    return 0;
}

std::vector<uint8_t> SystemInformationBlockType3::lateNonCriticalExtension_Value() const
{
    if(lateNonCriticalExtension_present)
        return lateNonCriticalExtension_internal_value;
    std::vector<uint8_t> tmp;
    return tmp;
}

int SystemInformationBlockType3::lateNonCriticalExtension_SetValue(std::vector<uint8_t> value)
{
    lateNonCriticalExtension_internal_value = value;
    lateNonCriticalExtension_present = true;
    return 0;
}

std::string SystemInformationBlockType3::lateNonCriticalExtension_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "lateNonCriticalExtension = {";
    for(auto byte : lateNonCriticalExtension_internal_value)
        out += std::to_string(byte) + ",";
    out = out.substr(0, out.length()-1) + "}\n";
    return out;
}

std::string SystemInformationBlockType3::lateNonCriticalExtension_ToStringNoNewLines() const
{
    std::string out = "lateNonCriticalExtension={";
    for(auto byte : lateNonCriticalExtension_internal_value)
        out += std::to_string(byte) + ",";
    out = out.substr(0, out.length()-1) + "},";
    return out;
}

int SystemInformationBlockType3::lateNonCriticalExtension_Clear()
{
    lateNonCriticalExtension_present = false;
    return 0;
}

bool SystemInformationBlockType3::lateNonCriticalExtension_IsPresent() const
{
    return lateNonCriticalExtension_present;
}

int SystemInformationBlockType3::s_IntraSearch_v920::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != s_IntraSearchP_r9.Pack(bits))
        {
            printf("SystemInformationBlockType3::s_IntraSearch_v920:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != s_IntraSearchQ_r9.Pack(bits))
        {
            printf("SystemInformationBlockType3::s_IntraSearch_v920:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int SystemInformationBlockType3::s_IntraSearch_v920::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int SystemInformationBlockType3::s_IntraSearch_v920::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != s_IntraSearchP_r9.Unpack(bits, idx))
        {
            printf("SystemInformationBlockType3::s_IntraSearch_v920:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != s_IntraSearchQ_r9.Unpack(bits, idx))
        {
            printf("SystemInformationBlockType3::s_IntraSearch_v920:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string SystemInformationBlockType3::s_IntraSearch_v920::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "s_IntraSearch_v920:\n";
    out += s_IntraSearchP_r9_ToString(indent+1);
    out += s_IntraSearchQ_r9_ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType3::s_IntraSearch_v920::ToStringNoNewLines() const
{
    std::string out = "s_IntraSearch_v920:";
    out += s_IntraSearchP_r9_ToStringNoNewLines();
    out += s_IntraSearchQ_r9_ToStringNoNewLines();
    return out;
}

int SystemInformationBlockType3::s_IntraSearch_v920::Set()
{
    present = true;
    return 0;
}

int SystemInformationBlockType3::s_IntraSearch_v920::SetPresence(bool is_present)
{
    present = is_present;
    return 0;
}

int SystemInformationBlockType3::s_IntraSearch_v920::Clear()
{
    present = false;
    return 0;
}

bool SystemInformationBlockType3::s_IntraSearch_v920::IsPresent() const
{
    return present;
}

ReselectionThreshold* SystemInformationBlockType3::s_IntraSearch_v920::s_IntraSearchP_r9_Set()
{
    s_IntraSearchP_r9_present = true;
    return &s_IntraSearchP_r9;
}

int SystemInformationBlockType3::s_IntraSearch_v920::s_IntraSearchP_r9_Set(ReselectionThreshold &value)
{
    s_IntraSearchP_r9_present = true;
    s_IntraSearchP_r9 = value;
    return 0;
}

const ReselectionThreshold& SystemInformationBlockType3::s_IntraSearch_v920::s_IntraSearchP_r9_Get() const
{
    return s_IntraSearchP_r9;
}

std::string SystemInformationBlockType3::s_IntraSearch_v920::s_IntraSearchP_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "s_IntraSearchP_r9:\n";
    out += s_IntraSearchP_r9.ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType3::s_IntraSearch_v920::s_IntraSearchP_r9_ToStringNoNewLines() const
{
    std::string out = "s_IntraSearchP_r9:";
    out += s_IntraSearchP_r9.ToStringNoNewLines();
    return out;
}

int SystemInformationBlockType3::s_IntraSearch_v920::s_IntraSearchP_r9_Clear()
{
    s_IntraSearchP_r9_present = false;
    return 0;
}

bool SystemInformationBlockType3::s_IntraSearch_v920::s_IntraSearchP_r9_IsPresent() const
{
    return s_IntraSearchP_r9_present;
}

ReselectionThresholdQ_r9* SystemInformationBlockType3::s_IntraSearch_v920::s_IntraSearchQ_r9_Set()
{
    s_IntraSearchQ_r9_present = true;
    return &s_IntraSearchQ_r9;
}

int SystemInformationBlockType3::s_IntraSearch_v920::s_IntraSearchQ_r9_Set(ReselectionThresholdQ_r9 &value)
{
    s_IntraSearchQ_r9_present = true;
    s_IntraSearchQ_r9 = value;
    return 0;
}

const ReselectionThresholdQ_r9& SystemInformationBlockType3::s_IntraSearch_v920::s_IntraSearchQ_r9_Get() const
{
    return s_IntraSearchQ_r9;
}

std::string SystemInformationBlockType3::s_IntraSearch_v920::s_IntraSearchQ_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "s_IntraSearchQ_r9:\n";
    out += s_IntraSearchQ_r9.ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType3::s_IntraSearch_v920::s_IntraSearchQ_r9_ToStringNoNewLines() const
{
    std::string out = "s_IntraSearchQ_r9:";
    out += s_IntraSearchQ_r9.ToStringNoNewLines();
    return out;
}

int SystemInformationBlockType3::s_IntraSearch_v920::s_IntraSearchQ_r9_Clear()
{
    s_IntraSearchQ_r9_present = false;
    return 0;
}

bool SystemInformationBlockType3::s_IntraSearch_v920::s_IntraSearchQ_r9_IsPresent() const
{
    return s_IntraSearchQ_r9_present;
}

int SystemInformationBlockType3::s_NonIntraSearch_v920::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != s_NonIntraSearchP_r9.Pack(bits))
        {
            printf("SystemInformationBlockType3::s_NonIntraSearch_v920:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != s_NonIntraSearchQ_r9.Pack(bits))
        {
            printf("SystemInformationBlockType3::s_NonIntraSearch_v920:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int SystemInformationBlockType3::s_NonIntraSearch_v920::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int SystemInformationBlockType3::s_NonIntraSearch_v920::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != s_NonIntraSearchP_r9.Unpack(bits, idx))
        {
            printf("SystemInformationBlockType3::s_NonIntraSearch_v920:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != s_NonIntraSearchQ_r9.Unpack(bits, idx))
        {
            printf("SystemInformationBlockType3::s_NonIntraSearch_v920:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string SystemInformationBlockType3::s_NonIntraSearch_v920::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "s_NonIntraSearch_v920:\n";
    out += s_NonIntraSearchP_r9_ToString(indent+1);
    out += s_NonIntraSearchQ_r9_ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType3::s_NonIntraSearch_v920::ToStringNoNewLines() const
{
    std::string out = "s_NonIntraSearch_v920:";
    out += s_NonIntraSearchP_r9_ToStringNoNewLines();
    out += s_NonIntraSearchQ_r9_ToStringNoNewLines();
    return out;
}

int SystemInformationBlockType3::s_NonIntraSearch_v920::Set()
{
    present = true;
    return 0;
}

int SystemInformationBlockType3::s_NonIntraSearch_v920::SetPresence(bool is_present)
{
    present = is_present;
    return 0;
}

int SystemInformationBlockType3::s_NonIntraSearch_v920::Clear()
{
    present = false;
    return 0;
}

bool SystemInformationBlockType3::s_NonIntraSearch_v920::IsPresent() const
{
    return present;
}

ReselectionThreshold* SystemInformationBlockType3::s_NonIntraSearch_v920::s_NonIntraSearchP_r9_Set()
{
    s_NonIntraSearchP_r9_present = true;
    return &s_NonIntraSearchP_r9;
}

int SystemInformationBlockType3::s_NonIntraSearch_v920::s_NonIntraSearchP_r9_Set(ReselectionThreshold &value)
{
    s_NonIntraSearchP_r9_present = true;
    s_NonIntraSearchP_r9 = value;
    return 0;
}

const ReselectionThreshold& SystemInformationBlockType3::s_NonIntraSearch_v920::s_NonIntraSearchP_r9_Get() const
{
    return s_NonIntraSearchP_r9;
}

std::string SystemInformationBlockType3::s_NonIntraSearch_v920::s_NonIntraSearchP_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "s_NonIntraSearchP_r9:\n";
    out += s_NonIntraSearchP_r9.ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType3::s_NonIntraSearch_v920::s_NonIntraSearchP_r9_ToStringNoNewLines() const
{
    std::string out = "s_NonIntraSearchP_r9:";
    out += s_NonIntraSearchP_r9.ToStringNoNewLines();
    return out;
}

int SystemInformationBlockType3::s_NonIntraSearch_v920::s_NonIntraSearchP_r9_Clear()
{
    s_NonIntraSearchP_r9_present = false;
    return 0;
}

bool SystemInformationBlockType3::s_NonIntraSearch_v920::s_NonIntraSearchP_r9_IsPresent() const
{
    return s_NonIntraSearchP_r9_present;
}

ReselectionThresholdQ_r9* SystemInformationBlockType3::s_NonIntraSearch_v920::s_NonIntraSearchQ_r9_Set()
{
    s_NonIntraSearchQ_r9_present = true;
    return &s_NonIntraSearchQ_r9;
}

int SystemInformationBlockType3::s_NonIntraSearch_v920::s_NonIntraSearchQ_r9_Set(ReselectionThresholdQ_r9 &value)
{
    s_NonIntraSearchQ_r9_present = true;
    s_NonIntraSearchQ_r9 = value;
    return 0;
}

const ReselectionThresholdQ_r9& SystemInformationBlockType3::s_NonIntraSearch_v920::s_NonIntraSearchQ_r9_Get() const
{
    return s_NonIntraSearchQ_r9;
}

std::string SystemInformationBlockType3::s_NonIntraSearch_v920::s_NonIntraSearchQ_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "s_NonIntraSearchQ_r9:\n";
    out += s_NonIntraSearchQ_r9.ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType3::s_NonIntraSearch_v920::s_NonIntraSearchQ_r9_ToStringNoNewLines() const
{
    std::string out = "s_NonIntraSearchQ_r9:";
    out += s_NonIntraSearchQ_r9.ToStringNoNewLines();
    return out;
}

int SystemInformationBlockType3::s_NonIntraSearch_v920::s_NonIntraSearchQ_r9_Clear()
{
    s_NonIntraSearchQ_r9_present = false;
    return 0;
}

bool SystemInformationBlockType3::s_NonIntraSearch_v920::s_NonIntraSearchQ_r9_IsPresent() const
{
    return s_NonIntraSearchQ_r9_present;
}

Q_QualMin_r9* SystemInformationBlockType3::q_QualMin_r9_Set()
{
    q_QualMin_r9_present = true;
    return &q_QualMin_r9;
}

int SystemInformationBlockType3::q_QualMin_r9_Set(Q_QualMin_r9 &value)
{
    q_QualMin_r9_present = true;
    q_QualMin_r9 = value;
    return 0;
}

const Q_QualMin_r9& SystemInformationBlockType3::q_QualMin_r9_Get() const
{
    return q_QualMin_r9;
}

std::string SystemInformationBlockType3::q_QualMin_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "q_QualMin_r9:\n";
    out += q_QualMin_r9.ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType3::q_QualMin_r9_ToStringNoNewLines() const
{
    std::string out = "q_QualMin_r9:";
    out += q_QualMin_r9.ToStringNoNewLines();
    return out;
}

int SystemInformationBlockType3::q_QualMin_r9_Clear()
{
    q_QualMin_r9_present = false;
    return 0;
}

bool SystemInformationBlockType3::q_QualMin_r9_IsPresent() const
{
    return q_QualMin_r9_present;
}

ReselectionThresholdQ_r9* SystemInformationBlockType3::threshServingLowQ_r9_Set()
{
    threshServingLowQ_r9_present = true;
    return &threshServingLowQ_r9;
}

int SystemInformationBlockType3::threshServingLowQ_r9_Set(ReselectionThresholdQ_r9 &value)
{
    threshServingLowQ_r9_present = true;
    threshServingLowQ_r9 = value;
    return 0;
}

const ReselectionThresholdQ_r9& SystemInformationBlockType3::threshServingLowQ_r9_Get() const
{
    return threshServingLowQ_r9;
}

std::string SystemInformationBlockType3::threshServingLowQ_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "threshServingLowQ_r9:\n";
    out += threshServingLowQ_r9.ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType3::threshServingLowQ_r9_ToStringNoNewLines() const
{
    std::string out = "threshServingLowQ_r9:";
    out += threshServingLowQ_r9.ToStringNoNewLines();
    return out;
}

int SystemInformationBlockType3::threshServingLowQ_r9_Clear()
{
    threshServingLowQ_r9_present = false;
    return 0;
}

bool SystemInformationBlockType3::threshServingLowQ_r9_IsPresent() const
{
    return threshServingLowQ_r9_present;
}

