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

#include "MeasResults.h"

#include <cmath>

int MeasResults::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator
    bool has_extension = false;
    if(measResultForECID_r9_IsPresent() || locationInfo_r10_IsPresent() || measResultServFreqList_r10_IsPresent())
    {
        bits.push_back(1);
        has_extension = true;
    }else{
        bits.push_back(0);
    }

    // Optional indicators
    bits.push_back(measResultNeighCells_IsPresent());

    // Fields
    {
        if(0 != measId.Pack(bits))
        {
            printf("MeasResults:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != measResultPCell_value.Pack(bits))
        {
            printf("MeasResults:: field pack failure\n");
            return -1;
        }
    }
    if(measResultNeighCells_IsPresent())
    {
        if(0 != measResultNeighCells_Pack(bits))
        {
            printf("MeasResults:: field pack failure\n");
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
            printf("MeasResults:: Extension list size too large failure\n");
            return -1;
        }

        // Extension field presence indicators
        bits.push_back(measResultForECID_r9_IsPresent());
        bits.push_back(locationInfo_r10_IsPresent());
        bits.push_back(measResultServFreqList_r10_IsPresent());

        // Extension fields
        if(measResultForECID_r9_IsPresent())
        {
            std::vector<uint8_t> field_bits;
            if(0 != measResultForECID_r9.Pack(field_bits))
            {
                printf("MeasResults:: field pack failure\n");
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
        if(locationInfo_r10_IsPresent())
        {
            std::vector<uint8_t> field_bits;
            if(0 != locationInfo_r10.Pack(field_bits))
            {
                printf("MeasResults:: field pack failure\n");
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
        if(measResultServFreqList_r10_IsPresent())
        {
            std::vector<uint8_t> field_bits;
            if(0 != measResultServFreqList_r10.Pack(field_bits))
            {
                printf("MeasResults:: field pack failure\n");
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

int MeasResults::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int MeasResults::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("MeasResults::Unpack() index out of bounds for extension\n");
        return -1;
    }
    bool has_extension = bits[idx++];

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("MeasResults::Unpack() index out of bounds for optional indiator measResultNeighCells\n");
        return -1;
    }
    measResultNeighCells_present = bits[idx++];

    // Fields
    {
        if(0 != measId.Unpack(bits, idx))
        {
            printf("MeasResults:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != measResultPCell_value.Unpack(bits, idx))
        {
            printf("MeasResults:: field unpack failure\n");
            return -1;
        }
    }
    if(measResultNeighCells_present)
    {
        if(0 != measResultNeighCells_Unpack(bits, idx))
        {
            printf("MeasResults:: field unpack failure\n");
            return -1;
        }
    }

    // Extension
    if(has_extension)
    {
        if((idx + 7) > bits.size())
        {
            printf("MeasResults::Unpack() index out of bounds for extension size\n");
            return -1;
        }
        // Number of extension fields
        if(bits[idx++] != 0)
        {
            printf("MeasResults:: Extension list size too large failure\n");
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
                printf("MeasResults::Unpack() index out of bounds for optional indiator measResultForECID_r9\n");
                return -1;
            }
            measResultForECID_r9_present = bits[idx++];
        }
        if(opt_ind_count++ < N_ext_fields)
        {
            if((idx + 1) > bits.size())
            {
                printf("MeasResults::Unpack() index out of bounds for optional indiator locationInfo_r10\n");
                return -1;
            }
            locationInfo_r10_present = bits[idx++];
        }
        if(opt_ind_count++ < N_ext_fields)
        {
            if((idx + 1) > bits.size())
            {
                printf("MeasResults::Unpack() index out of bounds for optional indiator measResultServFreqList_r10\n");
                return -1;
            }
            measResultServFreqList_r10_present = bits[idx++];
        }
        if((idx + (N_ext_fields - opt_ind_count)) > bits.size())
        {
            printf("MeasResults::Unpack() index out of bounds for extension optional indicators\n");
            return -1;
        }
        idx += (N_ext_fields - opt_ind_count);

        // Extension fields
        if(measResultForECID_r9_present)
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
            if(0 != measResultForECID_r9.Unpack(bits, idx))
            {
                printf("MeasResults:: field unpack failure\n");
                return -1;
            }
            idx = orig_idx + (N_octets * 8);
        }
        if(locationInfo_r10_present)
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
            if(0 != locationInfo_r10.Unpack(bits, idx))
            {
                printf("MeasResults:: field unpack failure\n");
                return -1;
            }
            idx = orig_idx + (N_octets * 8);
        }
        if(measResultServFreqList_r10_present)
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
            if(0 != measResultServFreqList_r10.Unpack(bits, idx))
            {
                printf("MeasResults:: field unpack failure\n");
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
            printf("MeasResults::Unpack() index out of bounds for extension fields\n");
            return -1;
        }
            idx += N_octets * 8;
        }
    }
    return 0;
}

std::string MeasResults::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "MeasResults:\n";
    out += measId_ToString(indent+1);
    out += measResultPCell_value.ToString(indent+1);
    if(measResultNeighCells_IsPresent())
        out += measResultNeighCells_ToString(indent+1);
    if(measResultForECID_r9_IsPresent())
        out += measResultForECID_r9_ToString(indent+1);
    if(locationInfo_r10_IsPresent())
        out += locationInfo_r10_ToString(indent+1);
    if(measResultServFreqList_r10_IsPresent())
        out += measResultServFreqList_r10_ToString(indent+1);
    return out;
}

std::string MeasResults::ToStringNoNewLines() const
{
    std::string out = "MeasResults:";
    out += measId_ToStringNoNewLines();
    out += measResultPCell_value.ToStringNoNewLines();
    if(measResultNeighCells_IsPresent())
        out += measResultNeighCells_ToStringNoNewLines();
    if(measResultForECID_r9_IsPresent())
        out += measResultForECID_r9_ToStringNoNewLines();
    if(locationInfo_r10_IsPresent())
        out += locationInfo_r10_ToStringNoNewLines();
    if(measResultServFreqList_r10_IsPresent())
        out += measResultServFreqList_r10_ToStringNoNewLines();
    return out;
}

MeasId* MeasResults::measId_Set()
{
    measId_present = true;
    return &measId;
}

int MeasResults::measId_Set(MeasId &value)
{
    measId_present = true;
    measId = value;
    return 0;
}

const MeasId& MeasResults::measId_Get() const
{
    return measId;
}

std::string MeasResults::measId_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "measId:\n";
    out += measId.ToString(indent+1);
    return out;
}

std::string MeasResults::measId_ToStringNoNewLines() const
{
    std::string out = "measId:";
    out += measId.ToStringNoNewLines();
    return out;
}

int MeasResults::measId_Clear()
{
    measId_present = false;
    return 0;
}

bool MeasResults::measId_IsPresent() const
{
    return measId_present;
}

int MeasResults::measResultPCell::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != rsrpResult.Pack(bits))
        {
            printf("MeasResults::measResultPCell:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != rsrqResult.Pack(bits))
        {
            printf("MeasResults::measResultPCell:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int MeasResults::measResultPCell::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int MeasResults::measResultPCell::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != rsrpResult.Unpack(bits, idx))
        {
            printf("MeasResults::measResultPCell:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != rsrqResult.Unpack(bits, idx))
        {
            printf("MeasResults::measResultPCell:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string MeasResults::measResultPCell::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "measResultPCell:\n";
    out += rsrpResult_ToString(indent+1);
    out += rsrqResult_ToString(indent+1);
    return out;
}

std::string MeasResults::measResultPCell::ToStringNoNewLines() const
{
    std::string out = "measResultPCell:";
    out += rsrpResult_ToStringNoNewLines();
    out += rsrqResult_ToStringNoNewLines();
    return out;
}

RSRP_Range* MeasResults::measResultPCell::rsrpResult_Set()
{
    rsrpResult_present = true;
    return &rsrpResult;
}

int MeasResults::measResultPCell::rsrpResult_Set(RSRP_Range &value)
{
    rsrpResult_present = true;
    rsrpResult = value;
    return 0;
}

const RSRP_Range& MeasResults::measResultPCell::rsrpResult_Get() const
{
    return rsrpResult;
}

std::string MeasResults::measResultPCell::rsrpResult_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "rsrpResult:\n";
    out += rsrpResult.ToString(indent+1);
    return out;
}

std::string MeasResults::measResultPCell::rsrpResult_ToStringNoNewLines() const
{
    std::string out = "rsrpResult:";
    out += rsrpResult.ToStringNoNewLines();
    return out;
}

int MeasResults::measResultPCell::rsrpResult_Clear()
{
    rsrpResult_present = false;
    return 0;
}

bool MeasResults::measResultPCell::rsrpResult_IsPresent() const
{
    return rsrpResult_present;
}

RSRQ_Range* MeasResults::measResultPCell::rsrqResult_Set()
{
    rsrqResult_present = true;
    return &rsrqResult;
}

int MeasResults::measResultPCell::rsrqResult_Set(RSRQ_Range &value)
{
    rsrqResult_present = true;
    rsrqResult = value;
    return 0;
}

const RSRQ_Range& MeasResults::measResultPCell::rsrqResult_Get() const
{
    return rsrqResult;
}

std::string MeasResults::measResultPCell::rsrqResult_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "rsrqResult:\n";
    out += rsrqResult.ToString(indent+1);
    return out;
}

std::string MeasResults::measResultPCell::rsrqResult_ToStringNoNewLines() const
{
    std::string out = "rsrqResult:";
    out += rsrqResult.ToStringNoNewLines();
    return out;
}

int MeasResults::measResultPCell::rsrqResult_Clear()
{
    rsrqResult_present = false;
    return 0;
}

bool MeasResults::measResultPCell::rsrqResult_IsPresent() const
{
    return rsrqResult_present;
}

int MeasResults::measResultNeighCells_Pack(std::vector<uint8_t> &bits)
{
    if(!measResultNeighCells_present)
    {
        printf("MeasResults::measResultNeighCells_Pack() presence failure\n");
        return -1;
    }
    // Extension indicator
    bits.push_back(0);

    // Choice
    for(uint32_t i=0; i<2; i++)
        bits.push_back((measResultNeighCells_internal_choice >> (2-i-1)) & 1);

    // Fields
    if(measResultNeighCells_internal_choice == k_measResultNeighCells_measResultListEUTRA)
    {
        if(0 != measResultNeighCells_measResultListEUTRA.Pack(bits))
        {
            printf("MeasResults::measResultNeighCells_measResultListEUTRA pack failure\n");
            return -1;
        }
    }
    if(measResultNeighCells_internal_choice == k_measResultNeighCells_measResultListUTRA)
    {
        if(0 != measResultNeighCells_measResultListUTRA.Pack(bits))
        {
            printf("MeasResults::measResultNeighCells_measResultListUTRA pack failure\n");
            return -1;
        }
    }
    if(measResultNeighCells_internal_choice == k_measResultNeighCells_measResultListGERAN)
    {
        if(0 != measResultNeighCells_measResultListGERAN.Pack(bits))
        {
            printf("MeasResults::measResultNeighCells_measResultListGERAN pack failure\n");
            return -1;
        }
    }
    if(measResultNeighCells_internal_choice == k_measResultNeighCells_measResultsCDMA2000)
    {
        if(0 != measResultNeighCells_measResultsCDMA2000.Pack(bits))
        {
            printf("MeasResults::measResultNeighCells_measResultsCDMA2000 pack failure\n");
            return -1;
        }
    }
    return 0;
}

int MeasResults::measResultNeighCells_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return measResultNeighCells_Unpack(bits, idx);
}

int MeasResults::measResultNeighCells_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("MeasResults::measResultNeighCells_Unpack() index out of bounds for extension\n");
        return -1;
    }
    idx++;

    // Choice
    uint32_t packed_val = 0;
    if((idx + 2) > bits.size())
    {
        printf("MeasResults::measResultNeighCells_Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<2; i++)
        packed_val |= bits[idx++] << (2-i-1);

    if((MeasResults::measResultNeighCells_Enum)packed_val > k_measResultNeighCells_measResultsCDMA2000)
    {
        printf("MeasResults::measResultNeighCells_Unpack() choice range failure\n");
        return -1;
    }
    measResultNeighCells_internal_choice = (MeasResults::measResultNeighCells_Enum)packed_val;
    measResultNeighCells_present = true;

    // Fields
    if(measResultNeighCells_internal_choice == k_measResultNeighCells_measResultListEUTRA)
    {
        if(0 != measResultNeighCells_measResultListEUTRA.Unpack(bits, idx))
        {
            printf("MeasResults::measResultNeighCells_measResultListEUTRA unpack failure\n");
            return -1;
        }
    }
    if(measResultNeighCells_internal_choice == k_measResultNeighCells_measResultListUTRA)
    {
        if(0 != measResultNeighCells_measResultListUTRA.Unpack(bits, idx))
        {
            printf("MeasResults::measResultNeighCells_measResultListUTRA unpack failure\n");
            return -1;
        }
    }
    if(measResultNeighCells_internal_choice == k_measResultNeighCells_measResultListGERAN)
    {
        if(0 != measResultNeighCells_measResultListGERAN.Unpack(bits, idx))
        {
            printf("MeasResults::measResultNeighCells_measResultListGERAN unpack failure\n");
            return -1;
        }
    }
    if(measResultNeighCells_internal_choice == k_measResultNeighCells_measResultsCDMA2000)
    {
        if(0 != measResultNeighCells_measResultsCDMA2000.Unpack(bits, idx))
        {
            printf("MeasResults::measResultNeighCells_measResultsCDMA2000 unpack failure\n");
            return -1;
        }
    }
    return 0;
}

MeasResults::measResultNeighCells_Enum MeasResults::measResultNeighCells_Choice() const
{
    if(measResultNeighCells_present)
        return measResultNeighCells_internal_choice;
    return (MeasResults::measResultNeighCells_Enum)0;
}

int MeasResults::measResultNeighCells_SetChoice(MeasResults::measResultNeighCells_Enum choice)
{
    measResultNeighCells_internal_choice = choice;
    measResultNeighCells_present = true;
    return 0;
}

std::string MeasResults::measResultNeighCells_ChoiceToString(measResultNeighCells_Enum value) const
{
    if(k_measResultNeighCells_measResultListEUTRA == value)
        return "measResultNeighCells_measResultListEUTRA";
    if(k_measResultNeighCells_measResultListUTRA == value)
        return "measResultNeighCells_measResultListUTRA";
    if(k_measResultNeighCells_measResultListGERAN == value)
        return "measResultNeighCells_measResultListGERAN";
    if(k_measResultNeighCells_measResultsCDMA2000 == value)
        return "measResultNeighCells_measResultsCDMA2000";
    return "";
}

uint64_t MeasResults::measResultNeighCells_NumberOfChoices() const
{
    return 4;
}

std::string MeasResults::measResultNeighCells_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "measResultNeighCells = " + measResultNeighCells_ChoiceToString(measResultNeighCells_internal_choice) + ":\n";
    if(measResultNeighCells_internal_choice == k_measResultNeighCells_measResultListEUTRA)
        out += measResultNeighCells_measResultListEUTRA.ToString(indent+1);
    if(measResultNeighCells_internal_choice == k_measResultNeighCells_measResultListUTRA)
        out += measResultNeighCells_measResultListUTRA.ToString(indent+1);
    if(measResultNeighCells_internal_choice == k_measResultNeighCells_measResultListGERAN)
        out += measResultNeighCells_measResultListGERAN.ToString(indent+1);
    if(measResultNeighCells_internal_choice == k_measResultNeighCells_measResultsCDMA2000)
        out += measResultNeighCells_measResultsCDMA2000.ToString(indent+1);
    return out;
}

std::string MeasResults::measResultNeighCells_ToStringNoNewLines() const
{
    std::string out = "measResultNeighCells=" + measResultNeighCells_ChoiceToString(measResultNeighCells_internal_choice) + ",";
    if(measResultNeighCells_internal_choice == k_measResultNeighCells_measResultListEUTRA)
        out += measResultNeighCells_measResultListEUTRA.ToStringNoNewLines();
    if(measResultNeighCells_internal_choice == k_measResultNeighCells_measResultListUTRA)
        out += measResultNeighCells_measResultListUTRA.ToStringNoNewLines();
    if(measResultNeighCells_internal_choice == k_measResultNeighCells_measResultListGERAN)
        out += measResultNeighCells_measResultListGERAN.ToStringNoNewLines();
    if(measResultNeighCells_internal_choice == k_measResultNeighCells_measResultsCDMA2000)
        out += measResultNeighCells_measResultsCDMA2000.ToStringNoNewLines();
    return out;
}

int MeasResults::measResultNeighCells_Clear()
{
    measResultNeighCells_present = false;
    return 0;
}

bool MeasResults::measResultNeighCells_IsPresent() const
{
    return measResultNeighCells_present;
}

MeasResultListEUTRA* MeasResults::measResultNeighCells_measResultListEUTRA_Set()
{
    measResultNeighCells_measResultListEUTRA_present = true;
    return &measResultNeighCells_measResultListEUTRA;
}

int MeasResults::measResultNeighCells_measResultListEUTRA_Set(MeasResultListEUTRA &value)
{
    measResultNeighCells_measResultListEUTRA_present = true;
    measResultNeighCells_measResultListEUTRA = value;
    return 0;
}

const MeasResultListEUTRA& MeasResults::measResultNeighCells_measResultListEUTRA_Get() const
{
    return measResultNeighCells_measResultListEUTRA;
}

std::string MeasResults::measResultNeighCells_measResultListEUTRA_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "measResultListEUTRA:\n";
    out += measResultNeighCells_measResultListEUTRA.ToString(indent+1);
    return out;
}

std::string MeasResults::measResultNeighCells_measResultListEUTRA_ToStringNoNewLines() const
{
    std::string out = "measResultListEUTRA:";
    out += measResultNeighCells_measResultListEUTRA.ToStringNoNewLines();
    return out;
}

int MeasResults::measResultNeighCells_measResultListEUTRA_Clear()
{
    measResultNeighCells_measResultListEUTRA_present = false;
    return 0;
}

bool MeasResults::measResultNeighCells_measResultListEUTRA_IsPresent() const
{
    return measResultNeighCells_measResultListEUTRA_present;
}

MeasResultListUTRA* MeasResults::measResultNeighCells_measResultListUTRA_Set()
{
    measResultNeighCells_measResultListUTRA_present = true;
    return &measResultNeighCells_measResultListUTRA;
}

int MeasResults::measResultNeighCells_measResultListUTRA_Set(MeasResultListUTRA &value)
{
    measResultNeighCells_measResultListUTRA_present = true;
    measResultNeighCells_measResultListUTRA = value;
    return 0;
}

const MeasResultListUTRA& MeasResults::measResultNeighCells_measResultListUTRA_Get() const
{
    return measResultNeighCells_measResultListUTRA;
}

std::string MeasResults::measResultNeighCells_measResultListUTRA_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "measResultListUTRA:\n";
    out += measResultNeighCells_measResultListUTRA.ToString(indent+1);
    return out;
}

std::string MeasResults::measResultNeighCells_measResultListUTRA_ToStringNoNewLines() const
{
    std::string out = "measResultListUTRA:";
    out += measResultNeighCells_measResultListUTRA.ToStringNoNewLines();
    return out;
}

int MeasResults::measResultNeighCells_measResultListUTRA_Clear()
{
    measResultNeighCells_measResultListUTRA_present = false;
    return 0;
}

bool MeasResults::measResultNeighCells_measResultListUTRA_IsPresent() const
{
    return measResultNeighCells_measResultListUTRA_present;
}

MeasResultListGERAN* MeasResults::measResultNeighCells_measResultListGERAN_Set()
{
    measResultNeighCells_measResultListGERAN_present = true;
    return &measResultNeighCells_measResultListGERAN;
}

int MeasResults::measResultNeighCells_measResultListGERAN_Set(MeasResultListGERAN &value)
{
    measResultNeighCells_measResultListGERAN_present = true;
    measResultNeighCells_measResultListGERAN = value;
    return 0;
}

const MeasResultListGERAN& MeasResults::measResultNeighCells_measResultListGERAN_Get() const
{
    return measResultNeighCells_measResultListGERAN;
}

std::string MeasResults::measResultNeighCells_measResultListGERAN_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "measResultListGERAN:\n";
    out += measResultNeighCells_measResultListGERAN.ToString(indent+1);
    return out;
}

std::string MeasResults::measResultNeighCells_measResultListGERAN_ToStringNoNewLines() const
{
    std::string out = "measResultListGERAN:";
    out += measResultNeighCells_measResultListGERAN.ToStringNoNewLines();
    return out;
}

int MeasResults::measResultNeighCells_measResultListGERAN_Clear()
{
    measResultNeighCells_measResultListGERAN_present = false;
    return 0;
}

bool MeasResults::measResultNeighCells_measResultListGERAN_IsPresent() const
{
    return measResultNeighCells_measResultListGERAN_present;
}

MeasResultsCDMA2000* MeasResults::measResultNeighCells_measResultsCDMA2000_Set()
{
    measResultNeighCells_measResultsCDMA2000_present = true;
    return &measResultNeighCells_measResultsCDMA2000;
}

int MeasResults::measResultNeighCells_measResultsCDMA2000_Set(MeasResultsCDMA2000 &value)
{
    measResultNeighCells_measResultsCDMA2000_present = true;
    measResultNeighCells_measResultsCDMA2000 = value;
    return 0;
}

const MeasResultsCDMA2000& MeasResults::measResultNeighCells_measResultsCDMA2000_Get() const
{
    return measResultNeighCells_measResultsCDMA2000;
}

std::string MeasResults::measResultNeighCells_measResultsCDMA2000_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "measResultsCDMA2000:\n";
    out += measResultNeighCells_measResultsCDMA2000.ToString(indent+1);
    return out;
}

