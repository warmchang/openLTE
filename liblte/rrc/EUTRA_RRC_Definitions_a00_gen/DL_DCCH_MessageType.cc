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

#include "DL_DCCH_MessageType.h"

#include <cmath>

int DL_DCCH_MessageType::Pack(std::vector<uint8_t> &bits)
{
    if(!present)
    {
        printf("DL_DCCH_MessageType::Pack() presence failure\n");
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
            printf("DL_DCCH_MessageType::c1 pack failure\n");
            return -1;
        }
    }
    return 0;
}

int DL_DCCH_MessageType::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int DL_DCCH_MessageType::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 1) > bits.size())
    {
        printf("DL_DCCH_MessageType::Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<1; i++)
        packed_val |= bits[idx++] << (1-i-1);

    if((DL_DCCH_MessageType::Enum)packed_val > k_messageClassExtension)
    {
        printf("DL_DCCH_MessageType::Unpack() choice range failure\n");
        return -1;
    }
    internal_choice = (DL_DCCH_MessageType::Enum)packed_val;
    present = true;

    // Fields
    if(internal_choice == k_c1)
    {
        if(0 != c1_Unpack(bits, idx))
        {
            printf("DL_DCCH_MessageType::c1 unpack failure\n");
            return -1;
        }
    }
    return 0;
}

DL_DCCH_MessageType::Enum DL_DCCH_MessageType::Choice() const
{
    if(present)
        return internal_choice;
    return (DL_DCCH_MessageType::Enum)0;
}

int DL_DCCH_MessageType::SetChoice(DL_DCCH_MessageType::Enum choice)
{
    internal_choice = choice;
    present = true;
    return 0;
}

std::string DL_DCCH_MessageType::ChoiceToString(Enum value) const
{
    if(k_c1 == value)
        return "c1";
    if(k_messageClassExtension == value)
        return "messageClassExtension";
    return "";
}

uint64_t DL_DCCH_MessageType::NumberOfChoices() const
{
    return 2;
}

std::string DL_DCCH_MessageType::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "DL_DCCH_MessageType = " + ChoiceToString(internal_choice) + ":\n";
    if(internal_choice == k_c1)
        out += c1_ToString(indent+1);
    return out;
}

std::string DL_DCCH_MessageType::ToStringNoNewLines() const
{
    std::string out = "DL_DCCH_MessageType=" + ChoiceToString(internal_choice) + ",";
    if(internal_choice == k_c1)
        out += c1_ToStringNoNewLines();
    return out;
}

int DL_DCCH_MessageType::Clear()
{
    present = false;
    return 0;
}

bool DL_DCCH_MessageType::IsPresent() const
{
    return present;
}

