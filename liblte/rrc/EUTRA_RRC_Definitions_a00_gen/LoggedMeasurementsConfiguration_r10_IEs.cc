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

#include "LoggedMeasurementsConfiguration_r10_IEs.h"

#include <cmath>

int LoggedMeasurementsConfiguration_r10_IEs::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(areaConfiguration_r10_IsPresent());
    bits.push_back(0);

    // Fields
    {
        if(0 != absoluteTimeInfo_r10_Pack(bits))
        {
            printf("LoggedMeasurementsConfiguration_r10_IEs:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != loggingDuration_r10_Pack(bits))
        {
            printf("LoggedMeasurementsConfiguration_r10_IEs:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != loggingInterval_r10_Pack(bits))
        {
            printf("LoggedMeasurementsConfiguration_r10_IEs:: field pack failure\n");
            return -1;
        }
    }
    if(areaConfiguration_r10_IsPresent())
    {
        if(0 != areaConfiguration_r10.Pack(bits))
        {
            printf("LoggedMeasurementsConfiguration_r10_IEs:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int LoggedMeasurementsConfiguration_r10_IEs::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int LoggedMeasurementsConfiguration_r10_IEs::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("LoggedMeasurementsConfiguration_r10_IEs::Unpack() index out of bounds for optional indiator areaConfiguration_r10\n");
        return -1;
    }
    areaConfiguration_r10_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("LoggedMeasurementsConfiguration_r10_IEs::Unpack() index out of bounds for optional indiator nonCriticalExtension\n");
        return -1;
    }
    idx++;

    // Fields
    {
        if(0 != absoluteTimeInfo_r10_Unpack(bits, idx))
        {
            printf("LoggedMeasurementsConfiguration_r10_IEs:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != loggingDuration_r10_Unpack(bits, idx))
        {
            printf("LoggedMeasurementsConfiguration_r10_IEs:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != loggingInterval_r10_Unpack(bits, idx))
        {
            printf("LoggedMeasurementsConfiguration_r10_IEs:: field unpack failure\n");
            return -1;
        }
    }
    if(areaConfiguration_r10_present)
    {
        if(0 != areaConfiguration_r10.Unpack(bits, idx))
        {
            printf("LoggedMeasurementsConfiguration_r10_IEs:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string LoggedMeasurementsConfiguration_r10_IEs::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "LoggedMeasurementsConfiguration_r10_IEs:\n";
    out += absoluteTimeInfo_r10_ToString(indent+1);
    out += loggingDuration_r10_ToString(indent+1);
    out += loggingInterval_r10_ToString(indent+1);
    if(areaConfiguration_r10_IsPresent())
        out += areaConfiguration_r10_ToString(indent+1);
    return out;
}

std::string LoggedMeasurementsConfiguration_r10_IEs::ToStringNoNewLines() const
{
    std::string out = "LoggedMeasurementsConfiguration_r10_IEs:";
    out += absoluteTimeInfo_r10_ToStringNoNewLines();
    out += loggingDuration_r10_ToStringNoNewLines();
    out += loggingInterval_r10_ToStringNoNewLines();
    if(areaConfiguration_r10_IsPresent())
        out += areaConfiguration_r10_ToStringNoNewLines();
    return out;
}

int LoggedMeasurementsConfiguration_r10_IEs::absoluteTimeInfo_r10_Pack(std::vector<uint8_t> &bits)
{
    if(!absoluteTimeInfo_r10_present)
    {
        printf("LoggedMeasurementsConfiguration_r10_IEs::absoluteTimeInfo_r10_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 48;
    if(size < 48 || size > 48)
    {
        printf("LoggedMeasurementsConfiguration_r10_IEs::absoluteTimeInfo_r10_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((absoluteTimeInfo_r10_internal_value >> (48-i-1)) & 1);
    return 0;
}

int LoggedMeasurementsConfiguration_r10_IEs::absoluteTimeInfo_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return absoluteTimeInfo_r10_Unpack(bits, idx);
}

int LoggedMeasurementsConfiguration_r10_IEs::absoluteTimeInfo_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 48;
    if(size < 48 || size > 48)
    {
        printf("LoggedMeasurementsConfiguration_r10_IEs::absoluteTimeInfo_r10_Unpack() size failure\n");
        return -1;
    }
    absoluteTimeInfo_r10_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("LoggedMeasurementsConfiguration_r10_IEs::absoluteTimeInfo_r10_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        absoluteTimeInfo_r10_internal_value |= (uint64_t)bits[idx++] << (uint64_t)(48-i-1);
    absoluteTimeInfo_r10_present = true;
    return 0;
}

uint64_t LoggedMeasurementsConfiguration_r10_IEs::absoluteTimeInfo_r10_Value() const
{
    if(absoluteTimeInfo_r10_present)
        return absoluteTimeInfo_r10_internal_value;
    uint64_t tmp = 0;
    return tmp;
}

int LoggedMeasurementsConfiguration_r10_IEs::absoluteTimeInfo_r10_SetValue(uint64_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 48)
    {
        printf("LoggedMeasurementsConfiguration_r10_IEs::absoluteTimeInfo_r10_SetValue() size failure\n");
        return -1;
    }
    absoluteTimeInfo_r10_internal_value = value;
    absoluteTimeInfo_r10_present = true;
    return 0;
}

std::string LoggedMeasurementsConfiguration_r10_IEs::absoluteTimeInfo_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "absoluteTimeInfo_r10 = ";
    out += std::to_string(absoluteTimeInfo_r10_internal_value);
    out += "\n";
    return out;
}

std::string LoggedMeasurementsConfiguration_r10_IEs::absoluteTimeInfo_r10_ToStringNoNewLines() const
{
    std::string out = "absoluteTimeInfo_r10=";
    out += std::to_string(absoluteTimeInfo_r10_internal_value);
    out += ",";
    return out;
}

int LoggedMeasurementsConfiguration_r10_IEs::absoluteTimeInfo_r10_Clear()
{
    absoluteTimeInfo_r10_present = false;
    return 0;
}

bool LoggedMeasurementsConfiguration_r10_IEs::absoluteTimeInfo_r10_IsPresent() const
{
    return absoluteTimeInfo_r10_present;
}

int LoggedMeasurementsConfiguration_r10_IEs::loggingDuration_r10_Pack(std::vector<uint8_t> &bits)
{
    if(!loggingDuration_r10_present)
    {
        printf("LoggedMeasurementsConfiguration_r10_IEs::loggingDuration_r10_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 3;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((loggingDuration_r10_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int LoggedMeasurementsConfiguration_r10_IEs::loggingDuration_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return loggingDuration_r10_Unpack(bits, idx);
}

int LoggedMeasurementsConfiguration_r10_IEs::loggingDuration_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 3;
    if((idx + N_bits) > bits.size())
    {
        printf("LoggedMeasurementsConfiguration_r10_IEs::loggingDuration_r10_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 7)
    {
        printf("LoggedMeasurementsConfiguration_r10_IEs::loggingDuration_r10_Unpack() max failure\n");
        return -1;
    }
    loggingDuration_r10_internal_value = (loggingDuration_r10_Enum)packed_val;
    loggingDuration_r10_present = true;
    return 0;
}

LoggedMeasurementsConfiguration_r10_IEs::loggingDuration_r10_Enum LoggedMeasurementsConfiguration_r10_IEs::loggingDuration_r10_Value() const
{
    if(loggingDuration_r10_present)
        return loggingDuration_r10_internal_value;
    return (LoggedMeasurementsConfiguration_r10_IEs::loggingDuration_r10_Enum)0;
}

int LoggedMeasurementsConfiguration_r10_IEs::loggingDuration_r10_SetValue(loggingDuration_r10_Enum value)
{
    loggingDuration_r10_internal_value = value;
    loggingDuration_r10_present = true;
    return 0;
}

int LoggedMeasurementsConfiguration_r10_IEs::loggingDuration_r10_SetValue(std::string value)
{
    if("min10" == value)
    {
        loggingDuration_r10_internal_value = k_loggingDuration_r10_min10;
        loggingDuration_r10_present = true;
        return 0;
    }
    if("min20" == value)
    {
        loggingDuration_r10_internal_value = k_loggingDuration_r10_min20;
        loggingDuration_r10_present = true;
        return 0;
    }
    if("min40" == value)
    {
        loggingDuration_r10_internal_value = k_loggingDuration_r10_min40;
        loggingDuration_r10_present = true;
        return 0;
    }
    if("min60" == value)
    {
        loggingDuration_r10_internal_value = k_loggingDuration_r10_min60;
        loggingDuration_r10_present = true;
        return 0;
    }
    if("min90" == value)
    {
        loggingDuration_r10_internal_value = k_loggingDuration_r10_min90;
        loggingDuration_r10_present = true;
        return 0;
    }
    if("min120" == value)
    {
        loggingDuration_r10_internal_value = k_loggingDuration_r10_min120;
        loggingDuration_r10_present = true;
        return 0;
    }
    if("spare2" == value)
    {
        loggingDuration_r10_internal_value = k_loggingDuration_r10_spare2;
        loggingDuration_r10_present = true;
        return 0;
    }
    if("spare1" == value)
    {
        loggingDuration_r10_internal_value = k_loggingDuration_r10_spare1;
        loggingDuration_r10_present = true;
        return 0;
    }
    return 1;
}

std::string LoggedMeasurementsConfiguration_r10_IEs::loggingDuration_r10_ValueToString(loggingDuration_r10_Enum value) const
{
    if(k_loggingDuration_r10_min10 == value)
        return "min10";
    if(k_loggingDuration_r10_min20 == value)
        return "min20";
    if(k_loggingDuration_r10_min40 == value)
        return "min40";
    if(k_loggingDuration_r10_min60 == value)
        return "min60";
    if(k_loggingDuration_r10_min90 == value)
        return "min90";
    if(k_loggingDuration_r10_min120 == value)
        return "min120";
    if(k_loggingDuration_r10_spare2 == value)
        return "spare2";
    if(k_loggingDuration_r10_spare1 == value)
        return "spare1";
    return "";
}

uint64_t LoggedMeasurementsConfiguration_r10_IEs::loggingDuration_r10_NumberOfValues() const
{
    return 8;
}

std::string LoggedMeasurementsConfiguration_r10_IEs::loggingDuration_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "loggingDuration_r10 = " + loggingDuration_r10_ValueToString(loggingDuration_r10_internal_value) + "\n";
    return out;
}

std::string LoggedMeasurementsConfiguration_r10_IEs::loggingDuration_r10_ToStringNoNewLines() const
{
    std::string out = "loggingDuration_r10=" + loggingDuration_r10_ValueToString(loggingDuration_r10_internal_value) + ",";
    return out;
}

int LoggedMeasurementsConfiguration_r10_IEs::loggingDuration_r10_Clear()
{
    loggingDuration_r10_present = false;
    return 0;
}

bool LoggedMeasurementsConfiguration_r10_IEs::loggingDuration_r10_IsPresent() const
{
    return loggingDuration_r10_present;
}

int LoggedMeasurementsConfiguration_r10_IEs::loggingInterval_r10_Pack(std::vector<uint8_t> &bits)
{
    if(!loggingInterval_r10_present)
    {
        printf("LoggedMeasurementsConfiguration_r10_IEs::loggingInterval_r10_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 3;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((loggingInterval_r10_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int LoggedMeasurementsConfiguration_r10_IEs::loggingInterval_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return loggingInterval_r10_Unpack(bits, idx);
}

int LoggedMeasurementsConfiguration_r10_IEs::loggingInterval_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 3;
    if((idx + N_bits) > bits.size())
    {
        printf("LoggedMeasurementsConfiguration_r10_IEs::loggingInterval_r10_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 7)
    {
        printf("LoggedMeasurementsConfiguration_r10_IEs::loggingInterval_r10_Unpack() max failure\n");
        return -1;
    }
    loggingInterval_r10_internal_value = (loggingInterval_r10_Enum)packed_val;
    loggingInterval_r10_present = true;
    return 0;
}

LoggedMeasurementsConfiguration_r10_IEs::loggingInterval_r10_Enum LoggedMeasurementsConfiguration_r10_IEs::loggingInterval_r10_Value() const
{
    if(loggingInterval_r10_present)
        return loggingInterval_r10_internal_value;
    return (LoggedMeasurementsConfiguration_r10_IEs::loggingInterval_r10_Enum)0;
}

int LoggedMeasurementsConfiguration_r10_IEs::loggingInterval_r10_SetValue(loggingInterval_r10_Enum value)
{
    loggingInterval_r10_internal_value = value;
    loggingInterval_r10_present = true;
    return 0;
}

int LoggedMeasurementsConfiguration_r10_IEs::loggingInterval_r10_SetValue(std::string value)
{
    if("ms1280" == value)
    {
        loggingInterval_r10_internal_value = k_loggingInterval_r10_ms1280;
        loggingInterval_r10_present = true;
        return 0;
    }
    if("ms2560" == value)
    {
        loggingInterval_r10_internal_value = k_loggingInterval_r10_ms2560;
        loggingInterval_r10_present = true;
        return 0;
    }
    if("ms5120" == value)
    {
        loggingInterval_r10_internal_value = k_loggingInterval_r10_ms5120;
        loggingInterval_r10_present = true;
        return 0;
    }
    if("ms10240" == value)
    {
        loggingInterval_r10_internal_value = k_loggingInterval_r10_ms10240;
        loggingInterval_r10_present = true;
        return 0;
    }
    if("ms20480" == value)
    {
        loggingInterval_r10_internal_value = k_loggingInterval_r10_ms20480;
        loggingInterval_r10_present = true;
        return 0;
    }
    if("ms30720" == value)
    {
        loggingInterval_r10_internal_value = k_loggingInterval_r10_ms30720;
        loggingInterval_r10_present = true;
        return 0;
    }
    if("ms40960" == value)
    {
        loggingInterval_r10_internal_value = k_loggingInterval_r10_ms40960;
        loggingInterval_r10_present = true;
        return 0;
    }
    if("ms61440" == value)
    {
        loggingInterval_r10_internal_value = k_loggingInterval_r10_ms61440;
        loggingInterval_r10_present = true;
        return 0;
    }
    return 1;
}

std::string LoggedMeasurementsConfiguration_r10_IEs::loggingInterval_r10_ValueToString(loggingInterval_r10_Enum value) const
{
    if(k_loggingInterval_r10_ms1280 == value)
        return "ms1280";
    if(k_loggingInterval_r10_ms2560 == value)
        return "ms2560";
    if(k_loggingInterval_r10_ms5120 == value)
        return "ms5120";
    if(k_loggingInterval_r10_ms10240 == value)
        return "ms10240";
    if(k_loggingInterval_r10_ms20480 == value)
        return "ms20480";
    if(k_loggingInterval_r10_ms30720 == value)
        return "ms30720";
    if(k_loggingInterval_r10_ms40960 == value)
        return "ms40960";
    if(k_loggingInterval_r10_ms61440 == value)
        return "ms61440";
    return "";
}

uint64_t LoggedMeasurementsConfiguration_r10_IEs::loggingInterval_r10_NumberOfValues() const
{
    return 8;
}

std::string LoggedMeasurementsConfiguration_r10_IEs::loggingInterval_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "loggingInterval_r10 = " + loggingInterval_r10_ValueToString(loggingInterval_r10_internal_value) + "\n";
    return out;
}

std::string LoggedMeasurementsConfiguration_r10_IEs::loggingInterval_r10_ToStringNoNewLines() const
{
    std::string out = "loggingInterval_r10=" + loggingInterval_r10_ValueToString(loggingInterval_r10_internal_value) + ",";
    return out;
}

int LoggedMeasurementsConfiguration_r10_IEs::loggingInterval_r10_Clear()
{
    loggingInterval_r10_present = false;
    return 0;
}

bool LoggedMeasurementsConfiguration_r10_IEs::loggingInterval_r10_IsPresent() const
{
    return loggingInterval_r10_present;
}

AreaConfiguration_r10* LoggedMeasurementsConfiguration_r10_IEs::areaConfiguration_r10_Set()
{
    areaConfiguration_r10_present = true;
    return &areaConfiguration_r10;
}

int LoggedMeasurementsConfiguration_r10_IEs::areaConfiguration_r10_Set(AreaConfiguration_r10 &value)
{
    areaConfiguration_r10_present = true;
    areaConfiguration_r10 = value;
    return 0;
}

const AreaConfiguration_r10& LoggedMeasurementsConfiguration_r10_IEs::areaConfiguration_r10_Get() const
{
    return areaConfiguration_r10;
}

std::string LoggedMeasurementsConfiguration_r10_IEs::areaConfiguration_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "areaConfiguration_r10:\n";
    out += areaConfiguration_r10.ToString(indent+1);
    return out;
}

std::string LoggedMeasurementsConfiguration_r10_IEs::areaConfiguration_r10_ToStringNoNewLines() const
{
    std::string out = "areaConfiguration_r10:";
    out += areaConfiguration_r10.ToStringNoNewLines();
    return out;
}

int LoggedMeasurementsConfiguration_r10_IEs::areaConfiguration_r10_Clear()
{
    areaConfiguration_r10_present = false;
    return 0;
}

bool LoggedMeasurementsConfiguration_r10_IEs::areaConfiguration_r10_IsPresent() const
{
    return areaConfiguration_r10_present;
}

