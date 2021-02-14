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

#ifndef __SON_Parameters_r9_H__
#define __SON_Parameters_r9_H__

#include <array>
#include <cstdint>
#include <vector>

class SON_Parameters_r9
{
public:
    SON_Parameters_r9() : rach_Report_r9_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // rach-Report-r9
public:
    enum rach_Report_r9_Enum {
        k_rach_Report_r9_supported = 0,
    };
    int rach_Report_r9_Pack(std::vector<uint8_t> &bits);
    int rach_Report_r9_Unpack(std::vector<uint8_t> bits);
    int rach_Report_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    rach_Report_r9_Enum rach_Report_r9_Value() const;
    int rach_Report_r9_SetValue(rach_Report_r9_Enum value);
    int rach_Report_r9_SetValue(std::string value);
    std::string rach_Report_r9_ValueToString(rach_Report_r9_Enum value) const;
    uint64_t rach_Report_r9_NumberOfValues() const;
    std::string rach_Report_r9_ToString(uint32_t indent) const;
    std::string rach_Report_r9_ToStringNoNewLines() const;
    int rach_Report_r9_Clear();
    bool rach_Report_r9_IsPresent() const;
private:
    bool rach_Report_r9_present;
    rach_Report_r9_Enum rach_Report_r9_internal_value;

};

#endif
