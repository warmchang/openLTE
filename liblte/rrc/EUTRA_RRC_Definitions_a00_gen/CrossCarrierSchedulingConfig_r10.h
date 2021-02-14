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

#ifndef __CrossCarrierSchedulingConfig_r10_H__
#define __CrossCarrierSchedulingConfig_r10_H__

#include "ServCellIndex_r10.h"

#include <array>
#include <cstdint>
#include <vector>

class CrossCarrierSchedulingConfig_r10
{
public:
    CrossCarrierSchedulingConfig_r10() : schedulingCellInfo_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // schedulingCellInfo
public:
    enum schedulingCellInfo_Enum {
        k_schedulingCellInfo_own = 0,
        k_schedulingCellInfo_other,
    };
    int schedulingCellInfo_Pack(std::vector<uint8_t> &bits);
    int schedulingCellInfo_Unpack(std::vector<uint8_t> bits);
    int schedulingCellInfo_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    schedulingCellInfo_Enum schedulingCellInfo_Choice() const;
    int schedulingCellInfo_SetChoice(schedulingCellInfo_Enum choice);
    std::string schedulingCellInfo_ChoiceToString(schedulingCellInfo_Enum value) const;
    uint64_t schedulingCellInfo_NumberOfChoices() const;
    std::string schedulingCellInfo_ToString(uint32_t indent) const;
    std::string schedulingCellInfo_ToStringNoNewLines() const;
    int schedulingCellInfo_Clear();
    bool schedulingCellInfo_IsPresent() const;
private:
    bool schedulingCellInfo_present;
    schedulingCellInfo_Enum schedulingCellInfo_internal_choice;

    // own
public:
    class schedulingCellInfo_own
    {
    public:
        schedulingCellInfo_own() : cif_Presence_present{false} {};
    public:
        int Pack(std::vector<uint8_t> &bits);
        int Unpack(std::vector<uint8_t> bits);
        int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        std::string ToString(uint32_t indent) const;
        std::string ToStringNoNewLines() const;

        // cif-Presence
    public:
        int cif_Presence_Pack(std::vector<uint8_t> &bits);
        int cif_Presence_Unpack(std::vector<uint8_t> bits);
        int cif_Presence_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        bool cif_Presence_Value() const;
        int cif_Presence_SetValue(bool value);
        std::string cif_Presence_ToString(uint32_t indent) const;
        std::string cif_Presence_ToStringNoNewLines() const;
        int cif_Presence_Clear();
        bool cif_Presence_IsPresent() const;
    private:
        bool cif_Presence_present;
        bool cif_Presence_internal_value;

    };

    schedulingCellInfo_own schedulingCellInfo_own_value;

    // other
public:
    class schedulingCellInfo_other
    {
    public:
        schedulingCellInfo_other() : schedulingCellId_r10_present{false}, pdsch_Start_r10_present{false} {};
    public:
        int Pack(std::vector<uint8_t> &bits);
        int Unpack(std::vector<uint8_t> bits);
        int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        std::string ToString(uint32_t indent) const;
        std::string ToStringNoNewLines() const;

        // schedulingCellId-r10
    public:
        ServCellIndex_r10* schedulingCellId_r10_Set();
        int schedulingCellId_r10_Set(ServCellIndex_r10 &value);
        const ServCellIndex_r10& schedulingCellId_r10_Get() const;
        std::string schedulingCellId_r10_ToString(uint32_t indent) const;
        std::string schedulingCellId_r10_ToStringNoNewLines() const;
        int schedulingCellId_r10_Clear();
        bool schedulingCellId_r10_IsPresent() const;
    private:
        bool schedulingCellId_r10_present;
        ServCellIndex_r10 schedulingCellId_r10;

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

    };

    schedulingCellInfo_other schedulingCellInfo_other_value;


};

#endif
