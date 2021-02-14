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

#ifndef __PRACH_ConfigInfo_H__
#define __PRACH_ConfigInfo_H__

#include <array>
#include <cstdint>
#include <vector>

class PRACH_ConfigInfo
{
public:
    PRACH_ConfigInfo() : prach_ConfigIndex_present{false}, highSpeedFlag_present{false}, zeroCorrelationZoneConfig_present{false}, prach_FreqOffset_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // prach-ConfigIndex
public:
    int prach_ConfigIndex_Pack(std::vector<uint8_t> &bits);
    int prach_ConfigIndex_Unpack(std::vector<uint8_t> bits);
    int prach_ConfigIndex_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t prach_ConfigIndex_Value() const;
    int prach_ConfigIndex_SetValue(int64_t value);
    std::string prach_ConfigIndex_ToString(uint32_t indent) const;
    std::string prach_ConfigIndex_ToStringNoNewLines() const;
    int prach_ConfigIndex_Clear();
    bool prach_ConfigIndex_IsPresent() const;
private:
    bool prach_ConfigIndex_present;
    int64_t prach_ConfigIndex_internal_value;

    // highSpeedFlag
public:
    int highSpeedFlag_Pack(std::vector<uint8_t> &bits);
    int highSpeedFlag_Unpack(std::vector<uint8_t> bits);
    int highSpeedFlag_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    bool highSpeedFlag_Value() const;
    int highSpeedFlag_SetValue(bool value);
    std::string highSpeedFlag_ToString(uint32_t indent) const;
    std::string highSpeedFlag_ToStringNoNewLines() const;
    int highSpeedFlag_Clear();
    bool highSpeedFlag_IsPresent() const;
private:
    bool highSpeedFlag_present;
    bool highSpeedFlag_internal_value;

    // zeroCorrelationZoneConfig
public:
    int zeroCorrelationZoneConfig_Pack(std::vector<uint8_t> &bits);
    int zeroCorrelationZoneConfig_Unpack(std::vector<uint8_t> bits);
    int zeroCorrelationZoneConfig_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t zeroCorrelationZoneConfig_Value() const;
    int zeroCorrelationZoneConfig_SetValue(int64_t value);
    std::string zeroCorrelationZoneConfig_ToString(uint32_t indent) const;
    std::string zeroCorrelationZoneConfig_ToStringNoNewLines() const;
    int zeroCorrelationZoneConfig_Clear();
    bool zeroCorrelationZoneConfig_IsPresent() const;
private:
    bool zeroCorrelationZoneConfig_present;
    int64_t zeroCorrelationZoneConfig_internal_value;

    // prach-FreqOffset
public:
    int prach_FreqOffset_Pack(std::vector<uint8_t> &bits);
    int prach_FreqOffset_Unpack(std::vector<uint8_t> bits);
    int prach_FreqOffset_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t prach_FreqOffset_Value() const;
    int prach_FreqOffset_SetValue(int64_t value);
    std::string prach_FreqOffset_ToString(uint32_t indent) const;
    std::string prach_FreqOffset_ToStringNoNewLines() const;
    int prach_FreqOffset_Clear();
    bool prach_FreqOffset_IsPresent() const;
private:
    bool prach_FreqOffset_present;
    int64_t prach_FreqOffset_internal_value;

};

#endif
