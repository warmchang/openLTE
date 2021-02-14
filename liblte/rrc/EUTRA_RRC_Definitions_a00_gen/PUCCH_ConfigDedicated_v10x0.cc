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

#include "PUCCH_ConfigDedicated_v10x0.h"

#include <cmath>

int PUCCH_ConfigDedicated_v10x0::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(n3PUCCH_AN_List_r10_IsPresent());
    bits.push_back(n1PUCCH_AN_CS_List_r10_IsPresent());
    bits.push_back(pucch_Format_r10_IsPresent());
    bits.push_back(simultaneousPUCCH_PUSCH_r10_IsPresent());
    bits.push_back(twoAntennaPortActivated_r10_IsPresent());
    bits.push_back(n1PUCCH_AN_RepP1_r10_IsPresent());

    // Fields
    if(n3PUCCH_AN_List_r10_IsPresent())
    {
        if(0 != n3PUCCH_AN_List_r10_Pack(bits))
        {
            printf("PUCCH_ConfigDedicated_v10x0:: field pack failure\n");
            return -1;
        }
    }
    if(n1PUCCH_AN_CS_List_r10_IsPresent())
    {
        if(0 != n1PUCCH_AN_CS_List_r10_Pack(bits))
        {
            printf("PUCCH_ConfigDedicated_v10x0:: field pack failure\n");
            return -1;
        }
    }
    if(pucch_Format_r10_IsPresent())
    {
        if(0 != pucch_Format_r10_Pack(bits))
        {
            printf("PUCCH_ConfigDedicated_v10x0:: field pack failure\n");
            return -1;
        }
    }
    if(simultaneousPUCCH_PUSCH_r10_IsPresent())
    {
        if(0 != simultaneousPUCCH_PUSCH_r10_Pack(bits))
        {
            printf("PUCCH_ConfigDedicated_v10x0:: field pack failure\n");
            return -1;
        }
    }
    if(twoAntennaPortActivated_r10_IsPresent())
    {
        if(0 != twoAntennaPortActivated_r10_Pack(bits))
        {
            printf("PUCCH_ConfigDedicated_v10x0:: field pack failure\n");
            return -1;
        }
    }
    if(n1PUCCH_AN_RepP1_r10_IsPresent())
    {
        if(0 != n1PUCCH_AN_RepP1_r10_Pack(bits))
        {
            printf("PUCCH_ConfigDedicated_v10x0:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int PUCCH_ConfigDedicated_v10x0::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int PUCCH_ConfigDedicated_v10x0::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("PUCCH_ConfigDedicated_v10x0::Unpack() index out of bounds for optional indiator n3PUCCH_AN_List_r10\n");
        return -1;
    }
    n3PUCCH_AN_List_r10_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("PUCCH_ConfigDedicated_v10x0::Unpack() index out of bounds for optional indiator n1PUCCH_AN_CS_List_r10\n");
        return -1;
    }
    n1PUCCH_AN_CS_List_r10_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("PUCCH_ConfigDedicated_v10x0::Unpack() index out of bounds for optional indiator pucch_Format_r10\n");
        return -1;
    }
    pucch_Format_r10_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("PUCCH_ConfigDedicated_v10x0::Unpack() index out of bounds for optional indiator simultaneousPUCCH_PUSCH_r10\n");
        return -1;
    }
    simultaneousPUCCH_PUSCH_r10_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("PUCCH_ConfigDedicated_v10x0::Unpack() index out of bounds for optional indiator twoAntennaPortActivated_r10\n");
        return -1;
    }
    twoAntennaPortActivated_r10_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("PUCCH_ConfigDedicated_v10x0::Unpack() index out of bounds for optional indiator n1PUCCH_AN_RepP1_r10\n");
        return -1;
    }
    n1PUCCH_AN_RepP1_r10_present = bits[idx++];

    // Fields
    if(n3PUCCH_AN_List_r10_present)
    {
        if(0 != n3PUCCH_AN_List_r10_Unpack(bits, idx))
        {
            printf("PUCCH_ConfigDedicated_v10x0:: field unpack failure\n");
            return -1;
        }
    }
    if(n1PUCCH_AN_CS_List_r10_present)
    {
        if(0 != n1PUCCH_AN_CS_List_r10_Unpack(bits, idx))
        {
            printf("PUCCH_ConfigDedicated_v10x0:: field unpack failure\n");
            return -1;
        }
    }
    if(pucch_Format_r10_present)
    {
        if(0 != pucch_Format_r10_Unpack(bits, idx))
        {
            printf("PUCCH_ConfigDedicated_v10x0:: field unpack failure\n");
            return -1;
        }
    }
    if(simultaneousPUCCH_PUSCH_r10_present)
    {
        if(0 != simultaneousPUCCH_PUSCH_r10_Unpack(bits, idx))
        {
            printf("PUCCH_ConfigDedicated_v10x0:: field unpack failure\n");
            return -1;
        }
    }
    if(twoAntennaPortActivated_r10_present)
    {
        if(0 != twoAntennaPortActivated_r10_Unpack(bits, idx))
        {
            printf("PUCCH_ConfigDedicated_v10x0:: field unpack failure\n");
            return -1;
        }
    }
    if(n1PUCCH_AN_RepP1_r10_present)
    {
        if(0 != n1PUCCH_AN_RepP1_r10_Unpack(bits, idx))
        {
            printf("PUCCH_ConfigDedicated_v10x0:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string PUCCH_ConfigDedicated_v10x0::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "PUCCH_ConfigDedicated_v10x0:\n";
    if(n3PUCCH_AN_List_r10_IsPresent())
        out += n3PUCCH_AN_List_r10_ToString(indent+1);
    if(n1PUCCH_AN_CS_List_r10_IsPresent())
        out += n1PUCCH_AN_CS_List_r10_ToString(indent+1);
    if(pucch_Format_r10_IsPresent())
        out += pucch_Format_r10_ToString(indent+1);
    if(simultaneousPUCCH_PUSCH_r10_IsPresent())
        out += simultaneousPUCCH_PUSCH_r10_ToString(indent+1);
    if(twoAntennaPortActivated_r10_IsPresent())
        out += twoAntennaPortActivated_r10_ToString(indent+1);
    if(n1PUCCH_AN_RepP1_r10_IsPresent())
        out += n1PUCCH_AN_RepP1_r10_ToString(indent+1);
    return out;
}

std::string PUCCH_ConfigDedicated_v10x0::ToStringNoNewLines() const
{
    std::string out = "PUCCH_ConfigDedicated_v10x0:";
    if(n3PUCCH_AN_List_r10_IsPresent())
        out += n3PUCCH_AN_List_r10_ToStringNoNewLines();
    if(n1PUCCH_AN_CS_List_r10_IsPresent())
        out += n1PUCCH_AN_CS_List_r10_ToStringNoNewLines();
    if(pucch_Format_r10_IsPresent())
        out += pucch_Format_r10_ToStringNoNewLines();
    if(simultaneousPUCCH_PUSCH_r10_IsPresent())
        out += simultaneousPUCCH_PUSCH_r10_ToStringNoNewLines();
    if(twoAntennaPortActivated_r10_IsPresent())
        out += twoAntennaPortActivated_r10_ToStringNoNewLines();
    if(n1PUCCH_AN_RepP1_r10_IsPresent())
        out += n1PUCCH_AN_RepP1_r10_ToStringNoNewLines();
    return out;
}

int PUCCH_ConfigDedicated_v10x0::n3PUCCH_AN_List_r10_items::n3PUCCH_AN_List_r10_itemsPack(std::vector<uint8_t> &bits)
{
    int64_t val_to_pack = n3PUCCH_AN_List_r10_itemsinternal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (0 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int PUCCH_ConfigDedicated_v10x0::n3PUCCH_AN_List_r10_items::n3PUCCH_AN_List_r10_itemsUnpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return n3PUCCH_AN_List_r10_itemsUnpack(bits, idx);
}

int PUCCH_ConfigDedicated_v10x0::n3PUCCH_AN_List_r10_items::n3PUCCH_AN_List_r10_itemsUnpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (0 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("PUCCH_ConfigDedicated_v10x0::n3PUCCH_AN_List_r10_items::n3PUCCH_AN_List_r10_itemsUnpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    n3PUCCH_AN_List_r10_itemsinternal_value = packed_val + 0;
    n3PUCCH_AN_List_r10_itemspresent = true;
    return 0;
}

int64_t PUCCH_ConfigDedicated_v10x0::n3PUCCH_AN_List_r10_items::n3PUCCH_AN_List_r10_itemsValue() const
{
    if(n3PUCCH_AN_List_r10_itemspresent)
        return n3PUCCH_AN_List_r10_itemsinternal_value;
    int64_t tmp = 0;
    return tmp;
}

int PUCCH_ConfigDedicated_v10x0::n3PUCCH_AN_List_r10_items::n3PUCCH_AN_List_r10_itemsSetValue(int64_t value)
{
    if(value < 0 || value > 0)
    {
        printf("PUCCH_ConfigDedicated_v10x0::n3PUCCH_AN_List_r10_items::n3PUCCH_AN_List_r10_itemsSetValue() range failure\n");
        return -1;
    }
    n3PUCCH_AN_List_r10_itemsinternal_value = value;
    n3PUCCH_AN_List_r10_itemspresent = true;
    return 0;
}

std::string PUCCH_ConfigDedicated_v10x0::n3PUCCH_AN_List_r10_items::n3PUCCH_AN_List_r10_itemsToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += " = " + std::to_string(n3PUCCH_AN_List_r10_itemsinternal_value) + "\n";
    return out;
}

std::string PUCCH_ConfigDedicated_v10x0::n3PUCCH_AN_List_r10_items::n3PUCCH_AN_List_r10_itemsToStringNoNewLines() const
{
    std::string out = "=" + std::to_string(n3PUCCH_AN_List_r10_itemsinternal_value) + ",";
    return out;
}

int PUCCH_ConfigDedicated_v10x0::n3PUCCH_AN_List_r10_items::n3PUCCH_AN_List_r10_itemsClear()
{
    n3PUCCH_AN_List_r10_itemspresent = false;
    return 0;
}

bool PUCCH_ConfigDedicated_v10x0::n3PUCCH_AN_List_r10_items::n3PUCCH_AN_List_r10_itemsIsPresent() const
{
    return n3PUCCH_AN_List_r10_itemspresent;
}

#include "maxFFS.h"

int PUCCH_ConfigDedicated_v10x0::n3PUCCH_AN_List_r10_Pack(std::vector<uint8_t> &bits)
{
    uint32_t N_size_bits = 1;
    while(pow(2, N_size_bits) <= (maxFFS - 1))
        N_size_bits++;
    uint32_t local_size = n3PUCCH_AN_List_r10_internal_value.size() - 1;
    for(uint32_t i=0; i<N_size_bits; i++)
        bits.push_back((local_size >> (N_size_bits-i-1)) & 1);
    for(auto item : n3PUCCH_AN_List_r10_internal_value)
        if(0 != item.n3PUCCH_AN_List_r10_itemsPack(bits))
        {
            printf("PUCCH_ConfigDedicated_v10x0::n3PUCCH_AN_List_r10_Pack() item_pack_failure\n");
            return -1;
        }
    return 0;
}

int PUCCH_ConfigDedicated_v10x0::n3PUCCH_AN_List_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return n3PUCCH_AN_List_r10_Unpack(bits, idx);
}

int PUCCH_ConfigDedicated_v10x0::n3PUCCH_AN_List_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_size_bits = 1;
    while(pow(2, N_size_bits) <= (maxFFS - 1))
        N_size_bits++;
    uint32_t size = 0;
    for(uint32_t i=0; i<N_size_bits; i++)
        size |= bits[idx++] << (N_size_bits-i-1);
    size += 1;
    n3PUCCH_AN_List_r10_internal_value.clear();
    for(uint32_t i=0; i<size; i++)
    {
        n3PUCCH_AN_List_r10_items tmp;
        if(0 != tmp.n3PUCCH_AN_List_r10_itemsUnpack(bits, idx))
        {
            printf("PUCCH_ConfigDedicated_v10x0::n3PUCCH_AN_List_r10_Unpack() item unpack failure\n");
            return -1;
        }
        n3PUCCH_AN_List_r10_internal_value.push_back(tmp);
    }
    n3PUCCH_AN_List_r10_present = true;
    return 0;
}

std::vector<PUCCH_ConfigDedicated_v10x0::n3PUCCH_AN_List_r10_items> PUCCH_ConfigDedicated_v10x0::n3PUCCH_AN_List_r10_Value() const
{
    if(n3PUCCH_AN_List_r10_present)
        return n3PUCCH_AN_List_r10_internal_value;
    return {};
}

int PUCCH_ConfigDedicated_v10x0::n3PUCCH_AN_List_r10_SetValue(std::vector<PUCCH_ConfigDedicated_v10x0::n3PUCCH_AN_List_r10_items> value)
{
    if(value.size() < 1 || value.size() > maxFFS)
    {
        printf("PUCCH_ConfigDedicated_v10x0::n3PUCCH_AN_List_r10_SetValue() list size failure\n");
        return -1;
    }
    n3PUCCH_AN_List_r10_internal_value = value;
    n3PUCCH_AN_List_r10_present = true;
    return 0;
}

int PUCCH_ConfigDedicated_v10x0::n3PUCCH_AN_List_r10_Clear()
{
    n3PUCCH_AN_List_r10_present = false;
    n3PUCCH_AN_List_r10_internal_value.clear();
    return 0;
}

bool PUCCH_ConfigDedicated_v10x0::n3PUCCH_AN_List_r10_IsPresent() const
{
    return n3PUCCH_AN_List_r10_present;
}

std::string PUCCH_ConfigDedicated_v10x0::n3PUCCH_AN_List_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "n3PUCCH_AN_List_r10:\n";
    for(auto item : n3PUCCH_AN_List_r10_internal_value)
        out += item.n3PUCCH_AN_List_r10_itemsToString(indent+1);
    return out;
}

