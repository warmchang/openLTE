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

#ifndef __SupportedBandGERAN_H__
#define __SupportedBandGERAN_H__

#include <array>
#include <cstdint>
#include <vector>

class SupportedBandGERAN
{
public:
    SupportedBandGERAN() : present{false} {};
public:
    enum Enum {
        k_gsm450 = 0,
        k_gsm480,
        k_gsm710,
        k_gsm750,
        k_gsm810,
        k_gsm850,
        k_gsm900P,
        k_gsm900E,
        k_gsm900R,
        k_gsm1800,
        k_gsm1900,
        k_spare5,
        k_spare4,
        k_spare3,
        k_spare2,
        k_spare1,
    };
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    Enum Value() const;
    int SetValue(Enum value);
    int SetValue(std::string value);
    std::string ValueToString(Enum value) const;
    uint64_t NumberOfValues() const;
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;
    int Clear();
    bool IsPresent() const;
private:
    bool present;
    Enum internal_value;
};

#endif
