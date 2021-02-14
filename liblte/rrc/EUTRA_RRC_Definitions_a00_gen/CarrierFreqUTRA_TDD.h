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

#ifndef __CarrierFreqUTRA_TDD_H__
#define __CarrierFreqUTRA_TDD_H__

#include "ARFCN_ValueUTRA.h"
#include "CellReselectionPriority.h"
#include "ReselectionThreshold.h"
#include "ReselectionThreshold.h"

#include <array>
#include <cstdint>
#include <vector>

class CarrierFreqUTRA_TDD
{
public:
    CarrierFreqUTRA_TDD() : carrierFreq_present{false}, cellReselectionPriority_present{false}, threshX_High_present{false}, threshX_Low_present{false}, q_RxLevMin_present{false}, p_MaxUTRA_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // carrierFreq
public:
    ARFCN_ValueUTRA* carrierFreq_Set();
    int carrierFreq_Set(ARFCN_ValueUTRA &value);
    const ARFCN_ValueUTRA& carrierFreq_Get() const;
    std::string carrierFreq_ToString(uint32_t indent) const;
    std::string carrierFreq_ToStringNoNewLines() const;
    int carrierFreq_Clear();
    bool carrierFreq_IsPresent() const;
private:
    bool carrierFreq_present;
    ARFCN_ValueUTRA carrierFreq;

    // cellReselectionPriority
public:
    CellReselectionPriority* cellReselectionPriority_Set();
    int cellReselectionPriority_Set(CellReselectionPriority &value);
    const CellReselectionPriority& cellReselectionPriority_Get() const;
    std::string cellReselectionPriority_ToString(uint32_t indent) const;
    std::string cellReselectionPriority_ToStringNoNewLines() const;
    int cellReselectionPriority_Clear();
    bool cellReselectionPriority_IsPresent() const;
private:
    bool cellReselectionPriority_present;
    CellReselectionPriority cellReselectionPriority;

    // threshX-High
public:
    ReselectionThreshold* threshX_High_Set();
    int threshX_High_Set(ReselectionThreshold &value);
    const ReselectionThreshold& threshX_High_Get() const;
    std::string threshX_High_ToString(uint32_t indent) const;
    std::string threshX_High_ToStringNoNewLines() const;
    int threshX_High_Clear();
    bool threshX_High_IsPresent() const;
private:
    bool threshX_High_present;
    ReselectionThreshold threshX_High;

    // threshX-Low
public:
    ReselectionThreshold* threshX_Low_Set();
    int threshX_Low_Set(ReselectionThreshold &value);
    const ReselectionThreshold& threshX_Low_Get() const;
    std::string threshX_Low_ToString(uint32_t indent) const;
    std::string threshX_Low_ToStringNoNewLines() const;
    int threshX_Low_Clear();
    bool threshX_Low_IsPresent() const;
private:
    bool threshX_Low_present;
    ReselectionThreshold threshX_Low;

    // q-RxLevMin
public:
    int q_RxLevMin_Pack(std::vector<uint8_t> &bits);
    int q_RxLevMin_Unpack(std::vector<uint8_t> bits);
    int q_RxLevMin_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t q_RxLevMin_Value() const;
    int q_RxLevMin_SetValue(int64_t value);
    std::string q_RxLevMin_ToString(uint32_t indent) const;
    std::string q_RxLevMin_ToStringNoNewLines() const;
    int q_RxLevMin_Clear();
    bool q_RxLevMin_IsPresent() const;
private:
    bool q_RxLevMin_present;
    int64_t q_RxLevMin_internal_value;

    // p-MaxUTRA
public:
    int p_MaxUTRA_Pack(std::vector<uint8_t> &bits);
    int p_MaxUTRA_Unpack(std::vector<uint8_t> bits);
    int p_MaxUTRA_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t p_MaxUTRA_Value() const;
    int p_MaxUTRA_SetValue(int64_t value);
    std::string p_MaxUTRA_ToString(uint32_t indent) const;
    std::string p_MaxUTRA_ToStringNoNewLines() const;
    int p_MaxUTRA_Clear();
    bool p_MaxUTRA_IsPresent() const;
private:
    bool p_MaxUTRA_present;
    int64_t p_MaxUTRA_internal_value;

};

#endif
