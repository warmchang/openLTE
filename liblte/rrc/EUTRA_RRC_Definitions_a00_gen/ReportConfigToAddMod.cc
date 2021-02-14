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

#include "ReportConfigToAddMod.h"

#include <cmath>

int ReportConfigToAddMod::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != reportConfigId.Pack(bits))
        {
            printf("ReportConfigToAddMod:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != reportConfig_Pack(bits))
        {
            printf("ReportConfigToAddMod:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int ReportConfigToAddMod::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int ReportConfigToAddMod::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != reportConfigId.Unpack(bits, idx))
        {
            printf("ReportConfigToAddMod:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != reportConfig_Unpack(bits, idx))
        {
            printf("ReportConfigToAddMod:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string ReportConfigToAddMod::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ReportConfigToAddMod:\n";
    out += reportConfigId_ToString(indent+1);
    out += reportConfig_ToString(indent+1);
    return out;
}

std::string ReportConfigToAddMod::ToStringNoNewLines() const
{
    std::string out = "ReportConfigToAddMod:";
    out += reportConfigId_ToStringNoNewLines();
    out += reportConfig_ToStringNoNewLines();
    return out;
}

ReportConfigId* ReportConfigToAddMod::reportConfigId_Set()
{
    reportConfigId_present = true;
    return &reportConfigId;
}

int ReportConfigToAddMod::reportConfigId_Set(ReportConfigId &value)
{
    reportConfigId_present = true;
    reportConfigId = value;
    return 0;
}

const ReportConfigId& ReportConfigToAddMod::reportConfigId_Get() const
{
    return reportConfigId;
}

std::string ReportConfigToAddMod::reportConfigId_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "reportConfigId:\n";
    out += reportConfigId.ToString(indent+1);
    return out;
}

std::string ReportConfigToAddMod::reportConfigId_ToStringNoNewLines() const
{
    std::string out = "reportConfigId:";
    out += reportConfigId.ToStringNoNewLines();
    return out;
}

int ReportConfigToAddMod::reportConfigId_Clear()
{
    reportConfigId_present = false;
    return 0;
}

bool ReportConfigToAddMod::reportConfigId_IsPresent() const
{
    return reportConfigId_present;
}

int ReportConfigToAddMod::reportConfig_Pack(std::vector<uint8_t> &bits)
{
    if(!reportConfig_present)
    {
        printf("ReportConfigToAddMod::reportConfig_Pack() presence failure\n");
        return -1;
    }
    // Extension indicator

    // Choice
    for(uint32_t i=0; i<1; i++)
        bits.push_back((reportConfig_internal_choice >> (1-i-1)) & 1);

    // Fields
    if(reportConfig_internal_choice == k_reportConfig_reportConfigEUTRA)
    {
        if(0 != reportConfig_reportConfigEUTRA.Pack(bits))
        {
            printf("ReportConfigToAddMod::reportConfig_reportConfigEUTRA pack failure\n");
            return -1;
        }
    }
    if(reportConfig_internal_choice == k_reportConfig_reportConfigInterRAT)
    {
        if(0 != reportConfig_reportConfigInterRAT.Pack(bits))
        {
            printf("ReportConfigToAddMod::reportConfig_reportConfigInterRAT pack failure\n");
            return -1;
        }
    }
    return 0;
}

int ReportConfigToAddMod::reportConfig_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return reportConfig_Unpack(bits, idx);
}

int ReportConfigToAddMod::reportConfig_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 1) > bits.size())
    {
        printf("ReportConfigToAddMod::reportConfig_Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<1; i++)
        packed_val |= bits[idx++] << (1-i-1);

    if((ReportConfigToAddMod::reportConfig_Enum)packed_val > k_reportConfig_reportConfigInterRAT)
    {
        printf("ReportConfigToAddMod::reportConfig_Unpack() choice range failure\n");
        return -1;
    }
    reportConfig_internal_choice = (ReportConfigToAddMod::reportConfig_Enum)packed_val;
    reportConfig_present = true;

    // Fields
    if(reportConfig_internal_choice == k_reportConfig_reportConfigEUTRA)
    {
        if(0 != reportConfig_reportConfigEUTRA.Unpack(bits, idx))
        {
            printf("ReportConfigToAddMod::reportConfig_reportConfigEUTRA unpack failure\n");
            return -1;
        }
    }
    if(reportConfig_internal_choice == k_reportConfig_reportConfigInterRAT)
    {
        if(0 != reportConfig_reportConfigInterRAT.Unpack(bits, idx))
        {
            printf("ReportConfigToAddMod::reportConfig_reportConfigInterRAT unpack failure\n");
            return -1;
        }
    }
    return 0;
}

ReportConfigToAddMod::reportConfig_Enum ReportConfigToAddMod::reportConfig_Choice() const
{
    if(reportConfig_present)
        return reportConfig_internal_choice;
    return (ReportConfigToAddMod::reportConfig_Enum)0;
}

int ReportConfigToAddMod::reportConfig_SetChoice(ReportConfigToAddMod::reportConfig_Enum choice)
{
    reportConfig_internal_choice = choice;
    reportConfig_present = true;
    return 0;
}

std::string ReportConfigToAddMod::reportConfig_ChoiceToString(reportConfig_Enum value) const
{
    if(k_reportConfig_reportConfigEUTRA == value)
        return "reportConfig_reportConfigEUTRA";
    if(k_reportConfig_reportConfigInterRAT == value)
        return "reportConfig_reportConfigInterRAT";
    return "";
}

uint64_t ReportConfigToAddMod::reportConfig_NumberOfChoices() const
{
    return 2;
}

std::string ReportConfigToAddMod::reportConfig_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "reportConfig = " + reportConfig_ChoiceToString(reportConfig_internal_choice) + ":\n";
    if(reportConfig_internal_choice == k_reportConfig_reportConfigEUTRA)
        out += reportConfig_reportConfigEUTRA.ToString(indent+1);
    if(reportConfig_internal_choice == k_reportConfig_reportConfigInterRAT)
        out += reportConfig_reportConfigInterRAT.ToString(indent+1);
    return out;
}

std::string ReportConfigToAddMod::reportConfig_ToStringNoNewLines() const
{
    std::string out = "reportConfig=" + reportConfig_ChoiceToString(reportConfig_internal_choice) + ",";
    if(reportConfig_internal_choice == k_reportConfig_reportConfigEUTRA)
        out += reportConfig_reportConfigEUTRA.ToStringNoNewLines();
    if(reportConfig_internal_choice == k_reportConfig_reportConfigInterRAT)
        out += reportConfig_reportConfigInterRAT.ToStringNoNewLines();
    return out;
}

int ReportConfigToAddMod::reportConfig_Clear()
{
    reportConfig_present = false;
    return 0;
}

bool ReportConfigToAddMod::reportConfig_IsPresent() const
{
    return reportConfig_present;
}

ReportConfigEUTRA* ReportConfigToAddMod::reportConfig_reportConfigEUTRA_Set()
{
    reportConfig_reportConfigEUTRA_present = true;
    return &reportConfig_reportConfigEUTRA;
}

int ReportConfigToAddMod::reportConfig_reportConfigEUTRA_Set(ReportConfigEUTRA &value)
{
    reportConfig_reportConfigEUTRA_present = true;
    reportConfig_reportConfigEUTRA = value;
    return 0;
}

const ReportConfigEUTRA& ReportConfigToAddMod::reportConfig_reportConfigEUTRA_Get() const
{
    return reportConfig_reportConfigEUTRA;
}

std::string ReportConfigToAddMod::reportConfig_reportConfigEUTRA_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "reportConfigEUTRA:\n";
    out += reportConfig_reportConfigEUTRA.ToString(indent+1);
    return out;
}

std::string ReportConfigToAddMod::reportConfig_reportConfigEUTRA_ToStringNoNewLines() const
{
    std::string out = "reportConfigEUTRA:";
    out += reportConfig_reportConfigEUTRA.ToStringNoNewLines();
    return out;
}

int ReportConfigToAddMod::reportConfig_reportConfigEUTRA_Clear()
{
    reportConfig_reportConfigEUTRA_present = false;
    return 0;
}

bool ReportConfigToAddMod::reportConfig_reportConfigEUTRA_IsPresent() const
{
    return reportConfig_reportConfigEUTRA_present;
}

ReportConfigInterRAT* ReportConfigToAddMod::reportConfig_reportConfigInterRAT_Set()
{
    reportConfig_reportConfigInterRAT_present = true;
    return &reportConfig_reportConfigInterRAT;
}

int ReportConfigToAddMod::reportConfig_reportConfigInterRAT_Set(ReportConfigInterRAT &value)
{
    reportConfig_reportConfigInterRAT_present = true;
    reportConfig_reportConfigInterRAT = value;
    return 0;
}

const ReportConfigInterRAT& ReportConfigToAddMod::reportConfig_reportConfigInterRAT_Get() const
{
    return reportConfig_reportConfigInterRAT;
}

std::string ReportConfigToAddMod::reportConfig_reportConfigInterRAT_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "reportConfigInterRAT:\n";
    out += reportConfig_reportConfigInterRAT.ToString(indent+1);
    return out;
}

std::string ReportConfigToAddMod::reportConfig_reportConfigInterRAT_ToStringNoNewLines() const
{
    std::string out = "reportConfigInterRAT:";
    out += reportConfig_reportConfigInterRAT.ToStringNoNewLines();
    return out;
}

int ReportConfigToAddMod::reportConfig_reportConfigInterRAT_Clear()
{
    reportConfig_reportConfigInterRAT_present = false;
    return 0;
}

bool ReportConfigToAddMod::reportConfig_reportConfigInterRAT_IsPresent() const
{
    return reportConfig_reportConfigInterRAT_present;
}

