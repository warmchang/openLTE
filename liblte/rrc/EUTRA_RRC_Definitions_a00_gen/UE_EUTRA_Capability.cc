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

#include "UE_EUTRA_Capability.h"

#include <cmath>

int UE_EUTRA_Capability::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(featureGroupIndicators_IsPresent());
    bits.push_back(nonCriticalExtension_IsPresent());

    // Fields
    {
        if(0 != accessStratumRelease.Pack(bits))
        {
            printf("UE_EUTRA_Capability:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != ue_Category_Pack(bits))
        {
            printf("UE_EUTRA_Capability:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != pdcp_Parameters.Pack(bits))
        {
            printf("UE_EUTRA_Capability:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != phyLayerParameters.Pack(bits))
        {
            printf("UE_EUTRA_Capability:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != rf_Parameters.Pack(bits))
        {
            printf("UE_EUTRA_Capability:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != measParameters.Pack(bits))
        {
            printf("UE_EUTRA_Capability:: field pack failure\n");
            return -1;
        }
    }
    if(featureGroupIndicators_IsPresent())
    {
        if(0 != featureGroupIndicators_Pack(bits))
        {
            printf("UE_EUTRA_Capability:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != interRAT_Parameters_value.Pack(bits))
        {
            printf("UE_EUTRA_Capability:: field pack failure\n");
            return -1;
        }
    }
    if(nonCriticalExtension_IsPresent())
    {
        if(0 != nonCriticalExtension.Pack(bits))
        {
            printf("UE_EUTRA_Capability:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int UE_EUTRA_Capability::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int UE_EUTRA_Capability::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("UE_EUTRA_Capability::Unpack() index out of bounds for optional indiator featureGroupIndicators\n");
        return -1;
    }
    featureGroupIndicators_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("UE_EUTRA_Capability::Unpack() index out of bounds for optional indiator nonCriticalExtension\n");
        return -1;
    }
    nonCriticalExtension_present = bits[idx++];

    // Fields
    {
        if(0 != accessStratumRelease.Unpack(bits, idx))
        {
            printf("UE_EUTRA_Capability:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != ue_Category_Unpack(bits, idx))
        {
            printf("UE_EUTRA_Capability:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != pdcp_Parameters.Unpack(bits, idx))
        {
            printf("UE_EUTRA_Capability:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != phyLayerParameters.Unpack(bits, idx))
        {
            printf("UE_EUTRA_Capability:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != rf_Parameters.Unpack(bits, idx))
        {
            printf("UE_EUTRA_Capability:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != measParameters.Unpack(bits, idx))
        {
            printf("UE_EUTRA_Capability:: field unpack failure\n");
            return -1;
        }
    }
    if(featureGroupIndicators_present)
    {
        if(0 != featureGroupIndicators_Unpack(bits, idx))
        {
            printf("UE_EUTRA_Capability:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != interRAT_Parameters_value.Unpack(bits, idx))
        {
            printf("UE_EUTRA_Capability:: field unpack failure\n");
            return -1;
        }
    }
    if(nonCriticalExtension_present)
    {
        if(0 != nonCriticalExtension.Unpack(bits, idx))
        {
            printf("UE_EUTRA_Capability:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string UE_EUTRA_Capability::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "UE_EUTRA_Capability:\n";
    out += accessStratumRelease_ToString(indent+1);
    out += ue_Category_ToString(indent+1);
    out += pdcp_Parameters_ToString(indent+1);
    out += phyLayerParameters_ToString(indent+1);
    out += rf_Parameters_ToString(indent+1);
    out += measParameters_ToString(indent+1);
    if(featureGroupIndicators_IsPresent())
        out += featureGroupIndicators_ToString(indent+1);
    out += interRAT_Parameters_value.ToString(indent+1);
    if(nonCriticalExtension_IsPresent())
        out += nonCriticalExtension_ToString(indent+1);
    return out;
}

std::string UE_EUTRA_Capability::ToStringNoNewLines() const
{
    std::string out = "UE_EUTRA_Capability:";
    out += accessStratumRelease_ToStringNoNewLines();
    out += ue_Category_ToStringNoNewLines();
    out += pdcp_Parameters_ToStringNoNewLines();
    out += phyLayerParameters_ToStringNoNewLines();
    out += rf_Parameters_ToStringNoNewLines();
    out += measParameters_ToStringNoNewLines();
    if(featureGroupIndicators_IsPresent())
        out += featureGroupIndicators_ToStringNoNewLines();
    out += interRAT_Parameters_value.ToStringNoNewLines();
    if(nonCriticalExtension_IsPresent())
        out += nonCriticalExtension_ToStringNoNewLines();
    return out;
}

AccessStratumRelease* UE_EUTRA_Capability::accessStratumRelease_Set()
{
    accessStratumRelease_present = true;
    return &accessStratumRelease;
}

int UE_EUTRA_Capability::accessStratumRelease_Set(AccessStratumRelease &value)
{
    accessStratumRelease_present = true;
    accessStratumRelease = value;
    return 0;
}

const AccessStratumRelease& UE_EUTRA_Capability::accessStratumRelease_Get() const
{
    return accessStratumRelease;
}

std::string UE_EUTRA_Capability::accessStratumRelease_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "accessStratumRelease:\n";
    out += accessStratumRelease.ToString(indent+1);
    return out;
}

std::string UE_EUTRA_Capability::accessStratumRelease_ToStringNoNewLines() const
{
    std::string out = "accessStratumRelease:";
    out += accessStratumRelease.ToStringNoNewLines();
    return out;
}

int UE_EUTRA_Capability::accessStratumRelease_Clear()
{
    accessStratumRelease_present = false;
    return 0;
}

bool UE_EUTRA_Capability::accessStratumRelease_IsPresent() const
{
    return accessStratumRelease_present;
}

int UE_EUTRA_Capability::ue_Category_Pack(std::vector<uint8_t> &bits)
{
    if(!ue_Category_present)
    {
        printf("UE_EUTRA_Capability::ue_Category_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = ue_Category_internal_value - (1);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (5 - 1))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int UE_EUTRA_Capability::ue_Category_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return ue_Category_Unpack(bits, idx);
}

int UE_EUTRA_Capability::ue_Category_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (5 - 1))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("UE_EUTRA_Capability::ue_Category_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    ue_Category_internal_value = packed_val + 1;
    ue_Category_present = true;
    return 0;
}

int64_t UE_EUTRA_Capability::ue_Category_Value() const
{
    if(ue_Category_present)
        return ue_Category_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int UE_EUTRA_Capability::ue_Category_SetValue(int64_t value)
{
    if(value < 1 || value > 5)
    {
        printf("UE_EUTRA_Capability::ue_Category_SetValue() range failure\n");
        return -1;
    }
    ue_Category_internal_value = value;
    ue_Category_present = true;
    return 0;
}

std::string UE_EUTRA_Capability::ue_Category_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ue_Category = " + std::to_string(ue_Category_internal_value) + "\n";
    return out;
}

std::string UE_EUTRA_Capability::ue_Category_ToStringNoNewLines() const
{
    std::string out = "ue_Category=" + std::to_string(ue_Category_internal_value) + ",";
    return out;
}

int UE_EUTRA_Capability::ue_Category_Clear()
{
    ue_Category_present = false;
    return 0;
}

bool UE_EUTRA_Capability::ue_Category_IsPresent() const
{
    return ue_Category_present;
}

PDCP_Parameters* UE_EUTRA_Capability::pdcp_Parameters_Set()
{
    pdcp_Parameters_present = true;
    return &pdcp_Parameters;
}

int UE_EUTRA_Capability::pdcp_Parameters_Set(PDCP_Parameters &value)
{
    pdcp_Parameters_present = true;
    pdcp_Parameters = value;
    return 0;
}

const PDCP_Parameters& UE_EUTRA_Capability::pdcp_Parameters_Get() const
{
    return pdcp_Parameters;
}

std::string UE_EUTRA_Capability::pdcp_Parameters_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "pdcp_Parameters:\n";
    out += pdcp_Parameters.ToString(indent+1);
    return out;
}

std::string UE_EUTRA_Capability::pdcp_Parameters_ToStringNoNewLines() const
{
    std::string out = "pdcp_Parameters:";
    out += pdcp_Parameters.ToStringNoNewLines();
    return out;
}

int UE_EUTRA_Capability::pdcp_Parameters_Clear()
{
    pdcp_Parameters_present = false;
    return 0;
}

bool UE_EUTRA_Capability::pdcp_Parameters_IsPresent() const
{
    return pdcp_Parameters_present;
}

PhyLayerParameters* UE_EUTRA_Capability::phyLayerParameters_Set()
{
    phyLayerParameters_present = true;
    return &phyLayerParameters;
}

int UE_EUTRA_Capability::phyLayerParameters_Set(PhyLayerParameters &value)
{
    phyLayerParameters_present = true;
    phyLayerParameters = value;
    return 0;
}

const PhyLayerParameters& UE_EUTRA_Capability::phyLayerParameters_Get() const
{
    return phyLayerParameters;
}

std::string UE_EUTRA_Capability::phyLayerParameters_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "phyLayerParameters:\n";
    out += phyLayerParameters.ToString(indent+1);
    return out;
}

std::string UE_EUTRA_Capability::phyLayerParameters_ToStringNoNewLines() const
{
    std::string out = "phyLayerParameters:";
    out += phyLayerParameters.ToStringNoNewLines();
    return out;
}

int UE_EUTRA_Capability::phyLayerParameters_Clear()
{
    phyLayerParameters_present = false;
    return 0;
}

bool UE_EUTRA_Capability::phyLayerParameters_IsPresent() const
{
    return phyLayerParameters_present;
}

RF_Parameters* UE_EUTRA_Capability::rf_Parameters_Set()
{
    rf_Parameters_present = true;
    return &rf_Parameters;
}

int UE_EUTRA_Capability::rf_Parameters_Set(RF_Parameters &value)
{
    rf_Parameters_present = true;
    rf_Parameters = value;
    return 0;
}

const RF_Parameters& UE_EUTRA_Capability::rf_Parameters_Get() const
{
    return rf_Parameters;
}

std::string UE_EUTRA_Capability::rf_Parameters_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "rf_Parameters:\n";
    out += rf_Parameters.ToString(indent+1);
    return out;
}

std::string UE_EUTRA_Capability::rf_Parameters_ToStringNoNewLines() const
{
    std::string out = "rf_Parameters:";
    out += rf_Parameters.ToStringNoNewLines();
    return out;
}

int UE_EUTRA_Capability::rf_Parameters_Clear()
{
    rf_Parameters_present = false;
    return 0;
}

bool UE_EUTRA_Capability::rf_Parameters_IsPresent() const
{
    return rf_Parameters_present;
}

MeasParameters* UE_EUTRA_Capability::measParameters_Set()
{
    measParameters_present = true;
    return &measParameters;
}

int UE_EUTRA_Capability::measParameters_Set(MeasParameters &value)
{
    measParameters_present = true;
    measParameters = value;
    return 0;
}

const MeasParameters& UE_EUTRA_Capability::measParameters_Get() const
{
    return measParameters;
}

std::string UE_EUTRA_Capability::measParameters_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "measParameters:\n";
    out += measParameters.ToString(indent+1);
    return out;
}

std::string UE_EUTRA_Capability::measParameters_ToStringNoNewLines() const
{
    std::string out = "measParameters:";
    out += measParameters.ToStringNoNewLines();
    return out;
}

int UE_EUTRA_Capability::measParameters_Clear()
{
    measParameters_present = false;
    return 0;
}

bool UE_EUTRA_Capability::measParameters_IsPresent() const
{
    return measParameters_present;
}

int UE_EUTRA_Capability::featureGroupIndicators_Pack(std::vector<uint8_t> &bits)
{
    uint32_t size = 32;
    if(size < 32 || size > 32)
    {
        printf("UE_EUTRA_Capability::featureGroupIndicators_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((featureGroupIndicators_internal_value >> (32-i-1)) & 1);
    return 0;
}

int UE_EUTRA_Capability::featureGroupIndicators_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return featureGroupIndicators_Unpack(bits, idx);
}

int UE_EUTRA_Capability::featureGroupIndicators_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 32;
    if(size < 32 || size > 32)
    {
        printf("UE_EUTRA_Capability::featureGroupIndicators_Unpack() size failure\n");
        return -1;
    }
    featureGroupIndicators_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("UE_EUTRA_Capability::featureGroupIndicators_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        featureGroupIndicators_internal_value |= (uint32_t)bits[idx++] << (uint32_t)(32-i-1);
    featureGroupIndicators_present = true;
    return 0;
}

uint32_t UE_EUTRA_Capability::featureGroupIndicators_Value() const
{
    if(featureGroupIndicators_present)
        return featureGroupIndicators_internal_value;
    uint32_t tmp = 0;
    return tmp;
}

int UE_EUTRA_Capability::featureGroupIndicators_SetValue(uint32_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 32)
    {
        printf("UE_EUTRA_Capability::featureGroupIndicators_SetValue() size failure\n");
        return -1;
    }
    featureGroupIndicators_internal_value = value;
    featureGroupIndicators_present = true;
    return 0;
}

std::string UE_EUTRA_Capability::featureGroupIndicators_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "featureGroupIndicators = ";
    out += std::to_string(featureGroupIndicators_internal_value);
    out += "\n";
    return out;
}

std::string UE_EUTRA_Capability::featureGroupIndicators_ToStringNoNewLines() const
{
    std::string out = "featureGroupIndicators=";
    out += std::to_string(featureGroupIndicators_internal_value);
    out += ",";
    return out;
}

int UE_EUTRA_Capability::featureGroupIndicators_Clear()
{
    featureGroupIndicators_present = false;
    return 0;
}

bool UE_EUTRA_Capability::featureGroupIndicators_IsPresent() const
{
    return featureGroupIndicators_present;
}

int UE_EUTRA_Capability::interRAT_Parameters::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(utraFDD_IsPresent());
    bits.push_back(utraTDD128_IsPresent());
    bits.push_back(utraTDD384_IsPresent());
    bits.push_back(utraTDD768_IsPresent());
    bits.push_back(geran_IsPresent());
    bits.push_back(cdma2000_HRPD_IsPresent());
    bits.push_back(cdma2000_1xRTT_IsPresent());

    // Fields
    if(utraFDD_IsPresent())
    {
        if(0 != utraFDD.Pack(bits))
        {
            printf("UE_EUTRA_Capability::interRAT_Parameters:: field pack failure\n");
            return -1;
        }
    }
    if(utraTDD128_IsPresent())
    {
        if(0 != utraTDD128.Pack(bits))
        {
            printf("UE_EUTRA_Capability::interRAT_Parameters:: field pack failure\n");
            return -1;
        }
    }
    if(utraTDD384_IsPresent())
    {
        if(0 != utraTDD384.Pack(bits))
        {
            printf("UE_EUTRA_Capability::interRAT_Parameters:: field pack failure\n");
            return -1;
        }
    }
    if(utraTDD768_IsPresent())
    {
        if(0 != utraTDD768.Pack(bits))
        {
            printf("UE_EUTRA_Capability::interRAT_Parameters:: field pack failure\n");
            return -1;
        }
    }
    if(geran_IsPresent())
    {
        if(0 != geran.Pack(bits))
        {
            printf("UE_EUTRA_Capability::interRAT_Parameters:: field pack failure\n");
            return -1;
        }
    }
    if(cdma2000_HRPD_IsPresent())
    {
        if(0 != cdma2000_HRPD.Pack(bits))
        {
            printf("UE_EUTRA_Capability::interRAT_Parameters:: field pack failure\n");
            return -1;
        }
    }
    if(cdma2000_1xRTT_IsPresent())
    {
        if(0 != cdma2000_1xRTT.Pack(bits))
        {
            printf("UE_EUTRA_Capability::interRAT_Parameters:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int UE_EUTRA_Capability::interRAT_Parameters::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int UE_EUTRA_Capability::interRAT_Parameters::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("interRAT_Parameters::Unpack() index out of bounds for optional indiator utraFDD\n");
        return -1;
    }
    utraFDD_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("interRAT_Parameters::Unpack() index out of bounds for optional indiator utraTDD128\n");
        return -1;
    }
    utraTDD128_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("interRAT_Parameters::Unpack() index out of bounds for optional indiator utraTDD384\n");
        return -1;
    }
    utraTDD384_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("interRAT_Parameters::Unpack() index out of bounds for optional indiator utraTDD768\n");
        return -1;
    }
    utraTDD768_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("interRAT_Parameters::Unpack() index out of bounds for optional indiator geran\n");
        return -1;
    }
    geran_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("interRAT_Parameters::Unpack() index out of bounds for optional indiator cdma2000_HRPD\n");
        return -1;
    }
    cdma2000_HRPD_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("interRAT_Parameters::Unpack() index out of bounds for optional indiator cdma2000_1xRTT\n");
        return -1;
    }
    cdma2000_1xRTT_present = bits[idx++];

    // Fields
    if(utraFDD_present)
    {
        if(0 != utraFDD.Unpack(bits, idx))
        {
            printf("UE_EUTRA_Capability::interRAT_Parameters:: field unpack failure\n");
            return -1;
        }
    }
    if(utraTDD128_present)
    {
        if(0 != utraTDD128.Unpack(bits, idx))
        {
            printf("UE_EUTRA_Capability::interRAT_Parameters:: field unpack failure\n");
            return -1;
        }
    }
    if(utraTDD384_present)
    {
        if(0 != utraTDD384.Unpack(bits, idx))
        {
            printf("UE_EUTRA_Capability::interRAT_Parameters:: field unpack failure\n");
            return -1;
        }
    }
    if(utraTDD768_present)
    {
        if(0 != utraTDD768.Unpack(bits, idx))
        {
            printf("UE_EUTRA_Capability::interRAT_Parameters:: field unpack failure\n");
            return -1;
        }
    }
    if(geran_present)
    {
        if(0 != geran.Unpack(bits, idx))
        {
            printf("UE_EUTRA_Capability::interRAT_Parameters:: field unpack failure\n");
            return -1;
        }
    }
    if(cdma2000_HRPD_present)
    {
        if(0 != cdma2000_HRPD.Unpack(bits, idx))
        {
            printf("UE_EUTRA_Capability::interRAT_Parameters:: field unpack failure\n");
            return -1;
        }
    }
    if(cdma2000_1xRTT_present)
    {
        if(0 != cdma2000_1xRTT.Unpack(bits, idx))
        {
            printf("UE_EUTRA_Capability::interRAT_Parameters:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string UE_EUTRA_Capability::interRAT_Parameters::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "interRAT_Parameters:\n";
    if(utraFDD_IsPresent())
        out += utraFDD_ToString(indent+1);
    if(utraTDD128_IsPresent())
        out += utraTDD128_ToString(indent+1);
    if(utraTDD384_IsPresent())
        out += utraTDD384_ToString(indent+1);
    if(utraTDD768_IsPresent())
        out += utraTDD768_ToString(indent+1);
    if(geran_IsPresent())
        out += geran_ToString(indent+1);
    if(cdma2000_HRPD_IsPresent())
        out += cdma2000_HRPD_ToString(indent+1);
    if(cdma2000_1xRTT_IsPresent())
        out += cdma2000_1xRTT_ToString(indent+1);
    return out;
}

std::string UE_EUTRA_Capability::interRAT_Parameters::ToStringNoNewLines() const
{
    std::string out = "interRAT_Parameters:";
    if(utraFDD_IsPresent())
        out += utraFDD_ToStringNoNewLines();
    if(utraTDD128_IsPresent())
        out += utraTDD128_ToStringNoNewLines();
    if(utraTDD384_IsPresent())
        out += utraTDD384_ToStringNoNewLines();
    if(utraTDD768_IsPresent())
        out += utraTDD768_ToStringNoNewLines();
    if(geran_IsPresent())
        out += geran_ToStringNoNewLines();
    if(cdma2000_HRPD_IsPresent())
        out += cdma2000_HRPD_ToStringNoNewLines();
    if(cdma2000_1xRTT_IsPresent())
        out += cdma2000_1xRTT_ToStringNoNewLines();
    return out;
}

IRAT_ParametersUTRA_FDD* UE_EUTRA_Capability::interRAT_Parameters::utraFDD_Set()
{
    utraFDD_present = true;
    return &utraFDD;
}

int UE_EUTRA_Capability::interRAT_Parameters::utraFDD_Set(IRAT_ParametersUTRA_FDD &value)
{
    utraFDD_present = true;
    utraFDD = value;
    return 0;
}

const IRAT_ParametersUTRA_FDD& UE_EUTRA_Capability::interRAT_Parameters::utraFDD_Get() const
{
    return utraFDD;
}

std::string UE_EUTRA_Capability::interRAT_Parameters::utraFDD_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "utraFDD:\n";
    out += utraFDD.ToString(indent+1);
    return out;
}

std::string UE_EUTRA_Capability::interRAT_Parameters::utraFDD_ToStringNoNewLines() const
{
    std::string out = "utraFDD:";
    out += utraFDD.ToStringNoNewLines();
    return out;
}

int UE_EUTRA_Capability::interRAT_Parameters::utraFDD_Clear()
{
    utraFDD_present = false;
    return 0;
}

bool UE_EUTRA_Capability::interRAT_Parameters::utraFDD_IsPresent() const
{
    return utraFDD_present;
}

IRAT_ParametersUTRA_TDD128* UE_EUTRA_Capability::interRAT_Parameters::utraTDD128_Set()
{
    utraTDD128_present = true;
    return &utraTDD128;
}

int UE_EUTRA_Capability::interRAT_Parameters::utraTDD128_Set(IRAT_ParametersUTRA_TDD128 &value)
{
    utraTDD128_present = true;
    utraTDD128 = value;
    return 0;
}

const IRAT_ParametersUTRA_TDD128& UE_EUTRA_Capability::interRAT_Parameters::utraTDD128_Get() const
{
    return utraTDD128;
}

std::string UE_EUTRA_Capability::interRAT_Parameters::utraTDD128_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "utraTDD128:\n";
    out += utraTDD128.ToString(indent+1);
    return out;
}

std::string UE_EUTRA_Capability::interRAT_Parameters::utraTDD128_ToStringNoNewLines() const
{
    std::string out = "utraTDD128:";
    out += utraTDD128.ToStringNoNewLines();
    return out;
}

int UE_EUTRA_Capability::interRAT_Parameters::utraTDD128_Clear()
{
    utraTDD128_present = false;
    return 0;
}

bool UE_EUTRA_Capability::interRAT_Parameters::utraTDD128_IsPresent() const
{
    return utraTDD128_present;
}

IRAT_ParametersUTRA_TDD384* UE_EUTRA_Capability::interRAT_Parameters::utraTDD384_Set()
{
    utraTDD384_present = true;
    return &utraTDD384;
}

int UE_EUTRA_Capability::interRAT_Parameters::utraTDD384_Set(IRAT_ParametersUTRA_TDD384 &value)
{
    utraTDD384_present = true;
    utraTDD384 = value;
    return 0;
}

const IRAT_ParametersUTRA_TDD384& UE_EUTRA_Capability::interRAT_Parameters::utraTDD384_Get() const
{
    return utraTDD384;
}

std::string UE_EUTRA_Capability::interRAT_Parameters::utraTDD384_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "utraTDD384:\n";
    out += utraTDD384.ToString(indent+1);
    return out;
}

std::string UE_EUTRA_Capability::interRAT_Parameters::utraTDD384_ToStringNoNewLines() const
{
    std::string out = "utraTDD384:";
    out += utraTDD384.ToStringNoNewLines();
    return out;
}

int UE_EUTRA_Capability::interRAT_Parameters::utraTDD384_Clear()
{
    utraTDD384_present = false;
    return 0;
}

bool UE_EUTRA_Capability::interRAT_Parameters::utraTDD384_IsPresent() const
{
    return utraTDD384_present;
}

IRAT_ParametersUTRA_TDD768* UE_EUTRA_Capability::interRAT_Parameters::utraTDD768_Set()
{
    utraTDD768_present = true;
    return &utraTDD768;
}

int UE_EUTRA_Capability::interRAT_Parameters::utraTDD768_Set(IRAT_ParametersUTRA_TDD768 &value)
{
    utraTDD768_present = true;
    utraTDD768 = value;
    return 0;
}

const IRAT_ParametersUTRA_TDD768& UE_EUTRA_Capability::interRAT_Parameters::utraTDD768_Get() const
{
    return utraTDD768;
}

std::string UE_EUTRA_Capability::interRAT_Parameters::utraTDD768_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "utraTDD768:\n";
    out += utraTDD768.ToString(indent+1);
    return out;
}

std::string UE_EUTRA_Capability::interRAT_Parameters::utraTDD768_ToStringNoNewLines() const
{
    std::string out = "utraTDD768:";
    out += utraTDD768.ToStringNoNewLines();
    return out;
}

int UE_EUTRA_Capability::interRAT_Parameters::utraTDD768_Clear()
{
    utraTDD768_present = false;
    return 0;
}

bool UE_EUTRA_Capability::interRAT_Parameters::utraTDD768_IsPresent() const
{
    return utraTDD768_present;
}

IRAT_ParametersGERAN* UE_EUTRA_Capability::interRAT_Parameters::geran_Set()
{
    geran_present = true;
    return &geran;
}

int UE_EUTRA_Capability::interRAT_Parameters::geran_Set(IRAT_ParametersGERAN &value)
{
    geran_present = true;
    geran = value;
    return 0;
}

const IRAT_ParametersGERAN& UE_EUTRA_Capability::interRAT_Parameters::geran_Get() const
{
    return geran;
}

std::string UE_EUTRA_Capability::interRAT_Parameters::geran_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "geran:\n";
    out += geran.ToString(indent+1);
    return out;
}

std::string UE_EUTRA_Capability::interRAT_Parameters::geran_ToStringNoNewLines() const
{
    std::string out = "geran:";
    out += geran.ToStringNoNewLines();
    return out;
}

int UE_EUTRA_Capability::interRAT_Parameters::geran_Clear()
{
    geran_present = false;
    return 0;
}

bool UE_EUTRA_Capability::interRAT_Parameters::geran_IsPresent() const
{
    return geran_present;
}

IRAT_ParametersCDMA2000_HRPD* UE_EUTRA_Capability::interRAT_Parameters::cdma2000_HRPD_Set()
{
    cdma2000_HRPD_present = true;
    return &cdma2000_HRPD;
}

int UE_EUTRA_Capability::interRAT_Parameters::cdma2000_HRPD_Set(IRAT_ParametersCDMA2000_HRPD &value)
{
    cdma2000_HRPD_present = true;
    cdma2000_HRPD = value;
    return 0;
}

const IRAT_ParametersCDMA2000_HRPD& UE_EUTRA_Capability::interRAT_Parameters::cdma2000_HRPD_Get() const
{
    return cdma2000_HRPD;
}

std::string UE_EUTRA_Capability::interRAT_Parameters::cdma2000_HRPD_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cdma2000_HRPD:\n";
    out += cdma2000_HRPD.ToString(indent+1);
    return out;
}

std::string UE_EUTRA_Capability::interRAT_Parameters::cdma2000_HRPD_ToStringNoNewLines() const
{
    std::string out = "cdma2000_HRPD:";
    out += cdma2000_HRPD.ToStringNoNewLines();
    return out;
}

int UE_EUTRA_Capability::interRAT_Parameters::cdma2000_HRPD_Clear()
{
    cdma2000_HRPD_present = false;
    return 0;
}

bool UE_EUTRA_Capability::interRAT_Parameters::cdma2000_HRPD_IsPresent() const
{
    return cdma2000_HRPD_present;
}

IRAT_ParametersCDMA2000_1XRTT* UE_EUTRA_Capability::interRAT_Parameters::cdma2000_1xRTT_Set()
{
    cdma2000_1xRTT_present = true;
    return &cdma2000_1xRTT;
}

int UE_EUTRA_Capability::interRAT_Parameters::cdma2000_1xRTT_Set(IRAT_ParametersCDMA2000_1XRTT &value)
{
    cdma2000_1xRTT_present = true;
    cdma2000_1xRTT = value;
    return 0;
}

const IRAT_ParametersCDMA2000_1XRTT& UE_EUTRA_Capability::interRAT_Parameters::cdma2000_1xRTT_Get() const
{
    return cdma2000_1xRTT;
}

std::string UE_EUTRA_Capability::interRAT_Parameters::cdma2000_1xRTT_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cdma2000_1xRTT:\n";
    out += cdma2000_1xRTT.ToString(indent+1);
    return out;
}

std::string UE_EUTRA_Capability::interRAT_Parameters::cdma2000_1xRTT_ToStringNoNewLines() const
{
    std::string out = "cdma2000_1xRTT:";
    out += cdma2000_1xRTT.ToStringNoNewLines();
    return out;
}

int UE_EUTRA_Capability::interRAT_Parameters::cdma2000_1xRTT_Clear()
{
    cdma2000_1xRTT_present = false;
    return 0;
}

bool UE_EUTRA_Capability::interRAT_Parameters::cdma2000_1xRTT_IsPresent() const
{
    return cdma2000_1xRTT_present;
}

UE_EUTRA_Capability_v920_IEs* UE_EUTRA_Capability::nonCriticalExtension_Set()
{
    nonCriticalExtension_present = true;
    return &nonCriticalExtension;
}

int UE_EUTRA_Capability::nonCriticalExtension_Set(UE_EUTRA_Capability_v920_IEs &value)
{
    nonCriticalExtension_present = true;
    nonCriticalExtension = value;
    return 0;
}

const UE_EUTRA_Capability_v920_IEs& UE_EUTRA_Capability::nonCriticalExtension_Get() const
{
    return nonCriticalExtension;
}

std::string UE_EUTRA_Capability::nonCriticalExtension_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "nonCriticalExtension:\n";
    out += nonCriticalExtension.ToString(indent+1);
    return out;
}

std::string UE_EUTRA_Capability::nonCriticalExtension_ToStringNoNewLines() const
{
    std::string out = "nonCriticalExtension:";
    out += nonCriticalExtension.ToStringNoNewLines();
    return out;
}

int UE_EUTRA_Capability::nonCriticalExtension_Clear()
{
    nonCriticalExtension_present = false;
    return 0;
}

bool UE_EUTRA_Capability::nonCriticalExtension_IsPresent() const
{
    return nonCriticalExtension_present;
}

