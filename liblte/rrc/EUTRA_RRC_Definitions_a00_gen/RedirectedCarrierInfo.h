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

#ifndef __RedirectedCarrierInfo_H__
#define __RedirectedCarrierInfo_H__

#include "ARFCN_ValueEUTRA.h"
#include "CarrierFreqsGERAN.h"
#include "ARFCN_ValueUTRA.h"
#include "ARFCN_ValueUTRA.h"
#include "CarrierFreqCDMA2000.h"
#include "CarrierFreqCDMA2000.h"

#include <array>
#include <cstdint>
#include <vector>

class RedirectedCarrierInfo
{
public:
    RedirectedCarrierInfo() : eutra_present{false}, geran_present{false}, utra_FDD_present{false}, utra_TDD_present{false}, cdma2000_HRPD_present{false}, cdma2000_1xRTT_present{false} {};
public:
    enum Enum {
        k_eutra = 0,
        k_geran,
        k_utra_FDD,
        k_utra_TDD,
        k_cdma2000_HRPD,
        k_cdma2000_1xRTT,
    };
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    Enum Choice() const;
    int SetChoice(Enum choice);
    std::string ChoiceToString(Enum value) const;
    uint64_t NumberOfChoices() const;
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;
    int Clear();
    bool IsPresent() const;
private:
    bool present;
    Enum internal_choice;

    // eutra
public:
    ARFCN_ValueEUTRA* eutra_Set();
    int eutra_Set(ARFCN_ValueEUTRA &value);
    const ARFCN_ValueEUTRA& eutra_Get() const;
    std::string eutra_ToString(uint32_t indent) const;
    std::string eutra_ToStringNoNewLines() const;
    int eutra_Clear();
    bool eutra_IsPresent() const;
private:
    bool eutra_present;
    ARFCN_ValueEUTRA eutra;

    // geran
public:
    CarrierFreqsGERAN* geran_Set();
    int geran_Set(CarrierFreqsGERAN &value);
    const CarrierFreqsGERAN& geran_Get() const;
    std::string geran_ToString(uint32_t indent) const;
    std::string geran_ToStringNoNewLines() const;
    int geran_Clear();
    bool geran_IsPresent() const;
private:
    bool geran_present;
    CarrierFreqsGERAN geran;

    // utra-FDD
public:
    ARFCN_ValueUTRA* utra_FDD_Set();
    int utra_FDD_Set(ARFCN_ValueUTRA &value);
    const ARFCN_ValueUTRA& utra_FDD_Get() const;
    std::string utra_FDD_ToString(uint32_t indent) const;
    std::string utra_FDD_ToStringNoNewLines() const;
    int utra_FDD_Clear();
    bool utra_FDD_IsPresent() const;
private:
    bool utra_FDD_present;
    ARFCN_ValueUTRA utra_FDD;

    // utra-TDD
public:
    ARFCN_ValueUTRA* utra_TDD_Set();
    int utra_TDD_Set(ARFCN_ValueUTRA &value);
    const ARFCN_ValueUTRA& utra_TDD_Get() const;
    std::string utra_TDD_ToString(uint32_t indent) const;
    std::string utra_TDD_ToStringNoNewLines() const;
    int utra_TDD_Clear();
    bool utra_TDD_IsPresent() const;
private:
    bool utra_TDD_present;
    ARFCN_ValueUTRA utra_TDD;

    // cdma2000-HRPD
public:
    CarrierFreqCDMA2000* cdma2000_HRPD_Set();
    int cdma2000_HRPD_Set(CarrierFreqCDMA2000 &value);
    const CarrierFreqCDMA2000& cdma2000_HRPD_Get() const;
    std::string cdma2000_HRPD_ToString(uint32_t indent) const;
    std::string cdma2000_HRPD_ToStringNoNewLines() const;
    int cdma2000_HRPD_Clear();
    bool cdma2000_HRPD_IsPresent() const;
private:
    bool cdma2000_HRPD_present;
    CarrierFreqCDMA2000 cdma2000_HRPD;

    // cdma2000-1xRTT
public:
    CarrierFreqCDMA2000* cdma2000_1xRTT_Set();
    int cdma2000_1xRTT_Set(CarrierFreqCDMA2000 &value);
    const CarrierFreqCDMA2000& cdma2000_1xRTT_Get() const;
    std::string cdma2000_1xRTT_ToString(uint32_t indent) const;
    std::string cdma2000_1xRTT_ToStringNoNewLines() const;
    int cdma2000_1xRTT_Clear();
    bool cdma2000_1xRTT_IsPresent() const;
private:
    bool cdma2000_1xRTT_present;
    CarrierFreqCDMA2000 cdma2000_1xRTT;

};

#endif
