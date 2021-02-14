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

#include "NeighCellSI_AcquisitionParameters_r9.h"

#include <cmath>

int NeighCellSI_AcquisitionParameters_r9::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(intraFreqSI_AcquisitionForHO_r9_IsPresent());
    bits.push_back(interFreqSI_AcquisitionForHO_r9_IsPresent());
    bits.push_back(utran_SI_AcquisitionForHO_r9_IsPresent());

    // Fields
    if(intraFreqSI_AcquisitionForHO_r9_IsPresent())
    {
        if(0 != intraFreqSI_AcquisitionForHO_r9_Pack(bits))
        {
            printf("NeighCellSI_AcquisitionParameters_r9:: field pack failure\n");
            return -1;
        }
    }
    if(interFreqSI_AcquisitionForHO_r9_IsPresent())
    {
        if(0 != interFreqSI_AcquisitionForHO_r9_Pack(bits))
        {
            printf("NeighCellSI_AcquisitionParameters_r9:: field pack failure\n");
            return -1;
        }
    }
    if(utran_SI_AcquisitionForHO_r9_IsPresent())
    {
        if(0 != utran_SI_AcquisitionForHO_r9_Pack(bits))
        {
            printf("NeighCellSI_AcquisitionParameters_r9:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int NeighCellSI_AcquisitionParameters_r9::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int NeighCellSI_AcquisitionParameters_r9::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("NeighCellSI_AcquisitionParameters_r9::Unpack() index out of bounds for optional indiator intraFreqSI_AcquisitionForHO_r9\n");
        return -1;
    }
    intraFreqSI_AcquisitionForHO_r9_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("NeighCellSI_AcquisitionParameters_r9::Unpack() index out of bounds for optional indiator interFreqSI_AcquisitionForHO_r9\n");
        return -1;
    }
    interFreqSI_AcquisitionForHO_r9_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("NeighCellSI_AcquisitionParameters_r9::Unpack() index out of bounds for optional indiator utran_SI_AcquisitionForHO_r9\n");
        return -1;
    }
    utran_SI_AcquisitionForHO_r9_present = bits[idx++];

    // Fields
    if(intraFreqSI_AcquisitionForHO_r9_present)
    {
        if(0 != intraFreqSI_AcquisitionForHO_r9_Unpack(bits, idx))
        {
            printf("NeighCellSI_AcquisitionParameters_r9:: field unpack failure\n");
            return -1;
        }
    }
    if(interFreqSI_AcquisitionForHO_r9_present)
    {
        if(0 != interFreqSI_AcquisitionForHO_r9_Unpack(bits, idx))
        {
            printf("NeighCellSI_AcquisitionParameters_r9:: field unpack failure\n");
            return -1;
        }
    }
    if(utran_SI_AcquisitionForHO_r9_present)
    {
        if(0 != utran_SI_AcquisitionForHO_r9_Unpack(bits, idx))
        {
            printf("NeighCellSI_AcquisitionParameters_r9:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string NeighCellSI_AcquisitionParameters_r9::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "NeighCellSI_AcquisitionParameters_r9:\n";
    if(intraFreqSI_AcquisitionForHO_r9_IsPresent())
        out += intraFreqSI_AcquisitionForHO_r9_ToString(indent+1);
    if(interFreqSI_AcquisitionForHO_r9_IsPresent())
        out += interFreqSI_AcquisitionForHO_r9_ToString(indent+1);
    if(utran_SI_AcquisitionForHO_r9_IsPresent())
        out += utran_SI_AcquisitionForHO_r9_ToString(indent+1);
    return out;
}

std::string NeighCellSI_AcquisitionParameters_r9::ToStringNoNewLines() const
{
    std::string out = "NeighCellSI_AcquisitionParameters_r9:";
    if(intraFreqSI_AcquisitionForHO_r9_IsPresent())
        out += intraFreqSI_AcquisitionForHO_r9_ToStringNoNewLines();
    if(interFreqSI_AcquisitionForHO_r9_IsPresent())
        out += interFreqSI_AcquisitionForHO_r9_ToStringNoNewLines();
    if(utran_SI_AcquisitionForHO_r9_IsPresent())
        out += utran_SI_AcquisitionForHO_r9_ToStringNoNewLines();
    return out;
}

int NeighCellSI_AcquisitionParameters_r9::intraFreqSI_AcquisitionForHO_r9_Pack(std::vector<uint8_t> &bits)
{
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((intraFreqSI_AcquisitionForHO_r9_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int NeighCellSI_AcquisitionParameters_r9::intraFreqSI_AcquisitionForHO_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return intraFreqSI_AcquisitionForHO_r9_Unpack(bits, idx);
}

int NeighCellSI_AcquisitionParameters_r9::intraFreqSI_AcquisitionForHO_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("NeighCellSI_AcquisitionParameters_r9::intraFreqSI_AcquisitionForHO_r9_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 0)
    {
        printf("NeighCellSI_AcquisitionParameters_r9::intraFreqSI_AcquisitionForHO_r9_Unpack() max failure\n");
        return -1;
    }
    intraFreqSI_AcquisitionForHO_r9_internal_value = (intraFreqSI_AcquisitionForHO_r9_Enum)packed_val;
    intraFreqSI_AcquisitionForHO_r9_present = true;
    return 0;
}

NeighCellSI_AcquisitionParameters_r9::intraFreqSI_AcquisitionForHO_r9_Enum NeighCellSI_AcquisitionParameters_r9::intraFreqSI_AcquisitionForHO_r9_Value() const
{
    if(intraFreqSI_AcquisitionForHO_r9_present)
        return intraFreqSI_AcquisitionForHO_r9_internal_value;
    return (NeighCellSI_AcquisitionParameters_r9::intraFreqSI_AcquisitionForHO_r9_Enum)0;
}

int NeighCellSI_AcquisitionParameters_r9::intraFreqSI_AcquisitionForHO_r9_SetValue(intraFreqSI_AcquisitionForHO_r9_Enum value)
{
    intraFreqSI_AcquisitionForHO_r9_internal_value = value;
    intraFreqSI_AcquisitionForHO_r9_present = true;
    return 0;
}

int NeighCellSI_AcquisitionParameters_r9::intraFreqSI_AcquisitionForHO_r9_SetValue(std::string value)
{
    if("supported" == value)
    {
        intraFreqSI_AcquisitionForHO_r9_internal_value = k_intraFreqSI_AcquisitionForHO_r9_supported;
        intraFreqSI_AcquisitionForHO_r9_present = true;
        return 0;
    }
    return 1;
}

std::string NeighCellSI_AcquisitionParameters_r9::intraFreqSI_AcquisitionForHO_r9_ValueToString(intraFreqSI_AcquisitionForHO_r9_Enum value) const
{
    if(k_intraFreqSI_AcquisitionForHO_r9_supported == value)
        return "supported";
    return "";
}

uint64_t NeighCellSI_AcquisitionParameters_r9::intraFreqSI_AcquisitionForHO_r9_NumberOfValues() const
{
    return 1;
}

std::string NeighCellSI_AcquisitionParameters_r9::intraFreqSI_AcquisitionForHO_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "intraFreqSI_AcquisitionForHO_r9 = " + intraFreqSI_AcquisitionForHO_r9_ValueToString(intraFreqSI_AcquisitionForHO_r9_internal_value) + "\n";
    return out;
}

std::string NeighCellSI_AcquisitionParameters_r9::intraFreqSI_AcquisitionForHO_r9_ToStringNoNewLines() const
{
    std::string out = "intraFreqSI_AcquisitionForHO_r9=" + intraFreqSI_AcquisitionForHO_r9_ValueToString(intraFreqSI_AcquisitionForHO_r9_internal_value) + ",";
    return out;
}

int NeighCellSI_AcquisitionParameters_r9::intraFreqSI_AcquisitionForHO_r9_Clear()
{
    intraFreqSI_AcquisitionForHO_r9_present = false;
    return 0;
}

bool NeighCellSI_AcquisitionParameters_r9::intraFreqSI_AcquisitionForHO_r9_IsPresent() const
{
    return intraFreqSI_AcquisitionForHO_r9_present;
}

int NeighCellSI_AcquisitionParameters_r9::interFreqSI_AcquisitionForHO_r9_Pack(std::vector<uint8_t> &bits)
{
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((interFreqSI_AcquisitionForHO_r9_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int NeighCellSI_AcquisitionParameters_r9::interFreqSI_AcquisitionForHO_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return interFreqSI_AcquisitionForHO_r9_Unpack(bits, idx);
}

int NeighCellSI_AcquisitionParameters_r9::interFreqSI_AcquisitionForHO_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("NeighCellSI_AcquisitionParameters_r9::interFreqSI_AcquisitionForHO_r9_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 0)
    {
        printf("NeighCellSI_AcquisitionParameters_r9::interFreqSI_AcquisitionForHO_r9_Unpack() max failure\n");
        return -1;
    }
    interFreqSI_AcquisitionForHO_r9_internal_value = (interFreqSI_AcquisitionForHO_r9_Enum)packed_val;
    interFreqSI_AcquisitionForHO_r9_present = true;
    return 0;
}

NeighCellSI_AcquisitionParameters_r9::interFreqSI_AcquisitionForHO_r9_Enum NeighCellSI_AcquisitionParameters_r9::interFreqSI_AcquisitionForHO_r9_Value() const
{
    if(interFreqSI_AcquisitionForHO_r9_present)
        return interFreqSI_AcquisitionForHO_r9_internal_value;
    return (NeighCellSI_AcquisitionParameters_r9::interFreqSI_AcquisitionForHO_r9_Enum)0;
}

int NeighCellSI_AcquisitionParameters_r9::interFreqSI_AcquisitionForHO_r9_SetValue(interFreqSI_AcquisitionForHO_r9_Enum value)
{
    interFreqSI_AcquisitionForHO_r9_internal_value = value;
    interFreqSI_AcquisitionForHO_r9_present = true;
    return 0;
}

int NeighCellSI_AcquisitionParameters_r9::interFreqSI_AcquisitionForHO_r9_SetValue(std::string value)
{
    if("supported" == value)
    {
        interFreqSI_AcquisitionForHO_r9_internal_value = k_interFreqSI_AcquisitionForHO_r9_supported;
        interFreqSI_AcquisitionForHO_r9_present = true;
        return 0;
    }
    return 1;
}

std::string NeighCellSI_AcquisitionParameters_r9::interFreqSI_AcquisitionForHO_r9_ValueToString(interFreqSI_AcquisitionForHO_r9_Enum value) const
{
    if(k_interFreqSI_AcquisitionForHO_r9_supported == value)
        return "supported";
    return "";
}

uint64_t NeighCellSI_AcquisitionParameters_r9::interFreqSI_AcquisitionForHO_r9_NumberOfValues() const
{
    return 1;
}

std::string NeighCellSI_AcquisitionParameters_r9::interFreqSI_AcquisitionForHO_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "interFreqSI_AcquisitionForHO_r9 = " + interFreqSI_AcquisitionForHO_r9_ValueToString(interFreqSI_AcquisitionForHO_r9_internal_value) + "\n";
    return out;
}

std::string NeighCellSI_AcquisitionParameters_r9::interFreqSI_AcquisitionForHO_r9_ToStringNoNewLines() const
{
    std::string out = "interFreqSI_AcquisitionForHO_r9=" + interFreqSI_AcquisitionForHO_r9_ValueToString(interFreqSI_AcquisitionForHO_r9_internal_value) + ",";
    return out;
}

int NeighCellSI_AcquisitionParameters_r9::interFreqSI_AcquisitionForHO_r9_Clear()
{
    interFreqSI_AcquisitionForHO_r9_present = false;
    return 0;
}

bool NeighCellSI_AcquisitionParameters_r9::interFreqSI_AcquisitionForHO_r9_IsPresent() const
{
    return interFreqSI_AcquisitionForHO_r9_present;
}

int NeighCellSI_AcquisitionParameters_r9::utran_SI_AcquisitionForHO_r9_Pack(std::vector<uint8_t> &bits)
{
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((utran_SI_AcquisitionForHO_r9_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int NeighCellSI_AcquisitionParameters_r9::utran_SI_AcquisitionForHO_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return utran_SI_AcquisitionForHO_r9_Unpack(bits, idx);
}

int NeighCellSI_AcquisitionParameters_r9::utran_SI_AcquisitionForHO_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("NeighCellSI_AcquisitionParameters_r9::utran_SI_AcquisitionForHO_r9_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 0)
    {
        printf("NeighCellSI_AcquisitionParameters_r9::utran_SI_AcquisitionForHO_r9_Unpack() max failure\n");
        return -1;
    }
    utran_SI_AcquisitionForHO_r9_internal_value = (utran_SI_AcquisitionForHO_r9_Enum)packed_val;
    utran_SI_AcquisitionForHO_r9_present = true;
    return 0;
}

NeighCellSI_AcquisitionParameters_r9::utran_SI_AcquisitionForHO_r9_Enum NeighCellSI_AcquisitionParameters_r9::utran_SI_AcquisitionForHO_r9_Value() const
{
    if(utran_SI_AcquisitionForHO_r9_present)
        return utran_SI_AcquisitionForHO_r9_internal_value;
    return (NeighCellSI_AcquisitionParameters_r9::utran_SI_AcquisitionForHO_r9_Enum)0;
}

int NeighCellSI_AcquisitionParameters_r9::utran_SI_AcquisitionForHO_r9_SetValue(utran_SI_AcquisitionForHO_r9_Enum value)
{
    utran_SI_AcquisitionForHO_r9_internal_value = value;
    utran_SI_AcquisitionForHO_r9_present = true;
    return 0;
}

int NeighCellSI_AcquisitionParameters_r9::utran_SI_AcquisitionForHO_r9_SetValue(std::string value)
{
    if("supported" == value)
    {
        utran_SI_AcquisitionForHO_r9_internal_value = k_utran_SI_AcquisitionForHO_r9_supported;
        utran_SI_AcquisitionForHO_r9_present = true;
        return 0;
    }
    return 1;
}

std::string NeighCellSI_AcquisitionParameters_r9::utran_SI_AcquisitionForHO_r9_ValueToString(utran_SI_AcquisitionForHO_r9_Enum value) const
{
    if(k_utran_SI_AcquisitionForHO_r9_supported == value)
        return "supported";
    return "";
}

uint64_t NeighCellSI_AcquisitionParameters_r9::utran_SI_AcquisitionForHO_r9_NumberOfValues() const
{
    return 1;
}

std::string NeighCellSI_AcquisitionParameters_r9::utran_SI_AcquisitionForHO_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "utran_SI_AcquisitionForHO_r9 = " + utran_SI_AcquisitionForHO_r9_ValueToString(utran_SI_AcquisitionForHO_r9_internal_value) + "\n";
    return out;
}

std::string NeighCellSI_AcquisitionParameters_r9::utran_SI_AcquisitionForHO_r9_ToStringNoNewLines() const
{
    std::string out = "utran_SI_AcquisitionForHO_r9=" + utran_SI_AcquisitionForHO_r9_ValueToString(utran_SI_AcquisitionForHO_r9_internal_value) + ",";
    return out;
}

int NeighCellSI_AcquisitionParameters_r9::utran_SI_AcquisitionForHO_r9_Clear()
{
    utran_SI_AcquisitionForHO_r9_present = false;
    return 0;
}

bool NeighCellSI_AcquisitionParameters_r9::utran_SI_AcquisitionForHO_r9_IsPresent() const
{
    return utran_SI_AcquisitionForHO_r9_present;
}

