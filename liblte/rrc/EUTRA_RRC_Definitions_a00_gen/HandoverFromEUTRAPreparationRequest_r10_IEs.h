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

#ifndef __HandoverFromEUTRAPreparationRequest_r10_IEs_H__
#define __HandoverFromEUTRAPreparationRequest_r10_IEs_H__

#include "CarrierFreqCDMA2000.h"

#include <array>
#include <cstdint>
#include <vector>

class HandoverFromEUTRAPreparationRequest_r10_IEs
{
public:
    HandoverFromEUTRAPreparationRequest_r10_IEs() : dualRxTxRedirectIndicator_r10_present{false}, redirectCarrierCDMA2000_1XRTT_r10_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // dualRxTxRedirectIndicator-r10
public:
    enum dualRxTxRedirectIndicator_r10_Enum {
        k_dualRxTxRedirectIndicator_r10_true = 0,
    };
    int dualRxTxRedirectIndicator_r10_Pack(std::vector<uint8_t> &bits);
    int dualRxTxRedirectIndicator_r10_Unpack(std::vector<uint8_t> bits);
    int dualRxTxRedirectIndicator_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    dualRxTxRedirectIndicator_r10_Enum dualRxTxRedirectIndicator_r10_Value() const;
    int dualRxTxRedirectIndicator_r10_SetValue(dualRxTxRedirectIndicator_r10_Enum value);
    int dualRxTxRedirectIndicator_r10_SetValue(std::string value);
    std::string dualRxTxRedirectIndicator_r10_ValueToString(dualRxTxRedirectIndicator_r10_Enum value) const;
    uint64_t dualRxTxRedirectIndicator_r10_NumberOfValues() const;
    std::string dualRxTxRedirectIndicator_r10_ToString(uint32_t indent) const;
    std::string dualRxTxRedirectIndicator_r10_ToStringNoNewLines() const;
    int dualRxTxRedirectIndicator_r10_Clear();
    bool dualRxTxRedirectIndicator_r10_IsPresent() const;
private:
    bool dualRxTxRedirectIndicator_r10_present;
    dualRxTxRedirectIndicator_r10_Enum dualRxTxRedirectIndicator_r10_internal_value;

    // redirectCarrierCDMA2000-1XRTT-r10
public:
    CarrierFreqCDMA2000* redirectCarrierCDMA2000_1XRTT_r10_Set();
    int redirectCarrierCDMA2000_1XRTT_r10_Set(CarrierFreqCDMA2000 &value);
    const CarrierFreqCDMA2000& redirectCarrierCDMA2000_1XRTT_r10_Get() const;
    std::string redirectCarrierCDMA2000_1XRTT_r10_ToString(uint32_t indent) const;
    std::string redirectCarrierCDMA2000_1XRTT_r10_ToStringNoNewLines() const;
    int redirectCarrierCDMA2000_1XRTT_r10_Clear();
    bool redirectCarrierCDMA2000_1XRTT_r10_IsPresent() const;
private:
    bool redirectCarrierCDMA2000_1XRTT_r10_present;
    CarrierFreqCDMA2000 redirectCarrierCDMA2000_1XRTT_r10;

    // nonCriticalExtension

};

#endif
