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

#include "UL_DCCH_MessageType.h"

#include <cmath>

int UL_DCCH_MessageType::Pack(std::vector<uint8_t> &bits)
{
    if(!present)
    {
        printf("UL_DCCH_MessageType::Pack() presence failure\n");
        return -1;
    }
    // Extension indicator

    // Choice
    for(uint32_t i=0; i<1; i++)
        bits.push_back((internal_choice >> (1-i-1)) & 1);

    // Fields
    if(internal_choice == k_c1)
    {
        if(0 != c1_Pack(bits))
        {
            printf("UL_DCCH_MessageType::c1 pack failure\n");
            return -1;
        }
    }
    return 0;
}

int UL_DCCH_MessageType::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int UL_DCCH_MessageType::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 1) > bits.size())
    {
        printf("UL_DCCH_MessageType::Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<1; i++)
        packed_val |= bits[idx++] << (1-i-1);

    if((UL_DCCH_MessageType::Enum)packed_val > k_messageClassExtension)
    {
        printf("UL_DCCH_MessageType::Unpack() choice range failure\n");
        return -1;
    }
    internal_choice = (UL_DCCH_MessageType::Enum)packed_val;
    present = true;

    // Fields
    if(internal_choice == k_c1)
    {
        if(0 != c1_Unpack(bits, idx))
        {
            printf("UL_DCCH_MessageType::c1 unpack failure\n");
            return -1;
        }
    }
    return 0;
}

UL_DCCH_MessageType::Enum UL_DCCH_MessageType::Choice() const
{
    if(present)
        return internal_choice;
    return (UL_DCCH_MessageType::Enum)0;
}

int UL_DCCH_MessageType::SetChoice(UL_DCCH_MessageType::Enum choice)
{
    internal_choice = choice;
    present = true;
    return 0;
}

std::string UL_DCCH_MessageType::ChoiceToString(Enum value) const
{
    if(k_c1 == value)
        return "c1";
    if(k_messageClassExtension == value)
        return "messageClassExtension";
    return "";
}

uint64_t UL_DCCH_MessageType::NumberOfChoices() const
{
    return 2;
}

std::string UL_DCCH_MessageType::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "UL_DCCH_MessageType = " + ChoiceToString(internal_choice) + ":\n";
    if(internal_choice == k_c1)
        out += c1_ToString(indent+1);
    return out;
}

std::string UL_DCCH_MessageType::ToStringNoNewLines() const
{
    std::string out = "UL_DCCH_MessageType=" + ChoiceToString(internal_choice) + ",";
    if(internal_choice == k_c1)
        out += c1_ToStringNoNewLines();
    return out;
}

int UL_DCCH_MessageType::Clear()
{
    present = false;
    return 0;
}

bool UL_DCCH_MessageType::IsPresent() const
{
    return present;
}

