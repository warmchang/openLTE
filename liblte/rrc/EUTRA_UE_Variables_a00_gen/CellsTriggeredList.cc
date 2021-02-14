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

#include "CellsTriggeredList.h"

#include <cmath>

int CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_Pack(std::vector<uint8_t> &bits)
{
    if(!CellsTriggeredList_present)
    {
        printf("CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_Pack() presence failure\n");
        return -1;
    }
    // Extension indicator

    // Choice
    for(uint32_t i=0; i<2; i++)
        bits.push_back((CellsTriggeredList_internal_choice >> (2-i-1)) & 1);

    // Fields
    if(CellsTriggeredList_internal_choice == k_CellsTriggeredList_physCellIdEUTRA)
    {
        if(0 != CellsTriggeredList_physCellIdEUTRA.Pack(bits))
        {
            printf("CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdEUTRA pack failure\n");
            return -1;
        }
    }
    if(CellsTriggeredList_internal_choice == k_CellsTriggeredList_physCellIdUTRA)
    {
        if(0 != CellsTriggeredList_physCellIdUTRA_Pack(bits))
        {
            printf("CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdUTRA pack failure\n");
            return -1;
        }
    }
    if(CellsTriggeredList_internal_choice == k_CellsTriggeredList_physCellIdGERAN)
    {
        if(0 != CellsTriggeredList_physCellIdGERAN_value.Pack(bits))
        {
            printf("CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdGERAN pack failure\n");
            return -1;
        }
    }
    if(CellsTriggeredList_internal_choice == k_CellsTriggeredList_physCellIdCDMA2000)
    {
        if(0 != CellsTriggeredList_physCellIdCDMA2000.Pack(bits))
        {
            printf("CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdCDMA2000 pack failure\n");
            return -1;
        }
    }
    return 0;
}

int CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return CellsTriggeredList_Unpack(bits, idx);
}

int CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 2) > bits.size())
    {
        printf("CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<2; i++)
        packed_val |= bits[idx++] << (2-i-1);

    if((CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_Enum)packed_val > k_CellsTriggeredList_physCellIdCDMA2000)
    {
        printf("CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_Unpack() choice range failure\n");
        return -1;
    }
    CellsTriggeredList_internal_choice = (CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_Enum)packed_val;
    CellsTriggeredList_present = true;

    // Fields
    if(CellsTriggeredList_internal_choice == k_CellsTriggeredList_physCellIdEUTRA)
    {
        if(0 != CellsTriggeredList_physCellIdEUTRA.Unpack(bits, idx))
        {
            printf("CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdEUTRA unpack failure\n");
            return -1;
        }
    }
    if(CellsTriggeredList_internal_choice == k_CellsTriggeredList_physCellIdUTRA)
    {
        if(0 != CellsTriggeredList_physCellIdUTRA_Unpack(bits, idx))
        {
            printf("CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdUTRA unpack failure\n");
            return -1;
        }
    }
    if(CellsTriggeredList_internal_choice == k_CellsTriggeredList_physCellIdGERAN)
    {
        if(0 != CellsTriggeredList_physCellIdGERAN_value.Unpack(bits, idx))
        {
            printf("CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdGERAN unpack failure\n");
            return -1;
        }
    }
    if(CellsTriggeredList_internal_choice == k_CellsTriggeredList_physCellIdCDMA2000)
    {
        if(0 != CellsTriggeredList_physCellIdCDMA2000.Unpack(bits, idx))
        {
            printf("CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdCDMA2000 unpack failure\n");
            return -1;
        }
    }
    return 0;
}

CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_Enum CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_Choice() const
{
    if(CellsTriggeredList_present)
        return CellsTriggeredList_internal_choice;
    return (CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_Enum)0;
}

int CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_SetChoice(CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_Enum choice)
{
    CellsTriggeredList_internal_choice = choice;
    CellsTriggeredList_present = true;
    return 0;
}

std::string CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_ChoiceToString(CellsTriggeredList_Enum value) const
{
    if(k_CellsTriggeredList_physCellIdEUTRA == value)
        return "CellsTriggeredList_physCellIdEUTRA";
    if(k_CellsTriggeredList_physCellIdUTRA == value)
        return "CellsTriggeredList_physCellIdUTRA";
    if(k_CellsTriggeredList_physCellIdGERAN == value)
        return "CellsTriggeredList_physCellIdGERAN";
    if(k_CellsTriggeredList_physCellIdCDMA2000 == value)
        return "CellsTriggeredList_physCellIdCDMA2000";
    return "";
}

uint64_t CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_NumberOfChoices() const
{
    return 4;
}

std::string CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "CellsTriggeredList = " + CellsTriggeredList_ChoiceToString(CellsTriggeredList_internal_choice) + ":\n";
    if(CellsTriggeredList_internal_choice == k_CellsTriggeredList_physCellIdEUTRA)
        out += CellsTriggeredList_physCellIdEUTRA.ToString(indent+1);
    if(CellsTriggeredList_internal_choice == k_CellsTriggeredList_physCellIdUTRA)
        out += CellsTriggeredList_physCellIdUTRA_ToString(indent+1);
    if(CellsTriggeredList_internal_choice == k_CellsTriggeredList_physCellIdGERAN)
        out += CellsTriggeredList_physCellIdGERAN_value.ToString(indent+1);
    if(CellsTriggeredList_internal_choice == k_CellsTriggeredList_physCellIdCDMA2000)
        out += CellsTriggeredList_physCellIdCDMA2000.ToString(indent+1);
    return out;
}

