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

#ifndef __UL_AM_RLC_H__
#define __UL_AM_RLC_H__

#include "T_PollRetransmit.h"
#include "PollPDU.h"
#include "PollByte.h"

#include <array>
#include <cstdint>
#include <vector>

class UL_AM_RLC
{
public:
    UL_AM_RLC() : t_PollRetransmit_present{false}, pollPDU_present{false}, pollByte_present{false}, maxRetxThreshold_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // t-PollRetransmit
public:
    T_PollRetransmit* t_PollRetransmit_Set();
    int t_PollRetransmit_Set(T_PollRetransmit &value);
    const T_PollRetransmit& t_PollRetransmit_Get() const;
    std::string t_PollRetransmit_ToString(uint32_t indent) const;
    std::string t_PollRetransmit_ToStringNoNewLines() const;
    int t_PollRetransmit_Clear();
    bool t_PollRetransmit_IsPresent() const;
private:
    bool t_PollRetransmit_present;
    T_PollRetransmit t_PollRetransmit;

    // pollPDU
public:
    PollPDU* pollPDU_Set();
    int pollPDU_Set(PollPDU &value);
    const PollPDU& pollPDU_Get() const;
    std::string pollPDU_ToString(uint32_t indent) const;
    std::string pollPDU_ToStringNoNewLines() const;
    int pollPDU_Clear();
    bool pollPDU_IsPresent() const;
private:
    bool pollPDU_present;
    PollPDU pollPDU;

    // pollByte
public:
    PollByte* pollByte_Set();
    int pollByte_Set(PollByte &value);
    const PollByte& pollByte_Get() const;
    std::string pollByte_ToString(uint32_t indent) const;
    std::string pollByte_ToStringNoNewLines() const;
    int pollByte_Clear();
    bool pollByte_IsPresent() const;
private:
    bool pollByte_present;
    PollByte pollByte;

    // maxRetxThreshold
public:
    enum maxRetxThreshold_Enum {
        k_maxRetxThreshold_t1 = 0,
        k_maxRetxThreshold_t2,
        k_maxRetxThreshold_t3,
        k_maxRetxThreshold_t4,
        k_maxRetxThreshold_t6,
        k_maxRetxThreshold_t8,
        k_maxRetxThreshold_t16,
        k_maxRetxThreshold_t32,
    };
    int maxRetxThreshold_Pack(std::vector<uint8_t> &bits);
    int maxRetxThreshold_Unpack(std::vector<uint8_t> bits);
    int maxRetxThreshold_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    maxRetxThreshold_Enum maxRetxThreshold_Value() const;
    int maxRetxThreshold_SetValue(maxRetxThreshold_Enum value);
    int maxRetxThreshold_SetValue(std::string value);
    std::string maxRetxThreshold_ValueToString(maxRetxThreshold_Enum value) const;
    uint64_t maxRetxThreshold_NumberOfValues() const;
    std::string maxRetxThreshold_ToString(uint32_t indent) const;
    std::string maxRetxThreshold_ToStringNoNewLines() const;
    int maxRetxThreshold_Clear();
    bool maxRetxThreshold_IsPresent() const;
private:
    bool maxRetxThreshold_present;
    maxRetxThreshold_Enum maxRetxThreshold_internal_value;

};

#endif
