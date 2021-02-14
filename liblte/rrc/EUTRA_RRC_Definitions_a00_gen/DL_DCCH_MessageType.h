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

#ifndef __DL_DCCH_MessageType_H__
#define __DL_DCCH_MessageType_H__

#include "CSFBParametersResponseCDMA2000.h"
#include "DLInformationTransfer.h"
#include "HandoverFromEUTRAPreparationRequest.h"
#include "MobilityFromEUTRACommand.h"
#include "RRCConnectionReconfiguration.h"
#include "RRCConnectionRelease.h"
#include "SecurityModeCommand.h"
#include "UECapabilityEnquiry.h"
#include "CounterCheck.h"
#include "UEInformationRequest_r9.h"
#include "LoggedMeasurementsConfiguration_r10.h"
#include "RNReconfiguration_r10.h"

#include <array>
#include <cstdint>
#include <vector>

class DL_DCCH_MessageType
{
public:
    enum Enum {
        k_c1 = 0,
        k_messageClassExtension,
    };
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    Enum Choice() const;
    int SetChoice(Enum choice);
    std::string ChoiceToString(Enum value) const;
    uint64_t NumberOfChoices() const;
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;
    int Clear();
    bool IsPresent() const;
private:
    bool present;
    Enum internal_choice;

    // c1
public:
    enum c1_Enum {
        k_c1_csfbParametersResponseCDMA2000 = 0,
        k_c1_dlInformationTransfer,
        k_c1_handoverFromEUTRAPreparationRequest,
        k_c1_mobilityFromEUTRACommand,
        k_c1_rrcConnectionReconfiguration,
        k_c1_rrcConnectionRelease,
        k_c1_securityModeCommand,
        k_c1_ueCapabilityEnquiry,
        k_c1_counterCheck,
        k_c1_ueInformationRequest_r9,
        k_c1_loggedMeasurementsConfiguration_r10,
        k_c1_rnReconfiguration_r10,
        k_c1_spare4,
        k_c1_spare3,
        k_c1_spare2,
        k_c1_spare1,
    };
    int c1_Pack(std::vector<uint8_t> &bits);
    int c1_Unpack(std::vector<uint8_t> bits);
    int c1_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    c1_Enum c1_Choice() const;
    int c1_SetChoice(c1_Enum choice);
    std::string c1_ChoiceToString(c1_Enum value) const;
    uint64_t c1_NumberOfChoices() const;
    std::string c1_ToString(uint32_t indent) const;
    std::string c1_ToStringNoNewLines() const;
    int c1_Clear();
    bool c1_IsPresent() const;
private:
    bool c1_present;
    c1_Enum c1_internal_choice;

    // csfbParametersResponseCDMA2000
public:
    CSFBParametersResponseCDMA2000* c1_csfbParametersResponseCDMA2000_Set();
    int c1_csfbParametersResponseCDMA2000_Set(CSFBParametersResponseCDMA2000 &value);
    const CSFBParametersResponseCDMA2000& c1_csfbParametersResponseCDMA2000_Get() const;
    std::string c1_csfbParametersResponseCDMA2000_ToString(uint32_t indent) const;
    std::string c1_csfbParametersResponseCDMA2000_ToStringNoNewLines() const;
    int c1_csfbParametersResponseCDMA2000_Clear();
    bool c1_csfbParametersResponseCDMA2000_IsPresent() const;
private:
    bool c1_csfbParametersResponseCDMA2000_present;
    CSFBParametersResponseCDMA2000 c1_csfbParametersResponseCDMA2000;

    // dlInformationTransfer
public:
    DLInformationTransfer* c1_dlInformationTransfer_Set();
    int c1_dlInformationTransfer_Set(DLInformationTransfer &value);
    const DLInformationTransfer& c1_dlInformationTransfer_Get() const;
    std::string c1_dlInformationTransfer_ToString(uint32_t indent) const;
    std::string c1_dlInformationTransfer_ToStringNoNewLines() const;
    int c1_dlInformationTransfer_Clear();
    bool c1_dlInformationTransfer_IsPresent() const;
private:
    bool c1_dlInformationTransfer_present;
    DLInformationTransfer c1_dlInformationTransfer;

