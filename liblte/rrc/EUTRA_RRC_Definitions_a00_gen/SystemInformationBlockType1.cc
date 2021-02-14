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

#include "SystemInformationBlockType1.h"

#include <cmath>

int SystemInformationBlockType1::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(p_Max_IsPresent());
    bits.push_back(tdd_Config_IsPresent());
    bits.push_back(nonCriticalExtension_IsPresent());

    // Fields
    {
        if(0 != cellAccessRelatedInfo_value.Pack(bits))
        {
            printf("SystemInformationBlockType1:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != cellSelectionInfo_value.Pack(bits))
        {
            printf("SystemInformationBlockType1:: field pack failure\n");
            return -1;
        }
    }
    if(p_Max_IsPresent())
    {
        if(0 != p_Max.Pack(bits))
        {
            printf("SystemInformationBlockType1:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != freqBandIndicator_Pack(bits))
        {
            printf("SystemInformationBlockType1:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != schedulingInfoList.Pack(bits))
        {
            printf("SystemInformationBlockType1:: field pack failure\n");
            return -1;
        }
    }
    if(tdd_Config_IsPresent())
    {
        if(0 != tdd_Config.Pack(bits))
        {
            printf("SystemInformationBlockType1:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != si_WindowLength_Pack(bits))
        {
            printf("SystemInformationBlockType1:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != systemInfoValueTag_Pack(bits))
        {
            printf("SystemInformationBlockType1:: field pack failure\n");
            return -1;
        }
    }
    if(nonCriticalExtension_IsPresent())
    {
        if(0 != nonCriticalExtension.Pack(bits))
        {
            printf("SystemInformationBlockType1:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int SystemInformationBlockType1::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int SystemInformationBlockType1::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("SystemInformationBlockType1::Unpack() index out of bounds for optional indiator p_Max\n");
        return -1;
    }
    p_Max_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("SystemInformationBlockType1::Unpack() index out of bounds for optional indiator tdd_Config\n");
        return -1;
    }
    tdd_Config_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("SystemInformationBlockType1::Unpack() index out of bounds for optional indiator nonCriticalExtension\n");
        return -1;
    }
    nonCriticalExtension_present = bits[idx++];

    // Fields
    {
        if(0 != cellAccessRelatedInfo_value.Unpack(bits, idx))
        {
            printf("SystemInformationBlockType1:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != cellSelectionInfo_value.Unpack(bits, idx))
        {
            printf("SystemInformationBlockType1:: field unpack failure\n");
            return -1;
        }
    }
    if(p_Max_present)
    {
        if(0 != p_Max.Unpack(bits, idx))
        {
            printf("SystemInformationBlockType1:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != freqBandIndicator_Unpack(bits, idx))
        {
            printf("SystemInformationBlockType1:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != schedulingInfoList.Unpack(bits, idx))
        {
            printf("SystemInformationBlockType1:: field unpack failure\n");
            return -1;
        }
    }
    if(tdd_Config_present)
    {
        if(0 != tdd_Config.Unpack(bits, idx))
        {
            printf("SystemInformationBlockType1:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != si_WindowLength_Unpack(bits, idx))
        {
            printf("SystemInformationBlockType1:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != systemInfoValueTag_Unpack(bits, idx))
        {
            printf("SystemInformationBlockType1:: field unpack failure\n");
            return -1;
        }
    }
    if(nonCriticalExtension_present)
    {
        if(0 != nonCriticalExtension.Unpack(bits, idx))
        {
            printf("SystemInformationBlockType1:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string SystemInformationBlockType1::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "SystemInformationBlockType1:\n";
    out += cellAccessRelatedInfo_value.ToString(indent+1);
    out += cellSelectionInfo_value.ToString(indent+1);
    if(p_Max_IsPresent())
        out += p_Max_ToString(indent+1);
    out += freqBandIndicator_ToString(indent+1);
    out += schedulingInfoList_ToString(indent+1);
    if(tdd_Config_IsPresent())
        out += tdd_Config_ToString(indent+1);
    out += si_WindowLength_ToString(indent+1);
    out += systemInfoValueTag_ToString(indent+1);
    if(nonCriticalExtension_IsPresent())
        out += nonCriticalExtension_ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType1::ToStringNoNewLines() const
{
    std::string out = "SystemInformationBlockType1:";
    out += cellAccessRelatedInfo_value.ToStringNoNewLines();
    out += cellSelectionInfo_value.ToStringNoNewLines();
    if(p_Max_IsPresent())
        out += p_Max_ToStringNoNewLines();
    out += freqBandIndicator_ToStringNoNewLines();
    out += schedulingInfoList_ToStringNoNewLines();
    if(tdd_Config_IsPresent())
        out += tdd_Config_ToStringNoNewLines();
    out += si_WindowLength_ToStringNoNewLines();
    out += systemInfoValueTag_ToStringNoNewLines();
    if(nonCriticalExtension_IsPresent())
        out += nonCriticalExtension_ToStringNoNewLines();
    return out;
}

int SystemInformationBlockType1::cellAccessRelatedInfo::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(csg_Identity_IsPresent());

    // Fields
    {
        if(0 != plmn_IdentityList.Pack(bits))
        {
            printf("SystemInformationBlockType1::cellAccessRelatedInfo:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != trackingAreaCode.Pack(bits))
        {
            printf("SystemInformationBlockType1::cellAccessRelatedInfo:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != cellIdentity.Pack(bits))
        {
            printf("SystemInformationBlockType1::cellAccessRelatedInfo:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != cellBarred_Pack(bits))
        {
            printf("SystemInformationBlockType1::cellAccessRelatedInfo:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != intraFreqReselection_Pack(bits))
        {
            printf("SystemInformationBlockType1::cellAccessRelatedInfo:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != csg_Indication_Pack(bits))
        {
            printf("SystemInformationBlockType1::cellAccessRelatedInfo:: field pack failure\n");
            return -1;
        }
    }
    if(csg_Identity_IsPresent())
    {
        if(0 != csg_Identity.Pack(bits))
        {
            printf("SystemInformationBlockType1::cellAccessRelatedInfo:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int SystemInformationBlockType1::cellAccessRelatedInfo::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int SystemInformationBlockType1::cellAccessRelatedInfo::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("cellAccessRelatedInfo::Unpack() index out of bounds for optional indiator csg_Identity\n");
        return -1;
    }
    csg_Identity_present = bits[idx++];

    // Fields
    {
        if(0 != plmn_IdentityList.Unpack(bits, idx))
        {
            printf("SystemInformationBlockType1::cellAccessRelatedInfo:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != trackingAreaCode.Unpack(bits, idx))
        {
            printf("SystemInformationBlockType1::cellAccessRelatedInfo:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != cellIdentity.Unpack(bits, idx))
        {
            printf("SystemInformationBlockType1::cellAccessRelatedInfo:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != cellBarred_Unpack(bits, idx))
        {
            printf("SystemInformationBlockType1::cellAccessRelatedInfo:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != intraFreqReselection_Unpack(bits, idx))
        {
            printf("SystemInformationBlockType1::cellAccessRelatedInfo:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != csg_Indication_Unpack(bits, idx))
        {
            printf("SystemInformationBlockType1::cellAccessRelatedInfo:: field unpack failure\n");
            return -1;
        }
    }
    if(csg_Identity_present)
    {
        if(0 != csg_Identity.Unpack(bits, idx))
        {
            printf("SystemInformationBlockType1::cellAccessRelatedInfo:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string SystemInformationBlockType1::cellAccessRelatedInfo::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cellAccessRelatedInfo:\n";
    out += plmn_IdentityList_ToString(indent+1);
    out += trackingAreaCode_ToString(indent+1);
    out += cellIdentity_ToString(indent+1);
    out += cellBarred_ToString(indent+1);
    out += intraFreqReselection_ToString(indent+1);
    out += csg_Indication_ToString(indent+1);
    if(csg_Identity_IsPresent())
        out += csg_Identity_ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType1::cellAccessRelatedInfo::ToStringNoNewLines() const
{
    std::string out = "cellAccessRelatedInfo:";
    out += plmn_IdentityList_ToStringNoNewLines();
    out += trackingAreaCode_ToStringNoNewLines();
    out += cellIdentity_ToStringNoNewLines();
    out += cellBarred_ToStringNoNewLines();
    out += intraFreqReselection_ToStringNoNewLines();
    out += csg_Indication_ToStringNoNewLines();
    if(csg_Identity_IsPresent())
        out += csg_Identity_ToStringNoNewLines();
    return out;
}

PLMN_IdentityList* SystemInformationBlockType1::cellAccessRelatedInfo::plmn_IdentityList_Set()
{
    plmn_IdentityList_present = true;
    return &plmn_IdentityList;
}

int SystemInformationBlockType1::cellAccessRelatedInfo::plmn_IdentityList_Set(PLMN_IdentityList &value)
{
    plmn_IdentityList_present = true;
    plmn_IdentityList = value;
    return 0;
}

const PLMN_IdentityList& SystemInformationBlockType1::cellAccessRelatedInfo::plmn_IdentityList_Get() const
{
    return plmn_IdentityList;
}

std::string SystemInformationBlockType1::cellAccessRelatedInfo::plmn_IdentityList_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "plmn_IdentityList:\n";
    out += plmn_IdentityList.ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType1::cellAccessRelatedInfo::plmn_IdentityList_ToStringNoNewLines() const
{
    std::string out = "plmn_IdentityList:";
    out += plmn_IdentityList.ToStringNoNewLines();
    return out;
}

int SystemInformationBlockType1::cellAccessRelatedInfo::plmn_IdentityList_Clear()
{
    plmn_IdentityList_present = false;
    return 0;
}

bool SystemInformationBlockType1::cellAccessRelatedInfo::plmn_IdentityList_IsPresent() const
{
    return plmn_IdentityList_present;
}

TrackingAreaCode* SystemInformationBlockType1::cellAccessRelatedInfo::trackingAreaCode_Set()
{
    trackingAreaCode_present = true;
    return &trackingAreaCode;
}

int SystemInformationBlockType1::cellAccessRelatedInfo::trackingAreaCode_Set(TrackingAreaCode &value)
{
    trackingAreaCode_present = true;
    trackingAreaCode = value;
    return 0;
}

const TrackingAreaCode& SystemInformationBlockType1::cellAccessRelatedInfo::trackingAreaCode_Get() const
{
    return trackingAreaCode;
}

std::string SystemInformationBlockType1::cellAccessRelatedInfo::trackingAreaCode_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "trackingAreaCode:\n";
    out += trackingAreaCode.ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType1::cellAccessRelatedInfo::trackingAreaCode_ToStringNoNewLines() const
{
    std::string out = "trackingAreaCode:";
    out += trackingAreaCode.ToStringNoNewLines();
    return out;
}

int SystemInformationBlockType1::cellAccessRelatedInfo::trackingAreaCode_Clear()
{
    trackingAreaCode_present = false;
    return 0;
}

bool SystemInformationBlockType1::cellAccessRelatedInfo::trackingAreaCode_IsPresent() const
{
    return trackingAreaCode_present;
}

CellIdentity* SystemInformationBlockType1::cellAccessRelatedInfo::cellIdentity_Set()
{
    cellIdentity_present = true;
    return &cellIdentity;
}

int SystemInformationBlockType1::cellAccessRelatedInfo::cellIdentity_Set(CellIdentity &value)
{
    cellIdentity_present = true;
    cellIdentity = value;
    return 0;
}

const CellIdentity& SystemInformationBlockType1::cellAccessRelatedInfo::cellIdentity_Get() const
{
    return cellIdentity;
}

std::string SystemInformationBlockType1::cellAccessRelatedInfo::cellIdentity_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cellIdentity:\n";
    out += cellIdentity.ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType1::cellAccessRelatedInfo::cellIdentity_ToStringNoNewLines() const
{
    std::string out = "cellIdentity:";
    out += cellIdentity.ToStringNoNewLines();
    return out;
}

int SystemInformationBlockType1::cellAccessRelatedInfo::cellIdentity_Clear()
{
    cellIdentity_present = false;
    return 0;
}

bool SystemInformationBlockType1::cellAccessRelatedInfo::cellIdentity_IsPresent() const
{
    return cellIdentity_present;
}

int SystemInformationBlockType1::cellAccessRelatedInfo::cellBarred_Pack(std::vector<uint8_t> &bits)
{
    if(!cellBarred_present)
    {
        printf("SystemInformationBlockType1::cellAccessRelatedInfo::cellBarred_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((cellBarred_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int SystemInformationBlockType1::cellAccessRelatedInfo::cellBarred_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return cellBarred_Unpack(bits, idx);
}

int SystemInformationBlockType1::cellAccessRelatedInfo::cellBarred_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("SystemInformationBlockType1::cellAccessRelatedInfo::cellBarred_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 1)
    {
        printf("SystemInformationBlockType1::cellAccessRelatedInfo::cellBarred_Unpack() max failure\n");
        return -1;
    }
    cellBarred_internal_value = (cellBarred_Enum)packed_val;
    cellBarred_present = true;
    return 0;
}

SystemInformationBlockType1::cellAccessRelatedInfo::cellBarred_Enum SystemInformationBlockType1::cellAccessRelatedInfo::cellBarred_Value() const
{
    if(cellBarred_present)
        return cellBarred_internal_value;
    return (SystemInformationBlockType1::cellAccessRelatedInfo::cellBarred_Enum)0;
}

int SystemInformationBlockType1::cellAccessRelatedInfo::cellBarred_SetValue(cellBarred_Enum value)
{
    cellBarred_internal_value = value;
    cellBarred_present = true;
    return 0;
}

int SystemInformationBlockType1::cellAccessRelatedInfo::cellBarred_SetValue(std::string value)
{
    if("barred" == value)
    {
        cellBarred_internal_value = k_cellBarred_barred;
        cellBarred_present = true;
        return 0;
    }
    if("notBarred" == value)
    {
        cellBarred_internal_value = k_cellBarred_notBarred;
        cellBarred_present = true;
        return 0;
    }
    return 1;
}

std::string SystemInformationBlockType1::cellAccessRelatedInfo::cellBarred_ValueToString(cellBarred_Enum value) const
{
    if(k_cellBarred_barred == value)
        return "barred";
    if(k_cellBarred_notBarred == value)
        return "notBarred";
    return "";
}

uint64_t SystemInformationBlockType1::cellAccessRelatedInfo::cellBarred_NumberOfValues() const
{
    return 2;
}

std::string SystemInformationBlockType1::cellAccessRelatedInfo::cellBarred_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cellBarred = " + cellBarred_ValueToString(cellBarred_internal_value) + "\n";
    return out;
}

std::string SystemInformationBlockType1::cellAccessRelatedInfo::cellBarred_ToStringNoNewLines() const
{
    std::string out = "cellBarred=" + cellBarred_ValueToString(cellBarred_internal_value) + ",";
    return out;
}

int SystemInformationBlockType1::cellAccessRelatedInfo::cellBarred_Clear()
{
    cellBarred_present = false;
    return 0;
}

bool SystemInformationBlockType1::cellAccessRelatedInfo::cellBarred_IsPresent() const
{
    return cellBarred_present;
}

int SystemInformationBlockType1::cellAccessRelatedInfo::intraFreqReselection_Pack(std::vector<uint8_t> &bits)
{
    if(!intraFreqReselection_present)
    {
        printf("SystemInformationBlockType1::cellAccessRelatedInfo::intraFreqReselection_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((intraFreqReselection_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int SystemInformationBlockType1::cellAccessRelatedInfo::intraFreqReselection_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return intraFreqReselection_Unpack(bits, idx);
}

int SystemInformationBlockType1::cellAccessRelatedInfo::intraFreqReselection_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("SystemInformationBlockType1::cellAccessRelatedInfo::intraFreqReselection_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 1)
    {
        printf("SystemInformationBlockType1::cellAccessRelatedInfo::intraFreqReselection_Unpack() max failure\n");
        return -1;
    }
    intraFreqReselection_internal_value = (intraFreqReselection_Enum)packed_val;
    intraFreqReselection_present = true;
    return 0;
}

SystemInformationBlockType1::cellAccessRelatedInfo::intraFreqReselection_Enum SystemInformationBlockType1::cellAccessRelatedInfo::intraFreqReselection_Value() const
{
    if(intraFreqReselection_present)
        return intraFreqReselection_internal_value;
    return (SystemInformationBlockType1::cellAccessRelatedInfo::intraFreqReselection_Enum)0;
}

int SystemInformationBlockType1::cellAccessRelatedInfo::intraFreqReselection_SetValue(intraFreqReselection_Enum value)
{
    intraFreqReselection_internal_value = value;
    intraFreqReselection_present = true;
    return 0;
}

int SystemInformationBlockType1::cellAccessRelatedInfo::intraFreqReselection_SetValue(std::string value)
{
    if("allowed" == value)
    {
        intraFreqReselection_internal_value = k_intraFreqReselection_allowed;
        intraFreqReselection_present = true;
        return 0;
    }
    if("notAllowed" == value)
    {
        intraFreqReselection_internal_value = k_intraFreqReselection_notAllowed;
        intraFreqReselection_present = true;
        return 0;
    }
    return 1;
}

std::string SystemInformationBlockType1::cellAccessRelatedInfo::intraFreqReselection_ValueToString(intraFreqReselection_Enum value) const
{
    if(k_intraFreqReselection_allowed == value)
        return "allowed";
    if(k_intraFreqReselection_notAllowed == value)
        return "notAllowed";
    return "";
}

uint64_t SystemInformationBlockType1::cellAccessRelatedInfo::intraFreqReselection_NumberOfValues() const
{
    return 2;
}

std::string SystemInformationBlockType1::cellAccessRelatedInfo::intraFreqReselection_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "intraFreqReselection = " + intraFreqReselection_ValueToString(intraFreqReselection_internal_value) + "\n";
    return out;
}

std::string SystemInformationBlockType1::cellAccessRelatedInfo::intraFreqReselection_ToStringNoNewLines() const
{
    std::string out = "intraFreqReselection=" + intraFreqReselection_ValueToString(intraFreqReselection_internal_value) + ",";
    return out;
}

int SystemInformationBlockType1::cellAccessRelatedInfo::intraFreqReselection_Clear()
{
    intraFreqReselection_present = false;
    return 0;
}

bool SystemInformationBlockType1::cellAccessRelatedInfo::intraFreqReselection_IsPresent() const
{
    return intraFreqReselection_present;
}

int SystemInformationBlockType1::cellAccessRelatedInfo::csg_Indication_Pack(std::vector<uint8_t> &bits)
{
    if(!csg_Indication_present)
    {
        printf("SystemInformationBlockType1::cellAccessRelatedInfo::csg_Indication_Pack() presence failure\n");
        return -1;
    }
    bits.push_back(csg_Indication_internal_value);
    return 0;
}

int SystemInformationBlockType1::cellAccessRelatedInfo::csg_Indication_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return csg_Indication_Unpack(bits, idx);
}

int SystemInformationBlockType1::cellAccessRelatedInfo::csg_Indication_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    if((idx + 1) > bits.size())
    {
        printf("SystemInformationBlockType1::cellAccessRelatedInfo::csg_Indication_Unpack() index out of bounds\n");
        return -1;
    }
    csg_Indication_internal_value = bits[idx++];
    csg_Indication_present = true;
    return 0;
}

bool SystemInformationBlockType1::cellAccessRelatedInfo::csg_Indication_Value() const
{
    if(csg_Indication_present)
        return csg_Indication_internal_value;
    return false;
}

int SystemInformationBlockType1::cellAccessRelatedInfo::csg_Indication_SetValue(bool value)
{
    csg_Indication_internal_value = value;
    csg_Indication_present = true;
    return 0;
}

std::string SystemInformationBlockType1::cellAccessRelatedInfo::csg_Indication_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "csg_Indication = " + std::to_string(csg_Indication_internal_value) + "\n";
    return out;
}

std::string SystemInformationBlockType1::cellAccessRelatedInfo::csg_Indication_ToStringNoNewLines() const
{
    std::string out = "csg_Indication=" + std::to_string(csg_Indication_internal_value) + ",";
    return out;
}

int SystemInformationBlockType1::cellAccessRelatedInfo::csg_Indication_Clear()
{
    csg_Indication_present = false;
    return 0;
}

bool SystemInformationBlockType1::cellAccessRelatedInfo::csg_Indication_IsPresent() const
{
    return csg_Indication_present;
}

CSG_Identity* SystemInformationBlockType1::cellAccessRelatedInfo::csg_Identity_Set()
{
    csg_Identity_present = true;
    return &csg_Identity;
}

int SystemInformationBlockType1::cellAccessRelatedInfo::csg_Identity_Set(CSG_Identity &value)
{
    csg_Identity_present = true;
    csg_Identity = value;
    return 0;
}

const CSG_Identity& SystemInformationBlockType1::cellAccessRelatedInfo::csg_Identity_Get() const
{
    return csg_Identity;
}

std::string SystemInformationBlockType1::cellAccessRelatedInfo::csg_Identity_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "csg_Identity:\n";
    out += csg_Identity.ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType1::cellAccessRelatedInfo::csg_Identity_ToStringNoNewLines() const
{
    std::string out = "csg_Identity:";
    out += csg_Identity.ToStringNoNewLines();
    return out;
}

int SystemInformationBlockType1::cellAccessRelatedInfo::csg_Identity_Clear()
{
    csg_Identity_present = false;
    return 0;
}

bool SystemInformationBlockType1::cellAccessRelatedInfo::csg_Identity_IsPresent() const
{
    return csg_Identity_present;
}

int SystemInformationBlockType1::cellSelectionInfo::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(q_RxLevMinOffset_IsPresent());

    // Fields
    {
        if(0 != q_RxLevMin.Pack(bits))
        {
            printf("SystemInformationBlockType1::cellSelectionInfo:: field pack failure\n");
            return -1;
        }
    }
    if(q_RxLevMinOffset_IsPresent())
    {
        if(0 != q_RxLevMinOffset_Pack(bits))
        {
            printf("SystemInformationBlockType1::cellSelectionInfo:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int SystemInformationBlockType1::cellSelectionInfo::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int SystemInformationBlockType1::cellSelectionInfo::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("cellSelectionInfo::Unpack() index out of bounds for optional indiator q_RxLevMinOffset\n");
        return -1;
    }
    q_RxLevMinOffset_present = bits[idx++];

    // Fields
    {
        if(0 != q_RxLevMin.Unpack(bits, idx))
        {
            printf("SystemInformationBlockType1::cellSelectionInfo:: field unpack failure\n");
            return -1;
        }
    }
    if(q_RxLevMinOffset_present)
    {
        if(0 != q_RxLevMinOffset_Unpack(bits, idx))
        {
            printf("SystemInformationBlockType1::cellSelectionInfo:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string SystemInformationBlockType1::cellSelectionInfo::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cellSelectionInfo:\n";
    out += q_RxLevMin_ToString(indent+1);
    if(q_RxLevMinOffset_IsPresent())
        out += q_RxLevMinOffset_ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType1::cellSelectionInfo::ToStringNoNewLines() const
{
    std::string out = "cellSelectionInfo:";
    out += q_RxLevMin_ToStringNoNewLines();
    if(q_RxLevMinOffset_IsPresent())
        out += q_RxLevMinOffset_ToStringNoNewLines();
    return out;
}

Q_RxLevMin* SystemInformationBlockType1::cellSelectionInfo::q_RxLevMin_Set()
{
    q_RxLevMin_present = true;
    return &q_RxLevMin;
}

int SystemInformationBlockType1::cellSelectionInfo::q_RxLevMin_Set(Q_RxLevMin &value)
{
    q_RxLevMin_present = true;
    q_RxLevMin = value;
    return 0;
}

const Q_RxLevMin& SystemInformationBlockType1::cellSelectionInfo::q_RxLevMin_Get() const
{
    return q_RxLevMin;
}

std::string SystemInformationBlockType1::cellSelectionInfo::q_RxLevMin_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "q_RxLevMin:\n";
    out += q_RxLevMin.ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType1::cellSelectionInfo::q_RxLevMin_ToStringNoNewLines() const
{
    std::string out = "q_RxLevMin:";
    out += q_RxLevMin.ToStringNoNewLines();
    return out;
}

int SystemInformationBlockType1::cellSelectionInfo::q_RxLevMin_Clear()
{
    q_RxLevMin_present = false;
    return 0;
}

bool SystemInformationBlockType1::cellSelectionInfo::q_RxLevMin_IsPresent() const
{
    return q_RxLevMin_present;
}

int SystemInformationBlockType1::cellSelectionInfo::q_RxLevMinOffset_Pack(std::vector<uint8_t> &bits)
{
    int64_t val_to_pack = q_RxLevMinOffset_internal_value - (1);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (8 - 1))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int SystemInformationBlockType1::cellSelectionInfo::q_RxLevMinOffset_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return q_RxLevMinOffset_Unpack(bits, idx);
}

int SystemInformationBlockType1::cellSelectionInfo::q_RxLevMinOffset_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (8 - 1))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("SystemInformationBlockType1::cellSelectionInfo::q_RxLevMinOffset_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    q_RxLevMinOffset_internal_value = packed_val + 1;
    q_RxLevMinOffset_present = true;
    return 0;
}

int64_t SystemInformationBlockType1::cellSelectionInfo::q_RxLevMinOffset_Value() const
{
    if(q_RxLevMinOffset_present)
        return q_RxLevMinOffset_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int SystemInformationBlockType1::cellSelectionInfo::q_RxLevMinOffset_SetValue(int64_t value)
{
    if(value < 1 || value > 8)
    {
        printf("SystemInformationBlockType1::cellSelectionInfo::q_RxLevMinOffset_SetValue() range failure\n");
        return -1;
    }
    q_RxLevMinOffset_internal_value = value;
    q_RxLevMinOffset_present = true;
    return 0;
}

std::string SystemInformationBlockType1::cellSelectionInfo::q_RxLevMinOffset_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "q_RxLevMinOffset = " + std::to_string(q_RxLevMinOffset_internal_value) + "\n";
    return out;
}

std::string SystemInformationBlockType1::cellSelectionInfo::q_RxLevMinOffset_ToStringNoNewLines() const
{
    std::string out = "q_RxLevMinOffset=" + std::to_string(q_RxLevMinOffset_internal_value) + ",";
    return out;
}

int SystemInformationBlockType1::cellSelectionInfo::q_RxLevMinOffset_Clear()
{
    q_RxLevMinOffset_present = false;
    return 0;
}

bool SystemInformationBlockType1::cellSelectionInfo::q_RxLevMinOffset_IsPresent() const
{
    return q_RxLevMinOffset_present;
}

P_Max* SystemInformationBlockType1::p_Max_Set()
{
    p_Max_present = true;
    return &p_Max;
}

int SystemInformationBlockType1::p_Max_Set(P_Max &value)
{
    p_Max_present = true;
    p_Max = value;
    return 0;
}

const P_Max& SystemInformationBlockType1::p_Max_Get() const
{
    return p_Max;
}

std::string SystemInformationBlockType1::p_Max_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "p_Max:\n";
    out += p_Max.ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType1::p_Max_ToStringNoNewLines() const
{
    std::string out = "p_Max:";
    out += p_Max.ToStringNoNewLines();
    return out;
}

int SystemInformationBlockType1::p_Max_Clear()
{
    p_Max_present = false;
    return 0;
}

bool SystemInformationBlockType1::p_Max_IsPresent() const
{
    return p_Max_present;
}

int SystemInformationBlockType1::freqBandIndicator_Pack(std::vector<uint8_t> &bits)
{
    if(!freqBandIndicator_present)
    {
        printf("SystemInformationBlockType1::freqBandIndicator_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = freqBandIndicator_internal_value - (1);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (64 - 1))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int SystemInformationBlockType1::freqBandIndicator_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return freqBandIndicator_Unpack(bits, idx);
}

int SystemInformationBlockType1::freqBandIndicator_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (64 - 1))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("SystemInformationBlockType1::freqBandIndicator_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    freqBandIndicator_internal_value = packed_val + 1;
    freqBandIndicator_present = true;
    return 0;
}

int64_t SystemInformationBlockType1::freqBandIndicator_Value() const
{
    if(freqBandIndicator_present)
        return freqBandIndicator_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int SystemInformationBlockType1::freqBandIndicator_SetValue(int64_t value)
{
    if(value < 1 || value > 64)
    {
        printf("SystemInformationBlockType1::freqBandIndicator_SetValue() range failure\n");
        return -1;
    }
    freqBandIndicator_internal_value = value;
    freqBandIndicator_present = true;
    return 0;
}

std::string SystemInformationBlockType1::freqBandIndicator_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "freqBandIndicator = " + std::to_string(freqBandIndicator_internal_value) + "\n";
    return out;
}

std::string SystemInformationBlockType1::freqBandIndicator_ToStringNoNewLines() const
{
    std::string out = "freqBandIndicator=" + std::to_string(freqBandIndicator_internal_value) + ",";
    return out;
}

int SystemInformationBlockType1::freqBandIndicator_Clear()
{
    freqBandIndicator_present = false;
    return 0;
}

bool SystemInformationBlockType1::freqBandIndicator_IsPresent() const
{
    return freqBandIndicator_present;
}

SchedulingInfoList* SystemInformationBlockType1::schedulingInfoList_Set()
{
    schedulingInfoList_present = true;
    return &schedulingInfoList;
}

int SystemInformationBlockType1::schedulingInfoList_Set(SchedulingInfoList &value)
{
    schedulingInfoList_present = true;
    schedulingInfoList = value;
    return 0;
}

const SchedulingInfoList& SystemInformationBlockType1::schedulingInfoList_Get() const
{
    return schedulingInfoList;
}

std::string SystemInformationBlockType1::schedulingInfoList_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "schedulingInfoList:\n";
    out += schedulingInfoList.ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType1::schedulingInfoList_ToStringNoNewLines() const
{
    std::string out = "schedulingInfoList:";
    out += schedulingInfoList.ToStringNoNewLines();
    return out;
}

int SystemInformationBlockType1::schedulingInfoList_Clear()
{
    schedulingInfoList_present = false;
    return 0;
}

bool SystemInformationBlockType1::schedulingInfoList_IsPresent() const
{
    return schedulingInfoList_present;
}

TDD_Config* SystemInformationBlockType1::tdd_Config_Set()
{
    tdd_Config_present = true;
    return &tdd_Config;
}

int SystemInformationBlockType1::tdd_Config_Set(TDD_Config &value)
{
    tdd_Config_present = true;
    tdd_Config = value;
    return 0;
}

const TDD_Config& SystemInformationBlockType1::tdd_Config_Get() const
{
    return tdd_Config;
}

std::string SystemInformationBlockType1::tdd_Config_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "tdd_Config:\n";
    out += tdd_Config.ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType1::tdd_Config_ToStringNoNewLines() const
{
    std::string out = "tdd_Config:";
    out += tdd_Config.ToStringNoNewLines();
    return out;
}

int SystemInformationBlockType1::tdd_Config_Clear()
{
    tdd_Config_present = false;
    return 0;
}

bool SystemInformationBlockType1::tdd_Config_IsPresent() const
{
    return tdd_Config_present;
}

int SystemInformationBlockType1::si_WindowLength_Pack(std::vector<uint8_t> &bits)
{
    if(!si_WindowLength_present)
    {
        printf("SystemInformationBlockType1::si_WindowLength_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 3;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((si_WindowLength_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int SystemInformationBlockType1::si_WindowLength_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return si_WindowLength_Unpack(bits, idx);
}

int SystemInformationBlockType1::si_WindowLength_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 3;
    if((idx + N_bits) > bits.size())
    {
        printf("SystemInformationBlockType1::si_WindowLength_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 6)
    {
        printf("SystemInformationBlockType1::si_WindowLength_Unpack() max failure\n");
        return -1;
    }
    si_WindowLength_internal_value = (si_WindowLength_Enum)packed_val;
    si_WindowLength_present = true;
    return 0;
}

SystemInformationBlockType1::si_WindowLength_Enum SystemInformationBlockType1::si_WindowLength_Value() const
{
    if(si_WindowLength_present)
        return si_WindowLength_internal_value;
    return (SystemInformationBlockType1::si_WindowLength_Enum)0;
}

int SystemInformationBlockType1::si_WindowLength_SetValue(si_WindowLength_Enum value)
{
    si_WindowLength_internal_value = value;
    si_WindowLength_present = true;
    return 0;
}

int SystemInformationBlockType1::si_WindowLength_SetValue(std::string value)
{
    if("ms1" == value)
    {
        si_WindowLength_internal_value = k_si_WindowLength_ms1;
        si_WindowLength_present = true;
        return 0;
    }
    if("ms2" == value)
    {
        si_WindowLength_internal_value = k_si_WindowLength_ms2;
        si_WindowLength_present = true;
        return 0;
    }
    if("ms5" == value)
    {
        si_WindowLength_internal_value = k_si_WindowLength_ms5;
        si_WindowLength_present = true;
        return 0;
    }
    if("ms10" == value)
    {
        si_WindowLength_internal_value = k_si_WindowLength_ms10;
        si_WindowLength_present = true;
        return 0;
    }
    if("ms15" == value)
    {
        si_WindowLength_internal_value = k_si_WindowLength_ms15;
        si_WindowLength_present = true;
        return 0;
    }
    if("ms20" == value)
    {
        si_WindowLength_internal_value = k_si_WindowLength_ms20;
        si_WindowLength_present = true;
        return 0;
    }
    if("ms40" == value)
    {
        si_WindowLength_internal_value = k_si_WindowLength_ms40;
        si_WindowLength_present = true;
        return 0;
    }
    return 1;
}

std::string SystemInformationBlockType1::si_WindowLength_ValueToString(si_WindowLength_Enum value) const
{
    if(k_si_WindowLength_ms1 == value)
        return "ms1";
    if(k_si_WindowLength_ms2 == value)
        return "ms2";
    if(k_si_WindowLength_ms5 == value)
        return "ms5";
    if(k_si_WindowLength_ms10 == value)
        return "ms10";
    if(k_si_WindowLength_ms15 == value)
        return "ms15";
    if(k_si_WindowLength_ms20 == value)
        return "ms20";
    if(k_si_WindowLength_ms40 == value)
        return "ms40";
    return "";
}

uint64_t SystemInformationBlockType1::si_WindowLength_NumberOfValues() const
{
    return 7;
}

std::string SystemInformationBlockType1::si_WindowLength_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "si_WindowLength = " + si_WindowLength_ValueToString(si_WindowLength_internal_value) + "\n";
    return out;
}

std::string SystemInformationBlockType1::si_WindowLength_ToStringNoNewLines() const
{
    std::string out = "si_WindowLength=" + si_WindowLength_ValueToString(si_WindowLength_internal_value) + ",";
    return out;
}

int SystemInformationBlockType1::si_WindowLength_Clear()
{
    si_WindowLength_present = false;
    return 0;
}

bool SystemInformationBlockType1::si_WindowLength_IsPresent() const
{
    return si_WindowLength_present;
}

int SystemInformationBlockType1::systemInfoValueTag_Pack(std::vector<uint8_t> &bits)
{
    if(!systemInfoValueTag_present)
    {
        printf("SystemInformationBlockType1::systemInfoValueTag_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = systemInfoValueTag_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (31 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int SystemInformationBlockType1::systemInfoValueTag_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return systemInfoValueTag_Unpack(bits, idx);
}

int SystemInformationBlockType1::systemInfoValueTag_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (31 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("SystemInformationBlockType1::systemInfoValueTag_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    systemInfoValueTag_internal_value = packed_val + 0;
    systemInfoValueTag_present = true;
    return 0;
}

int64_t SystemInformationBlockType1::systemInfoValueTag_Value() const
{
    if(systemInfoValueTag_present)
        return systemInfoValueTag_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int SystemInformationBlockType1::systemInfoValueTag_SetValue(int64_t value)
{
    if(value < 0 || value > 31)
    {
        printf("SystemInformationBlockType1::systemInfoValueTag_SetValue() range failure\n");
        return -1;
    }
    systemInfoValueTag_internal_value = value;
    systemInfoValueTag_present = true;
    return 0;
}

std::string SystemInformationBlockType1::systemInfoValueTag_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "systemInfoValueTag = " + std::to_string(systemInfoValueTag_internal_value) + "\n";
    return out;
}

std::string SystemInformationBlockType1::systemInfoValueTag_ToStringNoNewLines() const
{
    std::string out = "systemInfoValueTag=" + std::to_string(systemInfoValueTag_internal_value) + ",";
    return out;
}

int SystemInformationBlockType1::systemInfoValueTag_Clear()
{
    systemInfoValueTag_present = false;
    return 0;
}

bool SystemInformationBlockType1::systemInfoValueTag_IsPresent() const
{
    return systemInfoValueTag_present;
}

SystemInformationBlockType1_v890_IEs* SystemInformationBlockType1::nonCriticalExtension_Set()
{
    nonCriticalExtension_present = true;
    return &nonCriticalExtension;
}

int SystemInformationBlockType1::nonCriticalExtension_Set(SystemInformationBlockType1_v890_IEs &value)
{
    nonCriticalExtension_present = true;
    nonCriticalExtension = value;
    return 0;
}

const SystemInformationBlockType1_v890_IEs& SystemInformationBlockType1::nonCriticalExtension_Get() const
{
    return nonCriticalExtension;
}

std::string SystemInformationBlockType1::nonCriticalExtension_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "nonCriticalExtension:\n";
    out += nonCriticalExtension.ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType1::nonCriticalExtension_ToStringNoNewLines() const
{
    std::string out = "nonCriticalExtension:";
    out += nonCriticalExtension.ToStringNoNewLines();
    return out;
}

int SystemInformationBlockType1::nonCriticalExtension_Clear()
{
    nonCriticalExtension_present = false;
    return 0;
}

bool SystemInformationBlockType1::nonCriticalExtension_IsPresent() const
{
    return nonCriticalExtension_present;
}

