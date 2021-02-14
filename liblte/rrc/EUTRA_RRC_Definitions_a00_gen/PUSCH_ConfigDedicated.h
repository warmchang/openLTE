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

#ifndef __PUSCH_ConfigDedicated_H__
#define __PUSCH_ConfigDedicated_H__

#include <array>
#include <cstdint>
#include <vector>

class PUSCH_ConfigDedicated
{
public:
    PUSCH_ConfigDedicated() : betaOffset_ACK_Index_present{false}, betaOffset_RI_Index_present{false}, betaOffset_CQI_Index_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // betaOffset-ACK-Index
public:
    int betaOffset_ACK_Index_Pack(std::vector<uint8_t> &bits);
    int betaOffset_ACK_Index_Unpack(std::vector<uint8_t> bits);
    int betaOffset_ACK_Index_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t betaOffset_ACK_Index_Value() const;
    int betaOffset_ACK_Index_SetValue(int64_t value);
    std::string betaOffset_ACK_Index_ToString(uint32_t indent) const;
    std::string betaOffset_ACK_Index_ToStringNoNewLines() const;
    int betaOffset_ACK_Index_Clear();
    bool betaOffset_ACK_Index_IsPresent() const;
private:
    bool betaOffset_ACK_Index_present;
    int64_t betaOffset_ACK_Index_internal_value;

    // betaOffset-RI-Index
public:
    int betaOffset_RI_Index_Pack(std::vector<uint8_t> &bits);
    int betaOffset_RI_Index_Unpack(std::vector<uint8_t> bits);
    int betaOffset_RI_Index_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t betaOffset_RI_Index_Value() const;
    int betaOffset_RI_Index_SetValue(int64_t value);
    std::string betaOffset_RI_Index_ToString(uint32_t indent) const;
    std::string betaOffset_RI_Index_ToStringNoNewLines() const;
    int betaOffset_RI_Index_Clear();
    bool betaOffset_RI_Index_IsPresent() const;
private:
    bool betaOffset_RI_Index_present;
    int64_t betaOffset_RI_Index_internal_value;

    // betaOffset-CQI-Index
public:
    int betaOffset_CQI_Index_Pack(std::vector<uint8_t> &bits);
    int betaOffset_CQI_Index_Unpack(std::vector<uint8_t> bits);
    int betaOffset_CQI_Index_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t betaOffset_CQI_Index_Value() const;
    int betaOffset_CQI_Index_SetValue(int64_t value);
    std::string betaOffset_CQI_Index_ToString(uint32_t indent) const;
    std::string betaOffset_CQI_Index_ToStringNoNewLines() const;
    int betaOffset_CQI_Index_Clear();
    bool betaOffset_CQI_Index_IsPresent() const;
private:
    bool betaOffset_CQI_Index_present;
    int64_t betaOffset_CQI_Index_internal_value;

};

#endif
