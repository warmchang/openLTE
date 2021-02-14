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

#include "AntennaInfoDedicated.h"

#include <cmath>

int AntennaInfoDedicated::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(codebookSubsetRestriction_IsPresent());

    // Fields
    {
        if(0 != transmissionMode_Pack(bits))
        {
            printf("AntennaInfoDedicated:: field pack failure\n");
            return -1;
        }
    }
    if(codebookSubsetRestriction_IsPresent())
    {
        if(0 != codebookSubsetRestriction_Pack(bits))
        {
            printf("AntennaInfoDedicated:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != ue_TransmitAntennaSelection_Pack(bits))
        {
            printf("AntennaInfoDedicated:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int AntennaInfoDedicated::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int AntennaInfoDedicated::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("AntennaInfoDedicated::Unpack() index out of bounds for optional indiator codebookSubsetRestriction\n");
        return -1;
    }
    codebookSubsetRestriction_present = bits[idx++];

    // Fields
    {
        if(0 != transmissionMode_Unpack(bits, idx))
        {
            printf("AntennaInfoDedicated:: field unpack failure\n");
            return -1;
        }
    }
    if(codebookSubsetRestriction_present)
    {
        if(0 != codebookSubsetRestriction_Unpack(bits, idx))
        {
            printf("AntennaInfoDedicated:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != ue_TransmitAntennaSelection_Unpack(bits, idx))
        {
            printf("AntennaInfoDedicated:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string AntennaInfoDedicated::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "AntennaInfoDedicated:\n";
    out += transmissionMode_ToString(indent+1);
    if(codebookSubsetRestriction_IsPresent())
        out += codebookSubsetRestriction_ToString(indent+1);
    out += ue_TransmitAntennaSelection_ToString(indent+1);
    return out;
}

std::string AntennaInfoDedicated::ToStringNoNewLines() const
{
    std::string out = "AntennaInfoDedicated:";
    out += transmissionMode_ToStringNoNewLines();
    if(codebookSubsetRestriction_IsPresent())
        out += codebookSubsetRestriction_ToStringNoNewLines();
    out += ue_TransmitAntennaSelection_ToStringNoNewLines();
    return out;
}

int AntennaInfoDedicated::transmissionMode_Pack(std::vector<uint8_t> &bits)
{
    if(!transmissionMode_present)
    {
        printf("AntennaInfoDedicated::transmissionMode_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 3;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((transmissionMode_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int AntennaInfoDedicated::transmissionMode_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return transmissionMode_Unpack(bits, idx);
}

int AntennaInfoDedicated::transmissionMode_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 3;
    if((idx + N_bits) > bits.size())
    {
        printf("AntennaInfoDedicated::transmissionMode_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 7)
    {
        printf("AntennaInfoDedicated::transmissionMode_Unpack() max failure\n");
        return -1;
    }
    transmissionMode_internal_value = (transmissionMode_Enum)packed_val;
    transmissionMode_present = true;
    return 0;
}

AntennaInfoDedicated::transmissionMode_Enum AntennaInfoDedicated::transmissionMode_Value() const
{
    if(transmissionMode_present)
        return transmissionMode_internal_value;
    return (AntennaInfoDedicated::transmissionMode_Enum)0;
}

int AntennaInfoDedicated::transmissionMode_SetValue(transmissionMode_Enum value)
{
    transmissionMode_internal_value = value;
    transmissionMode_present = true;
    return 0;
}

int AntennaInfoDedicated::transmissionMode_SetValue(std::string value)
{
    if("tm1" == value)
    {
        transmissionMode_internal_value = k_transmissionMode_tm1;
        transmissionMode_present = true;
        return 0;
    }
    if("tm2" == value)
    {
        transmissionMode_internal_value = k_transmissionMode_tm2;
        transmissionMode_present = true;
        return 0;
    }
    if("tm3" == value)
    {
        transmissionMode_internal_value = k_transmissionMode_tm3;
        transmissionMode_present = true;
        return 0;
    }
    if("tm4" == value)
    {
        transmissionMode_internal_value = k_transmissionMode_tm4;
        transmissionMode_present = true;
        return 0;
    }
    if("tm5" == value)
    {
        transmissionMode_internal_value = k_transmissionMode_tm5;
        transmissionMode_present = true;
        return 0;
    }
    if("tm6" == value)
    {
        transmissionMode_internal_value = k_transmissionMode_tm6;
        transmissionMode_present = true;
        return 0;
    }
    if("tm7" == value)
    {
        transmissionMode_internal_value = k_transmissionMode_tm7;
        transmissionMode_present = true;
        return 0;
    }
    if("tm8_v920" == value)
    {
        transmissionMode_internal_value = k_transmissionMode_tm8_v920;
        transmissionMode_present = true;
        return 0;
    }
    return 1;
}

std::string AntennaInfoDedicated::transmissionMode_ValueToString(transmissionMode_Enum value) const
{
    if(k_transmissionMode_tm1 == value)
        return "tm1";
    if(k_transmissionMode_tm2 == value)
        return "tm2";
    if(k_transmissionMode_tm3 == value)
        return "tm3";
    if(k_transmissionMode_tm4 == value)
        return "tm4";
    if(k_transmissionMode_tm5 == value)
        return "tm5";
    if(k_transmissionMode_tm6 == value)
        return "tm6";
    if(k_transmissionMode_tm7 == value)
        return "tm7";
    if(k_transmissionMode_tm8_v920 == value)
        return "tm8_v920";
    return "";
}

uint64_t AntennaInfoDedicated::transmissionMode_NumberOfValues() const
{
    return 8;
}

std::string AntennaInfoDedicated::transmissionMode_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "transmissionMode = " + transmissionMode_ValueToString(transmissionMode_internal_value) + "\n";
    return out;
}

std::string AntennaInfoDedicated::transmissionMode_ToStringNoNewLines() const
{
    std::string out = "transmissionMode=" + transmissionMode_ValueToString(transmissionMode_internal_value) + ",";
    return out;
}

int AntennaInfoDedicated::transmissionMode_Clear()
{
    transmissionMode_present = false;
    return 0;
}

bool AntennaInfoDedicated::transmissionMode_IsPresent() const
{
    return transmissionMode_present;
}

int AntennaInfoDedicated::codebookSubsetRestriction_Pack(std::vector<uint8_t> &bits)
{
    if(!codebookSubsetRestriction_present)
    {
        printf("AntennaInfoDedicated::codebookSubsetRestriction_Pack() presence failure\n");
        return -1;
    }
    // Extension indicator

    // Choice
    for(uint32_t i=0; i<3; i++)
        bits.push_back((codebookSubsetRestriction_internal_choice >> (3-i-1)) & 1);

    // Fields
    if(codebookSubsetRestriction_internal_choice == k_codebookSubsetRestriction_n2TxAntenna_tm3)
    {
        if(0 != codebookSubsetRestriction_n2TxAntenna_tm3_Pack(bits))
        {
            printf("AntennaInfoDedicated::codebookSubsetRestriction_n2TxAntenna_tm3 pack failure\n");
            return -1;
        }
    }
    if(codebookSubsetRestriction_internal_choice == k_codebookSubsetRestriction_n4TxAntenna_tm3)
    {
        if(0 != codebookSubsetRestriction_n4TxAntenna_tm3_Pack(bits))
        {
            printf("AntennaInfoDedicated::codebookSubsetRestriction_n4TxAntenna_tm3 pack failure\n");
            return -1;
        }
    }
    if(codebookSubsetRestriction_internal_choice == k_codebookSubsetRestriction_n2TxAntenna_tm4)
    {
        if(0 != codebookSubsetRestriction_n2TxAntenna_tm4_Pack(bits))
        {
            printf("AntennaInfoDedicated::codebookSubsetRestriction_n2TxAntenna_tm4 pack failure\n");
            return -1;
        }
    }
    if(codebookSubsetRestriction_internal_choice == k_codebookSubsetRestriction_n4TxAntenna_tm4)
    {
        if(0 != codebookSubsetRestriction_n4TxAntenna_tm4_Pack(bits))
        {
            printf("AntennaInfoDedicated::codebookSubsetRestriction_n4TxAntenna_tm4 pack failure\n");
            return -1;
        }
    }
    if(codebookSubsetRestriction_internal_choice == k_codebookSubsetRestriction_n2TxAntenna_tm5)
    {
        if(0 != codebookSubsetRestriction_n2TxAntenna_tm5_Pack(bits))
        {
            printf("AntennaInfoDedicated::codebookSubsetRestriction_n2TxAntenna_tm5 pack failure\n");
            return -1;
        }
    }
    if(codebookSubsetRestriction_internal_choice == k_codebookSubsetRestriction_n4TxAntenna_tm5)
    {
        if(0 != codebookSubsetRestriction_n4TxAntenna_tm5_Pack(bits))
        {
            printf("AntennaInfoDedicated::codebookSubsetRestriction_n4TxAntenna_tm5 pack failure\n");
            return -1;
        }
    }
    if(codebookSubsetRestriction_internal_choice == k_codebookSubsetRestriction_n2TxAntenna_tm6)
    {
        if(0 != codebookSubsetRestriction_n2TxAntenna_tm6_Pack(bits))
        {
            printf("AntennaInfoDedicated::codebookSubsetRestriction_n2TxAntenna_tm6 pack failure\n");
            return -1;
        }
    }
    if(codebookSubsetRestriction_internal_choice == k_codebookSubsetRestriction_n4TxAntenna_tm6)
    {
        if(0 != codebookSubsetRestriction_n4TxAntenna_tm6_Pack(bits))
        {
            printf("AntennaInfoDedicated::codebookSubsetRestriction_n4TxAntenna_tm6 pack failure\n");
            return -1;
        }
    }
    return 0;
}

int AntennaInfoDedicated::codebookSubsetRestriction_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return codebookSubsetRestriction_Unpack(bits, idx);
}

int AntennaInfoDedicated::codebookSubsetRestriction_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 3) > bits.size())
    {
        printf("AntennaInfoDedicated::codebookSubsetRestriction_Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<3; i++)
        packed_val |= bits[idx++] << (3-i-1);

    if((AntennaInfoDedicated::codebookSubsetRestriction_Enum)packed_val > k_codebookSubsetRestriction_n4TxAntenna_tm6)
    {
        printf("AntennaInfoDedicated::codebookSubsetRestriction_Unpack() choice range failure\n");
        return -1;
    }
    codebookSubsetRestriction_internal_choice = (AntennaInfoDedicated::codebookSubsetRestriction_Enum)packed_val;
    codebookSubsetRestriction_present = true;

    // Fields
    if(codebookSubsetRestriction_internal_choice == k_codebookSubsetRestriction_n2TxAntenna_tm3)
    {
        if(0 != codebookSubsetRestriction_n2TxAntenna_tm3_Unpack(bits, idx))
        {
            printf("AntennaInfoDedicated::codebookSubsetRestriction_n2TxAntenna_tm3 unpack failure\n");
            return -1;
        }
    }
    if(codebookSubsetRestriction_internal_choice == k_codebookSubsetRestriction_n4TxAntenna_tm3)
    {
        if(0 != codebookSubsetRestriction_n4TxAntenna_tm3_Unpack(bits, idx))
        {
            printf("AntennaInfoDedicated::codebookSubsetRestriction_n4TxAntenna_tm3 unpack failure\n");
            return -1;
        }
    }
    if(codebookSubsetRestriction_internal_choice == k_codebookSubsetRestriction_n2TxAntenna_tm4)
    {
        if(0 != codebookSubsetRestriction_n2TxAntenna_tm4_Unpack(bits, idx))
        {
            printf("AntennaInfoDedicated::codebookSubsetRestriction_n2TxAntenna_tm4 unpack failure\n");
            return -1;
        }
    }
    if(codebookSubsetRestriction_internal_choice == k_codebookSubsetRestriction_n4TxAntenna_tm4)
    {
        if(0 != codebookSubsetRestriction_n4TxAntenna_tm4_Unpack(bits, idx))
        {
            printf("AntennaInfoDedicated::codebookSubsetRestriction_n4TxAntenna_tm4 unpack failure\n");
            return -1;
        }
    }
    if(codebookSubsetRestriction_internal_choice == k_codebookSubsetRestriction_n2TxAntenna_tm5)
    {
        if(0 != codebookSubsetRestriction_n2TxAntenna_tm5_Unpack(bits, idx))
        {
            printf("AntennaInfoDedicated::codebookSubsetRestriction_n2TxAntenna_tm5 unpack failure\n");
            return -1;
        }
    }
    if(codebookSubsetRestriction_internal_choice == k_codebookSubsetRestriction_n4TxAntenna_tm5)
    {
        if(0 != codebookSubsetRestriction_n4TxAntenna_tm5_Unpack(bits, idx))
        {
            printf("AntennaInfoDedicated::codebookSubsetRestriction_n4TxAntenna_tm5 unpack failure\n");
            return -1;
        }
    }
    if(codebookSubsetRestriction_internal_choice == k_codebookSubsetRestriction_n2TxAntenna_tm6)
    {
        if(0 != codebookSubsetRestriction_n2TxAntenna_tm6_Unpack(bits, idx))
        {
            printf("AntennaInfoDedicated::codebookSubsetRestriction_n2TxAntenna_tm6 unpack failure\n");
            return -1;
        }
    }
    if(codebookSubsetRestriction_internal_choice == k_codebookSubsetRestriction_n4TxAntenna_tm6)
    {
        if(0 != codebookSubsetRestriction_n4TxAntenna_tm6_Unpack(bits, idx))
        {
            printf("AntennaInfoDedicated::codebookSubsetRestriction_n4TxAntenna_tm6 unpack failure\n");
            return -1;
        }
    }
    return 0;
}

AntennaInfoDedicated::codebookSubsetRestriction_Enum AntennaInfoDedicated::codebookSubsetRestriction_Choice() const
{
    if(codebookSubsetRestriction_present)
        return codebookSubsetRestriction_internal_choice;
    return (AntennaInfoDedicated::codebookSubsetRestriction_Enum)0;
}

int AntennaInfoDedicated::codebookSubsetRestriction_SetChoice(AntennaInfoDedicated::codebookSubsetRestriction_Enum choice)
{
    codebookSubsetRestriction_internal_choice = choice;
    codebookSubsetRestriction_present = true;
    return 0;
}

std::string AntennaInfoDedicated::codebookSubsetRestriction_ChoiceToString(codebookSubsetRestriction_Enum value) const
{
    if(k_codebookSubsetRestriction_n2TxAntenna_tm3 == value)
        return "codebookSubsetRestriction_n2TxAntenna_tm3";
    if(k_codebookSubsetRestriction_n4TxAntenna_tm3 == value)
        return "codebookSubsetRestriction_n4TxAntenna_tm3";
    if(k_codebookSubsetRestriction_n2TxAntenna_tm4 == value)
        return "codebookSubsetRestriction_n2TxAntenna_tm4";
    if(k_codebookSubsetRestriction_n4TxAntenna_tm4 == value)
        return "codebookSubsetRestriction_n4TxAntenna_tm4";
    if(k_codebookSubsetRestriction_n2TxAntenna_tm5 == value)
        return "codebookSubsetRestriction_n2TxAntenna_tm5";
    if(k_codebookSubsetRestriction_n4TxAntenna_tm5 == value)
        return "codebookSubsetRestriction_n4TxAntenna_tm5";
    if(k_codebookSubsetRestriction_n2TxAntenna_tm6 == value)
        return "codebookSubsetRestriction_n2TxAntenna_tm6";
    if(k_codebookSubsetRestriction_n4TxAntenna_tm6 == value)
        return "codebookSubsetRestriction_n4TxAntenna_tm6";
    return "";
}

uint64_t AntennaInfoDedicated::codebookSubsetRestriction_NumberOfChoices() const
{
    return 8;
}

std::string AntennaInfoDedicated::codebookSubsetRestriction_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "codebookSubsetRestriction = " + codebookSubsetRestriction_ChoiceToString(codebookSubsetRestriction_internal_choice) + ":\n";
    if(codebookSubsetRestriction_internal_choice == k_codebookSubsetRestriction_n2TxAntenna_tm3)
        out += codebookSubsetRestriction_n2TxAntenna_tm3_ToString(indent+1);
    if(codebookSubsetRestriction_internal_choice == k_codebookSubsetRestriction_n4TxAntenna_tm3)
        out += codebookSubsetRestriction_n4TxAntenna_tm3_ToString(indent+1);
    if(codebookSubsetRestriction_internal_choice == k_codebookSubsetRestriction_n2TxAntenna_tm4)
        out += codebookSubsetRestriction_n2TxAntenna_tm4_ToString(indent+1);
    if(codebookSubsetRestriction_internal_choice == k_codebookSubsetRestriction_n4TxAntenna_tm4)
        out += codebookSubsetRestriction_n4TxAntenna_tm4_ToString(indent+1);
    if(codebookSubsetRestriction_internal_choice == k_codebookSubsetRestriction_n2TxAntenna_tm5)
        out += codebookSubsetRestriction_n2TxAntenna_tm5_ToString(indent+1);
    if(codebookSubsetRestriction_internal_choice == k_codebookSubsetRestriction_n4TxAntenna_tm5)
        out += codebookSubsetRestriction_n4TxAntenna_tm5_ToString(indent+1);
    if(codebookSubsetRestriction_internal_choice == k_codebookSubsetRestriction_n2TxAntenna_tm6)
        out += codebookSubsetRestriction_n2TxAntenna_tm6_ToString(indent+1);
    if(codebookSubsetRestriction_internal_choice == k_codebookSubsetRestriction_n4TxAntenna_tm6)
        out += codebookSubsetRestriction_n4TxAntenna_tm6_ToString(indent+1);
    return out;
}

std::string AntennaInfoDedicated::codebookSubsetRestriction_ToStringNoNewLines() const
{
    std::string out = "codebookSubsetRestriction=" + codebookSubsetRestriction_ChoiceToString(codebookSubsetRestriction_internal_choice) + ",";
    if(codebookSubsetRestriction_internal_choice == k_codebookSubsetRestriction_n2TxAntenna_tm3)
        out += codebookSubsetRestriction_n2TxAntenna_tm3_ToStringNoNewLines();
    if(codebookSubsetRestriction_internal_choice == k_codebookSubsetRestriction_n4TxAntenna_tm3)
        out += codebookSubsetRestriction_n4TxAntenna_tm3_ToStringNoNewLines();
    if(codebookSubsetRestriction_internal_choice == k_codebookSubsetRestriction_n2TxAntenna_tm4)
        out += codebookSubsetRestriction_n2TxAntenna_tm4_ToStringNoNewLines();
    if(codebookSubsetRestriction_internal_choice == k_codebookSubsetRestriction_n4TxAntenna_tm4)
        out += codebookSubsetRestriction_n4TxAntenna_tm4_ToStringNoNewLines();
    if(codebookSubsetRestriction_internal_choice == k_codebookSubsetRestriction_n2TxAntenna_tm5)
        out += codebookSubsetRestriction_n2TxAntenna_tm5_ToStringNoNewLines();
    if(codebookSubsetRestriction_internal_choice == k_codebookSubsetRestriction_n4TxAntenna_tm5)
        out += codebookSubsetRestriction_n4TxAntenna_tm5_ToStringNoNewLines();
    if(codebookSubsetRestriction_internal_choice == k_codebookSubsetRestriction_n2TxAntenna_tm6)
        out += codebookSubsetRestriction_n2TxAntenna_tm6_ToStringNoNewLines();
    if(codebookSubsetRestriction_internal_choice == k_codebookSubsetRestriction_n4TxAntenna_tm6)
        out += codebookSubsetRestriction_n4TxAntenna_tm6_ToStringNoNewLines();
    return out;
}

int AntennaInfoDedicated::codebookSubsetRestriction_Clear()
{
    codebookSubsetRestriction_present = false;
    return 0;
}

bool AntennaInfoDedicated::codebookSubsetRestriction_IsPresent() const
{
    return codebookSubsetRestriction_present;
}

int AntennaInfoDedicated::codebookSubsetRestriction_n2TxAntenna_tm3_Pack(std::vector<uint8_t> &bits)
{
    if(!codebookSubsetRestriction_n2TxAntenna_tm3_present)
    {
        printf("AntennaInfoDedicated::codebookSubsetRestriction_n2TxAntenna_tm3_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 2;
    if(size < 2 || size > 2)
    {
        printf("AntennaInfoDedicated::codebookSubsetRestriction_n2TxAntenna_tm3_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((codebookSubsetRestriction_n2TxAntenna_tm3_internal_value >> (2-i-1)) & 1);
    return 0;
}

int AntennaInfoDedicated::codebookSubsetRestriction_n2TxAntenna_tm3_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return codebookSubsetRestriction_n2TxAntenna_tm3_Unpack(bits, idx);
}

int AntennaInfoDedicated::codebookSubsetRestriction_n2TxAntenna_tm3_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 2;
    if(size < 2 || size > 2)
    {
        printf("AntennaInfoDedicated::codebookSubsetRestriction_n2TxAntenna_tm3_Unpack() size failure\n");
        return -1;
    }
    codebookSubsetRestriction_n2TxAntenna_tm3_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("AntennaInfoDedicated::codebookSubsetRestriction_n2TxAntenna_tm3_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        codebookSubsetRestriction_n2TxAntenna_tm3_internal_value |= (uint8_t)bits[idx++] << (uint8_t)(2-i-1);
    codebookSubsetRestriction_n2TxAntenna_tm3_present = true;
    return 0;
}

uint8_t AntennaInfoDedicated::codebookSubsetRestriction_n2TxAntenna_tm3_Value() const
{
    if(codebookSubsetRestriction_n2TxAntenna_tm3_present)
        return codebookSubsetRestriction_n2TxAntenna_tm3_internal_value;
    uint8_t tmp = 0;
    return tmp;
}

int AntennaInfoDedicated::codebookSubsetRestriction_n2TxAntenna_tm3_SetValue(uint8_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 2)
    {
        printf("AntennaInfoDedicated::codebookSubsetRestriction_n2TxAntenna_tm3_SetValue() size failure\n");
        return -1;
    }
    codebookSubsetRestriction_n2TxAntenna_tm3_internal_value = value;
    codebookSubsetRestriction_n2TxAntenna_tm3_present = true;
    return 0;
}

std::string AntennaInfoDedicated::codebookSubsetRestriction_n2TxAntenna_tm3_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "n2TxAntenna_tm3 = ";
    out += std::to_string(codebookSubsetRestriction_n2TxAntenna_tm3_internal_value);
    out += "\n";
    return out;
}

std::string AntennaInfoDedicated::codebookSubsetRestriction_n2TxAntenna_tm3_ToStringNoNewLines() const
{
    std::string out = "n2TxAntenna_tm3=";
    out += std::to_string(codebookSubsetRestriction_n2TxAntenna_tm3_internal_value);
    out += ",";
    return out;
}

int AntennaInfoDedicated::codebookSubsetRestriction_n2TxAntenna_tm3_Clear()
{
    codebookSubsetRestriction_n2TxAntenna_tm3_present = false;
    return 0;
}

bool AntennaInfoDedicated::codebookSubsetRestriction_n2TxAntenna_tm3_IsPresent() const
{
    return codebookSubsetRestriction_n2TxAntenna_tm3_present;
}

int AntennaInfoDedicated::codebookSubsetRestriction_n4TxAntenna_tm3_Pack(std::vector<uint8_t> &bits)
{
    if(!codebookSubsetRestriction_n4TxAntenna_tm3_present)
    {
        printf("AntennaInfoDedicated::codebookSubsetRestriction_n4TxAntenna_tm3_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 4;
    if(size < 4 || size > 4)
    {
        printf("AntennaInfoDedicated::codebookSubsetRestriction_n4TxAntenna_tm3_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((codebookSubsetRestriction_n4TxAntenna_tm3_internal_value >> (4-i-1)) & 1);
    return 0;
}

int AntennaInfoDedicated::codebookSubsetRestriction_n4TxAntenna_tm3_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return codebookSubsetRestriction_n4TxAntenna_tm3_Unpack(bits, idx);
}

int AntennaInfoDedicated::codebookSubsetRestriction_n4TxAntenna_tm3_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 4;
    if(size < 4 || size > 4)
    {
        printf("AntennaInfoDedicated::codebookSubsetRestriction_n4TxAntenna_tm3_Unpack() size failure\n");
        return -1;
    }
    codebookSubsetRestriction_n4TxAntenna_tm3_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("AntennaInfoDedicated::codebookSubsetRestriction_n4TxAntenna_tm3_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        codebookSubsetRestriction_n4TxAntenna_tm3_internal_value |= (uint8_t)bits[idx++] << (uint8_t)(4-i-1);
    codebookSubsetRestriction_n4TxAntenna_tm3_present = true;
    return 0;
}

uint8_t AntennaInfoDedicated::codebookSubsetRestriction_n4TxAntenna_tm3_Value() const
{
    if(codebookSubsetRestriction_n4TxAntenna_tm3_present)
        return codebookSubsetRestriction_n4TxAntenna_tm3_internal_value;
    uint8_t tmp = 0;
    return tmp;
}

int AntennaInfoDedicated::codebookSubsetRestriction_n4TxAntenna_tm3_SetValue(uint8_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 4)
    {
        printf("AntennaInfoDedicated::codebookSubsetRestriction_n4TxAntenna_tm3_SetValue() size failure\n");
        return -1;
    }
    codebookSubsetRestriction_n4TxAntenna_tm3_internal_value = value;
    codebookSubsetRestriction_n4TxAntenna_tm3_present = true;
    return 0;
}

std::string AntennaInfoDedicated::codebookSubsetRestriction_n4TxAntenna_tm3_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "n4TxAntenna_tm3 = ";
    out += std::to_string(codebookSubsetRestriction_n4TxAntenna_tm3_internal_value);
    out += "\n";
    return out;
}

std::string AntennaInfoDedicated::codebookSubsetRestriction_n4TxAntenna_tm3_ToStringNoNewLines() const
{
    std::string out = "n4TxAntenna_tm3=";
    out += std::to_string(codebookSubsetRestriction_n4TxAntenna_tm3_internal_value);
    out += ",";
    return out;
}

int AntennaInfoDedicated::codebookSubsetRestriction_n4TxAntenna_tm3_Clear()
{
    codebookSubsetRestriction_n4TxAntenna_tm3_present = false;
    return 0;
}

bool AntennaInfoDedicated::codebookSubsetRestriction_n4TxAntenna_tm3_IsPresent() const
{
    return codebookSubsetRestriction_n4TxAntenna_tm3_present;
}

int AntennaInfoDedicated::codebookSubsetRestriction_n2TxAntenna_tm4_Pack(std::vector<uint8_t> &bits)
{
    if(!codebookSubsetRestriction_n2TxAntenna_tm4_present)
    {
        printf("AntennaInfoDedicated::codebookSubsetRestriction_n2TxAntenna_tm4_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 6;
    if(size < 6 || size > 6)
    {
        printf("AntennaInfoDedicated::codebookSubsetRestriction_n2TxAntenna_tm4_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((codebookSubsetRestriction_n2TxAntenna_tm4_internal_value >> (6-i-1)) & 1);
    return 0;
}

int AntennaInfoDedicated::codebookSubsetRestriction_n2TxAntenna_tm4_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return codebookSubsetRestriction_n2TxAntenna_tm4_Unpack(bits, idx);
}

int AntennaInfoDedicated::codebookSubsetRestriction_n2TxAntenna_tm4_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 6;
    if(size < 6 || size > 6)
    {
        printf("AntennaInfoDedicated::codebookSubsetRestriction_n2TxAntenna_tm4_Unpack() size failure\n");
        return -1;
    }
    codebookSubsetRestriction_n2TxAntenna_tm4_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("AntennaInfoDedicated::codebookSubsetRestriction_n2TxAntenna_tm4_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        codebookSubsetRestriction_n2TxAntenna_tm4_internal_value |= (uint8_t)bits[idx++] << (uint8_t)(6-i-1);
    codebookSubsetRestriction_n2TxAntenna_tm4_present = true;
    return 0;
}

uint8_t AntennaInfoDedicated::codebookSubsetRestriction_n2TxAntenna_tm4_Value() const
{
    if(codebookSubsetRestriction_n2TxAntenna_tm4_present)
        return codebookSubsetRestriction_n2TxAntenna_tm4_internal_value;
    uint8_t tmp = 0;
    return tmp;
}

int AntennaInfoDedicated::codebookSubsetRestriction_n2TxAntenna_tm4_SetValue(uint8_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 6)
    {
        printf("AntennaInfoDedicated::codebookSubsetRestriction_n2TxAntenna_tm4_SetValue() size failure\n");
        return -1;
    }
    codebookSubsetRestriction_n2TxAntenna_tm4_internal_value = value;
    codebookSubsetRestriction_n2TxAntenna_tm4_present = true;
    return 0;
}

std::string AntennaInfoDedicated::codebookSubsetRestriction_n2TxAntenna_tm4_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "n2TxAntenna_tm4 = ";
    out += std::to_string(codebookSubsetRestriction_n2TxAntenna_tm4_internal_value);
    out += "\n";
    return out;
}

std::string AntennaInfoDedicated::codebookSubsetRestriction_n2TxAntenna_tm4_ToStringNoNewLines() const
{
    std::string out = "n2TxAntenna_tm4=";
    out += std::to_string(codebookSubsetRestriction_n2TxAntenna_tm4_internal_value);
    out += ",";
    return out;
}

int AntennaInfoDedicated::codebookSubsetRestriction_n2TxAntenna_tm4_Clear()
{
    codebookSubsetRestriction_n2TxAntenna_tm4_present = false;
    return 0;
}

bool AntennaInfoDedicated::codebookSubsetRestriction_n2TxAntenna_tm4_IsPresent() const
{
    return codebookSubsetRestriction_n2TxAntenna_tm4_present;
}

int AntennaInfoDedicated::codebookSubsetRestriction_n4TxAntenna_tm4_Pack(std::vector<uint8_t> &bits)
{
    if(!codebookSubsetRestriction_n4TxAntenna_tm4_present)
    {
        printf("AntennaInfoDedicated::codebookSubsetRestriction_n4TxAntenna_tm4_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 64;
    if(size < 64 || size > 64)
    {
        printf("AntennaInfoDedicated::codebookSubsetRestriction_n4TxAntenna_tm4_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((codebookSubsetRestriction_n4TxAntenna_tm4_internal_value >> (64-i-1)) & 1);
    return 0;
}

int AntennaInfoDedicated::codebookSubsetRestriction_n4TxAntenna_tm4_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return codebookSubsetRestriction_n4TxAntenna_tm4_Unpack(bits, idx);
}

int AntennaInfoDedicated::codebookSubsetRestriction_n4TxAntenna_tm4_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 64;
    if(size < 64 || size > 64)
    {
        printf("AntennaInfoDedicated::codebookSubsetRestriction_n4TxAntenna_tm4_Unpack() size failure\n");
        return -1;
    }
    codebookSubsetRestriction_n4TxAntenna_tm4_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("AntennaInfoDedicated::codebookSubsetRestriction_n4TxAntenna_tm4_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        codebookSubsetRestriction_n4TxAntenna_tm4_internal_value |= (uint64_t)bits[idx++] << (uint64_t)(64-i-1);
    codebookSubsetRestriction_n4TxAntenna_tm4_present = true;
    return 0;
}

uint64_t AntennaInfoDedicated::codebookSubsetRestriction_n4TxAntenna_tm4_Value() const
{
    if(codebookSubsetRestriction_n4TxAntenna_tm4_present)
        return codebookSubsetRestriction_n4TxAntenna_tm4_internal_value;
    uint64_t tmp = 0;
    return tmp;
}

int AntennaInfoDedicated::codebookSubsetRestriction_n4TxAntenna_tm4_SetValue(uint64_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 64)
    {
        printf("AntennaInfoDedicated::codebookSubsetRestriction_n4TxAntenna_tm4_SetValue() size failure\n");
        return -1;
    }
    codebookSubsetRestriction_n4TxAntenna_tm4_internal_value = value;
    codebookSubsetRestriction_n4TxAntenna_tm4_present = true;
    return 0;
}

std::string AntennaInfoDedicated::codebookSubsetRestriction_n4TxAntenna_tm4_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "n4TxAntenna_tm4 = ";
    out += std::to_string(codebookSubsetRestriction_n4TxAntenna_tm4_internal_value);
    out += "\n";
    return out;
}

std::string AntennaInfoDedicated::codebookSubsetRestriction_n4TxAntenna_tm4_ToStringNoNewLines() const
{
    std::string out = "n4TxAntenna_tm4=";
    out += std::to_string(codebookSubsetRestriction_n4TxAntenna_tm4_internal_value);
    out += ",";
    return out;
}

int AntennaInfoDedicated::codebookSubsetRestriction_n4TxAntenna_tm4_Clear()
{
    codebookSubsetRestriction_n4TxAntenna_tm4_present = false;
    return 0;
}

bool AntennaInfoDedicated::codebookSubsetRestriction_n4TxAntenna_tm4_IsPresent() const
{
    return codebookSubsetRestriction_n4TxAntenna_tm4_present;
}

int AntennaInfoDedicated::codebookSubsetRestriction_n2TxAntenna_tm5_Pack(std::vector<uint8_t> &bits)
{
    if(!codebookSubsetRestriction_n2TxAntenna_tm5_present)
    {
        printf("AntennaInfoDedicated::codebookSubsetRestriction_n2TxAntenna_tm5_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 4;
    if(size < 4 || size > 4)
    {
        printf("AntennaInfoDedicated::codebookSubsetRestriction_n2TxAntenna_tm5_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((codebookSubsetRestriction_n2TxAntenna_tm5_internal_value >> (4-i-1)) & 1);
    return 0;
}

int AntennaInfoDedicated::codebookSubsetRestriction_n2TxAntenna_tm5_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return codebookSubsetRestriction_n2TxAntenna_tm5_Unpack(bits, idx);
}

int AntennaInfoDedicated::codebookSubsetRestriction_n2TxAntenna_tm5_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 4;
    if(size < 4 || size > 4)
    {
        printf("AntennaInfoDedicated::codebookSubsetRestriction_n2TxAntenna_tm5_Unpack() size failure\n");
        return -1;
    }
    codebookSubsetRestriction_n2TxAntenna_tm5_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("AntennaInfoDedicated::codebookSubsetRestriction_n2TxAntenna_tm5_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        codebookSubsetRestriction_n2TxAntenna_tm5_internal_value |= (uint8_t)bits[idx++] << (uint8_t)(4-i-1);
    codebookSubsetRestriction_n2TxAntenna_tm5_present = true;
    return 0;
}

uint8_t AntennaInfoDedicated::codebookSubsetRestriction_n2TxAntenna_tm5_Value() const
{
    if(codebookSubsetRestriction_n2TxAntenna_tm5_present)
        return codebookSubsetRestriction_n2TxAntenna_tm5_internal_value;
    uint8_t tmp = 0;
    return tmp;
}

int AntennaInfoDedicated::codebookSubsetRestriction_n2TxAntenna_tm5_SetValue(uint8_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 4)
    {
        printf("AntennaInfoDedicated::codebookSubsetRestriction_n2TxAntenna_tm5_SetValue() size failure\n");
        return -1;
    }
    codebookSubsetRestriction_n2TxAntenna_tm5_internal_value = value;
    codebookSubsetRestriction_n2TxAntenna_tm5_present = true;
    return 0;
}

std::string AntennaInfoDedicated::codebookSubsetRestriction_n2TxAntenna_tm5_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "n2TxAntenna_tm5 = ";
    out += std::to_string(codebookSubsetRestriction_n2TxAntenna_tm5_internal_value);
    out += "\n";
    return out;
}

std::string AntennaInfoDedicated::codebookSubsetRestriction_n2TxAntenna_tm5_ToStringNoNewLines() const
{
    std::string out = "n2TxAntenna_tm5=";
    out += std::to_string(codebookSubsetRestriction_n2TxAntenna_tm5_internal_value);
    out += ",";
    return out;
}

int AntennaInfoDedicated::codebookSubsetRestriction_n2TxAntenna_tm5_Clear()
{
    codebookSubsetRestriction_n2TxAntenna_tm5_present = false;
    return 0;
}

bool AntennaInfoDedicated::codebookSubsetRestriction_n2TxAntenna_tm5_IsPresent() const
{
    return codebookSubsetRestriction_n2TxAntenna_tm5_present;
}

int AntennaInfoDedicated::codebookSubsetRestriction_n4TxAntenna_tm5_Pack(std::vector<uint8_t> &bits)
{
    if(!codebookSubsetRestriction_n4TxAntenna_tm5_present)
    {
        printf("AntennaInfoDedicated::codebookSubsetRestriction_n4TxAntenna_tm5_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 16;
    if(size < 16 || size > 16)
    {
        printf("AntennaInfoDedicated::codebookSubsetRestriction_n4TxAntenna_tm5_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((codebookSubsetRestriction_n4TxAntenna_tm5_internal_value >> (16-i-1)) & 1);
    return 0;
}

int AntennaInfoDedicated::codebookSubsetRestriction_n4TxAntenna_tm5_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return codebookSubsetRestriction_n4TxAntenna_tm5_Unpack(bits, idx);
}

int AntennaInfoDedicated::codebookSubsetRestriction_n4TxAntenna_tm5_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 16;
    if(size < 16 || size > 16)
    {
        printf("AntennaInfoDedicated::codebookSubsetRestriction_n4TxAntenna_tm5_Unpack() size failure\n");
        return -1;
    }
    codebookSubsetRestriction_n4TxAntenna_tm5_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("AntennaInfoDedicated::codebookSubsetRestriction_n4TxAntenna_tm5_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        codebookSubsetRestriction_n4TxAntenna_tm5_internal_value |= (uint16_t)bits[idx++] << (uint16_t)(16-i-1);
    codebookSubsetRestriction_n4TxAntenna_tm5_present = true;
    return 0;
}

uint16_t AntennaInfoDedicated::codebookSubsetRestriction_n4TxAntenna_tm5_Value() const
{
    if(codebookSubsetRestriction_n4TxAntenna_tm5_present)
        return codebookSubsetRestriction_n4TxAntenna_tm5_internal_value;
    uint16_t tmp = 0;
    return tmp;
}

int AntennaInfoDedicated::codebookSubsetRestriction_n4TxAntenna_tm5_SetValue(uint16_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 16)
    {
        printf("AntennaInfoDedicated::codebookSubsetRestriction_n4TxAntenna_tm5_SetValue() size failure\n");
        return -1;
    }
    codebookSubsetRestriction_n4TxAntenna_tm5_internal_value = value;
    codebookSubsetRestriction_n4TxAntenna_tm5_present = true;
    return 0;
}

std::string AntennaInfoDedicated::codebookSubsetRestriction_n4TxAntenna_tm5_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "n4TxAntenna_tm5 = ";
    out += std::to_string(codebookSubsetRestriction_n4TxAntenna_tm5_internal_value);
    out += "\n";
    return out;
}

std::string AntennaInfoDedicated::codebookSubsetRestriction_n4TxAntenna_tm5_ToStringNoNewLines() const
{
    std::string out = "n4TxAntenna_tm5=";
    out += std::to_string(codebookSubsetRestriction_n4TxAntenna_tm5_internal_value);
    out += ",";
    return out;
}

int AntennaInfoDedicated::codebookSubsetRestriction_n4TxAntenna_tm5_Clear()
{
    codebookSubsetRestriction_n4TxAntenna_tm5_present = false;
    return 0;
}

bool AntennaInfoDedicated::codebookSubsetRestriction_n4TxAntenna_tm5_IsPresent() const
{
    return codebookSubsetRestriction_n4TxAntenna_tm5_present;
}

int AntennaInfoDedicated::codebookSubsetRestriction_n2TxAntenna_tm6_Pack(std::vector<uint8_t> &bits)
{
    if(!codebookSubsetRestriction_n2TxAntenna_tm6_present)
    {
        printf("AntennaInfoDedicated::codebookSubsetRestriction_n2TxAntenna_tm6_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 4;
    if(size < 4 || size > 4)
    {
        printf("AntennaInfoDedicated::codebookSubsetRestriction_n2TxAntenna_tm6_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((codebookSubsetRestriction_n2TxAntenna_tm6_internal_value >> (4-i-1)) & 1);
    return 0;
}

int AntennaInfoDedicated::codebookSubsetRestriction_n2TxAntenna_tm6_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return codebookSubsetRestriction_n2TxAntenna_tm6_Unpack(bits, idx);
}

int AntennaInfoDedicated::codebookSubsetRestriction_n2TxAntenna_tm6_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 4;
    if(size < 4 || size > 4)
    {
        printf("AntennaInfoDedicated::codebookSubsetRestriction_n2TxAntenna_tm6_Unpack() size failure\n");
        return -1;
    }
    codebookSubsetRestriction_n2TxAntenna_tm6_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("AntennaInfoDedicated::codebookSubsetRestriction_n2TxAntenna_tm6_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        codebookSubsetRestriction_n2TxAntenna_tm6_internal_value |= (uint8_t)bits[idx++] << (uint8_t)(4-i-1);
    codebookSubsetRestriction_n2TxAntenna_tm6_present = true;
    return 0;
}

uint8_t AntennaInfoDedicated::codebookSubsetRestriction_n2TxAntenna_tm6_Value() const
{
    if(codebookSubsetRestriction_n2TxAntenna_tm6_present)
        return codebookSubsetRestriction_n2TxAntenna_tm6_internal_value;
    uint8_t tmp = 0;
    return tmp;
}

int AntennaInfoDedicated::codebookSubsetRestriction_n2TxAntenna_tm6_SetValue(uint8_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 4)
    {
        printf("AntennaInfoDedicated::codebookSubsetRestriction_n2TxAntenna_tm6_SetValue() size failure\n");
        return -1;
    }
    codebookSubsetRestriction_n2TxAntenna_tm6_internal_value = value;
    codebookSubsetRestriction_n2TxAntenna_tm6_present = true;
    return 0;
}

std::string AntennaInfoDedicated::codebookSubsetRestriction_n2TxAntenna_tm6_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "n2TxAntenna_tm6 = ";
    out += std::to_string(codebookSubsetRestriction_n2TxAntenna_tm6_internal_value);
    out += "\n";
    return out;
}

std::string AntennaInfoDedicated::codebookSubsetRestriction_n2TxAntenna_tm6_ToStringNoNewLines() const
{
    std::string out = "n2TxAntenna_tm6=";
    out += std::to_string(codebookSubsetRestriction_n2TxAntenna_tm6_internal_value);
    out += ",";
    return out;
}

int AntennaInfoDedicated::codebookSubsetRestriction_n2TxAntenna_tm6_Clear()
{
    codebookSubsetRestriction_n2TxAntenna_tm6_present = false;
    return 0;
}

bool AntennaInfoDedicated::codebookSubsetRestriction_n2TxAntenna_tm6_IsPresent() const
{
    return codebookSubsetRestriction_n2TxAntenna_tm6_present;
}

int AntennaInfoDedicated::codebookSubsetRestriction_n4TxAntenna_tm6_Pack(std::vector<uint8_t> &bits)
{
    if(!codebookSubsetRestriction_n4TxAntenna_tm6_present)
    {
        printf("AntennaInfoDedicated::codebookSubsetRestriction_n4TxAntenna_tm6_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 16;
    if(size < 16 || size > 16)
    {
        printf("AntennaInfoDedicated::codebookSubsetRestriction_n4TxAntenna_tm6_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((codebookSubsetRestriction_n4TxAntenna_tm6_internal_value >> (16-i-1)) & 1);
    return 0;
}

int AntennaInfoDedicated::codebookSubsetRestriction_n4TxAntenna_tm6_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return codebookSubsetRestriction_n4TxAntenna_tm6_Unpack(bits, idx);
}

int AntennaInfoDedicated::codebookSubsetRestriction_n4TxAntenna_tm6_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 16;
    if(size < 16 || size > 16)
    {
        printf("AntennaInfoDedicated::codebookSubsetRestriction_n4TxAntenna_tm6_Unpack() size failure\n");
        return -1;
    }
    codebookSubsetRestriction_n4TxAntenna_tm6_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("AntennaInfoDedicated::codebookSubsetRestriction_n4TxAntenna_tm6_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        codebookSubsetRestriction_n4TxAntenna_tm6_internal_value |= (uint16_t)bits[idx++] << (uint16_t)(16-i-1);
    codebookSubsetRestriction_n4TxAntenna_tm6_present = true;
    return 0;
}

uint16_t AntennaInfoDedicated::codebookSubsetRestriction_n4TxAntenna_tm6_Value() const
{
    if(codebookSubsetRestriction_n4TxAntenna_tm6_present)
        return codebookSubsetRestriction_n4TxAntenna_tm6_internal_value;
    uint16_t tmp = 0;
    return tmp;
}

int AntennaInfoDedicated::codebookSubsetRestriction_n4TxAntenna_tm6_SetValue(uint16_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 16)
    {
        printf("AntennaInfoDedicated::codebookSubsetRestriction_n4TxAntenna_tm6_SetValue() size failure\n");
        return -1;
    }
    codebookSubsetRestriction_n4TxAntenna_tm6_internal_value = value;
    codebookSubsetRestriction_n4TxAntenna_tm6_present = true;
    return 0;
}

std::string AntennaInfoDedicated::codebookSubsetRestriction_n4TxAntenna_tm6_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "n4TxAntenna_tm6 = ";
    out += std::to_string(codebookSubsetRestriction_n4TxAntenna_tm6_internal_value);
    out += "\n";
    return out;
}

std::string AntennaInfoDedicated::codebookSubsetRestriction_n4TxAntenna_tm6_ToStringNoNewLines() const
{
    std::string out = "n4TxAntenna_tm6=";
    out += std::to_string(codebookSubsetRestriction_n4TxAntenna_tm6_internal_value);
    out += ",";
    return out;
}

int AntennaInfoDedicated::codebookSubsetRestriction_n4TxAntenna_tm6_Clear()
{
    codebookSubsetRestriction_n4TxAntenna_tm6_present = false;
    return 0;
}

bool AntennaInfoDedicated::codebookSubsetRestriction_n4TxAntenna_tm6_IsPresent() const
{
    return codebookSubsetRestriction_n4TxAntenna_tm6_present;
}

int AntennaInfoDedicated::ue_TransmitAntennaSelection_Pack(std::vector<uint8_t> &bits)
{
    if(!ue_TransmitAntennaSelection_present)
    {
        printf("AntennaInfoDedicated::ue_TransmitAntennaSelection_Pack() presence failure\n");
        return -1;
    }
    // Extension indicator

    // Choice
    for(uint32_t i=0; i<1; i++)
        bits.push_back((ue_TransmitAntennaSelection_internal_choice >> (1-i-1)) & 1);

    // Fields
    if(ue_TransmitAntennaSelection_internal_choice == k_ue_TransmitAntennaSelection_release)
    {
        if(0 != ue_TransmitAntennaSelection_release_Pack(bits))
        {
            printf("AntennaInfoDedicated::ue_TransmitAntennaSelection_release pack failure\n");
            return -1;
        }
    }
    if(ue_TransmitAntennaSelection_internal_choice == k_ue_TransmitAntennaSelection_setup)
    {
        if(0 != ue_TransmitAntennaSelection_setup_Pack(bits))
        {
            printf("AntennaInfoDedicated::ue_TransmitAntennaSelection_setup pack failure\n");
            return -1;
        }
    }
    return 0;
}

int AntennaInfoDedicated::ue_TransmitAntennaSelection_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return ue_TransmitAntennaSelection_Unpack(bits, idx);
}

int AntennaInfoDedicated::ue_TransmitAntennaSelection_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 1) > bits.size())
    {
        printf("AntennaInfoDedicated::ue_TransmitAntennaSelection_Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<1; i++)
        packed_val |= bits[idx++] << (1-i-1);

    if((AntennaInfoDedicated::ue_TransmitAntennaSelection_Enum)packed_val > k_ue_TransmitAntennaSelection_setup)
    {
        printf("AntennaInfoDedicated::ue_TransmitAntennaSelection_Unpack() choice range failure\n");
        return -1;
    }
    ue_TransmitAntennaSelection_internal_choice = (AntennaInfoDedicated::ue_TransmitAntennaSelection_Enum)packed_val;
    ue_TransmitAntennaSelection_present = true;

    // Fields
    if(ue_TransmitAntennaSelection_internal_choice == k_ue_TransmitAntennaSelection_release)
    {
        if(0 != ue_TransmitAntennaSelection_release_Unpack(bits, idx))
        {
            printf("AntennaInfoDedicated::ue_TransmitAntennaSelection_release unpack failure\n");
            return -1;
        }
    }
    if(ue_TransmitAntennaSelection_internal_choice == k_ue_TransmitAntennaSelection_setup)
    {
        if(0 != ue_TransmitAntennaSelection_setup_Unpack(bits, idx))
        {
            printf("AntennaInfoDedicated::ue_TransmitAntennaSelection_setup unpack failure\n");
            return -1;
        }
    }
    return 0;
}

AntennaInfoDedicated::ue_TransmitAntennaSelection_Enum AntennaInfoDedicated::ue_TransmitAntennaSelection_Choice() const
{
    if(ue_TransmitAntennaSelection_present)
        return ue_TransmitAntennaSelection_internal_choice;
    return (AntennaInfoDedicated::ue_TransmitAntennaSelection_Enum)0;
}

int AntennaInfoDedicated::ue_TransmitAntennaSelection_SetChoice(AntennaInfoDedicated::ue_TransmitAntennaSelection_Enum choice)
{
    ue_TransmitAntennaSelection_internal_choice = choice;
    ue_TransmitAntennaSelection_present = true;
    return 0;
}

std::string AntennaInfoDedicated::ue_TransmitAntennaSelection_ChoiceToString(ue_TransmitAntennaSelection_Enum value) const
{
    if(k_ue_TransmitAntennaSelection_release == value)
        return "ue_TransmitAntennaSelection_release";
    if(k_ue_TransmitAntennaSelection_setup == value)
        return "ue_TransmitAntennaSelection_setup";
    return "";
}

uint64_t AntennaInfoDedicated::ue_TransmitAntennaSelection_NumberOfChoices() const
{
    return 2;
}

std::string AntennaInfoDedicated::ue_TransmitAntennaSelection_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ue_TransmitAntennaSelection = " + ue_TransmitAntennaSelection_ChoiceToString(ue_TransmitAntennaSelection_internal_choice) + ":\n";
    if(ue_TransmitAntennaSelection_internal_choice == k_ue_TransmitAntennaSelection_setup)
        out += ue_TransmitAntennaSelection_setup_ToString(indent+1);
    return out;
}

std::string AntennaInfoDedicated::ue_TransmitAntennaSelection_ToStringNoNewLines() const
{
    std::string out = "ue_TransmitAntennaSelection=" + ue_TransmitAntennaSelection_ChoiceToString(ue_TransmitAntennaSelection_internal_choice) + ",";
    if(ue_TransmitAntennaSelection_internal_choice == k_ue_TransmitAntennaSelection_setup)
        out += ue_TransmitAntennaSelection_setup_ToStringNoNewLines();
    return out;
}

int AntennaInfoDedicated::ue_TransmitAntennaSelection_Clear()
{
    ue_TransmitAntennaSelection_present = false;
    return 0;
}

bool AntennaInfoDedicated::ue_TransmitAntennaSelection_IsPresent() const
{
    return ue_TransmitAntennaSelection_present;
}

int AntennaInfoDedicated::ue_TransmitAntennaSelection_setup_Pack(std::vector<uint8_t> &bits)
{
    if(!ue_TransmitAntennaSelection_setup_present)
    {
        printf("AntennaInfoDedicated::ue_TransmitAntennaSelection_setup_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((ue_TransmitAntennaSelection_setup_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int AntennaInfoDedicated::ue_TransmitAntennaSelection_setup_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return ue_TransmitAntennaSelection_setup_Unpack(bits, idx);
}

int AntennaInfoDedicated::ue_TransmitAntennaSelection_setup_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("AntennaInfoDedicated::ue_TransmitAntennaSelection_setup_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 1)
    {
        printf("AntennaInfoDedicated::ue_TransmitAntennaSelection_setup_Unpack() max failure\n");
        return -1;
    }
    ue_TransmitAntennaSelection_setup_internal_value = (ue_TransmitAntennaSelection_setup_Enum)packed_val;
    ue_TransmitAntennaSelection_setup_present = true;
    return 0;
}

AntennaInfoDedicated::ue_TransmitAntennaSelection_setup_Enum AntennaInfoDedicated::ue_TransmitAntennaSelection_setup_Value() const
{
    if(ue_TransmitAntennaSelection_setup_present)
        return ue_TransmitAntennaSelection_setup_internal_value;
    return (AntennaInfoDedicated::ue_TransmitAntennaSelection_setup_Enum)0;
}

int AntennaInfoDedicated::ue_TransmitAntennaSelection_setup_SetValue(ue_TransmitAntennaSelection_setup_Enum value)
{
    ue_TransmitAntennaSelection_setup_internal_value = value;
    ue_TransmitAntennaSelection_setup_present = true;
    return 0;
}

int AntennaInfoDedicated::ue_TransmitAntennaSelection_setup_SetValue(std::string value)
{
    if("closedLoop" == value)
    {
        ue_TransmitAntennaSelection_setup_internal_value = k_ue_TransmitAntennaSelection_setup_closedLoop;
        ue_TransmitAntennaSelection_setup_present = true;
        return 0;
    }
    if("openLoop" == value)
    {
        ue_TransmitAntennaSelection_setup_internal_value = k_ue_TransmitAntennaSelection_setup_openLoop;
        ue_TransmitAntennaSelection_setup_present = true;
        return 0;
    }
    return 1;
}

std::string AntennaInfoDedicated::ue_TransmitAntennaSelection_setup_ValueToString(ue_TransmitAntennaSelection_setup_Enum value) const
{
    if(k_ue_TransmitAntennaSelection_setup_closedLoop == value)
        return "closedLoop";
    if(k_ue_TransmitAntennaSelection_setup_openLoop == value)
        return "openLoop";
    return "";
}

uint64_t AntennaInfoDedicated::ue_TransmitAntennaSelection_setup_NumberOfValues() const
{
    return 2;
}

std::string AntennaInfoDedicated::ue_TransmitAntennaSelection_setup_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "setup = " + ue_TransmitAntennaSelection_setup_ValueToString(ue_TransmitAntennaSelection_setup_internal_value) + "\n";
    return out;
}

std::string AntennaInfoDedicated::ue_TransmitAntennaSelection_setup_ToStringNoNewLines() const
{
    std::string out = "setup=" + ue_TransmitAntennaSelection_setup_ValueToString(ue_TransmitAntennaSelection_setup_internal_value) + ",";
    return out;
}

int AntennaInfoDedicated::ue_TransmitAntennaSelection_setup_Clear()
{
    ue_TransmitAntennaSelection_setup_present = false;
    return 0;
}

bool AntennaInfoDedicated::ue_TransmitAntennaSelection_setup_IsPresent() const
{
    return ue_TransmitAntennaSelection_setup_present;
}

