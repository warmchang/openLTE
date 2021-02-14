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

#ifndef __UEInformationRequest_v10xy_IEs_H__
#define __UEInformationRequest_v10xy_IEs_H__

#include <array>
#include <cstdint>
#include <vector>

class UEInformationRequest_v10xy_IEs
{
public:
    UEInformationRequest_v10xy_IEs() : logMeasReportReq_r10_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // logMeasReportReq-r10
public:
    enum logMeasReportReq_r10_Enum {
        k_logMeasReportReq_r10_true = 0,
    };
    int logMeasReportReq_r10_Pack(std::vector<uint8_t> &bits);
    int logMeasReportReq_r10_Unpack(std::vector<uint8_t> bits);
    int logMeasReportReq_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    logMeasReportReq_r10_Enum logMeasReportReq_r10_Value() const;
    int logMeasReportReq_r10_SetValue(logMeasReportReq_r10_Enum value);
    int logMeasReportReq_r10_SetValue(std::string value);
    std::string logMeasReportReq_r10_ValueToString(logMeasReportReq_r10_Enum value) const;
    uint64_t logMeasReportReq_r10_NumberOfValues() const;
    std::string logMeasReportReq_r10_ToString(uint32_t indent) const;
    std::string logMeasReportReq_r10_ToStringNoNewLines() const;
    int logMeasReportReq_r10_Clear();
    bool logMeasReportReq_r10_IsPresent() const;
private:
    bool logMeasReportReq_r10_present;
    logMeasReportReq_r10_Enum logMeasReportReq_r10_internal_value;

    // nonCriticalExtension

};

#endif
