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

#include "SCellToAddMod_r10.h"

#include <cmath>

int SCellToAddMod_r10::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator
    bits.push_back(0);

    // Optional indicators
    bits.push_back(cellIdentification_value.IsPresent());
    bits.push_back(radioResourceConfigCommon_r10_IsPresent());
    bits.push_back(radioResourceConfigDedicated_r10_IsPresent());

    // Fields
    {
        if(0 != sCellIndex_r10.Pack(bits))
        {
            printf("SCellToAddMod_r10:: field pack failure\n");
            return -1;
        }
    }
    if(cellIdentification_value.IsPresent())
    {
        if(0 != cellIdentification_value.Pack(bits))
        {
            printf("SCellToAddMod_r10:: field pack failure\n");
            return -1;
        }
    }
    if(radioResourceConfigCommon_r10_IsPresent())
    {
        if(0 != radioResourceConfigCommon_r10.Pack(bits))
        {
            printf("SCellToAddMod_r10:: field pack failure\n");
            return -1;
        }
    }
    if(radioResourceConfigDedicated_r10_IsPresent())
    {
        if(0 != radioResourceConfigDedicated_r10.Pack(bits))
        {
            printf("SCellToAddMod_r10:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int SCellToAddMod_r10::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int SCellToAddMod_r10::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("SCellToAddMod_r10::Unpack() index out of bounds for extension\n");
        return -1;
    }
    idx++;

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("SCellToAddMod_r10::Unpack() index out of bounds for optional indiator cellIdentification\n");
        return -1;
    }
    cellIdentification_value.SetPresence(bits[idx++]);
    if((idx + 1) > bits.size())
    {
        printf("SCellToAddMod_r10::Unpack() index out of bounds for optional indiator radioResourceConfigCommon_r10\n");
        return -1;
    }
    radioResourceConfigCommon_r10_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("SCellToAddMod_r10::Unpack() index out of bounds for optional indiator radioResourceConfigDedicated_r10\n");
        return -1;
    }
    radioResourceConfigDedicated_r10_present = bits[idx++];

    // Fields
    {
        if(0 != sCellIndex_r10.Unpack(bits, idx))
        {
            printf("SCellToAddMod_r10:: field unpack failure\n");
            return -1;
        }
    }
    if(cellIdentification_value.IsPresent())
    {
        if(0 != cellIdentification_value.Unpack(bits, idx))
        {
            printf("SCellToAddMod_r10:: field unpack failure\n");
            return -1;
        }
    }
    if(radioResourceConfigCommon_r10_present)
    {
        if(0 != radioResourceConfigCommon_r10.Unpack(bits, idx))
        {
            printf("SCellToAddMod_r10:: field unpack failure\n");
            return -1;
        }
    }
    if(radioResourceConfigDedicated_r10_present)
    {
        if(0 != radioResourceConfigDedicated_r10.Unpack(bits, idx))
        {
            printf("SCellToAddMod_r10:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string SCellToAddMod_r10::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "SCellToAddMod_r10:\n";
    out += sCellIndex_r10_ToString(indent+1);
    if(cellIdentification_value.IsPresent())
        out += cellIdentification_value.ToString(indent+1);
    if(radioResourceConfigCommon_r10_IsPresent())
        out += radioResourceConfigCommon_r10_ToString(indent+1);
    if(radioResourceConfigDedicated_r10_IsPresent())
        out += radioResourceConfigDedicated_r10_ToString(indent+1);
    return out;
}

std::string SCellToAddMod_r10::ToStringNoNewLines() const
{
    std::string out = "SCellToAddMod_r10:";
    out += sCellIndex_r10_ToStringNoNewLines();
    if(cellIdentification_value.IsPresent())
        out += cellIdentification_value.ToStringNoNewLines();
    if(radioResourceConfigCommon_r10_IsPresent())
        out += radioResourceConfigCommon_r10_ToStringNoNewLines();
    if(radioResourceConfigDedicated_r10_IsPresent())
        out += radioResourceConfigDedicated_r10_ToStringNoNewLines();
    return out;
}

SCellIndex_r10* SCellToAddMod_r10::sCellIndex_r10_Set()
{
    sCellIndex_r10_present = true;
    return &sCellIndex_r10;
}

int SCellToAddMod_r10::sCellIndex_r10_Set(SCellIndex_r10 &value)
{
    sCellIndex_r10_present = true;
    sCellIndex_r10 = value;
    return 0;
}

const SCellIndex_r10& SCellToAddMod_r10::sCellIndex_r10_Get() const
{
    return sCellIndex_r10;
}

std::string SCellToAddMod_r10::sCellIndex_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "sCellIndex_r10:\n";
    out += sCellIndex_r10.ToString(indent+1);
    return out;
}

std::string SCellToAddMod_r10::sCellIndex_r10_ToStringNoNewLines() const
{
    std::string out = "sCellIndex_r10:";
    out += sCellIndex_r10.ToStringNoNewLines();
    return out;
}

int SCellToAddMod_r10::sCellIndex_r10_Clear()
{
    sCellIndex_r10_present = false;
    return 0;
}

bool SCellToAddMod_r10::sCellIndex_r10_IsPresent() const
{
    return sCellIndex_r10_present;
}

int SCellToAddMod_r10::cellIdentification::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != physCellId_r10.Pack(bits))
        {
            printf("SCellToAddMod_r10::cellIdentification:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != dl_CarrierFreq.Pack(bits))
        {
            printf("SCellToAddMod_r10::cellIdentification:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int SCellToAddMod_r10::cellIdentification::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int SCellToAddMod_r10::cellIdentification::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != physCellId_r10.Unpack(bits, idx))
        {
            printf("SCellToAddMod_r10::cellIdentification:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != dl_CarrierFreq.Unpack(bits, idx))
        {
            printf("SCellToAddMod_r10::cellIdentification:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string SCellToAddMod_r10::cellIdentification::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cellIdentification:\n";
    out += physCellId_r10_ToString(indent+1);
    out += dl_CarrierFreq_ToString(indent+1);
    return out;
}

std::string SCellToAddMod_r10::cellIdentification::ToStringNoNewLines() const
{
    std::string out = "cellIdentification:";
    out += physCellId_r10_ToStringNoNewLines();
    out += dl_CarrierFreq_ToStringNoNewLines();
    return out;
}

int SCellToAddMod_r10::cellIdentification::Set()
{
    present = true;
    return 0;
}

int SCellToAddMod_r10::cellIdentification::SetPresence(bool is_present)
{
    present = is_present;
    return 0;
}

int SCellToAddMod_r10::cellIdentification::Clear()
{
    present = false;
    return 0;
}

bool SCellToAddMod_r10::cellIdentification::IsPresent() const
{
    return present;
}

PhysCellId* SCellToAddMod_r10::cellIdentification::physCellId_r10_Set()
{
    physCellId_r10_present = true;
    return &physCellId_r10;
}

int SCellToAddMod_r10::cellIdentification::physCellId_r10_Set(PhysCellId &value)
{
    physCellId_r10_present = true;
    physCellId_r10 = value;
    return 0;
}

const PhysCellId& SCellToAddMod_r10::cellIdentification::physCellId_r10_Get() const
{
    return physCellId_r10;
}

std::string SCellToAddMod_r10::cellIdentification::physCellId_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "physCellId_r10:\n";
    out += physCellId_r10.ToString(indent+1);
    return out;
}

std::string SCellToAddMod_r10::cellIdentification::physCellId_r10_ToStringNoNewLines() const
{
    std::string out = "physCellId_r10:";
    out += physCellId_r10.ToStringNoNewLines();
    return out;
}

int SCellToAddMod_r10::cellIdentification::physCellId_r10_Clear()
{
    physCellId_r10_present = false;
    return 0;
}

bool SCellToAddMod_r10::cellIdentification::physCellId_r10_IsPresent() const
{
    return physCellId_r10_present;
}

ARFCN_ValueEUTRA* SCellToAddMod_r10::cellIdentification::dl_CarrierFreq_Set()
{
    dl_CarrierFreq_present = true;
    return &dl_CarrierFreq;
}

int SCellToAddMod_r10::cellIdentification::dl_CarrierFreq_Set(ARFCN_ValueEUTRA &value)
{
    dl_CarrierFreq_present = true;
    dl_CarrierFreq = value;
    return 0;
}

const ARFCN_ValueEUTRA& SCellToAddMod_r10::cellIdentification::dl_CarrierFreq_Get() const
{
    return dl_CarrierFreq;
}

std::string SCellToAddMod_r10::cellIdentification::dl_CarrierFreq_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "dl_CarrierFreq:\n";
    out += dl_CarrierFreq.ToString(indent+1);
    return out;
}

std::string SCellToAddMod_r10::cellIdentification::dl_CarrierFreq_ToStringNoNewLines() const
{
    std::string out = "dl_CarrierFreq:";
    out += dl_CarrierFreq.ToStringNoNewLines();
    return out;
}

int SCellToAddMod_r10::cellIdentification::dl_CarrierFreq_Clear()
{
    dl_CarrierFreq_present = false;
    return 0;
}

bool SCellToAddMod_r10::cellIdentification::dl_CarrierFreq_IsPresent() const
{
    return dl_CarrierFreq_present;
}

RadioResourceConfigCommonSCell_r10* SCellToAddMod_r10::radioResourceConfigCommon_r10_Set()
{
    radioResourceConfigCommon_r10_present = true;
    return &radioResourceConfigCommon_r10;
}

int SCellToAddMod_r10::radioResourceConfigCommon_r10_Set(RadioResourceConfigCommonSCell_r10 &value)
{
    radioResourceConfigCommon_r10_present = true;
    radioResourceConfigCommon_r10 = value;
    return 0;
}

const RadioResourceConfigCommonSCell_r10& SCellToAddMod_r10::radioResourceConfigCommon_r10_Get() const
{
    return radioResourceConfigCommon_r10;
}

std::string SCellToAddMod_r10::radioResourceConfigCommon_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "radioResourceConfigCommon_r10:\n";
    out += radioResourceConfigCommon_r10.ToString(indent+1);
    return out;
}

std::string SCellToAddMod_r10::radioResourceConfigCommon_r10_ToStringNoNewLines() const
{
    std::string out = "radioResourceConfigCommon_r10:";
    out += radioResourceConfigCommon_r10.ToStringNoNewLines();
    return out;
}

int SCellToAddMod_r10::radioResourceConfigCommon_r10_Clear()
{
    radioResourceConfigCommon_r10_present = false;
    return 0;
}

bool SCellToAddMod_r10::radioResourceConfigCommon_r10_IsPresent() const
{
    return radioResourceConfigCommon_r10_present;
}

RadioResourceConfigDedicatedSCell_r10* SCellToAddMod_r10::radioResourceConfigDedicated_r10_Set()
{
    radioResourceConfigDedicated_r10_present = true;
    return &radioResourceConfigDedicated_r10;
}

int SCellToAddMod_r10::radioResourceConfigDedicated_r10_Set(RadioResourceConfigDedicatedSCell_r10 &value)
{
    radioResourceConfigDedicated_r10_present = true;
    radioResourceConfigDedicated_r10 = value;
    return 0;
}

const RadioResourceConfigDedicatedSCell_r10& SCellToAddMod_r10::radioResourceConfigDedicated_r10_Get() const
{
    return radioResourceConfigDedicated_r10;
}

std::string SCellToAddMod_r10::radioResourceConfigDedicated_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "radioResourceConfigDedicated_r10:\n";
    out += radioResourceConfigDedicated_r10.ToString(indent+1);
    return out;
}

std::string SCellToAddMod_r10::radioResourceConfigDedicated_r10_ToStringNoNewLines() const
{
    std::string out = "radioResourceConfigDedicated_r10:";
    out += radioResourceConfigDedicated_r10.ToStringNoNewLines();
    return out;
}

int SCellToAddMod_r10::radioResourceConfigDedicated_r10_Clear()
{
    radioResourceConfigDedicated_r10_present = false;
    return 0;
}

bool SCellToAddMod_r10::radioResourceConfigDedicated_r10_IsPresent() const
{
    return radioResourceConfigDedicated_r10_present;
}