int UL_DCCH_MessageType::c1_Pack(std::vector<uint8_t> &bits)
{
    if(!c1_present)
    {
        printf("UL_DCCH_MessageType::c1_Pack() presence failure\n");
        return -1;
    }
    // Extension indicator

    // Choice
    for(uint32_t i=0; i<4; i++)
        bits.push_back((c1_internal_choice >> (4-i-1)) & 1);

    // Fields
    if(c1_internal_choice == k_c1_csfbParametersRequestCDMA2000)
    {
        if(0 != c1_csfbParametersRequestCDMA2000.Pack(bits))
        {
            printf("UL_DCCH_MessageType::c1_csfbParametersRequestCDMA2000 pack failure\n");
            return -1;
        }
    }
    if(c1_internal_choice == k_c1_measurementReport)
    {
        if(0 != c1_measurementReport.Pack(bits))
        {
            printf("UL_DCCH_MessageType::c1_measurementReport pack failure\n");
            return -1;
        }
    }
    if(c1_internal_choice == k_c1_rrcConnectionReconfigurationComplete)
    {
        if(0 != c1_rrcConnectionReconfigurationComplete.Pack(bits))
        {
            printf("UL_DCCH_MessageType::c1_rrcConnectionReconfigurationComplete pack failure\n");
            return -1;
        }
    }
    if(c1_internal_choice == k_c1_rrcConnectionReestablishmentComplete)
    {
        if(0 != c1_rrcConnectionReestablishmentComplete.Pack(bits))
        {
            printf("UL_DCCH_MessageType::c1_rrcConnectionReestablishmentComplete pack failure\n");
            return -1;
        }
    }
    if(c1_internal_choice == k_c1_rrcConnectionSetupComplete)
    {
        if(0 != c1_rrcConnectionSetupComplete.Pack(bits))
        {
            printf("UL_DCCH_MessageType::c1_rrcConnectionSetupComplete pack failure\n");
            return -1;
        }
    }
    if(c1_internal_choice == k_c1_securityModeComplete)
    {
        if(0 != c1_securityModeComplete.Pack(bits))
        {
            printf("UL_DCCH_MessageType::c1_securityModeComplete pack failure\n");
            return -1;
        }
    }
    if(c1_internal_choice == k_c1_securityModeFailure)
    {
        if(0 != c1_securityModeFailure.Pack(bits))
        {
            printf("UL_DCCH_MessageType::c1_securityModeFailure pack failure\n");
            return -1;
        }
    }
    if(c1_internal_choice == k_c1_ueCapabilityInformation)
    {
        if(0 != c1_ueCapabilityInformation.Pack(bits))
        {
            printf("UL_DCCH_MessageType::c1_ueCapabilityInformation pack failure\n");
            return -1;
        }
    }
    if(c1_internal_choice == k_c1_ulHandoverPreparationTransfer)
    {
        if(0 != c1_ulHandoverPreparationTransfer.Pack(bits))
        {
            printf("UL_DCCH_MessageType::c1_ulHandoverPreparationTransfer pack failure\n");
            return -1;
        }
    }
    if(c1_internal_choice == k_c1_ulInformationTransfer)
    {
        if(0 != c1_ulInformationTransfer.Pack(bits))
        {
            printf("UL_DCCH_MessageType::c1_ulInformationTransfer pack failure\n");
            return -1;
        }
    }
    if(c1_internal_choice == k_c1_counterCheckResponse)
    {
        if(0 != c1_counterCheckResponse.Pack(bits))
        {
            printf("UL_DCCH_MessageType::c1_counterCheckResponse pack failure\n");
            return -1;
        }
    }
    if(c1_internal_choice == k_c1_ueInformationResponse_r9)
    {
        if(0 != c1_ueInformationResponse_r9.Pack(bits))
        {
            printf("UL_DCCH_MessageType::c1_ueInformationResponse_r9 pack failure\n");
            return -1;
        }
    }
    if(c1_internal_choice == k_c1_proximityIndication_r9)
    {
        if(0 != c1_proximityIndication_r9.Pack(bits))
        {
            printf("UL_DCCH_MessageType::c1_proximityIndication_r9 pack failure\n");
            return -1;
        }
    }
    if(c1_internal_choice == k_c1_rnReconfigurationComplete_r10)
    {
        if(0 != c1_rnReconfigurationComplete_r10.Pack(bits))
        {
            printf("UL_DCCH_MessageType::c1_rnReconfigurationComplete_r10 pack failure\n");
            return -1;
        }
    }
    if(c1_internal_choice == k_c1_spare2)
    {
        if(0 != c1_spare2_Pack(bits))
        {
            printf("UL_DCCH_MessageType::c1_spare2 pack failure\n");
            return -1;
        }
    }
    if(c1_internal_choice == k_c1_spare1)
    {
        if(0 != c1_spare1_Pack(bits))
        {
            printf("UL_DCCH_MessageType::c1_spare1 pack failure\n");
            return -1;
        }
    }
    return 0;
}

int UL_DCCH_MessageType::c1_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return c1_Unpack(bits, idx);
}