std::string MeasResults::measResultNeighCells_measResultsCDMA2000_ToStringNoNewLines() const
{
    std::string out = "measResultsCDMA2000:";
    out += measResultNeighCells_measResultsCDMA2000.ToStringNoNewLines();
    return out;
}

int MeasResults::measResultNeighCells_measResultsCDMA2000_Clear()
{
    measResultNeighCells_measResultsCDMA2000_present = false;
    return 0;
}

bool MeasResults::measResultNeighCells_measResultsCDMA2000_IsPresent() const
{
    return measResultNeighCells_measResultsCDMA2000_present;
}

MeasResultForECID_r9* MeasResults::measResultForECID_r9_Set()
{
    measResultForECID_r9_present = true;
    return &measResultForECID_r9;
}

int MeasResults::measResultForECID_r9_Set(MeasResultForECID_r9 &value)
{
    measResultForECID_r9_present = true;
    measResultForECID_r9 = value;
    return 0;
}

const MeasResultForECID_r9& MeasResults::measResultForECID_r9_Get() const
{
    return measResultForECID_r9;
}

std::string MeasResults::measResultForECID_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "measResultForECID_r9:\n";
    out += measResultForECID_r9.ToString(indent+1);
    return out;
}

std::string MeasResults::measResultForECID_r9_ToStringNoNewLines() const
{
    std::string out = "measResultForECID_r9:";
    out += measResultForECID_r9.ToStringNoNewLines();
    return out;
}

