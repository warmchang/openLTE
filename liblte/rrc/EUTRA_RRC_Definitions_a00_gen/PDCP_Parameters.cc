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

#include "PDCP_Parameters.h"

#include <cmath>

int PDCP_Parameters::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator
    bits.push_back(0);

    // Optional indicators
    if(!maxNumberROHC_ContextSessions_IsPresent() || maxNumberROHC_ContextSessions_Value() == maxNumberROHC_ContextSessions_GetDefault())
    {
        bits.push_back(0);
    }else{
        bits.push_back(1);
    }

    // Fields
    {
        if(0 != supportedROHC_Profiles_value.Pack(bits))
        {
            printf("PDCP_Parameters:: field pack failure\n");
            return -1;
        }
    }
    if(maxNumberROHC_ContextSessions_IsPresent() || maxNumberROHC_ContextSessions_Value() != maxNumberROHC_ContextSessions_GetDefault())
    {
        if(0 != maxNumberROHC_ContextSessions_Pack(bits))
        {
            printf("PDCP_Parameters:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int PDCP_Parameters::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int PDCP_Parameters::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("PDCP_Parameters::Unpack() index out of bounds for extension\n");
        return -1;
    }
    idx++;

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("PDCP_Parameters::Unpack() index out of bounds for optional indiator maxNumberROHC_ContextSessions\n");
        return -1;
    }
    maxNumberROHC_ContextSessions_present = bits[idx++];

    // Fields
    {
        if(0 != supportedROHC_Profiles_value.Unpack(bits, idx))
        {
            printf("PDCP_Parameters:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != maxNumberROHC_ContextSessions_Unpack(bits, idx))
        {
            printf("PDCP_Parameters:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string PDCP_Parameters::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "PDCP_Parameters:\n";
    out += supportedROHC_Profiles_value.ToString(indent+1);
    out += maxNumberROHC_ContextSessions_ToString(indent+1);
    return out;
}

std::string PDCP_Parameters::ToStringNoNewLines() const
{
    std::string out = "PDCP_Parameters:";
    out += supportedROHC_Profiles_value.ToStringNoNewLines();
    out += maxNumberROHC_ContextSessions_ToStringNoNewLines();
    return out;
}

int PDCP_Parameters::supportedROHC_Profiles::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != profile0x0001_Pack(bits))
        {
            printf("PDCP_Parameters::supportedROHC_Profiles:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != profile0x0002_Pack(bits))
        {
            printf("PDCP_Parameters::supportedROHC_Profiles:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != profile0x0003_Pack(bits))
        {
            printf("PDCP_Parameters::supportedROHC_Profiles:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != profile0x0004_Pack(bits))
        {
            printf("PDCP_Parameters::supportedROHC_Profiles:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != profile0x0006_Pack(bits))
        {
            printf("PDCP_Parameters::supportedROHC_Profiles:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != profile0x0101_Pack(bits))
        {
            printf("PDCP_Parameters::supportedROHC_Profiles:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != profile0x0102_Pack(bits))
        {
            printf("PDCP_Parameters::supportedROHC_Profiles:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != profile0x0103_Pack(bits))
        {
            printf("PDCP_Parameters::supportedROHC_Profiles:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != profile0x0104_Pack(bits))
        {
            printf("PDCP_Parameters::supportedROHC_Profiles:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int PDCP_Parameters::supportedROHC_Profiles::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int PDCP_Parameters::supportedROHC_Profiles::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != profile0x0001_Unpack(bits, idx))
        {
            printf("PDCP_Parameters::supportedROHC_Profiles:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != profile0x0002_Unpack(bits, idx))
        {
            printf("PDCP_Parameters::supportedROHC_Profiles:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != profile0x0003_Unpack(bits, idx))
        {
            printf("PDCP_Parameters::supportedROHC_Profiles:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != profile0x0004_Unpack(bits, idx))
        {
            printf("PDCP_Parameters::supportedROHC_Profiles:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != profile0x0006_Unpack(bits, idx))
        {
            printf("PDCP_Parameters::supportedROHC_Profiles:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != profile0x0101_Unpack(bits, idx))
        {
            printf("PDCP_Parameters::supportedROHC_Profiles:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != profile0x0102_Unpack(bits, idx))
        {
            printf("PDCP_Parameters::supportedROHC_Profiles:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != profile0x0103_Unpack(bits, idx))
        {
            printf("PDCP_Parameters::supportedROHC_Profiles:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != profile0x0104_Unpack(bits, idx))
        {
            printf("PDCP_Parameters::supportedROHC_Profiles:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string PDCP_Parameters::supportedROHC_Profiles::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "supportedROHC_Profiles:\n";
    out += profile0x0001_ToString(indent+1);
    out += profile0x0002_ToString(indent+1);
    out += profile0x0003_ToString(indent+1);
    out += profile0x0004_ToString(indent+1);
    out += profile0x0006_ToString(indent+1);
    out += profile0x0101_ToString(indent+1);
    out += profile0x0102_ToString(indent+1);
    out += profile0x0103_ToString(indent+1);
    out += profile0x0104_ToString(indent+1);
    return out;
}

std::string PDCP_Parameters::supportedROHC_Profiles::ToStringNoNewLines() const
{
    std::string out = "supportedROHC_Profiles:";
    out += profile0x0001_ToStringNoNewLines();
    out += profile0x0002_ToStringNoNewLines();
    out += profile0x0003_ToStringNoNewLines();
    out += profile0x0004_ToStringNoNewLines();
    out += profile0x0006_ToStringNoNewLines();
    out += profile0x0101_ToStringNoNewLines();
    out += profile0x0102_ToStringNoNewLines();
    out += profile0x0103_ToStringNoNewLines();
    out += profile0x0104_ToStringNoNewLines();
    return out;
}

int PDCP_Parameters::supportedROHC_Profiles::profile0x0001_Pack(std::vector<uint8_t> &bits)
{
    if(!profile0x0001_present)
    {
        printf("PDCP_Parameters::supportedROHC_Profiles::profile0x0001_Pack() presence failure\n");
        return -1;
    }
    bits.push_back(profile0x0001_internal_value);
    return 0;
}

int PDCP_Parameters::supportedROHC_Profiles::profile0x0001_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return profile0x0001_Unpack(bits, idx);
}

int PDCP_Parameters::supportedROHC_Profiles::profile0x0001_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    if((idx + 1) > bits.size())
    {
        printf("PDCP_Parameters::supportedROHC_Profiles::profile0x0001_Unpack() index out of bounds\n");
        return -1;
    }
    profile0x0001_internal_value = bits[idx++];
    profile0x0001_present = true;
    return 0;
}

bool PDCP_Parameters::supportedROHC_Profiles::profile0x0001_Value() const
{
    if(profile0x0001_present)
        return profile0x0001_internal_value;
    return false;
}

int PDCP_Parameters::supportedROHC_Profiles::profile0x0001_SetValue(bool value)
{
    profile0x0001_internal_value = value;
    profile0x0001_present = true;
    return 0;
}

std::string PDCP_Parameters::supportedROHC_Profiles::profile0x0001_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "profile0x0001 = " + std::to_string(profile0x0001_internal_value) + "\n";
    return out;
}

std::string PDCP_Parameters::supportedROHC_Profiles::profile0x0001_ToStringNoNewLines() const
{
    std::string out = "profile0x0001=" + std::to_string(profile0x0001_internal_value) + ",";
    return out;
}

int PDCP_Parameters::supportedROHC_Profiles::profile0x0001_Clear()
{
    profile0x0001_present = false;
    return 0;
}

bool PDCP_Parameters::supportedROHC_Profiles::profile0x0001_IsPresent() const
{
    return profile0x0001_present;
}

int PDCP_Parameters::supportedROHC_Profiles::profile0x0002_Pack(std::vector<uint8_t> &bits)
{
    if(!profile0x0002_present)
    {
        printf("PDCP_Parameters::supportedROHC_Profiles::profile0x0002_Pack() presence failure\n");
        return -1;
    }
    bits.push_back(profile0x0002_internal_value);
    return 0;
}

int PDCP_Parameters::supportedROHC_Profiles::profile0x0002_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return profile0x0002_Unpack(bits, idx);
}

int PDCP_Parameters::supportedROHC_Profiles::profile0x0002_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    if((idx + 1) > bits.size())
    {
        printf("PDCP_Parameters::supportedROHC_Profiles::profile0x0002_Unpack() index out of bounds\n");
        return -1;
    }
    profile0x0002_internal_value = bits[idx++];
    profile0x0002_present = true;
    return 0;
}

bool PDCP_Parameters::supportedROHC_Profiles::profile0x0002_Value() const
{
    if(profile0x0002_present)
        return profile0x0002_internal_value;
    return false;
}

int PDCP_Parameters::supportedROHC_Profiles::profile0x0002_SetValue(bool value)
{
    profile0x0002_internal_value = value;
    profile0x0002_present = true;
    return 0;
}

std::string PDCP_Parameters::supportedROHC_Profiles::profile0x0002_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "profile0x0002 = " + std::to_string(profile0x0002_internal_value) + "\n";
    return out;
}

std::string PDCP_Parameters::supportedROHC_Profiles::profile0x0002_ToStringNoNewLines() const
{
    std::string out = "profile0x0002=" + std::to_string(profile0x0002_internal_value) + ",";
    return out;
}

int PDCP_Parameters::supportedROHC_Profiles::profile0x0002_Clear()
{
    profile0x0002_present = false;
    return 0;
}

bool PDCP_Parameters::supportedROHC_Profiles::profile0x0002_IsPresent() const
{
    return profile0x0002_present;
}

int PDCP_Parameters::supportedROHC_Profiles::profile0x0003_Pack(std::vector<uint8_t> &bits)
{
    if(!profile0x0003_present)
    {
        printf("PDCP_Parameters::supportedROHC_Profiles::profile0x0003_Pack() presence failure\n");
        return -1;
    }
    bits.push_back(profile0x0003_internal_value);
    return 0;
}

int PDCP_Parameters::supportedROHC_Profiles::profile0x0003_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return profile0x0003_Unpack(bits, idx);
}

int PDCP_Parameters::supportedROHC_Profiles::profile0x0003_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    if((idx + 1) > bits.size())
    {
        printf("PDCP_Parameters::supportedROHC_Profiles::profile0x0003_Unpack() index out of bounds\n");
        return -1;
    }
    profile0x0003_internal_value = bits[idx++];
    profile0x0003_present = true;
    return 0;
}

bool PDCP_Parameters::supportedROHC_Profiles::profile0x0003_Value() const
{
    if(profile0x0003_present)
        return profile0x0003_internal_value;
    return false;
}

int PDCP_Parameters::supportedROHC_Profiles::profile0x0003_SetValue(bool value)
{
    profile0x0003_internal_value = value;
    profile0x0003_present = true;
    return 0;
}

std::string PDCP_Parameters::supportedROHC_Profiles::profile0x0003_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "profile0x0003 = " + std::to_string(profile0x0003_internal_value) + "\n";
    return out;
}

std::string PDCP_Parameters::supportedROHC_Profiles::profile0x0003_ToStringNoNewLines() const
{
    std::string out = "profile0x0003=" + std::to_string(profile0x0003_internal_value) + ",";
    return out;
}

int PDCP_Parameters::supportedROHC_Profiles::profile0x0003_Clear()
{
    profile0x0003_present = false;
    return 0;
}

bool PDCP_Parameters::supportedROHC_Profiles::profile0x0003_IsPresent() const
{
    return profile0x0003_present;
}

int PDCP_Parameters::supportedROHC_Profiles::profile0x0004_Pack(std::vector<uint8_t> &bits)
{
    if(!profile0x0004_present)
    {
        printf("PDCP_Parameters::supportedROHC_Profiles::profile0x0004_Pack() presence failure\n");
        return -1;
    }
    bits.push_back(profile0x0004_internal_value);
    return 0;
}

int PDCP_Parameters::supportedROHC_Profiles::profile0x0004_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return profile0x0004_Unpack(bits, idx);
}

int PDCP_Parameters::supportedROHC_Profiles::profile0x0004_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    if((idx + 1) > bits.size())
    {
        printf("PDCP_Parameters::supportedROHC_Profiles::profile0x0004_Unpack() index out of bounds\n");
        return -1;
    }
    profile0x0004_internal_value = bits[idx++];
    profile0x0004_present = true;
    return 0;
}

bool PDCP_Parameters::supportedROHC_Profiles::profile0x0004_Value() const
{
    if(profile0x0004_present)
        return profile0x0004_internal_value;
    return false;
}

int PDCP_Parameters::supportedROHC_Profiles::profile0x0004_SetValue(bool value)
{
    profile0x0004_internal_value = value;
    profile0x0004_present = true;
    return 0;
}

std::string PDCP_Parameters::supportedROHC_Profiles::profile0x0004_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "profile0x0004 = " + std::to_string(profile0x0004_internal_value) + "\n";
    return out;
}

std::string PDCP_Parameters::supportedROHC_Profiles::profile0x0004_ToStringNoNewLines() const
{
    std::string out = "profile0x0004=" + std::to_string(profile0x0004_internal_value) + ",";
    return out;
}

int PDCP_Parameters::supportedROHC_Profiles::profile0x0004_Clear()
{
    profile0x0004_present = false;
    return 0;
}

bool PDCP_Parameters::supportedROHC_Profiles::profile0x0004_IsPresent() const
{
    return profile0x0004_present;
}

int PDCP_Parameters::supportedROHC_Profiles::profile0x0006_Pack(std::vector<uint8_t> &bits)
{
    if(!profile0x0006_present)
    {
        printf("PDCP_Parameters::supportedROHC_Profiles::profile0x0006_Pack() presence failure\n");
        return -1;
    }
    bits.push_back(profile0x0006_internal_value);
    return 0;
}

int PDCP_Parameters::supportedROHC_Profiles::profile0x0006_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return profile0x0006_Unpack(bits, idx);
}

int PDCP_Parameters::supportedROHC_Profiles::profile0x0006_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    if((idx + 1) > bits.size())
    {
        printf("PDCP_Parameters::supportedROHC_Profiles::profile0x0006_Unpack() index out of bounds\n");
        return -1;
    }
    profile0x0006_internal_value = bits[idx++];
    profile0x0006_present = true;
    return 0;
}

bool PDCP_Parameters::supportedROHC_Profiles::profile0x0006_Value() const
{
    if(profile0x0006_present)
        return profile0x0006_internal_value;
    return false;
}

int PDCP_Parameters::supportedROHC_Profiles::profile0x0006_SetValue(bool value)
{
    profile0x0006_internal_value = value;
    profile0x0006_present = true;
    return 0;
}

std::string PDCP_Parameters::supportedROHC_Profiles::profile0x0006_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "profile0x0006 = " + std::to_string(profile0x0006_internal_value) + "\n";
    return out;
}

std::string PDCP_Parameters::supportedROHC_Profiles::profile0x0006_ToStringNoNewLines() const
{
    std::string out = "profile0x0006=" + std::to_string(profile0x0006_internal_value) + ",";
    return out;
}

int PDCP_Parameters::supportedROHC_Profiles::profile0x0006_Clear()
{
    profile0x0006_present = false;
    return 0;
}

bool PDCP_Parameters::supportedROHC_Profiles::profile0x0006_IsPresent() const
{
    return profile0x0006_present;
}

int PDCP_Parameters::supportedROHC_Profiles::profile0x0101_Pack(std::vector<uint8_t> &bits)
{
    if(!profile0x0101_present)
    {
        printf("PDCP_Parameters::supportedROHC_Profiles::profile0x0101_Pack() presence failure\n");
        return -1;
    }
    bits.push_back(profile0x0101_internal_value);
    return 0;
}

int PDCP_Parameters::supportedROHC_Profiles::profile0x0101_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return profile0x0101_Unpack(bits, idx);
}

int PDCP_Parameters::supportedROHC_Profiles::profile0x0101_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    if((idx + 1) > bits.size())
    {
        printf("PDCP_Parameters::supportedROHC_Profiles::profile0x0101_Unpack() index out of bounds\n");
        return -1;
    }
    profile0x0101_internal_value = bits[idx++];
    profile0x0101_present = true;
    return 0;
}

bool PDCP_Parameters::supportedROHC_Profiles::profile0x0101_Value() const
{
    if(profile0x0101_present)
        return profile0x0101_internal_value;
    return false;
}

int PDCP_Parameters::supportedROHC_Profiles::profile0x0101_SetValue(bool value)
{
    profile0x0101_internal_value = value;
    profile0x0101_present = true;
    return 0;
}

std::string PDCP_Parameters::supportedROHC_Profiles::profile0x0101_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "profile0x0101 = " + std::to_string(profile0x0101_internal_value) + "\n";
    return out;
}

std::string PDCP_Parameters::supportedROHC_Profiles::profile0x0101_ToStringNoNewLines() const
{
    std::string out = "profile0x0101=" + std::to_string(profile0x0101_internal_value) + ",";
    return out;
}

int PDCP_Parameters::supportedROHC_Profiles::profile0x0101_Clear()
{
    profile0x0101_present = false;
    return 0;
}

bool PDCP_Parameters::supportedROHC_Profiles::profile0x0101_IsPresent() const
{
    return profile0x0101_present;
}

int PDCP_Parameters::supportedROHC_Profiles::profile0x0102_Pack(std::vector<uint8_t> &bits)
{
    if(!profile0x0102_present)
    {
        printf("PDCP_Parameters::supportedROHC_Profiles::profile0x0102_Pack() presence failure\n");
        return -1;
    }
    bits.push_back(profile0x0102_internal_value);
    return 0;
}

int PDCP_Parameters::supportedROHC_Profiles::profile0x0102_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return profile0x0102_Unpack(bits, idx);
}

int PDCP_Parameters::supportedROHC_Profiles::profile0x0102_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    if((idx + 1) > bits.size())
    {
        printf("PDCP_Parameters::supportedROHC_Profiles::profile0x0102_Unpack() index out of bounds\n");
        return -1;
    }
    profile0x0102_internal_value = bits[idx++];
    profile0x0102_present = true;
    return 0;
}

bool PDCP_Parameters::supportedROHC_Profiles::profile0x0102_Value() const
{
    if(profile0x0102_present)
        return profile0x0102_internal_value;
    return false;
}

int PDCP_Parameters::supportedROHC_Profiles::profile0x0102_SetValue(bool value)
{
    profile0x0102_internal_value = value;
    profile0x0102_present = true;
    return 0;
}

std::string PDCP_Parameters::supportedROHC_Profiles::profile0x0102_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "profile0x0102 = " + std::to_string(profile0x0102_internal_value) + "\n";
    return out;
}

std::string PDCP_Parameters::supportedROHC_Profiles::profile0x0102_ToStringNoNewLines() const
{
    std::string out = "profile0x0102=" + std::to_string(profile0x0102_internal_value) + ",";
    return out;
}

int PDCP_Parameters::supportedROHC_Profiles::profile0x0102_Clear()
{
    profile0x0102_present = false;
    return 0;
}

bool PDCP_Parameters::supportedROHC_Profiles::profile0x0102_IsPresent() const
{
    return profile0x0102_present;
}

int PDCP_Parameters::supportedROHC_Profiles::profile0x0103_Pack(std::vector<uint8_t> &bits)
{
    if(!profile0x0103_present)
    {
        printf("PDCP_Parameters::supportedROHC_Profiles::profile0x0103_Pack() presence failure\n");
        return -1;
    }
    bits.push_back(profile0x0103_internal_value);
    return 0;
}

int PDCP_Parameters::supportedROHC_Profiles::profile0x0103_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return profile0x0103_Unpack(bits, idx);
}

int PDCP_Parameters::supportedROHC_Profiles::profile0x0103_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    if((idx + 1) > bits.size())
    {
        printf("PDCP_Parameters::supportedROHC_Profiles::profile0x0103_Unpack() index out of bounds\n");
        return -1;
    }
    profile0x0103_internal_value = bits[idx++];
    profile0x0103_present = true;
    return 0;
}

bool PDCP_Parameters::supportedROHC_Profiles::profile0x0103_Value() const
{
    if(profile0x0103_present)
        return profile0x0103_internal_value;
    return false;
}

int PDCP_Parameters::supportedROHC_Profiles::profile0x0103_SetValue(bool value)
{
    profile0x0103_internal_value = value;
    profile0x0103_present = true;
    return 0;
}

std::string PDCP_Parameters::supportedROHC_Profiles::profile0x0103_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "profile0x0103 = " + std::to_string(profile0x0103_internal_value) + "\n";
    return out;
}

std::string PDCP_Parameters::supportedROHC_Profiles::profile0x0103_ToStringNoNewLines() const
{
    std::string out = "profile0x0103=" + std::to_string(profile0x0103_internal_value) + ",";
    return out;
}

int PDCP_Parameters::supportedROHC_Profiles::profile0x0103_Clear()
{
    profile0x0103_present = false;
    return 0;
}

bool PDCP_Parameters::supportedROHC_Profiles::profile0x0103_IsPresent() const
{
    return profile0x0103_present;
}

int PDCP_Parameters::supportedROHC_Profiles::profile0x0104_Pack(std::vector<uint8_t> &bits)
{
    if(!profile0x0104_present)
    {
        printf("PDCP_Parameters::supportedROHC_Profiles::profile0x0104_Pack() presence failure\n");
        return -1;
    }
    bits.push_back(profile0x0104_internal_value);
    return 0;
}

int PDCP_Parameters::supportedROHC_Profiles::profile0x0104_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return profile0x0104_Unpack(bits, idx);
}

int PDCP_Parameters::supportedROHC_Profiles::profile0x0104_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    if((idx + 1) > bits.size())
    {
        printf("PDCP_Parameters::supportedROHC_Profiles::profile0x0104_Unpack() index out of bounds\n");
        return -1;
    }
    profile0x0104_internal_value = bits[idx++];
    profile0x0104_present = true;
    return 0;
}

bool PDCP_Parameters::supportedROHC_Profiles::profile0x0104_Value() const
{
    if(profile0x0104_present)
        return profile0x0104_internal_value;
    return false;
}

int PDCP_Parameters::supportedROHC_Profiles::profile0x0104_SetValue(bool value)
{
    profile0x0104_internal_value = value;
    profile0x0104_present = true;
    return 0;
}

std::string PDCP_Parameters::supportedROHC_Profiles::profile0x0104_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "profile0x0104 = " + std::to_string(profile0x0104_internal_value) + "\n";
    return out;
}

std::string PDCP_Parameters::supportedROHC_Profiles::profile0x0104_ToStringNoNewLines() const
{
    std::string out = "profile0x0104=" + std::to_string(profile0x0104_internal_value) + ",";
    return out;
}

int PDCP_Parameters::supportedROHC_Profiles::profile0x0104_Clear()
{
    profile0x0104_present = false;
    return 0;
}

bool PDCP_Parameters::supportedROHC_Profiles::profile0x0104_IsPresent() const
{
    return profile0x0104_present;
}

int PDCP_Parameters::maxNumberROHC_ContextSessions_Pack(std::vector<uint8_t> &bits)
{
    if(!maxNumberROHC_ContextSessions_present)
    {
        maxNumberROHC_ContextSessions_present = true;
        maxNumberROHC_ContextSessions_internal_value = maxNumberROHC_ContextSessions_GetDefault();
    }
    if(!maxNumberROHC_ContextSessions_present)
    {
        printf("PDCP_Parameters::maxNumberROHC_ContextSessions_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 4;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((maxNumberROHC_ContextSessions_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int PDCP_Parameters::maxNumberROHC_ContextSessions_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return maxNumberROHC_ContextSessions_Unpack(bits, idx);
}

int PDCP_Parameters::maxNumberROHC_ContextSessions_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 4;
    if((idx + N_bits) > bits.size())
    {
        printf("PDCP_Parameters::maxNumberROHC_ContextSessions_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 15)
    {
        printf("PDCP_Parameters::maxNumberROHC_ContextSessions_Unpack() max failure\n");
        return -1;
    }
    maxNumberROHC_ContextSessions_internal_value = (maxNumberROHC_ContextSessions_Enum)packed_val;
    maxNumberROHC_ContextSessions_present = true;
    return 0;
}

PDCP_Parameters::maxNumberROHC_ContextSessions_Enum PDCP_Parameters::maxNumberROHC_ContextSessions_Value() const
{
    if(maxNumberROHC_ContextSessions_present)
        return maxNumberROHC_ContextSessions_internal_value;
    return (PDCP_Parameters::maxNumberROHC_ContextSessions_Enum)0;
}

int PDCP_Parameters::maxNumberROHC_ContextSessions_SetValue(maxNumberROHC_ContextSessions_Enum value)
{
    maxNumberROHC_ContextSessions_internal_value = value;
    maxNumberROHC_ContextSessions_present = true;
    return 0;
}

int PDCP_Parameters::maxNumberROHC_ContextSessions_SetValue(std::string value)
{
    if("cs2" == value)
    {
        maxNumberROHC_ContextSessions_internal_value = k_maxNumberROHC_ContextSessions_cs2;
        maxNumberROHC_ContextSessions_present = true;
        return 0;
    }
    if("cs4" == value)
    {
        maxNumberROHC_ContextSessions_internal_value = k_maxNumberROHC_ContextSessions_cs4;
        maxNumberROHC_ContextSessions_present = true;
        return 0;
    }
    if("cs8" == value)
    {
        maxNumberROHC_ContextSessions_internal_value = k_maxNumberROHC_ContextSessions_cs8;
        maxNumberROHC_ContextSessions_present = true;
        return 0;
    }
    if("cs12" == value)
    {
        maxNumberROHC_ContextSessions_internal_value = k_maxNumberROHC_ContextSessions_cs12;
        maxNumberROHC_ContextSessions_present = true;
        return 0;
    }
    if("cs16" == value)
    {
        maxNumberROHC_ContextSessions_internal_value = k_maxNumberROHC_ContextSessions_cs16;
        maxNumberROHC_ContextSessions_present = true;
        return 0;
    }
    if("cs24" == value)
    {
        maxNumberROHC_ContextSessions_internal_value = k_maxNumberROHC_ContextSessions_cs24;
        maxNumberROHC_ContextSessions_present = true;
        return 0;
    }
    if("cs32" == value)
    {
        maxNumberROHC_ContextSessions_internal_value = k_maxNumberROHC_ContextSessions_cs32;
        maxNumberROHC_ContextSessions_present = true;
        return 0;
    }
    if("cs48" == value)
    {
        maxNumberROHC_ContextSessions_internal_value = k_maxNumberROHC_ContextSessions_cs48;
        maxNumberROHC_ContextSessions_present = true;
        return 0;
    }
    if("cs64" == value)
    {
        maxNumberROHC_ContextSessions_internal_value = k_maxNumberROHC_ContextSessions_cs64;
        maxNumberROHC_ContextSessions_present = true;
        return 0;
    }
    if("cs128" == value)
    {
        maxNumberROHC_ContextSessions_internal_value = k_maxNumberROHC_ContextSessions_cs128;
        maxNumberROHC_ContextSessions_present = true;
        return 0;
    }
    if("cs256" == value)
    {
        maxNumberROHC_ContextSessions_internal_value = k_maxNumberROHC_ContextSessions_cs256;
        maxNumberROHC_ContextSessions_present = true;
        return 0;
    }
    if("cs512" == value)
    {
        maxNumberROHC_ContextSessions_internal_value = k_maxNumberROHC_ContextSessions_cs512;
        maxNumberROHC_ContextSessions_present = true;
        return 0;
    }
    if("cs1024" == value)
    {
        maxNumberROHC_ContextSessions_internal_value = k_maxNumberROHC_ContextSessions_cs1024;
        maxNumberROHC_ContextSessions_present = true;
        return 0;
    }
    if("cs16384" == value)
    {
        maxNumberROHC_ContextSessions_internal_value = k_maxNumberROHC_ContextSessions_cs16384;
        maxNumberROHC_ContextSessions_present = true;
        return 0;
    }
    if("spare2" == value)
    {
        maxNumberROHC_ContextSessions_internal_value = k_maxNumberROHC_ContextSessions_spare2;
        maxNumberROHC_ContextSessions_present = true;
        return 0;
    }
    if("spare1" == value)
    {
        maxNumberROHC_ContextSessions_internal_value = k_maxNumberROHC_ContextSessions_spare1;
        maxNumberROHC_ContextSessions_present = true;
        return 0;
    }
    return 1;
}

std::string PDCP_Parameters::maxNumberROHC_ContextSessions_ValueToString(maxNumberROHC_ContextSessions_Enum value) const
{
    if(k_maxNumberROHC_ContextSessions_cs2 == value)
        return "cs2";
    if(k_maxNumberROHC_ContextSessions_cs4 == value)
        return "cs4";
    if(k_maxNumberROHC_ContextSessions_cs8 == value)
        return "cs8";
    if(k_maxNumberROHC_ContextSessions_cs12 == value)
        return "cs12";
    if(k_maxNumberROHC_ContextSessions_cs16 == value)
        return "cs16";
    if(k_maxNumberROHC_ContextSessions_cs24 == value)
        return "cs24";
    if(k_maxNumberROHC_ContextSessions_cs32 == value)
        return "cs32";
    if(k_maxNumberROHC_ContextSessions_cs48 == value)
        return "cs48";
    if(k_maxNumberROHC_ContextSessions_cs64 == value)
        return "cs64";
    if(k_maxNumberROHC_ContextSessions_cs128 == value)
        return "cs128";
    if(k_maxNumberROHC_ContextSessions_cs256 == value)
        return "cs256";
    if(k_maxNumberROHC_ContextSessions_cs512 == value)
        return "cs512";
    if(k_maxNumberROHC_ContextSessions_cs1024 == value)
        return "cs1024";
    if(k_maxNumberROHC_ContextSessions_cs16384 == value)
        return "cs16384";
    if(k_maxNumberROHC_ContextSessions_spare2 == value)
        return "spare2";
    if(k_maxNumberROHC_ContextSessions_spare1 == value)
        return "spare1";
    return "";
}

uint64_t PDCP_Parameters::maxNumberROHC_ContextSessions_NumberOfValues() const
{
    return 16;
}

PDCP_Parameters::maxNumberROHC_ContextSessions_Enum PDCP_Parameters::maxNumberROHC_ContextSessions_GetDefault() const
{
    return k_maxNumberROHC_ContextSessions_cs16;
}

std::string PDCP_Parameters::maxNumberROHC_ContextSessions_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "maxNumberROHC_ContextSessions = " + maxNumberROHC_ContextSessions_ValueToString(maxNumberROHC_ContextSessions_internal_value) + "\n";
    return out;
}

std::string PDCP_Parameters::maxNumberROHC_ContextSessions_ToStringNoNewLines() const
{
    std::string out = "maxNumberROHC_ContextSessions=" + maxNumberROHC_ContextSessions_ValueToString(maxNumberROHC_ContextSessions_internal_value) + ",";
    return out;
}

int PDCP_Parameters::maxNumberROHC_ContextSessions_Clear()
{
    maxNumberROHC_ContextSessions_present = false;
    return 0;
}

bool PDCP_Parameters::maxNumberROHC_ContextSessions_IsPresent() const
{
    return maxNumberROHC_ContextSessions_present;
}

