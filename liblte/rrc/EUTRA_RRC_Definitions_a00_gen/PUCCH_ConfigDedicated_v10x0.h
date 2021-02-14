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

#ifndef __PUCCH_ConfigDedicated_v10x0_H__
#define __PUCCH_ConfigDedicated_v10x0_H__

#include <array>
#include <cstdint>
#include <vector>

class PUCCH_ConfigDedicated_v10x0
{
public:
    PUCCH_ConfigDedicated_v10x0() : n3PUCCH_AN_List_r10_present{false}, n1PUCCH_AN_CS_List_r10_present{false}, pucch_Format_r10_present{false}, simultaneousPUCCH_PUSCH_r10_present{false}, twoAntennaPortActivated_r10_present{false}, n1PUCCH_AN_RepP1_r10_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // n3PUCCH-AN-List-r10
public:
    class n3PUCCH_AN_List_r10_items
    {
    public:
        int n3PUCCH_AN_List_r10_itemsPack(std::vector<uint8_t> &bits);
        int n3PUCCH_AN_List_r10_itemsUnpack(std::vector<uint8_t> bits);
        int n3PUCCH_AN_List_r10_itemsUnpack(std::vector<uint8_t> bits, uint32_t &idx);
        int64_t n3PUCCH_AN_List_r10_itemsValue() const;
        int n3PUCCH_AN_List_r10_itemsSetValue(int64_t value);
        std::string n3PUCCH_AN_List_r10_itemsToString(uint32_t indent) const;
        std::string n3PUCCH_AN_List_r10_itemsToStringNoNewLines() const;
        int n3PUCCH_AN_List_r10_itemsClear();
        bool n3PUCCH_AN_List_r10_itemsIsPresent() const;
    private:
        bool n3PUCCH_AN_List_r10_itemspresent;
        int64_t n3PUCCH_AN_List_r10_itemsinternal_value;
    };

public:
    int n3PUCCH_AN_List_r10_Pack(std::vector<uint8_t> &bits);
    int n3PUCCH_AN_List_r10_Unpack(std::vector<uint8_t> bits);
    int n3PUCCH_AN_List_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::vector<n3PUCCH_AN_List_r10_items> n3PUCCH_AN_List_r10_Value() const;
    int n3PUCCH_AN_List_r10_SetValue(std::vector<n3PUCCH_AN_List_r10_items>);
    int n3PUCCH_AN_List_r10_Clear();
    bool n3PUCCH_AN_List_r10_IsPresent() const;
    std::string n3PUCCH_AN_List_r10_ToString(uint32_t indent) const;
    std::string n3PUCCH_AN_List_r10_ToStringNoNewLines() const;
private:
    std::vector<n3PUCCH_AN_List_r10_items> n3PUCCH_AN_List_r10_internal_value;
    bool n3PUCCH_AN_List_r10_present;

    // n1PUCCH-AN-CS-List-r10
public:
    class n1PUCCH_AN_CS_List_r10_items
    {
    public:
        int n1PUCCH_AN_CS_List_r10_itemsPack(std::vector<uint8_t> &bits);
        int n1PUCCH_AN_CS_List_r10_itemsUnpack(std::vector<uint8_t> bits);
        int n1PUCCH_AN_CS_List_r10_itemsUnpack(std::vector<uint8_t> bits, uint32_t &idx);
        int64_t n1PUCCH_AN_CS_List_r10_itemsValue() const;
        int n1PUCCH_AN_CS_List_r10_itemsSetValue(int64_t value);
        std::string n1PUCCH_AN_CS_List_r10_itemsToString(uint32_t indent) const;
        std::string n1PUCCH_AN_CS_List_r10_itemsToStringNoNewLines() const;
        int n1PUCCH_AN_CS_List_r10_itemsClear();
        bool n1PUCCH_AN_CS_List_r10_itemsIsPresent() const;
    private:
        bool n1PUCCH_AN_CS_List_r10_itemspresent;
        int64_t n1PUCCH_AN_CS_List_r10_itemsinternal_value;
    };

public:
    int n1PUCCH_AN_CS_List_r10_Pack(std::vector<uint8_t> &bits);
    int n1PUCCH_AN_CS_List_r10_Unpack(std::vector<uint8_t> bits);
    int n1PUCCH_AN_CS_List_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::vector<n1PUCCH_AN_CS_List_r10_items> n1PUCCH_AN_CS_List_r10_Value() const;
    int n1PUCCH_AN_CS_List_r10_SetValue(std::vector<n1PUCCH_AN_CS_List_r10_items>);
    int n1PUCCH_AN_CS_List_r10_Clear();
    bool n1PUCCH_AN_CS_List_r10_IsPresent() const;
    std::string n1PUCCH_AN_CS_List_r10_ToString(uint32_t indent) const;
    std::string n1PUCCH_AN_CS_List_r10_ToStringNoNewLines() const;
private:
    std::vector<n1PUCCH_AN_CS_List_r10_items> n1PUCCH_AN_CS_List_r10_internal_value;
    bool n1PUCCH_AN_CS_List_r10_present;