int DL_DCCH_MessageType::c1_Pack(std::vector<uint8_t> &bits)
{
    if(!c1_present)
    {
        printf("DL_DCCH_MessageType::c1_Pack() presence failure\n");
        return -1;
    }
    // Extension indicator

    // Choice
    for(uint32_t i=0; i<4; i++)
        bits.push_back((c1_internal_choice >> (4-i-1)) & 1);

    // Fields
    if(c1_internal_choice == k_c1_csfbParametersResponseCDMA2000)
    {
        if(0 != c1_csfbParametersResponseCDMA2000.Pack(bits))
        {
            printf("DL_DCCH_MessageType::c1_csfbParametersResponseCDMA2000 pack failure\n");
            return -1;
        }
    }
    if(c1_internal_choice == k_c1_dlInformationTransfer)
    {
        if(0 != c1_dlInformationTransfer.Pack(bits))
        {
            printf("DL_DCCH_MessageType::c1_dlInformationTransfer pack failure\n");
            return -1;
        }
    }
    if(c1_internal_choice == k_c1_handoverFromEUTRAPreparationRequest)
    {
        if(0 != c1_handoverFromEUTRAPreparationRequest.Pack(bits))
        {
            printf("DL_DCCH_MessageType::c1_handoverFromEUTRAPreparationRequest pack failure\n");
            return -1;
        }
    }
    if(c1_internal_choice == k_c1_mobilityFromEUTRACommand)
    {
        if(0 != c1_mobilityFromEUTRACommand.Pack(bits))
        {
            printf("DL_DCCH_MessageType::c1_mobilityFromEUTRACommand pack failure\n");
            return -1;
        }
    }
    if(c1_internal_choice == k_c1_rrcConnectionReconfiguration)
    {
        if(0 != c1_rrcConnectionReconfiguration.Pack(bits))
        {
            printf("DL_DCCH_MessageType::c1_rrcConnectionReconfiguration pack failure\n");
            return -1;
        }
    }
    if(c1_internal_choice == k_c1_rrcConnectionRelease)
    {
        if(0 != c1_rrcConnectionRelease.Pack(bits))
        {
            printf("DL_DCCH_MessageType::c1_rrcConnectionRelease pack failure\n");
            return -1;
        }
    }
    if(c1_internal_choice == k_c1_securityModeCommand)
    {
        if(0 != c1_securityModeCommand.Pack(bits))
        {
            printf("DL_DCCH_MessageType::c1_securityModeCommand pack failure\n");
            return -1;
        }
    }
    if(c1_internal_choice == k_c1_ueCapabilityEnquiry)
    {
        if(0 != c1_ueCapabilityEnquiry.Pack(bits))
        {
            printf("DL_DCCH_MessageType::c1_ueCapabilityEnquiry pack failure\n");
            return -1;
        }
    }
    if(c1_internal_choice == k_c1_counterCheck)
    {
        if(0 != c1_counterCheck.Pack(bits))
        {
            printf("DL_DCCH_MessageType::c1_counterCheck pack failure\n");
            return -1;
        }
    }
    if(c1_internal_choice == k_c1_ueInformationRequest_r9)
    {
        if(0 != c1_ueInformationRequest_r9.Pack(bits))
        {
            printf("DL_DCCH_MessageType::c1_ueInformationRequest_r9 pack failure\n");
            return -1;
        }
    }
    if(c1_internal_choice == k_c1_loggedMeasurementsConfiguration_r10)
    {
        if(0 != c1_loggedMeasurementsConfiguration_r10.Pack(bits))
        {
            printf("DL_DCCH_MessageType::c1_loggedMeasurementsConfiguration_r10 pack failure\n");
            return -1;
        }
    }
    if(c1_internal_choice == k_c1_rnReconfiguration_r10)
    {
        if(0 != c1_rnReconfiguration_r10.Pack(bits))
        {
            printf("DL_DCCH_MessageType::c1_rnReconfiguration_r10 pack failure\n");
            return -1;
        }
    }
    if(c1_internal_choice == k_c1_spare4)
    {
        if(0 != c1_spare4_Pack(bits))
        {
            printf("DL_DCCH_MessageType::c1_spare4 pack failure\n");
            return -1;
        }
    }
    if(c1_internal_choice == k_c1_spare3)
    {
        if(0 != c1_spare3_Pack(bits))
        {
            printf("DL_DCCH_MessageType::c1_spare3 pack failure\n");
            return -1;
        }
    }
    if(c1_internal_choice == k_c1_spare2)
    {
        if(0 != c1_spare2_Pack(bits))
        {
            printf("DL_DCCH_MessageType::c1_spare2 pack failure\n");
            return -1;
        }
    }
    if(c1_internal_choice == k_c1_spare1)
    {
        if(0 != c1_spare1_Pack(bits))
        {
            printf("DL_DCCH_MessageType::c1_spare1 pack failure\n");
            return -1;
        }
    }
    return 0;
}

int DL_DCCH_MessageType::c1_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return c1_Unpack(bits, idx);
}

