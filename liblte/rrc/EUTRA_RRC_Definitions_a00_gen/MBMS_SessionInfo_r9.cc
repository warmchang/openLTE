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

#include "MBMS_SessionInfo_r9.h"

#include <cmath>

int MBMS_SessionInfo_r9::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator
    bits.push_back(0);

    // Optional indicators
    bits.push_back(sessionId_r9_IsPresent());

    // Fields
    {
        if(0 != tmgi_r9.Pack(bits))
        {
            printf("MBMS_SessionInfo_r9:: field pack failure\n");
            return -1;
        }
    }
    if(sessionId_r9_IsPresent())
    {
        if(0 != sessionId_r9_Pack(bits))
        {
            printf("MBMS_SessionInfo_r9:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != logicalChannelIdentity_r9_Pack(bits))
        {
            printf("MBMS_SessionInfo_r9:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int MBMS_SessionInfo_r9::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int MBMS_SessionInfo_r9::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("MBMS_SessionInfo_r9::Unpack() index out of bounds for extension\n");
        return -1;
    }
    idx++;

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("MBMS_SessionInfo_r9::Unpack() index out of bounds for optional indiator sessionId_r9\n");
        return -1;
    }
    sessionId_r9_present = bits[idx++];

    // Fields
    {
        if(0 != tmgi_r9.Unpack(bits, idx))
        {
            printf("MBMS_SessionInfo_r9:: field unpack failure\n");
            return -1;
        }
    }
    if(sessionId_r9_present)
    {
        if(0 != sessionId_r9_Unpack(bits, idx))
        {
            printf("MBMS_SessionInfo_r9:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != logicalChannelIdentity_r9_Unpack(bits, idx))
        {
            printf("MBMS_SessionInfo_r9:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string MBMS_SessionInfo_r9::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "MBMS_SessionInfo_r9:\n";
    out += tmgi_r9_ToString(indent+1);
    if(sessionId_r9_IsPresent())
        out += sessionId_r9_ToString(indent+1);
    out += logicalChannelIdentity_r9_ToString(indent+1);
    return out;
}

std::string MBMS_SessionInfo_r9::ToStringNoNewLines() const
{
    std::string out = "MBMS_SessionInfo_r9:";
    out += tmgi_r9_ToStringNoNewLines();
    if(sessionId_r9_IsPresent())
        out += sessionId_r9_ToStringNoNewLines();
    out += logicalChannelIdentity_r9_ToStringNoNewLines();
    return out;
}

TMGI_r9* MBMS_SessionInfo_r9::tmgi_r9_Set()
{
    tmgi_r9_present = true;
    return &tmgi_r9;
}

int MBMS_SessionInfo_r9::tmgi_r9_Set(TMGI_r9 &value)
{
    tmgi_r9_present = true;
    tmgi_r9 = value;
    return 0;
}

const TMGI_r9& MBMS_SessionInfo_r9::tmgi_r9_Get() const
{
    return tmgi_r9;
}

std::string MBMS_SessionInfo_r9::tmgi_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "tmgi_r9:\n";
    out += tmgi_r9.ToString(indent+1);
    return out;
}

std::string MBMS_SessionInfo_r9::tmgi_r9_ToStringNoNewLines() const
{
    std::string out = "tmgi_r9:";
    out += tmgi_r9.ToStringNoNewLines();
    return out;
}

int MBMS_SessionInfo_r9::tmgi_r9_Clear()
{
    tmgi_r9_present = false;
    return 0;
}

bool MBMS_SessionInfo_r9::tmgi_r9_IsPresent() const
{
    return tmgi_r9_present;
}

int MBMS_SessionInfo_r9::sessionId_r9_Pack(std::vector<uint8_t> &bits)
{
    if(sessionId_r9_internal_value.size() < 1 || sessionId_r9_internal_value.size() > 1)
    {
        printf("MBMS_SessionInfo_r9::sessionId_r9_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<sessionId_r9_internal_value.size(); i++)
        for(uint32_t j=0; j<8; j++)
            bits.push_back((sessionId_r9_internal_value[i] >> (8-j-1)) & 1);
    return 0;
}

int MBMS_SessionInfo_r9::sessionId_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return sessionId_r9_Unpack(bits, idx);
}

int MBMS_SessionInfo_r9::sessionId_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 1;
    if(size < 1 || size > 1)
    {
        printf("MBMS_SessionInfo_r9::sessionId_r9_Unpack() size failure\n");
        return -1;
    }
    sessionId_r9_internal_value.clear();
    if((idx +size*8) > bits.size())
    {
        printf("MBMS_SessionInfo_r9::sessionId_r9_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
    {
        uint8_t value = 0;
        for(uint32_t j=0; j<8; j++)
            value |= bits[idx+j] << (8-j-1);
        sessionId_r9_internal_value.push_back(value);
        idx += 8;
    }
    sessionId_r9_present = true;
    return 0;
}

std::vector<uint8_t> MBMS_SessionInfo_r9::sessionId_r9_Value() const
{
    if(sessionId_r9_present)
        return sessionId_r9_internal_value;
    std::vector<uint8_t> tmp;
    return tmp;
}

int MBMS_SessionInfo_r9::sessionId_r9_SetValue(std::vector<uint8_t> value)
{
    if(value.size() < 1 || value.size() > 1)
    {
        printf("MBMS_SessionInfo_r9::sessionId_r9_SetValue() size failure\n");
        return -1;
    }
    sessionId_r9_internal_value = value;
    sessionId_r9_present = true;
    return 0;
}

std::string MBMS_SessionInfo_r9::sessionId_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "sessionId_r9 = {";
    for(auto byte : sessionId_r9_internal_value)
        out += std::to_string(byte) + ",";
    out = out.substr(0, out.length()-1) + "}\n";
    return out;
}

std::string MBMS_SessionInfo_r9::sessionId_r9_ToStringNoNewLines() const
{
    std::string out = "sessionId_r9={";
    for(auto byte : sessionId_r9_internal_value)
        out += std::to_string(byte) + ",";
    out = out.substr(0, out.length()-1) + "},";
    return out;
}

int MBMS_SessionInfo_r9::sessionId_r9_Clear()
{
    sessionId_r9_present = false;
    return 0;
}

bool MBMS_SessionInfo_r9::sessionId_r9_IsPresent() const
{
    return sessionId_r9_present;
}

#include "maxSessionPerPMCH_1.h"

int MBMS_SessionInfo_r9::logicalChannelIdentity_r9_Pack(std::vector<uint8_t> &bits)
{
    if(!logicalChannelIdentity_r9_present)
    {
        printf("MBMS_SessionInfo_r9::logicalChannelIdentity_r9_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = logicalChannelIdentity_r9_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (maxSessionPerPMCH_1 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int MBMS_SessionInfo_r9::logicalChannelIdentity_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return logicalChannelIdentity_r9_Unpack(bits, idx);
}

int MBMS_SessionInfo_r9::logicalChannelIdentity_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (maxSessionPerPMCH_1 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("MBMS_SessionInfo_r9::logicalChannelIdentity_r9_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    logicalChannelIdentity_r9_internal_value = packed_val + 0;
    logicalChannelIdentity_r9_present = true;
    return 0;
}

int64_t MBMS_SessionInfo_r9::logicalChannelIdentity_r9_Value() const
{
    if(logicalChannelIdentity_r9_present)
        return logicalChannelIdentity_r9_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int MBMS_SessionInfo_r9::logicalChannelIdentity_r9_SetValue(int64_t value)
{
    if(value < 0 || value > maxSessionPerPMCH_1)
    {
        printf("MBMS_SessionInfo_r9::logicalChannelIdentity_r9_SetValue() range failure\n");
        return -1;
    }
    logicalChannelIdentity_r9_internal_value = value;
    logicalChannelIdentity_r9_present = true;
    return 0;
}

std::string MBMS_SessionInfo_r9::logicalChannelIdentity_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "logicalChannelIdentity_r9 = " + std::to_string(logicalChannelIdentity_r9_internal_value) + "\n";
    return out;
}

std::string MBMS_SessionInfo_r9::logicalChannelIdentity_r9_ToStringNoNewLines() const
{
    std::string out = "logicalChannelIdentity_r9=" + std::to_string(logicalChannelIdentity_r9_internal_value) + ",";
    return out;
}

int MBMS_SessionInfo_r9::logicalChannelIdentity_r9_Clear()
{
    logicalChannelIdentity_r9_present = false;
    return 0;
}

bool MBMS_SessionInfo_r9::logicalChannelIdentity_r9_IsPresent() const
{
    return logicalChannelIdentity_r9_present;
}

