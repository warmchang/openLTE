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

#include "PhyLayerParameters.h"

#include <cmath>

int PhyLayerParameters::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != ue_TxAntennaSelectionSupported_Pack(bits))
        {
            printf("PhyLayerParameters:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != ue_SpecificRefSigsSupported_Pack(bits))
        {
            printf("PhyLayerParameters:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int PhyLayerParameters::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int PhyLayerParameters::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != ue_TxAntennaSelectionSupported_Unpack(bits, idx))
        {
            printf("PhyLayerParameters:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != ue_SpecificRefSigsSupported_Unpack(bits, idx))
        {
            printf("PhyLayerParameters:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string PhyLayerParameters::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "PhyLayerParameters:\n";
    out += ue_TxAntennaSelectionSupported_ToString(indent+1);
    out += ue_SpecificRefSigsSupported_ToString(indent+1);
    return out;
}

std::string PhyLayerParameters::ToStringNoNewLines() const
{
    std::string out = "PhyLayerParameters:";
    out += ue_TxAntennaSelectionSupported_ToStringNoNewLines();
    out += ue_SpecificRefSigsSupported_ToStringNoNewLines();
    return out;
}

int PhyLayerParameters::ue_TxAntennaSelectionSupported_Pack(std::vector<uint8_t> &bits)
{
    if(!ue_TxAntennaSelectionSupported_present)
    {
        printf("PhyLayerParameters::ue_TxAntennaSelectionSupported_Pack() presence failure\n");
        return -1;
    }
    bits.push_back(ue_TxAntennaSelectionSupported_internal_value);
    return 0;
}

int PhyLayerParameters::ue_TxAntennaSelectionSupported_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return ue_TxAntennaSelectionSupported_Unpack(bits, idx);
}

int PhyLayerParameters::ue_TxAntennaSelectionSupported_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    if((idx + 1) > bits.size())
    {
        printf("PhyLayerParameters::ue_TxAntennaSelectionSupported_Unpack() index out of bounds\n");
        return -1;
    }
    ue_TxAntennaSelectionSupported_internal_value = bits[idx++];
    ue_TxAntennaSelectionSupported_present = true;
    return 0;
}

bool PhyLayerParameters::ue_TxAntennaSelectionSupported_Value() const
{
    if(ue_TxAntennaSelectionSupported_present)
        return ue_TxAntennaSelectionSupported_internal_value;
    return false;
}

int PhyLayerParameters::ue_TxAntennaSelectionSupported_SetValue(bool value)
{
    ue_TxAntennaSelectionSupported_internal_value = value;
    ue_TxAntennaSelectionSupported_present = true;
    return 0;
}

std::string PhyLayerParameters::ue_TxAntennaSelectionSupported_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ue_TxAntennaSelectionSupported = " + std::to_string(ue_TxAntennaSelectionSupported_internal_value) + "\n";
    return out;
}

std::string PhyLayerParameters::ue_TxAntennaSelectionSupported_ToStringNoNewLines() const
{
    std::string out = "ue_TxAntennaSelectionSupported=" + std::to_string(ue_TxAntennaSelectionSupported_internal_value) + ",";
    return out;
}

int PhyLayerParameters::ue_TxAntennaSelectionSupported_Clear()
{
    ue_TxAntennaSelectionSupported_present = false;
    return 0;
}

bool PhyLayerParameters::ue_TxAntennaSelectionSupported_IsPresent() const
{
    return ue_TxAntennaSelectionSupported_present;
}

int PhyLayerParameters::ue_SpecificRefSigsSupported_Pack(std::vector<uint8_t> &bits)
{
    if(!ue_SpecificRefSigsSupported_present)
    {
        printf("PhyLayerParameters::ue_SpecificRefSigsSupported_Pack() presence failure\n");
        return -1;
    }
    bits.push_back(ue_SpecificRefSigsSupported_internal_value);
    return 0;
}

int PhyLayerParameters::ue_SpecificRefSigsSupported_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return ue_SpecificRefSigsSupported_Unpack(bits, idx);
}

int PhyLayerParameters::ue_SpecificRefSigsSupported_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    if((idx + 1) > bits.size())
    {
        printf("PhyLayerParameters::ue_SpecificRefSigsSupported_Unpack() index out of bounds\n");
        return -1;
    }
    ue_SpecificRefSigsSupported_internal_value = bits[idx++];
    ue_SpecificRefSigsSupported_present = true;
    return 0;
}

bool PhyLayerParameters::ue_SpecificRefSigsSupported_Value() const
{
    if(ue_SpecificRefSigsSupported_present)
        return ue_SpecificRefSigsSupported_internal_value;
    return false;
}

int PhyLayerParameters::ue_SpecificRefSigsSupported_SetValue(bool value)
{
    ue_SpecificRefSigsSupported_internal_value = value;
    ue_SpecificRefSigsSupported_present = true;
    return 0;
}

std::string PhyLayerParameters::ue_SpecificRefSigsSupported_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ue_SpecificRefSigsSupported = " + std::to_string(ue_SpecificRefSigsSupported_internal_value) + "\n";
    return out;
}

std::string PhyLayerParameters::ue_SpecificRefSigsSupported_ToStringNoNewLines() const
{
    std::string out = "ue_SpecificRefSigsSupported=" + std::to_string(ue_SpecificRefSigsSupported_internal_value) + ",";
    return out;
}

int PhyLayerParameters::ue_SpecificRefSigsSupported_Clear()
{
    ue_SpecificRefSigsSupported_present = false;
    return 0;
}

bool PhyLayerParameters::ue_SpecificRefSigsSupported_IsPresent() const
{
    return ue_SpecificRefSigsSupported_present;
}

