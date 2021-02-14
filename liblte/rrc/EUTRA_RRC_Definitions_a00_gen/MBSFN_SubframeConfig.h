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

#ifndef __MBSFN_SubframeConfig_H__
#define __MBSFN_SubframeConfig_H__

#include <array>
#include <cstdint>
#include <vector>

class MBSFN_SubframeConfig
{
public:
    MBSFN_SubframeConfig() : radioframeAllocationPeriod_present{false}, radioframeAllocationOffset_present{false}, subframeAllocation_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // radioframeAllocationPeriod
public:
    enum radioframeAllocationPeriod_Enum {
        k_radioframeAllocationPeriod_n1 = 0,
        k_radioframeAllocationPeriod_n2,
        k_radioframeAllocationPeriod_n4,
        k_radioframeAllocationPeriod_n8,
        k_radioframeAllocationPeriod_n16,
        k_radioframeAllocationPeriod_n32,
    };
    int radioframeAllocationPeriod_Pack(std::vector<uint8_t> &bits);
    int radioframeAllocationPeriod_Unpack(std::vector<uint8_t> bits);
    int radioframeAllocationPeriod_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    radioframeAllocationPeriod_Enum radioframeAllocationPeriod_Value() const;
    int radioframeAllocationPeriod_SetValue(radioframeAllocationPeriod_Enum value);
    int radioframeAllocationPeriod_SetValue(std::string value);
    std::string radioframeAllocationPeriod_ValueToString(radioframeAllocationPeriod_Enum value) const;
    uint64_t radioframeAllocationPeriod_NumberOfValues() const;
    std::string radioframeAllocationPeriod_ToString(uint32_t indent) const;
    std::string radioframeAllocationPeriod_ToStringNoNewLines() const;
    int radioframeAllocationPeriod_Clear();
    bool radioframeAllocationPeriod_IsPresent() const;
private:
    bool radioframeAllocationPeriod_present;
    radioframeAllocationPeriod_Enum radioframeAllocationPeriod_internal_value;

    // radioframeAllocationOffset
public:
    int radioframeAllocationOffset_Pack(std::vector<uint8_t> &bits);
    int radioframeAllocationOffset_Unpack(std::vector<uint8_t> bits);
    int radioframeAllocationOffset_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t radioframeAllocationOffset_Value() const;
    int radioframeAllocationOffset_SetValue(int64_t value);
    std::string radioframeAllocationOffset_ToString(uint32_t indent) const;
    std::string radioframeAllocationOffset_ToStringNoNewLines() const;
    int radioframeAllocationOffset_Clear();
    bool radioframeAllocationOffset_IsPresent() const;
private:
    bool radioframeAllocationOffset_present;
    int64_t radioframeAllocationOffset_internal_value;

    // subframeAllocation
public:
    enum subframeAllocation_Enum {
        k_subframeAllocation_oneFrame = 0,
        k_subframeAllocation_fourFrames,
    };
    int subframeAllocation_Pack(std::vector<uint8_t> &bits);
    int subframeAllocation_Unpack(std::vector<uint8_t> bits);
    int subframeAllocation_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    subframeAllocation_Enum subframeAllocation_Choice() const;
    int subframeAllocation_SetChoice(subframeAllocation_Enum choice);
    std::string subframeAllocation_ChoiceToString(subframeAllocation_Enum value) const;
    uint64_t subframeAllocation_NumberOfChoices() const;
    std::string subframeAllocation_ToString(uint32_t indent) const;
    std::string subframeAllocation_ToStringNoNewLines() const;
    int subframeAllocation_Clear();
    bool subframeAllocation_IsPresent() const;
private:
    bool subframeAllocation_present;
    subframeAllocation_Enum subframeAllocation_internal_choice;

    // oneFrame
public:
    int subframeAllocation_oneFrame_Pack(std::vector<uint8_t> &bits);
    int subframeAllocation_oneFrame_Unpack(std::vector<uint8_t> bits);
    int subframeAllocation_oneFrame_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    uint8_t subframeAllocation_oneFrame_Value() const;
    int subframeAllocation_oneFrame_SetValue(uint8_t value);
    std::string subframeAllocation_oneFrame_ToString(uint32_t indent) const;
    std::string subframeAllocation_oneFrame_ToStringNoNewLines() const;
    int subframeAllocation_oneFrame_Clear();
    bool subframeAllocation_oneFrame_IsPresent() const;
private:
    bool subframeAllocation_oneFrame_present;
    uint8_t subframeAllocation_oneFrame_internal_value;

    // fourFrames
public:
    int subframeAllocation_fourFrames_Pack(std::vector<uint8_t> &bits);
    int subframeAllocation_fourFrames_Unpack(std::vector<uint8_t> bits);
    int subframeAllocation_fourFrames_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    uint32_t subframeAllocation_fourFrames_Value() const;
    int subframeAllocation_fourFrames_SetValue(uint32_t value);
    std::string subframeAllocation_fourFrames_ToString(uint32_t indent) const;
    std::string subframeAllocation_fourFrames_ToStringNoNewLines() const;
    int subframeAllocation_fourFrames_Clear();
    bool subframeAllocation_fourFrames_IsPresent() const;
private:
    bool subframeAllocation_fourFrames_present;
    uint32_t subframeAllocation_fourFrames_internal_value;


};

#endif