int UL_DCCH_MessageType::c1_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 4) > bits.size())
    {
        printf("UL_DCCH_MessageType::c1_Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<4; i++)
        packed_val |= bits[idx++] << (4-i-1);

    if((UL_DCCH_MessageType::c1_Enum)packed_val > k_c1_spare1)
    {
        printf("UL_DCCH_MessageType::c1_Unpack() choice range failure\n");
        return -1;
    }
    c1_internal_choice = (UL_DCCH_MessageType::c1_Enum)packed_val;
    c1_present = true;

    // Fields
    if(c1_internal_choice == k_c1_csfbParametersRequestCDMA2000)
    {
        if(0 != c1_csfbParametersRequestCDMA2000.Unpack(bits, idx))
        {
            printf("UL_DCCH_MessageType::c1_csfbParametersRequestCDMA2000 unpack failure\n");
            return -1;
        }
    }
    if(c1_internal_choice == k_c1_measurementReport)
    {
        if(0 != c1_measurementReport.Unpack(bits, idx))
        {
            printf("UL_DCCH_MessageType::c1_measurementReport unpack failure\n");
            return -1;
        }
    }
    if(c1_internal_choice == k_c1_rrcConnectionReconfigurationComplete)
    {
        if(0 != c1_rrcConnectionReconfigurationComplete.Unpack(bits, idx))
        {
            printf("UL_DCCH_MessageType::c1_rrcConnectionReconfigurationComplete unpack failure\n");
            return -1;
        }
    }
    if(c1_internal_choice == k_c1_rrcConnectionReestablishmentComplete)
    {
        if(0 != c1_rrcConnectionReestablishmentComplete.Unpack(bits, idx))
        {
            printf("UL_DCCH_MessageType::c1_rrcConnectionReestablishmentComplete unpack failure\n");
            return -1;
        }
    }
    if(c1_internal_choice == k_c1_rrcConnectionSetupComplete)
    {
        if(0 != c1_rrcConnectionSetupComplete.Unpack(bits, idx))
        {
            printf("UL_DCCH_MessageType::c1_rrcConnectionSetupComplete unpack failure\n");
            return -1;
        }
    }
    if(c1_internal_choice == k_c1_securityModeComplete)
    {
        if(0 != c1_securityModeComplete.Unpack(bits, idx))
        {
            printf("UL_DCCH_MessageType::c1_securityModeComplete unpack failure\n");
            return -1;
        }
    }
    if(c1_internal_choice == k_c1_securityModeFailure)
    {
        if(0 != c1_securityModeFailure.Unpack(bits, idx))
        {
            printf("UL_DCCH_MessageType::c1_securityModeFailure unpack failure\n");
            return -1;
        }
    }
    if(c1_internal_choice == k_c1_ueCapabilityInformation)
    {
        if(0 != c1_ueCapabilityInformation.Unpack(bits, idx))
        {
            printf("UL_DCCH_MessageType::c1_ueCapabilityInformation unpack failure\n");
            return -1;
        }
    }
    if(c1_internal_choice == k_c1_ulHandoverPreparationTransfer)
    {
        if(0 != c1_ulHandoverPreparationTransfer.Unpack(bits, idx))
        {
            printf("UL_DCCH_MessageType::c1_ulHandoverPreparationTransfer unpack failure\n");
            return -1;
        }
    }
    if(c1_internal_choice == k_c1_ulInformationTransfer)
    {
        if(0 != c1_ulInformationTransfer.Unpack(bits, idx))
        {
            printf("UL_DCCH_MessageType::c1_ulInformationTransfer unpack failure\n");
            return -1;
        }
    }
    if(c1_internal_choice == k_c1_counterCheckResponse)
    {
        if(0 != c1_counterCheckResponse.Unpack(bits, idx))
        {
            printf("UL_DCCH_MessageType::c1_counterCheckResponse unpack failure\n");
            return -1;
        }
    }
    if(c1_internal_choice == k_c1_ueInformationResponse_r9)
    {
        if(0 != c1_ueInformationResponse_r9.Unpack(bits, idx))
        {
            printf("UL_DCCH_MessageType::c1_ueInformationResponse_r9 unpack failure\n");
            return -1;
        }
    }
    if(c1_internal_choice == k_c1_proximityIndication_r9)
    {
        if(0 != c1_proximityIndication_r9.Unpack(bits, idx))
        {
            printf("UL_DCCH_MessageType::c1_proximityIndication_r9 unpack failure\n");
            return -1;
        }
    }
    if(c1_internal_choice == k_c1_rnReconfigurationComplete_r10)
    {
        if(0 != c1_rnReconfigurationComplete_r10.Unpack(bits, idx))
        {
            printf("UL_DCCH_MessageType::c1_rnReconfigurationComplete_r10 unpack failure\n");
            return -1;
        }
    }
    if(c1_internal_choice == k_c1_spare2)
    {
        if(0 != c1_spare2_Unpack(bits, idx))
        {
            printf("UL_DCCH_MessageType::c1_spare2 unpack failure\n");
            return -1;
        }
    }
    if(c1_internal_choice == k_c1_spare1)
    {
        if(0 != c1_spare1_Unpack(bits, idx))
        {
            printf("UL_DCCH_MessageType::c1_spare1 unpack failure\n");
            return -1;
        }
    }
    return 0;
}

UL_DCCH_MessageType::c1_Enum UL_DCCH_MessageType::c1_Choice() const
{
    if(c1_present)
        return c1_internal_choice;
    return (UL_DCCH_MessageType::c1_Enum)0;
}

int UL_DCCH_MessageType::c1_SetChoice(UL_DCCH_MessageType::c1_Enum choice)
{
    c1_internal_choice = choice;
    c1_present = true;
    return 0;
}

std::string UL_DCCH_MessageType::c1_ChoiceToString(c1_Enum value) const
{
    if(k_c1_csfbParametersRequestCDMA2000 == value)
        return "c1_csfbParametersRequestCDMA2000";
    if(k_c1_measurementReport == value)
        return "c1_measurementReport";
    if(k_c1_rrcConnectionReconfigurationComplete == value)
        return "c1_rrcConnectionReconfigurationComplete";
    if(k_c1_rrcConnectionReestablishmentComplete == value)
        return "c1_rrcConnectionReestablishmentComplete";
    if(k_c1_rrcConnectionSetupComplete == value)
        return "c1_rrcConnectionSetupComplete";
    if(k_c1_securityModeComplete == value)
        return "c1_securityModeComplete";
    if(k_c1_securityModeFailure == value)
        return "c1_securityModeFailure";
    if(k_c1_ueCapabilityInformation == value)
        return "c1_ueCapabilityInformation";
    if(k_c1_ulHandoverPreparationTransfer == value)
        return "c1_ulHandoverPreparationTransfer";
    if(k_c1_ulInformationTransfer == value)
        return "c1_ulInformationTransfer";
    if(k_c1_counterCheckResponse == value)
        return "c1_counterCheckResponse";
    if(k_c1_ueInformationResponse_r9 == value)
        return "c1_ueInformationResponse_r9";
    if(k_c1_proximityIndication_r9 == value)
        return "c1_proximityIndication_r9";
    if(k_c1_rnReconfigurationComplete_r10 == value)
        return "c1_rnReconfigurationComplete_r10";
    if(k_c1_spare2 == value)
        return "c1_spare2";
    if(k_c1_spare1 == value)
        return "c1_spare1";
    return "";
}

uint64_t UL_DCCH_MessageType::c1_NumberOfChoices() const
{
    return 16;
}

std::string UL_DCCH_MessageType::c1_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "c1 = " + c1_ChoiceToString(c1_internal_choice) + ":\n";
    if(c1_internal_choice == k_c1_csfbParametersRequestCDMA2000)
        out += c1_csfbParametersRequestCDMA2000.ToString(indent+1);
    if(c1_internal_choice == k_c1_measurementReport)
        out += c1_measurementReport.ToString(indent+1);
    if(c1_internal_choice == k_c1_rrcConnectionReconfigurationComplete)
        out += c1_rrcConnectionReconfigurationComplete.ToString(indent+1);
    if(c1_internal_choice == k_c1_rrcConnectionReestablishmentComplete)
        out += c1_rrcConnectionReestablishmentComplete.ToString(indent+1);
    if(c1_internal_choice == k_c1_rrcConnectionSetupComplete)
        out += c1_rrcConnectionSetupComplete.ToString(indent+1);
    if(c1_internal_choice == k_c1_securityModeComplete)
        out += c1_securityModeComplete.ToString(indent+1);
    if(c1_internal_choice == k_c1_securityModeFailure)
        out += c1_securityModeFailure.ToString(indent+1);
    if(c1_internal_choice == k_c1_ueCapabilityInformation)
        out += c1_ueCapabilityInformation.ToString(indent+1);
    if(c1_internal_choice == k_c1_ulHandoverPreparationTransfer)
        out += c1_ulHandoverPreparationTransfer.ToString(indent+1);
    if(c1_internal_choice == k_c1_ulInformationTransfer)
        out += c1_ulInformationTransfer.ToString(indent+1);
    if(c1_internal_choice == k_c1_counterCheckResponse)
        out += c1_counterCheckResponse.ToString(indent+1);
    if(c1_internal_choice == k_c1_ueInformationResponse_r9)
        out += c1_ueInformationResponse_r9.ToString(indent+1);
    if(c1_internal_choice == k_c1_proximityIndication_r9)
        out += c1_proximityIndication_r9.ToString(indent+1);
    if(c1_internal_choice == k_c1_rnReconfigurationComplete_r10)
        out += c1_rnReconfigurationComplete_r10.ToString(indent+1);
    return out;
}

