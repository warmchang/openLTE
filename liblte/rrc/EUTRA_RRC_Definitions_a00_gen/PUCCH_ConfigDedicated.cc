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

#include "PUCCH_ConfigDedicated.h"

#include <cmath>

int PUCCH_ConfigDedicated::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(tdd_AckNackFeedbackMode_IsPresent());

    // Fields
    {
        if(0 != ackNackRepetition_Pack(bits))
        {
            printf("PUCCH_ConfigDedicated:: field pack failure\n");
            return -1;
        }
    }
    if(tdd_AckNackFeedbackMode_IsPresent())
    {
        if(0 != tdd_AckNackFeedbackMode_Pack(bits))
        {
            printf("PUCCH_ConfigDedicated:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int PUCCH_ConfigDedicated::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int PUCCH_ConfigDedicated::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("PUCCH_ConfigDedicated::Unpack() index out of bounds for optional indiator tdd_AckNackFeedbackMode\n");
        return -1;
    }
    tdd_AckNackFeedbackMode_present = bits[idx++];

    // Fields
    {
        if(0 != ackNackRepetition_Unpack(bits, idx))
        {
            printf("PUCCH_ConfigDedicated:: field unpack failure\n");
            return -1;
        }
    }
    if(tdd_AckNackFeedbackMode_present)
    {
        if(0 != tdd_AckNackFeedbackMode_Unpack(bits, idx))
        {
            printf("PUCCH_ConfigDedicated:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string PUCCH_ConfigDedicated::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "PUCCH_ConfigDedicated:\n";
    out += ackNackRepetition_ToString(indent+1);
    if(tdd_AckNackFeedbackMode_IsPresent())
        out += tdd_AckNackFeedbackMode_ToString(indent+1);
    return out;
}

std::string PUCCH_ConfigDedicated::ToStringNoNewLines() const
{
    std::string out = "PUCCH_ConfigDedicated:";
    out += ackNackRepetition_ToStringNoNewLines();
    if(tdd_AckNackFeedbackMode_IsPresent())
        out += tdd_AckNackFeedbackMode_ToStringNoNewLines();
    return out;
}

int PUCCH_ConfigDedicated::ackNackRepetition_Pack(std::vector<uint8_t> &bits)
{
    if(!ackNackRepetition_present)
    {
        printf("PUCCH_ConfigDedicated::ackNackRepetition_Pack() presence failure\n");
        return -1;
    }
    // Extension indicator

    // Choice
    for(uint32_t i=0; i<1; i++)
        bits.push_back((ackNackRepetition_internal_choice >> (1-i-1)) & 1);

    // Fields
    if(ackNackRepetition_internal_choice == k_ackNackRepetition_release)
    {
        if(0 != ackNackRepetition_release_Pack(bits))
        {
            printf("PUCCH_ConfigDedicated::ackNackRepetition_release pack failure\n");
            return -1;
        }
    }
    if(ackNackRepetition_internal_choice == k_ackNackRepetition_setup)
    {
        if(0 != ackNackRepetition_setup_value.Pack(bits))
        {
            printf("PUCCH_ConfigDedicated::ackNackRepetition_setup pack failure\n");
            return -1;
        }
    }
    return 0;
}

int PUCCH_ConfigDedicated::ackNackRepetition_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return ackNackRepetition_Unpack(bits, idx);
}

int PUCCH_ConfigDedicated::ackNackRepetition_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 1) > bits.size())
    {
        printf("PUCCH_ConfigDedicated::ackNackRepetition_Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<1; i++)
        packed_val |= bits[idx++] << (1-i-1);

    if((PUCCH_ConfigDedicated::ackNackRepetition_Enum)packed_val > k_ackNackRepetition_setup)
    {
        printf("PUCCH_ConfigDedicated::ackNackRepetition_Unpack() choice range failure\n");
        return -1;
    }
    ackNackRepetition_internal_choice = (PUCCH_ConfigDedicated::ackNackRepetition_Enum)packed_val;
    ackNackRepetition_present = true;

    // Fields
    if(ackNackRepetition_internal_choice == k_ackNackRepetition_release)
    {
        if(0 != ackNackRepetition_release_Unpack(bits, idx))
        {
            printf("PUCCH_ConfigDedicated::ackNackRepetition_release unpack failure\n");
            return -1;
        }
    }
    if(ackNackRepetition_internal_choice == k_ackNackRepetition_setup)
    {
        if(0 != ackNackRepetition_setup_value.Unpack(bits, idx))
        {
            printf("PUCCH_ConfigDedicated::ackNackRepetition_setup unpack failure\n");
            return -1;
        }
    }
    return 0;
}

PUCCH_ConfigDedicated::ackNackRepetition_Enum PUCCH_ConfigDedicated::ackNackRepetition_Choice() const
{
    if(ackNackRepetition_present)
        return ackNackRepetition_internal_choice;
    return (PUCCH_ConfigDedicated::ackNackRepetition_Enum)0;
}

int PUCCH_ConfigDedicated::ackNackRepetition_SetChoice(PUCCH_ConfigDedicated::ackNackRepetition_Enum choice)
{
    ackNackRepetition_internal_choice = choice;
    ackNackRepetition_present = true;
    return 0;
}

std::string PUCCH_ConfigDedicated::ackNackRepetition_ChoiceToString(ackNackRepetition_Enum value) const
{
    if(k_ackNackRepetition_release == value)
        return "ackNackRepetition_release";
    if(k_ackNackRepetition_setup == value)
        return "ackNackRepetition_setup";
    return "";
}

uint64_t PUCCH_ConfigDedicated::ackNackRepetition_NumberOfChoices() const
{
    return 2;
}

std::string PUCCH_ConfigDedicated::ackNackRepetition_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ackNackRepetition = " + ackNackRepetition_ChoiceToString(ackNackRepetition_internal_choice) + ":\n";
    if(ackNackRepetition_internal_choice == k_ackNackRepetition_setup)
        out += ackNackRepetition_setup_value.ToString(indent+1);
    return out;
}

std::string PUCCH_ConfigDedicated::ackNackRepetition_ToStringNoNewLines() const
{
    std::string out = "ackNackRepetition=" + ackNackRepetition_ChoiceToString(ackNackRepetition_internal_choice) + ",";
    if(ackNackRepetition_internal_choice == k_ackNackRepetition_setup)
        out += ackNackRepetition_setup_value.ToStringNoNewLines();
    return out;
}

int PUCCH_ConfigDedicated::ackNackRepetition_Clear()
{
    ackNackRepetition_present = false;
    return 0;
}

bool PUCCH_ConfigDedicated::ackNackRepetition_IsPresent() const
{
    return ackNackRepetition_present;
}

int PUCCH_ConfigDedicated::ackNackRepetition_setup::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != repetitionFactor_Pack(bits))
        {
            printf("PUCCH_ConfigDedicated::ackNackRepetition_setup:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != n1PUCCH_AN_Rep_Pack(bits))
        {
            printf("PUCCH_ConfigDedicated::ackNackRepetition_setup:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int PUCCH_ConfigDedicated::ackNackRepetition_setup::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int PUCCH_ConfigDedicated::ackNackRepetition_setup::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != repetitionFactor_Unpack(bits, idx))
        {
            printf("PUCCH_ConfigDedicated::ackNackRepetition_setup:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != n1PUCCH_AN_Rep_Unpack(bits, idx))
        {
            printf("PUCCH_ConfigDedicated::ackNackRepetition_setup:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string PUCCH_ConfigDedicated::ackNackRepetition_setup::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "setup:\n";
    out += repetitionFactor_ToString(indent+1);
    out += n1PUCCH_AN_Rep_ToString(indent+1);
    return out;
}

std::string PUCCH_ConfigDedicated::ackNackRepetition_setup::ToStringNoNewLines() const
{
    std::string out = "setup:";
    out += repetitionFactor_ToStringNoNewLines();
    out += n1PUCCH_AN_Rep_ToStringNoNewLines();
    return out;
}

int PUCCH_ConfigDedicated::ackNackRepetition_setup::repetitionFactor_Pack(std::vector<uint8_t> &bits)
{
    if(!repetitionFactor_present)
    {
        printf("PUCCH_ConfigDedicated::ackNackRepetition_setup::repetitionFactor_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 2;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((repetitionFactor_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int PUCCH_ConfigDedicated::ackNackRepetition_setup::repetitionFactor_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return repetitionFactor_Unpack(bits, idx);
}

int PUCCH_ConfigDedicated::ackNackRepetition_setup::repetitionFactor_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 2;
    if((idx + N_bits) > bits.size())
    {
        printf("PUCCH_ConfigDedicated::ackNackRepetition_setup::repetitionFactor_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 3)
    {
        printf("PUCCH_ConfigDedicated::ackNackRepetition_setup::repetitionFactor_Unpack() max failure\n");
        return -1;
    }
    repetitionFactor_internal_value = (repetitionFactor_Enum)packed_val;
    repetitionFactor_present = true;
    return 0;
}

PUCCH_ConfigDedicated::ackNackRepetition_setup::repetitionFactor_Enum PUCCH_ConfigDedicated::ackNackRepetition_setup::repetitionFactor_Value() const
{
    if(repetitionFactor_present)
        return repetitionFactor_internal_value;
    return (PUCCH_ConfigDedicated::ackNackRepetition_setup::repetitionFactor_Enum)0;
}

int PUCCH_ConfigDedicated::ackNackRepetition_setup::repetitionFactor_SetValue(repetitionFactor_Enum value)
{
    repetitionFactor_internal_value = value;
    repetitionFactor_present = true;
    return 0;
}

int PUCCH_ConfigDedicated::ackNackRepetition_setup::repetitionFactor_SetValue(std::string value)
{
    if("n2" == value)
    {
        repetitionFactor_internal_value = k_repetitionFactor_n2;
        repetitionFactor_present = true;
        return 0;
    }
    if("n4" == value)
    {
        repetitionFactor_internal_value = k_repetitionFactor_n4;
        repetitionFactor_present = true;
        return 0;
    }
    if("n6" == value)
    {
        repetitionFactor_internal_value = k_repetitionFactor_n6;
        repetitionFactor_present = true;
        return 0;
    }
    if("spare1" == value)
    {
        repetitionFactor_internal_value = k_repetitionFactor_spare1;
        repetitionFactor_present = true;
        return 0;
    }
    return 1;
}

std::string PUCCH_ConfigDedicated::ackNackRepetition_setup::repetitionFactor_ValueToString(repetitionFactor_Enum value) const
{
    if(k_repetitionFactor_n2 == value)
        return "n2";
    if(k_repetitionFactor_n4 == value)
        return "n4";
    if(k_repetitionFactor_n6 == value)
        return "n6";
    if(k_repetitionFactor_spare1 == value)
        return "spare1";
    return "";
}

uint64_t PUCCH_ConfigDedicated::ackNackRepetition_setup::repetitionFactor_NumberOfValues() const
{
    return 4;
}

std::string PUCCH_ConfigDedicated::ackNackRepetition_setup::repetitionFactor_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "repetitionFactor = " + repetitionFactor_ValueToString(repetitionFactor_internal_value) + "\n";
    return out;
}

std::string PUCCH_ConfigDedicated::ackNackRepetition_setup::repetitionFactor_ToStringNoNewLines() const
{
    std::string out = "repetitionFactor=" + repetitionFactor_ValueToString(repetitionFactor_internal_value) + ",";
    return out;
}

int PUCCH_ConfigDedicated::ackNackRepetition_setup::repetitionFactor_Clear()
{
    repetitionFactor_present = false;
    return 0;
}

bool PUCCH_ConfigDedicated::ackNackRepetition_setup::repetitionFactor_IsPresent() const
{
    return repetitionFactor_present;
}

int PUCCH_ConfigDedicated::ackNackRepetition_setup::n1PUCCH_AN_Rep_Pack(std::vector<uint8_t> &bits)
{
    if(!n1PUCCH_AN_Rep_present)
    {
        printf("PUCCH_ConfigDedicated::ackNackRepetition_setup::n1PUCCH_AN_Rep_Pack() presence failure\n");
        return -1;
    }
    int64_t val_to_pack = n1PUCCH_AN_Rep_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (2047 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int PUCCH_ConfigDedicated::ackNackRepetition_setup::n1PUCCH_AN_Rep_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return n1PUCCH_AN_Rep_Unpack(bits, idx);
}

int PUCCH_ConfigDedicated::ackNackRepetition_setup::n1PUCCH_AN_Rep_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (2047 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("PUCCH_ConfigDedicated::ackNackRepetition_setup::n1PUCCH_AN_Rep_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    n1PUCCH_AN_Rep_internal_value = packed_val + 0;
    n1PUCCH_AN_Rep_present = true;
    return 0;
}

int64_t PUCCH_ConfigDedicated::ackNackRepetition_setup::n1PUCCH_AN_Rep_Value() const
{
    if(n1PUCCH_AN_Rep_present)
        return n1PUCCH_AN_Rep_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int PUCCH_ConfigDedicated::ackNackRepetition_setup::n1PUCCH_AN_Rep_SetValue(int64_t value)
{
    if(value < 0 || value > 2047)
    {
        printf("PUCCH_ConfigDedicated::ackNackRepetition_setup::n1PUCCH_AN_Rep_SetValue() range failure\n");
        return -1;
    }
    n1PUCCH_AN_Rep_internal_value = value;
    n1PUCCH_AN_Rep_present = true;
    return 0;
}

std::string PUCCH_ConfigDedicated::ackNackRepetition_setup::n1PUCCH_AN_Rep_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "n1PUCCH_AN_Rep = " + std::to_string(n1PUCCH_AN_Rep_internal_value) + "\n";
    return out;
}

std::string PUCCH_ConfigDedicated::ackNackRepetition_setup::n1PUCCH_AN_Rep_ToStringNoNewLines() const
{
    std::string out = "n1PUCCH_AN_Rep=" + std::to_string(n1PUCCH_AN_Rep_internal_value) + ",";
    return out;
}

int PUCCH_ConfigDedicated::ackNackRepetition_setup::n1PUCCH_AN_Rep_Clear()
{
    n1PUCCH_AN_Rep_present = false;
    return 0;
}

bool PUCCH_ConfigDedicated::ackNackRepetition_setup::n1PUCCH_AN_Rep_IsPresent() const
{
    return n1PUCCH_AN_Rep_present;
}

int PUCCH_ConfigDedicated::tdd_AckNackFeedbackMode_Pack(std::vector<uint8_t> &bits)
{
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((tdd_AckNackFeedbackMode_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int PUCCH_ConfigDedicated::tdd_AckNackFeedbackMode_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return tdd_AckNackFeedbackMode_Unpack(bits, idx);
}

int PUCCH_ConfigDedicated::tdd_AckNackFeedbackMode_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("PUCCH_ConfigDedicated::tdd_AckNackFeedbackMode_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 1)
    {
        printf("PUCCH_ConfigDedicated::tdd_AckNackFeedbackMode_Unpack() max failure\n");
        return -1;
    }
    tdd_AckNackFeedbackMode_internal_value = (tdd_AckNackFeedbackMode_Enum)packed_val;
    tdd_AckNackFeedbackMode_present = true;
    return 0;
}

PUCCH_ConfigDedicated::tdd_AckNackFeedbackMode_Enum PUCCH_ConfigDedicated::tdd_AckNackFeedbackMode_Value() const
{
    if(tdd_AckNackFeedbackMode_present)
        return tdd_AckNackFeedbackMode_internal_value;
    return (PUCCH_ConfigDedicated::tdd_AckNackFeedbackMode_Enum)0;
}

int PUCCH_ConfigDedicated::tdd_AckNackFeedbackMode_SetValue(tdd_AckNackFeedbackMode_Enum value)
{
    tdd_AckNackFeedbackMode_internal_value = value;
    tdd_AckNackFeedbackMode_present = true;
    return 0;
}

int PUCCH_ConfigDedicated::tdd_AckNackFeedbackMode_SetValue(std::string value)
{
    if("bundling" == value)
    {
        tdd_AckNackFeedbackMode_internal_value = k_tdd_AckNackFeedbackMode_bundling;
        tdd_AckNackFeedbackMode_present = true;
        return 0;
    }
    if("multiplexing" == value)
    {
        tdd_AckNackFeedbackMode_internal_value = k_tdd_AckNackFeedbackMode_multiplexing;
        tdd_AckNackFeedbackMode_present = true;
        return 0;
    }
    return 1;
}

std::string PUCCH_ConfigDedicated::tdd_AckNackFeedbackMode_ValueToString(tdd_AckNackFeedbackMode_Enum value) const
{
    if(k_tdd_AckNackFeedbackMode_bundling == value)
        return "bundling";
    if(k_tdd_AckNackFeedbackMode_multiplexing == value)
        return "multiplexing";
    return "";
}

uint64_t PUCCH_ConfigDedicated::tdd_AckNackFeedbackMode_NumberOfValues() const
{
    return 2;
}

std::string PUCCH_ConfigDedicated::tdd_AckNackFeedbackMode_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "tdd_AckNackFeedbackMode = " + tdd_AckNackFeedbackMode_ValueToString(tdd_AckNackFeedbackMode_internal_value) + "\n";
    return out;
}

std::string PUCCH_ConfigDedicated::tdd_AckNackFeedbackMode_ToStringNoNewLines() const
{
    std::string out = "tdd_AckNackFeedbackMode=" + tdd_AckNackFeedbackMode_ValueToString(tdd_AckNackFeedbackMode_internal_value) + ",";
    return out;
}

int PUCCH_ConfigDedicated::tdd_AckNackFeedbackMode_Clear()
{
    tdd_AckNackFeedbackMode_present = false;
    return 0;
}

bool PUCCH_ConfigDedicated::tdd_AckNackFeedbackMode_IsPresent() const
{
    return tdd_AckNackFeedbackMode_present;
}

