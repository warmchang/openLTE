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

#ifndef __UL_DCCH_MessageType_H__
#define __UL_DCCH_MessageType_H__

#include "CSFBParametersRequestCDMA2000.h"
#include "MeasurementReport.h"
#include "RRCConnectionReconfigurationComplete.h"
#include "RRCConnectionReestablishmentComplete.h"
#include "RRCConnectionSetupComplete.h"
#include "SecurityModeComplete.h"
#include "SecurityModeFailure.h"
#include "UECapabilityInformation.h"
#include "ULHandoverPreparationTransfer.h"
#include "ULInformationTransfer.h"
#include "CounterCheckResponse.h"
#include "UEInformationResponse_r9.h"
#include "ProximityIndication_r9.h"
#include "RNReconfigurationComplete_r10.h"

#include <array>
#include <cstdint>
#include <vector>

class UL_DCCH_MessageType
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
        k_c1_csfbParametersRequestCDMA2000 = 0,
        k_c1_measurementReport,
        k_c1_rrcConnectionReconfigurationComplete,
        k_c1_rrcConnectionReestablishmentComplete,
        k_c1_rrcConnectionSetupComplete,
        k_c1_securityModeComplete,
        k_c1_securityModeFailure,
        k_c1_ueCapabilityInformation,
        k_c1_ulHandoverPreparationTransfer,
        k_c1_ulInformationTransfer,
        k_c1_counterCheckResponse,
        k_c1_ueInformationResponse_r9,
        k_c1_proximityIndication_r9,
        k_c1_rnReconfigurationComplete_r10,
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

    // csfbParametersRequestCDMA2000
public:
    CSFBParametersRequestCDMA2000* c1_csfbParametersRequestCDMA2000_Set();
    int c1_csfbParametersRequestCDMA2000_Set(CSFBParametersRequestCDMA2000 &value);
    const CSFBParametersRequestCDMA2000& c1_csfbParametersRequestCDMA2000_Get() const;
    std::string c1_csfbParametersRequestCDMA2000_ToString(uint32_t indent) const;
    std::string c1_csfbParametersRequestCDMA2000_ToStringNoNewLines() const;
    int c1_csfbParametersRequestCDMA2000_Clear();
    bool c1_csfbParametersRequestCDMA2000_IsPresent() const;
private:
    bool c1_csfbParametersRequestCDMA2000_present;
    CSFBParametersRequestCDMA2000 c1_csfbParametersRequestCDMA2000;

    // measurementReport
public:
    MeasurementReport* c1_measurementReport_Set();
    int c1_measurementReport_Set(MeasurementReport &value);
    const MeasurementReport& c1_measurementReport_Get() const;
    std::string c1_measurementReport_ToString(uint32_t indent) const;
    std::string c1_measurementReport_ToStringNoNewLines() const;
    int c1_measurementReport_Clear();
    bool c1_measurementReport_IsPresent() const;
private:
    bool c1_measurementReport_present;
    MeasurementReport c1_measurementReport;

    // rrcConnectionReconfigurationComplete
public:
    RRCConnectionReconfigurationComplete* c1_rrcConnectionReconfigurationComplete_Set();
    int c1_rrcConnectionReconfigurationComplete_Set(RRCConnectionReconfigurationComplete &value);
    const RRCConnectionReconfigurationComplete& c1_rrcConnectionReconfigurationComplete_Get() const;
    std::string c1_rrcConnectionReconfigurationComplete_ToString(uint32_t indent) const;
    std::string c1_rrcConnectionReconfigurationComplete_ToStringNoNewLines() const;
    int c1_rrcConnectionReconfigurationComplete_Clear();
    bool c1_rrcConnectionReconfigurationComplete_IsPresent() const;
private:
    bool c1_rrcConnectionReconfigurationComplete_present;
    RRCConnectionReconfigurationComplete c1_rrcConnectionReconfigurationComplete;

    // rrcConnectionReestablishmentComplete
