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

#ifndef __RRCConnectionReconfiguration_r8_IEs_H__
#define __RRCConnectionReconfiguration_r8_IEs_H__

#include "MeasConfig.h"
#include "MobilityControlInfo.h"
#include "DedicatedInfoNAS.h"
#include "RadioResourceConfigDedicated.h"
#include "SecurityConfigHO.h"
#include "RRCConnectionReconfiguration_v890_IEs.h"

#include <array>
#include <cstdint>
#include <vector>

class RRCConnectionReconfiguration_r8_IEs
{
public:
    RRCConnectionReconfiguration_r8_IEs() : measConfig_present{false}, mobilityControlInfo_present{false}, dedicatedInfoNASList_present{false}, radioResourceConfigDedicated_present{false}, securityConfigHO_present{false}, nonCriticalExtension_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // measConfig
public:
    MeasConfig* measConfig_Set();
    int measConfig_Set(MeasConfig &value);
    const MeasConfig& measConfig_Get() const;
    std::string measConfig_ToString(uint32_t indent) const;
    std::string measConfig_ToStringNoNewLines() const;
    int measConfig_Clear();
    bool measConfig_IsPresent() const;
private:
    bool measConfig_present;
    MeasConfig measConfig;

    // mobilityControlInfo
public:
    MobilityControlInfo* mobilityControlInfo_Set();
    int mobilityControlInfo_Set(MobilityControlInfo &value);
    const MobilityControlInfo& mobilityControlInfo_Get() const;
    std::string mobilityControlInfo_ToString(uint32_t indent) const;
    std::string mobilityControlInfo_ToStringNoNewLines() const;
    int mobilityControlInfo_Clear();
    bool mobilityControlInfo_IsPresent() const;
private:
    bool mobilityControlInfo_present;
    MobilityControlInfo mobilityControlInfo;

    // dedicatedInfoNASList
public:
    int dedicatedInfoNASList_Pack(std::vector<uint8_t> &bits);
    int dedicatedInfoNASList_Unpack(std::vector<uint8_t> bits);
    int dedicatedInfoNASList_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::vector<DedicatedInfoNAS> dedicatedInfoNASList_Value() const;
    int dedicatedInfoNASList_SetValue(std::vector<DedicatedInfoNAS>);
    int dedicatedInfoNASList_Clear();
    bool dedicatedInfoNASList_IsPresent() const;
    std::string dedicatedInfoNASList_ToString(uint32_t indent) const;
    std::string dedicatedInfoNASList_ToStringNoNewLines() const;
private:
    std::vector<DedicatedInfoNAS> dedicatedInfoNASList_internal_value;
    bool dedicatedInfoNASList_present;

    // radioResourceConfigDedicated
public:
    RadioResourceConfigDedicated* radioResourceConfigDedicated_Set();
    int radioResourceConfigDedicated_Set(RadioResourceConfigDedicated &value);
    const RadioResourceConfigDedicated& radioResourceConfigDedicated_Get() const;
    std::string radioResourceConfigDedicated_ToString(uint32_t indent) const;
    std::string radioResourceConfigDedicated_ToStringNoNewLines() const;
    int radioResourceConfigDedicated_Clear();
    bool radioResourceConfigDedicated_IsPresent() const;
private:
    bool radioResourceConfigDedicated_present;
    RadioResourceConfigDedicated radioResourceConfigDedicated;

    // securityConfigHO
public:
    SecurityConfigHO* securityConfigHO_Set();
    int securityConfigHO_Set(SecurityConfigHO &value);
    const SecurityConfigHO& securityConfigHO_Get() const;
    std::string securityConfigHO_ToString(uint32_t indent) const;
    std::string securityConfigHO_ToStringNoNewLines() const;
    int securityConfigHO_Clear();
    bool securityConfigHO_IsPresent() const;
private:
    bool securityConfigHO_present;
    SecurityConfigHO securityConfigHO;

    // nonCriticalExtension
public:
    RRCConnectionReconfiguration_v890_IEs* nonCriticalExtension_Set();
    int nonCriticalExtension_Set(RRCConnectionReconfiguration_v890_IEs &value);
    const RRCConnectionReconfiguration_v890_IEs& nonCriticalExtension_Get() const;
    std::string nonCriticalExtension_ToString(uint32_t indent) const;
    std::string nonCriticalExtension_ToStringNoNewLines() const;
    int nonCriticalExtension_Clear();
    bool nonCriticalExtension_IsPresent() const;
private:
    bool nonCriticalExtension_present;
    RRCConnectionReconfiguration_v890_IEs nonCriticalExtension;

};

#endif