std::string PUCCH_ConfigDedicated_v10x0::n3PUCCH_AN_List_r10_ToStringNoNewLines() const
{
    std::string out = "n3PUCCH_AN_List_r10:";
    for(auto item : n3PUCCH_AN_List_r10_internal_value)
        out += item.n3PUCCH_AN_List_r10_itemsToStringNoNewLines();
    return out;
}

int PUCCH_ConfigDedicated_v10x0::n1PUCCH_AN_CS_List_r10_items::n1PUCCH_AN_CS_List_r10_itemsPack(std::vector<uint8_t> &bits)
{
    int64_t val_to_pack = n1PUCCH_AN_CS_List_r10_itemsinternal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (0 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int PUCCH_ConfigDedicated_v10x0::n1PUCCH_AN_CS_List_r10_items::n1PUCCH_AN_CS_List_r10_itemsUnpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return n1PUCCH_AN_CS_List_r10_itemsUnpack(bits, idx);
}

int PUCCH_ConfigDedicated_v10x0::n1PUCCH_AN_CS_List_r10_items::n1PUCCH_AN_CS_List_r10_itemsUnpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (0 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("PUCCH_ConfigDedicated_v10x0::n1PUCCH_AN_CS_List_r10_items::n1PUCCH_AN_CS_List_r10_itemsUnpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    n1PUCCH_AN_CS_List_r10_itemsinternal_value = packed_val + 0;
    n1PUCCH_AN_CS_List_r10_itemspresent = true;
    return 0;
}

int64_t PUCCH_ConfigDedicated_v10x0::n1PUCCH_AN_CS_List_r10_items::n1PUCCH_AN_CS_List_r10_itemsValue() const
{
    if(n1PUCCH_AN_CS_List_r10_itemspresent)
        return n1PUCCH_AN_CS_List_r10_itemsinternal_value;
    int64_t tmp = 0;
    return tmp;
}

int PUCCH_ConfigDedicated_v10x0::n1PUCCH_AN_CS_List_r10_items::n1PUCCH_AN_CS_List_r10_itemsSetValue(int64_t value)
{
    if(value < 0 || value > 0)
    {
        printf("PUCCH_ConfigDedicated_v10x0::n1PUCCH_AN_CS_List_r10_items::n1PUCCH_AN_CS_List_r10_itemsSetValue() range failure\n");
        return -1;
    }
    n1PUCCH_AN_CS_List_r10_itemsinternal_value = value;
    n1PUCCH_AN_CS_List_r10_itemspresent = true;
    return 0;
}

std::string PUCCH_ConfigDedicated_v10x0::n1PUCCH_AN_CS_List_r10_items::n1PUCCH_AN_CS_List_r10_itemsToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += " = " + std::to_string(n1PUCCH_AN_CS_List_r10_itemsinternal_value) + "\n";
    return out;
}

std::string PUCCH_ConfigDedicated_v10x0::n1PUCCH_AN_CS_List_r10_items::n1PUCCH_AN_CS_List_r10_itemsToStringNoNewLines() const
{
    std::string out = "=" + std::to_string(n1PUCCH_AN_CS_List_r10_itemsinternal_value) + ",";
    return out;
}

int PUCCH_ConfigDedicated_v10x0::n1PUCCH_AN_CS_List_r10_items::n1PUCCH_AN_CS_List_r10_itemsClear()
{
    n1PUCCH_AN_CS_List_r10_itemspresent = false;
    return 0;
}

bool PUCCH_ConfigDedicated_v10x0::n1PUCCH_AN_CS_List_r10_items::n1PUCCH_AN_CS_List_r10_itemsIsPresent() const
{
    return n1PUCCH_AN_CS_List_r10_itemspresent;
}

#include "maxFFS.h"

int PUCCH_ConfigDedicated_v10x0::n1PUCCH_AN_CS_List_r10_Pack(std::vector<uint8_t> &bits)
{
    uint32_t N_size_bits = 1;
    while(pow(2, N_size_bits) <= (maxFFS - 1))
        N_size_bits++;
    uint32_t local_size = n1PUCCH_AN_CS_List_r10_internal_value.size() - 1;
    for(uint32_t i=0; i<N_size_bits; i++)
        bits.push_back((local_size >> (N_size_bits-i-1)) & 1);
    for(auto item : n1PUCCH_AN_CS_List_r10_internal_value)
        if(0 != item.n1PUCCH_AN_CS_List_r10_itemsPack(bits))
        {
            printf("PUCCH_ConfigDedicated_v10x0::n1PUCCH_AN_CS_List_r10_Pack() item_pack_failure\n");
            return -1;
        }
    return 0;
}

int PUCCH_ConfigDedicated_v10x0::n1PUCCH_AN_CS_List_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return n1PUCCH_AN_CS_List_r10_Unpack(bits, idx);
}

