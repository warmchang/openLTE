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

#ifndef __PhysCellIdGERAN_H__
#define __PhysCellIdGERAN_H__

#include <array>
#include <cstdint>
#include <vector>

class PhysCellIdGERAN
{
public:
    PhysCellIdGERAN() : networkColourCode_present{false}, baseStationColourCode_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // networkColourCode
public:
    int networkColourCode_Pack(std::vector<uint8_t> &bits);
    int networkColourCode_Unpack(std::vector<uint8_t> bits);
    int networkColourCode_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    uint8_t networkColourCode_Value() const;
    int networkColourCode_SetValue(uint8_t value);
    std::string networkColourCode_ToString(uint32_t indent) const;
    std::string networkColourCode_ToStringNoNewLines() const;
    int networkColourCode_Clear();
    bool networkColourCode_IsPresent() const;
private:
    bool networkColourCode_present;
    uint8_t networkColourCode_internal_value;

    // baseStationColourCode
public:
    int baseStationColourCode_Pack(std::vector<uint8_t> &bits);
    int baseStationColourCode_Unpack(std::vector<uint8_t> bits);
    int baseStationColourCode_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    uint8_t baseStationColourCode_Value() const;
    int baseStationColourCode_SetValue(uint8_t value);
    std::string baseStationColourCode_ToString(uint32_t indent) const;
    std::string baseStationColourCode_ToStringNoNewLines() const;
    int baseStationColourCode_Clear();
    bool baseStationColourCode_IsPresent() const;
private:
    bool baseStationColourCode_present;
    uint8_t baseStationColourCode_internal_value;

};

#endif
