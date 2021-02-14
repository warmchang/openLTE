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

#ifndef __TMGI_r9_H__
#define __TMGI_r9_H__

#include "PLMN_Identity.h"

#include <array>
#include <cstdint>
#include <vector>

class TMGI_r9
{
public:
    TMGI_r9() : plmn_Id_r9_present{false}, serviceId_r9_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // plmn-Id-r9
public:
    enum plmn_Id_r9_Enum {
        k_plmn_Id_r9_plmn_Index_r9 = 0,
        k_plmn_Id_r9_explicitValue_r9,
    };
    int plmn_Id_r9_Pack(std::vector<uint8_t> &bits);
    int plmn_Id_r9_Unpack(std::vector<uint8_t> bits);
    int plmn_Id_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    plmn_Id_r9_Enum plmn_Id_r9_Choice() const;
    int plmn_Id_r9_SetChoice(plmn_Id_r9_Enum choice);
    std::string plmn_Id_r9_ChoiceToString(plmn_Id_r9_Enum value) const;
    uint64_t plmn_Id_r9_NumberOfChoices() const;
    std::string plmn_Id_r9_ToString(uint32_t indent) const;
    std::string plmn_Id_r9_ToStringNoNewLines() const;
    int plmn_Id_r9_Clear();
    bool plmn_Id_r9_IsPresent() const;
private:
    bool plmn_Id_r9_present;
    plmn_Id_r9_Enum plmn_Id_r9_internal_choice;

    // plmn-Index-r9
public:
    int plmn_Id_r9_plmn_Index_r9_Pack(std::vector<uint8_t> &bits);
    int plmn_Id_r9_plmn_Index_r9_Unpack(std::vector<uint8_t> bits);
    int plmn_Id_r9_plmn_Index_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t plmn_Id_r9_plmn_Index_r9_Value() const;
    int plmn_Id_r9_plmn_Index_r9_SetValue(int64_t value);
    std::string plmn_Id_r9_plmn_Index_r9_ToString(uint32_t indent) const;
    std::string plmn_Id_r9_plmn_Index_r9_ToStringNoNewLines() const;
    int plmn_Id_r9_plmn_Index_r9_Clear();
    bool plmn_Id_r9_plmn_Index_r9_IsPresent() const;
private:
    bool plmn_Id_r9_plmn_Index_r9_present;
    int64_t plmn_Id_r9_plmn_Index_r9_internal_value;

    // explicitValue-r9
public:
    PLMN_Identity* plmn_Id_r9_explicitValue_r9_Set();
    int plmn_Id_r9_explicitValue_r9_Set(PLMN_Identity &value);
    const PLMN_Identity& plmn_Id_r9_explicitValue_r9_Get() const;
    std::string plmn_Id_r9_explicitValue_r9_ToString(uint32_t indent) const;
    std::string plmn_Id_r9_explicitValue_r9_ToStringNoNewLines() const;
    int plmn_Id_r9_explicitValue_r9_Clear();
    bool plmn_Id_r9_explicitValue_r9_IsPresent() const;
private:
    bool plmn_Id_r9_explicitValue_r9_present;
    PLMN_Identity plmn_Id_r9_explicitValue_r9;


    // serviceId-r9
public:
    int serviceId_r9_Pack(std::vector<uint8_t> &bits);
    int serviceId_r9_Unpack(std::vector<uint8_t> bits);
    int serviceId_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::vector<uint8_t> serviceId_r9_Value() const;
    int serviceId_r9_SetValue(std::vector<uint8_t> value);
    std::string serviceId_r9_ToString(uint32_t indent) const;
    std::string serviceId_r9_ToStringNoNewLines() const;
    int serviceId_r9_Clear();
    bool serviceId_r9_IsPresent() const;
private:
    bool serviceId_r9_present;
    std::vector<uint8_t> serviceId_r9_internal_value;

};

#endif
