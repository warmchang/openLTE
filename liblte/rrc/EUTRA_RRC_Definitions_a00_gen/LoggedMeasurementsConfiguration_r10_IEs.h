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

#ifndef __LoggedMeasurementsConfiguration_r10_IEs_H__
#define __LoggedMeasurementsConfiguration_r10_IEs_H__

#include "AreaConfiguration_r10.h"

#include <array>
#include <cstdint>
#include <vector>

class LoggedMeasurementsConfiguration_r10_IEs
{
public:
    LoggedMeasurementsConfiguration_r10_IEs() : absoluteTimeInfo_r10_present{false}, loggingDuration_r10_present{false}, loggingInterval_r10_present{false}, areaConfiguration_r10_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // absoluteTimeInfo-r10
public:
    int absoluteTimeInfo_r10_Pack(std::vector<uint8_t> &bits);
    int absoluteTimeInfo_r10_Unpack(std::vector<uint8_t> bits);
    int absoluteTimeInfo_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    uint64_t absoluteTimeInfo_r10_Value() const;
    int absoluteTimeInfo_r10_SetValue(uint64_t value);
    std::string absoluteTimeInfo_r10_ToString(uint32_t indent) const;
    std::string absoluteTimeInfo_r10_ToStringNoNewLines() const;
    int absoluteTimeInfo_r10_Clear();
    bool absoluteTimeInfo_r10_IsPresent() const;
private:
    bool absoluteTimeInfo_r10_present;
    uint64_t absoluteTimeInfo_r10_internal_value;

    // loggingDuration-r10
public:
    enum loggingDuration_r10_Enum {
        k_loggingDuration_r10_min10 = 0,
        k_loggingDuration_r10_min20,
        k_loggingDuration_r10_min40,
        k_loggingDuration_r10_min60,
        k_loggingDuration_r10_min90,
        k_loggingDuration_r10_min120,
        k_loggingDuration_r10_spare2,
        k_loggingDuration_r10_spare1,
    };
    int loggingDuration_r10_Pack(std::vector<uint8_t> &bits);
    int loggingDuration_r10_Unpack(std::vector<uint8_t> bits);
    int loggingDuration_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    loggingDuration_r10_Enum loggingDuration_r10_Value() const;
    int loggingDuration_r10_SetValue(loggingDuration_r10_Enum value);
    int loggingDuration_r10_SetValue(std::string value);
    std::string loggingDuration_r10_ValueToString(loggingDuration_r10_Enum value) const;
    uint64_t loggingDuration_r10_NumberOfValues() const;
    std::string loggingDuration_r10_ToString(uint32_t indent) const;
    std::string loggingDuration_r10_ToStringNoNewLines() const;
    int loggingDuration_r10_Clear();
    bool loggingDuration_r10_IsPresent() const;
private:
    bool loggingDuration_r10_present;
    loggingDuration_r10_Enum loggingDuration_r10_internal_value;

    // loggingInterval-r10
public:
    enum loggingInterval_r10_Enum {
        k_loggingInterval_r10_ms1280 = 0,
        k_loggingInterval_r10_ms2560,
        k_loggingInterval_r10_ms5120,
        k_loggingInterval_r10_ms10240,
        k_loggingInterval_r10_ms20480,
        k_loggingInterval_r10_ms30720,
        k_loggingInterval_r10_ms40960,
        k_loggingInterval_r10_ms61440,
    };
    int loggingInterval_r10_Pack(std::vector<uint8_t> &bits);
    int loggingInterval_r10_Unpack(std::vector<uint8_t> bits);
    int loggingInterval_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    loggingInterval_r10_Enum loggingInterval_r10_Value() const;
    int loggingInterval_r10_SetValue(loggingInterval_r10_Enum value);
    int loggingInterval_r10_SetValue(std::string value);
    std::string loggingInterval_r10_ValueToString(loggingInterval_r10_Enum value) const;
    uint64_t loggingInterval_r10_NumberOfValues() const;
    std::string loggingInterval_r10_ToString(uint32_t indent) const;
    std::string loggingInterval_r10_ToStringNoNewLines() const;
    int loggingInterval_r10_Clear();
    bool loggingInterval_r10_IsPresent() const;
private:
    bool loggingInterval_r10_present;
    loggingInterval_r10_Enum loggingInterval_r10_internal_value;

    // areaConfiguration-r10
public:
    AreaConfiguration_r10* areaConfiguration_r10_Set();
    int areaConfiguration_r10_Set(AreaConfiguration_r10 &value);
    const AreaConfiguration_r10& areaConfiguration_r10_Get() const;
    std::string areaConfiguration_r10_ToString(uint32_t indent) const;
    std::string areaConfiguration_r10_ToStringNoNewLines() const;
    int areaConfiguration_r10_Clear();
    bool areaConfiguration_r10_IsPresent() const;
private:
    bool areaConfiguration_r10_present;
    AreaConfiguration_r10 areaConfiguration_r10;

    // nonCriticalExtension

};

#endif
