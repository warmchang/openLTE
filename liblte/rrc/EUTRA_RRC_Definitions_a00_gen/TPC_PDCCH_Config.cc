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

#include "TPC_PDCCH_Config.h"

#include <cmath>

int TPC_PDCCH_Config::Pack(std::vector<uint8_t> &bits)
{
    if(!present)
    {
        printf("TPC_PDCCH_Config::Pack() presence failure\n");
        return -1;
    }
    // Extension indicator

    // Choice
    for(uint32_t i=0; i<1; i++)
        bits.push_back((internal_choice >> (1-i-1)) & 1);

    // Fields
    if(internal_choice == k_release)
    {
        if(0 != release_Pack(bits))
        {
            printf("TPC_PDCCH_Config::release pack failure\n");
            return -1;
        }
    }
    if(internal_choice == k_setup)
    {
        if(0 != setup_value.Pack(bits))
        {
            printf("TPC_PDCCH_Config::setup pack failure\n");
            return -1;
        }
    }
    return 0;
}

int TPC_PDCCH_Config::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int TPC_PDCCH_Config::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 1) > bits.size())
    {
        printf("TPC_PDCCH_Config::Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<1; i++)
        packed_val |= bits[idx++] << (1-i-1);

    if((TPC_PDCCH_Config::Enum)packed_val > k_setup)
    {
        printf("TPC_PDCCH_Config::Unpack() choice range failure\n");
        return -1;
    }
    internal_choice = (TPC_PDCCH_Config::Enum)packed_val;
    present = true;

    // Fields
    if(internal_choice == k_release)
    {
        if(0 != release_Unpack(bits, idx))
        {
            printf("TPC_PDCCH_Config::release unpack failure\n");
            return -1;
        }
    }
    if(internal_choice == k_setup)
    {
        if(0 != setup_value.Unpack(bits, idx))
        {
            printf("TPC_PDCCH_Config::setup unpack failure\n");
            return -1;
        }
    }
    return 0;
}

TPC_PDCCH_Config::Enum TPC_PDCCH_Config::Choice() const
{
    if(present)
        return internal_choice;
    return (TPC_PDCCH_Config::Enum)0;
}

int TPC_PDCCH_Config::SetChoice(TPC_PDCCH_Config::Enum choice)
{
    internal_choice = choice;
    present = true;
    return 0;
}

std::string TPC_PDCCH_Config::ChoiceToString(Enum value) const
{
    if(k_release == value)
        return "release";
    if(k_setup == value)
        return "setup";
    return "";
}

uint64_t TPC_PDCCH_Config::NumberOfChoices() const
{
    return 2;
}

std::string TPC_PDCCH_Config::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "TPC_PDCCH_Config = " + ChoiceToString(internal_choice) + ":\n";
    if(internal_choice == k_setup)
        out += setup_value.ToString(indent+1);
    return out;
}

std::string TPC_PDCCH_Config::ToStringNoNewLines() const
{
    std::string out = "TPC_PDCCH_Config=" + ChoiceToString(internal_choice) + ",";
    if(internal_choice == k_setup)
        out += setup_value.ToStringNoNewLines();
    return out;
}

int TPC_PDCCH_Config::Clear()
{
    present = false;
    return 0;
}

bool TPC_PDCCH_Config::IsPresent() const
{
    return present;
}

