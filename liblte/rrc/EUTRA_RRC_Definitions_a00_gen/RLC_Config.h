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

#ifndef __RLC_Config_H__
#define __RLC_Config_H__

#include "UL_AM_RLC.h"
#include "DL_AM_RLC.h"
#include "UL_UM_RLC.h"
#include "DL_UM_RLC.h"
#include "UL_UM_RLC.h"
#include "DL_UM_RLC.h"

#include <array>
#include <cstdint>
#include <vector>

class RLC_Config
{
public:
    enum Enum {
        k_am = 0,
        k_um_Bi_Directional,
        k_um_Uni_Directional_UL,
        k_um_Uni_Directional_DL,
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

    // am
public:
    class am
    {
    public:
        am() : ul_AM_RLC_present{false}, dl_AM_RLC_present{false} {};
    public:
        int Pack(std::vector<uint8_t> &bits);
        int Unpack(std::vector<uint8_t> bits);
        int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        std::string ToString(uint32_t indent) const;
        std::string ToStringNoNewLines() const;

        // ul-AM-RLC
    public:
        UL_AM_RLC* ul_AM_RLC_Set();
        int ul_AM_RLC_Set(UL_AM_RLC &value);
        const UL_AM_RLC& ul_AM_RLC_Get() const;
        std::string ul_AM_RLC_ToString(uint32_t indent) const;
        std::string ul_AM_RLC_ToStringNoNewLines() const;
        int ul_AM_RLC_Clear();
        bool ul_AM_RLC_IsPresent() const;
    private:
        bool ul_AM_RLC_present;
        UL_AM_RLC ul_AM_RLC;

        // dl-AM-RLC
    public:
        DL_AM_RLC* dl_AM_RLC_Set();
        int dl_AM_RLC_Set(DL_AM_RLC &value);
        const DL_AM_RLC& dl_AM_RLC_Get() const;
        std::string dl_AM_RLC_ToString(uint32_t indent) const;
        std::string dl_AM_RLC_ToStringNoNewLines() const;
        int dl_AM_RLC_Clear();
        bool dl_AM_RLC_IsPresent() const;
    private:
        bool dl_AM_RLC_present;
        DL_AM_RLC dl_AM_RLC;

    };

    am am_value;

    // um-Bi-Directional
public:
    class um_Bi_Directional
    {
    public:
        um_Bi_Directional() : ul_UM_RLC_present{false}, dl_UM_RLC_present{false} {};
    public:
        int Pack(std::vector<uint8_t> &bits);
        int Unpack(std::vector<uint8_t> bits);
        int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        std::string ToString(uint32_t indent) const;
        std::string ToStringNoNewLines() const;

        // ul-UM-RLC
    public:
        UL_UM_RLC* ul_UM_RLC_Set();
        int ul_UM_RLC_Set(UL_UM_RLC &value);
        const UL_UM_RLC& ul_UM_RLC_Get() const;
        std::string ul_UM_RLC_ToString(uint32_t indent) const;
        std::string ul_UM_RLC_ToStringNoNewLines() const;
        int ul_UM_RLC_Clear();
        bool ul_UM_RLC_IsPresent() const;
    private:
        bool ul_UM_RLC_present;
        UL_UM_RLC ul_UM_RLC;

        // dl-UM-RLC
    public:
        DL_UM_RLC* dl_UM_RLC_Set();
        int dl_UM_RLC_Set(DL_UM_RLC &value);
        const DL_UM_RLC& dl_UM_RLC_Get() const;
        std::string dl_UM_RLC_ToString(uint32_t indent) const;
        std::string dl_UM_RLC_ToStringNoNewLines() const;
        int dl_UM_RLC_Clear();
        bool dl_UM_RLC_IsPresent() const;
    private:
        bool dl_UM_RLC_present;
        DL_UM_RLC dl_UM_RLC;

    };

    um_Bi_Directional um_Bi_Directional_value;

    // um-Uni-Directional-UL
public:
    class um_Uni_Directional_UL
    {
    public:
        um_Uni_Directional_UL() : ul_UM_RLC_present{false} {};
    public:
        int Pack(std::vector<uint8_t> &bits);
        int Unpack(std::vector<uint8_t> bits);
        int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        std::string ToString(uint32_t indent) const;
        std::string ToStringNoNewLines() const;

        // ul-UM-RLC
    public:
        UL_UM_RLC* ul_UM_RLC_Set();
        int ul_UM_RLC_Set(UL_UM_RLC &value);
        const UL_UM_RLC& ul_UM_RLC_Get() const;
        std::string ul_UM_RLC_ToString(uint32_t indent) const;
        std::string ul_UM_RLC_ToStringNoNewLines() const;
        int ul_UM_RLC_Clear();
        bool ul_UM_RLC_IsPresent() const;
    private:
        bool ul_UM_RLC_present;
        UL_UM_RLC ul_UM_RLC;

    };

    um_Uni_Directional_UL um_Uni_Directional_UL_value;

    // um-Uni-Directional-DL
public:
    class um_Uni_Directional_DL
    {
    public:
        um_Uni_Directional_DL() : dl_UM_RLC_present{false} {};
    public:
        int Pack(std::vector<uint8_t> &bits);
        int Unpack(std::vector<uint8_t> bits);
        int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        std::string ToString(uint32_t indent) const;
        std::string ToStringNoNewLines() const;

        // dl-UM-RLC
    public:
        DL_UM_RLC* dl_UM_RLC_Set();
        int dl_UM_RLC_Set(DL_UM_RLC &value);
        const DL_UM_RLC& dl_UM_RLC_Get() const;
        std::string dl_UM_RLC_ToString(uint32_t indent) const;
        std::string dl_UM_RLC_ToStringNoNewLines() const;
        int dl_UM_RLC_Clear();
        bool dl_UM_RLC_IsPresent() const;
    private:
        bool dl_UM_RLC_present;
        DL_UM_RLC dl_UM_RLC;

    };

    um_Uni_Directional_DL um_Uni_Directional_DL_value;

};

#endif
