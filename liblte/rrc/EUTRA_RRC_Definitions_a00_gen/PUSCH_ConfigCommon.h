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

#ifndef __PUSCH_ConfigCommon_H__
#define __PUSCH_ConfigCommon_H__

#include "UL_ReferenceSignalsPUSCH.h"

#include <array>
#include <cstdint>
#include <vector>

class PUSCH_ConfigCommon
{
public:
    PUSCH_ConfigCommon() : ul_ReferenceSignalsPUSCH_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // pusch-ConfigBasic
public:
    class pusch_ConfigBasic
    {
    public:
        pusch_ConfigBasic() : n_SB_present{false}, hoppingMode_present{false}, pusch_HoppingOffset_present{false}, enable64QAM_present{false} {};
    public:
        int Pack(std::vector<uint8_t> &bits);
        int Unpack(std::vector<uint8_t> bits);
        int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        std::string ToString(uint32_t indent) const;
        std::string ToStringNoNewLines() const;

        // n-SB
    public:
        int n_SB_Pack(std::vector<uint8_t> &bits);
        int n_SB_Unpack(std::vector<uint8_t> bits);
        int n_SB_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        int64_t n_SB_Value() const;
        int n_SB_SetValue(int64_t value);
        std::string n_SB_ToString(uint32_t indent) const;
        std::string n_SB_ToStringNoNewLines() const;
        int n_SB_Clear();
        bool n_SB_IsPresent() const;
    private:
        bool n_SB_present;
        int64_t n_SB_internal_value;

        // hoppingMode
    public:
        enum hoppingMode_Enum {
            k_hoppingMode_interSubFrame = 0,
            k_hoppingMode_intraAndInterSubFrame,
        };
        int hoppingMode_Pack(std::vector<uint8_t> &bits);
        int hoppingMode_Unpack(std::vector<uint8_t> bits);
        int hoppingMode_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        hoppingMode_Enum hoppingMode_Value() const;
        int hoppingMode_SetValue(hoppingMode_Enum value);
        int hoppingMode_SetValue(std::string value);
        std::string hoppingMode_ValueToString(hoppingMode_Enum value) const;
        uint64_t hoppingMode_NumberOfValues() const;
        std::string hoppingMode_ToString(uint32_t indent) const;
        std::string hoppingMode_ToStringNoNewLines() const;
        int hoppingMode_Clear();
        bool hoppingMode_IsPresent() const;
    private:
        bool hoppingMode_present;
        hoppingMode_Enum hoppingMode_internal_value;

        // pusch-HoppingOffset
    public:
        int pusch_HoppingOffset_Pack(std::vector<uint8_t> &bits);
        int pusch_HoppingOffset_Unpack(std::vector<uint8_t> bits);
        int pusch_HoppingOffset_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        int64_t pusch_HoppingOffset_Value() const;
        int pusch_HoppingOffset_SetValue(int64_t value);
        std::string pusch_HoppingOffset_ToString(uint32_t indent) const;
        std::string pusch_HoppingOffset_ToStringNoNewLines() const;
        int pusch_HoppingOffset_Clear();
        bool pusch_HoppingOffset_IsPresent() const;
    private:
        bool pusch_HoppingOffset_present;
        int64_t pusch_HoppingOffset_internal_value;

        // enable64QAM
    public:
        int enable64QAM_Pack(std::vector<uint8_t> &bits);
        int enable64QAM_Unpack(std::vector<uint8_t> bits);
        int enable64QAM_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        bool enable64QAM_Value() const;
        int enable64QAM_SetValue(bool value);
        std::string enable64QAM_ToString(uint32_t indent) const;
        std::string enable64QAM_ToStringNoNewLines() const;
        int enable64QAM_Clear();
        bool enable64QAM_IsPresent() const;
    private:
        bool enable64QAM_present;
        bool enable64QAM_internal_value;

    };

    pusch_ConfigBasic pusch_ConfigBasic_value;

    // ul-ReferenceSignalsPUSCH
public:
    UL_ReferenceSignalsPUSCH* ul_ReferenceSignalsPUSCH_Set();
    int ul_ReferenceSignalsPUSCH_Set(UL_ReferenceSignalsPUSCH &value);
    const UL_ReferenceSignalsPUSCH& ul_ReferenceSignalsPUSCH_Get() const;
    std::string ul_ReferenceSignalsPUSCH_ToString(uint32_t indent) const;
    std::string ul_ReferenceSignalsPUSCH_ToStringNoNewLines() const;
    int ul_ReferenceSignalsPUSCH_Clear();
    bool ul_ReferenceSignalsPUSCH_IsPresent() const;
private:
    bool ul_ReferenceSignalsPUSCH_present;
    UL_ReferenceSignalsPUSCH ul_ReferenceSignalsPUSCH;

};

#endif
