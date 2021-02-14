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

#ifndef __IRAT_ParametersGERAN_H__
#define __IRAT_ParametersGERAN_H__

#include "SupportedBandListGERAN.h"

#include <array>
#include <cstdint>
#include <vector>

class IRAT_ParametersGERAN
{
public:
    IRAT_ParametersGERAN() : supportedBandListGERAN_present{false}, interRAT_PS_HO_ToGERAN_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // supportedBandListGERAN
public:
    SupportedBandListGERAN* supportedBandListGERAN_Set();
    int supportedBandListGERAN_Set(SupportedBandListGERAN &value);
    const SupportedBandListGERAN& supportedBandListGERAN_Get() const;
    std::string supportedBandListGERAN_ToString(uint32_t indent) const;
    std::string supportedBandListGERAN_ToStringNoNewLines() const;
    int supportedBandListGERAN_Clear();
    bool supportedBandListGERAN_IsPresent() const;
private:
    bool supportedBandListGERAN_present;
    SupportedBandListGERAN supportedBandListGERAN;

    // interRAT-PS-HO-ToGERAN
public:
    int interRAT_PS_HO_ToGERAN_Pack(std::vector<uint8_t> &bits);
    int interRAT_PS_HO_ToGERAN_Unpack(std::vector<uint8_t> bits);
    int interRAT_PS_HO_ToGERAN_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    bool interRAT_PS_HO_ToGERAN_Value() const;
    int interRAT_PS_HO_ToGERAN_SetValue(bool value);
    std::string interRAT_PS_HO_ToGERAN_ToString(uint32_t indent) const;
    std::string interRAT_PS_HO_ToGERAN_ToStringNoNewLines() const;
    int interRAT_PS_HO_ToGERAN_Clear();
    bool interRAT_PS_HO_ToGERAN_IsPresent() const;
private:
    bool interRAT_PS_HO_ToGERAN_present;
    bool interRAT_PS_HO_ToGERAN_internal_value;

};

#endif
