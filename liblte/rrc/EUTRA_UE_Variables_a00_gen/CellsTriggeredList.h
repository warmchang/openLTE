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

#ifndef __CellsTriggeredList_H__
#define __CellsTriggeredList_H__

#include "PhysCellId.h"
#include "PhysCellIdUTRA_FDD.h"
#include "PhysCellIdUTRA_TDD.h"
#include "CarrierFreqGERAN.h"
#include "PhysCellIdGERAN.h"
#include "PhysCellIdCDMA2000.h"

#include <array>
#include <cstdint>
#include <vector>

class CellsTriggeredList
{
public:
    class CellsTriggeredList_
    {
    public:
        enum CellsTriggeredList_Enum {
            k_CellsTriggeredList_physCellIdEUTRA = 0,
            k_CellsTriggeredList_physCellIdUTRA,
            k_CellsTriggeredList_physCellIdGERAN,
            k_CellsTriggeredList_physCellIdCDMA2000,
        };
        int CellsTriggeredList_Pack(std::vector<uint8_t> &bits);
        int CellsTriggeredList_Unpack(std::vector<uint8_t> bits);
        int CellsTriggeredList_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        CellsTriggeredList_Enum CellsTriggeredList_Choice() const;
        int CellsTriggeredList_SetChoice(CellsTriggeredList_Enum choice);
        std::string CellsTriggeredList_ChoiceToString(CellsTriggeredList_Enum value) const;
        uint64_t CellsTriggeredList_NumberOfChoices() const;
        std::string CellsTriggeredList_ToString(uint32_t indent) const;
        std::string CellsTriggeredList_ToStringNoNewLines() const;
        int CellsTriggeredList_Clear();
        bool CellsTriggeredList_IsPresent() const;
    private:
        bool CellsTriggeredList_present;
        CellsTriggeredList_Enum CellsTriggeredList_internal_choice;

        // physCellIdEUTRA
    public:
        PhysCellId* CellsTriggeredList_physCellIdEUTRA_Set();
        int CellsTriggeredList_physCellIdEUTRA_Set(PhysCellId &value);
        const PhysCellId& CellsTriggeredList_physCellIdEUTRA_Get() const;
        std::string CellsTriggeredList_physCellIdEUTRA_ToString(uint32_t indent) const;
        std::string CellsTriggeredList_physCellIdEUTRA_ToStringNoNewLines() const;
        int CellsTriggeredList_physCellIdEUTRA_Clear();
        bool CellsTriggeredList_physCellIdEUTRA_IsPresent() const;
    private:
        bool CellsTriggeredList_physCellIdEUTRA_present;
        PhysCellId CellsTriggeredList_physCellIdEUTRA;

        // physCellIdUTRA
    public:
        enum CellsTriggeredList_physCellIdUTRA_Enum {
            k_CellsTriggeredList_physCellIdUTRA_fdd = 0,
            k_CellsTriggeredList_physCellIdUTRA_tdd,
        };
        int CellsTriggeredList_physCellIdUTRA_Pack(std::vector<uint8_t> &bits);
        int CellsTriggeredList_physCellIdUTRA_Unpack(std::vector<uint8_t> bits);
        int CellsTriggeredList_physCellIdUTRA_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        CellsTriggeredList_physCellIdUTRA_Enum CellsTriggeredList_physCellIdUTRA_Choice() const;
        int CellsTriggeredList_physCellIdUTRA_SetChoice(CellsTriggeredList_physCellIdUTRA_Enum choice);
        std::string CellsTriggeredList_physCellIdUTRA_ChoiceToString(CellsTriggeredList_physCellIdUTRA_Enum value) const;
        uint64_t CellsTriggeredList_physCellIdUTRA_NumberOfChoices() const;
        std::string CellsTriggeredList_physCellIdUTRA_ToString(uint32_t indent) const;
        std::string CellsTriggeredList_physCellIdUTRA_ToStringNoNewLines() const;
        int CellsTriggeredList_physCellIdUTRA_Clear();
        bool CellsTriggeredList_physCellIdUTRA_IsPresent() const;
    private:
        bool CellsTriggeredList_physCellIdUTRA_present;
        CellsTriggeredList_physCellIdUTRA_Enum CellsTriggeredList_physCellIdUTRA_internal_choice;

