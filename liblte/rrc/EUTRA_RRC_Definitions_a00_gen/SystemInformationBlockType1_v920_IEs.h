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

#ifndef __SystemInformationBlockType1_v920_IEs_H__
#define __SystemInformationBlockType1_v920_IEs_H__

#include "CellSelectionInfo_v920.h"

#include <array>
#include <cstdint>
#include <vector>

class SystemInformationBlockType1_v920_IEs
{
public:
    SystemInformationBlockType1_v920_IEs() : ims_EmergencySupport_r9_present{false}, cellSelectionInfo_v920_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // ims-EmergencySupport-r9
public:
    enum ims_EmergencySupport_r9_Enum {
        k_ims_EmergencySupport_r9_true = 0,
    };
    int ims_EmergencySupport_r9_Pack(std::vector<uint8_t> &bits);
    int ims_EmergencySupport_r9_Unpack(std::vector<uint8_t> bits);
    int ims_EmergencySupport_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    ims_EmergencySupport_r9_Enum ims_EmergencySupport_r9_Value() const;
    int ims_EmergencySupport_r9_SetValue(ims_EmergencySupport_r9_Enum value);
    int ims_EmergencySupport_r9_SetValue(std::string value);
    std::string ims_EmergencySupport_r9_ValueToString(ims_EmergencySupport_r9_Enum value) const;
    uint64_t ims_EmergencySupport_r9_NumberOfValues() const;
    std::string ims_EmergencySupport_r9_ToString(uint32_t indent) const;
    std::string ims_EmergencySupport_r9_ToStringNoNewLines() const;
    int ims_EmergencySupport_r9_Clear();
    bool ims_EmergencySupport_r9_IsPresent() const;
private:
    bool ims_EmergencySupport_r9_present;
    ims_EmergencySupport_r9_Enum ims_EmergencySupport_r9_internal_value;

    // cellSelectionInfo-v920
public:
    CellSelectionInfo_v920* cellSelectionInfo_v920_Set();
    int cellSelectionInfo_v920_Set(CellSelectionInfo_v920 &value);
    const CellSelectionInfo_v920& cellSelectionInfo_v920_Get() const;
    std::string cellSelectionInfo_v920_ToString(uint32_t indent) const;
    std::string cellSelectionInfo_v920_ToStringNoNewLines() const;
    int cellSelectionInfo_v920_Clear();
    bool cellSelectionInfo_v920_IsPresent() const;
private:
    bool cellSelectionInfo_v920_present;
    CellSelectionInfo_v920 cellSelectionInfo_v920;

    // nonCriticalExtension

};

#endif
