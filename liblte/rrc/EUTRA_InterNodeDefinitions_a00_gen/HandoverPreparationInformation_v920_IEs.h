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

#ifndef __HandoverPreparationInformation_v920_IEs_H__
#define __HandoverPreparationInformation_v920_IEs_H__

#include <array>
#include <cstdint>
#include <vector>

class HandoverPreparationInformation_v920_IEs
{
public:
    HandoverPreparationInformation_v920_IEs() : ue_ConfigRelease_r9_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // ue-ConfigRelease-r9
public:
    enum ue_ConfigRelease_r9_Enum {
        k_ue_ConfigRelease_r9_rel9 = 0,
        k_ue_ConfigRelease_r9_spare7,
        k_ue_ConfigRelease_r9_spare6,
        k_ue_ConfigRelease_r9_spare5,
        k_ue_ConfigRelease_r9_spare4,
        k_ue_ConfigRelease_r9_spare3,
        k_ue_ConfigRelease_r9_spare2,
        k_ue_ConfigRelease_r9_spare1,
    };
    int ue_ConfigRelease_r9_Pack(std::vector<uint8_t> &bits);
    int ue_ConfigRelease_r9_Unpack(std::vector<uint8_t> bits);
    int ue_ConfigRelease_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    ue_ConfigRelease_r9_Enum ue_ConfigRelease_r9_Value() const;
    int ue_ConfigRelease_r9_SetValue(ue_ConfigRelease_r9_Enum value);
    int ue_ConfigRelease_r9_SetValue(std::string value);
    std::string ue_ConfigRelease_r9_ValueToString(ue_ConfigRelease_r9_Enum value) const;
    uint64_t ue_ConfigRelease_r9_NumberOfValues() const;
    std::string ue_ConfigRelease_r9_ToString(uint32_t indent) const;
    std::string ue_ConfigRelease_r9_ToStringNoNewLines() const;
    int ue_ConfigRelease_r9_Clear();
    bool ue_ConfigRelease_r9_IsPresent() const;
private:
    bool ue_ConfigRelease_r9_present;
    ue_ConfigRelease_r9_Enum ue_ConfigRelease_r9_internal_value;

    // nonCriticalExtension

};

#endif
