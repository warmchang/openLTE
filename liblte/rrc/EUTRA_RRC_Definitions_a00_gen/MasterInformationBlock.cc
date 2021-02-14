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

#include "MasterInformationBlock.h"

#include <cmath>

int MasterInformationBlock::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != dl_Bandwidth_Pack(bits))
        {
            printf("MasterInformationBlock:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != phich_Config.Pack(bits))
        {
            printf("MasterInformationBlock:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != systemFrameNumber_Pack(bits))
        {
            printf("MasterInformationBlock:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != spare_Pack(bits))
        {
            printf("MasterInformationBlock:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int MasterInformationBlock::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int MasterInformationBlock::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != dl_Bandwidth_Unpack(bits, idx))
        {
            printf("MasterInformationBlock:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != phich_Config.Unpack(bits, idx))
        {
            printf("MasterInformationBlock:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != systemFrameNumber_Unpack(bits, idx))
        {
            printf("MasterInformationBlock:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != spare_Unpack(bits, idx))
        {
            printf("MasterInformationBlock:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string MasterInformationBlock::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "MasterInformationBlock:\n";
    out += dl_Bandwidth_ToString(indent+1);
    out += phich_Config_ToString(indent+1);
    out += systemFrameNumber_ToString(indent+1);
    out += spare_ToString(indent+1);
    return out;
}

std::string MasterInformationBlock::ToStringNoNewLines() const
{
    std::string out = "MasterInformationBlock:";
    out += dl_Bandwidth_ToStringNoNewLines();
    out += phich_Config_ToStringNoNewLines();
    out += systemFrameNumber_ToStringNoNewLines();
    out += spare_ToStringNoNewLines();
    return out;
}

int MasterInformationBlock::dl_Bandwidth_Pack(std::vector<uint8_t> &bits)
{
    if(!dl_Bandwidth_present)
    {
        printf("MasterInformationBlock::dl_Bandwidth_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 3;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((dl_Bandwidth_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int MasterInformationBlock::dl_Bandwidth_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return dl_Bandwidth_Unpack(bits, idx);
}

int MasterInformationBlock::dl_Bandwidth_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 3;
    if((idx + N_bits) > bits.size())
    {
        printf("MasterInformationBlock::dl_Bandwidth_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 5)
    {
        printf("MasterInformationBlock::dl_Bandwidth_Unpack() max failure\n");
        return -1;
    }
    dl_Bandwidth_internal_value = (dl_Bandwidth_Enum)packed_val;
    dl_Bandwidth_present = true;
    return 0;
}

MasterInformationBlock::dl_Bandwidth_Enum MasterInformationBlock::dl_Bandwidth_Value() const
{
    if(dl_Bandwidth_present)
        return dl_Bandwidth_internal_value;
    return (MasterInformationBlock::dl_Bandwidth_Enum)0;
}

int MasterInformationBlock::dl_Bandwidth_SetValue(dl_Bandwidth_Enum value)
{
    dl_Bandwidth_internal_value = value;
    dl_Bandwidth_present = true;
    return 0;
}

int MasterInformationBlock::dl_Bandwidth_SetValue(std::string value)
{
    if("n6" == value)
    {
        dl_Bandwidth_internal_value = k_dl_Bandwidth_n6;
        dl_Bandwidth_present = true;
        return 0;
    }
    if("n15" == value)
    {
        dl_Bandwidth_internal_value = k_dl_Bandwidth_n15;
        dl_Bandwidth_present = true;
        return 0;
    }
    if("n25" == value)
    {
        dl_Bandwidth_internal_value = k_dl_Bandwidth_n25;
        dl_Bandwidth_present = true;
        return 0;
    }
    if("n50" == value)
    {
        dl_Bandwidth_internal_value = k_dl_Bandwidth_n50;
        dl_Bandwidth_present = true;
        return 0;
    }
    if("n75" == value)
    {
        dl_Bandwidth_internal_value = k_dl_Bandwidth_n75;
        dl_Bandwidth_present = true;
        return 0;
    }
    if("n100" == value)
    {
        dl_Bandwidth_internal_value = k_dl_Bandwidth_n100;
        dl_Bandwidth_present = true;
        return 0;
    }
    return 1;
}

std::string MasterInformationBlock::dl_Bandwidth_ValueToString(dl_Bandwidth_Enum value) const
{
    if(k_dl_Bandwidth_n6 == value)
        return "n6";
    if(k_dl_Bandwidth_n15 == value)
        return "n15";
    if(k_dl_Bandwidth_n25 == value)
        return "n25";
    if(k_dl_Bandwidth_n50 == value)
        return "n50";
    if(k_dl_Bandwidth_n75 == value)
        return "n75";
    if(k_dl_Bandwidth_n100 == value)
        return "n100";
    return "";
}

uint64_t MasterInformationBlock::dl_Bandwidth_NumberOfValues() const
{
    return 6;
}

std::string MasterInformationBlock::dl_Bandwidth_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "dl_Bandwidth = " + dl_Bandwidth_ValueToString(dl_Bandwidth_internal_value) + "\n";
    return out;
}

std::string MasterInformationBlock::dl_Bandwidth_ToStringNoNewLines() const
{
    std::string out = "dl_Bandwidth=" + dl_Bandwidth_ValueToString(dl_Bandwidth_internal_value) + ",";
    return out;
}

int MasterInformationBlock::dl_Bandwidth_Clear()
{
    dl_Bandwidth_present = false;
    return 0;
}

bool MasterInformationBlock::dl_Bandwidth_IsPresent() const
{
    return dl_Bandwidth_present;
}

PHICH_Config* MasterInformationBlock::phich_Config_Set()
{
    phich_Config_present = true;
    return &phich_Config;
}

int MasterInformationBlock::phich_Config_Set(PHICH_Config &value)
{
    phich_Config_present = true;
    phich_Config = value;
    return 0;
}

const PHICH_Config& MasterInformationBlock::phich_Config_Get() const
{
    return phich_Config;
}

std::string MasterInformationBlock::phich_Config_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "phich_Config:\n";
    out += phich_Config.ToString(indent+1);
    return out;
}

std::string MasterInformationBlock::phich_Config_ToStringNoNewLines() const
{
    std::string out = "phich_Config:";
    out += phich_Config.ToStringNoNewLines();
    return out;
}

int MasterInformationBlock::phich_Config_Clear()
{
    phich_Config_present = false;
    return 0;
}

bool MasterInformationBlock::phich_Config_IsPresent() const
{
    return phich_Config_present;
}

int MasterInformationBlock::systemFrameNumber_Pack(std::vector<uint8_t> &bits)
{
    if(!systemFrameNumber_present)
    {
        printf("MasterInformationBlock::systemFrameNumber_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 8;
    if(size < 8 || size > 8)
    {
        printf("MasterInformationBlock::systemFrameNumber_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((systemFrameNumber_internal_value >> (8-i-1)) & 1);
    return 0;
}

int MasterInformationBlock::systemFrameNumber_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return systemFrameNumber_Unpack(bits, idx);
}

int MasterInformationBlock::systemFrameNumber_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 8;
    if(size < 8 || size > 8)
    {
        printf("MasterInformationBlock::systemFrameNumber_Unpack() size failure\n");
        return -1;
    }
    systemFrameNumber_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("MasterInformationBlock::systemFrameNumber_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        systemFrameNumber_internal_value |= (uint8_t)bits[idx++] << (uint8_t)(8-i-1);
    systemFrameNumber_present = true;
    return 0;
}

uint8_t MasterInformationBlock::systemFrameNumber_Value() const
{
    if(systemFrameNumber_present)
        return systemFrameNumber_internal_value;
    uint8_t tmp = 0;
    return tmp;
}

int MasterInformationBlock::systemFrameNumber_SetValue(uint8_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 8)
    {
        printf("MasterInformationBlock::systemFrameNumber_SetValue() size failure\n");
        return -1;
    }
    systemFrameNumber_internal_value = value;
    systemFrameNumber_present = true;
    return 0;
}

std::string MasterInformationBlock::systemFrameNumber_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "systemFrameNumber = ";
    out += std::to_string(systemFrameNumber_internal_value);
    out += "\n";
    return out;
}

std::string MasterInformationBlock::systemFrameNumber_ToStringNoNewLines() const
{
    std::string out = "systemFrameNumber=";
    out += std::to_string(systemFrameNumber_internal_value);
    out += ",";
    return out;
}

int MasterInformationBlock::systemFrameNumber_Clear()
{
    systemFrameNumber_present = false;
    return 0;
}

bool MasterInformationBlock::systemFrameNumber_IsPresent() const
{
    return systemFrameNumber_present;
}

int MasterInformationBlock::spare_Pack(std::vector<uint8_t> &bits)
{
    if(!spare_present)
    {
        printf("MasterInformationBlock::spare_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 10;
    if(size < 10 || size > 10)
    {
        printf("MasterInformationBlock::spare_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((spare_internal_value >> (10-i-1)) & 1);
    return 0;
}

int MasterInformationBlock::spare_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return spare_Unpack(bits, idx);
}

int MasterInformationBlock::spare_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 10;
    if(size < 10 || size > 10)
    {
        printf("MasterInformationBlock::spare_Unpack() size failure\n");
        return -1;
    }
    spare_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("MasterInformationBlock::spare_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        spare_internal_value |= (uint16_t)bits[idx++] << (uint16_t)(10-i-1);
    spare_present = true;
    return 0;
}

uint16_t MasterInformationBlock::spare_Value() const
{
    if(spare_present)
        return spare_internal_value;
    uint16_t tmp = 0;
    return tmp;
}

int MasterInformationBlock::spare_SetValue(uint16_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 10)
    {
        printf("MasterInformationBlock::spare_SetValue() size failure\n");
        return -1;
    }
    spare_internal_value = value;
    spare_present = true;
    return 0;
}

std::string MasterInformationBlock::spare_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "spare = ";
    out += std::to_string(spare_internal_value);
    out += "\n";
    return out;
}

std::string MasterInformationBlock::spare_ToStringNoNewLines() const
{
    std::string out = "spare=";
    out += std::to_string(spare_internal_value);
    out += ",";
    return out;
}

int MasterInformationBlock::spare_Clear()
{
    spare_present = false;
    return 0;
}

bool MasterInformationBlock::spare_IsPresent() const
{
    return spare_present;
}

