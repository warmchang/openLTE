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

#include "SystemInformationBlockType8.h"

#include <cmath>

int SystemInformationBlockType8::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator
    bool has_extension = false;
    if(lateNonCriticalExtension_IsPresent() || csfb_SupportForDualRxUEs_r9_IsPresent() || cellReselectionParametersHRPD_v920_IsPresent() || cellReselectionParameters1XRTT_v920_IsPresent() || csfb_RegistrationParam1XRTT_v920_IsPresent() || ac_BarringConfig1XRTT_r9_IsPresent() || csfb_DualRxTxSupport_r10_IsPresent())
    {
        bits.push_back(1);
        has_extension = true;
    }else{
        bits.push_back(0);
    }

    // Optional indicators
    bits.push_back(systemTimeInfo_IsPresent());
    bits.push_back(searchWindowSize_IsPresent());
    bits.push_back(parametersHRPD_value.IsPresent());
    bits.push_back(parameters1XRTT_value.IsPresent());

    // Fields
    if(systemTimeInfo_IsPresent())
    {
        if(0 != systemTimeInfo.Pack(bits))
        {
            printf("SystemInformationBlockType8:: field pack failure\n");
            return -1;
        }
    }
    if(searchWindowSize_IsPresent())
    {
        if(0 != searchWindowSize_Pack(bits))
        {
            printf("SystemInformationBlockType8:: field pack failure\n");
            return -1;
        }
    }
    if(parametersHRPD_value.IsPresent())
    {
        if(0 != parametersHRPD_value.Pack(bits))
        {
            printf("SystemInformationBlockType8:: field pack failure\n");
            return -1;
        }
    }
    if(parameters1XRTT_value.IsPresent())
    {
        if(0 != parameters1XRTT_value.Pack(bits))
        {
            printf("SystemInformationBlockType8:: field pack failure\n");
            return -1;
        }
    }

    // Extension
    if(has_extension)
    {
        // Number of extension fields
        if(6 < 64)
        {
            bits.push_back(0);
            for(uint32_t i=0; i<6; i++)
                bits.push_back((6 >> (6-i-1)) & 1);
        }else{
            printf("SystemInformationBlockType8:: Extension list size too large failure\n");
            return -1;
        }

        // Extension field presence indicators
        bits.push_back(lateNonCriticalExtension_IsPresent());
        bits.push_back(csfb_SupportForDualRxUEs_r9_IsPresent());
        bits.push_back(cellReselectionParametersHRPD_v920_IsPresent());
        bits.push_back(cellReselectionParameters1XRTT_v920_IsPresent());
        bits.push_back(csfb_RegistrationParam1XRTT_v920_IsPresent());
        bits.push_back(ac_BarringConfig1XRTT_r9_IsPresent());
        bits.push_back(csfb_DualRxTxSupport_r10_IsPresent());

        // Extension fields
        if(lateNonCriticalExtension_IsPresent())
        {
            std::vector<uint8_t> field_bits;
            if(0 != lateNonCriticalExtension_Pack(field_bits))
            {
                printf("SystemInformationBlockType8:: field pack failure\n");
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
        if(csfb_SupportForDualRxUEs_r9_IsPresent())
        {
            std::vector<uint8_t> field_bits;
            if(0 != csfb_SupportForDualRxUEs_r9_Pack(field_bits))
            {
                printf("SystemInformationBlockType8:: field pack failure\n");
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
        if(cellReselectionParametersHRPD_v920_IsPresent())
        {
            std::vector<uint8_t> field_bits;
            if(0 != cellReselectionParametersHRPD_v920.Pack(field_bits))
            {
                printf("SystemInformationBlockType8:: field pack failure\n");
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
        if(cellReselectionParameters1XRTT_v920_IsPresent())
        {
            std::vector<uint8_t> field_bits;
            if(0 != cellReselectionParameters1XRTT_v920.Pack(field_bits))
            {
                printf("SystemInformationBlockType8:: field pack failure\n");
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
        if(csfb_RegistrationParam1XRTT_v920_IsPresent())
        {
            std::vector<uint8_t> field_bits;
            if(0 != csfb_RegistrationParam1XRTT_v920.Pack(field_bits))
            {
                printf("SystemInformationBlockType8:: field pack failure\n");
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
        if(ac_BarringConfig1XRTT_r9_IsPresent())
        {
            std::vector<uint8_t> field_bits;
            if(0 != ac_BarringConfig1XRTT_r9.Pack(field_bits))
            {
                printf("SystemInformationBlockType8:: field pack failure\n");
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
        if(csfb_DualRxTxSupport_r10_IsPresent())
        {
            std::vector<uint8_t> field_bits;
            if(0 != csfb_DualRxTxSupport_r10_Pack(field_bits))
            {
                printf("SystemInformationBlockType8:: field pack failure\n");
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

int SystemInformationBlockType8::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int SystemInformationBlockType8::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("SystemInformationBlockType8::Unpack() index out of bounds for extension\n");
        return -1;
    }
    bool has_extension = bits[idx++];

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("SystemInformationBlockType8::Unpack() index out of bounds for optional indiator systemTimeInfo\n");
        return -1;
    }
    systemTimeInfo_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("SystemInformationBlockType8::Unpack() index out of bounds for optional indiator searchWindowSize\n");
        return -1;
    }
    searchWindowSize_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("SystemInformationBlockType8::Unpack() index out of bounds for optional indiator parametersHRPD\n");
        return -1;
    }
    parametersHRPD_value.SetPresence(bits[idx++]);
    if((idx + 1) > bits.size())
    {
        printf("SystemInformationBlockType8::Unpack() index out of bounds for optional indiator parameters1XRTT\n");
        return -1;
    }
    parameters1XRTT_value.SetPresence(bits[idx++]);

    // Fields
    if(systemTimeInfo_present)
    {
        if(0 != systemTimeInfo.Unpack(bits, idx))
        {
            printf("SystemInformationBlockType8:: field unpack failure\n");
            return -1;
        }
    }
    if(searchWindowSize_present)
    {
        if(0 != searchWindowSize_Unpack(bits, idx))
        {
            printf("SystemInformationBlockType8:: field unpack failure\n");
            return -1;
        }
    }
    if(parametersHRPD_value.IsPresent())
    {
        if(0 != parametersHRPD_value.Unpack(bits, idx))
        {
            printf("SystemInformationBlockType8:: field unpack failure\n");
            return -1;
        }
    }
    if(parameters1XRTT_value.IsPresent())
    {
        if(0 != parameters1XRTT_value.Unpack(bits, idx))
        {
            printf("SystemInformationBlockType8:: field unpack failure\n");
            return -1;
        }
    }

    // Extension
    if(has_extension)
    {
        if((idx + 7) > bits.size())
        {
            printf("SystemInformationBlockType8::Unpack() index out of bounds for extension size\n");
            return -1;
        }
        // Number of extension fields
        if(bits[idx++] != 0)
        {
            printf("SystemInformationBlockType8:: Extension list size too large failure\n");
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
                printf("SystemInformationBlockType8::Unpack() index out of bounds for optional indiator lateNonCriticalExtension\n");
                return -1;
            }
            lateNonCriticalExtension_present = bits[idx++];
        }
        if(opt_ind_count++ < N_ext_fields)
        {
            if((idx + 1) > bits.size())
            {
                printf("SystemInformationBlockType8::Unpack() index out of bounds for optional indiator csfb_SupportForDualRxUEs_r9\n");
                return -1;
            }
            csfb_SupportForDualRxUEs_r9_present = bits[idx++];
        }
        if(opt_ind_count++ < N_ext_fields)
        {
            if((idx + 1) > bits.size())
            {
                printf("SystemInformationBlockType8::Unpack() index out of bounds for optional indiator cellReselectionParametersHRPD_v920\n");
                return -1;
            }
            cellReselectionParametersHRPD_v920_present = bits[idx++];
        }
        if(opt_ind_count++ < N_ext_fields)
        {
            if((idx + 1) > bits.size())
            {
                printf("SystemInformationBlockType8::Unpack() index out of bounds for optional indiator cellReselectionParameters1XRTT_v920\n");
                return -1;
            }
            cellReselectionParameters1XRTT_v920_present = bits[idx++];
        }
        if(opt_ind_count++ < N_ext_fields)
        {
            if((idx + 1) > bits.size())
            {
                printf("SystemInformationBlockType8::Unpack() index out of bounds for optional indiator csfb_RegistrationParam1XRTT_v920\n");
                return -1;
            }
            csfb_RegistrationParam1XRTT_v920_present = bits[idx++];
        }
        if(opt_ind_count++ < N_ext_fields)
        {
            if((idx + 1) > bits.size())
            {
                printf("SystemInformationBlockType8::Unpack() index out of bounds for optional indiator ac_BarringConfig1XRTT_r9\n");
                return -1;
            }
            ac_BarringConfig1XRTT_r9_present = bits[idx++];
        }
        if(opt_ind_count++ < N_ext_fields)
        {
            if((idx + 1) > bits.size())
            {
                printf("SystemInformationBlockType8::Unpack() index out of bounds for optional indiator csfb_DualRxTxSupport_r10\n");
                return -1;
            }
            csfb_DualRxTxSupport_r10_present = bits[idx++];
        }
        if((idx + (N_ext_fields - opt_ind_count)) > bits.size())
        {
            printf("SystemInformationBlockType8::Unpack() index out of bounds for extension optional indicators\n");
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
                printf("SystemInformationBlockType8:: field unpack failure\n");
                return -1;
            }
            idx = orig_idx + (N_octets * 8);
        }
        if(csfb_SupportForDualRxUEs_r9_present)
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
            if(0 != csfb_SupportForDualRxUEs_r9_Unpack(bits, idx))
            {
                printf("SystemInformationBlockType8:: field unpack failure\n");
                return -1;
            }
            idx = orig_idx + (N_octets * 8);
        }
        if(cellReselectionParametersHRPD_v920_present)
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
            if(0 != cellReselectionParametersHRPD_v920.Unpack(bits, idx))
            {
                printf("SystemInformationBlockType8:: field unpack failure\n");
                return -1;
            }
            idx = orig_idx + (N_octets * 8);
        }
        if(cellReselectionParameters1XRTT_v920_present)
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
            if(0 != cellReselectionParameters1XRTT_v920.Unpack(bits, idx))
            {
                printf("SystemInformationBlockType8:: field unpack failure\n");
                return -1;
            }
            idx = orig_idx + (N_octets * 8);
        }
        if(csfb_RegistrationParam1XRTT_v920_present)
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
            if(0 != csfb_RegistrationParam1XRTT_v920.Unpack(bits, idx))
            {
                printf("SystemInformationBlockType8:: field unpack failure\n");
                return -1;
            }
            idx = orig_idx + (N_octets * 8);
        }
        if(ac_BarringConfig1XRTT_r9_present)
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
            if(0 != ac_BarringConfig1XRTT_r9.Unpack(bits, idx))
            {
                printf("SystemInformationBlockType8:: field unpack failure\n");
                return -1;
            }
            idx = orig_idx + (N_octets * 8);
        }
        if(csfb_DualRxTxSupport_r10_present)
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
            if(0 != csfb_DualRxTxSupport_r10_Unpack(bits, idx))
            {
                printf("SystemInformationBlockType8:: field unpack failure\n");
                return -1;
            }
            idx = orig_idx + (N_octets * 8);
        }
        for(uint32_t i=7; i<N_ext_fields; i++)
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
            printf("SystemInformationBlockType8::Unpack() index out of bounds for extension fields\n");
            return -1;
        }
            idx += N_octets * 8;
        }
    }
    return 0;
}