int PUCCH_ConfigDedicated_v10x0::n1PUCCH_AN_CS_List_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_size_bits = 1;
    while(pow(2, N_size_bits) <= (maxFFS - 1))
        N_size_bits++;
    uint32_t size = 0;
    for(uint32_t i=0; i<N_size_bits; i++)
        size |= bits[idx++] << (N_size_bits-i-1);
    size += 1;
    n1PUCCH_AN_CS_List_r10_internal_value.clear();
    for(uint32_t i=0; i<size; i++)
    {
        n1PUCCH_AN_CS_List_r10_items tmp;
        if(0 != tmp.n1PUCCH_AN_CS_List_r10_itemsUnpack(bits, idx))
        {
            printf("PUCCH_ConfigDedicated_v10x0::n1PUCCH_AN_CS_List_r10_Unpack() item unpack failure\n");
            return -1;
        }
        n1PUCCH_AN_CS_List_r10_internal_value.push_back(tmp);
    }
    n1PUCCH_AN_CS_List_r10_present = true;
    return 0;
}

std::vector<PUCCH_ConfigDedicated_v10x0::n1PUCCH_AN_CS_List_r10_items> PUCCH_ConfigDedicated_v10x0::n1PUCCH_AN_CS_List_r10_Value() const
{
    if(n1PUCCH_AN_CS_List_r10_present)
        return n1PUCCH_AN_CS_List_r10_internal_value;
    return {};
}

