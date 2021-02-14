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

#ifndef __RN_SubframeConfig_r10_H__
#define __RN_SubframeConfig_r10_H__

#include "FDD_SubframeConfig_r10.h"
#include "TDD_SubframeConfig_r10.h"

#include <array>
#include <cstdint>
#include <vector>

class RN_SubframeConfig_r10
{
public:
    RN_SubframeConfig_r10() : frameStructureType_r10_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // frameStructureType-r10
public:
    enum frameStructureType_r10_Enum {
        k_frameStructureType_r10_fdd_r10 = 0,
        k_frameStructureType_r10_tdd_r10,
    };
    int frameStructureType_r10_Pack(std::vector<uint8_t> &bits);
    int frameStructureType_r10_Unpack(std::vector<uint8_t> bits);
    int frameStructureType_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    frameStructureType_r10_Enum frameStructureType_r10_Choice() const;
    int frameStructureType_r10_SetChoice(frameStructureType_r10_Enum choice);
    std::string frameStructureType_r10_ChoiceToString(frameStructureType_r10_Enum value) const;
    uint64_t frameStructureType_r10_NumberOfChoices() const;
    std::string frameStructureType_r10_ToString(uint32_t indent) const;
    std::string frameStructureType_r10_ToStringNoNewLines() const;
    int frameStructureType_r10_Clear();
    bool frameStructureType_r10_IsPresent() const;
private:
    bool frameStructureType_r10_present;
    frameStructureType_r10_Enum frameStructureType_r10_internal_choice;

    // fdd-r10
public:
    FDD_SubframeConfig_r10* frameStructureType_r10_fdd_r10_Set();
    int frameStructureType_r10_fdd_r10_Set(FDD_SubframeConfig_r10 &value);
    const FDD_SubframeConfig_r10& frameStructureType_r10_fdd_r10_Get() const;
    std::string frameStructureType_r10_fdd_r10_ToString(uint32_t indent) const;
    std::string frameStructureType_r10_fdd_r10_ToStringNoNewLines() const;
    int frameStructureType_r10_fdd_r10_Clear();
    bool frameStructureType_r10_fdd_r10_IsPresent() const;
private:
    bool frameStructureType_r10_fdd_r10_present;
    FDD_SubframeConfig_r10 frameStructureType_r10_fdd_r10;

    // tdd-r10
public:
    TDD_SubframeConfig_r10* frameStructureType_r10_tdd_r10_Set();
    int frameStructureType_r10_tdd_r10_Set(TDD_SubframeConfig_r10 &value);
    const TDD_SubframeConfig_r10& frameStructureType_r10_tdd_r10_Get() const;
    std::string frameStructureType_r10_tdd_r10_ToString(uint32_t indent) const;
    std::string frameStructureType_r10_tdd_r10_ToStringNoNewLines() const;
    int frameStructureType_r10_tdd_r10_Clear();
    bool frameStructureType_r10_tdd_r10_IsPresent() const;
private:
    bool frameStructureType_r10_tdd_r10_present;
    TDD_SubframeConfig_r10 frameStructureType_r10_tdd_r10;


    // rpdcch-Config-r10
public:
    class rpdcch_Config_r10
    {
    public:
        rpdcch_Config_r10() : present{false}, resourceAllocationType_r10_present{false}, resourceBlockAssignment_r10_present{false}, demodulationRS_r10_present{false}, pdsch_Start_r10_present{false} {};
    public:
        int Pack(std::vector<uint8_t> &bits);
        int Unpack(std::vector<uint8_t> bits);
        int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        std::string ToString(uint32_t indent) const;
        std::string ToStringNoNewLines() const;
        int Set();
        int SetPresence(bool is_present);
        int Clear();
        bool IsPresent() const;
    private:
        bool present;

