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

#include "CellChangeOrder.h"

#include <cmath>

int CellChangeOrder::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != t304_Pack(bits))
        {
            printf("CellChangeOrder:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != targetRAT_Type_Pack(bits))
        {
            printf("CellChangeOrder:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int CellChangeOrder::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int CellChangeOrder::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != t304_Unpack(bits, idx))
        {
            printf("CellChangeOrder:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != targetRAT_Type_Unpack(bits, idx))
        {
            printf("CellChangeOrder:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string CellChangeOrder::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "CellChangeOrder:\n";
    out += t304_ToString(indent+1);
    out += targetRAT_Type_ToString(indent+1);
    return out;
}

std::string CellChangeOrder::ToStringNoNewLines() const
{
    std::string out = "CellChangeOrder:";
    out += t304_ToStringNoNewLines();
    out += targetRAT_Type_ToStringNoNewLines();
    return out;
}

int CellChangeOrder::t304_Pack(std::vector<uint8_t> &bits)
{
    if(!t304_present)
    {
        printf("CellChangeOrder::t304_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 3;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((t304_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int CellChangeOrder::t304_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return t304_Unpack(bits, idx);
}

int CellChangeOrder::t304_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 3;
    if((idx + N_bits) > bits.size())
    {
        printf("CellChangeOrder::t304_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 7)
    {
        printf("CellChangeOrder::t304_Unpack() max failure\n");
        return -1;
    }
    t304_internal_value = (t304_Enum)packed_val;
    t304_present = true;
    return 0;
}

CellChangeOrder::t304_Enum CellChangeOrder::t304_Value() const
{
    if(t304_present)
        return t304_internal_value;
    return (CellChangeOrder::t304_Enum)0;
}

int CellChangeOrder::t304_SetValue(t304_Enum value)
{
    t304_internal_value = value;
    t304_present = true;
    return 0;
}

int CellChangeOrder::t304_SetValue(std::string value)
{
    if("ms100" == value)
    {
        t304_internal_value = k_t304_ms100;
        t304_present = true;
        return 0;
    }
    if("ms200" == value)
    {
        t304_internal_value = k_t304_ms200;
        t304_present = true;
        return 0;
    }
    if("ms500" == value)
    {
        t304_internal_value = k_t304_ms500;
        t304_present = true;
        return 0;
    }
    if("ms1000" == value)
    {
        t304_internal_value = k_t304_ms1000;
        t304_present = true;
        return 0;
    }
    if("ms2000" == value)
    {
        t304_internal_value = k_t304_ms2000;
        t304_present = true;
        return 0;
    }
    if("ms4000" == value)
    {
        t304_internal_value = k_t304_ms4000;
        t304_present = true;
        return 0;
    }
    if("ms8000" == value)
    {
        t304_internal_value = k_t304_ms8000;
        t304_present = true;
        return 0;
    }
    if("spare1" == value)
    {
        t304_internal_value = k_t304_spare1;
        t304_present = true;
        return 0;
    }
    return 1;
}

std::string CellChangeOrder::t304_ValueToString(t304_Enum value) const
{
    if(k_t304_ms100 == value)
        return "ms100";
    if(k_t304_ms200 == value)
        return "ms200";
    if(k_t304_ms500 == value)
        return "ms500";
    if(k_t304_ms1000 == value)
        return "ms1000";
    if(k_t304_ms2000 == value)
        return "ms2000";
    if(k_t304_ms4000 == value)
        return "ms4000";
    if(k_t304_ms8000 == value)
        return "ms8000";
    if(k_t304_spare1 == value)
        return "spare1";
    return "";
}

uint64_t CellChangeOrder::t304_NumberOfValues() const
{
    return 8;
}

std::string CellChangeOrder::t304_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "t304 = " + t304_ValueToString(t304_internal_value) + "\n";
    return out;
}

std::string CellChangeOrder::t304_ToStringNoNewLines() const
{
    std::string out = "t304=" + t304_ValueToString(t304_internal_value) + ",";
    return out;
}

int CellChangeOrder::t304_Clear()
{
    t304_present = false;
    return 0;
}

bool CellChangeOrder::t304_IsPresent() const
{
    return t304_present;
}

int CellChangeOrder::targetRAT_Type_Pack(std::vector<uint8_t> &bits)
{
    if(!targetRAT_Type_present)
    {
        printf("CellChangeOrder::targetRAT_Type_Pack() presence failure\n");
        return -1;
    }
    // Extension indicator
    bits.push_back(0);

    // Choice

    // Fields
    if(targetRAT_Type_internal_choice == k_targetRAT_Type_geran)
    {
        if(0 != targetRAT_Type_geran_value.Pack(bits))
        {
            printf("CellChangeOrder::targetRAT_Type_geran pack failure\n");
            return -1;
        }
    }
    return 0;
}

int CellChangeOrder::targetRAT_Type_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return targetRAT_Type_Unpack(bits, idx);
}

int CellChangeOrder::targetRAT_Type_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("CellChangeOrder::targetRAT_Type_Unpack() index out of bounds for extension\n");
        return -1;
    }
    idx++;

    // Choice
    targetRAT_Type_internal_choice = (CellChangeOrder::targetRAT_Type_Enum)0;
    targetRAT_Type_present = true;

    // Fields
    if(targetRAT_Type_internal_choice == k_targetRAT_Type_geran)
    {
        if(0 != targetRAT_Type_geran_value.Unpack(bits, idx))
        {
            printf("CellChangeOrder::targetRAT_Type_geran unpack failure\n");
            return -1;
        }
    }
    return 0;
}

CellChangeOrder::targetRAT_Type_Enum CellChangeOrder::targetRAT_Type_Choice() const
{
    if(targetRAT_Type_present)
        return targetRAT_Type_internal_choice;
    return (CellChangeOrder::targetRAT_Type_Enum)0;
}

int CellChangeOrder::targetRAT_Type_SetChoice(CellChangeOrder::targetRAT_Type_Enum choice)
{
    targetRAT_Type_internal_choice = choice;
    targetRAT_Type_present = true;
    return 0;
}

std::string CellChangeOrder::targetRAT_Type_ChoiceToString(targetRAT_Type_Enum value) const
{
    if(k_targetRAT_Type_geran == value)
        return "targetRAT_Type_geran";
    return "";
}

uint64_t CellChangeOrder::targetRAT_Type_NumberOfChoices() const
{
    return 1;
}

std::string CellChangeOrder::targetRAT_Type_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "targetRAT_Type = " + targetRAT_Type_ChoiceToString(targetRAT_Type_internal_choice) + ":\n";
    if(targetRAT_Type_internal_choice == k_targetRAT_Type_geran)
        out += targetRAT_Type_geran_value.ToString(indent+1);
    return out;
}

std::string CellChangeOrder::targetRAT_Type_ToStringNoNewLines() const
{
    std::string out = "targetRAT_Type=" + targetRAT_Type_ChoiceToString(targetRAT_Type_internal_choice) + ",";
    if(targetRAT_Type_internal_choice == k_targetRAT_Type_geran)
        out += targetRAT_Type_geran_value.ToStringNoNewLines();
    return out;
}

int CellChangeOrder::targetRAT_Type_Clear()
{
    targetRAT_Type_present = false;
    return 0;
}

bool CellChangeOrder::targetRAT_Type_IsPresent() const
{
    return targetRAT_Type_present;
}

int CellChangeOrder::targetRAT_Type_geran::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(networkControlOrder_IsPresent());
    bits.push_back(systemInformation_IsPresent());

    // Fields
    {
        if(0 != physCellId.Pack(bits))
        {
            printf("CellChangeOrder::targetRAT_Type_geran:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != carrierFreq.Pack(bits))
        {
            printf("CellChangeOrder::targetRAT_Type_geran:: field pack failure\n");
            return -1;
        }
    }
    if(networkControlOrder_IsPresent())
    {
        if(0 != networkControlOrder_Pack(bits))
        {
            printf("CellChangeOrder::targetRAT_Type_geran:: field pack failure\n");
            return -1;
        }
    }
    if(systemInformation_IsPresent())
    {
        if(0 != systemInformation.Pack(bits))
        {
            printf("CellChangeOrder::targetRAT_Type_geran:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int CellChangeOrder::targetRAT_Type_geran::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int CellChangeOrder::targetRAT_Type_geran::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("targetRAT_Type_geran::Unpack() index out of bounds for optional indiator networkControlOrder\n");
        return -1;
    }
    networkControlOrder_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("targetRAT_Type_geran::Unpack() index out of bounds for optional indiator systemInformation\n");
        return -1;
    }
    systemInformation_present = bits[idx++];

    // Fields
    {
        if(0 != physCellId.Unpack(bits, idx))
        {
            printf("CellChangeOrder::targetRAT_Type_geran:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != carrierFreq.Unpack(bits, idx))
        {
            printf("CellChangeOrder::targetRAT_Type_geran:: field unpack failure\n");
            return -1;
        }
    }
    if(networkControlOrder_present)
    {
        if(0 != networkControlOrder_Unpack(bits, idx))
        {
            printf("CellChangeOrder::targetRAT_Type_geran:: field unpack failure\n");
            return -1;
        }
    }
    if(systemInformation_present)
    {
        if(0 != systemInformation.Unpack(bits, idx))
        {
            printf("CellChangeOrder::targetRAT_Type_geran:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string CellChangeOrder::targetRAT_Type_geran::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "geran:\n";
    out += physCellId_ToString(indent+1);
    out += carrierFreq_ToString(indent+1);
    if(networkControlOrder_IsPresent())
        out += networkControlOrder_ToString(indent+1);
    if(systemInformation_IsPresent())
        out += systemInformation_ToString(indent+1);
    return out;
}

std::string CellChangeOrder::targetRAT_Type_geran::ToStringNoNewLines() const
{
    std::string out = "geran:";
    out += physCellId_ToStringNoNewLines();
    out += carrierFreq_ToStringNoNewLines();
    if(networkControlOrder_IsPresent())
        out += networkControlOrder_ToStringNoNewLines();
    if(systemInformation_IsPresent())
        out += systemInformation_ToStringNoNewLines();
    return out;
}

PhysCellIdGERAN* CellChangeOrder::targetRAT_Type_geran::physCellId_Set()
{
    physCellId_present = true;
    return &physCellId;
}

int CellChangeOrder::targetRAT_Type_geran::physCellId_Set(PhysCellIdGERAN &value)
{
    physCellId_present = true;
    physCellId = value;
    return 0;
}

const PhysCellIdGERAN& CellChangeOrder::targetRAT_Type_geran::physCellId_Get() const
{
    return physCellId;
}

std::string CellChangeOrder::targetRAT_Type_geran::physCellId_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "physCellId:\n";
    out += physCellId.ToString(indent+1);
    return out;
}

std::string CellChangeOrder::targetRAT_Type_geran::physCellId_ToStringNoNewLines() const
{
    std::string out = "physCellId:";
    out += physCellId.ToStringNoNewLines();
    return out;
}

int CellChangeOrder::targetRAT_Type_geran::physCellId_Clear()
{
    physCellId_present = false;
    return 0;
}

bool CellChangeOrder::targetRAT_Type_geran::physCellId_IsPresent() const
{
    return physCellId_present;
}

CarrierFreqGERAN* CellChangeOrder::targetRAT_Type_geran::carrierFreq_Set()
{
    carrierFreq_present = true;
    return &carrierFreq;
}

int CellChangeOrder::targetRAT_Type_geran::carrierFreq_Set(CarrierFreqGERAN &value)
{
    carrierFreq_present = true;
    carrierFreq = value;
    return 0;
}

const CarrierFreqGERAN& CellChangeOrder::targetRAT_Type_geran::carrierFreq_Get() const
{
    return carrierFreq;
}

std::string CellChangeOrder::targetRAT_Type_geran::carrierFreq_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "carrierFreq:\n";
    out += carrierFreq.ToString(indent+1);
    return out;
}

std::string CellChangeOrder::targetRAT_Type_geran::carrierFreq_ToStringNoNewLines() const
{
    std::string out = "carrierFreq:";
    out += carrierFreq.ToStringNoNewLines();
    return out;
}

int CellChangeOrder::targetRAT_Type_geran::carrierFreq_Clear()
{
    carrierFreq_present = false;
    return 0;
}

bool CellChangeOrder::targetRAT_Type_geran::carrierFreq_IsPresent() const
{
    return carrierFreq_present;
}

int CellChangeOrder::targetRAT_Type_geran::networkControlOrder_Pack(std::vector<uint8_t> &bits)
{
    uint32_t size = 2;
    if(size < 2 || size > 2)
    {
        printf("CellChangeOrder::targetRAT_Type_geran::networkControlOrder_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((networkControlOrder_internal_value >> (2-i-1)) & 1);
    return 0;
}

int CellChangeOrder::targetRAT_Type_geran::networkControlOrder_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return networkControlOrder_Unpack(bits, idx);
}

int CellChangeOrder::targetRAT_Type_geran::networkControlOrder_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 2;
    if(size < 2 || size > 2)
    {
        printf("CellChangeOrder::targetRAT_Type_geran::networkControlOrder_Unpack() size failure\n");
        return -1;
    }
    networkControlOrder_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("CellChangeOrder::targetRAT_Type_geran::networkControlOrder_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        networkControlOrder_internal_value |= (uint8_t)bits[idx++] << (uint8_t)(2-i-1);
    networkControlOrder_present = true;
    return 0;
}

uint8_t CellChangeOrder::targetRAT_Type_geran::networkControlOrder_Value() const
{
    if(networkControlOrder_present)
        return networkControlOrder_internal_value;
    uint8_t tmp = 0;
    return tmp;
}

int CellChangeOrder::targetRAT_Type_geran::networkControlOrder_SetValue(uint8_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 2)
    {
        printf("CellChangeOrder::targetRAT_Type_geran::networkControlOrder_SetValue() size failure\n");
        return -1;
    }
    networkControlOrder_internal_value = value;
    networkControlOrder_present = true;
    return 0;
}

std::string CellChangeOrder::targetRAT_Type_geran::networkControlOrder_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "networkControlOrder = ";
    out += std::to_string(networkControlOrder_internal_value);
    out += "\n";
    return out;
}

std::string CellChangeOrder::targetRAT_Type_geran::networkControlOrder_ToStringNoNewLines() const
{
    std::string out = "networkControlOrder=";
    out += std::to_string(networkControlOrder_internal_value);
    out += ",";
    return out;
}

int CellChangeOrder::targetRAT_Type_geran::networkControlOrder_Clear()
{
    networkControlOrder_present = false;
    return 0;
}

bool CellChangeOrder::targetRAT_Type_geran::networkControlOrder_IsPresent() const
{
    return networkControlOrder_present;
}

SI_OrPSI_GERAN* CellChangeOrder::targetRAT_Type_geran::systemInformation_Set()
{
    systemInformation_present = true;
    return &systemInformation;
}

int CellChangeOrder::targetRAT_Type_geran::systemInformation_Set(SI_OrPSI_GERAN &value)
{
    systemInformation_present = true;
    systemInformation = value;
    return 0;
}

const SI_OrPSI_GERAN& CellChangeOrder::targetRAT_Type_geran::systemInformation_Get() const
{
    return systemInformation;
}

std::string CellChangeOrder::targetRAT_Type_geran::systemInformation_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "systemInformation:\n";
    out += systemInformation.ToString(indent+1);
    return out;
}

std::string CellChangeOrder::targetRAT_Type_geran::systemInformation_ToStringNoNewLines() const
{
    std::string out = "systemInformation:";
    out += systemInformation.ToStringNoNewLines();
    return out;
}

int CellChangeOrder::targetRAT_Type_geran::systemInformation_Clear()
{
    systemInformation_present = false;
    return 0;
}

bool CellChangeOrder::targetRAT_Type_geran::systemInformation_IsPresent() const
{
    return systemInformation_present;
}

