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

#ifndef __PDSCH_ConfigCommon_H__
#define __PDSCH_ConfigCommon_H__

#include <array>
#include <cstdint>
#include <vector>

class PDSCH_ConfigCommon
{
public:
    PDSCH_ConfigCommon() : referenceSignalPower_present{false}, p_b_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // referenceSignalPower
public:
    int referenceSignalPower_Pack(std::vector<uint8_t> &bits);
    int referenceSignalPower_Unpack(std::vector<uint8_t> bits);
    int referenceSignalPower_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t referenceSignalPower_Value() const;
    int referenceSignalPower_SetValue(int64_t value);
    std::string referenceSignalPower_ToString(uint32_t indent) const;
    std::string referenceSignalPower_ToStringNoNewLines() const;
    int referenceSignalPower_Clear();
    bool referenceSignalPower_IsPresent() const;
private:
    bool referenceSignalPower_present;
    int64_t referenceSignalPower_internal_value;

    // p-b
public:
    int p_b_Pack(std::vector<uint8_t> &bits);
    int p_b_Unpack(std::vector<uint8_t> bits);
    int p_b_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t p_b_Value() const;
    int p_b_SetValue(int64_t value);
    std::string p_b_ToString(uint32_t indent) const;
    std::string p_b_ToStringNoNewLines() const;
    int p_b_Clear();
    bool p_b_IsPresent() const;
private:
    bool p_b_present;
    int64_t p_b_internal_value;

};

#endif
