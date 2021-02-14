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

#include "PagingUE_Identity.h"

#include <cmath>

int PagingUE_Identity::Pack(std::vector<uint8_t> &bits)
{
    if(!present)
    {
        printf("PagingUE_Identity::Pack() presence failure\n");
        return -1;
    }
    // Extension indicator
    bits.push_back(0);

    // Choice
    for(uint32_t i=0; i<1; i++)
        bits.push_back((internal_choice >> (1-i-1)) & 1);

    // Fields
    if(internal_choice == k_s_TMSI)
    {
        if(0 != s_TMSI.Pack(bits))
        {
            printf("PagingUE_Identity::s_TMSI pack failure\n");
            return -1;
        }
    }
    if(internal_choice == k_imsi)
    {
        if(0 != imsi.Pack(bits))
        {
            printf("PagingUE_Identity::imsi pack failure\n");
            return -1;
        }
    }
    return 0;
}

int PagingUE_Identity::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int PagingUE_Identity::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("PagingUE_Identity::Unpack() index out of bounds for extension\n");
        return -1;
    }
    idx++;

    // Choice
    uint32_t packed_val = 0;
    if((idx + 1) > bits.size())
    {
        printf("PagingUE_Identity::Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<1; i++)
        packed_val |= bits[idx++] << (1-i-1);

    if((PagingUE_Identity::Enum)packed_val > k_imsi)
    {
        printf("PagingUE_Identity::Unpack() choice range failure\n");
        return -1;
    }
    internal_choice = (PagingUE_Identity::Enum)packed_val;
    present = true;

    // Fields
    if(internal_choice == k_s_TMSI)
    {
        if(0 != s_TMSI.Unpack(bits, idx))
        {
            printf("PagingUE_Identity::s_TMSI unpack failure\n");
            return -1;
        }
    }
    if(internal_choice == k_imsi)
    {
        if(0 != imsi.Unpack(bits, idx))
        {
            printf("PagingUE_Identity::imsi unpack failure\n");
            return -1;
        }
    }
    return 0;
}

PagingUE_Identity::Enum PagingUE_Identity::Choice() const
{
    if(present)
        return internal_choice;
    return (PagingUE_Identity::Enum)0;
}

int PagingUE_Identity::SetChoice(PagingUE_Identity::Enum choice)
{
    internal_choice = choice;
    present = true;
    return 0;
}

std::string PagingUE_Identity::ChoiceToString(Enum value) const
{
    if(k_s_TMSI == value)
        return "s_TMSI";
    if(k_imsi == value)
        return "imsi";
    return "";
}

uint64_t PagingUE_Identity::NumberOfChoices() const
{
    return 2;
}

std::string PagingUE_Identity::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "PagingUE_Identity = " + ChoiceToString(internal_choice) + ":\n";
    if(internal_choice == k_s_TMSI)
        out += s_TMSI.ToString(indent+1);
    if(internal_choice == k_imsi)
        out += imsi.ToString(indent+1);
    return out;
}

std::string PagingUE_Identity::ToStringNoNewLines() const
{
    std::string out = "PagingUE_Identity=" + ChoiceToString(internal_choice) + ",";
    if(internal_choice == k_s_TMSI)
        out += s_TMSI.ToStringNoNewLines();
    if(internal_choice == k_imsi)
        out += imsi.ToStringNoNewLines();
    return out;
}

int PagingUE_Identity::Clear()
{
    present = false;
    return 0;
}

bool PagingUE_Identity::IsPresent() const
{
    return present;
}

S_TMSI* PagingUE_Identity::s_TMSI_Set()
{
    s_TMSI_present = true;
    return &s_TMSI;
}

int PagingUE_Identity::s_TMSI_Set(S_TMSI &value)
{
    s_TMSI_present = true;
    s_TMSI = value;
    return 0;
}

const S_TMSI& PagingUE_Identity::s_TMSI_Get() const
{
    return s_TMSI;
}

std::string PagingUE_Identity::s_TMSI_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "s_TMSI:\n";
    out += s_TMSI.ToString(indent+1);
    return out;
}

std::string PagingUE_Identity::s_TMSI_ToStringNoNewLines() const
{
    std::string out = "s_TMSI:";
    out += s_TMSI.ToStringNoNewLines();
    return out;
}

int PagingUE_Identity::s_TMSI_Clear()
{
    s_TMSI_present = false;
    return 0;
}

bool PagingUE_Identity::s_TMSI_IsPresent() const
{
    return s_TMSI_present;
}

IMSI* PagingUE_Identity::imsi_Set()
{
    imsi_present = true;
    return &imsi;
}

int PagingUE_Identity::imsi_Set(IMSI &value)
{
    imsi_present = true;
    imsi = value;
    return 0;
}

const IMSI& PagingUE_Identity::imsi_Get() const
{
    return imsi;
}

std::string PagingUE_Identity::imsi_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "imsi:\n";
    out += imsi.ToString(indent+1);
    return out;
}

std::string PagingUE_Identity::imsi_ToStringNoNewLines() const
{
    std::string out = "imsi:";
    out += imsi.ToStringNoNewLines();
    return out;
}

int PagingUE_Identity::imsi_Clear()
{
    imsi_present = false;
    return 0;
}

bool PagingUE_Identity::imsi_IsPresent() const
{
    return imsi_present;
}

