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

#ifndef __FDD_SubframeConfig_r10_H__
#define __FDD_SubframeConfig_r10_H__

#include <array>
#include <cstdint>
#include <vector>

class FDD_SubframeConfig_r10
{
public:
    FDD_SubframeConfig_r10() : subframeConfigurationPatternFDD_r10_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // subframeConfigurationPatternFDD-r10
public:
    int subframeConfigurationPatternFDD_r10_Pack(std::vector<uint8_t> &bits);
    int subframeConfigurationPatternFDD_r10_Unpack(std::vector<uint8_t> bits);
    int subframeConfigurationPatternFDD_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    uint8_t subframeConfigurationPatternFDD_r10_Value() const;
    int subframeConfigurationPatternFDD_r10_SetValue(uint8_t value);
    std::string subframeConfigurationPatternFDD_r10_ToString(uint32_t indent) const;
    std::string subframeConfigurationPatternFDD_r10_ToStringNoNewLines() const;
    int subframeConfigurationPatternFDD_r10_Clear();
    bool subframeConfigurationPatternFDD_r10_IsPresent() const;
private:
    bool subframeConfigurationPatternFDD_r10_present;
    uint8_t subframeConfigurationPatternFDD_r10_internal_value;

};

#endif