std::string SystemInformationBlockType8::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "SystemInformationBlockType8:\n";
    if(systemTimeInfo_IsPresent())
        out += systemTimeInfo_ToString(indent+1);
    if(searchWindowSize_IsPresent())
        out += searchWindowSize_ToString(indent+1);
    if(parametersHRPD_value.IsPresent())
        out += parametersHRPD_value.ToString(indent+1);
    if(parameters1XRTT_value.IsPresent())
        out += parameters1XRTT_value.ToString(indent+1);
    if(lateNonCriticalExtension_IsPresent())
        out += lateNonCriticalExtension_ToString(indent+1);
    if(csfb_SupportForDualRxUEs_r9_IsPresent())
        out += csfb_SupportForDualRxUEs_r9_ToString(indent+1);
    if(cellReselectionParametersHRPD_v920_IsPresent())
        out += cellReselectionParametersHRPD_v920_ToString(indent+1);
    if(cellReselectionParameters1XRTT_v920_IsPresent())
        out += cellReselectionParameters1XRTT_v920_ToString(indent+1);
    if(csfb_RegistrationParam1XRTT_v920_IsPresent())
        out += csfb_RegistrationParam1XRTT_v920_ToString(indent+1);
    if(ac_BarringConfig1XRTT_r9_IsPresent())
        out += ac_BarringConfig1XRTT_r9_ToString(indent+1);
    if(csfb_DualRxTxSupport_r10_IsPresent())
        out += csfb_DualRxTxSupport_r10_ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType8::ToStringNoNewLines() const
{
    std::string out = "SystemInformationBlockType8:";
    if(systemTimeInfo_IsPresent())
        out += systemTimeInfo_ToStringNoNewLines();
    if(searchWindowSize_IsPresent())
        out += searchWindowSize_ToStringNoNewLines();
    if(parametersHRPD_value.IsPresent())
        out += parametersHRPD_value.ToStringNoNewLines();
    if(parameters1XRTT_value.IsPresent())
        out += parameters1XRTT_value.ToStringNoNewLines();
    if(lateNonCriticalExtension_IsPresent())
        out += lateNonCriticalExtension_ToStringNoNewLines();
    if(csfb_SupportForDualRxUEs_r9_IsPresent())
        out += csfb_SupportForDualRxUEs_r9_ToStringNoNewLines();
    if(cellReselectionParametersHRPD_v920_IsPresent())
        out += cellReselectionParametersHRPD_v920_ToStringNoNewLines();
    if(cellReselectionParameters1XRTT_v920_IsPresent())
        out += cellReselectionParameters1XRTT_v920_ToStringNoNewLines();
    if(csfb_RegistrationParam1XRTT_v920_IsPresent())
        out += csfb_RegistrationParam1XRTT_v920_ToStringNoNewLines();
    if(ac_BarringConfig1XRTT_r9_IsPresent())
        out += ac_BarringConfig1XRTT_r9_ToStringNoNewLines();
    if(csfb_DualRxTxSupport_r10_IsPresent())
        out += csfb_DualRxTxSupport_r10_ToStringNoNewLines();
    return out;
}

