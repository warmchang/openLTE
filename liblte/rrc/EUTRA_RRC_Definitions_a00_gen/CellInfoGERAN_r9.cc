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

#include "CellInfoGERAN_r9.h"

#include <cmath>

int CellInfoGERAN_r9::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != physCellId_r9.Pack(bits))
        {
            printf("CellInfoGERAN_r9:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != carrierFreq_r9.Pack(bits))
        {
            printf("CellInfoGERAN_r9:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != systemInformation_r9.Pack(bits))
        {
            printf("CellInfoGERAN_r9:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int CellInfoGERAN_r9::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int CellInfoGERAN_r9::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != physCellId_r9.Unpack(bits, idx))
        {
            printf("CellInfoGERAN_r9:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != carrierFreq_r9.Unpack(bits, idx))
        {
            printf("CellInfoGERAN_r9:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != systemInformation_r9.Unpack(bits, idx))
        {
            printf("CellInfoGERAN_r9:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string CellInfoGERAN_r9::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "CellInfoGERAN_r9:\n";
    out += physCellId_r9_ToString(indent+1);
    out += carrierFreq_r9_ToString(indent+1);
    out += systemInformation_r9_ToString(indent+1);
    return out;
}

std::string CellInfoGERAN_r9::ToStringNoNewLines() const
{
    std::string out = "CellInfoGERAN_r9:";
    out += physCellId_r9_ToStringNoNewLines();
    out += carrierFreq_r9_ToStringNoNewLines();
    out += systemInformation_r9_ToStringNoNewLines();
    return out;
}

PhysCellIdGERAN* CellInfoGERAN_r9::physCellId_r9_Set()
{
    physCellId_r9_present = true;
    return &physCellId_r9;
}

int CellInfoGERAN_r9::physCellId_r9_Set(PhysCellIdGERAN &value)
{
    physCellId_r9_present = true;
    physCellId_r9 = value;
    return 0;
}

const PhysCellIdGERAN& CellInfoGERAN_r9::physCellId_r9_Get() const
{
    return physCellId_r9;
}

std::string CellInfoGERAN_r9::physCellId_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "physCellId_r9:\n";
    out += physCellId_r9.ToString(indent+1);
    return out;
}

std::string CellInfoGERAN_r9::physCellId_r9_ToStringNoNewLines() const
{
    std::string out = "physCellId_r9:";
    out += physCellId_r9.ToStringNoNewLines();
    return out;
}

int CellInfoGERAN_r9::physCellId_r9_Clear()
{
    physCellId_r9_present = false;
    return 0;
}

bool CellInfoGERAN_r9::physCellId_r9_IsPresent() const
{
    return physCellId_r9_present;
}

CarrierFreqGERAN* CellInfoGERAN_r9::carrierFreq_r9_Set()
{
    carrierFreq_r9_present = true;
    return &carrierFreq_r9;
}

int CellInfoGERAN_r9::carrierFreq_r9_Set(CarrierFreqGERAN &value)
{
    carrierFreq_r9_present = true;
    carrierFreq_r9 = value;
    return 0;
}

const CarrierFreqGERAN& CellInfoGERAN_r9::carrierFreq_r9_Get() const
{
    return carrierFreq_r9;
}

std::string CellInfoGERAN_r9::carrierFreq_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "carrierFreq_r9:\n";
    out += carrierFreq_r9.ToString(indent+1);
    return out;
}

std::string CellInfoGERAN_r9::carrierFreq_r9_ToStringNoNewLines() const
{
    std::string out = "carrierFreq_r9:";
    out += carrierFreq_r9.ToStringNoNewLines();
    return out;
}

int CellInfoGERAN_r9::carrierFreq_r9_Clear()
{
    carrierFreq_r9_present = false;
    return 0;
}

bool CellInfoGERAN_r9::carrierFreq_r9_IsPresent() const
{
    return carrierFreq_r9_present;
}

SystemInfoListGERAN* CellInfoGERAN_r9::systemInformation_r9_Set()
{
    systemInformation_r9_present = true;
    return &systemInformation_r9;
}

int CellInfoGERAN_r9::systemInformation_r9_Set(SystemInfoListGERAN &value)
{
    systemInformation_r9_present = true;
    systemInformation_r9 = value;
    return 0;
}

const SystemInfoListGERAN& CellInfoGERAN_r9::systemInformation_r9_Get() const
{
    return systemInformation_r9;
}

std::string CellInfoGERAN_r9::systemInformation_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "systemInformation_r9:\n";
    out += systemInformation_r9.ToString(indent+1);
    return out;
}

std::string CellInfoGERAN_r9::systemInformation_r9_ToStringNoNewLines() const
{
    std::string out = "systemInformation_r9:";
    out += systemInformation_r9.ToStringNoNewLines();
    return out;
}

int CellInfoGERAN_r9::systemInformation_r9_Clear()
{
    systemInformation_r9_present = false;
    return 0;
}

bool CellInfoGERAN_r9::systemInformation_r9_IsPresent() const
{
    return systemInformation_r9_present;
}

