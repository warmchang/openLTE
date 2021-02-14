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

#ifndef __LogicalChannelConfig_H__
#define __LogicalChannelConfig_H__

#include <array>
#include <cstdint>
#include <vector>

class LogicalChannelConfig
{
public:
    LogicalChannelConfig() : logicalChannelSR_Mask_r9_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // ul-SpecificParameters
public:
    class ul_SpecificParameters
    {
    public:
        ul_SpecificParameters() : present{false}, priority_present{false}, prioritisedBitRate_present{false}, bucketSizeDuration_present{false}, logicalChannelGroup_present{false} {};
    public:
        int Pack(std::vector<uint8_t> &bits);
        int Unpack(std::vector<uint8_t> bits);
        int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        std::string ToString(uint32_t indent) const;
        std::string ToStringNoNewLines() const;
        int Set();
        int SetPresence(bool is_present);
        int Clear();
        bool IsPresent() const;
    private:
        bool present;

        // priority
    public:
        int priority_Pack(std::vector<uint8_t> &bits);
        int priority_Unpack(std::vector<uint8_t> bits);
        int priority_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        int64_t priority_Value() const;
        int priority_SetValue(int64_t value);
        std::string priority_ToString(uint32_t indent) const;
        std::string priority_ToStringNoNewLines() const;
        int priority_Clear();
        bool priority_IsPresent() const;
    private:
        bool priority_present;
        int64_t priority_internal_value;

        // prioritisedBitRate
    public:
        enum prioritisedBitRate_Enum {
            k_prioritisedBitRate_kBps0 = 0,
            k_prioritisedBitRate_kBps8,
            k_prioritisedBitRate_kBps16,
            k_prioritisedBitRate_kBps32,
            k_prioritisedBitRate_kBps64,
            k_prioritisedBitRate_kBps128,
            k_prioritisedBitRate_kBps256,
            k_prioritisedBitRate_infinity,
            k_prioritisedBitRate_spare8,
            k_prioritisedBitRate_spare7,
            k_prioritisedBitRate_spare6,
            k_prioritisedBitRate_spare5,
            k_prioritisedBitRate_spare4,
            k_prioritisedBitRate_spare3,
            k_prioritisedBitRate_spare2,
            k_prioritisedBitRate_spare1,
        };
        int prioritisedBitRate_Pack(std::vector<uint8_t> &bits);
        int prioritisedBitRate_Unpack(std::vector<uint8_t> bits);
        int prioritisedBitRate_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        prioritisedBitRate_Enum prioritisedBitRate_Value() const;
        int prioritisedBitRate_SetValue(prioritisedBitRate_Enum value);
        int prioritisedBitRate_SetValue(std::string value);
        std::string prioritisedBitRate_ValueToString(prioritisedBitRate_Enum value) const;
        uint64_t prioritisedBitRate_NumberOfValues() const;
        std::string prioritisedBitRate_ToString(uint32_t indent) const;
        std::string prioritisedBitRate_ToStringNoNewLines() const;
        int prioritisedBitRate_Clear();
        bool prioritisedBitRate_IsPresent() const;
    private:
        bool prioritisedBitRate_present;
        prioritisedBitRate_Enum prioritisedBitRate_internal_value;

        // bucketSizeDuration
    public:
        enum bucketSizeDuration_Enum {
            k_bucketSizeDuration_ms50 = 0,
            k_bucketSizeDuration_ms100,
            k_bucketSizeDuration_ms150,
            k_bucketSizeDuration_ms300,
            k_bucketSizeDuration_ms500,
            k_bucketSizeDuration_ms1000,
            k_bucketSizeDuration_spare2,
            k_bucketSizeDuration_spare1,
        };
        int bucketSizeDuration_Pack(std::vector<uint8_t> &bits);
        int bucketSizeDuration_Unpack(std::vector<uint8_t> bits);
        int bucketSizeDuration_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        bucketSizeDuration_Enum bucketSizeDuration_Value() const;
        int bucketSizeDuration_SetValue(bucketSizeDuration_Enum value);
        int bucketSizeDuration_SetValue(std::string value);
        std::string bucketSizeDuration_ValueToString(bucketSizeDuration_Enum value) const;
        uint64_t bucketSizeDuration_NumberOfValues() const;
        std::string bucketSizeDuration_ToString(uint32_t indent) const;
        std::string bucketSizeDuration_ToStringNoNewLines() const;
        int bucketSizeDuration_Clear();
        bool bucketSizeDuration_IsPresent() const;
    private:
        bool bucketSizeDuration_present;
        bucketSizeDuration_Enum bucketSizeDuration_internal_value;

        // logicalChannelGroup
    public:
        int logicalChannelGroup_Pack(std::vector<uint8_t> &bits);
        int logicalChannelGroup_Unpack(std::vector<uint8_t> bits);
        int logicalChannelGroup_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        int64_t logicalChannelGroup_Value() const;
        int logicalChannelGroup_SetValue(int64_t value);
        std::string logicalChannelGroup_ToString(uint32_t indent) const;
        std::string logicalChannelGroup_ToStringNoNewLines() const;
        int logicalChannelGroup_Clear();
        bool logicalChannelGroup_IsPresent() const;
    private:
        bool logicalChannelGroup_present;
        int64_t logicalChannelGroup_internal_value;

    };

    ul_SpecificParameters ul_SpecificParameters_value;

    // logicalChannelSR-Mask-r9
public:
    enum logicalChannelSR_Mask_r9_Enum {
        k_logicalChannelSR_Mask_r9_setup = 0,
    };
    int logicalChannelSR_Mask_r9_Pack(std::vector<uint8_t> &bits);
    int logicalChannelSR_Mask_r9_Unpack(std::vector<uint8_t> bits);
    int logicalChannelSR_Mask_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    logicalChannelSR_Mask_r9_Enum logicalChannelSR_Mask_r9_Value() const;
    int logicalChannelSR_Mask_r9_SetValue(logicalChannelSR_Mask_r9_Enum value);
    int logicalChannelSR_Mask_r9_SetValue(std::string value);
    std::string logicalChannelSR_Mask_r9_ValueToString(logicalChannelSR_Mask_r9_Enum value) const;
    uint64_t logicalChannelSR_Mask_r9_NumberOfValues() const;
    std::string logicalChannelSR_Mask_r9_ToString(uint32_t indent) const;
    std::string logicalChannelSR_Mask_r9_ToStringNoNewLines() const;
    int logicalChannelSR_Mask_r9_Clear();
    bool logicalChannelSR_Mask_r9_IsPresent() const;
private:
    bool logicalChannelSR_Mask_r9_present;
    logicalChannelSR_Mask_r9_Enum logicalChannelSR_Mask_r9_internal_value;

};

#endif
