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

#include "ReportConfigInterRAT.h"

#include <cmath>

int ReportConfigInterRAT::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator
    bool has_extension = false;
    if(si_RequestForHO_r9_IsPresent() || reportQuantityUTRA_FDD_r10_IsPresent())
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
            printf("ReportConfigInterRAT:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != maxReportCells_Pack(bits))
        {
            printf("ReportConfigInterRAT:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != reportInterval.Pack(bits))
        {
            printf("ReportConfigInterRAT:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != reportAmount_Pack(bits))
        {
            printf("ReportConfigInterRAT:: field pack failure\n");
            return -1;
        }
    }

    // Extension
    if(has_extension)
    {
        // Number of extension fields
        if(1 < 64)
        {
            bits.push_back(0);
            for(uint32_t i=0; i<6; i++)
                bits.push_back((1 >> (6-i-1)) & 1);
        }else{
            printf("ReportConfigInterRAT:: Extension list size too large failure\n");
            return -1;
        }

        // Extension field presence indicators
        bits.push_back(si_RequestForHO_r9_IsPresent());
        bits.push_back(reportQuantityUTRA_FDD_r10_IsPresent());

        // Extension fields
        if(si_RequestForHO_r9_IsPresent())
        {
            std::vector<uint8_t> field_bits;
            if(0 != si_RequestForHO_r9_Pack(field_bits))
            {
                printf("ReportConfigInterRAT:: field pack failure\n");
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
        if(reportQuantityUTRA_FDD_r10_IsPresent())
        {
            std::vector<uint8_t> field_bits;
            if(0 != reportQuantityUTRA_FDD_r10_Pack(field_bits))
            {
                printf("ReportConfigInterRAT:: field pack failure\n");
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

int ReportConfigInterRAT::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int ReportConfigInterRAT::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("ReportConfigInterRAT::Unpack() index out of bounds for extension\n");
        return -1;
    }
    bool has_extension = bits[idx++];

    // Optional indicators

    // Fields
    {
        if(0 != triggerType_Unpack(bits, idx))
        {
            printf("ReportConfigInterRAT:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != maxReportCells_Unpack(bits, idx))
        {
            printf("ReportConfigInterRAT:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != reportInterval.Unpack(bits, idx))
        {
            printf("ReportConfigInterRAT:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != reportAmount_Unpack(bits, idx))
        {
            printf("ReportConfigInterRAT:: field unpack failure\n");
            return -1;
        }
    }

    // Extension
    if(has_extension)
    {
        if((idx + 7) > bits.size())
        {
            printf("ReportConfigInterRAT::Unpack() index out of bounds for extension size\n");
            return -1;
        }
        // Number of extension fields
        if(bits[idx++] != 0)
        {
            printf("ReportConfigInterRAT:: Extension list size too large failure\n");
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
                printf("ReportConfigInterRAT::Unpack() index out of bounds for optional indiator si_RequestForHO_r9\n");
                return -1;
            }
            si_RequestForHO_r9_present = bits[idx++];
        }
        if(opt_ind_count++ < N_ext_fields)
        {
            if((idx + 1) > bits.size())
            {
                printf("ReportConfigInterRAT::Unpack() index out of bounds for optional indiator reportQuantityUTRA_FDD_r10\n");
                return -1;
            }
            reportQuantityUTRA_FDD_r10_present = bits[idx++];
        }
        if((idx + (N_ext_fields - opt_ind_count)) > bits.size())
        {
            printf("ReportConfigInterRAT::Unpack() index out of bounds for extension optional indicators\n");
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
                printf("ReportConfigInterRAT:: field unpack failure\n");
                return -1;
            }
            idx = orig_idx + (N_octets * 8);
        }
        if(reportQuantityUTRA_FDD_r10_present)
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
            if(0 != reportQuantityUTRA_FDD_r10_Unpack(bits, idx))
            {
                printf("ReportConfigInterRAT:: field unpack failure\n");
                return -1;
            }
            idx = orig_idx + (N_octets * 8);
        }
        for(uint32_t i=2; i<N_ext_fields; i++)
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
            printf("ReportConfigInterRAT::Unpack() index out of bounds for extension fields\n");
            return -1;
        }
            idx += N_octets * 8;
        }
    }
    return 0;
}

std::string ReportConfigInterRAT::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ReportConfigInterRAT:\n";
    out += triggerType_ToString(indent+1);
    out += maxReportCells_ToString(indent+1);
    out += reportInterval_ToString(indent+1);
    out += reportAmount_ToString(indent+1);
    if(si_RequestForHO_r9_IsPresent())
        out += si_RequestForHO_r9_ToString(indent+1);
    if(reportQuantityUTRA_FDD_r10_IsPresent())
        out += reportQuantityUTRA_FDD_r10_ToString(indent+1);
    return out;
}

std::string ReportConfigInterRAT::ToStringNoNewLines() const
{
    std::string out = "ReportConfigInterRAT:";
    out += triggerType_ToStringNoNewLines();
    out += maxReportCells_ToStringNoNewLines();
    out += reportInterval_ToStringNoNewLines();
    out += reportAmount_ToStringNoNewLines();
    if(si_RequestForHO_r9_IsPresent())
        out += si_RequestForHO_r9_ToStringNoNewLines();
    if(reportQuantityUTRA_FDD_r10_IsPresent())
        out += reportQuantityUTRA_FDD_r10_ToStringNoNewLines();
    return out;
}

int ReportConfigInterRAT::triggerType_Pack(std::vector<uint8_t> &bits)
{
    if(!triggerType_present)
    {
        printf("ReportConfigInterRAT::triggerType_Pack() presence failure\n");
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
            printf("ReportConfigInterRAT::triggerType_event pack failure\n");
            return -1;
        }
    }
    if(triggerType_internal_choice == k_triggerType_periodical)
    {
        if(0 != triggerType_periodical_value.Pack(bits))
        {
            printf("ReportConfigInterRAT::triggerType_periodical pack failure\n");
            return -1;
        }
    }
    return 0;
}

int ReportConfigInterRAT::triggerType_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return triggerType_Unpack(bits, idx);
}

int ReportConfigInterRAT::triggerType_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 1) > bits.size())
    {
        printf("ReportConfigInterRAT::triggerType_Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<1; i++)
        packed_val |= bits[idx++] << (1-i-1);

    if((ReportConfigInterRAT::triggerType_Enum)packed_val > k_triggerType_periodical)
    {
        printf("ReportConfigInterRAT::triggerType_Unpack() choice range failure\n");
        return -1;
    }
    triggerType_internal_choice = (ReportConfigInterRAT::triggerType_Enum)packed_val;
    triggerType_present = true;

    // Fields
    if(triggerType_internal_choice == k_triggerType_event)
    {
        if(0 != triggerType_event_value.Unpack(bits, idx))
        {
            printf("ReportConfigInterRAT::triggerType_event unpack failure\n");
            return -1;
        }
    }
    if(triggerType_internal_choice == k_triggerType_periodical)
    {
        if(0 != triggerType_periodical_value.Unpack(bits, idx))
        {
            printf("ReportConfigInterRAT::triggerType_periodical unpack failure\n");
            return -1;
        }
    }
    return 0;
}

ReportConfigInterRAT::triggerType_Enum ReportConfigInterRAT::triggerType_Choice() const
{
    if(triggerType_present)
        return triggerType_internal_choice;
    return (ReportConfigInterRAT::triggerType_Enum)0;
}

int ReportConfigInterRAT::triggerType_SetChoice(ReportConfigInterRAT::triggerType_Enum choice)
{
    triggerType_internal_choice = choice;
    triggerType_present = true;
    return 0;
}

std::string ReportConfigInterRAT::triggerType_ChoiceToString(triggerType_Enum value) const
{
    if(k_triggerType_event == value)
        return "triggerType_event";
    if(k_triggerType_periodical == value)
        return "triggerType_periodical";
    return "";
}

uint64_t ReportConfigInterRAT::triggerType_NumberOfChoices() const
{
    return 2;
}

std::string ReportConfigInterRAT::triggerType_ToString(uint32_t indent) const
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

std::string ReportConfigInterRAT::triggerType_ToStringNoNewLines() const
{
    std::string out = "triggerType=" + triggerType_ChoiceToString(triggerType_internal_choice) + ",";
    if(triggerType_internal_choice == k_triggerType_event)
        out += triggerType_event_value.ToStringNoNewLines();
    if(triggerType_internal_choice == k_triggerType_periodical)
        out += triggerType_periodical_value.ToStringNoNewLines();
    return out;
}

int ReportConfigInterRAT::triggerType_Clear()
{
    triggerType_present = false;
    return 0;
}

bool ReportConfigInterRAT::triggerType_IsPresent() const
{
    return triggerType_present;
}

int ReportConfigInterRAT::triggerType_event::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != eventId_Pack(bits))
        {
            printf("ReportConfigInterRAT::triggerType_event:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != hysteresis.Pack(bits))
        {
            printf("ReportConfigInterRAT::triggerType_event:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != timeToTrigger.Pack(bits))
        {
            printf("ReportConfigInterRAT::triggerType_event:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int ReportConfigInterRAT::triggerType_event::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int ReportConfigInterRAT::triggerType_event::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != eventId_Unpack(bits, idx))
        {
            printf("ReportConfigInterRAT::triggerType_event:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != hysteresis.Unpack(bits, idx))
        {
            printf("ReportConfigInterRAT::triggerType_event:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != timeToTrigger.Unpack(bits, idx))
        {
            printf("ReportConfigInterRAT::triggerType_event:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string ReportConfigInterRAT::triggerType_event::ToString(uint32_t indent) const
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

std::string ReportConfigInterRAT::triggerType_event::ToStringNoNewLines() const
{
    std::string out = "event:";
    out += eventId_ToStringNoNewLines();
    out += hysteresis_ToStringNoNewLines();
    out += timeToTrigger_ToStringNoNewLines();
    return out;
}

int ReportConfigInterRAT::triggerType_event::eventId_Pack(std::vector<uint8_t> &bits)
{
    if(!eventId_present)
    {
        printf("ReportConfigInterRAT::triggerType_event::eventId_Pack() presence failure\n");
        return -1;
    }
    // Extension indicator
    bits.push_back(0);

    // Choice
    for(uint32_t i=0; i<1; i++)
        bits.push_back((eventId_internal_choice >> (1-i-1)) & 1);

    // Fields
    if(eventId_internal_choice == k_eventId_eventB1)
    {
        if(0 != eventId_eventB1_value.Pack(bits))
        {
            printf("ReportConfigInterRAT::triggerType_event::eventId_eventB1 pack failure\n");
            return -1;
        }
    }
    if(eventId_internal_choice == k_eventId_eventB2)
    {
        if(0 != eventId_eventB2_value.Pack(bits))
        {
            printf("ReportConfigInterRAT::triggerType_event::eventId_eventB2 pack failure\n");
            return -1;
        }
    }
    return 0;
}

int ReportConfigInterRAT::triggerType_event::eventId_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return eventId_Unpack(bits, idx);
}

int ReportConfigInterRAT::triggerType_event::eventId_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("ReportConfigInterRAT::triggerType_event::eventId_Unpack() index out of bounds for extension\n");
        return -1;
    }
    idx++;

    // Choice
    uint32_t packed_val = 0;
    if((idx + 1) > bits.size())
    {
        printf("ReportConfigInterRAT::triggerType_event::eventId_Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<1; i++)
        packed_val |= bits[idx++] << (1-i-1);

    if((ReportConfigInterRAT::triggerType_event::eventId_Enum)packed_val > k_eventId_eventB2)
    {
        printf("ReportConfigInterRAT::triggerType_event::eventId_Unpack() choice range failure\n");
        return -1;
    }
    eventId_internal_choice = (ReportConfigInterRAT::triggerType_event::eventId_Enum)packed_val;
    eventId_present = true;

    // Fields
    if(eventId_internal_choice == k_eventId_eventB1)
    {
        if(0 != eventId_eventB1_value.Unpack(bits, idx))
        {
            printf("ReportConfigInterRAT::triggerType_event::eventId_eventB1 unpack failure\n");
            return -1;
        }
    }
    if(eventId_internal_choice == k_eventId_eventB2)
    {
        if(0 != eventId_eventB2_value.Unpack(bits, idx))
        {
            printf("ReportConfigInterRAT::triggerType_event::eventId_eventB2 unpack failure\n");
            return -1;
        }
    }
    return 0;
}

ReportConfigInterRAT::triggerType_event::eventId_Enum ReportConfigInterRAT::triggerType_event::eventId_Choice() const
{
    if(eventId_present)
        return eventId_internal_choice;
    return (ReportConfigInterRAT::triggerType_event::eventId_Enum)0;
}

int ReportConfigInterRAT::triggerType_event::eventId_SetChoice(ReportConfigInterRAT::triggerType_event::eventId_Enum choice)
{
    eventId_internal_choice = choice;
    eventId_present = true;
    return 0;
}

std::string ReportConfigInterRAT::triggerType_event::eventId_ChoiceToString(eventId_Enum value) const
{
    if(k_eventId_eventB1 == value)
        return "eventId_eventB1";
    if(k_eventId_eventB2 == value)
        return "eventId_eventB2";
    return "";
}

uint64_t ReportConfigInterRAT::triggerType_event::eventId_NumberOfChoices() const
{
    return 2;
}

std::string ReportConfigInterRAT::triggerType_event::eventId_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "eventId = " + eventId_ChoiceToString(eventId_internal_choice) + ":\n";
    if(eventId_internal_choice == k_eventId_eventB1)
        out += eventId_eventB1_value.ToString(indent+1);
    if(eventId_internal_choice == k_eventId_eventB2)
        out += eventId_eventB2_value.ToString(indent+1);
    return out;
}

std::string ReportConfigInterRAT::triggerType_event::eventId_ToStringNoNewLines() const
{
    std::string out = "eventId=" + eventId_ChoiceToString(eventId_internal_choice) + ",";
    if(eventId_internal_choice == k_eventId_eventB1)
        out += eventId_eventB1_value.ToStringNoNewLines();
    if(eventId_internal_choice == k_eventId_eventB2)
        out += eventId_eventB2_value.ToStringNoNewLines();
    return out;
}

int ReportConfigInterRAT::triggerType_event::eventId_Clear()
{
    eventId_present = false;
    return 0;
}

bool ReportConfigInterRAT::triggerType_event::eventId_IsPresent() const
{
    return eventId_present;
}

int ReportConfigInterRAT::triggerType_event::eventId_eventB1::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != b1_Threshold_Pack(bits))
        {
            printf("ReportConfigInterRAT::triggerType_event::eventId_eventB1:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int ReportConfigInterRAT::triggerType_event::eventId_eventB1::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int ReportConfigInterRAT::triggerType_event::eventId_eventB1::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != b1_Threshold_Unpack(bits, idx))
        {
            printf("ReportConfigInterRAT::triggerType_event::eventId_eventB1:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string ReportConfigInterRAT::triggerType_event::eventId_eventB1::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "eventB1:\n";
    out += b1_Threshold_ToString(indent+1);
    return out;
}

std::string ReportConfigInterRAT::triggerType_event::eventId_eventB1::ToStringNoNewLines() const
{
    std::string out = "eventB1:";
    out += b1_Threshold_ToStringNoNewLines();
    return out;
}

int ReportConfigInterRAT::triggerType_event::eventId_eventB1::b1_Threshold_Pack(std::vector<uint8_t> &bits)
{
    if(!b1_Threshold_present)
    {
        printf("ReportConfigInterRAT::triggerType_event::eventId_eventB1::b1_Threshold_Pack() presence failure\n");
        return -1;
    }
    // Extension indicator

    // Choice
    for(uint32_t i=0; i<2; i++)
        bits.push_back((b1_Threshold_internal_choice >> (2-i-1)) & 1);

    // Fields
    if(b1_Threshold_internal_choice == k_b1_Threshold_b1_ThresholdUTRA)
    {
        if(0 != b1_Threshold_b1_ThresholdUTRA.Pack(bits))
        {
            printf("ReportConfigInterRAT::triggerType_event::eventId_eventB1::b1_Threshold_b1_ThresholdUTRA pack failure\n");
            return -1;
        }
    }
    if(b1_Threshold_internal_choice == k_b1_Threshold_b1_ThresholdGERAN)
    {
        if(0 != b1_Threshold_b1_ThresholdGERAN.Pack(bits))
        {
            printf("ReportConfigInterRAT::triggerType_event::eventId_eventB1::b1_Threshold_b1_ThresholdGERAN pack failure\n");
            return -1;
        }
    }
    if(b1_Threshold_internal_choice == k_b1_Threshold_b1_ThresholdCDMA2000)
    {
        if(0 != b1_Threshold_b1_ThresholdCDMA2000.Pack(bits))
        {
            printf("ReportConfigInterRAT::triggerType_event::eventId_eventB1::b1_Threshold_b1_ThresholdCDMA2000 pack failure\n");
            return -1;
        }
    }
    return 0;
}

int ReportConfigInterRAT::triggerType_event::eventId_eventB1::b1_Threshold_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return b1_Threshold_Unpack(bits, idx);
}

int ReportConfigInterRAT::triggerType_event::eventId_eventB1::b1_Threshold_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 2) > bits.size())
    {
        printf("ReportConfigInterRAT::triggerType_event::eventId_eventB1::b1_Threshold_Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<2; i++)
        packed_val |= bits[idx++] << (2-i-1);

    if((ReportConfigInterRAT::triggerType_event::eventId_eventB1::b1_Threshold_Enum)packed_val > k_b1_Threshold_b1_ThresholdCDMA2000)
    {
        printf("ReportConfigInterRAT::triggerType_event::eventId_eventB1::b1_Threshold_Unpack() choice range failure\n");
        return -1;
    }
    b1_Threshold_internal_choice = (ReportConfigInterRAT::triggerType_event::eventId_eventB1::b1_Threshold_Enum)packed_val;
    b1_Threshold_present = true;

    // Fields
    if(b1_Threshold_internal_choice == k_b1_Threshold_b1_ThresholdUTRA)
    {
        if(0 != b1_Threshold_b1_ThresholdUTRA.Unpack(bits, idx))
        {
            printf("ReportConfigInterRAT::triggerType_event::eventId_eventB1::b1_Threshold_b1_ThresholdUTRA unpack failure\n");
            return -1;
        }
    }
    if(b1_Threshold_internal_choice == k_b1_Threshold_b1_ThresholdGERAN)
    {
        if(0 != b1_Threshold_b1_ThresholdGERAN.Unpack(bits, idx))
        {
            printf("ReportConfigInterRAT::triggerType_event::eventId_eventB1::b1_Threshold_b1_ThresholdGERAN unpack failure\n");
            return -1;
        }
    }
    if(b1_Threshold_internal_choice == k_b1_Threshold_b1_ThresholdCDMA2000)
    {
        if(0 != b1_Threshold_b1_ThresholdCDMA2000.Unpack(bits, idx))
        {
            printf("ReportConfigInterRAT::triggerType_event::eventId_eventB1::b1_Threshold_b1_ThresholdCDMA2000 unpack failure\n");
            return -1;
        }
    }
    return 0;
}

ReportConfigInterRAT::triggerType_event::eventId_eventB1::b1_Threshold_Enum ReportConfigInterRAT::triggerType_event::eventId_eventB1::b1_Threshold_Choice() const
{
    if(b1_Threshold_present)
        return b1_Threshold_internal_choice;
    return (ReportConfigInterRAT::triggerType_event::eventId_eventB1::b1_Threshold_Enum)0;
}

int ReportConfigInterRAT::triggerType_event::eventId_eventB1::b1_Threshold_SetChoice(ReportConfigInterRAT::triggerType_event::eventId_eventB1::b1_Threshold_Enum choice)
{
    b1_Threshold_internal_choice = choice;
    b1_Threshold_present = true;
    return 0;
}

std::string ReportConfigInterRAT::triggerType_event::eventId_eventB1::b1_Threshold_ChoiceToString(b1_Threshold_Enum value) const
{
    if(k_b1_Threshold_b1_ThresholdUTRA == value)
        return "b1_Threshold_b1_ThresholdUTRA";
    if(k_b1_Threshold_b1_ThresholdGERAN == value)
        return "b1_Threshold_b1_ThresholdGERAN";
    if(k_b1_Threshold_b1_ThresholdCDMA2000 == value)
        return "b1_Threshold_b1_ThresholdCDMA2000";
    return "";
}

uint64_t ReportConfigInterRAT::triggerType_event::eventId_eventB1::b1_Threshold_NumberOfChoices() const
{
    return 3;
}

std::string ReportConfigInterRAT::triggerType_event::eventId_eventB1::b1_Threshold_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "b1_Threshold = " + b1_Threshold_ChoiceToString(b1_Threshold_internal_choice) + ":\n";
    if(b1_Threshold_internal_choice == k_b1_Threshold_b1_ThresholdUTRA)
        out += b1_Threshold_b1_ThresholdUTRA.ToString(indent+1);
    if(b1_Threshold_internal_choice == k_b1_Threshold_b1_ThresholdGERAN)
        out += b1_Threshold_b1_ThresholdGERAN.ToString(indent+1);
    if(b1_Threshold_internal_choice == k_b1_Threshold_b1_ThresholdCDMA2000)
        out += b1_Threshold_b1_ThresholdCDMA2000.ToString(indent+1);
    return out;
}

std::string ReportConfigInterRAT::triggerType_event::eventId_eventB1::b1_Threshold_ToStringNoNewLines() const
{
    std::string out = "b1_Threshold=" + b1_Threshold_ChoiceToString(b1_Threshold_internal_choice) + ",";
    if(b1_Threshold_internal_choice == k_b1_Threshold_b1_ThresholdUTRA)
        out += b1_Threshold_b1_ThresholdUTRA.ToStringNoNewLines();
    if(b1_Threshold_internal_choice == k_b1_Threshold_b1_ThresholdGERAN)
        out += b1_Threshold_b1_ThresholdGERAN.ToStringNoNewLines();
    if(b1_Threshold_internal_choice == k_b1_Threshold_b1_ThresholdCDMA2000)
        out += b1_Threshold_b1_ThresholdCDMA2000.ToStringNoNewLines();
    return out;
}

int ReportConfigInterRAT::triggerType_event::eventId_eventB1::b1_Threshold_Clear()
{
    b1_Threshold_present = false;
    return 0;
}

bool ReportConfigInterRAT::triggerType_event::eventId_eventB1::b1_Threshold_IsPresent() const
{
    return b1_Threshold_present;
}

ThresholdUTRA* ReportConfigInterRAT::triggerType_event::eventId_eventB1::b1_Threshold_b1_ThresholdUTRA_Set()
{
    b1_Threshold_b1_ThresholdUTRA_present = true;
    return &b1_Threshold_b1_ThresholdUTRA;
}

int ReportConfigInterRAT::triggerType_event::eventId_eventB1::b1_Threshold_b1_ThresholdUTRA_Set(ThresholdUTRA &value)
{
    b1_Threshold_b1_ThresholdUTRA_present = true;
    b1_Threshold_b1_ThresholdUTRA = value;
    return 0;
}

const ThresholdUTRA& ReportConfigInterRAT::triggerType_event::eventId_eventB1::b1_Threshold_b1_ThresholdUTRA_Get() const
{
    return b1_Threshold_b1_ThresholdUTRA;
}

std::string ReportConfigInterRAT::triggerType_event::eventId_eventB1::b1_Threshold_b1_ThresholdUTRA_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "b1_ThresholdUTRA:\n";
    out += b1_Threshold_b1_ThresholdUTRA.ToString(indent+1);
    return out;
}

std::string ReportConfigInterRAT::triggerType_event::eventId_eventB1::b1_Threshold_b1_ThresholdUTRA_ToStringNoNewLines() const
{
    std::string out = "b1_ThresholdUTRA:";
    out += b1_Threshold_b1_ThresholdUTRA.ToStringNoNewLines();
    return out;
}

int ReportConfigInterRAT::triggerType_event::eventId_eventB1::b1_Threshold_b1_ThresholdUTRA_Clear()
{
    b1_Threshold_b1_ThresholdUTRA_present = false;
    return 0;
}

bool ReportConfigInterRAT::triggerType_event::eventId_eventB1::b1_Threshold_b1_ThresholdUTRA_IsPresent() const
{
    return b1_Threshold_b1_ThresholdUTRA_present;
}

ThresholdGERAN* ReportConfigInterRAT::triggerType_event::eventId_eventB1::b1_Threshold_b1_ThresholdGERAN_Set()
{
    b1_Threshold_b1_ThresholdGERAN_present = true;
    return &b1_Threshold_b1_ThresholdGERAN;
}

int ReportConfigInterRAT::triggerType_event::eventId_eventB1::b1_Threshold_b1_ThresholdGERAN_Set(ThresholdGERAN &value)
{
    b1_Threshold_b1_ThresholdGERAN_present = true;
    b1_Threshold_b1_ThresholdGERAN = value;
    return 0;
}

const ThresholdGERAN& ReportConfigInterRAT::triggerType_event::eventId_eventB1::b1_Threshold_b1_ThresholdGERAN_Get() const
{
    return b1_Threshold_b1_ThresholdGERAN;
}

std::string ReportConfigInterRAT::triggerType_event::eventId_eventB1::b1_Threshold_b1_ThresholdGERAN_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "b1_ThresholdGERAN:\n";
    out += b1_Threshold_b1_ThresholdGERAN.ToString(indent+1);
    return out;
}

std::string ReportConfigInterRAT::triggerType_event::eventId_eventB1::b1_Threshold_b1_ThresholdGERAN_ToStringNoNewLines() const
{
    std::string out = "b1_ThresholdGERAN:";
    out += b1_Threshold_b1_ThresholdGERAN.ToStringNoNewLines();
    return out;
}

int ReportConfigInterRAT::triggerType_event::eventId_eventB1::b1_Threshold_b1_ThresholdGERAN_Clear()
{
    b1_Threshold_b1_ThresholdGERAN_present = false;
    return 0;
}

bool ReportConfigInterRAT::triggerType_event::eventId_eventB1::b1_Threshold_b1_ThresholdGERAN_IsPresent() const
{
    return b1_Threshold_b1_ThresholdGERAN_present;
}

ThresholdCDMA2000* ReportConfigInterRAT::triggerType_event::eventId_eventB1::b1_Threshold_b1_ThresholdCDMA2000_Set()
{
    b1_Threshold_b1_ThresholdCDMA2000_present = true;
    return &b1_Threshold_b1_ThresholdCDMA2000;
}

int ReportConfigInterRAT::triggerType_event::eventId_eventB1::b1_Threshold_b1_ThresholdCDMA2000_Set(ThresholdCDMA2000 &value)
{
    b1_Threshold_b1_ThresholdCDMA2000_present = true;
    b1_Threshold_b1_ThresholdCDMA2000 = value;
    return 0;
}

const ThresholdCDMA2000& ReportConfigInterRAT::triggerType_event::eventId_eventB1::b1_Threshold_b1_ThresholdCDMA2000_Get() const
{
    return b1_Threshold_b1_ThresholdCDMA2000;
}

std::string ReportConfigInterRAT::triggerType_event::eventId_eventB1::b1_Threshold_b1_ThresholdCDMA2000_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "b1_ThresholdCDMA2000:\n";
    out += b1_Threshold_b1_ThresholdCDMA2000.ToString(indent+1);
    return out;
}

std::string ReportConfigInterRAT::triggerType_event::eventId_eventB1::b1_Threshold_b1_ThresholdCDMA2000_ToStringNoNewLines() const
{
    std::string out = "b1_ThresholdCDMA2000:";
    out += b1_Threshold_b1_ThresholdCDMA2000.ToStringNoNewLines();
    return out;
}

int ReportConfigInterRAT::triggerType_event::eventId_eventB1::b1_Threshold_b1_ThresholdCDMA2000_Clear()
{
    b1_Threshold_b1_ThresholdCDMA2000_present = false;
    return 0;
}

bool ReportConfigInterRAT::triggerType_event::eventId_eventB1::b1_Threshold_b1_ThresholdCDMA2000_IsPresent() const
{
    return b1_Threshold_b1_ThresholdCDMA2000_present;
}

int ReportConfigInterRAT::triggerType_event::eventId_eventB2::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != b2_Threshold1.Pack(bits))
        {
            printf("ReportConfigInterRAT::triggerType_event::eventId_eventB2:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != b2_Threshold2_Pack(bits))
        {
            printf("ReportConfigInterRAT::triggerType_event::eventId_eventB2:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int ReportConfigInterRAT::triggerType_event::eventId_eventB2::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int ReportConfigInterRAT::triggerType_event::eventId_eventB2::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != b2_Threshold1.Unpack(bits, idx))
        {
            printf("ReportConfigInterRAT::triggerType_event::eventId_eventB2:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != b2_Threshold2_Unpack(bits, idx))
        {
            printf("ReportConfigInterRAT::triggerType_event::eventId_eventB2:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string ReportConfigInterRAT::triggerType_event::eventId_eventB2::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "eventB2:\n";
    out += b2_Threshold1_ToString(indent+1);
    out += b2_Threshold2_ToString(indent+1);
    return out;
}

std::string ReportConfigInterRAT::triggerType_event::eventId_eventB2::ToStringNoNewLines() const
{
    std::string out = "eventB2:";
    out += b2_Threshold1_ToStringNoNewLines();
    out += b2_Threshold2_ToStringNoNewLines();
    return out;
}

ThresholdEUTRA* ReportConfigInterRAT::triggerType_event::eventId_eventB2::b2_Threshold1_Set()
{
    b2_Threshold1_present = true;
    return &b2_Threshold1;
}

int ReportConfigInterRAT::triggerType_event::eventId_eventB2::b2_Threshold1_Set(ThresholdEUTRA &value)
{
    b2_Threshold1_present = true;
    b2_Threshold1 = value;
    return 0;
}

const ThresholdEUTRA& ReportConfigInterRAT::triggerType_event::eventId_eventB2::b2_Threshold1_Get() const
{
    return b2_Threshold1;
}

std::string ReportConfigInterRAT::triggerType_event::eventId_eventB2::b2_Threshold1_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "b2_Threshold1:\n";
    out += b2_Threshold1.ToString(indent+1);
    return out;
}

std::string ReportConfigInterRAT::triggerType_event::eventId_eventB2::b2_Threshold1_ToStringNoNewLines() const
{
    std::string out = "b2_Threshold1:";
    out += b2_Threshold1.ToStringNoNewLines();
    return out;
}

int ReportConfigInterRAT::triggerType_event::eventId_eventB2::b2_Threshold1_Clear()
{
    b2_Threshold1_present = false;
    return 0;
}

bool ReportConfigInterRAT::triggerType_event::eventId_eventB2::b2_Threshold1_IsPresent() const
{
    return b2_Threshold1_present;
}

int ReportConfigInterRAT::triggerType_event::eventId_eventB2::b2_Threshold2_Pack(std::vector<uint8_t> &bits)
{
    if(!b2_Threshold2_present)
    {
        printf("ReportConfigInterRAT::triggerType_event::eventId_eventB2::b2_Threshold2_Pack() presence failure\n");
        return -1;
    }
    // Extension indicator

    // Choice
    for(uint32_t i=0; i<2; i++)
        bits.push_back((b2_Threshold2_internal_choice >> (2-i-1)) & 1);

    // Fields
    if(b2_Threshold2_internal_choice == k_b2_Threshold2_b2_Threshold2UTRA)
    {
        if(0 != b2_Threshold2_b2_Threshold2UTRA.Pack(bits))
        {
            printf("ReportConfigInterRAT::triggerType_event::eventId_eventB2::b2_Threshold2_b2_Threshold2UTRA pack failure\n");
            return -1;
        }
    }
    if(b2_Threshold2_internal_choice == k_b2_Threshold2_b2_Threshold2GERAN)
    {
        if(0 != b2_Threshold2_b2_Threshold2GERAN.Pack(bits))
        {
            printf("ReportConfigInterRAT::triggerType_event::eventId_eventB2::b2_Threshold2_b2_Threshold2GERAN pack failure\n");
            return -1;
        }
    }
    if(b2_Threshold2_internal_choice == k_b2_Threshold2_b2_Threshold2CDMA2000)
    {
        if(0 != b2_Threshold2_b2_Threshold2CDMA2000.Pack(bits))
        {
            printf("ReportConfigInterRAT::triggerType_event::eventId_eventB2::b2_Threshold2_b2_Threshold2CDMA2000 pack failure\n");
            return -1;
        }
    }
    return 0;
}

int ReportConfigInterRAT::triggerType_event::eventId_eventB2::b2_Threshold2_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return b2_Threshold2_Unpack(bits, idx);
}

int ReportConfigInterRAT::triggerType_event::eventId_eventB2::b2_Threshold2_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 2) > bits.size())
    {
        printf("ReportConfigInterRAT::triggerType_event::eventId_eventB2::b2_Threshold2_Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<2; i++)
        packed_val |= bits[idx++] << (2-i-1);

    if((ReportConfigInterRAT::triggerType_event::eventId_eventB2::b2_Threshold2_Enum)packed_val > k_b2_Threshold2_b2_Threshold2CDMA2000)
    {
        printf("ReportConfigInterRAT::triggerType_event::eventId_eventB2::b2_Threshold2_Unpack() choice range failure\n");
        return -1;
    }
    b2_Threshold2_internal_choice = (ReportConfigInterRAT::triggerType_event::eventId_eventB2::b2_Threshold2_Enum)packed_val;
    b2_Threshold2_present = true;

    // Fields
    if(b2_Threshold2_internal_choice == k_b2_Threshold2_b2_Threshold2UTRA)
    {
        if(0 != b2_Threshold2_b2_Threshold2UTRA.Unpack(bits, idx))
        {
            printf("ReportConfigInterRAT::triggerType_event::eventId_eventB2::b2_Threshold2_b2_Threshold2UTRA unpack failure\n");
            return -1;
        }
    }
    if(b2_Threshold2_internal_choice == k_b2_Threshold2_b2_Threshold2GERAN)
    {
        if(0 != b2_Threshold2_b2_Threshold2GERAN.Unpack(bits, idx))
        {
            printf("ReportConfigInterRAT::triggerType_event::eventId_eventB2::b2_Threshold2_b2_Threshold2GERAN unpack failure\n");
            return -1;
        }
    }
    if(b2_Threshold2_internal_choice == k_b2_Threshold2_b2_Threshold2CDMA2000)
    {
        if(0 != b2_Threshold2_b2_Threshold2CDMA2000.Unpack(bits, idx))
        {
            printf("ReportConfigInterRAT::triggerType_event::eventId_eventB2::b2_Threshold2_b2_Threshold2CDMA2000 unpack failure\n");
            return -1;
        }
    }
    return 0;
}

ReportConfigInterRAT::triggerType_event::eventId_eventB2::b2_Threshold2_Enum ReportConfigInterRAT::triggerType_event::eventId_eventB2::b2_Threshold2_Choice() const
{
    if(b2_Threshold2_present)
        return b2_Threshold2_internal_choice;
    return (ReportConfigInterRAT::triggerType_event::eventId_eventB2::b2_Threshold2_Enum)0;
}

int ReportConfigInterRAT::triggerType_event::eventId_eventB2::b2_Threshold2_SetChoice(ReportConfigInterRAT::triggerType_event::eventId_eventB2::b2_Threshold2_Enum choice)
{
    b2_Threshold2_internal_choice = choice;
    b2_Threshold2_present = true;
    return 0;
}

std::string ReportConfigInterRAT::triggerType_event::eventId_eventB2::b2_Threshold2_ChoiceToString(b2_Threshold2_Enum value) const
{
    if(k_b2_Threshold2_b2_Threshold2UTRA == value)
        return "b2_Threshold2_b2_Threshold2UTRA";
    if(k_b2_Threshold2_b2_Threshold2GERAN == value)
        return "b2_Threshold2_b2_Threshold2GERAN";
    if(k_b2_Threshold2_b2_Threshold2CDMA2000 == value)
        return "b2_Threshold2_b2_Threshold2CDMA2000";
    return "";
}

uint64_t ReportConfigInterRAT::triggerType_event::eventId_eventB2::b2_Threshold2_NumberOfChoices() const
{
    return 3;
}

std::string ReportConfigInterRAT::triggerType_event::eventId_eventB2::b2_Threshold2_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "b2_Threshold2 = " + b2_Threshold2_ChoiceToString(b2_Threshold2_internal_choice) + ":\n";
    if(b2_Threshold2_internal_choice == k_b2_Threshold2_b2_Threshold2UTRA)
        out += b2_Threshold2_b2_Threshold2UTRA.ToString(indent+1);
    if(b2_Threshold2_internal_choice == k_b2_Threshold2_b2_Threshold2GERAN)
        out += b2_Threshold2_b2_Threshold2GERAN.ToString(indent+1);
    if(b2_Threshold2_internal_choice == k_b2_Threshold2_b2_Threshold2CDMA2000)
        out += b2_Threshold2_b2_Threshold2CDMA2000.ToString(indent+1);
    return out;
}

std::string ReportConfigInterRAT::triggerType_event::eventId_eventB2::b2_Threshold2_ToStringNoNewLines() const
{
    std::string out = "b2_Threshold2=" + b2_Threshold2_ChoiceToString(b2_Threshold2_internal_choice) + ",";
    if(b2_Threshold2_internal_choice == k_b2_Threshold2_b2_Threshold2UTRA)
        out += b2_Threshold2_b2_Threshold2UTRA.ToStringNoNewLines();
    if(b2_Threshold2_internal_choice == k_b2_Threshold2_b2_Threshold2GERAN)
        out += b2_Threshold2_b2_Threshold2GERAN.ToStringNoNewLines();
    if(b2_Threshold2_internal_choice == k_b2_Threshold2_b2_Threshold2CDMA2000)
        out += b2_Threshold2_b2_Threshold2CDMA2000.ToStringNoNewLines();
    return out;
}

int ReportConfigInterRAT::triggerType_event::eventId_eventB2::b2_Threshold2_Clear()
{
    b2_Threshold2_present = false;
    return 0;
}

bool ReportConfigInterRAT::triggerType_event::eventId_eventB2::b2_Threshold2_IsPresent() const
{
    return b2_Threshold2_present;
}

ThresholdUTRA* ReportConfigInterRAT::triggerType_event::eventId_eventB2::b2_Threshold2_b2_Threshold2UTRA_Set()
{
    b2_Threshold2_b2_Threshold2UTRA_present = true;
    return &b2_Threshold2_b2_Threshold2UTRA;
}

int ReportConfigInterRAT::triggerType_event::eventId_eventB2::b2_Threshold2_b2_Threshold2UTRA_Set(ThresholdUTRA &value)
{
    b2_Threshold2_b2_Threshold2UTRA_present = true;
    b2_Threshold2_b2_Threshold2UTRA = value;
    return 0;
}

const ThresholdUTRA& ReportConfigInterRAT::triggerType_event::eventId_eventB2::b2_Threshold2_b2_Threshold2UTRA_Get() const
{
    return b2_Threshold2_b2_Threshold2UTRA;
}

std::string ReportConfigInterRAT::triggerType_event::eventId_eventB2::b2_Threshold2_b2_Threshold2UTRA_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "b2_Threshold2UTRA:\n";
    out += b2_Threshold2_b2_Threshold2UTRA.ToString(indent+1);
    return out;
}

std::string ReportConfigInterRAT::triggerType_event::eventId_eventB2::b2_Threshold2_b2_Threshold2UTRA_ToStringNoNewLines() const
{
    std::string out = "b2_Threshold2UTRA:";
    out += b2_Threshold2_b2_Threshold2UTRA.ToStringNoNewLines();
    return out;
}

int ReportConfigInterRAT::triggerType_event::eventId_eventB2::b2_Threshold2_b2_Threshold2UTRA_Clear()
{
    b2_Threshold2_b2_Threshold2UTRA_present = false;
    return 0;
}

bool ReportConfigInterRAT::triggerType_event::eventId_eventB2::b2_Threshold2_b2_Threshold2UTRA_IsPresent() const
{
    return b2_Threshold2_b2_Threshold2UTRA_present;
}

ThresholdGERAN* ReportConfigInterRAT::triggerType_event::eventId_eventB2::b2_Threshold2_b2_Threshold2GERAN_Set()
{
    b2_Threshold2_b2_Threshold2GERAN_present = true;
    return &b2_Threshold2_b2_Threshold2GERAN;
}

int ReportConfigInterRAT::triggerType_event::eventId_eventB2::b2_Threshold2_b2_Threshold2GERAN_Set(ThresholdGERAN &value)
{
    b2_Threshold2_b2_Threshold2GERAN_present = true;
    b2_Threshold2_b2_Threshold2GERAN = value;
    return 0;
}

const ThresholdGERAN& ReportConfigInterRAT::triggerType_event::eventId_eventB2::b2_Threshold2_b2_Threshold2GERAN_Get() const
{
    return b2_Threshold2_b2_Threshold2GERAN;
}

std::string ReportConfigInterRAT::triggerType_event::eventId_eventB2::b2_Threshold2_b2_Threshold2GERAN_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "b2_Threshold2GERAN:\n";
    out += b2_Threshold2_b2_Threshold2GERAN.ToString(indent+1);
    return out;
}

std::string ReportConfigInterRAT::triggerType_event::eventId_eventB2::b2_Threshold2_b2_Threshold2GERAN_ToStringNoNewLines() const
{
    std::string out = "b2_Threshold2GERAN:";
    out += b2_Threshold2_b2_Threshold2GERAN.ToStringNoNewLines();
    return out;
}

int ReportConfigInterRAT::triggerType_event::eventId_eventB2::b2_Threshold2_b2_Threshold2GERAN_Clear()
{
    b2_Threshold2_b2_Threshold2GERAN_present = false;
    return 0;
}

bool ReportConfigInterRAT::triggerType_event::eventId_eventB2::b2_Threshold2_b2_Threshold2GERAN_IsPresent() const
{
    return b2_Threshold2_b2_Threshold2GERAN_present;
}

ThresholdCDMA2000* ReportConfigInterRAT::triggerType_event::eventId_eventB2::b2_Threshold2_b2_Threshold2CDMA2000_Set()
{
    b2_Threshold2_b2_Threshold2CDMA2000_present = true;
    return &b2_Threshold2_b2_Threshold2CDMA2000;
}

int ReportConfigInterRAT::triggerType_event::eventId_eventB2::b2_Threshold2_b2_Threshold2CDMA2000_Set(ThresholdCDMA2000 &value)
{
    b2_Threshold2_b2_Threshold2CDMA2000_present = true;
    b2_Threshold2_b2_Threshold2CDMA2000 = value;
    return 0;
}

const ThresholdCDMA2000& ReportConfigInterRAT::triggerType_event::eventId_eventB2::b2_Threshold2_b2_Threshold2CDMA2000_Get() const
{
    return b2_Threshold2_b2_Threshold2CDMA2000;
}

std::string ReportConfigInterRAT::triggerType_event::eventId_eventB2::b2_Threshold2_b2_Threshold2CDMA2000_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "b2_Threshold2CDMA2000:\n";
    out += b2_Threshold2_b2_Threshold2CDMA2000.ToString(indent+1);
    return out;
}

std::string ReportConfigInterRAT::triggerType_event::eventId_eventB2::b2_Threshold2_b2_Threshold2CDMA2000_ToStringNoNewLines() const
{
    std::string out = "b2_Threshold2CDMA2000:";
    out += b2_Threshold2_b2_Threshold2CDMA2000.ToStringNoNewLines();
    return out;
}

int ReportConfigInterRAT::triggerType_event::eventId_eventB2::b2_Threshold2_b2_Threshold2CDMA2000_Clear()
{
    b2_Threshold2_b2_Threshold2CDMA2000_present = false;
    return 0;
}

bool ReportConfigInterRAT::triggerType_event::eventId_eventB2::b2_Threshold2_b2_Threshold2CDMA2000_IsPresent() const
{
    return b2_Threshold2_b2_Threshold2CDMA2000_present;
}

Hysteresis* ReportConfigInterRAT::triggerType_event::hysteresis_Set()
{
    hysteresis_present = true;
    return &hysteresis;
}

int ReportConfigInterRAT::triggerType_event::hysteresis_Set(Hysteresis &value)
{
    hysteresis_present = true;
    hysteresis = value;
    return 0;
}

const Hysteresis& ReportConfigInterRAT::triggerType_event::hysteresis_Get() const
{
    return hysteresis;
}

std::string ReportConfigInterRAT::triggerType_event::hysteresis_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "hysteresis:\n";
    out += hysteresis.ToString(indent+1);
    return out;
}

std::string ReportConfigInterRAT::triggerType_event::hysteresis_ToStringNoNewLines() const
{
    std::string out = "hysteresis:";
    out += hysteresis.ToStringNoNewLines();
    return out;
}

int ReportConfigInterRAT::triggerType_event::hysteresis_Clear()
{
    hysteresis_present = false;
    return 0;
}

bool ReportConfigInterRAT::triggerType_event::hysteresis_IsPresent() const
{
    return hysteresis_present;
}

TimeToTrigger* ReportConfigInterRAT::triggerType_event::timeToTrigger_Set()
{
    timeToTrigger_present = true;
    return &timeToTrigger;
}

int ReportConfigInterRAT::triggerType_event::timeToTrigger_Set(TimeToTrigger &value)
{
    timeToTrigger_present = true;
    timeToTrigger = value;
    return 0;
}

const TimeToTrigger& ReportConfigInterRAT::triggerType_event::timeToTrigger_Get() const
{
    return timeToTrigger;
}

std::string ReportConfigInterRAT::triggerType_event::timeToTrigger_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "timeToTrigger:\n";
    out += timeToTrigger.ToString(indent+1);
    return out;
}

std::string ReportConfigInterRAT::triggerType_event::timeToTrigger_ToStringNoNewLines() const
{
    std::string out = "timeToTrigger:";
    out += timeToTrigger.ToStringNoNewLines();
    return out;
}

int ReportConfigInterRAT::triggerType_event::timeToTrigger_Clear()
{
    timeToTrigger_present = false;
    return 0;
}

bool ReportConfigInterRAT::triggerType_event::timeToTrigger_IsPresent() const
{
    return timeToTrigger_present;
}

int ReportConfigInterRAT::triggerType_periodical::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != purpose_Pack(bits))
        {
            printf("ReportConfigInterRAT::triggerType_periodical:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int ReportConfigInterRAT::triggerType_periodical::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int ReportConfigInterRAT::triggerType_periodical::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != purpose_Unpack(bits, idx))
        {
            printf("ReportConfigInterRAT::triggerType_periodical:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string ReportConfigInterRAT::triggerType_periodical::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "periodical:\n";
    out += purpose_ToString(indent+1);
    return out;
}

std::string ReportConfigInterRAT::triggerType_periodical::ToStringNoNewLines() const
{
    std::string out = "periodical:";
    out += purpose_ToStringNoNewLines();
    return out;
}

int ReportConfigInterRAT::triggerType_periodical::purpose_Pack(std::vector<uint8_t> &bits)
{
    if(!purpose_present)
    {
        printf("ReportConfigInterRAT::triggerType_periodical::purpose_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 2;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((purpose_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int ReportConfigInterRAT::triggerType_periodical::purpose_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return purpose_Unpack(bits, idx);
}

int ReportConfigInterRAT::triggerType_periodical::purpose_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 2;
    if((idx + N_bits) > bits.size())
    {
        printf("ReportConfigInterRAT::triggerType_periodical::purpose_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 2)
    {
        printf("ReportConfigInterRAT::triggerType_periodical::purpose_Unpack() max failure\n");
        return -1;
    }
    purpose_internal_value = (purpose_Enum)packed_val;
    purpose_present = true;
    return 0;
}

ReportConfigInterRAT::triggerType_periodical::purpose_Enum ReportConfigInterRAT::triggerType_periodical::purpose_Value() const
{
    if(purpose_present)
        return purpose_internal_value;
    return (ReportConfigInterRAT::triggerType_periodical::purpose_Enum)0;
}

int ReportConfigInterRAT::triggerType_periodical::purpose_SetValue(purpose_Enum value)
{
    purpose_internal_value = value;
    purpose_present = true;
    return 0;
}

int ReportConfigInterRAT::triggerType_periodical::purpose_SetValue(std::string value)
{
    if("reportStrongestCells" == value)
    {
        purpose_internal_value = k_purpose_reportStrongestCells;
        purpose_present = true;
        return 0;
    }
    if("reportStrongestCellsForSON" == value)
    {
        purpose_internal_value = k_purpose_reportStrongestCellsForSON;
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

std::string ReportConfigInterRAT::triggerType_periodical::purpose_ValueToString(purpose_Enum value) const
{
    if(k_purpose_reportStrongestCells == value)
        return "reportStrongestCells";
    if(k_purpose_reportStrongestCellsForSON == value)
        return "reportStrongestCellsForSON";
    if(k_purpose_reportCGI == value)
        return "reportCGI";
    return "";
}

uint64_t ReportConfigInterRAT::triggerType_periodical::purpose_NumberOfValues() const
{
    return 3;
}

std::string ReportConfigInterRAT::triggerType_periodical::purpose_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "purpose = " + purpose_ValueToString(purpose_internal_value) + "\n";
    return out;
}

std::string ReportConfigInterRAT::triggerType_periodical::purpose_ToStringNoNewLines() const
{
    std::string out = "purpose=" + purpose_ValueToString(purpose_internal_value) + ",";
    return out;
}

int ReportConfigInterRAT::triggerType_periodical::purpose_Clear()
{
    purpose_present = false;
    return 0;
}

bool ReportConfigInterRAT::triggerType_periodical::purpose_IsPresent() const
{
    return purpose_present;
}

#include "maxCellReport.h"

int ReportConfigInterRAT::maxReportCells_Pack(std::vector<uint8_t> &bits)
{
    if(!maxReportCells_present)
    {
        printf("ReportConfigInterRAT::maxReportCells_Pack() presence failure\n");
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

int ReportConfigInterRAT::maxReportCells_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return maxReportCells_Unpack(bits, idx);
}

int ReportConfigInterRAT::maxReportCells_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (maxCellReport - 1))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("ReportConfigInterRAT::maxReportCells_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    maxReportCells_internal_value = packed_val + 1;
    maxReportCells_present = true;
    return 0;
}

int64_t ReportConfigInterRAT::maxReportCells_Value() const
{
    if(maxReportCells_present)
        return maxReportCells_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int ReportConfigInterRAT::maxReportCells_SetValue(int64_t value)
{
    if(value < 1 || value > maxCellReport)
    {
        printf("ReportConfigInterRAT::maxReportCells_SetValue() range failure\n");
        return -1;
    }
    maxReportCells_internal_value = value;
    maxReportCells_present = true;
    return 0;
}

std::string ReportConfigInterRAT::maxReportCells_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "maxReportCells = " + std::to_string(maxReportCells_internal_value) + "\n";
    return out;
}

std::string ReportConfigInterRAT::maxReportCells_ToStringNoNewLines() const
{
    std::string out = "maxReportCells=" + std::to_string(maxReportCells_internal_value) + ",";
    return out;
}

int ReportConfigInterRAT::maxReportCells_Clear()
{
    maxReportCells_present = false;
    return 0;
}

bool ReportConfigInterRAT::maxReportCells_IsPresent() const
{
    return maxReportCells_present;
}

ReportInterval* ReportConfigInterRAT::reportInterval_Set()
{
    reportInterval_present = true;
    return &reportInterval;
}

int ReportConfigInterRAT::reportInterval_Set(ReportInterval &value)
{
    reportInterval_present = true;
    reportInterval = value;
    return 0;
}

const ReportInterval& ReportConfigInterRAT::reportInterval_Get() const
{
    return reportInterval;
}

std::string ReportConfigInterRAT::reportInterval_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "reportInterval:\n";
    out += reportInterval.ToString(indent+1);
    return out;
}

std::string ReportConfigInterRAT::reportInterval_ToStringNoNewLines() const
{
    std::string out = "reportInterval:";
    out += reportInterval.ToStringNoNewLines();
    return out;
}

int ReportConfigInterRAT::reportInterval_Clear()
{
    reportInterval_present = false;
    return 0;
}

bool ReportConfigInterRAT::reportInterval_IsPresent() const
{
    return reportInterval_present;
}

int ReportConfigInterRAT::reportAmount_Pack(std::vector<uint8_t> &bits)
{
    if(!reportAmount_present)
    {
        printf("ReportConfigInterRAT::reportAmount_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 3;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((reportAmount_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int ReportConfigInterRAT::reportAmount_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return reportAmount_Unpack(bits, idx);
}

int ReportConfigInterRAT::reportAmount_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 3;
    if((idx + N_bits) > bits.size())
    {
        printf("ReportConfigInterRAT::reportAmount_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 7)
    {
        printf("ReportConfigInterRAT::reportAmount_Unpack() max failure\n");
        return -1;
    }
    reportAmount_internal_value = (reportAmount_Enum)packed_val;
    reportAmount_present = true;
    return 0;
}

ReportConfigInterRAT::reportAmount_Enum ReportConfigInterRAT::reportAmount_Value() const
{
    if(reportAmount_present)
        return reportAmount_internal_value;
    return (ReportConfigInterRAT::reportAmount_Enum)0;
}

int ReportConfigInterRAT::reportAmount_SetValue(reportAmount_Enum value)
{
    reportAmount_internal_value = value;
    reportAmount_present = true;
    return 0;
}

int ReportConfigInterRAT::reportAmount_SetValue(std::string value)
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

std::string ReportConfigInterRAT::reportAmount_ValueToString(reportAmount_Enum value) const
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

uint64_t ReportConfigInterRAT::reportAmount_NumberOfValues() const
{
    return 8;
}

std::string ReportConfigInterRAT::reportAmount_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "reportAmount = " + reportAmount_ValueToString(reportAmount_internal_value) + "\n";
    return out;
}

std::string ReportConfigInterRAT::reportAmount_ToStringNoNewLines() const
{
    std::string out = "reportAmount=" + reportAmount_ValueToString(reportAmount_internal_value) + ",";
    return out;
}

int ReportConfigInterRAT::reportAmount_Clear()
{
    reportAmount_present = false;
    return 0;
}

bool ReportConfigInterRAT::reportAmount_IsPresent() const
{
    return reportAmount_present;
}

int ReportConfigInterRAT::si_RequestForHO_r9_Pack(std::vector<uint8_t> &bits)
{
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((si_RequestForHO_r9_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int ReportConfigInterRAT::si_RequestForHO_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return si_RequestForHO_r9_Unpack(bits, idx);
}

int ReportConfigInterRAT::si_RequestForHO_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("ReportConfigInterRAT::si_RequestForHO_r9_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 0)
    {
        printf("ReportConfigInterRAT::si_RequestForHO_r9_Unpack() max failure\n");
        return -1;
    }
    si_RequestForHO_r9_internal_value = (si_RequestForHO_r9_Enum)packed_val;
    si_RequestForHO_r9_present = true;
    return 0;
}

ReportConfigInterRAT::si_RequestForHO_r9_Enum ReportConfigInterRAT::si_RequestForHO_r9_Value() const
{
    if(si_RequestForHO_r9_present)
        return si_RequestForHO_r9_internal_value;
    return (ReportConfigInterRAT::si_RequestForHO_r9_Enum)0;
}

int ReportConfigInterRAT::si_RequestForHO_r9_SetValue(si_RequestForHO_r9_Enum value)
{
    si_RequestForHO_r9_internal_value = value;
    si_RequestForHO_r9_present = true;
    return 0;
}

int ReportConfigInterRAT::si_RequestForHO_r9_SetValue(std::string value)
{
    if("setup" == value)
    {
        si_RequestForHO_r9_internal_value = k_si_RequestForHO_r9_setup;
        si_RequestForHO_r9_present = true;
        return 0;
    }
    return 1;
}

std::string ReportConfigInterRAT::si_RequestForHO_r9_ValueToString(si_RequestForHO_r9_Enum value) const
{
    if(k_si_RequestForHO_r9_setup == value)
        return "setup";
    return "";
}

uint64_t ReportConfigInterRAT::si_RequestForHO_r9_NumberOfValues() const
{
    return 1;
}

std::string ReportConfigInterRAT::si_RequestForHO_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "si_RequestForHO_r9 = " + si_RequestForHO_r9_ValueToString(si_RequestForHO_r9_internal_value) + "\n";
    return out;
}

std::string ReportConfigInterRAT::si_RequestForHO_r9_ToStringNoNewLines() const
{
    std::string out = "si_RequestForHO_r9=" + si_RequestForHO_r9_ValueToString(si_RequestForHO_r9_internal_value) + ",";
    return out;
}

int ReportConfigInterRAT::si_RequestForHO_r9_Clear()
{
    si_RequestForHO_r9_present = false;
    return 0;
}

bool ReportConfigInterRAT::si_RequestForHO_r9_IsPresent() const
{
    return si_RequestForHO_r9_present;
}

int ReportConfigInterRAT::reportQuantityUTRA_FDD_r10_Pack(std::vector<uint8_t> &bits)
{
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((reportQuantityUTRA_FDD_r10_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int ReportConfigInterRAT::reportQuantityUTRA_FDD_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return reportQuantityUTRA_FDD_r10_Unpack(bits, idx);
}

int ReportConfigInterRAT::reportQuantityUTRA_FDD_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("ReportConfigInterRAT::reportQuantityUTRA_FDD_r10_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 0)
    {
        printf("ReportConfigInterRAT::reportQuantityUTRA_FDD_r10_Unpack() max failure\n");
        return -1;
    }
    reportQuantityUTRA_FDD_r10_internal_value = (reportQuantityUTRA_FDD_r10_Enum)packed_val;
    reportQuantityUTRA_FDD_r10_present = true;
    return 0;
}

ReportConfigInterRAT::reportQuantityUTRA_FDD_r10_Enum ReportConfigInterRAT::reportQuantityUTRA_FDD_r10_Value() const
{
    if(reportQuantityUTRA_FDD_r10_present)
        return reportQuantityUTRA_FDD_r10_internal_value;
    return (ReportConfigInterRAT::reportQuantityUTRA_FDD_r10_Enum)0;
}

int ReportConfigInterRAT::reportQuantityUTRA_FDD_r10_SetValue(reportQuantityUTRA_FDD_r10_Enum value)
{
    reportQuantityUTRA_FDD_r10_internal_value = value;
    reportQuantityUTRA_FDD_r10_present = true;
    return 0;
}

int ReportConfigInterRAT::reportQuantityUTRA_FDD_r10_SetValue(std::string value)
{
    if("both" == value)
    {
        reportQuantityUTRA_FDD_r10_internal_value = k_reportQuantityUTRA_FDD_r10_both;
        reportQuantityUTRA_FDD_r10_present = true;
        return 0;
    }
    return 1;
}

std::string ReportConfigInterRAT::reportQuantityUTRA_FDD_r10_ValueToString(reportQuantityUTRA_FDD_r10_Enum value) const
{
    if(k_reportQuantityUTRA_FDD_r10_both == value)
        return "both";
    return "";
}

uint64_t ReportConfigInterRAT::reportQuantityUTRA_FDD_r10_NumberOfValues() const
{
    return 1;
}

std::string ReportConfigInterRAT::reportQuantityUTRA_FDD_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "reportQuantityUTRA_FDD_r10 = " + reportQuantityUTRA_FDD_r10_ValueToString(reportQuantityUTRA_FDD_r10_internal_value) + "\n";
    return out;
}

std::string ReportConfigInterRAT::reportQuantityUTRA_FDD_r10_ToStringNoNewLines() const
{
    std::string out = "reportQuantityUTRA_FDD_r10=" + reportQuantityUTRA_FDD_r10_ValueToString(reportQuantityUTRA_FDD_r10_internal_value) + ",";
    return out;
}

int ReportConfigInterRAT::reportQuantityUTRA_FDD_r10_Clear()
{
    reportQuantityUTRA_FDD_r10_present = false;
    return 0;
}

bool ReportConfigInterRAT::reportQuantityUTRA_FDD_r10_IsPresent() const
{
    return reportQuantityUTRA_FDD_r10_present;
}

