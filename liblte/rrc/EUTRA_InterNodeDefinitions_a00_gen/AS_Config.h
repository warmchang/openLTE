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

#ifndef __AS_Config_H__
#define __AS_Config_H__

#include "MeasConfig.h"
#include "RadioResourceConfigDedicated.h"
#include "SecurityAlgorithmConfig.h"
#include "C_RNTI.h"
#include "MasterInformationBlock.h"
#include "SystemInformationBlockType1.h"
#include "SystemInformationBlockType2.h"
#include "AntennaInfoCommon.h"
#include "ARFCN_ValueEUTRA.h"
#include "OtherConfig_r9.h"
#include "SCellToAddModList_r10.h"

#include <array>
#include <cstdint>
#include <vector>

class AS_Config
{
public:
    AS_Config() : sourceMeasConfig_present{false}, sourceRadioResourceConfig_present{false}, sourceSecurityAlgorithmConfig_present{false}, sourceUE_Identity_present{false}, sourceMasterInformationBlock_present{false}, sourceSystemInformationBlockType1_present{false}, sourceSystemInformationBlockType2_present{false}, antennaInfoCommon_present{false}, sourceDl_CarrierFreq_present{false}, sourceSystemInformationBlockType1Ext_present{false}, sourceOtherConfig_r9_present{false}, sourceSCellConfigList_r10_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // sourceMeasConfig
public:
    MeasConfig* sourceMeasConfig_Set();
    int sourceMeasConfig_Set(MeasConfig &value);
    const MeasConfig& sourceMeasConfig_Get() const;
    std::string sourceMeasConfig_ToString(uint32_t indent) const;
    std::string sourceMeasConfig_ToStringNoNewLines() const;
    int sourceMeasConfig_Clear();
    bool sourceMeasConfig_IsPresent() const;
private:
    bool sourceMeasConfig_present;
    MeasConfig sourceMeasConfig;

    // sourceRadioResourceConfig
public:
    RadioResourceConfigDedicated* sourceRadioResourceConfig_Set();
    int sourceRadioResourceConfig_Set(RadioResourceConfigDedicated &value);
    const RadioResourceConfigDedicated& sourceRadioResourceConfig_Get() const;
    std::string sourceRadioResourceConfig_ToString(uint32_t indent) const;
    std::string sourceRadioResourceConfig_ToStringNoNewLines() const;
    int sourceRadioResourceConfig_Clear();
    bool sourceRadioResourceConfig_IsPresent() const;
private:
    bool sourceRadioResourceConfig_present;
    RadioResourceConfigDedicated sourceRadioResourceConfig;

    // sourceSecurityAlgorithmConfig
public:
    SecurityAlgorithmConfig* sourceSecurityAlgorithmConfig_Set();
    int sourceSecurityAlgorithmConfig_Set(SecurityAlgorithmConfig &value);
    const SecurityAlgorithmConfig& sourceSecurityAlgorithmConfig_Get() const;
    std::string sourceSecurityAlgorithmConfig_ToString(uint32_t indent) const;
    std::string sourceSecurityAlgorithmConfig_ToStringNoNewLines() const;
    int sourceSecurityAlgorithmConfig_Clear();
    bool sourceSecurityAlgorithmConfig_IsPresent() const;
private:
    bool sourceSecurityAlgorithmConfig_present;
    SecurityAlgorithmConfig sourceSecurityAlgorithmConfig;

    // sourceUE-Identity
public:
    C_RNTI* sourceUE_Identity_Set();
    int sourceUE_Identity_Set(C_RNTI &value);
    const C_RNTI& sourceUE_Identity_Get() const;
    std::string sourceUE_Identity_ToString(uint32_t indent) const;
    std::string sourceUE_Identity_ToStringNoNewLines() const;
    int sourceUE_Identity_Clear();
    bool sourceUE_Identity_IsPresent() const;
private:
    bool sourceUE_Identity_present;
    C_RNTI sourceUE_Identity;

    // sourceMasterInformationBlock
public:
    MasterInformationBlock* sourceMasterInformationBlock_Set();
    int sourceMasterInformationBlock_Set(MasterInformationBlock &value);
    const MasterInformationBlock& sourceMasterInformationBlock_Get() const;
    std::string sourceMasterInformationBlock_ToString(uint32_t indent) const;
    std::string sourceMasterInformationBlock_ToStringNoNewLines() const;
    int sourceMasterInformationBlock_Clear();
    bool sourceMasterInformationBlock_IsPresent() const;
private:
    bool sourceMasterInformationBlock_present;
    MasterInformationBlock sourceMasterInformationBlock;

