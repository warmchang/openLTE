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

#include "MeasResultUTRA.h"

#include <cmath>

int MeasResultUTRA::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(cgi_Info_value.IsPresent());

    // Fields
    {
        if(0 != physCellId_Pack(bits))
        {
            printf("MeasResultUTRA:: field pack failure\n");
            return -1;
        }
    }
    if(cgi_Info_value.IsPresent())
    {
        if(0 != cgi_Info_value.Pack(bits))
        {
            printf("MeasResultUTRA:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != measResult_value.Pack(bits))
        {
            printf("MeasResultUTRA:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int MeasResultUTRA::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int MeasResultUTRA::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("MeasResultUTRA::Unpack() index out of bounds for optional indiator cgi_Info\n");
        return -1;
    }
    cgi_Info_value.SetPresence(bits[idx++]);

    // Fields
    {
        if(0 != physCellId_Unpack(bits, idx))
        {
            printf("MeasResultUTRA:: field unpack failure\n");
            return -1;
        }
    }
    if(cgi_Info_value.IsPresent())
    {
        if(0 != cgi_Info_value.Unpack(bits, idx))
        {
            printf("MeasResultUTRA:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != measResult_value.Unpack(bits, idx))
        {
            printf("MeasResultUTRA:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string MeasResultUTRA::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "MeasResultUTRA:\n";
    out += physCellId_ToString(indent+1);
    if(cgi_Info_value.IsPresent())
        out += cgi_Info_value.ToString(indent+1);
    out += measResult_value.ToString(indent+1);
    return out;
}

std::string MeasResultUTRA::ToStringNoNewLines() const
{
    std::string out = "MeasResultUTRA:";
    out += physCellId_ToStringNoNewLines();
    if(cgi_Info_value.IsPresent())
        out += cgi_Info_value.ToStringNoNewLines();
    out += measResult_value.ToStringNoNewLines();
    return out;
}

int MeasResultUTRA::physCellId_Pack(std::vector<uint8_t> &bits)
{
    if(!physCellId_present)
    {
        printf("MeasResultUTRA::physCellId_Pack() presence failure\n");
        return -1;
    }
    // Extension indicator

    // Choice
    for(uint32_t i=0; i<1; i++)
        bits.push_back((physCellId_internal_choice >> (1-i-1)) & 1);

    // Fields
    if(physCellId_internal_choice == k_physCellId_fdd)
    {
        if(0 != physCellId_fdd.Pack(bits))
        {
            printf("MeasResultUTRA::physCellId_fdd pack failure\n");
            return -1;
        }
    }
    if(physCellId_internal_choice == k_physCellId_tdd)
    {
        if(0 != physCellId_tdd.Pack(bits))
        {
            printf("MeasResultUTRA::physCellId_tdd pack failure\n");
            return -1;
        }
    }
    return 0;
}

int MeasResultUTRA::physCellId_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return physCellId_Unpack(bits, idx);
}

int MeasResultUTRA::physCellId_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 1) > bits.size())
    {
        printf("MeasResultUTRA::physCellId_Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<1; i++)
        packed_val |= bits[idx++] << (1-i-1);

    if((MeasResultUTRA::physCellId_Enum)packed_val > k_physCellId_tdd)
    {
        printf("MeasResultUTRA::physCellId_Unpack() choice range failure\n");
        return -1;
    }
    physCellId_internal_choice = (MeasResultUTRA::physCellId_Enum)packed_val;
    physCellId_present = true;

    // Fields
    if(physCellId_internal_choice == k_physCellId_fdd)
    {
        if(0 != physCellId_fdd.Unpack(bits, idx))
        {
            printf("MeasResultUTRA::physCellId_fdd unpack failure\n");
            return -1;
        }
    }
    if(physCellId_internal_choice == k_physCellId_tdd)
    {
        if(0 != physCellId_tdd.Unpack(bits, idx))
        {
            printf("MeasResultUTRA::physCellId_tdd unpack failure\n");
            return -1;
        }
    }
    return 0;
}

MeasResultUTRA::physCellId_Enum MeasResultUTRA::physCellId_Choice() const
{
    if(physCellId_present)
        return physCellId_internal_choice;
    return (MeasResultUTRA::physCellId_Enum)0;
}

int MeasResultUTRA::physCellId_SetChoice(MeasResultUTRA::physCellId_Enum choice)
{
    physCellId_internal_choice = choice;
    physCellId_present = true;
    return 0;
}

std::string MeasResultUTRA::physCellId_ChoiceToString(physCellId_Enum value) const
{
    if(k_physCellId_fdd == value)
        return "physCellId_fdd";
    if(k_physCellId_tdd == value)
        return "physCellId_tdd";
    return "";
}

uint64_t MeasResultUTRA::physCellId_NumberOfChoices() const
{
    return 2;
}

std::string MeasResultUTRA::physCellId_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "physCellId = " + physCellId_ChoiceToString(physCellId_internal_choice) + ":\n";
    if(physCellId_internal_choice == k_physCellId_fdd)
        out += physCellId_fdd.ToString(indent+1);
    if(physCellId_internal_choice == k_physCellId_tdd)
        out += physCellId_tdd.ToString(indent+1);
    return out;
}

std::string MeasResultUTRA::physCellId_ToStringNoNewLines() const
{
    std::string out = "physCellId=" + physCellId_ChoiceToString(physCellId_internal_choice) + ",";
    if(physCellId_internal_choice == k_physCellId_fdd)
        out += physCellId_fdd.ToStringNoNewLines();
    if(physCellId_internal_choice == k_physCellId_tdd)
        out += physCellId_tdd.ToStringNoNewLines();
    return out;
}

int MeasResultUTRA::physCellId_Clear()
{
    physCellId_present = false;
    return 0;
}

bool MeasResultUTRA::physCellId_IsPresent() const
{
    return physCellId_present;
}

PhysCellIdUTRA_FDD* MeasResultUTRA::physCellId_fdd_Set()
{
    physCellId_fdd_present = true;
    return &physCellId_fdd;
}

int MeasResultUTRA::physCellId_fdd_Set(PhysCellIdUTRA_FDD &value)
{
    physCellId_fdd_present = true;
    physCellId_fdd = value;
    return 0;
}

const PhysCellIdUTRA_FDD& MeasResultUTRA::physCellId_fdd_Get() const
{
    return physCellId_fdd;
}

std::string MeasResultUTRA::physCellId_fdd_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "fdd:\n";
    out += physCellId_fdd.ToString(indent+1);
    return out;
}

std::string MeasResultUTRA::physCellId_fdd_ToStringNoNewLines() const
{
    std::string out = "fdd:";
    out += physCellId_fdd.ToStringNoNewLines();
    return out;
}

int MeasResultUTRA::physCellId_fdd_Clear()
{
    physCellId_fdd_present = false;
    return 0;
}

bool MeasResultUTRA::physCellId_fdd_IsPresent() const
{
    return physCellId_fdd_present;
}

PhysCellIdUTRA_TDD* MeasResultUTRA::physCellId_tdd_Set()
{
    physCellId_tdd_present = true;
    return &physCellId_tdd;
}

int MeasResultUTRA::physCellId_tdd_Set(PhysCellIdUTRA_TDD &value)
{
    physCellId_tdd_present = true;
    physCellId_tdd = value;
    return 0;
}

const PhysCellIdUTRA_TDD& MeasResultUTRA::physCellId_tdd_Get() const
{
    return physCellId_tdd;
}

std::string MeasResultUTRA::physCellId_tdd_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "tdd:\n";
    out += physCellId_tdd.ToString(indent+1);
    return out;
}

std::string MeasResultUTRA::physCellId_tdd_ToStringNoNewLines() const
{
    std::string out = "tdd:";
    out += physCellId_tdd.ToStringNoNewLines();
    return out;
}

int MeasResultUTRA::physCellId_tdd_Clear()
{
    physCellId_tdd_present = false;
    return 0;
}

bool MeasResultUTRA::physCellId_tdd_IsPresent() const
{
    return physCellId_tdd_present;
}

int MeasResultUTRA::cgi_Info::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(locationAreaCode_IsPresent());
    bits.push_back(routingAreaCode_IsPresent());
    bits.push_back(plmn_IdentityList_IsPresent());

    // Fields
    {
        if(0 != cellGlobalId.Pack(bits))
        {
            printf("MeasResultUTRA::cgi_Info:: field pack failure\n");
            return -1;
        }
    }
    if(locationAreaCode_IsPresent())
    {
        if(0 != locationAreaCode_Pack(bits))
        {
            printf("MeasResultUTRA::cgi_Info:: field pack failure\n");
            return -1;
        }
    }
    if(routingAreaCode_IsPresent())
    {
        if(0 != routingAreaCode_Pack(bits))
        {
            printf("MeasResultUTRA::cgi_Info:: field pack failure\n");
            return -1;
        }
    }
    if(plmn_IdentityList_IsPresent())
    {
        if(0 != plmn_IdentityList.Pack(bits))
        {
            printf("MeasResultUTRA::cgi_Info:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int MeasResultUTRA::cgi_Info::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int MeasResultUTRA::cgi_Info::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("cgi_Info::Unpack() index out of bounds for optional indiator locationAreaCode\n");
        return -1;
    }
    locationAreaCode_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("cgi_Info::Unpack() index out of bounds for optional indiator routingAreaCode\n");
        return -1;
    }
    routingAreaCode_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("cgi_Info::Unpack() index out of bounds for optional indiator plmn_IdentityList\n");
        return -1;
    }
    plmn_IdentityList_present = bits[idx++];

    // Fields
    {
        if(0 != cellGlobalId.Unpack(bits, idx))
        {
            printf("MeasResultUTRA::cgi_Info:: field unpack failure\n");
            return -1;
        }
    }
    if(locationAreaCode_present)
    {
        if(0 != locationAreaCode_Unpack(bits, idx))
        {
            printf("MeasResultUTRA::cgi_Info:: field unpack failure\n");
            return -1;
        }
    }
    if(routingAreaCode_present)
    {
        if(0 != routingAreaCode_Unpack(bits, idx))
        {
            printf("MeasResultUTRA::cgi_Info:: field unpack failure\n");
            return -1;
        }
    }
    if(plmn_IdentityList_present)
    {
        if(0 != plmn_IdentityList.Unpack(bits, idx))
        {
            printf("MeasResultUTRA::cgi_Info:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string MeasResultUTRA::cgi_Info::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cgi_Info:\n";
    out += cellGlobalId_ToString(indent+1);
    if(locationAreaCode_IsPresent())
        out += locationAreaCode_ToString(indent+1);
    if(routingAreaCode_IsPresent())
        out += routingAreaCode_ToString(indent+1);
    if(plmn_IdentityList_IsPresent())
        out += plmn_IdentityList_ToString(indent+1);
    return out;
}

std::string MeasResultUTRA::cgi_Info::ToStringNoNewLines() const
{
    std::string out = "cgi_Info:";
    out += cellGlobalId_ToStringNoNewLines();
    if(locationAreaCode_IsPresent())
        out += locationAreaCode_ToStringNoNewLines();
    if(routingAreaCode_IsPresent())
        out += routingAreaCode_ToStringNoNewLines();
    if(plmn_IdentityList_IsPresent())
        out += plmn_IdentityList_ToStringNoNewLines();
    return out;
}

int MeasResultUTRA::cgi_Info::Set()
{
    present = true;
    return 0;
}

int MeasResultUTRA::cgi_Info::SetPresence(bool is_present)
{
    present = is_present;
    return 0;
}

int MeasResultUTRA::cgi_Info::Clear()
{
    present = false;
    return 0;
}

bool MeasResultUTRA::cgi_Info::IsPresent() const
{
    return present;
}

CellGlobalIdUTRA* MeasResultUTRA::cgi_Info::cellGlobalId_Set()
{
    cellGlobalId_present = true;
    return &cellGlobalId;
}

int MeasResultUTRA::cgi_Info::cellGlobalId_Set(CellGlobalIdUTRA &value)
{
    cellGlobalId_present = true;
    cellGlobalId = value;
    return 0;
}

const CellGlobalIdUTRA& MeasResultUTRA::cgi_Info::cellGlobalId_Get() const
{
    return cellGlobalId;
}

std::string MeasResultUTRA::cgi_Info::cellGlobalId_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cellGlobalId:\n";
    out += cellGlobalId.ToString(indent+1);
    return out;
}

std::string MeasResultUTRA::cgi_Info::cellGlobalId_ToStringNoNewLines() const
{
    std::string out = "cellGlobalId:";
    out += cellGlobalId.ToStringNoNewLines();
    return out;
}

int MeasResultUTRA::cgi_Info::cellGlobalId_Clear()
{
    cellGlobalId_present = false;
    return 0;
}

bool MeasResultUTRA::cgi_Info::cellGlobalId_IsPresent() const
{
    return cellGlobalId_present;
}

int MeasResultUTRA::cgi_Info::locationAreaCode_Pack(std::vector<uint8_t> &bits)
{
    uint32_t size = 16;
    if(size < 16 || size > 16)
    {
        printf("MeasResultUTRA::cgi_Info::locationAreaCode_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((locationAreaCode_internal_value >> (16-i-1)) & 1);
    return 0;
}

int MeasResultUTRA::cgi_Info::locationAreaCode_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return locationAreaCode_Unpack(bits, idx);
}

int MeasResultUTRA::cgi_Info::locationAreaCode_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 16;
    if(size < 16 || size > 16)
    {
        printf("MeasResultUTRA::cgi_Info::locationAreaCode_Unpack() size failure\n");
        return -1;
    }
    locationAreaCode_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("MeasResultUTRA::cgi_Info::locationAreaCode_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        locationAreaCode_internal_value |= (uint16_t)bits[idx++] << (uint16_t)(16-i-1);
    locationAreaCode_present = true;
    return 0;
}

uint16_t MeasResultUTRA::cgi_Info::locationAreaCode_Value() const
{
    if(locationAreaCode_present)
        return locationAreaCode_internal_value;
    uint16_t tmp = 0;
    return tmp;
}

int MeasResultUTRA::cgi_Info::locationAreaCode_SetValue(uint16_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 16)
    {
        printf("MeasResultUTRA::cgi_Info::locationAreaCode_SetValue() size failure\n");
        return -1;
    }
    locationAreaCode_internal_value = value;
    locationAreaCode_present = true;
    return 0;
}

std::string MeasResultUTRA::cgi_Info::locationAreaCode_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "locationAreaCode = ";
    out += std::to_string(locationAreaCode_internal_value);
    out += "\n";
    return out;
}

std::string MeasResultUTRA::cgi_Info::locationAreaCode_ToStringNoNewLines() const
{
    std::string out = "locationAreaCode=";
    out += std::to_string(locationAreaCode_internal_value);
    out += ",";
    return out;
}

int MeasResultUTRA::cgi_Info::locationAreaCode_Clear()
{
    locationAreaCode_present = false;
    return 0;
}

bool MeasResultUTRA::cgi_Info::locationAreaCode_IsPresent() const
{
    return locationAreaCode_present;
}

int MeasResultUTRA::cgi_Info::routingAreaCode_Pack(std::vector<uint8_t> &bits)
{
    uint32_t size = 8;
    if(size < 8 || size > 8)
    {
        printf("MeasResultUTRA::cgi_Info::routingAreaCode_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((routingAreaCode_internal_value >> (8-i-1)) & 1);
    return 0;
}

int MeasResultUTRA::cgi_Info::routingAreaCode_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return routingAreaCode_Unpack(bits, idx);
}

int MeasResultUTRA::cgi_Info::routingAreaCode_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 8;
    if(size < 8 || size > 8)
    {
        printf("MeasResultUTRA::cgi_Info::routingAreaCode_Unpack() size failure\n");
        return -1;
    }
    routingAreaCode_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("MeasResultUTRA::cgi_Info::routingAreaCode_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        routingAreaCode_internal_value |= (uint8_t)bits[idx++] << (uint8_t)(8-i-1);
    routingAreaCode_present = true;
    return 0;
}

uint8_t MeasResultUTRA::cgi_Info::routingAreaCode_Value() const
{
    if(routingAreaCode_present)
        return routingAreaCode_internal_value;
    uint8_t tmp = 0;
    return tmp;
}

int MeasResultUTRA::cgi_Info::routingAreaCode_SetValue(uint8_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 8)
    {
        printf("MeasResultUTRA::cgi_Info::routingAreaCode_SetValue() size failure\n");
        return -1;
    }
    routingAreaCode_internal_value = value;
    routingAreaCode_present = true;
    return 0;
}

std::string MeasResultUTRA::cgi_Info::routingAreaCode_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "routingAreaCode = ";
    out += std::to_string(routingAreaCode_internal_value);
    out += "\n";
    return out;
}

std::string MeasResultUTRA::cgi_Info::routingAreaCode_ToStringNoNewLines() const
{
    std::string out = "routingAreaCode=";
    out += std::to_string(routingAreaCode_internal_value);
    out += ",";
    return out;
}

int MeasResultUTRA::cgi_Info::routingAreaCode_Clear()
{
    routingAreaCode_present = false;
    return 0;
}

bool MeasResultUTRA::cgi_Info::routingAreaCode_IsPresent() const
{
    return routingAreaCode_present;
}

PLMN_IdentityList2* MeasResultUTRA::cgi_Info::plmn_IdentityList_Set()
{
    plmn_IdentityList_present = true;
    return &plmn_IdentityList;
}

int MeasResultUTRA::cgi_Info::plmn_IdentityList_Set(PLMN_IdentityList2 &value)
{
    plmn_IdentityList_present = true;
    plmn_IdentityList = value;
    return 0;
}

const PLMN_IdentityList2& MeasResultUTRA::cgi_Info::plmn_IdentityList_Get() const
{
    return plmn_IdentityList;
}

std::string MeasResultUTRA::cgi_Info::plmn_IdentityList_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "plmn_IdentityList:\n";
    out += plmn_IdentityList.ToString(indent+1);
    return out;
}

std::string MeasResultUTRA::cgi_Info::plmn_IdentityList_ToStringNoNewLines() const
{
    std::string out = "plmn_IdentityList:";
    out += plmn_IdentityList.ToStringNoNewLines();
    return out;
}

int MeasResultUTRA::cgi_Info::plmn_IdentityList_Clear()
{
    plmn_IdentityList_present = false;
    return 0;
}

bool MeasResultUTRA::cgi_Info::plmn_IdentityList_IsPresent() const
{
    return plmn_IdentityList_present;
}

int MeasResultUTRA::measResult::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator
    bool has_extension = false;
    if(additionalSI_Info_r9_IsPresent())
    {
        bits.push_back(1);
        has_extension = true;
    }else{
        bits.push_back(0);
    }

    // Optional indicators
    bits.push_back(utra_RSCP_IsPresent());
    bits.push_back(utra_EcN0_IsPresent());

    // Fields
    if(utra_RSCP_IsPresent())
    {
        if(0 != utra_RSCP_Pack(bits))
        {
            printf("MeasResultUTRA::measResult:: field pack failure\n");
            return -1;
        }
    }
    if(utra_EcN0_IsPresent())
    {
        if(0 != utra_EcN0_Pack(bits))
        {
            printf("MeasResultUTRA::measResult:: field pack failure\n");
            return -1;
        }
    }

    // Extension
    if(has_extension)
    {
        // Number of extension fields
        if(0 < 64)
        {
            bits.push_back(0);
            for(uint32_t i=0; i<6; i++)
                bits.push_back((0 >> (6-i-1)) & 1);
        }else{
            printf("measResult:: Extension list size too large failure\n");
            return -1;
        }

        // Extension field presence indicators
        bits.push_back(additionalSI_Info_r9_IsPresent());

        // Extension fields
        if(additionalSI_Info_r9_IsPresent())
        {
            std::vector<uint8_t> field_bits;
            if(0 != additionalSI_Info_r9.Pack(field_bits))
            {
                printf("MeasResultUTRA::measResult:: field pack failure\n");
                return -1;
            }
            while((field_bits.size() % 8) != 0)
                field_bits.push_back(0);
            uint32_t N_octets = field_bits.size() / 8;
            uint32_t local_size_length = 0;
            uint32_t local_size = N_octets;
            if(local_size < 128)
            {
                bits.push_back(0);
                local_size_length = 7;
            }else if(local_size < 16383){
                bits.push_back(1);
                bits.push_back(0);
                local_size_length = 14;
            }else{
                bits.push_back(1);
                bits.push_back(1);
                uint32_t N_16k_blocks = local_size / 16383;
                for(uint32_t i=0; i<6; i++)
                    bits.push_back((N_16k_blocks >> (6-i-1)) & 1);
                local_size %= 16383;
                if(local_size < 128)
                {
                    bits.push_back(0);
                    local_size_length = 7;
                }else{
                    bits.push_back(1);
                    bits.push_back(0);
                    local_size_length = 14;
                }
            }
            for(uint32_t i=0; i<local_size_length; i++)
                bits.push_back((local_size >> (local_size_length-i-1)) & 1);
            for(auto b : field_bits)
                bits.push_back(b);
        }
    }
    return 0;
}

