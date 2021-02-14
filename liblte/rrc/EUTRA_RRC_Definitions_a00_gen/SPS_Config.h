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

#ifndef __SPS_Config_H__
#define __SPS_Config_H__

#include "C_RNTI.h"
#include "SPS_ConfigDL.h"
#include "SPS_ConfigUL.h"

#include <array>
#include <cstdint>
#include <vector>

class SPS_Config
{
public:
    SPS_Config() : semiPersistSchedC_RNTI_present{false}, sps_ConfigDL_present{false}, sps_ConfigUL_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // semiPersistSchedC-RNTI
public:
    C_RNTI* semiPersistSchedC_RNTI_Set();
    int semiPersistSchedC_RNTI_Set(C_RNTI &value);
    const C_RNTI& semiPersistSchedC_RNTI_Get() const;
    std::string semiPersistSchedC_RNTI_ToString(uint32_t indent) const;
    std::string semiPersistSchedC_RNTI_ToStringNoNewLines() const;
    int semiPersistSchedC_RNTI_Clear();
    bool semiPersistSchedC_RNTI_IsPresent() const;
private:
    bool semiPersistSchedC_RNTI_present;
    C_RNTI semiPersistSchedC_RNTI;

    // sps-ConfigDL
public:
    SPS_ConfigDL* sps_ConfigDL_Set();
    int sps_ConfigDL_Set(SPS_ConfigDL &value);
    const SPS_ConfigDL& sps_ConfigDL_Get() const;
    std::string sps_ConfigDL_ToString(uint32_t indent) const;
    std::string sps_ConfigDL_ToStringNoNewLines() const;
    int sps_ConfigDL_Clear();
    bool sps_ConfigDL_IsPresent() const;
private:
    bool sps_ConfigDL_present;
    SPS_ConfigDL sps_ConfigDL;

    // sps-ConfigUL
public:
    SPS_ConfigUL* sps_ConfigUL_Set();
    int sps_ConfigUL_Set(SPS_ConfigUL &value);
    const SPS_ConfigUL& sps_ConfigUL_Get() const;
    std::string sps_ConfigUL_ToString(uint32_t indent) const;
    std::string sps_ConfigUL_ToStringNoNewLines() const;
    int sps_ConfigUL_Clear();
    bool sps_ConfigUL_IsPresent() const;
private:
    bool sps_ConfigUL_present;
    SPS_ConfigUL sps_ConfigUL;

};

#endif