SystemTimeInfoCDMA2000* SystemInformationBlockType8::systemTimeInfo_Set()
{
    systemTimeInfo_present = true;
    return &systemTimeInfo;
}

int SystemInformationBlockType8::systemTimeInfo_Set(SystemTimeInfoCDMA2000 &value)
{
    systemTimeInfo_present = true;
    systemTimeInfo = value;
    return 0;
}

const SystemTimeInfoCDMA2000& SystemInformationBlockType8::systemTimeInfo_Get() const
{
    return systemTimeInfo;
}

std::string SystemInformationBlockType8::systemTimeInfo_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "systemTimeInfo:\n";
    out += systemTimeInfo.ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType8::systemTimeInfo_ToStringNoNewLines() const
{
    std::string out = "systemTimeInfo:";
    out += systemTimeInfo.ToStringNoNewLines();
    return out;
}

int SystemInformationBlockType8::systemTimeInfo_Clear()
{
    systemTimeInfo_present = false;
    return 0;
}

bool SystemInformationBlockType8::systemTimeInfo_IsPresent() const
{
    return systemTimeInfo_present;
}

int SystemInformationBlockType8::searchWindowSize_Pack(std::vector<uint8_t> &bits)
{
    int64_t val_to_pack = searchWindowSize_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (15 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int SystemInformationBlockType8::searchWindowSize_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return searchWindowSize_Unpack(bits, idx);
}

int SystemInformationBlockType8::searchWindowSize_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (15 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("SystemInformationBlockType8::searchWindowSize_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    searchWindowSize_internal_value = packed_val + 0;
    searchWindowSize_present = true;
    return 0;
}

int64_t SystemInformationBlockType8::searchWindowSize_Value() const
{
    if(searchWindowSize_present)
        return searchWindowSize_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int SystemInformationBlockType8::searchWindowSize_SetValue(int64_t value)
{
    if(value < 0 || value > 15)
    {
        printf("SystemInformationBlockType8::searchWindowSize_SetValue() range failure\n");
        return -1;
    }
    searchWindowSize_internal_value = value;
    searchWindowSize_present = true;
    return 0;
}

std::string SystemInformationBlockType8::searchWindowSize_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "searchWindowSize = " + std::to_string(searchWindowSize_internal_value) + "\n";
    return out;
}

std::string SystemInformationBlockType8::searchWindowSize_ToStringNoNewLines() const
{
    std::string out = "searchWindowSize=" + std::to_string(searchWindowSize_internal_value) + ",";
    return out;
}

int SystemInformationBlockType8::searchWindowSize_Clear()
{
    searchWindowSize_present = false;
    return 0;
}

bool SystemInformationBlockType8::searchWindowSize_IsPresent() const
{
    return searchWindowSize_present;
}

int SystemInformationBlockType8::parametersHRPD::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(cellReselectionParametersHRPD_IsPresent());

    // Fields
    {
        if(0 != preRegistrationInfoHRPD.Pack(bits))
        {
            printf("SystemInformationBlockType8::parametersHRPD:: field pack failure\n");
            return -1;
        }
    }
    if(cellReselectionParametersHRPD_IsPresent())
    {
        if(0 != cellReselectionParametersHRPD.Pack(bits))
        {
            printf("SystemInformationBlockType8::parametersHRPD:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int SystemInformationBlockType8::parametersHRPD::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int SystemInformationBlockType8::parametersHRPD::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("parametersHRPD::Unpack() index out of bounds for optional indiator cellReselectionParametersHRPD\n");
        return -1;
    }
    cellReselectionParametersHRPD_present = bits[idx++];

    // Fields
    {
        if(0 != preRegistrationInfoHRPD.Unpack(bits, idx))
        {
            printf("SystemInformationBlockType8::parametersHRPD:: field unpack failure\n");
            return -1;
        }
    }
    if(cellReselectionParametersHRPD_present)
    {
        if(0 != cellReselectionParametersHRPD.Unpack(bits, idx))
        {
            printf("SystemInformationBlockType8::parametersHRPD:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string SystemInformationBlockType8::parametersHRPD::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "parametersHRPD:\n";
    out += preRegistrationInfoHRPD_ToString(indent+1);
    if(cellReselectionParametersHRPD_IsPresent())
        out += cellReselectionParametersHRPD_ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType8::parametersHRPD::ToStringNoNewLines() const
{
    std::string out = "parametersHRPD:";
    out += preRegistrationInfoHRPD_ToStringNoNewLines();
    if(cellReselectionParametersHRPD_IsPresent())
        out += cellReselectionParametersHRPD_ToStringNoNewLines();
    return out;
}

int SystemInformationBlockType8::parametersHRPD::Set()
{
    present = true;
    return 0;
}

int SystemInformationBlockType8::parametersHRPD::SetPresence(bool is_present)
{
    present = is_present;
    return 0;
}

int SystemInformationBlockType8::parametersHRPD::Clear()
{
    present = false;
    return 0;
}

bool SystemInformationBlockType8::parametersHRPD::IsPresent() const
{
    return present;
}

PreRegistrationInfoHRPD* SystemInformationBlockType8::parametersHRPD::preRegistrationInfoHRPD_Set()
{
    preRegistrationInfoHRPD_present = true;
    return &preRegistrationInfoHRPD;
}

int SystemInformationBlockType8::parametersHRPD::preRegistrationInfoHRPD_Set(PreRegistrationInfoHRPD &value)
{
    preRegistrationInfoHRPD_present = true;
    preRegistrationInfoHRPD = value;
    return 0;
}

const PreRegistrationInfoHRPD& SystemInformationBlockType8::parametersHRPD::preRegistrationInfoHRPD_Get() const
{
    return preRegistrationInfoHRPD;
}

std::string SystemInformationBlockType8::parametersHRPD::preRegistrationInfoHRPD_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "preRegistrationInfoHRPD:\n";
    out += preRegistrationInfoHRPD.ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType8::parametersHRPD::preRegistrationInfoHRPD_ToStringNoNewLines() const
{
    std::string out = "preRegistrationInfoHRPD:";
    out += preRegistrationInfoHRPD.ToStringNoNewLines();
    return out;
}

int SystemInformationBlockType8::parametersHRPD::preRegistrationInfoHRPD_Clear()
{
    preRegistrationInfoHRPD_present = false;
    return 0;
}

bool SystemInformationBlockType8::parametersHRPD::preRegistrationInfoHRPD_IsPresent() const
{
    return preRegistrationInfoHRPD_present;
}

CellReselectionParametersCDMA2000* SystemInformationBlockType8::parametersHRPD::cellReselectionParametersHRPD_Set()
{
    cellReselectionParametersHRPD_present = true;
    return &cellReselectionParametersHRPD;
}

int SystemInformationBlockType8::parametersHRPD::cellReselectionParametersHRPD_Set(CellReselectionParametersCDMA2000 &value)
{
    cellReselectionParametersHRPD_present = true;
    cellReselectionParametersHRPD = value;
    return 0;
}

const CellReselectionParametersCDMA2000& SystemInformationBlockType8::parametersHRPD::cellReselectionParametersHRPD_Get() const
{
    return cellReselectionParametersHRPD;
}

std::string SystemInformationBlockType8::parametersHRPD::cellReselectionParametersHRPD_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cellReselectionParametersHRPD:\n";
    out += cellReselectionParametersHRPD.ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType8::parametersHRPD::cellReselectionParametersHRPD_ToStringNoNewLines() const
{
    std::string out = "cellReselectionParametersHRPD:";
    out += cellReselectionParametersHRPD.ToStringNoNewLines();
    return out;
}

int SystemInformationBlockType8::parametersHRPD::cellReselectionParametersHRPD_Clear()
{
    cellReselectionParametersHRPD_present = false;
    return 0;
}

bool SystemInformationBlockType8::parametersHRPD::cellReselectionParametersHRPD_IsPresent() const
{
    return cellReselectionParametersHRPD_present;
}

int SystemInformationBlockType8::parameters1XRTT::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(csfb_RegistrationParam1XRTT_IsPresent());
    bits.push_back(longCodeState1XRTT_IsPresent());
    bits.push_back(cellReselectionParameters1XRTT_IsPresent());

    // Fields
    if(csfb_RegistrationParam1XRTT_IsPresent())
    {
        if(0 != csfb_RegistrationParam1XRTT.Pack(bits))
        {
            printf("SystemInformationBlockType8::parameters1XRTT:: field pack failure\n");
            return -1;
        }
    }
    if(longCodeState1XRTT_IsPresent())
    {
        if(0 != longCodeState1XRTT_Pack(bits))
        {
            printf("SystemInformationBlockType8::parameters1XRTT:: field pack failure\n");
            return -1;
        }
    }
    if(cellReselectionParameters1XRTT_IsPresent())
    {
        if(0 != cellReselectionParameters1XRTT.Pack(bits))
        {
            printf("SystemInformationBlockType8::parameters1XRTT:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int SystemInformationBlockType8::parameters1XRTT::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int SystemInformationBlockType8::parameters1XRTT::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("parameters1XRTT::Unpack() index out of bounds for optional indiator csfb_RegistrationParam1XRTT\n");
        return -1;
    }
    csfb_RegistrationParam1XRTT_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("parameters1XRTT::Unpack() index out of bounds for optional indiator longCodeState1XRTT\n");
        return -1;
    }
    longCodeState1XRTT_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("parameters1XRTT::Unpack() index out of bounds for optional indiator cellReselectionParameters1XRTT\n");
        return -1;
    }
    cellReselectionParameters1XRTT_present = bits[idx++];

    // Fields
    if(csfb_RegistrationParam1XRTT_present)
    {
        if(0 != csfb_RegistrationParam1XRTT.Unpack(bits, idx))
        {
            printf("SystemInformationBlockType8::parameters1XRTT:: field unpack failure\n");
            return -1;
        }
    }
    if(longCodeState1XRTT_present)
    {
        if(0 != longCodeState1XRTT_Unpack(bits, idx))
        {
            printf("SystemInformationBlockType8::parameters1XRTT:: field unpack failure\n");
            return -1;
        }
    }
    if(cellReselectionParameters1XRTT_present)
    {
        if(0 != cellReselectionParameters1XRTT.Unpack(bits, idx))
        {
            printf("SystemInformationBlockType8::parameters1XRTT:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string SystemInformationBlockType8::parameters1XRTT::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "parameters1XRTT:\n";
    if(csfb_RegistrationParam1XRTT_IsPresent())
        out += csfb_RegistrationParam1XRTT_ToString(indent+1);
    if(longCodeState1XRTT_IsPresent())
        out += longCodeState1XRTT_ToString(indent+1);
    if(cellReselectionParameters1XRTT_IsPresent())
        out += cellReselectionParameters1XRTT_ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType8::parameters1XRTT::ToStringNoNewLines() const
{
    std::string out = "parameters1XRTT:";
    if(csfb_RegistrationParam1XRTT_IsPresent())
        out += csfb_RegistrationParam1XRTT_ToStringNoNewLines();
    if(longCodeState1XRTT_IsPresent())
        out += longCodeState1XRTT_ToStringNoNewLines();
    if(cellReselectionParameters1XRTT_IsPresent())
        out += cellReselectionParameters1XRTT_ToStringNoNewLines();
    return out;
}

int SystemInformationBlockType8::parameters1XRTT::Set()
{
    present = true;
    return 0;
}

int SystemInformationBlockType8::parameters1XRTT::SetPresence(bool is_present)
{
    present = is_present;
    return 0;
}

int SystemInformationBlockType8::parameters1XRTT::Clear()
{
    present = false;
    return 0;
}

bool SystemInformationBlockType8::parameters1XRTT::IsPresent() const
{
    return present;
}

CSFB_RegistrationParam1XRTT* SystemInformationBlockType8::parameters1XRTT::csfb_RegistrationParam1XRTT_Set()
{
    csfb_RegistrationParam1XRTT_present = true;
    return &csfb_RegistrationParam1XRTT;
}

int SystemInformationBlockType8::parameters1XRTT::csfb_RegistrationParam1XRTT_Set(CSFB_RegistrationParam1XRTT &value)
{
    csfb_RegistrationParam1XRTT_present = true;
    csfb_RegistrationParam1XRTT = value;
    return 0;
}

const CSFB_RegistrationParam1XRTT& SystemInformationBlockType8::parameters1XRTT::csfb_RegistrationParam1XRTT_Get() const
{
    return csfb_RegistrationParam1XRTT;
}

std::string SystemInformationBlockType8::parameters1XRTT::csfb_RegistrationParam1XRTT_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "csfb_RegistrationParam1XRTT:\n";
    out += csfb_RegistrationParam1XRTT.ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType8::parameters1XRTT::csfb_RegistrationParam1XRTT_ToStringNoNewLines() const
{
    std::string out = "csfb_RegistrationParam1XRTT:";
    out += csfb_RegistrationParam1XRTT.ToStringNoNewLines();
    return out;
}

int SystemInformationBlockType8::parameters1XRTT::csfb_RegistrationParam1XRTT_Clear()
{
    csfb_RegistrationParam1XRTT_present = false;
    return 0;
}

bool SystemInformationBlockType8::parameters1XRTT::csfb_RegistrationParam1XRTT_IsPresent() const
{
    return csfb_RegistrationParam1XRTT_present;
}

int SystemInformationBlockType8::parameters1XRTT::longCodeState1XRTT_Pack(std::vector<uint8_t> &bits)
{
    uint32_t size = 42;
    if(size < 42 || size > 42)
    {
        printf("SystemInformationBlockType8::parameters1XRTT::longCodeState1XRTT_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((longCodeState1XRTT_internal_value >> (42-i-1)) & 1);
    return 0;
}

int SystemInformationBlockType8::parameters1XRTT::longCodeState1XRTT_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return longCodeState1XRTT_Unpack(bits, idx);
}

int SystemInformationBlockType8::parameters1XRTT::longCodeState1XRTT_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 42;
    if(size < 42 || size > 42)
    {
        printf("SystemInformationBlockType8::parameters1XRTT::longCodeState1XRTT_Unpack() size failure\n");
        return -1;
    }
    longCodeState1XRTT_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("SystemInformationBlockType8::parameters1XRTT::longCodeState1XRTT_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        longCodeState1XRTT_internal_value |= (uint64_t)bits[idx++] << (uint64_t)(42-i-1);
    longCodeState1XRTT_present = true;
    return 0;
}

uint64_t SystemInformationBlockType8::parameters1XRTT::longCodeState1XRTT_Value() const
{
    if(longCodeState1XRTT_present)
        return longCodeState1XRTT_internal_value;
    uint64_t tmp = 0;
    return tmp;
}

int SystemInformationBlockType8::parameters1XRTT::longCodeState1XRTT_SetValue(uint64_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 42)
    {
        printf("SystemInformationBlockType8::parameters1XRTT::longCodeState1XRTT_SetValue() size failure\n");
        return -1;
    }
    longCodeState1XRTT_internal_value = value;
    longCodeState1XRTT_present = true;
    return 0;
}

std::string SystemInformationBlockType8::parameters1XRTT::longCodeState1XRTT_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "longCodeState1XRTT = ";
    out += std::to_string(longCodeState1XRTT_internal_value);
    out += "\n";
    return out;
}

std::string SystemInformationBlockType8::parameters1XRTT::longCodeState1XRTT_ToStringNoNewLines() const
{
    std::string out = "longCodeState1XRTT=";
    out += std::to_string(longCodeState1XRTT_internal_value);
    out += ",";
    return out;
}

int SystemInformationBlockType8::parameters1XRTT::longCodeState1XRTT_Clear()
{
    longCodeState1XRTT_present = false;
    return 0;
}

bool SystemInformationBlockType8::parameters1XRTT::longCodeState1XRTT_IsPresent() const
{
    return longCodeState1XRTT_present;
}

CellReselectionParametersCDMA2000* SystemInformationBlockType8::parameters1XRTT::cellReselectionParameters1XRTT_Set()
{
    cellReselectionParameters1XRTT_present = true;
    return &cellReselectionParameters1XRTT;
}

int SystemInformationBlockType8::parameters1XRTT::cellReselectionParameters1XRTT_Set(CellReselectionParametersCDMA2000 &value)
{
    cellReselectionParameters1XRTT_present = true;
    cellReselectionParameters1XRTT = value;
    return 0;
}

const CellReselectionParametersCDMA2000& SystemInformationBlockType8::parameters1XRTT::cellReselectionParameters1XRTT_Get() const
{
    return cellReselectionParameters1XRTT;
}

std::string SystemInformationBlockType8::parameters1XRTT::cellReselectionParameters1XRTT_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cellReselectionParameters1XRTT:\n";
    out += cellReselectionParameters1XRTT.ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType8::parameters1XRTT::cellReselectionParameters1XRTT_ToStringNoNewLines() const
{
    std::string out = "cellReselectionParameters1XRTT:";
    out += cellReselectionParameters1XRTT.ToStringNoNewLines();
    return out;
}

int SystemInformationBlockType8::parameters1XRTT::cellReselectionParameters1XRTT_Clear()
{
    cellReselectionParameters1XRTT_present = false;
    return 0;
}

bool SystemInformationBlockType8::parameters1XRTT::cellReselectionParameters1XRTT_IsPresent() const
{
    return cellReselectionParameters1XRTT_present;
}

int SystemInformationBlockType8::lateNonCriticalExtension_Pack(std::vector<uint8_t> &bits)
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

int SystemInformationBlockType8::lateNonCriticalExtension_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return lateNonCriticalExtension_Unpack(bits, idx);
}

int SystemInformationBlockType8::lateNonCriticalExtension_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
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
        printf("SystemInformationBlockType8::lateNonCriticalExtension_Unpack() index out of bounds\n");
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

std::vector<uint8_t> SystemInformationBlockType8::lateNonCriticalExtension_Value() const
{
    if(lateNonCriticalExtension_present)
        return lateNonCriticalExtension_internal_value;
    std::vector<uint8_t> tmp;
    return tmp;
}

int SystemInformationBlockType8::lateNonCriticalExtension_SetValue(std::vector<uint8_t> value)
{
    lateNonCriticalExtension_internal_value = value;
    lateNonCriticalExtension_present = true;
    return 0;
}

std::string SystemInformationBlockType8::lateNonCriticalExtension_ToString(uint32_t indent) const
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

std::string SystemInformationBlockType8::lateNonCriticalExtension_ToStringNoNewLines() const
{
    std::string out = "lateNonCriticalExtension={";
    for(auto byte : lateNonCriticalExtension_internal_value)
        out += std::to_string(byte) + ",";
    out = out.substr(0, out.length()-1) + "},";
    return out;
}

int SystemInformationBlockType8::lateNonCriticalExtension_Clear()
{
    lateNonCriticalExtension_present = false;
    return 0;
}

bool SystemInformationBlockType8::lateNonCriticalExtension_IsPresent() const
{
    return lateNonCriticalExtension_present;
}

int SystemInformationBlockType8::csfb_SupportForDualRxUEs_r9_Pack(std::vector<uint8_t> &bits)
{
    bits.push_back(csfb_SupportForDualRxUEs_r9_internal_value);
    return 0;
}

int SystemInformationBlockType8::csfb_SupportForDualRxUEs_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return csfb_SupportForDualRxUEs_r9_Unpack(bits, idx);
}

int SystemInformationBlockType8::csfb_SupportForDualRxUEs_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    if((idx + 1) > bits.size())
    {
        printf("SystemInformationBlockType8::csfb_SupportForDualRxUEs_r9_Unpack() index out of bounds\n");
        return -1;
    }
    csfb_SupportForDualRxUEs_r9_internal_value = bits[idx++];
    csfb_SupportForDualRxUEs_r9_present = true;
    return 0;
}

bool SystemInformationBlockType8::csfb_SupportForDualRxUEs_r9_Value() const
{
    if(csfb_SupportForDualRxUEs_r9_present)
        return csfb_SupportForDualRxUEs_r9_internal_value;
    return false;
}

int SystemInformationBlockType8::csfb_SupportForDualRxUEs_r9_SetValue(bool value)
{
    csfb_SupportForDualRxUEs_r9_internal_value = value;
    csfb_SupportForDualRxUEs_r9_present = true;
    return 0;
}

std::string SystemInformationBlockType8::csfb_SupportForDualRxUEs_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "csfb_SupportForDualRxUEs_r9 = " + std::to_string(csfb_SupportForDualRxUEs_r9_internal_value) + "\n";
    return out;
}

std::string SystemInformationBlockType8::csfb_SupportForDualRxUEs_r9_ToStringNoNewLines() const
{
    std::string out = "csfb_SupportForDualRxUEs_r9=" + std::to_string(csfb_SupportForDualRxUEs_r9_internal_value) + ",";
    return out;
}

int SystemInformationBlockType8::csfb_SupportForDualRxUEs_r9_Clear()
{
    csfb_SupportForDualRxUEs_r9_present = false;
    return 0;
}

bool SystemInformationBlockType8::csfb_SupportForDualRxUEs_r9_IsPresent() const
{
    return csfb_SupportForDualRxUEs_r9_present;
}

CellReselectionParametersCDMA2000_v920* SystemInformationBlockType8::cellReselectionParametersHRPD_v920_Set()
{
    cellReselectionParametersHRPD_v920_present = true;
    return &cellReselectionParametersHRPD_v920;
}

int SystemInformationBlockType8::cellReselectionParametersHRPD_v920_Set(CellReselectionParametersCDMA2000_v920 &value)
{
    cellReselectionParametersHRPD_v920_present = true;
    cellReselectionParametersHRPD_v920 = value;
    return 0;
}

const CellReselectionParametersCDMA2000_v920& SystemInformationBlockType8::cellReselectionParametersHRPD_v920_Get() const
{
    return cellReselectionParametersHRPD_v920;
}

std::string SystemInformationBlockType8::cellReselectionParametersHRPD_v920_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cellReselectionParametersHRPD_v920:\n";
    out += cellReselectionParametersHRPD_v920.ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType8::cellReselectionParametersHRPD_v920_ToStringNoNewLines() const
{
    std::string out = "cellReselectionParametersHRPD_v920:";
    out += cellReselectionParametersHRPD_v920.ToStringNoNewLines();
    return out;
}

int SystemInformationBlockType8::cellReselectionParametersHRPD_v920_Clear()
{
    cellReselectionParametersHRPD_v920_present = false;
    return 0;
}

bool SystemInformationBlockType8::cellReselectionParametersHRPD_v920_IsPresent() const
{
    return cellReselectionParametersHRPD_v920_present;
}

CellReselectionParametersCDMA2000_v920* SystemInformationBlockType8::cellReselectionParameters1XRTT_v920_Set()
{
    cellReselectionParameters1XRTT_v920_present = true;
    return &cellReselectionParameters1XRTT_v920;
}

int SystemInformationBlockType8::cellReselectionParameters1XRTT_v920_Set(CellReselectionParametersCDMA2000_v920 &value)
{
    cellReselectionParameters1XRTT_v920_present = true;
    cellReselectionParameters1XRTT_v920 = value;
    return 0;
}

const CellReselectionParametersCDMA2000_v920& SystemInformationBlockType8::cellReselectionParameters1XRTT_v920_Get() const
{
    return cellReselectionParameters1XRTT_v920;
}

std::string SystemInformationBlockType8::cellReselectionParameters1XRTT_v920_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cellReselectionParameters1XRTT_v920:\n";
    out += cellReselectionParameters1XRTT_v920.ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType8::cellReselectionParameters1XRTT_v920_ToStringNoNewLines() const
{
    std::string out = "cellReselectionParameters1XRTT_v920:";
    out += cellReselectionParameters1XRTT_v920.ToStringNoNewLines();
    return out;
}

int SystemInformationBlockType8::cellReselectionParameters1XRTT_v920_Clear()
{
    cellReselectionParameters1XRTT_v920_present = false;
    return 0;
}

bool SystemInformationBlockType8::cellReselectionParameters1XRTT_v920_IsPresent() const
{
    return cellReselectionParameters1XRTT_v920_present;
}

CSFB_RegistrationParam1XRTT_v920* SystemInformationBlockType8::csfb_RegistrationParam1XRTT_v920_Set()
{
    csfb_RegistrationParam1XRTT_v920_present = true;
    return &csfb_RegistrationParam1XRTT_v920;
}

int SystemInformationBlockType8::csfb_RegistrationParam1XRTT_v920_Set(CSFB_RegistrationParam1XRTT_v920 &value)
{
    csfb_RegistrationParam1XRTT_v920_present = true;
    csfb_RegistrationParam1XRTT_v920 = value;
    return 0;
}

const CSFB_RegistrationParam1XRTT_v920& SystemInformationBlockType8::csfb_RegistrationParam1XRTT_v920_Get() const
{
    return csfb_RegistrationParam1XRTT_v920;
}

std::string SystemInformationBlockType8::csfb_RegistrationParam1XRTT_v920_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "csfb_RegistrationParam1XRTT_v920:\n";
    out += csfb_RegistrationParam1XRTT_v920.ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType8::csfb_RegistrationParam1XRTT_v920_ToStringNoNewLines() const
{
    std::string out = "csfb_RegistrationParam1XRTT_v920:";
    out += csfb_RegistrationParam1XRTT_v920.ToStringNoNewLines();
    return out;
}

int SystemInformationBlockType8::csfb_RegistrationParam1XRTT_v920_Clear()
{
    csfb_RegistrationParam1XRTT_v920_present = false;
    return 0;
}

bool SystemInformationBlockType8::csfb_RegistrationParam1XRTT_v920_IsPresent() const
{
    return csfb_RegistrationParam1XRTT_v920_present;
}

AC_BarringConfig1XRTT_r9* SystemInformationBlockType8::ac_BarringConfig1XRTT_r9_Set()
{
    ac_BarringConfig1XRTT_r9_present = true;
    return &ac_BarringConfig1XRTT_r9;
}

int SystemInformationBlockType8::ac_BarringConfig1XRTT_r9_Set(AC_BarringConfig1XRTT_r9 &value)
{
    ac_BarringConfig1XRTT_r9_present = true;
    ac_BarringConfig1XRTT_r9 = value;
    return 0;
}

const AC_BarringConfig1XRTT_r9& SystemInformationBlockType8::ac_BarringConfig1XRTT_r9_Get() const
{
    return ac_BarringConfig1XRTT_r9;
}

std::string SystemInformationBlockType8::ac_BarringConfig1XRTT_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ac_BarringConfig1XRTT_r9:\n";
    out += ac_BarringConfig1XRTT_r9.ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType8::ac_BarringConfig1XRTT_r9_ToStringNoNewLines() const
{
    std::string out = "ac_BarringConfig1XRTT_r9:";
    out += ac_BarringConfig1XRTT_r9.ToStringNoNewLines();
    return out;
}

int SystemInformationBlockType8::ac_BarringConfig1XRTT_r9_Clear()
{
    ac_BarringConfig1XRTT_r9_present = false;
    return 0;
}

bool SystemInformationBlockType8::ac_BarringConfig1XRTT_r9_IsPresent() const
{
    return ac_BarringConfig1XRTT_r9_present;
}

int SystemInformationBlockType8::csfb_DualRxTxSupport_r10_Pack(std::vector<uint8_t> &bits)
{
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((csfb_DualRxTxSupport_r10_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int SystemInformationBlockType8::csfb_DualRxTxSupport_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return csfb_DualRxTxSupport_r10_Unpack(bits, idx);
}

int SystemInformationBlockType8::csfb_DualRxTxSupport_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("SystemInformationBlockType8::csfb_DualRxTxSupport_r10_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 0)
    {
        printf("SystemInformationBlockType8::csfb_DualRxTxSupport_r10_Unpack() max failure\n");
        return -1;
    }
    csfb_DualRxTxSupport_r10_internal_value = (csfb_DualRxTxSupport_r10_Enum)packed_val;
    csfb_DualRxTxSupport_r10_present = true;
    return 0;
}

SystemInformationBlockType8::csfb_DualRxTxSupport_r10_Enum SystemInformationBlockType8::csfb_DualRxTxSupport_r10_Value() const
{
    if(csfb_DualRxTxSupport_r10_present)
        return csfb_DualRxTxSupport_r10_internal_value;
    return (SystemInformationBlockType8::csfb_DualRxTxSupport_r10_Enum)0;
}

int SystemInformationBlockType8::csfb_DualRxTxSupport_r10_SetValue(csfb_DualRxTxSupport_r10_Enum value)
{
    csfb_DualRxTxSupport_r10_internal_value = value;
    csfb_DualRxTxSupport_r10_present = true;
    return 0;
}

int SystemInformationBlockType8::csfb_DualRxTxSupport_r10_SetValue(std::string value)
{
    if("true" == value)
    {
        csfb_DualRxTxSupport_r10_internal_value = k_csfb_DualRxTxSupport_r10_true;
        csfb_DualRxTxSupport_r10_present = true;
        return 0;
    }
    return 1;
}

std::string SystemInformationBlockType8::csfb_DualRxTxSupport_r10_ValueToString(csfb_DualRxTxSupport_r10_Enum value) const
{
    if(k_csfb_DualRxTxSupport_r10_true == value)
        return "true";
    return "";
}

uint64_t SystemInformationBlockType8::csfb_DualRxTxSupport_r10_NumberOfValues() const
{
    return 1;
}

std::string SystemInformationBlockType8::csfb_DualRxTxSupport_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "csfb_DualRxTxSupport_r10 = " + csfb_DualRxTxSupport_r10_ValueToString(csfb_DualRxTxSupport_r10_internal_value) + "\n";
    return out;
}

std::string SystemInformationBlockType8::csfb_DualRxTxSupport_r10_ToStringNoNewLines() const
{
    std::string out = "csfb_DualRxTxSupport_r10=" + csfb_DualRxTxSupport_r10_ValueToString(csfb_DualRxTxSupport_r10_internal_value) + ",";
    return out;
}

int SystemInformationBlockType8::csfb_DualRxTxSupport_r10_Clear()
{
    csfb_DualRxTxSupport_r10_present = false;
    return 0;
}

bool SystemInformationBlockType8::csfb_DualRxTxSupport_r10_IsPresent() const
{
    return csfb_DualRxTxSupport_r10_present;
}