int DL_DCCH_MessageType::c1_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 4) > bits.size())
    {
        printf("DL_DCCH_MessageType::c1_Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<4; i++)
        packed_val |= bits[idx++] << (4-i-1);

    if((DL_DCCH_MessageType::c1_Enum)packed_val > k_c1_spare1)
    {
        printf("DL_DCCH_MessageType::c1_Unpack() choice range failure\n");
        return -1;
    }
    c1_internal_choice = (DL_DCCH_MessageType::c1_Enum)packed_val;
    c1_present = true;

    // Fields
    if(c1_internal_choice == k_c1_csfbParametersResponseCDMA2000)
    {
        if(0 != c1_csfbParametersResponseCDMA2000.Unpack(bits, idx))
        {
            printf("DL_DCCH_MessageType::c1_csfbParametersResponseCDMA2000 unpack failure\n");
            return -1;
        }
    }
    if(c1_internal_choice == k_c1_dlInformationTransfer)
    {
        if(0 != c1_dlInformationTransfer.Unpack(bits, idx))
        {
            printf("DL_DCCH_MessageType::c1_dlInformationTransfer unpack failure\n");
            return -1;
        }
    }
    if(c1_internal_choice == k_c1_handoverFromEUTRAPreparationRequest)
    {
        if(0 != c1_handoverFromEUTRAPreparationRequest.Unpack(bits, idx))
        {
            printf("DL_DCCH_MessageType::c1_handoverFromEUTRAPreparationRequest unpack failure\n");
            return -1;
        }
    }
    if(c1_internal_choice == k_c1_mobilityFromEUTRACommand)
    {
        if(0 != c1_mobilityFromEUTRACommand.Unpack(bits, idx))
        {
            printf("DL_DCCH_MessageType::c1_mobilityFromEUTRACommand unpack failure\n");
            return -1;
        }
    }
    if(c1_internal_choice == k_c1_rrcConnectionReconfiguration)
    {
        if(0 != c1_rrcConnectionReconfiguration.Unpack(bits, idx))
        {
            printf("DL_DCCH_MessageType::c1_rrcConnectionReconfiguration unpack failure\n");
            return -1;
        }
    }
    if(c1_internal_choice == k_c1_rrcConnectionRelease)
    {
        if(0 != c1_rrcConnectionRelease.Unpack(bits, idx))
        {
            printf("DL_DCCH_MessageType::c1_rrcConnectionRelease unpack failure\n");
            return -1;
        }
    }
    if(c1_internal_choice == k_c1_securityModeCommand)
    {
        if(0 != c1_securityModeCommand.Unpack(bits, idx))
        {
            printf("DL_DCCH_MessageType::c1_securityModeCommand unpack failure\n");
            return -1;
        }
    }
    if(c1_internal_choice == k_c1_ueCapabilityEnquiry)
    {
        if(0 != c1_ueCapabilityEnquiry.Unpack(bits, idx))
        {
            printf("DL_DCCH_MessageType::c1_ueCapabilityEnquiry unpack failure\n");
            return -1;
        }
    }
    if(c1_internal_choice == k_c1_counterCheck)
    {
        if(0 != c1_counterCheck.Unpack(bits, idx))
        {
            printf("DL_DCCH_MessageType::c1_counterCheck unpack failure\n");
            return -1;
        }
    }
    if(c1_internal_choice == k_c1_ueInformationRequest_r9)
    {
        if(0 != c1_ueInformationRequest_r9.Unpack(bits, idx))
        {
            printf("DL_DCCH_MessageType::c1_ueInformationRequest_r9 unpack failure\n");
            return -1;
        }
    }
    if(c1_internal_choice == k_c1_loggedMeasurementsConfiguration_r10)
    {
        if(0 != c1_loggedMeasurementsConfiguration_r10.Unpack(bits, idx))
        {
            printf("DL_DCCH_MessageType::c1_loggedMeasurementsConfiguration_r10 unpack failure\n");
            return -1;
        }
    }
    if(c1_internal_choice == k_c1_rnReconfiguration_r10)
    {
        if(0 != c1_rnReconfiguration_r10.Unpack(bits, idx))
        {
            printf("DL_DCCH_MessageType::c1_rnReconfiguration_r10 unpack failure\n");
            return -1;
        }
    }
    if(c1_internal_choice == k_c1_spare4)
    {
        if(0 != c1_spare4_Unpack(bits, idx))
        {
            printf("DL_DCCH_MessageType::c1_spare4 unpack failure\n");
            return -1;
        }
    }
    if(c1_internal_choice == k_c1_spare3)
    {
        if(0 != c1_spare3_Unpack(bits, idx))
        {
            printf("DL_DCCH_MessageType::c1_spare3 unpack failure\n");
            return -1;
        }
    }
    if(c1_internal_choice == k_c1_spare2)
    {
        if(0 != c1_spare2_Unpack(bits, idx))
        {
            printf("DL_DCCH_MessageType::c1_spare2 unpack failure\n");
            return -1;
        }
    }
    if(c1_internal_choice == k_c1_spare1)
    {
        if(0 != c1_spare1_Unpack(bits, idx))
        {
            printf("DL_DCCH_MessageType::c1_spare1 unpack failure\n");
            return -1;
        }
    }
    return 0;
}

DL_DCCH_MessageType::c1_Enum DL_DCCH_MessageType::c1_Choice() const
{
    if(c1_present)
        return c1_internal_choice;
    return (DL_DCCH_MessageType::c1_Enum)0;
}

int DL_DCCH_MessageType::c1_SetChoice(DL_DCCH_MessageType::c1_Enum choice)
{
    c1_internal_choice = choice;
    c1_present = true;
    return 0;
}

std::string DL_DCCH_MessageType::c1_ChoiceToString(c1_Enum value) const
{
    if(k_c1_csfbParametersResponseCDMA2000 == value)
        return "c1_csfbParametersResponseCDMA2000";
    if(k_c1_dlInformationTransfer == value)
        return "c1_dlInformationTransfer";
    if(k_c1_handoverFromEUTRAPreparationRequest == value)
        return "c1_handoverFromEUTRAPreparationRequest";
    if(k_c1_mobilityFromEUTRACommand == value)
        return "c1_mobilityFromEUTRACommand";
    if(k_c1_rrcConnectionReconfiguration == value)
        return "c1_rrcConnectionReconfiguration";
    if(k_c1_rrcConnectionRelease == value)
        return "c1_rrcConnectionRelease";
    if(k_c1_securityModeCommand == value)
        return "c1_securityModeCommand";
    if(k_c1_ueCapabilityEnquiry == value)
        return "c1_ueCapabilityEnquiry";
    if(k_c1_counterCheck == value)
        return "c1_counterCheck";
    if(k_c1_ueInformationRequest_r9 == value)
        return "c1_ueInformationRequest_r9";
    if(k_c1_loggedMeasurementsConfiguration_r10 == value)
        return "c1_loggedMeasurementsConfiguration_r10";
    if(k_c1_rnReconfiguration_r10 == value)
        return "c1_rnReconfiguration_r10";
    if(k_c1_spare4 == value)
        return "c1_spare4";
    if(k_c1_spare3 == value)
        return "c1_spare3";
    if(k_c1_spare2 == value)
        return "c1_spare2";
    if(k_c1_spare1 == value)
        return "c1_spare1";
    return "";
}

uint64_t DL_DCCH_MessageType::c1_NumberOfChoices() const
{
    return 16;
}

std::string DL_DCCH_MessageType::c1_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "c1 = " + c1_ChoiceToString(c1_internal_choice) + ":\n";
    if(c1_internal_choice == k_c1_csfbParametersResponseCDMA2000)
        out += c1_csfbParametersResponseCDMA2000.ToString(indent+1);
    if(c1_internal_choice == k_c1_dlInformationTransfer)
        out += c1_dlInformationTransfer.ToString(indent+1);
    if(c1_internal_choice == k_c1_handoverFromEUTRAPreparationRequest)
        out += c1_handoverFromEUTRAPreparationRequest.ToString(indent+1);
    if(c1_internal_choice == k_c1_mobilityFromEUTRACommand)
        out += c1_mobilityFromEUTRACommand.ToString(indent+1);
    if(c1_internal_choice == k_c1_rrcConnectionReconfiguration)
        out += c1_rrcConnectionReconfiguration.ToString(indent+1);
    if(c1_internal_choice == k_c1_rrcConnectionRelease)
        out += c1_rrcConnectionRelease.ToString(indent+1);
    if(c1_internal_choice == k_c1_securityModeCommand)
        out += c1_securityModeCommand.ToString(indent+1);
    if(c1_internal_choice == k_c1_ueCapabilityEnquiry)
        out += c1_ueCapabilityEnquiry.ToString(indent+1);
    if(c1_internal_choice == k_c1_counterCheck)
        out += c1_counterCheck.ToString(indent+1);
    if(c1_internal_choice == k_c1_ueInformationRequest_r9)
        out += c1_ueInformationRequest_r9.ToString(indent+1);
    if(c1_internal_choice == k_c1_loggedMeasurementsConfiguration_r10)
        out += c1_loggedMeasurementsConfiguration_r10.ToString(indent+1);
    if(c1_internal_choice == k_c1_rnReconfiguration_r10)
        out += c1_rnReconfiguration_r10.ToString(indent+1);
    return out;
}

