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

#ifndef __UERadioAccessCapabilityInformation_r8_IEs_H__
#define __UERadioAccessCapabilityInformation_r8_IEs_H__

#include <array>
#include <cstdint>
#include <vector>

class UERadioAccessCapabilityInformation_r8_IEs
{
public:
    UERadioAccessCapabilityInformation_r8_IEs() : ue_RadioAccessCapabilityInfo_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // ue-RadioAccessCapabilityInfo
public:
    int ue_RadioAccessCapabilityInfo_Pack(std::vector<uint8_t> &bits);
    int ue_RadioAccessCapabilityInfo_Unpack(std::vector<uint8_t> bits);
    int ue_RadioAccessCapabilityInfo_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::vector<uint8_t> ue_RadioAccessCapabilityInfo_Value() const;
    int ue_RadioAccessCapabilityInfo_SetValue(std::vector<uint8_t> value);
    std::string ue_RadioAccessCapabilityInfo_ToString(uint32_t indent) const;
    std::string ue_RadioAccessCapabilityInfo_ToStringNoNewLines() const;
    int ue_RadioAccessCapabilityInfo_Clear();
    bool ue_RadioAccessCapabilityInfo_IsPresent() const;
private:
    bool ue_RadioAccessCapabilityInfo_present;
    std::vector<uint8_t> ue_RadioAccessCapabilityInfo_internal_value;

    // nonCriticalExtension

};

#endif
