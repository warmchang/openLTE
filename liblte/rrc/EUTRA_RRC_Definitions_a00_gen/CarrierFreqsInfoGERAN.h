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

#ifndef __CarrierFreqsInfoGERAN_H__
#define __CarrierFreqsInfoGERAN_H__

#include "CarrierFreqsGERAN.h"
#include "CellReselectionPriority.h"
#include "ReselectionThreshold.h"
#include "ReselectionThreshold.h"

#include <array>
#include <cstdint>
#include <vector>

class CarrierFreqsInfoGERAN
{
public:
    CarrierFreqsInfoGERAN() : carrierFreqs_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // carrierFreqs
public:
    CarrierFreqsGERAN* carrierFreqs_Set();
    int carrierFreqs_Set(CarrierFreqsGERAN &value);
    const CarrierFreqsGERAN& carrierFreqs_Get() const;
    std::string carrierFreqs_ToString(uint32_t indent) const;
    std::string carrierFreqs_ToStringNoNewLines() const;
    int carrierFreqs_Clear();
    bool carrierFreqs_IsPresent() const;
private:
    bool carrierFreqs_present;
    CarrierFreqsGERAN carrierFreqs;

    // commonInfo
public:
    class commonInfo
    {
    public:
        commonInfo() : cellReselectionPriority_present{false}, ncc_Permitted_present{false}, q_RxLevMin_present{false}, p_MaxGERAN_present{false}, threshX_High_present{false}, threshX_Low_present{false} {};
    public:
        int Pack(std::vector<uint8_t> &bits);
        int Unpack(std::vector<uint8_t> bits);
        int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        std::string ToString(uint32_t indent) const;
        std::string ToStringNoNewLines() const;

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

        // ncc-Permitted
    public:
        int ncc_Permitted_Pack(std::vector<uint8_t> &bits);
        int ncc_Permitted_Unpack(std::vector<uint8_t> bits);
        int ncc_Permitted_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        uint8_t ncc_Permitted_Value() const;
        int ncc_Permitted_SetValue(uint8_t value);
        std::string ncc_Permitted_ToString(uint32_t indent) const;
        std::string ncc_Permitted_ToStringNoNewLines() const;
        int ncc_Permitted_Clear();
        bool ncc_Permitted_IsPresent() const;
    private:
        bool ncc_Permitted_present;
        uint8_t ncc_Permitted_internal_value;

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

        // p-MaxGERAN
    public:
        int p_MaxGERAN_Pack(std::vector<uint8_t> &bits);
        int p_MaxGERAN_Unpack(std::vector<uint8_t> bits);
        int p_MaxGERAN_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        int64_t p_MaxGERAN_Value() const;
        int p_MaxGERAN_SetValue(int64_t value);
        std::string p_MaxGERAN_ToString(uint32_t indent) const;
        std::string p_MaxGERAN_ToStringNoNewLines() const;
        int p_MaxGERAN_Clear();
        bool p_MaxGERAN_IsPresent() const;
    private:
        bool p_MaxGERAN_present;
        int64_t p_MaxGERAN_internal_value;

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

    };

    commonInfo commonInfo_value;

};

#endif
