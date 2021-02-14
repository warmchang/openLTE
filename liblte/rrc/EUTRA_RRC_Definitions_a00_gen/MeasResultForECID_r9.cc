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

#include "MeasResultForECID_r9.h"

#include <cmath>

int MeasResultForECID_r9::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != ue_RxTxTimeDiffResult_r9_Pack(bits))
        {
            printf("MeasResultForECID_r9:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != currentSFN_r9_Pack(bits))
        {
            printf("MeasResultForECID_r9:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int MeasResultForECID_r9::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int MeasResultForECID_r9::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != ue_RxTxTimeDiffResult_r9_Unpack(bits, idx))
        {
            printf("MeasResultForECID_r9:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != currentSFN_r9_Unpack(bits, idx))
        {
            printf("MeasResultForECID_r9:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string MeasResultForECID_r9::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "MeasResultForECID_r9:\n";
    out += ue_RxTxTimeDiffResult_r9_ToString(indent+1);
    out += currentSFN_r9_ToString(indent+1);
    return out;
}

std::string MeasResultForECID_r9::ToStringNoNewLines() const
{
    std::string out = "MeasResultForECID_r9:";
    out += ue_RxTxTimeDiffResult_r9_ToStringNoNewLines();
    out += currentSFN_r9_ToStringNoNewLines();
    return out;
}

int MeasResultForECID_r9::ue_RxTxTimeDiffResult_r9_Pack(std::vector<uint8_t> &bits)
{
    if(!ue_RxTxTimeDiffResult_r9_present)
    {
        printf("MeasResultForECID_r9::ue_RxTxTimeDiffResult_r9_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = ue_RxTxTimeDiffResult_r9_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (4095 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int MeasResultForECID_r9::ue_RxTxTimeDiffResult_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return ue_RxTxTimeDiffResult_r9_Unpack(bits, idx);
}

int MeasResultForECID_r9::ue_RxTxTimeDiffResult_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (4095 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("MeasResultForECID_r9::ue_RxTxTimeDiffResult_r9_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    ue_RxTxTimeDiffResult_r9_internal_value = packed_val + 0;
    ue_RxTxTimeDiffResult_r9_present = true;
    return 0;
}

int64_t MeasResultForECID_r9::ue_RxTxTimeDiffResult_r9_Value() const
{
    if(ue_RxTxTimeDiffResult_r9_present)
        return ue_RxTxTimeDiffResult_r9_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int MeasResultForECID_r9::ue_RxTxTimeDiffResult_r9_SetValue(int64_t value)
{
    if(value < 0 || value > 4095)
    {
        printf("MeasResultForECID_r9::ue_RxTxTimeDiffResult_r9_SetValue() range failure\n");
        return -1;
    }
    ue_RxTxTimeDiffResult_r9_internal_value = value;
    ue_RxTxTimeDiffResult_r9_present = true;
    return 0;
}

std::string MeasResultForECID_r9::ue_RxTxTimeDiffResult_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ue_RxTxTimeDiffResult_r9 = " + std::to_string(ue_RxTxTimeDiffResult_r9_internal_value) + "\n";
    return out;
}

std::string MeasResultForECID_r9::ue_RxTxTimeDiffResult_r9_ToStringNoNewLines() const
{
    std::string out = "ue_RxTxTimeDiffResult_r9=" + std::to_string(ue_RxTxTimeDiffResult_r9_internal_value) + ",";
    return out;
}

int MeasResultForECID_r9::ue_RxTxTimeDiffResult_r9_Clear()
{
    ue_RxTxTimeDiffResult_r9_present = false;
    return 0;
}

bool MeasResultForECID_r9::ue_RxTxTimeDiffResult_r9_IsPresent() const
{
    return ue_RxTxTimeDiffResult_r9_present;
}

int MeasResultForECID_r9::currentSFN_r9_Pack(std::vector<uint8_t> &bits)
{
    if(!currentSFN_r9_present)
    {
        printf("MeasResultForECID_r9::currentSFN_r9_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 10;
    if(size < 10 || size > 10)
    {
        printf("MeasResultForECID_r9::currentSFN_r9_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((currentSFN_r9_internal_value >> (10-i-1)) & 1);
    return 0;
}

int MeasResultForECID_r9::currentSFN_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return currentSFN_r9_Unpack(bits, idx);
}

int MeasResultForECID_r9::currentSFN_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 10;
    if(size < 10 || size > 10)
    {
        printf("MeasResultForECID_r9::currentSFN_r9_Unpack() size failure\n");
        return -1;
    }
    currentSFN_r9_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("MeasResultForECID_r9::currentSFN_r9_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        currentSFN_r9_internal_value |= (uint16_t)bits[idx++] << (uint16_t)(10-i-1);
    currentSFN_r9_present = true;
    return 0;
}

uint16_t MeasResultForECID_r9::currentSFN_r9_Value() const
{
    if(currentSFN_r9_present)
        return currentSFN_r9_internal_value;
    uint16_t tmp = 0;
    return tmp;
}

int MeasResultForECID_r9::currentSFN_r9_SetValue(uint16_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 10)
    {
        printf("MeasResultForECID_r9::currentSFN_r9_SetValue() size failure\n");
        return -1;
    }
    currentSFN_r9_internal_value = value;
    currentSFN_r9_present = true;
    return 0;
}

std::string MeasResultForECID_r9::currentSFN_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "currentSFN_r9 = ";
    out += std::to_string(currentSFN_r9_internal_value);
    out += "\n";
    return out;
}

std::string MeasResultForECID_r9::currentSFN_r9_ToStringNoNewLines() const
{
    std::string out = "currentSFN_r9=";
    out += std::to_string(currentSFN_r9_internal_value);
    out += ",";
    return out;
}

int MeasResultForECID_r9::currentSFN_r9_Clear()
{
    currentSFN_r9_present = false;
    return 0;
}

bool MeasResultForECID_r9::currentSFN_r9_IsPresent() const
{
    return currentSFN_r9_present;
}

