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

#ifndef __E_CSFB_r9_H__
#define __E_CSFB_r9_H__

#include "CarrierFreqCDMA2000.h"

#include <array>
#include <cstdint>
#include <vector>

class E_CSFB_r9
{
public:
    E_CSFB_r9() : messageContCDMA2000_1XRTT_r9_present{false}, mobilityCDMA2000_HRPD_r9_present{false}, messageContCDMA2000_HRPD_r9_present{false}, redirectCarrierCDMA2000_HRPD_r9_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // messageContCDMA2000-1XRTT-r9
public:
    int messageContCDMA2000_1XRTT_r9_Pack(std::vector<uint8_t> &bits);
    int messageContCDMA2000_1XRTT_r9_Unpack(std::vector<uint8_t> bits);
    int messageContCDMA2000_1XRTT_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::vector<uint8_t> messageContCDMA2000_1XRTT_r9_Value() const;
    int messageContCDMA2000_1XRTT_r9_SetValue(std::vector<uint8_t> value);
    std::string messageContCDMA2000_1XRTT_r9_ToString(uint32_t indent) const;
    std::string messageContCDMA2000_1XRTT_r9_ToStringNoNewLines() const;
    int messageContCDMA2000_1XRTT_r9_Clear();
    bool messageContCDMA2000_1XRTT_r9_IsPresent() const;
private:
    bool messageContCDMA2000_1XRTT_r9_present;
    std::vector<uint8_t> messageContCDMA2000_1XRTT_r9_internal_value;

    // mobilityCDMA2000-HRPD-r9
public:
    enum mobilityCDMA2000_HRPD_r9_Enum {
        k_mobilityCDMA2000_HRPD_r9_handover = 0,
        k_mobilityCDMA2000_HRPD_r9_redirection,
    };
    int mobilityCDMA2000_HRPD_r9_Pack(std::vector<uint8_t> &bits);
    int mobilityCDMA2000_HRPD_r9_Unpack(std::vector<uint8_t> bits);
    int mobilityCDMA2000_HRPD_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    mobilityCDMA2000_HRPD_r9_Enum mobilityCDMA2000_HRPD_r9_Value() const;
    int mobilityCDMA2000_HRPD_r9_SetValue(mobilityCDMA2000_HRPD_r9_Enum value);
    int mobilityCDMA2000_HRPD_r9_SetValue(std::string value);
    std::string mobilityCDMA2000_HRPD_r9_ValueToString(mobilityCDMA2000_HRPD_r9_Enum value) const;
    uint64_t mobilityCDMA2000_HRPD_r9_NumberOfValues() const;
    std::string mobilityCDMA2000_HRPD_r9_ToString(uint32_t indent) const;
    std::string mobilityCDMA2000_HRPD_r9_ToStringNoNewLines() const;
    int mobilityCDMA2000_HRPD_r9_Clear();
    bool mobilityCDMA2000_HRPD_r9_IsPresent() const;
private:
    bool mobilityCDMA2000_HRPD_r9_present;
    mobilityCDMA2000_HRPD_r9_Enum mobilityCDMA2000_HRPD_r9_internal_value;

    // messageContCDMA2000-HRPD-r9
public:
    int messageContCDMA2000_HRPD_r9_Pack(std::vector<uint8_t> &bits);
    int messageContCDMA2000_HRPD_r9_Unpack(std::vector<uint8_t> bits);
    int messageContCDMA2000_HRPD_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::vector<uint8_t> messageContCDMA2000_HRPD_r9_Value() const;
    int messageContCDMA2000_HRPD_r9_SetValue(std::vector<uint8_t> value);
    std::string messageContCDMA2000_HRPD_r9_ToString(uint32_t indent) const;
    std::string messageContCDMA2000_HRPD_r9_ToStringNoNewLines() const;
    int messageContCDMA2000_HRPD_r9_Clear();
    bool messageContCDMA2000_HRPD_r9_IsPresent() const;
private:
    bool messageContCDMA2000_HRPD_r9_present;
    std::vector<uint8_t> messageContCDMA2000_HRPD_r9_internal_value;

    // redirectCarrierCDMA2000-HRPD-r9
public:
    CarrierFreqCDMA2000* redirectCarrierCDMA2000_HRPD_r9_Set();
    int redirectCarrierCDMA2000_HRPD_r9_Set(CarrierFreqCDMA2000 &value);
    const CarrierFreqCDMA2000& redirectCarrierCDMA2000_HRPD_r9_Get() const;
    std::string redirectCarrierCDMA2000_HRPD_r9_ToString(uint32_t indent) const;
    std::string redirectCarrierCDMA2000_HRPD_r9_ToStringNoNewLines() const;
    int redirectCarrierCDMA2000_HRPD_r9_Clear();
    bool redirectCarrierCDMA2000_HRPD_r9_IsPresent() const;
private:
    bool redirectCarrierCDMA2000_HRPD_r9_present;
    CarrierFreqCDMA2000 redirectCarrierCDMA2000_HRPD_r9;

};

#endif
