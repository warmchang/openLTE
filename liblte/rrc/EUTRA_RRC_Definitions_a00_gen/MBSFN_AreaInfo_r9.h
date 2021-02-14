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

#ifndef __MBSFN_AreaInfo_r9_H__
#define __MBSFN_AreaInfo_r9_H__

#include <array>
#include <cstdint>
#include <vector>

class MBSFN_AreaInfo_r9
{
public:
    MBSFN_AreaInfo_r9() : mbsfn_AreaId_r9_present{false}, non_MBSFNregionLength_present{false}, notificationIndicator_r9_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // mbsfn-AreaId-r9
public:
    int mbsfn_AreaId_r9_Pack(std::vector<uint8_t> &bits);
    int mbsfn_AreaId_r9_Unpack(std::vector<uint8_t> bits);
    int mbsfn_AreaId_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t mbsfn_AreaId_r9_Value() const;
    int mbsfn_AreaId_r9_SetValue(int64_t value);
    std::string mbsfn_AreaId_r9_ToString(uint32_t indent) const;
    std::string mbsfn_AreaId_r9_ToStringNoNewLines() const;
    int mbsfn_AreaId_r9_Clear();
    bool mbsfn_AreaId_r9_IsPresent() const;
private:
    bool mbsfn_AreaId_r9_present;
    int64_t mbsfn_AreaId_r9_internal_value;

    // non-MBSFNregionLength
public:
    enum non_MBSFNregionLength_Enum {
        k_non_MBSFNregionLength_s1 = 0,
        k_non_MBSFNregionLength_s2,
    };
    int non_MBSFNregionLength_Pack(std::vector<uint8_t> &bits);
    int non_MBSFNregionLength_Unpack(std::vector<uint8_t> bits);
    int non_MBSFNregionLength_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    non_MBSFNregionLength_Enum non_MBSFNregionLength_Value() const;
    int non_MBSFNregionLength_SetValue(non_MBSFNregionLength_Enum value);
    int non_MBSFNregionLength_SetValue(std::string value);
    std::string non_MBSFNregionLength_ValueToString(non_MBSFNregionLength_Enum value) const;
    uint64_t non_MBSFNregionLength_NumberOfValues() const;
    std::string non_MBSFNregionLength_ToString(uint32_t indent) const;
    std::string non_MBSFNregionLength_ToStringNoNewLines() const;
    int non_MBSFNregionLength_Clear();
    bool non_MBSFNregionLength_IsPresent() const;
private:
    bool non_MBSFNregionLength_present;
    non_MBSFNregionLength_Enum non_MBSFNregionLength_internal_value;

    // notificationIndicator-r9
public:
    int notificationIndicator_r9_Pack(std::vector<uint8_t> &bits);
    int notificationIndicator_r9_Unpack(std::vector<uint8_t> bits);
    int notificationIndicator_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t notificationIndicator_r9_Value() const;
    int notificationIndicator_r9_SetValue(int64_t value);
    std::string notificationIndicator_r9_ToString(uint32_t indent) const;
    std::string notificationIndicator_r9_ToStringNoNewLines() const;
    int notificationIndicator_r9_Clear();
    bool notificationIndicator_r9_IsPresent() const;
private:
    bool notificationIndicator_r9_present;
    int64_t notificationIndicator_r9_internal_value;

    // mcch-Config-r9
public:
    class mcch_Config_r9
    {
    public:
        mcch_Config_r9() : mcch_RepetitionPeriod_r9_present{false}, mcch_Offset_r9_present{false}, mcch_ModificationPeriod_r9_present{false}, sf_AllocInfo_r9_present{false}, signallingMCS_r9_present{false} {};
    public:
        int Pack(std::vector<uint8_t> &bits);
        int Unpack(std::vector<uint8_t> bits);
        int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        std::string ToString(uint32_t indent) const;
        std::string ToStringNoNewLines() const;

        // mcch-RepetitionPeriod-r9
    public:
        enum mcch_RepetitionPeriod_r9_Enum {
            k_mcch_RepetitionPeriod_r9_rf32 = 0,
            k_mcch_RepetitionPeriod_r9_rf64,
            k_mcch_RepetitionPeriod_r9_rf128,
            k_mcch_RepetitionPeriod_r9_rf256,
        };
        int mcch_RepetitionPeriod_r9_Pack(std::vector<uint8_t> &bits);
        int mcch_RepetitionPeriod_r9_Unpack(std::vector<uint8_t> bits);
        int mcch_RepetitionPeriod_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        mcch_RepetitionPeriod_r9_Enum mcch_RepetitionPeriod_r9_Value() const;
        int mcch_RepetitionPeriod_r9_SetValue(mcch_RepetitionPeriod_r9_Enum value);
        int mcch_RepetitionPeriod_r9_SetValue(std::string value);
        std::string mcch_RepetitionPeriod_r9_ValueToString(mcch_RepetitionPeriod_r9_Enum value) const;
        uint64_t mcch_RepetitionPeriod_r9_NumberOfValues() const;
        std::string mcch_RepetitionPeriod_r9_ToString(uint32_t indent) const;
        std::string mcch_RepetitionPeriod_r9_ToStringNoNewLines() const;
        int mcch_RepetitionPeriod_r9_Clear();
        bool mcch_RepetitionPeriod_r9_IsPresent() const;
    private:
        bool mcch_RepetitionPeriod_r9_present;
        mcch_RepetitionPeriod_r9_Enum mcch_RepetitionPeriod_r9_internal_value;

