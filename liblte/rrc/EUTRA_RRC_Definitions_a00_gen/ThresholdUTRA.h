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

#ifndef __ThresholdUTRA_H__
#define __ThresholdUTRA_H__

#include <array>
#include <cstdint>
#include <vector>

class ThresholdUTRA
{
public:
    enum Enum {
        k_utra_RSCP = 0,
        k_utra_EcN0,
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

    // utra-RSCP
public:
    int utra_RSCP_Pack(std::vector<uint8_t> &bits);
    int utra_RSCP_Unpack(std::vector<uint8_t> bits);
    int utra_RSCP_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t utra_RSCP_Value() const;
    int utra_RSCP_SetValue(int64_t value);
    std::string utra_RSCP_ToString(uint32_t indent) const;
    std::string utra_RSCP_ToStringNoNewLines() const;
    int utra_RSCP_Clear();
    bool utra_RSCP_IsPresent() const;
private:
    bool utra_RSCP_present;
    int64_t utra_RSCP_internal_value;

    // utra-EcN0
public:
    int utra_EcN0_Pack(std::vector<uint8_t> &bits);
    int utra_EcN0_Unpack(std::vector<uint8_t> bits);
    int utra_EcN0_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t utra_EcN0_Value() const;
    int utra_EcN0_SetValue(int64_t value);
    std::string utra_EcN0_ToString(uint32_t indent) const;
    std::string utra_EcN0_ToStringNoNewLines() const;
    int utra_EcN0_Clear();
    bool utra_EcN0_IsPresent() const;
private:
    bool utra_EcN0_present;
    int64_t utra_EcN0_internal_value;

};

#endif
