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

#include "InterFreqCarrierFreqInfo.h"

#include <cmath>

int InterFreqCarrierFreqInfo::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator
    bool has_extension = false;
    if(q_QualMin_r9_IsPresent() || threshX_Q_r9_value.IsPresent())
    {
        bits.push_back(1);
        has_extension = true;
    }else{
        bits.push_back(0);
    }

    // Optional indicators
    bits.push_back(p_Max_IsPresent());
    bits.push_back(t_ReselectionEUTRA_SF_IsPresent());
    bits.push_back(cellReselectionPriority_IsPresent());
    if(!q_OffsetFreq_IsPresent() || q_OffsetFreq_Get().Value() == q_OffsetFreq_GetDefault())
    {
        bits.push_back(0);
    }else{
        bits.push_back(1);
    }
    bits.push_back(interFreqNeighCellList_IsPresent());
    bits.push_back(interFreqBlackCellList_IsPresent());

    // Fields
    {
        if(0 != dl_CarrierFreq.Pack(bits))
        {
            printf("InterFreqCarrierFreqInfo:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != q_RxLevMin.Pack(bits))
        {
            printf("InterFreqCarrierFreqInfo:: field pack failure\n");
            return -1;
        }
    }
    if(p_Max_IsPresent())
    {
        if(0 != p_Max.Pack(bits))
        {
            printf("InterFreqCarrierFreqInfo:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != t_ReselectionEUTRA.Pack(bits))
        {
            printf("InterFreqCarrierFreqInfo:: field pack failure\n");
            return -1;
        }
    }
    if(t_ReselectionEUTRA_SF_IsPresent())
    {
        if(0 != t_ReselectionEUTRA_SF.Pack(bits))
        {
            printf("InterFreqCarrierFreqInfo:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != threshX_High.Pack(bits))
        {
            printf("InterFreqCarrierFreqInfo:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != threshX_Low.Pack(bits))
        {
            printf("InterFreqCarrierFreqInfo:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != allowedMeasBandwidth.Pack(bits))
        {
            printf("InterFreqCarrierFreqInfo:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != presenceAntennaPort1.Pack(bits))
        {
            printf("InterFreqCarrierFreqInfo:: field pack failure\n");
            return -1;
        }
    }
    if(cellReselectionPriority_IsPresent())
    {
        if(0 != cellReselectionPriority.Pack(bits))
        {
            printf("InterFreqCarrierFreqInfo:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != neighCellConfig.Pack(bits))
        {
            printf("InterFreqCarrierFreqInfo:: field pack failure\n");
            return -1;
        }
    }
    if(q_OffsetFreq_IsPresent() || q_OffsetFreq_Get().Value() != q_OffsetFreq_GetDefault())
    {
        if(0 != q_OffsetFreq.Pack(bits))
        {
            printf("InterFreqCarrierFreqInfo:: field pack failure\n");
            return -1;
        }
    }
    if(interFreqNeighCellList_IsPresent())
    {
        if(0 != interFreqNeighCellList.Pack(bits))
        {
            printf("InterFreqCarrierFreqInfo:: field pack failure\n");
            return -1;
        }
    }
    if(interFreqBlackCellList_IsPresent())
    {
        if(0 != interFreqBlackCellList.Pack(bits))
        {
            printf("InterFreqCarrierFreqInfo:: field pack failure\n");
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
            printf("InterFreqCarrierFreqInfo:: Extension list size too large failure\n");
            return -1;
        }

        // Extension field presence indicators
        bits.push_back(q_QualMin_r9_IsPresent());
        bits.push_back(threshX_Q_r9_value.IsPresent());

        // Extension fields
        if(q_QualMin_r9_IsPresent())
        {
            std::vector<uint8_t> field_bits;
            if(0 != q_QualMin_r9.Pack(field_bits))
            {
                printf("InterFreqCarrierFreqInfo:: field pack failure\n");
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
        if(threshX_Q_r9_value.IsPresent())
        {
            std::vector<uint8_t> field_bits;
            if(0 != threshX_Q_r9_value.Pack(field_bits))
            {
                printf("InterFreqCarrierFreqInfo:: field pack failure\n");
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

int InterFreqCarrierFreqInfo::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int InterFreqCarrierFreqInfo::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("InterFreqCarrierFreqInfo::Unpack() index out of bounds for extension\n");
        return -1;
    }
    bool has_extension = bits[idx++];

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("InterFreqCarrierFreqInfo::Unpack() index out of bounds for optional indiator p_Max\n");
        return -1;
    }
    p_Max_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("InterFreqCarrierFreqInfo::Unpack() index out of bounds for optional indiator t_ReselectionEUTRA_SF\n");
        return -1;
    }
    t_ReselectionEUTRA_SF_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("InterFreqCarrierFreqInfo::Unpack() index out of bounds for optional indiator cellReselectionPriority\n");
        return -1;
    }
    cellReselectionPriority_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("InterFreqCarrierFreqInfo::Unpack() index out of bounds for optional indiator q_OffsetFreq\n");
        return -1;
    }
    q_OffsetFreq_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("InterFreqCarrierFreqInfo::Unpack() index out of bounds for optional indiator interFreqNeighCellList\n");
        return -1;
    }
    interFreqNeighCellList_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("InterFreqCarrierFreqInfo::Unpack() index out of bounds for optional indiator interFreqBlackCellList\n");
        return -1;
    }
    interFreqBlackCellList_present = bits[idx++];

    // Fields
    {
        if(0 != dl_CarrierFreq.Unpack(bits, idx))
        {
            printf("InterFreqCarrierFreqInfo:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != q_RxLevMin.Unpack(bits, idx))
        {
            printf("InterFreqCarrierFreqInfo:: field unpack failure\n");
            return -1;
        }
    }
    if(p_Max_present)
    {
        if(0 != p_Max.Unpack(bits, idx))
        {
            printf("InterFreqCarrierFreqInfo:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != t_ReselectionEUTRA.Unpack(bits, idx))
        {
            printf("InterFreqCarrierFreqInfo:: field unpack failure\n");
            return -1;
        }
    }
    if(t_ReselectionEUTRA_SF_present)
    {
        if(0 != t_ReselectionEUTRA_SF.Unpack(bits, idx))
        {
            printf("InterFreqCarrierFreqInfo:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != threshX_High.Unpack(bits, idx))
        {
            printf("InterFreqCarrierFreqInfo:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != threshX_Low.Unpack(bits, idx))
        {
            printf("InterFreqCarrierFreqInfo:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != allowedMeasBandwidth.Unpack(bits, idx))
        {
            printf("InterFreqCarrierFreqInfo:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != presenceAntennaPort1.Unpack(bits, idx))
        {
            printf("InterFreqCarrierFreqInfo:: field unpack failure\n");
            return -1;
        }
    }
    if(cellReselectionPriority_present)
    {
        if(0 != cellReselectionPriority.Unpack(bits, idx))
        {
            printf("InterFreqCarrierFreqInfo:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != neighCellConfig.Unpack(bits, idx))
        {
            printf("InterFreqCarrierFreqInfo:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != q_OffsetFreq.Unpack(bits, idx))
        {
            printf("InterFreqCarrierFreqInfo:: field unpack failure\n");
            return -1;
        }
    }
    if(interFreqNeighCellList_present)
    {
        if(0 != interFreqNeighCellList.Unpack(bits, idx))
        {
            printf("InterFreqCarrierFreqInfo:: field unpack failure\n");
            return -1;
        }
    }
    if(interFreqBlackCellList_present)
    {
        if(0 != interFreqBlackCellList.Unpack(bits, idx))
        {
            printf("InterFreqCarrierFreqInfo:: field unpack failure\n");
            return -1;
        }
    }

    // Extension
    if(has_extension)
    {
        if((idx + 7) > bits.size())
        {
            printf("InterFreqCarrierFreqInfo::Unpack() index out of bounds for extension size\n");
            return -1;
        }
        // Number of extension fields
        if(bits[idx++] != 0)
        {
            printf("InterFreqCarrierFreqInfo:: Extension list size too large failure\n");
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
                printf("InterFreqCarrierFreqInfo::Unpack() index out of bounds for optional indiator q_QualMin_r9\n");
                return -1;
            }
            q_QualMin_r9_present = bits[idx++];
        }
        if(opt_ind_count++ < N_ext_fields)
        {
            if((idx + 1) > bits.size())
            {
                printf("InterFreqCarrierFreqInfo::Unpack() index out of bounds for optional indiator threshX_Q_r9\n");
                return -1;
            }
            threshX_Q_r9_value.SetPresence(bits[idx++]);
        }
        if((idx + (N_ext_fields - opt_ind_count)) > bits.size())
        {
            printf("InterFreqCarrierFreqInfo::Unpack() index out of bounds for extension optional indicators\n");
            return -1;
        }
        idx += (N_ext_fields - opt_ind_count);

        // Extension fields
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
                printf("InterFreqCarrierFreqInfo:: field unpack failure\n");
                return -1;
            }
            idx = orig_idx + (N_octets * 8);
        }
        if(threshX_Q_r9_value.IsPresent())
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
            if(0 != threshX_Q_r9_value.Unpack(bits, idx))
            {
                printf("InterFreqCarrierFreqInfo:: field unpack failure\n");
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
            printf("InterFreqCarrierFreqInfo::Unpack() index out of bounds for extension fields\n");
            return -1;
        }
            idx += N_octets * 8;
        }
    }
    return 0;
}

std::string InterFreqCarrierFreqInfo::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "InterFreqCarrierFreqInfo:\n";
    out += dl_CarrierFreq_ToString(indent+1);
    out += q_RxLevMin_ToString(indent+1);
    if(p_Max_IsPresent())
        out += p_Max_ToString(indent+1);
    out += t_ReselectionEUTRA_ToString(indent+1);
    if(t_ReselectionEUTRA_SF_IsPresent())
        out += t_ReselectionEUTRA_SF_ToString(indent+1);
    out += threshX_High_ToString(indent+1);
    out += threshX_Low_ToString(indent+1);
    out += allowedMeasBandwidth_ToString(indent+1);
    out += presenceAntennaPort1_ToString(indent+1);
    if(cellReselectionPriority_IsPresent())
        out += cellReselectionPriority_ToString(indent+1);
    out += neighCellConfig_ToString(indent+1);
    out += q_OffsetFreq_ToString(indent+1);
    if(interFreqNeighCellList_IsPresent())
        out += interFreqNeighCellList_ToString(indent+1);
    if(interFreqBlackCellList_IsPresent())
        out += interFreqBlackCellList_ToString(indent+1);
    if(q_QualMin_r9_IsPresent())
        out += q_QualMin_r9_ToString(indent+1);
    if(threshX_Q_r9_value.IsPresent())
        out += threshX_Q_r9_value.ToString(indent+1);
    return out;
}

std::string InterFreqCarrierFreqInfo::ToStringNoNewLines() const
{
    std::string out = "InterFreqCarrierFreqInfo:";
    out += dl_CarrierFreq_ToStringNoNewLines();
    out += q_RxLevMin_ToStringNoNewLines();
    if(p_Max_IsPresent())
        out += p_Max_ToStringNoNewLines();
    out += t_ReselectionEUTRA_ToStringNoNewLines();
    if(t_ReselectionEUTRA_SF_IsPresent())
        out += t_ReselectionEUTRA_SF_ToStringNoNewLines();
    out += threshX_High_ToStringNoNewLines();
    out += threshX_Low_ToStringNoNewLines();
    out += allowedMeasBandwidth_ToStringNoNewLines();
    out += presenceAntennaPort1_ToStringNoNewLines();
    if(cellReselectionPriority_IsPresent())
        out += cellReselectionPriority_ToStringNoNewLines();
    out += neighCellConfig_ToStringNoNewLines();
    out += q_OffsetFreq_ToStringNoNewLines();
    if(interFreqNeighCellList_IsPresent())
        out += interFreqNeighCellList_ToStringNoNewLines();
    if(interFreqBlackCellList_IsPresent())
        out += interFreqBlackCellList_ToStringNoNewLines();
    if(q_QualMin_r9_IsPresent())
        out += q_QualMin_r9_ToStringNoNewLines();
    if(threshX_Q_r9_value.IsPresent())
        out += threshX_Q_r9_value.ToStringNoNewLines();
    return out;
}

ARFCN_ValueEUTRA* InterFreqCarrierFreqInfo::dl_CarrierFreq_Set()
{
    dl_CarrierFreq_present = true;
    return &dl_CarrierFreq;
}

int InterFreqCarrierFreqInfo::dl_CarrierFreq_Set(ARFCN_ValueEUTRA &value)
{
    dl_CarrierFreq_present = true;
    dl_CarrierFreq = value;
    return 0;
}

const ARFCN_ValueEUTRA& InterFreqCarrierFreqInfo::dl_CarrierFreq_Get() const
{
    return dl_CarrierFreq;
}

std::string InterFreqCarrierFreqInfo::dl_CarrierFreq_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "dl_CarrierFreq:\n";
    out += dl_CarrierFreq.ToString(indent+1);
    return out;
}

std::string InterFreqCarrierFreqInfo::dl_CarrierFreq_ToStringNoNewLines() const
{
    std::string out = "dl_CarrierFreq:";
    out += dl_CarrierFreq.ToStringNoNewLines();
    return out;
}

int InterFreqCarrierFreqInfo::dl_CarrierFreq_Clear()
{
    dl_CarrierFreq_present = false;
    return 0;
}

bool InterFreqCarrierFreqInfo::dl_CarrierFreq_IsPresent() const
{
    return dl_CarrierFreq_present;
}

Q_RxLevMin* InterFreqCarrierFreqInfo::q_RxLevMin_Set()
{
    q_RxLevMin_present = true;
    return &q_RxLevMin;
}

int InterFreqCarrierFreqInfo::q_RxLevMin_Set(Q_RxLevMin &value)
{
    q_RxLevMin_present = true;
    q_RxLevMin = value;
    return 0;
}

const Q_RxLevMin& InterFreqCarrierFreqInfo::q_RxLevMin_Get() const
{
    return q_RxLevMin;
}

std::string InterFreqCarrierFreqInfo::q_RxLevMin_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "q_RxLevMin:\n";
    out += q_RxLevMin.ToString(indent+1);
    return out;
}

std::string InterFreqCarrierFreqInfo::q_RxLevMin_ToStringNoNewLines() const
{
    std::string out = "q_RxLevMin:";
    out += q_RxLevMin.ToStringNoNewLines();
    return out;
}

int InterFreqCarrierFreqInfo::q_RxLevMin_Clear()
{
    q_RxLevMin_present = false;
    return 0;
}

bool InterFreqCarrierFreqInfo::q_RxLevMin_IsPresent() const
{
    return q_RxLevMin_present;
}

P_Max* InterFreqCarrierFreqInfo::p_Max_Set()
{
    p_Max_present = true;
    return &p_Max;
}

int InterFreqCarrierFreqInfo::p_Max_Set(P_Max &value)
{
    p_Max_present = true;
    p_Max = value;
    return 0;
}

const P_Max& InterFreqCarrierFreqInfo::p_Max_Get() const
{
    return p_Max;
}

std::string InterFreqCarrierFreqInfo::p_Max_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "p_Max:\n";
    out += p_Max.ToString(indent+1);
    return out;
}

std::string InterFreqCarrierFreqInfo::p_Max_ToStringNoNewLines() const
{
    std::string out = "p_Max:";
    out += p_Max.ToStringNoNewLines();
    return out;
}

int InterFreqCarrierFreqInfo::p_Max_Clear()
{
    p_Max_present = false;
    return 0;
}

bool InterFreqCarrierFreqInfo::p_Max_IsPresent() const
{
    return p_Max_present;
}

T_Reselection* InterFreqCarrierFreqInfo::t_ReselectionEUTRA_Set()
{
    t_ReselectionEUTRA_present = true;
    return &t_ReselectionEUTRA;
}

int InterFreqCarrierFreqInfo::t_ReselectionEUTRA_Set(T_Reselection &value)
{
    t_ReselectionEUTRA_present = true;
    t_ReselectionEUTRA = value;
    return 0;
}

const T_Reselection& InterFreqCarrierFreqInfo::t_ReselectionEUTRA_Get() const
{
    return t_ReselectionEUTRA;
}

std::string InterFreqCarrierFreqInfo::t_ReselectionEUTRA_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "t_ReselectionEUTRA:\n";
    out += t_ReselectionEUTRA.ToString(indent+1);
    return out;
}

std::string InterFreqCarrierFreqInfo::t_ReselectionEUTRA_ToStringNoNewLines() const
{
    std::string out = "t_ReselectionEUTRA:";
    out += t_ReselectionEUTRA.ToStringNoNewLines();
    return out;
}

int InterFreqCarrierFreqInfo::t_ReselectionEUTRA_Clear()
{
    t_ReselectionEUTRA_present = false;
    return 0;
}

bool InterFreqCarrierFreqInfo::t_ReselectionEUTRA_IsPresent() const
{
    return t_ReselectionEUTRA_present;
}

SpeedStateScaleFactors* InterFreqCarrierFreqInfo::t_ReselectionEUTRA_SF_Set()
{
    t_ReselectionEUTRA_SF_present = true;
    return &t_ReselectionEUTRA_SF;
}

int InterFreqCarrierFreqInfo::t_ReselectionEUTRA_SF_Set(SpeedStateScaleFactors &value)
{
    t_ReselectionEUTRA_SF_present = true;
    t_ReselectionEUTRA_SF = value;
    return 0;
}

const SpeedStateScaleFactors& InterFreqCarrierFreqInfo::t_ReselectionEUTRA_SF_Get() const
{
    return t_ReselectionEUTRA_SF;
}

std::string InterFreqCarrierFreqInfo::t_ReselectionEUTRA_SF_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "t_ReselectionEUTRA_SF:\n";
    out += t_ReselectionEUTRA_SF.ToString(indent+1);
    return out;
}

std::string InterFreqCarrierFreqInfo::t_ReselectionEUTRA_SF_ToStringNoNewLines() const
{
    std::string out = "t_ReselectionEUTRA_SF:";
    out += t_ReselectionEUTRA_SF.ToStringNoNewLines();
    return out;
}

int InterFreqCarrierFreqInfo::t_ReselectionEUTRA_SF_Clear()
{
    t_ReselectionEUTRA_SF_present = false;
    return 0;
}

bool InterFreqCarrierFreqInfo::t_ReselectionEUTRA_SF_IsPresent() const
{
    return t_ReselectionEUTRA_SF_present;
}

ReselectionThreshold* InterFreqCarrierFreqInfo::threshX_High_Set()
{
    threshX_High_present = true;
    return &threshX_High;
}

int InterFreqCarrierFreqInfo::threshX_High_Set(ReselectionThreshold &value)
{
    threshX_High_present = true;
    threshX_High = value;
    return 0;
}

const ReselectionThreshold& InterFreqCarrierFreqInfo::threshX_High_Get() const
{
    return threshX_High;
}

std::string InterFreqCarrierFreqInfo::threshX_High_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "threshX_High:\n";
    out += threshX_High.ToString(indent+1);
    return out;
}

std::string InterFreqCarrierFreqInfo::threshX_High_ToStringNoNewLines() const
{
    std::string out = "threshX_High:";
    out += threshX_High.ToStringNoNewLines();
    return out;
}

int InterFreqCarrierFreqInfo::threshX_High_Clear()
{
    threshX_High_present = false;
    return 0;
}

bool InterFreqCarrierFreqInfo::threshX_High_IsPresent() const
{
    return threshX_High_present;
}

ReselectionThreshold* InterFreqCarrierFreqInfo::threshX_Low_Set()
{
    threshX_Low_present = true;
    return &threshX_Low;
}

int InterFreqCarrierFreqInfo::threshX_Low_Set(ReselectionThreshold &value)
{
    threshX_Low_present = true;
    threshX_Low = value;
    return 0;
}

const ReselectionThreshold& InterFreqCarrierFreqInfo::threshX_Low_Get() const
{
    return threshX_Low;
}

std::string InterFreqCarrierFreqInfo::threshX_Low_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "threshX_Low:\n";
    out += threshX_Low.ToString(indent+1);
    return out;
}

std::string InterFreqCarrierFreqInfo::threshX_Low_ToStringNoNewLines() const
{
    std::string out = "threshX_Low:";
    out += threshX_Low.ToStringNoNewLines();
    return out;
}

int InterFreqCarrierFreqInfo::threshX_Low_Clear()
{
    threshX_Low_present = false;
    return 0;
}

bool InterFreqCarrierFreqInfo::threshX_Low_IsPresent() const
{
    return threshX_Low_present;
}

AllowedMeasBandwidth* InterFreqCarrierFreqInfo::allowedMeasBandwidth_Set()
{
    allowedMeasBandwidth_present = true;
    return &allowedMeasBandwidth;
}

int InterFreqCarrierFreqInfo::allowedMeasBandwidth_Set(AllowedMeasBandwidth &value)
{
    allowedMeasBandwidth_present = true;
    allowedMeasBandwidth = value;
    return 0;
}

const AllowedMeasBandwidth& InterFreqCarrierFreqInfo::allowedMeasBandwidth_Get() const
{
    return allowedMeasBandwidth;
}

std::string InterFreqCarrierFreqInfo::allowedMeasBandwidth_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "allowedMeasBandwidth:\n";
    out += allowedMeasBandwidth.ToString(indent+1);
    return out;
}

std::string InterFreqCarrierFreqInfo::allowedMeasBandwidth_ToStringNoNewLines() const
{
    std::string out = "allowedMeasBandwidth:";
    out += allowedMeasBandwidth.ToStringNoNewLines();
    return out;
}

int InterFreqCarrierFreqInfo::allowedMeasBandwidth_Clear()
{
    allowedMeasBandwidth_present = false;
    return 0;
}

bool InterFreqCarrierFreqInfo::allowedMeasBandwidth_IsPresent() const
{
    return allowedMeasBandwidth_present;
}

PresenceAntennaPort1* InterFreqCarrierFreqInfo::presenceAntennaPort1_Set()
{
    presenceAntennaPort1_present = true;
    return &presenceAntennaPort1;
}

int InterFreqCarrierFreqInfo::presenceAntennaPort1_Set(PresenceAntennaPort1 &value)
{
    presenceAntennaPort1_present = true;
    presenceAntennaPort1 = value;
    return 0;
}

const PresenceAntennaPort1& InterFreqCarrierFreqInfo::presenceAntennaPort1_Get() const
{
    return presenceAntennaPort1;
}

std::string InterFreqCarrierFreqInfo::presenceAntennaPort1_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "presenceAntennaPort1:\n";
    out += presenceAntennaPort1.ToString(indent+1);
    return out;
}

std::string InterFreqCarrierFreqInfo::presenceAntennaPort1_ToStringNoNewLines() const
{
    std::string out = "presenceAntennaPort1:";
    out += presenceAntennaPort1.ToStringNoNewLines();
    return out;
}

int InterFreqCarrierFreqInfo::presenceAntennaPort1_Clear()
{
    presenceAntennaPort1_present = false;
    return 0;
}

bool InterFreqCarrierFreqInfo::presenceAntennaPort1_IsPresent() const
{
    return presenceAntennaPort1_present;
}

CellReselectionPriority* InterFreqCarrierFreqInfo::cellReselectionPriority_Set()
{
    cellReselectionPriority_present = true;
    return &cellReselectionPriority;
}

int InterFreqCarrierFreqInfo::cellReselectionPriority_Set(CellReselectionPriority &value)
{
    cellReselectionPriority_present = true;
    cellReselectionPriority = value;
    return 0;
}

const CellReselectionPriority& InterFreqCarrierFreqInfo::cellReselectionPriority_Get() const
{
    return cellReselectionPriority;
}

std::string InterFreqCarrierFreqInfo::cellReselectionPriority_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cellReselectionPriority:\n";
    out += cellReselectionPriority.ToString(indent+1);
    return out;
}

std::string InterFreqCarrierFreqInfo::cellReselectionPriority_ToStringNoNewLines() const
{
    std::string out = "cellReselectionPriority:";
    out += cellReselectionPriority.ToStringNoNewLines();
    return out;
}

int InterFreqCarrierFreqInfo::cellReselectionPriority_Clear()
{
    cellReselectionPriority_present = false;
    return 0;
}

bool InterFreqCarrierFreqInfo::cellReselectionPriority_IsPresent() const
{
    return cellReselectionPriority_present;
}

NeighCellConfig* InterFreqCarrierFreqInfo::neighCellConfig_Set()
{
    neighCellConfig_present = true;
    return &neighCellConfig;
}

int InterFreqCarrierFreqInfo::neighCellConfig_Set(NeighCellConfig &value)
{
    neighCellConfig_present = true;
    neighCellConfig = value;
    return 0;
}

const NeighCellConfig& InterFreqCarrierFreqInfo::neighCellConfig_Get() const
{
    return neighCellConfig;
}

std::string InterFreqCarrierFreqInfo::neighCellConfig_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "neighCellConfig:\n";
    out += neighCellConfig.ToString(indent+1);
    return out;
}

std::string InterFreqCarrierFreqInfo::neighCellConfig_ToStringNoNewLines() const
{
    std::string out = "neighCellConfig:";
    out += neighCellConfig.ToStringNoNewLines();
    return out;
}

int InterFreqCarrierFreqInfo::neighCellConfig_Clear()
{
    neighCellConfig_present = false;
    return 0;
}

bool InterFreqCarrierFreqInfo::neighCellConfig_IsPresent() const
{
    return neighCellConfig_present;
}

Q_OffsetRange* InterFreqCarrierFreqInfo::q_OffsetFreq_Set()
{
    q_OffsetFreq_present = true;
    return &q_OffsetFreq;
}

int InterFreqCarrierFreqInfo::q_OffsetFreq_Set(Q_OffsetRange &value)
{
    q_OffsetFreq_present = true;
    q_OffsetFreq = value;
    return 0;
}

const Q_OffsetRange& InterFreqCarrierFreqInfo::q_OffsetFreq_Get() const
{
    return q_OffsetFreq;
}

Q_OffsetRange::Enum InterFreqCarrierFreqInfo::q_OffsetFreq_GetDefault() const
{
    return Q_OffsetRange::k_dB0;
}

std::string InterFreqCarrierFreqInfo::q_OffsetFreq_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "q_OffsetFreq:\n";
    out += q_OffsetFreq.ToString(indent+1);
    return out;
}

std::string InterFreqCarrierFreqInfo::q_OffsetFreq_ToStringNoNewLines() const
{
    std::string out = "q_OffsetFreq:";
    out += q_OffsetFreq.ToStringNoNewLines();
    return out;
}

int InterFreqCarrierFreqInfo::q_OffsetFreq_Clear()
{
    q_OffsetFreq_present = false;
    return 0;
}

bool InterFreqCarrierFreqInfo::q_OffsetFreq_IsPresent() const
{
    return q_OffsetFreq_present;
}

InterFreqNeighCellList* InterFreqCarrierFreqInfo::interFreqNeighCellList_Set()
{
    interFreqNeighCellList_present = true;
    return &interFreqNeighCellList;
}

int InterFreqCarrierFreqInfo::interFreqNeighCellList_Set(InterFreqNeighCellList &value)
{
    interFreqNeighCellList_present = true;
    interFreqNeighCellList = value;
    return 0;
}

const InterFreqNeighCellList& InterFreqCarrierFreqInfo::interFreqNeighCellList_Get() const
{
    return interFreqNeighCellList;
}

std::string InterFreqCarrierFreqInfo::interFreqNeighCellList_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "interFreqNeighCellList:\n";
    out += interFreqNeighCellList.ToString(indent+1);
    return out;
}

std::string InterFreqCarrierFreqInfo::interFreqNeighCellList_ToStringNoNewLines() const
{
    std::string out = "interFreqNeighCellList:";
    out += interFreqNeighCellList.ToStringNoNewLines();
    return out;
}

int InterFreqCarrierFreqInfo::interFreqNeighCellList_Clear()
{
    interFreqNeighCellList_present = false;
    return 0;
}

bool InterFreqCarrierFreqInfo::interFreqNeighCellList_IsPresent() const
{
    return interFreqNeighCellList_present;
}

InterFreqBlackCellList* InterFreqCarrierFreqInfo::interFreqBlackCellList_Set()
{
    interFreqBlackCellList_present = true;
    return &interFreqBlackCellList;
}

int InterFreqCarrierFreqInfo::interFreqBlackCellList_Set(InterFreqBlackCellList &value)
{
    interFreqBlackCellList_present = true;
    interFreqBlackCellList = value;
    return 0;
}

const InterFreqBlackCellList& InterFreqCarrierFreqInfo::interFreqBlackCellList_Get() const
{
    return interFreqBlackCellList;
}

std::string InterFreqCarrierFreqInfo::interFreqBlackCellList_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "interFreqBlackCellList:\n";
    out += interFreqBlackCellList.ToString(indent+1);
    return out;
}

std::string InterFreqCarrierFreqInfo::interFreqBlackCellList_ToStringNoNewLines() const
{
    std::string out = "interFreqBlackCellList:";
    out += interFreqBlackCellList.ToStringNoNewLines();
    return out;
}

int InterFreqCarrierFreqInfo::interFreqBlackCellList_Clear()
{
    interFreqBlackCellList_present = false;
    return 0;
}

bool InterFreqCarrierFreqInfo::interFreqBlackCellList_IsPresent() const
{
    return interFreqBlackCellList_present;
}

Q_QualMin_r9* InterFreqCarrierFreqInfo::q_QualMin_r9_Set()
{
    q_QualMin_r9_present = true;
    return &q_QualMin_r9;
}

int InterFreqCarrierFreqInfo::q_QualMin_r9_Set(Q_QualMin_r9 &value)
{
    q_QualMin_r9_present = true;
    q_QualMin_r9 = value;
    return 0;
}

const Q_QualMin_r9& InterFreqCarrierFreqInfo::q_QualMin_r9_Get() const
{
    return q_QualMin_r9;
}

std::string InterFreqCarrierFreqInfo::q_QualMin_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "q_QualMin_r9:\n";
    out += q_QualMin_r9.ToString(indent+1);
    return out;
}

std::string InterFreqCarrierFreqInfo::q_QualMin_r9_ToStringNoNewLines() const
{
    std::string out = "q_QualMin_r9:";
    out += q_QualMin_r9.ToStringNoNewLines();
    return out;
}

int InterFreqCarrierFreqInfo::q_QualMin_r9_Clear()
{
    q_QualMin_r9_present = false;
    return 0;
}

bool InterFreqCarrierFreqInfo::q_QualMin_r9_IsPresent() const
{
    return q_QualMin_r9_present;
}

int InterFreqCarrierFreqInfo::threshX_Q_r9::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != threshX_HighQ_r9.Pack(bits))
        {
            printf("InterFreqCarrierFreqInfo::threshX_Q_r9:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != threshX_LowQ_r9.Pack(bits))
        {
            printf("InterFreqCarrierFreqInfo::threshX_Q_r9:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int InterFreqCarrierFreqInfo::threshX_Q_r9::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int InterFreqCarrierFreqInfo::threshX_Q_r9::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != threshX_HighQ_r9.Unpack(bits, idx))
        {
            printf("InterFreqCarrierFreqInfo::threshX_Q_r9:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != threshX_LowQ_r9.Unpack(bits, idx))
        {
            printf("InterFreqCarrierFreqInfo::threshX_Q_r9:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string InterFreqCarrierFreqInfo::threshX_Q_r9::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "threshX_Q_r9:\n";
    out += threshX_HighQ_r9_ToString(indent+1);
    out += threshX_LowQ_r9_ToString(indent+1);
    return out;
}

std::string InterFreqCarrierFreqInfo::threshX_Q_r9::ToStringNoNewLines() const
{
    std::string out = "threshX_Q_r9:";
    out += threshX_HighQ_r9_ToStringNoNewLines();
    out += threshX_LowQ_r9_ToStringNoNewLines();
    return out;
}

int InterFreqCarrierFreqInfo::threshX_Q_r9::Set()
{
    present = true;
    return 0;
}

int InterFreqCarrierFreqInfo::threshX_Q_r9::SetPresence(bool is_present)
{
    present = is_present;
    return 0;
}

int InterFreqCarrierFreqInfo::threshX_Q_r9::Clear()
{
    present = false;
    return 0;
}

bool InterFreqCarrierFreqInfo::threshX_Q_r9::IsPresent() const
{
    return present;
}

ReselectionThresholdQ_r9* InterFreqCarrierFreqInfo::threshX_Q_r9::threshX_HighQ_r9_Set()
{
    threshX_HighQ_r9_present = true;
    return &threshX_HighQ_r9;
}

int InterFreqCarrierFreqInfo::threshX_Q_r9::threshX_HighQ_r9_Set(ReselectionThresholdQ_r9 &value)
{
    threshX_HighQ_r9_present = true;
    threshX_HighQ_r9 = value;
    return 0;
}

const ReselectionThresholdQ_r9& InterFreqCarrierFreqInfo::threshX_Q_r9::threshX_HighQ_r9_Get() const
{
    return threshX_HighQ_r9;
}

std::string InterFreqCarrierFreqInfo::threshX_Q_r9::threshX_HighQ_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "threshX_HighQ_r9:\n";
    out += threshX_HighQ_r9.ToString(indent+1);
    return out;
}

std::string InterFreqCarrierFreqInfo::threshX_Q_r9::threshX_HighQ_r9_ToStringNoNewLines() const
{
    std::string out = "threshX_HighQ_r9:";
    out += threshX_HighQ_r9.ToStringNoNewLines();
    return out;
}

int InterFreqCarrierFreqInfo::threshX_Q_r9::threshX_HighQ_r9_Clear()
{
    threshX_HighQ_r9_present = false;
    return 0;
}

bool InterFreqCarrierFreqInfo::threshX_Q_r9::threshX_HighQ_r9_IsPresent() const
{
    return threshX_HighQ_r9_present;
}

ReselectionThresholdQ_r9* InterFreqCarrierFreqInfo::threshX_Q_r9::threshX_LowQ_r9_Set()
{
    threshX_LowQ_r9_present = true;
    return &threshX_LowQ_r9;
}

int InterFreqCarrierFreqInfo::threshX_Q_r9::threshX_LowQ_r9_Set(ReselectionThresholdQ_r9 &value)
{
    threshX_LowQ_r9_present = true;
    threshX_LowQ_r9 = value;
    return 0;
}

const ReselectionThresholdQ_r9& InterFreqCarrierFreqInfo::threshX_Q_r9::threshX_LowQ_r9_Get() const
{
    return threshX_LowQ_r9;
}

std::string InterFreqCarrierFreqInfo::threshX_Q_r9::threshX_LowQ_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "threshX_LowQ_r9:\n";
    out += threshX_LowQ_r9.ToString(indent+1);
    return out;
}

std::string InterFreqCarrierFreqInfo::threshX_Q_r9::threshX_LowQ_r9_ToStringNoNewLines() const
{
    std::string out = "threshX_LowQ_r9:";
    out += threshX_LowQ_r9.ToStringNoNewLines();
    return out;
}

int InterFreqCarrierFreqInfo::threshX_Q_r9::threshX_LowQ_r9_Clear()
{
    threshX_LowQ_r9_present = false;
    return 0;
}

bool InterFreqCarrierFreqInfo::threshX_Q_r9::threshX_LowQ_r9_IsPresent() const
{
    return threshX_LowQ_r9_present;
}