std::string UL_DCCH_MessageType::c1_ToStringNoNewLines() const
{
    std::string out = "c1=" + c1_ChoiceToString(c1_internal_choice) + ",";
    if(c1_internal_choice == k_c1_csfbParametersRequestCDMA2000)
        out += c1_csfbParametersRequestCDMA2000.ToStringNoNewLines();
    if(c1_internal_choice == k_c1_measurementReport)
        out += c1_measurementReport.ToStringNoNewLines();
    if(c1_internal_choice == k_c1_rrcConnectionReconfigurationComplete)
        out += c1_rrcConnectionReconfigurationComplete.ToStringNoNewLines();
    if(c1_internal_choice == k_c1_rrcConnectionReestablishmentComplete)
        out += c1_rrcConnectionReestablishmentComplete.ToStringNoNewLines();
    if(c1_internal_choice == k_c1_rrcConnectionSetupComplete)
        out += c1_rrcConnectionSetupComplete.ToStringNoNewLines();
    if(c1_internal_choice == k_c1_securityModeComplete)
        out += c1_securityModeComplete.ToStringNoNewLines();
    if(c1_internal_choice == k_c1_securityModeFailure)
        out += c1_securityModeFailure.ToStringNoNewLines();
    if(c1_internal_choice == k_c1_ueCapabilityInformation)
        out += c1_ueCapabilityInformation.ToStringNoNewLines();
    if(c1_internal_choice == k_c1_ulHandoverPreparationTransfer)
        out += c1_ulHandoverPreparationTransfer.ToStringNoNewLines();
    if(c1_internal_choice == k_c1_ulInformationTransfer)
        out += c1_ulInformationTransfer.ToStringNoNewLines();
    if(c1_internal_choice == k_c1_counterCheckResponse)
        out += c1_counterCheckResponse.ToStringNoNewLines();
    if(c1_internal_choice == k_c1_ueInformationResponse_r9)
        out += c1_ueInformationResponse_r9.ToStringNoNewLines();
    if(c1_internal_choice == k_c1_proximityIndication_r9)
        out += c1_proximityIndication_r9.ToStringNoNewLines();
    if(c1_internal_choice == k_c1_rnReconfigurationComplete_r10)
        out += c1_rnReconfigurationComplete_r10.ToStringNoNewLines();
    return out;
}

int UL_DCCH_MessageType::c1_Clear()
{
    c1_present = false;
    return 0;
}

