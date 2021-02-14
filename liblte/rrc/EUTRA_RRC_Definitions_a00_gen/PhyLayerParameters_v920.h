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

#ifndef __PhyLayerParameters_v920_H__
#define __PhyLayerParameters_v920_H__

#include <array>
#include <cstdint>
#include <vector>

class PhyLayerParameters_v920
{
public:
    PhyLayerParameters_v920() : enhancedDualLayerFDD_r9_present{false}, enhancedDualLayerTDD_r9_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // enhancedDualLayerFDD-r9
public:
    enum enhancedDualLayerFDD_r9_Enum {
        k_enhancedDualLayerFDD_r9_supported = 0,
    };
    int enhancedDualLayerFDD_r9_Pack(std::vector<uint8_t> &bits);
    int enhancedDualLayerFDD_r9_Unpack(std::vector<uint8_t> bits);
    int enhancedDualLayerFDD_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    enhancedDualLayerFDD_r9_Enum enhancedDualLayerFDD_r9_Value() const;
    int enhancedDualLayerFDD_r9_SetValue(enhancedDualLayerFDD_r9_Enum value);
    int enhancedDualLayerFDD_r9_SetValue(std::string value);
    std::string enhancedDualLayerFDD_r9_ValueToString(enhancedDualLayerFDD_r9_Enum value) const;
    uint64_t enhancedDualLayerFDD_r9_NumberOfValues() const;
    std::string enhancedDualLayerFDD_r9_ToString(uint32_t indent) const;
    std::string enhancedDualLayerFDD_r9_ToStringNoNewLines() const;
    int enhancedDualLayerFDD_r9_Clear();
    bool enhancedDualLayerFDD_r9_IsPresent() const;
private:
    bool enhancedDualLayerFDD_r9_present;
    enhancedDualLayerFDD_r9_Enum enhancedDualLayerFDD_r9_internal_value;

    // enhancedDualLayerTDD-r9
public:
    enum enhancedDualLayerTDD_r9_Enum {
        k_enhancedDualLayerTDD_r9_supported = 0,
    };
    int enhancedDualLayerTDD_r9_Pack(std::vector<uint8_t> &bits);
    int enhancedDualLayerTDD_r9_Unpack(std::vector<uint8_t> bits);
    int enhancedDualLayerTDD_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    enhancedDualLayerTDD_r9_Enum enhancedDualLayerTDD_r9_Value() const;
    int enhancedDualLayerTDD_r9_SetValue(enhancedDualLayerTDD_r9_Enum value);
    int enhancedDualLayerTDD_r9_SetValue(std::string value);
    std::string enhancedDualLayerTDD_r9_ValueToString(enhancedDualLayerTDD_r9_Enum value) const;
    uint64_t enhancedDualLayerTDD_r9_NumberOfValues() const;
    std::string enhancedDualLayerTDD_r9_ToString(uint32_t indent) const;
    std::string enhancedDualLayerTDD_r9_ToStringNoNewLines() const;
    int enhancedDualLayerTDD_r9_Clear();
    bool enhancedDualLayerTDD_r9_IsPresent() const;
private:
    bool enhancedDualLayerTDD_r9_present;
    enhancedDualLayerTDD_r9_Enum enhancedDualLayerTDD_r9_internal_value;

};

#endif