    // pucch-Format-r10
public:
    enum pucch_Format_r10_Enum {
        k_pucch_Format_r10_format3 = 0,
        k_pucch_Format_r10_channelSelection,
    };
    int pucch_Format_r10_Pack(std::vector<uint8_t> &bits);
    int pucch_Format_r10_Unpack(std::vector<uint8_t> bits);
    int pucch_Format_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    pucch_Format_r10_Enum pucch_Format_r10_Value() const;
    int pucch_Format_r10_SetValue(pucch_Format_r10_Enum value);
    int pucch_Format_r10_SetValue(std::string value);
    std::string pucch_Format_r10_ValueToString(pucch_Format_r10_Enum value) const;
    uint64_t pucch_Format_r10_NumberOfValues() const;
    std::string pucch_Format_r10_ToString(uint32_t indent) const;
    std::string pucch_Format_r10_ToStringNoNewLines() const;
    int pucch_Format_r10_Clear();
    bool pucch_Format_r10_IsPresent() const;
private:
    bool pucch_Format_r10_present;
    pucch_Format_r10_Enum pucch_Format_r10_internal_value;

    // simultaneousPUCCH-PUSCH-r10
public:
    enum simultaneousPUCCH_PUSCH_r10_Enum {
        k_simultaneousPUCCH_PUSCH_r10_true = 0,
    };
    int simultaneousPUCCH_PUSCH_r10_Pack(std::vector<uint8_t> &bits);
    int simultaneousPUCCH_PUSCH_r10_Unpack(std::vector<uint8_t> bits);
    int simultaneousPUCCH_PUSCH_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    simultaneousPUCCH_PUSCH_r10_Enum simultaneousPUCCH_PUSCH_r10_Value() const;
    int simultaneousPUCCH_PUSCH_r10_SetValue(simultaneousPUCCH_PUSCH_r10_Enum value);
    int simultaneousPUCCH_PUSCH_r10_SetValue(std::string value);
    std::string simultaneousPUCCH_PUSCH_r10_ValueToString(simultaneousPUCCH_PUSCH_r10_Enum value) const;
    uint64_t simultaneousPUCCH_PUSCH_r10_NumberOfValues() const;
    std::string simultaneousPUCCH_PUSCH_r10_ToString(uint32_t indent) const;
    std::string simultaneousPUCCH_PUSCH_r10_ToStringNoNewLines() const;
    int simultaneousPUCCH_PUSCH_r10_Clear();
    bool simultaneousPUCCH_PUSCH_r10_IsPresent() const;
private:
    bool simultaneousPUCCH_PUSCH_r10_present;
    simultaneousPUCCH_PUSCH_r10_Enum simultaneousPUCCH_PUSCH_r10_internal_value;

    // twoAntennaPortActivated-r10
public:
    enum twoAntennaPortActivated_r10_Enum {
        k_twoAntennaPortActivated_r10_true = 0,
    };
    int twoAntennaPortActivated_r10_Pack(std::vector<uint8_t> &bits);
    int twoAntennaPortActivated_r10_Unpack(std::vector<uint8_t> bits);
    int twoAntennaPortActivated_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    twoAntennaPortActivated_r10_Enum twoAntennaPortActivated_r10_Value() const;
    int twoAntennaPortActivated_r10_SetValue(twoAntennaPortActivated_r10_Enum value);
    int twoAntennaPortActivated_r10_SetValue(std::string value);
    std::string twoAntennaPortActivated_r10_ValueToString(twoAntennaPortActivated_r10_Enum value) const;
    uint64_t twoAntennaPortActivated_r10_NumberOfValues() const;
    std::string twoAntennaPortActivated_r10_ToString(uint32_t indent) const;
    std::string twoAntennaPortActivated_r10_ToStringNoNewLines() const;
    int twoAntennaPortActivated_r10_Clear();
    bool twoAntennaPortActivated_r10_IsPresent() const;
private:
    bool twoAntennaPortActivated_r10_present;
    twoAntennaPortActivated_r10_Enum twoAntennaPortActivated_r10_internal_value;

    // n1PUCCH-AN-RepP1-r10
public:
    int n1PUCCH_AN_RepP1_r10_Pack(std::vector<uint8_t> &bits);
    int n1PUCCH_AN_RepP1_r10_Unpack(std::vector<uint8_t> bits);
    int n1PUCCH_AN_RepP1_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t n1PUCCH_AN_RepP1_r10_Value() const;
    int n1PUCCH_AN_RepP1_r10_SetValue(int64_t value);
    std::string n1PUCCH_AN_RepP1_r10_ToString(uint32_t indent) const;
    std::string n1PUCCH_AN_RepP1_r10_ToStringNoNewLines() const;
    int n1PUCCH_AN_RepP1_r10_Clear();
    bool n1PUCCH_AN_RepP1_r10_IsPresent() const;
private:
    bool n1PUCCH_AN_RepP1_r10_present;
    int64_t n1PUCCH_AN_RepP1_r10_internal_value;

};

#endif