bool UL_DCCH_MessageType::c1_IsPresent() const
{
    return c1_present;
}

CSFBParametersRequestCDMA2000* UL_DCCH_MessageType::c1_csfbParametersRequestCDMA2000_Set()
{
    c1_csfbParametersRequestCDMA2000_present = true;
    return &c1_csfbParametersRequestCDMA2000;
}

int UL_DCCH_MessageType::c1_csfbParametersRequestCDMA2000_Set(CSFBParametersRequestCDMA2000 &value)
{
    c1_csfbParametersRequestCDMA2000_present = true;
    c1_csfbParametersRequestCDMA2000 = value;
    return 0;
}

const CSFBParametersRequestCDMA2000& UL_DCCH_MessageType::c1_csfbParametersRequestCDMA2000_Get() const
{
    return c1_csfbParametersRequestCDMA2000;
}

std::string UL_DCCH_MessageType::c1_csfbParametersRequestCDMA2000_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "csfbParametersRequestCDMA2000:\n";
    out += c1_csfbParametersRequestCDMA2000.ToString(indent+1);
    return out;
}

std::string UL_DCCH_MessageType::c1_csfbParametersRequestCDMA2000_ToStringNoNewLines() const
{
    std::string out = "csfbParametersRequestCDMA2000:";
    out += c1_csfbParametersRequestCDMA2000.ToStringNoNewLines();
    return out;
}

int UL_DCCH_MessageType::c1_csfbParametersRequestCDMA2000_Clear()
{
    c1_csfbParametersRequestCDMA2000_present = false;
    return 0;
}

bool UL_DCCH_MessageType::c1_csfbParametersRequestCDMA2000_IsPresent() const
{
    return c1_csfbParametersRequestCDMA2000_present;
}

MeasurementReport* UL_DCCH_MessageType::c1_measurementReport_Set()
{
    c1_measurementReport_present = true;
    return &c1_measurementReport;
}

int UL_DCCH_MessageType::c1_measurementReport_Set(MeasurementReport &value)
{
    c1_measurementReport_present = true;
    c1_measurementReport = value;
    return 0;
}

const MeasurementReport& UL_DCCH_MessageType::c1_measurementReport_Get() const
{
    return c1_measurementReport;
}

std::string UL_DCCH_MessageType::c1_measurementReport_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "measurementReport:\n";
    out += c1_measurementReport.ToString(indent+1);
    return out;
}

std::string UL_DCCH_MessageType::c1_measurementReport_ToStringNoNewLines() const
{
    std::string out = "measurementReport:";
    out += c1_measurementReport.ToStringNoNewLines();
    return out;
}

int UL_DCCH_MessageType::c1_measurementReport_Clear()
{
    c1_measurementReport_present = false;
    return 0;
}

bool UL_DCCH_MessageType::c1_measurementReport_IsPresent() const
{
    return c1_measurementReport_present;
}

RRCConnectionReconfigurationComplete* UL_DCCH_MessageType::c1_rrcConnectionReconfigurationComplete_Set()
{
    c1_rrcConnectionReconfigurationComplete_present = true;
    return &c1_rrcConnectionReconfigurationComplete;
}

int UL_DCCH_MessageType::c1_rrcConnectionReconfigurationComplete_Set(RRCConnectionReconfigurationComplete &value)
{
    c1_rrcConnectionReconfigurationComplete_present = true;
    c1_rrcConnectionReconfigurationComplete = value;
    return 0;
}

const RRCConnectionReconfigurationComplete& UL_DCCH_MessageType::c1_rrcConnectionReconfigurationComplete_Get() const
{
    return c1_rrcConnectionReconfigurationComplete;
}

std::string UL_DCCH_MessageType::c1_rrcConnectionReconfigurationComplete_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "rrcConnectionReconfigurationComplete:\n";
    out += c1_rrcConnectionReconfigurationComplete.ToString(indent+1);
    return out;
}

std::string UL_DCCH_MessageType::c1_rrcConnectionReconfigurationComplete_ToStringNoNewLines() const
{
    std::string out = "rrcConnectionReconfigurationComplete:";
    out += c1_rrcConnectionReconfigurationComplete.ToStringNoNewLines();
    return out;
}

int UL_DCCH_MessageType::c1_rrcConnectionReconfigurationComplete_Clear()
{
    c1_rrcConnectionReconfigurationComplete_present = false;
    return 0;
}

bool UL_DCCH_MessageType::c1_rrcConnectionReconfigurationComplete_IsPresent() const
{
    return c1_rrcConnectionReconfigurationComplete_present;
}

RRCConnectionReestablishmentComplete* UL_DCCH_MessageType::c1_rrcConnectionReestablishmentComplete_Set()
{
    c1_rrcConnectionReestablishmentComplete_present = true;
    return &c1_rrcConnectionReestablishmentComplete;
}

int UL_DCCH_MessageType::c1_rrcConnectionReestablishmentComplete_Set(RRCConnectionReestablishmentComplete &value)
{
    c1_rrcConnectionReestablishmentComplete_present = true;
    c1_rrcConnectionReestablishmentComplete = value;
    return 0;
}

