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

#ifndef __CellGlobalIdCDMA2000_H__
#define __CellGlobalIdCDMA2000_H__

#include <array>
#include <cstdint>
#include <vector>

class CellGlobalIdCDMA2000
{
public:
    enum Enum {
        k_cellGlobalId1XRTT = 0,
        k_cellGlobalIdHRPD,
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

    // cellGlobalId1XRTT
public:
    int cellGlobalId1XRTT_Pack(std::vector<uint8_t> &bits);
    int cellGlobalId1XRTT_Unpack(std::vector<uint8_t> bits);
    int cellGlobalId1XRTT_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    uint64_t cellGlobalId1XRTT_Value() const;
    int cellGlobalId1XRTT_SetValue(uint64_t value);
    std::string cellGlobalId1XRTT_ToString(uint32_t indent) const;
    std::string cellGlobalId1XRTT_ToStringNoNewLines() const;
    int cellGlobalId1XRTT_Clear();
    bool cellGlobalId1XRTT_IsPresent() const;
private:
    bool cellGlobalId1XRTT_present;
    uint64_t cellGlobalId1XRTT_internal_value;

    // cellGlobalIdHRPD
public:
    int cellGlobalIdHRPD_Pack(std::vector<uint8_t> &bits);
    int cellGlobalIdHRPD_Unpack(std::vector<uint8_t> bits);
    int cellGlobalIdHRPD_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::vector<uint8_t> cellGlobalIdHRPD_Value() const;
    int cellGlobalIdHRPD_SetValue(std::vector<uint8_t> value);
    std::string cellGlobalIdHRPD_ToString(uint32_t indent) const;
    std::string cellGlobalIdHRPD_ToStringNoNewLines() const;
    int cellGlobalIdHRPD_Clear();
    bool cellGlobalIdHRPD_IsPresent() const;
private:
    bool cellGlobalIdHRPD_present;
    std::vector<uint8_t> cellGlobalIdHRPD_internal_value;

};

#endif
