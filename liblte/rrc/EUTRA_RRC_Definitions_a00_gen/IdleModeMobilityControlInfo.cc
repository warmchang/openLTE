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

#include "IdleModeMobilityControlInfo.h"

#include <cmath>

int IdleModeMobilityControlInfo::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator
    bits.push_back(0);

    // Optional indicators
    bits.push_back(freqPriorityListEUTRA_IsPresent());
    bits.push_back(freqPriorityListGERAN_IsPresent());
    bits.push_back(freqPriorityListUTRA_FDD_IsPresent());
    bits.push_back(freqPriorityListUTRA_TDD_IsPresent());
    bits.push_back(bandClassPriorityListHRPD_IsPresent());
    bits.push_back(bandClassPriorityList1XRTT_IsPresent());
    bits.push_back(t320_IsPresent());

    // Fields
    if(freqPriorityListEUTRA_IsPresent())
    {
        if(0 != freqPriorityListEUTRA.Pack(bits))
        {
            printf("IdleModeMobilityControlInfo:: field pack failure\n");
            return -1;
        }
    }
    if(freqPriorityListGERAN_IsPresent())
    {
        if(0 != freqPriorityListGERAN.Pack(bits))
        {
            printf("IdleModeMobilityControlInfo:: field pack failure\n");
            return -1;
        }
    }
    if(freqPriorityListUTRA_FDD_IsPresent())
    {
        if(0 != freqPriorityListUTRA_FDD.Pack(bits))
        {
            printf("IdleModeMobilityControlInfo:: field pack failure\n");
            return -1;
        }
    }
    if(freqPriorityListUTRA_TDD_IsPresent())
    {
        if(0 != freqPriorityListUTRA_TDD.Pack(bits))
        {
            printf("IdleModeMobilityControlInfo:: field pack failure\n");
            return -1;
        }
    }
    if(bandClassPriorityListHRPD_IsPresent())
    {
        if(0 != bandClassPriorityListHRPD.Pack(bits))
        {
            printf("IdleModeMobilityControlInfo:: field pack failure\n");
            return -1;
        }
    }
    if(bandClassPriorityList1XRTT_IsPresent())
    {
        if(0 != bandClassPriorityList1XRTT.Pack(bits))
        {
            printf("IdleModeMobilityControlInfo:: field pack failure\n");
            return -1;
        }
    }
    if(t320_IsPresent())
    {
        if(0 != t320_Pack(bits))
        {
            printf("IdleModeMobilityControlInfo:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int IdleModeMobilityControlInfo::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int IdleModeMobilityControlInfo::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("IdleModeMobilityControlInfo::Unpack() index out of bounds for extension\n");
        return -1;
    }
    idx++;

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("IdleModeMobilityControlInfo::Unpack() index out of bounds for optional indiator freqPriorityListEUTRA\n");
        return -1;
    }
    freqPriorityListEUTRA_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("IdleModeMobilityControlInfo::Unpack() index out of bounds for optional indiator freqPriorityListGERAN\n");
        return -1;
    }
    freqPriorityListGERAN_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("IdleModeMobilityControlInfo::Unpack() index out of bounds for optional indiator freqPriorityListUTRA_FDD\n");
        return -1;
    }
    freqPriorityListUTRA_FDD_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("IdleModeMobilityControlInfo::Unpack() index out of bounds for optional indiator freqPriorityListUTRA_TDD\n");
        return -1;
    }
    freqPriorityListUTRA_TDD_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("IdleModeMobilityControlInfo::Unpack() index out of bounds for optional indiator bandClassPriorityListHRPD\n");
        return -1;
    }
    bandClassPriorityListHRPD_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("IdleModeMobilityControlInfo::Unpack() index out of bounds for optional indiator bandClassPriorityList1XRTT\n");
        return -1;
    }
    bandClassPriorityList1XRTT_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("IdleModeMobilityControlInfo::Unpack() index out of bounds for optional indiator t320\n");
        return -1;
    }
    t320_present = bits[idx++];

    // Fields
    if(freqPriorityListEUTRA_present)
    {
        if(0 != freqPriorityListEUTRA.Unpack(bits, idx))
        {
            printf("IdleModeMobilityControlInfo:: field unpack failure\n");
            return -1;
        }
    }
    if(freqPriorityListGERAN_present)
    {
        if(0 != freqPriorityListGERAN.Unpack(bits, idx))
        {
            printf("IdleModeMobilityControlInfo:: field unpack failure\n");
            return -1;
        }
    }
    if(freqPriorityListUTRA_FDD_present)
    {
        if(0 != freqPriorityListUTRA_FDD.Unpack(bits, idx))
        {
            printf("IdleModeMobilityControlInfo:: field unpack failure\n");
            return -1;
        }
    }
    if(freqPriorityListUTRA_TDD_present)
    {
        if(0 != freqPriorityListUTRA_TDD.Unpack(bits, idx))
        {
            printf("IdleModeMobilityControlInfo:: field unpack failure\n");
            return -1;
        }
    }
    if(bandClassPriorityListHRPD_present)
    {
        if(0 != bandClassPriorityListHRPD.Unpack(bits, idx))
        {
            printf("IdleModeMobilityControlInfo:: field unpack failure\n");
            return -1;
        }
    }
    if(bandClassPriorityList1XRTT_present)
    {
        if(0 != bandClassPriorityList1XRTT.Unpack(bits, idx))
        {
            printf("IdleModeMobilityControlInfo:: field unpack failure\n");
            return -1;
        }
    }
    if(t320_present)
    {
        if(0 != t320_Unpack(bits, idx))
        {
            printf("IdleModeMobilityControlInfo:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string IdleModeMobilityControlInfo::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "IdleModeMobilityControlInfo:\n";
    if(freqPriorityListEUTRA_IsPresent())
        out += freqPriorityListEUTRA_ToString(indent+1);
    if(freqPriorityListGERAN_IsPresent())
        out += freqPriorityListGERAN_ToString(indent+1);
    if(freqPriorityListUTRA_FDD_IsPresent())
        out += freqPriorityListUTRA_FDD_ToString(indent+1);
    if(freqPriorityListUTRA_TDD_IsPresent())
        out += freqPriorityListUTRA_TDD_ToString(indent+1);
    if(bandClassPriorityListHRPD_IsPresent())
        out += bandClassPriorityListHRPD_ToString(indent+1);
    if(bandClassPriorityList1XRTT_IsPresent())
        out += bandClassPriorityList1XRTT_ToString(indent+1);
    if(t320_IsPresent())
        out += t320_ToString(indent+1);
    return out;
}

std::string IdleModeMobilityControlInfo::ToStringNoNewLines() const
{
    std::string out = "IdleModeMobilityControlInfo:";
    if(freqPriorityListEUTRA_IsPresent())
        out += freqPriorityListEUTRA_ToStringNoNewLines();
    if(freqPriorityListGERAN_IsPresent())
        out += freqPriorityListGERAN_ToStringNoNewLines();
    if(freqPriorityListUTRA_FDD_IsPresent())
        out += freqPriorityListUTRA_FDD_ToStringNoNewLines();
    if(freqPriorityListUTRA_TDD_IsPresent())
        out += freqPriorityListUTRA_TDD_ToStringNoNewLines();
    if(bandClassPriorityListHRPD_IsPresent())
        out += bandClassPriorityListHRPD_ToStringNoNewLines();
    if(bandClassPriorityList1XRTT_IsPresent())
        out += bandClassPriorityList1XRTT_ToStringNoNewLines();
    if(t320_IsPresent())
        out += t320_ToStringNoNewLines();
    return out;
}

FreqPriorityListEUTRA* IdleModeMobilityControlInfo::freqPriorityListEUTRA_Set()
{
    freqPriorityListEUTRA_present = true;
    return &freqPriorityListEUTRA;
}

int IdleModeMobilityControlInfo::freqPriorityListEUTRA_Set(FreqPriorityListEUTRA &value)
{
    freqPriorityListEUTRA_present = true;
    freqPriorityListEUTRA = value;
    return 0;
}

const FreqPriorityListEUTRA& IdleModeMobilityControlInfo::freqPriorityListEUTRA_Get() const
{
    return freqPriorityListEUTRA;
}

std::string IdleModeMobilityControlInfo::freqPriorityListEUTRA_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "freqPriorityListEUTRA:\n";
    out += freqPriorityListEUTRA.ToString(indent+1);
    return out;
}

std::string IdleModeMobilityControlInfo::freqPriorityListEUTRA_ToStringNoNewLines() const
{
    std::string out = "freqPriorityListEUTRA:";
    out += freqPriorityListEUTRA.ToStringNoNewLines();
    return out;
}

int IdleModeMobilityControlInfo::freqPriorityListEUTRA_Clear()
{
    freqPriorityListEUTRA_present = false;
    return 0;
}

bool IdleModeMobilityControlInfo::freqPriorityListEUTRA_IsPresent() const
{
    return freqPriorityListEUTRA_present;
}

FreqsPriorityListGERAN* IdleModeMobilityControlInfo::freqPriorityListGERAN_Set()
{
    freqPriorityListGERAN_present = true;
    return &freqPriorityListGERAN;
}

int IdleModeMobilityControlInfo::freqPriorityListGERAN_Set(FreqsPriorityListGERAN &value)
{
    freqPriorityListGERAN_present = true;
    freqPriorityListGERAN = value;
    return 0;
}

const FreqsPriorityListGERAN& IdleModeMobilityControlInfo::freqPriorityListGERAN_Get() const
{
    return freqPriorityListGERAN;
}

std::string IdleModeMobilityControlInfo::freqPriorityListGERAN_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "freqPriorityListGERAN:\n";
    out += freqPriorityListGERAN.ToString(indent+1);
    return out;
}

