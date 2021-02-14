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

#include "AntennaInfoDedicated_r10.h"

#include <cmath>

int AntennaInfoDedicated_r10::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(codebookSubsetRestriction_r10_IsPresent());

    // Fields
    {
        if(0 != transmissionMode_r10_Pack(bits))
        {
            printf("AntennaInfoDedicated_r10:: field pack failure\n");
            return -1;
        }
    }
    if(codebookSubsetRestriction_r10_IsPresent())
    {
        if(0 != codebookSubsetRestriction_r10_Pack(bits))
        {
            printf("AntennaInfoDedicated_r10:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != ue_TransmitAntennaSelection_r10_Pack(bits))
        {
            printf("AntennaInfoDedicated_r10:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int AntennaInfoDedicated_r10::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int AntennaInfoDedicated_r10::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("AntennaInfoDedicated_r10::Unpack() index out of bounds for optional indiator codebookSubsetRestriction_r10\n");
        return -1;
    }
    codebookSubsetRestriction_r10_present = bits[idx++];

    // Fields
    {
        if(0 != transmissionMode_r10_Unpack(bits, idx))
        {
            printf("AntennaInfoDedicated_r10:: field unpack failure\n");
            return -1;
        }
    }
    if(codebookSubsetRestriction_r10_present)
    {
        if(0 != codebookSubsetRestriction_r10_Unpack(bits, idx))
        {
            printf("AntennaInfoDedicated_r10:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != ue_TransmitAntennaSelection_r10_Unpack(bits, idx))
        {
            printf("AntennaInfoDedicated_r10:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string AntennaInfoDedicated_r10::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "AntennaInfoDedicated_r10:\n";
    out += transmissionMode_r10_ToString(indent+1);
    if(codebookSubsetRestriction_r10_IsPresent())
        out += codebookSubsetRestriction_r10_ToString(indent+1);
    out += ue_TransmitAntennaSelection_r10_ToString(indent+1);
    return out;
}

std::string AntennaInfoDedicated_r10::ToStringNoNewLines() const
{
    std::string out = "AntennaInfoDedicated_r10:";
    out += transmissionMode_r10_ToStringNoNewLines();
    if(codebookSubsetRestriction_r10_IsPresent())
        out += codebookSubsetRestriction_r10_ToStringNoNewLines();
    out += ue_TransmitAntennaSelection_r10_ToStringNoNewLines();
    return out;
}

int AntennaInfoDedicated_r10::transmissionMode_r10_Pack(std::vector<uint8_t> &bits)
{
    if(!transmissionMode_r10_present)
    {
        printf("AntennaInfoDedicated_r10::transmissionMode_r10_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 4;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((transmissionMode_r10_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int AntennaInfoDedicated_r10::transmissionMode_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return transmissionMode_r10_Unpack(bits, idx);
}

int AntennaInfoDedicated_r10::transmissionMode_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 4;
    if((idx + N_bits) > bits.size())
    {
        printf("AntennaInfoDedicated_r10::transmissionMode_r10_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 15)
    {
        printf("AntennaInfoDedicated_r10::transmissionMode_r10_Unpack() max failure\n");
        return -1;
    }
    transmissionMode_r10_internal_value = (transmissionMode_r10_Enum)packed_val;
    transmissionMode_r10_present = true;
    return 0;
}

AntennaInfoDedicated_r10::transmissionMode_r10_Enum AntennaInfoDedicated_r10::transmissionMode_r10_Value() const
{
    if(transmissionMode_r10_present)
        return transmissionMode_r10_internal_value;
    return (AntennaInfoDedicated_r10::transmissionMode_r10_Enum)0;
}

int AntennaInfoDedicated_r10::transmissionMode_r10_SetValue(transmissionMode_r10_Enum value)
{
    transmissionMode_r10_internal_value = value;
    transmissionMode_r10_present = true;
    return 0;
}

int AntennaInfoDedicated_r10::transmissionMode_r10_SetValue(std::string value)
{
    if("tm1" == value)
    {
        transmissionMode_r10_internal_value = k_transmissionMode_r10_tm1;
        transmissionMode_r10_present = true;
        return 0;
    }
    if("tm2" == value)
    {
        transmissionMode_r10_internal_value = k_transmissionMode_r10_tm2;
        transmissionMode_r10_present = true;
        return 0;
    }
    if("tm3" == value)
    {
        transmissionMode_r10_internal_value = k_transmissionMode_r10_tm3;
        transmissionMode_r10_present = true;
        return 0;
    }
    if("tm4" == value)
    {
        transmissionMode_r10_internal_value = k_transmissionMode_r10_tm4;
        transmissionMode_r10_present = true;
        return 0;
    }
    if("tm5" == value)
    {
        transmissionMode_r10_internal_value = k_transmissionMode_r10_tm5;
        transmissionMode_r10_present = true;
        return 0;
    }
    if("tm6" == value)
    {
        transmissionMode_r10_internal_value = k_transmissionMode_r10_tm6;
        transmissionMode_r10_present = true;
        return 0;
    }
    if("tm7" == value)
    {
        transmissionMode_r10_internal_value = k_transmissionMode_r10_tm7;
        transmissionMode_r10_present = true;
        return 0;
    }
    if("tm8_v920" == value)
    {
        transmissionMode_r10_internal_value = k_transmissionMode_r10_tm8_v920;
        transmissionMode_r10_present = true;
        return 0;
    }
    if("tm9_v10x0" == value)
    {
        transmissionMode_r10_internal_value = k_transmissionMode_r10_tm9_v10x0;
        transmissionMode_r10_present = true;
        return 0;
    }
    if("spare7" == value)
    {
        transmissionMode_r10_internal_value = k_transmissionMode_r10_spare7;
        transmissionMode_r10_present = true;
        return 0;
    }
    if("spare6" == value)
    {
        transmissionMode_r10_internal_value = k_transmissionMode_r10_spare6;
        transmissionMode_r10_present = true;
        return 0;
    }
    if("spare5" == value)
    {
        transmissionMode_r10_internal_value = k_transmissionMode_r10_spare5;
        transmissionMode_r10_present = true;
        return 0;
    }
    if("spare4" == value)
    {
        transmissionMode_r10_internal_value = k_transmissionMode_r10_spare4;
        transmissionMode_r10_present = true;
        return 0;
    }
    if("spare3" == value)
    {
        transmissionMode_r10_internal_value = k_transmissionMode_r10_spare3;
        transmissionMode_r10_present = true;
        return 0;
    }
    if("spare2" == value)
    {
        transmissionMode_r10_internal_value = k_transmissionMode_r10_spare2;
        transmissionMode_r10_present = true;
        return 0;
    }
    if("spare1" == value)
    {
        transmissionMode_r10_internal_value = k_transmissionMode_r10_spare1;
        transmissionMode_r10_present = true;
        return 0;
    }
    return 1;
}

std::string AntennaInfoDedicated_r10::transmissionMode_r10_ValueToString(transmissionMode_r10_Enum value) const
{
    if(k_transmissionMode_r10_tm1 == value)
        return "tm1";
    if(k_transmissionMode_r10_tm2 == value)
        return "tm2";
    if(k_transmissionMode_r10_tm3 == value)
        return "tm3";
    if(k_transmissionMode_r10_tm4 == value)
        return "tm4";
    if(k_transmissionMode_r10_tm5 == value)
        return "tm5";
    if(k_transmissionMode_r10_tm6 == value)
        return "tm6";
    if(k_transmissionMode_r10_tm7 == value)
        return "tm7";
    if(k_transmissionMode_r10_tm8_v920 == value)
        return "tm8_v920";
    if(k_transmissionMode_r10_tm9_v10x0 == value)
        return "tm9_v10x0";
    if(k_transmissionMode_r10_spare7 == value)
        return "spare7";
    if(k_transmissionMode_r10_spare6 == value)
        return "spare6";
    if(k_transmissionMode_r10_spare5 == value)
        return "spare5";
    if(k_transmissionMode_r10_spare4 == value)
        return "spare4";
    if(k_transmissionMode_r10_spare3 == value)
        return "spare3";
    if(k_transmissionMode_r10_spare2 == value)
        return "spare2";
    if(k_transmissionMode_r10_spare1 == value)
        return "spare1";
    return "";
}

uint64_t AntennaInfoDedicated_r10::transmissionMode_r10_NumberOfValues() const
{
    return 16;
}

std::string AntennaInfoDedicated_r10::transmissionMode_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "transmissionMode_r10 = " + transmissionMode_r10_ValueToString(transmissionMode_r10_internal_value) + "\n";
    return out;
}

std::string AntennaInfoDedicated_r10::transmissionMode_r10_ToStringNoNewLines() const
{
    std::string out = "transmissionMode_r10=" + transmissionMode_r10_ValueToString(transmissionMode_r10_internal_value) + ",";
    return out;
}

int AntennaInfoDedicated_r10::transmissionMode_r10_Clear()
{
    transmissionMode_r10_present = false;
    return 0;
}

bool AntennaInfoDedicated_r10::transmissionMode_r10_IsPresent() const
{
    return transmissionMode_r10_present;
}

int AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_Pack(std::vector<uint8_t> &bits)
{
    if(!codebookSubsetRestriction_r10_present)
    {
        printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_Pack() presence failure\n");
        return -1;
    }
    // Extension indicator
    bits.push_back(0);

    // Choice
    for(uint32_t i=0; i<4; i++)
        bits.push_back((codebookSubsetRestriction_r10_internal_choice >> (4-i-1)) & 1);

    // Fields
    if(codebookSubsetRestriction_r10_internal_choice == k_codebookSubsetRestriction_r10_n2TxAntenna_tm3)
    {
        if(0 != codebookSubsetRestriction_r10_n2TxAntenna_tm3_Pack(bits))
        {
            printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm3 pack failure\n");
            return -1;
        }
    }
    if(codebookSubsetRestriction_r10_internal_choice == k_codebookSubsetRestriction_r10_n4TxAntenna_tm3)
    {
        if(0 != codebookSubsetRestriction_r10_n4TxAntenna_tm3_Pack(bits))
        {
            printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm3 pack failure\n");
            return -1;
        }
    }
    if(codebookSubsetRestriction_r10_internal_choice == k_codebookSubsetRestriction_r10_n2TxAntenna_tm4)
    {
        if(0 != codebookSubsetRestriction_r10_n2TxAntenna_tm4_Pack(bits))
        {
            printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm4 pack failure\n");
            return -1;
        }
    }
    if(codebookSubsetRestriction_r10_internal_choice == k_codebookSubsetRestriction_r10_n4TxAntenna_tm4)
    {
        if(0 != codebookSubsetRestriction_r10_n4TxAntenna_tm4_Pack(bits))
        {
            printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm4 pack failure\n");
            return -1;
        }
    }
    if(codebookSubsetRestriction_r10_internal_choice == k_codebookSubsetRestriction_r10_n2TxAntenna_tm5)
    {
        if(0 != codebookSubsetRestriction_r10_n2TxAntenna_tm5_Pack(bits))
        {
            printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm5 pack failure\n");
            return -1;
        }
    }
    if(codebookSubsetRestriction_r10_internal_choice == k_codebookSubsetRestriction_r10_n4TxAntenna_tm5)
    {
        if(0 != codebookSubsetRestriction_r10_n4TxAntenna_tm5_Pack(bits))
        {
            printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm5 pack failure\n");
            return -1;
        }
    }
    if(codebookSubsetRestriction_r10_internal_choice == k_codebookSubsetRestriction_r10_n2TxAntenna_tm6)
    {
        if(0 != codebookSubsetRestriction_r10_n2TxAntenna_tm6_Pack(bits))
        {
            printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm6 pack failure\n");
            return -1;
        }
    }
    if(codebookSubsetRestriction_r10_internal_choice == k_codebookSubsetRestriction_r10_n4TxAntenna_tm6)
    {
        if(0 != codebookSubsetRestriction_r10_n4TxAntenna_tm6_Pack(bits))
        {
            printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm6 pack failure\n");
            return -1;
        }
    }
    if(codebookSubsetRestriction_r10_internal_choice == k_codebookSubsetRestriction_r10_n2TxAntenna_tm8_r9)
    {
        if(0 != codebookSubsetRestriction_r10_n2TxAntenna_tm8_r9_Pack(bits))
        {
            printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm8_r9 pack failure\n");
            return -1;
        }
    }
    if(codebookSubsetRestriction_r10_internal_choice == k_codebookSubsetRestriction_r10_n4TxAntenna_tm8_r9)
    {
        if(0 != codebookSubsetRestriction_r10_n4TxAntenna_tm8_r9_Pack(bits))
        {
            printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm8_r9 pack failure\n");
            return -1;
        }
    }
    if(codebookSubsetRestriction_r10_internal_choice == k_codebookSubsetRestriction_r10_n2TxAntenna_tm9_r10)
    {
        if(0 != codebookSubsetRestriction_r10_n2TxAntenna_tm9_r10_Pack(bits))
        {
            printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm9_r10 pack failure\n");
            return -1;
        }
    }
    if(codebookSubsetRestriction_r10_internal_choice == k_codebookSubsetRestriction_r10_n4TxAntenna_tm9_r10)
    {
        if(0 != codebookSubsetRestriction_r10_n4TxAntenna_tm9_r10_Pack(bits))
        {
            printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm9_r10 pack failure\n");
            return -1;
        }
    }
    if(codebookSubsetRestriction_r10_internal_choice == k_codebookSubsetRestriction_r10_n8TxAntenna_tm9_r10)
    {
        if(0 != codebookSubsetRestriction_r10_n8TxAntenna_tm9_r10_Pack(bits))
        {
            printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n8TxAntenna_tm9_r10 pack failure\n");
            return -1;
        }
    }
    return 0;
}

int AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return codebookSubsetRestriction_r10_Unpack(bits, idx);
}

int AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_Unpack() index out of bounds for extension\n");
        return -1;
    }
    idx++;

    // Choice
    uint32_t packed_val = 0;
    if((idx + 4) > bits.size())
    {
        printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<4; i++)
        packed_val |= bits[idx++] << (4-i-1);

    if((AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_Enum)packed_val > k_codebookSubsetRestriction_r10_n8TxAntenna_tm9_r10)
    {
        printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_Unpack() choice range failure\n");
        return -1;
    }
    codebookSubsetRestriction_r10_internal_choice = (AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_Enum)packed_val;
    codebookSubsetRestriction_r10_present = true;

    // Fields
    if(codebookSubsetRestriction_r10_internal_choice == k_codebookSubsetRestriction_r10_n2TxAntenna_tm3)
    {
        if(0 != codebookSubsetRestriction_r10_n2TxAntenna_tm3_Unpack(bits, idx))
        {
            printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm3 unpack failure\n");
            return -1;
        }
    }
    if(codebookSubsetRestriction_r10_internal_choice == k_codebookSubsetRestriction_r10_n4TxAntenna_tm3)
    {
        if(0 != codebookSubsetRestriction_r10_n4TxAntenna_tm3_Unpack(bits, idx))
        {
            printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm3 unpack failure\n");
            return -1;
        }
    }
    if(codebookSubsetRestriction_r10_internal_choice == k_codebookSubsetRestriction_r10_n2TxAntenna_tm4)
    {
        if(0 != codebookSubsetRestriction_r10_n2TxAntenna_tm4_Unpack(bits, idx))
        {
            printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm4 unpack failure\n");
            return -1;
        }
    }
    if(codebookSubsetRestriction_r10_internal_choice == k_codebookSubsetRestriction_r10_n4TxAntenna_tm4)
    {
        if(0 != codebookSubsetRestriction_r10_n4TxAntenna_tm4_Unpack(bits, idx))
        {
            printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm4 unpack failure\n");
            return -1;
        }
    }
    if(codebookSubsetRestriction_r10_internal_choice == k_codebookSubsetRestriction_r10_n2TxAntenna_tm5)
    {
        if(0 != codebookSubsetRestriction_r10_n2TxAntenna_tm5_Unpack(bits, idx))
        {
            printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm5 unpack failure\n");
            return -1;
        }
    }
    if(codebookSubsetRestriction_r10_internal_choice == k_codebookSubsetRestriction_r10_n4TxAntenna_tm5)
    {
        if(0 != codebookSubsetRestriction_r10_n4TxAntenna_tm5_Unpack(bits, idx))
        {
            printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm5 unpack failure\n");
            return -1;
        }
    }
    if(codebookSubsetRestriction_r10_internal_choice == k_codebookSubsetRestriction_r10_n2TxAntenna_tm6)
    {
        if(0 != codebookSubsetRestriction_r10_n2TxAntenna_tm6_Unpack(bits, idx))
        {
            printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm6 unpack failure\n");
            return -1;
        }
    }
    if(codebookSubsetRestriction_r10_internal_choice == k_codebookSubsetRestriction_r10_n4TxAntenna_tm6)
    {
        if(0 != codebookSubsetRestriction_r10_n4TxAntenna_tm6_Unpack(bits, idx))
        {
            printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm6 unpack failure\n");
            return -1;
        }
    }
    if(codebookSubsetRestriction_r10_internal_choice == k_codebookSubsetRestriction_r10_n2TxAntenna_tm8_r9)
    {
        if(0 != codebookSubsetRestriction_r10_n2TxAntenna_tm8_r9_Unpack(bits, idx))
        {
            printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm8_r9 unpack failure\n");
            return -1;
        }
    }
    if(codebookSubsetRestriction_r10_internal_choice == k_codebookSubsetRestriction_r10_n4TxAntenna_tm8_r9)
    {
        if(0 != codebookSubsetRestriction_r10_n4TxAntenna_tm8_r9_Unpack(bits, idx))
        {
            printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm8_r9 unpack failure\n");
            return -1;
        }
    }
    if(codebookSubsetRestriction_r10_internal_choice == k_codebookSubsetRestriction_r10_n2TxAntenna_tm9_r10)
    {
        if(0 != codebookSubsetRestriction_r10_n2TxAntenna_tm9_r10_Unpack(bits, idx))
        {
            printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm9_r10 unpack failure\n");
            return -1;
        }
    }
    if(codebookSubsetRestriction_r10_internal_choice == k_codebookSubsetRestriction_r10_n4TxAntenna_tm9_r10)
    {
        if(0 != codebookSubsetRestriction_r10_n4TxAntenna_tm9_r10_Unpack(bits, idx))
        {
            printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm9_r10 unpack failure\n");
            return -1;
        }
    }
    if(codebookSubsetRestriction_r10_internal_choice == k_codebookSubsetRestriction_r10_n8TxAntenna_tm9_r10)
    {
        if(0 != codebookSubsetRestriction_r10_n8TxAntenna_tm9_r10_Unpack(bits, idx))
        {
            printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n8TxAntenna_tm9_r10 unpack failure\n");
            return -1;
        }
    }
    return 0;
}

AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_Enum AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_Choice() const
{
    if(codebookSubsetRestriction_r10_present)
        return codebookSubsetRestriction_r10_internal_choice;
    return (AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_Enum)0;
}

int AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_SetChoice(AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_Enum choice)
{
    codebookSubsetRestriction_r10_internal_choice = choice;
    codebookSubsetRestriction_r10_present = true;
    return 0;
}

std::string AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_ChoiceToString(codebookSubsetRestriction_r10_Enum value) const
{
    if(k_codebookSubsetRestriction_r10_n2TxAntenna_tm3 == value)
        return "codebookSubsetRestriction_r10_n2TxAntenna_tm3";
    if(k_codebookSubsetRestriction_r10_n4TxAntenna_tm3 == value)
        return "codebookSubsetRestriction_r10_n4TxAntenna_tm3";
    if(k_codebookSubsetRestriction_r10_n2TxAntenna_tm4 == value)
        return "codebookSubsetRestriction_r10_n2TxAntenna_tm4";
    if(k_codebookSubsetRestriction_r10_n4TxAntenna_tm4 == value)
        return "codebookSubsetRestriction_r10_n4TxAntenna_tm4";
    if(k_codebookSubsetRestriction_r10_n2TxAntenna_tm5 == value)
        return "codebookSubsetRestriction_r10_n2TxAntenna_tm5";
    if(k_codebookSubsetRestriction_r10_n4TxAntenna_tm5 == value)
        return "codebookSubsetRestriction_r10_n4TxAntenna_tm5";
    if(k_codebookSubsetRestriction_r10_n2TxAntenna_tm6 == value)
        return "codebookSubsetRestriction_r10_n2TxAntenna_tm6";
    if(k_codebookSubsetRestriction_r10_n4TxAntenna_tm6 == value)
        return "codebookSubsetRestriction_r10_n4TxAntenna_tm6";
    if(k_codebookSubsetRestriction_r10_n2TxAntenna_tm8_r9 == value)
        return "codebookSubsetRestriction_r10_n2TxAntenna_tm8_r9";
    if(k_codebookSubsetRestriction_r10_n4TxAntenna_tm8_r9 == value)
        return "codebookSubsetRestriction_r10_n4TxAntenna_tm8_r9";
    if(k_codebookSubsetRestriction_r10_n2TxAntenna_tm9_r10 == value)
        return "codebookSubsetRestriction_r10_n2TxAntenna_tm9_r10";
    if(k_codebookSubsetRestriction_r10_n4TxAntenna_tm9_r10 == value)
        return "codebookSubsetRestriction_r10_n4TxAntenna_tm9_r10";
    if(k_codebookSubsetRestriction_r10_n8TxAntenna_tm9_r10 == value)
        return "codebookSubsetRestriction_r10_n8TxAntenna_tm9_r10";
    return "";
}

uint64_t AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_NumberOfChoices() const
{
    return 13;
}

std::string AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "codebookSubsetRestriction_r10 = " + codebookSubsetRestriction_r10_ChoiceToString(codebookSubsetRestriction_r10_internal_choice) + ":\n";
    if(codebookSubsetRestriction_r10_internal_choice == k_codebookSubsetRestriction_r10_n2TxAntenna_tm3)
        out += codebookSubsetRestriction_r10_n2TxAntenna_tm3_ToString(indent+1);
    if(codebookSubsetRestriction_r10_internal_choice == k_codebookSubsetRestriction_r10_n4TxAntenna_tm3)
        out += codebookSubsetRestriction_r10_n4TxAntenna_tm3_ToString(indent+1);
    if(codebookSubsetRestriction_r10_internal_choice == k_codebookSubsetRestriction_r10_n2TxAntenna_tm4)
        out += codebookSubsetRestriction_r10_n2TxAntenna_tm4_ToString(indent+1);
    if(codebookSubsetRestriction_r10_internal_choice == k_codebookSubsetRestriction_r10_n4TxAntenna_tm4)
        out += codebookSubsetRestriction_r10_n4TxAntenna_tm4_ToString(indent+1);
    if(codebookSubsetRestriction_r10_internal_choice == k_codebookSubsetRestriction_r10_n2TxAntenna_tm5)
        out += codebookSubsetRestriction_r10_n2TxAntenna_tm5_ToString(indent+1);
    if(codebookSubsetRestriction_r10_internal_choice == k_codebookSubsetRestriction_r10_n4TxAntenna_tm5)
        out += codebookSubsetRestriction_r10_n4TxAntenna_tm5_ToString(indent+1);
    if(codebookSubsetRestriction_r10_internal_choice == k_codebookSubsetRestriction_r10_n2TxAntenna_tm6)
        out += codebookSubsetRestriction_r10_n2TxAntenna_tm6_ToString(indent+1);
    if(codebookSubsetRestriction_r10_internal_choice == k_codebookSubsetRestriction_r10_n4TxAntenna_tm6)
        out += codebookSubsetRestriction_r10_n4TxAntenna_tm6_ToString(indent+1);
    if(codebookSubsetRestriction_r10_internal_choice == k_codebookSubsetRestriction_r10_n2TxAntenna_tm8_r9)
        out += codebookSubsetRestriction_r10_n2TxAntenna_tm8_r9_ToString(indent+1);
    if(codebookSubsetRestriction_r10_internal_choice == k_codebookSubsetRestriction_r10_n4TxAntenna_tm8_r9)
        out += codebookSubsetRestriction_r10_n4TxAntenna_tm8_r9_ToString(indent+1);
    if(codebookSubsetRestriction_r10_internal_choice == k_codebookSubsetRestriction_r10_n2TxAntenna_tm9_r10)
        out += codebookSubsetRestriction_r10_n2TxAntenna_tm9_r10_ToString(indent+1);
    if(codebookSubsetRestriction_r10_internal_choice == k_codebookSubsetRestriction_r10_n4TxAntenna_tm9_r10)
        out += codebookSubsetRestriction_r10_n4TxAntenna_tm9_r10_ToString(indent+1);
    if(codebookSubsetRestriction_r10_internal_choice == k_codebookSubsetRestriction_r10_n8TxAntenna_tm9_r10)
        out += codebookSubsetRestriction_r10_n8TxAntenna_tm9_r10_ToString(indent+1);
    return out;
}

std::string AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_ToStringNoNewLines() const
{
    std::string out = "codebookSubsetRestriction_r10=" + codebookSubsetRestriction_r10_ChoiceToString(codebookSubsetRestriction_r10_internal_choice) + ",";
    if(codebookSubsetRestriction_r10_internal_choice == k_codebookSubsetRestriction_r10_n2TxAntenna_tm3)
        out += codebookSubsetRestriction_r10_n2TxAntenna_tm3_ToStringNoNewLines();
    if(codebookSubsetRestriction_r10_internal_choice == k_codebookSubsetRestriction_r10_n4TxAntenna_tm3)
        out += codebookSubsetRestriction_r10_n4TxAntenna_tm3_ToStringNoNewLines();
    if(codebookSubsetRestriction_r10_internal_choice == k_codebookSubsetRestriction_r10_n2TxAntenna_tm4)
        out += codebookSubsetRestriction_r10_n2TxAntenna_tm4_ToStringNoNewLines();
    if(codebookSubsetRestriction_r10_internal_choice == k_codebookSubsetRestriction_r10_n4TxAntenna_tm4)
        out += codebookSubsetRestriction_r10_n4TxAntenna_tm4_ToStringNoNewLines();
    if(codebookSubsetRestriction_r10_internal_choice == k_codebookSubsetRestriction_r10_n2TxAntenna_tm5)
        out += codebookSubsetRestriction_r10_n2TxAntenna_tm5_ToStringNoNewLines();
    if(codebookSubsetRestriction_r10_internal_choice == k_codebookSubsetRestriction_r10_n4TxAntenna_tm5)
        out += codebookSubsetRestriction_r10_n4TxAntenna_tm5_ToStringNoNewLines();
    if(codebookSubsetRestriction_r10_internal_choice == k_codebookSubsetRestriction_r10_n2TxAntenna_tm6)
        out += codebookSubsetRestriction_r10_n2TxAntenna_tm6_ToStringNoNewLines();
    if(codebookSubsetRestriction_r10_internal_choice == k_codebookSubsetRestriction_r10_n4TxAntenna_tm6)
        out += codebookSubsetRestriction_r10_n4TxAntenna_tm6_ToStringNoNewLines();
    if(codebookSubsetRestriction_r10_internal_choice == k_codebookSubsetRestriction_r10_n2TxAntenna_tm8_r9)
        out += codebookSubsetRestriction_r10_n2TxAntenna_tm8_r9_ToStringNoNewLines();
    if(codebookSubsetRestriction_r10_internal_choice == k_codebookSubsetRestriction_r10_n4TxAntenna_tm8_r9)
        out += codebookSubsetRestriction_r10_n4TxAntenna_tm8_r9_ToStringNoNewLines();
    if(codebookSubsetRestriction_r10_internal_choice == k_codebookSubsetRestriction_r10_n2TxAntenna_tm9_r10)
        out += codebookSubsetRestriction_r10_n2TxAntenna_tm9_r10_ToStringNoNewLines();
    if(codebookSubsetRestriction_r10_internal_choice == k_codebookSubsetRestriction_r10_n4TxAntenna_tm9_r10)
        out += codebookSubsetRestriction_r10_n4TxAntenna_tm9_r10_ToStringNoNewLines();
    if(codebookSubsetRestriction_r10_internal_choice == k_codebookSubsetRestriction_r10_n8TxAntenna_tm9_r10)
        out += codebookSubsetRestriction_r10_n8TxAntenna_tm9_r10_ToStringNoNewLines();
    return out;
}

int AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_Clear()
{
    codebookSubsetRestriction_r10_present = false;
    return 0;
}

bool AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_IsPresent() const
{
    return codebookSubsetRestriction_r10_present;
}

int AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm3_Pack(std::vector<uint8_t> &bits)
{
    if(!codebookSubsetRestriction_r10_n2TxAntenna_tm3_present)
    {
        printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm3_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 2;
    if(size < 2 || size > 2)
    {
        printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm3_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((codebookSubsetRestriction_r10_n2TxAntenna_tm3_internal_value >> (2-i-1)) & 1);
    return 0;
}

int AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm3_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return codebookSubsetRestriction_r10_n2TxAntenna_tm3_Unpack(bits, idx);
}

int AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm3_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 2;
    if(size < 2 || size > 2)
    {
        printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm3_Unpack() size failure\n");
        return -1;
    }
    codebookSubsetRestriction_r10_n2TxAntenna_tm3_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm3_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        codebookSubsetRestriction_r10_n2TxAntenna_tm3_internal_value |= (uint8_t)bits[idx++] << (uint8_t)(2-i-1);
    codebookSubsetRestriction_r10_n2TxAntenna_tm3_present = true;
    return 0;
}

uint8_t AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm3_Value() const
{
    if(codebookSubsetRestriction_r10_n2TxAntenna_tm3_present)
        return codebookSubsetRestriction_r10_n2TxAntenna_tm3_internal_value;
    uint8_t tmp = 0;
    return tmp;
}

int AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm3_SetValue(uint8_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 2)
    {
        printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm3_SetValue() size failure\n");
        return -1;
    }
    codebookSubsetRestriction_r10_n2TxAntenna_tm3_internal_value = value;
    codebookSubsetRestriction_r10_n2TxAntenna_tm3_present = true;
    return 0;
}

std::string AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm3_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "n2TxAntenna_tm3 = ";
    out += std::to_string(codebookSubsetRestriction_r10_n2TxAntenna_tm3_internal_value);
    out += "\n";
    return out;
}

std::string AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm3_ToStringNoNewLines() const
{
    std::string out = "n2TxAntenna_tm3=";
    out += std::to_string(codebookSubsetRestriction_r10_n2TxAntenna_tm3_internal_value);
    out += ",";
    return out;
}

int AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm3_Clear()
{
    codebookSubsetRestriction_r10_n2TxAntenna_tm3_present = false;
    return 0;
}

bool AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm3_IsPresent() const
{
    return codebookSubsetRestriction_r10_n2TxAntenna_tm3_present;
}

int AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm3_Pack(std::vector<uint8_t> &bits)
{
    if(!codebookSubsetRestriction_r10_n4TxAntenna_tm3_present)
    {
        printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm3_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 4;
    if(size < 4 || size > 4)
    {
        printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm3_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((codebookSubsetRestriction_r10_n4TxAntenna_tm3_internal_value >> (4-i-1)) & 1);
    return 0;
}

int AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm3_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return codebookSubsetRestriction_r10_n4TxAntenna_tm3_Unpack(bits, idx);
}

int AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm3_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 4;
    if(size < 4 || size > 4)
    {
        printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm3_Unpack() size failure\n");
        return -1;
    }
    codebookSubsetRestriction_r10_n4TxAntenna_tm3_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm3_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        codebookSubsetRestriction_r10_n4TxAntenna_tm3_internal_value |= (uint8_t)bits[idx++] << (uint8_t)(4-i-1);
    codebookSubsetRestriction_r10_n4TxAntenna_tm3_present = true;
    return 0;
}

uint8_t AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm3_Value() const
{
    if(codebookSubsetRestriction_r10_n4TxAntenna_tm3_present)
        return codebookSubsetRestriction_r10_n4TxAntenna_tm3_internal_value;
    uint8_t tmp = 0;
    return tmp;
}

int AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm3_SetValue(uint8_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 4)
    {
        printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm3_SetValue() size failure\n");
        return -1;
    }
    codebookSubsetRestriction_r10_n4TxAntenna_tm3_internal_value = value;
    codebookSubsetRestriction_r10_n4TxAntenna_tm3_present = true;
    return 0;
}

std::string AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm3_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "n4TxAntenna_tm3 = ";
    out += std::to_string(codebookSubsetRestriction_r10_n4TxAntenna_tm3_internal_value);
    out += "\n";
    return out;
}

std::string AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm3_ToStringNoNewLines() const
{
    std::string out = "n4TxAntenna_tm3=";
    out += std::to_string(codebookSubsetRestriction_r10_n4TxAntenna_tm3_internal_value);
    out += ",";
    return out;
}

int AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm3_Clear()
{
    codebookSubsetRestriction_r10_n4TxAntenna_tm3_present = false;
    return 0;
}

bool AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm3_IsPresent() const
{
    return codebookSubsetRestriction_r10_n4TxAntenna_tm3_present;
}

int AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm4_Pack(std::vector<uint8_t> &bits)
{
    if(!codebookSubsetRestriction_r10_n2TxAntenna_tm4_present)
    {
        printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm4_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 6;
    if(size < 6 || size > 6)
    {
        printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm4_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((codebookSubsetRestriction_r10_n2TxAntenna_tm4_internal_value >> (6-i-1)) & 1);
    return 0;
}

int AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm4_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return codebookSubsetRestriction_r10_n2TxAntenna_tm4_Unpack(bits, idx);
}

int AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm4_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 6;
    if(size < 6 || size > 6)
    {
        printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm4_Unpack() size failure\n");
        return -1;
    }
    codebookSubsetRestriction_r10_n2TxAntenna_tm4_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm4_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        codebookSubsetRestriction_r10_n2TxAntenna_tm4_internal_value |= (uint8_t)bits[idx++] << (uint8_t)(6-i-1);
    codebookSubsetRestriction_r10_n2TxAntenna_tm4_present = true;
    return 0;
}

uint8_t AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm4_Value() const
{
    if(codebookSubsetRestriction_r10_n2TxAntenna_tm4_present)
        return codebookSubsetRestriction_r10_n2TxAntenna_tm4_internal_value;
    uint8_t tmp = 0;
    return tmp;
}

int AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm4_SetValue(uint8_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 6)
    {
        printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm4_SetValue() size failure\n");
        return -1;
    }
    codebookSubsetRestriction_r10_n2TxAntenna_tm4_internal_value = value;
    codebookSubsetRestriction_r10_n2TxAntenna_tm4_present = true;
    return 0;
}

std::string AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm4_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "n2TxAntenna_tm4 = ";
    out += std::to_string(codebookSubsetRestriction_r10_n2TxAntenna_tm4_internal_value);
    out += "\n";
    return out;
}

