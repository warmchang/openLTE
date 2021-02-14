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

#ifndef __DLInformationTransfer_r8_IEs_H__
#define __DLInformationTransfer_r8_IEs_H__

#include "DedicatedInfoNAS.h"
#include "DedicatedInfoCDMA2000.h"
#include "DedicatedInfoCDMA2000.h"
#include "DLInformationTransfer_v8a0_IEs.h"

#include <array>
#include <cstdint>
#include <vector>

class DLInformationTransfer_r8_IEs
{
public:
    DLInformationTransfer_r8_IEs() : dedicatedInfoType_present{false}, nonCriticalExtension_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // dedicatedInfoType
public:
    enum dedicatedInfoType_Enum {
        k_dedicatedInfoType_dedicatedInfoNAS = 0,
        k_dedicatedInfoType_dedicatedInfoCDMA2000_1XRTT,
        k_dedicatedInfoType_dedicatedInfoCDMA2000_HRPD,
    };
    int dedicatedInfoType_Pack(std::vector<uint8_t> &bits);
    int dedicatedInfoType_Unpack(std::vector<uint8_t> bits);
    int dedicatedInfoType_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    dedicatedInfoType_Enum dedicatedInfoType_Choice() const;
    int dedicatedInfoType_SetChoice(dedicatedInfoType_Enum choice);
    std::string dedicatedInfoType_ChoiceToString(dedicatedInfoType_Enum value) const;
    uint64_t dedicatedInfoType_NumberOfChoices() const;
    std::string dedicatedInfoType_ToString(uint32_t indent) const;
    std::string dedicatedInfoType_ToStringNoNewLines() const;
    int dedicatedInfoType_Clear();
    bool dedicatedInfoType_IsPresent() const;
private:
    bool dedicatedInfoType_present;
    dedicatedInfoType_Enum dedicatedInfoType_internal_choice;

    // dedicatedInfoNAS
public:
    DedicatedInfoNAS* dedicatedInfoType_dedicatedInfoNAS_Set();
    int dedicatedInfoType_dedicatedInfoNAS_Set(DedicatedInfoNAS &value);
    const DedicatedInfoNAS& dedicatedInfoType_dedicatedInfoNAS_Get() const;
    std::string dedicatedInfoType_dedicatedInfoNAS_ToString(uint32_t indent) const;
    std::string dedicatedInfoType_dedicatedInfoNAS_ToStringNoNewLines() const;
    int dedicatedInfoType_dedicatedInfoNAS_Clear();
    bool dedicatedInfoType_dedicatedInfoNAS_IsPresent() const;
private:
    bool dedicatedInfoType_dedicatedInfoNAS_present;
    DedicatedInfoNAS dedicatedInfoType_dedicatedInfoNAS;

    // dedicatedInfoCDMA2000-1XRTT
public:
    DedicatedInfoCDMA2000* dedicatedInfoType_dedicatedInfoCDMA2000_1XRTT_Set();
    int dedicatedInfoType_dedicatedInfoCDMA2000_1XRTT_Set(DedicatedInfoCDMA2000 &value);
    const DedicatedInfoCDMA2000& dedicatedInfoType_dedicatedInfoCDMA2000_1XRTT_Get() const;
    std::string dedicatedInfoType_dedicatedInfoCDMA2000_1XRTT_ToString(uint32_t indent) const;
    std::string dedicatedInfoType_dedicatedInfoCDMA2000_1XRTT_ToStringNoNewLines() const;
    int dedicatedInfoType_dedicatedInfoCDMA2000_1XRTT_Clear();
    bool dedicatedInfoType_dedicatedInfoCDMA2000_1XRTT_IsPresent() const;
private:
    bool dedicatedInfoType_dedicatedInfoCDMA2000_1XRTT_present;
    DedicatedInfoCDMA2000 dedicatedInfoType_dedicatedInfoCDMA2000_1XRTT;

    // dedicatedInfoCDMA2000-HRPD
public:
    DedicatedInfoCDMA2000* dedicatedInfoType_dedicatedInfoCDMA2000_HRPD_Set();
    int dedicatedInfoType_dedicatedInfoCDMA2000_HRPD_Set(DedicatedInfoCDMA2000 &value);
    const DedicatedInfoCDMA2000& dedicatedInfoType_dedicatedInfoCDMA2000_HRPD_Get() const;
    std::string dedicatedInfoType_dedicatedInfoCDMA2000_HRPD_ToString(uint32_t indent) const;
    std::string dedicatedInfoType_dedicatedInfoCDMA2000_HRPD_ToStringNoNewLines() const;
    int dedicatedInfoType_dedicatedInfoCDMA2000_HRPD_Clear();
    bool dedicatedInfoType_dedicatedInfoCDMA2000_HRPD_IsPresent() const;
private:
    bool dedicatedInfoType_dedicatedInfoCDMA2000_HRPD_present;
    DedicatedInfoCDMA2000 dedicatedInfoType_dedicatedInfoCDMA2000_HRPD;


    // nonCriticalExtension
public:
    DLInformationTransfer_v8a0_IEs* nonCriticalExtension_Set();
    int nonCriticalExtension_Set(DLInformationTransfer_v8a0_IEs &value);
    const DLInformationTransfer_v8a0_IEs& nonCriticalExtension_Get() const;
    std::string nonCriticalExtension_ToString(uint32_t indent) const;
    std::string nonCriticalExtension_ToStringNoNewLines() const;
    int nonCriticalExtension_Clear();
    bool nonCriticalExtension_IsPresent() const;
private:
    bool nonCriticalExtension_present;
    DLInformationTransfer_v8a0_IEs nonCriticalExtension;

};

#endif
