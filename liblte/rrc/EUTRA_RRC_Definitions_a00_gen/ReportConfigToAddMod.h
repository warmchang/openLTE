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

#ifndef __ReportConfigToAddMod_H__
#define __ReportConfigToAddMod_H__

#include "ReportConfigId.h"
#include "ReportConfigEUTRA.h"
#include "ReportConfigInterRAT.h"

#include <array>
#include <cstdint>
#include <vector>

class ReportConfigToAddMod
{
public:
    ReportConfigToAddMod() : reportConfigId_present{false}, reportConfig_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // reportConfigId
public:
    ReportConfigId* reportConfigId_Set();
    int reportConfigId_Set(ReportConfigId &value);
    const ReportConfigId& reportConfigId_Get() const;
    std::string reportConfigId_ToString(uint32_t indent) const;
    std::string reportConfigId_ToStringNoNewLines() const;
    int reportConfigId_Clear();
    bool reportConfigId_IsPresent() const;
private:
    bool reportConfigId_present;
    ReportConfigId reportConfigId;

    // reportConfig
public:
    enum reportConfig_Enum {
        k_reportConfig_reportConfigEUTRA = 0,
        k_reportConfig_reportConfigInterRAT,
    };
    int reportConfig_Pack(std::vector<uint8_t> &bits);
    int reportConfig_Unpack(std::vector<uint8_t> bits);
    int reportConfig_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    reportConfig_Enum reportConfig_Choice() const;
    int reportConfig_SetChoice(reportConfig_Enum choice);
    std::string reportConfig_ChoiceToString(reportConfig_Enum value) const;
    uint64_t reportConfig_NumberOfChoices() const;
    std::string reportConfig_ToString(uint32_t indent) const;
    std::string reportConfig_ToStringNoNewLines() const;
    int reportConfig_Clear();
    bool reportConfig_IsPresent() const;
private:
    bool reportConfig_present;
    reportConfig_Enum reportConfig_internal_choice;

    // reportConfigEUTRA
public:
    ReportConfigEUTRA* reportConfig_reportConfigEUTRA_Set();
    int reportConfig_reportConfigEUTRA_Set(ReportConfigEUTRA &value);
    const ReportConfigEUTRA& reportConfig_reportConfigEUTRA_Get() const;
    std::string reportConfig_reportConfigEUTRA_ToString(uint32_t indent) const;
    std::string reportConfig_reportConfigEUTRA_ToStringNoNewLines() const;
    int reportConfig_reportConfigEUTRA_Clear();
    bool reportConfig_reportConfigEUTRA_IsPresent() const;
private:
    bool reportConfig_reportConfigEUTRA_present;
    ReportConfigEUTRA reportConfig_reportConfigEUTRA;

    // reportConfigInterRAT
public:
    ReportConfigInterRAT* reportConfig_reportConfigInterRAT_Set();
    int reportConfig_reportConfigInterRAT_Set(ReportConfigInterRAT &value);
    const ReportConfigInterRAT& reportConfig_reportConfigInterRAT_Get() const;
    std::string reportConfig_reportConfigInterRAT_ToString(uint32_t indent) const;
    std::string reportConfig_reportConfigInterRAT_ToStringNoNewLines() const;
    int reportConfig_reportConfigInterRAT_Clear();
    bool reportConfig_reportConfigInterRAT_IsPresent() const;
private:
    bool reportConfig_reportConfigInterRAT_present;
    ReportConfigInterRAT reportConfig_reportConfigInterRAT;


};

#endif