    // sourceSystemInformationBlockType1
public:
    SystemInformationBlockType1* sourceSystemInformationBlockType1_Set();
    int sourceSystemInformationBlockType1_Set(SystemInformationBlockType1 &value);
    const SystemInformationBlockType1& sourceSystemInformationBlockType1_Get() const;
    std::string sourceSystemInformationBlockType1_ToString(uint32_t indent) const;
    std::string sourceSystemInformationBlockType1_ToStringNoNewLines() const;
    int sourceSystemInformationBlockType1_Clear();
    bool sourceSystemInformationBlockType1_IsPresent() const;
private:
    bool sourceSystemInformationBlockType1_present;
    SystemInformationBlockType1 sourceSystemInformationBlockType1;

    // sourceSystemInformationBlockType2
public:
    SystemInformationBlockType2* sourceSystemInformationBlockType2_Set();
    int sourceSystemInformationBlockType2_Set(SystemInformationBlockType2 &value);
    const SystemInformationBlockType2& sourceSystemInformationBlockType2_Get() const;
    std::string sourceSystemInformationBlockType2_ToString(uint32_t indent) const;
    std::string sourceSystemInformationBlockType2_ToStringNoNewLines() const;
    int sourceSystemInformationBlockType2_Clear();
    bool sourceSystemInformationBlockType2_IsPresent() const;
private:
    bool sourceSystemInformationBlockType2_present;
    SystemInformationBlockType2 sourceSystemInformationBlockType2;

    // antennaInfoCommon
public:
    AntennaInfoCommon* antennaInfoCommon_Set();
    int antennaInfoCommon_Set(AntennaInfoCommon &value);
    const AntennaInfoCommon& antennaInfoCommon_Get() const;
    std::string antennaInfoCommon_ToString(uint32_t indent) const;
    std::string antennaInfoCommon_ToStringNoNewLines() const;
    int antennaInfoCommon_Clear();
    bool antennaInfoCommon_IsPresent() const;
private:
    bool antennaInfoCommon_present;
    AntennaInfoCommon antennaInfoCommon;

    // sourceDl-CarrierFreq
public:
    ARFCN_ValueEUTRA* sourceDl_CarrierFreq_Set();
    int sourceDl_CarrierFreq_Set(ARFCN_ValueEUTRA &value);
    const ARFCN_ValueEUTRA& sourceDl_CarrierFreq_Get() const;
    std::string sourceDl_CarrierFreq_ToString(uint32_t indent) const;
    std::string sourceDl_CarrierFreq_ToStringNoNewLines() const;
    int sourceDl_CarrierFreq_Clear();
    bool sourceDl_CarrierFreq_IsPresent() const;
private:
    bool sourceDl_CarrierFreq_present;
    ARFCN_ValueEUTRA sourceDl_CarrierFreq;

    // sourceSystemInformationBlockType1Ext
public:
    int sourceSystemInformationBlockType1Ext_Pack(std::vector<uint8_t> &bits);
    int sourceSystemInformationBlockType1Ext_Unpack(std::vector<uint8_t> bits);
    int sourceSystemInformationBlockType1Ext_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::vector<uint8_t> sourceSystemInformationBlockType1Ext_Value() const;
    int sourceSystemInformationBlockType1Ext_SetValue(std::vector<uint8_t> value);
    std::string sourceSystemInformationBlockType1Ext_ToString(uint32_t indent) const;
    std::string sourceSystemInformationBlockType1Ext_ToStringNoNewLines() const;
    int sourceSystemInformationBlockType1Ext_Clear();
    bool sourceSystemInformationBlockType1Ext_IsPresent() const;
private:
    bool sourceSystemInformationBlockType1Ext_present;
    std::vector<uint8_t> sourceSystemInformationBlockType1Ext_internal_value;

    // sourceOtherConfig-r9
public:
    OtherConfig_r9* sourceOtherConfig_r9_Set();
    int sourceOtherConfig_r9_Set(OtherConfig_r9 &value);
    const OtherConfig_r9& sourceOtherConfig_r9_Get() const;
    std::string sourceOtherConfig_r9_ToString(uint32_t indent) const;
    std::string sourceOtherConfig_r9_ToStringNoNewLines() const;
    int sourceOtherConfig_r9_Clear();
    bool sourceOtherConfig_r9_IsPresent() const;
private:
    bool sourceOtherConfig_r9_present;
    OtherConfig_r9 sourceOtherConfig_r9;

    // sourceSCellConfigList-r10
public:
    SCellToAddModList_r10* sourceSCellConfigList_r10_Set();
    int sourceSCellConfigList_r10_Set(SCellToAddModList_r10 &value);
    const SCellToAddModList_r10& sourceSCellConfigList_r10_Get() const;
    std::string sourceSCellConfigList_r10_ToString(uint32_t indent) const;
    std::string sourceSCellConfigList_r10_ToStringNoNewLines() const;
    int sourceSCellConfigList_r10_Clear();
    bool sourceSCellConfigList_r10_IsPresent() const;
private:
    bool sourceSCellConfigList_r10_present;
    SCellToAddModList_r10 sourceSCellConfigList_r10;

};

#endif
