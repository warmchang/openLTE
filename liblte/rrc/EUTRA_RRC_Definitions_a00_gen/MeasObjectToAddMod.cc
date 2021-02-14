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

#include "MeasObjectToAddMod.h"

#include <cmath>

int MeasObjectToAddMod::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != measObjectId.Pack(bits))
        {
            printf("MeasObjectToAddMod:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != measObject_Pack(bits))
        {
            printf("MeasObjectToAddMod:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int MeasObjectToAddMod::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int MeasObjectToAddMod::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != measObjectId.Unpack(bits, idx))
        {
            printf("MeasObjectToAddMod:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != measObject_Unpack(bits, idx))
        {
            printf("MeasObjectToAddMod:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string MeasObjectToAddMod::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "MeasObjectToAddMod:\n";
    out += measObjectId_ToString(indent+1);
    out += measObject_ToString(indent+1);
    return out;
}

std::string MeasObjectToAddMod::ToStringNoNewLines() const
{
    std::string out = "MeasObjectToAddMod:";
    out += measObjectId_ToStringNoNewLines();
    out += measObject_ToStringNoNewLines();
    return out;
}

MeasObjectId* MeasObjectToAddMod::measObjectId_Set()
{
    measObjectId_present = true;
    return &measObjectId;
}

int MeasObjectToAddMod::measObjectId_Set(MeasObjectId &value)
{
    measObjectId_present = true;
    measObjectId = value;
    return 0;
}

const MeasObjectId& MeasObjectToAddMod::measObjectId_Get() const
{
    return measObjectId;
}

std::string MeasObjectToAddMod::measObjectId_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "measObjectId:\n";
    out += measObjectId.ToString(indent+1);
    return out;
}

std::string MeasObjectToAddMod::measObjectId_ToStringNoNewLines() const
{
    std::string out = "measObjectId:";
    out += measObjectId.ToStringNoNewLines();
    return out;
}

int MeasObjectToAddMod::measObjectId_Clear()
{
    measObjectId_present = false;
    return 0;
}

bool MeasObjectToAddMod::measObjectId_IsPresent() const
{
    return measObjectId_present;
}

int MeasObjectToAddMod::measObject_Pack(std::vector<uint8_t> &bits)
{
    if(!measObject_present)
    {
        printf("MeasObjectToAddMod::measObject_Pack() presence failure\n");
        return -1;
    }
    // Extension indicator
    bits.push_back(0);

    // Choice
    for(uint32_t i=0; i<2; i++)
        bits.push_back((measObject_internal_choice >> (2-i-1)) & 1);

    // Fields
    if(measObject_internal_choice == k_measObject_measObjectEUTRA)
    {
        if(0 != measObject_measObjectEUTRA.Pack(bits))
        {
            printf("MeasObjectToAddMod::measObject_measObjectEUTRA pack failure\n");
            return -1;
        }
    }
    if(measObject_internal_choice == k_measObject_measObjectUTRA)
    {
        if(0 != measObject_measObjectUTRA.Pack(bits))
        {
            printf("MeasObjectToAddMod::measObject_measObjectUTRA pack failure\n");
            return -1;
        }
    }
    if(measObject_internal_choice == k_measObject_measObjectGERAN)
    {
        if(0 != measObject_measObjectGERAN.Pack(bits))
        {
            printf("MeasObjectToAddMod::measObject_measObjectGERAN pack failure\n");
            return -1;
        }
    }
    if(measObject_internal_choice == k_measObject_measObjectCDMA2000)
    {
        if(0 != measObject_measObjectCDMA2000.Pack(bits))
        {
            printf("MeasObjectToAddMod::measObject_measObjectCDMA2000 pack failure\n");
            return -1;
        }
    }
    return 0;
}

int MeasObjectToAddMod::measObject_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return measObject_Unpack(bits, idx);
}

int MeasObjectToAddMod::measObject_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("MeasObjectToAddMod::measObject_Unpack() index out of bounds for extension\n");
        return -1;
    }
    idx++;

    // Choice
    uint32_t packed_val = 0;
    if((idx + 2) > bits.size())
    {
        printf("MeasObjectToAddMod::measObject_Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<2; i++)
        packed_val |= bits[idx++] << (2-i-1);

    if((MeasObjectToAddMod::measObject_Enum)packed_val > k_measObject_measObjectCDMA2000)
    {
        printf("MeasObjectToAddMod::measObject_Unpack() choice range failure\n");
        return -1;
    }
    measObject_internal_choice = (MeasObjectToAddMod::measObject_Enum)packed_val;
    measObject_present = true;

    // Fields
    if(measObject_internal_choice == k_measObject_measObjectEUTRA)
    {
        if(0 != measObject_measObjectEUTRA.Unpack(bits, idx))
        {
            printf("MeasObjectToAddMod::measObject_measObjectEUTRA unpack failure\n");
            return -1;
        }
    }
    if(measObject_internal_choice == k_measObject_measObjectUTRA)
    {
        if(0 != measObject_measObjectUTRA.Unpack(bits, idx))
        {
            printf("MeasObjectToAddMod::measObject_measObjectUTRA unpack failure\n");
            return -1;
        }
    }
    if(measObject_internal_choice == k_measObject_measObjectGERAN)
    {
        if(0 != measObject_measObjectGERAN.Unpack(bits, idx))
        {
            printf("MeasObjectToAddMod::measObject_measObjectGERAN unpack failure\n");
            return -1;
        }
    }
    if(measObject_internal_choice == k_measObject_measObjectCDMA2000)
    {
        if(0 != measObject_measObjectCDMA2000.Unpack(bits, idx))
        {
            printf("MeasObjectToAddMod::measObject_measObjectCDMA2000 unpack failure\n");
            return -1;
        }
    }
    return 0;
}

MeasObjectToAddMod::measObject_Enum MeasObjectToAddMod::measObject_Choice() const
{
    if(measObject_present)
        return measObject_internal_choice;
    return (MeasObjectToAddMod::measObject_Enum)0;
}

int MeasObjectToAddMod::measObject_SetChoice(MeasObjectToAddMod::measObject_Enum choice)
{
    measObject_internal_choice = choice;
    measObject_present = true;
    return 0;
}

std::string MeasObjectToAddMod::measObject_ChoiceToString(measObject_Enum value) const
{
    if(k_measObject_measObjectEUTRA == value)
        return "measObject_measObjectEUTRA";
    if(k_measObject_measObjectUTRA == value)
        return "measObject_measObjectUTRA";
    if(k_measObject_measObjectGERAN == value)
        return "measObject_measObjectGERAN";
    if(k_measObject_measObjectCDMA2000 == value)
        return "measObject_measObjectCDMA2000";
    return "";
}

uint64_t MeasObjectToAddMod::measObject_NumberOfChoices() const
{
    return 4;
}

std::string MeasObjectToAddMod::measObject_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "measObject = " + measObject_ChoiceToString(measObject_internal_choice) + ":\n";
    if(measObject_internal_choice == k_measObject_measObjectEUTRA)
        out += measObject_measObjectEUTRA.ToString(indent+1);
    if(measObject_internal_choice == k_measObject_measObjectUTRA)
        out += measObject_measObjectUTRA.ToString(indent+1);
    if(measObject_internal_choice == k_measObject_measObjectGERAN)
        out += measObject_measObjectGERAN.ToString(indent+1);
    if(measObject_internal_choice == k_measObject_measObjectCDMA2000)
        out += measObject_measObjectCDMA2000.ToString(indent+1);
    return out;
}

std::string MeasObjectToAddMod::measObject_ToStringNoNewLines() const
{
    std::string out = "measObject=" + measObject_ChoiceToString(measObject_internal_choice) + ",";
    if(measObject_internal_choice == k_measObject_measObjectEUTRA)
        out += measObject_measObjectEUTRA.ToStringNoNewLines();
    if(measObject_internal_choice == k_measObject_measObjectUTRA)
        out += measObject_measObjectUTRA.ToStringNoNewLines();
    if(measObject_internal_choice == k_measObject_measObjectGERAN)
        out += measObject_measObjectGERAN.ToStringNoNewLines();
    if(measObject_internal_choice == k_measObject_measObjectCDMA2000)
        out += measObject_measObjectCDMA2000.ToStringNoNewLines();
    return out;
}

int MeasObjectToAddMod::measObject_Clear()
{
    measObject_present = false;
    return 0;
}

bool MeasObjectToAddMod::measObject_IsPresent() const
{
    return measObject_present;
}

MeasObjectEUTRA* MeasObjectToAddMod::measObject_measObjectEUTRA_Set()
{
    measObject_measObjectEUTRA_present = true;
    return &measObject_measObjectEUTRA;
}

int MeasObjectToAddMod::measObject_measObjectEUTRA_Set(MeasObjectEUTRA &value)
{
    measObject_measObjectEUTRA_present = true;
    measObject_measObjectEUTRA = value;
    return 0;
}

const MeasObjectEUTRA& MeasObjectToAddMod::measObject_measObjectEUTRA_Get() const
{
    return measObject_measObjectEUTRA;
}

std::string MeasObjectToAddMod::measObject_measObjectEUTRA_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "measObjectEUTRA:\n";
    out += measObject_measObjectEUTRA.ToString(indent+1);
    return out;
}

std::string MeasObjectToAddMod::measObject_measObjectEUTRA_ToStringNoNewLines() const
{
    std::string out = "measObjectEUTRA:";
    out += measObject_measObjectEUTRA.ToStringNoNewLines();
    return out;
}

int MeasObjectToAddMod::measObject_measObjectEUTRA_Clear()
{
    measObject_measObjectEUTRA_present = false;
    return 0;
}

bool MeasObjectToAddMod::measObject_measObjectEUTRA_IsPresent() const
{
    return measObject_measObjectEUTRA_present;
}

MeasObjectUTRA* MeasObjectToAddMod::measObject_measObjectUTRA_Set()
{
    measObject_measObjectUTRA_present = true;
    return &measObject_measObjectUTRA;
}

int MeasObjectToAddMod::measObject_measObjectUTRA_Set(MeasObjectUTRA &value)
{
    measObject_measObjectUTRA_present = true;
    measObject_measObjectUTRA = value;
    return 0;
}

const MeasObjectUTRA& MeasObjectToAddMod::measObject_measObjectUTRA_Get() const
{
    return measObject_measObjectUTRA;
}

std::string MeasObjectToAddMod::measObject_measObjectUTRA_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "measObjectUTRA:\n";
    out += measObject_measObjectUTRA.ToString(indent+1);
    return out;
}

std::string MeasObjectToAddMod::measObject_measObjectUTRA_ToStringNoNewLines() const
{
    std::string out = "measObjectUTRA:";
    out += measObject_measObjectUTRA.ToStringNoNewLines();
    return out;
}

int MeasObjectToAddMod::measObject_measObjectUTRA_Clear()
{
    measObject_measObjectUTRA_present = false;
    return 0;
}

bool MeasObjectToAddMod::measObject_measObjectUTRA_IsPresent() const
{
    return measObject_measObjectUTRA_present;
}

MeasObjectGERAN* MeasObjectToAddMod::measObject_measObjectGERAN_Set()
{
    measObject_measObjectGERAN_present = true;
    return &measObject_measObjectGERAN;
}

int MeasObjectToAddMod::measObject_measObjectGERAN_Set(MeasObjectGERAN &value)
{
    measObject_measObjectGERAN_present = true;
    measObject_measObjectGERAN = value;
    return 0;
}

const MeasObjectGERAN& MeasObjectToAddMod::measObject_measObjectGERAN_Get() const
{
    return measObject_measObjectGERAN;
}

std::string MeasObjectToAddMod::measObject_measObjectGERAN_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "measObjectGERAN:\n";
    out += measObject_measObjectGERAN.ToString(indent+1);
    return out;
}

std::string MeasObjectToAddMod::measObject_measObjectGERAN_ToStringNoNewLines() const
{
    std::string out = "measObjectGERAN:";
    out += measObject_measObjectGERAN.ToStringNoNewLines();
    return out;
}

int MeasObjectToAddMod::measObject_measObjectGERAN_Clear()
{
    measObject_measObjectGERAN_present = false;
    return 0;
}

bool MeasObjectToAddMod::measObject_measObjectGERAN_IsPresent() const
{
    return measObject_measObjectGERAN_present;
}

MeasObjectCDMA2000* MeasObjectToAddMod::measObject_measObjectCDMA2000_Set()
{
    measObject_measObjectCDMA2000_present = true;
    return &measObject_measObjectCDMA2000;
}

int MeasObjectToAddMod::measObject_measObjectCDMA2000_Set(MeasObjectCDMA2000 &value)
{
    measObject_measObjectCDMA2000_present = true;
    measObject_measObjectCDMA2000 = value;
    return 0;
}

const MeasObjectCDMA2000& MeasObjectToAddMod::measObject_measObjectCDMA2000_Get() const
{
    return measObject_measObjectCDMA2000;
}

std::string MeasObjectToAddMod::measObject_measObjectCDMA2000_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "measObjectCDMA2000:\n";
    out += measObject_measObjectCDMA2000.ToString(indent+1);
    return out;
}

std::string MeasObjectToAddMod::measObject_measObjectCDMA2000_ToStringNoNewLines() const
{
    std::string out = "measObjectCDMA2000:";
    out += measObject_measObjectCDMA2000.ToStringNoNewLines();
    return out;
}

int MeasObjectToAddMod::measObject_measObjectCDMA2000_Clear()
{
    measObject_measObjectCDMA2000_present = false;
    return 0;
}

bool MeasObjectToAddMod::measObject_measObjectCDMA2000_IsPresent() const
{
    return measObject_measObjectCDMA2000_present;
}