const RRCConnectionReestablishmentComplete& UL_DCCH_MessageType::c1_rrcConnectionReestablishmentComplete_Get() const
{
    return c1_rrcConnectionReestablishmentComplete;
}

std::string UL_DCCH_MessageType::c1_rrcConnectionReestablishmentComplete_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "rrcConnectionReestablishmentComplete:\n";
    out += c1_rrcConnectionReestablishmentComplete.ToString(indent+1);
    return out;
}

std::string UL_DCCH_MessageType::c1_rrcConnectionReestablishmentComplete_ToStringNoNewLines() const
{
    std::string out = "rrcConnectionReestablishmentComplete:";
    out += c1_rrcConnectionReestablishmentComplete.ToStringNoNewLines();
    return out;
}

int UL_DCCH_MessageType::c1_rrcConnectionReestablishmentComplete_Clear()
{
    c1_rrcConnectionReestablishmentComplete_present = false;
    return 0;
}

bool UL_DCCH_MessageType::c1_rrcConnectionReestablishmentComplete_IsPresent() const
{
    return c1_rrcConnectionReestablishmentComplete_present;
}

RRCConnectionSetupComplete* UL_DCCH_MessageType::c1_rrcConnectionSetupComplete_Set()
{
    c1_rrcConnectionSetupComplete_present = true;
    return &c1_rrcConnectionSetupComplete;
}

int UL_DCCH_MessageType::c1_rrcConnectionSetupComplete_Set(RRCConnectionSetupComplete &value)
{
    c1_rrcConnectionSetupComplete_present = true;
    c1_rrcConnectionSetupComplete = value;
    return 0;
}

const RRCConnectionSetupComplete& UL_DCCH_MessageType::c1_rrcConnectionSetupComplete_Get() const
{
    return c1_rrcConnectionSetupComplete;
}

std::string UL_DCCH_MessageType::c1_rrcConnectionSetupComplete_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "rrcConnectionSetupComplete:\n";
    out += c1_rrcConnectionSetupComplete.ToString(indent+1);
    return out;
}

std::string UL_DCCH_MessageType::c1_rrcConnectionSetupComplete_ToStringNoNewLines() const
{
    std::string out = "rrcConnectionSetupComplete:";
    out += c1_rrcConnectionSetupComplete.ToStringNoNewLines();
    return out;
}

int UL_DCCH_MessageType::c1_rrcConnectionSetupComplete_Clear()
{
    c1_rrcConnectionSetupComplete_present = false;
    return 0;
}

bool UL_DCCH_MessageType::c1_rrcConnectionSetupComplete_IsPresent() const
{
    return c1_rrcConnectionSetupComplete_present;
}

SecurityModeComplete* UL_DCCH_MessageType::c1_securityModeComplete_Set()
{
    c1_securityModeComplete_present = true;
    return &c1_securityModeComplete;
}

int UL_DCCH_MessageType::c1_securityModeComplete_Set(SecurityModeComplete &value)
{
    c1_securityModeComplete_present = true;
    c1_securityModeComplete = value;
    return 0;
}

const SecurityModeComplete& UL_DCCH_MessageType::c1_securityModeComplete_Get() const
{
    return c1_securityModeComplete;
}

std::string UL_DCCH_MessageType::c1_securityModeComplete_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "securityModeComplete:\n";
    out += c1_securityModeComplete.ToString(indent+1);
    return out;
}

std::string UL_DCCH_MessageType::c1_securityModeComplete_ToStringNoNewLines() const
{
    std::string out = "securityModeComplete:";
    out += c1_securityModeComplete.ToStringNoNewLines();
    return out;
}

int UL_DCCH_MessageType::c1_securityModeComplete_Clear()
{
    c1_securityModeComplete_present = false;
    return 0;
}

bool UL_DCCH_MessageType::c1_securityModeComplete_IsPresent() const
{
    return c1_securityModeComplete_present;
}

SecurityModeFailure* UL_DCCH_MessageType::c1_securityModeFailure_Set()
{
    c1_securityModeFailure_present = true;
    return &c1_securityModeFailure;
}

int UL_DCCH_MessageType::c1_securityModeFailure_Set(SecurityModeFailure &value)
{
    c1_securityModeFailure_present = true;
    c1_securityModeFailure = value;
    return 0;
}

const SecurityModeFailure& UL_DCCH_MessageType::c1_securityModeFailure_Get() const
{
    return c1_securityModeFailure;
}

std::string UL_DCCH_MessageType::c1_securityModeFailure_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "securityModeFailure:\n";
    out += c1_securityModeFailure.ToString(indent+1);
    return out;
}

std::string UL_DCCH_MessageType::c1_securityModeFailure_ToStringNoNewLines() const
{
    std::string out = "securityModeFailure:";
    out += c1_securityModeFailure.ToStringNoNewLines();
    return out;
}

int UL_DCCH_MessageType::c1_securityModeFailure_Clear()
{
    c1_securityModeFailure_present = false;
    return 0;
}

