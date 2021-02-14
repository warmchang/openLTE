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

#ifndef __TDD_SubframeConfig_r10_H__
#define __TDD_SubframeConfig_r10_H__

#include <array>
#include <cstdint>
#include <vector>

class TDD_SubframeConfig_r10
{
public:
    TDD_SubframeConfig_r10() : subframeConfigurationPatternTDD_r10_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // subframeConfigurationPatternTDD-r10
public:
    int subframeConfigurationPatternTDD_r10_Pack(std::vector<uint8_t> &bits);
    int subframeConfigurationPatternTDD_r10_Unpack(std::vector<uint8_t> bits);
    int subframeConfigurationPatternTDD_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t subframeConfigurationPatternTDD_r10_Value() const;
    int subframeConfigurationPatternTDD_r10_SetValue(int64_t value);
    std::string subframeConfigurationPatternTDD_r10_ToString(uint32_t indent) const;
    std::string subframeConfigurationPatternTDD_r10_ToStringNoNewLines() const;
    int subframeConfigurationPatternTDD_r10_Clear();
    bool subframeConfigurationPatternTDD_r10_IsPresent() const;
private:
    bool subframeConfigurationPatternTDD_r10_present;
    int64_t subframeConfigurationPatternTDD_r10_internal_value;

};

#endif