std::string IdleModeMobilityControlInfo::freqPriorityListGERAN_ToStringNoNewLines() const
{
    std::string out = "freqPriorityListGERAN:";
    out += freqPriorityListGERAN.ToStringNoNewLines();
    return out;
}

int IdleModeMobilityControlInfo::freqPriorityListGERAN_Clear()
{
    freqPriorityListGERAN_present = false;
    return 0;
}

bool IdleModeMobilityControlInfo::freqPriorityListGERAN_IsPresent() const
{
    return freqPriorityListGERAN_present;
}

FreqPriorityListUTRA_FDD* IdleModeMobilityControlInfo::freqPriorityListUTRA_FDD_Set()
{
    freqPriorityListUTRA_FDD_present = true;
    return &freqPriorityListUTRA_FDD;
}

int IdleModeMobilityControlInfo::freqPriorityListUTRA_FDD_Set(FreqPriorityListUTRA_FDD &value)
{
    freqPriorityListUTRA_FDD_present = true;
    freqPriorityListUTRA_FDD = value;
    return 0;
}

const FreqPriorityListUTRA_FDD& IdleModeMobilityControlInfo::freqPriorityListUTRA_FDD_Get() const
{
    return freqPriorityListUTRA_FDD;
}

std::string IdleModeMobilityControlInfo::freqPriorityListUTRA_FDD_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "freqPriorityListUTRA_FDD:\n";
    out += freqPriorityListUTRA_FDD.ToString(indent+1);
    return out;
}