bool UL_DCCH_MessageType::c1_securityModeFailure_IsPresent() const
{
    return c1_securityModeFailure_present;
}

UECapabilityInformation* UL_DCCH_MessageType::c1_ueCapabilityInformation_Set()
{
    c1_ueCapabilityInformation_present = true;
    return &c1_ueCapabilityInformation;
}

int UL_DCCH_MessageType::c1_ueCapabilityInformation_Set(UECapabilityInformation &value)
{
    c1_ueCapabilityInformation_present = true;
    c1_ueCapabilityInformation = value;
    return 0;
}

const UECapabilityInformation& UL_DCCH_MessageType::c1_ueCapabilityInformation_Get() const
{
    return c1_ueCapabilityInformation;
}

std::string UL_DCCH_MessageType::c1_ueCapabilityInformation_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ueCapabilityInformation:\n";
    out += c1_ueCapabilityInformation.ToString(indent+1);
    return out;
}

std::string UL_DCCH_MessageType::c1_ueCapabilityInformation_ToStringNoNewLines() const
{
    std::string out = "ueCapabilityInformation:";
    out += c1_ueCapabilityInformation.ToStringNoNewLines();
    return out;
}

int UL_DCCH_MessageType::c1_ueCapabilityInformation_Clear()
{
    c1_ueCapabilityInformation_present = false;
    return 0;
}

bool UL_DCCH_MessageType::c1_ueCapabilityInformation_IsPresent() const
{
    return c1_ueCapabilityInformation_present;
}

ULHandoverPreparationTransfer* UL_DCCH_MessageType::c1_ulHandoverPreparationTransfer_Set()
{
    c1_ulHandoverPreparationTransfer_present = true;
    return &c1_ulHandoverPreparationTransfer;
}

int UL_DCCH_MessageType::c1_ulHandoverPreparationTransfer_Set(ULHandoverPreparationTransfer &value)
{
    c1_ulHandoverPreparationTransfer_present = true;
    c1_ulHandoverPreparationTransfer = value;
    return 0;
}

const ULHandoverPreparationTransfer& UL_DCCH_MessageType::c1_ulHandoverPreparationTransfer_Get() const
{
    return c1_ulHandoverPreparationTransfer;
}

std::string UL_DCCH_MessageType::c1_ulHandoverPreparationTransfer_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ulHandoverPreparationTransfer:\n";
    out += c1_ulHandoverPreparationTransfer.ToString(indent+1);
    return out;
}

std::string UL_DCCH_MessageType::c1_ulHandoverPreparationTransfer_ToStringNoNewLines() const
{
    std::string out = "ulHandoverPreparationTransfer:";
    out += c1_ulHandoverPreparationTransfer.ToStringNoNewLines();
    return out;
}

int UL_DCCH_MessageType::c1_ulHandoverPreparationTransfer_Clear()
{
    c1_ulHandoverPreparationTransfer_present = false;
    return 0;
}

bool UL_DCCH_MessageType::c1_ulHandoverPreparationTransfer_IsPresent() const
{
    return c1_ulHandoverPreparationTransfer_present;
}

ULInformationTransfer* UL_DCCH_MessageType::c1_ulInformationTransfer_Set()
{
    c1_ulInformationTransfer_present = true;
    return &c1_ulInformationTransfer;
}

int UL_DCCH_MessageType::c1_ulInformationTransfer_Set(ULInformationTransfer &value)
{
    c1_ulInformationTransfer_present = true;
    c1_ulInformationTransfer = value;
    return 0;
}

const ULInformationTransfer& UL_DCCH_MessageType::c1_ulInformationTransfer_Get() const
{
    return c1_ulInformationTransfer;
}

std::string UL_DCCH_MessageType::c1_ulInformationTransfer_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ulInformationTransfer:\n";
    out += c1_ulInformationTransfer.ToString(indent+1);
    return out;
}

std::string UL_DCCH_MessageType::c1_ulInformationTransfer_ToStringNoNewLines() const
{
    std::string out = "ulInformationTransfer:";
    out += c1_ulInformationTransfer.ToStringNoNewLines();
    return out;
}

int UL_DCCH_MessageType::c1_ulInformationTransfer_Clear()
{
    c1_ulInformationTransfer_present = false;
    return 0;
}

bool UL_DCCH_MessageType::c1_ulInformationTransfer_IsPresent() const
{
    return c1_ulInformationTransfer_present;
}

CounterCheckResponse* UL_DCCH_MessageType::c1_counterCheckResponse_Set()
{
    c1_counterCheckResponse_present = true;
    return &c1_counterCheckResponse;
}

int UL_DCCH_MessageType::c1_counterCheckResponse_Set(CounterCheckResponse &value)
{
    c1_counterCheckResponse_present = true;
    c1_counterCheckResponse = value;
    return 0;
}

const CounterCheckResponse& UL_DCCH_MessageType::c1_counterCheckResponse_Get() const
{
    return c1_counterCheckResponse;
}