        // resourceAllocationType-r10
    public:
        enum resourceAllocationType_r10_Enum {
            k_resourceAllocationType_r10_type0 = 0,
            k_resourceAllocationType_r10_type1,
            k_resourceAllocationType_r10_type2Localized,
            k_resourceAllocationType_r10_type2Distributed,
        };
        int resourceAllocationType_r10_Pack(std::vector<uint8_t> &bits);
        int resourceAllocationType_r10_Unpack(std::vector<uint8_t> bits);
        int resourceAllocationType_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        resourceAllocationType_r10_Enum resourceAllocationType_r10_Value() const;
        int resourceAllocationType_r10_SetValue(resourceAllocationType_r10_Enum value);
        int resourceAllocationType_r10_SetValue(std::string value);
        std::string resourceAllocationType_r10_ValueToString(resourceAllocationType_r10_Enum value) const;
        uint64_t resourceAllocationType_r10_NumberOfValues() const;
        std::string resourceAllocationType_r10_ToString(uint32_t indent) const;
        std::string resourceAllocationType_r10_ToStringNoNewLines() const;
        int resourceAllocationType_r10_Clear();
        bool resourceAllocationType_r10_IsPresent() const;
    private:
        bool resourceAllocationType_r10_present;
        resourceAllocationType_r10_Enum resourceAllocationType_r10_internal_value;

        // resourceBlockAssignment-r10
    public:
        enum resourceBlockAssignment_r10_Enum {
            k_resourceBlockAssignment_r10_type01_r10 = 0,
            k_resourceBlockAssignment_r10_type2_r10,
        };
        int resourceBlockAssignment_r10_Pack(std::vector<uint8_t> &bits);
        int resourceBlockAssignment_r10_Unpack(std::vector<uint8_t> bits);
        int resourceBlockAssignment_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        resourceBlockAssignment_r10_Enum resourceBlockAssignment_r10_Choice() const;
        int resourceBlockAssignment_r10_SetChoice(resourceBlockAssignment_r10_Enum choice);
        std::string resourceBlockAssignment_r10_ChoiceToString(resourceBlockAssignment_r10_Enum value) const;
        uint64_t resourceBlockAssignment_r10_NumberOfChoices() const;
        std::string resourceBlockAssignment_r10_ToString(uint32_t indent) const;
        std::string resourceBlockAssignment_r10_ToStringNoNewLines() const;
        int resourceBlockAssignment_r10_Clear();
        bool resourceBlockAssignment_r10_IsPresent() const;
    private:
        bool resourceBlockAssignment_r10_present;
        resourceBlockAssignment_r10_Enum resourceBlockAssignment_r10_internal_choice;

        // type01-r10
    public:
        enum resourceBlockAssignment_r10_type01_r10_Enum {
            k_resourceBlockAssignment_r10_type01_r10_nrb6_r10 = 0,
            k_resourceBlockAssignment_r10_type01_r10_nrb15_r10,
            k_resourceBlockAssignment_r10_type01_r10_nrb25_r10,
            k_resourceBlockAssignment_r10_type01_r10_nrb50_r10,
            k_resourceBlockAssignment_r10_type01_r10_nrb75_r10,
            k_resourceBlockAssignment_r10_type01_r10_nrb100_r10,
        };
        int resourceBlockAssignment_r10_type01_r10_Pack(std::vector<uint8_t> &bits);
        int resourceBlockAssignment_r10_type01_r10_Unpack(std::vector<uint8_t> bits);
        int resourceBlockAssignment_r10_type01_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        resourceBlockAssignment_r10_type01_r10_Enum resourceBlockAssignment_r10_type01_r10_Choice() const;
        int resourceBlockAssignment_r10_type01_r10_SetChoice(resourceBlockAssignment_r10_type01_r10_Enum choice);
        std::string resourceBlockAssignment_r10_type01_r10_ChoiceToString(resourceBlockAssignment_r10_type01_r10_Enum value) const;
        uint64_t resourceBlockAssignment_r10_type01_r10_NumberOfChoices() const;
        std::string resourceBlockAssignment_r10_type01_r10_ToString(uint32_t indent) const;
        std::string resourceBlockAssignment_r10_type01_r10_ToStringNoNewLines() const;
        int resourceBlockAssignment_r10_type01_r10_Clear();
        bool resourceBlockAssignment_r10_type01_r10_IsPresent() const;
    private:
        bool resourceBlockAssignment_r10_type01_r10_present;
        resourceBlockAssignment_r10_type01_r10_Enum resourceBlockAssignment_r10_type01_r10_internal_choice;

