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

#ifndef __SchedulingRequestConfig_v10x0_H__
#define __SchedulingRequestConfig_v10x0_H__

#include <array>
#include <cstdint>
#include <vector>

class SchedulingRequestConfig_v10x0
{
public:
    SchedulingRequestConfig_v10x0() : twoAntennaPortActivated_r10_present{false}, sr_PUCCH_ResourceIndexP1_r10_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // twoAntennaPortActivated-r10
public:
    enum twoAntennaPortActivated_r10_Enum {
        k_twoAntennaPortActivated_r10_true = 0,
    };
    int twoAntennaPortActivated_r10_Pack(std::vector<uint8_t> &bits);
    int twoAntennaPortActivated_r10_Unpack(std::vector<uint8_t> bits);
    int twoAntennaPortActivated_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    twoAntennaPortActivated_r10_Enum twoAntennaPortActivated_r10_Value() const;
    int twoAntennaPortActivated_r10_SetValue(twoAntennaPortActivated_r10_Enum value);
    int twoAntennaPortActivated_r10_SetValue(std::string value);
    std::string twoAntennaPortActivated_r10_ValueToString(twoAntennaPortActivated_r10_Enum value) const;
    uint64_t twoAntennaPortActivated_r10_NumberOfValues() const;
    std::string twoAntennaPortActivated_r10_ToString(uint32_t indent) const;
    std::string twoAntennaPortActivated_r10_ToStringNoNewLines() const;
    int twoAntennaPortActivated_r10_Clear();
    bool twoAntennaPortActivated_r10_IsPresent() const;
private:
    bool twoAntennaPortActivated_r10_present;
    twoAntennaPortActivated_r10_Enum twoAntennaPortActivated_r10_internal_value;

    // sr-PUCCH-ResourceIndexP1-r10
public:
    int sr_PUCCH_ResourceIndexP1_r10_Pack(std::vector<uint8_t> &bits);
    int sr_PUCCH_ResourceIndexP1_r10_Unpack(std::vector<uint8_t> bits);
    int sr_PUCCH_ResourceIndexP1_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t sr_PUCCH_ResourceIndexP1_r10_Value() const;
    int sr_PUCCH_ResourceIndexP1_r10_SetValue(int64_t value);
    std::string sr_PUCCH_ResourceIndexP1_r10_ToString(uint32_t indent) const;
    std::string sr_PUCCH_ResourceIndexP1_r10_ToStringNoNewLines() const;
    int sr_PUCCH_ResourceIndexP1_r10_Clear();
    bool sr_PUCCH_ResourceIndexP1_r10_IsPresent() const;
private:
    bool sr_PUCCH_ResourceIndexP1_r10_present;
    int64_t sr_PUCCH_ResourceIndexP1_r10_internal_value;

};

#endif
