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

#ifndef __Handover_H__
#define __Handover_H__

#include "SI_OrPSI_GERAN.h"

#include <array>
#include <cstdint>
#include <vector>

class Handover
{
public:
    Handover() : targetRAT_Type_present{false}, targetRAT_MessageContainer_present{false}, nas_SecurityParamFromEUTRA_present{false}, systemInformation_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // targetRAT-Type
public:
    enum targetRAT_Type_Enum {
        k_targetRAT_Type_utra = 0,
        k_targetRAT_Type_geran,
        k_targetRAT_Type_cdma2000_1XRTT,
        k_targetRAT_Type_cdma2000_HRPD,
        k_targetRAT_Type_spare4,
        k_targetRAT_Type_spare3,
        k_targetRAT_Type_spare2,
        k_targetRAT_Type_spare1,
    };
    int targetRAT_Type_Pack(std::vector<uint8_t> &bits);
    int targetRAT_Type_Unpack(std::vector<uint8_t> bits);
    int targetRAT_Type_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    targetRAT_Type_Enum targetRAT_Type_Value() const;
    int targetRAT_Type_SetValue(targetRAT_Type_Enum value);
    int targetRAT_Type_SetValue(std::string value);
    std::string targetRAT_Type_ValueToString(targetRAT_Type_Enum value) const;
    uint64_t targetRAT_Type_NumberOfValues() const;
    std::string targetRAT_Type_ToString(uint32_t indent) const;
    std::string targetRAT_Type_ToStringNoNewLines() const;
    int targetRAT_Type_Clear();
    bool targetRAT_Type_IsPresent() const;
private:
    bool targetRAT_Type_present;
    targetRAT_Type_Enum targetRAT_Type_internal_value;

    // targetRAT-MessageContainer
public:
    int targetRAT_MessageContainer_Pack(std::vector<uint8_t> &bits);
    int targetRAT_MessageContainer_Unpack(std::vector<uint8_t> bits);
    int targetRAT_MessageContainer_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::vector<uint8_t> targetRAT_MessageContainer_Value() const;
    int targetRAT_MessageContainer_SetValue(std::vector<uint8_t> value);
    std::string targetRAT_MessageContainer_ToString(uint32_t indent) const;
    std::string targetRAT_MessageContainer_ToStringNoNewLines() const;
    int targetRAT_MessageContainer_Clear();
    bool targetRAT_MessageContainer_IsPresent() const;
private:
    bool targetRAT_MessageContainer_present;
    std::vector<uint8_t> targetRAT_MessageContainer_internal_value;

    // nas-SecurityParamFromEUTRA
public:
    int nas_SecurityParamFromEUTRA_Pack(std::vector<uint8_t> &bits);
    int nas_SecurityParamFromEUTRA_Unpack(std::vector<uint8_t> bits);
    int nas_SecurityParamFromEUTRA_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::vector<uint8_t> nas_SecurityParamFromEUTRA_Value() const;
    int nas_SecurityParamFromEUTRA_SetValue(std::vector<uint8_t> value);
    std::string nas_SecurityParamFromEUTRA_ToString(uint32_t indent) const;
    std::string nas_SecurityParamFromEUTRA_ToStringNoNewLines() const;
    int nas_SecurityParamFromEUTRA_Clear();
    bool nas_SecurityParamFromEUTRA_IsPresent() const;
private:
    bool nas_SecurityParamFromEUTRA_present;
    std::vector<uint8_t> nas_SecurityParamFromEUTRA_internal_value;

    // systemInformation
public:
    SI_OrPSI_GERAN* systemInformation_Set();
    int systemInformation_Set(SI_OrPSI_GERAN &value);
    const SI_OrPSI_GERAN& systemInformation_Get() const;
    std::string systemInformation_ToString(uint32_t indent) const;
    std::string systemInformation_ToStringNoNewLines() const;
    int systemInformation_Clear();
    bool systemInformation_IsPresent() const;
private:
    bool systemInformation_present;
    SI_OrPSI_GERAN systemInformation;

};

#endif
