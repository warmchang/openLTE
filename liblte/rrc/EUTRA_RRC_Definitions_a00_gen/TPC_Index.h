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

#ifndef __TPC_Index_H__
#define __TPC_Index_H__

#include <array>
#include <cstdint>
#include <vector>

class TPC_Index
{
public:
    enum Enum {
        k_indexOfFormat3 = 0,
        k_indexOfFormat3A,
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

    // indexOfFormat3
public:
    int indexOfFormat3_Pack(std::vector<uint8_t> &bits);
    int indexOfFormat3_Unpack(std::vector<uint8_t> bits);
    int indexOfFormat3_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t indexOfFormat3_Value() const;
    int indexOfFormat3_SetValue(int64_t value);
    std::string indexOfFormat3_ToString(uint32_t indent) const;
    std::string indexOfFormat3_ToStringNoNewLines() const;
    int indexOfFormat3_Clear();
    bool indexOfFormat3_IsPresent() const;
private:
    bool indexOfFormat3_present;
    int64_t indexOfFormat3_internal_value;

    // indexOfFormat3A
public:
    int indexOfFormat3A_Pack(std::vector<uint8_t> &bits);
    int indexOfFormat3A_Unpack(std::vector<uint8_t> bits);
    int indexOfFormat3A_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t indexOfFormat3A_Value() const;
    int indexOfFormat3A_SetValue(int64_t value);
    std::string indexOfFormat3A_ToString(uint32_t indent) const;
    std::string indexOfFormat3A_ToStringNoNewLines() const;
    int indexOfFormat3A_Clear();
    bool indexOfFormat3A_IsPresent() const;
private:
    bool indexOfFormat3A_present;
    int64_t indexOfFormat3A_internal_value;

};

#endif