int PUCCH_ConfigDedicated_v10x0::n1PUCCH_AN_CS_List_r10_SetValue(std::vector<PUCCH_ConfigDedicated_v10x0::n1PUCCH_AN_CS_List_r10_items> value)
{
    if(value.size() < 1 || value.size() > maxFFS)
    {
        printf("PUCCH_ConfigDedicated_v10x0::n1PUCCH_AN_CS_List_r10_SetValue() list size failure\n");
        return -1;
    }
    n1PUCCH_AN_CS_List_r10_internal_value = value;
    n1PUCCH_AN_CS_List_r10_present = true;
    return 0;
}

int PUCCH_ConfigDedicated_v10x0::n1PUCCH_AN_CS_List_r10_Clear()
{
    n1PUCCH_AN_CS_List_r10_present = false;
    n1PUCCH_AN_CS_List_r10_internal_value.clear();
    return 0;
}

bool PUCCH_ConfigDedicated_v10x0::n1PUCCH_AN_CS_List_r10_IsPresent() const
{
    return n1PUCCH_AN_CS_List_r10_present;
}

std::string PUCCH_ConfigDedicated_v10x0::n1PUCCH_AN_CS_List_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "n1PUCCH_AN_CS_List_r10:\n";
    for(auto item : n1PUCCH_AN_CS_List_r10_internal_value)
        out += item.n1PUCCH_AN_CS_List_r10_itemsToString(indent+1);
    return out;
}