        // nrb6-r10
    public:
        int resourceBlockAssignment_r10_type01_r10_nrb6_r10_Pack(std::vector<uint8_t> &bits);
        int resourceBlockAssignment_r10_type01_r10_nrb6_r10_Unpack(std::vector<uint8_t> bits);
        int resourceBlockAssignment_r10_type01_r10_nrb6_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        uint8_t resourceBlockAssignment_r10_type01_r10_nrb6_r10_Value() const;
        int resourceBlockAssignment_r10_type01_r10_nrb6_r10_SetValue(uint8_t value);
        std::string resourceBlockAssignment_r10_type01_r10_nrb6_r10_ToString(uint32_t indent) const;
        std::string resourceBlockAssignment_r10_type01_r10_nrb6_r10_ToStringNoNewLines() const;
        int resourceBlockAssignment_r10_type01_r10_nrb6_r10_Clear();
        bool resourceBlockAssignment_r10_type01_r10_nrb6_r10_IsPresent() const;
    private:
        bool resourceBlockAssignment_r10_type01_r10_nrb6_r10_present;
        uint8_t resourceBlockAssignment_r10_type01_r10_nrb6_r10_internal_value;

        // nrb15-r10
    public:
        int resourceBlockAssignment_r10_type01_r10_nrb15_r10_Pack(std::vector<uint8_t> &bits);
        int resourceBlockAssignment_r10_type01_r10_nrb15_r10_Unpack(std::vector<uint8_t> bits);
        int resourceBlockAssignment_r10_type01_r10_nrb15_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        uint8_t resourceBlockAssignment_r10_type01_r10_nrb15_r10_Value() const;
        int resourceBlockAssignment_r10_type01_r10_nrb15_r10_SetValue(uint8_t value);
        std::string resourceBlockAssignment_r10_type01_r10_nrb15_r10_ToString(uint32_t indent) const;
        std::string resourceBlockAssignment_r10_type01_r10_nrb15_r10_ToStringNoNewLines() const;
        int resourceBlockAssignment_r10_type01_r10_nrb15_r10_Clear();
        bool resourceBlockAssignment_r10_type01_r10_nrb15_r10_IsPresent() const;
    private:
        bool resourceBlockAssignment_r10_type01_r10_nrb15_r10_present;
        uint8_t resourceBlockAssignment_r10_type01_r10_nrb15_r10_internal_value;

        // nrb25-r10
    public:
        int resourceBlockAssignment_r10_type01_r10_nrb25_r10_Pack(std::vector<uint8_t> &bits);
        int resourceBlockAssignment_r10_type01_r10_nrb25_r10_Unpack(std::vector<uint8_t> bits);
        int resourceBlockAssignment_r10_type01_r10_nrb25_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        uint16_t resourceBlockAssignment_r10_type01_r10_nrb25_r10_Value() const;
        int resourceBlockAssignment_r10_type01_r10_nrb25_r10_SetValue(uint16_t value);
        std::string resourceBlockAssignment_r10_type01_r10_nrb25_r10_ToString(uint32_t indent) const;
        std::string resourceBlockAssignment_r10_type01_r10_nrb25_r10_ToStringNoNewLines() const;
        int resourceBlockAssignment_r10_type01_r10_nrb25_r10_Clear();
        bool resourceBlockAssignment_r10_type01_r10_nrb25_r10_IsPresent() const;
    private:
        bool resourceBlockAssignment_r10_type01_r10_nrb25_r10_present;
        uint16_t resourceBlockAssignment_r10_type01_r10_nrb25_r10_internal_value;

