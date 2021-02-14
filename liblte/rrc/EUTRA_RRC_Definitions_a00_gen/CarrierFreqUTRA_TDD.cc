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

#include "CarrierFreqUTRA_TDD.h"

#include <cmath>

int CarrierFreqUTRA_TDD::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator
    bits.push_back(0);

    // Optional indicators
    bits.push_back(cellReselectionPriority_IsPresent());

    // Fields
    {
        if(0 != carrierFreq.Pack(bits))
        {
            printf("CarrierFreqUTRA_TDD:: field pack failure\n");
            return -1;
        }
    }
    if(cellReselectionPriority_IsPresent())
    {
        if(0 != cellReselectionPriority.Pack(bits))
        {
            printf("CarrierFreqUTRA_TDD:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != threshX_High.Pack(bits))
        {
            printf("CarrierFreqUTRA_TDD:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != threshX_Low.Pack(bits))
        {
            printf("CarrierFreqUTRA_TDD:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != q_RxLevMin_Pack(bits))
        {
            printf("CarrierFreqUTRA_TDD:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != p_MaxUTRA_Pack(bits))
        {
            printf("CarrierFreqUTRA_TDD:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int CarrierFreqUTRA_TDD::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int CarrierFreqUTRA_TDD::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("CarrierFreqUTRA_TDD::Unpack() index out of bounds for extension\n");
        return -1;
    }
    idx++;

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("CarrierFreqUTRA_TDD::Unpack() index out of bounds for optional indiator cellReselectionPriority\n");
        return -1;
    }
    cellReselectionPriority_present = bits[idx++];

    // Fields
    {
        if(0 != carrierFreq.Unpack(bits, idx))
        {
            printf("CarrierFreqUTRA_TDD:: field unpack failure\n");
            return -1;
        }
    }
    if(cellReselectionPriority_present)
    {
        if(0 != cellReselectionPriority.Unpack(bits, idx))
        {
            printf("CarrierFreqUTRA_TDD:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != threshX_High.Unpack(bits, idx))
        {
            printf("CarrierFreqUTRA_TDD:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != threshX_Low.Unpack(bits, idx))
        {
            printf("CarrierFreqUTRA_TDD:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != q_RxLevMin_Unpack(bits, idx))
        {
            printf("CarrierFreqUTRA_TDD:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != p_MaxUTRA_Unpack(bits, idx))
        {
            printf("CarrierFreqUTRA_TDD:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string CarrierFreqUTRA_TDD::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "CarrierFreqUTRA_TDD:\n";
    out += carrierFreq_ToString(indent+1);
    if(cellReselectionPriority_IsPresent())
        out += cellReselectionPriority_ToString(indent+1);
    out += threshX_High_ToString(indent+1);
    out += threshX_Low_ToString(indent+1);
    out += q_RxLevMin_ToString(indent+1);
    out += p_MaxUTRA_ToString(indent+1);
    return out;
}

std::string CarrierFreqUTRA_TDD::ToStringNoNewLines() const
{
    std::string out = "CarrierFreqUTRA_TDD:";
    out += carrierFreq_ToStringNoNewLines();
    if(cellReselectionPriority_IsPresent())
        out += cellReselectionPriority_ToStringNoNewLines();
    out += threshX_High_ToStringNoNewLines();
    out += threshX_Low_ToStringNoNewLines();
    out += q_RxLevMin_ToStringNoNewLines();
    out += p_MaxUTRA_ToStringNoNewLines();
    return out;
}

ARFCN_ValueUTRA* CarrierFreqUTRA_TDD::carrierFreq_Set()
{
    carrierFreq_present = true;
    return &carrierFreq;
}

int CarrierFreqUTRA_TDD::carrierFreq_Set(ARFCN_ValueUTRA &value)
{
    carrierFreq_present = true;
    carrierFreq = value;
    return 0;
}

const ARFCN_ValueUTRA& CarrierFreqUTRA_TDD::carrierFreq_Get() const
{
    return carrierFreq;
}

std::string CarrierFreqUTRA_TDD::carrierFreq_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "carrierFreq:\n";
    out += carrierFreq.ToString(indent+1);
    return out;
}

std::string CarrierFreqUTRA_TDD::carrierFreq_ToStringNoNewLines() const
{
    std::string out = "carrierFreq:";
    out += carrierFreq.ToStringNoNewLines();
    return out;
}

int CarrierFreqUTRA_TDD::carrierFreq_Clear()
{
    carrierFreq_present = false;
    return 0;
}

bool CarrierFreqUTRA_TDD::carrierFreq_IsPresent() const
{
    return carrierFreq_present;
}

CellReselectionPriority* CarrierFreqUTRA_TDD::cellReselectionPriority_Set()
{
    cellReselectionPriority_present = true;
    return &cellReselectionPriority;
}

int CarrierFreqUTRA_TDD::cellReselectionPriority_Set(CellReselectionPriority &value)
{
    cellReselectionPriority_present = true;
    cellReselectionPriority = value;
    return 0;
}

const CellReselectionPriority& CarrierFreqUTRA_TDD::cellReselectionPriority_Get() const
{
    return cellReselectionPriority;
}

std::string CarrierFreqUTRA_TDD::cellReselectionPriority_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cellReselectionPriority:\n";
    out += cellReselectionPriority.ToString(indent+1);
    return out;
}

std::string CarrierFreqUTRA_TDD::cellReselectionPriority_ToStringNoNewLines() const
{
    std::string out = "cellReselectionPriority:";
    out += cellReselectionPriority.ToStringNoNewLines();
    return out;
}

int CarrierFreqUTRA_TDD::cellReselectionPriority_Clear()
{
    cellReselectionPriority_present = false;
    return 0;
}

bool CarrierFreqUTRA_TDD::cellReselectionPriority_IsPresent() const
{
    return cellReselectionPriority_present;
}

ReselectionThreshold* CarrierFreqUTRA_TDD::threshX_High_Set()
{
    threshX_High_present = true;
    return &threshX_High;
}

int CarrierFreqUTRA_TDD::threshX_High_Set(ReselectionThreshold &value)
{
    threshX_High_present = true;
    threshX_High = value;
    return 0;
}

const ReselectionThreshold& CarrierFreqUTRA_TDD::threshX_High_Get() const
{
    return threshX_High;
}

std::string CarrierFreqUTRA_TDD::threshX_High_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "threshX_High:\n";
    out += threshX_High.ToString(indent+1);
    return out;
}

std::string CarrierFreqUTRA_TDD::threshX_High_ToStringNoNewLines() const
{
    std::string out = "threshX_High:";
    out += threshX_High.ToStringNoNewLines();
    return out;
}

int CarrierFreqUTRA_TDD::threshX_High_Clear()
{
    threshX_High_present = false;
    return 0;
}

bool CarrierFreqUTRA_TDD::threshX_High_IsPresent() const
{
    return threshX_High_present;
}

ReselectionThreshold* CarrierFreqUTRA_TDD::threshX_Low_Set()
{
    threshX_Low_present = true;
    return &threshX_Low;
}

int CarrierFreqUTRA_TDD::threshX_Low_Set(ReselectionThreshold &value)
{
    threshX_Low_present = true;
    threshX_Low = value;
    return 0;
}

const ReselectionThreshold& CarrierFreqUTRA_TDD::threshX_Low_Get() const
{
    return threshX_Low;
}

std::string CarrierFreqUTRA_TDD::threshX_Low_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "threshX_Low:\n";
    out += threshX_Low.ToString(indent+1);
    return out;
}

std::string CarrierFreqUTRA_TDD::threshX_Low_ToStringNoNewLines() const
{
    std::string out = "threshX_Low:";
    out += threshX_Low.ToStringNoNewLines();
    return out;
}

int CarrierFreqUTRA_TDD::threshX_Low_Clear()
{
    threshX_Low_present = false;
    return 0;
}

bool CarrierFreqUTRA_TDD::threshX_Low_IsPresent() const
{
    return threshX_Low_present;
}

int CarrierFreqUTRA_TDD::q_RxLevMin_Pack(std::vector<uint8_t> &bits)
{
    if(!q_RxLevMin_present)
    {
        printf("CarrierFreqUTRA_TDD::q_RxLevMin_Pack() presence failure\n");
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

int CarrierFreqUTRA_TDD::q_RxLevMin_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return q_RxLevMin_Unpack(bits, idx);
}

int CarrierFreqUTRA_TDD::q_RxLevMin_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (-13 - -60))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("CarrierFreqUTRA_TDD::q_RxLevMin_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    q_RxLevMin_internal_value = packed_val + -60;
    q_RxLevMin_present = true;
    return 0;
}

int64_t CarrierFreqUTRA_TDD::q_RxLevMin_Value() const
{
    if(q_RxLevMin_present)
        return q_RxLevMin_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int CarrierFreqUTRA_TDD::q_RxLevMin_SetValue(int64_t value)
{
    if(value < -60 || value > -13)
    {
        printf("CarrierFreqUTRA_TDD::q_RxLevMin_SetValue() range failure\n");
        return -1;
    }
    q_RxLevMin_internal_value = value;
    q_RxLevMin_present = true;
    return 0;
}

std::string CarrierFreqUTRA_TDD::q_RxLevMin_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "q_RxLevMin = " + std::to_string(q_RxLevMin_internal_value) + "\n";
    return out;
}

std::string CarrierFreqUTRA_TDD::q_RxLevMin_ToStringNoNewLines() const
{
    std::string out = "q_RxLevMin=" + std::to_string(q_RxLevMin_internal_value) + ",";
    return out;
}

int CarrierFreqUTRA_TDD::q_RxLevMin_Clear()
{
    q_RxLevMin_present = false;
    return 0;
}

bool CarrierFreqUTRA_TDD::q_RxLevMin_IsPresent() const
{
    return q_RxLevMin_present;
}

int CarrierFreqUTRA_TDD::p_MaxUTRA_Pack(std::vector<uint8_t> &bits)
{
    if(!p_MaxUTRA_present)
    {
        printf("CarrierFreqUTRA_TDD::p_MaxUTRA_Pack() presence failure\n");
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

int CarrierFreqUTRA_TDD::p_MaxUTRA_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return p_MaxUTRA_Unpack(bits, idx);
}

int CarrierFreqUTRA_TDD::p_MaxUTRA_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (33 - -50))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("CarrierFreqUTRA_TDD::p_MaxUTRA_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    p_MaxUTRA_internal_value = packed_val + -50;
    p_MaxUTRA_present = true;
    return 0;
}

int64_t CarrierFreqUTRA_TDD::p_MaxUTRA_Value() const
{
    if(p_MaxUTRA_present)
        return p_MaxUTRA_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int CarrierFreqUTRA_TDD::p_MaxUTRA_SetValue(int64_t value)
{
    if(value < -50 || value > 33)
    {
        printf("CarrierFreqUTRA_TDD::p_MaxUTRA_SetValue() range failure\n");
        return -1;
    }
    p_MaxUTRA_internal_value = value;
    p_MaxUTRA_present = true;
    return 0;
}

std::string CarrierFreqUTRA_TDD::p_MaxUTRA_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "p_MaxUTRA = " + std::to_string(p_MaxUTRA_internal_value) + "\n";
    return out;
}

std::string CarrierFreqUTRA_TDD::p_MaxUTRA_ToStringNoNewLines() const
{
    std::string out = "p_MaxUTRA=" + std::to_string(p_MaxUTRA_internal_value) + ",";
    return out;
}

int CarrierFreqUTRA_TDD::p_MaxUTRA_Clear()
{
    p_MaxUTRA_present = false;
    return 0;
}

bool CarrierFreqUTRA_TDD::p_MaxUTRA_IsPresent() const
{
    return p_MaxUTRA_present;
}