std::string CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_ToStringNoNewLines() const
{
    std::string out = "CellsTriggeredList=" + CellsTriggeredList_ChoiceToString(CellsTriggeredList_internal_choice) + ",";
    if(CellsTriggeredList_internal_choice == k_CellsTriggeredList_physCellIdEUTRA)
        out += CellsTriggeredList_physCellIdEUTRA.ToStringNoNewLines();
    if(CellsTriggeredList_internal_choice == k_CellsTriggeredList_physCellIdUTRA)
        out += CellsTriggeredList_physCellIdUTRA_ToStringNoNewLines();
    if(CellsTriggeredList_internal_choice == k_CellsTriggeredList_physCellIdGERAN)
        out += CellsTriggeredList_physCellIdGERAN_value.ToStringNoNewLines();
    if(CellsTriggeredList_internal_choice == k_CellsTriggeredList_physCellIdCDMA2000)
        out += CellsTriggeredList_physCellIdCDMA2000.ToStringNoNewLines();
    return out;
}

int CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_Clear()
{
    CellsTriggeredList_present = false;
    return 0;
}

bool CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_IsPresent() const
{
    return CellsTriggeredList_present;
}

PhysCellId* CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdEUTRA_Set()
{
    CellsTriggeredList_physCellIdEUTRA_present = true;
    return &CellsTriggeredList_physCellIdEUTRA;
}

int CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdEUTRA_Set(PhysCellId &value)
{
    CellsTriggeredList_physCellIdEUTRA_present = true;
    CellsTriggeredList_physCellIdEUTRA = value;
    return 0;
}

const PhysCellId& CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdEUTRA_Get() const
{
    return CellsTriggeredList_physCellIdEUTRA;
}

std::string CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdEUTRA_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "physCellIdEUTRA:\n";
    out += CellsTriggeredList_physCellIdEUTRA.ToString(indent+1);
    return out;
}

std::string CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdEUTRA_ToStringNoNewLines() const
{
    std::string out = "physCellIdEUTRA:";
    out += CellsTriggeredList_physCellIdEUTRA.ToStringNoNewLines();
    return out;
}

int CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdEUTRA_Clear()
{
    CellsTriggeredList_physCellIdEUTRA_present = false;
    return 0;
}

bool CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdEUTRA_IsPresent() const
{
    return CellsTriggeredList_physCellIdEUTRA_present;
}

int CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdUTRA_Pack(std::vector<uint8_t> &bits)
{
    if(!CellsTriggeredList_physCellIdUTRA_present)
    {
        printf("CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdUTRA_Pack() presence failure\n");
        return -1;
    }
    // Extension indicator

    // Choice
    for(uint32_t i=0; i<1; i++)
        bits.push_back((CellsTriggeredList_physCellIdUTRA_internal_choice >> (1-i-1)) & 1);

    // Fields
    if(CellsTriggeredList_physCellIdUTRA_internal_choice == k_CellsTriggeredList_physCellIdUTRA_fdd)
    {
        if(0 != CellsTriggeredList_physCellIdUTRA_fdd.Pack(bits))
        {
            printf("CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdUTRA_fdd pack failure\n");
            return -1;
        }
    }
    if(CellsTriggeredList_physCellIdUTRA_internal_choice == k_CellsTriggeredList_physCellIdUTRA_tdd)
    {
        if(0 != CellsTriggeredList_physCellIdUTRA_tdd.Pack(bits))
        {
            printf("CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdUTRA_tdd pack failure\n");
            return -1;
        }
    }
    return 0;
}

int CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdUTRA_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return CellsTriggeredList_physCellIdUTRA_Unpack(bits, idx);
}

int CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdUTRA_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 1) > bits.size())
    {
        printf("CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdUTRA_Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<1; i++)
        packed_val |= bits[idx++] << (1-i-1);

    if((CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdUTRA_Enum)packed_val > k_CellsTriggeredList_physCellIdUTRA_tdd)
    {
        printf("CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdUTRA_Unpack() choice range failure\n");
        return -1;
    }
    CellsTriggeredList_physCellIdUTRA_internal_choice = (CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdUTRA_Enum)packed_val;
    CellsTriggeredList_physCellIdUTRA_present = true;

    // Fields
    if(CellsTriggeredList_physCellIdUTRA_internal_choice == k_CellsTriggeredList_physCellIdUTRA_fdd)
    {
        if(0 != CellsTriggeredList_physCellIdUTRA_fdd.Unpack(bits, idx))
        {
            printf("CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdUTRA_fdd unpack failure\n");
            return -1;
        }
    }
    if(CellsTriggeredList_physCellIdUTRA_internal_choice == k_CellsTriggeredList_physCellIdUTRA_tdd)
    {
        if(0 != CellsTriggeredList_physCellIdUTRA_tdd.Unpack(bits, idx))
        {
            printf("CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdUTRA_tdd unpack failure\n");
            return -1;
        }
    }
    return 0;
}

CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdUTRA_Enum CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdUTRA_Choice() const
{
    if(CellsTriggeredList_physCellIdUTRA_present)
        return CellsTriggeredList_physCellIdUTRA_internal_choice;
    return (CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdUTRA_Enum)0;
}

int CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdUTRA_SetChoice(CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdUTRA_Enum choice)
{
    CellsTriggeredList_physCellIdUTRA_internal_choice = choice;
    CellsTriggeredList_physCellIdUTRA_present = true;
    return 0;
}

std::string CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdUTRA_ChoiceToString(CellsTriggeredList_physCellIdUTRA_Enum value) const
{
    if(k_CellsTriggeredList_physCellIdUTRA_fdd == value)
        return "CellsTriggeredList_physCellIdUTRA_fdd";
    if(k_CellsTriggeredList_physCellIdUTRA_tdd == value)
        return "CellsTriggeredList_physCellIdUTRA_tdd";
    return "";
}

uint64_t CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdUTRA_NumberOfChoices() const
{
    return 2;
}

std::string CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdUTRA_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "physCellIdUTRA = " + CellsTriggeredList_physCellIdUTRA_ChoiceToString(CellsTriggeredList_physCellIdUTRA_internal_choice) + ":\n";
    if(CellsTriggeredList_physCellIdUTRA_internal_choice == k_CellsTriggeredList_physCellIdUTRA_fdd)
        out += CellsTriggeredList_physCellIdUTRA_fdd.ToString(indent+1);
    if(CellsTriggeredList_physCellIdUTRA_internal_choice == k_CellsTriggeredList_physCellIdUTRA_tdd)
        out += CellsTriggeredList_physCellIdUTRA_tdd.ToString(indent+1);
    return out;
}

std::string CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdUTRA_ToStringNoNewLines() const
{
    std::string out = "physCellIdUTRA=" + CellsTriggeredList_physCellIdUTRA_ChoiceToString(CellsTriggeredList_physCellIdUTRA_internal_choice) + ",";
    if(CellsTriggeredList_physCellIdUTRA_internal_choice == k_CellsTriggeredList_physCellIdUTRA_fdd)
        out += CellsTriggeredList_physCellIdUTRA_fdd.ToStringNoNewLines();
    if(CellsTriggeredList_physCellIdUTRA_internal_choice == k_CellsTriggeredList_physCellIdUTRA_tdd)
        out += CellsTriggeredList_physCellIdUTRA_tdd.ToStringNoNewLines();
    return out;
}

int CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdUTRA_Clear()
{
    CellsTriggeredList_physCellIdUTRA_present = false;
    return 0;
}

bool CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdUTRA_IsPresent() const
{
    return CellsTriggeredList_physCellIdUTRA_present;
}

PhysCellIdUTRA_FDD* CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdUTRA_fdd_Set()
{
    CellsTriggeredList_physCellIdUTRA_fdd_present = true;
    return &CellsTriggeredList_physCellIdUTRA_fdd;
}

int CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdUTRA_fdd_Set(PhysCellIdUTRA_FDD &value)
{
    CellsTriggeredList_physCellIdUTRA_fdd_present = true;
    CellsTriggeredList_physCellIdUTRA_fdd = value;
    return 0;
}

const PhysCellIdUTRA_FDD& CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdUTRA_fdd_Get() const
{
    return CellsTriggeredList_physCellIdUTRA_fdd;
}

std::string CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdUTRA_fdd_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "fdd:\n";
    out += CellsTriggeredList_physCellIdUTRA_fdd.ToString(indent+1);
    return out;
}

std::string CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdUTRA_fdd_ToStringNoNewLines() const
{
    std::string out = "fdd:";
    out += CellsTriggeredList_physCellIdUTRA_fdd.ToStringNoNewLines();
    return out;
}

int CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdUTRA_fdd_Clear()
{
    CellsTriggeredList_physCellIdUTRA_fdd_present = false;
    return 0;
}

bool CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdUTRA_fdd_IsPresent() const
{
    return CellsTriggeredList_physCellIdUTRA_fdd_present;
}

PhysCellIdUTRA_TDD* CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdUTRA_tdd_Set()
{
    CellsTriggeredList_physCellIdUTRA_tdd_present = true;
    return &CellsTriggeredList_physCellIdUTRA_tdd;
}

int CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdUTRA_tdd_Set(PhysCellIdUTRA_TDD &value)
{
    CellsTriggeredList_physCellIdUTRA_tdd_present = true;
    CellsTriggeredList_physCellIdUTRA_tdd = value;
    return 0;
}

const PhysCellIdUTRA_TDD& CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdUTRA_tdd_Get() const
{
    return CellsTriggeredList_physCellIdUTRA_tdd;
}

std::string CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdUTRA_tdd_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "tdd:\n";
    out += CellsTriggeredList_physCellIdUTRA_tdd.ToString(indent+1);
    return out;
}

std::string CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdUTRA_tdd_ToStringNoNewLines() const
{
    std::string out = "tdd:";
    out += CellsTriggeredList_physCellIdUTRA_tdd.ToStringNoNewLines();
    return out;
}

int CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdUTRA_tdd_Clear()
{
    CellsTriggeredList_physCellIdUTRA_tdd_present = false;
    return 0;
}

bool CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdUTRA_tdd_IsPresent() const
{
    return CellsTriggeredList_physCellIdUTRA_tdd_present;
}

int CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdGERAN::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != carrierFreq.Pack(bits))
        {
            printf("CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdGERAN:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != physCellId.Pack(bits))
        {
            printf("CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdGERAN:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdGERAN::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdGERAN::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != carrierFreq.Unpack(bits, idx))
        {
            printf("CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdGERAN:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != physCellId.Unpack(bits, idx))
        {
            printf("CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdGERAN:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdGERAN::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "physCellIdGERAN:\n";
    out += carrierFreq_ToString(indent+1);
    out += physCellId_ToString(indent+1);
    return out;
}

std::string CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdGERAN::ToStringNoNewLines() const
{
    std::string out = "physCellIdGERAN:";
    out += carrierFreq_ToStringNoNewLines();
    out += physCellId_ToStringNoNewLines();
    return out;
}

CarrierFreqGERAN* CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdGERAN::carrierFreq_Set()
{
    carrierFreq_present = true;
    return &carrierFreq;
}

int CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdGERAN::carrierFreq_Set(CarrierFreqGERAN &value)
{
    carrierFreq_present = true;
    carrierFreq = value;
    return 0;
}

const CarrierFreqGERAN& CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdGERAN::carrierFreq_Get() const
{
    return carrierFreq;
}

std::string CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdGERAN::carrierFreq_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "carrierFreq:\n";
    out += carrierFreq.ToString(indent+1);
    return out;
}

std::string CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdGERAN::carrierFreq_ToStringNoNewLines() const
{
    std::string out = "carrierFreq:";
    out += carrierFreq.ToStringNoNewLines();
    return out;
}

int CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdGERAN::carrierFreq_Clear()
{
    carrierFreq_present = false;
    return 0;
}

bool CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdGERAN::carrierFreq_IsPresent() const
{
    return carrierFreq_present;
}

PhysCellIdGERAN* CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdGERAN::physCellId_Set()
{
    physCellId_present = true;
    return &physCellId;
}

int CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdGERAN::physCellId_Set(PhysCellIdGERAN &value)
{
    physCellId_present = true;
    physCellId = value;
    return 0;
}

const PhysCellIdGERAN& CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdGERAN::physCellId_Get() const
{
    return physCellId;
}

std::string CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdGERAN::physCellId_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "physCellId:\n";
    out += physCellId.ToString(indent+1);
    return out;
}

std::string CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdGERAN::physCellId_ToStringNoNewLines() const
{
    std::string out = "physCellId:";
    out += physCellId.ToStringNoNewLines();
    return out;
}

int CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdGERAN::physCellId_Clear()
{
    physCellId_present = false;
    return 0;
}

bool CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdGERAN::physCellId_IsPresent() const
{
    return physCellId_present;
}

PhysCellIdCDMA2000* CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdCDMA2000_Set()
{
    CellsTriggeredList_physCellIdCDMA2000_present = true;
    return &CellsTriggeredList_physCellIdCDMA2000;
}

int CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdCDMA2000_Set(PhysCellIdCDMA2000 &value)
{
    CellsTriggeredList_physCellIdCDMA2000_present = true;
    CellsTriggeredList_physCellIdCDMA2000 = value;
    return 0;
}

const PhysCellIdCDMA2000& CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdCDMA2000_Get() const
{
    return CellsTriggeredList_physCellIdCDMA2000;
}

std::string CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdCDMA2000_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "physCellIdCDMA2000:\n";
    out += CellsTriggeredList_physCellIdCDMA2000.ToString(indent+1);
    return out;
}

std::string CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdCDMA2000_ToStringNoNewLines() const
{
    std::string out = "physCellIdCDMA2000:";
    out += CellsTriggeredList_physCellIdCDMA2000.ToStringNoNewLines();
    return out;
}

int CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdCDMA2000_Clear()
{
    CellsTriggeredList_physCellIdCDMA2000_present = false;
    return 0;
}

bool CellsTriggeredList::CellsTriggeredList_::CellsTriggeredList_physCellIdCDMA2000_IsPresent() const
{
    return CellsTriggeredList_physCellIdCDMA2000_present;
}

#include "maxCellMeas.h"

int CellsTriggeredList::Pack(std::vector<uint8_t> &bits)
{
    if(!present)
    {
        printf("CellsTriggeredList::Pack() presence failure\n");
        return -1;
    }
    uint32_t N_size_bits = 1;
    while(pow(2, N_size_bits) <= (maxCellMeas - 1))
        N_size_bits++;
    uint32_t local_size = internal_value.size() - 1;
    for(uint32_t i=0; i<N_size_bits; i++)
        bits.push_back((local_size >> (N_size_bits-i-1)) & 1);
    for(auto item : internal_value)
        if(0 != item.CellsTriggeredList_Pack(bits))
        {
            printf("CellsTriggeredList::Pack() item_pack_failure\n");
            return -1;
        }
    return 0;
}

int CellsTriggeredList::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int CellsTriggeredList::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_size_bits = 1;
    while(pow(2, N_size_bits) <= (maxCellMeas - 1))
        N_size_bits++;
    uint32_t size = 0;
    for(uint32_t i=0; i<N_size_bits; i++)
        size |= bits[idx++] << (N_size_bits-i-1);
    size += 1;
    internal_value.clear();
    for(uint32_t i=0; i<size; i++)
    {
        CellsTriggeredList_ tmp;
        if(0 != tmp.CellsTriggeredList_Unpack(bits, idx))
        {
            printf("CellsTriggeredList::Unpack() item unpack failure\n");
            return -1;
        }
        internal_value.push_back(tmp);
    }
    present = true;
    return 0;
}

std::vector<CellsTriggeredList::CellsTriggeredList_> CellsTriggeredList::Value() const
{
    if(present)
        return internal_value;
    return {};
}

int CellsTriggeredList::SetValue(std::vector<CellsTriggeredList::CellsTriggeredList_> value)
{
    if(value.size() < 1 || value.size() > maxCellMeas)
    {
        printf("CellsTriggeredList::SetValue() list size failure\n");
        return -1;
    }
    internal_value = value;
    present = true;
    return 0;
}

std::string CellsTriggeredList::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "CellsTriggeredList:\n";
    for(auto item : internal_value)
        out += item.CellsTriggeredList_ToString(indent+1);
    return out;
}

std::string CellsTriggeredList::ToStringNoNewLines() const
{
    std::string out = "CellsTriggeredList:";
    for(auto item : internal_value)
        out += item.CellsTriggeredList_ToStringNoNewLines();
    return out;
}