    // handoverFromEUTRAPreparationRequest
public:
    HandoverFromEUTRAPreparationRequest* c1_handoverFromEUTRAPreparationRequest_Set();
    int c1_handoverFromEUTRAPreparationRequest_Set(HandoverFromEUTRAPreparationRequest &value);
    const HandoverFromEUTRAPreparationRequest& c1_handoverFromEUTRAPreparationRequest_Get() const;
    std::string c1_handoverFromEUTRAPreparationRequest_ToString(uint32_t indent) const;
    std::string c1_handoverFromEUTRAPreparationRequest_ToStringNoNewLines() const;
    int c1_handoverFromEUTRAPreparationRequest_Clear();
    bool c1_handoverFromEUTRAPreparationRequest_IsPresent() const;
private:
    bool c1_handoverFromEUTRAPreparationRequest_present;
    HandoverFromEUTRAPreparationRequest c1_handoverFromEUTRAPreparationRequest;

    // mobilityFromEUTRACommand
public:
    MobilityFromEUTRACommand* c1_mobilityFromEUTRACommand_Set();
    int c1_mobilityFromEUTRACommand_Set(MobilityFromEUTRACommand &value);
    const MobilityFromEUTRACommand& c1_mobilityFromEUTRACommand_Get() const;
    std::string c1_mobilityFromEUTRACommand_ToString(uint32_t indent) const;
    std::string c1_mobilityFromEUTRACommand_ToStringNoNewLines() const;
    int c1_mobilityFromEUTRACommand_Clear();
    bool c1_mobilityFromEUTRACommand_IsPresent() const;
private:
    bool c1_mobilityFromEUTRACommand_present;
    MobilityFromEUTRACommand c1_mobilityFromEUTRACommand;

    // rrcConnectionReconfiguration
public:
    RRCConnectionReconfiguration* c1_rrcConnectionReconfiguration_Set();
    int c1_rrcConnectionReconfiguration_Set(RRCConnectionReconfiguration &value);
    const RRCConnectionReconfiguration& c1_rrcConnectionReconfiguration_Get() const;
    std::string c1_rrcConnectionReconfiguration_ToString(uint32_t indent) const;
    std::string c1_rrcConnectionReconfiguration_ToStringNoNewLines() const;
    int c1_rrcConnectionReconfiguration_Clear();
    bool c1_rrcConnectionReconfiguration_IsPresent() const;
private:
    bool c1_rrcConnectionReconfiguration_present;
    RRCConnectionReconfiguration c1_rrcConnectionReconfiguration;

    // rrcConnectionRelease
public:
    RRCConnectionRelease* c1_rrcConnectionRelease_Set();
    int c1_rrcConnectionRelease_Set(RRCConnectionRelease &value);
    const RRCConnectionRelease& c1_rrcConnectionRelease_Get() const;
    std::string c1_rrcConnectionRelease_ToString(uint32_t indent) const;
    std::string c1_rrcConnectionRelease_ToStringNoNewLines() const;
    int c1_rrcConnectionRelease_Clear();
    bool c1_rrcConnectionRelease_IsPresent() const;
private:
    bool c1_rrcConnectionRelease_present;
    RRCConnectionRelease c1_rrcConnectionRelease;

    // securityModeCommand
public:
    SecurityModeCommand* c1_securityModeCommand_Set();
    int c1_securityModeCommand_Set(SecurityModeCommand &value);
    const SecurityModeCommand& c1_securityModeCommand_Get() const;
    std::string c1_securityModeCommand_ToString(uint32_t indent) const;
    std::string c1_securityModeCommand_ToStringNoNewLines() const;
    int c1_securityModeCommand_Clear();
    bool c1_securityModeCommand_IsPresent() const;
private:
    bool c1_securityModeCommand_present;
    SecurityModeCommand c1_securityModeCommand;

    // ueCapabilityEnquiry
public:
    UECapabilityEnquiry* c1_ueCapabilityEnquiry_Set();
    int c1_ueCapabilityEnquiry_Set(UECapabilityEnquiry &value);
    const UECapabilityEnquiry& c1_ueCapabilityEnquiry_Get() const;
    std::string c1_ueCapabilityEnquiry_ToString(uint32_t indent) const;
    std::string c1_ueCapabilityEnquiry_ToStringNoNewLines() const;
    int c1_ueCapabilityEnquiry_Clear();
    bool c1_ueCapabilityEnquiry_IsPresent() const;
private:
    bool c1_ueCapabilityEnquiry_present;
    UECapabilityEnquiry c1_ueCapabilityEnquiry;

    // counterCheck
public:
    CounterCheck* c1_counterCheck_Set();
    int c1_counterCheck_Set(CounterCheck &value);
    const CounterCheck& c1_counterCheck_Get() const;
    std::string c1_counterCheck_ToString(uint32_t indent) const;
    std::string c1_counterCheck_ToStringNoNewLines() const;
    int c1_counterCheck_Clear();
    bool c1_counterCheck_IsPresent() const;
private:
    bool c1_counterCheck_present;
    CounterCheck c1_counterCheck;

