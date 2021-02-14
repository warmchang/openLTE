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

#include "CarrierFreqUTRA_FDD.h"

#include <cmath>

int CarrierFreqUTRA_FDD::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator
    bool has_extension = false;
    if(threshX_Q_r9_value.IsPresent())
    {
        bits.push_back(1);
        has_extension = true;
    }else{
        bits.push_back(0);
    }

    // Optional indicators
    bits.push_back(cellReselectionPriority_IsPresent());

    // Fields
    {
        if(0 != carrierFreq.Pack(bits))
        {
            printf("CarrierFreqUTRA_FDD:: field pack failure\n");
            return -1;
        }
    }
    if(cellReselectionPriority_IsPresent())
    {
        if(0 != cellReselectionPriority.Pack(bits))
        {
            printf("CarrierFreqUTRA_FDD:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != threshX_High.Pack(bits))
        {
            printf("CarrierFreqUTRA_FDD:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != threshX_Low.Pack(bits))
        {
            printf("CarrierFreqUTRA_FDD:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != q_RxLevMin_Pack(bits))
        {
            printf("CarrierFreqUTRA_FDD:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != p_MaxUTRA_Pack(bits))
        {
            printf("CarrierFreqUTRA_FDD:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != q_QualMin_Pack(bits))
        {
            printf("CarrierFreqUTRA_FDD:: field pack failure\n");
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
            printf("CarrierFreqUTRA_FDD:: Extension list size too large failure\n");
            return -1;
        }

        // Extension field presence indicators
        bits.push_back(threshX_Q_r9_value.IsPresent());

        // Extension fields
        if(threshX_Q_r9_value.IsPresent())
        {
            std::vector<uint8_t> field_bits;
            if(0 != threshX_Q_r9_value.Pack(field_bits))
            {
                printf("CarrierFreqUTRA_FDD:: field pack failure\n");
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

int CarrierFreqUTRA_FDD::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int CarrierFreqUTRA_FDD::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("CarrierFreqUTRA_FDD::Unpack() index out of bounds for extension\n");
        return -1;
    }
    bool has_extension = bits[idx++];

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("CarrierFreqUTRA_FDD::Unpack() index out of bounds for optional indiator cellReselectionPriority\n");
        return -1;
    }
    cellReselectionPriority_present = bits[idx++];

    // Fields
    {
        if(0 != carrierFreq.Unpack(bits, idx))
        {
            printf("CarrierFreqUTRA_FDD:: field unpack failure\n");
            return -1;
        }
    }
    if(cellReselectionPriority_present)
    {
        if(0 != cellReselectionPriority.Unpack(bits, idx))
        {
            printf("CarrierFreqUTRA_FDD:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != threshX_High.Unpack(bits, idx))
        {
            printf("CarrierFreqUTRA_FDD:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != threshX_Low.Unpack(bits, idx))
        {
            printf("CarrierFreqUTRA_FDD:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != q_RxLevMin_Unpack(bits, idx))
        {
            printf("CarrierFreqUTRA_FDD:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != p_MaxUTRA_Unpack(bits, idx))
        {
            printf("CarrierFreqUTRA_FDD:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != q_QualMin_Unpack(bits, idx))
        {
            printf("CarrierFreqUTRA_FDD:: field unpack failure\n");
            return -1;
        }
    }

    // Extension
    if(has_extension)
    {
        if((idx + 7) > bits.size())
        {
            printf("CarrierFreqUTRA_FDD::Unpack() index out of bounds for extension size\n");
            return -1;
        }
        // Number of extension fields
        if(bits[idx++] != 0)
        {
            printf("CarrierFreqUTRA_FDD:: Extension list size too large failure\n");
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
                printf("CarrierFreqUTRA_FDD::Unpack() index out of bounds for optional indiator threshX_Q_r9\n");
                return -1;
            }
            threshX_Q_r9_value.SetPresence(bits[idx++]);
        }
        if((idx + (N_ext_fields - opt_ind_count)) > bits.size())
        {
            printf("CarrierFreqUTRA_FDD::Unpack() index out of bounds for extension optional indicators\n");
            return -1;
        }
        idx += (N_ext_fields - opt_ind_count);

        // Extension fields
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
                printf("CarrierFreqUTRA_FDD:: field unpack failure\n");
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
            printf("CarrierFreqUTRA_FDD::Unpack() index out of bounds for extension fields\n");
            return -1;
        }
            idx += N_octets * 8;
        }
    }
    return 0;
}

std::string CarrierFreqUTRA_FDD::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "CarrierFreqUTRA_FDD:\n";
    out += carrierFreq_ToString(indent+1);
    if(cellReselectionPriority_IsPresent())
        out += cellReselectionPriority_ToString(indent+1);
    out += threshX_High_ToString(indent+1);
    out += threshX_Low_ToString(indent+1);
    out += q_RxLevMin_ToString(indent+1);
    out += p_MaxUTRA_ToString(indent+1);
    out += q_QualMin_ToString(indent+1);
    if(threshX_Q_r9_value.IsPresent())
        out += threshX_Q_r9_value.ToString(indent+1);
    return out;
}

std::string CarrierFreqUTRA_FDD::ToStringNoNewLines() const
{
    std::string out = "CarrierFreqUTRA_FDD:";
    out += carrierFreq_ToStringNoNewLines();
    if(cellReselectionPriority_IsPresent())
        out += cellReselectionPriority_ToStringNoNewLines();
    out += threshX_High_ToStringNoNewLines();
    out += threshX_Low_ToStringNoNewLines();
    out += q_RxLevMin_ToStringNoNewLines();
    out += p_MaxUTRA_ToStringNoNewLines();
    out += q_QualMin_ToStringNoNewLines();
    if(threshX_Q_r9_value.IsPresent())
        out += threshX_Q_r9_value.ToStringNoNewLines();
    return out;
}

ARFCN_ValueUTRA* CarrierFreqUTRA_FDD::carrierFreq_Set()
{
    carrierFreq_present = true;
    return &carrierFreq;
}

int CarrierFreqUTRA_FDD::carrierFreq_Set(ARFCN_ValueUTRA &value)
{
    carrierFreq_present = true;
    carrierFreq = value;
    return 0;
}

const ARFCN_ValueUTRA& CarrierFreqUTRA_FDD::carrierFreq_Get() const
{
    return carrierFreq;
}

std::string CarrierFreqUTRA_FDD::carrierFreq_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "carrierFreq:\n";
    out += carrierFreq.ToString(indent+1);
    return out;
}

std::string CarrierFreqUTRA_FDD::carrierFreq_ToStringNoNewLines() const
{
    std::string out = "carrierFreq:";
    out += carrierFreq.ToStringNoNewLines();
    return out;
}

int CarrierFreqUTRA_FDD::carrierFreq_Clear()
{
    carrierFreq_present = false;
    return 0;
}

bool CarrierFreqUTRA_FDD::carrierFreq_IsPresent() const
{
    return carrierFreq_present;
}

CellReselectionPriority* CarrierFreqUTRA_FDD::cellReselectionPriority_Set()
{
    cellReselectionPriority_present = true;
    return &cellReselectionPriority;
}

int CarrierFreqUTRA_FDD::cellReselectionPriority_Set(CellReselectionPriority &value)
{
    cellReselectionPriority_present = true;
    cellReselectionPriority = value;
    return 0;
}

const CellReselectionPriority& CarrierFreqUTRA_FDD::cellReselectionPriority_Get() const
{
    return cellReselectionPriority;
}

std::string CarrierFreqUTRA_FDD::cellReselectionPriority_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cellReselectionPriority:\n";
    out += cellReselectionPriority.ToString(indent+1);
    return out;
}

std::string CarrierFreqUTRA_FDD::cellReselectionPriority_ToStringNoNewLines() const
{
    std::string out = "cellReselectionPriority:";
    out += cellReselectionPriority.ToStringNoNewLines();
    return out;
}

int CarrierFreqUTRA_FDD::cellReselectionPriority_Clear()
{
    cellReselectionPriority_present = false;
    return 0;
}

bool CarrierFreqUTRA_FDD::cellReselectionPriority_IsPresent() const
{
    return cellReselectionPriority_present;
}

ReselectionThreshold* CarrierFreqUTRA_FDD::threshX_High_Set()
{
    threshX_High_present = true;
    return &threshX_High;
}

int CarrierFreqUTRA_FDD::threshX_High_Set(ReselectionThreshold &value)
{
    threshX_High_present = true;
    threshX_High = value;
    return 0;
}

const ReselectionThreshold& CarrierFreqUTRA_FDD::threshX_High_Get() const
{
    return threshX_High;
}

std::string CarrierFreqUTRA_FDD::threshX_High_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "threshX_High:\n";
    out += threshX_High.ToString(indent+1);
    return out;
}

std::string CarrierFreqUTRA_FDD::threshX_High_ToStringNoNewLines() const
{
    std::string out = "threshX_High:";
    out += threshX_High.ToStringNoNewLines();
    return out;
}

int CarrierFreqUTRA_FDD::threshX_High_Clear()
{
    threshX_High_present = false;
    return 0;
}

bool CarrierFreqUTRA_FDD::threshX_High_IsPresent() const
{
    return threshX_High_present;
}

ReselectionThreshold* CarrierFreqUTRA_FDD::threshX_Low_Set()
{
    threshX_Low_present = true;
    return &threshX_Low;
}

int CarrierFreqUTRA_FDD::threshX_Low_Set(ReselectionThreshold &value)
{
    threshX_Low_present = true;
    threshX_Low = value;
    return 0;
}

const ReselectionThreshold& CarrierFreqUTRA_FDD::threshX_Low_Get() const
{
    return threshX_Low;
}

std::string CarrierFreqUTRA_FDD::threshX_Low_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "threshX_Low:\n";
    out += threshX_Low.ToString(indent+1);
    return out;
}

std::string CarrierFreqUTRA_FDD::threshX_Low_ToStringNoNewLines() const
{
    std::string out = "threshX_Low:";
    out += threshX_Low.ToStringNoNewLines();
    return out;
}

int CarrierFreqUTRA_FDD::threshX_Low_Clear()
{
    threshX_Low_present = false;
    return 0;
}

bool CarrierFreqUTRA_FDD::threshX_Low_IsPresent() const
{
    return threshX_Low_present;
}

int CarrierFreqUTRA_FDD::q_RxLevMin_Pack(std::vector<uint8_t> &bits)
{
    if(!q_RxLevMin_present)
    {
        printf("CarrierFreqUTRA_FDD::q_RxLevMin_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = q_RxLevMin_internal_value - (-60);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (-13 - -60))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int CarrierFreqUTRA_FDD::q_RxLevMin_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return q_RxLevMin_Unpack(bits, idx);
}

int CarrierFreqUTRA_FDD::q_RxLevMin_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (-13 - -60))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("CarrierFreqUTRA_FDD::q_RxLevMin_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    q_RxLevMin_internal_value = packed_val + -60;
    q_RxLevMin_present = true;
    return 0;
}

int64_t CarrierFreqUTRA_FDD::q_RxLevMin_Value() const
{
    if(q_RxLevMin_present)
        return q_RxLevMin_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int CarrierFreqUTRA_FDD::q_RxLevMin_SetValue(int64_t value)
{
    if(value < -60 || value > -13)
    {
        printf("CarrierFreqUTRA_FDD::q_RxLevMin_SetValue() range failure\n");
        return -1;
    }
    q_RxLevMin_internal_value = value;
    q_RxLevMin_present = true;
    return 0;
}

std::string CarrierFreqUTRA_FDD::q_RxLevMin_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "q_RxLevMin = " + std::to_string(q_RxLevMin_internal_value) + "\n";
    return out;
}

std::string CarrierFreqUTRA_FDD::q_RxLevMin_ToStringNoNewLines() const
{
    std::string out = "q_RxLevMin=" + std::to_string(q_RxLevMin_internal_value) + ",";
    return out;
}

int CarrierFreqUTRA_FDD::q_RxLevMin_Clear()
{
    q_RxLevMin_present = false;
    return 0;
}

bool CarrierFreqUTRA_FDD::q_RxLevMin_IsPresent() const
{
    return q_RxLevMin_present;
}

int CarrierFreqUTRA_FDD::p_MaxUTRA_Pack(std::vector<uint8_t> &bits)
{
    if(!p_MaxUTRA_present)
    {
        printf("CarrierFreqUTRA_FDD::p_MaxUTRA_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = p_MaxUTRA_internal_value - (-50);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (33 - -50))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int CarrierFreqUTRA_FDD::p_MaxUTRA_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return p_MaxUTRA_Unpack(bits, idx);
}

int CarrierFreqUTRA_FDD::p_MaxUTRA_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (33 - -50))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("CarrierFreqUTRA_FDD::p_MaxUTRA_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    p_MaxUTRA_internal_value = packed_val + -50;
    p_MaxUTRA_present = true;
    return 0;
}

int64_t CarrierFreqUTRA_FDD::p_MaxUTRA_Value() const
{
    if(p_MaxUTRA_present)
        return p_MaxUTRA_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int CarrierFreqUTRA_FDD::p_MaxUTRA_SetValue(int64_t value)
{
    if(value < -50 || value > 33)
    {
        printf("CarrierFreqUTRA_FDD::p_MaxUTRA_SetValue() range failure\n");
        return -1;
    }
    p_MaxUTRA_internal_value = value;
    p_MaxUTRA_present = true;
    return 0;
}

std::string CarrierFreqUTRA_FDD::p_MaxUTRA_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "p_MaxUTRA = " + std::to_string(p_MaxUTRA_internal_value) + "\n";
    return out;
}

std::string CarrierFreqUTRA_FDD::p_MaxUTRA_ToStringNoNewLines() const
{
    std::string out = "p_MaxUTRA=" + std::to_string(p_MaxUTRA_internal_value) + ",";
    return out;
}

int CarrierFreqUTRA_FDD::p_MaxUTRA_Clear()
{
    p_MaxUTRA_present = false;
    return 0;
}

bool CarrierFreqUTRA_FDD::p_MaxUTRA_IsPresent() const
{
    return p_MaxUTRA_present;
}

int CarrierFreqUTRA_FDD::q_QualMin_Pack(std::vector<uint8_t> &bits)
{
    if(!q_QualMin_present)
    {
        printf("CarrierFreqUTRA_FDD::q_QualMin_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = q_QualMin_internal_value - (-24);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (0 - -24))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int CarrierFreqUTRA_FDD::q_QualMin_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return q_QualMin_Unpack(bits, idx);
}

int CarrierFreqUTRA_FDD::q_QualMin_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (0 - -24))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("CarrierFreqUTRA_FDD::q_QualMin_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    q_QualMin_internal_value = packed_val + -24;
    q_QualMin_present = true;
    return 0;
}

int64_t CarrierFreqUTRA_FDD::q_QualMin_Value() const
{
    if(q_QualMin_present)
        return q_QualMin_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int CarrierFreqUTRA_FDD::q_QualMin_SetValue(int64_t value)
{
    if(value < -24 || value > 0)
    {
        printf("CarrierFreqUTRA_FDD::q_QualMin_SetValue() range failure\n");
        return -1;
    }
    q_QualMin_internal_value = value;
    q_QualMin_present = true;
    return 0;
}

std::string CarrierFreqUTRA_FDD::q_QualMin_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "q_QualMin = " + std::to_string(q_QualMin_internal_value) + "\n";
    return out;
}

std::string CarrierFreqUTRA_FDD::q_QualMin_ToStringNoNewLines() const
{
    std::string out = "q_QualMin=" + std::to_string(q_QualMin_internal_value) + ",";
    return out;
}

int CarrierFreqUTRA_FDD::q_QualMin_Clear()
{
    q_QualMin_present = false;
    return 0;
}

bool CarrierFreqUTRA_FDD::q_QualMin_IsPresent() const
{
    return q_QualMin_present;
}

int CarrierFreqUTRA_FDD::threshX_Q_r9::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != threshX_HighQ_r9.Pack(bits))
        {
            printf("CarrierFreqUTRA_FDD::threshX_Q_r9:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != threshX_LowQ_r9.Pack(bits))
        {
            printf("CarrierFreqUTRA_FDD::threshX_Q_r9:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int CarrierFreqUTRA_FDD::threshX_Q_r9::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int CarrierFreqUTRA_FDD::threshX_Q_r9::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != threshX_HighQ_r9.Unpack(bits, idx))
        {
            printf("CarrierFreqUTRA_FDD::threshX_Q_r9:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != threshX_LowQ_r9.Unpack(bits, idx))
        {
            printf("CarrierFreqUTRA_FDD::threshX_Q_r9:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string CarrierFreqUTRA_FDD::threshX_Q_r9::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "threshX_Q_r9:\n";
    out += threshX_HighQ_r9_ToString(indent+1);
    out += threshX_LowQ_r9_ToString(indent+1);
    return out;
}

std::string CarrierFreqUTRA_FDD::threshX_Q_r9::ToStringNoNewLines() const
{
    std::string out = "threshX_Q_r9:";
    out += threshX_HighQ_r9_ToStringNoNewLines();
    out += threshX_LowQ_r9_ToStringNoNewLines();
    return out;
}

int CarrierFreqUTRA_FDD::threshX_Q_r9::Set()
{
    present = true;
    return 0;
}

int CarrierFreqUTRA_FDD::threshX_Q_r9::SetPresence(bool is_present)
{
    present = is_present;
    return 0;
}

int CarrierFreqUTRA_FDD::threshX_Q_r9::Clear()
{
    present = false;
    return 0;
}

bool CarrierFreqUTRA_FDD::threshX_Q_r9::IsPresent() const
{
    return present;
}

ReselectionThresholdQ_r9* CarrierFreqUTRA_FDD::threshX_Q_r9::threshX_HighQ_r9_Set()
{
    threshX_HighQ_r9_present = true;
    return &threshX_HighQ_r9;
}

int CarrierFreqUTRA_FDD::threshX_Q_r9::threshX_HighQ_r9_Set(ReselectionThresholdQ_r9 &value)
{
    threshX_HighQ_r9_present = true;
    threshX_HighQ_r9 = value;
    return 0;
}

const ReselectionThresholdQ_r9& CarrierFreqUTRA_FDD::threshX_Q_r9::threshX_HighQ_r9_Get() const
{
    return threshX_HighQ_r9;
}

std::string CarrierFreqUTRA_FDD::threshX_Q_r9::threshX_HighQ_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "threshX_HighQ_r9:\n";
    out += threshX_HighQ_r9.ToString(indent+1);
    return out;
}

std::string CarrierFreqUTRA_FDD::threshX_Q_r9::threshX_HighQ_r9_ToStringNoNewLines() const
{
    std::string out = "threshX_HighQ_r9:";
    out += threshX_HighQ_r9.ToStringNoNewLines();
    return out;
}

int CarrierFreqUTRA_FDD::threshX_Q_r9::threshX_HighQ_r9_Clear()
{
    threshX_HighQ_r9_present = false;
    return 0;
}

bool CarrierFreqUTRA_FDD::threshX_Q_r9::threshX_HighQ_r9_IsPresent() const
{
    return threshX_HighQ_r9_present;
}

ReselectionThresholdQ_r9* CarrierFreqUTRA_FDD::threshX_Q_r9::threshX_LowQ_r9_Set()
{
    threshX_LowQ_r9_present = true;
    return &threshX_LowQ_r9;
}

int CarrierFreqUTRA_FDD::threshX_Q_r9::threshX_LowQ_r9_Set(ReselectionThresholdQ_r9 &value)
{
    threshX_LowQ_r9_present = true;
    threshX_LowQ_r9 = value;
    return 0;
}

const ReselectionThresholdQ_r9& CarrierFreqUTRA_FDD::threshX_Q_r9::threshX_LowQ_r9_Get() const
{
    return threshX_LowQ_r9;
}

std::string CarrierFreqUTRA_FDD::threshX_Q_r9::threshX_LowQ_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "threshX_LowQ_r9:\n";
    out += threshX_LowQ_r9.ToString(indent+1);
    return out;
}

std::string CarrierFreqUTRA_FDD::threshX_Q_r9::threshX_LowQ_r9_ToStringNoNewLines() const
{
    std::string out = "threshX_LowQ_r9:";
    out += threshX_LowQ_r9.ToStringNoNewLines();
    return out;
}

int CarrierFreqUTRA_FDD::threshX_Q_r9::threshX_LowQ_r9_Clear()
{
    threshX_LowQ_r9_present = false;
    return 0;
}

bool CarrierFreqUTRA_FDD::threshX_Q_r9::threshX_LowQ_r9_IsPresent() const
{
    return threshX_LowQ_r9_present;
}