public:
    RRCConnectionReestablishmentComplete* c1_rrcConnectionReestablishmentComplete_Set();
    int c1_rrcConnectionReestablishmentComplete_Set(RRCConnectionReestablishmentComplete &value);
    const RRCConnectionReestablishmentComplete& c1_rrcConnectionReestablishmentComplete_Get() const;
    std::string c1_rrcConnectionReestablishmentComplete_ToString(uint32_t indent) const;
    std::string c1_rrcConnectionReestablishmentComplete_ToStringNoNewLines() const;
    int c1_rrcConnectionReestablishmentComplete_Clear();
    bool c1_rrcConnectionReestablishmentComplete_IsPresent() const;
private:
    bool c1_rrcConnectionReestablishmentComplete_present;
    RRCConnectionReestablishmentComplete c1_rrcConnectionReestablishmentComplete;

    // rrcConnectionSetupComplete
public:
    RRCConnectionSetupComplete* c1_rrcConnectionSetupComplete_Set();
    int c1_rrcConnectionSetupComplete_Set(RRCConnectionSetupComplete &value);
    const RRCConnectionSetupComplete& c1_rrcConnectionSetupComplete_Get() const;
    std::string c1_rrcConnectionSetupComplete_ToString(uint32_t indent) const;
    std::string c1_rrcConnectionSetupComplete_ToStringNoNewLines() const;
    int c1_rrcConnectionSetupComplete_Clear();
    bool c1_rrcConnectionSetupComplete_IsPresent() const;
private:
    bool c1_rrcConnectionSetupComplete_present;
    RRCConnectionSetupComplete c1_rrcConnectionSetupComplete;

    // securityModeComplete
public:
    SecurityModeComplete* c1_securityModeComplete_Set();
    int c1_securityModeComplete_Set(SecurityModeComplete &value);
    const SecurityModeComplete& c1_securityModeComplete_Get() const;
    std::string c1_securityModeComplete_ToString(uint32_t indent) const;
    std::string c1_securityModeComplete_ToStringNoNewLines() const;
    int c1_securityModeComplete_Clear();
    bool c1_securityModeComplete_IsPresent() const;
private:
    bool c1_securityModeComplete_present;
    SecurityModeComplete c1_securityModeComplete;

    // securityModeFailure
public:
    SecurityModeFailure* c1_securityModeFailure_Set();
    int c1_securityModeFailure_Set(SecurityModeFailure &value);
    const SecurityModeFailure& c1_securityModeFailure_Get() const;
    std::string c1_securityModeFailure_ToString(uint32_t indent) const;
    std::string c1_securityModeFailure_ToStringNoNewLines() const;
    int c1_securityModeFailure_Clear();
    bool c1_securityModeFailure_IsPresent() const;
private:
    bool c1_securityModeFailure_present;
    SecurityModeFailure c1_securityModeFailure;

    // ueCapabilityInformation
public:
    UECapabilityInformation* c1_ueCapabilityInformation_Set();
    int c1_ueCapabilityInformation_Set(UECapabilityInformation &value);
    const UECapabilityInformation& c1_ueCapabilityInformation_Get() const;
    std::string c1_ueCapabilityInformation_ToString(uint32_t indent) const;
    std::string c1_ueCapabilityInformation_ToStringNoNewLines() const;
    int c1_ueCapabilityInformation_Clear();
    bool c1_ueCapabilityInformation_IsPresent() const;
private:
    bool c1_ueCapabilityInformation_present;
    UECapabilityInformation c1_ueCapabilityInformation;

    // ulHandoverPreparationTransfer
public:
    ULHandoverPreparationTransfer* c1_ulHandoverPreparationTransfer_Set();
    int c1_ulHandoverPreparationTransfer_Set(ULHandoverPreparationTransfer &value);
    const ULHandoverPreparationTransfer& c1_ulHandoverPreparationTransfer_Get() const;
    std::string c1_ulHandoverPreparationTransfer_ToString(uint32_t indent) const;
    std::string c1_ulHandoverPreparationTransfer_ToStringNoNewLines() const;
    int c1_ulHandoverPreparationTransfer_Clear();
    bool c1_ulHandoverPreparationTransfer_IsPresent() const;
