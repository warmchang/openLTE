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

#ifndef __IRAT_ParametersCDMA2000_HRPD_H__
#define __IRAT_ParametersCDMA2000_HRPD_H__

#include "SupportedBandListHRPD.h"

#include <array>
#include <cstdint>
#include <vector>

class IRAT_ParametersCDMA2000_HRPD
{
public:
    IRAT_ParametersCDMA2000_HRPD() : supportedBandListHRPD_present{false}, tx_ConfigHRPD_present{false}, rx_ConfigHRPD_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // supportedBandListHRPD
public:
    SupportedBandListHRPD* supportedBandListHRPD_Set();
    int supportedBandListHRPD_Set(SupportedBandListHRPD &value);
    const SupportedBandListHRPD& supportedBandListHRPD_Get() const;
    std::string supportedBandListHRPD_ToString(uint32_t indent) const;
    std::string supportedBandListHRPD_ToStringNoNewLines() const;
    int supportedBandListHRPD_Clear();
    bool supportedBandListHRPD_IsPresent() const;
private:
    bool supportedBandListHRPD_present;
    SupportedBandListHRPD supportedBandListHRPD;

    // tx-ConfigHRPD
public:
    enum tx_ConfigHRPD_Enum {
        k_tx_ConfigHRPD_single = 0,
        k_tx_ConfigHRPD_dual,
    };
    int tx_ConfigHRPD_Pack(std::vector<uint8_t> &bits);
    int tx_ConfigHRPD_Unpack(std::vector<uint8_t> bits);
    int tx_ConfigHRPD_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    tx_ConfigHRPD_Enum tx_ConfigHRPD_Value() const;
    int tx_ConfigHRPD_SetValue(tx_ConfigHRPD_Enum value);
    int tx_ConfigHRPD_SetValue(std::string value);
    std::string tx_ConfigHRPD_ValueToString(tx_ConfigHRPD_Enum value) const;
    uint64_t tx_ConfigHRPD_NumberOfValues() const;
    std::string tx_ConfigHRPD_ToString(uint32_t indent) const;
    std::string tx_ConfigHRPD_ToStringNoNewLines() const;
    int tx_ConfigHRPD_Clear();
    bool tx_ConfigHRPD_IsPresent() const;
private:
    bool tx_ConfigHRPD_present;
    tx_ConfigHRPD_Enum tx_ConfigHRPD_internal_value;

    // rx-ConfigHRPD
public:
    enum rx_ConfigHRPD_Enum {
        k_rx_ConfigHRPD_single = 0,
        k_rx_ConfigHRPD_dual,
    };
    int rx_ConfigHRPD_Pack(std::vector<uint8_t> &bits);
    int rx_ConfigHRPD_Unpack(std::vector<uint8_t> bits);
    int rx_ConfigHRPD_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    rx_ConfigHRPD_Enum rx_ConfigHRPD_Value() const;
    int rx_ConfigHRPD_SetValue(rx_ConfigHRPD_Enum value);
    int rx_ConfigHRPD_SetValue(std::string value);
    std::string rx_ConfigHRPD_ValueToString(rx_ConfigHRPD_Enum value) const;
    uint64_t rx_ConfigHRPD_NumberOfValues() const;
    std::string rx_ConfigHRPD_ToString(uint32_t indent) const;
    std::string rx_ConfigHRPD_ToStringNoNewLines() const;
    int rx_ConfigHRPD_Clear();
    bool rx_ConfigHRPD_IsPresent() const;
private:
    bool rx_ConfigHRPD_present;
    rx_ConfigHRPD_Enum rx_ConfigHRPD_internal_value;

};

#endif
