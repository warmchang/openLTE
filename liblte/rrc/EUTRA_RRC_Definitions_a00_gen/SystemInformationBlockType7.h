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

#ifndef __SystemInformationBlockType7_H__
#define __SystemInformationBlockType7_H__

#include "T_Reselection.h"
#include "SpeedStateScaleFactors.h"
#include "CarrierFreqsInfoListGERAN.h"

#include <array>
#include <cstdint>
#include <vector>

class SystemInformationBlockType7
{
public:
    SystemInformationBlockType7() : t_ReselectionGERAN_present{false}, t_ReselectionGERAN_SF_present{false}, carrierFreqsInfoList_present{false}, lateNonCriticalExtension_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // t-ReselectionGERAN
public:
    T_Reselection* t_ReselectionGERAN_Set();
    int t_ReselectionGERAN_Set(T_Reselection &value);
    const T_Reselection& t_ReselectionGERAN_Get() const;
    std::string t_ReselectionGERAN_ToString(uint32_t indent) const;
    std::string t_ReselectionGERAN_ToStringNoNewLines() const;
    int t_ReselectionGERAN_Clear();
    bool t_ReselectionGERAN_IsPresent() const;
private:
    bool t_ReselectionGERAN_present;
    T_Reselection t_ReselectionGERAN;

    // t-ReselectionGERAN-SF
public:
    SpeedStateScaleFactors* t_ReselectionGERAN_SF_Set();
    int t_ReselectionGERAN_SF_Set(SpeedStateScaleFactors &value);
    const SpeedStateScaleFactors& t_ReselectionGERAN_SF_Get() const;
    std::string t_ReselectionGERAN_SF_ToString(uint32_t indent) const;
    std::string t_ReselectionGERAN_SF_ToStringNoNewLines() const;
    int t_ReselectionGERAN_SF_Clear();
    bool t_ReselectionGERAN_SF_IsPresent() const;
private:
    bool t_ReselectionGERAN_SF_present;
    SpeedStateScaleFactors t_ReselectionGERAN_SF;

    // carrierFreqsInfoList
public:
    CarrierFreqsInfoListGERAN* carrierFreqsInfoList_Set();
    int carrierFreqsInfoList_Set(CarrierFreqsInfoListGERAN &value);
    const CarrierFreqsInfoListGERAN& carrierFreqsInfoList_Get() const;
    std::string carrierFreqsInfoList_ToString(uint32_t indent) const;
    std::string carrierFreqsInfoList_ToStringNoNewLines() const;
    int carrierFreqsInfoList_Clear();
    bool carrierFreqsInfoList_IsPresent() const;
private:
    bool carrierFreqsInfoList_present;
    CarrierFreqsInfoListGERAN carrierFreqsInfoList;

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