std::string DL_DCCH_MessageType::c1_ToStringNoNewLines() const
{
    std::string out = "c1=" + c1_ChoiceToString(c1_internal_choice) + ",";
    if(c1_internal_choice == k_c1_csfbParametersResponseCDMA2000)
        out += c1_csfbParametersResponseCDMA2000.ToStringNoNewLines();
    if(c1_internal_choice == k_c1_dlInformationTransfer)
        out += c1_dlInformationTransfer.ToStringNoNewLines();
    if(c1_internal_choice == k_c1_handoverFromEUTRAPreparationRequest)
        out += c1_handoverFromEUTRAPreparationRequest.ToStringNoNewLines();
    if(c1_internal_choice == k_c1_mobilityFromEUTRACommand)
        out += c1_mobilityFromEUTRACommand.ToStringNoNewLines();
    if(c1_internal_choice == k_c1_rrcConnectionReconfiguration)
        out += c1_rrcConnectionReconfiguration.ToStringNoNewLines();
    if(c1_internal_choice == k_c1_rrcConnectionRelease)
        out += c1_rrcConnectionRelease.ToStringNoNewLines();
    if(c1_internal_choice == k_c1_securityModeCommand)
        out += c1_securityModeCommand.ToStringNoNewLines();
    if(c1_internal_choice == k_c1_ueCapabilityEnquiry)
        out += c1_ueCapabilityEnquiry.ToStringNoNewLines();
    if(c1_internal_choice == k_c1_counterCheck)
        out += c1_counterCheck.ToStringNoNewLines();
    if(c1_internal_choice == k_c1_ueInformationRequest_r9)
        out += c1_ueInformationRequest_r9.ToStringNoNewLines();
    if(c1_internal_choice == k_c1_loggedMeasurementsConfiguration_r10)
        out += c1_loggedMeasurementsConfiguration_r10.ToStringNoNewLines();
    if(c1_internal_choice == k_c1_rnReconfiguration_r10)
        out += c1_rnReconfiguration_r10.ToStringNoNewLines();
    return out;
}

