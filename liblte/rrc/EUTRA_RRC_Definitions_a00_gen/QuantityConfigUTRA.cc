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

#include "QuantityConfigUTRA.h"

#include <cmath>

int QuantityConfigUTRA::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    if(!filterCoefficient_IsPresent() || filterCoefficient_Get().Value() == filterCoefficient_GetDefault())
    {
        bits.push_back(0);
    }else{
        bits.push_back(1);
    }

    // Fields
    {
        if(0 != measQuantityUTRA_FDD_Pack(bits))
        {
            printf("QuantityConfigUTRA:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != measQuantityUTRA_TDD_Pack(bits))
        {
            printf("QuantityConfigUTRA:: field pack failure\n");
            return -1;
        }
    }
    if(filterCoefficient_IsPresent() || filterCoefficient_Get().Value() != filterCoefficient_GetDefault())
    {
        if(0 != filterCoefficient.Pack(bits))
        {
            printf("QuantityConfigUTRA:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int QuantityConfigUTRA::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int QuantityConfigUTRA::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("QuantityConfigUTRA::Unpack() index out of bounds for optional indiator filterCoefficient\n");
        return -1;
    }
    filterCoefficient_present = bits[idx++];

    // Fields
    {
        if(0 != measQuantityUTRA_FDD_Unpack(bits, idx))
        {
            printf("QuantityConfigUTRA:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != measQuantityUTRA_TDD_Unpack(bits, idx))
        {
            printf("QuantityConfigUTRA:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != filterCoefficient.Unpack(bits, idx))
        {
            printf("QuantityConfigUTRA:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string QuantityConfigUTRA::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "QuantityConfigUTRA:\n";
    out += measQuantityUTRA_FDD_ToString(indent+1);
    out += measQuantityUTRA_TDD_ToString(indent+1);
    out += filterCoefficient_ToString(indent+1);
    return out;
}

std::string QuantityConfigUTRA::ToStringNoNewLines() const
{
    std::string out = "QuantityConfigUTRA:";
    out += measQuantityUTRA_FDD_ToStringNoNewLines();
    out += measQuantityUTRA_TDD_ToStringNoNewLines();
    out += filterCoefficient_ToStringNoNewLines();
    return out;
}

int QuantityConfigUTRA::measQuantityUTRA_FDD_Pack(std::vector<uint8_t> &bits)
{
    if(!measQuantityUTRA_FDD_present)
    {
        printf("QuantityConfigUTRA::measQuantityUTRA_FDD_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((measQuantityUTRA_FDD_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int QuantityConfigUTRA::measQuantityUTRA_FDD_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return measQuantityUTRA_FDD_Unpack(bits, idx);
}

int QuantityConfigUTRA::measQuantityUTRA_FDD_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("QuantityConfigUTRA::measQuantityUTRA_FDD_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 1)
    {
        printf("QuantityConfigUTRA::measQuantityUTRA_FDD_Unpack() max failure\n");
        return -1;
    }
    measQuantityUTRA_FDD_internal_value = (measQuantityUTRA_FDD_Enum)packed_val;
    measQuantityUTRA_FDD_present = true;
    return 0;
}

QuantityConfigUTRA::measQuantityUTRA_FDD_Enum QuantityConfigUTRA::measQuantityUTRA_FDD_Value() const
{
    if(measQuantityUTRA_FDD_present)
        return measQuantityUTRA_FDD_internal_value;
    return (QuantityConfigUTRA::measQuantityUTRA_FDD_Enum)0;
}

int QuantityConfigUTRA::measQuantityUTRA_FDD_SetValue(measQuantityUTRA_FDD_Enum value)
{
    measQuantityUTRA_FDD_internal_value = value;
    measQuantityUTRA_FDD_present = true;
    return 0;
}

int QuantityConfigUTRA::measQuantityUTRA_FDD_SetValue(std::string value)
{
    if("cpich_RSCP" == value)
    {
        measQuantityUTRA_FDD_internal_value = k_measQuantityUTRA_FDD_cpich_RSCP;
        measQuantityUTRA_FDD_present = true;
        return 0;
    }
    if("cpich_EcN0" == value)
    {
        measQuantityUTRA_FDD_internal_value = k_measQuantityUTRA_FDD_cpich_EcN0;
        measQuantityUTRA_FDD_present = true;
        return 0;
    }
    return 1;
}

std::string QuantityConfigUTRA::measQuantityUTRA_FDD_ValueToString(measQuantityUTRA_FDD_Enum value) const
{
    if(k_measQuantityUTRA_FDD_cpich_RSCP == value)
        return "cpich_RSCP";
    if(k_measQuantityUTRA_FDD_cpich_EcN0 == value)
        return "cpich_EcN0";
    return "";
}

uint64_t QuantityConfigUTRA::measQuantityUTRA_FDD_NumberOfValues() const
{
    return 2;
}

std::string QuantityConfigUTRA::measQuantityUTRA_FDD_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "measQuantityUTRA_FDD = " + measQuantityUTRA_FDD_ValueToString(measQuantityUTRA_FDD_internal_value) + "\n";
    return out;
}

std::string QuantityConfigUTRA::measQuantityUTRA_FDD_ToStringNoNewLines() const
{
    std::string out = "measQuantityUTRA_FDD=" + measQuantityUTRA_FDD_ValueToString(measQuantityUTRA_FDD_internal_value) + ",";
    return out;
}

int QuantityConfigUTRA::measQuantityUTRA_FDD_Clear()
{
    measQuantityUTRA_FDD_present = false;
    return 0;
}

bool QuantityConfigUTRA::measQuantityUTRA_FDD_IsPresent() const
{
    return measQuantityUTRA_FDD_present;
}

int QuantityConfigUTRA::measQuantityUTRA_TDD_Pack(std::vector<uint8_t> &bits)
{
    if(!measQuantityUTRA_TDD_present)
    {
        printf("QuantityConfigUTRA::measQuantityUTRA_TDD_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((measQuantityUTRA_TDD_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int QuantityConfigUTRA::measQuantityUTRA_TDD_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return measQuantityUTRA_TDD_Unpack(bits, idx);
}

int QuantityConfigUTRA::measQuantityUTRA_TDD_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("QuantityConfigUTRA::measQuantityUTRA_TDD_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 0)
    {
        printf("QuantityConfigUTRA::measQuantityUTRA_TDD_Unpack() max failure\n");
        return -1;
    }
    measQuantityUTRA_TDD_internal_value = (measQuantityUTRA_TDD_Enum)packed_val;
    measQuantityUTRA_TDD_present = true;
    return 0;
}

QuantityConfigUTRA::measQuantityUTRA_TDD_Enum QuantityConfigUTRA::measQuantityUTRA_TDD_Value() const
{
    if(measQuantityUTRA_TDD_present)
        return measQuantityUTRA_TDD_internal_value;
    return (QuantityConfigUTRA::measQuantityUTRA_TDD_Enum)0;
}

int QuantityConfigUTRA::measQuantityUTRA_TDD_SetValue(measQuantityUTRA_TDD_Enum value)
{
    measQuantityUTRA_TDD_internal_value = value;
    measQuantityUTRA_TDD_present = true;
    return 0;
}

int QuantityConfigUTRA::measQuantityUTRA_TDD_SetValue(std::string value)
{
    if("pccpch_RSCP" == value)
    {
        measQuantityUTRA_TDD_internal_value = k_measQuantityUTRA_TDD_pccpch_RSCP;
        measQuantityUTRA_TDD_present = true;
        return 0;
    }
    return 1;
}

std::string QuantityConfigUTRA::measQuantityUTRA_TDD_ValueToString(measQuantityUTRA_TDD_Enum value) const
{
    if(k_measQuantityUTRA_TDD_pccpch_RSCP == value)
        return "pccpch_RSCP";
    return "";
}

uint64_t QuantityConfigUTRA::measQuantityUTRA_TDD_NumberOfValues() const
{
    return 1;
}

std::string QuantityConfigUTRA::measQuantityUTRA_TDD_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "measQuantityUTRA_TDD = " + measQuantityUTRA_TDD_ValueToString(measQuantityUTRA_TDD_internal_value) + "\n";
    return out;
}

std::string QuantityConfigUTRA::measQuantityUTRA_TDD_ToStringNoNewLines() const
{
    std::string out = "measQuantityUTRA_TDD=" + measQuantityUTRA_TDD_ValueToString(measQuantityUTRA_TDD_internal_value) + ",";
    return out;
}

int QuantityConfigUTRA::measQuantityUTRA_TDD_Clear()
{
    measQuantityUTRA_TDD_present = false;
    return 0;
}

bool QuantityConfigUTRA::measQuantityUTRA_TDD_IsPresent() const
{
    return measQuantityUTRA_TDD_present;
}

FilterCoefficient* QuantityConfigUTRA::filterCoefficient_Set()
{
    filterCoefficient_present = true;
    return &filterCoefficient;
}

int QuantityConfigUTRA::filterCoefficient_Set(FilterCoefficient &value)
{
    filterCoefficient_present = true;
    filterCoefficient = value;
    return 0;
}

const FilterCoefficient& QuantityConfigUTRA::filterCoefficient_Get() const
{
    return filterCoefficient;
}

FilterCoefficient::Enum QuantityConfigUTRA::filterCoefficient_GetDefault() const
{
    return FilterCoefficient::k_fc4;
}

std::string QuantityConfigUTRA::filterCoefficient_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "filterCoefficient:\n";
    out += filterCoefficient.ToString(indent+1);
    return out;
}

std::string QuantityConfigUTRA::filterCoefficient_ToStringNoNewLines() const
{
    std::string out = "filterCoefficient:";
    out += filterCoefficient.ToStringNoNewLines();
    return out;
}

int QuantityConfigUTRA::filterCoefficient_Clear()
{
    filterCoefficient_present = false;
    return 0;
}

bool QuantityConfigUTRA::filterCoefficient_IsPresent() const
{
    return filterCoefficient_present;
}

