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

#include "SystemInformationBlockType1_v920_IEs.h"

#include <cmath>

int SystemInformationBlockType1_v920_IEs::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(ims_EmergencySupport_r9_IsPresent());
    bits.push_back(cellSelectionInfo_v920_IsPresent());
    bits.push_back(0);

    // Fields
    if(ims_EmergencySupport_r9_IsPresent())
    {
        if(0 != ims_EmergencySupport_r9_Pack(bits))
        {
            printf("SystemInformationBlockType1_v920_IEs:: field pack failure\n");
            return -1;
        }
    }
    if(cellSelectionInfo_v920_IsPresent())
    {
        if(0 != cellSelectionInfo_v920.Pack(bits))
        {
            printf("SystemInformationBlockType1_v920_IEs:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int SystemInformationBlockType1_v920_IEs::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int SystemInformationBlockType1_v920_IEs::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("SystemInformationBlockType1_v920_IEs::Unpack() index out of bounds for optional indiator ims_EmergencySupport_r9\n");
        return -1;
    }
    ims_EmergencySupport_r9_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("SystemInformationBlockType1_v920_IEs::Unpack() index out of bounds for optional indiator cellSelectionInfo_v920\n");
        return -1;
    }
    cellSelectionInfo_v920_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("SystemInformationBlockType1_v920_IEs::Unpack() index out of bounds for optional indiator nonCriticalExtension\n");
        return -1;
    }
    idx++;

    // Fields
    if(ims_EmergencySupport_r9_present)
    {
        if(0 != ims_EmergencySupport_r9_Unpack(bits, idx))
        {
            printf("SystemInformationBlockType1_v920_IEs:: field unpack failure\n");
            return -1;
        }
    }
    if(cellSelectionInfo_v920_present)
    {
        if(0 != cellSelectionInfo_v920.Unpack(bits, idx))
        {
            printf("SystemInformationBlockType1_v920_IEs:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string SystemInformationBlockType1_v920_IEs::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "SystemInformationBlockType1_v920_IEs:\n";
    if(ims_EmergencySupport_r9_IsPresent())
        out += ims_EmergencySupport_r9_ToString(indent+1);
    if(cellSelectionInfo_v920_IsPresent())
        out += cellSelectionInfo_v920_ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType1_v920_IEs::ToStringNoNewLines() const
{
    std::string out = "SystemInformationBlockType1_v920_IEs:";
    if(ims_EmergencySupport_r9_IsPresent())
        out += ims_EmergencySupport_r9_ToStringNoNewLines();
    if(cellSelectionInfo_v920_IsPresent())
        out += cellSelectionInfo_v920_ToStringNoNewLines();
    return out;
}

int SystemInformationBlockType1_v920_IEs::ims_EmergencySupport_r9_Pack(std::vector<uint8_t> &bits)
{
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((ims_EmergencySupport_r9_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int SystemInformationBlockType1_v920_IEs::ims_EmergencySupport_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return ims_EmergencySupport_r9_Unpack(bits, idx);
}

int SystemInformationBlockType1_v920_IEs::ims_EmergencySupport_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("SystemInformationBlockType1_v920_IEs::ims_EmergencySupport_r9_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 0)
    {
        printf("SystemInformationBlockType1_v920_IEs::ims_EmergencySupport_r9_Unpack() max failure\n");
        return -1;
    }
    ims_EmergencySupport_r9_internal_value = (ims_EmergencySupport_r9_Enum)packed_val;
    ims_EmergencySupport_r9_present = true;
    return 0;
}

SystemInformationBlockType1_v920_IEs::ims_EmergencySupport_r9_Enum SystemInformationBlockType1_v920_IEs::ims_EmergencySupport_r9_Value() const
{
    if(ims_EmergencySupport_r9_present)
        return ims_EmergencySupport_r9_internal_value;
    return (SystemInformationBlockType1_v920_IEs::ims_EmergencySupport_r9_Enum)0;
}

int SystemInformationBlockType1_v920_IEs::ims_EmergencySupport_r9_SetValue(ims_EmergencySupport_r9_Enum value)
{
    ims_EmergencySupport_r9_internal_value = value;
    ims_EmergencySupport_r9_present = true;
    return 0;
}

int SystemInformationBlockType1_v920_IEs::ims_EmergencySupport_r9_SetValue(std::string value)
{
    if("true" == value)
    {
        ims_EmergencySupport_r9_internal_value = k_ims_EmergencySupport_r9_true;
        ims_EmergencySupport_r9_present = true;
        return 0;
    }
    return 1;
}

std::string SystemInformationBlockType1_v920_IEs::ims_EmergencySupport_r9_ValueToString(ims_EmergencySupport_r9_Enum value) const
{
    if(k_ims_EmergencySupport_r9_true == value)
        return "true";
    return "";
}

uint64_t SystemInformationBlockType1_v920_IEs::ims_EmergencySupport_r9_NumberOfValues() const
{
    return 1;
}

std::string SystemInformationBlockType1_v920_IEs::ims_EmergencySupport_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ims_EmergencySupport_r9 = " + ims_EmergencySupport_r9_ValueToString(ims_EmergencySupport_r9_internal_value) + "\n";
    return out;
}

std::string SystemInformationBlockType1_v920_IEs::ims_EmergencySupport_r9_ToStringNoNewLines() const
{
    std::string out = "ims_EmergencySupport_r9=" + ims_EmergencySupport_r9_ValueToString(ims_EmergencySupport_r9_internal_value) + ",";
    return out;
}

int SystemInformationBlockType1_v920_IEs::ims_EmergencySupport_r9_Clear()
{
    ims_EmergencySupport_r9_present = false;
    return 0;
}

bool SystemInformationBlockType1_v920_IEs::ims_EmergencySupport_r9_IsPresent() const
{
    return ims_EmergencySupport_r9_present;
}

CellSelectionInfo_v920* SystemInformationBlockType1_v920_IEs::cellSelectionInfo_v920_Set()
{
    cellSelectionInfo_v920_present = true;
    return &cellSelectionInfo_v920;
}

int SystemInformationBlockType1_v920_IEs::cellSelectionInfo_v920_Set(CellSelectionInfo_v920 &value)
{
    cellSelectionInfo_v920_present = true;
    cellSelectionInfo_v920 = value;
    return 0;
}

const CellSelectionInfo_v920& SystemInformationBlockType1_v920_IEs::cellSelectionInfo_v920_Get() const
{
    return cellSelectionInfo_v920;
}

std::string SystemInformationBlockType1_v920_IEs::cellSelectionInfo_v920_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cellSelectionInfo_v920:\n";
    out += cellSelectionInfo_v920.ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType1_v920_IEs::cellSelectionInfo_v920_ToStringNoNewLines() const
{
    std::string out = "cellSelectionInfo_v920:";
    out += cellSelectionInfo_v920.ToStringNoNewLines();
    return out;
}

int SystemInformationBlockType1_v920_IEs::cellSelectionInfo_v920_Clear()
{
    cellSelectionInfo_v920_present = false;
    return 0;
}

bool SystemInformationBlockType1_v920_IEs::cellSelectionInfo_v920_IsPresent() const
{
    return cellSelectionInfo_v920_present;
}