int MeasResultUTRA::measResult::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int MeasResultUTRA::measResult::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("measResult::Unpack() index out of bounds for extension\n");
        return -1;
    }
    bool has_extension = bits[idx++];

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("measResult::Unpack() index out of bounds for optional indiator utra_RSCP\n");
        return -1;
    }
    utra_RSCP_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("measResult::Unpack() index out of bounds for optional indiator utra_EcN0\n");
        return -1;
    }
    utra_EcN0_present = bits[idx++];

    // Fields
    if(utra_RSCP_present)
    {
        if(0 != utra_RSCP_Unpack(bits, idx))
        {
            printf("MeasResultUTRA::measResult:: field unpack failure\n");
            return -1;
        }
    }
    if(utra_EcN0_present)
    {
        if(0 != utra_EcN0_Unpack(bits, idx))
        {
            printf("MeasResultUTRA::measResult:: field unpack failure\n");
            return -1;
        }
    }

    // Extension
    if(has_extension)
    {
        if((idx + 7) > bits.size())
        {
            printf("measResult::Unpack() index out of bounds for extension size\n");
            return -1;
        }
        // Number of extension fields
        if(bits[idx++] != 0)
        {
            printf("measResult:: Extension list size too large failure\n");
            return -1;
        }
        uint32_t N_ext_fields = 0;
        for(uint32_t i=0; i<6; i++)
            N_ext_fields |= bits[idx++] << (6-i-1);
        N_ext_fields++;

        // Extension field presence indicators
        uint32_t opt_ind_count = 0;
        if(opt_ind_count++ < N_ext_fields)
        {
            if((idx + 1) > bits.size())
            {
                printf("measResult::Unpack() index out of bounds for optional indiator additionalSI_Info_r9\n");
                return -1;
            }
            additionalSI_Info_r9_present = bits[idx++];
        }
        if((idx + (N_ext_fields - opt_ind_count)) > bits.size())
        {
            printf("measResult::Unpack() index out of bounds for extension optional indicators\n");
            return -1;
        }
        idx += (N_ext_fields - opt_ind_count);

        // Extension fields
        if(additionalSI_Info_r9_present)
        {
            uint32_t local_size_length = 0;
            uint32_t N_octets = 0;
            if(0 == bits[idx++])
            {
                local_size_length = 7;
            }else{
                if(0 == bits[idx++])
                {
                    local_size_length = 14;
                }else{
                    for(uint32_t i=0; i<6; i++)
                        N_octets |= bits[idx++] << (6-i-1);
                    N_octets *= 16383;
                    if(0 == bits[idx++])
                    {
                        local_size_length = 7;
                    }else{
                        idx++;
                        local_size_length = 14;
                    }
                }
            }
            for(uint32_t i=0; i<local_size_length; i++)
                N_octets |= bits[idx++] << (local_size_length-i-1);
            uint32_t orig_idx = idx;
            if(0 != additionalSI_Info_r9.Unpack(bits, idx))
            {
                printf("MeasResultUTRA::measResult:: field unpack failure\n");
                return -1;
            }
            idx = orig_idx + (N_octets * 8);
        }
        for(uint32_t i=1; i<N_ext_fields; i++)
        {
            uint32_t local_size_length = 0;
            uint32_t N_octets = 0;
            if(0 == bits[idx++])
            {
                local_size_length = 7;
            }else{
                if(0 == bits[idx++])
                {
                    local_size_length = 14;
                }else{
                    for(uint32_t i=0; i<6; i++)
                        N_octets |= bits[idx++] << (6-i-1);
                    N_octets *= 16383;
                    if(0 == bits[idx++])
                    {
                        local_size_length = 7;
                    }else{
                        idx++;
                        local_size_length = 14;
                    }
                }
            }
            for(uint32_t i=0; i<local_size_length; i++)
                N_octets |= bits[idx++] << (local_size_length-i-1);
        if((idx + (N_octets * 8)) > bits.size())
        {
            printf("measResult::Unpack() index out of bounds for extension fields\n");
            return -1;
        }
            idx += N_octets * 8;
        }
    }
    return 0;
}

