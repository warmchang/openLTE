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

#ifndef __PagingUE_Identity_H__
#define __PagingUE_Identity_H__

#include "S_TMSI.h"
#include "IMSI.h"

#include <array>
#include <cstdint>
#include <vector>

class PagingUE_Identity
{
public:
    PagingUE_Identity() : s_TMSI_present{false}, imsi_present{false} {};
public:
    enum Enum {
        k_s_TMSI = 0,
        k_imsi,
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

    // s-TMSI
public:
    S_TMSI* s_TMSI_Set();
    int s_TMSI_Set(S_TMSI &value);
    const S_TMSI& s_TMSI_Get() const;
    std::string s_TMSI_ToString(uint32_t indent) const;
    std::string s_TMSI_ToStringNoNewLines() const;
    int s_TMSI_Clear();
    bool s_TMSI_IsPresent() const;
private:
    bool s_TMSI_present;
    S_TMSI s_TMSI;

    // imsi
public:
    IMSI* imsi_Set();
    int imsi_Set(IMSI &value);
    const IMSI& imsi_Get() const;
    std::string imsi_ToString(uint32_t indent) const;
    std::string imsi_ToStringNoNewLines() const;
    int imsi_Clear();
    bool imsi_IsPresent() const;
private:
    bool imsi_present;
    IMSI imsi;

};

#endif