    // ueInformationRequest-r9
public:
    UEInformationRequest_r9* c1_ueInformationRequest_r9_Set();
    int c1_ueInformationRequest_r9_Set(UEInformationRequest_r9 &value);
    const UEInformationRequest_r9& c1_ueInformationRequest_r9_Get() const;
    std::string c1_ueInformationRequest_r9_ToString(uint32_t indent) const;
    std::string c1_ueInformationRequest_r9_ToStringNoNewLines() const;
    int c1_ueInformationRequest_r9_Clear();
    bool c1_ueInformationRequest_r9_IsPresent() const;
private:
    bool c1_ueInformationRequest_r9_present;
    UEInformationRequest_r9 c1_ueInformationRequest_r9;

    // loggedMeasurementsConfiguration-r10
public:
    LoggedMeasurementsConfiguration_r10* c1_loggedMeasurementsConfiguration_r10_Set();
    int c1_loggedMeasurementsConfiguration_r10_Set(LoggedMeasurementsConfiguration_r10 &value);
    const LoggedMeasurementsConfiguration_r10& c1_loggedMeasurementsConfiguration_r10_Get() const;
    std::string c1_loggedMeasurementsConfiguration_r10_ToString(uint32_t indent) const;
    std::string c1_loggedMeasurementsConfiguration_r10_ToStringNoNewLines() const;
    int c1_loggedMeasurementsConfiguration_r10_Clear();
    bool c1_loggedMeasurementsConfiguration_r10_IsPresent() const;
private:
    bool c1_loggedMeasurementsConfiguration_r10_present;
    LoggedMeasurementsConfiguration_r10 c1_loggedMeasurementsConfiguration_r10;

    // rnReconfiguration-r10
public:
    RNReconfiguration_r10* c1_rnReconfiguration_r10_Set();
    int c1_rnReconfiguration_r10_Set(RNReconfiguration_r10 &value);
    const RNReconfiguration_r10& c1_rnReconfiguration_r10_Get() const;
    std::string c1_rnReconfiguration_r10_ToString(uint32_t indent) const;
    std::string c1_rnReconfiguration_r10_ToStringNoNewLines() const;
    int c1_rnReconfiguration_r10_Clear();
    bool c1_rnReconfiguration_r10_IsPresent() const;
private:
    bool c1_rnReconfiguration_r10_present;
    RNReconfiguration_r10 c1_rnReconfiguration_r10;

    // spare4
public:
    int c1_spare4_Pack(std::vector<uint8_t> &bits) {return 0;};
    int c1_spare4_Unpack(std::vector<uint8_t> bits) {return 0;};
    int c1_spare4_Unpack(std::vector<uint8_t> bits, uint32_t &idx) {return 0;};
    bool c1_spare4_IsPresent() const {return true;};
    std::string c1_spare4_ToString(uint32_t indent) {return "";};
    std::string c1_spare4_ToStringNoNewLines() {return "";};

    // spare3
public:
    int c1_spare3_Pack(std::vector<uint8_t> &bits) {return 0;};
    int c1_spare3_Unpack(std::vector<uint8_t> bits) {return 0;};
    int c1_spare3_Unpack(std::vector<uint8_t> bits, uint32_t &idx) {return 0;};
    bool c1_spare3_IsPresent() const {return true;};
    std::string c1_spare3_ToString(uint32_t indent) {return "";};
    std::string c1_spare3_ToStringNoNewLines() {return "";};

    // spare2
public:
    int c1_spare2_Pack(std::vector<uint8_t> &bits) {return 0;};
    int c1_spare2_Unpack(std::vector<uint8_t> bits) {return 0;};
    int c1_spare2_Unpack(std::vector<uint8_t> bits, uint32_t &idx) {return 0;};
    bool c1_spare2_IsPresent() const {return true;};
    std::string c1_spare2_ToString(uint32_t indent) {return "";};
    std::string c1_spare2_ToStringNoNewLines() {return "";};

    // spare1
public:
    int c1_spare1_Pack(std::vector<uint8_t> &bits) {return 0;};
    int c1_spare1_Unpack(std::vector<uint8_t> bits) {return 0;};
    int c1_spare1_Unpack(std::vector<uint8_t> bits, uint32_t &idx) {return 0;};
    bool c1_spare1_IsPresent() const {return true;};
    std::string c1_spare1_ToString(uint32_t indent) {return "";};
    std::string c1_spare1_ToStringNoNewLines() {return "";};


    // messageClassExtension

};

#endif