std::string MeasResultUTRA::measResult::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "measResult:\n";
    if(utra_RSCP_IsPresent())
        out += utra_RSCP_ToString(indent+1);
    if(utra_EcN0_IsPresent())
        out += utra_EcN0_ToString(indent+1);
    if(additionalSI_Info_r9_IsPresent())
        out += additionalSI_Info_r9_ToString(indent+1);
    return out;
}

std::string MeasResultUTRA::measResult::ToStringNoNewLines() const
{
    std::string out = "measResult:";
    if(utra_RSCP_IsPresent())
        out += utra_RSCP_ToStringNoNewLines();
    if(utra_EcN0_IsPresent())
        out += utra_EcN0_ToStringNoNewLines();
    if(additionalSI_Info_r9_IsPresent())
        out += additionalSI_Info_r9_ToStringNoNewLines();
    return out;
}

int MeasResultUTRA::measResult::utra_RSCP_Pack(std::vector<uint8_t> &bits)
{
    int64_t val_to_pack = utra_RSCP_internal_value - (-5);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (91 - -5))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int MeasResultUTRA::measResult::utra_RSCP_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return utra_RSCP_Unpack(bits, idx);
}

int MeasResultUTRA::measResult::utra_RSCP_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (91 - -5))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("MeasResultUTRA::measResult::utra_RSCP_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    utra_RSCP_internal_value = packed_val + -5;
    utra_RSCP_present = true;
    return 0;
}

