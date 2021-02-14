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

#include "UE_EUTRA_Capability_v920_IEs.h"

#include <cmath>

int UE_EUTRA_Capability_v920_IEs::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(interRAT_ParametersUTRA_v920_IsPresent());
    bits.push_back(interRAT_ParametersCDMA2000_v920_IsPresent());
    bits.push_back(deviceType_r9_IsPresent());
    bits.push_back(nonCriticalExtension_IsPresent());

    // Fields
    {
        if(0 != phyLayerParameters_v920.Pack(bits))
        {
            printf("UE_EUTRA_Capability_v920_IEs:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != interRAT_ParametersGERAN_v920.Pack(bits))
        {
            printf("UE_EUTRA_Capability_v920_IEs:: field pack failure\n");
            return -1;
        }
    }
    if(interRAT_ParametersUTRA_v920_IsPresent())
    {
        if(0 != interRAT_ParametersUTRA_v920.Pack(bits))
        {
            printf("UE_EUTRA_Capability_v920_IEs:: field pack failure\n");
            return -1;
        }
    }
    if(interRAT_ParametersCDMA2000_v920_IsPresent())
    {
        if(0 != interRAT_ParametersCDMA2000_v920.Pack(bits))
        {
            printf("UE_EUTRA_Capability_v920_IEs:: field pack failure\n");
            return -1;
        }
    }
    if(deviceType_r9_IsPresent())
    {
        if(0 != deviceType_r9_Pack(bits))
        {
            printf("UE_EUTRA_Capability_v920_IEs:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != csg_ProximityIndicationParameters_r9.Pack(bits))
        {
            printf("UE_EUTRA_Capability_v920_IEs:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != neighCellSI_AcquisitionParameters_r9.Pack(bits))
        {
            printf("UE_EUTRA_Capability_v920_IEs:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != son_Parameters_r9.Pack(bits))
        {
            printf("UE_EUTRA_Capability_v920_IEs:: field pack failure\n");
            return -1;
        }
    }
    if(nonCriticalExtension_IsPresent())
    {
        if(0 != nonCriticalExtension.Pack(bits))
        {
            printf("UE_EUTRA_Capability_v920_IEs:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int UE_EUTRA_Capability_v920_IEs::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int UE_EUTRA_Capability_v920_IEs::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("UE_EUTRA_Capability_v920_IEs::Unpack() index out of bounds for optional indiator interRAT_ParametersUTRA_v920\n");
        return -1;
    }
    interRAT_ParametersUTRA_v920_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("UE_EUTRA_Capability_v920_IEs::Unpack() index out of bounds for optional indiator interRAT_ParametersCDMA2000_v920\n");
        return -1;
    }
    interRAT_ParametersCDMA2000_v920_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("UE_EUTRA_Capability_v920_IEs::Unpack() index out of bounds for optional indiator deviceType_r9\n");
        return -1;
    }
    deviceType_r9_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("UE_EUTRA_Capability_v920_IEs::Unpack() index out of bounds for optional indiator nonCriticalExtension\n");
        return -1;
    }
    nonCriticalExtension_present = bits[idx++];

    // Fields
    {
        if(0 != phyLayerParameters_v920.Unpack(bits, idx))
        {
            printf("UE_EUTRA_Capability_v920_IEs:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != interRAT_ParametersGERAN_v920.Unpack(bits, idx))
        {
            printf("UE_EUTRA_Capability_v920_IEs:: field unpack failure\n");
            return -1;
        }
    }
    if(interRAT_ParametersUTRA_v920_present)
    {
        if(0 != interRAT_ParametersUTRA_v920.Unpack(bits, idx))
        {
            printf("UE_EUTRA_Capability_v920_IEs:: field unpack failure\n");
            return -1;
        }
    }
    if(interRAT_ParametersCDMA2000_v920_present)
    {
        if(0 != interRAT_ParametersCDMA2000_v920.Unpack(bits, idx))
        {
            printf("UE_EUTRA_Capability_v920_IEs:: field unpack failure\n");
            return -1;
        }
    }
    if(deviceType_r9_present)
    {
        if(0 != deviceType_r9_Unpack(bits, idx))
        {
            printf("UE_EUTRA_Capability_v920_IEs:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != csg_ProximityIndicationParameters_r9.Unpack(bits, idx))
        {
            printf("UE_EUTRA_Capability_v920_IEs:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != neighCellSI_AcquisitionParameters_r9.Unpack(bits, idx))
        {
            printf("UE_EUTRA_Capability_v920_IEs:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != son_Parameters_r9.Unpack(bits, idx))
        {
            printf("UE_EUTRA_Capability_v920_IEs:: field unpack failure\n");
            return -1;
        }
    }
    if(nonCriticalExtension_present)
    {
        if(0 != nonCriticalExtension.Unpack(bits, idx))
        {
            printf("UE_EUTRA_Capability_v920_IEs:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string UE_EUTRA_Capability_v920_IEs::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "UE_EUTRA_Capability_v920_IEs:\n";
    out += phyLayerParameters_v920_ToString(indent+1);
    out += interRAT_ParametersGERAN_v920_ToString(indent+1);
    if(interRAT_ParametersUTRA_v920_IsPresent())
        out += interRAT_ParametersUTRA_v920_ToString(indent+1);
    if(interRAT_ParametersCDMA2000_v920_IsPresent())
        out += interRAT_ParametersCDMA2000_v920_ToString(indent+1);
    if(deviceType_r9_IsPresent())
        out += deviceType_r9_ToString(indent+1);
    out += csg_ProximityIndicationParameters_r9_ToString(indent+1);
    out += neighCellSI_AcquisitionParameters_r9_ToString(indent+1);
    out += son_Parameters_r9_ToString(indent+1);
    if(nonCriticalExtension_IsPresent())
        out += nonCriticalExtension_ToString(indent+1);
    return out;
}

std::string UE_EUTRA_Capability_v920_IEs::ToStringNoNewLines() const
{
    std::string out = "UE_EUTRA_Capability_v920_IEs:";
    out += phyLayerParameters_v920_ToStringNoNewLines();
    out += interRAT_ParametersGERAN_v920_ToStringNoNewLines();
    if(interRAT_ParametersUTRA_v920_IsPresent())
        out += interRAT_ParametersUTRA_v920_ToStringNoNewLines();
    if(interRAT_ParametersCDMA2000_v920_IsPresent())
        out += interRAT_ParametersCDMA2000_v920_ToStringNoNewLines();
    if(deviceType_r9_IsPresent())
        out += deviceType_r9_ToStringNoNewLines();
    out += csg_ProximityIndicationParameters_r9_ToStringNoNewLines();
    out += neighCellSI_AcquisitionParameters_r9_ToStringNoNewLines();
    out += son_Parameters_r9_ToStringNoNewLines();
    if(nonCriticalExtension_IsPresent())
        out += nonCriticalExtension_ToStringNoNewLines();
    return out;
}

PhyLayerParameters_v920* UE_EUTRA_Capability_v920_IEs::phyLayerParameters_v920_Set()
{
    phyLayerParameters_v920_present = true;
    return &phyLayerParameters_v920;
}

int UE_EUTRA_Capability_v920_IEs::phyLayerParameters_v920_Set(PhyLayerParameters_v920 &value)
{
    phyLayerParameters_v920_present = true;
    phyLayerParameters_v920 = value;
    return 0;
}

const PhyLayerParameters_v920& UE_EUTRA_Capability_v920_IEs::phyLayerParameters_v920_Get() const
{
    return phyLayerParameters_v920;
}

std::string UE_EUTRA_Capability_v920_IEs::phyLayerParameters_v920_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "phyLayerParameters_v920:\n";
    out += phyLayerParameters_v920.ToString(indent+1);
    return out;
}

std::string UE_EUTRA_Capability_v920_IEs::phyLayerParameters_v920_ToStringNoNewLines() const
{
    std::string out = "phyLayerParameters_v920:";
    out += phyLayerParameters_v920.ToStringNoNewLines();
    return out;
}

int UE_EUTRA_Capability_v920_IEs::phyLayerParameters_v920_Clear()
{
    phyLayerParameters_v920_present = false;
    return 0;
}

bool UE_EUTRA_Capability_v920_IEs::phyLayerParameters_v920_IsPresent() const
{
    return phyLayerParameters_v920_present;
}

IRAT_ParametersGERAN_v920* UE_EUTRA_Capability_v920_IEs::interRAT_ParametersGERAN_v920_Set()
{
    interRAT_ParametersGERAN_v920_present = true;
    return &interRAT_ParametersGERAN_v920;
}

int UE_EUTRA_Capability_v920_IEs::interRAT_ParametersGERAN_v920_Set(IRAT_ParametersGERAN_v920 &value)
{
    interRAT_ParametersGERAN_v920_present = true;
    interRAT_ParametersGERAN_v920 = value;
    return 0;
}

const IRAT_ParametersGERAN_v920& UE_EUTRA_Capability_v920_IEs::interRAT_ParametersGERAN_v920_Get() const
{
    return interRAT_ParametersGERAN_v920;
}

std::string UE_EUTRA_Capability_v920_IEs::interRAT_ParametersGERAN_v920_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "interRAT_ParametersGERAN_v920:\n";
    out += interRAT_ParametersGERAN_v920.ToString(indent+1);
    return out;
}

std::string UE_EUTRA_Capability_v920_IEs::interRAT_ParametersGERAN_v920_ToStringNoNewLines() const
{
    std::string out = "interRAT_ParametersGERAN_v920:";
    out += interRAT_ParametersGERAN_v920.ToStringNoNewLines();
    return out;
}

int UE_EUTRA_Capability_v920_IEs::interRAT_ParametersGERAN_v920_Clear()
{
    interRAT_ParametersGERAN_v920_present = false;
    return 0;
}

bool UE_EUTRA_Capability_v920_IEs::interRAT_ParametersGERAN_v920_IsPresent() const
{
    return interRAT_ParametersGERAN_v920_present;
}

IRAT_ParametersUTRA_v920* UE_EUTRA_Capability_v920_IEs::interRAT_ParametersUTRA_v920_Set()
{
    interRAT_ParametersUTRA_v920_present = true;
    return &interRAT_ParametersUTRA_v920;
}

int UE_EUTRA_Capability_v920_IEs::interRAT_ParametersUTRA_v920_Set(IRAT_ParametersUTRA_v920 &value)
{
    interRAT_ParametersUTRA_v920_present = true;
    interRAT_ParametersUTRA_v920 = value;
    return 0;
}

const IRAT_ParametersUTRA_v920& UE_EUTRA_Capability_v920_IEs::interRAT_ParametersUTRA_v920_Get() const
{
    return interRAT_ParametersUTRA_v920;
}

std::string UE_EUTRA_Capability_v920_IEs::interRAT_ParametersUTRA_v920_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "interRAT_ParametersUTRA_v920:\n";
    out += interRAT_ParametersUTRA_v920.ToString(indent+1);
    return out;
}

std::string UE_EUTRA_Capability_v920_IEs::interRAT_ParametersUTRA_v920_ToStringNoNewLines() const
{
    std::string out = "interRAT_ParametersUTRA_v920:";
    out += interRAT_ParametersUTRA_v920.ToStringNoNewLines();
    return out;
}

int UE_EUTRA_Capability_v920_IEs::interRAT_ParametersUTRA_v920_Clear()
{
    interRAT_ParametersUTRA_v920_present = false;
    return 0;
}

bool UE_EUTRA_Capability_v920_IEs::interRAT_ParametersUTRA_v920_IsPresent() const
{
    return interRAT_ParametersUTRA_v920_present;
}

IRAT_ParametersCDMA2000_1XRTT_v920* UE_EUTRA_Capability_v920_IEs::interRAT_ParametersCDMA2000_v920_Set()
{
    interRAT_ParametersCDMA2000_v920_present = true;
    return &interRAT_ParametersCDMA2000_v920;
}

int UE_EUTRA_Capability_v920_IEs::interRAT_ParametersCDMA2000_v920_Set(IRAT_ParametersCDMA2000_1XRTT_v920 &value)
{
    interRAT_ParametersCDMA2000_v920_present = true;
    interRAT_ParametersCDMA2000_v920 = value;
    return 0;
}

const IRAT_ParametersCDMA2000_1XRTT_v920& UE_EUTRA_Capability_v920_IEs::interRAT_ParametersCDMA2000_v920_Get() const
{
    return interRAT_ParametersCDMA2000_v920;
}

std::string UE_EUTRA_Capability_v920_IEs::interRAT_ParametersCDMA2000_v920_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "interRAT_ParametersCDMA2000_v920:\n";
    out += interRAT_ParametersCDMA2000_v920.ToString(indent+1);
    return out;
}

std::string UE_EUTRA_Capability_v920_IEs::interRAT_ParametersCDMA2000_v920_ToStringNoNewLines() const
{
    std::string out = "interRAT_ParametersCDMA2000_v920:";
    out += interRAT_ParametersCDMA2000_v920.ToStringNoNewLines();
    return out;
}

int UE_EUTRA_Capability_v920_IEs::interRAT_ParametersCDMA2000_v920_Clear()
{
    interRAT_ParametersCDMA2000_v920_present = false;
    return 0;
}

bool UE_EUTRA_Capability_v920_IEs::interRAT_ParametersCDMA2000_v920_IsPresent() const
{
    return interRAT_ParametersCDMA2000_v920_present;
}

int UE_EUTRA_Capability_v920_IEs::deviceType_r9_Pack(std::vector<uint8_t> &bits)
{
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((deviceType_r9_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int UE_EUTRA_Capability_v920_IEs::deviceType_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return deviceType_r9_Unpack(bits, idx);
}

int UE_EUTRA_Capability_v920_IEs::deviceType_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("UE_EUTRA_Capability_v920_IEs::deviceType_r9_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 0)
    {
        printf("UE_EUTRA_Capability_v920_IEs::deviceType_r9_Unpack() max failure\n");
        return -1;
    }
    deviceType_r9_internal_value = (deviceType_r9_Enum)packed_val;
    deviceType_r9_present = true;
    return 0;
}

UE_EUTRA_Capability_v920_IEs::deviceType_r9_Enum UE_EUTRA_Capability_v920_IEs::deviceType_r9_Value() const
{
    if(deviceType_r9_present)
        return deviceType_r9_internal_value;
    return (UE_EUTRA_Capability_v920_IEs::deviceType_r9_Enum)0;
}

int UE_EUTRA_Capability_v920_IEs::deviceType_r9_SetValue(deviceType_r9_Enum value)
{
    deviceType_r9_internal_value = value;
    deviceType_r9_present = true;
    return 0;
}

int UE_EUTRA_Capability_v920_IEs::deviceType_r9_SetValue(std::string value)
{
    if("noBenFromBatConsumpOpt" == value)
    {
        deviceType_r9_internal_value = k_deviceType_r9_noBenFromBatConsumpOpt;
        deviceType_r9_present = true;
        return 0;
    }
    return 1;
}

std::string UE_EUTRA_Capability_v920_IEs::deviceType_r9_ValueToString(deviceType_r9_Enum value) const
{
    if(k_deviceType_r9_noBenFromBatConsumpOpt == value)
        return "noBenFromBatConsumpOpt";
    return "";
}

uint64_t UE_EUTRA_Capability_v920_IEs::deviceType_r9_NumberOfValues() const
{
    return 1;
}

std::string UE_EUTRA_Capability_v920_IEs::deviceType_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "deviceType_r9 = " + deviceType_r9_ValueToString(deviceType_r9_internal_value) + "\n";
    return out;
}

std::string UE_EUTRA_Capability_v920_IEs::deviceType_r9_ToStringNoNewLines() const
{
    std::string out = "deviceType_r9=" + deviceType_r9_ValueToString(deviceType_r9_internal_value) + ",";
    return out;
}

int UE_EUTRA_Capability_v920_IEs::deviceType_r9_Clear()
{
    deviceType_r9_present = false;
    return 0;
}

bool UE_EUTRA_Capability_v920_IEs::deviceType_r9_IsPresent() const
{
    return deviceType_r9_present;
}

CSG_ProximityIndicationParameters_r9* UE_EUTRA_Capability_v920_IEs::csg_ProximityIndicationParameters_r9_Set()
{
    csg_ProximityIndicationParameters_r9_present = true;
    return &csg_ProximityIndicationParameters_r9;
}

int UE_EUTRA_Capability_v920_IEs::csg_ProximityIndicationParameters_r9_Set(CSG_ProximityIndicationParameters_r9 &value)
{
    csg_ProximityIndicationParameters_r9_present = true;
    csg_ProximityIndicationParameters_r9 = value;
    return 0;
}

const CSG_ProximityIndicationParameters_r9& UE_EUTRA_Capability_v920_IEs::csg_ProximityIndicationParameters_r9_Get() const
{
    return csg_ProximityIndicationParameters_r9;
}

std::string UE_EUTRA_Capability_v920_IEs::csg_ProximityIndicationParameters_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "csg_ProximityIndicationParameters_r9:\n";
    out += csg_ProximityIndicationParameters_r9.ToString(indent+1);
    return out;
}

std::string UE_EUTRA_Capability_v920_IEs::csg_ProximityIndicationParameters_r9_ToStringNoNewLines() const
{
    std::string out = "csg_ProximityIndicationParameters_r9:";
    out += csg_ProximityIndicationParameters_r9.ToStringNoNewLines();
    return out;
}

int UE_EUTRA_Capability_v920_IEs::csg_ProximityIndicationParameters_r9_Clear()
{
    csg_ProximityIndicationParameters_r9_present = false;
    return 0;
}

bool UE_EUTRA_Capability_v920_IEs::csg_ProximityIndicationParameters_r9_IsPresent() const
{
    return csg_ProximityIndicationParameters_r9_present;
}

NeighCellSI_AcquisitionParameters_r9* UE_EUTRA_Capability_v920_IEs::neighCellSI_AcquisitionParameters_r9_Set()
{
    neighCellSI_AcquisitionParameters_r9_present = true;
    return &neighCellSI_AcquisitionParameters_r9;
}

int UE_EUTRA_Capability_v920_IEs::neighCellSI_AcquisitionParameters_r9_Set(NeighCellSI_AcquisitionParameters_r9 &value)
{
    neighCellSI_AcquisitionParameters_r9_present = true;
    neighCellSI_AcquisitionParameters_r9 = value;
    return 0;
}

const NeighCellSI_AcquisitionParameters_r9& UE_EUTRA_Capability_v920_IEs::neighCellSI_AcquisitionParameters_r9_Get() const
{
    return neighCellSI_AcquisitionParameters_r9;
}

std::string UE_EUTRA_Capability_v920_IEs::neighCellSI_AcquisitionParameters_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "neighCellSI_AcquisitionParameters_r9:\n";
    out += neighCellSI_AcquisitionParameters_r9.ToString(indent+1);
    return out;
}

std::string UE_EUTRA_Capability_v920_IEs::neighCellSI_AcquisitionParameters_r9_ToStringNoNewLines() const
{
    std::string out = "neighCellSI_AcquisitionParameters_r9:";
    out += neighCellSI_AcquisitionParameters_r9.ToStringNoNewLines();
    return out;
}

int UE_EUTRA_Capability_v920_IEs::neighCellSI_AcquisitionParameters_r9_Clear()
{
    neighCellSI_AcquisitionParameters_r9_present = false;
    return 0;
}

bool UE_EUTRA_Capability_v920_IEs::neighCellSI_AcquisitionParameters_r9_IsPresent() const
{
    return neighCellSI_AcquisitionParameters_r9_present;
}

SON_Parameters_r9* UE_EUTRA_Capability_v920_IEs::son_Parameters_r9_Set()
{
    son_Parameters_r9_present = true;
    return &son_Parameters_r9;
}

int UE_EUTRA_Capability_v920_IEs::son_Parameters_r9_Set(SON_Parameters_r9 &value)
{
    son_Parameters_r9_present = true;
    son_Parameters_r9 = value;
    return 0;
}

const SON_Parameters_r9& UE_EUTRA_Capability_v920_IEs::son_Parameters_r9_Get() const
{
    return son_Parameters_r9;
}

std::string UE_EUTRA_Capability_v920_IEs::son_Parameters_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "son_Parameters_r9:\n";
    out += son_Parameters_r9.ToString(indent+1);
    return out;
}

std::string UE_EUTRA_Capability_v920_IEs::son_Parameters_r9_ToStringNoNewLines() const
{
    std::string out = "son_Parameters_r9:";
    out += son_Parameters_r9.ToStringNoNewLines();
    return out;
}

int UE_EUTRA_Capability_v920_IEs::son_Parameters_r9_Clear()
{
    son_Parameters_r9_present = false;
    return 0;
}

bool UE_EUTRA_Capability_v920_IEs::son_Parameters_r9_IsPresent() const
{
    return son_Parameters_r9_present;
}

UE_EUTRA_Capability_v940_IEs* UE_EUTRA_Capability_v920_IEs::nonCriticalExtension_Set()
{
    nonCriticalExtension_present = true;
    return &nonCriticalExtension;
}

int UE_EUTRA_Capability_v920_IEs::nonCriticalExtension_Set(UE_EUTRA_Capability_v940_IEs &value)
{
    nonCriticalExtension_present = true;
    nonCriticalExtension = value;
    return 0;
}

const UE_EUTRA_Capability_v940_IEs& UE_EUTRA_Capability_v920_IEs::nonCriticalExtension_Get() const
{
    return nonCriticalExtension;
}

std::string UE_EUTRA_Capability_v920_IEs::nonCriticalExtension_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "nonCriticalExtension:\n";
    out += nonCriticalExtension.ToString(indent+1);
    return out;
}

std::string UE_EUTRA_Capability_v920_IEs::nonCriticalExtension_ToStringNoNewLines() const
{
    std::string out = "nonCriticalExtension:";
    out += nonCriticalExtension.ToStringNoNewLines();
    return out;
}

int UE_EUTRA_Capability_v920_IEs::nonCriticalExtension_Clear()
{
    nonCriticalExtension_present = false;
    return 0;
}

bool UE_EUTRA_Capability_v920_IEs::nonCriticalExtension_IsPresent() const
{
    return nonCriticalExtension_present;
}

