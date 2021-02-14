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

#ifndef __MBMS_NotificationConfig_r9_H__
#define __MBMS_NotificationConfig_r9_H__

#include <array>
#include <cstdint>
#include <vector>

class MBMS_NotificationConfig_r9
{
public:
    MBMS_NotificationConfig_r9() : notificationRepetitionCoeff_r9_present{false}, notificationOffset_r9_present{false}, notificationSF_Index_r9_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // notificationRepetitionCoeff-r9
public:
    enum notificationRepetitionCoeff_r9_Enum {
        k_notificationRepetitionCoeff_r9_n2 = 0,
        k_notificationRepetitionCoeff_r9_n4,
    };
    int notificationRepetitionCoeff_r9_Pack(std::vector<uint8_t> &bits);
    int notificationRepetitionCoeff_r9_Unpack(std::vector<uint8_t> bits);
    int notificationRepetitionCoeff_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    notificationRepetitionCoeff_r9_Enum notificationRepetitionCoeff_r9_Value() const;
    int notificationRepetitionCoeff_r9_SetValue(notificationRepetitionCoeff_r9_Enum value);
    int notificationRepetitionCoeff_r9_SetValue(std::string value);
    std::string notificationRepetitionCoeff_r9_ValueToString(notificationRepetitionCoeff_r9_Enum value) const;
    uint64_t notificationRepetitionCoeff_r9_NumberOfValues() const;
    std::string notificationRepetitionCoeff_r9_ToString(uint32_t indent) const;
    std::string notificationRepetitionCoeff_r9_ToStringNoNewLines() const;
    int notificationRepetitionCoeff_r9_Clear();
    bool notificationRepetitionCoeff_r9_IsPresent() const;
private:
    bool notificationRepetitionCoeff_r9_present;
    notificationRepetitionCoeff_r9_Enum notificationRepetitionCoeff_r9_internal_value;

    // notificationOffset-r9
public:
    int notificationOffset_r9_Pack(std::vector<uint8_t> &bits);
    int notificationOffset_r9_Unpack(std::vector<uint8_t> bits);
    int notificationOffset_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t notificationOffset_r9_Value() const;
    int notificationOffset_r9_SetValue(int64_t value);
    std::string notificationOffset_r9_ToString(uint32_t indent) const;
    std::string notificationOffset_r9_ToStringNoNewLines() const;
    int notificationOffset_r9_Clear();
    bool notificationOffset_r9_IsPresent() const;
private:
    bool notificationOffset_r9_present;
    int64_t notificationOffset_r9_internal_value;

    // notificationSF-Index-r9
public:
    int notificationSF_Index_r9_Pack(std::vector<uint8_t> &bits);
    int notificationSF_Index_r9_Unpack(std::vector<uint8_t> bits);
    int notificationSF_Index_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t notificationSF_Index_r9_Value() const;
    int notificationSF_Index_r9_SetValue(int64_t value);
    std::string notificationSF_Index_r9_ToString(uint32_t indent) const;
    std::string notificationSF_Index_r9_ToStringNoNewLines() const;
    int notificationSF_Index_r9_Clear();
    bool notificationSF_Index_r9_IsPresent() const;
private:
    bool notificationSF_Index_r9_present;
    int64_t notificationSF_Index_r9_internal_value;

};

#endif