int DL_DCCH_MessageType::c1_Clear()
{
    c1_present = false;
    return 0;
}

bool DL_DCCH_MessageType::c1_IsPresent() const
{
    return c1_present;
}

CSFBParametersResponseCDMA2000* DL_DCCH_MessageType::c1_csfbParametersResponseCDMA2000_Set()
{
    c1_csfbParametersResponseCDMA2000_present = true;
    return &c1_csfbParametersResponseCDMA2000;
}

int DL_DCCH_MessageType::c1_csfbParametersResponseCDMA2000_Set(CSFBParametersResponseCDMA2000 &value)
{
    c1_csfbParametersResponseCDMA2000_present = true;
    c1_csfbParametersResponseCDMA2000 = value;
    return 0;
}

const CSFBParametersResponseCDMA2000& DL_DCCH_MessageType::c1_csfbParametersResponseCDMA2000_Get() const
{
    return c1_csfbParametersResponseCDMA2000;
}

std::string DL_DCCH_MessageType::c1_csfbParametersResponseCDMA2000_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "csfbParametersResponseCDMA2000:\n";
    out += c1_csfbParametersResponseCDMA2000.ToString(indent+1);
    return out;
}

std::string DL_DCCH_MessageType::c1_csfbParametersResponseCDMA2000_ToStringNoNewLines() const
{
    std::string out = "csfbParametersResponseCDMA2000:";
    out += c1_csfbParametersResponseCDMA2000.ToStringNoNewLines();
    return out;
}

int DL_DCCH_MessageType::c1_csfbParametersResponseCDMA2000_Clear()
{
    c1_csfbParametersResponseCDMA2000_present = false;
    return 0;
}

bool DL_DCCH_MessageType::c1_csfbParametersResponseCDMA2000_IsPresent() const
{
    return c1_csfbParametersResponseCDMA2000_present;
}

DLInformationTransfer* DL_DCCH_MessageType::c1_dlInformationTransfer_Set()
{
    c1_dlInformationTransfer_present = true;
    return &c1_dlInformationTransfer;
}

int DL_DCCH_MessageType::c1_dlInformationTransfer_Set(DLInformationTransfer &value)
{
    c1_dlInformationTransfer_present = true;
    c1_dlInformationTransfer = value;
    return 0;
}

const DLInformationTransfer& DL_DCCH_MessageType::c1_dlInformationTransfer_Get() const
{
    return c1_dlInformationTransfer;
}

std::string DL_DCCH_MessageType::c1_dlInformationTransfer_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "dlInformationTransfer:\n";
    out += c1_dlInformationTransfer.ToString(indent+1);
    return out;
}

std::string DL_DCCH_MessageType::c1_dlInformationTransfer_ToStringNoNewLines() const
{
    std::string out = "dlInformationTransfer:";
    out += c1_dlInformationTransfer.ToStringNoNewLines();
    return out;
}

int DL_DCCH_MessageType::c1_dlInformationTransfer_Clear()
{
    c1_dlInformationTransfer_present = false;
    return 0;
}

bool DL_DCCH_MessageType::c1_dlInformationTransfer_IsPresent() const
{
    return c1_dlInformationTransfer_present;
}

HandoverFromEUTRAPreparationRequest* DL_DCCH_MessageType::c1_handoverFromEUTRAPreparationRequest_Set()
{
    c1_handoverFromEUTRAPreparationRequest_present = true;
    return &c1_handoverFromEUTRAPreparationRequest;
}

int DL_DCCH_MessageType::c1_handoverFromEUTRAPreparationRequest_Set(HandoverFromEUTRAPreparationRequest &value)
{
    c1_handoverFromEUTRAPreparationRequest_present = true;
    c1_handoverFromEUTRAPreparationRequest = value;
    return 0;
}

const HandoverFromEUTRAPreparationRequest& DL_DCCH_MessageType::c1_handoverFromEUTRAPreparationRequest_Get() const
{
    return c1_handoverFromEUTRAPreparationRequest;
}

