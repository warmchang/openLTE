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

#include "RLC_Config.h"

#include <cmath>

int RLC_Config::Pack(std::vector<uint8_t> &bits)
{
    if(!present)
    {
        printf("RLC_Config::Pack() presence failure\n");
        return -1;
    }
    // Extension indicator
    bits.push_back(0);

    // Choice
    for(uint32_t i=0; i<2; i++)
        bits.push_back((internal_choice >> (2-i-1)) & 1);

    // Fields
    if(internal_choice == k_am)
    {
        if(0 != am_value.Pack(bits))
        {
            printf("RLC_Config::am pack failure\n");
            return -1;
        }
    }
    if(internal_choice == k_um_Bi_Directional)
    {
        if(0 != um_Bi_Directional_value.Pack(bits))
        {
            printf("RLC_Config::um_Bi_Directional pack failure\n");
            return -1;
        }
    }
    if(internal_choice == k_um_Uni_Directional_UL)
    {
        if(0 != um_Uni_Directional_UL_value.Pack(bits))
        {
            printf("RLC_Config::um_Uni_Directional_UL pack failure\n");
            return -1;
        }
    }
    if(internal_choice == k_um_Uni_Directional_DL)
    {
        if(0 != um_Uni_Directional_DL_value.Pack(bits))
        {
            printf("RLC_Config::um_Uni_Directional_DL pack failure\n");
            return -1;
        }
    }
    return 0;
}

int RLC_Config::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int RLC_Config::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("RLC_Config::Unpack() index out of bounds for extension\n");
        return -1;
    }
    idx++;

    // Choice
    uint32_t packed_val = 0;
    if((idx + 2) > bits.size())
    {
        printf("RLC_Config::Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<2; i++)
        packed_val |= bits[idx++] << (2-i-1);

    if((RLC_Config::Enum)packed_val > k_um_Uni_Directional_DL)
    {
        printf("RLC_Config::Unpack() choice range failure\n");
        return -1;
    }
    internal_choice = (RLC_Config::Enum)packed_val;
    present = true;

    // Fields
    if(internal_choice == k_am)
    {
        if(0 != am_value.Unpack(bits, idx))
        {
            printf("RLC_Config::am unpack failure\n");
            return -1;
        }
    }
    if(internal_choice == k_um_Bi_Directional)
    {
        if(0 != um_Bi_Directional_value.Unpack(bits, idx))
        {
            printf("RLC_Config::um_Bi_Directional unpack failure\n");
            return -1;
        }
    }
    if(internal_choice == k_um_Uni_Directional_UL)
    {
        if(0 != um_Uni_Directional_UL_value.Unpack(bits, idx))
        {
            printf("RLC_Config::um_Uni_Directional_UL unpack failure\n");
            return -1;
        }
    }
    if(internal_choice == k_um_Uni_Directional_DL)
    {
        if(0 != um_Uni_Directional_DL_value.Unpack(bits, idx))
        {
            printf("RLC_Config::um_Uni_Directional_DL unpack failure\n");
            return -1;
        }
    }
    return 0;
}

RLC_Config::Enum RLC_Config::Choice() const
{
    if(present)
        return internal_choice;
    return (RLC_Config::Enum)0;
}

int RLC_Config::SetChoice(RLC_Config::Enum choice)
{
    internal_choice = choice;
    present = true;
    return 0;
}

std::string RLC_Config::ChoiceToString(Enum value) const
{
    if(k_am == value)
        return "am";
    if(k_um_Bi_Directional == value)
        return "um_Bi_Directional";
    if(k_um_Uni_Directional_UL == value)
        return "um_Uni_Directional_UL";
    if(k_um_Uni_Directional_DL == value)
        return "um_Uni_Directional_DL";
    return "";
}

uint64_t RLC_Config::NumberOfChoices() const
{
    return 4;
}

std::string RLC_Config::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "RLC_Config = " + ChoiceToString(internal_choice) + ":\n";
    if(internal_choice == k_am)
        out += am_value.ToString(indent+1);
    if(internal_choice == k_um_Bi_Directional)
        out += um_Bi_Directional_value.ToString(indent+1);
    if(internal_choice == k_um_Uni_Directional_UL)
        out += um_Uni_Directional_UL_value.ToString(indent+1);
    if(internal_choice == k_um_Uni_Directional_DL)
        out += um_Uni_Directional_DL_value.ToString(indent+1);
    return out;
}

