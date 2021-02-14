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

#include "ReportConfigEUTRA.h"

#include <cmath>

int ReportConfigEUTRA::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator
    bool has_extension = false;
    if(si_RequestForHO_r9_IsPresent() || ue_RxTxTimeDiffPeriodical_r9_IsPresent() || includeLocationInfo_r10_IsPresent() || reportAddNeighMeas_r10_IsPresent())
    {
        bits.push_back(1);
        has_extension = true;
    }else{
        bits.push_back(0);
    }

    // Optional indicators

    // Fields
    {
        if(0 != triggerType_Pack(bits))
        {
            printf("ReportConfigEUTRA:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != triggerQuantity_Pack(bits))
        {
            printf("ReportConfigEUTRA:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != reportQuantity_Pack(bits))
        {
            printf("ReportConfigEUTRA:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != maxReportCells_Pack(bits))
        {
            printf("ReportConfigEUTRA:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != reportInterval.Pack(bits))
        {
            printf("ReportConfigEUTRA:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != reportAmount_Pack(bits))
        {
            printf("ReportConfigEUTRA:: field pack failure\n");
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
            printf("ReportConfigEUTRA:: Extension list size too large failure\n");
            return -1;
        }

        // Extension field presence indicators
        bits.push_back(si_RequestForHO_r9_IsPresent());
        bits.push_back(ue_RxTxTimeDiffPeriodical_r9_IsPresent());
        bits.push_back(includeLocationInfo_r10_IsPresent());
        bits.push_back(reportAddNeighMeas_r10_IsPresent());

        // Extension fields
        if(si_RequestForHO_r9_IsPresent())
        {
            std::vector<uint8_t> field_bits;
            if(0 != si_RequestForHO_r9_Pack(field_bits))
            {
                printf("ReportConfigEUTRA:: field pack failure\n");
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
        if(ue_RxTxTimeDiffPeriodical_r9_IsPresent())
        {
            std::vector<uint8_t> field_bits;
            if(0 != ue_RxTxTimeDiffPeriodical_r9_Pack(field_bits))
            {
                printf("ReportConfigEUTRA:: field pack failure\n");
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
        if(includeLocationInfo_r10_IsPresent())
        {
            std::vector<uint8_t> field_bits;
            if(0 != includeLocationInfo_r10_Pack(field_bits))
            {
                printf("ReportConfigEUTRA:: field pack failure\n");
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
        if(reportAddNeighMeas_r10_IsPresent())
        {
            std::vector<uint8_t> field_bits;
            if(0 != reportAddNeighMeas_r10_Pack(field_bits))
            {
                printf("ReportConfigEUTRA:: field pack failure\n");
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

int ReportConfigEUTRA::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int ReportConfigEUTRA::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("ReportConfigEUTRA::Unpack() index out of bounds for extension\n");
        return -1;
    }
    bool has_extension = bits[idx++];

    // Optional indicators

    // Fields
    {
        if(0 != triggerType_Unpack(bits, idx))
        {
            printf("ReportConfigEUTRA:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != triggerQuantity_Unpack(bits, idx))
        {
            printf("ReportConfigEUTRA:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != reportQuantity_Unpack(bits, idx))
        {
            printf("ReportConfigEUTRA:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != maxReportCells_Unpack(bits, idx))
        {
            printf("ReportConfigEUTRA:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != reportInterval.Unpack(bits, idx))
        {
            printf("ReportConfigEUTRA:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != reportAmount_Unpack(bits, idx))
        {
            printf("ReportConfigEUTRA:: field unpack failure\n");
            return -1;
        }
    }

    // Extension
    if(has_extension)
    {
        if((idx + 7) > bits.size())
        {
            printf("ReportConfigEUTRA::Unpack() index out of bounds for extension size\n");
            return -1;
        }
        // Number of extension fields
        if(bits[idx++] != 0)
        {
            printf("ReportConfigEUTRA:: Extension list size too large failure\n");
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
                printf("ReportConfigEUTRA::Unpack() index out of bounds for optional indiator si_RequestForHO_r9\n");
                return -1;
            }
            si_RequestForHO_r9_present = bits[idx++];
        }
        if(opt_ind_count++ < N_ext_fields)
        {
            if((idx + 1) > bits.size())
            {
                printf("ReportConfigEUTRA::Unpack() index out of bounds for optional indiator ue_RxTxTimeDiffPeriodical_r9\n");
                return -1;
            }
            ue_RxTxTimeDiffPeriodical_r9_present = bits[idx++];
        }
        if(opt_ind_count++ < N_ext_fields)
        {
            if((idx + 1) > bits.size())
            {
                printf("ReportConfigEUTRA::Unpack() index out of bounds for optional indiator includeLocationInfo_r10\n");
                return -1;
            }
            includeLocationInfo_r10_present = bits[idx++];
        }
        if(opt_ind_count++ < N_ext_fields)
        {
            if((idx + 1) > bits.size())
            {
                printf("ReportConfigEUTRA::Unpack() index out of bounds for optional indiator reportAddNeighMeas_r10\n");
                return -1;
            }
            reportAddNeighMeas_r10_present = bits[idx++];
        }
        if((idx + (N_ext_fields - opt_ind_count)) > bits.size())
        {
            printf("ReportConfigEUTRA::Unpack() index out of bounds for extension optional indicators\n");
            return -1;
        }
        idx += (N_ext_fields - opt_ind_count);

        // Extension fields
        if(si_RequestForHO_r9_present)
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
            if(0 != si_RequestForHO_r9_Unpack(bits, idx))
            {
                printf("ReportConfigEUTRA:: field unpack failure\n");
                return -1;
            }
            idx = orig_idx + (N_octets * 8);
        }
        if(ue_RxTxTimeDiffPeriodical_r9_present)
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
            if(0 != ue_RxTxTimeDiffPeriodical_r9_Unpack(bits, idx))
            {
                printf("ReportConfigEUTRA:: field unpack failure\n");
                return -1;
            }
            idx = orig_idx + (N_octets * 8);
        }
        if(includeLocationInfo_r10_present)
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
            if(0 != includeLocationInfo_r10_Unpack(bits, idx))
            {
                printf("ReportConfigEUTRA:: field unpack failure\n");
                return -1;
            }
            idx = orig_idx + (N_octets * 8);
        }
        if(reportAddNeighMeas_r10_present)
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
            if(0 != reportAddNeighMeas_r10_Unpack(bits, idx))
            {
                printf("ReportConfigEUTRA:: field unpack failure\n");
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
            printf("ReportConfigEUTRA::Unpack() index out of bounds for extension fields\n");
            return -1;
        }
            idx += N_octets * 8;
        }
    }
    return 0;
}

std::string ReportConfigEUTRA::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ReportConfigEUTRA:\n";
    out += triggerType_ToString(indent+1);
    out += triggerQuantity_ToString(indent+1);
    out += reportQuantity_ToString(indent+1);
    out += maxReportCells_ToString(indent+1);
    out += reportInterval_ToString(indent+1);
    out += reportAmount_ToString(indent+1);
    if(si_RequestForHO_r9_IsPresent())
        out += si_RequestForHO_r9_ToString(indent+1);
    if(ue_RxTxTimeDiffPeriodical_r9_IsPresent())
        out += ue_RxTxTimeDiffPeriodical_r9_ToString(indent+1);
    if(includeLocationInfo_r10_IsPresent())
        out += includeLocationInfo_r10_ToString(indent+1);
    if(reportAddNeighMeas_r10_IsPresent())
        out += reportAddNeighMeas_r10_ToString(indent+1);
    return out;
}

std::string ReportConfigEUTRA::ToStringNoNewLines() const
{
    std::string out = "ReportConfigEUTRA:";
    out += triggerType_ToStringNoNewLines();
    out += triggerQuantity_ToStringNoNewLines();
    out += reportQuantity_ToStringNoNewLines();
    out += maxReportCells_ToStringNoNewLines();
    out += reportInterval_ToStringNoNewLines();
    out += reportAmount_ToStringNoNewLines();
    if(si_RequestForHO_r9_IsPresent())
        out += si_RequestForHO_r9_ToStringNoNewLines();
    if(ue_RxTxTimeDiffPeriodical_r9_IsPresent())
        out += ue_RxTxTimeDiffPeriodical_r9_ToStringNoNewLines();
    if(includeLocationInfo_r10_IsPresent())
        out += includeLocationInfo_r10_ToStringNoNewLines();
    if(reportAddNeighMeas_r10_IsPresent())
        out += reportAddNeighMeas_r10_ToStringNoNewLines();
    return out;
}

int ReportConfigEUTRA::triggerType_Pack(std::vector<uint8_t> &bits)
{
    if(!triggerType_present)
    {
        printf("ReportConfigEUTRA::triggerType_Pack() presence failure\n");
        return -1;
    }
    // Extension indicator

    // Choice
    for(uint32_t i=0; i<1; i++)
        bits.push_back((triggerType_internal_choice >> (1-i-1)) & 1);

    // Fields
    if(triggerType_internal_choice == k_triggerType_event)
    {
        if(0 != triggerType_event_value.Pack(bits))
        {
            printf("ReportConfigEUTRA::triggerType_event pack failure\n");
            return -1;
        }
    }
    if(triggerType_internal_choice == k_triggerType_periodical)
    {
        if(0 != triggerType_periodical_value.Pack(bits))
        {
            printf("ReportConfigEUTRA::triggerType_periodical pack failure\n");
            return -1;
        }
    }
    return 0;
}

int ReportConfigEUTRA::triggerType_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return triggerType_Unpack(bits, idx);
}

int ReportConfigEUTRA::triggerType_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 1) > bits.size())
    {
        printf("ReportConfigEUTRA::triggerType_Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<1; i++)
        packed_val |= bits[idx++] << (1-i-1);

    if((ReportConfigEUTRA::triggerType_Enum)packed_val > k_triggerType_periodical)
    {
        printf("ReportConfigEUTRA::triggerType_Unpack() choice range failure\n");
        return -1;
    }
    triggerType_internal_choice = (ReportConfigEUTRA::triggerType_Enum)packed_val;
    triggerType_present = true;

    // Fields
    if(triggerType_internal_choice == k_triggerType_event)
    {
        if(0 != triggerType_event_value.Unpack(bits, idx))
        {
            printf("ReportConfigEUTRA::triggerType_event unpack failure\n");
            return -1;
        }
    }
    if(triggerType_internal_choice == k_triggerType_periodical)
    {
        if(0 != triggerType_periodical_value.Unpack(bits, idx))
        {
            printf("ReportConfigEUTRA::triggerType_periodical unpack failure\n");
            return -1;
        }
    }
    return 0;
}

ReportConfigEUTRA::triggerType_Enum ReportConfigEUTRA::triggerType_Choice() const
{
    if(triggerType_present)
        return triggerType_internal_choice;
    return (ReportConfigEUTRA::triggerType_Enum)0;
}

int ReportConfigEUTRA::triggerType_SetChoice(ReportConfigEUTRA::triggerType_Enum choice)
{
    triggerType_internal_choice = choice;
    triggerType_present = true;
    return 0;
}

std::string ReportConfigEUTRA::triggerType_ChoiceToString(triggerType_Enum value) const
{
    if(k_triggerType_event == value)
        return "triggerType_event";
    if(k_triggerType_periodical == value)
        return "triggerType_periodical";
    return "";
}

uint64_t ReportConfigEUTRA::triggerType_NumberOfChoices() const
{
    return 2;
}

std::string ReportConfigEUTRA::triggerType_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "triggerType = " + triggerType_ChoiceToString(triggerType_internal_choice) + ":\n";
    if(triggerType_internal_choice == k_triggerType_event)
        out += triggerType_event_value.ToString(indent+1);
    if(triggerType_internal_choice == k_triggerType_periodical)
        out += triggerType_periodical_value.ToString(indent+1);
    return out;
}

std::string ReportConfigEUTRA::triggerType_ToStringNoNewLines() const
{
    std::string out = "triggerType=" + triggerType_ChoiceToString(triggerType_internal_choice) + ",";
    if(triggerType_internal_choice == k_triggerType_event)
        out += triggerType_event_value.ToStringNoNewLines();
    if(triggerType_internal_choice == k_triggerType_periodical)
        out += triggerType_periodical_value.ToStringNoNewLines();
    return out;
}

int ReportConfigEUTRA::triggerType_Clear()
{
    triggerType_present = false;
    return 0;
}

bool ReportConfigEUTRA::triggerType_IsPresent() const
{
    return triggerType_present;
}

int ReportConfigEUTRA::triggerType_event::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != eventId_Pack(bits))
        {
            printf("ReportConfigEUTRA::triggerType_event:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != hysteresis.Pack(bits))
        {
            printf("ReportConfigEUTRA::triggerType_event:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != timeToTrigger.Pack(bits))
        {
            printf("ReportConfigEUTRA::triggerType_event:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int ReportConfigEUTRA::triggerType_event::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int ReportConfigEUTRA::triggerType_event::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != eventId_Unpack(bits, idx))
        {
            printf("ReportConfigEUTRA::triggerType_event:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != hysteresis.Unpack(bits, idx))
        {
            printf("ReportConfigEUTRA::triggerType_event:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != timeToTrigger.Unpack(bits, idx))
        {
            printf("ReportConfigEUTRA::triggerType_event:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string ReportConfigEUTRA::triggerType_event::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "event:\n";
    out += eventId_ToString(indent+1);
    out += hysteresis_ToString(indent+1);
    out += timeToTrigger_ToString(indent+1);
    return out;
}

std::string ReportConfigEUTRA::triggerType_event::ToStringNoNewLines() const
{
    std::string out = "event:";
    out += eventId_ToStringNoNewLines();
    out += hysteresis_ToStringNoNewLines();
    out += timeToTrigger_ToStringNoNewLines();
    return out;
}

int ReportConfigEUTRA::triggerType_event::eventId_Pack(std::vector<uint8_t> &bits)
{
    if(!eventId_present)
    {
        printf("ReportConfigEUTRA::triggerType_event::eventId_Pack() presence failure\n");
        return -1;
    }
    // Extension indicator
    bool is_extended = false;
    if(eventId_internal_choice > k_eventId_eventA5)
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
            bits.push_back(((eventId_internal_choice - k_eventId_eventA6) >> (6-i-1)) & 1);
    }else{
        for(uint32_t i=0; i<3; i++)
            bits.push_back((eventId_internal_choice >> (3-i-1)) & 1);
    }

    // Fields
    if(eventId_internal_choice == k_eventId_eventA1)
    {
        if(0 != eventId_eventA1_value.Pack(bits))
        {
            printf("ReportConfigEUTRA::triggerType_event::eventId_eventA1 pack failure\n");
            return -1;
        }
    }
    if(eventId_internal_choice == k_eventId_eventA2)
    {
        if(0 != eventId_eventA2_value.Pack(bits))
        {
            printf("ReportConfigEUTRA::triggerType_event::eventId_eventA2 pack failure\n");
            return -1;
        }
    }
    if(eventId_internal_choice == k_eventId_eventA3)
    {
        if(0 != eventId_eventA3_value.Pack(bits))
        {
            printf("ReportConfigEUTRA::triggerType_event::eventId_eventA3 pack failure\n");
            return -1;
        }
    }
    if(eventId_internal_choice == k_eventId_eventA4)
    {
        if(0 != eventId_eventA4_value.Pack(bits))
        {
            printf("ReportConfigEUTRA::triggerType_event::eventId_eventA4 pack failure\n");
            return -1;
        }
    }
    if(eventId_internal_choice == k_eventId_eventA5)
    {
        if(0 != eventId_eventA5_value.Pack(bits))
        {
            printf("ReportConfigEUTRA::triggerType_event::eventId_eventA5 pack failure\n");
            return -1;
        }
    }

    // Extension
    if(is_extended)
    {
        std::vector<uint8_t> ext_bits;
        if(eventId_internal_choice == k_eventId_eventA6)
        {
            if(0 != eventId_eventA6_value.Pack(ext_bits))
            {
                printf("ReportConfigEUTRA::triggerType_event::eventId_eventA6 pack failure\n");
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

int ReportConfigEUTRA::triggerType_event::eventId_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return eventId_Unpack(bits, idx);
}

int ReportConfigEUTRA::triggerType_event::eventId_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("ReportConfigEUTRA::triggerType_event::eventId_Unpack() index out of bounds for extension\n");
        return -1;
    }
    bool is_extended = bits[idx++];

    // Choice
    if(is_extended)
    {
        if((idx + 7) > bits.size())
        {
            printf("ReportConfigEUTRA::triggerType_event::eventId_Unpack() index out of bounds for extension size\n");
            return -1;
        }
        if(bits[idx++] != 0)
        {
            printf("ReportConfigEUTRA::triggerType_event::eventId_ Extension size too large failure\n");
            return -1;
        }
        uint32_t packed_val = 0;
        for(uint32_t i=0; i<6; i++)
            packed_val |= bits[idx++] << (6-i-1);
        if((ReportConfigEUTRA::triggerType_event::eventId_Enum)packed_val > k_eventId_eventA6)
        {
            printf("ReportConfigEUTRA::triggerType_event::eventId_Unpack choice range failure\n");
            return -1;
        }
        eventId_internal_choice = (ReportConfigEUTRA::triggerType_event::eventId_Enum)(packed_val + k_eventId_eventA6);
    }else{
        uint32_t packed_val = 0;
        if((idx + 3) > bits.size())
        {
            printf("ReportConfigEUTRA::triggerType_event::eventId_Unpack() index out of bounds for choice\n");
            return -1;
        }
        for(uint32_t i=0; i<3; i++)
            packed_val |= bits[idx++] << (3-i-1);

        if((ReportConfigEUTRA::triggerType_event::eventId_Enum)packed_val > k_eventId_eventA6)
        {
            printf("ReportConfigEUTRA::triggerType_event::eventId_Unpack choice range failure\n");
            return -1;
        }
        eventId_internal_choice = (ReportConfigEUTRA::triggerType_event::eventId_Enum)packed_val;
    }
    eventId_present = true;

    // Fields
    if(eventId_internal_choice == k_eventId_eventA1)
    {
        if(0 != eventId_eventA1_value.Unpack(bits, idx))
        {
            printf("ReportConfigEUTRA::triggerType_event::eventId_eventA1 unpack failure\n");
            return -1;
        }
    }
    if(eventId_internal_choice == k_eventId_eventA2)
    {
        if(0 != eventId_eventA2_value.Unpack(bits, idx))
        {
            printf("ReportConfigEUTRA::triggerType_event::eventId_eventA2 unpack failure\n");
            return -1;
        }
    }
    if(eventId_internal_choice == k_eventId_eventA3)
    {
        if(0 != eventId_eventA3_value.Unpack(bits, idx))
        {
            printf("ReportConfigEUTRA::triggerType_event::eventId_eventA3 unpack failure\n");
            return -1;
        }
    }
    if(eventId_internal_choice == k_eventId_eventA4)
    {
        if(0 != eventId_eventA4_value.Unpack(bits, idx))
        {
            printf("ReportConfigEUTRA::triggerType_event::eventId_eventA4 unpack failure\n");
            return -1;
        }
    }
    if(eventId_internal_choice == k_eventId_eventA5)
    {
        if(0 != eventId_eventA5_value.Unpack(bits, idx))
        {
            printf("ReportConfigEUTRA::triggerType_event::eventId_eventA5 unpack failure\n");
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
            printf("ReportConfigEUTRA::triggerType_event::eventId_Unpack() index out of bounds for choice items\n");
            return -1;
        }
        if(eventId_internal_choice == k_eventId_eventA6)
        {
            if(0 != eventId_eventA6_value.Unpack(bits, idx))
            {
                printf("ReportConfigEUTRA::triggerType_event::eventId_eventA6 unpack failure\n");
                return -1;
            }
        }
        idx = orig_idx + (N_octets * 8);
    }
    return 0;
}

ReportConfigEUTRA::triggerType_event::eventId_Enum ReportConfigEUTRA::triggerType_event::eventId_Choice() const
{
    if(eventId_present)
        return eventId_internal_choice;
    return (ReportConfigEUTRA::triggerType_event::eventId_Enum)0;
}

int ReportConfigEUTRA::triggerType_event::eventId_SetChoice(ReportConfigEUTRA::triggerType_event::eventId_Enum choice)
{
    eventId_internal_choice = choice;
    eventId_present = true;
    return 0;
}

std::string ReportConfigEUTRA::triggerType_event::eventId_ChoiceToString(eventId_Enum value) const
{
    if(k_eventId_eventA1 == value)
        return "eventId_eventA1";
    if(k_eventId_eventA2 == value)
        return "eventId_eventA2";
    if(k_eventId_eventA3 == value)
        return "eventId_eventA3";
    if(k_eventId_eventA4 == value)
        return "eventId_eventA4";
    if(k_eventId_eventA5 == value)
        return "eventId_eventA5";
    if(k_eventId_eventA6 == value)
        return "eventId_eventA6";
    return "";
}

uint64_t ReportConfigEUTRA::triggerType_event::eventId_NumberOfChoices() const
{
    return 6;
}

std::string ReportConfigEUTRA::triggerType_event::eventId_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "eventId = " + eventId_ChoiceToString(eventId_internal_choice) + ":\n";
    if(eventId_internal_choice == k_eventId_eventA1)
        out += eventId_eventA1_value.ToString(indent+1);
    if(eventId_internal_choice == k_eventId_eventA2)
        out += eventId_eventA2_value.ToString(indent+1);
    if(eventId_internal_choice == k_eventId_eventA3)
        out += eventId_eventA3_value.ToString(indent+1);
    if(eventId_internal_choice == k_eventId_eventA4)
        out += eventId_eventA4_value.ToString(indent+1);
    if(eventId_internal_choice == k_eventId_eventA5)
        out += eventId_eventA5_value.ToString(indent+1);
    if(eventId_internal_choice == k_eventId_eventA6)
        out += eventId_eventA6_value.ToString(indent+1);
    return out;
}

std::string ReportConfigEUTRA::triggerType_event::eventId_ToStringNoNewLines() const
{
    std::string out = "eventId=" + eventId_ChoiceToString(eventId_internal_choice) + ",";
    if(eventId_internal_choice == k_eventId_eventA1)
        out += eventId_eventA1_value.ToStringNoNewLines();
    if(eventId_internal_choice == k_eventId_eventA2)
        out += eventId_eventA2_value.ToStringNoNewLines();
    if(eventId_internal_choice == k_eventId_eventA3)
        out += eventId_eventA3_value.ToStringNoNewLines();
    if(eventId_internal_choice == k_eventId_eventA4)
        out += eventId_eventA4_value.ToStringNoNewLines();
    if(eventId_internal_choice == k_eventId_eventA5)
        out += eventId_eventA5_value.ToStringNoNewLines();
    if(eventId_internal_choice == k_eventId_eventA6)
        out += eventId_eventA6_value.ToStringNoNewLines();
    return out;
}

int ReportConfigEUTRA::triggerType_event::eventId_Clear()
{
    eventId_present = false;
    return 0;
}

bool ReportConfigEUTRA::triggerType_event::eventId_IsPresent() const
{
    return eventId_present;
}

int ReportConfigEUTRA::triggerType_event::eventId_eventA1::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != a1_Threshold.Pack(bits))
        {
            printf("ReportConfigEUTRA::triggerType_event::eventId_eventA1:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int ReportConfigEUTRA::triggerType_event::eventId_eventA1::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int ReportConfigEUTRA::triggerType_event::eventId_eventA1::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != a1_Threshold.Unpack(bits, idx))
        {
            printf("ReportConfigEUTRA::triggerType_event::eventId_eventA1:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string ReportConfigEUTRA::triggerType_event::eventId_eventA1::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "eventA1:\n";
    out += a1_Threshold_ToString(indent+1);
    return out;
}

std::string ReportConfigEUTRA::triggerType_event::eventId_eventA1::ToStringNoNewLines() const
{
    std::string out = "eventA1:";
    out += a1_Threshold_ToStringNoNewLines();
    return out;
}

ThresholdEUTRA* ReportConfigEUTRA::triggerType_event::eventId_eventA1::a1_Threshold_Set()
{
    a1_Threshold_present = true;
    return &a1_Threshold;
}

int ReportConfigEUTRA::triggerType_event::eventId_eventA1::a1_Threshold_Set(ThresholdEUTRA &value)
{
    a1_Threshold_present = true;
    a1_Threshold = value;
    return 0;
}

const ThresholdEUTRA& ReportConfigEUTRA::triggerType_event::eventId_eventA1::a1_Threshold_Get() const
{
    return a1_Threshold;
}

std::string ReportConfigEUTRA::triggerType_event::eventId_eventA1::a1_Threshold_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "a1_Threshold:\n";
    out += a1_Threshold.ToString(indent+1);
    return out;
}

std::string ReportConfigEUTRA::triggerType_event::eventId_eventA1::a1_Threshold_ToStringNoNewLines() const
{
    std::string out = "a1_Threshold:";
    out += a1_Threshold.ToStringNoNewLines();
    return out;
}

int ReportConfigEUTRA::triggerType_event::eventId_eventA1::a1_Threshold_Clear()
{
    a1_Threshold_present = false;
    return 0;
}

bool ReportConfigEUTRA::triggerType_event::eventId_eventA1::a1_Threshold_IsPresent() const
{
    return a1_Threshold_present;
}

int ReportConfigEUTRA::triggerType_event::eventId_eventA2::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != a2_Threshold.Pack(bits))
        {
            printf("ReportConfigEUTRA::triggerType_event::eventId_eventA2:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int ReportConfigEUTRA::triggerType_event::eventId_eventA2::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int ReportConfigEUTRA::triggerType_event::eventId_eventA2::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != a2_Threshold.Unpack(bits, idx))
        {
            printf("ReportConfigEUTRA::triggerType_event::eventId_eventA2:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string ReportConfigEUTRA::triggerType_event::eventId_eventA2::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "eventA2:\n";
    out += a2_Threshold_ToString(indent+1);
    return out;
}

std::string ReportConfigEUTRA::triggerType_event::eventId_eventA2::ToStringNoNewLines() const
{
    std::string out = "eventA2:";
    out += a2_Threshold_ToStringNoNewLines();
    return out;
}

ThresholdEUTRA* ReportConfigEUTRA::triggerType_event::eventId_eventA2::a2_Threshold_Set()
{
    a2_Threshold_present = true;
    return &a2_Threshold;
}

int ReportConfigEUTRA::triggerType_event::eventId_eventA2::a2_Threshold_Set(ThresholdEUTRA &value)
{
    a2_Threshold_present = true;
    a2_Threshold = value;
    return 0;
}

const ThresholdEUTRA& ReportConfigEUTRA::triggerType_event::eventId_eventA2::a2_Threshold_Get() const
{
    return a2_Threshold;
}

std::string ReportConfigEUTRA::triggerType_event::eventId_eventA2::a2_Threshold_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "a2_Threshold:\n";
    out += a2_Threshold.ToString(indent+1);
    return out;
}

std::string ReportConfigEUTRA::triggerType_event::eventId_eventA2::a2_Threshold_ToStringNoNewLines() const
{
    std::string out = "a2_Threshold:";
    out += a2_Threshold.ToStringNoNewLines();
    return out;
}

int ReportConfigEUTRA::triggerType_event::eventId_eventA2::a2_Threshold_Clear()
{
    a2_Threshold_present = false;
    return 0;
}

bool ReportConfigEUTRA::triggerType_event::eventId_eventA2::a2_Threshold_IsPresent() const
{
    return a2_Threshold_present;
}

int ReportConfigEUTRA::triggerType_event::eventId_eventA3::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != a3_Offset_Pack(bits))
        {
            printf("ReportConfigEUTRA::triggerType_event::eventId_eventA3:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != reportOnLeave_Pack(bits))
        {
            printf("ReportConfigEUTRA::triggerType_event::eventId_eventA3:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int ReportConfigEUTRA::triggerType_event::eventId_eventA3::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int ReportConfigEUTRA::triggerType_event::eventId_eventA3::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != a3_Offset_Unpack(bits, idx))
        {
            printf("ReportConfigEUTRA::triggerType_event::eventId_eventA3:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != reportOnLeave_Unpack(bits, idx))
        {
            printf("ReportConfigEUTRA::triggerType_event::eventId_eventA3:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string ReportConfigEUTRA::triggerType_event::eventId_eventA3::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "eventA3:\n";
    out += a3_Offset_ToString(indent+1);
    out += reportOnLeave_ToString(indent+1);
    return out;
}

std::string ReportConfigEUTRA::triggerType_event::eventId_eventA3::ToStringNoNewLines() const
{
    std::string out = "eventA3:";
    out += a3_Offset_ToStringNoNewLines();
    out += reportOnLeave_ToStringNoNewLines();
    return out;
}

int ReportConfigEUTRA::triggerType_event::eventId_eventA3::a3_Offset_Pack(std::vector<uint8_t> &bits)
{
    if(!a3_Offset_present)
    {
        printf("ReportConfigEUTRA::triggerType_event::eventId_eventA3::a3_Offset_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = a3_Offset_internal_value - (-30);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (30 - -30))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int ReportConfigEUTRA::triggerType_event::eventId_eventA3::a3_Offset_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return a3_Offset_Unpack(bits, idx);
}

int ReportConfigEUTRA::triggerType_event::eventId_eventA3::a3_Offset_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (30 - -30))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("ReportConfigEUTRA::triggerType_event::eventId_eventA3::a3_Offset_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    a3_Offset_internal_value = packed_val + -30;
    a3_Offset_present = true;
    return 0;
}

int64_t ReportConfigEUTRA::triggerType_event::eventId_eventA3::a3_Offset_Value() const
{
    if(a3_Offset_present)
        return a3_Offset_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int ReportConfigEUTRA::triggerType_event::eventId_eventA3::a3_Offset_SetValue(int64_t value)
{
    if(value < -30 || value > 30)
    {
        printf("ReportConfigEUTRA::triggerType_event::eventId_eventA3::a3_Offset_SetValue() range failure\n");
        return -1;
    }
    a3_Offset_internal_value = value;
    a3_Offset_present = true;
    return 0;
}

std::string ReportConfigEUTRA::triggerType_event::eventId_eventA3::a3_Offset_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "a3_Offset = " + std::to_string(a3_Offset_internal_value) + "\n";
    return out;
}

std::string ReportConfigEUTRA::triggerType_event::eventId_eventA3::a3_Offset_ToStringNoNewLines() const
{
    std::string out = "a3_Offset=" + std::to_string(a3_Offset_internal_value) + ",";
    return out;
}

int ReportConfigEUTRA::triggerType_event::eventId_eventA3::a3_Offset_Clear()
{
    a3_Offset_present = false;
    return 0;
}

bool ReportConfigEUTRA::triggerType_event::eventId_eventA3::a3_Offset_IsPresent() const
{
    return a3_Offset_present;
}

int ReportConfigEUTRA::triggerType_event::eventId_eventA3::reportOnLeave_Pack(std::vector<uint8_t> &bits)
{
    if(!reportOnLeave_present)
    {
        printf("ReportConfigEUTRA::triggerType_event::eventId_eventA3::reportOnLeave_Pack() presence failure\n");
        return -1;
    }
    bits.push_back(reportOnLeave_internal_value);
    return 0;
}

int ReportConfigEUTRA::triggerType_event::eventId_eventA3::reportOnLeave_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return reportOnLeave_Unpack(bits, idx);
}

int ReportConfigEUTRA::triggerType_event::eventId_eventA3::reportOnLeave_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    if((idx + 1) > bits.size())
    {
        printf("ReportConfigEUTRA::triggerType_event::eventId_eventA3::reportOnLeave_Unpack() index out of bounds\n");
        return -1;
    }
    reportOnLeave_internal_value = bits[idx++];
    reportOnLeave_present = true;
    return 0;
}

bool ReportConfigEUTRA::triggerType_event::eventId_eventA3::reportOnLeave_Value() const
{
    if(reportOnLeave_present)
        return reportOnLeave_internal_value;
    return false;
}

int ReportConfigEUTRA::triggerType_event::eventId_eventA3::reportOnLeave_SetValue(bool value)
{
    reportOnLeave_internal_value = value;
    reportOnLeave_present = true;
    return 0;
}

std::string ReportConfigEUTRA::triggerType_event::eventId_eventA3::reportOnLeave_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "reportOnLeave = " + std::to_string(reportOnLeave_internal_value) + "\n";
    return out;
}

std::string ReportConfigEUTRA::triggerType_event::eventId_eventA3::reportOnLeave_ToStringNoNewLines() const
{
    std::string out = "reportOnLeave=" + std::to_string(reportOnLeave_internal_value) + ",";
    return out;
}

int ReportConfigEUTRA::triggerType_event::eventId_eventA3::reportOnLeave_Clear()
{
    reportOnLeave_present = false;
    return 0;
}

bool ReportConfigEUTRA::triggerType_event::eventId_eventA3::reportOnLeave_IsPresent() const
{
    return reportOnLeave_present;
}

int ReportConfigEUTRA::triggerType_event::eventId_eventA4::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != a4_Threshold.Pack(bits))
        {
            printf("ReportConfigEUTRA::triggerType_event::eventId_eventA4:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int ReportConfigEUTRA::triggerType_event::eventId_eventA4::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int ReportConfigEUTRA::triggerType_event::eventId_eventA4::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != a4_Threshold.Unpack(bits, idx))
        {
            printf("ReportConfigEUTRA::triggerType_event::eventId_eventA4:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string ReportConfigEUTRA::triggerType_event::eventId_eventA4::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "eventA4:\n";
    out += a4_Threshold_ToString(indent+1);
    return out;
}

std::string ReportConfigEUTRA::triggerType_event::eventId_eventA4::ToStringNoNewLines() const
{
    std::string out = "eventA4:";
    out += a4_Threshold_ToStringNoNewLines();
    return out;
}

ThresholdEUTRA* ReportConfigEUTRA::triggerType_event::eventId_eventA4::a4_Threshold_Set()
{
    a4_Threshold_present = true;
    return &a4_Threshold;
}

int ReportConfigEUTRA::triggerType_event::eventId_eventA4::a4_Threshold_Set(ThresholdEUTRA &value)
{
    a4_Threshold_present = true;
    a4_Threshold = value;
    return 0;
}

const ThresholdEUTRA& ReportConfigEUTRA::triggerType_event::eventId_eventA4::a4_Threshold_Get() const
{
    return a4_Threshold;
}

std::string ReportConfigEUTRA::triggerType_event::eventId_eventA4::a4_Threshold_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "a4_Threshold:\n";
    out += a4_Threshold.ToString(indent+1);
    return out;
}

std::string ReportConfigEUTRA::triggerType_event::eventId_eventA4::a4_Threshold_ToStringNoNewLines() const
{
    std::string out = "a4_Threshold:";
    out += a4_Threshold.ToStringNoNewLines();
    return out;
}

int ReportConfigEUTRA::triggerType_event::eventId_eventA4::a4_Threshold_Clear()
{
    a4_Threshold_present = false;
    return 0;
}

bool ReportConfigEUTRA::triggerType_event::eventId_eventA4::a4_Threshold_IsPresent() const
{
    return a4_Threshold_present;
}

int ReportConfigEUTRA::triggerType_event::eventId_eventA5::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != a5_Threshold1.Pack(bits))
        {
            printf("ReportConfigEUTRA::triggerType_event::eventId_eventA5:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != a5_Threshold2.Pack(bits))
        {
            printf("ReportConfigEUTRA::triggerType_event::eventId_eventA5:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int ReportConfigEUTRA::triggerType_event::eventId_eventA5::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int ReportConfigEUTRA::triggerType_event::eventId_eventA5::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != a5_Threshold1.Unpack(bits, idx))
        {
            printf("ReportConfigEUTRA::triggerType_event::eventId_eventA5:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != a5_Threshold2.Unpack(bits, idx))
        {
            printf("ReportConfigEUTRA::triggerType_event::eventId_eventA5:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string ReportConfigEUTRA::triggerType_event::eventId_eventA5::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "eventA5:\n";
    out += a5_Threshold1_ToString(indent+1);
    out += a5_Threshold2_ToString(indent+1);
    return out;
}

std::string ReportConfigEUTRA::triggerType_event::eventId_eventA5::ToStringNoNewLines() const
{
    std::string out = "eventA5:";
    out += a5_Threshold1_ToStringNoNewLines();
    out += a5_Threshold2_ToStringNoNewLines();
    return out;
}

ThresholdEUTRA* ReportConfigEUTRA::triggerType_event::eventId_eventA5::a5_Threshold1_Set()
{
    a5_Threshold1_present = true;
    return &a5_Threshold1;
}

int ReportConfigEUTRA::triggerType_event::eventId_eventA5::a5_Threshold1_Set(ThresholdEUTRA &value)
{
    a5_Threshold1_present = true;
    a5_Threshold1 = value;
    return 0;
}

const ThresholdEUTRA& ReportConfigEUTRA::triggerType_event::eventId_eventA5::a5_Threshold1_Get() const
{
    return a5_Threshold1;
}

std::string ReportConfigEUTRA::triggerType_event::eventId_eventA5::a5_Threshold1_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "a5_Threshold1:\n";
    out += a5_Threshold1.ToString(indent+1);
    return out;
}

std::string ReportConfigEUTRA::triggerType_event::eventId_eventA5::a5_Threshold1_ToStringNoNewLines() const
{
    std::string out = "a5_Threshold1:";
    out += a5_Threshold1.ToStringNoNewLines();
    return out;
}

int ReportConfigEUTRA::triggerType_event::eventId_eventA5::a5_Threshold1_Clear()
{
    a5_Threshold1_present = false;
    return 0;
}

bool ReportConfigEUTRA::triggerType_event::eventId_eventA5::a5_Threshold1_IsPresent() const
{
    return a5_Threshold1_present;
}

ThresholdEUTRA* ReportConfigEUTRA::triggerType_event::eventId_eventA5::a5_Threshold2_Set()
{
    a5_Threshold2_present = true;
    return &a5_Threshold2;
}

int ReportConfigEUTRA::triggerType_event::eventId_eventA5::a5_Threshold2_Set(ThresholdEUTRA &value)
{
    a5_Threshold2_present = true;
    a5_Threshold2 = value;
    return 0;
}

const ThresholdEUTRA& ReportConfigEUTRA::triggerType_event::eventId_eventA5::a5_Threshold2_Get() const
{
    return a5_Threshold2;
}

std::string ReportConfigEUTRA::triggerType_event::eventId_eventA5::a5_Threshold2_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "a5_Threshold2:\n";
    out += a5_Threshold2.ToString(indent+1);
    return out;
}

std::string ReportConfigEUTRA::triggerType_event::eventId_eventA5::a5_Threshold2_ToStringNoNewLines() const
{
    std::string out = "a5_Threshold2:";
    out += a5_Threshold2.ToStringNoNewLines();
    return out;
}

int ReportConfigEUTRA::triggerType_event::eventId_eventA5::a5_Threshold2_Clear()
{
    a5_Threshold2_present = false;
    return 0;
}

bool ReportConfigEUTRA::triggerType_event::eventId_eventA5::a5_Threshold2_IsPresent() const
{
    return a5_Threshold2_present;
}

int ReportConfigEUTRA::triggerType_event::eventId_eventA6::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != a6_Offset_Pack(bits))
        {
            printf("ReportConfigEUTRA::triggerType_event::eventId_eventA6:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != a6_ReportOnLeave_Pack(bits))
        {
            printf("ReportConfigEUTRA::triggerType_event::eventId_eventA6:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int ReportConfigEUTRA::triggerType_event::eventId_eventA6::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int ReportConfigEUTRA::triggerType_event::eventId_eventA6::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != a6_Offset_Unpack(bits, idx))
        {
            printf("ReportConfigEUTRA::triggerType_event::eventId_eventA6:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != a6_ReportOnLeave_Unpack(bits, idx))
        {
            printf("ReportConfigEUTRA::triggerType_event::eventId_eventA6:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string ReportConfigEUTRA::triggerType_event::eventId_eventA6::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "eventA6:\n";
    out += a6_Offset_ToString(indent+1);
    out += a6_ReportOnLeave_ToString(indent+1);
    return out;
}

std::string ReportConfigEUTRA::triggerType_event::eventId_eventA6::ToStringNoNewLines() const
{
    std::string out = "eventA6:";
    out += a6_Offset_ToStringNoNewLines();
    out += a6_ReportOnLeave_ToStringNoNewLines();
    return out;
}

int ReportConfigEUTRA::triggerType_event::eventId_eventA6::a6_Offset_Pack(std::vector<uint8_t> &bits)
{
    if(!a6_Offset_present)
    {
        printf("ReportConfigEUTRA::triggerType_event::eventId_eventA6::a6_Offset_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = a6_Offset_internal_value - (-30);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (30 - -30))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int ReportConfigEUTRA::triggerType_event::eventId_eventA6::a6_Offset_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return a6_Offset_Unpack(bits, idx);
}

int ReportConfigEUTRA::triggerType_event::eventId_eventA6::a6_Offset_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (30 - -30))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("ReportConfigEUTRA::triggerType_event::eventId_eventA6::a6_Offset_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    a6_Offset_internal_value = packed_val + -30;
    a6_Offset_present = true;
    return 0;
}

int64_t ReportConfigEUTRA::triggerType_event::eventId_eventA6::a6_Offset_Value() const
{
    if(a6_Offset_present)
        return a6_Offset_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int ReportConfigEUTRA::triggerType_event::eventId_eventA6::a6_Offset_SetValue(int64_t value)
{
    if(value < -30 || value > 30)
    {
        printf("ReportConfigEUTRA::triggerType_event::eventId_eventA6::a6_Offset_SetValue() range failure\n");
        return -1;
    }
    a6_Offset_internal_value = value;
    a6_Offset_present = true;
    return 0;
}

std::string ReportConfigEUTRA::triggerType_event::eventId_eventA6::a6_Offset_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "a6_Offset = " + std::to_string(a6_Offset_internal_value) + "\n";
    return out;
}

std::string ReportConfigEUTRA::triggerType_event::eventId_eventA6::a6_Offset_ToStringNoNewLines() const
{
    std::string out = "a6_Offset=" + std::to_string(a6_Offset_internal_value) + ",";
    return out;
}

int ReportConfigEUTRA::triggerType_event::eventId_eventA6::a6_Offset_Clear()
{
    a6_Offset_present = false;
    return 0;
}

bool ReportConfigEUTRA::triggerType_event::eventId_eventA6::a6_Offset_IsPresent() const
{
    return a6_Offset_present;
}

int ReportConfigEUTRA::triggerType_event::eventId_eventA6::a6_ReportOnLeave_Pack(std::vector<uint8_t> &bits)
{
    if(!a6_ReportOnLeave_present)
    {
        printf("ReportConfigEUTRA::triggerType_event::eventId_eventA6::a6_ReportOnLeave_Pack() presence failure\n");
        return -1;
    }
    bits.push_back(a6_ReportOnLeave_internal_value);
    return 0;
}

int ReportConfigEUTRA::triggerType_event::eventId_eventA6::a6_ReportOnLeave_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return a6_ReportOnLeave_Unpack(bits, idx);
}

int ReportConfigEUTRA::triggerType_event::eventId_eventA6::a6_ReportOnLeave_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    if((idx + 1) > bits.size())
    {
        printf("ReportConfigEUTRA::triggerType_event::eventId_eventA6::a6_ReportOnLeave_Unpack() index out of bounds\n");
        return -1;
    }
    a6_ReportOnLeave_internal_value = bits[idx++];
    a6_ReportOnLeave_present = true;
    return 0;
}

bool ReportConfigEUTRA::triggerType_event::eventId_eventA6::a6_ReportOnLeave_Value() const
{
    if(a6_ReportOnLeave_present)
        return a6_ReportOnLeave_internal_value;
    return false;
}

int ReportConfigEUTRA::triggerType_event::eventId_eventA6::a6_ReportOnLeave_SetValue(bool value)
{
    a6_ReportOnLeave_internal_value = value;
    a6_ReportOnLeave_present = true;
    return 0;
}

std::string ReportConfigEUTRA::triggerType_event::eventId_eventA6::a6_ReportOnLeave_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "a6_ReportOnLeave = " + std::to_string(a6_ReportOnLeave_internal_value) + "\n";
    return out;
}

std::string ReportConfigEUTRA::triggerType_event::eventId_eventA6::a6_ReportOnLeave_ToStringNoNewLines() const
{
    std::string out = "a6_ReportOnLeave=" + std::to_string(a6_ReportOnLeave_internal_value) + ",";
    return out;
}

int ReportConfigEUTRA::triggerType_event::eventId_eventA6::a6_ReportOnLeave_Clear()
{
    a6_ReportOnLeave_present = false;
    return 0;
}

bool ReportConfigEUTRA::triggerType_event::eventId_eventA6::a6_ReportOnLeave_IsPresent() const
{
    return a6_ReportOnLeave_present;
}

Hysteresis* ReportConfigEUTRA::triggerType_event::hysteresis_Set()
{
    hysteresis_present = true;
    return &hysteresis;
}

int ReportConfigEUTRA::triggerType_event::hysteresis_Set(Hysteresis &value)
{
    hysteresis_present = true;
    hysteresis = value;
    return 0;
}

const Hysteresis& ReportConfigEUTRA::triggerType_event::hysteresis_Get() const
{
    return hysteresis;
}

std::string ReportConfigEUTRA::triggerType_event::hysteresis_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "hysteresis:\n";
    out += hysteresis.ToString(indent+1);
    return out;
}

std::string ReportConfigEUTRA::triggerType_event::hysteresis_ToStringNoNewLines() const
{
    std::string out = "hysteresis:";
    out += hysteresis.ToStringNoNewLines();
    return out;
}

int ReportConfigEUTRA::triggerType_event::hysteresis_Clear()
{
    hysteresis_present = false;
    return 0;
}

bool ReportConfigEUTRA::triggerType_event::hysteresis_IsPresent() const
{
    return hysteresis_present;
}

TimeToTrigger* ReportConfigEUTRA::triggerType_event::timeToTrigger_Set()
{
    timeToTrigger_present = true;
    return &timeToTrigger;
}

int ReportConfigEUTRA::triggerType_event::timeToTrigger_Set(TimeToTrigger &value)
{
    timeToTrigger_present = true;
    timeToTrigger = value;
    return 0;
}

const TimeToTrigger& ReportConfigEUTRA::triggerType_event::timeToTrigger_Get() const
{
    return timeToTrigger;
}

std::string ReportConfigEUTRA::triggerType_event::timeToTrigger_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "timeToTrigger:\n";
    out += timeToTrigger.ToString(indent+1);
    return out;
}

std::string ReportConfigEUTRA::triggerType_event::timeToTrigger_ToStringNoNewLines() const
{
    std::string out = "timeToTrigger:";
    out += timeToTrigger.ToStringNoNewLines();
    return out;
}

int ReportConfigEUTRA::triggerType_event::timeToTrigger_Clear()
{
    timeToTrigger_present = false;
    return 0;
}

bool ReportConfigEUTRA::triggerType_event::timeToTrigger_IsPresent() const
{
    return timeToTrigger_present;
}

int ReportConfigEUTRA::triggerType_periodical::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != purpose_Pack(bits))
        {
            printf("ReportConfigEUTRA::triggerType_periodical:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int ReportConfigEUTRA::triggerType_periodical::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int ReportConfigEUTRA::triggerType_periodical::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != purpose_Unpack(bits, idx))
        {
            printf("ReportConfigEUTRA::triggerType_periodical:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string ReportConfigEUTRA::triggerType_periodical::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "periodical:\n";
    out += purpose_ToString(indent+1);
    return out;
}

std::string ReportConfigEUTRA::triggerType_periodical::ToStringNoNewLines() const
{
    std::string out = "periodical:";
    out += purpose_ToStringNoNewLines();
    return out;
}

int ReportConfigEUTRA::triggerType_periodical::purpose_Pack(std::vector<uint8_t> &bits)
{
    if(!purpose_present)
    {
        printf("ReportConfigEUTRA::triggerType_periodical::purpose_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((purpose_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int ReportConfigEUTRA::triggerType_periodical::purpose_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return purpose_Unpack(bits, idx);
}

int ReportConfigEUTRA::triggerType_periodical::purpose_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("ReportConfigEUTRA::triggerType_periodical::purpose_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 1)
    {
        printf("ReportConfigEUTRA::triggerType_periodical::purpose_Unpack() max failure\n");
        return -1;
    }
    purpose_internal_value = (purpose_Enum)packed_val;
    purpose_present = true;
    return 0;
}

ReportConfigEUTRA::triggerType_periodical::purpose_Enum ReportConfigEUTRA::triggerType_periodical::purpose_Value() const
{
    if(purpose_present)
        return purpose_internal_value;
    return (ReportConfigEUTRA::triggerType_periodical::purpose_Enum)0;
}

int ReportConfigEUTRA::triggerType_periodical::purpose_SetValue(purpose_Enum value)
{
    purpose_internal_value = value;
    purpose_present = true;
    return 0;
}

int ReportConfigEUTRA::triggerType_periodical::purpose_SetValue(std::string value)
{
    if("reportStrongestCells" == value)
    {
        purpose_internal_value = k_purpose_reportStrongestCells;
        purpose_present = true;
        return 0;
    }
    if("reportCGI" == value)
    {
        purpose_internal_value = k_purpose_reportCGI;
        purpose_present = true;
        return 0;
    }
    return 1;
}

std::string ReportConfigEUTRA::triggerType_periodical::purpose_ValueToString(purpose_Enum value) const
{
    if(k_purpose_reportStrongestCells == value)
        return "reportStrongestCells";
    if(k_purpose_reportCGI == value)
        return "reportCGI";
    return "";
}

uint64_t ReportConfigEUTRA::triggerType_periodical::purpose_NumberOfValues() const
{
    return 2;
}

std::string ReportConfigEUTRA::triggerType_periodical::purpose_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "purpose = " + purpose_ValueToString(purpose_internal_value) + "\n";
    return out;
}

std::string ReportConfigEUTRA::triggerType_periodical::purpose_ToStringNoNewLines() const
{
    std::string out = "purpose=" + purpose_ValueToString(purpose_internal_value) + ",";
    return out;
}

int ReportConfigEUTRA::triggerType_periodical::purpose_Clear()
{
    purpose_present = false;
    return 0;
}

bool ReportConfigEUTRA::triggerType_periodical::purpose_IsPresent() const
{
    return purpose_present;
}

int ReportConfigEUTRA::triggerQuantity_Pack(std::vector<uint8_t> &bits)
{
    if(!triggerQuantity_present)
    {
        printf("ReportConfigEUTRA::triggerQuantity_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((triggerQuantity_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int ReportConfigEUTRA::triggerQuantity_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return triggerQuantity_Unpack(bits, idx);
}

int ReportConfigEUTRA::triggerQuantity_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("ReportConfigEUTRA::triggerQuantity_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 1)
    {
        printf("ReportConfigEUTRA::triggerQuantity_Unpack() max failure\n");
        return -1;
    }
    triggerQuantity_internal_value = (triggerQuantity_Enum)packed_val;
    triggerQuantity_present = true;
    return 0;
}

ReportConfigEUTRA::triggerQuantity_Enum ReportConfigEUTRA::triggerQuantity_Value() const
{
    if(triggerQuantity_present)
        return triggerQuantity_internal_value;
    return (ReportConfigEUTRA::triggerQuantity_Enum)0;
}

int ReportConfigEUTRA::triggerQuantity_SetValue(triggerQuantity_Enum value)
{
    triggerQuantity_internal_value = value;
    triggerQuantity_present = true;
    return 0;
}

int ReportConfigEUTRA::triggerQuantity_SetValue(std::string value)
{
    if("rsrp" == value)
    {
        triggerQuantity_internal_value = k_triggerQuantity_rsrp;
        triggerQuantity_present = true;
        return 0;
    }
    if("rsrq" == value)
    {
        triggerQuantity_internal_value = k_triggerQuantity_rsrq;
        triggerQuantity_present = true;
        return 0;
    }
    return 1;
}

std::string ReportConfigEUTRA::triggerQuantity_ValueToString(triggerQuantity_Enum value) const
{
    if(k_triggerQuantity_rsrp == value)
        return "rsrp";
    if(k_triggerQuantity_rsrq == value)
        return "rsrq";
    return "";
}

uint64_t ReportConfigEUTRA::triggerQuantity_NumberOfValues() const
{
    return 2;
}

std::string ReportConfigEUTRA::triggerQuantity_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "triggerQuantity = " + triggerQuantity_ValueToString(triggerQuantity_internal_value) + "\n";
    return out;
}

std::string ReportConfigEUTRA::triggerQuantity_ToStringNoNewLines() const
{
    std::string out = "triggerQuantity=" + triggerQuantity_ValueToString(triggerQuantity_internal_value) + ",";
    return out;
}

int ReportConfigEUTRA::triggerQuantity_Clear()
{
    triggerQuantity_present = false;
    return 0;
}

bool ReportConfigEUTRA::triggerQuantity_IsPresent() const
{
    return triggerQuantity_present;
}

int ReportConfigEUTRA::reportQuantity_Pack(std::vector<uint8_t> &bits)
{
    if(!reportQuantity_present)
    {
        printf("ReportConfigEUTRA::reportQuantity_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((reportQuantity_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int ReportConfigEUTRA::reportQuantity_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return reportQuantity_Unpack(bits, idx);
}

int ReportConfigEUTRA::reportQuantity_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("ReportConfigEUTRA::reportQuantity_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 1)
    {
        printf("ReportConfigEUTRA::reportQuantity_Unpack() max failure\n");
        return -1;
    }
    reportQuantity_internal_value = (reportQuantity_Enum)packed_val;
    reportQuantity_present = true;
    return 0;
}

ReportConfigEUTRA::reportQuantity_Enum ReportConfigEUTRA::reportQuantity_Value() const
{
    if(reportQuantity_present)
        return reportQuantity_internal_value;
    return (ReportConfigEUTRA::reportQuantity_Enum)0;
}

int ReportConfigEUTRA::reportQuantity_SetValue(reportQuantity_Enum value)
{
    reportQuantity_internal_value = value;
    reportQuantity_present = true;
    return 0;
}

int ReportConfigEUTRA::reportQuantity_SetValue(std::string value)
{
    if("sameAsTriggerQuantity" == value)
    {
        reportQuantity_internal_value = k_reportQuantity_sameAsTriggerQuantity;
        reportQuantity_present = true;
        return 0;
    }
    if("both" == value)
    {
        reportQuantity_internal_value = k_reportQuantity_both;
        reportQuantity_present = true;
        return 0;
    }
    return 1;
}

std::string ReportConfigEUTRA::reportQuantity_ValueToString(reportQuantity_Enum value) const
{
    if(k_reportQuantity_sameAsTriggerQuantity == value)
        return "sameAsTriggerQuantity";
    if(k_reportQuantity_both == value)
        return "both";
    return "";
}

uint64_t ReportConfigEUTRA::reportQuantity_NumberOfValues() const
{
    return 2;
}

std::string ReportConfigEUTRA::reportQuantity_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "reportQuantity = " + reportQuantity_ValueToString(reportQuantity_internal_value) + "\n";
    return out;
}

std::string ReportConfigEUTRA::reportQuantity_ToStringNoNewLines() const
{
    std::string out = "reportQuantity=" + reportQuantity_ValueToString(reportQuantity_internal_value) + ",";
    return out;
}

int ReportConfigEUTRA::reportQuantity_Clear()
{
    reportQuantity_present = false;
    return 0;
}

bool ReportConfigEUTRA::reportQuantity_IsPresent() const
{
    return reportQuantity_present;
}

#include "maxCellReport.h"

int ReportConfigEUTRA::maxReportCells_Pack(std::vector<uint8_t> &bits)
{
    if(!maxReportCells_present)
    {
        printf("ReportConfigEUTRA::maxReportCells_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = maxReportCells_internal_value - (1);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (maxCellReport - 1))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int ReportConfigEUTRA::maxReportCells_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return maxReportCells_Unpack(bits, idx);
}

int ReportConfigEUTRA::maxReportCells_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (maxCellReport - 1))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("ReportConfigEUTRA::maxReportCells_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    maxReportCells_internal_value = packed_val + 1;
    maxReportCells_present = true;
    return 0;
}

int64_t ReportConfigEUTRA::maxReportCells_Value() const
{
    if(maxReportCells_present)
        return maxReportCells_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int ReportConfigEUTRA::maxReportCells_SetValue(int64_t value)
{
    if(value < 1 || value > maxCellReport)
    {
        printf("ReportConfigEUTRA::maxReportCells_SetValue() range failure\n");
        return -1;
    }
    maxReportCells_internal_value = value;
    maxReportCells_present = true;
    return 0;
}

std::string ReportConfigEUTRA::maxReportCells_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "maxReportCells = " + std::to_string(maxReportCells_internal_value) + "\n";
    return out;
}

std::string ReportConfigEUTRA::maxReportCells_ToStringNoNewLines() const
{
    std::string out = "maxReportCells=" + std::to_string(maxReportCells_internal_value) + ",";
    return out;
}

int ReportConfigEUTRA::maxReportCells_Clear()
{
    maxReportCells_present = false;
    return 0;
}

bool ReportConfigEUTRA::maxReportCells_IsPresent() const
{
    return maxReportCells_present;
}

ReportInterval* ReportConfigEUTRA::reportInterval_Set()
{
    reportInterval_present = true;
    return &reportInterval;
}

int ReportConfigEUTRA::reportInterval_Set(ReportInterval &value)
{
    reportInterval_present = true;
    reportInterval = value;
    return 0;
}

const ReportInterval& ReportConfigEUTRA::reportInterval_Get() const
{
    return reportInterval;
}

std::string ReportConfigEUTRA::reportInterval_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "reportInterval:\n";
    out += reportInterval.ToString(indent+1);
    return out;
}

std::string ReportConfigEUTRA::reportInterval_ToStringNoNewLines() const
{
    std::string out = "reportInterval:";
    out += reportInterval.ToStringNoNewLines();
    return out;
}

int ReportConfigEUTRA::reportInterval_Clear()
{
    reportInterval_present = false;
    return 0;
}

bool ReportConfigEUTRA::reportInterval_IsPresent() const
{
    return reportInterval_present;
}

int ReportConfigEUTRA::reportAmount_Pack(std::vector<uint8_t> &bits)
{
    if(!reportAmount_present)
    {
        printf("ReportConfigEUTRA::reportAmount_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 3;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((reportAmount_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int ReportConfigEUTRA::reportAmount_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return reportAmount_Unpack(bits, idx);
}

int ReportConfigEUTRA::reportAmount_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 3;
    if((idx + N_bits) > bits.size())
    {
        printf("ReportConfigEUTRA::reportAmount_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 7)
    {
        printf("ReportConfigEUTRA::reportAmount_Unpack() max failure\n");
        return -1;
    }
    reportAmount_internal_value = (reportAmount_Enum)packed_val;
    reportAmount_present = true;
    return 0;
}

ReportConfigEUTRA::reportAmount_Enum ReportConfigEUTRA::reportAmount_Value() const
{
    if(reportAmount_present)
        return reportAmount_internal_value;
    return (ReportConfigEUTRA::reportAmount_Enum)0;
}

int ReportConfigEUTRA::reportAmount_SetValue(reportAmount_Enum value)
{
    reportAmount_internal_value = value;
    reportAmount_present = true;
    return 0;
}

int ReportConfigEUTRA::reportAmount_SetValue(std::string value)
{
    if("r1" == value)
    {
        reportAmount_internal_value = k_reportAmount_r1;
        reportAmount_present = true;
        return 0;
    }
    if("r2" == value)
    {
        reportAmount_internal_value = k_reportAmount_r2;
        reportAmount_present = true;
        return 0;
    }
    if("r4" == value)
    {
        reportAmount_internal_value = k_reportAmount_r4;
        reportAmount_present = true;
        return 0;
    }
    if("r8" == value)
    {
        reportAmount_internal_value = k_reportAmount_r8;
        reportAmount_present = true;
        return 0;
    }
    if("r16" == value)
    {
        reportAmount_internal_value = k_reportAmount_r16;
        reportAmount_present = true;
        return 0;
    }
    if("r32" == value)
    {
        reportAmount_internal_value = k_reportAmount_r32;
        reportAmount_present = true;
        return 0;
    }
    if("r64" == value)
    {
        reportAmount_internal_value = k_reportAmount_r64;
        reportAmount_present = true;
        return 0;
    }
    if("infinity" == value)
    {
        reportAmount_internal_value = k_reportAmount_infinity;
        reportAmount_present = true;
        return 0;
    }
    return 1;
}

std::string ReportConfigEUTRA::reportAmount_ValueToString(reportAmount_Enum value) const
{
    if(k_reportAmount_r1 == value)
        return "r1";
    if(k_reportAmount_r2 == value)
        return "r2";
    if(k_reportAmount_r4 == value)
        return "r4";
    if(k_reportAmount_r8 == value)
        return "r8";
    if(k_reportAmount_r16 == value)
        return "r16";
    if(k_reportAmount_r32 == value)
        return "r32";
    if(k_reportAmount_r64 == value)
        return "r64";
    if(k_reportAmount_infinity == value)
        return "infinity";
    return "";
}

uint64_t ReportConfigEUTRA::reportAmount_NumberOfValues() const
{
    return 8;
}

std::string ReportConfigEUTRA::reportAmount_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "reportAmount = " + reportAmount_ValueToString(reportAmount_internal_value) + "\n";
    return out;
}

std::string ReportConfigEUTRA::reportAmount_ToStringNoNewLines() const
{
    std::string out = "reportAmount=" + reportAmount_ValueToString(reportAmount_internal_value) + ",";
    return out;
}

int ReportConfigEUTRA::reportAmount_Clear()
{
    reportAmount_present = false;
    return 0;
}

bool ReportConfigEUTRA::reportAmount_IsPresent() const
{
    return reportAmount_present;
}

int ReportConfigEUTRA::si_RequestForHO_r9_Pack(std::vector<uint8_t> &bits)
{
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((si_RequestForHO_r9_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int ReportConfigEUTRA::si_RequestForHO_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return si_RequestForHO_r9_Unpack(bits, idx);
}

int ReportConfigEUTRA::si_RequestForHO_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("ReportConfigEUTRA::si_RequestForHO_r9_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 0)
    {
        printf("ReportConfigEUTRA::si_RequestForHO_r9_Unpack() max failure\n");
        return -1;
    }
    si_RequestForHO_r9_internal_value = (si_RequestForHO_r9_Enum)packed_val;
    si_RequestForHO_r9_present = true;
    return 0;
}

ReportConfigEUTRA::si_RequestForHO_r9_Enum ReportConfigEUTRA::si_RequestForHO_r9_Value() const
{
    if(si_RequestForHO_r9_present)
        return si_RequestForHO_r9_internal_value;
    return (ReportConfigEUTRA::si_RequestForHO_r9_Enum)0;
}

int ReportConfigEUTRA::si_RequestForHO_r9_SetValue(si_RequestForHO_r9_Enum value)
{
    si_RequestForHO_r9_internal_value = value;
    si_RequestForHO_r9_present = true;
    return 0;
}

int ReportConfigEUTRA::si_RequestForHO_r9_SetValue(std::string value)
{
    if("setup" == value)
    {
        si_RequestForHO_r9_internal_value = k_si_RequestForHO_r9_setup;
        si_RequestForHO_r9_present = true;
        return 0;
    }
    return 1;
}

std::string ReportConfigEUTRA::si_RequestForHO_r9_ValueToString(si_RequestForHO_r9_Enum value) const
{
    if(k_si_RequestForHO_r9_setup == value)
        return "setup";
    return "";
}

uint64_t ReportConfigEUTRA::si_RequestForHO_r9_NumberOfValues() const
{
    return 1;
}

std::string ReportConfigEUTRA::si_RequestForHO_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "si_RequestForHO_r9 = " + si_RequestForHO_r9_ValueToString(si_RequestForHO_r9_internal_value) + "\n";
    return out;
}

std::string ReportConfigEUTRA::si_RequestForHO_r9_ToStringNoNewLines() const
{
    std::string out = "si_RequestForHO_r9=" + si_RequestForHO_r9_ValueToString(si_RequestForHO_r9_internal_value) + ",";
    return out;
}

int ReportConfigEUTRA::si_RequestForHO_r9_Clear()
{
    si_RequestForHO_r9_present = false;
    return 0;
}

bool ReportConfigEUTRA::si_RequestForHO_r9_IsPresent() const
{
    return si_RequestForHO_r9_present;
}

int ReportConfigEUTRA::ue_RxTxTimeDiffPeriodical_r9_Pack(std::vector<uint8_t> &bits)
{
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((ue_RxTxTimeDiffPeriodical_r9_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int ReportConfigEUTRA::ue_RxTxTimeDiffPeriodical_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return ue_RxTxTimeDiffPeriodical_r9_Unpack(bits, idx);
}

int ReportConfigEUTRA::ue_RxTxTimeDiffPeriodical_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("ReportConfigEUTRA::ue_RxTxTimeDiffPeriodical_r9_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 0)
    {
        printf("ReportConfigEUTRA::ue_RxTxTimeDiffPeriodical_r9_Unpack() max failure\n");
        return -1;
    }
    ue_RxTxTimeDiffPeriodical_r9_internal_value = (ue_RxTxTimeDiffPeriodical_r9_Enum)packed_val;
    ue_RxTxTimeDiffPeriodical_r9_present = true;
    return 0;
}

ReportConfigEUTRA::ue_RxTxTimeDiffPeriodical_r9_Enum ReportConfigEUTRA::ue_RxTxTimeDiffPeriodical_r9_Value() const
{
    if(ue_RxTxTimeDiffPeriodical_r9_present)
        return ue_RxTxTimeDiffPeriodical_r9_internal_value;
    return (ReportConfigEUTRA::ue_RxTxTimeDiffPeriodical_r9_Enum)0;
}

int ReportConfigEUTRA::ue_RxTxTimeDiffPeriodical_r9_SetValue(ue_RxTxTimeDiffPeriodical_r9_Enum value)
{
    ue_RxTxTimeDiffPeriodical_r9_internal_value = value;
    ue_RxTxTimeDiffPeriodical_r9_present = true;
    return 0;
}

int ReportConfigEUTRA::ue_RxTxTimeDiffPeriodical_r9_SetValue(std::string value)
{
    if("setup" == value)
    {
        ue_RxTxTimeDiffPeriodical_r9_internal_value = k_ue_RxTxTimeDiffPeriodical_r9_setup;
        ue_RxTxTimeDiffPeriodical_r9_present = true;
        return 0;
    }
    return 1;
}

std::string ReportConfigEUTRA::ue_RxTxTimeDiffPeriodical_r9_ValueToString(ue_RxTxTimeDiffPeriodical_r9_Enum value) const
{
    if(k_ue_RxTxTimeDiffPeriodical_r9_setup == value)
        return "setup";
    return "";
}

uint64_t ReportConfigEUTRA::ue_RxTxTimeDiffPeriodical_r9_NumberOfValues() const
{
    return 1;
}

std::string ReportConfigEUTRA::ue_RxTxTimeDiffPeriodical_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ue_RxTxTimeDiffPeriodical_r9 = " + ue_RxTxTimeDiffPeriodical_r9_ValueToString(ue_RxTxTimeDiffPeriodical_r9_internal_value) + "\n";
    return out;
}

std::string ReportConfigEUTRA::ue_RxTxTimeDiffPeriodical_r9_ToStringNoNewLines() const
{
    std::string out = "ue_RxTxTimeDiffPeriodical_r9=" + ue_RxTxTimeDiffPeriodical_r9_ValueToString(ue_RxTxTimeDiffPeriodical_r9_internal_value) + ",";
    return out;
}

int ReportConfigEUTRA::ue_RxTxTimeDiffPeriodical_r9_Clear()
{
    ue_RxTxTimeDiffPeriodical_r9_present = false;
    return 0;
}

bool ReportConfigEUTRA::ue_RxTxTimeDiffPeriodical_r9_IsPresent() const
{
    return ue_RxTxTimeDiffPeriodical_r9_present;
}

int ReportConfigEUTRA::includeLocationInfo_r10_Pack(std::vector<uint8_t> &bits)
{
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((includeLocationInfo_r10_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int ReportConfigEUTRA::includeLocationInfo_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return includeLocationInfo_r10_Unpack(bits, idx);
}

int ReportConfigEUTRA::includeLocationInfo_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("ReportConfigEUTRA::includeLocationInfo_r10_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 0)
    {
        printf("ReportConfigEUTRA::includeLocationInfo_r10_Unpack() max failure\n");
        return -1;
    }
    includeLocationInfo_r10_internal_value = (includeLocationInfo_r10_Enum)packed_val;
    includeLocationInfo_r10_present = true;
    return 0;
}

ReportConfigEUTRA::includeLocationInfo_r10_Enum ReportConfigEUTRA::includeLocationInfo_r10_Value() const
{
    if(includeLocationInfo_r10_present)
        return includeLocationInfo_r10_internal_value;
    return (ReportConfigEUTRA::includeLocationInfo_r10_Enum)0;
}

int ReportConfigEUTRA::includeLocationInfo_r10_SetValue(includeLocationInfo_r10_Enum value)
{
    includeLocationInfo_r10_internal_value = value;
    includeLocationInfo_r10_present = true;
    return 0;
}

int ReportConfigEUTRA::includeLocationInfo_r10_SetValue(std::string value)
{
    if("true" == value)
    {
        includeLocationInfo_r10_internal_value = k_includeLocationInfo_r10_true;
        includeLocationInfo_r10_present = true;
        return 0;
    }
    return 1;
}

std::string ReportConfigEUTRA::includeLocationInfo_r10_ValueToString(includeLocationInfo_r10_Enum value) const
{
    if(k_includeLocationInfo_r10_true == value)
        return "true";
    return "";
}

uint64_t ReportConfigEUTRA::includeLocationInfo_r10_NumberOfValues() const
{
    return 1;
}

std::string ReportConfigEUTRA::includeLocationInfo_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "includeLocationInfo_r10 = " + includeLocationInfo_r10_ValueToString(includeLocationInfo_r10_internal_value) + "\n";
    return out;
}

std::string ReportConfigEUTRA::includeLocationInfo_r10_ToStringNoNewLines() const
{
    std::string out = "includeLocationInfo_r10=" + includeLocationInfo_r10_ValueToString(includeLocationInfo_r10_internal_value) + ",";
    return out;
}

int ReportConfigEUTRA::includeLocationInfo_r10_Clear()
{
    includeLocationInfo_r10_present = false;
    return 0;
}

bool ReportConfigEUTRA::includeLocationInfo_r10_IsPresent() const
{
    return includeLocationInfo_r10_present;
}

int ReportConfigEUTRA::reportAddNeighMeas_r10_Pack(std::vector<uint8_t> &bits)
{
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((reportAddNeighMeas_r10_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int ReportConfigEUTRA::reportAddNeighMeas_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return reportAddNeighMeas_r10_Unpack(bits, idx);
}

int ReportConfigEUTRA::reportAddNeighMeas_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("ReportConfigEUTRA::reportAddNeighMeas_r10_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 0)
    {
        printf("ReportConfigEUTRA::reportAddNeighMeas_r10_Unpack() max failure\n");
        return -1;
    }
    reportAddNeighMeas_r10_internal_value = (reportAddNeighMeas_r10_Enum)packed_val;
    reportAddNeighMeas_r10_present = true;
    return 0;
}

ReportConfigEUTRA::reportAddNeighMeas_r10_Enum ReportConfigEUTRA::reportAddNeighMeas_r10_Value() const
{
    if(reportAddNeighMeas_r10_present)
        return reportAddNeighMeas_r10_internal_value;
    return (ReportConfigEUTRA::reportAddNeighMeas_r10_Enum)0;
}

int ReportConfigEUTRA::reportAddNeighMeas_r10_SetValue(reportAddNeighMeas_r10_Enum value)
{
    reportAddNeighMeas_r10_internal_value = value;
    reportAddNeighMeas_r10_present = true;
    return 0;
}

int ReportConfigEUTRA::reportAddNeighMeas_r10_SetValue(std::string value)
{
    if("setup" == value)
    {
        reportAddNeighMeas_r10_internal_value = k_reportAddNeighMeas_r10_setup;
        reportAddNeighMeas_r10_present = true;
        return 0;
    }
    return 1;
}

std::string ReportConfigEUTRA::reportAddNeighMeas_r10_ValueToString(reportAddNeighMeas_r10_Enum value) const
{
    if(k_reportAddNeighMeas_r10_setup == value)
        return "setup";
    return "";
}

uint64_t ReportConfigEUTRA::reportAddNeighMeas_r10_NumberOfValues() const
{
    return 1;
}

std::string ReportConfigEUTRA::reportAddNeighMeas_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "reportAddNeighMeas_r10 = " + reportAddNeighMeas_r10_ValueToString(reportAddNeighMeas_r10_internal_value) + "\n";
    return out;
}

std::string ReportConfigEUTRA::reportAddNeighMeas_r10_ToStringNoNewLines() const
{
    std::string out = "reportAddNeighMeas_r10=" + reportAddNeighMeas_r10_ValueToString(reportAddNeighMeas_r10_internal_value) + ",";
    return out;
}

int ReportConfigEUTRA::reportAddNeighMeas_r10_Clear()
{
    reportAddNeighMeas_r10_present = false;
    return 0;
}

bool ReportConfigEUTRA::reportAddNeighMeas_r10_IsPresent() const
{
    return reportAddNeighMeas_r10_present;
}

