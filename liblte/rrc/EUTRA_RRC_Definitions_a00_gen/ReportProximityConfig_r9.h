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

#ifndef __ReportProximityConfig_r9_H__
#define __ReportProximityConfig_r9_H__

#include <array>
#include <cstdint>
#include <vector>

class ReportProximityConfig_r9
{
public:
    ReportProximityConfig_r9() : proximityIndicationEUTRA_r9_present{false}, proximityIndicationUTRA_r9_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // proximityIndicationEUTRA-r9
public:
    enum proximityIndicationEUTRA_r9_Enum {
        k_proximityIndicationEUTRA_r9_enabled = 0,
    };
    int proximityIndicationEUTRA_r9_Pack(std::vector<uint8_t> &bits);
    int proximityIndicationEUTRA_r9_Unpack(std::vector<uint8_t> bits);
    int proximityIndicationEUTRA_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    proximityIndicationEUTRA_r9_Enum proximityIndicationEUTRA_r9_Value() const;
    int proximityIndicationEUTRA_r9_SetValue(proximityIndicationEUTRA_r9_Enum value);
    int proximityIndicationEUTRA_r9_SetValue(std::string value);
    std::string proximityIndicationEUTRA_r9_ValueToString(proximityIndicationEUTRA_r9_Enum value) const;
    uint64_t proximityIndicationEUTRA_r9_NumberOfValues() const;
    std::string proximityIndicationEUTRA_r9_ToString(uint32_t indent) const;
    std::string proximityIndicationEUTRA_r9_ToStringNoNewLines() const;
    int proximityIndicationEUTRA_r9_Clear();
    bool proximityIndicationEUTRA_r9_IsPresent() const;
private:
    bool proximityIndicationEUTRA_r9_present;
    proximityIndicationEUTRA_r9_Enum proximityIndicationEUTRA_r9_internal_value;

    // proximityIndicationUTRA-r9
public:
    enum proximityIndicationUTRA_r9_Enum {
        k_proximityIndicationUTRA_r9_enabled = 0,
    };
    int proximityIndicationUTRA_r9_Pack(std::vector<uint8_t> &bits);
    int proximityIndicationUTRA_r9_Unpack(std::vector<uint8_t> bits);
    int proximityIndicationUTRA_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    proximityIndicationUTRA_r9_Enum proximityIndicationUTRA_r9_Value() const;
    int proximityIndicationUTRA_r9_SetValue(proximityIndicationUTRA_r9_Enum value);
    int proximityIndicationUTRA_r9_SetValue(std::string value);
    std::string proximityIndicationUTRA_r9_ValueToString(proximityIndicationUTRA_r9_Enum value) const;
    uint64_t proximityIndicationUTRA_r9_NumberOfValues() const;
    std::string proximityIndicationUTRA_r9_ToString(uint32_t indent) const;
    std::string proximityIndicationUTRA_r9_ToStringNoNewLines() const;
    int proximityIndicationUTRA_r9_Clear();
    bool proximityIndicationUTRA_r9_IsPresent() const;
private:
    bool proximityIndicationUTRA_r9_present;
    proximityIndicationUTRA_r9_Enum proximityIndicationUTRA_r9_internal_value;

};

#endif
