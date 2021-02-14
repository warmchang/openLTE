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

#include "LogMeasReport_r10.h"

#include <cmath>

int LogMeasReport_r10::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator
    bits.push_back(0);

    // Optional indicators
    bits.push_back(mdt_MeasurementInfoList_r10_IsPresent());
    bits.push_back(logMeasAvailable_r10_IsPresent());

    // Fields
    {
        if(0 != absoluteTimeStamp_r10_Pack(bits))
        {
            printf("LogMeasReport_r10:: field pack failure\n");
            return -1;
        }
    }
    if(mdt_MeasurementInfoList_r10_IsPresent())
    {
        if(0 != mdt_MeasurementInfoList_r10.Pack(bits))
        {
            printf("LogMeasReport_r10:: field pack failure\n");
            return -1;
        }
    }
    if(logMeasAvailable_r10_IsPresent())
    {
        if(0 != logMeasAvailable_r10_Pack(bits))
        {
            printf("LogMeasReport_r10:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int LogMeasReport_r10::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int LogMeasReport_r10::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("LogMeasReport_r10::Unpack() index out of bounds for extension\n");
        return -1;
    }
    idx++;

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("LogMeasReport_r10::Unpack() index out of bounds for optional indiator mdt_MeasurementInfoList_r10\n");
        return -1;
    }
    mdt_MeasurementInfoList_r10_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("LogMeasReport_r10::Unpack() index out of bounds for optional indiator logMeasAvailable_r10\n");
        return -1;
    }
    logMeasAvailable_r10_present = bits[idx++];

    // Fields
    {
        if(0 != absoluteTimeStamp_r10_Unpack(bits, idx))
        {
            printf("LogMeasReport_r10:: field unpack failure\n");
            return -1;
        }
    }
    if(mdt_MeasurementInfoList_r10_present)
    {
        if(0 != mdt_MeasurementInfoList_r10.Unpack(bits, idx))
        {
            printf("LogMeasReport_r10:: field unpack failure\n");
            return -1;
        }
    }
    if(logMeasAvailable_r10_present)
    {
        if(0 != logMeasAvailable_r10_Unpack(bits, idx))
        {
            printf("LogMeasReport_r10:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string LogMeasReport_r10::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "LogMeasReport_r10:\n";
    out += absoluteTimeStamp_r10_ToString(indent+1);
    if(mdt_MeasurementInfoList_r10_IsPresent())
        out += mdt_MeasurementInfoList_r10_ToString(indent+1);
    if(logMeasAvailable_r10_IsPresent())
        out += logMeasAvailable_r10_ToString(indent+1);
    return out;
}

std::string LogMeasReport_r10::ToStringNoNewLines() const
{
    std::string out = "LogMeasReport_r10:";
    out += absoluteTimeStamp_r10_ToStringNoNewLines();
    if(mdt_MeasurementInfoList_r10_IsPresent())
        out += mdt_MeasurementInfoList_r10_ToStringNoNewLines();
    if(logMeasAvailable_r10_IsPresent())
        out += logMeasAvailable_r10_ToStringNoNewLines();
    return out;
}

int LogMeasReport_r10::absoluteTimeStamp_r10_Pack(std::vector<uint8_t> &bits)
{
    if(!absoluteTimeStamp_r10_present)
    {
        printf("LogMeasReport_r10::absoluteTimeStamp_r10_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 48;
    if(size < 48 || size > 48)
    {
        printf("LogMeasReport_r10::absoluteTimeStamp_r10_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((absoluteTimeStamp_r10_internal_value >> (48-i-1)) & 1);
    return 0;
}

int LogMeasReport_r10::absoluteTimeStamp_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return absoluteTimeStamp_r10_Unpack(bits, idx);
}

int LogMeasReport_r10::absoluteTimeStamp_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 48;
    if(size < 48 || size > 48)
    {
        printf("LogMeasReport_r10::absoluteTimeStamp_r10_Unpack() size failure\n");
        return -1;
    }
    absoluteTimeStamp_r10_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("LogMeasReport_r10::absoluteTimeStamp_r10_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        absoluteTimeStamp_r10_internal_value |= (uint64_t)bits[idx++] << (uint64_t)(48-i-1);
    absoluteTimeStamp_r10_present = true;
    return 0;
}

uint64_t LogMeasReport_r10::absoluteTimeStamp_r10_Value() const
{
    if(absoluteTimeStamp_r10_present)
        return absoluteTimeStamp_r10_internal_value;
    uint64_t tmp = 0;
    return tmp;
}

int LogMeasReport_r10::absoluteTimeStamp_r10_SetValue(uint64_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 48)
    {
        printf("LogMeasReport_r10::absoluteTimeStamp_r10_SetValue() size failure\n");
        return -1;
    }
    absoluteTimeStamp_r10_internal_value = value;
    absoluteTimeStamp_r10_present = true;
    return 0;
}

std::string LogMeasReport_r10::absoluteTimeStamp_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "absoluteTimeStamp_r10 = ";
    out += std::to_string(absoluteTimeStamp_r10_internal_value);
    out += "\n";
    return out;
}

std::string LogMeasReport_r10::absoluteTimeStamp_r10_ToStringNoNewLines() const
{
    std::string out = "absoluteTimeStamp_r10=";
    out += std::to_string(absoluteTimeStamp_r10_internal_value);
    out += ",";
    return out;
}

int LogMeasReport_r10::absoluteTimeStamp_r10_Clear()
{
    absoluteTimeStamp_r10_present = false;
    return 0;
}

bool LogMeasReport_r10::absoluteTimeStamp_r10_IsPresent() const
{
    return absoluteTimeStamp_r10_present;
}

MDT_MeasurementInfoList_r10* LogMeasReport_r10::mdt_MeasurementInfoList_r10_Set()
{
    mdt_MeasurementInfoList_r10_present = true;
    return &mdt_MeasurementInfoList_r10;
}

int LogMeasReport_r10::mdt_MeasurementInfoList_r10_Set(MDT_MeasurementInfoList_r10 &value)
{
    mdt_MeasurementInfoList_r10_present = true;
    mdt_MeasurementInfoList_r10 = value;
    return 0;
}

const MDT_MeasurementInfoList_r10& LogMeasReport_r10::mdt_MeasurementInfoList_r10_Get() const
{
    return mdt_MeasurementInfoList_r10;
}

std::string LogMeasReport_r10::mdt_MeasurementInfoList_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "mdt_MeasurementInfoList_r10:\n";
    out += mdt_MeasurementInfoList_r10.ToString(indent+1);
    return out;
}

std::string LogMeasReport_r10::mdt_MeasurementInfoList_r10_ToStringNoNewLines() const
{
    std::string out = "mdt_MeasurementInfoList_r10:";
    out += mdt_MeasurementInfoList_r10.ToStringNoNewLines();
    return out;
}

int LogMeasReport_r10::mdt_MeasurementInfoList_r10_Clear()
{
    mdt_MeasurementInfoList_r10_present = false;
    return 0;
}

bool LogMeasReport_r10::mdt_MeasurementInfoList_r10_IsPresent() const
{
    return mdt_MeasurementInfoList_r10_present;
}

int LogMeasReport_r10::logMeasAvailable_r10_Pack(std::vector<uint8_t> &bits)
{
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((logMeasAvailable_r10_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int LogMeasReport_r10::logMeasAvailable_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return logMeasAvailable_r10_Unpack(bits, idx);
}

int LogMeasReport_r10::logMeasAvailable_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("LogMeasReport_r10::logMeasAvailable_r10_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 0)
    {
        printf("LogMeasReport_r10::logMeasAvailable_r10_Unpack() max failure\n");
        return -1;
    }
    logMeasAvailable_r10_internal_value = (logMeasAvailable_r10_Enum)packed_val;
    logMeasAvailable_r10_present = true;
    return 0;
}

LogMeasReport_r10::logMeasAvailable_r10_Enum LogMeasReport_r10::logMeasAvailable_r10_Value() const
{
    if(logMeasAvailable_r10_present)
        return logMeasAvailable_r10_internal_value;
    return (LogMeasReport_r10::logMeasAvailable_r10_Enum)0;
}

int LogMeasReport_r10::logMeasAvailable_r10_SetValue(logMeasAvailable_r10_Enum value)
{
    logMeasAvailable_r10_internal_value = value;
    logMeasAvailable_r10_present = true;
    return 0;
}

int LogMeasReport_r10::logMeasAvailable_r10_SetValue(std::string value)
{
    if("true" == value)
    {
        logMeasAvailable_r10_internal_value = k_logMeasAvailable_r10_true;
        logMeasAvailable_r10_present = true;
        return 0;
    }
    return 1;
}

std::string LogMeasReport_r10::logMeasAvailable_r10_ValueToString(logMeasAvailable_r10_Enum value) const
{
    if(k_logMeasAvailable_r10_true == value)
        return "true";
    return "";
}

uint64_t LogMeasReport_r10::logMeasAvailable_r10_NumberOfValues() const
{
    return 1;
}

std::string LogMeasReport_r10::logMeasAvailable_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "logMeasAvailable_r10 = " + logMeasAvailable_r10_ValueToString(logMeasAvailable_r10_internal_value) + "\n";
    return out;
}

std::string LogMeasReport_r10::logMeasAvailable_r10_ToStringNoNewLines() const
{
    std::string out = "logMeasAvailable_r10=" + logMeasAvailable_r10_ValueToString(logMeasAvailable_r10_internal_value) + ",";
    return out;
}

int LogMeasReport_r10::logMeasAvailable_r10_Clear()
{
    logMeasAvailable_r10_present = false;
    return 0;
}

bool LogMeasReport_r10::logMeasAvailable_r10_IsPresent() const
{
    return logMeasAvailable_r10_present;
}