int64_t MeasResultUTRA::measResult::utra_RSCP_Value() const
{
    if(utra_RSCP_present)
        return utra_RSCP_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int MeasResultUTRA::measResult::utra_RSCP_SetValue(int64_t value)
{
    if(value < -5 || value > 91)
    {
        printf("MeasResultUTRA::measResult::utra_RSCP_SetValue() range failure\n");
        return -1;
    }
    utra_RSCP_internal_value = value;
    utra_RSCP_present = true;
    return 0;
}

std::string MeasResultUTRA::measResult::utra_RSCP_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "utra_RSCP = " + std::to_string(utra_RSCP_internal_value) + "\n";
    return out;
}

std::string MeasResultUTRA::measResult::utra_RSCP_ToStringNoNewLines() const
{
    std::string out = "utra_RSCP=" + std::to_string(utra_RSCP_internal_value) + ",";
    return out;
}

int MeasResultUTRA::measResult::utra_RSCP_Clear()
{
    utra_RSCP_present = false;
    return 0;
}

bool MeasResultUTRA::measResult::utra_RSCP_IsPresent() const
{
    return utra_RSCP_present;
}

int MeasResultUTRA::measResult::utra_EcN0_Pack(std::vector<uint8_t> &bits)
{
    int64_t val_to_pack = utra_EcN0_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (49 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int MeasResultUTRA::measResult::utra_EcN0_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return utra_EcN0_Unpack(bits, idx);
}

int MeasResultUTRA::measResult::utra_EcN0_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (49 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("MeasResultUTRA::measResult::utra_EcN0_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    utra_EcN0_internal_value = packed_val + 0;
    utra_EcN0_present = true;
    return 0;
}

int64_t MeasResultUTRA::measResult::utra_EcN0_Value() const
{
    if(utra_EcN0_present)
        return utra_EcN0_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int MeasResultUTRA::measResult::utra_EcN0_SetValue(int64_t value)
{
    if(value < 0 || value > 49)
    {
        printf("MeasResultUTRA::measResult::utra_EcN0_SetValue() range failure\n");
        return -1;
    }
    utra_EcN0_internal_value = value;
    utra_EcN0_present = true;
    return 0;
}

std::string MeasResultUTRA::measResult::utra_EcN0_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "utra_EcN0 = " + std::to_string(utra_EcN0_internal_value) + "\n";
    return out;
}

std::string MeasResultUTRA::measResult::utra_EcN0_ToStringNoNewLines() const
{
    std::string out = "utra_EcN0=" + std::to_string(utra_EcN0_internal_value) + ",";
    return out;
}

int MeasResultUTRA::measResult::utra_EcN0_Clear()
{
    utra_EcN0_present = false;
    return 0;
}

bool MeasResultUTRA::measResult::utra_EcN0_IsPresent() const
{
    return utra_EcN0_present;
}

AdditionalSI_Info_r9* MeasResultUTRA::measResult::additionalSI_Info_r9_Set()
{
    additionalSI_Info_r9_present = true;
    return &additionalSI_Info_r9;
}

int MeasResultUTRA::measResult::additionalSI_Info_r9_Set(AdditionalSI_Info_r9 &value)
{
    additionalSI_Info_r9_present = true;
    additionalSI_Info_r9 = value;
    return 0;
}

const AdditionalSI_Info_r9& MeasResultUTRA::measResult::additionalSI_Info_r9_Get() const
{
    return additionalSI_Info_r9;
}

std::string MeasResultUTRA::measResult::additionalSI_Info_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "additionalSI_Info_r9:\n";
    out += additionalSI_Info_r9.ToString(indent+1);
    return out;
}

std::string MeasResultUTRA::measResult::additionalSI_Info_r9_ToStringNoNewLines() const
{
    std::string out = "additionalSI_Info_r9:";
    out += additionalSI_Info_r9.ToStringNoNewLines();
    return out;
}

int MeasResultUTRA::measResult::additionalSI_Info_r9_Clear()
{
    additionalSI_Info_r9_present = false;
    return 0;
}

bool MeasResultUTRA::measResult::additionalSI_Info_r9_IsPresent() const
{
    return additionalSI_Info_r9_present;
}