int TPC_PDCCH_Config::setup::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != tpc_RNTI_Pack(bits))
        {
            printf("TPC_PDCCH_Config::setup:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != tpc_Index.Pack(bits))
        {
            printf("TPC_PDCCH_Config::setup:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int TPC_PDCCH_Config::setup::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int TPC_PDCCH_Config::setup::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != tpc_RNTI_Unpack(bits, idx))
        {
            printf("TPC_PDCCH_Config::setup:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != tpc_Index.Unpack(bits, idx))
        {
            printf("TPC_PDCCH_Config::setup:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string TPC_PDCCH_Config::setup::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "setup:\n";
    out += tpc_RNTI_ToString(indent+1);
    out += tpc_Index_ToString(indent+1);
    return out;
}

std::string TPC_PDCCH_Config::setup::ToStringNoNewLines() const
{
    std::string out = "setup:";
    out += tpc_RNTI_ToStringNoNewLines();
    out += tpc_Index_ToStringNoNewLines();
    return out;
}

int TPC_PDCCH_Config::setup::tpc_RNTI_Pack(std::vector<uint8_t> &bits)
{
    if(!tpc_RNTI_present)
    {
        printf("TPC_PDCCH_Config::setup::tpc_RNTI_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 16;
    if(size < 16 || size > 16)
    {
        printf("TPC_PDCCH_Config::setup::tpc_RNTI_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((tpc_RNTI_internal_value >> (16-i-1)) & 1);
    return 0;
}

int TPC_PDCCH_Config::setup::tpc_RNTI_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return tpc_RNTI_Unpack(bits, idx);
}

int TPC_PDCCH_Config::setup::tpc_RNTI_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 16;
    if(size < 16 || size > 16)
    {
        printf("TPC_PDCCH_Config::setup::tpc_RNTI_Unpack() size failure\n");
        return -1;
    }
    tpc_RNTI_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("TPC_PDCCH_Config::setup::tpc_RNTI_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        tpc_RNTI_internal_value |= (uint16_t)bits[idx++] << (uint16_t)(16-i-1);
    tpc_RNTI_present = true;
    return 0;
}

uint16_t TPC_PDCCH_Config::setup::tpc_RNTI_Value() const
{
    if(tpc_RNTI_present)
        return tpc_RNTI_internal_value;
    uint16_t tmp = 0;
    return tmp;
}

int TPC_PDCCH_Config::setup::tpc_RNTI_SetValue(uint16_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 16)
    {
        printf("TPC_PDCCH_Config::setup::tpc_RNTI_SetValue() size failure\n");
        return -1;
    }
    tpc_RNTI_internal_value = value;
    tpc_RNTI_present = true;
    return 0;
}

std::string TPC_PDCCH_Config::setup::tpc_RNTI_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "tpc_RNTI = ";
    out += std::to_string(tpc_RNTI_internal_value);
    out += "\n";
    return out;
}

std::string TPC_PDCCH_Config::setup::tpc_RNTI_ToStringNoNewLines() const
{
    std::string out = "tpc_RNTI=";
    out += std::to_string(tpc_RNTI_internal_value);
    out += ",";
    return out;
}

int TPC_PDCCH_Config::setup::tpc_RNTI_Clear()
{
    tpc_RNTI_present = false;
    return 0;
}

bool TPC_PDCCH_Config::setup::tpc_RNTI_IsPresent() const
{
    return tpc_RNTI_present;
}

TPC_Index* TPC_PDCCH_Config::setup::tpc_Index_Set()
{
    tpc_Index_present = true;
    return &tpc_Index;
}

int TPC_PDCCH_Config::setup::tpc_Index_Set(TPC_Index &value)
{
    tpc_Index_present = true;
    tpc_Index = value;
    return 0;
}

const TPC_Index& TPC_PDCCH_Config::setup::tpc_Index_Get() const
{
    return tpc_Index;
}

std::string TPC_PDCCH_Config::setup::tpc_Index_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "tpc_Index:\n";
    out += tpc_Index.ToString(indent+1);
    return out;
}

std::string TPC_PDCCH_Config::setup::tpc_Index_ToStringNoNewLines() const
{
    std::string out = "tpc_Index:";
    out += tpc_Index.ToStringNoNewLines();
    return out;
}

int TPC_PDCCH_Config::setup::tpc_Index_Clear()
{
    tpc_Index_present = false;
    return 0;
}

bool TPC_PDCCH_Config::setup::tpc_Index_IsPresent() const
{
    return tpc_Index_present;
}

