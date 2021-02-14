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

#ifndef __InitialUE_Identity_H__
#define __InitialUE_Identity_H__

#include "S_TMSI.h"

#include <array>
#include <cstdint>
#include <vector>

class InitialUE_Identity
{
public:
    enum Enum {
        k_s_TMSI = 0,
        k_randomValue,
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

    // randomValue
public:
    int randomValue_Pack(std::vector<uint8_t> &bits);
    int randomValue_Unpack(std::vector<uint8_t> bits);
    int randomValue_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    uint64_t randomValue_Value() const;
    int randomValue_SetValue(uint64_t value);
    std::string randomValue_ToString(uint32_t indent) const;
    std::string randomValue_ToStringNoNewLines() const;
    int randomValue_Clear();
    bool randomValue_IsPresent() const;
private:
    bool randomValue_present;
    uint64_t randomValue_internal_value;

};

#endif