std::string DL_DCCH_MessageType::c1_handoverFromEUTRAPreparationRequest_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "handoverFromEUTRAPreparationRequest:\n";
    out += c1_handoverFromEUTRAPreparationRequest.ToString(indent+1);
    return out;
}

std::string DL_DCCH_MessageType::c1_handoverFromEUTRAPreparationRequest_ToStringNoNewLines() const
{
    std::string out = "handoverFromEUTRAPreparationRequest:";
    out += c1_handoverFromEUTRAPreparationRequest.ToStringNoNewLines();
    return out;
}

int DL_DCCH_MessageType::c1_handoverFromEUTRAPreparationRequest_Clear()
{
    c1_handoverFromEUTRAPreparationRequest_present = false;
    return 0;
}

bool DL_DCCH_MessageType::c1_handoverFromEUTRAPreparationRequest_IsPresent() const
{
    return c1_handoverFromEUTRAPreparationRequest_present;
}

MobilityFromEUTRACommand* DL_DCCH_MessageType::c1_mobilityFromEUTRACommand_Set()
{
    c1_mobilityFromEUTRACommand_present = true;
    return &c1_mobilityFromEUTRACommand;
}

int DL_DCCH_MessageType::c1_mobilityFromEUTRACommand_Set(MobilityFromEUTRACommand &value)
{
    c1_mobilityFromEUTRACommand_present = true;
    c1_mobilityFromEUTRACommand = value;
    return 0;
}

const MobilityFromEUTRACommand& DL_DCCH_MessageType::c1_mobilityFromEUTRACommand_Get() const
{
    return c1_mobilityFromEUTRACommand;
}

std::string DL_DCCH_MessageType::c1_mobilityFromEUTRACommand_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "mobilityFromEUTRACommand:\n";
    out += c1_mobilityFromEUTRACommand.ToString(indent+1);
    return out;
}

std::string DL_DCCH_MessageType::c1_mobilityFromEUTRACommand_ToStringNoNewLines() const
{
    std::string out = "mobilityFromEUTRACommand:";
    out += c1_mobilityFromEUTRACommand.ToStringNoNewLines();
    return out;
}

int DL_DCCH_MessageType::c1_mobilityFromEUTRACommand_Clear()
{
    c1_mobilityFromEUTRACommand_present = false;
    return 0;
}

bool DL_DCCH_MessageType::c1_mobilityFromEUTRACommand_IsPresent() const
{
    return c1_mobilityFromEUTRACommand_present;
}

RRCConnectionReconfiguration* DL_DCCH_MessageType::c1_rrcConnectionReconfiguration_Set()
{
    c1_rrcConnectionReconfiguration_present = true;
    return &c1_rrcConnectionReconfiguration;
}

int DL_DCCH_MessageType::c1_rrcConnectionReconfiguration_Set(RRCConnectionReconfiguration &value)
{
    c1_rrcConnectionReconfiguration_present = true;
    c1_rrcConnectionReconfiguration = value;
    return 0;
}

const RRCConnectionReconfiguration& DL_DCCH_MessageType::c1_rrcConnectionReconfiguration_Get() const
{
    return c1_rrcConnectionReconfiguration;
}

std::string DL_DCCH_MessageType::c1_rrcConnectionReconfiguration_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "rrcConnectionReconfiguration:\n";
    out += c1_rrcConnectionReconfiguration.ToString(indent+1);
    return out;
}

std::string DL_DCCH_MessageType::c1_rrcConnectionReconfiguration_ToStringNoNewLines() const
{
    std::string out = "rrcConnectionReconfiguration:";
    out += c1_rrcConnectionReconfiguration.ToStringNoNewLines();
    return out;
}

int DL_DCCH_MessageType::c1_rrcConnectionReconfiguration_Clear()
{
    c1_rrcConnectionReconfiguration_present = false;
    return 0;
}

bool DL_DCCH_MessageType::c1_rrcConnectionReconfiguration_IsPresent() const
{
    return c1_rrcConnectionReconfiguration_present;
}

RRCConnectionRelease* DL_DCCH_MessageType::c1_rrcConnectionRelease_Set()
{
    c1_rrcConnectionRelease_present = true;
    return &c1_rrcConnectionRelease;
}

int DL_DCCH_MessageType::c1_rrcConnectionRelease_Set(RRCConnectionRelease &value)
{
    c1_rrcConnectionRelease_present = true;
    c1_rrcConnectionRelease = value;
    return 0;
}

const RRCConnectionRelease& DL_DCCH_MessageType::c1_rrcConnectionRelease_Get() const
{
    return c1_rrcConnectionRelease;
}