        // nrb50-r10
    public:
        int resourceBlockAssignment_r10_type01_r10_nrb50_r10_Pack(std::vector<uint8_t> &bits);
        int resourceBlockAssignment_r10_type01_r10_nrb50_r10_Unpack(std::vector<uint8_t> bits);
        int resourceBlockAssignment_r10_type01_r10_nrb50_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        uint32_t resourceBlockAssignment_r10_type01_r10_nrb50_r10_Value() const;
        int resourceBlockAssignment_r10_type01_r10_nrb50_r10_SetValue(uint32_t value);
        std::string resourceBlockAssignment_r10_type01_r10_nrb50_r10_ToString(uint32_t indent) const;
        std::string resourceBlockAssignment_r10_type01_r10_nrb50_r10_ToStringNoNewLines() const;
        int resourceBlockAssignment_r10_type01_r10_nrb50_r10_Clear();
        bool resourceBlockAssignment_r10_type01_r10_nrb50_r10_IsPresent() const;
    private:
        bool resourceBlockAssignment_r10_type01_r10_nrb50_r10_present;
        uint32_t resourceBlockAssignment_r10_type01_r10_nrb50_r10_internal_value;

        // nrb75-r10
    public:
        int resourceBlockAssignment_r10_type01_r10_nrb75_r10_Pack(std::vector<uint8_t> &bits);
        int resourceBlockAssignment_r10_type01_r10_nrb75_r10_Unpack(std::vector<uint8_t> bits);
        int resourceBlockAssignment_r10_type01_r10_nrb75_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        uint32_t resourceBlockAssignment_r10_type01_r10_nrb75_r10_Value() const;
        int resourceBlockAssignment_r10_type01_r10_nrb75_r10_SetValue(uint32_t value);
        std::string resourceBlockAssignment_r10_type01_r10_nrb75_r10_ToString(uint32_t indent) const;
        std::string resourceBlockAssignment_r10_type01_r10_nrb75_r10_ToStringNoNewLines() const;
        int resourceBlockAssignment_r10_type01_r10_nrb75_r10_Clear();
        bool resourceBlockAssignment_r10_type01_r10_nrb75_r10_IsPresent() const;
    private:
        bool resourceBlockAssignment_r10_type01_r10_nrb75_r10_present;
        uint32_t resourceBlockAssignment_r10_type01_r10_nrb75_r10_internal_value;

        // nrb100-r10
    public:
        int resourceBlockAssignment_r10_type01_r10_nrb100_r10_Pack(std::vector<uint8_t> &bits);
        int resourceBlockAssignment_r10_type01_r10_nrb100_r10_Unpack(std::vector<uint8_t> bits);
        int resourceBlockAssignment_r10_type01_r10_nrb100_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        uint32_t resourceBlockAssignment_r10_type01_r10_nrb100_r10_Value() const;
        int resourceBlockAssignment_r10_type01_r10_nrb100_r10_SetValue(uint32_t value);
        std::string resourceBlockAssignment_r10_type01_r10_nrb100_r10_ToString(uint32_t indent) const;
        std::string resourceBlockAssignment_r10_type01_r10_nrb100_r10_ToStringNoNewLines() const;
        int resourceBlockAssignment_r10_type01_r10_nrb100_r10_Clear();
        bool resourceBlockAssignment_r10_type01_r10_nrb100_r10_IsPresent() const;
    private:
        bool resourceBlockAssignment_r10_type01_r10_nrb100_r10_present;
        uint32_t resourceBlockAssignment_r10_type01_r10_nrb100_r10_internal_value;


