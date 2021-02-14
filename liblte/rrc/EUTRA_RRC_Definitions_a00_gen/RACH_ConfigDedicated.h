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

#ifndef __RACH_ConfigDedicated_H__
#define __RACH_ConfigDedicated_H__

#include <array>
#include <cstdint>
#include <vector>

class RACH_ConfigDedicated
{
public:
    RACH_ConfigDedicated() : ra_PreambleIndex_present{false}, ra_PRACH_MaskIndex_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // ra-PreambleIndex
public:
    int ra_PreambleIndex_Pack(std::vector<uint8_t> &bits);
    int ra_PreambleIndex_Unpack(std::vector<uint8_t> bits);
    int ra_PreambleIndex_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t ra_PreambleIndex_Value() const;
    int ra_PreambleIndex_SetValue(int64_t value);
    std::string ra_PreambleIndex_ToString(uint32_t indent) const;
    std::string ra_PreambleIndex_ToStringNoNewLines() const;
    int ra_PreambleIndex_Clear();
    bool ra_PreambleIndex_IsPresent() const;
private:
    bool ra_PreambleIndex_present;
    int64_t ra_PreambleIndex_internal_value;

    // ra-PRACH-MaskIndex
public:
    int ra_PRACH_MaskIndex_Pack(std::vector<uint8_t> &bits);
    int ra_PRACH_MaskIndex_Unpack(std::vector<uint8_t> bits);
    int ra_PRACH_MaskIndex_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t ra_PRACH_MaskIndex_Value() const;
    int ra_PRACH_MaskIndex_SetValue(int64_t value);
    std::string ra_PRACH_MaskIndex_ToString(uint32_t indent) const;
    std::string ra_PRACH_MaskIndex_ToStringNoNewLines() const;
    int ra_PRACH_MaskIndex_Clear();
    bool ra_PRACH_MaskIndex_IsPresent() const;
private:
    bool ra_PRACH_MaskIndex_present;
    int64_t ra_PRACH_MaskIndex_internal_value;

};

#endif
