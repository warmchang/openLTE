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

#ifndef __CellChangeOrder_H__
#define __CellChangeOrder_H__

#include "PhysCellIdGERAN.h"
#include "CarrierFreqGERAN.h"
#include "SI_OrPSI_GERAN.h"

#include <array>
#include <cstdint>
#include <vector>

class CellChangeOrder
{
public:
    CellChangeOrder() : t304_present{false}, targetRAT_Type_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // t304
public:
    enum t304_Enum {
        k_t304_ms100 = 0,
        k_t304_ms200,
        k_t304_ms500,
        k_t304_ms1000,
        k_t304_ms2000,
        k_t304_ms4000,
        k_t304_ms8000,
        k_t304_spare1,
    };
    int t304_Pack(std::vector<uint8_t> &bits);
    int t304_Unpack(std::vector<uint8_t> bits);
    int t304_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    t304_Enum t304_Value() const;
    int t304_SetValue(t304_Enum value);
    int t304_SetValue(std::string value);
    std::string t304_ValueToString(t304_Enum value) const;
    uint64_t t304_NumberOfValues() const;
    std::string t304_ToString(uint32_t indent) const;
    std::string t304_ToStringNoNewLines() const;
    int t304_Clear();
    bool t304_IsPresent() const;
private:
    bool t304_present;
    t304_Enum t304_internal_value;

    // targetRAT-Type
public:
    enum targetRAT_Type_Enum {
        k_targetRAT_Type_geran = 0,
    };
    int targetRAT_Type_Pack(std::vector<uint8_t> &bits);
    int targetRAT_Type_Unpack(std::vector<uint8_t> bits);
    int targetRAT_Type_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    targetRAT_Type_Enum targetRAT_Type_Choice() const;
    int targetRAT_Type_SetChoice(targetRAT_Type_Enum choice);
    std::string targetRAT_Type_ChoiceToString(targetRAT_Type_Enum value) const;
    uint64_t targetRAT_Type_NumberOfChoices() const;
    std::string targetRAT_Type_ToString(uint32_t indent) const;
    std::string targetRAT_Type_ToStringNoNewLines() const;
    int targetRAT_Type_Clear();
    bool targetRAT_Type_IsPresent() const;
private:
    bool targetRAT_Type_present;
    targetRAT_Type_Enum targetRAT_Type_internal_choice;

    // geran
public:
    class targetRAT_Type_geran
    {
    public:
        targetRAT_Type_geran() : physCellId_present{false}, carrierFreq_present{false}, networkControlOrder_present{false}, systemInformation_present{false} {};
    public:
        int Pack(std::vector<uint8_t> &bits);
        int Unpack(std::vector<uint8_t> bits);
        int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        std::string ToString(uint32_t indent) const;
        std::string ToStringNoNewLines() const;

        // physCellId
    public:
        PhysCellIdGERAN* physCellId_Set();
        int physCellId_Set(PhysCellIdGERAN &value);
        const PhysCellIdGERAN& physCellId_Get() const;
        std::string physCellId_ToString(uint32_t indent) const;
        std::string physCellId_ToStringNoNewLines() const;
        int physCellId_Clear();
        bool physCellId_IsPresent() const;
    private:
        bool physCellId_present;
        PhysCellIdGERAN physCellId;

        // carrierFreq
    public:
        CarrierFreqGERAN* carrierFreq_Set();
        int carrierFreq_Set(CarrierFreqGERAN &value);
        const CarrierFreqGERAN& carrierFreq_Get() const;
        std::string carrierFreq_ToString(uint32_t indent) const;
        std::string carrierFreq_ToStringNoNewLines() const;
        int carrierFreq_Clear();
        bool carrierFreq_IsPresent() const;
    private:
        bool carrierFreq_present;
        CarrierFreqGERAN carrierFreq;

        // networkControlOrder
    public:
        int networkControlOrder_Pack(std::vector<uint8_t> &bits);
        int networkControlOrder_Unpack(std::vector<uint8_t> bits);
        int networkControlOrder_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        uint8_t networkControlOrder_Value() const;
        int networkControlOrder_SetValue(uint8_t value);
        std::string networkControlOrder_ToString(uint32_t indent) const;
        std::string networkControlOrder_ToStringNoNewLines() const;
        int networkControlOrder_Clear();
        bool networkControlOrder_IsPresent() const;
    private:
        bool networkControlOrder_present;
        uint8_t networkControlOrder_internal_value;

        // systemInformation
    public:
        SI_OrPSI_GERAN* systemInformation_Set();
        int systemInformation_Set(SI_OrPSI_GERAN &value);
        const SI_OrPSI_GERAN& systemInformation_Get() const;
        std::string systemInformation_ToString(uint32_t indent) const;
        std::string systemInformation_ToStringNoNewLines() const;
        int systemInformation_Clear();
        bool systemInformation_IsPresent() const;
    private:
        bool systemInformation_present;
        SI_OrPSI_GERAN systemInformation;

    };

    targetRAT_Type_geran targetRAT_Type_geran_value;


};

#endif