std::string AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm4_ToStringNoNewLines() const
{
    std::string out = "n2TxAntenna_tm4=";
    out += std::to_string(codebookSubsetRestriction_r10_n2TxAntenna_tm4_internal_value);
    out += ",";
    return out;
}

int AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm4_Clear()
{
    codebookSubsetRestriction_r10_n2TxAntenna_tm4_present = false;
    return 0;
}

bool AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm4_IsPresent() const
{
    return codebookSubsetRestriction_r10_n2TxAntenna_tm4_present;
}

int AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm4_Pack(std::vector<uint8_t> &bits)
{
    if(!codebookSubsetRestriction_r10_n4TxAntenna_tm4_present)
    {
        printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm4_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 64;
    if(size < 64 || size > 64)
    {
        printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm4_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((codebookSubsetRestriction_r10_n4TxAntenna_tm4_internal_value >> (64-i-1)) & 1);
    return 0;
}

int AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm4_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return codebookSubsetRestriction_r10_n4TxAntenna_tm4_Unpack(bits, idx);
}

int AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm4_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 64;
    if(size < 64 || size > 64)
    {
        printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm4_Unpack() size failure\n");
        return -1;
    }
    codebookSubsetRestriction_r10_n4TxAntenna_tm4_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm4_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        codebookSubsetRestriction_r10_n4TxAntenna_tm4_internal_value |= (uint64_t)bits[idx++] << (uint64_t)(64-i-1);
    codebookSubsetRestriction_r10_n4TxAntenna_tm4_present = true;
    return 0;
}

