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

#ifndef __IRAT_ParametersCDMA2000_1XRTT_H__
#define __IRAT_ParametersCDMA2000_1XRTT_H__

#include "SupportedBandList1XRTT.h"

#include <array>
#include <cstdint>
#include <vector>

class IRAT_ParametersCDMA2000_1XRTT
{
public:
    IRAT_ParametersCDMA2000_1XRTT() : supportedBandList1XRTT_present{false}, tx_Config1XRTT_present{false}, rx_Config1XRTT_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // supportedBandList1XRTT
public:
    SupportedBandList1XRTT* supportedBandList1XRTT_Set();
    int supportedBandList1XRTT_Set(SupportedBandList1XRTT &value);
    const SupportedBandList1XRTT& supportedBandList1XRTT_Get() const;
    std::string supportedBandList1XRTT_ToString(uint32_t indent) const;
    std::string supportedBandList1XRTT_ToStringNoNewLines() const;
    int supportedBandList1XRTT_Clear();
    bool supportedBandList1XRTT_IsPresent() const;
private:
    bool supportedBandList1XRTT_present;
    SupportedBandList1XRTT supportedBandList1XRTT;

    // tx-Config1XRTT
public:
    enum tx_Config1XRTT_Enum {
        k_tx_Config1XRTT_single = 0,
        k_tx_Config1XRTT_dual,
    };
    int tx_Config1XRTT_Pack(std::vector<uint8_t> &bits);
    int tx_Config1XRTT_Unpack(std::vector<uint8_t> bits);
    int tx_Config1XRTT_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    tx_Config1XRTT_Enum tx_Config1XRTT_Value() const;
    int tx_Config1XRTT_SetValue(tx_Config1XRTT_Enum value);
    int tx_Config1XRTT_SetValue(std::string value);
    std::string tx_Config1XRTT_ValueToString(tx_Config1XRTT_Enum value) const;
    uint64_t tx_Config1XRTT_NumberOfValues() const;
    std::string tx_Config1XRTT_ToString(uint32_t indent) const;
    std::string tx_Config1XRTT_ToStringNoNewLines() const;
    int tx_Config1XRTT_Clear();
    bool tx_Config1XRTT_IsPresent() const;
private:
    bool tx_Config1XRTT_present;
    tx_Config1XRTT_Enum tx_Config1XRTT_internal_value;

    // rx-Config1XRTT
public:
    enum rx_Config1XRTT_Enum {
        k_rx_Config1XRTT_single = 0,
        k_rx_Config1XRTT_dual,
    };
    int rx_Config1XRTT_Pack(std::vector<uint8_t> &bits);
    int rx_Config1XRTT_Unpack(std::vector<uint8_t> bits);
    int rx_Config1XRTT_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    rx_Config1XRTT_Enum rx_Config1XRTT_Value() const;
    int rx_Config1XRTT_SetValue(rx_Config1XRTT_Enum value);
    int rx_Config1XRTT_SetValue(std::string value);
    std::string rx_Config1XRTT_ValueToString(rx_Config1XRTT_Enum value) const;
    uint64_t rx_Config1XRTT_NumberOfValues() const;
    std::string rx_Config1XRTT_ToString(uint32_t indent) const;
    std::string rx_Config1XRTT_ToStringNoNewLines() const;
    int rx_Config1XRTT_Clear();
    bool rx_Config1XRTT_IsPresent() const;
private:
    bool rx_Config1XRTT_present;
    rx_Config1XRTT_Enum rx_Config1XRTT_internal_value;

};

#endif
