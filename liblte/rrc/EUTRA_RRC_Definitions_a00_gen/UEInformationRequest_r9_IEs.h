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

#ifndef __UEInformationRequest_r9_IEs_H__
#define __UEInformationRequest_r9_IEs_H__

#include "UEInformationRequest_v930_IEs.h"

#include <array>
#include <cstdint>
#include <vector>

class UEInformationRequest_r9_IEs
{
public:
    UEInformationRequest_r9_IEs() : rach_ReportReq_r9_present{false}, rlf_ReportReq_r9_present{false}, nonCriticalExtension_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // rach-ReportReq-r9
public:
    int rach_ReportReq_r9_Pack(std::vector<uint8_t> &bits);
    int rach_ReportReq_r9_Unpack(std::vector<uint8_t> bits);
    int rach_ReportReq_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    bool rach_ReportReq_r9_Value() const;
    int rach_ReportReq_r9_SetValue(bool value);
    std::string rach_ReportReq_r9_ToString(uint32_t indent) const;
    std::string rach_ReportReq_r9_ToStringNoNewLines() const;
    int rach_ReportReq_r9_Clear();
    bool rach_ReportReq_r9_IsPresent() const;
private:
    bool rach_ReportReq_r9_present;
    bool rach_ReportReq_r9_internal_value;

    // rlf-ReportReq-r9
public:
    int rlf_ReportReq_r9_Pack(std::vector<uint8_t> &bits);
    int rlf_ReportReq_r9_Unpack(std::vector<uint8_t> bits);
    int rlf_ReportReq_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    bool rlf_ReportReq_r9_Value() const;
    int rlf_ReportReq_r9_SetValue(bool value);
    std::string rlf_ReportReq_r9_ToString(uint32_t indent) const;
    std::string rlf_ReportReq_r9_ToStringNoNewLines() const;
    int rlf_ReportReq_r9_Clear();
    bool rlf_ReportReq_r9_IsPresent() const;
private:
    bool rlf_ReportReq_r9_present;
    bool rlf_ReportReq_r9_internal_value;

    // nonCriticalExtension
public:
    UEInformationRequest_v930_IEs* nonCriticalExtension_Set();
    int nonCriticalExtension_Set(UEInformationRequest_v930_IEs &value);
    const UEInformationRequest_v930_IEs& nonCriticalExtension_Get() const;
    std::string nonCriticalExtension_ToString(uint32_t indent) const;
    std::string nonCriticalExtension_ToStringNoNewLines() const;
    int nonCriticalExtension_Clear();
    bool nonCriticalExtension_IsPresent() const;
private:
    bool nonCriticalExtension_present;
    UEInformationRequest_v930_IEs nonCriticalExtension;

};

#endif