        // type2-r10
    public:
        enum resourceBlockAssignment_r10_type2_r10_Enum {
            k_resourceBlockAssignment_r10_type2_r10_nrb6_r10 = 0,
            k_resourceBlockAssignment_r10_type2_r10_nrb15_r10,
            k_resourceBlockAssignment_r10_type2_r10_nrb25_r10,
            k_resourceBlockAssignment_r10_type2_r10_nrb50_r10,
            k_resourceBlockAssignment_r10_type2_r10_nrb75_r10,
            k_resourceBlockAssignment_r10_type2_r10_nrb100_r10,
        };
        int resourceBlockAssignment_r10_type2_r10_Pack(std::vector<uint8_t> &bits);
        int resourceBlockAssignment_r10_type2_r10_Unpack(std::vector<uint8_t> bits);
        int resourceBlockAssignment_r10_type2_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        resourceBlockAssignment_r10_type2_r10_Enum resourceBlockAssignment_r10_type2_r10_Choice() const;
        int resourceBlockAssignment_r10_type2_r10_SetChoice(resourceBlockAssignment_r10_type2_r10_Enum choice);
        std::string resourceBlockAssignment_r10_type2_r10_ChoiceToString(resourceBlockAssignment_r10_type2_r10_Enum value) const;
        uint64_t resourceBlockAssignment_r10_type2_r10_NumberOfChoices() const;
        std::string resourceBlockAssignment_r10_type2_r10_ToString(uint32_t indent) const;
        std::string resourceBlockAssignment_r10_type2_r10_ToStringNoNewLines() const;
        int resourceBlockAssignment_r10_type2_r10_Clear();
        bool resourceBlockAssignment_r10_type2_r10_IsPresent() const;
    private:
        bool resourceBlockAssignment_r10_type2_r10_present;
        resourceBlockAssignment_r10_type2_r10_Enum resourceBlockAssignment_r10_type2_r10_internal_choice;

        // nrb6-r10
    public:
        int resourceBlockAssignment_r10_type2_r10_nrb6_r10_Pack(std::vector<uint8_t> &bits);
        int resourceBlockAssignment_r10_type2_r10_nrb6_r10_Unpack(std::vector<uint8_t> bits);
        int resourceBlockAssignment_r10_type2_r10_nrb6_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        uint8_t resourceBlockAssignment_r10_type2_r10_nrb6_r10_Value() const;
        int resourceBlockAssignment_r10_type2_r10_nrb6_r10_SetValue(uint8_t value);
        std::string resourceBlockAssignment_r10_type2_r10_nrb6_r10_ToString(uint32_t indent) const;
        std::string resourceBlockAssignment_r10_type2_r10_nrb6_r10_ToStringNoNewLines() const;
        int resourceBlockAssignment_r10_type2_r10_nrb6_r10_Clear();
        bool resourceBlockAssignment_r10_type2_r10_nrb6_r10_IsPresent() const;
    private:
        bool resourceBlockAssignment_r10_type2_r10_nrb6_r10_present;
        uint8_t resourceBlockAssignment_r10_type2_r10_nrb6_r10_internal_value;

        // nrb15-r10
    public:
        int resourceBlockAssignment_r10_type2_r10_nrb15_r10_Pack(std::vector<uint8_t> &bits);
        int resourceBlockAssignment_r10_type2_r10_nrb15_r10_Unpack(std::vector<uint8_t> bits);
        int resourceBlockAssignment_r10_type2_r10_nrb15_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        uint8_t resourceBlockAssignment_r10_type2_r10_nrb15_r10_Value() const;
        int resourceBlockAssignment_r10_type2_r10_nrb15_r10_SetValue(uint8_t value);
        std::string resourceBlockAssignment_r10_type2_r10_nrb15_r10_ToString(uint32_t indent) const;
        std::string resourceBlockAssignment_r10_type2_r10_nrb15_r10_ToStringNoNewLines() const;
        int resourceBlockAssignment_r10_type2_r10_nrb15_r10_Clear();
        bool resourceBlockAssignment_r10_type2_r10_nrb15_r10_IsPresent() const;
    private:
        bool resourceBlockAssignment_r10_type2_r10_nrb15_r10_present;
        uint8_t resourceBlockAssignment_r10_type2_r10_nrb15_r10_internal_value;