std::string UL_DCCH_MessageType::c1_counterCheckResponse_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "counterCheckResponse:\n";
    out += c1_counterCheckResponse.ToString(indent+1);
    return out;
}

std::string UL_DCCH_MessageType::c1_counterCheckResponse_ToStringNoNewLines() const
{
    std::string out = "counterCheckResponse:";
    out += c1_counterCheckResponse.ToStringNoNewLines();
    return out;
}

int UL_DCCH_MessageType::c1_counterCheckResponse_Clear()
{
    c1_counterCheckResponse_present = false;
    return 0;
}

bool UL_DCCH_MessageType::c1_counterCheckResponse_IsPresent() const
{
    return c1_counterCheckResponse_present;
}

UEInformationResponse_r9* UL_DCCH_MessageType::c1_ueInformationResponse_r9_Set()
{
    c1_ueInformationResponse_r9_present = true;
    return &c1_ueInformationResponse_r9;
}

int UL_DCCH_MessageType::c1_ueInformationResponse_r9_Set(UEInformationResponse_r9 &value)
{
    c1_ueInformationResponse_r9_present = true;
    c1_ueInformationResponse_r9 = value;
    return 0;
}

const UEInformationResponse_r9& UL_DCCH_MessageType::c1_ueInformationResponse_r9_Get() const
{
    return c1_ueInformationResponse_r9;
}

std::string UL_DCCH_MessageType::c1_ueInformationResponse_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ueInformationResponse_r9:\n";
    out += c1_ueInformationResponse_r9.ToString(indent+1);
    return out;
}

std::string UL_DCCH_MessageType::c1_ueInformationResponse_r9_ToStringNoNewLines() const
{
    std::string out = "ueInformationResponse_r9:";
    out += c1_ueInformationResponse_r9.ToStringNoNewLines();
    return out;
}

int UL_DCCH_MessageType::c1_ueInformationResponse_r9_Clear()
{
    c1_ueInformationResponse_r9_present = false;
    return 0;
}

bool UL_DCCH_MessageType::c1_ueInformationResponse_r9_IsPresent() const
{
    return c1_ueInformationResponse_r9_present;
}

ProximityIndication_r9* UL_DCCH_MessageType::c1_proximityIndication_r9_Set()
{
    c1_proximityIndication_r9_present = true;
    return &c1_proximityIndication_r9;
}

int UL_DCCH_MessageType::c1_proximityIndication_r9_Set(ProximityIndication_r9 &value)
{
    c1_proximityIndication_r9_present = true;
    c1_proximityIndication_r9 = value;
    return 0;
}

const ProximityIndication_r9& UL_DCCH_MessageType::c1_proximityIndication_r9_Get() const
{
    return c1_proximityIndication_r9;
}

std::string UL_DCCH_MessageType::c1_proximityIndication_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "proximityIndication_r9:\n";
    out += c1_proximityIndication_r9.ToString(indent+1);
    return out;
}

std::string UL_DCCH_MessageType::c1_proximityIndication_r9_ToStringNoNewLines() const
{
    std::string out = "proximityIndication_r9:";
    out += c1_proximityIndication_r9.ToStringNoNewLines();
    return out;
}

int UL_DCCH_MessageType::c1_proximityIndication_r9_Clear()
{
    c1_proximityIndication_r9_present = false;
    return 0;
}

bool UL_DCCH_MessageType::c1_proximityIndication_r9_IsPresent() const
{
    return c1_proximityIndication_r9_present;
}

RNReconfigurationComplete_r10* UL_DCCH_MessageType::c1_rnReconfigurationComplete_r10_Set()
{
    c1_rnReconfigurationComplete_r10_present = true;
    return &c1_rnReconfigurationComplete_r10;
}

int UL_DCCH_MessageType::c1_rnReconfigurationComplete_r10_Set(RNReconfigurationComplete_r10 &value)
{
    c1_rnReconfigurationComplete_r10_present = true;
    c1_rnReconfigurationComplete_r10 = value;
    return 0;
}

const RNReconfigurationComplete_r10& UL_DCCH_MessageType::c1_rnReconfigurationComplete_r10_Get() const
{
    return c1_rnReconfigurationComplete_r10;
}

std::string UL_DCCH_MessageType::c1_rnReconfigurationComplete_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "rnReconfigurationComplete_r10:\n";
    out += c1_rnReconfigurationComplete_r10.ToString(indent+1);
    return out;
}

std::string UL_DCCH_MessageType::c1_rnReconfigurationComplete_r10_ToStringNoNewLines() const
{
    std::string out = "rnReconfigurationComplete_r10:";
    out += c1_rnReconfigurationComplete_r10.ToStringNoNewLines();
    return out;
}

int UL_DCCH_MessageType::c1_rnReconfigurationComplete_r10_Clear()
{
    c1_rnReconfigurationComplete_r10_present = false;
    return 0;
}

bool UL_DCCH_MessageType::c1_rnReconfigurationComplete_r10_IsPresent() const
{
    return c1_rnReconfigurationComplete_r10_present;
}

