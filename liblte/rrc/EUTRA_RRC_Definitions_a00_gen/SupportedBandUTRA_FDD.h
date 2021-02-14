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

#ifndef __SupportedBandUTRA_FDD_H__
#define __SupportedBandUTRA_FDD_H__

#include <array>
#include <cstdint>
#include <vector>

class SupportedBandUTRA_FDD
{
public:
    SupportedBandUTRA_FDD() : present{false} {};
public:
    enum Enum {
        k_bandI = 0,
        k_bandII,
        k_bandIII,
        k_bandIV,
        k_bandV,
        k_bandVI,
        k_bandVII,
        k_bandVIII,
        k_bandIX,
        k_bandX,
        k_bandXI,
        k_bandXII,
        k_bandXIII,
        k_bandXIV,
        k_bandXV,
        k_bandXVI,
        k_bandXVII_8a0,
        k_bandXVIII_8a0,
        k_bandXIX_8a0,
        k_bandXX_8a0,
        k_bandXXI_8a0,
        k_bandXXII_8a0,
        k_bandXXIII_8a0,
        k_bandXXIV_8a0,
        k_bandXXV_8a0,
        k_bandXXVI_8a0,
        k_bandXXVII_8a0,
        k_bandXXVIII_8a0,
        k_bandXXIX_8a0,
        k_bandXXX_8a0,
        k_bandXXXI_8a0,
        k_bandXXXII_8a0,
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