        // nrb25-r10
    public:
        int resourceBlockAssignment_r10_type2_r10_nrb25_r10_Pack(std::vector<uint8_t> &bits);
        int resourceBlockAssignment_r10_type2_r10_nrb25_r10_Unpack(std::vector<uint8_t> bits);
        int resourceBlockAssignment_r10_type2_r10_nrb25_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        uint16_t resourceBlockAssignment_r10_type2_r10_nrb25_r10_Value() const;
        int resourceBlockAssignment_r10_type2_r10_nrb25_r10_SetValue(uint16_t value);
        std::string resourceBlockAssignment_r10_type2_r10_nrb25_r10_ToString(uint32_t indent) const;
        std::string resourceBlockAssignment_r10_type2_r10_nrb25_r10_ToStringNoNewLines() const;
        int resourceBlockAssignment_r10_type2_r10_nrb25_r10_Clear();
        bool resourceBlockAssignment_r10_type2_r10_nrb25_r10_IsPresent() const;
    private:
        bool resourceBlockAssignment_r10_type2_r10_nrb25_r10_present;
        uint16_t resourceBlockAssignment_r10_type2_r10_nrb25_r10_internal_value;

        // nrb50-r10
    public:
        int resourceBlockAssignment_r10_type2_r10_nrb50_r10_Pack(std::vector<uint8_t> &bits);
        int resourceBlockAssignment_r10_type2_r10_nrb50_r10_Unpack(std::vector<uint8_t> bits);
        int resourceBlockAssignment_r10_type2_r10_nrb50_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        uint16_t resourceBlockAssignment_r10_type2_r10_nrb50_r10_Value() const;
        int resourceBlockAssignment_r10_type2_r10_nrb50_r10_SetValue(uint16_t value);
        std::string resourceBlockAssignment_r10_type2_r10_nrb50_r10_ToString(uint32_t indent) const;
        std::string resourceBlockAssignment_r10_type2_r10_nrb50_r10_ToStringNoNewLines() const;
        int resourceBlockAssignment_r10_type2_r10_nrb50_r10_Clear();
        bool resourceBlockAssignment_r10_type2_r10_nrb50_r10_IsPresent() const;
    private:
        bool resourceBlockAssignment_r10_type2_r10_nrb50_r10_present;
        uint16_t resourceBlockAssignment_r10_type2_r10_nrb50_r10_internal_value;

        // nrb75-r10
    public:
        int resourceBlockAssignment_r10_type2_r10_nrb75_r10_Pack(std::vector<uint8_t> &bits);
        int resourceBlockAssignment_r10_type2_r10_nrb75_r10_Unpack(std::vector<uint8_t> bits);
        int resourceBlockAssignment_r10_type2_r10_nrb75_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        uint16_t resourceBlockAssignment_r10_type2_r10_nrb75_r10_Value() const;
        int resourceBlockAssignment_r10_type2_r10_nrb75_r10_SetValue(uint16_t value);
        std::string resourceBlockAssignment_r10_type2_r10_nrb75_r10_ToString(uint32_t indent) const;
        std::string resourceBlockAssignment_r10_type2_r10_nrb75_r10_ToStringNoNewLines() const;
        int resourceBlockAssignment_r10_type2_r10_nrb75_r10_Clear();
        bool resourceBlockAssignment_r10_type2_r10_nrb75_r10_IsPresent() const;
    private:
        bool resourceBlockAssignment_r10_type2_r10_nrb75_r10_present;
        uint16_t resourceBlockAssignment_r10_type2_r10_nrb75_r10_internal_value;

        // nrb100-r10
    public:
        int resourceBlockAssignment_r10_type2_r10_nrb100_r10_Pack(std::vector<uint8_t> &bits);
        int resourceBlockAssignment_r10_type2_r10_nrb100_r10_Unpack(std::vector<uint8_t> bits);
        int resourceBlockAssignment_r10_type2_r10_nrb100_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        uint16_t resourceBlockAssignment_r10_type2_r10_nrb100_r10_Value() const;
        int resourceBlockAssignment_r10_type2_r10_nrb100_r10_SetValue(uint16_t value);
        std::string resourceBlockAssignment_r10_type2_r10_nrb100_r10_ToString(uint32_t indent) const;
        std::string resourceBlockAssignment_r10_type2_r10_nrb100_r10_ToStringNoNewLines() const;
        int resourceBlockAssignment_r10_type2_r10_nrb100_r10_Clear();
        bool resourceBlockAssignment_r10_type2_r10_nrb100_r10_IsPresent() const;
    private:
        bool resourceBlockAssignment_r10_type2_r10_nrb100_r10_present;
        uint16_t resourceBlockAssignment_r10_type2_r10_nrb100_r10_internal_value;