std::string DL_DCCH_MessageType::c1_rrcConnectionRelease_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "rrcConnectionRelease:\n";
    out += c1_rrcConnectionRelease.ToString(indent+1);
    return out;
}

std::string DL_DCCH_MessageType::c1_rrcConnectionRelease_ToStringNoNewLines() const
{
    std::string out = "rrcConnectionRelease:";
    out += c1_rrcConnectionRelease.ToStringNoNewLines();
    return out;
}

int DL_DCCH_MessageType::c1_rrcConnectionRelease_Clear()
{
    c1_rrcConnectionRelease_present = false;
    return 0;
}

bool DL_DCCH_MessageType::c1_rrcConnectionRelease_IsPresent() const
{
    return c1_rrcConnectionRelease_present;
}

SecurityModeCommand* DL_DCCH_MessageType::c1_securityModeCommand_Set()
{
    c1_securityModeCommand_present = true;
    return &c1_securityModeCommand;
}

int DL_DCCH_MessageType::c1_securityModeCommand_Set(SecurityModeCommand &value)
{
    c1_securityModeCommand_present = true;
    c1_securityModeCommand = value;
    return 0;
}

const SecurityModeCommand& DL_DCCH_MessageType::c1_securityModeCommand_Get() const
{
    return c1_securityModeCommand;
}

std::string DL_DCCH_MessageType::c1_securityModeCommand_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "securityModeCommand:\n";
    out += c1_securityModeCommand.ToString(indent+1);
    return out;
}

std::string DL_DCCH_MessageType::c1_securityModeCommand_ToStringNoNewLines() const
{
    std::string out = "securityModeCommand:";
    out += c1_securityModeCommand.ToStringNoNewLines();
    return out;
}

int DL_DCCH_MessageType::c1_securityModeCommand_Clear()
{
    c1_securityModeCommand_present = false;
    return 0;
}

bool DL_DCCH_MessageType::c1_securityModeCommand_IsPresent() const
{
    return c1_securityModeCommand_present;
}

UECapabilityEnquiry* DL_DCCH_MessageType::c1_ueCapabilityEnquiry_Set()
{
    c1_ueCapabilityEnquiry_present = true;
    return &c1_ueCapabilityEnquiry;
}

int DL_DCCH_MessageType::c1_ueCapabilityEnquiry_Set(UECapabilityEnquiry &value)
{
    c1_ueCapabilityEnquiry_present = true;
    c1_ueCapabilityEnquiry = value;
    return 0;
}

const UECapabilityEnquiry& DL_DCCH_MessageType::c1_ueCapabilityEnquiry_Get() const
{
    return c1_ueCapabilityEnquiry;
}

std::string DL_DCCH_MessageType::c1_ueCapabilityEnquiry_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ueCapabilityEnquiry:\n";
    out += c1_ueCapabilityEnquiry.ToString(indent+1);
    return out;
}

std::string DL_DCCH_MessageType::c1_ueCapabilityEnquiry_ToStringNoNewLines() const
{
    std::string out = "ueCapabilityEnquiry:";
    out += c1_ueCapabilityEnquiry.ToStringNoNewLines();
    return out;
}

int DL_DCCH_MessageType::c1_ueCapabilityEnquiry_Clear()
{
    c1_ueCapabilityEnquiry_present = false;
    return 0;
}

bool DL_DCCH_MessageType::c1_ueCapabilityEnquiry_IsPresent() const
{
    return c1_ueCapabilityEnquiry_present;
}

CounterCheck* DL_DCCH_MessageType::c1_counterCheck_Set()
{
    c1_counterCheck_present = true;
    return &c1_counterCheck;
}

int DL_DCCH_MessageType::c1_counterCheck_Set(CounterCheck &value)
{
    c1_counterCheck_present = true;
    c1_counterCheck = value;
    return 0;
}

const CounterCheck& DL_DCCH_MessageType::c1_counterCheck_Get() const
{
    return c1_counterCheck;
}

std::string DL_DCCH_MessageType::c1_counterCheck_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "counterCheck:\n";
    out += c1_counterCheck.ToString(indent+1);
    return out;
}

std::string DL_DCCH_MessageType::c1_counterCheck_ToStringNoNewLines() const
{
    std::string out = "counterCheck:";
    out += c1_counterCheck.ToStringNoNewLines();
    return out;
}

int DL_DCCH_MessageType::c1_counterCheck_Clear()
{
    c1_counterCheck_present = false;
    return 0;
}

bool DL_DCCH_MessageType::c1_counterCheck_IsPresent() const
{
    return c1_counterCheck_present;
}

