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

#include "CarrierFreqsInfoGERAN.h"

#include <cmath>

int CarrierFreqsInfoGERAN::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator
    bits.push_back(0);

    // Optional indicators

    // Fields
    {
        if(0 != carrierFreqs.Pack(bits))
        {
            printf("CarrierFreqsInfoGERAN:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != commonInfo_value.Pack(bits))
        {
            printf("CarrierFreqsInfoGERAN:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int CarrierFreqsInfoGERAN::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int CarrierFreqsInfoGERAN::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("CarrierFreqsInfoGERAN::Unpack() index out of bounds for extension\n");
        return -1;
    }
    idx++;

    // Optional indicators

    // Fields
    {
        if(0 != carrierFreqs.Unpack(bits, idx))
        {
            printf("CarrierFreqsInfoGERAN:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != commonInfo_value.Unpack(bits, idx))
        {
            printf("CarrierFreqsInfoGERAN:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string CarrierFreqsInfoGERAN::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "CarrierFreqsInfoGERAN:\n";
    out += carrierFreqs_ToString(indent+1);
    out += commonInfo_value.ToString(indent+1);
    return out;
}

std::string CarrierFreqsInfoGERAN::ToStringNoNewLines() const
{
    std::string out = "CarrierFreqsInfoGERAN:";
    out += carrierFreqs_ToStringNoNewLines();
    out += commonInfo_value.ToStringNoNewLines();
    return out;
}

CarrierFreqsGERAN* CarrierFreqsInfoGERAN::carrierFreqs_Set()
{
    carrierFreqs_present = true;
    return &carrierFreqs;
}

int CarrierFreqsInfoGERAN::carrierFreqs_Set(CarrierFreqsGERAN &value)
{
    carrierFreqs_present = true;
    carrierFreqs = value;
    return 0;
}

const CarrierFreqsGERAN& CarrierFreqsInfoGERAN::carrierFreqs_Get() const
{
    return carrierFreqs;
}

std::string CarrierFreqsInfoGERAN::carrierFreqs_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "carrierFreqs:\n";
    out += carrierFreqs.ToString(indent+1);
    return out;
}

std::string CarrierFreqsInfoGERAN::carrierFreqs_ToStringNoNewLines() const
{
    std::string out = "carrierFreqs:";
    out += carrierFreqs.ToStringNoNewLines();
    return out;
}

int CarrierFreqsInfoGERAN::carrierFreqs_Clear()
{
    carrierFreqs_present = false;
    return 0;
}

bool CarrierFreqsInfoGERAN::carrierFreqs_IsPresent() const
{
    return carrierFreqs_present;
}

int CarrierFreqsInfoGERAN::commonInfo::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(cellReselectionPriority_IsPresent());
    bits.push_back(p_MaxGERAN_IsPresent());

    // Fields
    if(cellReselectionPriority_IsPresent())
    {
        if(0 != cellReselectionPriority.Pack(bits))
        {
            printf("CarrierFreqsInfoGERAN::commonInfo:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != ncc_Permitted_Pack(bits))
        {
            printf("CarrierFreqsInfoGERAN::commonInfo:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != q_RxLevMin_Pack(bits))
        {
            printf("CarrierFreqsInfoGERAN::commonInfo:: field pack failure\n");
            return -1;
        }
    }
    if(p_MaxGERAN_IsPresent())
    {
        if(0 != p_MaxGERAN_Pack(bits))
        {
            printf("CarrierFreqsInfoGERAN::commonInfo:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != threshX_High.Pack(bits))
        {
            printf("CarrierFreqsInfoGERAN::commonInfo:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != threshX_Low.Pack(bits))
        {
            printf("CarrierFreqsInfoGERAN::commonInfo:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int CarrierFreqsInfoGERAN::commonInfo::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int CarrierFreqsInfoGERAN::commonInfo::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("commonInfo::Unpack() index out of bounds for optional indiator cellReselectionPriority\n");
        return -1;
    }
    cellReselectionPriority_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("commonInfo::Unpack() index out of bounds for optional indiator p_MaxGERAN\n");
        return -1;
    }
    p_MaxGERAN_present = bits[idx++];

    // Fields
    if(cellReselectionPriority_present)
    {
        if(0 != cellReselectionPriority.Unpack(bits, idx))
        {
            printf("CarrierFreqsInfoGERAN::commonInfo:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != ncc_Permitted_Unpack(bits, idx))
        {
            printf("CarrierFreqsInfoGERAN::commonInfo:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != q_RxLevMin_Unpack(bits, idx))
        {
            printf("CarrierFreqsInfoGERAN::commonInfo:: field unpack failure\n");
            return -1;
        }
    }
    if(p_MaxGERAN_present)
    {
        if(0 != p_MaxGERAN_Unpack(bits, idx))
        {
            printf("CarrierFreqsInfoGERAN::commonInfo:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != threshX_High.Unpack(bits, idx))
        {
            printf("CarrierFreqsInfoGERAN::commonInfo:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != threshX_Low.Unpack(bits, idx))
        {
            printf("CarrierFreqsInfoGERAN::commonInfo:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string CarrierFreqsInfoGERAN::commonInfo::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "commonInfo:\n";
    if(cellReselectionPriority_IsPresent())
        out += cellReselectionPriority_ToString(indent+1);
    out += ncc_Permitted_ToString(indent+1);
    out += q_RxLevMin_ToString(indent+1);
    if(p_MaxGERAN_IsPresent())
        out += p_MaxGERAN_ToString(indent+1);
    out += threshX_High_ToString(indent+1);
    out += threshX_Low_ToString(indent+1);
    return out;
}

std::string CarrierFreqsInfoGERAN::commonInfo::ToStringNoNewLines() const
{
    std::string out = "commonInfo:";
    if(cellReselectionPriority_IsPresent())
        out += cellReselectionPriority_ToStringNoNewLines();
    out += ncc_Permitted_ToStringNoNewLines();
    out += q_RxLevMin_ToStringNoNewLines();
    if(p_MaxGERAN_IsPresent())
        out += p_MaxGERAN_ToStringNoNewLines();
    out += threshX_High_ToStringNoNewLines();
    out += threshX_Low_ToStringNoNewLines();
    return out;
}

CellReselectionPriority* CarrierFreqsInfoGERAN::commonInfo::cellReselectionPriority_Set()
{
    cellReselectionPriority_present = true;
    return &cellReselectionPriority;
}

int CarrierFreqsInfoGERAN::commonInfo::cellReselectionPriority_Set(CellReselectionPriority &value)
{
    cellReselectionPriority_present = true;
    cellReselectionPriority = value;
    return 0;
}

const CellReselectionPriority& CarrierFreqsInfoGERAN::commonInfo::cellReselectionPriority_Get() const
{
    return cellReselectionPriority;
}

std::string CarrierFreqsInfoGERAN::commonInfo::cellReselectionPriority_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cellReselectionPriority:\n";
    out += cellReselectionPriority.ToString(indent+1);
    return out;
}

std::string CarrierFreqsInfoGERAN::commonInfo::cellReselectionPriority_ToStringNoNewLines() const
{
    std::string out = "cellReselectionPriority:";
    out += cellReselectionPriority.ToStringNoNewLines();
    return out;
}

int CarrierFreqsInfoGERAN::commonInfo::cellReselectionPriority_Clear()
{
    cellReselectionPriority_present = false;
    return 0;
}

bool CarrierFreqsInfoGERAN::commonInfo::cellReselectionPriority_IsPresent() const
{
    return cellReselectionPriority_present;
}

int CarrierFreqsInfoGERAN::commonInfo::ncc_Permitted_Pack(std::vector<uint8_t> &bits)
{
    if(!ncc_Permitted_present)
    {
        printf("CarrierFreqsInfoGERAN::commonInfo::ncc_Permitted_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 8;
    if(size < 8 || size > 8)
    {
        printf("CarrierFreqsInfoGERAN::commonInfo::ncc_Permitted_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((ncc_Permitted_internal_value >> (8-i-1)) & 1);
    return 0;
}

int CarrierFreqsInfoGERAN::commonInfo::ncc_Permitted_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return ncc_Permitted_Unpack(bits, idx);
}

int CarrierFreqsInfoGERAN::commonInfo::ncc_Permitted_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 8;
    if(size < 8 || size > 8)
    {
        printf("CarrierFreqsInfoGERAN::commonInfo::ncc_Permitted_Unpack() size failure\n");
        return -1;
    }
    ncc_Permitted_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("CarrierFreqsInfoGERAN::commonInfo::ncc_Permitted_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        ncc_Permitted_internal_value |= (uint8_t)bits[idx++] << (uint8_t)(8-i-1);
    ncc_Permitted_present = true;
    return 0;
}

uint8_t CarrierFreqsInfoGERAN::commonInfo::ncc_Permitted_Value() const
{
    if(ncc_Permitted_present)
        return ncc_Permitted_internal_value;
    uint8_t tmp = 0;
    return tmp;
}

int CarrierFreqsInfoGERAN::commonInfo::ncc_Permitted_SetValue(uint8_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 8)
    {
        printf("CarrierFreqsInfoGERAN::commonInfo::ncc_Permitted_SetValue() size failure\n");
        return -1;
    }
    ncc_Permitted_internal_value = value;
    ncc_Permitted_present = true;
    return 0;
}

std::string CarrierFreqsInfoGERAN::commonInfo::ncc_Permitted_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ncc_Permitted = ";
    out += std::to_string(ncc_Permitted_internal_value);
    out += "\n";
    return out;
}

std::string CarrierFreqsInfoGERAN::commonInfo::ncc_Permitted_ToStringNoNewLines() const
{
    std::string out = "ncc_Permitted=";
    out += std::to_string(ncc_Permitted_internal_value);
    out += ",";
    return out;
}

int CarrierFreqsInfoGERAN::commonInfo::ncc_Permitted_Clear()
{
    ncc_Permitted_present = false;
    return 0;
}

bool CarrierFreqsInfoGERAN::commonInfo::ncc_Permitted_IsPresent() const
{
    return ncc_Permitted_present;
}

int CarrierFreqsInfoGERAN::commonInfo::q_RxLevMin_Pack(std::vector<uint8_t> &bits)
{
    if(!q_RxLevMin_present)
    {
        printf("CarrierFreqsInfoGERAN::commonInfo::q_RxLevMin_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = q_RxLevMin_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (45 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int CarrierFreqsInfoGERAN::commonInfo::q_RxLevMin_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return q_RxLevMin_Unpack(bits, idx);
}

int CarrierFreqsInfoGERAN::commonInfo::q_RxLevMin_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (45 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("CarrierFreqsInfoGERAN::commonInfo::q_RxLevMin_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    q_RxLevMin_internal_value = packed_val + 0;
    q_RxLevMin_present = true;
    return 0;
}

int64_t CarrierFreqsInfoGERAN::commonInfo::q_RxLevMin_Value() const
{
    if(q_RxLevMin_present)
        return q_RxLevMin_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int CarrierFreqsInfoGERAN::commonInfo::q_RxLevMin_SetValue(int64_t value)
{
    if(value < 0 || value > 45)
    {
        printf("CarrierFreqsInfoGERAN::commonInfo::q_RxLevMin_SetValue() range failure\n");
        return -1;
    }
    q_RxLevMin_internal_value = value;
    q_RxLevMin_present = true;
    return 0;
}

std::string CarrierFreqsInfoGERAN::commonInfo::q_RxLevMin_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "q_RxLevMin = " + std::to_string(q_RxLevMin_internal_value) + "\n";
    return out;
}

std::string CarrierFreqsInfoGERAN::commonInfo::q_RxLevMin_ToStringNoNewLines() const
{
    std::string out = "q_RxLevMin=" + std::to_string(q_RxLevMin_internal_value) + ",";
    return out;
}

int CarrierFreqsInfoGERAN::commonInfo::q_RxLevMin_Clear()
{
    q_RxLevMin_present = false;
    return 0;
}

bool CarrierFreqsInfoGERAN::commonInfo::q_RxLevMin_IsPresent() const
{
    return q_RxLevMin_present;
}

int CarrierFreqsInfoGERAN::commonInfo::p_MaxGERAN_Pack(std::vector<uint8_t> &bits)
{
    int64_t val_to_pack = p_MaxGERAN_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (39 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int CarrierFreqsInfoGERAN::commonInfo::p_MaxGERAN_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return p_MaxGERAN_Unpack(bits, idx);
}

int CarrierFreqsInfoGERAN::commonInfo::p_MaxGERAN_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (39 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("CarrierFreqsInfoGERAN::commonInfo::p_MaxGERAN_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    p_MaxGERAN_internal_value = packed_val + 0;
    p_MaxGERAN_present = true;
    return 0;
}

int64_t CarrierFreqsInfoGERAN::commonInfo::p_MaxGERAN_Value() const
{
    if(p_MaxGERAN_present)
        return p_MaxGERAN_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int CarrierFreqsInfoGERAN::commonInfo::p_MaxGERAN_SetValue(int64_t value)
{
    if(value < 0 || value > 39)
    {
        printf("CarrierFreqsInfoGERAN::commonInfo::p_MaxGERAN_SetValue() range failure\n");
        return -1;
    }
    p_MaxGERAN_internal_value = value;
    p_MaxGERAN_present = true;
    return 0;
}

std::string CarrierFreqsInfoGERAN::commonInfo::p_MaxGERAN_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "p_MaxGERAN = " + std::to_string(p_MaxGERAN_internal_value) + "\n";
    return out;
}

std::string CarrierFreqsInfoGERAN::commonInfo::p_MaxGERAN_ToStringNoNewLines() const
{
    std::string out = "p_MaxGERAN=" + std::to_string(p_MaxGERAN_internal_value) + ",";
    return out;
}

int CarrierFreqsInfoGERAN::commonInfo::p_MaxGERAN_Clear()
{
    p_MaxGERAN_present = false;
    return 0;
}

bool CarrierFreqsInfoGERAN::commonInfo::p_MaxGERAN_IsPresent() const
{
    return p_MaxGERAN_present;
}

ReselectionThreshold* CarrierFreqsInfoGERAN::commonInfo::threshX_High_Set()
{
    threshX_High_present = true;
    return &threshX_High;
}

int CarrierFreqsInfoGERAN::commonInfo::threshX_High_Set(ReselectionThreshold &value)
{
    threshX_High_present = true;
    threshX_High = value;
    return 0;
}

const ReselectionThreshold& CarrierFreqsInfoGERAN::commonInfo::threshX_High_Get() const
{
    return threshX_High;
}

std::string CarrierFreqsInfoGERAN::commonInfo::threshX_High_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "threshX_High:\n";
    out += threshX_High.ToString(indent+1);
    return out;
}

std::string CarrierFreqsInfoGERAN::commonInfo::threshX_High_ToStringNoNewLines() const
{
    std::string out = "threshX_High:";
    out += threshX_High.ToStringNoNewLines();
    return out;
}

int CarrierFreqsInfoGERAN::commonInfo::threshX_High_Clear()
{
    threshX_High_present = false;
    return 0;
}

bool CarrierFreqsInfoGERAN::commonInfo::threshX_High_IsPresent() const
{
    return threshX_High_present;
}

ReselectionThreshold* CarrierFreqsInfoGERAN::commonInfo::threshX_Low_Set()
{
    threshX_Low_present = true;
    return &threshX_Low;
}

int CarrierFreqsInfoGERAN::commonInfo::threshX_Low_Set(ReselectionThreshold &value)
{
    threshX_Low_present = true;
    threshX_Low = value;
    return 0;
}

const ReselectionThreshold& CarrierFreqsInfoGERAN::commonInfo::threshX_Low_Get() const
{
    return threshX_Low;
}

std::string CarrierFreqsInfoGERAN::commonInfo::threshX_Low_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "threshX_Low:\n";
    out += threshX_Low.ToString(indent+1);
    return out;
}

std::string CarrierFreqsInfoGERAN::commonInfo::threshX_Low_ToStringNoNewLines() const
{
    std::string out = "threshX_Low:";
    out += threshX_Low.ToStringNoNewLines();
    return out;
}

int CarrierFreqsInfoGERAN::commonInfo::threshX_Low_Clear()
{
    threshX_Low_present = false;
    return 0;
}

bool CarrierFreqsInfoGERAN::commonInfo::threshX_Low_IsPresent() const
{
    return threshX_Low_present;
}

