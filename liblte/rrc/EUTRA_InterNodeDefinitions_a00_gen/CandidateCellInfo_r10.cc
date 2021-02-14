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

#include "CandidateCellInfo_r10.h"

#include <cmath>

int CandidateCellInfo_r10::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator
    bits.push_back(0);

    // Optional indicators
    bits.push_back(rsrpResult_r10_IsPresent());
    bits.push_back(rsrqResult_r10_IsPresent());

    // Fields
    {
        if(0 != physCellId_r10.Pack(bits))
        {
            printf("CandidateCellInfo_r10:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != dl_CarrierFreq_r10.Pack(bits))
        {
            printf("CandidateCellInfo_r10:: field pack failure\n");
            return -1;
        }
    }
    if(rsrpResult_r10_IsPresent())
    {
        if(0 != rsrpResult_r10.Pack(bits))
        {
            printf("CandidateCellInfo_r10:: field pack failure\n");
            return -1;
        }
    }
    if(rsrqResult_r10_IsPresent())
    {
        if(0 != rsrqResult_r10.Pack(bits))
        {
            printf("CandidateCellInfo_r10:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int CandidateCellInfo_r10::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int CandidateCellInfo_r10::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("CandidateCellInfo_r10::Unpack() index out of bounds for extension\n");
        return -1;
    }
    idx++;

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("CandidateCellInfo_r10::Unpack() index out of bounds for optional indiator rsrpResult_r10\n");
        return -1;
    }
    rsrpResult_r10_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("CandidateCellInfo_r10::Unpack() index out of bounds for optional indiator rsrqResult_r10\n");
        return -1;
    }
    rsrqResult_r10_present = bits[idx++];

    // Fields
    {
        if(0 != physCellId_r10.Unpack(bits, idx))
        {
            printf("CandidateCellInfo_r10:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != dl_CarrierFreq_r10.Unpack(bits, idx))
        {
            printf("CandidateCellInfo_r10:: field unpack failure\n");
            return -1;
        }
    }
    if(rsrpResult_r10_present)
    {
        if(0 != rsrpResult_r10.Unpack(bits, idx))
        {
            printf("CandidateCellInfo_r10:: field unpack failure\n");
            return -1;
        }
    }
    if(rsrqResult_r10_present)
    {
        if(0 != rsrqResult_r10.Unpack(bits, idx))
        {
            printf("CandidateCellInfo_r10:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string CandidateCellInfo_r10::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "CandidateCellInfo_r10:\n";
    out += physCellId_r10_ToString(indent+1);
    out += dl_CarrierFreq_r10_ToString(indent+1);
    if(rsrpResult_r10_IsPresent())
        out += rsrpResult_r10_ToString(indent+1);
    if(rsrqResult_r10_IsPresent())
        out += rsrqResult_r10_ToString(indent+1);
    return out;
}

std::string CandidateCellInfo_r10::ToStringNoNewLines() const
{
    std::string out = "CandidateCellInfo_r10:";
    out += physCellId_r10_ToStringNoNewLines();
    out += dl_CarrierFreq_r10_ToStringNoNewLines();
    if(rsrpResult_r10_IsPresent())
        out += rsrpResult_r10_ToStringNoNewLines();
    if(rsrqResult_r10_IsPresent())
        out += rsrqResult_r10_ToStringNoNewLines();
    return out;
}

PhysCellId* CandidateCellInfo_r10::physCellId_r10_Set()
{
    physCellId_r10_present = true;
    return &physCellId_r10;
}

int CandidateCellInfo_r10::physCellId_r10_Set(PhysCellId &value)
{
    physCellId_r10_present = true;
    physCellId_r10 = value;
    return 0;
}

const PhysCellId& CandidateCellInfo_r10::physCellId_r10_Get() const
{
    return physCellId_r10;
}

std::string CandidateCellInfo_r10::physCellId_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "physCellId_r10:\n";
    out += physCellId_r10.ToString(indent+1);
    return out;
}

std::string CandidateCellInfo_r10::physCellId_r10_ToStringNoNewLines() const
{
    std::string out = "physCellId_r10:";
    out += physCellId_r10.ToStringNoNewLines();
    return out;
}

int CandidateCellInfo_r10::physCellId_r10_Clear()
{
    physCellId_r10_present = false;
    return 0;
}

bool CandidateCellInfo_r10::physCellId_r10_IsPresent() const
{
    return physCellId_r10_present;
}

ARFCN_ValueEUTRA* CandidateCellInfo_r10::dl_CarrierFreq_r10_Set()
{
    dl_CarrierFreq_r10_present = true;
    return &dl_CarrierFreq_r10;
}

int CandidateCellInfo_r10::dl_CarrierFreq_r10_Set(ARFCN_ValueEUTRA &value)
{
    dl_CarrierFreq_r10_present = true;
    dl_CarrierFreq_r10 = value;
    return 0;
}

const ARFCN_ValueEUTRA& CandidateCellInfo_r10::dl_CarrierFreq_r10_Get() const
{
    return dl_CarrierFreq_r10;
}

std::string CandidateCellInfo_r10::dl_CarrierFreq_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "dl_CarrierFreq_r10:\n";
    out += dl_CarrierFreq_r10.ToString(indent+1);
    return out;
}

std::string CandidateCellInfo_r10::dl_CarrierFreq_r10_ToStringNoNewLines() const
{
    std::string out = "dl_CarrierFreq_r10:";
    out += dl_CarrierFreq_r10.ToStringNoNewLines();
    return out;
}

int CandidateCellInfo_r10::dl_CarrierFreq_r10_Clear()
{
    dl_CarrierFreq_r10_present = false;
    return 0;
}

bool CandidateCellInfo_r10::dl_CarrierFreq_r10_IsPresent() const
{
    return dl_CarrierFreq_r10_present;
}

RSRP_Range* CandidateCellInfo_r10::rsrpResult_r10_Set()
{
    rsrpResult_r10_present = true;
    return &rsrpResult_r10;
}

int CandidateCellInfo_r10::rsrpResult_r10_Set(RSRP_Range &value)
{
    rsrpResult_r10_present = true;
    rsrpResult_r10 = value;
    return 0;
}

const RSRP_Range& CandidateCellInfo_r10::rsrpResult_r10_Get() const
{
    return rsrpResult_r10;
}

std::string CandidateCellInfo_r10::rsrpResult_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "rsrpResult_r10:\n";
    out += rsrpResult_r10.ToString(indent+1);
    return out;
}

std::string CandidateCellInfo_r10::rsrpResult_r10_ToStringNoNewLines() const
{
    std::string out = "rsrpResult_r10:";
    out += rsrpResult_r10.ToStringNoNewLines();
    return out;
}

int CandidateCellInfo_r10::rsrpResult_r10_Clear()
{
    rsrpResult_r10_present = false;
    return 0;
}

bool CandidateCellInfo_r10::rsrpResult_r10_IsPresent() const
{
    return rsrpResult_r10_present;
}

RSRQ_Range* CandidateCellInfo_r10::rsrqResult_r10_Set()
{
    rsrqResult_r10_present = true;
    return &rsrqResult_r10;
}

int CandidateCellInfo_r10::rsrqResult_r10_Set(RSRQ_Range &value)
{
    rsrqResult_r10_present = true;
    rsrqResult_r10 = value;
    return 0;
}

const RSRQ_Range& CandidateCellInfo_r10::rsrqResult_r10_Get() const
{
    return rsrqResult_r10;
}

std::string CandidateCellInfo_r10::rsrqResult_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "rsrqResult_r10:\n";
    out += rsrqResult_r10.ToString(indent+1);
    return out;
}

std::string CandidateCellInfo_r10::rsrqResult_r10_ToStringNoNewLines() const
{
    std::string out = "rsrqResult_r10:";
    out += rsrqResult_r10.ToStringNoNewLines();
    return out;
}

int CandidateCellInfo_r10::rsrqResult_r10_Clear()
{
    rsrqResult_r10_present = false;
    return 0;
}

bool CandidateCellInfo_r10::rsrqResult_r10_IsPresent() const
{
    return rsrqResult_r10_present;
}