        // mcch-Offset-r9
    public:
        int mcch_Offset_r9_Pack(std::vector<uint8_t> &bits);
        int mcch_Offset_r9_Unpack(std::vector<uint8_t> bits);
        int mcch_Offset_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        int64_t mcch_Offset_r9_Value() const;
        int mcch_Offset_r9_SetValue(int64_t value);
        std::string mcch_Offset_r9_ToString(uint32_t indent) const;
        std::string mcch_Offset_r9_ToStringNoNewLines() const;
        int mcch_Offset_r9_Clear();
        bool mcch_Offset_r9_IsPresent() const;
    private:
        bool mcch_Offset_r9_present;
        int64_t mcch_Offset_r9_internal_value;

        // mcch-ModificationPeriod-r9
    public:
        enum mcch_ModificationPeriod_r9_Enum {
            k_mcch_ModificationPeriod_r9_rf512 = 0,
            k_mcch_ModificationPeriod_r9_rf1024,
        };
        int mcch_ModificationPeriod_r9_Pack(std::vector<uint8_t> &bits);
        int mcch_ModificationPeriod_r9_Unpack(std::vector<uint8_t> bits);
        int mcch_ModificationPeriod_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        mcch_ModificationPeriod_r9_Enum mcch_ModificationPeriod_r9_Value() const;
        int mcch_ModificationPeriod_r9_SetValue(mcch_ModificationPeriod_r9_Enum value);
        int mcch_ModificationPeriod_r9_SetValue(std::string value);
        std::string mcch_ModificationPeriod_r9_ValueToString(mcch_ModificationPeriod_r9_Enum value) const;
        uint64_t mcch_ModificationPeriod_r9_NumberOfValues() const;
        std::string mcch_ModificationPeriod_r9_ToString(uint32_t indent) const;
        std::string mcch_ModificationPeriod_r9_ToStringNoNewLines() const;
        int mcch_ModificationPeriod_r9_Clear();
        bool mcch_ModificationPeriod_r9_IsPresent() const;
    private:
        bool mcch_ModificationPeriod_r9_present;
        mcch_ModificationPeriod_r9_Enum mcch_ModificationPeriod_r9_internal_value;

        // sf-AllocInfo-r9
    public:
        int sf_AllocInfo_r9_Pack(std::vector<uint8_t> &bits);
        int sf_AllocInfo_r9_Unpack(std::vector<uint8_t> bits);
        int sf_AllocInfo_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        uint8_t sf_AllocInfo_r9_Value() const;
        int sf_AllocInfo_r9_SetValue(uint8_t value);
        std::string sf_AllocInfo_r9_ToString(uint32_t indent) const;
        std::string sf_AllocInfo_r9_ToStringNoNewLines() const;
        int sf_AllocInfo_r9_Clear();
        bool sf_AllocInfo_r9_IsPresent() const;
    private:
        bool sf_AllocInfo_r9_present;
        uint8_t sf_AllocInfo_r9_internal_value;

        // signallingMCS-r9
    public:
        enum signallingMCS_r9_Enum {
            k_signallingMCS_r9_n2 = 0,
            k_signallingMCS_r9_n7,
            k_signallingMCS_r9_n13,
            k_signallingMCS_r9_n19,
        };
        int signallingMCS_r9_Pack(std::vector<uint8_t> &bits);
        int signallingMCS_r9_Unpack(std::vector<uint8_t> bits);
        int signallingMCS_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        signallingMCS_r9_Enum signallingMCS_r9_Value() const;
        int signallingMCS_r9_SetValue(signallingMCS_r9_Enum value);
        int signallingMCS_r9_SetValue(std::string value);
        std::string signallingMCS_r9_ValueToString(signallingMCS_r9_Enum value) const;
        uint64_t signallingMCS_r9_NumberOfValues() const;
        std::string signallingMCS_r9_ToString(uint32_t indent) const;
        std::string signallingMCS_r9_ToStringNoNewLines() const;
        int signallingMCS_r9_Clear();
        bool signallingMCS_r9_IsPresent() const;
    private:
        bool signallingMCS_r9_present;
        signallingMCS_r9_Enum signallingMCS_r9_internal_value;

    };

    mcch_Config_r9 mcch_Config_r9_value;

};

#endif