private:
    bool c1_ulHandoverPreparationTransfer_present;
    ULHandoverPreparationTransfer c1_ulHandoverPreparationTransfer;

    // ulInformationTransfer
public:
    ULInformationTransfer* c1_ulInformationTransfer_Set();
    int c1_ulInformationTransfer_Set(ULInformationTransfer &value);
    const ULInformationTransfer& c1_ulInformationTransfer_Get() const;
    std::string c1_ulInformationTransfer_ToString(uint32_t indent) const;
    std::string c1_ulInformationTransfer_ToStringNoNewLines() const;
    int c1_ulInformationTransfer_Clear();
    bool c1_ulInformationTransfer_IsPresent() const;
private:
    bool c1_ulInformationTransfer_present;
    ULInformationTransfer c1_ulInformationTransfer;

    // counterCheckResponse
public:
    CounterCheckResponse* c1_counterCheckResponse_Set();
    int c1_counterCheckResponse_Set(CounterCheckResponse &value);
    const CounterCheckResponse& c1_counterCheckResponse_Get() const;
    std::string c1_counterCheckResponse_ToString(uint32_t indent) const;
    std::string c1_counterCheckResponse_ToStringNoNewLines() const;
    int c1_counterCheckResponse_Clear();
    bool c1_counterCheckResponse_IsPresent() const;
private:
    bool c1_counterCheckResponse_present;
    CounterCheckResponse c1_counterCheckResponse;

    // ueInformationResponse-r9
public:
    UEInformationResponse_r9* c1_ueInformationResponse_r9_Set();
    int c1_ueInformationResponse_r9_Set(UEInformationResponse_r9 &value);
    const UEInformationResponse_r9& c1_ueInformationResponse_r9_Get() const;
    std::string c1_ueInformationResponse_r9_ToString(uint32_t indent) const;
    std::string c1_ueInformationResponse_r9_ToStringNoNewLines() const;
    int c1_ueInformationResponse_r9_Clear();
    bool c1_ueInformationResponse_r9_IsPresent() const;
private:
    bool c1_ueInformationResponse_r9_present;
    UEInformationResponse_r9 c1_ueInformationResponse_r9;

    // proximityIndication-r9
public:
    ProximityIndication_r9* c1_proximityIndication_r9_Set();
    int c1_proximityIndication_r9_Set(ProximityIndication_r9 &value);
    const ProximityIndication_r9& c1_proximityIndication_r9_Get() const;
    std::string c1_proximityIndication_r9_ToString(uint32_t indent) const;
    std::string c1_proximityIndication_r9_ToStringNoNewLines() const;
    int c1_proximityIndication_r9_Clear();
    bool c1_proximityIndication_r9_IsPresent() const;
private:
    bool c1_proximityIndication_r9_present;
    ProximityIndication_r9 c1_proximityIndication_r9;

    // rnReconfigurationComplete-r10
public:
    RNReconfigurationComplete_r10* c1_rnReconfigurationComplete_r10_Set();
    int c1_rnReconfigurationComplete_r10_Set(RNReconfigurationComplete_r10 &value);
    const RNReconfigurationComplete_r10& c1_rnReconfigurationComplete_r10_Get() const;
    std::string c1_rnReconfigurationComplete_r10_ToString(uint32_t indent) const;
    std::string c1_rnReconfigurationComplete_r10_ToStringNoNewLines() const;
    int c1_rnReconfigurationComplete_r10_Clear();
    bool c1_rnReconfigurationComplete_r10_IsPresent() const;
private:
    bool c1_rnReconfigurationComplete_r10_present;
    RNReconfigurationComplete_r10 c1_rnReconfigurationComplete_r10;

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
