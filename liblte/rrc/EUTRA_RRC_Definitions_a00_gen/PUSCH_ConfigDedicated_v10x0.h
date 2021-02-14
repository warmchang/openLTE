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

#ifndef __PUSCH_ConfigDedicated_v10x0_H__
#define __PUSCH_ConfigDedicated_v10x0_H__

#include <array>
#include <cstdint>
#include <vector>

class PUSCH_ConfigDedicated_v10x0
{
public:
    PUSCH_ConfigDedicated_v10x0() : betaOffset_ACK_Index_MC_r10_present{false}, betaOffset_RI_Index_MC_r10_present{false}, betaOffset_CQI_Index_MC_r10_present{false}, groupHoppingDisabled_r10_present{false}, dmrs_WithOCC_Activated_r10_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // betaOffset-ACK-Index-MC-r10
public:
    int betaOffset_ACK_Index_MC_r10_Pack(std::vector<uint8_t> &bits);
    int betaOffset_ACK_Index_MC_r10_Unpack(std::vector<uint8_t> bits);
    int betaOffset_ACK_Index_MC_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t betaOffset_ACK_Index_MC_r10_Value() const;
    int betaOffset_ACK_Index_MC_r10_SetValue(int64_t value);
    std::string betaOffset_ACK_Index_MC_r10_ToString(uint32_t indent) const;
    std::string betaOffset_ACK_Index_MC_r10_ToStringNoNewLines() const;
    int betaOffset_ACK_Index_MC_r10_Clear();
    bool betaOffset_ACK_Index_MC_r10_IsPresent() const;
private:
    bool betaOffset_ACK_Index_MC_r10_present;
    int64_t betaOffset_ACK_Index_MC_r10_internal_value;

    // betaOffset-RI-Index-MC-r10
public:
    int betaOffset_RI_Index_MC_r10_Pack(std::vector<uint8_t> &bits);
    int betaOffset_RI_Index_MC_r10_Unpack(std::vector<uint8_t> bits);
    int betaOffset_RI_Index_MC_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t betaOffset_RI_Index_MC_r10_Value() const;
    int betaOffset_RI_Index_MC_r10_SetValue(int64_t value);
    std::string betaOffset_RI_Index_MC_r10_ToString(uint32_t indent) const;
    std::string betaOffset_RI_Index_MC_r10_ToStringNoNewLines() const;
    int betaOffset_RI_Index_MC_r10_Clear();
    bool betaOffset_RI_Index_MC_r10_IsPresent() const;
private:
    bool betaOffset_RI_Index_MC_r10_present;
    int64_t betaOffset_RI_Index_MC_r10_internal_value;

    // betaOffset-CQI-Index-MC-r10
public:
    int betaOffset_CQI_Index_MC_r10_Pack(std::vector<uint8_t> &bits);
    int betaOffset_CQI_Index_MC_r10_Unpack(std::vector<uint8_t> bits);
    int betaOffset_CQI_Index_MC_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t betaOffset_CQI_Index_MC_r10_Value() const;
    int betaOffset_CQI_Index_MC_r10_SetValue(int64_t value);
    std::string betaOffset_CQI_Index_MC_r10_ToString(uint32_t indent) const;
    std::string betaOffset_CQI_Index_MC_r10_ToStringNoNewLines() const;
    int betaOffset_CQI_Index_MC_r10_Clear();
    bool betaOffset_CQI_Index_MC_r10_IsPresent() const;
private:
    bool betaOffset_CQI_Index_MC_r10_present;
    int64_t betaOffset_CQI_Index_MC_r10_internal_value;

    // groupHoppingDisabled-r10
public:
    enum groupHoppingDisabled_r10_Enum {
        k_groupHoppingDisabled_r10_true = 0,
    };
    int groupHoppingDisabled_r10_Pack(std::vector<uint8_t> &bits);
    int groupHoppingDisabled_r10_Unpack(std::vector<uint8_t> bits);
    int groupHoppingDisabled_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    groupHoppingDisabled_r10_Enum groupHoppingDisabled_r10_Value() const;
    int groupHoppingDisabled_r10_SetValue(groupHoppingDisabled_r10_Enum value);
    int groupHoppingDisabled_r10_SetValue(std::string value);
    std::string groupHoppingDisabled_r10_ValueToString(groupHoppingDisabled_r10_Enum value) const;
    uint64_t groupHoppingDisabled_r10_NumberOfValues() const;
    std::string groupHoppingDisabled_r10_ToString(uint32_t indent) const;
    std::string groupHoppingDisabled_r10_ToStringNoNewLines() const;
    int groupHoppingDisabled_r10_Clear();
    bool groupHoppingDisabled_r10_IsPresent() const;
private:
    bool groupHoppingDisabled_r10_present;
    groupHoppingDisabled_r10_Enum groupHoppingDisabled_r10_internal_value;

    // dmrs-WithOCC-Activated-r10
public:
    enum dmrs_WithOCC_Activated_r10_Enum {
        k_dmrs_WithOCC_Activated_r10_true = 0,
    };
    int dmrs_WithOCC_Activated_r10_Pack(std::vector<uint8_t> &bits);
    int dmrs_WithOCC_Activated_r10_Unpack(std::vector<uint8_t> bits);
    int dmrs_WithOCC_Activated_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    dmrs_WithOCC_Activated_r10_Enum dmrs_WithOCC_Activated_r10_Value() const;
    int dmrs_WithOCC_Activated_r10_SetValue(dmrs_WithOCC_Activated_r10_Enum value);
    int dmrs_WithOCC_Activated_r10_SetValue(std::string value);
    std::string dmrs_WithOCC_Activated_r10_ValueToString(dmrs_WithOCC_Activated_r10_Enum value) const;
    uint64_t dmrs_WithOCC_Activated_r10_NumberOfValues() const;
    std::string dmrs_WithOCC_Activated_r10_ToString(uint32_t indent) const;
    std::string dmrs_WithOCC_Activated_r10_ToStringNoNewLines() const;
    int dmrs_WithOCC_Activated_r10_Clear();
    bool dmrs_WithOCC_Activated_r10_IsPresent() const;
private:
    bool dmrs_WithOCC_Activated_r10_present;
    dmrs_WithOCC_Activated_r10_Enum dmrs_WithOCC_Activated_r10_internal_value;

};

#endif