int MeasResults::measResultForECID_r9_Clear()
{
    measResultForECID_r9_present = false;
    return 0;
}

bool MeasResults::measResultForECID_r9_IsPresent() const
{
    return measResultForECID_r9_present;
}

LocationInfo_r10* MeasResults::locationInfo_r10_Set()
{
    locationInfo_r10_present = true;
    return &locationInfo_r10;
}

int MeasResults::locationInfo_r10_Set(LocationInfo_r10 &value)
{
    locationInfo_r10_present = true;
    locationInfo_r10 = value;
    return 0;
}

const LocationInfo_r10& MeasResults::locationInfo_r10_Get() const
{
    return locationInfo_r10;
}

std::string MeasResults::locationInfo_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "locationInfo_r10:\n";
    out += locationInfo_r10.ToString(indent+1);
    return out;
}

std::string MeasResults::locationInfo_r10_ToStringNoNewLines() const
{
    std::string out = "locationInfo_r10:";
    out += locationInfo_r10.ToStringNoNewLines();
    return out;
}

int MeasResults::locationInfo_r10_Clear()
{
    locationInfo_r10_present = false;
    return 0;
}

bool MeasResults::locationInfo_r10_IsPresent() const
{
    return locationInfo_r10_present;
}

MeasResultServFreqList_r10* MeasResults::measResultServFreqList_r10_Set()
{
    measResultServFreqList_r10_present = true;
    return &measResultServFreqList_r10;
}

int MeasResults::measResultServFreqList_r10_Set(MeasResultServFreqList_r10 &value)
{
    measResultServFreqList_r10_present = true;
    measResultServFreqList_r10 = value;
    return 0;
}

const MeasResultServFreqList_r10& MeasResults::measResultServFreqList_r10_Get() const
{
    return measResultServFreqList_r10;
}

std::string MeasResults::measResultServFreqList_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "measResultServFreqList_r10:\n";
    out += measResultServFreqList_r10.ToString(indent+1);
    return out;
}

std::string MeasResults::measResultServFreqList_r10_ToStringNoNewLines() const
{
    std::string out = "measResultServFreqList_r10:";
    out += measResultServFreqList_r10.ToStringNoNewLines();
    return out;
}

int MeasResults::measResultServFreqList_r10_Clear()
{
    measResultServFreqList_r10_present = false;
    return 0;
}

bool MeasResults::measResultServFreqList_r10_IsPresent() const
{
    return measResultServFreqList_r10_present;
}