std::string IdleModeMobilityControlInfo::freqPriorityListUTRA_FDD_ToStringNoNewLines() const
{
    std::string out = "freqPriorityListUTRA_FDD:";
    out += freqPriorityListUTRA_FDD.ToStringNoNewLines();
    return out;
}

int IdleModeMobilityControlInfo::freqPriorityListUTRA_FDD_Clear()
{
    freqPriorityListUTRA_FDD_present = false;
    return 0;
}

bool IdleModeMobilityControlInfo::freqPriorityListUTRA_FDD_IsPresent() const
{
    return freqPriorityListUTRA_FDD_present;
}

FreqPriorityListUTRA_TDD* IdleModeMobilityControlInfo::freqPriorityListUTRA_TDD_Set()
{
    freqPriorityListUTRA_TDD_present = true;
    return &freqPriorityListUTRA_TDD;
}

int IdleModeMobilityControlInfo::freqPriorityListUTRA_TDD_Set(FreqPriorityListUTRA_TDD &value)
{
    freqPriorityListUTRA_TDD_present = true;
    freqPriorityListUTRA_TDD = value;
    return 0;
}

const FreqPriorityListUTRA_TDD& IdleModeMobilityControlInfo::freqPriorityListUTRA_TDD_Get() const
{
    return freqPriorityListUTRA_TDD;
}