UEInformationRequest_r9* DL_DCCH_MessageType::c1_ueInformationRequest_r9_Set()
{
    c1_ueInformationRequest_r9_present = true;
    return &c1_ueInformationRequest_r9;
}

int DL_DCCH_MessageType::c1_ueInformationRequest_r9_Set(UEInformationRequest_r9 &value)
{
    c1_ueInformationRequest_r9_present = true;
    c1_ueInformationRequest_r9 = value;
    return 0;
}

const UEInformationRequest_r9& DL_DCCH_MessageType::c1_ueInformationRequest_r9_Get() const
{
    return c1_ueInformationRequest_r9;
}

std::string DL_DCCH_MessageType::c1_ueInformationRequest_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ueInformationRequest_r9:\n";
    out += c1_ueInformationRequest_r9.ToString(indent+1);
    return out;
}

std::string DL_DCCH_MessageType::c1_ueInformationRequest_r9_ToStringNoNewLines() const
{
    std::string out = "ueInformationRequest_r9:";
    out += c1_ueInformationRequest_r9.ToStringNoNewLines();
    return out;
}

int DL_DCCH_MessageType::c1_ueInformationRequest_r9_Clear()
{
    c1_ueInformationRequest_r9_present = false;
    return 0;
}

bool DL_DCCH_MessageType::c1_ueInformationRequest_r9_IsPresent() const
{
    return c1_ueInformationRequest_r9_present;
}

LoggedMeasurementsConfiguration_r10* DL_DCCH_MessageType::c1_loggedMeasurementsConfiguration_r10_Set()
{
    c1_loggedMeasurementsConfiguration_r10_present = true;
    return &c1_loggedMeasurementsConfiguration_r10;
}

int DL_DCCH_MessageType::c1_loggedMeasurementsConfiguration_r10_Set(LoggedMeasurementsConfiguration_r10 &value)
{
    c1_loggedMeasurementsConfiguration_r10_present = true;
    c1_loggedMeasurementsConfiguration_r10 = value;
    return 0;
}

const LoggedMeasurementsConfiguration_r10& DL_DCCH_MessageType::c1_loggedMeasurementsConfiguration_r10_Get() const
{
    return c1_loggedMeasurementsConfiguration_r10;
}

std::string DL_DCCH_MessageType::c1_loggedMeasurementsConfiguration_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "loggedMeasurementsConfiguration_r10:\n";
    out += c1_loggedMeasurementsConfiguration_r10.ToString(indent+1);
    return out;
}

std::string DL_DCCH_MessageType::c1_loggedMeasurementsConfiguration_r10_ToStringNoNewLines() const
{
    std::string out = "loggedMeasurementsConfiguration_r10:";
    out += c1_loggedMeasurementsConfiguration_r10.ToStringNoNewLines();
    return out;
}

int DL_DCCH_MessageType::c1_loggedMeasurementsConfiguration_r10_Clear()
{
    c1_loggedMeasurementsConfiguration_r10_present = false;
    return 0;
}

bool DL_DCCH_MessageType::c1_loggedMeasurementsConfiguration_r10_IsPresent() const
{
    return c1_loggedMeasurementsConfiguration_r10_present;
}

RNReconfiguration_r10* DL_DCCH_MessageType::c1_rnReconfiguration_r10_Set()
{
    c1_rnReconfiguration_r10_present = true;
    return &c1_rnReconfiguration_r10;
}

int DL_DCCH_MessageType::c1_rnReconfiguration_r10_Set(RNReconfiguration_r10 &value)
{
    c1_rnReconfiguration_r10_present = true;
    c1_rnReconfiguration_r10 = value;
    return 0;
}

const RNReconfiguration_r10& DL_DCCH_MessageType::c1_rnReconfiguration_r10_Get() const
{
    return c1_rnReconfiguration_r10;
}

std::string DL_DCCH_MessageType::c1_rnReconfiguration_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "rnReconfiguration_r10:\n";
    out += c1_rnReconfiguration_r10.ToString(indent+1);
    return out;
}

std::string DL_DCCH_MessageType::c1_rnReconfiguration_r10_ToStringNoNewLines() const
{
    std::string out = "rnReconfiguration_r10:";
    out += c1_rnReconfiguration_r10.ToStringNoNewLines();
    return out;
}

int DL_DCCH_MessageType::c1_rnReconfiguration_r10_Clear()
{
    c1_rnReconfiguration_r10_present = false;
    return 0;
}

bool DL_DCCH_MessageType::c1_rnReconfiguration_r10_IsPresent() const
{
    return c1_rnReconfiguration_r10_present;
}