uint64_t AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm4_Value() const
{
    if(codebookSubsetRestriction_r10_n4TxAntenna_tm4_present)
        return codebookSubsetRestriction_r10_n4TxAntenna_tm4_internal_value;
    uint64_t tmp = 0;
    return tmp;
}

int AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm4_SetValue(uint64_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 64)
    {
        printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm4_SetValue() size failure\n");
        return -1;
    }
    codebookSubsetRestriction_r10_n4TxAntenna_tm4_internal_value = value;
    codebookSubsetRestriction_r10_n4TxAntenna_tm4_present = true;
    return 0;
}

std::string AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm4_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "n4TxAntenna_tm4 = ";
    out += std::to_string(codebookSubsetRestriction_r10_n4TxAntenna_tm4_internal_value);
    out += "\n";
    return out;
}

std::string AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm4_ToStringNoNewLines() const
{
    std::string out = "n4TxAntenna_tm4=";
    out += std::to_string(codebookSubsetRestriction_r10_n4TxAntenna_tm4_internal_value);
    out += ",";
    return out;
}

int AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm4_Clear()
{
    codebookSubsetRestriction_r10_n4TxAntenna_tm4_present = false;
    return 0;
}

bool AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm4_IsPresent() const
{
    return codebookSubsetRestriction_r10_n4TxAntenna_tm4_present;
}

int AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm5_Pack(std::vector<uint8_t> &bits)
{
    if(!codebookSubsetRestriction_r10_n2TxAntenna_tm5_present)
    {
        printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm5_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 4;
    if(size < 4 || size > 4)
    {
        printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm5_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((codebookSubsetRestriction_r10_n2TxAntenna_tm5_internal_value >> (4-i-1)) & 1);
    return 0;
}

int AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm5_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return codebookSubsetRestriction_r10_n2TxAntenna_tm5_Unpack(bits, idx);
}

int AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm5_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 4;
    if(size < 4 || size > 4)
    {
        printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm5_Unpack() size failure\n");
        return -1;
    }
    codebookSubsetRestriction_r10_n2TxAntenna_tm5_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm5_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        codebookSubsetRestriction_r10_n2TxAntenna_tm5_internal_value |= (uint8_t)bits[idx++] << (uint8_t)(4-i-1);
    codebookSubsetRestriction_r10_n2TxAntenna_tm5_present = true;
    return 0;
}

uint8_t AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm5_Value() const
{
    if(codebookSubsetRestriction_r10_n2TxAntenna_tm5_present)
        return codebookSubsetRestriction_r10_n2TxAntenna_tm5_internal_value;
    uint8_t tmp = 0;
    return tmp;
}

int AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm5_SetValue(uint8_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 4)
    {
        printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm5_SetValue() size failure\n");
        return -1;
    }
    codebookSubsetRestriction_r10_n2TxAntenna_tm5_internal_value = value;
    codebookSubsetRestriction_r10_n2TxAntenna_tm5_present = true;
    return 0;
}

std::string AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm5_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "n2TxAntenna_tm5 = ";
    out += std::to_string(codebookSubsetRestriction_r10_n2TxAntenna_tm5_internal_value);
    out += "\n";
    return out;
}

std::string AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm5_ToStringNoNewLines() const
{
    std::string out = "n2TxAntenna_tm5=";
    out += std::to_string(codebookSubsetRestriction_r10_n2TxAntenna_tm5_internal_value);
    out += ",";
    return out;
}

int AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm5_Clear()
{
    codebookSubsetRestriction_r10_n2TxAntenna_tm5_present = false;
    return 0;
}

bool AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm5_IsPresent() const
{
    return codebookSubsetRestriction_r10_n2TxAntenna_tm5_present;
}

int AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm5_Pack(std::vector<uint8_t> &bits)
{
    if(!codebookSubsetRestriction_r10_n4TxAntenna_tm5_present)
    {
        printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm5_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 16;
    if(size < 16 || size > 16)
    {
        printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm5_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((codebookSubsetRestriction_r10_n4TxAntenna_tm5_internal_value >> (16-i-1)) & 1);
    return 0;
}

int AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm5_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return codebookSubsetRestriction_r10_n4TxAntenna_tm5_Unpack(bits, idx);
}

int AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm5_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 16;
    if(size < 16 || size > 16)
    {
        printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm5_Unpack() size failure\n");
        return -1;
    }
    codebookSubsetRestriction_r10_n4TxAntenna_tm5_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm5_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        codebookSubsetRestriction_r10_n4TxAntenna_tm5_internal_value |= (uint16_t)bits[idx++] << (uint16_t)(16-i-1);
    codebookSubsetRestriction_r10_n4TxAntenna_tm5_present = true;
    return 0;
}

uint16_t AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm5_Value() const
{
    if(codebookSubsetRestriction_r10_n4TxAntenna_tm5_present)
        return codebookSubsetRestriction_r10_n4TxAntenna_tm5_internal_value;
    uint16_t tmp = 0;
    return tmp;
}

int AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm5_SetValue(uint16_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 16)
    {
        printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm5_SetValue() size failure\n");
        return -1;
    }
    codebookSubsetRestriction_r10_n4TxAntenna_tm5_internal_value = value;
    codebookSubsetRestriction_r10_n4TxAntenna_tm5_present = true;
    return 0;
}

std::string AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm5_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "n4TxAntenna_tm5 = ";
    out += std::to_string(codebookSubsetRestriction_r10_n4TxAntenna_tm5_internal_value);
    out += "\n";
    return out;
}

std::string AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm5_ToStringNoNewLines() const
{
    std::string out = "n4TxAntenna_tm5=";
    out += std::to_string(codebookSubsetRestriction_r10_n4TxAntenna_tm5_internal_value);
    out += ",";
    return out;
}

int AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm5_Clear()
{
    codebookSubsetRestriction_r10_n4TxAntenna_tm5_present = false;
    return 0;
}

bool AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm5_IsPresent() const
{
    return codebookSubsetRestriction_r10_n4TxAntenna_tm5_present;
}

int AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm6_Pack(std::vector<uint8_t> &bits)
{
    if(!codebookSubsetRestriction_r10_n2TxAntenna_tm6_present)
    {
        printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm6_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 4;
    if(size < 4 || size > 4)
    {
        printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm6_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((codebookSubsetRestriction_r10_n2TxAntenna_tm6_internal_value >> (4-i-1)) & 1);
    return 0;
}

int AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm6_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return codebookSubsetRestriction_r10_n2TxAntenna_tm6_Unpack(bits, idx);
}

int AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm6_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 4;
    if(size < 4 || size > 4)
    {
        printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm6_Unpack() size failure\n");
        return -1;
    }
    codebookSubsetRestriction_r10_n2TxAntenna_tm6_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm6_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        codebookSubsetRestriction_r10_n2TxAntenna_tm6_internal_value |= (uint8_t)bits[idx++] << (uint8_t)(4-i-1);
    codebookSubsetRestriction_r10_n2TxAntenna_tm6_present = true;
    return 0;
}

uint8_t AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm6_Value() const
{
    if(codebookSubsetRestriction_r10_n2TxAntenna_tm6_present)
        return codebookSubsetRestriction_r10_n2TxAntenna_tm6_internal_value;
    uint8_t tmp = 0;
    return tmp;
}

int AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm6_SetValue(uint8_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 4)
    {
        printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm6_SetValue() size failure\n");
        return -1;
    }
    codebookSubsetRestriction_r10_n2TxAntenna_tm6_internal_value = value;
    codebookSubsetRestriction_r10_n2TxAntenna_tm6_present = true;
    return 0;
}

std::string AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm6_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "n2TxAntenna_tm6 = ";
    out += std::to_string(codebookSubsetRestriction_r10_n2TxAntenna_tm6_internal_value);
    out += "\n";
    return out;
}

std::string AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm6_ToStringNoNewLines() const
{
    std::string out = "n2TxAntenna_tm6=";
    out += std::to_string(codebookSubsetRestriction_r10_n2TxAntenna_tm6_internal_value);
    out += ",";
    return out;
}

int AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm6_Clear()
{
    codebookSubsetRestriction_r10_n2TxAntenna_tm6_present = false;
    return 0;
}

bool AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm6_IsPresent() const
{
    return codebookSubsetRestriction_r10_n2TxAntenna_tm6_present;
}

int AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm6_Pack(std::vector<uint8_t> &bits)
{
    if(!codebookSubsetRestriction_r10_n4TxAntenna_tm6_present)
    {
        printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm6_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 16;
    if(size < 16 || size > 16)
    {
        printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm6_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((codebookSubsetRestriction_r10_n4TxAntenna_tm6_internal_value >> (16-i-1)) & 1);
    return 0;
}

int AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm6_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return codebookSubsetRestriction_r10_n4TxAntenna_tm6_Unpack(bits, idx);
}

int AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm6_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 16;
    if(size < 16 || size > 16)
    {
        printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm6_Unpack() size failure\n");
        return -1;
    }
    codebookSubsetRestriction_r10_n4TxAntenna_tm6_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm6_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        codebookSubsetRestriction_r10_n4TxAntenna_tm6_internal_value |= (uint16_t)bits[idx++] << (uint16_t)(16-i-1);
    codebookSubsetRestriction_r10_n4TxAntenna_tm6_present = true;
    return 0;
}

uint16_t AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm6_Value() const
{
    if(codebookSubsetRestriction_r10_n4TxAntenna_tm6_present)
        return codebookSubsetRestriction_r10_n4TxAntenna_tm6_internal_value;
    uint16_t tmp = 0;
    return tmp;
}

int AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm6_SetValue(uint16_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 16)
    {
        printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm6_SetValue() size failure\n");
        return -1;
    }
    codebookSubsetRestriction_r10_n4TxAntenna_tm6_internal_value = value;
    codebookSubsetRestriction_r10_n4TxAntenna_tm6_present = true;
    return 0;
}

std::string AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm6_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "n4TxAntenna_tm6 = ";
    out += std::to_string(codebookSubsetRestriction_r10_n4TxAntenna_tm6_internal_value);
    out += "\n";
    return out;
}

std::string AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm6_ToStringNoNewLines() const
{
    std::string out = "n4TxAntenna_tm6=";
    out += std::to_string(codebookSubsetRestriction_r10_n4TxAntenna_tm6_internal_value);
    out += ",";
    return out;
}

int AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm6_Clear()
{
    codebookSubsetRestriction_r10_n4TxAntenna_tm6_present = false;
    return 0;
}

bool AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm6_IsPresent() const
{
    return codebookSubsetRestriction_r10_n4TxAntenna_tm6_present;
}

int AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm8_r9_Pack(std::vector<uint8_t> &bits)
{
    if(!codebookSubsetRestriction_r10_n2TxAntenna_tm8_r9_present)
    {
        printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm8_r9_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 6;
    if(size < 6 || size > 6)
    {
        printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm8_r9_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((codebookSubsetRestriction_r10_n2TxAntenna_tm8_r9_internal_value >> (6-i-1)) & 1);
    return 0;
}

int AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm8_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return codebookSubsetRestriction_r10_n2TxAntenna_tm8_r9_Unpack(bits, idx);
}

int AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm8_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 6;
    if(size < 6 || size > 6)
    {
        printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm8_r9_Unpack() size failure\n");
        return -1;
    }
    codebookSubsetRestriction_r10_n2TxAntenna_tm8_r9_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm8_r9_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        codebookSubsetRestriction_r10_n2TxAntenna_tm8_r9_internal_value |= (uint8_t)bits[idx++] << (uint8_t)(6-i-1);
    codebookSubsetRestriction_r10_n2TxAntenna_tm8_r9_present = true;
    return 0;
}

uint8_t AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm8_r9_Value() const
{
    if(codebookSubsetRestriction_r10_n2TxAntenna_tm8_r9_present)
        return codebookSubsetRestriction_r10_n2TxAntenna_tm8_r9_internal_value;
    uint8_t tmp = 0;
    return tmp;
}

int AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm8_r9_SetValue(uint8_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 6)
    {
        printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm8_r9_SetValue() size failure\n");
        return -1;
    }
    codebookSubsetRestriction_r10_n2TxAntenna_tm8_r9_internal_value = value;
    codebookSubsetRestriction_r10_n2TxAntenna_tm8_r9_present = true;
    return 0;
}

std::string AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm8_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "n2TxAntenna_tm8_r9 = ";
    out += std::to_string(codebookSubsetRestriction_r10_n2TxAntenna_tm8_r9_internal_value);
    out += "\n";
    return out;
}

std::string AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm8_r9_ToStringNoNewLines() const
{
    std::string out = "n2TxAntenna_tm8_r9=";
    out += std::to_string(codebookSubsetRestriction_r10_n2TxAntenna_tm8_r9_internal_value);
    out += ",";
    return out;
}

int AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm8_r9_Clear()
{
    codebookSubsetRestriction_r10_n2TxAntenna_tm8_r9_present = false;
    return 0;
}

bool AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm8_r9_IsPresent() const
{
    return codebookSubsetRestriction_r10_n2TxAntenna_tm8_r9_present;
}

int AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm8_r9_Pack(std::vector<uint8_t> &bits)
{
    if(!codebookSubsetRestriction_r10_n4TxAntenna_tm8_r9_present)
    {
        printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm8_r9_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 32;
    if(size < 32 || size > 32)
    {
        printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm8_r9_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((codebookSubsetRestriction_r10_n4TxAntenna_tm8_r9_internal_value >> (32-i-1)) & 1);
    return 0;
}

int AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm8_r9_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return codebookSubsetRestriction_r10_n4TxAntenna_tm8_r9_Unpack(bits, idx);
}

int AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm8_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 32;
    if(size < 32 || size > 32)
    {
        printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm8_r9_Unpack() size failure\n");
        return -1;
    }
    codebookSubsetRestriction_r10_n4TxAntenna_tm8_r9_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm8_r9_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        codebookSubsetRestriction_r10_n4TxAntenna_tm8_r9_internal_value |= (uint32_t)bits[idx++] << (uint32_t)(32-i-1);
    codebookSubsetRestriction_r10_n4TxAntenna_tm8_r9_present = true;
    return 0;
}

uint32_t AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm8_r9_Value() const
{
    if(codebookSubsetRestriction_r10_n4TxAntenna_tm8_r9_present)
        return codebookSubsetRestriction_r10_n4TxAntenna_tm8_r9_internal_value;
    uint32_t tmp = 0;
    return tmp;
}

int AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm8_r9_SetValue(uint32_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 32)
    {
        printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm8_r9_SetValue() size failure\n");
        return -1;
    }
    codebookSubsetRestriction_r10_n4TxAntenna_tm8_r9_internal_value = value;
    codebookSubsetRestriction_r10_n4TxAntenna_tm8_r9_present = true;
    return 0;
}

std::string AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm8_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "n4TxAntenna_tm8_r9 = ";
    out += std::to_string(codebookSubsetRestriction_r10_n4TxAntenna_tm8_r9_internal_value);
    out += "\n";
    return out;
}

std::string AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm8_r9_ToStringNoNewLines() const
{
    std::string out = "n4TxAntenna_tm8_r9=";
    out += std::to_string(codebookSubsetRestriction_r10_n4TxAntenna_tm8_r9_internal_value);
    out += ",";
    return out;
}

int AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm8_r9_Clear()
{
    codebookSubsetRestriction_r10_n4TxAntenna_tm8_r9_present = false;
    return 0;
}

bool AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm8_r9_IsPresent() const
{
    return codebookSubsetRestriction_r10_n4TxAntenna_tm8_r9_present;
}

int AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm9_r10_Pack(std::vector<uint8_t> &bits)
{
    if(!codebookSubsetRestriction_r10_n2TxAntenna_tm9_r10_present)
    {
        printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm9_r10_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 6;
    if(size < 6 || size > 6)
    {
        printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm9_r10_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((codebookSubsetRestriction_r10_n2TxAntenna_tm9_r10_internal_value >> (6-i-1)) & 1);
    return 0;
}

int AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm9_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return codebookSubsetRestriction_r10_n2TxAntenna_tm9_r10_Unpack(bits, idx);
}

int AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm9_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 6;
    if(size < 6 || size > 6)
    {
        printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm9_r10_Unpack() size failure\n");
        return -1;
    }
    codebookSubsetRestriction_r10_n2TxAntenna_tm9_r10_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm9_r10_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        codebookSubsetRestriction_r10_n2TxAntenna_tm9_r10_internal_value |= (uint8_t)bits[idx++] << (uint8_t)(6-i-1);
    codebookSubsetRestriction_r10_n2TxAntenna_tm9_r10_present = true;
    return 0;
}

uint8_t AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm9_r10_Value() const
{
    if(codebookSubsetRestriction_r10_n2TxAntenna_tm9_r10_present)
        return codebookSubsetRestriction_r10_n2TxAntenna_tm9_r10_internal_value;
    uint8_t tmp = 0;
    return tmp;
}

int AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm9_r10_SetValue(uint8_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 6)
    {
        printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm9_r10_SetValue() size failure\n");
        return -1;
    }
    codebookSubsetRestriction_r10_n2TxAntenna_tm9_r10_internal_value = value;
    codebookSubsetRestriction_r10_n2TxAntenna_tm9_r10_present = true;
    return 0;
}

std::string AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm9_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "n2TxAntenna_tm9_r10 = ";
    out += std::to_string(codebookSubsetRestriction_r10_n2TxAntenna_tm9_r10_internal_value);
    out += "\n";
    return out;
}

std::string AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm9_r10_ToStringNoNewLines() const
{
    std::string out = "n2TxAntenna_tm9_r10=";
    out += std::to_string(codebookSubsetRestriction_r10_n2TxAntenna_tm9_r10_internal_value);
    out += ",";
    return out;
}

int AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm9_r10_Clear()
{
    codebookSubsetRestriction_r10_n2TxAntenna_tm9_r10_present = false;
    return 0;
}

bool AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n2TxAntenna_tm9_r10_IsPresent() const
{
    return codebookSubsetRestriction_r10_n2TxAntenna_tm9_r10_present;
}

int AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm9_r10_Pack(std::vector<uint8_t> &bits)
{
    if(!codebookSubsetRestriction_r10_n4TxAntenna_tm9_r10_present)
    {
        printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm9_r10_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 64;
    if(size < 64 || size > 64)
    {
        printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm9_r10_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((codebookSubsetRestriction_r10_n4TxAntenna_tm9_r10_internal_value >> (64-i-1)) & 1);
    return 0;
}

int AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm9_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return codebookSubsetRestriction_r10_n4TxAntenna_tm9_r10_Unpack(bits, idx);
}

int AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm9_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 64;
    if(size < 64 || size > 64)
    {
        printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm9_r10_Unpack() size failure\n");
        return -1;
    }
    codebookSubsetRestriction_r10_n4TxAntenna_tm9_r10_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm9_r10_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        codebookSubsetRestriction_r10_n4TxAntenna_tm9_r10_internal_value |= (uint64_t)bits[idx++] << (uint64_t)(64-i-1);
    codebookSubsetRestriction_r10_n4TxAntenna_tm9_r10_present = true;
    return 0;
}

uint64_t AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm9_r10_Value() const
{
    if(codebookSubsetRestriction_r10_n4TxAntenna_tm9_r10_present)
        return codebookSubsetRestriction_r10_n4TxAntenna_tm9_r10_internal_value;
    uint64_t tmp = 0;
    return tmp;
}

int AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm9_r10_SetValue(uint64_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 64)
    {
        printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm9_r10_SetValue() size failure\n");
        return -1;
    }
    codebookSubsetRestriction_r10_n4TxAntenna_tm9_r10_internal_value = value;
    codebookSubsetRestriction_r10_n4TxAntenna_tm9_r10_present = true;
    return 0;
}

std::string AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm9_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "n4TxAntenna_tm9_r10 = ";
    out += std::to_string(codebookSubsetRestriction_r10_n4TxAntenna_tm9_r10_internal_value);
    out += "\n";
    return out;
}

std::string AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm9_r10_ToStringNoNewLines() const
{
    std::string out = "n4TxAntenna_tm9_r10=";
    out += std::to_string(codebookSubsetRestriction_r10_n4TxAntenna_tm9_r10_internal_value);
    out += ",";
    return out;
}

int AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm9_r10_Clear()
{
    codebookSubsetRestriction_r10_n4TxAntenna_tm9_r10_present = false;
    return 0;
}

bool AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n4TxAntenna_tm9_r10_IsPresent() const
{
    return codebookSubsetRestriction_r10_n4TxAntenna_tm9_r10_present;
}

int AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n8TxAntenna_tm9_r10_Pack(std::vector<uint8_t> &bits)
{
    if(!codebookSubsetRestriction_r10_n8TxAntenna_tm9_r10_present)
    {
        printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n8TxAntenna_tm9_r10_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 1;
    if(size < 1 || size > 1)
    {
        printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n8TxAntenna_tm9_r10_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((codebookSubsetRestriction_r10_n8TxAntenna_tm9_r10_internal_value >> (1-i-1)) & 1);
    return 0;
}

int AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n8TxAntenna_tm9_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return codebookSubsetRestriction_r10_n8TxAntenna_tm9_r10_Unpack(bits, idx);
}

int AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n8TxAntenna_tm9_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 1;
    if(size < 1 || size > 1)
    {
        printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n8TxAntenna_tm9_r10_Unpack() size failure\n");
        return -1;
    }
    codebookSubsetRestriction_r10_n8TxAntenna_tm9_r10_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n8TxAntenna_tm9_r10_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        codebookSubsetRestriction_r10_n8TxAntenna_tm9_r10_internal_value |= (uint8_t)bits[idx++] << (uint8_t)(1-i-1);
    codebookSubsetRestriction_r10_n8TxAntenna_tm9_r10_present = true;
    return 0;
}

uint8_t AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n8TxAntenna_tm9_r10_Value() const
{
    if(codebookSubsetRestriction_r10_n8TxAntenna_tm9_r10_present)
        return codebookSubsetRestriction_r10_n8TxAntenna_tm9_r10_internal_value;
    uint8_t tmp = 0;
    return tmp;
}

int AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n8TxAntenna_tm9_r10_SetValue(uint8_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 1)
    {
        printf("AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n8TxAntenna_tm9_r10_SetValue() size failure\n");
        return -1;
    }
    codebookSubsetRestriction_r10_n8TxAntenna_tm9_r10_internal_value = value;
    codebookSubsetRestriction_r10_n8TxAntenna_tm9_r10_present = true;
    return 0;
}

std::string AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n8TxAntenna_tm9_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "n8TxAntenna_tm9_r10 = ";
    out += std::to_string(codebookSubsetRestriction_r10_n8TxAntenna_tm9_r10_internal_value);
    out += "\n";
    return out;
}

std::string AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n8TxAntenna_tm9_r10_ToStringNoNewLines() const
{
    std::string out = "n8TxAntenna_tm9_r10=";
    out += std::to_string(codebookSubsetRestriction_r10_n8TxAntenna_tm9_r10_internal_value);
    out += ",";
    return out;
}

int AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n8TxAntenna_tm9_r10_Clear()
{
    codebookSubsetRestriction_r10_n8TxAntenna_tm9_r10_present = false;
    return 0;
}

bool AntennaInfoDedicated_r10::codebookSubsetRestriction_r10_n8TxAntenna_tm9_r10_IsPresent() const
{
    return codebookSubsetRestriction_r10_n8TxAntenna_tm9_r10_present;
}

int AntennaInfoDedicated_r10::ue_TransmitAntennaSelection_r10_Pack(std::vector<uint8_t> &bits)
{
    if(!ue_TransmitAntennaSelection_r10_present)
    {
        printf("AntennaInfoDedicated_r10::ue_TransmitAntennaSelection_r10_Pack() presence failure\n");
        return -1;
    }
    // Extension indicator

    // Choice
    for(uint32_t i=0; i<1; i++)
        bits.push_back((ue_TransmitAntennaSelection_r10_internal_choice >> (1-i-1)) & 1);

    // Fields
    if(ue_TransmitAntennaSelection_r10_internal_choice == k_ue_TransmitAntennaSelection_r10_release)
    {
        if(0 != ue_TransmitAntennaSelection_r10_release_Pack(bits))
        {
            printf("AntennaInfoDedicated_r10::ue_TransmitAntennaSelection_r10_release pack failure\n");
            return -1;
        }
    }
    if(ue_TransmitAntennaSelection_r10_internal_choice == k_ue_TransmitAntennaSelection_r10_setup)
    {
        if(0 != ue_TransmitAntennaSelection_r10_setup_Pack(bits))
        {
            printf("AntennaInfoDedicated_r10::ue_TransmitAntennaSelection_r10_setup pack failure\n");
            return -1;
        }
    }
    return 0;
}

