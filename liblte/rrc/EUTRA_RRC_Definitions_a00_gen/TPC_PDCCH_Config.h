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

#ifndef __TPC_PDCCH_Config_H__
#define __TPC_PDCCH_Config_H__

#include "TPC_Index.h"

#include <array>
#include <cstdint>
#include <vector>

class TPC_PDCCH_Config
{
public:
    enum Enum {
        k_release = 0,
        k_setup,
    };
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    Enum Choice() const;
    int SetChoice(Enum choice);
    std::string ChoiceToString(Enum value) const;
    uint64_t NumberOfChoices() const;
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;
    int Clear();
    bool IsPresent() const;
private:
    bool present;
    Enum internal_choice;

    // release
public:
    int release_Pack(std::vector<uint8_t> &bits) {return 0;};
    int release_Unpack(std::vector<uint8_t> bits) {return 0;};
    int release_Unpack(std::vector<uint8_t> bits, uint32_t &idx) {return 0;};
    bool release_IsPresent() const {return true;};
    std::string release_ToString(uint32_t indent) {return "";};
    std::string release_ToStringNoNewLines() {return "";};

    // setup
public:
    class setup
    {
    public:
        setup() : tpc_RNTI_present{false}, tpc_Index_present{false} {};
    public:
        int Pack(std::vector<uint8_t> &bits);
        int Unpack(std::vector<uint8_t> bits);
        int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        std::string ToString(uint32_t indent) const;
        std::string ToStringNoNewLines() const;

        // tpc-RNTI
    public:
        int tpc_RNTI_Pack(std::vector<uint8_t> &bits);
        int tpc_RNTI_Unpack(std::vector<uint8_t> bits);
        int tpc_RNTI_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        uint16_t tpc_RNTI_Value() const;
        int tpc_RNTI_SetValue(uint16_t value);
        std::string tpc_RNTI_ToString(uint32_t indent) const;
        std::string tpc_RNTI_ToStringNoNewLines() const;
        int tpc_RNTI_Clear();
        bool tpc_RNTI_IsPresent() const;
    private:
        bool tpc_RNTI_present;
        uint16_t tpc_RNTI_internal_value;

        // tpc-Index
    public:
        TPC_Index* tpc_Index_Set();
        int tpc_Index_Set(TPC_Index &value);
        const TPC_Index& tpc_Index_Get() const;
        std::string tpc_Index_ToString(uint32_t indent) const;
        std::string tpc_Index_ToStringNoNewLines() const;
        int tpc_Index_Clear();
        bool tpc_Index_IsPresent() const;
    private:
        bool tpc_Index_present;
        TPC_Index tpc_Index;

    };

    setup setup_value;

};

#endif