std::string PUCCH_ConfigDedicated_v10x0::n1PUCCH_AN_CS_List_r10_ToStringNoNewLines() const
{
    std::string out = "n1PUCCH_AN_CS_List_r10:";
    for(auto item : n1PUCCH_AN_CS_List_r10_internal_value)
        out += item.n1PUCCH_AN_CS_List_r10_itemsToStringNoNewLines();
    return out;
}

int PUCCH_ConfigDedicated_v10x0::pucch_Format_r10_Pack(std::vector<uint8_t> &bits)
{
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((pucch_Format_r10_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int PUCCH_ConfigDedicated_v10x0::pucch_Format_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return pucch_Format_r10_Unpack(bits, idx);
}

int PUCCH_ConfigDedicated_v10x0::pucch_Format_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("PUCCH_ConfigDedicated_v10x0::pucch_Format_r10_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 1)
    {
        printf("PUCCH_ConfigDedicated_v10x0::pucch_Format_r10_Unpack() max failure\n");
        return -1;
    }
    pucch_Format_r10_internal_value = (pucch_Format_r10_Enum)packed_val;
    pucch_Format_r10_present = true;
    return 0;
}

PUCCH_ConfigDedicated_v10x0::pucch_Format_r10_Enum PUCCH_ConfigDedicated_v10x0::pucch_Format_r10_Value() const
{
    if(pucch_Format_r10_present)
        return pucch_Format_r10_internal_value;
    return (PUCCH_ConfigDedicated_v10x0::pucch_Format_r10_Enum)0;
}

int PUCCH_ConfigDedicated_v10x0::pucch_Format_r10_SetValue(pucch_Format_r10_Enum value)
{
    pucch_Format_r10_internal_value = value;
    pucch_Format_r10_present = true;
    return 0;
}

int PUCCH_ConfigDedicated_v10x0::pucch_Format_r10_SetValue(std::string value)
{
    if("format3" == value)
    {
        pucch_Format_r10_internal_value = k_pucch_Format_r10_format3;
        pucch_Format_r10_present = true;
        return 0;
    }
    if("channelSelection" == value)
    {
        pucch_Format_r10_internal_value = k_pucch_Format_r10_channelSelection;
        pucch_Format_r10_present = true;
        return 0;
    }
    return 1;
}

std::string PUCCH_ConfigDedicated_v10x0::pucch_Format_r10_ValueToString(pucch_Format_r10_Enum value) const
{
    if(k_pucch_Format_r10_format3 == value)
        return "format3";
    if(k_pucch_Format_r10_channelSelection == value)
        return "channelSelection";
    return "";
}

uint64_t PUCCH_ConfigDedicated_v10x0::pucch_Format_r10_NumberOfValues() const
{
    return 2;
}

std::string PUCCH_ConfigDedicated_v10x0::pucch_Format_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "pucch_Format_r10 = " + pucch_Format_r10_ValueToString(pucch_Format_r10_internal_value) + "\n";
    return out;
}

std::string PUCCH_ConfigDedicated_v10x0::pucch_Format_r10_ToStringNoNewLines() const
{
    std::string out = "pucch_Format_r10=" + pucch_Format_r10_ValueToString(pucch_Format_r10_internal_value) + ",";
    return out;
}

int PUCCH_ConfigDedicated_v10x0::pucch_Format_r10_Clear()
{
    pucch_Format_r10_present = false;
    return 0;
}

bool PUCCH_ConfigDedicated_v10x0::pucch_Format_r10_IsPresent() const
{
    return pucch_Format_r10_present;
}

int PUCCH_ConfigDedicated_v10x0::simultaneousPUCCH_PUSCH_r10_Pack(std::vector<uint8_t> &bits)
{
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((simultaneousPUCCH_PUSCH_r10_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int PUCCH_ConfigDedicated_v10x0::simultaneousPUCCH_PUSCH_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return simultaneousPUCCH_PUSCH_r10_Unpack(bits, idx);
}

int PUCCH_ConfigDedicated_v10x0::simultaneousPUCCH_PUSCH_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("PUCCH_ConfigDedicated_v10x0::simultaneousPUCCH_PUSCH_r10_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 0)
    {
        printf("PUCCH_ConfigDedicated_v10x0::simultaneousPUCCH_PUSCH_r10_Unpack() max failure\n");
        return -1;
    }
    simultaneousPUCCH_PUSCH_r10_internal_value = (simultaneousPUCCH_PUSCH_r10_Enum)packed_val;
    simultaneousPUCCH_PUSCH_r10_present = true;
    return 0;
}

PUCCH_ConfigDedicated_v10x0::simultaneousPUCCH_PUSCH_r10_Enum PUCCH_ConfigDedicated_v10x0::simultaneousPUCCH_PUSCH_r10_Value() const
{
    if(simultaneousPUCCH_PUSCH_r10_present)
        return simultaneousPUCCH_PUSCH_r10_internal_value;
    return (PUCCH_ConfigDedicated_v10x0::simultaneousPUCCH_PUSCH_r10_Enum)0;
}

int PUCCH_ConfigDedicated_v10x0::simultaneousPUCCH_PUSCH_r10_SetValue(simultaneousPUCCH_PUSCH_r10_Enum value)
{
    simultaneousPUCCH_PUSCH_r10_internal_value = value;
    simultaneousPUCCH_PUSCH_r10_present = true;
    return 0;
}

int PUCCH_ConfigDedicated_v10x0::simultaneousPUCCH_PUSCH_r10_SetValue(std::string value)
{
    if("true" == value)
    {
        simultaneousPUCCH_PUSCH_r10_internal_value = k_simultaneousPUCCH_PUSCH_r10_true;
        simultaneousPUCCH_PUSCH_r10_present = true;
        return 0;
    }
    return 1;
}

std::string PUCCH_ConfigDedicated_v10x0::simultaneousPUCCH_PUSCH_r10_ValueToString(simultaneousPUCCH_PUSCH_r10_Enum value) const
{
    if(k_simultaneousPUCCH_PUSCH_r10_true == value)
        return "true";
    return "";
}

uint64_t PUCCH_ConfigDedicated_v10x0::simultaneousPUCCH_PUSCH_r10_NumberOfValues() const
{
    return 1;
}

std::string PUCCH_ConfigDedicated_v10x0::simultaneousPUCCH_PUSCH_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "simultaneousPUCCH_PUSCH_r10 = " + simultaneousPUCCH_PUSCH_r10_ValueToString(simultaneousPUCCH_PUSCH_r10_internal_value) + "\n";
    return out;
}

std::string PUCCH_ConfigDedicated_v10x0::simultaneousPUCCH_PUSCH_r10_ToStringNoNewLines() const
{
    std::string out = "simultaneousPUCCH_PUSCH_r10=" + simultaneousPUCCH_PUSCH_r10_ValueToString(simultaneousPUCCH_PUSCH_r10_internal_value) + ",";
    return out;
}

int PUCCH_ConfigDedicated_v10x0::simultaneousPUCCH_PUSCH_r10_Clear()
{
    simultaneousPUCCH_PUSCH_r10_present = false;
    return 0;
}

bool PUCCH_ConfigDedicated_v10x0::simultaneousPUCCH_PUSCH_r10_IsPresent() const
{
    return simultaneousPUCCH_PUSCH_r10_present;
}

int PUCCH_ConfigDedicated_v10x0::twoAntennaPortActivated_r10_Pack(std::vector<uint8_t> &bits)
{
    uint32_t N_bits = 1;
    for(uint32_t i=0; i<N_bits; i++)
    {
        bits.push_back((twoAntennaPortActivated_r10_internal_value >> (N_bits-1-i)) & 1);
    }
    return 0;
}

int PUCCH_ConfigDedicated_v10x0::twoAntennaPortActivated_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return twoAntennaPortActivated_r10_Unpack(bits, idx);
}

int PUCCH_ConfigDedicated_v10x0::twoAntennaPortActivated_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t packed_val = 0;
    uint32_t N_bits = 1;
    if((idx + N_bits) > bits.size())
    {
        printf("PUCCH_ConfigDedicated_v10x0::twoAntennaPortActivated_r10_Unpack() index out of bounds for value\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    if(packed_val > 0)
    {
        printf("PUCCH_ConfigDedicated_v10x0::twoAntennaPortActivated_r10_Unpack() max failure\n");
        return -1;
    }
    twoAntennaPortActivated_r10_internal_value = (twoAntennaPortActivated_r10_Enum)packed_val;
    twoAntennaPortActivated_r10_present = true;
    return 0;
}

PUCCH_ConfigDedicated_v10x0::twoAntennaPortActivated_r10_Enum PUCCH_ConfigDedicated_v10x0::twoAntennaPortActivated_r10_Value() const
{
    if(twoAntennaPortActivated_r10_present)
        return twoAntennaPortActivated_r10_internal_value;
    return (PUCCH_ConfigDedicated_v10x0::twoAntennaPortActivated_r10_Enum)0;
}

int PUCCH_ConfigDedicated_v10x0::twoAntennaPortActivated_r10_SetValue(twoAntennaPortActivated_r10_Enum value)
{
    twoAntennaPortActivated_r10_internal_value = value;
    twoAntennaPortActivated_r10_present = true;
    return 0;
}

int PUCCH_ConfigDedicated_v10x0::twoAntennaPortActivated_r10_SetValue(std::string value)
{
    if("true" == value)
    {
        twoAntennaPortActivated_r10_internal_value = k_twoAntennaPortActivated_r10_true;
        twoAntennaPortActivated_r10_present = true;
        return 0;
    }
    return 1;
}

std::string PUCCH_ConfigDedicated_v10x0::twoAntennaPortActivated_r10_ValueToString(twoAntennaPortActivated_r10_Enum value) const
{
    if(k_twoAntennaPortActivated_r10_true == value)
        return "true";
    return "";
}

uint64_t PUCCH_ConfigDedicated_v10x0::twoAntennaPortActivated_r10_NumberOfValues() const
{
    return 1;
}

std::string PUCCH_ConfigDedicated_v10x0::twoAntennaPortActivated_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "twoAntennaPortActivated_r10 = " + twoAntennaPortActivated_r10_ValueToString(twoAntennaPortActivated_r10_internal_value) + "\n";
    return out;
}

std::string PUCCH_ConfigDedicated_v10x0::twoAntennaPortActivated_r10_ToStringNoNewLines() const
{
    std::string out = "twoAntennaPortActivated_r10=" + twoAntennaPortActivated_r10_ValueToString(twoAntennaPortActivated_r10_internal_value) + ",";
    return out;
}

int PUCCH_ConfigDedicated_v10x0::twoAntennaPortActivated_r10_Clear()
{
    twoAntennaPortActivated_r10_present = false;
    return 0;
}

bool PUCCH_ConfigDedicated_v10x0::twoAntennaPortActivated_r10_IsPresent() const
{
    return twoAntennaPortActivated_r10_present;
}

int PUCCH_ConfigDedicated_v10x0::n1PUCCH_AN_RepP1_r10_Pack(std::vector<uint8_t> &bits)
{
    int64_t val_to_pack = n1PUCCH_AN_RepP1_r10_internal_value - (0);
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (2047 - 0))
        N_bits++;
    for(uint32_t i=0; i<N_bits; i++)
        bits.push_back((val_to_pack >> (N_bits-i-1)) & 1);
    return 0;
}

