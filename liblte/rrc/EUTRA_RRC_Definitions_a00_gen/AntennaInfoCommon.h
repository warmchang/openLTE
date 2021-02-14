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

#ifndef __AntennaInfoCommon_H__
#define __AntennaInfoCommon_H__

#include <array>
#include <cstdint>
#include <vector>

class AntennaInfoCommon
{
public:
    AntennaInfoCommon() : antennaPortsCount_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // antennaPortsCount
public:
    enum antennaPortsCount_Enum {
        k_antennaPortsCount_an1 = 0,
        k_antennaPortsCount_an2,
        k_antennaPortsCount_an4,
        k_antennaPortsCount_spare1,
    };
    int antennaPortsCount_Pack(std::vector<uint8_t> &bits);
    int antennaPortsCount_Unpack(std::vector<uint8_t> bits);
    int antennaPortsCount_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    antennaPortsCount_Enum antennaPortsCount_Value() const;
    int antennaPortsCount_SetValue(antennaPortsCount_Enum value);
    int antennaPortsCount_SetValue(std::string value);
    std::string antennaPortsCount_ValueToString(antennaPortsCount_Enum value) const;
    uint64_t antennaPortsCount_NumberOfValues() const;
    std::string antennaPortsCount_ToString(uint32_t indent) const;
    std::string antennaPortsCount_ToStringNoNewLines() const;
    int antennaPortsCount_Clear();
    bool antennaPortsCount_IsPresent() const;
private:
    bool antennaPortsCount_present;
    antennaPortsCount_Enum antennaPortsCount_internal_value;

};

#endif
