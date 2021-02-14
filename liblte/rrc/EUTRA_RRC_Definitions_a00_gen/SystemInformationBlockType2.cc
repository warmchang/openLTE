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

#include "SystemInformationBlockType2.h"

#include <cmath>

int SystemInformationBlockType2::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator
    bool has_extension = false;
    if(lateNonCriticalExtension_IsPresent() || ssac_BarringForMMTEL_Voice_r9_IsPresent() || ssac_BarringForMMTEL_Video_r9_IsPresent() || ac_BarringForCSFB_r10_IsPresent())
    {
        bits.push_back(1);
        has_extension = true;
    }else{
        bits.push_back(0);
    }

    // Optional indicators
    bits.push_back(ac_BarringInfo_value.IsPresent());
    bits.push_back(mbsfn_SubframeConfigList_IsPresent());

    // Fields
    if(ac_BarringInfo_value.IsPresent())
    {
        if(0 != ac_BarringInfo_value.Pack(bits))
        {
            printf("SystemInformationBlockType2:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != radioResourceConfigCommon.Pack(bits))
        {
            printf("SystemInformationBlockType2:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != ue_TimersAndConstants.Pack(bits))
        {
            printf("SystemInformationBlockType2:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != freqInfo_value.Pack(bits))
        {
            printf("SystemInformationBlockType2:: field pack failure\n");
            return -1;
        }
    }
    if(mbsfn_SubframeConfigList_IsPresent())
    {
        if(0 != mbsfn_SubframeConfigList.Pack(bits))
        {
            printf("SystemInformationBlockType2:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != timeAlignmentTimerCommon.Pack(bits))
        {
            printf("SystemInformationBlockType2:: field pack failure\n");
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
            printf("SystemInformationBlockType2:: Extension list size too large failure\n");
            return -1;
        }

        // Extension field presence indicators
        bits.push_back(lateNonCriticalExtension_IsPresent());
        bits.push_back(ssac_BarringForMMTEL_Voice_r9_IsPresent());
        bits.push_back(ssac_BarringForMMTEL_Video_r9_IsPresent());
        bits.push_back(ac_BarringForCSFB_r10_IsPresent());

        // Extension fields
        if(lateNonCriticalExtension_IsPresent())
        {
            std::vector<uint8_t> field_bits;
            if(0 != lateNonCriticalExtension_Pack(field_bits))
            {
                printf("SystemInformationBlockType2:: field pack failure\n");
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
        if(ssac_BarringForMMTEL_Voice_r9_IsPresent())
        {
            std::vector<uint8_t> field_bits;
            if(0 != ssac_BarringForMMTEL_Voice_r9.Pack(field_bits))
            {
                printf("SystemInformationBlockType2:: field pack failure\n");
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
        if(ssac_BarringForMMTEL_Video_r9_IsPresent())
        {
            std::vector<uint8_t> field_bits;
            if(0 != ssac_BarringForMMTEL_Video_r9.Pack(field_bits))
            {
                printf("SystemInformationBlockType2:: field pack failure\n");
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
        if(ac_BarringForCSFB_r10_IsPresent())
        {
            std::vector<uint8_t> field_bits;
            if(0 != ac_BarringForCSFB_r10.Pack(field_bits))
            {
                printf("SystemInformationBlockType2:: field pack failure\n");
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

int SystemInformationBlockType2::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int SystemInformationBlockType2::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("SystemInformationBlockType2::Unpack() index out of bounds for extension\n");
        return -1;
    }
    bool has_extension = bits[idx++];

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("SystemInformationBlockType2::Unpack() index out of bounds for optional indiator ac_BarringInfo\n");
        return -1;
    }
    ac_BarringInfo_value.SetPresence(bits[idx++]);
    if((idx + 1) > bits.size())
    {
        printf("SystemInformationBlockType2::Unpack() index out of bounds for optional indiator mbsfn_SubframeConfigList\n");
        return -1;
    }
    mbsfn_SubframeConfigList_present = bits[idx++];

    // Fields
    if(ac_BarringInfo_value.IsPresent())
    {
        if(0 != ac_BarringInfo_value.Unpack(bits, idx))
        {
            printf("SystemInformationBlockType2:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != radioResourceConfigCommon.Unpack(bits, idx))
        {
            printf("SystemInformationBlockType2:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != ue_TimersAndConstants.Unpack(bits, idx))
        {
            printf("SystemInformationBlockType2:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != freqInfo_value.Unpack(bits, idx))
        {
            printf("SystemInformationBlockType2:: field unpack failure\n");
            return -1;
        }
    }
    if(mbsfn_SubframeConfigList_present)
    {
        if(0 != mbsfn_SubframeConfigList.Unpack(bits, idx))
        {
            printf("SystemInformationBlockType2:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != timeAlignmentTimerCommon.Unpack(bits, idx))
        {
            printf("SystemInformationBlockType2:: field unpack failure\n");
            return -1;
        }
    }

    // Extension
    if(has_extension)
    {
        if((idx + 7) > bits.size())
        {
            printf("SystemInformationBlockType2::Unpack() index out of bounds for extension size\n");
            return -1;
        }
        // Number of extension fields
        if(bits[idx++] != 0)
        {
            printf("SystemInformationBlockType2:: Extension list size too large failure\n");
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
                printf("SystemInformationBlockType2::Unpack() index out of bounds for optional indiator lateNonCriticalExtension\n");
                return -1;
            }
            lateNonCriticalExtension_present = bits[idx++];
        }
        if(opt_ind_count++ < N_ext_fields)
        {
            if((idx + 1) > bits.size())
            {
                printf("SystemInformationBlockType2::Unpack() index out of bounds for optional indiator ssac_BarringForMMTEL_Voice_r9\n");
                return -1;
            }
            ssac_BarringForMMTEL_Voice_r9_present = bits[idx++];
        }
        if(opt_ind_count++ < N_ext_fields)
        {
            if((idx + 1) > bits.size())
            {
                printf("SystemInformationBlockType2::Unpack() index out of bounds for optional indiator ssac_BarringForMMTEL_Video_r9\n");
                return -1;
            }
            ssac_BarringForMMTEL_Video_r9_present = bits[idx++];
        }
        if(opt_ind_count++ < N_ext_fields)
        {
            if((idx + 1) > bits.size())
            {
                printf("SystemInformationBlockType2::Unpack() index out of bounds for optional indiator ac_BarringForCSFB_r10\n");
                return -1;
            }
            ac_BarringForCSFB_r10_present = bits[idx++];
        }
        if((idx + (N_ext_fields - opt_ind_count)) > bits.size())
        {
            printf("SystemInformationBlockType2::Unpack() index out of bounds for extension optional indicators\n");
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
                printf("SystemInformationBlockType2:: field unpack failure\n");
                return -1;
            }
            idx = orig_idx + (N_octets * 8);
        }
        if(ssac_BarringForMMTEL_Voice_r9_present)
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
            if(0 != ssac_BarringForMMTEL_Voice_r9.Unpack(bits, idx))
            {
                printf("SystemInformationBlockType2:: field unpack failure\n");
                return -1;
            }
            idx = orig_idx + (N_octets * 8);
        }
        if(ssac_BarringForMMTEL_Video_r9_present)
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
            if(0 != ssac_BarringForMMTEL_Video_r9.Unpack(bits, idx))
            {
                printf("SystemInformationBlockType2:: field unpack failure\n");
                return -1;
            }
            idx = orig_idx + (N_octets * 8);
        }
        if(ac_BarringForCSFB_r10_present)
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
            if(0 != ac_BarringForCSFB_r10.Unpack(bits, idx))
            {
                printf("SystemInformationBlockType2:: field unpack failure\n");
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
            printf("SystemInformationBlockType2::Unpack() index out of bounds for extension fields\n");
            return -1;
        }
            idx += N_octets * 8;
        }
    }
    return 0;
}

std::string SystemInformationBlockType2::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "SystemInformationBlockType2:\n";
    if(ac_BarringInfo_value.IsPresent())
        out += ac_BarringInfo_value.ToString(indent+1);
    out += radioResourceConfigCommon_ToString(indent+1);
    out += ue_TimersAndConstants_ToString(indent+1);
    out += freqInfo_value.ToString(indent+1);
    if(mbsfn_SubframeConfigList_IsPresent())
        out += mbsfn_SubframeConfigList_ToString(indent+1);
    out += timeAlignmentTimerCommon_ToString(indent+1);
    if(lateNonCriticalExtension_IsPresent())
        out += lateNonCriticalExtension_ToString(indent+1);
    if(ssac_BarringForMMTEL_Voice_r9_IsPresent())
        out += ssac_BarringForMMTEL_Voice_r9_ToString(indent+1);
    if(ssac_BarringForMMTEL_Video_r9_IsPresent())
        out += ssac_BarringForMMTEL_Video_r9_ToString(indent+1);
    if(ac_BarringForCSFB_r10_IsPresent())
        out += ac_BarringForCSFB_r10_ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType2::ToStringNoNewLines() const
{
    std::string out = "SystemInformationBlockType2:";
    if(ac_BarringInfo_value.IsPresent())
        out += ac_BarringInfo_value.ToStringNoNewLines();
    out += radioResourceConfigCommon_ToStringNoNewLines();
    out += ue_TimersAndConstants_ToStringNoNewLines();
    out += freqInfo_value.ToStringNoNewLines();
    if(mbsfn_SubframeConfigList_IsPresent())
        out += mbsfn_SubframeConfigList_ToStringNoNewLines();
    out += timeAlignmentTimerCommon_ToStringNoNewLines();
    if(lateNonCriticalExtension_IsPresent())
        out += lateNonCriticalExtension_ToStringNoNewLines();
    if(ssac_BarringForMMTEL_Voice_r9_IsPresent())
        out += ssac_BarringForMMTEL_Voice_r9_ToStringNoNewLines();
    if(ssac_BarringForMMTEL_Video_r9_IsPresent())
        out += ssac_BarringForMMTEL_Video_r9_ToStringNoNewLines();
    if(ac_BarringForCSFB_r10_IsPresent())
        out += ac_BarringForCSFB_r10_ToStringNoNewLines();
    return out;
}

int SystemInformationBlockType2::ac_BarringInfo::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(ac_BarringForMO_Signalling_IsPresent());
    bits.push_back(ac_BarringForMO_Data_IsPresent());

    // Fields
    {
        if(0 != ac_BarringForEmergency_Pack(bits))
        {
            printf("SystemInformationBlockType2::ac_BarringInfo:: field pack failure\n");
            return -1;
        }
    }
    if(ac_BarringForMO_Signalling_IsPresent())
    {
        if(0 != ac_BarringForMO_Signalling.Pack(bits))
        {
            printf("SystemInformationBlockType2::ac_BarringInfo:: field pack failure\n");
            return -1;
        }
    }
    if(ac_BarringForMO_Data_IsPresent())
    {
        if(0 != ac_BarringForMO_Data.Pack(bits))
        {
            printf("SystemInformationBlockType2::ac_BarringInfo:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int SystemInformationBlockType2::ac_BarringInfo::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int SystemInformationBlockType2::ac_BarringInfo::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("ac_BarringInfo::Unpack() index out of bounds for optional indiator ac_BarringForMO_Signalling\n");
        return -1;
    }
    ac_BarringForMO_Signalling_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("ac_BarringInfo::Unpack() index out of bounds for optional indiator ac_BarringForMO_Data\n");
        return -1;
    }
    ac_BarringForMO_Data_present = bits[idx++];

    // Fields
    {
        if(0 != ac_BarringForEmergency_Unpack(bits, idx))
        {
            printf("SystemInformationBlockType2::ac_BarringInfo:: field unpack failure\n");
            return -1;
        }
    }
    if(ac_BarringForMO_Signalling_present)
    {
        if(0 != ac_BarringForMO_Signalling.Unpack(bits, idx))
        {
            printf("SystemInformationBlockType2::ac_BarringInfo:: field unpack failure\n");
            return -1;
        }
    }
    if(ac_BarringForMO_Data_present)
    {
        if(0 != ac_BarringForMO_Data.Unpack(bits, idx))
        {
            printf("SystemInformationBlockType2::ac_BarringInfo:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string SystemInformationBlockType2::ac_BarringInfo::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ac_BarringInfo:\n";
    out += ac_BarringForEmergency_ToString(indent+1);
    if(ac_BarringForMO_Signalling_IsPresent())
        out += ac_BarringForMO_Signalling_ToString(indent+1);
    if(ac_BarringForMO_Data_IsPresent())
        out += ac_BarringForMO_Data_ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType2::ac_BarringInfo::ToStringNoNewLines() const
{
    std::string out = "ac_BarringInfo:";
    out += ac_BarringForEmergency_ToStringNoNewLines();
    if(ac_BarringForMO_Signalling_IsPresent())
        out += ac_BarringForMO_Signalling_ToStringNoNewLines();
    if(ac_BarringForMO_Data_IsPresent())
        out += ac_BarringForMO_Data_ToStringNoNewLines();
    return out;
}

int SystemInformationBlockType2::ac_BarringInfo::Set()
{
    present = true;
    return 0;
}

int SystemInformationBlockType2::ac_BarringInfo::SetPresence(bool is_present)
{
    present = is_present;
    return 0;
}

int SystemInformationBlockType2::ac_BarringInfo::Clear()
{
    present = false;
    return 0;
}

bool SystemInformationBlockType2::ac_BarringInfo::IsPresent() const
{
    return present;
}

int SystemInformationBlockType2::ac_BarringInfo::ac_BarringForEmergency_Pack(std::vector<uint8_t> &bits)
{
    if(!ac_BarringForEmergency_present)
    {
        printf("SystemInformationBlockType2::ac_BarringInfo::ac_BarringForEmergency_Pack() presence failure\n");
        return -1;
    }
    bits.push_back(ac_BarringForEmergency_internal_value);
    return 0;
}

int SystemInformationBlockType2::ac_BarringInfo::ac_BarringForEmergency_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return ac_BarringForEmergency_Unpack(bits, idx);
}

int SystemInformationBlockType2::ac_BarringInfo::ac_BarringForEmergency_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    if((idx + 1) > bits.size())
    {
        printf("SystemInformationBlockType2::ac_BarringInfo::ac_BarringForEmergency_Unpack() index out of bounds\n");
        return -1;
    }
    ac_BarringForEmergency_internal_value = bits[idx++];
    ac_BarringForEmergency_present = true;
    return 0;
}

bool SystemInformationBlockType2::ac_BarringInfo::ac_BarringForEmergency_Value() const
{
    if(ac_BarringForEmergency_present)
        return ac_BarringForEmergency_internal_value;
    return false;
}

int SystemInformationBlockType2::ac_BarringInfo::ac_BarringForEmergency_SetValue(bool value)
{
    ac_BarringForEmergency_internal_value = value;
    ac_BarringForEmergency_present = true;
    return 0;
}

std::string SystemInformationBlockType2::ac_BarringInfo::ac_BarringForEmergency_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ac_BarringForEmergency = " + std::to_string(ac_BarringForEmergency_internal_value) + "\n";
    return out;
}

std::string SystemInformationBlockType2::ac_BarringInfo::ac_BarringForEmergency_ToStringNoNewLines() const
{
    std::string out = "ac_BarringForEmergency=" + std::to_string(ac_BarringForEmergency_internal_value) + ",";
    return out;
}

int SystemInformationBlockType2::ac_BarringInfo::ac_BarringForEmergency_Clear()
{
    ac_BarringForEmergency_present = false;
    return 0;
}

bool SystemInformationBlockType2::ac_BarringInfo::ac_BarringForEmergency_IsPresent() const
{
    return ac_BarringForEmergency_present;
}

AC_BarringConfig* SystemInformationBlockType2::ac_BarringInfo::ac_BarringForMO_Signalling_Set()
{
    ac_BarringForMO_Signalling_present = true;
    return &ac_BarringForMO_Signalling;
}

int SystemInformationBlockType2::ac_BarringInfo::ac_BarringForMO_Signalling_Set(AC_BarringConfig &value)
{
    ac_BarringForMO_Signalling_present = true;
    ac_BarringForMO_Signalling = value;
    return 0;
}

const AC_BarringConfig& SystemInformationBlockType2::ac_BarringInfo::ac_BarringForMO_Signalling_Get() const
{
    return ac_BarringForMO_Signalling;
}

std::string SystemInformationBlockType2::ac_BarringInfo::ac_BarringForMO_Signalling_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ac_BarringForMO_Signalling:\n";
    out += ac_BarringForMO_Signalling.ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType2::ac_BarringInfo::ac_BarringForMO_Signalling_ToStringNoNewLines() const
{
    std::string out = "ac_BarringForMO_Signalling:";
    out += ac_BarringForMO_Signalling.ToStringNoNewLines();
    return out;
}

int SystemInformationBlockType2::ac_BarringInfo::ac_BarringForMO_Signalling_Clear()
{
    ac_BarringForMO_Signalling_present = false;
    return 0;
}

bool SystemInformationBlockType2::ac_BarringInfo::ac_BarringForMO_Signalling_IsPresent() const
{
    return ac_BarringForMO_Signalling_present;
}

AC_BarringConfig* SystemInformationBlockType2::ac_BarringInfo::ac_BarringForMO_Data_Set()
{
    ac_BarringForMO_Data_present = true;
    return &ac_BarringForMO_Data;
}

int SystemInformationBlockType2::ac_BarringInfo::ac_BarringForMO_Data_Set(AC_BarringConfig &value)
{
    ac_BarringForMO_Data_present = true;
    ac_BarringForMO_Data = value;
    return 0;
}

const AC_BarringConfig& SystemInformationBlockType2::ac_BarringInfo::ac_BarringForMO_Data_Get() const
{
    return ac_BarringForMO_Data;
}

std::string SystemInformationBlockType2::ac_BarringInfo::ac_BarringForMO_Data_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ac_BarringForMO_Data:\n";
    out += ac_BarringForMO_Data.ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType2::ac_BarringInfo::ac_BarringForMO_Data_ToStringNoNewLines() const
{
    std::string out = "ac_BarringForMO_Data:";
    out += ac_BarringForMO_Data.ToStringNoNewLines();
    return out;
}

int SystemInformationBlockType2::ac_BarringInfo::ac_BarringForMO_Data_Clear()
{
    ac_BarringForMO_Data_present = false;
    return 0;
}

bool SystemInformationBlockType2::ac_BarringInfo::ac_BarringForMO_Data_IsPresent() const
{
    return ac_BarringForMO_Data_present;
}

RadioResourceConfigCommonSIB* SystemInformationBlockType2::radioResourceConfigCommon_Set()
{
    radioResourceConfigCommon_present = true;
    return &radioResourceConfigCommon;
}

int SystemInformationBlockType2::radioResourceConfigCommon_Set(RadioResourceConfigCommonSIB &value)
{
    radioResourceConfigCommon_present = true;
    radioResourceConfigCommon = value;
    return 0;
}

const RadioResourceConfigCommonSIB& SystemInformationBlockType2::radioResourceConfigCommon_Get() const
{
    return radioResourceConfigCommon;
}

std::string SystemInformationBlockType2::radioResourceConfigCommon_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "radioResourceConfigCommon:\n";
    out += radioResourceConfigCommon.ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType2::radioResourceConfigCommon_ToStringNoNewLines() const
{
    std::string out = "radioResourceConfigCommon:";
    out += radioResourceConfigCommon.ToStringNoNewLines();
    return out;
}

int SystemInformationBlockType2::radioResourceConfigCommon_Clear()
{
    radioResourceConfigCommon_present = false;
    return 0;
}

bool SystemInformationBlockType2::radioResourceConfigCommon_IsPresent() const
{
    return radioResourceConfigCommon_present;
}

UE_TimersAndConstants* SystemInformationBlockType2::ue_TimersAndConstants_Set()
{
    ue_TimersAndConstants_present = true;
    return &ue_TimersAndConstants;
}

int SystemInformationBlockType2::ue_TimersAndConstants_Set(UE_TimersAndConstants &value)
{
    ue_TimersAndConstants_present = true;
    ue_TimersAndConstants = value;
    return 0;
}

const UE_TimersAndConstants& SystemInformationBlockType2::ue_TimersAndConstants_Get() const
{
    return ue_TimersAndConstants;
}

std::string SystemInformationBlockType2::ue_TimersAndConstants_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ue_TimersAndConstants:\n";
    out += ue_TimersAndConstants.ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType2::ue_TimersAndConstants_ToStringNoNewLines() const
{
    std::string out = "ue_TimersAndConstants:";
    out += ue_TimersAndConstants.ToStringNoNewLines();
    return out;
}

int SystemInformationBlockType2::ue_TimersAndConstants_Clear()
{
    ue_TimersAndConstants_present = false;
    return 0;
}

bool SystemInformationBlockType2::ue_TimersAndConstants_IsPresent() const
{
    return ue_TimersAndConstants_present;
}

int SystemInformationBlockType2::freqInfo::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(ul_CarrierFreq_IsPresent());
    bits.push_back(ul_Bandwidth_IsPresent());

    // Fields
    if(ul_CarrierFreq_IsPresent())
    {
        if(0 != ul_CarrierFreq.Pack(bits))
        {
            printf("SystemInformationBlockType2::freqInfo:: field pack failure\n");
            return -1;
        }
    }
    if(ul_Bandwidth_IsPresent())
    {
        if(0 != ul_Bandwidth_Pack(bits))
        {
            printf("SystemInformationBlockType2::freqInfo:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != additionalSpectrumEmission.Pack(bits))
        {
            printf("SystemInformationBlockType2::freqInfo:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int SystemInformationBlockType2::freqInfo::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int SystemInformationBlockType2::freqInfo::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("freqInfo::Unpack() index out of bounds for optional indiator ul_CarrierFreq\n");
        return -1;
    }
    ul_CarrierFreq_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("freqInfo::Unpack() index out of bounds for optional indiator ul_Bandwidth\n");
        return -1;
    }
    ul_Bandwidth_present = bits[idx++];

    // Fields
    if(ul_CarrierFreq_present)
    {
        if(0 != ul_CarrierFreq.Unpack(bits, idx))
        {
            printf("SystemInformationBlockType2::freqInfo:: field unpack failure\n");
            return -1;
        }
    }
    if(ul_Bandwidth_present)
    {
        if(0 != ul_Bandwidth_Unpack(bits, idx))
        {
            printf("SystemInformationBlockType2::freqInfo:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != additionalSpectrumEmission.Unpack(bits, idx))
        {
            printf("SystemInformationBlockType2::freqInfo:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string SystemInformationBlockType2::freqInfo::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "freqInfo:\n";
    if(ul_CarrierFreq_IsPresent())
        out += ul_CarrierFreq_ToString(indent+1);
    if(ul_Bandwidth_IsPresent())
        out += ul_Bandwidth_ToString(indent+1);
    out += additionalSpectrumEmission_ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType2::freqInfo::ToStringNoNewLines() const
{
    std::string out = "freqInfo:";
    if(ul_CarrierFreq_IsPresent())
        out += ul_CarrierFreq_ToStringNoNewLines();
    if(ul_Bandwidth_IsPresent())
        out += ul_Bandwidth_ToStringNoNewLines();
    out += additionalSpectrumEmission_ToStringNoNewLines();
    return out;
}

ARFCN_ValueEUTRA* SystemInformationBlockType2::freqInfo::ul_CarrierFreq_Set()
{
    ul_CarrierFreq_present = true;
    return &ul_CarrierFreq;
}

int SystemInformationBlockType2::freqInfo::ul_CarrierFreq_Set(ARFCN_ValueEUTRA &value)
{
    ul_CarrierFreq_present = true;
    ul_CarrierFreq = value;
    return 0;
}

const ARFCN_ValueEUTRA& SystemInformationBlockType2::freqInfo::ul_CarrierFreq_Get() const
{
    return ul_CarrierFreq;
}

std::string SystemInformationBlockType2::freqInfo::ul_CarrierFreq_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ul_CarrierFreq:\n";
    out += ul_CarrierFreq.ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType2::freqInfo::ul_CarrierFreq_ToStringNoNewLines() const
{
    std::string out = "ul_CarrierFreq:";
    out += ul_CarrierFreq.ToStringNoNewLines();
    return out;
}

int SystemInformationBlockType2::freqInfo::ul_CarrierFreq_Clear()
{
    ul_CarrierFreq_present = false;
    return 0;
}

bool SystemInformationBlockType2::freqInfo::ul_CarrierFreq_IsPresent() const
{
    return ul_CarrierFreq_present;
}

int SystemInformationBlockType2::freqInfo::ul_Bandwidth_Pack(std::vector<uint8_t> &bits)
{
    uint32_t N_bits = 3;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((ul_Bandwidth_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int SystemInformationBlockType2::freqInfo::ul_Bandwidth_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return ul_Bandwidth_Unpack(bits, idx);
}

int SystemInformationBlockType2::freqInfo::ul_Bandwidth_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 3;
    if((idx + N_bits) > bits.size())
    {
        printf("SystemInformationBlockType2::freqInfo::ul_Bandwidth_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 5)
    {
        printf("SystemInformationBlockType2::freqInfo::ul_Bandwidth_Unpack() max failure\n");
        return -1;
    }
    ul_Bandwidth_internal_value = (ul_Bandwidth_Enum)packed_val;
    ul_Bandwidth_present = true;
    return 0;
}

SystemInformationBlockType2::freqInfo::ul_Bandwidth_Enum SystemInformationBlockType2::freqInfo::ul_Bandwidth_Value() const
{
    if(ul_Bandwidth_present)
        return ul_Bandwidth_internal_value;
    return (SystemInformationBlockType2::freqInfo::ul_Bandwidth_Enum)0;
}

int SystemInformationBlockType2::freqInfo::ul_Bandwidth_SetValue(ul_Bandwidth_Enum value)
{
    ul_Bandwidth_internal_value = value;
    ul_Bandwidth_present = true;
    return 0;
}

int SystemInformationBlockType2::freqInfo::ul_Bandwidth_SetValue(std::string value)
{
    if("n6" == value)
    {
        ul_Bandwidth_internal_value = k_ul_Bandwidth_n6;
        ul_Bandwidth_present = true;
        return 0;
    }
    if("n15" == value)
    {
        ul_Bandwidth_internal_value = k_ul_Bandwidth_n15;
        ul_Bandwidth_present = true;
        return 0;
    }
    if("n25" == value)
    {
        ul_Bandwidth_internal_value = k_ul_Bandwidth_n25;
        ul_Bandwidth_present = true;
        return 0;
    }
    if("n50" == value)
    {
        ul_Bandwidth_internal_value = k_ul_Bandwidth_n50;
        ul_Bandwidth_present = true;
        return 0;
    }
    if("n75" == value)
    {
        ul_Bandwidth_internal_value = k_ul_Bandwidth_n75;
        ul_Bandwidth_present = true;
        return 0;
    }
    if("n100" == value)
    {
        ul_Bandwidth_internal_value = k_ul_Bandwidth_n100;
        ul_Bandwidth_present = true;
        return 0;
    }
    return 1;
}

std::string SystemInformationBlockType2::freqInfo::ul_Bandwidth_ValueToString(ul_Bandwidth_Enum value) const
{
    if(k_ul_Bandwidth_n6 == value)
        return "n6";
    if(k_ul_Bandwidth_n15 == value)
        return "n15";
    if(k_ul_Bandwidth_n25 == value)
        return "n25";
    if(k_ul_Bandwidth_n50 == value)
        return "n50";
    if(k_ul_Bandwidth_n75 == value)
        return "n75";
    if(k_ul_Bandwidth_n100 == value)
        return "n100";
    return "";
}

uint64_t SystemInformationBlockType2::freqInfo::ul_Bandwidth_NumberOfValues() const
{
    return 6;
}

std::string SystemInformationBlockType2::freqInfo::ul_Bandwidth_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ul_Bandwidth = " + ul_Bandwidth_ValueToString(ul_Bandwidth_internal_value) + "\n";
    return out;
}

std::string SystemInformationBlockType2::freqInfo::ul_Bandwidth_ToStringNoNewLines() const
{
    std::string out = "ul_Bandwidth=" + ul_Bandwidth_ValueToString(ul_Bandwidth_internal_value) + ",";
    return out;
}

int SystemInformationBlockType2::freqInfo::ul_Bandwidth_Clear()
{
    ul_Bandwidth_present = false;
    return 0;
}

bool SystemInformationBlockType2::freqInfo::ul_Bandwidth_IsPresent() const
{
    return ul_Bandwidth_present;
}

AdditionalSpectrumEmission* SystemInformationBlockType2::freqInfo::additionalSpectrumEmission_Set()
{
    additionalSpectrumEmission_present = true;
    return &additionalSpectrumEmission;
}

int SystemInformationBlockType2::freqInfo::additionalSpectrumEmission_Set(AdditionalSpectrumEmission &value)
{
    additionalSpectrumEmission_present = true;
    additionalSpectrumEmission = value;
    return 0;
}

const AdditionalSpectrumEmission& SystemInformationBlockType2::freqInfo::additionalSpectrumEmission_Get() const
{
    return additionalSpectrumEmission;
}

std::string SystemInformationBlockType2::freqInfo::additionalSpectrumEmission_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "additionalSpectrumEmission:\n";
    out += additionalSpectrumEmission.ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType2::freqInfo::additionalSpectrumEmission_ToStringNoNewLines() const
{
    std::string out = "additionalSpectrumEmission:";
    out += additionalSpectrumEmission.ToStringNoNewLines();
    return out;
}

int SystemInformationBlockType2::freqInfo::additionalSpectrumEmission_Clear()
{
    additionalSpectrumEmission_present = false;
    return 0;
}

bool SystemInformationBlockType2::freqInfo::additionalSpectrumEmission_IsPresent() const
{
    return additionalSpectrumEmission_present;
}

MBSFN_SubframeConfigList* SystemInformationBlockType2::mbsfn_SubframeConfigList_Set()
{
    mbsfn_SubframeConfigList_present = true;
    return &mbsfn_SubframeConfigList;
}

int SystemInformationBlockType2::mbsfn_SubframeConfigList_Set(MBSFN_SubframeConfigList &value)
{
    mbsfn_SubframeConfigList_present = true;
    mbsfn_SubframeConfigList = value;
    return 0;
}

const MBSFN_SubframeConfigList& SystemInformationBlockType2::mbsfn_SubframeConfigList_Get() const
{
    return mbsfn_SubframeConfigList;
}

std::string SystemInformationBlockType2::mbsfn_SubframeConfigList_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "mbsfn_SubframeConfigList:\n";
    out += mbsfn_SubframeConfigList.ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType2::mbsfn_SubframeConfigList_ToStringNoNewLines() const
{
    std::string out = "mbsfn_SubframeConfigList:";
    out += mbsfn_SubframeConfigList.ToStringNoNewLines();
    return out;
}

int SystemInformationBlockType2::mbsfn_SubframeConfigList_Clear()
{
    mbsfn_SubframeConfigList_present = false;
    return 0;
}

bool SystemInformationBlockType2::mbsfn_SubframeConfigList_IsPresent() const
{
    return mbsfn_SubframeConfigList_present;
}

TimeAlignmentTimer* SystemInformationBlockType2::timeAlignmentTimerCommon_Set()
{
    timeAlignmentTimerCommon_present = true;
    return &timeAlignmentTimerCommon;
}

int SystemInformationBlockType2::timeAlignmentTimerCommon_Set(TimeAlignmentTimer &value)
{
    timeAlignmentTimerCommon_present = true;
    timeAlignmentTimerCommon = value;
    return 0;
}

const TimeAlignmentTimer& SystemInformationBlockType2::timeAlignmentTimerCommon_Get() const
{
    return timeAlignmentTimerCommon;
}

std::string SystemInformationBlockType2::timeAlignmentTimerCommon_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "timeAlignmentTimerCommon:\n";
    out += timeAlignmentTimerCommon.ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType2::timeAlignmentTimerCommon_ToStringNoNewLines() const
{
    std::string out = "timeAlignmentTimerCommon:";
    out += timeAlignmentTimerCommon.ToStringNoNewLines();
    return out;
}

int SystemInformationBlockType2::timeAlignmentTimerCommon_Clear()
{
    timeAlignmentTimerCommon_present = false;
    return 0;
}

bool SystemInformationBlockType2::timeAlignmentTimerCommon_IsPresent() const
{
    return timeAlignmentTimerCommon_present;
}

int SystemInformationBlockType2::lateNonCriticalExtension_Pack(std::vector<uint8_t> &bits)
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

int SystemInformationBlockType2::lateNonCriticalExtension_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return lateNonCriticalExtension_Unpack(bits, idx);
}

int SystemInformationBlockType2::lateNonCriticalExtension_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
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
        printf("SystemInformationBlockType2::lateNonCriticalExtension_Unpack() index out of bounds\n");
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

std::vector<uint8_t> SystemInformationBlockType2::lateNonCriticalExtension_Value() const
{
    if(lateNonCriticalExtension_present)
        return lateNonCriticalExtension_internal_value;
    std::vector<uint8_t> tmp;
    return tmp;
}

int SystemInformationBlockType2::lateNonCriticalExtension_SetValue(std::vector<uint8_t> value)
{
    lateNonCriticalExtension_internal_value = value;
    lateNonCriticalExtension_present = true;
    return 0;
}

std::string SystemInformationBlockType2::lateNonCriticalExtension_ToString(uint32_t indent) const
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

std::string SystemInformationBlockType2::lateNonCriticalExtension_ToStringNoNewLines() const
{
    std::string out = "lateNonCriticalExtension={";
    for(auto byte : lateNonCriticalExtension_internal_value)
        out += std::to_string(byte) + ",";
    out = out.substr(0, out.length()-1) + "},";
    return out;
}

int SystemInformationBlockType2::lateNonCriticalExtension_Clear()
{
    lateNonCriticalExtension_present = false;
    return 0;
}

bool SystemInformationBlockType2::lateNonCriticalExtension_IsPresent() const
{
    return lateNonCriticalExtension_present;
}

AC_BarringConfig* SystemInformationBlockType2::ssac_BarringForMMTEL_Voice_r9_Set()
{
    ssac_BarringForMMTEL_Voice_r9_present = true;
    return &ssac_BarringForMMTEL_Voice_r9;
}

int SystemInformationBlockType2::ssac_BarringForMMTEL_Voice_r9_Set(AC_BarringConfig &value)
{
    ssac_BarringForMMTEL_Voice_r9_present = true;
    ssac_BarringForMMTEL_Voice_r9 = value;
    return 0;
}

const AC_BarringConfig& SystemInformationBlockType2::ssac_BarringForMMTEL_Voice_r9_Get() const
{
    return ssac_BarringForMMTEL_Voice_r9;
}

std::string SystemInformationBlockType2::ssac_BarringForMMTEL_Voice_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ssac_BarringForMMTEL_Voice_r9:\n";
    out += ssac_BarringForMMTEL_Voice_r9.ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType2::ssac_BarringForMMTEL_Voice_r9_ToStringNoNewLines() const
{
    std::string out = "ssac_BarringForMMTEL_Voice_r9:";
    out += ssac_BarringForMMTEL_Voice_r9.ToStringNoNewLines();
    return out;
}

int SystemInformationBlockType2::ssac_BarringForMMTEL_Voice_r9_Clear()
{
    ssac_BarringForMMTEL_Voice_r9_present = false;
    return 0;
}

bool SystemInformationBlockType2::ssac_BarringForMMTEL_Voice_r9_IsPresent() const
{
    return ssac_BarringForMMTEL_Voice_r9_present;
}

AC_BarringConfig* SystemInformationBlockType2::ssac_BarringForMMTEL_Video_r9_Set()
{
    ssac_BarringForMMTEL_Video_r9_present = true;
    return &ssac_BarringForMMTEL_Video_r9;
}

int SystemInformationBlockType2::ssac_BarringForMMTEL_Video_r9_Set(AC_BarringConfig &value)
{
    ssac_BarringForMMTEL_Video_r9_present = true;
    ssac_BarringForMMTEL_Video_r9 = value;
    return 0;
}

const AC_BarringConfig& SystemInformationBlockType2::ssac_BarringForMMTEL_Video_r9_Get() const
{
    return ssac_BarringForMMTEL_Video_r9;
}

std::string SystemInformationBlockType2::ssac_BarringForMMTEL_Video_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ssac_BarringForMMTEL_Video_r9:\n";
    out += ssac_BarringForMMTEL_Video_r9.ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType2::ssac_BarringForMMTEL_Video_r9_ToStringNoNewLines() const
{
    std::string out = "ssac_BarringForMMTEL_Video_r9:";
    out += ssac_BarringForMMTEL_Video_r9.ToStringNoNewLines();
    return out;
}

int SystemInformationBlockType2::ssac_BarringForMMTEL_Video_r9_Clear()
{
    ssac_BarringForMMTEL_Video_r9_present = false;
    return 0;
}

bool SystemInformationBlockType2::ssac_BarringForMMTEL_Video_r9_IsPresent() const
{
    return ssac_BarringForMMTEL_Video_r9_present;
}

AC_BarringConfig* SystemInformationBlockType2::ac_BarringForCSFB_r10_Set()
{
    ac_BarringForCSFB_r10_present = true;
    return &ac_BarringForCSFB_r10;
}

int SystemInformationBlockType2::ac_BarringForCSFB_r10_Set(AC_BarringConfig &value)
{
    ac_BarringForCSFB_r10_present = true;
    ac_BarringForCSFB_r10 = value;
    return 0;
}

const AC_BarringConfig& SystemInformationBlockType2::ac_BarringForCSFB_r10_Get() const
{
    return ac_BarringForCSFB_r10;
}

std::string SystemInformationBlockType2::ac_BarringForCSFB_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ac_BarringForCSFB_r10:\n";
    out += ac_BarringForCSFB_r10.ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType2::ac_BarringForCSFB_r10_ToStringNoNewLines() const
{
    std::string out = "ac_BarringForCSFB_r10:";
    out += ac_BarringForCSFB_r10.ToStringNoNewLines();
    return out;
}

int SystemInformationBlockType2::ac_BarringForCSFB_r10_Clear()
{
    ac_BarringForCSFB_r10_present = false;
    return 0;
}

bool SystemInformationBlockType2::ac_BarringForCSFB_r10_IsPresent() const
{
    return ac_BarringForCSFB_r10_present;
}

