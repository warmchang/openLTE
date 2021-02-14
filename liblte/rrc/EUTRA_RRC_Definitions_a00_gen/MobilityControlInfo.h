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

#ifndef __MobilityControlInfo_H__
#define __MobilityControlInfo_H__

#include "PhysCellId.h"
#include "CarrierFreqEUTRA.h"
#include "CarrierBandwidthEUTRA.h"
#include "AdditionalSpectrumEmission.h"
#include "C_RNTI.h"
#include "RadioResourceConfigCommon.h"
#include "RACH_ConfigDedicated.h"

#include <array>
#include <cstdint>
#include <vector>

class MobilityControlInfo
{
public:
    MobilityControlInfo() : targetPhysCellId_present{false}, carrierFreq_present{false}, carrierBandwidth_present{false}, additionalSpectrumEmission_present{false}, t304_present{false}, newUE_Identity_present{false}, radioResourceConfigCommon_present{false}, rach_ConfigDedicated_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // targetPhysCellId
public:
    PhysCellId* targetPhysCellId_Set();
    int targetPhysCellId_Set(PhysCellId &value);
    const PhysCellId& targetPhysCellId_Get() const;
    std::string targetPhysCellId_ToString(uint32_t indent) const;
    std::string targetPhysCellId_ToStringNoNewLines() const;
    int targetPhysCellId_Clear();
    bool targetPhysCellId_IsPresent() const;
private:
    bool targetPhysCellId_present;
    PhysCellId targetPhysCellId;

    // carrierFreq
public:
    CarrierFreqEUTRA* carrierFreq_Set();
    int carrierFreq_Set(CarrierFreqEUTRA &value);
    const CarrierFreqEUTRA& carrierFreq_Get() const;
    std::string carrierFreq_ToString(uint32_t indent) const;
    std::string carrierFreq_ToStringNoNewLines() const;
    int carrierFreq_Clear();
    bool carrierFreq_IsPresent() const;
private:
    bool carrierFreq_present;
    CarrierFreqEUTRA carrierFreq;

    // carrierBandwidth
public:
    CarrierBandwidthEUTRA* carrierBandwidth_Set();
    int carrierBandwidth_Set(CarrierBandwidthEUTRA &value);
    const CarrierBandwidthEUTRA& carrierBandwidth_Get() const;
    std::string carrierBandwidth_ToString(uint32_t indent) const;
    std::string carrierBandwidth_ToStringNoNewLines() const;
    int carrierBandwidth_Clear();
    bool carrierBandwidth_IsPresent() const;
private:
    bool carrierBandwidth_present;
    CarrierBandwidthEUTRA carrierBandwidth;

    // additionalSpectrumEmission
public:
    AdditionalSpectrumEmission* additionalSpectrumEmission_Set();
    int additionalSpectrumEmission_Set(AdditionalSpectrumEmission &value);
    const AdditionalSpectrumEmission& additionalSpectrumEmission_Get() const;
    std::string additionalSpectrumEmission_ToString(uint32_t indent) const;
    std::string additionalSpectrumEmission_ToStringNoNewLines() const;
    int additionalSpectrumEmission_Clear();
    bool additionalSpectrumEmission_IsPresent() const;
private:
    bool additionalSpectrumEmission_present;
    AdditionalSpectrumEmission additionalSpectrumEmission;

    // t304
public:
    enum t304_Enum {
        k_t304_ms50 = 0,
        k_t304_ms100,
        k_t304_ms150,
        k_t304_ms200,
        k_t304_ms500,
        k_t304_ms1000,
        k_t304_ms2000,
        k_t304_spare1,
    };
    int t304_Pack(std::vector<uint8_t> &bits);
    int t304_Unpack(std::vector<uint8_t> bits);
    int t304_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    t304_Enum t304_Value() const;
    int t304_SetValue(t304_Enum value);
    int t304_SetValue(std::string value);
    std::string t304_ValueToString(t304_Enum value) const;
    uint64_t t304_NumberOfValues() const;
    std::string t304_ToString(uint32_t indent) const;
    std::string t304_ToStringNoNewLines() const;
    int t304_Clear();
    bool t304_IsPresent() const;
private:
    bool t304_present;
    t304_Enum t304_internal_value;

    // newUE-Identity
public:
    C_RNTI* newUE_Identity_Set();
    int newUE_Identity_Set(C_RNTI &value);
    const C_RNTI& newUE_Identity_Get() const;
    std::string newUE_Identity_ToString(uint32_t indent) const;
    std::string newUE_Identity_ToStringNoNewLines() const;
    int newUE_Identity_Clear();
    bool newUE_Identity_IsPresent() const;
private:
    bool newUE_Identity_present;
    C_RNTI newUE_Identity;

    // radioResourceConfigCommon
public:
    RadioResourceConfigCommon* radioResourceConfigCommon_Set();
    int radioResourceConfigCommon_Set(RadioResourceConfigCommon &value);
    const RadioResourceConfigCommon& radioResourceConfigCommon_Get() const;
    std::string radioResourceConfigCommon_ToString(uint32_t indent) const;
    std::string radioResourceConfigCommon_ToStringNoNewLines() const;
    int radioResourceConfigCommon_Clear();
    bool radioResourceConfigCommon_IsPresent() const;
private:
    bool radioResourceConfigCommon_present;
    RadioResourceConfigCommon radioResourceConfigCommon;

    // rach-ConfigDedicated
public:
    RACH_ConfigDedicated* rach_ConfigDedicated_Set();
    int rach_ConfigDedicated_Set(RACH_ConfigDedicated &value);
    const RACH_ConfigDedicated& rach_ConfigDedicated_Get() const;
    std::string rach_ConfigDedicated_ToString(uint32_t indent) const;
    std::string rach_ConfigDedicated_ToStringNoNewLines() const;
    int rach_ConfigDedicated_Clear();
    bool rach_ConfigDedicated_IsPresent() const;
private:
    bool rach_ConfigDedicated_present;
    RACH_ConfigDedicated rach_ConfigDedicated;

};

#endif
