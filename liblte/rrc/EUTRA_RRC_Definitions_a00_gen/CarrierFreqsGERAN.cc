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

#include "CarrierFreqsGERAN.h"

#include <cmath>

int CarrierFreqsGERAN::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != startingARFCN.Pack(bits))
        {
            printf("CarrierFreqsGERAN:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != bandIndicator.Pack(bits))
        {
            printf("CarrierFreqsGERAN:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != followingARFCNs_Pack(bits))
        {
            printf("CarrierFreqsGERAN:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int CarrierFreqsGERAN::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int CarrierFreqsGERAN::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != startingARFCN.Unpack(bits, idx))
        {
            printf("CarrierFreqsGERAN:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != bandIndicator.Unpack(bits, idx))
        {
            printf("CarrierFreqsGERAN:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != followingARFCNs_Unpack(bits, idx))
        {
            printf("CarrierFreqsGERAN:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string CarrierFreqsGERAN::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "CarrierFreqsGERAN:\n";
    out += startingARFCN_ToString(indent+1);
    out += bandIndicator_ToString(indent+1);
    out += followingARFCNs_ToString(indent+1);
    return out;
}

std::string CarrierFreqsGERAN::ToStringNoNewLines() const
{
    std::string out = "CarrierFreqsGERAN:";
    out += startingARFCN_ToStringNoNewLines();
    out += bandIndicator_ToStringNoNewLines();
    out += followingARFCNs_ToStringNoNewLines();
    return out;
}

ARFCN_ValueGERAN* CarrierFreqsGERAN::startingARFCN_Set()
{
    startingARFCN_present = true;
    return &startingARFCN;
}

int CarrierFreqsGERAN::startingARFCN_Set(ARFCN_ValueGERAN &value)
{
    startingARFCN_present = true;
    startingARFCN = value;
    return 0;
}

const ARFCN_ValueGERAN& CarrierFreqsGERAN::startingARFCN_Get() const
{
    return startingARFCN;
}

std::string CarrierFreqsGERAN::startingARFCN_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "startingARFCN:\n";
    out += startingARFCN.ToString(indent+1);
    return out;
}

std::string CarrierFreqsGERAN::startingARFCN_ToStringNoNewLines() const
{
    std::string out = "startingARFCN:";
    out += startingARFCN.ToStringNoNewLines();
    return out;
}

int CarrierFreqsGERAN::startingARFCN_Clear()
{
    startingARFCN_present = false;
    return 0;
}

bool CarrierFreqsGERAN::startingARFCN_IsPresent() const
{
    return startingARFCN_present;
}

BandIndicatorGERAN* CarrierFreqsGERAN::bandIndicator_Set()
{
    bandIndicator_present = true;
    return &bandIndicator;
}

int CarrierFreqsGERAN::bandIndicator_Set(BandIndicatorGERAN &value)
{
    bandIndicator_present = true;
    bandIndicator = value;
    return 0;
}

const BandIndicatorGERAN& CarrierFreqsGERAN::bandIndicator_Get() const
{
    return bandIndicator;
}

std::string CarrierFreqsGERAN::bandIndicator_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "bandIndicator:\n";
    out += bandIndicator.ToString(indent+1);
    return out;
}

std::string CarrierFreqsGERAN::bandIndicator_ToStringNoNewLines() const
{
    std::string out = "bandIndicator:";
    out += bandIndicator.ToStringNoNewLines();
    return out;
}

int CarrierFreqsGERAN::bandIndicator_Clear()
{
    bandIndicator_present = false;
    return 0;
}

bool CarrierFreqsGERAN::bandIndicator_IsPresent() const
{
    return bandIndicator_present;
}

int CarrierFreqsGERAN::followingARFCNs_Pack(std::vector<uint8_t> &bits)
{
    if(!followingARFCNs_present)
    {
        printf("CarrierFreqsGERAN::followingARFCNs_Pack() presence failure\n");
        return -1;
    }
    // Extension indicator

    // Choice
    for(uint32_t i=0; i<2; i++)
        bits.push_back((followingARFCNs_internal_choice >> (2-i-1)) & 1);

    // Fields
    if(followingARFCNs_internal_choice == k_followingARFCNs_explicitListOfARFCNs)
    {
        if(0 != followingARFCNs_explicitListOfARFCNs.Pack(bits))
        {
            printf("CarrierFreqsGERAN::followingARFCNs_explicitListOfARFCNs pack failure\n");
            return -1;
        }
    }
    if(followingARFCNs_internal_choice == k_followingARFCNs_equallySpacedARFCNs)
    {
        if(0 != followingARFCNs_equallySpacedARFCNs_value.Pack(bits))
        {
            printf("CarrierFreqsGERAN::followingARFCNs_equallySpacedARFCNs pack failure\n");
            return -1;
        }
    }
    if(followingARFCNs_internal_choice == k_followingARFCNs_variableBitMapOfARFCNs)
    {
        if(0 != followingARFCNs_variableBitMapOfARFCNs_Pack(bits))
        {
            printf("CarrierFreqsGERAN::followingARFCNs_variableBitMapOfARFCNs pack failure\n");
            return -1;
        }
    }
    return 0;
}

int CarrierFreqsGERAN::followingARFCNs_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return followingARFCNs_Unpack(bits, idx);
}

int CarrierFreqsGERAN::followingARFCNs_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 2) > bits.size())
    {
        printf("CarrierFreqsGERAN::followingARFCNs_Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<2; i++)
        packed_val |= bits[idx++] << (2-i-1);

    if((CarrierFreqsGERAN::followingARFCNs_Enum)packed_val > k_followingARFCNs_variableBitMapOfARFCNs)
    {
        printf("CarrierFreqsGERAN::followingARFCNs_Unpack() choice range failure\n");
        return -1;
    }
    followingARFCNs_internal_choice = (CarrierFreqsGERAN::followingARFCNs_Enum)packed_val;
    followingARFCNs_present = true;

    // Fields
    if(followingARFCNs_internal_choice == k_followingARFCNs_explicitListOfARFCNs)
    {
        if(0 != followingARFCNs_explicitListOfARFCNs.Unpack(bits, idx))
        {
            printf("CarrierFreqsGERAN::followingARFCNs_explicitListOfARFCNs unpack failure\n");
            return -1;
        }
    }
    if(followingARFCNs_internal_choice == k_followingARFCNs_equallySpacedARFCNs)
    {
        if(0 != followingARFCNs_equallySpacedARFCNs_value.Unpack(bits, idx))
        {
            printf("CarrierFreqsGERAN::followingARFCNs_equallySpacedARFCNs unpack failure\n");
            return -1;
        }
    }
    if(followingARFCNs_internal_choice == k_followingARFCNs_variableBitMapOfARFCNs)
    {
        if(0 != followingARFCNs_variableBitMapOfARFCNs_Unpack(bits, idx))
        {
            printf("CarrierFreqsGERAN::followingARFCNs_variableBitMapOfARFCNs unpack failure\n");
            return -1;
        }
    }
    return 0;
}

CarrierFreqsGERAN::followingARFCNs_Enum CarrierFreqsGERAN::followingARFCNs_Choice() const
{
    if(followingARFCNs_present)
        return followingARFCNs_internal_choice;
    return (CarrierFreqsGERAN::followingARFCNs_Enum)0;
}

int CarrierFreqsGERAN::followingARFCNs_SetChoice(CarrierFreqsGERAN::followingARFCNs_Enum choice)
{
    followingARFCNs_internal_choice = choice;
    followingARFCNs_present = true;
    return 0;
}

std::string CarrierFreqsGERAN::followingARFCNs_ChoiceToString(followingARFCNs_Enum value) const
{
    if(k_followingARFCNs_explicitListOfARFCNs == value)
        return "followingARFCNs_explicitListOfARFCNs";
    if(k_followingARFCNs_equallySpacedARFCNs == value)
        return "followingARFCNs_equallySpacedARFCNs";
    if(k_followingARFCNs_variableBitMapOfARFCNs == value)
        return "followingARFCNs_variableBitMapOfARFCNs";
    return "";
}

uint64_t CarrierFreqsGERAN::followingARFCNs_NumberOfChoices() const
{
    return 3;
}

std::string CarrierFreqsGERAN::followingARFCNs_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "followingARFCNs = " + followingARFCNs_ChoiceToString(followingARFCNs_internal_choice) + ":\n";
    if(followingARFCNs_internal_choice == k_followingARFCNs_explicitListOfARFCNs)
        out += followingARFCNs_explicitListOfARFCNs.ToString(indent+1);
    if(followingARFCNs_internal_choice == k_followingARFCNs_equallySpacedARFCNs)
        out += followingARFCNs_equallySpacedARFCNs_value.ToString(indent+1);
    if(followingARFCNs_internal_choice == k_followingARFCNs_variableBitMapOfARFCNs)
        out += followingARFCNs_variableBitMapOfARFCNs_ToString(indent+1);
    return out;
}

std::string CarrierFreqsGERAN::followingARFCNs_ToStringNoNewLines() const
{
    std::string out = "followingARFCNs=" + followingARFCNs_ChoiceToString(followingARFCNs_internal_choice) + ",";
    if(followingARFCNs_internal_choice == k_followingARFCNs_explicitListOfARFCNs)
        out += followingARFCNs_explicitListOfARFCNs.ToStringNoNewLines();
    if(followingARFCNs_internal_choice == k_followingARFCNs_equallySpacedARFCNs)
        out += followingARFCNs_equallySpacedARFCNs_value.ToStringNoNewLines();
    if(followingARFCNs_internal_choice == k_followingARFCNs_variableBitMapOfARFCNs)
        out += followingARFCNs_variableBitMapOfARFCNs_ToStringNoNewLines();
    return out;
}

int CarrierFreqsGERAN::followingARFCNs_Clear()
{
    followingARFCNs_present = false;
    return 0;
}

bool CarrierFreqsGERAN::followingARFCNs_IsPresent() const
{
    return followingARFCNs_present;
}

ExplicitListOfARFCNs* CarrierFreqsGERAN::followingARFCNs_explicitListOfARFCNs_Set()
{
    followingARFCNs_explicitListOfARFCNs_present = true;
    return &followingARFCNs_explicitListOfARFCNs;
}

int CarrierFreqsGERAN::followingARFCNs_explicitListOfARFCNs_Set(ExplicitListOfARFCNs &value)
{
    followingARFCNs_explicitListOfARFCNs_present = true;
    followingARFCNs_explicitListOfARFCNs = value;
    return 0;
}

const ExplicitListOfARFCNs& CarrierFreqsGERAN::followingARFCNs_explicitListOfARFCNs_Get() const
{
    return followingARFCNs_explicitListOfARFCNs;
}

std::string CarrierFreqsGERAN::followingARFCNs_explicitListOfARFCNs_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "explicitListOfARFCNs:\n";
    out += followingARFCNs_explicitListOfARFCNs.ToString(indent+1);
    return out;
}

std::string CarrierFreqsGERAN::followingARFCNs_explicitListOfARFCNs_ToStringNoNewLines() const
{
    std::string out = "explicitListOfARFCNs:";
    out += followingARFCNs_explicitListOfARFCNs.ToStringNoNewLines();
    return out;
}

int CarrierFreqsGERAN::followingARFCNs_explicitListOfARFCNs_Clear()
{
    followingARFCNs_explicitListOfARFCNs_present = false;
    return 0;
}

bool CarrierFreqsGERAN::followingARFCNs_explicitListOfARFCNs_IsPresent() const
{
    return followingARFCNs_explicitListOfARFCNs_present;
}

int CarrierFreqsGERAN::followingARFCNs_equallySpacedARFCNs::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != arfcn_Spacing_Pack(bits))
        {
            printf("CarrierFreqsGERAN::followingARFCNs_equallySpacedARFCNs:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != numberOfFollowingARFCNs_Pack(bits))
        {
            printf("CarrierFreqsGERAN::followingARFCNs_equallySpacedARFCNs:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int CarrierFreqsGERAN::followingARFCNs_equallySpacedARFCNs::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int CarrierFreqsGERAN::followingARFCNs_equallySpacedARFCNs::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != arfcn_Spacing_Unpack(bits, idx))
        {
            printf("CarrierFreqsGERAN::followingARFCNs_equallySpacedARFCNs:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != numberOfFollowingARFCNs_Unpack(bits, idx))
        {
            printf("CarrierFreqsGERAN::followingARFCNs_equallySpacedARFCNs:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string CarrierFreqsGERAN::followingARFCNs_equallySpacedARFCNs::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "equallySpacedARFCNs:\n";
    out += arfcn_Spacing_ToString(indent+1);
    out += numberOfFollowingARFCNs_ToString(indent+1);
    return out;
}

std::string CarrierFreqsGERAN::followingARFCNs_equallySpacedARFCNs::ToStringNoNewLines() const
{
    std::string out = "equallySpacedARFCNs:";
    out += arfcn_Spacing_ToStringNoNewLines();
    out += numberOfFollowingARFCNs_ToStringNoNewLines();
    return out;
}

int CarrierFreqsGERAN::followingARFCNs_equallySpacedARFCNs::arfcn_Spacing_Pack(std::vector<uint8_t> &bits)
{
    if(!arfcn_Spacing_present)
    {
        printf("CarrierFreqsGERAN::followingARFCNs_equallySpacedARFCNs::arfcn_Spacing_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = arfcn_Spacing_internal_value - (1);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (8 - 1))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int CarrierFreqsGERAN::followingARFCNs_equallySpacedARFCNs::arfcn_Spacing_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return arfcn_Spacing_Unpack(bits, idx);
}

int CarrierFreqsGERAN::followingARFCNs_equallySpacedARFCNs::arfcn_Spacing_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (8 - 1))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("CarrierFreqsGERAN::followingARFCNs_equallySpacedARFCNs::arfcn_Spacing_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    arfcn_Spacing_internal_value = packed_val + 1;
    arfcn_Spacing_present = true;
    return 0;
}

int64_t CarrierFreqsGERAN::followingARFCNs_equallySpacedARFCNs::arfcn_Spacing_Value() const
{
    if(arfcn_Spacing_present)
        return arfcn_Spacing_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int CarrierFreqsGERAN::followingARFCNs_equallySpacedARFCNs::arfcn_Spacing_SetValue(int64_t value)
{
    if(value < 1 || value > 8)
    {
        printf("CarrierFreqsGERAN::followingARFCNs_equallySpacedARFCNs::arfcn_Spacing_SetValue() range failure\n");
        return -1;
    }
    arfcn_Spacing_internal_value = value;
    arfcn_Spacing_present = true;
    return 0;
}

std::string CarrierFreqsGERAN::followingARFCNs_equallySpacedARFCNs::arfcn_Spacing_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "arfcn_Spacing = " + std::to_string(arfcn_Spacing_internal_value) + "\n";
    return out;
}

std::string CarrierFreqsGERAN::followingARFCNs_equallySpacedARFCNs::arfcn_Spacing_ToStringNoNewLines() const
{
    std::string out = "arfcn_Spacing=" + std::to_string(arfcn_Spacing_internal_value) + ",";
    return out;
}

int CarrierFreqsGERAN::followingARFCNs_equallySpacedARFCNs::arfcn_Spacing_Clear()
{
    arfcn_Spacing_present = false;
    return 0;
}

bool CarrierFreqsGERAN::followingARFCNs_equallySpacedARFCNs::arfcn_Spacing_IsPresent() const
{
    return arfcn_Spacing_present;
}

int CarrierFreqsGERAN::followingARFCNs_equallySpacedARFCNs::numberOfFollowingARFCNs_Pack(std::vector<uint8_t> &bits)
{
    if(!numberOfFollowingARFCNs_present)
    {
        printf("CarrierFreqsGERAN::followingARFCNs_equallySpacedARFCNs::numberOfFollowingARFCNs_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = numberOfFollowingARFCNs_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (31 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int CarrierFreqsGERAN::followingARFCNs_equallySpacedARFCNs::numberOfFollowingARFCNs_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return numberOfFollowingARFCNs_Unpack(bits, idx);
}

int CarrierFreqsGERAN::followingARFCNs_equallySpacedARFCNs::numberOfFollowingARFCNs_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (31 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("CarrierFreqsGERAN::followingARFCNs_equallySpacedARFCNs::numberOfFollowingARFCNs_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    numberOfFollowingARFCNs_internal_value = packed_val + 0;
    numberOfFollowingARFCNs_present = true;
    return 0;
}

int64_t CarrierFreqsGERAN::followingARFCNs_equallySpacedARFCNs::numberOfFollowingARFCNs_Value() const
{
    if(numberOfFollowingARFCNs_present)
        return numberOfFollowingARFCNs_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int CarrierFreqsGERAN::followingARFCNs_equallySpacedARFCNs::numberOfFollowingARFCNs_SetValue(int64_t value)
{
    if(value < 0 || value > 31)
    {
        printf("CarrierFreqsGERAN::followingARFCNs_equallySpacedARFCNs::numberOfFollowingARFCNs_SetValue() range failure\n");
        return -1;
    }
    numberOfFollowingARFCNs_internal_value = value;
    numberOfFollowingARFCNs_present = true;
    return 0;
}

std::string CarrierFreqsGERAN::followingARFCNs_equallySpacedARFCNs::numberOfFollowingARFCNs_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "numberOfFollowingARFCNs = " + std::to_string(numberOfFollowingARFCNs_internal_value) + "\n";
    return out;
}

std::string CarrierFreqsGERAN::followingARFCNs_equallySpacedARFCNs::numberOfFollowingARFCNs_ToStringNoNewLines() const
{
    std::string out = "numberOfFollowingARFCNs=" + std::to_string(numberOfFollowingARFCNs_internal_value) + ",";
    return out;
}

int CarrierFreqsGERAN::followingARFCNs_equallySpacedARFCNs::numberOfFollowingARFCNs_Clear()
{
    numberOfFollowingARFCNs_present = false;
    return 0;
}

bool CarrierFreqsGERAN::followingARFCNs_equallySpacedARFCNs::numberOfFollowingARFCNs_IsPresent() const
{
    return numberOfFollowingARFCNs_present;
}

int CarrierFreqsGERAN::followingARFCNs_variableBitMapOfARFCNs_Pack(std::vector<uint8_t> &bits)
{
    if(!followingARFCNs_variableBitMapOfARFCNs_present)
    {
        printf("CarrierFreqsGERAN::followingARFCNs_variableBitMapOfARFCNs_Pack() presence failure\n");
        return -1;
    }
    if(followingARFCNs_variableBitMapOfARFCNs_internal_value.size() < 1 || followingARFCNs_variableBitMapOfARFCNs_internal_value.size() > 16)
    {
        printf("CarrierFreqsGERAN::followingARFCNs_variableBitMapOfARFCNs_Pack() size failure\n");
        return -1;
    }
    uint32_t N_size_bits = 1;
    while(pow(2, N_size_bits) <= (16 - 1))
        N_size_bits++;
    uint32_t local_size = followingARFCNs_variableBitMapOfARFCNs_internal_value.size() - 1;
    for(uint32_t i=0; i<N_size_bits; i++)
        bits.push_back((local_size >> (N_size_bits-i-1)) & 1);
    for(uint32_t i=0; i<followingARFCNs_variableBitMapOfARFCNs_internal_value.size(); i++)
        for(uint32_t j=0; j<8; j++)
            bits.push_back((followingARFCNs_variableBitMapOfARFCNs_internal_value[i] >> (8-j-1)) & 1);
    return 0;
}

int CarrierFreqsGERAN::followingARFCNs_variableBitMapOfARFCNs_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return followingARFCNs_variableBitMapOfARFCNs_Unpack(bits, idx);
}

int CarrierFreqsGERAN::followingARFCNs_variableBitMapOfARFCNs_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_size_bits = 1;
    while(pow(2, N_size_bits) <= (16 - 1))
        N_size_bits++;
    uint32_t size = 0;
    for(uint32_t i=0; i<N_size_bits; i++)
        size |= bits[idx++] << (N_size_bits-i-1);
    size += 1;
    if(size < 1 || size > 16)
    {
        printf("CarrierFreqsGERAN::followingARFCNs_variableBitMapOfARFCNs_Unpack() size failure\n");
        return -1;
    }
    followingARFCNs_variableBitMapOfARFCNs_internal_value.clear();
    if((idx +size*8) > bits.size())
    {
        printf("CarrierFreqsGERAN::followingARFCNs_variableBitMapOfARFCNs_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
    {
        uint8_t value = 0;
        for(uint32_t j=0; j<8; j++)
            value |= bits[idx+j] << (8-j-1);
        followingARFCNs_variableBitMapOfARFCNs_internal_value.push_back(value);
        idx += 8;
    }
    followingARFCNs_variableBitMapOfARFCNs_present = true;
    return 0;
}

std::vector<uint8_t> CarrierFreqsGERAN::followingARFCNs_variableBitMapOfARFCNs_Value() const
{
    if(followingARFCNs_variableBitMapOfARFCNs_present)
        return followingARFCNs_variableBitMapOfARFCNs_internal_value;
    std::vector<uint8_t> tmp;
    return tmp;
}

int CarrierFreqsGERAN::followingARFCNs_variableBitMapOfARFCNs_SetValue(std::vector<uint8_t> value)
{
    if(value.size() < 1 || value.size() > 16)
    {
        printf("CarrierFreqsGERAN::followingARFCNs_variableBitMapOfARFCNs_SetValue() size failure\n");
        return -1;
    }
    followingARFCNs_variableBitMapOfARFCNs_internal_value = value;
    followingARFCNs_variableBitMapOfARFCNs_present = true;
    return 0;
}

std::string CarrierFreqsGERAN::followingARFCNs_variableBitMapOfARFCNs_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "variableBitMapOfARFCNs = {";
    for(auto byte : followingARFCNs_variableBitMapOfARFCNs_internal_value)
        out += std::to_string(byte) + ",";
    out = out.substr(0, out.length()-1) + "}\n";
    return out;
}

std::string CarrierFreqsGERAN::followingARFCNs_variableBitMapOfARFCNs_ToStringNoNewLines() const
{
    std::string out = "variableBitMapOfARFCNs={";
    for(auto byte : followingARFCNs_variableBitMapOfARFCNs_internal_value)
        out += std::to_string(byte) + ",";
    out = out.substr(0, out.length()-1) + "},";
    return out;
}

int CarrierFreqsGERAN::followingARFCNs_variableBitMapOfARFCNs_Clear()
{
    followingARFCNs_variableBitMapOfARFCNs_present = false;
    return 0;
}

bool CarrierFreqsGERAN::followingARFCNs_variableBitMapOfARFCNs_IsPresent() const
{
    return followingARFCNs_variableBitMapOfARFCNs_present;
}