        // fdd
    public:
        PhysCellIdUTRA_FDD* CellsTriggeredList_physCellIdUTRA_fdd_Set();
        int CellsTriggeredList_physCellIdUTRA_fdd_Set(PhysCellIdUTRA_FDD &value);
        const PhysCellIdUTRA_FDD& CellsTriggeredList_physCellIdUTRA_fdd_Get() const;
        std::string CellsTriggeredList_physCellIdUTRA_fdd_ToString(uint32_t indent) const;
        std::string CellsTriggeredList_physCellIdUTRA_fdd_ToStringNoNewLines() const;
        int CellsTriggeredList_physCellIdUTRA_fdd_Clear();
        bool CellsTriggeredList_physCellIdUTRA_fdd_IsPresent() const;
    private:
        bool CellsTriggeredList_physCellIdUTRA_fdd_present;
        PhysCellIdUTRA_FDD CellsTriggeredList_physCellIdUTRA_fdd;

        // tdd
    public:
        PhysCellIdUTRA_TDD* CellsTriggeredList_physCellIdUTRA_tdd_Set();
        int CellsTriggeredList_physCellIdUTRA_tdd_Set(PhysCellIdUTRA_TDD &value);
        const PhysCellIdUTRA_TDD& CellsTriggeredList_physCellIdUTRA_tdd_Get() const;
        std::string CellsTriggeredList_physCellIdUTRA_tdd_ToString(uint32_t indent) const;
        std::string CellsTriggeredList_physCellIdUTRA_tdd_ToStringNoNewLines() const;
        int CellsTriggeredList_physCellIdUTRA_tdd_Clear();
        bool CellsTriggeredList_physCellIdUTRA_tdd_IsPresent() const;
    private:
        bool CellsTriggeredList_physCellIdUTRA_tdd_present;
        PhysCellIdUTRA_TDD CellsTriggeredList_physCellIdUTRA_tdd;


        // physCellIdGERAN
    public:
        class CellsTriggeredList_physCellIdGERAN
        {
        public:
            CellsTriggeredList_physCellIdGERAN() : carrierFreq_present{false}, physCellId_present{false} {};
        public:
            int Pack(std::vector<uint8_t> &bits);
            int Unpack(std::vector<uint8_t> bits);
            int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
            std::string ToString(uint32_t indent) const;
            std::string ToStringNoNewLines() const;

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

        };

        CellsTriggeredList_physCellIdGERAN CellsTriggeredList_physCellIdGERAN_value;

        // physCellIdCDMA2000
    public:
        PhysCellIdCDMA2000* CellsTriggeredList_physCellIdCDMA2000_Set();
        int CellsTriggeredList_physCellIdCDMA2000_Set(PhysCellIdCDMA2000 &value);
        const PhysCellIdCDMA2000& CellsTriggeredList_physCellIdCDMA2000_Get() const;
        std::string CellsTriggeredList_physCellIdCDMA2000_ToString(uint32_t indent) const;
        std::string CellsTriggeredList_physCellIdCDMA2000_ToStringNoNewLines() const;
        int CellsTriggeredList_physCellIdCDMA2000_Clear();
        bool CellsTriggeredList_physCellIdCDMA2000_IsPresent() const;
    private:
        bool CellsTriggeredList_physCellIdCDMA2000_present;
        PhysCellIdCDMA2000 CellsTriggeredList_physCellIdCDMA2000;

    };

public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::vector<CellsTriggeredList_> Value() const;
    int SetValue(std::vector<CellsTriggeredList_>);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;
private:
    std::vector<CellsTriggeredList_> internal_value;
    bool present;
};

#endif
