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

#ifndef __QuantityConfigCDMA2000_H__
#define __QuantityConfigCDMA2000_H__

#include <array>
#include <cstdint>
#include <vector>

class QuantityConfigCDMA2000
{
public:
    QuantityConfigCDMA2000() : measQuantityCDMA2000_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // measQuantityCDMA2000
public:
    enum measQuantityCDMA2000_Enum {
        k_measQuantityCDMA2000_pilotStrength = 0,
        k_measQuantityCDMA2000_pilotPnPhaseAndPilotStrength,
    };
    int measQuantityCDMA2000_Pack(std::vector<uint8_t> &bits);
    int measQuantityCDMA2000_Unpack(std::vector<uint8_t> bits);
    int measQuantityCDMA2000_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    measQuantityCDMA2000_Enum measQuantityCDMA2000_Value() const;
    int measQuantityCDMA2000_SetValue(measQuantityCDMA2000_Enum value);
    int measQuantityCDMA2000_SetValue(std::string value);
    std::string measQuantityCDMA2000_ValueToString(measQuantityCDMA2000_Enum value) const;
    uint64_t measQuantityCDMA2000_NumberOfValues() const;
    std::string measQuantityCDMA2000_ToString(uint32_t indent) const;
    std::string measQuantityCDMA2000_ToStringNoNewLines() const;
    int measQuantityCDMA2000_Clear();
    bool measQuantityCDMA2000_IsPresent() const;
private:
    bool measQuantityCDMA2000_present;
    measQuantityCDMA2000_Enum measQuantityCDMA2000_internal_value;

};

#endif