int PUCCH_ConfigDedicated_v10x0::n1PUCCH_AN_RepP1_r10_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return n1PUCCH_AN_RepP1_r10_Unpack(bits, idx);
}

int PUCCH_ConfigDedicated_v10x0::n1PUCCH_AN_RepP1_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t N_bits = 1;
    while(pow(2, N_bits) <= (2047 - 0))
        N_bits++;
    int64_t packed_val = 0;
    if((idx + N_bits) > bits.size())
    {
        printf("PUCCH_ConfigDedicated_v10x0::n1PUCCH_AN_RepP1_r10_Unpack() index out of bound\n");
        return -1;
    }
    for(uint32_t i=0; i<N_bits; i++)
        packed_val |= bits[idx++] << (N_bits-i-1);
    n1PUCCH_AN_RepP1_r10_internal_value = packed_val + 0;
    n1PUCCH_AN_RepP1_r10_present = true;
    return 0;
}

int64_t PUCCH_ConfigDedicated_v10x0::n1PUCCH_AN_RepP1_r10_Value() const
{
    if(n1PUCCH_AN_RepP1_r10_present)
        return n1PUCCH_AN_RepP1_r10_internal_value;
    int64_t tmp = 0;
    return tmp;
}

int PUCCH_ConfigDedicated_v10x0::n1PUCCH_AN_RepP1_r10_SetValue(int64_t value)
{
    if(value < 0 || value > 2047)
    {
        printf("PUCCH_ConfigDedicated_v10x0::n1PUCCH_AN_RepP1_r10_SetValue() range failure\n");
        return -1;
    }
    n1PUCCH_AN_RepP1_r10_internal_value = value;
    n1PUCCH_AN_RepP1_r10_present = true;
    return 0;
}

std::string PUCCH_ConfigDedicated_v10x0::n1PUCCH_AN_RepP1_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "n1PUCCH_AN_RepP1_r10 = " + std::to_string(n1PUCCH_AN_RepP1_r10_internal_value) + "\n";
    return out;
}

std::string PUCCH_ConfigDedicated_v10x0::n1PUCCH_AN_RepP1_r10_ToStringNoNewLines() const
{
    std::string out = "n1PUCCH_AN_RepP1_r10=" + std::to_string(n1PUCCH_AN_RepP1_r10_internal_value) + ",";
    return out;
}

int PUCCH_ConfigDedicated_v10x0::n1PUCCH_AN_RepP1_r10_Clear()
{
    n1PUCCH_AN_RepP1_r10_present = false;
    return 0;
}

bool PUCCH_ConfigDedicated_v10x0::n1PUCCH_AN_RepP1_r10_IsPresent() const
{
    return n1PUCCH_AN_RepP1_r10_present;
}

