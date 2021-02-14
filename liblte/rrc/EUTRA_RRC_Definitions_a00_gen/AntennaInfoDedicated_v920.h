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

#ifndef __AntennaInfoDedicated_v920_H__
#define __AntennaInfoDedicated_v920_H__

#include <array>
#include <cstdint>
#include <vector>

class AntennaInfoDedicated_v920
{
public:
    AntennaInfoDedicated_v920() : codebookSubsetRestriction_v920_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // codebookSubsetRestriction-v920
public:
    enum codebookSubsetRestriction_v920_Enum {
        k_codebookSubsetRestriction_v920_n2TxAntenna_tm8_r9 = 0,
        k_codebookSubsetRestriction_v920_n4TxAntenna_tm8_r9,
    };
    int codebookSubsetRestriction_v920_Pack(std::vector<uint8_t> &bits);
    int codebookSubsetRestriction_v920_Unpack(std::vector<uint8_t> bits);
    int codebookSubsetRestriction_v920_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    codebookSubsetRestriction_v920_Enum codebookSubsetRestriction_v920_Choice() const;
    int codebookSubsetRestriction_v920_SetChoice(codebookSubsetRestriction_v920_Enum choice);
    std::string codebookSubsetRestriction_v920_ChoiceToString(codebookSubsetRestriction_v920_Enum value) const;
    uint64_t codebookSubsetRestriction_v920_NumberOfChoices() const;
    std::string codebookSubsetRestriction_v920_ToString(uint32_t indent) const;
    std::string codebookSubsetRestriction_v920_ToStringNoNewLines() const;
    int codebookSubsetRestriction_v920_Clear();
    bool codebookSubsetRestriction_v920_IsPresent() const;
private:
    bool codebookSubsetRestriction_v920_present;
    codebookSubsetRestriction_v920_Enum codebookSubsetRestriction_v920_internal_choice;

    // n2TxAntenna-tm8-r9
public:
    int codebookSubsetRestriction_v920_n2TxAntenna_tm8_r9_Pack(std::vector<uint8_t> &bits);
    int codebookSubsetRestriction_v920_n2TxAntenna_tm8_r9_Unpack(std::vector<uint8_t> bits);
    int codebookSubsetRestriction_v920_n2TxAntenna_tm8_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    uint8_t codebookSubsetRestriction_v920_n2TxAntenna_tm8_r9_Value() const;
    int codebookSubsetRestriction_v920_n2TxAntenna_tm8_r9_SetValue(uint8_t value);
    std::string codebookSubsetRestriction_v920_n2TxAntenna_tm8_r9_ToString(uint32_t indent) const;
    std::string codebookSubsetRestriction_v920_n2TxAntenna_tm8_r9_ToStringNoNewLines() const;
    int codebookSubsetRestriction_v920_n2TxAntenna_tm8_r9_Clear();
    bool codebookSubsetRestriction_v920_n2TxAntenna_tm8_r9_IsPresent() const;
private:
    bool codebookSubsetRestriction_v920_n2TxAntenna_tm8_r9_present;
    uint8_t codebookSubsetRestriction_v920_n2TxAntenna_tm8_r9_internal_value;

    // n4TxAntenna-tm8-r9
public:
    int codebookSubsetRestriction_v920_n4TxAntenna_tm8_r9_Pack(std::vector<uint8_t> &bits);
    int codebookSubsetRestriction_v920_n4TxAntenna_tm8_r9_Unpack(std::vector<uint8_t> bits);
    int codebookSubsetRestriction_v920_n4TxAntenna_tm8_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    uint32_t codebookSubsetRestriction_v920_n4TxAntenna_tm8_r9_Value() const;
    int codebookSubsetRestriction_v920_n4TxAntenna_tm8_r9_SetValue(uint32_t value);
    std::string codebookSubsetRestriction_v920_n4TxAntenna_tm8_r9_ToString(uint32_t indent) const;
    std::string codebookSubsetRestriction_v920_n4TxAntenna_tm8_r9_ToStringNoNewLines() const;
    int codebookSubsetRestriction_v920_n4TxAntenna_tm8_r9_Clear();
    bool codebookSubsetRestriction_v920_n4TxAntenna_tm8_r9_IsPresent() const;
private:
    bool codebookSubsetRestriction_v920_n4TxAntenna_tm8_r9_present;
    uint32_t codebookSubsetRestriction_v920_n4TxAntenna_tm8_r9_internal_value;


};

#endif
