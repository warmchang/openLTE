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

#ifndef __SupportedBandEUTRA_H__
#define __SupportedBandEUTRA_H__

#include <array>
#include <cstdint>
#include <vector>

class SupportedBandEUTRA
{
public:
    SupportedBandEUTRA() : bandEUTRA_present{false}, halfDuplex_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // bandEUTRA
public:
    int bandEUTRA_Pack(std::vector<uint8_t> &bits);
    int bandEUTRA_Unpack(std::vector<uint8_t> bits);
    int bandEUTRA_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t bandEUTRA_Value() const;
    int bandEUTRA_SetValue(int64_t value);
    std::string bandEUTRA_ToString(uint32_t indent) const;
    std::string bandEUTRA_ToStringNoNewLines() const;
    int bandEUTRA_Clear();
    bool bandEUTRA_IsPresent() const;
private:
    bool bandEUTRA_present;
    int64_t bandEUTRA_internal_value;

    // halfDuplex
public:
    int halfDuplex_Pack(std::vector<uint8_t> &bits);
    int halfDuplex_Unpack(std::vector<uint8_t> bits);
    int halfDuplex_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    bool halfDuplex_Value() const;
    int halfDuplex_SetValue(bool value);
    std::string halfDuplex_ToString(uint32_t indent) const;
    std::string halfDuplex_ToStringNoNewLines() const;
    int halfDuplex_Clear();
    bool halfDuplex_IsPresent() const;
private:
    bool halfDuplex_present;
    bool halfDuplex_internal_value;

};

#endif
