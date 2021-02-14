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

#ifndef __CQI_ReportConfig_v920_H__
#define __CQI_ReportConfig_v920_H__

#include <array>
#include <cstdint>
#include <vector>

class CQI_ReportConfig_v920
{
public:
    CQI_ReportConfig_v920() : cqi_Mask_r9_present{false}, pmi_RI_Report_r9_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // cqi-Mask-r9
public:
    enum cqi_Mask_r9_Enum {
        k_cqi_Mask_r9_setup = 0,
    };
    int cqi_Mask_r9_Pack(std::vector<uint8_t> &bits);
    int cqi_Mask_r9_Unpack(std::vector<uint8_t> bits);
    int cqi_Mask_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    cqi_Mask_r9_Enum cqi_Mask_r9_Value() const;
    int cqi_Mask_r9_SetValue(cqi_Mask_r9_Enum value);
    int cqi_Mask_r9_SetValue(std::string value);
    std::string cqi_Mask_r9_ValueToString(cqi_Mask_r9_Enum value) const;
    uint64_t cqi_Mask_r9_NumberOfValues() const;
    std::string cqi_Mask_r9_ToString(uint32_t indent) const;
    std::string cqi_Mask_r9_ToStringNoNewLines() const;
    int cqi_Mask_r9_Clear();
    bool cqi_Mask_r9_IsPresent() const;
private:
    bool cqi_Mask_r9_present;
    cqi_Mask_r9_Enum cqi_Mask_r9_internal_value;

    // pmi-RI-Report-r9
public:
    enum pmi_RI_Report_r9_Enum {
        k_pmi_RI_Report_r9_setup = 0,
    };
    int pmi_RI_Report_r9_Pack(std::vector<uint8_t> &bits);
    int pmi_RI_Report_r9_Unpack(std::vector<uint8_t> bits);
    int pmi_RI_Report_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    pmi_RI_Report_r9_Enum pmi_RI_Report_r9_Value() const;
    int pmi_RI_Report_r9_SetValue(pmi_RI_Report_r9_Enum value);
    int pmi_RI_Report_r9_SetValue(std::string value);
    std::string pmi_RI_Report_r9_ValueToString(pmi_RI_Report_r9_Enum value) const;
    uint64_t pmi_RI_Report_r9_NumberOfValues() const;
    std::string pmi_RI_Report_r9_ToString(uint32_t indent) const;
    std::string pmi_RI_Report_r9_ToStringNoNewLines() const;
    int pmi_RI_Report_r9_Clear();
    bool pmi_RI_Report_r9_IsPresent() const;
private:
    bool pmi_RI_Report_r9_present;
    pmi_RI_Report_r9_Enum pmi_RI_Report_r9_internal_value;

};

#endif
