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

#ifndef __UE_EUTRA_Capability_v10xy_IEs_H__
#define __UE_EUTRA_Capability_v10xy_IEs_H__

#include "RF_Parameters_v10xy.h"

#include <array>
#include <cstdint>
#include <vector>

class UE_EUTRA_Capability_v10xy_IEs
{
public:
    UE_EUTRA_Capability_v10xy_IEs() : ue_Category_v10xy_present{false}, rf_Parameters_v10xy_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // ue-Category-v10xy
public:
    int ue_Category_v10xy_Pack(std::vector<uint8_t> &bits);
    int ue_Category_v10xy_Unpack(std::vector<uint8_t> bits);
    int ue_Category_v10xy_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t ue_Category_v10xy_Value() const;
    int ue_Category_v10xy_SetValue(int64_t value);
    std::string ue_Category_v10xy_ToString(uint32_t indent) const;
    std::string ue_Category_v10xy_ToStringNoNewLines() const;
    int ue_Category_v10xy_Clear();
    bool ue_Category_v10xy_IsPresent() const;
private:
    bool ue_Category_v10xy_present;
    int64_t ue_Category_v10xy_internal_value;

    // rf-Parameters-v10xy
public:
    RF_Parameters_v10xy* rf_Parameters_v10xy_Set();
    int rf_Parameters_v10xy_Set(RF_Parameters_v10xy &value);
    const RF_Parameters_v10xy& rf_Parameters_v10xy_Get() const;
    std::string rf_Parameters_v10xy_ToString(uint32_t indent) const;
    std::string rf_Parameters_v10xy_ToStringNoNewLines() const;
    int rf_Parameters_v10xy_Clear();
    bool rf_Parameters_v10xy_IsPresent() const;
private:
    bool rf_Parameters_v10xy_present;
    RF_Parameters_v10xy rf_Parameters_v10xy;

    // nonCriticalExtension

};

#endif
