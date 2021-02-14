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

#include "ThresholdEUTRA.h"

#include <cmath>

int ThresholdEUTRA::Pack(std::vector<uint8_t> &bits)
{
    if(!present)
    {
        printf("ThresholdEUTRA::Pack() presence failure\n");
        return -1;
    }
    // Extension indicator

    // Choice
    for(uint32_t i=0; i<1; i++)
        bits.push_back((internal_choice >> (1-i-1)) & 1);

    // Fields
    if(internal_choice == k_threshold_RSRP)
    {
        if(0 != threshold_RSRP.Pack(bits))
        {
            printf("ThresholdEUTRA::threshold_RSRP pack failure\n");
            return -1;
        }
    }
    if(internal_choice == k_threshold_RSRQ)
    {
        if(0 != threshold_RSRQ.Pack(bits))
        {
            printf("ThresholdEUTRA::threshold_RSRQ pack failure\n");
            return -1;
        }
    }
    return 0;
}

int ThresholdEUTRA::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int ThresholdEUTRA::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 1) > bits.size())
    {
        printf("ThresholdEUTRA::Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<1; i++)
        packed_val |= bits[idx++] << (1-i-1);

    if((ThresholdEUTRA::Enum)packed_val > k_threshold_RSRQ)
    {
        printf("ThresholdEUTRA::Unpack() choice range failure\n");
        return -1;
    }
    internal_choice = (ThresholdEUTRA::Enum)packed_val;
    present = true;

    // Fields
    if(internal_choice == k_threshold_RSRP)
    {
        if(0 != threshold_RSRP.Unpack(bits, idx))
        {
            printf("ThresholdEUTRA::threshold_RSRP unpack failure\n");
            return -1;
        }
    }
    if(internal_choice == k_threshold_RSRQ)
    {
        if(0 != threshold_RSRQ.Unpack(bits, idx))
        {
            printf("ThresholdEUTRA::threshold_RSRQ unpack failure\n");
            return -1;
        }
    }
    return 0;
}

ThresholdEUTRA::Enum ThresholdEUTRA::Choice() const
{
    if(present)
        return internal_choice;
    return (ThresholdEUTRA::Enum)0;
}

int ThresholdEUTRA::SetChoice(ThresholdEUTRA::Enum choice)
{
    internal_choice = choice;
    present = true;
    return 0;
}

std::string ThresholdEUTRA::ChoiceToString(Enum value) const
{
    if(k_threshold_RSRP == value)
        return "threshold_RSRP";
    if(k_threshold_RSRQ == value)
        return "threshold_RSRQ";
    return "";
}

uint64_t ThresholdEUTRA::NumberOfChoices() const
{
    return 2;
}

std::string ThresholdEUTRA::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ThresholdEUTRA = " + ChoiceToString(internal_choice) + ":\n";
    if(internal_choice == k_threshold_RSRP)
        out += threshold_RSRP.ToString(indent+1);
    if(internal_choice == k_threshold_RSRQ)
        out += threshold_RSRQ.ToString(indent+1);
    return out;
}

std::string ThresholdEUTRA::ToStringNoNewLines() const
{
    std::string out = "ThresholdEUTRA=" + ChoiceToString(internal_choice) + ",";
    if(internal_choice == k_threshold_RSRP)
        out += threshold_RSRP.ToStringNoNewLines();
    if(internal_choice == k_threshold_RSRQ)
        out += threshold_RSRQ.ToStringNoNewLines();
    return out;
}

int ThresholdEUTRA::Clear()
{
    present = false;
    return 0;
}

bool ThresholdEUTRA::IsPresent() const
{
    return present;
}

RSRP_Range* ThresholdEUTRA::threshold_RSRP_Set()
{
    threshold_RSRP_present = true;
    return &threshold_RSRP;
}

int ThresholdEUTRA::threshold_RSRP_Set(RSRP_Range &value)
{
    threshold_RSRP_present = true;
    threshold_RSRP = value;
    return 0;
}

const RSRP_Range& ThresholdEUTRA::threshold_RSRP_Get() const
{
    return threshold_RSRP;
}

std::string ThresholdEUTRA::threshold_RSRP_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "threshold_RSRP:\n";
    out += threshold_RSRP.ToString(indent+1);
    return out;
}

std::string ThresholdEUTRA::threshold_RSRP_ToStringNoNewLines() const
{
    std::string out = "threshold_RSRP:";
    out += threshold_RSRP.ToStringNoNewLines();
    return out;
}

int ThresholdEUTRA::threshold_RSRP_Clear()
{
    threshold_RSRP_present = false;
    return 0;
}

bool ThresholdEUTRA::threshold_RSRP_IsPresent() const
{
    return threshold_RSRP_present;
}

RSRQ_Range* ThresholdEUTRA::threshold_RSRQ_Set()
{
    threshold_RSRQ_present = true;
    return &threshold_RSRQ;
}

int ThresholdEUTRA::threshold_RSRQ_Set(RSRQ_Range &value)
{
    threshold_RSRQ_present = true;
    threshold_RSRQ = value;
    return 0;
}

const RSRQ_Range& ThresholdEUTRA::threshold_RSRQ_Get() const
{
    return threshold_RSRQ;
}

std::string ThresholdEUTRA::threshold_RSRQ_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "threshold_RSRQ:\n";
    out += threshold_RSRQ.ToString(indent+1);
    return out;
}

std::string ThresholdEUTRA::threshold_RSRQ_ToStringNoNewLines() const
{
    std::string out = "threshold_RSRQ:";
    out += threshold_RSRQ.ToStringNoNewLines();
    return out;
}

int ThresholdEUTRA::threshold_RSRQ_Clear()
{
    threshold_RSRQ_present = false;
    return 0;
}

bool ThresholdEUTRA::threshold_RSRQ_IsPresent() const
{
    return threshold_RSRQ_present;
}

