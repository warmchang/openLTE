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

#ifndef __CQI_ReportConfig_v10x0_H__
#define __CQI_ReportConfig_v10x0_H__

#include <array>
#include <cstdint>
#include <vector>

class CQI_ReportConfig_v10x0
{
public:
    CQI_ReportConfig_v10x0() : ri_ReportMode_r10_present{false}, twoAntennaPortActivated_r10_present{false}, cqi_PUCCH_ResourceIndexP1_r10_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // ri-ReportMode-r10
public:
    enum ri_ReportMode_r10_Enum {
        k_ri_ReportMode_r10_riWithW1 = 0,
        k_ri_ReportMode_r10_riWithoutW1,
    };
    int ri_ReportMode_r10_Pack(std::vector<uint8_t> &bits);
    int ri_ReportMode_r10_Unpack(std::vector<uint8_t> bits);
    int ri_ReportMode_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    ri_ReportMode_r10_Enum ri_ReportMode_r10_Value() const;
    int ri_ReportMode_r10_SetValue(ri_ReportMode_r10_Enum value);
    int ri_ReportMode_r10_SetValue(std::string value);
    std::string ri_ReportMode_r10_ValueToString(ri_ReportMode_r10_Enum value) const;
    uint64_t ri_ReportMode_r10_NumberOfValues() const;
    std::string ri_ReportMode_r10_ToString(uint32_t indent) const;
    std::string ri_ReportMode_r10_ToStringNoNewLines() const;
    int ri_ReportMode_r10_Clear();
    bool ri_ReportMode_r10_IsPresent() const;
private:
    bool ri_ReportMode_r10_present;
    ri_ReportMode_r10_Enum ri_ReportMode_r10_internal_value;

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

    // cqi-PUCCH-ResourceIndexP1-r10
public:
    int cqi_PUCCH_ResourceIndexP1_r10_Pack(std::vector<uint8_t> &bits);
    int cqi_PUCCH_ResourceIndexP1_r10_Unpack(std::vector<uint8_t> bits);
    int cqi_PUCCH_ResourceIndexP1_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t cqi_PUCCH_ResourceIndexP1_r10_Value() const;
    int cqi_PUCCH_ResourceIndexP1_r10_SetValue(int64_t value);
    std::string cqi_PUCCH_ResourceIndexP1_r10_ToString(uint32_t indent) const;
    std::string cqi_PUCCH_ResourceIndexP1_r10_ToStringNoNewLines() const;
    int cqi_PUCCH_ResourceIndexP1_r10_Clear();
    bool cqi_PUCCH_ResourceIndexP1_r10_IsPresent() const;
private:
    bool cqi_PUCCH_ResourceIndexP1_r10_present;
    int64_t cqi_PUCCH_ResourceIndexP1_r10_internal_value;

};

#endif