std::string RLC_Config::ToStringNoNewLines() const
{
    std::string out = "RLC_Config=" + ChoiceToString(internal_choice) + ",";
    if(internal_choice == k_am)
        out += am_value.ToStringNoNewLines();
    if(internal_choice == k_um_Bi_Directional)
        out += um_Bi_Directional_value.ToStringNoNewLines();
    if(internal_choice == k_um_Uni_Directional_UL)
        out += um_Uni_Directional_UL_value.ToStringNoNewLines();
    if(internal_choice == k_um_Uni_Directional_DL)
        out += um_Uni_Directional_DL_value.ToStringNoNewLines();
    return out;
}

int RLC_Config::Clear()
{
    present = false;
    return 0;
}

bool RLC_Config::IsPresent() const
{
    return present;
}

int RLC_Config::am::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != ul_AM_RLC.Pack(bits))
        {
            printf("RLC_Config::am:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != dl_AM_RLC.Pack(bits))
        {
            printf("RLC_Config::am:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int RLC_Config::am::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int RLC_Config::am::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != ul_AM_RLC.Unpack(bits, idx))
        {
            printf("RLC_Config::am:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != dl_AM_RLC.Unpack(bits, idx))
        {
            printf("RLC_Config::am:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string RLC_Config::am::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "am:\n";
    out += ul_AM_RLC_ToString(indent+1);
    out += dl_AM_RLC_ToString(indent+1);
    return out;
}

std::string RLC_Config::am::ToStringNoNewLines() const
{
    std::string out = "am:";
    out += ul_AM_RLC_ToStringNoNewLines();
    out += dl_AM_RLC_ToStringNoNewLines();
    return out;
}

UL_AM_RLC* RLC_Config::am::ul_AM_RLC_Set()
{
    ul_AM_RLC_present = true;
    return &ul_AM_RLC;
}

int RLC_Config::am::ul_AM_RLC_Set(UL_AM_RLC &value)
{
    ul_AM_RLC_present = true;
    ul_AM_RLC = value;
    return 0;
}

const UL_AM_RLC& RLC_Config::am::ul_AM_RLC_Get() const
{
    return ul_AM_RLC;
}

std::string RLC_Config::am::ul_AM_RLC_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ul_AM_RLC:\n";
    out += ul_AM_RLC.ToString(indent+1);
    return out;
}

std::string RLC_Config::am::ul_AM_RLC_ToStringNoNewLines() const
{
    std::string out = "ul_AM_RLC:";
    out += ul_AM_RLC.ToStringNoNewLines();
    return out;
}

int RLC_Config::am::ul_AM_RLC_Clear()
{
    ul_AM_RLC_present = false;
    return 0;
}

bool RLC_Config::am::ul_AM_RLC_IsPresent() const
{
    return ul_AM_RLC_present;
}

DL_AM_RLC* RLC_Config::am::dl_AM_RLC_Set()
{
    dl_AM_RLC_present = true;
    return &dl_AM_RLC;
}

int RLC_Config::am::dl_AM_RLC_Set(DL_AM_RLC &value)
{
    dl_AM_RLC_present = true;
    dl_AM_RLC = value;
    return 0;
}

const DL_AM_RLC& RLC_Config::am::dl_AM_RLC_Get() const
{
    return dl_AM_RLC;
}

std::string RLC_Config::am::dl_AM_RLC_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "dl_AM_RLC:\n";
    out += dl_AM_RLC.ToString(indent+1);
    return out;
}

std::string RLC_Config::am::dl_AM_RLC_ToStringNoNewLines() const
{
    std::string out = "dl_AM_RLC:";
    out += dl_AM_RLC.ToStringNoNewLines();
    return out;
}

int RLC_Config::am::dl_AM_RLC_Clear()
{
    dl_AM_RLC_present = false;
    return 0;
}

bool RLC_Config::am::dl_AM_RLC_IsPresent() const
{
    return dl_AM_RLC_present;
}

int RLC_Config::um_Bi_Directional::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != ul_UM_RLC.Pack(bits))
        {
            printf("RLC_Config::um_Bi_Directional:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != dl_UM_RLC.Pack(bits))
        {
            printf("RLC_Config::um_Bi_Directional:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int RLC_Config::um_Bi_Directional::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int RLC_Config::um_Bi_Directional::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != ul_UM_RLC.Unpack(bits, idx))
        {
            printf("RLC_Config::um_Bi_Directional:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != dl_UM_RLC.Unpack(bits, idx))
        {
            printf("RLC_Config::um_Bi_Directional:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string RLC_Config::um_Bi_Directional::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "um_Bi_Directional:\n";
    out += ul_UM_RLC_ToString(indent+1);
    out += dl_UM_RLC_ToString(indent+1);
    return out;
}

std::string RLC_Config::um_Bi_Directional::ToStringNoNewLines() const
{
    std::string out = "um_Bi_Directional:";
    out += ul_UM_RLC_ToStringNoNewLines();
    out += dl_UM_RLC_ToStringNoNewLines();
    return out;
}

UL_UM_RLC* RLC_Config::um_Bi_Directional::ul_UM_RLC_Set()
{
    ul_UM_RLC_present = true;
    return &ul_UM_RLC;
}

int RLC_Config::um_Bi_Directional::ul_UM_RLC_Set(UL_UM_RLC &value)
{
    ul_UM_RLC_present = true;
    ul_UM_RLC = value;
    return 0;
}

const UL_UM_RLC& RLC_Config::um_Bi_Directional::ul_UM_RLC_Get() const
{
    return ul_UM_RLC;
}

std::string RLC_Config::um_Bi_Directional::ul_UM_RLC_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ul_UM_RLC:\n";
    out += ul_UM_RLC.ToString(indent+1);
    return out;
}

std::string RLC_Config::um_Bi_Directional::ul_UM_RLC_ToStringNoNewLines() const
{
    std::string out = "ul_UM_RLC:";
    out += ul_UM_RLC.ToStringNoNewLines();
    return out;
}

int RLC_Config::um_Bi_Directional::ul_UM_RLC_Clear()
{
    ul_UM_RLC_present = false;
    return 0;
}

bool RLC_Config::um_Bi_Directional::ul_UM_RLC_IsPresent() const
{
    return ul_UM_RLC_present;
}

DL_UM_RLC* RLC_Config::um_Bi_Directional::dl_UM_RLC_Set()
{
    dl_UM_RLC_present = true;
    return &dl_UM_RLC;
}

int RLC_Config::um_Bi_Directional::dl_UM_RLC_Set(DL_UM_RLC &value)
{
    dl_UM_RLC_present = true;
    dl_UM_RLC = value;
    return 0;
}

const DL_UM_RLC& RLC_Config::um_Bi_Directional::dl_UM_RLC_Get() const
{
    return dl_UM_RLC;
}

std::string RLC_Config::um_Bi_Directional::dl_UM_RLC_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "dl_UM_RLC:\n";
    out += dl_UM_RLC.ToString(indent+1);
    return out;
}

std::string RLC_Config::um_Bi_Directional::dl_UM_RLC_ToStringNoNewLines() const
{
    std::string out = "dl_UM_RLC:";
    out += dl_UM_RLC.ToStringNoNewLines();
    return out;
}

int RLC_Config::um_Bi_Directional::dl_UM_RLC_Clear()
{
    dl_UM_RLC_present = false;
    return 0;
}

bool RLC_Config::um_Bi_Directional::dl_UM_RLC_IsPresent() const
{
    return dl_UM_RLC_present;
}

int RLC_Config::um_Uni_Directional_UL::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != ul_UM_RLC.Pack(bits))
        {
            printf("RLC_Config::um_Uni_Directional_UL:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int RLC_Config::um_Uni_Directional_UL::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int RLC_Config::um_Uni_Directional_UL::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != ul_UM_RLC.Unpack(bits, idx))
        {
            printf("RLC_Config::um_Uni_Directional_UL:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string RLC_Config::um_Uni_Directional_UL::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "um_Uni_Directional_UL:\n";
    out += ul_UM_RLC_ToString(indent+1);
    return out;
}

std::string RLC_Config::um_Uni_Directional_UL::ToStringNoNewLines() const
{
    std::string out = "um_Uni_Directional_UL:";
    out += ul_UM_RLC_ToStringNoNewLines();
    return out;
}

UL_UM_RLC* RLC_Config::um_Uni_Directional_UL::ul_UM_RLC_Set()
{
    ul_UM_RLC_present = true;
    return &ul_UM_RLC;
}

int RLC_Config::um_Uni_Directional_UL::ul_UM_RLC_Set(UL_UM_RLC &value)
{
    ul_UM_RLC_present = true;
    ul_UM_RLC = value;
    return 0;
}

const UL_UM_RLC& RLC_Config::um_Uni_Directional_UL::ul_UM_RLC_Get() const
{
    return ul_UM_RLC;
}

std::string RLC_Config::um_Uni_Directional_UL::ul_UM_RLC_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ul_UM_RLC:\n";
    out += ul_UM_RLC.ToString(indent+1);
    return out;
}

std::string RLC_Config::um_Uni_Directional_UL::ul_UM_RLC_ToStringNoNewLines() const
{
    std::string out = "ul_UM_RLC:";
    out += ul_UM_RLC.ToStringNoNewLines();
    return out;
}

int RLC_Config::um_Uni_Directional_UL::ul_UM_RLC_Clear()
{
    ul_UM_RLC_present = false;
    return 0;
}

bool RLC_Config::um_Uni_Directional_UL::ul_UM_RLC_IsPresent() const
{
    return ul_UM_RLC_present;
}

int RLC_Config::um_Uni_Directional_DL::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != dl_UM_RLC.Pack(bits))
        {
            printf("RLC_Config::um_Uni_Directional_DL:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int RLC_Config::um_Uni_Directional_DL::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int RLC_Config::um_Uni_Directional_DL::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != dl_UM_RLC.Unpack(bits, idx))
        {
            printf("RLC_Config::um_Uni_Directional_DL:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string RLC_Config::um_Uni_Directional_DL::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "um_Uni_Directional_DL:\n";
    out += dl_UM_RLC_ToString(indent+1);
    return out;
}

std::string RLC_Config::um_Uni_Directional_DL::ToStringNoNewLines() const
{
    std::string out = "um_Uni_Directional_DL:";
    out += dl_UM_RLC_ToStringNoNewLines();
    return out;
}

DL_UM_RLC* RLC_Config::um_Uni_Directional_DL::dl_UM_RLC_Set()
{
    dl_UM_RLC_present = true;
    return &dl_UM_RLC;
}

int RLC_Config::um_Uni_Directional_DL::dl_UM_RLC_Set(DL_UM_RLC &value)
{
    dl_UM_RLC_present = true;
    dl_UM_RLC = value;
    return 0;
}

const DL_UM_RLC& RLC_Config::um_Uni_Directional_DL::dl_UM_RLC_Get() const
{
    return dl_UM_RLC;
}

std::string RLC_Config::um_Uni_Directional_DL::dl_UM_RLC_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "dl_UM_RLC:\n";
    out += dl_UM_RLC.ToString(indent+1);
    return out;
}

std::string RLC_Config::um_Uni_Directional_DL::dl_UM_RLC_ToStringNoNewLines() const
{
    std::string out = "dl_UM_RLC:";
    out += dl_UM_RLC.ToStringNoNewLines();
    return out;
}

int RLC_Config::um_Uni_Directional_DL::dl_UM_RLC_Clear()
{
    dl_UM_RLC_present = false;
    return 0;
}

bool RLC_Config::um_Uni_Directional_DL::dl_UM_RLC_IsPresent() const
{
    return dl_UM_RLC_present;
}

