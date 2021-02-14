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

#ifndef __SystemInformationBlockType6_H__
#define __SystemInformationBlockType6_H__

#include "CarrierFreqListUTRA_FDD.h"
#include "CarrierFreqListUTRA_TDD.h"
#include "T_Reselection.h"
#include "SpeedStateScaleFactors.h"

#include <array>
#include <cstdint>
#include <vector>

class SystemInformationBlockType6
{
public:
    SystemInformationBlockType6() : carrierFreqListUTRA_FDD_present{false}, carrierFreqListUTRA_TDD_present{false}, t_ReselectionUTRA_present{false}, t_ReselectionUTRA_SF_present{false}, lateNonCriticalExtension_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // carrierFreqListUTRA-FDD
public:
    CarrierFreqListUTRA_FDD* carrierFreqListUTRA_FDD_Set();
    int carrierFreqListUTRA_FDD_Set(CarrierFreqListUTRA_FDD &value);
    const CarrierFreqListUTRA_FDD& carrierFreqListUTRA_FDD_Get() const;
    std::string carrierFreqListUTRA_FDD_ToString(uint32_t indent) const;
    std::string carrierFreqListUTRA_FDD_ToStringNoNewLines() const;
    int carrierFreqListUTRA_FDD_Clear();
    bool carrierFreqListUTRA_FDD_IsPresent() const;
private:
    bool carrierFreqListUTRA_FDD_present;
    CarrierFreqListUTRA_FDD carrierFreqListUTRA_FDD;

    // carrierFreqListUTRA-TDD
public:
    CarrierFreqListUTRA_TDD* carrierFreqListUTRA_TDD_Set();
    int carrierFreqListUTRA_TDD_Set(CarrierFreqListUTRA_TDD &value);
    const CarrierFreqListUTRA_TDD& carrierFreqListUTRA_TDD_Get() const;
    std::string carrierFreqListUTRA_TDD_ToString(uint32_t indent) const;
    std::string carrierFreqListUTRA_TDD_ToStringNoNewLines() const;
    int carrierFreqListUTRA_TDD_Clear();
    bool carrierFreqListUTRA_TDD_IsPresent() const;
private:
    bool carrierFreqListUTRA_TDD_present;
    CarrierFreqListUTRA_TDD carrierFreqListUTRA_TDD;

    // t-ReselectionUTRA
public:
    T_Reselection* t_ReselectionUTRA_Set();
    int t_ReselectionUTRA_Set(T_Reselection &value);
    const T_Reselection& t_ReselectionUTRA_Get() const;
    std::string t_ReselectionUTRA_ToString(uint32_t indent) const;
    std::string t_ReselectionUTRA_ToStringNoNewLines() const;
    int t_ReselectionUTRA_Clear();
    bool t_ReselectionUTRA_IsPresent() const;
private:
    bool t_ReselectionUTRA_present;
    T_Reselection t_ReselectionUTRA;

    // t-ReselectionUTRA-SF
public:
    SpeedStateScaleFactors* t_ReselectionUTRA_SF_Set();
    int t_ReselectionUTRA_SF_Set(SpeedStateScaleFactors &value);
    const SpeedStateScaleFactors& t_ReselectionUTRA_SF_Get() const;
    std::string t_ReselectionUTRA_SF_ToString(uint32_t indent) const;
    std::string t_ReselectionUTRA_SF_ToStringNoNewLines() const;
    int t_ReselectionUTRA_SF_Clear();
    bool t_ReselectionUTRA_SF_IsPresent() const;
private:
    bool t_ReselectionUTRA_SF_present;
    SpeedStateScaleFactors t_ReselectionUTRA_SF;

    // lateNonCriticalExtension
public:
    int lateNonCriticalExtension_Pack(std::vector<uint8_t> &bits);
    int lateNonCriticalExtension_Unpack(std::vector<uint8_t> bits);
    int lateNonCriticalExtension_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::vector<uint8_t> lateNonCriticalExtension_Value() const;
    int lateNonCriticalExtension_SetValue(std::vector<uint8_t> value);
    std::string lateNonCriticalExtension_ToString(uint32_t indent) const;
    std::string lateNonCriticalExtension_ToStringNoNewLines() const;
    int lateNonCriticalExtension_Clear();
    bool lateNonCriticalExtension_IsPresent() const;
private:
    bool lateNonCriticalExtension_present;
    std::vector<uint8_t> lateNonCriticalExtension_internal_value;

};

#endif
