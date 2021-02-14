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

#ifndef __CQI_ReportConfig_H__
#define __CQI_ReportConfig_H__

#include "CQI_ReportPeriodic.h"

#include <array>
#include <cstdint>
#include <vector>

class CQI_ReportConfig
{
public:
    CQI_ReportConfig() : cqi_ReportModeAperiodic_present{false}, nomPDSCH_RS_EPRE_Offset_present{false}, cqi_ReportPeriodic_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // cqi-ReportModeAperiodic
public:
    enum cqi_ReportModeAperiodic_Enum {
        k_cqi_ReportModeAperiodic_rm12 = 0,
        k_cqi_ReportModeAperiodic_rm20,
        k_cqi_ReportModeAperiodic_rm22,
        k_cqi_ReportModeAperiodic_rm30,
        k_cqi_ReportModeAperiodic_rm31,
        k_cqi_ReportModeAperiodic_spare3,
        k_cqi_ReportModeAperiodic_spare2,
        k_cqi_ReportModeAperiodic_spare1,
    };
    int cqi_ReportModeAperiodic_Pack(std::vector<uint8_t> &bits);
    int cqi_ReportModeAperiodic_Unpack(std::vector<uint8_t> bits);
    int cqi_ReportModeAperiodic_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    cqi_ReportModeAperiodic_Enum cqi_ReportModeAperiodic_Value() const;
    int cqi_ReportModeAperiodic_SetValue(cqi_ReportModeAperiodic_Enum value);
    int cqi_ReportModeAperiodic_SetValue(std::string value);
    std::string cqi_ReportModeAperiodic_ValueToString(cqi_ReportModeAperiodic_Enum value) const;
    uint64_t cqi_ReportModeAperiodic_NumberOfValues() const;
    std::string cqi_ReportModeAperiodic_ToString(uint32_t indent) const;
    std::string cqi_ReportModeAperiodic_ToStringNoNewLines() const;
    int cqi_ReportModeAperiodic_Clear();
    bool cqi_ReportModeAperiodic_IsPresent() const;
private:
    bool cqi_ReportModeAperiodic_present;
    cqi_ReportModeAperiodic_Enum cqi_ReportModeAperiodic_internal_value;

    // nomPDSCH-RS-EPRE-Offset
public:
    int nomPDSCH_RS_EPRE_Offset_Pack(std::vector<uint8_t> &bits);
    int nomPDSCH_RS_EPRE_Offset_Unpack(std::vector<uint8_t> bits);
    int nomPDSCH_RS_EPRE_Offset_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t nomPDSCH_RS_EPRE_Offset_Value() const;
    int nomPDSCH_RS_EPRE_Offset_SetValue(int64_t value);
    std::string nomPDSCH_RS_EPRE_Offset_ToString(uint32_t indent) const;
    std::string nomPDSCH_RS_EPRE_Offset_ToStringNoNewLines() const;
    int nomPDSCH_RS_EPRE_Offset_Clear();
    bool nomPDSCH_RS_EPRE_Offset_IsPresent() const;
private:
    bool nomPDSCH_RS_EPRE_Offset_present;
    int64_t nomPDSCH_RS_EPRE_Offset_internal_value;

    // cqi-ReportPeriodic
public:
    CQI_ReportPeriodic* cqi_ReportPeriodic_Set();
    int cqi_ReportPeriodic_Set(CQI_ReportPeriodic &value);
    const CQI_ReportPeriodic& cqi_ReportPeriodic_Get() const;
    std::string cqi_ReportPeriodic_ToString(uint32_t indent) const;
    std::string cqi_ReportPeriodic_ToStringNoNewLines() const;
    int cqi_ReportPeriodic_Clear();
    bool cqi_ReportPeriodic_IsPresent() const;
private:
    bool cqi_ReportPeriodic_present;
    CQI_ReportPeriodic cqi_ReportPeriodic;

};

#endif