std::string IdleModeMobilityControlInfo::freqPriorityListUTRA_TDD_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "freqPriorityListUTRA_TDD:\n";
    out += freqPriorityListUTRA_TDD.ToString(indent+1);
    return out;
}

std::string IdleModeMobilityControlInfo::freqPriorityListUTRA_TDD_ToStringNoNewLines() const
{
    std::string out = "freqPriorityListUTRA_TDD:";
    out += freqPriorityListUTRA_TDD.ToStringNoNewLines();
    return out;
}

int IdleModeMobilityControlInfo::freqPriorityListUTRA_TDD_Clear()
{
    freqPriorityListUTRA_TDD_present = false;
    return 0;
}

bool IdleModeMobilityControlInfo::freqPriorityListUTRA_TDD_IsPresent() const
{
    return freqPriorityListUTRA_TDD_present;
}

BandClassPriorityListHRPD* IdleModeMobilityControlInfo::bandClassPriorityListHRPD_Set()
{
    bandClassPriorityListHRPD_present = true;
    return &bandClassPriorityListHRPD;
}

int IdleModeMobilityControlInfo::bandClassPriorityListHRPD_Set(BandClassPriorityListHRPD &value)
{
    bandClassPriorityListHRPD_present = true;
    bandClassPriorityListHRPD = value;
    return 0;
}

const BandClassPriorityListHRPD& IdleModeMobilityControlInfo::bandClassPriorityListHRPD_Get() const
{
    return bandClassPriorityListHRPD;
}

std::string IdleModeMobilityControlInfo::bandClassPriorityListHRPD_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "bandClassPriorityListHRPD:\n";
    out += bandClassPriorityListHRPD.ToString(indent+1);
    return out;
}

std::string IdleModeMobilityControlInfo::bandClassPriorityListHRPD_ToStringNoNewLines() const
{
    std::string out = "bandClassPriorityListHRPD:";
    out += bandClassPriorityListHRPD.ToStringNoNewLines();
    return out;
}

int IdleModeMobilityControlInfo::bandClassPriorityListHRPD_Clear()
{
    bandClassPriorityListHRPD_present = false;
    return 0;
}

bool IdleModeMobilityControlInfo::bandClassPriorityListHRPD_IsPresent() const
{
    return bandClassPriorityListHRPD_present;
}

BandClassPriorityList1XRTT* IdleModeMobilityControlInfo::bandClassPriorityList1XRTT_Set()
{
    bandClassPriorityList1XRTT_present = true;
    return &bandClassPriorityList1XRTT;
}

int IdleModeMobilityControlInfo::bandClassPriorityList1XRTT_Set(BandClassPriorityList1XRTT &value)
{
    bandClassPriorityList1XRTT_present = true;
    bandClassPriorityList1XRTT = value;
    return 0;
}

const BandClassPriorityList1XRTT& IdleModeMobilityControlInfo::bandClassPriorityList1XRTT_Get() const
{
    return bandClassPriorityList1XRTT;
}

std::string IdleModeMobilityControlInfo::bandClassPriorityList1XRTT_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "bandClassPriorityList1XRTT:\n";
    out += bandClassPriorityList1XRTT.ToString(indent+1);
    return out;
}

