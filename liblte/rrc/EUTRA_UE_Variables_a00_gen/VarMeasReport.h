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

#ifndef __VarMeasReport_H__
#define __VarMeasReport_H__

#include "MeasId.h"
#include "CellsTriggeredList.h"

#include <array>
#include <cstdint>
#include <vector>

class VarMeasReport
{
public:
    VarMeasReport() : measId_present{false}, cellsTriggeredList_present{false}, numberOfReportsSent_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // measId
public:
    MeasId* measId_Set();
    int measId_Set(MeasId &value);
    const MeasId& measId_Get() const;
    std::string measId_ToString(uint32_t indent) const;
    std::string measId_ToStringNoNewLines() const;
    int measId_Clear();
    bool measId_IsPresent() const;
private:
    bool measId_present;
    MeasId measId;

    // cellsTriggeredList
public:
    CellsTriggeredList* cellsTriggeredList_Set();
    int cellsTriggeredList_Set(CellsTriggeredList &value);
    const CellsTriggeredList& cellsTriggeredList_Get() const;
    std::string cellsTriggeredList_ToString(uint32_t indent) const;
    std::string cellsTriggeredList_ToStringNoNewLines() const;
    int cellsTriggeredList_Clear();
    bool cellsTriggeredList_IsPresent() const;
private:
    bool cellsTriggeredList_present;
    CellsTriggeredList cellsTriggeredList;

    // numberOfReportsSent
public:
    int numberOfReportsSent_Pack(std::vector<uint8_t> &bits);
    int numberOfReportsSent_Unpack(std::vector<uint8_t> bits);
    int numberOfReportsSent_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t numberOfReportsSent_Value() const;
    int numberOfReportsSent_SetValue(int64_t value);
    std::string numberOfReportsSent_ToString(uint32_t indent) const;
    std::string numberOfReportsSent_ToStringNoNewLines() const;
    int numberOfReportsSent_Clear();
    bool numberOfReportsSent_IsPresent() const;
private:
    bool numberOfReportsSent_present;
    int64_t numberOfReportsSent_internal_value;

};

#endif
