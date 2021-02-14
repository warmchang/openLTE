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

#include "SecurityAlgorithmConfig.h"

#include <cmath>

int SecurityAlgorithmConfig::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != cipheringAlgorithm_Pack(bits))
        {
            printf("SecurityAlgorithmConfig:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != integrityProtAlgorithm_Pack(bits))
        {
            printf("SecurityAlgorithmConfig:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int SecurityAlgorithmConfig::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int SecurityAlgorithmConfig::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != cipheringAlgorithm_Unpack(bits, idx))
        {
            printf("SecurityAlgorithmConfig:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != integrityProtAlgorithm_Unpack(bits, idx))
        {
            printf("SecurityAlgorithmConfig:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string SecurityAlgorithmConfig::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "SecurityAlgorithmConfig:\n";
    out += cipheringAlgorithm_ToString(indent+1);
    out += integrityProtAlgorithm_ToString(indent+1);
    return out;
}

std::string SecurityAlgorithmConfig::ToStringNoNewLines() const
{
    std::string out = "SecurityAlgorithmConfig:";
    out += cipheringAlgorithm_ToStringNoNewLines();
    out += integrityProtAlgorithm_ToStringNoNewLines();
    return out;
}

int SecurityAlgorithmConfig::cipheringAlgorithm_Pack(std::vector<uint8_t> &bits)
{
    if(!cipheringAlgorithm_present)
    {
        printf("SecurityAlgorithmConfig::cipheringAlgorithm_Pack() presence failure\n");
        return -1;
    }
    if(cipheringAlgorithm_internal_value > k_cipheringAlgorithm_spare1)
    {
        bits.push_back(1);
    }else{
        bits.push_back(0);
    }
    uint32_t N_bits = 3;
    if(cipheringAlgorithm_internal_value > k_cipheringAlgorithm_spare1)
        N_bits = 0;
    for(uint32_t i=0; i<N_bits; i++)
    {
        if(cipheringAlgorithm_internal_value > k_cipheringAlgorithm_spare1)
        {
            bits.push_back(((cipheringAlgorithm_internal_value - k_cipheringAlgorithm_spare1) >> (N_bits-1-i)) & 1);
        }else{
            bits.push_back((cipheringAlgorithm_internal_value >> (N_bits-1-i)) & 1);
        }
    }
    return 0;
}

int SecurityAlgorithmConfig::cipheringAlgorithm_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return cipheringAlgorithm_Unpack(bits, idx);
}

int SecurityAlgorithmConfig::cipheringAlgorithm_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    if((idx + 1) > bits.size())
    {
        printf("SecurityAlgorithmConfig::cipheringAlgorithm_Unpack() index out of bounds for extension\n");
        return -1;
    }
    bool has_extension = bits[idx++];
    uint32_t packed_val = 0;
    uint32_t N_bits = 3;
    if(has_extension)
        N_bits = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("SecurityAlgorithmConfig::cipheringAlgorithm_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(has_extension)
    {
        cipheringAlgorithm_internal_value = (cipheringAlgorithm_Enum)(packed_val + 8);
    }else{
        if(packed_val > 7)
        {
            printf("SecurityAlgorithmConfig::cipheringAlgorithm_Unpack() max failure\n");
            return -1;
        }
        cipheringAlgorithm_internal_value = (cipheringAlgorithm_Enum)packed_val;
    }
    cipheringAlgorithm_present = true;
    return 0;
}

SecurityAlgorithmConfig::cipheringAlgorithm_Enum SecurityAlgorithmConfig::cipheringAlgorithm_Value() const
{
    if(cipheringAlgorithm_present)
        return cipheringAlgorithm_internal_value;
    return (SecurityAlgorithmConfig::cipheringAlgorithm_Enum)0;
}

int SecurityAlgorithmConfig::cipheringAlgorithm_SetValue(cipheringAlgorithm_Enum value)
{
    cipheringAlgorithm_internal_value = value;
    cipheringAlgorithm_present = true;
    return 0;
}

int SecurityAlgorithmConfig::cipheringAlgorithm_SetValue(std::string value)
{
    if("eea0" == value)
    {
        cipheringAlgorithm_internal_value = k_cipheringAlgorithm_eea0;
        cipheringAlgorithm_present = true;
        return 0;
    }
    if("eea1" == value)
    {
        cipheringAlgorithm_internal_value = k_cipheringAlgorithm_eea1;
        cipheringAlgorithm_present = true;
        return 0;
    }
    if("eea2" == value)
    {
        cipheringAlgorithm_internal_value = k_cipheringAlgorithm_eea2;
        cipheringAlgorithm_present = true;
        return 0;
    }
    if("spare5" == value)
    {
        cipheringAlgorithm_internal_value = k_cipheringAlgorithm_spare5;
        cipheringAlgorithm_present = true;
        return 0;
    }
    if("spare4" == value)
    {
        cipheringAlgorithm_internal_value = k_cipheringAlgorithm_spare4;
        cipheringAlgorithm_present = true;
        return 0;
    }
    if("spare3" == value)
    {
        cipheringAlgorithm_internal_value = k_cipheringAlgorithm_spare3;
        cipheringAlgorithm_present = true;
        return 0;
    }
    if("spare2" == value)
    {
        cipheringAlgorithm_internal_value = k_cipheringAlgorithm_spare2;
        cipheringAlgorithm_present = true;
        return 0;
    }
    if("spare1" == value)
    {
        cipheringAlgorithm_internal_value = k_cipheringAlgorithm_spare1;
        cipheringAlgorithm_present = true;
        return 0;
    }
    return 1;
}

std::string SecurityAlgorithmConfig::cipheringAlgorithm_ValueToString(cipheringAlgorithm_Enum value) const
{
    if(k_cipheringAlgorithm_eea0 == value)
        return "eea0";
    if(k_cipheringAlgorithm_eea1 == value)
        return "eea1";
    if(k_cipheringAlgorithm_eea2 == value)
        return "eea2";
    if(k_cipheringAlgorithm_spare5 == value)
        return "spare5";
    if(k_cipheringAlgorithm_spare4 == value)
        return "spare4";
    if(k_cipheringAlgorithm_spare3 == value)
        return "spare3";
    if(k_cipheringAlgorithm_spare2 == value)
        return "spare2";
    if(k_cipheringAlgorithm_spare1 == value)
        return "spare1";
    return "";
}

uint64_t SecurityAlgorithmConfig::cipheringAlgorithm_NumberOfValues() const
{
    return 8;
}

std::string SecurityAlgorithmConfig::cipheringAlgorithm_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cipheringAlgorithm = " + cipheringAlgorithm_ValueToString(cipheringAlgorithm_internal_value) + "\n";
    return out;
}

std::string SecurityAlgorithmConfig::cipheringAlgorithm_ToStringNoNewLines() const
{
    std::string out = "cipheringAlgorithm=" + cipheringAlgorithm_ValueToString(cipheringAlgorithm_internal_value) + ",";
    return out;
}

int SecurityAlgorithmConfig::cipheringAlgorithm_Clear()
{
    cipheringAlgorithm_present = false;
    return 0;
}

bool SecurityAlgorithmConfig::cipheringAlgorithm_IsPresent() const
{
    return cipheringAlgorithm_present;
}

int SecurityAlgorithmConfig::integrityProtAlgorithm_Pack(std::vector<uint8_t> &bits)
{
    if(!integrityProtAlgorithm_present)
    {
        printf("SecurityAlgorithmConfig::integrityProtAlgorithm_Pack() presence failure\n");
        return -1;
    }
    if(integrityProtAlgorithm_internal_value > k_integrityProtAlgorithm_spare1)
    {
        bits.push_back(1);
    }else{
        bits.push_back(0);
    }
    uint32_t N_bits = 3;
    if(integrityProtAlgorithm_internal_value > k_integrityProtAlgorithm_spare1)
        N_bits = 0;
    for(uint32_t i=0; i<N_bits; i++)
    {
        if(integrityProtAlgorithm_internal_value > k_integrityProtAlgorithm_spare1)
        {
            bits.push_back(((integrityProtAlgorithm_internal_value - k_integrityProtAlgorithm_spare1) >> (N_bits-1-i)) & 1);
        }else{
            bits.push_back((integrityProtAlgorithm_internal_value >> (N_bits-1-i)) & 1);
        }
    }
    return 0;
}

int SecurityAlgorithmConfig::integrityProtAlgorithm_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return integrityProtAlgorithm_Unpack(bits, idx);
}

int SecurityAlgorithmConfig::integrityProtAlgorithm_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    if((idx + 1) > bits.size())
    {
        printf("SecurityAlgorithmConfig::integrityProtAlgorithm_Unpack() index out of bounds for extension\n");
        return -1;
    }
    bool has_extension = bits[idx++];
    uint32_t packed_val = 0;
    uint32_t N_bits = 3;
    if(has_extension)
        N_bits = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("SecurityAlgorithmConfig::integrityProtAlgorithm_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(has_extension)
    {
        integrityProtAlgorithm_internal_value = (integrityProtAlgorithm_Enum)(packed_val + 8);
    }else{
        if(packed_val > 7)
        {
            printf("SecurityAlgorithmConfig::integrityProtAlgorithm_Unpack() max failure\n");
            return -1;
        }
        integrityProtAlgorithm_internal_value = (integrityProtAlgorithm_Enum)packed_val;
    }
    integrityProtAlgorithm_present = true;
    return 0;
}

SecurityAlgorithmConfig::integrityProtAlgorithm_Enum SecurityAlgorithmConfig::integrityProtAlgorithm_Value() const
{
    if(integrityProtAlgorithm_present)
        return integrityProtAlgorithm_internal_value;
    return (SecurityAlgorithmConfig::integrityProtAlgorithm_Enum)0;
}

int SecurityAlgorithmConfig::integrityProtAlgorithm_SetValue(integrityProtAlgorithm_Enum value)
{
    integrityProtAlgorithm_internal_value = value;
    integrityProtAlgorithm_present = true;
    return 0;
}

int SecurityAlgorithmConfig::integrityProtAlgorithm_SetValue(std::string value)
{
    if("eia0_v920" == value)
    {
        integrityProtAlgorithm_internal_value = k_integrityProtAlgorithm_eia0_v920;
        integrityProtAlgorithm_present = true;
        return 0;
    }
    if("eia1" == value)
    {
        integrityProtAlgorithm_internal_value = k_integrityProtAlgorithm_eia1;
        integrityProtAlgorithm_present = true;
        return 0;
    }
    if("eia2" == value)
    {
        integrityProtAlgorithm_internal_value = k_integrityProtAlgorithm_eia2;
        integrityProtAlgorithm_present = true;
        return 0;
    }
    if("spare5" == value)
    {
        integrityProtAlgorithm_internal_value = k_integrityProtAlgorithm_spare5;
        integrityProtAlgorithm_present = true;
        return 0;
    }
    if("spare4" == value)
    {
        integrityProtAlgorithm_internal_value = k_integrityProtAlgorithm_spare4;
        integrityProtAlgorithm_present = true;
        return 0;
    }
    if("spare3" == value)
    {
        integrityProtAlgorithm_internal_value = k_integrityProtAlgorithm_spare3;
        integrityProtAlgorithm_present = true;
        return 0;
    }
    if("spare2" == value)
    {
        integrityProtAlgorithm_internal_value = k_integrityProtAlgorithm_spare2;
        integrityProtAlgorithm_present = true;
        return 0;
    }
    if("spare1" == value)
    {
        integrityProtAlgorithm_internal_value = k_integrityProtAlgorithm_spare1;
        integrityProtAlgorithm_present = true;
        return 0;
    }
    return 1;
}

std::string SecurityAlgorithmConfig::integrityProtAlgorithm_ValueToString(integrityProtAlgorithm_Enum value) const
{
    if(k_integrityProtAlgorithm_eia0_v920 == value)
        return "eia0_v920";
    if(k_integrityProtAlgorithm_eia1 == value)
        return "eia1";
    if(k_integrityProtAlgorithm_eia2 == value)
        return "eia2";
    if(k_integrityProtAlgorithm_spare5 == value)
        return "spare5";
    if(k_integrityProtAlgorithm_spare4 == value)
        return "spare4";
    if(k_integrityProtAlgorithm_spare3 == value)
        return "spare3";
    if(k_integrityProtAlgorithm_spare2 == value)
        return "spare2";
    if(k_integrityProtAlgorithm_spare1 == value)
        return "spare1";
    return "";
}

uint64_t SecurityAlgorithmConfig::integrityProtAlgorithm_NumberOfValues() const
{
    return 8;
}

std::string SecurityAlgorithmConfig::integrityProtAlgorithm_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "integrityProtAlgorithm = " + integrityProtAlgorithm_ValueToString(integrityProtAlgorithm_internal_value) + "\n";
    return out;
}

std::string SecurityAlgorithmConfig::integrityProtAlgorithm_ToStringNoNewLines() const
{
    std::string out = "integrityProtAlgorithm=" + integrityProtAlgorithm_ValueToString(integrityProtAlgorithm_internal_value) + ",";
    return out;
}

int SecurityAlgorithmConfig::integrityProtAlgorithm_Clear()
{
    integrityProtAlgorithm_present = false;
    return 0;
}

bool SecurityAlgorithmConfig::integrityProtAlgorithm_IsPresent() const
{
    return integrityProtAlgorithm_present;
}