int AntennaInfoDedicated_r10::ue_TransmitAntennaSelection_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return ue_TransmitAntennaSelection_r10_Unpack(bits, idx);
}

int AntennaInfoDedicated_r10::ue_TransmitAntennaSelection_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 1) > bits.size())
    {
        printf("AntennaInfoDedicated_r10::ue_TransmitAntennaSelection_r10_Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<1; i++)
        packed_val |= bits[idx++] << (1-i-1);

    if((AntennaInfoDedicated_r10::ue_TransmitAntennaSelection_r10_Enum)packed_val > k_ue_TransmitAntennaSelection_r10_setup)
    {
        printf("AntennaInfoDedicated_r10::ue_TransmitAntennaSelection_r10_Unpack() choice range failure\n");
        return -1;
    }
    ue_TransmitAntennaSelection_r10_internal_choice = (AntennaInfoDedicated_r10::ue_TransmitAntennaSelection_r10_Enum)packed_val;
    ue_TransmitAntennaSelection_r10_present = true;

    // Fields
    if(ue_TransmitAntennaSelection_r10_internal_choice == k_ue_TransmitAntennaSelection_r10_release)
    {
        if(0 != ue_TransmitAntennaSelection_r10_release_Unpack(bits, idx))
        {
            printf("AntennaInfoDedicated_r10::ue_TransmitAntennaSelection_r10_release unpack failure\n");
            return -1;
        }
    }
    if(ue_TransmitAntennaSelection_r10_internal_choice == k_ue_TransmitAntennaSelection_r10_setup)
    {
        if(0 != ue_TransmitAntennaSelection_r10_setup_Unpack(bits, idx))
        {
            printf("AntennaInfoDedicated_r10::ue_TransmitAntennaSelection_r10_setup unpack failure\n");
            return -1;
        }
    }
    return 0;
}

AntennaInfoDedicated_r10::ue_TransmitAntennaSelection_r10_Enum AntennaInfoDedicated_r10::ue_TransmitAntennaSelection_r10_Choice() const
{
    if(ue_TransmitAntennaSelection_r10_present)
        return ue_TransmitAntennaSelection_r10_internal_choice;
    return (AntennaInfoDedicated_r10::ue_TransmitAntennaSelection_r10_Enum)0;
}

int AntennaInfoDedicated_r10::ue_TransmitAntennaSelection_r10_SetChoice(AntennaInfoDedicated_r10::ue_TransmitAntennaSelection_r10_Enum choice)
{
    ue_TransmitAntennaSelection_r10_internal_choice = choice;
    ue_TransmitAntennaSelection_r10_present = true;
    return 0;
}

std::string AntennaInfoDedicated_r10::ue_TransmitAntennaSelection_r10_ChoiceToString(ue_TransmitAntennaSelection_r10_Enum value) const
{
    if(k_ue_TransmitAntennaSelection_r10_release == value)
        return "ue_TransmitAntennaSelection_r10_release";
    if(k_ue_TransmitAntennaSelection_r10_setup == value)
        return "ue_TransmitAntennaSelection_r10_setup";
    return "";
}

uint64_t AntennaInfoDedicated_r10::ue_TransmitAntennaSelection_r10_NumberOfChoices() const
{
    return 2;
}

std::string AntennaInfoDedicated_r10::ue_TransmitAntennaSelection_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ue_TransmitAntennaSelection_r10 = " + ue_TransmitAntennaSelection_r10_ChoiceToString(ue_TransmitAntennaSelection_r10_internal_choice) + ":\n";
    if(ue_TransmitAntennaSelection_r10_internal_choice == k_ue_TransmitAntennaSelection_r10_setup)
        out += ue_TransmitAntennaSelection_r10_setup_ToString(indent+1);
    return out;
}

std::string AntennaInfoDedicated_r10::ue_TransmitAntennaSelection_r10_ToStringNoNewLines() const
{
    std::string out = "ue_TransmitAntennaSelection_r10=" + ue_TransmitAntennaSelection_r10_ChoiceToString(ue_TransmitAntennaSelection_r10_internal_choice) + ",";
    if(ue_TransmitAntennaSelection_r10_internal_choice == k_ue_TransmitAntennaSelection_r10_setup)
        out += ue_TransmitAntennaSelection_r10_setup_ToStringNoNewLines();
    return out;
}

int AntennaInfoDedicated_r10::ue_TransmitAntennaSelection_r10_Clear()
{
    ue_TransmitAntennaSelection_r10_present = false;
    return 0;
}

bool AntennaInfoDedicated_r10::ue_TransmitAntennaSelection_r10_IsPresent() const
{
    return ue_TransmitAntennaSelection_r10_present;
}

int AntennaInfoDedicated_r10::ue_TransmitAntennaSelection_r10_setup_Pack(std::vector<uint8_t> &bits)
{
    if(!ue_TransmitAntennaSelection_r10_setup_present)
    {
        printf("AntennaInfoDedicated_r10::ue_TransmitAntennaSelection_r10_setup_Pack() presence failure\n");
        return -1;
    }
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((ue_TransmitAntennaSelection_r10_setup_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int AntennaInfoDedicated_r10::ue_TransmitAntennaSelection_r10_setup_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return ue_TransmitAntennaSelection_r10_setup_Unpack(bits, idx);
}

int AntennaInfoDedicated_r10::ue_TransmitAntennaSelection_r10_setup_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("AntennaInfoDedicated_r10::ue_TransmitAntennaSelection_r10_setup_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 1)
    {
        printf("AntennaInfoDedicated_r10::ue_TransmitAntennaSelection_r10_setup_Unpack() max failure\n");
        return -1;
    }
    ue_TransmitAntennaSelection_r10_setup_internal_value = (ue_TransmitAntennaSelection_r10_setup_Enum)packed_val;
    ue_TransmitAntennaSelection_r10_setup_present = true;
    return 0;
}

AntennaInfoDedicated_r10::ue_TransmitAntennaSelection_r10_setup_Enum AntennaInfoDedicated_r10::ue_TransmitAntennaSelection_r10_setup_Value() const
{
    if(ue_TransmitAntennaSelection_r10_setup_present)
        return ue_TransmitAntennaSelection_r10_setup_internal_value;
    return (AntennaInfoDedicated_r10::ue_TransmitAntennaSelection_r10_setup_Enum)0;
}

int AntennaInfoDedicated_r10::ue_TransmitAntennaSelection_r10_setup_SetValue(ue_TransmitAntennaSelection_r10_setup_Enum value)
{
    ue_TransmitAntennaSelection_r10_setup_internal_value = value;
    ue_TransmitAntennaSelection_r10_setup_present = true;
    return 0;
}

int AntennaInfoDedicated_r10::ue_TransmitAntennaSelection_r10_setup_SetValue(std::string value)
{
    if("closedLoop" == value)
    {
        ue_TransmitAntennaSelection_r10_setup_internal_value = k_ue_TransmitAntennaSelection_r10_setup_closedLoop;
        ue_TransmitAntennaSelection_r10_setup_present = true;
        return 0;
    }
    if("openLoop" == value)
    {
        ue_TransmitAntennaSelection_r10_setup_internal_value = k_ue_TransmitAntennaSelection_r10_setup_openLoop;
        ue_TransmitAntennaSelection_r10_setup_present = true;
        return 0;
    }
    return 1;
}

std::string AntennaInfoDedicated_r10::ue_TransmitAntennaSelection_r10_setup_ValueToString(ue_TransmitAntennaSelection_r10_setup_Enum value) const
{
    if(k_ue_TransmitAntennaSelection_r10_setup_closedLoop == value)
        return "closedLoop";
    if(k_ue_TransmitAntennaSelection_r10_setup_openLoop == value)
        return "openLoop";
    return "";
}

uint64_t AntennaInfoDedicated_r10::ue_TransmitAntennaSelection_r10_setup_NumberOfValues() const
{
    return 2;
}

std::string AntennaInfoDedicated_r10::ue_TransmitAntennaSelection_r10_setup_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "setup = " + ue_TransmitAntennaSelection_r10_setup_ValueToString(ue_TransmitAntennaSelection_r10_setup_internal_value) + "\n";
    return out;
}

std::string AntennaInfoDedicated_r10::ue_TransmitAntennaSelection_r10_setup_ToStringNoNewLines() const
{
    std::string out = "setup=" + ue_TransmitAntennaSelection_r10_setup_ValueToString(ue_TransmitAntennaSelection_r10_setup_internal_value) + ",";
    return out;
}

int AntennaInfoDedicated_r10::ue_TransmitAntennaSelection_r10_setup_Clear()
{
    ue_TransmitAntennaSelection_r10_setup_present = false;
    return 0;
}

bool AntennaInfoDedicated_r10::ue_TransmitAntennaSelection_r10_setup_IsPresent() const
{
    return ue_TransmitAntennaSelection_r10_setup_present;
}