        // demodulationRS-r10
    public:
        enum demodulationRS_r10_Enum {
            k_demodulationRS_r10_interleaving_r10 = 0,
            k_demodulationRS_r10_noInterleaving_r10,
        };
        int demodulationRS_r10_Pack(std::vector<uint8_t> &bits);
        int demodulationRS_r10_Unpack(std::vector<uint8_t> bits);
        int demodulationRS_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        demodulationRS_r10_Enum demodulationRS_r10_Choice() const;
        int demodulationRS_r10_SetChoice(demodulationRS_r10_Enum choice);
        std::string demodulationRS_r10_ChoiceToString(demodulationRS_r10_Enum value) const;
        uint64_t demodulationRS_r10_NumberOfChoices() const;
        std::string demodulationRS_r10_ToString(uint32_t indent) const;
        std::string demodulationRS_r10_ToStringNoNewLines() const;
        int demodulationRS_r10_Clear();
        bool demodulationRS_r10_IsPresent() const;
    private:
        bool demodulationRS_r10_present;
        demodulationRS_r10_Enum demodulationRS_r10_internal_choice;

        // interleaving-r10
    public:
        enum demodulationRS_r10_interleaving_r10_Enum {
            k_demodulationRS_r10_interleaving_r10_crs = 0,
        };
        int demodulationRS_r10_interleaving_r10_Pack(std::vector<uint8_t> &bits);
        int demodulationRS_r10_interleaving_r10_Unpack(std::vector<uint8_t> bits);
        int demodulationRS_r10_interleaving_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        demodulationRS_r10_interleaving_r10_Enum demodulationRS_r10_interleaving_r10_Value() const;
        int demodulationRS_r10_interleaving_r10_SetValue(demodulationRS_r10_interleaving_r10_Enum value);
        int demodulationRS_r10_interleaving_r10_SetValue(std::string value);
        std::string demodulationRS_r10_interleaving_r10_ValueToString(demodulationRS_r10_interleaving_r10_Enum value) const;
        uint64_t demodulationRS_r10_interleaving_r10_NumberOfValues() const;
        std::string demodulationRS_r10_interleaving_r10_ToString(uint32_t indent) const;
        std::string demodulationRS_r10_interleaving_r10_ToStringNoNewLines() const;
        int demodulationRS_r10_interleaving_r10_Clear();
        bool demodulationRS_r10_interleaving_r10_IsPresent() const;
    private:
        bool demodulationRS_r10_interleaving_r10_present;
        demodulationRS_r10_interleaving_r10_Enum demodulationRS_r10_interleaving_r10_internal_value;

        // noInterleaving-r10
    public:
        enum demodulationRS_r10_noInterleaving_r10_Enum {
            k_demodulationRS_r10_noInterleaving_r10_crs = 0,
            k_demodulationRS_r10_noInterleaving_r10_dmrs,
        };
        int demodulationRS_r10_noInterleaving_r10_Pack(std::vector<uint8_t> &bits);
        int demodulationRS_r10_noInterleaving_r10_Unpack(std::vector<uint8_t> bits);
        int demodulationRS_r10_noInterleaving_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        demodulationRS_r10_noInterleaving_r10_Enum demodulationRS_r10_noInterleaving_r10_Value() const;
        int demodulationRS_r10_noInterleaving_r10_SetValue(demodulationRS_r10_noInterleaving_r10_Enum value);
        int demodulationRS_r10_noInterleaving_r10_SetValue(std::string value);
        std::string demodulationRS_r10_noInterleaving_r10_ValueToString(demodulationRS_r10_noInterleaving_r10_Enum value) const;
        uint64_t demodulationRS_r10_noInterleaving_r10_NumberOfValues() const;
        std::string demodulationRS_r10_noInterleaving_r10_ToString(uint32_t indent) const;
        std::string demodulationRS_r10_noInterleaving_r10_ToStringNoNewLines() const;
        int demodulationRS_r10_noInterleaving_r10_Clear();
        bool demodulationRS_r10_noInterleaving_r10_IsPresent() const;
    private:
        bool demodulationRS_r10_noInterleaving_r10_present;
        demodulationRS_r10_noInterleaving_r10_Enum demodulationRS_r10_noInterleaving_r10_internal_value;


