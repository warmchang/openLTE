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

#include "S_TMSI.h"

#include <cmath>

int S_TMSI::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != mmec.Pack(bits))
        {
            printf("S_TMSI:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != m_TMSI_Pack(bits))
        {
            printf("S_TMSI:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int S_TMSI::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int S_TMSI::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != mmec.Unpack(bits, idx))
        {
            printf("S_TMSI:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != m_TMSI_Unpack(bits, idx))
        {
            printf("S_TMSI:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string S_TMSI::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "S_TMSI:\n";
    out += mmec_ToString(indent+1);
    out += m_TMSI_ToString(indent+1);
    return out;
}

std::string S_TMSI::ToStringNoNewLines() const
{
    std::string out = "S_TMSI:";
    out += mmec_ToStringNoNewLines();
    out += m_TMSI_ToStringNoNewLines();
    return out;
}

MMEC* S_TMSI::mmec_Set()
{
    mmec_present = true;
    return &mmec;
}

int S_TMSI::mmec_Set(MMEC &value)
{
    mmec_present = true;
    mmec = value;
    return 0;
}

const MMEC& S_TMSI::mmec_Get() const
{
    return mmec;
}

std::string S_TMSI::mmec_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "mmec:\n";
    out += mmec.ToString(indent+1);
    return out;
}

std::string S_TMSI::mmec_ToStringNoNewLines() const
{
    std::string out = "mmec:";
    out += mmec.ToStringNoNewLines();
    return out;
}

int S_TMSI::mmec_Clear()
{
    mmec_present = false;
    return 0;
}

bool S_TMSI::mmec_IsPresent() const
{
    return mmec_present;
}

int S_TMSI::m_TMSI_Pack(std::vector<uint8_t> &bits)
{
    if(!m_TMSI_present)
    {
        printf("S_TMSI::m_TMSI_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 32;
    if(size < 32 || size > 32)
    {
        printf("S_TMSI::m_TMSI_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((m_TMSI_internal_value >> (32-i-1)) & 1);
    return 0;
}

int S_TMSI::m_TMSI_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return m_TMSI_Unpack(bits, idx);
}

int S_TMSI::m_TMSI_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 32;
    if(size < 32 || size > 32)
    {
        printf("S_TMSI::m_TMSI_Unpack() size failure\n");
        return -1;
    }
    m_TMSI_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("S_TMSI::m_TMSI_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        m_TMSI_internal_value |= (uint32_t)bits[idx++] << (uint32_t)(32-i-1);
    m_TMSI_present = true;
    return 0;
}

uint32_t S_TMSI::m_TMSI_Value() const
{
    if(m_TMSI_present)
        return m_TMSI_internal_value;
    uint32_t tmp = 0;
    return tmp;
}

int S_TMSI::m_TMSI_SetValue(uint32_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 32)
    {
        printf("S_TMSI::m_TMSI_SetValue() size failure\n");
        return -1;
    }
    m_TMSI_internal_value = value;
    m_TMSI_present = true;
    return 0;
}

std::string S_TMSI::m_TMSI_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "m_TMSI = ";
    out += std::to_string(m_TMSI_internal_value);
    out += "\n";
    return out;
}

std::string S_TMSI::m_TMSI_ToStringNoNewLines() const
{
    std::string out = "m_TMSI=";
    out += std::to_string(m_TMSI_internal_value);
    out += ",";
    return out;
}

int S_TMSI::m_TMSI_Clear()
{
    m_TMSI_present = false;
    return 0;
}

bool S_TMSI::m_TMSI_IsPresent() const
{
    return m_TMSI_present;
}

