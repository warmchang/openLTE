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

#ifndef __IdleModeMobilityControlInfo_H__
#define __IdleModeMobilityControlInfo_H__

#include "FreqPriorityListEUTRA.h"
#include "FreqsPriorityListGERAN.h"
#include "FreqPriorityListUTRA_FDD.h"
#include "FreqPriorityListUTRA_TDD.h"
#include "BandClassPriorityListHRPD.h"
#include "BandClassPriorityList1XRTT.h"

#include <array>
#include <cstdint>
#include <vector>

class IdleModeMobilityControlInfo
{
public:
    IdleModeMobilityControlInfo() : freqPriorityListEUTRA_present{false}, freqPriorityListGERAN_present{false}, freqPriorityListUTRA_FDD_present{false}, freqPriorityListUTRA_TDD_present{false}, bandClassPriorityListHRPD_present{false}, bandClassPriorityList1XRTT_present{false}, t320_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // freqPriorityListEUTRA
public:
    FreqPriorityListEUTRA* freqPriorityListEUTRA_Set();
    int freqPriorityListEUTRA_Set(FreqPriorityListEUTRA &value);
    const FreqPriorityListEUTRA& freqPriorityListEUTRA_Get() const;
    std::string freqPriorityListEUTRA_ToString(uint32_t indent) const;
    std::string freqPriorityListEUTRA_ToStringNoNewLines() const;
    int freqPriorityListEUTRA_Clear();
    bool freqPriorityListEUTRA_IsPresent() const;
private:
    bool freqPriorityListEUTRA_present;
    FreqPriorityListEUTRA freqPriorityListEUTRA;

    // freqPriorityListGERAN
public:
    FreqsPriorityListGERAN* freqPriorityListGERAN_Set();
    int freqPriorityListGERAN_Set(FreqsPriorityListGERAN &value);
    const FreqsPriorityListGERAN& freqPriorityListGERAN_Get() const;
    std::string freqPriorityListGERAN_ToString(uint32_t indent) const;
    std::string freqPriorityListGERAN_ToStringNoNewLines() const;
    int freqPriorityListGERAN_Clear();
    bool freqPriorityListGERAN_IsPresent() const;
private:
    bool freqPriorityListGERAN_present;
    FreqsPriorityListGERAN freqPriorityListGERAN;

    // freqPriorityListUTRA-FDD
public:
    FreqPriorityListUTRA_FDD* freqPriorityListUTRA_FDD_Set();
    int freqPriorityListUTRA_FDD_Set(FreqPriorityListUTRA_FDD &value);
    const FreqPriorityListUTRA_FDD& freqPriorityListUTRA_FDD_Get() const;
    std::string freqPriorityListUTRA_FDD_ToString(uint32_t indent) const;
    std::string freqPriorityListUTRA_FDD_ToStringNoNewLines() const;
    int freqPriorityListUTRA_FDD_Clear();
    bool freqPriorityListUTRA_FDD_IsPresent() const;
private:
    bool freqPriorityListUTRA_FDD_present;
    FreqPriorityListUTRA_FDD freqPriorityListUTRA_FDD;

    // freqPriorityListUTRA-TDD
public:
    FreqPriorityListUTRA_TDD* freqPriorityListUTRA_TDD_Set();
    int freqPriorityListUTRA_TDD_Set(FreqPriorityListUTRA_TDD &value);
    const FreqPriorityListUTRA_TDD& freqPriorityListUTRA_TDD_Get() const;
    std::string freqPriorityListUTRA_TDD_ToString(uint32_t indent) const;
    std::string freqPriorityListUTRA_TDD_ToStringNoNewLines() const;
    int freqPriorityListUTRA_TDD_Clear();
    bool freqPriorityListUTRA_TDD_IsPresent() const;
private:
    bool freqPriorityListUTRA_TDD_present;
    FreqPriorityListUTRA_TDD freqPriorityListUTRA_TDD;

    // bandClassPriorityListHRPD
public:
    BandClassPriorityListHRPD* bandClassPriorityListHRPD_Set();
    int bandClassPriorityListHRPD_Set(BandClassPriorityListHRPD &value);
    const BandClassPriorityListHRPD& bandClassPriorityListHRPD_Get() const;
    std::string bandClassPriorityListHRPD_ToString(uint32_t indent) const;
    std::string bandClassPriorityListHRPD_ToStringNoNewLines() const;
    int bandClassPriorityListHRPD_Clear();
    bool bandClassPriorityListHRPD_IsPresent() const;
private:
    bool bandClassPriorityListHRPD_present;
    BandClassPriorityListHRPD bandClassPriorityListHRPD;

    // bandClassPriorityList1XRTT
public:
    BandClassPriorityList1XRTT* bandClassPriorityList1XRTT_Set();
    int bandClassPriorityList1XRTT_Set(BandClassPriorityList1XRTT &value);
    const BandClassPriorityList1XRTT& bandClassPriorityList1XRTT_Get() const;
    std::string bandClassPriorityList1XRTT_ToString(uint32_t indent) const;
    std::string bandClassPriorityList1XRTT_ToStringNoNewLines() const;
    int bandClassPriorityList1XRTT_Clear();
    bool bandClassPriorityList1XRTT_IsPresent() const;
private:
    bool bandClassPriorityList1XRTT_present;
    BandClassPriorityList1XRTT bandClassPriorityList1XRTT;

    // t320
public:
    enum t320_Enum {
        k_t320_min5 = 0,
        k_t320_min10,
        k_t320_min20,
        k_t320_min30,
        k_t320_min60,
        k_t320_min120,
        k_t320_min180,
        k_t320_spare1,
    };
    int t320_Pack(std::vector<uint8_t> &bits);
    int t320_Unpack(std::vector<uint8_t> bits);
    int t320_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    t320_Enum t320_Value() const;
    int t320_SetValue(t320_Enum value);
    int t320_SetValue(std::string value);
    std::string t320_ValueToString(t320_Enum value) const;
    uint64_t t320_NumberOfValues() const;
    std::string t320_ToString(uint32_t indent) const;
    std::string t320_ToStringNoNewLines() const;
    int t320_Clear();
    bool t320_IsPresent() const;
private:
    bool t320_present;
    t320_Enum t320_internal_value;

};

#endif