        // pdsch-Start-r10
    public:
        int pdsch_Start_r10_Pack(std::vector<uint8_t> &bits);
        int pdsch_Start_r10_Unpack(std::vector<uint8_t> bits);
        int pdsch_Start_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        int64_t pdsch_Start_r10_Value() const;
        int pdsch_Start_r10_SetValue(int64_t value);
        std::string pdsch_Start_r10_ToString(uint32_t indent) const;
        std::string pdsch_Start_r10_ToStringNoNewLines() const;
        int pdsch_Start_r10_Clear();
        bool pdsch_Start_r10_IsPresent() const;
    private:
        bool pdsch_Start_r10_present;
        int64_t pdsch_Start_r10_internal_value;

        // pucch-Config-r10
    public:
        class pucch_Config_r10
        {
        public:
            pucch_Config_r10() : n1_PUCCH_AN_port0_r10_present{false}, n1_PUCCH_AN_port1_r10_present{false} {};
        public:
            int Pack(std::vector<uint8_t> &bits);
            int Unpack(std::vector<uint8_t> bits);
            int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
            std::string ToString(uint32_t indent) const;
            std::string ToStringNoNewLines() const;

            // n1-PUCCH-AN-port0-r10
        public:
            int n1_PUCCH_AN_port0_r10_Pack(std::vector<uint8_t> &bits);
            int n1_PUCCH_AN_port0_r10_Unpack(std::vector<uint8_t> bits);
            int n1_PUCCH_AN_port0_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
            int64_t n1_PUCCH_AN_port0_r10_Value() const;
            int n1_PUCCH_AN_port0_r10_SetValue(int64_t value);
            std::string n1_PUCCH_AN_port0_r10_ToString(uint32_t indent) const;
            std::string n1_PUCCH_AN_port0_r10_ToStringNoNewLines() const;
            int n1_PUCCH_AN_port0_r10_Clear();
            bool n1_PUCCH_AN_port0_r10_IsPresent() const;
        private:
            bool n1_PUCCH_AN_port0_r10_present;
            int64_t n1_PUCCH_AN_port0_r10_internal_value;

            // n1-PUCCH-AN-port1-r10
        public:
            int n1_PUCCH_AN_port1_r10_Pack(std::vector<uint8_t> &bits);
            int n1_PUCCH_AN_port1_r10_Unpack(std::vector<uint8_t> bits);
            int n1_PUCCH_AN_port1_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
            int64_t n1_PUCCH_AN_port1_r10_Value() const;
            int n1_PUCCH_AN_port1_r10_SetValue(int64_t value);
            std::string n1_PUCCH_AN_port1_r10_ToString(uint32_t indent) const;
            std::string n1_PUCCH_AN_port1_r10_ToStringNoNewLines() const;
            int n1_PUCCH_AN_port1_r10_Clear();
            bool n1_PUCCH_AN_port1_r10_IsPresent() const;
        private:
            bool n1_PUCCH_AN_port1_r10_present;
            int64_t n1_PUCCH_AN_port1_r10_internal_value;

        };

        pucch_Config_r10 pucch_Config_r10_value;

    };

    rpdcch_Config_r10 rpdcch_Config_r10_value;

};

#endif