std::string IdleModeMobilityControlInfo::bandClassPriorityList1XRTT_ToStringNoNewLines() const
{
    std::string out = "bandClassPriorityList1XRTT:";
    out += bandClassPriorityList1XRTT.ToStringNoNewLines();
    return out;
}

int IdleModeMobilityControlInfo::bandClassPriorityList1XRTT_Clear()
{
    bandClassPriorityList1XRTT_present = false;
    return 0;
}

bool IdleModeMobilityControlInfo::bandClassPriorityList1XRTT_IsPresent() const
{
    return bandClassPriorityList1XRTT_present;
}

int IdleModeMobilityControlInfo::t320_Pack(std::vector<uint8_t> &bits)
{
    uint32_t N_bits = 3;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((t320_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int IdleModeMobilityControlInfo::t320_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return t320_Unpack(bits, idx);
}

int IdleModeMobilityControlInfo::t320_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 3;
    if((idx + N_bits) > bits.size())
    {
        printf("IdleModeMobilityControlInfo::t320_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 7)
    {
        printf("IdleModeMobilityControlInfo::t320_Unpack() max failure\n");
        return -1;
    }
    t320_internal_value = (t320_Enum)packed_val;
    t320_present = true;
    return 0;
}

IdleModeMobilityControlInfo::t320_Enum IdleModeMobilityControlInfo::t320_Value() const
{
    if(t320_present)
        return t320_internal_value;
    return (IdleModeMobilityControlInfo::t320_Enum)0;
}

int IdleModeMobilityControlInfo::t320_SetValue(t320_Enum value)
{
    t320_internal_value = value;
    t320_present = true;
    return 0;
}

int IdleModeMobilityControlInfo::t320_SetValue(std::string value)
{
    if("min5" == value)
    {
        t320_internal_value = k_t320_min5;
        t320_present = true;
        return 0;
    }
    if("min10" == value)
    {
        t320_internal_value = k_t320_min10;
        t320_present = true;
        return 0;
    }
    if("min20" == value)
    {
        t320_internal_value = k_t320_min20;
        t320_present = true;
        return 0;
    }
    if("min30" == value)
    {
        t320_internal_value = k_t320_min30;
        t320_present = true;
        return 0;
    }
    if("min60" == value)
    {
        t320_internal_value = k_t320_min60;
        t320_present = true;
        return 0;
    }
    if("min120" == value)
    {
        t320_internal_value = k_t320_min120;
        t320_present = true;
        return 0;
    }
    if("min180" == value)
    {
        t320_internal_value = k_t320_min180;
        t320_present = true;
        return 0;
    }
    if("spare1" == value)
    {
        t320_internal_value = k_t320_spare1;
        t320_present = true;
        return 0;
    }
    return 1;
}

std::string IdleModeMobilityControlInfo::t320_ValueToString(t320_Enum value) const
{
    if(k_t320_min5 == value)
        return "min5";
    if(k_t320_min10 == value)
        return "min10";
    if(k_t320_min20 == value)
        return "min20";
    if(k_t320_min30 == value)
        return "min30";
    if(k_t320_min60 == value)
        return "min60";
    if(k_t320_min120 == value)
        return "min120";
    if(k_t320_min180 == value)
        return "min180";
    if(k_t320_spare1 == value)
        return "spare1";
    return "";
}

uint64_t IdleModeMobilityControlInfo::t320_NumberOfValues() const
{
    return 8;
}

std::string IdleModeMobilityControlInfo::t320_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "t320 = " + t320_ValueToString(t320_internal_value) + "\n";
    return out;
}

std::string IdleModeMobilityControlInfo::t320_ToStringNoNewLines() const
{
    std::string out = "t320=" + t320_ValueToString(t320_internal_value) + ",";
    return out;
}

int IdleModeMobilityControlInfo::t320_Clear()
{
    t320_present = false;
    return 0;
}

bool IdleModeMobilityControlInfo::t320_IsPresent() const
{
    return t320_present;
}

